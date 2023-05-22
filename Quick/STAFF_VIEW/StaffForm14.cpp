// StaffForm14.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "StaffForm14.h"
#include "KingoHttp.h"
#include "FileUpload.h"
#include "RiderDepositGroupDlg.h"
#include "RiderDepositInfoDlg.h"
#include "AllocateLimitDlg1.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"
#include "RiderCashLogDlg.h"
#include "RiderColorDlg.h"
#include "WorkStateChangeLogDlg.h"
#include "RiderInfoLogDlg.h"
#include "InsertNewCardDlg.h"
#include "RiderDepositLogDlg.h"
#include "RiderIncomeDlg.h"
#include "RiderInitLogDlg.h"
#include "LoadInsuranceDlg.h"
#include "LoadInsurance.h"

#define ID_UPLOAD_PIC 100
#define ID_DELETE_PIC 101

#define TIMER_REFRESH_JOB 1000

#define FTP_IP "211.172.242.163"
//#define FTP_URL_ID_PICTURE "quick3/images/IDpicture/"
#define FTP_URL_ID_PICTURE "/IDpicture"

extern CMkDatabase *m_pMkDb4DrvLic;
extern BOOL ConnectDrvLicSvr();

IMPLEMENT_DYNCREATE(CStaffForm14, CMyFormView)

#define ID_MENU_ADD_JOB 2000
#define ID_MENU_DELETE_JOB 3000

void CStaffForm14::InitData()
{
	m_nLastANo = ZERO;
	m_bLastAdminTable = FALSE;

	m_strName = "";
	m_strRNo = "";
	m_strMp = "";
	m_strPhone = "";
	m_strRT = "";
	m_strPDA = "";
	m_strBankOwner = "";
	m_strBankName = "";
	m_strBankAccount = "";
	m_strMarketLine = "";
	m_dtEnter =	COleDateTime::GetCurrentTime();
	m_strSSN1 = "";
	m_strSSN2 = "";
	m_strLicenceNo = "";
	m_strAddress = "";
	m_strMemo = "";
	m_strInnerMemo = "";
	m_strCarNo = "";
	m_bAuto = TRUE; 
	m_bBigAuto = TRUE;
	m_bDama = TRUE;
	m_bRabo = TRUE;
	m_bTruck= TRUE;
	m_bSedan = TRUE;
	m_bAll = TRUE;
	m_strIncome = "";
	m_strInnerMemo = "";
	m_strSearch = "";
	m_nMyCallRateType = ZERO;
	m_nOtherCallRateType = ZERO;
	m_bNotShowRightOrder = FALSE;
	m_strRtSerial = "";

	m_nLicenceValid = -1;
	m_bAddRiderMode = TRUE;
	m_strDailyReportCharge = "";
	m_dtIns = COleDateTime::GetCurrentTime();

	m_strTruckMyDepositRate = "15";
	m_strTruckOtherDepositRate = "15";

	m_pRiderDepositDlg = NULL;
}

CStaffForm14::CStaffForm14()
	: CMyFormView(CStaffForm14::IDD)
	, m_strDailyReportCharge(_T(""))
	, m_dtIns(COleDateTime::GetCurrentTime())
	, m_strCarNo(_T(""))
	, m_strAllocMinCharge(_T(""))
{
	InitData();
}

CStaffForm14::~CStaffForm14()
{
	if(m_lstReport.GetSafeHwnd())
		m_lstReport.SaveReportOrder("CStaffForm14", "m_lstReport");

	DELETE_OBJECT(m_pRiderDepositDlg);
}

void CStaffForm14::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);

	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_MP_EDIT, m_edtMp);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_RT_EDIT, m_edtRT);
	DDX_Control(pDX, IDC_PDA_EDIT, m_edtPDA);
	DDX_Control(pDX, IDC_BANK_OWNER_EDIT, m_edtBankOwner);
	DDX_Control(pDX, IDC_BANK_NAME_EDIT, m_edtBankName);
	DDX_Control(pDX, IDC_BANK_ACCOUNT_EDIT, m_edtBankAccount);
	DDX_Control(pDX, IDC_MARKET_LINE_EDIT, m_edtMarketLine);
	DDX_Control(pDX, IDC_ENTER_DT, m_dtpEnter);
	DDX_Control(pDX, IDC_SSN_EDIT1, m_edtSSN1);
	DDX_Control(pDX, IDC_SSN_EDIT2, m_edtSSN2);
	DDX_Control(pDX, IDC_LICENCE_COMBO, m_cmbLicence);
	DDX_Control(pDX, IDC_LICENCE_NO_EDIT, m_edtLicenceNo);
	DDX_Control(pDX, IDC_PDA_ALLOCATE_CHECK, m_chkPDAAllocate);
	DDX_Control(pDX, IDC_SMS_ALLOCATE_CHECK, m_chkSmsAllocate);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO, m_cmbCarType);
	DDX_Control(pDX, IDC_SHARE_LIMIT_COMBO, m_cmbShareLimit);
	DDX_Control(pDX, IDC_ALLOCATE_LIMIT_CHECK, m_chkAllocateLimit);
	DDX_Control(pDX, IDC_ALLOCATE_LIMIT_MINUTE_COMBO, m_cmbAllocateLimitMinute);
	DDX_Control(pDX, IDC_ALLOCATE_LIMIT_COUNT_COMBO, m_cmbAllocateLimitCount);
	DDX_Control(pDX, IDC_WORK_STATE_COMBO, m_cmbWorkState);
	DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_cmbAllocGroup);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_edtAddress);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);
	DDX_Control(pDX, IDC_INNER_MEMO_EDIT, m_edtInnerMemo);
	DDX_Control(pDX, IDC_AUTO_CHECK, m_chkAuto);
	DDX_Control(pDX, IDC_BIG_AUTO_CHECK, m_chkBigAuto);
	DDX_Control(pDX, IDC_DAMA_CHECK, m_chkDama);
	DDX_Control(pDX, IDC_RABO_CHECK, m_chkRabo);
	DDX_Control(pDX, IDC_TRUCK_CHECK, m_chkTruck);
	DDX_Control(pDX, IDC_ALL_CHECK, m_chkAll);
	DDX_Control(pDX, IDC_INCOME_EDIT, m_edtIncome);
	DDX_Control(pDX, IDC_INCOME_MEMO_EDIT, m_edtIncomeMemo);
	DDX_Control(pDX, IDC_INCOME_COMBO, m_cmbIncome);
	DDX_Control(pDX, IDC_DEPOSIT_TYPE_COMBO1, m_cmbDepositType);
	DDX_Control(pDX, IDC_DEPOSIT_ALLOCATE_TYPE_COMBO, m_cmbDepositAllocateType);
	DDX_Control(pDX, IDC_MYCALL_CHECK, m_chkMyCall);
	DDX_Control(pDX, IDC_OTHERCALL_CHECK, m_chkOtherCall);
	DDX_Control(pDX, IDC_CON_WORKING_COMBO, m_cmbConWorking);
	DDX_Control(pDX, IDC_SEARCH_RIDER_EDIT, m_edtSearch);

	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_RNO_EDIT, m_strRNo);
	DDX_Text(pDX, IDC_MP_EDIT, m_strMp);
	DDX_Text(pDX, IDC_PHONE_EDIT, m_strPhone);
	DDX_Text(pDX, IDC_RT_EDIT, m_strRT);
	DDX_Text(pDX, IDC_PDA_EDIT, m_strPDA);
	DDX_Text(pDX, IDC_BANK_OWNER_EDIT, m_strBankOwner);
	DDX_Text(pDX, IDC_BANK_NAME_EDIT, m_strBankName);
	DDX_Text(pDX, IDC_BANK_ACCOUNT_EDIT, m_strBankAccount);
	DDX_Text(pDX, IDC_MARKET_LINE_EDIT, m_strMarketLine);
	DDX_DateTimeCtrl(pDX, IDC_ENTER_DT, m_dtEnter);
	DDX_Text(pDX, IDC_SSN_EDIT1, m_strSSN1);
	DDX_Text(pDX, IDC_SSN_EDIT2, m_strSSN2);
	DDX_Text(pDX, IDC_LICENCE_NO_EDIT, m_strLicenceNo);
	DDX_Text(pDX, IDC_ADDRESS_EDIT, m_strAddress);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);
	DDX_Text(pDX, IDC_INNER_MEMO_EDIT, m_strInnerMemo);
	DDX_Check(pDX, IDC_AUTO_CHECK, m_bAuto);
	DDX_Check(pDX, IDC_BIG_AUTO_CHECK, m_bBigAuto);
	DDX_Check(pDX, IDC_DAMA_CHECK, m_bDama);
	DDX_Check(pDX, IDC_RABO_CHECK, m_bRabo);
	DDX_Check(pDX, IDC_TRUCK_CHECK, m_bTruck);
	DDX_Check(pDX, IDC_ALL_CHECK, m_bAll);
	DDX_Text(pDX, IDC_INCOME_EDIT, m_strIncome);
	DDX_Text(pDX, IDC_INCOME_MEMO_EDIT, m_strIncomeMemo);
	//DDX_Text(pDX, IDC_SEARCH_RIDER_EDIT, m_strSearch);

	DDX_Control(pDX, IDC_RT_SERIAL_EDIT, m_edtRtSerial);
	DDX_Text(pDX, IDC_RT_SERIAL_EDIT, m_strRtSerial);

	DDX_Control(pDX, IDC_MY_CALL_RATE_TYPE_EDIT, m_edtMyCallRateType);
	DDX_Control(pDX, IDC_OTHER_CALL_RATE_TYPE_EDIT, m_edtOtherCallRateType);
	DDX_Text(pDX, IDC_MY_CALL_RATE_TYPE_EDIT, m_strMyCallRateType);
	DDX_Text(pDX, IDC_OTHER_CALL_RATE_TYPE_EDIT, m_strOtherCallRateType);

	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, IDC_INCOME_BTN, m_btnIncome);
	DDX_Control(pDX, IDC_DAILY_DEPOSIT_CHARGE_EDIT, m_edtDailyDepositCharge);
	DDX_Control(pDX, IDC_NOT_SHOW_RIGHT_ORDER_CHECK2, m_chkNotShowRightOrder);
	DDX_Check(pDX, IDC_NOT_SHOW_RIGHT_ORDER_CHECK2, m_bNotShowRightOrder);
	DDX_Text(pDX, IDC_DAILY_DEPOSIT_CHARGE_EDIT, m_strDailyReportCharge);

	DDX_Control(pDX, IDC_JOB_REPORT, m_wndJobReport);	
	DDX_Control(pDX, IDC_BANK_ID_COMBO, m_cmbBankID);
	DDX_Control(pDX, IDC_MAX_WITH_DRAW_MONEY_PER_DAY_EDIT, m_edtMaxWithDrawMoneyPerDay);
	DDX_Control(pDX, IDC_MIN_LEFT_MONEY_FOR_WITH_DRAW_EDIT, m_edtMinLeftMoneyForWithDraw);
	DDX_Control(pDX, IDC_WITH_DRAW_TYPE_CHECK, m_chkWithDrawType);
	DDX_Control(pDX, IDC_INS_DT, m_dtlIns);
	DDX_DateTimeCtrl(pDX, IDC_INS_DT, m_dtIns);
	DDX_Control(pDX, IDC_INS_TYPE_COMBO, m_cmbInsType);

	DDX_Control(pDX, IDC_USE_RIDER_TAX_CHECK, m_chkUseRiderTax);	
	DDX_Control(pDX, IDC_AUTO_ALLOCATE_CHECK, m_chkAutoAllocate);
	DDX_Control(pDX, IDC_TRUCK_MY_DEPOSIT_RATE_EDIT, m_edtTruckMyDepositRate);
	DDX_Control(pDX, IDC_TRUCK_OTHER_DEPOSIT_RATE_EDIT, m_edtTruckOtherDepositRate);
	DDX_Text(pDX, IDC_TRUCK_MY_DEPOSIT_RATE_EDIT, m_strTruckMyDepositRate);
	DDX_Text(pDX, IDC_TRUCK_OTHER_DEPOSIT_RATE_EDIT, m_strTruckOtherDepositRate);
	DDX_Control(pDX, IDC_CARD_NUMBER_EDIT, m_edtCardNumber);
	DDX_Control(pDX, IDC_CAR_NO_EDIT, m_edtCarNo);
	DDX_Text(pDX, IDC_CAR_NO_EDIT, m_strCarNo);
	DDX_Control(pDX, IDC_ALLOC_MIN_CHARGE_CHECK, m_edtAllocMinCharge);
	DDX_Text(pDX, IDC_ALLOC_MIN_CHARGE_CHECK, m_strAllocMinCharge);

	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSearch);
	DDX_Control(pDX, IDC_INS_REGISTER_CHECK, m_chkInsNotRegister);
	DDX_Control(pDX, IDC_BUSINESS_CAR_COMBO, m_cmbBusinessCar);

	DDX_Control(pDX, IDC_SEDAN_CHECK, m_chkSedan);
	DDX_Check(pDX, IDC_SEDAN_CHECK, m_bSedan);
}

