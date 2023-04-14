#pragma once


#include "ColorListCtrl.h"

// CCustomerPage4 대화 상자입니다.

class CCustomerPage4 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage4)

public:
	CCustomerPage4();
	virtual ~CCustomerPage4();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedSearchBtn();

	DECLARE_MESSAGE_MAP()

protected:
	CComboBox m_MinCountCombo;
	CXTPListCtrl2 m_lcData;
	CComboBox m_DateCombo;
	CMyStatic m_MinCountStatic;
	CMyStatic m_DateStatic;
	CButton m_SearchBtn;

	CString m_strMinCount;
	long m_nDOrderTable;
	long m_nCustomerTable;
	BOOL m_bIntegrated;

public:
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	void RefreshList();
};
