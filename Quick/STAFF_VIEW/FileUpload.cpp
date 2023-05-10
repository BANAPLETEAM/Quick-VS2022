#include "StdAfx.h"
#include "FileUpload.h"
#include "direct.h"
#include "afxsock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFileUpload::CFileUpload(void)
{
	m_pConnection = NULL;
	m_pFileFind = NULL;

	if(!AfxSocketInit())
	{
		AfxMessageBox("���� �ʱ�ȭ ����", MB_ICONINFORMATION);
	}
}

CFileUpload::~CFileUpload(void)
{
}

void CFileUpload::SetConnectInfo(CString strIP, CString strUrl, CString strUserName, CString strPassword)
{
	if(m_pConnection != NULL)
	{
		m_pConnection->Close();
		delete m_pConnection; 
		m_pConnection = NULL;  
	}
	 
	//m_pConnection = m_session.GetFtpConnection("211.172.242.163", USER_NAME, USER_PASS, 23000, TRUE);
	m_pConnection = m_session.GetFtpConnection("211.172.242.170", USER_NAME, "data@@server230", 23000, TRUE);

	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�,\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return;
	}
	
	m_pConnection->SetCurrentDirectory(strUrl);
	m_pConnection->GetCurrentDirectory(m_strRemote);
	
}

BOOL CFileUpload::UploadFile(CString &strLocalFileName)
{
	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�,\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return FALSE;
	}

/* 
	m_pFileFind = new CFtpFileFind(m_pConnection);
	m_pFileFind->FindFile(m_strRemote);

	CString sFileName = m_pFileFind->GetFileName();
	CString sPath = m_pFileFind->GetFilePath();
*/
	//rand() 


	srand(time(NULL)); 
	long nRand = rand()%10000;  

	CString strLocalName;

	long nIndex = strLocalFileName.ReverseFind('\\');
	COleDateTime dtCur(COleDateTime::GetCurrentTime());
 
	if(nIndex >= 0) 
	{	
		CString strName = strLocalFileName.Right(strLocalFileName.GetLength() - nIndex - 1);
		CString strFirst = strName.Left(strName.GetLength() - 4);
		CString strLast = strName.Right(4);

		strLocalName.Format("%s_%s%d%s", strFirst, dtCur.Format("%y%m%d%H%M%S"), nRand, strLast);
	}
	else
	{
		CString strName = strLocalFileName;
		CString strFirst = strName.Left(strName.GetLength() - 4);
		CString strLast = strName.Right(4);

		strLocalName.Format("%s_%s%d%s", strFirst, dtCur.Format("%y%m%d%H%M%S"), nRand, strLast);
	}

	CString strServerFile = m_strRemote+ "/" + strLocalName ;
	BOOL bRet = m_pConnection->PutFile(strLocalFileName, strServerFile); 

	if(bRet == TRUE)
		strLocalFileName = strLocalName;

	return bRet;
}

BOOL CFileUpload::DeleteFile(long nANo)
{
	char buffer [10];

	if(m_pConnection == NULL)
		AfxMessageBox("���� ���ӿ� ���� �߽��ϴ�", MB_ICONINFORMATION);

	if(m_pFileFind != NULL)
	{
		delete m_pFileFind;
		m_pFileFind = NULL;
	}

	m_pFileFind = new CFtpFileFind(m_pConnection);
	BOOL bFineFile = m_pFileFind->FindFile(m_strRemote);
	CString strANo = itoa(nANo, buffer, 10);
	CString strFileName = "";
	BOOL bFind = FALSE;
	
	m_pFileFind->FindNextFile();
	while(bFineFile)
	{
		strFileName = m_pFileFind->GetFileName();

		if(strFileName.Find(strANo) >=0)
		{
			bFind = TRUE;
			break;		
		}

		bFineFile = m_pFileFind->FindNextFile();
	}

	BOOL bRet = FALSE;

	if(bFind == TRUE)
	{
		CString strServerFile = m_strRemote+ "/" + strFileName;
		bRet = m_pConnection->Remove(strServerFile);
	}
	
	return bRet;
}