BEGIN_MESSAGE_MAP(CStaffForm14, CMyFormView)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_LIST_REPORT, OnReportColumnChangeChanged)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPORT, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CStaffForm14::OnBnClickedSearchBtn)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_LIST_REPORT, OnReportItemChange)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CStaffForm14::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_RIDER_CONFIDENCE_BTN, &CStaffForm14::OnBnClickedRiderConfidenceBtn)
	ON_BN_CLICKED(IDC_LICENSE_QUERY_BUTTON, &CStaffForm14::OnBnClickedLicenseQueryButton)
	ON_BN_CLICKED(IDC_RIDER_PIC_INSERT_BTN, &CStaffForm14::OnBnClickedRiderPicInsertBtn)
	ON_COMMAND(ID_UPLOAD_PIC, OnUploadPic)
	ON_COMMAND(ID_DELETE_PIC, OnDeletePic)
	ON_COMMAND(ID_SHOW_DEPOSIT_LOG, OnShowDepositLog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CStaffForm14::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_INCOME_BTN, &CStaffForm14::OnBnClickedIncomeBtn)
	ON_BN_CLICKED(IDC_MY_CALL_RATE_TYPE_BTN, &CStaffForm14::OnBnClickedMyCallRateTypeBtn)
	ON_BN_CLICKED(IDC_OTHER_CALL_RATE_TYPE_BTN, &CStaffForm14::OnBnClickedOtherCallRateTypeBtn)
	ON_CBN_SELCHANGE(IDC_INCOME_COMBO, &CStaffForm14::OnCbnSelchangeIncomeCombo)
	ON_BN_CLICKED(IDC_RIDER_PIC_INSERT_BTN2, &CStaffForm14::OnBnClickedRiderPicInsertBtn2)
	ON_BN_CLICKED(IDC_INCOME_SETTING_BTN, &CStaffForm14::OnBnClickedIncomeSettingBtn)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CStaffForm14::OnBnClickedButtonDelete)
	ON_EN_CHANGE(IDC_SEARCH_RIDER_EDIT, &CStaffForm14::OnEnChangeSaerchEdit)
	ON_BN_CLICKED(IDC_PDA_ALLOCATE_CHECK, &CStaffForm14::OnBnClickedPdaAllocateCheck)
	ON_BN_CLICKED(IDC_SMS_ALLOCATE_CHECK, &CStaffForm14::OnBnClickedSmsAllocateCheck)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_CHANGE_RIDER_COLOR, OnChangeRiderColor)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_CARD_INSERT_PRE, OnCardInsertPre)
	ON_COMMAND(ID_CARD_INSERT_NEW, OnCardInsertNew)
	ON_COMMAND(ID_CARD_RELEASE, OnCardRelease)
	ON_COMMAND(ID_RIDER_INCOME, OnRiderIncome)
	ON_COMMAND(ID_CANCEL_TYPE_0, OnCancelType0)
	ON_COMMAND(ID_CANCEL_TYPE_1, OnCancelType1)
	ON_COMMAND(ID_CANCEL_TYPE_2, OnCancelType2)

	ON_BN_CLICKED(IDC_ALL_CHECK, &CStaffForm14::OnBnClickedAllCheck)
	ON_BN_CLICKED(IDC_AUTO_CHECK, &CStaffForm14::OnBnClickedAutoCheck)
	ON_BN_CLICKED(IDC_BIG_AUTO_CHECK, &CStaffForm14::OnBnClickedBigAutoCheck)
	ON_BN_CLICKED(IDC_DAMA_CHECK, &CStaffForm14::OnBnClickedDamaCheck)
	ON_BN_CLICKED(IDC_RABO_CHECK, &CStaffForm14::OnBnClickedRaboCheck)
	ON_BN_CLICKED(IDC_BAN_CHECK, &CStaffForm14::OnBnClickedBanCheck)
	ON_BN_CLICKED(IDC_TRUCK_CHECK, &CStaffForm14::OnBnClickedTruckCheck)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, &CStaffForm14::OnCbnSelchangeBranchCombo)
	ON_BN_CLICKED(IDC_MYCALL_CHECK, &CStaffForm14::OnBnClickedMycallCheck)
	ON_BN_CLICKED(IDC_OTHERCALL_CHECK, &CStaffForm14::OnBnClickedOthercallCheck)
	ON_CBN_SELCHANGE(IDC_CAR_TYPE_COMBO, &CStaffForm14::OnCbnSelchangeCarTypeCombo)
	ON_CBN_SELCHANGE(IDC_SEARCH_COMBO, &CStaffForm14::OnCbnSelchangeSearchCombo)

	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_JOB_ADD_BUTTON, &CStaffForm14::OnBnClickedJobAddButton)
	ON_BN_CLICKED(IDC_JOB_DELETE_BUTTON, &CStaffForm14::OnBnClickedJobDeleteButton)
	ON_WM_TIMER()
	ON_COMMAND_RANGE(ID_MENU_ADD_JOB, ID_MENU_ADD_JOB + 100, OnMenuAddJob)
	ON_COMMAND_RANGE(ID_MENU_DELETE_JOB, ID_MENU_DELETE_JOB + 100, OnMenuDeleteJob)
	ON_CBN_SELCHANGE(IDC_DEPOSIT_TYPE_COMBO1, &CStaffForm14::OnCbnSelchangeDepositTypeCombo1)
	ON_BN_CLICKED(IDC_6BAN_CHECK, &CStaffForm14::OnBnClicked6banCheck)
	ON_BN_CLICKED(IDC_CHANGE_LOG_BTN, &CStaffForm14::OnBnClickedChangeLogBtn)
	ON_CBN_SELCHANGE(IDC_CON_WORKING_COMBO, &CStaffForm14::OnCbnSelchangeConWorkingCombo)
	ON_BN_CLICKED(IDC_RIDER_INFO_LOG_BTN, &CStaffForm14::OnBnClickedRiderInfoLog)

	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER1, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER2, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER3, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER4, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER5, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER6, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER7, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER8, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER9, OnCardNumber)
	ON_COMMAND_RANGE_SINGLE(ID_CARD_NUMBER10, OnCardNumber)

	ON_EN_CHANGE(IDC_MEMO_EDIT, &CStaffForm14::OnEnChangeMemoEdit)
	ON_BN_CLICKED(IDC_INIT_LOG_BTN, &CStaffForm14::OnBnClickedInitLogBtn)
	ON_BN_CLICKED(IDC_LOAD_INSURANCE_BTN, &CStaffForm14::OnBnClickedLoadInsuranceBtn)
	ON_BN_CLICKED(IDC_INS_REGISTER_CHECK, &CStaffForm14::OnBnClickedInsRegisterCheck)
	ON_EN_CHANGE(IDC_SSN_EDIT1, &CStaffForm14::OnEnChangeSsnEdit1)
	ON_EN_CHANGE(IDC_SSN_EDIT2, &CStaffForm14::OnEnChangeSsnEdit2)
END_MESSAGE_MAP()


void CStaffForm14::OnCardNumber(UINT nFlag)
{
	CString strCard = m_strCardNumber[GetIndexFromCardID(nFlag)];

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);

	if(pRecord == NULL || info == NULL)
		return;

	CString strTemp = "";

	if(UpdateRiderCardState(strCard, info->nCompany, info->nRNo, strTemp))
	{
		MessageBox("적용되었습니다", "확인", MB_ICONINFORMATION);
		RefreshOneRider(pRecord, FALSE);
		m_lstReport.RedrawControl();
	}
}

// CStaffForm14 진단입니다.

#ifdef _DEBUG
void CStaffForm14::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffForm14::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStaffForm14 메시지 처리기입니다.

void CStaffForm14::OnBnClickedSearchBtn()
{
	RefreshList();
}

BOOL CStaffForm14::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{ 
			if(::GetDlgCtrlID(pMsg->hwnd) == IDC_NAME_EDIT)
				GetDlgItem(IDC_RNO_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_RNO_EDIT)
				GetDlgItem(IDC_MP_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_MP_EDIT)
				GetDlgItem(IDC_PHONE_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_PHONE_EDIT)
				GetDlgItem(IDC_MARKET_LINE_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_MARKET_LINE_EDIT)
				GetDlgItem(IDC_PDA_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_PDA_EDIT)
				GetDlgItem(IDC_BANK_OWNER_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BANK_OWNER_EDIT)
				GetDlgItem(IDC_BANK_NAME_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BANK_NAME_EDIT)
				GetDlgItem(IDC_BANK_ACCOUNT_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BANK_ACCOUNT_EDIT)
				GetDlgItem(IDC_RT_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_RT_EDIT)
				GetDlgItem(IDC_SSN_EDIT1)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SSN_EDIT1)
				GetDlgItem(IDC_SSN_EDIT2)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SSN_EDIT2)
				GetDlgItem(IDC_LICENCE_NO_EDIT)->SetFocus(); 
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_LICENCE_NO_EDIT)
				GetDlgItem(IDC_ADDRESS_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_ADDRESS_EDIT)
				GetDlgItem(IDC_MEMO_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_MEMO_EDIT)
				GetDlgItem(IDC_INNER_MEMO_EDIT)->SetFocus();
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_INNER_MEMO_EDIT)
			{
				if(m_bAddRiderMode == TRUE)
					GetDlgItem(IDC_BUTTON_NEW)->SetFocus();
				else
					GetDlgItem(IDC_BUTTON_MODIFY)->SetFocus();
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BUTTON_NEW)
			{
				OnBnClickedButtonNew();
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BUTTON_MODIFY)
			{
				OnBnClickedButtonModify();
			}	
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CStaffForm14::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	//if(!pItemNotify->pRow || !pItemNotify->pColumn)
	//	return;

	SetDataFromMap();
}

ST_RIDER_INFO* CStaffForm14::GetCurSelRiderInfo(CXTPGridRecord *pRecord)
{
	if(pRecord == NULL)
		pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return NULL;

	BOOL nLastANo = m_lstReport.GetItemLong(pRecord);
	BOOL bLastAdminTable = m_lstReport.GetItemLong2(pRecord);

	RIDER_INFO_MAP::iterator it = m_map.find(make_pair(bLastAdminTable, nLastANo));
	
	if(it == m_map.end())
		return NULL;

	ST_RIDER_INFO *info = it->second;

	return info;
}

void CStaffForm14::SetDataFromMap()
{	
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	char buffer[10];
	m_strName = info->strName;
	m_strRNo = itoa(info->nRNo, buffer, 10);
	m_strMp = ::GetDashPhoneNumber(info->strMp);
	m_strPhone = ::GetDashPhoneNumber(info->strPhone);
	m_strRT = info->strRT;
	m_strPDA = info->strID;
	m_strBankOwner = info->strBankOwner;
	m_strBankName = info->strBankName;
	m_strBankAccount = info->strBankAccount; m_strBankAccount.Replace("-", "");
	m_strMarketLine = ::RemoveZero(itoa(info->nMarketLine, buffer, 10));
	m_dtEnter = info->dtEnter;
	m_strSSN1 = info->strSSN1;
	m_strSSN2 = info->strSSN2;
	m_cmbLicence.SetCurSel(info->nLicenceType);
	m_strLicenceNo = info->strLicenceNo;
	m_dtIns = info->dtInsJoin;
	m_strRtSerial = info->strRTSerial; 
	m_strCarNo = info->strCarNo;

	m_strTruckMyDepositRate = ::GetStringFromLong(info->nTruckMyDepositRate);
	m_strTruckOtherDepositRate = ::GetStringFromLong(info->nTruckOtherDepositRate);

	if(info->nAllocType == TWO)
	{
		m_chkPDAAllocate.SetCheck(TRUE); m_chkSmsAllocate.SetCheck(FALSE);
	}
	else if(info->nAllocType == ONE)
	{
		m_chkPDAAllocate.SetCheck(FALSE); m_chkSmsAllocate.SetCheck(TRUE);
	}
	else
	{
		m_chkPDAAllocate.SetCheck(FALSE); m_chkSmsAllocate.SetCheck(FALSE);
	}

	::SetCarType(&m_cmbCarType, info->nCarType);
	m_cmbShareLimit.SetCurSel(info->nPanaltyTypeShowOrder);

	if(info->nLockTime == ZERO || info->nLockCount >= 100)
	{ 
		m_chkAllocateLimit.SetCheck(FALSE);
		m_cmbAllocateLimitMinute.SetWindowText("");
		m_cmbAllocateLimitCount.SetWindowText("무제한");
	}
	else 
	{
		m_chkAllocateLimit.SetCheck(TRUE);
		m_cmbAllocateLimitMinute.SetWindowText(itoa(info->nLockTime, buffer, 10));
		m_cmbAllocateLimitCount.SetWindowText(itoa(info->nLockCount, buffer, 10));
	}

	if(info->bAdminTable == TRUE)
	{
		if(info->nWorkState == ZERO)
			m_cmbWorkState.SetCurSel(ZERO);
		else
			m_cmbWorkState.SetCurSel(ONE);
	}
	else
		m_cmbWorkState.SetCurSel(TWO);

	m_cmbAllocGroup.SetCurSel(info->nAllocGroup);

	m_strAddress = info->strAddress;
	m_strMemo = info->strMemo;
	m_strInnerMemo = info->strInnerMemo;
	m_bAuto = info->bAuto;
	m_bBigAuto = info->bBigAuto;
	m_bDama = info->bDama;
	m_bRabo = info->bRabo;
	m_bSedan = info->bSedan;
	m_bTruck = info->bTruck;

	if(m_bAuto && m_bBigAuto && m_bDama && m_bRabo && m_bSedan && m_bTruck)
		m_bAll = TRUE;
	else
		m_bAll = FALSE; 

	m_cmbInsType.SetCurSel(info->nInsType);
	m_cmbDepositType.SetCurSel(::GetDepositTypeToComboSel(info->nDepositType));
	OnCbnSelchangeDepositTypeCombo1();
	m_cmbDepositAllocateType.SetCurSel(::GetDepositAllocateTypeToComboSel(info->nDepositAllocateType));

	m_chkMyCall.SetCheck(info->nMyCallRateType);
	m_chkOtherCall.SetCheck(info->nOtherCallRateType);
	m_chkUseRiderTax.SetCheck(info->bUseRiderTax);
	m_chkAutoAllocate.SetCheck(info->bAutoAlloc);
	m_cmbBusinessCar.SetCurSel(info->bBusinessCar);

	m_strMyCallRateType = info->strMyCallRateType;
	m_strOtherCallRateType = info->strOtherCallRateType;
	m_nMyCallRateType = info->nMyCallRateType;
	m_nOtherCallRateType = info->nOtherCallRateType;

	m_nLicenceValid = info->nLicenceValid;
	m_bAddRiderMode = FALSE;
	m_btnNew.SetWindowText("신규"); 
	m_cmbBranch.EnableWindow(FALSE);
	ReLoadImage();

	m_nLastANo = info->nANo;
	m_bLastAdminTable = info->bAdminTable;

	for(int i=ZERO; i<m_cmbBranch.GetCount(); i++)
	{
		if(info->nCompany == (long)m_cmbBranch.GetItemData(i))
		{
			m_cmbBranch.SetCurSel(i);
			break;
		}
	} 

	m_chkInsNotRegister.SetCheck(!info->bRegisterLoadIns);
	m_bNotShowRightOrder = info->nThShareExceptType > ZERO ? TRUE : FALSE;
	m_strDailyReportCharge = RemoveZero(::GetMyNumberFormat(info->nDailyDepositCharge));
	m_strAllocMinCharge = RemoveZero(::GetMyNumberFormat(info->nAllocMinCharge));

	m_edtIncome.GetWindowText(m_strIncome);
	m_edtIncomeMemo.GetWindowText(m_strIncomeMemo);
	m_edtRNo.EnableWindow(FALSE);	
	m_chkWithDrawType.SetCheck(info->nWithdrawType);
	m_edtMaxWithDrawMoneyPerDay.SetWindowText(::RemoveZero(::GetMyNumberFormat(info->nMaxWithdrawMoneyPerDay)));
	m_edtMinLeftMoneyForWithDraw.SetWindowText(::RemoveZero(::GetMyNumberFormat(info->nMinLeftMoneyForWithdraw)));
	m_edtCardNumber.SetWindowText(::GetDashCardNumber(info->strCardNumber));
	FillBankCode(FALSE, &m_cmbBankID, info->nBankID);	
	EnableShowControl();
	UpdateData(FALSE);
	ChangeSSNColor();

	SetTimer(TIMER_REFRESH_JOB, 500, NULL);
}

