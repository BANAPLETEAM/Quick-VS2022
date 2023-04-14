#include "stdafx.h"

#include "MkDatabase.h"
#include "MkType.h"
#include "MkRecordset.h"
#include "MkCommand.h"
#include "QueryLogDlg.h"
#include "QSocket.h"
#include "MkLock.h"

CStringArray CMkCommand::m_saExecute;
CDisplayBarProgressInfo CMkCommand::m_dbpiBasic("처리중입니다.", 0);


#define MAX_PARAMETER_LENGTH	8192	

CMkCommand::CMkCommand(void)
{
	m_hRunningThread = NULL;
	m_hUserStopEvent = NULL;
	m_pDatabase = NULL;
	CMkDatabase::AddRefCommand(this);
	//SetMkCommand(NULL, "", FALSE, FALSE);
}

CMkCommand::CMkCommand(CMkDatabase *pDatabase, BOOL bPreventCancel, BOOL bNoThreadMode)
{
	SetMkCommand(pDatabase, "", bPreventCancel, bNoThreadMode);
}

CMkCommand::CMkCommand(CMkDatabase *pDatabase, CString strCommandText, BOOL bPreventCancel, BOOL bNoThreadMode)
{
	SetMkCommand(pDatabase, strCommandText, bPreventCancel, bNoThreadMode);
}

CMkCommand::~CMkCommand(void)
{
	CMkDatabase::RemoveRefCommand(this);

	for(int i = 0; i < m_Parameter.GetCount(); i++)
	{
		CMkParameter *pParameter = m_Parameter.GetAt(i);
		delete pParameter;
	}

	if(m_hRunningThread)
		CloseHandle(m_hRunningThread);
	if(m_hUserStopEvent)
		CloseHandle(m_hUserStopEvent);
}

void CMkCommand::SetDatabase(CMkDatabase *pDatabase)
{
	m_pDatabase = pDatabase;
}

void CMkCommand::SetMkCommand(CMkDatabase *pDatabase, CString strCommandText, BOOL bPreventCancel, BOOL bNoThreadMode)
{
	CMkDatabase::AddRefCommand(this);

	m_pDatabase = pDatabase;

	m_pRecordset = NULL;
	m_nParameterSize = 0;
	m_strCommandText = strCommandText;
	m_bHideWaitCursor = FALSE;
	m_hRunningThread = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hUserStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bNoThreadMode = bNoThreadMode;
	
	if(m_strCommandText.Find("insert_", 0) >= 0 || 
		m_strCommandText.Find("update_", 0) >= 0 ||
		m_strCommandText.Find("delete_", 0) >= 0 ||
		m_strCommandText.Find("change_", 0) >= 0)
	{
		m_bPreventCancel = TRUE;
	}
	else
	{
		m_bPreventCancel = bPreventCancel;
	}

	m_strQueryDebugInfo = strCommandText + " ";
	if(m_pDatabase)
		m_pDatabase->SetEnteringCmd(this);
}


CMkParameter* CMkCommand::AddParameter(CMkParameter *pParameter)
{
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();
	return pParameter;
}


