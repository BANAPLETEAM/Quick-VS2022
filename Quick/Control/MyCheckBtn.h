#pragma once


// CMyCheckBtn

class CMyCheckBtn : public CButton
{
	DECLARE_DYNAMIC(CMyCheckBtn)

public:
	CMyCheckBtn();
	virtual ~CMyCheckBtn();

protected:
	BOOL m_bGetBkColor;
	COLORREF m_crBack;

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);
};


