#pragma once

// CIncomeForm5 대화 상자입니다.


class CIncomeForm5 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm5)

public:
	CIncomeForm5();
	virtual ~CIncomeForm5();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_INCOME_PAGE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnViewExcel();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnCbnSelchangeXtplistctrlCombo();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnCbnSelchangeXtplistctrlTypeCombo();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCbnSelchangeShowTypeCombo();

	void RefreshOneRider(long nCompany, long nRNo);
	void RefreshList();
	void ListFilter();
	void MoveClient();
	void FillReport(CMkRecordset *rs);

	long m_nPreCompany;
	long m_nPreRNo;

protected:
	CMyXTPListCtrl_IF3 m_List;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CStatic m_ExampleStatic;

	CDateButton m_DateBtn;

	CButton m_RefreshBtn;
	CComboBox m_cmbShowType;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CFlatEdit2 m_RNoEdit;

	BOOL m_bServerTime;
	BOOL m_bTodayDeposit;
	BOOL m_bIntegrated;

	long m_nCompanyCode;
	long m_nDOrderTable;

	CString m_strRNo;

	CFlatEdit2 m_edtRNoSearch;
	CFlatEdit2 m_edtRNameSearch;
	CFlatEdit2 m_edtManagerSearch;
	CFlatEdit2 m_edtEtcSearch;

	void CheckFilter();
	void GetStringEmpty(CString strShManager, CString &strManager1, CString &strManager2, CString &strManager3, CString &strManager4, CString &strManager5);
public:
	afx_msg void OnEnChangeRnoSearchEdit();
	afx_msg void OnEnChangeRnameSearchEdit();
	afx_msg void OnEnChangeManagerSearchEdit();
	afx_msg void OnEnChangeEtcSearchEdit();
};
