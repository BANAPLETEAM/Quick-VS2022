#pragma once

// CDepositJobLogDlg 대화 상자입니다.

class CDepositJobLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositJobLogDlg)

public:
	CDepositJobLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDepositJobLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DEPOSIT_JOB_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stcHelp;
	CXTPListCtrl2 m_lstLog;

	long m_nScheduleID;
	CString m_strDisplayName;

	void RefreshList();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshJobBtn();
	afx_msg void OnBnClickedCloseBtn();
};
