#pragma once
#include "afxwin.h"


// CShareOrderAllocate3 대화 상자입니다.

class CShareOrderAllocate3 : public CMyDialog
{
	DECLARE_DYNAMIC(CShareOrderAllocate3)

public:
	CShareOrderAllocate3(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareOrderAllocate3();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_ORDER_ALLOCATE_DLG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeDetailEdit();
	afx_msg void OnBnClickedTestButton();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButtonApplyAll();

	DECLARE_MESSAGE_MAP()
public:

	void InitControl();
	void SetCompany(int nCompany){m_nCompany = nCompany;}
	void ModifyUser();
	void ModifyUserOk(BOOL bAll);
	void NewUserOk(BOOL bAll);
	void VerifyRider(BOOL bNoMsg = FALSE);

	int m_nMode;
	int m_nID;
	int m_nCompany;
	int m_nRiderCompany;
	int m_nRider;

	long m_nSeletedCompany;
	CString m_sDetailEdit;
	CString m_sRiderName;
	BOOL m_ModifyButtonEnable;
	CEdit m_edtSelectedCompanyName;
	CEdit m_edtCompanyName;
	CEdit m_edtRiderNO;
	CEdit m_DetailEdit;
	CListCtrl m_List;
	CButton m_btnModify;
	CButton m_btnApplyAll;

	void SearchCompanyList();	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edtRiderName;
	CComboBox m_cmbDay;
};
