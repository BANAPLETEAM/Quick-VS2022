#pragma once

#include "VirtualRecord.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxmt.h"
#include "MyReportPaintManager.h"
#include "PPTooltip.h"
#include "MyStaticBlue.h"
#include "MyStaticGreen.h"

typedef vector<ST_RIDER_STRUCT*> EMPTY_RIDER_VECTOR;
typedef map<std::pair<long, long>, ST_RIDER_STRUCT*> EMPTY_RIDER_MAP;
typedef multimap<std::pair<long, long>, ST_EMPTY_ORDER> EMPTY_ORDER_MAP;


class CDelayOrderDlg2;

#define MAX_RIDER_COUNT 1000

class CEmptyCarDlg1 : public CMyFormView
{
	DECLARE_DYNCREATE(CEmptyCarDlg1)

protected:
	CEmptyCarDlg1();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CEmptyCarDlg1();

public:
	enum { IDD = IDD_EMPTY_CAR1_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	virtual void OnInitialUpdate();
public:

	CXTPGridControl m_wndReport;
	CXTPGridControl m_wndReport2;
	
	CEmptyPaintManager *m_pEPM;
	CEmptyPaintManager *m_pAPM;
	EMPTY_ORDER_MAP m_OrderMap;
	EMPTY_RIDER_VECTOR m_RiderVec;
	
	BOOL m_bDragMode;
	BOOL m_bFollowRcpRefresh;

	long m_nState;
	long m_nTNo;
	long m_nCarType;
	long m_nCompany; 

	CCriticalSection m_csOrder;
	CPPToolTip m_tooltip;

	long m_nDiscountSec;
	CImageList m_imgList;

	CMyStaticBlue m_Static1;
	CMyStaticBlue m_Static2;
	CButton m_RefreshBtn;
	
	CVirtualRecord *m_vrOrder;

	void RefreshList(BOOL bSearchOrder = TRUE);
	void GetRider();
	void InitRider();
	void InitOrderMap();
	void UpdateLastLocation(ST_RIDER_STRUCT *rider);
	void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);

	BOOL m_bFirst;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_SearchEdt;
	CString m_sSearch;
};


