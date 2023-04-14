#pragma once


#include "LogiMapNew.h"
#include "VirtualRecord.h"

#define  DISPLAY_ORDER_COUNT 4
// CRiderTraceCtrl
class CRiderTraceCtrl : public CLogiMapNew
{
	DECLARE_DYNAMIC(CRiderTraceCtrl)

public:
	CRiderTraceCtrl();
	virtual ~CRiderTraceCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	afx_msg void OnCreateMap(long Value);

	void SetTraceRider(long nCompany, long nRNo, OrderRecord *pOrder = NULL, BOOL bRider = FALSE);
	void RightTopImage(CString strRightTopImage, int nWidth, int nHeight);
	void SetRcpView(CRcpView *pRcpView) { m_pRcpView = pRcpView;}
	BOOL RefreshRiderPos();
	void RefreshOrderState();
	BOOL IsTraceRider(long nCompany, long nRNo);
	
	CXUIStaticText m_uistcOrder[DISPLAY_ORDER_COUNT];
	CXUIImage m_uiimageOrder[DISPLAY_ORDER_COUNT];

protected:
	long m_nCompany;
	long m_nRNo;
	CRcpView* m_pRcpView;
	CString m_strRightTopImage;
	int m_nRightTopWidth;
	int m_nRightTopHeight;
};


