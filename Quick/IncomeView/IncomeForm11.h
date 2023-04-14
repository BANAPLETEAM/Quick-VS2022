#pragma once
#include "afxwin.h"



// CIncomeForm11 폼 뷰입니다.

class CIncomeForm11 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm11)

protected:
	CIncomeForm11();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CIncomeForm11();

public:
	enum { IDD = IDD_INCOME_PAGE11 };
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
	afx_msg void OnBnClickedRefreshBtn();
	void RefreshList();
	CEdit m_edtSearch;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;

	CXTPListCtrl2 m_lstReport;

	afx_msg void OnEnChangeSearchEdit();
};


