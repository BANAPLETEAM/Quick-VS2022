
#include "stdafx.h"
#include "resource.h"
#include "ExceptionHandler.h"

#ifndef _DEBUG

#include "CrashDlg.h"
#include "MyFormView.h"
#include "MyDialog.h"
#include "LogiUtil.h"
#include "POIDataNew.h"

LONG WINAPI TheCrashHandlerFunction(EXCEPTION_POINTERS * pExPtrs)
{
	pExPtrs = pExPtrs;

	CCrashDlg Dlg;
	Dlg.SetExceptionPointers(pExPtrs);

	LONG lReturnVal = EXCEPTION_EXECUTE_HANDLER;
	INT_PTR iRet = Dlg.DoModal();

	if(IDOK == iRet)
	{
		lReturnVal = EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		lReturnVal = EXCEPTION_CONTINUE_SEARCH;
	}

	return (lReturnVal);
}


LONG WINAPI TheCrashHandlerNormalFunction(EXCEPTION_POINTERS * pExPtrs)
{
	encProfile.WriteInt("Shutdown", m_ui.strID + "_runtime_error", 1);

	char szPathName[_MAX_PATH], szFileName[_MAX_PATH], szCurTime[100];
	char szLocalPath[_MAX_PATH];
	SYSTEMTIME st;
	CString strFaultReason, strTemp, strVersion, strErrorLogName;
	BOOL bDumpOK = FALSE;

	g_bana_log->Print("exception handler\n");

	LPCTSTR szStr = GetFaultReason(pExPtrs);
	strTemp.Format("%S\r\n", szStr);
	strFaultReason += strTemp;

	szStr = GetRegisterString(pExPtrs);
	strTemp.Format("%S\r\n", szStr);
	strFaultReason += strTemp;

	szStr = GetFirstStackTraceString(GSTSO_MODULE |
		GSTSO_SYMBOL |
		GSTSO_SRCLINE,
		pExPtrs);

	while(NULL != szStr)
	{
		strTemp.Format("%S\r\n", szStr);
		strFaultReason += strTemp;

		szStr = GetNextStackTraceString(GSTSO_MODULE |
			GSTSO_SYMBOL |
			GSTSO_SRCLINE,
			pExPtrs);
	}


	strcpy(szPathName, (LPSTR)(LPCTSTR)LF->GetModuleFullPath());

	strcpy(szLocalPath, szPathName);
	strcat(szLocalPath, "\\error.log");

	WriteErrorLogFile(strFaultReason, szLocalPath);

	GetLocalTime(&st);
	sprintf(szCurTime, "%d%02d%02d_%02d%02d%02d_%d", st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	TCHAR szFullPath[MAX_PATH];
	if(GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		VS_FIXEDFILEINFO pvsf;

		if(LF->GetFileVersion(szFullPath, &pvsf))
		{
			strVersion.Format("%d%d%d", HIWORD(pvsf.dwFileVersionMS),
				LOWORD(pvsf.dwFileVersionMS),
				HIWORD(pvsf.dwFileVersionLS));
			strFaultReason += "PRGRAM_VERSION = " + strVersion + "\r\n";
		}
	}

	strErrorLogName = strVersion + "_" + szCurTime + ".txt";
	encProfile.WriteString("Debug", "FileName", strErrorLogName);


	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	strTemp.Format("ERROR_TIME = %s\r\n", dtCur.Format("%Y-%m-%d %H:%M:%S"));
	strFaultReason += strTemp;

	strTemp.Format("COMPANY_CODE = %d\r\n", m_ui.nCompany);
	strFaultReason += strTemp;

	strTemp.Format("USER_ID = %s\r\n\r\n\r\n", m_ui.strID);
	strFaultReason += strTemp;

	WriteErrorLogFile(strFaultReason, szLocalPath);


	if(m_pMkDb)
	{
		strFaultReason += "LAST_QUERY: " + m_pMkDb->GetLastQueryInfo() + "\r\n\r\n";

		if(m_pMkDb->GetEnteringCmd())
			strFaultReason += "LAST_ENTERING_CMD: " + m_pMkDb->GetEnteringCmd()->GetQueryDebugInfo() + "\r\n\r\n";
	}

	strFaultReason += "LAST_MYFORMVIEW:\r\n" + CMyFormView::m_strLastFormView + "\r\n\r\n";
	strFaultReason += "LAST_MYDIALOG:\r\n" + CMyDialog::m_strLastDialog + "\r\n\r\n";

	WriteErrorLogFile(strFaultReason, szLocalPath);


	if(LU)
	{
		CString strRunning;
		strRunning.Format("Program start Elapsed time: %d분\r\n\r\n", (GetTickCount() - m_ei.dwProgramStartTick) / 1000 / 60);
		strFaultReason += strRunning;
		strFaultReason += "Special LOG:\r\n" + LU->GetSpecialLog() + "\r\n\r\n";
	}

	strFaultReason += "POI LOG:\r\n" + m_poiNew.GetSpecialLog() + "\r\n\r\n";

	strcpy(szFileName, szPathName);
	strcat(szFileName, "\\");
	strcat(szFileName, (LPSTR)(LPCTSTR)strVersion);
	strcat(szFileName, "_");
	strcat(szFileName, szCurTime);

	if(strFaultReason.Find("프로그램종료중") > 0)
	{
		strcat(szFileName, "_exit");
		strErrorLogName.Replace(".txt", "_exit.txt");
		encProfile.WriteString("Debug", "FileName", strErrorLogName);	
	}

	strcat(szFileName, ".txt");

	WriteErrorLogFile(strFaultReason, szLocalPath);

	if(TRUE == IsMiniDumpFunctionAvailable())
	{
		strcpy(szFileName, szPathName);
		strcat(szFileName, "\\");
		strcat(szFileName, (LPSTR)(LPCTSTR)strVersion);
		strcat(szFileName, "_");
		strcat(szFileName, szCurTime);
		strcat(szFileName, ".DMP");

		BSUMDRET eRet = CreateCurrentProcessCrashDumpA(MiniDumpWithHandleData ,
		szFileName,
		GetCurrentThreadId(),
		pExPtrs);

		if(eDUMP_SUCCEEDED == eRet)
		{
			bDumpOK = TRUE;
		}
	}

	if(UploadExceptionErrorData(strFaultReason, bDumpOK, szPathName, szFileName, strVersion))
		DeleteFile(szLocalPath);

	return ( EXCEPTION_EXECUTE_HANDLER ) ;
}

#endif


#define PST_START_UPDATE_UPLOAD 6039


BOOL UploadExceptionErrorData(CString strFaultReason, BOOL bDumpOK, CString strDumpPath, CString strDumpFileName,
							  CString strVersion)
{
#ifdef _LOGIDB2012
	return FALSE;
#endif

	CMkDatabase *pMkDb = new CMkDatabase(g_bana_log);
	CMkDatabase *pMkDb2 = new CMkDatabase(g_bana_log);
	CString strAddr = "211.172.242.178";

	try {
		CString strServerPath, strBackup, strUpdateFiles, strUpdateSystem;
		CString strFileName = strDumpFileName;

		{
			BYTE nXorKey = (pMkDb->GetXorKey() + 3) % 128;
			BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
			BYTE nXoredKey[8];

			for(int i = 0; i < 8; i++)
				nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
			pMkDb->SetServerKey(nXoredKey); 
			pMkDb->SetErrorMsgType(2);
		}

		strFileName.Replace(strDumpPath + CString("\\"), "");

		if(!pMkDb->Open(m_si.strRealMainServerAddr, 3500)) throw "서버에 접속할 수 없습니다.";


		CMkCommand pCmd(pMkDb, "insert_debug_report_2010");
		pCmd.AddParameter(strVersion);
		pCmd.AddParameter(m_ui.strID);
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(strFaultReason.Left(3000));
		pCmd.AddParameter(bDumpOK ? strFileName : "");
		if(!pCmd.Execute())
			throw "insert_dump_data중에 오류 발생";

		pMkDb->Close();


		{
			BYTE nXorKey = (pMkDb2->GetXorKey() + 3) % 128;
			BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
			BYTE nXoredKey[8];

			for(int i = 0; i < 8; i++)
				nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
			pMkDb2->SetServerKey(nXoredKey); 
			pMkDb2->SetErrorMsgType(2);
		}


		if(!pMkDb2->Open(strAddr, 3610)) throw "서버에 접속할 수 없습니다.";


		CMkRecordset pRs(pMkDb2);
		UINT nType = PT_OK, nSubType = PST_START_UPDATE_UPLOAD, nSize = 0;
		if(!pRs.ExecuteRecordsetOnly(nType, nSubType, nSize, ""))
			throw "통신중에 오류가 발생했습니다.";

		pRs.GetFieldValue(0, strServerPath);
		pRs.GetFieldValue(1, strBackup);
		pRs.GetFieldValue(2, strUpdateFiles);
		pRs.GetFieldValue(3, strUpdateSystem);
		pRs.Close();


		CString strServerFileName;
		strServerFileName = strServerPath + "\\" + strBackup + "\\SmartQ\\" + strFileName;

		if(!LF->SendUpdateFile(*pMkDb2, strDumpFileName, strServerFileName))
			throw "파일 업로드중에 에러발생";
		strServerFileName.Replace(".DMP", ".txt");

		if(!pMkDb2->UploadFile(strServerFileName, strFaultReason.GetBuffer(), strFaultReason.GetLength()))
			throw "파일 업로드중에 에러발생";

		pMkDb2->Close();
	}
	catch(char *szMsg)
	{
		g_bana_log->Print("UploadExceptionErrorData: %s\n", szMsg);
		delete pMkDb;
		delete pMkDb2;
		return FALSE;
	}

	delete pMkDb;
	delete pMkDb2;

	return TRUE;
}


void WriteErrorLogFile(CString &strErrorLog, CString strPath)
{
	DWORD dwDriveList;

	HANDLE hFile = CreateFile(strPath, 
		GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != (HANDLE)hFile) 
	{
		WriteFile((void*)hFile, 
			strErrorLog.GetBuffer(), 
			strErrorLog.GetLength(), 
			&dwDriveList, 
			NULL);

		CloseHandle(hFile);
	}
}