#include "StdAfx.h"
#include "POIUnit.h"
#include <math.h>

#define NEAR_MAX_POS_DONG_DEMISE	40000
#define NEAR_MAX_POS_POI_DEMISE		5000 


CPOIUnit::CPOIUnit(void)
{
}

CPOIUnit::~CPOIUnit(void)
{
}

void CPOIUnit::SetPOI(char *szName, char *szSubName, char *szPhone)
{
	m_bDongData = FALSE;
	strcpy(m_szName, szName);
	strcpy(m_szSubName, szSubName);
	strcpy(m_szPhone, szPhone);
}

void CPOIUnit::SetPOI(char *szSido, char *szGugun, char *szGugun2, char *szDong)
{
	m_bDongData = TRUE;
	strcpy(m_szSido, szSido);
	strcpy(m_szGugun, szGugun);
	strcpy(m_szGugun2, szGugun2);
	strcpy(m_szDong, szDong);
}

void CPOIUnit::SetPos(long nPosX, long nPosY)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CPOIUnit::SetChildUnit(CPOIUnit *pDong, CPOIUnit *pParent)
{
	m_pDong = pDong;
	m_pParent = pParent;
}

void CPOIUnit::SetPOIType(BOOL bDong)
{
	m_bDongData = bDong ? TRUE: FALSE;
} 

CString CPOIUnit::GetPhoneNumber(BOOL bNoneDash, BOOL bHasBracket)
{
	if(IsDongPOI()) return "";

	if(m_bHasPhone)
	{
		CString strTemp;
		if(bNoneDash)
		{
			strTemp.Format("%s%s%s%s", bHasBracket ? "(" : "", m_szDDD, m_szPhone, bHasBracket ? ")" : "");
			return strTemp;
		}
		else
		{
			char szMid[5];
			if(m_szPhone[7] == 0)
			{
				strncpy(szMid, m_szPhone, 3);
				szMid[3] = 0;
				strTemp.Format("%s%s-%s-%s%s", bHasBracket ? "(" : "", m_szDDD, 
						szMid, &m_szPhone[3], bHasBracket ? ")" : "");
			}
			else
			{
				strncpy(szMid, m_szPhone, 4);
				szMid[4] = 0;
				strTemp.Format("%s%s-%s-%s%s", bHasBracket ? "(" : "", m_szDDD, 
						szMid, &m_szPhone[4], bHasBracket ? ")" : "");
			}

			return strTemp;
		}
	}
	return "";
}

int CPOIUnit::IsNearPOI(CPOIUnit *pPOI, int nMaxMeter, int nFilterLevel)
{
	if(abs(m_nPosX - pPOI->m_nPosX) < nFilterLevel &&
		abs(m_nPosY - pPOI->m_nPosY) < nFilterLevel)
	{
		int nMeter = GetDistanceMeter(pPOI);
		if(nMeter == 0) nMeter = 1;
		if(nMeter < nMaxMeter)
			return nMeter;
	}

	return 0;
}

int CPOIUnit::GetDistanceMeter(CPOIUnit *pPOI)
{ 
	if(pPOI == NULL) return 0xFFFFFF;
	return GetDistanceMeter(pPOI->m_nPosX, pPOI->m_nPosY);
}

int CPOIUnit::GetDistanceMeter(long nPosX, long nPosY)
{
	double dx = (m_nPosY - nPosY) * 0.30918467038935;
	double dy = (m_nPosX - nPosX) * cos((m_nPosY + nPosY) * 0.000000024240661) * 0.30918467038935;
	return sqrt(dx*dx + dy*dy);
}

int CPOIUnit::GetDistanceMeterDeMiSe(long nPosX, long nPosY)
{
	double dx = (m_nPosY - nPosY) * 0.111306481340166;
	double dy = (m_nPosX - nPosX) * cos((m_nPosY + nPosY) * 0.000000008726638) * 0.111306481340166;
	return sqrt(dx*dx + dy*dy);
}

