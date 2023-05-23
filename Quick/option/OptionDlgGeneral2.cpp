// OptionDlgGeneral2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgGeneral2.h"
#include "MainOptionDlg2011.h"
#include "MainFrm.h"
#include "TankTypeQDlg.h"
#include "MyCallDepositDlg.h"
#include "OptionTipDlg.h"
//#include "SetCountMileageDlg.h"
// COptionDlgGeneral2

IMPLEMENT_DYNCREATE(COptionDlgGeneral2, CMyFormView)

COptionDlgGeneral2::COptionDlgGeneral2()
: CMyFormView(COptionDlgGeneral2::IDD)

, m_bSingleAllocate(FALSE)
, m_bGiveChargeRider(FALSE)

, m_bUseRTIDOnSpeedAllocate(FALSE)
, m_bCancelToInquiry(FALSE)
, m_bEtcAuto(FALSE)
, m_bInsertPhoneToInterCallID(FALSE)
, m_strInterCallPassword(_T(""))
, m_strNewCustomerName(_T(""))
{
	m_ci.m_bCheckMidWord = TRUE;	
	m_bMemoToEtc = FALSE;
	m_bRiderMemoToEtc = FALSE;
	m_strRcpTimeColor1 = "";
	m_strRcpTimeColor2 = "";
	m_strRcpTimeColor3 = "";
	m_bWaitSecondCall = FALSE;

	m_bNoUseCNS = FALSE;		
	m_bSingleAllocate = FALSE;
	m_bUsageHistory = FALSE;
	m_bGiveChargeRider = FALSE;
	m_bDisableCreditBtn = FALSE;	
	m_bUseOrderChangeMent = FALSE;	
	m_bUseRTIDOnSpeedAllocate = FALSE;	
	m_bDistaceCharge = 0;
	m_nDistanceCharge = 0;

	m_bAutoShareOrder = FALSE;
	m_strAutoShareTime = "";
	m_nTankType = 0;
	m_bShowTank = FALSE;
	m_bCancelReason = FALSE;
	m_bInitDongInfo = FALSE;
	m_bCreditListPopup = FALSE;
	m_bNotClientPhone1 = FALSE;
	m_bNotCustomerAddCID = FALSE;
}

COptionDlgGeneral2::~COptionDlgGeneral2()
{
}

