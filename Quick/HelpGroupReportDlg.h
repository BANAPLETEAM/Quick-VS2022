#pragma once


// CHelpGroupReportDlg ��ȭ �����Դϴ�.

class CHelpGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CHelpGroupReportDlg)

public:
	CHelpGroupReportDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHelpGroupReportDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HELP_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
