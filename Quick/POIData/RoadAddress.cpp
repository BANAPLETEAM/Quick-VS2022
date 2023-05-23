#include "StdAfx.h"
#include "RoadAddress.h"
#include "POIDataNew.h"

#define ROAD_NAME_FILE		"RDATA.txt"
#define STREET_NAME_FILE	"SDATA.txt"
#define ENC_OFFSET_VALUE		99


vector<ROAD_NAME> CRoadAddress::m_vecRoadName;
vector<STREET_NAME> CRoadAddress::m_vecStreetName;
CRoadAddressCacheMap CRoadAddress::m_mapRoadAddressCache;
CMkDatabase* CRoadAddress::m_pMkDb = NULL;


CRoadAddress::CRoadAddress(CPOIDataNew *pPOIData)
{
	m_pPOIData = pPOIData;
}

CRoadAddress::~CRoadAddress(void)
{
} 

void CRoadAddress::AutoLoad(CMkDatabase *pMkDb)
{
	m_pMkDb = pMkDb;

	if(!LoadFromFile())
		LoadFromDB();
}

BOOL CRoadAddress::LoadFromFile()
{
	ROAD_NAME rname;
	ZeroMemory(&rname, sizeof(rname));
	if(LoadVector(m_vecRoadName, rname, ROAD_NAME_FILE))
	{
		STREET_NAME sname;
		ZeroMemory(&sname, sizeof(sname));
		if(LoadVector(m_vecStreetName, sname, STREET_NAME_FILE))
		{
			g_bana_log->Print("CRoadAddress:LoadFromFile(ROAD NAME = %d개, STREET NAME = %d개)\n", m_vecRoadName.size(), m_vecStreetName.size());
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CRoadAddress::SaveToFile()
{
	ROAD_NAME rname;
	ZeroMemory(&rname, sizeof(rname));
	if(SaveVector(m_vecRoadName, rname, ROAD_NAME_FILE))
	{
		STREET_NAME sname;
		ZeroMemory(&sname, sizeof(sname));
		if(SaveVector(m_vecStreetName, sname, STREET_NAME_FILE))
			return TRUE;
	}
	
	return FALSE;
}

void CRoadAddress::LoadFromDB()
{
	CString strRoadNameOnly;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_road_address_road_name");
	pCmd.AddParameter(0);

	if(pRs.Execute(&pCmd))
	{
		ROAD_NAME rname;
		ZeroMemory(&rname, sizeof(ROAD_NAME));
		m_vecRoadName.clear();
		m_vecRoadName.assign(pRs.GetRecordCount(), rname);

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("sRoadNameOnly", m_vecRoadName[i].m_szName);
			pRs.GetFieldValue("bUsingAlone", m_vecRoadName[i].m_bUsingAlone);
			pRs.GetFieldValue("nID", m_vecRoadName[i].m_nID);
			pRs.MoveNext();
		}

		sort(m_vecRoadName.begin(), m_vecRoadName.end(), CRoadNameOnlyCompare());

		CString strRoadNameOnly;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "select_road_address_street_name");
		pCmd2.AddParameter(0);

		if(pRs2.Execute(&pCmd2))
		{
			STREET_NAME sname;
			ZeroMemory(&sname, sizeof(STREET_NAME));
			m_vecStreetName.clear();
			m_vecStreetName.assign(pRs2.GetRecordCount(), sname);

			for(int i = 0; i < pRs2.GetRecordCount(); i++)
			{
				pRs2.GetFieldValue("sStreetNameOnly", m_vecStreetName[i].m_szName);
				pRs2.GetFieldValue("nID", m_vecStreetName[i].m_nID);
				pRs2.MoveNext();
			}

			sort(m_vecStreetName.begin(), m_vecStreetName.end(), CStreetNameOnlyCompare());
			g_bana_log->Print("CRoadAddress:LoadFromDB(ROAD NAME = %d개, STREET NAME = %d개)\n", m_vecRoadName.size(), m_vecStreetName.size());
			SaveToFile();
		}
	}
}


BOOL CRoadAddress::SearchRoadAddress(CString strText, SEARCH_POI_VEC &vecPOI)
{
	m_pvecPOI = &vecPOI;

	CString strDigit, strPreDigit;
	SearchSubDigit(strText, strPreDigit, strDigit);

	//숫자를 포함하지 않으면 검색 제외
	if(strDigit.IsEmpty())
		return FALSE;

	//아래 단어가 포함되어 있지 않으면 검색 제외
	if(strText.Find("길") < 0 && strText.Find("로") < 0 && strText.Find("거리") < 0 && strText.Find("고개") < 0 && strText.Find("리") < 0)
		return FALSE;

	for(int i = 0; i < strText.GetLength(); i++)
		for(int k = strText.GetLength() - i; k >= 4; k--)
			if(SearchRoadAddress(strText, strText.Mid(i, k), i + k))
				return TRUE;

	return FALSE;
}

BOOL CRoadAddress::SearchRoadAddress(CString &strText, CString strPart, UINT nEndPos)
{
	vector<ROAD_NAME>::iterator it;
	pair<vector<ROAD_NAME>::iterator, vector<ROAD_NAME>::iterator> itPair;
	itPair = equal_range(m_vecRoadName.begin(), m_vecRoadName.end(), strPart, CRoadNameOnlyCompare());

	for(it = itPair.first; it != itPair.second; it++)
	{
		CString strPart2 = strText.Mid(nEndPos);
		CString strPart3 = strPart2;
		int nStreetPos = strPart2.Find("길");

		if(nStreetPos < 0)
			nStreetPos = strPart2.Find("로");

		UINT nStreetID = 1;

		if(nStreetPos > 0)
		{
			vector<STREET_NAME>::iterator it2;
			pair<vector<STREET_NAME>::iterator, vector<STREET_NAME>::iterator> itPair2;
			itPair2 = equal_range(m_vecStreetName.begin(), m_vecStreetName.end(), strPart2.Left(nStreetPos + 2), CStreetNameOnlyCompare());

			for(it2 = itPair2.first; it2 != itPair2.second; it2++)
			{
				strPart3 = strText.Mid(nEndPos + nStreetPos + 2);
				strPart2 = strPart2.Left(nStreetPos + 2);
				nStreetID = it2->m_nID;
				break;
			}
		}

		if(nStreetID == 1)
		{
			if(it->m_bUsingAlone)
				strPart2.Empty();
			else
				continue;
		}

		CString strPreDigit, strDigit;
		SearchSubDigit(strPart3, strPreDigit, strDigit);

		if(!strDigit.IsEmpty())
		{
			m_strRoadStreetName = it->m_szName + strPart2;

			//CString strRoadAddress;
			//strRoadAddress.Format("[%s][%s][%s][%s][%s]", it->m_szName, strPart2, strPreDigit, strPreDigit.IsEmpty() ? "" : "-", strDigit);
			//g_bana_log->Print("%s\n", strRoadAddress);

			BOOL bMapFound = FALSE;
			CRoadAddressKey rkey(it->m_nID, nStreetID, atol(strPreDigit), atol(strDigit));
			CRoadAddressCacheMap::iterator it;
			it = m_mapRoadAddressCache.find(rkey);
			while(it != m_mapRoadAddressCache.end())
			{
				if(it->first != rkey)
					break;

				bMapFound = TRUE;
				InsertSearchPOI(it->second);
				//g_bana_log->Print("%s %d %d %s (%d, %d)\n", strRoadAddress, it->second.m_nBuildingNo1, 
				//	it->second.m_nBuildingNo2, it->second.m_strBuildingName,
				//	it->second.m_nPosX, it->second.m_nPosY);
				it++;
			}

			if(bMapFound)
				return TRUE;

			if(SearchRoadAddressDB(rkey))
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CRoadAddress::SearchRoadAddressDB(CRoadAddressKey &rkey)
{
	CString strRoadNameOnly;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_road_address_list_1");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(rkey.m_nRoadID);
	pCmd.AddParameter(rkey.m_nStreetID);
	pCmd.AddParameter(rkey.m_nBuildingNo1);
	pCmd.AddParameter(rkey.m_nBuildingNo2);
	if(pRs.Execute(&pCmd)) 
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			CRoadAddressData rdata;
			CString 건물본번, 건물부번;
//			CString 시도명, 시군구명, 법정읍면동명, 건물본번, 건물부번, 건물명, 도로명;

			//pRs.GetFieldValue("시도명", 시도명);
			//pRs.GetFieldValue("시군구명", 시군구명);
			//pRs.GetFieldValue("법정읍면동명", 법정읍면동명);
			//pRs.GetFieldValue("도로명", 도로명);
			pRs.GetFieldValue("건물본번", 건물본번);
			pRs.GetFieldValue("건물부번", 건물부번);
			pRs.GetFieldValue("건물명", rdata.m_strBuildingName);
			pRs.GetFieldValue("POSX", rdata.m_nPosX);
			pRs.GetFieldValue("POSY", rdata.m_nPosY);
			pRs.GetFieldValue("DONGID", rdata.m_nDongID);

			rdata.m_strBuildingName.Remove(' ');
			rdata.m_nBuildingNo1 = atol(건물본번);
			rdata.m_nBuildingNo2 = atol(건물부번);
			rdata.m_nPosX = rdata.m_nPosX * 0.36;
			rdata.m_nPosY = rdata.m_nPosY * 0.36;
			
			InsertSearchPOI(rdata);
	
			m_mapRoadAddressCache.insert(CRoadAddressCacheMap::value_type(rkey, rdata));
//			g_bana_log->Print("%s %s %s %s %s %s %s(%d, %d)\n", 시도명, 시군구명, 법정읍면동명, 도로명, 
//				건물본번, 건물부번, rdata.m_strBuildingName, rdata.m_nPosX, rdata.m_nPosY);
			pRs.MoveNext();
		}

		if(pRs.GetRecordCount() > 0)
			return TRUE;
	}

	return FALSE;
}


void CRoadAddress::SearchSubDigit(CString &strText, CString &strPreDigit, CString &strDigit)
{
	for(int i = 0; i < strText.GetLength(); i++)
	{
		char szTemp = strText.GetAt(i);
		if(szTemp >= '0' && szTemp <= '9')
		{
			strDigit += szTemp;
		}
		else if(szTemp == '-')
		{
			strDigit += szTemp;
		}
		else 
		{
			if(strDigit.GetLength() > 0)
				strPreDigit = strDigit;
			strDigit = "";
		}
	}

	if(strPreDigit.GetLength() > strDigit.GetLength())
		strDigit = strPreDigit;

	strPreDigit.Empty();

	if(strDigit.GetLength() > 0)
	{
		int nPos = strDigit.Find('-');

		if(nPos > 0)
		{
			strPreDigit = strDigit.Left(nPos);
			strDigit = strDigit.Mid(nPos + 1);
		}
	}
}

void CRoadAddress::InsertSearchPOI(CRoadAddressData &rdata)
{
	CSearchPOI poi;

	poi.pPOI = m_pPOIData->GetDongPOI(rdata.m_nDongID, 0, 0); 
	if(!poi.pPOI)
		return;

	poi.bAddressSearch = TRUE;
	poi.nNewPosX = rdata.m_nPosX;
	poi.nNewPosY = rdata.m_nPosY;
	strncpy(poi.szKeyword, rdata.GetDisplayName(rdata, m_strRoadStreetName), 50);
	//strcpy(poi.szKeyword, rdata.GetDisplayName(rdata, m_strRoadStreetName));

	long nDistance = 3000;
	poi.pNearPOI = m_pPOIData->GetNearMainPOI(poi.nNewPosX,	poi.nNewPosY, nDistance);
	poi.nNearDistance = nDistance;

	if(!poi.pNearPOI)
	{
		poi.pNearPOI = m_pPOIData->GetDongPOI(rdata.m_nDongID);
		poi.nNearDistance = poi.pNearPOI->GetDistanceMeter(poi.nNewPosX, poi.nNewPosY);
	}

	poi.nDataPos = 0xFFFF;
	m_pvecPOI->push_back(make_pair(0, poi));
}


template<typename MyVector, typename T>
void CRoadAddress::EncVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] + ENC_OFFSET_VALUE) ^ (i % ENC_OFFSET_VALUE);
}

