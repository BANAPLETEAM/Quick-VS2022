#if !defined(AFX_LISTCTRLWITHCUSTOMDRAW_H__AA70C396_EC02_4103_BD7D_3CCEDE0E1C65__INCLUDED_)
#define AFX_LISTCTRLWITHCUSTOMDRAW_H__AA70C396_EC02_4103_BD7D_3CCEDE0E1C65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlWithCustomDraw.h : header file
//

#include "SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlWithCustomDraw window

class CListCtrlWithCustomDraw : public CSortListCtrl
{
	// Construction
public:
	CListCtrlWithCustomDraw();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlWithCustomDraw)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CListCtrlWithCustomDraw();

protected:
	CFont* m_pOldItemFont;
	CFont* m_pOldSubItemFont;

	//
	// Callbacks for whole control
	//
	
	// do we want to do the drawing ourselves?
	virtual bool IsDraw() { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual bool OnDraw(CDC* /*pDC*/) { return false; }
	// do we want to handle custom draw for
	// individual items
	virtual bool IsNotifyItemDraw() { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual bool IsNotifyPostPaint() { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual bool IsPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual bool OnPostDraw(CDC* /*pDC*/) { return false; }
	
	//
	// Callbacks for each item
	//
	
	// return a pointer to the font to use for this item.
	// return NULL to use default
	virtual CFont* FontForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return NULL; }
	// return the text color to use for this item
	// return CLR_DEFAULT to use default
	virtual COLORREF TextColorForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// return the background color to use for this item
	// return CLR_DEFAULT to use default
	virtual COLORREF BkColorForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// do we want to do the drawing for this item ourselves?
	virtual bool IsItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual bool OnItemDraw(CDC* /*pDC*/, int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to handle custom draw for
	// individual sub items
	virtual bool IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual bool IsNotifyItemPostPaint(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual bool IsItemPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual bool OnItemPostDraw(CDC* /*pDC*/, int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }

	//
	// Callbacks for each sub item
	//
	
	// return a pointer to the font to use for this sub item.
	// return NULL to use default
	virtual CFont* FontForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return NULL; }
	// return the text color to use for this sub item
	// return CLR_DEFAULT to use default
	virtual COLORREF TextColorForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// return the background color to use for this sub item
	// return CLR_DEFAULT to use default
	virtual COLORREF BkColorForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// do we want to do the drawing for this sub item ourselves?
	virtual bool IsSubItemDraw(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual bool OnSubItemDraw(CDC* /*pDC*/, int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual bool IsNotifySubItemPostPaint(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual bool IsSubItemPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual bool OnSubItemPostDraw(CDC* /*pDC*/, int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlWithCustomDraw)
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLWITHCUSTOMDRAW_H__AA70C396_EC02_4103_BD7D_3CCEDE0E1C65__INCLUDED_)
