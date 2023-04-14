#include "StdAfx.h"
#include "POIBoundary.h"
#include "POIUnit.h"
#include "POIDataNew.h"
#include <functional>


CPOIBoundary::CPOIBoundary(CPOIDataNew *poiNew, BOOL bAutoDelete, CString strSido, CString strsido2,
						   CString strSido3, CString strSido4, CString strSido5)
{
	m_poiNew = poiNew;
	m_bSort = FALSE;
	m_bAutoDelete = bAutoDelete;
	AddSido(strSido, strsido2, strSido3, strSido4, strSido5);

	BOUNDARY_VEC::iterator it;
	for(it = m_vecBoundary.begin(); it != m_vecBoundary.end(); it++)
		g_bana_log->Print("Have Sido: %s\n", poiNew->GetDongPOI(*it)->GetRegionName());
}

CPOIBoundary::~CPOIBoundary(void)
{
}

void CPOIBoundary::RemoveAll()
{
	m_strSido.Empty();
	m_vecBoundary.clear();
}

void CPOIBoundary::AddSidoReal(CString strSido)
{		
	if(strSido.IsEmpty())
		return;

	BOOL bIsDo = CPOIDataNew::IsDo(strSido);
	POI_VEC_POINT::iterator it;
	POI_VEC_POINT &vecSido = m_poiNew->m_vecSido;

	m_strSido += strSido + ",";

	for(it = vecSido.begin(); it != vecSido.end(); it++)
	{
		if(bIsDo)
		{
			if((*it)->GetSido() == strSido)
				m_vecBoundary.push_back((*it)->GetDongID());
		}
		else
		{
			if((*it)->GetSido() == strSido && (*it)->m_nClass == PN_SIDO)
			{
				m_vecBoundary.push_back((*it)->GetDongID());
				break;
			}
		}
	}
	m_bSort = FALSE;
}

void CPOIBoundary::AddSido(CString strSido, CString strSido2, 
						   CString strSido3, CString strSido4, CString strSido5)
{
	AddSidoReal(strSido);
	AddSidoReal(strSido2);
	AddSidoReal(strSido3);
	AddSidoReal(strSido4);
	AddSidoReal(strSido5);
}

void CPOIBoundary::CheckSort()
{
	if(!m_bSort)	
	{
		sort(m_vecBoundary.begin(), m_vecBoundary.end(), less<USHORT>());
		m_bSort = TRUE;
	}
}

BOOL CPOIBoundary::Has(CPOIUnit *pPOI)
{
	CheckSort();
	BOOL bRet = binary_search(m_vecBoundary.begin(), m_vecBoundary.end(), pPOI->GetTopPOI()->GetDongID(), less<USHORT>());
	g_bana_log->Print("Has = %d, in = %d\n", pPOI->GetTopPOI()->GetDongID(), bRet);
	return bRet;
}

BOOL CPOIBoundary::Has(long nDongID)
{
	return Has(m_poiNew->GetDongPOI(nDongID));
}

BOOL CPOIBoundary::Has(CString strSido)
{
	CString strSido2 = strSido + ",";
	return m_strSido.Find(strSido2) >= 0;
}

void CPOIBoundary::Save()
{
	AfxGetApp()->WriteProfileString("POIBoundary", "HaveSido", m_strSido);
}

BOOL CPOIBoundary::Load()
{
	m_vecBoundary.clear();
	m_strSido = AfxGetApp()->GetProfileString("POIBoundary", "HaveSido", "");
	if(!m_strSido.IsEmpty())
	{
		int nPos = 0;
		for(int i = 0; i < m_strSido.GetLength(); i++)
		{
			if(m_strSido.GetAt(i) == ',')
			{
				AddSidoReal(m_strSido.Mid(nPos, nPos - i + 1));
				nPos = i + 1;
			}
		}
	}

	return !m_vecBoundary.empty();
	//return m_vecBoundary.size() > 0;
}

CString CPOIBoundary::GetSido()
{
	if(m_strSido.IsEmpty())
		return "";

	if(m_strSido.Right(1) == ',')
		return m_strSido.Left(m_strSido.GetLength() - 1);
	else
		return m_strSido;
}

BOOL CPOIBoundary::IsAutoDelete()
{
	return m_bAutoDelete;
}

BOOL CPOIBoundary::IsSameBoundary(CPOIBoundary *pPOIBoundary)
{
	CString strSido1 = GetSido() + ",";
	CString strSido2 = pPOIBoundary->GetSido() + ",";
	long nPre = 0;

	for(int i = 0; i < strSido1.GetLength(); i++)
	{
		if(strSido1.GetAt(i) == ',')
		{
			strSido2.Replace(strSido1.Mid(nPre, i - nPre + 1), "");
			nPre = i + 1;
		}
	}

	strSido2.Trim();
	return strSido2.GetLength() == 0;
}

CPOIBoundary& CPOIBoundary::operator = (const CPOIBoundary &p)
{
	m_vecBoundary = p.m_vecBoundary;
	m_strSido = p.m_strSido;
	m_poiNew = p.m_poiNew;
	m_bSort = p.m_bSort;
	m_bAutoDelete = p.m_bAutoDelete;
	return (*this);
}