void CStaffForm14::EnableShowControl()
{
	/*BOOL bEnable = !(::GetCarType(&m_cmbCarType) == CAR_1_4_TON);
	m_chkAll.EnableWindow(bEnable);
	m_chkAuto.EnableWindow(bEnable);
	m_chkBigAuto.EnableWindow(bEnable);
	m_chkDama.EnableWindow(bEnable);
	m_chkRabo.EnableWindow(bEnable);
	m_chkBan.EnableWindow(bEnable);
	m_chk6Ban.EnableWindow(bEnable);
	m_chkTruck.EnableWindow(bEnable);
	m_chkSubway.EnableWindow(bEnable);
	m_chkParcelService.EnableWindow(bEnable);*/
}

void CStaffForm14::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();


	/*
	m_cmbCarType.AddString("오토바이");
	m_cmbCarType.AddString("짐받이");
	m_cmbCarType.AddString("다마스");
	m_cmbCarType.AddString("라보");
	m_cmbCarType.AddString("3밴");
	m_cmbCarType.AddString("6밴");
	m_cmbCarType.AddString("트럭");
	m_cmbCarType.AddString("1.4톤");
	m_cmbCarType.AddString("지하철");
	m_cmbCarType.AddString("당일택배");
	*/


	::MakeCarTypeCombo(&m_cmbCarType);

	m_cmbIncome.SetCurSel(0);


	m_lstReport.SetExternalControl(GetDlgItem(IDC_SEARCH_COMBO),
		GetDlgItem(IDC_SEARCH_COMBO),			//SetExternalControl함수의 순서중요함
		GetDlgItem(IDC_SEARCH_COMBO));	//반드시 InsertColumn앞에 있어야함

	m_lstReport.InsertColumn(0, "NO", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "사번", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(2, "소 속", LVCFMT_CENTER, 85);
	m_lstReport.InsertColumn(3, "PDA",	LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "성 명", LVCFMT_LEFT, 80);	
	m_lstReport.InsertColumn(5, "차량", LVCFMT_CENTER, 40);	
	m_lstReport.InsertColumn(6, "전화번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(7, "휴대폰", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(8, "입사일", LVCFMT_CENTER, 80);	
	m_lstReport.InsertColumn(9, "퇴사일", LVCFMT_CENTER, 80);
	m_lstReport.InsertColumn(10, "주민번호",LVCFMT_CENTER, 110);
	m_lstReport.InsertColumn(11, "내부메모",LVCFMT_LEFT, 110);
	m_lstReport.InsertColumn(12, "업무중지", LVCFMT_CENTER, 70);
	m_lstReport.InsertColumn(13, "배차그룹", LVCFMT_CENTER, 70);
	m_lstReport.InsertColumn(14, "즉시공유", LVCFMT_CENTER, 65);
	m_lstReport.InsertColumn(15, "충전금잔액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(16, "근무유형", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(17, "입금방식", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(18, "자사콜", LVCFMT_CENTER, 55);
	m_lstReport.InsertColumn(19, "타사콜", LVCFMT_CENTER, 55);
	m_lstReport.InsertColumn(20, "자사콜(트럭)", LVCFMT_CENTER, 65);
	m_lstReport.InsertColumn(21, "타사콜(트럭)", LVCFMT_CENTER, 65);
	m_lstReport.InsertColumn(22, "일비차감", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(23, "최근6개월충전금", LVCFMT_RIGHT, 100);
	m_lstReport.InsertColumn(24, "메모", LVCFMT_LEFT, 250);
	m_lstReport.InsertColumn(25, "주소", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(26, "출금은행", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(27, "예금계좌", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(28, "예금주", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(29, "입금그룹명", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(30, "선불카드", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(31, "차량번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(32, "적재물보험가입", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(33, "적재물보험적용중", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(34, "단말기취소", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(35, "기기ID", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(36, "제조번호", LVCFMT_LEFT, 70);

	//m_lstReport.InsertColumn(13, "무전기ID", LVCFMT_CENTER, 70);

	m_lstReport.SetFreezeColumnsCount(FIVE);
	m_lstReport.SetOrderIndexCol(ZERO);
	m_lstReport.Populate();

	m_lstReport.LoadReportOrder("CStaffForm14", "m_lstReport");

	if(IsThisCompany("대전_나이스"))
		m_lstReport.GetColumns()->GetAt(33)->SetVisible(TRUE);
	else
		m_lstReport.GetColumns()->GetAt(33)->SetVisible(FALSE);

	m_wndJobReport.InsertColumn(0, "", LVCFMT_LEFT, 150);
	m_wndJobReport.ShowHeader(FALSE);
	m_wndJobReport.GetPaintManager()->m_strNoItems = "";
	m_wndJobReport.Populate();

	m_wndJobReport.SetScrollMode(xtpGridOrientationHorizontal, xtpGridScrollModeNone);
	m_wndJobReport.Populate();
 
	m_edtSSN1.LimitText(SIX);
	m_edtSSN2.LimitText(SEVEN);
	
	m_cmbConWorking.SetCurSel(ONE);
	LU->MakeAllocateGroupCombo(&m_cmbAllocGroup);

	m_cmbIncome.InsertString(ZERO, "(+)잔액충전(현금)");
	m_cmbIncome.SetItemData(ZERO, 17);
	m_cmbIncome.InsertString(ONE, "(+)잔액충전(온라인)");
	m_cmbIncome.SetItemData(ONE, 16);
	m_cmbIncome.InsertString(TWO, "(-)잔액차감");
	m_cmbIncome.SetItemData(TWO, 40);
	m_cmbIncome.InsertString(THREE, "(-)잔액차감(충전취소)");
	m_cmbIncome.SetItemData(THREE, 49);
	m_cmbIncome.SetCurSel(ZERO);

	m_edtIncome.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "금액");
	m_edtIncomeMemo.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "입금적요");

	m_edtName.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "성 명");
	m_edtRNo.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "기사번호");
	m_edtMp.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "휴 대 폰");
	m_edtPDA.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "단 말 기");
	m_edtSSN1.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "주 민");
	m_edtSSN2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "번 호");
	m_edtCarNo.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "차량번호");

	m_edtName.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtRNo.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtMp.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtPDA.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtSSN1.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtSSN2.SetUserTextColorNoFocus(RGB(255, 0, 0));
	m_edtCarNo.SetUserTextColorNoFocus(RGB(255, 0, 0));

	//m_edtCardNumber.SetEditMask("0000-0000-0000-0000", LITERAL_CARD_NUMBER);
	//m_edtCardNumber.SetPromptChar(' ');

	FillBankCode(TRUE, &m_cmbBankID);
	
	InitControl();
	MakeBranchCombo();
	ReLoadImage();
	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CStaffForm14::DeleteMapData()
{
	RIDER_INFO_MAP::iterator it = m_map.begin();

	for(RIDER_INFO_MAP::iterator it = m_map.begin(); it != m_map.end(); it++)
	{
		ST_RIDER_INFO *info = it->second;

		if(info)
		{
			delete info;
			info = NULL;
		}
	}

	m_map.clear();
}

void CStaffForm14::RefreshList()
{
	CMyFormView::RefreshList();

	DeleteMapData();
	m_lstReport.DeleteAllItems();

	CWaitCursor wait;  

	long nSel = ZERO;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_worker30"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_cmbConWorking.GetCurSel());

	if(!pRs.Execute(&pCmd)) return;

	for(int i = ZERO; i < pRs.GetRecordCount(); i++)
	{
		//long a = LU->m_mapAllocateGroup.size();
		long nSubItem = ONE;		
		ST_RIDER_INFO *info = new ST_RIDER_INFO;

		GetRSData(&pRs, info, i, TRUE);

		if(info->bAdminTable == m_bLastAdminTable && info->nANo == m_nLastANo)
			nSel = i;

		pRs.MoveNext();
	}

	pRs.Close();
	m_lstReport.Populate();

 	if(nSel < m_lstReport.GetItemCount())  
	{ 
		CXTPGridRows *pRows = m_lstReport.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(min(max(nSel + 10, nSel), m_lstReport.GetItemCount()-1));
		m_lstReport.EnsureVisible(pRow);
		m_lstReport.SetSelectedRow(nSel);
		SetDataFromMap();
	}
}

void CStaffForm14::OnBnClickedButtonNew()
{
	if(m_bAddRiderMode == TRUE)
	{
		if(InsertUser())
		{
			RefreshList();
			m_edtRNo.EnableWindow(FALSE);
		}
	}
	else
	{
		InitData();
		UpdateData(FALSE);
		m_bAddRiderMode = TRUE;
 
		InitControl();
	}
}

void CStaffForm14::InitControl()
{
	m_dtpEnter.SetTime(COleDateTime::GetCurrentTime());
	m_chkPDAAllocate.SetCheck(TRUE);
	m_chkSmsAllocate.SetCheck(FALSE);
	m_cmbLicence.SetCurSel(ZERO);
	m_cmbWorkState.SetCurSel(ZERO);
	m_cmbCarType.SetCurSel(ZERO);

	m_cmbDepositType.SetCurSel(THREE);
	m_cmbDepositAllocateType.SetCurSel(ZERO);

	SetDefaultDepositRate();

	m_chkNotShowRightOrder.SetCheck(FALSE);
	m_edtDailyDepositCharge.SetWindowText("");

	m_btnNew.SetWindowText("등록");
	m_cmbBranch.EnableWindow(TRUE);

	m_edtIncome.SetWindowText("");
	m_edtIncomeMemo.SetWindowText("");

	m_edtRNo.EnableWindow(TRUE);
	m_edtName.SetFocus();

	m_cmbBankID.SetCurSel(ZERO);
	m_chkWithDrawType.SetCheck(FALSE);
	m_edtMaxWithDrawMoneyPerDay.SetWindowText("");
	m_edtMinLeftMoneyForWithDraw.SetWindowText("");

	m_cmbShareLimit.SetCurSel(ZERO);
	m_cmbAllocGroup.SetCurSel(ZERO);
	m_cmbIncome.SetCurSel(ZERO);
	m_chkUseRiderTax.SetCheck(FALSE);

	m_chkAutoAllocate.SetCheck(FALSE);
}

void CStaffForm14::OnBnClickedRiderConfidenceBtn()
{
	CString strSSN1, strSSN2;

	m_edtSSN1.GetWindowText(strSSN1);
	m_edtSSN2.GetWindowText(strSSN2);

	CString strSSN = strSSN1 + strSSN2;

	if(!LU->IsSSNOk(strSSN)) {
		MessageBox("주민번호가 유효하지 않습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	//if(IsRRN(strSSN, TRUE) == FALSE)
	//	return;	

	CString strCompany, strMemo;
	COleDateTime dtPrevent;

	CString strMent = "", strDate = "";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_refusal_info");
	pCmd.AddParameter(strSSN);

	if(pRs.Execute(&pCmd) == FALSE)
		return;  

	strMent = "아래와 같이 배차제한 되어 있습니다\r\n\r\n";

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sCompany", strCompany);
	 	pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("dtPrevent", dtPrevent); 

		strDate.Format("%4d-%02d-%02d", dtPrevent.GetYear(), dtPrevent.GetMonth(), dtPrevent.GetDay());
		
		strMent += strDate + "  " + strCompany + "  " + strMemo + "\r\n";

		pRs.MoveNext();
	}

	if(pRs.GetRecordCount() == ZERO)
		strMent = "배차제한에 등록되어 있지 않습니다";
	

	MessageBox(strMent, "확인", MB_ICONINFORMATION);
}

void CStaffForm14::OnBnClickedLicenseQueryButton()
{
	UpdateData(TRUE);

	BOOL bLicenseOK;
	CString sRet;
	CKingoHttp http;
	CString    sRand;
	CString sName, sJumin1, sJumin2, sJumin, sLicense;

	m_edtSSN1.GetWindowText(sJumin1);
	m_edtSSN2.GetWindowText(sJumin2);
	m_edtName.GetWindowText(sName);
	m_edtLicenceNo.GetWindowText(sLicense);

	sName.Trim();
	sJumin1.Trim();
	sJumin2.Trim();


	if(sName.GetLength() < 4) 
	{
		MessageBox(GetLicenseStateString(-5,&bLicenseOK), "확인", MB_ICONINFORMATION);
		m_nLicenceValid = -5;
		return;
	}

	if(sJumin1.GetLength() != 6 || sJumin2.GetLength() != 7 ) 
	{
		MessageBox(GetLicenseStateString(-6,&bLicenseOK), "확인", MB_ICONINFORMATION);
		m_nLicenceValid = -6;
		return;
	}

	sLicense.Remove(' ');
	sLicense.Remove('-');
	int nLen2 = sLicense.GetLength();
	if(nLen2 != 14)
	{
		MessageBox(GetLicenseStateString(-3,&bLicenseOK), "확인", MB_ICONINFORMATION);
		m_nLicenceValid = -3;
		return;
	}

	char szbuffer[50]={0,};
	char szdata[1024]={0,};

	BOOL bRet = ConnectDrvLicSvr();

	//STRCPY(szdata,ltoa(m_nRiderCompany,szbuffer,10),ltoa(m_nRNo,szbuffer,10),sName,sJumin1,sJumin2,sLicense,"0",VL_END);
	STRCPY(szdata,ltoa(0,szbuffer,10),ltoa(0,szbuffer,10),sName,sJumin1,sJumin2,sLicense,"0",VL_END);
	if( !m_pMkDb4DrvLic->GetSocket()->SendData(PT_REQUEST,PST_RIDER_LICENSE_VALID,szdata) )
	{
		MessageBox("면허 조회 서버에 접속 할수없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4DrvLic->GetSocket()->ReadStream();
	if(p != NULL) {
		MessageBox(p->data, "확인", MB_ICONINFORMATION);
		m_nLicenceValid = p->nSubType;
		free(p);
	}

	return;
}

void CStaffForm14::OnBnClickedRiderPicInsertBtn()
{
	MakeContextMenu();
}

void CStaffForm14::MakeContextMenu()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	pMenu->AppendMenu(MF_BYCOMMAND, ID_UPLOAD_PIC, "사진등록");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_DELETE_PIC, "사진삭제");

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CStaffForm14::OnUploadPic() 
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(m_bAddRiderMode == TRUE || info == NULL)
	{
		MessageBox("기사 등록후 사진을 등록해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(info->bAdminTable == FALSE)
	{
		MessageBox("퇴사자는 사진 등록이 불가능 합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, "Image (*.PNG, *.JPG)|*.*||");
	if(dlg.DoModal() == IDOK)
	{ 
		CString strPath = dlg.GetPathName();
		CString strName = dlg.GetFileName();

		if(strName.Right(3) != "png" && strName.Right(3) != "jpg" &&
			strName.Right(3) != "PNG" && strName.Right(3) != "JPG")
		{
			MessageBox("png, jpg 형식의 파일만 업로드 가능합니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		CStdioFile file;		 
		file.Open(strPath,CStdioFile::modeRead, 0);
		long nSize = file.GetLength() / 1024;
		
		file.Close();

		if(nSize > 100)
		{
			MessageBox("100Kb이상의 파일은 업로드 하실 수 없습니다.", "확인", MB_ICONINFORMATION);
			return;
		}
	
		CFileUpload fu;
		fu.SetConnectInfo(FTP_IP, FTP_URL_ID_PICTURE, "", "");

/*		
		if(fu.UploadFile(strPath, strName, info->nANo))
		{
			MessageBox("등록되었습니다", "확인", MB_ICONINFORMATION);
			ReLoadImage();
		}
*/		
	}
}

void CStaffForm14::OnDeletePic()
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(m_bAddRiderMode == TRUE || info == NULL)
	{
		MessageBox("기사 등록후 사진을 등록해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(info->bAdminTable == FALSE)
	{
		MessageBox("퇴사자는 사진 등록이 불가능 합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("삭제하시겠습니까?\r\n삭제 후 복원 불가능합니다.", "확인", MB_OKCANCEL) != IDOK)
		return;

	CFileUpload fu;
	fu.SetConnectInfo(FTP_IP, FTP_URL_ID_PICTURE, "", "");

	if(fu.DeleteFile(info->nANo))
	{
		MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
		ReLoadImage();
	}
}

void CStaffForm14::ReLoadImage()
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	//char buffer[10];
	long nANo = 0;

	if(info != NULL && 
		info->bAdminTable == TRUE)
		nANo = info->nANo;

	//CString sUrl = "http://quick3.logisoft.co.kr/manager_IDPicture/IDPicture.asp";
	CString sUrl = "http://quick3.logisoft.co.kr/SmartQ/driver_profile_upload.asp";
	CString strTemp = "";
	strTemp.Format("?lANo=%ld&nSiteSessionkey=%ld", nANo, m_ui.nSiteSessionKey);
	//sUrl += "?nANo=" + CString(itoa(nANo, buffer,10));
	sUrl += strTemp;
	m_Explorer.Navigate(sUrl, NULL, NULL, NULL, NULL);
}

BOOL CStaffForm14::GetRSData(CMkRecordset *pRs, ST_RIDER_INFO *info, long nIndex, BOOL bInsert)
{
	char buffer[10];
	int nSubItem = ONE;

	pRs->GetFieldValue("lANo", info->nANo);
	pRs->GetFieldValue("sName", info->strName);
	pRs->GetFieldValue("lCode", info->nCompany);		
	pRs->GetFieldValue("nMNo", info->nRNo);
	pRs->GetFieldValue("sHp", info->strMp); 
	pRs->GetFieldValue("sTel", info->strPhone);
	pRs->GetFieldValue("sRTID", info->strRT);
	pRs->GetFieldValue("sID", info->strID); 
	pRs->GetFieldValue("sBankAccountOwner", info->strBankOwner);  
	pRs->GetFieldValue("sBankName", info->strBankName); 
	pRs->GetFieldValue("sBankAccount", info->strBankAccount);
	pRs->GetFieldValue("nMarketLine", info->nMarketLine);
	pRs->GetFieldValue("dtEnter", info->dtEnter);
	pRs->GetFieldValue("dtOut", info->dtOut);
	pRs->GetFieldValue("sSSN1", info->strSSN1);
	pRs->GetFieldValue("sSSN2", info->strSSN2);
	pRs->GetFieldValue("nRicenceType", info->nLicenceType);
	pRs->GetFieldValue("sRicenceNumber", info->strLicenceNo);
	pRs->GetFieldValue("nAllocType", info->nAllocType);
	pRs->GetFieldValue("nCarType", info->nCarType); 
	//pRs->GetFieldValue("bLock", info->bLock);
	pRs->GetFieldValue("nLockTime", info->nLockTime); 
	pRs->GetFieldValue("nLockCount", info->nLockCount);
	pRs->GetFieldValue("nWorkState", info->nWorkState);	
	pRs->GetFieldValue("nAllocGroup", info->nAllocGroup);
	pRs->GetFieldValue("sAddress", info->strAddress);
	pRs->GetFieldValue("sEtc", info->strMemo);
	pRs->GetFieldValue("sInnerMemo", info->strInnerMemo);
	pRs->GetFieldValue("bAutoShow", info->bAuto);
	pRs->GetFieldValue("bBigAutoShow", info->bBigAuto);
	pRs->GetFieldValue("bDamaShow", info->bDama);
	pRs->GetFieldValue("bRaboShow", info->bRabo);
	pRs->GetFieldValue("bSedanShow", info->bSedan);
	pRs->GetFieldValue("bTruckShow", info->bTruck);
	pRs->GetFieldValue("nDepositType", info->nDepositType);
	pRs->GetFieldValue("nDepositAllocateType", info->nDepositAllocateType);
	pRs->GetFieldValue("nMyCallRateType", info->nMyCallRateType);
	pRs->GetFieldValue("nOtherCallRateType", info->nOtherCallRateType);
	pRs->GetFieldValue("sMyCallRateType", info->strMyCallRateType);
	pRs->GetFieldValue("sOtherCallRateType", info->strOtherCallRateType);	
	pRs->GetFieldValue("dtWorkStateDate", info->dtWorkStateDate);
	pRs->GetFieldValue("nLicenseValid", info->nLicenceValid);
	pRs->GetFieldValue("nThShareExceptType", info->nThShareExceptType);
	pRs->GetFieldValue("nDailyDepositCharge", info->nDailyDepositCharge);
	pRs->GetFieldValue("nPanaltyTypeShowOrder", info->nPanaltyTypeShowOrder);
	pRs->GetFieldValue("nBalance", info->nBalance);
	pRs->GetFieldValue("nSaveSixMonth", info->nSaveSixMonth);
	pRs->GetFieldValue("nBankID", info->nBankID);
	pRs->GetFieldValue("nWithdrawType", info->nWithdrawType);
	pRs->GetFieldValue("nMaxWithdrawMoneyPerDay", info->nMaxWithdrawMoneyPerDay);
	pRs->GetFieldValue("nMinLeftMoneyForWithdraw", info->nMinLeftMoneyForWithdraw);
	pRs->GetFieldValue("nRiderColor", info->nRiderColor);
	pRs->GetFieldValue("dtInsJoin", info->dtInsJoin);
	pRs->GetFieldValue("nInsType", info->nInsType);
	pRs->GetFieldValue("bUseRiderTax", info->bUseRiderTax);
	pRs->GetFieldValue("sRTSerial", info->strRTSerial);
	pRs->GetFieldValue("bAdminTable", info->bAdminTable);		
	pRs->GetFieldValue("sRiderDepositGroup", info->strRiderDepositGroup);		
	pRs->GetFieldValue("bAutoAlloc", info->bAutoAlloc);
	pRs->GetFieldValue("nTruckMyDepositRate", info->nTruckMyDepositRate);		
	pRs->GetFieldValue("nTruckOtherDepositRate", info->nTruckOtherDepositRate);
	pRs->GetFieldValue("sCardNumber", info->strCardNumber);
	pRs->GetFieldValue("sCarNo", info->strCarNo);
	pRs->GetFieldValue("nAllocMinCharge", info->nAllocMinCharge);
	pRs->GetFieldValue("bRegisterLoadIns", info->bRegisterLoadIns);
	pRs->GetFieldValue("bBusinessCar", info->bBusinessCar);

	BOOL bLoadInsApply;
	long nPenaltyTypeCancel;
	pRs->GetFieldValue("bLoadInsApply", bLoadInsApply);
	pRs->GetFieldValue("nPenaltyTypeCancel", nPenaltyTypeCancel);
	
	
	if(bInsert)
		m_lstReport.InsertItem(nIndex, "");

	m_lstReport.SetItemText(nIndex, nSubItem++, ltoa(info->nRNo, buffer, 10));
	m_lstReport.SetItemText(nIndex, nSubItem++, m_ci.GetName(info->nCompany));

	CString strCarType, strWorkStop = "";

	if(info->nWorkState > 0)
	{
		if(info->dtWorkStateDate.m_dt == 0)
			strWorkStop = "업무중지";
		else
		{
			strWorkStop.Format("%4d-%02d-%02d %02d:%02d:%02d",info->dtWorkStateDate.GetYear(),
				info->dtWorkStateDate.GetMonth(),info->dtWorkStateDate.GetDay(),info->dtWorkStateDate.GetHour(),
				info->dtWorkStateDate.GetMinute(),info->dtWorkStateDate.GetSecond());
		} 
	}

	m_lstReport.SetItemText(nIndex, nSubItem++, info->strID);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strName); 
	m_lstReport.SetItemText(nIndex, nSubItem++, GetCarTypeFromLong(info->nCarType));
	m_lstReport.SetItemText(nIndex, nSubItem++, GetDashPhoneNumber(info->strPhone));
	m_lstReport.SetItemText(nIndex, nSubItem++, GetDashPhoneNumber(info->strMp));

	CString strTemp = info->dtEnter.Format("%Y/%m/%d"); 

	m_lstReport.SetItemText(nIndex, nSubItem++, strTemp);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->bAdminTable == FALSE && info->dtOut.m_status != 2 ? info->dtOut.Format("%Y-%m-%d") : "");
	m_lstReport.SetItemText(nIndex, nSubItem++, (info->strSSN1.IsEmpty() && info->strSSN2.IsEmpty()) ? "" : info->strSSN1 + "-" + info->strSSN2);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strInnerMemo);
	m_lstReport.SetItemText(nIndex, nSubItem++, strWorkStop);

	long nAllocGroup = max(info->nAllocGroup, 0);
	nAllocGroup = min(info->nAllocGroup, 9);
	m_lstReport.SetItemText(nIndex, nSubItem++, LU->m_mapAllocateGroup[nAllocGroup]);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->nThShareExceptType > ZERO ? "안봄" : "");
	m_lstReport.SetItemText(nIndex, nSubItem++, ::RemoveZero(::GetMyNumberFormat(info->nBalance)));
	m_lstReport.SetItemText(nIndex, nSubItem++, GetDepositTypeStringFromType(info->nDepositType));
	m_lstReport.SetItemText(nIndex, nSubItem++, GetDepositAllocateTypeStringFromType(info->nDepositAllocateType));
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strMyCallRateType);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strOtherCallRateType);
	m_lstReport.SetItemText(nIndex, nSubItem++, ::GetStringFromLong(info->nTruckMyDepositRate, FALSE));
	m_lstReport.SetItemText(nIndex, nSubItem++, ::GetStringFromLong(info->nTruckOtherDepositRate, FALSE));
	m_lstReport.SetItemText(nIndex, nSubItem++, ::RemoveZero(::GetMyNumberFormat(info->nDailyDepositCharge)));
	m_lstReport.SetItemText(nIndex, nSubItem++, ::RemoveZero(::GetMyNumberFormat(info->nSaveSixMonth)));
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strMemo);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strAddress);
	m_lstReport.SetItemText(nIndex, nSubItem++, ::GetBankName(info->nBankID));
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strBankAccount);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strBankOwner);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strRiderDepositGroup);
	m_lstReport.SetItemText(nIndex, nSubItem++, ::GetDashCardNumber(info->strCardNumber));
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strCarNo);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->bRegisterLoadIns ? "가입" : "");
	m_lstReport.SetItemText(nIndex, nSubItem++, bLoadInsApply ? "적용중" : "");

	strTemp = "";

	if(nPenaltyTypeCancel == 1) strTemp = "취소불가";
	else if(nPenaltyTypeCancel == 2) strTemp = "상세정보 본후 취소불가";

	m_lstReport.SetItemText(nIndex, nSubItem++, strTemp);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strRT);
	m_lstReport.SetItemText(nIndex, nSubItem++, info->strRTSerial);

	m_lstReport.SetItemLong(nIndex, info->nANo);
	m_lstReport.SetItemLong2(nIndex, info->bAdminTable);
	m_lstReport.SetItemLong3(nIndex, info->nRiderColor);
	m_lstReport.SetItemData(nIndex, info->nWorkState);

	CString ssn = info->strSSN1 + info->strSSN2;

	if (!LU->IsSSNOk(ssn) && ssn != "1111111111111") {
		m_lstReport.SetItemDataText(nIndex, "1");
	}
	else {
		m_lstReport.SetItemDataText(nIndex, "0");
	}

	RIDER_INFO_MAP::iterator it = m_map.find(make_pair(info->bAdminTable, info->nANo));
	
	if(it == m_map.end())
		m_map.insert(RIDER_INFO_MAP::value_type(std::make_pair(info->bAdminTable, info->nANo), info));
	else
		it->second = info;

	return TRUE;
}

