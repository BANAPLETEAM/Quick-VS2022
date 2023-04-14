#pragma once

// CDepositJobLogDlg ��ȭ �����Դϴ�.

class CDepositJobLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositJobLogDlg)

public:
	CDepositJobLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDepositJobLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEPOSIT_JOB_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
