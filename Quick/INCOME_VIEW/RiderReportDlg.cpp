// RiderReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderReportDlg.h"
#include "WebPrintDlg.h"
#include "RiderReportOrderDlg.h"
//#include "IncomeForm7.h"
#include "RiderDepositInfoDlg.h"

#define MAX_ETC_COUNT 20
// CRiderReportDlg 대화 상자입니다.

HBRUSH m_Bluebrush = CreateSolidBrush(RGB(230,230,255)); 
HBRUSH m_Redbrush = CreateSolidBrush(RGB(255,230,230)); 
HBRUSH m_Whitebrush = CreateSolidBrush(RGB(255,255,255)); 

IMPLEMENT_DYNAMIC(CRiderReportDlg, CMyDialog)
CRiderReportDlg::CRiderReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderReportDlg::IDD, pParent)
{
	m_Font = m_FontManager.GetFont("맑은 고딕", 16);
	m_bComplete = FALSE;
	m_dtFrom = COleDateTime::GetCurrentTime();
	m_dtTo = COleDateTime::GetCurrentTime();
	m_nRiderCharge = 0;
	m_pRiderReportOrderDlg = NULL;

	m_nCashDTType = 0;
	m_bCashDTWon = 0;
	m_strCashDTFee = "";
	m_nMyCallDTType = 0;
	m_bMyCallDTWon = 0;
	m_strMyCallDTFee = "";
	m_nOtherCallDTType = 0;
	m_bOtherCallDTWon = 0;
	m_strOtherCallDTFee = "";

	m_bAbleMove = FALSE;
	m_pParentWnd = pParent;

	m_nMyCallGiveToRiderCount = 0;
	m_nMyCallGiveToRiderCharge = 0;
	m_nOtherCallGiveToRiderCount = 0;
	m_nOtherCallGiveToRiderCharge = 0;

	m_nFixedDepositIncomeOnline = 0;

	m_bInitList = FALSE;
}

CRiderReportDlg::~CRiderReportDlg()
{	
	if(m_pRiderReportOrderDlg != NULL)
	{
		delete m_pRiderReportOrderDlg;
		m_pRiderReportOrderDlg = NULL;
	}
}

void CRiderReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_COMPLETE_BTN, m_btnComplete);
	DDX_Control(pDX, IDC_DELETE_REPORT_BTN, m_btnDeleteReport);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_REPORT_LIST2, m_lstReport2);

	DDX_Control(pDX, IDC_RECEIVE_CHARGE_EDIT, m_edtReceiveCharge);
	DDX_Control(pDX, IDC_FIXED_DEPOSIT_EDIT, m_edtFixedDeposit);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CASH_COUNT_EDIT, m_edtMyCallAllCashCount);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CASH_CHARGE_EDIT, m_edtMyCallAllCashCharge);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_CASH_COUNT_EDIT, m_edtMyCallApplyCashCount);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_CASH_CHARGE_EDIT, m_edtMyCallApplyCashCharge);
	DDX_Control(pDX, IDC_MY_CALL_CASH_FEE_EDIT, m_edtMyCallCashFee);
	DDX_Control(pDX, IDC_MY_CALL_CASH_WON_BTN, m_btnMyCallCashWon);
	DDX_Control(pDX, IDC_MY_CALL_CASH_FEE_TOTAL_EDIT, m_edtMyCallCashFeeTotal);

	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CASH_COUNT_EDIT, m_edtOtherCallAllCashCount);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CASH_CHARGE_EDIT, m_edtOtherCallAllCashCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_CASH_COUNT_EDIT, m_edtOtherCallApplyCashCount);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_CASH_CHARGE_EDIT, m_edtOtherCallApplyCashCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_CASH_FEE_EDIT, m_edtOtherCallCashFee);
	DDX_Control(pDX, IDC_OTHER_CALL_CASH_WON_BTN, m_btnOtherCallCashWon);
	DDX_Control(pDX, IDC_OTHER_CALL_CASH_FEE_TOTAL_EDIT, m_edtOtherCallCashFeeTotal);
	DDX_Control(pDX, IDC_CASH_CALL_ALL_COUNT_EDIT, m_edtCashCallAllCount);
	DDX_Control(pDX, IDC_CASH_CALL_ALL_CHARGE_EDIT, m_edtCashCallAllCharge);
	DDX_Control(pDX, IDC_CASH_FEE_TOTAL_EDIT, m_edtCashFeeTotal);
	DDX_Control(pDX, IDC_LAST_MONTH_EDIT, m_edtLastMonth);
	DDX_Control(pDX, IDC_CASH_MY_CALL_DEDUCTING_TAX_CHECK, m_chkCashMyCallDeductingTax);
	DDX_Control(pDX, IDC_CASH_OTHER_CALL_DEDUCTING_TAX_CHECK, m_chkCashOtherCallDeductingTax);
	DDX_Control(pDX, IDC_CASH_DEDUCTING_TAX_FEE_EDIT, m_edtCashDeductingTaxFee);
	DDX_Control(pDX, IDC_CASH_DEDUCTING_TAX_FEE_BTN, m_btnCashDeductingTaxFee);
	DDX_Control(pDX, IDC_CASH_DEDUCTING_TAX_FEE_TOTAL_EDIT, m_edtCashDeductingTaxFeeTotal);
	DDX_Control(pDX, IDC_TAKE_TOTAL_EDIT, m_edtTakeTotal);
	DDX_Control(pDX, IDC_TAKE_TOTAL_EDIT1, m_edtTakeTotal1);
	DDX_Control(pDX, IDC_MY_CALL_BEFORE_CHECK, m_chkMyCallBefore);
	DDX_Control(pDX, IDC_MY_CALL_AFTER_CHECK, m_chkMyCallAfter);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CREDIT_COUNT_EDIT, m_edtMyCallAllCreditCount);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CREDIT_CHARGE_EDIT, m_edtMyCallAllCreditCharge);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_CREDIT_COUNT_EDIT, m_edtMyCallNotApplyCreditCount);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_CREDIT_CHARGE_EDIT, m_edtMyCallNotApplyCreditCharge);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_CREDIT_COUNT_EDIT, m_edtMyCallApplyCreditCount);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_CREDIT_CHARGE_EDIT, m_edtMyCallApplyCreditCharge);
	DDX_Control(pDX, IDC_MY_CALL_CREDIT_FEE_EDIT, m_edtMyCallCreditFee);
	DDX_Control(pDX, IDC_MY_CALL_CREDIT_WON_BTN, m_btnMyCallCreditWon);
	DDX_Control(pDX, IDC_MY_CALL_CREDIT_FEE_TOTAL_EDIT, m_edtMyCallCreditFeeTotal);
	DDX_Control(pDX, IDC_MY_CALL_ALL_ONLINE_COUNT_EDIT, m_edtMyCallAllOnlineCount);
	DDX_Control(pDX, IDC_MY_CALL_ALL_ONLINE_CHARGE_EDIT, m_edtMyCallAllOnlineCharge);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_ONLINE_COUNT_EDIT, m_edtMyCallNotApplyOnlineCount);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_ONLINE_CHARGE_EDIT, m_edtMyCallNotApplyOnlineCharge);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_ONLINE_COUNT_EDIT, m_edtMyCallApplyOnlineCount);
	DDX_Control(pDX, IDC_MY_CALL_APPLY_ONLINE_CHARGE_EDIT, m_edtMyCallApplyOnlineCharge);
	DDX_Control(pDX, IDC_MY_CALL_ONLINE_FEE_EDIT, m_edtMyCallOnlineFee);
	DDX_Control(pDX, IDC_MY_CALL_ONLINE_WON_BTN, m_btnMyCallOnlineWon);
	DDX_Control(pDX, IDC_MY_CALL_ONLINE_FEE_TOTAL_EDIT, m_edtMyCallOnlineFeeTotal);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CREDIT_ONLINE_COUNT_EDIT, m_edtMyCallAllCreditOnlineCount);
	DDX_Control(pDX, IDC_MY_CALL_ALL_CREDIT_ONLINE_CHARGE_EDIT, m_edtMyCallAllCreditOnlineCharge);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_CREDIT_ONLINE_COUNT_EDIT, m_edtMyCallNotApplyCreditOnlineCount);
	DDX_Control(pDX, IDC_MY_CALL_NOT_APPLY_CREDIT_ONLINE_CHARGE_EDIT, m_edtMyCallNotApplyCreditOnlineCharge);
	DDX_Control(pDX, IDC_MY_CALL_CREDIT_ONLINE_FEE_TOTAL_EDIT, m_edtMyCallCreditOnlineFeeTotal);
	DDX_Control(pDX, IDC_BEFORE_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, m_edtBeforeMyCallCreditOnlineDeductingTaxFee);
	DDX_Control(pDX, IDC_BEFORE_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_WON_BTN, m_btnBeforeMyCallCreditOnlineDeductingTaxWon);
	DDX_Control(pDX, IDC_BEFORE_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_TOTAL_EDIT, m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal);
	DDX_Control(pDX, IDC_AFTER_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, m_edtAfterMyCallCreditOnlineDeductingTaxFee);
	DDX_Control(pDX, IDC_AFTER_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_WON_BTN, m_btnAfterMyCallCreditOnlineDeductingTaxWon);
	DDX_Control(pDX, IDC_AFTER_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_TOTAL_EDIT, m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal);
	DDX_Control(pDX, IDC_OTHER_CALL_BEFORE_CHECK, m_chkOtherCallBefore); 
	DDX_Control(pDX, IDC_OTHER_CALL_AFTER_CHECK, m_chkOtherCallAfter);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CREDIT_COUNT_EDIT, m_edtOtherCallAllCreditCount);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CREDIT_CHARGE_EDIT, m_edtOtherCallAllCreditCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_CREDIT_COUNT_EDIT, m_edtOtherCallNotApplyCreditCount);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_CREDIT_CHARGE_EDIT, m_edtOtherCallNotApplyCreditCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_CREDIT_COUNT_EDIT, m_edtOtherCallApplyCreditCount);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_CREDIT_CHARGE_EDIT, m_edtOtherCallApplyCreditCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_CREDIT_FEE_EDIT, m_edtOtherCallCreditFee);
	DDX_Control(pDX, IDC_OTHER_CALL_CREDIT_WON_BTN, m_btnOtherCallCreditWon);
	DDX_Control(pDX, IDC_OTHER_CALL_CREDIT_FEE_TOTAL_EDIT, m_edtOtherCallCreditFeeTotal);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_ONLINE_COUNT_EDIT, m_edtOtherCallAllOnlineCount);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_ONLINE_CHARGE_EDIT, m_edtOtherCallAllOnlineCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_ONLINE_COUNT_EDIT, m_edtOtherCallNotApplyOnlineCount);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_ONLINE_CHARGE_EDIT, m_edtOtherCallNotApplyOnlineCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_ONLINE_COUNT_EDIT, m_edtOtherCallApplyOnlineCount);
	DDX_Control(pDX, IDC_OTHER_CALL_APPLY_ONLINE_CHARGE_EDIT, m_edtOtherCallApplyOnlineCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_ONLINE_FEE_EDIT, m_edtOtherCallOnlineFee);
	DDX_Control(pDX, IDC_OTHER_CALL_ONLINE_WON_BTN, m_btnOtherCallOnlineWon);
	DDX_Control(pDX, IDC_OTHER_CALL_ONLINE_FEE_TOTAL_EDIT, m_edtOtherCallOnlineFeeTotal);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CREDIT_ONLINE_COUNT_EDIT, m_edtOtherCallAllCreditOnlineCount);
	DDX_Control(pDX, IDC_OTHER_CALL_ALL_CREDIT_ONLINE_CHARGE_EDIT, m_edtOtherCallAllCreditOnlineCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_CREDIT_ONLINE_COUNT_EDIT, m_edtOtherCallNotApplyCreditOnlineCount);
	DDX_Control(pDX, IDC_OTHER_CALL_NOT_APPLY_CREDIT_ONLINE_CHARGE_EDIT, m_edtOtherCallNotApplyCreditOnlineCharge);
	DDX_Control(pDX, IDC_OTHER_CALL_CREDIT_ONLINE_FEE_TOTAL_EDIT, m_edtOtherCallCreditOnlineFeeTotal);

	//	DDX_Control(pDX, IDC_BEFORE_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, m_edtBeforeOtherCallCreditOnlineDeductingTaxFee);
	DDX_Control(pDX, IDC_BEFORE_OTHER_CALL_ALL_CREADIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, m_edtBeforeOtherCallCreditOnlineDeductingTaxFee);
	DDX_Control(pDX, IDC_BEFORE_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_WON_BTN, m_btnBeforeOtherCallCreditOnlineDeductingWon);
	DDX_Control(pDX, IDC_BEFORE_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_TOTAL_EDIT, m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal);
	DDX_Control(pDX, IDC_AFTER_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, m_edtAfterOtherCallCreditOnlineDeductingTaxFee);
	DDX_Control(pDX, IDC_AFTER_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_WON_BTN, m_btnAfterOtherCallCreditOnlineDeductingWon);
	DDX_Control(pDX, IDC_AFTER_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_TOTAL_EDIT, m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal);
	DDX_Control(pDX, IDC_PRINT_BTN, m_btnPrint);
	DDX_Control(pDX, IDC_DELETE_REPORT_BTN, m_btnDeleteReport);
	DDX_Control(pDX, IDC_GIVE_TOTAL_EDIT, m_edtGiveTotal);
	DDX_Control(pDX, IDC_GIVE_TOTAL_EDIT1, m_edtGiveTotal1);
	DDX_Control(pDX, IDC_GIVE_ETC_TOTAL_EDIT, m_edtGiveEtcTotal);
	DDX_Control(pDX, IDC_GIVE_GROUP_STC, m_stcGiveGroup);
	DDX_Control(pDX, IDC_TAKE_GROUP_STC, m_stcTakeGroup);
	DDX_Control(pDX, IDC_TAKE_ETC_TOTAL_EDIT, m_edtTakeEtcTotal);
	DDX_Control(pDX, IDC_TRANS_COUNT_EDIT, m_edtTransCount);
	DDX_Control(pDX, IDC_TRANS_CHARGE_EDIT, m_edtTransCharge);
	DDX_Control(pDX, IDC_TOTAL_EDIT, m_edtTotal);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);

	DDX_Control(pDX, IDC_COUPON_EDIT, m_edtCoupon);
	DDX_Control(pDX, IDC_COUPON_PLUS_EDIT, m_edtCouponPlus);
	DDX_Control(pDX, IDC_COUPON_TOTAL_EDIT, m_edtCouponTotal);

	DDX_Control(pDX, IDC_TAKE_STC100, m_stcTakeEtc100);
	DDX_Control(pDX, IDC_TAKE_STC101, m_stcTakeEtc101);
	DDX_Control(pDX, IDC_TAKE_STC102, m_stcTakeEtc102);
	DDX_Control(pDX, IDC_TAKE_STC103, m_stcTakeEtc103);
	DDX_Control(pDX, IDC_TAKE_STC104, m_stcTakeEtc104);
	DDX_Control(pDX, IDC_TAKE_STC105, m_stcTakeEtc105);
	DDX_Control(pDX, IDC_TAKE_STC106, m_stcTakeEtc106);
	DDX_Control(pDX, IDC_TAKE_STC107, m_stcTakeEtc107);
	DDX_Control(pDX, IDC_TAKE_STC108, m_stcTakeEtc108);
	DDX_Control(pDX, IDC_TAKE_STC109, m_stcTakeEtc109);
	DDX_Control(pDX, IDC_TAKE_STC111, m_stcTakeEtc111);
	DDX_Control(pDX, IDC_TAKE_STC112, m_stcTakeEtc112);
	DDX_Control(pDX, IDC_TAKE_STC113, m_stcTakeEtc113);
	DDX_Control(pDX, IDC_TAKE_STC114, m_stcTakeEtc114);
	DDX_Control(pDX, IDC_TAKE_STC115, m_stcTakeEtc115);
	DDX_Control(pDX, IDC_TAKE_STC116, m_stcTakeEtc116);
	DDX_Control(pDX, IDC_TAKE_STC117, m_stcTakeEtc117);

	DDX_Control(pDX, IDC_GIVE_STC100, m_stcGiveEtc100);
	DDX_Control(pDX, IDC_GIVE_STC101, m_stcGiveEtc101);
	DDX_Control(pDX, IDC_GIVE_STC102, m_stcGiveEtc102);
	DDX_Control(pDX, IDC_GIVE_STC103, m_stcGiveEtc103);
	DDX_Control(pDX, IDC_GIVE_STC104, m_stcGiveEtc104);
	DDX_Control(pDX, IDC_GIVE_STC105, m_stcGiveEtc105);
	DDX_Control(pDX, IDC_GIVE_STC106, m_stcGiveEtc106);
	DDX_Control(pDX, IDC_GIVE_STC107, m_stcGiveEtc107);
	DDX_Control(pDX, IDC_GIVE_STC108, m_stcGiveEtc108);
	DDX_Control(pDX, IDC_GIVE_STC109, m_stcGiveEtc109);
	DDX_Control(pDX, IDC_GIVE_STC110, m_stcGiveEtc110);
	DDX_Control(pDX, IDC_GIVE_STC111, m_stcGiveEtc111);
	DDX_Control(pDX, IDC_GIVE_STC112, m_stcGiveEtc112);
	DDX_Control(pDX, IDC_GIVE_STC113, m_stcGiveEtc113);
	DDX_Control(pDX, IDC_GIVE_STC114, m_stcGiveEtc114);
	DDX_Control(pDX, IDC_GIVE_STC115, m_stcGiveEtc115);
	DDX_Control(pDX, IDC_GIVE_STC116, m_stcGiveEtc116);
	DDX_Control(pDX, IDC_GIVE_STC117, m_stcGiveEtc117);
	DDX_Control(pDX, IDC_GIVE_STC118, m_stcGiveEtc118);
	DDX_Control(pDX, IDC_GIVE_STC119, m_stcGiveEtc119);
	DDX_Control(pDX, IDC_GIVE_STC120, m_stcGiveEtc120);
	DDX_Control(pDX, IDC_GIVE_STC121, m_stcGiveEtc121);
	DDX_Control(pDX, IDC_TOTAL_STATIC, m_stcTotal);

	DDX_Control(pDX, IDC_RIDER_STATIC, m_stcRider);
	DDX_Control(pDX, IDC_REPORT_NO_STC, m_stcReportNo);
	DDX_Control(pDX, IDC_COUNT_STC, m_stcCount);
	DDX_Control(pDX, IDC_SMS_CHECK, m_chkSMS);
	DDX_Control(pDX, IDC_PDA_CHECK, m_chkPDA);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_MY_GIVE_CHARGE_STATIC, m_stcMyGiveCharge);
	DDX_Control(pDX, IDC_OTHER_GIVE_CHARGE_STATIC, m_stcOtherGiveCharge);
}


