#pragma once
#include "afxwin.h"

class CQuickDoc;
class CReportForm2 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm2)

public:
	CReportForm2();   // 표준 생성자입니다.
	virtual ~CReportForm2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnClicklcLeftItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonRiderFetch2();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnSendSms();
	afx_msg void OnBnClickedButtonRiderFetch();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void OnReportLeftItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	DECLARE_MESSAGE_MAP()

public:
	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;
	CMyStatic m_Static5;

	CFlatEdit2 m_edtDisrate;
	CFlatEdit2 m_edtCashrate;

	CXTPListCtrl2 m_lcLeft;
	//CListCtrl m_lcData;
	CXTPListCtrl13 m_lcData;

	COleDateTime m_tmFrom;
	COleDateTime m_tmTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CDateButton m_DateBtn;
	CButton m_RefreshBtn;
	CButton m_RefreshBtn2;
	CButton m_chkLaterDisCount;

	CString m_strDisRate;
	CString m_strCashRate;
	BOOL m_bCash;
	BOOL m_bCredit;
	BOOL m_bOnline;
	BOOL m_bLaterDisCount;
	BOOL m_bCard;
	BOOL m_bMile;

public:
	void InsertDayTotal(long nTCash, long nTCredit, long nTBasic, long nTAdd, long nTDis, long nTTrans, long nTAfter, 
		long nTSum, long nTChargeDriving, long nDepositT, long nTRealDeposit, long nTCoupon, long nTBill, long nItem, BOOL bInsert);

	void RefreshRider();
	void RefreshList(long nParameterRNo = 0);
	void RefreshListAfterDisCount(long nParameterRNo = 0);
	void InitReportColumn(BOOL bSMS);
	CString GetType(long nShareCode1, long nRiderShareCode1);

	afx_msg void OnBnClickedTodayBtn();
	afx_msg void OnBnClickedMsgBtn();
	void RefreshSMSData();
	BOOL m_bSms;
	CButton m_btnMsg;
	CComboBox m_chkType;
	afx_msg void OnBnClickedRefreshBtn();
	CEdit m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
};
