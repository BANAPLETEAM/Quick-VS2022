#pragma once



class CCustomerMileageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerMileageDlg)
		
public:
	CCustomerMileageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCustomerMileageDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CUSTOMER_MILEAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCNo;
	virtual BOOL OnInitDialog();
	CXTPListCtrl5 m_Report;
	void RefreshList();
	afx_msg void OnBnClickedChangeMileageBtn();
	afx_msg void OnBnClickedRefreshBtn();
	CEdit m_edtChangeMileage;
	afx_msg void OnBnClickedInitMileageBtn();
	//afx_msg void OnBnClickedAllowCompanySetting();
	//CButton m_chkAllowCompanySetting;
	CComboBox m_cmbPercent;
	CEdit m_edtMileage;
	afx_msg void OnBnClickedSaveSettingBtn();
	void InitSetting(long nCompanySetting, long nCustomerSetting,long nCustomerMileType);
	void MileageModify(int nType, long nAmount);
	afx_msg void OnCbnSelchangePercentCombo();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedMileagePayBtn();
	CEdit m_edtMileEtc;
	CWnd *m_pWnd;
	long m_nPersonMileage;
	long m_nPersonMileageType;
	BOOL m_bApply;
	long m_nMileageBalance;

};





















