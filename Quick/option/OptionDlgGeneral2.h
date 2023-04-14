#pragma once
#include "afxwin.h"
// COptionDlgGeneral2 폼 뷰입니다.

class COptionDlgGeneral2 : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgGeneral2)

protected:
	COptionDlgGeneral2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgGeneral2();

public:
	enum { IDD = IDD_OPTION_DLG_GENERAL2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg long OnRefresh(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedMileageCheck();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	BOOL Save(long nCompany, BOOL bAll);

	CFlatEdit2		m_RcpTimeColorEdit1;
	CFlatEdit2		m_RcpTimeColorEdit2;
	CFlatEdit2		m_RcpTimeColorEdit3;
	CString		m_strRcpTimeColor1;
	CString		m_strRcpTimeColor2;
	CString		m_strRcpTimeColor3;	
	BOOL		m_bWaitSecondCall;
	BOOL m_bDistaceCharge;
	long		m_nDistanceCharge;

	CButton	m_WaitSecondCallCheck;
	CButton	m_NoUseCNSCheck;
	CButton m_UserIDSequenceCheck;	
	CButton m_chkMemoToEtc;
	CButton m_chkSingleAllocate;
	CButton		m_chkUsageHistory;	
	CButton m_GiveChargeRider;
	CButton m_chkDisableCreditBtn;
	CButton m_chkUserDongPos;
	CButton m_chkUseOrderChangeMent;
	CButton m_chkUseRTIDOnSpeedAllocate;
	CButton m_chkUsePayBonggoFromLabo;
	CButton m_chkUseCardTax;
	CButton m_chkNotUseEtcForCancel;
	CButton m_chkRiderMemoToEtc;
	CButton m_chkCallerIDToPhone1;
	CButton m_chkFirstWaitTimePast;// IDC_FIRST_RECEIPT_WAIT_CHANGE_TIME_CHECK

	CButton m_btnCarType1;
	CButton m_btnCarType2;
	CButton m_btnCarType3;
	CButton m_btnPayType1;
	CButton m_btnPayType2;
	CButton m_btnPayType3;
	CButton m_btnPayType4;
	CButton m_btnTankAllView;
	CStatic m_stcTank;
	
	CComboBox m_cmbConsignPopup; 

	BOOL m_bNoUseCNS;	
	BOOL m_bMemoToEtc;	
	BOOL m_bSingleAllocate;
	BOOL m_bUsageHistory;
	BOOL m_bGiveChargeRider;
	BOOL m_bDisableCreditBtn;	
	BOOL m_bUseOrderChangeMent;	
	BOOL m_bUseRTIDOnSpeedAllocate;	
	BOOL m_bUseCardTax;
	BOOL m_bNotUseEtcForCancel;
	BOOL m_bRiderMemoToEtc;
	BOOL m_bCallerIDToPhone1;
	BOOL m_bFirstWaitTimePast;

	long m_nCarType1;
	long m_nCarType2;
	long m_nCarType3;

	long m_nPayType1;
	long m_nPayType2;
	long m_nPayType3;
	long m_nPayType4;

	long m_nLastSelCarBtn;
	long m_nLastSelPayBtn;

	CButton m_chkClearDestForAfterCopy;
	BOOL m_bClearDestForAfterCopy; 
	CButton m_chkHistoryDetailAllView;
	CButton m_chkFocusToWaitBtn;
	BOOL m_bFocusToWaitBtn; 
	BOOL m_bShowTank;
	long m_nTankType;

	CButton m_btnCarType4;
	CButton m_btnCarType5;
	CButton m_btnPayType5;
	long m_nCarType4;
	long m_nCarType5;
	long m_nPayType5;
		
	afx_msg void OnMenuContextCarType(UINT nFlag);
	afx_msg void OnMenuContextPayType(UINT nFlag);

	afx_msg void OnBnClickedCarTypeBtn1();
	afx_msg void OnBnClickedCarTypeBtn2();
	afx_msg void OnBnClickedCarTypeBtn3();
	afx_msg void OnBnClickedPayTypeBtn1();
	afx_msg void OnBnClickedPayTypeBtn2();
	afx_msg void OnBnClickedPayTypeBtn3();

	void OpenPayContextMenu(long nSel);
	void OpenCarContextMenu(long nSel);
	void SavePayType(long nPayType);
	void SaveCarType(long nCarType);
	void SetCarOrder(CString strCarTypeOrder);
	void SetPayOrder(CString strPayTypeOrder);

	afx_msg void OnBnClickedPayTypeBtn4();

	BOOL m_bAutoShareOrder;
	CString m_strAutoShareTime;
	CButton m_chkAutoShareOrder;
	CFlatEdit2 m_edtAutoShareTime;
	afx_msg void OnBnClickedAutoShareOrderCheck();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString  m_strRevisitCustomerSendDay;
	CFlatEdit2 m_edtRevisitCustomerSendDay;
	CFlatEdit2 m_edtTaxUseEmail; 
	
	CButton m_chkRevisitCustomer;
	afx_msg void OnBnClickedRevisitCustomerCheck();
	afx_msg void OnBnClickedTankAllViewButton();
	CButton m_chkUseOrderBundle;
	BOOL m_bUseOrderBundle;

	BOOL m_bCancelToInquiry;
	CButton m_chkCancelToInquiry;

	CButton m_chkEtcAuto;
	BOOL m_bEtcAuto;

	CButton m_chkCancelReason;
	BOOL m_bCancelReason;

	CButton m_chkInitDongInfo;
	BOOL m_bInitDongInfo;
	CButton m_chkCreditListPopup;
	BOOL m_bCreditListPopup;

	CButton m_chkNoDestPoi;
	BOOL m_bNoDestPoi;
	CButton m_chkNotClientPhone1;
	BOOL m_bNotClientPhone1;
	CButton m_chkNotCustomerAddCID;
	BOOL m_bNotCustomerAddCID;

	BOOL m_bCustomerAutoInsert;
	CButton m_chkCustomerAutoInsert;

	afx_msg void OnBnClickedCallerIDToPhone1();

	CString m_strEtcAuto;
	CEdit m_edtEtcAuto;
	CButton m_chkCompanyTelHidden;
	CButton m_chkMyCallRiderDeposit;
	CButton m_btnMyCallRiderDeposit;
	afx_msg void OnBnClickedMyCallBtn();
	afx_msg void OnBnClickedMycallRiderDepositCheck();
	afx_msg void OnBnClickedCarTypeBtn4();
	afx_msg void OnBnClickedCarTypeBtn5();
	afx_msg void OnBnClickedPayTypeBtn5();
	CButton m_chkInsertPhoneToInterCallID;
	BOOL m_bInsertPhoneToInterCallID;
	CEdit m_edtInterCallPassword;
	CString m_strInterCallPassword;
	afx_msg void OnBnClickedTipButton();
	afx_msg void OnBnClickedFirstReceiptWaitChangeTimeCheck(); 

	BOOL m_bNotChangedt1ForDelay;
	CButton m_chkNotChangedt1ForDelay;
	CEdit m_edtNewCustomerName;
	CString m_strNewCustomerName;
	afx_msg void OnBnClickedHistoryDetailAllView();
	CButton m_chkPopupFocus;
	BOOL m_bPopupFocus;
	CButton m_chkColorChange;
	BOOL m_bColorChange;
	CButton m_chkOnlyLoadInsRider;
	BOOL m_bOnlyLoadInsRider;
	CButton m_chkVRAccountNoRider;
	BOOL m_bVRAccountNoRider;
	CButton m_chkInitDt1StateToRcp;

	CEdit m_edtAutoDelay;
	CString m_strAutoDelay;	
	CButton m_chkAutoDelay;
	BOOL m_bAutoDelay;
	
	afx_msg void OnPaint();
	CComboBox m_cmbCnsSearchType1;
	CComboBox m_cmbCnsSearchType2;
	CComboBox m_cmbCnsSearchPaid;
	afx_msg void OnBnClickedKakaoHelpBtn();
	CEdit m_edtKakaoKey;
	CString m_strKakaoKey;
	CButton m_chkKeepChargeCompany;
};


