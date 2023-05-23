// KingoHttp.cpp: implementation of the CKingoHttp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KingoHttp.h"
#include <afxinet.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKingoHttp::CKingoHttp()
{
	Init();
}

CKingoHttp::~CKingoHttp()
{

}

void CKingoHttp::Init()
{
	m_byteRespone.SetByte(NULL,0);
	m_sUserName		= "";
	m_sUserPassWord = "";
	m_sError = "";
	m_dwError= 0;
	m_sServer="";
	m_uPort  =80;
	m_nVerb  =0;
	m_sUrl   ="";
	m_sParamData="";

	m_bSSL = FALSE;
}

void CKingoHttp::SetConnectInfo(CString sServer, UINT uPort,CString sUrl, int nVerb,CString sUserName,CString sUserPassWord)
{
	m_sServer=sServer;
	m_uPort  =uPort;
	m_sUrl	 =sUrl;
	m_nVerb  =nVerb;
	m_sUserName = sUserName;
	m_sUserPassWord = sUserPassWord;

}

BOOL CKingoHttp::AddParamValue(CString sName, CString sValue)
{
	if(sName == "")
	{
		SetError("Name should not be empty",-1);
		return FALSE;
	}
	if(m_sParamData != "")	m_sParamData += "&";
	m_sParamData				= m_sParamData + sName + "=" + ((sValue.GetLength() < 1000 ) ? LF->EnCodeStr(sValue) : sValue);
	return TRUE;
}




int CKingoHttp::Call()
{
	CHttpConnection* pHttpConnection = NULL;
	CInternetSession session;	
	CHttpFile* pFile  = NULL;	

	DWORD HttpRequestFlags;
	int nRet = 0;
	BOOL bFirst = TRUE;
	do
	{
		try
		{
			HttpRequestFlags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;
			if  (m_bSSL)
			{
				HttpRequestFlags |= INTERNET_FLAG_SECURE;
			}

			if(pHttpConnection == NULL)
			{
				pHttpConnection = session.GetHttpConnection(m_sServer,m_uPort,m_sUserName,m_sUserPassWord);
				bFirst = TRUE;
			}
			else bFirst = FALSE;

			BOOL result1;

			CString sAddHeaders = "Accept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, ";
			sAddHeaders += "image/pjpeg, application/x-ms-xbap, application/x-shockwave-flash, application/vnd.ms-excel, ";
			sAddHeaders += "application/vnd.ms-powerpoint, application/msword, */*\r\n";
			sAddHeaders += "Accept-Language: ko-KR\r\n";
			sAddHeaders += "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; ";
			sAddHeaders += ".NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2)";

			if(CHttpConnection::HTTP_VERB_POST != m_nVerb )
			{
				pFile = pHttpConnection->OpenRequest(m_nVerb,m_sUrl + (m_sParamData.IsEmpty() ? "" : "?") + m_sParamData, NULL, 1, NULL, (LPCTSTR)"1.1", HttpRequestFlags);
				pFile->AddRequestHeaders(sAddHeaders);
				result1 = pFile->SendRequest();
			}
			else
			{
				CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
				pFile   = pHttpConnection->OpenRequest(m_nVerb,m_sUrl , NULL, 1, NULL, (LPCTSTR)"1.1", HttpRequestFlags);
				pFile->AddRequestHeaders(sAddHeaders);
				result1 = pFile->SendRequest(strHeaders,(LPVOID)(LPCTSTR)m_sParamData, m_sParamData.GetLength());
			}

			DWORD dwStatusCode;
			BOOL result2 = pFile->QueryInfoStatusCode( dwStatusCode ) ;
			if(result2 == FALSE)
			{
				LPVOID lpMsgBuf;
				FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL 
				);

				SetError((LPCTSTR)lpMsgBuf,-1);
				// Free the buffer.
				LocalFree( lpMsgBuf );
				nRet = -1;
				break;
			}

			if(dwStatusCode >= 300 || dwStatusCode < 200)
			{
				char buffer[10];
				CString sEMsg;
				sEMsg = CString("Error during connect to \r\n") + 
					CString("http://") + m_sServer + CString(":") + ltoa(m_uPort, buffer, 10) + CString("/") + m_sUrl /*+ CString("?") + m_sParamData*/ ;

				SetError(sEMsg,dwStatusCode);
				nRet = -1;
				break;
			}

			int lread=50000;
			BYTE c[50000];
			while(lread>0)
			{
				lread = pFile->Read(c,50000);
				m_byteRespone = m_byteRespone + CByte(c,lread);
			}
			c[0] = 0;
			m_byteRespone = m_byteRespone + CByte(c,1);

			nRet = 0;
		}
		catch(CInternetException* pEx)
		{
			TCHAR   szCause[2048];
			pEx->GetErrorMessage(szCause, 2048);

			SetError(CString(szCause),-1);
			nRet = -1;
			break;
		}
	}while(0);


	if(pFile) pFile->Close();
	if(pHttpConnection) pHttpConnection->Close();
	delete pFile;
	delete pHttpConnection;

	return nRet;
}

