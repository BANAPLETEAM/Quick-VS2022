// MyButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyButton.h"



HBRUSH CMyButton::m_hBrush = NULL;
HPEN CMyButton::m_hPen = NULL;
HPEN CMyButton::m_hPen2 = NULL;



// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)
CMyButton::CMyButton()
{
	if(m_hBrush == NULL)
		m_hBrush = CreateSolidBrush(RGB(255, 255, 255));

	if(m_hPen == NULL)
		m_hPen = CreatePen(PS_SOLID, 1, RGB(153,149,153));

	if(m_hPen2 == NULL)
		m_hPen2 = CreatePen(PS_SOLID, 1, RGB(223,222,223));
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyButton 메시지 처리기입니다.

/*
void CMyButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	CBrush brush, *pOldBrush;
	CPen pen, pen2, *pOldPen;
	CFont *pOldFont;

	GetClientRect(rc);
	brush.CreateSolidBrush(RGB(255, 255, 255));
	pen.CreatePen(PS_SOLID, 1, RGB(153,149,153));

	pOldBrush = dc.SelectObject(&brush);
	pOldPen = dc.SelectObject(&pen);
	dc.Rectangle(rc);
	rc.DeflateRect(0, 0, 1, 1);
	dc.SetPixel(rc.left, rc.top, RGB(255,255,255));
	dc.SetPixel(rc.left, rc.bottom, RGB(255,255,255));
	dc.SetPixel(rc.right, rc.top, RGB(255,255,255));
	dc.SetPixel(rc.right, rc.bottom, RGB(255,255,255));

	pen2.CreatePen(PS_SOLID, 1, RGB(223,222,223));
	dc.SelectObject(&pen2);
	dc.MoveTo(CPoint(rc.left + 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.top));

	CString strText;
	GetWindowText(strText);
	pOldFont = dc.SelectObject(&m_Font);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);

}
*/
void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);     //Get device context object
	CRect rc;
	rc = lpDrawItemStruct->rcItem;        //Get button rect


	GetClientRect(rc);

	HBRUSH oldHbrush = (HBRUSH)dc.SelectObject(m_hBrush);
	HPEN oldhPen =  (HPEN)dc.SelectObject(m_hPen);
	dc.Rectangle(rc);
	rc.DeflateRect(0, 0, 1, 1);
	dc.SetPixel(rc.left, rc.top, RGB(200,200,200));
	dc.SetPixel(rc.left, rc.bottom, RGB(200,200,200));
	dc.SetPixel(rc.right, rc.top, RGB(200,200,200));
	dc.SetPixel(rc.right, rc.bottom, RGB(200,200,200));
	dc.SelectObject(oldhPen);

	HPEN  oldHPEN = (HPEN)dc.SelectObject(m_hPen2);
	dc.MoveTo(CPoint(rc.left + 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.top));

	UINT state = lpDrawItemStruct->itemState; //Get state of the button

	if((state & ODS_SELECTED))					// If it is pressed
		dc.DrawEdge(rc,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face

	CString strText;
	GetWindowText(strText);
	CFont* pOldFont = dc.SelectObject(m_FontManager.GetFont("돋움", 12));
	dc.SetBkMode(TRANSPARENT);
	
	if(IsWindowEnabled())
		dc.SetTextColor(RGB(0, 0, 0));
	else
		dc.SetTextColor(RGB(150, 150, 150));

	dc.DrawText(strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	
	if((state & ODS_FOCUS))       // If the button is focused
	{
		rc.DeflateRect(3, 3, 3, 3);
		dc.DrawFocusRect(rc);
	}

	
	dc.SelectObject(oldHbrush);
	dc.SelectObject(oldHPEN);
	dc.SelectObject(pOldFont);
	dc.Detach();

}

void CMyButton::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}