void CStaffForm14::MakeBranchCombo()
{
	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);
		
		int nIndex = m_cmbBranch.AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
		m_cmbBranch.SetItemData(nIndex, pBi->nCompanyCode);

		if(GetCurBranchInfo()->nCompanyCode == pBi->nCompanyCode)
			m_cmbBranch.SetCurSel(nIndex);
	}
}

void CStaffForm14::RefreshOneRider(CXTPGridRecord *pRecord, BOOL bPopulate)
{
	if(pRecord == NULL)
		pRecord = m_lstReport.GetFirstSelectedRecord();

	BOOL nLastANo = m_lstReport.GetItemLong(pRecord);
	BOOL bLastAdminTable = m_lstReport.GetItemLong2(pRecord);

	RIDER_INFO_MAP::iterator it = m_map.find(make_pair(bLastAdminTable, nLastANo));
	
	if(it != m_map.end())
	{
		ST_RIDER_INFO *info = it->second;

		if(info)
		{
			delete info;
			info = NULL;
			m_map.erase(it);
		}
	}

	ST_RIDER_INFO *pInfo = new ST_RIDER_INFO;

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_one_new_19");
	pCmd.AddParameter(nLastANo);
	pCmd.AddParameter(bLastAdminTable);
	//pCmd.AddParameter(m_nLastANo);
	//pCmd.AddParameter(m_bLastAdminTable);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == ZERO) return;

	if(GetRSData(&pRs, pInfo, pRecord->GetIndex(), FALSE))
	{
		if(bPopulate)
			m_lstReport.Populate();
	}
}

