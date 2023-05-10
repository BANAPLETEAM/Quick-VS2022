//#pragma once
//
//
#pragma once


#include "MakeBranchCombo.h"
#include "MainBranchCombo.h"

// CCallCountDlg ��ȭ �����Դϴ�.

class CCallCountDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCallCountDlg)

public:
	CCallCountDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCallCountDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALL_COUNT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//CListCtrl m_List;

	afx_msg void OnBnClickedOk();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedExcelOutButton();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedOpenBranchBtn();
	afx_msg void OnBnClickedNoShowZeroCheck();

	void ListFilter();

	CXTPListCtrl2 m_List;

	CButton m_btnOk;
	CButton m_btnCancel;
	CButton m_btnExcelOut;
	CButton m_btnRefresh;
	CButton m_btnOpenBranch;
	CButton m_chkNoShowZero;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CDateTimeCtrl m_DateDT;

	CDateButton m_btnDate;
	CMakeBranchCombo m_cBranchCombo;
	CMainBranchCombo m_cmbMain;

	CFlatEdit2 m_edtBranch;
};

