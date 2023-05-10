#pragma once

#include "MainBranchCombo.h"
#include "BranchSel.h"

#define WM_CHANGE_BRANCH_ALL_CODE		WM_USER + 8001

class CComboBranchListDlg;

typedef map<long, ST_BRANCH_PANE_INFO*> BRANCH_PANE_MAP;

class CMakeBranchCombo
{
public:
	CMakeBranchCombo(void);
	~CMakeBranchCombo(void);

	CMainBranchCombo *m_cmbMain;
	CFlatEdit2 *m_edtSub;
	CButton *m_btnSel;

	CComboBranchListDlg *m_pDlg;
	BRANCH_PANE_MAP m_mapBranchPane;
	ST_BRANCH_PANE_INFO *m_BranchPaneInfo;
	long m_nSelIndex;

	void InitBranchCombo(CMainBranchCombo *pMainCombo, CEdit *pEdit, CButton *pBtn);
	void OnMainSelChange();
	void GetVirtualCode(long &nVirtualCompany, BOOL &bIntegrated, CString &sCodeList);
	void OpenBranchDlg(const CWnd *pwndZOrder = NULL);
	void ChangeSubSel(ST_BRANCH_PANE_INFO *pInfo, CString sBranchName, long nIndex);
	void CloseBranchDlg();
	void SetParent(CWnd* pWnd) {m_pParent = pWnd;};

	CWnd *m_pParent;
};
