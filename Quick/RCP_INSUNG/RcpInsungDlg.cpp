// RcpInsungDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpInsungDlg.h"
#include "SearchCustomerInsungDlg.h"
#include "CustomerDlg.h"
#include "SearchDongInsungDlg.h"
#include "SearchDongInsungJibunDlg.h"
#include "InsungCustomerDlg.h"
#include "RcpView.h"
#include "SearchCustomerInsungRcpDlg.h"
#include "historyInsungDlg.h"
// CRcpInsungDlg 대화 상자입니다.

#define TIMER_CID 5500
#define TIMER_FOCUS 5501 
IMPLEMENT_DYNAMIC(CRcpInsungDlg, CRcpDlg)

const COLORREF crLightBlue = RGB(166, 202, 240);
const COLORREF crLightRed = RGB(255, 172, 172);
const COLORREF crGreen = RGB(201, 230, 233);
const COLORREF crGreen2 = RGB(201, 233, 217);
const COLORREF crBtnGreen = RGB(192, 220, 192);

long _paytype[] = { IDC_PAY_TYPE_0_RADIO, IDC_PAY_TYPE_1_RADIO, IDC_PAY_TYPE_2_RADIO, IDC_PAY_TYPE_3_RADIO, IDC_PAY_TYPE_4_RADIO, IDC_PAY_TYPE_7_RADIO};
long _cartype[] = {	IDC_CAR_TYPE_0_RADIO, IDC_CAR_TYPE_2_RADIO, IDC_CAR_TYPE_3_RADIO, IDC_CAR_TYPE_4_RADIO, IDC_CAR_TYPE_5_RADIO, IDC_CAR_TYPE_6_RADIO, IDC_CAR_TYPE_9_RADIO };
long _waytype[] = {	IDC_WAY_TYPE_0_RADIO, IDC_WAY_TYPE_1_RADIO, IDC_WAY_TYPE_2_RADIO};
long _runtype[] = {	IDC_RUN_TYPE_0_RADIO, IDC_RUN_TYPE_1_RADIO, IDC_RUN_TYPE_2_RADIO, IDC_RUN_TYPE_4_RADIO};


//long _car
//CRcpInsungDlg::CRcpInsungDlg(CWnd* pParent /*=NULL*/)
//	: CRcpInsungDlg(CRcpInsungDlg::IDD, pParent)
//{
//}

CRcpInsungDlg::CRcpInsungDlg()
{
	m_bInsertColumn = FALSE;
	m_pHistoryInsung = NULL;
	m_pInsungCustomerDlg = NULL;
}

CRcpInsungDlg::~CRcpInsungDlg()
{
	DELETE_OBJECT(m_pHistoryInsung);
	DELETE_OBJECT(m_pInsungCustomerDlg);
}

//#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d, ID = %d\n", TEXT(__FILE__), TEXT(__LINE__), y);DDX_Control(x, y, z);}


void CRcpInsungDlg::DoDataExchange(CDataExchange* pDX)
{
	CRcpDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_STATIC, m_stcStart);
	DDX_Control(pDX, IDC_DEST_STATIC, m_stcDest);
	DDX_Control(pDX, IDC_CHANGE_START_DEST_BTN, m_btnChangeStartDest);
	DDX_Control(pDX, IDC_ETC_COMBO, m_cmbEtc);

	DDX_Control(pDX, IDC_PAY_TYPE_0_RADIO, m_rdoPayType0);
	DDX_Control(pDX, IDC_PAY_TYPE_1_RADIO, m_rdoPayType1);
	DDX_Control(pDX, IDC_PAY_TYPE_2_RADIO, m_rdoPayType2);
	DDX_Control(pDX, IDC_PAY_TYPE_3_RADIO, m_rdoPayType3);
	DDX_Control(pDX, IDC_PAY_TYPE_4_RADIO, m_rdoPayType4);
	DDX_Control(pDX, IDC_PAY_TYPE_7_RADIO, m_rdoPayType7);

	DDX_Control(pDX, IDC_CAR_TYPE_0_RADIO, m_rdoCarType0);
	DDX_Control(pDX, IDC_CAR_TYPE_2_RADIO, m_rdoCarType2);
	DDX_Control(pDX, IDC_CAR_TYPE_3_RADIO, m_rdoCarType3);
	DDX_Control(pDX, IDC_CAR_TYPE_4_RADIO, m_rdoCarType4);
	DDX_Control(pDX, IDC_CAR_TYPE_5_RADIO, m_rdoCarType5);
	DDX_Control(pDX, IDC_CAR_TYPE_6_RADIO, m_rdoCarType6);
	DDX_Control(pDX, IDC_CAR_TYPE_9_RADIO, m_rdoCarType9);

	DDX_Control(pDX, IDC_WAY_TYPE_0_RADIO, m_rdoWayType0);
	DDX_Control(pDX, IDC_WAY_TYPE_1_RADIO, m_rdoWayType1);
	DDX_Control(pDX, IDC_WAY_TYPE_2_RADIO, m_rdoWayType2);

	DDX_Control(pDX, IDC_RUN_TYPE_0_RADIO, m_rdoRunType0);
	DDX_Control(pDX, IDC_RUN_TYPE_1_RADIO, m_rdoRunType1);
	DDX_Control(pDX, IDC_RUN_TYPE_2_RADIO, m_rdoRunType2);
	DDX_Control(pDX, IDC_RUN_TYPE_4_RADIO, m_rdoRunType4);

	DDX_Control(pDX, IDC_RESERVE_CHECK, m_chkReserve);
	DDX_Control(pDX, IDC_RESERVE_DATE_DTP, m_dtpReserveData);
	DDX_Control(pDX, IDC_RESERVE_TIME_DTP, m_dtpReserveTime);
	DDX_Control(pDX, IDC_RELEASE_MIN_EDIT, m_edtReleaseMin);
	DDX_Control(pDX, IDC_CUSTOMER_MEMO_COMBO, m_cmbCustomerMemo);
	DDX_Control(pDX, IDC_TNO_TITLE_STATIC, m_stcTNoTitle);
	DDX_Control(pDX, IDC_STATE_TITLE_STATIC, m_stcStateTitle);
	DDX_Control(pDX, IDC_WNAME_TITLE_STATIC, m_stcWNameTitle);
	DDX_Control(pDX, IDC_RCP_TIME_STATIC, m_stcRcpTime);
	DDX_Control(pDX, IDC_BRANCH_RIGHT_STATIC, m_stcBranchRight);
	DDX_Control(pDX, IDC_ORDER_STATIC, m_stcOrder);
	DDX_Control(pDX, IDC_ORDER_PHONE_STATIC, m_stcOrderPhone);
	DDX_Control(pDX, IDC_ORDER_PHONE_COMBO, m_cmbOrderPhone);
	DDX_Control(pDX, IDC_START_ADDRESS_BTN, m_btnStartAddress);
	DDX_Control(pDX, IDC_START_CLEAR_BTN, m_btnStartClear);
	DDX_Control(pDX, IDC_DEST_CLEAR_BTN, m_btnDestClear);
	DDX_Control(pDX, IDC_DEST_TO_ONAME_BTN, m_btnDestToOName);
	DDX_Control(pDX, IDC_DEST_ADDRESS_BTN, m_btnDestAddress);
	DDX_Control(pDX, IDC_DISTANCE_TITLE_STATIC, m_stcDistanceTitle);
	DDX_Control(pDX, IDC_DISTANCE_STATIC, m_stcDistance);
	DDX_Control(pDX, IDC_USE_CHARGE_CHECK, m_chkUseCharge);
	DDX_Control(pDX, IDC_GI_CHECK, m_chkGI);
	DDX_Control(pDX, IDC_CHARGE_STAT_BTN, m_btnChargeStat);
	DDX_Control(pDX, IDC_RCP_TITLE_STATIC, m_stcRcpTitle);
	DDX_Control(pDX, IDC_RESERVE_RELEASE_STATIC, m_stcReserveRelease);
	DDX_Control(pDX, IDC_SMS_TITLE_STATIC, m_stcSMSTitle);
	DDX_Control(pDX, IDC_SMS_COMBO, m_cmbSMS);
	DDX_Control(pDX, IDC_ETC_STATIC, m_stcEtc);
	DDX_Control(pDX, IDC_ETC_ADD_BTN, m_btnEtcAdd);
	DDX_Control(pDX, IDC_ETC_DELETE_BTN, m_btnEtcDelete);
	DDX_Control(pDX, IDC_CARD_INFO_EDIT, m_edtCardInfo);
	DDX_Control(pDX, IDC_CARD_INFO_EDIT2, m_edtCardInfo2);
	DDX_Control(pDX, IDC_CARD_TITLE_STATIC, m_stcCardTitle);
	DDX_Control(pDX, IDC_TRANS_CHECK, m_chkTrans);
	DDX_Control(pDX, IDC_TAX_SHEET_CHECK, m_chkTaxSheet);
	DDX_Control(pDX, IDC_KM_STATIC, m_stcKM);
	DDX_Control(pDX, IDC_ALLOC_DISTANCE_EDIT, m_edtAllocDistance);
	DDX_Control(pDX, IDC_ALLOC_DISTANCE_TITLE_STATIC, m_stcAllocDistanceTitle);
	DDX_Control(pDX, IDC_RIDER_NO_TITLE_STATIC, m_stcRiderNoTitle);
	DDX_Control(pDX, IDC_RIDER_COMPANY_TITLE_STATIC, m_stcRiderCompanyTitle);
	DDX_Control(pDX, IDC_RIDER_PHONE_TITLE_STATIC, m_stcRiderPhoneTitle);
	DDX_Control(pDX, IDC_RIDER_GROUP_STATIC, m_stcRiderGroup);
	DDX_Control(pDX, IDC_CARGO_SHARE_CHECK, m_chkCargoShare);
	DDX_Control(pDX, IDC_NO_FEE_CHECK, m_chkNoFee);
	DDX_Control(pDX, IDC_ITEM_TYPE_COMBO_STATIC, m_stcItemType);
	DDX_Control(pDX, IDC_CHARGE_TYPE_STATIC, m_stcChargeType);
	DDX_Control(pDX, IDC_PAY_TYPE_TITLE_STATIC, m_stcPayTypeTitle);
	DDX_Control(pDX, IDC_CAR_TYPE_TITLE_STATIC, m_stcCarTypeTitle);
	DDX_Control(pDX, IDC_WAY_TYPE_TITLE_STATIC, m_stcWayTypeTitle);
	DDX_Control(pDX, IDC_RUN_TYPE_TITLE_STATIC, m_stcRunTypeTitle);
	DDX_Control(pDX, IDC_CHARGE_BASIC_STATIC, m_stcChargeBasic);
	DDX_Control(pDX, IDC_CHARGE_ADD_STATIC, m_stcChargeAdd);
	DDX_Control(pDX, IDC_CHARGE_DIS_STATIC, m_stcChargeDis);
	DDX_Control(pDX, IDC_CHARGE_TRANS_STATIC, m_stcChargeTrans);
	DDX_Control(pDX, IDC_CHARGE_SUM_STATIC, m_stcChargeSum);
	DDX_Control(pDX, IDC_CHARGE_DRIVING_STATIC, m_stcChargeDriving);
	DDX_Control(pDX, IDC_RIDER_STATIC, m_stcRider);
	DDX_Control(pDX, IDC_SAVE_DEST_CHECK, m_chkSaveDest);


	DDX_Control(pDX, IDC_RIDER_INFO_BTN, m_btnRiderInfo);
	DDX_Control(pDX, IDC_ALLOCATE_BTN, m_btnAllocate);
	DDX_Control(pDX, IDC_RCP_BTN, m_btnRcp);
	DDX_Control(pDX, IDC_RCP_CANCEL_BTN, m_btnRcpCancel);
	DDX_Control(pDX, IDC_RCP_WAIT_BTN, m_btnRcpWait);
	DDX_Control(pDX, IDC_COMPLETE_BTN, m_btnCancel);
	DDX_Control(pDX, IDC_PRIN_BTN, m_btnPrint);
	DDX_Control(pDX, IDC_ORDER_CUSTOMER_DLG_BTN, m_btnOrderCustomerDlg);
	DDX_Control(pDX, IDC_CUSTOMER_INFO_STATIC, m_stcCustsomerInfo);
	DDX_Control(pDX, IDC_RIDER_NO_EDIT, m_edtRiderNo);
	DDX_Control(pDX, IDC_RIDER_COMPANY_EDIT, m_edtRiderCompany);
	DDX_Control(pDX, IDC_RIDER_PHONE_EDIT, m_edtRiderPhone);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelpStatic);
	DDX_Control(pDX, IDC_TRUCK_TYPE_COMBO, m_cmbTruckType);
}


