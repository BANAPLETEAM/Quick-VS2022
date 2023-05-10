#pragma once


#include "ColorListCtrl.h"

// CCustomerPage5 ��ȭ �����Դϴ�.

class CCustomerPage5 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage5)

public:
	CCustomerPage5();
	virtual ~CCustomerPage5();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CUSTOMER_PAGE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedIncreaseRadio();
	afx_msg void OnBnClickedDecreaseRadio();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();

	DECLARE_MESSAGE_MAP()
protected:
	CXTPListCtrl2 m_lcData;
	CComboBox m_DateCombo;
	CComboBox m_MinCountCombo;
	CMyStatic m_DateStatic;
	CMyStatic m_UseTypeStatic;
	CMyStatic m_MinCountStatic;
	CButton m_SearchBtn;

	BOOL m_bIncType;
	long m_nDOrderTable;
	long m_nCustomerTable;
	BOOL m_bIntegrated;

public:
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	void RefreshList();
};
