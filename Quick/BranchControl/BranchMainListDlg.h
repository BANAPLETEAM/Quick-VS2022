#pragma once

#include "BranchSubListDlg.h"

class CBranchMainListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchMainListDlg)

public:
	CBranchMainListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBranchMainListDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_MAIN_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListBranch m_lst;
	CBranchSel *m_pBranchSel;
	virtual BOOL OnInitDialog();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedCloseBtn();
	CButton m_btnClose;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBranchListFocus(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBranchKillFocus(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


