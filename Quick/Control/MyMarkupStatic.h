#pragma once


// CMyMarkupStatic

class CMyMarkupStatic : public CMarkupStatic
{
	//DECLARE_DYNAMIC(CMyMarkupStatic)

public:
	CMyMarkupStatic();
	virtual ~CMyMarkupStatic();

protected:
	DECLARE_MESSAGE_MAP()
	CString m_strFooterMsg;

public:
	void SetFooterMsg(CString strFotterMsg) { m_strFooterMsg = strFotterMsg; Invalidate();};
	CString GetFotterMsg() {return m_strFooterMsg;};

	afx_msg void OnPaint();
};


