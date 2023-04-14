#pragma once


// CQueryLogDlg ��ȭ �����Դϴ�.

class CQueryLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CQueryLogDlg)

public:
	CQueryLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CQueryLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_QUERY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CXTPListCtrl2 m_lstQuery;
	CString m_strQuery;

public:
	void AddQuery(CString strQuery);
	void RefreshList();

public:
	afx_msg void OnBnClickedCopyClipBtn();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