CMkParameter* CMkCommand::AddParameter(int nValue, enum cmkDir nDirection)
{
	CMkParameter *pParameter = new CMkParameter(nValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";

	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("int:%s\n", strTemp);

	return pParameter;
}


CMkParameter* CMkCommand::AddParameter(UINT nValue, enum cmkDir nDirection)
{
	CMkParameter *pParameter = new CMkParameter(nValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("UINT:%s\n", strTemp);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(long nValue, enum cmkDir nDirection)
{
	CMkParameter *pParameter = new CMkParameter(nValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("long:%d\n", nValue);

	return pParameter;
}


CMkParameter* CMkCommand::AddParameter(double fValue, enum cmkDir nDirection)
{
	CMkParameter *pParameter = new CMkParameter(fValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%f", fValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("float:%f\n", fValue);

	return pParameter;
}

void CMkCommand::MsgInvalidStringParameter()
{
	AfxGetMainWnd()->MessageBox("AddParameter에서 CString의 output은 사이즈를 지정해야 합니다.\n"\
		"AddParameter(CString strValue, long nSize, enum cmkDir nDirection) 함수를 참조바람", 
		"CMkCommand",
		MB_ICONERROR);
}

CMkParameter* CMkCommand::AddParameter(CString strValue, enum cmkDir nDirection)
{
	if(nDirection >= typeOutput)
		MsgInvalidStringParameter();

	CMkParameter *pParameter = new CMkParameter(strValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", strValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("str:%s\n", strValue);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(CString strValue, long nSize, enum cmkDir nDirection)
{
	if(nDirection >= typeOutput && nSize == 0)
		MsgInvalidStringParameter();

	CMkParameter *pParameter = new CMkParameter(strValue, nSize, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", strValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("str:%s\n", strValue);

	return pParameter;
}



CMkParameter* CMkCommand::AddParameter(COleDateTime dtValue, enum cmkDir nDirection)
{
	CMkParameter *pParameter = new CMkParameter(dtValue, nDirection);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", dtValue.Format("%Y-%m-%d %H:%M:%S"));
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("time:%s\n", strTemp);

	return pParameter;
}



CMkParameter* CMkCommand::AddParameterRef(int &nValue, enum cmkDir nDirection, BOOL bRefValue)
{
	CMkParameter *pParameter = new CMkParameter(nValue, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("int:%s\n", strTemp);

	return pParameter;
}



CMkParameter* CMkCommand::AddParameterRef(long &nValue, enum cmkDir nDirection, BOOL bRefValue)
{
	CMkParameter *pParameter = new CMkParameter(nValue, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("long:%d\n", nValue);

	return pParameter;
}


CMkParameter* CMkCommand::AddParameterRef(double &fValue, enum cmkDir nDirection, BOOL bRefValue)
{
	CMkParameter *pParameter = new CMkParameter(fValue, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("%f", fValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("float:%f\n", fValue);

	return pParameter;
}


CMkParameter* CMkCommand::AddParameterRef(CString &strValue, enum cmkDir nDirection, BOOL bRefValue)
{
	if(nDirection >= typeOutput)
		MsgInvalidStringParameter();

	CMkParameter *pParameter = new CMkParameter(strValue, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", strValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("str:%s\n", strValue);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameterRef(CString &strValue, long nSize, enum cmkDir nDirection, BOOL bRefValue)
{
	if(nDirection >= typeOutput && nSize == 0)
		MsgInvalidStringParameter();

	CMkParameter *pParameter = new CMkParameter(strValue, nSize, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", strValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("str:%s\n", strValue);

	return pParameter;
}



CMkParameter* CMkCommand::AddParameterRef(COleDateTime &dtValue, enum cmkDir nDirection, BOOL bRefValue)
{
	CMkParameter *pParameter = new CMkParameter(dtValue, nDirection, bRefValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();

	CString strTemp;
	strTemp.Format("\'%s\'", dtValue.Format("%Y-%m-%d %H:%M:%S"));
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode())
		g_bana_log->Print("time:%s\n", strTemp);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameterRefOutput(CString &strValue , long nSize)
{
	return AddParameterRef(strValue, nSize, typeOutput, TRUE);
}


CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;
	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, int nValue)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize, (void*)&nValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;

	CString strTemp;
	strTemp.Format("%d", nValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode() && nDirection != typeReturn)
		g_bana_log->Print("int:%s\n", strTemp);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, long lValue)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize, (void*)&lValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;

	CString strTemp;
	strTemp.Format("%d", lValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode() && nDirection != typeReturn)
		g_bana_log->Print("long:%d\n", lValue);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, CString strValue)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize, (LPSTR)(LPCTSTR)strValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;

	CString strTemp;
	strTemp.Format("\'%s\'", strValue);
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode() && nDirection != typeReturn)
		g_bana_log->Print("str:%s\n", strValue);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, COleDateTime time)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize, (void*)&time);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;

	CString strTemp;
	strTemp.Format("\'%s\'", time.Format("%Y-%m-%d %H:%M:%S"));
	m_strQueryDebugInfo += strTemp + ", ";
	//if(m_pDatabase->GetDeveloperMode() && nDirection != typeReturn)
		g_bana_log->Print("time:%s\n", strTemp);

	return pParameter;
}

CMkParameter* CMkCommand::AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue)
{
	CMkParameter *pParameter = new CMkParameter;
	lSize = pParameter->SetParameter(nType, nDirection, lSize, (void*)pValue);
	m_Parameter.Add(pParameter);
	m_nParameterSize += sizeof(PARAMETER_STRUCT) + lSize;
	g_bana_log->Print("void:\n");
	return pParameter;
} 

BOOL CMkCommand::Execute(CMkDatabase *pDatabase, CString strCommandText) 
{
	m_strCommandText = strCommandText;
	m_pDatabase = pDatabase;
	return Execute();
}


BOOL CMkCommand::Execute(CString strCommandText) 
{
	if(m_pDatabase == NULL)
	{
		MessageBox(NULL, "CMkDatabase가 지정되지 않았음", "일반오류", MB_ICONERROR);
		return FALSE;
	}

	m_strCommandText = strCommandText;
	return Execute();
}

BOOL CMkCommand::Execute(CMkDatabase *pDatabase)
{
	if(pDatabase)
		m_pDatabase = pDatabase;

	if(!m_pDatabase)
		return FALSE;

	g_bana_log->Print("sp:%s\t (%s,%d)\n", m_strCommandText, 
				m_pDatabase->GetCurServerAddr(), 
				m_pDatabase->GetCurServerPort());

	if(m_pDatabase->GetDeveloperMode())
	{
		m_strQueryDebugInfo.TrimRight(", ");
		m_saExecute.Add(m_strQueryDebugInfo);

		if(m_pDatabase->GetQueryLogDlg())
			m_pDatabase->GetQueryLogDlg()->AddQuery(m_strQueryDebugInfo);
	}
	else
	{
		m_pDatabase->SetLastQueryInfo(m_strQueryDebugInfo);
	}

	m_pDatabase->SetEnteringCmd(NULL);
	m_strQueryDebugInfo.Empty();


	LPVOID buffer;
	int nType = 0;
	int nCursor = 0;
	UINT nSize = sizeof(COMMAND_STRUCT) + m_nParameterSize;
	COMMAND_STRUCT *pCS = (COMMAND_STRUCT*)new char[nSize + 1];

	ZeroMemory(pCS, nSize);

	pCS->nType = typeStoredProc;
	if(m_pRecordset)
		pCS->nType |= typeRecordset;

	pCS->nVarCount = (USHORT)m_Parameter.GetCount();
	strcpy(pCS->szStoredProc, (LPSTR)(LPCTSTR)m_strCommandText); 

	DWORD dwTick = GetTickCount();

	for(int i = 0; i < m_Parameter.GetCount(); i++)
	{
		CMkParameter *pParameter = m_Parameter.GetAt(i);
		int nParSize = sizeof(PARAMETER_STRUCT) + pParameter->GetValueSize();
	    memcpy(pCS->data + nCursor, (void*)pParameter->GetParameter(), nParSize);
		nCursor += nParSize;
	}
	
	if((buffer = m_pDatabase->Execute(&nType, (void*)pCS, &nSize, m_strCommandText)) != NULL)
	{
		if(nType & typeParameter)
		{
			nCursor = 0;
			COMMAND_STRUCT *pCS = (COMMAND_STRUCT*)buffer;

			for(int c = 0; c < m_Parameter.GetCount(); c++)
			{
				CMkParameter *pParameter = m_Parameter.GetAt(c);
				if(pParameter->GetDirection() >= typeOutput)
				{
					PARAMETER_STRUCT *pPS = (PARAMETER_STRUCT*)(pCS->data + nCursor);
                    pParameter->SetValue(pPS->lSize, pPS->pValue);
					nCursor += sizeof(PARAMETER_STRUCT) + pPS->lSize;
				}
			}

			if((nType & typeRecordset) && m_pRecordset)
				m_pRecordset->SetChunk(pCS->data + nCursor, nSize - nCursor - sizeof(COMMAND_STRUCT));
		}
		else if((nType & typeRecordset) && m_pRecordset)
		{
			m_pRecordset->SetChunk(buffer, nSize);
		}

		g_bana_log->Print("(%5d)->%s)\n", GetTickCount() - dwTick, pCS->szStoredProc);
		delete[] buffer;
		delete[] (char*)pCS;
		return TRUE;
	}

	delete[] (char*)pCS;
	return FALSE;
}

CString& CMkCommand::RemakeDisplayText(CString &strDisplayText)
{
	if(GetDatabase()->GetDeveloperMode())
	{
		if(strDisplayText.GetLength() == 0)
			strDisplayText = m_strQueryDebugInfo;
		else
			strDisplayText += "\n" + m_strQueryDebugInfo;
	}
	else
	{
		if(strDisplayText.GetLength() == 0)
			strDisplayText = "잠시만 기다려주세요.";
	}

	return strDisplayText;
}

CDisplayBarThread* CMkCommand::ExecuteDisplay()
{
	CDisplayBarThread *pDBT = GetDatabase()->GetDisplayBarThread();
	pDBT->PostThreadMessage(WM_DISPLAY_BAR_PROGRESS, (LPARAM)&m_dbpiBasic, 1);
	pDBT->PostThreadMessage(WM_DISPLAY_BAR_WAIT, 1, 1);
	pDBT->PostThreadMessage(WM_DISPLAY_BAR_PREVENT_CANCEL, (WPARAM)IsPreventCancel(), 0);
	pDBT->PostThreadMessage(WM_DISPLAY_BAR_CANCEL_EVENT, (WPARAM)m_hUserStopEvent, 0);
	m_dwProgressSize = 0;
	return pDBT;
}

BOOL CMkCommand::ExecuteThreadMode(CString strDisplayText)
{
	RemakeDisplayText(strDisplayText);
	//g_bana_log->Print("---Start ExecuteThreadMode(%s)\n", strDisplayText);

	CMkLock lock(GetDatabase()->m_csQuery);
	ResetEvent(m_hRunningThread);
	ResetEvent(m_hUserStopEvent);

	CDisplayBarThread *pDBT = ExecuteDisplay();
	CDisplayBarThreadText display(pDBT, strDisplayText);
	GetDatabase()->RunThread(this);

	DWORD dwTick = GetTickCount();
	HANDLE hWaitObject[2];

	hWaitObject[0] = m_hRunningThread;
	hWaitObject[1] = m_hUserStopEvent;

	while(1)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(2, hWaitObject, FALSE, 50);

		if(dwWaitResult == WAIT_OBJECT_0)
			break;
		
		if(dwWaitResult == WAIT_OBJECT_0 + 1 || GetTickCount() - dwTick > 120 * 1000)
		{
			if(dwWaitResult == WAIT_OBJECT_0 + 1)
				GetDatabase()->SetUserStop();

			GetDatabase()->GetSocket()->Close();
			WaitForSingleObject(m_hRunningThread, 3000);
			m_bThreadRunningResult = FALSE;
			break;
		}

		RedrawProgressBar(pDBT);
	}

	//g_bana_log->Print("---End ExecuteThreadMode(%s)\n", strDisplayText);
	return m_bThreadRunningResult;
}

BOOL CMkCommand::ExecuteThreadModeDual(CMkCommand *pCmd2, CString strDisplayText)
{
	RemakeDisplayText(strDisplayText);

	//g_bana_log->Print("---Start ExecuteThreadMode(%s)\n", strDisplayText);

	CMkLock lock(GetDatabase()->m_csQuery);
	ResetEvent(m_hRunningThread);
	ResetEvent(pCmd2->GetRunningEvent());
	ResetEvent(m_hUserStopEvent);

	CDisplayBarThread *pDBT = ExecuteDisplay();
	CDisplayBarThreadText display(pDBT, strDisplayText);
	GetDatabase()->RunThread(this);
	pCmd2->GetDatabase()->RunThread(pCmd2);

	long nRecvWaitEvent = 0;
	DWORD dwTick = GetTickCount();
	HANDLE hWaitObject[3];
	hWaitObject[0] = m_hRunningThread;
	hWaitObject[1] = pCmd2->GetRunningEvent();
	hWaitObject[2] = m_hUserStopEvent;

	while(1)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(3, hWaitObject, FALSE, 50);

		if(dwWaitResult == WAIT_OBJECT_0)
			nRecvWaitEvent++;
		else if(dwWaitResult == WAIT_OBJECT_0 + 1)
			nRecvWaitEvent++;

		if(nRecvWaitEvent >= 2)
			break;

		if(dwWaitResult == WAIT_OBJECT_0 + 2 || GetTickCount() - dwTick > 120 * 1000)
		{
			GetDatabase()->SetUserStop();
			pCmd2->GetDatabase()->SetUserStop();

			HANDLE hCloseEvent[2];
			hCloseEvent[0] = m_hRunningThread;
			hCloseEvent[1] = pCmd2->GetRunningEvent();

			GetDatabase()->GetSocket()->Close();
			pCmd2->GetDatabase()->GetSocket()->Close();
			WaitForMultipleObjects(2, hCloseEvent, TRUE, 3000);
			m_bThreadRunningResult = FALSE;
			break;
		}

		RedrawProgressBar(pDBT, pCmd2);
	}

	//g_bana_log->Print("---End ExecuteThreadMode(%s)\n", strDisplayText);
	return m_bThreadRunningResult;
}

void CMkCommand::SetThreadRunningResult(BOOL bRet)
{
	m_bThreadRunningResult = bRet;
	if(m_hRunningThread)
		SetEvent(m_hRunningThread);
}

void CMkCommand::RedrawProgressBar(CDisplayBarThread *pBar, CMkCommand *pCmd2)
{
	CString strFormat;
	DWORD dwCurSize = 0, dwTotalSize = 0, dwElapsedTime = 0;
	DWORD dwCurSize2 = 0, dwTotalSize2 = 0, dwElapsedTime2 = 0;

	GetDatabase()->GetProgressInfo(dwCurSize, dwTotalSize, dwElapsedTime);
	if(pCmd2)
		pCmd2->GetDatabase()->GetProgressInfo(dwCurSize2, dwTotalSize2, dwElapsedTime2);

	if(m_dwProgressSize < dwCurSize + dwCurSize2)
	{
		if(dwCurSize + dwCurSize2 == dwTotalSize + dwTotalSize2)
		{
			m_dwProgressSize = dwCurSize + dwCurSize2;
		}
		else
		{
			if(dwCurSize > 0)
				m_dwProgressSize += dwCurSize;

			if(dwCurSize2 > 0)
				m_dwProgressSize += dwCurSize2;

			m_dwProgressSize = min(m_dwProgressSize, dwCurSize + dwCurSize2);
		}

		double dPos = 100.0 * m_dwProgressSize / (dwTotalSize + dwTotalSize2);

		if(dwCurSize + dwCurSize2 > 1024 * 1024)
		{
			double dSpeed;
			if(dwElapsedTime > 0 && dwTotalSize != dwCurSize && dwElapsedTime2 > 0 && dwTotalSize2 != dwCurSize2)
				dSpeed = (dwCurSize / (double)dwElapsedTime + dwCurSize2 / (double)dwElapsedTime2) / 1024.0;
			else if(dwElapsedTime > 0 && dwTotalSize != dwCurSize)
				dSpeed = dwCurSize / (double)dwElapsedTime / 1024.0;
			else if(dwElapsedTime2 > 0  && dwTotalSize2 != dwCurSize2)
				dSpeed = dwCurSize2 / (double)dwElapsedTime2 / 1024.0;
			else 
				dSpeed = 0;

			strFormat.Format("수신중(%0.0f%%) %0.1fMB/sec, %dKB", dPos, dSpeed, (dwCurSize + dwCurSize2) / 1024);
		}
		else
		{
			strFormat.Format("수신중(%0.f%%)", dPos);
		}

		pBar->PostThreadMessage(WM_DISPLAY_BAR_PROGRESS,
			(WPARAM)new CDisplayBarProgressInfo(strFormat, dPos), 
			0);
	}
}

///////////////////////////////////////////////////////////////////////////
//CMkParameter
///////////////////////////////////////////////////////////////////////////

const char szParError[] = "파라메터 타입이 일치하지 않습니다.";
const char szDBError[] = "데이터베이스 오류";


void CMkParameter::InitParameter()
{
	m_pRefValue = NULL;
	m_pParameter = (PARAMETER_STRUCT*)new char[MAX_PARAMETER_LENGTH];
	m_pParameter->lSize = NULL;
}

CMkParameter::CMkParameter(void)
{
	InitParameter();
}

CMkParameter::CMkParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue)
{
	InitParameter();
	SetParameter(nType, nDirection, lSize, pValue);
}

CMkParameter::CMkParameter(int &nValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeLong, nDirection, sizeof(int), (void*)&nValue, bRefOutput);
}

CMkParameter::CMkParameter(UINT &nValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeLong, nDirection, sizeof(UINT), (void*)&nValue, bRefOutput);
}

CMkParameter::CMkParameter(long &nValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeLong, nDirection, sizeof(long), (void*)&nValue, bRefOutput);
}

CMkParameter::CMkParameter(double &dValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeFloat, nDirection, sizeof(double), (void*)&dValue, bRefOutput);
}

CMkParameter::CMkParameter(CString &strValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeString, nDirection, strValue.GetLength(), (LPSTR)(LPCTSTR)strValue, bRefOutput);
}

