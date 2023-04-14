#pragma once


#include "AfxStr.h"
#include "POIDataDef.h"
#include "SearchPOI.h"
#include "GeoCoordConv.h"

class CQLog;
class CPOIBoundary;

class AFX_EXT_CLASS CPOIDataNew
{
	friend class CMakePOIData;

public:
	CPOIDataNew(void);
	~CPOIDataNew(void);

public:
	POI_VEC m_vecPOI;
	POI_VEC m_vecDong;
	POI_VEC_POINT m_vecSido;
	PART_POI_VEC m_vecPartPOI;
	POI_CHILD_LIST_MAP m_mapChildList;
	SEARCH_DONG_VEC m_vecSearchDong;
	NORMALIZE_POI_VEC m_vecMain;
	NORMALIZE_POI_VEC m_vecNorDong;
	NORMALIZE_POI_VEC m_vecStation;
	PHONE_INDEX_VEC m_vecPhone;
	POIID_VEC m_vecID;
	P_POI_VEC m_vecPPOITemp;
	static CGeoCoordConv m_CoordConv;
	static CQLog *m_pLog;
	CPOIBoundary* m_pHaveSido;
	CPOIBoundary* m_pSearchSido;
	CPOIUnit* m_pPOICenter;
	CPOIUnit* m_pPOICenterDefault;
	DWORD* m_pDongCache;

