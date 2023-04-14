#pragma once
#include "PSListCtrl.h"
#include "MyListCtrl9.h"

// CPenaltySetDlg ��ȭ �����Դϴ�.

#define CANCEL_DEFAULT_TIME		"60"


class CPenaltySetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPenaltySetDlg)

public:
	
	CPenaltySetDlg(long nCompanyCode,CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPenaltySetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PENALTY_SET_DLG };

protected:
	long m_nCompanyCode;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedCopyButton();
	afx_msg void OnBnClickedAllNotButton();
	afx_msg void OnBnClickedAllAmountButton();
	afx_msg void OnBnClickedAllNotButton2();
	afx_msg void OnBnClickedAllApplyCompanyButton();
	afx_msg void OnCbnSelchangeBranchCombo();

public:
	void InitControl(void);
	void RefreshList(void);

public:
	CButton m_btnIntegrated;
	CFlatComboBox m_cmbBranchCombo;
	long	m_nAmount;
	BOOL	m_bIntegrated;
	CPSListCtrl m_List;
	CXTFlatEdit m_AmountEdit;

	CButton m_RefreshBtn;
	CButton m_AllNotButton;
	CButton m_AllNotButton2;
	CButton m_AllAmountButton;
	CButton m_CopyButton;
	CButton m_OkBtn;
	CButton m_CancelBtn;
	
};

