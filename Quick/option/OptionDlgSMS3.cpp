// OptionDlgSMS3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgSMS3.h"
#include "AllocateSMSFSettingDlg.h"
#include "MainOptionDlg2011.h"
// COptionDlgSMS3

IMPLEMENT_DYNCREATE(COptionDlgSMS3, CMyFormView)

COptionDlgSMS3::COptionDlgSMS3()
: CMyFormView(COptionDlgSMS3::IDD)	
, m_nAllocateSMSType(0)
, m_bSendOnePage(FALSE)
, m_sCompleteBannerSms(_T(""))
, m_strAllocateSmsFType(_T(""))
, m_strHappyCallMentInquiry(_T(""))
, m_bUseHappyCallInquiry(FALSE)
, m_dtHappyCallInquiry(COleDateTime::GetCurrentTime())
, m_bPickupSms(FALSE)
, m_strPickupSms(_T(""))
, m_dtHappyCallCompleted(COleDateTime::GetCurrentTime())
, m_dtHappyCallCancel(COleDateTime::GetCurrentTime())
, m_strCompanyAppUrl(_T(""))
, m_strCompanyHomePage(_T(""))
, m_strCompanyLogoImage(_T(""))
{
	m_nAllocateSMSType = 0;
	m_strBankAccountSMS = "";
	 m_bSaveMent =FALSE;
}

COptionDlgSMS3::~COptionDlgSMS3()
{
}

