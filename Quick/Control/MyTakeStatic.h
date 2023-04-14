#pragma once


// CMyTakeStatic

class CMyTakeStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyTakeStatic)

public:
	CMyTakeStatic();
	virtual ~CMyTakeStatic();

protected:
	DECLARE_MESSAGE_MAP()

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


