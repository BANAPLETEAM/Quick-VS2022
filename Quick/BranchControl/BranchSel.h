#pragma once
#include "BranchMainBtn.h"
#include "BranchSubBtn.h"
#include "FlatBranchEdit.h"
#include "FlatMainEdit.h"
#include "FlatSubEdit.h"


class CBranchMainListDlg;
class CBranchSubListDlg;
class CBranchListDlg;

class CBranchSel :public CWnd
{
public:
	CBranchSel();
	~CBranchSel(void);

	void InitData(CEdit *pMainEdt, CEdit *pSubEdt, CButton *pMainBtn, CButton *pSubBtn, CEdit *pSearchEdt = NULL);
	CFlatMainEdit *m_edtMain;
	CFlatSubEdit *m_edtSub;
	CFlatBranchEdit *m_pSearchEdt;

	CBranchMainBtn *m_btnMain; 
	CBranchSubBtn *m_btnSub;
	CWnd *m_pParent;

	CBranchInfo *m_pBi;
	MAP_BRANCH m_map;
	BOOL m_bSendParentBranchChangeInfo;
	BOOL m_bOneSite;

	CBranchMainListDlg *m_pMainListDlg;
	CBranchSubListDlg *m_pSubListDlg;
	CBranchListDlg *m_pBranchListDlg;

	void ChangeMainBranch(CXTPTaskPanelItem *pItem, BOOL nFirstSelect = TRUE);
	void ChangeSubBranch();
	CBranchInfo *GetBranchInfo(){return m_pBi;};
	long GetCompany(){return m_pBi->nCompanyCode;};
	CBranchInfo* SetCompany(long nCompany);
	void SetEditTextColor();
	MAP_BRANCH* GetMapData(){return &m_map;};

	void InsertMainData();
	void MakeDialog();
	void ReLocateControl();

	void OpenMainListDlg();
	void OpenSubListDlg();
	void OpenAllBranchListDlg();
	void CloseMainListDlg();

	void SetParent(CWnd *pWnd, BOOL bSendParentBranchChangeInfo){m_pParent = pWnd; m_bSendParentBranchChangeInfo = bSendParentBranchChangeInfo;};
	void SendChangeBranchInfToParent();
	void SearchBranch(CString strSearch);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
