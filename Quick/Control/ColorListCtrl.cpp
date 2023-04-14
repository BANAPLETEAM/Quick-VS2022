// ColorListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl

CColorListCtrl::CColorListCtrl()
{
}

CColorListCtrl::~CColorListCtrl()
{
}

bool CColorListCtrl::IsDraw() {
	return true;
}

bool CColorListCtrl::IsNotifyItemDraw() {
	return true;
}

bool CColorListCtrl::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) {
	return true;
}

COLORREF CColorListCtrl::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/) 
{
	COLOR_STRUCT *pCS = (COLOR_STRUCT*)GetItemData(nItem);
	if(pCS != NULL) return pCS->crText;
	else return RGB(0,0,0);
}

COLORREF CColorListCtrl::BkColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	COLOR_STRUCT *pCS = (COLOR_STRUCT*)GetItemData(nItem);
	if(pCS != NULL) return pCS->crBk;
	else return RGB(255,255,255);
}


BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrlWithCustomDraw)
	//{{AFX_MSG_MAP(CColorListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnLvnDeleteallitems)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnLvnDeleteitem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl message handlers

BOOL CColorListCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect r;
	GetClientRect(r);
	CBrush brush(RGB(255,255,255));	// cyan
	pDC->FillRect(r,&brush);
	return false; // do default drawing as well
}

void CColorListCtrl::OnLvnDeleteallitems(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	for(int i = 0; i < GetItemCount(); i++)
	{
		COLOR_STRUCT *pCS = (COLOR_STRUCT*) GetItemData(i);
		if(pCS != NULL) delete pCS;
	}

	*pResult = 0;
}

void CColorListCtrl::OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

//	COLOR_STRUCT *pCS = (COLOR_STRUCT*) GetItemData(pNMLV->iItem);
//	if(pCS != NULL) delete pCS;

	*pResult = 0;
}
