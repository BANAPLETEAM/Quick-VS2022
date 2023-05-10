#pragma once

#include "afxwin.h"


// CReportForm34 폼 뷰입니다.

class CReportForm34 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm34)

protected:
	CReportForm34();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm34();

public:
	enum { IDD = IDD_REPORT34 };
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
	CXTPListCtrl2 m_lstReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;
	virtual void OnInitialUpdate();
	void RefreshList();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeRnoEdit();
	void SearchFilter();
	void OnCancelPayCash();
	CFlatEdit2 m_edtRNo;
};


