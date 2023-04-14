#pragma once


// CMyButton

class CMyDrawButton : public CButton
{
	DECLARE_DYNAMIC(CMyDrawButton)

public:
	CMyDrawButton();
	virtual ~CMyDrawButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
public:
	COLORREF m_clrText;
	COLORREF m_clrBack;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void SetTextColor(COLORREF rgb) {m_clrText = rgb; Invalidate();};
	void SetBackColor(COLORREF rgb) {m_clrBack = rgb; Invalidate();}
};


