// FlatButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "FlatButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFlatButton

IMPLEMENT_DYNAMIC(CFlatButton, CXTPButton)

CFlatButton::CFlatButton()
{
	m_nBorderGap = 2;
	m_pFont = NULL;
	m_crPushText = RGB(255, 255, 255);
	m_crPushBorder = RGB(51, 58, 66);
	m_crPushHotBorder = RGB(0, 198, 255);
	m_crPushBack = RGB(84, 96, 110);
	m_crCheckText = RGB(0, 0, 0);
	m_crCheckSelectedText = RGB(0, 198, 255);
	m_crCheckBack = RGB(255, 255, 255);
	m_crCheckBorder = RGB(204, 204, 204);
	m_crCheckHotBorder = RGB(0, 198, 255);
	m_crCheckSelected = RGB(0, 198, 255);
	m_bHasTextBackColor = FALSE;
	SetTheme(new CFlatButtonTheme);
}

CFlatButton::~CFlatButton()
{
}	


BEGIN_MESSAGE_MAP(CFlatButton, CXTPButton)
END_MESSAGE_MAP()



// CFlatButton 메시지 처리기입니다.

void CFlatButton::SetFont(CFont *pFont) 
{ 
	m_pFont = pFont;
	CWnd::SetFont(m_pFont);
}

CFont* CFlatButton::GetMyFont() const 
{ 
	if(!m_pFont)
		return m_FontManager.GetFont("맑은 고딕", 16, (GetStyle() & BS_CHECKBOX) ? FW_NORMAL : FW_BOLD);

	return m_pFont; 
}

void CFlatButton::SetPushColor(COLORREF crText, COLORREF crBack, COLORREF crBorder, COLORREF crHotBorder)
{
	m_crPushText = crText;
	m_crPushBack = crBack;
	m_crPushBorder = crBorder;
	m_crPushHotBorder = crHotBorder;
}

void CFlatButton::OnDraw(CDC* pDC)
{
	if ((GetButtonStyle() == BS_GROUPBOX))
	{
		CFont* pOldFont = pDC->SelectObject(CWnd::GetFont());
		pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
		pDC->SetBkMode(TRANSPARENT);

		DoDraw(pDC);

		pDC->SelectObject(pOldFont);
	}
	else
	{
		CXTPClientRect rc(this);
		CXTPBufferDC memDC(*pDC, rc);

		if(m_bHasTextBackColor)
		{
			memDC.FillSolidRect(rc, m_crCheckTextBack);
		}
		else
		{
			HBRUSH hBrush = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORBTN, (WPARAM)memDC.GetSafeHdc(), (LPARAM)GetSafeHwnd());
			if (hBrush)
			{
				::FillRect(memDC.GetSafeHdc(), rc, hBrush);
			}
			else
			{
				memDC.FillSolidRect(rc, GetSysColor(COLOR_3DFACE));
			}
		}

		CFont* pOldFont = memDC.SelectObject(CWnd::GetFont());
		memDC.SetBkMode(TRANSPARENT);

		DoDraw(&memDC);

		memDC.SelectObject(pOldFont);
	}
}

void CFlatButton::SetCheckTextBackColor(COLORREF crText, COLORREF crBack)
{
	m_bHasTextBackColor = TRUE;
	m_crCheckText = crText;
	m_crCheckTextBack = crBack;
	m_crCheckBack = crBack;
}

void CFlatButton::SetCheckSelectedColor(COLORREF crText, COLORREF crSelected)
{
	m_crCheckSelectedText = crText;
	m_crCheckSelected = crSelected;
	m_crCheckHotBorder = crText;
	m_crCheckBorder = crText;
}

void CFlatButton::SetCheckColor(COLORREF crText, COLORREF crBack, COLORREF crSelected)
{
	m_bHasTextBackColor = TRUE;

	if((DWORD)crText != -1)
	{
		m_crCheckText = crText;
		m_crCheckSelectedText = crText;
		m_crCheckHotBorder = crText;
		m_crCheckBorder = crText;
	}

	if((DWORD)crBack != -1)
	{
		m_crCheckTextBack = crBack;
		m_crCheckBack = crBack;
	}

	if((DWORD)crSelected != -1)
	{
		m_crCheckSelected = crSelected;
	}
}

CString CFlatButton::GetText()
{
	CString strText;
	GetWindowText(strText);
	return strText;
}

long CFlatButton::GetTextLong()
{
	CString strText;
	GetWindowText(strText);
	strText.Replace(",", "");
	return atol(strText);
}

void CFlatButton::SetWindowTextLong(long nNumber, BOOL bThousandsSep)
{
	CString strNumber;
	strNumber.Format("%ld", nNumber);
	SetWindowText(bThousandsSep ? ::GetMyNumberFormat(strNumber) : strNumber);
}