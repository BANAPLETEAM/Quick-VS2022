#pragma once


// CRoundStatic

class CRoundStatic : public CStatic
{
	DECLARE_DYNAMIC(CRoundStatic)

public:
	CRoundStatic();
	virtual ~CRoundStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};


