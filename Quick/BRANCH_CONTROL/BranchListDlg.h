#pragma once

class CBranchSel;
// CBranchListDlg ��ȭ �����Դϴ�.

class CBranchListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchListDlg)

public:
	CBranchListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBranchListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRANCH_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void SetFilterText(CString strSearchFilter);
	void SelectTopRow();
	void SelectRow(CXTPGridRow *pRow);

	CXTPListCtrl45 m_lst;
	CBranchSel *m_pBranchSel;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_btnClose;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
