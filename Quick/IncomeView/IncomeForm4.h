#pragma once

// CIncomeForm4 대화 상자입니다.

class CIncomeForm4 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm4)

public:
	CIncomeForm4();
	virtual ~CIncomeForm4();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_INCOME_PAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOneDayBtn();
	afx_msg void OnBnClickedBeforeDayBtn();
	afx_msg void OnBnClickedShowBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnIncomeOk();
	afx_msg void OnViewExcel();
	afx_msg void OnSendMsg();
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedShowTodaySaveBtn();
	afx_msg void OnBnClickedClearDepositBtn();
	afx_msg void OnEditOtherAccount();
	afx_msg void OnRiderDepositMenu();

	void OnNMDblclkList1(NMHDR * pNotifyStruct, LRESULT * /*result*/);


protected:
	COleDateTime m_dtCurrent;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CMyXTPListCtrl_1 m_List;
	CStatic m_ExampleStatic;
	BOOL m_bServerTime;
	BOOL m_bTodayDeposit;
	long m_nCurSel;
	CFlatEdit2 m_SearchEdit;
	CString m_strSearch;

	CButton m_ShowBtn;
	CButton m_MakeJobBtn;
	CButton m_btnMakeDepositGroup;

public:
	void RefreshList();

	CString GetFixedDepositType(long nFixedDeposit, BOOL bWeeklyDeposit, long nPaymentDay);
	CString GetFixedDepositDayString(long nFixedDeposit, COleDateTime dtNextDeposit, long &nRemainDays);
	CString GetMyPercentString(long nPercent, BOOL bRemoveZero = FALSE);
	CString GetCreditReportType(long nType);


	afx_msg void OnCbnSelchangeXtplistctrlCombo();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnCbnSelchangeXtplistctrlTypeCombo();

	BOOL GetRealTime(long nDepositType, long nDepositAllocateType);
	CComboBox m_cmbWorkType;
	afx_msg void OnCbnSelchangeWorkType();
	afx_msg void OnBnClickedMakeDepositGroupBtn();
};
