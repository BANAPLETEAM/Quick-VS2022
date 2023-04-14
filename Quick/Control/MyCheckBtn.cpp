// MyCheckBtn.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyCheckBtn.h"


// CMyCheckBtn

IMPLEMENT_DYNAMIC(CMyCheckBtn, CButton)

CMyCheckBtn::CMyCheckBtn()
{
	m_bGetBkColor = FALSE;
	m_crBack = RGB(255, 255, 255);
}

CMyCheckBtn::~CMyCheckBtn()
{
}


BEGIN_MESSAGE_MAP(CMyCheckBtn, CButton)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


// CMyCheckBtn 메시지 처리기입니다.

HBRUSH CMyCheckBtn::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if(!m_bGetBkColor)
	{
		CDC MemDC;
		CRect rc;
		GetWindowRect(&rc);
		CWnd *pParent = GetParent();
		pParent->ScreenToClient(&rc);

		CDC *pParentDC = pParent->GetDC();

		CPoint pt;
		pt.x = rc.left + rc.Width() / 2;
		pt.y = rc.top + rc.Height() / 2;

		for(int n = pt.x; n >= 0; n-=5)
		{
			m_crBack = pParentDC->GetPixel(n, pt.y);
			if(m_crBack != 0 && m_crBack != 0xFFFFFFFF)
				break;
		}

		//g_bana_log->Print("m_crBack = %X\n", m_crBack);
		pParent->ReleaseDC(pParentDC);
		m_bGetBkColor = TRUE;
	}

	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)m_HandleManager.GetBrushObject(m_crBack);
}

