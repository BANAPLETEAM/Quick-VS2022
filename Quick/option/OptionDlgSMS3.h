#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// COptionDlgSMS3 폼 뷰입니다.

class COptionDlgSMS3 : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgSMS3)

protected:
	COptionDlgSMS3();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgSMS3();

public:
	enum { IDD = IDD_OPTION_DLG_SMS3 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
public:

	BOOL Save(long nCompany, BOOL bAll);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitControl();
	BOOL CheckData();
	
	bool m_bIntegrated;

	// 배차관련 변수

	BOOL	m_bSMSOfRider;	
	BOOL	m_bSMSOfCompany;
	BOOL	m_bSMSOfIns;
	BOOL	m_bSMSOfInsRider;
	BOOL	m_bSaveMent;


	BOOL	m_bUseCancelSMS;
	CString m_strCancelSMSText;
	CString m_strBankAccountSMS;

	CButton m_RiderCheck;
	CButton m_CompanyCheck;	
	CButton m_InsCheck;	
	CButton m_InsRiderCheck;
	CButton m_rdoSMSSendCompanyName;
	CButton m_rdoSMSSendBranchName;
	CButton m_SaveMentChk;
	CComboBox m_AllocateSMSDelayCombo;
	CButton m_CancelSMSCheck;	
	CEdit		m_CancelSMSEdit;	
	CButton m_rdoRandomCompanyTel;
	CButton m_rdoRandomOfficeTel;
	CStatic m_LengthStatic;
	afx_msg void OnBnClickedSmsOfSaveMentCheck();
	afx_msg void OnBnClickedLookAheadButton();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedSmsOfRiderCheck();
	afx_msg void OnBnClickedSmsOfCompanyCheck();
	afx_msg void OnBnClickedSmsOfInsCheck();
	afx_msg void OnBnClickedSmsOfInsCheck2();
	afx_msg void OnBnClickedCancelSmsCheck();
	afx_msg void OnEnChangeCancelSmsEdit();	
	//	afx_msg void OnBnHotItemChangeSmsOfSaveMentCheck(NMHDR *pNMHDR, LRESULT *pResult);




	// 종료관련 변수
	CStatic m_LengthStatic2;
	CButton m_SmsOfRiderNameChk;
	CButton m_SmsOfDt1Chk;	
	CButton m_chkSmsOfBanner;
	CEdit m_edtCompleteBannerSms;	
	CButton m_SmsOfEtcChk;
	CEdit m_CompleteSmsEdt;	
	CButton m_chkSendCompleteSmsForRiderComplete;	
	CButton m_chkUseHappyCallCompleted;	
	CDateTimeCtrl m_dtpHappyCallCompleted;

	COleDateTime m_dtHappyCallCompleted;
	
	BOOL m_bSmsOfDt1;
	BOOL m_bSmsOfEtc;
	CString m_sCompleteSms;
	BOOL m_bSmsOfBanner;
	CString m_sCompleteBannerSms;
	BOOL m_bSendCompleteSmsForRiderComplete;
	BOOL m_bSmsOfRiderName;
	
	afx_msg void OnBnClickedSmsOfRiderNameCheck();
	afx_msg void OnBnClickedSmsOfDt1Check();
	afx_msg void OnBnClickedSmsOfEtcCheck();
	afx_msg void OnEnChangeCompleteSmsEdit();
	afx_msg void OnBnClickedSettingFTypeBtn();
	afx_msg void OnBnClickedSmsOfBannerCheck();
	afx_msg void OnBnClickedSettingHappyMentBtn();

	// 취소관련변수
	
	CButton m_chkUseHappyCallCancel;	
	CEdit m_edtHappyCallMentCancel;	
	COleDateTime m_dtHappyCallCancel;
	CDateTimeCtrl m_dtpHappyCallCancel;
	
	// 기사 개별메세지

	CButton m_chkSendOnePage;
	CComboBox m_AllocateSmsTypeCmb;
	CComboBox m_cmbFirstPage;
	CComboBox m_cmbSecondPage;
	CComboBox m_cmbThirdPage;
	int m_nAllocateSMSType;	
	BOOL m_bSendOnePage;
	
	CEdit m_edtAllocateSmsFType;
	CString m_strAllocateSmsFType;
	CEdit m_edtAllocateCustomerSms;
	CString m_strAllocateCustomerSms;
	    	
	CButton m_rdoRiderPhone;
	CButton m_rdoCompanyPhone;

	//문의관련
	afx_msg void OnBnClickedInqueryHappyMsgBtn();
	CEdit m_edtHappyCallMentInquiry;
	CString m_strHappyCallMentInquiry;
	CButton m_chkUseHappyCallInquiry;	
	BOOL m_bUseHappyCallInquiry;
	CDateTimeCtrl m_dtpHappyCallInquery;
	COleDateTime m_dtHappyCallInquiry;

	afx_msg void OnBnClickedPickupMsgBtn();
	BOOL m_bPickupSms;
	CString m_strPickupSms;
	CEdit m_edtPickupSms;
	BOOL m_bPickupSms2;
	CString m_strPickupSms2;
	CEdit m_edtPickupSms2;
	afx_msg void OnBnClickedPickupMsgBtn2();
	afx_msg void OnBnClickedCancelHappyMsgBtn();
	afx_msg void OnBnClickedUseHappyCallFinishCheck();
	afx_msg void OnBnClickedUseHappyCallCancelCheck();
	afx_msg void OnBnClickedUseHappyCallInquiryCheck();
	afx_msg void OnBnClickedInqueryHappyMsgTodayBtn();

	CEdit m_edtHappyCallMentInquiryToday;
	CString m_strHappyCallMentInquiryToday;
	CButton m_chkUseHappyCallInquiryToday;
	BOOL m_bUseHappyCallInquiryToday;

	CComboBox m_cmbHappyCallDelayInquiryToday;
	afx_msg void OnBnClickedUseHappyCallInquiryTodayCheck();
	afx_msg void OnBnClickedInqueryHappyMsgTodayBtn2();

	CEdit m_edtHappyCallMentCancelToday;
	CString m_strHappyCallMentCancelToday;
	CButton m_chkUseHappyCallCancelToday;
	BOOL m_bUseHappyCallCancelToday;

	CComboBox m_cmbHappyCallDelayCancelToday;

	afx_msg void OnBnClickedUseHappyCallCancelTodayCheck();
	afx_msg void OnBnClickedShowUrlBtn();
	afx_msg void OnBnClickedShowUrlBtn2();
	CEdit m_edtCompanyAppUrl;
	CEdit m_edtCompanyHomePage;
	CEdit m_edtCompanyLogoImage;
	CString m_strCompanyAppUrl;
	CString m_strCompanyHomePage;
	CString m_strCompanyLogoImage;
	CButton m_chkUsePreSms;
	CComboBox m_cmbPreSmsDay;
	CComboBox m_cmbPreSmsTerm;
	CEdit m_edtPreSmsMent;
	afx_msg void OnBnClickedPreSmsBtn();

	long ComboToSqlDay(long nItem);
	void SqlDayToCombo(CComboBox *pBox, long nDay);
	CComboBox m_cmbPreSmsSendTime;
	afx_msg void OnPaint();
	CComboBox m_cmbCompleteSmsDelay;
};


