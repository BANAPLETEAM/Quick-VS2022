// FlatSubEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FlatSubEdit.h"
#include "BranchSel.h"
// CFlatSubEdit

IMPLEMENT_DYNAMIC(CFlatSubEdit, CEdit)

CFlatSubEdit::CFlatSubEdit()
{
	m_pParent = NULL;
}

CFlatSubEdit::~CFlatSubEdit()
{
}


BEGIN_MESSAGE_MAP(CFlatSubEdit, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CFlatSubEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pParent->OpenSubListDlg();

	CFlatEdit2::OnLButtonDown(nFlags, point);
}

void CFlatSubEdit::OnPaint()
{ 
	CFocusEditCtrl2::OnPaint();
}

BOOL CFlatSubEdit::OnEraseBkgnd(CDC* pDC)
{
	return CFlatEdit2::OnEraseBkgnd(pDC);
}


BOOL CFlatSubEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == this->GetSafeHwnd())
			m_pParent->OpenSubListDlg();
	}

	return CFlatEdit2::PreTranslateMessage(pMsg);
}