void CKingoHttp::SetError(CString sError, DWORD dwError)
{
	if(sError != "")
	{
		if(m_sError != "") return;
	}
	m_sError  = sError;
	m_dwError = dwError;
}

CString CKingoHttp::GetError()
{
	return m_sError;
}

CString CKingoHttp::GetError(DWORD& dwError)
{
	dwError = m_dwError;
	return m_sError;
}

const char* CKingoHttp::GetError(DWORD* dwError)
{
	*dwError = m_dwError;
	return (const char*)(LPCSTR)m_sError;
}

BOOL CKingoHttp::GetResponse(CString &strRet)
{
	if( FALSE == GetError().IsEmpty() ) return FALSE;
	strRet = CString( (unsigned char*)m_byteRespone.GetByte() );
	
	return TRUE;
}

const char* CKingoHttp::GetResponse()
{
	if( FALSE == GetError().IsEmpty() ) return NULL;
	return  (const char*)(unsigned char*)m_byteRespone.GetByte();
}


BOOL CKingoHttp::GetResponse(BYTE **byteRet, int &nLen)
{
	if( FALSE == GetError().IsEmpty() ) return FALSE;
	*byteRet = m_byteRespone.GetByte();
	nLen    = m_byteRespone.GetLength() -1;
	return TRUE;
}


BOOL CKingoHttp::GetResponse(BYTE **byteRet, int *nLen)
{
	if( FALSE == GetError().IsEmpty() ) return FALSE;

	*byteRet = m_byteRespone.GetByte();
	*nLen    = m_byteRespone.GetLength() - 1;
	return FALSE;
}


CString CKingoHttp::utf8_cp949(char* utf8)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	LPWSTR wStr = new WCHAR[size];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wStr, size);

	USES_CONVERSION;
	CString str = "";

	if(size < 400000)
		str = W2CT(wStr);

	delete[] wStr;
	return str;

	/*
	//utf8->unicode
	int nWLen = strlen(utf8) + 1;
	WCHAR *pwChar = new WCHAR[nWLen];
	ZeroMemory(pwChar, nWLen);

	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, pwChar, nWLen); 

	//unicode->cp949
	int nLen = nWLen * 2;
	char *pChar = new CHAR[nLen];
	ZeroMemory(pChar, nLen);

	WideCharToMultiByte(CP_ACP, 0, pwChar, -1, pChar, nLen, NULL, NULL); 

	CString strReturn(pChar);
	
	delete pwChar;
	delete pChar;

	return strReturn;
	*/
}

CString CKingoHttp::ansi_utf8(char* ansi)
{

	WCHAR uniCode[100000];
	memset(uniCode,0,sizeof(uniCode));

	MultiByteToWideChar(CP_ACP, 0, ansi, -1, uniCode, sizeof(uniCode));


	char utf8[100000] = {0,};
	WideCharToMultiByte(CP_UTF8, 0, uniCode, -1, utf8, sizeof(utf8), NULL, NULL); 

	return utf8;

}