void COptionDlgGeneral2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);	

	DDX_Control(pDX, IDC_WAIT_SECOND_CALL_CHECK, m_WaitSecondCallCheck);
	DDX_Check(pDX, IDC_WAIT_SECOND_CALL_CHECK, m_bWaitSecondCall);

	DDX_Control(pDX, IDC_RCP_TIME_COLOR_EDIT1, m_RcpTimeColorEdit1);
	DDX_Control(pDX, IDC_RCP_TIME_COLOR_EDIT2, m_RcpTimeColorEdit2);
	DDX_Control(pDX, IDC_RCP_TIME_COLOR_EDIT3, m_RcpTimeColorEdit3);
	DDX_Text(pDX, IDC_RCP_TIME_COLOR_EDIT1, m_strRcpTimeColor1);
	DDX_Text(pDX, IDC_RCP_TIME_COLOR_EDIT2, m_strRcpTimeColor2);
	DDX_Text(pDX, IDC_RCP_TIME_COLOR_EDIT3, m_strRcpTimeColor3);

	DDX_Control(pDX, IDC_NO_USE_CNS_CHECK, m_NoUseCNSCheck);
	DDX_Check(pDX, IDC_NO_USE_CNS_CHECK, m_bNoUseCNS);
	DDX_Control(pDX, IDC_USERID_SEQUENCE_CHECK, m_UserIDSequenceCheck);
	DDX_Control(pDX, IDC_MEMO_TO_ETC_CHECK, m_chkMemoToEtc);
	DDX_Check(pDX, IDC_MEMO_TO_ETC_CHECK, m_bMemoToEtc);
	DDX_Control(pDX, IDC_SINGLE_ALLOCATE_CHECK, m_chkSingleAllocate);
	DDX_Check(pDX, IDC_SINGLE_ALLOCATE_CHECK, m_bSingleAllocate);
	DDX_Control(pDX, IDC_USAGE_HISTORY_CHECK, m_chkUsageHistory);
	DDX_Check(pDX, IDC_USAGE_HISTORY_CHECK, m_bUsageHistory);
	DDX_Control(pDX, IDC_GIVE_CHARGE_RIDER, m_GiveChargeRider);
	DDX_Check(pDX, IDC_GIVE_CHARGE_RIDER, m_bGiveChargeRider);
	DDX_Control(pDX, IDC_DISABLE_CREDIT_BTN_CHECK, m_chkDisableCreditBtn);
	DDX_Check(pDX, IDC_DISABLE_CREDIT_BTN_CHECK, m_bDisableCreditBtn);
	DDX_Control(pDX, IDC_USER_DONGPOS_CHECK, m_chkUserDongPos);
	DDX_Control(pDX, IDC_USE_ORDER_CHANGE_MENT_CHECK, m_chkUseOrderChangeMent);
	DDX_Check(pDX, IDC_USE_ORDER_CHANGE_MENT_CHECK, m_bUseOrderChangeMent);
	DDX_Control(pDX, IDC_USE_RTID_ON_SPEED_ALLOCATE, m_chkUseRTIDOnSpeedAllocate);
	DDX_Check(pDX, IDC_USE_RTID_ON_SPEED_ALLOCATE, m_bUseRTIDOnSpeedAllocate);
	DDX_Control(pDX, IDC_USE_BONGGO_FROM_LABO_CHECK, m_chkUsePayBonggoFromLabo);	
	DDX_Control(pDX, IDC_CONSIGNPOPUP_COMBO, m_cmbConsignPopup);
	DDX_Control(pDX, IDC_TAX_USE_EMAIL_EDIT , m_edtTaxUseEmail);
	DDX_Control(pDX, IDC_USE_CARD_TAX_CHECK, m_chkUseCardTax);
	DDX_Check(pDX, IDC_USE_CARD_TAX_CHECK, m_bUseCardTax);

	DDX_Control(pDX, IDC_NOT_USE_ETC_FOR_CANCEL_CHECK, m_chkNotUseEtcForCancel);
	DDX_Check(pDX, IDC_NOT_USE_ETC_FOR_CANCEL_CHECK, m_bNotUseEtcForCancel);

	DDX_Control(pDX, IDC_CAR_TYPE_BTN1, m_btnCarType1);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN2, m_btnCarType2);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN3, m_btnCarType3);
	DDX_Control(pDX, IDC_PAY_TYPE_BTN1, m_btnPayType1);
	DDX_Control(pDX, IDC_PAY_TYPE_BTN2, m_btnPayType2);
	DDX_Control(pDX, IDC_PAY_TYPE_BTN3, m_btnPayType3);
	DDX_Control(pDX, IDC_PAY_TYPE_BTN4, m_btnPayType4);
	DDX_Control(pDX, IDC_TANK_ALL_VIEW_BUTTON, m_btnTankAllView);	
	DDX_Control(pDX, IDC_TAX_STATIC, m_stcTank);

	DDX_Control(pDX, IDC_AUTO_SHARE_ORDER_CHECK, m_chkAutoShareOrder);
	DDX_Check(pDX, IDC_AUTO_SHARE_ORDER_CHECK, m_bAutoShareOrder);
	DDX_Control(pDX, IDC_AUTO_SHARE_TIME_EDIT, m_edtAutoShareTime);
	DDX_Text(pDX, IDC_AUTO_SHARE_TIME_EDIT, m_strAutoShareTime);

	DDX_Control(pDX, IDC_RIDER_MEMO_TO_ETC_CHECK, m_chkRiderMemoToEtc);
	DDX_Check(pDX, IDC_RIDER_MEMO_TO_ETC_CHECK, m_bRiderMemoToEtc); 

	DDX_Control(pDX, IDC_CALLER_ID_TO_PHONE1_CHECK, m_chkCallerIDToPhone1);
	DDX_Check(pDX, IDC_CALLER_ID_TO_PHONE1_CHECK, m_bCallerIDToPhone1); 

	DDX_Control(pDX, IDC_CLEAR_DEST_FOR_AFTER_COPY_CHECK, m_chkClearDestForAfterCopy);
	DDX_Check(pDX, IDC_CLEAR_DEST_FOR_AFTER_COPY_CHECK, m_bClearDestForAfterCopy); 

	DDX_Control(pDX, IDC_HISTORY_DETAIL_ALL_VIEW, m_chkHistoryDetailAllView);

	DDX_Control(pDX, IDC_FOCUS_TO_WAIT_BTN_CHECK, m_chkFocusToWaitBtn);
	DDX_Check(pDX, IDC_FOCUS_TO_WAIT_BTN_CHECK, m_bFocusToWaitBtn); 

	DDX_Control(pDX, IDC_REVISIT_EDIT, m_edtRevisitCustomerSendDay);
	DDX_Text(pDX, IDC_REVISIT_EDIT, m_strRevisitCustomerSendDay);
	DDX_Control(pDX, IDC_REVISIT_CUSTOMER_CHECK, m_chkRevisitCustomer);

	DDX_Control(pDX, IDC_USE_ORDER_BUNDLE_CHECK, m_chkUseOrderBundle);
	DDX_Check(pDX, IDC_USE_ORDER_BUNDLE_CHECK, m_bUseOrderBundle);
	DDX_Control(pDX, IDC_CANCEL_TO_INQUIRY, m_chkCancelToInquiry);

	DDX_Check(pDX, IDC_CANCEL_TO_INQUIRY, m_bCancelToInquiry);
	DDX_Control(pDX, IDC_CANCEL_TO_INQUIRY, m_chkCancelToInquiry);
	DDX_Check(pDX, IDC_CANCEL_REASON_CHECK, m_bCancelReason);
	DDX_Control(pDX, IDC_CANCEL_REASON_CHECK, m_chkCancelReason);
	DDX_Check(pDX, IDC_INIT_DONGINFO_CHECK, m_bInitDongInfo);
	DDX_Control(pDX, IDC_INIT_DONGINFO_CHECK, m_chkInitDongInfo);
	DDX_Check(pDX, IDC_CREDIT_POPUP_CHECK, m_bCreditListPopup);
	DDX_Control(pDX, IDC_CREDIT_POPUP_CHECK, m_chkCreditListPopup);
	DDX_Check(pDX, IDC_NO_DEST_POI_CHECK, m_bNoDestPoi);
	DDX_Control(pDX, IDC_NO_DEST_POI_CHECK, m_chkNoDestPoi);
	DDX_Check(pDX, IDC_CUSTOMER_AUTO_INSERT_CHECK, m_bCustomerAutoInsert);
	DDX_Control(pDX, IDC_CUSTOMER_AUTO_INSERT_CHECK, m_chkCustomerAutoInsert);

	DDX_Control(pDX, IDC_FIRST_RECEIPT_WAIT_CHANGE_TIME_CHECK , m_chkFirstWaitTimePast);
	DDX_Check(pDX, IDC_FIRST_RECEIPT_WAIT_CHANGE_TIME_CHECK , m_bFirstWaitTimePast);

	DDX_Check(pDX, IDC_ETC_AUTO_CHECK, m_bEtcAuto);
	DDX_Control(pDX, IDC_ETC_AUTO_CHECK, m_chkEtcAuto);
	DDX_CBString(pDX, IDC_ETC_AUTO_EDIT, m_strEtcAuto);
	DDX_Control(pDX, IDC_ETC_AUTO_EDIT, m_edtEtcAuto); 
	DDX_Control(pDX, IDC_CORPORATION_TEL_HIDDEN_CHECK, m_chkCompanyTelHidden);
	DDX_Control(pDX, IDC_MYCALL_RIDER_DEPOSIT_CHECK, m_chkMyCallRiderDeposit);
	DDX_Control(pDX, IDC_MY_CALL_BTN, m_btnMyCallRiderDeposit);

	DDX_Control(pDX, IDC_PAY_TYPE_BTN5, m_btnPayType5);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN4, m_btnCarType4);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN5, m_btnCarType5);
	DDX_Check(pDX, IDC_NO_CLINT_PHONE1_CHECK, m_bNotClientPhone1);
	DDX_Control(pDX, IDC_NO_CLINT_PHONE1_CHECK, m_chkNotClientPhone1);
	DDX_Check(pDX, IDC_NO_CUSTOMER_CID_CHECK, m_bNotCustomerAddCID);
	DDX_Control(pDX, IDC_NO_CUSTOMER_CID_CHECK, m_chkNotCustomerAddCID);
	DDX_Control(pDX, IDC_INSERT_PHONE_TO_INTER_CALL_ID_CHECK, m_chkInsertPhoneToInterCallID);
	DDX_Check(pDX, IDC_INSERT_PHONE_TO_INTER_CALL_ID_CHECK, m_bInsertPhoneToInterCallID);
	DDX_Control(pDX, IDC_INTER_CALL_PASS_WORD_EDIT, m_edtInterCallPassword);
	DDX_Text(pDX, IDC_INTER_CALL_PASS_WORD_EDIT, m_strInterCallPassword);

	DDX_Check(pDX, IDC_NOT_CHANGE_DT1_FOR_DELAY_CHECK, m_bNotChangedt1ForDelay);
	DDX_Control(pDX, IDC_NOT_CHANGE_DT1_FOR_DELAY_CHECK, m_chkNotChangedt1ForDelay);
	DDX_Control(pDX, IDC_NEW_CUSTOMER_NAME_EDIT, m_edtNewCustomerName);
	DDX_Text(pDX, IDC_NEW_CUSTOMER_NAME_EDIT, m_strNewCustomerName);
	DDX_Control(pDX, IDC_POPUP_FOCUS_CHECK, m_chkPopupFocus);
	DDX_Check(pDX, IDC_POPUP_FOCUS_CHECK, m_bPopupFocus);
	DDX_Control(pDX, IDC_COLOR_CHANGE_CHECK, m_chkColorChange);
	DDX_Check(pDX, IDC_COLOR_CHANGE_CHECK, m_bColorChange);
	DDX_Control(pDX, IDC_ONLY_LOAD_INS_RIDER_CHECK, m_chkOnlyLoadInsRider);
	DDX_Check(pDX, IDC_ONLY_LOAD_INS_RIDER_CHECK, m_bOnlyLoadInsRider);

	DDX_Control(pDX, IDC_VRACCOUNT_NO_RIDER_CHECK, m_chkVRAccountNoRider);
	DDX_Check(pDX, IDC_VRACCOUNT_NO_RIDER_CHECK, m_bVRAccountNoRider);

	DDX_Control(pDX, IDC_INIT_DT1_STATE_TO_RCP_CHECK, m_chkInitDt1StateToRcp);

	DDX_Control(pDX, IDC_AUTO_DELAY_EDIT, m_edtAutoDelay);
	DDX_Text(pDX, IDC_AUTO_DELAY_EDIT, m_strAutoDelay);	

	DDX_Control(pDX, IDC_AUTO_DELAY_CHECK, m_chkAutoDelay);
	//DDX_Check(pDX, IDC_AUTO_DELAY_CHECK, m_bAutoDelay);
	DDX_Control(pDX, IDC_CNS_SEARCH_TYPE1_COMBO, m_cmbCnsSearchType1);
	DDX_Control(pDX, IDC_CNS_SEARCH_TYPE2_COMBO, m_cmbCnsSearchType2);
	DDX_Control(pDX, IDC_CNS_SEARCH_PAID_COMBO, m_cmbCnsSearchPaid);
	DDX_Control(pDX, IDC_KAKAO_KEY_EDIT, m_edtKakaoKey);
	DDX_Text(pDX, IDC_KAKAO_KEY_EDIT, m_strKakaoKey);

	DDX_Control(pDX, IDC_KEEP_CHARGE_COMPANY_CHECK, m_chkKeepChargeCompany);
}