void COptionDlgSMS3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	// 배차관련
	DDX_Control(pDX, IDC_SMS_OF_RIDER_CHECK, m_RiderCheck);
	DDX_Control(pDX, IDC_SMS_OF_COMPANY_CHECK, m_CompanyCheck);
	DDX_Control(pDX, IDC_SMS_OF_INS_CHECK, m_InsCheck);
	DDX_Control(pDX, IDC_SMS_OF_INS_CHECK2, m_InsRiderCheck);
	DDX_Control(pDX, IDC_SEND_SMSCOMPANY_RADIO, m_rdoSMSSendCompanyName);
	DDX_Control(pDX, IDC_SEND_BRANCH_RADIO, m_rdoSMSSendBranchName);
	DDX_Control(pDX, IDC_SMS_OF_SAVE_MENT_CHECK, m_SaveMentChk);
	DDX_Control(pDX, IDC_ALLOCATE_SMS_DELAY_COMBO, m_AllocateSMSDelayCombo);
	DDX_Control(pDX, IDC_CANCEL_SMS_CHECK, m_CancelSMSCheck);
	DDX_Control(pDX, IDC_CANCEL_SMS_EDIT, m_CancelSMSEdit);
	DDX_Control(pDX, IDC_RANDOM_COMPANYTEL_RADIO, m_rdoRandomCompanyTel);
	DDX_Control(pDX, IDC_RANDOM_OFFICETEL_RADIO, m_rdoRandomOfficeTel);


	DDX_Check(pDX, IDC_SMS_OF_RIDER_CHECK, m_bSMSOfRider);	
	DDX_Check(pDX, IDC_SMS_OF_COMPANY_CHECK, m_bSMSOfCompany);
	DDX_Check(pDX, IDC_SMS_OF_INS_CHECK, m_bSMSOfIns);
	DDX_Check(pDX, IDC_SMS_OF_INS_CHECK2, m_bSMSOfInsRider);
	DDX_Check(pDX, IDC_SMS_OF_SAVE_MENT_CHECK, m_bSaveMent);
	DDX_Check(pDX, IDC_CANCEL_SMS_CHECK, m_bUseCancelSMS);
	DDX_Text(pDX, IDC_CANCEL_SMS_EDIT, m_strCancelSMSText);
	DDX_Control(pDX, IDC_LENGTH_STATIC2, m_LengthStatic2);
	DDX_Text(pDX, IDC_EDIT_BANK_ACCOUNT_SMS, m_strBankAccountSMS);


	// 종료관련
	DDX_Control(pDX, IDC_LENGTH_STATIC, m_LengthStatic);
	DDX_Control(pDX, IDC_SMS_OF_RIDER_NAME_CHECK, m_SmsOfRiderNameChk);
	DDX_Control(pDX, IDC_SMS_OF_DT1_CHECK, m_SmsOfDt1Chk);
	DDX_Control(pDX, IDC_SMS_OF_BANNER_CHECK, m_chkSmsOfBanner);
	DDX_Control(pDX, IDC_COMPLETE_BANNER_SMS_EDIT, m_edtCompleteBannerSms);
	DDX_Control(pDX, IDC_SMS_OF_ETC_CHECK, m_SmsOfEtcChk);
	DDX_Control(pDX, IDC_COMPLETE_SMS_EDIT, m_CompleteSmsEdt);
	DDX_Control(pDX, IDC_SEND_COMPLETE_SMS_FOR_RIDER_COMPLETE_CHECK, m_chkSendCompleteSmsForRiderComplete);

	DDX_Check(pDX, IDC_SMS_OF_RIDER_NAME_CHECK, m_bSmsOfRiderName);
	DDX_Check(pDX, IDC_SMS_OF_DT1_CHECK, m_bSmsOfDt1);
	DDX_Check(pDX, IDC_SMS_OF_ETC_CHECK, m_bSmsOfEtc);
	DDX_Text(pDX, IDC_COMPLETE_SMS_EDIT, m_sCompleteSms);

	DDX_Text(pDX, IDC_COMPLETE_BANNER_SMS_EDIT, m_sCompleteBannerSms);
	DDX_Check(pDX, IDC_SMS_OF_BANNER_CHECK, m_bSmsOfBanner);

	DDX_Control(pDX, IDC_USE_HAPPY_CALL_FINISH_CHECK, m_chkUseHappyCallCompleted);
	DDX_DateTimeCtrl(pDX, IDC_HAPPY_CALL_FINISH_DTP, m_dtHappyCallCompleted);
	DDX_Control(pDX, IDC_HAPPY_CALL_FINISH_DTP, m_dtpHappyCallCompleted);

	DDX_Check(pDX, IDC_SEND_COMPLETE_SMS_FOR_RIDER_COMPLETE_CHECK, m_bSendCompleteSmsForRiderComplete);

	// 취소관련


	DDX_Control(pDX, IDC_USE_HAPPY_CALL_CANCEL_CHECK, m_chkUseHappyCallCancel);
	DDX_Control(pDX, IDC_HAPPY_CALL_CANCEL_DTP,		 m_dtpHappyCallCancel);
	DDX_DateTimeCtrl(pDX, IDC_HAPPY_CALL_CANCEL_DTP, m_dtHappyCallCancel);	
	DDX_Control(pDX, IDC_HAPPY_CALL_MENT_CANCEL_EDIT , m_edtHappyCallMentCancel);

	// 문의관련	
	DDX_Control(pDX, IDC_HAPPY_CALL_INQUIRY_DTP, m_dtpHappyCallInquery);
	DDX_DateTimeCtrl(pDX, IDC_HAPPY_CALL_INQUIRY_DTP, m_dtHappyCallInquiry);

	// 기사 개별
	DDX_Control(pDX, IDC_SEND_ONE_PAGE_CHECK, m_chkSendOnePage);
	DDX_Control(pDX, IDC_ALLOCATE_SMS_TYPE_CMB, m_AllocateSmsTypeCmb);
	DDX_Control(pDX, IDC_FIRST_PAGE_COMBO, m_cmbFirstPage);
	DDX_Control(pDX, IDC_SECOND_PAGE_COMBO, m_cmbSecondPage);
	DDX_Control(pDX, IDC_THIRD_PAGE_COMBO, m_cmbThirdPage);

	DDX_Check(pDX, IDC_SEND_ONE_PAGE_CHECK, m_bSendOnePage);
	DDX_CBIndex(pDX, IDC_ALLOCATE_SMS_TYPE_CMB, m_nAllocateSMSType);

	DDX_Control(pDX, IDC_LENGTH_STATIC, m_LengthStatic);

	DDX_Control(pDX, IDC_ALLOCATE_SMS_F_TYPE_EDIT, m_edtAllocateSmsFType);
	DDX_Text(pDX, IDC_ALLOCATE_SMS_F_TYPE_EDIT, m_strAllocateSmsFType);

	DDX_Control(pDX, IDC_ALLOCATE_CUSTOMER_SMS_EDIT, m_edtAllocateCustomerSms);
	DDX_Text(pDX, IDC_ALLOCATE_CUSTOMER_SMS_EDIT, m_strAllocateCustomerSms);
	DDX_Control(pDX, IDC_SEND_COMPANY_PHONE_RADIO, m_rdoCompanyPhone);
	DDX_Control(pDX, IDC_SEND_RIDER_PHONE_RADIO, m_rdoRiderPhone);
	DDX_Control(pDX, IDC_HAPPY_CALL_MENT_INQUIRY_EDIT, m_edtHappyCallMentInquiry);
	DDX_Text(pDX, IDC_HAPPY_CALL_MENT_INQUIRY_EDIT, m_strHappyCallMentInquiry);
	DDX_Control(pDX, IDC_USE_HAPPY_CALL_INQUIRY_CHECK, m_chkUseHappyCallInquiry);
	DDX_Check(pDX, IDC_USE_HAPPY_CALL_INQUIRY_CHECK, m_bUseHappyCallInquiry);


	DDX_Check(pDX, IDC_PICKUP_SMS_CHECK, m_bPickupSms);
	DDX_Text(pDX, IDC_PICKUP_SMS_EDIT, m_strPickupSms);
	DDX_Control(pDX, IDC_PICKUP_SMS_EDIT, m_edtPickupSms);

	DDX_Check(pDX, IDC_PICKUP_SMS_CHECK2, m_bPickupSms2);
	DDX_Text(pDX, IDC_PICKUP_SMS_EDIT2, m_strPickupSms2);
	DDX_Control(pDX, IDC_PICKUP_SMS_EDIT2, m_edtPickupSms2);

	DDX_Control(pDX, IDC_HAPPY_CALL_MENT_INQUIRY_TODAY_EDIT, m_edtHappyCallMentInquiryToday);
	DDX_Text(pDX, IDC_HAPPY_CALL_MENT_INQUIRY_TODAY_EDIT, m_strHappyCallMentInquiryToday);
	DDX_Control(pDX, IDC_USE_HAPPY_CALL_INQUIRY_TODAY_CHECK, m_chkUseHappyCallInquiryToday);
	DDX_Check(pDX, IDC_USE_HAPPY_CALL_INQUIRY_TODAY_CHECK, m_bUseHappyCallInquiryToday);

	DDX_Control(pDX, IDC_HAPPY_CALL_DELAY_INQUIRY_TODAY_COMBO, m_cmbHappyCallDelayInquiryToday);

	DDX_Control(pDX, IDC_HAPPY_CALL_MENT_CANCEL_TODAY_EDIT, m_edtHappyCallMentCancelToday);
	DDX_Text(pDX, IDC_HAPPY_CALL_MENT_CANCEL_TODAY_EDIT, m_strHappyCallMentCancelToday);
	DDX_Control(pDX, IDC_USE_HAPPY_CALL_CANCEL_TODAY_CHECK, m_chkUseHappyCallCancelToday);
	DDX_Check(pDX, IDC_USE_HAPPY_CALL_CANCEL_TODAY_CHECK, m_bUseHappyCallCancelToday);

	DDX_Control(pDX, IDC_HAPPY_CALL_DELAY_CANCEL_TODAY_COMBO, m_cmbHappyCallDelayCancelToday);
	DDX_Control(pDX, IDC_COMPANY_APP_URL_EDIT, m_edtCompanyAppUrl);
	DDX_Control(pDX, IDC_COMPANY_HOME_PAGE_EDIT, m_edtCompanyHomePage);
	DDX_Control(pDX, IDC_COMPANY_LOGO_IMAGE_EDIT, m_edtCompanyLogoImage);
	DDX_Text(pDX, IDC_COMPANY_APP_URL_EDIT, m_strCompanyAppUrl);
	DDX_Text(pDX, IDC_COMPANY_HOME_PAGE_EDIT, m_strCompanyHomePage);
	DDX_Text(pDX, IDC_COMPANY_LOGO_IMAGE_EDIT, m_strCompanyLogoImage);
	DDX_Control(pDX, IDC_USE_PRE_SMS_CHECK, m_chkUsePreSms);
	DDX_Control(pDX, IDC_PRE_SMS_DAY_COMBO, m_cmbPreSmsDay);
	DDX_Control(pDX, IDC_PRE_SMS_TERM_COMBO, m_cmbPreSmsTerm);
	DDX_Control(pDX, IDC_PRE_SMS_MENT_EDIT, m_edtPreSmsMent);
	DDX_Control(pDX, IDC_PRE_SMS_SEND_TIME_COMBO, m_cmbPreSmsSendTime);
	DDX_Control(pDX, IDC_COMPLETE_SMS_DELAY_COMBO, m_cmbCompleteSmsDelay);
}