BEGIN_MESSAGE_MAP(CRcpInsungDlg, CRcpDlg)
	
	ON_BN_CLICKED(ID_SIGN_BTN, &CRcpInsungDlg::OnBnClickedSignBtn)
	ON_EN_SETFOCUS(IDC_START_EDIT, &CRcpInsungDlg::OnEnSetfocusStartEdit)
	ON_BN_CLICKED(IDC_ORDER_CUSTOMER_DLG_BTN, &CRcpInsungDlg::OnBnClickedOrderCustomerDlgBtn)
	ON_BN_CLICKED(IDC_ETC_ADD_BTN, &CRcpInsungDlg::OnBnClickedEtcAddBtn)
	ON_CBN_SELCHANGE(IDC_ETC_COMBO, &CRcpInsungDlg::OnCbnSelchangeEtcCombo)
	ON_BN_CLICKED(IDC_SEARCH_RIDER_BTN, &CRcpInsungDlg::OnBnClickedSearchRiderBtn)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_START_ADDRESS_STATIC, &CRcpInsungDlg::OnStnClickedStartAddressStatic)
	ON_STN_CLICKED(IDC_DEST_ADDRESS_STATIC, &CRcpInsungDlg::OnStnClickedDestAddressStatic)
	ON_WM_CONTEXTMENU()
	
	ON_CBN_KILLFOCUS(IDC_ORDER_PHONE_COMBO, &CRcpInsungDlg::OnCbnKillfocusOrderPhoneCombo)
	ON_CBN_SELCHANGE(IDC_ORDER_PHONE_COMBO, &CRcpInsungDlg::OnCbnSelchangeOrderPhoneCombo)
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, &CRcpInsungDlg::OnBnClickedAllocateBtn)
	ON_BN_CLICKED(IDC_RCP_BTN, &CRcpInsungDlg::OnBnClickedRcpBtn)
	ON_BN_CLICKED(IDC_RCP_CANCEL_BTN, &CRcpInsungDlg::OnBnClickedRcpCancelBtn)
	ON_BN_CLICKED(IDC_RCP_WAIT_BTN, &CRcpInsungDlg::OnBnClickedRcpWaitBtn)
	ON_BN_CLICKED(IDC_COMPLETE_BTN, &CRcpInsungDlg::OnBnClickedCompleteBtn)
	ON_BN_CLICKED(ID_CUSTOMER_CHARGE_BTN2, &CRcpInsungDlg::OnBnClickedCustomerChargeBtn2)
	ON_BN_CLICKED(IDC_CHANGE_START_DEST_BTN, &CRcpInsungDlg::OnBnClickedChangeStartDestBtn)
	ON_BN_CLICKED(IDC_DEST_TO_ONAME_BTN, &CRcpInsungDlg::OnBnClickedDestToOnameBtn)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RIDER_INFO_BTN, &CRcpInsungDlg::OnBnClickedRiderInfoBtn)
	ON_BN_CLICKED(IDC_RIDER_SEARCH_BTN, &CRcpInsungDlg::OnBnClickedRiderSearchBtn) 
	ON_BN_CLICKED(IDC_PAY_TYPE_0_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_PAY_TYPE_1_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_PAY_TYPE_2_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_PAY_TYPE_3_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_PAY_TYPE_4_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_PAY_TYPE_7_RADIO, &CRcpInsungDlg::OnBnClickedPayTypeRadio)
	ON_BN_CLICKED(IDC_ETC_DELETE_BTN, &CRcpInsungDlg::OnBnClickedEtcDeleteBtn)

	
	ON_BN_CLICKED(IDC_NO_FEE_CHECK, &CRcpInsungDlg::OnBnClickedNoFeeCheck)
	ON_BN_CLICKED(ID_PICK_INFO_BTN, &CRcpInsungDlg::OnBnClickedPickup)

	ON_BN_CLICKED(IDC_START_CLEAR_BTN, &CRcpInsungDlg::OnBnClickedStartClearBtn)
	ON_BN_CLICKED(IDC_DEST_CLEAR_BTN, &CRcpInsungDlg::OnBnClickedDestClearBtn)
	ON_BN_CLICKED(ID_CUSTOMER_CHARGE_BTN, &CRcpInsungDlg::OnBnClickedCustomerChargeBtn)
	ON_BN_CLICKED(ID_CUSTOMER_SEARCH_BTN, &CRcpInsungDlg::OnBnClickedCustomerSearchBtn)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CLIENT_SHARE_ORDER_CHECK, &CRcpInsungDlg::OnBnClickedClientShareOrderCheck)

	ON_MESSAGE(WM_INSUNG_CUSTOMER_OK, OnInsungCustomerOk)
	ON_BN_CLICKED(IDC_CAR_TYPE_0_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_2_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_3_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_4_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_5_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_6_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_BN_CLICKED(IDC_CAR_TYPE_9_RADIO, &CRcpInsungDlg::OnBnClickedCarTypeRadio)
	ON_CBN_SELCHANGE(IDC_TRUCK_TYPE_COMBO, &CRcpInsungDlg::OnCbnSelchangeTruckTypeCombo)
END_MESSAGE_MAP()



LONG CRcpInsungDlg::OnInsungCustomerOk(WPARAM wParam, LPARAM lParam)
{
	m_pPlaceCustomer->SearchCustomerCNo((long)wParam, TRUE, TRUE, (long)lParam, FALSE);
	return 0;
}


// CRcpInsungDlg 메시지 처리기입니다.
void CRcpInsungDlg::OnBnClickedSignBtn()
{
	ShowSign();
}

BOOL CRcpInsungDlg::OnInitDialog()
{
	CRcpDlg::OnInitDialog();

	enum {CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK, CAR_SUBWAY, CAR_PS, CAR_6VAN, 
		CAR_1_4_TON, CAR_2_5_TON,CAR_3_5_TON, CAR_5_TON, CAR_11_TON, CAR_18_TON, CAR_25_TON}; //CAR_PARCEL_SERVICE

	
	m_cmbTruckType.InsertString(0, "1톤");
	m_cmbTruckType.SetItemData(0, CAR_TRUCK);
	m_cmbTruckType.InsertString(1, "1.4톤");
	m_cmbTruckType.SetItemData(1, CAR_1_4_TON);
	m_cmbTruckType.InsertString(2, "2.5톤");
	m_cmbTruckType.SetItemData(2, CAR_2_5_TON);
	m_cmbTruckType.InsertString(3, "3.5톤");
	m_cmbTruckType.SetItemData(3, CAR_3_5_TON);
	m_cmbTruckType.InsertString(4, "5톤");
	m_cmbTruckType.SetItemData(4, CAR_5_TON);
	m_cmbTruckType.InsertString(5, "11톤");
	m_cmbTruckType.SetItemData(5, CAR_11_TON);
	m_cmbTruckType.InsertString(6, "18톤");
	m_cmbTruckType.SetItemData(6, CAR_18_TON);
	m_cmbTruckType.InsertString(7, "25톤");
	m_cmbTruckType.SetItemData(7, CAR_25_TON);
	m_cmbTruckType.SetCurSel(0);
	
	CWnd *pWnd = GetWindow(GW_CHILD);
  
	while(pWnd) 
	{ 
		pWnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

		if(pWnd->GetDlgCtrlID() != IDC_HELP_STATIC)
		pWnd->ModifyStyleEx(WS_EX_STATICEDGE, 0, SWP_FRAMECHANGED);
		pWnd = pWnd->GetNextWindow();
	}

	m_btnRiderInfo.ShowWindow(SW_HIDE);	

	m_brPink.CreateSolidBrush(RGB(255, 240, 255));
	m_brWhite.CreateSolidBrush(RGB(255, 255, 255));
	m_brOrange.CreateSolidBrush(RGB(0xEF, 0xE1, 0xC3));
	m_brBlue.CreateSolidBrush(RGB(0xC9, 0xE6, 0xE9)); 
	m_brRed.CreateSolidBrush(RGB(0xF3, 0xCF, 0xCF));
	m_brYellow.CreateSolidBrush(RGB(0xF7, 0xFC, 0x98));
	m_btGreen.CreateSolidBrush(crGreen);
	m_btGreen2.CreateSolidBrush(crGreen2);
	//m_brSystem.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	m_brSystem.CreateSolidBrush(RGB(0xF0, 0xF0, 0xF0));

	LOGFONT lfFont; 
	CFont *pFont = GetFont();
	pFont->GetLogFont(&lfFont);
	lfFont.lfWeight = FW_BOLD;
	m_fntBold.CreateFontIndirect(&lfFont);

	//lfFont.lfHeight += 10;
	m_fntLarge.CreateFontIndirect(&lfFont); 

	m_dtpReserveTime.SetFormat("HH:mm");
	m_cmbEtc.SetDroppedWidth(500);
	m_cmbOrderPhone.SetDroppedWidth(300);
	InitLeftControls();
	InitRightControls();
	RepositionLeftControls();
	RepositionRightControls(); 

	m_EDT_START_NAME.pEdit->SetFocus();

//	m_edtSearchDest.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "qweq");
	

//	m_stcAllocDistanceTitle.SetTextColor(RGB(255, 0, 0));
//	m_edtAllocDistance.SetColor(RGB(255, 0, 0));
//	m_stcKM.SetTextColor(RGB(255, 0, 0));

	

	MakeStartStatic();

  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpInsungDlg::SetButtonShowHide()
{
	//CRect rcNew, rcwait, rcAllocate, rcCancel, rcPrint;
	//m_btnNew.GetWindowRect(rcNew);
	//ScreenToClient(rcNew);
	//m_btnWait.GetWindowRect(rcwait);
	//ScreenToClient(rcwait);	
	//m_btnAllocate.GetWindowRect(rcAllocate);
	//ScreenToClient(rcAllocate);	
	//m_btnClose.GetWindowRect(rcCancel);
	//ScreenToClient(rcCancel);	
	//m_btnPrint.GetWindowRect(rcPrint);
	//ScreenToClient(rcPrint);	
 
	if(m_nInitItem > 0)
	{
		m_btnNew.ShowWindow(FALSE);
		m_btnWait.ShowWindow(FALSE);
		m_btnAllocate.ShowWindow(TRUE);
		m_btnRcp.ShowWindow(TRUE);
		m_btnRcpCancel.ShowWindow(TRUE);
		m_btnRcpWait.ShowWindow(TRUE);
		m_btnCancel.ShowWindow(TRUE);
		m_btnPrint.ShowWindow(TRUE);
		m_EDT_CID.pEdit->EnableWindow(FALSE);
		m_btnUpdate.ShowWindow(TRUE);
		m_btnUpdateAndNew.ShowWindow(TRUE);

		//m_btnNew.SetWindowText("저 장");
		//rcNew.bottom = rcCancel.top - 5;
		//rcNew.top = rcPrint.bottom + 5;
		//m_btnNew.MoveWindow(rcNew);
	}
	else
	{
		m_btnNew.ShowWindow(TRUE);
		m_btnWait.ShowWindow(TRUE);
		m_btnAllocate.ShowWindow(FALSE);
		m_btnRcp.ShowWindow(FALSE);
		m_btnRcpCancel.ShowWindow(FALSE);
		m_btnRcpWait.ShowWindow(FALSE);
		m_btnCancel.ShowWindow(FALSE);
		m_btnPrint.ShowWindow(FALSE);
		m_EDT_CID.pEdit->EnableWindow(TRUE);
		m_btnUpdate.ShowWindow(FALSE);
		m_btnUpdateAndNew.ShowWindow(FALSE);

		//m_btnNew.SetWindowText("접수저장");
		//rcNew.top = rcAllocate.top;
		//rcNew.bottom = rcwait.top - 5;
		//m_btnNew.MoveWindow(rcNew);
	}
}

void CRcpInsungDlg::SetRcpTimeControl(COleDateTime dtTime)
{
	m_stcRcpTime.SetWindowText(dtTime.Format("%Y-%m-%d %H:%M:%S"));
}

void CRcpInsungDlg::OnInitialUpdate()
{
	InitEtcCombo();

	/*
	SetCarTypeNew(CAR_AUTO);
	SetPayTypeNew(PAY_PRE);
	SetWayTypeNew(WAY_ONE);
	SetRunTypeNew(RUN_NORMAL); 
	*/

	CRcpDlg::OnInitialUpdate();

	m_EDT_CID.pEdit->SetFocus(); 
	ChangeRcpState();
	DisplayRiderInfo();
	SetRcpTimeControl(COleDateTime::GetCurrentTime());
	DeleteOphoneCombo();
	

	if(m_nInitItem <= 0 && m_EDT_CID.pEdit->GetWindowTextLength() > 0)
		SetTimer(TIMER_CID, 200, NULL);

	if(m_nInitItem > 0)
		SetTimer(TIMER_FOCUS, 200, NULL);

	m_EDT_CID.pEdit->EnableWindow(TRUE);

	if(m_nInitItem > 0)
	{ 
		FIllOrderCombo();
		SetRcpTimeControl(m_dtRcpTime); 
		m_EDT_START_NAME.pEdit->SetFocus();
	}
	else
		m_EDT_CID.pEdit->SetFocus();
 
	if(LF->GetLongFromEdit(&m_edtDeposit) == 0)
		m_chkNoFee.SetCheck(TRUE);
	else
		m_chkNoFee.SetCheck(FALSE);
	
	//SetButtonShowHide();
}


void CRcpInsungDlg::InitLeftControls()
{
	m_cmbOrderPhone.ShowWindow(SW_HIDE); 
//	m_btnRiderInfo.ShowWindow(SW_HIDE);	

	m_EDT_TNO.edtFlatEditInsung.SetBorderColor(RGB(0, 0, 0));
	m_EDT_TNO.edtFlatEditInsung.SetFont(m_FontManager.GetFont("돋움", 12, FW_BOLD)); 
	m_EDT_CID.edtFlatEditInsung.SetColor(RGB(255, 255, 0), RGB(0, 0, 0));
	m_EDT_CID.edtFlatEditInsung.SetFont(m_FontManager.GetFont("돋움", 35, FW_BOLD));

	m_btnChangeStartDest.SetPushColor(RGB(0, 0, 0), crBtnGreen, XTPDrawHelpers()->DarkenColor(30, crBtnGreen),  XTPDrawHelpers()->DarkenColor(30, crBtnGreen));
	m_btnDestToOName.SetPushColor(RGB(0, 0, 0), crBtnGreen, XTPDrawHelpers()->DarkenColor(30, crBtnGreen),  XTPDrawHelpers()->DarkenColor(30, crBtnGreen));
	m_chkSaveDest.SetCheckColor(RGB(0, 0, 0), crGreen);
	m_btnStartClear.SetPushColor(RGB(255, 0, 0), RGB(255, 255, 0), XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)),  XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)));
	m_btnDestClear.SetPushColor(RGB(255, 0, 0), RGB(255, 255, 0), XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)),  XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)));
	m_chkUseCharge.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_chkGI.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));

	m_EDT_TNO.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_STATE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_WNAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255)); 

	m_EDT_TNO.edtFlatEditInsung.SetColor(RGB(0, 0, 0));
	//m_EDT_STATE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
	//m_EDT_WNAME.edtFlatEditInsung.SetColor(RGB(0, 0, 255));

	m_EDT_ORDER_NAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_ORDER_PHONE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_ORDER_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_ORDER_MANAGER.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_NAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_MANAGER.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_PHONE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_DONG.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_START_DETAIL.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_NAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_MANAGER.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_PHONE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_DONG.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_DEST_DETAIL.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));

	m_EDT_ORDER_NAME.pEdit->SetWindowText("고객님");
	//m_stcOrderPhone.SetWindowText("의뢰자전화번호");
	//m_stcOrderPhone.SetTextColor(crLightBlue);
	m_EDT_START.edtFlatEditInsung.SetHelpText("*검색", RGB(255, 0, 0));
	m_EDT_START_NAME.edtFlatEditInsung.SetHelpText(" *출발지고객명", crLightRed, DT_LEFT);
	m_EDT_START_DEPART.edtFlatEditInsung.SetHelpText(" 부서명", crLightBlue, DT_LEFT);
	m_EDT_START_MANAGER.edtFlatEditInsung.SetHelpText(" 담당/직위명", crLightBlue, DT_LEFT);
	m_EDT_START_PHONE.edtFlatEditInsung.SetHelpText(" *전화번호", crLightRed, DT_LEFT);
	m_EDT_START_DONG.edtFlatEditInsung.SetHelpText(" *출발동명", crLightRed, DT_LEFT);
	//m_STC_START_ADDERSS.stcFlat.SetTextColor(crLightBlue);
	m_EDT_START_DETAIL.edtFlatEditInsung.SetHelpText("출발지상세위치", crLightBlue);
	m_EDT_START_NAME.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
	m_EDT_START_PHONE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
	m_EDT_ORDER_PHONE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));

 
	m_EDT_DEST.edtFlatEditInsung.SetHelpText("*검색", RGB(255, 0, 0));
	m_EDT_DEST_NAME.edtFlatEditInsung.SetHelpText(" *도착지고객명", crLightRed, DT_LEFT);
	m_EDT_DEST_DEPART.edtFlatEditInsung.SetHelpText(" 부서명", crLightBlue, DT_LEFT);
	m_EDT_DEST_MANAGER.edtFlatEditInsung.SetHelpText(" 담당/직위명", crLightBlue, DT_LEFT);
	m_EDT_DEST_PHONE.edtFlatEditInsung.SetHelpText(" *전화번호", crLightRed, DT_LEFT);
	m_EDT_DEST_DONG.edtFlatEditInsung.SetHelpText(" *도착동명", crLightRed, DT_LEFT);
	//m_STC_DEST_ADDERSS.stcFlat.SetTextColor(crLightBlue);
	m_EDT_DEST_DETAIL.edtFlatEditInsung.SetHelpText("도착지상세위치", crLightBlue);
	m_EDT_DEST_NAME.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
	m_EDT_DEST_PHONE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));

	m_stcDistanceTitle.SetTextColor(RGB(255, 0, 0));
	m_stcDistance.SetTextColor(RGB(0, 0, 255));

	//m_stcWName.SetAutoAddSpace(TRUE);