BEGIN_MESSAGE_MAP(COptionDlgGeneral2, CMyFormView)
	ON_WM_MOUSEACTIVATE()
	ON_MESSAGE(WM_REFRESH, OnRefresh )
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN1, &COptionDlgGeneral2::OnBnClickedCarTypeBtn1)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN2, &COptionDlgGeneral2::OnBnClickedCarTypeBtn2)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN3, &COptionDlgGeneral2::OnBnClickedCarTypeBtn3)
	ON_BN_CLICKED(IDC_PAY_TYPE_BTN1, &COptionDlgGeneral2::OnBnClickedPayTypeBtn1)
	ON_BN_CLICKED(IDC_PAY_TYPE_BTN2, &COptionDlgGeneral2::OnBnClickedPayTypeBtn2)
	ON_BN_CLICKED(IDC_PAY_TYPE_BTN3, &COptionDlgGeneral2::OnBnClickedPayTypeBtn3)

	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_AUTO, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_BIGBIKE, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_SEDAN, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_DAMA, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_LABO, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_1TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_1_4TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_2_5TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_3_5TON, OnMenuContextCarType) 
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_5TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_5_5TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_8TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_11TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_14TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_15TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_18TON, OnMenuContextCarType)
	ON_COMMAND_RANGE_SINGLE(ID_CAR_TYPE_25TON, OnMenuContextCarType)

	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE0, OnMenuContextPayType)
	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE1, OnMenuContextPayType)
	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE2, OnMenuContextPayType)
	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE3, OnMenuContextPayType)
	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE4, OnMenuContextPayType)
	ON_COMMAND_RANGE_SINGLE(ID_PAY_TYPE7, OnMenuContextPayType)
	ON_BN_CLICKED(IDC_PAY_TYPE_BTN4, &COptionDlgGeneral2::OnBnClickedPayTypeBtn4)
	ON_BN_CLICKED(IDC_AUTO_SHARE_ORDER_CHECK, &COptionDlgGeneral2::OnBnClickedAutoShareOrderCheck)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_REVISIT_CUSTOMER_CHECK, &COptionDlgGeneral2::OnBnClickedRevisitCustomerCheck)
	ON_BN_CLICKED(IDC_TANK_ALL_VIEW_BUTTON, &COptionDlgGeneral2::OnBnClickedTankAllViewButton)
	ON_BN_CLICKED(IDC_MY_CALL_BTN, &COptionDlgGeneral2::OnBnClickedMyCallBtn)
	ON_BN_CLICKED(IDC_MYCALL_RIDER_DEPOSIT_CHECK, &COptionDlgGeneral2::OnBnClickedMycallRiderDepositCheck)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN4, &COptionDlgGeneral2::OnBnClickedCarTypeBtn4)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN5, &COptionDlgGeneral2::OnBnClickedCarTypeBtn5)
	ON_BN_CLICKED(IDC_PAY_TYPE_BTN5, &COptionDlgGeneral2::OnBnClickedPayTypeBtn5)
	ON_BN_CLICKED(IDC_CALLER_ID_TO_PHONE1_CHECK, &COptionDlgGeneral2::OnBnClickedCallerIDToPhone1)
	ON_BN_CLICKED(IDC_TIP_BUTTON, &COptionDlgGeneral2::OnBnClickedTipButton)
	ON_BN_CLICKED(IDC_FIRST_RECEIPT_WAIT_CHANGE_TIME_CHECK, &COptionDlgGeneral2::OnBnClickedFirstReceiptWaitChangeTimeCheck)
	ON_BN_CLICKED(IDC_HISTORY_DETAIL_ALL_VIEW, &COptionDlgGeneral2::OnBnClickedHistoryDetailAllView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_KAKAO_HELP_BTN, &COptionDlgGeneral2::OnBnClickedKakaoHelpBtn)