int CPOIUnit::GetDistanceMeterLevel(CPOIUnit *pPOI, long nLevelMeter)
{
	if(pPOI == NULL) return 0xFFFFFF;
	int nOffset = (pPOI->GetTopPOI() == GetTopPOI()) ? 1 : 0;
	int nDistance = GetDistanceMeter(pPOI->m_nPosX, pPOI->m_nPosY);
	return nDistance - (nDistance % nLevelMeter) - nOffset;
}



#define P_S		pPOI->m_szSido
#define P_G		pPOI->GetGugun()
#define P_G1	pPOI->GetGugun1Only()
#define P_D		pPOI->m_szDong
#define P_L		pPOI->m_szLi
#define P_CLS	pPOI->m_nClass

void CPOIUnit::GetRegionName(CString &strR, BOOL bReverse)
{
	CPOIUnit *pPOI = GetDongPOI();

	if(!pPOI || !pPOI->GetDongID())
	{
		//g_bana_log->Print("GetRegionName: poiid = %d, dongid = %d, %s\n", m_nID, pPOI->GetDongID(), "EMPTY");
		strR.Empty();
		return;
	}

	if(!bReverse)
	{
		if(P_CLS == PN_SIDO && !m_bTopIsDO)
			strR.Format("%s", P_S);
		else if(P_CLS == PN_SIDO && m_bTopIsDO)
			strR.Format("%s %s", P_S, P_G1);
		else if(P_CLS == PN_GUGUN)
			strR.Format("%s %s", P_S, P_G);
		else if(P_CLS == PN_LI)
			strR.Format("%s %s %s %s", P_S, P_G, P_D, P_L);
		else
			strR.Format("%s %s %s", P_S, P_G, P_D);
	}
	else
	{
		if(P_CLS == PN_SIDO && !m_bTopIsDO)
			strR.Format("%s", P_S);
		else if(P_CLS == PN_SIDO && m_bTopIsDO)
			strR.Format("%s %s", P_G1, P_S);
		else if(P_CLS == PN_GUGUN)
			strR.Format("%s %s", P_G, P_S);
		else if(P_CLS == PN_LI)
			strR.Format("%s %s %s %s", P_L, P_D, P_G, P_S);
		else
			strR.Format("%s %s %s", P_D, P_G, P_S);
	}

	strR.Replace("  ", " ");
	//g_bana_log->Print("GetRegionName: poiid = %d, dongid = %d, %s\n", m_nID, pPOI->m_nDongID, strR);
}

CString CPOIUnit::GetRegionName(BOOL bReverse)
{
	CString strName;
	GetRegionName(strName, bReverse);
	return strName;
}

void CPOIUnit::GetFullName(CString &strFullName, BOOL bReverse)
{
	GetRegionName(strFullName, bReverse);

	if(!IsDongPOI())
	{
		if(!bReverse)
			strFullName = strFullName + CString(" ") + GetPOIName();
		else
			strFullName = GetPOIName() + CString(" ") + strFullName;
	}
}

CString CPOIUnit::GetFullName(BOOL bReverse)
{
	CString strFullName;
	GetFullName(strFullName, bReverse);
	return strFullName;
}


BOOL CPOIUnit::IsSameDong(CPOIUnit *pPOI, BOOL bMainDongAlsoSame)
{
	if(bMainDongAlsoSame)
		return GetMainDongID() == pPOI->GetMainDongID();
	else
		return GetDongID() == pPOI->GetDongID();
}

void CPOIUnit::GetNormalizePos(long &nPosX, long &nPosY)
{
	if(IsDongPOI())
	{
		nPosX = m_nPosX - m_nPosX % NEAR_MAX_POS_DONG + NEAR_MAX_POS_DONG / 2;
		nPosY = m_nPosY - m_nPosY % NEAR_MAX_POS_DONG + NEAR_MAX_POS_DONG / 2;
	}
	else
	{
		nPosX = m_nPosX - m_nPosX % NEAR_MAX_POS_POI + NEAR_MAX_POS_POI / 2;
		nPosY = m_nPosY - m_nPosY % NEAR_MAX_POS_POI + NEAR_MAX_POS_POI / 2;
	}
}

