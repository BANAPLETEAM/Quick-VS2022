#if !defined(AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_)
#define AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

#include "ListCtrlWithCustomDraw.h"


typedef struct {
	int nState;
	long nTNo;
	int nCarType;
	CString strCName;
	int nCompany;
	int nRiderCompany;
	COleDateTime dtRcp;
	int nShareLevel;
	BOOL bCross;
	int nStartSection;
	int nRNo;
} ItemBaseInfo;



class CMyListCtrl : public CListCtrlWithCustomDraw
{
// Construction
public:
	CMyListCtrl();

protected:
	long m_nCompanyCode;
	long m_nDOrderCompany;
	long m_bIntegrated;
	long m_nRcpTimeCol;
	long m_nStartCol;
	long m_nRcpTimeColor1;
	long m_nRcpTimeColor2;
	long m_nRcpTimeColor3;

// Attributes
public:
	void SetCompanyCode(long nCompany)
	{ m_nCompanyCode = nCompany; }
	void SetDOrderCompany(long nCompany) 
	{ m_nDOrderCompany = nCompany; }
	void SetIntegrated(BOOL bIntegrated)
	{ m_bIntegrated = bIntegrated; }
	void SetRcpTimeCol(long nCol)
	{ m_nRcpTimeCol = nCol; }
	void SetStartCol(long nCol)
	{ m_nStartCol = nCol; }

	void SetRcpTimeColor(long one, long two, long three)
	{
		m_nRcpTimeColor1 = one;
		m_nRcpTimeColor2 = two;
		m_nRcpTimeColor3 = three;
	}

    
// Operations
public:
	enum STATE{
		STATE_INTERNET		= 2,
		STATE_SITE			= 3,
		STATE_CARRY			= 5,
		STATE_WAIT			= 8,
		STATE_RESERVED		= 9,
		STATE_OK			= 10,
		STATE_OK_ONLY_MAN	= 11,
		STATE_ALLOCATED		= 30,
		STATE_FINISH		= 35,
		STATE_CANCELED		= 40
	};


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL
	virtual bool IsDraw();
	virtual bool IsNotifyItemDraw();
	virtual bool IsNotifySubItemDraw(int nItem, UINT nState, LPARAM lParam);
	virtual COLORREF TextColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual COLORREF BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
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

#endif // !defined(AFX_MYLISTCTRL_H__CB326412_CA34_4365_8571_70ABC6341C92__INCLUDED_)
