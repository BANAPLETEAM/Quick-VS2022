#pragma once

// CReportForm19 대화 상자입니다.

class CReportForm19 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm19)

public:
	CReportForm19();   // 표준 생성자입니다.
	virtual ~CReportForm19();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT19 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:	
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedOrderSearchBtn();
	afx_msg void OnLvnItemchangedListLeft(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnLvnItemDbClickListLeft(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedMileageAllBtn();
	afx_msg void OnBnClickedMileageModifyBtn();

	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnlstDataItemRClick(NMHDR * pNotifyStruct, LRESULT *);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnViewExcel();
	afx_msg void OnViewExcel2();
	afx_msg void OnBnClickedBalanceSearchBtn();
	afx_msg void OnBnClickedBalanceModifyButton();
	afx_msg void OnCbnSelchangeOptionCombo();
	afx_msg void OnCbnSelchangeSearchCombo();
	afx_msg void OnBnClickedBalanceInitButton();
	afx_msg void OnBnClickedMialeageSmsBtn();
	afx_msg void OnBnClickedDirectModifyButton();

	BOOL CheckData();
	void SearchOnlyCustomerAlone(long nCNo);
	void SearchEdit();
	void RefreshList();
	void MultiSelectBalance(int nType);
	void SearchTypeCustomer(BOOL bType);

	CMyMileageReport m_lstLeft;
	CXTPListCtrl2 m_lstData;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	
	CDateButton m_btnDate;

	CFlatEdit2 m_edtSearch;	
	CFlatEdit2 m_edtBalanceFrom;
	CFlatEdit2 m_edtBalanceTo;
	CFlatEdit2 m_edtBalance;
	CFlatEdit2 m_edtMileageModify;
	
	CComboBox m_cmbOption;
	CComboBox m_cmbSearch;

	MAP_CUSTOMER_DATA m_mapCust;
	MAP_CUSTOMER_DATA m_mapCust2;
	MAP_ROW_DATA m_mapRow;
};
