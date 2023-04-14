#pragma once


// CQueryLogDlg 대화 상자입니다.

class CQueryLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CQueryLogDlg)

public:
	CQueryLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CQueryLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_QUERY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
