#pragma once


// CHelpGroupReportDlg 대화 상자입니다.

class CHelpGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CHelpGroupReportDlg)

public:
	CHelpGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHelpGroupReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HELP_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
