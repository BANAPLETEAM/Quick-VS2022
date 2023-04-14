// MyStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyStaticText.h"


UINT CMyStaticText::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyStaticText, CStatic)
CMyStaticText::CMyStaticText()
{
	m_rgbBackGround = RGB(0, 0, 0);
	m_rgbText = RGB(0, 0, 0);
}

CMyStaticText::~CMyStaticText()
{
}


BEGIN_MESSAGE_MAP(CMyStaticText, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStaticText 메시지 처리기입니다.


void CMyStaticText::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush colorbrush;
	CRgn rgn, rgn2;
	CRect r;
	CString strText;
	int nLine = 0;

	GetWindowText(strText);

	for(int i = 0; i < strText.GetLength(); i++)
		if(strText.GetAt(i) == '\n')
			nLine++;
	
	if(nLine > 0) strText.Remove('\n');


	colorbrush.CreateSolidBrush(m_rgbBackGround);
	GetClientRect(r);

	if(m_rgbBackGround == RGB(0, 0, 0))
	{
		CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
		dc.SelectObject(pOldBrush); 
	}
	else
	{
		rgn.CreateRectRgn(r.left , r.top , r.right , r.bottom);
		dc.FillRgn(&rgn , &colorbrush);
	}

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_rgbText);
	dc.SelectObject(m_FontManager.GetFont("굴림체", 12, FW_BOLD));

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

	colorbrush.DeleteObject();
	rgn.DeleteObject();
}

BOOL CMyStaticText::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyStaticText::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyStaticText::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyStaticText::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	RedrawWindow();	
}