//	m_stcOrderPhone.SetAutoAddSpace(TRUE);
	//m_stcOrderDepart.SetAutoAddSpace(TRUE);
	//m_stcOrderManager.SetAutoAddSpace(TRUE);
	m_STC_START_ADDERSS.stcFlat.SetAutoAddSpace(TRUE);
	m_STC_DEST_ADDERSS.stcFlat.SetAutoAddSpace(TRUE);
	m_stcDistance.SetAutoAddSpace(TRUE);
 
	//m_cmbBranch.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_cmbOrderPhone.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0)); 
	m_cmbCustomerMemo.SetColor(-1, -1, RGB(0xF0, 0xF0, 0xF0), -1, RGB(0, 0, 0));

	m_stcOrderPhone.SetFont(&m_fntBold);
	m_stcTNoTitle.SetFont(&m_fntBold);
	//m_stcTNo.SetFont(&m_fntBold);
	m_stcStateTitle.SetFont(&m_fntBold); 
	//m_stcState.SetFont(&m_fntBold);
	m_stcDistance.SetFont(&m_fntBold);
	m_EDT_ORDER_PHONE.edtFlatEditInsung.SetFont(&m_fntBold);
	m_EDT_START_PHONE.edtFlatEditInsung.SetFont(&m_fntBold);
	m_EDT_DEST_PHONE.edtFlatEditInsung.SetFont(&m_fntBold); 
	m_EDT_STATE.edtFlatEditInsung.SetFont(&m_fntBold); 
	m_CMB_BRANCH.comboInsung.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));

	m_stcHelpStatic.SetFont(m_FontManager.GetFont("돋움", 13, FW_BOLD));
}

void CRcpInsungDlg::InitRightControls()
{
	m_cmbSMS.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_cmbEtc.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_CMB_ALLOC_GROUP.comboInsung.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_cmbItemType.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_CMB_CHARGE_TYPE.comboInsung.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	m_cmbTruckType.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));

	m_chkReserve.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_BTN_NOT_SEND_COMPLETE_SMS.buttonFlat.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_chkTaxSheet.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_chkTrans.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_BTN_AUTO_SHARE_ORDER.buttonFlat.SetCheckColor(RGB(0, 0, 255), RGB(255, 255, 255)); 
	m_chkCargoShare.SetCheckColor(RGB(0, 0, 255), RGB(255, 255, 255));
	m_chkNoFee.SetCheckColor(RGB(255, 0, 0), RGB(255, 255, 255));
	m_chkTrans.SetCheckColor(RGB(0, 0, 255), RGB(255, 255, 255));
	m_chkTaxSheet.SetCheckColor(RGB(0, 0, 255), RGB(255, 255, 255));
	m_chkClientShareOrder.SetCheckColor(RGB(0, 0, 255), RGB(255, 255, 255));

	m_btnEtcDelete.SetPushColor(RGB(255, 0, 0), RGB(255, 255, 0), XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)),  XTPDrawHelpers()->DarkenColor(100, RGB(255, 255, 0)));
	//m_btnNew.SetPushColor(RGB(255, 255, 255), RGB(0, 97,160));
	//m_btnWait.SetPushColor(RGB(255, 255, 255), RGB(0, 97,160));
	//m_btnRiderSearch.SetPushColor(RGB(255, 255, 255), RGB(0, 97,160));
	m_btnNew.SetFont(&m_fntLarge);
	m_btnWait.SetFont(&m_fntLarge);
	m_btnUpdate.SetFont(&m_fntLarge);

	m_EDT_ETC.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_edtReleaseMin.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_BASIC.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_ADD.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_DIS.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_TRANS.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_SUM.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_EDT_CHARGE_DRIVING.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
	m_edtRiderNo.SetBorderColor(RGB(255, 255, 255));
	m_edtRiderCompany.SetBorderColor(RGB(255, 255, 255));
	m_edtRiderPhone.SetBorderColor(RGB(255, 255, 255));
	m_edtAllocDistance.SetBorderColor(RGB(255, 255, 255));
	m_edtCardInfo.SetBorderColor(RGB(255, 255, 255));
	m_edtCardInfo2.SetBorderColor(RGB(255, 255, 255));
	
	//m_cmbSMS.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	//m_cmbEtc.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	//m_cmbAllocGroup.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	//m_cmbItemType.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));
	//m_cmbChargeType.SetColor(-1, -1, RGB(255, 255, 255), -1, RGB(0, 0, 0));

	m_rdoPayType0.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoPayType1.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoPayType2.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoPayType3.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoPayType4.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoPayType7.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType0.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType2.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType4.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType3.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType5.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType6.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoCarType9.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoWayType0.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoWayType1.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoWayType2.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoRunType0.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoRunType1.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoRunType2.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));
	m_rdoRunType4.SetCheckColor(RGB(0, 0, 0), RGB(255, 255, 255));

	m_stcAllocDistanceTitle.SetTextColor(RGB(255, 0, 0));
	m_edtAllocDistance.SetColor(RGB(255, 0, 0));
	m_stcCardTitle.SetTextColor(RGB(255, 0, 0));
	//m_stcKM.SetTextColor(RGB(255, 0, 0));
}


void CRcpInsungDlg::InitEtcCombo()
{
	m_cmbEtc.ResetContent();

	if(m_pBi->sEtcUserMemo1 != "") m_cmbEtc.AddString(m_pBi->sEtcUserMemo1);
	if(m_pBi->sEtcUserMemo2 != "") m_cmbEtc.AddString(m_pBi->sEtcUserMemo2);
	if(m_pBi->sEtcUserMemo3 != "") m_cmbEtc.AddString(m_pBi->sEtcUserMemo3);
	if(m_pBi->sEtcUserMemo4 != "") m_cmbEtc.AddString(m_pBi->sEtcUserMemo4);
		
	CString stRegMemo =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	if(stRegMemo != "") m_cmbEtc.AddString(stRegMemo);
}

void CRcpInsungDlg::MakeStartStatic()
{
	m_btnRiderSearch.SetParent(&m_stcRider);

	CRect rcClient; m_stcRider.GetClientRect(rcClient);
	CRect rc; m_btnRiderSearch.GetClientRect(rc);
	long nHeight = rc.Height();
	long nWidth = rc.Width();

	rc.bottom = rcClient.bottom - 2;
	rc.top = rcClient.bottom - nHeight;
	rc.left = 0;
	rc.right = rc.left + nWidth;
	m_btnRiderSearch.MoveWindow(rc);


	m_btnRiderInfo.SetParent(&m_edtRiderNo);

	m_edtRiderNo.GetClientRect(rcClient);
	m_btnRiderInfo.GetClientRect(rc);
	nHeight = rc.Height();
	nWidth = rc.Width();
 
	rc.right = rcClient.right + 2;
	rc.left = rc.right - nWidth;
	rc.top = rcClient.top - 1;
	rc.bottom = rcClient.bottom + 1;
	m_btnRiderInfo.MoveWindow(rc);

	m_btnRiderSmsSend.SetParent(&m_edtRiderPhone);

	m_edtRiderPhone.GetClientRect(rcClient);
	m_btnRiderSmsSend.GetClientRect(rc);
	nHeight = rc.Height();
	nWidth = rc.Width();

	rc.right = rcClient.right + 2;
	rc.left = rc.right - nWidth;
	rc.top = rcClient.top - 1;
	rc.bottom = rcClient.bottom + 1;
	m_btnRiderSmsSend.MoveWindow(rc);
}

