#include "StdAfx.h"
#include "resource.h"
#include "DaumHttpParser.h"
#include "MkLock.h"
#include "SearchPOIDlg.h"
#include "SimpleMapDlg.h"
#include "LogiMapNew.h"
#include "POIDataNew.h"
#include "JibunData.h"
#include "libjson.h"
//#include "CrashHandler.h"
#include <wininet.h>
#include "afxinet.h"
#include "json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//키 추가시 배열에 넣고 키 카운트만 올리세요.


CDaumHttpParser::CDaumHttpParser(void)
{
	m_strKakaoKey = "";	
	m_bLoadKakaoKey = FALSE;
}

CDaumHttpParser::~CDaumHttpParser(void)
{
	
}

void CDaumHttpParser::GetKakaoKey()
{
	CMkCommand cmd(m_pMkDb, "select_kakao_key");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	CMkParameter *pParKey = cmd.AddParameter(typeString, typeOutput, 100, "");

	if(!cmd.Execute())
		return;

	pParKey->GetValue(m_strKakaoKey);
	
}

void CDaumHttpParser::Refresh2(QUERY_INFO &QI)
{
	{
		CMkLock lock(&m_cs);
		m_QueryInfo.strKeyword.Empty();
	}

	if(m_bLoadKakaoKey == FALSE)
	{
		GetKakaoKey();
		m_bLoadKakaoKey = TRUE;
	}

	if(m_strKakaoKey.IsEmpty())
		return;

	CString strKeyword = QI.bPhoneSearch ? LF->GetDashPhoneNumber(QI.strKeyword) : QI.strKeyword;

	CString strHtml = OpenKakaoLocation(m_strKakaoKey, strKeyword);
	//CString strHtml = OpenKakaoLocation(m_strDaumKey, m_QueryInfo.strKeyword);

	int nLength = strHtml.GetLength();
	int nCount = 0;
	QI.nApiType = DAUM;

	if(QI.nDebugPrintType & DEBUG_PRINT_BODY)
	{
		while(nLength >= nCount)
		{
			nCount += 1000; 
		}
	}

	vector<SEARCH_RESULT_INFO> vec;
	ParseJSON4NaverLocalValues(strHtml, &vec);
	Analyze2(QI, vec);
}

void CDaumHttpParser::ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec)
{
	if(strHtml.IsEmpty())
		return;

	Json::Value root;
	Json::Reader reader;

	std::string str(strHtml);


	BOOL bRet = reader.parse(str, root);

	if(bRet == FALSE)
		return;

	Json::Value jsonDocuments = root["documents"];

	if(!jsonDocuments)
		return;

	for(int i=0; i<jsonDocuments.size(); i++)
	{
		SEARCH_RESULT_INFO st;

		st.name_val = jsonDocuments[i]["place_name"] ? jsonDocuments[i]["place_name"].asCString() : "";
		st.tel_val = jsonDocuments[i]["phone"] ? jsonDocuments[i]["phone"].asCString() : "";
		st.address_val = jsonDocuments[i]["address_name"] ? jsonDocuments[i]["address_name"].asCString() : "";
		st.x_val = jsonDocuments[i]["x"] ? jsonDocuments[i]["x"].asCString() : "";
		st.y_val = jsonDocuments[i]["y"] ? jsonDocuments[i]["y"].asCString() : "";

		vec->push_back(st);
	}		
}



