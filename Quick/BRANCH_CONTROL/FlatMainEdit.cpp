// FlatMainEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FlatMainEdit.h"
#include "BranchSel.h"

// CFlatMainEdit

IMPLEMENT_DYNAMIC(CFlatMainEdit, CEdit)

CFlatMainEdit::CFlatMainEdit()
{
	m_pParent = NULL;
}

CFlatMainEdit::~CFlatMainEdit()
{
}


BEGIN_MESSAGE_MAP(CFlatMainEdit, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CFlatMainEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFlatEdit2::OnLButtonDown(nFlags, point);
	m_pParent->OpenMainListDlg();
}

void CFlatMainEdit::OnPaint()
{ 
	CFocusEditCtrl2::OnPaint();
}

BOOL CFlatMainEdit::OnEraseBkgnd(CDC* pDC)
{
	return CFlatEdit2::OnEraseBkgnd(pDC);
}
