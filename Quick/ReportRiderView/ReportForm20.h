#pragma once

#include "DataBox.h"

 //CReportForm20 대화 상자입니다.

class CMileageReport : public CDataBox
{
	public:
		void CMileageReport::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
		{
			int nCol = pDrawArgs->pColumn->GetIndex();
			int nRow = pDrawArgs->pRow->GetIndex();

			if(this->GetItemDataLong(nRow) == 1)
			{
				pItemMetrics->clrBackground = RGB(220, 230, 220);
				pItemMetrics->clrForeground = RGB(0, 0, 255);
			}
		}

};
class CQuickDoc;
class CReportForm20 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm20)

public:
	CReportForm20();   // 표준 생성자입니다.
	virtual ~CReportForm20();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT20 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonRiderFetch2();
	afx_msg void OnBnClickedButtonRiderFetch();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnViewExcel2();
	afx_msg void OnViewExcel3();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemLogRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemCustomRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	DECLARE_MESSAGE_MAP()

public:
	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;
	CMyStatic m_Static5;
	CMyStatic m_Static6;

	CFlatEdit2 m_edtMNo;
	CFlatEdit2 m_edtSName;
	CFlatEdit2 m_edtDisrate;
	CFlatEdit2 m_edtCashrate;

	
	CDataBox m_RiderList;	
	CMileageReport m_OrderList;
	CDataBox m_LogList;

	COleDateTime m_tmFrom;
	COleDateTime m_tmTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	COleDateTime m_dtLogFrom;
	COleDateTime m_dtLogTo;
	CDateTimeCtrl m_dtpFromLog;
	CDateTimeCtrl m_dtpToLog;



	CDateButton m_DateBtn;
	CDateButton m_DateLogBtn;
	CComboBox m_cmbCouphon;


	CButton m_btnRiderRefresh;
	CButton m_btnCalculate;
	CButton m_btnInput;
	CButton m_btnOutput;

	
	CButton m_RefreshBtn;
	CButton m_RefreshBtn2;
	CButton m_chkLaterDisCount;

	CString m_strDisRate;
	CString m_strCashRate;
	int m_nMNo;
	
	BOOL m_bCash;
	BOOL m_bCredit;
	BOOL m_bOnline;
	BOOL m_bLaterDisCount;
	long m_nRiderCompany;

	CString m_sName;



public:
	void InsertDayTotal(long nTCash, long nTCredit, long nTBasic, long nTAdd, long nTDis, long nTTrans, long nTAfter, 
		long nTSum, long nTCoupon, long nItem, BOOL bInsert);

	void RefreshRider();
	void RefreshList();
	void RefreshLogList();

	CString GetType(long nShareCode1, long nRiderShareCode1);

	afx_msg void OnBnClickedTodayBtn();

//
	afx_msg void OnReportItemDblClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReportItemClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCalculateBtn();
	afx_msg void OnBnClickedReceiveBalanceBtn();
	afx_msg void OnBnClickedCalculateBtn3();
	afx_msg void OnCbnSelchangeCouphonCombo();
	afx_msg void OnBnClickedRiderRefreshBtn();
};