END_MESSAGE_MAP()


// COptionDlgGeneral2 진단입니다.

#ifdef _DEBUG
void COptionDlgGeneral2::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgGeneral2::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgGeneral2 메시지 처리기입니다.

void COptionDlgGeneral2::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate(); 

	SetOptiobView(TRUE);
 
	if(!LF->POWER_CHECK(1301, "일반"))
		EnableWindow(FALSE);

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 
	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;  
	sizeTotal.cy = 950;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_cmbConsignPopup.SetCurSel(0);

	if(m_ui.bDeveloper)
	{
		m_chkMyCallRiderDeposit.ShowWindow(SW_SHOW);
		m_btnMyCallRiderDeposit.ShowWindow(SW_SHOW);
	}
}

int COptionDlgGeneral2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	
	return TRUE;
	//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);

}


BOOL COptionDlgGeneral2::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);
	char buffer[10]; 
	
	// 일반 
	CString strTaxUseEmail = "";
	m_edtTaxUseEmail.GetWindowText(strTaxUseEmail); 
	long nRcpTimeColor = 0;
	nRcpTimeColor = (atol(m_strRcpTimeColor1) << 16) + (atol(m_strRcpTimeColor2) << 8) +
		atol(m_strRcpTimeColor3);
	CMkCommand pCmd(m_pMkDb, "update_option_2015_general_9");	// 
	pCmd.AddParameter(bAll);	
	pCmd.AddParameter(nCompany);	
	pCmd.AddParameter(nRcpTimeColor);	
	pCmd.AddParameter(m_cmbConsignPopup.GetCurSel());
	pCmd.AddParameter(m_bNoUseCNS);
	pCmd.AddParameter(m_UserIDSequenceCheck.GetCheck());	
	pCmd.AddParameter(m_chkMemoToEtc.GetCheck());
	pCmd.AddParameter(m_chkRiderMemoToEtc.GetCheck());
	pCmd.AddParameter(m_bSingleAllocate); // 개별배차시 확인창
	pCmd.AddParameter(m_bUsageHistory); // 사용내역 날개창을 항상뛰움
	pCmd.AddParameter(m_bGiveChargeRider); 	
	pCmd.AddParameter(m_bDisableCreditBtn);  //현금 고객 접수시 신용송금 
	pCmd.AddParameter(m_bWaitSecondCall);  
	pCmd.AddParameter(m_chkUserDongPos.GetCheck());  // 사용자저의 동설정
	pCmd.AddParameter(m_chkUseOrderChangeMent.GetCheck()); 
	pCmd.AddParameter(m_bUseRTIDOnSpeedAllocate); 	
	pCmd.AddParameter(m_chkUsePayBonggoFromLabo.GetCheck()); 
	pCmd.AddParameter(m_ui.strID); 	
	pCmd.AddParameter(m_chkUseCardTax.GetCheck());
	pCmd.AddParameter(m_chkNotUseEtcForCancel.GetCheck());

	CString strPayType = CString(itoa(m_nPayType1, buffer, 10)) + ";" + CString(itoa(m_nPayType2, buffer, 10)) + ";" + CString(itoa(m_nPayType3, buffer, 10)) + ";" + CString(itoa(m_nPayType4, buffer, 10)) + ";" + CString(itoa(m_nPayType5, buffer, 10)) + ";";
	CString strCarType = CString(itoa(m_nCarType1, buffer, 10)) + ";" + CString(itoa(m_nCarType2, buffer, 10)) + ";" + CString(itoa(m_nCarType3, buffer, 10)) + ";" + CString(itoa(m_nCarType4, buffer, 10)) + ";" + CString(itoa(m_nCarType5, buffer, 10)) + ";";

	pCmd.AddParameter(strPayType);
	pCmd.AddParameter(strCarType);
	pCmd.AddParameter(m_chkAutoShareOrder.GetCheck());
	pCmd.AddParameter(atoi(m_strAutoShareTime));
	pCmd.AddParameter(m_chkCallerIDToPhone1.GetCheck());
	pCmd.AddParameter(m_chkClearDestForAfterCopy.GetCheck());
	pCmd.AddParameter(m_chkRevisitCustomer.GetCheck() ? atoi(m_strRevisitCustomerSendDay) : ZERO);
	pCmd.AddParameter(m_chkFocusToWaitBtn.GetCheck());
	pCmd.AddParameter(m_chkUseOrderBundle.GetCheck());
	pCmd.AddParameter(m_chkCancelToInquiry.GetCheck());
	pCmd.AddParameter(m_chkEtcAuto.GetCheck());
	pCmd.AddParameter(m_strEtcAuto);
	pCmd.AddParameter(m_chkCompanyTelHidden.GetCheck());
	pCmd.AddParameter(m_chkMyCallRiderDeposit.GetCheck());
	pCmd.AddParameter(strTaxUseEmail);
	pCmd.AddParameter(m_chkCancelReason.GetCheck());
	pCmd.AddParameter(m_chkInitDongInfo.GetCheck());
	pCmd.AddParameter(m_chkCreditListPopup.GetCheck());
	pCmd.AddParameter(m_chkNoDestPoi.GetCheck());
	pCmd.AddParameter(m_chkNotClientPhone1.GetCheck());
	pCmd.AddParameter(m_chkNotCustomerAddCID.GetCheck());
	pCmd.AddParameter(m_chkInsertPhoneToInterCallID.GetCheck());
	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtInterCallPassword));
	pCmd.AddParameter(m_chkCustomerAutoInsert.GetCheck());	
	pCmd.AddParameter(m_chkFirstWaitTimePast.GetCheck());
	pCmd.AddParameter(m_chkNotChangedt1ForDelay.GetCheck());
	pCmd.AddParameter(LF->GetStringFromEdit(&m_edtNewCustomerName));
	pCmd.AddParameter(m_chkHistoryDetailAllView.GetCheck());
	pCmd.AddParameter(m_chkPopupFocus.GetCheck());
	pCmd.AddParameter(m_chkColorChange.GetCheck());
	pCmd.AddParameter(m_chkOnlyLoadInsRider.GetCheck());
	pCmd.AddParameter(m_chkVRAccountNoRider.GetCheck());

	if(m_chkAutoDelay.GetCheck())
		pCmd.AddParameter(atoi(m_strAutoDelay));
	else
		pCmd.AddParameter(0);

	pCmd.AddParameter(m_cmbCnsSearchType1.GetCurSel() + 1);
	pCmd.AddParameter(m_cmbCnsSearchType2.GetCurSel() + 1);
	pCmd.AddParameter(m_cmbCnsSearchPaid.GetCurSel() + 1);
	pCmd.AddParameter(m_strKakaoKey);
	pCmd.AddParameter(m_chkKeepChargeCompany.GetCheck());
	pCmd.AddParameter(m_chkInitDt1StateToRcp.GetCheck());

	return pCmd.Execute();
}

