#pragma once

// CAfterReportDlg ��ȭ �����Դϴ�.

class CAfterReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAfterReportDlg)

public:
	CAfterReportDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAfterReportDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AFTER_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_Report;

	long m_nGNo;
	BOOL m_bAll;

	void RefreshList();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL OnInitDialog();
};
