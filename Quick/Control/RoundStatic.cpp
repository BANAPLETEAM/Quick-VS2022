// RoundStatic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RoundStatic.h"


// CRoundStatic

IMPLEMENT_DYNAMIC(CRoundStatic, CStatic)
CRoundStatic::CRoundStatic()
{
}

CRoundStatic::~CRoundStatic()
{
}


BEGIN_MESSAGE_MAP(CRoundStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CRoundStatic �޽��� ó�����Դϴ�.


void CRoundStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBrush colorbrush, blackbrush;
	CRgn rgn, rgn2;
	CRect r;
	CString strText;

	GetWindowText(strText);

	GetClientRect(r);
	rgn.CreateRoundRectRgn( r.left , r.top , r.right , r.bottom, 10, 10 );
	dc.FillRgn(&rgn , CBrush::FromHandle(m_HandleManager.GetBrushObject(RGB(132, 130, 132))));
	r.DeflateRect(1, 1);
	rgn2.CreateRoundRectRgn( r.left , r.top , r.right , r.bottom, 10, 10 );
	dc.FillRgn(&rgn2 , CBrush::FromHandle(m_HandleManager.GetBrushObject(RGB(222, 219 , 214))));

	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_FontManager.GetFont("����ü", 13));
	dc.DrawText(strText, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	DeleteObject(&rgn);
	DeleteObject(&rgn2);
}