BEGIN_MESSAGE_MAP(COptionDlgSMS3, CMyFormView)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_SMS_OF_RIDER_NAME_CHECK, OnBnClickedSmsOfRiderNameCheck)
	ON_BN_CLICKED(IDC_SMS_OF_DT1_CHECK, OnBnClickedSmsOfDt1Check)
	ON_BN_CLICKED(IDC_SMS_OF_ETC_CHECK, OnBnClickedSmsOfEtcCheck)
	ON_EN_CHANGE(IDC_COMPLETE_SMS_EDIT, OnEnChangeCompleteSmsEdit)
	ON_BN_CLICKED(IDC_SETTING_F_TYPE_BTN, OnBnClickedSettingFTypeBtn)
	ON_BN_CLICKED(IDC_SMS_OF_BANNER_CHECK, &COptionDlgSMS3::OnBnClickedSmsOfBannerCheck)
	ON_BN_CLICKED(IDC_SMS_OF_RIDER_CHECK, OnBnClickedSmsOfRiderCheck)
	ON_BN_CLICKED(IDC_SMS_OF_COMPANY_CHECK, OnBnClickedSmsOfCompanyCheck)
	ON_BN_CLICKED(IDC_SMS_OF_INS_CHECK, OnBnClickedSmsOfInsCheck)
	ON_BN_CLICKED(IDC_SMS_OF_INS_CHECK2, OnBnClickedSmsOfInsCheck2)
	ON_BN_CLICKED(IDC_CANCEL_SMS_CHECK, OnBnClickedCancelSmsCheck)
	ON_EN_CHANGE(IDC_CANCEL_SMS_EDIT, OnEnChangeCancelSmsEdit)
