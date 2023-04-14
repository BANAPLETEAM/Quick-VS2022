#pragma once

//FlatStatic이 아니고 배경색없애는 TransparentStatic인데
//네이밍 맞출려고 이름 Flat으로 정했임

// CFlatStatic

class CFlatStatic : public CStatic
{
	DECLARE_DYNAMIC(CFlatStatic)

	CFlatStatic();

	// Attributes
private:
	COLORREF m_clrText;
	COLORREF m_clrBack;
	CBrush m_hBrush;
	BOOL m_bAutoAddSpace;
	BOOL m_bAddedSpace;

	// Operations
public:
	void SetTextColor(COLORREF col);
	void SetBackColor(COLORREF col);
	CString GetText();
	long GetTextLong();
	void SetWindowTextLong(long nNumber, BOOL bThousandsSep = FALSE);
	void SetWindowText(LPCTSTR lpszString);
	void GetWindowText(CString& rString) const;
	int GetWindowTextLength() const;
	void SetAutoAddSpace(BOOL bAdd);
	
private:
	void UpdateCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditTrans)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};


