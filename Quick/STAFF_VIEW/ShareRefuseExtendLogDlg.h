#pragma once


// CShareRefuseExtendLogDlg ��ȭ �����Դϴ�.

class CShareRefuseExtendLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CShareRefuseExtendLogDlg)

public:
	CShareRefuseExtendLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareRefuseExtendLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_REFUSE_EXTEND_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_lstReport;
	long m_nID;
	void RefreshList();
	afx_msg void OnBnClickedOk();
};
