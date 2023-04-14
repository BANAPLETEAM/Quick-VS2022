#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CInsStaffDlg1 ��ȭ �����Դϴ�.

class CInsStaffDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CInsStaffDlg1)

public:
	CInsStaffDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsStaffDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INS_STAFF_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
