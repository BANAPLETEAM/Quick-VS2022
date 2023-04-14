#pragma once


// CMyStaticRed

class CMyStaticRed : public CStatic
{
	DECLARE_DYNAMIC(CMyStaticRed)

public:
	CMyStaticRed();
	virtual ~CMyStaticRed();

protected:
	DECLARE_MESSAGE_MAP()
	static UINT m_RefCnt;
	

public:
	afx_msg void OnPaint();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	virtual void OnFinalRelease();
	void SetWindowText(CString strText);
	void SetNotPoiDong(BOOL bUseDong)
	{
		m_bPoiDong = bUseDong;
		if(m_bPoiDong)
			this->SetWindowText("동오류");
		else
			this->SetWindowText("기준동");
	}
	BOOL m_bPoiDong;

	void SetBackGroundColor(COLORREF rgb){m_clrBackGround = rgb;};
	void SetTextColor(COLORREF rgb){m_clrText = rgb;};

	COLORREF m_clrBackGround;
	COLORREF m_clrText;
};


