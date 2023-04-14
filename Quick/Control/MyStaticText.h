#pragma once


// CMyStaticText

class CMyStaticText : public CStatic
{
	DECLARE_DYNAMIC(CMyStaticText)

public:
	CMyStaticText();
	virtual ~CMyStaticText();

protected:
	DECLARE_MESSAGE_MAP()

	static UINT m_RefCnt;
	
public:
	afx_msg void OnPaint();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	COLORREF m_rgbBackGround;
	COLORREF m_rgbText;
	virtual void OnFinalRelease();
	void SetWindowText(CString strText);

	void SetBackGroundColor(COLORREF rgb)
	{
		m_rgbBackGround = rgb;
		Invalidate(TRUE);
	}
	void SetTextColor(COLORREF rgb)
	{
		m_rgbText = rgb;
		Invalidate(TRUE);
	}
};