BOOL CRcpInsungDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		if(pMsg->wParam == VK_RETURN)		 
	 	{		
			if(pMsg->hwnd == m_EDT_CID.pEdit->GetSafeHwnd())
			{
				SearchCustomer(PLACE_ORDER);
				return TRUE;
			} 
			else if(pMsg->hwnd == m_EDT_START_NAME.pEdit->GetSafeHwnd())
			{
				if(m_EDT_START_NAME.pEdit->GetWindowTextLength() == 0 &&
					m_pOrder->GetCNo() > 0) 
				{
					m_pStart->Copy(m_pOrder);

					if(m_pBi->bNoDestPoi)
						m_EDT_DEST_DONG.pEdit->SetFocus();
					else
						m_EDT_DEST_NAME.pEdit->SetFocus();
				}
				else
					SearchCustomer(PLACE_START);
				return TRUE;
			}
			else if(pMsg->hwnd == m_EDT_DEST_NAME.pEdit->GetSafeHwnd())
			{
				if(m_EDT_DEST_NAME.pEdit->GetWindowTextLength() == 0 &&
					m_pOrder->GetCNo() > 0)
				{
					m_pDest->Copy(m_pOrder);
					m_EDT_ETC.pEdit->SetFocus();
				}
				else
				SearchCustomer(PLACE_DEST);
				return TRUE;
			}
			else if(pMsg->hwnd == m_EDT_START.pEdit->GetSafeHwnd())
			{
				SearchPoi(PLACE_START);
				return TRUE;
			}
			else if(pMsg->hwnd == m_EDT_DEST.pEdit->GetSafeHwnd())
			{
				SearchPoi(PLACE_DEST);
				return TRUE;
			}
			else if(pMsg->hwnd == m_EDT_START_DONG.pEdit->GetSafeHwnd())
			{
				SearchDong(PLACE_START);
				return TRUE;
			}
			else if(pMsg->hwnd == m_EDT_DEST_DONG.pEdit->GetSafeHwnd())
			{
				SearchDong(PLACE_DEST);
				return TRUE;
			}

			if(pMsg->hwnd == m_EDT_START_DETAIL.pEdit->GetSafeHwnd() ||
				pMsg->hwnd == m_EDT_DEST_DETAIL.pEdit->GetSafeHwnd() ||
				pMsg->hwnd == m_EDT_ETC.pEdit->GetSafeHwnd())
				return CDialog::PreTranslateMessage(pMsg);

			return TRUE;
		}
		else if(pMsg->wParam == VK_F2)
		{
			OnBnClickedOrderCustomerDlgBtn();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F3)
		{
			OnBnClickedRiderSearchBtn();
			return TRUE;
		}
		// 올바로 발신 Edit 창에서 복사시 전화번호 '-' 삭제
		else if(GetKeyState(VK_CONTROL) & 0x8000 && (pMsg->wParam == 'c' || pMsg->wParam == 'C')
			&& LF->IsThisCompany("올바로"))
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_CID_EDIT:
				CString strText, strRet;
				m_EDT_CID.pEdit->GetWindowText(strText);

				DWORD dwSel = m_EDT_CID.pEdit->GetSel();
				strRet = strText.Mid(LOWORD(dwSel), HIWORD(dwSel) - LOWORD(dwSel));

				strRet.Replace("-", "");

				if(strRet.GetLength() > 0)
				{
					if(::OpenClipboard(m_hWnd))
					{
						::EmptyClipboard();

						HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, strRet.GetLength() + 1);
						LPSTR pData = (LPSTR)::GlobalLock(hData);
						::strcpy(pData, strRet);
						::GlobalUnlock(hData);

						::SetClipboardData(CF_TEXT, hData);
						::CloseClipboard();
					}
				}

				return TRUE;
				break;
			}
		}
	}		
	else if(pMsg->message == WM_LBUTTONDOWN)
	{
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		if(pMsg->hwnd == m_EDT_CHARGE_SUM.pEdit->GetSafeHwnd() ||
			pMsg->hwnd == m_EDT_STATE.pEdit->GetSafeHwnd() ||
			pMsg->hwnd == m_EDT_WNAME.pEdit->GetSafeHwnd())
		{
			return TRUE;
		}

		if(pMsg->hwnd == m_EDT_ORDER_PHONE.pEdit->GetSafeHwnd())
		{
			m_EDT_ORDER_PHONE.pEdit->ShowWindow(FALSE);
			m_cmbOrderPhone.ShowWindow(TRUE);
		}		
		if(pMsg->hwnd == m_stcStart.GetSafeHwnd())
			OpenInsungCustomerDlg(PLACE_START);
		if(pMsg->hwnd == m_stcDest.GetSafeHwnd())
			OpenInsungCustomerDlg(PLACE_DEST);
	} 
	else if(pMsg->message == WM_LBUTTONUP)
	{
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		if(pMsg->hwnd == m_btnRiderSearch.GetSafeHwnd())
		{
			OnBnClickedRiderSearchBtn();
		}
		if(pMsg->hwnd == m_btnRiderInfo.GetSafeHwnd())
		{
			OnBnClickedRiderInfoBtn();
			return TRUE;
		}
		if(pMsg->hwnd == m_btnRiderSmsSend.GetSafeHwnd())
		{
			OnBnClickedRiderSMSBtn();
			return TRUE;
		}	
	}
	if(pMsg->message == WM_SYSKEYDOWN)
	{
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		if(pMsg->wParam =='s' || pMsg->wParam == 'S')
		{
			OnBnClickedNewBtn();
		}
		else if(pMsg->wParam =='d' || pMsg->wParam == 'D')
		{
			if(m_nInitItem > 0)
				OnBnClickedWaitBtn();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
	//return CRcpDlg::PreTranslateMessage(pMsg);
}

void CRcpInsungDlg::SearchCustomer(long nType)
{
	CRcpPlaceInfo* pPlace = GetPlaceInfo(nType);

	CString strSearch = pPlace->GetSearch(); //검색이 틀림
	UINT nSearchType = 0;
	CString strKeyWord;

	if(nType == PLACE_ORDER)
		m_EDT_CID.pEdit->GetWindowText(strSearch);
	else if(nType == PLACE_START)
		m_EDT_START_NAME.pEdit->GetWindowText(strSearch);
	else if(nType == PLACE_DEST)
		m_EDT_DEST_NAME.pEdit->GetWindowText(strSearch);
	
	if(!CRcpDlg::MakeSearchQuery(strSearch, strKeyWord, &nSearchType)) return;
	 
	CMkCommand cmd(m_pMkDb, "search_customer_2011_10_like_insung");
	CMkRecordset rs(m_pMkDb);

	if(nSearchType == ST_COMPANY) 
		nSearchType++;

	cmd.AddParameter(typeLong, typeInput, sizeof(long), (long)nSearchType);
	cmd.AddParameter(typeLong, typeInput, sizeof(long), m_pBi->nCustomerTable);
	cmd.AddParameter(typeString, typeInput, strKeyWord.GetLength(), strKeyWord);
	cmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);
	cmd.AddParameter(typeBool, typeInput, sizeof(BOOL), 0);

	if(!rs.Execute(&cmd)) return;

	long nRecordCount = rs.GetRecordCount();

	pPlace->Clear();

	BOOL bSelectCustomer = FALSE;

	if(nRecordCount == 0)
	{
		if(nType == PLACE_ORDER)
			m_pOrder->SetPhone(strSearch);
		else
			pPlace->SetCompany(strSearch);

		bSelectCustomer = TRUE;
	}
	else if(nRecordCount == 1)
	{
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		COleDateTime dtPRDate;
		CCustomerDlg::GetPcInfo(&rs, pc, dtPRDate, TRUE);
		pPlace->SearchCustomerCNo(pc->nCNo, TRUE, TRUE, pc->nTelID, FALSE);
		bSelectCustomer = TRUE;
	}
	else
	{
		CSearchCustomerInsungDlg dlg;
		dlg.m_pRs = &rs;

		if(dlg.DoModal() == IDOK)			
		{
			pPlace->SearchCustomerCNo(dlg.m_nCNo, TRUE, TRUE, dlg.m_nTelID, FALSE);
			bSelectCustomer = TRUE;
		}
		
	}

	if(bSelectCustomer)
	{
		if(nType == PLACE_ORDER)
		{
			LF->MoveFocus(m_EDT_START_NAME.pEdit);
			FIllOrderCombo();
		}
		else if(nType == PLACE_START)
			LF->MoveFocus(nRecordCount == 0 ? m_EDT_START_DONG.pEdit : m_EDT_DEST_NAME.pEdit);
		else if(nType == PLACE_DEST)
			LF->MoveFocus(nRecordCount == 0 ? m_EDT_DEST_DONG.pEdit : m_EDT_ETC.pEdit);
	}
	else
	{
		if(nType == PLACE_START)
			LF->MoveFocus(m_EDT_DEST_NAME.pEdit);
		else if(nType == PLACE_DEST)
			LF->MoveFocus(m_EDT_ETC.pEdit);
	}

	ChangeRcpState();
	GetSectionCharge();
}

void CRcpInsungDlg::DeleteOphoneCombo()
{
	for(int i=0; i<m_cmbOrderPhone.GetCount(); i++)
	{
		ST_PHONE_INFO *st = (ST_PHONE_INFO*)m_cmbOrderPhone.GetItemData(i);

		delete st;
		st = NULL;
	}

	m_cmbOrderPhone.ResetContent();
}

void CRcpInsungDlg::FIllOrderCombo()
{
	DeleteOphoneCombo();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_tel_info");
	cmd.AddParameter(m_pOrder->GetCNo());

	if(!rs.Execute(&cmd))
		return;
	
	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_PHONE_INFO *st = new ST_PHONE_INFO;

		rs.GetFieldValue("nID", st->nTelID);
		rs.GetFieldValue("sTel", st->strTel);
		rs.GetFieldValue("sTelDepart", st->strDepart);
		rs.GetFieldValue("sTelManager", st->strManager);
	
		m_cmbOrderPhone.InsertString(i, GetOrderPhoneString(st));
		m_cmbOrderPhone.SetItemData(i, (DWORD)st);

		rs.MoveNext();
	}

	m_cmbOrderPhone.SetWindowText(LF->GetStringFromEdit(m_EDT_ORDER_PHONE.pEdit));
}

CString CRcpInsungDlg::GetOrderPhoneString(ST_PHONE_INFO *st)
{
	CString strTemp = "";
	CString strDashPhone = LF->GetDashPhoneNumber(st->strTel);
	CString strCustomer = st->strDepart + "/" + st->strManager; 

	strTemp = strDashPhone;

	for(int i=strDashPhone.GetLength(); i<20; i++)
		strTemp += " ";	

	strTemp += strCustomer;

	return strTemp;
}

void CRcpInsungDlg::OnEnSetfocusStartEdit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnBnClickedOrderCustomerDlgBtn()
{
	OpenInsungCustomerDlg(PLACE_ORDER);
}

void CRcpInsungDlg::OpenInsungCustomerDlg(long nPlaceType)
{
	m_pPlaceCustomer = NULL;
	
	if(nPlaceType == PLACE_ORDER) m_pPlaceCustomer = m_pOrder;
	if(nPlaceType == PLACE_START) m_pPlaceCustomer = m_pStart;
	if(nPlaceType == PLACE_DEST) m_pPlaceCustomer = m_pDest;

	if(m_pPlaceCustomer == NULL)
		return;

	if(m_pInsungCustomerDlg != NULL)
	{
		delete m_pInsungCustomerDlg;
		m_pInsungCustomerDlg = NULL;
	}

	m_pInsungCustomerDlg = new CInsungCustomerDlg(this);
	m_pInsungCustomerDlg->m_nCNo = m_pPlaceCustomer->GetCNo();
	m_pInsungCustomerDlg->m_nTelID = m_pPlaceCustomer->GetTelID();
	m_pInsungCustomerDlg->m_nCompany = m_pBi->nCustomerTable;
	m_pInsungCustomerDlg->Create(CInsungCustomerDlg::IDD, this);
	m_pInsungCustomerDlg->ShowWindow(TRUE);


	/*
	CInsungCustomerDlg dlg;
	dlg.m_nCNo = pPlace->GetCNo();
	dlg.m_nTelID = pPlace->GetTelID();
	dlg.m_nCompany = m_pBi->nCustomerTable;

	if(dlg.DoModal() == IDOK)
	{
		pPlace->SearchCustomerCNo(dlg.m_nCNo, TRUE, TRUE, dlg.m_nTelID, FALSE);
	}
	*/
}

void CRcpInsungDlg::ShowCustomerInnerMemo(CString strMemo)
{
	m_cmbCustomerMemo.ResetContent();
	m_cmbCustomerMemo.SetWindowText(strMemo);
	m_cmbCustomerMemo.AddString(strMemo);
}

