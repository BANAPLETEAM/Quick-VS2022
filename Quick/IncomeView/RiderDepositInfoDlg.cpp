// RiderDepositInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositInfoDlg.h"

#include "AddRiderBalanceDlg.h"
#include "MakeFixedDepositDlg.h"
#include "HalfInsertFixedDepositDlg.h"
#include "RiderReportDlg.h"
#include "RiderCreditDlg.h"
#include "RiderDepositEditHistoryDlg.h"
#include "DepositGroupDlg.h"
#include "RiderDepositGroupDlg.h"
// CRiderDepositInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderDepositInfoDlg, CMyDialog)
CRiderDepositInfoDlg::CRiderDepositInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderDepositInfoDlg::IDD, pParent)
{
	m_stRiderInfo.nFixedDeposit = 0;
	m_nPreDepositAllocateType = 0;
}

CRiderDepositInfoDlg::~CRiderDepositInfoDlg()
{
}

void CRiderDepositInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_SMS_CHECK,m_chkUseSMS);
	DDX_Control(pDX, IDC_BRANCH_AS_OTHER_CHECK, m_chkBranchAsOther);
	DDX_Control(pDX, IDC_PENALTY_CHECK, m_chkPenalty);

	DDX_Control(pDX, IDC_FIX_DEPOSIT_EDIT, m_edtFixDeposit);
	DDX_Control(pDX, IDC_DEPOSIT_EXPENSION_EDIT, m_edtDepositExpension);

	DDX_Control(pDX, IDC_INCOME_DAY_COMBO1, m_cmbIncomeDay1);
	DDX_Control(pDX, IDC_INCOME_DAY_COMBO2, m_cmbIncomeDay2);
	DDX_Control(pDX, IDC_CREDIT_REPORT_TYPE_COMBO, m_cmbreditReportType);
	DDX_Control(pDX, IDC_CUR_CHARGE_STC, m_stcCurCharge);

	DDX_Control(pDX, IDC_FIXED_DEPOSIT_REPORT_LIST, m_wndFixedReport);
	DDX_Control(pDX, IDC_HALF_INSERT_FIXEDEPOSIT_BTN, m_btnHalfInsertFixedDeposit);
	DDX_Control(pDX, IDC_MAKE_FIXEDEPOSIT_BTN, m_btnMakeFixedDeposit);
	DDX_Control(pDX, IDC_DELETE_FIXED_DEPOSIT_BTN, m_btnDeleteFixedDeposit);

	DDX_Control(pDX, IDC_STATE_STC, m_stcState);
	DDX_Control(pDX, IDC_CHANGE_STATE_BTN, m_btnChange);
	DDX_Control(pDX, IDC_SAVE_BTN, m_btnSave);
	DDX_Control(pDX, IDC_MINUS_BTN, m_btnMinus);
	DDX_Control(pDX, IDC_CLEAR_DEPOSIT_BTN, m_btnClearDepositBtn);

	DDX_Control(pDX, IDC_DEPOSIT_TYPE_COMBO1, m_cmbDepositType);
	DDX_Control(pDX, IDC_CASH_FEE_EDIT, m_edtCashFee);

	DDX_Control(pDX, IDC_MY_CALL_CREDIT_FEE_EDIT, m_edtMyCallCreditFee);
	DDX_Control(pDX, IDC_OTHER_CALL_CREDIT_FEE_EDIT, m_edtOtherCallCreditFee);

	DDX_Control(pDX, IDC_FEE_TYPE_COMBO1, m_cmbFeeType1);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO2, m_cmbFeeType2);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO3, m_cmbFeeType3);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO4, m_cmbFeeType4);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO5, m_cmbFeeType5);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO6, m_cmbFeeType6);
	DDX_Control(pDX, IDC_FEE_EDIT1, m_edtFee1);
	DDX_Control(pDX, IDC_FEE_EDIT2, m_edtFee2);
	DDX_Control(pDX, IDC_FEE_EDIT3, m_edtFee3);
	DDX_Control(pDX, IDC_FEE_EDIT4, m_edtFee4);
	DDX_Control(pDX, IDC_FEE_EDIT5, m_edtFee5);
	DDX_Control(pDX, IDC_FEE_EDIT6, m_edtFee6);
	DDX_Control(pDX, IDC_CHARGE_EDT1, m_edtCharge1);
	DDX_Control(pDX, IDC_CHARGE_EDT2, m_edtCharge2);
	DDX_Control(pDX, IDC_CHARGE_EDT3, m_edtCharge3);
	DDX_Control(pDX, IDC_CHARGE_EDT4, m_edtCharge4);
	DDX_Control(pDX, IDC_CHARGE_EDT5, m_edtCharge5);
	DDX_Control(pDX, IDC_CHARGE_EDT6, m_edtCharge6);
	DDX_Control(pDX, IDC_PERCENT_RADIO, m_rdoPercent);
	DDX_Control(pDX, IDC_MONTH_RADIO, m_rdoMonth);
	DDX_Control(pDX, IDC_DT_CASH_FEE_MONTH_EDIT, m_edtDTCashDeeMonth);
	DDX_Control(pDX, IDC_DT_CASH_TYPE_COMBO, m_cmbDTCashType);
	DDX_Control(pDX, IDC_DT_CASH_WON_COBMO, m_cmbDTCashWon);
	DDX_Control(pDX, IDC_DT_MY_CALL_CREDIT_TYPE_COMBO, m_cmbDTMyCallCreditType);
	DDX_Control(pDX, IDC_DT_MY_CALL_CREDIT_WON_COBMO, m_cmbDTMyCallCreditWon);
	DDX_Control(pDX, IDC_DT_OTHER_CALL_CREDIT_TYPE_COMBO, m_cmbDTOtherCallCreditType);
	DDX_Control(pDX, IDC_DT_OTHER_CALL_CREDIT_WON_COBMO, m_cmbDTOtherCallCreditWon);

	//DDX_CBIndex(pDX, IDC_DEPOSIT_TYPE_COMBO1, m_stRiderInfo.nDepositType);
	DDX_Check(pDX, IDC_BRANCH_AS_OTHER_CHECK, m_stRiderInfo.bBranchAsOtherCall);
	DDX_Check(pDX, IDC_PENALTY_CHECK, m_stRiderInfo.bPenaltyCharge);
	DDX_Text(pDX, IDC_FIX_DEPOSIT_EDIT, m_stRiderInfo.nFixedDeposit);
	DDX_CBIndex(pDX, IDC_INCOME_DAY_COMBO1, m_stRiderInfo.bWeeklyDeposit);
	DDX_CBIndex(pDX, IDC_INCOME_DAY_COMBO2, m_stRiderInfo.nPayMentDay);
	DDX_CBIndex(pDX, IDC_RIDER_INCOME_DAY_COMBO2, m_stRiderInfo.nRiderIncomeDay);
	DDX_CBIndex(pDX, IDC_CREDIT_REPORT_TYPE_COMBO, m_stRiderInfo.nCreditReportType);
	DDX_Text(pDX, IDC_DEPOSIT_EXPENSION_EDIT, m_stRiderInfo.nDepositExtensionDay);
	DDX_Check(pDX, IDC_USE_SMS_CHECK, m_stRiderInfo.bUseSmsNotify);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO1, m_stRiderInfo.nMyCallCashWon);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO2, m_stRiderInfo.nOtherCallCashWon);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO3, m_stRiderInfo.nMyCallCreditWon);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO4, m_stRiderInfo.nMyCallOnlineWon);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO5, m_stRiderInfo.nOtherCallCreditWon);
	DDX_CBIndex(pDX, IDC_FEE_TYPE_COMBO6, m_stRiderInfo.nOtherCallOnlineWon);
	DDX_Text(pDX, IDC_FEE_EDIT1, m_stRiderInfo.nMyCallCash);
	DDX_Text(pDX, IDC_FEE_EDIT2, m_stRiderInfo.nOtherCallCash);
	DDX_Text(pDX, IDC_FEE_EDIT3, m_stRiderInfo.nMyCallCredit);
	DDX_Text(pDX, IDC_FEE_EDIT4, m_stRiderInfo.nMyCallOnline);
	DDX_Text(pDX, IDC_FEE_EDIT5, m_stRiderInfo.nOtherCallCredit);
	DDX_Text(pDX, IDC_FEE_EDIT6, m_stRiderInfo.nOtherCallOnline);
	DDX_Text(pDX, IDC_CHARGE_EDT1, m_stRiderInfo.nMyCashApplyCharge);
	DDX_Text(pDX, IDC_CHARGE_EDT2, m_stRiderInfo.nOtherCashApplyCharge);
	DDX_Text(pDX, IDC_CHARGE_EDT3, m_stRiderInfo.nMyCreditApplyCharge);
	DDX_Text(pDX, IDC_CHARGE_EDT4, m_stRiderInfo.nMyOnlineApplyCharge);
	DDX_Text(pDX, IDC_CHARGE_EDT5, m_stRiderInfo.nOtherCreditApplyCharge);
	DDX_Text(pDX, IDC_CHARGE_EDT6, m_stRiderInfo.nOtherOnlineApplyCharge);
	DDX_Text(pDX, IDC_DT_CASH_FEE_MONTH_EDIT, m_stRiderInfo.nDT);
	DDX_CBIndex(pDX, IDC_DT_CASH_TYPE_COMBO, m_stRiderInfo.nCashDTType);
	DDX_CBIndex(pDX, IDC_DT_CASH_WON_COBMO, m_stRiderInfo.nCashDTWon);
	DDX_Text(pDX, IDC_CASH_FEE_EDIT, m_stRiderInfo.strCashDTFee);
	DDX_CBIndex(pDX, IDC_DT_MY_CALL_CREDIT_TYPE_COMBO, m_stRiderInfo.nMyCallDTType);
	DDX_CBIndex(pDX, IDC_DT_MY_CALL_CREDIT_WON_COBMO, m_stRiderInfo.nMyCallDTWon);
	DDX_Text(pDX, IDC_MY_CALL_CREDIT_FEE_EDIT, m_stRiderInfo.strMyCallDTFee);
	DDX_CBIndex(pDX, IDC_DT_OTHER_CALL_CREDIT_TYPE_COMBO, m_stRiderInfo.nOtherCallDTType);
	DDX_CBIndex(pDX, IDC_DT_OTHER_CALL_CREDIT_WON_COBMO, m_stRiderInfo.nOtherCallDTWon);
	DDX_Text(pDX, IDC_OTHER_CALL_CREDIT_FEE_EDIT, m_stRiderInfo.strOtherCallDTFee);

	DDX_Control(pDX, IDC_ETC_RE_EDIT1, m_edtEtcRe1);
	DDX_Control(pDX, IDC_ETC_RE_EDIT2, m_edtEtcRe2);
	DDX_Control(pDX, IDC_ETC_RE_EDIT3, m_edtEtcRe3);
	DDX_Control(pDX, IDC_ETC_RE_EDIT4, m_edtEtcRe4);

	DDX_Control(pDX, IDC_ETC_RE_CHARGE_EDIT1, m_edtEtcReCharge1);
	DDX_Control(pDX, IDC_ETC_RE_CHARGE_EDIT2, m_edtEtcReCharge2);
	DDX_Control(pDX, IDC_ETC_RE_CHARGE_EDIT3, m_edtEtcReCharge3);
	DDX_Control(pDX, IDC_ETC_RE_CHARGE_EDIT4, m_edtEtcReCharge4);

	DDX_Control(pDX, IDC_SMS_DELAY_DAY_COMBO, m_cmbSmsDelayDay);
	DDX_CBIndex(pDX, IDC_SMS_DELAY_DAY_COMBO, m_stRiderInfo.nSMSDealyDay);

	DDX_Control(pDX, IDC_DEPOSIT_ALLOCATE_TYPE_COMBO, m_cmbDepositAllocateType);
	DDX_Control(pDX, IDC_RIDER_INCOME_DAY_COMBO1, m_cmbRiderIncomeDay1);
	DDX_Control(pDX, IDC_RIDER_INCOME_DAY_COMBO2, m_cmbRiderIncomeDay2);

	DDX_CBIndex(pDX, IDC_RIDER_INCOME_DAY_COMBO1, m_stRiderInfo.nSameRiderIncomeDay);
	DDX_Control(pDX, IDC_EDIT_LOG_BTN, m_btnEditlog);

	DDX_Control(pDX, IDC_ALLOC_MIN_CHARGE_EDIT, m_edtAllocMinCharge);
	DDX_Text(pDX, IDC_ALLOC_MIN_CHARGE_EDIT, m_stRiderInfo.nAllocMinCharge);

	DDX_Text(pDX, IDC_MY_CALL_RATE_TYPE_EDIT, m_strMyCallRateType);
	DDX_Control(pDX, IDC_MY_CALL_RATE_TYPE_EDIT, m_edtMyCallRateType);
	DDX_Text(pDX, IDC_OTHER_CALL_RATE_TYPE_EDIT, m_strOtherCallRateType);
	DDX_Control(pDX, IDC_OTHER_CALL_RATE_TYPE_EDIT, m_edtOtherCallRateType);
	DDX_Control(pDX, IDC_MYCALL_CHECK, m_chkMyCall);
	DDX_Control(pDX, IDC_OTHERCALL_CHECK, m_chkOtherCall);
	DDX_Control(pDX, IDC_MY_CALL_RATE_TYPE_BTN, m_btnMyCallRate);
	DDX_Control(pDX, IDC_OTHER_CALL_RATE_TYPE_BTN, m_btnOtherCallRate);
}