BEGIN_MESSAGE_MAP(CRiderReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_OPEN_BTN, OnBnClickedOpenBtn)
	ON_BN_CLICKED(IDC_OPEN_BTN2, OnBnClickedOpenBtn2)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST2, OnReportItemClick2)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN2, OnBnClickedDeleteBtn2)
	ON_BN_CLICKED(IDC_REFRESH_ORDER_BTN, OnBnClickedRefreshOrderBtn)
	ON_BN_CLICKED(IDC_COMPLETE_BTN, OnBnClickedCompleteBtn)
	ON_BN_CLICKED(IDC_PRINT_BTN, OnBnClickedPrintBtn)
	ON_BN_CLICKED(IDC_APPLICATION_BTN, OnBnClickedApplicationBtn)
	ON_BN_CLICKED(IDC_APPLICATION_BTN2, OnBnClickedApplicationBtn2)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_REPORT_LIST, OnReportItemChange)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_REPORT_LIST2, OnReportItemChange2)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_DELETE_REPORT_BTN, OnBnClickedDeleteReportBtn)
ON_BN_CLICKED(IDC_SAVE_OPTION_BTN, OnBnClickedSaveOptionBtn)
ON_BN_CLICKED(IDC_MY_CALL_CASH_WON_BTN, OnBnClickedMyCallCashWonBtn)
ON_BN_CLICKED(IDC_OTHER_CALL_CASH_WON_BTN, OnBnClickedOtherCallCashWonBtn)
ON_BN_CLICKED(IDC_MY_CALL_ONLINE_WON_BTN, OnBnClickedMyCallOnlineWonBtn)
ON_BN_CLICKED(IDC_OTHER_CALL_CREDIT_WON_BTN, OnBnClickedOtherCallCreditWonBtn)
ON_BN_CLICKED(IDC_OTHER_CALL_ONLINE_WON_BTN, OnBnClickedOtherCallOnlineWonBtn)
ON_BN_CLICKED(IDC_CASH_DEDUCTING_TAX_FEE_BTN, OnBnClickedCashDeductingTaxFeeBtn)
ON_BN_CLICKED(IDC_AFTER_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_WON_BTN, OnBnClickedAfterMyCallCreditOnlineDeductingTaxWonBtn)
ON_BN_CLICKED(IDC_BEFORE_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_WON_BTN, OnBnClickedBeforeMyCallCreditOnlineDeductingTaxWonBtn)
ON_BN_CLICKED(IDC_BEFORE_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_WON_BTN, OnBnClickedBeforeOtherCallCreditOnlineDeductingWonBtn)
ON_BN_CLICKED(IDC_AFTER_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_WON_BTN, OnBnClickedAfterOtherCallCreditOnlineDeductingWonBtn)
ON_BN_CLICKED(IDC_CASH_MY_CALL_DEDUCTING_TAX_CHECK, OnBnClickedCashMyCallDeductingTaxCheck)
ON_BN_CLICKED(IDC_OTHER_CALL_BEFORE_CHECK, OnBnClickedOtherCallBeforeCheck)
ON_BN_CLICKED(IDC_OTHER_CALL_AFTER_CHECK, OnBnClickedOtherCallAfterCheck)
ON_BN_CLICKED(IDC_MY_CALL_BEFORE_CHECK, OnBnClickedMyCallBeforeCheck)
ON_BN_CLICKED(IDC_MY_CALL_AFTER_CHECK, OnBnClickedMyCallAfterCheck)
ON_BN_CLICKED(IDC_CASH_OTHER_CALL_DEDUCTING_TAX_CHECK, OnBnClickedCashOtherCallDeductingTaxCheck)
ON_EN_CHANGE(IDC_MY_CALL_CASH_FEE_EDIT, OnEnChangeMyCallCashFeeEdit)
ON_EN_CHANGE(IDC_OTHER_CALL_CASH_FEE_EDIT, OnEnChangeOtherCallCashFeeEdit)
ON_EN_CHANGE(IDC_CASH_DEDUCTING_TAX_FEE_EDIT, OnEnChangeCashDeductingTaxFeeEdit)
ON_EN_CHANGE(IDC_BEFORE_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, OnEnChangeBeforeMyCallCreditOnlineDeductingTaxFeeEdit)
ON_EN_CHANGE(IDC_MY_CALL_CREDIT_FEE_EDIT, OnEnChangeMyCallCreditFeeEdit)
ON_EN_CHANGE(IDC_MY_CALL_ONLINE_FEE_EDIT, OnEnChangeMyCallOnlineFeeEdit)
ON_EN_CHANGE(IDC_OTHER_CALL_CREDIT_FEE_EDIT, OnEnChangeOtherCallCreditFeeEdit)
ON_EN_CHANGE(IDC_OTHER_CALL_ONLINE_FEE_EDIT, OnEnChangeOtherCallOnlineFeeEdit)
ON_EN_CHANGE(IDC_AFTER_OTHER_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, OnEnChangeAfterOtherCallCreditOnlineDeductingTaxFeeEdit)
ON_BN_CLICKED(IDC_MY_CALL_CREDIT_WON_BTN, OnBnClickedMyCallCreditWonBtn)
ON_EN_CHANGE(IDC_FIXED_DEPOSIT_EDIT, OnEnChangeFixedDepositEdit)
ON_EN_CHANGE(IDC_AFTER_MY_CALL_CREDIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, OnEnChangeAfterMyCallCreditOnlineDeductingTaxFeeEdit)
ON_EN_CHANGE(IDC_BEFORE_OTHER_CALL_ALL_CREADIT_ONLINE_DEDUCTING_TAX_FEE_EDIT, OnEnChangeBeforeOtherCallAllCreaditOnlineDeductingTaxFeeEdit)
ON_WM_NCLBUTTONDOWN()
ON_BN_CLICKED(IDC_SAVE_BTN2, OnBnClickedSaveBtn2)
ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
ON_EN_CHANGE(IDC_COUPON_PLUS_EDIT, OnEnChangeCouponPlusEdit)
ON_WM_PAINT()
END_MESSAGE_MAP()

#define MY_CALL_CASH 0 
#define OTHER_CALL_CASH 1
#define MY_CALL_CREDIT 2
#define MY_CALL_ONLINE 3
#define OTHER_CALL_CREDIT 4
#define OTHER_CALL_ONLINE 5

long CRiderReportDlg::GetOrderType(long nShareCode1, long nRiderShareCode1, long nPayType)
{
	if((nShareCode1 == nRiderShareCode1)  || nRiderShareCode1 == 0)
	{
		if(nPayType == 0 || nPayType == 1 || nPayType == 4) 
			return MY_CALL_CASH;

		if(nPayType == 2 || nPayType == 7) 
			return MY_CALL_CREDIT;
				
		if(nPayType == 3) 
			return MY_CALL_ONLINE;
	}

	if((nShareCode1 != nRiderShareCode1)  && nRiderShareCode1 != 0) 
	{
		if(nPayType == 0 || nPayType == 1 || nPayType == 4)
			return OTHER_CALL_CASH;

		if(nPayType == 2 || nPayType == 7)
			return OTHER_CALL_CREDIT;

		if(nPayType == 3)
			return OTHER_CALL_ONLINE;
	}

	return -1;
}

void CRiderReportDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(m_bInitList == FALSE)
		return;

	long nIndex = m_lstReport.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex == -1) return;

	m_lstReport.SetItemText(nIndex, 0, "1");
	FindNotAvailabilityRow(&m_lstReport, nIndex);

	RefreshCharge();
}

void CRiderReportDlg::OnReportItemChange2(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(m_bInitList == FALSE)
		return;

	long nIndex = m_lstReport2.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex == -1) return;

	m_lstReport2.SetItemText(nIndex, 0, "2");
	FindNotAvailabilityRow(&m_lstReport2, nIndex);

	RefreshCharge();
}

void CRiderReportDlg::FindNotAvailabilityRow(CXTPListCtrl2 *pList, long nIndex)
{
	for(int i=0; i<MAX_ETC_COUNT; i++)
	{
		if(nIndex == i)
			continue;

		CString sEtc = pList->GetItemText(i, 1);
		CString sEtcCharge = pList->GetItemText(i, 2);

		if(sEtc == "" || sEtcCharge == "")
		{
			if(m_lstReport.GetSafeHwnd() == pList->GetSafeHwnd())
				m_lstReport.SetItemText(i, 0, "");

			if(m_lstReport2.GetSafeHwnd() == pList->GetSafeHwnd())
				m_lstReport2.SetItemText(i, 0, "");
		}
	}

}

void CRiderReportDlg::OnBnClickedRefreshBtn()
{
	InitData(); 
	InitCharge();
	//ChangeTakeFee();
	//ChangeGiveFee();
	RefreshCharge(); 

	if(!m_bComplete)
		OnBnClickedOpenBtn();

	MakeMsg();
}

void CRiderReportDlg::InitData()
{
	m_map.clear();
			
	COleDateTime dtFrom; m_FromDT.GetTime(dtFrom);
	COleDateTime dtTo; m_ToDT.GetTime(dtTo);

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rider_order_count_10");

	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTo);
	CMkParameter *parRiderCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	CMkParameter *parMyCallCashWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallCash = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallCashWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallCash = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallCreditWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallCredit = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallCreditWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallCredit = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallOnlineWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallOnline = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallOnlineWon = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallOnline = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	CMkParameter *pParMyCashApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCashApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCreditApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCreditApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyOnlineApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherOnlineApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	CMkParameter *parCashDTType= pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parCashDTWon = pCmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);
	CMkParameter *parCashDTFee = pCmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parMyCallDTType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parMyCallDTWon = pCmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);
	CMkParameter *parMyCallDTFee = pCmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parOtherCallDTType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parOtherCallDTWon = pCmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);
	CMkParameter *parOtherCallDTFee = pCmd.AddParameter(typeString, typeOutput, 50, "");

	CMkParameter *parUseDTPercent = pCmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);
	CMkParameter *parDT = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parIncomeOnline = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;
	parRiderCharge->GetValue(m_nRiderCharge);
	parIncomeOnline->GetValue(m_nFixedDepositIncomeOnline);

	parUseDTPercent->GetValue(m_bUseDTPercent);
	parDT->GetValue(m_nDT);

	parMyCallCashWon->GetValue(m_bMyCallCashWon);
	parMyCallCash->GetValue(m_nMyCallCash);
	parOtherCallCashWon->GetValue(m_bOtherCallCashWon);
	parOtherCallCash->GetValue(m_nOtherCallCash);
	parMyCallCreditWon->GetValue(m_bMyCallCreditWon);
	parMyCallCredit->GetValue(m_nMyCallCredit);
	parOtherCallCreditWon->GetValue(m_bOtherCallCreditWon);
	parOtherCallCredit->GetValue(m_nOtherCallCredit);
	parMyCallOnlineWon->GetValue(m_bMyCallOnlineWon);
	parMyCallOnline->GetValue(m_nMyCallOnline);
	parOtherCallOnlineWon->GetValue(m_bOtherCallOnlineWon);
	parOtherCallOnline->GetValue(m_nOtherCallOnline);

	pParMyCashApplyCharge->GetValue(m_nMyCashApplyCharge);
	parOtherCashApplyCharge->GetValue(m_nOtherCashApplyCharge);
	parMyCreditApplyCharge->GetValue(m_nMyCreditApplyCharge);
	parOtherCreditApplyCharge->GetValue(m_nOtherCreditApplyCharge);
	parMyOnlineApplyCharge->GetValue(m_nMyOnlineApplyCharge);
	parOtherOnlineApplyCharge->GetValue(m_nOtherOnlineApplyCharge);

	parCashDTType->GetValue(m_nCashDTType);
	parCashDTWon->GetValue(m_bCashDTWon);
	parCashDTFee->GetValue(m_strCashDTFee);
	parMyCallDTType->GetValue(m_nMyCallDTType);
	parMyCallDTWon->GetValue(m_bMyCallDTWon);
	parMyCallDTFee->GetValue(m_strMyCallDTFee);
	parOtherCallDTType->GetValue(m_nOtherCallDTType);
	parOtherCallDTWon->GetValue(m_bOtherCallDTWon);
	parOtherCallDTFee->GetValue(m_strOtherCallDTFee);

	ApplyDT();

	m_btnMyCallCashWon.SetChecked(!m_bMyCallCashWon);
	m_btnOtherCallCashWon.SetChecked(!m_bOtherCallCashWon);
	m_btnMyCallCreditWon.SetChecked(!m_bMyCallCreditWon);
	m_btnOtherCallCreditWon.SetChecked(!m_bOtherCallCreditWon);
	m_btnMyCallOnlineWon.SetChecked(!m_bMyCallOnlineWon);
	m_btnOtherCallOnlineWon.SetChecked(!m_bOtherCallOnlineWon);

	OnBnClickedMyCallCashWonBtn();
	OnBnClickedOtherCallCashWonBtn();
	OnBnClickedMyCallCreditWonBtn();
	OnBnClickedMyCallOnlineWonBtn();
	OnBnClickedOtherCallCreditWonBtn();
	OnBnClickedOtherCallOnlineWonBtn();
 
	m_edtMyCallCashFee.SetWindowText(LF->GetMyNumberFormat(m_nMyCallCash));
	m_edtOtherCallCashFee.SetWindowText(LF->GetMyNumberFormat(m_nOtherCallCash));
	m_edtMyCallCreditFee.SetWindowText(LF->GetMyNumberFormat(m_nMyCallCredit));
	m_edtOtherCallCreditFee.SetWindowText(LF->GetMyNumberFormat(m_nOtherCallCredit));
	m_edtMyCallOnlineFee.SetWindowText(LF->GetMyNumberFormat(m_nMyCallOnline));
	m_edtOtherCallOnlineFee.SetWindowText(LF->GetMyNumberFormat(m_nOtherCallOnline));
	
	if(m_nFixedDepositIncomeOnline > 0)
	{
		char buffer [10];
		m_lstReport2.InsertItem(0, "2");
		m_lstReport2.SetItemText(0, 1, "지입금 온라인입금");
		m_lstReport2.SetItemText(0, 2, ::itoa(m_nFixedDepositIncomeOnline, buffer, 10));
	}

	ST_RIDER_REPORT st;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTNo", st.nTNo);
		pRs.GetFieldValue("dt1", st.dt1);
		pRs.GetFieldValue("nChargeSum", st.nChargeSum);
		pRs.GetFieldValue("nChargeTrans", st.nChargeTrans);
		pRs.GetFieldValue("nCouponCharge", st.nCouponCharge);
		pRs.GetFieldValue("nShareCode1", st.nShareCode1);
		pRs.GetFieldValue("nRiderShareCode1", st.nRiderShareCode1);
		pRs.GetFieldValue("nPayType", st.nPayType);
		pRs.GetFieldValue("bGiveChargeToRider", st.bGiveChargeToRider);

		st.nOrderType = GetOrderType(st.nShareCode1, st.nRiderShareCode1, st.nPayType);

		m_map[i] = st;

		pRs.MoveNext();
	}

}

