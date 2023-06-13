// RcpDlg.cpp : 구현 파일입니다.

#include "stdafx.h"
#include "quick.h" 
#include "RcpDlg.h"
#include "RcpView.h" 
#include "MainFrm.h"
#include "SmsDlg.h"
#include "NewConnListDlg.h"  
#include "DelayOrderDlg2.h"
#include "SignDlg.h"  
#include "HistoryDlg.h"     
#include "SelectChargeDlg.h"
#include "ChargeSectionTypeDlg.h"  
#include "ScheduleOrderDlg.h"
#include "ScheduleOrderListDlg.h"
#include "ConsignDlg.h"
#include "RiderMapDlg.h"
#include "VarietyDlg.h"
#include "RcpCopyData.h" 
#include "MyMkMessenger.h"
#include "JinsangTelRegDlg.h"
#include "RcpPageCTIForm.h"
#include "OrderProcessStateDlg.h"
#include "MileageInfo.h"
#include "CompleteAfterEditDlg.h"
#include "UserDongPos.h"
#include "CustomerMileageDlg.h"
#include "CountMileageLogDlg.h" 
#include "SearchPOIDlg.h"
#include "POIBoundary.h"
#include "RcpPlaceInfo.h"
#include "RcpPageMapForm.h"
#include "MenuEtcUserDlg.h"
#include "RegisterWNoDlg.h"
#include "DepositRateDlg.h"
#include "ReserveOrderDlg.h"
#include "MakeHtmlTable.h"
#include "OrderLogDetailDlg.h"
#include "CustomerData.h"
#include "MenuEtcUserDlg.h"
#include "LogiMapCns.h"
#include "Charge.h"
#include "SimpleMapDlg.h"
#include "RcpDlgMapDlg.h"
#include "RiderTraceMapDlg.h"
#include "ChargeAdd.h"
#include "EditItemDlg.h"
#include "ChargeHistoryMemDlg.h"
#include "RcpDlgSetupDlg.h"
#include "RcpMultiStateChange.h"
#include "RcpViewBase.h"
#include "SearchManagerDlg.h"
#include "ConsignLinkDlg.h"
#include "RcpPlaceInfo.h"
#include "CardVerifyDlg.h"
#include "SearchRegionDlg.h"
#include <math.h>
#include "CancelDlg.h"
#include "RiderMsgDlg.h"
#include "CreditHistoryDlg.h"
#include "ProperChargeDlg.h"
#include "DirectChargeInputDlg1.h"
#include "PayCashDlg.h"
#include "EMailDlg.h"
#include "FoodCompleteDlg.h"
#include "AddRiderShareInfoDlg.h"
#include "CustomMyAfxMessgagebox.h"
#include "IPass.h"

#define ID_MENU_ITEM_SELECT 100
#define ID_MENU_ITEM_EDIT 200
#define ID_MENU_PHONE_SET_SMS 40000

#define HIDE_DLG(x) if(x) x->ShowWindow(SW_HIDE);
#define SHOW_DLG(x) if(x) x->ShowWindow(SW_SHOWNA);
#define REFRESH_TIMER_ORDER_LOG 3000
#define TIMER_REVISIT_CUSTOMER 4000

#define INIT_SEARCH_EDIT(x) if(x) {  \
	x->m_edtSearchStart.SetWindowText(""""); \
	x->m_edtSearchDest.SetWindowText(""""); \
	x->m_edtSearchEtc.SetWindowText(""""); \
	x->m_edtSearchManager.SetWindowText(""""); } 

#define QUICK_OK_2920_MENT "{신규/친절/쿠폰판지급}"
#define QUICK_OK_2904_MENT "{친절,홍보금지,확인함}"
#define QUICK_OK_2931_MENT "{친절,홍보금지,쿠폰판 도장 꼭 찍어주세요}"
#define QUICK_OK_2907_MENT "{쿠폰판싸인꼭하세요}"

#define QUICK_CALL_7700 7700
#define DEMO_10 10
#define ID_CHARGE_REINIT 1001

static BOOL bRouteSend = FALSE;
static float fRouteDistance = 0.0;

#pragma comment(lib, "UxTheme.lib")

#define GET_CUR_CHARGE()	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat( \
	m_pCharge->GetCharge(m_pBi->nCompanyCode, \
	m_pStart->GetPOI() == NULL ? 0 : m_pStart->GetPOI()->GetDongID(), \
	m_pDest->GetPOI() == NULL ? 0 : m_pDest->GetPOI()->GetDongID(), \
	GetCarTypeNew(&m_cmbCarType), m_cmbChargeType.GetCurSel(), \
	m_pOrder->GetGNo()) \
	)); \
	RefreshCharge();

//리소스 번호가 자꾸 바껴버림
UINT nStatic[RCP_STATIC_COUNT] = {IDC_RCP_STATIC1, IDC_RCP_STATIC2, IDC_RCP_STATIC3, IDC_RCP_STATIC4, IDC_RCP_STATIC5, IDC_RCP_STATIC6, IDC_RCP_STATIC7, IDC_RCP_STATIC8, IDC_RCP_STATIC9, IDC_RCP_STATIC10, 
IDC_RCP_STATIC11, IDC_RCP_STATIC12, IDC_RCP_STATIC13, IDC_RCP_STATIC14, IDC_RCP_STATIC15, IDC_RCP_STATIC16, IDC_RCP_STATIC17, IDC_RCP_STATIC18, IDC_RCP_STATIC19, IDC_RCP_STATIC20,
IDC_RCP_STATIC21, IDC_RCP_STATIC22, IDC_RCP_STATIC23, IDC_RCP_STATIC24, IDC_RCP_STATIC25, IDC_RCP_STATIC26, IDC_RCP_STATIC27, IDC_RCP_STATIC28, IDC_RCP_STATIC29, IDC_RCP_STATIC30,
IDC_RCP_STATIC31, IDC_RCP_STATIC32, IDC_RCP_STATIC33, IDC_RCP_STATIC34, IDC_RCP_STATIC35, IDC_RCP_STATIC36, IDC_RCP_STATIC37, IDC_RCP_STATIC38, IDC_RCP_STATIC39, IDC_RCP_STATIC40,
IDC_RCP_STATIC41, IDC_RCP_STATIC42, IDC_RCP_STATIC43, IDC_RCP_STATIC44, IDC_RCP_STATIC45, IDC_RCP_STATIC46, IDC_RCP_STATIC47, IDC_RCP_STATIC48, IDC_RCP_STATIC49, IDC_RCP_STATIC50,
IDC_RCP_STATIC51, IDC_RCP_STATIC52, IDC_RCP_STATIC53, IDC_RCP_STATIC54, IDC_RCP_STATIC55, IDC_RCP_STATIC56, IDC_RCP_STATIC57, IDC_RCP_STATIC58, IDC_RCP_STATIC59, IDC_RCP_STATIC61,
IDC_RCP_STATIC63, IDC_RCP_STATIC64, IDC_RCP_STATIC70};

static char* chMin[] = {"0","5","10","15","20","25","30","40","50","60","70","80","90","120"};
static long nMinCount = 14;

static char* chMoneyCoupon[] = {"0", "100", "200","250", "300", "400","450", "500", "600", "700", "800", "900", "1000", 
"1500", "2000", "2500", "3000", "3500", "4000", "4500", "5000"};
static char* chPercentPoupon[] = {"0", "5", "10", "20", "30", "40", "50", "60", "70", "80", "90"};
static long nMoneyCoupon = 19;
static long nPercentCoupon = 11;

static DWORD dwLastCNSTime = 0;
static int nCnsServerErrorCount = 0;

#define TIMER_FOR_CNS				1000
#define TIMER_FOR_CURRENT_TIME		2000
#define EDIT_ORDER_STATE_TIMER		2002	
#define CHARGE_CHANGED_TIMER		9898
#define HIDE_SEARCH_DONG_LIST_TIMER	1004
#define  PAY_TYPE_MILEAGE_CREDIT 6

#define  NO_MODIFY_POI 0
#define  MODIFY_POI_START 1
#define  MODIFY_POI_DEST 2
#define  MODIFY_POI_VIA 3

#define  TOP_WINDOW 400

#define  NO_MILEAGE_PERSON 10
static long m_nCurQueryChargeUniqueID = 1;

#define ONLY_DISTANCE 10

enum { ID_MENU_REG_JINSANG = 0xF000, 
ID_MENU_MAKE_CALL_CID,
ID_MENU_ADD_CID,
ID_MENU_COPY_CID};


// CRcpDlg

IMPLEMENT_DYNAMIC(CRcpDlg, CRcpDlgBase)

CRcpDlg::CRcpDlg()
: CRcpDlgBase()
, m_strChargeRevision(_T(""))
{
	Construct(TRUE); 
}

CRcpDlg::~CRcpDlg()
{
	//by mksong (2012-01-26 오전 11:10) 이 부분 추가 안되면, HideHistoryDlgExeMe에서 
	//이미 소멸된 m_pLastSelRcpDlg 값의 GetSafeHwnd() 를 호촐하여 런타임에러 발생
	if(LU->GetRcpView()->m_pLastSelRcpDlg == this)
		LU->GetRcpView()->m_pLastSelRcpDlg = NULL;

	DELETE_OBJECT(m_pOrder);
	DELETE_OBJECT(m_pStart);
	DELETE_OBJECT(m_pDest);
	DELETE_OBJECT(m_pHistoryDlg);
	DELETE_OBJECT(m_pOrderProcessStateDlg);
	DELETE_OBJECT(m_pSearchPOIDlg);
	DELETE_OBJECT(m_pCharge);
	DELETE_OBJECT(m_pDisplayChargeInfo);	 
	DELETE_OBJECT(m_pReserveOrderDlg);
	DELETE_OBJECT(m_pCreditHistoryDlg);
}

//"지원되지 않는 작업을 시도하였습니다." 에러인 경우에 아래 주석을 풀고 로그를 보면 위치를 정확히 알수 있음
//#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d, ID = %d\n", TEXT(__FILE__), TEXT(__LINE__), y);DDX_Control(x, y, z);}


void CRcpDlg::DoDataExchange(CDataExchange* pDX)
{
	CRcpDlgBase::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
	DDX_Control(pDX, IDC_CNS_EDIT, m_edtCNS);
	DDX_Control(pDX, IDC_COUPON_CHARGE_COMBO, m_cmbCouponCharge);	
	DDX_Control(pDX, IDC_COUPON_TYPE_COMBO, m_cmbCouponType);
	DDX_Control(pDX, IDC_DEST_MAP_BTN, m_btnDestMap);
	DDX_Control(pDX, IDC_DEST_MP_EDIT, m_edtDestMP);
	DDX_Control(pDX, IDC_ITEM_TYPE_COMBO, m_cmbItemType);
	DDX_Control(pDX, IDC_NEW_AFTER_COPY_BTN, m_btnNewAfterCopy);
	DDX_Control(pDX, IDC_NEW_BTN, m_btnNew);
	DDX_Control(pDX, IDC_ORDER_CNO_EDIT, m_edtOrderCNo);
	DDX_Control(pDX, IDC_ORDER_DETAIL_EDIT, m_edtOrderDetail);
	DDX_Control(pDX, IDC_ORDER_MAP_BTN, m_btnOrderMap);
	DDX_Control(pDX, IDC_ORDER_MEMO_EDIT, m_edtOrderMemo);
	DDX_Control(pDX, IDC_ORDER_MP_EDIT, m_edtOrderMP);
	DDX_Control(pDX, IDC_INTERCALL_ETC_EDIT, m_edtIntercallEtc);
	DDX_Control(pDX, IDC_QUERY_CHARGE_BTN, m_btnQueryCharge);
	DDX_Control(pDX, IDC_QUERY_CHARGE_BTN2, m_btnQueryCharge2);
	DDX_Control(pDX, IDC_RCP_COPY_BTN, m_btnRcpCopy);

	DDX_Control(pDX, IDC_START_MAP_BTN, m_btnStartMap);
	DDX_Control(pDX, IDC_START_MP_EDIT, m_edtStartMP);

	DDX_Control(pDX, IDC_START_ADDRESS_STATIC, m_STC_START_ADDERSS.stcMarkup);
	DDX_Control(pDX, IDC_DEST_ADDRESS_STATIC, m_STC_DEST_ADDERSS.stcMarkup);
	DDX_Control(pDX, IDC_START_ADDRESS_IS_STATIC, m_STC_START_ADDERSS.stcFlat);
	DDX_Control(pDX, IDC_DEST_ADDRESS_IS_STATIC, m_STC_DEST_ADDERSS.stcFlat);

	DDX_Control(pDX, IDC_ABLE_ALLOC_LOAD_INS_CHECK, m_chkAbleAllocLoadIns);
	DDX_Control(pDX, IDC_FOOD_ORDER_CHECK, m_chkFoodOrder);
	DDX_Control(pDX, IDC_DIRECT_DISTANCE_CHECK, m_chkDirectDistance);

	if(IsInsungDlg())
	{
		DDX_Control(pDX, IDC_CID_EDIT, m_EDT_CID.edtFlatEditInsung);
		DDX_Control(pDX, IDC_STATE_EDIT, m_EDT_STATE.edtFlatEditInsung);
		DDX_Control(pDX, IDC_TNO_EDIT, m_EDT_TNO.edtFlatEditInsung);
		DDX_Control(pDX, IDC_ETC_EDIT, m_EDT_ETC.edtFlatEditInsung);
		DDX_Control(pDX, IDC_WNAME_EDIT, m_EDT_WNAME.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_DRIVING_EDIT, m_EDT_CHARGE_DRIVING.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_ADD_EDIT, m_EDT_CHARGE_ADD.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_BASIC_EDIT, m_EDT_CHARGE_BASIC.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_DIS_EDIT, m_EDT_CHARGE_DIS.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_SUM_EDIT, m_EDT_CHARGE_SUM.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_TRANS_EDIT, m_EDT_CHARGE_TRANS.edtFlatEditInsung);
		DDX_Control(pDX, IDC_ORDER_NAME_EDIT, m_EDT_ORDER_NAME.edtFlatEditInsung);
		DDX_Control(pDX, IDC_ORDER_PHONE_EDIT, m_EDT_ORDER_PHONE.edtFlatEditInsung);
		DDX_Control(pDX, IDC_ORDER_DEPART_EDIT, m_EDT_ORDER_DEPART.edtFlatEditInsung); 
		DDX_Control(pDX, IDC_ORDER_MANAGER_EDIT, m_EDT_ORDER_MANAGER.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_EDIT, m_EDT_START.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_NAME_EDIT, m_EDT_START_NAME.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_DEPART_EDIT, m_EDT_START_DEPART.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_MANAGER_EDIT, m_EDT_START_MANAGER.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_PHONE_EDIT, m_EDT_START_PHONE.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_DONG_EDIT, m_EDT_START_DONG.edtFlatEditInsung);
		DDX_Control(pDX, IDC_START_DETAIL_EDIT, m_EDT_START_DETAIL.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_EDIT, m_EDT_DEST.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_NAME_EDIT, m_EDT_DEST_NAME.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_DEPART_EDIT, m_EDT_DEST_DEPART.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_MANAGER_EDIT, m_EDT_DEST_MANAGER.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_PHONE_EDIT, m_EDT_DEST_PHONE.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_DONG_EDIT, m_EDT_DEST_DONG.edtFlatEditInsung);
		DDX_Control(pDX, IDC_DEST_DETAIL_EDIT, m_EDT_DEST_DETAIL.edtFlatEditInsung);
		DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_CMB_CHARGE_TYPE.comboInsung);
		DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_CMB_ALLOC_GROUP.comboInsung);
		DDX_Control(pDX, IDC_NOT_SEND_COMPLETE_SMS_CHECK, m_BTN_NOT_SEND_COMPLETE_SMS.buttonFlat);
		DDX_Control(pDX, IDC_AUTO_SHARE_ORDER_CHECK, m_BTN_AUTO_SHARE_ORDER.buttonFlat);


		m_EDT_CID.pEdit = &m_EDT_CID.edtFlatEditInsung;
		m_EDT_STATE.pEdit = &m_EDT_STATE.edtFlatEditInsung;
		m_EDT_TNO.pEdit = &m_EDT_TNO.edtFlatEditInsung;
		m_EDT_ETC.pEdit = &m_EDT_ETC.edtFlatEditInsung;
		m_EDT_WNAME.pEdit = &m_EDT_WNAME.edtFlatEditInsung;
		m_EDT_CHARGE_DRIVING.pEdit = &m_EDT_CHARGE_DRIVING.edtFlatEditInsung;
		m_EDT_CHARGE_ADD.pEdit = &m_EDT_CHARGE_ADD.edtFlatEditInsung;
		m_EDT_CHARGE_BASIC.pEdit = &m_EDT_CHARGE_BASIC.edtFlatEditInsung;
		m_EDT_CHARGE_DIS.pEdit = &m_EDT_CHARGE_DIS.edtFlatEditInsung;
		m_EDT_CHARGE_SUM.pEdit = &m_EDT_CHARGE_SUM.edtFlatEditInsung;
		m_EDT_CHARGE_TRANS.pEdit = &m_EDT_CHARGE_TRANS.edtFlatEditInsung;
		m_EDT_ORDER_NAME.pEdit = &m_EDT_ORDER_NAME.edtFlatEditInsung;
		m_EDT_ORDER_PHONE.pEdit = &m_EDT_ORDER_PHONE.edtFlatEditInsung;
		m_EDT_ORDER_DEPART.pEdit = &m_EDT_ORDER_DEPART.edtFlatEditInsung;
		m_EDT_ORDER_MANAGER.pEdit = &m_EDT_ORDER_MANAGER.edtFlatEditInsung;
		m_EDT_START.pEdit = &m_EDT_START.edtFlatEditInsung;
		m_EDT_START_NAME.pEdit = &m_EDT_START_NAME.edtFlatEditInsung;
		m_EDT_START_DEPART.pEdit = &m_EDT_START_DEPART.edtFlatEditInsung;
		m_EDT_START_MANAGER.pEdit = &m_EDT_START_MANAGER.edtFlatEditInsung;
		m_EDT_START_PHONE.pEdit = &m_EDT_START_PHONE.edtFlatEditInsung;
		m_EDT_START_DONG.pEdit = &m_EDT_START_DONG.edtFlatEditInsung;
		m_EDT_START_DETAIL.pEdit = &m_EDT_START_DETAIL.edtFlatEditInsung;
		m_EDT_DEST.pEdit = &m_EDT_DEST.edtFlatEditInsung;
		m_EDT_DEST_NAME.pEdit = &m_EDT_DEST_NAME.edtFlatEditInsung;
		m_EDT_DEST_DEPART.pEdit = &m_EDT_DEST_DEPART.edtFlatEditInsung;
		m_EDT_DEST_MANAGER.pEdit = &m_EDT_DEST_MANAGER.edtFlatEditInsung;
		m_EDT_DEST_PHONE.pEdit = &m_EDT_DEST_PHONE.edtFlatEditInsung;
		m_EDT_DEST_DONG.pEdit = &m_EDT_DEST_DONG.edtFlatEditInsung;
		m_EDT_DEST_DETAIL.pEdit = &m_EDT_DEST_DETAIL.edtFlatEditInsung;
		m_CMB_CHARGE_TYPE.pCombo = &m_CMB_CHARGE_TYPE.comboInsung;
		m_CMB_ALLOC_GROUP.pCombo = &m_CMB_ALLOC_GROUP.comboInsung;
		m_BTN_NOT_SEND_COMPLETE_SMS.pButton = &m_BTN_NOT_SEND_COMPLETE_SMS.buttonFlat;
		m_BTN_AUTO_SHARE_ORDER.pButton = &m_BTN_AUTO_SHARE_ORDER.buttonFlat;

		m_STC_START_ADDERSS.pStatic = &m_STC_START_ADDERSS.stcMarkup;
		m_STC_DEST_ADDERSS.pStatic = &m_STC_DEST_ADDERSS.stcMarkup;	
	}
	else
	{
		DDX_Control(pDX, IDC_CID_EDIT, m_EDT_CID.edtFlatEdit2);
		DDX_Control(pDX, IDC_STATE_EDIT, m_EDT_STATE.edtFlatEdit2);
		DDX_Control(pDX, IDC_TNO_EDIT, m_EDT_TNO.edtFlatEdit2);
		DDX_Control(pDX, IDC_ETC_EDIT, m_EDT_ETC.edtFlatEdit2);
		DDX_Control(pDX, IDC_WNAME_EDIT, m_EDT_WNAME.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_DRIVING_EDIT, m_EDT_CHARGE_DRIVING.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_ADD_EDIT, m_EDT_CHARGE_ADD.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_BASIC_EDIT, m_EDT_CHARGE_BASIC.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_DIS_EDIT, m_EDT_CHARGE_DIS.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_SUM_EDIT, m_EDT_CHARGE_SUM.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_TRANS_EDIT, m_EDT_CHARGE_TRANS.edtFlatEdit2);
		DDX_Control(pDX, IDC_ORDER_NAME_EDIT, m_EDT_ORDER_NAME.edtFlatEdit2);
		DDX_Control(pDX, IDC_ORDER_PHONE_EDIT, m_EDT_ORDER_PHONE.edtFlatEdit2);
		DDX_Control(pDX, IDC_ORDER_DEPART_EDIT, m_EDT_ORDER_DEPART.edtFlatEdit2);
		DDX_Control(pDX, IDC_ORDER_MANAGER_EDIT, m_EDT_ORDER_MANAGER.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_EDIT, m_EDT_START.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_NAME_EDIT, m_EDT_START_NAME.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_DEPART_EDIT, m_EDT_START_DEPART.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_MANAGER_EDIT, m_EDT_START_MANAGER.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_PHONE_EDIT, m_EDT_START_PHONE.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_DONG_EDIT, m_EDT_START_DONG.edtFlatEdit2);
		DDX_Control(pDX, IDC_START_DETAIL_EDIT, m_EDT_START_DETAIL.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_EDIT, m_EDT_DEST.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_NAME_EDIT, m_EDT_DEST_NAME.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_DEPART_EDIT, m_EDT_DEST_DEPART.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_MANAGER_EDIT, m_EDT_DEST_MANAGER.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_PHONE_EDIT, m_EDT_DEST_PHONE.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_DONG_EDIT, m_EDT_DEST_DONG.edtFlatEdit2);
		DDX_Control(pDX, IDC_DEST_DETAIL_EDIT, m_EDT_DEST_DETAIL.edtFlatEdit2);
		DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_CMB_CHARGE_TYPE.combo);
		DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_CMB_ALLOC_GROUP.combo);
		DDX_Control(pDX, IDC_NOT_SEND_COMPLETE_SMS_CHECK, m_BTN_NOT_SEND_COMPLETE_SMS.button);
		DDX_Control(pDX, IDC_AUTO_SHARE_ORDER_CHECK, m_BTN_AUTO_SHARE_ORDER.button);
		//DDX_Control(pDX, IDC_START_ADDRESS_STATIC, m_STC_START_ADDERSS.stcMarkup);
		//DDX_Control(pDX, IDC_DEST_ADDRESS_STATIC, m_STC_DEST_ADDERSS.stcMarkup);

		m_EDT_CID.pEdit = &m_EDT_CID.edtFlatEdit2;
		m_EDT_STATE.pEdit = &m_EDT_STATE.edtFlatEdit2;
		m_EDT_TNO.pEdit = &m_EDT_TNO.edtFlatEdit2;
		m_EDT_ETC.pEdit = &m_EDT_ETC.edtFlatEdit2;
		m_EDT_WNAME.pEdit = &m_EDT_WNAME.edtFlatEdit2;
		m_EDT_CHARGE_DRIVING.pEdit = &m_EDT_CHARGE_DRIVING.edtFlatEdit2;
		m_EDT_CHARGE_ADD.pEdit = &m_EDT_CHARGE_ADD.edtFlatEdit2;
		m_EDT_CHARGE_BASIC.pEdit = &m_EDT_CHARGE_BASIC.edtFlatEdit2;
		m_EDT_CHARGE_DIS.pEdit = &m_EDT_CHARGE_DIS.edtFlatEdit2;
		m_EDT_CHARGE_SUM.pEdit = &m_EDT_CHARGE_SUM.edtFlatEdit2;
		m_EDT_CHARGE_TRANS.pEdit = &m_EDT_CHARGE_TRANS.edtFlatEdit2;
		m_EDT_ORDER_NAME.pEdit = &m_EDT_ORDER_NAME.edtFlatEdit2;
		m_EDT_ORDER_PHONE.pEdit = &m_EDT_ORDER_PHONE.edtFlatEdit2;
		m_EDT_ORDER_DEPART.pEdit = &m_EDT_ORDER_DEPART.edtFlatEdit2;
		m_EDT_ORDER_MANAGER.pEdit = &m_EDT_ORDER_MANAGER.edtFlatEdit2;
		m_EDT_START.pEdit = &m_EDT_START.edtFlatEdit2;
		m_EDT_START_NAME.pEdit =&m_EDT_START_NAME.edtFlatEdit2;
		m_EDT_START_DEPART.pEdit = &m_EDT_START_DEPART.edtFlatEdit2;
		m_EDT_START_MANAGER.pEdit = &m_EDT_START_MANAGER.edtFlatEdit2;
		m_EDT_START_PHONE.pEdit = &m_EDT_START_PHONE.edtFlatEdit2;
		m_EDT_START_DONG.pEdit = &m_EDT_START_DONG.edtFlatEdit2;
		m_EDT_START_DETAIL.pEdit = &m_EDT_START_DETAIL.edtFlatEdit2;
		m_EDT_DEST.pEdit = &m_EDT_DEST.edtFlatEdit2;
		m_EDT_DEST_NAME.pEdit =&m_EDT_DEST_NAME.edtFlatEdit2;
		m_EDT_DEST_DEPART.pEdit = &m_EDT_DEST_DEPART.edtFlatEdit2;
		m_EDT_DEST_MANAGER.pEdit = &m_EDT_DEST_MANAGER.edtFlatEdit2;
		m_EDT_DEST_PHONE.pEdit = &m_EDT_DEST_PHONE.edtFlatEdit2;
		m_EDT_DEST_DONG.pEdit = &m_EDT_DEST_DONG.edtFlatEdit2;
		m_EDT_DEST_DETAIL.pEdit = &m_EDT_DEST_DETAIL.edtFlatEdit2;
		m_CMB_CHARGE_TYPE.pCombo = &m_CMB_CHARGE_TYPE.combo;
		m_CMB_ALLOC_GROUP.pCombo = &m_CMB_ALLOC_GROUP.combo;
		m_BTN_NOT_SEND_COMPLETE_SMS.pButton = &m_BTN_NOT_SEND_COMPLETE_SMS.button;
		m_BTN_AUTO_SHARE_ORDER.pButton = &m_BTN_AUTO_SHARE_ORDER.button;
		m_STC_START_ADDERSS.pStatic = &m_STC_START_ADDERSS.stcMarkup;
		m_STC_DEST_ADDERSS.pStatic = &m_STC_DEST_ADDERSS.stcMarkup;	

	}

	DDX_Control(pDX, IDC_STATE_PICTURE, m_stcPicState);

	DDX_Control(pDX, IDC_WAIT_AFTER_COPY_BTN, m_btnWaitAfterCopy);
	DDX_Control(pDX, IDC_WAIT_BTN, m_btnWait);
	DDX_Control(pDX, IDC_START_CNO_EDIT, m_edtStartCNo);
	DDX_Control(pDX, IDC_DEST_CNO_EDIT, m_edtDestCNo);
	DDX_Control(pDX, IDC_ORDER_DONG_EDIT, m_edtOrderDong);
	DDX_Control(pDX, IDC_DEPOSIT_EDIT, m_edtDeposit);
	DDX_Control(pDX, IDC_INQUIRY_BTN, m_btnInquiry);
	DDX_Control(pDX, IDC_NOTICE_BTN, m_btnNotice);
	//DDX_Control(pDX, ID_CONSIGN_BTN, m_btnConsign);
	DDX_Control(pDX, IDC_RIDER_AUTO_CHARGE_CHK, m_chkAutoCharge);	
	DDX_Control(pDX, IDC_RIDER_AUTO_CHARGE_EDIT, m_edtAutoCharge);
	DDX_Control(pDX, IDC_VALUE_ADD_EDIT, m_edtValueAdd);

	DDX_Control(pDX, IDC_CHARGE_VIA_BET_STATIC, m_stcChargeViaBet);

	DDX_Control(pDX, IDC_CONSIGN_BACK_CHARGE_STATIC, m_stcConBackOrderCharge);
	DDX_Control(pDX, IDC_COMMISSION_STATIC, m_stcConCommissionCharge);
	DDX_Control(pDX, IDC_TOTAL_CHARGE_STATIC, m_stcConTotalCharge);

	DDX_Control(pDX, IDC_COMMISSION_EDIT, m_edtConCommissionCharge);
	DDX_Control(pDX, IDC_TOTAL_CHARGE_EDIT, m_edtConTotalCharge);
	DDX_Control(pDX, IDC_CONSIGN_VIEW_BTN, m_btnConsignView);
	DDX_Control(pDX, IDC_MILE_RESERVE_EDIT, m_edtMileReserve);
	DDX_Control(pDX, IDC_CONSIGN_BACK_CHARGE_EDIT, m_edtConBackOrderCharge);



	//DDX_Text(pDX, IDC_START_ADDRESS_STATIC2, m_strChargeViaBet);
	DDX_Text(pDX, IDC_MILE_RESERVE_EDIT, m_strMileReserve);
	DDX_Text(pDX, IDC_RIDER_AUTO_CHARGE_EDIT, m_strMileageAutoCharge);
	DDX_Text(pDX, IDC_VALUE_ADD_EDIT, m_strValueAdd);
	DDX_Text(pDX, IDC_CID_EDIT, m_strCID);
	DDX_Text(pDX, IDC_CNS_EDIT, m_strCNS);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
	DDX_Text(pDX, IDC_STATE_EDIT, m_strState);
	DDX_Text(pDX, IDC_TNO_EDIT, m_strTNo);
	DDX_Text(pDX, IDC_WNAME_EDIT, m_strWName);
	DDX_Text(pDX, IDC_CHARGE_ADD_EDIT, m_strChargeAdd);
	DDX_Text(pDX, IDC_CHARGE_BASIC_EDIT, m_strChargeBasic);
	DDX_Text(pDX, IDC_CHARGE_DRIVING_EDIT, m_strChargeDriving);	
	DDX_Text(pDX, IDC_CHARGE_DIS_EDIT, m_strChargeDis);
	DDX_Text(pDX, IDC_CHARGE_SUM_EDIT, m_strChargeSum);
	DDX_Text(pDX, IDC_CHARGE_TRANS_EDIT, m_strChargeTrans);

	DDX_Text(pDX, IDC_ITEM_TYPE_COMBO, m_strItemType);
	DDX_Text(pDX, IDC_DEPOSIT_EDIT, m_strDeposit);
	DDX_Text(pDX, IDC_INTERCALL_ETC_EDIT, m_strIntercallEtc);
	DDX_Text(pDX, IDC_SMS_PHONE_EDIT, m_strSmsPhone);
	DDX_Text(pDX, IDC_CONSIGN_BACK_CHARGE_EDIT, m_strConBackOrderCharge);
	DDX_Text(pDX, IDC_COMMISSION_EDIT, m_sConCommissionCharge);
	DDX_Text(pDX, IDC_TOTAL_CHARGE_EDIT, m_strConTotalCharge);

	DDX_Control(pDX, IDC_UPDATE_AND_NEW_BTN, m_btnUpdateAndNew);
	DDX_Control(pDX, IDC_UPDATE_BTN, m_btnUpdate);
	DDX_Control(pDX, IDC_INPUT_CHARGE_NEW_BTN, m_btnInputNewCharge);
	DDX_Control(pDX, IDC_CONTEXT_MILEAGE_BTN, m_btnContextMileage);
	DDX_Control(pDX, IDC_MILEAGE_BALANCE_EDIT, m_edtMileageBalance);
	DDX_Text(pDX, IDC_MILEAGE_BALANCE_EDIT, m_sMileageBalance);
	//DDX_Control(pDX, IDC_NOT_ORDER_MILAGE_EDIT, m_edtNotOrderMileage);

	DDX_Control(pDX, IDC_ETC_BTN, m_btnEtc);

	DDX_Control(pDX, IDC_ORDER_EDIT, m_edtOrder);

	DDX_Control(pDX, IDC_ORDER_ADDRESS_STATIC, m_stcOrderAddress);

	DDX_Control(pDX, IDC_DEL_TYPE_COMBO, m_cmbDelType);
	DDX_Control(pDX, IDC_PAY_TYPE_COMBO, m_cmbPayType);
	DDX_Control(pDX, IDC_WAY_TYPE_COMBO, m_cmbWayType);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO, m_cmbCarType);
	DDX_Control(pDX, IDC_RUN_TYPE_COMBO, m_cmbRunType);
	DDX_Control(pDX, IDC_ORDER_LOG_LIST, m_lstOrderLog);
	DDX_Control(pDX, IDC_RESERVE_DISPLAY_STATIC, m_stcReserveDisplay);
	DDX_Control(pDX, IDC_SAVE_CHARGE_CHECK, m_chkSaveCharge);

	if(IsInsungDlg() == FALSE)
	{
		for(int i=0; i<RCP_STATIC_COUNT; i++)
			DDX_Control(pDX, nStatic[i], m_stcRcp[i]);
	}

	DDX_Control(pDX, IDC_CONTEXT_CHARGE_BTN, m_btnContextCharge);
	DDX_Control(pDX, IDC_CHARGE_SUM_TOTAL_EDIT, m_edtChargeSumTotal);
	DDX_Control(pDX, IDC_RIDER_INFO_STATIC, m_stcRiderInfo);

	DDX_Control(pDX, IDC_PAY_TYPE_PRE_BTN, m_btnPayType1);
	DDX_Control(pDX, IDC_PAY_TYPE_AFTER_BTN, m_btnPayType2);
	DDX_Control(pDX, IDC_PAY_TYPE_CREDIT_BTN, m_btnPayType3);
	DDX_Control(pDX, IDC_PAY_TYPE_ONLINE_BTN, m_btnPayType4);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN, m_btnCarType1);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN2, m_btnCarType2);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN3, m_btnCarType3);

	DDX_Control(pDX, IDC_ORDER_ADDRESS_EDIT, m_edtOrderAddress);
	DDX_Control(pDX, IDC_START_ADDRESS_EDIT, m_edtStartAddress);
	DDX_Control(pDX, IDC_DEST_ADDRESS_EDIT, m_edtDestAddress);
	DDX_Control(pDX, IDC_SMS_PHONE_EDIT, m_edtSmsPhone);

	DDX_Control(pDX, IDC_ORDER_DEST_SAME_BTN, m_btnOrderDestSame);
	DDX_Control(pDX, IDC_ORDER_START_SAME_BTN, m_btnOrderStartSame);
	DDX_Control(pDX, IDC_ORDER_DIFFERENT_BTN, m_btnOrderDifferent);
	DDX_Control(pDX, IDC_SAME_CAR_TYPE_ONLY_CHECK, m_chkSameCarTypeOnly);
	DDX_Control(pDX, IDC_ZERO_INCOME_BTN, m_btnZeroIncome);
	DDX_Control(pDX, IDC_CARD_STATE_STATIC, m_stcCardState);

	DDX_Control(pDX, IDC_CHARGE_RETURN_EDIT, m_edtChargeReturn);
	DDX_Text(pDX, IDC_CHARGE_RETURN_EDIT, m_strChargeReturn);
	DDX_Control(pDX, IDC_UPDATE_CANCEL_BTN, m_btnUpdateCancel);
	DDX_Control(pDX, IDC_PAY_TYPE_ONLINE_BTN2, m_btnPayType5);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN4, m_btnCarType4);
	DDX_Control(pDX, IDC_CAR_TYPE_BTN5, m_btnCarType5);
	DDX_Control(pDX, IDC_WAY_TYPE_BTN, m_btnWayType1);
	DDX_Control(pDX, IDC_WAY_TYPE_BTN2, m_btnWayType2);
	DDX_Control(pDX, IDC_WAY_TYPE_BTN3, m_btnWayType3);
	DDX_Control(pDX, IDC_RUN_TYPE_BTN, m_btnRunType1);
	DDX_Control(pDX, IDC_RUN_TYPE_BTN2, m_btnRunType2);
	DDX_Control(pDX, IDC_RUN_TYPE_BTN3, m_btnRunType3);
	DDX_Control(pDX, IDC_RUN_TYPE_BTN4, m_btnRunType4);
	DDX_Control(pDX, IDC_RIDER_COMPANY_STATIC, m_stcRiderCompany);
	DDX_Control(pDX, IDC_RIDER_PHONE_STATIC, m_stcRiderPhone);
	DDX_Control(pDX, IDC_RIDER_SEARCH_BTN, m_btnRiderSearch);
	DDX_Control(pDX, IDC_RIDER_SMS_SEND_BTN, m_btnRiderSmsSend);
	DDX_Control(pDX, IDC_NICE_CARD_BTN, m_btnNiceCard);
	DDX_Control(pDX, IDC_CHARGE_LOGI_EDIT, m_edtChargeLogi);

	DDX_Control(pDX, IDC_PROPER_CHARGE_EDIT1, m_edtProperCharge1);
	DDX_Control(pDX, IDC_PROPER_CHARGE_EDIT2, m_edtProperCharge2);
	DDX_Control(pDX, IDC_CLIENT_SHARE_ORDER_CHECK, m_chkClientShareOrder);

	DDX_Control(pDX, IDC_SHOW_PHONE_TYPE_ORDER_CHECK, m_chkShowPhoneTypeOrder);
	DDX_Control(pDX, IDC_SHOW_PHONE_TYPE_START_CHECK, m_chkShowPhoneTypeStart);
	DDX_Control(pDX, IDC_SHOW_PHONE_TYPE_DEST_CHECK, m_chkShowPhoneTypeDest);
	DDX_Control(pDX, IDC_CHARGE_COMPANY_EDIT, m_edtChargeCompany);
	DDX_Control(pDX, IDC_CHARGE_REVISION_EDIT, m_edtChargeRevision);
	DDX_Text(pDX, IDC_CHARGE_REVISION_EDIT, m_strChargeRevision);
	DDX_Control(pDX, IDC_CALL_PASS_BTN, m_btnCallPass);

	DDX_Control(pDX, IDC_CARGO_JABARA_CHECK, m_chkCargoJabara);
	DDX_Control(pDX, IDC_CARGO_LIFT_CHECK, m_chkCargoLift);
	DDX_Control(pDX, IDC_CARGO_WING_BODY_CHECK, m_chkCargoWingBody);
	DDX_Control(pDX, IDC_CARGO_LIFT_WING_CHECK, m_chkCargoLiftWing);
	DDX_Control(pDX, IDC_CARGO_FREEZER_CHECK, m_chkCargoFreezer);
}

BEGIN_MESSAGE_MAP(CRcpDlg, CRcpDlgBase)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
	ON_BN_CLICKED(IDC_NEW_BTN, OnBnClickedNewBtn)
	//ON_MESSAGE(WM_USER + 5656, OnOnGetCnsViaInfoGetCnsInfo)
	ON_MESSAGE(WM_USER + 6000, OnGetCnsInfo)
	ON_MESSAGE(WM_USER + 6005, OnHistoryChargeApply)
	ON_MESSAGE(WM_USER + ID_CHARGE_REINIT, OnPreChargeInit)

	ON_MESSAGE(WM_CHANGE_POI, OnChangePoi)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_WAIT_BTN, OnBnClickedWaitBtn)
	ON_BN_CLICKED(IDC_NEW_AFTER_COPY_BTN, OnBnClickedNewAfterCopyBtn)
	ON_BN_CLICKED(IDC_WAIT_AFTER_COPY_BTN, OnBnClickedWaitAfterCopyBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, OnBnClickedUpdateBtn)
	ON_BN_CLICKED(IDC_START_MAP_BTN, OnBnClickedStartMapBtn)
	ON_BN_CLICKED(IDC_DEST_MAP_BTN, OnBnClickedDestMapBtn)
	ON_CBN_SELCHANGE(IDC_COUPON_TYPE_COMBO, OnCbnSelchangeCouponTypeCombo)
	ON_EN_CHANGE(IDC_CHARGE_BASIC_EDIT, OnEnChangeChargeBasicEdit)
	ON_EN_CHANGE(IDC_CHARGE_ADD_EDIT, OnEnChangeChargeAddEdit)
	ON_EN_CHANGE(IDC_CHARGE_DIS_EDIT, OnEnChangeChargeDisEdit)
	ON_EN_CHANGE(IDC_CHARGE_SUM_EDIT, OnEnChangeChargeSumEdit)
	ON_EN_CHANGE(IDC_RIDER_AUTO_CHARGE_EDIT, OnEnChangeRiderAutoChargeEdit)
	
	ON_BN_CLICKED(IDC_QUERY_CHARGE_BTN, OnBnClickedQueryChargeBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND_RANGE(ID_PHONE1, ID_PHONE10, OnPhoneControl)
	ON_COMMAND_RANGE(ID_PHONE11, ID_PHONE20, OnPhoneControlSMS)
	ON_BN_CLICKED(IDC_ORDER_MAP_BTN, OnBnClickedOrderMapBtn)
	ON_BN_CLICKED(IDC_INQUIRY_BTN, OnBnClickedInquiryBtn)
	ON_BN_CLICKED(IDC_NOTICE_BTN, OnBnClickedNoticeBtn)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()


	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickHistoryList)
	ON_CBN_EDITCHANGE(IDC_COUPON_CHARGE_COMBO, OnCbnEditchangeCouponChargeCombo)
	ON_BN_CLICKED(IDC_INPUT_CHARGE_NEW_BTN, OnBnClickedInputChargeNewBtn)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_BN_CLICKED(IDC_QUERY_CHARGE_BTN2, OnBnClickedQueryChargeBtn2)
	ON_BN_CLICKED(ID_CONSIGN_BTN, OnBnClickedConsignBtn)
	ON_EN_KILLFOCUS(IDC_CHARGE_BASIC_EDIT, OnEnKillfocusChargeBasicEdit)
	ON_EN_KILLFOCUS(IDC_CHARGE_SUM_EDIT, OnEnKillfocusChargeSumEdit)
	ON_EN_KILLFOCUS(IDC_CHARGE_TRANS_EDIT, OnEnKillfocusChargeTransEdit)
	ON_BN_CLICKED(IDC_RIDER_AUTO_CHARGE_CHK, OnBnClickedRiderAutoChargeChk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CHARGE_LIST, OnLvnItemchangedChargeList)
	ON_COMMAND(ID_CUR_ORDER_STATE, OnCurOrderState)
	ON_EN_KILLFOCUS(IDC_RIDER_AUTO_CHARGE_EDIT, OnEnKillfocusRiderAutoChargeEdit)
	ON_EN_CHANGE(IDC_START_EDIT, &CRcpDlg::OnEnChangeStartEdit)
	ON_EN_CHANGE(IDC_DEST_EDIT, &CRcpDlg::OnEnChangeDestEdit)
	ON_EN_CHANGE(IDC_ORDER_EDIT, &CRcpDlg::OnEnChangeOrderEdit)
	ON_EN_SETFOCUS(IDC_ORDER_EDIT, &CRcpDlg::OnEnSetfocusOrderEdit)
	ON_EN_SETFOCUS(IDC_START_EDIT, &CRcpDlg::OnEnSetfocusStartEdit)
	ON_EN_SETFOCUS(IDC_DEST_EDIT, &CRcpDlg::OnEnSetfocusDestEdit)
	ON_EN_SETFOCUS(IDC_CID_EDIT, &CRcpDlg::OnEnSetfocusCIDEdit)
	ON_BN_CLICKED(IDC_ORDER_CUSTOMER_DLG_BTN, &CRcpDlg::OnBnClickedOrderCustomerDlgBtn)
	ON_BN_CLICKED(IDC_START_CUSTOMER_DLG_BTN, &CRcpDlg::OnBnClickedStartCustomerDlgBtn)
	ON_BN_CLICKED(IDC_DEST_CUSTOMER_DLG_BTN, &CRcpDlg::OnBnClickedDestCustomerDlgBtn)

	ON_COMMAND_RANGE(ID_MENU_ITEM_SELECT, ID_MENU_ITEM_SELECT + 20, OnMenuContextItem)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ITEM_EDIT, OnMenuContextItem)

	ON_COMMAND_RANGE_SINGLE(ID_MENU_FUNC_PASS_DATA, OnMenuContextFunc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_FUNC_USAGE_HISTORY, OnMenuContextFunc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_FUNC_VERIFY_SIGN, OnMenuContextFunc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_FUNC_ADD_TRANS, OnMenuContextFunc)

	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_LOG, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_COUNT_LOG, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MAILEAGE_NOT_COMPANY, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_NOT_ORDER1, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_USE_ORDER1, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_USER_ORDER, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CONSIGN_MODE, OnMenuContextMileage)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MILEAGE_MODE, OnMenuContextMileage)

	ON_COMMAND_RANGE_SINGLE(ID_PLACE_DELETE_O, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_DELETE_S, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_DELETE_D, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SEARCH_O, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SEARCH_S, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SEARCH_D, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_OS, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_OD, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_OS, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_OD, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_SO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_SD, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_SO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_SD, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_DO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_COPY_DS, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_DO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_EXCHANGE_DS, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_SHOW_DISTANCE, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SAVE_ADDRESS_SO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SAVE_ADDRESS_SS, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SAVE_ADDRESS_DO, OnMenuContextPlace)
	ON_COMMAND_RANGE_SINGLE(ID_PLACE_SAVE_ADDRESS_DD, OnMenuContextPlace)
	//ON_COMMAND_RANGE_SINGLE(ID_SHOW_DISTANCE, OnMenuContextPlace)

	ON_COMMAND(ID_SHOW_HISTORY, OnBnClickedHistoryBtn)
	ON_COMMAND(ID_SETUP_DLG, ShowSetupDlg)
	ON_COMMAND(ID_PLACE_SHOW_MAP_O, OnBnClickedOrderMapBtn)
	ON_COMMAND(ID_SHOW_ORDER_LOG, OnShowOrderLog)
	ON_COMMAND(ID_OPEN_RCP_DLG, OnOpenRcpDlg)

	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_QUERY, OnMenuContextCharge)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_WNO_REGISTION, OnMenuContextCharge)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_REFRESH_BASIC, OnMenuContextCharge)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_DEPOSIT_REFRESH, OnMenuContextCharge)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_DEPOSIT_REFRESH_BASIC, OnMenuContextCharge)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_CHARGE_DEPOSIT_EDIT, OnMenuContextCharge)

	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_URGE, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_RECALL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_JUST_CALL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_SPECIAL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER1, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER2, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER3, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER4, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER5, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER_UPDATE, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_TO_INTERCALL_ETC, OnMenuContextEtc)

	ON_COMMAND_RANGE_SINGLE(ID_MENU_REG_JINSANG, OnMenuContextCID)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_MAKE_CALL_CID, OnMenuContextCID)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ADD_CID, OnMenuContextCID)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_COPY_CID, OnMenuContextCID)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_ALLOC_CANCEL, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_ALLOC, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_ALLOC_OTHER, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_CALL, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_POS, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW, OnMenuContextRider)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_PHONE_CUR_CALL, OnMenuCall)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_PHONE_CUR_REMOVE, OnMenuCall)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_PHONE_SEND_SMS, OnMenuCall)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_PHONE_ALLOCATE_SEND_SMS, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_SELECT, ID_MENU_PHONE_SELECT + 100, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_CALL, ID_MENU_PHONE_CALL + 100, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_REMOVE, ID_MENU_PHONE_REMOVE + 100, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_SET_NUMBER1, ID_MENU_PHONE_SET_NUMBER1 + 100, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_SET_NUMBER2, ID_MENU_PHONE_SET_NUMBER2 + 100, OnMenuCall)
	ON_COMMAND_RANGE(ID_MENU_PHONE_ETC, ID_MENU_PHONE_ETC + 10, OnMenuCall)

	ON_COMMAND_RANGE(ID_MENU_PHONE_SET_SMS, ID_MENU_PHONE_SET_SMS + 10, OnMenuSetSms)

	ON_COMMAND_RANGE_SINGLE(IDC_CARGO_JABARA_CHECK, OnSpecialTrcukSelect)
	ON_COMMAND_RANGE_SINGLE(IDC_CARGO_LIFT_CHECK, OnSpecialTrcukSelect)
	ON_COMMAND_RANGE_SINGLE(IDC_CARGO_WING_BODY_CHECK, OnSpecialTrcukSelect)
	ON_COMMAND_RANGE_SINGLE(IDC_CARGO_LIFT_WING_CHECK, OnSpecialTrcukSelect)
	ON_COMMAND_RANGE_SINGLE(IDC_CARGO_FREEZER_CHECK, OnSpecialTrcukSelect)


	ON_BN_CLICKED(IDC_ORDER_MOVE_BTN, &CRcpDlg::OnBnClickedOrderMoveBtn)
	ON_BN_CLICKED(IDC_START_MOVE_BTN, &CRcpDlg::OnBnClickedStartMoveBtn)
	ON_BN_CLICKED(IDC_DEST_MOVE_BTN, &CRcpDlg::OnBnClickedDestMoveBtn)
	ON_BN_CLICKED(IDC_PAY_TYPE_PRE_BTN, &CRcpDlg::OnBnClickedPayTypePreBtn)
	ON_BN_CLICKED(IDC_PAY_TYPE_AFTER_BTN, &CRcpDlg::OnBnClickedPayTypeAfterBtn)
	ON_BN_CLICKED(IDC_PAY_TYPE_CREDIT_BTN, &CRcpDlg::OnBnClickedPayTypeCreditBtn)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN, &CRcpDlg::OnBnClickedCarTypeBtn)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN2, &CRcpDlg::OnBnClickedCarTypeBtn2)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN3, &CRcpDlg::OnBnClickedCarTypeBtn3)
	ON_NOTIFY(NM_CLICK, IDC_ORDER_LOG_LIST, OnNMClickLogList)
	ON_CBN_SELCHANGE(IDC_CHARGE_TYPE_COMBO, OnCbnSelchangeChargeTypeBombo)
	ON_CBN_SELCHANGE(IDC_CAR_TYPE_COMBO, &CRcpDlg::OnCbnSelchangeCarTypeCombo)
	ON_CBN_SELCHANGE(IDC_PAY_TYPE_COMBO, &CRcpDlg::OnCbnSelchangePayTypeCombo)
	ON_CBN_SELCHANGE(IDC_DEL_TYPE_COMBO, &CRcpDlg::OnCbnSelchangeDelTypeCombo)
	ON_CBN_SELCHANGE(IDC_WAY_TYPE_COMBO, &CRcpDlg::OnCbnSelchangeWayTypeCombo)
	ON_CBN_SELCHANGE(IDC_RUN_TYPE_COMBO, &CRcpDlg::OnCbnSelchangeRunTypeCombo)	
	ON_BN_CLICKED(IDC_CONTEXT_CHARGE_BTN, &CRcpDlg::OnBnClickedContextChargeBtn)
	ON_BN_CLICKED(IDC_RESERVE_BTN, &CRcpDlg::OnBnClickedReserveBtn)
	ON_BN_CLICKED(IDC_CID_MENU_BTN, &CRcpDlg::OnBnClickedCidMenuBtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RIDER_MENU_BTN, &CRcpDlg::OnBnClickedRiderMenuBtn)
	ON_MESSAGE(WM_GET_ALLOCATE_RIDER, OnGetAllocateRider)
	ON_BN_CLICKED(IDC_ETC_BTN, &CRcpDlg::OnBnClickedEtcBtn)
	ON_BN_CLICKED(IDC_CONTEXT_MILEAGE_BTN, &CRcpDlg::OnBnClickedContextMileageBtn)
	ON_BN_CLICKED(IDC_ROUTE_MENU_BTN, &CRcpDlg::OnBnClickedRouteMenuBtn)
	ON_BN_CLICKED(IDC_RCP_COPY_BTN, &CRcpDlg::OnBnClickedRcpCopyBtn)
	ON_EN_CHANGE(IDC_CHARGE_TRANS_EDIT, &CRcpDlg::OnEnChangeChargeTransEdit)
	ON_BN_CLICKED(IDC_HISTORY_BTN, &CRcpDlg::OnBnClickedHistoryBtn)
	ON_BN_CLICKED(IDC_ITEM_MENU_BTN, &CRcpDlg::OnBnClickedItemMenuBtn)
	ON_BN_CLICKED(IDC_STATE_MENU_BTN, &CRcpDlg::OnBnClickedStateMenuBtn)
	ON_BN_CLICKED(IDC_ORDER_PHONE_BTN, &CRcpDlg::OnBnClickedOrderPhoneBtn)
	ON_BN_CLICKED(IDC_ORDER_PHONE_BTN2, &CRcpDlg::OnBnClickedOrderPhoneBtn2)
	ON_BN_CLICKED(IDC_START_PHONE_BTN, &CRcpDlg::OnBnClickedStartPhoneBtn)
	ON_BN_CLICKED(IDC_START_PHONE_BTN2, &CRcpDlg::OnBnClickedStartPhoneBtn2)
	ON_BN_CLICKED(IDC_DEST_PHONE_BTN, &CRcpDlg::OnBnClickedDestPhoneBtn)
	ON_BN_CLICKED(IDC_DEST_PHONE_BTN2, &CRcpDlg::OnBnClickedDestPhoneBtn2)
	ON_BN_CLICKED(IDC_EDIT_ORDER_CHECK, &CRcpDlg::OnBnClickedEditOrderCheck)
	ON_BN_CLICKED(IDC_EDIT_START_CHECK, &CRcpDlg::OnBnClickedEditStartCheck)
	ON_BN_CLICKED(IDC_EDIT_DEST_CHECK, &CRcpDlg::OnBnClickedEditDestCheck)
	ON_EN_SETFOCUS(IDC_CHARGE_BASIC_EDIT, &CRcpDlg::OnEnSetfocusChargeBasicEdit)
	ON_BN_CLICKED(IDC_SAVE_CHARGE_CHECK, &CRcpDlg::OnBnClickedSaveChargeCheck)
	ON_BN_CLICKED(IDC_FOOD_ORDER_CHECK, &CRcpDlg::OnBnClickedFoodOrderCheck)
	ON_EN_SETFOCUS(IDC_START_DEPART_EDIT, &CRcpDlg::OnEnSetfocusStartDepartEdit)
	ON_WM_KILLFOCUS()
	ON_EN_SETFOCUS(IDC_ORDER_DEPART_EDIT, &CRcpDlg::OnEnSetfocusOrderDepartEdit)
	ON_EN_SETFOCUS(IDC_DEST_DEPART_EDIT, &CRcpDlg::OnEnSetfocusDestDepartEdit)
	ON_EN_KILLFOCUS(IDC_ORDER_DEPART_EDIT, &CRcpDlg::OnEnKillfocusOrderDepartEdit)
	ON_EN_KILLFOCUS(IDC_START_DEPART_EDIT, &CRcpDlg::OnEnKillfocusStartDepartEdit)
	ON_EN_KILLFOCUS(IDC_DEST_DEPART_EDIT, &CRcpDlg::OnEnKillfocusDestDepartEdit)
	ON_STN_CLICKED(IDC_RESERVE_DISPLAY_STATIC, &CRcpDlg::OnStnClickedReserveDisplayStatic)
	ON_BN_CLICKED(IDC_SHOW_ROUTE_BTN, &CRcpDlg::OnBnClickedShowRouteBtn)
	ON_BN_CLICKED(IDC_ETC_MENU_BTN1, &CRcpDlg::OnBnClickedEtcMenuBtn1)
	ON_BN_CLICKED(IDC_ETC_MENU_BTN2, &CRcpDlg::OnBnClickedEtcMenuBtn2)
	ON_STN_CLICKED(IDC_ORDER_ADDRESS_STATIC, &CRcpDlg::OnStnClickedOrderAddressStatic)
	ON_STN_CLICKED(IDC_START_ADDRESS_STATIC, &CRcpDlg::OnStnClickedStartAddressStatic)
	ON_STN_CLICKED(IDC_DEST_ADDRESS_STATIC, &CRcpDlg::OnStnClickedDestAddressStatic)
	ON_EN_KILLFOCUS(IDC_ORDER_ADDRESS_EDIT, &CRcpDlg::OnEnKillfocusOrderAddressEdit)
	ON_EN_KILLFOCUS(IDC_START_ADDRESS_EDIT, &CRcpDlg::OnEnKillfocusStartAddressEdit)
	ON_EN_KILLFOCUS(IDC_DEST_ADDRESS_EDIT, &CRcpDlg::OnEnKillfocusDestAddressEdit)
	ON_EN_KILLFOCUS(IDC_CHARGE_DRIVING_EDIT, &CRcpDlg::OnEnKillfocusChargeDrivingEdit)
	ON_BN_CLICKED(IDC_PAY_TYPE_ONLINE_BTN, &CRcpDlg::OnBnClickedPayTypeOnlineBtn)
	ON_EN_CHANGE(IDC_CHARGE_DRIVING_EDIT, &CRcpDlg::OnEnChangeChargeDrivingEdit)
	ON_BN_CLICKED(IDC_NOT_SEND_COMPLETE_SMS_CHECK, &CRcpDlg::OnBnClickedNotSendCompleteSmsCheck)
	ON_BN_CLICKED(ID_SHOW_ORDER_LOG_BTN, &CRcpDlg::OnBnClickedShowOrderLogBtn)
	ON_BN_CLICKED(IDC_SMS_BTN, &CRcpDlg::OnBnClickedSmsBtn)
	ON_BN_CLICKED(IDC_AUTO_SHARE_ORDER_CHECK, &CRcpDlg::OnBnClickedAutoShareOrderCheck)
	ON_BN_CLICKED(IDC_UPDATE_AND_NEW_BTN, &CRcpDlg::OnBnClickedUpdateAndNewBtn)
	ON_BN_CLICKED(IDC_ORDER_DEST_SAME_BTN, &CRcpDlg::OnBnClickedOrderDestSameBtn)
	ON_BN_CLICKED(IDC_ORDER_START_SAME_BTN, &CRcpDlg::OnBnClickedOrderStartSameBtn)
	ON_BN_CLICKED(IDC_ORDER_DIFFERENT_BTN, &CRcpDlg::OnBnClickedOrderDifferentBtn)
	ON_EN_CHANGE(IDC_COMMISSION_EDIT, &CRcpDlg::OnEnChangeCommissionEdit)

	ON_BN_CLICKED(IDC_CONSIGN_VIEW_BTN, &CRcpDlg::OnBnClickedConsignViewBtn)
	ON_BN_CLICKED(IDC_ZERO_INCOME_BTN, &CRcpDlg::OnBnClickedZeroIncomeBtn)	
	ON_BN_CLICKED(IDC_NICE_CARD_BTN, &CRcpDlg::OnBnClickedNiceCardBtn)
	ON_BN_CLICKED(IDC_UPDATE_CANCEL_BTN, &CRcpDlg::OnBnClickedUpdateCancelBtn)
	ON_BN_CLICKED(IDC_PAY_TYPE_ONLINE_BTN2, &CRcpDlg::OnBnClickedPayTypeOnlineBtn2)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN4, &CRcpDlg::OnBnClickedCarTypeBtn4)
	ON_BN_CLICKED(IDC_CAR_TYPE_BTN5, &CRcpDlg::OnBnClickedCarTypeBtn5)
	ON_BN_CLICKED(IDC_WAY_TYPE_BTN, &CRcpDlg::OnBnClickedWayTypeBtn)
	ON_BN_CLICKED(IDC_WAY_TYPE_BTN2, &CRcpDlg::OnBnClickedWayTypeBtn2)
	ON_BN_CLICKED(IDC_WAY_TYPE_BTN3, &CRcpDlg::OnBnClickedWayTypeBtn3)
	ON_BN_CLICKED(IDC_RUN_TYPE_BTN, &CRcpDlg::OnBnClickedRunTypeBtn)
	ON_BN_CLICKED(IDC_RUN_TYPE_BTN2, &CRcpDlg::OnBnClickedRunTypeBtn2)
	ON_BN_CLICKED(IDC_RUN_TYPE_BTN3, &CRcpDlg::OnBnClickedRunTypeBtn3)
	ON_BN_CLICKED(IDC_RUN_TYPE_BTN4, &CRcpDlg::OnBnClickedRunTypeBtn4)
	ON_BN_CLICKED(IDC_START_CLEAR_BTN, &CRcpDlg::OnBnClickedStartClearBtn)
	ON_BN_CLICKED(IDC_DEST_CLEAR_BTN, &CRcpDlg::OnBnClickedDestClearBtn)
	ON_BN_CLICKED(IDC_RIDER_SEARCH_BTN, &CRcpDlg::OnBnClickedRiderSearchBtn)
	ON_BN_CLICKED(IDC_RIDER_SMS_SEND_BTN, &CRcpDlg::OnBnClickedRiderSMSBtn)
	ON_BN_CLICKED(IDC_ORDER_CLEAR_BTN, &CRcpDlg::OnBnClickedOrderClearBtn)
	ON_BN_CLICKED(IDC_NEW_RCP_DLG_BTN, &CRcpDlg::OnBnClickedNewRcpDlgBtn)
	ON_BN_CLICKED(IDC_PRO_PER_BTN, &CRcpDlg::OnBnClickedProPerBtn)
	ON_BN_CLICKED(IDC_RUN_TYPE_BTN5, &CRcpDlg::OnBnClickedRunTypeBtn5)

	ON_COMMAND(ID_PAY_CASH, OnPayCash)
	ON_COMMAND(ID_RE_SEND_EMAIL, OnReSendEMail)

	ON_BN_CLICKED(IDC_DIRECT_DISTANCE_CHECK, &CRcpDlg::OnBnClickedDirectDistanceCheck)

	ON_EN_CHANGE(IDC_CHARGE_COMPANY_EDIT, &CRcpDlg::OnEnChangeChargeCompanyEdit)
	ON_EN_CHANGE(IDC_TNO_EDIT, &CRcpDlg::OnEnChangeTnoEdit)
	ON_BN_CLICKED(IDC_CALL_PASS_BTN, &CRcpDlg::OnBnClickedCallPassBtn)
	END_MESSAGE_MAP()

// CRcpDlg 진단입니다.

#ifdef _DEBUG
void CRcpDlg::AssertValid() const
{
	CRcpDlgBase::AssertValid();
}

void CRcpDlg::Dump(CDumpContext& dc) const
{
	CRcpDlgBase::Dump(dc);
}
#endif //_DEBUG

void CRcpDlg::Construct(BOOL bFirstInit)
{
	if(bFirstInit)
	{
		LF->LoadFromReg(CRcpDlgSetupDlg::m_info);

		m_pRcpView = NULL;
		m_pSearchPOIDlg = NULL;
		m_pHistoryDlg = NULL;
		m_pOrderProcessStateDlg = NULL;
		m_pReserveOrderDlg = NULL;
		m_pSearchManagerDlg = NULL;
		m_pCreditHistoryDlg = NULL;
		m_bRiderSmsSend = FALSE;

		m_pOrder = new CRcpPlaceInfo(this, PLACE_ORDER);
		m_pStart = new CRcpPlaceInfo(this, PLACE_START); 
		m_pDest = new CRcpPlaceInfo(this, PLACE_DEST);
		m_pCharge = new CCharge(this);

		m_pDisplayChargeInfo = new CDisplayChargeInfo(this);
		m_pOrder->SetStartDontAutoCopy(CRcpDlgSetupDlg::m_info.nStartDontAutoCopy);

		m_pOrder->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
		m_pStart->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
		m_pDest->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
	}
	else
	{
		HIDE_DLG(m_pHistoryDlg);
		INIT_SEARCH_EDIT(m_pHistoryDlg)
		HIDE_DLG(m_pOrderProcessStateDlg);
		HIDE_DLG(m_pSearchPOIDlg);
		HIDE_DLG(m_pReserveOrderDlg);
		HIDE_DLG(m_pSearchManagerDlg);
		HIDE_DLG(m_pCreditHistoryDlg);
		INIT_SEARCH_EDIT(m_pCreditHistoryDlg)
		m_pCharge->RemoveAllData();
		m_pDisplayChargeInfo->RemoveAllData();
	}

	m_bLoadInit = FALSE;
	m_bPreFoodOrder = FALSE;
	m_dtPreFoodComplete = COleDateTime::GetCurrentTime();

	m_pConsignLinkDlg = NULL;
	m_bDepositMessage = TRUE;
	m_nConsignTNo = 0;
	m_nTerminalWayID = 0;
	m_bConsignLink = FALSE;		
	m_strConBackOrderCharge = "0";
	m_strConTotalCharge = "0";
	m_sConCommissionCharge = "0";

	m_nCNoChargeDriving = 0;
	m_nCNoDiscount = 0;

	m_nCardProcess = 0;
	m_strConsignCity = "";
	m_nConsignCompany = 0;
	m_bInternet = FALSE;
	m_nLoadChargeBasic =0;
	m_bDirtyBasicCharge = FALSE;
	m_bChangeDrivingCharge = TRUE;
	m_bAllocRider = FALSE;
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_bCopyDlg = FALSE;
	m_nInitItem = -1;
	m_bTempCNo = FALSE;
	m_nTempCNo = 0;
	m_bOrderOK = FALSE;
	m_bStartOK = FALSE;
	m_bDestOK = FALSE;
	m_bCnsServerError	= FALSE;
	m_nProcessCns		= -1;
	m_nDistance = 0;
	m_bSearchCNS = FALSE;
	m_nPayType = 0;
	m_nWayType = 0;
	m_nRunType = 0;
	m_bCoupon = FALSE;
	m_strCouponCharge = "";
	m_nQueryChargeUniqueID = 0;
	m_bFlashPayEdit = FALSE;
	m_bInquiryOrder = FALSE;
	m_bNoticeOrder = FALSE;
	m_strOldRiderNo = "";
	m_strOldRiderName = "";
	m_nTransID = -1;
	m_bCreditAfterDis = FALSE;
	m_nState = 0;
	m_nDiscountType = 0;
	m_nDiscountValue = 0;
	m_nPriceGrade = 0;
	m_nWebID = 0;
	m_bScheduleOrder = FALSE;
	m_nChargeAdd = 0;
	m_nChargeDis = 0;
	m_nMileageBalance = 0;
	m_sMileageBalance = "";
	m_nLoadMileage = 0;
	m_nLoadChargeRiderAuto = 0;
	m_bNotOrderMileage = FALSE;
	m_bEditExampleDlg = FALSE;
	m_bOrderUpdated = FALSE;
	m_nOperatorID = 0;
	m_nToCallingType = CALL_TO_CUSTOMER;
	m_bTodayOrder = TRUE;
	m_nOrderSpecialMileage = 0;
	m_bOrderSpecialMileage = FALSE;
	m_nPersonMileage = 0;
	m_nModifyPoiConfirmCharge = 0;
	m_strDistanceInfo = "";
	m_nChargeMemCNo = 0;
	m_nLoadMileage = 0;
	m_dt1.SetDateTime(1900,1,1,0,0,0);
	m_strSmsPhone = "";
	m_strCNS = "";
	m_bPOIAutoCompleteOnce = FALSE;
	m_bIgnoreEnChangeEvent = FALSE;
	m_bSkipChangeDelType = FALSE;
	m_bReadyToReuse = FALSE;
	m_nDiscountRange = 0;
	m_strRiderName = "";
	m_strChargeAddOption = "";
	m_fDirectDistance = 0.0;
	m_strChargeBet = "";
	m_nRevisitCustomer = 0;
	m_nOriginalCompany = ZERO;
	m_strMileReserve = "";
	m_bInsertCidPhone = FALSE;
	m_bAllocRiderChangeTime = -1;
	m_nPreRiderAutoCharge = 0;
	m_nPreCharge = 0;
	m_bHistoryMoveDown = AfxGetApp()->GetProfileInt("HistoryDlg", "MoveDown", 0);
	m_strExtraTitle = "";
	m_pFocusControl = NULL;
	m_pCNSCheckStart = NULL;
	m_pCNSCheckDest = NULL;
	m_nReserveAfter = 0;
	m_strChargeRevision = "";
}

// CRcpDlg 메시지 처리기입니다.

BOOL CRcpDlg::OnInitDialog()
{

	CRcpDlgBase::OnInitDialog();

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	//m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	//m_tooltip.SetImageList(IDB_LIST, 16, 18, 18, RGB(0,255,255));
	m_tooltip.SetTransparency(30);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

	m_tooltip.AddTool(&m_chkFoodOrder, "");

	if(m_ci.m_nCompanyCode < 100 || m_ci.m_nShareCode5 == 9999)
		m_btnCallPass.ShowWindow(SW_SHOW);

	OnInitialUpdate();	

	return FALSE;
}


void CRcpDlg::OnInitialUpdate()
{
	if(!m_bReadyToReuse)
		InitControl();
	else
		ReInitControl();

	ReSetItemCombo();
	InitCommon();
	InitData();
	InitControlAfterGetData();	
	ChangeCargoControl();
	m_bLoadInit = TRUE;
}

void CRcpDlg::InitCommon()
{
	m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(m_pBi->bAutoShareOrder);
	m_cmbDelType.SetCurSel(ZERO);
	SetPayTypeNew(PAY_PRE);
	SetCarTypeNew(m_pBi->IsCargo() ? CAR_TRUCK : CAR_AUTO);
	m_cmbRunType.SetCurSel(ZERO);
	m_cmbWayType.SetCurSel(ZERO);
	m_BTN_NOT_SEND_COMPLETE_SMS.pButton->SetCheck(FALSE);
	m_chkSameCarTypeOnly.SetCheck(FALSE);

	if(LF->IsThisCompany("올바로"))
		m_chkSameCarTypeOnly.SetCheck(TRUE);

	m_CMB_CHARGE_TYPE.pCombo->SetCurSel(0);

	if(m_pBi->nRevisitCustomerSendDay > ZERO &&
		m_strCID.GetLength() > SIX)
	{
		SetTimer(TIMER_REVISIT_CUSTOMER, 500, NULL);
	}
}

void CRcpDlg::GetCompanyCodeForRevisitCustomer(long &nCompany, long &nLastDay, long &nCNo)
{
	CMkCommand pCmd(m_pMkDb, "select_revisit_customer_1");
	pCmd.AddParameter(m_pBi->nShareCode1);
	pCmd.AddParameter(m_pBi->nCompanyCode);
	pCmd.AddParameter(LF->GetRemoveDDDNumber(m_strCID, m_pBi->nCompanyCode));
	pCmd.AddParameter(m_pBi->nRevisitCustomerSendDay);
	CMkParameter *parCompany = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parLastDay = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *patCNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pCmd.Execute())
		return;

	parCompany->GetValue(nCompany);
	parLastDay->GetValue(nLastDay);
	patCNo->GetValue(nCNo);
}

void CRcpDlg::InitControl()
{
	MakeReserveDlg();

	LF->SetHanEngMode(this->GetSafeHwnd(), TRUE);


	m_pOrder->SetOtherPlaceInfo(m_pOrder, m_pStart, m_pDest);
	m_pStart->SetOtherPlaceInfo(m_pOrder, m_pStart, m_pDest);
	m_pDest->SetOtherPlaceInfo(m_pOrder, m_pStart, m_pDest);

	m_pOrder->SetControl(&m_edtOrder, &m_edtOrderCNo, m_EDT_ORDER_NAME.pEdit, m_EDT_ORDER_DEPART.pEdit, m_EDT_ORDER_MANAGER.pEdit, 
		&m_stcOrderAddress, NULL, &m_edtOrderDetail, &m_edtOrderMemo, m_EDT_ORDER_PHONE.pEdit, &m_edtOrderMP, 
		&m_edtOrderDong, &m_cmbDelType, &m_chkShowPhoneTypeOrder, &m_bSkipChangeDelType);
	m_pStart->SetControl(m_EDT_START.pEdit, &m_edtStartCNo, m_EDT_START_NAME.pEdit, m_EDT_START_DEPART.pEdit, m_EDT_START_MANAGER.pEdit, 
		&m_STC_START_ADDERSS.stcMarkup, &m_STC_START_ADDERSS.stcFlat, m_EDT_START_DETAIL.pEdit, NULL, m_EDT_START_PHONE.pEdit, &m_edtStartMP, 		
		m_EDT_START_DONG.pEdit, &m_cmbDelType, &m_chkShowPhoneTypeStart, &m_bSkipChangeDelType);
	m_pDest->SetControl(m_EDT_DEST.pEdit, &m_edtDestCNo, m_EDT_DEST_NAME.pEdit, m_EDT_DEST_DEPART.pEdit, m_EDT_DEST_MANAGER.pEdit, 
		&m_STC_DEST_ADDERSS.stcMarkup, &m_STC_DEST_ADDERSS.stcFlat, m_EDT_DEST_DETAIL.pEdit, NULL, m_EDT_DEST_PHONE.pEdit, &m_edtDestMP,
		m_EDT_DEST_DONG.pEdit, &m_cmbDelType, &m_chkShowPhoneTypeDest, &m_bSkipChangeDelType);

	m_pCharge->RemoveAllData();
	m_pDisplayChargeInfo->RemoveAllData();

	//choe
	LF->MakeCarTypeCombo(&m_cmbCarType);

	// 콤보박스 테마로인해 OnCtlColor 안먹히는 현상 수정
	SetWindowTheme(GetDlgItem(IDC_BRANCH_COMBO)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(m_cmbPayType.m_hWnd, L"", L"");
	SetWindowTheme(m_cmbWayType.m_hWnd, L"", L"");
	SetWindowTheme(m_cmbCarType.m_hWnd, L"", L"");
	SetWindowTheme(m_cmbRunType.m_hWnd, L"", L"");
	

	DisplayReserveInfo();

	m_pDelayOrderPane = LU->m_pDelayOrderPane;

	m_edtOrder.SetMyFont("돋움", 13, FW_NORMAL);
	m_edtOrder.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "의뢰지검색F1");
	m_edtOrder.SetUserTextColorNoFocusHasText(RGB(200, 200, 200));
	m_edtOrder.SetGradientBK();

	m_edtOrderDong.SetMyFont("맑은 고딕", 18, FW_NORMAL);
	m_edtOrderDong.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "단말기표시");

	m_edtProperCharge1.SetMyFont("맑은 고딕", 18, FW_NORMAL);
	m_edtProperCharge1.SetUserOption(RGB(0, 0, 0), RGB(255, 230, 255), "");
	m_edtProperCharge2.SetMyFont("맑은 고딕", 18, FW_NORMAL);
	m_edtProperCharge2.SetUserOption(RGB(0, 0, 0), RGB(255, 230, 255), "");
		

	if(IsInsungDlg())
	{
		/*
		m_EDT_START.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START.edtFlatEditInsung.SetHelpText("*검색", RGB(255, 0, 0));
		m_EDT_START_NAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_NAME.edtFlatEditInsung.SetHelpText(" *출발지고객명", crLightRed, DT_LEFT);
		m_EDT_START_NAME.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
		m_EDT_START_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_DEPART.edtFlatEditInsung.SetHelpText(" 부서명", crLightBlue, DT_LEFT);
		m_EDT_START_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_MANAGER.edtFlatEditInsung.SetHelpText(" 담당/직위명", crLightBlue, DT_LEFT);
		m_EDT_START_PHONE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_PHONE.edtFlatEditInsung.SetHelpText(" *전화번호", crLightRed, DT_LEFT);
		m_EDT_START_PHONE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));

		m_EDT_START_DONG.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_DONG.edtFlatEditInsung.SetHelpText(" *출발동명", crLightRed, DT_LEFT);

		m_EDT_START_DETAIL.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_START_DETAIL.edtFlatEditInsung.SetHelpText("출발지상세위치", crLightBlue);

		m_EDT_DEST.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST.edtFlatEditInsung.SetHelpText("*검색", RGB(255, 0, 0));
 
		m_EDT_DEST_NAME.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_NAME.edtFlatEditInsung.SetHelpText(" *도착지고객명", crLightRed, DT_LEFT);
		m_EDT_DEST_NAME.edtFlatEditInsung.SetColor(RGB(0, 0, 255));
		m_EDT_DEST_DEPART.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_DEPART.edtFlatEditInsung.SetHelpText(" 부서명", crLightBlue, DT_LEFT);
		m_EDT_DEST_MANAGER.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_MANAGER.edtFlatEditInsung.SetHelpText(" 담당/직위명", crLightBlue, DT_LEFT);
		m_EDT_DEST_PHONE.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_PHONE.edtFlatEditInsung.SetHelpText(" *전화번호", crLightRed, DT_LEFT);
		m_EDT_DEST_PHONE.edtFlatEditInsung.SetColor(RGB(0, 0, 255));

		m_EDT_DEST_DONG.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_DONG.edtFlatEditInsung.SetHelpText(" *도착동명", crLightRed, DT_LEFT);

		m_EDT_DEST_DETAIL.edtFlatEditInsung.SetBorderColor(RGB(255, 255, 255));
		m_EDT_DEST_DETAIL.edtFlatEditInsung.SetHelpText("도착지상세위치", crLightBlue);

		CRcpInsungdlg 에서 초기화
		*/
	}
	else
	{
		m_EDT_CID.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_CID.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 220), "발신전화번호");
		m_EDT_CID.edtFlatEdit2.SetGradientBK();

		m_EDT_ORDER_NAME.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_ORDER_NAME.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "F4키 이동");
		m_EDT_ORDER_PHONE.edtFlatEdit2.SetMyFont("맑은 고딕", 19, FW_NORMAL);
		m_EDT_START.edtFlatEdit2.SetMyFont("돋움", 13, FW_NORMAL);
		m_EDT_START.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "출발지검색F2");
		m_EDT_START.edtFlatEdit2.SetUserTextColorNoFocusHasText(RGB(200, 200, 200));
		m_EDT_START.edtFlatEdit2.SetGradientBK();
		m_EDT_START_NAME.edtFlatEdit2.SetMyFont("맑은 고딕", 19, FW_NORMAL);
		m_EDT_START_NAME.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "F5키 이동");
		
		m_EDT_START_PHONE.edtFlatEdit2.SetMyFont("맑은 고딕", 19, FW_NORMAL);
		m_EDT_START_DONG.edtFlatEdit2.SetMyFont("맑은 고딕", 18, FW_BOLD);
		m_EDT_START_DONG.edtFlatEdit2.SetUserOption(RGB(0, 150, 0), RGB(255, 255, 255), "단말기표시");
		m_EDT_START_DETAIL.edtFlatEdit2.SetMyFont("맑은 고딕", 15, FW_NORMAL);

		m_EDT_DEST.edtFlatEdit2.SetMyFont("돋움", 13, FW_NORMAL);
		m_EDT_DEST.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "도착지검색F3");
		m_EDT_DEST.edtFlatEdit2.SetUserTextColorNoFocusHasText(RGB(200, 200, 200));
		m_EDT_DEST.edtFlatEdit2.SetGradientBK();

		m_EDT_DEST_NAME.edtFlatEdit2.SetMyFont("맑은 고딕", 19, FW_NORMAL);
		m_EDT_DEST_NAME.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "F6키 이동");
		m_EDT_DEST_PHONE.edtFlatEdit2.SetMyFont("맑은 고딕", 19, FW_NORMAL);

		m_EDT_DEST_DONG.edtFlatEdit2.SetMyFont("맑은 고딕", 18, FW_BOLD);
		m_EDT_DEST_DONG.edtFlatEdit2.SetUserOption(RGB(0, 150, 0), RGB(255, 255, 255), "단말기표시");
		m_EDT_DEST_DETAIL.edtFlatEdit2.SetMyFont("맑은 고딕", 15, FW_NORMAL);

		m_EDT_CHARGE_ADD.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_CHARGE_BASIC.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_CHARGE_TRANS.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_CHARGE_DIS.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_CHARGE_SUM.edtFlatEdit2.SetMyFont("맑은 고딕", 20, FW_BOLD);
		m_EDT_CHARGE_SUM.edtFlatEdit2.SetUserOption(RGB(255, 0, 0), RGB(200, 255, 155)); 
		m_EDT_CHARGE_DRIVING.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_BOLD);
		m_EDT_CHARGE_DRIVING.edtFlatEdit2.SetUserOption(RGB(0, 0, 255), RGB(255, 255, 255));
		m_EDT_CHARGE_DRIVING.edtFlatEdit2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EDT_ETC.edtFlatEdit2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "적요");

		m_STC_START_ADDERSS.stcMarkup.SetDefaultFont(m_FontManager.GetLogFont("맑은 고딕", 15));
		m_STC_DEST_ADDERSS.stcMarkup.SetDefaultFont(m_FontManager.GetLogFont("맑은 고딕", 15));
	}

	m_edtSmsPhone.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtSmsPhone.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "SMS전송번호");

	m_stcOrderAddress.SetDefaultFont(m_FontManager.GetLogFont("맑은 고딕", 15));

	m_edtOrderMemo.SetMyFont("맑은 고딕", 15, FW_NORMAL);
	m_edtOrderMP.SetMyFont("맑은 고딕", 19, FW_NORMAL);
	m_edtStartMP.SetMyFont("맑은 고딕", 19, FW_NORMAL);


	m_edtDestMP.SetMyFont("맑은 고딕", 19, FW_NORMAL);
	m_edtSmsPhone.SetMyFont("맑은 고딕", 17, FW_NORMAL);

	m_edtChargeSumTotal.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtConTotalCharge.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtDeposit.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtValueAdd.SetMyFont("맑은 고딕", 20, FW_NORMAL);
	//m_btnConsignView.Set.SetMyFont("맑은 고딕", 22, FW_BOLD);

	m_edtChargeReturn.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtChargeReturn.SetUserOption(RGB(0, 150, 0), RGB(255, 255, 255)); 
	m_edtChargeRevision.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_edtChargeRevision.SetUserOption(RGB(0, 150, 0), RGB(255, 255, 255)); 


	m_edtChargeSumTotal.SetUserOption(RGB(255, 0, 0), RGB(200, 255, 155)); 
	m_edtConTotalCharge.SetUserOption(RGB(255, 0, 0), RGB(200, 255, 155)); 
	//m_btnConsignView.SetUserOption(RGB(0, 0, 0), RGB(255, 0, 0)); 

	m_edtAutoCharge.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	
	//m_edtAutoCharge.SetMyFont("맑은고딕", 15, FW_BOLD);
	//m_edtAutoCharge.SetUserOption(RGB(0, 0, 0), RGB(255, 204, 193), "마일사용");

	m_edtIntercallEtc.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "인터콜적요(수정가능)");

	m_lstOrderLog.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstOrderLog.InsertColumn(0, "시각", LVCFMT_LEFT, 40);
	m_lstOrderLog.InsertColumn(1, "상태", LVCFMT_LEFT, 40);
	m_lstOrderLog.InsertColumn(2, "접수자", LVCFMT_LEFT, 45);
	m_lstOrderLog.InsertColumn(3, "기타", LVCFMT_LEFT, 170);
	m_lstOrderLog.ShowHeader(FALSE);
	//m_lstOrderLog.GetPaintManager()->SetTextFont(lfLogFont);
	m_lstOrderLog.GetPaintManager()->m_strNoItems = "오더로그가 없습니다";
	m_lstOrderLog.GetPaintManager()->m_bHideSelection = TRUE;

	m_stcOrderAddress.ModifyStyle(0, SS_NOTIFY);
	m_STC_START_ADDERSS.stcMarkup.ModifyStyle(0, SS_NOTIFY);
	m_STC_DEST_ADDERSS.stcMarkup.ModifyStyle(0, SS_NOTIFY);
	m_chkAbleAllocLoadIns.SetCheck(m_pBi->bOnlyLoadInsRider);
	
	SetTimer(HIDE_SEARCH_DONG_LIST_TIMER, 100, NULL);

	LU->MakeAllocateGroupCombo(m_CMB_ALLOC_GROUP.pCombo);
	LU->GetRcpDlgMap(this, FALSE);
	LU->GetSimpleMap(FALSE);

	if(!m_bRiderSmsSend)
		m_btnRiderSmsSend.SetWindowText("타사기사검색");

	if(LF->IsThisCompany("사천퀵", m_pBi->nCompanyCode))
		SetGrade(-100); //노란색 

}


void CRcpDlg::InitData()
{
	long nTNo = m_nInitItem;

	m_pCharge->InitBranchInfo(this, m_pBi);
	if(nTNo < 0)
	{
		if(m_pBi->bEtcAuto)
			m_EDT_ETC.pEdit->SetWindowText(m_pBi->strEtcAuto);

		m_CMB_CHARGE_TYPE.pCombo->SetCurSel(0);
		SetTimer(TIMER_FOR_CURRENT_TIME, 1000 , NULL);
		return;	//신규
	}

	//CRcpView m_nInitItem
	
	long nItem = m_pRcpView->GetItemRowFromTNo(m_nInitItem);
	
	BOOL bTodayOrder = m_pRcpView->GetItemTodayOrder(nItem);
	long nOrderCNo = m_pRcpView->GetItemCNo(nItem);
		

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_row_detail_smartQ_23");

	if(m_strYear != "")
		pCmd.SetMkCommand(m_pMkDb, "select_dorder_row_detail_smartSQ_by_" + m_strYear);

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parMileageBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parMileagePersonType = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parMileagePerson = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_bScheduleOrder);
	if(m_strYear == "")
	{
		pCmd.AddParameter(m_bConsignLink);
		pCmd.AddParameter(nOrderCNo);
	}
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.IsEOF() || parRet->GetLong() == 0) {
		MessageBox("해당 데이터가 DB에 존재하지 않습니다.", "확인", MB_ICONERROR);
		pRs.Close();
		return;
	}

	char buffer[20];
	long nDistanceKM, nReserveReleaseMin, nCompany, nConsignTNo, nDiscountType, nDiscount, nChargeLogi;
	long nChargeAdd, nChargeBasic, nChargeTrans, nChargeDis, nChargeSum, nDeposit, nCouponCharge, nChargeDriving;
	long nAllocateGroup, nBackOrderChargeSum, nConsignCommission = 0;
	long nOrderPosX, nOrderPosY, nStartPosX, nStartPosY, nDestPosX, nDestPosY;
	BOOL bCoupon;
	long nUseCount, nCancelCount, nValueAdd;
	COleDateTime dtRegister, dtLastUse, dtReserve;
	CString strUserID;
	long nTransOrder, nChargeType, nReserveAfter;
	CString strOrderName, strOrderPhone, strOrderMP, strOrderDepart, strOrderManager, strOrderAddress;
	CString strOrderDetail, strOrderMemo, strOrderDong;
	long nOCNo, nOID, nOGNo, nOrderDongID;
	BOOL bOrderHasDetailPos, bOCredit;
	COleDateTime dtDBCur;
	long nOTelID, nSTelID, nDTelID, nConsignRate, nChargeReturn;
	long nShowPhoneTypeOrder, nShowPhoneTypeStart, nShowPhoneTypeDest, nChargeCompany, nChargeRevision;
	BOOL bAbleAllocLoadIns;

	//if(m_strYear.IsEmpty())	//백업오더테이블에 아래 컬럼이 없음 by mksong (2011-04-18 오전 11:07)
	//{ //초기화 안한 에러 컬럼에 추가함
		pRs.GetFieldValue("nOTelID", nOTelID);
		pRs.GetFieldValue("nSTelID", nSTelID);
		pRs.GetFieldValue("nDTelID", nDTelID);
	//}

	pRs.GetFieldValue("bTodayOrder", m_bTodayOrder);
	pRs.GetFieldValue("bTempCNo", m_bTempCNo);
	pRs.GetFieldValue("sWName", m_strWName);
	pRs.GetFieldValue("nState", m_nState);
	pRs.GetFieldValue("dt1", m_dtRcpTime);	
	pRs.GetFieldValue("dtCur", dtDBCur);
	pRs.GetFieldValue("dtReserve", dtReserve);
	pRs.GetFieldValue("nCompany", nCompany);

	pRs.GetFieldValue("nOCNo", nOCNo);
	pRs.GetFieldValue("nOID", nOID); 
	pRs.GetFieldValue("nOGNo", nOGNo);
	pRs.GetFieldValue("sOName", strOrderName);
	pRs.GetFieldValue("sOPhone", strOrderPhone);
	pRs.GetFieldValue("sOMobile", strOrderMP);
	pRs.GetFieldValue("sODepart", strOrderDepart);
	pRs.GetFieldValue("sOManager", strOrderManager);
	pRs.GetFieldValue("sOAddress", strOrderAddress);
	pRs.GetFieldValue("sODetail", strOrderDetail);
	pRs.GetFieldValue("sOMemo", strOrderMemo);
	pRs.GetFieldValue("sODong", strOrderDong);
	pRs.GetFieldValue("nOrderPosX", nOrderPosX);
	pRs.GetFieldValue("nOrderPosY", nOrderPosY);
	pRs.GetFieldValue("sUserID", strUserID);
	pRs.GetFieldValue("nOrderDongID", nOrderDongID);
	pRs.GetFieldValue("bOrderHasDetailPos", bOrderHasDetailPos);
	pRs.GetFieldValue("bOCredit", bOCredit);
	pRs.GetFieldValue("nMemCharge", m_nChargeMemCNo);  // 
	pRs.GetFieldValue("sSmsNumber", m_strSmsPhone);
	pRs.GetFieldValue("nUseCount", nUseCount);
	pRs.GetFieldValue("nShowPhoneTypeOrder", nShowPhoneTypeOrder);

	if(m_pBi->bNotMemberCharge)
		m_nChargeMemCNo = 0; // 개별요금 미사용업체


	m_pOrder->SetData(nOrderDongID, nOrderPosX, nOrderPosY, strOrderDepart, strOrderManager, 
		strOrderPhone, strOrderDetail, nOCNo, nOID, strUserID, nOGNo, strOrderMemo, strOrderMP, 
		strOrderDong, strOrderName, bOrderHasDetailPos, strOrderAddress, 
		nOTelID, bOCredit, nUseCount, 0, 0, nShowPhoneTypeOrder, m_bTempCNo, TRUE);


	//m_pOrder->SetPrePoiFromNowPoi();
	//m_edtSms.SetWindowText(m_strSmsNumber);


	m_strTempCompany = strOrderName;
	m_strTempDong = strOrderDong;
	m_strTempTel = strOrderPhone;
	m_strTempDepart = strOrderDepart;
	m_strTempName = strOrderManager;
	m_strTempLocation = strOrderDetail;

	long nSCNo, nSID, nStartDongID, nStartRealDongID, nSGNo;
	CString strStartName, strStartPhone, strStartMP, strStartDepart, strStartManager, strStartAddress;
	CString strStartDetail, strStartDong;
	BOOL bStartHasDetailPos, bSCredit;

	pRs.GetFieldValue("nSCNo", nSCNo);
	pRs.GetFieldValue("nSID", nSID); 
	pRs.GetFieldValue("nSGNo", nSGNo);
	pRs.GetFieldValue("sSName", strStartName);
	pRs.GetFieldValue("sSPhone", strStartPhone);
	pRs.GetFieldValue("sSMobile", strStartMP);
	pRs.GetFieldValue("sSDepart", strStartDepart);
	pRs.GetFieldValue("sSManager", strStartManager);
	pRs.GetFieldValue("sSAddress", strStartAddress);
	pRs.GetFieldValue("sSDetail", strStartDetail);
	pRs.GetFieldValue("sSDong", strStartDong); 
	pRs.GetFieldValue("nStartPosX", nStartPosX);
	pRs.GetFieldValue("nStartPosY", nStartPosY);
	pRs.GetFieldValue("nStartDongID", nStartDongID);
	pRs.GetFieldValue("nStartRealDongID", nStartRealDongID);
	pRs.GetFieldValue("bStartHasDetailPos", bStartHasDetailPos);
	pRs.GetFieldValue("bSCredit", bSCredit);
	pRs.GetFieldValue("nCreditCardType", m_nCardProcess);
	pRs.GetFieldValue("sExtraTitle", m_strExtraTitle);
	pRs.GetFieldValue("nShowPhoneTypeStart", nShowPhoneTypeStart);
	
	if(nSCNo <= ZERO && strStartName == strStartDong)
		strStartName = "";

	//인터콜에서 접수할때, nStartDongID/nDestDongID가 정상적으로 안들어오는 경우가 있음, 인터콜을 수정해야함
	m_pStart->SetData(nStartDongID == 0 || m_nState == STATE_INTERNET ? nStartRealDongID : nStartDongID, 
		nStartPosX, nStartPosY, strStartDepart, strStartManager, 
		strStartPhone, strStartDetail, nSCNo, nSID, nOCNo == nSCNo ? strUserID : "", nSGNo, "", strStartMP, 
		strStartDong, strStartName, bStartHasDetailPos, strStartAddress, 
		nSTelID, bSCredit, 0, 0, 0, nShowPhoneTypeStart);


	m_pStart->SetPrePoiFromNowPoi();

	long nDCNo, nDID, nDestDongID, nDestRealDongID, nDGNo, nCarType;
	CString strDestName, strDestPhone, strDestMP, strDestDepart, strDestManager, strDestAddress;
	CString strDestDetail, strDestDong;
	BOOL bDestHasDetailPos, bDCredit, bNotSendCompleteSms;
	BOOL bAutoShareOrder, bSameCarTypeOnly;
	BOOL bClientShare;
	long nCustomerGrade, nCustomerColor, nMemoColor, special_truck_type;

	pRs.GetFieldValue("nDCNo", nDCNo);
	pRs.GetFieldValue("nDID", nDID); 
	pRs.GetFieldValue("nDGNo", nDGNo);
	pRs.GetFieldValue("sDName", strDestName);
	pRs.GetFieldValue("sDPhone", strDestPhone);
	pRs.GetFieldValue("sDMobile", strDestMP);
	pRs.GetFieldValue("sDDepart", strDestDepart);
	pRs.GetFieldValue("sDManager", strDestManager);
	pRs.GetFieldValue("sDAddress", strDestAddress);
	pRs.GetFieldValue("sDDetail", strDestDetail);
	pRs.GetFieldValue("sDDong", strDestDong);
	pRs.GetFieldValue("nDestPosX", nDestPosX);
	pRs.GetFieldValue("nDestPosY", nDestPosY);
	pRs.GetFieldValue("nDestDongID", nDestDongID);
	pRs.GetFieldValue("nDestRealDongID", nDestRealDongID);
	pRs.GetFieldValue("bDestHasDetailPos", bDestHasDetailPos);
	pRs.GetFieldValue("bDCredit", bDCredit);
	pRs.GetFieldValue("nShowPhoneTypeDest", nShowPhoneTypeDest);

	//if(nDCNo <= 0)//지명으로 입력된경우 매니져2008과의 호환성땜시->매니저2008호환성이제없음 //by mksong (2011-03-22 오후 7:39)
	//	strDestName = "";

	m_pDest->SetData(nDestDongID == 0 || m_nState == STATE_INTERNET ? nDestRealDongID : nDestDongID, 
		nDestPosX, nDestPosY, strDestDepart, strDestManager, 
		strDestPhone, strDestDetail, nDCNo, nDID, nOCNo == nDCNo ? strUserID : "", nDGNo, "", strDestMP, 
		strDestDong, strDestName, bDestHasDetailPos, strDestAddress, 
		nDTelID, bDCredit, 0, 0, 0, nShowPhoneTypeDest);

	m_pDest->SetPrePoiFromNowPoi();

	pRs.GetFieldValue("sEtc", m_strEtc);
	pRs.GetFieldValue("nReserveReleaseMin", nReserveReleaseMin);
	//	pRs.GetFieldValue("nFinalSMSSend", m_bFinalSendSMS);
	pRs.GetFieldValue("sItemType", m_strItemType);
	pRs.GetFieldValue("nPayType", m_nPayType);
	pRs.GetFieldValue("nCarType", nCarType);
	pRs.GetFieldValue("nWayType", m_nWayType);
	pRs.GetFieldValue("nRunType", m_nRunType);

	pRs.GetFieldValue("nChargeAdd", nChargeAdd );
	pRs.GetFieldValue("nChargeBasic", nChargeBasic);
	pRs.GetFieldValue("nChargeTrans", nChargeTrans);
	pRs.GetFieldValue("nChargeDis", nChargeDis);
	pRs.GetFieldValue("nChargeSum", nChargeSum);
	pRs.GetFieldValue("nDeposit", nDeposit);
	pRs.GetFieldValue("nChargeDriving", nChargeDriving);
	pRs.GetFieldValue("sChargeBet", m_strChargeBet);// m_strCharbet

	pRs.GetFieldValue("nDistanceKM", nDistanceKM);

	pRs.GetFieldValue("nRiderCompany", m_nRiderCompany);
	pRs.GetFieldValue("nRNo", m_nRNo);
	pRs.GetFieldValue("sRMobile", m_strRPhone);
	pRs.GetFieldValue("sRName", m_strRiderName);
	pRs.GetFieldValue("nAllocGroup", nAllocateGroup);
	pRs.GetFieldValue("bCoupon", bCoupon);
	pRs.GetFieldValue("nCouponCharge", nCouponCharge);

	pRs.GetFieldValue("nUseCount", nUseCount);
	pRs.GetFieldValue("nCancelCount", nCancelCount);
	pRs.GetFieldValue("dtRegister", dtRegister);
	pRs.GetFieldValue("dtLastUse", dtLastUse);

	pRs.GetFieldValue("nTransOrder", nTransOrder); 
	pRs.GetFieldValue("nChargeType", nChargeType);
	pRs.GetFieldValue("nReserveAfter", nReserveAfter);
	pRs.GetFieldValue("dt0", m_dt0);
	pRs.GetFieldValue("dt1", m_dt1);
	pRs.GetFieldValue("sIntercallEtc", m_strIntercallEtc);
	pRs.GetFieldValue("nMileage", m_nLoadMileage);
	pRs.GetFieldValue("nChargeRiderAuto", m_nLoadChargeRiderAuto);

	pRs.GetFieldValue("bNotOrderMileage", m_bNotOrderMileage);
	pRs.GetFieldValue("nTax", nValueAdd);
	pRs.GetFieldValue("bOrderSpecialMileage", m_bOrderSpecialMileage);
	pRs.GetFieldValue("sChargeInfoTop", m_strChargeGeneralOption);
	pRs.GetFieldValue("sChargeInfoBottom", m_strChargeAddOption);
	pRs.GetFieldValue("sCID", m_strCID);
	pRs.GetFieldValue("bNotSendCompleteSms", bNotSendCompleteSms);
	pRs.GetFieldValue("bAutoShareOrder", bAutoShareOrder);
	pRs.GetFieldValue("bInternet", m_bInternet);
	pRs.GetFieldValue("nConsignRate", nConsignRate);
	pRs.GetFieldValue("nConsignTNo", nConsignTNo);
	pRs.GetFieldValue("nBackOrderChargeSum", nBackOrderChargeSum);
	pRs.GetFieldValue("nConsignCommission", nConsignCommission);
	pRs.GetFieldValue("nTerminalWayID", m_nTerminalWayID);
	pRs.GetFieldValue("sConsignCity", m_strConsignCity);
	pRs.GetFieldValue("nConsignCompany", m_nConsignCompany);
	pRs.GetFieldValue("bSameCarTypeOnly", bSameCarTypeOnly);
	pRs.GetFieldValue("nChargeReturn", nChargeReturn);
	pRs.GetFieldValue("nDiscount", nDiscount);
	pRs.GetFieldValue("nDiscountType", nDiscountType);
	pRs.GetFieldValue("nChargeLogi", nChargeLogi);
	pRs.GetFieldValue("nChargeCompany", nChargeCompany);
	pRs.GetFieldValue("bClientShare", bClientShare);

	pRs.GetFieldValue("nCustomerGrade", nCustomerGrade);
	pRs.GetFieldValue("nCustomerColor", nCustomerColor);
	pRs.GetFieldValue("nMemoColor", nMemoColor);
	pRs.GetFieldValue("bAbleAllocLoadIns", bAbleAllocLoadIns);

	pRs.GetFieldValue("bFoodOrder", m_bPreFoodOrder);
	pRs.GetFieldValue("dtFoodComplete", m_dtPreFoodComplete);
	pRs.GetFieldValue("nChargeRevision", nChargeRevision);
	pRs.GetFieldValue("nTruckType", special_truck_type);
	
	SetSpecialTruckType(special_truck_type);
	//COleDateTime dt;
	//COleDateTime dt1 = COleDateTime::GetCurrentTime();

	//pRs.GetFieldValue("dtFoodComplete", dt);
	//pRs.GetFieldValue("dtFoodComplete", dt1);

	if(m_strChargeGeneralOption.Find("직선") >= 0)
		m_chkDirectDistance.SetCheck(TRUE);

	if(m_dtPreFoodComplete.m_status == 2)
		m_dtPreFoodComplete = COleDateTime::GetCurrentTime();

	m_chkFoodOrder.SetCheck(m_bPreFoodOrder);
	m_edtOrderMemo.SetUserTextColor(nMemoColor);

	if(LF->IsThisCompany("사천퀵", m_pBi->nCompanyCode))
		SetGrade(-100); //노란색 
	else
		SetGrade(nCustomerGrade);

	m_chkAbleAllocLoadIns.SetCheck(bAbleAllocLoadIns);

	m_nPrePayType = m_nPayType;

	
	m_chkClientShareOrder.SetCheck(bClientShare);
	m_nPreCharge = nChargeSum;
	
	m_dtsDBTime = COleDateTime::GetCurrentTime() - dtDBCur;	


	m_EDT_CID.pEdit->SetWindowText(LF->IsPhoneNumber(m_strCID) ? m_strCID : "");
	m_CMB_CHARGE_TYPE.pCombo->SetCurSel(nChargeType);
	m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(bAutoShareOrder);
	m_chkSameCarTypeOnly.SetCheck(bSameCarTypeOnly);


	//if(m_bAddCall == FALSE && (m_nState != m_nPreState))


	if(m_nState != m_nPreState && !m_bConsignLink)
	{
		CString strMsg;
		strMsg = "해당 아이템의 상태가 다른 사람에 의해서 변경되었습니다.\n";
		strMsg += "확인 하시기 바랍니다.\n\n\n상태: ";
		strMsg += LF->GetStateString(m_nPreState);
		strMsg += " --> ";
		strMsg += LF->GetStateString(m_nState);
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);

		LU->m_pDelayOrderPane->m_bRcpPageRefresh = TRUE;
	}

	if(m_bAddCall == TRUE)
	{
		m_nRiderCompany = 0;
		m_nRNo = 0;
		m_strRiderName = "";
		m_strRPhone = "";
		m_nCardProcess = 0;
	}

	m_edtMileReserve.SetWindowText(LF->GetMyNumberFormat(m_nLoadMileage));

	//오더번호 접수상태 접수자 접수시간

	m_EDT_TNO.pEdit->SetWindowText(itoa(nTNo, buffer, 10));
	m_EDT_STATE.pEdit->SetWindowText(LF->GetStateString(m_nState));
	m_EDT_WNAME.pEdit->SetWindowText(m_strWName);

	if(m_nState == STATE_RESERVED || (m_nState == STATE_INTERNET && nReserveAfter > 0 ) )
	{		
		SetReserveState(dtReserve, nReserveAfter, nReserveReleaseMin);
	}
	else if(IsInsungDlg())
	{
		InitReserveState();
	}

	m_EDT_ETC.pEdit->SetWindowText(m_strEtc);

	//요금관련
	m_strChargeAdd = LF->RemoveZero(LF->GetMyNumberFormat(nChargeAdd));
	m_strChargeBasic = LF->RemoveZero(LF->GetMyNumberFormat(nChargeBasic));
	m_strChargeTrans = LF->RemoveZero(LF->GetMyNumberFormat(nChargeTrans)); 
	m_strChargeDis = LF->RemoveZero(LF->GetMyNumberFormat(nChargeDis));
	m_strChargeSum = LF->RemoveZero(LF->GetMyNumberFormat(nChargeSum));
	m_strDeposit = LF->RemoveZero(LF->GetMyNumberFormat(nDeposit));
	m_strValueAdd = LF->RemoveZero(LF->GetMyNumberFormat(nValueAdd));
	m_strChargeDriving = LF->RemoveZero(LF->GetMyNumberFormat(nChargeDriving));
	m_strChargeReturn = LF->RemoveZero(LF->GetMyNumberFormat(nChargeReturn));
	m_strChargeRevision = LF->RemoveZero(LF->GetMyNumberFormat(nChargeRevision));
	
	m_nLoadChargeBasic = nChargeBasic;  // 수정시 읽어들인 기본금액
	m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);
	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic); 
	m_EDT_CHARGE_TRANS.pEdit->SetWindowText(m_strChargeTrans);
	m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
	m_EDT_CHARGE_SUM.pEdit->SetWindowText(m_strChargeSum);
	m_edtDeposit.SetWindowText(m_strDeposit);
	m_edtValueAdd.SetWindowText(m_strValueAdd);
	m_EDT_CHARGE_DRIVING.pEdit->SetWindowText(m_strChargeDriving);
	m_edtChargeSumTotal.SetWindowText(LF->RemoveZero(LF->GetMyNumberFormat(nChargeSum + nChargeTrans)));
	m_edtChargeReturn.SetWindowText(m_strChargeReturn);
	m_edtChargeLogi.SetWindowText(LF->GetMyNumberFormat(nChargeLogi));
	m_edtChargeCompany.SetWindowText(LF->GetMyNumberFormat(nChargeCompany));
	m_edtChargeRevision.SetWindowText(LF->GetMyNumberFormat(nChargeRevision));

	SetDiscountType(nOGNo,nDiscountType, nDiscount);
	
	//경로관련
	//m_strCNS.Format("%d.%dkm", nDistanceKM/100, nDistanceKM%100);
	/*m_strCNS.Format("%d", nDistanceKM/100);

	if((nDistanceKM%100) < 10)
	m_strCNS += ".0" + (CString)itoa(nDistanceKM%100, buffer, 10) + "km";
	else
	m_strCNS += "." + (CString)itoa(nDistanceKM%100, buffer, 10) + "km";


	m_edtCNS.SetWindowText(m_strCNS);*/
	m_fDirectDistance = nDistanceKM / 100.0;

	ChangeDistance();
	m_stcChargeViaBet.SetMarkupText(m_strChargeBet);


	// 마일리지 관련

	long nMileageBalance = 0;
	parMileageBalance->GetValue(m_nMileageBalance);
	parMileagePersonType->GetValue(m_nPersonMileageType);
	parMileagePerson->GetValue(m_nPersonMileage);
	m_nPreRiderAutoCharge = m_nLoadChargeRiderAuto;
	m_strMileageAutoCharge = LF->GetStringFromLong(m_nPreRiderAutoCharge);
	
	m_edtAutoCharge.SetWindowText(m_strMileageAutoCharge);
	m_edtMileageBalance.SetWindowText(LF->GetMyNumberFormat(m_nMileageBalance));

	//기타
	m_BTN_NOT_SEND_COMPLETE_SMS.pButton->SetCheck(bNotSendCompleteSms);
	m_CMB_ALLOC_GROUP.pCombo->SetCurSel(nAllocateGroup);	
	m_strAllocateGroup = itoa(nAllocateGroup, buffer, 10);	
	m_strCouponCharge = itoa(nCouponCharge, buffer, 10);
	m_cmbCouponCharge.SetWindowText(m_strCouponCharge);
	m_edtIntercallEtc.SetWindowText(m_strIntercallEtc);
	m_edtSmsPhone.SetWindowText(LF->GetDashPhoneNumber(m_strSmsPhone));
	SetCarTypeNew(nCarType);

	if(nConsignTNo > 0)
	{
		m_nConsignTNo = nConsignTNo;
		SetConsignMode(m_nConsignTNo > 0  && !m_bConsignLink ? TRUE : FALSE);
		SetConsignViewInfo(nConsignTNo, nConsignCommission, nBackOrderChargeSum);
	}

	if(bCoupon) // BIT타입이 -1이나옴 ;
		m_bCoupon = TRUE;
	else
		m_bCoupon = FALSE;

	for(int i = 0; i < m_CMB_BRANCH.pCombo->GetCount(); i++)
		if(nCompany == m_CMB_BRANCH.pCombo->GetItemData(i))
			m_CMB_BRANCH.pCombo->SetCurSel(i);

	//수정인 경우에 지사를 변경해 준다.
	if(nCompany != m_pBi->nCompanyCode)
	{
		for(int i = 0; i < m_ba.GetCount(); i++) {
			CBranchInfo *pBi = m_ba.GetAt(i);
			if(nCompany == pBi->nCompanyCode) {
				m_pBi = pBi;
			}
		}
	}

	m_cmbItemType.SetWindowText(m_strItemType);

	if(m_nState == STATE_INTERNET)
		OnEnChangeRiderAutoChargeEdit();

	if((IsEditMode()))
		SaveCurInfo(m_stPreInfo);

	DisplayReserveInfo();
	DisplayRiderInfo();
	DisplayChargeInfo(TRUE);

	m_nReserveAfter = nReserveAfter;
	/*if(m_nPreState == STATE_INTERNET)
		GetSectionCharge();*/

}

void CRcpDlg::InitControlAfterGetData()
{
	if(_ttoi(m_strCouponCharge) < 100)
		m_cmbCouponType.SetCurSel(0);
	else
		m_cmbCouponType.SetCurSel(1);

	OnCbnSelchangeCouponTypeCombo();

	//지불 운송 급 타입
	SetPayTypeNew(m_nPayType);
	SetCarTypeNew(GetCarTypeNew());
	SetWayTypeNew(m_nWayType);
	SetRunTypeNew(m_nRunType);

	SetButtonShowHide();

	//m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(m_pBi->bAutoShareOrder);

	if(m_nState == STATE_INTERNET)
	{
		if(m_pOrder->GetCustomerID() > 0 && m_pStart->GetCustomerID() > 0 && m_pDest->GetCustomerID() > 0)
			m_EDT_ETC.pEdit->SetFocus();
		else if(m_pOrder->GetCustomerID() > 0 && m_pStart->GetCustomerID() > 0)
			m_EDT_DEST.pEdit->SetFocus();
		else if(m_pDest->GetCustomerID() > 0)
			m_EDT_START.pEdit->SetFocus();

		m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(m_pBi->bAutoShareOrder);
	}

	m_EDT_CID.pEdit->SetWindowText(m_strCID); //없으면 암됨

	if(m_nInitItem <= ZERO && m_pBi->nDefaultCharge > 0)
	{
		m_strChargeBasic.Format("%d", m_pBi->nDefaultCharge);
		m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic);
		RefreshCharge();
	}

	if(!IsEditMode())
	{ 
		if(LF->IsThisCompany("퀵오케이_적요", m_pBi->nCompanyCode))
			AddEtcOK();
	}

	//if(m_ci.m_nCompanyCode == 10)
	//	GetDlgItem(ID_CONSIGN_BTN)->ShowWindow(SW_SHOW);

	ReLocationAddCustomerBtn();

	m_btnPayType1.SetWindowText(STR_PAY_TYPE[m_pBi->nPayType1]);
	m_btnPayType2.SetWindowText(STR_PAY_TYPE[m_pBi->nPayType2]);
	m_btnPayType3.SetWindowText(STR_PAY_TYPE[m_pBi->nPayType3]);
	m_btnPayType4.SetWindowText(STR_PAY_TYPE[m_pBi->nPayType4]);
	m_btnPayType5.SetWindowText(STR_PAY_TYPE[m_pBi->nPayType5]);

	m_btnCarType1.SetWindowText(LF->GetCarTypeFromLong(m_pBi->nCarType1));
	m_btnCarType2.SetWindowText(LF->GetCarTypeFromLong(m_pBi->nCarType2));
	m_btnCarType3.SetWindowText(LF->GetCarTypeFromLong(m_pBi->nCarType3));
	m_btnCarType4.SetWindowText(LF->GetCarTypeFromLong(m_pBi->nCarType4));
	m_btnCarType5.SetWindowText(LF->GetCarTypeFromLong(m_pBi->nCarType5));

	if(!m_pBi->sEtcUserTitle1.IsEmpty())
	{
		GetDlgItem(IDC_ETC_MENU_BTN1)->SetWindowText(m_pBi->sEtcUserTitle1);
		GetDlgItem(IDC_ETC_MENU_BTN1)->SetFont(m_FontManager.GetFont("맑은 고딕", 13));
		GetDlgItem(IDC_ETC_MENU_BTN1)->ShowWindow(SW_SHOW);
	}

	if(!m_pBi->sEtcUserTitle2.IsEmpty())
	{
		GetDlgItem(IDC_ETC_MENU_BTN2)->SetWindowText(m_pBi->sEtcUserTitle2);
		GetDlgItem(IDC_ETC_MENU_BTN2)->SetFont(m_FontManager.GetFont("맑은 고딕", 13));
		GetDlgItem(IDC_ETC_MENU_BTN2)->ShowWindow(SW_SHOW);
	}


	m_cus.GetNewCustomer();

	if(IsEditMode() && !m_bEditExampleDlg)
	{
		if(LU->m_pMsg)
			LU->m_pMsg->SendEditOrderState(m_nInitItem, EOS_GET_STATE);
		SetTimer(EDIT_ORDER_STATE_TIMER, 5000, NULL);
	}
	else
	{
		if(SearchCID() == FALSE)
		{
			m_edtOrder.SetFocus();
			m_edtOrder.SetSel(0);
		}
	}

	if(!m_bAddCall)
		SetTimer(REFRESH_TIMER_ORDER_LOG, 100, NULL);

	SetTimer(HIDE_SEARCH_DONG_LIST_TIMER, 100, NULL);

	if(m_pBi->bUsageHistory)
		ShowUsageHistory(TRUE);

	ShowCreditHistory(TRUE);
	HideSubHistoryDlgExeMe();

  
	ShowCardPayInfo();

	if(m_nState == STATE_INTERNET 
			&& m_strWName != "인터넷등록(웹)"
			&& m_strWName != "인터넷등록"
			&& m_strWName != "앱접수"
			&& m_strWName != "API등록")
		GetSectionCharge(TRUE); 
 
	if(m_nState != STATE_FINISH &&
//		m_nInitItem > 0 &&
		m_bTodayOrder == TRUE) 
	{
		if(m_pBi->nUseUpChargeForNotAllocate == 1)
			m_edtChargeCompany.EnableWindow(TRUE);
		else
			m_edtChargeCompany.EnableWindow(FALSE);

		//m_edtChargeReturn.EnableWindow(TRUE);
	}
	else
	{
		m_edtChargeCompany.EnableWindow(FALSE);
		//m_edtChargeReturn.EnableWindow(FALSE);		
	}	

	if(m_nInitItem <= 0)
		m_edtChargeReturn.EnableWindow(TRUE);

	if(m_bScheduleOrder)
		m_edtChargeReturn.EnableWindow(TRUE);
	
	if( LF->IsThisCompany("전주퀵서비스") && !IsEditMode())
		m_BTN_NOT_SEND_COMPLETE_SMS.pButton->SetCheck(TRUE);

	GetDlgItem(IDC_RCP_STATIC31)->SetWindowText(m_nInitItem <= 0 ? "검색" : "번호");	
	m_EDT_TNO.pEdit->SetReadOnly(m_nInitItem <= 0 ? FALSE : TRUE);
}

void CRcpDlg::SetButtonShowHide()
{
	CRect rcNew, rcUpdateAndNew, rcWait, rcUpdate, rcWaitAfterCopy, rcUpdateCancel;

	m_btnNew.GetWindowRect(rcNew); 
	ScreenToClient(rcNew);
	m_btnWait.GetWindowRect(rcWait); 
	ScreenToClient(rcWait);
	m_btnUpdateAndNew.GetWindowRect(rcUpdateAndNew); 
	ScreenToClient(rcUpdateAndNew);
	m_btnWaitAfterCopy.GetWindowRect(rcWaitAfterCopy); 
	ScreenToClient(rcWaitAfterCopy); 
	m_btnUpdateCancel.GetWindowRect(rcUpdateCancel);
	ScreenToClient(rcUpdateCancel);

	if(IsEditMode() && m_nState != STATE_INTERNET && m_bAddCall == FALSE) 
	{
		if(m_nState == STATE_INQUIRY ||
			m_nState == STATE_OK ||
			m_nState == STATE_RESERVED ||
			m_nState == STATE_WAIT ||
			//m_nState == STATE_FINISH ||
			m_nState == STATE_CANCELED)
		{
			rcUpdate = rcNew;
			rcUpdate.bottom = rcWaitAfterCopy.bottom;

			rcUpdateAndNew = rcWait;

			if(m_nState == STATE_CANCELED)
			{
				rcUpdateAndNew.bottom = rcWaitAfterCopy.bottom;
				m_btnUpdateCancel.ShowWindow(SW_HIDE);
			}
			else
			{
				rcUpdateCancel = rcWaitAfterCopy;
				m_btnUpdateCancel.MoveWindow(rcUpdateCancel);
				m_btnUpdateCancel.ShowWindow(SW_SHOW);
			}
			
			m_btnUpdateAndNew.MoveWindow(rcUpdateAndNew);
			m_btnUpdateAndNew.ShowWindow(SW_SHOW);
		}
		else if(m_nState == STATE_ALLOCATED || m_nState ==  STATE_PICKUP || m_nState == STATE_OK_ONLY_MAN)
		{
			rcUpdate = rcNew;
			rcUpdate.bottom = rcWaitAfterCopy.bottom;
			rcUpdateCancel = rcWaitAfterCopy;
			rcUpdateCancel.top = rcWait.top;

			m_btnUpdateCancel.MoveWindow(rcUpdateCancel);
			m_btnUpdateCancel.ShowWindow(SW_SHOW);
			m_btnUpdateAndNew.ShowWindow(SW_HIDE);
		}
		else
		{
			rcUpdate.top = rcNew.top;
			rcUpdate.left = rcNew.left;
			rcUpdate.bottom = rcWaitAfterCopy.bottom;
			rcUpdate.right = rcWaitAfterCopy.right;

			m_btnUpdateAndNew.ShowWindow(SW_HIDE);
			m_btnUpdateCancel.ShowWindow(SW_HIDE);
		}


		m_btnUpdate.MoveWindow(rcUpdate);
		m_btnUpdate.ShowWindow(SW_SHOW);

		m_btnNew.ShowWindow(SW_HIDE);
		m_btnWait.ShowWindow(SW_HIDE);
		m_btnNewAfterCopy.ShowWindow(SW_HIDE);
		m_btnWaitAfterCopy.ShowWindow(SW_HIDE);

		if(!LF->IsThisCompany("올바로") &&
			!LF->IsThisCompany("로지") )
			m_btnRcpCopy.SetWindowText("기사위치");	

		m_btnInquiry.SetWindowText("오더상태");
		m_btnNotice.SetWindowText("서명확인");
	}
	else
	{
		m_btnNew.ShowWindow(SW_SHOW);
		m_btnWait.ShowWindow(SW_SHOW);
		m_btnNewAfterCopy.ShowWindow(SW_SHOW);
		m_btnWaitAfterCopy.ShowWindow(SW_SHOW);
		m_btnRcpCopy.ShowWindow(SW_SHOW);
		m_btnUpdate.ShowWindow(SW_HIDE);
		m_btnNotice.ShowWindow(SW_SHOW);
		m_btnInquiry.ShowWindow(SW_SHOW);
		m_btnUpdateAndNew.ShowWindow(SW_HIDE);
		m_btnUpdateCancel.ShowWindow(SW_HIDE);

		m_btnRcpCopy.SetWindowText("접수창복사");
		m_btnInquiry.SetWindowText("문의등록");
		m_btnNotice.SetWindowText("공지등록");
	}	
}

void CRcpDlg::ReSetItemCombo()
{
	CString strItem = AfxGetApp()->GetProfileString("CEditItemDlg", "Item", "서류봉투;소박스;중박스;대박스;컴퓨터;");

	CStringArray strArry;
	LF->GetItemCommaToArray(strItem, strArry);

	m_cmbItemType.ResetContent();
	m_cmbItemType.SetWindowText("");

	for(int i=0; i<strArry.GetCount(); i++)
		m_cmbItemType.InsertString(i, strArry.GetAt(i));
}


BOOL CRcpDlg::SearchCID()
{
	if(!m_strCID.IsEmpty()) {
		BOOL bMini = ((GetWindowLong(GetParent()->GetSafeHwnd(), GWL_STYLE) & SW_SHOWMINIMIZED) == SW_SHOWMINIMIZED);
		if(bMini) GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
		else GetParent()->ShowWindow(SW_SHOW);
		GetParent()->SetWindowPos(&wndTop,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
		m_bIgnoreEnChangeEvent = TRUE;
		m_EDT_CID.pEdit->SetWindowText(m_strCID);
		m_EDT_CID.pEdit->SetFocus();

		if(m_ci.m_bUseSearchPopup)
		{
			m_pOrder->SearchCustomer(m_strCID, ST_AUTO_DETECT, TRUE);

			//OnBnClickedOrderCustomerDlgBtn();
		}
		else
		{
			if(m_pSearchPOIDlg == NULL)
			{
				CString strText;
				m_EDT_CID.pEdit->GetWindowText(strText);
				ShowSearchPOIDlg(strText, m_pOrder, FALSE, m_EDT_START.pEdit, TRUE, 1, TYPE_PHONE);
				//ShowSearchPOIDlg(m_strCID, m_pOrder, FALSE, &m_edtStart, TRUE, 1, TYPE_PHONE);
			}

			SearchEditVK_RETURN(IDC_CID_EDIT, TRUE);  
		}

		return TRUE;
	}

	return FALSE;
}


void CRcpDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		//Order to update a tooltip for a specified window as tooltip's tool

		//Gets a ID of the window if needed
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();

		//Change a tooltip's parameters for a current window (control)
		BOOL bOutside = FALSE;
		CPoint pt = *pNotify->pt;
		CRect rect, rcCtrl, rcCol;


		if(m_dtPreFoodComplete.m_status == 2)
			m_dtPreFoodComplete = COleDateTime::GetCurrentTime();

		if(nID == IDC_FOOD_ORDER_CHECK && m_chkFoodOrder.GetCheck() && m_dtPreFoodComplete.m_status != 2)
		{
			CMakeHtmlTable htable;
			CString strCaption = "";

			COleDateTimeSpan span = m_dtPreFoodComplete - COleDateTime::GetCurrentTime();
			CString strTemp = m_dtPreFoodComplete.Format("%H시%M분");
			long nMinute = span.GetTotalMinutes() + 1;
 
			if(nMinute >= 0)
				strCaption.Format("완료시간까지 %d분 남았습니다. [%s]", nMinute, strTemp);
			else
				strCaption.Format("완료시간이 %d분 지났습니다. [%s]", (-1 * nMinute), strTemp);
				
			htable.SetTitle(strCaption);
			htable.SetTableBorder(1);
			pNotify->ti->sTooltip = htable.GetHtmlTable();
			pt = *pNotify->pt;
			pt.x += 5;
			pt.y += 20;
			*pNotify->pt = pt;
		}
		/*
		if (IDC_QUERY_CHARGE_BTN == nID || IDC_QUERY_CHARGE_BTN2 == nID)
		{
			long nCompany;
			long nRNo;
			if(IDC_QUERY_CHARGE_BTN == nID)
			{
				nCompany = AfxGetApp()->GetProfileInt("Messanger", "nFindCompany", 0);
				nRNo = AfxGetApp()->GetProfileInt("Messanger", "nFindRNo", 0);
			}
			else
			{
				nCompany = AfxGetApp()->GetProfileInt("Messanger", "nFindCompany2", 0);
				nRNo = AfxGetApp()->GetProfileInt("Messanger", "nFindRNo2", 0);
			}

			char buffer[20];
			CString str;

			if(nCompany == 0)
				str = "등록안됨";
			else
				str = m_ci.GetBranchName(nCompany) + " " + itoa(nRNo, buffer, 10) + "번 접수자";

			CMakeHtmlTable htable;
			htable.AddCol(str);
			htable.AddRow();

			htable.SetTableBorder(1);
			pNotify->ti->sTooltip = htable.GetHtmlTable();
			pt = *pNotify->pt;
			pt.x += 5;
			pt.y += 20;
			*pNotify->pt = pt;	
		}
		*/
	}
}

BOOL CRcpDlg::GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp)
{
	IMAGEINFO pImageInfo;
	imglist->GetImageInfo(0, &pImageInfo);
	int nWidth = pImageInfo.rcImage.right - pImageInfo.rcImage.left;
	int nHeight = pImageInfo.rcImage.bottom - pImageInfo.rcImage.top;

	CDC dc, *pDC = GetDC();
	HICON hIcon = imglist->ExtractIcon(nIndex);

	dc.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, nWidth, nHeight);

	COLORREF m_newclrBack;
	m_newclrBack=GetSysColor(COLOR_3DFACE);

	CBitmap* pOldBmp = dc.SelectObject(&bmp);
	CBrush brush ;

	::DrawIconEx(
		dc.GetSafeHdc(),
		0,
		0,
		hIcon,
		nWidth,
		nHeight,
		0,
		(HBRUSH)m_HandleManager.GetBrushObject(m_newclrBack),
		DI_NORMAL);

	dc.SelectObject(pOldBmp);
	dc.DeleteDC();

	// the icon is not longer needed
	::DestroyIcon(hIcon);

	ReleaseDC(pDC);
	return(TRUE);
}

long CRcpDlg::GetMatchCmb(UINT nFlag)
{
	CString strCompare;
	if(nFlag == IDC_ITEM_TYPE_COMBO)
		strCompare = m_strItemType;
	else if(nFlag == IDC_COUPON_CHARGE_COMBO)
		strCompare = m_strCouponCharge;
	else 
		return 0;


	CComboBox *pCombo = (CComboBox*)GetDlgItem(nFlag);

	for(int i=0; i<pCombo->GetCount(); i++)
	{
		CString str;
		pCombo->GetLBText(i, str);

		if(str == strCompare)
			return i;		
	}

	return 0;
}

CString CRcpDlg::GetCustomerTypeString(long nCNo, long nID, CString strUserID)
{
	char buffer[10];

	if(nCNo == 0) return "지명";
	else if(strUserID.GetLength() > 0) return strUserID;
	else if(nID <= 0) return "임시고객";
	else return ltoa(nID, buffer, 10);
}



void CRcpDlg::SetMileageData(int nAutoCharge , int nMileageValue, BOOL bRefreshCharge)
{

	long nMileage; 
	nMileage = m_mi.GetMileageVal(m_pBi->nCompanyCode, m_cmbCarType.GetCurSel(), m_nPersonMileageType, 
		m_nPersonMileage,	GetStringChargeToNumber(m_strChargeSum), GetCarTypeNew()	);

	if(nMileage > 0)
	{
		m_strMileReserve = LF->GetMyNumberFormat(nMileage);
		m_edtMileReserve.SetWindowText(m_strMileReserve);	
	}
	else
		m_edtMileReserve.SetWindowText("0");
	
}

void CRcpDlg::SaveCurInfo(ST_EDIT_HISTORY &st)
{
	long nItem = 0;
	st.item[nItem++] = m_pOrder->GetCompany();
	st.item[nItem++] = m_pOrder->GetPhone();
	st.item[nItem++] = m_pOrder->GetMP();
	st.item[nItem++] = m_pOrder->GetDepart();
	st.item[nItem++] = m_pOrder->GetManager();
	st.item[nItem++] = m_pOrder->GetAddress();
	st.item[nItem++] = m_pOrder->GetDetail();
	st.item[nItem++] = m_pOrder->GetDisplayDong();
	st.item[nItem++] = m_pOrder->GetMemo();

	st.item[nItem++] = m_pStart->GetCompany();
	st.item[nItem++] = m_pStart->GetPhone();
	st.item[nItem++] = m_pStart->GetMP();
	st.item[nItem++] = m_pStart->GetDepart();
	st.item[nItem++] = m_pStart->GetManager();
	st.item[nItem++] = m_pStart->GetAddress();
	st.item[nItem++] = m_pStart->GetDetail();
	st.item[nItem++] = m_pStart->GetDisplayDong();

	st.item[nItem++] = m_pDest->GetCompany();
	st.item[nItem++] = m_pDest->GetPhone();
	st.item[nItem++] = m_pDest->GetMP();
	st.item[nItem++] = m_pDest->GetDepart();
	st.item[nItem++] = m_pDest->GetManager();
	st.item[nItem++] = m_pDest->GetAddress();
	st.item[nItem++] = m_pDest->GetDetail();
	st.item[nItem++] = m_pDest->GetDisplayDong();

	st.item[nItem++] = m_strEtc;
	st.item[nItem++] = m_strItemType;
	st.item[nItem++] = LF->GetPayTypeFromLong(m_nPayType);
	st.item[nItem++] = LF->GetCarTypeFromLong(GetCarTypeNew() );
	st.item[nItem++] = LF->GetWayTypeFromLong(m_nWayType);
	st.item[nItem++] = LF->GetRunTypeFromLong(m_nRunType);

	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strChargeAdd));
	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strChargeBasic));
	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strChargeTrans));
	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strChargeDis));
	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strChargeSum));
	st.item[nItem++] = LF->RemoveZero(LF->GetMyNumberFormat(m_strDeposit));
	st.item[nItem++] = m_strCouponCharge;;
	//	st.item[nItem++] = m_strChargeBet;
	//	st.item[nItem++] = LF->GetDashPhoneNumber(m_strSmsNumber);

	st.nCompany = m_pBi->nCompanyCode;
	st.nRiderCompany = m_nRiderCompany;

	CString sDeposit = m_strDeposit;

	sDeposit.Replace(",", "");
	st.nDeposit = atoi(sDeposit);
	st.nPayType = GetPayTypeNew();
	st.nCarType = GetCarTypeNew();

	st.nRNo = m_nRNo;

	m_strChargeSum.Replace(",", "");
	st.nChargeSum = atoi(m_strChargeSum);
	m_strChargeTrans.Replace(",", "");
	st.nChargeTrans = atoi(m_strChargeTrans);
	st.nTNo = m_nInitItem;
}

BOOL CRcpDlg::GetCreditCount(long &nCreditCount, long &nCreditCharge)
{
	if(m_pOrder->GetCNo() < 1) return FALSE;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_credit_count");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pOrder->GetCNo());

	if(!pRs.Execute(&pCmd)) return FALSE;

	if(pRs.GetRecordCount() == 0)
		return TRUE;


	pRs.GetFieldValue("nCreditCount", nCreditCount);
	pRs.GetFieldValue("nCreditCharge", nCreditCharge);

	pRs.Close();

	return TRUE;

}


HBRUSH CRcpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CRcpDlgBase::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == this)
		return m_HandleManager.GetBrushObject(RGB(0, 0, 0), 1);

	if(pWnd->GetDlgCtrlID() == IDC_BRANCH_COMBO)
	{
		if(m_pBi->nRcpColor != 0)
			pDC->SetBkColor(m_pBi->nRcpColor);

		if(m_pBi->nRcpTextColor != 0)
			pDC->SetTextColor(m_pBi->nRcpTextColor);
	}

	switch(pWnd->GetDlgCtrlID()) 
	{ 
		case IDC_PAY_TYPE_COMBO:
		case IDC_CAR_TYPE_COMBO:
		case IDC_WAY_TYPE_COMBO:
		case IDC_RUN_TYPE_COMBO:
		case IDC_ALLOC_GROUP_COMBO:
		case IDC_CHARGE_TYPE_COMBO:
		{
			if(pWnd->GetDlgCtrlID() == IDC_PAY_TYPE_COMBO && ((CComboBox*)pWnd)->GetCurSel() == 2)
				pDC->SetBkColor(RGB(255, 180, 180));
			else if(((CComboBox*)pWnd)->GetCurSel() > 0)
				pDC->SetBkColor(RGB(200, 255, 200));	
			else 
				pDC->SetBkColor(RGB(255, 255, 255));	

			break;
		}
	}

	HBRUSH hUserBrush;
	if(pWnd != this)
		if(LF->OnMyCtlColor(pDC, pWnd, nCtlColor, hUserBrush))
			return hUserBrush;

	return hbr;
}

BOOL CRcpDlg::MakeSearchQuery(CString strSource, CString &strKeyword, UINT *pnType)
{
	if(LF->IsPhoneNumber(strSource))
	{
		if(strSource.GetAt(0) == '-')
		{
			//strSearchQuery.Format("c.nID = '%s' ", LF->GetNoneDashNumber(strSource));
			strKeyword = LF->GetNoneDashNumber(strSource);
			*pnType = ST_ID;
		}
		else
		{
			//remove some dash
			strKeyword = LF->GetNoneDashNumber(strSource);
			//remove a local DDD number, if the number is not this country...just go~
			if(strKeyword.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
				strKeyword = strKeyword.Right(strKeyword.GetLength() - m_ci.m_strDDD.GetLength());

			UINT nLen = strKeyword.GetLength();

			//if(nLen < 4 || nLen == 5 || nLen == 6)

			//if(nLen == 5 || nLen == 6)
			//{
			//	//the number must be last four number or full number except for the local DDD number
			//	LF->MsgBox(IDS_NUMBER_WRONG);
			//	return FALSE;
			//}

			*pnType = ST_PHONE;
		}
	}
	else {
		if(strSource.GetAt(0) == '-')
		{
			strSource.Replace("-", "");
			strKeyword = strSource;
			*pnType = ST_ID;
		}
		else if(strSource.GetAt(0) == '~')
		{
			strSource.Replace("~", "");
			strKeyword = strSource;
			*pnType = ST_NAME_DEPART;   // 부서_담당자 검색 '임대리%' 검색
		}
		else
		{
			strKeyword = strSource;
			*pnType = ST_COMPANY;
		}
	}

	return TRUE;
}


void CRcpDlg::OnBnClickedCloseBtn()
{
	CString strText, strText2, strText3;

	m_EDT_START_DONG.pEdit->GetWindowText(strText);
	m_EDT_DEST_DONG.pEdit->GetWindowText(strText2);
	m_edtOrderDong.GetWindowText(strText3);

	//입력한 데이터가 있는 경우, 쿼리하여 취소한다.
	if(!IsEditMode()) //수정모드가 아닌경우에
	{
		if(!strText.IsEmpty() && !strText2.IsEmpty() && !strText3.IsEmpty())
			if(IDYES != MessageBox("접수 데이터가 일부 입력된 창을 닫겠습니까?", "취소", MB_YESNO))
				return;

		if(m_pBi->bCancelToInquiry && m_EDT_CID.pEdit->GetWindowTextLength() != 0)
		{
			m_EDT_START.pEdit->SetWindowText(strText + "[취소]");
			OnBnClickedInquiryBtn();
			return;
		}
	}

	OnCancel();
}




int CRcpDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int nResult = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
		return nResult;   // frame does not want to activate

	return nResult;

	//	return CRcpDlgBase::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CRcpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if(!IsIconic()) 
	{   
		LF->FillBackground(&dc, this);    

		MakeRectangle(&dc, IDC_TEST_STATIC, IDC_DEST_MAP_BTN, TRUE, CRect(8, 8, 8, 8));
		MakeLine(&dc, IDC_RCP_STATIC12, IDC_ORDER_MEMO_EDIT, IDC_SHOW_PHONE_TYPE_ORDER_CHECK, IDC_START_EDIT, 0, -7);// RGB(255, 102, 0));
		MakeLine(&dc, IDC_RCP_STATIC21, IDC_START_DETAIL_EDIT, IDC_SHOW_PHONE_TYPE_START_CHECK, IDC_DEST_EDIT, 0, -7);// RGB(255, 102, 0));
		MakeLine(&dc, IDC_RCP_STATIC30, IDC_DEST_DETAIL_EDIT, IDC_SHOW_PHONE_TYPE_DEST_CHECK, IDC_RIDER_INFO_STATIC, 0, -7);//RGB(255, 102, 0));
		//MakeLine(&dc, IDC_RCP_STATIC40, IDC_CHARGE_VIA_BET_STATIC, IDC_ROUTE_MENU_BTN, IDC_CHARGE_BASIC_EDIT);
		//MakeLine(&dc, IDC_RCP_STATIC54, IDC_RIDER_AUTO_CHARGE_CHK, IDC_CONTEXT_MILEAGE_BTN, IDC_RCP_STATIC60);

		//if(IsEditMode() || m_nState == STATE_INTERNET)
		//	MakeLine(&dc, IDC_RCP_STATIC58, IDC_RCP_STATIC60, IDC_ETC_BTN, IDC_NEW_BTN);

		DrawTop(&dc);
	}
}

void CRcpDlg::AllocRiderInfo()
{
	if(m_nRiderCompany > 0 && m_nRNo > 0)
		OnMenuContextRider(ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW);
	else 
		OnMenuContextRider(ID_MENU_RIDER_ALLOC);
}

BOOL CRcpDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	long  nRet = FALSE;

	if(pMsg->message == WM_LBUTTONDOWN)
	{
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		HideSubHistoryDlgExeMe();

		if(pMsg->hwnd == m_stcRiderInfo.GetSafeHwnd() || pMsg->hwnd == m_stcRiderCompany.GetSafeHwnd())
		{
			AllocRiderInfo();
		}
		else if(pMsg->hwnd == m_stcRiderPhone.GetSafeHwnd())
		{
			OnMenuContextRider(ID_MENU_RIDER_CALL);
		}
		else if(pMsg->hwnd == m_EDT_ORDER_DEPART.pEdit->GetSafeHwnd())
		{				
			m_nLastDepartFocus = IDC_ORDER_DEPART_EDIT;	
			OpenManagerSearchDlg();
		}
		else if(pMsg->hwnd == m_EDT_START_DEPART.pEdit->GetSafeHwnd())
		{			
			m_nLastDepartFocus = IDC_START_DEPART_EDIT;	
			OpenManagerSearchDlg();
		}
		else if(pMsg->hwnd == m_EDT_DEST_DEPART.pEdit->GetSafeHwnd())
		{
			m_nLastDepartFocus = IDC_DEST_DEPART_EDIT;	
			OpenManagerSearchDlg();
		}
		else if(pMsg->hwnd == m_edtProperCharge1.GetSafeHwnd())
		{
			if(m_edtProperCharge1.GetWindowTextLength() > 0)
			{
				m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat(LF->GetStringFromEdit(&m_edtProperCharge1)));
				RefreshCharge();
			}
		}
		else if(pMsg->hwnd == m_edtProperCharge2.GetSafeHwnd())
		{
			if(m_edtProperCharge2.GetWindowTextLength() > 0)
			{
				m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat(LF->GetStringFromEdit(&m_edtProperCharge2)));
				RefreshCharge();
			}
		}
		else 
			HIDE_DLG(m_pSearchManagerDlg);
	}
	else if(pMsg->message == WM_KEYUP)
	{ 
		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		return OnPretransMessageWM_KEYUP(pMsg);
	}
	else if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickedCloseBtn();
			return TRUE;
		}

		m_pRcpView->SetFocusControl(this, CWnd::FromHandle(pMsg->hwnd));
		if(pMsg->wParam == VK_RETURN)		
		{		

			/*
			//by mksong (2011-02-11 오후 12:19)
			//combobox는 3개의 핸들을 가지고 있다. VK_KEYDOWN이 발생하는 핸들은 combo의 editbox이다.
			COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
			m_cmbOrderMP.GetComboBoxInfo(&info);
			if(info.hwndItem == pMsg->hwnd)
			{
			m_edtOrderMemo.SetFocus();
			return TRUE;
			}
			*/ 
			COMBOBOXINFO itemInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO couponInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO paytypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO waytypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO cartypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO runtypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO chargetypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO coupontypeInfo = { sizeof(COMBOBOXINFO)};
			COMBOBOXINFO allocgroupInfo = { sizeof(COMBOBOXINFO)};

			m_cmbItemType.GetComboBoxInfo(&itemInfo);
			m_cmbCouponCharge.GetComboBoxInfo(&couponInfo);
			m_cmbPayType.GetComboBoxInfo(&paytypeInfo);
			m_cmbWayType.GetComboBoxInfo(&waytypeInfo);
			m_cmbCarType.GetComboBoxInfo(&cartypeInfo);
			m_cmbRunType.GetComboBoxInfo(&runtypeInfo);
			m_CMB_CHARGE_TYPE.pCombo->GetComboBoxInfo(&chargetypeInfo);
			m_cmbRunType.GetComboBoxInfo(&runtypeInfo);
			m_cmbCouponType.GetComboBoxInfo(&coupontypeInfo);
			m_CMB_ALLOC_GROUP.pCombo->GetComboBoxInfo(&allocgroupInfo);


			if(itemInfo.hwndItem == pMsg->hwnd)
			{
				m_EDT_CHARGE_BASIC.pEdit->SetFocus();
				return TRUE;
			}
			else if(couponInfo.hwndItem == pMsg->hwnd)
			{
				m_EDT_ETC.pEdit->SetFocus();
				return TRUE;
			}
			else if(paytypeInfo.hwndItem == pMsg->hwnd)
			{
				m_cmbWayType.SetFocus();
				return TRUE;
			}
			else if(waytypeInfo.hwndItem == pMsg->hwnd)
			{
				m_cmbCarType.SetFocus();
				return TRUE;
			}
			else if(cartypeInfo.hwndItem == pMsg->hwnd)
			{
				m_cmbRunType.SetFocus();
				return TRUE;
			}
			else if(runtypeInfo.hwndItem == pMsg->hwnd)
			{
				m_cmbItemType.SetFocus();
				return TRUE;
			}
			else if(coupontypeInfo.hwndItem == pMsg->hwnd)
			{
				m_EDT_ETC.pEdit->SetFocus();
				return TRUE;
			}
			else if(allocgroupInfo.hwndItem == pMsg->hwnd)
			{
				m_EDT_ETC.pEdit->SetFocus();
				return TRUE;
			}

			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_ORDER_EDIT:
			case IDC_CID_EDIT:		
			case IDC_ORDER_ADDRESS_EDIT: 
				if(m_ci.m_bUseSearchPopup)
					ShowPlaceCustomerDlgBtn(m_pOrder, TRUE);
				else
					nRet = SearchEditVK_RETURN(::GetDlgCtrlID(pMsg->hwnd));
				GetSectionCharge();
				return nRet;
				break;
			case IDC_START_EDIT: 
			case IDC_START_ADDRESS_EDIT: 
				if(m_ci.m_bUseSearchPopup)
				{
					if(!SearchRegion(IDC_START_EDIT, TRUE))
						ShowPlaceCustomerDlgBtn(m_pStart, TRUE);
				}
				else
					nRet = SearchEditVK_RETURN(::GetDlgCtrlID(pMsg->hwnd));
				
				GetSectionCharge();  // 아래에 가면 2번 실행됨 //sujun 위에도 2번 실행하는데 요금타입이 안맞는 경우가 있어 아래로 내렸습니다.
				return TRUE;
				break;
			case IDC_DEST_EDIT:	
			case IDC_DEST_ADDRESS_EDIT: 
				if(m_ci.m_bUseSearchPopup)
				{
					if(!SearchRegion(IDC_DEST_EDIT, TRUE))
						ShowPlaceCustomerDlgBtn(m_pDest, TRUE);
				}
				else
					nRet = SearchEditVK_RETURN(::GetDlgCtrlID(pMsg->hwnd));
				
				GetSectionCharge(); // 아래에 가면 2번 실행됨 //sujun 위에도 2번 실행하는데 요금타입이 안맞는 경우가 있어 아래로 내렸습니다.
				return TRUE;
				break;
			
				//if(m_ui.bDeveloper)
				//	IsConsignApply();
				//if(::GetDlgCtrlID(pMsg->hwnd) == IDC_START_EDIT )
				//GetSectionCharge();  // IDC_DEST_EDIT  BASIC_EDIT_SETFOCUS실행
				//return TRUE;
				//break;
			case IDC_ORDER_CNO_EDIT:
				{
					m_EDT_ORDER_NAME.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_ORDER_NAME_EDIT:
				{
					m_EDT_ORDER_DEPART.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_ORDER_DEPART_EDIT:
				{
					m_EDT_ORDER_MANAGER.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_ORDER_MANAGER_EDIT:
				{
					m_EDT_ORDER_PHONE.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_ORDER_PHONE_EDIT:
				{
					m_edtOrderMP.SetFocus();
					return TRUE;
				}

			case IDC_ORDER_MP_EDIT:
				{
					OnStnClickedOrderAddressStatic();
					return TRUE;
				}

			case IDC_ORDER_DETAIL_EDIT:
				{
					m_edtOrderMemo.SetFocus();
					return TRUE;
				}

			case IDC_ORDER_MEMO_EDIT:
				{
					m_EDT_START.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_START_CNO_EDIT:
				{
					m_EDT_START_NAME.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_START_NAME_EDIT:
				{						
					m_EDT_START_DEPART.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_START_DEPART_EDIT:
				{
					m_EDT_START_MANAGER.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_START_MANAGER_EDIT:
				{
					m_EDT_START_PHONE.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_START_PHONE_EDIT:
				{
					m_edtStartMP.SetFocus();
					return TRUE;
				}

			case IDC_START_MP_EDIT:
				{
					OnStnClickedStartAddressStatic();
					return TRUE;
				}

			case IDC_START_DETAIL_EDIT:
				{
					m_EDT_DEST.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_DEST_CNO_EDIT:
				{
					m_EDT_DEST_NAME.pEdit->SetFocus();
					return TRUE;				
				}

			case IDC_DEST_NAME_EDIT:
				{
					m_EDT_DEST_DEPART.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_DEST_DEPART_EDIT:
				{
					m_EDT_DEST_MANAGER.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_DEST_MANAGER_EDIT:
				{
					m_EDT_DEST_PHONE.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_DEST_PHONE_EDIT:
				{
					m_edtDestMP.SetFocus();
					return TRUE;
				}

			case IDC_DEST_MP_EDIT:
				{
					OnStnClickedDestAddressStatic();
					return TRUE;
				}

			case IDC_DEST_DETAIL_EDIT:
				{
					m_EDT_ETC.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_RIDER_AUTO_CHARGE_EDIT:
				{
					m_EDT_ETC.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_ETC_EDIT:
				{
					if((GetKeyState(VK_CONTROL) & 0xF000) != 0xF000) 
					{
						if(!IsEditMode())
							m_btnNew.SetFocus();
						else 
							m_btnUpdate.SetFocus();

						return TRUE;
					}
					break;

				}				
			case IDC_CHARGE_BASIC_EDIT:
				{
					//m_EDT_ETC.pEdit->SetFocus();
					m_EDT_CHARGE_ADD.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_CHARGE_ADD_EDIT:
				{
					m_EDT_CHARGE_DIS.pEdit->SetFocus();
					return TRUE;
				}

			case IDC_CHARGE_DIS_EDIT:
				{
					m_EDT_CHARGE_TRANS.pEdit->SetFocus();
					return TRUE;
				}	
			case IDC_CHARGE_SUM_EDIT:
			case IDC_CHARGE_TRANS_EDIT:
				{
					m_EDT_CHARGE_DRIVING.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_CHARGE_DRIVING_EDIT: 
				{
					if(!IsEditMode())
					{
						if(m_pBi->bFocusToWaitBtn)
							m_btnWait.SetFocus();
						else
							m_btnNew.SetFocus();
					}
					else 
						m_btnUpdate.SetFocus();
					return TRUE;
				}
			case IDC_NEW_BTN:
				OnBnClickedNewBtn();
				return TRUE;

			case IDC_WAIT_BTN:
				OnBnClickedWaitBtn();
				return TRUE;

			case IDC_UPDATE_BTN:
				OnBnClickedUpdateBtn();
				return TRUE;

			case IDC_ORDER_DONG_EDIT:
				m_EDT_ORDER_DEPART.pEdit->SetFocus();
				return TRUE;

			case IDC_START_DONG_EDIT:
				m_EDT_START_DEPART.pEdit->SetFocus();
				return TRUE;

			case IDC_DEST_DONG_EDIT:
				m_EDT_DEST_DEPART.pEdit->SetFocus();
				return TRUE;

			case IDC_TNO_EDIT:
				SelectBranchCombo();
				return TRUE;
			}
		}//if(pMsg->wParam == VK_RETURN )	 끝
		else if(pMsg->wParam == VK_LEFT)
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_CHARGE_ADD_EDIT:
				{
					m_EDT_CHARGE_BASIC.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_CHARGE_DIS_EDIT:
				{
					m_EDT_CHARGE_ADD.pEdit->SetFocus();
					return TRUE;
				}
			}
		}
		else if(pMsg->wParam == VK_RIGHT)
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_CHARGE_BASIC_EDIT:
				{
					m_EDT_CHARGE_ADD.pEdit->SetFocus();
					return TRUE;
				}
			case IDC_CHARGE_ADD_EDIT:
				{
					m_EDT_CHARGE_DIS.pEdit->SetFocus();
					return TRUE;
				}
			}
		}
		else if(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{ 
			case IDC_CID_EDIT:
			case IDC_ORDER_EDIT:
			case IDC_START_EDIT: 
			case IDC_DEST_EDIT:
				if(m_ci.m_bUseSearchPopup == FALSE)
				{
					if(m_pSearchPOIDlg)
						m_pSearchPOIDlg->PostMessage(pMsg->message , pMsg->wParam, pMsg->lParam);	

				return TRUE;
				break;
				}

			case IDC_CHARGE_TRANS_EDIT:
				{
					m_EDT_CHARGE_ADD.pEdit->SetFocus();
					return TRUE;
					break;
				}
			}
			
		}
		else if(pMsg->wParam == VK_F1)
		{
			m_edtOrder.SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F2)
		{
			m_EDT_START.pEdit->SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F3)
		{
			m_EDT_DEST.pEdit->SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F4)
		{
			m_EDT_ORDER_NAME.pEdit->SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F5)
		{
			m_EDT_START_NAME.pEdit->SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F6)
		{
			m_EDT_DEST_NAME.pEdit->SetFocus();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F7)
		{
			OnBnClickedOrderCustomerDlgBtn();
			return TRUE;
		}
		else if(pMsg->wParam == VK_F8)
		{			
			OnBnClickedInputChargeNewBtn();
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

	return CRcpDlgBase::PreTranslateMessage(pMsg);
}

void CRcpDlg::OnCbnSelchangeBranchCombo()
{
	if(!IsEditMode())
	{
		m_pBi = GetBranchComboToBranchInfo();
		InitControlAfterGetData();

		if(LF->IsThisCompany("퀵오케이_적요", m_pBi->nCompanyCode))
			AddEtcOK();
 
		m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(m_pBi->bAutoShareOrder);

		if(LF->IsThisCompany("사천퀵", m_pBi->nCompanyCode))
			SetGrade(-100); //노란색 
		else
			SetGrade(0);

		//m_edtOrder.SetFocus();

		if(m_pSearchPOIDlg)
		{
			m_pSearchPOIDlg->SetPreData(""); 
			m_pSearchPOIDlg->m_strPreData = "";
		}

		CWnd *pWnd = &m_edtOrder;

		if(m_EDT_CID.pEdit->GetWindowTextLength() > 0)
			pWnd = m_EDT_CID.pEdit;		


		MSG pMsg;  
		pMsg.message = WM_KEYUP;
		pMsg.wParam = VK_RETURN;
		pMsg.hwnd = pWnd->GetSafeHwnd();

		PreTranslateMessage(&pMsg);
		pWnd->SetFocus();
		
	}
	else {
		MessageBox("오더 이동은 접수리스트 우클릭 메뉴를 이용하세요.", 
			"확인", MB_ICONINFORMATION);
	}
}


CBranchInfo* CRcpDlg::GetBranchComboToBranchInfo()
{
	CBranchInfo *pBi = NULL;
	long nCompanyCode = (long)m_CMB_BRANCH.pCombo->GetItemData(m_CMB_BRANCH.pCombo->GetCurSel());
	if(nCompanyCode < 0)
		return NULL;

	for (int i=0; i < m_ba.GetCount(); i++)
	{
		pBi = (CBranchInfo *)m_ba.GetAt(i);
		if(pBi->nCompanyCode == nCompanyCode)
			break;
	} 
	if (pBi == NULL)
		return NULL;
	else
		return pBi;
}

CString CRcpDlg::GetDisplayDongAndAddress(long nDongID, CString strDong, CString strAddress)
{
	CString strText = strDong;
	if(nDongID > 0)
	{
		strText.Format("%s %s", m_poiNew.GetPOI(nDongID)->GetRegionName(), strAddress);
		strText.Trim(' ');
	}

	return strText;
} 

void CRcpDlg::CopyPoiData(CPOIUnit **pDst, CPOIUnit *pSrc, long nPosX, long nPosY)
{
	if(pSrc == NULL)
	{
		if(*pDst)
		{
			delete *pDst;
			*pDst = NULL;
		}
	}
	else
	{
		*pDst = m_poiNew.NewPOI(1, pSrc, nPosX, nPosY);
	}
}

long CRcpDlg::GetPayTypeNew()
{
	return m_nPayType;
}

long CRcpDlg::GetWayTypeNew()
{
	return m_nWayType;
}

long CRcpDlg::GetRunTypeNew()
{
	return m_nRunType;
}

long CRcpDlg::GetRcpBasicCharge()
{
	//UpdateData();

	m_EDT_CHARGE_BASIC.pEdit->GetWindowText(m_strChargeBasic);
	CString strChargeBasic = "0";
	strChargeBasic = m_strChargeBasic;
	strChargeBasic.Replace(",", "");
	if(! LF->IsStringDigit(strChargeBasic))
		return 0;

	long nCharge = 0;
	nCharge = atol(strChargeBasic);

	return nCharge;

}
long CRcpDlg::GetStringChargeToNumber(CString strCharge)
{

	CString strTempCharge = "0";
	strTempCharge = strCharge;
	strTempCharge.Replace(",", "");
	if(! LF->IsStringDigit(strTempCharge))
		return 0;

	return atol(strTempCharge);

}
CString CRcpDlg::GetChargeBet()
{
	m_strChargeBet = m_stcChargeViaBet.GetMarkupText();
	//m_stcChargeViaBet.GetWindowText(m_strChargeBet);   //m_strChargeBet;
	return m_strChargeBet;
}

BOOL CRcpDlg::IsCreditOrderInsertOk()
{
	if(GetPayTypeNew() != PAY_CREDIT &&
		GetPayTypeNew() != PAY_ONLINE &&
		GetPayTypeNew() != PAY_CARD)
		return TRUE;

	if(m_pBi->nShareCode2 <= 0 && 
		m_pBi->nShareCode3 <= 0 &&
		m_pBi->nShareCode4 <= 0 &&
		m_pBi->nShareCode5 <= 0)
		return TRUE;

	CString strCharge; m_EDT_CHARGE_SUM.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", ""); 

	CString strTrans; m_EDT_CHARGE_TRANS.pEdit->GetWindowText(strTrans);
	strTrans.Replace(",", ""); 

	CMkCommand cmd(m_pMkDb, "select_share_balance_for_insert");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_pBi->nCompanyCode);
	cmd.AddParameter(atoi(strCharge) + atoi(strTrans));

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 0)
		MessageBox("공유 정산금이 부족하여 신용오더를 접수/수정 하실수 없습니다", "확인", MB_ICONINFORMATION);

	return nRet;
}


long CRcpDlg::AddNewOrder(BOOL bWait, BOOL bSMS, BOOL bAfterCopy, long nConsignLinkTNo, BOOL bInserForCard)
{
	if(!IsCreditOrderInsertOk())
		return 0;

	long nTNo = 0;
	//CString strCNo;
	//m_edtOrderCNo.GetWindowText(strCNo);
	//if(strCNo == "자동검색")
	//	JustInsertNewCustomer();

	UpdateData(TRUE);

	m_strChargeBasic.Replace(",", "");
	m_strChargeAdd.Replace(",", "");
	m_strChargeDis.Replace(",", "");
	m_strChargeSum.Replace(",", "");
	m_strChargeTrans.Replace(",", "");
	m_strDeposit.Replace(",", "");
	m_strValueAdd.Replace(",","");
	m_strChargeDriving.Replace(",","");
	m_strChargeRevision.Replace(",","");

	CWaitCursor wait;
	COleDateTime dtReserve = COleDateTime::GetCurrentTime();

	if(!m_bInquiryOrder && !m_bNoticeOrder)
	{
		try {
			if(m_pOrder->GetPhone().GetLength() < 1 &&
				m_pOrder->GetMP().GetLength() < 1)
				throw "의뢰지 전화번호를 입력하세요";

			if(m_pStart->GetDisplayDong().GetLength() < 1 || m_pStart->GetPOI() == NULL)
				throw "출발지 동이나 위치정보가 설정되지 않았습니다.";

			//CPOIUnit *p = m_pStart->GetPOI(); 

			if(m_pStart->GetPOI()->m_nID == 0)
				throw "출발지 동이나 위치정보가 설정되지 않았습니다.";

			if(m_pBi->bNoDestPoi == FALSE)
			{
				if(m_pDest->GetDisplayDong().GetLength() < 1 || m_pDest->GetPOI() == NULL)
					throw "도착지 동이나 위치정보가 설정되지 않았습니다.";

				if(m_pDest->GetPOI()->m_nID == 0)
					throw "도착지 동이나 위치정보가 설정되지 않았습니다.";
			}
		}
		catch(char *msg)
		{
			MessageBox(msg, "정보입력확인", MB_ICONINFORMATION);
			return FALSE;
		}

		//if(m_pOrder->GetCompany() == "")
		//	m_pOrder->SetCompany("일반");

		if(m_strChargeBasic.IsEmpty()) {
			if(IDYES != MessageBox("기본요금이 0원이 정상입니까?", 
				"요금확인", MB_YESNO | MB_ICONQUESTION))
				return FALSE;
		}

		if(m_strChargeDriving.IsEmpty()) {
			if(IDYES != MessageBox("기사요금이 0원이 정상입니까?", 
				"요금확인", MB_YESNO | MB_ICONQUESTION))
				return FALSE;
		}

		if(IsReserve()) 
		{
			if(!ReserveCheck())
				return FALSE;
		}

		m_cmbCouponCharge.GetWindowText(m_strCouponCharge);

		if(atoi(m_strCouponCharge) != 0)
			m_bCoupon = TRUE;

		m_strCNS.Replace("km", "");

	} //예약 공지 오더인지 체크 끝in

	if(m_pStart->GetPOI() == NULL)
	{
		if(MessageBox("출발지 정보가 없습니다\r\n접수시 PDA상에서 배차불가합니다\r\n접수하시겠습니까?", "확인", MB_YESNO) == IDNO)
			return FALSE;
	}
	else
	{
		if(m_pStart->GetPOI()->m_nID == 0)
		{
			if(MessageBox("출발지 정보가 없습니다\r\n접수시 PDA상에서 배차불가합니다\r\n접수하시겠습니까?", "확인", MB_YESNO) == IDNO)
				return FALSE;
		}
	}

	long nMileageSetting = 0, 	nMileageAutoCharge = 0, nStartChargeType = 0, nDestChargeType = 0, nStartDestChargeType = 0;
	BOOL bHistoryType = FALSE;
	CString sChargeHistoryName = "";
	//CheckMileage(nMileageSetting, nMileageAutoCharge);

	long nMileage = 0, nMileageReserveControl = 0;
	BOOL bMileException = FALSE;

	if(m_bNotOrderMileage || m_bOrderSpecialMileage)
	{
		nMileageSetting = GetMileageControlAmount();  
	}
	else if(m_mi.IsBranchUseMile(m_pBi->nCompanyCode, m_nPersonMileageType )  )
	{

		nMileageSetting = LF->GetLongFromEdit(&m_edtMileReserve);
		nMileageReserveControl = GetMileageControlAmount();
		nMileageAutoCharge = GetRiderAutoChargeControlAmount();
		bMileException = (nMileageSetting != nMileageReserveControl && nMileageReserveControl > 0) ? TRUE : FALSE;		
		

		if(IsSpanMile() &&   ! m_mi.IsMileageUseSpanCheck( m_pOrder->GetCNo(), GetRiderAutoChargeControlAmount() ) )
		{
			MessageBox("마일리지의 잔액이 사용금액을 초과합니다." );
			return 0;
		}
		else if( ( m_bInquiryOrder || m_bNoticeOrder)  && IsSpanMile() )
		{
			MessageBox("문의는 마일리지를 사용하실수 없습니다. 현금및 후불로 적용하세요", "확인", MB_ICONINFORMATION );
			return 0;
		}
	}
	
	if(LF->GetCurBranchInfo()->bAddDisChargeRound)
		CheckChargeRound(); 
		
		
	

	if(CheckDeposit() == FALSE)
		return FALSE;

	if(IsGroupInsertOk() == FALSE)
		return FALSE;  

	//  m_pCharge->m_nCharge != GetRcpBasicCharge() && m_pCharge->m_nChargeType == m_cmbChargeType.GetCurSel() && m_pCharge)
	if(	 m_chkSaveCharge.GetCheck() && GetRcpBasicCharge() > 0 ) 
	{
		sChargeHistoryName = LF->GetDashPhoneNumber( m_pOrder->GetPhone() ) + "_" + m_pOrder->GetCompany();
		nStartChargeType = LF->GetChargeDongTypeInfo(m_pStart->GetPOI()->GetDongID());
		nDestChargeType = LF->GetChargeDongTypeInfo(m_pDest->GetPOI()->GetDongID());
		nStartDestChargeType = LF->GetChargeType(nStartChargeType, nDestChargeType);
		bHistoryType = m_chkSaveCharge.GetCheck() ? TRUE : FALSE;	
	}	

	BOOL bNewCus = m_pOrder->IsNewCus(); 

	if(!CheckCompanyEmp())
		return FALSE;
 
	CMkCommand pCmd(m_pMkDb, "insert_new_dorder_item_2022");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	CMkParameter *parUseOutReturn = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);// 마일리지및 리턴결과여부
	CMkParameter *parState = pCmd.AddParameter(typeInt, typeInput, sizeof(int));	//상태
	pCmd.AddParameter(m_pBi->nDOrderTable);
	pCmd.AddParameter(m_pBi->nCustomerTable);
	pCmd.AddParameter(m_pStart->NeedToAddCustomer() && m_pBi->bCustomerAutoInsert);
	pCmd.AddParameter(m_pDest->NeedToAddCustomer() && m_pBi->bCustomerAutoInsert);
	pCmd.AddParameter(m_cmbDelType.GetCurSel());
	pCmd.AddParameter(m_pOrder->GetCNo());
	pCmd.AddParameter(m_pOrder->GetGNo());
	pCmd.AddParameter(m_pOrder->IsTempCNo());
	pCmd.AddParameter(m_pStart->GetCNo()); 
	pCmd.AddParameter(m_pDest->GetCNo());
	pCmd.AddParameter(m_pOrder->GetTelID());
	pCmd.AddParameter(m_pStart->GetTelID());
	pCmd.AddParameter(m_pDest->GetTelID());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBCompany() : m_pOrder->GetCompany());
	//pCmd.AddParameter(m_pOrder->GetPhone());
	//pCmd.AddParameter(m_pOrder->GetMP());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPhone() : m_pOrder->GetPhone());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBMP() : m_pOrder->GetMP());

	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBDepart() : m_pOrder->GetDepart());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBManager() : m_pOrder->GetManager());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBAddress() : m_pOrder->GetAddress());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBDetail() : m_pOrder->GetDetail());
	//pCmd.AddParameter(m_pOrder->GetDetail());
	pCmd.AddParameter(m_pOrder->GetMemo());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBDisplayDong() : m_pOrder->GetDisplayDong());

	CPOIUnit *pOrderPOI = bNewCus ? m_pOrder->GetDBPOI() : m_pOrder->GetPOI();

	if(pOrderPOI) 
	{
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPOI()->GetID() : m_pOrder->GetPOI()->GetID());		
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPOI()->GetDongID(TRUE) : m_pOrder->GetPOI()->GetDongID(TRUE));	
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPosX() :  m_pOrder->GetPosX());
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPosY() :  m_pOrder->GetPosY());
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPOI()->GetDong() :  m_pOrder->GetPOI()->GetDong());
	}
	else 
	{
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
		pCmd.AddParameter("");	
	}

	pCmd.AddParameter(m_pStart->GetCompany());
	pCmd.AddParameter(m_pStart->GetPhone());
	pCmd.AddParameter(m_pStart->GetMP());
	pCmd.AddParameter(m_pStart->GetDepart());
	pCmd.AddParameter(m_pStart->GetManager());
	pCmd.AddParameter(m_pStart->GetAddress()); 
	pCmd.AddParameter(m_pStart->GetDetail());
	pCmd.AddParameter(m_pStart->GetDisplayDong());


	if(m_pStart->GetPOI()) 
	{
		pCmd.AddParameter(m_pStart->GetPOI()->GetID());		
		pCmd.AddParameter(m_pStart->GetPOI()->GetDongID(TRUE));  // RealDongID
		pCmd.AddParameter(LF->IsExceptionDetailDongUse(m_pStart->GetPOI()) ?
			m_pStart->GetPOI()->GetDongID(TRUE) : m_pStart->GetPOI()->GetMainDongID());  // 요금관련
		pCmd.AddParameter(m_pStart->GetPosX());
		pCmd.AddParameter(m_pStart->GetPosY());
		pCmd.AddParameter(m_pStart->GetPOI()->GetDong());
	}
	else 
	{
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//charge dongid  // 번1, 2, 동, 창1,2, 3 메인동으로처리
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
		pCmd.AddParameter("");	
	}
	pCmd.AddParameter(m_pDest->GetCompany());
	pCmd.AddParameter(m_pDest->GetPhone());
	pCmd.AddParameter(m_pDest->GetMP());
	pCmd.AddParameter(m_pDest->GetDepart());
	pCmd.AddParameter(m_pDest->GetManager());
	pCmd.AddParameter(m_pDest->GetAddress());
	pCmd.AddParameter(m_pDest->GetDetail());
	pCmd.AddParameter(m_pDest->GetDisplayDong());

	if(m_pDest->GetPOI()) 
	{
		pCmd.AddParameter(m_pDest->GetPOI()->GetID());		
		pCmd.AddParameter(m_pDest->GetPOI()->GetDongID(TRUE));	
		pCmd.AddParameter(LF->IsExceptionDetailDongUse(m_pDest->GetPOI()) ?
			m_pDest->GetPOI()->GetDongID(TRUE) : m_pDest->GetPOI()->GetMainDongID());  // 요금관련
		pCmd.AddParameter(m_pDest->GetPosX());
		pCmd.AddParameter(m_pDest->GetPosY());
		pCmd.AddParameter(m_pDest->GetPOI()->GetDong());
	}
	else 
	{
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//charge dongid   LF->IsExceptionDetailDongUse(종로구, 중구)예외
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
		pCmd.AddParameter("");	
	}

	pCmd.AddParameter(m_strEtc);
	pCmd.AddParameter(GetReserveTime());
	pCmd.AddParameter(GetReleaseMin());
	pCmd.AddParameter(m_pBi->nFinalSMSSend);
	pCmd.AddParameter(0); //m_bNoSMS
	pCmd.AddParameter(m_strItemType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetPayTypeNew());
	pCmd.AddParameter(GetCarTypeNew());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetWayTypeNew());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetRunTypeNew());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), (long)(m_fDirectDistance * 100));
	//pCmd.AddParameter(0);

	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeBasic));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeAdd));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeDis));
	//pCmd.AddParameter(int(GetStringChargeToNumber(m_strChargeSum)));
	pCmd.AddParameter(atoi(m_strChargeSum));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeTrans));
	pCmd.AddParameter(GetStringChargeToNumber(m_strDeposit));
	pCmd.AddParameter(GetStringChargeToNumber(m_strValueAdd));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeDriving));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeReturn));
	
	pCmd.AddParameter(m_bCoupon);
	pCmd.AddParameter(atol(m_strCouponCharge));
	//pCmd.AddParameter((int)m_cmbAllocGroup.GetItemData(m_cmbAllocGroup.GetCurSel()));
	pCmd.AddParameter((int)(m_CMB_ALLOC_GROUP.pCombo->GetCurSel()));

	pCmd.AddParameter(m_strCID);
	pCmd.AddParameter(""); //m_strChargeBet

	pCmd.AddParameter(0); //탁송인지 아닌지 플래그가 들어감
	pCmd.AddParameter(m_CMB_CHARGE_TYPE.pCombo->GetCurSel());
	pCmd.AddParameter( m_nChargeMemCNo);
	pCmd.AddParameter( sChargeHistoryName);

	pCmd.AddParameter(nStartDestChargeType);
	pCmd.AddParameter(bHistoryType);
	pCmd.AddParameter(m_pBi->bNoGroupCharge);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_nLineID);
	//pCmd.AddParameter(min(30000, m_nLineID));
	pCmd.AddParameter(m_nOperatorID);

	if(IsReserve())
		pCmd.AddParameter(GetReleaseStateDB());
	else
		pCmd.AddParameter(0);

	pCmd.AddParameter(m_bScheduleOrder);
	pCmd.AddParameter(m_strIntercallEtc);

	pCmd.AddParameter(nMileageSetting);
	pCmd.AddParameter(nMileageAutoCharge);
	pCmd.AddParameter(m_bNotOrderMileage);
	pCmd.AddParameter(m_pBi->bUserIDSequence);
	pCmd.AddParameter(LF->GetDashPhoneNumberRemoveDDD(m_strSmsPhone));
	pCmd.AddParameter(m_bOrderSpecialMileage); // 2009-05-20 해당오더의 개별마일
	pCmd.AddParameter(m_strChargeGeneralOption);
	pCmd.AddParameter(m_strChargeAddOption);
	pCmd.AddParameter(m_BTN_NOT_SEND_COMPLETE_SMS.pButton->GetCheck());
	pCmd.AddParameter(m_BTN_AUTO_SHARE_ORDER.pButton->GetCheck()); 
	long nCount = m_pOrder->GetUseCount();
	pCmd.AddParameter(m_pOrder->GetUseCount()); 
	pCmd.AddParameter(nConsignLinkTNo); 
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtConCommissionCharge)); 
	pCmd.AddParameter(m_nTerminalWayID); 
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtConTotalCharge)); 
	pCmd.AddParameter(m_chkSameCarTypeOnly.GetCheck());
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_pBi->bMemChaNoGeneralData );
	pCmd.AddParameter(m_pBi->bFirstWaitTimePast );
	pCmd.AddParameter(m_pOrder->GetShowPhoneType());
	pCmd.AddParameter(m_pStart->GetShowPhoneType());
	pCmd.AddParameter(m_pDest->GetShowPhoneType());
	pCmd.AddParameter(m_chkAbleAllocLoadIns.GetCheck());
	pCmd.AddParameter(m_chkFoodOrder.GetCheck());
	pCmd.AddParameter(m_dtPreFoodComplete);
	pCmd.AddParameter(atoi(m_strChargeRevision));
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtChargeCompany));

	pCmd.AddParameter(IsInsungDlg());
	pCmd.AddParameter(GetSpecialTruckType());


	long nState = 0;

	if(m_bInquiryOrder)
		nState = STATE_INQUIRY;
	else if(m_bNoticeOrder)
		nState = STATE_NOTICE;
	else  
	{
		if(IsReserve()) 
			nState = STATE_RESERVED;
		else if(bWait) 
			nState = STATE_WAIT;	
		else 
			nState = STATE_OK;	
	}

	parState->SetValue(nState);


	//프로시져 실행
	if(pCmd.Execute()){
		long nOutReturn = 0;		
		parRet->GetValue(nTNo);
		parUseOutReturn->GetValue(nOutReturn);
		if(nTNo != 0)
		{
			if(nOutReturn == 1000)  //@MILE_BALANCE_SHORTAGE
			{
				LF->MsgBox("마일잔액이 부족하여 접수되지 않았습니다.");
			}

			if(nTNo == 100)  //@MILE_BALANCE_SHORTAGE
			{
				LF->MsgBox("출발지 위치정보가 올바르지 않습니다.\r\n출발지 위치 수정 후 다시 등록하세요");
				return 0;
			}

			if(nTNo == 101)  //@MILE_BALANCE_SHORTAGE
			{
				LF->MsgBox("도착지 위치정보가 올바르지 않습니다.\r\n도착지 위치 수정 후 다시 등록하세요");
				return 0;
			}

			m_pRcpView->PostMessage(WM_REFRESH_LIST, nTNo, 0L);

			if(m_bScheduleOrder)
			{
				if(((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg)
					((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg->RefreshList();
			}

			if(m_bAllocRider == TRUE)
			{
				if(IsReserve() == FALSE || 
					(IsReserve() && m_bAllocRiderChangeTime == 0))
				{
					AllocateRider(nTNo, nState, atol(m_strDeposit));
				}
			}


			if(m_nRevisitCustomer > 0)
				UpdateRevisitCustomerInfo(nTNo);

			CBranchInfo *pBi = m_ba.GetAt(0);
			if (m_strCID.GetLength() > 0 && pBi->bIPPBXType)
			{
				CMkRecordset rs(m_pMkDb);
				CMkCommand cmd(m_pMkDb, "update_record_file_name_TNo_1");

				long nInsertID = -1;
				if(LU->GetRcpView())
					nInsertID = LU->GetRcpView()->m_pCTIForm->GetRecordFileNameInsertID(m_strCID);

				cmd.AddParameter(m_pBi->nDOrderTable);
				CString strTemp = m_strCID;
				strTemp.Remove('-');
				cmd.AddParameter(strTemp);
				cmd.AddParameter(nTNo);
				cmd.AddParameter(nInsertID);

				rs.Execute(&cmd);
			}

			if(!bAfterCopy && !bInserForCard)
				OnCancel(); 

			if(m_pBi->bClearDestForAfterCopy)
				m_pDest->Clear();
		}
		else {
			m_pRcpView->PostMessage(WM_REFRESH_LIST, nTNo, 0L);
			MessageBox("오더등록은 되었을 가능성이 크지만, 접수가되었는지 필히 확인해 보시기 바랍니다.", "확인", MB_ICONINFORMATION);
		}


		if(m_nWebID > 0)
		{			
			long nWebID = m_nWebID;
			BOOL bOk = FALSE;
			if(IDYES == MessageBox("웹으로 접수된 오더를 완료하시려면 예(Y) 취소처리하려면 (N)을 선택하세요?", 
				"처리확인", MB_YESNO | MB_ICONINFORMATION) )
				bOk = TRUE;
			else
				bOk = FALSE;

			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "web_update_simple_order_finish");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWebID);  //web아이디	
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);  //web아이디	
			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);  //접수자
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), bOk);  // 상태
			pCmd.Execute();		

			m_pRcpView->OnCloseWebOrder();
		}

		UserCNSClose();

	}
	else {
		MessageBox("데이터 추가를 실패하였습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	return nTNo;
}


BOOL CRcpDlg::IsSpanMile()
{
	BOOL bUse = FALSE;
	bUse = (m_cmbPayType.GetCurSel() == PAY_TYPE_MILEAGE_CREDIT )
		? TRUE : FALSE;
	return bUse;

}

long CRcpDlg::GetRiderAutoChargeControlAmount()
{	
	return LF->GetMyUnNumberFormatEdit(&m_edtAutoCharge);
}

long CRcpDlg::GetMileageControlAmount()
{
	return LF->GetMyUnNumberFormatEdit(&m_edtMileReserve);
}


void CRcpDlg::UpdateRevisitCustomerInfo(long nTNo)
{
	CMkCommand pCmd(m_pMkDb, "update_revisit_customer_from_TNo_2");
	pCmd.AddParameter(m_nRevisitCustomer);
	pCmd.AddParameter(nTNo);

	pCmd.Execute();
} 

void CRcpDlg::OnBnClickedNewBtn()
{
	if(m_nState == STATE_INTERNET)
		EditOrder(FALSE);
	else 
		AddNewOrder(FALSE);
}


void CRcpDlg::OnBnClickedWaitBtn()
{
	if(m_nState == STATE_INTERNET)
		EditOrder(TRUE);
	else 
		AddNewOrder(TRUE);
}


void CRcpDlg::OnBnClickedNewAfterCopyBtn()
{
	if(m_nState == STATE_INTERNET)
		EditOrder(FALSE, TRUE);
	else
		AddNewOrder(FALSE, FALSE, TRUE);
}


void CRcpDlg::OnBnClickedWaitAfterCopyBtn()
{
	if(m_nState == STATE_INTERNET)
		EditOrder(TRUE, TRUE);
	else
		AddNewOrder(TRUE, FALSE, TRUE);
}

void CRcpDlg::OnCancel()
{
	KillTimer(HIDE_SEARCH_DONG_LIST_TIMER);

	UserCNSClose();

	if(!m_bOrderUpdated && IsEditMode() && !m_bEditExampleDlg)
	{
		KillTimer(EDIT_ORDER_STATE_TIMER);
		if(LU->m_pMsg)
			LU->m_pMsg->SendEditOrderState(m_nInitItem, EOS_CANCEL_EDIT);
	}

	if(m_strCID.GetLength() >  0)
	{
		LU->GetRcpView()->m_pCTIForm->RemoveRecordFileNameInsertID(m_strCID);
		LU->GetRcpView()->m_pCTIForm->QueueRecvModeSecond();
	}

	if(m_pHistoryDlg)
		m_pHistoryDlg->Clear();
	if(m_pCreditHistoryDlg)
		m_pCreditHistoryDlg->DeleteAllItems();

	m_pRcpView->PostMessage(WM_CLOSE_RCPDLG, (WPARAM)this);
}

void CRcpDlg::UserCNSClose()
{
	UINT bCNSClose = AfxGetApp()->GetProfileInt("RcpDlgMapDlg", "RcpCloseSameClose", 0);

	CRcpDlgMapDlg *pMapDlg = LU->GetRcpDlgMap(this, FALSE, TRUE);
	if(bCNSClose && pMapDlg && pMapDlg->IsWindowVisible())
		pMapDlg->ShowWindow(SW_HIDE);
}

void CRcpDlg::OnMenuCountMileageLog()
{
	if(m_pOrder->GetCNo() < 1)
	{
		MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_pBi->nMileageSettingCount != COUNT_MILEAGE)
	{
		CString sTemp = "마일리지를 사용하는 지사가 아니거나";
		sTemp += "[사용횟수당] 마일리지를 적용하지 않는 지사입니다.";
		MessageBox(sTemp, "확인", MB_ICONINFORMATION);

		return;
	}

	CCountMileageLogDlg dlg;
	dlg.m_nCompany = m_pBi->nCompanyCode;
	dlg.m_nCNo = m_pOrder->GetCNo();
	dlg.DoModal();	
}

void CRcpDlg::OnMileagePopupWindow()
{
	if(m_pOrder->GetCNo() <= 0)
	{
		MessageBox("고객이 등록 되어있지 않습니다.", "확인", MB_ICONINFORMATION);
		return;

	}
	
	CCustomerMileageDlg dlg;	
	dlg.m_nCNo = m_pOrder->GetCNo();
	dlg.m_nMileageBalance = m_nMileageBalance;
	dlg.DoModal();

	if(dlg.m_bApply)
	{
		m_nPersonMileageType = dlg.m_nPersonMileageType;
		m_nPersonMileage = dlg.m_nPersonMileage;
		m_nMileageBalance = dlg.m_nMileageBalance;
		m_edtMileageBalance.SetWindowText(LF->GetMyNumberFormat(m_nMileageBalance));
			
		m_edtAutoCharge.SetWindowText("");

		SetMileageData(0,0, TRUE);
	}
}


void CRcpDlg::OnMenuMileageMode()
{
	SetConsignMode(FALSE);
}


void CRcpDlg::OnMenuConsignMode()
{
	SetConsignMode(TRUE);
}

void CRcpDlg::OnUserMileage()
{
	try
	{
		if(m_nPersonMileageType == NO_MILEAGE_PERSON || m_chkAutoCharge.GetCheck())
		{
			LF->MsgBox("해당고객님은 마일리지를 사용하고 있지 않습니다.");
			return;
		}

		if(m_pOrder->GetCNo() <= 0)
			throw("고객이 활성화 되어있지 않습니다.");

		if(m_strMileageAutoCharge.GetLength() > 0 && m_chkAutoCharge.GetCheck())
			throw("마일리지를 지금 사용중입니다. 마일리지를 사용을 풀어주세요");

		CVarietyDlg dlg;
		dlg.m_sTitleDlg = "해당오더에 적용될 마일리지";
		dlg.DoModal();

		CString sValue = dlg.m_sValue;
		if(sValue.GetLength() == 0)
			throw("개별 마일리지 금액이 없습니다.");

		sValue.Replace("," ,"");
		sValue.Replace("\\", "");

		if(!LF->IsStringDigit(sValue))
			throw("숫자가 아닙니다.");
		/*
		1. 1회만 미적용  m_bNotOrderMileage TRUE  ,  m_bOrderSpecialMileage = 0
		2. 정상적용	 m_bNotOrderMileage FALSE	  ,	m_bOrderSpecialMileage = 0
		3. 1회만 사용자금액 적용 m_bNotOrderMileage FALSE   ,  m_bOrderSpecialMileage > 0
		*/

		m_nOrderSpecialMileage = atol(sValue);
		m_bNotOrderMileage = FALSE;
		m_bOrderSpecialMileage = TRUE;
		
		m_edtMileReserve.SetUserBkColor(RGB(255, 204, 193));
		m_edtMileReserve.SetWindowText(LF->GetMyNumberFormat(m_nOrderSpecialMileage));

	}
	catch(char *e)
	{
		LF->MsgBox(e);
	}
	catch (CString s)
	{
		LF->MsgBox(s);
	}
}

void CRcpDlg::OnUseOrderMileage()
{
	try
	{
		if(m_nPersonMileageType == NO_MILEAGE_PERSON || m_chkAutoCharge.GetCheck())
		{
			LF->MsgBox("해당고객님은 마일리지를 사용하고 있지 않습니다.");
			return;
		}

		if(m_pOrder->GetCNo() <= 0)
			throw("고객이 활성화 되어있지 않습니다.");

		if(m_strMileageAutoCharge.GetLength() > 0 && m_chkAutoCharge.GetCheck())
			throw("마일리지를 지금 사용중입니다. 마일리지를 사용을 풀어주세요");

		if(MessageBox(" 마일리지를 일반으로 돌려놓으시겠습니까? ", "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
			return;	

		/*
		1. 1회만 미적용  m_bNotOrderMileage TRUE  ,  m_bOrderSpecialMileage = 0
		2. 정상적용	 m_bNotOrderMileage FALSE	  ,	m_bOrderSpecialMileage = 0
		3. 1회만 사용자금액 적용 m_bNotOrderMileage FALSE   ,  m_bOrderSpecialMileage > 0
		*/

		m_bNotOrderMileage = FALSE;			
		m_bOrderSpecialMileage = FALSE;
		m_nOrderSpecialMileage = 0;
		m_edtMileReserve.SetUserBkColor(RGB(255, 255, 255));
		SetMileageData(0,0);
		
	}
	catch(char *e)
	{
		LF->MsgBox(e);
	}
}

void CRcpDlg::OnNotOrderMileage()
{
	try
	{
		if(m_nPersonMileageType == NO_MILEAGE_PERSON)
		{
			LF->MsgBox("해당고객님은 마일리지를 사용하고 있지 않습니다.");
			return;
		}

		// 신규  - 고객번호 체크하고, 멤버변수에 저장하고 오더등록 할때 등록
		if(m_pOrder->GetCNo() <= 0)
			throw("고객이 활성화 되어있지 않습니다.");

		if(m_bNotOrderMileage)
			throw("지금 마일 미적용중(1회성) 입니다.");

		// 불러오기 -- 오더불러온후 멤버변수에 저장하고 당오더 마일적용 안함표시
		// 수정  -- 수정할때 멤버변수로 저장

		CString strAutoCharge = "";
		m_edtAutoCharge.GetWindowText(strAutoCharge);
		strAutoCharge.Replace(",","");
		long nAutoCharge = atol(strAutoCharge);
		if(nAutoCharge > 0 && m_chkAutoCharge.GetCheck())
			throw("마일리지를 지금 사용중입니다. 마일리지를 사용을 풀어주고 작업하세요");


		if(MessageBox("해당오더의 마일리지를 적용안하시겠습니까? ", "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
			return;	

		/*
		1. 1회만 미적용  m_bNotOrderMileage TRUE  ,  m_bOrderSpecialMileage = 0
		2. 정상적용	 m_bNotOrderMileage FALSE	  ,	m_bOrderSpecialMileage = 0
		3. 1회만 사용자금액 적용 m_bNotOrderMileage FALSE   ,  m_bOrderSpecialMileage > 0
		*/

		m_bNotOrderMileage = TRUE;		
		m_bOrderSpecialMileage = FALSE;
		m_nOrderSpecialMileage = 0;
		m_edtMileReserve.SetUserBkColor(RGB(255, 204, 193));
		m_edtMileReserve.SetWindowText(LF->GetMyNumberFormat(m_nOrderSpecialMileage));

		
	}
	catch (char * e)
	{
		LF->MsgBox(e);
	}
	catch (CString s)
	{
		LF->MsgBox(s);
	}
}

void CRcpDlg::OnNotCompanyMileage()
{
	if(m_pOrder->GetCNo() <= 0)
	{
		MessageBox("의뢰지 고객을 검색 후 다시 시도하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("해당고객의 마일리지를 적용안하시겠습니까? ", "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		return;

	m_strMileageAutoCharge == "0";
	m_edtAutoCharge.SetWindowText(m_strMileageAutoCharge);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_mileage_not_cno2");
	pCmd.AddParameter(m_pOrder->GetCNo());
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_ui.nCompany);

	if(!pCmd.Execute())
		LF->MsgBox("작업중 오류가 났습니다.");
	else
	{
		LF->MsgBox("해당고객의 마일리지를 금일부로 적용하지 않습니다");			
		m_nMileageBalance = 0;
		m_edtMileageBalance.SetWindowText("");



		m_nPersonMileageType = NO_MILEAGE_PERSON;

		m_bNotOrderMileage = FALSE;		
		m_bOrderSpecialMileage = FALSE;
		m_nOrderSpecialMileage = 0;
		m_edtMileReserve.SetWindowText(0);
		
	}
}


LONG CRcpDlg::OnPreChargeInit(WPARAM wParam, LPARAM lParam)
{
	if(m_pCharge)
	{
		m_pCharge->SetNullData();
		
	}
	return 0;
}


LONG CRcpDlg::OnHistoryChargeApply(WPARAM wParam, LPARAM lParam)
{

	long nMemCNo = 0;
	BOOL bChargeRecalulate = FALSE;

	nMemCNo = (long)wParam;
	bChargeRecalulate = (long)lParam;

	if(nMemCNo < 0 && bChargeRecalulate == 0)
		return 0;

	m_nChargeMemCNo = nMemCNo;
	if(bChargeRecalulate)
		GetSectionCharge(TRUE);

	return 0;
}

void CRcpDlg::ChangeDistance()
{

}

void CRcpDlg::InsertCnsLog(long nTNo, long nDistance)
{
	if(m_pStart == NULL || m_pDest == NULL)
		return;

	if(m_pStart->GetPOI() == NULL || m_pDest->GetPOI() == NULL)
		return;

	CMkCommand cmd(m_pMkDb, "insert_cns_ok_log");
	cmd.AddParameter(m_pBi->nCompanyCode);
	cmd.AddParameter(m_pStart->GetPOI()->GetDongID());
	cmd.AddParameter(m_pDest->GetPOI()->GetDongID());
	cmd.AddParameter(nDistance);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_nInitItem);

	cmd.Execute();
}

void CRcpDlg::InitRiderInfo()
{
	m_bAllocRider = FALSE;
	m_bAllocRiderMyRider = FALSE;
	m_nRiderCompany = -1;
	m_nRNo = -1;
	m_strRiderName = "";
	m_strRPhone = "";

	DisplayRiderInfo();
}

BOOL CRcpDlg::ReserveOption()
{
	if(m_pReserveOrderDlg->m_bChangeRiderForReserve == 1)
	{
		//choe
		// 기사정보 초기화 > 예약으로 진행
		InitRiderInfo(); // 기사정보 초기화

		long nState = m_pRcpView->GetStateChange()->ReserveOrder(m_nInitItem, m_nState, GetReleaseMin(), GetReserveTime(), TRUE);

		//아래 프로시저 생성 요청
		if(STATE_RESERVED != nState)
		{
			MessageBox("예약 설정중 오류가 발생했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		m_nState = nState;
	}
	else
	{
		long nState = m_pRcpView->GetStateChange()->ReserveOrder(m_nInitItem, m_nState, 
			GetReleaseMin(), GetReserveTime(), FALSE);

		if(STATE_RESERVED != nState)
		{
			MessageBox("예약 설정중 오류가 발생했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		m_nState = nState;
	}
	/*
	else if(STATE_RESERVED != m_pRcpView->GetStateChange()->ReserveOrder(m_nInitItem, m_nState, 
		GetReleaseMin(), GetReserveTime(), FALSE)) //예약하는부분
	{
		MessageBox("예약 설정중 오류가 발생했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	*/

	m_pReserveOrderDlg->m_bChangeRiderForReserve = -1; //데이터가 남아 추후 영향을 미칠 수 있음

	return TRUE;
}

LONG CRcpDlg::OnGetCnsInfo(WPARAM wParam, LPARAM lParam)
{
	CString strCharge = "", strChangePOIString = "", szKm = "";
	int nModifyPoiConfirmCharge = (int)lParam;  // 이계 요금계산을 하고 끝나는건지 거리만 계산하는걵 확인
	float fDirectDistance = 0.0, fViaOnlyDistance  = 0.0;

	double* pdDistance = (double*)wParam;

	if(pdDistance == NULL)
	{
		InsertCnsLog(m_nInitItem, 0);
		return 0;
	}


	fDirectDistance = (float)*pdDistance;

	CString strDistance = "";
	strDistance.Format("%f",fDirectDistance );
	m_fDirectDistance = fDirectDistance;

	InsertCnsLog(m_nInitItem, m_fDirectDistance * 100);

	ChangeDistance();
	DELETE_OBJECT(pdDistance); 

	if(IsUseDirectDistance())
	{
		double fDistance = LF->GetDistanceMeter(m_pStart->GetPosX(), m_pStart->GetPosY(),
			m_pDest->GetPosX(), m_pDest->GetPosY());
		fDistance = fDistance / 1000;

		m_fDirectDistance = fDistance;
	}
	
	if(! bRouteSend   )
	{
		return FALSE;
	}
	bRouteSend = FALSE;
	m_pCNSCheckStart = m_pCNSCheckDest = NULL;


	if ( nModifyPoiConfirmCharge >= ONLY_DISTANCE ) 
	{
		DisplayChargeInfo(!IsEditMode() ? FALSE : TRUE);

		return 0;  // 동기반 거리요금이 아닌 경우... GetRouteDistance -> GetRouteDistance2
	}

	if(IsCardPayed())
		return 0;

	int nCarType = 0;
	long nOldCharge = 0, nNewCharge = 0, nMemCharge = 0;	
	if(m_pOrder->GetGNo() > 0)
		nMemCharge = 0;
	else
		nMemCharge = m_nChargeMemCNo;

	m_EDT_CHARGE_BASIC.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");			
	if(LF->IsStringDigit(strCharge))
		nOldCharge = atol(strCharge);	
	
	long nTempCarType = GetCarTypeNew();

	if(nTempCarType == CAR_LABO)
	{
		if(m_pBi->nLaboChargeType == LABO_CHARGE_DAMAS)
			nCarType = CAR_DAMA;
		else if(m_pBi->nLaboChargeType == LABO_CHARGE_VAN)
			nCarType = CAR_VAN;
		else if(m_pBi->nLaboChargeType == LABO_CHARGE_EACH)
			nCarType = CAR_LABO;
	}
	else
		nCarType = GetCarTypeNew();



	//nCarType = ( m_pBi->bUsePayBonggoFromLabo && GetCarTypeNew() == CAR_LABO ) ? CAR_VAN : GetCarTypeNew() ;

	nNewCharge = m_pCharge->GetTotalCharge( nMemCharge, 
		m_pStart->GetPOI(), m_pDest->GetPOI(),  m_pOrder->GetGNo(),
		m_pBi, m_nCNoChargeDriving, m_nCNoDiscount, m_fDirectDistance, 
		m_CMB_CHARGE_TYPE.pCombo->GetCurSel(), LF->GetCarTypeForCharge(nCarType),m_nRunType, 0, nCarType );

	g_bana_log->Print("OnGetCNS Info GetTotalCahrge %ld", nNewCharge);

	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat( nNewCharge));
	RefreshCharge();
	return 0;
}

void CRcpDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_FOR_CURRENT_TIME)
	{
		KillTimer(TIMER_FOR_CURRENT_TIME);
	}
	else if(nIDEvent == CHARGE_CHANGED_TIMER)
	{
		static int nCount = 0;

		if(nCount % 2 == 0)
		{
			m_EDT_CHARGE_SUM.edtFlatEdit2.SetUserBkColor(RGB(255, 0, 0));
			m_EDT_CHARGE_SUM.edtFlatEdit2.SetUserTextColor(RGB(255,255,255));
		}
		else
		{
			m_EDT_CHARGE_SUM.edtFlatEdit2.SetUserBkColor(RGB(255, 255, 255));
			m_EDT_CHARGE_SUM.edtFlatEdit2.SetUserTextColor(RGB(0,0,0));
		}

		m_EDT_CHARGE_SUM.pEdit->Invalidate();

		if(nCount++ > 6)
		{
			nCount = 0;
			m_bFlashPayEdit = FALSE;
			KillTimer(CHARGE_CHANGED_TIMER);
		}
	}
	else if(nIDEvent == EDIT_ORDER_STATE_TIMER)
	{
		KillTimer(nIDEvent);

		if(!m_bEditExampleDlg)
		{
			if(LU->m_pMsg)
				LU->m_pMsg->SendEditOrderState(m_nInitItem, EOS_EDITING);
			SetTimer(nIDEvent, 5000, NULL);
		}
	}
	else if(nIDEvent == HIDE_SEARCH_DONG_LIST_TIMER)
	{
		if(m_pSearchPOIDlg)
		{
			if(m_pSearchPOIDlg->IsWindowVisible() &&
				GetForegroundWindow() != m_pSearchPOIDlg &&
				!m_pSearchPOIDlg->m_chkAlwaysShow.GetCheck())
			{
				CWnd *pWnd = GetFocus();
				if(pWnd->GetSafeHwnd() != NULL)			
				{
					if(pWnd != (CWnd*)m_EDT_CID.pEdit && 
						pWnd != (CWnd*)&m_edtOrder &&
						pWnd != (CWnd*)m_EDT_START.pEdit && 
						pWnd != (CWnd*)m_EDT_DEST.pEdit &&
						pWnd != (CWnd*)&m_edtOrderAddress &&
						pWnd != (CWnd*)&m_edtStartAddress &&
						pWnd != (CWnd*)&m_edtDestAddress)
					{
						HideSearchPOIDlg();
					}
					else if((pWnd == (CWnd*)m_EDT_CID.pEdit && m_EDT_CID.pEdit->GetWindowTextLength() == 0) ||
						(pWnd == (CWnd*)&m_edtOrder && m_edtOrder.GetWindowTextLength() == 0) ||
						(pWnd == (CWnd*)m_EDT_START.pEdit && m_EDT_START.pEdit->GetWindowTextLength() == 0) ||
						(pWnd == (CWnd*)m_EDT_DEST.pEdit && m_EDT_DEST.pEdit->GetWindowTextLength() == 0))
					{
						HideSearchPOIDlg();				
					}
				}
				else
				{
					HideSearchPOIDlg();
				}
			}
		}
	}
	else if(nIDEvent == REFRESH_TIMER_ORDER_LOG)
	{
		KillTimer(nIDEvent);
		RefreshOrderLog(m_nInitItem);
	}
	else if(nIDEvent == TIMER_REVISIT_CUSTOMER)
	{
		KillTimer(TIMER_REVISIT_CUSTOMER);
		long nLastDay = 0;
		long nCNo = 0;
		long nPreCompany = m_pBi->nCompanyCode;
		GetCompanyCodeForRevisitCustomer(m_nOriginalCompany, nLastDay, nCNo);

		if(m_nOriginalCompany > 0 && nLastDay > 0)
		{
			//1차 공유 안에서, 통합콜센터 ID로 로그인 해서 전화 받으면 내부콜센터, 지사ID로 로그인해서 받으면 외부콜센터

			if(m_ci.m_nShareCode1 == m_ci.m_nCompanyCode &&
				m_ci.m_bRcpIntMode1 == TRUE) // 내부콜센터일경우
			{
				//CString strTemp = "";
				//strTemp.Format("[%s]지사에 %d일전에 접수한 내역이 있습니다.\r\n[%s]지사로 변경하시겠습니까?", \
				//	GetBranchInfo(m_nOriginalCompany)->strBranchName, nLastDay, GetBranchInfo(m_nOriginalCompany)->strBranchName);

				//if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
				//	return;

				for(int i = 0; i < m_CMB_BRANCH.pCombo->GetCount(); i++)
				{  
					if(m_nOriginalCompany == m_CMB_BRANCH.pCombo->GetItemData(i))
					{					 
						m_CMB_BRANCH.pCombo->SetCurSel(i);
						m_pBi = LF->GetBranchInfo(m_nOriginalCompany);

						if(m_pSearchPOIDlg)
							m_pSearchPOIDlg->SetPreData("");
						//OnCbnSelchangeBranchCombo();
						ShowSearchPOIDlg(m_strCID, m_pOrder, FALSE, m_EDT_START.pEdit, TRUE, 1, TYPE_PHONE);

						m_nRevisitCustomer = InsertRevisitCustomerLog(TRUE, TRUE, nCNo, nPreCompany);
						break;
					}
				}
			}
			else //외부 콜센터
			{
				CString strTemp = "";
				strTemp.Format("[%s]지사에 %d일전에 접수한 내역이 있습니다. (보장고객)", LF->GetBranchInfo(m_nOriginalCompany)->strBranchName, nLastDay);

				m_nRevisitCustomer = InsertRevisitCustomerLog(FALSE, FALSE, nCNo, nPreCompany);
			}
		}
	}

	CRcpDlgBase::OnTimer(nIDEvent);
}

long CRcpDlg::InsertRevisitCustomerLog(BOOL bChangeBranch, BOOL bInnerCallCenter, long nOriginalCNo, long nPreCompany)
{
	CMkCommand pCmd(m_pMkDb, "insert_revisit_customer_log");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(nPreCompany);
	pCmd.AddParameter(bInnerCallCenter);
	pCmd.AddParameter(bChangeBranch);
	pCmd.AddParameter(nOriginalCNo);

	long nRet = 0;

	if(!pCmd.Execute())
		return 0;

	parRet->GetValue(nRet);

	return nRet;
}

void CRcpDlg::InsertChargeChangeRequest()
{
	CMkCommand cmd(m_pMkDb, "insert_dorder_change_request_2");
	cmd.AddParameter(m_nInitItem);
	cmd.AddParameter(m_pBi->nCompanyCode);
	cmd.AddParameter(atoi(m_strChargeBasic));
	cmd.AddParameter(atoi(m_strChargeAdd));
	cmd.AddParameter(atoi(m_strChargeDis));
	cmd.AddParameter(atoi(m_strChargeSum));
	cmd.AddParameter(atoi(m_strChargeTrans));
	m_strChargeDriving.Replace("-", "");
	cmd.AddParameter(atoi(m_strChargeDriving));
	cmd.AddParameter(GetPayTypeNew());
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	//cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(atoi(m_strDeposit));
	cmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtChargeCompany));
	cmd.AddParameter(atoi(m_strChargeReturn));

	cmd.Execute();
}

void CRcpDlg::OnBnClickedUpdateBtn()
{
	EditOrder();
}

BOOL CRcpDlg::IsNeedRequest()
{
	CMkCommand cmd(m_pMkDb, "select_is_need_request");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_nInitItem);
	cmd.AddParameter(atoi(m_strChargeSum));
	cmd.AddParameter(atoi(m_strDeposit));
	cmd.AddParameter(atoi(m_strChargeTrans));
	cmd.AddParameter(GetCarTypeNew());
	cmd.AddParameter(GetPayTypeNew());
	cmd.AddParameter(atoi(m_strChargeReturn));
	cmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtChargeCompany));

	CMkParameter *pParPre = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pParNew = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute())
		return FALSE;

	long nRet, nPre, nNew;
	parRet->GetValue(nRet);
	pParPre->GetValue(nPre);
	pParNew->GetValue(nNew);

	if(nRet == 1)
		return FALSE;

	if(nPre == nNew)
		return FALSE;

	if(nPre > nNew)
		return TRUE;

	return FALSE;
}

BOOL CRcpDlg::CheckChangeOk()
{
	CMkCommand cmd(m_pMkDb, "is_order_change_ok");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_nInitItem);

	if(!cmd.Execute())
		return FALSE;

	long nRet;
	parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	return FALSE;
}

BOOL CRcpDlg::EditOrder(BOOL bWait, BOOL bAfterCopy, BOOL bAfterRcp)
{
 	if(!IsCreditOrderInsertOk())
		return 0;

	if(m_strYear != "")
	{
		if(!LF->POWER_CHECK(2012, "이전오더 수정", TRUE))
			return FALSE;
	}

	UpdateData(TRUE);

	try {
		if(m_pOrder->GetCompany().GetLength() < 1)
			throw "의뢰지 고객명을 입력하세요";

		if(m_pOrder->GetPhone().GetLength() < 1 &&
			m_pOrder->GetMP().GetLength() < 1)
			throw "의뢰지 전화번호를 입력하세요";

		if(m_pStart->GetDisplayDong().GetLength() < 1 || m_pStart->GetPOI() == NULL)
			throw "출발동이 선택되지 않았습니다.\n\n출발지 고객명/지명을 다시 검색하시기 바랍니다.";

		if(m_pDest->GetDisplayDong().GetLength() < 1 || m_pDest->GetPOI() == NULL)
			throw "출발동이 선택되지 않았습니다.\n\n출발지 고객명/지명을 다시 검색하시기 바랍니다.";
	}
	catch(char *msg)
	{
		MessageBox(msg, "정보입력확인", MB_ICONINFORMATION);
		return FALSE;
	}


	if(m_strChargeBasic.IsEmpty()) {
		if(IDYES != MessageBox("기본요금이 0원이 정상입니까?", 
			"요금확인", MB_YESNO | MB_ICONQUESTION))
			return FALSE;
	}

	if(m_strChargeDriving.IsEmpty()) {
		if(IDYES != MessageBox("기사요금이 0원이 정상입니까?", 
			"요금확인", MB_YESNO | MB_ICONQUESTION))
			return FALSE;
	}


	CWaitCursor wait;
	COleDateTime dtReserve = COleDateTime::GetCurrentTime();

	if(IsReserve())
	{
		if(!ReserveCheck())
			return FALSE;

		if(m_nState != STATE_RESERVED)
		{
			if(!ReserveOption())
				return FALSE;
		}
	}

	if(m_nState == STATE_RESERVED && IsReserve() == FALSE)   // 예약 해지하는 부분
	{
		long nStateTemp = m_pRcpView->GetStateChange()->CancelReserve(m_nInitItem, m_nState);

		if(STATE_OK != nStateTemp)
		{
			MessageBox("예약 해지중 오류가 발생했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		m_nState = nStateTemp;
	}

	//   일반  마일리지 개념 
	//  m_nPersonMileageType  = 0 회사적용
	//  m_nPersonMileageType  = 1 % 당 ,  2 금액당 ,  10 적용안함  100000  구간당
	//  특수한 경우 오더에 한해서
	//  m_bNotOrderMileage 이번오더 마일리지 적용안함, m_bOrderSpecialMileage  > 0 이번오더만 이금액적용
	// 
/*
	long nMileageSetting = 0, 	nMileageAutoCharge = 0;
	CString sMileageSetting = "", sMileageAuto = "", sValue = "";	
	m_edtAutoCharge.GetWindowText(sValue);
	sValue.Replace(",", "");
	if(m_chkAutoCharge.GetCheck())
	{
		nMileageSetting = 0;
		nMileageAutoCharge = atol(sValue);
		m_bNotOrderMileage = FALSE;
		m_bOrderSpecialMileage = FALSE;
		m_nOrderSpecialMileage = 0;
	}
	else
	{
		if(m_bNotOrderMileage || m_nPersonMileageType == NO_MILEAGE_PERSON)
			nMileageSetting = 0;
		else
			nMileageSetting = atol(sValue);
		nMileageAutoCharge = 0;
	}
*/
	long nMileage = 0, nMileageReserveControl = 0, nMileageSetting = 0,nMileageAutoCharge = 0 ;
	BOOL bMileException = FALSE;


	/*
	if(m_bNotOrderMileage || m_bOrderSpecialMileage)
		nMileageSetting = GetMileageControlAmount();
	else if(m_mi.IsBranchUseMile(m_pBi->nCompanyCode,m_nPersonMileageType)  )
	{
		nMileage = LF->GetLongFromEdit(&m_edtMileReserve);
			
		nMileageReserveControl = GetMileageControlAmount();
		bMileException = (nMileage != nMileageReserveControl && nMileageReserveControl > 0) ? TRUE : FALSE;

		nMileageSetting  = bMileException? nMileage : nMileageReserveControl;  // 마일리지
		nMileageAutoCharge = GetRiderAutoChargeControlAmount();

		if( IsSpanMile()  && m_bTodayOrder &&  ! m_mi.IsMileageUseSpanCheck(m_pOrder->GetCNo(),GetRiderAutoChargeControlAmount() , m_nInitItem))
		{
			MessageBox("마일리지의 잔액이 사용금액을 초과합니다." );
			return FALSE;
		}
	}
	*/

	
	if(m_mi.IsBranchUseMile(m_pBi->nCompanyCode,m_nPersonMileageType)  )
	{
		nMileage = LF->GetLongFromEdit(&m_edtMileReserve);

		nMileageReserveControl = GetMileageControlAmount();
		bMileException = (nMileage != nMileageReserveControl && nMileageReserveControl > 0) ? TRUE : FALSE;

		nMileageSetting  = bMileException? nMileage : nMileageReserveControl;  // 마일리지
		nMileageAutoCharge = GetRiderAutoChargeControlAmount();

		if(m_bNotOrderMileage || m_bOrderSpecialMileage)
			nMileageSetting = GetMileageControlAmount();

		if( IsSpanMile()  && m_bTodayOrder &&  ! m_mi.IsMileageUseSpanCheck(m_pOrder->GetCNo(),GetRiderAutoChargeControlAmount() , m_nInitItem))
		{
			MessageBox("마일리지의 잔액이 사용금액을 초과합니다." );
			return FALSE;
		}
	}


	m_cmbCouponCharge.GetWindowText(m_strCouponCharge);

	if(atoi(m_strCouponCharge) != 0)
		m_bCoupon = TRUE; 

	m_strCNS.Replace("km", "");

	BOOL bAfterChange = FALSE;
	long nFinalDeposit = 0;
	CString sEtc = "", sChargeHistoryName ="";

	m_strChargeBasic.Remove(',');
	m_strChargeAdd.Remove(',');
	m_strChargeDis.Remove(',');
	m_strChargeSum.Remove(',');
	m_strChargeTrans.Remove(',');
	m_strDeposit.Remove(',');
	m_strValueAdd.Remove(',');
	m_strChargeDriving.Remove(',');

	if(CheckDeposit() == FALSE)
		return FALSE;

	if(LF->GetCurBranchInfo()->bAddDisChargeRound )
		CheckChargeRound();
		

	BOOL bChangeCrossOrderCharge = FALSE;


	if(m_bTodayOrder == FALSE)
	{
		if(!CheckChangeOk())
		{
			MessageBox("오더 수정요청중에 있으므로 수정하실수 없습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(IsNeedRequest())
			bChangeCrossOrderCharge = TRUE;
	}

	

	if(bChangeCrossOrderCharge)
	{
		if(MessageBox("금액을 수정하실 경우 수주사로부터 승인을 받아야합니다\r\n금액수정 요청을 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		{
			OnCancel();
			return FALSE;
		}

		InsertChargeChangeRequest();
		
		OnCancel();
		return FALSE;
	}

	BOOL bHistoryType = FALSE;
	int nStartChargeType = 0, nDestChargeType = 0, nStartDestChargeType = 0;

	if(	
		(m_nLoadChargeBasic  != GetRcpBasicCharge() ) &&  // 불러온 금액과 현재금액이 틀리고
		(m_chkSaveCharge.GetCheck() || m_nChargeMemCNo > 0 ) // 업체요금체크나  업체요금 타입일때
		)
	{
		sChargeHistoryName = LF->GetDashPhoneNumber( m_pOrder->GetPhone()) + "_" + m_pOrder->GetCompany();

		nStartChargeType = LF->GetChargeDongTypeInfo(m_pStart->GetPOI()->GetDongID());
		nDestChargeType = LF->GetChargeDongTypeInfo(m_pDest->GetPOI()->GetDongID());
		nStartDestChargeType = LF->GetChargeType(nStartChargeType, nDestChargeType);
		bHistoryType = m_chkSaveCharge.GetCheck()  ? TRUE : FALSE;			
	}	
 
	if(IsGroupInsertOk() == FALSE)
		return FALSE;  

	if(m_nPreCharge != atoi(m_strChargeSum) && m_bTodayOrder == FALSE)
	{
		if(!LF->POWER_CHECK(2030, "이전오더 요금수정", TRUE))
			return FALSE;
	}

	CMkCommand pCmd(m_pMkDb, "update_dorder_item_2022");

	if(m_strYear != "")  
	{
		MessageBox("이전오더는 수정 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_nInitItem);
	pCmd.AddParameter(m_nState);
	pCmd.AddParameter(m_pBi->nCustomerTable);
	pCmd.AddParameter(m_pStart->NeedToAddCustomer());
	pCmd.AddParameter(m_pDest->NeedToAddCustomer());
	pCmd.AddParameter(m_cmbDelType.GetCurSel());
	pCmd.AddParameter(m_pOrder->GetCNo());
	pCmd.AddParameter(m_pOrder->GetGNo());

	if(m_strYear.IsEmpty())
		pCmd.AddParameter(m_pOrder->IsTempCNo());

	pCmd.AddParameter(m_pStart->GetCNo());
	pCmd.AddParameter(m_pDest->GetCNo());

	if(m_strYear.IsEmpty()) //백업오더 테이블에 아래 컬럼 존재하지않음 by mksong (2011-04-18 오전 11:11)
	{
		pCmd.AddParameter(m_pOrder->GetTelID());
		pCmd.AddParameter(m_pStart->GetTelID());
		pCmd.AddParameter(m_pDest->GetTelID());
	}

	pCmd.AddParameter(bWait);
	pCmd.AddParameter(IsReserve()); //m_pReserveOrderDlg->GetChangeRiderForReserve(); TRUE일때 현재 배차상태 기사 삭제
	//pCmd.AddParameter(m_pReserveOrderDlg->GetChangeRiderForReserve()); //m_pReserveOrderDlg->GetChangeRiderForReserve(); TRUE일때 현재 배차상태 기사 삭제
	pCmd.AddParameter(m_pOrder->GetCompany());
	pCmd.AddParameter(m_pOrder->GetPhone());
	pCmd.AddParameter(m_pOrder->GetMP());
	pCmd.AddParameter(m_pOrder->GetDepart());
	pCmd.AddParameter(m_pOrder->GetManager());

	BOOL bNewCus = m_pOrder->IsNewCus();

	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBAddress() : m_pOrder->GetAddress());
	pCmd.AddParameter(m_pOrder->GetDetail());
	pCmd.AddParameter(m_pOrder->GetMemo());
	pCmd.AddParameter(bNewCus ? m_pOrder->GetDBDisplayDong() : m_pOrder->GetDisplayDong());

	CPOIUnit *pOrderPOI = bNewCus ? m_pOrder->GetDBPOI() : m_pOrder->GetPOI();
	if(pOrderPOI) 
	{
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPOI()->GetID() : m_pOrder->GetPOI()->GetID());		
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPOI()->GetDongID(TRUE) : m_pOrder->GetPOI()->GetDongID(TRUE));	

		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPosX() : m_pOrder->GetPosX());
		pCmd.AddParameter(bNewCus ? m_pOrder->GetDBPosY() : m_pOrder->GetPosY());
	}
	else 
	{
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//charge dongid
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
	}

	pCmd.AddParameter(m_pStart->GetCompany());
	pCmd.AddParameter(m_pStart->GetPhone());
	pCmd.AddParameter(m_pStart->GetMP());
	pCmd.AddParameter(m_pStart->GetDepart());
	pCmd.AddParameter(m_pStart->GetManager());
	pCmd.AddParameter(m_pStart->GetAddress());
	pCmd.AddParameter(m_pStart->GetDetail());
	pCmd.AddParameter(m_pStart->GetDisplayDong());


	if(m_pStart->GetPOI()) {
		pCmd.AddParameter(m_pStart->GetPOI()->GetID());		
		pCmd.AddParameter(m_pStart->GetPOI()->GetDongID(TRUE));	
		pCmd.AddParameter(LF->IsExceptionDetailDongUse(m_pStart->GetPOI()) ?
			m_pStart->GetPOI()->GetDongID(TRUE) : m_pStart->GetPOI()->GetMainDongID());  // 요금관련
		pCmd.AddParameter(m_pStart->GetPosX());
		pCmd.AddParameter(m_pStart->GetPosY());

	}
	else {
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
	}


	pCmd.AddParameter(m_pDest->GetCompany());
	pCmd.AddParameter(m_pDest->GetPhone());
	pCmd.AddParameter(m_pDest->GetMP());
	pCmd.AddParameter(m_pDest->GetDepart());
	pCmd.AddParameter(m_pDest->GetManager());
	pCmd.AddParameter(m_pDest->GetAddress());
	pCmd.AddParameter(m_pDest->GetDetail());
	pCmd.AddParameter(m_pDest->GetDisplayDong());

	if(m_pDest->GetDBPOI()) {
		pCmd.AddParameter(m_pDest->GetPOI()->GetID());		
		pCmd.AddParameter(m_pDest->GetPOI()->GetDongID(TRUE));	
		pCmd.AddParameter(LF->IsExceptionDetailDongUse(m_pDest->GetPOI()) ?
			m_pDest->GetPOI()->GetDongID(TRUE) : m_pDest->GetPOI()->GetMainDongID());  // 요금관련
		pCmd.AddParameter(m_pDest->GetPosX());
		pCmd.AddParameter(m_pDest->GetPosY());
	}
	else {
		pCmd.AddParameter(0);	//dongid
		pCmd.AddParameter(0);	//real dongid
		pCmd.AddParameter(0);	//charge dongid
		pCmd.AddParameter(0);	//posx
		pCmd.AddParameter(0);	//posy
	}

	pCmd.AddParameter(m_strEtc);
	pCmd.AddParameter(GetReserveTime());
	pCmd.AddParameter(GetReleaseMin()); 
	pCmd.AddParameter(m_pBi->nFinalSMSSend);
	pCmd.AddParameter(0); //m_bNoSMS
	pCmd.AddParameter(m_strItemType);
	pCmd.AddParameter(GetPayTypeNew());
	pCmd.AddParameter(GetCarTypeNew());
	pCmd.AddParameter(GetWayTypeNew());
	pCmd.AddParameter(GetRunTypeNew());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), (long)(m_fDirectDistance * 100) );

	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeBasic));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeAdd));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeDis));
	pCmd.AddParameter(atoi(m_strChargeSum));
	//pCmd.AddParameter(GetStringChargeToNumber(m_strChargeSum));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeTrans));
	pCmd.AddParameter(GetStringChargeToNumber(m_strDeposit));
	pCmd.AddParameter(GetStringChargeToNumber(m_strValueAdd));
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeDriving)); 
	pCmd.AddParameter(GetStringChargeToNumber(m_strChargeReturn));

	pCmd.AddParameter(m_bCoupon);
	pCmd.AddParameter(atol(m_strCouponCharge));
	pCmd.AddParameter((int)(m_CMB_ALLOC_GROUP.pCombo->GetCurSel()));
	//pCmd.AddParameter(0); //m_strRiderNo
	//pCmd.AddParameter(0);	//nRiderCompany;
	//pCmd.AddParameter(""); //m_strRiderName
	//pCmd.AddParameter(""); //m_strRiderMP
	pCmd.AddParameter(""); // m_stcChargeViaBet.GetWindowText(str)   //m_strChargeBet
	pCmd.AddParameter(0); //탁송인지 아닌지 플래그가 들어감

	pCmd.AddParameter(bHistoryType);
	pCmd.AddParameter(m_nChargeMemCNo);
	pCmd.AddParameter(m_pBi->bMemChaNoGeneralData);
	pCmd.AddParameter(m_pBi->bNoGroupCharge);
	pCmd.AddParameter(sChargeHistoryName);
	pCmd.AddParameter(m_CMB_CHARGE_TYPE.pCombo->GetCurSel());
	pCmd.AddParameter(nStartDestChargeType);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(IsReserve())
		pCmd.AddParameter(GetReleaseStateDB());
	else
		pCmd.AddParameter(0);

	pCmd.AddParameter(m_bScheduleOrder);
	pCmd.AddParameter(m_strIntercallEtc);
	pCmd.AddParameter(nMileageSetting);
	pCmd.AddParameter(nMileageAutoCharge);
	pCmd.AddParameter(m_bNotOrderMileage);
	pCmd.AddParameter(LF->GetDashPhoneNumberRemoveDDD(m_strSmsPhone));
	pCmd.AddParameter(m_bOrderSpecialMileage);
	pCmd.AddParameter(m_strChargeGeneralOption);
	pCmd.AddParameter(m_strChargeAddOption);
	pCmd.AddParameter(m_pBi->bUserIDSequence);
	pCmd.AddParameter(m_BTN_NOT_SEND_COMPLETE_SMS.pButton->GetCheck());
	pCmd.AddParameter(m_BTN_AUTO_SHARE_ORDER.pButton->GetCheck());
	pCmd.AddParameter(bAfterRcp);
	pCmd.AddParameter(0);   /// 탁송연계오더인지여부
	//pCmd.AddParameter(m_bConsignLink);   /// 탁송연계오더인지여부
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtConCommissionCharge)); 
	pCmd.AddParameter(m_nTerminalWayID); 
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtConTotalCharge)); 
	pCmd.AddParameter(m_chkSameCarTypeOnly.GetCheck());
	pCmd.AddParameter(m_pOrder->GetShowPhoneType());
	pCmd.AddParameter(m_pStart->GetShowPhoneType());
	pCmd.AddParameter(m_pDest->GetShowPhoneType());
	pCmd.AddParameter(LF->GetMyUnNumberFormatEdit(&m_edtChargeCompany));
	pCmd.AddParameter(m_chkAbleAllocLoadIns.GetCheck());
	pCmd.AddParameter(m_chkFoodOrder.GetCheck());
	pCmd.AddParameter(m_dtPreFoodComplete);
	m_strChargeRevision.Replace(",", "");
	pCmd.AddParameter(atoi(m_strChargeRevision));
	pCmd.AddParameter(GetSpecialTruckType());;

	CMkParameter *parShareError = pCmd.AddParameter(typeString, typeOutput, 200, "");


	if(pCmd.Execute()) {
		long nRet = parRet->GetLong();
		if(nRet == 0)
		{
			LF->MsgBox("하루가 지난 공유된 신용오더는\r\n정산이 이루어진 관계로 금액수정이 불가합니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}
		else if(nRet == 2)
		{
			MessageBox("타사기사가 배차한 완료오더가 요금관련 수정이 발생되어\n"\
				"기사소속회사에 수정요청이 전달되었습니다.\n\n"\
				"현재상태에서 요금관련 수정 정보는 오더에 반영되어 있지 않으며\n"\
				"기사소속회사에서 승인처리시에 자동으로 반영됩니다.\n\n"\
				"이는 모든 정산관련 부분에서의 오류를 막기 위함입니다.",
				"요금관련 수정요청", 
				MB_ICONINFORMATION);
		}
		else if(nRet == 3)
		{
			MessageBox("해당 오더는 세금계산서가 이미 발행되어\n오더 수정이 불가합니다.",
				"그룹정산_세금계산서발행", 
				MB_ICONINFORMATION);
		}
		else if(nRet == 4)
		{
			CString strError; parShareError->GetValue(strError);
			MessageBox(strError, "제휴오더",  MB_ICONINFORMATION);
			return FALSE;
		}
		else if(nRet > 4) 
		{
			CString strMsg;
			strMsg = "해당 아이템의 상태가 다른 사람에 의해서 변경되었습니다.\n";
			strMsg += "계속 하시려면 수정버튼을 한번 더 눌러주세요.\n\n\n상태: ";
			strMsg += LF->GetStateString(m_nState);
			strMsg += " --> ";
			strMsg += LF->GetStateString(nRet);
			m_nState = nRet;
			m_EDT_STATE.pEdit->SetWindowText(CString("    ") + LF->GetStateString(m_nState));
			m_pRcpView->PostMessage(WM_REFRESH_LIST, m_nInitItem, 0L);
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(m_nTempCNo > 0)
		{
			CMkCommand pCmd(m_pMkDb, "update_intercustomer_cno");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTempCNo);	//TempCNo
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pOrder->GetCNo());		//RealCNo
			pCmd.Execute();
		}

		m_pRcpView->PostMessage(WM_REFRESH_LIST, m_nInitItem, 0L);

		if(m_bScheduleOrder)
		{
			if(((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg)
				((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg->RefreshList();
		}

		if(m_nPreState == STATE_INTERNET)
			LU->SendGcmMsgForSmartQ2(m_nInitItem);

		//if(bAfterChange) 실시간정산함
		//	CheckOrderAfterChange(nFinalDeposit, sEtc); 

		if(m_bAllocRider == TRUE)
			AllocateRider(m_nInitItem, m_nState, atol(m_strDeposit));

		if(!bAfterCopy)
			OnCancel();

		m_bOrderUpdated = TRUE;
		if(IsEditMode() && !m_bEditExampleDlg)
		{
			KillTimer(EDIT_ORDER_STATE_TIMER);
			if(LU->m_pMsg)
				LU->m_pMsg->SendEditOrderState(m_nInitItem, EOS_END_EDIT);
		}

		UserCNSClose();
	}
	else 
	{
		MessageBox("수정 실패됨", "수정실패", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	return TRUE;
}

BOOL CRcpDlg::IsRequesting()
{
	CMkCommand pCmd(m_pMkDb, "select_is_order_request");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));	//return
	pCmd.AddParameter(m_nInitItem);

	if(!pCmd.Execute()) return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 0)
		return TRUE;

	return FALSE;	
}

BOOL CRcpDlg::IsOrderAfterChange(long &nFinalDeposit, CString &sEtc)
{
	if(m_stPreInfo.nRiderCompany == 0 || m_stPreInfo.nRNo == 0)
		return FALSE;

	if(m_pBi->nShareCode1 == m_ci.GetShareCode1(m_stPreInfo.nRiderCompany))
		return FALSE;

	return IsOrderAfterChangeDetail(nFinalDeposit, sEtc);
}

BOOL CRcpDlg::IsOrderAfterChangeDetail(long &nFinalDeposit, CString &sEtc)
{
	sEtc = "";
	sEtc.Format("오더%d, ", m_nInitItem);

	ST_EDIT_HISTORY stCur; 
	SaveCurInfo(stCur);

	nFinalDeposit = 0;

	if(m_stPreInfo.nDeposit != stCur.nDeposit)
	{
		long nPreDeposit = GetRiderRealDeposit(&m_stPreInfo);
		long nCurDeposit = GetRiderRealDeposit(&stCur);

		nFinalDeposit = nPreDeposit - nCurDeposit;

		if(nFinalDeposit != 0)
			sEtc += "[입금액변경 " + LF->GetMyNumberFormat(nPreDeposit) + "->" + LF->GetMyNumberFormat(nCurDeposit) + "] ";
	}

	if(::CCompleteAfterEditDlg::IsDifferentPayType(m_stPreInfo.nPayType, stCur.nPayType) == FALSE)
	{
		if(LF->IsCash(m_stPreInfo.nPayType))//현금->신용
		{
			sEtc += "[입금방식변경 현->외 " + LF->GetMyNumberFormat(stCur.nChargeSum + stCur.nChargeTrans) + "] ";
			nFinalDeposit += stCur.nChargeSum + stCur.nChargeTrans;
		}
		else //신용 -> 현금
		{
			sEtc += "[입금방식변경 외->현 " + LF->GetMyNumberFormat(m_stPreInfo.nChargeSum + m_stPreInfo.nChargeTrans) + "] ";
			nFinalDeposit -= m_stPreInfo.nChargeSum + m_stPreInfo.nChargeTrans;					
		}
	}
	else
	{
		if(!LF->IsCash(m_stPreInfo.nPayType))//신용->신용
		{
			if(m_stPreInfo.nChargeSum != stCur.nChargeSum ||
				m_stPreInfo.nChargeTrans != stCur.nChargeTrans)
			{
				sEtc += "[금액변경 " + LF->GetMyNumberFormat(stCur.nChargeSum + stCur.nChargeTrans) + "->" + LF->GetMyNumberFormat(m_stPreInfo.nChargeSum + m_stPreInfo.nChargeTrans) +"]";
				nFinalDeposit += (stCur.nChargeSum + stCur.nChargeTrans) - (m_stPreInfo.nChargeSum + m_stPreInfo.nChargeTrans);
			}
		}
	}

	if(nFinalDeposit == 0)
		return FALSE;

	return TRUE;
}

void CRcpDlg::CheckOrderAfterChange(long nDeposit, CString sEtc)
{
	CMkCommand pCmd(m_pMkDb, "transfer_after_order_change");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_nInitItem);
	pCmd.AddParameter(m_stPreInfo.nCompany);
	pCmd.AddParameter(m_stPreInfo.nRiderCompany);
	pCmd.AddParameter(nDeposit);
	pCmd.AddParameter(sEtc);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_ui.strID);

	if(pCmd.Execute())
	{
		long nRet; parRet->GetValue(nRet);
		CString sTemp = "";

		if(nRet == 1)
		{
			sTemp.Format("[%s]지사로 %s원 이체하였습니다", m_ci.GetName(m_stPreInfo.nRiderCompany), LF->GetMyNumberFormat(nDeposit));
			MessageBox(sTemp, "확인", MB_ICONINFORMATION);
			return;
		}
		else if(nRet == 2)
		{
			sTemp.Format("[%s]지사로 %s원 청구요청하였습니다", m_ci.GetName(m_stPreInfo.nRiderCompany), LF->GetMyNumberFormat(-1 * nDeposit));
			MessageBox(sTemp, "확인", MB_ICONINFORMATION);
			return;
		}
	}
}

long CRcpDlg::GetRiderRealDeposit(ST_EDIT_HISTORY *pStruct)
{
	long nRet = 0;
	CMkCommand pCmd(m_pMkDb, "get_rider_real_deposit");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));

	pCmd.AddParameter(pStruct->nCompany);
	pCmd.AddParameter(pStruct->nRiderCompany);
	pCmd.AddParameter(pStruct->nRNo);
	pCmd.AddParameter(pStruct->nChargeSum);
	pCmd.AddParameter(pStruct->nDeposit);
	pCmd.AddParameter(pStruct->nCarType);

	if(!pCmd.Execute()) return nRet;

	parRet->GetValue(nRet);
	return nRet;
}

void CRcpDlg::OnBnClickedStartMapBtn()
{ 
	m_pStart->ShowMap();
}

void CRcpDlg::OnBnClickedDestMapBtn()
{
	m_pDest->ShowMap();
}

void CRcpDlg::OnCbnSelchangeCouponTypeCombo()
{
	long index = m_cmbCouponType.GetCurSel();

	CString str;
	m_cmbCouponType.GetLBText(index, str);

	for(int i=m_cmbCouponCharge.GetCount(); i>=0; i--)
		m_cmbCouponCharge.DeleteString(i);

	if(str == "퍼센트")
	{
		for(int i=0; i<nPercentCoupon; i++)
			m_cmbCouponCharge.InsertString(i, chPercentPoupon[i]);
	}
	else
	{
		for(int i=0; i<nMoneyCoupon; i++)
			m_cmbCouponCharge.InsertString(i, chMoneyCoupon[i]);
	}


}

void CRcpDlg::OnEnChangeChargeBasicEdit()
{

	m_bDirtyBasicCharge = TRUE;
	CheckDrivingChargeChange();
	RefreshCharge();
}

void CRcpDlg::OnEnChangeChargeAddEdit()
{	
	CheckDrivingChargeChange();
	RefreshCharge(TRUE, FALSE);
}

void CRcpDlg::OnEnChangeChargeDisEdit()
{
	CheckDrivingChargeChange();
	RefreshCharge(TRUE, FALSE);
}

double CRcpDlg::round( double value, int pos )
{

	double temp;

	temp = value * pow( (double)10, pos );  // 원하는 소수점 자리수만큼 10의 누승을 함

	temp = floor( temp + 0.5 );          // 0.5를 더한후 버림하면 반올림이 됨

	temp *= pow( (double)10, -pos );           // 다시 원래 소수점 자리수로

	return temp;

} 
long CRcpDlg::RefreshCharge(BOOL bApplyChargeSum, BOOL bApplyAddCharge)
{
	//g_bana_log->Print("RefreshCharge: %s", this->m_strChargeBasic);

	//if(bApplyAddCharge == TRUE && m_edtStart.GetFocus() != this->GetFocus() && m_edtDest.GetFocus() != this->GetFocus())
	if(bApplyAddCharge == TRUE)
		CheckAddOptionCharge();

	UpdateData(TRUE); //반드시 위 함수 밑에 있어야함

	char buf[20];
 

	m_strChargeBasic.Replace(",", "");
	m_strChargeAdd.Replace(",", "");
	m_strChargeDis.Replace(",", "");
	m_strChargeTrans.Replace(",", "");
	m_strChargeDriving.Replace(",", "");

	if(bApplyAddCharge == FALSE)
	{  
		if(atoi(m_strChargeAdd) > 0)
			m_strChargeAddOption = "사용자추가금입력(" + m_strChargeAdd + ")";
		else
			m_strChargeAddOption = "";

	}


	long nTotal = CheckAddDisCharge();
	m_strChargeSum = itoa(nTotal, buf, 10);
	m_EDT_CHARGE_SUM.pEdit->SetWindowText(LF->GetMyNumberFormat(_ttoi(m_strChargeSum)));
	m_edtChargeSumTotal.SetWindowText(LF->GetMyNumberFormat(nTotal + _ttoi(m_strChargeTrans)));

	if(m_bChangeDrivingCharge == TRUE)
		m_EDT_CHARGE_DRIVING.pEdit->SetWindowText(LF->GetMyNumberFormat(_ttoi(m_strChargeSum)));

	if(m_nCNoChargeDriving > 0)
	{
		m_EDT_CHARGE_DRIVING.pEdit->SetWindowText(LF->GetMyNumberFormat(m_nCNoChargeDriving));
	}

	long nMileageValue=0, nMileageAuto= 0;
	SetMileageData(nMileageAuto, nMileageValue,TRUE);

	CheckCardTax();	
	DisplayChargeInfo(); 
	OnEnChangeChargeDrivingEdit();
	OnEnChangeRiderAutoChargeEdit();

	return nTotal;
}


void CRcpDlg::SetDiscountType(long nGNo, long nDiscountType, long nDiscount )
{
	
	
	//m_bCreditAfterDis = bCreditAfterDis;


	if(nGNo > 0 && nDiscount == 0 && m_pOrder->GetGNo() > 0 )  // 그룹고객 할인할증
	{
		if(m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountType > 0 &&
			m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount != 0 )
		{


			nDiscount = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount;
			m_nDiscountRange = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountRange;
			m_nDiscountType = 100;  // 그룹할인
			m_nDiscountValue = nDiscount;
		}
	}
	else   /// 일반고객 할인 하릊
	{
		m_nDiscountValue = nDiscount;
		m_nDiscountType = nDiscountType;
	}

	if(nDiscount > 0)
	{
		m_nChargeAdd = nDiscount;
		m_nChargeDis = 0;
	}
	else if(nDiscount < 0)
	{
		m_nChargeAdd = 0;
		m_nChargeDis = nDiscount;
	}
	else if(nDiscount == 0)
	{
		m_nChargeAdd = 0;
		m_nChargeDis = 0;
	}
}

long CRcpDlg::CheckAllbaroRoound(long nCharge)
{
	if(LF->IsThisCompany("올바로"))
	{
		long nPer = nCharge % 1000;

		if(nPer > 0)
			nCharge = nCharge + (1000 - nPer);
	}

	return nCharge;
}

long CRcpDlg::CheckAddOptionCharge()
{
	char buffer[10];
	CString strFormat = "";

	//  할인금 -> 할증 넘어갈시 기존할인금 지우고 할증으로 채워야 함. 
	// 안그러면 2군데 채워짐.
	m_strChargeAddOption = "";
	m_strChargeAdd = "";
	m_strChargeDis = "";
	m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);
	m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
	//
	long nAddWeather = 0; // 날씨
	long nAddWeatherSnow = 0;
	long nSlowDiscount = 0;
	long nAddperBoth = 0;
	long nAddperEmergency = 0;
	long nAddperCarType = 0;
	long nAddperTimeCharge = 0;
	long nDisperTimeCharge = 0;
	long nTempTimeCharge = 0;
	long nBasicCharge = 0;
	long nAddperCustomerOption = 0;
	long nSpecialTruckAdd = 0;

	long nAddBranchDiscount = 0, nDisBranchDiscount = 0;
	
	long nSubtractCustomerOption = 0;

	CString sBasicCharge; m_EDT_CHARGE_BASIC.pEdit->GetWindowText(sBasicCharge);
	sBasicCharge.Replace(",", "");

	nBasicCharge = atoi(sBasicCharge);

	
	if(m_pBi->nBothCharge > 0 && m_cmbWayType.GetCurSel() == WAY_TWO)
	{		
		if(m_pBi->nBothCharge == 999) // 사용자정의 타입	
			nAddperBoth = UserDefineBothCharge(nBasicCharge);		
		else
			nAddperBoth = (nBasicCharge * (m_pBi->nBothCharge * 0.01));

		nAddperBoth = CheckAllbaroRoound(nAddperBoth);	

		m_strChargeAddOption += "왕복할인(" + CString(itoa(nAddperBoth, buffer, 10)) + "),";
	}


	if(m_pBi->bWeatherCharge && nBasicCharge > 0 )
	{
		int BIGBIKE = 1;
		switch(GetCarTypeNew())
		{
		case CAR_AUTO:
		case CAR_BIGBIKE:

			if(m_pBi->nBikeAddWeather > 0 && m_pBi->nBikeAddWeather <= 300)
				nAddWeather = nBasicCharge * m_pBi->nBikeAddWeather / 100;
			else if(m_pBi->nBikeAddWeather > 300 )
				nAddWeather = m_pBi->nBikeAddWeather;				
			break;
		case CAR_DAMA:
			if(m_pBi->nDamaAddWeather > 0 && m_pBi->nDamaAddWeather <= 300)
				nAddWeather = nBasicCharge * m_pBi->nDamaAddWeather / 100;
			else if(m_pBi->nDamaAddWeather > 300 )
				nAddWeather = m_pBi->nDamaAddWeather;				
			break;
		case CAR_LABO:
			if(m_pBi->nLaboAddWeather > 0 && m_pBi->nLaboAddWeather <= 300)
				nAddWeather = nBasicCharge * m_pBi->nLaboAddWeather / 100;
			else if(m_pBi->nLaboAddWeather > 300 )
				nAddWeather = m_pBi->nLaboAddWeather;				
			break;
		case CAR_VAN:
			if(m_pBi->nVanAddWeather > 0 && m_pBi->nVanAddWeather <= 300)
				nAddWeather = nBasicCharge * m_pBi->nVanAddWeather / 100;
			else if(m_pBi->nVanAddWeather > 300 )
				nAddWeather = m_pBi->nVanAddWeather;				
			break;
		case CAR_TRUCK:
			if(m_pBi->nTruckAddWeather > 0 && m_pBi->nTruckAddWeather <= 300)
				nAddWeather = nBasicCharge * m_pBi->nTruckAddWeather / 100;
			else if(m_pBi->nTruckAddWeather > 300 )
				nAddWeather = m_pBi->nTruckAddWeather;				
			break;
		}

		nAddWeather = CheckAllbaroRoound(nAddWeather);

		if(nAddWeather > 0)
			m_strChargeAddOption += "우천할증(" + CString(itoa(nAddWeather, buffer, 10)) + "),";
	}


	if(m_pBi->bWeatherChargeSnow && nBasicCharge > 0 )
	{
		int BIGBIKE = 1;
		switch(GetCarTypeNew())
		{
		case CAR_AUTO:
		case CAR_BIGBIKE:

			if(m_pBi->nBikeAddWeatherSnow > 0 && m_pBi->nBikeAddWeatherSnow <= 300)
				nAddWeatherSnow = nBasicCharge * m_pBi->nBikeAddWeatherSnow / 100;
			else if(m_pBi->nBikeAddWeatherSnow > 300 )
				nAddWeatherSnow = m_pBi->nBikeAddWeatherSnow;				
			break;
		case CAR_DAMA:
			if(m_pBi->nDamaAddWeatherSnow > 0 && m_pBi->nDamaAddWeatherSnow <= 300)
				nAddWeatherSnow = nBasicCharge * m_pBi->nDamaAddWeatherSnow / 100;
			else if(m_pBi->nDamaAddWeatherSnow > 300 )
				nAddWeatherSnow = m_pBi->nDamaAddWeatherSnow;				
			break;
		case CAR_LABO:
			if(m_pBi->nLaboAddWeatherSnow > 0 && m_pBi->nLaboAddWeatherSnow <= 300)
				nAddWeatherSnow = nBasicCharge * m_pBi->nLaboAddWeatherSnow / 100;
			else if(m_pBi->nLaboAddWeatherSnow > 300 )
				nAddWeatherSnow = m_pBi->nLaboAddWeatherSnow;				
			break;
		case CAR_VAN:
			if(m_pBi->nVanAddWeatherSnow > 0 && m_pBi->nVanAddWeatherSnow <= 300)
				nAddWeatherSnow = nBasicCharge * m_pBi->nVanAddWeatherSnow / 100;
			else if(m_pBi->nVanAddWeatherSnow > 300 )
				nAddWeatherSnow = m_pBi->nVanAddWeather;				
			break;
		case CAR_TRUCK:
			if(m_pBi->nTruckAddWeatherSnow > 0 && m_pBi->nTruckAddWeatherSnow <= 300)
				nAddWeatherSnow = nBasicCharge * m_pBi->nTruckAddWeatherSnow / 100;
			else if(m_pBi->nTruckAddWeatherSnow > 300 )
				nAddWeatherSnow = m_pBi->nTruckAddWeatherSnow;				
			break;
		}

		nAddWeatherSnow = CheckAllbaroRoound(nAddWeatherSnow);

		if(nAddWeatherSnow > 0)
			m_strChargeAddOption += "눈할증(" + CString(itoa(nAddWeatherSnow, buffer, 10)) + "),";
	}

	if(m_pBi->nBranchDiscount != 0 )   // 지사 할인
	{
		if(m_pBi->nBranchDiscount > 0)
		{
			if(m_pBi->nBranchDiscount > 300)
			{
				nAddBranchDiscount = m_pBi->nBranchDiscount;
				nAddBranchDiscount = CheckAllbaroRoound(nAddBranchDiscount);
				strFormat.Format("지사할증(%d),", m_pBi->nBranchDiscount );
			}
			else
			{
				nAddBranchDiscount = (nBasicCharge * (m_pBi->nBranchDiscount * 0.01));
				nAddBranchDiscount = CheckAllbaroRoound(nAddBranchDiscount);
				strFormat.Format("지사할증(%d%%),", m_pBi->nBranchDiscount );
			}
		}
		else
		{
			if(m_pBi->nBranchDiscount < -300)
			{
				nDisBranchDiscount = m_pBi->nBranchDiscount * -1;
				nDisBranchDiscount = CheckAllbaroRoound(nDisBranchDiscount);
				strFormat.Format("지사할인(%d),", m_pBi->nBranchDiscount );
			}
			else
			{
				nDisBranchDiscount = (nBasicCharge * (m_pBi->nBranchDiscount * -1 * 0.01));
				nDisBranchDiscount = CheckAllbaroRoound(nDisBranchDiscount);
				strFormat.Format("지사할인(%d%%),", m_pBi->nBranchDiscount );
			}
		}
		m_strChargeAddOption += strFormat;
	}

	if(m_pBi->nSlowDiscount != 0 && GetRunTypeNew() == 1 )   // 완급 할인
	{
		if(m_pBi->nSlowDiscount > 0)
		{
			if(m_pBi->nSlowDiscount > 300)
			{
				nSlowDiscount = m_pBi->nSlowDiscount;
				nSlowDiscount = CheckAllbaroRoound(nSlowDiscount);
				strFormat.Format("완급할증(%d),", m_pBi->nSlowDiscount );
			}
			else
			{
				nSlowDiscount = (nBasicCharge * (m_pBi->nSlowDiscount * 0.01));
				nSlowDiscount = CheckAllbaroRoound(nSlowDiscount);
				strFormat.Format("완급할증(%d%%),", m_pBi->nSlowDiscount );
			}
		}
		else
		{
			if(m_pBi->nSlowDiscount < -300)
			{
				nSlowDiscount = m_pBi->nSlowDiscount * -1;
				nSlowDiscount = CheckAllbaroRoound(nSlowDiscount);
				strFormat.Format("완급할인(%d),", m_pBi->nSlowDiscount );
			}
			else
			{
				nSlowDiscount = (nBasicCharge * (m_pBi->nSlowDiscount * -1 * 0.01));
				nSlowDiscount = CheckAllbaroRoound(nSlowDiscount);
				strFormat.Format("완급할인(%d%%),", m_pBi->nSlowDiscount );
			}
		}
		m_strChargeAddOption += strFormat;
		strFormat = "";
	}

	if(m_nCNoDiscount == 0) //특정고객 요금 할인 걸어놓은거
	{
		strFormat = "";
			if( 
			(m_nChargeAdd > 0 || m_nChargeDis < 0) && 
			( m_nDiscountType == 0 || m_nDiscountType == 1))
		{
			if(m_nDiscountType == 0 && m_nChargeAdd > 0 && m_nChargeAdd <= 100)
			{			
				nAddperCustomerOption = nBasicCharge * (m_nChargeAdd * 0.01);	
				nAddperCustomerOption = CheckAllbaroRoound(nAddperCustomerOption);
				strFormat.Format("고객할증(%d%%),", m_nChargeAdd );
			}
			else if(m_nDiscountType == 0 &&  m_nChargeDis < 0 && m_nChargeDis >= -100)
			{			
				nSubtractCustomerOption = nBasicCharge * (m_nChargeDis * -1 * 0.01);	
				nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);			
				strFormat.Format("고객할인(%d%%),", 	m_nChargeDis * -1);						
			}
			else if( m_nDiscountType == 1 &&  m_nChargeAdd > 100 )
			{			
				nAddperCustomerOption = m_nChargeAdd;
				nAddperCustomerOption = CheckAllbaroRoound(nAddperCustomerOption);	
				strFormat.Format("고객할증(%s),", LF->GetMyNumberFormat(	m_nChargeAdd));			
			}			
			else if( m_nDiscountType == 1 && m_nChargeDis < -100 )
			{			
				nSubtractCustomerOption = m_nChargeDis * -1;		
				nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);	
				strFormat.Format("고객할인(%s),", LF->GetMyNumberFormat(	m_nChargeDis));						
			}
			m_strChargeAddOption += strFormat;

		}
		else if(m_nDiscountType > 1 && m_nDiscountType <= 5 )  // 2 A 3 B 4C 5 D
		{
				/*SELECT * 
				FROM ChargeSectionType
				where nCompany = 10
				and nValueType = 0  0 할인 1 쿠폰 2 마일리지 
				and nClass = 1  -- a, b, c, d*/
			int DISCOUNT = 0;
			long nChargeDis = 0;  
			nChargeDis = LU->GetChargeSectionValue(nBasicCharge, DISCOUNT, m_nDiscountType - 2, 0);  //0  디스카운트 1 쿠폰
			if(nChargeDis != 0)
			{
				if(nChargeDis > 0)
				{
					nAddperCustomerOption = nChargeDis;
					nAddperCustomerOption = CheckAllbaroRoound(nAddperCustomerOption);	
					strFormat.Format("고객할증(%s),", LF->GetDiscountType(	m_nDiscountType));
				}
				else 
				{
					nSubtractCustomerOption = nChargeDis * -1;
					nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);	
					strFormat.Format("고객할인(%s),", LF->GetDiscountType(	m_nDiscountType));
				}
				m_strChargeAddOption += strFormat;
			}
			
		}
		else if(m_nDiscountType == 100)  // 그룹할증
		{
			if(nBasicCharge > m_nDiscountRange )
			{

				if(m_nDiscountType == 100 && m_nChargeAdd > 0 && m_nChargeAdd <= 100)
				{			
					nAddperCustomerOption = nBasicCharge * (m_nChargeAdd * 0.01);	
					nAddperCustomerOption = CheckAllbaroRoound(nAddperCustomerOption);			
					strFormat.Format("그룹할증(%d%%),", m_nChargeAdd );
				}
				else if(m_nDiscountType == 100 &&  m_nChargeDis < 0 && m_nChargeDis >= -100)
				{			
					nSubtractCustomerOption = nBasicCharge * (m_nChargeDis * -1 * 0.01);
					nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);					
					strFormat.Format("그룹할인(%d%%),", 	m_nChargeDis * -1);						
				}
				else if( m_nDiscountType == 100 &&  m_nChargeAdd > 100 )
				{			
					nAddperCustomerOption = m_nChargeAdd;
					nAddperCustomerOption = CheckAllbaroRoound(nAddperCustomerOption);
					strFormat.Format("그룹할증(%s),", LF->GetMyNumberFormat(	m_nChargeAdd));			
				}			
				else if( m_nDiscountType == 100 && m_nChargeDis < -100 )
				{			
					nSubtractCustomerOption = m_nChargeDis * -1;
					nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);
					strFormat.Format("그룹할인(%s),", LF->GetMyNumberFormat(	m_nChargeDis));						
				}
				m_strChargeAddOption += strFormat;
			}
		}		
	}
	else
	{
		if(m_nCNoDiscount <= 100)
		{
			nSubtractCustomerOption += nBasicCharge * (m_nCNoDiscount * 0.01);
			nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);
			strFormat.Format("요금할인(%d%%),", m_nCNoDiscount );
		}
		else
		{
			nSubtractCustomerOption += m_nCNoDiscount;
			nSubtractCustomerOption = CheckAllbaroRoound(nSubtractCustomerOption);
			strFormat.Format("요금할인(%d),", m_nCNoDiscount );
		}

		m_strChargeAddOption += strFormat;
	}
	
	if(m_pBi->nEmergencyCharge > 0 && 
		(GetRunTypeNew() == RUN_FAST || GetRunTypeNew() == RUN_VERY_FAST))
		//( m_cmbRunType.GetCurSel() == RUN_FAST || m_cmbRunType.GetCurSel() == RUN_VERY_FAST) )
	{		  

		if(m_pBi->nEmergencyCharge == 999) // 사용자정의 타입
		{
			nAddperEmergency = UserDefineEmergencyCharge(nBasicCharge, nAddperBoth);
		}
		else if(m_pBi->nEmergencyCharge <= 300)
			nAddperEmergency = (atoi(sBasicCharge) * (m_pBi->nEmergencyCharge * 0.01));
		else
			nAddperEmergency = m_pBi->nEmergencyCharge;

 
		nAddperEmergency = CheckAllbaroRoound(nAddperEmergency);

		m_strChargeAddOption += "긴급요금(" + CString(itoa(nAddperEmergency, buffer, 10)) + "),";
	}

	if(LF->IsCarTypeTruck(GetCarTypeNew()))  //카고
	{
		int cargo_type = 0;

		if(m_chkCargoJabara.GetCheck()) cargo_type = CARGO_JABARA;
		else if(m_chkCargoLift.GetCheck()) cargo_type = CARGO_LIFT;
		else if(m_chkCargoWingBody.GetCheck()) cargo_type = CARGO_WING_BODY;
		else if(m_chkCargoLiftWing.GetCheck()) cargo_type = CARGO_LIFT_WING;
		else if(m_chkCargoFreezer.GetCheck()) cargo_type = CARGO_FREEZER;

		if(cargo_type > 0) {
			MAP_SPECIAL_TRUCK_CHARGE::iterator it = g_special_truck_charge.find(make_pair(m_pBi->nCompanyCode, GetCarTypeNew()));

			if(it != g_special_truck_charge.end()) {
				if(cargo_type == CARGO_JABARA) {
					nSpecialTruckAdd = it->second.jabara_add;
					strFormat.Format("자바라할증(%s),", LF->GetMyNumberFormat(nSpecialTruckAdd));	
				}
				else if(cargo_type == CARGO_LIFT) {
					nSpecialTruckAdd = it->second.lift_add;
					strFormat.Format("리프트할증(%s),", LF->GetMyNumberFormat(nSpecialTruckAdd));	
				}
				else if(cargo_type == CARGO_WING_BODY) {
					nSpecialTruckAdd = it->second.wing_body_add;
					strFormat.Format("윙바디할증(%s),", LF->GetMyNumberFormat(nSpecialTruckAdd));	
				}
				else if(cargo_type == CARGO_LIFT_WING) {
					nSpecialTruckAdd = it->second.lift_wing_add;
					strFormat.Format("리프트윙할증(%s),", LF->GetMyNumberFormat(nSpecialTruckAdd));	
				}
				else if(cargo_type == CARGO_FREEZER) {
					nSpecialTruckAdd = it->second.freezer_add;
					strFormat.Format("냉동할증(%s),", LF->GetMyNumberFormat(nSpecialTruckAdd));	
				}
				m_strChargeAddOption += strFormat;
			}
		}			
	}

	switch(GetCarTypeNew())
	{
	case CAR_DAMA:
		nAddperCarType = m_pBi->nDamasPay <= 300 ? (atoi(sBasicCharge) * (m_pBi->nDamasPay * 0.01)) : m_pBi->nDamasPay;
		nAddperCarType = CheckAllbaroRoound(nAddperCarType);
		m_strChargeAddOption += "다마스추가(" + CString(itoa(nAddperCarType, buffer, 10)) + "),";
		break;
	case CAR_LABO:
		if(m_pBi->nLaboChargeType == LABO_CHARGE_VAN)
		{
			nAddperCarType = m_pBi->nBonggoPay <= 300 ? (atoi(sBasicCharge) * (m_pBi->nBonggoPay * 0.01)) : m_pBi->nBonggoPay;
			nAddperCarType = CheckAllbaroRoound(nAddperCarType);
			m_strChargeAddOption += "라보요금을 봉고(밴)적용(" + CString(itoa(nAddperCarType, buffer, 10)) + ",";
		}
		else if(m_pBi->nLaboChargeType == LABO_CHARGE_DAMAS)
		{
			nAddperCarType = m_pBi->nDamasPay <= 300 ? (atoi(sBasicCharge) * (m_pBi->nDamasPay * 0.01)) : m_pBi->nDamasPay;
			nAddperCarType = CheckAllbaroRoound(nAddperCarType);
			m_strChargeAddOption += "라보요금을 다마스적용(" + CString(itoa(nAddperCarType, buffer, 10)) + ",";
		}
		else
		{
			nAddperCarType = m_pBi->nRaboPay <= 300 ? (atoi(sBasicCharge) * (m_pBi->nRaboPay * 0.01)) : m_pBi->nRaboPay;;
			nAddperCarType = CheckAllbaroRoound(nAddperCarType);
			m_strChargeAddOption += "라보추가금(" + CString(itoa(nAddperCarType, buffer, 10)) + ",";
		}

		break;

	case CAR_VAN:
		nAddperCarType = m_pBi->nBonggoPay <= 300 ? (atoi(sBasicCharge) * (m_pBi->nBonggoPay * 0.01)) : m_pBi->nBonggoPay;
		nAddperCarType = CheckAllbaroRoound(nAddperCarType);
		m_strChargeAddOption += "밴추가금(" + CString(itoa(nAddperCarType, buffer, 10)) + "),";
		break;

	case CAR_TRUCK:
		nAddperCarType = m_pBi->nTruckPay  <= 300 ? (atoi(sBasicCharge) * (m_pBi->nTruckPay * 0.01)) : m_pBi->nTruckPay;
		nAddperCarType = CheckAllbaroRoound(nAddperCarType);
		m_strChargeAddOption += "트럭추가금(" + CString(itoa(nAddperCarType, buffer, 10)) + "),";
		break;

	default:
		break;
	}


	COleDateTime dtOrderInputTime(COleDateTime::GetCurrentTime()), dt(COleDateTime::GetCurrentTime());

	if(IsReserve())
		dtOrderInputTime = GetReserveTime();
	//else  주석 있어야함
	//	dtOrderInputTime = m_dt1;

	/* 이전에 제대로 동작했는지가 의문..
	if(m_pReserveOrderDlg){		
		if(m_pReserveOrderDlg->IsReserve()  )
			dtOrderInputTime = m_pReserveOrderDlg->GetReserveTime();
	}
	else
		dtOrderInputTime = m_dt1;
	*/ 
	nTempTimeCharge = LU->m_pChargeAdd->GetChargeAdd(m_pBi->nCompanyCode,dt.GetDayOfWeek(), 
		LF->GetCarChargeType(GetCarTypeNew()), nBasicCharge, dtOrderInputTime );
  
	if(nTempTimeCharge > 0)
		nAddperTimeCharge = nTempTimeCharge;
	else if(nTempTimeCharge < 0)
		nDisperTimeCharge = nTempTimeCharge;

	nAddperTimeCharge = CheckAllbaroRoound(nAddperTimeCharge);
	nDisperTimeCharge = CheckAllbaroRoound(nDisperTimeCharge);


	if(nAddperTimeCharge > 0)
		m_strChargeAddOption += "시간할증(" + LF->GetMyNumberFormat(nAddperTimeCharge) + "),";
	if(nDisperTimeCharge < 0)
		m_strChargeAddOption += "시간할인(" + LF->GetMyNumberFormat(nDisperTimeCharge) + "),";

	long nTotal = nAddperBoth +  nAddperEmergency + nAddperCarType + nAddperTimeCharge + nAddperCustomerOption + nAddBranchDiscount + nAddWeather + nAddWeatherSnow + nSpecialTruckAdd;
	long nTotalDis = nSubtractCustomerOption + ( nDisperTimeCharge * -1 ) +  nDisBranchDiscount + nSlowDiscount;  // 접수창에는 + 로 표시 

	if(!m_strChargeAddOption.IsEmpty())
		m_strChargeAddOption = m_strChargeAddOption.Left(m_strChargeAddOption.GetLength() - 1);

	
	//m_strChargeAdd = LF->GetMyNumberFormat(nAddperBoth +  nAddperEmergency + nAddperCarType);

	
	if(nTotal > 0)
	{
		if(nTotal / 1000.0 != 0 && m_pBi->bAddDisChargeRound)
			nTotal = round(nTotal, -3);

		m_EDT_CHARGE_ADD.pEdit->SetWindowText(LF->GetMyNumberFormat(nTotal));
	}
	

	if(nTotalDis > 0)
	{
		if(nTotalDis / 1000.0 != 0 && m_pBi->bAddDisChargeRound)
			nTotalDis = round(nTotalDis, -3);

		m_EDT_CHARGE_DIS.pEdit->SetWindowText(LF->GetMyNumberFormat(nTotalDis));
		//RefreshBasicCharge(TRUE, FALSE);
	}
	return nTotal;
}



BOOL CRcpDlg::CheckChargeRound()
{

	long nChargeBasic	= GetStringChargeToNumber(m_strChargeBasic);
	long nChargeDis		= GetStringChargeToNumber(m_strChargeDis);
	long nChargeAdd		= GetStringChargeToNumber(m_strChargeAdd);
	long nChargeSum	= atoi(m_strChargeSum);

	long nCalChargeBasic = 0, nCalChargeDis = 0, nCalChargeAdd = 0,
		nCalChargeSum = 0;
	CString sDefaultMsg = "천원이하의 금액입니다.";
	CString sErrorMsg = "";

	if( nChargeBasic / 100.0 != 0 )
		nCalChargeBasic = round(nChargeBasic, -3);	
	if( nChargeDis / 100.0 != 0 )
		nCalChargeDis = round(nChargeDis, -3);	
	if( nChargeAdd / 100.0 != 0 )
		nCalChargeAdd = round(nChargeAdd, -3);	

	nCalChargeSum = nCalChargeBasic + nCalChargeAdd -  nCalChargeDis;

	if( nChargeBasic + nChargeAdd - nChargeDis == nChargeSum )
		return TRUE;



	if(nChargeBasic != nCalChargeBasic)
	{
		sErrorMsg.Format("%s %s\n\r\n\r수정(반올림)하시면서 등록하시겠습니까?", "기본금",sDefaultMsg);
		if( MessageBox(sErrorMsg, "확인", MB_YESNO ) == IDYES)
		{
			m_strChargeBasic = LF->GetMyNumberFormat(nCalChargeBasic);
			m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic);
			return TRUE;
		}
		return FALSE;
	}

	if(nChargeAdd != nCalChargeAdd)
	{
		sErrorMsg.Format("%s %s\n\r\n\r수정(반올림)하시면서 등록하시겠습니까?", "추가금",sDefaultMsg);
		if( MessageBox(sErrorMsg, "확인", MB_YESNO ) == IDYES)
		{
			m_strChargeAdd = LF->GetMyNumberFormat(nCalChargeAdd);
			m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);
			return TRUE;
		}
		return FALSE;
	}

	if(nChargeDis != nCalChargeDis)
	{
		sErrorMsg.Format("%s %s\n\r\n\r수정(반올림)하시면서 등록하시겠습니까?", "할인금",sDefaultMsg);
		if( MessageBox(sErrorMsg, "확인", MB_YESNO ) == IDYES)
		{
			m_strChargeDis = LF->GetMyNumberFormat(nCalChargeDis);
			m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
			return TRUE;
		}
		return FALSE;
	}

	if(nCalChargeSum != nChargeSum)
	{
		sErrorMsg.Format("%s %s\n\r\n\r수정(반올림)하시면서 등록하시겠습니까?", "정산금",sDefaultMsg);
		if( MessageBox(sErrorMsg, "확인", MB_YESNO ) == IDYES)
		{
			m_strChargeSum = LF->GetMyNumberFormat(nCalChargeSum);
			m_EDT_CHARGE_SUM.pEdit->SetWindowText(m_strChargeSum);
			return TRUE;
		}
		return FALSE;
		
	}
	return FALSE;



}
long  CRcpDlg::CheckAddDisCharge(long nChargeInpuBasic)
{
	long nTotal = 0;
	long nDisPer = 0;  
	long nAddPer = 0;

	long nChargeBasic = GetStringChargeToNumber(m_strChargeBasic);
	long nChargeDis = GetStringChargeToNumber(m_strChargeDis);
	long nChargeAdd = GetStringChargeToNumber(m_strChargeAdd);
	/*
	if(nChargeInpuBasic > 0)
	nChargeBasic = nChargeInpuBasic;

	if(nChargeDis< MINPAY_BOUND && m_nDiscountRange <= nChargeBasic  ) 
	nDisPer = nChargeBasic * nChargeDis * 0.01;
	else if (nChargeDis< MINPAY_BOUND )
	nDisPer = 0;
	else
	nDisPer = nChargeDis;



	if(nChargeAdd < MINPAY_BOUND && m_nDiscountRange <= nChargeBasic  ) 
	nAddPer = nChargeBasic * nChargeAdd * 0.01;
	else if(nChargeAdd < MINPAY_BOUND  ) 
	nAddPer = 0;
	else
	nAddPer = nChargeAdd;
	*/



	nDisPer = nChargeDis;
	// nDisPer >999 타이핑시 0 으로 돌아감
	//if(nDisPer / 1000.0 !=0 && nDisPer >999 && m_pBi->bAddDisChargeRound )
	//{
	//	nDisPer = round(nDisPer, -3);
	//	m_strChargeDis = LF->GetMyNumberFormat(nDisPer);
	//	m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
	//}



	nAddPer = nChargeAdd;
	/*if(nAddPer / 1000.0 !=0 && nAddPer > 999 && m_pBi->bAddDisChargeRound )
	{
	nAddPer = round(nAddPer, -3);
	m_strChargeAdd = LF->GetMyNumberFormat(nAddPer);
	m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);

	}*/


	nTotal = nChargeBasic + nAddPer - nDisPer; 


	if( (nAddPer != 0 || nDisPer != 0) && m_pBi->bAddDisChargeRound   )
		nTotal = round(nTotal, -3);	

	return nTotal;
}

long CRcpDlg::UserDefineEmergencyCharge(long nBasicCharge, long nAddWayCharge)
{

	long nEmergecyCharge = 0;
	if(m_pBi)
	{
		if(m_pBi->nCompanyCode == QUICK_CALL_7700)
			nEmergecyCharge = UserDefineEmergencyQuickCall(nBasicCharge + nAddWayCharge);
		else if(m_pBi->nCompanyCode == DEMO_10)
			nEmergecyCharge = UserDefineEmergencyQuickCall(nBasicCharge);


	}

	

	return nEmergecyCharge;

}
long CRcpDlg::UserDefineBothCharge(long nBasicCharge)
{
	long nBothCharge = 0;
	if(m_pBi)
	{
		if(m_pBi->nCompanyCode == QUICK_CALL_7700)
			nBothCharge = UserDefinenBothQuickCall(nBasicCharge );	
		else if(m_pBi->nCompanyCode == DEMO_10)
			nBothCharge = UserDefinenBothQuickCall(nBasicCharge);
	}
	return nBothCharge;
}

LONG CRcpDlg::UserDefineEmergencyQuickCall(long nBasicCharge)
{

	if(nBasicCharge < 7000)		  return 0;
	else if(nBasicCharge == 7000) return  5000;
	else if( nBasicCharge >= 8000 && nBasicCharge < 10000)	return  6000;
	else if( nBasicCharge >= 10000 && nBasicCharge < 13000)	return  7000;
	else if( nBasicCharge >= 13000 && nBasicCharge < 15000)	return  8000;
	else if( nBasicCharge >= 15000 && nBasicCharge < 16000)	return  9000;
	else if( nBasicCharge >= 16000 && nBasicCharge < 21000)	return  10000;
	else if( nBasicCharge >= 21000 && nBasicCharge < 23000)	return  11000;
	else if( nBasicCharge >= 23000 && nBasicCharge < 25000)	return  12000;
	else if( nBasicCharge >= 25000 && nBasicCharge < 27000)	return  13000;
	else if( nBasicCharge >= 27000 && nBasicCharge < 29000)	return  14000;
	else if( nBasicCharge >= 29000 && nBasicCharge < 37000) return  15000;
	else if( nBasicCharge >= 37000 )			            return  16000;
	else													return  8000;
	
	return 0;

}

LONG CRcpDlg::UserDefinenBothQuickCall(long nBasicCharge)
{

	long nUserDefineBothCharge = 0;
	float fTemp = 0.0;
	if( nBasicCharge >= 80000 )
	{
		nUserDefineBothCharge = nBasicCharge / 2;
		nUserDefineBothCharge = round(nUserDefineBothCharge, -3);	
	}
	else
	{
		//fTemp = ( nBasicCharge / 10000.0 ) * 7.0;
		
		//nUserDefineBothCharge =  round(fTemp,2);
		//nUserDefineBothCharge =  nUserDefineBothCharge * 1000; 
		//nUserDefineBothCharge =  round(nUserDefineBothCharge,-3);


		fTemp = nBasicCharge * 0.7;
		nUserDefineBothCharge =  round(fTemp,-3);


	}
		

	return nUserDefineBothCharge;

}


void CRcpDlg::DisplayChargeInfo(BOOL bHasData)
{
	CString strTemp = "";
	CString strTop = "", strBottom = "";

	if(m_strChargeGeneralOption.Find("처리중") >= 0)
	{
		CString strCNS = "";
		if(m_fDirectDistance > 0)
		{
			int distance = m_fDirectDistance * 100;
			strCNS.Format("%.1fKm", (float)distance / 100); 

			if(IsUseDirectDistance())
				strCNS = "직선" + strCNS;

			m_strChargeGeneralOption.Replace("처리중", strCNS);
		}
	}

	if(bHasData == TRUE)  
	{
		strTemp = ""; 
		strTemp += "<Border Padding='0'>";
		strTemp +=  "<StackPanel TextBlock.FontFamily='Microsoft YaHei'>";  

		/*
		if(m_strChargeGeneralOption.IsEmpty() == FALSE)
		m_strChargeGeneralOption = "[" + m_strChargeGeneralOption + "]";
		if(m_strChargeAddOption.IsEmpty() == FALSE)
		m_strChargeAddOption = "[" + m_strChargeAddOption + "]";
		*/

		strTemp += "   <TextBlock Padding='0'><Run Foreground='blue' FontWeight='Normal'>" + m_strChargeGeneralOption + "</Run></TextBlock>";
		strTemp += "   <TextBlock Padding='0'><Run Foreground='red' FontWeight='Normal'>" + m_strChargeAddOption+ "</Run></TextBlock>";

		strTemp += "</StackPanel>";  
		strTemp += "</Border>" ;
	}
	else
	{
		strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='left' VerticalAlignment='center'>";

		CPOIUnit *pStart = m_pStart->GetPOI();
		CPOIUnit *pDest = m_pDest->GetPOI();

		if(pStart == NULL || pDest == NULL)
		{
			m_strChargeGeneralOption = "기본요금 적용중";
			strTemp += "<Run Foreground='blue' FontWeight='Normal'>" + m_strChargeGeneralOption + "</Run>";
			strTemp += "</TextBlock>";			
		}

		strTemp = "";
		strTemp += "<Border Padding='0'>";
		strTemp +=  "<StackPanel TextBlock.FontFamily='Microsoft YaHei'>"; 

		CString strStartDest = "", strBasicCharge = "", strCNS = "";

		strStartDest = m_pStart->GetDisplayDong() + "->" + m_pDest->GetDisplayDong();
		strBasicCharge = m_pCharge->GetDistanceLableView();

		if(m_fDirectDistance <= 0)
			strCNS = "처리중";
		else
		{
			int distance = m_fDirectDistance * 100;
			strCNS.Format("%.1fKm", (float)distance / 100);

			if(IsUseDirectDistance())
				strCNS = "직선" + strCNS;
		}

		int nIndex = m_CMB_CHARGE_TYPE.pCombo->GetCurSel();

		CString strCarType = LF->GetCarTypeFromLong(GetCarTypeNew(), TRUE);
		CString strChargeType; 	m_CMB_CHARGE_TYPE.pCombo->GetLBText(m_CMB_CHARGE_TYPE.pCombo->GetCurSel(), strChargeType);

		strStartDest.Replace("<", ",");
		m_strChargeGeneralOption = "[" + strCNS + ", " + strStartDest + ", " + strBasicCharge + "]";
		CString strTop = "<Run Foreground='blue' FontWeight='Normal'>" + m_strChargeGeneralOption + "</Run>";

		CString strBottom = "";

		if(m_strChargeAddOption.IsEmpty())
			m_strChargeAddOption = "추가요금 없음";

		m_strChargeAddOption = "[" + m_strChargeAddOption + "]";
		m_strChargeAddOption.Replace("[[", "[");
		m_strChargeAddOption.Replace("]]", "]");

		strBottom = "<Run Foreground='red' FontWeight='Normal'>" + m_strChargeAddOption + "</Run>";

		strTemp += "   <TextBlock Padding='0'>" + strTop + "</TextBlock>";
		strTemp += "   <TextBlock Padding='0'>" + strBottom+ "</TextBlock>";

		strTemp += "</StackPanel>"; 
		strTemp += "</Border>" ;
	}

	//m_stcChargeViaBet.SetMarkupText("aa");
	m_stcChargeViaBet.SetMarkupText(strTemp);

}

BOOL CRcpDlg::IsUseDirectDistance()
{
	return m_pBi->bUseDirectDistance || m_chkDirectDistance.GetCheck();
	//return AfxGetApp()->GetProfileInt("SearchPOIDlg", "UseDirectDistance", 0);
}


BOOL CRcpDlg::GetRouteDistance(BOOL bShowMap, BOOL bViaApply,BOOL bChargeCalculate, int  nModifyPoiConfirmCharge)
{
	if(m_ci.m_bNotUseCNS == TRUE &&  !m_pBi->bDistanceCharge )
		return FALSE;

	if(bRouteSend && ( m_pStart == m_pCNSCheckStart && m_pDest == m_pCNSCheckDest)  )
		return FALSE;

	if(!m_pStart->GetPOI() || !m_pDest->GetPOI())
		return FALSE;

	if(IsUseDirectDistance() && bShowMap == FALSE)
	{
		bRouteSend = TRUE;
		double fDistance = LF->GetDistanceMeter(m_pStart->GetPosX(), m_pStart->GetPosY(),
				m_pDest->GetPosX(), m_pDest->GetPosY());
		fDistance = fDistance / 1000;
		double* pfDistance = new double;
		*pfDistance = fDistance;
		if(bChargeCalculate == FALSE ) // 거리로 계산을 하지 않으려면 
			nModifyPoiConfirmCharge = 100;
		PostMessage(WM_USER + 6000, (WPARAM)pfDistance,(LPARAM)nModifyPoiConfirmCharge);
		return TRUE;
	}

	CString strStartSido = "", strDestSido = "";
	strStartSido = m_pStart->GetPOI()->GetSido();
	strDestSido = m_pDest->GetPOI()->GetSido();
	if( strStartSido.GetLength() <= 0 || strStartSido.Compare("NULL") == 0)
		return FALSE;

	if( strDestSido.GetLength() <= 0 || strDestSido.Compare("NULL") == 0)
		return FALSE;
	
	if( m_pStart->GetPosX() <= 10000 || m_pStart->GetPosY() <= 10000 )
		return FALSE;

	if( m_pDest->GetPosX() <= 10000 || m_pDest->GetPosY() <= 10000 )
		return FALSE;


	if(m_pStart->GetPOI() && m_pDest->GetPOI())
	{
		CPoint s, d, v;
		CLogiMapCns *pCNS = LU->GetLogiMapCns();

		pCNS->ClearPos();
		pCNS->AddPos(m_pStart->GetPosX(), m_pStart->GetPosY());
		pCNS->AddPos(m_pDest->GetPosX(), m_pDest->GetPosY());

		CString strStart, strDest;		
		strStart = m_pStart->GetDisplayDong();
		strDest = m_pDest->GetDisplayDong();

		pCNS->SetDebugInfo(strStart, strDest, m_pStart->GetPOI()->GetDongID() ,m_pStart->GetPOI()->GetID(), 
			m_pDest->GetPOI()->GetDongID() ,m_pDest->GetPOI()->GetID(), 0, m_pBi->nCompanyCode);
		bRouteSend = TRUE;
		m_pCNSCheckStart = m_pStart;
		m_pCNSCheckDest = m_pDest;

		//pCNS->GetRouteDistance(this, bShowMap, bViaApply,bChargeCalculate, nModifyPoiConfirmCharge);

		BOOL bMotor = (GetCarTypeNew() == CAR_AUTO || GetCarTypeNew() == CAR_BIGBIKE ? TRUE : FALSE);
		
		pCNS->GetRouteDistance(this, bShowMap, FALSE, bChargeCalculate, nModifyPoiConfirmCharge, TRUE, m_pBi->nCompanyCode, bMotor);
		m_edtCNS.SetWindowText("검색중..");
		return TRUE;
	}
	else
	{
		g_bana_log->Print("출발지 도착지의 설정이 빠져있습니다.");
		//MessageBox("출발지 도착지의 설정이 빠져있습니다. ", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
}



BOOL CRcpDlg::IsNoGroupCharge(long nGroupNo)
{
	if(m_pBi->bNoGroupCharge)
		return TRUE;

	if(nGroupNo > 0)
	{
		ST_CUSTOMER_GROUP_INFOMATION *pGroupIfno = 	m_cg.GetGroupData(nGroupNo);
		if(pGroupIfno == NULL)
			return FALSE;

		if(pGroupIfno->bNoGroupCharge )
			return TRUE;		
	}


	return FALSE;

}


void CRcpDlg::OnBnClickedConsignViewBtn()
{

	AddTran();

	//IsConsignApply(TRUE);

}

void CRcpDlg::AddTran()
{

	if(m_nInitItem < 1 && m_nTransID > 0) //오더는 입력이 안되었는데 탁송정보가 먼저 등록되어있는경우
	{
		MessageBox("탁송정보가 입력되어 있습니다\r\n 오더 등록후 확인 하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_pBi == NULL)
		return;

	long nCompany =  m_pBi->nCompanyCode;
	
	LU->OpenTranDlg(m_nInitItem, nCompany);

	//CTransInfoDlg dlg;
	//dlg.m_nTNo = m_nInitItem;

//	BRANCH_INFO *pBi = NULL;

	/*long nSel = m_cmbBranch.GetCurSel();
	if(m_cmbBranch.GetCurSel() == -1)
		pBi = m_pBi;
	else
		pBi = m_ba.GetAt(nSel);

	long nCompany = pBi->nCompanyCode;
	if(nCompany <= 0)
		nCompany = LF->GetCurBranchInfo()->nCompanyCode;*/

//	dlg.m_nCompany = nCompany;
//
//	char buffer[20];
//
//	if(m_nInitItem > 0)
//	{
//		CMkRecordset pRs(m_pMkDb);
//		CMkCommand pCmd(m_pMkDb, "select_trans_info");
//
//
//		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nInitItem);
//		//pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTransID);
//		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
//
//		if(!pRs.Execute(&pCmd)) return;
//
//
//		if(pRs.GetRecordCount() == 0 )
//		{
//			MessageBox("탁송정보가 없습니다", "확인", MB_ICONINFORMATION);
//			return;
//		}
//
//		if(pRs.GetRecordCount() != 0) 
//		{
//			CString sStart, sDest, sExpressName, sExpressNumber, sEtc, sName, sItemNo;
//			COleDateTime dtDeparture, dtArrival, dtRegister;
//
//			pRs.GetFieldValue("sStart", sStart);
//			pRs.GetFieldValue("sDest", sDest);
//			pRs.GetFieldValue("sExpressName", sExpressName);
//			pRs.GetFieldValue("sExpressNumber", sExpressNumber);
//			pRs.GetFieldValue("sEtc", sEtc);
//			pRs.GetFieldValue("sName", sName);
//			pRs.GetFieldValue("sItemNo", sItemNo);
//			pRs.GetFieldValue("dtDeparture", dtDeparture);
//			pRs.GetFieldValue("dtArrival", dtArrival);
//			pRs.GetFieldValue("dtRegister", dtRegister);
//
//			dlg.m_bNew = FALSE;
//
//			dlg.m_sStart = sStart;
//			dlg.m_sDest = sDest;
//			dlg.m_sExpressName = sExpressName;
//			dlg.m_sExpressNumber = sExpressNumber;
//			dlg.m_sEtc = sEtc;
//			dlg.m_sName = sName;
//			dlg.m_sItemNo = sItemNo;
//			dlg.m_dtDeparture = dtDeparture;
//			dlg.m_dtArrival = dtArrival;
//			dlg.m_dtRegister = dtRegister;
//
//			dlg.m_sTitle = "탁송정보 - " + CString(itoa(m_nInitItem, buffer, 10));
//		}
//		else 
//			dlg.m_sTitle = "탁송정보";
//
//	}	
//
//	if(dlg.DoModal() == IDOK)
//	{
////		m_chkTransOrder.SetCheck(TRUE);
//		m_nTransID = dlg.m_nReturn;
//	}
}

BOOL CRcpDlg::IsConsignApply(BOOL bConsignButton)
{
	if(m_pOrder == NULL)
	{
		if(bConsignButton) 	MessageBox("의뢰지를 입력하여주세요", "확인",MB_ICONINFORMATION);
		return FALSE;
	}

	if(m_pStart == NULL || m_pDest == NULL ||m_pStart->GetPOI() == NULL || m_pDest->GetPOI() == NULL)
	{
		if(bConsignButton) 	MessageBox("출발지 도착지의 지명을 입력하여주세요", "확인",MB_ICONINFORMATION);
		return FALSE;
	}


	if(m_pStart->GetPOI()->GetSido().GetLength() <= 0 || m_pDest->GetPOI()->GetSido().GetLength() <= 0)
	{
		if(bConsignButton) 	MessageBox("출발지 도착지의 지명을 입력하여주세요", "확인",MB_ICONINFORMATION);
		return FALSE;
	}

	CPOIUnit *pPoi = m_pDest->GetPOI();
	CString sDestSido = pPoi->GetSido();

	if(m_nConsignTNo > 0)
	{

	}
	else
	{
		if(! LU->IsConsignCity(sDestSido) )
			return FALSE;

		if(m_nConsignTNo <= 0 && MessageBox("탁송연계를 하시겠습니까?", "확인", MB_YESNO) == IDNO)
			return FALSE;
	}	

	m_pConsignLinkDlg = LU->OpenConsignLinkDlg(m_nInitItem, m_pBi->nCompanyCode, m_pStart, m_pDest, m_nConsignTNo, m_nTerminalWayID, m_strConsignCity,  this);

	return TRUE;
}

long CRcpDlg::GetCarTypeChargeTemp()
{
	long nCarType = 0;

	long nTempCarType = GetCarTypeNew();

	if(nTempCarType == CAR_LABO)
	{
		if(m_pBi->nLaboChargeType == LABO_CHARGE_DAMAS)
			nCarType = CAR_DAMA;
		else if(m_pBi->nLaboChargeType == LABO_CHARGE_VAN)
			nCarType = CAR_VAN;
		else if(m_pBi->nLaboChargeType == LABO_CHARGE_EACH)
			nCarType = CAR_LABO;
	}
	else
		nCarType = GetCarTypeNew();

	return nCarType;
}

long CRcpDlg::GetSectionCharge(BOOL bMustApply, int nModifyPoiConfirmCharge, BOOL bCashCharge,  BOOL bChargeTypeCelChange )
{
	// GetSectionCharge는 출발지 도착지 엔터 키로 들어오지만 출발지 도착지가 이전꺼와 같은면 튕겨낸다. 
	// bMustApply 는 마우스 BASIC_EDIT 마우스로 포커스 될때만 무조건 요금 검색을 한다. 
	// nModifyPoiConfirmCharge POI 수정후  창을 닫을시 금액이 변경되야할 부분을 상태값
	// 이미 요금조회후 캐쉬에 남아 있는걸로 금액을 표시해준다.
	// GetPreSectionCharge 수정후 닫기 POI 변경후 확인한다.


	//by mksong (2011-03-03 오후 4:46) 
	//to love7310 - 아래 주석처리하면서 창닫을시에 에러발생, choi가 처리한것이 맞음
	//m_pOrder가 NULL이면 이창이 소멸되고 있는것임


	if(m_pOrder == NULL)
		return 0; //choi 

	m_nCNoChargeDriving = 0;
	m_nCNoDiscount = 0;

	long nSumCharge = 0;
	long nCharge = 0, nMemCharge = m_nChargeMemCNo;	
	int nCarType = 0;
	if( m_pOrder->GetGNo() > 0 && ! IsNoGroupCharge(m_pOrder->GetGNo()) )
		nMemCharge = 0; 
	
	 if(LF->GetCurBranchInfo()->bNotMemberCharge )
		 nMemCharge = 0;
	
	
	if(!IsStartDestPoi()) 
		return 0;

	if(LF->IsThisCompany("엔콜") || LF->IsThisCompany("로지"))  /// 엔콜 업체요금 + 긴급 
	{
		if( !m_pCharge->IsSameRunType(m_nRunType) )
		{
			if(!IsPreChangePOI()  && m_pCharge->IsCashCharge())
				m_pCharge->SetCashCharge(FALSE);
		}
	}

	//static DWORD dwTick = GetTickCount() - 1000;

	//if(GetTickCount() - dwTick < 300)
	//{
	//	g_bana_log->Print("GetTickCount() - dwTick < 300 : %f초 return;", GetTickCount() / 1000 );
	//	return;
	//}
	//dwTick = GetTickCount();

	//nCarType = ( m_pBi->bUsePayBonggoFromLabo && GetCarTypeNew() == CAR_LABO ) ? CAR_VAN : GetCarTypeNew() ;
	nCarType = GetCarTypeChargeTemp(); 

 
	if(bCashCharge && IsPreChangePOI() == FALSE && m_pCharge->IsCashCharge()  )  // 한번요금이 검색된 이후에 
	{ 
		nCharge = m_pCharge->GetCashCharge(nMemCharge,m_pStart->GetPOI(), m_pDest->GetPOI(),  m_pOrder->GetGNo(),
			m_pBi,	m_nCNoChargeDriving, m_nCNoDiscount, m_fDirectDistance,m_CMB_CHARGE_TYPE.pCombo->GetCurSel(), 			
			LF->GetCarTypeForCharge(nCarType),
			bChargeTypeCelChange	);

		//g_bana_log->Print("skip CRcpDlg::GetSectionCharge  CashCahrge 실행 ******\n");
		m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat( nCharge));

		return RefreshCharge();
	}


	if(IsPreChangePOI() == FALSE && bMustApply == FALSE )
	{
		if(m_strChargeBasic == "0" || m_strChargeBasic.GetLength() <= 0 || 
			(m_fDirectDistance <= 0 && m_pBi->bDistanceCharge) )
			bMustApply = TRUE;
		else
		{
			if( ! m_pCharge->IsCashCharge() )
			{
				g_bana_log->Print(" CRcpDlg::GetSectionCharge  ! m_pCharge->IsCashCharge() \n");
				/*if(IsEditMode() )
				Sleep(400);*/

				//if(m_nInitItem <= 0)
					GetSectionCharge(TRUE,FALSE, FALSE);
			}
			else
				return RefreshCharge();
			g_bana_log->Print("skip CRcpDlg::GetSectionCharge\n");

			return 0;
		}
	}

	m_bDirtyBasicCharge = FALSE;  
	if( IsPreChangePOI() || bMustApply )
		m_pCharge->RemoveAllData();	

	m_pStart->SetPrePoiFromNowPoi();
	m_pDest->SetPrePoiFromNowPoi();
	m_fDirectDistance = 0;

	COleDateTime dt(COleDateTime::GetCurrentTime());
	g_bana_log->Print(" ***************** GetSectionCharge실행" + dt.Format("%y-%m-%d %H:%M:%S") + "\n\r" );	

	if(m_pBi->bDistanceCharge  )  //동기반 거리요금(선택거리, 거리요금)
	{					
		GetRouteDistance(FALSE, FALSE,TRUE, nModifyPoiConfirmCharge);  ///  OnGetCNSVia OnGetCNS 이동
		return 0;  
	} 
	else
	{
		GetRouteDistance(FALSE, FALSE, FALSE, FALSE );  // 밑에서 return 하기에 단순히 거리만 구해와 텍스트 뿌리기 .. 세번째 인다 bChargeCalculae = FALSE

		long nOldCharge = 0; nOldCharge = GetNowChargeControlAmount();			

		nCharge =  m_pCharge->GetTotalCharge(nMemCharge , 
			m_pStart->GetPOI(), m_pDest->GetPOI(),  m_pOrder->GetGNo(),
			m_pBi,m_nCNoChargeDriving, m_nCNoDiscount, m_fDirectDistance, m_CMB_CHARGE_TYPE.pCombo->GetCurSel(),  
			
			LF->GetCarTypeForCharge(nCarType),
			IsNoGroupCharge(m_pOrder->GetGNo()), m_nRunType);		


		if(  nOldCharge != nCharge && nCharge > 0 ) // 신규든 수정이든 m_nModifyPoiConfirmCharge POI 변경시
		{				
			if(  IsEditMode() && !m_bConsignLink && m_nState != STATE_INTERNET) // 수정시만 POI 변경시 alert....
			{
				// 여기는 거리계산시 금액계산을 하지 말라고 해서 10 DISTANCE 안빼도 됨. 
				// 그러나 거리요금제는 금액계산을 하라고 
				if(ChangePOIConfirmString(nModifyPoiConfirmCharge, nOldCharge, nCharge) == FALSE)	
				{
					RefreshCharge();
					return 0;					 
				}

			}
			if(m_pCharge->IsGroupChargeApply() || m_pCharge->IsMemberChargeApply())
			{
				m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);				
			}
			else
			{
				m_CMB_CHARGE_TYPE.pCombo->SetCurSel(m_pCharge->m_nChargeType  == TYPE_GNO ? 0 : m_pCharge->m_nChargeType );
				m_chkSaveCharge.SetCheck(FALSE);
			}



		}	
	}
	m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat( nCharge));
	nSumCharge = RefreshCharge(TRUE);
	RefreshProperCharge();
	return nSumCharge;
}

void CRcpDlg::RefreshProperCharge()
{
	m_edtProperCharge1.SetWindowText("");
	m_edtProperCharge2.SetWindowText("");

	CPOIUnit *pStart = m_pStart->GetPOI();
	CPOIUnit *pDest = m_pDest->GetPOI();
 
	if(!pStart  || !pDest)
		return;

	long nProper1 = 0, nProper2 = 0;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_proper_charge");
	cmd.AddParameter(pStart->GetDongID());
	cmd.AddParameter(pDest->GetDongID()); 
	cmd.AddParameter(GetCarTypeNew());  

	if(!rs.Execute(&cmd))
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		if(i == 0)
			rs.GetFieldValue("nCharge", nProper1);
		else if(i == 1)
			rs.GetFieldValue("nCharge", nProper2);
		else 
			break;

		rs.MoveNext();
	}

	if(nProper1 > 0)
		m_edtProperCharge1.SetWindowText(LF->GetMyNumberFormat(nProper1));
	if(nProper2 > 0)
		m_edtProperCharge2.SetWindowText(LF->GetMyNumberFormat(nProper2));
}


void CRcpDlg::OnCbnSelchangeChargeTypeBombo()
{
	GetSectionCharge(FALSE, FALSE, TRUE, TRUE	);
}

BOOL CRcpDlg::ChangePOIConfirmString(int nModifyPoiConfirmCharge, long nOldCharge, long nNewCharge)
{
	if(m_nPreState == STATE_INTERNET)
		return FALSE;

	CString sMessage = "";
	sMessage.Format("출발지 수정으로 이전요금 %s -> 변경요금 %s원 \n\r변경하시겠습니까? ",
		LF->GetMyNumberFormat(nOldCharge), LF->GetMyNumberFormat(nNewCharge) );

	/*if(nModifyPoiConfirmCharge == MODIFY_POI_DEST)
	sMessage.Replace("출발지", "도착지");
	else if(nModifyPoiConfirmCharge == MODIFY_POI_START)
	sMessage.Replace("출발지", "출발지");*/
	if(m_pDest->GetPOI() != m_pDest->GetPrePOI())
		sMessage.Replace("출발지", "도착지");
	else if(m_pStart->GetPOI() != m_pStart->GetPrePOI())
		sMessage.Replace("출발지", "출발지");
	else
		sMessage.Replace("출발지", "타입또는 차종");

	m_nModifyPoiConfirmCharge = NO_MODIFY_POI;

	if(MessageBox(sMessage, "확인", MB_ICONINFORMATION || MB_YESNO) == IDCANCEL ) 
		return FALSE;

	return TRUE;

}


long CRcpDlg::GetNowChargeControlAmount()
{
	CString strCharge = "", strChangePOIString ="";
	long nOldCharge = 0;
	m_EDT_CHARGE_BASIC.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");			
	if(LF->IsStringDigit(strCharge))
		nOldCharge = atol(strCharge);

	return nOldCharge;

}

BOOL CRcpDlg::IsStartDestPoi()
{
	if(m_pStart->GetPOI() != NULL && m_pDest->GetPOI() != NULL 
		&& m_pStart->GetPosX() > 0 && m_pDest->GetPosY() > 0)
		return TRUE;
	else
		return FALSE;

}
BOOL CRcpDlg::IsPreChangePOI()
{
	CPOIUnit *pS1 = m_pStart->GetPOI();
	CPOIUnit *pS2 = m_pStart->GetPrePOI();
	CPOIUnit *pD1 = m_pDest->GetPOI();
	CPOIUnit *pD2 = m_pDest->GetPrePOI();
	if((m_pStart->GetPOI() != m_pStart->GetPrePOI() || m_pDest->GetPOI() != m_pDest->GetPrePOI() ) &&
		(m_pStart->GetPOI() > NULL && m_pDest->GetPOI() > NULL))
	{
		return TRUE;
	}

	return FALSE;
}

void CRcpDlg::CheckCustomerUsageCharge(long nBasicCharge)
{
	if(m_pOrder->IsNewCus() || m_pStart->IsNewCus() || m_pDest->IsNewCus())
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_usage_charge");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pBi->nDOrderTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pOrder->GetCNo());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pStart->GetCNo());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pDest->GetCNo());

	if(!pRs.Execute(&pCmd)) return;

	if(!pRs.IsEOF())
	{
		CSelectChargeDlg dlg;
		dlg.m_pRs = &pRs;
		dlg.m_strDongCharge.Format("%d", nBasicCharge);
		if(dlg.DoModal() == IDOK)
		{
			m_cmbRunType.SetCurSel(dlg.m_nRunType);
			m_cmbWayType.SetCurSel(dlg.m_nWayType);
			SetCarTypeNew(dlg.m_nCarType);

			m_strChargeBasic.Format("%d", dlg.m_nChargeBasic);
			m_strChargeAdd.Format("%d", dlg.m_nChargeAdd);
			m_strChargeDis.Format("%d", dlg.m_nChargeDis);

			m_strChargeBasic = LF->RemoveZero(m_strChargeBasic);
			m_strChargeAdd = LF->RemoveZero(m_strChargeAdd);
			m_strChargeDis = LF->RemoveZero(m_strChargeDis);

			m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic);
			m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);
			m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
			RefreshCharge();
		}
	}

}


void CRcpDlg::OnEnChangeChargeSumEdit()
{
}

void CRcpDlg::ShowChargeBet(long nIndex)
{
	return;
	/*
	CString sFormat, sS, sD, sT, sC;

	sS = m_pStart->GetPOI()->GetDong();
	sD = m_pDest->GetPOI()->GetDong();
	sT = m_lstCharge.GetItemText(nIndex, 3);
	sC = m_lstCharge.GetItemText(nIndex, 4);
	sC = sC.GetLength() == 0 ? "0" : sC;


	sFormat.Format("%s->%s(%s) %s원", sS, sD, sT, sC);
	m_edtChargeBet.SetWindowText(sFormat);

	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(sC);
	RefreshCharge();
	*/
}

void CRcpDlg::OnBnClickedQueryChargeBtn()
{
	long nFindCompany = AfxGetApp()->GetProfileInt("Messanger", "nFindCompany", 0);
	long nFindRNo = AfxGetApp()->GetProfileInt("Messanger", "nFindRNo", 0);

	RequestCharge(TRUE, nFindCompany, nFindRNo);
}

void CRcpDlg::RequestCharge(BOOL bClose, long nFindCompany, long nFindRNo)
{
	char buffer[20];
	CNewConnListDlg dlg(LU->m_pMsg);
	if(dlg.GetMsgDatabase())
	{
		dlg.m_bQueryChargeMode = TRUE;

		CString strOrderName;
		m_EDT_START_NAME.pEdit->GetWindowText(m_pStart->GetCompany());
		m_EDT_DEST_NAME.pEdit->GetWindowText(m_pDest->GetCompany());
		m_EDT_ORDER_NAME.pEdit->GetWindowText(strOrderName);

		strOrderName += "[" + LF->GetCarTypeFromLong(GetCarTypeNew()) + "]";
		strOrderName += "[" + LF->GetWayTypeFromLong(m_nWayType) + "]";
		strOrderName += "[" + LF->GetRunTypeFromLong(m_nRunType) + "]";
		strOrderName += "[" + LF->GetPayTypeFromLong(m_nPayType) + "]";

		if(m_nQueryChargeUniqueID == 0)
			m_nQueryChargeUniqueID = m_nCurQueryChargeUniqueID++;

		dlg.m_szQueryCharge[0] = 0;
		STRCAT2("^&", dlg.m_szQueryCharge, "$$%QUERYCHARGE", ltoa(m_nQueryChargeUniqueID, buffer, 10), VL_END);
		STRCAT2("^&", dlg.m_szQueryCharge, strOrderName, VL_END);
		STRCAT2("^&", dlg.m_szQueryCharge, m_pStart->GetCompany(), m_pStart->GetAddress(), VL_END);
		STRCAT2("^&", dlg.m_szQueryCharge, m_pDest->GetCompany(), m_pDest->GetAddress(), VL_END);
		dlg.m_nRequestCompany = m_ci.m_nCompanyCode;
		dlg.m_bCloseMode = bClose;
		dlg.m_nFindCompany = nFindCompany;
		dlg.m_nFindRNo = nFindRNo;
		//g_bana_log->Print("m_szQueryCharge=%s\n", dlg.m_szQueryCharge);
		if(dlg.DoModal() == IDCANCEL && bClose)
		{
			CString str;
			str.Format("[%s] %d번 접수자 연결안됨!!!", m_ci.GetBranchName(dlg.m_nFindCompany), dlg.m_nFindRNo);
			MessageBox(str, "확인", MB_ICONINFORMATION);
		}
	}
}


void CRcpDlg::ChangeChargeFromQuery(long nCharge)
{
	m_strChargeBasic.Format("%d", nCharge);
	m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic);
	RefreshCharge();

	m_bFlashPayEdit = TRUE;
	SetTimer(CHARGE_CHANGED_TIMER, 200, NULL);
}

void CRcpDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{	
}

void CRcpDlg::GetPhoneNumberByRider(BCMenu *pRMenu)
{
	CString sTel, sHp;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_phone");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	pRs.GetFieldValue("sTel", sTel);
	pRs.GetFieldValue("sHp", sHp);

	long nItem = 0;

	if(sTel != "")
	{
		pRMenu->SetMenuText(ID_PHONE1 + nItem, LF->GetDashPhoneNumber(sTel), MF_BYCOMMAND);
		m_strCallPhone[nItem++] = sTel;
	}

	if(sHp != "")
	{
		pRMenu->SetMenuText(ID_PHONE1 + nItem, LF->GetDashPhoneNumber(sHp), MF_BYCOMMAND);
		m_strCallPhone[nItem++] = sHp;
	}

	for(int j=nItem; j<MAX_PHONE_NUMBER; j++ )
		pRMenu->RemoveMenu(ID_PHONE1 + j, MF_BYCOMMAND);

	for(int j=0; j<MAX_PHONE_NUMBER; j++ )
		pRMenu->RemoveMenu(ID_PHONE11 + j, MF_BYCOMMAND);
}

BOOL CRcpDlg::GetAddressInfo(BCMenu* pRMenu,long nCNo)
{
	CMkCommand pCmd(m_pMkDb, "select_customer_address_with_gno");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pBi->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCNo);

	if(!pRs.Execute(&pCmd)) return FALSE;
	if(pRs.GetRecordCount() <= 1)  return FALSE;

	for(int i=0; i<pRs.GetRecordCount(); i++) 
	{
		if(i>10) 
			break;

		ST_ADDRESS st;

		//pRs.GetFieldValue("nID", st.nID);
		pRs.GetFieldValue("nCNo", st.nCNo); 
		pRs.GetFieldValue("nGNo", st.nGNo);
		pRs.GetFieldValue("nCompany", st.nCompany);
		pRs.GetFieldValue("sAddressTitle", st.strAddressTitle);
		pRs.GetFieldValue("sDong", st.strDong);
		pRs.GetFieldValue("sLocation", st.strLocation);
		pRs.GetFieldValue("nPosX", st.nPosX);
		pRs.GetFieldValue("nPosY", st.nPosY);
		pRs.GetFieldValue("nDongID", st.nDongID);
		pRs.GetFieldValue("sAddress", st.strAddress);

		CString strTitle = "";

		if(st.nCNo != 0)  
			strTitle = "[" + st.strAddressTitle + "]" +  m_poiNew.GetPOI(st.nDongID)->GetFullName() + st.strAddress;
		else
			strTitle =  "[그룹]" + m_poiNew.GetPOI(st.nDongID)->GetFullName() + st.strAddress;

		pRMenu->SetMenuText(ID_ADDRESS1 + i, strTitle, MF_BYCOMMAND);

		m_stAddress[i] = st;

		pRs.MoveNext();
	}

	for(int j=pRs.GetRecordCount(); j<MAX_PHONE_NUMBER; j++ )
	{
		pRMenu->RemoveMenu(ID_ADDRESS1 + j, MF_BYCOMMAND);
	}

	return TRUE;
}

void CRcpDlg::GetPhoneNumberByServer(BCMenu* pRMenu,long nCNo)
{
	CString sTel;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_cno_phone");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCNo);

	if(!pRs.Execute(&pCmd)) return;

	long nRecordCount = pRs.GetRecordCount();

	long i = 0;

	for(i=0; i<nRecordCount; i++)
	{
		if(i > 10) 
			break;

		pRs.GetFieldValue("sTel", sTel);
		pRMenu->SetMenuText(ID_PHONE1 + i, LF->GetDashPhoneNumber(sTel), MF_BYCOMMAND);
		pRMenu->SetMenuText(ID_PHONE11 + i, LF->GetDashPhoneNumber(sTel) + "(SMS)", MF_BYCOMMAND);

		m_strCallPhone[i] = sTel;

		pRs.MoveNext();
	}

	int j= nRecordCount;

	for(j=nRecordCount; j<MAX_PHONE_NUMBER; j++ )
	{
		pRMenu->RemoveMenu(ID_PHONE1 + j, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_PHONE11 + j, MF_BYCOMMAND);
	}
}

void CRcpDlg::GetPhoneNumberByClient(BCMenu* pRMenu,UINT nFlagPhone, UINT nFlagMP)
{
	CString sPhone, sMP;

	GetDlgItem(nFlagPhone)->GetWindowText(sPhone);
	GetDlgItem(nFlagMP)->GetWindowText(sMP);

	sPhone.Replace("-","");
	sPhone.Replace(" ", "");
	sMP.Replace("-","");
	sMP.Replace(" ", "");

	if(sPhone != "")
	{
		pRMenu->SetMenuText(ID_PHONE1 , sPhone, MF_BYCOMMAND);
		pRMenu->SetMenuText(ID_PHONE11 , sPhone + "(SMS)", MF_BYCOMMAND);
		m_strCallPhone[0] = sPhone;
	}
	else
	{
		pRMenu->RemoveMenu(ID_PHONE1 , MF_BYCOMMAND);
		pRMenu->SetMenuText(ID_PHONE11 , MF_BYCOMMAND);
	}

	if(sMP != "")
	{
		pRMenu->SetMenuText(ID_PHONE2 , sMP, MF_BYCOMMAND);
		pRMenu->SetMenuText(ID_PHONE12 , sPhone + "(SMS)", MF_BYCOMMAND);
		m_strCallPhone[1] = sMP;
	}
	else
	{
		pRMenu->RemoveMenu(ID_PHONE2 , MF_BYCOMMAND);
		pRMenu->SetMenuText(ID_PHONE12 , sPhone + "(SMS)", MF_BYCOMMAND);
	}

	for(int j=2; j<MAX_PHONE_NUMBER; j++ )
	{
		pRMenu->RemoveMenu(ID_PHONE1 + j, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_PHONE11 + j, MF_BYCOMMAND);
	}
}

void CRcpDlg::OnPhoneControl(UINT nFlag)
{	
	m_pRcpView->MakeCall(m_pBi->nCompanyCode, LF->GetNoneDashNumber(m_strCallPhone[nFlag - ID_PHONE1]), m_nToCallingType);
}

void CRcpDlg::OnPhoneControlSMS(UINT nFlag)
{	
	m_pRcpView->SendSms(m_pBi->nCompanyCode, m_strCallPhone[nFlag - ID_PHONE11]);
}

void CRcpDlg::OnBnClickedOrderMapBtn()
{
	m_pOrder->ShowMap();
}

void CRcpDlg::OnBnClickedInquiryBtn()
{ 
	CString strItem;
	m_btnInquiry.GetWindowText(strItem);
	
	//if(IsEditMode())
	if(strItem == "문의등록")
	{
		m_bInquiryOrder = TRUE;
		AddNewOrder(FALSE);
	}
	else 
	{
		m_pRcpView->SelectRowFromTNo(m_nInitItem);
		m_pRcpView->OnCurOrderState();
	}
}

void CRcpDlg::OnBnClickedNoticeBtn()
{
	if(!IsEditMode())
	{
		m_bNoticeOrder = TRUE;
		AddNewOrder(FALSE);
	}
	else 
	{
		OnMenuContextFunc(ID_MENU_FUNC_VERIFY_SIGN);
	}
}

void CRcpDlg::InsertCharge(BOOL bShuttle)
{
	try
	{
		if(m_pStart->GetPOI() == NULL || m_pStart->GetPOI()->GetID() <= 0)
			throw("출발지 동데이터가 입력이 없거나 오류입니다. ");

		if(m_pDest->GetPOI() == NULL || m_pDest->GetPOI()->GetID() <= 0)
			throw("도착지 동데이터가 입력이 없거나 오류입니다. ");

		if(m_strChargeBasic.GetLength() == 0)
			throw("요금칸이 비어있습니다.");

		long nCharge = 0, nType = 0;
		long nStartID =0, nDestID =0,  nStartType =0, nDestType = 0;

		m_strChargeBasic.Replace(",","");
		m_strChargeBasic.Replace("\\", "");

		if(!LF->IsStringDigit(m_strChargeBasic))
			throw("금액이 숫자가 아닙니다.");

		nCharge = GetStringChargeToNumber(m_strChargeBasic);
		if(nCharge <= 0)
			throw("금액이 0보다 작습니다.");

		if(m_pStart->GetPOI()->m_nClass == 10 && m_pStart->GetPOI()->IsDongPOI())
			nStartID = 3;
		else if(m_pStart->GetPOI()->m_nClass == 10 && !m_pStart->GetPOI()->IsDongPOI())
			nStartID = 2;
		else if(m_pStart->GetPOI()->m_nClass != 10)
			nStartID = 1;
		else
			throw("출발지 데이터가 오류입니다");

		if(m_pDest->GetPOI()->m_nClass == 10 && m_pDest->GetPOI()->IsDongPOI())
			nStartID = 3;
		else if(m_pDest->GetPOI()->m_nClass == 10 && !m_pDest->GetPOI()->IsDongPOI())
			nStartID = 2;
		else if(m_pDest->GetPOI()->m_nClass != 10)
			nStartID = 1;
		else
			throw("도착지 데이터가 오류입니다");



		if(nStartType == 3 && nDestType == 3)
			nType = 8;
		else if(nStartType == 3 && nDestType == 2)
			nType = 7;
		else if(nStartType == 3 && nDestType == 1)
			nType = 6;
		else if(nStartType == 2 && nDestType == 3)
			nType = 5;
		else if(nStartType == 1 && nDestType == 3)
			nType = 4;
		else if(nStartType == 2 && nDestType == 2)
			nType = 3;
		else if(nStartType == 2 && nDestType == 1)
			nType = 2;
		else if(nStartType == 1 && nDestType == 2)
			nType = 1;
		else if(nStartType == 1 && nDestType == 1)
			nType = 0;

		int nSelectCarType = 0, nCarType = 0;
		int nChargeType = m_CMB_CHARGE_TYPE.pCombo->GetCurSel();
		nCarType = GetCarTypeNew();

		if(nCarType == CAR_AUTO || nCarType == CAR_BIGBIKE)
			nSelectCarType = 0;
		else if(nCarType == CAR_DAMA || nCarType == CAR_LABO)
			nSelectCarType = 1;
		else if(nCarType == CAR_VAN)
			nSelectCarType = 2;
		else if(nCarType == CAR_TRUCK)
			nSelectCarType = 3;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_charge_dong_data");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pBi->nPayTable);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nType);
		pCmd.AddParameter(m_pStart->GetPOI()->GetID());
		pCmd.AddParameter(m_pDest->GetPOI()->GetID());
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCharge);		
		pCmd.AddParameter(typeLong, typeInput, sizeof(BOOL), bShuttle);		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_CMB_CHARGE_TYPE.pCombo->GetCurSel());
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSelectCarType);		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pOrder->GetGNo());		

		if(!pRs.Execute(&pCmd)) 
			throw("입력중 오류가 났습니다.");

		throw("정상적으로 입력되었습니다.");

	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}
}

void CRcpDlg::OnHdnItemclickHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	ShowUsageHistory();

	*pResult = 0;
}

void CRcpDlg::ShowUsageHistory(BOOL bRefresh, BOOL bRcpDlgForceSizing)
{
	if(m_pOrder->GetCNo() < 1)
		return;

	if(m_pHistoryDlg == NULL)
	{
		UINT nResourceID = m_bHistoryMoveDown ? IDD_HISTORY_CHILD_DLG : IDD_HISTORY_DLG;

		m_pHistoryDlg = new CHistoryDlg(nResourceID, this);
		m_pHistoryDlg->m_pRcpDlg = this;
		m_pHistoryDlg->m_nOGNo = m_pOrder->GetGNo(); 
		m_pHistoryDlg->m_nOCNo = m_pOrder->GetCNo(); 
		m_pHistoryDlg->m_nCompany = m_pBi->nCustomerTable;
		m_pHistoryDlg->Create(nResourceID, this);

		ChangeRcpDlgSize(!m_bHistoryMoveDown, bRcpDlgForceSizing);

		if(m_bHistoryMoveDown)
		{
			CRect rcHistory, rcClose, rcDlg;
			GetClientRect(rcDlg);
			m_btnClose.GetWindowRect(rcClose);
			ScreenToClient(rcClose);

			rcHistory.top = rcClose.bottom + 5;
			rcHistory.bottom = rcDlg.bottom - 5;
			rcHistory.left = rcDlg.left + 5; 
			rcHistory.right = rcDlg.right - 5;
			m_pHistoryDlg->MoveWindow(rcHistory);
		}
		else
		{
			CRect rcDlg, rcHistory, rcNew, rcClose;
			GetWindowRect(rcDlg);
			m_pHistoryDlg->GetWindowRect(rcHistory);

			long nHeight = rcHistory.Height();
			long nWeight = rcHistory.Width();

			rcHistory.top = rcDlg.top + 200;
			rcHistory.bottom = rcHistory.top + nHeight;
			rcHistory.right = rcDlg.left - 2;
			rcHistory.left = rcHistory.right - nWeight;
			m_pHistoryDlg->MoveWindow(rcHistory);
		}
	}
	else
	{
		ChangeRcpDlgSize(!m_bHistoryMoveDown, bRcpDlgForceSizing);

		m_pHistoryDlg->m_nOGNo = m_pOrder->GetGNo(); //m_pOrder->GetGNo();
		m_pHistoryDlg->m_nOCNo = m_pOrder->GetCNo(); //m_pOrder->GetCNo();
		m_pHistoryDlg->m_nCompany = m_pBi->nCustomerTable;

		if(bRefresh)
		{
			m_pHistoryDlg->Clear();
			m_pHistoryDlg->RefreshList();
		}
	}

	m_pHistoryDlg->ShowWindow(SW_SHOW);
}

void CRcpDlg::ChangeRcpDlgSize(BOOL bOriginal, BOOL bForceChange)
{
	if(bOriginal)
	{
		CRect rcDlg, rcNew, rcClose;
		GetWindowRect(rcDlg);
		m_btnClose.GetWindowRect(rcClose);

		if(rcDlg.bottom - rcClose.bottom > 20 || bForceChange)
		{
			rcDlg.bottom = rcClose.bottom + 10;
			MoveWindow(rcDlg);

			if(m_pHistoryDlg)
				m_pHistoryDlg->ShowWindow(SW_HIDE);	
		}
	}
	else if(m_pHistoryDlg)
	{
		long nHeight = AfxGetApp()->GetProfileInt("HistoryDlg", "Height", 200);

		CRect rcHistory, rcClose, rcDlg;
		GetWindowRect(rcDlg);
		m_btnClose.GetWindowRect(rcClose);

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
			m_pHistoryDlg->ShowWindow(SW_SHOW);	
		}
	}
}

void CRcpDlg::OnCbnEditchangeCouponChargeCombo()
{
	return;
}

void CRcpDlg::OnBnClickedInputChargeNewBtn()
{
	if(!LF->POWER_CHECK(1100, "요금창 보기", TRUE))
		return;

	if(m_pStart->GetPOI() == NULL || m_pDest->GetPOI() == NULL) return;

	long nCompany = (long)m_CMB_BRANCH.pCombo->GetItemData(m_CMB_BRANCH.pCombo->GetCurSel());
	//if(nCompany <= 0 )
	nCompany = m_pBi->nPayTable;
	CString strCharge = "";
	m_EDT_CHARGE_BASIC.pEdit->GetWindowText(strCharge);

	long nChargeType, nCarType;

	nCarType = LF->GetCarTypeForCharge(GetCarTypeNew());
	nChargeType = m_CMB_CHARGE_TYPE.pCombo->GetCurSel();

	BOOL bUpdateChargeOk = FALSE;

	if(m_pBi->nCompanyCode == m_pBi->nPayTable)
		bUpdateChargeOk = TRUE;
	else if(m_pBi->nPayTable == m_ui.nCompany)
		bUpdateChargeOk = TRUE;
	else 
		bUpdateChargeOk = FALSE;

	long nPreMemCNo = m_nChargeMemCNo;
	CDirectChargeInputDlg1 dlg;

	dlg.m_pStartPoi = m_pStart->GetPOI();
	dlg.m_pDestPoi = m_pDest->GetPOI(); 

	dlg.m_nCompany = nCompany;
	dlg.m_bUpdateChargeOk = bUpdateChargeOk;
	dlg.m_nGNo =  m_pOrder->GetGNo();
	dlg.m_nCNo = m_pOrder->GetCNo();
	dlg.m_nStartDongID = m_pStart->GetPOI()->GetDongID();
	dlg.m_nDestDongID = m_pDest->GetPOI()->GetDongID();
	//dlg.m_nMemCNo = m_pBi->bNotMemberCharge ? 0 : m_nChargeMemCNo; 

	long nRet = dlg.DoModal();
	if(nRet == IDOK)
		LU->GetMemberChargeDlg()->SetCNoPopup(m_nChargeMemCNo, m_pOrder->GetCNo(), nCompany,this);

	//if(nPreMemCNo <= 0 && dlg.m_nMemCNo > 0 )
		m_nChargeMemCNo = dlg.m_nCNo;

	
	GetSectionCharge();

	
}

void CRcpDlg::OnBnClickedQueryChargeBtn2()
{
	long nFindCompany =AfxGetApp()->GetProfileInt("Messanger", "nFindCompany2", 0);
	long nFindRNo = AfxGetApp()->GetProfileInt("Messanger", "nFindRNo2", 0);

	RequestCharge(TRUE, nFindCompany, nFindRNo);
}


void CRcpDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CRcpDlgBase::PostNcDestroy();
}


void CRcpDlg::OnBnClickedConsignBtn()
{
	CConsignDlg dlg;
	dlg.m_pStartPoi = m_pStart->GetPOI();
	dlg.m_pDestPoi = m_pDest->GetPOI();
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nCharge > 0)
		{			
			m_EDT_CHARGE_TRANS.pEdit->SetWindowText(LF->GetMyNumberFormat(dlg.m_nCharge));
			RefreshCharge();
		}
	}
}


void CRcpDlg::OnBnClickedShowRiderPosBtn()
{
	if(m_nRiderCompany > 0)
	{
		CREATE_MODALESS(CRiderTraceMapDlg, this);
		pDlg->m_nCompany = m_nRiderCompany; 
		pDlg->m_nRNo = m_nRNo;
		SHOW_MODALESS(CRiderTraceMapDlg, this);

		if(m_pStart->IsPosValid() && m_pDest->IsPosValid())
		{ 
			CLogiMapCns *pCNS = LU->GetLogiMapCns();
			pDlg->GetMap()->ClearAllLayer();
			pCNS->SetOnceShowMap(pDlg->GetMap());
			GetRouteDistance(TRUE, FALSE, FALSE, FALSE);
		}

		pDlg->MoveRider();
	}
}

void CRcpDlg::OnEnKillfocusChargeBasicEdit()
{


	if(LF->GetCurBranchInfo()->bNotMemberCharge)  // 업체요금 사용안함.
		return;

	if(m_EDT_CHARGE_BASIC.pEdit->IsWindowVisible() == FALSE ||
		m_EDT_CHARGE_BASIC.pEdit->GetSafeHwnd() == FALSE)
		return ;

	CString strCharge;
	m_EDT_CHARGE_BASIC.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");
	if(atol(strCharge) < 500 && atol(strCharge) > 0)
	{
		m_strChargeBasic = LF->GetMyNumberFormat(atol(strCharge) * 1000);
		m_EDT_CHARGE_BASIC.pEdit->SetWindowText(m_strChargeBasic);
		OnEnChangeChargeBasicEdit();
	}

	if(IsEditMode() && m_nLoadChargeBasic != GetRcpBasicCharge() && m_bDirtyBasicCharge && !LF->GetCurBranchInfo()->bNotMemberCharge )
	{
		m_chkSaveCharge.SetCheck(TRUE);	
		m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);
		m_bDirtyBasicCharge = FALSE;
		return;
	}

	if(!m_pCharge->IsCashCharge())
		return;


	if(m_bDirtyBasicCharge)
	{
		long nCashCharge = 0;
		int nCarType = 0;

		//nCarType = ( m_pBi->bUsePayBonggoFromLabo && GetCarTypeNew() == CAR_LABO ) ? CAR_VAN : GetCarTypeNew();
		nCarType = GetCarTypeChargeTemp();

		nCashCharge = m_pCharge->GetCashCharge(m_nChargeMemCNo, m_pStart->GetPOI(), m_pDest->GetPOI(), 
			m_pOrder->GetGNo(), m_pBi,	m_nCNoChargeDriving, m_nCNoDiscount,  m_fDirectDistance, m_CMB_CHARGE_TYPE.pCombo->GetCurSel(), 
			
			LF->GetCarTypeForCharge(nCarType),
			FALSE);

		if(
			GetRcpBasicCharge() != nCashCharge &&
			GetRcpBasicCharge() > 0 &&  nCashCharge > 0 &&  // 1.캐쉬된금액과 현재금액이 틀리고 ,  2. 금액이 0이상이고 
			( m_pCharge->GetStartPoi() > 0 && m_pCharge->GetDestPoi() > 0 ) && // POI 가 입력되어 요금계산이 된적
			!LF->GetCurBranchInfo()->bNotMemberCharge
			)
		{
			m_chkSaveCharge.SetCheck(TRUE);	
			m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);
		}
		else
			m_chkSaveCharge.SetCheck(FALSE);		
	}
	m_bDirtyBasicCharge = FALSE;
}

void CRcpDlg::OnEnKillfocusChargeSumEdit()
{
	CString strCharge;
	m_EDT_CHARGE_SUM.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");
	if(atol(strCharge) < 500 && atol(strCharge) > 0)
	{
		m_strChargeSum = LF->GetMyNumberFormat(atol(strCharge) * 1000);
		m_EDT_CHARGE_SUM.pEdit->SetWindowText(m_strChargeSum);
		OnEnChangeChargeSumEdit();
	}
}

void CRcpDlg::OnEnKillfocusChargeTransEdit()
{
	/*
	CString strCharge;
	m_EDT_CHARGE_TRANS.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");
	if(atol(strCharge) < 500 && atol(strCharge) > 0)
	{
	m_strChargeTrans = LF->GetMyNumberFormat(atol(strCharge) * 1000);
	m_EDT_CHARGE_TRANS.pEdit->SetWindowText(m_strChargeTrans);
	}
	*/

}

BOOL CRcpDlg::MileageUse(long nOrderCNo)
{
	try{

		//UpdateData();
		CString strChargeSum, strMileageBalance, strMsg, strEtc, strMent;
		//char buffer[10];
		m_EDT_CHARGE_SUM.pEdit->GetWindowText(strChargeSum);
		m_edtMileageBalance.GetWindowText(strMileageBalance);
		strChargeSum.Replace(",","");
		strMileageBalance.Replace(",","");

		long nChargeSum = atol(strChargeSum);
		long nMileageBalance = atol(strMileageBalance);

		if(m_bNotOrderMileage)
			throw("마일리지 미적용(1회성) 상태입니다.");

		if(nChargeSum <= 0)
			throw("합계금액이 없습니다. 요금을 입력하세요");

		long nFixedMileage = 0;
		long nCompany = GetBranchComboToBranchInfo()->nCompanyCode;
		long nMileSpan = m_mi.GetMileData(nCompany)->nMileageSpan;

		strMsg.Format("마일리지 최소사용 금액은 %s원 입니다. ",LF->GetMyNumberFormat(nMileSpan) );
		if(nMileSpan > nMileageBalance)
			throw(strMsg);


		if( MessageBox("마일리지를 적용하시겠습니까?", "확인", MB_YESNO) == IDNO)
			return FALSE;


		long nUseMileage = nChargeSum; //, buffer,10);
		if(nUseMileage < nMileSpan)
			throw(strMsg);



		if(nChargeSum >=  nUseMileage && nUseMileage <= nMileageBalance )
			nFixedMileage = nUseMileage;

		else if(nChargeSum < nUseMileage && nUseMileage <=  nMileageBalance)
			nFixedMileage = nChargeSum;				
		else
		{
			LF->MsgBox("금액적용을 다시하여주세요");
			return FALSE;
		}
		m_edtAutoCharge.SetWindowText(LF->GetMyNumberFormat(nFixedMileage));
		m_EDT_ETC.pEdit->GetWindowText(strEtc);
		strMent.Format("※마일리지적용[%s원]", LF->GetMyNumberFormat(nFixedMileage));
		strEtc += strMent;
		m_EDT_ETC.pEdit->SetWindowText(strEtc);

		LF->MsgBox("오더를 수정하시거나 신규로올리셔야만 적용이 됩니다.");
		return TRUE;
	}
	catch(char *sMsg)
	{
		MessageBox(sMsg, "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	catch(CString sMsg)
	{
		MessageBox(sMsg,"확인", MB_ICONINFORMATION);
		return FALSE;
	}
}


void CRcpDlg::OnBnClickedRiderAutoChargeChk()
{
	CString sRiderAuto; m_chkAutoCharge.GetWindowText(sRiderAuto);
	int nPrePayType = m_cmbPayType.GetCurSel();
	if(sRiderAuto.Compare("X") == 0 )
		m_cmbPayType.SetCurSel(PAY_TYPE_MILEAGE_CREDIT);

	SetConsignMode(FALSE);
}


void CRcpDlg::OnEnChangeRiderAutoChargeEdit()
{	
	CString strChargeSum; 
	CString strEtc, strPayMsg;

	m_edtAutoCharge.GetWindowText(m_strMileageAutoCharge);
	this->m_EDT_CHARGE_SUM.pEdit->GetWindowText(strChargeSum);
	strChargeSum.Replace(",", "");
	m_strMileageAutoCharge.Replace(",", ""); 

	long nChargeSum = atoi(strChargeSum);
	long nMileageAutoCharge = atoi(m_strMileageAutoCharge);

	long nMileageBalance = m_nMileageBalance;

	if(m_nInitItem > 0)
		nMileageBalance = nMileageBalance + m_nPreRiderAutoCharge;

	if(_ttoi(m_strMileageAutoCharge) > nMileageBalance)
	{

		//m_strMileageAutoCharge.Format("%d", nMileageBalance);
		m_strMileageAutoCharge.Format("%d", 0);
		m_edtAutoCharge.SetWindowText(LF->GetMyNumberFormat(m_strMileageAutoCharge));

		MessageBox("마일리지잔액보다 마일리지사용액이 더 많습니다", "확인", MB_ICONINFORMATION);
		//return;
	}


	if(_ttoi(m_strMileageAutoCharge) > _ttoi(strChargeSum) && _ttoi(strChargeSum) > 0)
	{
		MessageBox("요금보다 마일리지사용액이 더 많습니다", "확인", MB_ICONINFORMATION);

		m_strMileageAutoCharge = strChargeSum;
		m_edtAutoCharge.SetWindowText(LF->GetMyNumberFormat(m_strMileageAutoCharge));
	}

	m_EDT_ETC.pEdit->GetWindowText(strEtc);

	if(strEtc.Find("{현금") >= 0 ||
		strEtc.Find("{신용") >= 0)
	{
		int nStart = strEtc.Find("{현금");
		if(nStart < 0)
			nStart = strEtc.Find("{신용");

		if(nStart >= 0)
		{
			int nEnd = 0;

			if(strEtc.Find("{업체부담금") >= 0)
				nEnd = strEtc.Find("}", nStart);
			else
				nEnd = strEtc.Find("}");

			if(nEnd > nStart)
			{
				CString strDelete = strEtc.Mid(nStart, nEnd - nStart + 1);
				strEtc.Replace(strDelete, "");
			}
		}
	}

	long nMileage = m_mi.GetMileageVal(m_pBi->nCompanyCode, m_cmbCarType.GetCurSel(), m_nPersonMileageType, 
		m_nPersonMileage, GetStringChargeToNumber(m_strChargeSum), GetCarTypeNew());

	if(GetPayTypeNew() == PAY_CREDIT && !LF->IsThisCompany("빨간모자퀵") && !LF->IsThisCompany("주식회사대구조합"))
		nMileage = 0;
	//if(m_cmbPayType.GetCurSel() == PAY_TYPE_MILEAGE_CREDIT)
	if(atoi(m_strMileageAutoCharge) > 0)
	{
		if(GetPayTypeNew() == PAY_PRE || GetPayTypeNew() == PAY_AFTER || GetPayTypeNew() == PAY_DIRECT)
		{
			strPayMsg.Format("{현금%s/마일리지(신용)%s/}", LF->GetMyNumberFormat(_ttoi(strChargeSum) - _ttoi(m_strMileageAutoCharge)), LF->GetMyNumberFormat(m_strMileageAutoCharge));
		}	
		else
		{
			strPayMsg.Format("{신용%s/마일리지(신용)%s/}", 
				LF->GetMyNumberFormat(_ttoi(strChargeSum) - _ttoi(m_strMileageAutoCharge)), 
				LF->GetMyNumberFormat(m_strMileageAutoCharge));		
		}

		m_edtMileReserve.SetWindowText("");
	}
	else
		m_edtMileReserve.SetWindowText(LF->GetMyNumberFormat(nMileage));


	m_EDT_ETC.pEdit->SetWindowText(strPayMsg + strEtc);
}

BOOL CRcpDlg::JustInsertNewCustomer(int nCtrl)
{
	CString strPhone, strMP, strPhone1, strPhone2;
	CString strName, strDepart, strManager, strDetail;
	CString strAddress, strDong, strMemo;
	long nDongID = 0, nPosX = 0, nPosY = 0;

	if(nCtrl == PLACE_ORDER)
	{
		m_EDT_ORDER_PHONE.pEdit->GetWindowText(strPhone);
		m_edtOrderMP.GetWindowText(strMP);

		strPhone1 = LF->GetNoneDashNumber(strPhone);
		strPhone2 = LF->GetNoneDashNumber(strMP);

		if(!LF->IsPhoneNumber(strPhone1) || !LF->IsPhoneNumber(strPhone2))
		{
			MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
				"의뢰지 자동추가 과정에서 오류발생", MB_ICONINFORMATION);
			return FALSE;
		}

		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		if(strPhone2.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone2 = strPhone2.Right(strPhone2.GetLength() - m_ci.m_strDDD.GetLength());

		m_EDT_ORDER_NAME.pEdit->GetWindowText(strName);
		m_EDT_ORDER_DEPART.pEdit->GetWindowText(strDepart);
		m_EDT_ORDER_MANAGER.pEdit->GetWindowText(strManager);
		m_edtOrderDetail.GetWindowText(strDetail);
		m_edtOrderDong.GetWindowText(strDong);
		m_edtOrderMemo.GetWindowText(strMemo);

		if(m_pOrder->GetPOI())
		{
			strAddress = m_pOrder->GetAddress();
			nDongID = m_pOrder->GetPOI()->GetDongID();
			nPosX = m_pOrder->GetPOI()->GetPosX();
			nPosY = m_pOrder->GetPOI()->GetPosY();
		}
	}
	else if(nCtrl == PLACE_START)
	{
		m_EDT_START_PHONE.pEdit->GetWindowText(strPhone);
		m_edtStartMP.GetWindowText(strMP);

		strPhone1 = LF->GetNoneDashNumber(strPhone);
		strPhone2 = LF->GetNoneDashNumber(strMP);

		if(!LF->IsPhoneNumber(strPhone1) || !LF->IsPhoneNumber(strPhone2))
		{
			MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
				"의뢰지 자동추가 과정에서 오류발생", MB_ICONINFORMATION);
			return FALSE;
		}

		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		if(strPhone2.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone2 = strPhone2.Right(strPhone2.GetLength() - m_ci.m_strDDD.GetLength());

		m_EDT_START_NAME.pEdit->GetWindowText(strName);
		m_EDT_START_DEPART.pEdit->GetWindowText(strDepart);
		m_EDT_START_MANAGER.pEdit->GetWindowText(strManager);
		m_EDT_START_DETAIL.pEdit->GetWindowText(strDetail);
		m_EDT_START_DONG.pEdit->GetWindowText(strDong);

		if(m_pStart->GetPOI())
		{
			strAddress = m_pStart->GetAddress();
			nDongID = m_pStart->GetPOI()->GetDongID();
			nPosX = m_pStart->GetPOI()->GetPosX();
			nPosY = m_pStart->GetPOI()->GetPosY();
		}
	}
	else if(nCtrl == PLACE_DEST)
	{
		m_EDT_DEST_PHONE.pEdit->GetWindowText(strPhone);
		m_edtDestMP.GetWindowText(strMP);

		strPhone1 = LF->GetNoneDashNumber(strPhone);
		strPhone2 = LF->GetNoneDashNumber(strMP);

		if(!LF->IsPhoneNumber(strPhone1) || !LF->IsPhoneNumber(strPhone2))
		{
			MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
				"의뢰지 자동추가 과정에서 오류발생", MB_ICONINFORMATION);
			return FALSE;
		}

		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		if(strPhone2.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone2 = strPhone2.Right(strPhone2.GetLength() - m_ci.m_strDDD.GetLength());

		m_EDT_DEST_NAME.pEdit->GetWindowText(strName);
		m_EDT_DEST_DEPART.pEdit->GetWindowText(strDepart);
		m_EDT_DEST_MANAGER.pEdit->GetWindowText(strManager);
		m_EDT_DEST_DETAIL.pEdit->GetWindowText(strDetail);
		m_EDT_DEST_DONG.pEdit->GetWindowText(strDong);

		if(m_pDest->GetPOI())
		{
			strAddress = m_pDest->GetAddress();
			nDongID = m_pDest->GetPOI()->GetID();
			nPosX = (long)(m_pDest->GetPOI()->GetPosX());
			nPosY = (long)(m_pDest->GetPOI()->GetPosY());
		}
	}


	CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "insert_new_customer_for_rcp_dlg");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));	//return
	CMkParameter *parCustomerID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long));	//output
	pCmd.AddParameter("");
	pCmd.AddParameter(m_pBi->nCustomerTable);
	pCmd.AddParameter(strName);
	pCmd.AddParameter(strDepart);
	pCmd.AddParameter(strManager);
	pCmd.AddParameter(strPhone1);
	pCmd.AddParameter(strDong);
	pCmd.AddParameter(strDetail);
	pCmd.AddParameter(0);
	pCmd.AddParameter(0);
	pCmd.AddParameter(0);
	pCmd.AddParameter(0);
	pCmd.AddParameter(strPhone2);
	pCmd.AddParameter(0);
	pCmd.AddParameter(strMemo);
	pCmd.AddParameter("");
	pCmd.AddParameter("");
	pCmd.AddParameter("");
	pCmd.AddParameter(nDongID);
	pCmd.AddParameter(nPosX);
	pCmd.AddParameter(nPosY);
	pCmd.AddParameter(0);
	pCmd.AddParameter(0);

	if(pCmd.Execute())
	{
		if(nCtrl == 0)
			m_pOrder->SetCNo(parRet->GetLong());
		else if(nCtrl == PLACE_START)
			m_pStart->SetCNo(parRet->GetLong());
		else if(nCtrl == PLACE_DEST)
			m_pDest->SetCNo(parRet->GetLong());

		return TRUE;
	}
	return FALSE;
}

void CRcpDlg::OnLvnItemchangedChargeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CRcpDlg::OnPassData()
{
	if(IsEditMode())
	{
		MessageBox("수정모드에서는 지원되지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CRcpCopyData data;
	char *pszData = GetInsertData(data);

	if(pszData)
	{
		CNewConnListDlg dlg(LU->m_pMsg);
		dlg.GetMsgDatabase();
		dlg.m_bQueryChargeMode = FALSE;
		dlg.m_bRcpCopyData = TRUE;
		dlg.m_pszRcpCopyData = pszData;
		dlg.m_nRequestCompany = m_ci.m_nCompanyCode;
		dlg.m_bCloseMode = FALSE;
		dlg.m_nFindCompany = 0;
		dlg.m_nFindRNo = 0;
		dlg.DoModal();
	}
}

void CRcpDlg::OnRcpCopyData(CRcpCopyData *pData)
{
	//by mksong (2010-12-19 오후 8:28)
	//재작업 필요함

	long nPoiID;
	double nPosX, nPosY;
	BOOL bChkTransOrder;
	int nChargeType;
	int nReserve;
	int nReserveAfterWait;
	BOOL bAutoCharge;
	CString strMileageBalance, strNotOrderMileage;  

	long nOCNo, nGNo, nSCNo, nDCNo, nCarType, nOTelID;
	CString strOCompany, strOPhone, strOMP, strODepart, strOManager, strOAddress, strODetail, strODisplayDong, strOMemo;
	CString strSCompany, strSPhone, strSMP, strSDepart, strSManager, strSAddress, strSDetail, strSDisplayDong;
	CString strDCompany, strDPhone, strDMP, strDDepart, strDManager, strDAddress, strDDetail, strDDisplayDong;
	long nSID, nSDongID, nDID, nDDongID;


	GET_RCP_DATA(m_strCID);
	GET_RCP_DATA(nOCNo);
	GET_RCP_DATA(nOTelID);
	GET_RCP_DATA(nGNo);
	GET_RCP_DATA(nSCNo);
	GET_RCP_DATA(nDCNo);
 
	m_pOrder->SearchCustomerCNo(nOCNo, TRUE, TRUE, nOTelID, FALSE);

	if(nSCNo > 0)
		m_pStart->SearchCustomerCNo(nSCNo);

	if(nDCNo > 0)
		m_pDest->SearchCustomerCNo(nDCNo);

	//GET_RCP_DATA(CReserveOrderDlg::m_bReserve);
	GET_RCP_DATA(strOCompany);
	GET_RCP_DATA(strOPhone);
	GET_RCP_DATA(strOMP);
	GET_RCP_DATA(strODepart);
	GET_RCP_DATA(strOManager);
	GET_RCP_DATA(strOAddress);
	GET_RCP_DATA(strODetail);
	GET_RCP_DATA(strOMemo);
	GET_RCP_DATA(strODisplayDong);
	GET_RCP_DATA(strSCompany);
	GET_RCP_DATA(strSPhone);
	GET_RCP_DATA(strSMP);
	GET_RCP_DATA(strSDepart);
	GET_RCP_DATA(strSManager);
	GET_RCP_DATA(strSAddress);
	GET_RCP_DATA(strSDetail);
	GET_RCP_DATA(strSDisplayDong);

	pData->GetValue("m_pStartPoi->GetID()", nPoiID);
	if(nPoiID > 0)
	{
		GET_RCP_DATA(nPosX);
		GET_RCP_DATA(nPosY);

		CPOIUnit *pStartPoi = m_pStart->GetPOI();
		CopyPoiData(&pStartPoi, m_poiNew.GetPOI(nPoiID), nPosX, nPosY);
	}

	GET_RCP_DATA(strDCompany);
	GET_RCP_DATA(strDPhone);
	GET_RCP_DATA(strDMP);
	GET_RCP_DATA(strDDepart);
	GET_RCP_DATA(strDManager);
	GET_RCP_DATA(strDAddress);
	GET_RCP_DATA(strDDetail);
	GET_RCP_DATA(strDDisplayDong);


	pData->GetValue("m_pDestPoi->GetID()", nPoiID);
	if(nPoiID > 0)
	{
		GET_RCP_DATA(nPosX);
		GET_RCP_DATA(nPosY);
		CPOIUnit *pDestPoi = m_pDest->GetPOI();
		CopyPoiData(&pDestPoi, m_poiNew.GetPOI(nPoiID), nPosX, nPosY);
	}

	GET_RCP_DATA(m_strEtc);
	//GET_RCP_DATA(CReserveOrderDlg::m_dtReserveDate);
	//GET_RCP_DATA(CReserveOrderDlg::m_dtReserveTime);
	//GET_RCP_DATA(CReserveOrderDlg::m_nReleaseMin);
	//GET_RCP_DATA(m_bFinalSendSMS);
	GET_RCP_DATA(m_strItemType);
	GET_RCP_DATA(m_nPayType);
	GET_RCP_DATA(nCarType);
	GET_RCP_DATA(m_nWayType);
	GET_RCP_DATA(m_nRunType);
	GET_RCP_DATA(m_strCNS);

	GET_RCP_DATA(m_strChargeBasic);
	GET_RCP_DATA(m_strChargeAdd);
	GET_RCP_DATA(m_strChargeDis);
	GET_RCP_DATA(m_strChargeSum);
	GET_RCP_DATA(m_strChargeTrans);
	GET_RCP_DATA(m_strDeposit);

	GET_RCP_DATA(m_bCoupon);
	GET_RCP_DATA(m_strCouponCharge);
	GET_RCP_DATA(m_strAllocateGroup);
	//GET_RCP_DATA(m_strRiderNo);
	//GET_RCP_DATA(m_strRiderCompany);	//nRiderCompany;
	//GET_RCP_DATA(m_strRiderName);
	//GET_RCP_DATA(m_strRiderMP);
	GET_RCP_DATA(m_strChargeBet);
	GET_RCP_DATA(m_bScheduleOrder);
	GET_RCP_DATA(m_strIntercallEtc);
	GET_RCP_DATA(nCarType);
	
	SetCarTypeNew(nCarType);

	GET_RCP_DATA(nSID);
	GET_RCP_DATA(nSDongID);
	GET_RCP_DATA(nDID);
	GET_RCP_DATA(nDDongID);

	MakeSearchPOIDlgForSerchPopup();

	if(nSCNo == 0)
	{
		CPOIUnit *pDongPoi = m_poiNew.GetPOI(nSID);

		if(!pDongPoi) 
			pDongPoi = m_poiNew.GetDongPOI(nSDongID);

		if(pDongPoi)
		{
			m_pSearchPOIDlg->SetRcpPlace(m_pStart, m_EDT_START_NAME.pEdit);
			m_pSearchPOIDlg->SaveCurPOI(POI_COMPLETE_EVENT, pDongPoi, NULL);
		}
	}

	if(nDCNo == 0)
	{
		CPOIUnit *pDongPoi = m_poiNew.GetPOI(nDID);

		if(!pDongPoi)
			pDongPoi = m_poiNew.GetDongPOI(nDDongID);

		if(pDongPoi)
		{
			m_pSearchPOIDlg->SetRcpPlace(m_pDest, m_EDT_DEST_NAME.pEdit);
			m_pSearchPOIDlg->SaveCurPOI(POI_COMPLETE_EVENT, pDongPoi, NULL,"" ,"" ,"" ,"" ,strDAddress ,"" );
		}
	}

	UpdateData(FALSE);

	m_EDT_START_NAME.pEdit->SetWindowText(strSCompany); 
	m_EDT_START_DEPART.pEdit->SetWindowText(strSDepart);
	m_EDT_START_MANAGER.pEdit->SetWindowText(strSManager);
	m_EDT_START_DETAIL.pEdit->SetWindowText(strSDetail);
	m_EDT_START_DONG.pEdit->SetWindowText(strSDisplayDong);
	m_EDT_START_PHONE.pEdit->SetWindowText(strSPhone);
	m_edtStartMP.SetWindowText(strSMP);

	m_EDT_DEST_NAME.pEdit->SetWindowText(strDCompany); 
	m_EDT_DEST_DEPART.pEdit->SetWindowText(strDDepart);
	m_EDT_DEST_MANAGER.pEdit->SetWindowText(strDManager);
	m_EDT_DEST_DETAIL.pEdit->SetWindowText(strDDetail);
	m_EDT_DEST_DONG.pEdit->SetWindowText(strDDisplayDong);
	m_EDT_DEST_PHONE.pEdit->SetWindowText(strDPhone);
	m_edtDestMP.SetWindowText(strDMP);
	
	//DDX_변수 로 연결되어있지 않는 경우에, 아래에 배치한다.
	GET_RCP_DATA(bChkTransOrder);
	GET_RCP_DATA(nChargeType);
	//m_chkTransOrder.SetCheck(bChkTransOrder);


	GET_RCP_DATA(nReserve);
	GET_RCP_DATA(nReserveAfterWait);

	//CReserveOrderDlg::m_bReserve = nReserve;
	//CReserveOrderDlg::m_bReserveAfterWait = nReserveAfterWait;

	GET_RCP_DATA(bAutoCharge);
	GET_RCP_DATA(strMileageBalance);
	GET_RCP_DATA(strNotOrderMileage);
	m_chkAutoCharge.SetCheck(bAutoCharge);
	m_edtMileageBalance.SetWindowText(strMileageBalance);
	//	m_edtNotOrderMileage.SetWindowText(strNotOrderMileage);
}

void CRcpDlg::OnRecvEditOrderState(long nTNo, long nTickCount, long nState, CString strWName)
{
	CString strMsg;
	if(nState == EOS_EDITING)
	{
		strMsg.Format("[%s]님이 해당오더를 먼저 수정중에 있습니다.\n중복수정에 유의하여 주시기 바랍니다.",
			strWName);
		MessageBox(strMsg, "수정상태확인", MB_ICONINFORMATION);
	}
	else if(nState == EOS_END_EDIT)
	{
		strMsg.Format("[%s]님이 해당오더를 %d초전에 수정 완료하였습니다.\n수정내용을 보시려면 (예)를 누르시기 바랍니다.",
			strWName, nTickCount);
		if(IDYES == MessageBox(strMsg, "수정상태확인", MB_ICONQUESTION | MB_YESNO))
		{
			CRcpDlg *pDlg = m_pRcpView->CreateRcpDlg(NULL, 
				"수정상태확인",
				m_nInitItem, 
				m_nState, "", FALSE, -1, 0, 0, FALSE, m_strYear);

			if(pDlg)
			{
				pDlg->m_bEditExampleDlg = TRUE;
			}
		}
	}
}

void CRcpDlg::OnCurOrderState()
{
	LU->OpenCurOrderState(m_nInitItem);
}

CString CRcpDlg::GetJibunFromFullName(CString sFullName)
{
	CStringW wszBuffer(sFullName);
	CStringW sReturn;
	//WCHAR wszBuffer[255];
	//MultiByteToWideChar(CP_ACP, 0, (LPCSTR)sFullName, -1, wszBuffer, 255);

	long nCur = 0;
	BOOL bFInd = FALSE;

	for(int i=0; i<strlen(sFullName); i++)
	{
		if(bFInd)
		{
			sReturn += wszBuffer.Mid(i, 1);
			continue;
		}

		int nNextIndex = min(i+1, strlen(sFullName) -1);
		CString sChar(wszBuffer.Mid(i, 1));
		CString sNextChar(wszBuffer.Mid(nNextIndex, 1));

		//int a = min(i+1, strlen(sFullName) -1);
		//CString sChar = (LPSTR)(LPCTSTR)wszBuffer[i];
		//CString sNextChar = "a";//(LPSTR)(LPCTSTR)wszBuffer[min(i+1, strlen(sFullName) -1)];

		if((LF->IsNumeric(sChar) == TRUE) && 
			(sNextChar!= "가") &&
			(sNextChar != "로") &&
			(sNextChar != "동"))
		{
			sReturn += wszBuffer.Mid(i, 1);
			bFInd = TRUE;
		}
	}

	CString sString(sReturn);

	return sString;	
} 

BOOL CRcpDlg::SaveCustomerAddress(long nCNo, long nDongID, CString sDong, CString sAddress)
{
	if(nCNo <= 0)
	{
		MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_address");
	pCmd.AddParameter(nCNo);
	pCmd.AddParameter(nDongID);
	pCmd.AddParameter(sDong);
	pCmd.AddParameter(sAddress);

	return pCmd.Execute();
}

CString CRcpDlg::GetSaveMent(ST_EDIT_HISTORY stPre, ST_EDIT_HISTORY stCur)
{
	CString sTitle[] = {"(의)고객명", "(의)전화번호", "(의)휴대폰", "(의)부서", "(의)담당", "(의)주소", "(의)상세위치", "(의)기준동", "(의)메모", 
		"(출)고객명", "(출)전화번호", "(출)휴대폰", "(출)부서", "(출)담당", "(출)주소", "(출)상세위치", "(출)기준동",
		"(도)고객명", "(도)전화번호", "(도)휴대폰", "(도)부서", "(도)담당", "(도)주소", "(도)상세위치", "(도)기준동",
		"적요", "물품", "지불", "차량", "운송", "급", 
		"추가",	"기본", "탁송", "할인", "합계", "입금", "쿠폰", "구간", "SMS번호"};

	CString sReturn = "";

	BOOL bChange = FALSE;
	long nItem = 0;
	char buffer[10];

	for(int i=0; i<COMPARE_STRING_COUNT; i++)
	{
		if(stPre.item[i] != stCur.item[i]) 
		{
			sReturn += (CString)itoa(nItem++, buffer, 10) + ", " + sTitle[i] + " ==> " "[" + stPre.item[i] + "] -> [" + stCur.item[i] + "]" + "\r\n";
			bChange = TRUE;
		}
	}

	if(bChange)
		sReturn = "아래의 항목이 변경됩니다. [" + (CString)itoa(nItem, buffer, 10) + "건]\r\n\r\n" + sReturn;

	return sReturn;
}

long CRcpDlg::RequestOrder(ST_EDIT_HISTORY stCur)
{
	CString sSaveItemMent = "아래의 이유로 수정 하실 수 없습니다\r\n";

	if((m_stPreInfo.nRiderCompany != stCur.nRiderCompany) &&
		(m_stPreInfo.nRNo != stCur.nRNo))
		sSaveItemMent += "[기사수정]\r\n\r\n";
	else if(m_stPreInfo. nDeposit != stCur.nDeposit)
		sSaveItemMent += "[입금액수정]\r\n\r\n";

	sSaveItemMent += GetSaveMent(m_stPreInfo, stCur) + "\r\n";
	sSaveItemMent += "수정요청 하시겠습니까?\r\n"; 

	if(MessageBox(sSaveItemMent, "확인", MB_OKCANCEL) != IDOK)
		return FALSE;

	CMkCommand pCmd(m_pMkDb, "insert_order_change_request");	 

	m_strChargeBasic.Replace(",", "");
	m_strChargeAdd.Replace(",", "");
	m_strChargeDis.Replace(",", "");
	m_strChargeSum.Replace(",", "");
	m_strChargeTrans.Replace(",", "");
	m_strDeposit.Replace(",", "");

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_nInitItem); 

	return pCmd.Execute();	
}


void CRcpDlg::OnEnKillfocusRiderAutoChargeEdit()
{
	//m_chkAutoCharge.
}

long CRcpDlg::GetGroupTodayUseCharge()
{
	long nCharge = 0;
	OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nGNo == m_pOrder->GetGNo() &&
			it->second.nState >= STATE_OK && 
			it->second.nState <= STATE_FINISH &&
			it->second.nPayType >= 2 &&
			it->second.nPayType <= 3)
		{
			if(m_nInitItem != it->second.nTNo)
				nCharge += (it->second.nCharge + it->second.nChargeTrans);
		}
	}

	return nCharge;
}

BOOL CRcpDlg::IsGroupInsertOk()
{
	if(m_pOrder->GetGNo() > 0 && 
		(IsPayType(PAY_CREDIT) || IsPayType(PAY_ONLINE)))
	{
		ST_CUSTOMER_GROUP_INFOMATION *pCFInfo = m_cg.GetGroupData(m_pOrder->GetGNo());
		long nGroupAbleCharge = pCFInfo->nAbleUseCharge * 10000;
		long nGroupCharge = pCFInfo->nUseCharge;

		if(nGroupAbleCharge > 0)
		{
			long nTodayUseCharge = GetGroupTodayUseCharge();
			nGroupCharge += (nTodayUseCharge + atoi(m_strChargeSum) + atoi(m_strChargeTrans));

			if(nGroupCharge > nGroupAbleCharge)
			{
				CString strTemp = "";
				strTemp.Format("해당 고객이 속한 그룹(%s)은 %s원까지 사용가능 하므로접수 하실수 없습니다.\r\n금일까지 사용금액 %s원", pCFInfo->strFullName, LF->GetMyNumberFormat(nGroupAbleCharge), LF->GetMyNumberFormat(nGroupCharge));

				MessageBox(strTemp, "확인", MB_ICONINFORMATION);

				return FALSE;	
			}
		}
	}

	return TRUE;
}

void CRcpDlg::ReLocationAddCustomerBtn()
{
	//by mksong (2010-11-25 오후 10:40)
	//작업필요함
	/*
	CRect rcEdt, rcBtn;
	m_edtOrderDetail.GetWindowRect(rcEdt);
	m_btnAddOrderCustomer.GetWindowRect(rcBtn);

	ScreenToClient(rcEdt);
	ScreenToClient(rcBtn);

	if(m_pOrder->GetCNo() > 0) //기존
	{		 
	rcEdt.right = rcBtn.right;
	m_btnAddOrderCustomer.ShowWindow(SW_HIDE);
	}
	else
	{
	rcEdt.right = rcBtn.left; rcEdt.right -= 2;
	m_btnAddOrderCustomer.ShowWindow(SW_SHOW);
	}

	m_edtOrderDetail.MoveWindow(rcEdt);		
	*/
}

void CRcpDlg::AddEtcOK()
{
	//#define QUICK_OK_2920_MENT "{신규/친절/쿠폰판지급}"
	//#define QUICK_OK_2904_MENT "{친절,홍보금지,확인함}"
	//#define QUICK_OK_2931_MENT "{친절,홍보금지,쿠폰판 도장 꼭 찍어주세요}"

	CString strEtc;
	CString strMsg;

	if(LF->IsThisCompany("퀵오케이_2904", m_pBi->nCompanyCode))
		strMsg = QUICK_OK_2904_MENT;
	else if(LF->IsThisCompany("퀵오케이_2920", m_pBi->nCompanyCode))
		strMsg = QUICK_OK_2920_MENT;
	else if(LF->IsThisCompany("퀵오케이_2931", m_pBi->nCompanyCode))
		strMsg = QUICK_OK_2931_MENT;
	else if(LF->IsThisCompany("퀵오케이_2907", m_pBi->nCompanyCode))
		strMsg = QUICK_OK_2907_MENT;

	CString strFind = strMsg.Left(5);

	m_EDT_ETC.pEdit->GetWindowText(strEtc);
	if(strEtc.Find("{신규") >= 0)
	{
		int nStart = strEtc.Find("{신규");

		if(nStart >= 0)
		{
			int nEnd = strEtc.Find("}");

			if(nEnd > nStart)
			{
				CString strDelete = strEtc.Mid(nStart, nEnd - nStart + 1);
				strEtc.Replace(strDelete, "");
			}
		}
	}

	m_EDT_ETC.pEdit->SetWindowText(strMsg + strEtc);
}

void CRcpDlg::OnMove(int x, int y)
{
	if(m_pHistoryDlg && !m_bHistoryMoveDown)
		m_pHistoryDlg->m_Magnetic.AttachTo();

	if(m_pSearchPOIDlg)
		m_pSearchPOIDlg->m_Magnetic.AttachTo();

	if(m_pCreditHistoryDlg)
		m_pCreditHistoryDlg->m_Magnetic.AttachTo();

	if(m_pSearchManagerDlg)
		ShowSearchManagerDlg(TRUE);
}

void CRcpDlg::MakeSearchPOIDlgForSerchPopup()
{
	if(m_pSearchPOIDlg == NULL)
	{
		m_pSearchPOIDlg = new CSearchPOIDlg(this);
		m_pSearchPOIDlg->SetPOIDataNew(&m_poiNew);
		m_pSearchPOIDlg->SetCusData(&m_cus);
		m_pSearchPOIDlg->SetDatabase(m_pMkDb);
		m_pSearchPOIDlg->Create(IDD_SEARCH_POI_DLG, this);
	}
}

void CRcpDlg::ShowSearchPOIDlg(CString strKeyword, CRcpPlaceInfo *pPlace, BOOL bFromGetFocus, CWnd *pwndNextFocus, 
							   BOOL bJustSearch, BOOL bChangeMapPos, int nSearchType)
{
	if(bFromGetFocus && !m_pSearchPOIDlg)
		return;

	BOOL bKeywordOn = strKeyword.GetLength() > 0;

	if(!m_pSearchPOIDlg)
	{
		CRect rc, rcDlg, rcOrder, rcNew;

		m_pSearchPOIDlg = new CSearchPOIDlg(this);
		m_pSearchPOIDlg->SetPOIDataNew(&m_poiNew);
		m_pSearchPOIDlg->SetCusData(&m_cus);
		m_pSearchPOIDlg->SetDatabase(m_pMkDb);
		m_pSearchPOIDlg->Create(IDD_SEARCH_POI_DLG, this);

		m_pSearchPOIDlg->GetWindowRect(rc);
		GetWindowRect(rcDlg);
		m_edtOrder.GetWindowRect(rcOrder);

		rcNew.right = rcDlg.left - 2;  
		rcNew.left = rcNew.right - rc.Width();  
		rcNew.top = rcOrder.top;
		rcNew.bottom = rcNew.top + rc.Height(); 
		m_pSearchPOIDlg->MoveWindow(rcNew);

		if(bKeywordOn)
			m_pSearchPOIDlg->ShowWindow(SW_SHOWNA);

		m_pSearchPOIDlg->SetSearchSido(m_poiNew.GetSearchSido()->GetSido());

		if(m_pRcpView->m_pMapForm && m_pRcpView->m_pMapForm->m_setinfo.nRcpDlgMoveMap)
			m_pSearchPOIDlg->SetLogiMap(&m_pRcpView->m_pMapForm->m_wndOrderMap);

		//		m_poiNew.SetSearchSido(new CPOIBoundary(&m_poiNew, TRUE, "서울", "인천", "경기"));
		//		if(!m_poiNew.SetCenterSido("서울"))
		//			return;
	}
	else if(bKeywordOn)
	{
		if(bFromGetFocus && m_pSearchPOIDlg->m_bClosedByUser)
			return;

		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pSearchPOIDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pSearchPOIDlg->ShowWindow(SW_RESTORE);
		else if(!m_pSearchPOIDlg->IsWindowVisible())
			m_pSearchPOIDlg->ShowWindow(SW_SHOWNA);
	}

	CPOIUnit *pPOICenter = m_poiNew.SetCenterSido(m_pBi->strCity);

	if(pPOICenter)
	{
		if(pPlace->GetPOI())
			m_pSearchPOIDlg->GetNaver()->SetCenterPos(pPlace->GetPosX(), pPlace->GetPosY());
		else
			m_pSearchPOIDlg->GetNaver()->SetCenterPos(pPOICenter->GetPosX(), pPOICenter->GetPosY());

		m_pSearchPOIDlg->SetCenterSido(m_poiNew.GetCenterSido());
	}

	m_pSearchPOIDlg->m_bAutoCompleteOnce = m_bPOIAutoCompleteOnce;
	m_bPOIAutoCompleteOnce = FALSE;

	BOOL bWebPosAutoSelect = FALSE;

	BOOL bUseNaverPoiToCustomer  = AfxGetApp()->GetProfileInt("RcpPage", "UseNaverPoiToCustomer", 1);

	if(bUseNaverPoiToCustomer == TRUE)
	{
		if(!m_strCID.IsEmpty() && pPlace->GetPlaceType() == PLACE_ORDER)
		{
			CString strTemp = strKeyword;
			strTemp.Replace("-", "");
			if(LF->IsNumeric(strTemp))
			{
				//if(m_ci.m_strDDD == strTemp.Left(m_ci.m_strDDD.GetLength()))
				bWebPosAutoSelect = TRUE;
			}				
		}
	}

	m_pSearchPOIDlg->SetRcpPlace(pPlace, pwndNextFocus);
	m_pSearchPOIDlg->SetCustomerTable(m_pBi->nCustomerTable); 
	m_pSearchPOIDlg->SearchPOIWithSetText(strKeyword, bJustSearch, bChangeMapPos, nSearchType, bWebPosAutoSelect);
}

void CRcpDlg::OnEnSetfocusCIDEdit()
{
	CString strText;
	m_EDT_CID.pEdit->GetWindowText(strText);
	ShowSearchPOIDlg(strText, m_pOrder, TRUE, m_EDT_START.pEdit, TRUE, 1, TYPE_PHONE);
}

void CRcpDlg::OnEnSetfocusOrderEdit()
{
	CString strText;
	m_edtOrder.GetWindowText(strText);
	ShowSearchPOIDlg(strText, m_pOrder, TRUE, m_EDT_START.pEdit);
}

void CRcpDlg::OnEnSetfocusStartEdit()
{
	CString strText;
	m_EDT_START.pEdit->GetWindowText(strText);
	ShowSearchPOIDlg(strText, m_pStart,TRUE,  m_pBi->bNoDestPoi ? m_EDT_DEST_DONG.pEdit : m_EDT_DEST.pEdit);
}

void CRcpDlg::OnEnSetfocusDestEdit()
{
	CString strText;
	m_EDT_DEST.pEdit->GetWindowText(strText);

	if(LF->IsThisCompany("엔콜"))
		ShowSearchPOIDlg(strText, m_pDest, TRUE, m_EDT_ETC.pEdit);
	else
		ShowSearchPOIDlg(strText, m_pDest, TRUE, m_EDT_CHARGE_BASIC.pEdit);
}

void CRcpDlg::OnEnChangeOrderEdit()
{
	CString strText;
	m_edtOrder.GetWindowText(strText);
	ShowSearchPOIDlg(strText, m_pOrder, TRUE, m_EDT_START.pEdit);
}

void CRcpDlg::OnEnChangeStartEdit()
{
	CString strText;
	m_EDT_START.pEdit->GetWindowText(strText);
	ShowSearchPOIDlg(strText, m_pStart,TRUE,  m_pBi->bNoDestPoi ? m_EDT_DEST_DONG.pEdit : m_EDT_DEST.pEdit);
}

void CRcpDlg::OnEnChangeDestEdit()
{
	CString strText;
	m_EDT_DEST.pEdit->GetWindowText(strText);

	if(LF->IsThisCompany("엔콜"))
		ShowSearchPOIDlg(strText, m_pDest, TRUE, m_EDT_ETC.pEdit);
	else
		ShowSearchPOIDlg(strText, m_pDest, TRUE, m_EDT_CHARGE_BASIC.pEdit);
}

void CRcpDlg::OnBnClickedOrderCustomerDlgBtn()
{
	ShowPlaceCustomerDlgBtn(m_pOrder);
}

void CRcpDlg::OnBnClickedStartCustomerDlgBtn()
{
	ShowPlaceCustomerDlgBtn(m_pStart);
}

void CRcpDlg::OnBnClickedDestCustomerDlgBtn()
{
	ShowPlaceCustomerDlgBtn(m_pDest);
}

void CRcpDlg::ShowPlaceCustomerDlgBtn(CRcpPlaceInfo *pPlace, BOOL bSearchCustomer)
{
	if(pPlace->GetCNo() > 0 && bSearchCustomer == FALSE)
	{ 
		CString strText;
		strText.Format("%d", pPlace->GetCNo());
		pPlace->SearchCustomer(strText, ST_CNO);
	}
	else
	{
		//CString strPhone = pPlace->GetSearch();
		CString strPhone = pPlace->GetPhone();		

		pPlace->SearchCustomer(strPhone);
		//pPlace->SearchCustomer(m_pOrder->GetSearch());
	}
}

int CRcpDlg::SearchEditVK_RETURN(int nID, BOOL bSelectWhenSingleResult)
{
	CString strText;
	CEdit *pEdit = (CEdit*)GetDlgItem(nID);
	pEdit->GetWindowText(strText);

	//BOOL bDongInfohas = FALSE;

	if(strText.GetLength() == 0)
	{
		CRcpPlaceInfo *pPlace = GetPlaceInfo(nID); 
		long nOCNo = m_pOrder->GetCNo();

		BOOL bDongInfohas = m_pOrder->GetPOI() != NULL ? TRUE : FALSE;

		if(!pPlace->IsOrder() && (nOCNo > 0 || bDongInfohas == TRUE))
		{
			pPlace->Copy(m_pOrder);
		}
		else if(pPlace->IsOrder())
		{
			CString strCID;
			m_EDT_CID.pEdit->GetWindowText(strCID);
			if(strCID.GetLength() > 0 && nOCNo == 0)
				pPlace->SetPhone(strCID);
		}

		GotoNextFocus(nID);						
	}
	else if(m_pSearchPOIDlg)// || bDongInfohas == TRUE)
	{
		BOOL bIsPhone = LF->IsPhoneNumber(strText);
		BOOL bSearchPhone = (nID == IDC_CID_EDIT) && bIsPhone;

		m_pSearchPOIDlg->SearchPOIJust(strText);

		if(!m_pSearchPOIDlg->OnAutoSelectEvent(bSearchPhone ? TYPE_PHONE : TYPE_AUTO, 0, 
			bSelectWhenSingleResult, strText))
		{
			if(bIsPhone) 
			{
				if(nID == IDC_CID_EDIT || nID == IDC_ORDER_EDIT)
					m_pOrder->SetPhone(strText);
				else if(nID == IDC_START_EDIT)
					m_pStart->SetPhone(strText);
				else if(nID == IDC_DEST_EDIT)
					m_pDest->SetPhone(strText);

				if(bSelectWhenSingleResult == FALSE)
					GotoNextFocus(nID);
			}
			else
			{
				if(nID == IDC_ORDER_EDIT)
				{
					m_pOrder->SetCompany(strText);
					m_pOrder->GetCompanyEdit()->SetFocus();
				}
				else if(nID == IDC_START_EDIT)
				{
					m_pStart->SetCompany(strText);
					m_pStart->GetCompanyEdit()->SetFocus();
				}
				else if(nID == IDC_DEST_EDIT)
				{
					m_pDest->SetCompany(strText);
					m_pDest->GetCompanyEdit()->SetFocus();
				}
			}
		}
	}


	return FALSE;
}

CRcpPlaceInfo *CRcpDlg::GetPlaceInfo(int nID)
{
	if(nID == IDC_START_EDIT ||
		nID == IDC_START_NAME_EDIT || 
		nID == PLACE_START)
		return m_pStart;
	else if(nID == IDC_DEST_EDIT || 
		nID == IDC_DEST_NAME_EDIT || 
		nID == PLACE_DEST)
		return m_pDest;
	else
		return m_pOrder;
}

void CRcpDlg::GotoNextFocus(int nID)
{
	CRcpPlaceInfo *pPlace = GetPlaceInfo(nID);

	if(nID == IDC_CID_EDIT)
		m_EDT_START.pEdit->SetFocus();			
	else if(nID == IDC_ORDER_ADDRESS_EDIT)
		m_edtOrderDetail.SetFocus();
	else if(nID == IDC_START_ADDRESS_EDIT)
		m_EDT_START_DETAIL.pEdit->SetFocus();
	else if(nID == IDC_DEST_ADDRESS_EDIT)
		m_EDT_DEST_DETAIL.pEdit->SetFocus();
	else if(pPlace->GetPlaceType() == PLACE_ORDER)
		m_EDT_START.pEdit->SetFocus();
	else if(pPlace->GetPlaceType() == PLACE_START)
	{
		if(m_pBi->bNoDestPoi)
			m_EDT_DEST_DONG.pEdit->SetFocus();
		else
			m_EDT_DEST.pEdit->SetFocus();
	}
	else if(pPlace->GetPlaceType() == PLACE_DEST)
		m_EDT_CHARGE_BASIC.pEdit->SetFocus();
}

void CRcpDlg::SetDiscountInfoInit()
{
	m_strChargeDis = "";
	m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
	m_strChargeAdd = "";
	m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);

	m_nDiscountType = ZERO;
	m_nDiscountValue = ZERO;
}

void CRcpDlg::SetDiscountInfo(BOOL bCreditAfterDis, long nDiscount, long nDiscountType, long nDiscountRange, BOOL bDiscountApplyOnlyCredit)
{
	m_bCreditAfterDis = bCreditAfterDis;

	// 1. 그룹할인 먼저적용
	// 2. 고객할인 나중적용
	/*
	if(!m_bCreditAfterDis)
	{

		if(nDiscount != 0)
			m_nDiscountRange = nDiscountRange;


		if(nDiscount == 0 &&m_pOrder->GetGNo() > 0 )
		{
			if(m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountType > 0 &&
				m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount != 0 )
			{
				nDiscount = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount;
				m_nDiscountRange = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountRange;
			}
		}

		if(nDiscount > ZERO ) 
		{ 
			if(bDiscountApplyOnlyCredit == FALSE || 
				(bDiscountApplyOnlyCredit == TRUE && IsCash(GetPayTypeNew()) == FALSE)) //고객창에 외상오더만 할인 여부
			{
				m_strChargeAdd.Format("%d", abs(nDiscount));
				m_EDT_CHARGE_ADD.pEdit->SetWindowText(LF->RemoveZero(m_strChargeAdd));
				m_strChargeDis = "";
				m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
			}			
		}	
		else if(nDiscount < ZERO ) {
			if(bDiscountApplyOnlyCredit == FALSE || 
				(bDiscountApplyOnlyCredit == TRUE && IsCash(GetPayTypeNew()) == FALSE))
			{
				m_strChargeDis.Format("%d", abs(nDiscount));
				m_EDT_CHARGE_DIS.pEdit->SetWindowText(LF->RemoveZero(m_strChargeDis));
				m_strChargeAdd = "";
				m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);
			}
		}		
		else
		{

			// 고객 그룹 모두 적용되지 않을때..
			m_strChargeDis = "";
			m_EDT_CHARGE_DIS.pEdit->SetWindowText(m_strChargeDis);
			m_strChargeAdd = "";
			m_EDT_CHARGE_ADD.pEdit->SetWindowText(m_strChargeAdd);


		}

		m_nDiscountType = ZERO;
		m_nDiscountValue = ZERO;
	}
	else
	{
		m_nDiscountType = nDiscountType;
		m_nDiscountValue = nDiscount;
	}
	*/


	if(m_bCreditAfterDis && nDiscount == 0 && m_pOrder->GetGNo() > 0 )
	{
		if(m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountType > 0 &&
			m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount != 0 )
		{
			

			nDiscount = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscount;
			m_nDiscountRange = m_cg.GetGroupData(m_pOrder->GetGNo())->nDirectDiscountRange;
			m_nDiscountType = 100;  // 그룹할인
		}
	}
	else
	{


		m_nDiscountType = nDiscountType;
		m_nDiscountValue = nDiscount;
	}
}

void CRcpDlg::SetMileageInfo(long nMileageType, long nMileageValue, long nMileageBalance, long nCNo, long nMemCNo)
{
	m_nPersonMileage = nMileageValue;
	m_nPersonMileageType = nMileageType;
	m_nMileageBalance = nMileageBalance;		
	m_edtMileageBalance.SetWindowText(LF->GetMyNumberFormat(m_nMileageBalance));


	SetMileageData(0, 0);

	if(nMemCNo > 0 && !m_pBi->bNotMemberCharge)
	{
		m_nChargeMemCNo = nMemCNo;
		//m_chkSaveCharge.SetCheck(TRUE);
	}
	else
	{
		m_nChargeMemCNo = 0;
		//m_chkSaveCharge.SetCheck(FALSE);
	}	

	RefreshCharge(TRUE, m_nInitItem > 0 ? FALSE : TRUE);
}

void CRcpDlg::SetChargeOrCouponInfo(long bCredit, BOOL nPriceGrade, int nCouponCharge, int nCouponType)
{
	char buffer[20];

	/*
	if(bCredit && !IsEditMode())
	SetPayTypeNew(PAY_CREDIT);
	else
	SetPayTypeNew(PAY_PRE);
	*/

	if(!IsEditMode())
	{
		if(bCredit == 1)
			SetPayTypeNew(PAY_CREDIT);
		else if(bCredit == 2)
			SetPayTypeNew(PAY_ONLINE);
		else if(bCredit == 3)
			SetPayTypeNew(PAY_CARD);
		else
			SetPayTypeNew(PAY_PRE);
	}

	m_nPriceGrade = nPriceGrade;
	m_CMB_CHARGE_TYPE.pCombo->SetCurSel(nPriceGrade > 3 ? 0 : nPriceGrade );
	m_cmbCouponType.SetCurSel(nCouponCharge < 100 ? 1 : 0);
	m_cmbCouponCharge.SetWindowText(ltoa(nCouponCharge, buffer, 10));
}

void CRcpDlg::OnMenuContextEtc(UINT nFlag)
{
	if(nFlag == ID_MENU_ETC_USER_UPDATE)
	{
		CMenuEtcUserDlg dlg;
		dlg.m_pBi = m_pBi;
		dlg.DoModal();
		return;
	}
	else if(nFlag == ID_MENU_ETC_TO_INTERCALL_ETC)
	{
		CString strEtc; m_EDT_ETC.pEdit->GetWindowText(strEtc);
		CString strInterEtc; m_edtIntercallEtc.GetWindowText(strInterEtc);

		if(strInterEtc.IsEmpty())
			m_edtIntercallEtc.SetWindowText(strEtc);
		else
			m_edtIntercallEtc.SetWindowText(strEtc + " " + strInterEtc);

		return;
	}

	CString strUrge;
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	strUrge.Format("[독촉%s]", dtCurrent.Format("%H:%M"));

	CString strRecall;
	strRecall.Format("[리콜%s]", dtCurrent.Format("%H:%M"));

	CString strReg = AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	CString strArry[]  = {strUrge, strRecall, "[전화먼저]", "[특별대우]", m_pBi->sEtcUserMemo1,
		m_pBi->sEtcUserMemo2, m_pBi->sEtcUserMemo3, m_pBi->sEtcUserMemo4, strReg};

	BOOL bFront = AfxGetApp()->GetProfileInt(m_ui.strID + "_Etc", "Front", 0);

	LF->SetEditText(m_EDT_ETC.pEdit, strArry[nFlag - ID_MENU_ETC_URGE], bFront);
}

void CRcpDlg::OnMenuContextCharge(UINT nFlag)
{
	switch(nFlag)
	{
	case ID_MENU_CHARGE_QUERY:
		RequestCharge();
		break;
	case ID_MENU_CHARGE_WNO_REGISTION:
		{
			CRegisterWNoDlg dlg;
			dlg.DoModal();
			break;
		}
	case ID_MENU_CHARGE_DEPOSIT_REFRESH:
		RefreshCharge(TRUE);
		break;
	case ID_MENU_CHARGE_DEPOSIT_REFRESH_BASIC:
		RefreshCharge(FALSE);
		break;
	case ID_MENU_CHARGE_DEPOSIT_EDIT:
		if(!LF->POWER_CHECK(1710, "입금테이블 설정", TRUE))
			return;

		if(m_ui.strPW != "")
		{
			MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
			return;
		}

		CDepositRateDlg dlg;
		dlg.m_nCompany = m_pBi->nDOrderTable;
		dlg.DoModal();
		break;

	}
}

void CRcpDlg::OnMenuContextPlace(UINT nFlag)
{
	switch(nFlag)
	{
	case ID_PLACE_DELETE_O:
		m_pOrder->Clear();
		break;
	case ID_PLACE_DELETE_S:
		m_pStart->Clear();
		break;
	case ID_PLACE_DELETE_D:
		m_pDest->Clear();
		break;
	case ID_PLACE_SEARCH_O:
		ShowNameSearch(m_EDT_ORDER_NAME.pEdit, &m_edtOrder);
		break;
	case ID_PLACE_SEARCH_S:
		ShowNameSearch(m_EDT_START_NAME.pEdit, m_EDT_START.pEdit);
		break;
	case ID_PLACE_SEARCH_D:
		ShowNameSearch(m_EDT_DEST_NAME.pEdit, m_EDT_DEST.pEdit);
		break;
	case ID_PLACE_COPY_OS:
		m_pStart->Copy(m_pOrder);
		break;
	case ID_PLACE_COPY_OD:
		m_pDest->Copy(m_pOrder);
		break;
	case ID_PLACE_COPY_SO:
		m_pOrder->Copy(m_pStart);
		break;
	case ID_PLACE_COPY_SD:
		m_pDest->Copy(m_pStart);
		break;
	case ID_PLACE_COPY_DO:
		m_pOrder->Copy(m_pDest);
		break;
	case ID_PLACE_COPY_DS:
		m_pStart->Copy(m_pDest);
		break;
	case ID_PLACE_EXCHANGE_OS:
	case ID_PLACE_EXCHANGE_SO:
		m_pOrder->Exchange(m_pStart);
		break;
	case ID_PLACE_EXCHANGE_OD:
	case ID_PLACE_EXCHANGE_DO:
		m_pDest->Exchange(m_pOrder);
		break;
	case ID_PLACE_EXCHANGE_SD:
	case ID_PLACE_EXCHANGE_DS:
		m_pStart->Exchange(m_pDest);
		break;
	case ID_SHOW_DISTANCE:
		GetRouteDistance(TRUE, FALSE, FALSE, FALSE);
		break;

	case ID_PLACE_SAVE_ADDRESS_SO:
		m_pStart->SaveAddressToOrder(m_pOrder);
		break;

	case ID_PLACE_SAVE_ADDRESS_SS:
		m_pStart->SaveAddressToOrder(m_pStart);
		break;

	case ID_PLACE_SAVE_ADDRESS_DO:
		m_pDest->SaveAddressToOrder(m_pOrder);
		break;

	case ID_PLACE_SAVE_ADDRESS_DD:
		m_pDest->SaveAddressToOrder(m_pDest);
		break;
	}
}

void CRcpDlg::ShowPlaceMenu(int nSubMenu)
{
	CPoint pt; 
	GetCursorPos(&pt);

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_PLACE_MENU);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(nSubMenu);
	pRMenu->SetMenuDrawMode(TRUE);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CRcpDlg::OnBnClickedOrderMoveBtn()
{
	ShowPlaceMenu(0);
}

void CRcpDlg::OnBnClickedStartMoveBtn()
{
	ShowPlaceMenu(1);
}

void CRcpDlg::OnBnClickedDestMoveBtn()
{
	ShowPlaceMenu(2);
}

void CRcpDlg::HideSearchPOIDlg()
{
	m_pSearchPOIDlg->ShowWindow(SW_HIDE);
	if(m_pConsignLinkDlg)
	{
		if(m_pConsignLinkDlg->m_bRcpDlgForgroudView)
		{
			m_pConsignLinkDlg->SetFocus();
			if(m_pConsignLinkDlg->m_nWindowType == TOP_WINDOW)
				m_pConsignLinkDlg->CommissionEditFocus();
			else
				m_pConsignLinkDlg->BusNameEditFocus();
		}
	}
}

void CRcpDlg::OnCbnSelchangeDelTypeCombo()
{
	if(!m_bSkipChangeDelType)
	{
		int nSelType = m_cmbDelType.GetCurSel();
		int nType = m_pOrder->CheckDelType(FALSE);

		if(nSelType == 0 && nType != nSelType)
			OnBnClickedOrderStartSameBtn();
		else if(nSelType == 1 && nType != nSelType)
			OnBnClickedOrderDestSameBtn();
		else if(nSelType == 2 && nType != nSelType)
			OnBnClickedOrderDifferentBtn();

		/*if(m_pOrder->GetCNo() > 0)	//신규고객이 아닌 경우만 체인지 가능토록함
		{
			if(nSelType < 2 && nType < 2 && nSelType != nType)
			{
				m_bSkipChangeDelType = TRUE;
				m_pStart->Exchange(m_pDest);
			}
		}

		if(nSelType == 2)
			OnBnClickedOrderDifferentBtn();*/
	}
	m_bSkipChangeDelType = FALSE;
}

void CRcpDlg::OnBnClickedPayTypePreBtn()
{
	SetPayTypeNew(m_pBi->nPayType1);
}

void CRcpDlg::OnBnClickedPayTypeAfterBtn()
{
	SetPayTypeNew(m_pBi->nPayType2);
}

void CRcpDlg::OnBnClickedPayTypeCreditBtn()
{
	SetPayTypeNew(m_pBi->nPayType3);
}

void CRcpDlg::OnBnClickedCarTypeBtn()
{
	SetCarTypeNew(m_pBi->nCarType1);
	//GET_CUR_CHARGE();
	OnCbnSelchangeCarTypeCombo();
}

void CRcpDlg::OnBnClickedCarTypeBtn2()
{
	SetCarTypeNew(m_pBi->nCarType2);
	//GET_CUR_CHARGE();
	OnCbnSelchangeCarTypeCombo();
}

void CRcpDlg::OnBnClickedCarTypeBtn3()
 {
	SetCarTypeNew(m_pBi->nCarType3);	
	//GET_CUR_CHARGE();
	OnCbnSelchangeCarTypeCombo();
}

void CRcpDlg::RefreshOrderLog(int nTNo)
{
	return;
	if(nTNo < 1)
		return; 

	m_lstOrderLog.DeleteAllItems();

	char buffer[20];
	int nItem = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_log", FALSE, TRUE);
	pCmd.SetHideWaitCursor(TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo); 
	if(pRs.Execute(&pCmd)) 
	{
		COleDateTime dtLog;
		int nState, nWNo;
		CString strEtc;

		for(int i=0; i<pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("dtLog", dtLog);
			pRs.GetFieldValue("nState", nState);
			pRs.GetFieldValue("nWNo", nWNo);
			pRs.GetFieldValue("sEtc", strEtc);
			m_lstOrderLog.InsertItem(i, dtLog.Format("%H:%M"));
			m_lstOrderLog.SetItemText(i, 1, LF->GetStateString(nState));

			if(nWNo == m_ui.nWNo)
				m_lstOrderLog.SetItemText(i, 2, "본인");
			else if(nWNo == -1)
				m_lstOrderLog.SetItemText(i, 2, "기사");
			else if(nWNo == -2)
				m_lstOrderLog.SetItemText(i, 2, "서버");
			else
				m_lstOrderLog.SetItemText(i, 2, ltoa(nWNo, buffer, 10));

			m_lstOrderLog.SetItemText(i, 3, strEtc);
			pRs.MoveNext();
		}
		m_lstOrderLog.Populate();
	}
}

void CRcpDlg::OnNMClickLogList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnShowOrderLog();
	*pResult = 0;
}

void CRcpDlg::OnShowOrderLog()
{
	//if(m_lstOrderLog.GetItemCount() == 0)
	//	return;

	if(!IsEditMode())
		return;

	


	CREATE_MODALESS(COrderLogDetailDlg, this);
	pDlg->m_nTNo = m_nInitItem;
	pDlg->m_nState = m_nState;
	pDlg->m_bCross = FALSE;

	if(m_bTodayOrder == TRUE)
	{
		if(m_nReserveAfter > 0)
			pDlg->m_bFullSearch = TRUE;
		else
			pDlg->m_bFullSearch = FALSE;

	}
	else
		pDlg->m_bFullSearch = TRUE;
	
	pDlg->m_nOrderCompany = m_pBi->nCompanyCode;
	SHOW_MODALESS(COrderLogDetailDlg, this);
}

void CRcpDlg::MakeRectangle(CDC *pDC, long nLeftID, long nRightID, BOOL bRightControlToHeight, CRect rcMargin,
							COLORREF clrTopLine, COLORREF clrBottomLine, COLORREF clrLeftLine, COLORREF clrRightLine, 
							long nBorder, long nColSpan)
{
	CWnd *pLeft = GetDlgItem(nLeftID); 
	CWnd *pRight = GetDlgItem(nRightID); 

	if(pLeft == NULL || pRight == NULL)
		return;

	CRect rcOLeft, rcORight;
	pLeft->GetWindowRect(rcOLeft);
	pRight->GetWindowRect(rcORight);
	ScreenToClient(rcOLeft);
	ScreenToClient(rcORight);
	rcOLeft.right = rcORight.right;

	if(bRightControlToHeight)
		rcOLeft.bottom = rcORight.bottom;

	rcOLeft.InflateRect(rcMargin.left, rcMargin.top + nColSpan, rcMargin.right, rcMargin.bottom + nColSpan);

	if(clrTopLine != 0)  
		pDC->FillSolidRect(rcOLeft.left + nBorder, rcOLeft.top, rcOLeft.Width() - nBorder, nBorder, clrTopLine);

	if(clrBottomLine != 0)
		pDC->FillSolidRect(rcOLeft.left + nBorder, rcOLeft.bottom - nBorder, rcOLeft.Width() - nBorder, nBorder, clrBottomLine);

	if(clrLeftLine != 0)
		pDC->FillSolidRect(rcOLeft.left + nBorder, rcOLeft.top + nBorder , nBorder, rcOLeft.Height() - nBorder, clrLeftLine);

	if(clrRightLine != 0)
		pDC->FillSolidRect(rcOLeft.right - nBorder, rcOLeft.top + nBorder , nBorder, rcOLeft.Height() - nBorder, clrRightLine);
}

void CRcpDlg::MakeLine(CDC *pDC, long nLeftID, long nTopID, long nRightID, long nBottomID,
					   long nLeftOfffset, long nRightOffset,
					   COLORREF clrLine)
{
	CWnd *pLeft = GetDlgItem(nLeftID);
	CWnd *pTop = GetDlgItem(nTopID); 
	CWnd *pRight = GetDlgItem(nRightID);
	CWnd *pBottom = GetDlgItem(nBottomID); 

	if(pTop == NULL || pBottom == NULL)
		return;

	CRect rcLeft, rcTop, rcRight, rcBottom;
	pLeft->GetWindowRect(rcLeft);
	pTop->GetWindowRect(rcTop);
	pRight->GetWindowRect(rcRight);
	pBottom->GetWindowRect(rcBottom);

	ScreenToClient(rcLeft);
	ScreenToClient(rcTop);
	ScreenToClient(rcRight);
	ScreenToClient(rcBottom);

	long nCenter = (rcTop.bottom + rcBottom.top) / 2;
	pDC->FillSolidRect(rcLeft.left + nLeftOfffset, nCenter - 1, rcRight.right + nRightOffset, 2 , clrLine);
} 

void CRcpDlg::OnCbnSelchangeCarTypeCombo()
{ 
	ChangeCargoControl();
	GetSectionCharge(TRUE, FALSE, FALSE);
	RefreshProperCharge();
}

void CRcpDlg::OnCbnSelchangePayTypeCombo()
{ 

	int nPrePayType = m_cmbPayType.GetCurSel();
	if(m_cmbPayType.GetCurSel() == 5)
		m_nPayType = PAY_CARD;
	else
		m_nPayType = m_cmbPayType.GetCurSel();

	if(m_nPayType == PAY_AFTER &&  
		m_pDest->IsCredit() && 
		m_pOrder->GetCNo() != m_pDest->GetCNo())
	{
		if(CRcpDlgSetupDlg::m_info.nCopyDestCreditCustomer ||
			IDYES == MessageBox("도착지가 신용거래처 이면서, 착불로 설정하셨습니다.\n"\
			"도착지->의뢰지로 복사하고, 신용으로 설정하시겠습니까?\n\n"\
			"(변경할경우 고객정산시 편리함)", 
			"도착지 신용거래처, 착불",
			MB_ICONQUESTION | MB_YESNO))
		{
			m_pOrder->Copy(m_pDest);
			SetPayTypeNew(PAY_CREDIT);
			m_EDT_ETC.pEdit->GetWindowText(m_strEtc);
			m_EDT_ETC.pEdit->SetWindowText(m_strEtc + "[착불/신용고객 의뢰지로 복사함]");
		}
	}
	CString sCharge = "";
		// 선불;착불;신용;송금;수금;카드;마일;
	switch (m_cmbPayType.GetCurSel())
	{
	case  0:  // 선불
	case  1:  // 착불
	case 2: // 신용
	case 3: // 송금
	case 4: // 수금
	case 5: // 카드
		//m_edtAutoCharge.SetWindowText(""); 
		
		//m_edtAutoCharge.ShowWindow(SW_HIDE);
		m_edtMileReserve.ShowWindow(SW_SHOW);
		m_chkAutoCharge.SetWindowText("X");	
		break;
	}

	OnEnChangeRiderAutoChargeEdit();
		

	// 지불은 굳이 요금이 변동될 이유가 없을거 같다.
	//GET_CUR_CHARGE();
	//GetSectionCharge();
}

void CRcpDlg::OnCbnSelchangeWayTypeCombo()
{
	m_nWayType = m_cmbWayType.GetCurSel();
	//GET_CUR_CHARGE();
	GetSectionCharge(FALSE, FALSE, TRUE);
}

void CRcpDlg::OnCbnSelchangeRunTypeCombo()
{
	if(m_cmbRunType.GetCurSel() == TWO)		
		m_nRunType = RUN_FAST;
	else if(  m_cmbRunType.GetCurSel() == THREE)
		m_nRunType = RUN_VERY_FAST;
	else if(m_cmbRunType.GetCurSel() == FOUR)
		m_nRunType = RUN_TOGETHER;
	else
		m_nRunType = m_cmbRunType.GetCurSel(); 

	//GET_CUR_CHARGE();
	/*if(LF->IsThisCompany("엔콜") || LF->IsThisCompany("로지") )
	{
		if(m_pCharge)
		{
			if(!IsPreChangePOI()  && m_pCharge->IsCashCharge())
				m_pCharge->SetCashCharge(FALSE);
		}
	}*/
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedContextChargeBtn()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_QUERY, "요금문의");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_WNO_REGISTION, "문의 접수자 등록");
	//pMenu->AppendMenu(MF_SEPARATOR);
	//pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_REFRESH, "요금갱신");
	//pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_SEE, "요금표보기");
	//pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_CLOSE, "요금표닫기");
	pMenu->AppendMenu(MF_SEPARATOR);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CONSIGN_MODE, "탁송요금 정보보이기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_MODE, "마일리지 정보보이기");

	pMenu->AppendMenu(MF_SEPARATOR);
	//pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_REFRESH_BASIC, "기사정보창 보시");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_DEPOSIT_REFRESH, "입금액갱신[합계]");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_DEPOSIT_REFRESH_BASIC, "입금액갱신[기본]");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHARGE_DEPOSIT_EDIT, "입금테이블수정");

	pMenu->AppendMenu(MF_SEPARATOR);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_PAY_CASH, "현금영수증발행");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_RE_SEND_EMAIL, "카드결제 이메일재발송");


	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CRcpDlg::DisplayReserveInfo()
{
	CString strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='left' VerticalAlignment='center'>";
	if(!IsReserve())
	{ 
		//strTemp += " <Run Foreground='Black' FontWeight='Bold'> 예약오더가 아닙니다</Run>";
		m_stcReserveDisplay.ShowWindow(SW_HIDE);
	} 
	else
	{
		CString strTime;
		strTemp += "예약 <Run Foreground='blue' FontWeight='Normal'>" + GetReserveTimeString() + "</Run> ";

		if(GetReleaseMin() > 0)
		{
			strTime.Format("[%d]", m_pReserveOrderDlg->GetReleaseMin());
			strTime = "<Run Foreground='Red' FontWeight='Normal'>" + strTime + "</Run>";
			strTime += "<Run Foreground='Black' FontWeight='Normal'>분전에</Run> ";

			strTemp += strTime;
		}

		strTime = IsReleaseAfterWait() ? "[대기]" : "[접수]";
		strTime = "<Run Foreground='green' FontWeight='Normal'>" + strTime + "</Run>";
		strTime += "<Run Foreground='Black' FontWeight='Normal'>로 예약해지됨!!</Run>";

		strTemp += strTime;
		m_stcReserveDisplay.ShowWindow(SW_SHOW);

		/*if(m_pBi)
			if(LU->IsTimeChargeCompany(m_pBi->nCompanyCode))
				RefreshCharge();*/
	}

	strTemp += "</TextBlock>";

	m_stcReserveDisplay.SetMarkupText(strTemp);
	AfxGetApp()->WriteProfileInt("RcpDlg", "ReserveAfterWait", IsReleaseAfterWait());
	AfxGetApp()->WriteProfileInt("RcpDlg", "ReserveMin", GetReleaseMin());

}

void CRcpDlg::MakeSearchManagerDlg()
{
	if(m_pSearchManagerDlg == NULL)
	{
		m_pSearchManagerDlg = new CSearchManagerDlg();
		m_pSearchManagerDlg->m_pRcpDlg = this;
		m_pSearchManagerDlg->Create(IDD_SEARCH_MANAGER_DLG, this);
	}
}

void CRcpDlg::MakeReserveDlg()
{
	if(m_pReserveOrderDlg == NULL)
	{
		m_pReserveOrderDlg = new CReserveOrderDlg();
		m_pReserveOrderDlg->m_pRcpDlg = this;
		m_pReserveOrderDlg->Create(IDD_RESERVE_ORDER_DLG, this);
	}
}

void CRcpDlg::OnBnClickedReserveBtn()
{
	ShowReserveDlg();
}

void CRcpDlg::ShowReserveDlg()
{
	if(m_pReserveOrderDlg == NULL) 
		MakeReserveDlg();

	m_stcReserveDisplay.ModifyStyle(0, SS_NOTIFY);

	CRect rcReserveDlg, rcStc, rcTitle;
	m_pReserveOrderDlg->GetWindowRect(rcReserveDlg); 
	GetDlgItem(IDC_RCP_STATIC31)->GetWindowRect(rcStc);
	GetDlgItem(IDC_TITLE_STATIC)->GetWindowRect(rcTitle);

	ScreenToClient(rcReserveDlg);
	ScreenToClient(rcStc);
	ScreenToClient(rcTitle);

	long nWidht = rcReserveDlg.Width();
	long nHeight = rcReserveDlg.Height();

	rcReserveDlg.top = rcTitle.bottom + 1;
	rcReserveDlg.bottom = rcReserveDlg.top + nHeight;
	rcReserveDlg.left = rcStc.left;
	rcReserveDlg.right = rcReserveDlg.left + nWidht;

	m_pReserveOrderDlg->MoveWindow(rcReserveDlg);
	m_pReserveOrderDlg->ShowWindow(SW_SHOW);

	if(!IsReserve())
	{ 
		if(LF->IsThisCompany("코리아바이크") || LF->IsThisCompany("엔콜"))
			m_pReserveOrderDlg->SetReserveTime(COleDateTime::GetCurrentTime());
		else
			m_pReserveOrderDlg->SetReserveTime(COleDateTime::GetCurrentTime() + COleDateTimeSpan(0, 1, 0, 0));
	}
	m_pReserveOrderDlg->OnDisplayReserveInfo();
	m_pReserveOrderDlg->MakeAddTime();
	m_pReserveOrderDlg->m_dtpTime.SetFocus();
	HideReserveBehindControl(TRUE);
}

void CRcpDlg::HideReserveBehindControl(BOOL bHide, BOOL bConstruct)
{
	CPtrArray pa;
	pa.Add(GetDlgItem(IDC_TITLE_STATIC));

	if(bConstruct == FALSE)
	{
		if(m_pBi)
		{
			if(LU->IsTimeChargeCompany(m_pBi->nCompanyCode))
			{
				CheckDrivingChargeChange();
				RefreshCharge(TRUE, FALSE); //창이 열릴때 Add값이 초기화
			}
		}
	}
	
	LF->HideBehindControl(this, m_pReserveOrderDlg, bHide, &pa);
}

void CRcpDlg::OnBnClickedCidMenuBtn()
{
	CPoint pt; 
	GetCursorPos(&pt);
	CMenu *pMenu = new CMenu;
	pMenu->CreatePopupMenu();
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_REG_JINSANG, "수신차단고객등록(CTI만 가능)");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MAKE_CALL_CID, "전화걸기");

	if(m_EDT_CID.pEdit->GetWindowTextLength() > 0)
	{
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ADD_CID, "의뢰지 전화 저장");
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_COPY_CID, "의뢰지 휴대로 복사");
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CRcpDlg::OnMenuContextCID(UINT nID)
{
	if(nID == ID_MENU_REG_JINSANG)
	{
		CString strPhone1 = "";

		if(IsEditMode())
			m_EDT_ORDER_PHONE.pEdit->GetWindowText(strPhone1);
		else
			m_EDT_CID.pEdit->GetWindowText(strPhone1);

		strPhone1 = LF->GetNoneDashNumber(strPhone1);


		if( !strPhone1.IsEmpty() )
		{
			if(strPhone1[0] != '0')
			{
				strPhone1 = m_ci.m_strDDD + strPhone1;
			}
		}

		if((strPhone1.GetLength() < 9) ||
			(LF->IsStringDigit(strPhone1) == FALSE))
		{
			MessageBox("번호가 유효하지 않습니다", "확인", MB_ICONINFORMATION);
			return;
		}

		CJinsangTelRegDlg dlg;
		dlg.m_nDuration  = 3650;
		dlg.m_sTelNumber = strPhone1;

		if( IDOK != dlg.DoModal() )
		{
			return;
		}

		//	szDenialPhoneNumber,szDenialDuration,szName,szDesc
		CString szDenialDuration;
		szDenialDuration.Format("%d",dlg.m_nDuration*24*60);

		if(m_pRcpView->m_pCTIForm->m_bConnected)
		{
			m_pRcpView->m_pCTIForm->m_call.DenialAnswer(dlg.m_sTelNumber, atol(szDenialDuration), dlg.m_sName, dlg.m_sDesc);
			MessageBox("진상고객 전화거부 등록하였습니다.", 
				"진상고객 전화거부 등록(CTI)", 
				MB_ICONINFORMATION);
		}
		else
		{
			char data[500] = {0,};
			STRCPY(data, "B",VL_END); 
			STRCAT(data, (LPSTR)(LPCTSTR) dlg.m_sTelNumber,VL_END); //진상고객전화
			STRCAT(data, (LPSTR)(LPCTSTR) szDenialDuration,VL_END);	//거부기간
			STRCAT(data, (LPSTR)(LPCTSTR) dlg.m_sName,VL_END);	//진상고객이름
			STRCAT(data, (LPSTR)(LPCTSTR) dlg.m_sDesc,VL_END);	//진상이유

			if(LU->SendCopyDataToTelClient(data, CALL_TO_CUSTOMER))
			{
				MessageBox("진상고객 전화거부 등록을 요청하였습니다.", 
					"진상고객 전화거부 등록", 
					MB_ICONINFORMATION);
			}
			else
			{
				MessageBox("진상고객 전화거부 등록 요청 실패\n텔클라이언트의 실행여부를 확인하시기 바랍니다.", 
					"진상고객 전화거부 등록 실패", 
					MB_ICONINFORMATION);
			}
		}
	}
	else if(nID == ID_MENU_MAKE_CALL_CID)
	{
		m_EDT_CID.pEdit->GetWindowText(m_strCID);
		m_pRcpView->MakeCall(m_pBi->nCompanyCode, LF->GetNoneDashNumber(m_strCID), CALL_TO_CUSTOMER);
	}
	else if(nID == ID_MENU_ADD_CID)
	{
		m_EDT_CID.pEdit->GetWindowText(m_strCID);
		if(LF->AddCustomerTel(m_pBi->nCustomerTable, m_pOrder->GetCNo(), m_pOrder->GetTelID(), m_strCID))
		{
			MessageBox("등록되었습니다", "확인", MB_ICONINFORMATION);
		}
		//m_pRcpView->MakeCall(m_pBi->nCompanyCode, LF->GetNoneDashNumber(m_strCID), CALL_TO_CUSTOMER);
	}
	else if(nID == ID_MENU_COPY_CID)
	{
		m_EDT_CID.pEdit->GetWindowText(m_strCID);
		m_edtOrderMP.SetWindowText(m_strCID);
	}
}

void CRcpDlg::ReInitControl()
{
	//if(IsInsungDlg() == FALSE)
	ChangeRcpDlgSize(TRUE, TRUE);

	m_bReadyToReuse = FALSE;
	m_bRiderSmsSend = FALSE;
	m_bAllocRider = FALSE;

	m_pOrder->Clear();
	m_pStart->Clear();
	m_pDest->Clear();

	m_lstOrderLog.DeleteAllItems();

	m_EDT_CID.pEdit->SetWindowText("");
	m_EDT_TNO.pEdit->SetWindowText("");
	m_EDT_STATE.pEdit->SetWindowText("");
	m_EDT_WNAME.pEdit->SetWindowText("");
	m_edtIntercallEtc.SetWindowText("");
	m_stcChargeViaBet.SetMarkupText("");
	m_cmbItemType.ResetContent();
	m_cmbItemType.SetWindowText("");

	m_CMB_CHARGE_TYPE.pCombo->SetCurSel(0);
	m_EDT_CHARGE_BASIC.pEdit->SetWindowText("");
	m_EDT_CHARGE_ADD.pEdit->SetWindowText("");
	m_EDT_CHARGE_DRIVING.pEdit->SetWindowText("");
	m_EDT_CHARGE_DIS.pEdit->SetWindowText("");
	m_edtDeposit.SetWindowText("");
	m_EDT_CHARGE_SUM.pEdit->SetWindowText("");
	m_edtValueAdd.SetWindowText("");
	m_EDT_CHARGE_TRANS.pEdit->SetWindowText("");
	m_edtAutoCharge.SetWindowText("");
	m_edtChargeSumTotal.SetWindowText("");
	m_edtConBackOrderCharge.SetWindowText("");
	m_edtConCommissionCharge.SetWindowText("");
	m_edtConTotalCharge.SetWindowText("");

	m_cmbCouponCharge.SetCurSel(0);
	m_cmbCouponType.SetCurSel(0);
	m_edtMileageBalance.SetWindowText("");

	m_edtChargeReturn.SetWindowText("");
	m_EDT_ETC.pEdit->SetWindowText("");
	m_stcReserveDisplay.SetMarkupText("");
	m_stcRiderInfo.SetMarkupText("");
	m_stcRiderCompany.SetMarkupText("");
	m_stcRiderPhone.SetMarkupText("");

	m_edtProperCharge1.SetWindowText("");
	m_edtProperCharge2.SetWindowText("");

	m_nDiscountRange = 0;
	m_bDirtyBasicCharge = FALSE;
	m_nLoadChargeBasic = 0;
	m_chkSaveCharge.SetCheck(FALSE);

	m_strChargeAdd = "";
	m_strChargeBasic = "";
	m_strChargeDriving = "";	
	m_strChargeDis = "";
	m_strChargeSum = "";
	m_strChargeTrans = "";
	m_nConsignTNo = FALSE;

	m_strConBackOrderCharge = "0";
	m_strConTotalCharge = "0";
	m_sConCommissionCharge = "0";
	m_nConsignTNo = 0;
	m_nTerminalWayID = 0;
	m_strConsignCity = "";
	m_nConsignCompany = 0;
	m_dt1.SetDateTime(1900,1,1,0,0,0);
	m_nPreRiderAutoCharge = 0;

	//m_bConsignLink = FALSE;
	m_strMileReserve = "";
	m_edtConCommissionCharge.SetWindowText("");
	m_edtConBackOrderCharge.SetWindowText("");
	m_edtConTotalCharge.SetWindowText("");
	m_edtMileReserve.SetWindowText("");
	m_chkAutoCharge.SetWindowText("X"); 
	m_edtMileReserve.ShowWindow(SW_SHOW);
	m_edtAutoCharge.ShowWindow(SW_HIDE);
	m_edtChargeCompany.SetWindowText("");

	m_chkShowPhoneTypeOrder.SetCheck(FALSE);
	m_chkShowPhoneTypeStart.SetCheck(FALSE);
	m_chkShowPhoneTypeDest.SetCheck(FALSE);

	if(!m_bAllocRider)
		m_btnRiderSmsSend.SetWindowText("타사기사검색");
	if(m_nInitItem < 0)
		m_btnRiderSearch.SetWindowText("자사기사검색");
		
	((CStatic*)GetDlgItem(IDC_RCP_STATIC51))->SetWindowText("마일적립");
	m_edtMileReserve.SetUserBkColor(RGB(255, 255, 255));
	SetConsignMode(FALSE);	

	if(m_pReserveOrderDlg)
	{
		m_pReserveOrderDlg->InitControl();
		HideReserveBehindControl(FALSE, TRUE);
		DisplayReserveInfo();
	}
	m_pConsignLinkDlg = NULL;

	for(int i=ZERO; i<m_CMB_BRANCH.pCombo->GetCount(); i++)
	{
		if(m_CMB_BRANCH.pCombo->GetItemData(i) ==m_pBi->nCompanyCode)
		{
			m_CMB_BRANCH.pCombo->SetCurSel(i);
			break;
		}
	}

	m_chkFoodOrder.SetCheck(FALSE);
	m_chkDirectDistance.SetCheck(FALSE);
	m_chkClientShareOrder.SetCheck(FALSE);

	if(LF->IsThisCompany("사천퀵", m_pBi->nCompanyCode))
		SetGrade(-100); //노란색 
	else
		SetGrade(0);

	m_chkAbleAllocLoadIns.SetCheck(m_pBi->bOnlyLoadInsRider);

	m_CMB_ALLOC_GROUP.pCombo->SetCurSel(-1);

	m_chkCargoJabara.SetCheck(FALSE);
	m_chkCargoLift.SetCheck(FALSE);
	m_chkCargoWingBody.SetCheck(FALSE);
	m_chkCargoLiftWing.SetCheck(FALSE);
	m_chkCargoFreezer.SetCheck(FALSE);
}

AFX_INLINE BOOL CRcpDlg::IsCarType(int nCarType)
{
	return m_cmbCarType.GetCurSel() == nCarType;
}

AFX_INLINE BOOL CRcpDlg::IsPayType(int nPayType)
{
	return m_cmbPayType.GetCurSel() == nPayType;
}

AFX_INLINE BOOL CRcpDlg::IsWayType(int nWayType)
{
	return m_cmbWayType.GetCurSel() == nWayType;
}

AFX_INLINE BOOL CRcpDlg::IsRunType(int nRunType)
{
	return m_cmbRunType.GetCurSel() == nRunType;
}

void CRcpDlg::OnSize(UINT nType, int cx, int cy)
{
	CRcpDlgBase::OnSize(nType, cx, cy);
}

void CRcpDlg::OnBnClickedRiderMenuBtn()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	if(!IsEditMode())
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_RIDER_ALLOC_CANCEL, "개별취소"); //신규등록시

	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_RIDER_ALLOC, "자사기사에게 배차하기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_RIDER_ALLOC_OTHER, "타회사기사에게 개별배차");
	pMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_RIDER_CALL, "기사에게 전화걸기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_RIDER_POS, "기사위치 보기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW, "기사정보창 보기");

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CRcpDlg::OnMenuContextRider(UINT nID)
{
	if(nID == ID_MENU_RIDER_ALLOC_CANCEL)
	{
		InitRiderInfo();
	}
	else if(nID == ID_MENU_RIDER_ALLOC)
	{
		/*if(m_nRiderCompany > ZERO && m_nRNo > ZERO)
		{
			LU->ShowRiderInfoDlg(m_nRiderCompany, m_nRNo);
			return;
		}*/

		CString sStart; m_EDT_START_DONG.pEdit->GetWindowText(sStart);
		CString sDest; m_EDT_DEST_DONG.pEdit->GetWindowText(sDest);

		CString strTitle = "[개별] " + sStart + " -> " + sDest;
		CString strDeposit; m_edtDeposit.GetWindowText(strDeposit);

		LU->OpenAllocateDlg(m_nInitItem, m_nState, strTitle, m_nRNo, atoi(strDeposit), GetCarTypeNew(), FALSE, this);
	}
	else if(nID == ID_MENU_RIDER_ALLOC_OTHER)
	{
		CString strDeposit; m_edtDeposit.GetWindowText(strDeposit);
		LU->OpenOtherAllocateDlg(m_nInitItem, m_pBi->nCompanyCode, m_nState, atoi(strDeposit), FALSE, this);
	}
	else if(nID == ID_MENU_RIDER_CALL)
	{
		LU->ShowCallPhoneRiderDlg(m_nRiderCompany, m_nRNo, m_pBi->nCompanyCode, FALSE);
	}
	else if(nID == ID_MENU_RIDER_POS)
	{
		OnBnClickedShowRiderPosBtn();
	}
	else if(nID == ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW)
	{
		if(m_nRiderCompany > 0 && m_nRNo > 0)
			LU->ShowRiderInfoDlg(m_nRiderCompany, m_nRNo, -1, -1, "");
	}
	//else if(nID == ID_MENU_ALLOCATE)

}

void CRcpDlg::SendMsgForReserve()
{
	CMkCommand cmd(m_pMkDb, "send_sms_for_reserve");
	cmd.AddParameter(m_nInitItem);
	cmd.Execute();
}

LONG CRcpDlg::OnGetAllocateRider(WPARAM wParam, LPARAM lParam)
{	
	ST_RIDER_WORK_STATE_INFO *pInfo = (ST_RIDER_WORK_STATE_INFO*)wParam;
	BOOL bInsert = (BOOL)lParam;

	m_bAllocRider = TRUE;
	m_bAllocRiderMyRider = (BOOL)lParam;
	m_nRiderCompany = pInfo->nCompany;
	m_nRNo = pInfo->nRNo;
	m_strRiderName = pInfo->strName;
	m_strRPhone = pInfo->strPhone;

	delete pInfo;
	pInfo = NULL;

	DisplayRiderInfo();

	if(m_nState == STATE_RESERVED || 
		(m_pReserveOrderDlg != NULL && IsReserve())) 		//(!IsEditMode() && m_pReserveOrderDlg != NULL && m_pReserveOrderDlg->IsReserve()))
	{
		if(m_nState != STATE_RESERVED && m_nState != STATE_OK_ONLY_MAN)
			m_bAllocRiderChangeTime = 1;
		else
		{
			CCustomMyAfxMessgagebox dlg;
			long nRet = dlg.DoModal();

			if(nRet == IDOK)
				m_bAllocRiderChangeTime = dlg.m_nType;
			else if(nRet == IDCANCEL)
				InitRiderInfo();
		}
	}

	if(bInsert)
	{
		if(!IsEditMode())
			OnBnClickedNewBtn();
		else
			OnBnClickedUpdateBtn();
	}

	return 0;
}

void CRcpDlg::DisplayRiderInfo()
{
	/*CString strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='left' VerticalAlignment='center'>";
	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{ 
		CString strTime;
		char buffer[10];

		if(m_ci.IsChildCompany(m_nRiderCompany)) //자사
			strTemp += " <Run Foreground='blue' FontWeight='Normal'>";
		else
			strTemp += " <Run Foreground='green' FontWeight='Normal'>";

		strTemp += m_strRiderName + "/";
		strTemp += CString(itoa(m_nRNo, buffer, 10)) + "/";
		strTemp += m_ci.GetName(m_nRiderCompany);
		strTemp += "</Run> ";
	} 

	strTemp += "</TextBlock>";*/

	CString strTitle = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='left' VerticalAlignment='center'>";
	CString strRiderInfo, strRiderCompany, strRiderPhone;
	CString strEnd = "</TextBlock>";
	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{ 
		if(m_ci.IsChildCompany(m_nRiderCompany)) //자사
			strRiderCompany = " <Run Foreground='blue' FontSize='13' FontWeight='Normal'>";
		else
			strRiderCompany = " <Run Foreground='green' FontSize='13' FontWeight='Normal'>";

		char buffer[10];
		strRiderInfo = "<Run Foreground='black' FontSize='13' FontWeight='Normal'> "+ m_strRiderName + "/" + CString(itoa(m_nRNo, buffer, 10)) + "</Run>";
		strRiderCompany += m_ci.GetName(m_nRiderCompany) + "/" + m_ci.GetPhone(m_nRiderCompany) + "</Run>";
		strRiderPhone = "<Run Foreground='black' FontSize='13' FontWeight='Normal'> "+ LF->GetDashPhoneNumber(m_strRPhone) + "</Run>";

		m_btnRiderSearch.SetWindowText("기사정보");
		m_btnRiderSmsSend.SetWindowText("독촉문자");
		m_bRiderSmsSend = TRUE;
	}
	else
	{
		
		m_btnRiderSearch.SetWindowText("자사기사검색");
		m_btnRiderSmsSend.SetWindowText("타사기사검색");
		m_bRiderSmsSend = FALSE;
	}

	m_stcRiderInfo.SetMarkupText(strTitle + strRiderInfo + strEnd);
	m_stcRiderCompany.SetMarkupText(strTitle + strRiderCompany + strEnd);
	m_stcRiderPhone.SetMarkupText(strTitle + strRiderPhone + strEnd);
}

void CRcpDlg::AllocateRider(long nTNo, long nState, long nDeposit)
{
	if(m_nRiderCompany <= 0 || m_nRNo <= 0)
		return;

	if(m_bAllocRiderChangeTime == 1 || m_pReserveOrderDlg->m_bChangeRiderForReserve == 0)
	{
		LU->UpdateRiderInfoForReserveOrder(nTNo, m_nRiderCompany, m_nRNo); 
		SendMsgForReserve();
		m_bAllocRiderChangeTime = -1;
		m_pReserveOrderDlg->m_bChangeRiderForReserve = -1;
	}
	else //바로 배차
	{
		if(m_bAllocRiderMyRider == FALSE)
		{
			if(!m_ci.IsChildCompany(m_nRiderCompany))
			{
				if(LU->IsOtherShareBalanceOk(nDeposit, m_nRiderCompany) == FALSE)
				{
					MessageBox("기사님 소속사의 공동금액잔액이 부족하여 개별배차를 내리실 수 없습니다.", "확인", MB_ICONINFORMATION);
					return;
				}
			}			
		}

		m_pRcpView->GetStateChange()->Allocate(nTNo, m_nRNo, nState, m_nRiderCompany);
		m_bAllocRiderChangeTime = -1;
	}
}

void CRcpDlg::SetConsignInit()
{
	m_edtConCommissionCharge.SetWindowText("0");
	m_edtConBackOrderCharge.SetWindowText("0");
	m_edtConTotalCharge.SetWindowText("0");



}

void CRcpDlg::SetConsignViewInfo(long nConsignTNo,long nConsignCommission,long nBackOrderChargeSum)
{
	if(m_nInitItem > ZERO && m_nConsignTNo > ZERO)
	{
		m_btnConsignView.SetWindowText("탁송모드");
		m_btnConsignView.SetState(TRUE);
		//m_btnConsignView.Set


		m_edtConBackOrderCharge.SetWindowText(LF->GetMyNumberFormat(nBackOrderChargeSum));
		m_edtConCommissionCharge.SetWindowText(LF->GetMyNumberFormat(nConsignCommission));

		if(!m_bConsignLink)
			RefreshConsignCharge();
	}
}
void CRcpDlg::SetConsignMode(BOOL bConsignMode)
{
	if(bConsignMode)
	{

		CRect rCommision, rBackOrderCharge, rTotalCharge, rCommisionRight, rCommisionMove;
		CRect rCouphoneStc, rMileageStc, rAftetChargeStc;
		m_edtAutoCharge.GetWindowRect(rBackOrderCharge);
		m_edtMileageBalance.GetWindowRect(rTotalCharge);
		m_cmbCouponCharge.GetWindowRect(rCommision);
		m_cmbCouponType.GetWindowRect(rCommisionRight);

		GetDlgItem(IDC_RCP_STATIC54)->GetWindowRect(rCouphoneStc); // 쿠폰
		GetDlgItem(IDC_RCP_STATIC51)->GetWindowRect(rMileageStc); // 후불
		GetDlgItem(IDC_RCP_STATIC55)->GetWindowRect(rAftetChargeStc); // 마일리지

		rCommisionMove.left = rCommision.left;
		rCommisionMove.top = rCommision.top;
		rCommisionMove.bottom = rCommision.bottom;
		rCommisionMove.right = rCommisionRight.right - 5 ;

		rTotalCharge.bottom += 3;

		ScreenToClient(rBackOrderCharge);
		ScreenToClient(rTotalCharge);
		ScreenToClient(rCommisionMove);

		ScreenToClient(rCouphoneStc);
		ScreenToClient(rMileageStc);
		ScreenToClient(rAftetChargeStc);

		m_edtConCommissionCharge.MoveWindow(&rCommisionMove,TRUE);
		m_edtConTotalCharge.MoveWindow(&rTotalCharge, TRUE);
		m_edtConBackOrderCharge.MoveWindow(&rBackOrderCharge, TRUE);

		m_stcConCommissionCharge.MoveWindow(rCouphoneStc);		
		m_stcConBackOrderCharge.MoveWindow(rMileageStc);
		m_stcConTotalCharge.MoveWindow( rAftetChargeStc );

	}
	else
	{

		m_edtConBackOrderCharge.SetWindowText("");
		m_edtConCommissionCharge.SetWindowText("");
		m_edtConTotalCharge.SetWindowText("");
	}


	long bConShow = bConsignMode ? SW_SHOW : SW_HIDE;
	long bMileageShow = bConsignMode ?  SW_HIDE : SW_SHOW;

	m_edtConCommissionCharge.ShowWindow(bConShow);
	m_edtConTotalCharge.ShowWindow(bConShow);
	m_edtConBackOrderCharge.ShowWindow(bConShow);

	m_stcConCommissionCharge.ShowWindow(bConShow);		
	m_stcConBackOrderCharge.ShowWindow(bConShow);
	m_stcConTotalCharge.ShowWindow(bConShow);


	m_edtAutoCharge.ShowWindow(bMileageShow);
	m_edtMileageBalance.ShowWindow(bMileageShow);
	//m_cmbCouponType.ShowWindow(FALSE);
	//m_cmbCouponCharge.ShowWindow(FALSE);
	//m_cmbCouponType.ShowWindow(bMileageShow);
	//m_cmbCouponCharge.ShowWindow(bMileageShow);

	//GetDlgItem(IDC_RCP_STATIC54)->ShowWindow(bMileageShow);
	GetDlgItem(IDC_RCP_STATIC51)->ShowWindow(bMileageShow);
	GetDlgItem(IDC_RCP_STATIC55)->ShowWindow(bMileageShow);

	GetDlgItem(IDC_RCP_STATIC54)->ShowWindow(bMileageShow);
	m_cmbCouponCharge.ShowWindow(bMileageShow);
	m_cmbCouponType.ShowWindow(bMileageShow);
}

BOOL CRcpDlg::CheckDeposit()
{
	m_strDeposit.Remove(',');

	if(atol(m_strDeposit) == 0)
	{
		if(!(m_pBi->nShareCode2 == 0 && m_pBi->nShareCode3 == 0 &&
			m_pBi->nShareCode4 == 0 && m_pBi->nShareCode5 == 0))
		{
			long nDeposit = 0;

			if(!m_pBi->IsCargo())
			{
				if(m_bDepositMessage == TRUE)
				{
					if(MessageBox("입금액이 0원입니까?", "확인", MB_OKCANCEL) != IDOK)
						return FALSE;


					/*
					if(GetPayTypeNew() == CAR_TRUCK && m_pBi->nTruckDeposit > 0)
					{
					nDeposit = atoi(m_strChargeDriving) * m_pBi->nTruckDeposit * 0.01;
					sTemp.Replace("20", "10");
					}
					else
					nDeposit = atoi(m_strChargeDriving) * 0.23;

					if(nDeposit == ZERO)
					nDeposit = atoi(m_strChargeSum) * 0.23;

					m_strDeposit.Format("%d", nDeposit);
					m_edtDeposit.SetWindowText(LF->GetMyNumberFormat(m_strDeposit));
					*/
				}				
			}
		}
	}
	else if(m_pBi->IsCargo())
	{
		m_strDeposit = "";
		m_edtDeposit.SetWindowText("");
	}

	return TRUE;
}

void CRcpDlg::CheckMileage(long &nMileageSetting, long &nMileageAutoCharge)
{
	CString sMileageSetting = "", sMileageAuto = "", sValue = "";	
	m_edtAutoCharge.GetWindowText(sValue);
	sValue.Replace(",", "");
	if(m_chkAutoCharge.GetCheck())
	{
		nMileageSetting = 0;
		nMileageAutoCharge = atol(sValue);
	}
	else
	{
		nMileageSetting = atol(sValue);
		nMileageAutoCharge = 0;
	}
}

void CRcpDlg::OnBnClickedEtcBtn()
{
	CPoint pt;
	GetCursorPos(&pt);

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CHECK_MENU);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(0);

	if(m_pBi->sEtcUserTitle1 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER1, m_pBi->sEtcUserTitle1, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER1, MF_BYCOMMAND);

	if(m_pBi->sEtcUserTitle2 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER2, m_pBi->sEtcUserTitle2, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER2, MF_BYCOMMAND);

	if(m_pBi->sEtcUserTitle3 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER3, m_pBi->sEtcUserTitle3, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER3, MF_BYCOMMAND);

	if(m_pBi->sEtcUserTitle4 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER4, m_pBi->sEtcUserTitle4, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER4, MF_BYCOMMAND);

	CString sRegTitle, sRegMemo;

	sRegTitle =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Title", "");
	sRegMemo =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	if(sRegTitle != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER5, sRegTitle, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER5, MF_BYCOMMAND);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CRcpDlg::OnMenuContextMileage(UINT nFlag)
{
	if(nFlag == ID_MENU_MILEAGE_LOG)
	{
		OnMileagePopupWindow();
	}
	else if(nFlag == ID_MENU_MILEAGE_COUNT_LOG)
	{
		OnMenuCountMileageLog();
	}
	else if(nFlag == ID_MENU_MAILEAGE_NOT_COMPANY)
	{
		OnNotCompanyMileage();
	}
	else if(nFlag == ID_MENU_MILEAGE_NOT_ORDER1)
	{
		OnNotOrderMileage();
	}
	else if(nFlag == ID_MENU_MILEAGE_USE_ORDER1)
	{
		OnUseOrderMileage();
	}
	else if(nFlag == ID_MENU_MILEAGE_USER_ORDER)
	{
		OnUserMileage();
	}
	else if(nFlag == ID_MENU_CONSIGN_MODE)
	{
		OnMenuConsignMode();
	}					      
	else if(nFlag == ID_MENU_MILEAGE_MODE)
	{
		OnMenuMileageMode();
	}
}

void CRcpDlg::OnBnClickedContextMileageBtn()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_LOG, "마일리지 로그보기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_COUNT_LOG, "사용횟수 로그보기");
	pMenu->AppendMenu(MF_SEPARATOR);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MAILAGE_MODE, "마일리지 모드보기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CONSIGN_MODE, "탁송관련 모드보기");

	pMenu->AppendMenu(MF_SEPARATOR);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MAILEAGE_NOT_COMPANY, "업체 적용안함(영구적 잔액0원)");
	pMenu->AppendMenu(MF_SEPARATOR);
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_NOT_ORDER1, "해당오더만 적용안함(1회성)");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_USE_ORDER1, "해당오더 마일리지 표준적용");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MILEAGE_USER_ORDER, "해당오더만 사용자금액입력");
	
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;	
}

void CRcpDlg::ShowSign()
{
	CSignDlg dlg;
	dlg.m_nTNo = m_nInitItem;
	dlg.m_nCNo = m_pOrder->GetCNo();
	dlg.DoModal();
}

void CRcpDlg::OnMenuContextFunc(UINT nFlag)
{
	if(nFlag == ID_MENU_FUNC_PASS_DATA)
	{
		//MessageBox("준비중 입니다", "확안", MB_ICONINFORMATION);
		//return;

		OnPassData();
	}
	else if(nFlag == ID_MENU_FUNC_USAGE_HISTORY)
	{
		ShowUsageHistory();
	}
	else if(nFlag == ID_MENU_FUNC_VERIFY_SIGN)
	{
		ShowSign();
	}
	else if(nFlag == ID_MENU_FUNC_ADD_TRANS)
	{
		//OnAddTransInfo();
	}
}

void CRcpDlg::OnBnClickedRouteMenuBtn()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_FUNC_PASS_DATA, "정보넘기기");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_FUNC_USAGE_HISTORY, "이용내역");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_FUNC_VERIFY_SIGN, "서명확인");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_FUNC_ADD_TRANS, "탁송정보입력");
	pMenu->AppendMenu(MF_BYCOMMAND, ID_SHOW_DISTANCE, "경로지도보기");

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CRcpDlg::OnBnClickedRcpCopyBtn()
{
	CString strText; m_btnRcpCopy.GetWindowText(strText);

	if(strText == "기사위치")
	{
		if(IsEditMode())
			OnMenuContextRider(ID_MENU_RIDER_POS);

		// 수정시 버튼명 바뀜...
		return;
	}

	CRcpCopyData data;
	char *pszData = GetInsertData(data);

	CRcpCopyData *pRcpCopyData = new CRcpCopyData;
	pRcpCopyData->PacketToMap(pszData);
	if(pRcpCopyData)
		AfxGetMainWnd()->SendMessage(WM_USER+889, (WPARAM)pRcpCopyData, (LPARAM)0);
}

void CRcpDlg::OnEnChangeChargeTransEdit()
{
	CheckDrivingChargeChange();
	RefreshCharge(TRUE, FALSE);
}

void CRcpDlg::CheckDrivingChargeChange()
{
	CString strChargeSum, strChargeDriving;
	m_EDT_CHARGE_SUM.pEdit->GetWindowText(strChargeSum); strChargeSum.Replace(",", "");
	m_EDT_CHARGE_DRIVING.pEdit->GetWindowText(strChargeDriving); strChargeDriving.Replace(",", "");

	if(strChargeSum == strChargeDriving || strChargeDriving == "")
		m_bChangeDrivingCharge = TRUE;
	else
		m_bChangeDrivingCharge = FALSE;
}

void CRcpDlg::ShowNameSearch(CEdit *edtName, CEdit *edt)
{
	CString strStartName;
	edtName->GetWindowText(strStartName); 
	edt->SetWindowText(strStartName);
	edt->SetFocus();
}

void CRcpDlg::OnBnClickedHistoryBtn()
{
	ShowUsageHistory();
}

void CRcpDlg::CheckCardTax()
{
	if(m_pBi->bUseCardTax == TRUE)
	{
		if(GetPayTypeNew() == PAY_CARD)
		{
			CString strChargeSum; m_EDT_CHARGE_SUM.pEdit->GetWindowText(strChargeSum);
			long nTax = atoi(m_strChargeSum) * 0.1;

			m_edtValueAdd.SetWindowText(LF->GetMyNumberFormat(nTax));
		}
		else
			m_edtValueAdd.SetWindowText("");
	}
}

long CRcpDlg::GetDeposit(long nTotal)
{	
	long nDeposit = 0, nDepositRate = 0;

	MAP_CUSTOMER_GROUP::iterator it;
	it = m_cg.GetGroup()->find(m_pOrder->GetGNo());

	/*
	if(it != m_cg.GetGroup()->end())
	{ 
	nDepositRate = m_cg.GetGroupData(m_pOrder->GetGNo())->nDepositRate;
	if(m_pOrder->GetGNo() > 0 && nDepositRate > 0)
	{
	if(nDepositRate > 30)
	nDepositRate = 0;

	if(nDepositRate < 100)
	{
	nDeposit = nTotal * (100 - nDepositRate) / 10000;
	nDeposit = (int)nDeposit * 100;

	}
	else
	{
	nDeposit = nTotal - nDepositRate;
	}
	}
	}
	*/

	if(nDeposit == 0)
	{
		if((GetCarTypeNew() == CAR_TRUCK || GetCarTypeNew() == CAR_1_4_TON || GetCarTypeNew() == CAR_2_5_TON || GetCarTypeNew() == CAR_3_5_TON || 
			GetCarTypeNew() == CAR_5_TON || GetCarTypeNew() == CAR_11_TON || GetCarTypeNew() == CAR_18_TON || GetCarTypeNew() == CAR_25_TON ||
			GetCarTypeNew() == CAR_5_TON_PLUS || GetCarTypeNew() == CAR_8_TON || GetCarTypeNew() == CAR_14_TON || GetCarTypeNew() == CAR_15_TON) && 
			!LF->IsThisCompany("퀵콜"))
			nDeposit = nTotal * 0.15;
		else
			nDeposit = LU->GetDepositRate(m_pBi->nDOrderTable, nTotal);
	}

	return nDeposit;
}

BOOL CRcpDlg::CheckAutoSave()
{
	if(LF->IsThisCompany("월드코리아퀵"))
		return FALSE;

	if(m_nInitItem > ZERO)
		return FALSE;

	if(m_bInsertCidPhone == TRUE)
		return FALSE;

	if(m_pOrder->GetCNo() <= ZERO)
		return FALSE;

	CString strCID = m_strCID;
	strCID.Replace("-", "");

	if(LF->IsNumeric(strCID) && strCID.GetLength() > FIVE)
	{ 		
		if(CheckAutoSaveServer(strCID) == TRUE)
		{
			if(MessageBox("[" + m_strCID + "]를 의뢰지 번호에 추가 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
			{
				OnMenuContextCID(ID_MENU_ADD_CID);
				m_bInsertCidPhone = TRUE;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CRcpDlg::CheckAutoSaveServer(CString strCID)
{
	CMkCommand pCmd(m_pMkDb, "select_customer_tel_dup");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_pOrder->GetCNo());
	pCmd.AddParameter(strCID);

	if(!pCmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	return nRet;
}


BOOL CRcpDlg::OnPretransMessageWM_KEYUP(MSG *pMsg)
{
	CString strText;
	UINT nID = ::GetDlgCtrlID(pMsg->hwnd);

	switch(nID)
	{
	case IDC_CID_EDIT:
		m_EDT_CID.pEdit->GetWindowText(strText);
		if(LF->IsPhoneNumber(strText))
			m_strCID = strText;

		if(!m_ci.m_bUseSearchPopup)
			ShowSearchPOIDlg(strText, m_pOrder, FALSE, m_EDT_START.pEdit, TRUE, 1, TYPE_PHONE);

		return FALSE;

	case IDC_ORDER_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			m_edtOrder.GetWindowText(strText);
			ShowSearchPOIDlg(strText, m_pOrder, FALSE, m_EDT_START.pEdit);
		}
		
		return FALSE;

	case IDC_ORDER_ADDRESS_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			ShowSearchPOIDlgForAddressEdit(&m_edtOrderAddress, m_pOrder, &m_edtOrderDetail);
		}
		return FALSE;

	case IDC_START_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			m_EDT_START.pEdit->GetWindowText(strText);
			ShowSearchPOIDlg(strText, m_pStart, FALSE, m_pBi->bNoDestPoi ? m_EDT_DEST_DONG.pEdit : m_EDT_DEST.pEdit);
		}
		return FALSE; 

	case IDC_START_ADDRESS_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			ShowSearchPOIDlgForAddressEdit(&m_edtStartAddress, m_pStart, m_EDT_START_DETAIL.pEdit);
		}
		return FALSE;

	case IDC_DEST_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			m_EDT_DEST.pEdit->GetWindowText(strText);
			ShowSearchPOIDlg(strText, m_pDest, FALSE, m_EDT_CHARGE_BASIC.pEdit);
		}
		return FALSE;

	case IDC_DEST_ADDRESS_EDIT:
		if(!m_ci.m_bUseSearchPopup)
		{
			ShowSearchPOIDlgForAddressEdit(&m_edtDestAddress, m_pDest, m_EDT_DEST_DETAIL.pEdit);
		}
		return FALSE;

	case IDC_ORDER_CNO_EDIT:
	case IDC_ORDER_NAME_EDIT:
	case IDC_ORDER_DONG_EDIT:
	case IDC_ORDER_DEPART_EDIT:
	case IDC_ORDER_MANAGER_EDIT:
	case IDC_ORDER_PHONE_EDIT:
	case IDC_ORDER_MP_EDIT:
	case IDC_ORDER_DETAIL_EDIT:
		m_pOrder->UpdateJoinedControl(nID);
		return FALSE;

	case IDC_START_CNO_EDIT:
	case IDC_START_NAME_EDIT:
	case IDC_START_DONG_EDIT:
	case IDC_START_DEPART_EDIT:
	case IDC_START_MANAGER_EDIT:
	case IDC_START_PHONE_EDIT:
	case IDC_START_MP_EDIT:
	case IDC_START_DETAIL_EDIT:
		m_pStart->UpdateJoinedControl(nID);
		return FALSE;

	case IDC_DEST_CNO_EDIT:
	case IDC_DEST_NAME_EDIT:
	case IDC_DEST_DONG_EDIT:
	case IDC_DEST_DEPART_EDIT:
	case IDC_DEST_MANAGER_EDIT:
	case IDC_DEST_PHONE_EDIT:
	case IDC_DEST_MP_EDIT:
	case IDC_DEST_DETAIL_EDIT:
		m_pDest->UpdateJoinedControl(nID);
		return FALSE;
	}


	return CRcpDlgBase::PreTranslateMessage(pMsg);
}

void CRcpDlg::ShowSearchPOIDlgForAddressEdit(CFlatEdit2 *pEdit, CRcpPlaceInfo *pPlace, CWnd *pNextFocus)
{
	//지번만 입력하면, 이미 입력된 동정보를 보태기 하여 검색한다.
	CString strText, strCompare;
	pEdit->GetWindowText(strText);
	strCompare = strText;
	strCompare.Replace("산", "");

	//지번의 구조가 전화번호와 비슷한 DASH구조라 IsPhoneNumber로 체크함
	if(LF->IsPhoneNumber(strCompare) && pPlace->GetPOI())
	{
		CPOIUnit *pPOI = pPlace->GetPOI()->GetDongPOI();
		if(pPOI)
		{
			if(pPOI->IsLiPOI())
				strText = pPOI->GetDongLi() + strText;
			else 
				strText = pPOI->GetGugun1Only() + pPOI->GetDong() + strText;
		}
	}

	ShowSearchPOIDlg(strText, pPlace, FALSE, pNextFocus, 0, 0, TYPE_DONG);
}


void CRcpDlg::SetPayTypeNew(long nPayType)
{
	m_nPayType = nPayType;

	if(m_nPayType == PAY_CARD)
		m_cmbPayType.SetCurSel(5);
	else
		m_cmbPayType.SetCurSel(m_nPayType);	
}

void CRcpDlg::SetRunTypeNew(long nRunType)
{
	m_nRunType = nRunType;

	if(m_nRunType == RUN_FAST)
		m_cmbRunType.SetCurSel(TWO);
	else if(m_nRunType == RUN_VERY_FAST)
		m_cmbRunType.SetCurSel(THREE);
	else if (m_nRunType == RUN_TOGETHER)
		m_cmbRunType.SetCurSel(FOUR);
	else
		m_cmbRunType.SetCurSel(m_nRunType);	
}

void CRcpDlg::SetWayTypeNew(long nWayType)
{
	m_nWayType = nWayType;
	m_cmbWayType.SetCurSel(m_nWayType);	
}

void CRcpDlg::OnBnClickedItemMenuBtn()
{
	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	CString strItem = AfxGetApp()->GetProfileString("CEditItemDlg", "Item", "서류봉투;소박스;중박스;대박스;컴퓨터;");

	CStringArray strArry;
	LF->GetItemCommaToArray(strItem, strArry);

	for(int i=0; i<strArry.GetCount(); i++)
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ITEM_SELECT + i, strArry.GetAt(i));

	if(strArry.GetCount() > 0)
		pMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

	pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ITEM_EDIT, "항목수정");

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CRcpDlg::OnMenuContextItem(UINT nFlag)
{
	if(nFlag == ID_MENU_ITEM_EDIT)
	{
		CEditItemDlg dlg;
		dlg.m_nCompany = m_pBi->nCompanyCode;
		if(dlg.DoModal() == IDOK)
		{
			ReSetItemCombo();
		}

		return;
	}

	long nIndex = nFlag - ID_MENU_ITEM_SELECT;

	CString strItem = AfxGetApp()->GetProfileString("CEditItemDlg", "Item", "서류봉투;소박스;중박스;대박스;컴퓨터;");

	CStringArray strArry;
	LF->GetItemCommaToArray(strItem, strArry);

	m_cmbItemType.SetWindowText(strArry.GetAt(nIndex));
}

void CRcpDlg::OnBnClickedStateMenuBtn()
{
	if(!IsEditMode())
		return;

	m_pRcpView->SelectRowFromTNo(m_nInitItem);
	m_pRcpView->MakeContextMenu(TRUE, m_nInitItem);
}

void CRcpDlg::OnBnClickedOrderPhoneBtn()
{
	m_pOrder->OnContextMenuCall();
	m_pMenuSelPlace = m_pOrder;
}

void CRcpDlg::OnBnClickedOrderPhoneBtn2()
{
	m_pOrder->OnContextMenuCall(TRUE);
	m_pMenuSelPlace = m_pOrder;
}

void CRcpDlg::OnBnClickedStartPhoneBtn()
{
	m_pStart->OnContextMenuCall();
	m_pMenuSelPlace = m_pStart;
}

void CRcpDlg::OnBnClickedStartPhoneBtn2()
{
	m_pStart->OnContextMenuCall(TRUE);
	m_pMenuSelPlace = m_pStart;
}

void CRcpDlg::OnBnClickedDestPhoneBtn()
{
	m_pDest->OnContextMenuCall();
	m_pMenuSelPlace = m_pDest;
}

void CRcpDlg::OnBnClickedDestPhoneBtn2()
{
	m_pDest->OnContextMenuCall(TRUE);
	m_pMenuSelPlace = m_pDest;
}

void CRcpDlg::OnMenuCall(UINT nID)
{
	m_pMenuSelPlace->OnSelectMenuCall(nID);
}

void CRcpDlg::OnMenuSetSms(UINT nID)
{
	CString strPhone = m_arryPhone.GetAt(nID - ID_MENU_PHONE_SET_SMS);
	m_edtSmsPhone.SetWindowText(LF->GetDashPhoneNumber(strPhone));
}

void CRcpDlg::OnBnClickedEditOrderCheck()
{
	ShowAutoEditMsg((CButton*)GetDlgItem(IDC_EDIT_ORDER_CHECK), "의뢰지");
}

void CRcpDlg::OnBnClickedEditStartCheck()
{
	ShowAutoEditMsg((CButton*)GetDlgItem(IDC_EDIT_START_CHECK), "출발지");
}

void CRcpDlg::OnBnClickedEditDestCheck()
{
	ShowAutoEditMsg((CButton*)GetDlgItem(IDC_EDIT_DEST_CHECK), "도착지");
}

void CRcpDlg::ShowAutoEditMsg(CButton *pBtn, CString strPlace)
{
	CString strMsg;

	if(pBtn->GetCheck())
	{
		strMsg.Format("%s 수정시 기존 고객데이터에 자동 반영됩니다.\n** 고객전화번호 변경시 종속으로 추가됩니다.\n(신규고객은 무조건 반영됨)", strPlace);
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
	}
}

void CRcpDlg::ShowSetupDlg()
{
	CRcpDlgSetupDlg dlg;
	if(IDOK == dlg.DoModal())
	{
		m_pOrder->SetStartDontAutoCopy(CRcpDlgSetupDlg::m_info.nStartDontAutoCopy);

		m_pOrder->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
		m_pStart->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
		m_pDest->SetMenualAddCustomer(CRcpDlgSetupDlg::m_info.nManualAddCustomer);
	}
}

void CRcpDlg::OnEnSetfocusChargeBasicEdit()
{
	//	GetSectionCharge(FALSE, FALSE, TRUE);
}

void CRcpDlg::OnBnClickedFoodOrderCheck()
{
	BOOL bCheck = m_chkFoodOrder.GetCheck();

	CFoodCompleteDlg dlg;
	dlg.m_bFoodOrder = m_bPreFoodOrder;
	dlg.m_dtFoodComplete = m_dtPreFoodComplete;
	
	if(dlg.DoModal() == IDOK)
	{
		m_chkFoodOrder.SetCheck(dlg.m_bFoodOrder);
		m_dtPreFoodComplete = dlg.m_dtFoodComplete;
	}
	else
	{
		m_chkFoodOrder.SetCheck(m_bPreFoodOrder);		
	}
}

void CRcpDlg::OnBnClickedSaveChargeCheck()
{

}

void CRcpDlg::OnKillFocus(CWnd* pNewWnd)
{
	CRcpDlgBase::OnKillFocus(pNewWnd);
}

LONG CRcpDlg::OnChangePoi(WPARAM wParam, LPARAM lParam)
{

	if(m_ui.bDeveloper)
	{
		if( IsConsignApply() )
			return ZERO;
	}

	GetSectionCharge();
	return ZERO;
}

void CRcpDlg::ShowSearchManagerDlg(BOOL bMoveOnly)
{
	if(m_pSearchManagerDlg == NULL)
		MakeSearchManagerDlg();

	if(!bMoveOnly || m_pSearchManagerDlg->IsWindowVisible())
	{
#define MAX_DEPART_COUNT 10
#define	TOP_TO_LIST_SIZE 25
#define ONE_ROW_HEIGHT 20

		CRect rcManagerDlg, rcList, rcEdt;
		m_pSearchManagerDlg->GetWindowRect(rcManagerDlg); 
		m_pSearchManagerDlg->m_List.GetWindowRect(rcList); 

		CEdit *pManagerEdit = NULL;

		if(m_nLastDepartFocus == IDC_ORDER_DEPART_EDIT)
			pManagerEdit = m_EDT_ORDER_MANAGER.pEdit;
		else if(m_nLastDepartFocus == IDC_START_DEPART_EDIT)
			pManagerEdit = m_EDT_START_MANAGER.pEdit;
		else if(m_nLastDepartFocus == IDC_DEST_DEPART_EDIT)
			pManagerEdit = m_EDT_DEST_MANAGER.pEdit;

		if(pManagerEdit == NULL)
			return;

		pManagerEdit->GetWindowRect(rcEdt);

		long nListWidth = rcList.Width();
		long nWidth = rcManagerDlg.Width();
		long nCount = m_pSearchManagerDlg->m_List.GetItemCount();
		long nDlgHeight = rcManagerDlg.Height();
		long nListHeight = min(nCount, MAX_DEPART_COUNT) * ONE_ROW_HEIGHT;

		rcManagerDlg.top = rcEdt.top; 
		rcManagerDlg.bottom = rcManagerDlg.top + TOP_TO_LIST_SIZE + nListHeight;
		rcManagerDlg.left = rcEdt.right + 5;
		rcManagerDlg.right = rcManagerDlg.left + nWidth;

		m_pSearchManagerDlg->MoveWindow(rcManagerDlg);
		rcManagerDlg.DeflateRect(1, 1);
		m_pSearchManagerDlg->ScreenToClient(rcManagerDlg);
		rcManagerDlg.top += TOP_TO_LIST_SIZE;
		m_pSearchManagerDlg->m_List.MoveWindow(rcManagerDlg);
		/* 
		rcList.top = rcManagerDlg.top + TOP_TO_LIST_SIZE;
		rcList.bottom = rcList.top + nListHeight;
		rcList.left = rcManagerDlg.left + 2;
		rcList.right = rcList.left + nListWidth; 

		m_pSearchManagerDlg->MoveWindow(rcManagerDlg);
		m_pSearchManagerDlg->ScreenToClient(rcList);
		m_pSearchManagerDlg->m_List.MoveWindow(rcList);
		*/

		if(!bMoveOnly)
		{
			m_pSearchManagerDlg->ShowWindow(SW_SHOWNA);
			m_pSearchManagerDlg->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}
}

void CRcpDlg::OpenManagerSearchDlg()
{
	CRcpPlaceInfo *pPlace = NULL;

	if(m_nLastDepartFocus == IDC_ORDER_DEPART_EDIT)
		pPlace = m_pOrder;
	else if(m_nLastDepartFocus == IDC_START_DEPART_EDIT)
		pPlace = m_pStart;
	else if(m_nLastDepartFocus == IDC_DEST_DEPART_EDIT)
		pPlace = m_pDest;

	if(pPlace == NULL)
		return;


	if(m_pSearchPOIDlg && pPlace->GetCNo())
	{		
		if(m_pSearchManagerDlg == NULL)
			MakeSearchManagerDlg();

		CXTPListCtrl2 *pControl = &m_pSearchManagerDlg->m_List;
		pControl->DeleteAllItems();

		long nCount = ZERO;

		m_pSearchManagerDlg->m_nCompany = m_pBi->nCompanyCode;
		m_pSearchManagerDlg->m_nCNo = pPlace->GetCNo();

		SEARCH_CUS_VEC vecCus;
		if(m_pSearchPOIDlg->m_pCus->SearchCustomer(m_pBi->nCompanyCode, "", vecCus, pPlace->GetCNo()))
		{
			SEARCH_CUS_VEC::iterator it;
			for(it = vecCus.begin(); it != vecCus.end(); it++)
			{ 
				pControl->InsertItem(nCount, LF->GetDashPhoneNumber(it->strPhone));
				pControl->SetItemText(nCount, 1, it->strDepart);
				pControl->SetItemText(nCount++, 2, it->strName);
			}
		}

		if(nCount > ONE) 
		{
			pControl->Populate();
			ShowSearchManagerDlg();
		}
		else
			pControl->ShowWindow(FALSE);
	}
}

void CRcpDlg::OnEnSetfocusStartDepartEdit()
{
}

void CRcpDlg::OnEnSetfocusOrderDepartEdit()
{
}

void CRcpDlg::OnEnSetfocusDestDepartEdit()
{
}

void CRcpDlg::OnEnKillfocusOrderDepartEdit()
{	
}

void CRcpDlg::OnEnKillfocusStartDepartEdit()
{	
}

void CRcpDlg::OnEnKillfocusDestDepartEdit()
{	
}

void CRcpDlg::OnStnClickedReserveDisplayStatic()
{
	ShowReserveDlg();
}

void CRcpDlg::OnBnClickedShowRouteBtn()
{
	OnMenuContextPlace(ID_SHOW_DISTANCE);
}

void CRcpDlg::OnBnClickedEtcMenuBtn1()
{
	OnMenuContextEtc(ID_MENU_ETC_USER1);
}

void CRcpDlg::OnBnClickedEtcMenuBtn2()
{
	OnMenuContextEtc(ID_MENU_ETC_USER2);
}

void CRcpDlg::OnStnClickedOrderAddressStatic()
{
	RepositionAddressControl(m_edtOrderAddress, m_stcOrderAddress, m_pOrder, TRUE);	
}

void CRcpDlg::OnStnClickedStartAddressStatic()
{
	RepositionAddressControl(m_edtStartAddress, *m_STC_START_ADDERSS.pStatic, m_pStart, TRUE);	
}

void CRcpDlg::OnStnClickedDestAddressStatic()
{
	RepositionAddressControl(m_edtDestAddress, *m_STC_DEST_ADDERSS.pStatic, m_pDest, TRUE);	
}

void CRcpDlg::RepositionAddressControl(CFlatEdit2 &edt, CStatic &stc, CRcpPlaceInfo *pPlace, BOOL bShowEdit)
{
	CRect rcEdit, rcStatic;
	edt.GetWindowRect(rcEdit);
	stc.GetWindowRect(rcStatic);
	ScreenToClient(rcEdit);
	ScreenToClient(rcStatic);

	if(bShowEdit)
	{
		if(edt.IsWindowVisible()) {
			if(::OpenClipboard(m_hWnd))
			{
				CString strAddress = pPlace->GetAddress();			

				if(!strAddress.IsEmpty()) {
					::EmptyClipboard();
					HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, strAddress.GetLength() + 1);
					LPSTR pData = (LPSTR)::GlobalLock(hData);
					::strcpy(pData, strAddress);
					::GlobalUnlock(hData);

					::SetClipboardData(CF_TEXT, hData);
					::CloseClipboard();
					MessageBox("클립보드로 복사되었습니다", "확인", MB_ICONINFORMATION);
				}				
			}
		}

		rcStatic.left = rcEdit.right + 1;
		stc.MoveWindow(rcStatic);
		edt.ShowWindow(SW_SHOW);
		edt.SetWindowText("");
		edt.SetFocus();
	}
	else
	{
		rcStatic.left = rcEdit.left;
		stc.MoveWindow(rcStatic);
		edt.ShowWindow(SW_HIDE);
	}
}

void CRcpDlg::OnEnKillfocusOrderAddressEdit()
{
	RepositionAddressControl(m_edtOrderAddress, m_stcOrderAddress);	
}

void CRcpDlg::OnEnKillfocusStartAddressEdit()
{
	RepositionAddressControl(m_edtStartAddress, *m_STC_START_ADDERSS.pStatic);	
}

void CRcpDlg::OnEnKillfocusDestAddressEdit()
{
	RepositionAddressControl(m_edtDestAddress, *m_STC_DEST_ADDERSS.pStatic);	
}

void CRcpDlg::AddStringToEtc(CString strAdd, BOOL bFront)
{
	CString strEtc;
	m_EDT_ETC.pEdit->GetWindowText(strEtc);
	if(bFront)
		m_EDT_ETC.pEdit->SetWindowText(strAdd + strEtc);
	else
		m_EDT_ETC.pEdit->SetWindowText(strEtc + strAdd);
}

void CRcpDlg::OnEnKillfocusChargeDrivingEdit()
{
	long nCharge = LF->GetControlDigit(m_EDT_CHARGE_DRIVING.pEdit);

	if(nCharge < 500 && nCharge > 0)
		m_EDT_CHARGE_DRIVING.pEdit->SetWindowText(LF->GetMyNumberFormat(nCharge * 1000));
}

void CRcpDlg::OnBnClickedPayTypeOnlineBtn()
{
	SetPayTypeNew(m_pBi->nPayType4);
}

void CRcpDlg::OnEnChangeChargeDrivingEdit()
{ 
	CString strChargeDriving; m_EDT_CHARGE_DRIVING.pEdit->GetWindowText(strChargeDriving);
	strChargeDriving.Replace(",", "");

	m_edtDeposit.SetWindowText(LF->GetMyNumberFormat(GetDeposit(_ttoi(strChargeDriving))));
}

void CRcpDlg::OnBnClickedNotSendCompleteSmsCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRcpDlg::OnBnClickedShowOrderLogBtn()
{
	OnShowOrderLog();
}

void CRcpDlg::OnBnClickedSmsBtn()
{
	if(m_pOrder->GetCNo() <= ZERO)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_mobile_phone_list");

	pCmd.AddParameter(m_pBi->nCompanyCode);
	pCmd.AddParameter(m_pOrder->GetCNo());

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	m_arryPhone.RemoveAll();

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		CString strPhone;
		pRs.GetFieldValue("sTel", strPhone);
		m_arryPhone.Add(strPhone);

		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_SET_SMS + i, LF->GetDashPhoneNumber(strPhone));

		pRs.MoveNext();
	} 

	if(pRs.GetRecordCount() > ZERO)
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CRcpDlg::OnBnClickedAutoShareOrderCheck()
{
	if(m_pBi->bAutoShareOrder == FALSE)
	{
		MessageBox("자동오더해제 기능을 사용하지 않는 지사입니다\r\n\\r\n \
				   [옵션] - [일반] 공유 항목에서설정 후 체크하세요", "확인", MB_ICONINFORMATION);

		m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(FALSE);
	}
}

void CRcpDlg::OnBnClickedUpdateAndNewBtn()
{
	EditOrder(FALSE, FALSE, TRUE);
	//if(EditOrder(FALSE))
	//	LU->GetRcpView()->CopyOrder(LU->GetRcpView()->SelectRowFromTNo(m_nInitItem), STATE_OK);
}

void CRcpDlg::OnBnClickedOrderDestSameBtn()
{
	if(m_pOrder->GetCNo()> ZERO)
	{
		m_pStart->Clear();
		m_pDest->Copy(m_pOrder);
		m_EDT_START.pEdit->SetFocus();
	}
}

void CRcpDlg::OnBnClickedOrderStartSameBtn()
{
	if(m_pOrder->GetCNo()> ZERO)
	{
		m_pDest->Clear();
		m_pStart->Copy(m_pOrder);
		m_EDT_DEST.pEdit->SetFocus();
	}
}

void CRcpDlg::OnBnClickedOrderDifferentBtn()
{
	if(m_pOrder->GetCNo()> ZERO)
	{
		m_pStart->Clear();
		m_pDest->Clear();
		m_EDT_START.pEdit->SetFocus();
	}
}

void CRcpDlg::OnEnChangeCommissionEdit()
{
	RefreshConsignCharge();
}

void CRcpDlg::RefreshConsignCharge()
{

	//long nTempTotalCharge = 0, nConsignCharge = 0, nBackOrderCharge = 0, nCommissionCharge = 0,  nConsignTotalCharge = 0;
	long nConsignTotalCharge = 0,  nTempSumCharge = 0;
	if(LF->IsStringDigit(m_strChargeSum))
	{
		nTempSumCharge = atol(m_strChargeSum);
	}

	nConsignTotalCharge = LF->GetMyUnNumberFormatEdit(m_EDT_CHARGE_SUM.pEdit) + LF->GetMyUnNumberFormatEdit(m_EDT_CHARGE_TRANS.pEdit)+
		//nConsignTotalCharge =	nTempSumCharge + LF->GetMyUnNumberFormatEdit(&m_edtChargeTrans)+
		LF->GetMyUnNumberFormatEdit(&m_edtConBackOrderCharge) + LF->GetMyUnNumberFormatEdit(&m_edtConCommissionCharge);

	m_edtConTotalCharge.SetWindowText(LF->GetMyNumberFormat(nConsignTotalCharge));


}

void CRcpDlg::OnBnClickedZeroIncomeBtn()
{
	m_edtDeposit.SetWindowText("");
	m_bDepositMessage = FALSE;
}

void CRcpDlg::OnOpenRcpDlg()
{
	if(m_pHistoryDlg == NULL)
		return;

	CXTPGridRecord *pRecord = m_pHistoryDlg->m_wndReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_pHistoryDlg->m_wndReport.GetItemData(pRecord);

	if(pItem == NULL)
		return;

	CString strsOName = m_pOrder->GetCompany();

	if(m_pOrder->GetCNo() != pItem->nOCNo)
		strsOName = LU->GetCustomerName(pItem->nOCNo);

	LU->CreateRcpDlg(strsOName, pItem->nTNo, pItem->nState);
}

void CRcpDlg::OnBnClickedNiceCardBtn()
{
	if(m_pBi->bUseCardPay == FALSE)
	{
		MessageBox("해당 지사는 카드결제 옵션을 사용하지 않습니다.\r\n[옵션]-[카드가맹신청]에서 카드결제사용함에 체크하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!LF->POWER_CHECK(1890, "카드결제", FALSE) && !LF->POWER_CHECK(1891, "카드취소", FALSE))
	{
		MessageBox("카드결제/취소권한이 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nCardVendor = LF->GetCardVendor(m_pBi->nCompanyCode);

	if(nCardVendor != NICE_CARD_WAIT && nCardVendor != NICE_CARD_WAIT_QUICKCALL)
	{
		MessageBox("카드결제를 지원하지 않는 업체입니다\r\n로지소프트로 문의하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	long nCharge = GetCardPayVaild();
 
	if(nCharge <= 0)
		return;


	if(m_nInitItem < 0)
	{
		if(MessageBox("오더를 대기로 접수 후 카드결제가 가능합니다\r\n\r\n일반후불오더로 접수됩니다\r\n해당 오더를 접수 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
		{
			//if(m_cmbPayType.GetCurSel() != 2)
			//	m_cmbAfterPayType.SetCurSel(m_pBi->nAfterPayType);

			SetPayTypeNew(PAY_CARD);
			//m_cmbPayType.SetCurSel(2);

			//m_edtRiderAutoCharge.SetWindowText(LF->GetMyNumberFormat(nCharge));
			//m_chkCardPay.SetCheck(TRUE);			

			if(m_nInitItem = AddNewOrder(TRUE, FALSE, FALSE, ZERO, TRUE))
			{
				m_strCID = ""; 
				RefreshRcpDlg(STATE_WAIT);
				nCharge = GetCardPayVaild();
				//MessageBox("오더가 대기상태로 접수 되었습니다.\r\n카드결제 후 접수상태로 변경하세요", "확인", MB_ICONINFORMATION);
			}
		}
		else
			return;
	} 

	long nMileage = LF->GetLongFromEdit(&m_edtAutoCharge);

	if((m_nPreCharge - nMileage) != nCharge)
	{
		MessageBox("금액이 변경되었습니다.\r\n오더 수정 후 다시시도해주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CCardVerifyDlg dlg(this);
	dlg.m_pBi = m_pBi;
	dlg.m_nTNo = m_nInitItem;
	dlg.m_nCharge = nCharge;
	dlg.m_nCNo = m_pOrder->GetCNo();
	dlg.m_strEMail = LF->GetCustomerEMail(m_pOrder->GetCNo());

	if(dlg.DoModal() == IDOK)
	{
		if(!dlg.m_bAgreeCardSave)
			DeleteBillkey();

		LU->SendEMailCardResult(m_nInitItem, dlg.m_strEMail);

		RefreshRcpDlg();
		OnEnChangeRiderAutoChargeEdit();
	}
}


void CRcpDlg::DeleteBillkey()
{
	CMkCommand cmd(m_pMkDb, "delete_card_save_info_user");
	cmd.AddParameter(m_pOrder->GetCNo());
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	cmd.Execute();
}

void CRcpDlg::RefreshRcpDlg(long nState)
{
	long nTempTNo = m_nInitItem;
	long nTempState = nState > 0 ? nState : m_nPreState;
	Construct(FALSE); 
	m_nInitItem = nTempTNo; //위에서 초기화됨
	m_nPreState = nTempState;
	OnInitialUpdate();
}

long CRcpDlg::GetCardPayVaild()
{
	CString strCharge, strDeposit, strMileage; 
	m_EDT_CHARGE_SUM.pEdit->GetWindowText(strCharge); strCharge.Replace(",", "");
	m_edtDeposit.GetWindowText(strDeposit); strDeposit.Replace(",", "");
	m_edtAutoCharge.GetWindowText(strMileage); strMileage.Replace(",", "");

	long nCharge = atoi(strCharge);
	long nDeposit = atoi(strDeposit);
	long nMileage = atoi(strMileage);

	nCharge = nCharge - nMileage;

	if(m_pStart->GetPOI() == NULL ||
		m_pDest->GetPOI() == NULL)
	{
		MessageBox("출발지, 도착지 정보 입력 후 카드결제를 진행하세요", "확인", MB_ICONINFORMATION);
		return 0;
	}

	if(nCharge <= 0)
	{
		MessageBox("요금을 확인하세요", "확인", MB_ICONINFORMATION);
		return 0;
	}

	CString strError;

	if(!LF->CheckCardPayCondition(m_nInitItem, nCharge, nDeposit, strError))
	{
		MessageBox(strError, "확인", MB_ICONINFORMATION);
		return 0;
	}

	if(nCharge == m_pBi->nDefaultCharge && 
		m_nCardProcess != NICE_CARD_COMPLETE &&
		m_nCardProcess != NICE_CARD_COMPLETE_QUICKCALL)
	{
		if(MessageBox("요금이 기본요금입니다.\r\n요금이 정확합니까?", "확인", MB_ICONINFORMATION) == IDOK)
			return nCharge;
		else
			return 0;
	}

	return nCharge;
};

void CRcpDlg::ShowCardPayInfo()
{
	CString strTemp = ""; 
	CString strCharge = "";
	m_EDT_CHARGE_SUM.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");

	if(IsCardPayed())
	{ 
		strTemp += "<Run Foreground='Red' FontWeight='Bold'>카드결제</Run> ";
		strTemp += "<Run Foreground='Green' FontWeight='Bold'>[</Run>";
		strTemp += "<Run Foreground='Blue' FontWeight='Bold'>" + LF->GetMyNumberFormat(LF->GetCardRealPay(m_nInitItem)) + "</Run>";
		strTemp += "<Run Foreground='Green' FontWeight='Bold'>]</Run> ";
		strTemp += "<Run Foreground='Red' FontWeight='Bold'>원</Run> ";
		strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Left' VerticalAlignment='Center'>" + strTemp;
		strTemp += "</TextBlock>";

		m_stcCardState.ShowWindow(TRUE);
		m_btnPayType1.ShowWindow(FALSE);
		m_btnPayType2.ShowWindow(FALSE);
		m_btnPayType3.ShowWindow(FALSE);
		m_btnPayType4.ShowWindow(FALSE);
		m_btnPayType5.ShowWindow(FALSE);
	}
	else 
	{
		strTemp = "";
		m_stcCardState.ShowWindow(FALSE);
		m_btnPayType1.ShowWindow(TRUE);
		m_btnPayType2.ShowWindow(TRUE);
		m_btnPayType3.ShowWindow(TRUE);
		m_btnPayType4.ShowWindow(TRUE);
		m_btnPayType5.ShowWindow(TRUE);

		//m_btnPayType4.ShowWindow(TRUE);
	}
	

	m_stcCardState.SetMarkupText(strTemp);
}

BOOL CRcpDlg::IsDongSearch(CString strDong)
{
	POI_VEC *pVec = m_poiNew.GetDongVec();

	for(int i=0; i<pVec->size(); i++)
	{ 
		CPOIUnit *pUnit = &pVec->at(i); 

		CString strTemp = pUnit->GetDong();

		if(strTemp.Left(strDong.GetLength()) == strDong)
			return TRUE;
	}

	return FALSE;
}



//bMustCheckDongSearch: m_poi의 동데이터에서 해당명칭이 찾아지지 않으면 검색을 중단한다.
//bExpandLiData: 명칭에서 마지막글자에 '리'를 붙이지 않아도 리를 검색한다.
BOOL CRcpDlg::SearchRegion(UINT nCtrl, BOOL bMustCheckDongSearch, BOOL bExpandLiData)
{

	CString strDong;
	GetDlgItemText(nCtrl, strDong);
	if(strDong.GetLength() == 0)
	{
		if(bMustCheckDongSearch)
			return FALSE;

		MessageBox("지명을 입력하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CString strNewDong = strDong;
	if(strNewDong.GetLength() > 4)
	{
		if(strNewDong.Right(2) == "동" ||
			strNewDong.Right(2) == "면" ||
			strNewDong.Right(2) == "군" ||
			strNewDong.Right(2) == "가" ||
			strNewDong.Right(2) == "시" ||
			strNewDong.Right(2) == "읍")
			strNewDong = strDong.Left(strDong.GetLength() - 2);
	}


	if(bMustCheckDongSearch)
	{
		if(!IsDongSearch(strNewDong))
			return FALSE;
	}

	//m_poiNew.LoadDongPOI())->
/*
	if(bMustCheckDongSearch && m_poiNew.GetPoiDongMap()->end() == m_poiNew.GetPoiDongMap()->find(string(strNewDong)))
	{
		return FALSE;
	}
*/

	CSearchRegionDlg dlg;
	dlg.m_strSearch = strDong;
	dlg.m_bAloneItemAutoClosed = bMustCheckDongSearch;
	dlg.m_bExpandLiData = bExpandLiData;
	if(IDOK == dlg.DoModal() && dlg.m_nDongID > 0)
	{
		MakeSearchPOIDlgForSerchPopup();
		CPOIUnit *pDongPoi = m_poiNew.GetDongPOI(dlg.m_nDongID);

		if(nCtrl == IDC_START_EDIT || 
			nCtrl == IDC_START_DONG_EDIT)
		{
			m_pSearchPOIDlg->SetRcpPlace(m_pStart, m_EDT_DEST_NAME.pEdit);
			m_pSearchPOIDlg->SaveCurPOI(POI_COMPLETE_EVENT, pDongPoi, NULL);
			m_EDT_DEST.pEdit->SetFocus();
		}
		else if(nCtrl == IDC_DEST_EDIT ||
			nCtrl == IDC_DEST_DONG_EDIT)
		{
			m_pSearchPOIDlg->SetRcpPlace(m_pDest, m_EDT_CHARGE_BASIC.pEdit);
			m_pSearchPOIDlg->SaveCurPOI(POI_COMPLETE_EVENT, pDongPoi, NULL);
			m_EDT_CHARGE_BASIC.pEdit->SetFocus();
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void CRcpDlg::OnBnClickedUpdateCancelBtn()
{
	CString strCancel;
	long nCancelType = 11, nPenaltyMin = 0, nPenaltyCharge = 0;

	if(m_pBi->bCancelReason)
	{
		strCancel = "[취소:즉시취소]";
		nCancelType = 11;
		nPenaltyMin = ZERO;
		nPenaltyCharge = ZERO;
	}
	else
	{
		CCancelDlg dlg;
		CStringArray saCancel;
		saCancel.Add("[취소1:전화불통]");
		saCancel.Add("[취소2:시간지연]");
		saCancel.Add("[취소3:배달지이상]");
		saCancel.Add("[취소4:물건크기불량]");
		saCancel.Add("[취소5:취급불가불건]");
		saCancel.Add("[취소6:고객없음]");
		saCancel.Add("[취소7:일부취소]");
		saCancel.Add("[취소8:기사부족]");
		saCancel.Add("[취소9:연습오더]");
		saCancel.Add("[취소10:본인취소]");
		saCancel.Add("[취소:배차실수]");

		dlg.m_nTNo = m_nInitItem;
		dlg.m_nCompany = m_pBi->nCompanyCode;
		dlg.m_psaCancel = &saCancel;
		dlg.m_strCustomerPhone = "";
		dlg.m_nOrderCompany = m_pBi->nCompanyCode;

		if(dlg.DoModal() == IDOK)
		{
			if(dlg.m_nCancelType >= 11)
			{
				if(dlg.m_strEtc.GetLength() > 0)			
					strCancel = "[취소:" + dlg.m_strEtc + "]";
				else 
					strCancel = "[취소:기타]";

				dlg.m_nCancelType = 11;
			}
			else 
			{
				strCancel = saCancel.GetAt(dlg.m_nCancelType);
			}

			nCancelType = dlg.m_nCancelType;
			nPenaltyMin = dlg.m_bAllocateLimit ? atol(dlg.m_strPenaltyMin) : 0;
			nPenaltyCharge = dlg.m_bCancelPenaltyCharge ? atol(dlg.m_strPenaltyCharge) : 0;
		}
		else
			return;
	}

	int nRet = m_pRcpView->GetStateChange()->CancelOrder(m_pBi->nCompanyCode, m_nInitItem, m_nState, 
		strCancel, nCancelType, nPenaltyMin, nPenaltyCharge);
	if(nRet == STATE_CANCELED)
		OnCancel();
}
void CRcpDlg::OnBnClickedPayTypeOnlineBtn2()
{
	SetPayTypeNew(m_pBi->nPayType5);
}

void CRcpDlg::OnBnClickedCarTypeBtn4()
{
	SetCarTypeNew(m_pBi->nCarType4);
	OnCbnSelchangeCarTypeCombo();
}

void CRcpDlg::OnBnClickedCarTypeBtn5()
{
	SetCarTypeNew(m_pBi->nCarType5);
	OnCbnSelchangeCarTypeCombo();
}

void CRcpDlg::OnBnClickedWayTypeBtn()
{
	SetWayTypeNew(WAY_ONE);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedWayTypeBtn2()
{
	SetWayTypeNew(WAY_TWO);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedWayTypeBtn3()
{ 
	SetWayTypeNew(WAY_SEVERAL);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedRunTypeBtn()
{
	SetRunTypeNew(RUN_NORMAL);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedRunTypeBtn2()
{
	SetRunTypeNew(RUN_SLOW);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedRunTypeBtn3()
{
	SetRunTypeNew(RUN_FAST);
	/*if(LF->IsThisCompany("엔콜") || LF->IsThisCompany("로지") )
	{
		if(m_pCharge)
		{
			if(!IsPreChangePOI()  && m_pCharge->IsCashCharge())
				m_pCharge->SetCashCharge(FALSE);
		}
	}*/
	
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedRunTypeBtn4()
{
	SetRunTypeNew(RUN_VERY_FAST);
	GetSectionCharge();
}

void CRcpDlg::OnBnClickedStartClearBtn()
{
	m_pStart->Clear();
}

void CRcpDlg::OnBnClickedDestClearBtn()
{
	m_pDest->Clear();
}

void CRcpDlg::OnBnClickedOrderClearBtn()
{
	m_pOrder->Clear();
}

void CRcpDlg::OnBnClickedRiderSearchBtn()
{
	if(m_nRiderCompany > 0 && m_nRNo > 0)
		OnMenuContextRider(ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW);
	else 
		OnMenuContextRider(ID_MENU_RIDER_ALLOC);
}

void CRcpDlg::OnBnClickedRiderSMSBtn()
{
	MSG_RIDER_INFO *pInfo = new MSG_RIDER_INFO;

	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{
		CRiderMsgDlg dlg;
		dlg.SetIntegrated(m_ba.GetCount() > 2);
		dlg.SetCompanyCode(m_pBi->nCompanyCode);
		pInfo->nCompany = m_nRiderCompany;
		pInfo->nRNo = m_nRNo;
		dlg.m_paSelected.Add((MSG_RIDER_INFO*)pInfo);
		dlg.DoModal();
		delete pInfo;
	}
	else if(!m_bRiderSmsSend)
	{
		OnMenuContextRider(ID_MENU_RIDER_ALLOC_OTHER);
	}
	//--charko

}

void CRcpDlg::ShowCreditHistory(BOOL bRefresh)
{
	if(m_pOrder->GetCNo() < 1 || !m_pBi->bCreditListPopup)
		return;

	if(m_pCreditHistoryDlg == NULL)
	{
		m_pCreditHistoryDlg = new CCreditHistoryDlg(this);
		m_pCreditHistoryDlg->m_pRcpDlg = this;
		m_pCreditHistoryDlg->m_nOGNo = m_pOrder->GetGNo(); 
		m_pCreditHistoryDlg->m_nOCNo = m_pOrder->GetCNo(); 
		m_pCreditHistoryDlg->m_nCompany = m_pBi->nCustomerTable;
		m_pCreditHistoryDlg->Create(IDD_CREDIT_HISTORY_DLG, this);

		CRect rcDlg, rcHistory, rcNew, rcClose;
		GetWindowRect(rcDlg);
		m_pCreditHistoryDlg->GetWindowRect(rcHistory);

		long nHeight = rcHistory.Height();
		long nWeight = rcHistory.Width();

		rcHistory.top = rcDlg.top + 400;
		rcHistory.bottom = rcHistory.top + nHeight;
		rcHistory.right = rcDlg.left - 2;
		rcHistory.left = rcHistory.right - nWeight;
		m_pCreditHistoryDlg->MoveWindow(rcHistory);
	}
	else
	{
		m_pCreditHistoryDlg->m_nOGNo = m_pOrder->GetGNo(); //m_pOrder->GetGNo();
		m_pCreditHistoryDlg->m_nOCNo = m_pOrder->GetCNo(); //m_pOrder->GetCNo();
		m_pCreditHistoryDlg->m_nCompany = m_pBi->nCustomerTable;

		if(bRefresh)
		{
			m_pCreditHistoryDlg->DeleteAllItems();
			m_pCreditHistoryDlg->RefreshList();
		}
	}

	if(m_pCreditHistoryDlg->GetListRowCount() > 0)
		m_pCreditHistoryDlg->ShowWindow(SW_SHOW);
	else
		m_pCreditHistoryDlg->ShowWindow(SW_HIDE);
}

void CRcpDlg::HideSubHistoryDlgExeMe()
{
	if(LU->GetRcpView()->m_pLastSelRcpDlg != this)
	{
		RCP_DLG_MAP::iterator it;
		RCP_DLG_MAP *pMap = LU->GetRcpView()->GetRcpDlgMap();
		for(it = pMap->begin(); it != pMap->end(); it++)
		{
			CRcpDlg *pDlg = it->first;
			if(pDlg->GetSafeHwnd() != this->GetSafeHwnd())
			{
				HIDE_DLG(pDlg->m_pCreditHistoryDlg);
				if(!m_bHistoryMoveDown)
				{
					HIDE_DLG(pDlg->m_pHistoryDlg);
				}
			}
			else
			{
				if(LU->GetRcpView()->m_pLastSelRcpDlg != NULL)
				{
					if(LU->GetRcpView()->m_pLastSelRcpDlg->GetSafeHwnd() != this->GetSafeHwnd())
					{
						if(pDlg->m_pCreditHistoryDlg)
						{
							if(pDlg->m_pCreditHistoryDlg->GetListRowCount() > 0)
								pDlg->m_pCreditHistoryDlg->ShowWindow(SW_SHOW);
							else
								pDlg->m_pCreditHistoryDlg->ShowWindow(SW_HIDE);
						}
						
						if(!m_bHistoryMoveDown)
							SHOW_DLG(pDlg->m_pHistoryDlg);
					}
				}
			}
		}

		LU->GetRcpView()->m_pLastSelRcpDlg = this;
	}
}

void CRcpDlg::SetCarTypeNew(long nCarType)
{
	LF->SetCarType(&m_cmbCarType, nCarType);
}

long CRcpDlg::GetCarTypeNew()
{
	//choe
	return LF->GetCarType(&m_cmbCarType);
}

void CRcpDlg::InitEtcCombo()
{
}

void CRcpDlg::ShowCustomerInnerMemo(CString strMemo)
{

}

BOOL CRcpDlg::IsReserve()
{
	return m_pReserveOrderDlg->IsReserve();
}

BOOL CRcpDlg::ReserveCheck()
{
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	COleDateTimeSpan dtSpan(0, 0, m_pReserveOrderDlg->GetReleaseMin(), 0);

	if(dtCurrent > m_pReserveOrderDlg->GetReserveTime() - dtSpan)
	{
		if(!m_pReserveOrderDlg->IsReleaseAfterWait())
		{
			if(MessageBox("이전오더 접수시 예약후대기 버튼에 반드시 체크되어 있어야합니다\r\n체크 하지 않을시 기사님 단말기에 오더나타남!!", "확인", MB_OKCANCEL) == IDOK)
				return FALSE;
		}
	}

	return TRUE;
}

long CRcpDlg::GetReleaseStateDB()
{
	return m_pReserveOrderDlg->GetReleaseStateDB();	
}

void CRcpDlg::SetReserveState(COleDateTime dtReserve, long nReserveAfter, long nReserveReleaseMin)
{
	m_pReserveOrderDlg->SetReserve(TRUE);
	m_pReserveOrderDlg->SetReserveTime(dtReserve);
	m_pReserveOrderDlg->SetReleaseStateDB(nReserveAfter);
	m_pReserveOrderDlg->SetReleaseMin(nReserveReleaseMin);
}

COleDateTime CRcpDlg::GetReserveTime()
{
	if(m_pReserveOrderDlg != NULL)
		return m_pReserveOrderDlg->GetReserveTime();	

	return COleDateTime::GetCurrentTime();
}

long CRcpDlg::GetReleaseMin()
{
	return m_pReserveOrderDlg->GetReleaseMin();	
}

CString CRcpDlg::GetReserveTimeString()
{
	return m_pReserveOrderDlg->GetReserveTimeString();
}

BOOL CRcpDlg::IsReleaseAfterWait()
{
	return m_pReserveOrderDlg->IsReleaseAfterWait();
}

void CRcpDlg::OnBnClickedNewRcpDlgBtn()
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;
	//최상위가 카고이면, 퀵메인을 넣어준다. 항상 퀵메인 접수창이 떠야한다.
	LU->GetRcpView()->CreateRcpDlg(m_ci.IsCargoMain() ? m_ci.m_pQuickMainBranch : NULL, "신규", -1, 0, "", FALSE, -10, GetTickCount());
}

void CRcpDlg::OnBnClickedProPerBtn()
{
	if(m_pStart->GetPOI() == NULL ||
		m_pDest->GetPOI() == NULL)
		return;

	CProperChargeDlg dlg;
	dlg.m_nStartID = m_pStart->GetPOI()->GetDongID();
	dlg.m_nDestID = m_pDest->GetPOI()->GetDongID();
	dlg.m_nCarType = GetCarTypeNew();
	dlg.m_nCharge = LF->GetLongFromEdit(m_EDT_CHARGE_BASIC.pEdit);
	dlg.m_nProperCharge1 = LF->GetLongFromEdit(&m_edtProperCharge1);
	dlg.m_nProperCharge2 = LF->GetLongFromEdit(&m_edtProperCharge2);

	if(dlg.DoModal() == IDOK)
	{
		m_EDT_CHARGE_BASIC.pEdit->SetWindowText(LF->GetMyNumberFormat(dlg.m_nProperCharge1));
		RefreshCharge();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

char* CRcpDlg::GetInsertData(CRcpCopyData &data)
{
	UpdateData(TRUE);

	data.InsertData("nCompany", m_pBi->nCompanyCode);
	INSERT_RCP_DATA(m_strCID);
	//INSERT_RCP_DATA(m_pOrder->GetCNo());
	//INSERT_RCP_DATA(m_pOrder->GetGNo());
	//INSERT_RCP_DATA(m_pStart->GetCNo());
	//INSERT_RCP_DATA(m_pDest->GetCNo());
	data.InsertData("nOCNo", m_pOrder->GetCNo());
	data.InsertData("nOTelID", m_pOrder->GetTelID());	
	data.InsertData("nGNo", m_pOrder->GetGNo());
	data.InsertData("nSCNo", m_pStart->GetCNo());
	data.InsertData("nDCNo", m_pDest->GetCNo());
	//INSERT_RCP_DATA(m_pReserveOrderDlg->IsReserve());
	data.InsertData("strOCompany", m_pOrder->GetCompany());
	data.InsertData("strOPhone", m_pOrder->GetPhone());
	data.InsertData("strOMP", m_pOrder->GetMP());
	data.InsertData("strODepart", m_pOrder->GetDepart());
	data.InsertData("strOManager", m_pOrder->GetManager());
	data.InsertData("strOAddress", m_pOrder->GetAddress());
	data.InsertData("strODetail", m_pOrder->GetDetail());
	data.InsertData("strOMemo", m_pOrder->GetMemo());
	data.InsertData("strODisplayDong", m_pOrder->GetDisplayDong());

	data.InsertData("strSCompany", m_pStart->GetCompany());
	data.InsertData("strSPhone", m_pStart->GetPhone());
	data.InsertData("strSMP", m_pStart->GetMP());
	data.InsertData("strSDepart", m_pStart->GetDepart());
	data.InsertData("strSManager", m_pStart->GetManager());
	data.InsertData("strSAddress", m_pStart->GetAddress());
	data.InsertData("strSDetail", m_pStart->GetDetail());
	data.InsertData("strSDisplayDong", m_pStart->GetDisplayDong());

	/*
	INSERT_RCP_DATA(m_pOrder->GetCompany()); 
	INSERT_RCP_DATA(m_pOrder->GetPhone());
	INSERT_RCP_DATA(m_pOrder->GetMP());
	INSERT_RCP_DATA(m_pOrder->GetDepart());
	INSERT_RCP_DATA(m_pOrder->GetManager());
	INSERT_RCP_DATA(m_pOrder->GetAddress());
	INSERT_RCP_DATA(m_pOrder->GetDetail());
	INSERT_RCP_DATA(m_pOrder->GetMemo());
	INSERT_RCP_DATA(m_pOrder->GetDisplayDong());
	INSERT_RCP_DATA(m_pStart->GetCompany());
	INSERT_RCP_DATA(m_pStart->GetPhone());
	INSERT_RCP_DATA(m_pStart->GetMP());
	INSERT_RCP_DATA(m_pStart->GetDepart());
	INSERT_RCP_DATA(m_pStart->GetManager());
	INSERT_RCP_DATA(m_pStart->GetAddress());
	INSERT_RCP_DATA(m_pStart->GetDetail());
	INSERT_RCP_DATA(m_pStart->GetDisplayDong());
	*/

	if(m_pStart->GetPOI()) {
		data.InsertData("nSID", m_pStart->GetPOI()->GetID());		
		data.InsertData("nSDongID", m_pStart->GetPOI()->GetDongID());	
		data.InsertData("nSPosX", m_pStart->GetPOI()->GetPosX());
		data.InsertData("nSPosY", m_pStart->GetPOI()->GetPosY());
		//INSERT_RCP_DATA(m_pStart->GetPOI()->GetID());		
		//INSERT_RCP_DATA(m_pStart->GetPOI()->GetDongID());	
		//INSERT_RCP_DATA(m_pStart->GetPOI()->GetPosX());
		//INSERT_RCP_DATA(m_pStart->GetPOI()->GetPosY());

	}
	else {
		data.InsertData("nSID", 0);		
		data.InsertData("nSDongID", 0);	
		data.InsertData("nSPosX", 0);
		data.InsertData("nSPosY", 0);
		//INSERT_RCP_DATA(0);	//dongid
		//INSERT_RCP_DATA(0);	//real dongid
		//INSERT_RCP_DATA(0);	//posx
		//INSERT_RCP_DATA(0);	//posy
	}

	/*
	INSERT_RCP_DATA(m_pDest->GetCompany());
	INSERT_RCP_DATA(m_pDest->GetPhone());
	INSERT_RCP_DATA(m_pDest->GetMP());
	INSERT_RCP_DATA(m_pDest->GetDepart());
	INSERT_RCP_DATA(m_pDest->GetManager());
	INSERT_RCP_DATA(m_pDest->GetAddress());
	INSERT_RCP_DATA(m_pDest->GetDetail());
	INSERT_RCP_DATA(m_pDest->GetDisplayDong());
	*/
	data.InsertData("strDCompany", m_pDest->GetCompany());
	data.InsertData("strDPhone", m_pDest->GetPhone());
	data.InsertData("strDMP", m_pDest->GetMP());
	data.InsertData("strDDepart", m_pDest->GetDepart());
	data.InsertData("strDManager", m_pDest->GetManager());
	data.InsertData("strDAddress", m_pDest->GetAddress());
	data.InsertData("strDDetail", m_pDest->GetDetail());
	data.InsertData("strDDisplayDong", m_pDest->GetDisplayDong());

	if(m_pDest->GetPOI()) {
		data.InsertData("nDID", m_pDest->GetPOI()->GetID());		
		data.InsertData("nDDongID", m_pDest->GetPOI()->GetDongID());	
		data.InsertData("nDPosX", m_pDest->GetPOI()->GetPosX());
		data.InsertData("nDPosY", m_pDest->GetPOI()->GetPosY());
		//INSERT_RCP_DATA(m_pDest->GetPOI()->GetID());		
		//INSERT_RCP_DATA(m_pDest->GetPOI()->GetDongID());	
		//INSERT_RCP_DATA(m_pDest->GetPOI()->GetPosX());
		//INSERT_RCP_DATA(m_pDest->GetPOI()->GetPosY());
	}
	else {
		data.InsertData("nDID", 0);		
		data.InsertData("nDDongID", 0);	
		data.InsertData("nDPosX", 0);
		data.InsertData("nDPosY", 0);
		//INSERT_RCP_DATA(0);	//dongid
		//INSERT_RCP_DATA(0);	//real dongid
		//INSERT_RCP_DATA(0);	//posx
		//INSERT_RCP_DATA(0);	//posy
	}

	INSERT_RCP_DATA(m_strEtc);

	//by mksong (2011-01-10 오전 11:38) 작업필요함
	//INSERT_RCP_DATA(CReserveOrderDlg::m_dtReserveDate);
	//INSERT_RCP_DATA(CReserveOrderDlg::m_dtReserveTime);
	//INSERT_RCP_DATA(CReserveOrderDlg::m_nReleaseMin);
	//	INSERT_RCP_DATA(m_bFinalSendSMS);
	INSERT_RCP_DATA(m_strItemType);
	INSERT_RCP_DATA(m_nPayType);
	//INSERT_RCP_DATA(::GetCarTypeNew(&m_cmbCarType));
	data.InsertData("nCarType", GetCarTypeNew());
	INSERT_RCP_DATA(m_nWayType);
	INSERT_RCP_DATA(m_nRunType);
	INSERT_RCP_DATA(m_strCNS);

	INSERT_RCP_DATA(m_strChargeBasic);
	INSERT_RCP_DATA(m_strChargeAdd);
	INSERT_RCP_DATA(m_strChargeDis);
	INSERT_RCP_DATA(m_strChargeSum);
	INSERT_RCP_DATA(m_strChargeTrans);
	INSERT_RCP_DATA(m_strDeposit);

	INSERT_RCP_DATA(m_bCoupon);
	INSERT_RCP_DATA(m_strCouponCharge);
	INSERT_RCP_DATA(m_strAllocateGroup);
	//	INSERT_RCP_DATA(m_strChargeBet);

	INSERT_RCP_DATA(m_bScheduleOrder);
	INSERT_RCP_DATA(m_strIntercallEtc);


	//DDX_변수 로 연결되어있지 않는 경우에, 아래에 배치한다.
	BOOL bChkTransOrder = FALSE;//m_chkTransOrder.GetCheck();
	int nChargeType = m_CMB_CHARGE_TYPE.pCombo->GetCurSel();

	INSERT_RCP_DATA(bChkTransOrder);
	INSERT_RCP_DATA(nChargeType);

	INSERT_RCP_DATA(IsReserve());
	INSERT_RCP_DATA(IsReleaseAfterWait());


	BOOL bAutoCharge;
	CString strMileageBalance, strNotOrderMileage; 
	bAutoCharge = m_chkAutoCharge.GetCheck();

	INSERT_RCP_DATA(bAutoCharge);
	INSERT_RCP_DATA(strMileageBalance);
	INSERT_RCP_DATA(strNotOrderMileage);

	return data.MakePacket();
}

void CRcpDlg::OnBnClickedRunTypeBtn5()
{
	SetRunTypeNew(RUN_TOGETHER);
	GetSectionCharge();
}


void CRcpDlg::OnPayCash()
{
	if(m_nInitItem < 0)
	{
		MessageBox("오더가 접수되지 않았습니다.", "확인", MB_ICONINFORMATION);
		return;
	}  

	if(IsCardPayed())
	{
		MessageBox("카드결제 오더는 현금영수증을 발행할수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strCharge; m_EDT_CHARGE_SUM.pEdit->GetWindowText(strCharge);
	strCharge.Replace(",", "");
	CString strPhone; m_EDT_ORDER_PHONE.pEdit->GetWindowText(strPhone);
	strPhone.Replace("-", "");

	long nCharge = atoi(strCharge);

	CPayCashDlg dlg;
	dlg.m_strInfo = strPhone;
	dlg.m_strEMail = LF->GetCustomerEMail(m_pOrder->GetCNo());

	if(dlg.DoModal() != IDOK) 
		return;

	CString strTemp;
	strTemp.Format("<USAGE_ID=2><SEND_SMS=0><COMPANY=%d><WCOMPANY=%d><WNO=%d><TNO=%d><AMT=%d><ISSUE_TYPE=%d><ISSUE_KEY=%s><CALLER_TYPE=%s><BUYER_NAME=%s><BUYER_EMAIL=%s><BUYER_TEL=%s>",
		m_pBi->nCompanyCode, m_ui.nCompany, m_ui.nWNo, m_nInitItem, nCharge, dlg.m_nType, dlg.m_strInfo, "Q", "퀵서비스", dlg.m_strEMail, strPhone);

	char data[300];
	strcpy(data, strTemp);

	CString strAddr; long nPort;

	if(!LF->GetConnetcInfo(strAddr, nPort))
	{
		MessageBox("서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;	
	}

	if(!CCardVerifyDlg::GetCardSocket(strAddr, nPort))
	{
		MessageBox("서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;
	}

	if(!CCardVerifyDlg::m_pMkCard->GetSocket()->SendData(PT_REQUEST, PST_NICE_REQUSET_PROTOCOL, data)) 
	{
		MessageBox("카드결제정보 전송 실패\r\n다시 시도하세요", "확인", MB_ICONERROR);
		return;
	}

	CString strMsg;
	QPACKET *rcv = (QPACKET*)CCardVerifyDlg::m_pMkCard->GetSocket()->ReadStream();

	if(rcv == NULL)
	{
		MessageBox("현금영수증 요청 실패\r\n다시 시도하세요", "확인", MB_ICONERROR);
		return;
	}

	if(rcv != NULL) 
	{
		if(PT_OK == rcv->nType)
		{
			MessageBox("현금영수증 발급이 정상적으로 완료되었습니다", "확인", MB_ICONINFORMATION);
		}
		else
		{
			int nRet = rcv->nSubType;
			strMsg = rcv->data;			
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}

		free(rcv);
	}
}

void CRcpDlg::OnReSendEMail()
{
	if(!IsCardPayed())
	{ 
		MessageBox("카드결제가 이루어 지지 않은 오더입니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nTNo = m_nInitItem;

	if(nTNo < 0)
	{
		MessageBox("오더가 접수되지 않았습니다.", "확인", MB_ICONINFORMATION);
		return;
	}


	if(m_pOrder->GetCNo() <= 0)
	{
		MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CEMailDlg dlg;
	dlg.m_strEMail = LF->GetCustomerEMail(m_pOrder->GetCNo());

	if (dlg.DoModal() == IDOK) {
		if(!dlg.m_strEMail.IsEmpty()) {
			CString error = LU->SendEMailCardResult(nTNo, dlg.m_strEMail, true);

			if (!error.IsEmpty()) 
				MessageBox(error, "확인", MB_ICONINFORMATION);
			else
				MessageBox("이메일을 재발송 하였습니다", "확인", MB_ICONINFORMATION);
       }
        else
			MessageBox("이메일을 입력하세요", "확인", MB_ICONINFORMATION);
    }
}

void CRcpDlg::OnBnClickedDirectDistanceCheck()
{
	GetSectionCharge(TRUE);
}

void CRcpDlg::OnEnChangeChargeCompanyEdit()
{
	CString strEtc;
	m_EDT_ETC.pEdit->GetWindowText(strEtc);
	CString strTemp = "";
	CString strDelete = "";

	if(strEtc.Find("{업체부담금") >= 0)
	{
		int nStart = strEtc.Find("{업체부담금");

		if(nStart >= 0)
		{
			int nEnd = strEtc.Find("}", nStart);

			if(nEnd > nStart)
			{
				strDelete = strEtc.Mid(nStart, nEnd - nStart + 1);
				strEtc.Replace(strDelete, "");
			}
		}
	}

	long nChargeCompany = LF->GetLongFromEdit(&m_edtChargeCompany);
	strTemp = "{업체부담금(신용):" + LF->GetMyNumberFormat(nChargeCompany)  + "}";

	m_EDT_ETC.pEdit->SetWindowText(strTemp + strEtc);

}

void CRcpDlg::OnEnChangeTnoEdit()
{
	if(m_nInitItem > 0 || m_bLoadInit == FALSE)
		return;

	CString strSearch;
	m_EDT_TNO.pEdit->GetWindowText(strSearch);
	m_CMB_BRANCH.pCombo->ShowDropDown(TRUE);

	COMBOBOXINFO itemInfo = { sizeof(COMBOBOXINFO)};
	m_CMB_BRANCH.pCombo->GetComboBoxInfo(&itemInfo);

	CListBox *pListBox = (CListBox*)CWnd::FromHandle(itemInfo.hwndList);

	for(int i=0; i<pListBox->GetCount(); i++)
	{
		CString strBranch = "";
		pListBox->GetText(i, strBranch);

		if(strBranch.Find(strSearch) >= 0)
		{
			pListBox->SetCurSel(i);
			break;
		}
	}
}

void CRcpDlg::SelectBranchCombo()
{
	if(m_nInitItem > 0 || m_bLoadInit == FALSE)
		return;

	COMBOBOXINFO itemInfo = { sizeof(COMBOBOXINFO)};
	m_CMB_BRANCH.pCombo->GetComboBoxInfo(&itemInfo);

	CListBox *pListBox = (CListBox*)CWnd::FromHandle(itemInfo.hwndList);

	if(!pListBox->IsWindowVisible())
		return;

	long nSel = pListBox->GetCurSel();

	if(nSel >= 0)
	{
		m_CMB_BRANCH.pCombo->SetCurSel(nSel);
		m_CMB_BRANCH.pCombo->ShowDropDown(FALSE);	
		OnCbnSelchangeBranchCombo();
	}
}
void CRcpDlg::OnBnClickedCallPassBtn()
{
	CIPass c(this);

	if(c.ClickRcpDlg())
		c.PassData();
}

BOOL CRcpDlg::CheckCompanyEmp() 
{
	CMkCommand cmd(m_pMkDb, "select_company_emp_biz_no_check");
	cmd.AddParameter(m_pBi->nCompanyCode);
	CMkParameter *pParMent = cmd.AddParameter(typeString, typeOutput, 1000, "");
	CMkParameter *parAction = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(cmd.Execute()){
		CString strMent; pParMent->GetValue(strMent);
		int nAction = 0; parAction->GetValue(nAction);

		if(nAction == 0)
			return TRUE;

		MessageBox(strMent, "확인", MB_ICONINFORMATION);

		return nAction == 2 ? FALSE : TRUE;
	}

	return FALSE;
}


void CRcpDlg::OnSpecialTrcukSelect(UINT nFlag)
{
	if(((CButton*)GetDlgItem(nFlag))->GetCheck()){
		UINT control[] = {IDC_CARGO_JABARA_CHECK, IDC_CARGO_LIFT_CHECK, IDC_CARGO_WING_BODY_CHECK, IDC_CARGO_LIFT_WING_CHECK, IDC_CARGO_FREEZER_CHECK};

		for(int i=0; i<sizeof(control) / sizeof(long); i++) {
			if(nFlag != control[i])
				((CButton*)GetDlgItem(control[i]))->SetCheck(FALSE);
		}
	}

	GetSectionCharge(FALSE, FALSE, FALSE);
}

void CRcpDlg::ChangeCargoControl()
{
	if(LF->IsCarTypeTruck(GetCarTypeNew())) {
		m_chkCargoJabara.EnableWindow(TRUE);
		m_chkCargoLift.EnableWindow(TRUE);
		m_chkCargoWingBody.EnableWindow(TRUE);
		m_chkCargoLiftWing.EnableWindow(TRUE);
		m_chkCargoFreezer.EnableWindow(TRUE);
	}
	else {
		m_chkCargoJabara.EnableWindow(FALSE); m_chkCargoJabara.SetCheck(FALSE);
		m_chkCargoLift.EnableWindow(FALSE); m_chkCargoLift.SetCheck(FALSE);
		m_chkCargoWingBody.EnableWindow(FALSE); m_chkCargoWingBody.SetCheck(FALSE);
		m_chkCargoLiftWing.EnableWindow(FALSE); m_chkCargoLiftWing.SetCheck(FALSE);
		m_chkCargoFreezer.EnableWindow(FALSE); m_chkCargoFreezer.SetCheck(FALSE);
	}

}

int CRcpDlg::GetSpecialTruckType()
{
	if(m_chkCargoJabara.GetCheck()) return CARGO_JABARA;
	if(m_chkCargoLift.GetCheck()) return CARGO_LIFT;
	if(m_chkCargoWingBody.GetCheck()) return CARGO_WING_BODY;
	if(m_chkCargoLiftWing.GetCheck()) return CARGO_LIFT_WING;
	if(m_chkCargoFreezer.GetCheck()) return CARGO_FREEZER;

	return 0;
}

void CRcpDlg::SetSpecialTruckType(int special_truck_type)
{
	if(special_truck_type == CARGO_JABARA) m_chkCargoJabara.SetCheck(TRUE);
	if(special_truck_type == CARGO_LIFT) m_chkCargoLift.SetCheck(TRUE);
	if(special_truck_type == CARGO_WING_BODY) m_chkCargoWingBody.SetCheck(TRUE);
	if(special_truck_type == CARGO_LIFT_WING) m_chkCargoLiftWing.SetCheck(TRUE);
	if(special_truck_type == CARGO_FREEZER) m_chkCargoFreezer.SetCheck(TRUE);

}