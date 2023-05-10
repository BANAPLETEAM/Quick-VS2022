#pragma once
#include "afxwin.h"



// CStaffPage16 �� ���Դϴ�.

class CStaffPage16 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage16)

protected:
	CStaffPage16();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStaffPage16();

public:
	enum { IDD = IDD_STAFF_PAGE16 };
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
	CFlatEdit2 m_edtSearch;

	void RefreshList();
	afx_msg void OnBnClickedRefreshListButton();
	virtual void OnInitialUpdate();
	afx_msg void OnEnChangeSearchEdit();
};