BEGIN_MESSAGE_MAP(CRiderDepositInfoDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_INCOME_DAY_COMBO1, OnCbnSelchangeIncomeDayCombo1)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_MINUS_BTN, OnBnClickedMinusBtn)
	ON_BN_CLICKED(IDC_CLEAR_DEPOSIT_BTN, OnBnClickedClearDepositBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_MAKE_FIXEDEPOSIT_BTN, OnBnClickedMakeFixedepositBtn)
	ON_BN_CLICKED(IDC_DELETE_FIXED_DEPOSIT_BTN, OnBnClickedDeleteFixedDepositBtn)
	ON_BN_CLICKED(IDC_HALF_INSERT_FIXEDEPOSIT_BTN, OnBnClickedHalfInsertFixedepositBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_FIXED_DEPOSIT_REPORT_LIST, OnReportItemDblClick)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_INCOME_COMPLETE_BTN, OnBnClickedIncomeCompleteBtn)
	ON_BN_CLICKED(IDC_NOT_REPORT_BTN, OnBnClickedNotReportBtn)
	ON_CBN_SELCHANGE(IDC_DEPOSIT_TYPE_COMBO1, OnCbnSelchangeDepositTypeCombo1)
	ON_BN_CLICKED(IDC_RIDER_CREDIT_BTN, OnBnClickedRiderCreditBtn)

	ON_BN_CLICKED(IDC_PERCENT_RADIO, OnBnClickedPercentRadio)
	ON_BN_CLICKED(IDC_MONTH_RADIO, OnBnClickedMonthRadio)
	ON_CBN_SELCHANGE(IDC_DEPOSIT_ALLOCATE_TYPE_COMBO, OnCbnSelchangeDepositAllocateTypeCombo)
	ON_BN_CLICKED(IDC_HELP_BTN, OnBnClickedHelpBtn)
	ON_BN_CLICKED(IDC_EDIT_LOG_BTN, OnBnClickedEditLogBtn)
	ON_BN_CLICKED(IDC_MY_CALL_RATE_TYPE_BTN, &CRiderDepositInfoDlg::OnBnClickedMyCallRateTypeBtn)
	ON_BN_CLICKED(IDC_OTHER_CALL_RATE_TYPE_BTN, &CRiderDepositInfoDlg::OnBnClickedOtherCallRateTypeBtn)
	ON_BN_CLICKED(IDC_MYCALL_CHECK, &CRiderDepositInfoDlg::OnBnClickedMycallCheck)
	ON_BN_CLICKED(IDC_OTHERCALL_CHECK, &CRiderDepositInfoDlg::OnBnClickedOthercallCheck)
