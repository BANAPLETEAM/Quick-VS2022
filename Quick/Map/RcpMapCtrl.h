#pragma once


#include "LogiMapNew.h"
// CRcpMapCtrl

class CRcpMapCtrl : public CLogiMapNew
{
	DECLARE_DYNAMIC(CRcpMapCtrl)

public:
	CRcpMapCtrl();
	virtual ~CRcpMapCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	afx_msg void OnCreateMap(long Value);

	void RightTopImage(CString strRightTopImage, int nWidth, int nHeight);

	CString m_strRightTopImage;
	int m_nRightTopWidth;
	int m_nRightTopHeight;
};


