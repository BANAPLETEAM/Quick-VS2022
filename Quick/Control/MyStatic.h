#pragma once


// CMyStatic

#define WM_MY_STATIC_CLICK	WM_USER + 846

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:
	CMyStatic();
	virtual ~CMyStatic();

protected:
	DECLARE_MESSAGE_MAP()

	static UINT m_RefCnt;

	COLORREF m_clrText;
	COLORREF m_clrBack;
	BOOL m_bSelected;
	BOOL m_bEnableClick;
	BOOL m_bMakeLine;
	long m_nAlign;
	long m_nLeftMargin;
	//CBitmap m_bmpBack;
	//CRect m_rcLast;

	CFont *m_pfontText;

public:
	afx_msg void OnPaint();
	afx_msg void OnStnClicked();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void PreSubclassWindow();
public:
	void SetLeftMargin(long nLeft){m_nLeftMargin = nLeft;}
	void SetTextColor(COLORREF clrText, BOOL bMakeLine = FALSE) { m_clrText = clrText; m_bMakeLine = bMakeLine; RedrawWindow();}
	void SetBkColor(COLORREF clrBk, BOOL bMakeLine = FALSE) { m_clrBack = clrBk; m_bMakeLine = bMakeLine; RedrawWindow();}
	COLORREF GetTextColor(){return m_clrText;}
	COLORREF GetBkColor(){return m_clrBack;}
	void EnableClick(BOOL bEnable) { m_bEnableClick = bEnable;}
	BOOL GetCheck() { return m_bSelected; }
	void SetCheck(BOOL bCheck) { m_bSelected = bCheck; RefreshState();}
	void RefreshState();
	void SetWindowText(LPCTSTR lpszString);
	void SetMakeLine(BOOL bMakeLine) { m_bMakeLine = bMakeLine;}
	void SetAlign(long nAlign) { m_nAlign = nAlign;}
	void SetTextFont(CFont *font) { m_pfontText = font;}

	//void GetWindowText(CString& rString);
};