END_MESSAGE_MAP()

// CRiderDepositInfoDlg 메시지 처리기입니다.

BOOL CRiderDepositInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	::InitRiderIncomeStruct(&m_stRiderInfo);
	CenterWindow();
	m_btnChange.InitButton(this);

	CString strCaption;
	strCaption =  "입금정산(";
	strCaption += m_strRName;
	strCaption += ")";
	SetWindowText(strCaption);

	m_edtEtcRe1.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcRe1.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "공제설정1", TRUE);
	m_edtEtcRe2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcRe2.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "공제설정2", TRUE);
	m_edtEtcRe3.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcRe3.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "공제설정3", TRUE);
	m_edtEtcRe4.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcRe4.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "공제설정4", TRUE);

	m_edtEtcReCharge1.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcReCharge1.SetTitle("입력하세요", TRUE);
	m_edtEtcReCharge2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcReCharge2.SetTitle("입력하세요", TRUE);
	m_edtEtcReCharge3.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcReCharge3.SetTitle("입력하세요", TRUE);
	m_edtEtcReCharge4.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtEtcReCharge4.SetTitle("입력하세요", TRUE);

	m_stRiderInfo.nCompany = m_nRiderCompany;
	m_stRiderInfo.nRNo = m_nRNo;

	InitRiderState();

	m_wndFixedReport.InsertColumn(0, "입금날짜", LVCFMT_LEFT, 115);
	m_wndFixedReport.InsertColumn(1, "지입날짜", LVCFMT_LEFT, 90);
	m_wndFixedReport.InsertColumn(2, "월납", LVCFMT_LEFT, 60);
	m_wndFixedReport.InsertColumn(3, "지입금", LVCFMT_RIGHT, 60);
	m_wndFixedReport.InsertColumn(4, "신용오더", LVCFMT_RIGHT, 60);
	m_wndFixedReport.InsertColumn(5, "집계시작", LVCFMT_LEFT, 55);
	m_wndFixedReport.InsertColumn(6, "집계끝", LVCFMT_LEFT, 55);
	m_wndFixedReport.InsertColumn(7, "상태", LVCFMT_CENTER, 70);
	m_wndFixedReport.InsertColumn(8, "입금자", LVCFMT_RIGHT, 70);
	m_wndFixedReport.InsertColumn(9, "최종금액(지입금-신용오더)", LVCFMT_RIGHT, 160);
	m_wndFixedReport.InsertColumn(10, "적요", LVCFMT_LEFT, 160);

	m_wndFixedReport.Populate();

	RefreshFixedList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderDepositInfoDlg::RefreshFixedList()
{
	m_wndFixedReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);

	CMkCommand pCmd(m_pMkDb, "select_fixeddeposit_one_rider");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	long nID, nRNo, nFixedDeposit, nWNo, nState, nCreditOrderSum;
	CString sRName, sTakeDate, sEtc;
	BOOL bWeeklyDeposit;
	COleDateTime dtGenerate, dtCreditOrderStart, dtCreditOrderEnd;

	char buffer[20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
		pRs.GetFieldValue("sTakeDate", sTakeDate);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nCreditOrderSum", nCreditOrderSum);
		pRs.GetFieldValue("dtCreditOrderStart", dtCreditOrderStart);
		pRs.GetFieldValue("dtCreditOrderEnd", dtCreditOrderEnd);
		pRs.GetFieldValue("sEtc", sEtc);
	
		m_wndFixedReport.InsertItem(i, dtGenerate.Format("%Y-%m-%d %H:%M"));
		m_wndFixedReport.SetItemText(i, 1, sTakeDate.Left(4) + "-" + sTakeDate.Mid(4, 2) + "-" + sTakeDate.Right(2));
		m_wndFixedReport.SetItemText(i, 2, bWeeklyDeposit == TRUE ? "주납" : "월납");
		m_wndFixedReport.SetItemText(i, 3, ::GetMyNumberFormat(nFixedDeposit));
		m_wndFixedReport.SetItemText(i, 4, ::GetMyNumberFormat(nCreditOrderSum));
		m_wndFixedReport.SetItemText(i, 5, dtCreditOrderStart.Format("%y-%m-%d"));
		m_wndFixedReport.SetItemText(i, 6, dtCreditOrderEnd.Format("%y-%m-%d"));

		if(nState == 0)
			m_wndFixedReport.SetItemText(i, 7, "미정산");
		else if(nState == 1)
			m_wndFixedReport.SetItemText(i, 7, "정산완료");
		else if(nState == 2)
			m_wndFixedReport.SetItemText(i, 7, "입금완료");
		
		m_wndFixedReport.SetItemText(i, 8, nWNo == -1 ? "서버" : itoa(nWNo, buffer, 10));
		m_wndFixedReport.SetItemText(i, 9, ::GetMyNumberFormat(nFixedDeposit - nCreditOrderSum));
		m_wndFixedReport.SetItemText(i, 10, sEtc);

		m_wndFixedReport.SetItemData(i, nID);

		pRs.MoveNext();
	}

	m_wndFixedReport.Populate();
}

