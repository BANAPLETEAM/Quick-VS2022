#pragma once

#include "MyFormView.h"
#include "FlatComboBox.h"
#include "Graph.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MyButton.h"

class CVRRiderLogListDlg;

// CReportForm10 대화 상자입니다.
class CIncomeForm9 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm9)

public:
	CIncomeForm9();   // 표준 생성자입니다.
	virtual ~CIncomeForm9();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_INCOME_PAGE9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnBranchAllot();
	afx_msg void OnBranchRecovery();	
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedSmsSaveButton();

	afx_msg void OnCbnSelchangeBranchCombo();

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_BaranchList;
	CXTPListCtrl2 m_SaveList;

	CXTPListCtrl2 m_NoAccountList;

	CMyButton m_RefreshBtn;



	CStatic m_GraphStatic;



	CFlatComboBox m_cmbBranch;

	CMyButton m_btnSMSSave;
	CFlatComboBox m_cmbSaveRecovery;


	CString m_sSaveUseAmount;
	CString m_sRecoveryAmount;
	int m_nSMSAmount;

	CFlatEdit2 m_edtSMSAmount;
	CVRRiderLogListDlg *m_pVRRiderLogListDlg;

public:
	void InitControl();
	void RefreshList();
	void NoAccountList();
	void AccountList();
	void BranchComboReset();
	BOOL IsOnlyLogiAccount();

	afx_msg void OnBnClickedAutoAllotBtn();
	afx_msg void OnBnClickedChoiceAllotBtn();
	afx_msg void OnBnClickedRecovertBtn();
	afx_msg void OnBnClickedLogBtn();

	afx_msg void OnBnClickedButton1();
	CEdit m_SearchEdt;
	afx_msg void OnEnChangeSerachEdit();
	afx_msg void OnHdnItemclickListReport2(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cmbAccountOwner;
	afx_msg void OnNMRclickNoaccountList(NMHDR *pNMHDR, LRESULT *pResult);
};
