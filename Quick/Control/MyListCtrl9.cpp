// MyListCtrl9.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyListCtrl9.h"
#include "RcpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl9

CMyListCtrl9::CMyListCtrl9()
{

}

CMyListCtrl9::~CMyListCtrl9()
{
}

bool CMyListCtrl9::IsDraw() {
	return true;
}

bool CMyListCtrl9::IsNotifyItemDraw() {
	return true;
}

bool CMyListCtrl9::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) {
	return true;
}


COLORREF CMyListCtrl9::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/) 
{
/*
	if(GetItemText(nItem, nSubItem) == "O")
		return RGB(255, 255, 255);
	else if(GetItemText(nItem, nSubItem) == "X")
		return RGB(255, 255, 255);
*/
	return RGB(0, 0, 0);
}

COLORREF CMyListCtrl9::BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM /*lParam*/)
{
	if((nItem / 2) % 2 == 0)
		return RGB(255, 255, 220);
	else
		return RGB(255, 255, 255);
}



BEGIN_MESSAGE_MAP(CMyListCtrl9, CListCtrlWithCustomDraw)
	//{{AFX_MSG_MAP(CMyListCtrl9)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl9 message handlers

BOOL CMyListCtrl9::OnEraseBkgnd(CDC* pDC)
{
	CRect r;
	GetClientRect(r);
	CBrush brush(RGB(255,255,255));	
	pDC->FillRect(r,&brush);
	return false; // do default drawing as well
}


// Detects column resizing.
/*
BOOL CMyListCtrl9::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	LPNMHEADER pNMHD = (LPNMHEADER)lParam;

	switch(pNMHD->hdr.code)
	{
		case HDN_ITEMCHANGEDA:
		case HDN_ITEMCHANGEDW:
			BOOL bRes;
			bRes = CListCtrl::OnNotify(wParam, lParam, pResult);
			//m_Header.RecalcToolRect();
			return bRes;
	}
	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}
*/