#pragma once

// MyListCtrl9.h : header file
//`

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl9 window

#include "ListCtrlWithCustomDraw.h"


class CMyListCtrl9 : public CListCtrlWithCustomDraw
{
// Construction
public:
	CMyListCtrl9();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl9)
	//}}AFX_VIRTUAL
	virtual bool IsDraw();
	virtual bool IsNotifyItemDraw();
	virtual bool IsNotifySubItemDraw(int nItem, UINT nState, LPARAM lParam);
	virtual COLORREF TextColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual COLORREF BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);

// Implementation
public:
	virtual ~CMyListCtrl9();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl9)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		//afx_msg BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


