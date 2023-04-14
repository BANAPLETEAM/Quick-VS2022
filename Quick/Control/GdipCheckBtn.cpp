#include "StdAfx.h"
#include "GdipCheckBtn.h"

IMPLEMENT_DYNAMIC(CGdipCheckBtn, CGdipButton)

CGdipCheckBtn::CGdipCheckBtn(void)
{
	m_pMsgWnd = NULL;
}

CGdipCheckBtn::~CGdipCheckBtn(void)
{
}

BOOL CGdipCheckBtn::LoadAltImage(UINT id, LPCTSTR pType, HMODULE hInst)
{
	m_bIsToggle = TRUE;
	return CGdipButton::LoadAltImage(id, pType, hInst);
}

int CGdipCheckBtn::GetCheck() const
{
	return m_nCurType == ALT_TYPE;
}
void CGdipCheckBtn::SetCheck(int nCheck)
{
	m_nCurType = nCheck ? ALT_TYPE : STD_TYPE;
	Invalidate();
}

void CGdipCheckBtn::SetCheckImage(UINT nIDUncheck, UINT nIDCheck, LPCTSTR pType, CWnd *pWnd)
{
	m_pMsgWnd = pWnd;
	LoadStdImage(nIDUncheck, pType, m_hCommondll);	
	LoadAltImage(nIDCheck, pType, m_hCommondll);	
}

BEGIN_MESSAGE_MAP(CGdipCheckBtn, CGdipButton)
	//ON_CONTROL_REFLECT(BN_CLICKED, OnBnClicked)
END_MESSAGE_MAP()

/*
void CGdipCheckBtn::OnBnClicked()
{
	if(m_pMsgWnd)
		m_pMsgWnd->PostMessage(WM_CLICKED_BUTTON, (WPARAM)this, 0);

	CButton::OnBnClicked();
}
*/