void CRiderDepositInfoDlg::InitRiderState()
{
	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_info_5");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	//long nBalance, nTodaySave, nMyCallRate, nOtherCallRate, nPayMentDay, nCreditReportType, nDepositExtensionDay, nFixedDeposit, nDepositType;
	//BOOL bPenaltyCharge, bWeeklyDeposit, bUseSMSNotify, bBranchAsOtherCall;
 //   COleDateTime dtNextDeposit;
//	char buffer[20];

	//BOOL bUseDT, bCashDTWon, bMyCallDTWon, bOtherCallDTWon;
	//long nCashDTType,nMyCallDTType, nOtherCallDTType;
	//CString sCashDTFee, sMyCallDTFee, sOtherCallDTFee;

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() < 1)
	{
		//MessageBox("지입금액이 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nBalance;
	long nFixedDeposit;

	pRs.GetFieldValue("nDepositType", m_stRiderInfo.nDepositType);
	pRs.GetFieldValue("nDepositAllocateType", m_stRiderInfo.nDepositAllocateType);
	pRs.GetFieldValue("nBalance", nBalance);
	pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
	m_stRiderInfo.nFixedDeposit = nFixedDeposit;
	pRs.GetFieldValue("bPenaltyCharge", m_stRiderInfo.bPenaltyCharge);
	pRs.GetFieldValue("bWeeklyDeposit", m_stRiderInfo.bWeeklyDeposit);
	pRs.GetFieldValue("nPaymentDay", m_stRiderInfo.nPayMentDay);
	pRs.GetFieldValue("nCreditReportType", m_stRiderInfo.nCreditReportType);
	pRs.GetFieldValue("bUseSMSNotify", m_stRiderInfo.bUseSmsNotify);
	pRs.GetFieldValue("nSMSDelayDay", m_stRiderInfo.nSMSDealyDay);
	pRs.GetFieldValue("nDepositExtensionDay", m_stRiderInfo.nDepositExtensionDay);
	pRs.GetFieldValue("bBranchAsOtherCall", m_stRiderInfo.bBranchAsOtherCall);
	pRs.GetFieldValue("nRiderIncomeDay", m_stRiderInfo.nRiderIncomeDay);

	long nDT;
	pRs.GetFieldValue("nDT", nDT);
	m_stRiderInfo.nDT = nDT;
	pRs.GetFieldValue("bUseDTPercent", m_stRiderInfo.bUseDTPercent);

	if(m_stRiderInfo.bUseDTPercent)
		m_rdoPercent.SetCheck(TRUE);
	else
		m_rdoMonth.SetCheck(TRUE);

	OnBnClickedPercentRadio();
					    
	pRs.GetFieldValue("bCashDTWon1", m_stRiderInfo.nCashDTWon);
	pRs.GetFieldValue("nCashDTType", m_stRiderInfo.nCashDTType);
	pRs.GetFieldValue("sCashDTFee", m_stRiderInfo.strCashDTFee);
	pRs.GetFieldValue("bMyCallDTWon1", m_stRiderInfo.nMyCallDTWon);
	pRs.GetFieldValue("nMyCallDTType", m_stRiderInfo.nMyCallDTType);
	pRs.GetFieldValue("sMyCallDTFee", m_stRiderInfo.strMyCallDTFee);
	pRs.GetFieldValue("nOtherCallDTType", m_stRiderInfo.nOtherCallDTType);
	pRs.GetFieldValue("bOtherCallDTWon1", m_stRiderInfo.nOtherCallDTWon);
	pRs.GetFieldValue("sOtherCallDTFee", m_stRiderInfo.strOtherCallDTFee);

	pRs.GetFieldValue("bMyCallCashWon1", m_stRiderInfo.nMyCallCashWon);
	pRs.GetFieldValue("nMyCallCash", m_stRiderInfo.nMyCallCash);
	pRs.GetFieldValue("bOtherCallCashWon1", m_stRiderInfo.nOtherCallCashWon);
	pRs.GetFieldValue("nOtherCallCash", m_stRiderInfo.nOtherCallCash);
	pRs.GetFieldValue("bMyCallCreditWon1", m_stRiderInfo.nMyCallCreditWon);
	pRs.GetFieldValue("nMyCallCredit", m_stRiderInfo.nMyCallCredit);
	pRs.GetFieldValue("bOtherCallCreditWon1", m_stRiderInfo.nOtherCallCreditWon);
	pRs.GetFieldValue("nOtherCallCredit", m_stRiderInfo.nOtherCallCredit);
	pRs.GetFieldValue("bMyCallOnlineWon1", m_stRiderInfo.nMyCallOnlineWon);
	pRs.GetFieldValue("nMyCallOnline", m_stRiderInfo.nMyCallOnline);
	pRs.GetFieldValue("bOtherCallOnlineWon1", m_stRiderInfo.nOtherCallOnlineWon);
	pRs.GetFieldValue("nOtherCallOnline", m_stRiderInfo.nOtherCallOnline);

	long nMyCashApplyCharge;
	long nOtherCashApplyCharge;
	long nMyCreditApplyCharge;
	long nMyOnlineApplyCharge;
	long nOtherCreditApplyCharge;
	long nOtherOnlineApplyCharge;

	pRs.GetFieldValue("nMyCashApplyCharge", nMyCashApplyCharge);
	pRs.GetFieldValue("nOtherCashApplyCharge", nOtherCashApplyCharge);
	pRs.GetFieldValue("nMyCreditApplyCharge", nMyCreditApplyCharge);
	pRs.GetFieldValue("nOtherCreditApplyCharge", nOtherCreditApplyCharge);
	pRs.GetFieldValue("nMyOnlineApplyCharge", nMyOnlineApplyCharge);
	pRs.GetFieldValue("nOtherOnlineApplyCharge", nOtherOnlineApplyCharge);

	m_stRiderInfo.nMyCashApplyCharge = nMyCashApplyCharge;
	m_stRiderInfo.nOtherCashApplyCharge = nOtherCashApplyCharge;
	m_stRiderInfo.nMyCreditApplyCharge = nMyCreditApplyCharge;
	m_stRiderInfo.nOtherCreditApplyCharge = nOtherCreditApplyCharge;
	m_stRiderInfo.nMyOnlineApplyCharge = nMyOnlineApplyCharge;
	m_stRiderInfo.nOtherOnlineApplyCharge = nOtherOnlineApplyCharge;

   	pRs.GetFieldValue("sEtc", m_stRiderInfo.strEtc);
	pRs.GetFieldValue("sEtcCharge", m_stRiderInfo.strEtcCharge);

	//pRs.GetFieldValue("bUseDepositGroup", m_stRiderInfo.bUseDepositGroup);
	//pRs.GetFieldValue("nDepositGroup", m_stRiderInfo.nDepositRateGroup);
	//pRs.GetFieldValue("sDepositRateGroup", m_sDepositRateGroup);

	pRs.GetFieldValue("nMyCallRateType", m_stRiderInfo.nMyCallRateType);
	pRs.GetFieldValue("sMyCallRateType", m_strMyCallRateType);
	pRs.GetFieldValue("nOtherCallRateType", m_stRiderInfo.nOtherCallRateType);
	pRs.GetFieldValue("sOtherCallRateType", m_strOtherCallRateType);

	pRs.GetFieldValue("nAllocMinCharge", m_stRiderInfo.nAllocMinCharge);

	SetEtcEdit(m_stRiderInfo.strEtc, m_stRiderInfo.strEtcCharge);

	//m_stRiderInfo.nDepositType = m_stRiderInfo.nDepositType / 10; 

	m_nPreDepositAllocateType = m_stRiderInfo.nDepositAllocateType;
	m_cmbDepositType.SetCurSel(::GetDepositTypeToComboSel(m_stRiderInfo.nDepositType));
	m_cmbDepositAllocateType.SetCurSel(::GetDepositAllocateTypeToComboSel(m_stRiderInfo.nDepositAllocateType));

	m_chkMyCall.SetCheck(m_stRiderInfo.nMyCallRateType);
	m_chkOtherCall.SetCheck(m_stRiderInfo.nOtherCallRateType);

    InitControl();
	OnCbnSelchangeIncomeDayCombo1();
	UpdateData(FALSE); 

	if(m_stRiderInfo.nDepositType == WEEKLY_DEPOSIT_TYPE) //주납
	{		
		m_cmbIncomeDay2.SetCurSel(m_stRiderInfo.nPayMentDay);
		m_cmbRiderIncomeDay2.SetCurSel(m_stRiderInfo.nRiderIncomeDay);
	}
	else if(m_stRiderInfo.nDepositType == MONTHLY_DEPOSIT_TYPE)
	{
		m_cmbRiderIncomeDay2.SetCurSel(m_stRiderInfo.nRiderIncomeDay-1);
		m_cmbIncomeDay2.SetCurSel(m_stRiderInfo.nPayMentDay-1);
	}

	m_cmbRiderIncomeDay1.SetCurSel(m_stRiderInfo.nSameRiderIncomeDay);

	//m_edtFixDeposit.SetWindowText(itoa(m_stRiderInfo.nFixedDeposit, buffer, 10)); //위에서이상하게찍힘
	m_stcCurCharge.SetWindowText(::GetMyNumberFormat(nBalance));
}

