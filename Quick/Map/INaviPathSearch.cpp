#include "stdafx.h"
#include "INaviPathSearch.h"
#include <math.h>
#include <algorithm>
#include <wininet.h>
#include "afxinet.h"

CINaviPathSearch::CINaviPathSearch(BOOL bOnlyDistance, CPoint ptStart, CPoint ptEnd, CString strOption)
{
	m_cINaviPathSection = NULL;
	m_bParse = FALSE;
	m_bOnlyDistance = bOnlyDistance;
	m_ptStartPos = ptStart;
	m_ptEndPos = ptEnd;
	m_strOption = strOption;

	/* 옵션정의
	real_traffic: 실시간 추천 1
	real_traffic_freeroad: 실시간 (무료)
	real_traffic2: 실시간 추천 2
	short_distance_priority: 단거리
	motorcycle: 이륜차
	recommendation1: 실시간추천인데 실시간교통정보를 감안하지 않은것
	*/
}

CINaviPathSearch::CINaviPathSearch(BOOL bOnlyDistance, LONG nStartPosX, LONG nStartPosY, LONG nEndPosX, LONG nEndPosY, CString strOption)
{
	m_cINaviPathSection = NULL;
	m_bParse = FALSE;
	m_bOnlyDistance = bOnlyDistance;
	m_ptStartPos.x = nStartPosX;
	m_ptStartPos.y = nStartPosY;
	m_ptEndPos.x = nEndPosX;
	m_ptEndPos.y = nEndPosY;
	m_strOption = strOption;
}

CINaviPathSearch::~CINaviPathSearch(void)
{
	if(!m_cINaviPathSection) {
		delete m_cINaviPathSection;
		m_cINaviPathSection = NULL;
	}
}

void CINaviPathSearch::AddVia(CPoint ptVia)
{
	m_vecVia.push_back(ptVia);
}

void CINaviPathSearch::AddVia(LONG nPosX, LONG nPosY)
{
	CPoint pt(nPosX, nPosY);
	AddVia(pt);
}

LONG CINaviPathSearch::GetRouteDistance()
{	
	if(!m_bOnlyDistance)
		return 0;

	long nDistance = 0;
	Json::Value jsonBody;

	if (GetBodyJson(jsonBody)) {
		Json::Value jsonData = jsonBody["data"];

		if (jsonData&& jsonData.size() > 0)  {
			Json::Value jsonItem = jsonData[0];

			if(jsonItem && jsonItem["distance"])
				nDistance = jsonItem["distance"].asInt();
		}
	}	

	return nDistance;
}

LONG CINaviPathSearch::GetRouteDistance(vector<CPoint> &vec)
{
	if(m_bOnlyDistance)
		return 0;

	vec.clear();

	long nDistance = 0;
	Json::Value jsonBody;

	if (GetBodyJson(jsonBody)) {
		Json::Value jsonData = jsonBody["data"];

		if (jsonData)  {
			if(jsonData["distance"])
				nDistance = jsonData["distance"].asInt();

			Json::Value paths = jsonData["paths"];
			CPoint ptPre;

			if (paths) {
				for (INT i = 0; i < (INT)paths.size(); i++) {
					Json::Value pathSub = paths[i];
					Json::Value coords = pathSub["coords"];

					for (INT j = 0; j < (INT)coords.size(); j++) {
						CPoint pt;
						pt.x = (LONG)(coords[j]["x"].asDouble() * 1000000.0);
						pt.y = (LONG)(coords[j]["y"].asDouble() * 1000000.0);

						if(ptPre != pt) //중복이 많이 나옴
							vec.push_back(pt);

						ptPre = pt;
					}					
				}
			}
		}
	}	

	return nDistance;
}

 BOOL CINaviPathSearch::GetBodyJson(Json::Value &value)
{
	if(!ParseJson())
		return FALSE;

	Json::Value jsonHeader = m_jsonRoot["header"];

	if(!jsonHeader)							  return FALSE;
	if(!jsonHeader["isSuccessful"])			  return FALSE;
	if(!jsonHeader["isSuccessful"].asBool())  return FALSE;
	if(!jsonHeader["resultCode"])		 	  return FALSE;
	if(jsonHeader["resultCode"].asInt() != 0) return FALSE;

	value = m_jsonRoot["route"];
	return TRUE;
}

