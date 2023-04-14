// MyButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyDrawButton.h"

static CFont* m_pfntButton = NULL;
static LOGFONT m_lfButton = {12,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};


// CMyDrawButton

IMPLEMENT_DYNAMIC(CMyDrawButton, CButton)
CMyDrawButton::CMyDrawButton()
{
	m_clrText = RGB(0, 0, 0);
	m_clrBack = RGB(255, 255, 255);

	if(m_pfntButton == NULL)
	{
		m_pfntButton = new CFont;		
		m_pfntButton->CreateFontIndirect(&m_lfButton);
	}
	
}

CMyDrawButton::~CMyDrawButton()
{
}

BEGIN_MESSAGE_MAP(CMyDrawButton, CButton)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CMyDrawButton::OnPaint()
{ 
	CPaintDC dc(this);

	CRect rc;

	CBrush brush, *pOldBrush;
	CPen pen, pen2, *pOldPen;
	CFont *pOldFont;

	GetClientRect(rc);
	brush.CreateSolidBrush(m_clrBack);
	pen.CreatePen(PS_SOLID, 1, RGB(153,149,153));

	pOldBrush = dc.SelectObject(&brush);
	pOldPen = dc.SelectObject(&pen);
	dc.Rectangle(rc);
	rc.DeflateRect(0, 0, 1, 1);
	dc.SetPixel(rc.left, rc.top, RGB(200,200,200));
	dc.SetPixel(rc.left, rc.bottom, RGB(200,200,200));
	dc.SetPixel(rc.right, rc.top, RGB(200,200,200));
	dc.SetPixel(rc.right, rc.bottom, RGB(200,200,200));

	pen2.CreatePen(PS_SOLID, 1, RGB(223,222,223));
	dc.SelectObject(&pen2);
	dc.MoveTo(CPoint(rc.left + 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.top));

	CString strText;
	GetWindowText(strText);
	pOldFont = dc.SelectObject(m_pfntButton);
	dc.SetBkMode(TRANSPARENT);
	
	if(IsWindowEnabled())
		dc.SetTextColor(m_clrText);
	else
		dc.SetTextColor(RGB(150, 150, 150));

	dc.DrawText(strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);
	pen2.DeleteObject();
	pen.DeleteObject();
	brush.DeleteObject();
}

// CMyDrawButton 메시지 처리기입니다.

void CMyDrawButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CMyDrawButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	// Set the style to BS_OWNERDRAW.
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= ~BS_OWNERDRAW;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
}



int CMyDrawButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set the style to BS_OWNERDRAW.
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= ~BS_OWNERDRAW;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	return 0;
}
