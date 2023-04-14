#pragma once
#include "afxwin.h"



// CStaffPage15 폼 뷰입니다.

class CStaffPage15 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage15)

protected:
	CStaffPage15();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStaffPage15();

public:
	enum { IDD = IDD_STAFF_PAGE15 };
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
	CXTPListCtrl2 m_lstReport;
	CXTPListCtrl2 m_lstOtherReport;
	
	void RefreshList();
	void RefreshListMyLimit();
	void RefreshListOtherLimit();
	
	CFlatEdit2 m_edtSearch;	
	CFlatEdit2  m_edtSearchOther;
	CStatic m_stcHelp;

	afx_msg void OnBnClickedRefreshListButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedShareRiderButton();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnEnChangeSearchOtherEdit();

};


