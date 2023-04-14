#include "StdAfx.h"
#include "SMSFileUpload.h"
#include "direct.h"
#include "afxsock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




CSMSFileUpload::CSMSFileUpload(void)
{
	m_pConnection = NULL;
	m_pFileFind = NULL;

	if(!AfxSocketInit())
	{
		AfxMessageBox("���� �ʱ�ȭ ����", MB_ICONINFORMATION);
	}
}

CSMSFileUpload::~CSMSFileUpload(void)
{
}

void CSMSFileUpload::SetConnectInfo(CString strIP, CString strUrl, CString strUserName, CString strPassword)
{
	if(m_pConnection != NULL)
	{
		m_pConnection->Close();
		delete m_pConnection; 
		m_pConnection = NULL;  
	}
	 
	m_pConnection = m_session.GetFtpConnection(FTP_IP, m_strID, m_strPass, 23000, TRUE);

	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�,\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return;
	}
	
	m_pConnection->SetCurrentDirectory(strUrl);
	m_pConnection->GetCurrentDirectory(m_strRemote);
	
}


void CSMSFileUpload::SetConnectInfoSMS(CString strUrl)
{
	if(m_pConnection != NULL)
	{
		m_pConnection->Close();
		delete m_pConnection; 
		m_pConnection = NULL;  
	}

	m_pConnection = m_session.GetFtpConnection("210.127.244.199", m_strID, m_strPass, 21000, TRUE);

	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�,\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return;
	}

	m_pConnection->SetCurrentDirectory(strUrl);
	m_pConnection->GetCurrentDirectory(m_strRemote);

}


BOOL CSMSFileUpload::SMSCallBackFileDelete(CString strDirectory ,CString strFileName)
{

	BOOL bRet = FALSE;


	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�.\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return FALSE;
	}

	if( m_pConnection->SetCurrentDirectory(strDirectory) )
	{



		bRet = m_pConnection->Remove(strFileName);
		if(! bRet ) // ������
		{	
			//m_pConnection->GetFile(strFileName);
			AfxMessageBox("�̹� ���������ϴ�");
			bRet = TRUE;
		}
	}	

	return bRet;

}

BOOL CSMSFileUpload::UploadSMSCallBackFile(CString strLocalFileName, CString &strFileName, CString strOldFileName)
{
	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�.\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return FALSE;
	}
	CString strLocalName;
	CString strExt = "";
	COleDateTime dtCur(COleDateTime::GetCurrentTime());

	strExt = strLocalFileName.Right(3);
	strExt.MakeLower();

	if(strExt == "com" || strExt == "exe" || strExt == "bat" 
		|| strExt == "sys" || strExt == "ocx" ||strExt == "dll" 
		|| strExt == "jar" 
 		)
	{
		AfxMessageBox("�ý��� ������ ���ε带 �ϽǼ� �����ϴ�.\r\n�ٽýõ��ϼ���", MB_ICONINFORMATION);
		return FALSE;
	}


	long nIndex = strLocalFileName.ReverseFind('\\');

	BOOL bRet = TRUE;
	if(strOldFileName.GetLength() > 0)
	{
		bRet = m_pConnection->Remove(strOldFileName); 	
	}
	if(bRet)
		bRet = m_pConnection->PutFile(strLocalFileName, strFileName); 	

	return bRet;

}

BOOL CSMSFileUpload::UploadFile(CString &strLocalFileName, CString strNameString)
{
	if(m_pConnection == NULL)
	{
		AfxMessageBox("���ε� ������ �������� ���߽��ϴ�.\r\n�ٽ� �õ��� �ּ���", MB_ICONINFORMATION);
		return FALSE;
	}

	CString strFileName = strLocalFileName; 
	strFileName.MakeLower();

	if(strFileName.Right(3) == "com" || strFileName.Right(3) == "exe" || strFileName.Right(3) == "bat" 
		|| strFileName.Right(3) == "sys" || strFileName.Right(3) == "ocx" || strFileName.Right(3) == "dll" 
		|| strFileName.Right(3) == "jar" 
		)
	{
		AfxMessageBox("�ý��� ������ ���ε带 �ϽǼ� �����ϴ�.\r\n�ٽýõ��ϼ���", MB_ICONINFORMATION);
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

		if(!strNameString.IsEmpty())
			strFirst = strNameString;

		strLocalName.Format("%s_%s%d%s", strFirst, dtCur.Format("%y%m%d%H%M%S"), nRand, strLast);
	}
	else
	{
		CString strName = strLocalFileName;
		CString strFirst = strName.Left(strName.GetLength() - 4);
		CString strLast = strName.Right(4);

		if(!strNameString.IsEmpty())
			strFirst = strNameString;

		strLocalName.Format("%s_%s%d%s", strFirst, dtCur.Format("%y%m%d%H%M%S"), nRand, strLast);
	}

	CString strServerFile = m_strRemote+ "/" + strLocalName ;
	BOOL bRet = m_pConnection->PutFile(strLocalFileName, strServerFile); 

	if(bRet == TRUE)
		strLocalFileName = strLocalName;

	return bRet;
}

BOOL CSMSFileUpload::DeleteFile(long nANo)
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