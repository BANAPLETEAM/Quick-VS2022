#pragma once
#include "afxwin.h"



// CStaffPage20 �� ���Դϴ�.

class CStaffPage20 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage20)

protected:
	CStaffPage20();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStaffPage20();

public:
	enum { IDD = IDD_STAFF_PAGE20 };
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
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_btnDate;

	CXTPListCtrl2 m_lstReport;

	void RefreshList();

	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_edtSearch;
};


