#pragma once

#include "DateButton.h"
#include "afxwin.h"

// CCustomerPage13 �� ���Դϴ�.

class CCustomerPage13 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage13)

protected:
	CCustomerPage13();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCustomerPage13();

public:
	enum { IDD = IDD_CUSTOMER_PAGE13 };
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
	CXTPListCtrl2 m_lstReport;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_btnDate;
	
	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSearchAllBtn();
};


