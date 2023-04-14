#include "StdAfx.h"
#include "POIDataNew.h"
#include "POICompareFunc.h"
#include "POIBoundary.h"
#include "MkLock.h"
#include "math.h"


#define POI_BASE_NEAR_DISTANCE	700	//meter
#define DONG_BASE_NEAR_DISTANCE	10000	//meter
#define MIN_POI_LEN				2
#define ENC_OFFSET_VALUE		99
#define LI_OFFSET_START			2000000
#define LI_OFFSET_END			2100000
#define DONG_OFFSET_END			10000
#define SHORT_LI_VALID_METER	50000


static WCHAR m_lpwstr[MAX_PATH];
static CHAR m_lpstr[MAX_PATH];
//static int nAllowMatchLen[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
static int nAllowMatchLen[] =   {0, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7,  8,  8,  9,  9,  10, 10, 11, 12, 12, 13};
static int nAllowMatchLen2[] =  {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4};
CGeoCoordConv CPOIDataNew::m_CoordConv;
CQLog *CPOIDataNew::m_pLog = NULL;


CPOIDataNew::CPOIDataNew(void)
{
	m_pHaveSido = NULL;
	m_pSearchSido = NULL;
	m_pPOICenter = NULL;
	m_bMainSidoDongOnly = FALSE;
	m_pNullPOI = NULL;
	m_bHasPreviousPOIPointSub = FALSE;
	m_nPreviousPOIPointSub = 0;
	m_bHasPreviousDongPointSub = FALSE;
	m_nPreviousDongPointSub = 0;
	m_pDongCache = NULL;
	m_nMaxDongID = 0;
	m_pPOICenterDefault = NULL;
	m_bCapitalArea = FALSE;
	m_bUseSimpleSearch = FALSE;
	m_bDongPriority = FALSE;
	m_bPlaceUsingMyunLi = FALSE;
	m_bSkipSearchPOIIfDongExactlyMatch = FALSE;
	m_bSkipSearchPOIIfDongExactlyMatchLi = FALSE;
	m_vecPPOITemp.reserve(5000);
	m_bHasStationPOI = FALSE;
}

CPOIDataNew::~CPOIDataNew(void)
{
	if(m_pNullPOI)
		DELETE_OBJECT(m_pNullPOI);

	DELETE_OBJECT(m_pHaveSido);
	DELETE_OBJECT(m_pSearchSido);
	DELETE_OBJECT_BR(m_pDongCache);

	P_POI_VEC::iterator it;
	for(it = m_vecPPOITemp.begin(); it != m_vecPPOITemp.end(); it++)
		delete it->second;
	m_vecPPOITemp.clear();

	m_vecPOI.clear();
	m_vecDong.clear();
	m_vecSido.clear();
	m_vecPartPOI.clear();
	m_vecSearchDong.clear();
	m_vecMain.clear();
	m_vecNorDong.clear();
	m_vecPhone.clear();
	m_vecID.clear();
	m_vecPPOITemp.clear();
}


template<typename MyVector, typename T>
void CPOIDataNew::EncVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] + ENC_OFFSET_VALUE) ^ (i % ENC_OFFSET_VALUE);
}

template<typename MyVector, typename T>
void CPOIDataNew::DecVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] ^ (i % ENC_OFFSET_VALUE)) - ENC_OFFSET_VALUE;
}