void CRcpInsungDlg::SearchPoi(long nType)
{
	CString strSearch;

	CRcpPlaceInfo* pPlace = GetPlaceInfo(nType);

	nType == PLACE_START ? m_EDT_START.pEdit->GetWindowText(strSearch) : m_EDT_DEST.pEdit->GetWindowText(strSearch);
	
	CSearchDongInsungDlg dlg;
	dlg.m_nCustomerTable = m_pBi->nCustomerTable;
	dlg.m_strSearch = strSearch;

	if(dlg.DoModal() != IDOK)
		return;

	if(dlg.m_nOkType == 0) //동선택
	{  
		InsertDongInfo(pPlace, dlg.m_nDongID);
	}
	else if(dlg.m_nOkType == 1) //고객선택
	{
		pPlace->SearchCustomerCNo(dlg.m_nCNo, TRUE, TRUE, dlg.m_nTelID);
	}
	else if(dlg.m_nOkType == 2)//웹선택
	{
		pPlace->Clear();
 
		CString str = dlg.m_pDetailPOI->GetRegionName() + " " + dlg.m_strAddress;
		str = str.Trim();

		//pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(dlg.m_pDetailPOI), dlg.m_pDetailPOI-);
		pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(str), str);
		pPlace->SetPOI(dlg.m_pDetailPOI->GetDongPOI(FALSE));
		pPlace->SetDetailPos(dlg.m_pDetailPOI->m_nPosX, dlg.m_pDetailPOI->m_nPosY); 
		pPlace->SetDetail(str);
		pPlace->SetPhone(dlg.m_pDetailPOI->GetPhoneNumber());
		pPlace->SetCompany(dlg.m_pDetailPOI->GetPlaceName());
		pPlace->SetDisplayDong(dlg.m_pDetailPOI->GetDong());	
	}

	if(nType == PLACE_START)
		m_EDT_DEST.pEdit->SetFocus();
	else
		m_EDT_ETC.pEdit->SetFocus();

	GetSectionCharge();

}
void CRcpInsungDlg::OnBnClickedEtcAddBtn()
{
	OnMenuContextEtc(ID_MENU_ETC_USER_UPDATE);
	InitEtcCombo();	
}

void CRcpInsungDlg::OnCbnSelchangeEtcCombo()
{
	long nItemIndex = m_cmbEtc.GetCurSel();
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();

	CString strItem = "";

	if(nItemIndex == 0)
		strItem.Format("[독촉%s]", dtCurrent.Format("%H:%M"));
	if(nItemIndex == 1)
		strItem.Format("[리콜%s]", dtCurrent.Format("%H:%M"));

	m_cmbEtc.GetLBText(nItemIndex, strItem);

	m_EDT_ETC.pEdit->SetWindowText(strItem);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

long CRcpInsungDlg::GetTypeControlCount(long nType)
{
	if(nType == TYPE_PAY) return PAY_TYPE_CONTROL_COUNT;
	if(nType == TYPE_CAR) return CAR_TYPE_CONTROL_COUNT;
	if(nType == TYPE_WAY) return WAY_TYPE_CONTROL_COUNT;
	if(nType == TYPE_RUN) return RUN_TYPE_CONTROL_COUNT;

	return -1;
}

long* CRcpInsungDlg::GetTypeControlItem(long nType)
{
	if(nType == TYPE_PAY) return _paytype;
	if(nType == TYPE_CAR) return _cartype;
	if(nType == TYPE_WAY) return _waytype;
	if(nType == TYPE_RUN) return _runtype;

	return NULL;
}

long CRcpInsungDlg::GetTypeControl(long nType, long nSubType)
{
	if(nType == TYPE_PAY)
	{
		if(nSubType == PAY_PRE) return IDC_PAY_TYPE_0_RADIO;
		if(nSubType == PAY_AFTER) return IDC_PAY_TYPE_1_RADIO;
		if(nSubType == PAY_CREDIT) return IDC_PAY_TYPE_2_RADIO;
		if(nSubType == PAY_ONLINE) return IDC_PAY_TYPE_3_RADIO;
		if(nSubType == PAY_DIRECT) return IDC_PAY_TYPE_4_RADIO;
		if(nSubType == PAY_CARD) return IDC_PAY_TYPE_7_RADIO;

	}
	else if(nType == TYPE_CAR)
	{
		if(nSubType == CAR_AUTO) return IDC_CAR_TYPE_0_RADIO;
		if(nSubType == CAR_DAMA) return IDC_CAR_TYPE_2_RADIO;
		if(nSubType == CAR_LABO) return IDC_CAR_TYPE_3_RADIO;
		if(nSubType == CAR_VAN) return IDC_CAR_TYPE_4_RADIO;
		if(nSubType == CAR_TRUCK) return IDC_CAR_TYPE_5_RADIO;
		if(nSubType == CAR_SUBWAY) return IDC_CAR_TYPE_6_RADIO;
		if(nSubType == CAR_1_4_TON) return IDC_CAR_TYPE_9_RADIO;
	}
	else if(nType == TYPE_WAY)
	{
		if(nSubType == WAY_ONE) return IDC_WAY_TYPE_0_RADIO;
		if(nSubType == WAY_TWO) return IDC_WAY_TYPE_1_RADIO;
		if(nSubType == WAY_SEVERAL) return IDC_WAY_TYPE_2_RADIO;
	}
	else if(nType == TYPE_RUN)
	{
		if(nSubType == WAY_ONE) return IDC_RUN_TYPE_0_RADIO;
		if(nSubType == RUN_SLOW) return IDC_RUN_TYPE_1_RADIO;
		if(nSubType == RUN_FAST) return IDC_RUN_TYPE_2_RADIO;
		if(nSubType == RUN_VERY_FAST) return IDC_RUN_TYPE_3_RADIO;
	}

	return -1;
}

void CRcpInsungDlg::SetCheckOptionControl(long nType, long nSubType)
{
	if(nType == TYPE_CAR)
	{
		SetCheckOptionControlCarType(nSubType);
		return;
	}

	long nControl = GetTypeControl(nType, nSubType);
	long nMaxCount = GetTypeControlCount(nType);
	long *pControl = GetTypeControlItem(nType);

	for(int i=0; i<nMaxCount; i++)
	{
		if(nControl == pControl[i])
			((CButton*)GetDlgItem(pControl[i]))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(pControl[i]))->SetCheck(FALSE);
	}

	if(nType == TYPE_PAY)
	{
		if(GetPayTypeNew() == PAY_CARD)
			m_btnNiceCard.ShowWindow(TRUE);
		else
			m_btnNiceCard.ShowWindow(FALSE);	
	}
}

void CRcpInsungDlg::SetCheckOptionControlCarType(long nCarType)
{
	enum {CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK, CAR_SUBWAY, CAR_PS, CAR_6VAN, 
		CAR_1_4_TON, CAR_2_5_TON,CAR_3_5_TON, CAR_5_TON, CAR_11_TON, CAR_18_TON, CAR_25_TON}; //CAR_PARCEL_SERVICE

	long nTempCarType = nCarType;
	BOOL bTruck = nCarType == CAR_TRUCK ||
		nCarType == CAR_1_4_TON ||
		nCarType == CAR_2_5_TON ||
		nCarType == CAR_3_5_TON ||
		nCarType == CAR_5_TON ||
		nCarType == CAR_11_TON ||
		nCarType == CAR_18_TON ||
		nCarType == CAR_25_TON;

	if(bTruck)
		nTempCarType = CAR_TRUCK;

	long nControl = GetTypeControl(TYPE_CAR, nTempCarType);

	int nSize = sizeof(_cartype);

	for(int i=0; i<nSize/sizeof(long); i++)
	{
		if(nControl == _cartype[i])
			((CButton*)GetDlgItem(_cartype[i]))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(_cartype[i]))->SetCheck(FALSE);
	}

	if(bTruck)
	{
		for(int i=0; i<m_cmbTruckType.GetCount(); i++)
		{
			if(m_cmbTruckType.GetItemData(i) == nCarType)
				m_cmbTruckType.SetCurSel(i);
		}		
	}
	else
	{
		m_cmbTruckType.SetCurSel(0);		
	}
}

void CRcpInsungDlg::SetPayTypeNew(long nPayType)
{
	SetCheckOptionControl(TYPE_PAY, nPayType);
}

void CRcpInsungDlg::SetCarTypeNew(long nCarType)
{
	SetCheckOptionControl(TYPE_CAR, nCarType);
}

void CRcpInsungDlg::SetWayTypeNew(long nWayType)
{
	SetCheckOptionControl(TYPE_WAY, nWayType);
}

void CRcpInsungDlg::SetRunTypeNew(long nRunType)
{
	SetCheckOptionControl(TYPE_RUN, nRunType);
}

long CRcpInsungDlg::GetCarTypeNew()
{
	if(m_rdoCarType0.GetCheck()) return CAR_AUTO;
	if(m_rdoCarType2.GetCheck()) return CAR_DAMA;
	if(m_rdoCarType3.GetCheck()) return CAR_LABO;
	if(m_rdoCarType4.GetCheck()) return CAR_VAN;
	if(m_rdoCarType6.GetCheck()) return CAR_SUBWAY;
	if(m_rdoCarType9.GetCheck()) return CAR_1_4_TON;

	if(m_rdoCarType5.GetCheck())
	{
		long nCarType = m_cmbTruckType.GetItemData(m_cmbTruckType.GetCurSel());
		return nCarType;
	}

	return CAR_AUTO;
}

long CRcpInsungDlg::GetPayTypeNew()
{
	if(m_rdoPayType0.GetCheck()) return PAY_PRE;
	if(m_rdoPayType1.GetCheck()) return PAY_AFTER;
	if(m_rdoPayType2.GetCheck()) return PAY_CREDIT;
	if(m_rdoPayType3.GetCheck()) return PAY_ONLINE;
	if(m_rdoPayType4.GetCheck()) return PAY_DIRECT;
	if(m_rdoPayType7.GetCheck()) return PAY_CARD;

	return CAR_AUTO;
}

long CRcpInsungDlg::GetWayTypeNew()
{
	if(m_rdoWayType0.GetCheck()) return WAY_ONE;
	if(m_rdoWayType1.GetCheck()) return WAY_TWO;
	if(m_rdoWayType2.GetCheck()) return WAY_SEVERAL;

	return WAY_ONE;
}

long CRcpInsungDlg::GetRunTypeNew()
{
	if(m_rdoRunType0.GetCheck()) return RUN_NORMAL;
	if(m_rdoRunType1.GetCheck()) return RUN_SLOW;
	if(m_rdoRunType2.GetCheck()) return RUN_FAST;
	if(m_rdoRunType4.GetCheck()) return RUN_VERY_FAST;

	return RUN_NORMAL;
}

void CRcpInsungDlg::OnBnClickedSearchRiderBtn()
{
	AllocRiderInfo();
}

BOOL CRcpInsungDlg::IsReserve()
{
	return m_chkReserve.GetCheck();
}

BOOL CRcpInsungDlg::ReserveCheck()
{

	CString strReleaseMin;
	m_edtReleaseMin.GetWindowText(strReleaseMin);
	
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	COleDateTimeSpan dtSpan(0, 0, GetReleaseMin(), 0);

	if(dtCurrent > GetReserveTime() - dtSpan) 
	{
		if(MessageBox("이전시간으로 예약 하실수 없습니다.", "확인", MB_OKCANCEL) == IDOK)
			return FALSE;
	}
	
	return TRUE;
}

long CRcpInsungDlg::GetReleaseStateDB()
{
	return 1;
}

COleDateTime CRcpInsungDlg::GetReserveTime()
{
	COleDateTime dtDate, dtTime;
	m_dtpReserveData.GetTime(dtDate);
	m_dtpReserveTime.GetTime(dtTime);

	COleDateTime dt(COleDateTime::GetCurrentTime());
	if(m_chkReserve.GetCheck() )
		dt.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 
		dtTime.GetHour(), dtTime.GetMinute(), 0);
	return dt;
}

long CRcpInsungDlg::GetReleaseMin()
{
	CString strReleaseMin;
	m_edtReleaseMin.GetWindowText(strReleaseMin);

	return atol(strReleaseMin);
}

void CRcpInsungDlg::SetReserveState(COleDateTime dtReserve, long nReserveAfter, long nReserveReleaseMin)
{
	m_chkReserve.SetCheck(TRUE);
	m_dtpReserveData.SetTime(dtReserve);
	m_dtpReserveTime.SetTime(dtReserve);

	m_edtReleaseMin.SetWindowText(LF->GetStringFromLong(nReserveReleaseMin, FALSE));
}

void CRcpInsungDlg::InitReserveState()
{
	m_chkReserve.SetCheck(FALSE);
	m_dtpReserveData.SetTime(COleDateTime::GetCurrentTime());
	m_dtpReserveTime.SetTime(COleDateTime::GetCurrentTime());

	m_edtReleaseMin.SetWindowText("");
}

CBrush* CRcpInsungDlg::GetOrderBrush()
{
	if(m_nState == STATE_RESERVED)
		return &m_brRed;
	else if(m_nState == STATE_OK)
		return &m_brPink;
	else if(m_nState == STATE_OK_ONLY_MAN)
		return &m_brOrange;
	else if(m_nState == STATE_ALLOCATED || m_nState == STATE_PICKUP)
		return &m_btGreen;
	else if(m_nState == STATE_FINISH)
		return &m_brWhite;
	else if(m_nState == STATE_CANCELED)
		return &m_brBlue;

	return &m_brYellow;
}

