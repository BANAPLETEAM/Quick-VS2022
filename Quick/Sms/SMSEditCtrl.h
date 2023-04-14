#if !defined(AFX_SMSEditCTRL_H__9CECF3E6_5C4C_11D2_90CC_00104B2C8FCC__INCLUDED_)
#define AFX_SMSEditCTRL_H__9CECF3E6_5C4C_11D2_90CC_00104B2C8FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*|*\
|*|  File:      SMSEditCtrl.h
|*|  
|*|  By:        James R. Twine, Rubin And Associates, Inc.
|*|             Copyright 1988, Rubin And Associates, Inc.
|*|  Date:      Friday, October 09, 1998
|*|             
|*|             This implementes an Edit Control that provides
|*|             a custom background color to indicate focus.
|*|             (This class uses static variables for the colors,
|*|             so all controls that uses this class will use the
|*|             same colors).
|*|				Portions of this code are derived from CDropEdit
|*|				by Chris Losinger.  (See comments below)
|*|             
|*|             These Changes May Be Freely Incorporated Into 
|*|             Projects Of Any Type Subject To The Following 
|*|             Conditions:
|*|             
|*|             o This Header Must Remain In This File, And Any
|*|               Files Derived From It
|*|             o Do Not Misrepresent The Origin Of Any Parts Of 
|*|               This Code (IOW, Do Not Claim You Wrote It)
|*|             
|*|             A "Mention In The Credits", Or Similar Acknowledgement,
|*|             Is *NOT* Required.  It Would Be Nice, Though! :)
|*|             
|*|  Revisions: 
|*|             xx/xx/99 Incorporated The Ability To "Filter" The Input.
|*|	
\*|*/
//	CDropEdit
//	Copyright 1997 Chris Losinger
//
//	This code is freely distributable and modifiable, as long as credit
//	is given to where it's due. Watch, I'll demonstrate :
//
//	shortcut expansion code modified from :
//	CShortcut, 1996 Rob Warner

/////////////////////////////////////////////////////////////////////////////
// CSMSEditCtrl window


class CSMSEditCtrl : public CEdit
{
// Construction
public:
	CSMSEditCtrl();
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
	//{{AFX_VIRTUAL(CSMSEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSMSEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSMSEditCtrl)
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

	DECLARE_MESSAGE_MAP()

	CString	m_sExcludeCharMask;								// Exclusion Character Mask
	CString	m_sIncludeCharMask;								// Inclusion Character Mask
	CBrush	m_brBGBrush;									// Background Brush
	bool	m_bExcludeMask;									// Exclude Mask Flag
	bool	m_bIncludeMask;									// Include Mask Flag

	CFont m_font;
	

private:
	CSMSEditCtrl(const CSMSEditCtrl& rSrc);
	CSMSEditCtrl&		operator = (const CSMSEditCtrl& rSrc);

public:
	virtual void OnFinalRelease();
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	void SetFontSize(int nSize);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSEditCTRL_H__9CECF3E6_5C4C_11D2_90CC_00104B2C8FCC__INCLUDED_)
