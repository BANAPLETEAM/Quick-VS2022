#pragma once
#include "afxwin.h"

typedef struct  
{
	long nOCNoCount;
	long nOCNoChargeSum;
	long nOCNoChargeTrans;
	long nOCNoCountTrans;
	long nOCNoChargeDisAfter;
	long nOCNoChargeCredit;
	long nOCNoCountCredit;
	long nOCNoCountOnline;
	long nOCNoChargeOnline;
	long nCompleteCount;
	long nNotCompleteCount;

} ST_REPORT10_CHARGE;

#define INIT_REPORT10_STRUCT(x) \
	x.nOCNoCount = 0; \
	x.nOCNoChargeSum = 0; \
	x.nOCNoChargeTrans = 0; \
	x.nOCNoCountTrans = 0; \
	x.nOCNoChargeDisAfter = 0; \
	x.nOCNoCountCredit = 0; \
	x.nOCNoChargeCredit = 0; \
	x.nOCNoCountOnline = 0; \
	x.nOCNoChargeOnline = 0; \
	x.nCompleteCount = 0; \
	x.nNotCompleteCount = 0; \

class CReportForm10 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm10)

protected:
	CReportForm10();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm10();

public:
	enum { IDD = IDD_REPORT10 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl44 m_wndReport;

	void FIlterData();
	void RefreshList();
	void IncomeComplete(long nTNo, CXTPGridRecord *pRecord, long nRransferState);
	void RefreshCount();
	CString GetInputType(long nType);
	void SearchData(CString strData, long nColumn, CString strData1, long nColumn1);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedCompleteBtn();
	afx_msg void OnViewExcel();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnCbnSelchangeColumnCombo();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedAllCheck();
	afx_msg void OnBnClickedInputBtn();

	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;
	
	CDateButton m_btnDate;

	CComboBox m_cmbType;
	CComboBox m_cmbPayType;
	CComboBox m_cmbColumn;

	CButton m_btnComplete;
	CButton m_btnRefresh;
	CButton m_btnInput;
	CButton m_chkAll;

	CMyStatic m_stcPeriod;
	CMyStatic m_stc1;
	CMyStatic m_stc2;

	CFlatEdit2 m_edtSearch;

	CComboBox m_cmbColumn2;
	CEdit m_edtSearch2;
	afx_msg void OnCbnSelchangeColumnCombo2();
	afx_msg void OnEnChangeSearchEdit2();
	afx_msg void OnBnClickedShowSumCheck();
	CButton m_chkShowSum;
};


