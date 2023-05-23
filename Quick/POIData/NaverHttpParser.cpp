#include "StdAfx.h"
#include "resource.h"
#include "NaverHttpParser.h"
#include "MkLock.h"
#include "SearchPOIDlg.h"
#include "SimpleMapDlg.h"
#include "LogiUtil.h"
#include "LogiMapNew.h"
#include "POIDataNew.h"
#include "libjson.h"
#include <wininet.h>
#include "afxinet.h"
#include "json.h"

CNaverHttpParser::CNaverHttpParser(void)
{
}

CNaverHttpParser::~CNaverHttpParser(void)
{	
}


JSONNODE*	ParseJSON4NaverLocal(JSONNODE *n,const char* szNodeName);
void		ParseJSON4NaverLocalArray(JSONNODE *n,vector<SEARCH_RESULT_INFO>& vec );


void CNaverHttpParser::Refresh2(QUERY_INFO &QI)
{
	//CString sUrl = "search2/local.nhn?sm=hty&query=#query&menu=location";
	CString strUrl = "v5/api/search?caller=pcweb&query=#query&type=all&page=1&displayCount=20&isPlaceRecommendationReplace=true&lang=ko";
	//CString strUrl = "search2/local.nhn?sm=hty&isFirstSearch=true&query=#query&menu=location";
	CString strKeyword = QI.bPhoneSearch ? LF->GetDashPhoneNumber(QI.strKeyword) : QI.strKeyword;

	CString sSendUrl = strUrl;
	sSendUrl.Replace("#page" ,   "1");
	sSendUrl.Replace("#query", LF->ConvertStringToSendData(strKeyword));


	CString strUrlResult = "http://map.naver.com/" + sSendUrl;
	CString strHtml = OpenNaver(strUrlResult);


	int nLength = strHtml.GetLength();
	int nCount = 0;
 
	//g_bana_log->Print(strHtml); 


	if(QI.nDebugPrintType & DEBUG_PRINT_BODY)
	{
		while(nLength >= nCount)
		{
			//g_bana_log->Print("%s", strHtml.Mid(nCount, min(1000, nLength - nCount)));
			nCount += 1000; 
		}

		//g_bana_log->Print("\n\n");
	}

	vector<SEARCH_RESULT_INFO> vec;
	ParseJSON4NaverLocalValues(strHtml, &vec);
	Analyze2(QI, vec);
}

void CNaverHttpParser::ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec)
{
	if(strHtml.IsEmpty())
		return;

	Json::Value root;
	Json::Reader reader;

	std::string str(strHtml);


	BOOL bRet = reader.parse(str, root);

	if(bRet == FALSE)
		return;

	Json::Value jsonResult = root["result"];

	if(!jsonResult)
		return;

	Json::Value jsonPlace = jsonResult["place"];

	if(!jsonPlace) {
		Json::Value jsonAddress = jsonResult["address"];
		if (!jsonAddress)
			return;
		
		Json::Value jsonJibunsAddress = jsonAddress["jibunsAddress"];
		if (!jsonJibunsAddress)
			return;

		Json::Value jsonList = jsonJibunsAddress["list"];
		if(!jsonList)
			return;

		for(int i=0; i<jsonList.size(); i++)
		{
			SEARCH_RESULT_INFO st;

			st.name_val = jsonList[i]["siteRepName"] ? jsonList[i]["siteRepName"].asCString() : jsonList[i]["name"] ? jsonList[i]["name"].asCString() : "";
			st.tel_val = jsonList[i]["tel"] ? jsonList[i]["tel"].asCString() : "";
			st.address_val = jsonList[i]["fullAddress"] ? jsonList[i]["fullAddress"].asCString() : "";
			st.x_val = jsonList[i]["x"] ? jsonList[i]["x"].asCString() : "";
			st.y_val = jsonList[i]["y"] ? jsonList[i]["y"].asCString() : "";

			vec->push_back(st);
		}

		return;
	}

	Json::Value jsonList = jsonPlace["list"];

	if(!jsonList)
		return;

	for(int i=0; i<jsonList.size(); i++)
	{
		SEARCH_RESULT_INFO st;

		st.name_val = jsonList[i]["name"] ? jsonList[i]["name"].asCString() : "";
		st.tel_val = jsonList[i]["tel"] ? jsonList[i]["tel"].asCString() : "";
		st.address_val = jsonList[i]["address"] ? jsonList[i]["address"].asCString() : "";
		st.x_val = jsonList[i]["x"] ? jsonList[i]["x"].asCString() : "";
		st.y_val = jsonList[i]["y"] ? jsonList[i]["y"].asCString() : "";

		vec->push_back(st);
	}
}

CString CNaverHttpParser::OpenNaver(CString strLocation)
{	
	CString strUrl = strLocation;
	HINTERNET hOpen = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hReq = NULL;
	INTERNET_PORT dwPort;
	/*
	DWORD  dwFlags = INTERNET_FLAG_RELOAD | 
					 INTERNET_FLAG_NO_CACHE_WRITE |
					 INTERNET_FLAG_KEEP_CONNECTION;
	*/

	DWORD  dwFlags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;
	
	
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
	CString sAddHeaders = "";
	CString tmp_url = strUrl;
	tmp_url.Replace("http://", "https://");
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

	/*
    dwFlags |= INTERNET_FLAG_SECURE | 
               INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
               INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  ;
	*/

	if (!(hConnect = InternetConnect(hOpen, strServerName, 80, "", "", INTERNET_SERVICE_HTTP, 0, 0)))
	{
		printf("InternetOpen Failed '%d'\n", GetLastError());
		return "";
	}

	if ( !(hReq = HttpOpenRequest (hConnect, "GET", strObject, HTTP_VERSION, "",
									(LPCTSTR*) AcceptTypes, dwFlags ,0 )))

	{
		printf ("InternetConnect %d", GetLastError());
		return "";
	}

	char szPostData[2048] = {0};

	char szHeader[2048] = {0};
	char buffer[10];
	sAddHeaders += "Connection: keep-alive\r\n";
	sAddHeaders += "Content-Type:text/html\r\n";
	sAddHeaders += "Keep-Alive: timeout=3\r\n";
	sAddHeaders += "Location: " + tmp_url + "\r\n";
	lstrcpy(szHeader, sAddHeaders);

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
				dwCert = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
					SECURITY_FLAG_IGNORE_REVOCATION |
					SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
					SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS |
					SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
					SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
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