UINT CPOIUnit::GetDongID(BOOL bIfLIThenReturnDongID)
{
	if(this == NULL)
		return 0;

	if(bIfLIThenReturnDongID && GetDongPOI()->m_nClass == PN_LI)
		return GetDongPOI()->GetParent()->GetDongID();
	else
		return m_bDongData ? m_nID : m_nDongID;
}

UINT CPOIUnit::GetMainDongID()
{
	if(this == NULL)
		return 0;

	if(IsDongPOI())
		return m_nMainDongID > 0 ? m_nMainDongID : m_nID;
	else 
		return m_pDong->GetMainDongID();
}

CPOIUnit* CPOIUnit::GetTopPOI()
{
	if(this == NULL)
		return 0;

	if(!GetDongPOI()) 
		return 0;

	if(m_nClass == PN_LI)
	{
		if(IsSiDongOnlyPOI())
			return GetDongPOI()->m_pParent->m_pParent;
		else
			return GetDongPOI()->m_pParent->m_pParent->m_pParent;
	}
	else if(m_nClass <= PN_SAME_NAME_DONG)
	{
		if(IsSiDongOnlyPOI())
			return GetDongPOI()->m_pParent;
		else
		{
			CPOIUnit *p = GetDongPOI();
			CPOIUnit *p1 = GetDongPOI()->m_pParent;
			CPOIUnit *p2 = p1->m_pParent;
			CPOIUnit *p3 = GetDongPOI()->m_pParent->m_pParent;
			return GetDongPOI()->m_pParent->m_pParent;
		}
	}
	else if(m_nClass == PN_GUGUN)
	{
		if(IsSiDongOnlyPOI())
			return this;
		else
			return GetDongPOI()->m_pParent;
	}
	
	return this;
}

CString CPOIUnit::GetPOIName(BOOL bNotHasSubName, BOOL bShowPhone)
{
	if(IsDongPOI()) 
		return IsLiPOI() ? GetDong() + GetLi() : GetDong();
	else if(bShowPhone && m_bHasPhone)
		return CString(m_szName) + GetPhoneNumber(FALSE, TRUE);
	else 
		return (m_szSubName[0] != 0 && !m_bHasPhone && !bNotHasSubName) ? 
				CString(m_szName) + "(" + CString(m_szSubName) + ")" : m_szName;
}

CString CPOIUnit::GetPOISubName(BOOL bHasScope)
{
	if(IsDongPOI()) 
		return "";
	else 
	{
		if(bHasScope)
			return (m_szSubName[0] != 0 && !m_bHasPhone) ? CString("(") + m_szSubName + ")" : "";
		else
			return (m_szSubName[0] != 0 && !m_bHasPhone) ? m_szSubName : "";
	}

}

BOOL CPOIUnit::IsRightEndString(CString &strSrc, const char *szPart)
{
	int nLen = strlen(szPart);
	if(strSrc.GetLength() > nLen)
		if(strSrc.Right(nLen) == szPart)
			return TRUE;
	return FALSE;
}

BOOL CPOIUnit::IsMainPOI()
{
	if(IsDongPOI())
		return FALSE;

//	if(IsMobilePOI())
//		return TRUE;

	CString strPOI = m_szName;

	if(IsRightEndString(strPOI, "무역"))
		return FALSE;

	if(IsRightEndString(strPOI, "역") ||
		IsRightEndString(strPOI, "사거리") ||
		IsRightEndString(strPOI, "삼거리") ||
		IsRightEndString(strPOI, "오거리") ||
		IsRightEndString(strPOI, "교차로") ||
		IsRightEndString(strPOI, "로터리") )
	{
		return TRUE;
	}
	return FALSE;
}


