#include "StdAfx.h"
#include "CompanyInfo.h"

CCompanyInfo::CCompanyInfo(void)
{
	m_nMaxChildCompanyCode = -1;
	m_pCargoMainBranch = NULL;
	m_pQuickMainBranch = NULL;
}

CCompanyInfo::~CCompanyInfo(void)
{
}

CString CCompanyInfo::GetName(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_strName;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strName;
}

void CCompanyInfo::GetCNsInfo(long nCompany, long &nCnsSearchType1, long &nCnsSearchType2, long &nCnsSearchPaid)
{
	nCnsSearchType1 = 1;
	nCnsSearchType2 = 2;
	nCnsSearchPaid = 2;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return;

	nCnsSearchType1 = it->second.nCnsSearchType1;
	nCnsSearchType2 = it->second.nCnsSearchType2;
	nCnsSearchPaid = it->second.nCnsSearchPaid;
}

CString CCompanyInfo::GetBranchName(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_strBranchName;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strBranchName;
}

CString CCompanyInfo::GetCompanyName(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_strName;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strName;
}

long CCompanyInfo::GetRcpIntMode1(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_bRcpIntMode1;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.bRcpIntMode1;
}


long CCompanyInfo::GetShareCode1(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode1;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.nShareCode1;
}


long CCompanyInfo::GetShareCode2(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode2;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.nShareCode2;
}

long CCompanyInfo::GetShareCode3(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode3;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.nShareCode3;
}

long CCompanyInfo::GetShareCode4(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode4;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.nShareCode4;
}

long CCompanyInfo::GetShareCode5(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode5;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return 0;

	return it->second.nShareCode5;
} 

long CCompanyInfo::GetShareCode(long nCompany, long nLevel)
{
	if(nLevel == 2)
		return GetShareCode2(nCompany);
	else if(nLevel == 3)
		return GetShareCode3(nCompany);
	else if(nLevel == 4)
		return GetShareCode4(nCompany);
	else if(nLevel == 5)
		return GetShareCode5(nCompany);
	else
		return GetShareCode1(nCompany);
}


CString CCompanyInfo::GetShareCompanyName(long nCompany)
{
	MAP_SHARED_COMPANY::iterator it;
	it = m_ci.GetMap().find(nCompany);


	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strName;
}
 
CString CCompanyInfo::GetShareCompanyBranchName(long nCompany)
{
	MAP_SHARED_COMPANY::iterator it;
	it = m_ci.GetMap().find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strBranchName;
}

CString CCompanyInfo::GetShareCompanyPhone(long nCompany)
{
	MAP_SHARED_COMPANY::iterator it;
	it = m_ci.GetMap().find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strPhone;
}

CString CCompanyInfo::GetShareCompanyOfficePhone(long nCompany)
{
	MAP_SHARED_COMPANY::iterator it;
	it = m_ci.GetMap().find(nCompany);

	if(it == m_ci.GetShareMapEnd())
		return "";

	return it->second.strOfficePhone;
}

BOOL CCompanyInfo::IsShareCompany(long nCompany)
{
	if(nCompany == 0)
		return m_ci.m_nShareCode1;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	return it != m_ci.GetShareMapEnd();
}

BOOL CCompanyInfo::IsUseBranchShareReport(long nCompany)
{
	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	return (it != m_ci.GetShareMapEnd()) ? it->second.bUseBranchShareReport : 0;
}


CString CCompanyInfo::GetPhone(long nCompany, BOOL bOfficePhone)
{
	if(nCompany == 0)
		return bOfficePhone ? m_ci.m_strOfficePhone : m_ci.m_strPhone;

	MAP_SHARED_COMPANY::iterator it;
	it = m_ShareCompanyMap.find(nCompany);

	if(it != m_ShareCompanyMap.end())
		return bOfficePhone ? it->second.strOfficePhone : it->second.strPhone;

	return "";
}

BOOL CCompanyInfo::IsChildCompany(long nCompany)
{
	if(m_nMaxChildCompanyCode >= 0)
	{
		if(nCompany > 0 && nCompany <= m_nMaxChildCompanyCode)
			return (m_vecChildCompany[nCompany] == 1);
		else
			return 0;
	}
	else
	{
		if(m_ccm.size() > 0)
		{
			m_nMaxChildCompanyCode = 0;

			MAP_CHILD_COMPANY::iterator it;
			for(it = m_ccm.begin(); it != m_ccm.end(); it++)
				m_nMaxChildCompanyCode = max(m_nMaxChildCompanyCode, it->second);

			BYTE nByte = 0;
			m_vecChildCompany.assign(m_nMaxChildCompanyCode + 1, nByte);
			for(it = m_ccm.begin(); it != m_ccm.end(); it++)
				m_vecChildCompany[it->second] = 1;

			return IsChildCompany(nCompany);
		}
	}
	return (m_ccm.find(nCompany) != m_ccm.end());
}

BOOL CCompanyInfo::IsThisCompany(CString strCompanyName, long nCompany, long nShareCode1)
{
	long nShare1 = nShareCode1 > 0 ? nShareCode1 : m_nShareCode1;

	if(strCompanyName == "퀵오케이")
		return (m_nShareCode1 == 2900);
	else if(strCompanyName == "적재물보험")
	{
		return (m_nShareCode1 == 2020);
	}
	else
	{
		MessageBox(GetDesktopWindow(), CString("알수없는 회사구분 코드 ") + strCompanyName,
			"확인",
			MB_ICONINFORMATION);
	}

	return FALSE;
} 

CString CCompanyInfo::GetProperName(long nCompany)
{
	if(IsChildCompany(nCompany))
		return GetBranchName(nCompany);
	else
		return GetName(nCompany);
}




BOOL CCompanyInfo::HasShareCompany()
{
	return m_ShareCompanyMap.size() > 1;
}

void CCompanyInfo::CheckFirstMain(CBranchInfo *pBi)
{
	BOOL bCargo = pBi->IsCargo();
	BOOL bQuick = pBi->IsQuick();
	if(m_ci.m_pCargoMainBranch == NULL && pBi->IsCargo())
		m_ci.m_pCargoMainBranch = pBi;

	if(m_ci.m_pQuickMainBranch == NULL && pBi->IsQuick())
		m_ci.m_pQuickMainBranch = pBi;
}

BOOL CCompanyInfo::IsCapitalShare()
{
	return (m_nShareCode5 == 9999);
}

BOOL CCompanyInfo::IsRealtimeShareCompany()
{
	return (IsCapitalShare() && m_nShareCode4 > 0);
}

BOOL CCompanyInfo::IsRealtimeShareRider(long nRiderCompany)
{
	return (IsRealtimeShareCompany() && m_ci.m_nShareCode4 == m_ci.GetShareCode4(nRiderCompany));
}

BOOL CCompanyInfo::IsCrossCompany(long nCompany)
{
	MAP_CHILD_COMPANY::iterator it;
	it = m_ccm.find(nCompany);

	if(it == m_ccm.end())
		return TRUE;

	return FALSE;
}
