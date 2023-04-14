#pragma once
// CBranchReportMainDlg 대화 상자입니다.

class CBranchTabControl : public CXTPTabControl
{
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};

class CBranchReportMainDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchReportMainDlg)

public:
	CBranchReportMainDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBranchReportMainDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_REPORT_MAIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	CWnd* GetTabItem(int nTab);

public:
	bool m_bRequest;
	CBranchTabControl m_wndTabControl;
	CEdit m_MoneyEdt;
};
