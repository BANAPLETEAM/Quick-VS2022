// MyStatic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MyStaticRed.h"

// CMyStaticRed
UINT CMyStaticRed::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyStaticRed, CStatic)
CMyStaticRed::CMyStaticRed()
{
	m_bPoiDong = FALSE;

	m_clrBackGround = RGB(255, 230 , 230);
	m_clrText = RGB(0, 0, 0);
}

CMyStaticRed::~CMyStaticRed()
{
}


BEGIN_MESSAGE_MAP(CMyStaticRed, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStaticRed �޽��� ó�����Դϴ�.


void CMyStaticRed::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush colorbrush, blackbrush;
	CRgn rgn, rgn2;
	CRect r;
	CString strText;
	int nLine = 0;

	GetWindowText(strText);

	for(int i = 0; i < strText.GetLength(); i++)
		if(strText.GetAt(i) == '\n')
			nLine++;
	
	if(nLine > 0) strText.Remove('\n');

	if(m_bPoiDong)
	{
		//colorbrush.CreateSolidBrush(RGB(245, 155 , 140));
		//this->SetWindowText("���ص�����");
		colorbrush.CreateSolidBrush(m_clrBackGround);
	}
	else
	{
		//colorbrush.CreateSolidBrush(RGB(230, 246 , 253));
		//this->SetWindowText("���ص�");
		colorbrush.CreateSolidBrush(m_clrBackGround);
	}
	blackbrush.CreateSolidBrush(RGB(150, 150, 150));
	GetClientRect(r);
	rgn.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn , &blackbrush);
	r.DeflateRect(1, 1);
	rgn2.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn2 , &colorbrush);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_clrText);
	dc.SelectObject(m_FontManager.GetFont("����ü", 12, FW_BOLD));

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
	blackbrush.DeleteObject();
	rgn.DeleteObject();
	rgn2.DeleteObject();
}

BOOL CMyStaticRed::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyStaticRed::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyStaticRed::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyStaticRed::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	RedrawWindow();	
}


