#include "StdAfx.h"
#include "JusoGoKr.h"
#include "tinyxml.h"
#include "WinInet.h"
#include "UTF8Conv.h"
#include "SearchPOI.h"
#include "RoadAddress.h"
#include "POIDataNew.h"

CJusoGoKr::CJusoGoKr()
{
}

CJusoGoKr::~CJusoGoKr(void)
{
	m_mapJuso.clear();
}

void CJusoGoKr::SearchJuso(CString strSearch)
{
	m_mapJuso.clear();

	if(strSearch.GetLength() <= 4)
		return;

	if(strSearch.Find("길") < 0 && strSearch.Find("로") < 0 && strSearch.Find("거리") < 0 && strSearch.Find("고개") < 0 && strSearch.Find("리") < 0)
		return;

	if(strSearch.Right(2) == "길" || strSearch.Right(2) == "로" || strSearch.Right(4) == "거리" || strSearch.Right(4) == "고개" || strSearch.Right(2) == "리")
		return;

	LPCTSTR accept[2]={ _T("*/*"), NULL };

	HINTERNET hInternet = InternetOpen( _T("HTTP"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
 
	//HINTERNET hConnect = InternetConnect( hInternet, "www.juso.go.kr", 80, 
	HINTERNET hConnect = InternetConnect( hInternet, "www.juso.go.kr", 80, 
																	 NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );

	CString strUrl;
	strUrl.Format("addrlink/addrLinkApi.do?confmKey=U01TX0FVVEgyMDE4MDkwNTE5MTM0NjEwODE1OTE=&currentPage=1&countPerPage=10&keyword=%s", ::ConvertStringToSendData(strSearch));

	HINTERNET hRequest = HttpOpenRequest( hConnect, _T("POST"),strUrl, NULL, NULL, accept, 
														   INTERNET_FLAG_DONT_CACHE, 0 );


	//DWORD dwValue = 1000; 
	//BOOL bRet = InternetSetOption(hRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &dwValue, sizeof(dwValue));
 
	HttpSendRequest( hRequest, NULL, 0, NULL, 0 );

	DWORD dwSize = 0; 
	BOOL bQuery = InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );

	CString strText;

	char* szXml = NULL;
	
	if ( bQuery && dwSize > 0 )
	{

		DWORD dwTotal = 0;
		char* pData = (char*)malloc( dwTotal + dwSize + 1 );
		while ( pData && dwSize ) 
		{ 
			DWORD dwRead = 0;
			InternetReadFile( hRequest, pData+dwTotal, dwSize, &dwRead );
			dwTotal += dwRead;
			pData[dwTotal] = NULL;
			InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );
			if ( dwSize > 0 )
			{ 
				pData = (char*)realloc( pData, dwTotal + dwSize+1 );
			}

			szXml = pData;
		}
	}

	InternetCloseHandle( hRequest );
	InternetCloseHandle( hConnect );
	InternetCloseHandle( hInternet );

	ParseXml(szXml);


	//if(m_nType == LOAD_INS_INSERT || m_nType == LOAD_INS_DELETE)
//		return ParseXmlInsertDelete(szXml);
//	else if(m_nType == LOAD_INS_SEARCH)
//		return ParseXmlSearch(szXml);
}

BOOL CJusoGoKr::ParseXml(char *sz)
{
	#define GET_ELEMENT_TEXT(x, y) ::UTF8ToANSI(x->FirstChildElement(y)->GetText());

	if(!sz)
		return FALSE;

	g_bana_log->Print(sz);

	TiXmlDocument doc;
	doc.Parse(sz);

	delete sz;

	TiXmlElement *pRoot = doc.FirstChildElement("results");

	if(!pRoot) 
		return FALSE;

	TiXmlElement *pCommon = pRoot->FirstChildElement("common");

	if(!pCommon) 
		return FALSE;

	CString strErrorCode = GET_ELEMENT_TEXT(pCommon, "errorCode");
	CString strTotalCount = GET_ELEMENT_TEXT(pCommon, "totalCount");

	if(strErrorCode != "0")
		return FALSE;

	if(atoi(strTotalCount) <= 0)
		return FALSE;

	//if(atoi(strTotalCount) > 20)
	//	return FALSE;
	
	TiXmlElement *pJuso = pRoot->FirstChildElement("juso");

	int count = 0;
	

	while(pJuso)
	{
		if(count > 10)
			break;

		CSearchPOI *poi = new CSearchPOI;

		CRoadAddressData rdata;

		CString strAddress = GET_ELEMENT_TEXT(pJuso, "rn");
		CString strBuilding1 = GET_ELEMENT_TEXT(pJuso, "buldMnnm");
		CString strBuilding2 = GET_ELEMENT_TEXT(pJuso, "buldSlno");
		CString strBCode = GET_ELEMENT_TEXT(pJuso, "admCd");
		CString strSan = GET_ELEMENT_TEXT(pJuso, "mtYn");
		CString strJibun1 = GET_ELEMENT_TEXT(pJuso, "lnbrMnnm");
		CString strJibun2 = GET_ELEMENT_TEXT(pJuso, "lnbrSlno");
	
		GetPosXY(strBCode, strSan, strJibun1, strJibun2, &rdata);
		rdata.m_nBuildingNo1 = atoi(strBuilding1);
		rdata.m_nBuildingNo2 = atoi(strBuilding2);

		poi->pPOI = m_poiNew.GetDongPOI(rdata.m_nDongID, 0, 0);

		if(!poi->pPOI)
		{
			pJuso = pJuso->NextSiblingElement("juso");
			continue;
		}
		
		poi->bAddressSearch = TRUE;
		poi->nNewPosX = rdata.m_nPosX;
		poi->nNewPosY = rdata.m_nPosY;
		strcpy(poi->szKeyword, rdata.GetDisplayName(rdata, strAddress));

		long nDistance = 3000;
		poi->pNearPOI = m_poiNew.GetNearMainPOI(poi->nNewPosX,	poi->nNewPosY, nDistance);
		poi->nNearDistance = nDistance;

		if(!poi->pNearPOI)
		{
			poi->pNearPOI = m_poiNew.GetDongPOI(rdata.m_nDongID);
			poi->nNearDistance = poi->pNearPOI->GetDistanceMeter(poi->nNewPosX, poi->nNewPosY);
		}

		poi->nDataPos = 0xFFFF;


		m_mapJuso.insert(MAP_JUSO::value_type(m_mapJuso.size(), poi));
		
		pJuso = pJuso->NextSiblingElement("juso");
		count++;
	}	

	return TRUE;
}

void CJusoGoKr::GetPosXY(CString strBCode, CString strSan, CString strJibun1, CString strJibun2, CRoadAddressData *data)
{
	CMkCommand cmd(m_pMkDb, "select_pos_xy");
	cmd.AddParameter(strBCode);
	cmd.AddParameter(strSan);
	cmd.AddParameter(strJibun1);
	cmd.AddParameter(strJibun2);
	CMkParameter *pParX = cmd.AddParameter(typeBool, typeOutput, sizeof(long), 0);
	CMkParameter *pParY = cmd.AddParameter(typeBool, typeOutput, sizeof(long), 0);
	CMkParameter *pParDongID = cmd.AddParameter(typeBool, typeOutput, sizeof(long), 0);

	if(cmd.Execute())
	{
		long nPosX;
		long nPosY;
		long nDongID;


		pParX->GetValue(nPosX);
		pParY->GetValue(nPosY);
		pParDongID->GetValue(nDongID);

		data->m_nPosX = nPosX;
		data->m_nPosY = nPosY;
		data->m_nDongID = nDongID;
	}
}
