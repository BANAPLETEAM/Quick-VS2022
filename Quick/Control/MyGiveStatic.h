#pragma once


// CMyGiveStatic

class CMyGiveStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyGiveStatic)

public:
	CMyGiveStatic();
	virtual ~CMyGiveStatic();

protected:
	DECLARE_MESSAGE_MAP()

	static CFont *m_Font;
	static UINT m_RefCnt;
	
	COLORREF m_clrText;

public:
	afx_msg void OnPaint();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	virtual void OnFinalRelease();
	void SetWindowText(CString strText);
	void SetTextColor(COLORREF clrText) { m_clrText = clrText; }
};