	static CString GetModuleFullPath();
	static LPWSTR A2U(LPCSTR lpData);
	static void A2U2(LPCSTR lpData, LPWSTR lpOut, int nBufferLen);
	static LPSTR U2A(LPWSTR lpData);
	static void U2A2(LPWSTR lpData, LPSTR lpOut, int nBufferLen);
	static UINT LenToPos(UINT nLen);
	static CString PosToString(USHORT nPos);
	static void TMtoGPS(long tmx, long tmy, long &gx, long &gy);
	static BOOL IsDo(CString strSido);
	static BOOL IsPosUsable(long &nPosX, long &nPosY, BOOL bDontChange = FALSE, BOOL bWGS84ToBessel = FALSE);
	static int GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2);

	template<typename MyVector, typename T>
	void EncVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	void DecVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	BOOL SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE);

	template<typename MyVector, typename T>
	BOOL LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE, long nAssignFreeSpaceRate = 0);

	BOOL SavePOI(CString strFile = POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadPOI(CString strFile = POI_FILE_NAME, BOOL bDefaultPath = TRUE, long nAssignFreeSpaceRate = 0);
	BOOL SavePartPOI(CString strFile = PART_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadPartPOI(CString strFile = PART_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL SaveDongPOI(CString strFile = DONG_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadDongPOI(CString strFile = DONG_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL SavePartDongPOI(CString strFile = DONG_PART_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadPartDongPOI(CString strFile = DONG_PART_POI_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL SaveMainVec(CString strFile = POI_MAIN_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadMainVec(CString strFile = POI_MAIN_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL SaveStationVec(CString strFile = POI_STATION_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadStationVec(CString strFile = POI_STATION_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL SavePhoneVec(CString strFile = POI_PHONE_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadPhoneVec(CString strFile = POI_PHONE_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL SaveIDVec(CString strFile = POI_ID_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadIDVec(CString strFile = POI_ID_VEC_NAME, BOOL bDefaultPath = TRUE);
	BOOL SaveNorDongVec(CString strFile = DONG_NOR_FILE_NAME, BOOL bDefaultPath = TRUE);
	BOOL LoadNorDongVec(CString strFile = DONG_NOR_FILE_NAME, BOOL bDefaultPath = TRUE);


	void MakePartPOIVector();
	void MakeDongVector();
	BOOL MakeDongCacheArray();
	void SortPOIVector(POI_VEC &vec);
	BOOL UpdateDongHasPOI(BOOL bFromFile = FALSE);
	void UpdatePOIHasPOI(CString strRegionName, BOOL bFromFile = FALSE);
	void CheckDongRelation(SEARCH_POI_MAP &mapPOI, SEARCH_POI_MAP &mapDong, BOOL bDongSepQuery = FALSE);
	void CheckPOIRelation(SEARCH_POI_MAP &mapPOI);
	void CheckPOIRelationSeparate(SEARCH_POI_MAP &mapPOI);

	int SearchPOI(CString strKeyword, POI_VEC &vecPOI, int nShowCount = POI_SHOW_COUNT);
	int SearchPOI(SEARCH_POI_MAP &mapDong_IN, CString strKeyword, POI_VEC &vecPOI, 
				int nShowCount = POI_SHOW_COUNT,  BOOL bDongSepQuery = FALSE,
				int nPOISepQuery = 0);
	int SearchPOI(SEARCH_POI_MAP &mapDong_IN, CString strKeyword, SEARCH_POI_VEC &vecPOI, 
				int nShowCount = POI_SHOW_COUNT, BOOL bDongSepQuery = FALSE, 
				int nPOISepQuery = 0);
	int SearchDong(CString strKeyword, POI_VEC &vecDong, SEARCH_POI_MAP &m, int nShowCount = POI_SHOW_COUNT);
	int SearchDong(CString strKeyword, SEARCH_POI_VEC &vecDong, SEARCH_POI_MAP &m, BOOL bOnlyFullNameQuery = FALSE);
	int SearchDong(CString strKeyword, POI_VEC_POINT &vecDong, int nShowCount = POI_SHOW_COUNT);
	CPOIUnit* SearchDong(CString strKeyword);
	int SearchPOIWithDong(CString strKeyword, SEARCH_POI_VEC &vecPOI, SEARCH_POI_VEC &vecDong, 
							BOOL bSearchPhone = TRUE, BOOL bOnlySearchPhone = FALSE, 
							BOOL bStartPlace = TRUE);
	int SearchPOIWithDong(CString strKeyword, POI_VEC &vecPOI, POI_VEC &vecDong, 
							int nShowCount = POI_SHOW_COUNT, BOOL bSearchPhone = TRUE);
	int SearchPhoneNumber(CString strPhone, POI_VEC &vecPhone);
	int SearchPhoneNumber(CString strPhone, SEARCH_POI_VEC &vecPhone);

	CPOIUnit* GetNormalPOI(UINT nID, CPOIUnit *pDefaultPOI = NULL, BOOL bIfNotExistReturnNullPOI = TRUE);
	CPOIUnit* GetDongPOI(UINT nID, CPOIUnit *pDefaultPOI = NULL, BOOL bIfNotExistReturnNullPOI = TRUE);
	CPOIUnit* GetPOI(UINT nID, CPOIUnit *pDefaultPOI = NULL, BOOL bIfNotExistReturnNullPOI = TRUE);
	void GetLastKeyword(CString &strDongKeyword, CString &strPOIKeyword);

	template<typename T>
	CPOIUnit *GetNorNearPOI(T &t, CPOIUnit *pPOI, long &nDistance);
	template<typename T>
	CPOIUnit* GetNorNearPOI(T &t, long nPosX, long nPosY, long &nMinDistance);
	CPOIUnit* GetNearMainPOI(CPOIUnit *pPOI, long &nDistance);
	CPOIUnit* GetNearMainPOI(CPOIUnit *pPOI);
	CPOIUnit* GetNearMainPOI(long nPosX, long nPosY, long &nMinDistance);
	CPOIUnit* GetNearDongPOI(CPOIUnit *pPOI, long &nDistance);
	CPOIUnit* GetNearDongPOI(CPOIUnit *pPOI);
	CPOIUnit* GetNearDongPOI(long nPosX, long nPosY, long &nMinDistance);
	CPOIUnit* GetNearStationPOI(CPOIUnit *pPOI, long& nMinDistance);
	CPOIUnit* GetNearStationPOI(CPOIUnit *pPOI);
	CPOIUnit* GetNearStationPOI(long nPosX, long nPosY, long& nMinDistance);

	CPOIBoundary *GetHaveSido();
	CPOIBoundary *GetSearchSido();
	CString GetCenterSido();
	CPOIUnit* GetNullPOI();
	CPOIUnit* GetNullPOI(CPOIUnit *pPOI, BOOL bIfNotExistReturnNullPOI);
	CPOIUnit* GetPOICenter();

	int IDToVectorID(long nPOIID);
	CPOIUnit* NewPOI(UINT nGroupID, CPOIUnit *pDong, long nPosX, long nPosY,
			CString strName = "", CString strSubName = "", long nID = 0);
	CPOIUnit* NewPOI(UINT nGroupID, CPOIUnit *pSrcPOI, CString strName, long nID = 0);

	void DeletePOI(CPOIUnit *pPOI);
	void DeletePOIGroup(UINT nGroupID);
	void DeletePOIGroup(void *pVoid);
	void SetHaveSido(CPOIBoundary *pPOIBoundary);
	void SetSearchSido(CPOIBoundary *pPOIBoundary);
	CPOIUnit* SetCenterSido(CString strSido, CString strSido2 = "", long nSystemCode = 3);
	void SetMainSidoDongOnly(BOOL bEnable);
	CString RemoveCache();
	void ClearAllData();

	BOOL IsDataLoadOK(BOOL bDongOnly = FALSE);
	BOOL IsLiPOI(UINT nID);
	BOOL IsDongPOI(UINT nID, BOOL bIncludeLi = TRUE);
	void SetLog(CQLog *pLog);
	void SetCapitalArea(BOOL bCapitalArea);
	void UpdatePOINameForUserPOI();
	void ClearPOIFile(CString strCity, BOOL bCapitalArea);
	BOOL IsCapitalArea();

	CString AddressExceptionReplace(CString &strKeyword);
	CString AddressToShortName(CString &strKeyword);
	CString AddressToLongName(CString &strKeyword);
	CString GetPlaceUsingType(CString strPOI, CPOIUnit *pPOI, CPOIUnit *pDetailPOI, BOOL bDisplayDong);
	CPOIUnit* GetDongPOIFromCache(UINT nID, CPOIUnit *pDefaultPOI = NULL);
	void SetUseSimpleSearch(BOOL bSimpleSearch);
	CString GetSpecialLog() { return m_strSpecialLog; }
	void AddSpecialLog(const char* format, ...);
	void SetCompareDongPriority(BOOL bDongPriority) { m_bDongPriority = bDongPriority; }
	BOOL IsValidDongID(UINT nID) { return nID >= 0 && nID < m_nMaxDongID; } 
	void SetPlaceUsingType(BOOL bPlaceUsingTypeMyun, BOOL bNotPlaceUsingTypeMyun);
	void SetSkipSearchPOIIfDongExactlyMatch(BOOL bSkipDong, BOOL bSkipLi);
	void SetHasStationPOI(BOOL bHasStationPOI) { m_bHasStationPOI = bHasStationPOI;}

	POI_VEC *GetDongVec() { return &m_vecDong;}

protected:
	CString m_strLastDongKeyword;
	CString m_strLastPOIKeyword;
	CString m_strLastKeyword;
	BOOL m_bMainSidoDongOnly;
	CPOIUnit *m_pNullPOI;
	BOOL m_bHasPreviousPOIPointSub;
	long m_nPreviousPOIPointSub;
	BOOL m_bHasPreviousDongPointSub;
	long m_nPreviousDongPointSub;
	long m_nMaxDongID;
	BOOL m_bCapitalArea;
	CCriticalSection m_csNewPOI;
	BOOL m_bUseSimpleSearch;
	CString m_strSpecialLog;
	BOOL m_bDongPriority;
	BOOL m_bPlaceUsingMyunLi;
	BOOL m_bNotPlaceUsingMyunLi;
	BOOL m_bSkipSearchPOIIfDongExactlyMatch;
	BOOL m_bSkipSearchPOIIfDongExactlyMatchLi;
	CString m_strPreCenterSido;
	BOOL m_bHasStationPOI;

	int SearchPartPOI(WCHAR *pWChar, PART_PAIR_ITER &itPair);
	int SearchPartDong(WCHAR *pWChar, DONG_PAIR_ITER &itPair);

	void MakeDongVectorException(CPOIUnit &poi, long nVecID);
	void MakeDongVectorSub(long nVecID, CStringW strDong, int nType);
	BOOL InsertSearchPOI(WCHAR *pWChar, int nLen, SEARCH_POI_MAP &m, 
		PART_PAIR_ITER &itPair, BOOL bIfInsertSkip, BOOL bPOISepSecond = FALSE);
	void UpdateDongMatchTypeToPOI(SEARCH_POI_VEC &vecDong, SEARCH_POI_VEC &vecPOI);
	void DeleteNotMainSidoDong(SEARCH_POI_VEC &vecPOI);

	BOOL CheckKeywordSpace(CString &strKeyword, CString &strDong, CString &strPOI);
	void CheckDongRelationComparePOI(CSearchPOI &poi, const CSearchPOI &dong, BOOL bDongSepQuery);
	int IsFrontMatch(const USHORT &nPos);
	BOOL IsXORMatch(const USHORT &nPos, const USHORT &nPos2);

	void GetPhoneDivBody(CString &strPhone, int nDDDLen, CString &strDDD, CString &strBody);
	CString ExtractPhoneNumber(CString strText);
	BOOL VerifyAvailblePhoneNumber(char *pBuffer);
	void TrimKeyword(CString &strKeyword);
	BOOL IsStringDigit(CString strData);
	UINT WCharToIndex(WCHAR *pWChar);
	void MakeDongPreviousOffset(BOOL bFromFile);
	CPOIUnit* GetDongPreviousOffset(CPOIUnit *pPOIDong);
	void MakePOIPreviousOffset(BOOL bFromFile);
	CPOIUnit* GetPOIPreviousOffset(CPOIUnit *pPOI);
	void GetStdCenterSidoName(CString& strSido, CString& strSido2, long nSystemCode);
	void MakePOIAdditionalValue(SEARCH_POI_VEC &v, CString &strKeyword);
	void MakePOIDongAvantage(SEARCH_POI_VEC &v);
	long GetMaxMatchDongSize(SEARCH_POI_MAP &mapDong);
	void ReplaceHeadString(CString &strKeyword, const char *szHead);
	void RemoveNearSimilarPOI(SEARCH_POI_VEC &v);
	long GetMaxID();
};

