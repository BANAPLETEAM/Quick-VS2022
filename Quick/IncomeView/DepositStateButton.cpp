// DateButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DepositStateButton.h"
#include "RiderDepositInfoDlg.h" 


// CDepostStateButton

//IMPLEMENT_DYNAMIC(CDepositStateButton, CButtonST)
CDepositStateButton::CDepositStateButton()
{
}

CDepositStateButton::~CDepositStateButton()
{
}


BEGIN_MESSAGE_MAP(CDepositStateButton, CButtonST)
	ON_COMMAND(ID_NOT_REPORT, OnNotReport)
	ON_COMMAND(ID_REPORT_COMPLETE, OnReportComplete)
	ON_COMMAND(ID_INCOME_COMPLETE, OnIncomeComplete)
END_MESSAGE_MAP()


void CDepositStateButton::OnNotReport()
{
	m_pRdiDlg->OnBnClickedNotReportBtn();

}
void CDepositStateButton::OnReportComplete()
{
	m_pRdiDlg->OnBnClickedReportCompleteBtn();

}
void CDepositStateButton::OnIncomeComplete()
{
	m_pRdiDlg->OnBnClickedIncomeCompleteBtn();
}

void CDepositStateButton::InitButton(CRiderDepositInfoDlg *pDlg)
{
	short	shBtnColor = 30;
	m_pRdiDlg = pDlg;

	//	m_DateBtn.SetIcon(IDI_TOOLS4);
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 28);

	//#ifdef	BTNST_USE_BCMENU
	//	pBtn->SetMenu(IDR_DATE_MENU, m_hParent, TRUE, IDR_TOOLBAR);
	SetMenu(IDR_DEPOSIT_STATE, GetSafeHwnd());
	SetMenuCallback(GetSafeHwnd(), WM_USER + 100);		
}    