void CRiderReportDlg::InitCharge()
{
	RIDER_REPORT_MAP1::iterator it;

	m_nMyCallGiveToRiderCount = 0; 
	m_nMyCallGiveToRiderCharge = 0;
	m_nOtherCallGiveToRiderCount = 0;
	m_nOtherCallGiveToRiderCharge = 0;
	m_nCouponCount = 0;

	long nMyCallAllCashCount = 0;
	long nMyCallAllCashCharge = 0;
	long nMyCallApplyCashCount = 0;
	long nMyCallApplyCashCharge = 0;

	long nOtherCallAllCashCount = 0;
	long nOtherCallAllCashCharge = 0;
	long nOtherCallApplyCashCount = 0;
	long nOtherCallApplyCashCharge = 0;

	long nMyCallAllCreditCount = 0;
	long nMyCallAllCreditCharge = 0;
	long nMyCallApplyCreditCount = 0;
	long nMyCallApplyCreditCharge = 0;
	long nMyCallNotApplyCreditCount = 0;
	long nMyCallNotApplyCreditCharge = 0;

	long nMyCallAllOnlineCount = 0;
	long nMyCallAllOnlineCharge = 0;
	long nMyCallApplyOnlineCount = 0;
	long nMyCallApplyOnlineCharge = 0;
	long nMyCallNotApplyOnlineCount = 0;
	long nMyCallNotApplyOnlineCharge = 0;

	long nOtherCallAllCreditCount = 0;
	long nOtherCallAllCreditCharge = 0;
	long nOtherCallApplyCreditCount = 0;
	long nOtherCallApplyCreditCharge = 0;
	long nOtherCallNotApplyCreditCount = 0;
	long nOtherCallNotApplyCreditCharge = 0;

	long nOtherCallAllOnlineCount = 0;
	long nOtherCallAllOnlineCharge = 0;
	long nOtherCallApplyOnlineCount = 0;
	long nOtherCallApplyOnlineCharge = 0;
	long nOtherCallNotApplyOnlineCount = 0;
	long nOtherCallNotApplyOnlineCharge = 0;

	long nTransCount = 0;
	long nTransCharge = 0;
	long nCouponCharge = 0;

	for(it = m_map.begin(); it != m_map.end(); it++)
	{
		if(it->second.nCouponCharge > 0)
		{
			m_nCouponCount++;
			nCouponCharge += it->second.nCouponCharge;
		}

		switch(it->second.nOrderType)
		{  
		case MY_CALL_CASH:
			{			
				nMyCallAllCashCount++;
				nMyCallAllCashCharge += it->second.nChargeSum;

				if(it->second.nChargeSum >= m_nMyCashApplyCharge)
				{
					nMyCallApplyCashCount++;
					nMyCallApplyCashCharge += it->second.nChargeSum;
				}
				break;
			}
		case OTHER_CALL_CASH:
			{
				nOtherCallAllCashCount++;
				nOtherCallAllCashCharge += it->second.nChargeSum;

				if(it->second.nChargeSum >= m_nOtherCashApplyCharge)
				{
					nOtherCallApplyCashCount++;
					nOtherCallApplyCashCharge += it->second.nChargeSum;
				}
				break;
			}
		case MY_CALL_CREDIT:
			{
                nMyCallAllCreditCount++;
				nMyCallAllCreditCharge += it->second.nChargeSum;

				if(it->second.nChargeTrans > 0)
				{
					nTransCount++;
					nTransCharge += it->second.nChargeTrans;
				}

				if(it->second.bGiveChargeToRider == 1) //이미 이체가 된 항목
				{
					m_nMyCallGiveToRiderCount++;
					m_nMyCallGiveToRiderCharge += it->second.nChargeSum;
				}
				else if(it->second.nChargeSum >= m_nMyCreditApplyCharge)
				{
					nMyCallApplyCreditCount++;
					nMyCallApplyCreditCharge += it->second.nChargeSum;
				}
				else
				{
					nMyCallNotApplyCreditCount++;
					nMyCallNotApplyCreditCharge += it->second.nChargeSum;
				}
				break;
			}
		case MY_CALL_ONLINE:
			{
				nMyCallAllOnlineCount++;
				nMyCallAllOnlineCharge += it->second.nChargeSum;

				if(it->second.nChargeTrans > 0)
				{
					nTransCount++;
					nTransCharge += it->second.nChargeTrans;
				}

				if(it->second.bGiveChargeToRider == 1) //이미 이체가 된 항목
				{
					m_nMyCallGiveToRiderCount++;
					m_nMyCallGiveToRiderCharge += it->second.nChargeSum;
				}
				else if(it->second.nChargeSum >= m_nMyOnlineApplyCharge)
				{
					nMyCallApplyOnlineCount++;
					nMyCallApplyOnlineCharge += it->second.nChargeSum;
				}
				else
				{
					nMyCallNotApplyOnlineCount++;
					nMyCallNotApplyOnlineCharge += it->second.nChargeSum;
				}
				break;
			}
		case OTHER_CALL_CREDIT:
			{
				nOtherCallAllCreditCount++;
				nOtherCallAllCreditCharge += it->second.nChargeSum;

				if(it->second.nChargeTrans > 0)
				{
					nTransCount++;
					nTransCharge += it->second.nChargeTrans;
				}

				if(it->second.bGiveChargeToRider == 1) //이미 이체가 된 항목
				{
					m_nOtherCallGiveToRiderCount++;
					m_nOtherCallGiveToRiderCharge += it->second.nChargeSum;
				}
				else if(it->second.nChargeSum >= m_nOtherCreditApplyCharge)
				{
					nOtherCallApplyCreditCount++;
					nOtherCallApplyCreditCharge += it->second.nChargeSum;
				}
				else
				{
					nOtherCallNotApplyCreditCount++;
					nOtherCallNotApplyCreditCharge += it->second.nChargeSum;
				}
				break;
			}
		case OTHER_CALL_ONLINE:
			{
				nOtherCallAllOnlineCount++;
				nOtherCallAllOnlineCharge += it->second.nChargeSum;

				if(it->second.nChargeTrans > 0)
				{
					nTransCount++;
					nTransCharge += it->second.nChargeTrans;
				}

				if(it->second.bGiveChargeToRider == 1) //이미 이체가 된 항목
				{
					m_nOtherCallGiveToRiderCount++;
					m_nOtherCallGiveToRiderCharge += it->second.nChargeSum;
				}
				else if(it->second.nChargeSum >= m_nOtherOnlineApplyCharge)
				{
					nOtherCallApplyOnlineCount++;
					nOtherCallApplyOnlineCharge += it->second.nChargeSum;
				}
				else
				{
					nOtherCallNotApplyOnlineCount++;
					nOtherCallNotApplyOnlineCharge += it->second.nChargeSum;
				}
				break;
			}
		}
	}

	SetTextStc(); 

	m_btnMyCallCashWon.SetCheck(!m_bMyCallCashWon);
	m_btnOtherCallCashWon.SetCheck(!m_bOtherCallCashWon);
	m_btnMyCallCreditWon.SetCheck(!m_bMyCallCreditWon);
	m_btnOtherCallCreditWon.SetCheck(!m_bOtherCallCreditWon);
	m_btnMyCallOnlineWon.SetCheck(!m_bMyCallOnlineWon);
	m_btnOtherCallOnlineWon.SetCheck(!m_bOtherCallOnlineWon);

	m_edtMyCallAllCashCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCount));
	m_edtMyCallAllCashCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCharge));
	m_edtMyCallApplyCashCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCashCount));
	m_edtMyCallApplyCashCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCashCharge));

	m_edtOtherCallAllCashCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCashCount));
	m_edtOtherCallAllCashCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCashCharge));
	m_edtOtherCallApplyCashCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCashCount));
	m_edtOtherCallApplyCashCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCashCharge));

	m_edtMyCallAllCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCount));
	m_edtMyCallAllCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCharge));
	m_edtMyCallApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCreditCount));
	m_edtMyCallApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCreditCharge));
	m_edtMyCallNotApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCount));
	m_edtMyCallNotApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCharge));

	m_edtMyCallAllOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllOnlineCount));
	m_edtMyCallAllOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllOnlineCharge));
	m_edtMyCallApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyOnlineCount));
	m_edtMyCallApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyOnlineCharge));
	m_edtMyCallNotApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyOnlineCount));
	m_edtMyCallNotApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyOnlineCharge));

	m_edtOtherCallAllCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCount));
	m_edtOtherCallAllCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCharge));
	m_edtOtherCallApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCreditCount));
	m_edtOtherCallApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCreditCharge));
	m_edtOtherCallNotApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCount));
	m_edtOtherCallNotApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCharge));

	m_edtOtherCallAllOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllOnlineCount));
	m_edtOtherCallAllOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllOnlineCharge));
	m_edtOtherCallApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyOnlineCount));
	m_edtOtherCallApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyOnlineCharge));
	m_edtOtherCallNotApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyOnlineCount));
	m_edtOtherCallNotApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyOnlineCharge));

	m_edtCashCallAllCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCount + nOtherCallAllCashCount));
	m_edtCashCallAllCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCharge + nOtherCallAllCashCharge));

	m_edtMyCallAllCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCount + nMyCallAllOnlineCount));
	m_edtMyCallAllCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCharge + nMyCallAllOnlineCharge));

	m_edtMyCallNotApplyCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCount + nMyCallNotApplyOnlineCount));
	m_edtMyCallNotApplyCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCharge + nMyCallNotApplyOnlineCharge));
 
	m_edtOtherCallAllCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCount + nOtherCallAllOnlineCount));
	m_edtOtherCallAllCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCharge + nOtherCallAllOnlineCharge));
	m_edtOtherCallNotApplyCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCount + nOtherCallNotApplyOnlineCount));
	m_edtOtherCallNotApplyCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCharge + nOtherCallNotApplyOnlineCharge));

	m_edtTransCount.SetWindowText(LF->GetMyNumberFormat(nTransCount));
	m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(nTransCharge));

	m_edtCoupon.SetWindowText(LF->GetMyNumberFormat(nCouponCharge)); 
	m_edtCouponPlus.SetWindowText("1");
	m_edtCouponTotal.SetWindowText(LF->GetMyNumberFormat(nCouponCharge));

	//Invalidate(TRUE);
}