void CRiderDepositInfoDlg::OnCbnSelchangeIncomeDayCombo1()
{
	long nCurSel = m_cmbDepositType.GetCurSel();

	m_cmbRiderIncomeDay1.ResetContent();

	if(nCurSel == 0)
	{
		m_cmbRiderIncomeDay1.InsertString(0, "당월");
		m_cmbRiderIncomeDay1.InsertString(1, "익월");
		m_cmbRiderIncomeDay1.EnableWindow(TRUE);
		m_cmbIncomeDay2.EnableWindow(TRUE);
		m_cmbRiderIncomeDay2.EnableWindow(TRUE);
		m_cmbRiderIncomeDay1.SetCurSel(0);
	}
	else if(nCurSel == 1)
	{
		m_cmbRiderIncomeDay1.InsertString(0, "금주");
		m_cmbRiderIncomeDay1.InsertString(1, "다음주");
		m_cmbRiderIncomeDay1.EnableWindow(TRUE);
		m_cmbIncomeDay2.EnableWindow(TRUE);
		m_cmbRiderIncomeDay2.EnableWindow(TRUE);
		m_cmbRiderIncomeDay1.SetCurSel(0);
	}
	else
	{
		m_cmbRiderIncomeDay1.EnableWindow(FALSE);
		m_cmbIncomeDay2.EnableWindow(FALSE);
		m_cmbRiderIncomeDay2.EnableWindow(FALSE);
	}
	
	UINT RES[] = {IDC_INCOME_DAY_COMBO2,IDC_RIDER_INCOME_DAY_COMBO2};

	for(int i=0; i<2; i++)
	{
		CComboBox *pBox =  (CComboBox*)GetDlgItem(RES[i]);
		pBox->ResetContent();

		if(m_cmbIncomeDay1.GetCurSel() == 0) //월
		{
			char buffer[10];

			for(int i=0; i<31; i++)
			{
				pBox->InsertString(i, itoa(i+1, buffer, 10));
			}
		}
		else if(m_cmbIncomeDay1.GetCurSel() == 1)// 주
		{
			CString sDay[] = {"일", "월", "화", "수", "목", "금", "토"};

			for(int i=0; i<7; i++)
			{
				pBox->InsertString(i, sDay[i]);            
			}
		}
		else
		{
			pBox->SetCurSel(-1);
			continue;
		}

		pBox->SetCurSel(0);
	}
/*
	m_cmbIncomeDay2.ResetContent();

	if(m_cmbIncomeDay1.GetCurSel() == 0) //월
	{
		char buffer[10];

		for(int i=0; i<31; i++)
		{
			m_cmbIncomeDay2.InsertString(i, itoa(i+1, buffer, 10));
		}
	}
	else if(m_cmbIncomeDay1.GetCurSel() == 1)// 주
	{
		CString sDay[] = {"일", "월", "화", "수", "목", "금", "토"};

		for(int i=0; i<7; i++)
		{
			m_cmbIncomeDay2.InsertString(i, sDay[i]);            
		}
	}
	else
	{
		m_cmbIncomeDay2.SetCurSel(-1);
		return;
	}

	m_cmbIncomeDay2.SetCurSel(0);
*/
}

