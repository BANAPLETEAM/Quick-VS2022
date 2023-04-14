#pragma once
#include "afxwin.h"
#include "BranchSel.h"

#include "XTPListCtrl_Branch.h"
// CCTIFormSetupDlg ��ȭ �����Դϴ�.

class CCIDSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCIDSelectDlg)

public:
	CCIDSelectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCIDSelectDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CID_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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

