// MyStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"

// CMyStatic
UINT CMyStatic::m_RefCnt = 0;
COLORREF clrDefaultBk = RGB(0, 0, 0);


IMPLEMENT_DYNAMIC(CMyStatic, CStatic)
CMyStatic::CMyStatic()
{
	m_clrText = RGB(0, 0, 0);
	m_clrBack = clrDefaultBk;
	m_bSelected = FALSE;
	m_bEnableClick = FALSE;
	m_bMakeLine = FALSE;
	//m_rcLast = CRect(-1, -1, -1, -1);

	m_nAlign = DT_CENTER;
	m_pfontText = NULL;
	m_nLeftMargin = 0;
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_PAINT()
	//ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT(STN_CLICKED, OnStnClicked)
END_MESSAGE_MAP()



// CMyStatic 메시지 처리기입니다.


void CMyStatic::OnPaint()
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

	if(m_bMakeLine)
	{
		CBrush colorbrush, blackbrush;
		CRgn rgn, rgn2;

		blackbrush.CreateSolidBrush(RGB(150, 150, 150));
		rgn.CreateRectRgn(r.left , r.top , r.right , r.bottom);
		dc.FillRgn(&rgn , &blackbrush);
		r.DeflateRect(1, 1);
		rgn2.CreateRectRgn(r.left , r.top , r.right , r.bottom);
		dc.FillRgn(&rgn2 , &colorbrush);
	}

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_clrText);
	if(m_clrBack != clrDefaultBk)
		dc.FillSolidRect(r, m_clrBack);

	CFont* pOldFont = NULL;

	if(m_pfontText)
		pOldFont = dc.SelectObject(m_pfontText);
	else
		pOldFont = dc.SelectObject(m_FontManager.GetFont("Tahoma", 14, FW_NORMAL));

	if(nLine == 0) {

		if(m_nAlign == DT_LEFT && m_nLeftMargin > 0)
		{ 
			r.left += m_nLeftMargin;
			dc.DrawText(strText, r, DT_SINGLELINE | m_nAlign | DT_VCENTER);
		}
		else
			dc.DrawText(strText, r, DT_SINGLELINE | m_nAlign | DT_VCENTER);
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

void CMyStatic::PreSubclassWindow()
{
	ModifyStyleEx(WS_EX_STATICEDGE, WS_EX_TRANSPARENT);
	ModifyStyle(NULL, SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

void CMyStatic::OnStnClicked()
{
	if(m_bEnableClick)
	{
		m_bSelected = !m_bSelected;
		RefreshState();
	}

	GetParent()->PostMessage(WM_MY_STATIC_CLICK, GetDlgCtrlID(), NULL);
}

void CMyStatic::RefreshState()
{
	if(m_bEnableClick)
	{
		SetBkColor(m_bSelected ? RGB(255, 200, 200) : clrDefaultBk);
		RedrawWindow();
	}
}

/*
BOOL CMyStatic::OnEraseBkgnd(CDC* pDC)
{

	CDC MemDC;
	CRect rc;
	GetWindowRect(&rc);
	CWnd *pParent = GetParent();

	if(!m_rcLast.EqualRect(rc))
	{
		if(m_bmpBack.GetSafeHandle())
			m_bmpBack.DeleteObject();
	}

	pParent->ScreenToClient(&rc);
	if(m_bmpBack.GetSafeHandle() == NULL)
	{
		CDC *pParentDC = pParent->GetDC();
		MemDC.CreateCompatibleDC(pParentDC);
		m_bmpBack.CreateCompatibleBitmap(pParentDC, rc.Width(), rc.Height());
		CBitmap *pOldBmp = MemDC.SelectObject(&m_bmpBack);
		MemDC.BitBlt(0, 0, rc.Width(), rc.Height(), pParentDC, rc.left, rc.top, SRCCOPY);
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBmp);
		pParent->ReleaseDC(pParentDC);
		GetWindowRect(&m_rcLast);
	}
	else
	{
		MemDC.CreateCompatibleDC(pDC);
		CBitmap *pOldBmp = MemDC.SelectObject(&m_bmpBack);
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBmp);
	}

	MemDC.DeleteDC();	
	return FALSE;
}
*/

void CMyStatic::SetWindowText(LPCTSTR lpszString)
{
	CRect rc;
	GetWindowRect(&rc);
	CWnd *pParent = GetParent();
	if(pParent)
	{
		pParent->ScreenToClient(rc);
		pParent->InvalidateRect(rc, 1);
	}

	CStatic::SetWindowText(lpszString);
	Invalidate();
}