void CRiderDepositInfoDlg::OnBnClickedSaveBtn()
{
	CAddRiderBalanceDlg dlg;
	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
    dlg.m_strRName = m_strRName;    
	dlg.m_bAdd = TRUE;

	if(dlg.DoModal() == IDOK)
	{
		InitRiderState();
	}
}

void CRiderDepositInfoDlg::OnBnClickedMinusBtn()
{
	CAddRiderBalanceDlg dlg;
	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_strRName = m_strRName;    
	dlg.m_bAdd = FALSE;
	
	if(dlg.DoModal() == IDOK)
	{
		InitRiderState();
	}
}

void CRiderDepositInfoDlg::OnBnClickedClearDepositBtn()
{

	CString str;
	str.Format("%s 기사님의 잔액을 0원으로 만듭니다", m_strRName);

	if(MessageBox(str, "확인", MB_YESNO) == IDYES)
	{
        CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_rider_balance_to_zero");

		pCmd.AddParameter(m_nRiderCompany);
		pCmd.AddParameter(m_nRNo);
		pCmd.AddParameter(m_strRName);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);

		if(!pRs.Execute(&pCmd)) return;

		InitRiderState();
   	}
}

void CRiderDepositInfoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_stRiderInfo.nDepositType = ::GetDepositTypeFromComboSel(m_cmbDepositType.GetCurSel());
	m_stRiderInfo.nDepositAllocateType = ::GetDepositAllocateTypeFromComboSel(m_cmbDepositAllocateType.GetCurSel());

	if(m_nPreDepositAllocateType != m_stRiderInfo.nDepositAllocateType)
	{
		CString str = "";
		str.Format("입금방식이 [%s]에서 [%s]로 변경 될 경우 정산을\r\n금일 날짜 기준으로 정산을 다시 하셔야 합니다\r \r계속 진행하시겠습니까?", 
			m_nPreDepositAllocateType == 0 ? "선입금" : "후입금", m_stRiderInfo.nDepositAllocateType == 0 ? "선입금" : "후입금");
		
		if(MessageBox(str, "확인", MB_ICONINFORMATION | MB_OKCANCEL) != IDOK)
			return;		
	}

	if(m_stRiderInfo.nDepositType == MONTHLY_DEPOSIT_TYPE)
	{
		m_stRiderInfo.nPayMentDay++;
		m_stRiderInfo.nRiderIncomeDay++; 
	}

	if(m_stRiderInfo.nDepositType == MONTHLY_DEPOSIT_TYPE || m_stRiderInfo.nDepositType == WEEKLY_DEPOSIT_TYPE)
	{
		if(m_stRiderInfo.nSameRiderIncomeDay == 0) // 당월
		{
			if(m_stRiderInfo.nPayMentDay > m_stRiderInfo.nRiderIncomeDay)
			{
				MessageBox("입금일의 날짜가 납입일의 날짜보다 큽니다", "확인", MB_ICONINFORMATION);
				return;
			}
		}
	}

	m_stRiderInfo.strEtc = "";
	m_stRiderInfo.strEtcCharge = "";

	GetEtcEdit(m_stRiderInfo.strEtc, m_stRiderInfo.strEtcCharge);

	if(m_rdoPercent.GetCheck())	
		m_stRiderInfo.bUseDTPercent = TRUE;
	else
		m_stRiderInfo.bUseDTPercent = FALSE;

	SaveIncomeInfo(&m_stRiderInfo, FALSE);

	OnOK();
}