//	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_SMS_OF_SAVE_MENT_CHECK, OnBnHotItemChangeSmsOfSaveMentCheck)
	ON_BN_CLICKED(IDC_SMS_OF_SAVE_MENT_CHECK, OnBnClickedSmsOfSaveMentCheck)
	ON_BN_CLICKED(IDC_LOOK_AHEAD_BUTTON, OnBnClickedLookAheadButton)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SETTING_HAPPY_MENT_BTN, &COptionDlgSMS3::OnBnClickedSettingHappyMentBtn)
	ON_BN_CLICKED(IDC_INQUERY_HAPPY_MSG_BTN, &COptionDlgSMS3::OnBnClickedInqueryHappyMsgBtn)
	ON_BN_CLICKED(IDC_PICKUP_MSG_BTN, &COptionDlgSMS3::OnBnClickedPickupMsgBtn)
	ON_BN_CLICKED(IDC_PICKUP_MSG_BTN2, &COptionDlgSMS3::OnBnClickedPickupMsgBtn2)
	ON_BN_CLICKED(IDC_CANCEL_HAPPY_MSG_BTN, &COptionDlgSMS3::OnBnClickedCancelHappyMsgBtn)
	ON_BN_CLICKED(IDC_USE_HAPPY_CALL_FINISH_CHECK, &COptionDlgSMS3::OnBnClickedUseHappyCallFinishCheck)
	ON_BN_CLICKED(IDC_USE_HAPPY_CALL_CANCEL_CHECK, &COptionDlgSMS3::OnBnClickedUseHappyCallCancelCheck)
	ON_BN_CLICKED(IDC_USE_HAPPY_CALL_INQUIRY_CHECK, &COptionDlgSMS3::OnBnClickedUseHappyCallInquiryCheck)
	ON_BN_CLICKED(IDC_INQUERY_HAPPY_MSG_TODAY_BTN, &COptionDlgSMS3::OnBnClickedInqueryHappyMsgTodayBtn)
	ON_BN_CLICKED(IDC_USE_HAPPY_CALL_INQUIRY_TODAY_CHECK, &COptionDlgSMS3::OnBnClickedUseHappyCallInquiryTodayCheck)
	ON_BN_CLICKED(IDC_INQUERY_HAPPY_MSG_TODAY_BTN2, &COptionDlgSMS3::OnBnClickedInqueryHappyMsgTodayBtn2)
	ON_BN_CLICKED(IDC_USE_HAPPY_CALL_CANCEL_TODAY_CHECK, &COptionDlgSMS3::OnBnClickedUseHappyCallCancelTodayCheck)
	ON_BN_CLICKED(IDC_SHOW_URL_BTN, &COptionDlgSMS3::OnBnClickedShowUrlBtn)
	ON_BN_CLICKED(IDC_SHOW_URL_BTN2, &COptionDlgSMS3::OnBnClickedShowUrlBtn2)
	ON_BN_CLICKED(IDC_PRE_SMS_BTN, &COptionDlgSMS3::OnBnClickedPreSmsBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgSMS3 진단입니다.

#ifdef _DEBUG
void COptionDlgSMS3::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgSMS3::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


void COptionDlgSMS3::OnInitialUpdate()
{	 
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);

	if(!LF->POWER_CHECK(1303, "SMS"))
		EnableWindow(FALSE);

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 
	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;
 
	sizeTotal.cx = 150;  
	sizeTotal.cy = 1400;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


void COptionDlgSMS3::InitControl()
{
	/*
	if(m_SmsOfRiderNameChk.GetCheck() == BST_CHECKED)
	{
		m_CompleteSmsEdt.EnableWindow(FALSE);
		m_edtCompleteBannerSms.EnableWindow(FALSE);
	}
	else if(m_SmsOfDt1Chk.GetCheck() == BST_CHECKED)
	{ 
		m_CompleteSmsEdt.EnableWindow(FALSE);
		m_edtCompleteBannerSms.EnableWindow(FALSE);
	}		
	else if(m_SmsOfEtcChk.GetCheck() == BST_CHECKED)
	{
		m_edtCompleteBannerSms.EnableWindow(FALSE);
		m_CompleteSmsEdt.EnableWindow(TRUE);
	}
	else if(m_chkSmsOfBanner.GetCheck() == BST_CHECKED)
	{
		m_edtCompleteBannerSms.EnableWindow(TRUE);
		m_CompleteSmsEdt.EnableWindow(FALSE);
	}
	*/
}

// COptionDlgSMS3 메시지 처리기입니다.

int COptionDlgSMS3::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return TRUE;

	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


BOOL COptionDlgSMS3::CheckData()
{

	UpdateData(TRUE);

	long nHour  = 0;
	if(m_bUseHappyCallInquiry)
	{
		nHour = m_dtHappyCallInquiry.GetHour();

		if(nHour <= 9 || nHour >= 21)
		{
			MessageBox("오후 9시에서 오전 9시 사이는 문의 해피콜을 설정하실수 없습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}
	}


	if(m_chkUseHappyCallCancel.GetCheck())
	{
		nHour = m_dtHappyCallCancel.GetHour();

		if(nHour <= 9 || nHour >= 21)
		{
			MessageBox("오후 9시에서 오전 9시 사이는 취소 해피콜을 설정하실수 없습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}
	}


	if(m_chkUseHappyCallCompleted.GetCheck())
	{
		nHour = m_dtHappyCallCompleted.GetHour();

		if(nHour <= 9 || nHour >= 21)
		{
			MessageBox("오후 9시에서 오전 9시 사이는 종료 해피콜을 설정하실수 없습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if( m_bSmsOfRiderName == FALSE && m_bSmsOfDt1 == FALSE && m_bSmsOfBanner == FALSE && m_bSmsOfEtc == FALSE)
		{
			MessageBox("위에서 발송할 옵션을 체크하여 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}
	}
	return TRUE;
		 


}
BOOL COptionDlgSMS3::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	long nAllocateSMS = 0;
	if(m_bSMSOfRider) 
		nAllocateSMS = 1;
	else if(m_bSMSOfCompany)
		nAllocateSMS = 2;
	else if(m_bSMSOfIns)
		nAllocateSMS = 3;
	else if(m_bSMSOfInsRider)
		nAllocateSMS = 4;
	else if(m_bSaveMent && m_rdoCompanyPhone.GetCheck())
		nAllocateSMS = 5;
	else if(m_bSaveMent && m_rdoRiderPhone.GetCheck())
		nAllocateSMS = 6;

	//else if(m_bSaveMent)
	//	nAllocateSMS = 5;
	//else if(m_bSaveMent2)
	//		nAllocateSMS = 6;

	
	if(CheckData() == FALSE)
		return FALSE;

	CString sCallBackNumber = "", sHappyCallCancelMent = "";

	sCallBackNumber.Format("%d;%d;%d", m_cmbFirstPage.GetCurSel(), 
		m_cmbSecondPage.GetCurSel(), m_cmbThirdPage.GetCurSel());
	m_edtHappyCallMentCancel.GetWindowText(sHappyCallCancelMent);


	CMkCommand pCmd(m_pMkDb, "update_option_2011_sms_10");	//   
	pCmd.AddParameter(bAll);	
	pCmd.AddParameter(nCompany);		
	pCmd.AddParameter(nAllocateSMS);
	pCmd.AddParameter(m_rdoSMSSendCompanyName.GetCheck());		
	pCmd.AddParameter(m_AllocateSMSDelayCombo.GetCurSel());
	pCmd.AddParameter(m_bUseCancelSMS);	
	pCmd.AddParameter(m_strCancelSMSText);	
	pCmd.AddParameter(m_rdoRandomCompanyTel.GetCheck());		

	// 종료
	if(m_SmsOfRiderNameChk.GetCheck() == BST_CHECKED)
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 1);
	else if(m_SmsOfDt1Chk.GetCheck() == BST_CHECKED)
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 2);
	else if(m_SmsOfEtcChk.GetCheck() == BST_CHECKED)
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 3);
	else if(m_chkSmsOfBanner.GetCheck() == BST_CHECKED)
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 4);
	else 
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);

	pCmd.AddParameter(m_sCompleteBannerSms);
	pCmd.AddParameter(m_sCompleteSms);	
	pCmd.AddParameter(m_bSendCompleteSmsForRiderComplete);
	// 기사개별
	pCmd.AddParameter(m_bSendOnePage);
	pCmd.AddParameter(m_AllocateSmsTypeCmb.GetCurSel());	 
	pCmd.AddParameter(sCallBackNumber); 
	pCmd.AddParameter(m_strAllocateSmsFType); 
	pCmd.AddParameter(m_strAllocateCustomerSms); 
	pCmd.AddParameter(m_bUseHappyCallInquiry);
	pCmd.AddParameter(m_dtHappyCallInquiry);
	pCmd.AddParameter(m_strHappyCallMentInquiry);
	pCmd.AddParameter(m_bPickupSms);
	pCmd.AddParameter(m_strPickupSms);
	pCmd.AddParameter(m_bPickupSms2);
	pCmd.AddParameter(m_strPickupSms2);

	pCmd.AddParameter(m_chkUseHappyCallCompleted.GetCheck());
	pCmd.AddParameter(m_dtHappyCallCompleted);
	pCmd.AddParameter(m_chkUseHappyCallCancel.GetCheck());
	pCmd.AddParameter(m_dtHappyCallCancel);
	pCmd.AddParameter(sHappyCallCancelMent);	
	pCmd.AddParameter(m_chkUseHappyCallInquiryToday.GetCheck());
	pCmd.AddParameter(m_strHappyCallMentInquiryToday);

	CString strHappyCallDelayInquiryToday;
	m_cmbHappyCallDelayInquiryToday.GetWindowText(strHappyCallDelayInquiryToday);
	pCmd.AddParameter(atoi(strHappyCallDelayInquiryToday));

	pCmd.AddParameter(m_chkUseHappyCallCancelToday.GetCheck());
	pCmd.AddParameter(m_strHappyCallMentCancelToday);

	CString strHappyCallDelayCancelToday;
	m_cmbHappyCallDelayCancelToday.GetWindowText(strHappyCallDelayCancelToday);
	pCmd.AddParameter(atoi(strHappyCallDelayCancelToday));

	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtCompanyAppUrl));
	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtCompanyHomePage));
	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtCompanyLogoImage));

	pCmd.AddParameter(m_chkUsePreSms.GetCheck());
	pCmd.AddParameter(ComboToSqlDay(m_cmbPreSmsDay.GetCurSel()));
	pCmd.AddParameter(m_cmbPreSmsTerm.GetCurSel() + 1);
	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtPreSmsMent));
	pCmd.AddParameter(m_cmbPreSmsSendTime.GetCurSel() + 9);

	CString strTime;
	m_cmbCompleteSmsDelay.GetWindowText(strTime);
	pCmd.AddParameter(atoi(strTime));
	
	pCmd.AddParameter(m_ui.strID); 	
	return pCmd.Execute();
}