void CStaffForm14::OnBnClickedButtonModify()
{
	if(m_bAddRiderMode == TRUE)
	{
		MessageBox("수정하려는 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
 
	if(UpdateUser())
	{
		ST_RIDER_INFO *info = GetCurSelRiderInfo();

		if(m_cmbConWorking.GetCurSel() == ZERO)
			RefreshOneRider();
		else if((m_cmbConWorking.GetCurSel() == ONE && m_cmbWorkState.GetCurSel()  != ZERO) ||
			(m_cmbConWorking.GetCurSel() == TWO && m_cmbWorkState.GetCurSel()  != ONE) ||
			(m_cmbConWorking.GetCurSel() == THREE && m_cmbWorkState.GetCurSel()  != TWO))
			RefreshList();
		else
			RefreshOneRider();

		MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);
	}
}

BOOL CStaffForm14::CheckLocal()
{
	CString strMsg = "";
	if(m_strName.IsEmpty())
	{ 
		strMsg = "성명을 입력하세요";
		m_edtName.SetFocus();
	}
	else if(atoi(m_strRNo) <= ZERO)
	{
		strMsg = "사번 입력하세요";
		m_edtRNo.SetFocus();
	}
	else if(atoi(m_strRNo) >= 32000)
	{
		strMsg = "사번은 30000번 이하로 입력하세요";
		m_edtRNo.SetFocus();
	}
	else if(m_strMp.IsEmpty())
	{
		strMsg = "휴대폰을 입력하세요";
		m_edtMp.SetFocus();
	}
	else if(m_strPDA.GetLength() < FIVE)
	{
		strMsg = "PDA번호를 입력하세요";
		m_edtPDA.SetFocus();
	}
	else if(m_strCarNo.IsEmpty())
	{
		strMsg = "차량번번호를 입력하세요";
		m_edtCarNo.SetFocus();
	}
	else if(m_strSSN1.IsEmpty() || m_strSSN2.IsEmpty() || m_strSSN1.GetLength() != SIX || m_strSSN2.GetLength() != SEVEN)
	{
		strMsg = "주민번호를 입력하세요";
		m_edtSSN1.SetFocus();
	}
	else if(!LU->IsSSNOk(m_strSSN1 + m_strSSN2) && m_strSSN1 + m_strSSN2 != "1111111111111")
	{
		strMsg = "주민번호가 유효성이 맞지 않습니다. 주민번호가 없을시 '1'로 주민번호란을 체우세요";
		m_edtSSN1.SetFocus();
	}
	else if(m_cmbDepositType.GetCurSel() < ZERO)
		strMsg = "근무유형을 선택하세요";
	else if(m_cmbDepositAllocateType.GetCurSel() < ZERO)
		strMsg = "입금방식을 선택하세요";
	else if(m_cmbDepositType.GetCurSel() == THREE && (m_nMyCallRateType == ZERO || m_nOtherCallRateType == ZERO))
		strMsg = "프로제유형은 자사콜,타사콜 입금액그룹을 선택하세요";
	else if(m_chkPDAAllocate.GetCheck() == FALSE && m_chkSmsAllocate.GetCheck() == FALSE)
		strMsg = "배차방식을 선택하세요";
	else if(m_cmbCarType.GetCurSel() < 0)
		strMsg = "차량을 선택하세요";
	else if(atoi(m_strTruckMyDepositRate) > 25 || atoi(m_strTruckMyDepositRate) < 0)
		strMsg = "트럭자사입금액은 0~25사이로 입력하세요";
	else if(atoi(m_strTruckOtherDepositRate) > 25 || atoi(m_strTruckOtherDepositRate) < 0)
		strMsg = "트럭타사입금액은 0~25사이로 입력하세요";

	if(strMsg.GetLength() > ZERO)
	{  
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());

	if(m_ci.GetShareCode5(nCompany) == 9999)
	{
		if(!CheckCarNo(m_strCarNo))
		{
			if(MessageBox("차량번호가 올바르지 않아, 보험적용이 되지 않을 수 있습니다.\r\n진행하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
				return FALSE;
		}		
	}	

	return TRUE;
}

BOOL CStaffForm14::InsertUser()
{
	UpdateData(TRUE);

	if(CheckLocal() == FALSE)
		return FALSE;
	
	CMkCommand pCmd(m_pMkDb, "insert_rider_new_11");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter((long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	pCmd.AddParameter(m_strName);
	pCmd.AddParameter(atoi(m_strRNo));
	pCmd.AddParameter(::GetNoneDashNumber(m_strMp));
	pCmd.AddParameter(::GetNoneDashNumber(m_strPhone));
	pCmd.AddParameter(::GetNoneDashNumber(m_strPDA));
	pCmd.AddParameter(m_strBankOwner);
	pCmd.AddParameter(m_strBankName);
	pCmd.AddParameter(m_strBankAccount);
	pCmd.AddParameter(m_strRT);
	pCmd.AddParameter(m_dtEnter);
	pCmd.AddParameter(m_strSSN1);
	pCmd.AddParameter(m_strSSN2);
	pCmd.AddParameter(m_nLicenceValid);
	pCmd.AddParameter(m_cmbLicence.GetCurSel());
	pCmd.AddParameter(m_strLicenceNo);

	long nAllocType = ZERO;
	if(m_chkPDAAllocate.GetCheck() && !m_chkSmsAllocate.GetCheck())
		nAllocType = TWO;
	else if(!m_chkPDAAllocate.GetCheck() && m_chkSmsAllocate.GetCheck())
		nAllocType = ONE;

	pCmd.AddParameter(nAllocType);
	pCmd.AddParameter(::GetCarType(&m_cmbCarType));
	pCmd.AddParameter(m_cmbShareLimit.GetCurSel());

	if(m_chkAllocateLimit.GetCheck())
	{
		CString strLockTime; m_cmbAllocateLimitMinute.GetWindowText(strLockTime);
		CString strLockCount; m_cmbAllocateLimitCount.GetWindowText(strLockCount);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(strLockTime));
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),	(strLockCount == "무제한")? 100 : atoi(strLockCount) );
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
	}

	pCmd.AddParameter(m_cmbWorkState.GetCurSel());
	pCmd.AddParameter(m_cmbAllocGroup.GetCurSel());
	pCmd.AddParameter(m_strAddress);
	pCmd.AddParameter(atoi(m_strMarketLine));
	pCmd.AddParameter(m_strMemo);
	pCmd.AddParameter(m_strInnerMemo);
	pCmd.AddParameter(m_bAuto);	
	pCmd.AddParameter(m_bBigAuto);
	pCmd.AddParameter(m_bDama);
	pCmd.AddParameter(m_bRabo);
	pCmd.AddParameter(m_bSedan);
	pCmd.AddParameter(m_bTruck);
	pCmd.AddParameter(GetDepositType());
	pCmd.AddParameter(GetDepositAllocateType());
	pCmd.AddParameter(m_nMyCallRateType);
	pCmd.AddParameter(m_nOtherCallRateType);
	pCmd.AddParameter(m_bNotShowRightOrder); 
	m_strDailyReportCharge.Replace(",", "");
	pCmd.AddParameter(atoi(m_strDailyReportCharge));
	pCmd.AddParameter((long)m_cmbBankID.GetItemData(m_cmbBankID.GetCurSel()));
	pCmd.AddParameter(m_chkWithDrawType.GetCheck());
	pCmd.AddParameter(::GetWindowTextLong(&m_edtMaxWithDrawMoneyPerDay));
	pCmd.AddParameter(::GetWindowTextLong(&m_edtMinLeftMoneyForWithDraw));
	pCmd.AddParameter(m_chkUseRiderTax.GetCheck());
	pCmd.AddParameter(m_strRtSerial); 
	pCmd.AddParameter(m_chkAuto.GetCheck());
	pCmd.AddParameter(atoi(m_strTruckMyDepositRate));
	pCmd.AddParameter(atoi(m_strTruckOtherDepositRate));
	pCmd.AddParameter(m_strCarNo); 
	m_strAllocMinCharge.Replace(",", "");
	pCmd.AddParameter(atoi(m_strAllocMinCharge));
	pCmd.AddParameter(m_cmbBusinessCar.GetCurSel());
	CMkParameter *parAdminTable = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parANo = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(pCmd.Execute() == FALSE)
		return FALSE;

	long nRet = 0;
	parRet->GetValue(nRet);
	parAdminTable->GetValue(m_bLastAdminTable);
	parANo->GetValue(m_nLastANo);

	if(nRet == 10)
	{
		MessageBox("아이디(PDA번호)가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 20)
	{
		MessageBox("사원번호가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	
	if(!pCmd.Execute())
		return FALSE;

	MessageBox("등록 되었습니다", "확인", MB_ICONINFORMATION);	
	
	if(m_edtIncome.GetWindowTextLength() > ZERO &&	m_edtIncomeMemo.GetWindowTextLength() > ZERO)
	{
		CString strIncome; CString strIncomeMemo;
		m_edtIncome.GetWindowText(strIncome); strIncome.Replace(",", "");
		m_edtIncomeMemo.GetWindowText(strIncomeMemo);
		IncomeRider((long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()), atoi(m_strRNo), m_strName, atoi(strIncome), strIncomeMemo, (long)m_cmbIncome.GetItemData(m_cmbIncome.GetCurSel()));
	}

	if(m_cmbWorkState.GetCurSel() != 2)
	{
		long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
		if(CLoadInsurance::IsForceLoadInsuranceRegister(nCompany)) //강제등록 시킬것인지.
		{
			CLoadInsuranceData st;
			st.strSSN = m_strSSN1 + m_strSSN2;

			CLoadInsurance d(LOAD_INS_SEARCH, &st, "조회");
			BOOL bRegister = d.Open();

			if(bRegister == FALSE || st.nWorkState == LOAD_INS_WORK_STATE_CANCEL) //보험에 등록되어 있지 않거나. 당일이후로 해지됨.
			{	
				long nCarType = ::GetCarType(&m_cmbCarType);

				if(CLoadInsurance::IsAbleCarType(nCarType))
				{					
					st.strCompanyName = m_ci.GetCompanyName(nCompany);
					st.nRNo = atoi(m_strRNo);
					st.strSSN = m_strSSN1 + m_strSSN2;
					st.strPhone = m_strPDA;
					st.strCarNo = m_strCarNo;
					st.strRiderName = m_strName;
					st.nRiderCompany = nCompany;
					st.nCarType = CLoadInsurance::GetCarTypeForLoadIns(nCarType);

					CLoadInsurance d(LOAD_INS_INSERT, &st, "신규가입");

					if(d.Open())
					{
						MessageBox("신규가입으로 적재물 보험에 등록되었습니다.", "확인", MB_ICONINFORMATION);
					}
					else
					{
						MessageBox(st.strErrorMsg, "확인", MB_ICONINFORMATION);
					}
				}
			}
		}
	}

	InsertTRSRider();

	return TRUE;
}

BOOL CStaffForm14::UpdateUser()
{
	UpdateData(TRUE);

	if(CheckLocal() == FALSE)
		return FALSE;
	 
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(!info)
	{
		MessageBox("수정하실 기사님을 선택 후 수정 버튼을 클릭하세요", "확인", MB_ICONINFORMATION);
		return FALSE;			
	}

	if(info->nWorkState == 0 && m_cmbWorkState.GetCurSel() == 1 && info->nDailyDepositCharge > 0)
	{
		if(MessageBox("일비차감 설정은 그대로 차감됩니다\r\n일비차감 설정 변경해주세요\r\n\r\n계속 진행하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
			return FALSE;
	}

	//if(!CheckRetireAble(info->nCompany, info->nRNo, info->strSSN1 + info->strSSN2)) // 프로시져 안에서 체크
	//	return;

	CMkCommand pCmd(m_pMkDb, "update_rider_info_19");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nLastANo);
	pCmd.AddParameter(m_bLastAdminTable);
	pCmd.AddParameter(info->nCompany);
	pCmd.AddParameter(m_strName);
	pCmd.AddParameter(atoi(m_strRNo));
	pCmd.AddParameter(::GetNoneDashNumber(m_strMp));
	pCmd.AddParameter(::GetNoneDashNumber(m_strPhone));
	pCmd.AddParameter(::GetNoneDashNumber(m_strPDA));
	pCmd.AddParameter(m_strBankOwner);
	pCmd.AddParameter(m_strBankName);
	pCmd.AddParameter(m_strBankAccount);
	pCmd.AddParameter(m_strRT);
	pCmd.AddParameter(m_dtEnter);
	pCmd.AddParameter(m_strSSN1);
	pCmd.AddParameter(m_strSSN2);
	pCmd.AddParameter(m_nLicenceValid);
	pCmd.AddParameter(m_cmbLicence.GetCurSel());
	pCmd.AddParameter(m_strLicenceNo);

	long nAllocType = ZERO;
	if(m_chkPDAAllocate.GetCheck() && !m_chkSmsAllocate.GetCheck())
		nAllocType = TWO;
	else if(!m_chkPDAAllocate.GetCheck() && m_chkSmsAllocate.GetCheck())
		nAllocType = ONE;

	pCmd.AddParameter(nAllocType);
	pCmd.AddParameter(::GetCarType(&m_cmbCarType));
	pCmd.AddParameter(m_cmbShareLimit.GetCurSel());

	if(m_chkAllocateLimit.GetCheck())
	{
		CString strLockTime; m_cmbAllocateLimitMinute.GetWindowText(strLockTime);
		CString strLockCount; m_cmbAllocateLimitCount.GetWindowText(strLockCount);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(strLockTime));
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),	(strLockCount == "무제한")? 100 : atoi(strLockCount) );
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
	}

	pCmd.AddParameter(info->bAdminTable == TRUE ? info->nWorkState : TWO);
	pCmd.AddParameter(m_cmbWorkState.GetCurSel());
	pCmd.AddParameter(m_cmbAllocGroup.GetCurSel());
	pCmd.AddParameter(m_strAddress);
	pCmd.AddParameter(atoi(m_strMarketLine));
	pCmd.AddParameter(m_strMemo);
	pCmd.AddParameter(m_strInnerMemo);
	pCmd.AddParameter(m_bAuto);	
	pCmd.AddParameter(m_bBigAuto);
	pCmd.AddParameter(m_bDama);
	pCmd.AddParameter(m_bRabo);
	pCmd.AddParameter(m_bSedan);
	pCmd.AddParameter(m_bTruck);
	pCmd.AddParameter(GetDepositType());
	pCmd.AddParameter(GetDepositAllocateType());
	pCmd.AddParameter(m_nMyCallRateType);
	pCmd.AddParameter(m_nOtherCallRateType); 
	pCmd.AddParameter(m_bNotShowRightOrder); 
	m_strDailyReportCharge.Replace(",", "");
	pCmd.AddParameter(atoi(m_strDailyReportCharge));
	pCmd.AddParameter((long)m_cmbBankID.GetItemData(m_cmbBankID.GetCurSel()));
	pCmd.AddParameter(m_chkWithDrawType.GetCheck()); 
	pCmd.AddParameter(::GetWindowTextLong(&m_edtMaxWithDrawMoneyPerDay));
	pCmd.AddParameter(::GetWindowTextLong(&m_edtMinLeftMoneyForWithDraw));
	pCmd.AddParameter(m_cmbInsType.GetCurSel()); 
	pCmd.AddParameter(m_chkUseRiderTax.GetCheck()); 
	pCmd.AddParameter(m_strRtSerial); 
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_chkAutoAllocate.GetCheck()); 
	pCmd.AddParameter(atoi(m_strTruckMyDepositRate));
	pCmd.AddParameter(atoi(m_strTruckOtherDepositRate));
	pCmd.AddParameter(m_strCarNo);

	m_strAllocMinCharge.Replace(",", "");
	pCmd.AddParameter(atoi(m_strAllocMinCharge)); 
	pCmd.AddParameter(m_cmbBusinessCar.GetCurSel());

	CMkParameter *parANo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parAdminTable = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parError = pCmd.AddParameter(typeString, typeOutput, 100, "");

	if(!pCmd.Execute())
	return FALSE;

	long nRet = 0;
	parRet->GetValue(nRet);
	parANo->GetValue(m_nLastANo);
	parAdminTable->GetValue(m_bLastAdminTable);	

	if(nRet == 10)
	{
		MessageBox("아이디(PDA번호)가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 20)
	{
		MessageBox("사원번호가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 30)
	{
		CString strError; parError->GetValue(strError);
		MessageBox(strError, "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	//1, 재직 -> 퇴사상태 //다른주민번호가 등록되어 있는지를 체크후 보험해지
	//2. 퇴사 -> 재직 // 다른곳에 등록되 있는지 확인후 보험등록
	//3. 재직상태가 변경되지 않으면 보험에정보와 비교해서 해지후 재등록,

	if(CLoadInsurance::IsForceLoadInsuranceRegister(info->nCompany)) //강제등록 시킬것인지.
	{
		if(!(info->bAdminTable == FALSE && m_cmbWorkState.GetCurSel() == TWO))
		{
			long nCarType = ::GetCarType(&m_cmbCarType);
			CLoadInsurance::CheckRiderStateChange(info, m_cmbWorkState.GetCurSel() < TWO ? TRUE : FALSE,
				m_strSSN1 + m_strSSN2, nCarType, m_strCarNo);
		}		
	}
	
	return TRUE;
}
	
long CStaffForm14::GetDepositType()
{
	if(m_cmbDepositType.GetCurSel() == ZERO) return 20;
	else if(m_cmbDepositType.GetCurSel() == ONE) return 30;
	else if(m_cmbDepositType.GetCurSel() == TWO) return 40;
	else if(m_cmbDepositType.GetCurSel() == THREE) return 50;
	return 50;
}

long CStaffForm14::GetDepositAllocateType()
{
	if(m_cmbDepositAllocateType.GetCurSel() == ZERO) return ZERO;
	else if(m_cmbDepositAllocateType.GetCurSel() == ONE) return TEN;
	else if(m_cmbDepositAllocateType.GetCurSel() == TWO) return 20;
	return ZERO;
}

void CStaffForm14::OnBnClickedIncomeBtn()
{
	if(!POWER_CHECK(7031, "선입금충전전용", TRUE))
		return;

	if(m_bAddRiderMode)
	{
		if(m_edtIncome.GetWindowTextLength() <= 0)
		{
			MessageBox("입금하실 금액을 입력하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		if(m_edtIncome.GetWindowTextLength() <= 0)
		{
			MessageBox("입금 적요를 입력하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		MessageBox("신규 기사의 경우 등록을 클릭하시면 기사 등록과 동시에 입금(차감)이 이루어집니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	CString strIncome; m_edtIncome.GetWindowText(strIncome);
	strIncome.Replace(",", "");
	CString strIncomeMemo; m_edtIncomeMemo.GetWindowText(strIncomeMemo);
	long nType = (long)m_cmbIncome.GetItemData(m_cmbIncome.GetCurSel());
 
	IncomeRider(info->nCompany, info->nRNo, info->strName, atoi(strIncome), strIncomeMemo, nType, NULL, TRUE);
}

void CStaffForm14::IncomeRider(long nCompany, long nRNo, CString strName, long nIncome, CString strIncomeMemo, long nType, CXTPGridRecord *pRecord , BOOL bPopulate)
{
	/*
	CString strIncome; m_edtIncome.GetWindowText(strIncome);
	CString strIncomeMemo; m_edtIncomeMemo.GetWindowText(strIncomeMemo);

	if(atoi(strIncome) <= ZERO)
	{
		MessageBox("금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(strIncomeMemo.IsEmpty())
	{
		MessageBox("입금적요를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	*/

	//long nType = (long)m_cmbIncome.GetItemData(m_cmbIncome.GetCurSel());

	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_balance_today");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
	pCmd.AddParameter(typeString, typeInput, strName.GetLength(), strName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nType); //잔액충전
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nIncome);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeString, typeInput, strIncomeMemo.GetLength(), strIncomeMemo); //사유

	if(pCmd.Execute())
	{
		if(bPopulate)
		{
			if(nType < 40)
				MessageBox("충전되었습니다", "확인", MB_ICONINFORMATION);
			else
				MessageBox("차감되었습니다", "확인", MB_ICONINFORMATION);
		}

		m_edtIncome.SetWindowText("");
		m_edtIncomeMemo.SetWindowText("");
		RefreshOneRider(pRecord, bPopulate);
	}
}

void CStaffForm14::OnBnClickedMyCallRateTypeBtn()
{
	CRiderDepositGroupDlg dlg;
	dlg.m_bSelectMode = TRUE;
	dlg.m_nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	dlg.m_nDepositRateGroup = m_nMyCallRateType;

	if(dlg.DoModal() == IDOK)
	{
		m_chkMyCall.SetCheck(TRUE);
		m_nMyCallRateType = dlg.m_nDepositRateGroup;
		m_edtMyCallRateType.SetWindowText(dlg.m_strDepositRateGroupName);
	}
}

void CStaffForm14::OnBnClickedOtherCallRateTypeBtn()
{
	CRiderDepositGroupDlg dlg;
	dlg.m_bSelectMode = TRUE;
	dlg.m_nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	dlg.m_nDepositRateGroup = m_nOtherCallRateType;

	if(dlg.DoModal() == IDOK)
	{
		m_chkOtherCall.SetCheck(TRUE);
		m_nOtherCallRateType = dlg.m_nDepositRateGroup;
		m_edtOtherCallRateType.SetWindowText(dlg.m_strDepositRateGroupName);
	}
}

void CStaffForm14::OnCbnSelchangeIncomeCombo()
{
	if(m_cmbIncome.GetCurSel() < TWO)
		m_btnIncome.SetWindowText("입금");
	else
		m_btnIncome.SetWindowText("차감");
}

void CStaffForm14::OnBnClickedRiderPicInsertBtn2()
{
	if(m_bAddRiderMode)
	{
		MessageBox("기사등록 후 진행해 주세요", "확인" ,MB_ICONINFORMATION);
		return;
	}

	ST_RIDER_INFO* info = GetCurSelRiderInfo();

	if(info->bAdminTable == FALSE)
	{
		MessageBox("최사자는 설정 하실 수 없습니다", "확인" ,MB_ICONINFORMATION);
		return;
	}

	CAllocateLimitDlg1 dlg;
	dlg.m_nRiderCompany = info->nCompany;
	dlg.m_nRNo = info->nRNo;

	if(dlg.DoModal() == IDOK)
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		RefreshOneRider();
	}
}

void CStaffForm14::OnBnClickedIncomeSettingBtn()
{
	if(m_bAddRiderMode)
	{
		MessageBox("기사등록 후 진행해 주세요", "확인" ,MB_ICONINFORMATION);
		return;
	}

	ST_RIDER_INFO* info = GetCurSelRiderInfo();

	if(info->bAdminTable == FALSE)
	{
		MessageBox("최사자는 설정 하실 수 없습니다", "확인" ,MB_ICONINFORMATION);
		return;
	}

	CRiderDepositInfoDlg dlg;
	dlg.m_nRiderCompany = info->nCompany;
	dlg.m_nRNo = info->nRNo;
	dlg.m_strRName = info->strName;

	if(dlg.DoModal() == IDOK)
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		RefreshOneRider();
	}
}

void CStaffForm14::OnBnClickedButtonDelete()
{
	if(!POWER_CHECK(5012, "퇴사/삭제/재입사처리", TRUE))
		return;

	int nSelect = MessageBox("삭제를 하시면 데이타가 영구히 지워집니다.\n\n"\
		"삭제 하시겠습니까?","삭제확인창",MB_ICONQUESTION | MB_OKCANCEL);

	if(nSelect != IDOK)
		return;

	ST_RIDER_INFO* info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(!CheckRetireAble(info->nCompany, info->nRNo, info->strSSN1 + info->strSSN2))
		return;

	CMkCommand pCmd(m_pMkDb, "delete_rider_new_2");
	pCmd.AddParameter(info->bAdminTable);
	pCmd.AddParameter(info->nANo);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
	{
		MessageBox("삭제 되었습니다", "확인", MB_ICONINFORMATION);
		m_nLastANo = ZERO;
		m_bLastAdminTable = FALSE;
		RefreshList();
		return;
	}
}

void CStaffForm14::OnEnChangeSaerchEdit()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_SEARCH_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SEARCH_RIDER_EDIT);
	CComboBox *pTypeCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim(); 
 
	//if(pCombo->GetCurSel() == 9)
	//	strText = fc.GetDashPhoneNumber(strText);

	int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_lstReport.Filter(strText, pCombo->GetCurSel(), nTypeData);

	/*
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch); 


	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strPDA = pRecord->GetItem(3)->GetCaption(NULL);
		CString strName = pRecord->GetItem(4)->GetCaption(NULL);

		if(strRNo.Find(strSearch) >= ZERO ||
			strPDA.Find(strSearch) >= ZERO ||
			strName.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
	*/
}

void CStaffForm14::OnBnClickedPdaAllocateCheck()
{
	if(m_chkPDAAllocate.GetCheck())
		m_chkSmsAllocate.SetCheck(FALSE);
}

void CStaffForm14::OnBnClickedSmsAllocateCheck()
{
	if(m_chkSmsAllocate.GetCheck())
		m_chkPDAAllocate.SetCheck(FALSE);
}

void CStaffForm14::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	BCMenu *pRMenu= (BCMenu*)rMenu.GetSubMenu(3);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_card_list");
	cmd.AddParameter(m_ci.m_nShareCode1);

	if(!rs.Execute(&cmd))
		return;


	int nItemCount = pRMenu->GetMenuItemCount();

	if(!IsThisCompany("대전_나이스"))
	{
		pRMenu->RemoveMenu(--nItemCount, MF_BYPOSITION);
		pRMenu->RemoveMenu(--nItemCount, MF_BYPOSITION);
	}


	long nCount = 0;

	for (int i=0; i<rs.GetRecordCount(); i++)
	{
		nCount = i;
		CString strsCardNumber;
		rs.GetFieldValue("sCardNumber", strsCardNumber);

		pRMenu->SetMenuText(GetCardID(i), ::GetDashCardNumber(strsCardNumber), MF_BYCOMMAND);
		m_strCardNumber[i] = strsCardNumber;
		nCount++;

		rs.MoveNext();
	}

	for(int j=nCount; j<CARD_COUNT; j++)
	{
		pRMenu->RemoveMenu(GetCardID(j), MF_BYCOMMAND);
	}

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

long CStaffForm14::GetCardID(long nID)
{
	if(nID == 0) return ID_CARD_NUMBER1;
	if(nID == 1) return ID_CARD_NUMBER2;
	if(nID == 2) return ID_CARD_NUMBER3;
	if(nID == 3) return ID_CARD_NUMBER4;
	if(nID == 4) return ID_CARD_NUMBER5;
	if(nID == 5) return ID_CARD_NUMBER6;
	if(nID == 6) return ID_CARD_NUMBER7;
	if(nID == 7) return ID_CARD_NUMBER8;
	if(nID == 8) return ID_CARD_NUMBER9;
	if(nID == 9) return ID_CARD_NUMBER10;

	return -1;
}

long CStaffForm14::GetIndexFromCardID(long nID)
{
	if(nID == ID_CARD_NUMBER1) return 0;
	if(nID == ID_CARD_NUMBER2) return 1;
	if(nID == ID_CARD_NUMBER3) return 2;
	if(nID == ID_CARD_NUMBER4) return 3;
	if(nID == ID_CARD_NUMBER5) return 4;
	if(nID == ID_CARD_NUMBER6) return 5;
	if(nID == ID_CARD_NUMBER7) return 6;
	if(nID == ID_CARD_NUMBER8) return 7;
	if(nID == ID_CARD_NUMBER9) return 8;
	if(nID == ID_CARD_NUMBER10) return 9;

	return -1;
}

void CStaffForm14::OnViewExcel()
{
	if(!POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 401, m_ui.nWNo, m_lstReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void CStaffForm14::ChangeWorkState(BOOL nWorkState)
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	// Update all of the selected items.
	if(pRows->GetCount() > ZERO)
    {
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
			strWorkMemo = dlg.m_strWorkStopMemo;
		else
			return;

		for (int i = 0;i < pRows->GetCount(); i++)
		{
			CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
			ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);

			CMkCommand pCmd(m_pMkDb, "update_rider_workstate_2008_1");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), info->nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), info->nRNo);		
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nWorkState);
			pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
			pCmd.AddParameter(m_ui.nCompany);
			pCmd.AddParameter(m_ui.nWNo);
			
			if(pCmd.Execute())
				RefreshOneRider(pRecord, FALSE);
		}
	}
	else {
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	}

	m_lstReport.Populate();
}

void CStaffForm14::OnWorkStop()
{
	ChangeWorkState(ONE);
}

void CStaffForm14::OnWorkOk()
{
	ChangeWorkState(ZERO);
}


void CStaffForm14::OnMenuMsg()
{
	if(!POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	/*
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info)
	{
		CRiderMsgDlg dlg;
		dlg.m_nRNo = info->nRNo;
		dlg.DoModal();
	}
	*/

	CRiderMsgDlg dlg;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		MSG_RIDER_INFO *pMRI = new MSG_RIDER_INFO;
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		ST_RIDER_INFO* st = GetCurSelRiderInfo(pRecord);

		pMRI->nCompany = st->nCompany;
		pMRI->nRNo = st->nRNo;
		dlg.m_paSelected.Add(pMRI);
	}

	dlg.DoModal();
}

void CStaffForm14::OnBnClickedAllCheck()
{ 
	m_chkAuto.SetCheck(m_chkAll.GetCheck());
	m_chkBigAuto.SetCheck(m_chkAll.GetCheck());
	m_chkDama.SetCheck(m_chkAll.GetCheck());
	m_chkRabo.SetCheck(m_chkAll.GetCheck());
	m_chkSedan.SetCheck(m_chkAll.GetCheck());
	m_chkTruck.SetCheck(m_chkAll.GetCheck());
}

void CStaffForm14::OnBnClickedAutoCheck()
{
	CheckAll();
}

void CStaffForm14::CheckAll()
{
	if(m_chkAuto.GetCheck() &&
		m_chkBigAuto.GetCheck() &&
		m_chkDama.GetCheck() &&
		m_chkRabo.GetCheck() &&
		m_chkSedan.GetCheck() &&
		m_chkTruck.GetCheck())
		m_chkAll.SetCheck(TRUE);
	else
		m_chkAll.SetCheck(FALSE);
}
void CStaffForm14::OnBnClickedBigAutoCheck()
{
	CheckAll();
}

void CStaffForm14::OnBnClickedDamaCheck()
{
	CheckAll();
}

void CStaffForm14::OnBnClickedRaboCheck()
{
	CheckAll();
}

void CStaffForm14::OnBnClickedBanCheck()
{
	CheckAll();
}

void CStaffForm14::OnBnClickedTruckCheck()
{
	CheckAll();
}

void CStaffForm14::SetDefaultDepositRate()
{
	long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());

	RATE_INFO_MAP::iterator it = m_mapRate.find(nCompany);

	if(it == m_mapRate.end())
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_default_deposit_rate");
		pCmd.AddParameter(nCompany);

		if(!pRs.Execute(&pCmd))
			return;

		ST_RATE *info = new ST_RATE;

		pRs.GetFieldValue("nType", info->nType);
		pRs.GetFieldValue("sTypeName", info->strTypeName);

		m_mapRate.insert(RATE_INFO_MAP::value_type(nCompany, info));
	}

	it = m_mapRate.find(nCompany);
	ST_RATE *info = it->second;

	m_chkMyCall.SetCheck(TRUE);
	m_chkOtherCall.SetCheck(TRUE);
	m_edtMyCallRateType.SetWindowText(info->strTypeName);
	m_edtOtherCallRateType.SetWindowText(info->strTypeName);
	m_nMyCallRateType = info->nType;
	m_nOtherCallRateType = info->nType;
}

void CStaffForm14::OnCbnSelchangeBranchCombo()
{
	if(m_bAddRiderMode == TRUE)
		SetDefaultDepositRate();
}

void CStaffForm14::OnBnClickedMycallCheck()
{
	if(m_chkMyCall.GetCheck() == FALSE)
	{
		m_edtMyCallRateType.SetWindowText("");
		m_nMyCallRateType = 0;
	}
}

void CStaffForm14::OnBnClickedOthercallCheck()
{
	if(m_chkOtherCall.GetCheck() == FALSE)
	{
		m_edtOtherCallRateType.SetWindowText("");
		m_nOtherCallRateType = 0;
	}
}

void CStaffForm14::OnCbnSelchangeSearchCombo()
{

}

void CStaffForm14::OnCbnSelchangeCarTypeCombo()
{
	// 아래 다시정리 // choe
	int car_type = ::GetCarType(&m_cmbCarType);

	if(::IsCarTypeTruck(car_type)) {
		m_chkAuto.SetCheck(FALSE);
		m_chkBigAuto.SetCheck(FALSE); 
		m_chkDama.SetCheck(FALSE);
		m_chkRabo.SetCheck(FALSE);
		m_chkSedan.SetCheck(FALSE);
		m_chkTruck.SetCheck(TRUE);
		m_chkAll.SetCheck(FALSE);
	}
	else if(car_type == CAR_AUTO) {
		m_chkAuto.SetCheck(TRUE);
		m_chkBigAuto.SetCheck(FALSE); 
		m_chkDama.SetCheck(FALSE);
		m_chkRabo.SetCheck(FALSE);
		m_chkSedan.SetCheck(FALSE);
		m_chkTruck.SetCheck(FALSE);
		m_chkAll.SetCheck(FALSE);
	}
	else if(car_type == CAR_BIGBIKE) {
		m_chkAuto.SetCheck(FALSE);
		m_chkBigAuto.SetCheck(TRUE); 
		m_chkDama.SetCheck(FALSE);
		m_chkRabo.SetCheck(FALSE);
		m_chkSedan.SetCheck(FALSE);
		m_chkTruck.SetCheck(FALSE);
		m_chkAll.SetCheck(FALSE);
	}
	else if(car_type == CAR_DAMA) {
		m_chkAuto.SetCheck(FALSE);
		m_chkBigAuto.SetCheck(FALSE); 
		m_chkDama.SetCheck(TRUE);
		m_chkRabo.SetCheck(FALSE);
		m_chkSedan.SetCheck(FALSE);
		m_chkTruck.SetCheck(FALSE);
		m_chkAll.SetCheck(FALSE);
	}
	else if(car_type == CAR_LABO) {
		m_chkAuto.SetCheck(FALSE);
		m_chkBigAuto.SetCheck(FALSE); 
		m_chkDama.SetCheck(FALSE);
		m_chkRabo.SetCheck(TRUE);
		m_chkSedan.SetCheck(FALSE);
		m_chkTruck.SetCheck(FALSE);
		m_chkAll.SetCheck(FALSE);
	}
	else if(car_type == CAR_SEDAN) {
		m_chkAuto.SetCheck(FALSE);
		m_chkBigAuto.SetCheck(FALSE); 
		m_chkDama.SetCheck(FALSE);
		m_chkRabo.SetCheck(FALSE);
		m_chkSedan.SetCheck(TRUE);
		m_chkTruck.SetCheck(FALSE);
		m_chkAll.SetCheck(FALSE);	
	}
	else {
		m_chkAuto.SetCheck(TRUE);
		m_chkBigAuto.SetCheck(TRUE); 
		m_chkDama.SetCheck(TRUE);
		m_chkRabo.SetCheck(TRUE);
		m_chkSedan.SetCheck(TRUE);
		m_chkTruck.SetCheck(TRUE);
		m_chkAll.SetCheck(TRUE);	
	}
	

	EnableShowControl();
}

void CStaffForm14::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
}

void CStaffForm14::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetIndex() <= 4)
	{
		ST_RIDER_INFO *info = GetCurSelRiderInfo();
		LU->ShowRiderInfoDlg(info->nCompany, info->nRNo);
	}

	m_lstReport.SaveReportOrder("CStaffForm14", "m_lstReport");
}

