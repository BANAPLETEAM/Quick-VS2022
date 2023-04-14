#pragma once


typedef map<COLORREF, pair<HBRUSH, int>> EDIT_BRUSH_MAP;

#define WM_EDIT_RESIZE	WM_USER + 1

// CFlatEditInsung

class CFlatEditInsung : public CXTPEdit
{
	DECLARE_DYNAMIC(CFlatEditInsung)

public:
	CFlatEditInsung();
	virtual ~CFlatEditInsung();

protected:
	DECLARE_MESSAGE_MAP()

	COLORREF m_clrBorderHot; //아래 두개 다시 확인해야함 choe
	COLORREF m_clrBorderNormal;

	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/ );
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);


	void OnUserChar();
	HBRUSH GetClientBrush();
	void CreateClientBrush();
	void ReleaseClientBrush();
	//virtual void DrawNcBorders(CDC* pDC, CRect rc);
	void DrawFrameNC(CDC *pDC, CRect rc, COLORREF cr);
	void DrawFrame(CDC *pDC, CRect rc, int nSize, COLORREF cr);
	void FillSolidRect(CDC *pDC, int x, int y, int cx, int cy, COLORREF cr);
	void PreSubclassWindow();
	void DrawHelpText(CDC *pDC, CRect rc);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	static EDIT_BRUSH_MAP m_mapBrush;
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrHelpText;
	BOOL m_bShowCommaNumber;
	BOOL m_bShowDashPhoneNumber;
	CString m_strHelpText;
	BOOL m_bAutoResize;
	int m_nEditLineExtent;
	int m_nMaxLine;
	UINT m_nTextAlign;
	
public:
	void SetColor(COLORREF clrText, COLORREF clrBack = RGB(255, 255, 255), BOOL bRedraw = FALSE);
	void SetBorderColor(COLORREF clrNormal = RGB(204, 204, 204), COLORREF clrHot = RGB(0, 198, 255));
	void EnableCommaNumber(BOOL bEnable = TRUE) { m_bShowCommaNumber = bEnable; }
	void EnableDashPhoneNumber(BOOL bEnable = TRUE) { m_bShowDashPhoneNumber = bEnable; }
	void SetHelpText(CString strHelpText, COLORREF clrHelpText = RGB(150, 150, 150), UINT nTextAlign = DT_CENTER, BOOL bRedraw = FALSE);
	void EnableAutoResize(BOOL bEnable = TRUE) { m_bAutoResize = bEnable; }
	void SetWindowText(LPCTSTR lpszString);
	void SetWindowTextLong(long nNumber, BOOL bThousandsSep = FALSE);
	CString GetText();
	long GetTextLong();
	void SetMaxLine(UINT nMaxLine) { m_nMaxLine = nMaxLine; }
	void ResetLineExtent() { m_nEditLineExtent = 0;}
	void Refresh() { OnUserChar(); }

};


