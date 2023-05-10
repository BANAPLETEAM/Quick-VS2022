#pragma once
#include "afxwin.h"


class CCustomerDlg;

// CCustomerPage16 폼 뷰입니다.

class CCustomerPage16 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage16)

protected:
	CCustomerPage16();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerPage16();

public:
	enum { IDD = IDD_CUSTOMER_PAGE16 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnViewExcel();
	afx_msg void OnClickedRefreshBtn1();
	afx_msg void OnClickedRefreshBtn2();
	void RefreshData(CMkRecordset *pRs);

	void OnContextMenu(CWnd* pWnd, CPoint point);

	CXTPListCtrl2 m_lstCustomer;

	CDateTimeCtrl m_dtpMain;
	CComboBox m_cmbDate1;
	CComboBox m_cmbCount1;
	CComboBox m_cmbUpDown1;
	CButton m_btnRefresh1;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CComboBox m_cmbCount2;
	CComboBox m_cmbUpDown2;
	CButton m_btnRefresh2;
};


