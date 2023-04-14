
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CFocusEditCtrl2 window



class CFocusEditCtrl2 : public CEdit
{
// Construction
public:
	CFocusEditCtrl2();
	//
	//	Use This Function To Remove Invalid Characters From 
	//	A String *BEFORE* Using SetWindowText(...).
	//
	void	StripFilteredChars( LPTSTR cpBuffer );			// Remove Bad Characters From Specified String

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusEditCtrl2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFocusEditCtrl2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFocusEditCtrl2)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP dropInfo);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnKillFocusReflect();
	afx_msg BOOL OnSetFocusReflect();
	//}}AFX_MSG

	afx_msg	LRESULT	OnPaste( WPARAM, LPARAM );				// Overidden Paste Handler
	afx_msg	LRESULT	OnCut( WPARAM, LPARAM );				// Overidden Cut Handler
	afx_msg	LRESULT	OnCopy( WPARAM, LPARAM );				// Overidden Copy Handler
	afx_msg	LRESULT	OnClear( WPARAM, LPARAM );				// Overidden Delete Handler
	afx_msg	LRESULT	OnUndo( WPARAM, LPARAM );				// Overidden Undo Handler
//	afx_msg	LRESULT	OnSelectAll( WPARAM, LPARAM );			// Overidden Select All Handler

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

	CString	m_sExcludeCharMask;								// Exclusion Character Mask
	CString	m_sIncludeCharMask;								// Inclusion Character Mask
	static HBRUSH m_hBrush;
	bool	m_bExcludeMask;									// Exclude Mask Flag
	bool	m_bIncludeMask;									// Include Mask Flag

	CString m_strTitle;
	COLORREF m_clrBk;
	COLORREF m_clrText;
	COLORREF m_clrTextNoFocus;
	COLORREF m_clrTextNoFocusHasText;
	long m_nFontSize;

	CString m_strFaceName;
	int m_nHeight;
	int m_nWeight;

	BOOL m_bInitFont;
	DWORD m_dwData;
	BOOL m_bCenter;
	BOOL m_bGradientBK;
	long m_nGradientScale;
	BOOL m_bUseNoFocusHasTextColor;

	BOOL m_bMustClrText;
	BOOL m_bMustClrBack;

private:
	CFocusEditCtrl2(const CFocusEditCtrl2& rSrc);
	CFocusEditCtrl2&		operator = (const CFocusEditCtrl2& rSrc);

public:
	virtual void OnFinalRelease();
protected:
	virtual void PreSubclassWindow();
public:

	void SetTitle(CString strTitle, BOOL bCenter = FALSE, BOOL bSetWindowText = FALSE) 
	{ 
		m_strTitle = strTitle; 
		m_bCenter = bCenter;
		if(bSetWindowText)
		{
			SetWindowText(strTitle);
		}
		RedrawWindow();
	}

	void SetFontSize(int nSize);
	void SetMyFont(CString strFaceName, int nHeight, int nWeight);

	COLORREF GetUserTextColor() {return m_clrText; }

	void SetUserBkColor(COLORREF clr, BOOL bMust = FALSE) { m_clrBk = clr; m_bMustClrBack = bMust; }
	void SetUserTextColor(COLORREF clr, BOOL bMust = FALSE) { m_clrText = clr; m_bMustClrText = bMust; }
	void SetUserTextColorNoFocus(COLORREF clr) { m_clrTextNoFocus = clr;};
	void SetUserTextColorNoFocusHasText(COLORREF clr) { m_clrTextNoFocusHasText = clr; m_bUseNoFocusHasTextColor = TRUE;};
	void SetUserOption(COLORREF clrText, COLORREF clrBk, CString strTitle = "", BOOL bCenter = FALSE,
				BOOL bSetWindowText = FALSE) 
	{ 
		m_clrText = clrText;
		m_clrBk = clrBk;
		m_strTitle = strTitle;
		m_bCenter = bCenter;

		if(bSetWindowText)
		{
			SetWindowText(strTitle);
		}
	}


	void SetItemData(DWORD dwData) { m_dwData = dwData;}

	CString GetTitle() { return m_strTitle;}
	DWORD GetItemData() { return m_dwData;}
	void SetGradientBK(BOOL bGradientBK = TRUE, long nGradientScale = 20, BOOL bRedraw = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