CMkParameter::CMkParameter(COleDateTime &dtValue, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();
	SetParameter(typeDate, nDirection, sizeof(dtValue), (void*)&dtValue, bRefOutput);
}

CMkParameter::CMkParameter(CString &strValue, long nSize, enum cmkDir nDirection, BOOL bRefOutput)
{
	InitParameter();

	if(bRefOutput)
		m_pRefValue = (void*)&strValue;
	SetParameter(typeString, nDirection, nSize, (LPSTR)(LPCTSTR)strValue, bRefOutput);
}

CMkParameter::~CMkParameter(void)
{
	if(m_pParameter != NULL)
		delete[] m_pParameter;
}

int CMkParameter::SetParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue, BOOL bRefOutput)
{
	if(nDirection >= typeOutput && bRefOutput)
	{
		if(nType != typeString)
			m_pRefValue = pValue;
	}
	else
		m_pRefValue = NULL;

	m_pParameter->nType = nType;
	m_pParameter->nDirection = nDirection;
	m_pParameter->lSize = lSize;
	if(pValue != NULL) {
		if(nType == typeString) {
			memset(m_pParameter->pValue, 0x00, lSize + 1);
			strcpy((char*)m_pParameter->pValue, (char*)pValue);
			m_pParameter->lSize = m_pParameter->lSize + 1;
		}
		else {
			memcpy(m_pParameter->pValue, pValue, lSize);
		}
	}
	else
	{
		memset(m_pParameter->pValue, 0x00, lSize);
	}
	return m_pParameter->lSize;
}

