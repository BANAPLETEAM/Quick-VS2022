#include "StdAfx.h"
#include "Quick.h"
#include "ChargeContainer.h"
#include "ChargeDongDlg2.h"
#include "ChargeDongDlg3.h"
#include "ChargeDistanceDlg2.h"
#include "SelectChargeType.h"

CChargeContainer::CChargeContainer()
{

}

CChargeContainer::CChargeContainer(CWnd *pOwner)
{
	m_pwndOwner = pOwner;
	m_pChargeDongDlg2 = NULL;
	m_pChargeDongDlg3 = NULL;
	m_pSelectChargeTypeDlg = NULL;
	m_pChargeDistanceDlg2 = NULL;

}

CChargeContainer::~CChargeContainer(void)
{
	if(m_pChargeDongDlg2)
		delete m_pChargeDongDlg2;
	if(m_pChargeDongDlg3)
		delete m_pChargeDongDlg3;
	if(m_pSelectChargeTypeDlg)
		delete m_pSelectChargeTypeDlg;
	if(m_pChargeDistanceDlg2)
		delete m_pChargeDistanceDlg2;
}

BOOL CChargeContainer::IsIntegrated()
{
	CBranchInfo *pBi = NULL;
	for(int i = 0; i < m_ba.GetCount(); i++) 
	{
		pBi = m_ba.GetAt(i);
		if(pBi->bIntegrated)
		{
			return TRUE;
		}		
	}
	return FALSE;
}

template<class CMyDlg>
void CChargeContainer::CreateModalessChargeDlg(CMyDlg **pDlg, long nCompany, 
							CString strBranchName, void (*pfInit)(CMyDlg*, CChargeContainer*))
{
	if((*pDlg) == NULL)
	{
		(*pDlg) = new CMyDlg(m_pwndOwner);
		(*pDlg)->m_nCompany = nCompany;
		(*pDlg)->m_bIntegrated = IsIntegrated();
		(*pDlg)->Create(CMyDlg::IDD, m_pwndOwner);
		
		
		if(pfInit) (*pfInit)(*pDlg, this);
		(*pDlg)->ShowWindow(SW_SHOW);
		(*pDlg)->CenterWindow();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		(*pDlg)->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
		{
			(*pDlg)->ShowWindow(SW_RESTORE);
		}
		else
		{
			(*pDlg)->ShowWindow(SW_SHOW);
			(*pDlg)->SetForegroundWindow();
			(*pDlg)->SetFocus();
		}
	}
}

void CChargeContainer::ChargeDongDlg3Show()
{
	CBranchInfo *pBi = GetCurBranchInfo();
	CreateModalessChargeDlg(&m_pChargeDongDlg3, 
		IsIntegrated() ? pBi->nPayTable : pBi->nPayTable);
 
}



void CChargeContainer::ChargeDistanceDlgShow(CBranchInfo *pBi)
{
	if(!pBi) pBi = GetCurBranchInfo();
	CreateModalessChargeDlg(&m_pChargeDistanceDlg2, 
		IsIntegrated() ? pBi->nCompanyCode : pBi->nPayTable);
}

void InitSelectChargeType(CSelectChargeType *pDlg, CChargeContainer *pThis)
{
	pDlg->m_pChargeContainer = pThis;
}

void CChargeContainer::ChargeShow()
{
	CBranchInfo *pBi = GetCurBranchInfo();
	CreateModalessChargeDlg(&m_pSelectChargeTypeDlg, 
			IsIntegrated() ? pBi->nCompanyCode : pBi->nPayTable, pBi->strBranchName, 
			InitSelectChargeType);
}