template<typename MyVector, typename T>
void CRoadAddress::DecVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] ^ (i % ENC_OFFSET_VALUE)) - ENC_OFFSET_VALUE;
}


template<typename MyVector, typename T>
BOOL CRoadAddress::SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath)
{
	DWORD dwDriveList;
	HANDLE hFile = NULL;
	int nRecordSize = 0;
	CString strFileName = (bDefaultPath ? LF->GetModuleFullPath() : "") + strFile;

	//if(vec.size() == 0)
	if(vec.empty())
	{
		DeleteFile(strFileName);
		return FALSE;
	}

	hFile = CreateFile(strFileName, 
		GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != (HANDLE)hFile) 
	{
#ifndef _DEBUG
		EncVector(vec, t);
#endif
		WriteFile((void*)hFile, 
			reinterpret_cast<const char*>(&vec[0]), 
			(DWORD)(vec.size() * sizeof(T)), 
			&dwDriveList, 
			NULL);
		CloseHandle(hFile);
#ifndef _DEBUG
		DecVector(vec, t);
#endif
		return TRUE;
	}

	return FALSE;
}

//reinterpret_cast<const char*>(&m_vecPartPOI[0]), 
//m_vecPartPOI.size() * sizeof(PART_POI_PAIR) , 


template<typename MyVector, typename T>
BOOL CRoadAddress::LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath, long nAssignFreeSpaceRate)
{
	HANDLE hFile, hFileMap;
	unsigned char *pBasePointer;
	DWORD dwSize;
	CString strFileName = (bDefaultPath ? LF->GetModuleFullPath() : "") + strFile;

	hFile = CreateFile(strFileName, GENERIC_READ, 
		FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != hFile)
	{
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		dwSize = GetFileSize(hFile, 0);
		pBasePointer = (unsigned char*) MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);

		long nVSize = dwSize / sizeof(T);
		if(nVSize > 0)
		{
			if(nAssignFreeSpaceRate > 0)
				vec.reserve(nVSize * ( 1.0 + nAssignFreeSpaceRate / 100.0));
			vec.assign(nVSize, t);
			memcpy(reinterpret_cast<char*>(&vec[0]), pBasePointer, nVSize * sizeof(T));
#ifndef _DEBUG
			DecVector(vec, t);
#endif
		}

		UnmapViewOfFile((LPVOID)pBasePointer);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		return nVSize > 0;
	}

	return FALSE;
}
