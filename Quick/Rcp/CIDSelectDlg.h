#pragma once
#include "afxwin.h"
#include "BranchSel.h"

#include "XTPListCtrl_Branch.h"
// CCTIFormSetupDlg 대화 상자입니다.

class CCIDSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCIDSelectDlg)

public:
	CCIDSelectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCIDSelectDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CID_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	//LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	CXTPListCtrl_Branch m_lstBranch;
	CComboBox m_cmbBranch;

	CBranchSel m_cBranch;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain;
	CBranchSubBtn m_btnSub;

	afx_msg void OnEnChangeSearchEdt();
	CFlatEdit2 m_edtSearch;
};

