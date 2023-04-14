#pragma once



// COptionDlgSmartQuick 폼 뷰입니다.

class COptionDlgSmartQuick : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgSmartQuick)

protected:
	COptionDlgSmartQuick();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgSmartQuick();

public:
	enum { IDD = IDD_OPTION_DLG_SMART_QUICK };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTipBtn();
	BOOL Save(long nCompany, BOOL bAll);

	CButton m_chkUseAutoWithdraw;
	CEdit m_edtWithdrawAbleMileage;
	CEdit m_edtWithdrawAbleMileageMax;
	CComboBox m_cmbMonthlyWithdrawAbleMileage;
	CComboBox m_cmbDailyWithdrawAbleMileageCount;
	CEdit m_edtMileageToCashPer;


	void RefreshData(CMkRecordset *pRs);
	afx_msg void OnBnClickedEventDlgBtn();
	void ChangeBoardItem(long nBoardIndex);
	CButton m_chkUseEventBoard;

	long m_nBoard1;
	long m_nBoard2;
	long m_nBoard3;
	long m_nMoreInfo1;
	long m_nMoreInfo2;
	long m_nMoreInfo3;
	long m_nEventBoard;

	CEdit m_edtChargeEtc;
	CEdit m_edtPayTypeEtc0;
	CEdit m_edtPayTypeEtc1;
	CEdit m_edtPayTypeEtc2;
	CEdit m_edtPayTypeEtc3;
	CEdit m_edtPayTypeEtc4;
	CEdit m_edtPayTypeEtc6;
	CEdit m_edtPayTypeEtc7;

	CEdit m_edtCarTypeWeightEtc0;
	CEdit m_edtCarTypeWeightEtc2;
	CEdit m_edtCarTypeWeightEtc3;
	CEdit m_edtCarTypeWeightEtc4;
	CEdit m_edtCarTypeWeightEtc5;

	CEdit m_edtCarTypeEtc0;
	CEdit m_edtCarTypeEtc2;
	CEdit m_edtCarTypeEtc3;
	CEdit m_edtCarTypeEtc4;
	CEdit m_edtCarTypeEtc5;

	CEdit m_edtCustomerEtc1;
	CEdit m_edtCustomerEtc2;
	CEdit m_edtCustomerEtc3;
	CEdit m_edtCustomerEtc4;

	CEdit m_edtItemTypeEtc1;
	CEdit m_edtItemTypeEtc2;
	CEdit m_edtItemTypeEtc3;
	CEdit m_edtItemTypeEtc4;
	CEdit m_edtItemTypeEtc5;

	CButton m_chkUsePayCash;
	CButton m_chkUseRunType1;

	CButton m_chkUseInquiryCharge;
	CEdit m_edtInquiryChargeMent;

	CButton m_chkUseCustomerChargeChange;
	CEdit m_edtChargeChangeMin;
	CEdit m_edtChargeChangeMax;
	CEdit m_edtChargeChangeMent;
	CButton m_chkNotRcpZeroCharge;

	virtual void OnInitialUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSetAppTimeBtn();
	afx_msg void OnBnClickedSetBoxAddChargeBtn();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedHelpBtn();
};


