#pragma once
#include "afxwin.h"


// CShareOrderAllocate ��ȭ �����Դϴ�.

class CShareOrderAllocate : public CMyDialog
{
	DECLARE_DYNAMIC(CShareOrderAllocate)

public:
	CShareOrderAllocate(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareOrderAllocate();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_ORDER_ALLOCATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
	void ModifyUserOk();
	void NewUserOk(BOOL bAll);
	void VerifyRider(BOOL bNoMsg = FALSE);

	int m_nMode;
	int m_nID;
	int m_nCompany;
	int m_nRiderCompany;
	int m_nRider;

	CString m_sDetailEdit;
	CString m_sRiderName;
	BOOL m_ModifyButtonEnable;

	CEdit m_edtRiderNO;
	CEdit m_DetailEdit;
	CComboBox m_cmbCompany;
	CButton m_btnModify;
	CButton m_btnApplyAll;

};
