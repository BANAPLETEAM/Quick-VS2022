#pragma once


// CNewRadioBtn

class CNewRadioBtn : public CButton
{
	DECLARE_DYNAMIC(CNewRadioBtn)

public:
	CNewRadioBtn();
	virtual ~CNewRadioBtn();

protected:
	DECLARE_MESSAGE_MAP()

	BOOL m_bChecked;

	static HBRUSH m_hBrush1;
	static HBRUSH m_hBrush2;
	static HPEN m_hPen;
	static HPEN m_hPen2;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void SetCheck(BOOL bCheck) { m_bChecked = bCheck; }
	BOOL GetCheck() { return m_bChecked; }

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
};


