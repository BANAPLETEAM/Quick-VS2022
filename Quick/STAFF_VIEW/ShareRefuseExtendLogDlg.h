#pragma once


// CShareRefuseExtendLogDlg 대화 상자입니다.

class CShareRefuseExtendLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CShareRefuseExtendLogDlg)

public:
	CShareRefuseExtendLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareRefuseExtendLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REFUSE_EXTEND_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_lstReport;
	long m_nID;
	void RefreshList();
	afx_msg void OnBnClickedOk();
};
