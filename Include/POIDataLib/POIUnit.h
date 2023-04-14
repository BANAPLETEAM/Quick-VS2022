#pragma once

#include "AfxStr.h"


#pragma pack(push)
#pragma pack(1)

enum { PN_SAME_NAME_DONG = 3, PN_GUGUN = 5, PN_SIDO = 10, PN_LI = 20};
enum { PN_NORMAL = 0, PN_MOBILE = 1, PN_TEMP = 2, PN_STATION = 3};

#define NEAR_MAX_POS_DONG			14400
#define NEAR_MAX_POS_POI			1800 
#define VERY_NEAR_MAX_POS			500


class AFX_EXT_CLASS CPOIUnit		//������� �߰�����(�޸𸮿뷮�þ)
{
public:
	CPOIUnit(void);
	~CPOIUnit(void);

public:
	UINT m_nID;	//POI�� ��쿡 POI_ID, DONG�� ��쿡 DONG_ID
	bool m_bDongData;	//TRUE: ��������, FALSE: POI������

	union {
		struct {
			bool m_bHasPhone;			//POI�� ��쿡�� ��ȿ��
			char m_szName[30];			//POI�� ��쿡 ��Ī, DONG�� ��쿡 SIDO
			union
			{
				char m_szSubName[29];	//POI�� ��쿡�� ��ȿ��
				struct {
					char m_szDDD[5];	//POI�� ��쿡�� ��ȿ��
					char m_szPhone[10];	//POI�� ��쿡�� ��ȿ��
					char m_szRFU[14];	//POI�� ��쿡�� ��ȿ��
				};
			};
	
			CPOIUnit *m_pDong;		//POI�� ��츸 ��POI
			UINT m_nDongID;			//POI�� ��츸 ��ID
			BYTE m_nPriority;		//POI�� ��츸 �˻� �켱����
			BYTE m_nClass;	
		};

		struct {
			bool m_bHasChild;			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			char m_szSido[5];			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			char m_szGugun[11];			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			char m_szGugun2[11];		//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			char m_szDong[12];			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			char m_szLi[11];			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			CPOIUnit *m_pMainDong;		//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			CPOIUnit *m_pParent;		//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			USHORT m_nParentID;			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			USHORT m_nMainDongID;		//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			BYTE m_bTopIsDO;			//DONG�������� ��츸 ��ȿ��, POI�� pDong ����
			BYTE m_nClass;
		};
	};

	long m_nPosX;						//WGS84 Coordinator�� �浵, LONGITUDE
	long m_nPosY;						//WGS84 Coordinator�� ����, LATTITUDE

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
	int GetDistanceMeter(long nPosX, long nPosY);	//�ʴ���
	int GetDistanceMeterDeMiSe(long nPosX, long nPosY); //�����ʴ���
	int GetDistanceMeterLevel(CPOIUnit *pPOI, long nLevelMeter = 7000);

	BOOL IsSameDong(CPOIUnit *pPOI, BOOL bMainDongAlsoSame = TRUE);
	void GetNormalizePos(long &nPosX, long &nPosY);
	BOOL IsMainPOI();					//���̳� ������ �ΰ��(����ȭ�� �ȵǾ��־�, �뷮�������)
	BOOL IsMobilePOI();					//���������
	BOOL IsTempPOI();					//���Ƿ� ���� POI, �Ҹ��� ����ؼ� ����ؾ��Ѵ�.
	BOOL IsDongPOI();
	BOOL IsSiDongOnlyPOI();				//�ֻ����� ���̸鼭, �ÿ� ���� �ִ� POI 
	BOOL IsLiPOI();
	BOOL IsTopTheDoPOI();				//�ֻ����� ���ΰ�쿡

	void GetRegionName(CString &strRegionName, BOOL bReverse = FALSE);	//������ FULLNAME
	CString GetRegionName(BOOL bReverse = FALSE); //������ FULLNAME
	void GetFullName(CString &strFullName, BOOL bReverse = FALSE);		//������ FULLNAME + POI_NAME
	CString GetFullName(BOOL bReverse = FALSE);							//������ FULLNAME + POI_NAME
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
	CString GetPlaceName();	//����â �����/�������� ����ϴ� �̸�
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