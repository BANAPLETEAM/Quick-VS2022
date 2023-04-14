#pragma once

#include "AfxStr.h"


#pragma pack(push)
#pragma pack(1)

enum { PN_SAME_NAME_DONG = 3, PN_GUGUN = 5, PN_SIDO = 10, PN_LI = 20};
enum { PN_NORMAL = 0, PN_MOBILE = 1, PN_TEMP = 2, PN_STATION = 3};

#define NEAR_MAX_POS_DONG			14400
#define NEAR_MAX_POS_POI			1800 
#define VERY_NEAR_MAX_POS			500


class AFX_EXT_CLASS CPOIUnit		//멤버변수 추가금지(메모리용량늘어남)
{
public:
	CPOIUnit(void);
	~CPOIUnit(void);

public:
	UINT m_nID;	//POI인 경우에 POI_ID, DONG인 경우에 DONG_ID
	bool m_bDongData;	//TRUE: 동데이터, FALSE: POI데이터

	union {
		struct {
			bool m_bHasPhone;			//POI인 경우에만 유효함
			char m_szName[30];			//POI인 경우에 명칭, DONG인 경우에 SIDO
			union
			{
				char m_szSubName[29];	//POI인 경우에만 유효함
				struct {
					char m_szDDD[5];	//POI인 경우에만 유효함
					char m_szPhone[10];	//POI인 경우에만 유효함
					char m_szRFU[14];	//POI인 경우에만 유효함
				};
			};
	
			CPOIUnit *m_pDong;		//POI인 경우만 동POI
			UINT m_nDongID;			//POI인 경우만 동ID
			BYTE m_nPriority;		//POI인 경우만 검색 우선순위
			BYTE m_nClass;	
		};

		struct {
			bool m_bHasChild;			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			char m_szSido[5];			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			char m_szGugun[11];			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			char m_szGugun2[11];		//DONG데이터인 경우만 유효함, POI는 pDong 참조
			char m_szDong[12];			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			char m_szLi[11];			//DONG테이터인 경우만 유효함, POI는 pDong 참조
			CPOIUnit *m_pMainDong;		//DONG데이터인 경우만 유효함, POI는 pDong 참조
			CPOIUnit *m_pParent;		//DONG데이터인 경우만 유효함, POI는 pDong 참조
			USHORT m_nParentID;			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			USHORT m_nMainDongID;		//DONG데이터인 경우만 유효함, POI는 pDong 참조
			BYTE m_bTopIsDO;			//DONG데이터인 경우만 유효함, POI는 pDong 참조
			BYTE m_nClass;
		};
	};

	long m_nPosX;						//WGS84 Coordinator의 경도, LONGITUDE
	long m_nPosY;						//WGS84 Coordinator의 위도, LATTITUDE

public:
	void SetPOI(char *szName, char *szSubName, char *szPhone);
	void SetPOI(char *szSido, char *szGugun, char *szGugun2, char *szDong);
	void SetPos(long nPosX, long nPosY);
	void SetChildUnit(CPOIUnit *pDong, CPOIUnit *pParent);
	void SetPOIType(BOOL bDongData);
	CString GetPhoneNumber(BOOL bNoneDash = FALSE, BOOL bHasBracket = FALSE);
	UINT GetDongID(BOOL bIfLIThenReturnDongID = FALSE);
	UINT GetMainDongID();
	CPOIUnit* GetDongPOI(BOOL bMainDong = FALSE);
	BOOL IsValidGugun2();

	int IsNearPOI(CPOIUnit *pPOI, int nMaxMeter = 2000, int nFilterLevel = NEAR_MAX_POS_DONG);
	int IsVeryNearPOI(CPOIUnit *pPOI, int nMaxMeter = 100);
	int GetDistanceMeter(CPOIUnit *pPOI);
	int GetDistanceMeter(long nPosX, long nPosY);	//초단위
	int GetDistanceMeterDeMiSe(long nPosX, long nPosY); //도분초단위
	int GetDistanceMeterLevel(CPOIUnit *pPOI, long nLevelMeter = 7000);

	BOOL IsSameDong(CPOIUnit *pPOI, BOOL bMainDongAlsoSame = TRUE);
	void GetNormalizePos(long &nPosX, long &nPosY);
	BOOL IsMainPOI();					//역이나 교차로 인경우(최적화가 안되어있어, 대량사용자제)
	BOOL IsMobilePOI();					//기사포인터
	BOOL IsTempPOI();					//임의로 만든 POI, 소멸을 고려해서 사용해야한다.
	BOOL IsDongPOI();
	BOOL IsSiDongOnlyPOI();				//최상위가 도이면서, 시와 동만 있는 POI 
	BOOL IsLiPOI();
	BOOL IsTopTheDoPOI();				//최상위가 도인경우에

