#pragma once


// CSmsMentDlg ��ȭ �����Դϴ�.

class CSmsMentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsMentDlg)

public:
	CSmsMentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmsMentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_MENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
public:

public:	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRegisterButton();
	afx_msg void OnBnClickedModifyButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnEnChangeHpContentEdit();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnCbnSelchangeContentCombo();
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTimeCheck();
	afx_msg void OnBnClickedComNameCheck();
	afx_msg void OnBnClickedRnameCheck();
	afx_msg void OnBnClickedRnoCheck();
	afx_msg void OnBnClickedInsuNameCheck();
	afx_msg void OnBnClickedInsuNoCheck();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedTimeCheck2();
	afx_msg void OnBnClickedInsuStartCheck();
	afx_msg void OnBnClickedInsuEndCheck();
	afx_msg void OnBnClickedStartCheck();
	afx_msg void OnBnClickedDestCheck();
	afx_msg void OnBnClickedAmountCheck();
	afx_msg void OnBnClickedOrderCompanyCheck();

	void CheckBoxEnable(int nIndex);

	CListCtrl m_lstRegister;
	CListCtrl m_lstPublic;

	CComboBox m_cmbBranchCombo;
	CComboBox m_cmbContent;	
	CComboBox m_cmbReceiveTel;
	CComboBox m_cmbSendTel;

	CButton m_chkDefault;
	CButton m_chkTime;
	CButton m_chkCompanyName;
	CButton m_chkRiderName;
	CButton m_chkInsuranceName;
	CButton m_chkRNo;
	CButton m_chkInsuranceNo;
	CButton m_chkInsuranceStart;
	CButton m_chkInsuranceEnd;
	CButton m_chkStart;
	CButton m_chkDest;
	CButton m_chkAmount;
	CButton m_chkTime2;
	CButton m_chkOrderCompanyCheck;

	CFlatEdit2 m_edtHpContent;
	CFlatEdit2 m_edtSpecialSymbol;

	CStatic m_stcStringLength;
	
	BOOL	m_bIntegrated;
	long	m_nCompany;	

	CString m_strSpecialSymbol;
	CString m_strHpContent;
};