void CRiderReportDlg::RefreshCharge()
{
	long nTotal = 0;
	long nTakeTotal = 0;
	long nGiveTotal = 0;

	nTakeTotal += GetEditTextByLong(&m_edtFixedDeposit); // 지입금

	if(GetEditTextByLong(&m_edtMyCallCashFee) != 0)
	{
		if(m_btnMyCallCashWon.GetChecked() == BST_CHECKED) 
		{
			m_edtMyCallCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(GetEditTextByLong(&m_edtMyCallApplyCashCharge) * GetEditTextByLong(&m_edtMyCallCashFee) * 0.01));
		}
		else
		{
			m_edtMyCallCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(GetEditTextByLong(&m_edtMyCallApplyCashCount) * GetEditTextByLong(&m_edtMyCallCashFee)));
		}
	}
	else
		m_edtMyCallCashFeeTotal.SetWindowText("0");

	nTakeTotal += GetEditTextByLong(&m_edtMyCallCashFeeTotal); //자사현금수수료;

	long nOtherCash = 0;

	if(GetEditTextByLong(&m_edtOtherCallCashFee) != 0)
	{
		if(m_btnOtherCallCashWon.GetChecked() == BST_CHECKED) 
		{
			nOtherCash = GetEditTextByLong(&m_edtOtherCallApplyCashCharge) * GetEditTextByLong(&m_edtOtherCallCashFee) * 0.01;
		}
		else
		{
            nOtherCash = GetEditTextByLong(&m_edtOtherCallApplyCashCount) * GetEditTextByLong(&m_edtOtherCallCashFee);			
		}
	}

	m_edtOtherCallCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherCash));
	nTakeTotal += GetEditTextByLong(&m_edtOtherCallCashFeeTotal); //타사현금수수료;

	m_edtCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(GetEditTextByLong(&m_edtMyCallCashFeeTotal) + GetEditTextByLong(&m_edtOtherCallCashFeeTotal)));

	nTakeTotal += GetReportCharge(&m_lstReport); //적요금액
	m_edtTakeEtcTotal.SetWindowText(LF->GetMyNumberFormat(GetReportCharge(&m_lstReport)));

	//전월 미수금 패스

	nGiveTotal += GetEditTextByLong(&m_edtReceiveCharge);// 섭입금

	long nApplyCreditCount =	GetEditTextByLong(&m_edtMyCallApplyCreditCount);
	long nApplyCreditCharge =	GetEditTextByLong(&m_edtMyCallApplyCreditCharge);
	long nApplyOnlineCount =	GetEditTextByLong(&m_edtMyCallApplyOnlineCount);
	long nApplyOnlineCharge =	GetEditTextByLong(&m_edtMyCallApplyOnlineCharge);

    if(GetEditTextByLong(&m_edtMyCallCreditFee) != 0)
	{
		long nPer = nApplyCreditCharge * GetEditTextByLong(&m_edtMyCallCreditFee) * 0.01;
	
		if(m_btnMyCallCreditWon.GetChecked() == BST_CHECKED) 
		{			
			m_edtMyCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge - nPer));
		}
		else
		{
			m_edtMyCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge - (nApplyCreditCount * GetEditTextByLong(&m_edtMyCallCreditFee))));
		}
	}
	else
		m_edtMyCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge));

	nGiveTotal += GetEditTextByLong(&m_edtMyCallCreditFeeTotal);// 자사신용

	if(GetEditTextByLong(&m_edtMyCallOnlineFee) != 0)
	{
		long nPer = nApplyOnlineCharge * GetEditTextByLong(&m_edtMyCallOnlineFee) * 0.01;

		if(m_btnMyCallOnlineWon.GetChecked() == BST_CHECKED) 
		{			
			m_edtMyCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge - nPer));
		}
		else
		{
			m_edtMyCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge - (nApplyOnlineCount * GetEditTextByLong(&m_edtMyCallOnlineFee))));
		}
	}
	else
		m_edtMyCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge));

	nGiveTotal += GetEditTextByLong(&m_edtMyCallOnlineFeeTotal);// 자사송금
	nGiveTotal += GetEditTextByLong(&m_edtMyCallNotApplyCreditOnlineCharge); //미적용

	m_edtMyCallCreditOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(GetEditTextByLong(&m_edtMyCallCreditFeeTotal) + GetEditTextByLong(&m_edtMyCallOnlineFeeTotal) + GetEditTextByLong(&m_edtMyCallNotApplyCreditOnlineCharge)));

	nApplyCreditCount = GetEditTextByLong(&m_edtOtherCallApplyCreditCount);
	nApplyCreditCharge = GetEditTextByLong(&m_edtOtherCallApplyCreditCharge);
	nApplyOnlineCount = GetEditTextByLong(&m_edtOtherCallApplyOnlineCount);
	nApplyOnlineCharge = GetEditTextByLong(&m_edtOtherCallApplyOnlineCharge);

	if(GetEditTextByLong(&m_edtOtherCallCreditFee) != 0)
	{
		long nPer = nApplyCreditCharge * GetEditTextByLong(&m_edtOtherCallCreditFee) * 0.01;

		if(m_btnOtherCallCreditWon.GetChecked() == BST_CHECKED) 
		{			
			m_edtOtherCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge - nPer));
		}
		else
		{
			m_edtOtherCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge - (nApplyCreditCount * GetEditTextByLong(&m_edtOtherCallCreditFee))));
		}
	}
	else
		m_edtOtherCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyCreditCharge));

	nGiveTotal += GetEditTextByLong(&m_edtOtherCallCreditFeeTotal);// 타사신용

	if(GetEditTextByLong(&m_edtOtherCallOnlineFee) != 0)
	{
		long nPer = nApplyOnlineCharge * GetEditTextByLong(&m_edtMyCallOnlineFee) * 0.01;

		if(m_btnOtherCallOnlineWon.GetChecked() == BST_CHECKED) 
		{			
			m_edtOtherCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge - nPer));
		}
		else
		{
			m_edtOtherCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge - (nApplyOnlineCount * GetEditTextByLong(&m_edtOtherCallOnlineFee))));
		}
	}
	else
		m_edtOtherCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nApplyOnlineCharge));

	m_edtOtherCallCreditOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(GetEditTextByLong(&m_edtOtherCallCreditFeeTotal) + GetEditTextByLong(&m_edtOtherCallOnlineFeeTotal) + GetEditTextByLong(&m_edtOtherCallNotApplyCreditOnlineCharge)));

	nGiveTotal += GetEditTextByLong(&m_edtOtherCallOnlineFeeTotal);// 타사송금
	nGiveTotal += GetEditTextByLong(&m_edtOtherCallNotApplyCreditOnlineCharge);// 미적용

	nGiveTotal += GetReportCharge(&m_lstReport2); //적요금액
	m_edtGiveEtcTotal.SetWindowText(LF->GetMyNumberFormat(GetReportCharge(&m_lstReport2)));

	nGiveTotal += GetEditTextByLong(&m_edtTransCharge); //탁송
	nGiveTotal += GetEditTextByLong(&m_edtCouponTotal); //탁송

	long nWonChun = 0 ;

	if(m_chkCashMyCallDeductingTax.GetCheck() == BST_CHECKED ||
		m_chkCashOtherCallDeductingTax.GetCheck() == BST_CHECKED)
	{
		if(m_btnCashDeductingTaxFee.GetChecked() == BST_CHECKED)//퍼센트
		{
			CString str; m_edtCashDeductingTaxFee.GetWindowText(str);
			float nPer = atof(str);

			if(m_chkCashMyCallDeductingTax.GetCheck() == BST_CHECKED)
			{
				nWonChun += nPer * GetEditTextByLong(&m_edtMyCallAllCashCharge) * 0.01;
			}            

			if(m_chkCashOtherCallDeductingTax.GetCheck() == BST_CHECKED)
			{
				nWonChun += nPer * GetEditTextByLong(&m_edtOtherCallAllCashCharge) * 0.01;
			}            
		}
		else
		{
			nWonChun = GetEditTextByLong(&m_edtCashDeductingTaxFee);
		}
	}

	nTakeTotal += nWonChun;

	m_edtCashDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nWonChun)); //현금원천징수

	long nMyWonChun = 0;

	if(m_chkMyCallBefore.GetCheck() == BST_CHECKED)
	{
		if(m_btnBeforeMyCallCreditOnlineDeductingTaxWon.GetChecked() == BST_CHECKED)//퍼센트
		{
			CString str; m_edtBeforeMyCallCreditOnlineDeductingTaxFee.GetWindowText(str);
			float nPer = atof(str);

			nMyWonChun += nPer * GetEditTextByLong(&m_edtMyCallAllCreditOnlineCharge) * 0.01;
		}
		else
			nMyWonChun = GetEditTextByLong(&m_edtBeforeMyCallCreditOnlineDeductingTaxFee);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyWonChun));
	}
	else
	{
		if(m_btnAfterMyCallCreditOnlineDeductingTaxWon.GetChecked() == BST_CHECKED)//퍼센트
		{
			CString str; m_edtAfterMyCallCreditOnlineDeductingTaxFee.GetWindowText(str);
			float nPer = atof(str);

			nMyWonChun += GetEditTextByLong(&m_edtMyCallCreditOnlineFeeTotal) * nPer * 0.01;
		}
		else
			nMyWonChun = GetEditTextByLong(&m_edtAfterMyCallCreditOnlineDeductingTaxFee);

		m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyWonChun));
	}

	nTakeTotal += nMyWonChun; // 자사신용송금 원천징수

	long nOtherWonChun = 0;

	if(m_chkOtherCallBefore.GetCheck() == BST_CHECKED)
	{
		if(m_btnBeforeOtherCallCreditOnlineDeductingWon.GetChecked() == BST_CHECKED)//퍼센트
		{
			CString str; m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.GetWindowText(str);
			float nPer = atof(str);

			nOtherWonChun += nPer * GetEditTextByLong(&m_edtOtherCallAllCreditOnlineCharge) * 0.01;
		}
		else
			nOtherWonChun = GetEditTextByLong(&m_edtBeforeOtherCallCreditOnlineDeductingTaxFee);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherWonChun));
	}
	else
	{
		if(m_btnAfterOtherCallCreditOnlineDeductingWon.GetChecked() == BST_CHECKED)//퍼센트
		{
			CString str; m_edtAfterOtherCallCreditOnlineDeductingTaxFee.GetWindowText(str);
			float nPer = atof(str);

			nOtherWonChun += GetEditTextByLong(&m_edtOtherCallCreditOnlineFeeTotal) * nPer * 0.01;
		}
		else
			nOtherWonChun = GetEditTextByLong(&m_edtAfterOtherCallCreditOnlineDeductingTaxFee);

		m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherWonChun));
	}

	nTakeTotal += nOtherWonChun; // 타사신용송금 원천징수


	m_edtTakeTotal.SetWindowText(LF->GetMyNumberFormat(nTakeTotal));
	//nGiveTotal += GetEditTextByLong(&m_edtMyCallNotApplyCreditOnlineCharge); // 적용되지않은 자사신용송금
	//nGiveTotal += GetEditTextByLong(&m_edtOtherCallNotApplyCreditOnlineCharge); // 적용되지않은 타사신용송금

	m_edtTakeTotal1.SetWindowText(LF->GetMyNumberFormat(nTakeTotal));
	m_edtGiveTotal.SetWindowText(LF->GetMyNumberFormat(nGiveTotal));
	m_edtGiveTotal1.SetWindowText(LF->GetMyNumberFormat(nGiveTotal)); 

	m_edtTotal.SetWindowText(LF->GetMyNumberFormat(nTakeTotal - nGiveTotal));
}

long CRiderReportDlg::GetReportCharge(CXTPListCtrl2 *pList)
{
	long nCharge = 0;

	for(int i=0; i<MAX_ETC_COUNT; i++)
	{
		CString str = pList->GetItemText(i, 2);
		str.Replace(",", "");
		nCharge += _ttoi(str);
	}

	//if(pList->GetSafeHwnd() == m_lstReport.GetSafeHwnd())
	//	m_edtTakeEtcTotal.SetWindowText(LF->GetMyNumberFormat(nCharge));
	//else
	//	m_edtGiveEtcTotal.SetWindowText(LF->GetMyNumberFormat(nCharge));

	return nCharge;

}

BOOL CRiderReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//CenterWindow(); 

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);

	CString str;
	str.Format("(%d)%s %s", m_nRNo, m_strRName, "기사님");
	//this->SetWindowText(str);
	m_stcRider.SetWindowText(str);

	m_stcTakeGroup.SetFont(m_Font, TRUE);
	m_stcGiveGroup.SetFont(m_Font, TRUE);


	m_lstReport.AddColumn(new CXTPGridColumn(0,_T(""), 0, FALSE));
	CXTPGridColumn * pCol0 = m_lstReport.AddColumn(new CXTPGridColumn(1,_T("적 요"), 150, TRUE));
	CXTPGridColumn * pCol1 = m_lstReport.AddColumn(new CXTPGridColumn(2,_T("금 액"), 150, TRUE));

	m_lstReport2.AddColumn(new CXTPGridColumn(0,_T(""), 0, FALSE));
	CXTPGridColumn * pCol2 = m_lstReport2.AddColumn(new CXTPGridColumn(1,_T("적 요"), 150, TRUE));
	CXTPGridColumn * pCol3 = m_lstReport2.AddColumn(new CXTPGridColumn(2,_T("금 액"), 150, TRUE));

	pCol0->SetAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_CENTER);
	pCol3->SetAlignment(DT_CENTER);

	pCol0->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol1->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol3->GetEditOptions()->m_bAllowEdit = TRUE;

	InitReport(&m_lstReport);
	InitReport(&m_lstReport2);

	m_bInitList = TRUE;

	m_edtFixedDeposit.SetMyFont("돋움체", 14, FW_BOLD);
	m_edtFixedDeposit.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");

	m_edtMyCallAllCashCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCashCount.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtMyCallAllCashCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCashCharge.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtMyCallApplyCashCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyCashCount.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtMyCallApplyCashCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyCashCharge.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtMyCallCashFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallCashFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtMyCallCashFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallCashFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtOtherCallAllCashCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCashCount.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtOtherCallAllCashCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCashCharge.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtOtherCallApplyCashCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyCashCount.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtOtherCallApplyCashCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyCashCharge.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtOtherCallCashFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallCashFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtOtherCallCashFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallCashFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtCashCallAllCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCashCallAllCount.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtCashCallAllCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCashCallAllCharge.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtCashFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCashFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtTakeEtcTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTakeEtcTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtLastMonth.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtLastMonth.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtCashDeductingTaxFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCashDeductingTaxFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtCashDeductingTaxFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCashDeductingTaxFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtTakeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTakeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtTakeTotal1.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTakeTotal1.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");
	m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 255), "");
	m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");

	m_edtReceiveCharge.SetMyFont("돋움체", 14, FW_BOLD);
	m_edtReceiveCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallAllCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallAllCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallNotApplyCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallNotApplyCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallApplyCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallApplyCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallCreditFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallCreditFee.SetUserOption(RGB(255, 0, 0), RGB(255, 240, 240), "");
	m_edtMyCallCreditFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallCreditFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtMyCallAllOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallAllOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallNotApplyOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallNotApplyOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallApplyOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallApplyOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallApplyOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallOnlineFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallOnlineFee.SetUserOption(RGB(255, 0, 0), RGB(255, 240, 240), "");
	m_edtMyCallOnlineFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallOnlineFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtMyCallAllCreditOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCreditOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallAllCreditOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallAllCreditOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtMyCallNotApplyCreditOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyCreditOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtMyCallNotApplyCreditOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallNotApplyCreditOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtOtherCallAllCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallAllCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallNotApplyCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallNotApplyCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallApplyCreditCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyCreditCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallApplyCreditCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyCreditCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallCreditFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallCreditFee.SetUserOption(RGB(255, 0, 0), RGB(255, 240, 240), "");
	m_edtOtherCallCreditFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallCreditFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtOtherCallAllOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallAllOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallNotApplyOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallNotApplyOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallApplyOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallApplyOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallApplyOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallOnlineFee.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallOnlineFee.SetUserOption(RGB(255, 0, 0), RGB(255, 240, 240), "");
	m_edtOtherCallOnlineFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallOnlineFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtOtherCallAllCreditOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCreditOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallAllCreditOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallAllCreditOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtOtherCallNotApplyCreditOnlineCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyCreditOnlineCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallNotApplyCreditOnlineCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallNotApplyCreditOnlineCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtMyCallCreditOnlineFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtMyCallCreditOnlineFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtOtherCallCreditOnlineFeeTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtOtherCallCreditOnlineFeeTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtTakeTotal1.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTakeTotal1.SetUserOption(RGB(0, 0, 255), RGB(220, 220, 255), "");

	m_edtGiveEtcTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtGiveEtcTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtTransCount.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTransCount.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtTransCharge.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtTransCharge.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtCoupon.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCoupon.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtCouponPlus.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCouponPlus.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtCouponTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtCouponTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtGiveTotal.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtGiveTotal.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");
	m_edtGiveTotal1.SetMyFont("돋움체", 12, FW_BOLD);
	m_edtGiveTotal1.SetUserOption(RGB(255, 0, 0), RGB(255, 220, 220), "");

	m_edtTotal.SetMyFont("돋움체", 14, FW_BOLD);
	m_edtTotal.SetUserOption(RGB(0, 255, 0), RGB(230, 255, 230), "");

	m_stcMyGiveCharge.SetTextColor(RGB(255, 0, 0));
	m_stcOtherGiveCharge.SetTextColor(RGB(255, 0, 0));

	if(m_bComplete) //정산완료
	{
		CallCompleteReport();
		MakeMsg();
		return TRUE;
	}
	else
		OnBnClickedOpenBtn();

	OnBnClickedRefreshBtn();
	m_edtFixedDeposit.SetWindowText(LF->GetMyNumberFormat(m_nFixedDepositCharge)); // 반드시 조회버튼 호출 뒤로


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderReportDlg::InitReport(CXTPListCtrl2 *pList)
{
	pList->GetReportHeader()->AllowColumnRemove(FALSE);
	pList->GetReportHeader()->AllowColumnResize(TRUE);
	pList->GetReportHeader()->AllowColumnSort(FALSE);
	pList->GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	pList->FocusSubItems(TRUE);
	pList->SetGridColor(RGB(180, 180, 200));

	pList->SetPaintManager(new CRiderPaintManager);

	pList->GetPaintManager()->m_strNoItems = "";
    pList->AllowEdit(TRUE);
	pList->Populate();

    for(int i=0; i<MAX_ETC_COUNT; i++)
	{
		if(pList->GetSafeHwnd() == m_lstReport.GetSafeHwnd())
			pList->InsertItem(i, "1");
		else
			pList->InsertItem(i, "2");
	}

	pList->Populate();
}

void CRiderReportDlg::OnBnClickedOpenBtn()
{

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_take_etc_1");
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
    
	if(!pRs.Execute(&pCmd)) return;

	CString sEtcSum;
	CString sEtcChargeSum;

	pRs.GetFieldValue("sEtc", sEtcSum);
	pRs.GetFieldValue("sEtcCharge", sEtcChargeSum);

	RefreshEtcList(&m_lstReport, sEtcSum, sEtcChargeSum);
	RefreshEtcListByRiderCredit();
	RefreshCharge();
}

void CRiderReportDlg::RefreshEtcListByRiderCredit()
{
	m_mapCredit.clear();

	COleDateTime dtFrom; m_FromDT.GetTime(dtFrom);
	COleDateTime dtTo; m_ToDT.GetTime(dtTo);

	char buffer[20];
	long nItem = GetReportEmtpyRow();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb , "select_rider_credit_by_report_1");

	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(dtFrom);
	pCmd.AddParameter(dtTo);

	if(!pRs.Execute(&pCmd)) return;  

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_CREDIT st;

		pRs.GetFieldValue("nIndex", st.nIndex);
		pRs.GetFieldValue("sMemo", st.strMemo);
		pRs.GetFieldValue("nCharge", st.nCharge);

		m_lstReport.SetItemText(nItem, 0, "1");
		m_lstReport.SetItemText(nItem, 1, st.strMemo);
		m_lstReport.SetItemText(nItem, 2, itoa(st.nCharge, buffer, 10));
		m_lstReport.SetItemLong(nItem++, st.nIndex);


		//((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(i)->GetItem(1))->SetValue(st.sMemo);
		//((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(i)->GetItem(1))->SetCaption(st.sMemo);
		//((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(i)->GetItem(2))->SetValue(itoa(st.nCharge, buffer, 10));
		//((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(i)->GetItem(2))->SetCaption(itoa(st.nCharge, buffer, 10));


		m_mapCredit[st.nIndex] = st;
		pRs.MoveNext();
	}


	m_lstReport.Populate();

	//m_lstReport.Populate();
}

long CRiderReportDlg::GetReportEmtpyRow()
{
	for(int i=0; i<MAX_ETC_COUNT; i++)
	{
		CString sText = m_lstReport.GetItemText(i, 1);
		
		if(sText == "")
			return i;
	}
	return 0;
}

