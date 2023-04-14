#pragma once
// CBranchReportMainDlg ��ȭ �����Դϴ�.

class CBranchTabControl : public CXTPTabControl
{
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};

class CBranchReportMainDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchReportMainDlg)

public:
	CBranchReportMainDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBranchReportMainDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRANCH_REPORT_MAIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
