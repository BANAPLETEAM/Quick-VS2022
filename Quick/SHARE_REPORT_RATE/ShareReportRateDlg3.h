#pragma once

#include "ColorListCtrl.h"
#include "ReportForm5.h"

// CShareReportRateDlg3 �� ���Դϴ�.

class CShareReportRateDlg3 : public CMyFormView
{
	DECLARE_DYNCREATE(CShareReportRateDlg3)

protected:
	CShareReportRateDlg3();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CShareReportRateDlg3();
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

protected:
	CDateButton m_DateBtn;
	CColorListCtrl m_List;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CButton m_ReportIntCheck;

	long m_nDOrderTable;
	BOOL m_bIntegrated;

public:
	enum { IDD = IDD_SHARE_REPORT_RATE_DLG3 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	void OnViewExcel();
	void RefreshList();
	CString GetShareReportRateString(long nRcpRate);
public:

	afx_msg void OnBnClickedShowBtn();
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