void CStaffForm14::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetIndex() != 20)
		return;

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info  == NULL)
		return;

	CRiderCashLogDlg dlg;
	dlg.m_nCompany = info->nCompany;
	dlg.m_nRNo = info->nRNo;
	dlg.m_strRName = info->strName;

	dlg.DoModal();
}

void CStaffForm14::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CStaffForm14::OnBnClickedJobAddButton()
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(info->bAdminTable == FALSE)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job_not_me");
	pCmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(::GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(info->nANo);

	if(pRs.Execute(&pCmd))
	{
		for(int i=ZERO; i<pRs.GetRecordCount(); i++)
		{
			CString strDisplayName; 
			long nID;

			pRs.GetFieldValue("sDisplayName", strDisplayName);
			pRs.GetFieldValue("nID", nID);

			m_nArryID[i] = nID;
			pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ADD_JOB + i, strDisplayName);

			pRs.MoveNext();
		}

		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	delete pMenu;
	pMenu = NULL;
}

void CStaffForm14::OnBnClickedJobDeleteButton()
{
	if(m_wndJobReport.GetItemCount() == ZERO)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	CXTPGridRecords *pRecords = m_wndJobReport.GetRecords();
	
	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord= pRecords->GetAt(i);
		CString strDisplay = m_wndJobReport.GetItemText(pRecord, 0);

		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_DELETE_JOB + i, strDisplay);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	delete pMenu;
	pMenu = NULL;
}

