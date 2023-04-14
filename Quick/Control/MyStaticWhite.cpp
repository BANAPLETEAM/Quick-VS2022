// MyStatic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MyStaticWhite.h"



// CMyStaticWhite
CFont *CMyStaticWhite::m_Font = NULL;
UINT CMyStaticWhite::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyStaticWhite, CStatic)
CMyStaticWhite::CMyStaticWhite()
{
	if(m_RefCnt++ == 0) 
		m_Font = m_FontManager.GetFont("����ü", FW_BOLD, 13);

	m_bPoiDong = FALSE;
}

CMyStaticWhite::~CMyStaticWhite()
{
	if(--m_RefCnt == 0)
	{
		delete m_Font;
	}
}


BEGIN_MESSAGE_MAP(CMyStaticWhite, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStaticWhite �޽��� ó�����Դϴ�.


void CMyStaticWhite::OnPaint()
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
		colorbrush.CreateSolidBrush(RGB(255, 255 , 255));
		//colorbrush.CreateSolidBrush(RGB(245, 155 , 140));
		//this->SetWindowText("���ص�����");
	}
	else
	{
		colorbrush.CreateSolidBrush(RGB(255, 255 , 255));
		//colorbrush.CreateSolidBrush(RGB(230, 246 , 253));
		//this->SetWindowText("���ص�");
	}
	blackbrush.CreateSolidBrush(RGB(150, 150, 150));
	GetClientRect(r);
	rgn.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn , &blackbrush);
	r.DeflateRect(1, 1);
	rgn2.CreateRectRgn(r.left , r.top , r.right , r.bottom);
	dc.FillRgn(&rgn2 , &colorbrush);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SelectObject(m_Font);

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

BOOL CMyStaticWhite::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyStaticWhite::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyStaticWhite::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyStaticWhite::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	//RedrawWindow();	
}