void CRiderReportDlg::RefreshEtcList(CXTPListCtrl2 *pList, CString sEtcSum, CString sEtcChargeSum)
{
	pList->DeleteAllItems();

	long nStartEtcPos = 0;
	long nDestEtcPos = 0;

	long nStartEtcChargePos = 0;
	long nDestEtcChargePos = 0;

	long nItem = 0;

	while(1)
	{
		nDestEtcPos = sEtcSum.Find(";", nStartEtcPos);
		nDestEtcChargePos = sEtcChargeSum.Find(";", nStartEtcChargePos);

		if(nDestEtcPos == -1) break;

		CString sEtc = sEtcSum.Mid(nStartEtcPos, nDestEtcPos - nStartEtcPos);
		CString sEtcCharge = sEtcChargeSum.Mid(nStartEtcChargePos, nDestEtcChargePos - nStartEtcChargePos);

		if(m_lstReport.GetSafeHwnd() == pList->GetSafeHwnd())
			pList->InsertItem(nItem, "1");
		else
			pList->InsertItem(nItem, "2");

		pList->SetItemText(nItem, 1, sEtc);
		pList->SetItemText(nItem, 2, sEtcCharge);

		nItem++;

		nStartEtcPos = nDestEtcPos + 1;
		nStartEtcChargePos = nDestEtcChargePos + 1;
	}


	for(int i=nItem; i<MAX_ETC_COUNT; i++)
		pList->InsertItem(i, "");

	pList->Populate();
}

void CRiderReportDlg::OnBnClickedOpenBtn2()
{	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_give_etc");

	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return;

	CString sEtcSum;
	CString sEtcChargeSum;

	pRs.GetFieldValue("sEtc", sEtcSum);
	pRs.GetFieldValue("sEtcCharge", sEtcChargeSum);

	RefreshEtcList(&m_lstReport2, sEtcSum, sEtcChargeSum);
	RefreshCharge();
}


void CRiderReportDlg::GetReportEtc(CXTPListCtrl2 *pList, CString &sEtc, CString &sEtcCharge)
{
	CString sEtc1 = "";
	CString sEtcCharge1 = "";

	for(int i=0; i<MAX_ETC_COUNT; i++)
	{
		CString sEtc2 = pList->GetItemText(i, 1) ;
		CString sEtcCharge2 = pList->GetItemText(i, 2);

		if(sEtc2 == "")
			continue;

		if(sEtcCharge2 == "") sEtcCharge2 = "0";

		sEtc1 += sEtc2 + ";";
		sEtcCharge1 += sEtcCharge2 + ";";
	}

	sEtc = sEtc1;
	sEtcCharge = sEtcCharge1;
}

void CRiderReportDlg::SaveEtcList(CXTPListCtrl2 *pList)
{
	CString sEtcSum = "";
	CString sEtcChargeSum = "";

	GetReportEtc(pList, sEtcSum, sEtcChargeSum);

	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_etc");

	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, sEtcSum .GetLength(), sEtcSum );
	pCmd.AddParameter(typeString, typeInput, sEtcChargeSum.GetLength(), sEtcChargeSum);

	if(m_lstReport.GetSafeHwnd() == pList->GetSafeHwnd())
		pCmd.AddParameter(1);
	else
		pCmd.AddParameter(0);

	if(!pCmd.Execute()) {
		MessageBox("저장에 실패했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
	}
}



void CRiderReportDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetValue("");
	((CXTPGridRecordItemText*)m_lstReport.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetCaption("");
}

void CRiderReportDlg::OnReportItemClick2(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	((CXTPGridRecordItemText*)m_lstReport2.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetValue("");
	((CXTPGridRecordItemText*)m_lstReport2.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetCaption("");
}

void CRiderReportDlg::DeleteEtcList(CXTPListCtrl2 *pList)
{
	pList->DeleteAllItems();

	CMkCommand pCmd(m_pMkDb, "delete_rider_deposit_etc");

	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(m_lstReport.GetSafeHwnd() == pList->GetSafeHwnd())
		pCmd.AddParameter(1);
	else
		pCmd.AddParameter(0);

	for(int i=0; i<MAX_ETC_COUNT; i++)
		pList->InsertItem(i, "");

	pList->Populate();

}

void CRiderReportDlg::OnBnClickedDeleteBtn()
{
	DeleteEtcList(&m_lstReport);
	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedDeleteBtn2()
{
	DeleteEtcList(&m_lstReport2);
	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedRefreshOrderBtn()
{	
		if(m_pRiderReportOrderDlg != NULL)
	{
		delete m_pRiderReportOrderDlg;
		m_pRiderReportOrderDlg = NULL;
	}

	m_pRiderReportOrderDlg = new CRiderReportOrderDlg;
	m_pRiderReportOrderDlg->m_nRiderCompany = m_nRiderCompany;
	m_pRiderReportOrderDlg->m_nRNo = m_nRNo;
	m_pRiderReportOrderDlg->m_sRName = m_strRName;
	m_FromDT.GetTime(m_pRiderReportOrderDlg->m_dtFrom);
	m_ToDT.GetTime(m_pRiderReportOrderDlg->m_dtTo);

	m_pRiderReportOrderDlg->Create(CRiderReportOrderDlg::IDD);
	m_pRiderReportOrderDlg->ShowWindow(SW_SHOW);

	CRect mcRect, orRect, NewRect;
	GetWindowRect(mcRect);  
	//m_pRiderReportOrderDlg->GetClientRect(orRect);
	m_pRiderReportOrderDlg->GetWindowRect(orRect);

	NewRect.left = mcRect.left;
	NewRect.right = NewRect.left + orRect.Width();
	NewRect.bottom = mcRect.bottom;
	NewRect.top = NewRect.bottom - orRect.Height();

	m_pRiderReportOrderDlg->MoveWindow(NewRect);
}

long CRiderReportDlg::GetEditTextByLong(CFlatEdit2 *pEdit)
{
	CString str;
	pEdit->GetWindowText(str);
	str.Replace(",", "");

	return _ttoi(str);
}

void CRiderReportDlg::OnBnClickedCompleteBtn()
{
    ReportComplete(FALSE);
}

void CRiderReportDlg::ReportComplete(BOOL bPrint)
{
	COleDateTime dtStart; m_FromDT.GetTime(dtStart);
	COleDateTime dtEnd; m_ToDT.GetTime(dtEnd);

	CString strTakeEtc, strTakeEtcCharge, strGiveEtc, strGiveEtcCharge;
	GetReportEtc(&m_lstReport, strTakeEtc, strTakeEtcCharge);
	GetReportEtc(&m_lstReport2, strGiveEtc, strGiveEtcCharge);
 
	CMkCommand pCmd(m_pMkDb, "complete_rider_fixed_deposit_report_4");
	CMkCommand pCmd1(m_pMkDb, "complete_rider_fixed_deposit_report_7_left"); //두번에 나눠친다

	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_strRName);
	pCmd.AddParameter(dtStart);
	pCmd.AddParameter(dtEnd);
	pCmd.AddParameter(GetEditTextByLong(&m_edtFixedDeposit)); // 지입금
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCashCount));//자사현금
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCashCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyCashCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyCashCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallCashFee));
	pCmd.AddParameter(m_btnMyCallCashWon.GetChecked() ? 0 : 1);// 반대로
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallCashFeeTotal)); // 자사현금끝
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCashCount));//타사현금
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCashCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyCashCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyCashCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallCashFee));
	pCmd.AddParameter(m_btnOtherCallCashWon.GetChecked() ? 0 : 1);// 반대로
	pCmd.AddParameter(GetEditTextByLong(&m_edtOtherCallCashFeeTotal)); // 타사현금끝
	pCmd.AddParameter(GetEditTextByLong(&m_edtCashCallAllCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtCashCallAllCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtCashFeeTotal));
	pCmd.AddParameter(GetEditTextByLong(&m_edtLastMonth)); // 전어ㅜㄹ
	pCmd.AddParameter(strTakeEtc);
	pCmd.AddParameter(strTakeEtcCharge);
	pCmd.AddParameter(GetEditTextByLong(&m_edtTakeEtcTotal));

	long nCashDeductTaxType = 0;
	if(m_chkCashMyCallDeductingTax.GetCheck() == TRUE &&
		m_chkCashOtherCallDeductingTax.GetCheck() == TRUE)
		nCashDeductTaxType = 3;
	else if(m_chkCashMyCallDeductingTax.GetCheck() == TRUE)
		nCashDeductTaxType = 2;
	else if(m_chkCashOtherCallDeductingTax.GetCheck() == TRUE)
		nCashDeductTaxType = 1;
	else 
		nCashDeductTaxType = 0;

	pCmd.AddParameter(nCashDeductTaxType); //원천칭수 자사타사

	CString strDeductingTaxFee; m_edtCashDeductingTaxFee.GetWindowText(strDeductingTaxFee);
	 
	pCmd.AddParameter(strDeductingTaxFee);
	pCmd.AddParameter(m_btnCashDeductingTaxFee.GetChecked() ? 0 : 1);// 반대로
	pCmd.AddParameter(GetEditTextByLong(&m_edtCashDeductingTaxFeeTotal));
	pCmd.AddParameter(GetEditTextByLong(&m_edtTakeTotal1)); //받는부분 끝
	pCmd.AddParameter(GetEditTextByLong(&m_edtGiveTotal1)); //Log째문에 먼저넣음

	pCmd.AddParameter(GetEditTextByLong(&m_edtReceiveCharge)); // 줄금액 시작
	pCmd.AddParameter(m_chkMyCallBefore.GetCheck() ? 0 : 1); //자사원천 DC전후

	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCreditCount));//자사신용
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCreditCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyCreditCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyCreditCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyCreditCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyCreditCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallCreditFee));
	pCmd.AddParameter(m_btnMyCallCreditWon.GetChecked() ? 0 : 1);// 반대로
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallCreditFeeTotal)); // 자사신용끝

	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllOnlineCount));//자사송금
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllOnlineCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyOnlineCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyOnlineCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyOnlineCount));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallApplyOnlineCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallOnlineFee));
	pCmd.AddParameter(m_btnMyCallOnlineWon.GetChecked() ? 0 : 1);// 반대로
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallOnlineFeeTotal)); // 자사송금끝

	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCreditOnlineCount)); // 자사신용송금합계
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallAllCreditOnlineCharge));
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyCreditOnlineCount)); 
	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallNotApplyCreditOnlineCharge));

	pCmd.AddParameter(GetEditTextByLong(&m_edtMyCallCreditOnlineFeeTotal));
	
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bPrint);
	// 요기까지 한번치고

	if(!pCmd.Execute()) return;

	pCmd1.AddParameter(m_nID);

	m_edtBeforeMyCallCreditOnlineDeductingTaxFee.GetWindowText(strDeductingTaxFee);

	pCmd1.AddParameter(strDeductingTaxFee);
	pCmd1.AddParameter(m_btnBeforeMyCallCreditOnlineDeductingTaxWon.GetChecked() ? 0 : 1);
	pCmd1.AddParameter(GetEditTextByLong(&m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal));

	m_edtAfterMyCallCreditOnlineDeductingTaxFee.GetWindowText(strDeductingTaxFee);
	pCmd1.AddParameter(strDeductingTaxFee);
	pCmd1.AddParameter(m_btnAfterMyCallCreditOnlineDeductingTaxWon.GetChecked() ? 0 : 1);
	pCmd1.AddParameter(GetEditTextByLong(&m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal));

	pCmd1.AddParameter(m_chkOtherCallBefore.GetCheck() ? 0 : 1); //타사원천 DC전후

	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCreditCount));//타사신용
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCreditCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyCreditCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyCreditCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyCreditCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyCreditCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallCreditFee));
	pCmd1.AddParameter(m_btnOtherCallCreditWon.GetChecked() ? 0 : 1);// 반대로
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallCreditFeeTotal)); // 타사신용끝

	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllOnlineCount));//자사송금
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllOnlineCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyOnlineCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyOnlineCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyOnlineCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallApplyOnlineCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallOnlineFee));
	pCmd1.AddParameter(m_btnOtherCallCreditWon.GetChecked() ? 0 : 1);// 반대로
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallOnlineFeeTotal)); // 자사송금끝

	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCreditOnlineCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallAllCreditOnlineCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyCreditOnlineCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallNotApplyCreditOnlineCharge));

	pCmd1.AddParameter(GetEditTextByLong(&m_edtOtherCallCreditOnlineFeeTotal));

	m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.GetWindowText(strDeductingTaxFee);
	pCmd1.AddParameter(strDeductingTaxFee);
	pCmd1.AddParameter(m_btnBeforeOtherCallCreditOnlineDeductingWon.GetChecked() ? 0 : 1);// 반대로
	pCmd1.AddParameter(GetEditTextByLong(&m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal));

	m_edtAfterOtherCallCreditOnlineDeductingTaxFee.GetWindowText(strDeductingTaxFee);
	pCmd1.AddParameter(strDeductingTaxFee);
	pCmd1.AddParameter(m_btnAfterOtherCallCreditOnlineDeductingWon.GetChecked() ? 0 : 1);// 반대로
	pCmd1.AddParameter(GetEditTextByLong(&m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal));

	pCmd1.AddParameter(strGiveEtc);
	pCmd1.AddParameter(strGiveEtcCharge);
	pCmd1.AddParameter(GetEditTextByLong(&m_edtGiveEtcTotal));

	pCmd1.AddParameter(GetEditTextByLong(&m_edtTransCount));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtTransCharge));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtTotal));

	CString sMemo; m_edtMemo.GetWindowText(sMemo); 
	pCmd1.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);

	CString sRiderCredit = GetRiderCredit();
	pCmd1.AddParameter(typeString, typeInput, sRiderCredit.GetLength(), sRiderCredit);
	pCmd1.AddParameter(GetEditTextByLong(&m_edtCoupon));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtCouponPlus));
	pCmd1.AddParameter(GetEditTextByLong(&m_edtCouponTotal));
	pCmd1.AddParameter(m_nCouponCount);

	pCmd1.AddParameter(m_nMyCallGiveToRiderCount);
	pCmd1.AddParameter(m_nMyCallGiveToRiderCharge);
	pCmd1.AddParameter(m_nOtherCallGiveToRiderCount);
	pCmd1.AddParameter(m_nOtherCallGiveToRiderCharge);

	if(pCmd1.Execute())
	{ 
		if(!bPrint)
		{	
			m_bComplete = TRUE;
			//CString str = Print(FALSE) + " 경로로 저장 되었습니다.";
			//MessageBox(str, "확인", MB_ICONINFORMATION);
			MessageBox("정산완료", "확인", MB_ICONINFORMATION);
			OnBnClickedCancelBtn();
		}
	}
}

CString CRiderReportDlg::GetRiderCredit()
{
	CString strRiderCredit = "";
	char buffer[20];

	for(int i=0; i<m_lstReport.GetRecords()->GetCount(); i++)
	{
		long nID = m_lstReport.GetItemLong(i);
		CString strMemo = m_lstReport.GetItemText(i, 1);
		CString strCharge = m_lstReport.GetItemText(i, 2);

		if(nID > 0)
		{
			if(m_mapCredit[nID].strMemo == strMemo &&
				m_mapCredit[nID].nCharge == _ttoi(strCharge))
			{
				strRiderCredit += CString(_itoa(nID, buffer, 10)) + ";";
			}
		}
	}

	return strRiderCredit;
}

void CRiderReportDlg::OnBnClickedPrintBtn()
{
	Print(TRUE);
}

CString CRiderReportDlg::Print(BOOL bShow)
{
	if(!m_bComplete) // 정산이 되지않았으면 출력용 완료시킨다
		ReportComplete(TRUE);

	char buffer[20];
	CString sFor = "RiderDeposit/RiderDeposit.asp?nID=" + (CString)itoa(m_nID, buffer, 10);

	m_Http.Init();
	m_Http.SetConnectInfo("work.logisoft.co.kr", 8000, sFor);

	//m_Http.AddParamValue("nID", "136");

	if(0 != m_Http.Call()) {
		MessageBox("웹서버 이상", "확인", MB_ICONINFORMATION);
		return "";
	}

	CString sInfo = (char*)m_Http.GetResponse();	

	COleDateTime dtFrom; m_FromDT.GetTime(dtFrom);
	COleDateTime dtTo; m_ToDT.GetTime(dtTo);
	CString strFileName = dtFrom.Format("%m%d") + "_" + dtTo.Format("%m%d") + m_strRName;

	CString strFullName = "c:\\SmartQ\\정산\\" + strFileName + ".html";

	if(MakeFile(sInfo, strFileName))
	{
		if(!bShow)
			return strFullName;

		CWebPrintDlg dlg;
		dlg.m_sUrl = strFullName;
		dlg.m_bDelete = !m_bComplete;
		dlg.DoModal();
	}

	return strFullName;
}


