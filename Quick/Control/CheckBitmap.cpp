// CheckBitmap.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "CheckBitmap.h"

 
// CCheckBitmap

IMPLEMENT_DYNAMIC(CCheckBitmap, CBitmapButton)

CCheckBitmap::CCheckBitmap()
{
	m_bCheck = FALSE;
}

CCheckBitmap::~CCheckBitmap()
{
}


BEGIN_MESSAGE_MAP(CCheckBitmap, CBitmapButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CCheckBitmap::OnBnClicked)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CCheckBitmap::SetCheck(int nCheck)
{
	m_bCheck = nCheck;
	ChangeImage();
}

BOOL CCheckBitmap::GetCheck()
{
	return m_bCheck;
}

void CCheckBitmap::OnBnClicked()
{
	long nCheck = GetCheck();
	SetCheck(!GetCheck());

	ChangeImage();

	if(m_pMsgWnd)
		m_pMsgWnd->PostMessage(WM_CLICKED_BUTTON, (WPARAM)this, 0);
}

void CCheckBitmap::ChangeImage()
{
	SetTimer(10, 10, NULL);
}


void CCheckBitmap::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	if(nIDEvent == 10)
	{
		if(GetCheck()) 
			LoadBitmaps(m_nCheckImage);
		else
			LoadBitmaps(m_nNotCheckImage);

		SizeToContent();
		Invalidate(); 
	}

	CBitmapButton::OnTimer(nIDEvent);
}
