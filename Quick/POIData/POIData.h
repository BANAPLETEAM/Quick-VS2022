#pragma once


#include "POIDataNew.h"


#define FNAME_COUNT	5
#define CNAME_COUNT 4
#define MAX_CENTER_COUNT	10

typedef struct _poi_data {
	long nID;

	//char C1[11];
	char C1[21];

	union {
		struct {
			char F1[21];			//szSido
			char F2[15];			//szGugun
			char F3[15];			//szGugun2
			char F4[15];			//szDong
			char F5[15];			//szBaseDong
		};

		struct {
			char szDong[21];		//szDong
			char szSido[15];		//szSido
			char szGugun[15];		//szGugun
			char szGugun2[15];		//szGugun2
			//char szBaseDong[21];	//szBaseDong
		};
	};

	long nFCnt;
	long nMainDongID;
	long nClass;
	long nUID;
	double dPosY;
	double dPosX;
	double dKMFromCenter;
	long nBoundaryLevel;
	BOOL bDongData;
	BOOL bHide;
	_poi_data *pDong;
	_poi_data *pParent;
} POI_DATA;



typedef struct {
	POI_DATA *pPOI;
	long nMatchPoint;

	BOOL bDongMatch;
	long nDongMatchPosition;

	union {
		long nDongMatchWordSize;
		long nFMatchWordSize;
	};

	BOOL bValidFMatch;
	BOOL bFMatch[FNAME_COUNT];
	BOOL bValidCMatch;
	long nCMatchWordSize;
	BOOL bCMatch[CNAME_COUNT];
	long nMatchWordRate;
	short int nMatchRate;

} POI_MATCH_DATA;


typedef struct {
	POI_DATA *pData;
	int nDepth;
} POI_DATA_DEPTH;


typedef struct {
	POI_DATA *pPOI;
	int bFullMatch;
	int nPos;
	int nLength;
	int nFullMatchLength;
	int nFullMatchPos;
	BOOL bSidoMatch;
	BOOL bGugunMatch;
	int nMP;
} POI_DONG_SEARCH;



typedef multimap<string, POI_DATA*> POI_DATA_MAP;
typedef multimap<string, POI_DATA_DEPTH*> POI_DATA_DEPTH_MAP;
typedef map<long, POI_DATA*> POI_DATA_ID_MAP;
typedef vector<POI_DATA*> POI_VECTOR;
typedef map<POI_DATA*,POI_MATCH_DATA*> POI_MATCH_MAP;
typedef vector<POI_MATCH_DATA*> POI_MATCH_VECTOR;
typedef map<string, string> POI_LARGE_DATA;
typedef map<long, long> POI_DUAL_MODE_DONG_MAP;

class CPOIData
{
public:
	CPOIData(void);
	~CPOIData(void);

public:
	void Insert(POI_DATA *pPOI, long nID = 0);		//콜센터도시위치를 내부에 가지고 있는 값으로 거리계산해서 필터링함
	void Insert2(POI_DATA *pPOI);					//콜센터도시위치를 외부에서 가지고 있고 외부에서 필터링해서 데이터만 넘김
	void Insert3(POI_DATA *pPOI);					//바운데리/거리 계산을 하지 않고, 데이터만 추가함
	void InsertDong(POI_DATA *pPOI);				//동데이터 입력용

	bool LikeSearch(CString strWord, POI_MATCH_VECTOR &poi);
	bool LikeSearchOld(CString strWord, POI_MATCH_VECTOR &poi);

	POI_DATA* FindDataFromID(long nID);
	long GetUniqueID(POI_DATA *pPOI);
	void SetCenterPos(long x, long y, long nID = 0);
	static double GetDistanceKMeter(double dPosX1, double dPosY1, double dPosX2, double dPosY2);
	double GetDistanceKMeter(double dPosX1, double dPosY1, long nID = 0);
	void GetDisplayName(POI_DATA *pPOI, CString &strDisplayName);
	CString GetDisplayName(POI_DATA *pPOI);
	CString GetDisplayName(long nID);
	void GetDisplayNameReverse(POI_DATA *pPOI, CString &strDisplayName);
	CString GetDisplayNameReverse(POI_DATA *pPOI);
	CString GetDisplayNameReverse(long nID);
	void GetGugunName(POI_DATA *pPOI, CString &strName);
	CString GetGugunName(long nID);
	void GetDongName(POI_DATA *pPOI, CString &strName);
	CString GetDongName(long nID);
	void GetGugunSidoName(POI_DATA *pPOI, CString &strName);
	CString GetGugunSidoName(long nID);
	void GetSidoName(POI_DATA *pPOI, CString &strName);
	CString GetSidoName(long nID);


	CString MakeGugunName(CString strGugun1, CString strGugun2);
	void ReplacePeseudoWord(CString &strWord);
	void ReplaceShortWord(CString &strWord, CString strShort, CString strReplace, BOOL bCheckAlpha = FALSE, BOOL bNumeric = FALSE);

	BOOL SearchDongData(CString &strWord, char *szData, POI_MATCH_MAP &poiMatchMap);
	BOOL SearchDongDataNew(CString &strWord, POI_MATCH_MAP &poiMatchMap, CPtrArray &arrayDong, CUIntArray &arrayMatchEndPos);


	BOOL SearchNameData(CString &strWord, char *szData, POI_MATCH_MAP &poiMatchMap);

	void MakeJoinPOINameToDong();
	void MakeDongParent();
	CString MakeFullName(POI_DATA *pPOI);
	void DeleteFromID(long ID);

	POI_DATA_MAP* GetPoiDongMap()
	{ return &m_poiDong; }

	POI_DATA_MAP* GetPoiDongNearMap()
	{ return &m_poiDongNear; }

	int GetDongParentID(int nDongID);
	void SetMatchPassRate(long nRate)
	{ m_nMatchPassRate = nRate; }

	BOOL CheckIncludeSpace(CString& strData, CString& strDong, POI_DUAL_MODE_DONG_MAP& poiHasDong);
	POI_DATA* LikeSearchDongFor114(CString strLongName, CString &strRemainName, BOOL &bSan);
	CString GetFullName(POI_DATA *pPOI);

protected:
	POI_DATA_DEPTH_MAP m_poiName;
	POI_DATA_MAP m_poiCName1;	///POIName에서 CNAME에 해당하는 데이터만 추가함(CNAME:체인점인 경우에 브랜치명 or 체인종류)
	POI_DATA_MAP m_poiDong;		////POIName에서 '동', '읍', '면' 글자를 제외하고 추가함
	POI_DATA_MAP m_poiDongNear;	////POIName에서 '동', '읍', '면' 글자를 제외하고 추가함, 중심으로 가까운거리에 있는것만
	POI_DATA_ID_MAP m_poiDongID;
	POI_LARGE_DATA m_poiLargeData;
	POI_DATA_MAP m_poiDongSearch;

	double m_dCenterPosX[MAX_CENTER_COUNT];
	double m_dCenterPosY[MAX_CENTER_COUNT];

	long m_nMatchPassRate;

};