long COptionDlgSMS3::ComboToSqlDay(long nItem)
{
	if(nItem == 0) return 2; //월요일
	if(nItem == 1) return 3; //화요일
	if(nItem == 2) return 4; //수요일
	if(nItem == 3) return 5; //목요일
	if(nItem == 4) return 6; //금요일
	if(nItem == 5) return 7; //토요일
	if(nItem == 6) return 1; //일요일

	return 0;
}

void COptionDlgSMS3::SqlDayToCombo(CComboBox *pBox, long nDay)
{
	if(nDay == 2) pBox->SetCurSel(0); //월요일
	else if(nDay == 3) pBox->SetCurSel(1); //화요일
	else if(nDay == 4) pBox->SetCurSel(2); //수요일
	else if(nDay == 5) pBox->SetCurSel(3); //목요일
	else if(nDay == 6) pBox->SetCurSel(4); //금요일
	else if(nDay == 7) pBox->SetCurSel(5); //토요일
	else if(nDay == 1) pBox->SetCurSel(6); //일요일
	else
		pBox->SetCurSel(0);
}

void COptionDlgSMS3::OnBnClickedSmsOfRiderCheck()
{
	m_CompanyCheck.SetCheck(FALSE);
	m_InsCheck.SetCheck(FALSE);
	m_InsRiderCheck.SetCheck(FALSE);
	m_SaveMentChk.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedSmsOfCompanyCheck()
{
	m_RiderCheck.SetCheck(FALSE);
	m_InsCheck.SetCheck(FALSE);
	m_InsRiderCheck.SetCheck(FALSE);
	m_SaveMentChk.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedSmsOfInsCheck()
{
	m_CompanyCheck.SetCheck(FALSE);
	m_RiderCheck.SetCheck(FALSE);
	m_InsRiderCheck.SetCheck(FALSE);
	m_SaveMentChk.SetCheck(FALSE);
}
void COptionDlgSMS3::OnBnClickedSmsOfInsCheck2()
{	
	m_CompanyCheck.SetCheck(FALSE);
	m_RiderCheck.SetCheck(FALSE);
	m_InsCheck.SetCheck(FALSE);
	m_SaveMentChk.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedSmsOfSaveMentCheck()
{
	m_CompanyCheck.SetCheck(FALSE);
	m_RiderCheck.SetCheck(FALSE);
	m_InsCheck.SetCheck(FALSE);
	m_InsRiderCheck.SetCheck(FALSE);
	
	if(m_rdoCompanyPhone.GetCheck() == FALSE &&
		m_rdoRiderPhone.GetCheck() == FALSE)
		m_rdoCompanyPhone.SetCheck(TRUE);
}


void COptionDlgSMS3::OnBnClickedCancelSmsCheck()
{
	if(m_CancelSMSCheck.GetCheck())
		m_CancelSMSEdit.EnableWindow(TRUE);
	else
		m_CancelSMSEdit.EnableWindow(FALSE);
}
void COptionDlgSMS3::OnEnChangeCancelSmsEdit()
{
	CString strMent, strLength;
	m_CancelSMSEdit.GetWindowText(strMent);
	strLength.Format("%d/80", strMent.GetLength());
	m_LengthStatic.SetWindowText(strLength);
}

void COptionDlgSMS3::OnBnClickedLookAheadButton()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtAllocateCustomerSms.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK)
		m_edtAllocateCustomerSms.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnBnClickedSmsOfRiderNameCheck()
{
	m_SmsOfDt1Chk.SetCheck(FALSE);
	m_SmsOfEtcChk.SetCheck(FALSE);
	m_chkSmsOfBanner.SetCheck(FALSE);
	InitControl();
}

void COptionDlgSMS3::OnBnClickedSmsOfDt1Check()
{
	m_SmsOfRiderNameChk.SetCheck(FALSE);
	m_SmsOfEtcChk.SetCheck(FALSE);
	m_chkSmsOfBanner.SetCheck(FALSE);
	InitControl();
}

void COptionDlgSMS3::OnBnClickedSmsOfEtcCheck()
{
	m_SmsOfDt1Chk.SetCheck(FALSE);
	m_SmsOfRiderNameChk.SetCheck(FALSE);
	m_chkSmsOfBanner.SetCheck(FALSE);
	InitControl();
}


void COptionDlgSMS3::OnEnChangeCompleteSmsEdit()
{
	CString strMent, strLength;
	m_CompleteSmsEdt.GetWindowText(strMent);
	strLength.Format("%d/80", strMent.GetLength());
	m_LengthStatic.SetWindowText(strLength);
}

void COptionDlgSMS3::OnBnClickedSettingFTypeBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtAllocateSmsFType.GetWindowText(dlg.m_strInput);
	
	if(dlg.DoModal() == IDOK)
		m_edtAllocateSmsFType.SetWindowText(dlg.m_strInput);		

}

void COptionDlgSMS3::OnBnClickedSmsOfBannerCheck()
{
	m_SmsOfDt1Chk.SetCheck(FALSE);
	m_SmsOfRiderNameChk.SetCheck(FALSE);
	m_SmsOfEtcChk.SetCheck(FALSE);
	InitControl();
}



void COptionDlgSMS3::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL COptionDlgSMS3::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);
	g_bana_log->Print("%ld, nFlags  zDelta = %d", nFlags, int(zDelta));
	return TRUE;
}


