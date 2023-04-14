#pragma once

// CAfterReportDlg 대화 상자입니다.

class CAfterReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAfterReportDlg)

public:
	CAfterReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAfterReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AFTER_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
