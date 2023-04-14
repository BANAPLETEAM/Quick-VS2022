// FlatComboBox.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// ?998-2005 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "FlatComboBoxInsung.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatComboBoxInsung

CFlatComboBoxInsung::CFlatComboBoxInsung()
{
	m_crBack = RGB(0xff,0xff,0xff); // white
	m_crText = RGB(0x00,0x00,0x00); // black
	m_crBorder = RGB(204, 204, 204);
	m_crHotBorder = RGB(0, 198, 255);
	m_crCombo = RGB(0, 198, 255);
}

CFlatComboBoxInsung::~CFlatComboBoxInsung()
{
}

BEGIN_MESSAGE_MAP(CFlatComboBoxInsung, CXTFlatComboBox)
	//{{AFX_MSG_MAP(CFlatComboBoxInsung)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatComboBoxInsung message handlers

HBRUSH CFlatComboBoxInsung::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTFlatComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor  (m_crBack);
		pDC->SetTextColor(m_crText);
	}

	return hbr;
}

// a helper for rendering the control appearance
void CFlatComboBoxInsung::DoPaint(CDC* pDC)
{
	// draw theme.
	if (IsFlat())
	{
		// Get the client rect.
		CXTPClientRect r(this);

		// exclude client portions from redraw.
		CRect rClip(r);
		CalcClientRect(rClip);
		pDC->ExcludeClipRect(&rClip);

		// Paint to a memory device context to help
		// eliminate screen flicker.
		// 

		CXTPBufferDC memDC(*pDC, r);
		memDC.FillSolidRect(r, (m_bHasFocus || PointInRect()) ? m_crHotBorder : m_crBorder);
		r.DeflateRect(1, 1, 1, 1);
		memDC.FillSolidRect(r, m_crBack);
		r.InflateRect(1, 1, 1, 1);

		DrawCombo(&memDC, r);
	}
}

void CFlatComboBoxInsung::DrawCombo(CDC *pDC, CRect rcItem)
{
	// determine background size.
	CRect rcArrow(rcItem);
	rcArrow.left = rcArrow.right - 18;

	pDC->FillSolidRect(rcArrow.left, rcArrow.top + 1, 1, rcArrow.Height() - 2, (m_bHasFocus || PointInRect()) ? m_crHotBorder : m_crBorder);

	CPoint pt;
	pt.x = (rcArrow.left + rcArrow.right - 4) / 2 - 1;
	pt.y = (rcArrow.top + rcArrow.bottom - 2) / 2 - 1;

	COLORREF cr = IsWindowEnabled() ? m_crCombo : GetXtremeColor(COLOR_3DSHADOW);

	pDC->FillSolidRect(pt.x,		pt.y,		9, 1, cr);
	pDC->FillSolidRect(pt.x + 1,	pt.y + 1,	7, 1, cr);
	pDC->FillSolidRect(pt.x + 2,	pt.y + 2,	5, 1, cr);
	pDC->FillSolidRect(pt.x + 3,	pt.y + 3,	3, 1, cr);
	pDC->FillSolidRect(pt.x + 4,	pt.y + 4,	1, 1, cr);
}

