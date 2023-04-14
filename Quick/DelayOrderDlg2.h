#pragma once

#include "MyStaticText.h"

class CRcpView;
class CEmptyCarDlg1;
class CVirtualRecord;

#define REPORT_COUNT 4

typedef vector<ST_DELAY_ORDER*> DELAY_ORDER_VECTOR2;
// CDelayOrderDlg2 폼 뷰입니다.

class CDelayOrderDlg2 : public CMyFormView
{
	DECLARE_DYNCREATE(CDelayOrderDlg2)

protected:
	CDelayOrderDlg2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDelayOrderDlg2();

public:
	enum { IDD = IDD_DELAY_ORDER_DLG2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();

	CVirtualRecord *m_vrOrder;
	CCriticalSection m_csOrder;
	CEmptyCarDlg1 *m_pEmptyCarPane;
	DELAY_ORDER_VECTOR2 m_OrderVec;

	BOOL m_bRcpPageRefresh;

	CXTPListCtrl16 m_AllocateReport[REPORT_COUNT];
	CXTPListCtrl16 m_PickupReport[REPORT_COUNT];
	CXTPListCtrl16 m_RcpReport[REPORT_COUNT];

	void InitOrder();
	void RefreshList();
	void InsertReport(CXTPListCtrl2 *pReport, ST_DELAY_ORDER *order, long &nRecordCount);
	CMyStaticText m_AllocateStc;
	CMyStaticText m_PickupStc;
	CMyStaticText m_Al15Stc;
	CMyStaticText m_Al21Stc;
	CMyStaticText m_Al31Stc;
	CMyStaticText m_Al41Stc;
	CMyStaticText m_Pi60Stc;
	CMyStaticText m_Pi91Stc;
	CMyStaticText m_Pi121Stc;
	CMyStaticText m_Pi151Stc;
	CMyStaticText m_Al15CountStc;
	CMyStaticText m_Al21CountStc;
	CMyStaticText m_Al31CountStc;
	CMyStaticText m_Al41CountStc;
	CMyStaticText m_Pi60CountStc;
	CMyStaticText m_Pi91CountStc;
	CMyStaticText m_Pi121CountStc;
	CMyStaticText m_Pi151CountStc;
	CMyStaticText m_RcpStc;
	CMyStaticText m_Rcp5Stc;
	CMyStaticText m_Rcp11Stc;
	CMyStaticText m_Rcp21Stc;
	CMyStaticText m_Rcp31Stc;
	CMyStaticText m_Rcp5CountStc;
	CMyStaticText m_Rcp11CountStc;
	CMyStaticText m_Rcp21CountStc;
	CMyStaticText m_Rcp31CountStc;

	afx_msg void OnAllocateReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnPickupReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnRcpReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnAllocateReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnPickupReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnRcpReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg LONG OnRefreshList(WPARAM wParam, LPARAM lParam);
};