int CMkParameter::SetValue(long lSize, void *pValue)
{
	m_pParameter->lSize = lSize;
	if(pValue != NULL) {
		if(m_pParameter->nType == typeString) {
			memset(m_pParameter->pValue, 0x00, lSize + 1);
			memcpy(m_pParameter->pValue, pValue, lSize);
			m_pParameter->lSize = m_pParameter->lSize + 1;
		}
		else {
			memcpy(m_pParameter->pValue, pValue, lSize);
		}
	}

	if(m_pRefValue)
	{
		if(m_pParameter->nType == typeInt ||
			m_pParameter->nType == typeLong ||
			m_pParameter->nType == typeFloat)
		{
			memcpy(m_pRefValue, m_pParameter->pValue, lSize);
		}
		else if(m_pParameter->nType == typeString)
		{
			((CString*)m_pRefValue)->SetString((const char*)m_pParameter->pValue);
		}
		else if(m_pParameter->nType == typeDate)
		{
			*((COleDateTime*)m_pRefValue) = *((COleDateTime*)m_pParameter->pValue);
		}
	}

	return m_pParameter->lSize;
}

void CMkParameter::SetValue(int nValue)
{
	memcpy(m_pParameter->pValue, &nValue, sizeof(int));
}

BOOL CMkParameter::GetValue(int &nValue)
{
	nValue = *((int*)m_pParameter->pValue);
	return TRUE;
}

BOOL CMkParameter::GetValue(long &lValue)
{
	lValue = *((long*)m_pParameter->pValue);
	return TRUE;
}

BOOL CMkParameter::GetValue(double &dValue)
{
	dValue = *((double*)m_pParameter->pValue);
	return TRUE;
}

BOOL CMkParameter::GetValue(COleDateTime &dtValue)
{
	dtValue = *((COleDateTime*)m_pParameter->pValue);
	return TRUE;
}

BOOL CMkParameter::GetValue(CString &strValue)
{
	strValue = (char*)m_pParameter->pValue;
	return TRUE;
}

int	CMkParameter::GetInt()
{
	return *((int*)m_pParameter->pValue);
}

long CMkParameter::GetLong()
{
	return *((long*)m_pParameter->pValue);
}

COleDateTime CMkParameter::GetDate()
{
	return *((COleDateTime*)m_pParameter->pValue);
}

CString CMkParameter::GetString()
{
	return (char*)m_pParameter->pValue;
}

double CMkParameter::GetFloat()
{
	return *((double*)m_pParameter->pValue);
}








