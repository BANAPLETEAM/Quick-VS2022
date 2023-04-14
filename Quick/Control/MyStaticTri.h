#pragma once


// CMyStaticTri

class CMyStaticTri : public CStatic
{
	DECLARE_DYNAMIC(CMyStaticTri)

public:
	CMyStaticTri();
	virtual ~CMyStaticTri();

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
	
	COLORREF m_rgbText;
	COLORREF m_rgbBorder;
	void SetBorderColor(COLORREF rgb) { m_rgbBorder = rgb; }
	void SetTextColor(COLORREF rgb) { m_rgbText = rgb; }

};


