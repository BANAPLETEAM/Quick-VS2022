#if !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrl.h : header file
//

#include "MyListCtrl9.h"

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl window

class gxListCtrl : public CMyListCtrl9
{
public:
			gxListCtrl (CString Text = "");
    virtual ~gxListCtrl();

    CString DefaultText;

    CEdit*  EditSubItem (int Item, int Column);
    int	    HitTestEx (CPoint& Point, int* Column);
    int	    InsertItemEx (int Item);
    void    Resize (int cx, int cy);

	void	SetDisableCol(int nCol)
	{ m_bDisableCol[nCol] = TRUE; };
		
    
    //{{AFX_VIRTUAL(gxListCtrl)
	virtual BOOL EndLabelEdit(LV_ITEM *plvItem);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(gxListCtrl)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
	BOOL	m_bDisableCol[MAX_PATH];
	int		m_nLastEditRow;
	int		m_nLastEditCol;
	BOOL	m_bEditing;


public:
	
	int InsertItemEx2(int Item);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
