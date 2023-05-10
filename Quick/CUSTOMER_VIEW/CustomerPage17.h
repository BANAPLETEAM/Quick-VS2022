#pragma once
#include "afxwin.h"


class CCustomerDlg;

// CCustomerPage17 �� ���Դϴ�.

class CCustomerPage17 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage17)

protected:
	CCustomerPage17();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCustomerPage17();

public:
	enum { IDD = IDD_CUSTOMER_PAGE17 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnViewExcel();
	afx_msg void OnClickedRefreshBtn1();
	afx_msg void OnClickedRefreshBtn2();

	void OnContextMenu(CWnd* pWnd, CPoint point);

public:
	CXTPListCtrl2 m_lstMain;
	CXTPListCtrl2 m_lstSub;

	CDateTimeCtrl m_dtpMainFrom;
	CDateTimeCtrl m_dtpMainTo;
	CComboBox m_cmbMainCount;
	CComboBox m_cmbMainUpDown;
	
	CDateTimeCtrl m_dtpSubFrom;
	CDateTimeCtrl m_dtpSubTo;
	CComboBox m_cmbSubCount;
	CComboBox m_cmbSubUpDown;


	BOOL m_bMainExcel;
};