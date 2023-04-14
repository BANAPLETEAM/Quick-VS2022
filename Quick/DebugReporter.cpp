
#include "stdafx.h"
#include "DebugReporter.h"



CDebugReporter::CDebugReporter(CMkDatabase *pMkDb, CString strID, int nCompany)
{
	m_pDb = pMkDb;
	m_strID = strID;
	m_nCompany = nCompany;
}

CDebugReporter::~CDebugReporter(void)
{
}


BOOL CDebugReporter::FindDebugFileText(CString &strText)
{
	CString strName = GetMyFileName();
	strName.Replace(".EXE", ".RPT");
	strName.Replace(".exe", ".rpt");

	HANDLE hFile = CreateFile(strName, 
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,         
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if(hFile == INVALID_HANDLE_VALUE) 
		return FALSE;

	DWORD dwFile = GetFileSize(hFile, NULL);
	DWORD dwRead = 0;
	char *pBuffer = new CHAR[dwFile + 1];

	if(ReadFile(hFile, pBuffer, dwFile, &dwRead, NULL))
		strText = pBuffer;

	delete pBuffer;

	CloseHandle(hFile);
	DeleteFile(strName);
	return TRUE;
}



void CDebugReporter::Report()
{
	CString strText, strResult;

	if(FindDebugFileText(strText))
	{
		strResult = strText.Left(3000);
        
		CMkCommand pCmd(m_pDb, "insert_debug_report");
		pCmd.AddParameter(typeString, typeInput, m_strID.GetLength(), m_strID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(m_nCompany), m_nCompany);
		pCmd.AddParameter(typeString, typeInput, strResult.GetLength(), strResult);
		pCmd.Execute();
	}
}