HBRUSH CRcpInsungDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_TNO_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_TNO_STATIC || 
		pWnd->GetDlgCtrlID() == IDC_STATE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_STATE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_WNAME_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_WNAME_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RCP_TIME_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_nInitItem > 0 ? *GetOrderBrush() : m_brPink;
	}

	if(pWnd->GetDlgCtrlID() == IDC_RCP_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_BRANCH_RIGHT_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ORDER_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ORDER_DEPART_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ORDER_MANAGER_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ORDER_PHONE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_START_ADDRESS_IS_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_DEST_ADDRESS_IS_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_DISTANCE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_DISTANCE_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brWhite;
	}

	if(pWnd->GetDlgCtrlID() == IDC_START_EDIT ||
		pWnd->GetDlgCtrlID() == IDC_START_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHANGE_START_DEST_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_btGreen;
	}

	if(pWnd->GetDlgCtrlID() == IDC_DEST_EDIT ||
		pWnd->GetDlgCtrlID() == IDC_DEST_STATIC)
	{ 
		pDC->SetBkMode(TRANSPARENT);
		return m_btGreen2;
	}

	if(pWnd->GetDlgCtrlID() == IDC_SMS_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ETC_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_GROUP_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ITEM_TYPE_COMBO_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_PAY_TYPE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CAR_TYPE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_WAY_TYPE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_BASIC_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_DIS_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_SUM_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_ALLOC_DISTANCE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CARD_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RESERVE_RELEASE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_TYPE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RUN_TYPE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_ADD_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_TRANS_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_CHARGE_DRIVING_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_NO_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_COMPANY_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_PHONE_TITLE_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_KM_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_INFO_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_COMPANY_STATIC ||
		pWnd->GetDlgCtrlID() == IDC_RIDER_PHONE_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brWhite;
	} 

	if(pWnd->GetDlgCtrlID() == IDC_HELP_STATIC)
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 255));
		//pDC->SetBkColor(GetSysColor(COLOR_BACKGROUND));
		return m_brSystem;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	return hbr;
}



void CRcpInsungDlg::RepositionLeftControls()
{  
	MoveSameLine(m_EDT_TNO.pEdit, &m_stcTNoTitle, NULL); 
	MoveSameLine(&m_stcStateTitle, m_EDT_TNO.pEdit, NULL);
	MoveSameLine(m_EDT_STATE.pEdit, &m_stcStateTitle, NULL);

	MoveSameLine(&m_stcWNameTitle, NULL, &m_stcTNoTitle);
	MoveSameLine(m_EDT_WNAME.pEdit, &m_stcWNameTitle, NULL); 
	MoveSameLine(&m_stcRcpTime, m_EDT_WNAME.pEdit, NULL, 1);

	MoveSameLine(&m_stcRcpTitle, NULL, &m_stcWNameTitle);
	MoveSameLine(m_CMB_BRANCH.pCombo, &m_stcRcpTitle, NULL); 
	MoveSameLine(&m_stcBranchRight, m_CMB_BRANCH.pCombo, NULL, 1);

	MoveSameLine(&m_stcOrder, NULL, &m_stcRcpTitle);
	MoveSameLine(m_EDT_ORDER_NAME.pEdit, &m_stcOrder, NULL); 
	MoveSameLine(m_EDT_ORDER_PHONE.pEdit, m_EDT_ORDER_NAME.pEdit, NULL, 2);
	MoveSameLine(&m_cmbOrderPhone, m_EDT_ORDER_NAME.pEdit, NULL); 

	MoveSameLine(m_EDT_ORDER_DEPART.pEdit, &m_stcOrder, m_EDT_ORDER_NAME.pEdit);
	MoveSameLine(m_EDT_ORDER_MANAGER.pEdit, m_EDT_ORDER_DEPART.pEdit, m_EDT_ORDER_NAME.pEdit, 2, -1);
	//MoveSameLine(m_EDT_ORDER_MANAGER.pEdit, m_EDT_ORDER_DEPART.pEdit, NULL, 1);

	MoveSameLine(m_EDT_START.pEdit, NULL, &m_stcOrder, 0, 0, 0, 1); 
	MoveSameLine(m_EDT_START_NAME.pEdit, m_EDT_START.pEdit, &m_stcOrder, 0, 0, 0, 1);
	MoveSameLine(&m_btnStartMap, m_EDT_START_NAME.pEdit, &m_stcOrder, 1, 0, 0, 1);
 
	MoveSameLine(&m_stcStart, NULL, m_EDT_START.pEdit); 	
	MoveSameLine(m_EDT_START_DEPART.pEdit, &m_stcStart, NULL);
	MoveSameLine(m_EDT_START_MANAGER.pEdit, m_EDT_START_DEPART.pEdit, NULL, 1);

 	MoveSameLine(m_EDT_START_PHONE.pEdit, &m_stcStart, m_EDT_START_DEPART.pEdit); 
	MoveSameLine(m_EDT_START_DONG.pEdit, m_EDT_START_PHONE.pEdit, NULL, 1); 

	MoveSameLine(&m_STC_START_ADDERSS.stcFlat, NULL, m_EDT_START_PHONE.pEdit);
	MoveSameLine(&m_btnStartAddress, &m_STC_START_ADDERSS.stcFlat, NULL, 1); 

	MoveSameLine(m_EDT_START_DETAIL.pEdit, NULL, &m_STC_START_ADDERSS.stcFlat); 
	MoveSameLine(&m_btnStartClear, NULL, &m_STC_START_ADDERSS.stcFlat, 0, -4, 0, 4);
  
 
	MoveSameLine(m_EDT_DEST.pEdit, NULL, m_EDT_START_DETAIL.pEdit, 0, 0, 0, 1);
	MoveSameLine(m_EDT_DEST_NAME.pEdit, m_EDT_DEST.pEdit, m_EDT_START_DETAIL.pEdit, 0, 0, 0, 1);
	MoveSameLine(&m_btnDestMap, m_EDT_DEST_NAME.pEdit, m_EDT_START_DETAIL.pEdit, 1, 0, 0, 1);
 
	MoveSameLine(&m_btnDestToOName, NULL, m_EDT_DEST.pEdit); 
	MoveSameLine(m_EDT_DEST_DEPART.pEdit, &m_btnDestToOName, NULL);
	MoveSameLine(m_EDT_DEST_MANAGER.pEdit, m_EDT_DEST_DEPART.pEdit, NULL, 1);

	MoveSameLine(&m_stcDest, NULL, m_EDT_DEST_DEPART.pEdit);
	MoveSameLine(m_EDT_DEST_PHONE.pEdit, &m_stcDest, m_EDT_DEST_DEPART.pEdit);
	MoveSameLine(m_EDT_DEST_DONG.pEdit, m_EDT_DEST_PHONE.pEdit, NULL, 1);

	MoveSameLine(&m_STC_DEST_ADDERSS.stcFlat, NULL, m_EDT_DEST_PHONE.pEdit);
	MoveSameLine(&m_btnDestAddress, &m_STC_DEST_ADDERSS.stcFlat, NULL, 1);

	MoveSameLine(m_EDT_DEST_DETAIL.pEdit, NULL, &m_STC_DEST_ADDERSS.stcFlat);
	MoveSameLine(&m_btnDestClear, NULL, &m_STC_DEST_ADDERSS.stcFlat, 0, -4, 0, 4);

	MoveSameLine(&m_stcDistanceTitle, NULL, m_EDT_DEST_DETAIL.pEdit, 0, -1);
	MoveSameLine(&m_stcDistance, &m_stcDistanceTitle, NULL);
	MoveSameLine(&m_chkUseCharge, &m_stcDistance, NULL); 
	MoveSameLine(&m_chkGI, &m_chkUseCharge, NULL);
	MoveSameLine(&m_btnChargeStat, &m_chkGI, NULL, 1);
}

void CRcpInsungDlg::RepositionRightControls()
{				    
	MoveSameLine(&m_dtpReserveData, &m_chkReserve, NULL, 1, 0, -1);
	MoveSameLine(&m_dtpReserveTime, &m_dtpReserveData, NULL, 1, 0, -1); 
	MoveSameLine(&m_edtReleaseMin, &m_dtpReserveTime, NULL, 1, 0, -1);
	MoveSameLine(&m_stcReserveRelease, &m_edtReleaseMin, NULL, 1, 0, -1); 
 
	MoveSameLine(&m_stcSMSTitle, NULL, &m_chkReserve);
	MoveSameLine(&m_cmbSMS, &m_stcSMSTitle, NULL);
	MoveSameLine(m_BTN_NOT_SEND_COMPLETE_SMS.pButton, &m_cmbSMS, NULL);

	MoveSameLine(&m_stcEtc, NULL, &m_stcSMSTitle);
	MoveSameLine(m_EDT_ETC.pEdit, &m_stcEtc, NULL, 0);  
	MoveSameLine(&m_cmbEtc, NULL, &m_stcEtc);  
	MoveSameLine(&m_btnEtcAdd, NULL, &m_cmbEtc, 0, 1);
	MoveSameLine(&m_btnEtcDelete, &m_btnEtcAdd, NULL, 0, 1);          
     
	//MoveSameLine(&m_stcRiderGroup, NULL, &m_btnEtcAdd, 0, 0, 0, 0);  
	MoveSameLine(&m_stcRiderGroup, NULL, m_EDT_ETC.pEdit, 0, 0, 0, 0); 
	MoveSameLine(m_CMB_ALLOC_GROUP.pCombo, &m_stcRiderGroup, NULL, 0, 0, 0, 0);      
	MoveSameLine(&m_chkClientShareOrder, m_CMB_ALLOC_GROUP.pCombo, NULL);
	MoveSameLine(&m_chkCargoShare, &m_chkClientShareOrder, NULL, 1, 0, -1);
	//MoveSameLine(&m_chkCargoShare, m_BTN_AUTO_SHARE_ORDER.pButton, NULL, 1, 0, -1);
	MoveSameLine(&m_chkNoFee, &m_chkCargoShare, NULL, 0, 0);

	MoveSameLine(&m_stcItemType, NULL, &m_stcRiderGroup);
	MoveSameLine(&m_cmbItemType, &m_stcItemType, NULL);
	MoveSameLine(&m_stcChargeType, &m_cmbItemType, NULL);
	MoveSameLine(m_CMB_CHARGE_TYPE.pCombo, &m_stcChargeType, NULL);

	MoveSameLine(&m_stcPayTypeTitle, NULL, &m_stcItemType);
	MoveSameLine(&m_rdoPayType0, &m_stcPayTypeTitle, NULL);
	MoveSameLine(&m_rdoPayType1, &m_rdoPayType0, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoPayType2, &m_rdoPayType1, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoPayType3, &m_rdoPayType2, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoPayType4, &m_rdoPayType3, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoPayType7, &m_rdoPayType4, NULL, 1, 0, -1);

	MoveSameLine(&m_stcCarTypeTitle, NULL, &m_stcPayTypeTitle);
	MoveSameLine(&m_rdoCarType0, &m_stcCarTypeTitle, NULL);
	MoveSameLine(&m_rdoCarType2, &m_rdoCarType0, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoCarType4, &m_rdoCarType2, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoCarType3, &m_rdoCarType4, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoCarType5, &m_rdoCarType3, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoCarType6, &m_rdoCarType5, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoCarType9, &m_rdoCarType6, NULL, 2, 0, -1); 
   
	MoveSameLine(&m_cmbTruckType, NULL, NULL, 0, 0, -1, 0); 

	MoveSameLine(&m_stcWayTypeTitle, NULL, &m_stcCarTypeTitle);
	MoveSameLine(&m_rdoWayType0, &m_stcWayTypeTitle, NULL);
	MoveSameLine(&m_rdoWayType1, &m_rdoWayType0, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoWayType2, &m_rdoWayType1, NULL, 1, 0, -1);
	MoveSameLine(&m_stcRunTypeTitle, &m_rdoWayType2, NULL);
	MoveSameLine(&m_rdoRunType0, &m_stcRunTypeTitle, NULL);
	MoveSameLine(&m_rdoRunType1, &m_rdoRunType0, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoRunType2, &m_rdoRunType1, NULL, 1, 0, -1);
	MoveSameLine(&m_rdoRunType4, &m_rdoRunType2, NULL, 2, 0, -1);

	MoveSameLine(&m_stcChargeBasic, NULL, &m_stcWayTypeTitle);
	MoveSameLine(m_EDT_CHARGE_BASIC.pEdit, &m_stcChargeBasic, NULL);
	MoveSameLine(&m_stcChargeAdd, m_EDT_CHARGE_BASIC.pEdit, NULL);
	MoveSameLine(m_EDT_CHARGE_ADD.pEdit, &m_stcChargeAdd, NULL, 1);

	MoveSameLine(&m_stcChargeDis, NULL, &m_stcChargeBasic, 0, -1, 0, 0);
	MoveSameLine(m_EDT_CHARGE_DIS.pEdit, &m_stcChargeDis, NULL, 0, -1, 0, 0);
	MoveSameLine(&m_stcChargeTrans, m_EDT_CHARGE_DIS.pEdit, NULL, 0, -1, 0, 0);
	MoveSameLine(m_EDT_CHARGE_TRANS.pEdit, &m_stcChargeTrans, NULL, 1, -1, 0, 0);

	MoveSameLine(&m_stcChargeSum, NULL, &m_stcChargeDis, 0, -1, 0, 0);
	MoveSameLine(m_EDT_CHARGE_SUM.pEdit, &m_stcChargeSum, NULL, 0, -1, 0, 0);
	MoveSameLine(&m_stcChargeDriving, m_EDT_CHARGE_SUM.pEdit, NULL, 0, -1, 0, 0);
	MoveSameLine(m_EDT_CHARGE_DRIVING.pEdit, &m_stcChargeDriving, NULL, 1, -1, 0, 0);

	MoveSameLine(&m_stcRider, NULL, &m_stcChargeSum, 0, -1, 0, 0);
	MoveSameLine(&m_stcRiderNoTitle, &m_stcRider, NULL, 0, -1, 0, 0);
	MoveSameLine(&m_edtRiderNo, &m_stcRiderNoTitle, NULL, 1, -1, 0, 0); 
	MoveSameLine(&m_stcRiderCompanyTitle, &m_stcRider, &m_stcRiderNoTitle, 0, -1, 0, 0);
	MoveSameLine(&m_edtRiderCompany, &m_stcRiderCompanyTitle, NULL, 1, -1, 0, 0);

	MoveSameLine(&m_stcRiderPhoneTitle, &m_stcRider, &m_stcRiderCompanyTitle, 0, -1, 0, 0);
	MoveSameLine(&m_edtRiderPhone, &m_stcRiderPhoneTitle, NULL, 1, -1, 0, 0);

	MoveSameLine(&m_stcAllocDistanceTitle, NULL, &m_stcRiderPhoneTitle, 0, -2);
	MoveSameLine(&m_edtAllocDistance, &m_stcAllocDistanceTitle, NULL, 0, -2);
	MoveSameLine(&m_stcKM, &m_edtAllocDistance, NULL, -1, -2, -1);
	MoveSameLine(&m_chkTrans, &m_stcKM, NULL, 0, -2); 
	MoveSameLine(&m_chkTaxSheet, &m_chkTrans, NULL, 1, -2);

	MoveSameLine(&m_stcCardTitle, NULL, &m_stcAllocDistanceTitle, 0, 1);
	MoveSameLine(&m_edtCardInfo, &m_stcCardTitle, NULL, 0, 1);
	MoveSameLine(&m_edtCardInfo2, &m_edtCardInfo, NULL, 1, 1);

	//MoveSameLine(&m_btnRiderInfo, &m_edt, NULL, 1, 1);
	//MoveSameLine(&m_btnRiderSmsSend, &m_edtCardInfo, NULL, 1, 1);

	//MoveSameLine(&m_stcRiderInfo, &m_stcRiderNoTitle, NULL, 1, 0, -1);
	//MoveSameLine(&m_stcRiderCompany, &m_stcRiderCompanyTitle, NULL, 1, 0, -1);
	//MoveSameLine(&m_stcRiderPhone, &m_stcRiderPhoneTitle, NULL, 1, 0, -1);
}