BOOL CRiderReportDlg::MakeFile(CString strHtml,CString strFileName)
{
	CFileFind findfile;
	CString strFolder = "c:\\SmartQ\\정산\\*.*";
	CString FileName;

	BOOL bFind = findfile.FindFile(strFolder);
	BOOL bFindFile = FALSE;

	LF->CreateDir("c:\\SmartQ\\정산");

	if(bFind)
	{
		while(bFind)
		{
			bFind = findfile.FindNextFile();

			if(findfile.IsDots())
				continue;

			CString str = findfile.GetFileName();

			if(str.Find(strFileName) >=0)
			{
				bFindFile = TRUE;
				break;
			}
		}
	}

	CString strFullName = "c:\\SmartQ\\정산\\" + strFileName + ".html";

	if(!bFindFile)
		CFile file(_T(strFullName), CFile::modeCreate | CFile::modeWrite);

	FILE* fp = NULL;
	fp = fopen(strFullName, "wt");

	if(fp == NULL)
		return FALSE;

	fprintf(fp, strHtml);

	fclose(fp);

	return TRUE;

	//	m_Explorer.Navigate(sFullName, NULL, NULL, NULL, NULL);

	//	Sleep(1000);
	//	DeleteFile("C:\\weather.html");
}


BOOL CRiderReportDlg::PreTranslateMessage(MSG* pMsg)
{
	//if(pMsg->message == WM_KEYDOWN)
	//{	
	//	if(pMsg->hwnd == m_ReportOrderList.GetSafeHwnd())
	//	{
	//		RefreshCharge();
	//		return TRUE;
	//	}		
	//}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CRiderReportDlg::OnBnClickedApplicationBtn()
{
	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedApplicationBtn2()
{
	RefreshCharge();
}


HBRUSH CRiderReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_TAKE_GROUP_STC) {
		CRect r;
		m_stcTakeGroup.GetClientRect(r);
 
		r.top += 9;
		r.bottom -= 11;
		r.left += 2;
		r.right -= 4;

		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(0, 0, 255));
		r.DeflateRect(1, 1, 2, 2);
		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 255 , 255));

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 255));
		hbr = m_Bluebrush;
		}
	if(pWnd->GetDlgCtrlID() == IDC_GIVE_GROUP_STC) {
		CRect r;
		m_stcGiveGroup.GetClientRect(r);

		r.top += 9;
		r.bottom -= 11;
		r.left += 2;
		r.right -= 4; 

		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 0, 0));
		r.DeflateRect(1, 1, 2, 2);
		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 255 , 255));

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 0, 0));

		hbr = m_Redbrush;
	} 
	
	if(pWnd->GetDlgCtrlID() == IDC_DC_STC ||
		pWnd->GetDlgCtrlID() == IDC_HELP_STC1 ||
		pWnd->GetDlgCtrlID() == IDC_HELP_STC2 ||
		pWnd->GetDlgCtrlID() == IDC_MY_CALL_BEFORE_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_MY_CALL_AFTER_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_OTHER_CALL_BEFORE_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_OTHER_CALL_AFTER_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_CASH_MY_CALL_DEDUCTING_TAX_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_CASH_OTHER_CALL_DEDUCTING_TAX_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_PLUS_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_EQUAL_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_STATIC_HELP)
	{
		CWnd *pWnd1 = (CWnd*)GetDlgItem(pWnd->GetDlgCtrlID());

		CRect r;
		pWnd1->GetClientRect(r);
		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 255, 255));
		
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));

		hbr = m_Whitebrush;
	}

	

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CRiderReportDlg::CallCompleteReport()
{
	char buffer[20];
	m_stcReportNo.ShowWindow(TRUE);
	m_stcReportNo.SetWindowText("정산번호 : " + CString(itoa(m_nID, buffer, 10)));

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_complete_report_1");

	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtStart, dtEnd;
	long nFixedDeposit;
	long nMyCallAllCashCount, nMyCallAllCashCharge,	nMyCallApplyCashCount, nMyCallApplyCashCharge, nMyCallCashFee;
	BOOL bMyCallCashWon, bOtherCallCreditWon;
	long nMyCallCashFeeTotal;
	long nOtherCallAllCashCount, nOtherCallAllCashCharge, nOtherCallApplyCashCount, nOtherCallApplyCashCharge, nOtherCallCashFee;
	BOOL bOtherCallCashWon, bOtherCallBefore, bOtherCallOnlineWon, bBeforeOtherCallCreditOnlineDeductingWon;
	long nOtherCallCashFeeTotal, nCashCallAllCount, nCashCallAllCharge, nCashFeeTotal, nLastMonth, nTakeEtcTotal, nCashDeductTaxType;
	CString sCashDeductingTaxFee, sTakeEtc, sTakeEtcCharge, sGiveEtc, sGiveEtcCharge, sAfterOtherCallCreditOnlineDeductingTaxFee;
	BOOL bCashDeductingTaxFee, bMyCallBefore, bMyCallCreditWon, bMyCallOnlineWon, bBeforeMyCallCreditOnlineDeductingTaxWon, bAfterMyCallCreditOnlineDeductingTaxWon;
	long nCashDeductingTaxFeeTotal, nTakeTotal, nReceiveCharge;
	long nMyCallAllCreditCount, nMyCallAllCreditCharge, nMyCallNotApplyCreditCount, nMyCallNotApplyCreditCharge, nMyCallApplyCreditCount, nMyCallApplyCreditCharge, nMyCallCreditFee;
	long nMyCallCreditFeeTotal, nMyCallAllOnlineCount, nMyCallAllOnlineCharge, nMyCallNotApplyOnlineCount, nMyCallNotApplyOnlineCharge, nMyCallApplyOnlineCount, nMyCallApplyOnlineCharge;
	long nMyCallOnlineFee;
	long nMyCallOnlineFeeTotal, nMyCallAllCreditOnlineCount, nMyCallAllCreditOnlineCharge, nMyCallNotApplyCreditOnlineCount, nMyCallNotApplyCreditOnlineCharge;
	long nMyCallCreditOnlineFeeTotal, nBeforeMyCallCreditOnlineDeductingTaxFeeTotal;
	CString sBeforeMyCallCreditOnlineDeductingTaxFee, sAfterMyCallCreditOnlineDeductingTaxFee, sBeforeOtherCallCreditOnlineDeductingTaxFee;
	long nOtherCallAllCreditCount, nOtherCallAllCreditCharge, nOtherCallNotApplyCreditCount, nOtherCallNotApplyCreditCharge, nOtherCallApplyCreditCount, nOtherCallApplyCreditCharge;
	long nOtherCallCreditFee, nOtherCallCreditFeeTotal, nOtherCallAllOnlineCount, nOtherCallAllOnlineCharge, nOtherCallNotApplyOnlineCount, nOtherCallNotApplyOnlineCharge;
	long nOtherCallApplyOnlineCount, nOtherCallApplyOnlineCharge, nOtherCallOnlineFee, nOtherCallOnlineFeeTotal, nOtherCallAllCreditOnlineCount, nOtherCallAllCreditOnlineCharge;
	long nOtherCallNotApplyCreditOnlineCount, nOtherCallNotApplyCreditOnlineCharge, nOtherCallCreditOnlineFeeTotal, nBeforeOtherCallCreditOnlineDeductingTaxFeeTotal;
	long nAfterMyCallCreditOnlineDeductingTaxFeeTotal;
	BOOL bAfterOtherCallCreditOnlineDeductingWon;
	long nAfterOtherCallCreditOnlineDeductingTaxFeeTotal, nGiveEtcTotal, nTransCount, nTransCharge, nGiveTotal, nTotal;
	CString sMemo;

	if(pRs.GetRecordCount() == 0) return;

	parRet->GetValue(m_nRiderCharge);

	pRs.GetFieldValue("dtStart", dtStart); 	pRs.GetFieldValue("dtEnd", dtEnd);
	pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
	pRs.GetFieldValue("nMyCallAllCashCount", nMyCallAllCashCount);
	pRs.GetFieldValue("nMyCallAllCashCharge", nMyCallAllCashCharge);
	pRs.GetFieldValue("nMyCallApplyCashCount", nMyCallApplyCashCount);
	pRs.GetFieldValue("nMyCallApplyCashCharge", nMyCallApplyCashCharge);
	pRs.GetFieldValue("nMyCallCashFee", nMyCallCashFee);
	pRs.GetFieldValue("bMyCallCashWon", bMyCallCashWon);
	pRs.GetFieldValue("nMyCallCashFeeTotal", nMyCallCashFeeTotal);

	m_FromDT.SetTime(dtStart);
	m_ToDT.SetTime(dtEnd);

	m_edtFixedDeposit.SetWindowText(LF->GetMyNumberFormat(nFixedDeposit));
	m_edtMyCallAllCashCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCount));
	m_edtMyCallAllCashCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCashCharge));
	m_edtMyCallApplyCashCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCashCount));
	m_edtMyCallApplyCashCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCashCharge));
	m_edtMyCallCashFee.SetWindowText(LF->GetMyNumberFormat(nMyCallCashFee));
	if(bMyCallCashWon)
	{
		m_btnMyCallCashWon.SetWindowText("원");
		m_btnMyCallCashWon.SetChecked(TRUE);
	}

	m_edtMyCallCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyCallCashFeeTotal));

	pRs.GetFieldValue("nOtherCallAllCashCount", nOtherCallAllCashCount);
	pRs.GetFieldValue("nOtherCallAllCashCharge", nOtherCallAllCashCharge);
	pRs.GetFieldValue("nOtherCallApplyCashCount", nOtherCallApplyCashCount);
	pRs.GetFieldValue("nOtherCallApplyCashCharge", nOtherCallApplyCashCharge);
	pRs.GetFieldValue("nOtherCallCashFee", nOtherCallCashFee);
	pRs.GetFieldValue("bOtherCallCashWon", bOtherCallCashWon);
	pRs.GetFieldValue("nOtherCallCashFeeTotal", nOtherCallCashFeeTotal);

	m_edtOtherCallAllCashCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCashCount));
	m_edtOtherCallAllCashCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCashCharge));
	m_edtOtherCallApplyCashCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCashCount));
	m_edtOtherCallApplyCashCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCashCharge));
	m_edtOtherCallCashFee.SetWindowText(LF->GetMyNumberFormat(nOtherCallCashFee));
	if(bOtherCallCashWon)
	{
		m_btnOtherCallCashWon.SetWindowText("원");
		m_btnOtherCallCashWon.SetChecked(TRUE);
	}
	m_edtOtherCallCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyCallCashFeeTotal));


	pRs.GetFieldValue("nCashCallAllCount", nCashCallAllCount);
	pRs.GetFieldValue("nCashCallAllCharge", nCashCallAllCharge);
	pRs.GetFieldValue("nCashFeeTotal", nCashFeeTotal);
	pRs.GetFieldValue("nLastMonth", nLastMonth);
	pRs.GetFieldValue("sTakeEtc", sTakeEtc);
	pRs.GetFieldValue("sTakeEtcCharge", sTakeEtcCharge);
	pRs.GetFieldValue("nTakeEtcTotal", nTakeEtcTotal);
	pRs.GetFieldValue("nCashDeductTaxType", nCashDeductTaxType);
	pRs.GetFieldValue("sCashDeductingTaxFee", sCashDeductingTaxFee);
	pRs.GetFieldValue("bCashDeductingTaxFee", bCashDeductingTaxFee);
	pRs.GetFieldValue("nCashDeductingTaxFeeTotal", nCashDeductingTaxFeeTotal);
	pRs.GetFieldValue("nTakeTotal", nTakeTotal);

	m_edtCashCallAllCount.SetWindowText(LF->GetMyNumberFormat(nCashCallAllCount));
	m_edtCashCallAllCharge.SetWindowText(LF->GetMyNumberFormat(nCashCallAllCharge));
	m_edtCashFeeTotal.SetWindowText(LF->GetMyNumberFormat(nCashFeeTotal));
	m_edtLastMonth.SetWindowText(LF->GetMyNumberFormat(nLastMonth));
	RefreshEtcList(&m_lstReport, sTakeEtc, sTakeEtcCharge);
	m_edtTakeEtcTotal.SetWindowText(LF->GetMyNumberFormat(nTakeEtcTotal));
	if(nCashDeductTaxType == 3)
	{
		m_chkCashMyCallDeductingTax.SetCheck(TRUE);
		m_chkCashOtherCallDeductingTax.SetCheck(TRUE);
	}
	else if(nCashDeductTaxType == 2)
		m_chkCashMyCallDeductingTax.SetCheck(TRUE);
	else if(nCashDeductTaxType == 1)
		m_chkCashOtherCallDeductingTax.SetCheck(TRUE);
	else
	{
		m_chkCashMyCallDeductingTax.SetCheck(FALSE);
		m_chkCashOtherCallDeductingTax.SetCheck(FALSE);
	}
	OnBnClickedMyCallBeforeCheck();
	m_edtCashDeductingTaxFee.SetWindowText(sCashDeductingTaxFee);
	if(bCashDeductingTaxFee)
	{
		m_btnCashDeductingTaxFee.SetWindowText("원");
		m_btnCashDeductingTaxFee.SetChecked(TRUE);
	}
	m_edtCashDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nCashDeductingTaxFeeTotal));
	m_edtTakeTotal.SetWindowText(LF->GetMyNumberFormat(nTakeEtcTotal));
	m_edtTakeTotal1.SetWindowText(LF->GetMyNumberFormat(nTakeEtcTotal));

	pRs.GetFieldValue("nReceiveCharge", nReceiveCharge);
	pRs.GetFieldValue("bMyCallBefore", bMyCallBefore);
	pRs.GetFieldValue("nMyCallAllCreditCount", nMyCallAllCreditCount);
	pRs.GetFieldValue("nMyCallAllCreditCharge", nMyCallAllCreditCharge);
	pRs.GetFieldValue("nMyCallNotApplyCreditCount", nMyCallNotApplyCreditCount);
	pRs.GetFieldValue("nMyCallNotApplyCreditCharge", nMyCallNotApplyCreditCharge);
	pRs.GetFieldValue("nMyCallApplyCreditCount", nMyCallApplyCreditCount);
	pRs.GetFieldValue("nMyCallApplyCreditCharge", nMyCallApplyCreditCharge);
	pRs.GetFieldValue("nMyCallCreditFee", nMyCallCreditFee);
	pRs.GetFieldValue("bMyCallCreditWon", bMyCallCreditWon);
	pRs.GetFieldValue("nMyCallCreditFeeTotal", nMyCallCreditFeeTotal);
	
	m_edtReceiveCharge.SetWindowText(LF->GetMyNumberFormat(nReceiveCharge));
	if(bMyCallBefore)
	{
		m_chkMyCallBefore.SetCheck(FALSE);
		m_chkMyCallAfter.SetCheck(TRUE);
	}
	else
	{
		m_chkMyCallBefore.SetCheck(TRUE);
		m_chkMyCallAfter.SetCheck(FALSE);
	}
	OnBnClickedMyCallBeforeCheck();
	m_edtMyCallAllCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCount));
	m_edtMyCallAllCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditCharge));
	m_edtMyCallNotApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCount));
	m_edtMyCallNotApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditCharge));
	m_edtMyCallApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCreditCount));
	m_edtMyCallApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyCreditCharge));
	m_edtMyCallCreditFee.SetWindowText(LF->GetMyNumberFormat(nMyCallCreditFee));
	if(bMyCallCreditWon)
	{
		m_btnMyCallCreditWon.SetWindowText("원");
		m_btnMyCallCreditWon.SetChecked(TRUE);
	}
	m_edtMyCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyCallCreditFeeTotal));

	pRs.GetFieldValue("nMyCallAllOnlineCount", nMyCallAllOnlineCount);
	pRs.GetFieldValue("nMyCallAllOnlineCharge", nMyCallAllOnlineCharge);
	pRs.GetFieldValue("nMyCallNotApplyOnlineCount", nMyCallNotApplyOnlineCount);
	pRs.GetFieldValue("nMyCallNotApplyOnlineCharge", nMyCallNotApplyOnlineCharge);
	pRs.GetFieldValue("nMyCallApplyOnlineCount", nMyCallApplyOnlineCount);
	pRs.GetFieldValue("nMyCallApplyOnlineCharge", nMyCallApplyOnlineCharge);
	pRs.GetFieldValue("nMyCallOnlineFee", nMyCallOnlineFee);
	pRs.GetFieldValue("bMyCallOnlineWon", bMyCallOnlineWon);
	pRs.GetFieldValue("nMyCallOnlineFeeTotal", nMyCallOnlineFeeTotal);

	m_edtMyCallAllOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllOnlineCount));
	m_edtMyCallAllOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllOnlineCharge));
	m_edtMyCallNotApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyOnlineCount));
	m_edtMyCallNotApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyOnlineCharge));
	m_edtMyCallApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyOnlineCount));
	m_edtMyCallApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallApplyOnlineCharge));
	m_edtMyCallOnlineFee.SetWindowText(LF->GetMyNumberFormat(nMyCallOnlineFee));
	if(m_btnMyCallOnlineWon)
	{
		m_btnMyCallOnlineWon.SetWindowText("원");
		m_btnMyCallOnlineWon.SetChecked(TRUE);
	}
	m_edtMyCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyCallOnlineFeeTotal));

	pRs.Close();


	CMkRecordset pRs2(m_pMkDb); 
	CMkCommand pCmd2(m_pMkDb, "select_rider_complete_report_3_left");
	pCmd2.AddParameter(m_nID);
	pCmd2.AddParameter(m_nRiderCompany);
	pCmd2.AddParameter(m_nRNo); 
 
	if(!pRs2.Execute(&pCmd2)) return; 

	pRs2.GetFieldValue("nMyCallAllCreditOnlineCount", nMyCallAllCreditOnlineCount);
	pRs2.GetFieldValue("nMyCallAllCreditOnlineCharge", nMyCallAllCreditOnlineCharge);
	pRs2.GetFieldValue("nMyCallNACreditOnlineCount", nMyCallNotApplyCreditOnlineCount);
	pRs2.GetFieldValue("nMyCallNACreditOnlineCharge", nMyCallNotApplyCreditOnlineCharge);
	pRs2.GetFieldValue("nMyCallCreditOnlineFeeTotal", nMyCallCreditOnlineFeeTotal);
	pRs2.GetFieldValue("sBeMyCallCreditOnlineDTFee", sBeforeMyCallCreditOnlineDeductingTaxFee);
	pRs2.GetFieldValue("bBeMyCallCreditOnlineDTWon", bBeforeMyCallCreditOnlineDeductingTaxWon);
	pRs2.GetFieldValue("nBeMyCallCreditOnlineDTFeeTotal", nBeforeMyCallCreditOnlineDeductingTaxFeeTotal);
	pRs2.GetFieldValue("sAfMyCallCreditOnlineDTFee", sAfterMyCallCreditOnlineDeductingTaxFee);
	pRs2.GetFieldValue("bAfMyCallCreditOnlineDTWon", bAfterMyCallCreditOnlineDeductingTaxWon);
	pRs2.GetFieldValue("nAfMyCallCODTFeeTotal", nAfterMyCallCreditOnlineDeductingTaxFeeTotal);
	
	m_edtMyCallAllCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditOnlineCount));
	m_edtMyCallAllCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallAllCreditOnlineCharge));
	m_edtMyCallNotApplyCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditOnlineCount));
	m_edtMyCallNotApplyCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nMyCallNotApplyCreditOnlineCharge));
	m_edtMyCallCreditOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nMyCallCreditOnlineFeeTotal));
	m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetWindowText(sBeforeMyCallCreditOnlineDeductingTaxFee);
	if(bBeforeMyCallCreditOnlineDeductingTaxWon)
	{
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetWindowText("원");
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetChecked(TRUE);
	}
	m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nBeforeMyCallCreditOnlineDeductingTaxFeeTotal));
	m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetWindowText(sAfterMyCallCreditOnlineDeductingTaxFee);
	if(bAfterMyCallCreditOnlineDeductingTaxWon)
	{
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetWindowText("원");
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetChecked(TRUE);
	}
	m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nAfterMyCallCreditOnlineDeductingTaxFeeTotal)); // 요까지한번

	pRs2.GetFieldValue("bOtherCallBefore", bOtherCallBefore);
	pRs2.GetFieldValue("nOtherCallAllCreditCount", nOtherCallAllCreditCount);
	pRs2.GetFieldValue("nOtherCallAllCreditCharge", nOtherCallAllCreditCharge);
	pRs2.GetFieldValue("nOtherCallNACreditCount", nOtherCallNotApplyCreditCount);
	pRs2.GetFieldValue("nOtherCallNACreditCharge", nOtherCallNotApplyCreditCharge);
	pRs2.GetFieldValue("nOtherCallApplyCreditCount", nOtherCallApplyCreditCount);
	pRs2.GetFieldValue("nOtherCallApplyCreditCharge", nOtherCallApplyCreditCharge);
	pRs2.GetFieldValue("nOtherCallCreditFee", nOtherCallCreditFee);
	pRs2.GetFieldValue("bOtherCallCreditWon", bOtherCallCreditWon);
	pRs2.GetFieldValue("nOtherCallCreditFeeTotal", nOtherCallCreditFeeTotal);

	if(bOtherCallBefore)
	{
		m_chkOtherCallBefore.SetCheck(FALSE);
		m_chkOtherCallAfter.SetCheck(TRUE);
	}
	else
	{
		m_chkOtherCallBefore.SetCheck(TRUE);
		m_chkOtherCallAfter.SetCheck(FALSE);
	}
	OnBnClickedMyCallAfterCheck();
	m_edtOtherCallAllCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCount));
	m_edtOtherCallAllCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditCharge));
	m_edtOtherCallNotApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCount));
	m_edtOtherCallNotApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditCharge));
	m_edtOtherCallApplyCreditCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCreditCount));
	m_edtOtherCallApplyCreditCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyCreditCharge));
	m_edtOtherCallCreditFee.SetWindowText(LF->GetMyNumberFormat(nOtherCallCreditFee));
	if(bOtherCallCreditWon)
	{
		m_btnOtherCallCreditWon.SetWindowText("원");
		m_btnOtherCallCreditWon.SetChecked(TRUE);
	}
	m_edtOtherCallCreditFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherCallCreditFeeTotal)); 

	pRs2.GetFieldValue("nOtherCallAllOnlineCount", nOtherCallAllOnlineCount);
	pRs2.GetFieldValue("nOtherCallAllOnlineCharge", nOtherCallAllOnlineCharge);
	pRs2.GetFieldValue("nOtherCallNAOnlineCount", nOtherCallNotApplyOnlineCount);
	pRs2.GetFieldValue("nOtherCallNAOnlineCharge", nOtherCallNotApplyOnlineCharge);
	pRs2.GetFieldValue("nOtherCallApplyOnlineCount", nOtherCallApplyOnlineCount);
	pRs2.GetFieldValue("nOtherCallApplyOnlineCharge", nOtherCallApplyOnlineCharge);
	pRs2.GetFieldValue("nOtherCallOnlineFee", nOtherCallOnlineFee);
	pRs2.GetFieldValue("bOtherCallOnlineWon", bOtherCallOnlineWon);
	pRs2.GetFieldValue("nOtherCallOnlineFeeTotal", nOtherCallOnlineFeeTotal);
	
	m_edtOtherCallAllOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllOnlineCount));
	m_edtOtherCallAllOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllOnlineCharge));
	m_edtOtherCallNotApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyOnlineCount));
	m_edtOtherCallNotApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyOnlineCharge));
	m_edtOtherCallApplyOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyOnlineCount));
	m_edtOtherCallApplyOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallApplyOnlineCharge));
	m_edtOtherCallOnlineFee.SetWindowText(LF->GetMyNumberFormat(nOtherCallOnlineFee));
	if(bOtherCallOnlineWon)
	{
		m_btnOtherCallOnlineWon.SetWindowText("원");
		m_btnOtherCallOnlineWon.SetChecked(TRUE);
	}
	m_edtOtherCallOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherCallOnlineFeeTotal));

	pRs2.GetFieldValue("nOtherCallAllCreditOnlineCount", nOtherCallAllCreditOnlineCount);
	pRs2.GetFieldValue("nOtherCallAllCreditOnlineCharge", nOtherCallAllCreditOnlineCharge);
	pRs2.GetFieldValue("nOtherCallNACreditOnlineCount", nOtherCallNotApplyCreditOnlineCount);
	pRs2.GetFieldValue("nOtherCallNACreditOnlineCharge", nOtherCallNotApplyCreditOnlineCharge);
	pRs2.GetFieldValue("nOtherCallCreditOnlineFeeTotal", nOtherCallCreditOnlineFeeTotal);
	pRs2.GetFieldValue("sBeOtherCallCreditOnlineDTFee", sBeforeOtherCallCreditOnlineDeductingTaxFee);
	pRs2.GetFieldValue("bBeOtherCallCreditOnlineDWon", bBeforeOtherCallCreditOnlineDeductingWon);
	pRs2.GetFieldValue("nBeOtherCallCODTFeeTotal", nBeforeOtherCallCreditOnlineDeductingTaxFeeTotal);
	pRs2.GetFieldValue("sAfOtherCallCreditOnlineDTFee", sAfterOtherCallCreditOnlineDeductingTaxFee);
	pRs2.GetFieldValue("bAfOtherCallCreditOnlineDWon", bAfterOtherCallCreditOnlineDeductingWon);
	pRs2.GetFieldValue("nAfOtherCallCODTFeeTotal", nAfterOtherCallCreditOnlineDeductingTaxFeeTotal);
	
	m_edtOtherCallAllCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditOnlineCount));
	m_edtOtherCallAllCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallAllCreditOnlineCharge));
	m_edtOtherCallNotApplyCreditOnlineCount.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditOnlineCount));
	m_edtOtherCallNotApplyCreditOnlineCharge.SetWindowText(LF->GetMyNumberFormat(nOtherCallNotApplyCreditOnlineCharge));
	m_edtOtherCallCreditOnlineFeeTotal.SetWindowText(LF->GetMyNumberFormat(nOtherCallCreditOnlineFeeTotal));
	m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetWindowText(sBeforeOtherCallCreditOnlineDeductingTaxFee);
	if(bBeforeOtherCallCreditOnlineDeductingWon)
	{
		m_btnBeforeOtherCallCreditOnlineDeductingWon.SetWindowText("원");
		m_btnBeforeOtherCallCreditOnlineDeductingWon.SetChecked(TRUE);
	}
	m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nBeforeOtherCallCreditOnlineDeductingTaxFeeTotal));
	m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetWindowText(sAfterOtherCallCreditOnlineDeductingTaxFee);
	if(bAfterOtherCallCreditOnlineDeductingWon)
	{
		m_btnAfterOtherCallCreditOnlineDeductingWon.SetWindowText("원");
		m_btnAfterOtherCallCreditOnlineDeductingWon.SetChecked(TRUE);
	}
	m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText(LF->GetMyNumberFormat(nAfterOtherCallCreditOnlineDeductingTaxFeeTotal));

	pRs2.GetFieldValue("sGiveEtc", sGiveEtc);
	pRs2.GetFieldValue("sGiveEtcCharge", sGiveEtcCharge);
	pRs2.GetFieldValue("nGiveEtcTotal", nGiveEtcTotal);
	pRs2.GetFieldValue("nTransCount", nTransCount);
	pRs2.GetFieldValue("nTransCharge", nTransCharge);
	pRs2.GetFieldValue("nGiveTotal", nGiveTotal);
	pRs2.GetFieldValue("nTotal", nTotal);
	pRs2.GetFieldValue("sMemo", sMemo);

	long nCouponCharge, nCouponPlus, nCouponTotal;

	pRs2.GetFieldValue("nCouponCharge", nCouponCharge);
	pRs2.GetFieldValue("nCouponPlus", nCouponPlus);
	pRs2.GetFieldValue("nCouponTotal", nCouponTotal);
