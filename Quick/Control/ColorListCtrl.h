#if !defined(AFX_COLORLIST_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_)
#define AFX_COLORLIST_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

#include "ListCtrlWithCustomDraw.h"

typedef struct {
	COLORREF crText;
	COLORREF crBk;
} COLOR_STRUCT;

class CColorListCtrl : public CListCtrlWithCustomDraw
{
// Construction
public:
	CColorListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListCtrl)
	//}}AFX_VIRTUAL
	virtual bool IsDraw();
	virtual bool IsNotifyItemDraw();
	virtual bool IsNotifySubItemDraw(int nItem, UINT nState, LPARAM lParam);
	virtual COLORREF TextColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual COLORREF BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);

// Implementation
public:
	virtual ~CColorListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnDeleteallitems(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLIST_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_)