long CRcpInsungDlg::GetTodayCount()
{
	long nCount = 0;
	long nCNo = m_pOrder->GetCNo();

	OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	BOOL bUpdate = FALSE;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nCNo == nCNo)
		{
			nCount++;
		}
	}

	return nCount;
}

void CRcpInsungDlg::ChangeRcpState()
{
	if(m_pOrder->GetCNo() > 0)
	{
		m_stcCustsomerInfo.SetInfo(m_pOrder->GetCNo(), GetTodayCount(), m_pOrder->GetUseCount(), m_pOrder->GetCancelCount(), m_pOrder->GetMileageBalance());
		m_btnOrderCustomerDlg.SetWindowText("고객수정");
	}
	else
	{
		m_stcCustsomerInfo.SetInfo(0);
		m_btnOrderCustomerDlg.SetWindowText("고객등록");
	}
}

void CRcpInsungDlg::GetCRect(CWnd *pWnd, CRect &rcClient)
{
	pWnd->GetWindowRect(rcClient);
	ScreenToClient(rcClient);
}

void CRcpInsungDlg::MoveSameLine(CWnd *pWnd, CWnd *pNeighborX, CWnd *pNeighborY, int nAddCX, int nAddCY, int nOffsetX, int nOffsetY)
{ 
	CRect rc, rcNeighborX, rcNeighborY;
	GetCRect(pWnd, rc);

	if(pNeighborX)
	{
		GetCRect(pNeighborX, rcNeighborX);
		rc.left = rcNeighborX.right + 1;
	}

	if(pNeighborY)
	{
		GetCRect(pNeighborY, rcNeighborY);
		rc.top = rcNeighborY.bottom + 1;
	}
	else if(pNeighborX)
	{
		GetCRect(pNeighborX, rcNeighborY);
		rc.top = rcNeighborY.top;
	}

	rc.OffsetRect(nOffsetX, nOffsetY);
	pWnd->MoveWindow(rc.left, rc.top, rc.Width() + nAddCX, rc.Height() + nAddCY);
}

void CRcpInsungDlg::OnPaint()
{	
	CPaintDC dc(this); // device context for painting

	DrawLeftBox(&dc);
	DrawRightBox(&dc);
}


void CRcpInsungDlg::DrawLeftBox(CDC *pDC)
{
	CRect rcTNoTitle, rcChargeStat, rcState, rcBlackBox;
	GetCRect(&m_stcTNoTitle, rcTNoTitle);
	GetCRect(&m_btnChargeStat, rcChargeStat);
	GetCRect(m_EDT_STATE.pEdit, rcState);

	rcBlackBox.left = rcTNoTitle.left - 1;
	rcBlackBox.top = rcTNoTitle.top - 1;
	rcBlackBox.right = rcState.right + 1;
	rcBlackBox.bottom = rcChargeStat.bottom;

	pDC->FillSolidRect(rcBlackBox, RGB(0, 0, 0));

	CRect rcStartStatic, rcStartDetailEdit, rcGreenBox, rcBtnBox;
	GetCRect(&m_stcStart, rcStartStatic);
	GetCRect(m_EDT_START_DETAIL.pEdit, rcStartDetailEdit);

	rcGreenBox.left = rcStartStatic.left;
	rcGreenBox.top = rcStartStatic.top;
	rcGreenBox.right = rcStartStatic.right;
	rcGreenBox.bottom = rcStartDetailEdit.top - 1;
	pDC->FillSolidRect(rcGreenBox, crGreen);

	rcBtnBox.left = rcStartDetailEdit.right + 1;
	rcBtnBox.right = rcState.right;
	rcBtnBox.top = rcStartDetailEdit.top;
	rcBtnBox.bottom = rcStartDetailEdit.bottom;
	pDC->FillSolidRect(rcBtnBox, GetSysColor(COLOR_BTNFACE));


	CRect rcDestStatic, rcDestDetailEdit, rcGreenBox2;
	GetCRect(&m_stcDest, rcDestStatic);
	GetCRect(m_EDT_DEST_DETAIL.pEdit, rcDestDetailEdit);

	rcGreenBox2.left = rcDestStatic.left;
	rcGreenBox2.top = rcDestStatic.top;
	rcGreenBox2.right = rcDestStatic.right;
	rcGreenBox2.bottom = rcDestDetailEdit.top - 1;
	pDC->FillSolidRect(rcGreenBox2, crGreen2);

	rcBtnBox.left = rcDestDetailEdit.right + 1;
	rcBtnBox.right = rcState.right;
	rcBtnBox.top = rcDestDetailEdit.top;
	rcBtnBox.bottom = rcDestDetailEdit.bottom;
	pDC->FillSolidRect(rcBtnBox, GetSysColor(COLOR_BTNFACE));
}

void CRcpInsungDlg::DrawRightBox(CDC *pDC)
{
	CRect rcReserve, rcReserveRelease, rcCardInfo2, rcBlackBox;
	GetCRect(&m_chkReserve, rcReserve);
	GetCRect(&m_stcReserveRelease, rcReserveRelease);
	GetCRect(&m_btnChargeStat, rcCardInfo2);

	rcBlackBox.left = rcReserve.left - 1;
	rcBlackBox.top = rcReserve.top - 1;
	rcBlackBox.right = rcReserveRelease.right + 1;
	rcBlackBox.bottom = rcCardInfo2.bottom;

	pDC->FillSolidRect(rcBlackBox, RGB(0, 0, 0));

}
void CRcpInsungDlg::OnStnClickedStartAddressStatic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnStnClickedDestAddressStatic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CRcpInsungDlg::ShowUsageHistory(BOOL bRefresh, BOOL bRcpDlgForceSizing)
{
	//if(m_pOrder->GetCNo() < 1)
	//	return;

	if(m_pHistoryInsung == NULL) 
	{
		//UINT nResourceID = m_bHistoryMoveDown ? IDD_HISTORY_CHILD_DLG : IDD_HISTORY_DLG;
		UINT nResourceID = m_bHistoryMoveDown ? IDD_HISTORY_INSUNG_CHILD_DLG : IDD_HISTORY_INSUNG_DLG;

		m_pHistoryInsung = new ChistoryInsungDlg(nResourceID, this);
		m_pHistoryInsung->m_pRcpInsungDlg = this;
		//m_pHistoryInsung->m_nOGNo = m_pOrder->GetGNo(); 
		//m_pHistoryInsung->m_nOCNo = m_pOrder->GetCNo(); 
		//m_pHistoryInsung->m_nCompany = m_pBi->nCustomerTable;
		m_pHistoryInsung->Create(nResourceID, this);

		ChangeRcpDlgSize(!m_bHistoryMoveDown, bRcpDlgForceSizing);

		if(m_bHistoryMoveDown)
		{
			//m_pHistoryInsung->SetParent(this);
			CRect rcHistory, rcClose, rcDlg;
			GetClientRect(rcDlg);
			m_btnChargeStat.GetWindowRect(rcClose);
			ScreenToClient(rcClose);

			rcHistory.top = rcClose.bottom + 5; 
			rcHistory.bottom = rcDlg.bottom - 5;
			rcHistory.left = rcDlg.left + 5; 
			rcHistory.right = rcDlg.right - 5;
			m_pHistoryInsung->MoveWindow(rcHistory);
		}
		else
		{
			CRect rcDlg, rcHistory, rcNew, rcClose;
			GetWindowRect(rcDlg);
			m_pHistoryInsung->GetWindowRect(rcHistory);

			long nHeight = rcHistory.Height();
			long nWeight = rcHistory.Width();

			rcHistory.top = rcDlg.top + 200;
			rcHistory.bottom = rcHistory.top + nHeight;
			rcHistory.right = rcDlg.left - 2;
			rcHistory.left = rcHistory.right - nWeight;
			m_pHistoryInsung->MoveWindow(rcHistory);
		}
	}
	else
	{
		ChangeRcpDlgSize(!m_bHistoryMoveDown, bRcpDlgForceSizing);

		//m_pHistoryInsung->m_nOGNo = m_pOrder->GetGNo(); //m_pOrder->GetGNo();
		//m_pHistoryInsung->m_nOCNo = m_pOrder->GetCNo(); //m_pOrder->GetCNo();
		//m_pHistoryInsung->m_nCompany = m_pBi->nCustomerTable;

		if(bRefresh)
		{
			//m_pHistoryInsung->Clear();
			m_pHistoryInsung->RefreshList();
		}
	}

	m_pHistoryInsung->ShowWindow(SW_SHOW);
}


void CRcpInsungDlg::ChangeRcpDlgSize(BOOL bOriginal, BOOL bForceChange)
{
	if(bOriginal)
	{
		CRect rcDlg, rcNew, rcClose;
		GetWindowRect(rcDlg);
		m_btnChargeStat.GetWindowRect(rcClose);

		if(rcDlg.bottom - rcClose.bottom > 20 || bForceChange)
		{
			rcDlg.bottom = rcClose.bottom + 10;
			MoveWindow(rcDlg);

			if(m_pHistoryInsung)
				m_pHistoryInsung->ShowWindow(SW_HIDE);	
		}
	}
	else if(m_pHistoryInsung)
	{
		long nHeight = AfxGetApp()->GetProfileInt("HistoryDlg", "Height", 200);

		CRect rcHistory, rcClose, rcDlg;
		GetWindowRect(rcDlg);
		m_btnChargeStat.GetWindowRect(rcClose);

		if(rcDlg.bottom - rcClose.bottom < 20 || bForceChange)
		{
			rcDlg.bottom = rcClose.bottom + nHeight;

			CRect rcScreen;

			if(LF->GetHandleScreenSize(this, rcScreen))
			{
				if(rcScreen.bottom < rcDlg.bottom + 30 &&
					rcScreen.Height() > rcDlg.Height())
				{
					int nTop = (rcScreen.Height() - rcDlg.Height()) / 2;
					rcDlg.OffsetRect(0, nTop - rcDlg.top);
				}
			}

			MoveWindow(rcDlg);
			m_pHistoryInsung->ShowWindow(SW_SHOW);	
		}
	}
}

