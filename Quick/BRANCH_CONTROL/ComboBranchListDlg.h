#pragma once

class CMakeBranchCombo;

class CComboBranchListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CComboBranchListDlg)

public:
	CComboBranchListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CComboBranchListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMBO_BRANCH_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CMakeBranchCombo *m_pParent;
	CXTPListCtrl45 m_lstBranch;
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedCloseBtn();
};