void CStaffForm14::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_REFRESH_JOB)
	{
		KillTimer(TIMER_REFRESH_JOB);
		RefreshJobList();
		ShowDepositLog(FALSE);
	}

	CMyFormView::OnTimer(nIDEvent);
}

void CStaffForm14::RefreshJobList()
{
	m_wndJobReport.DeleteAllItems();

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(info->bAdminTable == FALSE)
		return;

	long nScheduleID;
	CString strDisplayName;
	BOOL bUse;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_schedule");
	pCmd.AddParameter(info->nANo);

	if(!pRs.Execute(&pCmd))
		return; 
	
	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nScheduleID", nScheduleID);
		pRs.GetFieldValue("sDisplayName", strDisplayName);
		pRs.GetFieldValue("bUse", bUse);

		m_wndJobReport.InsertItem(i, strDisplayName); 
		m_wndJobReport.SetItemLong(i, bUse);
		m_wndJobReport.SetItemLong2(i, nScheduleID);

		pRs.MoveNext();
	}

	m_wndJobReport.Populate();
}

void CStaffForm14::OnMenuAddJob(UINT nFlag)
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(info->bAdminTable == FALSE)
		return;

	long nID = m_nArryID[nFlag - ID_MENU_ADD_JOB];

	CMkCommand pCmd(m_pMkDb, "insert_schedule_rider_1");
	pCmd.AddParameter(nID);
	pCmd.AddParameter(info->nANo);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
		RefreshJobList();
}

void CStaffForm14::OnMenuDeleteJob(UINT nFlag)
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(info->bAdminTable == FALSE)
		return;

	long nIndex = nFlag - ID_MENU_DELETE_JOB;
	long nScheduleID = m_wndJobReport.GetItemLong2(nIndex);
	long nANo = info->nANo;

	CMkCommand pCmd(m_pMkDb, "delete_schedule_rider_1");
	pCmd.AddParameter(nScheduleID);
	pCmd.AddParameter(nANo);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
		RefreshJobList();
}

void CStaffForm14::OnCbnSelchangeDepositTypeCombo1()
{
	long nItem = m_cmbDepositAllocateType.GetCurSel();

	m_cmbDepositAllocateType.ResetContent();

	m_cmbDepositAllocateType.InsertString(0, "선입금");
	m_cmbDepositAllocateType.InsertString(1, "후입금");

	if(m_cmbDepositType.GetCurSel() <= TWO) //월비,주비,일비
		m_cmbDepositAllocateType.InsertString(2, "프로제");

	//m_cmbDepositAllocateType.SetCurSel(min(nItem, m_cmbDepositAllocateType.GetItemCount() - 1));
}

