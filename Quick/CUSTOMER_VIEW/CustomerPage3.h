#pragma once
#include "afxwin.h"

// CCustomerPage3 대화 상자입니다.

class CCustomerPage3 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage3)

public:
	CCustomerPage3();
	virtual ~CCustomerPage3();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE3 };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	afx_msg void OnClickedTodayBtn();
	afx_msg void OnClickedOneBeforeBtn();
	afx_msg void OnClickedTwoBeforeBtn();
	afx_msg void OnClickedFiveBeforeBtn();
	afx_msg void OnClickedTenBeforeBtn();
	afx_msg void OnClickedTwelveBeforeBtn();
	afx_msg void OnClickedMonthBeforeBtn();
	afx_msg void OnClickedSearchBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnSendSMS();

	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()

protected:
	CDateTimeCtrl m_FromDT;
	//CListCtrl	m_lcData;
	CXTPListCtrl2	m_lcData;
	CStatic m_DateStatic;
	CButton m_Btn0;
	CButton m_Btn1;
	CButton m_Btn2;
	CButton m_Btn3;
	CButton m_Btn4;
	CButton m_Btn5;
	CButton m_Btn6;
	CButton m_Btn7;

	long m_nDOrderTable;
	long m_nCustomerTable;
	BOOL m_bIntegrated;

public:
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }

	CButton m_chkNoGeneralCustomer;
};
