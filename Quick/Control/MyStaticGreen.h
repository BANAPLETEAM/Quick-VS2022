#pragma once


// CMyStaticGreen

class CMyStaticGreen : public CStatic
{
	DECLARE_DYNAMIC(CMyStaticGreen)

public:
	CMyStaticGreen();
	virtual ~CMyStaticGreen();

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
			this->SetWindowText("������");
		else
			this->SetWindowText("���ص�");
	}
	BOOL m_bPoiDong;
};


