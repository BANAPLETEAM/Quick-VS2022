
#include "StdAfx.h"
#include "MyCall.h"
#include "resource.h"
#include "RcpPageCtiForm.h"
#include "MyCallMessage.h"
#include "TelserverDIDRouteDlg.h"

#ifdef _SYSMANAGER
KEY_PHONE_ID_MAP CMyCall::m_mapOPLineMapping;
#endif


CMyCall::CMyCall(void) 
: CCall()
{
	m_pDIDRouteDlg = NULL;
}

CMyCall::~CMyCall(void)
{

}

void CMyCall::onCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID)
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return;

	CMyCallMessage msg(m_pDlg);
	msg.CallChange(nType, (char*)szPhoneNumber, (char*)szKeyPhoneID, (char*)szDID);

	//sText.Format("%s,PHONE=%s,ID= %s,DID = %s ",nType==PH_RING ? "RING" : nType == PH_ANSWER ? "ANSWER" : "HANG UP",szPhoneNumber,szKeyPhoneID,szDID);
	//m_pDlg->SetPhoneState(sText);
}

void CMyCall::onCallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
							char* szOperator,char* szCustomer,char* szLastOperator)
{
	/*
	GetLog()->Print("CALL_EVENT: nType:%d, szPhoneNumber:%s szKeyPhoneID:%s, szDID:%s, szOperator:%s, szCustomer:%s, szLastOperator:%s\n",
	nType, szPhoneNumber, szKeyPhoneID, szDID, szOperator, szCustomer, szLastOperator);
	*/

	CallInfoLog(nType, szPhoneNumber, szKeyPhoneID, szDID, szOperator, szCustomer, szLastOperator);
}



void CMyCall::CallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
						  char* szOperator,char* szCustomer,char* szLastOperator,
						  COleDateTime dtCur, BOOL bRedraw)
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return;

	if(!m_pDlg) return;

	if(nType == PH_ANSWER && strstr(szOperator, "ARS-") > 0)
		nType = PH_ARS_ANSWER;


	CString strOperator = szOperator;

#ifdef _SYSMANAGER
	if(strOperator.GetLength() <= 2 || strOperator == "관리자")
	{
		CString strOp = FindOpLineMapping(szKeyPhoneID);
		if(!strOp.IsEmpty())
			strOperator = strOp;
	}
#endif

	CMyCallMessage msg(m_pDlg);
	msg.SetCallList(nType, (char*)szPhoneNumber, (char*)szKeyPhoneID, (char*)szDID, (LPSTR)(LPCTSTR)strOperator, (char*)szCustomer, dtCur, bRedraw);
}

void CMyCall::onMoniter( int nRing,int nAnswer,int nMissingCallCnt ,int nMissingCallPerMin)
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return;

	if(m_pDlg && m_pDlg->m_stcRingInfo.GetSafeHwnd())
	{
		m_pDlg->DisplayRingInfo(nRing, nAnswer, nMissingCallCnt, nMissingCallPerMin);
	}
}

void CMyCall::onConnected()
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return;

	if(!m_pDlg) return;
	m_pDlg->SocketConnected(); 
}
void CMyCall::onDisConnected()
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return; 

	if(!m_pDlg || !m_pDlg->GetSafeHwnd()) return;
	m_pDlg->SocketDisConnected();
}


void CMyCall::onMoniterLog(const char* szLog)
{
	if(!IsValidState())
		return;

	if(IsOnlyRecvCustomerInfo())
		return;

	/*
	if(UI()->bDeveloper)
	GetLog()->Print("%s", szLog);
	*/
}

void CMyCall::onMoniterUserLog(const char* szLog)
{
	if(!IsValidState())
		return;
}

void CMyCall::onSocketState(const char* szLog)
{
	if(!IsValidState())
		return;
}

void CMyCall::onMoniterAnswerLinesChanged(const char* szKeyPhoneLines)
{
	if(!IsValidState())
		return;
}

void CMyCall::onError(int nCode,CString strError)
{
	if(!IsValidState())
		return;

	m_pDlg->m_bConnected = FALSE;
	m_pDlg->RefreshState(strError);
}

void CMyCall::onCustomerInfo(const char* szPhoneNumber,const char* strCName, const char* sDesc)
{
	if(!IsValidState())
		return;

	if(!IsOnlyRecvCustomerInfo())
		return;

	CMyCallMessage msg(m_pDlg);
	msg.CustomerInfo((char*)szPhoneNumber, (char*)strCName, (char*)sDesc);
}

void CMyCall::onRecordFileNameInsertID(CString strKeyPhoneID, CString strPhoneNumber, int nInsertID)
{
	if(!IsValidState())
		return;

	if(m_pDlg)
	{
		m_pDlg->AddRecordFileNameInsertID(strKeyPhoneID, strPhoneNumber, nInsertID);
	}
}

void CMyCall::onDIDRouteChange(int nSubType, const char* szDID, const char* szToLine, int nUseType, const char* szDesc)
{
	if(m_pDIDRouteDlg)
	{
		if(nSubType == 0)
			m_pDIDRouteDlg->SuccessDIDRouteAdd(szDID, szToLine, nUseType, szDesc);
		else if(nSubType == 1)
			m_pDIDRouteDlg->SuccessDIDRouteDelete(szDID);
		else if(nSubType == 2)
			m_pDIDRouteDlg->SuccessDIDRouteAllUse();
		else if(nSubType == 3)
			m_pDIDRouteDlg->SuccessDIDRouteAllUnuse();
	}
}

void CMyCall::SetQueuePause(int nPause)/*0 수신가능, 1 수신거부, 2 인터넷전화아님*/
{
	if(!IsValidState())
		return;

	m_nQueuePause = nPause;

	CMyCallMessage msg(m_pDlg);
	msg.RefreshQueueState();
}

int CMyCall::GetQueuePause()
{
	if(!IsValidState())
		return LINE_UNUSE_MODE;

	return m_nQueuePause;
}

BOOL CMyCall::IsValidState()
{
	if(m_pDlg && m_pDlg->GetSafeHwnd())
		return TRUE;
	return FALSE;
}


#ifdef _SYSMANAGER
void CMyCall::MakeOpLineMapping()
{
	CMkRecordset rs(m_pMkSysmanager);
	CMkCommand cmd(m_pMkSysmanager, "select_logi_keyphoneid_list");	
	cmd.AddParameter(0);					
	if(rs.Execute(&cmd))
	{		
		CString strKeyPhoneID, strName;
		for(int i = 0; i < rs.GetRecordCount(); i++)
		{
			rs.GetFieldValue("sKeyPhoneID", strKeyPhoneID);
			rs.GetFieldValue("sName", strName);

			m_mapOPLineMapping.insert(KEY_PHONE_ID_MAP::value_type(atol(strKeyPhoneID), strName));

			//int nKeyPhoneID = atol(strKeyPhoneID);
			//if(nKeyPhoneID >= 3900 && nKeyPhoneID < 4000)
			//	strcpy(m_szOpLine[nKeyPhoneID - 3900], (LPSTR)(LPCTSTR)strName);

			rs.MoveNext();
		}
	}
}

CString CMyCall::FindOpLineMapping(CString strLine)
{
	//	int nKeyPhoneID = atol(strLine);
	//	if(nKeyPhoneID >= 3900 && nKeyPhoneID < 4000)
	//		return m_szOpLine[nKeyPhoneID - 3900];
	//
	//	return "";

	KEY_PHONE_ID_MAP::iterator it;
	it = m_mapOPLineMapping.find(atol(strLine));
	if(it != m_mapOPLineMapping.end())
		return it->second;

	return "";
}
#endif