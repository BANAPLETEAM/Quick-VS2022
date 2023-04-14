#pragma once


#include "POIUnit.h"
#include "SearchPOI.h"


#ifdef _DEBUG
#define POI_FILE_NAME		"poi_debug.txt"
#define PART_POI_FILE_NAME	"poi_part_debug.txt"
#define POI_MAIN_VEC_NAME	"poi_main_debug.txt"
#define POI_PHONE_VEC_NAME	"poi_phone_debug.txt"
#define POI_ID_VEC_NAME		"poi_id_debug.txt"
#define POI_STATION_VEC_NAME "poi_station_debug.txt"
#else
#define POI_FILE_NAME	"poi.dat"
#define PART_POI_FILE_NAME "poi_pa.dat"
#define POI_MAIN_VEC_NAME	"poi_ma.dat"
#define POI_PHONE_VEC_NAME	"poi_ph.dat"
#define POI_ID_VEC_NAME		"poi_id.dat"
#define POI_STATION_VEC_NAME "poi_st.dat"
#endif

#define DONG_POI_FILE_NAME "poi_d.dat"
#define DONG_PART_POI_FILE_NAME "poi_dp.dat"
#define DONG_NOR_FILE_NAME	"poi_dn.dat"

#define POI_SHOW_COUNT	15
#define POI_INI_FILE_NAME	"POI.INI"


#pragma pack(push)
#pragma pack(1)


typedef vector<CPOIUnit> POI_VEC;
typedef vector<CPOIUnit*> POI_VEC_POINT;
typedef vector<pair<UINT, CPOIUnit*>> P_POI_VEC;
typedef multimap<long, long> POI_CHILD_LIST_MAP;



typedef struct
{
	long nIndex;
	BYTE nPos;
	BYTE nFullLen;
	long nVecID;
} PART_POI_INFO;

typedef vector<PART_POI_INFO> PART_POI_VEC;
typedef PART_POI_VEC::iterator PART_ITER;
typedef pair<PART_ITER, PART_ITER> PART_PAIR_ITER;	



typedef map<long, CSearchPOI> SEARCH_POI_MAP;
typedef pair<long, CSearchPOI> SEARCH_POI_PAIR;
typedef vector<SEARCH_POI_PAIR> SEARCH_POI_VEC;


typedef struct
{
	WCHAR wszKeyword[20];
	long nVecID;
	int nType;
} SEARCH_DONG;

typedef vector<SEARCH_DONG> SEARCH_DONG_VEC;
typedef SEARCH_DONG_VEC::iterator DONG_ITER;
typedef pair<DONG_ITER, DONG_ITER> DONG_PAIR_ITER;	


typedef struct  
{
	long nNorPosX;		//normalize posX;
	long nNorPosY;		//normalize posY;
	CPOIUnit *pPOI;
	long nID;			//point offset 계산을 위해서
} NORMALIZE_POI;

typedef vector<NORMALIZE_POI> NORMALIZE_POI_VEC;
typedef NORMALIZE_POI_VEC::iterator NORMALIZE_POI_ITER;
typedef pair<NORMALIZE_POI_ITER, NORMALIZE_POI_ITER> NORMALIZE_POI_PAIR_ITER;	


typedef struct
{
	UINT nPhone;
	CPOIUnit *pPOI;
} PHONE_INDEX;

typedef vector<PHONE_INDEX> PHONE_INDEX_VEC;
typedef PHONE_INDEX_VEC::iterator PHONE_INDEX_ITER;
typedef pair<PHONE_INDEX_ITER, PHONE_INDEX_ITER> PHONE_INDEX_PAIR_ITER;	


typedef struct
{
	long nVecID;
	long nPOIID;
} POIID_INDEX;


typedef vector<POIID_INDEX> POIID_VEC;

class CPlaceInfo
{
public:
	CPlaceInfo()
	{
		m_pPOI = NULL;
		m_pDetailPOI = NULL;
		m_pBasePOI = NULL;
	}

	void SetPlace(CPOIUnit *pPOI, CPOIUnit *pDetailPOI, CPOIUnit *pBasePOI = NULL)
	{
		m_pPOI = pPOI;
		m_pDetailPOI = pDetailPOI;
		m_pBasePOI = pBasePOI;
	}

	CPOIUnit *m_pPOI;
	CPOIUnit *m_pDetailPOI;
	CPOIUnit *m_pBasePOI;
};


typedef map<long, double> DONG_MACTH_POINT;


#pragma pack(pop)