long COptionDlgGeneral2::OnRefresh(WPARAM wParam,LPARAM lParam)
{
	BOOL bDistanceChargeCheck = FALSE;

	int  nViaAmount = 0;


	//m_nDistanceCharge = -1;

	CMkRecordset* pRs = (CMkRecordset*)lParam;

	return 0L;
}

void COptionDlgGeneral2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	//if(nSBCode == SB_ENDSCROLL)
	//	Invalidate(TRUE);
}

BOOL COptionDlgGeneral2::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);
	//if(nFlags == SB_ENDSCROLL)
	//Invalidate(TRUE);

	return TRUE;
}

void COptionDlgGeneral2::OpenPayContextMenu(long nSel)
{
	m_nLastSelPayBtn = nSel;

	CPoint pt; 
	GetCursorPos(&pt);

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(1);
	pRMenu->SetMenuDrawMode(TRUE);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void COptionDlgGeneral2::OpenCarContextMenu(long nSel)
{
	m_nLastSelCarBtn = nSel;

	CPoint pt; 
	GetCursorPos(&pt);

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(0);
	pRMenu->SetMenuDrawMode(TRUE);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void COptionDlgGeneral2::OnBnClickedCarTypeBtn1()
{
	OpenCarContextMenu(ZERO);
}

void COptionDlgGeneral2::OnBnClickedCarTypeBtn2()
{
	OpenCarContextMenu(ONE);
}

void COptionDlgGeneral2::OnBnClickedCarTypeBtn3()
{
	OpenCarContextMenu(2);
}

void COptionDlgGeneral2::OnBnClickedPayTypeBtn1()
{
	OpenPayContextMenu(ZERO);
}

void COptionDlgGeneral2::OnBnClickedPayTypeBtn2()
{
	OpenPayContextMenu(ONE);
}

void COptionDlgGeneral2::OnBnClickedPayTypeBtn3()
{
	OpenPayContextMenu(2);
}

void COptionDlgGeneral2::OnMenuContextCarType(UINT nFlag)
{

	switch (nFlag)
	{
		case ID_CAR_TYPE_AUTO:	SaveCarType(CAR_AUTO);	break;
		case ID_CAR_TYPE_BIGBIKE:	SaveCarType(CAR_BIGBIKE);	break;
		case ID_CAR_TYPE_SEDAN:	SaveCarType(CAR_SEDAN);	break;
		case ID_CAR_TYPE_DAMA:	SaveCarType(CAR_DAMA);	break;
		case ID_CAR_TYPE_LABO:	SaveCarType(CAR_LABO);	break;
		case ID_CAR_TYPE_1TON:	SaveCarType(CAR_TRUCK);	break;
		case ID_CAR_TYPE_1_4TON:	SaveCarType(CAR_1_4_TON);	break;
		case ID_CAR_TYPE_2_5TON:	SaveCarType(CAR_2_5_TON);	break;
		case ID_CAR_TYPE_3_5TON:	SaveCarType(CAR_3_5_TON);	break;
		case ID_CAR_TYPE_5TON:	SaveCarType(CAR_5_TON);	break;
		case ID_CAR_TYPE_5_5TON:	SaveCarType(CAR_5_TON_PLUS);	break;
		case ID_CAR_TYPE_8TON:	SaveCarType(CAR_8_TON);	break;
		case ID_CAR_TYPE_11TON:	SaveCarType(CAR_11_TON);	break;
		case ID_CAR_TYPE_14TON:	SaveCarType(CAR_14_TON);	break;
		case ID_CAR_TYPE_15TON:	SaveCarType(CAR_15_TON);	break;
		case ID_CAR_TYPE_18TON:	SaveCarType(CAR_18_TON);	break;
		case ID_CAR_TYPE_25TON:	SaveCarType(CAR_25_TON);	break;
		
	}
}

void COptionDlgGeneral2::OnMenuContextPayType(UINT nFlag)
{
	switch (nFlag)
	{
		case ID_PAY_TYPE0:
			SavePayType(PAY_PRE);
		break;
		case ID_PAY_TYPE1:
			SavePayType(PAY_AFTER);
		break;
		case ID_PAY_TYPE2:
			SavePayType(PAY_CREDIT);
		break;
		case ID_PAY_TYPE3:
			SavePayType(PAY_ONLINE);
		break;
		case ID_PAY_TYPE4:
			SavePayType(PAY_DIRECT);
		break;
		case ID_PAY_TYPE7:
			SavePayType(PAY_CARD);
		break;
	}
}

void COptionDlgGeneral2::SavePayType(long nPayType)
{
	if(m_nPayType1 == nPayType ||
		m_nPayType2 == nPayType ||
		m_nPayType3 == nPayType ||
		m_nPayType4 == nPayType ||
		m_nPayType5 == nPayType)
	{
		MessageBox("동일한 항목이 저장되어 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CButton *pButton = NULL;
	long *nSel = NULL;

	if(m_nLastSelPayBtn == ZERO)
	{
		nSel = &m_nPayType1;
		pButton = &m_btnPayType1;
	}
	else if(m_nLastSelPayBtn == ONE)
	{
		nSel = &m_nPayType2;
		pButton = &m_btnPayType2;
	}
	else if(m_nLastSelPayBtn == 2)
	{
		nSel = &m_nPayType3;
		pButton = &m_btnPayType3;
	}
	else if(m_nLastSelPayBtn == 3)
	{
		nSel = &m_nPayType4;
		pButton = &m_btnPayType4;
	}
	else if(m_nLastSelPayBtn == 4)
	{
		nSel = &m_nPayType5;
		pButton = &m_btnPayType5;
	}

	*nSel = nPayType;
	pButton->SetWindowText(STR_PAY_TYPE[nPayType]);
}

void COptionDlgGeneral2::SaveCarType(long nCarType)
{
	if(m_nCarType1 == nCarType ||
		m_nCarType2 == nCarType ||
		m_nCarType3 == nCarType ||
		m_nCarType4 == nCarType ||
		m_nCarType5 == nCarType)
	{
		MessageBox("동일한 항목이 저장되어 있습니다", "확인", MB_ICONINFORMATION);
		return;

	}
	CButton *pButton = NULL;
	long *nSel = NULL;

	if(m_nLastSelCarBtn == ZERO)
	{
		nSel = &m_nCarType1;
		pButton = &m_btnCarType1;
	}
	else if(m_nLastSelCarBtn == ONE)
	{
		nSel = &m_nCarType2;
		pButton = &m_btnCarType2;
	}
	else if(m_nLastSelCarBtn == 2)
	{
		nSel = &m_nCarType3;
		pButton = &m_btnCarType3;
	}
	else if(m_nLastSelCarBtn == 3)
	{
		nSel = &m_nCarType4;
		pButton = &m_btnCarType4;
	}
	else if(m_nLastSelCarBtn == 4)
	{
		nSel = &m_nCarType5;
		pButton = &m_btnCarType5;
	}

	*nSel = nCarType;
	pButton->SetWindowText(LF->GetCarTypeFromLong(nCarType));
}

void COptionDlgGeneral2::SetCarOrder(CString strCarTypeOrder)
{
	long nCarType = ZERO;
	long nFirstFind = ZERO;
	long nSecondFind = ZERO; 
	long nNewVisible = ZERO;
	long nStrIndex = ZERO;

	if(LF->GetCommaCount(strCarTypeOrder) == 5)
	{ 
		for(int i = ZERO; i < 5; i++)
		{
			nSecondFind = strCarTypeOrder.Find(";", nFirstFind);
			nCarType = _ttoi(strCarTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));


			if(i == ZERO)
			{
				m_nCarType1 = nCarType;
				m_btnCarType1.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == ONE)
			{
				m_nCarType2 = nCarType;
				m_btnCarType2.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == 2)
			{
				m_nCarType3 = nCarType;
				m_btnCarType3.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == 3)
			{
				m_nCarType4 = nCarType;
				m_btnCarType4.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == 4)
			{
				m_nCarType5 = nCarType;
				m_btnCarType5.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			nFirstFind = nSecondFind + 1;
		}
	}
	else if(LF->GetCommaCount(strCarTypeOrder) == 3)
	{
		for(int i = ZERO; i < 3; i++)
		{
			nSecondFind = strCarTypeOrder.Find(";", nFirstFind);
			nCarType = _ttoi(strCarTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));
			if(i == ZERO)
			{
				m_nCarType1 = nCarType;
				m_btnCarType1.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == ONE)
			{
				m_nCarType2 = nCarType;
				m_btnCarType2.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			else if(i == 2)
			{
				m_nCarType3 = nCarType;
				m_btnCarType3.SetWindowText(LF->GetCarTypeFromLong(nCarType));
			}
			nFirstFind = nSecondFind + 1;
		}

		BOOL bFindCarType4 = FALSE;
		CString strTemp;
		for(int i = 0; i < 5; i++)
		{
			strTemp.Format("%d", i);
			if(strCarTypeOrder.Find(strTemp) == -1)
			{
				if(bFindCarType4 == FALSE)
				{
					m_nCarType4 = i;
					m_btnCarType4.SetWindowText(LF->GetCarTypeFromLong(m_nCarType4));
					bFindCarType4 = TRUE;
				}
				else
				{
					m_nCarType5 = i;
					m_btnCarType5.SetWindowText(LF->GetCarTypeFromLong(m_nCarType5));
					break;
				}
			}
		}
	}
	else
	{
		m_nCarType1 = CAR_AUTO;
		m_btnCarType1.SetWindowText(LF->GetCarTypeFromLong(m_nCarType1));
		m_nCarType2 = CAR_DAMA;
		m_btnCarType2.SetWindowText(LF->GetCarTypeFromLong(m_nCarType2));
		m_nCarType3 = CAR_LABO;
		m_btnCarType3.SetWindowText(LF->GetCarTypeFromLong(m_nCarType3));
		m_nCarType4 = CAR_BIGBIKE;
		m_btnCarType4.SetWindowText(LF->GetCarTypeFromLong(m_nCarType4));
		m_nCarType5 = CAR_TRUCK;
		m_btnCarType5.SetWindowText(LF->GetCarTypeFromLong(m_nCarType5));
	}
}

void COptionDlgGeneral2::SetPayOrder(CString strPayTypeOrder)
{
	if(LF->GetCommaCount(strPayTypeOrder) == 5) 
	{
		long nPayType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i = ZERO; i < 5; i++)
		{
			nSecondFind = strPayTypeOrder.Find(";", nFirstFind);
			nPayType = _ttoi(strPayTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
			{
				m_nPayType1 = nPayType;
				m_btnPayType1.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == ONE)
			{
				m_nPayType2 = nPayType;
				m_btnPayType2.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == 2)
			{
				m_nPayType3 = nPayType;
				m_btnPayType3.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == 3)
			{
				m_nPayType4 = nPayType;
				m_btnPayType4.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == 4)
			{
				m_nPayType5 = nPayType;
				m_btnPayType5.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			nFirstFind = nSecondFind + 1;
		}
	}
	else if(LF->GetCommaCount(strPayTypeOrder) == 4)
	{
		long nPayType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i = ZERO; i < 4; i++)
		{
			nSecondFind = strPayTypeOrder.Find(";", nFirstFind);
			nPayType = _ttoi(strPayTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
			{
				m_nPayType1 = nPayType;
				m_btnPayType1.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == ONE)
			{
				m_nPayType2 = nPayType;
				m_btnPayType2.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == 2)
			{
				m_nPayType3 = nPayType;
				m_btnPayType3.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			else if(i == 3)
			{
				m_nPayType4 = nPayType;
				m_btnPayType4.SetWindowText(STR_PAY_TYPE[nPayType]);
			}
			nFirstFind = nSecondFind + 1;
		}

		CString strTemp;
		for(int i = 0; i < 5; i++)
		{
			strTemp.Format("%d", i);
			if(strPayTypeOrder.Find(strTemp) == -1)
			{
				m_nPayType5 = i;
				m_btnPayType5.SetWindowText(STR_PAY_TYPE[i]);
				break;
			}
		}
	}
	else
	{
		m_nPayType1 = PAY_PRE;
		m_btnPayType1.SetWindowText(STR_PAY_TYPE[m_nPayType1]);
		m_nPayType2 = PAY_AFTER;
		m_btnPayType2.SetWindowText(STR_PAY_TYPE[m_nPayType2]);
		m_nPayType3 = PAY_CREDIT;
		m_btnPayType3.SetWindowText(STR_PAY_TYPE[m_nPayType3]);
		m_nPayType4 = PAY_ONLINE;
		m_btnPayType4.SetWindowText(STR_PAY_TYPE[m_nPayType4]);
		m_nPayType5 = PAY_CARD;
		m_btnPayType5.SetWindowText(STR_PAY_TYPE[m_nPayType5]);
	}
}
void COptionDlgGeneral2::OnBnClickedPayTypeBtn4()
{
	OpenPayContextMenu(3);
}

void COptionDlgGeneral2::OnBnClickedAutoShareOrderCheck()
{
	m_edtAutoShareTime.EnableWindow(m_chkAutoShareOrder.GetCheck());
}

void COptionDlgGeneral2::OnSize(UINT nType, int cx, int cy)
{
	return; 
	CMyFormView::OnSize(nType, cx, cy);	
}

void COptionDlgGeneral2::OnBnClickedRevisitCustomerCheck()
{
	m_edtRevisitCustomerSendDay.EnableWindow(m_chkRevisitCustomer.GetCheck());
}

void COptionDlgGeneral2::OnBnClickedTankAllViewButton()
{
	

	CTankTypeQDlg dlg;
	dlg.m_nCompany = m_ui.nCompany;
	dlg.DoModal();
}

void COptionDlgGeneral2::OnBnClickedMyCallBtn()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode();

	if(nCompany <= 0)
	{
		MessageBox("지사를 선택하시기 바랍니다.","지사 선택",MB_ICONINFORMATION);
		return;
	}
	CMyCallDepositDlg dlg;
	dlg.m_nCompany = nCompany;
	dlg.DoModal();

}

void COptionDlgGeneral2::OnBnClickedMycallRiderDepositCheck()
{
	if(m_chkMyCallRiderDeposit.GetCheck())
		m_btnMyCallRiderDeposit.EnableWindow(TRUE);	
	else
		m_btnMyCallRiderDeposit.EnableWindow(FALSE);	
}

void COptionDlgGeneral2::OnBnClickedPayTypeBtn5()
{
	OpenPayContextMenu(4);
}

void COptionDlgGeneral2::OnBnClickedCarTypeBtn4()
{
	OpenCarContextMenu(3);
}

void COptionDlgGeneral2::OnBnClickedCarTypeBtn5()
{
	OpenCarContextMenu(4);
}

void COptionDlgGeneral2::OnBnClickedCallerIDToPhone1()
{
	m_chkNotClientPhone1.EnableWindow(m_chkCallerIDToPhone1.GetCheck());
}

void COptionDlgGeneral2::OnBnClickedTipButton()
{
	COptionTipDlg dlg;
	dlg.DoModal();
}

void COptionDlgGeneral2::OnBnClickedFirstReceiptWaitChangeTimeCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgGeneral2::OnBnClickedHistoryDetailAllView()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgGeneral2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}

void COptionDlgGeneral2::OnBnClickedKakaoHelpBtn()
{
	ShellExecute(NULL, "open", "iexplore.exe", "http://0070.co.kr/helpapi/index_q.html", "", SW_SHOW); 
}
