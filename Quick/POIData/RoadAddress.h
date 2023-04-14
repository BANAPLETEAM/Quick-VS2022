#pragma once


#include "POIDataDef.h"

typedef struct 
{
	CHAR m_szName[21];
	BYTE m_bUsingAlone;
	USHORT m_nID;
} ROAD_NAME;


typedef struct 
{
	CHAR m_szName[14];
	USHORT m_nID;
} STREET_NAME;

class CRoadAddressData
{
public:
	UINT m_nDongID;
	UINT m_nPosX;
	UINT m_nPosY;
	CString m_strBuildingName;
	USHORT m_nBuildingNo1;
	USHORT m_nBuildingNo2;

	CString GetDisplayName(CRoadAddressData &rdata, CString &strRoadStreetName)
	{
		CString strTemp;
		if(m_nBuildingNo2 > 0)
			strTemp.Format("%s %d-%d",strRoadStreetName, m_nBuildingNo1, m_nBuildingNo2);
		else
			strTemp.Format("%s %d", strRoadStreetName, m_nBuildingNo1);

		if(m_strBuildingName.GetLength() > 0)
			strTemp += " " + m_strBuildingName;

		return strTemp;
	}


};

class CRoadAddressKey
{
public:
	CRoadAddressKey(USHORT nRoadID, USHORT nStreetID, USHORT nBuildingNo1, USHORT nBuildingNo2)
	{
		m_nRoadID = nRoadID;
		m_nStreetID = nStreetID;
		m_nBuildingNo1 = nBuildingNo1;
		m_nBuildingNo2 = nBuildingNo2;
	};

	USHORT m_nRoadID;
	USHORT m_nStreetID;
	USHORT m_nBuildingNo1;
	USHORT m_nBuildingNo2;

	bool operator<(const CRoadAddressKey& other) const
	{
		if(m_nRoadID < other.m_nRoadID) return TRUE;
		if(m_nRoadID > other.m_nRoadID) return FALSE;

		if(m_nStreetID < other.m_nStreetID) return TRUE;
		if(m_nStreetID > other.m_nStreetID) return FALSE;

		if(m_nBuildingNo1 < other.m_nBuildingNo1) return TRUE;
		if(m_nBuildingNo1 > other.m_nBuildingNo1) return FALSE;


		return m_nBuildingNo2 < other.m_nBuildingNo2;
	}

	bool operator!=(const CRoadAddressKey& other) const
	{
		return	m_nRoadID != other.m_nRoadID ||
			m_nStreetID != other.m_nStreetID ||
			m_nBuildingNo1 != other.m_nBuildingNo1 ||
			m_nBuildingNo2 != other.m_nBuildingNo2;
	}
};



class CRiderChargeKey
{
public:
	CRiderChargeKey(UINT &_nCompany, UINT &_nRNo, long &_nCharge)
	{
		nCompany = _nCompany;
		nRNo = _nRNo;
		nCharge = _nCharge;
	}

	UINT nCompany;
	UINT nRNo;
	long nCharge;

public:
	bool operator<(const CRiderChargeKey& other) const
	{
		if(nCompany < other.nCompany) return TRUE;
		if(nCompany > other.nCompany) return FALSE;

		if(nRNo < other.nRNo) return TRUE;
		if(nRNo > other.nRNo) return FALSE;

		return nCharge < other.nCharge;
	}
};



typedef multimap<CRoadAddressKey, CRoadAddressData> CRoadAddressCacheMap;

class CRoadAddress
{
public:
	CRoadAddress(CPOIDataNew *pPOIData);
	~CRoadAddress();

	void AutoLoad(CMkDatabase *pMkDb);
	BOOL SearchRoadAddress(CString strText, SEARCH_POI_VEC &vecPOI);

protected:
	BOOL SearchRoadAddress(CString &strText, CString strPart, UINT nEndPos);
	BOOL SearchRoadAddressDB(CRoadAddressKey &rkey);
	void SearchSubDigit(CString &strText, CString &strPreDigit, CString &strDigit);
	CString GetDisplayName(CRoadAddressData &rdata, CPOIUnit *pPOI);
	void InsertSearchPOI(CRoadAddressData &rdata);
	BOOL LoadFromFile();
	void LoadFromDB();
	BOOL SaveToFile();

	template<typename MyVector, typename T>
	void EncVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	void DecVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	BOOL SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE);

	template<typename MyVector, typename T>
	BOOL LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE, long nAssignFreeSpaceRate = 0);


public:
	static vector<ROAD_NAME> m_vecRoadName;
	static vector<STREET_NAME> m_vecStreetName;
	static CRoadAddressCacheMap m_mapRoadAddressCache;
	static CMkDatabase *m_pMkDb;

protected:
	CPOIDataNew *m_pPOIData;
	SEARCH_POI_VEC *m_pvecPOI;
	CString m_strRoadStreetName;

};





class CRoadNameOnlyCompare
{
public:
	bool operator() (const ROAD_NAME& road1, const ROAD_NAME& road2) const
	{
		return KeyLess(road1.m_szName, road2.m_szName);
	}

	bool operator() (const ROAD_NAME& road1, const char *pszName) const
	{
		return KeyLess(road1.m_szName, pszName);
	}

	bool operator() (const char *pszName, const ROAD_NAME& road2) const
	{
		return KeyLess(pszName, road2.m_szName);
	}

private:
	bool KeyLess(const char *pszName1, const char *pszName2) const
	{
		return strcmp(pszName1, pszName2) < 0;
	}
};


class CStreetNameOnlyCompare
{
public:
	bool operator() (const STREET_NAME& road1, const STREET_NAME& road2) const
	{
		return KeyLess(road1.m_szName, road2.m_szName);
	}

	bool operator() (const STREET_NAME& road1, const char *pszName) const
	{
		return KeyLess(road1.m_szName, pszName);
	}

	bool operator() (const char *pszName, const STREET_NAME& road2) const
	{
		return KeyLess(pszName, road2.m_szName);
	}

private:
	bool KeyLess(const char *pszName1, const char *pszName2) const
	{
		return strcmp(pszName1, pszName2) < 0;
	}
};

