#pragma once

class CCustomerPage2 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage2)

public: 
	CCustomerPage2();
	virtual ~CCustomerPage2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();

	DECLARE_MESSAGE_MAP()

protected:
	COleDateTime m_dtFrom, m_dtTo;
	CComboBox m_MinCountCombo;
	CXTPListCtrl2 m_lcData;

	CMyStatic m_MinCountStatic;
	CMyStatic m_DateStatic;
	CDateTimeCtrl m_FromDT, m_ToDT;
	CDateButton m_DateBtn;

	long m_nDOrderTable;
	long m_nCustomerTable;
	BOOL m_bIntegrated;

public:
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	void RefreshList();
	afx_msg void OnBnClickedDateBtn();
};