	void GetRegionName(CString &strRegionName, BOOL bReverse = FALSE);	//지역명 FULLNAME
	CString GetRegionName(BOOL bReverse = FALSE); //지역명 FULLNAME
	void GetFullName(CString &strFullName, BOOL bReverse = FALSE);		//지역명 FULLNAME + POI_NAME
	CString GetFullName(BOOL bReverse = FALSE);							//지역명 FULLNAME + POI_NAME
	CString GetSido();
	CString GetGugun();
	CString GetGugun1Only(BOOL bShortName = FALSE);
	CString GetGugun2Only(BOOL bShortName = FALSE);
	CString GetDong(BOOL bShortName = FALSE);
	CString GetLi(BOOL bShortName = FALSE);
	CString GetDongLi();
	CPOIUnit* GetTopPOI();
	CString GetPOIName(BOOL bNotHasSubName = FALSE, BOOL bShowPhone = FALSE);
	CString GetPOISubName(BOOL bHasScope = FALSE);
	CString GetChargeDivideSiGuDong();
	int GetChargeDivideSiGuDongType();
	UINT GetID();
	long GetPosX();
	long GetPosY();
	double GetdPosX();
	double GetdPosY();
	int GetClass();
	CPOIUnit* GetParent();
	void GetTreeID(int &nSido, int &nGugun, int &nDong, int &nLi, BOOL bUseParentDetailDong = TRUE);
	BOOL IsRightEndString(CString &strSrc, const char *szPart);
	BOOL IsSimilarName(CPOIUnit *pPOI);
	CString GetPlaceName();	//접수창 출발지/도착지에 사용하는 이름
	BOOL CheckSubNamePhone();
};


#pragma pack(pop)

AFX_INLINE BOOL CPOIUnit::IsValidGugun2()
{
	return GetDongPOI()->m_szGugun2[0] != 0;
}

AFX_INLINE CPOIUnit* CPOIUnit::GetDongPOI(BOOL bMainDong)	
{ 
	if(bMainDong) 
		return m_bDongData ? this->m_pMainDong : m_pDong->m_pMainDong;
	else
		return m_bDongData ? this : m_pDong; 
}

AFX_INLINE CString CPOIUnit::GetSido() 
{ 
	return GetDongPOI()->m_szSido; 
}

AFX_INLINE CString CPOIUnit::GetGugun() 
{ 
	return IsValidGugun2() ?  CString(GetDongPOI()->m_szGugun) + " " + GetDongPOI()->m_szGugun2 : 
		GetDongPOI()->m_szGugun;
}

AFX_INLINE CString CPOIUnit::GetGugun1Only(BOOL bShortName)
{
	if(bShortName)
	{
		char *pszGugun = GetDongPOI(TRUE)->m_szGugun;
		return (strlen(pszGugun) <= 4) ? pszGugun : CString(pszGugun).Left(strlen(pszGugun) - 2);
	}
	return GetDongPOI()->m_szGugun;  
}

AFX_INLINE CString CPOIUnit::GetGugun2Only(BOOL bShortName)
{
	if(bShortName)
	{
		char *pszGugun = GetDongPOI(TRUE)->m_szGugun2;
		return (strlen(pszGugun) <= 4) ? pszGugun : CString(pszGugun).Left(strlen(pszGugun) - 2);
	}
	return GetDongPOI()->m_szGugun2;  
}

AFX_INLINE CString CPOIUnit::GetDong(BOOL bShortName)
{
	if(bShortName)
	{
		char *pszDong = GetDongPOI(TRUE)->m_szDong;
		return (strlen(pszDong) <= 4) ? pszDong : CString(pszDong).Left(strlen(pszDong) - 2);
	}
	return GetDongPOI()->m_szDong; 
}

AFX_INLINE CString CPOIUnit::GetLi(BOOL bShortName)
{
	if(bShortName)
	{
		char *pszLi = GetDongPOI(TRUE)->m_szLi;
		return (strlen(pszLi) <= 4) ? pszLi : CString(pszLi).Left(strlen(pszLi) - 2);
	}
	return GetDongPOI()->m_szLi; 
}

AFX_INLINE CString CPOIUnit::GetDongLi()
{
	if(IsLiPOI())
		return GetDong() + " " + GetLi();
	else
		return GetDong();
}

AFX_INLINE BOOL CPOIUnit::IsMobilePOI()
{
	if(m_bDongData)
		return FALSE;

	return (m_nClass == PN_MOBILE);
}

AFX_INLINE BOOL CPOIUnit::IsTempPOI()
{
	return this && (m_nClass == PN_TEMP);
}

AFX_INLINE UINT CPOIUnit::GetID()
{
	return this == NULL ? NULL : m_nID;
}

AFX_INLINE BOOL CPOIUnit::IsDongPOI()
{
	return m_bDongData;
}

AFX_INLINE long CPOIUnit::GetPosX()
{
	return m_nPosX;
}

AFX_INLINE long CPOIUnit::GetPosY()
{
	return m_nPosY;
}

AFX_INLINE double CPOIUnit::GetdPosX()
{
	return m_nPosX / 1000000.0;
}

AFX_INLINE double CPOIUnit::GetdPosY()
{
	return m_nPosY / 1000000.0;
}

AFX_INLINE int CPOIUnit::GetClass()
{
	return (int)m_nClass;
}

AFX_INLINE 	CPOIUnit* CPOIUnit::GetParent()
{
	return (this == NULL || GetDongPOI() == NULL) ? NULL : GetDongPOI()->m_pParent;
}

AFX_INLINE BOOL CPOIUnit::IsSiDongOnlyPOI()
{
	if(!GetDongPOI())
		return FALSE;

	return (GetDongPOI()->m_bTopIsDO && !IsValidGugun2());
}

AFX_INLINE BOOL CPOIUnit::IsLiPOI()
{
	return (m_nClass == PN_LI);
}

AFX_INLINE BOOL CPOIUnit::IsTopTheDoPOI()
{
	return m_bTopIsDO;
}