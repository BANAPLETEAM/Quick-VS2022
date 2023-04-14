#pragma once

class CMakeBranchCombo;

class CComboBranchListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CComboBranchListDlg)

public:
	CComboBranchListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CComboBranchListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMBO_BRANCH_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CMakeBranchCombo *m_pParent;
	CXTPListCtrl45 m_lstBranch;
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedCloseBtn();
};
