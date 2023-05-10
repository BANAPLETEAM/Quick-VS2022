#pragma once

#include "MyFormView.h"


// ReportForm4 �� ���Դϴ�.

class CReportForm4 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm4)

protected:
	CReportForm4();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CReportForm4();

public:
	enum { IDD = IDD_REPORT4 };
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
	afx_msg void OnBnClickedRefreshButton();
	virtual void OnInitialUpdate();
	void RefreshList();

	CDateButton m_btnDate;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CXTPListCtrl2 m_lstRider;
	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};