void CStaffForm14::OnChangeRiderColor()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) {MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION); return;};

	CRiderColorDlg dlg;

	if(dlg.DoModal() != IDOK) return;

	for(int i = 0;i < pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		ST_RIDER_INFO *pInfo = GetCurSelRiderInfo(pRecord);	

		CMkCommand pCmd(m_pMkDb, "update_rider_color_only_back");
		pCmd.AddParameter(pInfo->nCompany);
		pCmd.AddParameter(pInfo->nRNo);
		pCmd.AddParameter(dlg.m_nColor);

		if(!pCmd.Execute())
		{
			MessageBox("작업이 실패 했습니다\r\n다시시도해주세요", "확인", MB_ICONINFORMATION);
			return;
		}	

		RefreshOneRider(pRecord, FALSE);
	}

	m_lstReport.Populate();
}

void CStaffForm14::OnBnClicked6banCheck()
{
	CheckAll();
}

void CStaffForm14::OnBnClickedChangeLogBtn()
{
	if(!POWER_CHECK(5015, "근무구분수정로그 보기", TRUE))
		return;

	ST_RIDER_INFO *pInfo = GetCurSelRiderInfo();	

	if(pInfo == NULL)
		return;

	CWorkStateChangeLogDlg dlg;
	dlg.m_nRiderCompany = pInfo->nCompany;
	dlg.m_nRNo = pInfo->nRNo;
	dlg.DoModal();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CStaffForm14::OnCbnSelchangeConWorkingCombo()
{
	RefreshList();
}

void CStaffForm14::OnBnClickedRiderInfoLog()
{
	if(!POWER_CHECK(5016, "기사정보수정로그 보기", TRUE))
		return;


	CREATE_MODALESS(CRiderInfoLogDlg, NULL);
	SHOW_MODALESS(CRiderInfoLogDlg, NULL);
}

void CStaffForm14::OnCardInsertPre()
{

}

void CStaffForm14::OnCardInsertNew()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);

	if(pRecord == NULL || info == NULL)
		return;

	CInsertNewCardDlg dlg;
	
	if(dlg.DoModal() != IDOK)
		return;
	
	if(InsertNewCard(dlg.m_strCardNumber, info->nCompany, info->nRNo))
	{
		MessageBox("등록되었습니다", "확인", MB_ICONINFORMATION);
		RefreshOneRider(pRecord);
		m_lstReport.RedrawControl();
	}
}

void CStaffForm14::OnRiderIncome()
{
	if(m_lstReport.GetFirstSelectedRecord() == NULL)
	{
		MessageBox("충전/차감 할 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CRiderIncomeDlg dlg;

	if(dlg.DoModal() != IDOK)
		return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	long nCount = pRows->GetCount();

	CString strTemp = "";
	strTemp.Format("[%d]명의 기사에게 [%s]원을 [%s]하시겠습니까?", nCount, ::GetMyNumberFormat(dlg.m_nIncome), dlg.m_nType > 10 && dlg.m_nType < 40 ? "입금" : "차감");

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);
		IncomeRider(info->nCompany, info->nRNo, info->strName, dlg.m_nIncome, dlg.m_strIncomeMemo, dlg.m_nType, pRecord, FALSE);
	}

	strTemp = dlg.m_nType > 10 && dlg.m_nType < 40 ? "입금되었습니다" : "차감되었습니다";

	MessageBox(strTemp, "확인", MB_ICONINFORMATION);

	m_lstReport.Populate();
}

void CStaffForm14::OnCardRelease()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);

	if(pRecord == NULL || info == NULL)
		return;

	if(info->strCardNumber.IsEmpty())
	{
		MessageBox("선불카드가 할당 된 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strTemp = "";	

	if(UpdateRiderCardState(info->strCardNumber, 0, 0, strTemp))
	{ 
		MessageBox("해지되었습니다", "확인", MB_ICONINFORMATION);
		RefreshOneRider(pRecord, FALSE);
		m_lstReport.RedrawControl();
	}
}

void CStaffForm14::ShowDepositLog(BOOL bShow)
{
	if(bShow == FALSE)
	{
		if(m_pRiderDepositDlg == NULL)
			return;

		if(!m_pRiderDepositDlg->IsWindowVisible())
			return;
	}

	if(!POWER_CHECK(7020, "통장식로그", TRUE))
		return;

	if(m_pRiderDepositDlg == NULL)
	{
		m_pRiderDepositDlg = new CRiderDepositLogDlg(this);
		m_pRiderDepositDlg->Create(CRiderDepositLogDlg::IDD, this);
	}	

	m_pRiderDepositDlg->ShowWindow(SW_SHOW);

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	m_pRiderDepositDlg->RefreshOneRider(info->nCompany, info->nRNo);
}

void CStaffForm14::OnShowDepositLog()
{
	ShowDepositLog(TRUE);
}

void CStaffForm14::OnEnChangeMemoEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CMyFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CStaffForm14::OnBnClickedInitLogBtn()
{
	if(!POWER_CHECK(5017, "초기화수정로그 보기", TRUE))
		return;

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	CREATE_MODALESS(CRiderInitLogDlg, NULL);
	pDlg->m_nCompany = info->nCompany;;
	pDlg->m_nRNo = info->nRNo;
	SHOW_MODALESS(CRiderInitLogDlg, NULL);
}

void CStaffForm14::OnBnClickedLoadInsuranceBtn()
{	
	MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
	return;

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	if(info == NULL)
		return;

	if(info->strSSN1.IsEmpty() || info->strSSN2.IsEmpty())
	{
		MessageBox("주민번호가 입력되지 않았습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(info->bAdminTable == FALSE)
	{
		MessageBox("퇴사자입니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!CLoadInsurance::IsAbleCarType(info->nCarType))
	{
		MessageBox("1톤 이상의 차령은 적재물 보험에 가입이 불가능합니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CLoadInsuranceDlg dlg;
	dlg.m_strSSN = info->strSSN1 + info->strSSN2;
	dlg.m_strCarNo = info->strCarNo;
	dlg.m_nCompany = info->nCompany;
	dlg.m_nRNo = info->nRNo;
	dlg.m_strName = info->strName;
	dlg.m_strSID = info->strID;
	dlg.m_nCarType = info->nCarType;
	dlg.DoModal();	

//	CLoadInsurance d("");
	//CLoadInsuranceDlg dlg;
	//dlg.DoModal();	
}

void CStaffForm14::OnBnClickedInsRegisterCheck()
{
	BOOL bCheck = !m_chkInsNotRegister.GetCheck(); 

	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	CString strSSN = info->strSSN1 + info->strSSN2;

	if(info == NULL)
	{
		MessageBox("보험에 가입/해지 하실 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		m_chkInsNotRegister.SetCheck(bCheck);
		return;
	}

	if(info->bAdminTable == FALSE)
	{
		MessageBox("퇴가자는 보험에 가입/해지 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		m_chkInsNotRegister.SetCheck(bCheck);
		return;
	}

	if(!IsRiderInsOk(info->strSSN1 + info->strSSN2))
	{
		MessageBox("보험 가입/해지 일주일 이후 수정하실수 있습니다", "확인", MB_ICONINFORMATION);
		m_chkInsNotRegister.SetCheck(bCheck);
		return;
	}	

	if(LU->IsSSNOk(info->strSSN1 + info->strSSN2) == FALSE)
	{
		MessageBox("주민번호가 유효하지 않습니다.", "확인", MB_ICONINFORMATION);
		m_chkInsNotRegister.SetCheck(bCheck);
		return;
	}

	CString strTemp = "";
	strTemp += "보험이 가입/해지시 일주일이내 재등록 하실수 없습니다\r\n";
	strTemp += "해당 주민번호로 타사에 등록시 타사에 등록된 보험정보도 함께 수정됩니다\r\n";
	strTemp += "보험가입시 가입당일 이후로 적용이 됩니다\r\n";
	strTemp += "보험해지시 당일까지 보험이 적용됩니다\r\n";
	strTemp += "\r\n";
	strTemp += CString(bCheck == TRUE ? "가입" : "해지") + "하시겠습니까?";

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
	{
		m_chkInsNotRegister.SetCheck(bCheck);
		return;
	}

	if(LoadInsRegister(bCheck))
	{
		if(bCheck)
		{
			MessageBox("가입되었습니다. 당일 0시 이후로 보험이 적용됩니다", "확인", MB_ICONINFORMATION);
		}
		else
		{		
			MessageBox("해지되었습니다. 당일 0시 이후로 보험이 적용되지 않습니다", "확인", MB_ICONINFORMATION);
		}

		RefreshOneRider();
		CheckLoadIns(strSSN, bCheck);
	}
}

void CStaffForm14::CheckLoadIns(CString strSSN, BOOL bRegister)
{
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		ST_RIDER_INFO *info = GetCurSelRiderInfo(pRecord);

		if(strSSN == info->strSSN1 + info->strSSN2)
		{
			info->bRegisterLoadIns = bRegister;

			if(info->bRegisterLoadIns)
				m_lstReport.SetItemText(pRecord,31, "가입");
			else	 
				m_lstReport.SetItemText(pRecord, 31, "");
		}
	}

	m_lstReport.RedrawWindow();
}

BOOL CStaffForm14::IsRiderInsOk(CString strSSN)
{
	COleDateTime dtGenerate;
	CMkCommand cmd(m_pMkDb, "select_is_rider_load_ins_ok");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(strSSN);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	return FALSE;
}


BOOL CStaffForm14::LoadInsRegister(BOOL bRegister)
{
	ST_RIDER_INFO *info = GetCurSelRiderInfo();

	COleDateTime dtGenerate;
	CMkCommand cmd(m_pMkDb, "insert_rider_load_ins");
	cmd.AddParameter(info->nCompany);
	cmd.AddParameter(info->nRNo);
	cmd.AddParameter(info->strName);
	cmd.AddParameter(info->strSSN1 + info->strSSN2);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(bRegister);

	return cmd.Execute();
}

BOOL CStaffForm14::CheckCarNo(CString strCarNo)
{
	CMkCommand cmd(m_pMkDb, "select_check_car_no");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(strCarNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	return FALSE;
}

BOOL CStaffForm14::InsertTRSRider()
{
	CString strOutboundCID = ::GetNoneDashNumber(m_strMp);

	if(!::IsPhoneNumber(strOutboundCID) || strOutboundCID.Left(2) != "01" || 
		(strOutboundCID.GetLength() < 10 || strOutboundCID.GetLength() > 12))
	{
		MessageBox("휴대폰 번호가 유효하지 않아 TRS 등록하지 못합니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkCommand cmd(m_pMkDb, "insert_trs_message_telserver_extension_1");
	cmd.AddParameter((long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	cmd.AddParameter((long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	cmd.AddParameter(atoi(m_strRNo));
	cmd.AddParameter(strOutboundCID);
	cmd.AddParameter(strOutboundCID);
	cmd.AddParameter(m_ui.nCompany); 
	cmd.AddParameter(m_ui.nWNo); 
	cmd.AddParameter(m_ui.strName);
	CMkParameter *parInsertID = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute())
		return FALSE;

	long nInsertID = 0;
	parInsertID->GetValue(nInsertID);

	if(nInsertID < 0)
	{
		MessageBox("TRS에 등록하지 못했습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

void CStaffForm14::OnCancelType0()
{
	UpdateCancelType(0);
}

void CStaffForm14::OnCancelType1()
{
	UpdateCancelType(1);
}

void CStaffForm14::OnCancelType2()
{
	UpdateCancelType(2);
}

void CStaffForm14::UpdateCancelType(long nCancelType)
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	long nUpdateCount = 0;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		ST_RIDER_INFO *st = GetCurSelRiderInfo(pRecord);

		if(!st->bAdminTable)
			continue;
		
		CMkCommand cmd(m_pMkDb, "update_rider_penalty_type_cancel");
		cmd.AddParameter(st->nCompany);
		cmd.AddParameter(st->nRNo);
		cmd.AddParameter(nCancelType);

		if(cmd.Execute())
		{
			RefreshOneRider(pRecord, FALSE);
			nUpdateCount++;
		}
	}

	if(nUpdateCount > 0)
	{
		MessageBox(::GetStringFromLong(nUpdateCount) + "명의 기사님에게 적용되었습니다", "확인", MB_ICONINFORMATION);
		m_lstReport.RedrawControl();
	}
}

BOOL CStaffForm14::CheckRetireAble(int nRiderCompany, int nRNo, CString strSSN) 
{
	if(::GetCarType(&m_cmbCarType) != CAR_AUTO &&
		::GetCarType(&m_cmbCarType) != CAR_BIGBIKE)
		return TRUE;		

	CMkCommand cmd(m_pMkDb, "check_retire_available");
	CMkParameter *pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);
	cmd.AddParameter(strSSN);
	CMkParameter *pParMsg = cmd.AddParameter(typeString, typeOutput, 200, "");

	if(!cmd.Execute())
		return FALSE;

	long nRet; CString strMsg;
	pParRet->GetValue(nRet);
	pParMsg->GetValue(strMsg);

	if(nRet == 0) 
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);	

	return nRet;
}

void CStaffForm14::OnEnChangeSsnEdit1()
{
	ChangeSSNColor();
}

void CStaffForm14::OnEnChangeSsnEdit2()
{
	ChangeSSNColor();
}

void CStaffForm14::ChangeSSNColor()
{
	CString ssn = ::GetStringFromEdit(&m_edtSSN1) + ::GetStringFromEdit(&m_edtSSN2);

	if (!LU->IsSSNOk(ssn) && ssn != "1111111111111") {
		m_edtSSN1.SetUserOption(RGB(255, 255, 255), RGB(255, 0, 0), "주 민");
		m_edtSSN2.SetUserOption(RGB(255, 255, 255), RGB(255, 0, 0), "번 호");
	}
	else {
		m_edtSSN1.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "주 민");
		m_edtSSN2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "번 호");
	}

	m_edtSSN1.Invalidate();
	m_edtSSN2.Invalidate();
}