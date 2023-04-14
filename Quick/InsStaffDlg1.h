#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CInsStaffDlg1 대화 상자입니다.

class CInsStaffDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CInsStaffDlg1)

public:
	CInsStaffDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsStaffDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INS_STAFF_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefreshButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedExcelButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDateTimeCtrl m_dtpDay;
	void RefreshList();
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_edtSearch;
};