void CRiderDepositInfoDlg::OnBnClickedMakeFixedepositBtn()
{
	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	CMakeFixedDepositDlg dlg;
	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_strRName = m_strRName;

	if(dlg.DoModal() == IDOK)
		RefreshFixedList();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRiderDepositInfoDlg::OnBnClickedDeleteFixedDepositBtn()
{
	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) 
	{
		MessageBox("삭제 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sDate = m_wndFixedReport.GetItemText(index, 1);
	CString sCharge = m_wndFixedReport.GetItemText(index, 9);

	CString str;
	str.Format("지입일 : %s, 금액 : %s원을 삭제 하시겠습니까?", sDate.Right(5), sCharge);

	if(MessageBox(str, "확인", MB_OKCANCEL) == IDOK)
	{
		long nID = (long)m_wndFixedReport.GetItemData(index);

		CMkCommand pCmd(m_pMkDb, "delete_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshFixedList();
	}
}

void CRiderDepositInfoDlg::OnBnClickedHalfInsertFixedepositBtn()
{
	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{
		MessageBox("부분 입금 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	CString str;
	m_wndFixedReport.GetItemText(index, 7);

	if(str == "미정산")
	{
		MessageBox("정산 먼저 하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(str == "입금완료")
	{
		MessageBox("입금완료 되었습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CHalfInsertFixedDepositDlg dlg;
	
	if(dlg.DoModal() == IDOK)
	{
        long nID = (long)m_wndFixedReport.GetItemData(index);

		CString sDepositCharge; sDepositCharge = m_wndFixedReport.GetItemText(index, 9);
		sDepositCharge.Replace(",", "");

        if(dlg.m_nCharge > _ttoi(sDepositCharge))
		{
			if(MessageBox("부분 수정 할 금액이 지입금보다 큽니다\r\n   진행하시겠습니까", "확인", MB_OKCANCEL) != IDOK)
				return;
		}

		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nCharge);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshFixedList();

	}
}

void CRiderDepositInfoDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return; 

	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	OpenRiderReportDlg();
}

void CRiderDepositInfoDlg::OpenRiderReportDlg()
{
	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);
	if(index == -1) return;

	long nID = (long)m_wndFixedReport.GetItemData(index);
	CString strStartDate = "20" + CString(m_wndFixedReport.GetItemText(index, 5));
	CString strEndDate = "20" + CString(m_wndFixedReport.GetItemText(index, 6));
	CString strFixedDeposit = m_wndFixedReport.GetItemText(index, 3);
	strFixedDeposit.Replace(",", "");
	long nFixedDeposit = _ttoi(strFixedDeposit);

	CString strState = m_wndFixedReport.GetItemText(index, 7);

	CRiderReportDlg dlg;
	dlg.m_nID = nID;
	dlg.m_strRName = m_strRName;

	if(strState == "정산완료" || strState == "입금완료")
		dlg.m_bComplete = TRUE;

	if(strStartDate == "20")
	{
		dlg.m_dtFrom = COleDateTime::GetCurrentTime();
		dlg.m_dtTo = COleDateTime::GetCurrentTime();
	}
	else
	{
		dlg.m_dtFrom = COleDateTime(_ttoi(strStartDate.Left(4)), _ttoi(strStartDate.Mid(5,2)), _ttoi(strStartDate.Right(2)), 0, 0, 0);
		dlg.m_dtTo = COleDateTime(_ttoi(strEndDate.Left(4)), _ttoi(strEndDate.Mid(5,2)), _ttoi(strEndDate.Right(2)), 23, 59, 59);
	}

	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_nFixedDepositCharge = nFixedDeposit;
	dlg.m_bAbleMove = TRUE;

	if(dlg.DoModal() == IDOK)
		RefreshFixedList();	
}

void CRiderDepositInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CRiderDepositInfoDlg::OnBnClickedIncomeCompleteBtn()
{
	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndFixedReport.GetItemText(index, 7);

	if(sState == "미정산")
	{
		MessageBox("정산먼저 완료하세요", "확인", MB_ICONINFORMATION);
		//OpenRiderReportDlg();
	}
	else if(sState == "정산완료")
	{
		long nID = (long)m_wndFixedReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 2);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshFixedList();
	}
	else if(sState == "입금완료")
	{
		return;
	}
} 

void CRiderDepositInfoDlg::OnBnClickedNotReportBtn()
{
	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndFixedReport.GetItemText(index, 7);

	if(sState == "미정산")
	{
		return;
	}
	else if(sState == "정산완료" || sState == "입금완료")
	{
		long nID = (long)m_wndFixedReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshFixedList();	
	}
}

void CRiderDepositInfoDlg::OnBnClickedReportCompleteBtn()
{
	long index = m_wndFixedReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndFixedReport.GetItemText(index, 7);

	if(sState == "미정산")
	{
		MessageBox("정산창을 이용하세요!", "확인", MB_ICONINFORMATION);
		return;
	}
	else if(sState == "입금완료")
	{
		long nID = (long)m_wndFixedReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshFixedList();	
	}
}


void CRiderDepositInfoDlg::OnCbnSelchangeDepositTypeCombo1()
{
	InitControl();
}

void CRiderDepositInfoDlg::InitControl()
{
	BOOL bEnable = FALSE; 
 
	if(m_cmbDepositType.GetCurSel() == 0) 
	{
		m_cmbIncomeDay1.SetCurSel(0);
		bEnable = TRUE;
	}
	else if(m_cmbDepositType.GetCurSel() == 1)
	{
		m_cmbIncomeDay1.SetCurSel(1);
		bEnable = TRUE;
	}
	else
	{
		m_cmbIncomeDay1.SetCurSel(-1);
		bEnable = FALSE;
	}

	OnCbnSelchangeIncomeDayCombo1();


	if(m_cmbDepositAllocateType.GetCurSel() == 0) //선입
	{
		m_cmbreditReportType.EnableWindow(TRUE);
		m_edtDepositExpension.EnableWindow(TRUE);
		m_chkUseSMS.EnableWindow(TRUE);
		m_cmbSmsDelayDay.EnableWindow(TRUE);
		m_chkBranchAsOther.EnableWindow(TRUE);
		m_chkPenalty.EnableWindow(TRUE);
		m_edtAllocMinCharge.EnableWindow(TRUE);
		m_chkMyCall.EnableWindow(TRUE);
		m_chkOtherCall.EnableWindow(TRUE);
		m_btnMyCallRate.EnableWindow(TRUE);
		m_btnOtherCallRate.EnableWindow(TRUE);
	}
	else // 후입
	{ 
		if(m_cmbDepositType.GetCurSel() == 3) //프로제
		{
			m_cmbreditReportType.EnableWindow(FALSE);
			m_edtDepositExpension.EnableWindow(FALSE);
			m_chkUseSMS.EnableWindow(FALSE);
			m_cmbSmsDelayDay.EnableWindow(FALSE);

			m_chkBranchAsOther.EnableWindow(TRUE);
			m_chkPenalty.EnableWindow(TRUE);		
			m_edtAllocMinCharge.EnableWindow(TRUE);
			m_chkMyCall.EnableWindow(TRUE);
			m_chkOtherCall.EnableWindow(TRUE);
			m_btnMyCallRate.EnableWindow(TRUE);
			m_btnOtherCallRate.EnableWindow(TRUE);
		}
		else
		{
			m_cmbreditReportType.EnableWindow(TRUE);
			m_edtDepositExpension.EnableWindow(TRUE);
			m_chkUseSMS.EnableWindow(TRUE);
			m_cmbSmsDelayDay.EnableWindow(TRUE);

			m_chkBranchAsOther.EnableWindow(FALSE);
			m_chkPenalty.EnableWindow(FALSE);

			m_edtAllocMinCharge.EnableWindow(FALSE);

			m_chkMyCall.EnableWindow(FALSE);
			m_chkOtherCall.EnableWindow(FALSE);
			m_btnMyCallRate.EnableWindow(FALSE);
			m_btnOtherCallRate.EnableWindow(FALSE);
		}
	}

	m_cmbFeeType1.EnableWindow(bEnable);
	m_cmbFeeType2.EnableWindow(bEnable);
	m_cmbFeeType3.EnableWindow(bEnable);
	m_cmbFeeType4.EnableWindow(bEnable);
	m_cmbFeeType5.EnableWindow(bEnable);
	m_cmbFeeType6.EnableWindow(bEnable);

	m_edtFee1.EnableWindow(bEnable);
	m_edtFee2.EnableWindow(bEnable);
	m_edtFee3.EnableWindow(bEnable);
	m_edtFee4.EnableWindow(bEnable);
	m_edtFee5.EnableWindow(bEnable);
	m_edtFee6.EnableWindow(bEnable);

	m_edtCharge1.EnableWindow(bEnable);
	m_edtCharge2.EnableWindow(bEnable);
	m_edtCharge3.EnableWindow(bEnable);
	m_edtCharge4.EnableWindow(bEnable);
	m_edtCharge5.EnableWindow(bEnable);
	m_edtCharge6.EnableWindow(bEnable);

	m_rdoPercent.EnableWindow(bEnable);
	m_rdoMonth.EnableWindow(bEnable);
	m_edtDTCashDeeMonth.EnableWindow(bEnable);

	m_cmbDTCashType.EnableWindow(bEnable);
	m_cmbDTCashWon.EnableWindow(bEnable);
	m_edtCashFee.EnableWindow(bEnable);

	m_cmbDTMyCallCreditType.EnableWindow(bEnable);
	m_cmbDTMyCallCreditWon.EnableWindow(bEnable);
	m_edtMyCallCreditFee.EnableWindow(bEnable);

	m_cmbDTOtherCallCreditType.EnableWindow(bEnable);
	m_cmbDTOtherCallCreditWon.EnableWindow(bEnable);
	m_edtOtherCallCreditFee.EnableWindow(bEnable);
 
	if(m_cmbDepositType.GetCurSel() < 3)
		m_edtFixDeposit.EnableWindow(TRUE);
	else
		m_edtFixDeposit.EnableWindow(FALSE);
}


void CRiderDepositInfoDlg::OnBnClickedRiderCreditBtn()
{
	CRiderCreditDlg dlg;
	dlg.m_nCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_sRName = m_strRName;
	dlg.DoModal();
}

void CRiderDepositInfoDlg::OnBnClickedPercentRadio()
{
	if(m_rdoPercent.GetCheck())
		m_rdoMonth.SetCheck(!m_rdoPercent.GetCheck());

	DTChangeControl();
}

void CRiderDepositInfoDlg::DTChangeControl()
{
	BOOL bCheck = m_rdoPercent.GetCheck();

	m_edtDTCashDeeMonth.EnableWindow(!bCheck);

	m_cmbDTCashType.EnableWindow(bCheck);
	m_cmbDTCashWon.EnableWindow(bCheck);
	m_edtCashFee.EnableWindow(bCheck);

	m_cmbDTMyCallCreditType.EnableWindow(bCheck);
	m_cmbDTMyCallCreditWon.EnableWindow(bCheck);
	m_edtMyCallCreditFee.EnableWindow(bCheck);

	m_cmbDTOtherCallCreditType.EnableWindow(bCheck);
	m_cmbDTOtherCallCreditWon.EnableWindow(bCheck);
	m_edtOtherCallCreditFee.EnableWindow(bCheck);        
}

void CRiderDepositInfoDlg::OnBnClickedMonthRadio()
{
	if(m_rdoMonth.GetCheck())
		m_rdoPercent.SetCheck(!m_rdoMonth.GetCheck());
	
	DTChangeControl();
}

void CRiderDepositInfoDlg::SetEtcEdit(CString strEtc, CString strEtcCharge)
{
	long nStartEtcPos = 0;
	long nDestEtcPos = 0;

	long nStartEtcChargePos = 0;
	long nDestEtcChargePos = 0;

	long nItem = 0;

	while(1)
	{
		nDestEtcPos = strEtc.Find(";", nStartEtcPos);
		nDestEtcChargePos = strEtcCharge.Find(";", nStartEtcChargePos);

		if(nDestEtcPos == -1) break;

		CString strEtcPart = strEtc.Mid(nStartEtcPos, nDestEtcPos - nStartEtcPos);
		CString strEtcChargePart = strEtcCharge.Mid(nStartEtcChargePos, nDestEtcChargePos - nStartEtcChargePos);

		CEdit *pEtcEdt = (CEdit*)GetDlgItem(IDC_ETC_RE_EDIT1 + nItem);
		CEdit *pEtcChargeEdt = (CEdit*)GetDlgItem(IDC_ETC_RE_CHARGE_EDIT1 + nItem);

		pEtcEdt->SetWindowText(strEtcPart);
		pEtcChargeEdt->SetWindowText(strEtcChargePart);


		nItem++;

		nStartEtcPos = nDestEtcPos + 1;
		nStartEtcChargePos = nDestEtcChargePos + 1;
	}
}

void CRiderDepositInfoDlg::GetEtcEdit(CString &strEtc, CString &strEtcCharge)
{
	for(int i=0; i<4; i++)
	{
		CString strEtc1, strEtcCharge1;
		CEdit *pEtcEdt = (CEdit*)GetDlgItem(IDC_ETC_RE_EDIT1 + i);
		CEdit *pEtcChargeEdt = (CEdit*)GetDlgItem(IDC_ETC_RE_CHARGE_EDIT1 + i);

		pEtcEdt->GetWindowText(strEtc1);
		strEtc += strEtc1 + ";";
		pEtcChargeEdt->GetWindowText(strEtcCharge1);
		strEtcCharge += strEtcCharge1 + ";";
	}
}

void CRiderDepositInfoDlg::OnCbnSelchangeDepositAllocateTypeCombo()
{
	InitControl();
}

void CRiderDepositInfoDlg::OnBnClickedHelpBtn()
{
//	CRiderDepositHelpDlg dlg;
//	dlg.DoModal();
}


void CRiderDepositInfoDlg::OnBnClickedEditLogBtn()
{
	CRiderDepositEditHistoryDlg dlg;
	dlg.m_nRiderCompany = m_nRiderCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.DoModal();
}

void CRiderDepositInfoDlg::OnBnClickedMyCallRateTypeBtn()
{
	CRiderDepositGroupDlg dlg;
	dlg.m_bSelectMode = TRUE;
	dlg.m_nCompany = m_stRiderInfo.nCompany;
	dlg.m_nDepositRateGroup = m_stRiderInfo.nMyCallRateType;

	if(dlg.DoModal() == IDOK)
	{
		m_stRiderInfo.nMyCallRateType = dlg.m_nDepositRateGroup;
		m_edtMyCallRateType.SetWindowText(dlg.m_strDepositRateGroupName);
	}
}

void CRiderDepositInfoDlg::OnBnClickedOtherCallRateTypeBtn()
{
	CRiderDepositGroupDlg dlg;
	dlg.m_bSelectMode = TRUE;
	dlg.m_nCompany = m_stRiderInfo.nCompany;
	dlg.m_nDepositRateGroup = m_stRiderInfo.nOtherCallRateType;

	if(dlg.DoModal() == IDOK)
	{
		m_stRiderInfo.nOtherCallRateType = dlg.m_nDepositRateGroup;
		m_edtOtherCallRateType.SetWindowText(dlg.m_strDepositRateGroupName);
	}
}

void CRiderDepositInfoDlg::OnBnClickedMycallCheck()
{
	if(m_chkMyCall.GetCheck() == FALSE)
	{
		m_edtMyCallRateType.SetWindowText("");
		m_stRiderInfo.nMyCallRateType = 0;
	}
}

void CRiderDepositInfoDlg::OnBnClickedOthercallCheck()
{
	if(m_chkOtherCall.GetCheck() == FALSE)
	{
		m_edtOtherCallRateType.SetWindowText("");
		m_stRiderInfo.nOtherCallRateType = 0;
	}
}
