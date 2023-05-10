// FlatBranchEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FlatBranchEdit.h"
#include "BranchSel.h"

// CFlatBranchEdit

IMPLEMENT_DYNAMIC(CFlatBranchEdit, CEdit)

CFlatBranchEdit::CFlatBranchEdit()
{
	m_pParent = NULL;
}

CFlatBranchEdit::~CFlatBranchEdit()
{
}


BEGIN_MESSAGE_MAP(CFlatBranchEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CFlatBranchEdit::OnEnChange)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CFlatBranchEdit::OnEnKillfocus)
END_MESSAGE_MAP()



// CFlatBranchEdit 메시지 처리기입니다.



void CFlatBranchEdit::OnEnChange()
{
	CString strSearch; GetWindowText(strSearch);

	m_pParent->SearchBranch(strSearch);
}

void CFlatBranchEdit::OnLButtonDown(UINT nFlags, CPoint point)
{    
	OnEnChange();
	m_pParent->OpenAllBranchListDlg(); 
	CFlatEdit2::OnLButtonDown(nFlags, point);
}

void CFlatBranchEdit::OnPaint()
{ 
	CFocusEditCtrl2::OnPaint();
}

BOOL CFlatBranchEdit::OnEraseBkgnd(CDC* pDC)
{
	return CFlatEdit2::OnEraseBkgnd(pDC);
}

void CFlatBranchEdit::OnEnKillfocus()
{
	//m_pParent->HideDlg();
}

BOOL CFlatBranchEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == this->GetSafeHwnd()) 
		{
			//	m_pParent->OpenAllBranchListDlg();
		}
		
	}

	return CFlatEdit2::PreTranslateMessage(pMsg);
}