void CRcpInsungDlg::InsertDongInfo(CRcpPlaceInfo *pPlace, long nDongID)
{	
	CPOIUnit *pPoi = m_poiNew.GetPOI(nDongID);
	pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(pPoi), pPoi->GetRegionName());
	pPlace->SetPOI(pPoi->GetDongPOI(FALSE));
	pPlace->SetDetailPos(0, 0); 
	pPlace->SetDisplayDong(pPoi->GetPOIName());
	//pPlace->SetDisplayDong(pPoi->GetDong());

}

void CRcpInsungDlg::SearchDong(long nType)
{
	CSearchDongInsungJibunDlg dlg;

	CRcpPlaceInfo* pPlace = GetPlaceInfo(nType);

	nType == PLACE_START ? m_EDT_START_DONG.pEdit->GetWindowText(dlg.m_strSearch) : 
						m_EDT_DEST_DONG.pEdit->GetWindowText(dlg.m_strSearch);

	if(dlg.m_strSearch.IsEmpty())
	{
		nType == PLACE_START ? m_EDT_DEST_NAME.pEdit->SetFocus() :
			m_EDT_DEST_DETAIL.pEdit->SetFocus();
	}

	BOOL bMapFocus = FALSE;

	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nDongID == 0)
			return;

		if(dlg.m_nJibun1 == 0 && dlg.m_nJibun1 == 0)
		{
			InsertDongInfo(pPlace, dlg.m_nDongID);
		}
		else 
		{
			long nPosX = 0, nPosY = 0;
			CPOIUnit *pPoi = m_poiNew.GetPOI(dlg.m_nDongID);				
			CString str = pPoi->GetFullName() + " ";
			str += dlg.m_nRoadID > 0? dlg.m_strRoad	+ " " : "";
			str += dlg.m_strJibun;

			GetJibunPos(dlg.m_nDongID, dlg.m_nRoadID, dlg.m_nRoadSubID, dlg.m_nJibun1, dlg.m_nJibun2, nPosX, nPosY);

			if(nPosX > 0 && nPosY > 0)
			{				
				//pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(dlg.m_pDetailPOI), dlg.m_pDetailPOI-);
				pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(str), str);
				pPlace->SetPOI(pPoi);
				pPlace->SetDetailPos(nPosX, nPosY); 
				pPlace->SetDetail(str);

				nType == PLACE_START ? OnBnClickedStartMapBtn() :
								OnBnClickedDestMapBtn();

				bMapFocus = TRUE;
			}
			else
			{
				InsertDongInfo(pPlace, dlg.m_nDongID);
				pPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(str), str);
			}
		}

		if(bMapFocus == FALSE)
		{
			nType == PLACE_START ? m_EDT_DEST_DONG.pEdit->SetFocus() : 
				m_EDT_DEST_DETAIL.pEdit->SetFocus();
		}
	}

	GetSectionCharge();
}


void CRcpInsungDlg::ChangeDistance()
{
	CString strDistance = "";
	strDistance.Format("%.1f",m_fDirectDistance );

	m_stcDistance.SetWindowText(strDistance+"K");
}

void CRcpInsungDlg::GetJibunPos(long nDongID, long nRoadID, long nRoadSubID, long nJibun1, long nJibun2, long &nPosX, long &nPosY)
{ 
	nPosX = 0, nPosY = 0;

	CMkCommand cmd(m_pMkDb, "select_address_list_insung_1");
	cmd.AddParameter(nDongID);
	cmd.AddParameter(nRoadID);
	cmd.AddParameter(nRoadSubID);
	cmd.AddParameter(nJibun1);
	cmd.AddParameter(nJibun2);
	CMkParameter *parPosX = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parPosY = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute())
		return;
	parPosX->GetValue(nPosX);
	parPosY->GetValue(nPosY);

	if(nPosX > 0 && nPosY > 0)
	{
		if(nPosX <100000000)
		{
			nPosX = ((float)nPosX / 0.36);
			nPosY = ((float)nPosY / 0.36);
		}		
	}
}
void CRcpInsungDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	
}
void CRcpInsungDlg::OnCbnKillfocusOrderPhoneCombo()
{
	m_EDT_ORDER_PHONE.pEdit->ShowWindow(TRUE);
	m_cmbOrderPhone.ShowWindow(FALSE);

}

void CRcpInsungDlg::OnCbnSelchangeOrderPhoneCombo()
{
	long nIndex = m_cmbOrderPhone.GetCurSel();

	if(nIndex == -1)
		return;

	ST_PHONE_INFO *st = (ST_PHONE_INFO*)m_cmbOrderPhone.GetItemData(nIndex);

	m_EDT_ORDER_DEPART.pEdit->SetWindowText(st->strDepart);
	m_EDT_ORDER_MANAGER.pEdit->SetWindowText(st->strManager);
	m_EDT_ORDER_PHONE.pEdit->SetWindowText(LF->GetDashPhoneNumber(st->strTel));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnBnClickedAllocateBtn()
{
	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->OnBnClickedCompleteBtn();
}

void CRcpInsungDlg::OnBnClickedRcpBtn()
{
	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->OnBnClickedCancelABtn();
}

void CRcpInsungDlg::OnBnClickedRcpCancelBtn()
{
	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->OnBnClickedCancelOBtn();
}

void CRcpInsungDlg::OnBnClickedRcpWaitBtn()
{
	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->OnChangeWaitState();
}

void CRcpInsungDlg::OnBnClickedCompleteBtn()
{
	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->OnBnClickedFinishBtn();
}

void CRcpInsungDlg::OnBnClickedCustomerChargeBtn2()
{
	OnMileagePopupWindow();
}

void CRcpInsungDlg::OnBnClickedChangeStartDestBtn()
{
	OnMenuContextPlace(ID_PLACE_EXCHANGE_DS);
}

void CRcpInsungDlg::OnBnClickedDestToOnameBtn()
{
	OnMenuContextPlace(ID_PLACE_COPY_DO);
	ChangeRcpState();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_CID)
	{
		KillTimer(TIMER_CID);
		SearchCustomer(PLACE_ORDER);
	}
	else if(nIDEvent == TIMER_FOCUS)
	{
		KillTimer(TIMER_FOCUS);
		m_EDT_START_NAME.pEdit->SetFocus();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRcpDlg::OnTimer(nIDEvent);
}



void CRcpInsungDlg::DisplayRiderInfo()
{
	CRect rcNo, rcPhone, rcBtn, rcEdt;
 
	m_edtRiderNo.GetWindowRect(&rcNo); ScreenToClient(rcNo);
	m_edtRiderPhone.GetWindowRect(&rcPhone); ScreenToClient(rcPhone);
	m_btnRiderInfo.GetWindowRect(&rcBtn); ScreenToClient(rcBtn);
	m_EDT_CHARGE_DRIVING.pEdit->GetWindowRect(&rcEdt); ScreenToClient(rcEdt);

	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{
		//rcNo.right = rcBtn.left - 2;
		//rcPhone.right = rcBtn.left - 2;

		//m_edtRiderNo.MoveWindow(rcNo);
		//m_edtRiderPhone.MoveWindow(rcPhone);

		m_btnRiderInfo.ShowWindow(TRUE);
		m_btnRiderSmsSend.ShowWindow(TRUE);
		m_edtRiderNo.SetWindowText(LF->GetStringFromLong(m_nRNo));
		m_edtRiderCompany.SetWindowText(m_ci.GetName(m_nRiderCompany));
		m_edtRiderPhone.SetWindowText(LF->GetDashPhoneNumber(m_strRPhone));
	}
	else
	{
		//rcNo.right = rcEdt.right;
		//rcPhone.right = rcEdt.right;

		//m_edtRiderNo.MoveWindow(rcNo);
		//m_edtRiderPhone.MoveWindow(rcPhone);

		m_btnRiderInfo.ShowWindow(FALSE);
		m_btnRiderSmsSend.ShowWindow(FALSE);
		m_edtRiderNo.SetWindowText("");
		m_edtRiderCompany.SetWindowText("");
		m_edtRiderPhone.SetWindowText("");
	}
	
};

void CRcpInsungDlg::OnBnClickedRiderInfoBtn()
{
	if(m_nRiderCompany > 0 && m_nRNo > 0)
		LU->ShowRiderInfoDlg(m_nRiderCompany, m_nRNo);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnBnClickedRiderSearchBtn()
{
	OnMenuContextRider(ID_MENU_RIDER_ALLOC);
}

void CRcpInsungDlg::OnBnClickedPayTypeRadio()
{
	if(GetPayTypeNew() == PAY_CARD) 
		m_btnNiceCard.ShowWindow(SW_SHOW);
	else
		m_btnNiceCard.ShowWindow(SW_HIDE);	
}

void CRcpInsungDlg::OnBnClickedEtcDeleteBtn()
{
	m_EDT_ETC.pEdit->SetWindowText("");
}


void CRcpInsungDlg::OnBnClickedPickup()
{
	OnBnClickedShowRiderPosBtn();
}

void CRcpInsungDlg::OnBnClickedNoFeeCheck()
{
	if(m_chkNoFee.GetCheck())
		OnBnClickedZeroIncomeBtn();
	else
	{
		OnEnChangeChargeDrivingEdit();
	}
}

void CRcpInsungDlg::OnBnClickedStartClearBtn()
{
	if(MessageBox("출발지 정보를 초기화 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
		CRcpDlg::OnBnClickedStartClearBtn();
}

void CRcpInsungDlg::OnBnClickedDestClearBtn()
{
	if(MessageBox("도착지 정보를 초기화 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
		CRcpDlg::OnBnClickedDestClearBtn();
}

void CRcpInsungDlg::OnBnClickedCustomerChargeBtn()
{
	OnBnClickedInputChargeNewBtn();
}

void CRcpInsungDlg::OnBnClickedCustomerSearchBtn()
{
	CSearchCustomerInsungRcpDlg dlg;
	dlg.m_nCompany = m_pBi->nCompanyCode;
	dlg.m_nCNo = m_pOrder->GetCNo();
	
	
	if(dlg.DoModal() == IDOK) //아무 액션도 없움
	{
//		m_pOrder->SearchCustomerCNo(dlg.m_nCNo, TRUE, TRUE, dlg.m_nTelID, FALSE);
//		DeleteOphoneCombo();
	}
}

void CRcpInsungDlg::OnCancel()
{
	DELETE_OBJECT(m_pHistoryInsung);
	

	CRcpDlg::OnCancel();
}

void CRcpInsungDlg::OnMove(int x, int y)
{
	CRcpDlg::OnMove(x, y);

	if(m_pHistoryInsung && !m_bHistoryMoveDown)
		m_pHistoryInsung->m_Magnetic.AttachTo();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CRcpInsungDlg::OnBnClickedClientShareOrderCheck()
{
	if(m_nInitItem <= 0)
		return;

	BOOL bCheck = m_chkClientShareOrder.GetCheck();
 
	if(bCheck == TRUE)
	{
		if(LF->MakeShareOrder(m_nInitItem, FALSE))
			MessageBox("공유되었습니다", "확인", MB_ICONINFORMATION);
		else
			m_chkClientShareOrder.SetCheck(FALSE);
	}
	else
	{
		if(LF->MakeShareOrder(m_nInitItem, TRUE))
			MessageBox("공유해지되었습니다", "확인", MB_ICONINFORMATION);
		else
			m_chkClientShareOrder.SetCheck(TRUE);
	}
	
}



CString CRcpInsungDlg::GetDisplayDongAndAddress(long nDongID, CString strDong, CString strAddress)
{
	CString strText = strDong;
	if(nDongID > 0)
	{
		strText.Format("%s %s", m_poiNew.GetPOI(nDongID)->GetRegionName(), strAddress);
		strText.Trim(' ');
	}

	return strText;
}



void CRcpInsungDlg::OnBnClickedCarTypeRadio()
{
	m_cmbTruckType.SetCurSel(0);
// 	for(int i=0; i<_cartype.size() / sizeof(long); i++)
// 	{
// 		long nItem
// 	}
	
}

void CRcpInsungDlg::OnCbnSelchangeTruckTypeCombo()
{
	long nTruck = m_cmbTruckType.GetItemData(m_cmbTruckType.GetCurSel());
	SetCarTypeNew(nTruck);
}