void COptionDlgSMS3::OnSize(UINT nType, int cx, int cy)
{
	return; 
	CMyFormView::OnSize(nType, cx, cy); 

}
void COptionDlgSMS3::OnBnClickedSettingHappyMentBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_CompleteSmsEdt.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK)
		m_CompleteSmsEdt.SetWindowText(dlg.m_strInput);
}


void COptionDlgSMS3::OnBnClickedPickupMsgBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtPickupSms.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtPickupSms.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnBnClickedPickupMsgBtn2()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtPickupSms2.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtPickupSms2.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnBnClickedCancelHappyMsgBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtHappyCallMentCancel.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtHappyCallMentCancel.SetWindowText(dlg.m_strInput);
}


void COptionDlgSMS3::OnBnClickedInqueryHappyMsgBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtHappyCallMentInquiry.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtHappyCallMentInquiry.SetWindowText(dlg.m_strInput);
}


void COptionDlgSMS3::OnBnClickedUseHappyCallFinishCheck()
{
	m_dtpHappyCallCompleted.EnableWindow(m_chkUseHappyCallCompleted.GetCheck());	
}

void COptionDlgSMS3::OnBnClickedUseHappyCallCancelCheck()
{
	m_dtpHappyCallCancel.EnableWindow(m_chkUseHappyCallCancel.GetCheck());	

	if(m_chkUseHappyCallCancel.GetCheck())
		m_chkUseHappyCallCancelToday.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedUseHappyCallInquiryCheck()
{
	m_dtpHappyCallInquery.EnableWindow(m_chkUseHappyCallInquiry.GetCheck());	

	if(m_chkUseHappyCallInquiry.GetCheck())
		m_chkUseHappyCallInquiryToday.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedUseHappyCallInquiryTodayCheck()
{
	if(m_chkUseHappyCallInquiryToday.GetCheck())
		m_chkUseHappyCallInquiry.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedInqueryHappyMsgTodayBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtHappyCallMentInquiryToday.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtHappyCallMentInquiryToday.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnBnClickedInqueryHappyMsgTodayBtn2()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtHappyCallMentCancelToday.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtHappyCallMentCancelToday.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnBnClickedUseHappyCallCancelTodayCheck()
{
	if(m_chkUseHappyCallCancelToday.GetCheck())
		m_chkUseHappyCallCancel.SetCheck(FALSE);
}

void COptionDlgSMS3::OnBnClickedShowUrlBtn()
{
	CString strItem = LF->GetStringFromEdit(&m_edtCompanyHomePage);

	if(!strItem.IsEmpty())
		ShellExecute(NULL, "open", "iexplore.exe", strItem, "", SW_SHOW);
}

void COptionDlgSMS3::OnBnClickedShowUrlBtn2()
{
	CString strItem = LF->GetStringFromEdit(&m_edtCompanyLogoImage);

	if(!strItem.IsEmpty())
		ShellExecute(NULL, "open", "iexplore.exe", strItem, "", SW_SHOW);
}

void COptionDlgSMS3::OnBnClickedPreSmsBtn()
{
	CAllocateSMSFSettingDlg dlg;
	m_edtPreSmsMent.GetWindowText(dlg.m_strInput);

	if(dlg.DoModal() == IDOK) 
		m_edtPreSmsMent.SetWindowText(dlg.m_strInput);
}

void COptionDlgSMS3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}
