#pragma once


// CTransparentStatic

class CTransparentStatic : public CStatic
{
	DECLARE_DYNAMIC(CTransparentStatic)

public:
	CTransparentStatic();
	virtual ~CTransparentStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetImage(UINT nID, COLORREF clrTransparent = RGB(255, 255, 255))
	{
		m_nID = nID;
		m_clrTransparent = clrTransparent;
		Invalidate(TRUE);
	}

	long m_nID;
	COLORREF m_clrTransparent;
};