BOOL CINaviPathSearch::ParseJson()
{
	if(m_bParse)
		return TRUE;
	
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	JSONCPP_STRING errs;

	CString strParameter = GetParameter();
	CString strResult = RouteStart(strParameter);
	char *text = (char*)((LPCSTR)strResult);
	bool ok = reader->parse(text, text + std::strlen(text), &m_jsonRoot, &errs);

	m_bParse = (ok && errs.size() == 0);
	
	LU->InsertINaviCnsLog(m_bParse, strParameter, strResult, "Q");

	delete reader;
	return m_bParse;
}

CString CINaviPathSearch::RouteStart(CString strParameter)
{	
	CString strJson;

	HINTERNET hSession = InternetOpen("INaviPathSearch", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
	HINTERNET hConnect = InternetConnect(hSession, "api-maps.cloud.toast.com", INTERNET_INVALID_PORT_NUMBER, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hHttpFile = HttpOpenRequest(hConnect, "GET", strParameter, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

	if (::HttpSendRequest(hHttpFile, NULL, 0, 0, 0)) {
		char buffer[1025];
		DWORD dwReadByte = 0, dwErrorCount = 0;

		while (::InternetReadFile(hHttpFile, buffer, 1024, &dwReadByte)) {
			buffer[dwReadByte] = 0;
			strJson += buffer;

			if (dwReadByte < 1024) {
				dwErrorCount++;
				if (dwErrorCount > 10) break;
			}
			else dwErrorCount = 0;
		}

		::InternetCloseHandle(hHttpFile);
	}
	::InternetCloseHandle(hConnect);
	::InternetCloseHandle(hSession);

	return strJson;
}

CString CINaviPathSearch::GetUrl()
{
	return m_bOnlyDistance ? "maps/v3.0/appkeys/SaENtIlAgnLuS0ru/route-summary?" : "maps/v3.0/appkeys/SaENtIlAgnLuS0ru/route-normal?";
}

CString CINaviPathSearch::GetParameter()
{
	///strUrl = "http://api-maps.cloud.toast.com/maps/v3.0/appkeys/SaENtIlAgnLuS0ru/route-summary?";			
	CString strUrl = GetUrl();
	strUrl += "startX="  + GetStringFloat(m_ptStartPos.x / 1000000.0);
	strUrl += "&startY=" + GetStringFloat(m_ptStartPos.y / 1000000.0);
	strUrl += "&endX="   + GetStringFloat(m_ptEndPos.x   / 1000000.0);
	strUrl += "&endY="   + GetStringFloat(m_ptEndPos.y   / 1000000.0);

	char buffer[20];
	LONG nIndex = 1;

	for(int i=0; i<m_vecVia.size(); i++) 
	{
		strUrl += "&via" + CString(_itoa(nIndex, buffer, 10)) + "X=" + GetStringFloat(m_vecVia.at(i).x / 1000000.0);
		strUrl += "&via" + CString(_itoa(nIndex++, buffer, 10)) + "Y=" + GetStringFloat(m_vecVia.at(i).y / 1000000.0);
	}

	strUrl += "&option=" + m_strOption;
	strUrl += "&coordType=WGS84";
	return strUrl;
}

CString CINaviPathSearch::GetStringFloat(float f)
{
	CString strResult; 
	strResult.Format("%.6f",f);
	return strResult;
}

LONG CINaviPathSearch::GetRouteDistanceVia(long nIndex)
{
	if (m_vecVia.size() <= 0) 
		return 0;

	if(!m_cINaviPathSection) {
		m_cINaviPathSection = new CINaviPathSection(m_bOnlyDistance, m_ptStartPos, m_ptEndPos, m_strOption);
		
		for(INT i=0; i<m_vecVia.size(); i++) 
			m_cINaviPathSection->AddVia(m_vecVia.at(i));
	}

	Json::Value jsonBody;

	if (m_cINaviPathSection->GetBodyJson(jsonBody)) {
		Json::Value jsonData = jsonBody["data"];

		if (jsonData)  {
			Json::Value jsonDetailDistance = jsonData["detailDistance"];

			if(jsonDetailDistance) {
				for (INT i = 0; i < jsonDetailDistance.size(); i++) {
					Json::Value jsonItem = jsonDetailDistance[i];

					if(jsonItem && jsonItem["position"] && jsonItem["distance"]) {
						CString strPosition = jsonItem["position"].asCString();
						LONG nDistance = jsonItem["distance"].asInt();

						if(atoi(strPosition.Left(1)) == nIndex)
							return nDistance;
					}
				}
			}
		}
	}	
	
	return 0;
}