template<typename MyVector, typename T>
BOOL CPOIDataNew::SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath)
{
	DWORD dwDriveList;
	HANDLE hFile = NULL;
	int nRecordSize = 0;
	CString strFileName = (bDefaultPath ? GetModuleFullPath() : "") + strFile;

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
BOOL CPOIDataNew::LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath, long nAssignFreeSpaceRate)
{
	HANDLE hFile, hFileMap;
	unsigned char *pBasePointer;
	DWORD dwSize;
	CString strFileName = (bDefaultPath ? GetModuleFullPath() : "") + strFile;

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


BOOL CPOIDataNew::SavePOI(CString strFile, BOOL bDefaultPath)
{
	CPOIUnit temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecPOI, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadPOI(CString strFile, BOOL bDefaultPath, long nAssignFreeSpaceRate)
{
	CPOIUnit temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecPOI, temp, strFile, bDefaultPath, nAssignFreeSpaceRate);
}

BOOL CPOIDataNew::SavePartPOI(CString strFile, BOOL bDefaultPath)
{
	PART_POI_INFO temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecPartPOI, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadPartPOI(CString strFile, BOOL bDefaultPath)
{
	PART_POI_INFO temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecPartPOI, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SaveDongPOI(CString strFile, BOOL bDefaultPath)
{
	CPOIUnit temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecDong, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadDongPOI(CString strFile, BOOL bDefaultPath)
{
	CPOIUnit temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecDong, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SavePartDongPOI(CString strFile, BOOL bDefaultPath)
{
	SEARCH_DONG temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecSearchDong, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadPartDongPOI(CString strFile, BOOL bDefaultPath)
{
	SEARCH_DONG temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecSearchDong, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SaveMainVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecMain, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadMainVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecMain, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SaveStationVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecStation, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadStationVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecStation, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SavePhoneVec(CString strFile, BOOL bDefaultPath)
{
	PHONE_INDEX temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecPhone, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadPhoneVec(CString strFile, BOOL bDefaultPath)
{
	PHONE_INDEX temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecPhone, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SaveIDVec(CString strFile, BOOL bDefaultPath)
{
	POIID_INDEX temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecID, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadIDVec(CString strFile, BOOL bDefaultPath)
{
	POIID_INDEX temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecID, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::SaveNorDongVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return SaveVector(m_vecNorDong, temp, strFile, bDefaultPath);
}

BOOL CPOIDataNew::LoadNorDongVec(CString strFile, BOOL bDefaultPath)
{
	NORMALIZE_POI temp;
	ZeroMemory(&temp, sizeof(temp));
	return LoadVector(m_vecNorDong, temp, strFile, bDefaultPath);
}

void CPOIDataNew::SortPOIVector(POI_VEC &vec)
{
	sort(vec.begin(), vec.end(), POIKeyCompare());
}


CString CPOIDataNew::GetModuleFullPath()
{
	CString strFullPath;
	TCHAR szFullPath[MAX_PATH];
	if(GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		int nPos;
		strFullPath = szFullPath;
		if ((nPos = strFullPath.ReverseFind('\\')) != -1)
			strFullPath = strFullPath.Mid(0, ++nPos);
	}

	return strFullPath;
}

LPWSTR CPOIDataNew::A2U(LPCSTR lpData)
{
	m_lpwstr[0] = 0;
	MultiByteToWideChar(949, MB_COMPOSITE, lpData, -1, m_lpwstr, sizeof(m_lpwstr) / sizeof(m_lpwstr[0])); 
	return m_lpwstr;
} 

void CPOIDataNew::A2U2(LPCSTR lpData, LPWSTR lpOut, int nBufferLen)
{
	lpOut[0] = 0;
	MultiByteToWideChar(949, MB_COMPOSITE, lpData, -1, lpOut, nBufferLen); 
}

LPSTR CPOIDataNew::U2A(LPWSTR lpData)
{
	m_lpstr[0] = 0;
	WideCharToMultiByte(CP_ACP, 0, lpData, -1, m_lpstr, MAX_PATH, NULL, NULL); 
	return m_lpstr;
}

void CPOIDataNew::U2A2(LPWSTR lpData, LPSTR lpOut, int nBufferLen)
{
	lpOut[0] = 0;
	WideCharToMultiByte(CP_ACP, 0, lpData, -1, lpOut, nBufferLen, NULL, NULL); 
}

void CPOIDataNew::MakePartPOIVector()
{
	DWORD dwTickCount = GetTickCount();

	m_vecPartPOI.clear();

	long nCount = 0;
	POI_VEC::iterator it;
	PART_POI_INFO info;
	long nVecID = 0;

	for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
	{
		WCHAR *pWStr = A2U(it->m_szName);
		int nLen = wcslen(pWStr);

		info.nVecID = nVecID;
		info.nFullLen = nLen;

		for(int n = 0; n < nLen - 1; n++)
		{
			info.nPos = n;
			info.nIndex = WCharToIndex(&pWStr[n]);
			m_vecPartPOI.push_back(info);
		}

		if(++nCount % 50000 == 0)
			g_bana_log->Print("%d, size= %d\n", nCount, m_vecPartPOI.size());

		nVecID++;
	}


	sort(m_vecPartPOI.begin(), m_vecPartPOI.end(), PartPOIKeyCompare());


	/*
	long nPrintCount = 0;
	for(PART_ITER it = m_vecPartPOI.begin(); it != m_vecPartPOI.end(); it++)
	{
	g_bana_log->Print("%d\n", it->first);
	if(nPrintCount++ > 10000)
	break;
	}
	*/
	g_bana_log->Print("elapsed time = %d, size = %d\n", GetTickCount() - dwTickCount, m_vecPartPOI.size());


}


int CPOIDataNew::SearchPartPOI(WCHAR *pWChar, PART_PAIR_ITER &itPair)
{
	UINT nIndex = WCharToIndex(pWChar);
	itPair = equal_range(m_vecPartPOI.begin(), m_vecPartPOI.end(), nIndex, PartPOIKeyCompare());
	if(itPair.first != itPair.second)
		return distance(itPair.first, itPair.second);

	return 0;
}


inline bool IsSearchPOIBasicConditionOver4(const SEARCH_POI_PAIR &poi, BOOL bDongSepQuery, 
										   CPOIBoundary &boundary, long nMinMatchSize)
{
	if(bDongSepQuery)
	{
		return (poi.second.bDongNearPOI || poi.second.bMatchDongID) && 
			boundary.Has(poi.second.pPOI->GetDongID());
	}
	else
	{
		int nMinMatchSizeFinal = max(nAllowMatchLen[poi.second.nFullLen], nMinMatchSize);
		return (nMinMatchSizeFinal <= poi.second.nLen || 
			poi.second.bBasePOI || poi.second.bHasBasePOI) &&
			boundary.Has(poi.second.pPOI->GetDongID());
	}
}

inline bool IsSearchPOIBasicConditionOver3(const SEARCH_POI_PAIR &poi, BOOL bDongSepQuery,
										   long nMinMatchSize)
{
	if(bDongSepQuery)
	{
		return (poi.second.bDongNearPOI || poi.second.bMatchDongID);
	}
	else
	{
		int nMinMatchSizeFinal = max(nAllowMatchLen[poi.second.nFullLen], nMinMatchSize);
		return (nMinMatchSizeFinal <= poi.second.nLen || 
			poi.second.bBasePOI || poi.second.bHasBasePOI);
	}
}

inline bool IsSearchDongBasicConditionOver(const SEARCH_POI_PAIR &poi)
{
	return (poi.second.nDongMatchType != SHORT_LI_TYPE || 
		poi.second.nCenterPosAwayMeter < SHORT_LI_VALID_METER);
}


void CPOIDataNew::CheckDongRelation(SEARCH_POI_MAP &poiMap, SEARCH_POI_MAP &mapDong, BOOL bDongSepQuery)
{
	SEARCH_POI_MAP::iterator it;
	SEARCH_POI_MAP::const_iterator itDong;

	if(mapDong.size() > 0)
	{
		for(it = poiMap.begin(); it != poiMap.end(); it++)
		{
			CSearchPOI &poi = it->second;
			if(bDongSepQuery)
			{
				for(itDong = mapDong.begin(); itDong != mapDong.end(); itDong++)
				{
					CheckDongRelationComparePOI(poi, itDong->second, bDongSepQuery);
				}
			} 
			else if(!(poi.nKeywordPos & 0x8000))
			{
				for(itDong = mapDong.begin(); itDong != mapDong.end(); itDong++)
				{
					if(poi.nDataPos >> 15)
					{
						if(IsXORMatch(itDong->second.nKeywordPos, poi.nKeywordPos))
						{
							//앞부분이 매칭되지 않은 POI중에서, 해당동명길이가 빠진 경우다
							CheckDongRelationComparePOI(poi, itDong->second, bDongSepQuery);
						}
					}
				}
			}
		}
	}
}

void CPOIDataNew::CheckDongRelationComparePOI(CSearchPOI &poi, const CSearchPOI &dong, BOOL bDongSepQuery)
{
	int nMeter;

	if(poi.pPOI->GetDongID() == dong.pPOI->GetDongID() ||
		poi.pPOI->GetMainDongID() == dong.pPOI->GetDongID())
	{
		if(strstr(poi.pPOI->m_szName, dong.szKeyword) == NULL || bDongSepQuery)
		{
			poi.nLen = poi.nLen + dong.nLen;
			poi.nKeywordPos = poi.nKeywordPos | dong.nKeywordPos;
			poi.bMatchDongID = TRUE;
			poi.pDongMatchPOI = dong.pPOI;
		}
	}
	else if(nMeter = poi.pPOI->IsNearPOI(dong.pPOI))
	{
		//g_bana_log->Print("nMeter = %d, %s %s : %s\n", nMeter,  poi.pPOI->m_szName, poi.pPOI->m_pDong->m_szDong, dong.pPOI->m_szDong);
		if(strstr(poi.pPOI->m_szName, dong.szKeyword) == NULL || bDongSepQuery)
		{
			poi.bDongNearPOI = TRUE;
			poi.pDongMatchPOI = dong.pPOI;
		}
	}

	/*
	g_bana_log->Print("match: %s %d %s DP%s, %s %d %s %d\n", poi.pPOI->m_szName, 
	poi.pPOI->GetDongID(), 
	CPOIDataNew::PosToString(poi.nKeywordPos),
	CPOIDataNew::PosToString(poi.nDataPos),
	itDong->second.pPOI->m_szDong,
	itDong->second.pPOI->GetDongID(),
	CPOIDataNew::PosToString(itDong->second.nKeywordPos),
	poi.nDataPos >> 15);
	*/
}


void CPOIDataNew::CheckPOIRelation(SEARCH_POI_MAP &poiMap)
{																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																			
	SEARCH_POI_MAP::iterator it, it2;

	for(it = poiMap.begin(); it != poiMap.end(); it++)
	{
		if(it->second.nDataPos == it->second.nKeywordPos &&
			it->second.nLen == it->second.nFullLen)
		{
			int nLen = IsFrontMatch(it->second.nDataPos);
			if(nLen >= MIN_POI_LEN)
			{
				USHORT nPos = LenToPos(nLen);				
				for(it2 = poiMap.begin(); it2 != poiMap.end(); it2++)
				{
					int nLen2 = IsFrontMatch(it2->second.nDataPos);
					if(nLen2 >= MIN_POI_LEN + 1)
					{
						if(nAllowMatchLen[it2->second.nFullLen] <= it2->second.nLen)
						{
							if(IsXORMatch(it->second.nKeywordPos, it2->second.nKeywordPos))
							{
								UINT nMeter = it->second.pPOI->IsNearPOI(it2->second.pPOI, POI_BASE_NEAR_DISTANCE);
								if(nMeter > 0)
								{
									it->second.bBasePOI = TRUE;
									if(!(it2->second.bHasBasePOI && 
										it2->second.nBasePOIAwayMeter < nMeter))
									{
										it2->second.bHasBasePOI = TRUE;
										it2->second.pBasePOI = it->second.pPOI;
										it2->second.nBasePOIAwayMeter = nMeter;
									}
								}
							}						
						}
					}
				}
			}
		}
	}	
}

void CPOIDataNew::CheckPOIRelationSeparate(SEARCH_POI_MAP &poiMap)
{
	SEARCH_POI_MAP::iterator it, it2;

	for(it = poiMap.begin(); it != poiMap.end(); it++)
	{
		if(!it->second.bPOISepSecond)
		{
			if(it->second.nDataPos == it->second.nKeywordPos &&
				it->second.nLen == it->second.nFullLen)
			{
				int nLen = IsFrontMatch(it->second.nDataPos);
				if(nLen >= MIN_POI_LEN)
				{
					USHORT nPos = LenToPos(nLen);				
					for(it2 = poiMap.begin(); it2 != poiMap.end(); it2++)
					{
						if(it2->second.bPOISepSecond)
						{
							int nLen2 = IsFrontMatch(it2->second.nDataPos);
							if(nLen2 >= MIN_POI_LEN)
							{
								UINT nMeter = it->second.pPOI->IsNearPOI(it2->second.pPOI, 700);
								if(nMeter > 0)
								{
									it->second.bBasePOI = TRUE;
									if(!(it2->second.bHasBasePOI && 
										it2->second.nBasePOIAwayMeter < nMeter))
									{
										it2->second.bHasBasePOI = TRUE;
										it2->second.pBasePOI = it->second.pPOI;
										it2->second.nBasePOIAwayMeter = nMeter;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int CPOIDataNew::IsFrontMatch(const USHORT &nPos)
{
	int nLen = 0;
	for(int i = 0; i < 16; i++)
	{
		int nOffset = 1 << (15 - i);
		if(nOffset & nPos)
			nLen++;
		else
			break;
	}
	return nLen;
}

BOOL CPOIDataNew::IsXORMatch(const USHORT &nPos, const USHORT &nPos2)
{
	if((nPos & nPos2) == 0) 
	{
		if(nPos & (nPos2 << 1))
		{
			return TRUE;
		}
	}						
	return FALSE;
}

int CPOIDataNew::SearchPOI(CString strKeyword, POI_VEC &vecPOI, int nShowCount)
{
	SEARCH_POI_MAP mapDong;
	return SearchPOI(mapDong, strKeyword, vecPOI, nShowCount);
}

#define SKIP_CUT_COUNT	3000


int CPOIDataNew::SearchPOI(SEARCH_POI_MAP &mapDong, CString strKeyword, POI_VEC &vecPOI, 
						   int nShowCount, BOOL bDongSepQuery, 
						   int nPOISepQuery)
{
	vecPOI.clear();

	SEARCH_POI_VEC v;
	if(SearchPOI(mapDong, strKeyword, v, bDongSepQuery, nPOISepQuery))
	{
		long nCount = 1;
		SEARCH_POI_VEC::iterator it2, itPre;

		for(it2 = v.begin(); it2 != v.end(); it2++)
		{
			CString strDistance;
			if(it2->second.pBasePOI)
				strDistance.Format("→%dm", it2->second.nBasePOIAwayMeter);
			else if(it2 != v.begin())
			{
				int nMeter = itPre->second.pPOI->IsNearPOI(it2->second.pPOI);
				if(nMeter == 0)
					strDistance = "↑2km+";
				else if(nMeter == 1)
					strDistance = "↑상동";
				else 
					strDistance.Format("↑%dm", nMeter);
			}

			CPOIUnit *pPOI = (CPOIUnit*)&(m_vecPOI[it2->first]);
/*
			g_bana_log->Print("%d, %d %s, %s %s %s L:%d,%s %s %s%s\n", nCount, 
				pPOI->m_nID,
				pPOI->m_szName, 
				pPOI->m_pDong->m_szSido, 
				pPOI->m_pDong->m_szGugun, 
				pPOI->m_pDong->m_szDong,
				it2->second.nLen,
				it2->second.bBasePOI ? "H" : "", 
				it2->second.bHasBasePOI ? "HB" : "",
				it2->second.pBasePOI ? it2->second.pBasePOI->m_szName : "",
				strDistance);
*/
			vecPOI.push_back(*pPOI);
			if(++nCount == nShowCount)
				break;

			itPre = it2;
		}
		return nCount;
	}

	return 0;
}

int CPOIDataNew::SearchPOI(SEARCH_POI_MAP &mapDong, CString strKeyword, SEARCH_POI_VEC &v,
						   int nShowCount, BOOL bDongSepQuery, 
						   int nPOISepQuery)
{
	SEARCH_POI_MAP m;
	WCHAR *pWChar = A2U(strKeyword);
	int nLen = wcslen(pWChar);
	PART_PAIR_ITER itPair;
	PART_ITER it;
	BOOL bPOISepSecond = FALSE;

	if(nLen < 2)
		return 0;

	if(!m_bUseSimpleSearch)
	{
		if(nPOISepQuery == 2)
			m.swap(mapDong);		

		InsertSearchPOI(pWChar, nLen, m, itPair, FALSE, (nPOISepQuery == 2));
		//InsertSearchPOI(pWChar, nLen, m, itPair, TRUE, (nPOISepQuery == 2));

		if(nPOISepQuery == 0)	//POI구분쿼리아님
		{
			CheckDongRelation(m, mapDong, bDongSepQuery);
			CheckPOIRelation(m);
		}
		else if(nPOISepQuery == 1)	//POI구분쿼리1차
		{
			mapDong.swap(m);
			m.clear();
			return 0;
		}
		else if(nPOISepQuery == 2) //POI구분쿼리2차
		{
			CheckPOIRelationSeparate(m);
		}

		if(m.size() > 0)
		{
			SEARCH_POI_PAIR temp;
			SEARCH_POI_VEC::iterator itSearchPOI;
			v.assign(m.size(), temp);
			//g_bana_log->Print("v.size() = %d\n", v.size());

			long nMinMatchSize = GetMaxMatchDongSize(mapDong); 

			if(m_pSearchSido && !m_pSearchSido->IsSameBoundary(m_pHaveSido))
			{
				itSearchPOI = copy_if4(m.begin(), m.end(), v.begin(), 
					IsSearchPOIBasicConditionOver4, bDongSepQuery, *m_pSearchSido, nMinMatchSize); 
			}
			else
			{
				itSearchPOI = copy_if3(m.begin(), m.end(), v.begin(), 
					IsSearchPOIBasicConditionOver3, bDongSepQuery, nMinMatchSize); 
			}

			v.erase(itSearchPOI, v.end());
			MakePOIAdditionalValue(v, strKeyword);
			MakePOIDongAvantage(v);
			sort(v.begin(), v.end(), SearchDataCompare());
			RemoveNearSimilarPOI(v);

			return v.size();
		}
	}
	else
	{
		InsertSearchPOI(pWChar, nLen, m, itPair, FALSE, 0);
		CheckDongRelation(m, mapDong, bDongSepQuery);
		CheckPOIRelation(m);

		if(m.size() > 0)
		{
			SEARCH_POI_PAIR temp;
			SEARCH_POI_VEC::iterator itSearchPOI;
			v.assign(m.size(), temp);
			copy(m.begin(), m.end(), v.begin());
			MakePOIAdditionalValue(v, strKeyword);
			sort(v.begin(), v.end(), SearchDataCompareSimple());
			return v.size();
		}
	}

	return 0;
}

void CPOIDataNew::RemoveNearSimilarPOI(SEARCH_POI_VEC &v)
{
	SEARCH_POI_VEC::iterator it, it2;
	int nCount = 10;

	for(it = v.begin(); it != v.end(); it++)
	{
		for(it2 = it; it2 != v.end();)
		{
			if(it != it2)
			{
				if(it->second.pPOI->GetPOIName(TRUE) == it2->second.pPOI->GetPOIName(TRUE) &&
					it->second.pPOI->IsNearPOI(it2->second.pPOI, 80, VERY_NEAR_MAX_POS))
				{
					it2 = v.erase(it2);
					continue;
				}
			}
			it2++;
		}

		if(nCount-- == 0)
			break;
	}
}

long CPOIDataNew::GetMaxMatchDongSize(SEARCH_POI_MAP &mapDong)
{
	SEARCH_POI_MAP::iterator it;
	long nMaxMatch = 0;
	for(it = mapDong.begin(); it != mapDong.end(); it++)
		nMaxMatch = max(nMaxMatch, it->second.nLen);

	return nMaxMatch;
}


void CPOIDataNew::MakePOIAdditionalValue(SEARCH_POI_VEC &v, CString &strKeyword)
{
	SEARCH_POI_VEC::iterator itSearchPOI;

	for(itSearchPOI = v.begin(); itSearchPOI != v.end(); itSearchPOI++)
	{
		if(!itSearchPOI->second.pBasePOI)
		{
			long nDistance = 0;
			itSearchPOI->second.pNearPOI = GetNearMainPOI(itSearchPOI->second.pPOI, nDistance);
			itSearchPOI->second.nNearDistance = nDistance;
		}
		itSearchPOI->second.nCenterPosAwayMeter = itSearchPOI->second.pPOI->GetDistanceMeterLevel(m_pPOICenter);
		itSearchPOI->second.bFullMatch = FALSE;
		if(itSearchPOI->second.pPOI->GetPOIName().Find(strKeyword) == 0 && strKeyword.GetLength() >= 8)
			itSearchPOI->second.bFullMatch = TRUE;
	}
}

void CPOIDataNew::MakePOIDongAvantage(SEARCH_POI_VEC &v)
{
	SEARCH_POI_VEC::iterator itSearchPOI, itSearchEnd;
	DONG_MACTH_POINT dpoint;
	DONG_MACTH_POINT::iterator itdpoint;
	long nDongAvdantage = 10;

	for(itSearchPOI = v.begin(); itSearchPOI != v.end(); itSearchPOI++)
	{
		double dAvantage = sqrt(sqrt((double)nDongAvdantage));
		long nMainDongID = itSearchPOI->second.pPOI->GetMainDongID();
		itdpoint = dpoint.find(nMainDongID);
		if(itdpoint == dpoint.end())
			dpoint.insert(DONG_MACTH_POINT::value_type(nMainDongID, dAvantage));
		else
			itdpoint->second += dAvantage;

		if(nDongAvdantage-- <= 0)
		{
			itSearchPOI++;
			break;
		}
	}

	itSearchEnd = itSearchPOI;
	for(itSearchPOI = v.begin(); itSearchPOI != itSearchEnd; itSearchPOI++)
	{
		long nMainDongID = itSearchPOI->second.pPOI->GetMainDongID();
		itdpoint = dpoint.find(nMainDongID);
		if(itdpoint != dpoint.end())
			itSearchPOI->second.dDongAdvantagePoint = itdpoint->second;

		//g_bana_log->Print("%s, dpoint=%f\n", itSearchPOI->second.pPOI->GetFullName(), itSearchPOI->second.dDongAdvantagePoint);
	}
}

BOOL CPOIDataNew::InsertSearchPOI(WCHAR *pWChar, int nLen, SEARCH_POI_MAP &m, 
								  PART_PAIR_ITER &itPair, BOOL bIfInsertSkip,
								  BOOL bPOISepSecond)
{
	PART_ITER it;

	for(int i = 0; i < nLen - 1; i++)
	{
		int nCount = SearchPartPOI(&pWChar[i], itPair);

		//if(!bIfInsertSkip && nCount > SKIP_CUT_COUNT)
		//	continue;

		//if(bIfInsertSkip && nCount <= SKIP_CUT_COUNT)
		//	continue;

		for(it = itPair.first; it != itPair.second; it++)
		{
			SEARCH_POI_MAP::iterator itSearch;

			itSearch = m.find(it->nVecID);
			if(itSearch != m.end())
			{
				if((BOOL)itSearch->second.bPOISepSecond == bPOISepSecond)
				{
					itSearch->second.nLen++;
					itSearch->second.nKeywordPos |= (3 << (14 - i));
					itSearch->second.nDataPos |= (3 << (14 - it->nPos));
				}
			}
			else
			{
				//if(bIfInsertSkip) 
				//	continue;

				CSearchPOI poi;
				//ZeroMemory(&poi, sizeof(poi));
				poi.nLen = 2;
				poi.nKeywordPos = (3 << (14 - i));
				poi.nDataPos = (3 << (14 - it->nPos));
				poi.nFullLen = it->nFullLen;
				poi.pPOI = &m_vecPOI[it->nVecID];
				poi.bPOISepSecond = bPOISepSecond ? true : false;
				m.insert(SEARCH_POI_MAP::value_type(it->nVecID, poi));
			}
		}

		//g_bana_log->Print("%s%dth: index = %d, wchar = %s, count = %d\n", bIfInsertSkip ? "S" : "N", 
		//					i, WCharToIndex(&pWChar[i]), U2A(&pWChar[i]), nCount);
	}

	return TRUE;
}

CPOIUnit* CPOIDataNew::GetDongPOI(UINT nID, CPOIUnit *pDefaultPOI, BOOL bIfNotExistReturnNullPOI)
{
	if(nID > 0)
	{
		if(m_nMaxDongID > 0 && nID < m_nMaxDongID)
		{
			CPOIUnit *pPOI = GetDongPOIFromCache(nID, pDefaultPOI);
			if(pPOI)
				return pPOI;
		}
		else
		{
			POI_VEC::iterator it = lower_bound(m_vecDong.begin(), m_vecDong.end(), nID, POIKeyCompare());
			if(it != m_vecDong.end() && it->m_nID == nID)
				return &(*it);
		}
	}

	return GetNullPOI(pDefaultPOI, bIfNotExistReturnNullPOI);
}

long CPOIDataNew::GetMaxID()
{
	static long nMaxID = 0;

	if(nMaxID > 0)
		return nMaxID;

	for(int i=0; i<m_vecPOI.size(); i++)
	{
		CPOIUnit unit = m_vecPOI.at(i);

		if(unit.m_nID > nMaxID)
			nMaxID = unit.m_nID;
	}

	return nMaxID;
}

CPOIUnit* CPOIDataNew::GetNormalPOI(UINT nID, CPOIUnit *pDefaultPOI, BOOL bIfNotExistReturnNullPOI)
{
	if(nID > 0)
	{
		if(nID <= GetMaxID())
		{
			POI_VEC::iterator it = lower_bound(m_vecPOI.begin(), m_vecPOI.end(), nID, POIKeyCompare());
			if(it != m_vecPOI.end() && it->m_nID == nID)
				return &(*it);
		}
	}

	return GetNullPOI(pDefaultPOI, bIfNotExistReturnNullPOI);
}

CPOIUnit* CPOIDataNew::GetPOI(UINT nID, CPOIUnit *pDefaultPOI, BOOL bIfNotExistReturnNullPOI)
{
	if(IsDongPOI(nID))
		return GetDongPOI(nID, pDefaultPOI, bIfNotExistReturnNullPOI);
	else
		return GetNormalPOI(nID, pDefaultPOI, bIfNotExistReturnNullPOI);
}


int CPOIDataNew::SearchPartDong(WCHAR *pWChar, DONG_PAIR_ITER &itPair)
{
	//g_bana_log->Print("전동면 %d %d\n", m_vecSearchDong.size());

	itPair = equal_range(m_vecSearchDong.begin(), m_vecSearchDong.end(), pWChar[0], SearchDongKeyCompare());

	if(itPair.first != itPair.second)
		return distance(itPair.first, itPair.second);

	return 0;
}

int CPOIDataNew::SearchDong(CString strKeyword, POI_VEC &vecDong, SEARCH_POI_MAP &m, int nShowCount)
{
	SEARCH_POI_VEC v;
	if(SearchDong(strKeyword, v, m)) 
	{
		long nCount = 1;
		SEARCH_POI_VEC::iterator it2;

		for(it2 = v.begin(); it2 != v.end(); it2++)
		{
			CPOIUnit *pPOI = (CPOIUnit*)&(m_vecDong[it2->first]);
			//g_bana_log->Print("%d\t%d %s %s %s %s %s, nLen = %d, nPos:%s\n", nCount, pPOI->m_nID, pPOI->m_szSido, pPOI->m_szGugun, pPOI->m_szGugun2,
			//	pPOI->m_szDong, pPOI->m_nClass == PN_LI ? pPOI->m_szLi : "", 
			//	it2->second.nLen, PosToString(it2->second.nDataPos));
			vecDong.push_back(*pPOI);
			if(++nCount == nShowCount)
				break;
		}
		return nCount;
	}
	return 0;
}

int CPOIDataNew::SearchDong(CString strKeyword, POI_VEC_POINT &vecDong, int nShowCount)
{
	SEARCH_POI_VEC v;
	SEARCH_POI_MAP m;

	if(SearchDong(strKeyword, v, m)) 
	{
		long nCount = 1;
		SEARCH_POI_VEC::iterator it2;

		for(it2 = v.begin(); it2 != v.end(); it2++)
		{
			CPOIUnit *pPOI = (CPOIUnit*)&(m_vecDong[it2->first]);
			//g_bana_log->Print("전동면 %d\t%d %s %s %s %s %s, nLen = %d, nPos:%s\n", nCount, pPOI->m_nID, pPOI->m_szSido, pPOI->m_szGugun, pPOI->m_szGugun2,
			//	pPOI->m_szDong, pPOI->m_nClass == PN_LI ? pPOI->m_szLi : "", 
			//	it2->second.nLen, PosToString(it2->second.nDataPos));
			vecDong.push_back(pPOI);
			if(++nCount == nShowCount)
				break;
		}
		return nCount;
	}
	return 0;
}

int CPOIDataNew::SearchDong(CString strKeyword, SEARCH_POI_VEC &v, SEARCH_POI_MAP &m, BOOL bOnlyFullNameQuery)
{
	SEARCH_POI_MAP::iterator itSearch;
	CStringW strKeywordW = A2U(strKeyword);
	int nLen = min(strKeywordW.GetLength(), 20);
	DONG_PAIR_ITER itPair;
	DONG_ITER it;
	WCHAR wTemp[100];

	if(nLen < 2)
		return 0;

	int nCheckDong = 0;
	BOOL bCheckDong = FALSE, bSearchDong = FALSE;

	if(strKeyword.Find("1동") > 0 ||
		strKeyword.Find("2동") > 0 ||
		strKeyword.Find("3동") > 0 ||
		strKeyword.Find("4동") > 0)
	{
		int nDong1 = strKeyword.Find("1동");
		int nDong2 = strKeyword.Find("2동");
		int nDong3 = strKeyword.Find("3동");
		int nDong4 = strKeyword.Find("4동");
		BYTE tt = 'A';

		if(nDong1 > 0)
		{
			nCheckDong = 1;
			tt = strKeyword.GetAt(nDong1 - 1);
		}
		else if(nDong2 != -1)
		{
			nCheckDong = 2;
			tt = strKeyword.GetAt(nDong2 - 1);
		}
		else if(nDong3 != -1)
		{
			nCheckDong = 3;
			tt = strKeyword.GetAt(nDong3 - 1);
		}
		else if(nDong4 != -1)
		{
			nCheckDong = 4;
			tt = strKeyword.GetAt(nDong4 - 1);
		}

		if(IsDBCSLeadByte(tt))
			bCheckDong = TRUE;
	}

	for(int i = 2; i <= nLen; i++)
	{
		wcsncpy(wTemp, strKeywordW, 20);
		if(!bOnlyFullNameQuery)
			wTemp[i] = 0;

		//g_bana_log->Print("search dong = %s\n", U2A(wTemp));
		int nCount = SearchPartDong(wTemp, itPair);

		//g_bana_log->Print("count search dong = %s %d\n", U2A(wTemp), nCount);

		for(it = itPair.first; it != itPair.second; it++)
		{
			itSearch = m.find(it->nVecID);

			if(it->nType == 102) //동정보 찾음
				bSearchDong = TRUE;

			if(itSearch != m.end())
			{
				itSearch->second.nLen = wcslen(it->wszKeyword);
				itSearch->second.nDataPos = LenToPos(itSearch->second.nLen);
				itSearch->second.nKeywordPos = itSearch->second.nDataPos;
				itSearch->second.pPOI = &m_vecDong[it->nVecID];
				itSearch->second.nDongMatchType = it->nType;
				U2A2(it->wszKeyword, itSearch->second.szKeyword, 20);
			}
			else
			{
				CSearchPOI poi;
				//ZeroMemory(&poi, sizeof(poi));
				poi.nLen = wcslen(it->wszKeyword);
				poi.nDataPos = LenToPos(poi.nLen);
				poi.nKeywordPos = poi.nDataPos;
				U2A2(it->wszKeyword, poi.szKeyword, 20);
				poi.pPOI = &m_vecDong[it->nVecID];
				poi.nDongMatchType = it->nType;
				poi.nCenterPosAwayMeter = poi.pPOI->GetDistanceMeterLevel(m_pPOICenter, 3000);
				if(it->nType != SHORT_LI_TYPE || poi.nCenterPosAwayMeter < SHORT_LI_VALID_METER)
					m.insert(SEARCH_POI_MAP::value_type(it->nVecID, poi));
			}
		}

		if(bOnlyFullNameQuery)
			break;
	}

	if(bCheckDong == TRUE && nCheckDong != 0 && bSearchDong == FALSE) //반여1동, 반여2동... 이며 앞에 검색에서 동정보를 찾지 못함, 반여동으로 검색
	{
		switch (nCheckDong)
		{
		case 1 :
			strKeyword.Replace("1동", "동");
			break;
		case 2 :
			strKeyword.Replace("2동", "동");
			break;
		case 3 :
			strKeyword.Replace("3동", "동");
			break;
		case 4 :
			strKeyword.Replace("4동", "동");
			break;
		default:
			break;
		}

		strKeywordW = A2U(strKeyword);
		nLen = min(strKeywordW.GetLength(), 20);

		if(nLen >= 2)
		{
			for(int i = 2; i <= nLen; i++)
			{
				wcsncpy(wTemp, strKeywordW, 20);
				if(!bOnlyFullNameQuery)
					wTemp[i] = 0;

				int nCount = SearchPartDong(wTemp, itPair);

				for(it = itPair.first; it != itPair.second; it++)
				{
					itSearch = m.find(it->nVecID);

					if(itSearch != m.end())
					{
						itSearch->second.nLen = wcslen(it->wszKeyword);
						itSearch->second.nDataPos = LenToPos(itSearch->second.nLen);
						itSearch->second.nKeywordPos = itSearch->second.nDataPos;
						itSearch->second.pPOI = &m_vecDong[it->nVecID];
						itSearch->second.nDongMatchType = it->nType;
						U2A2(it->wszKeyword, itSearch->second.szKeyword, 20);
					}
					else
					{
						CSearchPOI poi;
						//ZeroMemory(&poi, sizeof(poi));
						poi.nLen = wcslen(it->wszKeyword);
						poi.nDataPos = LenToPos(poi.nLen);
						poi.nKeywordPos = poi.nDataPos;
						U2A2(it->wszKeyword, poi.szKeyword, 20);
						poi.pPOI = &m_vecDong[it->nVecID];
						poi.nDongMatchType = it->nType;
						poi.nCenterPosAwayMeter = poi.pPOI->GetDistanceMeterLevel(m_pPOICenter, 3000);
						if(it->nType != SHORT_LI_TYPE || poi.nCenterPosAwayMeter < SHORT_LI_VALID_METER)
							m.insert(SEARCH_POI_MAP::value_type(it->nVecID, poi));
					}
				}

				if(bOnlyFullNameQuery)
					break;
			}
		}
	}

	if(m.size() > 0)
	{
		SEARCH_POI_PAIR temp;
		//SEARCH_POI_VEC::iterator itSearchPOI;
		v.assign(m.size(), temp);
		//itSearchPOI = copy_if(m.begin(), m.end(), v.begin(), IsSearchDongBasicConditionOver); 
		//v.erase(itSearchPOI, v.end());
		copy(m.begin(), m.end(), v.begin());
		if(m_bMainSidoDongOnly)
			DeleteNotMainSidoDong(v);

		if(m_bDongPriority)
			sort(v.begin(), v.end(), SearchDongDataCompareDongPriority());
		else
			sort(v.begin(), v.end(), SearchDongDataCompare());

		int nCount = 1;
		SEARCH_POI_VEC::iterator it;
		for(it = v.begin(); it != v.end(); it++)
		{
			CPOIUnit *pPOI = (CPOIUnit*)&(m_vecDong[it->first]);
			g_bana_log->Print("전동면  %d\t%d %s %s %s %s %s, nLen = %d, nPos:%s, %d   %d\n", nCount, pPOI->m_nID, pPOI->m_szSido, pPOI->m_szGugun, pPOI->m_szGugun2,
				pPOI->m_szDong, pPOI->m_nClass == PN_LI ? pPOI->m_szLi : "", 
				it->second.nLen, PosToString(it->second.nDataPos),
				it->second.nCenterPosAwayMeter, m_bMainSidoDongOnly);
		}

		return v.size();
	}

	return 0;
}


CPOIUnit* CPOIDataNew::SearchDong(CString strKeyword)
{
	AddressExceptionReplace(strKeyword);
	AddressToShortName(strKeyword);

	POI_VEC_POINT vecDong; 
	if(SearchDong(strKeyword, vecDong, 0) > 0)
	{
		//g_bana_log->Print("전동면 %s %d <-> %d\n", strKeyword, vecDong[0]->GetDongID());
		return vecDong[0];
	}
	else
		return NULL;
}

CString CPOIDataNew::AddressExceptionReplace(CString &strKeyword)
{ 
	//strKeyword.Replace("일산동구", "일산구");
	//strKeyword.Replace("일산서구", "일산구"); 
	//strKeyword.Replace("천안시 서북구", "천안시");
	//strKeyword.Replace("천안시 동남구", "천안시");
	//strKeyword.Replace("창원시 의창구", "창원시");
	//strKeyword.Replace("창원시 성산구", "창원시");
	//strKeyword.Replace("창원시 마산합포구", "마산시");
	//strKeyword.Replace("창원시 마산회원구", "마산시");
	//strKeyword.Replace("창원시 진해구", "진해시");

	return strKeyword;
}

CString CPOIDataNew::AddressToShortName(CString &strKeyword)
{
	strKeyword.Replace("광역시 ", " ");
	strKeyword.Replace("특별시 ", " ");
	strKeyword.Replace("특별자치도 ", " ");
	strKeyword.Replace("경기도 ", "경기 ");
	strKeyword.Replace("강원도 ", "강원 ");
	strKeyword.Replace("충청북도 ", "충북 ");
	strKeyword.Replace("충청남도 ", "충남 ");
	strKeyword.Replace("경상북도 ", "경북 ");
	strKeyword.Replace("경상남도 ", "경남 ");
	strKeyword.Replace("전라북도 ", "전북 ");
	strKeyword.Replace("전라남도 ", "전남 ");
	//strKeyword.Replace("일산동구 ", "일산구 ");
	//strKeyword.Replace("일산서구 ", "일산구 ");
	strKeyword.Replace("천안시 서북구", "천안시 ");
	//strKeyword.Replace("천안시 동남구", "천안시 ");
	//strKeyword.Replace("세종특별자치시", "세종");
	strKeyword.Remove(' ');

	return strKeyword;
}

CString CPOIDataNew::AddressToLongName(CString &strKeyword)
{
	strKeyword = " " + strKeyword;
	strKeyword.Replace(" 서울 ", " 서울특별시 ");
	strKeyword.Replace(" 부산 ", " 부산광역시 ");
	strKeyword.Replace(" 대구 ", " 대구광역시 ");
	strKeyword.Replace(" 인천 ", " 인천광역시 ");
	strKeyword.Replace(" 대전 ", " 대전광역시 ");
	strKeyword.Replace(" 광주 ", " 광주광역시 ");
	strKeyword.Replace(" 울산 ", " 울산광역시 ");
	strKeyword.Replace(" 제주 ", " 제주특별자치도 ");
	strKeyword.Replace(" 경기 ", " 경기도 ");
	strKeyword.Replace(" 강원 ", " 강원도 ");
	strKeyword.Replace(" 충북 ", " 충청북도 ");
	strKeyword.Replace(" 충남 ", " 충청남도 ");
	strKeyword.Replace(" 경북 ", " 경상북도 ");
	strKeyword.Replace(" 경남 ", " 경상남도 ");
	strKeyword.Replace(" 전북 ", " 전라북도 ");
	strKeyword.Replace(" 전남 ", " 전라남도 ");
	strKeyword.Replace(" 세종", " 세종특별자치시 ");
	strKeyword.Delete(0);

	return strKeyword;
}



void CPOIDataNew::DeleteNotMainSidoDong(SEARCH_POI_VEC &vecPOI)
{
	SEARCH_POI_VEC::iterator it, itRemove;
	itRemove = remove_if(vecPOI.begin(), vecPOI.end(), bind2nd(PPOIDeleteNotMainSidoDong(), *m_pSearchSido));
	vecPOI.erase(itRemove, vecPOI.end());
}

UINT CPOIDataNew::LenToPos(UINT nLen)
{
	int nPos = 0;
	for(int i = 0; i < nLen; i++)
		nPos |= (1 << max(0, (15 - i)));	
	return nPos;
}

CString CPOIDataNew::PosToString(USHORT nPos)
{
#define SIZE_POS	16
	char szPos[SIZE_POS+1];
	for(int i = 0; i < SIZE_POS; i++)
	{
		szPos[SIZE_POS - 1 - i] = (nPos & (1 << i)) ? '1' : '0';
	}

	szPos[SIZE_POS] = 0;
	return CString(szPos);
}

void CPOIDataNew::MakeDongVector()
{
	POI_VEC::iterator it;
	long nVecID = 0;

	if(m_vecSearchDong.size())
		m_vecSearchDong.clear();

	for(it = m_vecDong.begin(); it != m_vecDong.end(); it++)
	{
		CStringW strSido = A2U(it->m_szSido);
		CStringW strGugun = A2U(it->m_szGugun);
		CStringW strGugun2 = A2U(it->m_szGugun2);
		CStringW strDong = A2U(it->m_szDong);
		CStringW strSidoFull;
		CStringW strDo;

		if(IsDo(it->m_szSido))
		{
			strDo = strSido;
			strSido = strGugun;
			strGugun = strGugun2;
			strGugun2 = "";
		}
		else
			strSidoFull = strSido + L"시";


		if(it->m_nClass == PN_SIDO)
		{
			//1.서울시, 강남구
			MakeDongVectorSub(nVecID, strDong, 1);

			//2.서울, 강남
			if(strDong.GetLength() > 2)
				MakeDongVectorSub(nVecID, strDong.Left(strDong.GetLength() - 1), 2);

			//3.서울강남구
			if(strGugun == strDong && strGugun2.IsEmpty() && strGugun.Right(1) != L"시")
			{
				CStringW strGugunTemp = strGugun.Left(strGugun.GetLength() - 1);
				if(strSido != strGugunTemp)
					MakeDongVectorSub(nVecID, strSido + strGugunTemp, 3);
			}
		}
		else if(it->m_nClass == PN_LI)
		{
			CStringW strSidoS = strSido.GetLength() > 2 ? strSido.Left(strSido.GetLength() - 1) : strSido;
			CStringW strLi = A2U(it->m_szLi);
			CStringW strLiS = strLi.GetLength() > 2 ? strLi.Left(strLi.GetLength() - 1) : strLi;
			BOOL bHasSidoS = (strSido != strSidoS);
			BOOL bHasLiS = (strLi != strLiS);

			if(strDo.GetLength() > 0)
				MakeDongVectorSub(nVecID, strDo + strSido + strGugun + strGugun2 + strDong + strLi, 300);

			MakeDongVectorSub(nVecID, strSido + strGugun + strGugun2 + strDong + strLi, 100);
			if(strSidoFull.GetLength() > 0)
				MakeDongVectorSub(nVecID, strSidoFull + strGugun + strGugun2 + strDong + strLi, 101);

			MakeDongVectorSub(nVecID, strGugun + strGugun2 + strDong + strLi, 101);
			MakeDongVectorSub(nVecID, strLi, 14);
			if(bHasLiS)
				MakeDongVectorSub(nVecID, strLiS, SHORT_LI_TYPE);
			MakeDongVectorSub(nVecID, strDong + strLi, 15);
			MakeDongVectorSub(nVecID, strSido + strLi, 16);
			if(bHasSidoS)
				MakeDongVectorSub(nVecID, strSidoS + strLi, 17);
		}
		else
		{
			CStringW strDongS = strDong.GetLength() > 2 ? strDong.Left(strDong.GetLength() - 1) : strDong;
			CStringW strGugunS = strGugun.GetLength() > 2 ? strGugun.Left(strGugun.GetLength() - 1) : strGugun;
			CStringW strSidoS = strSido.GetLength() > 2 ? strSido.Left(strSido.GetLength() - 1) : strSido;
			BOOL bHasDongS = (strDong != strDongS);
			BOOL bHasGugunS = (strGugun != strGugunS);
			BOOL bHasSidoS = (strSido != strSidoS);

			if(strDo.GetLength() > 0)
			{
				MakeDongVectorSub(nVecID, strDo + strSido + strGugun + strGugun2 + strDong, 301);
				MakeDongVectorSub(nVecID, strDo + strDong, 200);
				if(bHasDongS)
					MakeDongVectorSub(nVecID, strDo + strDongS, 201);
			}
			
			MakeDongVectorSub(nVecID, strSido + strGugun + strGugun2 + strDong, 102);
			if(strSidoFull.GetLength() > 0)
				MakeDongVectorSub(nVecID, strSidoFull + strGugun + strGugun2 + strDong, 103);

			MakeDongVectorSub(nVecID, strSido + strDong, 4);
			if(bHasDongS)
				MakeDongVectorSub(nVecID, strSido + strDongS, 5);

			if(bHasSidoS)
			{
				MakeDongVectorSub(nVecID, strSidoS + strDong, 30);
				if(bHasDongS)
					MakeDongVectorSub(nVecID, strSidoS + strDongS, 31);
			}

			if(!strGugun.IsEmpty())
			{
				MakeDongVectorSub(nVecID, strGugun + strDong, 6);

				if(strGugunS != strDongS)
				{
					if(bHasGugunS)
						MakeDongVectorSub(nVecID, strGugunS + strDong, 7);
					if(bHasDongS)
						MakeDongVectorSub(nVecID, strGugun + strDongS, 8);
					if(bHasGugunS && bHasDongS)
						MakeDongVectorSub(nVecID, strGugunS + strDongS, 9);
				}
			}

			MakeDongVectorSub(nVecID, strDong, 10);
			if(bHasDongS && it->GetDistanceMeter(m_pPOICenter) < 80000)	//80km이내의 동만 '동'때고 검색가능하게
				MakeDongVectorSub(nVecID, strDongS, 11);

			MakeDongVectorException(*it, nVecID);
		}

		nVecID++;
	}

	sort(m_vecSearchDong.begin(), m_vecSearchDong.end(), SearchDongKeyCompare());

	g_bana_log->Print("dong vector size = %d\n", m_vecSearchDong.size());

	//	SEARCH_DONG_VEC::iterator it2;
	//	for(it2 = m_vecSearchDong.begin(); it2 != m_vecSearchDong.end(); it2++)
	//	{
	//		g_bana_log->Print("%s\n", U2A(it2->wszKeyword));
	//	}

}

void CPOIDataNew::MakeDongVectorSub(long nVecID, CStringW strDong, int nType)
{
	SEARCH_DONG dong;
	dong.nVecID = nVecID;
	dong.nType = nType;
	wcscpy(dong.wszKeyword, strDong);
	m_vecSearchDong.push_back(dong);
	//	g_bana_log->Print("%d. %s\n", nType, U2A(dong.wszKeyword));
}

void CPOIDataNew::MakeDongVectorException(CPOIUnit& poi, long nVecID)
{
	if(poi.m_nID == 7764)	//여의동->여의도
		MakeDongVectorSub(nVecID, L"여의도", 12);

	if(poi.m_nID == 4130)
	{
		MakeDongVectorSub(nVecID, L"동부이촌", 12);
		MakeDongVectorSub(nVecID, L"서부이촌", 12);
	}
}

BOOL CPOIDataNew::MakeDongCacheArray()
{
	long nMaxID = 0, nID;
	POI_VEC::iterator it;

	DELETE_OBJECT_BR(m_pDongCache);

	for(it = m_vecDong.begin(); it != m_vecDong.end(); it++)
	{
		if(it->m_nClass == PN_LI)
			nID = it->m_nID - LI_OFFSET_START + DONG_OFFSET_END;
		else 
			nID = it->m_nID;

		nMaxID = max(nMaxID, nID);
	}

	if(nMaxID > 1000000)
		return FALSE;

	m_pDongCache = new DWORD[++nMaxID];
	ZeroMemory(m_pDongCache, nMaxID * sizeof(DWORD));

	for(it = m_vecDong.begin(); it != m_vecDong.end(); it++)
	{
		if(it->m_nClass == PN_LI)
			nID = it->m_nID - LI_OFFSET_START + DONG_OFFSET_END;
		else 
			nID = it->m_nID;

		m_pDongCache[nID] = (DWORD)&(*it);
	}

	m_nMaxDongID = nMaxID;

	return TRUE;
}

int CPOIDataNew::SearchPOIWithDong(CString strKeyword, SEARCH_POI_VEC &vecPOI, SEARCH_POI_VEC &vecDong,
								   BOOL bSearchPhone, BOOL bOnlySearchPhone, BOOL bStartPlace)
{
	static SEARCH_POI_VEC vecLastPOI, vecLastDong;
	SEARCH_POI_MAP mapDong;
	int nCountDong = 0, nCountPOI = 0;
	SEARCH_POI_PAIR temp;

	AddSpecialLog("Keyword: " + strKeyword);
	TrimKeyword(strKeyword);

	if(m_strLastKeyword == strKeyword)
	{
		vecPOI.assign(vecLastPOI.size(), temp);
		std::copy(vecLastPOI.begin(), vecLastPOI.end(), vecPOI.begin());
		vecDong.assign(vecLastDong.size(), temp);
		std::copy(vecLastDong.begin(), vecLastDong.end(), vecDong.begin());
		nCountDong = vecDong.size();
		nCountPOI = vecPOI.size();
		//g_bana_log->Print("Cache hit\n");
	}
	else
	{
		if(!bOnlySearchPhone)
		{
			if(!m_bUseSimpleSearch && CheckKeywordSpace(strKeyword, m_strLastDongKeyword, m_strLastPOIKeyword))
			{
				int nPOISepQuery = 0;
				nCountDong = SearchDong(m_strLastDongKeyword, vecDong, mapDong, TRUE);
				if(nCountDong == 0)
				{
					nPOISepQuery++;
					nCountPOI = SearchPOI(mapDong, m_strLastDongKeyword, vecPOI, 0, FALSE, nPOISepQuery++);
				}

				nCountPOI += SearchPOI(mapDong, m_strLastPOIKeyword, vecPOI, 0, (nPOISepQuery == 0), nPOISepQuery);
				UpdateDongMatchTypeToPOI(vecDong, vecPOI);
			}
			else if(!IsStringDigit(strKeyword))
			{
				BOOL bSkipPOISearch = FALSE;

				m_strLastDongKeyword = strKeyword;
				m_strLastPOIKeyword.Empty();

				nCountDong = SearchDong(strKeyword, vecDong, mapDong);
				if(nCountDong > 0 && (m_bSkipSearchPOIIfDongExactlyMatch || !bStartPlace))
				{
					if(vecDong[0].second.pPOI->GetDong() == strKeyword ||
						vecDong[0].second.pPOI->GetDong(TRUE) == strKeyword)
					{
						bSkipPOISearch = TRUE;
					}
					else if(m_bSkipSearchPOIIfDongExactlyMatchLi &&
							vecDong[0].second.pPOI->IsLiPOI() &&
							vecDong[0].second.pPOI->GetLi(FALSE) == strKeyword)
					{
						bSkipPOISearch = TRUE;
					}
				}

				if(!bSkipPOISearch)
					nCountPOI = SearchPOI(mapDong, strKeyword, vecPOI);

				UpdateDongMatchTypeToPOI(vecDong, vecPOI);
			}
		}

		if(bSearchPhone)
		{
			m_strLastDongKeyword = strKeyword;
			m_strLastPOIKeyword.Empty();

			CString strPhone = ExtractPhoneNumber(strKeyword);
			if(strPhone.GetLength() > 0)
				SearchPhoneNumber(strPhone, vecPOI);				
		}

		m_strLastKeyword = strKeyword;

		SEARCH_POI_VEC(vecLastPOI).swap(vecLastPOI);
		SEARCH_POI_VEC(vecLastDong).swap(vecLastDong);

		vecLastPOI.assign(vecPOI.size(), temp);
		copy(vecPOI.begin(), vecPOI.end(), vecLastPOI.begin());
		vecLastDong.assign(vecDong.size(), temp);
		copy(vecDong.begin(), vecDong.end(), vecLastDong.begin());
	}

	return nCountDong + nCountPOI;
}

void CPOIDataNew::UpdateDongMatchTypeToPOI(SEARCH_POI_VEC &vecDong, SEARCH_POI_VEC &vecPOI)
{
	SEARCH_POI_VEC::iterator it, it2;
	for(it = vecPOI.begin(); it != vecPOI.end(); it++)
	{
		for(it2 = vecDong.begin(); it2 != vecDong.end(); it2++)
		{
			if(it2->second.pPOI->GetDongID() == it->second.pPOI->GetMainDongID())
			{
				it->second.nDongMatchType = it2->second.nDongMatchType;
			}
		}
	}
}

int CPOIDataNew::SearchPOIWithDong(CString strKeyword, POI_VEC &vecPOI, POI_VEC &vecDong, 
								   int nShowCount, BOOL bSearchPhone)
{
	SEARCH_POI_MAP mapDong;
	int nCountDong, nCountPOI;

	if(CheckKeywordSpace(strKeyword, m_strLastDongKeyword, m_strLastPOIKeyword))
	{
		g_bana_log->Print("dong = %s, poi = %s\n", m_strLastDongKeyword, m_strLastPOIKeyword);
		nCountDong = SearchDong(m_strLastDongKeyword, vecDong, mapDong);
		nCountPOI = SearchPOI(mapDong, m_strLastPOIKeyword, vecPOI, nShowCount, TRUE);
	}
	else
	{
		m_strLastDongKeyword = strKeyword;
		m_strLastPOIKeyword.Empty();
		nCountDong = SearchDong(strKeyword, vecDong, mapDong);
		nCountPOI = SearchPOI(mapDong, strKeyword, vecPOI, nShowCount);
	}

	return nCountDong + nCountPOI;
}

BOOL CPOIDataNew::CheckKeywordSpace(CString &strKeyword, CString &strDong, CString &strPOI)
{
	int n = strKeyword.Find(" ");	
	if(n > 0)
	{
		strDong = strKeyword.Left(n);
		strPOI = strKeyword.Right(strKeyword.GetLength() - n - 1);
		if(strDong.GetLength() <= 10 && strPOI.GetLength() >= 6)
			return TRUE;
	}

	strKeyword.Remove(' ');
	return FALSE;
}

inline bool NormalizePosCompare(const NORMALIZE_POI &lhs, const NORMALIZE_POI &rhs)
{
	return (lhs.nNorPosX < rhs.nNorPosX) ||
		(lhs.nNorPosX == rhs.nNorPosX &&
		lhs.nNorPosY < rhs.nNorPosY);
}

BOOL CPOIDataNew::UpdateDongHasPOI(BOOL bFromFile)
{
	POI_VEC::iterator it;
	m_vecSido.clear();
	m_vecNorDong.clear();

	if(!MakeDongCacheArray())
		return FALSE;

	BOOL bLoadNorDongVector = bFromFile ? LoadNorDongVec() : FALSE;

	for(it = m_vecDong.begin(); it != m_vecDong.end(); it++)
	{
		it->m_pParent = GetDongPOIFromCache((UINT)it->m_nParentID);
		it->m_pMainDong = GetDongPOIFromCache((UINT)it->m_nMainDongID, (CPOIUnit*)&(*it));
		it->m_bTopIsDO = IsDo(it->m_szSido);

		if(it->m_nClass == PN_SIDO)
		{
			CString strRight2 = CString(it->m_szDong).Right(2);
			if(strRight2 == "구" || strRight2 == "군")
				it->m_nClass = PN_GUGUN;

			m_vecSido.push_back((CPOIUnit*)&(*it));
		}
		else if(it->m_nClass == PN_GUGUN)
		{
			m_vecSido.push_back((CPOIUnit*)&(*it));
		}


		if(!bLoadNorDongVector)
		{
			if(it->m_nClass == PN_MOBILE)
			{
				NORMALIZE_POI nor;
				nor.pPOI = (CPOIUnit*)&(*it);
				nor.pPOI->GetNormalizePos(nor.nNorPosX, nor.nNorPosY);
				nor.nID = it->m_nID;
				m_vecNorDong.push_back(nor);
			}
		}

		m_mapChildList.insert(POI_CHILD_LIST_MAP::value_type(it->m_nParentID, it->m_nID));
	}

	if(!bLoadNorDongVector)
	{
		sort(m_vecNorDong.begin(), m_vecNorDong.end(), NormalizePosCompare);
		SaveNorDongVec();
	}
	else
	{
		MakeDongPreviousOffset(TRUE);

		NORMALIZE_POI_ITER it;
		for(it = m_vecNorDong.begin(); it != m_vecNorDong.end(); it++)
			it->pPOI = GetDongPreviousOffset(it->pPOI);
	}

	
	

	return TRUE;
}

BOOL CPOIDataNew::IsDo(CString strSido)
{
	if(strSido == "경기" ||
		strSido == "충북" ||
		strSido == "충남" ||
		strSido == "경북" ||
		strSido == "경남" ||
		strSido == "전북" ||
		strSido == "전남" ||
		strSido == "강원" ||
		strSido == "제주")
	{
		return TRUE;
	}
	return FALSE;
}

void CPOIDataNew::UpdatePOIHasPOI(CString strRegionName, BOOL bFromFile)
{
	m_vecMain.clear();
	m_vecPhone.clear();
	m_vecID.clear();
	m_vecStation.clear();

	BOOL bLoadMainVector = bFromFile ? LoadMainVec(strRegionName + POI_MAIN_VEC_NAME) : FALSE;
	BOOL bLoadStationVector = (bFromFile && m_bHasStationPOI) ? LoadStationVec(strRegionName + POI_STATION_VEC_NAME) : FALSE;
	BOOL bLoadPhoneVector = bFromFile ? LoadPhoneVec(strRegionName + POI_PHONE_VEC_NAME) : FALSE;
	BOOL bLoadIDVector = bFromFile ? LoadIDVec(strRegionName + POI_ID_VEC_NAME) : FALSE;

	long nVecID = 0;
	POI_VEC::iterator it;
	for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
	{
		//if(it->GetDongID() > 10000)
		//	g_bana_log->Print("**it->GetDongID() > 10000, %d, %d\n", it->m_nID, it->GetDongID());

		it->m_pDong = GetDongPOIFromCache(it->GetDongID());

		if(!bLoadMainVector)
		{
			if(it->m_nClass == PN_MOBILE)
			{
				NORMALIZE_POI nor;
				nor.pPOI = (CPOIUnit*)&(*it);
				nor.pPOI->GetNormalizePos(nor.nNorPosX, nor.nNorPosY);
				nor.nID = it->m_nID;
				m_vecMain.push_back(nor);
			}
		}

		if(m_bHasStationPOI && !bLoadStationVector)
		{
			if((it->m_nClass == PN_MOBILE || it->m_nPriority > 0))
			{
				if(strncmp(&it->m_szName[strlen(it->m_szName) - 2], "역", 2) == 0)
				{
					NORMALIZE_POI nor;
					nor.pPOI = (CPOIUnit*)&(*it);
					nor.pPOI->GetNormalizePos(nor.nNorPosX, nor.nNorPosY);
					nor.nID = it->m_nID;
					m_vecStation.push_back(nor);
				}
			}
		}

		if(!bLoadPhoneVector)
		{
			if(it->m_bHasPhone)
			{
				PHONE_INDEX pi;
				pi.nPhone = atol(it->m_szPhone);
				pi.pPOI = (CPOIUnit*)&(*it);
				m_vecPhone.push_back(pi);
			}
		}

		if(!bLoadIDVector)
		{
			POIID_INDEX id;
			id.nVecID = nVecID++;
			id.nPOIID = it->m_nID;
			m_vecID.push_back(id);
		}
	}

	if(!bLoadMainVector)
	{
		sort(m_vecMain.begin(), m_vecMain.end(), NormalizePosCompare);
		SaveMainVec(strRegionName + POI_MAIN_VEC_NAME);
	}
	else
	{
		MakePOIPreviousOffset(TRUE);

		NORMALIZE_POI_ITER it;
		for(it = m_vecMain.begin(); it != m_vecMain.end(); it++)
			it->pPOI = GetPOIPreviousOffset(it->pPOI);
	}

	if(m_bHasStationPOI)
	{
		if(!bLoadMainVector)
		{
			sort(m_vecStation.begin(), m_vecStation.end(), NormalizePosCompare);
			SaveStationVec(strRegionName + POI_STATION_VEC_NAME);
		}
		else
		{
			NORMALIZE_POI_ITER it;
			for(it = m_vecStation.begin(); it != m_vecStation.end(); it++)
				it->pPOI = GetPOIPreviousOffset(it->pPOI);
		}
	}

	if(!bLoadPhoneVector)
	{
		sort(m_vecPhone.begin(), m_vecPhone.end(), PhoneIndexCompare());
		SavePhoneVec(strRegionName + POI_PHONE_VEC_NAME);
	}
	else
	{
		PHONE_INDEX_ITER it;
		for(it = m_vecPhone.begin(); it != m_vecPhone.end(); it++)
			it->pPOI = GetPOIPreviousOffset(it->pPOI);
	}

	if(!bLoadIDVector)
	{
		sort(m_vecID.begin(), m_vecID.end(), POIIDIndexCompare());
		SaveIDVec(strRegionName + POI_ID_VEC_NAME);
	}

	CString strInfo;
	strInfo.Format("m_vecMain(%d)= %d, m_vecPhone(%d) = %d, m_vecID(%d) = %d, m_vecStation(%d) = %d", 
					bLoadMainVector, m_vecMain.size(), 
					bLoadPhoneVector, m_vecPhone.size(), 
					bLoadIDVector, m_vecID.size(),
					bLoadStationVector && m_bHasStationPOI, m_vecStation.size());
	AddSpecialLog(strInfo);
	g_bana_log->Print("%s\n", strInfo);
}

template<typename T>
CPOIUnit* CPOIDataNew::GetNorNearPOI(T &t, CPOIUnit *pPOI, long &nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = POI_BASE_NEAR_DISTANCE;

	NORMALIZE_POI nor, nor2;
	pPOI->GetNormalizePos(nor.nNorPosX, nor.nNorPosY);
	nor.pPOI = pPOI;

	NORMALIZE_POI_ITER it, itMin = t.end();
	nor2.nNorPosX = nor.nNorPosX - NEAR_MAX_POS_POI;
	nor2.nNorPosY = nor.nNorPosY - NEAR_MAX_POS_POI;
	NORMALIZE_POI_PAIR_ITER itPairL = equal_range(t.begin(), t.end(), nor2, NormalizePosCompare);

	nor2.nNorPosX = nor.nNorPosX + NEAR_MAX_POS_POI;
	nor2.nNorPosY = nor.nNorPosY + NEAR_MAX_POS_POI;
	NORMALIZE_POI_PAIR_ITER itPairR = equal_range(itPairL.first, t.end(), nor2, NormalizePosCompare);

	long nNorPosY1 = nor.nNorPosY - NEAR_MAX_POS_POI;
	long nNorPosY2 = nor.nNorPosY + NEAR_MAX_POS_POI; 

	for(it = itPairL.first; it != itPairR.second; it++)
	{
		if(it->nNorPosY >= nNorPosY1 &&
			it->nNorPosY <= nNorPosY2)
		{
			long nDistance = pPOI->GetDistanceMeter(it->pPOI);
			if(nDistance < nMinDistance)
			{
				nMinDistance = nDistance;
				itMin = it;
			}
		}
	}

	return (itMin == t.end()) ? NULL : itMin->pPOI;
}

template<typename T>
CPOIUnit* CPOIDataNew::GetNorNearPOI(T &t, long nPosX, long nPosY, long& nMinDistance)
{
	CPOIUnit *pPOI = new CPOIUnit;
	memcpy(pPOI, this, sizeof(CPOIUnit));
	pPOI->m_nPosX = nPosX;
	pPOI->m_nPosY = nPosY;
	CPOIUnit *pNearPOI = GetNorNearPOI(t, pPOI, nMinDistance);
	delete pPOI;
	return pNearPOI;
}

CPOIUnit* CPOIDataNew::GetNearMainPOI(CPOIUnit *pPOI, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = POI_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecMain, pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearMainPOI(CPOIUnit *pPOI)
{
	long nMinDistance = POI_BASE_NEAR_DISTANCE;
	return GetNearMainPOI(pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearMainPOI(long nPosX, long nPosY, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = POI_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecMain, nPosX, nPosY, nMinDistance);
}


CPOIUnit* CPOIDataNew::GetNearStationPOI(CPOIUnit *pPOI, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = POI_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecStation, pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearStationPOI(CPOIUnit *pPOI)
{
	long nMinDistance = POI_BASE_NEAR_DISTANCE;
	return GetNearStationPOI(pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearStationPOI(long nPosX, long nPosY, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = POI_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecStation, nPosX, nPosY, nMinDistance);
}


CPOIUnit* CPOIDataNew::GetNearDongPOI(CPOIUnit *pPOI, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = DONG_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecNorDong, pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearDongPOI(CPOIUnit *pPOI)
{
	long nMinDistance = DONG_BASE_NEAR_DISTANCE;
	return GetNearDongPOI(pPOI, nMinDistance);
}

CPOIUnit* CPOIDataNew::GetNearDongPOI(long nPosX, long nPosY, long& nMinDistance)
{
	if(nMinDistance == 0)
		nMinDistance = DONG_BASE_NEAR_DISTANCE;

	return GetNorNearPOI(m_vecNorDong, nPosX, nPosY, nMinDistance);
}


int CPOIDataNew::SearchPhoneNumber(CString strPhone, POI_VEC &vecPhone)
{
	strPhone.Remove('-');

	if(strPhone.GetLength() >= 7)
	{
		CString strDDD, strBody;
		if(strPhone.Left(2) == "01")
			GetPhoneDivBody(strPhone, 3, strDDD, strBody);
		else if(strPhone.Left(2) == "02")
			GetPhoneDivBody(strPhone, 2, strDDD, strBody);
		else if(strPhone.Left(3) == "050")
			GetPhoneDivBody(strPhone, 4, strDDD, strBody);
		else if(strPhone.Left(1) == "0")
			GetPhoneDivBody(strPhone, 3, strDDD, strBody);
		else
			strBody = strPhone;

		PHONE_INDEX_ITER it; 
		PHONE_INDEX_PAIR_ITER itPair = equal_range(m_vecPhone.begin(), m_vecPhone.end(), atol(strBody), PhoneIndexCompare());
		for(it = itPair.first; it != itPair.second; it++)
		{
			if(strDDD.IsEmpty() || strDDD == it->pPOI->m_szDDD)
				vecPhone.push_back(*(it->pPOI));
		}
	}

	return vecPhone.size();
}

int CPOIDataNew::SearchPhoneNumber(CString strPhone, SEARCH_POI_VEC &vecPhone)
{
	POI_VEC vec;
	POI_VEC::iterator it;
	SEARCH_POI_VEC::iterator it2;
	SEARCH_POI_VEC vecTemp;
	SEARCH_POI_PAIR	temp;

	if(SearchPhoneNumber(strPhone, vec))
	{
		vecTemp.reserve(vec.size() + vecPhone.size());

		for(it = vec.begin(); it != vec.end(); it++)
		{
			CSearchPOI poi;
			//ZeroMemory(&poi, sizeof(poi));
			long nVecID = IDToVectorID(it->m_nID);
			poi.pPOI = (CPOIUnit*)&(m_vecPOI[nVecID]);
			//g_bana_log->Print("vecID = %d\n", nVecID);
			poi.bPhoneMatch = TRUE;
			long nDistance = 0;
			poi.pNearPOI = GetNearMainPOI(poi.pPOI, nDistance);
			vecTemp.push_back(make_pair(nVecID, poi));
		}

		for(it2 = vecPhone.begin(); it2 != vecPhone.end(); it2++)
			vecTemp.push_back(*it2);

		vecPhone.swap(vecTemp);
	}

	return vecPhone.size();
}


void CPOIDataNew::GetPhoneDivBody(CString &strPhone, int nDDDLen, CString &strDDD, CString &strBody)
{
	strDDD = strPhone.Left(nDDDLen);
	strBody = strPhone.Right(strPhone.GetLength() - nDDDLen);
}

CString CPOIDataNew::ExtractPhoneNumber(CString strText)
{
#define MIN_PHONE_LENGTH 7
#define MAX_PHONE_LENGTH 11
	char buffer[MAX_PHONE_LENGTH+10];
	int nCount = 0;
	int idx = 0;
	int nLen = strText.GetLength();

	for(int n = 0; n < nLen; n++)
	{
		if(strText.GetAt(n) >= '0' && strText.GetAt(n) <= '9')
		{
			if(idx > MAX_PHONE_LENGTH) 
				idx = 0;
			else
				buffer[idx++] = strText.GetAt(n);
		}
		else if(strText.GetAt(n) == '-')
		{
			continue;
		}
		else
		{
			if(idx >= MIN_PHONE_LENGTH)
			{
				buffer[idx] = 0;
				if(VerifyAvailblePhoneNumber(buffer))
					return buffer;
			}
			idx = 0;
		}
	}

	if(idx >= MIN_PHONE_LENGTH)
	{
		buffer[idx] = 0;
		if(VerifyAvailblePhoneNumber(buffer))
			return buffer;
	}


	return "";
}


BOOL CPOIDataNew::VerifyAvailblePhoneNumber(char *p)
{
	char szDDD[][20] = {"010", "011", "013", "016", "017", 
		"018", "019", "02", "031", "032", 
		"033", "041", "042", "043", "050", 
		"051", "052", "053", "054", "055",
		"061", "062", "063", "064", "070", 
		"080"};

	if(strlen(p) <= 8)
	{
		if(p[0] == '0')
			return FALSE;
		else
			return TRUE;
	}
	else 
	{
		if(p[0] != '0')		
			return FALSE;

		for(int i = 0; i < 26; i++)
		{
			if(strncmp(szDDD[i], p, strlen(szDDD[i])) == 0)
				return TRUE;
		}
	}

	return FALSE;
}


int CPOIDataNew::IDToVectorID(long nPOIID)
{
	POIID_VEC::iterator it = lower_bound(m_vecID.begin(), m_vecID.end(), nPOIID, POIIDIndexCompare());
	if(it != m_vecID.end() && it->nPOIID == nPOIID)
		return it->nVecID;

	return -1;
}

CPOIUnit* CPOIDataNew::NewPOI(UINT nGroupID, CPOIUnit *pDong, long nPosX, long nPosY,
							  CString strName, CString strSubName, long nID)
{
	CPOIUnit *pPOI = new CPOIUnit;
	ZeroMemory(pPOI, sizeof(CPOIUnit));
	pPOI->m_nID = nID;
	pPOI->m_pDong = pDong;
	pPOI->m_nPosX = nPosX;
	pPOI->m_nPosY = nPosY;
	pPOI->m_bDongData = FALSE;
	pPOI->m_nClass = PN_TEMP;
	pPOI->m_nDongID = pDong->m_nID;

	if(strSubName.IsEmpty())
	{
		strncpy(pPOI->m_szName, strName, 58);
		pPOI->m_szSubName[28] = 0;
	}
	else
	{
		strncpy(pPOI->m_szName, strName, 29);
		strncpy(pPOI->m_szSubName, strSubName, 28);
		pPOI->m_szName[29] = 0;
		pPOI->m_szSubName[28] = 0;
		pPOI->CheckSubNamePhone();
	}


	CMkLock lock(&m_csNewPOI);
	m_vecPPOITemp.push_back(make_pair(nGroupID, pPOI));

	return pPOI;
}

CPOIUnit* CPOIDataNew::NewPOI(UINT nGroupID, CPOIUnit *pSrcPOI, CString strName, long nID)
{
	return NewPOI(nGroupID, pSrcPOI->GetDongPOI(), pSrcPOI->GetPosX(), pSrcPOI->GetPosY(),
				strName, "", nID);
}

void CPOIDataNew::DeletePOI(CPOIUnit *pPOI)
{
	CMkLock lock(&m_csNewPOI);

	P_POI_VEC::iterator it;
	for(it = m_vecPPOITemp.begin(); it != m_vecPPOITemp.end(); it++)
	{
		if(it->second == pPOI)
		{
			delete it->second;
			m_vecPPOITemp.erase(it);
			return;
		}
	}
}

void CPOIDataNew::DeletePOIGroup(UINT nGroupID)
{
	CMkLock lock(&m_csNewPOI);

	P_POI_VEC::iterator it;
	for(it = m_vecPPOITemp.begin(); it != m_vecPPOITemp.end();)
	{
		if(it->first == nGroupID)
		{
			//g_bana_log->Print("TEMP DELETE: G%d, %s\n", it->first, it->second->GetPOIName());
			delete it->second;
			it = m_vecPPOITemp.erase(it);
		}
		else
			it++;
	}

	//g_bana_log->Print("DeletePOIGroup(G%d): temp poi counts = %d\n", nGroupID, m_vecPPOITemp.size());
}

void CPOIDataNew::TMtoGPS(long tmx, long tmy, long &gx, long &gy)
{
	m_CoordConv.SetSrcType((GeoEllips)1, (GeoSystem)2);
	m_CoordConv.SetDstType((GeoEllips)1, (GeoSystem)0);

	double dLon = tmx / 1000000.0;
	double dLat = tmy / 1000000.0;
	double dOutLon, dOutLat;
	m_CoordConv.Conv(dLon, dLat, dOutLon, dOutLat);

	gx = (long)(dOutLon * 1000000);
	gy = (long)(dOutLat * 1000000);
}

void CPOIDataNew::ReplaceHeadString(CString &strKeyword, const char *szHead)
{
	if(strKeyword.Find(szHead) == 0)
		strKeyword = strKeyword.Right(strKeyword.GetLength() - strlen(szHead));
}

void CPOIDataNew::TrimKeyword(CString &strKeyword)
{
	strKeyword.MakeUpper();
	CString strKeywordOri = strKeyword;
	int nLen = strKeyword.GetLength();

	char szLeftTrim[] = {'/', ')', ']', '*', ','};
	for(int i = 0; i < sizeof(szLeftTrim); i++)
		strKeyword.Remove(szLeftTrim[i]);

	ReplaceHeadString(strKeyword, "후불");
	ReplaceHeadString(strKeyword, "경유");

	strKeyword.Replace("대기자만", "");
	strKeyword.Replace("대기자", "");
	strKeyword.Replace("테스트", "");
	strKeyword.Replace("TEST", "");
	strKeyword.Replace("잡지마세요", "");

	if(strKeyword.GetLength() == 0)
		return;

	CString strRemove[]  = {"2콜", "3콜", "4콜", "5콜", "6콜"};
	for(int i = 0; i < sizeof(strRemove) / sizeof(CString); i++)
		strKeyword.Replace(strRemove[i], "");

	CString strReplace[]  = 
	{
		"초등학교", "초교",
		"여자중학교", "여중",
		"중학교", "중교",
		"여자고등학교", "여고",
		"외국어고등학교", "외고",
		"고등학교", "고교",
		"@", "아파트",
		"패밀리마트", "훼미리마트",
		"패미리마트", "훼미리마트",
		"에스케이주유소", "SK주유소", 
		"지에스25", "GS25",
		"에스케이텔레콤", "SK텔레콤", 
		"지에스주유소", "GS주유소", 
		"GS칼텍스", "GS주유소", 
		"지엠대우", "GM대우",
		"케이티에프", "KTF",
		"S-OIL", "SOIL", 
		"에스오일", "SOIL",
		"OILBANK", "오일뱅크",
		"오케이마트", "OK마트",
		"비와이씨", "BYC",
		"엘지전자", "LG전자",
		"아이지에이마트", "IGA마트",
		"조이마트", "JOY마트",
		"케이티엔지", "KT&G",
		"쇼매장", "SHOW",
		"로타리", "로터리"
	};


	for(int i = 0; i < sizeof(strReplace) / sizeof(CString); i+=2)
		strKeyword.Replace(strReplace[i], strReplace[i+1]);


	int nPos = strKeyword.Find('.');
	if(nPos >= 2)
		strKeyword = strKeyword.Left(nPos);

	nPos = strKeyword.Find(';');
	if(nPos >= 2)
		strKeyword = strKeyword.Left(nPos);
	
	nPos = strKeyword.Find('A');
	if(nPos <= 3)
		nPos = strKeyword.Find('@');

	if(nPos > 3)
	{
		char szLeft = strKeyword.GetAt(nPos - 1);
		if(szLeft < 'A' || szLeft > 'Z')
		{
			strKeyword.SetAt(nPos, '^');
			strKeyword.Replace("^", "아파트");
		}
	}

	nPos = strKeyword.Find('4');
	if(nPos == strKeyword.GetLength() - 1 && nPos > -1)
	{
		char szLeft = strKeyword.GetAt(nPos - 1);
		if(szLeft < '0' || szLeft > '9')
		{
			strKeyword.SetAt(nPos, '^');
			strKeyword.Replace("^", "사거리");
		}
	}

//	if(strKeywordOri != strKeyword)
//		g_bana_log->Print("keyword: %s -> %s\n", strKeywordOri, strKeyword);
}


UINT CPOIDataNew::WCharToIndex(WCHAR *pWChar)
{
	return *((UINT*)pWChar);
}

void CPOIDataNew::GetLastKeyword(CString &strDongKeyword, CString &strPOIKeyword)
{
	strDongKeyword = m_strLastDongKeyword;
	strPOIKeyword = m_strLastPOIKeyword;
}

void CPOIDataNew::DeletePOIGroup(void *pVoid)
{
	DeletePOIGroup((UINT)pVoid);
} 

void CPOIDataNew::SetHaveSido(CPOIBoundary *pPOIBoundary)
{
	if(m_pHaveSido && m_pHaveSido->IsAutoDelete())
		delete m_pHaveSido;

	m_pHaveSido = pPOIBoundary;
}

CPOIBoundary* CPOIDataNew::GetHaveSido()
{
	return m_pHaveSido;
}

void CPOIDataNew::SetSearchSido(CPOIBoundary *pPOIBoundary)
{
	if(m_pSearchSido && m_pSearchSido->IsAutoDelete())
		delete m_pSearchSido;

	m_pSearchSido = pPOIBoundary;
}

CPOIBoundary* CPOIDataNew::GetSearchSido()
{
	return m_pSearchSido;
}

CPOIUnit* CPOIDataNew::SetCenterSido(CString strSido, CString strSido2, long nSystemCode)
{
	POI_VEC_POINT::iterator it;
	CPOIUnit *pPOISelected = NULL;
    
	strSido.Trim();
	strSido.Remove('2');
	strSido.Remove('3');
	strSido.Remove('4');
	strSido2.Trim();
	strSido2.Remove('2');
	strSido2.Remove('3');
	strSido2.Remove('4');

	if(m_strPreCenterSido == (strSido + "/" + strSido2))
		return m_pPOICenter;
	else
		m_strPreCenterSido = strSido + "/" + strSido2;

	if(!IsDo(strSido))
		GetStdCenterSidoName(strSido, strSido2, nSystemCode);
	else if(strSido == "경남")
		strSido2 = "창원시";

	for(it = m_vecSido.begin(); it != m_vecSido.end(); it++)
	{
		CPOIUnit *pPOI = (*it);

		if(pPOI->GetClass() >= PN_GUGUN)
		{
			if(strSido2.IsEmpty())
			{
				if(strSido == pPOI->GetSido() && pPOI->GetDong().Find(strSido) >= 0)
				{
					pPOISelected = pPOI;
					break;
				}
			}
			else
			{
				if(strSido == pPOI->GetSido() &&
					strSido2 == pPOI->GetGugun1Only())
				{
					pPOISelected = pPOI;
					break;
				}
			}
		}
	}

	if(pPOISelected)
	{
		m_pPOICenter = pPOISelected;
		if(!m_pPOICenterDefault)
			m_pPOICenterDefault = pPOISelected;
	}
	else
	{
		CString strMsg;

		if(m_pPOICenterDefault)
			m_pPOICenter = m_pPOICenterDefault;

		strMsg.Format("해당 중심 POI가 존재하지 않습니다.[%s][%s]", strSido, strSido2);

		if(!m_pPOICenter)
			MessageBox(AfxGetMainWnd()->GetSafeHwnd(), strMsg + "\n", "POI기준설정오류", MB_ICONEXCLAMATION); 
		else
			g_bana_log->Print("%s\n표준위치를 기준으로 합니다.", strMsg);
	}

	return pPOISelected;
}

CString CPOIDataNew::GetCenterSido()
{
	if(m_pPOICenter)
	{
		if(IsDo(m_pPOICenter->GetSido()))
			return m_pPOICenter->GetSido() + " " + m_pPOICenter->GetGugun1Only();
		else
			return m_pPOICenter->GetSido();
	}
	return "";
}

void CPOIDataNew::SetMainSidoDongOnly(BOOL bEnable)
{
	m_bMainSidoDongOnly = bEnable;	
}

CString CPOIDataNew::RemoveCache()
{
	CString strTemp = m_strLastKeyword;
	m_strLastKeyword.Empty();
	return strTemp;

}

void CPOIDataNew::ClearAllData()
{
	m_vecPOI.clear();
	m_vecDong.clear();
	m_vecSido.clear();
	m_vecPartPOI.clear();
	m_vecSearchDong.clear();
	m_vecMain.clear();
	m_vecPhone.clear();
	m_vecID.clear();
	m_vecPPOITemp.clear();
	m_vecStation.clear();
}

BOOL CPOIDataNew::IsDataLoadOK(BOOL bDongOnly)
{
	if(bDongOnly)
	{
		/*
		if(	m_vecDong.size() > 0 &&
			m_vecSido.size() > 0 &&
			m_vecSearchDong.size() > 0)
		*/
		if(!m_vecDong.empty() &&
			!m_vecSido.empty() &&
			!m_vecSearchDong.empty())
		{
			return TRUE;
		}
	}
	else
	{
		/*
		if(m_vecPOI.size() > 0 &&
			m_vecDong.size() > 0 &&
			m_vecSido.size() > 0 &&
			m_vecPartPOI.size() > 0 &&
			m_vecSearchDong.size() > 0)
		*/
		if(!m_vecPOI.empty() &&
			!m_vecDong.empty() &&
			!m_vecSido.empty() &&
			!m_vecPartPOI.empty() &&
			!m_vecSearchDong.empty())
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CPOIDataNew::IsStringDigit(CString strData)
{
	int i = 0;
	for(i = 0; i < strData.GetLength(); i++)
	{
		char s = strData.GetAt(i);
		if((s >= '0' && s <= '9') || s == ' ' || s == '-')
			continue;
		else
			return FALSE;
	}

	return (i > 8);
}

BOOL CPOIDataNew::IsLiPOI(UINT nID)
{
	return (nID >= LI_OFFSET_START && nID <= LI_OFFSET_END);
}

BOOL CPOIDataNew::IsDongPOI(UINT nID, BOOL bIncludeLi)
{
	return (nID < DONG_OFFSET_END) || (bIncludeLi & IsLiPOI(nID));
}

CPOIUnit* CPOIDataNew::GetNullPOI()
{
	if(!m_pNullPOI)
	{	
		m_pNullPOI = new CPOIUnit;
		ZeroMemory(m_pNullPOI, sizeof(CPOIUnit));
		m_pNullPOI->m_bDongData = TRUE;
		m_pNullPOI->m_pMainDong = m_pNullPOI;
		m_pNullPOI->m_pParent = m_pNullPOI;
		m_pNullPOI->m_nPosX = 1;
		m_pNullPOI->m_nPosY = 1;
		strcpy(m_pNullPOI->m_szSido, "NULL");
		strcpy(m_pNullPOI->m_szGugun, "NULL");
		strcpy(m_pNullPOI->m_szGugun2, "NULL");
		strcpy(m_pNullPOI->m_szDong, "NULL");
	}

	return m_pNullPOI;
}

CPOIUnit* CPOIDataNew::GetNullPOI(CPOIUnit *pPOI, BOOL bIfNotExistReturnNullPOI)
{
	return (bIfNotExistReturnNullPOI && !pPOI) ? GetNullPOI() : pPOI;
}

CPOIUnit* CPOIDataNew::GetPOICenter()
{
	return m_pPOICenter;
}

void CPOIDataNew::SetLog(CQLog *pLog)
{
	m_pLog = pLog;
	g_bana_log->Print("POIData: _SECURE_SCL = %d, _HAS_ITERATOR_DEBUGGING = %d\n", _SECURE_SCL, _HAS_ITERATOR_DEBUGGING);
}

void CPOIDataNew::MakePOIPreviousOffset(BOOL bFromFile)
{
	//if(bFromFile && m_vecMain.size() > 0)
	if(bFromFile && !m_vecMain.empty())
	{
		UINT nOldPOIPoint = (UINT)m_vecMain[0].pPOI;
		UINT nNewPOIPoint = (UINT)GetPOI((UINT)m_vecMain[0].nID);
		if(nOldPOIPoint > 0 && nNewPOIPoint > 0)
		{
			m_nPreviousPOIPointSub = nNewPOIPoint - nOldPOIPoint;
			m_bHasPreviousPOIPointSub = TRUE;
		}
	}
}

AFX_INLINE CPOIUnit *CPOIDataNew::GetPOIPreviousOffset(CPOIUnit *pPOI)
{
	return m_bHasPreviousPOIPointSub ? (CPOIUnit*)((long)pPOI + m_nPreviousPOIPointSub) : pPOI;
}

void CPOIDataNew::MakeDongPreviousOffset(BOOL bFromFile)
{
	//if(bFromFile && m_vecDong.size() > 0)
	if(bFromFile && !m_vecDong.empty())
	{
		UINT nOldPOIPoint = (UINT)m_vecNorDong[0].pPOI;
		UINT nNewPOIPoint = (UINT)GetPOI((UINT)m_vecNorDong[0].nID);
		if(nOldPOIPoint > 0 && nNewPOIPoint > 0)
		{
			m_nPreviousDongPointSub = nNewPOIPoint - nOldPOIPoint;
			m_bHasPreviousDongPointSub = TRUE;
		}
	}
}

AFX_INLINE CPOIUnit *CPOIDataNew::GetDongPreviousOffset(CPOIUnit *pPOI)
{
	return m_bHasPreviousDongPointSub ? (CPOIUnit*)((long)pPOI + m_nPreviousDongPointSub) : pPOI;
}


AFX_INLINE CPOIUnit* CPOIDataNew::GetDongPOIFromCache(UINT nID, CPOIUnit *pDefaultPOI)
{
	if(nID >= LI_OFFSET_START && nID <= LI_OFFSET_END)
		nID = nID - LI_OFFSET_START + DONG_OFFSET_END;

	return nID < m_nMaxDongID && m_pDongCache[nID] ? (CPOIUnit*)m_pDongCache[nID] : pDefaultPOI;
}


#define SET_SIDO_IF(x, y, z) if(strSido == x) { strSido = y; strSido2 = z;}
#define SET_SIDO_ELSE_IF(x, y, z) if(strSido == x) { strSido = y; strSido2 = z;}

void CPOIDataNew::GetStdCenterSidoName(CString& strSido, CString& strSido2, long nSystemCode)
{
	if(strSido2.GetLength() > 0)
		return;

	//#ifndef _DAERI
		if(nSystemCode >= 3)
	//#else
	//	if(m_bCapitalArea)
	//#endif
	{
		SET_SIDO_IF("광명", "경기", "광명시"); 
		SET_SIDO_ELSE_IF("구리", "경기", "구리시");
		SET_SIDO_ELSE_IF("이천", "경기", "이천시");
		SET_SIDO_ELSE_IF("파주", "경기", "파주시");
		SET_SIDO_ELSE_IF("군포", "경기", "군포시");
		SET_SIDO_ELSE_IF("김포", "경기", "김포시");
		SET_SIDO_ELSE_IF("남양주", "경기", "남양주시"); 
		SET_SIDO_ELSE_IF("부천", "경기", "부천시");
		SET_SIDO_ELSE_IF("분당", "경기", "성남시");
		SET_SIDO_ELSE_IF("서산", "충남", "서산시");
		SET_SIDO_ELSE_IF("성남", "경기", "성남시");
		SET_SIDO_ELSE_IF("수원", "경기", "수원시");
		SET_SIDO_ELSE_IF("안성", "경기", "안성시");
		SET_SIDO_ELSE_IF("시흥", "경기", "시흥시");
		SET_SIDO_ELSE_IF("아산", "충남", "아산시");
		SET_SIDO_ELSE_IF("안산", "경기", "안산시");
		SET_SIDO_ELSE_IF("안양", "경기", "안양시");
		SET_SIDO_ELSE_IF("여주", "경기", "여주시");
		SET_SIDO_ELSE_IF("오산", "경기",  "오산시");
		SET_SIDO_ELSE_IF("용인", "경기", "용인시");
		SET_SIDO_ELSE_IF("이천", "경기", "이천시");
		SET_SIDO_ELSE_IF("의정부", "경기", "의정부시");
		SET_SIDO_ELSE_IF("일산", "경기", "고양시");
		SET_SIDO_ELSE_IF("천안", "충남", "천안시");
		SET_SIDO_ELSE_IF("파주", "경기", "파주시");
		SET_SIDO_ELSE_IF("평택", "경기", "평택시");
		SET_SIDO_ELSE_IF("포천", "경기", "포천시");
		SET_SIDO_ELSE_IF("광명", "경기", "광명시");
		SET_SIDO_ELSE_IF("하남", "경기", "하남시");
		SET_SIDO_ELSE_IF("화성", "경기", "화성시");
		SET_SIDO_ELSE_IF("광주", "경기", "광주시");
		SET_SIDO_ELSE_IF("연기", "충남", "연기군");
		SET_SIDO_ELSE_IF("춘천", "강원", "춘천시");
		SET_SIDO_ELSE_IF("강릉", "강원", "강릉시");
		SET_SIDO_ELSE_IF("원주", "강원", "원주시");
		SET_SIDO_ELSE_IF("속초", "강원", "속초시");
		SET_SIDO_ELSE_IF("평창", "강원", "평창군");
		SET_SIDO_ELSE_IF("영월", "강원", "영월군");
		SET_SIDO_ELSE_IF("홍성", "충남", "홍성군");
		SET_SIDO_ELSE_IF("공주", "충남", "공주시");
		SET_SIDO_ELSE_IF("익산", "전북", "익산시");
		SET_SIDO_ELSE_IF("전주", "전북", "전주시");
		SET_SIDO_ELSE_IF("창원", "경남", "창원시");
		SET_SIDO_ELSE_IF("진주", "경남", "진주시");
		SET_SIDO_ELSE_IF("부천", "경기", "부천시");
		SET_SIDO_ELSE_IF("안동", "경북", "안동시");
		SET_SIDO_IF("청주", "충북", "청주시");
		SET_SIDO_ELSE_IF("정읍", "전북", "정읍시");

	}
	else 
	{
		SET_SIDO_IF("청주", "충북", "청주시");
		SET_SIDO_ELSE_IF("충주", "충북", "충주시");
		SET_SIDO_ELSE_IF("목포", "전남", "목포시");
		SET_SIDO_ELSE_IF("순천", "전남", "순천시");
		SET_SIDO_ELSE_IF("전주", "전북", "전주시");
		SET_SIDO_ELSE_IF("군산", "전북", "군산시");
		SET_SIDO_ELSE_IF("익산", "전북", "익산시");
		SET_SIDO_ELSE_IF("김제", "전북", "김제시");
		SET_SIDO_ELSE_IF("창원", "경남", "창원시");
		SET_SIDO_ELSE_IF("마산", "경남", "마산시");
		SET_SIDO_ELSE_IF("진해", "경남", "진해시");
		SET_SIDO_ELSE_IF("김해", "경남", "김해시");
		SET_SIDO_ELSE_IF("거제", "경남", "거제시");
		SET_SIDO_ELSE_IF("진주", "경남", "진주시");
		SET_SIDO_ELSE_IF("포항", "경북", "포항시");
		SET_SIDO_ELSE_IF("경주", "경북", "경주시");
		SET_SIDO_ELSE_IF("춘천", "강원", "춘천시");
		SET_SIDO_ELSE_IF("강릉", "강원", "강릉시");
		SET_SIDO_ELSE_IF("원주", "강원", "원주시");
		SET_SIDO_ELSE_IF("속초", "강원", "속초시");
		SET_SIDO_ELSE_IF("정읍", "전북", "정읍시");
		SET_SIDO_ELSE_IF("홍성", "충남", "홍성군");
		SET_SIDO_ELSE_IF("공주", "충남", "공주시");
		SET_SIDO_ELSE_IF("창원", "경남", "창원시");
		SET_SIDO_ELSE_IF("진주", "경남", "진주시");
		SET_SIDO_ELSE_IF("부천", "경기", "부천시");
		SET_SIDO_ELSE_IF("안동", "경북", "안동시");
		SET_SIDO_ELSE_IF("군산", "전북", "군산시");
		SET_SIDO_ELSE_IF("상주", "경북", "상주시");
		SET_SIDO_ELSE_IF("정읍", "전북", "정읍시");
		SET_SIDO_ELSE_IF("광명", "경기", "광명시");
	} 
}

void CPOIDataNew::SetCapitalArea(BOOL bCapitalArea)
{
	m_bCapitalArea = bCapitalArea;

//	if(!m_bCapitalArea)
//	{
		//g_bana_log->Print("change AllowMatchLen\n");
		//for(int i = 0; i < sizeof(nAllowMatchLen) / sizeof(int); i++)
		//	nAllowMatchLen[i] = nAllowMatchLen2[i];
//	}
}

BOOL CPOIDataNew::IsPosUsable(long &nPosX, long &nPosY, BOOL bDontChange, BOOL bWGS84ToBessel)
{
	//도:분:초 -> 초단위
	if(nPosX > 100000000)
	{
		if(!bDontChange)	
		{
			nPosX = nPosX * 0.36;
			nPosY = nPosY * 0.36;
		}

		return FALSE;
	}
	else if(nPosX == 0 || nPosY == 0)
	{
		return FALSE;
	}
	//초단위인데, X/Y가 뒤집어져 있음
	else if(nPosX < 20000000)
	{
		long nPos = nPosX;
		nPosX = nPosY;
		nPosY = nPos;
	}

	return TRUE;
}

void CPOIDataNew::UpdatePOINameForUserPOI()
{
	POI_VEC::iterator it;
	for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
	{
		long nDongID = GetDongPOIFromCache(it->m_nDongID)->GetMainDongID();
		CString strShortDong = GetDongPOIFromCache(nDongID)->GetDong(TRUE);
		int nDongLen = strShortDong.GetLength();
		if(strncmp(strShortDong, it->m_szName, nDongLen) == 0)
			strcpy(it->m_szName, &it->m_szName[nDongLen]);
	}
}

void CPOIDataNew::ClearPOIFile(CString strCity, BOOL bCapitalArea)
{
	CString strHead = bCapitalArea ? "수도권" : strCity;
	strHead += "_";
	DeleteFile(GetModuleFullPath() + DONG_POI_FILE_NAME);
	DeleteFile(GetModuleFullPath() + DONG_PART_POI_FILE_NAME);
	DeleteFile(GetModuleFullPath() + DONG_NOR_FILE_NAME);
	DeleteFile(GetModuleFullPath() + strHead + POI_FILE_NAME);
	DeleteFile(GetModuleFullPath() + strHead + PART_POI_FILE_NAME);
	DeleteFile(GetModuleFullPath() + strHead + POI_MAIN_VEC_NAME);
	DeleteFile(GetModuleFullPath() + strHead + POI_PHONE_VEC_NAME);
	DeleteFile(GetModuleFullPath() + strHead + POI_ID_VEC_NAME);
}

AFX_INLINE BOOL CPOIDataNew::IsCapitalArea()
{
	return m_bCapitalArea;
}

CString CPOIDataNew::GetPlaceUsingType(CString strPOI, CPOIUnit *pPOI, CPOIUnit *pDetailPOI, BOOL bDisplayDong)
{
	CString strDong;

	if(strPOI.IsEmpty())
		strPOI = pPOI->GetPOIName(FALSE);

	if(bDisplayDong)
	{
		CPOIUnit *pDongPOI = pDetailPOI ? pDetailPOI->GetDongPOI() : pPOI->GetDongPOI();
		strDong = pDongPOI->GetDong(FALSE);
		if(strDong.Right(2) == "읍" ||
			strDong.Right(2) == "면")
		{
			if(pDongPOI->IsLiPOI())
				strDong = (m_bPlaceUsingMyunLi ? pDongPOI->GetDong() : pDongPOI->GetGugun1Only())  + pDongPOI->GetLi();
			else
			{
				if(m_bNotPlaceUsingMyunLi)
					strDong = "";
				else
					strDong = pDongPOI->GetGugun1Only() + pDongPOI->GetDong();
			}
		}
		else 
		{
			strDong = pDongPOI->GetDong(TRUE);
		}
	}

	int nPos = strPOI.ReverseFind('(');
	if(nPos > 0)
	{
		int nEndPos = strPOI.Find(')');
		if(nEndPos > 0)
		{
			CString strSubName = strPOI.Mid(nPos, nEndPos - nPos + 1);

			if(strSubName.Find("호선") >= 0)
				strPOI.Replace(strSubName, "");
			else
			{
				CString strRegion = pPOI->GetRegionName();

				strSubName.Replace("(", "");
				strSubName.Replace(")", "");

				if(strRegion.Find(strSubName) >= 0)
					strPOI.Replace(strPOI.Mid(nPos, nEndPos - nPos + 1), "");
			}
		}
	}

	strPOI.Replace("(사거리)", "");
	strPOI.Replace("(교차로)", "");

	return ((strPOI.Find(strDong) != 0) ? strDong : CString("")) + strPOI;
}

void CPOIDataNew::SetPlaceUsingType(BOOL bPlaceUsingMyunLi, BOOL bNotPlaceUsingMyunLi)
{
	m_bNotPlaceUsingMyunLi = bNotPlaceUsingMyunLi;	
	m_bPlaceUsingMyunLi = bPlaceUsingMyunLi;	
}

int CPOIDataNew::GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2)
{
	IsPosUsable(nPosX, nPosY);
	IsPosUsable(nPosX2, nPosY2);

	double dx = (nPosY2 - nPosY) * 0.30918467038935;
	double dy = (nPosX2 - nPosX) * cos((nPosY2 + nPosY) * 0.000000024240661) * 0.30918467038935;
	return sqrt(dx*dx + dy*dy);
}

void CPOIDataNew::SetUseSimpleSearch(BOOL bSimpleSearch)
{
	m_bUseSimpleSearch = bSimpleSearch;
}

void CPOIDataNew::SetSkipSearchPOIIfDongExactlyMatch(BOOL bSkipDong, BOOL bSkipLi)
{
	m_bSkipSearchPOIIfDongExactlyMatch = bSkipDong;
	m_bSkipSearchPOIIfDongExactlyMatchLi = bSkipLi;
}

/*

int CPOIDataNew::LikeSearchPOI(CString strData, POI_SEARCH_VECTOR &vecPOIData, BOOL bOnlyNoneSubName)
{
	POI_DATA_DEPTH_MAP::const_iterator iter;

	for(iter = m_poiName.begin(); iter != m_poiName.end(); iter++)
	{
		static basic_string<char>::size_type notfound = -1;
		basic_string<char>::size_type cur;

		cur	= iter->first.find(strData);

		if(cur != notfound)
		{
			basic_string<char>::size_type sub = iter->first.find("(");

			if(sub != notfound && (cur >= sub || bOnlyNoneSubName))
				continue;

			POI_SEARCH *pPOI = new POI_SEARCH;
			pPOI->pPOI = iter->second->pData;
			pPOI->nCharIndex = (int)cur;
			pPOI->nLength = iter->first.length();
			pPOI->nSidoID = CPOIData::GetMySidoPOI(pPOI->pPOI)->nID;
			//g_bana_log->Print("POI=%s, CharIndex=%d, Length=%d\n", pPOI->pPOI->F1, pPOI->nCharIndex, pPOI->nLength);
			vecPOIData.push_back(pPOI);
		}
	}

	if(m_ci.strCity == "울산" || m_ci.strCity == "제주" || m_ci.strCity == "대구")
	{
		POI_DATA_MAP::iterator it;
		for(it = m_poiDong.begin(); it != m_poiDong.end(); it++)
		{
			if(!strcmp(it->second->szSido, m_ci.strCity) ||
				it->second->nClass == POI_GUGUN ||
				it->second->nClass == POI_SIDO)
			{
				int nCharIndex = CString(it->second->szDong).Find(strData);
				if(nCharIndex >= 0)
				{
					POI_SEARCH *pPOI = new POI_SEARCH;
					pPOI->pPOI = it->second;
					pPOI->nCharIndex = nCharIndex;
					pPOI->nLength = strlen(it->second->szDong);
					pPOI->nSidoID = CPOIData::GetMySidoPOI(pPOI->pPOI)->nID;
					//g_bana_log->Print("dong POI=%s, CharIndex=%d, Length=%d\n", pPOI->pPOI->F1, pPOI->nCharIndex, pPOI->nLength);
					vecPOIData.push_back(pPOI);
				}
			}
		}
	}
	else
	{
		POI_DATA_MAP::iterator it;
		for(it = m_poiDong.begin(); it != m_poiDong.end(); it++)
		{
			if(it->second->nClass == POI_GUGUN ||
				it->second->nClass == POI_SIDO)
			{
				int nCharIndex = CString(it->second->szDong).Find(strData);
				if(nCharIndex >= 0)
				{
					POI_SEARCH *pPOI = new POI_SEARCH;
					pPOI->pPOI = it->second;
					pPOI->nCharIndex = nCharIndex;
					pPOI->nLength = strlen(it->second->szDong);
					pPOI->nSidoID = CPOIData::GetMySidoPOI(pPOI->pPOI)->nID;
					//g_bana_log->Print("dong POI=%s, CharIndex=%d, Length=%d\n", pPOI->pPOI->F1, pPOI->nCharIndex, pPOI->nLength);
					vecPOIData.push_back(pPOI);
				}
			}
		}
	}

	return vecPOIData.size();
}

int CPOIDataNew::LikeSearchCustomPOI(CString strData, POI_VECTOR &vecPOIData, CString &strKeyword, int nSortType, BOOL bDest)
{
	POI_SEARCH_VECTOR vec;
	strKeyword = strData;

	if(LikeSearchPOI(strData, vec, bDest) == 0)
	{
		WCHAR wChar[255];
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strData, -1, wChar, 255);
		int nWLen = wcslen(wChar) - 1;

		while(nWLen > 2)
		{
			char szData[255];
			int nLen = WideCharToMultiByte(CP_ACP, 0, wChar, nWLen, szData, 255, NULL, NULL);
			szData[nLen] = 0;
			strKeyword = szData;
			if(LikeSearchPOI(strKeyword, vec, bDest) > 0)
				break;

			nWLen--;
		}
	}

	//g_bana_log->Print("------%s, %s-------\n", strData, strKeyword);

	if(vec.size() > 0)
	{
		std::sort(vec.begin(), vec.end(), 
			nSortType == 0 ? POI_custom_sort_type0 : POI_custom_sort_type1);

		POI_SEARCH_VECTOR::iterator it;
		for(it = vec.begin(); it != vec.end(); it++)
		{
			POI_DATA *pPOI = (POI_DATA*)((*it)->pPOI);
			vecPOIData.push_back(pPOI);
			delete (*it);
			//g_bana_log->Print("%s, %s\n", pPOI->F1, GetDisplayName(pPOI));
		}
	}

	return vecPOIData.size();
}

POI_DATA* CPOIDataNew::GetMySidoPOI(POI_DATA *pPOI)
{
	POI_DATA *pTemp = pPOI;

	while(pTemp != NULL && pTemp->nClass != POI_SIDO)
	{
		pTemp = pTemp->pParent;
	}

	return pTemp == NULL ? pPOI : pTemp;
}
*/


void CPOIDataNew::AddSpecialLog(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	TCHAR line[8192];
	_vsnprintf(line, 8192, format, ap);

	va_end(ap);

	m_strSpecialLog += CString(line) + "\r\n";
}