CString CDaumHttpParser::OpenKakaoLocation(CString strKey, CString strSearch)
{		
	CString strUrl = "https://dapi.kakao.com/v2/local/search/keyword.json?"; 
	strUrl += "y=" + LF->GetStringFromLong(m_ci.m_bound.nPosY / 1000000) + "." + LF->GetStringFromLong(m_ci.m_bound.nPosY % 1000000);
	strUrl += "&x=" + LF->GetStringFromLong(m_ci.m_bound.nPosX / 1000000) + "." + LF->GetStringFromLong(m_ci.m_bound.nPosX % 1000000);
	strUrl += "&query=" + LF->ConvertStringToSendData(strSearch);

	//CString strUrl = "https://dapi.kakao.com/v2/local/search/keyword.json?y=37.514322572335935&x=127.06283102249932&query=naver";


	HINTERNET hOpen = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hReq = NULL;
	INTERNET_PORT dwPort;
	DWORD  dwFlags = INTERNET_FLAG_RELOAD | 
					 INTERNET_FLAG_NO_CACHE_WRITE |
					 INTERNET_FLAG_KEEP_CONNECTION;
	DWORD dwError;
	DWORD  dwSize, dwCode;
	TCHAR szAccept[] = "*/*";
	LPSTR AcceptTypes[2]={0}; 
	AcceptTypes[0]=szAccept;	
	CString strServerName;
	CString strObject;
	DWORD dwServiceType;
	CString strJson = "";
	CString strSecret = "";
	//CString strPostData
	
	if (!AfxParseURL((LPCTSTR)strUrl, dwServiceType, strServerName, strObject, dwPort) )
	{
		printf ("Error: can only use URLs beginning with http:// or https://");
		return "";
	}
    
	// Initialize wininet.
	if (!(hOpen = InternetOpen (NULL,							// app name
							 INTERNET_OPEN_TYPE_PRECONFIG,	// access type
							 NULL,							// proxy server
							 INTERNET_INVALID_PORT_NUMBER,	// proxy port
							 0								// flags
							)))
	{
		printf ("InternetOpen Failed '%d'\n", GetLastError());
		goto done;
	}

    dwFlags |= INTERNET_FLAG_SECURE | 
               INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
               INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  ;

	if ( !(hConnect = InternetConnect ( hOpen, strServerName , dwPort, "",  "", INTERNET_SERVICE_HTTP, 0  , 0) ) )
	{
		printf ("InternetConnect %s", GetLastError());
		return "";
	}

	if ( !(hReq = HttpOpenRequest (hConnect, "GET", strObject, HTTP_VERSION, "", 
									(LPCTSTR*) AcceptTypes, dwFlags ,0 )))

	{
		printf ("HttpOpenRequest %d", GetLastError());
		return "";
	}

	char szPostData[2048] = {0};

	char szHeader[2048] = {0};
	//lstrcpy(szHeader, "Content-Type: application/json;charset=utf-8\r\n");
	lstrcat(szHeader, "Authorization: KakaoAK " + strKey + "\r\n");

		
	DWORD dwFlags1 = HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD;
	BOOL bApply = HttpAddRequestHeaders(hReq, szHeader, lstrlen(szHeader), dwFlags1);
	
again:
	try
	{
		if (!HttpSendRequest (hReq, NULL, 0, szPostData, lstrlen(szPostData)) )
		{
			dwError = GetLastError () ;
			if ( dwError == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED)
			{
				//This works but there is no way to iterate through the client certs
				DWORD dwCert = 0;
				InternetSetOption(hReq, INTERNET_OPTION_SECURITY_SELECT_CLIENT_CERT, 
					&dwCert, sizeof(dwCert));

				goto again;
			}
		}

		dwSize = sizeof (DWORD) ;  
		if ( !HttpQueryInfo (hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL))
		{
			printf ("HttpQueryInfo %d", GetLastError());
			return "";
		}
	}
	catch (CException* e)
	{
		goto done;
	} 

	dwSize = sizeof (DWORD) ;  
	if ( !HttpQueryInfo (hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL))
	{
		printf ("HttpQueryInfo %d", GetLastError());
		return "";
	}

	if (dwSize > 0 )
	{	
		DWORD dwTotal = 0;
		char* pData = (char*)malloc( dwTotal + dwSize + 1 );
		while ( pData && dwSize ) 
		{ 
			DWORD dwRead = 0;
			InternetReadFile( hReq, pData+dwTotal, dwSize, &dwRead );			
			dwTotal += dwRead;
			pData[dwTotal] = NULL;
			InternetQueryDataAvailable( hReq, &dwSize, 0, 0 );
			if ( dwSize > 0 )
			{ 
				pData = (char*)realloc( pData, dwTotal + dwSize+1 );
			}						
		}

		char* pszAnsi = LF->UTF8ToANSI(pData);
		strJson = pszAnsi;
		delete pszAnsi;
		delete pData;
		pData = NULL;
	}
	
done: // Clean up
	
	if (hReq)
		InternetCloseHandle (hReq);
	if (hConnect)
		InternetCloseHandle (hConnect);
	if (hOpen)
		InternetCloseHandle (hOpen);

	return strJson; 
}