//	pRs2.GetFieldValue("nCouponcount", nCouponCount);

	RefreshEtcList(&m_lstReport2, sGiveEtc, sGiveEtcCharge);
	m_edtGiveEtcTotal.SetWindowText(LF->GetMyNumberFormat(nGiveEtcTotal));
	m_edtTransCount.SetWindowText(LF->GetMyNumberFormat(nTransCount));
	m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(nTransCharge));

	m_edtCoupon.SetWindowText(LF->GetMyNumberFormat(nCouponCharge));
	m_edtCouponPlus.SetWindowText(LF->GetMyNumberFormat(nCouponPlus));
	m_edtCouponTotal.SetWindowText(LF->GetMyNumberFormat(nCouponTotal));

	m_edtGiveTotal.SetWindowText(LF->GetMyNumberFormat(nGiveTotal));
	m_edtGiveTotal1.SetWindowText(LF->GetMyNumberFormat(nGiveTotal));
	m_edtTotal.SetWindowText(LF->GetMyNumberFormat(nTotal));

	m_edtMemo.SetWindowText(sMemo);
	m_btnComplete.SetWindowText("정산수정");

	pRs2.GetFieldValue("nMyCallGiveToRiderCount", m_nMyCallGiveToRiderCount);
	pRs2.GetFieldValue("nMyCallGiveToRiderCharge", m_nMyCallGiveToRiderCharge);
	pRs2.GetFieldValue("nOtherCallGiveToRiderCount", m_nOtherCallGiveToRiderCount);
	pRs2.GetFieldValue("nOtherCallGiveToRiderCharge", m_nOtherCallGiveToRiderCharge);

	SetTextStc();

	OnBnClickedMyCallCashWonBtn();
	OnBnClickedOtherCallCashWonBtn();
	OnBnClickedCashDeductingTaxFeeBtn();
	OnBnClickedBeforeMyCallCreditOnlineDeductingTaxWonBtn();
	OnBnClickedMyCallCreditWonBtn();
	OnBnClickedMyCallOnlineWonBtn();
	OnBnClickedOtherCallCreditWonBtn();
	OnBnClickedOtherCallOnlineWonBtn();
	OnBnClickedAfterMyCallCreditOnlineDeductingTaxWonBtn();
	OnBnClickedBeforeOtherCallCreditOnlineDeductingWonBtn();
	OnBnClickedAfterOtherCallCreditOnlineDeductingWonBtn();
}



