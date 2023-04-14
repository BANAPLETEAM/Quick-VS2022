#include "stdafx.h"
#include "MyCheckButton.h"

// CMyCheckButton

//IMPLEMENT_DYNAMIC(CMyCheckButton, CMacCheckBox)
CMyCheckButton::CMyCheckButton()
{
}

CMyCheckButton::~CMyCheckButton()
{
}


BEGIN_MESSAGE_MAP(CMyCheckButton, CMacCheckBox)
	ON_MESSAGE(BM_GETCHECK, OnGetCheck)
	ON_MESSAGE(BM_SETCHECK, OnSetCheck)
END_MESSAGE_MAP()



// CMyCheckButton 메시지 처리기입니다.

LRESULT CMyCheckButton::OnGetCheck(WPARAM wParam, LPARAM lParam)
{
	return this->GetCheck();
} 

LRESULT CMyCheckButton::OnSetCheck(WPARAM wParam, LPARAM lParam)
{
	//#ifdef	BTNST_USE_BCMENU
	//	BCMenu*	pMenu = (BCMenu*)wParam;
	//	pMenu->EnableMenuItem(IDM_ITEM3, TRUE);
	//::EnableMenuItem((HMENU)wParam, IDM_ITEM3, MF_BYCOMMAND | MF_GRAYED);
	this->SetCheck((int)wParam);
	return 0;
} 