CString CPOIUnit::GetChargeDivideSiGuDong()
{
	CString sAreaDivide = "";
	if(m_nClass == PN_SIDO && m_bDongData)
		sAreaDivide = "시";
	else if(m_nClass == PN_GUGUN )
		sAreaDivide = "구";		
	else if(m_nClass <= PN_SAME_NAME_DONG)
		sAreaDivide = "동";		
	else if(m_nClass == PN_LI)
		sAreaDivide = "리";		
	else 
		sAreaDivide = "";		

	return sAreaDivide;
}


int CPOIUnit::GetChargeDivideSiGuDongType()
{
	int  nAreaDivide = 0;
	if(m_nClass == PN_SIDO && m_bDongData)
		nAreaDivide = 3;
	else if(m_nClass == PN_GUGUN )
		nAreaDivide = 2;
	else if(m_nClass <= PN_SAME_NAME_DONG)
		nAreaDivide = 1;
	else if(m_nClass == PN_LI)
		nAreaDivide = -1;
	else 
		nAreaDivide = 0;		

	return nAreaDivide;
}

void CPOIUnit::GetTreeID(int &nSido, int &nGugun, int &nDong, int &nLi, BOOL bUseParentDetailDong )
{
	nSido = 0;
	nGugun = 0;
	nDong = 0;
	nLi = 0;

	// bUseDetailDong Default TRUE
	CPOIUnit *pDong = GetDongPOI(bUseParentDetailDong);

	if(pDong == NULL)
		return;

	if(pDong->m_nClass == PN_LI)
	{
		nLi = pDong->GetID();
		nDong = pDong->GetParent()->GetID();
		nGugun = pDong->GetParent()->GetParent()->GetID();
		if(!IsSiDongOnlyPOI() && pDong->GetParent()->GetParent()->GetParent())
			nSido = pDong->GetParent()->GetParent()->GetParent()->GetID();
	}
	else if(pDong->m_nClass <= PN_SAME_NAME_DONG)
	{
		nDong = pDong->GetID();
		nGugun = pDong->GetParent()->GetID();
		if(!IsSiDongOnlyPOI() && pDong->GetParent()->GetParent())
			nSido = pDong->GetParent()->GetParent()->GetID();
	}
	else if(pDong->m_nClass == PN_GUGUN)
	{
		nGugun = pDong->GetID();
		if(!IsSiDongOnlyPOI() && pDong->GetParent())
			nSido = pDong->GetParent()->GetID();
	}
	else if(pDong->m_nClass == PN_SIDO)
	{
		nSido = pDong->GetID();
	}
}

BOOL CPOIUnit::IsSimilarName(CPOIUnit *pPOI)
{
	CString strName = pPOI->GetPOIName(TRUE);
	CString strName2 = GetPOIName(TRUE);

	if(strName.Find(strName2) >= 0 ||
		strName2.Find(strName) >= 0)
	{
		return TRUE;
	}
	return FALSE;
}

CString CPOIUnit::GetPlaceName()
{
	if(IsMainPOI())
	{
		return GetPOIName();
	}
	else if(IsDongPOI())
	{
		return GetDong(FALSE);
	}
	else
	{
		CString strDong = GetDong(TRUE);
		CString strPOI = GetPOIName();

		if(strPOI.Find(strDong) == 0)
			return strPOI;
		else
			return strDong + strPOI;
	}
}

BOOL CPOIUnit::CheckSubNamePhone()
{
	if(!m_bHasPhone)
	{
		if(m_szSubName[0] == '0')
		{
			int nLen = strlen(m_szSubName);
			if(m_szSubName[1] >= '0' && m_szSubName[1] <= '9' && nLen > 7)
			{
				BYTE nOffset = 3;
				m_bHasPhone = TRUE;

				if(m_szSubName[1] == '2')
					nOffset = 2;
				else if(m_szSubName[2] == '0')
					nOffset = 4;

				for(int i = nLen - 1; i >= nOffset; i--)
					m_szPhone[i - nOffset] = m_szSubName[i];

				m_szPhone[nLen - nOffset] = 0;
				m_szSubName[nOffset] = 0;

				return TRUE;
			}
		}
		else
		{
			m_szSubName[28] = 0;
		}
	}

	return FALSE;
}