void CRiderReportDlg::OnBnClickedDeleteReportBtn()
{
	if(!m_bComplete)
	{
		MessageBox("아직 정산이 되지 않았습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sMsg = "정산을 삭제 하시면 미정산 상태로 돌아갑니다\r\n계속 하시겠습니까?";

	if(MessageBox(sMsg, "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CMkCommand pCmd(m_pMkDb, "delete_rider_report_fixedposit");
		pCmd.AddParameter(m_nID);
		pCmd.AddParameter(m_nRiderCompany);
		pCmd.AddParameter(m_nRNo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);

		if(pCmd.Execute())
			OnOK();
	}
}


void CRiderReportDlg::OnBnClickedSaveOptionBtn()
{
	CRiderDepositInfoDlg dlg;
	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_strRName = m_strRName;
	dlg.DoModal();
}

void CRiderReportDlg::OnBnClickedMyCallCashWonBtn()
{
	m_btnMyCallCashWon.SetChecked(!m_btnMyCallCashWon.GetChecked());

	if(m_btnMyCallCashWon.GetChecked() == BST_CHECKED)
		m_btnMyCallCashWon.SetWindowText("%");
	else
		m_btnMyCallCashWon.SetWindowText("원");

	RefreshCharge();
}


void CRiderReportDlg::OnBnClickedOtherCallCashWonBtn()
{
	m_btnOtherCallCashWon.SetChecked(!m_btnOtherCallCashWon.GetChecked());

	if(m_btnOtherCallCashWon.GetChecked() == BST_CHECKED)
		m_btnOtherCallCashWon.SetWindowText("%");
	else
		m_btnOtherCallCashWon.SetWindowText("원");

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedMyCallOnlineWonBtn()
{
	m_btnMyCallOnlineWon.SetChecked(!m_btnMyCallOnlineWon.GetChecked());

	if(m_btnMyCallOnlineWon.GetChecked() == BST_CHECKED)
		m_btnMyCallOnlineWon.SetWindowText("%");
	else
		m_btnMyCallOnlineWon.SetWindowText("원");

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedOtherCallCreditWonBtn()
{
	m_btnOtherCallCreditWon.SetChecked(!m_btnOtherCallCreditWon.GetChecked());

	if(m_btnOtherCallCreditWon.GetChecked() == BST_CHECKED)
		m_btnOtherCallCreditWon.SetWindowText("%");
	else
		m_btnOtherCallCreditWon.SetWindowText("원");

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedOtherCallOnlineWonBtn()
{
	m_btnOtherCallOnlineWon.SetChecked(!m_btnOtherCallOnlineWon.GetChecked());

	if(m_btnOtherCallOnlineWon.GetChecked() == BST_CHECKED)
		m_btnOtherCallOnlineWon.SetWindowText("%");
	else
		m_btnOtherCallOnlineWon.SetWindowText("원");

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedCashDeductingTaxFeeBtn()
{
	m_btnCashDeductingTaxFee.SetChecked(!m_btnCashDeductingTaxFee.GetChecked());

	if(m_btnCashDeductingTaxFee.GetChecked() == BST_CHECKED)
	{
		m_btnCashDeductingTaxFee.SetWindowText("%");
	}
	else
	{
		m_btnCashDeductingTaxFee.SetWindowText("원");
	}

	RefreshCharge();
}


void CRiderReportDlg::OnBnClickedAfterMyCallCreditOnlineDeductingTaxWonBtn()
{
	m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetChecked(!m_btnAfterMyCallCreditOnlineDeductingTaxWon.GetChecked());

	if(m_btnAfterMyCallCreditOnlineDeductingTaxWon.GetChecked() == BST_CHECKED)
	{
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetWindowText("%");
	}
	else
	{
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetWindowText("원");
	}

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedBeforeMyCallCreditOnlineDeductingTaxWonBtn()
{
	m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetChecked(!m_btnBeforeMyCallCreditOnlineDeductingTaxWon.GetChecked());

	if(m_btnBeforeMyCallCreditOnlineDeductingTaxWon.GetChecked() == BST_CHECKED)
	{
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetWindowText("%");
	}
	else
	{
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetWindowText("원");
	}

	RefreshCharge();
}


void CRiderReportDlg::OnBnClickedBeforeOtherCallCreditOnlineDeductingWonBtn()
{
	m_btnBeforeOtherCallCreditOnlineDeductingWon.SetChecked(!m_btnBeforeOtherCallCreditOnlineDeductingWon.GetChecked());

	if(m_btnBeforeOtherCallCreditOnlineDeductingWon.GetChecked() == BST_CHECKED)
	{
		m_btnBeforeOtherCallCreditOnlineDeductingWon.SetWindowText("%");
	}
	else
	{
		m_btnBeforeOtherCallCreditOnlineDeductingWon.SetWindowText("원");
	}
	
	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedAfterOtherCallCreditOnlineDeductingWonBtn()
{
	m_btnAfterOtherCallCreditOnlineDeductingWon.SetChecked(!m_btnAfterOtherCallCreditOnlineDeductingWon.GetChecked());

	if(m_btnAfterOtherCallCreditOnlineDeductingWon.GetChecked() == BST_CHECKED)
	{
		m_btnAfterOtherCallCreditOnlineDeductingWon.SetWindowText("%");
	}
	else
	{
		m_btnAfterOtherCallCreditOnlineDeductingWon.SetWindowText("원");
	}

	RefreshCharge();

}
void CRiderReportDlg::OnBnClickedCashMyCallDeductingTaxCheck()
{
	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedOtherCallBeforeCheck()
{ 
	if(m_chkOtherCallBefore.GetCheck() == TRUE)
	{
		AfxGetApp()->WriteProfileInt("nOtherDcBeforeAfter", "nOtherDcBeforeAfter", 0);
		m_chkOtherCallAfter.SetCheck(FALSE);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnBeforeOtherCallCreditOnlineDeductingWon.EnableWindow(TRUE);
	
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnAfterOtherCallCreditOnlineDeductingWon.EnableWindow(FALSE);
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	}
	else
	{
		AfxGetApp()->WriteProfileInt("nOtherDcBeforeAfter", "nOtherDcBeforeAfter", 1);
		m_chkOtherCallBefore.SetCheck(FALSE);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnBeforeOtherCallCreditOnlineDeductingWon.EnableWindow(FALSE);
		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
		
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnAfterOtherCallCreditOnlineDeductingWon.EnableWindow(TRUE);
		
	}

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedOtherCallAfterCheck()
{
	if(m_chkOtherCallAfter.GetCheck() == TRUE)
	{
		AfxGetApp()->WriteProfileInt("nOtherDcBeforeAfter", "nOtherDcBeforeAfter", 1);
        m_chkOtherCallBefore.SetCheck(FALSE);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnBeforeOtherCallCreditOnlineDeductingWon.EnableWindow(FALSE);
		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnAfterOtherCallCreditOnlineDeductingWon.EnableWindow(TRUE);
	}
	else
	{
		AfxGetApp()->WriteProfileInt("nOtherDcBeforeAfter", "nOtherDcBeforeAfter", 0);
		m_chkOtherCallBefore.SetCheck(TRUE);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnBeforeOtherCallCreditOnlineDeductingWon.EnableWindow(TRUE);
	
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnAfterOtherCallCreditOnlineDeductingWon.EnableWindow(FALSE);
		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	}
	RefreshCharge();
}


void CRiderReportDlg::OnBnClickedMyCallBeforeCheck()
{
	if(m_chkMyCallBefore.GetCheck() == TRUE)
	{
		AfxGetApp()->WriteProfileInt("nMyDcBeforeAfter", "nMyDcBeforeAfter", 0);
		m_chkMyCallAfter.SetCheck(FALSE);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.EnableWindow(TRUE);
	
		m_edtAfterMyCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.EnableWindow(FALSE);
		m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	}
	else
	{
		AfxGetApp()->WriteProfileInt("nMyDcBeforeAfter", "nMyDcBeforeAfter", 1);
		m_chkMyCallAfter.SetCheck(TRUE);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.EnableWindow(FALSE);
		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");

		m_edtAfterMyCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.EnableWindow(TRUE);
	}

	RefreshCharge();
}

void CRiderReportDlg::OnBnClickedMyCallAfterCheck()
{
	if(m_chkMyCallAfter.GetCheck() == TRUE)
	{
		AfxGetApp()->WriteProfileInt("nMyDcBeforeAfter", "nMyDcBeforeAfter", 1);
		m_chkMyCallBefore.SetCheck(FALSE);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.EnableWindow(FALSE);
		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	
		m_edtAfterMyCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.EnableWindow(TRUE);

	}
	else
	{
		AfxGetApp()->WriteProfileInt("nMyDcBeforeAfter", "nMyDcBeforeAfter", 0);
		m_chkMyCallBefore.SetCheck(TRUE);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.EnableWindow(TRUE);
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.EnableWindow(TRUE);

		m_edtAfterMyCallCreditOnlineDeductingTaxFee.EnableWindow(FALSE);
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.EnableWindow(FALSE);
		m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetWindowText("");
		m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal.SetWindowText("");
	}

	RefreshCharge();

}

void CRiderReportDlg::OnBnClickedCashOtherCallDeductingTaxCheck()
{
	OnBnClickedCashMyCallDeductingTaxCheck();

	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeMyCallCashFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeOtherCallCashFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeCashDeductingTaxFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeBeforeMyCallCreditOnlineDeductingTaxFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeMyCallCreditFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeMyCallOnlineFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeOtherCallCreditFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeOtherCallOnlineFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeAfterOtherCallCreditOnlineDeductingTaxFeeEdit()
{
	RefreshCharge();
}


void CRiderReportDlg::OnBnClickedMyCallCreditWonBtn()
{
	m_btnMyCallCreditWon.SetChecked(!m_btnMyCallCreditWon.GetChecked());

	if(m_btnMyCallCreditWon.GetChecked() == BST_CHECKED)
		m_btnMyCallCreditWon.SetWindowText("%");
	else
		m_btnMyCallCreditWon.SetWindowText("원");

	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeFixedDepositEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::OnEnChangeAfterMyCallCreditOnlineDeductingTaxFeeEdit()
{
	RefreshCharge();
}


void CRiderReportDlg::OnEnChangeBeforeOtherCallAllCreaditOnlineDeductingTaxFeeEdit()
{
	RefreshCharge();
}

void CRiderReportDlg::ApplyDT()
{	
	char buffer[20];
 
	if(!m_bUseDTPercent)
	{
		m_edtCashDeductingTaxFee.SetWindowText(itoa(m_nDT, buffer, 10));
		m_btnCashDeductingTaxFee.SetChecked(TRUE);
		m_chkCashMyCallDeductingTax.SetCheck(TRUE);
	}
	else
	{
		if(m_nCashDTType == 0)
		{
			m_chkCashMyCallDeductingTax.SetCheck(FALSE);
			m_chkCashMyCallDeductingTax.SetCheck(FALSE);
		}
		else if(m_nCashDTType == 1)
			m_chkCashOtherCallDeductingTax.SetCheck(TRUE);
		else if(m_nCashDTType == 2)
			m_chkCashMyCallDeductingTax.SetCheck(TRUE);
		else if(m_nCashDTType == 3)
		{
			m_chkCashMyCallDeductingTax.SetCheck(TRUE);
			m_chkCashOtherCallDeductingTax.SetCheck(TRUE);
		}

		if(m_nMyCallDTType == 0)
			m_chkMyCallBefore.SetCheck(TRUE);
		else
			m_chkMyCallAfter.SetCheck(TRUE);

		if(m_nOtherCallDTType == 0)
			m_chkOtherCallBefore.SetCheck(TRUE);
		else
			m_chkOtherCallAfter.SetCheck(TRUE);


		m_edtCashDeductingTaxFee.SetWindowText(m_strCashDTFee);
		m_btnCashDeductingTaxFee.SetChecked(m_bCashDTWon);

		m_edtBeforeMyCallCreditOnlineDeductingTaxFee.SetWindowText(m_strMyCallDTFee);
		m_btnBeforeMyCallCreditOnlineDeductingTaxWon.SetChecked(m_bMyCallDTWon);

		m_edtAfterMyCallCreditOnlineDeductingTaxFee.SetWindowText(m_strMyCallDTFee);
		m_btnAfterMyCallCreditOnlineDeductingTaxWon.SetChecked(m_bMyCallDTWon);

		m_edtBeforeOtherCallCreditOnlineDeductingTaxFee.SetWindowText(m_strOtherCallDTFee);
		m_btnBeforeOtherCallCreditOnlineDeductingWon.SetChecked(m_bOtherCallDTWon);

		m_edtAfterOtherCallCreditOnlineDeductingTaxFee.SetWindowText(m_strOtherCallDTFee);
		m_btnAfterOtherCallCreditOnlineDeductingWon.SetChecked(m_bOtherCallDTWon);
	}

	OnBnClickedMyCallBeforeCheck();
	OnBnClickedOtherCallBeforeCheck();

	OnBnClickedCashDeductingTaxFeeBtn();
}

void CRiderReportDlg::OnBnClickedSaveBtn2()
{
	SaveEtcList(&m_lstReport2);
}

void CRiderReportDlg::OnBnClickedCancelBtn()
{
	this->ShowWindow(SW_HIDE);
	OnOK();
}

void CRiderReportDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bAbleMove)
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CRiderReportDlg::OnBnClickedSendBtn()
{
	m_strRiderPhone = LF->GetRiderPhone(m_nRiderCompany, m_nRNo);
	
	CString sMsg; m_edtMsg.GetWindowText(sMsg);

	if(sMsg.IsEmpty())
	{
		MessageBox("전송하실 메세지를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	BOOL bSendPDA = FALSE;
	BOOL bSendSMS = FALSE;

	if(m_chkPDA.GetCheck() == BST_CHECKED)
		bSendPDA = SendPDA(sMsg);
	else
		bSendPDA = TRUE;

    if(m_chkSMS.GetCheck() == BST_CHECKED)    	
		bSendSMS = SendSMS(sMsg);
	else
		bSendSMS = TRUE;

	if((bSendSMS == TRUE) && (bSendPDA == TRUE))
		MessageBox("전송하였습니다", "확인", MB_ICONINFORMATION);

}

BOOL CRiderReportDlg::SendPDA(CString sMsg)
{
	UpdateData(TRUE);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "edit_rider_msg4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, sMsg.GetLength(), sMsg);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);

	return pCmd.Execute();
}

BOOL CRiderReportDlg::SendSMS(CString strMsg)
{
	if(m_strRiderPhone.IsEmpty() || m_strRiderPhone.Left(2) != "01") 
	{
		MessageBox("기사 전화번호가 존재하지 않거나, 휴대폰 번호가 아닙니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return LF->SendSmsNew(m_ci.m_nCompanyCode, 777, m_strRiderPhone, m_ci.m_strOfficePhone, strMsg, "접수프로그램(기사입금)", "", "", TRUE);
}

void CRiderReportDlg::OnEnChangeMsgEdit()
{
	CString strMsg, strCount;
	m_edtMsg.GetWindowText(strMsg);
	strCount.Format("글자수: %d", strMsg.GetLength());
	m_stcCount.SetWindowText(strCount);
}

void CRiderReportDlg::MakeMsg()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_info_by_incomday_1");

	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	BOOL bWeeklyDeposit, bSameRiderIncomeDay;
	CString sTakeDate;
	long nRiderIncomeDay;

	pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
	pRs.GetFieldValue("bSameRiderIncomeDay", bSameRiderIncomeDay);
	pRs.GetFieldValue("sTakeDate", sTakeDate);
	pRs.GetFieldValue("nRiderIncomeDay", nRiderIncomeDay);

	COleDateTime dtMainDate(atoi(sTakeDate.Left(4)), atoi(sTakeDate.Mid(4,2)), atoi(sTakeDate.Right(2)), 0, 0, 0);

	COleDateTime dtIncomeDate = LF->GetCompareDate(bWeeklyDeposit, dtMainDate, nRiderIncomeDay, bSameRiderIncomeDay);
	CString sMsg = "";

	sMsg.Format("%d월%d일", dtIncomeDate.GetMonth(), dtIncomeDate.GetDay());
	sMsg += "은 지입금 입금일입니다.";

 
	CString sTotal; m_edtTotal.GetWindowText(sTotal);
	CString sTakeTotal; m_edtTakeTotal.GetWindowText(sTakeTotal);
	CString sGiveTotal; m_edtGiveTotal.GetWindowText(sGiveTotal);

	sTotal.Replace(",", "");
	sTakeTotal.Replace(",", "");
	sGiveTotal.Replace(",", "");
 
	sMsg += sGiveTotal + "-" +  sTakeTotal;

	if(atoi(sTotal) > 0)
		sMsg += " 최종 " + sTotal + "입금하시길 바랍니다.";
	else if(atoi(sTotal) < 0)
	{
		sTotal.Replace("-", "");
		sMsg += " 최종 " + sTotal + "입금예정입니다.";
	}
	else
		sMsg += " 최종금액 0원입니다.";

	m_edtMsg.SetWindowText(sMsg);
	OnEnChangeMsgEdit();
}

void CRiderReportDlg::OnEnChangeCouponPlusEdit()
{ 
	CString strCouponCharge; m_edtCoupon.GetWindowText(strCouponCharge);
	strCouponCharge.Replace(",", "");

	CString strCouponPlus; m_edtCouponPlus.GetWindowText(strCouponPlus);
	strCouponPlus.Replace(",", "");

	m_edtCouponTotal.SetWindowText(LF->GetMyNumberFormat(atoi(strCouponCharge) * atoi(strCouponPlus)));

	RefreshCharge();
}

void CRiderReportDlg::SetTextStc()
{
	CString strTemp = "";
	strTemp.Format("이미 이체함 : %d건 %d원", m_nMyCallGiveToRiderCount, m_nMyCallGiveToRiderCharge); 
	m_stcMyGiveCharge.SetWindowText(strTemp);
	strTemp.Format("이미 이체함 : %d건 %d원", m_nOtherCallGiveToRiderCount, m_nOtherCallGiveToRiderCharge);
	m_stcOtherGiveCharge.SetWindowText(strTemp);
}

void CRiderReportDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}
