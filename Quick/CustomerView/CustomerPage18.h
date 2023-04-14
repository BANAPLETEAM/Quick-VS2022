#pragma once
#include "afxwin.h"


// CCustomerPage18 �� ���Դϴ�.

class CCustomerPage18 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage18)

protected:
	CCustomerPage18();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCustomerPage18();

public:
	enum { IDD = IDD_CUSTOMER_PAGE18 };
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
	afx_msg void OnDelete();

	void OnContextMenu(CWnd* pWnd, CPoint point);

	CXTPListCtrl2 m_lstReport;

	afx_msg void OnBnClickedRefreshBtn();
	void RefreshList();
	CEdit m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
};


