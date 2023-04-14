// FlatComboBox.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// ?998-2005 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATCOMBOBOX_H__54D57830_4382_47C7_992E_77F364993544__INCLUDED_111)
#define AFX_FLATCOMBOBOX_H__54D57830_4382_47C7_992E_77F364993544__INCLUDED_111

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 
/////////////////////////////////////////////////////////////////////////////
// CFlatComboBoxInsung window

class CFlatComboBoxInsung : public CXTFlatComboBox
{
// Construction
public:
	CFlatComboBoxInsung();

// Attributes
public:

// Operations
public:

	COLORREF m_crBack;
	COLORREF m_crText;
	COLORREF m_crBorder;
	COLORREF m_crHotBorder;
	COLORREF m_crCombo;


	void SetColor(COLORREF crText = -1, 
					COLORREF crBack = -1, 
					COLORREF crBorder = -1, 
					COLORREF crHotBorder = -1, 
					COLORREF crCombo = -1)
	{
		if((int)crText != -1)
			m_crText = crText;

		if((int)crBack != -1)
			m_crBack = crBack;

		if((int)crBorder != -1)
			m_crBorder = crBorder;
	
		if((int)crHotBorder != -1)
			m_crHotBorder = crHotBorder;
	
		if((int)crCombo != -1)
			m_crCombo = crCombo;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboBoxInsung)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatComboBoxInsung();
	virtual void DoPaint(CDC* pDC);

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlatComboBoxInsung)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void DrawCombo(CDC *pDC, CRect rcItem);


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBOBOX_H__54D57830_4382_47C7_992E_77F364993544__INCLUDED_)
