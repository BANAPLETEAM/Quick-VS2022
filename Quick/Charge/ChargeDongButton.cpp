

// DepositButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDongButton.h"
#include "ChargeDongUDlg.h"

// CDepositButton
#define  WM_ID_INITDATA_LOAD WM_USER + 1500
#define  WM_ID_USERDONGPOS_LOAD WM_USER + 1510
#define  WM_ID_USERDONGPOS_SAVE WM_USER + 1520
#define  WM_ID_USERDONGPOS_PASTE_DEST WM_USER + 1530

//IMPLEMENT_DYNAMIC(CChargeDongButton, CButtonST)
CChargeDongButton::CChargeDongButton()
{
	m_nSelectedCNo = 0;
}

CChargeDongButton::~CChargeDongButton()
{
}


BEGIN_MESSAGE_MAP(CChargeDongButton, CButtonST)

	ON_COMMAND(ID_INITDATA_LOAD, OnInItDataLoad)
	ON_COMMAND(ID_USERDONGPOS_LOAD, OnUserDongPosLoad)
	ON_COMMAND(ID_USERDONGPOS_SAVE, OnUserDongPosSave)
	ON_COMMAND(ID_USERDONGPOS_PASTE_DEST, OnUserDongPosPasteDest)
END_MESSAGE_MAP()




void CChargeDongButton::OnInItDataLoad()
{
	m_pChargeDongUDlg->SendMessage(WM_ID_INITDATA_LOAD,(WPARAM)m_pChargeDongUDlg,(LPARAM)this->m_nSelectedCNo);
}

void CChargeDongButton::OnUserDongPosLoad()
{
	m_pChargeDongUDlg->SendMessage(WM_ID_USERDONGPOS_LOAD,(WPARAM)m_pChargeDongUDlg,(LPARAM)this->m_nSelectedCNo);
}
void CChargeDongButton::OnUserDongPosSave()
{
	m_pChargeDongUDlg->SendMessage(WM_ID_USERDONGPOS_SAVE,(WPARAM)m_pChargeDongUDlg,(LPARAM)this->m_nSelectedCNo);
}
void CChargeDongButton::OnUserDongPosPasteDest()
{
	m_pChargeDongUDlg->SendMessage(WM_ID_USERDONGPOS_PASTE_DEST,(WPARAM)m_pChargeDongUDlg,(LPARAM)this->m_nSelectedCNo);
}

void CChargeDongButton::InitButton(CChargeDongUDlg *pDlg)
{
	short	shBtnColor = 130;
	m_pChargeDongUDlg = pDlg;

	//	m_DateBtn.SetIcon(IDI_TOOLS4);
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 128);

	//#ifdef	BTNST_USE_BCMENU
	//	pBtn->SetMenu(IDR_DATE_MENU, m_hParent, TRUE, IDR_TOOLBAR);
	
	SetMenu(IDR_MENU_USERDONGPOS, GetSafeHwnd());

}    



