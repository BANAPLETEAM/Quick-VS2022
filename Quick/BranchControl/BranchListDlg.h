#pragma once

class CBranchSel;
// CBranchListDlg 대화 상자입니다.

class CBranchListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchListDlg)

public:
	CBranchListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBranchListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
