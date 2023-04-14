#if !defined(AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_90ABC6341C92__INCLUDED_)
#define AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_90ABC6341C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl4 window

#include "ListCtrlWithCustomDraw.h"


class CMyListCtrl4 : public CListCtrlWithCustomDraw
{
// Construction
public:
	CMyListCtrl4();

protected:
	long m_nCompanyCode;
	long m_nDOrderCompany;
	long m_bIntegrated;

// Attributes
public:
	void SetCompanyCode(long nCompany)
	{ m_nCompanyCode = nCompany; }
	void SetDOrderCompany(long nCompany) 
	{ m_nDOrderCompany = nCompany; }
	void SetIntegrated(BOOL bIntegrated)
	{ m_bIntegrated = bIntegrated; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl4)
	//}}AFX_VIRTUAL
	virtual bool IsDraw();
	virtual bool IsNotifyItemDraw();
	virtual bool IsNotifySubItemDraw(int nItem, UINT nState, LPARAM lParam);
	virtual COLORREF TextColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual COLORREF BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);

// Implementation
public:
	virtual ~CMyListCtrl4();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl4)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	WCHAR *m_pwchTip;
	TCHAR *m_pchTip;
	BOOL m_bToolTipCtrlCustomizeDone;

	int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	BOOL OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_90ABC6341C92__INCLUDED_)
