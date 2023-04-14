#pragma once

// COptionDlgInterCall �� ���Դϴ�.

class COptionDlgInterCall2 : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgInterCall2)

protected:
	COptionDlgInterCall2();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~COptionDlgInterCall2();

public:
	enum { IDD = IDD_OPTION_DLG_INTERCALL2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	

	BOOL Save(long nCompany, BOOL bAll);
	virtual void OnInitialUpdate();

	// ������
	CButton m_chkInterCallRiderPhoneView;
			
	CButton m_chkEtcInterCallCopy;
	CButton m_CompanyWorkingCheck;
	CButton m_SlowOrderCheck;
	CEdit m_SlowMsgEdit;
	CEdit m_SlowChargeEdit;

	CEdit m_edtIntercallName;
	CString m_strIntercallName;

	BOOL m_bCompanyWorking;
	BOOL m_bUseSlowOrder;
	CString m_strSlowMsg;
	CString m_sSlowMsg;
	CString m_strSlowCharge;
	CButton m_chkICDisplayType;
	BOOL m_bICDisplayType;
	
	CButton m_chkTransOpen;
	CComboBox m_cmbChargeOpenType;
	CComboBox m_cmbReceiptType;
	int m_nChargeOpenType;
	BOOL m_bTransOpen;
	CString m_sICBanner;	
	CString m_sICDisplayName;
	afx_msg void OnBnCancelBTN();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSlowOrderCheck();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedIcDisplayTypeChk();
	afx_msg void OnCbnSelchangeChargeOpenTypeCombo();
	afx_msg void OnBnClickedPreViewBtn();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	// ��
	
	CButton m_chkInternetCardNotUse;
	CButton m_chkMileage;
	CButton m_chkPayMent;

	CButton m_chkWayUse;
	CEdit m_edtWayAddAmount;
	CEdit m_edtNightReceiptCallSMS;
	CEdit m_edtAccountInfo;
	CEdit m_edtAccountInfoOwner;
	CEdit m_edtBgColor;
	CEdit m_edtFontColor;
	CEdit m_edtRunAddAmount;
	CEdit	m_edtWebAddress;
	CEdit m_edtReciptStop;


	CButton m_chkReceiptStop;	
	CButton m_btnWebInterWorkTime;
	CButton m_chkRunUse;
	CComboBox m_cmbIntercallNotViewAmount;
	CComboBox m_cmbInterCallReceiptState;
	CComboBox m_cmbWebChargeType;
	CComboBox m_cmbWebReceiptState;
	CButton m_chkChargeListUse;
	CButton m_chkCouphonUse;
	CButton m_chkBBSUse;
	CButton	m_chkOnLinePayUse;
	CButton	m_chkInnerFrameUse;
	CButton m_chkSettleMentTax;

	CXTColorPicker m_btnBgColor;
	CXTColorPicker m_btnFontColor;
	
	
	afx_msg void OnBnClickedWebInterWorkTime();
	afx_msg void OnBnClickedOnlinepayCheck();
	afx_msg void OnBnClickedInnerframeuseCheck();	
	afx_msg void OnBnClickedBgcolorBtn();
	afx_msg void OnBnClickedFontcolorBtn();
	afx_msg void OnBnClickedInternetCardNotUse();
	afx_msg void OnNMThemeChangedBgcolorBtn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedWebBtn();
	afx_msg void OnBnClickedIntercallBtn();
	afx_msg void OnPaint();
};


