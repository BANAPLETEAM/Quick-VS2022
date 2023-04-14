// MyStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyStaticBlue.h"

// CMyStaticTri
UINT CMyStaticTri::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyStaticTri, CStatic)
CMyStaticTri::CMyStaticTri()
{
	m_bPoiDong = FALSE;
	m_rgbBorder = RGB(0, 128, 255);
	m_rgbText = RGB(0, 0, 0);
}

CMyStaticTri::~CMyStaticTri()
{
}


BEGIN_MESSAGE_MAP(CMyStaticTri, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStaticTri 메시지 처리기입니다.


void CMyStaticTri::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush colorbrush, blackbrush;
	CRgn rgn, rgn2;
	CRect r, r3;
	CString strText;
	int nLine = 0;

	GetWindowText(strText);

	for(int i = 0; i < strText.GetLength(); i++)
		if(strText.GetAt(i) == '\n')
			nLine++;
	
	if(nLine > 0) strText.Remove('\n');

	colorbrush.CreateSolidBrush(RGB(255, 255 , 255));

	blackbrush.CreateSolidBrush(m_rgbBorder);
	GetClientRect(r);
	r3 = r;
	rgn.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn , &blackbrush);
	r.DeflateRect(1, 1);
	rgn2.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn2 , &colorbrush);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_rgbText);
	dc.SelectObject(m_FontManager.GetFont("굴림체", 12, FW_NORMAL));

	if(nLine == 0) {
		dc.DrawText(strText, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	else {
		nLine++;
		for(int i = 0; i < nLine; i++)
		{
			CRect r2;
			r2.CopyRect(r);
			r2.top = i * (int)(r.Height() / nLine) + 10;
			r2.bottom = (i + 1) * (int)(r.Height() / nLine) + 10;
			dc.DrawText(strText.Mid(i * 2, 2), r2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}

	CPen pen(PS_SOLID, 1, m_rgbBorder);
	CPen* pOldPen = dc.SelectObject(&pen);

	for(int i=0; i<8; i++) 
	{				 
		dc.MoveTo(r3.left + i, r3.top);
		dc.LineTo(r3.left, r3.top + i); 
		//dc.MoveTo(r.right - i,r.top);
		//dc.LineTo(r.right, r.top + i); 
	}

	dc.SelectObject(pOldPen);

	colorbrush.DeleteObject();
	blackbrush.DeleteObject();
	rgn.DeleteObject();
	rgn2.DeleteObject();
}

BOOL CMyStaticTri::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyStaticTri::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyStaticTri::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyStaticTri::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	RedrawWindow();	
}


