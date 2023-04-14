// MyStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyStaticGreen.h"

// CMyStaticGreen
UINT CMyStaticGreen::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyStaticGreen, CStatic)
CMyStaticGreen::CMyStaticGreen()
{
	m_bPoiDong = FALSE;
}

CMyStaticGreen::~CMyStaticGreen()
{
}


BEGIN_MESSAGE_MAP(CMyStaticGreen, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStaticGreen 메시지 처리기입니다.


void CMyStaticGreen::OnPaint()
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
		colorbrush.CreateSolidBrush(RGB(230, 255 , 230));
		//colorbrush.CreateSolidBrush(RGB(245, 155 , 140));
		//this->SetWindowText("기준동오류");
	}
	else
	{
		colorbrush.CreateSolidBrush(RGB(230, 255 , 230));
		//colorbrush.CreateSolidBrush(RGB(230, 246 , 253));
		//this->SetWindowText("기준동");
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
	CFont* pOldFont = dc.SelectObject(m_FontManager.GetFont("굴림체", 12, FW_BOLD));

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
	dc.SelectObject(pOldFont);
}

BOOL CMyStaticGreen::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyStaticGreen::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyStaticGreen::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyStaticGreen::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	RedrawWindow();	
}


