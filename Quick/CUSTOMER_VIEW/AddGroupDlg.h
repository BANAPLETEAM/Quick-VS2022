#pragma once

// CAddGroupDlg 대화 상자입니다.

class CAddGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddGroupDlg)

public:
	CAddGroupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddGroupDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:

	void GNoListAdd(long nGNo);
	void GNoListInit();
	void GNoListAll();
	void GNoListPerson(long nGNo);
	void GNoListStateCheck(int nType);
	void GNoListAllUnCheck();
	CString GNoListString();
	int	GetListTypeCheck();
	BOOL GNoListInputAllSame();

public:
	void LoadGroup();
	void AddNewGroup();
	void EditGroup();
	void ChargeTypeNameRefresh();
	void GetChargeType();
	void MakeGrouopReport(long nGNo, long nFirstDay, long nSecondDay);
	BOOL UniqueCheckTypeName();
	void CheckCombo();
	void ShowAutoCalculateControl(BOOL bShow);
	void GetParseToken(CString strList, CString sToken, CStringArray &sArr);

	

protected:
	virtual void OnOK();

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedCoporationChargeCheck();	
	afx_msg void OnCbnSelchangeReportSecondDayCombo();
	afx_msg void OnCbnSelchangeReportFirstDayCombo();
	afx_msg void OnBnClickedSearchChargeListBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedAutoChargeCreateCheck();

	CComboBox m_cmbChargeType;
	CComboBox m_cmbReportFirstDay;
	CComboBox m_cmbReportSecondDay;
	CComboBox m_cmbAbleUseCharge;
	CComboBox m_cmbInitDay;
	CComboBox m_cmbInterCallNotViewAmount;
	CComboBox m_cmbDirectDiscount;
	CComboBox m_cmbAddTaxApplyType;
	CComboBox m_cmbAutoCalculate;
	CComboBox m_cmbTaxType;
	CComboBox m_cmbPayMentAdd;
	CComboBox m_cmbBillCollectionAdd;
	
	CButton m_chkIntercallGroupOwner;
	CButton m_chkCredit;	
	CButton m_chkAutoChargeCreate;
	CButton m_chkManagerIsOrderInput;
	CButton m_chkCashApply;
	CButton m_chkCreditApply;
	CButton m_chkOnlineApply;
	CButton m_chkTransApply;
	CButton m_chkNotShowCash;
	CButton m_chkCoporationCharge;

	CButton m_chkGNoAll;
	CButton m_chkGNoPerson;
	CButton m_chkGNoMulti;

	CButton m_btnGNoInit;
	CButton m_btnGNoAdd;
	CButton m_btnGNoDel;
	CButton m_btnGNoFull;
	CDataBox m_lstGNo;

	CMyStatic m_stcGNoReportCount;
	CMyStatic m_stcLengthStatic;
	CFlatEdit2 m_edtDiscount;	
	CFlatEdit2 m_edtDirectDiscount;
	CFlatEdit2 m_edtDirectDiscouintRange;
	
	CString m_strID;
	CString m_strDept;
	CString m_strPwd;
	CString m_strName;
	CString m_strEmail;
	CString m_strMemberTel;
	CString m_strRiderDeposit;
	CString m_strDetaileEtc;
	CString m_strPresident;
	CString m_strBussinessNo;
	CString m_strBusinessStatus;
	CString m_strBussinessCategroy;
	CString m_strArea;
	CString m_strDirectDiscountRange;
	CString m_strDirectDiscount;
	CString m_strAbleUseCharge;
	CString m_strDiscount;
	CString	m_strGroupName;
	CString m_strManagerHP;

	BOOL m_bCredit;
	BOOL m_bAdd;	
	
	long m_nCompany;
	long m_nGNo;
	int m_nAddTaxApplyType;

	BOOL m_bCashApply;
	BOOL m_bCreditApply;
	BOOL m_bOnlineApply;
	BOOL m_bTransApply;

	BOOL m_bDirtyDiscount;
	long m_nDirtyDiscount;
	BOOL m_bDirtyTaxApply;
	long m_nDirtyTaxApply;
	afx_msg void OnCbnSelchangeAutoCalculateCombo();
	afx_msg void OnBnClickedGnoInitBtn();
	afx_msg void OnBnClickedGnoAddBtn();
	afx_msg void OnBnClickedGnoAllCheck();
	afx_msg void OnBnClickedGnoDelBtn();
	afx_msg void OnBnClickedGnoFulllBtn();
	afx_msg void OnBnClickedGnoPersonCheck();
	afx_msg void OnBnClickedGnoMultiCheck();
};
