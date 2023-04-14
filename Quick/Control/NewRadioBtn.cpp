// NewRadioBtn.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "NewRadioBtn.h"





HBRUSH CNewRadioBtn::m_hBrush1 = NULL;
HBRUSH CNewRadioBtn::m_hBrush2 = NULL;
HPEN CNewRadioBtn::m_hPen = NULL;
HPEN CNewRadioBtn::m_hPen2 = NULL;


// CNewRadioBtn

IMPLEMENT_DYNAMIC(CNewRadioBtn, CButton)
CNewRadioBtn::CNewRadioBtn()
{
	m_bChecked = 0;

	if(m_hBrush1 == NULL)
		m_hBrush1 = CreateSolidBrush(RGB(140, 140, 255));

	if(m_hBrush2 == NULL)
		m_hBrush2 = CreateSolidBrush(RGB(255, 255, 255));


	if(m_hPen == NULL)
		m_hPen = CreatePen(PS_SOLID, 1, RGB(153,149,153));

	if(m_hPen2 == NULL)
		m_hPen2 = CreatePen(PS_SOLID, 1, RGB(223,222,223));

}

CNewRadioBtn::~CNewRadioBtn()
{
}


BEGIN_MESSAGE_MAP(CNewRadioBtn, CButton)
END_MESSAGE_MAP()



// CNewRadioBtn 메시지 처리기입니다.
void CNewRadioBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);     //Get device context object
	CRect rc;
	rc = lpDrawItemStruct->rcItem;        //Get button rect


	GetClientRect(rc);

	HBRUSH hOldBrush ;
	if(m_bChecked)
		hOldBrush = (HBRUSH)dc.SelectObject(m_hBrush1);
	else
		hOldBrush = (HBRUSH)dc.SelectObject(m_hBrush2);


	HPEN oldhPen = (HPEN)dc.SelectObject(m_hPen);
	dc.Rectangle(rc);
	rc.DeflateRect(0, 0, 1, 1);
	dc.SetPixel(rc.left, rc.top, RGB(255,255,255));
	dc.SetPixel(rc.left, rc.bottom, RGB(255,255,255));
	dc.SetPixel(rc.right, rc.top, RGB(255,255,255));
	dc.SetPixel(rc.right, rc.bottom, RGB(255,255,255));
	dc.SelectObject(oldhPen);

	oldhPen = (HPEN)dc.SelectObject(m_hPen2);
	dc.MoveTo(CPoint(rc.left + 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.bottom - 1));
	dc.LineTo(CPoint(rc.right - 1, rc.top));

	UINT state = lpDrawItemStruct->itemState; //Get state of the button

	if((state & ODS_SELECTED))					// If it is pressed
		dc.DrawEdge(rc,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face

	CString strText;
	GetWindowText(strText);
	CFont* poldFont = dc.SelectObject(m_FontManager.GetFont("굴림", 12));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	
	if((state & ODS_FOCUS))       // If the button is focused
	{
		rc.DeflateRect(3, 3, 3, 3);
		dc.DrawFocusRect(rc);
	}

	dc.SelectObject(hOldBrush);
	dc.SelectObject(oldhPen);
	dc.SelectObject(poldFont);
	dc.Detach();
}

BOOL CNewRadioBtn::PreCreateWindow(CREATESTRUCT& cs)
{
	return CButton::PreCreateWindow(cs);
}

void CNewRadioBtn::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}
