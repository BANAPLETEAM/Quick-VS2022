// MyStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyGiveStatic.h"

// CMyGiveStatic
UINT CMyGiveStatic::m_RefCnt = 0;

IMPLEMENT_DYNAMIC(CMyGiveStatic, CStatic)
CMyGiveStatic::CMyGiveStatic()
{
	m_clrText = RGB(255, 0, 0);
}

CMyGiveStatic::~CMyGiveStatic()
{
}


BEGIN_MESSAGE_MAP(CMyGiveStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyGiveStatic 메시지 처리기입니다.


void CMyGiveStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect r;
	CString strText;
	int nLine = 0;

	GetWindowText(strText);

	for(int i = 0; i < strText.GetLength(); i++)
		if(strText.GetAt(i) == '\n')
			nLine++;
	
	if(nLine > 0) strText.Remove('\n');

	GetClientRect(r);
	dc.FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 0, 0));
	r.DeflateRect(1, 1, 2, 2);
	dc.FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 255 , 255));

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_clrText);
	CFont* pOldFont = dc.SelectObject(m_FontManager.GetFont("굴림체", 13, FW_BOLD));

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

	dc.SelectObject(pOldFont);
}

BOOL CMyGiveStatic::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}


void CMyGiveStatic::PreSubclassWindow()
{
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	rc.InflateRect(1, 1, 1, 1);
	MoveWindow(rc);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

void CMyGiveStatic::OnFinalRelease()
{
	CStatic::OnFinalRelease();
}

void CMyGiveStatic::SetWindowText(CString strText)
{
	CStatic::SetWindowText(strText);
	RedrawWindow();	
}


