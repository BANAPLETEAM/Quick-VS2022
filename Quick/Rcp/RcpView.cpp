// RcpView.cpp : 구현 파일입니다.
//
 
#include "stdafx.h"
#include "resource.h"
#include "RcpView.h"

#include "RcpDlg.h"
#include "MainFrm.h" 
#include "CustomerDlg.h"   
#include "ShowRcpNotice.h"
#include "SimpleSearchDlg.h" 
#include "MkLock.h"
#include "MyReportPaintManager.h"
#include "MakeRiderStat.h"

#include "DelayOrderDlg2.h" //Pane창 
#include "EmptyCarDlg1.h" //Pane창 
#include "AllocatePaneDlg.h"
#include "RiderMapDlg.h"

#include "AllocateBoardDlg.h"
#include "SetRcpPageDlg.h"

#include "WebOrderDlg.h"
#include "CustomerSmsDlg2.h"
#include "RcpPageCTIForm.h"
#include "RcpPageInfoForm.h"
#include "RcpPageMemoForm.h"
#include "OrderLogDetailDlg.h"
#include "ShowRiderInfoDlg.h"
#include "VRPreDate.h"
//#include "AdminAllocateDlg.h"
#include "CompleteAfterEditDlg.h"

#include "AllocateBoardTRSDlg.h"
#include "RcpPageMemoForm.h" 

#include "RcpSearchCarTypeDlg.h"
#include "RcpSearchPayTypeDlg.h"
#include "RegionSelectDlg.h"
#include "RcpPageMapForm.h"
#include "CompanyBranchListDlg1.h"
#include "MakeHtmlTable.h"
#include "RiderTraceMapDlg.h"
#include "RcpDlgSetupDlg.h"

#include "RcpMultiStateChange.h"
#include "ReceiptPrint.h"
#include "TransactionListDlg.h"
#include "RcpSearchTruckTypeDlg.h"
#include "MkMessenger.h"
#include "OrderPassDlg.h"
#include "ConnListDlg2.h"
#include "MyMkMessenger.h"
#include "LogiMapCns.h"
#include "RcpInsungDlg.h"
#include "JinsangTelRegDlg.h"
#include "JusoGoKr.h"

#include <iterator>

#define CALL_TO_RIDER 30
#define CALL_TO_CUSTOMER 40

#define LINE_PER_PAGE 40
#define YMARGIN		2000
#define XMARGIN		1000
#define SPACE		300

#define AUTO_REFRESH_TIMER 10
#define INIT_COMPLETE_TIMER	30

#define ID_POPUP_CLOSE (-1)
#define ID_GOTO_SITE (-2)
#define FLOAT_LOCATE -3

#define CHECK_STATE_COUNT 3
#define CHECK_STATE_NO_CHECK 0
#define CHECK_STATE_O 1
#define CHECK_STATE_X 2

#define SEARCH_CHECK_COUNT 8
#define SEARCH_EDIT_COUNT 8

#define  BILL_DRAW 10


#define ID_USE_UP_CHARGE1 7000
#define ID_USE_UP_CHARGE2 7001
#define ID_USE_UP_CHARGE3 7002
#define ID_USE_UP_CHARGE_RELEASE 7003

UINT searchCheckBox[] = {IDC_SEARCH_MY_RIDER_CHECK, IDC_MY_CALL_CHECK, IDC_HIDE_CROSS_CALL_CHECK, IDC_SHOW_CROSS_CALL_CHECK, IDC_SCHEDULE_ORDER_CHECK, IDC_INTERORDER_CHECK,  IDC_GET_ALLOC_CHECK, IDC_GET_MSG_CHECK};

UINT searchEditBox1[] = {IDC_SEARCH_TNO_EDIT, IDC_SEARCH_CUSTOMER_EDIT, IDC_SEARCH_DEPART_EDIT, IDC_SEARCH_MANAGER_EDIT, IDC_SEARCH_CUSTOMER_ID_EDIT, IDC_SEARCH_GROUP_EDIT, IDC_SEARCH_GROUP_DEPART_EDIT, IDC_SEARCH_CID_EDIT};
UINT searchEditBox2[] = {IDC_SEARCH_ETC_EDIT, IDC_SEARCH_START_EDIT, IDC_SEARCH_DEST_EDIT, IDC_SEARCH_RIDER_EDIT, IDC_SEARCH_RIDER_NO_EDIT, IDC_SEARCH_WNO_EDIT, IDC_SEARCH_MEMO_EDIT, IDC_SEARCH_INNER_MEMO_EDIT};//IDC_SEARCH_INNER_MEMO_EDIT 이거는 안씀 갯수 맞추기 위한 //IDC_SEARCH_START_REGION_EDIT, IDC_SEARCH_DEST_REGION_EDIT,


const char *szRefreshText[] = {"수동갱신", "1초", "3초", "5초", "10초", "15초", "20초", "30초", 
"40초", "50초", "1분", "2분", "5분", "10분"};

enum { RCPPAGE_CTI_FORM = 0, RCPPACE_MAP_FORM = 4};

bool IsNotMyAllocatedOrder(OrderRecord* pOrder)
{
	return !(pOrder->bMyOrder &&
		(pOrder->nState == STATE_ALLOCATED ||
			pOrder->nState == STATE_OK_ONLY_MAN ||
			pOrder->nState == STATE_FINISH));
}

void CRcpFormTabControl::OnItemClick(CXTPTabManagerItem* pItem)
{
	static BOOL bFirst = TRUE;

	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();

	if(hWnd == NULL)
		return;

	CFormView *pView = (CRcpViewBase*)CWnd::FromHandle(pItem->GetHandle());
	CRuntimeClass * pClass = pView->GetRuntimeClass();

	if(strcmp(pClass->m_lpszClassName, "CRcpPageMemoForm") == 0)
	{
		if(bFirst == FALSE)
			((CRcpPageMemoForm*)pView)->LoadText();
	}
	else if(strcmp(pClass->m_lpszClassName, "CRcpPageMapForm") == 0)
	{
		((CRcpView*)GetParent())->m_bAutoChangeMapForm = FALSE;
	}

	bFirst = FALSE;
}


// CRcpView

IMPLEMENT_DYNCREATE(CRcpView, CRcpViewBase)

CRcpView::CRcpView()
	: CRcpViewBase()
{
	m_bIgnoreCheckState = FALSE;
	m_bIsSaveState = FALSE;
	m_bGroup = FALSE;
	m_nCurBranch = 0xFFFF;

	m_bMove = FALSE;
	m_bFirstLocation = TRUE;

	m_nShareBalance = 0;
	m_nSmsBalance = 0;
	m_nKind = m_kPay = m_nKDoc = 0;
	m_nKDel = m_bR = FALSE;
	m_CurTab = 0;
	lTemp = 0;
	m_nLastSelItemNo = -1;
	m_nCurSel = -1;
	m_bAppRunFirst = TRUE;

	m_nCurCol = 0;
	m_bColAsc = TRUE;

	m_pDragWnd = NULL;

	m_bCreateRcpDlg = TRUE;
	m_bPartRefresh = FALSE;
	m_bPrePartRefresh = FALSE;
	m_dtLastRefresh = COleDateTime(2000,  1, 1, 1, 1, 1);
	m_dtLastRemove = COleDateTime::GetCurrentTime();
	m_dtLastGetCustomerInfo = COleDateTime(2000,  1, 1, 1, 1, 1);
	m_dt1 = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 1, 0);

	//m_strFilter = "dt1 > CONVERT(smalldatetime, CONVERT(char(12), GETDATE(), 23) ) ";
	m_nLastSearchCNo = 0;
	m_nDiscountSec =0xFFFF;
	m_dtLastForLimit = m_dtLastRefresh;

	m_bRefreshWithCID = FALSE;
	m_bRefreshOK	= TRUE;


	m_vrOrder = new CVirtualRecord();
	m_vrShareOrder = new CVirtualRecord();
	m_vrPreDate = new CVRPreDate();
	m_vrCur = m_vrOrder;

	m_bFirstRefresh = TRUE;
	m_bMultiSelectRefreshStop = FALSE;

	m_sAllocateRNo = "";

	m_bTooltipNoUse = FALSE;
	m_nReserveShowCount = 0;
	m_bStateSecondSort = FALSE;
	m_pWebOrderDlg = NULL;

	m_bBigUnderForm = 0;
	m_pInfoForm = NULL;
	m_pCTIForm = NULL;
	m_pMapForm = NULL;
	m_pMemoForm = NULL;
	m_sYear = "";
	m_bShareOrderRefresh = FALSE;
	m_bMoveControl = FALSE;
	m_bChangeCursor = FALSE;


	m_dtLastRefreshByShareCall = COleDateTime(2000, 1, 1, 1, 1, 1);
	m_nShareRcpCount = 0;
	m_nShareAllocateCount = 0; 
	m_nShareCompleteCount = 0;
	m_nShareCancelCount = 0;
	m_nShareEtcCount = 0;
	m_nShareAllCount = 0;
	m_bLoadReportState = FALSE;

	m_nRefreshType = 0;

	m_nLastSelItemNoCondition = -1;

	m_strInfoEditSearch = "";
	m_strInfoCheckSearch = "";
	m_strInfoCount = "";

	m_nShMyRider = 0;
	m_nShMyCall = 0;
	m_nShHideCrossCall = 0;
	m_nShShowCrossCall = 0;
	m_nShScheduleOrder = 0;
	m_nShInterOrder = 0;

	m_bSearchMode = FALSE;
	m_pRcpShTruckDlg = NULL;
	m_pRcpShCarDlg = NULL;
	m_pRcpShPayDlg = NULL;
	m_pLastSelRcpDlg = NULL;

	m_nStateAll = 0;
	m_nStateWait = 0;
	m_nStateReserved = 0;
	m_nStateRcp = 0;
	m_nStateAlloc = 0;
	m_nStateOnlyMan = 0;
	m_nStateCancelWait = 0;
	m_nStateFinish = 0;
	m_nStateCancel = 0;
	m_nStateEtc = 0;
	m_nStatePickup = 0;
	m_bAutoChangeMapForm = FALSE;
	m_nRefreshTNoForStateChange = -1;
	m_bAutoScroll = TRUE;

	memset(m_nSelectedRegionStartDongID, 0, MAX_REGION_SELECT_COUNT* sizeof(int));
	memset(m_nSelectedRegionDestDongID, 0, MAX_REGION_SELECT_COUNT * sizeof(int));

	m_pStateChange = new CRcpMultiStateChange(this);

	m_pReceiptPrint = new CReceiptPrint;
	m_nOnceSelectedTNo = 0;

	m_strShPreCustomerID = "";
	m_strShPreCustomerMemo = "";
	m_bGetCustomerMemo = FALSE;
	m_bUseCardOkNumberAddColumn = 0;
	m_bAllCheck = FALSE;
	m_nTodayIncome = 0;

	m_bReportReadyToPopulate = FALSE;
} 

CRcpView::~CRcpView()
{
	DELETE_OBJECT(m_pWebOrderDlg);
}

void CRcpView::DoDataExchange(CDataExchange* pDX)
{
	CRcpViewBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST_RCPPAGE, m_xList);
	DDX_Control(pDX, IDC_PERIOD_STATIC, m_PeriodStatic);

	DDX_Control(pDX, IDC_SEARCH_TNO_EDIT, m_edtShTNo);
	DDX_Control(pDX, IDC_SEARCH_CUSTOMER_EDIT, m_edtShCustomer);
	DDX_Control(pDX, IDC_SEARCH_DEPART_EDIT, m_edtShDepart);
	DDX_Control(pDX, IDC_SEARCH_MANAGER_EDIT, m_edtShManager);
	DDX_Control(pDX, IDC_SEARCH_CUSTOMER_ID_EDIT, m_edtShCustomerID);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT, m_edtShGroup);
	DDX_Control(pDX, IDC_SEARCH_GROUP_DEPART_EDIT, m_edtShGroupDepart);
	DDX_Control(pDX, IDC_SEARCH_CID_EDIT, m_edtShCID);
	DDX_Control(pDX, IDC_SEARCH_WNO_EDIT, m_edtShWNo);
	DDX_Control(pDX, IDC_SEARCH_ETC_EDIT, m_edtShEtc);
	DDX_Control(pDX, IDC_SEARCH_START_EDIT, m_edtShStart);
	DDX_Control(pDX, IDC_SEARCH_DEST_EDIT, m_edtShDest);
	DDX_Control(pDX, IDC_SEARCH_RIDER_EDIT, m_edtShRider);
	DDX_Control(pDX, IDC_SEARCH_RIDER_NO_EDIT, m_edtShRiderNo);
	DDX_Control(pDX, IDC_SEARCH_START_REGION_EDIT, m_edtShRegionStart);
	DDX_Control(pDX, IDC_SEARCH_DEST_REGION_EDIT, m_edtShRegionDest);
	DDX_Control(pDX, IDC_SEARCH_MEMO_EDIT, m_edtShCustomerMemo);
	DDX_Control(pDX, IDC_SEARCH_INNER_MEMO_EDIT, m_edtShCustomerInnerMemo);

	DDX_Text(pDX, IDC_SEARCH_TNO_EDIT, m_strShTNo);
	DDX_Text(pDX, IDC_SEARCH_CUSTOMER_EDIT, m_strShCustomer);
	DDX_Text(pDX, IDC_SEARCH_DEPART_EDIT, m_strShDepart);
	DDX_Text(pDX, IDC_SEARCH_MANAGER_EDIT, m_strShManager);
	DDX_Text(pDX, IDC_SEARCH_CUSTOMER_ID_EDIT, m_strShCustomerID);
	DDX_Text(pDX, IDC_SEARCH_GROUP_EDIT, m_strShGroup);
	DDX_Text(pDX, IDC_SEARCH_GROUP_DEPART_EDIT, m_strShGroupDepart);
	DDX_Text(pDX, IDC_SEARCH_CID_EDIT, m_strShCID);
	DDX_Text(pDX, IDC_SEARCH_WNO_EDIT, m_strShWNo);
	DDX_Text(pDX, IDC_SEARCH_ETC_EDIT, m_strShEtc);
	DDX_Text(pDX, IDC_SEARCH_START_EDIT, m_strShStart);
	DDX_Text(pDX, IDC_SEARCH_DEST_EDIT, m_strShDest);
	DDX_Text(pDX, IDC_SEARCH_RIDER_EDIT, m_strShRider);
	DDX_Text(pDX, IDC_SEARCH_RIDER_NO_EDIT, m_strShRiderNo);
	DDX_Text(pDX, IDC_SEARCH_START_REGION_EDIT, m_strShRegionStart);
	DDX_Text(pDX, IDC_SEARCH_DEST_REGION_EDIT, m_strShRegionDest);
	DDX_Text(pDX, IDC_SHOW_RIDER_INFO_EDIT, m_strShowRiderInfo);
	DDX_Text(pDX, IDC_SEARCH_MEMO_EDIT, m_strShCustomerMemo);
	DDX_Text(pDX, IDC_SEARCH_INNER_MEMO_EDIT, m_strShCustomerInnerMemo);
		
	DDX_Control(pDX, IDC_SEARCH_MY_RIDER_CHECK, m_chkShMyRider);
	DDX_Control(pDX, IDC_MY_CALL_CHECK, m_chkMyCall);
	DDX_Control(pDX, IDC_HIDE_CROSS_CALL_CHECK, m_chkHideCrossCall);
	DDX_Control(pDX, IDC_SHOW_CROSS_CALL_CHECK, m_chkShowCrossCall);
	DDX_Control(pDX, IDC_SCHEDULE_ORDER_CHECK, m_chkScheduleOrder);
	DDX_Control(pDX, IDC_INTERORDER_CHECK, m_chkInterOrder);
	DDX_Control(pDX, IDC_WEB_ORDER_CHECK, m_chkShWebOrder);

	DDX_Control(pDX, IDC_GET_ALLOC_CHECK, m_chkGetAlloc);
	DDX_Control(pDX, IDC_GET_MSG_CHECK, m_chkGetMsg);

	DDX_Control(pDX, IDC_DISPLAY_STATIC, m_stcDisplay);

	DDX_Control(pDX, IDC_CLEAR_ALL_CHECK_BTN, m_btnClearAllCheck);
	DDX_Control(pDX, IDC_DELETE_SEARCH_TEXT_BTN, m_btnDeleteSearchText);

	DDX_Control(pDX, IDC_INIT_SEARCH_BTN, m_btnInitSearch);
	DDX_Control(pDX, IDC_SHARE_SEARCH_BTN, m_btnShareSearch);

	DDX_Control(pDX, IDC_DATEFROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETO, m_ToDT);
	DDX_Control(pDX, IDC_NEW_BTN, m_btnNew);
	DDX_Control(pDX, IDC_NEW_BTN2, m_btnNew2);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);

	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_COMBO, m_RefreshCombo);


	DDX_Control(pDX, IDC_STATE_ALL_BTN3, m_btnStateAll);
	DDX_Control(pDX, IDC_STATE_RCP_BTN3, m_btnStateRcp);
	DDX_Control(pDX, IDC_STATE_WAIT_BTN3, m_btnStateWait);
	DDX_Control(pDX, IDC_STATE_RESERVED_BTN3, m_btnStateReserved);
	DDX_Control(pDX, IDC_STATE_ONLY_MAN_BTN3, m_btnStateOnlyMan);
	DDX_Control(pDX, IDC_STATE_ALLOC_BTN3, m_btnStateAlloc);
	DDX_Control(pDX, IDC_STATE_PICKUP_BTN3, m_btnStatePickup);
	DDX_Control(pDX, IDC_STATE_FINISH_BTN3, m_btnStateFinish);
	DDX_Control(pDX, IDC_STATE_CANCEL_BTN3, m_btnStateCancel);
	DDX_Control(pDX, IDC_STATE_ETC_BTN3, m_btnStateEtc);

	//DDX_Control(pDX, IDC_REFRESH_IC_BTN, m_RefreshICBtn);
	DDX_Control(pDX, IDC_PRE_ORDER_CHECK, m_chkPreOrder);

	DDX_Control(pDX, IDC_WEB_ORDER_BTN, m_btnWebOrder);
	DDX_Control(pDX, IDC_REFRESH_IC_BTN, m_btnRefreshIC);

	DDX_Control(pDX, IDC_STATIC1, m_stc1);

	DDX_Control(pDX, IDC_PAY_TYPE_STATIC, m_stcPayType);
	DDX_Control(pDX, IDC_CAR_TYPE_STATIC, m_stcCarType);
	DDX_Control(pDX, IDC_DISPLAY_STATIC2, m_stcDisplay2);//이소스 변경해야함

	DDX_Control(pDX, IDC_SHOW_RIDER_INFO_EDIT, m_edtShowRiderInfo);
	DDX_Control(pDX, IDC_USE_NEW_DLG_CHECK, m_chkUseNewDlg);
	DDX_Control(pDX, IDC_AUTO_SCROLL_BTN, m_btnAutoScroll);
}

BEGIN_MESSAGE_MAP(CRcpView, CRcpViewBase)
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CLOSE()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY() 
	ON_WM_CHAR()

	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
	ON_MESSAGE(WM_RECV_CID, OnRecvCid)
	ON_MESSAGE(WM_RESERVE_ORDER, OnReserveOrder)
	ON_MESSAGE(WM_REFRESH_LIST, OnRefreshList)

	ON_MESSAGE(WM_SAVE_RCP_LIST, OnSaveRcpList)
	ON_MESSAGE(WM_LOAD_RCP_LIST, OnLoadRcpList)
	ON_MESSAGE(WM_SAVE_CTI_LIST, OnSaveCtiList)
	ON_MESSAGE(WM_LOAD_CTI_LIST, OnLoadCtiList)

	ON_BN_CLICKED(IDC_USE_NEW_DLG_CHECK, OnBnClickedUseNewDlgChk)
	ON_BN_CLICKED(IDC_NEW_BTN, OnBnClickedNewBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(ID_STATE_SITE, OnChangeStateSite)
	ON_BN_CLICKED(ID_STATE_CARRY, OnChangeStateCarry)
	ON_BN_CLICKED(ID_STATE_ALLOCATE, OnBnClickedAllocateBtn)
	ON_BN_CLICKED(ID_STATE_RCP, OnBnClickedCancelABtn)
	ON_BN_CLICKED(ID_STATE_CANCEL, OnBnClickedCancelOBtn)
	ON_BN_CLICKED(ID_STATE_COMPLETE, OnBnClickedCompleteBtn)
	ON_BN_CLICKED(ID_STATE_FINISH, OnBnClickedFinishBtn)
	ON_BN_CLICKED(ID_STATE_INQUIRY, OnBnClickedInquiryBtn)
	ON_BN_CLICKED(ID_STATE_WAIT, OnChangeWaitState)
	ON_BN_CLICKED(ID_SHARE_ORDER, OnBnClickedShareOrder)	
	ON_BN_CLICKED(ID_COPY_ORDER, OnBnClickedCopyOrder)
	ON_BN_CLICKED(ID_ADD_ORDER, OnBnClickedAddOrder)
	ON_BN_CLICKED(ID_TRANS_INFO, OnBnClickedTransInfo)
	
	ON_BN_CLICKED(ID_ORDER_MOVE, OnMoveOrder)
	ON_BN_CLICKED(ID_OTHER_ALLOCATE, OnOtherAllocate)
	ON_BN_CLICKED(ID_STATE_PICKUP, OnBnClickedPickupBtn)

	ON_BN_CLICKED(IDC_SHOW_NOTICE_BTN, OnBnClickedShowNoticeBtn)

	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_REPORT_LIST_RCPPAGE, OnReportItemSelChanged)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST_RCPPAGE, OnReportItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST_RCPPAGE, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST_RCPPAGE, OnReportItemDblClick)
	ON_NOTIFY(XTP_NM_GRID_VSCROLL, IDC_REPORT_LIST_RCPPAGE, OnReportVScroll)
	ON_NOTIFY(XTP_NM_GRID_SORTORDERCHANGED, IDC_REPORT_LIST_RCPPAGE, OnReportSortOrderChanged)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_REPORT_LIST_RCPPAGE, OnReportColumnChangeChanged)
	ON_NOTIFY(XTP_NM_GRID_COLUMNWIDTHCHANGED, IDC_REPORT_LIST_RCPPAGE, OnReportColumnWidthChanged)
	
	ON_NOTIFY(LVN_BEGINDRAG, IDC_REPORT_LIST_RCPPAGE, OnReportBeginDrag)

	ON_MESSAGE(WM_RIDER_ALLOCATE, OnRiderAllocate)
	ON_MESSAGE(WM_RIDER_ALLOCATE2, OnRiderAllocate2)

	ON_CBN_SELCHANGE(IDC_REFRESH_COMBO, OnCbnSelchangeRefreshCombo)
	ON_COMMAND(ID_NEW_RIDER_LIST, OnNewRiderList)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_PRINTER_SETTING, OnPrinterSetting)
	ON_COMMAND(ID_RECEIPT_PRINT, OnReceiptPrint)
	ON_COMMAND(ID_RECEIPT_TAX_PRINT, OnReceiptTaxPrintView)	
	ON_COMMAND(ID_RECEIPT_GENERAL_PRINT, OnReceiptGeneralPrintView)
	ON_COMMAND(ID_STATE_BILLDRAW, OnReceiptTaxPrint)
	ON_COMMAND(ID_SHOW_ORDER_LOG, OnShowOrderLog)
	ON_COMMAND(ID_DAERI_SHARE, OnDaeriShare)
	ON_COMMAND(ID_DAERI_SHARE_RELEASE, OnDaeriShareRelease)
	ON_COMMAND(ID_DELAY_NOTICE,		OnDelayNotice)
	ON_COMMAND(ID_DELAY_NOTICE_RELEASE,		OnDelayNoticeRelesae)
	ON_COMMAND(ID_AUTO_WAIT, OnAutoWait)
		
	ON_COMMAND(ID_MENU_SEND_SMS, OnMenuSendSms)
	ON_COMMAND(ID_ALLOCATE_SEND_SMS, OnMenuAllocateSendSms)
	ON_COMMAND(ID_OTHER_ALLOCATE, OnOtherAllocate)
	ON_COMMAND(ID_SHOW_RIDER_POS_BTN, OnShowRiderPosBtn)
	ON_COMMAND(ID_CUR_ORDER_STATE, OnCurOrderState)
	ON_COMMAND(ID_MOVE_ORDER, OnMoveOrderBranch)
	ON_COMMAND(ID_MAKE_NEW_RCP_DLG, OnMakeNewRcpDlg)
	ON_COMMAND(ID_SET_DEPOSIT_ZERO, OnSetDepositZero)
	ON_COMMAND(ID_CALL_PASS, OnCallPass)
	ON_COMMAND(ID_REC_PLAYER, OnRecPlayer)
	ON_COMMAND(ID_REC_DOWNLOAD, OnRecDownload)
	ON_COMMAND(ID_JINSANG_CALLING_DENY, OnJinsangCallingDeny)

	ON_COMMAND(ID_USE_UP_CHARGE1, OnUseUpCharge1)
	ON_COMMAND(ID_USE_UP_CHARGE2, OnUseUpCharge2)
	ON_COMMAND(ID_USE_UP_CHARGE3, OnUseUpCharge3)
	ON_COMMAND(ID_USE_UP_CHARGE_RELEASE, OnUseUpChargeRelease)
	
	ON_BN_CLICKED(IDC_STATE_ALL_BTN3, OnBnClickedStateAllBtn)
	ON_BN_CLICKED(IDC_STATE_RCP_BTN3, OnBnClickedStateRcpBtn)
	ON_BN_CLICKED(IDC_STATE_WAIT_BTN3, OnBnClickedStateWaitBtn)
	ON_BN_CLICKED(IDC_STATE_ONLY_MAN_BTN3, OnBnClickedStateOnlyManBtn)
	ON_BN_CLICKED(IDC_STATE_RESERVED_BTN3, OnBnClickedStateReservedBtn)
	ON_BN_CLICKED(IDC_STATE_ALLOC_BTN3, OnBnClickedStateAllocBtn)
	ON_BN_CLICKED(IDC_STATE_PICKUP_BTN3, OnBnClickedStatePickupBtn)
	ON_BN_CLICKED(IDC_STATE_FINISH_BTN3, OnBnClickedStateFinishBtn)
	ON_BN_CLICKED(IDC_STATE_CANCEL_BTN3, OnBnClickedStateCancelBtn)
	ON_BN_CLICKED(IDC_STATE_ETC_BTN3, OnBnClickedStateEtcBtn)
	ON_BN_CLICKED(IDC_SHOW_CROSS_CALL_CHECK, OnBnClickedShowCrossCallCheck)
	ON_BN_CLICKED(IDC_INIT_SEARCH_BTN, OnBnClickedInitSearchBtn)
	ON_BN_CLICKED(IDC_STATE_RESERVED_BTN, OnBnClickedStateStateReservedBtn)
	ON_BN_CLICKED(IDC_SET_INIT_SEARCH_BTN, OnBnClickedSetInitSearchBtn)
	ON_BN_CLICKED(IDC_DELETE_SEARCH_TEXT_BTN, OnBnClickedDeleteSearchTextBtn)
	ON_BN_CLICKED(IDC_INTERORDER_CHECK, OnBnClickedInterorderCheck)

	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_NOTIFY(NM_SETFOCUS, IDC_DATEFROM, OnNMSetfocusDatefrom)

	ON_EN_CHANGE(IDC_SEARCH_START_EDIT, OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEST_EDIT, OnEnChangeSearchDestEdit)
	ON_EN_CHANGE(IDC_SEARCH_RIDER_EDIT, OnEnChangeSearchRiderEdit)
	ON_EN_CHANGE(IDC_SEARCH_CUSTOMER_EDIT, OnEnChangeSearchCustomerEdit)
	ON_EN_CHANGE(IDC_SEARCH_ETC_EDIT, OnEnChangeSearchEtcEdit)
	ON_BN_CLICKED(IDC_SHARE_SEARCH_BTN, OnBnClickedShareSearchBtn)
	ON_BN_CLICKED(IDC_SEARCH_MY_RIDER_CHECK, OnBnClickedSearchMyRiderCheck)
	ON_BN_CLICKED(IDC_MY_CALL_CHECK, OnBnClickedMyCallCheck)
	ON_BN_CLICKED(IDC_HIDE_CROSS_CALL_CHECK, OnBnClickedHideCrossCallCheck)
	ON_BN_CLICKED(IDC_SCHEDULE_ORDER_CHECK, OnBnClickedScheduleOrderCheck)
	ON_BN_CLICKED(IDC_WEB_ORDER_CHECK, OnBnClickedWebOrderCheck)
	ON_BN_CLICKED(IDC_WEB_ORDER_BTN, OnBnClickedWebOrderBtn)
	ON_BN_CLICKED(IDC_REFRESH_IC_BTN, OnBnClickedRefreshIcBtn)

	ON_EN_CHANGE(IDC_SEARCH_TNO_EDIT, &CRcpView::OnEnChangeSearchTnoEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEPART_EDIT, &CRcpView::OnEnChangeSearchDepartEdit)

	ON_EN_CHANGE(IDC_SEARCH_MANAGER_EDIT, &CRcpView::OnEnChangeSearchManagerEdit)
	ON_EN_CHANGE(IDC_SEARCH_CUSTOMER_ID_EDIT, &CRcpView::OnEnChangeSearchCustomerIDEdit)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT, &CRcpView::OnEnChangeSearchGroupEdit)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_DEPART_EDIT, &CRcpView::OnEnChangeSearchGroupDepartEdit)
	ON_EN_CHANGE(IDC_SEARCH_RIDER_NO_EDIT, &CRcpView::OnEnChangeSearchRiderNoEdit)
	ON_EN_CHANGE(IDC_SEARCH_WNO_EDIT, &CRcpView::OnEnChangeSearchWNoEdit)
	ON_EN_CHANGE(IDC_SEARCH_START_REGION_EDIT, &CRcpView::OnEnChangeSearchStartRegionEdit)
	ON_BN_CLICKED(IDC_GET_ALLOC_CHECK, &CRcpView::OnBnClickedGetAllocCheck)
	ON_BN_CLICKED(IDC_GET_MSG_CHECK, &CRcpView::OnBnClickedGetMsgCheck)
	ON_BN_CLICKED(IDC_OPEN_SEARCH_BTN, &CRcpView::OnBnClickedOpenSearchBtn)
	ON_BN_CLICKED(IDC_CLEAR_ALL_CHECK_BTN, &CRcpView::OnBnClickedClearAllCheckBtn)
	ON_BN_CLICKED(IDC_CONNECT_MESSENGER_FOR_LOGI_BTN, &CRcpView::OnBnClickedConnectMessengerForLogiBtn)
	ON_WM_KILLFOCUS()
	ON_EN_CHANGE(IDC_SEARCH_CID_EDIT, &CRcpView::OnEnChangeSearchCidEdit)
	ON_BN_CLICKED(IDC_NEW_RCP_DLG_BTN, &CRcpView::OnBnClickedNewRcpDlgBtn)
	ON_BN_CLICKED(IDC_DELETE_EDIT_BTN, &CRcpView::OnBnClickedDeleteEditBtn)
	ON_EN_CHANGE(IDC_SHOW_RIDER_INFO_EDIT, &CRcpView::OnEnChangeShowRiderInfoEdit)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEFROM, &CRcpView::OnDtnDatetimechangeDatefrom)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETO, &CRcpView::OnDtnDatetimechangeDateto)
	ON_BN_CLICKED(IDC_CARGO_NEW_BTN, &CRcpView::OnBnClickedCargoNewBtn)
	ON_EN_CHANGE(IDC_SEARCH_INNER_MEMO_EDIT, &CRcpView::OnEnChangeSearchInnerMemoEdit)
	ON_EN_CHANGE(IDC_SEARCH_MEMO_EDIT, &CRcpView::OnEnChangeSearchMemoEdit)
	ON_BN_CLICKED(IDC_SHOW_MY_CALL_COUNT_BTN, &CRcpView::OnBnClickedShowMyCallCountBtn)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_AUTO_SCROLL_BTN, &CRcpView::OnBnClickedAutoScrollBtn)
	ON_WM_MOUSEWHEEL()
	END_MESSAGE_MAP()


// CRcpView 진단입니다.

#ifdef _DEBUG
void CRcpView::AssertValid() const
{
	CRcpViewBase::AssertValid();
}

void CRcpView::Dump(CDumpContext& dc) const
{
	CRcpViewBase::Dump(dc);
}
#endif //_DEBUG


// CRcpView 메시지 처리기입니다.

void CRcpView::OnInitialUpdate()
{
	CRcpViewBase::OnInitialUpdate();
	LF->FillSpeicalTruckChage();

	m_pwndTaskPanel = LU->m_pwndTaskPanel;
	m_pwndPaneNetwork = LU->m_pwndPaneNetwork;


	m_chkUseNewDlg.SetCheck(LF->IsUseNewDlg());

	m_xList.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_xList.GetReportHeader()->AllowColumnSort(TRUE);
	m_xList.GetReportHeader()->AllowColumnResize(TRUE);
	m_xList.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_xList.SetPaintManager(new CMyReportPaintManager());
	m_xList.SetGridStyle(TRUE, xtpGridSolid);
	m_xList.SetGridColor(RGB(0x9f, 0xb2, 0xc7));
	m_xList.GetPaintManager()->SetGridColor(RGB(0x9f, 0xb2, 0xc7));

	LOGFONT m_lfList = {13,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움체"};
	CMyReportPaintManager *pPaint = (CMyReportPaintManager*)m_xList.GetPaintManager();
	pPaint->SetTextFont(m_lfList);
	pPaint->m_strNoItems = "조건에 맞는 데이터가 존재하지 않습니다.";
	//pPaint->SetColumnStyle(xtpGridColumnResource);
	m_xList.SetSelectedColor(CVirtualRecord::m_crStateBack12);
	m_xList.Populate();

	m_listIcons.Create(16,18, ILC_COLOR24|ILC_MASK, 0, 1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_LIST_NEW);
	m_listIcons.Add(&bmp, RGB(0,255,255));
	m_xList.SetImageList(&m_listIcons);

	m_xList.LoadListInfo();

	OnBnClickedStateAllBtn(); //전체선택
	LoadListFont(FALSE);

	LU->SetYesterDayCompleteCount();

	for(int i = 0; i < (int)m_xList.m_nColumnCount; i++)
	{
		m_xList.AddColumn(new CXTPGridColumn(i, 
			header_string[i], 
			header_width[i], TRUE));
	}

	m_xList.Populate();

	m_btnAutoScroll.SetCheckImage(IDB_SCROLL_O_PNG, IDB_SCROLL_X_PNG);

	LoadReportState();
	m_bLoadReportState = TRUE;

	MakeDistinctShareCodeMap();

	InitForm();
	InitControl();
	InitBranchInfo();
	InitMessengerInfo();

	if(!IsDialogMode())
		SetTimer(INIT_COMPLETE_TIMER, 1000, NULL);

	m_xList.GetReportHeader()->AllowColumnSort(TRUE);
	m_xList.GetReportHeader()->AllowColumnRemove(TRUE);
	m_xList.GetReportHeader()->AllowColumnResize(TRUE);
	m_xList.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_xList.Populate();
	
	if(LF->IsThisCompany("하나로퀵"))
	{
		m_chkGetMsg.SetCheck(TRUE);
		m_chkGetMsg.EnableWindow(FALSE);
		SetMsgCheck(TRUE);
		m_chkMyCall.EnableWindow(FALSE);
	}

//	SetTimer(AUTO_REFRESH_TIMER, 1000, NULL);
}

void CRcpView::InitControl()
{
	//by mksong (2011-02-17 오후 8:31) 아래 주석처리하지 마세요~
	if(m_ui.bDeveloper)
		GetDlgItem(IDC_CONNECT_MESSENGER_FOR_LOGI_BTN)->ShowWindow(SW_SHOW);

	m_nReserveShowCount = AfxGetApp()->GetProfileInt("RcpPage", "ReserveCount", 0);
	m_bStateSecondSort = AfxGetApp()->GetProfileInt("RcpPage", "StateSecondSort", 0);
	m_bGetCustomerMemo = AfxGetApp()->GetProfileInt("RcpPage", "GetCustomerMemo", 0);
	m_bUseCardOkNumberAddColumn = AfxGetApp()->GetProfileInt("RcpPage", "CardOkNumberAddColumn", 0);
	m_bIgnoreCheckState = AfxGetApp()->GetProfileInt("RcpPage", "IgnoreCheckState", 1);
	m_bRemoveSearch = AfxGetApp()->GetProfileInt("RcpPage", "RemoveSearch", 0);
	m_bAddTacksongCharge = AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongCharge", 0);
	m_bAddTacksongDrivingCharge = AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongDrivingCharge", 0);
	m_bSearchWithNoWName = AfxGetApp()->GetProfileInt("RcpPage", "SearchWithNoWName", 0);

	if(LF->IsThisCompany("하나로퀵"))
		m_bSearchWithNoWName = TRUE;

	RefreshStateSecondSort();

	m_stcDisplay.AddHandler(CXTPMarkupHyperlink::m_pClickEvent, CreateMarkupClassDelegate(this, &CRcpView::OnHyperlinkClick));
	ShowSearchMode(m_bSearchMode);

	m_btnStateAll.SetWindowText("전체");
	m_btnStateRcp.SetWindowText("접수");
	m_btnStateWait.SetWindowText("대기");
	m_btnStateReserved.SetWindowText("예약");
	m_btnStateOnlyMan.SetWindowText("개별");
	m_btnStateAlloc.SetWindowText("배차");
	m_btnStatePickup.SetWindowText("픽업");
	m_btnStateFinish.SetWindowText("완료");
	m_btnStateCancel.SetWindowText("취소");
	m_btnStateEtc.SetWindowText("문의/공지");

	m_vrOrder->SetCompanyCode(m_pBi->nCompanyCode);
	m_vrOrder->SetDOrderCompany(m_pBi->nDOrderTable);
	m_vrOrder->SetIntegrated(m_pBi->bIntegrated);
	m_vrOrder->SetRcpTimeCol(99);
	m_vrOrder->SetStartCol(99);
	m_vrOrder->SetUseCountCol(99);
	m_vrOrder->SetPayTypeCol(99);
	m_vrOrder->SetMyControl(&m_xList);
	m_btnStateAll.SetCheck(TRUE);

	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcNo = AfxGetApp()->LoadStandardCursor(IDC_NO);
	m_hcMoveHold = AfxGetApp()->LoadCursor(IDC_MOVEHOLD);
	m_hcMiddle = AfxGetApp()->LoadCursor(IDC_MIDDLE);

	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_CONTEXT_MENU));

	m_edtShTNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShCustomer.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShDepart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShManager.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShCustomerID.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShGroup.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShGroupDepart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShCID.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShWNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShEtc.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShStart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShDest.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShRider.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShRiderNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShRegionStart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShRegionDest.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShCustomerMemo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShCustomerInnerMemo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	
	m_edtShTNo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "오더번호");
	m_edtShCustomer.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "의뢰지명");
	m_edtShDepart.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "부서명");
	m_edtShManager.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "담당자");
	m_edtShCustomerID.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "고객번호");
	m_edtShGroup.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "출발상호");
	m_edtShGroupDepart.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "도착상호");
	m_edtShCID.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "CID");
	m_edtShWNo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "접수자");
	m_edtShEtc.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "적요");
	m_edtShStart.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "출발지");
	m_edtShDest.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "도착지");
	m_edtShRider.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "기사명");
	m_edtShRiderNo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "기사사번");
	m_edtShRegionStart.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "출발지역");
	m_edtShRegionDest.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "도착지역");
	m_edtShCustomerMemo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "고객메모");
	m_edtShCustomerInnerMemo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "DNIS");

	m_edtShowRiderInfo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtShowRiderInfo.SetUserOption(RGB(0, 0, 255), RGB(0xFF, 0xFF, 0xCC), "기사검색");

	m_vrOrder->SetRcpTimeColor(m_ci.m_nRcpTimeColor1, m_ci.m_nRcpTimeColor2, m_ci.m_nRcpTimeColor3);

	long nSelect = AfxGetApp()->GetProfileInt("TCombo", "TCombo", 0);

	m_strSortField = "nTNo";
	m_bColAsc = TRUE;
	m_nCurCol = 0;


	m_FromDT.SetFormat("yyyy-MM-dd");
	m_ToDT.SetFormat("yyyy-MM-dd");

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	m_RefreshCombo.SetCurSel(0);

	if(!m_bTooltipNoUse)
	{
		m_tooltip.Create(this, FALSE);
		m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
		m_tooltip.SetNotify();
		m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
		//m_tooltip.SetImageList(IDB_LIST, 16, 18, 18, RGB(0,255,255));
		m_tooltip.SetTransparency(30);

		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

		m_tooltip.AddTool(&m_xList, "");
	}

	if(m_ci.m_pQuickMainBranch && m_ci.m_pCargoMainBranch)
	{
		CRect rcQuick, rcCargo;
		m_btnNew.GetWindowRect(rcQuick);
		m_btnNew2.GetWindowRect(rcCargo);

		ScreenToClient(rcQuick);
		ScreenToClient(rcCargo);

		rcQuick.right = rcQuick.left + rcCargo.Width();
		rcCargo.left = rcQuick.right + 2;
		rcCargo.right = rcCargo.left + rcQuick.Width();

		m_btnNew.MoveWindow(rcQuick);
		m_btnNew2.MoveWindow(rcCargo);

		m_btnNew.SetWindowText("퀵\n접수");
		m_btnNew2.ShowWindow(SW_SHOW);
	}

	//WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP
	m_xList.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_xList.Populate();	
}

void CRcpView::InitMessengerInfo()
{
	BOOL bRecvIntercall = AfxGetApp()->GetProfileInt("RcpPage", "RecvIntercall", 0);
	BOOL bRecvAllocMsg = AfxGetApp()->GetProfileInt("RcpPage", "RecvAllocMsg", 0);

	m_chkGetMsg.SetCheck(bRecvIntercall);
	m_chkGetAlloc.SetCheck(bRecvAllocMsg);
	
	MyIntercallState("인터콜 받음");
}

LONG CRcpView::OnBranchClickEvent(WPARAM wParam, LPARAM lParam)
{
	CBranchInfo *pBi = (CBranchInfo*)wParam;

	if(m_ba.GetCount() > 1)
	{
		ChangeBranch(pBi);
		LF->StatusText(0, "현재 페이지가 '" + pBi->strBranchName + "' 지점으로 바뀌었습니다.");
		MoveClient();
	}

	return 0;
}

LONG CRcpView::OnRecvCid(WPARAM wParam, LPARAM lParam)
{
	ST_CID_INFO *pCIDInfo = (ST_CID_INFO*)wParam;

	if(pCIDInfo == NULL) return 0;

	//long nGroupID = max(min(pCIDInfo->nGroupID, 0), 0);
	long nGroupID = max(min(pCIDInfo->nLineID, 0), 0);
	
	RECV_PHONE_LIST_MAP::iterator it = m_mapRecvPhoneList.find(pCIDInfo->strPhone);
	if(it != m_mapRecvPhoneList.end())
	{
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - it->second;
		if(span.GetTotalSeconds() < 5.0)
		{
			delete pCIDInfo;
			return 0;
		}
		it->second = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_mapRecvPhoneList.insert(RECV_PHONE_LIST_MAP::value_type(pCIDInfo->strPhone, 
				COleDateTime::GetCurrentTime()));
	}

	if(nGroupID> 0)
	{
		if(nGroupID == 999) nGroupID = 0;

		if(m_ba.GetCount() > 1 && nGroupID != m_nCurBranch)
		{
			CBranchInfo *pBi;

			//통합모드권한이 없는 경우에 지사로 이동못하게 함
			if(!m_ci.m_bCidNonfiexdIntegrationTab)
				pBi = m_ba.GetAt(0);
			else
				pBi = pCIDInfo->pBi;

			LU->ChangeBranchItemInTaskPanel(m_pwndTaskPanel, pBi, m_pwndPaneNetwork);
			ChangeBranch(pBi, TRUE);

			LF->StatusText(0, "현재 페이지가 '" + pBi->strBranchName + 
				"' 지점으로 바뀌었습니다.");
			MoveClient();
		}
	}

	CMkLock lock(&m_csOrder);

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return 0;

	if(pCIDInfo->strPhone != "PRIVATE")
	{
		// choi 0을 붙히는 이유가 먼지..-> 키폰에서 0이 빠져서 들어오는 경우가 꽤있음by mksong (2011-03-22 오전 10:56)

		if(pCIDInfo->strPhone.GetLength() >= 8 && pCIDInfo->strPhone.GetAt(0) != '0' && 
			pCIDInfo->strPhone.GetAt(0) != '1')
			pCIDInfo->strPhone = "0" + pCIDInfo->strPhone;

		pCIDInfo->strPhone = LF->GetNoneDashNumber(pCIDInfo->strPhone);

		//remove a local DDD number, if the number is not this country...just go~
		if(pCIDInfo->strPhone.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			pCIDInfo->strPhone = pCIDInfo->strPhone.Right(pCIDInfo->strPhone.GetLength() - m_ci.m_strDDD.GetLength());

		CBranchInfo *pBi = NULL;
		CString strCallBranch;
		long nOperatorID = 0;  // cid 수신전화목록의 등록된 아이디

		if(m_ba.GetCount() > 1)
		{
			pBi = pCIDInfo->pBi;
			//pBi = m_ba.GetAt(nGroupID);
			strCallBranch = CString("[") + pBi->strPhone + "/" + pBi->strBranchName + "]" + "로 전화했음";
		}
		else
			pBi = m_ba.GetAt(0);

		if(pBi == NULL)
			return 0;

		nOperatorID = RefreshList(pCIDInfo->strPhone, "", pBi);
		nOperatorID = nOperatorID > 0 ? nOperatorID : 0;

		/* 당일오더만 갱신시켜야 하나 이전 접수리스트와 같이 동작하려면 이전조회에서도 리스트 갱신 필요
		if(IsTodaySearch()) //당일 오더만 화면갱신
		{
			nOperatorID = RefreshList(pCIDInfo->strPhone, "", pBi);
			nOperatorID = nOperatorID > 0 ? nOperatorID : 0;
		}
		else
		{
			long nRCompany = 0, nRNo = 0;

			nOperatorID = GetRiderAndInsertOperatorLog(pBi->nCompanyCode, pCIDInfo->strPhone, nRCompany, nRNo);
			nOperatorID = nOperatorID > 0 ? nOperatorID : 0;

			if(nRCompany > 0 && nRNo > 0)
			{
				LU->ShowRiderInfoDlg(nRCompany, nRNo, -1, -1, strCallBranch, -1, -1, pCIDInfo->strPhone);
				m_bCreateRcpDlg = FALSE; 
				delete pCIDInfo;
				return 0;
			}
		}
		*/

		if(m_bCreateRcpDlg) 
		{
			pCIDInfo->strPhone = LF->GetDashPhoneNumber(pCIDInfo->strPhone);

			CreateRcpDlg(m_ba.GetCount() > 1 ? pBi : NULL, 
				pCIDInfo->strPhone, -1, 0, pCIDInfo->strPhone, FALSE, pCIDInfo->nLineID, pCIDInfo->dwTick,0,FALSE,"",nOperatorID);
		}
	}
	else
	{
		if(m_bCreateRcpDlg) {
			CreateRcpDlg(m_ba.GetCount() > 1 ? m_ba.GetAt(nGroupID) : NULL, 
				"번호없음", -1, 0, "", FALSE, pCIDInfo->nLineID, pCIDInfo->dwTick);
		}
	}

	delete pCIDInfo;
	return 0;
}

LONG CRcpView::OnReserveOrder(WPARAM wParam, LPARAM lParam)
{
	CString *pstrName = (CString*)lParam;
	m_nLastSelItemNo = (int)wParam;

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return 0;


	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)
	CBranchInfo *pBi = LF->GetBranchInfo(GetItemCompany(m_vrOrder->GetItemRowFromTNo(m_nLastSelItemNo)));
	CreateRcpDlg(pBi, *pstrName, m_nLastSelItemNo, STATE_INTERNET);	

	delete pstrName;
	return 0;
}

LONG CRcpView::OnRefreshList(WPARAM wParam, LPARAM lParam)
{
	long nTNo = (long)wParam;

	if(lParam == NULL) {
		if(nTNo >= 0)
			m_nLastSelItemNo = nTNo;
	}
	else {
		CString *strFilter = (CString*)lParam;
		m_strFilter = *strFilter;
		m_nLastSelItemNo = 0;
		delete strFilter;
	}
	AllRefresh(TRUE);
	return 0;
}


int CRcpView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CRcpViewBase::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CRcpView::FirstRefresh()
{
	RefreshList();
}

void CRcpView::AllRefresh(BOOL bFromOrderChange)
{
	RefreshList(m_strCidNumber, "", NULL, FALSE, TRUE, ZERO, ZERO, bFromOrderChange);

	if(LU->m_pwndPane3)
	{
		if(!LU->m_pwndPane3->IsHidden())
		{
			if(LU->m_pwndPane3 != NULL)
				LU->m_pDelayOrderPane->RefreshList();
		}
	}
	

	if(LU->m_pwndPane4)
	{
		if(!LU->m_pwndPane4->IsHidden())
		{
			if(LU->m_pwndPane4 != NULL)
				LU->m_pEmptyCarPane->RefreshList();
		}
	}
	
	if(LU->m_pwndPane2)
	{
		if(!LU->m_pwndPane2->IsHidden())
		{
			if(LU->m_pwndPane2 != NULL)
				LU->m_pConnListPane->RefreshList(FALSE);
		}
	}
}


BOOL CRcpView::IsTodaySearch()
{
	COleDateTime dtFrom;
	m_FromDT.GetTime(dtFrom);

	//Base time 구하기
	m_ei.dtTodayBound.SetDateTime(m_ei.dtServerTime.GetYear(),
		m_ei.dtServerTime.GetMonth(),
		m_ei.dtServerTime.GetDay(),
		0, 0, 0);

	CString str;
	str.Format("%s, %s\n", m_ei.dtTodayBound.Format("%Y-%m-%d %H:%M:%S"),
		dtFrom.Format("%Y-%m-%d %H:%M:%S"));

	//g_bana_log->Print("%s\n", str);

	if(m_ei.dtTodayBound <= dtFrom)
		return TRUE;
	else 
		return FALSE;
}

long CRcpView::RefreshList(CString strRecvCID, CString strCallBranch, CBranchInfo *pBI, BOOL bShareOrder, BOOL bScrollTopOnce, long nRefreshRiderCompany, long nRefreshRNo, BOOL bFromOrderChange)
{	
	//UpdateData(TRUE); //by mksong (2011-01-09 오후 8:14) 이거는 별로 좋지 않은것 같아 삭제함

	if(FALSE == m_bRefreshOK) TRUE;
	CMkLock lock(&m_csOrder);

	//CWaitCursor wait;
	CString strSearchData;
	CString strSP;
	CVirtualRecord *vr = NULL;
	int nType;
	BOOL bTodaySearch = IsTodaySearch();
	BOOL bInsertTodayOrder = FALSE;

	m_bShareOrderRefresh = bShareOrder;

	m_xList.ShowRiderInfo(FALSE);
	m_xList.ShowCustomerInfo(FALSE);
	m_xList.ShowShareOrder(bShareOrder); 

	if(bShareOrder)
		nType = RT_TODAY_SHARE;
	else if(bTodaySearch || strRecvCID.GetLength() > 0)
		nType = RT_TODAY;
	else
		nType = RT_PREDATE;

	if(m_edtShTNo.GetWindowTextLength() == 8 || 
		m_edtShTNo.GetWindowTextLength() == 9) //아홉자리
		nType = RT_PREDATE;

	if(nType == RT_TODAY)  
	{
		//today query인 경우에 모든데이터를 가져와서 프로그램에서 필터링챵함

#ifdef _DEBUG
		strSP = "select_order_list_today_2011_37";
#else
		strSP = "@select_order_list_today_2011_37"; //@빠짐 
#endif
		vr = m_vrOrder; 
		RemoveNoneCrossOrder();
	}
	else if(nType == RT_PREDATE)
	{
		//predate query인 경우에 SP내에서 필티링함(데이터양 때문에)
#ifdef _DEBUG //이전이 _ 없느거였음
		strSP = "select_order_list_predate_2011_40";
#else
		strSP = "@select_order_list_predate_2011_40"; //@빠짐
#endif
		vr = m_vrPreDate;
	}
	else if(nType == RT_TODAY_SHARE)
	{
		strSP = "select_order_list_today_share_2011_37";
		vr = m_vrShareOrder;
	}

	if(m_chkPreOrder.GetCheck())
	{		
		COleDateTime dtFrom, dtTo;
		m_FromDT.GetTime(dtFrom); 
		m_ToDT.GetTime(dtTo);

		nType = RT_PREDATE;
		vr = m_vrPreDate;

		if(dtFrom.GetYear() != dtTo.GetYear())
		{
			MessageBox("이전오더 검색은 조회기간 년도가 같아야 합니다", "확인", MB_ICONINFORMATION);
			return 0;
		}

		long nYear = dtFrom.GetYear(); 

		COleDateTime dtCur = COleDateTime::GetCurrentTime();

		if(nYear <= 2003)
			m_sYear.Format("%d", 2004);
		else
			m_sYear.Format("%d", nYear + 1);

		strSP = "select_order_list_predate_SQ_by_2_" + m_sYear;
	}
	else
		m_sYear = "";

	CMkParameter *parOutCurDate = NULL;
	CMkParameter *parRCompany = NULL;
	CMkParameter *parRNo = NULL;
	CMkParameter *parCustomerID = NULL;
	CMkParameter *parWebOrderCount = NULL;
	CMkParameter *parReturnOperatorID = NULL;
	CMkParameter *parnShareRcpCount = NULL;
	CMkParameter *parShareAllocateCount = NULL;
	CMkParameter *parShareCompleteCount = NULL;
	CMkParameter *parShareCancelCount = NULL;
	CMkParameter *parShareEtcCount = NULL;
	CMkParameter *parShareAllCount = NULL;
	CMkParameter *parShareBalance = NULL;
	CMkParameter *parSmsBalance = NULL;

	//CBranchInfo *pBI = m_ba.GetAt(0);
	CMkCommand pCmd(m_pMkDb, strSP);
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), (int)0);

	if(nType == RT_TODAY || nType == RT_TODAY_SHARE)
	{
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_ba.GetCount() > 2);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode4 ? MAKE_SHARE_CODE(m_ci.m_nShareCode4) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode5 ? MAKE_SHARE_CODE(m_ci.m_nShareCode5) : -1);

		parOutCurDate = 
			pCmd.AddParameter(typeDate, typeInputOutput, sizeof(COleDateTime), m_dtLastRefresh);
	}
	else
	{
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	}

	long nSearchCustomerID = 0,  nOperatorID = 0;
	CString strSearch = "";
	
	if(m_strShCustomerID.GetLength() > 0)
		nSearchCustomerID = atol(strSearch);

	if(nType == RT_TODAY || nType == RT_TODAY_SHARE)
	{
		BOOL bShareRiderHaveMyOrder = FALSE;
		static DWORD dwTickCount = GetTickCount() - 60000;
		if(GetTickCount() - dwTickCount >= 60000)
		{
			bShareRiderHaveMyOrder = TRUE;
			dwTickCount = GetTickCount();
		}

		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bShareRiderHaveMyOrder);
		pCmd.AddParameter(typeString, typeInput, strRecvCID.GetLength(), strRecvCID);
		parRCompany = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		parRNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);		
		parCustomerID = pCmd.AddParameter(typeLong, typeInputOutput, sizeof(long), nSearchCustomerID);
		parWebOrderCount = pCmd.AddParameter(typeLong, typeInputOutput, sizeof(long), 
			m_chkShWebOrder.GetCheck() == 0 ? 0 : 1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long),LF->GetCurBranchInfo()->nCompanyCode <= 0 ? 0 : LF->GetCurBranchInfo()->nCompanyCode);
		parReturnOperatorID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long),0);

		parnShareRcpCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareRcpCount);
		parShareAllocateCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareAllocateCount);
		parShareCompleteCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareCompleteCount);
		parShareCancelCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareCancelCount);
		parShareEtcCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareEtcCount);
		parShareAllCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareAllCount);
		parShareBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nShareBalance);
		parSmsBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nSmsBalance);
	} 
	else if(nType == RT_PREDATE)
	{
		UpdateData(TRUE);
		COleDateTime dtFrom, dtTo;
		m_FromDT.GetTime(dtFrom);
		m_ToDT.GetTime(dtTo);
	
		COleDateTime dt(COleDateTime::GetCurrentTime());

		COleDateTimeSpan span = dtFrom - dtTo;

		/*if(m_btnStateAll.GetCheck() && m_strShTNo.GetLength() == 0 && m_strShCustomer.GetLength() == 0 && m_strShDepart.GetLength() == 0 && m_strShManager.GetLength() == 0 &&
			m_strShCustomerID.GetLength() == 0 && m_strShGroup.GetLength() == 0 && m_strShGroupDepart.GetLength() == 0 && m_strShCID.GetLength() == 0 && m_strShEtc.GetLength() == 0 &&
			m_strShStart.GetLength() == 0 && m_strShDest.GetLength() == 0 && m_strShRider.GetLength() == 0 && m_strShRiderNo.GetLength() == 0 && m_strShWNo.GetLength() == 0 &&
			m_strShCustomerMemo.GetLength() == 0 && m_strShCustomerInnerMemo.GetLength() == 0 && !CRcpSearchCarTypeDlg::IsUseSearchFilter() && 
			!CRcpSearchPayTypeDlg::IsUseSearchFilter() && !CRcpSearchTruckTypeDlg::IsUseTruckSearchFilter() && !CRcpSearchTruckTypeDlg::IsUseTonSearchFilter())
		{
			MessageBox("이전오더 검색조건이 설정되지 않았습니다.", "확인", MB_ICONINFORMATION);
			return 0;
		}*/

		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtFrom);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTo);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateAll.GetCheck() ? 0 : 1);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateWait.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateReserved.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateRcp.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateOnlyMan.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateAlloc.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStatePickup.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateFinish.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateCancel.GetCheck() ? 1 : 0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_btnStateEtc.GetCheck() ? 1 : 0);
		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_strShTNo));
		pCmd.AddParameter(typeString, typeInput, m_strShCustomer.GetLength(), m_strShCustomer);
		pCmd.AddParameter(typeString, typeInput, m_strShDepart.GetLength(), m_strShDepart);
		pCmd.AddParameter(typeString, typeInput, m_strShManager.GetLength(), m_strShManager);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_strShCustomerID));
		pCmd.AddParameter(typeString, typeInput, m_strShGroup.GetLength(), m_strShGroup);
		pCmd.AddParameter(typeString, typeInput, m_strShGroupDepart.GetLength(), m_strShGroupDepart);
		pCmd.AddParameter(typeString, typeInput, m_strShCID.GetLength(), m_strShCID);
		pCmd.AddParameter(typeString, typeInput, m_strShEtc.GetLength(), m_strShEtc);
		pCmd.AddParameter(typeString, typeInput, m_strShStart.GetLength(), m_strShStart);
		pCmd.AddParameter(typeString, typeInput, m_strShDest.GetLength(), m_strShDest);
		pCmd.AddParameter(typeString, typeInput, m_strShRider.GetLength(), m_strShRider); 
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_strShRiderNo));
		pCmd.AddParameter(typeString, typeInput, m_strShWNo.GetLength(), m_strShWNo);
		pCmd.AddParameter(typeString, typeInput, m_strShCustomerMemo.GetLength(), m_strShCustomerMemo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atoi(m_strShCustomerInnerMemo));//DNIS 

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShMyRider);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShMyCall);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShHideCrossCall);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShShowCrossCall);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShScheduleOrder);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShInterOrder);

		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::IsUseSearchFilter());
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType1);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType2);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType3);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType4);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType5);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType6);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType7);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType8);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType9);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType10);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType11);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType12);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType13);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType14);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchCarTypeDlg::m_bCarType15);

		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::IsUseSearchFilter());
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType1);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType2);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType3);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType4);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchPayTypeDlg::m_bPayType7);

		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::IsUseTruckSearchFilter());
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTruckType0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTruckType1);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTruckType2);

		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::IsUseTonSearchFilter());
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType0);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType1);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType2);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType3);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType4);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType5);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), CRcpSearchTruckTypeDlg::m_bTonType6);

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.GetShareCode1(m_ui.nCompany));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	}

	CMkRecordset pRs(m_pMkDb);
	if(!pRs.Execute(&pCmd)) 
		return 0;

	int nState, nKDelivery = 0;
	long nTNo , nCompany, nRiderCompany;
	int nRNo, nPayType, nAllocGroup, nRunType, nWayType;
	long nTotal = 0; 
	BOOL bInternet, bScheduleOrder, bClientShare5, bReserved, bAutoWait;
	CString strCName, strStart, strDest, strEtc, strSName, strDName;
	COleDateTime dt0, dt1, dt2, dt3,dt4, dtFinal, dtLast, dtReserve, dtDelayNotice, dtFoodComplete;
	long nCNo, nWNo = 0, nSCNo = 0, nDCNo = 0;
	CString strRName, strManager, sWName;
	long nShareCode1 = 0, nShareCompany = 0;
	long nStartRealDongID, nDestRealDongID, nStartPosX, nStartPosY, nDestPosX, nDestPosY, nDistanceKM = 0, nTransOrder = 0, nChargeTrans = 0;
	CString strOPhone, strSPhone, strDPhone, sWebCount ="", strItemType, strOMobile;
	long nReserveAfter =0, nWebOrderCount = 0;
	BOOL bClientShare, bOtherOrder, bTodayOrder, bFoodOrder;
	long nSignType = 0, nOGNo = 0, nRiderAllocate = 0, nDeposit = 0, nDNIS =0, nRiderShareCode1 = 0;
	CString strSAddress, strDAddress, strSDetail, strDDetail, strCID, strDepart;
	long nDepositRate = 0, nFinalDepositRate = 0, nConsignTNo = 0, nConsignWayID = 0, nCardOkAmt = 0;
	long nChargeBasic = 0, nChargeAdd = 0, nChargeDis = 0,  nChargeDriving = 0, nCreditCardType = 0, nUseCount = 0, nWCompany = 0, 
		nConsignSumCharge = 0,nTNoSet = 0 ;
	int nTruckType = 0, nLoadType = 0, nBillDraw = 0, nReceiptType = 0, nOrderAllocType = 0, nRcpType = 0, nDaeriCode = 0;
	CString strTon = "", sStateString = "", sConsignDestSido = "";
	CString strDManager, strSManager, strODong, strSMobile, strDMobile, strOAddress, strODetail, strBCCardTranNumber;
	long nCTNo = 0, nFinalRiderDeposit, nChargeCompany;
	char buffer[15];
	long nRow = 0, nChargeReturn, nMileage, nChargeRiderAuto, nChargeRevision;
	BOOL bSentPickupSms2;
	CString strOMemo;

	BOOL bNoShowPhone = FALSE; //!LF->POWER_CHECK(2004, "고객전화번호 항상표시");
	//BOOL bShowLastPhoneNumber = LF->POWER_CHECK(2009, "고객전화번호 끝번호 보이기");
	//BOOL bNoPowerUseCountDisplay = !LF->POWER_CHECK(2012, "고객이용횟수 표시");
	
	BOOL bNoPowerRcpInt = FALSE,bStartWaitInquiryReceipt = FALSE;
	OrderRecordList::iterator it;
	OrderRecord tempRecord;
	OrderRecordList &order = vr->GetOrderRecordList();
	OrderIndex &index = vr->GetOrderIndex();
	OrderIndex &filter = vr->GetFilterIndex();
	
	MAP_ORDER_OWN_RIDER::iterator OrderOWNRider_iter;

	if(nType == RT_TODAY)
	{
		parCustomerID->GetValue(nSearchCustomerID);
	}
	else if(nType == RT_PREDATE)
	{
		order.clear();
		index.clear();
		filter.clear();

		if(!LF->POWER_CHECK(2003, "이전오더검색", FALSE))
			return 0;

		if(IsLeftTodayOrder()) //오늘 오더는 남겨둠
			InsertTodayOrder(order, index, bInsertTodayOrder);
	}
	else if(nType == RT_TODAY_SHARE)
	{
		order.clear();
		index.clear();
		filter.clear();
	}
	else
	{
		parWebOrderCount->GetValue(nWebOrderCount);
		sWebCount.Format("web-%d", nWebOrderCount);
		m_btnWebOrder.SetWindowText(sWebCount);
	}

	m_vrCur = vr;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue(0, nState);
		pRs.GetFieldValue(1, nTNo);
		pRs.GetFieldValue(2, strCName);
		pRs.GetFieldValue(3, strDepart);
		pRs.GetFieldValue(4, strStart);
		pRs.GetFieldValue(5, strDest);
		pRs.GetFieldValue(6, dt0);
		pRs.GetFieldValue(7, dt1);
		pRs.GetFieldValue(8, nWayType);
		pRs.GetFieldValue(9, nKDelivery);
		pRs.GetFieldValue(10, nRunType);
		pRs.GetFieldValue(11, nRNo);
		pRs.GetFieldValue(12, dt2);
		pRs.GetFieldValue(13, dt3);
		pRs.GetFieldValue(14, dt4);
		pRs.GetFieldValue(15, nTotal);
		pRs.GetFieldValue(16, nPayType);
		pRs.GetFieldValue(17, strEtc);
		pRs.GetFieldValue(18, dtFinal);
		pRs.GetFieldValue(19, strDName);
		pRs.GetFieldValue(20, nCompany);
		pRs.GetFieldValue(21, bInternet);
		pRs.GetFieldValue(22, nRiderCompany);
		pRs.GetFieldValue(23, nAllocGroup);
		pRs.GetFieldValue(24, nCNo);
		pRs.GetFieldValue(25, nWNo);
		pRs.GetFieldValue(26, strRName);
		pRs.GetFieldValue(27, strManager);
		pRs.GetFieldValue(28, nShareCode1);
		pRs.GetFieldValue(29, dtLast);
		pRs.GetFieldValue(30, nStartRealDongID);
		pRs.GetFieldValue(31, nDestRealDongID);
		pRs.GetFieldValue(32, sWName);
		pRs.GetFieldValue(33, nStartPosX);
		pRs.GetFieldValue(34, nStartPosY);
		pRs.GetFieldValue(35, nDestPosX);
		pRs.GetFieldValue(36, nDestPosY);
		pRs.GetFieldValue(37, strOPhone);
		pRs.GetFieldValue(38, strSPhone);
		pRs.GetFieldValue(39, strDPhone);
		pRs.GetFieldValue(40, strOMobile);
		pRs.GetFieldValue(41, nDistanceKM);
		pRs.GetFieldValue(42, nTransOrder);
		pRs.GetFieldValue(43, strSName);
		pRs.GetFieldValue(44, nSCNo);
		pRs.GetFieldValue(45, nDCNo);
		pRs.GetFieldValue(46, nReserveAfter);
		pRs.GetFieldValue(47, bScheduleOrder);
		pRs.GetFieldValue(48, nChargeTrans);
		pRs.GetFieldValue(49, bClientShare);
		pRs.GetFieldValue(50, nSignType);
		pRs.GetFieldValue(51, strItemType);
		pRs.GetFieldValue(52, strSAddress);
		pRs.GetFieldValue(53, strDAddress);
		pRs.GetFieldValue(54, strSDetail);
		pRs.GetFieldValue(55, strDDetail);
		pRs.GetFieldValue(56, bOtherOrder);
		pRs.GetFieldValue(57, bTodayOrder);
		pRs.GetFieldValue(58, nOGNo);
		pRs.GetFieldValue(59, nRiderAllocate);
		pRs.GetFieldValue(60, nDeposit);
		pRs.GetFieldValue(61, nDNIS);
		pRs.GetFieldValue(62, strCID);
		pRs.GetFieldValue(63, nRiderShareCode1);
		pRs.GetFieldValue(64, nDepositRate);
		pRs.GetFieldValue(65, nFinalDepositRate);
		pRs.GetFieldValue(66, nChargeBasic);
		pRs.GetFieldValue(67, nChargeAdd);
		pRs.GetFieldValue(68, nChargeDis);
		pRs.GetFieldValue(69, bClientShare5);

		//if(nType != RT_PREDATE)
		//{
			pRs.GetFieldValue(70, nTNoSet);
			pRs.GetFieldValue(71, nChargeDriving);
			pRs.GetFieldValue(72, dtReserve);
			pRs.GetFieldValue(73, nTruckType);
			pRs.GetFieldValue(74, strTon);
			pRs.GetFieldValue(75, nLoadType);
			pRs.GetFieldValue(76, nBillDraw);
			pRs.GetFieldValue(77, strDManager);
			pRs.GetFieldValue(78, strSManager);
			pRs.GetFieldValue(79, strODong);
			pRs.GetFieldValue(80, nReceiptType);
			pRs.GetFieldValue(81, nCreditCardType);
			pRs.GetFieldValue(82, strSMobile);
			pRs.GetFieldValue(83, strDMobile);
			pRs.GetFieldValue(84, nUseCount);
			pRs.GetFieldValue(85, bReserved);
			pRs.GetFieldValue(86, nWCompany);
			pRs.GetFieldValue(87, nConsignSumCharge);
			pRs.GetFieldValue(88, nConsignTNo);
			pRs.GetFieldValue(89, sConsignDestSido);
			pRs.GetFieldValue(90, nConsignWayID);
			pRs.GetFieldValue(91, nOrderAllocType);
			pRs.GetFieldValue(92, strOAddress);
			pRs.GetFieldValue(93, strODetail);
			pRs.GetFieldValue(94, nCardOkAmt);
			pRs.GetFieldValue(95, strBCCardTranNumber);
			pRs.GetFieldValue(96, nRcpType);
			pRs.GetFieldValue(97, nDaeriCode);
			pRs.GetFieldValue(98, nCTNo);
			pRs.GetFieldValue(99, nFinalRiderDeposit);
			pRs.GetFieldValue(100, nChargeCompany);
			pRs.GetFieldValue(101, bStartWaitInquiryReceipt);
			pRs.GetFieldValue(102, dtDelayNotice);
			pRs.GetFieldValue(103, bFoodOrder);
			pRs.GetFieldValue(104, dtFoodComplete);
			pRs.GetFieldValue(105, nChargeReturn);
			pRs.GetFieldValue(106, bSentPickupSms2);
			pRs.GetFieldValue(107, bAutoWait);
			pRs.GetFieldValue(108, nMileage);
			pRs.GetFieldValue(109, nChargeRiderAuto);
			pRs.GetFieldValue(110, strOMemo);
			pRs.GetFieldValue(111, nChargeRevision);

		//}

		
		nShareCompany = 0; 

		//접수자 공지 추가, 101: 종료후 오더 수정에 대한 요청오더
		if(nState == 1 || nState == 101) {
			if(dt1 > m_ei.dtTodayBound)
			{
				if(nState == 1)
					AddRcpNotice(nTNo, dt0, strCName, strEtc);
				else 
				{
					if(!m_ci.IsChildCompany(nCompany))
					{
						CString strNotice;
						strNotice.Format("[%s]에서 %s에 완료된 자사기사 배차오더 [%s->%s]에 대해서, 오더완료후 요금관련 수정요청입니다.",
							m_ci.GetName(nCompany), 
							dtFinal.Format("%Y-%m-%d %H:%M:%S"), strStart, strDest);
						AddRcpNotice(nTNo, dt0, "수정요청", strNotice, TRUE);
					}
				}
			}
			pRs.MoveNext();
			continue;
		}


		BOOL bMyOrder = m_ci.IsChildCompany(nCompany);

		if((!bMyOrder) && (nType != RT_TODAY_SHARE) &&
			((nState == 8 || nState == 9 || nState == 10 || nState == 40) || 
			(nState == 11 && dt2 > COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 2, 0, 0))))
		{ 
			pRs.MoveNext();
			continue;
		}

		strEtc.Replace("\r\n", "  ");

		BOOL bHidePhone = GetSecondCrossState(nCompany) ? TRUE : FALSE;
		BOOL bInserted = FALSE;
		BOOL bAsteriskPhone = !LF->POWER_CHECK(2020, "뒷자리*처리", FALSE);

		if(bOtherOrder)
		{
			it = m_mapOtherOrder.find(nTNo);
			if(it == m_mapOtherOrder.end())
			{
				m_mapOtherOrder.insert(OrderRecordList::value_type(nTNo, tempRecord));
				it = m_mapOtherOrder.find(nTNo);
				bInserted = TRUE;
			}
		}
		else
		{
			it = order.find(nTNo);
			if(it == order.end())
			{ 
				order.insert(OrderRecordList::value_type(nTNo, tempRecord));
				it = order.find(nTNo);
				index.insert(OrderIndex::value_type((long)index.size(), nTNo));
				bInserted = TRUE;
			}
			else
			{
				if((nTransOrder == 2) && (it->second.nTransOrder!= 2))
				{
					((CMainFrame*)AfxGetMainWnd())->ShowTransInformationRequestPopup(nTNo, strStart, strDest, strRName, nRNo, strCName, nState);
				}
			}
		}

		//(*it).second.info[1] = m_ci.GetName(nCompany);
		(*it).second.info[1] = m_ci.GetProperName(nCompany); 
		(*it).second.info[2] = ltoa(nTNo, buffer, 10);
		sStateString = LF->GetStateString((bShareOrder && bClientShare5 > 0 && nState == 10) ? 100 : nState);	
		(*it).second.info[3] = (LF->GetBranchInfo(nCompany)->IsCargo() && nState == STATE_FINISH && nBillDraw == BILL_DRAW ) ? "발행" : sStateString;

		CString strTemp= "";
		if(bInternet && nAllocGroup > 0) 
			strTemp.Format("(%s%d)", LF->GetInternetReceiptType(nReceiptType), nAllocGroup);
		else if(bInternet) 
			strTemp.Format("(%s)", LF->GetInternetReceiptType(nReceiptType) );
		else if(nAllocGroup > 0) 
			strTemp.Format("(%d)", nAllocGroup);			
		
		strCName = strTemp + strCName;

		if(nState == 11) 
			(*it).second.dtState = dt2;
		else if(nState == 30 )
			(*it).second.dtState = dt3;
		else if(nState == 31 )
			(*it).second.dtState = dt4;
		else if(nState == 35)
			(*it).second.dtState = dtFinal;
		else
			(*it).second.dtState = dt1;

		(*it).second.dt3 = dt3;
		(*it).second.dt4 = dt4;
		(*it).second.dtFinal = dtFinal;

		(*it).second.nDeposit = nDeposit;
		(*it).second.bReserved = bReserved;
		(*it).second.bStartWaitInquiryReceipt = bStartWaitInquiryReceipt;

		COleDateTimeSpan span = 0; CString strTime = "";
		if((*it).second.dtState.m_status  != 2)  // DateTimeStatus.null
		{
			//음 dt1이 맞는듯.. 기존 dt0이었습니다
			//if(nState == STATE_OK)// 접수상태는 대기로 갈때 dt1을 현재 시간으로 바꿔버림 최초접수시간에서 시간경과
			//	span = COleDateTime::GetCurrentTime() - dt0;
			//else
			//	span = COleDateTime::GetCurrentTime() - (*it).second.dtState;
			//span =  COleDateTime::GetCurrentTime() - dt1;
			
			// 예약오더는 접수기준시간
			if(bReserved || bStartWaitInquiryReceipt )  // bStartWaitInquiryReceipt 첫대기후 접수변경시 옵션
				span =   COleDateTime::GetCurrentTime() - dt1;
			else
				COleDateTime::GetCurrentTime() - dt1;			
			
			if(nState ==  STATE_OK ||  nState == STATE_INTERNET ||
				nState == STATE_OK_ONLY_MAN || nState == STATE_FINISH ||				 
				nState == STATE_ALLOCATED || nState == STATE_CANCELED ||
				nState == STATE_PICKUP)
			{					
				strTime.Format("%d", (long)span.GetTotalMinutes());									
			}
			
		}
 
		if(bHidePhone)
			(*it).second.info[4] = "N/A";  
		else
		{
			//if(nFinalDepositRate == ZERO)
			if(nDeposit == ZERO) 
				(*it).second.info[4] = "무/" + strCName;
			else
				(*it).second.info[4] = strCName;

		}

		(*it).second.info[5] = (bHidePhone) ? "N/A" : strODong;
		(*it).second.info[6] = (bHidePhone) ? "N/A" : strDepart;

		//(*it).second.info[7] = (bHidePhone) ? "N/A" : strCID;

		if(bHidePhone)
			(*it).second.info[7] = "N/A";
		else
		{
			if(bAsteriskPhone)
				(*it).second.info[7] = LF->GetAsteriskPhoneNumber(strCID);
			else
				(*it).second.info[7] = strCID;
		}
		
		if(bHidePhone)
			strTemp = "N/A";
		else
		{
			if(bAsteriskPhone)
				strTemp = LF->GetAsteriskPhoneNumber(strOPhone) + "/" + LF->GetAsteriskPhoneNumber(strOMobile);
			else
				strTemp = LF->GetDashPhoneNumber(strOPhone) + "/" + LF->GetDashPhoneNumber(strOMobile);
			
			if(strTemp == "/")
				strTemp = "";
		} 

		(*it).second.info[8] = strTemp;
		(*it).second.info[9] = (bHidePhone) ? "N/A" : strSName;
		(*it).second.info[10] = (bHidePhone) ? "N/A" : strSManager;
		if(nConsignTNo > 0 && nConsignTNo < 5500000 && sConsignDestSido.GetLength() > 0)
			strDName = "[연계대기:" +sConsignDestSido + "]" + strDName;
		else if(nConsignTNo > 0 && nConsignTNo > 5500000 && sConsignDestSido.GetLength() > 0)
			strDName = "[연계:" +sConsignDestSido + "]" + strDName;

		(*it).second.info[11] = (bHidePhone) ? "N/A" : strDName;
		(*it).second.info[12] = (bHidePhone) ? "N/A" : strDManager;

		(*it).second.info[13] = nStartRealDongID <= 0 ? "" : m_poiNew.GetPOI(nStartRealDongID)->GetGugun() + m_poiNew.GetPOI(nStartRealDongID)->GetSido();
		(*it).second.info[14] = strStart;
		(*it).second.info[15] = nDestRealDongID <= 0 ? "" :m_poiNew.GetPOI(nDestRealDongID)->GetGugun() + m_poiNew.GetPOI(nDestRealDongID)->GetSido();
		(*it).second.info[16] = strDest;
		
		if(nState == STATE_RESERVED)// || http://www.teamoffice.com/myoffice/logisoft/task/show/882360#1345101047091 요청
			//(bReserved == TRUE && (nState == STATE_OK_ONLY_MAN || nState == STATE_ALLOCATED || nState == STATE_PICKUP || nState == STATE_FINISH)))
		{
			(*it).second.info[17] = dtReserve.Format("%m/%d");
			(*it).second.info[18] = dtReserve.Format("%H:%M@");
			(*it).second.dtSort = dtReserve;
		}
		else if(bReserved == TRUE && (nState == STATE_WAIT || nState == STATE_OK || nState == STATE_OK_ONLY_MAN || nState == STATE_ALLOCATED || nState == STATE_PICKUP || nState == STATE_FINISH))
		{
			(*it).second.info[17] = dt1.Format("%m/%d");
			(*it).second.info[18] = dt1.Format("@%H:%M");
			(*it).second.dtSort = dt1;
		}
		else
		{
			if(m_ci.m_nCompanyCode == 10 || m_ci.m_nCompanyCode == 20)
			{
				(*it).second.info[17] = dt1.Format("%m/%d");
				(*it).second.info[18] = dt1.Format("%H:%M");
				(*it).second.dtSort = dt1;
			}
			else
			{
				(*it).second.info[17] = dt0.Format("%m/%d");
				(*it).second.info[18] = dt0.Format("%H:%M");
				(*it).second.dtSort = dt0;
			}			
		}
	 
		(*it).second.info[19] = strTime; //ltoa(span.GetMinutes(), buffer, 10);
		(*it).second.info[20] = LF->GetWayTypeFromLong(nWayType, TRUE, nLoadType);
		(*it).second.info[21] = LF->GetRunTypeFromLong(nRunType, TRUE);
		(*it).second.info[22] = LF->GetCarTypeFromLong(nKDelivery, TRUE, nTruckType, strTon);
		(*it).second.info[23] = LF->GetPayTypeFromLong(nPayType, TRUE, nCreditCardType);	
		//(*it).second.info16] = nTransOrder == TRUE ? "탁송" : "";
		//(*it).second.info[16] = nTransOrder == TRUE ? LF->GetMyNumberFormat(nChargeTrans) : "";
		(*it).second.info[24] = LF->RemoveZero(LF->GetMyNumberFormat(nChargeTrans));
		(*it).second.info[25] = GetSecondCrossState(nRiderCompany == 0 ? nCompany : nRiderCompany ) ? 
			CString("ⓒ") + LF->RemoveZero(ltoa(nRNo, buffer, 10)) : LF->RemoveZero(ltoa(nRNo, buffer, 10));
		(*it).second.info[26] = strRName;
		(*it).second.info[27] = sWName;//LF->RemoveZero(ltoa(nWNo, buffer, 10));

		(*it).second.info[28] = (bHidePhone) ? "N/A" : LF->RemoveZero(LF->GetMyNumberFormat(nChargeBasic));
		(*it).second.info[29] = (bHidePhone) ? "N/A" : LF->RemoveZero(LF->GetMyNumberFormat(nChargeAdd));
		(*it).second.info[30] = (bHidePhone) ? "N/A" : LF->RemoveZero(LF->GetMyNumberFormat(nChargeDis));

		if(bHidePhone)
			strTemp = "N/A";
		else
		{
			long nTempCharge = nTotal;

			if(m_bAddTacksongCharge)
				nTempCharge += nChargeTrans;

			if(nCardOkAmt > 0)
				strTemp = (CString)LF->GetMyNumberFormat(ltoa(nTempCharge, buffer, 10)) + "/" + (CString)LF->GetMyNumberFormat(ltoa(nCardOkAmt, buffer, 10));
			else
				strTemp = LF->GetMyNumberFormat(ltoa(nTempCharge, buffer, 10));
		} 

		(*it).second.info[31] = strTemp;
		(*it).second.info[32] = LF->GetMyNumberFormat(ltoa(m_bAddTacksongDrivingCharge ? nChargeDriving + nChargeTrans : nChargeDriving, buffer, 10));
		(*it).second.info[33] = (nState > 10 && nState != 40) ? dt2.Format("%H:%M") : "-";
		(*it).second.info[34] = (nState > 29 && nState != 40) ? dt3.Format("%H:%M") : "-";
		(*it).second.info[35] = (nState > 30 && nState != 40) ? dt4.Format("%H:%M") : "-";
		(*it).second.info[36] = "";//배차경과o

		if(nState >= 35)
		{
			if(dt1.GetDay() == dtFinal.GetDay())
				(*it).second.info[37] = dtFinal.Format("%H:%M");
			else
				(*it).second.info[37] = dtFinal.Format("%m-%d %H:%M");
		}
		else
			(*it).second.info[37] = "-";

		(*it).second.info[38] = (bHidePhone) ? "N/A" : strEtc;
		(*it).second.info[39] = (bHidePhone) ? "N/A" : strManager;
		(*it).second.info[40] = (bHidePhone) ? "N/A" : strItemType;
		(*it).second.info[41] = (bHidePhone) ? "N/A" : m_cg.GetGroupData(nOGNo)->strGroupName;
		(*it).second.info[42] = (bHidePhone) ? "N/A" : m_cg.GetGroupData(nOGNo)->strDept;
		(*it).second.info[43] = nDNIS <= 0 ? "" : itoa(nDNIS, buffer, 10);
 
		
		if(nFinalDepositRate > 0)
			(*it).second.info[44] = CString(ltoa(nFinalDepositRate, buffer, 10)) + "%";
		else
			(*it).second.info[44] = "";

		//(*it).second.info[45] = GetRiderDeposit(nChargeDriving, nFinalRiderDeposit);
		(*it).second.info[45] = LF->GetMyNumberFormat(nFinalRiderDeposit);
		(*it).second.info[46] = (bHidePhone) ? "N/A" : strSDetail;
		(*it).second.info[47] = (bHidePhone) ? "N/A" : strDDetail;

		if(nCNo == nSCNo)
			strTemp = ""; //
		else if(nCNo == nDCNo)
			strTemp = "가져오기";
		else
			strTemp = "외부";

		(*it).second.info[48] = (bHidePhone) ? "N/A" : strTemp;
		(*it).second.info[49] = (bHidePhone) ? "N/A" : strOMemo;

		if(bHidePhone)
		{
			(*it).second.info[50] = "N/A";
			(*it).second.info[51] = "N/A";
		}
		else
		{
			if(bAsteriskPhone)			
			{
				(*it).second.info[50] = LF->GetTwoPhoneAsterisk(strSPhone, strSMobile);
				(*it).second.info[51] = LF->GetTwoPhoneAsterisk(strDPhone, strDMobile);
			}
			else
			{
				(*it).second.info[50] = LF->GetTwoPhone(strSPhone, strSMobile);
				(*it).second.info[51] = LF->GetTwoPhone(strDPhone, strDMobile);
			}
		}
		
		(*it).second.info[52] = bHidePhone ? "N/A" : LF->RemoveZero(nUseCount);

		CheckOfficeAllocateOnly(nRiderAllocate, (*it).second.bRiderOkOnlyMan, (*it).second.bOfficeOkOnlyMan);

		if(bHidePhone)
			(*it).second.info[53] = "N/A";
		else
		{
			if((*it).second.bRiderOkOnlyMan == TRUE)
				(*it).second.info[53] = "기사배차";
			else if((*it).second.bOfficeOkOnlyMan == TRUE)
				(*it).second.info[53] = "사무실직권배차";

			if(nOrderAllocType && 2 == 2)
				(*it).second.info[52] += "/자동배차";
		}
		(*it).second.info[54] = nConsignSumCharge >0 ? LF->GetMyNumberFormat(nConsignSumCharge) : ""; // 연계오더합계금액
		(*it).second.info[55] = ""; //virtualrecord에서 체인지
		(*it).second.info[56] = LF->GetMyNumberFormat(nDeposit); //virtualrecord에서 체인지
		(*it).second.info[57] = bHidePhone ? "N/A" : strOAddress;
		(*it).second.info[58] = bHidePhone ? "N/A" : strODetail;
		(*it).second.info[59] = bHidePhone ? "N/A" : strBCCardTranNumber;

		//strTemp.Format("%d.%dKm", nDistanceKM / 100, nDistanceKM % 100); 
		strTemp.Format("%.1fKm", nDistanceKM / 100.0); 
		(*it).second.info[60] = bHidePhone ? "N/A" : strTemp;

		(*it).second.info[61] = bHidePhone ? "N/A" : LF->GetRcpType(nRcpType, bInternet);
		(*it).second.info[62] = LF->GetStringFromLong(nChargeCompany, FALSE); 
		(*it).second.info[63] = dt0.Format("%m-%d %H:%M");
		(*it).second.info[64] = LF->GetMyNumberFormat(nChargeReturn);
		(*it).second.info[65] = bSentPickupSms2 == TRUE ? "ㅇ" : "";
		(*it).second.info[67] = bHidePhone ? "N/A" : strSAddress;
		(*it).second.info[68] = bHidePhone ? "N/A" : strDAddress;
		(*it).second.info[69] = bHidePhone ? "N/A" : LF->GetMyNumberFormat(nChargeRiderAuto);
		(*it).second.info[70] = bHidePhone ? "N/A" : LF->GetMyNumberFormat(nMileage);
		(*it).second.info[71] = bHidePhone ? "N/A" : LF->GetMyNumberFormat(nChargeRevision);


		(*it).second.nState = nState;
		(*it).second.nTNo = nTNo;
		(*it).second.strCName = strCName;
		(*it).second.strDName = strDName;
		(*it).second.nCompany = nCompany;
		(*it).second.nRiderCompany = nRiderCompany;
		(*it).second.dtRcp = dt1;

		(*it).second.nShareLevel = (nCompany == m_pBi->nCompanyCode || 
			nShareCode1 == m_pBi->nShareCode1) ? 1 : 2;

		(*it).second.bCross = GetSecondCrossState(nCompany);

		(*it).second.nRNo = nRNo;
		(*it).second.nWNo = nWNo;
		(*it).second.strEtc = strEtc;
		(*it).second.strStart = strStart;
		(*it).second.strDest = strDest;
		(*it).second.nCarType = nKDelivery;
		(*it).second.nShareCompany = nShareCompany;
		(*it).second.nCharge = nTotal;
		(*it).second.nWayType = nWayType;
		(*it).second.nRunType = nRunType;
		(*it).second.nPayType = nPayType;

		(*it).second.bTwoWay = nWayType; 
		(*it).second.dtLast = dtLast; 

		(*it).second.nStartPosX = nStartPosX;
		(*it).second.nStartPosY = nStartPosY;
		(*it).second.nDestPosX = nDestPosX;
		(*it).second.nDestPosY = nDestPosY;
		(*it).second.nStartRealDongID = nStartRealDongID;
		(*it).second.nDestRealDongID = nDestRealDongID;
		(*it).second.strOPhone = strOPhone;
		(*it).second.strSPhone = strSPhone;
		(*it).second.strDPhone = strDPhone;
		(*it).second.strOMobile = strOMobile;
		(*it).second.strSMobile = strSMobile;
		(*it).second.strDMobile = strDMobile;
		(*it).second.bInternet = bInternet;
		(*it).second.nDistanceKM = nDistanceKM;
		(*it).second.nCNo = nCNo;
		(*it).second.strSName = strSName;
		(*it).second.nSCNo = nSCNo;
		(*it).second.nDCNo = nDCNo;
		(*it).second.nReserveAfter = nReserveAfter;
		(*it).second.bScheduleOrder = bScheduleOrder;
		(*it).second.bShareOrder = bClientShare;
		(*it).second.nSignType = nSignType;
		(*it).second.strItemType = strItemType;
		(*it).second.strSAddress = strSAddress;
		(*it).second.strDAddress = strDAddress;
		(*it).second.strSDetail = strSDetail;
		(*it).second.strDDetail = strSDetail;
		(*it).second.nTransOrder = nTransOrder;
		(*it).second.bTodayOrder = bTodayOrder;
		(*it).second.nGNo = nOGNo;
		(*it).second.nShareCode1 = nShareCode1;
		(*it).second.nRiderShareCode1 = nRiderShareCode1;
		(*it).second.strRName = strRName;
		(*it).second.strWName = sWName;
		(*it).second.nChargeTrans = nChargeTrans;
		(*it).second.nDepositRate = nDeposit;
		(*it).second.nFinalDepositRate = nFinalDepositRate;
		(*it).second.bClientShare5 = bClientShare5;
		(*it).second.nTNoSet = nTNoSet;
		(*it).second.bMyOrder = bMyOrder;
		(*it).second.dt0 = dt0;
		(*it).second.nTruckType = nTruckType;
		(*it).second.strTon = strTon;
		(*it).second.nLoadType = nLoadType;
		(*it).second.nBillDraw = nBillDraw;
		(*it).second.nCreditCardType = nCreditCardType;
		(*it).second.nDNIS = nDNIS;
		(*it).second.nWCompany = nWCompany;
		(*it).second.nConsignTNo = nConsignTNo;
		(*it).second.sConsignDestSido = sConsignDestSido;
		(*it).second.nConsignWayID = nConsignWayID;
		(*it).second.nReserveAfter = nReserveAfter;
		(*it).second.dtReserve = dtReserve;
		(*it).second.nRiderAllocate = nRiderAllocate;
		(*it).second.nCardOkAmt = nCardOkAmt;
		(*it).second.nDaeriCode = nDaeriCode;
		(*it).second.nCTNo = nCTNo;
		(*it).second.nChargeDriving = nChargeDriving;
		(*it).second.nChargeCompany = nChargeCompany;
		(*it).second.dtDelayNotice = dtDelayNotice;
		(*it).second.bFoodOrder = bFoodOrder;		
		(*it).second.dtFoodComplete = dtFoodComplete;		
		(*it).second.bAutoWait = bAutoWait;		

		pRs.MoveNext();
	}

	if(m_bUseCardOkNumberAddColumn)
		RefreshListCardOkNumber();


	BOOL bUseFilter = FALSE, bAsc;
	int nSortCol, nDisplayRowCount;

	vr->SetParentSearch(TRUE);

	if(nType == RT_TODAY)
	{ 
		m_dtLastRefresh = parOutCurDate->GetDate();

		parReturnOperatorID->GetValue(nOperatorID);
		parnShareRcpCount->GetValue(m_nShareRcpCount);
		parShareAllocateCount->GetValue(m_nShareAllocateCount);
		parShareCompleteCount->GetValue(m_nShareCompleteCount);
		parShareCancelCount->GetValue(m_nShareCancelCount);
		parShareEtcCount->GetValue(m_nShareEtcCount);
		parShareAllCount->GetValue(m_nShareAllCount);
		parShareBalance->GetValue(m_nShareBalance);
		parSmsBalance->GetValue(m_nSmsBalance);
		
		long nRCompany = 0, nRNo = 0;

		if(strRecvCID.GetLength() > 0)
		{
			if(pBI == NULL)
				pBI = m_pBi;
			nOperatorID = GetRiderAndInsertOperatorLog(pBI->nCompanyCode, strRecvCID, nRCompany, nRNo);
		}

		if(nRCompany > 0 && nRNo > 0) //기사전화
		{
			nDisplayRowCount = CheckRiderFilter(nRCompany, nRNo, &bUseFilter, order, index, filter);
			if(bUseFilter)
			{
				m_xList.ShowRiderInfo(TRUE);
				m_bRefreshWithCID = TRUE;
			}

			LU->ShowRiderInfoDlg(nRCompany, nRNo, -1, -1, strCallBranch, -1, -1, strRecvCID);
			m_strPreRecvRiderCID = strRecvCID;
			m_bCreateRcpDlg = FALSE; 

			if (strRecvCID.GetLength() > 0)
				m_pCTIForm->QueueWorkingMode();
		}
		else if(strRecvCID.GetLength() > 0) //고객전화
		{
			nDisplayRowCount = CheckCustomerFilter(strRecvCID, &bUseFilter, order, index, filter);
			if(bUseFilter)
			{
				ShowCustomerInfoInList(bUseFilter, strRecvCID);
				m_bRefreshWithCID = TRUE;
			}
			m_bCreateRcpDlg = TRUE;
		}
		else
		{
			if(LF->POWER_CHECK(2007, "카운트 표시"))
				UpdateOrderCount();
		}

		//고객/기사전화 검색시 데이터가 없거나, 단순검색인 경우에 기존 검색조건으로 검색한다.
		if(!bUseFilter)
		{
			if(nSearchCustomerID > 0)
				strSearchData.Format("%d", nSearchCustomerID);

			nDisplayRowCount = CheckFilter(&bUseFilter, order, index, filter);
		}
		vr->SetUseFilter(bUseFilter);
		m_xList.GetSortCol(&nSortCol, &bAsc);
		vr->SortRecord(nSortCol, STRING_SORT, bAsc, m_bStateSecondSort);
		OnCbnSelchangeRefreshCombo();	//자동갱신 타이머 세팅

		if(m_bGetCustomerMemo)
			ShowCustomerInfoToMainList();
	}
	else if(nType == RT_PREDATE)
	{
		vr->SetParentSearch(FALSE);

		if(bInsertTodayOrder)
			nDisplayRowCount = CheckFilter(&bUseFilter, order, index, filter);
		else
			nDisplayRowCount = CheckFilterPredateDedicated(&bUseFilter, order, index, filter);

		vr->SetUseFilter(bUseFilter);
		m_xList.GetSortCol(&nSortCol, &bAsc);
		vr->SortRecord(nSortCol, STRING_SORT, bAsc, m_bStateSecondSort);

		if(LF->POWER_CHECK(2007, "카운트 표시"))
			UpdateOrderCount();
	}
	else if(nType == RT_TODAY_SHARE)
	{
		parReturnOperatorID->GetValue(nOperatorID);

		parnShareRcpCount->GetValue(m_nShareRcpCount);
		parShareAllocateCount->GetValue(m_nShareAllocateCount);
		parShareCompleteCount->GetValue(m_nShareCompleteCount);
		parShareCancelCount->GetValue(m_nShareCancelCount);
		parShareEtcCount->GetValue(m_nShareEtcCount);
		parShareAllCount->GetValue(m_nShareAllCount);

		CString strSearchData;
		if(nSearchCustomerID > 0)
			strSearchData.Format("%d", nSearchCustomerID);

		nDisplayRowCount = CheckFilter(&bUseFilter, order, index, filter);

		vr->SetUseFilter(bUseFilter);
		m_xList.GetSortCol(&nSortCol, &bAsc);
		vr->SortRecord(nSortCol, STRING_SORT, bAsc, m_bStateSecondSort);
		OnCbnSelchangeRefreshCombo();	//자동갱신 타이머 세팅
	}

	vector<UINT> vecTNo; 

	if(nType == RT_TODAY)
		SaveReportEnsureVisible(vecTNo, bFromOrderChange);

	m_xList.GetRecords()->RemoveAll();
	vr->InternalAddRef();
	m_xList.SetVirtualMode(vr, nDisplayRowCount);
	//m_xList.Populate();
	m_xList.Populate();

	//3번연속으로 동일한 nTNo가 검출되면 최하위 아이템을 자동 선택하도록 함
	static int nPreLastSelItemNo;
	static int nLastSelHitCount;
	if(nPreLastSelItemNo == GetLastSelItemNo()) {
		nLastSelHitCount++;
	}
	else {
		nLastSelHitCount = 0;
		nPreLastSelItemNo = GetLastSelItemNo();
	}

	//시간순으로 정렬되어 있는 경우만, 최하위로 가도록 함

	/*
	if(m_bScrollToTop == TRUE && bScrollTopOnce == TRUE)//최상위로 스크롤
	{ 
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(0);  
		m_xList.EnsureVisible(pRow); 


		int nRow = m_vrCur->GetItemRowFromTNo(GetLastSelItemNo());
		CXTPGridRow *pSelRow = pRows->GetAt(nRow);
		//m_xList.SetFocusedRow(pSelRow);
		//m_xList.GetSelectedRows()->Select(pSelRow);
	}
	else if(!m_bStateSecondSort && nLastSelHitCount > 4 && bAsc &&
		(nSortCol == RCP_TNO_COL || nSortCol == RCP_TIME_COL || nSortCol == RCP_TIME_COL + 1))
	{
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(bAsc ? (pRows->GetCount() - 1) : 0);
		m_xList.EnsureVisible(pRow);
		m_xList.GetSelectedRows()->Select(pRow);
		m_xList.SetFocusedRow(pRow);
	}
	else
	{
		int nRow = m_vrCur->GetItemRowFromTNo(GetLastSelItemNo());
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
		m_xList.EnsureVisible(pRow);
		pRow = pRows->GetAt(nRow);
		m_xList.GetSelectedRows()->Select(pRow);
		m_xList.SetFocusedRow(pRow);
	}
	*/

	/*
	m_xList.GetRecords()->RemoveAll();
	vr->InternalAddRef();
	m_xList.SetVirtualMode(vr, nDisplayRowCount);
	m_xList.Populate();
	*/

	if(nType == RT_TODAY)
		LoadReportEnsureVisible(vecTNo, nSortCol, bAsc, bFromOrderChange);


	LF->StatusText(0, LF->FormatString("%s개의 데이터가 검색되었습니다.",
		LF->POWER_CHECK(2007, "카운트 표시") ? ltoa(m_xList.GetRecords()->GetCount(), buffer, 10) : "N/A"));


	if(LU->GetAllocateBoardDlg())
		LU->GetAllocateBoardDlg()->RefreshList();

	if(LU->GetRiderMapDlg())
		LU->GetRiderMapDlg()->RefreshOrderState(); 


	if(m_bFirstRefresh)
	{

		//m_pEmptyCarPane = LU->m_pEmptyCarPane;
		//m_pDelayOrderPane = LU->m_pDelayOrderPane;
		//m_pAllocatePane = LU->GetAllocatePane();

		//### //by mksong (2010-08-16 오전 12:37)
		// 아래의 다이얼로그가 나중에 초기화됨
		//		m_pEmptyCarPane->RefreshList();
		//		m_pDelayOrderPane->RefreshList();
		//		LU->m_pDelayOrderPane->m_pEmptyCarPane = LU->m_pEmptyCarPane;

		//###멤버가 존재하지 않는데, 확인이 필요함, //by mksong (2010-08-15 오후 11:13)
		//		LU->m_pEmptyCarPane->m_pDelayOrderPane = LU->m_pDelayOrderPane;

		m_bFirstRefresh = FALSE;
	}

	if(LU->m_pwndPane3)
	{
		if(!LU->m_pwndPane3->IsHidden())
		//if(!LU->m_pwndPane3->IsClosed())
		{
			LU->GetDelayOrderPane()->RefreshList();
		}
	}
	

	//if(!LU->m_pwndPane2->IsHidden())
	//{
	//	LU->m_pConnListPane->RefreshList(FALSE);
	//}

	pRs.Close();
	m_nRefreshType = nType;

	
	if(m_nRefreshTNoForStateChange > ZERO)
	{
		SelectRowFromTNo(m_nRefreshTNoForStateChange);
		OnBnClickedEditBtn();
		m_nRefreshTNoForStateChange = MINUS_ONE;
	}
		
	if(m_bRefreshWithCID)
		RefreshMapForm(GetLastTimeOrderInVisibleRows(), TRUE);
	else if(m_bAutoChangeMapForm)
	{
		m_bAutoChangeMapForm = FALSE;
		m_wndTabControl.SetCurSel(RCPPAGE_CTI_FORM);
	}

	//Invalidate(TRUE);  //by mksong (2011-01-09 오후 8:14),  이건또 뭔감? 화면껌벅임으로 삭제함

	return nOperatorID;
} 

CString CRcpView::GetRiderDeposit(long nChargeDriving, long nRiderDeposit)
{
	float fTemp = 0;
	
	if(nRiderDeposit != 0)
		fTemp = (float) nRiderDeposit / (float)nChargeDriving * 100;

	if(fTemp == 0)
		return"";

	CString strTemp = "";
	strTemp.Format("%d%%", (int)fTemp);
	return strTemp;
}

BOOL CRcpView::IsLeftTodayOrder()
{
	COleDateTime dtTo;
	m_ToDT.GetTime(dtTo);

	//Base time 구하기
	m_ei.dtTodayBound.SetDateTime(m_ei.dtServerTime.GetYear(),
		m_ei.dtServerTime.GetMonth(),
		m_ei.dtServerTime.GetDay(),
		7, 0, 0);

	if(m_ei.dtServerTime.GetHour() < BASE_HOUR)
		m_ei.dtTodayBound = m_ei.dtTodayBound;

	if(dtTo > m_ei.dtTodayBound)
		return TRUE;
	else 
		return FALSE;
}

void CRcpView::InsertTodayOrder(OrderRecordList &order, OrderIndex &index, BOOL &bInsertTodayOrder)
{
	m_ei.dtTodayBound.SetDateTime(m_ei.dtServerTime.GetYear(),
		m_ei.dtServerTime.GetMonth(),
		m_ei.dtServerTime.GetDay(),
		0, 0, 0);

	if(m_ei.dtServerTime.GetHour() < BASE_HOUR)
		m_ei.dtTodayBound = m_ei.dtTodayBound - COleDateTimeSpan(1, 0, 0, 0);

	OrderRecordList temp;
	temp.insert(order.begin(), order.end());

	OrderRecordList::iterator it;
	for(it = m_vrOrder->GetOrderRecordList().begin(); it != m_vrOrder->GetOrderRecordList().end(); it++)
	{
		if(it->second.dtRcp >= m_ei.dtTodayBound)
		{
			order.insert(OrderRecordList::value_type(it->first, it->second));
			index.insert(OrderIndex::value_type(index.size(), it->first));
			bInsertTodayOrder = TRUE;
		}
	}
}

void CRcpView::ShowCustomerInfoInList(BOOL bUseFilter, CString strRecvCID)
{
	m_xList.m_bConfirmCall = bUseFilter;
	m_xList.m_strRecvCID = strRecvCID;
	m_xList.m_strCurBranch = m_pBi->strBranchName; //#### + "/" + m_pBi->strPhone;
	m_xList.ShowCustomerInfo(TRUE);
}	

void CRcpView::UpdateOrderCount()
{
	long nWaitCount = 0, nRcpCount = 0, nAllocCount = 0, nOnlyManCount = 0, nReserverdCount = 0;
	long nFinishCount = 0, nCancelCount = 0, nEtcCount = 0, nPickupCount = 0;
	long nMyAllCount = 0, nMyFinishCount = 0;
	long nRepicientCount = 0, nGiveCount = 0, nTakeCount = 0;
	OrderRecordList &order = m_vrCur->GetOrderRecordList();
	OrderRecordList::iterator it;

	m_nTodayIncome = 0;

	long nMyComleteCount = 0;

	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	m_ToDT.GetTime(dtTo);


	for(it = order.begin(); it != order.end(); it++)
	{
		if(!LF->GetCurBranchInfo()->bIntegrated &&
			LF->GetCurBranchInfo()->nCompanyCode != it->second.nCompany &&
			LF->GetCurBranchInfo()->nCompanyCode != it->second.nRiderCompany)
			continue;

		if(!m_ci.IsChildCompany(it->second.nCompany) &&
			!m_ci.IsChildCompany(it->second.nRiderCompany))
			continue;

		if (it->second.dtRcp.Format("%Y-%m-%d").IsEmpty())
			continue;

		if(it->second.dtRcp < dtFrom || it->second.dtRcp > dtTo)
			continue;

		switch(it->second.nState)
		{
		case 8:
		case 2:
			nWaitCount++;
			break;

		case 9:
			nReserverdCount++;
			break;

		case 10:
			{
				if(!LF->GetCurBranchInfo()->bIntegrated &&	LF->GetCurBranchInfo()->nCompanyCode == it->second.nCompany )
				{
					nRcpCount++;
					break;
				}
				else
				{
					nRcpCount++;
					break;
				}
			}		

			break;

		case 11:
			nOnlyManCount++;
			break;
		case 30:
			nAllocCount++;
			break;

		case 31:
			nPickupCount++;
			break;

		case 35:
			nFinishCount++;
			break;

		case 40:
			nCancelCount++;
			break;

		default:
			nEtcCount++;
			break;
		}

		if(m_ci.IsChildCompany(it->second.nCompany))
		{
			nMyAllCount++;		//자사콜수

			if(it->second.nState >= 30 && it->second.nState <= 35)
			{
				nMyFinishCount++;	//자사콜 완료콜수

				if(it->second.nState == 35)
				{
					m_nTodayIncome += it->second.nChargeDriving;

					if(it->second.bTodayOrder)
						nMyComleteCount++;
				}

				if(!m_ci.IsChildCompany(it->second.nRiderCompany))
				{
					nGiveCount++;	//넘긴콜수
				}
			}

			if(it->second.nWCompany == m_ui.nCompany && it->second.nWNo == m_ui.nWNo)
			{
				nRepicientCount++;
			}
		}
		else
		{
			nTakeCount++;
		}
	}

	LU->SetTodayCompleteCount(nMyComleteCount);

	if(m_btnStateWait.GetSafeHwnd() == NULL)
		return;


	if(LF->POWER_CHECK(2007, "카운트 표시"))
	{
		CString s;  

		long nTotalCount = nWaitCount + nRcpCount + nOnlyManCount + nAllocCount + nPickupCount + nFinishCount + nCancelCount + nEtcCount;

		const char szTemp[] =  

			"<Hyperlink Tag='stateALL' ToolTip='전체오더를 검색합니다' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state10' ToolTip='접수오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state8' ToolTip='대기오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state11' ToolTip='개별오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state30' ToolTip='배차오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state35' ToolTip='완료오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\

			"<Hyperlink Tag='state1135' ToolTip='개별,배차,완료오더만 검색합니다' Background='%s' Foreground='%s' FontWeight='Bold'>(</Hyperlink>"\
			"<Hyperlink Tag='state1135' ToolTip='개별,배차,완료오더만 검색합니다' Background='%s' Foreground='%s' FontWeight='Bold'>%s</Hyperlink>"\
			"<Hyperlink Tag='state1135' ToolTip='개별,배차,완료오더만 검색합니다' Background='%s' Foreground='%s' FontWeight='Bold'>)</Hyperlink> "\

			"<Hyperlink Tag='state40' ToolTip='취소오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> "\
			"<Hyperlink Tag='state9' ToolTip='예약오더만 검색합니다' Background='%s' Foreground='%s'>%s</Hyperlink> ";
			//"<Hyperlink Tag='state60' ToolTip='문의오더만 검색합니다' Foreground='%s' Foreground='%s'>%s</Hyperlink> ";


		m_strInfoCount.Format(szTemp, 
			"Black", "전체:" + LF->GetMyNumberFormat(nTotalCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack1), GetColorTo0x(CVirtualRecord::m_crStateText1), "접수:" + LF->GetMyNumberFormat(nRcpCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack2), GetColorTo0x(CVirtualRecord::m_crStateText2), "대기:" + LF->GetMyNumberFormat(nWaitCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack4), GetColorTo0x(CVirtualRecord::m_crStateText4), "개별:" + LF->GetMyNumberFormat(nOnlyManCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack5), GetColorTo0x(CVirtualRecord::m_crStateText5), "배차:" + LF->GetMyNumberFormat(nAllocCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack7), GetColorTo0x(CVirtualRecord::m_crStateText7), "완료:" + LF->GetMyNumberFormat(nFinishCount),

			GetColorTo0x(CVirtualRecord::m_crStateBack7), GetColorTo0x(CVirtualRecord::m_crStateText7),
			GetColorTo0x(CVirtualRecord::m_crStateBack7), GetColorTo0x(CVirtualRecord::m_crStateText7), LF->GetMyNumberFormat(nOnlyManCount + nAllocCount + nFinishCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack7), GetColorTo0x(CVirtualRecord::m_crStateText7),

			GetColorTo0x(CVirtualRecord::m_crStateBack8), GetColorTo0x(CVirtualRecord::m_crStateText8), "취소:" + LF->GetMyNumberFormat(nCancelCount),
			GetColorTo0x(CVirtualRecord::m_crStateBack3), GetColorTo0x(CVirtualRecord::m_crStateText3), "예약:" + LF->GetMyNumberFormat(nReserverdCount));
			//GetColorTo0x(CVirtualRecord::m_crStateBack9), GetColorTo0x(CVirtualRecord::m_crStateText9), "문의:" + LF->GetMyNumberFormat(nInqueryCount));

		/*
		CString strTemp;
		strTemp.Format("대기 %d", nWaitCount);
		m_btnStateWait.SetWindowText(strTemp);
		strTemp.Format("예약 %d", nReserverdCount);
		m_btnStateReserved.SetWindowText(strTemp);
		strTemp.Format("접수 %d", nRcpCount);
		m_btnStateRcp.SetWindowText(strTemp);
		strTemp.Format("개별 %d", nOnlyManCount);
		m_btnStateOnlyMan.SetWindowText(strTemp);
		strTemp.Format("배차 %d", nAllocCount);
		m_btnStateAlloc.SetWindowText(strTemp);
		strTemp.Format("픽업 %d", nPickupCount);
		m_btnStatePickup.SetWindowText(strTemp);
		strTemp.Format("완료 %d", nFinishCount);
		m_btnStateFinish.SetWindowText(strTemp);
		strTemp.Format("취소 %d", nCancelCount);
		m_btnStateCancel.SetWindowText(strTemp);
		strTemp.Format("기타 %d", nEtcCount);
		m_btnStateEtc.SetWindowText(strTemp);
		strTemp.Format("전체 %d", nWaitCount + nRcpCount + nOnlyManCount + nAllocCount + 
			nPickupCount + nFinishCount + nCancelCount + nEtcCount);
		m_btnStateAll.SetWindowText(strTemp);
		*/

	}


	//CString strInfo;
	//strInfo = CString("본인접수:") + ltoa(nRepicientCount, buffer, 10) + "건";

	//if(LF->POWER_CHECK(2007, "카운트 표시"))
	//{
		DisplaySearchInfo();
		/*
		int nMyAllCount = nWaitCount + nRcpCount + nOnlyManCount + nAllocCount + nFinishCount + nCancelCount;
		strInfo += CString("  자사: ") + ltoa(nMyAllCount, buffer, 10) + "건";
		strInfo += CString("  자사완료: ") + ltoa(nMyFinishCount, buffer, 10) + "건(취소" + ltoa(100 * nCancelCount / (max(1, nMyFinishCount+nCancelCount)), buffer, 10) + "%)"; 
		strInfo += CString("  넘긴콜: ") + ltoa(nGiveCount, buffer, 10) + "건(자사콜" + ltoa(100 * nGiveCount / (max(1, nMyFinishCount)), buffer, 10) + "%)";
		strInfo += CString("  받은콜: ") + ltoa(nTakeCount, buffer, 10) + "건(총콜" + ltoa(100 * nTakeCount / (max(1, nMyAllCount + nTakeCount)), buffer, 10) + "%)";
		strInfo += CString("  넘김-받음: ") + ltoa(nGiveCount - nTakeCount, buffer, 10) + "건";

		m_strCountInfo = strInfo;
		DisplayInfo1Stc(DISPLAY_TYPE_STATE_COUNT);
		*/
	//}
}



void CRcpView::RefreshFilterOnly(BOOL bStateCheck)
{
	UpdateData(TRUE);

	if(bStateCheck == TRUE)
		m_bIsSaveState = FALSE;

	BOOL bUseFilter, bAsc;
	int nSortCol, nDisplayRowCount;
	CString strSearchData;
	char buffer[20];

	if(m_vrCur == m_vrPreDate || !IsTodaySearch())
	{
		LF->StatusText(0, "이전오더 검색인 경우에 검색버튼을 누르셔야 정상적으로 갱신됩니다.");
		return;
	}

	OrderRecordList &order = m_vrOrder->GetOrderRecordList();
	OrderIndex &index = m_vrOrder->GetOrderIndex();
	OrderIndex &filter = m_vrOrder->GetFilterIndex();

	vector<UINT> vecTNo;
	SaveReportEnsureVisible(vecTNo, FALSE);

	nDisplayRowCount = CheckFilter(&bUseFilter, order, index, filter);
	m_vrOrder->SetUseFilter(bUseFilter);
	m_xList.GetSortCol(&nSortCol, &bAsc);
	m_vrOrder->SortRecord(nSortCol, STRING_SORT, bAsc, m_bStateSecondSort);
	m_xList.GetRecords()->RemoveAll();
	m_vrOrder->InternalAddRef();
	m_xList.SetVirtualMode(m_vrOrder, nDisplayRowCount);
	m_xList.Populate();
	
	//3번연속으로 동일한 nTNo가 검출되면 최하위 아이템을 자동 선택하도록 함
	static int nPreLastSelItemNo;
	static int nLastSelHitCount;
	if(nPreLastSelItemNo == GetLastSelItemNo()) {
		nLastSelHitCount++;
	}
	else {
		nLastSelHitCount = 0;
		nPreLastSelItemNo = GetLastSelItemNo();
	}

	LoadReportEnsureVisible(vecTNo, nSortCol, bAsc, FALSE);

	/*
	//시간순으로 정렬되어 있는 경우만, 최하위로 가도록 함
	if(!m_bStateSecondSort && nLastSelHitCount > 4 && bAsc &&
		(nSortCol == RCP_TNO_COL || nSortCol == RCP_TIME_COL || nSortCol == RCP_TIME_COL + 1))
	{
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(bAsc ? (pRows->GetCount() - 1) : 0);
		m_xList.EnsureVisible(pRow);
		m_xList.GetSelectedRows()->Select(pRow);
	}
	else
	{
		int nRow = m_vrCur->GetItemRowFromTNo(GetLastSelItemNo());
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
		m_xList.EnsureVisible(pRow);
		pRow = pRows->GetAt(nRow);
		m_xList.GetSelectedRows()->Select(pRow);
	}
	*/

	LF->StatusText(0, LF->FormatString("%s개의 데이터가 검색되었습니다.",
		LF->POWER_CHECK(2007, "카운트 표시") ? ltoa(m_xList.GetRecords()->GetCount(), buffer, 10) : "N/A"));

}


long CRcpView::CheckFilter(BOOL *bUseFilter, OrderRecordList &order, OrderIndex &index, OrderIndex &filter)
{
	BOOL bRcpCheck1 = m_btnStateRcp.GetCheck();

	UpdateData(TRUE); 

	BOOL bRcpCheck2 = m_btnStateRcp.GetCheck();

	BOOL bHideCompleteOrder = !LF->POWER_CHECK(2005, "완료된 오더 보이기");
	BOOL bHideExpiredOrder = !LF->POWER_CHECK(2006, "1시간 지난오더 보기");

	filter.clear();
	*bUseFilter = TRUE;

	BOOL bStartValidRegion = CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionStartDongID);
	BOOL bDestValidRegion = CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionDestDongID);

	if(m_bStateSecondSort && m_nReserveShowCount > 0)
		m_vrCur->MakeReserveOrderSortNumber();

	OrderIndex::iterator it;
	OrderRecordList::iterator itOrder;

	CString strSearchCNo = "";
	CString strSearchMemoCNo = "";

	if(atoi(m_strShCustomerID) > ZERO &&
		m_strShPreCustomerID != m_strShCustomerID)
	{
		strSearchCNo = GetSearchCustomerID();	
	}

	if(m_strShCustomerMemo.GetLength() > THREE &&
		LF->IsKoreaWord(m_strShCustomerMemo) == TRUE &&
		m_strShPreCustomerMemo != m_strShCustomerMemo)
	{ 
		strSearchMemoCNo = GetSearchCustomerMemo();	
	}

	m_strShPreCustomerID = m_strShCustomerID;
	m_strShPreCustomerMemo = m_strShCustomerMemo;

	BOOL bESOk= IsCheckEditBox();
	BOOL bCSOk = IsCheckCheckBox();

	BOOL bApplySupport = FALSE;

	BOOL bRcpCheck3 = m_btnStateRcp.GetCheck();

	if(m_bIgnoreCheckState == TRUE)
	{
		bApplySupport = TRUE;

		if(LF->IsThisCompany("엔콜") || m_ci.m_nCompanyCode < 100)
		{
			if(m_strShStart.IsEmpty() == FALSE ||
				m_strShDest.IsEmpty() == FALSE)
			{
				bApplySupport = FALSE;
			}
		}
	}

	BOOL bRcpCheck4 = m_btnStateRcp.GetCheck();

	if(bApplySupport)
	{
		if(bESOk == TRUE)
		{
			if(m_bIsSaveState == FALSE)
				SaveStateRegForCheckFilter();
		}
		else
		{
			if(m_bIsSaveState == TRUE)
				LoadStateRegForCheckFilter();
		}
	}

	BOOL bRcpCheck5 = m_btnStateRcp.GetCheck();

	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	m_ToDT.GetTime(dtTo);

	BOOL bAllCheck = m_btnStateAll.GetCheck();
	BOOL bRcpCheck = m_btnStateRcp.GetCheck();
	BOOL bWaitCheck = m_btnStateWait.GetCheck();
	BOOL bReservedCheck = m_btnStateReserved.GetCheck();
	BOOL bOnlyManCheck = m_btnStateOnlyMan.GetCheck();
	BOOL bAllocCheck = m_btnStateAlloc.GetCheck();
	BOOL bFinishCheck = m_btnStateFinish.GetCheck();
	BOOL bCancelCheck = m_btnStateCancel.GetCheck();
	BOOL bPickupCheck = m_btnStatePickup.GetCheck();
	BOOL bEtcCheck = m_btnStateEtc.GetCheck();

	BOOL bShowReserveOrder = AfxGetApp()->GetProfileInt("RcpPage", "ShowReserveOrderDay", 0);

	for(it = index.begin(); it != index.end(); it++)
	{	
		BOOL bFilter = FALSE; 

		{
			itOrder = order.find((*it).second);
			if(itOrder == order.end())
				continue;
		} 

		if(bAllCheck == FALSE &&
			bRcpCheck == FALSE &&
			bWaitCheck == FALSE &&
			bOnlyManCheck == FALSE &&
			bAllocCheck == FALSE &&
			bFinishCheck == FALSE &&
			bCancelCheck == FALSE &&
			bPickupCheck == FALSE &&
			bEtcCheck == FALSE && 
			bReservedCheck == TRUE &&
			itOrder->second.nState == STATE_RESERVED)
		{
			filter.insert(OrderIndex::value_type((long)filter.size(), (*it).first));
			continue;
		}
 
		BOOL bMyOrder = m_ci.IsChildCompany(itOrder->second.nCompany);

		/*  --아래의 if문을 해당주석으로 바꿔야함 choi test 예약오더 나오기
		if(itOrder->second.nState == STATE_RESERVED)
		{
			if(itOrder->second.dtRcp < dtFrom || itOrder->second.dtRcp > dtTo)
			{
				bFilter = TRUE;
				continue;
			}
		}
		else
		{
			if((itOrder->second.dtRcp < dtFrom || itOrder->second.dtRcp > dtTo) &&
				(itOrder->second.dt0 < dtFrom || itOrder->second.dt0 > dtTo) && itOrder->second.nState == STATE_RESERVED)
			{
				bFilter = TRUE;
				continue;
			}
		}
		*/

		if (itOrder->second.dtRcp.Format("%Y-%m-%d").IsEmpty())
			continue;
		
		if(bShowReserveOrder == FALSE)
		{
			if((itOrder->second.dtRcp < dtFrom || itOrder->second.dtRcp > dtTo) &&
				(itOrder->second.dt0 < dtFrom || itOrder->second.dt0 > dtTo) && itOrder->second.nState == STATE_RESERVED)
			{
				bFilter = TRUE;
				continue;
			}
		}
		
		if(bHideExpiredOrder)
		{
			if(itOrder->second.dtRcp + COleDateTimeSpan(0, 1, 0, 0) < m_dtLastRefresh)
			{
				bFilter = TRUE;
				continue;
			}
		}

		if(!m_bShareOrderRefresh && !m_pBi->bIntegrated)
		{
			if(m_pBi->nCompanyCode != itOrder->second.nCompany &&
				m_pBi->nCompanyCode != itOrder->second.nRiderCompany)
			{
				bFilter = TRUE;
				continue;
			}
		}


		bFilter = CheckFilterSubState(&itOrder->second, bHideCompleteOrder, 
						bAllCheck, bRcpCheck, bWaitCheck, bReservedCheck, bOnlyManCheck, bAllocCheck, 
						bFinishCheck, bCancelCheck, bPickupCheck, bEtcCheck);

		if(bFilter == TRUE)
			continue;

		if(bCSOk == TRUE) //체크 항목만 검색
		{
			bFilter = CheckFilterSubCheckBox(&itOrder->second);

			if(bFilter == TRUE)
				continue;			
		}

		if(bESOk == TRUE) //에디트 항목만 검색
		{
			bFilter = CheckFilterSubEditBox(&itOrder->second, strSearchCNo, strSearchMemoCNo);

			if(bFilter == TRUE)
				continue;			
		}

		/*
		int nStartDongID = itOrder->second.nStartRealDongID;
		int nDestDongID = itOrder->second.nDestRealDongID;

		if(bStartValidRegion && !CRegionSelectDlg::IsSelectedRegion(nStartDongID, m_nSelectedRegionStartDongID))
		{
			bFilter = TRUE;
			continue;
		}

		if(bDestValidRegion && !CRegionSelectDlg::IsSelectedRegion(nDestDongID, m_nSelectedRegionDestDongID))
		{
			bFilter = TRUE;
			continue;
		}
		*/
		
		if(!bFilter || m_nOnceSelectedTNo == itOrder->second.nTNo)
		{
			filter.insert(OrderIndex::value_type((long)filter.size(), (*it).first));
		}
	}

	if(filter.size() == index.size())
		*bUseFilter = FALSE;

	m_nOnceSelectedTNo = 0;
	return (long)filter.size();
}



long CRcpView::CheckCustomerFilter(CString &strData, BOOL *bUseFilter, 
								   OrderRecordList &order, OrderIndex &index, OrderIndex &filter)
{
	filter.clear();
	*bUseFilter = TRUE;

	OrderIndex::iterator it;

	for(it = index.begin(); it != index.end(); it++)
	{	
		BOOL bFilter = FALSE;

		if(!((CString(order[(*it).second].strOPhone.c_str()).Find(strData) >= 0) ||
			(CString(order[(*it).second].strSPhone.c_str()).Find(strData) >= 0) ||
			(CString(order[(*it).second].strDPhone.c_str()).Find(strData) >= 0) ||
			(CString(order[(*it).second].strOMobile.c_str()).Find(strData) >= 0) ||
			(CString(order[(*it).second].strSMobile.c_str()).Find(strData) >= 0) ||
			(CString(order[(*it).second].strDMobile.c_str()).Find(strData) >= 0)
			))
		{
			bFilter = TRUE;
		}

		if(!bFilter)
		{
			filter.insert(OrderIndex::value_type((long)filter.size(), (*it).first));
		}

	}

	if(filter.size() == index.size() ||
		filter.size() == 0)
		*bUseFilter = FALSE;

	return (long)filter.size();
}


long CRcpView::CheckRiderFilter(long nRCompany, long nRNo, 
								BOOL *bUseFilter, OrderRecordList &order, 
								OrderIndex &index, OrderIndex &filter)
{
	filter.clear();
	*bUseFilter = TRUE;

	OrderIndex::iterator it;

	for(it = index.begin(); it != index.end(); it++)
	{	
		BOOL bFilter = FALSE;

		if(!(order[(*it).second].nRiderCompany == nRCompany &&
			order[(*it).second].nRNo == nRNo))
		{
			bFilter = TRUE;
		}

		if(!bFilter)
		{
			filter.insert(OrderIndex::value_type((long)filter.size(), (*it).first));
		}
	}

	if(filter.size() == index.size() ||
		filter.size() == 0)
		*bUseFilter = FALSE;

	return (long)filter.size();
}



long CRcpView::CheckFilterPredateDedicated(BOOL *bUseFilter, OrderRecordList &order, OrderIndex &index, OrderIndex &filter)
{
	filter.clear();
	*bUseFilter = TRUE;
	OrderIndex::iterator it;

	BOOL bStartValidRegion = CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionStartDongID) ;
	BOOL bDestValidRegion = CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionDestDongID);


	if(!(m_pBi->bUseNewRegion && 
	(CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionStartDongID) ||
	CRegionSelectDlg::IsValidRegionArray(m_nSelectedRegionDestDongID))))
	{
	*bUseFilter = FALSE;
	return index.size();
	}


	for(it = index.begin(); it != index.end(); it++)
	{	
		BOOL bFilter = FALSE;

		if(m_pBi->bUseNewRegion && (bStartValidRegion || bDestValidRegion))
		{
			int nStartDongID = order[(*it).second].nStartRealDongID;
			int nDestDongID = order[(*it).second].nDestRealDongID;

			if(bStartValidRegion && !CRegionSelectDlg::IsSelectedRegion(nStartDongID, m_nSelectedRegionStartDongID))
			{
				bFilter = TRUE;
			}
			else if(bDestValidRegion && !CRegionSelectDlg::IsSelectedRegion(nDestDongID, m_nSelectedRegionDestDongID))
			{
				bFilter = TRUE;
			}
		}

	
		if(!bFilter)
		{
			filter.insert(OrderIndex::value_type((long)filter.size(), (*it).first));
		}

	}

	if(filter.size() == index.size())
		*bUseFilter = FALSE;

	return (long)filter.size();
}

void CRcpView::MakeDistinctShareCodeMap()
{
	for(int n = 0; n < m_ba.GetCount(); n++)
	{
		CBranchInfo *pBi = m_ba.GetAt(n);
		if(pBi->nShareCode1 > 0)
		{
			m_mapDistinctShareCode[pBi->nShareCode1] = pBi->nShareCode1;
		}
	}

	long nCount = 1;
	DISTINCT_SHARE_CODE_MAP::iterator it;
	for(it = m_mapDistinctShareCode.begin(); it != m_mapDistinctShareCode.end(); it++)
	{
		g_bana_log->Print("DISCINTC SHARE CODE %d = %d\n", nCount++, it->second);
	}
}

void CRcpView::ShowCustomerInfoToMainList()
{
	return;

	if(COleDateTime::GetCurrentTime() - m_dtLastGetCustomerInfo <= COleDateTimeSpan(0, 0, 0, 30))
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_info_for_dordertoday");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_ba.GetCount() > 2);
	CMkParameter *parOutCurDate = pCmd.AddParameter(typeDate, typeInputOutput, sizeof(COleDateTime), m_dtLastGetCustomerInfo);

	if(!pRs.Execute(&pCmd))
		return;

	long nTNo,nID;
	CString strMemo;
	parOutCurDate->GetValue(m_dtLastGetCustomerInfo);

	OrderRecordList &order = m_vrOrder->GetOrderRecordList();
	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("nID", nID);

		OrderRecordList::iterator it = order.find(nTNo);

		if(it != order.end())
		{	
			(*it).second.info[CUSTOMER_ID_COL] = LF->GetStringFromLong(nID);
		}		

		pRs.MoveNext();
	}
}

void CRcpView::RemoveNoneCrossOrder()
{
#define SHARE_CODE_PARAMETER_COUNT 20

	if(COleDateTime::GetCurrentTime() - m_dtLastRemove <= COleDateTimeSpan(0, 0, 0, 30))
		return;

	m_dtLastRemove = COleDateTime::GetCurrentTime();

	CMkRecordset pRs(m_pMkDb);
	CString strSP = "select_order_list_for_check_delete_new";

	DISTINCT_SHARE_CODE_MAP::iterator itCode;
	CMkCommand pCmd(m_pMkDb, strSP);
	long nCount = 0;

	for(itCode = m_mapDistinctShareCode.begin(); itCode != m_mapDistinctShareCode.end(); itCode++)
	{
		pCmd.AddParameter(itCode->second);
		if(++nCount > SHARE_CODE_PARAMETER_COUNT)
			break;	
	}

	for(int n = nCount; n < SHARE_CODE_PARAMETER_COUNT; n++)
		pCmd.AddParameter(-1);

	CMkParameter *parOutCurDate = pCmd.AddParameter(typeDate, typeInputOutput, sizeof(COleDateTime), m_dt1);

	OrderRecordList::iterator it;
	OrderRecordList &OrderList = m_vrOrder->GetOrderRecordList();
	OrderIndex &index = m_vrOrder->GetOrderIndex();
	BOOL bDeleted = FALSE;

	if(pRs.Execute(&pCmd))
	{
		parOutCurDate->GetValue(m_dt1);

		while(!pRs.IsEOF())
		{
			long nTNo;
			pRs.GetFieldValue("nTNo", nTNo);		

			it = OrderList.find(nTNo);
			if(it != OrderList.end())
			{
				if(!it->second.bMyOrder)
				{
					OrderList.erase(it);
					bDeleted = TRUE;
#ifdef _DEBUG
					g_bana_log->Print("** delete none cross order = %d\n", nTNo);
#endif
				}
				else
				{
#ifdef _DEBUG
					g_bana_log->Print("** my order cross checked = %d\n", nTNo);
#endif
				}
			}

			pRs.MoveNext();
		}
	}
	else
	{
		return;
	}

	if(bDeleted)
	{
		index.clear();
		for(it = OrderList.begin(); it != OrderList.end();it++)
		{
			index.insert(OrderIndex::value_type(index.size(), it->second.nTNo));
		}
	}
}


//접수창을 새로띄우는 함수이다.
void CRcpView::OnBnClickedNewBtn()
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	//최상위가 카고이면, 퀵메인을 넣어준다. 항상 퀵메인 접수창이 떠야한다.
	CreateRcpDlg(m_ci.IsCargoMain() ? m_ci.m_pQuickMainBranch : NULL, "신규", -1, 0, "", FALSE, -10, GetTickCount());
}

void CRcpView::OnBnClickedCargoNewBtn()
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	//항상 카고메인 접수창이 떠야한다.
	CreateRcpDlg(m_ci.m_pCargoMainBranch, "신규", -1, 0, "", FALSE, -10, GetTickCount());
}

void CRcpView::OnBnClickedCancelOBtn()
{
	GetStateChange()->ChangeItemState(STATE_CANCELED);
}

void CRcpView::OnBnClickedAllocateBtn()
{
	SetRefreshStop();
	GetStateChange()->ChangeItemState(STATE_OK_ONLY_MAN); //charko
}


void CRcpView::OnBnClickedCancelABtn()
{
	GetStateChange()->ChangeItemState(STATE_OK);
	/*
	if(IsMultiSelected())
	{
		
	}

	CMkLock lock(&m_csOrder);
	int nSelItem = m_xList.GetSelectedItem();

	if(GetItemSecondCross(nSelItem))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	if(nSelItem >= 0) {
		CancelAllocate(GetItemTNo(nSelItem), GetItemState(nSelItem));
		return;
	}
	LF->MsgBox(IDS_INVALID_ITEM);
	*/ 
}



void CRcpView::OnBnClickedCompleteBtn()
{
	GetStateChange()->ChangeItemState(STATE_ALLOCATED);
}

void CRcpView::OnBnClickedInquiryBtn()
{
	GetStateChange()->ChangeItemState(STATE_INQUIRY);
}

void CRcpView::OnBnClickedFinishBtn()
{
	GetStateChange()->ChangeItemState(STATE_FINISH);
}

void CRcpView::OnChangeStateSite()
{
	if(!LF->POWER_CHECK(2002, "오더상태변경", TRUE))
		return;

	int nRet = 0;
	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	long nTNo = GetItemTNo(nSelItem);
	int nPreState = GetItemState(nSelItem);
	CString strMsg = "현장으로 오더를 전송하시겠습니까?";

	if(MessageBox(strMsg, "현장전송", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CMkCommand pCmd(m_pMkDb, "change_item_state");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(long), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_SITE);

		if(!pCmd.Execute()) return;
		parRet->GetValue(nRet);					

		switch(nRet)
		{
		case 0:
			LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_SITE;
			AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(strMsg, "확인", MB_ICONEXCLAMATION);
			break;
		}
	}
}

void CRcpView::OnChangeWaitState()
{
	GetStateChange()->ChangeItemState(STATE_WAIT); 
}


void CRcpView::OnChangeStateCarry()
{
	if(!LF->POWER_CHECK(2002, "오더상태변경", TRUE))
		return;

	CMkLock lock(&m_csOrder);
	int nRet = 0;
	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	long nTNo = GetItemTNo(nSelItem);
	int nPreState = GetItemState(nSelItem);
	CString strMsg = "물건을 이동중인 상태로 변경하시겠습니까?";

	if(MessageBox(strMsg, "물건이동", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CMkCommand pCmd(m_pMkDb, "change_item_state");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(long), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_CARRY);

		if(!pCmd.Execute()) return;		
		parRet->GetValue(nRet);					

		switch(nRet)
		{
		case 0:
			LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_CARRY;
			AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(strMsg, "확인", MB_ICONEXCLAMATION);
			break;
		}
	}
}
 
void CRcpView::OnBnClickedSearchBtn()
{	
	if(IsTodaySearch() && m_bRemoveSearch)
		RemoveSearch(FALSE);

	COleDateTimeSpan span = COleDateTime::GetCurrentTime() - m_dtLastForLimit;
	if(span.GetTotalSeconds() < 1)
	{
		RefreshFilterOnly();
		return;
	}

	m_bRefreshWithCID = FALSE;

	RefreshList();

	m_dtLastForLimit = COleDateTime::GetCurrentTime();

}

void CRcpView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	MakeContextMenu();
}

void CRcpView::MakeContextMenuUpCharge(long nState, BCMenu *pRMenu)
{
	if(nState == STATE_OK || nState == STATE_OK_ONLY_MAN)
	{ 
		if(m_pBi->nUseUpChargeForNotAllocate == 1)
		{ 
			CString strTemp; 
			long nItem = pRMenu->GetMenuItemCount(); 

			if(m_pBi->nUpChargeForNotAllocate1 > 0 ||
				m_pBi->nUpChargeForNotAllocate2 > 0 ||
				m_pBi->nUpChargeForNotAllocate3 > 0)
			{
				pRMenu->InsertMenu(nItem++, MF_BYPOSITION|MF_SEPARATOR,  (UINT)-1, LPCTSTR(NULL));

				if(m_pBi->nUpChargeForNotAllocate1 > 0)
				{
					strTemp.Format("요금 %d원 추가함", m_pBi->nUpChargeForNotAllocate1);
					pRMenu->InsertMenu(nItem++, MF_BYPOSITION | MF_BYCOMMAND, ID_USE_UP_CHARGE1, strTemp);
				}				
				if(m_pBi->nUpChargeForNotAllocate2 > 0)
				{
					strTemp.Format("요금 %d원 추가함", m_pBi->nUpChargeForNotAllocate2);
					pRMenu->InsertMenu(nItem++, MF_BYPOSITION | MF_BYCOMMAND, ID_USE_UP_CHARGE2, strTemp);
				}				
				if(m_pBi->nUpChargeForNotAllocate3 > 0)
				{
					strTemp.Format("요금 %d원 추가함", m_pBi->nUpChargeForNotAllocate3);
					pRMenu->InsertMenu(nItem++, MF_BYPOSITION | MF_BYCOMMAND, ID_USE_UP_CHARGE3, strTemp);
				}

				pRMenu->InsertMenu(nItem++, MF_BYPOSITION | MF_BYCOMMAND, ID_USE_UP_CHARGE_RELEASE, "요금인상해지");
				pRMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");
			}								
		}
	}
}

void CRcpView::MakeContextMenu(BOOL bMenuFromRcpDlg, long nTNo)
{
	CPoint point;
	GetCursorPos(&point);

	HDHITTESTINFO HitTest;
	CPoint cpyPoint = point;

	m_xList.ScreenToClient(&cpyPoint);

	HitTest.pt.x = cpyPoint.x;
	HitTest.pt.y = cpyPoint.y;

	CRect rect;
	m_xList.GetWindowRect(&rect);
	if(!rect.PtInRect(point) && bMenuFromRcpDlg == FALSE) return;

	BCMenu	m_menuPopup;

	m_menuPopup.SetMenuDrawMode(TRUE);
	m_menuPopup.LoadMenu(IDR_CONTEXT_MENU);
	m_menuPopup.SetBitmapBackground(RGB(0, 255, 255));
	m_menuPopup.SetIconSize(16,18);// 16,18
	m_menuPopup.LoadToolbar(IDR_MENU_TOOLBAR);

	int nItem = m_xList.GetSelectedItem();
	BCMenu* pRMenu = (BCMenu*)m_menuPopup.GetSubMenu(0);
	OrderRecord *ibi = m_vrCur->GetOrderRecord(nItem);

	if(m_ci.m_nStateType == 3)
	{
		pRMenu->RemoveMenu(ID_STATE_SITE, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_STATE_CARRY, MF_BYCOMMAND);
	}

	
	if(!LF->GetBranchInfo(ibi->nCompany)->IsCargo()  )
		pRMenu->RemoveMenu(ID_STATE_BILLDRAW, MF_BYCOMMAND);				
	else if(LF->GetBranchInfo(ibi->nCompany)->IsCargo() && ibi->nState != STATE_FINISH )
		pRMenu->EnableMenuItem(ID_STATE_BILLDRAW,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);	
	else if(LF->GetBranchInfo(ibi->nCompany)->IsCargo() && ibi->nState == STATE_FINISH  && ibi->nBillDraw == BILL_DRAW )
	{
		pRMenu->EnableMenuItem(ID_STATE_ALLOCATE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_RCP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_CANCEL,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_COMPLETE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_FINISH,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_SITE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_CARRY,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_WAIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_OTHER_ALLOCATE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);	
		pRMenu->EnableMenuItem(ID_STATE_SITE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_ORDER_MOVE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_SHARE_ORDER,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_BILLDRAW,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	
	if(nItem < 0)
	{	
		pRMenu->EnableMenuItem(ID_STATE_ALLOCATE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_RCP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_CANCEL,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_COMPLETE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_FINISH,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_SITE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_CARRY,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_STATE_WAIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		//pRMenu->EnableMenuItem(ID_MOVE_ORDER,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	else {
		
		if(ibi->nState == STATE_INTERNET)
		{
			pRMenu->EnableMenuItem(ID_STATE_ALLOCATE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_RCP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_COMPLETE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_FINISH,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_SITE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_CARRY,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_STATE_WAIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pRMenu->EnableMenuItem(ID_OTHER_ALLOCATE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_SITE)
		{
			pRMenu->EnableMenuItem(ID_STATE_SITE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_CARRY)
		{
			pRMenu->EnableMenuItem(ID_STATE_CARRY,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_OK)
		{
			pRMenu->EnableMenuItem(ID_STATE_RCP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			if(ibi->bShareOrder)
			{
				pRMenu->SetMenuText(ID_SHARE_ORDER, "공유해제", MF_BYCOMMAND);
			}
		}
		else if(ibi->nState == STATE_OK_ONLY_MAN)
		{
			pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_ALLOCATED)
		{
			pRMenu->EnableMenuItem(ID_STATE_COMPLETE,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_PICKUP)
		{
			pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}		
		else if(ibi->nState == STATE_FINISH)
		{
			pRMenu->EnableMenuItem(ID_STATE_FINISH,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			//pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_CANCELED)
		{
			pRMenu->EnableMenuItem(ID_STATE_CANCEL,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			//pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
		else if(ibi->nState == STATE_WAIT)
		{
			pRMenu->EnableMenuItem(ID_STATE_WAIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			//pRMenu->EnableMenuItem(ID_STATE_PICKUP,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}

		if(ibi->nState == STATE_WAIT || ibi->nState == STATE_OK)
		{
			if(m_ci.m_bUseCoaliShare == FALSE)
			{
				pRMenu->RemoveMenu(ID_DAERI_SHARE, MF_BYCOMMAND);
				pRMenu->RemoveMenu(ID_DAERI_SHARE_RELEASE, MF_BYCOMMAND);
			}
			else
			{
				if(ibi->nCTNo > 0) //공유중
					pRMenu->RemoveMenu(ID_DAERI_SHARE, MF_BYCOMMAND);
				else
					pRMenu->RemoveMenu(ID_DAERI_SHARE_RELEASE, MF_BYCOMMAND);

			}
		}	 
		else
		{
			pRMenu->RemoveMenu(ID_DAERI_SHARE, MF_BYCOMMAND);
			pRMenu->RemoveMenu(ID_DAERI_SHARE_RELEASE, MF_BYCOMMAND);
		}

		if(!LF->POWER_CHECK(2013, "녹취파일재생") && !LF->POWER_CHECK(2016, "본인접수파일듣기"))
		{
			pRMenu->RemoveMenu(ID_REC_PLAYER, MF_BYCOMMAND);
			pRMenu->RemoveMenu(ID_REC_DOWNLOAD, MF_BYCOMMAND);
			//BCMenu	menuRecord;
			//pRMenu->AppendMenu(MF_POPUP, (UINT)menuRecord.m_hMenu, "녹취확인");
			//menuRecord.AppendMenu(MF_STRING, ID_REC_PLAYER, "전화기듣기");
			//menuRecord.AppendMenu(MF_STRING, ID_REC_DOWNLOAD, "다운로드");
			//menuRecord.Detach();
		}

		if(!LF->POWER_CHECK(1350, "진상고객수신거부"))
			pRMenu->RemoveMenu(ID_JINSANG_CALLING_DENY, MF_BYCOMMAND);

		if(ibi->nState == STATE_OK) 
		{ 
			if(ibi->dtDelayNotice.m_status != COleDateTime::null)
				pRMenu->SetMenuText(ID_DELAY_NOTICE, "지연알림 재설정", MF_BYCOMMAND);
			else
				pRMenu->RemoveMenu(ID_DELAY_NOTICE_RELEASE, MF_BYCOMMAND);
		}
		else
		{
			pRMenu->RemoveMenu(ID_DELAY_NOTICE, MF_BYCOMMAND);
			pRMenu->RemoveMenu(ID_DELAY_NOTICE_RELEASE, MF_BYCOMMAND);
		}

		if(ibi->bAutoWait)
			pRMenu->SetMenuText(ID_AUTO_WAIT, "자동대기(현재 자동대기상태)", MF_BYCOMMAND);		
		else
			pRMenu->SetMenuText(ID_AUTO_WAIT, "자동대기(현재 자동대기상태아님)", MF_BYCOMMAND);

		MakeContextMenuUpCharge(ibi->nState, pRMenu);

	}

	if(!m_ci.m_bAllocateWithPDA)
	{
		pRMenu->SetMenuText(ID_STATE_COMPLETE, "배      차(&B)", MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_STATE_ALLOCATE, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_STATE_WAIT, MF_BYCOMMAND);
	}

	if(bMenuFromRcpDlg == TRUE)
	{
		pRMenu->RemoveMenu(ID_SET_DEPOSIT_ZERO, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_SHARE_ORDER, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_ORDER_MOVE, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_OTHER_ALLOCATE, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_CUR_ORDER_STATE, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_SHOW_RIDER_POS_BTN, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_MOVE_ORDER, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_COPY_ORDER, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_MENU_SEND_SMS, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_VIEW_EXCEL, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_MAKE_NEW_RCP_DLG, MF_BYCOMMAND);

		for(int i = pRMenu->GetMenuItemCount() - 1; i >= 0; i--)
		{
			MENUITEMINFO info;
			info.cbSize = sizeof (MENUITEMINFO); 
			info.fMask = MIIM_TYPE;
			if(pRMenu->GetMenuItemInfo(i, &info, TRUE))
				if(info.fType & MFT_SEPARATOR)
					pRMenu->RemoveMenu(i, MF_BYPOSITION);
		}
	}

	
	if(m_ci.m_nShareCode5 == 9999)
	{
		pRMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");
		pRMenu->AppendMenu(MF_BYCOMMAND, ID_CALL_PASS, "인성 콜패스");
	}

	m_nRefreshTNoForStateChange = nTNo;

	DWORD dwRetValue = pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, 
		point.x, point.y, this);

	if(dwRetValue)	 
		PostMessage(WM_COMMAND, MAKEWPARAM(dwRetValue, 0), (LPARAM)NULL);

	m_menuPopup.DestroyMenu();
}

void CRcpView::OnBnClickedEditBtn()
{	
	EditOrder();
}

void CRcpView::EditOrder(BOOL bAdd)
{
	CMkLock lock(&m_csOrder);

	int nItem = m_xList.GetSelectedItem();

	CXTPGridSelectedRows *pRows = m_xList.GetSelectedRows();

	if(pRows->GetCount() > 1) 
	{
		CXTPGridRow *pRow = pRows->GetAt(0);

		if(pRow)
		{ 
			nItem = pRow->GetIndex();
		}
	}

	/*
	if(m_xList.GetSelectedRows()->GetCount() > 1) 
	{
		CXTPGridRow *pRow = m_xList.GetFocusedRow();

		if(pRow)
		{ 
			nItem = pRow->GetIndex();
		}
	}
	*/

	if(GetItemSecondCross(nItem))
	{ 
		CREATE_MODALESS(COrderLogDetailDlg, this);
		pDlg->m_nTNo = GetItemTNo((nItem));
		pDlg->m_nState = GetItemState(nItem);
		pDlg->m_bCross = GetItemSecondCross(nItem);
		pDlg->m_bFullSearch = GetItemTodayOrder(nItem) ? FALSE : TRUE;
		SHOW_MODALESS(COrderLogDetailDlg, this);

		return;
	}


	if(nItem < 0)
	{
		MessageBox("수정할 데이터를 선택하시기 바랍니다.", 
			"확인", MB_ICONEXCLAMATION);
		return;
	}

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;


	CRcpDlg *pDlg = NULL;
	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)

	CString strName = GetItemCName(nItem);

	if(LF->IsUseNewDlg())
		strName += CString(" ") + GetItemPhone(nItem);

	m_nLastSelItemNo = GetItemTNo(nItem);
	pDlg = CreateRcpDlg(LF->GetBranchInfo(GetItemCompany(nItem)),
		strName,
		m_nLastSelItemNo, 
		GetItemState(nItem), "", bAdd, -1, 0, 0, FALSE, IsTodaySearch() ? "" : m_sYear);
 
	//if(pDlg && GetItemConsignTNo(nItem) > 0)
	//	pDlg->ShowWindow(SW_SHOW);
}
 
BOOL CRcpView::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);


	//마우스입력이 있는 동안에는 timer를 중지시킴
	if(pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_RBUTTONDOWN ||
		pMsg->message == WM_NCLBUTTONDOWN || pMsg->message == WM_NCRBUTTONDOWN)
	{
		KillTimer(AUTO_REFRESH_TIMER);
		m_sAllocateRNo = "";

		if(m_bChangeCursor)
		{
			CPoint point; ::GetCursorPos(&point);
			ScreenToClient(&point); 

			CRect rcControl;   

			m_wndTabControl.GetWindowRect(&rcControl);  
			ScreenToClient(rcControl);

			if((rcControl.top - 6 < point.y) && (point.y < rcControl.top - 0))
			{
				m_bMoveControl = TRUE;
				SetCursor(m_hcMiddle);
			}
		}
	}
	else if(pMsg->message == WM_LBUTTONUP || pMsg->message == WM_RBUTTONUP ||
		pMsg->message == WM_NCLBUTTONUP || pMsg->message == WM_NCRBUTTONUP)
	{
		SetTimer(AUTO_REFRESH_TIMER, 1000, NULL);
		m_sAllocateRNo = "";

		m_bChangeCursor = FALSE; // 화면이동 변수들
		m_bMoveControl = FALSE;
		SetCursor(m_hcArrow);
	}
	else if(pMsg->message == WM_MOUSEMOVE)
	{
		CPoint point; ::GetCursorPos(&point);
		ScreenToClient(&point); 


		if(m_bMoveControl)
		{ // 커서 땜시 10 위로 

			CRect rcControl, rcWnd;   

			m_wndTabControl.GetWindowRect(&rcControl);  
			ScreenToClient(rcControl);
			m_xList.GetWindowRect(rcWnd);
			ScreenToClient(rcWnd);

			if((point.x < rcControl.left + 50) ||
				(point.x > rcControl.right -50) ||
				(point.y < rcWnd.top + 50) ||
				(point.y > rcControl.bottom - 50)
				) 
			{
				m_bChangeCursor = FALSE; // 화면이동 변수들
				m_bMoveControl = FALSE; 
				SetCursor(m_hcArrow); 
				return CFormView::PreTranslateMessage(pMsg); 
			}

			SetCursor(m_hcMiddle);  
			CRect rcPage;
			this->GetWindowRect(&rcPage);

			long nHeight = rcPage.Height() - point.y;
			ChangeFormHeight(nHeight);
		}
		else
		{
			CRect rcControl;   

			m_wndTabControl.GetWindowRect(&rcControl);  
			ScreenToClient(rcControl);

			if((rcControl.top - 6 < point.y) && (point.y < rcControl.top - 0))
			{
				SetCursor(m_hcMiddle);
				m_bChangeCursor = TRUE;
			}
			else
			{
				m_bChangeCursor = FALSE;
				SetCursor(m_hcArrow);
			}
		}
	}


	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->hwnd == m_xList.GetSafeHwnd())
		{
			if( ((int)pMsg->wParam >= 48 && (int)pMsg->wParam <= 57  ) 
				|| ((int)pMsg->wParam >= 96 && (int)pMsg->wParam <= 105 ) ||
				pMsg->wParam == VK_RETURN || pMsg->wParam == VK_BACK)// 0 - 9
			{

				this->SetRefreshStop();

				if(LU) 
				{
					if(LU->m_pwndPane5->IsHidden()) 
					{					
						LU->GetAllocatePane()->SetPaneDocking(FALSE);
						LU->m_pwndPane5->Select();
						XTPDockingPaneDirection dir =   
							LU->m_paneManager.GetPaneDirection(LU->m_pwndPane5);

						CRect rc = GetAllocatePaneRect();

						if(rc.left != FLOAT_LOCATE)
							LU->m_paneManager.FloatPane(LU->m_pwndPane5, rc);

						int nSelItem = m_xList.GetSelectedItem();
						LU->GetAllocatePane()->SetTNo(GetItemTNo(nSelItem), m_bShareOrderRefresh, GetItemCompany(nSelItem),
							GetItemRiderCompany(nSelItem), GetItemRNo(nSelItem), GetItemTodayOrder(nSelItem));
						LU->GetAllocatePane()->SetCustomerRefresh();
						LU->GetAllocatePane()->NearOrderRefresh(GetItemTNo(nSelItem));
						LU->GetAllocatePane()->AutoHide(TRUE);
					}
					else
					{
						LU->m_pAllocatePane->SetPaneDocking(TRUE);
					}

					LU->GetAllocatePane()->PostMessage(WM_READY_ALLOCATE, pMsg->wParam, 1);	
				}
				
				return TRUE;
			}			
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_edtShowRiderInfo.GetSafeHwnd())
			{
				SearchRiderInfo();
				return TRUE;
			}
			else if(pMsg->hwnd == m_edtShTNo.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShCustomer.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShDepart.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShManager.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShCustomerID.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShGroup.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShGroupDepart.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShCID.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShWNo.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShEtc.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShStart.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShDest.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShRider.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShRiderNo.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShRegionStart.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShRegionDest.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShCustomerMemo.GetSafeHwnd() ||
				pMsg->hwnd == m_edtShCustomerInnerMemo.GetSafeHwnd())
			{
				if(IsTodaySearch() && pMsg->hwnd != m_edtShTNo.GetSafeHwnd())
					OnBnClickedDeleteSearchTextBtn();

				OnBnClickedSearchBtn();
				return TRUE;
			}
		}
	}

	if(GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CONTROL) & 0x8000)
	{
		if(pMsg->hwnd == m_xList.GetSafeHwnd() )
		{
			if (pMsg->message == WM_LBUTTONUP)
			{
				if(m_xList.GetSelectedRows()->GetCount() > 1 && m_bMultiSelectRefreshStop == FALSE)
				{
					CMkLock lock(&m_csOrder);
					KillTimer(AUTO_REFRESH_TIMER);
					m_bMultiSelectRefreshStop = TRUE;
					ShowRefreshSec(m_nDiscountSec,  TRUE,  FALSE);
				}
			}
		}
	}

	
	if(m_xList.GetSelectedRows()->GetCount() <= 1 && m_bMultiSelectRefreshStop)
	{
		SetTimer(AUTO_REFRESH_TIMER, 1000, NULL);
		ShowRefreshSec(m_nDiscountSec,  FALSE,  TRUE);
		m_bMultiSelectRefreshStop = 0;
	}
	

	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->hwnd == m_xList.GetSafeHwnd()) 
		{
			return ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg); 
			/*
			switch(pMsg->wParam)
			{ 
			case	'W':  //밑에서 부터 단축키 Accelerator이 안걸리네요? // 대
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnChangeWaitState();
				break;
				
			case	'T': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnChangeStateSite();					
				break;
				
			case	'C': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedCancelABtn();					
				break;
			case	'P': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedPickupBtn();					
				break;
			case	'Z': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedFinishBtn();					
				break;
			case	'F': 
			case	'f': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedCompleteBtn();					
				break;
			case	'M': 
			case	'm': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnChangeStateCarry();					
				break;
			case	'O': 
			case	'o': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedCancelOBtn();					
				break;
			case	'B': 
			case	'b': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedAllocateBtn();					
				break;
			case	'S': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedShareOrder();	
				break;
			case	'G': 
			case	'g': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnMoveOrder();				 	
				break;
			case	'T': 
			case	't': 
				if(GetKeyState(VK_CONTROL) & 0x8000)
					OnBnClickedCopyOrder();	
				break;
			}
			*/
		}
		else
		{
			switch(pMsg->wParam)
			{
			case VK_F1:
				OnBnClickedStateAllBtn();
				break;
			case VK_F2:
				OnBnClickedStateRcpBtn();
				break;
			case VK_F3:
				OnBnClickedStateWaitBtn();
				break;
			case VK_F4:
				OnBnClickedStateStateReservedBtn();
				break;
			case VK_F5:
				OnBnClickedStateCancelBtn();
				break;
			case VK_F6:
				OnBnClickedStateOnlyManBtn();
				break;
			case VK_F7:
				OnBnClickedStateAllocBtn();
				break;
			case VK_F8:
				OnBnClickedStatePickupBtn();
				break;
			case VK_F9:
				OnBnClickedStateFinishBtn();
				break;
			case VK_F10:
				OnBnClickedStateEtcBtn();
				break;
			case VK_F11:
				SimpleSearch();
				return TRUE;
			case VK_F12:
				OnBnClickedSearchBtn();
				return TRUE;
			}
		}
	}

	if(pMsg->message == WM_LBUTTONDOWN) 
	{
		long nID = ::GetDlgCtrlID(pMsg->hwnd);
		if(nID == IDC_CAR_TYPE_STATIC)
		{
			if(LF->GetCurBranchInfo()->IsCargo())
				ShowShTruckTypeDlg();
			else
				ShowShCarTypeDlg();

			return TRUE;
		}
		else if(nID == IDC_PAY_TYPE_STATIC)
		{
			ShowShPayTypeDlg();
			return TRUE;
		}
		else if(nID == IDC_SEARCH_START_REGION_EDIT)
		{
			OpenRegionDlg(TRUE); 
			return TRUE;
		}
		else if(nID == IDC_SEARCH_DEST_REGION_EDIT)
		{
			OpenRegionDlg(FALSE);
			return TRUE;
		}
		/*
		else if(nID == IDC_REPORT_LIST_RCPPAGE)
		{			
			CRect rect;
			m_xList.GetWindowRect(&rect);
			ScreenToClient(rect); 

			CPoint point; ::GetCursorPos(&point);
			ScreenToClient(&point); 
			point -= rect.TopLeft();
			CXTPGridRow *pRow = m_xList.HitTest(point);
			
			if(pRow == NULL)
				return FALSE;

			long nItem = pRow->GetIndex();
			if(pRow != NULL)
			{
				CVirtualRecord *pRecord = (CVirtualRecord*)pRow->GetRecord();
				m_nTreeParTNo = pRecord->GetOrderRecord(nItem)->nTNo;
			}
			return FALSE;
		} 
		*/

		//m_nTreeParTNo = GetItemTNo(nRow);
	}

	return CFormView::PreTranslateMessage(pMsg); 
	//return ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg); 
}


void CRcpView::SimpleSearch()
{
	CSimpleSearchDlg dlg;
	dlg.m_nCompany = m_pBi->nDOrderTable;
	dlg.m_bIntegrated = m_pBi->bIntegrated;	
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nTNo == -1) return;
		if(dlg.m_nState == -1) return;
		if(dlg.m_sCName == "") return;
		CreateRcpDlg(NULL, dlg.m_sCName,dlg.m_nTNo,dlg.m_nState);		

	}

}

void CRcpView::OnPrinterSetting()
{
	m_pReceiptPrint->PrinterSetting();
}

void CRcpView::OnReceiptTaxPrint()
{

	TaxPrint();
}
void CRcpView::OnReceiptTaxPrintView()
{

	TaxPrint(TRUE);
}

void CRcpView::TaxPrint(BOOL bView)
{
	if(m_xList.GetSelectedRows()->GetCount() <= 0 )
	{
		MessageBox("출력하실 오더를 선택하여주세요");
		return;
	}

	CVirtualRecord *pvrOrder;
	if(m_vrCur == m_vrPreDate || !IsTodaySearch())
		pvrOrder = m_vrPreDate;
	else
		pvrOrder = m_vrOrder;

	
	CString sTNoList = "", sTNo = "";
	POSITION pos = m_xList.GetSelectedRows()->GetFirstSelectedRowPosition();
	long nIndex = -1, nCompany = 0;
	do{

		nIndex = m_xList.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		if(nIndex >= 0)
		{
			if(pvrOrder->GetOrderRecord(nIndex)->nState == STATE_CANCELED )//종료되기전 출력해서 가기를 원함 
			{
				MessageBox("종료되지 않은 오더입니다 . 종료되었으면 갱신하시고 다시시도하세요", "확인", MB_ICONINFORMATION);
				return;
			}

			if(pvrOrder->GetOrderRecord(nIndex)->nRiderCompany <=0 ||
				pvrOrder->GetOrderRecord(nIndex)->nRNo <=0 )			
			{
				MessageBox("기사가 없는 오더입니다 . 갱신하시고 다시시도하세요", "확인", MB_ICONINFORMATION);
				return;

			}
			


			nCompany = pvrOrder->GetOrderRecord(nIndex)->nCompany;
			sTNo.Format("%ld", pvrOrder->GetOrderRecord(nIndex)->nTNo);
			sTNoList += sTNo + ",";			

			
		}
	}while (pos != NULL);

	CREATE_MODALESS(CTransactionListDlg, this);
	pDlg->m_nType = 0;
	pDlg->m_sTNoList = sTNoList;
	pDlg->m_bBillView = bView;
	pDlg->m_nCompany = nCompany;
	//pDlg->m_nCorporationID = nCorporationID;
	//pDlg->m_nBillID = nBillID;
	SHOW_MODALESS(CTransactionListDlg, this);

	

	//m_pReceiptPrint->Print();
}

void CRcpView::OnReceiptGeneralPrintView()
{
	



	if(m_xList.GetSelectedRows()->GetCount() <= 0 )
	{
		MessageBox("출력하실 오더를 선택하여주세요");
		return;
	}

	CVirtualRecord *pvrOrder;
	if(m_vrCur == m_vrPreDate || !IsTodaySearch())
		pvrOrder = m_vrPreDate;
	else
		pvrOrder = m_vrOrder;


	CString sTNoList = "", sTNo = "";
	POSITION pos = m_xList.GetSelectedRows()->GetFirstSelectedRowPosition();
	long nIndex = -1, nCompany = 0;
	int i = 0;
	do{

		nIndex = m_xList.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		if(nIndex >= 0)
		{
			if(pvrOrder->GetOrderRecord(nIndex)->nState == STATE_CANCELED)				
			{
				MessageBox("종료되지 않은 오더입니다 . 종료되었으면 갱신하시고 다시시도하세요", "확인", MB_ICONINFORMATION);
				return; 
			}

			if(pvrOrder->GetOrderRecord(nIndex)->nRiderCompany <=0 ||
				pvrOrder->GetOrderRecord(nIndex)->nRNo <=0 )			
			{
				MessageBox("기사가 없는 오더입니다 . 갱신하시고 다시시도하세요", "확인", MB_ICONINFORMATION);
				return;

			}

			nCompany = pvrOrder->GetOrderRecord(nIndex)->nCompany;
			sTNo.Format("%ld", pvrOrder->GetOrderRecord(nIndex)->nTNo);
			sTNoList += sTNo + ",";			
			++i;

		}
	}while (pos != NULL);


	CString sID ="";
	CString sPass ="";	
	long nCorporationID = 0;
	CMyXTPGridRecord *pRecord = NULL;

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	// nLoginType 1 : 접수프로그램,  0 : 인터콜
	strForm.Format(" quick3.logisoft.co.kr/Receipt/receipt.asp?sID=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&nTNoComma=%s&checkCnt=%d&nLoginType=1",
		m_ui.strID, m_ui.strPW,m_ui.strName, m_ci.m_nCompanyCode,m_ci.m_bRcpIntMode1 ? "1" : "0", 
		m_ui.nSiteSessionKey, m_ei.strExternalIP, sTNoList,i);


	str += strForm;
	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}	

}

void CRcpView::OnReceiptPrint()
{
	if(m_ci.m_nCompanyCode != 15480)
	{
		MessageBox("송장 제본출력은 로지소프트 문의하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(! m_pReceiptPrint->IsPrinterSetting() )
		OnPrinterSetting();

	if(m_xList.GetSelectedRows()->GetCount() <= 0 )
	{
		MessageBox("출력하실 오더를 선택하여주세요");
		return;
	}

	CVirtualRecord *pvrOrder;
	if(m_vrCur == m_vrPreDate || !IsTodaySearch())
		pvrOrder = m_vrPreDate;
	else
		pvrOrder = m_vrOrder;


	
	POSITION pos = m_xList.GetSelectedRows()->GetFirstSelectedRowPosition();
	long nIndex = -1;
	do{
		
		nIndex = m_xList.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		if(nIndex >= 0)
		{

	
			CPOIUnit *pDest = NULL; 
			CString strChargeAdd = "", strChargeDis = "", strChargeBasic = "", sDestRealDong = ""; 
			CString sCarName = "", sChargeType = "", sCarNameAndChargeType = "", sDt = "";
			long nChargeAdd = 0, nChargeDis = 0, nChargeAddDis = 0, nDestRealDongID = 0;

			strChargeAdd = pvrOrder->GetOrderRecord(nIndex)->info[29].c_str();			
			strChargeDis = pvrOrder->GetOrderRecord(nIndex)->info[30].c_str();
			strChargeAdd.Replace(",", ""); strChargeDis.Replace(",", "");
			nChargeAdd = atol(strChargeAdd); nChargeDis = atol(strChargeDis);
			nChargeAddDis = nChargeAdd - nChargeDis;


			sCarName = LF->GetCarTypeFromLong(pvrOrder->GetOrderRecord(nIndex)->nCarType );
			sChargeType = LF->GetPayTypeFromLong(pvrOrder->GetOrderRecord(nIndex)->nPayType);
			if(sCarName.GetLength() > 0 && sChargeType.GetLength() > 0)
				sCarName +=  " / " + sChargeType;

			sCarNameAndChargeType = sCarName;

			CStringArray sArr; CString s1, strTempSSAddress;
			CStringW strSDetail(pvrOrder->GetOrderRecord(nIndex)->strSAddress.c_str());
			strTempSSAddress = pvrOrder->GetOrderRecord(nIndex)->strSDetail.c_str();
			strTempSSAddress.Replace("  " , " ");		
			CStringW strSSAddress(strTempSSAddress);						
				
			long nLenSize = strSDetail.GetLength();			
			int nCount = nLenSize / 32;
			
			s1 = strSSAddress.Mid(0, strSSAddress.GetLength() );
			sArr.Add(s1);			

			for(int i =0; i < nCount+ 1; i++)
			{
				s1 = strSDetail.Mid(i * 32,  32);
				sArr.InsertAt(i,s1);				
			}			

			RECEIPT_INFO *pReceiptInfo = new RECEIPT_INFO;
			pReceiptInfo->sDate = pvrOrder->GetOrderRecord(nIndex)->dtFinal.Format("%Y-%m-%d");
			pReceiptInfo->sCompany = pvrOrder->GetOrderRecord(nIndex)->strCName.c_str();

			pReceiptInfo->sDept = pvrOrder->GetOrderRecord(nIndex)->info[6].c_str();
			pReceiptInfo->sName = pvrOrder->GetOrderRecord(nIndex)->info[39].c_str();
			pReceiptInfo->sTel = pvrOrder->GetOrderRecord(nIndex)->strOPhone.c_str();

			nDestRealDongID = pvrOrder->GetOrderRecord(nIndex)->nDestRealDongID;
			if(nDestRealDongID > 0)
			{
				pDest = m_poiNew.GetDongPOI(nDestRealDongID);
				sDestRealDong = pDest->GetDong();
			}	


			pReceiptInfo->sDestDong = pvrOrder->GetOrderRecord(nIndex)->strDest.c_str();
			pReceiptInfo->sCarNameAndChargeType = sCarNameAndChargeType;
			
			pReceiptInfo->sDestCompany = pvrOrder->GetOrderRecord(nIndex)->strDName.c_str();  //>strDest.c_str();

			pReceiptInfo->sDestTel = pvrOrder->GetOrderRecord(nIndex)->strDPhone.c_str();
			pReceiptInfo->sDestDept = ""; //pvrOrder->GetOrderRecord(nIndex)->strD>strD
			pReceiptInfo->sDestName = pvrOrder->GetOrderRecord(nIndex)->info[12].c_str(); //pvrOrder->GetOrderRecord(nIndex)->strDName.c_str();
			pReceiptInfo->nRNo = pvrOrder->GetOrderRecord(nIndex)->nRNo;
			pReceiptInfo->nTNo = pvrOrder->GetOrderRecord(nIndex)->nTNo;
			pReceiptInfo->sRName = pvrOrder->GetOrderRecord(nIndex)->strRName.c_str();

			strChargeBasic = pvrOrder->GetOrderRecord(nIndex)->info[28].c_str(); strChargeBasic.Replace(",","");
			pReceiptInfo->nBasicCharge = atol(strChargeBasic);
			pReceiptInfo->nAddCharge = nChargeAddDis;
			pReceiptInfo->nTransCharge = pvrOrder->GetOrderRecord(nIndex)->nChargeTrans;
			pReceiptInfo->nTotalCharge =  pvrOrder->GetOrderRecord(nIndex)->nCharge;
			pReceiptInfo->sStartDetail.Copy(sArr);
			//pReceiptInfo->sStartDetail = pvrOrder->GetOrderRecord(nIndex)->strSDetail.c_str();

			m_pReceiptPrint->SetInputData(pReceiptInfo);

			//CPOIUnit *pDest = NULL; 
			//CString strChargeAdd = "", strChargeDis = "", strChargeBasic = "", sDestRealDong = ""; 
			//CString sCarName = "", sChargeType = "", sCarNameAndChargeType = "", sDt = "";
			//long nChargeAdd = 0, nChargeDis = 0, nChargeAddDis = 0, nDestRealDongID = 0;

			//strChargeAdd = m_vrOrder->GetOrderRecord(nIndex)->info[26].c_str();			
			//strChargeDis = m_vrOrder->GetOrderRecord(nIndex)->info[27].c_str();
			//strChargeAdd.Replace(",", ""); strChargeDis.Replace(",", "");
			//nChargeAdd = atol(strChargeAdd); nChargeDis = atol(strChargeDis);
			//nChargeAddDis = nChargeAdd - nChargeDis;

			//
			//sCarName = LF->GetCarTypeFromLong(m_vrOrder->GetOrderRecord(nIndex)->nCarType );
			//sChargeType = LF->GetPayTypeFromLong(m_vrOrder->GetOrderRecord(nIndex)->nPayType);
			//if(sCarName.GetLength() > 0 && sChargeType.GetLength() > 0)
			//	sCarName +=  " / " + sChargeType;

			//sCarNameAndChargeType = sCarName;

			//CStringW strStartDetail(m_vrOrder->GetOrderRecord(nIndex)->strSDetail.c_str());

			//long nTotalLen = strStartDetail.GetLength();
			//long nLEn = m_vrOrder->GetOrderRecord(nIndex)->strSDetail.length();
			////wstring ws = m_vrOrder->GetOrderRecord(nIndex)->strSDetail;
			////str = m_vrOrder->GetOrderRecord(nIndex)->strSDetail;
			////CStringW str = (L"[경서동 350-227번지]북항고가에서 검단방향 직진 경서삼거리가기전 사거리에서 주물공단쪽으로 좌회전 대우자동차학원지나 영빈관 중국집끼고 우회전 직진 두번째 삼거리에서 우회전 두번째집");
			////CStringW str2("[경서동 350-227번지]북항고가에서 검단방향 직진 경서");
			//
			//long nLenSize = strStartDetail.GetLength();			
			//
			//int nCount = nLenSize / 32;
			//CStringArray sArr; CString s1;
			//for(int i =0; i < nCount+ 1; i++)
			//{
			//	s1 = strStartDetail.Mid(i * 32,  32);
			//	sArr.InsertAt(i,s1);
			//}			

			//RECEIPT_INFO *pReceiptInfo = new RECEIPT_INFO;
			//pReceiptInfo->sDate = m_vrOrder->GetOrderRecord(nIndex)->dtFinal.Format("%Y-%m-%d");
			//pReceiptInfo->sCompany = m_vrOrder->GetOrderRecord(nIndex)->strCName.c_str();
			//
			//pReceiptInfo->sDept = m_vrOrder->GetOrderRecord(nIndex)->info[5].c_str();
			//pReceiptInfo->sName = m_vrOrder->GetOrderRecord(nIndex)->info[36].c_str();
			//pReceiptInfo->sTel = m_vrOrder->GetOrderRecord(nIndex)->strOPhone.c_str();

			//nDestRealDongID = m_vrOrder->GetOrderRecord(nIndex)->nDestRealDongID;
			//if(nDestRealDongID > 0)
			//{
			//	pDest = m_poiNew.GetDongPOI(nDestRealDongID);
			//	sDestRealDong = pDest->GetDong();
			//}	
			//
			//
			//pReceiptInfo->sDestDong = sDestRealDong;
			//pReceiptInfo->sCarNameAndChargeType = sCarNameAndChargeType;
			//pReceiptInfo->sDestCompany = m_vrOrder->GetOrderRecord(nIndex)->strDest.c_str();

			//pReceiptInfo->sDestTel = m_vrOrder->GetOrderRecord(nIndex)->strDPhone.c_str();
			//pReceiptInfo->sDestDept = ""; //m_vrOrder->GetOrderRecord(nIndex)->strD>strD
			//pReceiptInfo->sDestName = m_vrOrder->GetOrderRecord(nIndex)->strDName.c_str();
			//pReceiptInfo->nRNo = m_vrOrder->GetOrderRecord(nIndex)->nRNo;
			//pReceiptInfo->nTNo = m_vrOrder->GetOrderRecord(nIndex)->nTNo;
			//pReceiptInfo->sRName = m_vrOrder->GetOrderRecord(nIndex)->strRName.c_str();

			//strChargeBasic = m_vrOrder->GetOrderRecord(nIndex)->info[25].c_str(); strChargeBasic.Replace(",","");
			//pReceiptInfo->nBasicCharge = atol(strChargeBasic);
			//pReceiptInfo->nAddCharge = nChargeAddDis;
			//pReceiptInfo->nTransCharge = m_vrOrder->GetOrderRecord(nIndex)->nChargeTrans;
			//pReceiptInfo->nTotalCharge =  m_vrOrder->GetOrderRecord(nIndex)->nCharge;
			//pReceiptInfo->sStartDetail.Copy(sArr);
			////pReceiptInfo->sStartDetail = m_vrOrder->GetOrderRecord(nIndex)->strSDetail.c_str();

			//m_pReceiptPrint->SetInputData(pReceiptInfo);
		}
		
	}while (pos != NULL);

	m_pReceiptPrint->Print();

		
	//CDC dcPrinter;
	//dcPrinter.Attach(hdcPrinter);


}
void CRcpView::OnViewExcel()
{
	if(!LF->POWER_CHECK(2010, "엑셀변환", TRUE))
		return;

	CoInitialize(NULL);

	long rows = m_xList.GetRecords()->GetCount() + 1;
	long cols = m_xList.GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = { static_cast<unsigned long>(rows), static_cast<unsigned long>(cols) };
	sa.Create(VT_VARIANT, 2, elements);

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			long index[] = {r, c};
			VARIANT v;
			VariantInit(&v);
			CString str;

			if(r == 0)
			{
				CXTPGridColumn *pCol = m_xList.GetColumns()->GetVisibleAt(c);
				str = pCol->GetCaption();
				v.vt = VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);
			}
			else
			{
				OrderRecord *pRec = m_vrCur->GetOrderRecord(r-1);
				CXTPGridColumn *pCol = m_xList.GetColumns()->GetVisibleAt(c);
				str = pRec->info[pCol->GetItemIndex()].c_str();
				if(str.GetLength() > 0 && str.Left(1) == "=")
					str.Remove('=');
 
				if(pCol->GetItemIndex() == RCP_DT0)
				{
					str = LF->GetStringFromLong(pRec->dt0.GetYear()) + "-" + str;					
				}
				else if(pCol->GetItemIndex() == RCP_TIME_COL)
				{
					str = LF->GetStringFromLong(pRec->dtRcp.GetYear()) + "/" + str;
				}
				else if(pCol->GetItemIndex() == RCP_DEPART_COL)
				{
					if(str.GetLength() > 0 && LF->IsNumber(str))
					{
						if(str.Left(1) == "0")
							str = "'" + str;
					}
				}

				v.vt= VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);

			}
			VariantClear(&v);
		}
	}

	LF->AddSecurityLog(m_pBi->nDOrderTable, 101, m_ui.nWNo, rows);  
	CMyExcel::ToExcel(sa, cols, rows);
}

LONG CRcpView::OnRiderAllocate(WPARAM wParam, LPARAM lParam)
{
	if(!LF->POWER_CHECK(2002, "오더상태변경", TRUE))
		return 0;

	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return 0;
	}

	if(GetItemState(nSelItem) == STATE_INTERNET) {
		MessageBox("인터넷 접수오더는 정상접수하신 후에, 배차하십시오!", 
			"확인", MB_ICONINFORMATION);
		return 0;
	}
	else if(GetItemState(nSelItem) >= 30)
	{
		MessageBox("이미 배차/완료되었거나, 취소된 오더입니다.", "확인", MB_ICONEXCLAMATION);
		return 0;
	}

	CString strMsg;
	strMsg.Format("'%s'의 오더에 %d호 기사님을 배차하시겠습니까?", GetItemCName(nSelItem), wParam);

	if(IDYES == MessageBox(strMsg, "배차 확인", MB_ICONQUESTION | MB_YESNO))
	{
		if(m_ci.m_bAllocateWithPDA)
			GetStateChange()->Allocate(GetItemTNo(nSelItem), (int)wParam, GetItemState(nSelItem), (int)lParam);	
		else 
			GetStateChange()->CompleteState(GetItemCompany(nSelItem), GetItemTNo(nSelItem), (int)wParam, GetItemState(nSelItem));
	}			

	return 0;
}


LONG CRcpView::OnRiderAllocate2(WPARAM wParam, LPARAM lParam)
{
	if(!LF->POWER_CHECK(2002, "오더상태변경"))
		return 0;

	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return 0;
	}

	if(GetItemState(nSelItem) == STATE_INTERNET) {
		MessageBox("인터넷 접수오더는 정상접수하신 후에, 배차하십시오!", 
			"확인", MB_ICONINFORMATION);
		return 0;
	}
	else if(GetItemState(nSelItem) >= 30)
	{
		MessageBox("이미 배차/완료되었거나, 취소된 오더입니다.", "확인", MB_ICONEXCLAMATION);
		return 0;
	}

	if(m_ci.m_bAllocateWithPDA)
		GetStateChange()->Allocate(GetItemTNo(nSelItem), (int)wParam, GetItemState(nSelItem), (int)lParam);	
	else 
		GetStateChange()->CompleteState(GetItemCompany(nSelItem), GetItemTNo(nSelItem), (int)wParam, GetItemState(nSelItem));

	return 0;
}


void CRcpView::OnMouseMove(UINT nFlags, CPoint point)
{

	if(TRUE == m_bDragMode)
	{
		SetCursor( m_hcMoveHold );
		if(m_ptDrag.x == -1)
		{ 
			m_ptDrag.x = point.x;
			m_ptDrag.y = point.y;
		}

	}

	CFormView::OnMouseMove(nFlags, point);
}

void CRcpView::OnLButtonUp(UINT nFlags, CPoint point)
{
//by mksong (2011-03-02 오후 12:38)
//클릭중에 오더합치기 메시지 뜨는 경우가 많아서 일단 보류함

	//if(m_ci.m_nCompanyCode > 500)
	//	return;

	if(!LF->GetCurBranchInfo()->bUseOrderBundle)
		return;
 
	if(TRUE == m_bDragMode)
	{
		::ReleaseCapture();
		m_bRefreshOK = TRUE;
		m_bDragMode  = FALSE;  //순서에 주의 할것

		CRect rect;
		m_xList.GetWindowRect(&rect);
		ScreenToClient(rect);

		if(rect.PtInRect(point))
		{			
			point -= rect.TopLeft();
			CXTPGridRow *pRow = m_xList.HitTest(point);

			if(pRow == NULL) 
			{
				//오더해제
				InsertOrderToTreeFree();
				return;
			}

			long nItem = pRow->GetIndex(); 

			if(pRow != NULL)
			{
				CVirtualRecord *pRecord = (CVirtualRecord*)pRow->GetRecord();
				
				CRect rcRecord1, rcRecord2;
				rcRecord1 = pRow->GetItemRect(pRecord->GetItem(START_GUGUN_COL));
				rcRecord2 = pRow->GetItemRect(pRecord->GetItem(START_DONG_COL));

				if((rcRecord1.PtInRect(point) == FALSE) &&
					(rcRecord2.PtInRect(point) == FALSE))
					return;

				long nDrcTNo = pRecord->GetOrderRecord(nItem)->nTNoSet;

				InsertOrderToTree(nDrcTNo);
			}
		}
		else
			InsertOrderToTreeFree();
	}

	CFormView::OnLButtonUp(nFlags, point);
}

void CRcpView::InsertOrderToTree(long nDrcTNo)
{
	if(nDrcTNo == ZERO)
		return;

	CXTPGridSelectedRows * pRows = m_xList.GetSelectedRows();
	
	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CString strMsg = "";

	if(pRows->GetCount() > ONE)
		strMsg.Format("%d개의 오더를 합치시겠습니까?", pRows->GetCount());
	else
		strMsg = "오더를 합치시겠습니까?";

	if(MessageBox(strMsg, "확인", MB_OKCANCEL) != IDOK)
		return;

	if(CheckCrossOrder() == FALSE)
	{
		MessageBox("크로스로더는 합치실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	for(int i=ZERO; i<pRows->GetCount(); i++)
	{
		long nItem = pRows->GetAt(i)->GetIndex();

		if(InsertOrderToTreeSub(GetItemTNo(nItem), nDrcTNo) == FALSE)
			break;
	}

	RefreshList();
}

BOOL CRcpView::InsertOrderToTreeSub(long nSrcTNo, long nDrcTNo)
{
	CMkCommand pCmd(m_pMkDb, "make_order_to_tree");
	pCmd.AddParameter(nSrcTNo);
	pCmd.AddParameter(nDrcTNo);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	return pCmd.Execute();
}

void CRcpView::InsertOrderToTreeFree()
{
	CXTPGridSelectedRows *pRows = m_xList.GetSelectedRows();
 
	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	long nTNoSet = GetItemTNo(pRows->GetAt(ZERO)->GetIndex());

	CMkCommand pCmd(m_pMkDb, "make_order_to_tree_free");
	pCmd.AddParameter(nTNoSet);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	pCmd.Execute();
	RefreshList();
}

void CRcpView::OnBnClickedInterorderCheck()
{
	if(LF->IsThisCompany("하나로퀵") && m_nShInterOrder == 1)
		m_nShInterOrder++; 

	ClickSeachCheckBox(IDC_INTERORDER_CHECK, m_nShInterOrder, "인터넷접수");
}


void CRcpView::ShowRefreshSec(int nSec, BOOL bStopState, BOOL bRefresh)
{
	int nDisplaySec = max(nSec, 0);

	if(m_RefreshCombo.GetSafeHwnd())
	{
		if(m_RefreshCombo.GetCurSel() < 1)
		{
			m_RefreshCombo.SetCurSel(0);
		}
		else
		{
			CString strRefresh;

			if(bStopState)
				strRefresh.Format("%s(STOP)", szRefreshText[m_RefreshCombo.GetCurSel()]);
			else if(bRefresh)
				strRefresh.Format("%s(갱신중)", szRefreshText[m_RefreshCombo.GetCurSel()]);
			else
				strRefresh.Format("%s(%d)", szRefreshText[m_RefreshCombo.GetCurSel()], nDisplaySec);

			m_RefreshCombo.SetWindowText(strRefresh);
		}
	}
}

void CRcpView::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == AUTO_REFRESH_TIMER) 
	{
		KillTimer(nIDEvent);

		CMkLock lock(&m_csOrder,FALSE,FALSE); 
		BOOL bLock = lock.IsLocked();
		BOOL bToday = IsTodaySearch();

		if(FALSE == lock.IsLocked() && 
			!m_bRefreshWithCID &&  
			!IsRcpDlgVisible() &&
			IsTodaySearch() && 
			LU->GetCurView() == RCP_VIEW &&
			m_bMultiSelectRefreshStop == FALSE)
		{
			m_nDiscountSec--;
			if(m_nDiscountSec == 0)
			{
				ShowRefreshSec(m_nDiscountSec, FALSE, TRUE);

				if(IsTodaySearch())
					RefreshList("", "", NULL, m_bShareOrderRefresh);
				else
					OnCbnSelchangeRefreshCombo();
			}
			else
				ShowRefreshSec(m_nDiscountSec);
		}
		else
			ShowRefreshSec(m_nDiscountSec, TRUE, FALSE);

		SetTimer(nIDEvent,1000,NULL);
	}
	else if(nIDEvent == INIT_COMPLETE_TIMER)
	{
		((CMainFrame*)AfxGetMainWnd())->SetInitCompleted(TRUE);
		KillTimer(nIDEvent);
	}

	CFormView::OnTimer(nIDEvent);
}

void CRcpView::SetRefreshStart()
{
	CMkLock lock(&m_csOrder);
	ShowRefreshSec(m_nDiscountSec, TRUE);
	SetTimer(AUTO_REFRESH_TIMER, 1000, NULL);
}


void CRcpView::SetRefreshStop()
{
	CMkLock lock(&m_csOrder);
	KillTimer(AUTO_REFRESH_TIMER);				
	ShowRefreshSec(m_nDiscountSec,  FALSE,  FALSE);
}


CString CRcpView::GetPaddingString(CString strData, UINT nLen)
{
	while((UINT)strData.GetLength() < nLen)
		strData += " ";			

	if((UINT)strData.GetLength() > nLen)
		strData = strData.Left(nLen);

	return strData;
}

long CRcpView::GetRiderOrder(CListCtrl &list, long nCompany, long nRNo) 
{
	long nItem = 0;
	long nCount = 0;
	long nSum = 0;
	char buffer[20];
	long nCashCount = 0, nCashSum = 0, nCreditCount = 0, nCreditSum = 0, nTodayIncome = 0;

	OrderRecordList &OrderList = m_vrOrder->GetOrderRecordList();
	OrderRecordList::reverse_iterator it;

	list.DeleteAllItems();

	for(it = OrderList.rbegin(); it != OrderList.rend(); it++)
	{
		if((*it).second.nRiderCompany == nCompany && (*it).second.nRNo == nRNo &&
			LF->IsAllocOrder((*it).second.nState))
		{
			CString strTime;

			if(nItem == 0)
			{
				list.InsertItem(nItem++, "합계");
			}

			list.InsertItem(nItem, "");
			list.SetItemText(nItem, 1, LF->GetStateString(it->second.nState));
			list.SetItemText(nItem, 2, m_ci.GetName(it->second.nCompany) + "/" + 
				m_ci.GetBranchName(it->second.nCompany));
			list.SetItemText(nItem, 3, it->second.strStart.c_str());
			list.SetItemText(nItem, 4, it->second.strDest.c_str());
			list.SetItemText(nItem, 5, it->second.dt0.Format("%H:%M"));
			list.SetItemText(nItem, 6, it->second.dt3.Format("%H:%M"));
			list.SetItemText(nItem, 7, it->second.dtFinal.Format("%H:%M"));
			list.SetItemText(nItem, 8, ltoa(it->second.nCharge, buffer, 10));
			list.SetItemData(nItem++, it->second.nTNo);

			if(it->second.nPayType == PAY_CREDIT || it->second.nPayType == PAY_ONLINE || it->second.nPayType == PAY_CARD)
			{
				nCreditCount++;
				nCreditSum += it->second.nCharge;
			}
			else
			{
				nCashCount++;
				nCashSum += it->second.nCharge;
			}

			nCount++;
			nSum += (*it).second.nCharge;

			int nRate = it->second.nFinalDepositRate;

			nTodayIncome += (it->second.nCharge - (it->second.nCharge * ((float)it->second.nFinalDepositRate / 100.0)) );
		}
	} 

	if(nItem > 0) {
		list.SetItemText(0, 1, CString(ltoa(nCount, buffer, 10)) + "건");
		list.SetItemText(0, 2, CString(ltoa(nSum, buffer, 10)) + "원");
		list.SetItemText(0, 3, "현금 : " + CString(itoa(nCashCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCashSum));
		list.SetItemText(0, 4, "신용 : " + CString(itoa(nCreditCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCreditSum));
		list.SetItemData(0, 0);

		for(int i=1; i<list.GetItemCount(); i++)
			list.SetItemText(i, 0, ltoa(nCount - i +1, buffer, 10));
	}

	return nTodayIncome;
}

void CRcpView::EditOrderFromTNo(long nTNo)
{
	InitSearch(TRUE);
	int nRow = m_vrOrder->GetItemRowFromTNo(nTNo);
	CXTPGridRows *pRows = m_xList.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
	m_xList.EnsureVisible(pRow);
	pRow = pRows->GetAt(nRow);
	m_xList.GetSelectedRows()->Select(pRow);
	OnBnClickedEditBtn();
} 

void CRcpView::CancelOrderFromTNo(long nTNo)
{
	InitSearch(TRUE);
	int nRow = m_vrOrder->GetItemRowFromTNo(nTNo);
	CXTPGridRows *pRows = m_xList.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
	m_xList.EnsureVisible(pRow);
	pRow = pRows->GetAt(nRow);
	m_xList.GetSelectedRows()->Select(pRow);
	OnBnClickedCancelOBtn();
}

void CRcpView::RcpStateFromTNo(long nTNo)
{
	InitSearch(TRUE);
	int nRow = m_vrOrder->GetItemRowFromTNo(nTNo);
	CXTPGridRows *pRows = m_xList.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
	m_xList.EnsureVisible(pRow);
	pRow = pRows->GetAt(nRow);
	m_xList.GetSelectedRows()->Select(pRow);
	OnBnClickedCancelABtn();
}

void CRcpView::OnCbnSelchangeRefreshCombo()
{
	CString strSecond;
	static int nSecond[] = {0xFFFF, 1, 3, 5, 10, 15, 20, 30, 40, 50, 60, 120, 300, 600};

	if(m_RefreshCombo.GetSafeHwnd())
		m_nDiscountSec = nSecond[m_RefreshCombo.GetCurSel()];

}

void CRcpView::OnNewRiderList()
{
	return;
	
}

void CRcpView::OnBnClickedShowNoticeBtn()
{
	if(!LF->POWER_CHECK(2008, "접수자 공지 등록", TRUE))
		return;

	CShowRcpNotice dlg;
	dlg.m_nCompanyCode = m_pBi->nDOrderTable;
	dlg.m_bIntegrated = m_pBi->bIntegrated;
	dlg.DoModal();
	RefreshList();
}

void CRcpView::AddRcpNotice(long nTNo, COleDateTime dt, CString strUser, CString strNotice, 
							BOOL bRequestEditOrder)
{

	CString strUser2 = "(" + strUser + ")";
	int i = 0;
	for(i = 0; i < m_pInfoForm->m_NoticeList.GetItemCount(); i++) 
	{
		if(m_pInfoForm->m_NoticeList.GetItemData(i) == nTNo)
		{
			m_pInfoForm->m_NoticeList.SetItemText(i, 0, dt.Format("[%H:%M:%S]"));
			m_pInfoForm->m_NoticeList.SetItemText(i, 1, strUser2);
			m_pInfoForm->m_NoticeList.SetItemText(i, 2, strNotice);
			m_pInfoForm->m_NoticeList.SetItemText(i, 3, bRequestEditOrder ? " " : "");
			break;
		}
	}

	if(i == m_pInfoForm->m_NoticeList.GetItemCount()) {
		m_pInfoForm->m_NoticeList.InsertItem(0, dt.Format("[%H:%M:%S]"));
		m_pInfoForm->m_NoticeList.SetItemText(0, 1, strUser2);
		m_pInfoForm->m_NoticeList.SetItemText(0, 2, strNotice);
		m_pInfoForm->m_NoticeList.SetItemText(0, 3, bRequestEditOrder ? " " : "");
		m_pInfoForm->m_NoticeList.SetItemData(0, nTNo);		
		if(!bRequestEditOrder)
			ShowRcpPopupControl(strNotice, strUser, dt);
	}
}


void CRcpView::ShowRcpPopupControl(CString strText, CString strWriter, COleDateTime dtTime)
{
	m_wndPopupControl.RemoveAllItems();

	// add text items.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(46, 16, 270, 41), "접수자 공지사항"));
	pItemText->SetBold(FALSE);

	CString strTime;
	strTime.Format("%s 님으로 부터 %s", strWriter, dtTime.Format("%H:%M:%S"));

	pItemText = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(46, 29, 400, 54), strTime));
	pItemText->SetHyperLink(FALSE);

	pItemText = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(46, 42, 460, 130), strText));
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(0, 61, 178));
	pItemText->SetTextAlignment(DT_LEFT|DT_WORDBREAK);
	pItemText->SetBold(TRUE);

	// letter icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(5, 12, 17, 24)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER), IMAGE_ICON, 32, 32, 0));
	pItemIcon->SetButton(FALSE);

	// close icon.
	pItemIcon = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(468, 14, 484, 30)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CLOSE), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// flag icon.
	pItemIcon = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(4, 49, 20, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_FLAG), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	// cross icon.
	pItemIcon = (CXTPPopupItem*)m_wndPopupControl.AddItem(
		new CXTPPopupItem(CRect(23, 49, 39, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CROSS), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	m_wndPopupControl.SetTheme(xtpPopupThemeOffice2003);
	//m_wndPopupControl.RedrawControl();

	m_wndPopupControl.GetPaintManager()->RefreshMetrics();
	
	CSize szPopup (500, 100);

	m_wndPopupControl.SetPopupAnimation((XTPPopupAnimation)1);
	m_wndPopupControl.SetShowDelay(5000);
	m_wndPopupControl.SetAnimateDelay(500);
	m_wndPopupControl.SetTransparency(200);
	m_wndPopupControl.SetPopupSize(szPopup);
	m_wndPopupControl.AllowMove(TRUE);
	m_wndPopupControl.Show(this);


}


void CRcpView::OnMoveOrder()
{
	CMkLock lock(&m_csOrder);

	int nSelItem = m_xList.GetSelectedItem();

	if(GetItemSecondCross(nSelItem))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	long nTNo = GetItemTNo(nSelItem);
	long nState = GetItemState(nSelItem);
	long nRiderCompany = GetItemRiderCompany(nSelItem);
	long nRNo = GetItemRNo(nSelItem);
 
	if(nState != STATE_PICKUP && nState != STATE_ALLOCATED) {
		MessageBox("배차,픽업 상태의 오더만 가능합니다", 
			"확인", MB_ICONINFORMATION);
		return;
	}

	COrderPassDlg dlg;

	if(dlg.DoModal() == IDOK) 
	{
		if(nRiderCompany == dlg.m_nRiderCompany &&
			nRNo == dlg.m_nRNo)
		{
			MessageBox("오더넘김 하려는 기사님이 현재 배차된 기사님과 같습니다", "확인", MB_ICONINFORMATION);
			return;
		}

		ChangeOrderRider(nTNo, nState, dlg.m_nRiderCompany, dlg.m_nRNo);
	}

	/*
	dlg.m_nCompanyCode = m_pBi->nCompanyCode;
	dlg.m_nDOrderTable = m_pBi->nDOrderTable;
	dlg.m_nCarType = GetItemCarType(nSelItem);


	long nTRNo = GetItemTNo(nSelItem);
	if(dlg.DoModal() != IDOK) return;

	GetStateChange()->Allocate(nTRNo, dlg.m_nRNo, GetItemState(nSelItem), dlg.m_nRCompanyCode);
	*/
}

void CRcpView::ChangeOrderRider(long nTNo, long nState, long nRiderCompany, long nRNo)
{
	if(nRiderCompany == 1122 ||
		nRiderCompany == 1123 ||
		nRiderCompany == 1124 ||
		nRiderCompany == 1125)
	{
		MessageBox("제휴 공유 오더는 넘김 기능을 사용하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "change_item_order_rider");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	if(nState == STATE_ALLOCATED)
		pCmd.AddParameter(OFFICE_ALLOCATED);
	else
		pCmd.AddParameter(OFFICE_PICKUP);

	long nRet = 0;

	if(pCmd.Execute())
		parRet->GetValue(nRet);

	if(nRet == 1)
	{
		MessageBox("해당 기사에게 오더넘김을 실행하였습니다", "확인", MB_ICONINFORMATION);
		RefreshList();
	}
}


void CRcpView::OnBnClickedShareOrder()
{ 
	if(m_pBi->nShareCode1 == 0 &&
		m_pBi->nShareCode2 == 0 &&
		m_pBi->nShareCode3 == 0 &&
		m_pBi->nShareCode4 == 0 &&
		m_pBi->nShareCode5 == 0)
	{
		CString strMsg;
		strMsg =  "오더를 공유할 수 있는 협력사가 설정되어있지 않습니다.\n";
		strMsg += "협력관계 구축과 관련된 사항은 로지소프트로 문의하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0) {
		MessageBox("공유/공유해제할 오더가 선택되지 않았습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	OrderRecord *ibi = m_vrCur->GetOrderRecord(nSelItem);
	long nState = GetItemState(nSelItem);

	if(nState != STATE_OK && nState != STATE_WAIT)
	{
		MessageBox("접수상태가 아닙니다. 오더공유/해제는 접수/대기상태만 가능합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(GetItemSecondCross(nSelItem))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	if(nState == STATE_WAIT)
	{
		if(ibi->bShareOrder == FALSE) //공유설정을 할거임
		{
			GetStateChange()->ChangeItemState(STATE_OK, TRUE);
			return;
		}
		else
		{
			MessageBox("대기 상태에서는 해제가 불가합니다.", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	if(LF->MakeShareOrder(GetItemTNo(nSelItem), ibi->bShareOrder))
	{
		RefreshList();
	}
}

void CRcpView::OnBnClickedAddOrder()
{
	EditOrder(TRUE);
}

void CRcpView::OnBnClickedTransInfo()
{
	CMkLock lock(&m_csOrder);

	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	long nTNo = GetItemTNo(nSelItem);
	long nCompany = GetItemCompany(nSelItem);

	LU->OpenTranDlg(nTNo, nCompany);

}

void CRcpView::OnBnClickedCopyOrder()
{
	CMkLock lock(&m_csOrder);

	int nSelItem = m_xList.GetSelectedItem();

	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	if(GetItemSecondCross(nSelItem))
	{
		CString strMsg;
		strMsg = "공유콜은 오더복제를 하실 수 없습니다\n";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CopyOrder(nSelItem, STATE_WAIT);
}

void CRcpView::CopyOrder(long nSelItem, long nState)
{
	if(GetItemState(nSelItem) == STATE_OK_ONLY_MAN ||
		GetItemState(nSelItem) == STATE_ALLOCATED ||
		GetItemState(nSelItem) == STATE_PICKUP)
	{
		if(MessageBox("이미 배차상태 오더입니다\r\n복제추가 하시겠습니까?", "확인", MB_YESNO) != IDYES)
		{
			return;
		}
	}

	CMkCommand pCmd(m_pMkDb, "insert_copied_order_3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetItemTNo(nSelItem));
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetItemCompany(nSelItem));
	pCmd.AddParameter(nState);

	if(!pCmd.Execute()) {
		MessageBox("추가 실패하였습니다!", "확인", MB_ICONINFORMATION);
	}
	else
	{
		AllRefresh();
	}
}

void CRcpView::InitBranchInfo()
{
	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);

		pBi->strSort = "";
		pBi->strFilter = "";
		pBi->strCID = "";
		pBi->dtLastRefresh = COleDateTime(2000, 1, 1, 1, 1, 1);
		pBi->bPartRefresh = FALSE;
		pBi->bPrePartRefresh = FALSE;
		pBi->nCurTab = 0;
		pBi->nLastSelItemNo = -1;
		pBi->nCurSel = -1;
		pBi->nCurCol = 0;
		pBi->bColAsc = TRUE;
		pBi->strPreCondition = "";
		pBi->strSortField = m_strSortField;

		pBi->dtFrom = COleDateTime::GetCurrentTime();
		pBi->dtTo = COleDateTime::GetCurrentTime();

		pBi->dtFrom.SetDateTime(pBi->dtFrom.GetYear(),pBi->dtFrom.GetMonth(),pBi->dtFrom.GetDay(),0,0,0);
		pBi->dtTo.SetDateTime(pBi->dtFrom.GetYear(),pBi->dtFrom.GetMonth(),pBi->dtFrom.GetDay(),23,59,59);
		/*pBi->dtTo.SetDateTime(pBi->dtFrom.GetYear(), pBi->dtFrom.GetMonth(), 
		pBi->dtFrom.GetDay(), 0, 0, 0);
		pBi->dtFrom = pBi->dtTo - COleDateTimeSpan(1, 0, 0, 0);*/

		pBi->nCondition1 = 0;
		pBi->nCondition2 = 0;
		pBi->strCondition2 = "";
		pBi->nRegionSection = 0;
	}
}

void CRcpView::ChangeBranch(CBranchInfo *pBi, BOOL bNotRefresh)
{
	if(m_pBi == pBi)
		return;

	m_pBi->strSort = m_strSort;
	m_pBi->strFilter = m_strFilter;
	m_pBi->strCID = m_strCID;
	m_pBi->nCurTab = m_CurTab;
	m_pBi->nLastSelItemNo = m_nLastSelItemNo;
	m_pBi->nCurSel = m_nCurSel;
	m_pBi->nCurCol = m_nCurCol;
	m_pBi->bColAsc = m_bColAsc;
	m_pBi->strPreCondition = m_strPreCondition;
	m_pBi->strSortField = m_strSortField;
	m_FromDT.GetTime(m_pBi->dtFrom);
	m_ToDT.GetTime(m_pBi->dtTo);

	m_pBi = pBi;

	m_strSort = m_pBi->strSort;
	m_strFilter = m_pBi->strFilter;
	m_strCID = m_pBi->strCID;
	m_CurTab = m_pBi->nCurTab;
	m_nLastSelItemNo = m_pBi->nLastSelItemNo;
	m_nCurSel = m_pBi->nCurSel;
	m_nCurCol = m_pBi->nCurCol;
	m_bColAsc = m_pBi->bColAsc;
	m_strPreCondition = m_pBi->strPreCondition;
	m_strSortField = m_pBi->strSortField;

	m_FromDT.SetTime(m_pBi->dtFrom);
	m_ToDT.SetTime(m_pBi->dtTo);
	m_dtLastForLimit = COleDateTime(2000, 1, 1, 1, 1, 1);

	m_vrOrder->SetIntegrated(m_pBi->bIntegrated);
	m_vrOrder->SetCompanyCode(m_pBi->nCompanyCode);
	m_vrOrder->SetDOrderCompany(m_pBi->nDOrderTable);
	//	m_vrOrder->SetUseNewRegion(m_pBi->bUseNewRegion);

	if(!bNotRefresh)
		AllRefresh();
}

void CRcpView::OnReportSortOrderChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify != NULL);

	AllRefresh();
}

void CRcpView::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	if(m_bLoadReportState)
	{
		CString strTemp; long nSize;
		SaveReportState(strTemp, nSize);
	}
}

void CRcpView::OnReportColumnWidthChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{

	if(m_bLoadReportState)
	{
		CString strTemp; long nSize;
		SaveReportState(strTemp, nSize);
	}
}

void CRcpView::OnDestroy()
{
	CFormView::OnDestroy();
	
	CString strTemp; long nSize;
	SaveReportState(strTemp, nSize);
}

void CRcpView::OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
 
	/*
	CXTPGridSelectedRows *pRows = m_xList.GetSelectedRows();

	if(NULL == pRows) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRow *pRow = pRows->GetAt(0);
	long nSel = pRow->GetIndex();
	pRows->Select(pRow);
	*/
}


void CRcpView::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return; 

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	int nCompany = GetItemRiderCompany(nRow);
	int nRNo = GetItemRNo(nRow);
	int nOrderCompany = GetItemCompany(nRow);
	long nTNo = GetItemTNo(nRow);
	long nState = GetItemState(nRow);
	long nPayType = GetItemPayType(nRow);
	long nConsignTNo = GetItemConsignTNo(nRow);
	long nConsignWayID = GetItemConsignWayID(nRow);
	CString sDestSido = GetItemConsignDestSido(nRow);
	//long nChargeLogi = GetItemChargeLogi(nRow);
	CString strStart = GetItemStart(nRow);
	CString strDest = GetItemDest(nRow);
	BOOL bShareOrder = GetItemShare(nRow);

	if(nCol == RIDER_NO_COL || nCol == RIDER_NAME_COL)		
	{
		if(nCompany != 0 && nRNo != 0)
		{ 
			if(nCol == RIDER_NO_COL)
				LU->ShowCallPhoneRiderDlg(nCompany, nRNo, nOrderCompany, FALSE);
			else
				LU->ShowRiderInfoDlg(nCompany, nRNo, nOrderCompany, nTNo, "", nState, nPayType);
		}
	}
	else if(nCol == CONSIGN_SUM_COL && nConsignTNo > 0)
	{		
		if(m_ui.bDeveloper)  // 개발후
			LU->OpenConsignLinkDlg(nTNo,nOrderCompany,NULL,NULL, nConsignTNo, nConsignWayID,sDestSido , NULL, TRUE);
			
	}
	else if(nCol == WNO_COL)
	{
		char buffer[10];
		int nWCompany = GetItemWCompany(nRow);
		int nWNo = GetItemWNo(nRow);
		CString strWName = GetItemWName(nRow);

		if(GetItemSecondCross(nRow))
			return;

		if(nWCompany == m_ui.nCompany &&
			nWNo == m_ui.nWNo)
			return;

		CMyMkMessenger *pMsg = LU->GetMessenger();

		if(pMsg)
		{
			pMsg->ShowMsgDlg(
				this, 
				"", 
				ltoa(nWCompany, buffer, 10),
				ltoa(nWNo, buffer, 10),
				ltoa(0, buffer, 10),
				LF->GetBranchInfo(nWCompany)->strBranchName,
				strWName);
		}
	}
	else
	{
		if(LU->m_pwndPane5 == NULL)
			return;

		int nSelItem = m_xList.GetSelectedItem();

		if(!LU->m_pwndPane5->IsHidden() )
		{
			LU->GetAllocatePane()->SetTNo(GetItemTNo(nSelItem), m_bShareOrderRefresh, GetItemCompany(nSelItem), 
				GetItemRiderCompany(nSelItem), GetItemRNo(nSelItem), GetItemTodayOrder(nSelItem));
			LU->GetAllocatePane()->SetCustomerRefresh();
			LU->GetAllocatePane()->NearOrderRefresh(GetItemTNo(nSelItem));
		}

		//if(GetItemState(nRow) == STATE_OK || GetItemState(nRow) == STATE_WAIT)
		{
			CAllocateBoardDlg *pDlg = LU->GetAllocateBoardDlg();
			if(pDlg)
			{
				if(pDlg->m_chkFindProperRider.GetCheck())
				{
					if(pDlg->m_bFinishTest ||
						!pDlg->m_bFinishTest && m_vrCur->GetOrderRecord(nSelItem)->nState < 11) 
					{
						CRect rcBase;
						m_xList.GetWindowRect(rcBase);

						pDlg->FindProperRiderLinearType(rcBase, GetItemTNo(nRow), 
							GetItemCarType(nRow),
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosY,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosY);

						/*
						if(pDlg->m_bLinearType)
							pDlg->FindProperRiderLinearType(rcBase, GetItemTNo(nRow), 
							GetItemCarType(nRow),
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosY,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosY);
						else
							pDlg->FindProperRider(rcBase, GetItemTNo(nRow),  
							GetItemCarType(nRow),
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nStartPosY,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosX,
							m_vrCur->GetOrderRecord(nSelItem)->nDestPosY);
							*/
					}
				}
			} 
		}

		//if(GetKeyState(VK_SHIFT) & 0x8000)
		//	OnBnClickedEditBtn();

		SetLastSelItemNo(m_xList.GetSelectedItem());
		OrderClickAutoMoveMap(m_vrCur->GetOrderRecord(nRow)->nStartPosX, m_vrCur->GetOrderRecord(nRow)->nStartPosY,
							m_vrCur->GetOrderRecord(nRow)->nRiderCompany, m_vrCur->GetOrderRecord(nRow)->nRNo);
	}

	RefreshMapForm(m_vrCur->GetOrderRecord(nRow));
}

void CRcpView::RefreshMapForm(OrderRecord *pOrder, BOOL bCIDPopup)
{
	if(m_pMapForm && pOrder)
	{
		BOOL bMoveMap = m_pMapForm->m_setinfo.nRcpMoveMap || 
						bCIDPopup && m_pMapForm->m_setinfo.nJoinWithCID;

		if(bCIDPopup)
		{
			if(m_wndTabControl.GetCurSel() != RCPPACE_MAP_FORM)
			{
				m_bAutoChangeMapForm = TRUE;
				m_wndTabControl.SetCurSel(RCPPACE_MAP_FORM);
			}

			m_pMapForm->RefreshShowType(SHOW_TYPE_BOTH);
		}


		if(bMoveMap)
		{ 
			if(m_wndTabControl.GetCurSel() == RCPPACE_MAP_FORM)
			{
				if(pOrder->nState >= STATE_WAIT && pOrder->nState <= STATE_FINISH)
				{
					if(pOrder->nRiderCompany > 0 && pOrder->nRNo > 0)
					{ 
						m_pMapForm->SetTraceRider(pOrder->nRiderCompany, pOrder->nRNo, pOrder);
					} 

					if(pOrder->nStartPosX > 0 && pOrder->nStartPosY > 0)
						m_pMapForm->AddStartPos(pOrder->nState < STATE_PICKUP, pOrder->nStartPosX, pOrder->nStartPosY, 
						pOrder->strStart.c_str(), pOrder->strSAddress.c_str());

					if(pOrder->nDestPosX > 0 && pOrder->nDestPosY > 0)
						m_pMapForm->AddDestPos(pOrder->nState >= STATE_PICKUP, pOrder->nDestPosX, pOrder->nDestPosY, 
						pOrder->strDest.c_str(), pOrder->strDAddress.c_str());
					else 
						m_pMapForm->DeleteDest();	

				}
			}			
		}
	}
}

void CRcpView::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CMkLock lock(&m_csOrder);

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	SetLastSelItemNo(m_xList.GetSelectedItem());

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_xList, pt);

}


void CRcpView::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	OnBnClickedEditBtn();
	SetLastSelItemNo(m_xList.GetSelectedItem());
}

void CRcpView::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	//if(m_ci.m_nCompanyCode > 500)
	//	return;

	if(!LF->GetCurBranchInfo()->bUseOrderBundle)
		return;

	//choi
	m_bRefreshOK = FALSE;
	m_bDragMode = TRUE; 
	m_ptDrag.x = -1;
	m_ptDrag.y = -1;
	SetCursor( m_hcMoveHold );
	SetCapture();
}

BOOL CRcpView::MakeCall(int nCompany, CString strPhone, long nType)
{
	CString strOrderCompanyPhone, strCallingLine, strOriginPhone, strDID;
	for(int i = 0; i < m_ba.GetCount(); i++) {
		CBranchInfo *pBi = m_ba.GetAt(i);
		if(nCompany == pBi->nCompanyCode) {
			CString strTemp1 = LF->GetNoneDashNumber(pBi->strPhone);
			if(strTemp1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
				strTemp1 = strTemp1.Right(strTemp1.GetLength() - m_ci.m_strDDD.GetLength());

			strOrderCompanyPhone = strTemp1;
			strCallingLine = pBi->strCallingLine;

			strDID = pBi->strLineGroup;
			if(strDID.Find(",") != -1)
				strDID = strDID.Mid(strDID.Find(",") + 1, strDID.Find(",", strDID.Find(",") + 1) - strDID.Find(",") - 1);

			break;
		}
	}

	if(strCallingLine.IsEmpty())
		strCallingLine = m_ba.GetAt(ZERO)->strCallingLine;
	
	if (nCompany < 0) {
		if (strCallingLine.IsEmpty())
			strCallingLine = "9";
	}
	else
		strCallingLine = LF->GetAutoDDDSetting(nCompany, strCallingLine);

	strPhone = LF->GetNoneDashNumber(strPhone);
	if(strPhone.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strPhone = strPhone.Right(strPhone.GetLength() - m_ci.m_strDDD.GetLength());

	if(strCallingLine.Find("A") != -1 && strPhone.Find("0") != 0)
		//strPhone = GetBranchInfo(nCompany)->strDDD + strPhone;
		strPhone = m_ci.m_strDDD + strPhone;

	strOriginPhone = strPhone;
	strPhone = strCallingLine + strPhone;

	if(m_pCTIForm->m_bConnected)
	{
		if(LF->GetBranchInfo(m_ui.nCompany)->bIPPBXType)
		{
			strDID = strDID + "OP" + strOriginPhone;
			m_pCTIForm->m_call.MakeCall(strDID, strPhone);
		}
		else
			m_pCTIForm->m_call.MakeCall(strOrderCompanyPhone, strPhone);

		MessageBox("전화걸기를 요청하였습니다.", 
			"전화걸기 시도", 
			MB_ICONINFORMATION);

		SaveCallingLog(strOriginPhone, nType);
		return TRUE;
	}
	else
	{
		char data[255] = {0,};
		STRCPY(data, "C",VL_END); 
		STRCAT(data, (LPSTR)(LPCTSTR) strOrderCompanyPhone,VL_END); //회사전화(CID프린트용)
		STRCAT(data, (LPSTR)(LPCTSTR) strPhone,VL_END);			//고객전화(발신용)
		if(LU->SendCopyDataToTelClient(data))
		{
			MessageBox("전화걸기를 요청하였습니다.", 
				"전화걸기 시도", 
				MB_ICONINFORMATION);

			SaveCallingLog(strOriginPhone, nType);
			return TRUE;
		}
		else
		{
			MessageBox("전화걸기 요청 실패\n텔클라이언트의 실행여부를 확인하시기 바랍니다.", 
				"전화걸기 실패", 
				MB_ICONINFORMATION);

			return FALSE;
		}
	}
}

void CRcpView::SaveCallingLog(CString sPhone, long nType)
{
	static COleDateTime dtDate(2000, 1, 1, 1,1,1);

	COleDateTime dt = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 0, 10);

	if(dtDate > dt)
		return;

	CMkCommand pCmd(m_pMkDb, "insert_calling_phone_log");
	pCmd.AddParameter(typeString, typeInput, sPhone.GetLength(), sPhone);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);

	pCmd.Execute();

	dtDate = COleDateTime::GetCurrentTime();
};

void CRcpView::OnBnClickedStateAllBtn()
{
	m_bAllCheck = !m_bAllCheck;

	m_btnStateRcp.SetCheck(m_bAllCheck);
	m_btnStateWait.SetCheck(m_bAllCheck);
	m_btnStateReserved.SetCheck(m_bAllCheck);
	m_btnStateOnlyMan.SetCheck(m_bAllCheck);
	m_btnStateAlloc.SetCheck(m_bAllCheck);
	m_btnStateFinish.SetCheck(m_bAllCheck);
	m_btnStateCancel.SetCheck(m_bAllCheck);
	m_btnStateEtc.SetCheck(m_bAllCheck);
	m_btnStatePickup.SetCheck(m_bAllCheck);

	RefreshFilterOnly(TRUE);

	/*
	if(m_btnStateAll.GetCheck())
	{
		m_btnStateRcp.SetCheck(0);
		m_btnStateWait.SetCheck(0);
		m_btnStateReserved.SetCheck(0);
		m_btnStateOnlyMan.SetCheck(0);
		m_btnStateAlloc.SetCheck(0);
		m_btnStateFinish.SetCheck(0);
		m_btnStateCancel.SetCheck(0);
		m_btnStateEtc.SetCheck(0);
		m_btnStatePickup.SetCheck(0);
	}
	*/

//	RefreshFilterOnly(TRUE);
}



void CRcpView::OnBnClickedStateRcpBtn()
{
	//if(m_btnStateRcp.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}



void CRcpView::OnBnClickedStateWaitBtn()
{
	//if(m_btnStateWait.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}

void CRcpView::OnBnClickedStateOnlyManBtn()
{
	//if(m_btnStateOnlyMan.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}

void CRcpView::OnBnClickedStateAllocBtn()
{
	//if(m_btnStateAlloc.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}

void CRcpView::OnBnClickedStatePickupBtn()
{
	//if(m_btnStatePickup.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}

void CRcpView::OnBnClickedStateFinishBtn()
{
	//if(m_btnStateFinish.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}



void CRcpView::OnBnClickedStateCancelBtn()
{
	//if(m_btnStateCancel.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}


void CRcpView::OnBnClickedStateEtcBtn()
{ 
	/*
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_aaaaa");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return;

	char szA[21] = "";
	char szB[21] = "";

	rs.GetFieldValue("sA", szA);
	rs.GetFieldValue("sB", szB);

	int i = 0;
	*/

	LU->m_paneManager.MoveWindow(CRect(300, 200, 600, 600));
	RefreshFilterOnly(TRUE);
}


void CRcpView::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
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
		if (IDC_REPORT_LIST_RCPPAGE == nID)
		{
			m_xList.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_xList.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				if(pCol->GetItemIndex() == RIDER_NO_COL || pCol->GetItemIndex() == RIDER_NAME_COL)
				{
					if(!m_vrCur->GetOrderRecord(pRow->GetIndex())->bCross)
					{
						CMakeHtmlTable htable;
						long nRiderCompany = m_vrCur->GetOrderRecord(pRow->GetIndex())->nRiderCompany;
						long nRNo = m_vrCur->GetOrderRecord(pRow->GetIndex())->nRNo;
						CString strRName = m_vrCur->GetOrderRecord(pRow->GetIndex())->strRName.c_str();

						long nTNo = m_vrCur->GetOrderRecord(pRow->GetIndex())->nTNo;
						long bTodayOrder = m_vrCur->GetOrderRecord(pRow->GetIndex())->bTodayOrder;

						

						if(GetRiderInfoToolTip(&htable, nRiderCompany, nRNo, nTNo, bTodayOrder))
						{
							CString strTitle;
							strTitle.Format("%s,%d번", strRName, nRNo);
							htable.SetTitle(strTitle);
							htable.SetTableBorder(1);
							pNotify->ti->sTooltip = htable.GetHtmlTable();
							pt = *pNotify->pt;
							pt.x += 5;
							pt.y += 20;
							*pNotify->pt = pt;
						}
						/*
						if(GetRiderOrderHtmlTable(&htable, nRiderCompany, nRNo))
						{
							CString strTitle;
							strTitle.Format("%s/%s,%d번", 
								m_ci.GetName(nRiderCompany), 
								m_ci.GetBranchName(nRiderCompany),
								nRNo);
							htable.SetTitle(strTitle);
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
				else if(pCol->GetItemIndex() == TRANS_COL) 
				{
					CMakeHtmlTable htable;

					if(MakeTransInfo(&htable, pRow->GetIndex()))
					{
						htable.SetTitle("탁송정보");
						htable.SetTableBorder(1);
						pNotify->ti->sTooltip = htable.GetHtmlTable();
						pt = *pNotify->pt;
						pt.x += 5;
						pt.y += 20;
						*pNotify->pt = pt;
					}
				}
				else if(pCol->GetItemIndex() == CONSIGN_SUM_COL) 
				{
					//LU->OpenConsignLinkDlg()
					
				}
				else if(pCol->GetItemIndex() == START_DONG_COL || pCol->GetItemIndex() == DEST_DONG_COL)
				{
					if(m_vrCur->GetOrderRecord(pRow->GetIndex())->bCross)
						return;
					
					CMakeHtmlTable htable; 
					CString sDetail = "";

					if(pCol->GetItemIndex() == START_DONG_COL)
						sDetail = m_vrCur->GetOrderRecord(pRow->GetIndex())->strSDetail.c_str();
					else if(pCol->GetItemIndex() == DEST_DONG_COL)
						sDetail = m_vrCur->GetOrderRecord(pRow->GetIndex())->strDDetail.c_str();

					htable.AddCol(sDetail);
					htable.AddRow();

					htable.SetTitle("");
					htable.SetTableBorder(1);
					pNotify->ti->sTooltip = htable.GetHtmlTable();
					pt = *pNotify->pt;
					pt.x += 5;
					pt.y += 20;
					*pNotify->pt = pt;
				}
				else if(pCol->GetItemIndex() == RCP_COMPANY_COL ||
					pCol->GetItemIndex() == RIDER_NO_COL || 
					pCol->GetItemIndex() == RIDER_NAME_COL)
				{
					if(m_vrCur->GetOrderRecord(pRow->GetIndex())->bCross)
					{
						CMakeHtmlTable htable;
						long nRiderCompany = m_vrCur->GetOrderRecord(pRow->GetIndex())->nRiderCompany;
						long nOrderCompany = m_vrCur->GetOrderRecord(pRow->GetIndex())->nCompany;

						if(pCol->GetItemIndex() == RCP_COMPANY_COL)
							GetCompanyInfoToolTip(&htable, nOrderCompany);
						else
							GetCompanyInfoToolTip(&htable, nRiderCompany);

						htable.SetTitle("타회사정보"); 
						htable.SetTableBorder(1);
						pNotify->ti->sTooltip = htable.GetHtmlTable();
						pt = *pNotify->pt;
						pt.x += 5;
						pt.y += 20;
						*pNotify->pt = pt;
					}
				}


				/*
				else
				{
				pNotify->ti->sTooltip = m_vrCur->GetOrderRecord(pRow->GetIndex())->info[pCol->GetItemIndex()].c_str();
				pt = *pNotify->pt;
				pt.x += 5;
				pt.y += 20;
				*pNotify->pt = pt;
				}
				*/
			}

		} //if
	} //if
} //End NotifyDisplayTooltip


BOOL CRcpView::GetRiderOrderHtmlTable(CMakeHtmlTable *pTable, long nCompany, long nRNo)
{	
	long nCount = 0;
	long nSum = 0;
	char buffer[10];

	OrderRecordList &OrderList = m_vrOrder->GetOrderRecordList();
	OrderRecordList::iterator it;

	if(nCompany == 0 || nRNo == 0)
		return FALSE;
	if(m_ci.GetShareCode1(nCompany) == m_ci.m_nShareCode1)
	{
		for(it = OrderList.begin(); it != OrderList.end(); it++)
			GetRiderOrderHtmlTableSubRoutine(it->second, pTable, nCompany, nRNo, nCount, nSum);

		for(it = m_mapOtherOrder.begin(); it != m_mapOtherOrder.end(); it++)
			GetRiderOrderHtmlTableSubRoutine(it->second, pTable, nCompany, nRNo, nCount, nSum);

		if(nCount > 0) 
		{
			pTable->AddCol("합계");
			pTable->AddCol(CString(ltoa(nCount, buffer, 10)) + "건");
			pTable->AddCol(CString(ltoa(nSum, buffer, 10)) + "원");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddCol("");
			pTable->AddRow();
			return TRUE;
		}
	}
	else
	{
		GetCompanyInfoToolTip(pTable, nCompany);
		return TRUE;
	}	

	return FALSE;
}


BOOL CRcpView::GetRiderInfoToolTip(CMakeHtmlTable *pTable, long nCompany, long nRNo, long nTNo, BOOL bTodayOrder)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_info_with_company_1");
	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(bTodayOrder);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nRNo);

	if(!pRs.Execute(&pCmd))
		return FALSE;
 
	if(pRs.GetRecordCount() == ZERO)
		return FALSE;
 
	CString strCompanyName, strCompanyTel, strCompanyOfficeTel, strID, strHp;

	pRs.GetFieldValue("sCompanyName", strCompanyName);
	pRs.GetFieldValue("sCompanyTel", strCompanyTel);
	pRs.GetFieldValue("sCompanyOfficeTel", strCompanyOfficeTel);
	pRs.GetFieldValue("sID", strID);
	pRs.GetFieldValue("sHp", strHp);

	pTable->AddCol("회사명");
	pTable->AddCol(strCompanyName);
	pTable->AddRow();
	pTable->AddCol("대표번호");
	pTable->AddCol(LF->GetDashPhoneNumber(strCompanyTel));
	pTable->AddRow();
	pTable->AddCol("상황실번호");
	pTable->AddCol(LF->GetDashPhoneNumber(strCompanyOfficeTel));
	pTable->AddRow();
	pTable->AddCol("PDA번호");
	pTable->AddCol(LF->GetDashPhoneNumber(strID));
	pTable->AddRow();
	pTable->AddCol("회사명");
	pTable->AddCol(LF->GetDashPhoneNumber(strHp));
	pTable->AddRow();

	return TRUE;
}

void CRcpView::GetCompanyInfoToolTip(CMakeHtmlTable *pTable, long nCompany)
{
	pTable->AddCol("회사명");
	pTable->AddCol(m_ci.GetName(nCompany));
	pTable->AddCol("대표번호");
	pTable->AddCol(m_ci.GetPhone(nCompany));
	pTable->AddCol("상황실");
	pTable->AddCol(m_ci.GetPhone(nCompany, TRUE));
}

void CRcpView::GetRiderOrderHtmlTableSubRoutine(OrderRecord &order, CMakeHtmlTable *pTable,
												long nCompany, long nRNo, long &nCount, long nSum)
{
	if(order.nRiderCompany == nCompany && order.nRNo == nRNo &&
		LF->IsAllocOrder(order.nState))
	{
		CString strTime;

		pTable->AddCol(nCount + 1);
		pTable->AddImageList(LF->GetImageNumber(order.nState), "");
		pTable->AddCol(m_ci.GetName(order.nCompany) + "/" + 
			m_ci.GetBranchName(order.nCompany));
		pTable->AddCol(order.strStart.c_str());
		pTable->AddCol(order.strDest.c_str());
		pTable->AddCol(order.dtState.Format("%H:%M"));
		pTable->AddCol(LF->GetMyNumberFormat(order.nCharge));
		pTable->AddCol(LF->GetCarTypeFromLong(order.nCarType));
		pTable->AddCol(LF->GetWayTypeFromLong(order.nWayType));
		pTable->AddCol(LF->GetRunTypeFromLong(order.nRunType));
		pTable->AddRow();

		nCount++;
		nSum += order.nCharge;
	}
}

BOOL CRcpView::GetOrderInfoHtmlTable(CMakeHtmlTable *pTable, long nTNo)
{
	OrderRecordList mapOrderRecord = m_vrOrder->GetOrderRecordList();
	OrderRecordList::iterator it = mapOrderRecord.find(nTNo);

	if(it == mapOrderRecord.end())
	{
		it = m_mapOtherOrder.find(nTNo);
		if(it == m_mapOtherOrder.end())
			return FALSE;
	}

	if(m_ci.IsChildCompany(it->second.nCompany))
	{
		pTable->AddCol("의뢰");
		pTable->AddCol(CString(it->second.strCName.c_str()) + "(" + it->second.strOPhone.c_str() + ")");
		pTable->AddRow();
	}

	pTable->AddCol("출/도");
	pTable->AddCol(CString(it->second.strStart.c_str()) + "/" + it->second.strDest.c_str());
	pTable->AddRow();
	pTable->AddCol("분류");
	pTable->AddCol(LF->GetPayTypeFromLong(it->second.nPayType, 1) + 
		LF->GetCarTypeFromLong(it->second.nCarType, 1) + 
		LF->GetWayTypeFromLong(it->second.nWayType, 1) +
		LF->GetRunTypeFromLong(it->second.nRunType, 1));
	pTable->AddRow();
	pTable->AddCol("요금");
	pTable->AddCol(LF->GetMyNumberFormat(it->second.nCharge));
	pTable->AddRow();
	pTable->AddCol("적요");
	pTable->AddCol(CString(it->second.strEtc.c_str()));
	pTable->AddRow();
	return TRUE;
}

void CRcpView::OnBnClickedPickupBtn()
{
	GetStateChange()->ChangeItemState(STATE_PICKUP);
}

void CRcpView::MoveOrder(CBranchInfo *pBi, BOOL bCopy)
{
	if(pBi->nCompanyCode == m_pBi->nCompanyCode &&
		pBi->bIntegrated == m_pBi->bIntegrated) {
			MessageBox("다른 지사를 선택하십시오!", "오더 이동실패", MB_ICONEXCLAMATION);
	}
	else if(pBi->bIntegrated) {
		MessageBox("통합보기로 이동할 수 없습니다.", "오더 이동실패", MB_ICONEXCLAMATION);
	}
	else
	{ 
		//CWaitCursor wait;
		long k = -1, nTNo, nState;

		POSITION pos = m_xList.GetSelectedRows()->GetFirstSelectedRowPosition();

		while(pos)
		{

			k =   m_xList.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
			if(k >= 0) {
				//if(GetItemSecondCross(k) && (GetItemPreventGroupCancel(k) || m_ci.m_bPreventGroupCancel) )
				if(GetItemSecondCross(k))
				{
					CString strMsg;
					strMsg = "2차 크로스배차된 오더를 이동할 수 없습니다.";
					MessageBox(strMsg, "확인", MB_ICONINFORMATION);
					continue;;
				}
				else {
					nTNo = GetItemTNo(k);
					nState = GetItemState(k);
					/*
					CMkCommand pCmd(m_pMkDb, "change_order_company3_1");
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), nState);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
					*/

					CMkCommand pCmd(m_pMkDb, "move_order_company_to_company_1");
					CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
					pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
					pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
					pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bCopy);

					if(pCmd.Execute()) 
					{
						long nRet; parRet->GetValue(nRet);

						if(nRet == 100)
						{
							MessageBox("이동하려는 지사에 공동정산 잔액이 부족하여 이동하실 수 없습니다", "확인", MB_ICONINFORMATION);
						}
						

						RefreshList();
					}
				}
			}

			//			if(FALSE == m_pBi->bIntegrated) /* 해당행이 삭제 되었으므로 다시 선택된 행을 찾는다 올 가능성 큼 */
			//			{
			//				pos = m_xList.GetSelectedRows()->GetFirstSelectedRowPosition();
			//			}
		}
	}
}

void CRcpView::InitSearch(BOOL bNoCondition)
{ 
	m_btnStateAll.SetCheck(0);
	m_btnStateWait.SetCheck(0);
	m_btnStateReserved.SetCheck(0);
	m_btnStateRcp.SetCheck(0);
	m_btnStateAlloc.SetCheck(0);
	m_btnStateOnlyMan.SetCheck(0);
	m_btnStatePickup.SetCheck(0);
	m_btnStateFinish.SetCheck(0);
	m_btnStateCancel.SetCheck(0);
	m_btnStateEtc.SetCheck(0);

	m_nShMyRider = -1;
	m_nShMyCall = -1;
	m_nShHideCrossCall = -1;
	m_nShShowCrossCall = -1;
	m_nShScheduleOrder = -1;
	m_nShInterOrder = -1;

	ClickSeachCheckBox(IDC_SEARCH_MY_RIDER_CHECK, m_nShMyRider, "자사기사");
	ClickSeachCheckBox(IDC_MY_CALL_CHECK, m_nShMyCall, "본인콜");
	ClickSeachCheckBox(IDC_HIDE_CROSS_CALL_CHECK, m_nShHideCrossCall, "크로스미표시");
	ClickSeachCheckBox(IDC_SHOW_CROSS_CALL_CHECK, m_nShShowCrossCall, "공유콜");
	ClickSeachCheckBox(IDC_SCHEDULE_ORDER_CHECK, m_nShScheduleOrder, "정기오더");
	ClickSeachCheckBox(IDC_INTERORDER_CHECK, m_nShInterOrder, "인터넷접수");

	if(!bNoCondition)
	{
		/*
		if(AfxGetApp()->GetProfileInt("RcpPage", "state1", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state2", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state3", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state4", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state5", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state6", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state7", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state8", 1) &&
			AfxGetApp()->GetProfileInt("RcpPage", "state9", 1))
		{
			m_btnStateAll.SetCheck(1);
		}
		else
		{
		*/
			m_btnStateRcp.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state1", 1));
			m_btnStateWait.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state2", 1));
			m_btnStateReserved.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state3", 1));
			m_btnStateOnlyMan.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state4", 1));
			m_btnStateAlloc.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state5", 1));
			m_btnStatePickup.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state6", 1));
			m_btnStateFinish.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state7", 1));
			m_btnStateCancel.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state8", 1));
			m_btnStateEtc.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state9", 1));
		//}
	}
	else
	{
		m_btnStateAll.SetCheck(1);
	}

	m_dtLastRefreshByShareCall = COleDateTime(2000, 1, 1, 1, 1, 1);
	m_dtLastRefresh = COleDateTime(2000, 1, 1, 1, 1, 1);

	m_chkInterOrder.SetCheck(0);
	OnBnClickedClearAllCheckBtn();
	OnBnClickedDeleteSearchTextBtn();

	m_DateBtn.OnMenuToday();
	OnBnClickedSearchBtn();	
}


void CRcpView::OnBnClickedInitSearchBtn()
{
	InitSearch();
	
	CXTPGridRows *pRows = m_xList.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(0);
	m_xList.EnsureVisible(pRow);
	pRow = pRows->GetAt(0);
	m_xList.GetSelectedRows()->Select(pRow);
}


void CRcpView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CRcpView::MakeTransInfo(CMakeHtmlTable *table, long nIndex)
{
	CXTPGridColumn *pColumn = NULL;

	CString str = m_vrCur->GetOrderRecord(nIndex)->info[TRANS_COL].c_str();
	long nCompany = m_vrCur->GetOrderRecord(nIndex)->nCompany;
	long nTNo = m_vrCur->GetOrderRecord(nIndex)->nTNo;

	if(str == "")
		return FALSE;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_trans_info");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if(!pRs.Execute(&pCmd)) return FALSE;

	if(pRs.GetRecordCount() != 0) 
	{
		CString sStart, sDest, sExpressName, sExpressNumber, sEtc, sName, sItemNo;
		COleDateTime dtDeparture, dtArrival, dtRegister;

		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("sExpressName", sExpressName);
		pRs.GetFieldValue("sExpressNumber", sExpressNumber);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sItemNo", sItemNo);
		pRs.GetFieldValue("dtDeparture", dtDeparture);
		pRs.GetFieldValue("dtArrival", dtArrival);
		pRs.GetFieldValue("dtRegister", dtRegister);

		table->AddCol("출발지");
		table->AddCol(sStart);
		table->AddRow();
		table->AddCol("도착지");
		table->AddCol(sDest);
		table->AddRow();
		table->AddCol("고속버스");
		table->AddCol(sExpressName);
		table->AddRow();
		table->AddCol("차량번호");
		table->AddCol(sExpressNumber);
		table->AddRow();
		table->AddCol("송장번호");
		table->AddCol(sItemNo);
		table->AddRow();
		table->AddCol("도착시간");
		table->AddCol(dtArrival.Format("%m:%d %H:%M"));
		table->AddRow();
		table->AddCol("출발시간");
		table->AddCol(dtDeparture.Format("%m:%d %H:%M"));
		table->AddRow();
		table->AddCol("등록시간");
		table->AddCol(dtRegister.Format("%m:%d %H:%M"));
		table->AddRow();
		table->AddCol("적요");
		table->AddCol(sEtc);
		table->AddRow();
		table->AddCol("등록자");
		table->AddCol(sName);
		table->AddRow();

		return TRUE;
	}

	return FALSE;
}


void CRcpView::OnBnClickedStateStateReservedBtn()
{
	m_btnStateReserved.SetCheck(!m_btnStateReserved.GetCheck());

	if(m_btnStateReserved.GetCheck())
	{
		m_btnStateAll.SetCheck(0);
	}

	RefreshFilterOnly();
}

void CRcpView::RefreshStateSecondSort()
{

	CString strOrderSort = AfxGetApp()->GetProfileString("RcpPage", "OrderStateSort", ""); 
	MAP_ORDER_STATE_SECOND_SORT_MAP *pMap = m_vrCur->GetSecondSortMap();

	pMap->clear();

	long nFirstFind = 0;
	long nSecondFind = 0;
	long nState = 0;
	CComboBox *pCmb = NULL;

	for(int i=0; i<LF->GetCommaCount(strOrderSort); i++)
	{
		nSecondFind = strOrderSort.Find(";", nFirstFind);
		nState = _ttoi(strOrderSort.Mid(nFirstFind, nSecondFind - nFirstFind));

		MAP_ORDER_STATE_SECOND_SORT_MAP::iterator it = pMap->find(nState);

		if(it != pMap->end())
			continue;

		pMap->insert(MAP_ORDER_STATE_SECOND_SORT_MAP::value_type(nState, i));

		nFirstFind = nSecondFind + 1;
	}
}

void CRcpView::OnBnClickedSetInitSearchBtn()
{
	CSetRcpPageDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_nReserveShowCount = AfxGetApp()->GetProfileInt("RcpPage", "ReserveCount", 0);
		m_bStateSecondSort = AfxGetApp()->GetProfileInt("RcpPage", "StateSecondSort", 0);
		m_bGetCustomerMemo = AfxGetApp()->GetProfileInt("RcpPage", "GetCustomerMemo", 0);
		m_bUseCardOkNumberAddColumn = AfxGetApp()->GetProfileInt("RcpPage", "CardOkNumberAddColumn", 0);
		m_bIgnoreCheckState = AfxGetApp()->GetProfileInt("RcpPage", "IgnoreCheckState", 1); 
		m_bRemoveSearch = AfxGetApp()->GetProfileInt("RcpPage", "RemoveSearch", 0);
		m_bAddTacksongCharge = AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongCharge", 0);
		m_bAddTacksongDrivingCharge = AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongDrivingCharge", 0);
		m_bSearchWithNoWName = AfxGetApp()->GetProfileInt("RcpPage", "SearchWithNoWName", 0);

		if(LF->IsThisCompany("하나로퀵"))
			m_bSearchWithNoWName = TRUE;
	
		RefreshStateColor();
		LoadListFont(TRUE);
		RefreshStateSecondSort();

		if(dlg.m_bShowMapForm)
			AddMapForm(TRUE);
	}
}

void CRcpView::OnCloseWebOrder()
{
	if(m_pWebOrderDlg)
	{
		RefreshList();
		m_pWebOrderDlg->ShowWindow(SW_HIDE);		
	}
}

void CRcpView::OnOtherAllocate()
{
	CString strTemp;
	int nItem = m_xList.GetSelectedItem();

	if(nItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	if(GetItemSecondCross(nItem))
	{
		CString strMsg;
		strMsg = "전화번호가 표시되지 않은 크로스콜은 타기사 개별배차를 하실 수 없습니다.\n";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	LU->OpenOtherAllocateDlg(GetItemTNo(nItem), GetItemCompany(nItem), GetItemState(nItem), GetItemDeposit(nItem));

	//Allocate(dlg.m_nTNo, dlg.m_nRNo, GetItemState(nItem), dlg.m_nRiderCompany);
}

void CRcpView::OnMenuSendSms()
{
	long nIndex = m_xList.GetSelectedItem();

	if(GetItemSecondCross(nIndex))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더에 SMS를 보내실수 없습니다.\n";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CString str = GetItemPhone(nIndex);

	SendSms(GetItemCompany(nIndex), str);
}

void CRcpView::OnMenuAllocateSendSms()
{
	long nIndex = m_xList.GetSelectedItem();

	if(GetItemSecondCross(nIndex))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더에 SMS를 보내실수 없습니다.\n";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CString str = GetItemPhone(nIndex);

	SendSms(GetItemCompany(nIndex), str, true);
}

void CRcpView::SendSms(long nCompany, CString sPhone, bool bAllocate)
{ 
	CString strRiderPhone;
	if (bAllocate) {
		int nSelItem = m_xList.GetSelectedItem();
		CVirtualRecord *pRecord = (CVirtualRecord*)m_xList.GetSelectedRows()->GetAt(0)->GetRecord();
		OrderRecord *order = pRecord->GetOrderRecord(nSelItem);
		strRiderPhone = LF->GetRiderPhone(order->nRiderCompany, order->nRNo);

		if (strRiderPhone.IsEmpty()) {
			MessageBox("기사가 배차된 오더만 문자를 전송할 수 있습니다.", "알림", MB_ICONINFORMATION);
			return;
		}
	}

	CCustomerSmsDlg2 dlg(NULL, bAllocate ? POPUP_ALLOCATE : POPUP_CUSTOMER);
	dlg.m_strCustomerPN = sPhone;
	dlg.m_strRiderPN = strRiderPhone;
	dlg.m_strCustomerPN = dlg.m_strCustomerPN.GetLength() > 0 ? LF->GetNoneDashNumber(dlg.m_strCustomerPN) : "";
	dlg.m_nCompany = nCompany; //LF->GetCurBranchInfo()->nCompanyCode;//m_ci.m_nCompanyCode;
	dlg.m_nContent = bAllocate ? 2 : 0; //  2번 = 배차관련, 0번 = 임의 고객에 메세지전송

	if(IDOK == dlg.DoModal())
	{
		CString strEtc;
		dlg.m_strRecvPhone = LF->GetNoneDashNumber(dlg.m_strRecvPhone);
		dlg.m_strCustomerPN = LF->GetNoneDashNumber(dlg.m_strCustomerPN);

		COleDateTime dtDate(COleDateTime::GetCurrentTime());

		dtDate.SetDateTime(dlg.m_dtReservationDate.GetYear(), dlg.m_dtReservationDate.GetMonth(),
			dlg.m_dtReservationDate.GetDay(), dlg.m_dtReservationTime.GetHour(), 
			dlg.m_dtReservationTime.GetMinute(), dlg.m_dtReservationTime.GetSecond());

		BOOL bOk = FALSE;

		long nIndex = m_xList.GetSelectedItem();
		COleDateTime dtRcp = GetItemDtRcp(nIndex);

		if(dlg.m_strMsg.Find("[시간]") >= 0)
			dlg.m_strMsg.Replace("[시간]", dtRcp.Format("%H:%M"));

		if(dlg.m_strMsg.Find("[년월일]") >= 0)
			dlg.m_strMsg.Replace("[년월일]", dtRcp.Format("%Y/%m/%d"));

		if(dlg.m_strMsg.Find("[퀵회사명]") >= 0)
			dlg.m_strMsg.Replace("[퀵회사명]", m_ci.GetCompanyName(GetItemCompany(nIndex)));

		if(dlg.m_strMsg.Find("[기사명]") >= 0)
			dlg.m_strMsg.Replace("[기사명]", GetItemRName(nIndex));

		if(dlg.m_bReservation)
			bOk = LF->SendSmsNewRev(nCompany > 0 ? nCompany : m_ci.m_nCompanyCode, 777, dlg.m_strCustomerPN, dlg.m_strRecvPhone, dlg.m_strMsg, "접수프로그램(임의)", "", "", dtDate);
		else
			bOk = LF->SendSmsNew(nCompany > 0 ? nCompany : m_ci.m_nCompanyCode, 777, dlg.m_strCustomerPN, dlg.m_strRecvPhone, dlg.m_strMsg, "접수프로그램(임의)", "", "");

		if(bOk) 
		{
			MessageBox("전송되었습니다.", "전송성공", MB_ICONINFORMATION);
		}
		else {
			MessageBox("SMS 전송을 실패하였습니다.", "전송실패", MB_ICONINFORMATION);
		}
	}
}

void CRcpView::OnBnClickedShowCrossCallCheck()
{
	ClickSeachCheckBox(IDC_SHOW_CROSS_CALL_CHECK, m_nShShowCrossCall, "공유콜");
}

void CRcpView::OnShowRiderPosBtn()
{
	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem > 0)
	{
		long nCompany = GetItemRiderCompany(nSelItem);
		long nRNo = GetItemRNo(nSelItem);

		if(nCompany == 0)
		{
			MessageBox("배차된 오더만 기사위치를 볼 수 있습니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		CREATE_MODALESS(CRiderTraceMapDlg, this);
		pDlg->m_nCompany = nCompany;
		pDlg->m_nRNo = nRNo;
		SHOW_MODALESS(CRiderTraceMapDlg, this);
		pDlg->MoveRider();
	}
}

void CRcpView::OnNMSetfocusDatefrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(LU->GetAllocatePane() != NULL)
	{
		if(!LU->m_pwndPane5->IsHidden())
			LU->GetAllocatePane()->m_edtSearch.SetFocus();
	}

	*pResult = 0;
}

void CRcpView::RemoveSearch(BOOL bSearchFilter)
{
	for(int i=0; i<SEARCH_EDIT_COUNT; i++)
	{
		GetDlgItem(searchEditBox1[i])->SetWindowText("");
		GetDlgItem(searchEditBox2[i])->SetWindowText("");

		if(i<MAX_REGION_SELECT_COUNT)
		{
			m_nSelectedRegionStartDongID[i] = -1;
			m_nSelectedRegionDestDongID[i] = -1;
		}
	}

	m_edtShowRiderInfo.SetWindowText("");

	if(bSearchFilter)
		ChangeSearchFilter();
}

void CRcpView::OnBnClickedDeleteSearchTextBtn()
{
	RemoveSearch(TRUE);	
}

void CRcpView::OnBnClickedShareSearchBtn()
{
	RefreshList("", "", NULL, TRUE);
}

void CRcpView::ClickSeachCheckBox(UINT nFlag, long &nState, CString sTitle)
{
	nState = ++nState % CHECK_STATE_COUNT;

	CXTPButtonUniCode *pWnd = (CXTPButtonUniCode*)GetDlgItem(nFlag);

	CString sTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Right' VerticalAlignment='Center'>";

	if(nState > CHECK_STATE_NO_CHECK)
	{ 
		pWnd->SetCheck(TRUE);

		if(nState == CHECK_STATE_O)
			sTemp += "<Run Foreground='Red' FontWeight='Normal'>"+ sTitle + " O</Run></TextBlock>" ;
		else if(nState == CHECK_STATE_X)
			sTemp += "<Run Foreground='Blue' FontWeight='Normal'>"+ sTitle + " X</Run></TextBlock>" ;
	}
	else
	{
		pWnd->SetCheck(FALSE);	
		sTemp += "<Run Foreground='Black' FontWeight='Normal'>"+ sTitle + "</Run></TextBlock>" ;
	}

	pWnd->SetMarkupText(sTemp);

	ChangeSearchFilter();
	DisplaySearchInfo();
}							

void CRcpView::OnBnClickedSearchMyRiderCheck()
{
	ClickSeachCheckBox(IDC_SEARCH_MY_RIDER_CHECK, m_nShMyRider, "자사기사");
}


CRect CRcpView::GetAllocatePaneRect() 
{ 
	CRect rc = LU->m_pwndPane5->GetPaneWindowRect();  
	//CRect rc; m_pAllocatePane->GetWindowRect(rc); 

	long nWidth = rc.Width();
	long nHeight = rc.Height();  

	rc.left = (AfxGetApp()->GetProfileInt("AllocatePaneDlg", m_ui.strID + "left", rc.left));
	rc.top = (AfxGetApp()->GetProfileInt("AllocatePaneDlg", m_ui.strID + "top", rc.top));
	rc.right = (AfxGetApp()->GetProfileInt("AllocatePaneDlg", m_ui.strID + "right", rc.right));
	rc.bottom = (AfxGetApp()->GetProfileInt("AllocatePaneDlg", m_ui.strID + "bottom", rc.bottom));

	rc.left -= 3;
	rc.top -= 25; // 전체 부분을 못가져 오는거 같은 다시 확인해야함

	rc.right = rc.left + nWidth; 
	rc.bottom = rc.bottom + 3;

	return rc;
}

void CRcpView::SaveAllocatePaneLocation()  
{  
	CRect rc = LU->m_pwndPane5->GetPaneWindowRect();
	//CRect rc; m_pAllocatePane->GetWindowRect(rc); 

	if(LU->m_pwndPane5->IsFloating() == FALSE)
	{
		rc.left = 0;
		rc.right = 0;
	}		

	AfxGetApp()->WriteProfileInt("AllocatePaneDlg", m_ui.strID + "left", rc.left);
	AfxGetApp()->WriteProfileInt("AllocatePaneDlg", m_ui.strID + "right", rc.right);
	AfxGetApp()->WriteProfileInt("AllocatePaneDlg", m_ui.strID + "top", rc.top);
	AfxGetApp()->WriteProfileInt("AllocatePaneDlg", m_ui.strID + "bottom", rc.bottom);

}

void CRcpView::OnBnClickedMyCallCheck()
{
	ClickSeachCheckBox(IDC_MY_CALL_CHECK, m_nShMyCall, "본인콜");
}

void CRcpView::OnBnClickedHideCrossCallCheck()
{
	ClickSeachCheckBox(IDC_HIDE_CROSS_CALL_CHECK, m_nShHideCrossCall, "크로스미표시");
}

void CRcpView::OnBnClickedScheduleOrderCheck()
{
	ClickSeachCheckBox(IDC_SCHEDULE_ORDER_CHECK, m_nShScheduleOrder, "정기오더");
}

void CRcpView::OnBnClickedWebOrderCheck()
{
	ChangeSearchFilter();
}

void CRcpView::OnBnClickedWebOrderBtn()
{
	if(m_pWebOrderDlg == NULL)
	{
		m_pWebOrderDlg = new CWebOrderDlg(this);
		m_pWebOrderDlg->Create(IDD_WEBORDER_DLG, this);
	}

	m_pWebOrderDlg->ShowWindow(SW_SHOW);	
}

void CRcpView::OnBnClickedRefreshIcBtn()
{
	((CMainFrame*)AfxGetMainWnd())->RefreshIntercallConnList();
	OnBnClickedSearchBtn();
}

void CRcpView::OnCurOrderState()
{
	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem == -1) return;

	COleDateTime dtRcp = GetItemCNameDtRcp(nSelItem);
	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	if(GetItemSecondCross(nSelItem))
	{
		MessageBox("크로스 배차된 오더는 확인 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if((dtRcp.GetYear() == dtCur.GetYear()) &&
		(dtRcp.GetMonth() == dtCur.GetMonth()) &&
		(dtRcp.GetDay() == dtCur.GetDay()))
		LU->OpenCurOrderState(GetItemTNo(nSelItem));
	else
		MessageBox("금일오더만 확인 하실수 있습니다", "확인", MB_ICONINFORMATION);
}


void CRcpView::CheckOfficeAllocateOnly(long nType, BOOL &bRiderOnlyMan, BOOL &bOfficeOnlyMan)
{
	long bRider = RIDER_OK_ONLY_MAN & nType;
	long bOffice = OFFICE_OK_ONLY_MAN & nType;

	bRiderOnlyMan = bRider == RIDER_OK_ONLY_MAN ? TRUE : FALSE;
	bOfficeOnlyMan = bOffice == OFFICE_OK_ONLY_MAN ? TRUE : FALSE;
}

void CRcpView::OrderClickAutoMoveMap(long nPosX, long nPosY, long nRCompany, long nRNo, BOOL bNearRider)
{
	if(LU->GetRiderMapDlg() && LU->GetRiderMapDlg()->IsWindowVisible())
		LU->GetRiderMapDlg()->OrderClickAutoMoveMap(nPosX, nPosY, nRCompany, nRNo, bNearRider);
	else if(LU->GetRiderMapDlg2() && LU->GetRiderMapDlg2()->IsWindowVisible())
		LU->GetRiderMapDlg2()->OrderClickAutoMoveMap(nPosX, nPosY, nRCompany, nRNo, bNearRider);
}


BOOL CRcpView::HasSearchCondition()
{
	if(m_edtShStart.GetWindowTextLength() == 0)
		if(m_edtShDest.GetWindowTextLength() == 0)
			if(m_edtShRider.GetWindowTextLength() == 0)
				if(m_edtShCustomer.GetWindowTextLength() == 0)
					if(m_edtShEtc.GetWindowTextLength() == 0)
						return FALSE;

	return TRUE;
}

void CRcpView::SetLastSelItemNo(long nItem)
{
	if(!HasSearchCondition())
	{
		m_nLastSelItemNo = GetItemTNo(nItem);
		m_nLastSelItemNoCondition = -1;
	}
	else
	{
		m_nLastSelItemNo = GetItemTNo(nItem);
		m_nLastSelItemNoCondition = GetItemTNo(nItem);
	}
}

long CRcpView::GetLastSelItemNo()
{
	long nItem; 

	if(!HasSearchCondition())
		nItem = m_nLastSelItemNo;
	else
	{
		if(m_nLastSelItemNoCondition == -1)
			nItem = m_nLastSelItemNo;
		else
			nItem = m_nLastSelItemNoCondition;
	}

	//	g_bana_log->Print("selitem = %d\n", nItem);

	return nItem;
}

void CRcpView::OnSetDepositZero()
{
	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}
 
	int nState = GetItemState(nSelItem);

	/*
	if(GetItemState(nSelItem) != STATE_OK)
	{
		MessageBox("접수상태가 아닙니다. 수수료율 변경은 접수상태만 가능합니다.", "확인", MB_ICONEXCLAMATION);
		return;
	}
	*/

	if(GetItemSecondCross(nSelItem))
	{

		CString strMsg;
		strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONEXCLAMATION);
		return;
	}

	if(MessageBox("수수료 0% 설정 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand pCmd(m_pMkDb, "update_order_deposit_rate_1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), (int)0);
	pCmd.AddParameter(GetItemTNo(nSelItem));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(0);
	pCmd.AddParameter(m_ui.strName);
	if(pCmd.Execute())
	{
		if(parRet->GetLong() == 10)
			MessageBox("오더의 상태가 접수상태가 아닙니다.", "확인", MB_ICONEXCLAMATION);
		else
			MessageBox("수수료율을 0%로 변경하였습니다.", "확인", MB_ICONEXCLAMATION);

		RefreshList();
	}
}


void CRcpView::ChangeSearchFilter()
{
	UpdateData(TRUE);

	const char szTemp[] = 
		"<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Center' VerticalAlignment='Center'>"\
		"%s"\
		">%s"\
		"%s"\
		"</TextBlock>"; 

	m_strInfoEditSearch = "";

	if(!m_strShTNo.IsEmpty()) m_strInfoEditSearch += GetSearchText("오더번호:", m_strShTNo);
	if(!m_strShCustomer.IsEmpty()) m_strInfoEditSearch += GetSearchText("의뢰지명:", m_strShCustomer);
	if(!m_strShDepart.IsEmpty()) m_strInfoEditSearch += GetSearchText("부서명:", m_strShDepart);
	if(!m_strShManager.IsEmpty()) m_strInfoEditSearch += GetSearchText("담당자:", m_strShManager);
	if(!m_strShCustomerID.IsEmpty()) m_strInfoEditSearch += GetSearchText("고객번호:", m_strShCustomerID);
	if(!m_strShGroup.IsEmpty()) m_strInfoEditSearch += GetSearchText("그룹명:", m_strShGroup);
	if(!m_strShGroupDepart.IsEmpty()) m_strInfoEditSearch += GetSearchText("그룹부서명:", m_strShGroupDepart);
	if(!m_strShCID.IsEmpty()) m_strInfoEditSearch += GetSearchText("CID:", m_strShCID);
	if(!m_strShWNo.IsEmpty()) m_strInfoEditSearch += GetSearchText("접수자:", m_strShWNo);
	if(!m_strShEtc.IsEmpty()) m_strInfoEditSearch += GetSearchText("적요:", m_strShEtc);
	if(!m_strShStart.IsEmpty()) m_strInfoEditSearch += GetSearchText("출발지:", m_strShStart);
	if(!m_strShDest.IsEmpty()) m_strInfoEditSearch += GetSearchText("도착지:", m_strShDest);
	if(!m_strShRider.IsEmpty()) m_strInfoEditSearch += GetSearchText("기사명:", m_strShRider);
	if(!m_strShRiderNo.IsEmpty()) m_strInfoEditSearch += GetSearchText("기사사번:", m_strShRiderNo);
	if(!m_strShRegionStart.IsEmpty()) m_strInfoEditSearch += GetSearchText("출발지역:", m_strShRegionStart);
	if(!m_strShRegionDest.IsEmpty()) m_strInfoEditSearch += GetSearchText("도착지역:", m_strShRegionDest);
	if(!m_strShowRiderInfo.IsEmpty()) m_strInfoEditSearch += GetSearchText("기사사번:", m_strShowRiderInfo);
	if(!m_strShCustomerMemo.IsEmpty()) m_strShCustomerMemo += GetSearchText("고객메모:", m_strShCustomerMemo);

	if(!m_strInfoEditSearch.IsEmpty())
	{
		m_strInfoEditSearch = "[" + m_strInfoEditSearch + "] ";
		//m_strInfoEditSearch = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Center' VerticalAlignment='Center'>" + m_strInfoEditSearch;
		//m_strInfoEditSearch += "</TextBlock>";
	}


	CString sVal ="";
	m_strInfoCheckSearch = "";

	m_strInfoCheckSearch += CheckOXCheckBox(m_nShMyRider, "자사기사:");
	m_strInfoCheckSearch += CheckOXCheckBox(m_nShMyCall, "본인콜:");
	m_strInfoCheckSearch += CheckOXCheckBox(m_nShHideCrossCall, "크로스미표시:");
	m_strInfoCheckSearch += CheckOXCheckBox(m_nShShowCrossCall, "공유콜:");
	m_strInfoCheckSearch += CheckOXCheckBox(m_nShScheduleOrder, "정기오더:");
	m_strInfoCheckSearch += CheckOXCheckBox(m_nShInterOrder, "인터넷:");

	if(!m_strInfoCheckSearch.IsEmpty())
	{
		m_strInfoCheckSearch = "[" + m_strInfoCheckSearch + "]";
	}

	DisplaySearchInfo();
	RefreshFilterOnly();
}

void CRcpView::DisplaySearchInfo()
{
	if(!LF->POWER_CHECK(2007, "카운트 표시"))
		return;

	CString strTemp = "";

	if(m_strInfoEditSearch.IsEmpty() && m_strInfoCheckSearch.IsEmpty() && 
		GetCarTypeDisplay(FALSE).IsEmpty() && GetPayTypeDisplay(FALSE).IsEmpty())
	{
		m_strInfoCheckSearch = "<Run Foreground='Black' FontWeight='Normal'>[전체검색중]</Run>";
	}

	CString strShareCount = ""; 
 
	if(LF->POWER_CHECK(2014, "공유콜잔액"))
	{
		strShareCount += "<Run Foreground='black' FontSize='11' FontWeight='Bold'> [공유콜잔액 :</Run> ";
		strShareCount += "<Run Foreground='black' FontSize='12' FontWeight='Bold'> " + LF->GetMyNumberFormat(m_nShareBalance) + "원]</Run>   ";
	}

	if(LF->POWER_CHECK(2015, "SMS잔액"))
	{
		strShareCount += "<Run Foreground='black' FontSize='11' FontWeight='Bold'> [SMS잔액 :</Run> ";
		strShareCount += "<Run Foreground='black' FontSize='12' FontWeight='Bold'> " + LF->GetMyNumberFormat(m_nSmsBalance) + "원]</Run>   ";
	}	

	strTemp = m_strInfoCount + m_strInfoEditSearch + m_strInfoCheckSearch + GetCarTypeDisplay(FALSE) + GetPayTypeDisplay(FALSE) + strShareCount;

	strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Center' VerticalAlignment='Center'>" + strTemp;
	strTemp += "</TextBlock>";
	m_stcDisplay.SetMarkupText(strTemp); 

	strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Center' VerticalAlignment='Center'>" + GetCarTypeDisplay(TRUE);
	strTemp += "</TextBlock>";
	m_stcCarType.SetMarkupText(strTemp); 

	strTemp = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Center' VerticalAlignment='Center'>" + GetPayTypeDisplay(TRUE);
	strTemp += "</TextBlock>"; 
	m_stcPayType.SetMarkupText(strTemp); 
 
	CString strTempAll = m_strInfoEditSearch + m_strInfoCheckSearch;
	if(strTempAll.IsEmpty())
		strTempAll = "<Run Foreground='Black' FontWeight='Normal'>[전체검색중]</Run>";
   
	strTemp = "";    
	strTemp += "<Border Padding='0'>";
	strTemp += "<StackPanel TextBlock.FontFamily='Microsoft YaHei'>"; 
	strTemp += "   <TextBlock Padding='0'>" + m_strInfoCount + "</TextBlock>";

	strTemp += "   <TextBlock Padding='0'>" + GetShareCallCount() + "</TextBlock>";
	
	strTemp += "   <TextBlock Padding='0'>" + GetShareCallBalance() + "</TextBlock>";
	
	
	strTemp += "</StackPanel>"; 
	strTemp += "</Border>" ;

	m_stcDisplay2.SetMarkupText(strTemp);
}

CString CRcpView::GetSearchText(CString sTitle, CString sEtc)
{ 
	CString sTemp = "" + sTitle + "";
	sTemp += "" + sEtc + " ";
	return sTemp;
}

CString CRcpView::CheckOXCheckBox(long nState, CString sTitle)
{
	CString sTemp = "<Run Foreground='Black' FontWeight='Normal'>" + sTitle + "</Run>";

	if(nState == CHECK_STATE_O)
		sTemp += "<Run Foreground='Red' FontWeight='Normal'>O</Run> ";
	else if(nState == CHECK_STATE_X)
		sTemp += "<Run Foreground='Blue' FontWeight='Normal'>X </Run>";
	else
		sTemp = "";

	return sTemp;
}

void CRcpView::OnEnChangeSearchTnoEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchDepartEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchManagerEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchCustomerIDEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchGroupEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchGroupDepartEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchRiderNoEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchWNoEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchStartRegionEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchStartEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchDestEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchRiderEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchCustomerEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnEnChangeSearchEtcEdit()
{
	ChangeSearchFilter();
}

BOOL CRcpView::IsCheckEditBox()
{
	if(!m_strShTNo.IsEmpty()) return TRUE;
	if(!m_strShCustomer.IsEmpty()) return TRUE;
	if(!m_strShDepart.IsEmpty()) return TRUE; 
	if(!m_strShManager.IsEmpty()) return TRUE;
	if(!m_strShCustomerID.IsEmpty()) return TRUE;
	if(!m_strShGroup.IsEmpty()) return TRUE;
	if(!m_strShGroupDepart.IsEmpty()) return TRUE;
	if(!m_strShCID.IsEmpty()) return TRUE;
	if(!m_strShWNo.IsEmpty()) return TRUE;
	if(!m_strShEtc.IsEmpty()) return TRUE;
	if(!m_strShStart.IsEmpty()) return TRUE;
	if(!m_strShDest.IsEmpty()) return TRUE;
	if(!m_strShRider.IsEmpty()) return TRUE;
	if(!m_strShRiderNo.IsEmpty()) return TRUE;
	//if(!m_strShRegionStart.IsEmpty()) return TRUE;
	//if(!m_strShRegionDest.IsEmpty()) return TRUE;
	if(!m_strShowRiderInfo.IsEmpty()) return TRUE;
	if(!m_strShCustomerMemo.IsEmpty()) return TRUE;
	if(!m_strShCustomerInnerMemo.IsEmpty()) return TRUE;

	return FALSE;
}

BOOL CRcpView::IsCheckCheckBox()
{
	if(m_chkShMyRider.GetCheck()) return TRUE;
	if(m_chkMyCall.GetCheck()) return TRUE;
	if(m_chkHideCrossCall.GetCheck()) return TRUE;
	if(m_chkShowCrossCall.GetCheck()) return TRUE;
	if(m_chkScheduleOrder.GetCheck()) return TRUE;
	if(m_chkInterOrder.GetCheck()) return TRUE;
	if(m_chkShWebOrder.GetCheck()) return TRUE;
	//if(m_chkShCarTypeAll.GetCheck()) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType0 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType1 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType2 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType3 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType4 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType5 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType6 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType7 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType8 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType9 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType10 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType11 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType12 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType13 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType14 == TRUE) return TRUE;
	if(CRcpSearchCarTypeDlg::m_bCarType15 == TRUE) return TRUE;	
	//if(m_chkShPayTypeAll.GetCheck()) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType0 == TRUE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType1 == TRUE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType2 == TRUE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType3 == TRUE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType4 == TRUE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType7 == TRUE) return TRUE;

	return FALSE;
}

AFX_INLINE BOOL CRcpView::CheckFilterSubCheckBox(OrderRecord *order)
{	
	BOOL bMyOrder = m_ci.IsChildCompany(order->nCompany);
	BOOL bMyRiderOrder = m_ci.IsChildCompany(order->nRiderCompany);
	long nCompany = LF->GetCurBranchInfo()->nCompanyCode;
	BOOL bIntegrated = LF->GetCurBranchInfo()->bIntegrated;
	
	if(order->nRNo <= 0)
		bMyRiderOrder = FALSE;
 
	if((m_nShMyRider == CHECK_STATE_O && bMyRiderOrder == FALSE) ||
		(m_nShMyRider == CHECK_STATE_X &&  bMyRiderOrder == TRUE)) 
	{
		return TRUE;
	}


	if(m_nShMyCall == CHECK_STATE_O)		
	{
		if(LF->IsThisCompany("하나로퀵"))
		{
			if((m_ui.nCompany != order->nWCompany ||  m_ui.nWNo != order->nWNo) &&
				!order->bInternet)
				return TRUE;		
		}
		else
		{
			if(m_ui.nCompany != order->nWCompany ||  m_ui.nWNo != order->nWNo)
				return TRUE;
		}
	}

	if((m_nShMyCall == CHECK_STATE_X) &&
		(m_ui.nCompany == order->nWCompany &&  m_ui.nWNo == order->nWNo))
	{
		return TRUE;
	}

	if(bIntegrated)
	{
		if((m_nShHideCrossCall == CHECK_STATE_O && bMyOrder == FALSE) ||
			(m_nShHideCrossCall == CHECK_STATE_X && bMyOrder == TRUE))
		{
			return TRUE;
		}
	}
	else
	{
		if((m_nShHideCrossCall == CHECK_STATE_O && order->nCompany != nCompany) ||
			(m_nShHideCrossCall == CHECK_STATE_X && order->nCompany == nCompany))
		{
			return TRUE;
		}	
	}	

	if((m_nShShowCrossCall == CHECK_STATE_O && bMyOrder == TRUE) ||
		(m_nShShowCrossCall == CHECK_STATE_X && bMyOrder == FALSE))
	{
		return TRUE;
	}

	if((m_nShScheduleOrder == CHECK_STATE_O && order->bScheduleOrder == FALSE) ||
		(m_nShScheduleOrder == CHECK_STATE_X && order->bScheduleOrder == TRUE))
	{
		return TRUE;
	}
	
	if((m_nShInterOrder == CHECK_STATE_O && order->bInternet == FALSE) ||
		(m_nShInterOrder == CHECK_STATE_X && order->bInternet == TRUE))
	{
		return TRUE;
	}

	if(m_pBi->IsCargo())
	{
		/*
		if(CRcpSearchTruckTypeDlg::m_bTruckType0 == FALSE && order->nTruckType == TRUCK_CARGO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTruckType1 == FALSE && order->nTruckType == TRUCK_TOP) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTruckType1 == FALSE && order->nTruckType == TRUCK_WING) return TRUE;
		*/

		if(CRcpSearchTruckTypeDlg::m_bTonType0 == FALSE && order->strTon.compare("1.0") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType1 == FALSE && order->strTon.compare("1.4") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType2 == FALSE && order->strTon.compare("2.5") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType3 == FALSE && order->strTon.compare("3.5") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType4 == FALSE && order->strTon.compare("4.5") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType5 == FALSE && order->strTon.compare("5.0") == ZERO) return TRUE;
		if(CRcpSearchTruckTypeDlg::m_bTonType6 == FALSE && order->strTon.compare("11") == ZERO) return TRUE;
	}
	else
	{
		if(CRcpSearchCarTypeDlg::m_bCarType0 == FALSE && order->nCarType == CAR_AUTO) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType1 == FALSE && order->nCarType == CAR_BIGBIKE) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType2 == FALSE && order->nCarType == CAR_DAMA) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType3 == FALSE && order->nCarType == CAR_LABO) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType4 == FALSE && order->nCarType == CAR_VAN) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType5 == FALSE && order->nCarType == CAR_TRUCK) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType6 == FALSE && order->nCarType == CAR_SUBWAY) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType7 == FALSE && order->nCarType == CAR_PS) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType8 == FALSE && order->nCarType == CAR_6VAN) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType9 == FALSE && order->nCarType == CAR_1_4_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType10 == FALSE && order->nCarType == CAR_2_5_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType11 == FALSE && order->nCarType == CAR_3_5_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType12 == FALSE && order->nCarType == CAR_5_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType13 == FALSE && order->nCarType == CAR_11_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType14 == FALSE && order->nCarType == CAR_18_TON) return TRUE;
		if(CRcpSearchCarTypeDlg::m_bCarType15 == FALSE && order->nCarType == CAR_25_TON) return TRUE;
	}
 
	if(CRcpSearchPayTypeDlg::m_bPayType0 == FALSE && order->nPayType == PAY_PRE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType1 == FALSE && order->nPayType == PAY_AFTER) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType2 == FALSE && order->nPayType == PAY_CREDIT) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType3 == FALSE && order->nPayType == PAY_ONLINE) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType4 == FALSE && order->nPayType == PAY_DIRECT) return TRUE;
	if(CRcpSearchPayTypeDlg::m_bPayType7 == FALSE && order->nPayType == PAY_CARD) return TRUE;

	return FALSE;
}

AFX_INLINE BOOL CRcpView::CheckFilterSubState(OrderRecord *order, BOOL &bHideCompleteOrder, 
				BOOL &bAll, BOOL &bRcp, BOOL &bWait, BOOL &bReserved, BOOL &bOnlyMan, BOOL &bAlloc, 
				BOOL &bFinish, BOOL &bCancel, BOOL &bPickup, BOOL &bEtc)
{
	long nState = order->nState;

	if(!bAll)
	{
		if(!((bRcp && (nState == STATE_OK|| nState == STATE_INTERNET)) ||
			(bWait && (nState == STATE_WAIT || nState == STATE_INTERNET)) ||
			(bReserved && nState == STATE_RESERVED) ||
			(bOnlyMan && nState == STATE_OK_ONLY_MAN) ||
			(bAlloc && nState == STATE_ALLOCATED) ||
			(bFinish && nState == STATE_FINISH && !bHideCompleteOrder) ||
			(bCancel && nState == STATE_CANCELED) ||
			(bPickup && nState == STATE_PICKUP) ||
			(bEtc && (nState == STATE_INQUIRY || nState == STATE_NOTICE))))
		{
			return TRUE;			
		}
	}
	else
	{
		if(nState == STATE_FINISH && bHideCompleteOrder)
			return TRUE;
	}

	if(nState == STATE_RESERVED)
	{
		if(!bAll && bReserved)
		{
			if(m_bStateSecondSort && 
				m_nReserveShowCount > 0 && 
				order->nReserveSortNumber > m_nReserveShowCount)
			{
				return TRUE;
			}
		}

/*//by mksong (2011-02-21 오후 5:31) 필요없지 않을까?
		COleDateTime dtFrom, dtTo;
		m_FromDT.GetTime(dtFrom);
		m_ToDT.GetTime(dtTo);

		if(order->dtRcp < dtFrom || order->dtRcp > dtTo)
		{
			return TRUE;
		}
*/
	}	

	return FALSE;
}

AFX_INLINE BOOL CRcpView::CheckFilterSubEditBox(OrderRecord *order, CString strCNoSum, CString strSearchMemoCNo)
{
	//CString m_strShCustomerID;


	if(atol(m_strShTNo) > 0)
	{
		if(!(order->nTNo == atol(m_strShTNo))) //오더번호
			return TRUE;
	}

	if(!(CString(order->strCName.c_str()).Find(m_strShCustomer) >= 0)) //고객명
		return TRUE;

	if(!(CString(order->info[RCP_DEPART_COL].c_str()).Find(m_strShDepart) >= 0))  //부서명
		return TRUE;

	if(!(CString(order->info[MANAGER_COL].c_str()).Find(m_strShManager) >= 0))  //담당자
		return TRUE;

	CString str = order->info[START_COMPANY_COL].c_str(); 

	if(!(CString(order->info[START_COMPANY_COL].c_str()).Find(m_strShGroup) >= 0))  //출발지고객
		return TRUE;

	if(!(CString(order->info[DEST_COMPANY_COL].c_str()).Find(m_strShGroupDepart) >= 0))  //도착지고객
		return TRUE;

	/*
	if(!(CString(order->info[RCP_GNO_COL].c_str()).Find(m_strShGroup) >= 0))  //그룹
		return TRUE;

	if(!(CString(order->info[RCP_GNO_DEPT_COL].c_str()).Find(m_strShGroupDepart) >= 0))  //그룹부서명
		return TRUE;
	*/


	if(atoi(m_strShCustomerID) > 0) //고객번호
	{
		char buffer[10];
		CString strCNo = ";" + CString(itoa(order->nCNo, buffer, 10)) + ";";

		if(!(strCNoSum.Find(strCNo) >= 0))
				return TRUE;
	}
	
	//m_strShCustomerID고객번호 체크해야함
 
	CString strPhone = m_strShCID;
	strPhone.Replace("-", "");

	CString strCID = CString(order->info[RCP_CID_COL].c_str());
	CString strOPhone = CString(order->info[RCP_PHONE_COL].c_str());

	strCID.Replace("-", "");
	strOPhone.Replace("-", "");

	if(!((strCID.Find(strPhone) >= 0) || //고
		(strOPhone.Find(strPhone) >= 0)))
		return TRUE;

	if(m_bSearchWithNoWName)
	{
		CString strWName = order->strWName.c_str();

		/*
		if(!(strWName == "인터콜" || 
			strWName == "스마트콜" ||
			strWName == "스마트콜2" ||
			strWName == "정기오더") || )
			return TRUE;
		*/

		if(!((order->nWNo == atol(m_strShWNo) && LF->IsNumeric(m_strShWNo) == TRUE) ||
			(CString(order->strWName.c_str()).Find(m_strShWNo) >= 0) ||
			(strWName == "인터콜" || 
			strWName == "스마트콜" ||
			strWName == "스마트콜2" ||
			strWName == "정기오더" )
			)) //접수자
			return TRUE;
	}
	else
	{
		if(!((order->nWNo == atol(m_strShWNo) && LF->IsNumeric(m_strShWNo) == TRUE) ||
			(CString(order->strWName.c_str()).Find(m_strShWNo) >= 0))) //접수자
			return TRUE;
	}	

	if(!(CString(order->info[ETC_COL].c_str()).Find(m_strShEtc) >= 0))  //적요
		return TRUE;

	if(!((CString(order->strStart.c_str()).Find(m_strShStart) >= 0) || 
		(CString(order->info[START_DONG_COL].c_str()).Find(m_strShStart) >= 0))) //출발지
		return TRUE;

	if(!((CString(order->strDest.c_str()).Find(m_strShDest) >= 0) ||
		(CString(order->info[DEST_DONG_COL].c_str()).Find(m_strShDest) >= 0))) //도착지
		return TRUE;

	if(!(CString(order->strRName.c_str()).Find(m_strShRider) >= 0)) //기사명
		return TRUE;

	if(atol(m_strShRiderNo) > 0)//기사번호
	{
		if(atoi(m_strShRiderNo) != order->nRNo) 
			return TRUE;
	} 

	if(atol(m_strShowRiderInfo) > 0)//오른쪽위에 기사검색
	{
		if(atoi(m_strShowRiderInfo) != order->nRNo) 
			return TRUE;
	} 

	if(!m_strShCustomerMemo.IsEmpty()) //고객메모
	{
		char buffer[10];
		CString strCNo = ";" + CString(itoa(order->nCNo, buffer, 10)) + ";";

		if(!(strSearchMemoCNo.Find(strCNo) >= 0))
			return TRUE;
	}

	if(atoi(m_strShCustomerInnerMemo) > 0)  //DNIS
	{
		if(atoi(m_strShCustomerInnerMemo) != order->nDNIS) 
			return TRUE;
	}

	/*
	if(m_strShCID.IsEmpty() == FALSE)
	{
		CString strPhone = m_strShCID; strPhone.Replace("-", "");		
		CString strOrderPhone = CString(order->info[RCP_CID_COL].c_str());
		if(!(strOrderPhone.Find(strPhone) >= 0))  //CID
			return TRUE;
	}
	*/

	return FALSE;
}

void CRcpView::OnBnClickedGetAllocCheck()
{
	SetAllocCheck();
}

void CRcpView::SetAllocCheck(BOOL bMsgBox)
{
	if(m_chkGetAlloc.GetCheck())
	{
		if(!m_ci.m_bAllocateWithPDA) 
		{
			if(bMsgBox)
			{
				CString strText = "PDA배차를 이용하시는 회원사만 유효합니다.";
				MessageBox(strText, "확인", MB_ICONINFORMATION);
			}		
			m_chkGetAlloc.SetCheck(FALSE);
		}
		else 
		{
			LU->GetRightOfAllocation(bMsgBox);
			AfxGetApp()->WriteProfileInt("RcpPage", "RecvAllocMsg", 1);
		}
	}
	else
	{
		LU->ReleaseRightOfAllocation();
		AfxGetApp()->WriteProfileInt("RcpPage", "RecvAllocMsg", 0);
	}
}

void CRcpView::OnBnClickedGetMsgCheck()
{
	SetMsgCheck();
}

void CRcpView::SetMsgCheck(BOOL bMsgBox)
{ 
	if(m_chkGetMsg.GetCheck())
	{
		if(!m_ci.m_bUseInterCall) 
		{
			if(bMsgBox)
			{
				CString strText = "인터넷 고객접수프로그램(인터콜)을 사용하지 않는 회원사입니다";
				MessageBox(strText, "확인", MB_ICONINFORMATION);
			}		
			m_chkGetMsg.SetCheck(FALSE);
		}
		else 
			m_chkGetMsg.SetCheck(LU->GetRightOfMessenger(bMsgBox));
	}
	else
	{
		LU->ReleaseRightOfMessenger();
	}


	if(m_chkGetMsg.GetCheck())
	{
		AfxGetApp()->WriteProfileInt("RcpPage", "RecvIntercall", 1);
		MyIntercallState("인터콜 받음");
	}
	else 
	{
		AfxGetApp()->WriteProfileInt("RcpPage", "RecvIntercall", 0);
		MyIntercallState("");
	}
}

void CRcpView::OnBnClickedOpenSearchBtn()
{
	//CreateRcpDlg(FALSE);
	ShowSearchMode(m_bSearchMode);
}

void CRcpView::ShowSearchMode(BOOL bSearchMode)
{ 
	m_stcDisplay.ShowWindow(!bSearchMode);
	m_btnClearAllCheck.ShowWindow(bSearchMode);
	m_btnDeleteSearchText.ShowWindow(bSearchMode);

	CRect rcInfo; m_stcDisplay.GetWindowRect(rcInfo);
	CRect rcSearch; m_btnSearch.GetWindowRect(rcSearch);
	CRect rcNew; m_btnNew.GetWindowRect(rcNew);
	CRect rcList; m_xList.GetWindowRect(rcList);
	CRect rcInitSearch; m_btnInitSearch.GetWindowRect(rcInitSearch);
	CRect rcShareSearch; m_btnShareSearch.GetWindowRect(rcShareSearch);
	CRect rcDeleteSearchText; m_btnDeleteSearchText.GetWindowRect(rcDeleteSearchText);

	ScreenToClient(rcInfo);
	ScreenToClient(rcSearch);
	ScreenToClient(rcNew);
	ScreenToClient(rcList);
	ScreenToClient(rcInitSearch);
	ScreenToClient(rcShareSearch);
	ScreenToClient(rcDeleteSearchText);
	
	if(bSearchMode)  
	{ 
		rcList.top = rcDeleteSearchText.bottom + 3;
		//rcSearch.bottom = rcShareSearch.bottom;
		//rcNew.bottom = rcShareSearch.bottom;
	} 
	else
	{
		rcList.top = rcShareSearch.bottom + 2;
		//rcSearch.bottom = rcShareSearch.bottom;
		//rcNew.bottom = rcShareSearch.bottom;
	}
	

	m_xList.MoveWindow(rcList);
	m_btnSearch.MoveWindow(rcSearch);
	m_btnNew.MoveWindow(rcNew);

	for(int i=0; i<SEARCH_CHECK_COUNT; i++)
	{  
		GetDlgItem(searchCheckBox[i])->ShowWindow(bSearchMode);

		if(i< SEARCH_EDIT_COUNT)
		{
			GetDlgItem(searchEditBox1[i])->ShowWindow(bSearchMode);
			GetDlgItem(searchEditBox2[i])->ShowWindow(bSearchMode);
		}
	}

	m_btnClearAllCheck.ShowWindow(bSearchMode);
	m_btnDeleteSearchText.ShowWindow(bSearchMode);

	m_stcCarType.ShowWindow(bSearchMode);
	m_stcPayType.ShowWindow(bSearchMode);
	m_stcDisplay2.ShowWindow(bSearchMode);
	m_chkPreOrder.ShowWindow(bSearchMode);

	m_bSearchMode = !bSearchMode;
}

CString CRcpView::GetColorTo0x(long nColor)
{
	long nR = GetRValue(nColor);
	long nG = GetGValue(nColor);
	long nB = GetBValue(nColor);

	CString strColor = "";

	strColor.Format("#%02X%02X%02X", GetRValue(nColor), GetGValue(nColor), GetBValue(nColor));
	//strColor.Format("#%c,%c,%c", dec2hex(nR), dec2hex(nG), dec2hex(nB));
	return strColor;
}

void CRcpView::HideSearchDlg()
{
	if(m_pRcpShCarDlg != NULL)
		m_pRcpShCarDlg->ShowWindow(SW_HIDE);
	if(m_pRcpShPayDlg != NULL)
		m_pRcpShPayDlg->ShowWindow(SW_HIDE);
	if(m_pRcpShTruckDlg != NULL)
		m_pRcpShTruckDlg->ShowWindow(SW_HIDE);
}

void CRcpView::ShowShTruckTypeDlg()
{
	if(m_pRcpShTruckDlg == NULL)
		MakeRcpShTruckDlg();

	if(m_pRcpShTruckDlg->IsWindowVisible())
	{
		m_pRcpShTruckDlg->ShowWindow(FALSE);
		return;
	} 

	CRect rcDlg, rcStc;
	m_pRcpShTruckDlg->GetWindowRect(rcDlg);
	m_stcCarType.GetWindowRect(rcStc);

	ScreenToClient(rcDlg);

	long nHeight = rcDlg.Height();
	long nWidth = rcDlg.Width();

	rcDlg.bottom = rcStc.top - 2;
	rcDlg.top = rcDlg.bottom - nHeight;
	rcDlg.right = rcStc.left - 1;
	rcDlg.left = rcDlg.right - nWidth;

	LF->SetCrystal(m_pRcpShTruckDlg, 245);
	m_pRcpShTruckDlg->MoveWindow(rcDlg);
	m_pRcpShTruckDlg->ShowWindow(SW_SHOW);
}

void CRcpView::ShowShCarTypeDlg()
{
	if(m_pRcpShCarDlg == NULL)
		MakeRcpShCarDlg();

	if(m_pRcpShCarDlg->IsWindowVisible())
	{
		m_pRcpShCarDlg->ShowWindow(FALSE);
		return;
	} 

	CRect rcDlg, rcStc;
	m_pRcpShCarDlg->GetWindowRect(rcDlg);
	m_stcCarType.GetWindowRect(rcStc);

	ScreenToClient(rcDlg);

	long nHeight = rcDlg.Height();
	long nWidth = rcDlg.Width();

	rcDlg.bottom = rcStc.top - 2;
	rcDlg.top = rcDlg.bottom - nHeight;
	rcDlg.right = rcStc.left - 1;
	rcDlg.left = rcDlg.right - nWidth;

	if(!LF->IsWindowXP())
		LF->SetCrystal(m_pRcpShCarDlg, 245);

	m_pRcpShCarDlg->MoveWindow(rcDlg);
	m_pRcpShCarDlg->ShowWindow(SW_SHOW);
}

void CRcpView::ShowShPayTypeDlg()
{
	if(m_pRcpShPayDlg == NULL)
		MakeRcpShPayDlg();

	if(m_pRcpShPayDlg->IsWindowVisible())
	{
		m_pRcpShPayDlg->ShowWindow(FALSE);
		return;
	}
 
	CRect rcDlg, rcStc;
	m_pRcpShPayDlg->GetWindowRect(rcDlg);
	m_stcCarType.GetWindowRect(rcStc);

	ScreenToClient(rcDlg);

	long nHeight = rcDlg.Height();
	long nWidth = rcDlg.Width();

	rcDlg.bottom = rcStc.top - 2;
	rcDlg.top = rcDlg.bottom - nHeight;
	rcDlg.left = rcStc.left + 1;
	rcDlg.right = rcDlg.left + nWidth;
	
	if(!LF->IsWindowXP())
		LF->SetCrystal(m_pRcpShPayDlg, 245);

	m_pRcpShPayDlg->MoveWindow(rcDlg);
	m_pRcpShPayDlg->ShowWindow(SW_SHOW);
}

void CRcpView::MakeRcpShTruckDlg()
{
	if(m_pRcpShTruckDlg == NULL)
	{
		m_pRcpShTruckDlg = new CRcpSearchTruckTypeDlg(this);
		m_pRcpShTruckDlg->Create(IDD_RCP_SEARCH_TRUCK_TYPE_DLG);
	}
}

void CRcpView::MakeRcpShCarDlg()
{
	if(m_pRcpShCarDlg == NULL)
	{
		m_pRcpShCarDlg = new CRcpSearchCarTypeDlg(this);
		m_pRcpShCarDlg->Create(IDD_RCP_SEARCH_CAR_TYPE_DLG);
	}
}

void CRcpView::MakeRcpShPayDlg()
{
	if(m_pRcpShPayDlg == NULL)
	{
		m_pRcpShPayDlg = new CRcpSearchPayTypeDlg(this);
		m_pRcpShPayDlg->Create(IDD_RCP_SEARCH_PAY_TYPE_DLG);
	}
}

CString CRcpView::GetCarTypeDisplay(BOOL bAllDisplay)
{
	CString strTemp = "";
 
	if(CRcpSearchCarTypeDlg::m_bCarType0 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType1 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType2 == TRUE && 
		CRcpSearchCarTypeDlg::m_bCarType3 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType4 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType5 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType6 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType7 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType8 == TRUE &&
		CRcpSearchCarTypeDlg::m_bCarType9 == TRUE )
	{
		if(bAllDisplay)
			strTemp += "<Run Foreground='blue' FontWeight='Normal'>차량조건선택</Run>";
	}
	else if(CRcpSearchCarTypeDlg::m_bCarType0 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType1 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType2 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType3 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType4 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType5 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType6 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType7 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType8 == FALSE &&
		CRcpSearchCarTypeDlg::m_bCarType9 == FALSE)
	{
		if(bAllDisplay)
			strTemp += "<Run Foreground='blue' FontWeight='Normal'>선택안됨</Run>";
	}
	else
	{
		strTemp = "<Run Foreground='blue' FontWeight='Normal'>";

		if(CRcpSearchCarTypeDlg::m_bCarType0 == TRUE)
				strTemp += "오토,";
		if(CRcpSearchCarTypeDlg::m_bCarType1 == TRUE)
			strTemp += "짐받이,";
		if(CRcpSearchCarTypeDlg::m_bCarType2 == TRUE)
			strTemp += "다마,";
		if(CRcpSearchCarTypeDlg::m_bCarType3 == TRUE)
			strTemp += "라보,";
		if(CRcpSearchCarTypeDlg::m_bCarType4 == TRUE)
			strTemp += "3밴,";
		if(CRcpSearchCarTypeDlg::m_bCarType5 == TRUE)
			strTemp += "트럭,";
		if(CRcpSearchCarTypeDlg::m_bCarType6 == TRUE)
			strTemp += "지하철,";
		if(CRcpSearchCarTypeDlg::m_bCarType7 == TRUE)
			strTemp += "당일택배,";
		if(CRcpSearchCarTypeDlg::m_bCarType8 == TRUE)
			strTemp += "6밴,";
		if(CRcpSearchCarTypeDlg::m_bCarType9 == TRUE)
			strTemp += "1.4톤,";		
		if(CRcpSearchCarTypeDlg::m_bCarType10 == TRUE)
			strTemp += "2.5톤,";
		if(CRcpSearchCarTypeDlg::m_bCarType11 == TRUE)
			strTemp += "3.5톤,";
		if(CRcpSearchCarTypeDlg::m_bCarType12 == TRUE)
			strTemp += "5톤,";
		if(CRcpSearchCarTypeDlg::m_bCarType13 == TRUE)
			strTemp += "11톤,";
		if(CRcpSearchCarTypeDlg::m_bCarType14 == TRUE)
			strTemp += "18톤,";
		if(CRcpSearchCarTypeDlg::m_bCarType15 == TRUE)
			strTemp += "25톤,";

		strTemp = strTemp.Left(strTemp.GetLength() - 1);
		strTemp += "</Run>";
	} 
 
	if(strTemp.GetLength() > 0 && bAllDisplay == FALSE) // 위쪽에 메인 뿌림
	{
		strTemp = "<Run Foreground='black' FontWeight='Normal'>[</Run>" + strTemp;
		strTemp += "<Run Foreground='black' FontWeight='Normal'>]</Run>";
	}

	return strTemp;
}

CString CRcpView::GetPayTypeDisplay(BOOL bAllDisplay)
{
	CString strTemp = "";

	if(CRcpSearchPayTypeDlg::m_bPayType0 == TRUE &&
		CRcpSearchPayTypeDlg::m_bPayType1 == TRUE &&
		CRcpSearchPayTypeDlg::m_bPayType2 == TRUE &&
		CRcpSearchPayTypeDlg::m_bPayType3 == TRUE &&
		CRcpSearchPayTypeDlg::m_bPayType4 == TRUE &&
		CRcpSearchPayTypeDlg::m_bPayType7 == TRUE)
	{
		if(bAllDisplay)
			strTemp = "<Run Foreground='blue' FontWeight='Normal'>지불타입선택</Run>";
	}	
	else if(CRcpSearchPayTypeDlg::m_bPayType0 == FALSE &&
		CRcpSearchPayTypeDlg::m_bPayType1 == FALSE &&
		CRcpSearchPayTypeDlg::m_bPayType2 == FALSE &&
		CRcpSearchPayTypeDlg::m_bPayType3 == FALSE &&
		CRcpSearchPayTypeDlg::m_bPayType4 == FALSE &&
		CRcpSearchPayTypeDlg::m_bPayType7 == FALSE)
	{
		if(bAllDisplay)
			strTemp += "<Run Foreground='blue' FontWeight='Normal'>선택안됨</Run>";
	}
	else
	{
		strTemp += "<Run Foreground='blue' FontWeight='Normal'>";
		
		if(CRcpSearchPayTypeDlg::m_bPayType0 == TRUE)
			strTemp += "선불,";
		if(CRcpSearchPayTypeDlg::m_bPayType1 == TRUE)
			strTemp += "착불,";
		if(CRcpSearchPayTypeDlg::m_bPayType2 == TRUE)
			strTemp += "신용,";
		if(CRcpSearchPayTypeDlg::m_bPayType3 == TRUE)
			strTemp += "송금,";
		if(CRcpSearchPayTypeDlg::m_bPayType4 == TRUE)
			strTemp += "수금,";
		if(CRcpSearchPayTypeDlg::m_bPayType7 == TRUE)
			strTemp += "카드,";

		strTemp = strTemp.Left(strTemp.GetLength() - 1);
		strTemp += "</Run>";
	}

	if(strTemp.GetLength() > 0 && bAllDisplay == FALSE) // 위쪽에 메인 뿌림
	{
		strTemp = "<Run Foreground='black' FontWeight='Normal'>[</Run>" + strTemp;
		strTemp += "<Run Foreground='black' FontWeight='Normal'>]</Run>";
	}

	return strTemp; 
}

void CRcpView::OnBnClickedClearAllCheckBtn()
{
	for(int i=0; i<SEARCH_CHECK_COUNT; i++)
	{
		((CButton*)GetDlgItem(searchCheckBox[i]))->SetCheck(FALSE);
	}

	m_nShMyRider = 0;
	m_nShMyCall = 0;
	m_nShHideCrossCall = 0;
	m_nShShowCrossCall = 0;
	m_nShScheduleOrder = 0;
	m_nShInterOrder = 0;
	ChangeSearchFilter();
}


void CRcpView::OpenRegionDlg(BOOL bStart)
{
	CRegionSelectDlg dlg;
	dlg.m_bStart = bStart;

	if(bStart == TRUE)
		memcpy(dlg.m_nSelectedRegionDongID, m_nSelectedRegionStartDongID, MAX_REGION_SELECT_COUNT * sizeof(int));
	else
		memcpy(dlg.m_nSelectedRegionDongID, m_nSelectedRegionDestDongID, MAX_REGION_SELECT_COUNT * sizeof(int));

	if(dlg.DoModal() == IDOK)
	{
		if(bStart)
			memcpy(m_nSelectedRegionStartDongID, dlg.m_nSelectedRegionDongID, MAX_REGION_SELECT_COUNT * sizeof(int));
		else
			memcpy(m_nSelectedRegionDestDongID, dlg.m_nSelectedRegionDongID, MAX_REGION_SELECT_COUNT * sizeof(int));

		SetRegionText();
		ChangeSearchFilter();
	}
}

void CRcpView::SetRegionText()
{
	CString sStart = "", sDest = "";
	for(int i=0; i<MAX_REGION_SELECT_COUNT; i++)
	{
		if(m_nSelectedRegionStartDongID[i] > 0)
		{
			sStart += m_poiNew.GetDongPOI(m_nSelectedRegionStartDongID[i])->GetDong() + ",";
		}

		if(m_nSelectedRegionDestDongID[i] > 0)
			sDest += m_poiNew.GetDongPOI(m_nSelectedRegionDestDongID[i])->GetDong() + ",";
	}

	if(sStart.IsEmpty() == TRUE && sDest.IsEmpty() == FALSE)
		sStart = "전체";
	else if(sStart.IsEmpty() == FALSE && sDest.IsEmpty() == TRUE)
		sDest = "전체";

	m_edtShRegionStart.SetWindowText(sStart);
	m_edtShRegionDest.SetWindowText(sDest);
}

CString CRcpView::GetSearchCustomerID()
{ 
	CMkCommand pCmd(m_pMkDb, "select_customer_search_nID_1");

	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(atoi(m_strShCustomerID));
	CMkParameter *parRet = pCmd.AddParameter(typeString, typeOutput, 4000, "");

	CString strRet = "";

	if(pCmd.Execute())
		parRet->GetValue(strRet);

	return strRet;
}

CString CRcpView::GetSearchCustomerMemo()
{ 
	CMkCommand pCmd(m_pMkDb, "select_customer_search_memo_1");

	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_strShCustomerMemo);
	CMkParameter *parRet = pCmd.AddParameter(typeString, typeOutput, 4000, "");

	CString strRet = "";

	if(pCmd.Execute()) 
		parRet->GetValue(strRet);

	return strRet;
}

void CRcpView::FindCustomerFromPhone(CString strPhone, CString strDID, BOOL bPopupLastOrder)
{
//by mksong (2010-12-10 오전 11:38) 작업해야함
/*
	m_nSearchLastPhoneTNo = 0;

	CBranchInfo *pBi = LU->SearchLineGroup((LPSTR)(LPCTSTR)strDID);
	if(pBi == NULL)
		pBi = m_ba.GetAt(0);

	long nOperatorID; 
	nOperatorID = RefreshList(strPhone, pBi);
	nOperatorID = nOperatorID > 0 ? nOperatorID : 0;

	if(bPopupLastOrder && m_nSearchLastPhoneTNo > 0)
	{
		SelectRowFromTNo(m_nSearchLastPhoneTNo);
		OnBnClickedEditBtn();
	}
*/
}

void CRcpView::OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		CXTPMarkupString* pTag = MARKUP_DYNAMICCAST(CXTPMarkupString, ((CXTPMarkupHyperlink*)pSender)->GetTag());
		if (pTag)
		{
			CString strTag; strTag.Format("%ls",  (LPCWSTR)*pTag);

			if(strTag == "stateALL") {m_btnStateAll.SetCheck(!m_btnStateAll.GetCheck()); OnBnClickedStateAllBtn();}
			else if(strTag == "state10") {m_btnStateRcp.SetCheck(!m_btnStateRcp.GetCheck()); OnBnClickedStateRcpBtn();}
			else if(strTag == "state8") {m_btnStateWait.SetCheck(!m_btnStateWait.GetCheck()); OnBnClickedStateWaitBtn();}
			else if(strTag == "state11") {m_btnStateOnlyMan.SetCheck(!m_btnStateOnlyMan.GetCheck()); OnBnClickedStateOnlyManBtn();}
			else if(strTag == "state30") {m_btnStateAlloc.SetCheck(!m_btnStateAlloc.GetCheck()); OnBnClickedStateAllocBtn();}
			else if(strTag == "state35") {m_btnStateFinish.SetCheck(!m_btnStateFinish.GetCheck()); OnBnClickedStateFinishBtn();}
			else if(strTag == "state1135")
			{	
				m_btnStateOnlyMan.SetCheck(!m_btnStateOnlyMan.GetCheck()); OnBnClickedStateOnlyManBtn();
				m_btnStateAlloc.SetCheck(!m_btnStateAlloc.GetCheck()); OnBnClickedStateAllocBtn();
				m_btnStateFinish.SetCheck(!m_btnStateFinish.GetCheck()); OnBnClickedStateFinishBtn();
			}
			else if(strTag == "state40") {m_btnStateCancel.SetCheck(!m_btnStateCancel.GetCheck()); OnBnClickedStateCancelBtn();}
			else if(strTag == "state9") {m_btnStateReserved.SetCheck(!m_btnStateReserved.GetCheck()); OnBnClickedStateReservedBtn();}
		}

		pArgs->SetHandled();
	}
}

void CRcpView::OnBnClickedStateReservedBtn()
{
	//if(m_btnStateReserved.GetCheck())
	//	m_btnStateAll.SetCheck(0);

	RefreshFilterOnly(TRUE);
}

void CRcpView::OnMoveOrderBranch()
{
	if(!LF->POWER_CHECK(2011, "접수 오더이동권한", TRUE))
		return;

	int nItem = m_xList.GetSelectedItem();
	long nCorpID = -1;

	if(GetItemSecondCross(nItem))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더를 직접 취소하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 취소 요청을 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CCompanyBranchListDlg1 dlg;

	if(dlg.DoModal() == IDOK)
	{
		BOOL bCopy = dlg.m_bCopy;
		if(dlg.m_pBi->nCustomerTable != dlg.m_pBi->nCompanyCode)
			bCopy = FALSE;
		MoveOrder(dlg.m_pBi, bCopy);
	} 

}

void CRcpView::ShowOrderLogDetailDlgFromTNo(long nTNo, long nState, BOOL bCrossOrder, BOOL bFullSearch)
{
	//SearchCondition(TRUE);
	//InitSearch(TRUE);
	//long nRow = SelectRowFromTNo(nTNo); 

	SearchCondition(TRUE);
 
	CREATE_MODALESS(COrderLogDetailDlg, this);
	pDlg->m_nTNo = nTNo;
	pDlg->m_nState = nState;
	pDlg->m_bCross = bCrossOrder;
	pDlg->m_bFullSearch = bFullSearch;

	SHOW_MODALESS(COrderLogDetailDlg, this);
	/*
	COrderLogDetailDlg dlg;
	dlg.m_nTNo = nTNo;
	dlg.m_nState = nState;
	dlg.m_bCross = bCrossOrder;
//	dlg.m_pRcpView = this;
	dlg.DoModal();
	*/

	SearchCondition(FALSE);
} 

void CRcpView::SearchCondition(BOOL bSave)
{
	if(bSave)
	{
		m_nStateAll = m_btnStateAll.GetCheck();
		m_nStateWait = m_btnStateWait.GetCheck();
		m_nStateReserved = m_btnStateReserved.GetCheck();
		m_nStateRcp = m_btnStateRcp.GetCheck();
		m_nStateAlloc = m_btnStateAlloc.GetCheck();
		m_nStateOnlyMan = m_btnStateOnlyMan.GetCheck();
		m_nStateFinish = m_btnStateFinish.GetCheck();
		m_nStateCancel = m_btnStateCancel.GetCheck();
		m_nStateEtc = m_btnStateEtc.GetCheck();		
		m_nStatePickup = m_btnStatePickup.GetCheck();
	}
	else
	{
		m_btnStateAll.SetCheck(m_nStateAll);
		m_btnStateWait.SetCheck(m_nStateWait);
		m_btnStateReserved.SetCheck(m_nStateReserved);
		m_btnStateRcp.SetCheck(m_nStateRcp);
		m_btnStateAlloc.SetCheck(m_nStateAlloc);
		m_btnStateOnlyMan.SetCheck(m_nStateOnlyMan);
		m_btnStateFinish.SetCheck(m_nStateFinish);
		m_btnStateCancel.SetCheck(m_nStateCancel);
		m_btnStateEtc.SetCheck(m_nStateEtc);
		m_btnStatePickup.SetCheck(m_nStatePickup);

		RefreshFilterOnly();
	}
}

long CRcpView::SelectRowFromTNo(long nTNo)
{
	int nRow = m_vrOrder->GetItemRowFromTNo(nTNo);  

	if(nRow == -1)
	{
		m_nOnceSelectedTNo = nTNo;
		RefreshFilterOnly();

		nRow = m_vrOrder->GetItemRowFromTNo(nTNo);  

		if(nRow == -1)
			return -1;
	}

	CXTPGridRows *pRows = m_xList.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
	m_xList.EnsureVisible(pRow);
	pRow = pRows->GetAt(nRow);
	m_xList.GetSelectedRows()->Select(pRow);
	return nRow;
}

void CRcpView::AlllocateFromTNo(long nTNo, long nCompany, long nRNo)
{
	SearchCondition(TRUE);
	InitSearch(TRUE);
	SelectRowFromTNo(nTNo);

	if(nCompany > 0)
		OnRiderAllocate(nRNo, nCompany);
	else
		OnBnClickedAllocateBtn();
	SearchCondition(FALSE);
}

void* CRcpView::GetTodayOrderRecord(long nTNo)
{	
	OrderRecordList &list = m_vrOrder->GetOrderRecordList();
	OrderRecordList::iterator it;
	it = list.find(nTNo);

	if(it != list.end())
		return &it->second;
	else 
		return NULL;
}

#include "CustomerData.h"

void CRcpView::OnBnClickedConnectMessengerForLogiBtn()
{
//	CIDX_ITER_PAIR iterpair;
//	BOOL bRet = m_cus.SearchCustomerCNo(10, 12696405, iterpair);
//	g_bana_log->Print("Found = %d\n", bRet);
	LU->StartMessenger(TRUE);
}

CString CRcpView::GetShareCallCount()
{
	CString strTemp = ""; 

	if(LF->POWER_CHECK(2014, "공유콜잔액"))
	{
		strTemp = "<Run Foreground='black' FontWeight='Bold'>현재공유콜잔액 :</Run> ";
		strTemp += "<Run Foreground='black' FontWeight='Bold'> " + LF->GetMyNumberFormat(m_nShareBalance) + "원</Run>   ";
	}

	if(LF->POWER_CHECK(2015, "SMS잔액"))
	{
		strTemp += "<Run Foreground='blue' FontWeight='Bold'>SMS잔액 :</Run> ";
		strTemp += "<Run Foreground='blue' FontWeight='Bold'> " + LF->GetMyNumberFormat(m_nSmsBalance) + "원</Run>";
	}

	return strTemp;
}

CString CRcpView::GetShareCallBalance() 
{ 
	if(!LU->IsShareInfoShowOk())
		return "";

	CString strTemp;  
	strTemp = "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText1) /*+ "'Background='"+ GetColorTo0x(CVirtualRecord::m_crStateBack1)*/ + "' FontWeight='Normal'>접수:</Run>";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText1) /*+ "'Background='" + GetColorTo0x(CVirtualRecord::m_crStateBack1)*/ + "' FontWeight='Normal'>" + LF->GetMyNumberFormat(m_nShareRcpCount) + " </Run> ";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText5) /*+ "'Background='"+ GetColorTo0x(CVirtualRecord::m_crStateBack5)*/ + "' FontWeight='Normal'>배차:</Run>";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText5) /*+ "'Background='" + GetColorTo0x(CVirtualRecord::m_crStateBack5)*/ + "' FontWeight='Normal'>" + LF->GetMyNumberFormat(m_nShareAllocateCount) + " </Run> ";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText7) /*+ "'Background='"+ GetColorTo0x(CVirtualRecord::m_crStateBack7)*/ + "' FontWeight='Normal'>완료:</Run>";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText7) /*+ "'Background='" + GetColorTo0x(CVirtualRecord::m_crStateBack7)*/ + "' FontWeight='Normal'>" + LF->GetMyNumberFormat(m_nShareCompleteCount) + " </Run> ";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText8) /*+ "'Background='"+ GetColorTo0x(CVirtualRecord::m_crStateBack8)*/ + "' FontWeight='Normal'>취소:</Run>";
	strTemp += "<Run Foreground='" + GetColorTo0x(CVirtualRecord::m_crStateText8) /*+ "'Background='" + GetColorTo0x(CVirtualRecord::m_crStateBack8)*/ + "' FontWeight='Normal'>" + LF->GetMyNumberFormat(m_nShareCancelCount) + " </Run> ";
	strTemp += "<Run Foreground='black' FontWeight='Bold'>합계:</Run>";
	strTemp += "<Run Foreground='black' FontWeight='Bold'>" + LF->GetMyNumberFormat(m_nShareAllCount) + "</Run>";
 
	strTemp += "<Run Foreground='blue' FontWeight='Bold'> 금일수입:</Run>";
	strTemp += "<Run Foreground='blue' FontWeight='Bold'>" + LF->GetMyNumberFormat(m_nTodayIncome) + "</Run>";


	return strTemp;
}

void CRcpView::OnKillFocus(CWnd* pNewWnd)
{
	CRcpViewBase::OnKillFocus(pNewWnd);
}

void CRcpView::OnEnChangeSearchCidEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnBnClickedNewRcpDlgBtn()
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	CreateRcpDlg(NULL, "신규", -1, 0, "", FALSE, -10, GetTickCount(), 0, FALSE, "", 0, TRUE);
}

void CRcpView::SearchRiderInfo()
{
	CString sRNo;
	long nRNo = 0;

	m_edtShowRiderInfo.GetWindowText(sRNo);
	if(sRNo.IsEmpty())
		return;

	if(LF->IsStringDigit(sRNo))
	{
		nRNo = atol(sRNo);
		if(nRNo <= 0)
			return;
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "search_rider_rcppage_list");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ba.GetCount() > 2);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(nRNo > 0 ? "" : sRNo);
	if(!pRs.Execute(&pCmd)) 
		return; 

	if(pRs.GetRecordCount() == 0)
	{
		MessageBox("검색된 기사님이 존재하지 않습니다.", "확인", MB_ICONINFORMATION);
	}
	else
	{
		long nCompany, nRNo;

		pRs.GetFieldValue("lCode", nCompany);		
		pRs.GetFieldValue("nMNo", nRNo);		

		LU->ShowRiderInfoDlg(nCompany, nRNo);
	}

	m_edtShowRiderInfo.SetWindowText("");
	m_edtShowRiderInfo.SetFocus();
}

void CRcpView::OnBnClickedDeleteEditBtn()
{
	m_edtShowRiderInfo.SetWindowText("");
	//OnReceiptPrint();
	

}

void CRcpView::OnMakeNewRcpDlg()
{
	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0)
	{
		MessageBox("수정할 데이터를 선택하시기 바랍니다.", 
			"확인", MB_ICONEXCLAMATION);
		return;
	}

	if(GetItemSecondCross(nSelItem))
	{
		BOOL bTodayOrder = GetItemTodayOrder(nSelItem);
		ShowOrderLogDetailDlgFromTNo(GetItemTNo(nSelItem), GetItemState(nSelItem), GetItemSecondCross(nSelItem), bTodayOrder == TRUE ? FALSE : TRUE);
		return;
	}

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)
	m_nLastSelItemNo = GetItemTNo(nSelItem);

	CreateRcpDlg(LF->GetBranchInfo(GetItemCompany(nSelItem)),
		GetItemCName(nSelItem),
		m_nLastSelItemNo, 
		GetItemState(nSelItem),"",FALSE, -10, GetTickCount(), 
		0, FALSE, "", 0, TRUE);
}

BOOL CRcpView::CheckCrossOrder() 
{
	CXTPGridSelectedRows * pRows = m_xList.GetSelectedRows();
	
	if(pRows == NULL) return FALSE;
	if(pRows->GetCount() == ZERO) return FALSE;

	for(int i=ZERO; i<pRows->GetCount(); i++)
	{
		int nItem = pRows->GetAt(i)->GetIndex();
			
		if(GetItemSecondCross(nItem))
			return FALSE;
	}

	return TRUE;
}

void CRcpView::OnEnChangeShowRiderInfoEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnDtnDatetimechangeDatefrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	if(IsTodaySearch())
		ChangeSearchFilter();


	*pResult = 0;
}

void CRcpView::OnDtnDatetimechangeDateto(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	if(IsTodaySearch())
		ChangeSearchFilter();

	*pResult = 0;
}

OrderRecord* CRcpView::GetLastTimeOrderInVisibleRows()
{
	long nMaxTNo = 0;
	OrderRecord *pLastOrder = NULL;

	for(int i = 0; i < m_xList.GetRows()->GetCount(); i++)
	{
		int nItem = m_xList.GetRows()->GetAt(i)->GetIndex();
		OrderRecord *pOrder = m_vrCur->GetOrderRecord(nItem);
		nMaxTNo = max(pOrder->nTNo, nMaxTNo);

		if(nMaxTNo == pOrder->nTNo)
			pLastOrder = pOrder;
	}

	return pLastOrder;
}

void CRcpView::SaveStateRegForCheckFilter()
{ 
	UINT nFlag[] = {IDC_STATE_ALL_BTN3, IDC_STATE_RCP_BTN3, IDC_STATE_WAIT_BTN3, IDC_STATE_RESERVED_BTN3, IDC_STATE_ONLY_MAN_BTN3,
IDC_STATE_ALLOC_BTN3, IDC_STATE_PICKUP_BTN3, IDC_STATE_FINISH_BTN3, IDC_STATE_CANCEL_BTN3, IDC_STATE_ETC_BTN3};

	for (int i=0; i<STATE_BTN_COUNT; i++)
	{
		m_bSaveState[i] = ((CButton*)GetDlgItem(nFlag[i]))->GetCheck();
		//((CButton*)GetDlgItem(nFlag[i]))->SetCheck(TRUE);
	}

	//m_btnStateAll.SetCheck(TRUE);
	m_btnStateRcp.SetCheck(TRUE);
	m_btnStateWait.SetCheck(TRUE);
	m_btnStateReserved.SetCheck(TRUE);
	m_btnStateOnlyMan.SetCheck(TRUE);
	m_btnStateAlloc.SetCheck(TRUE);
	m_btnStatePickup.SetCheck(TRUE);
	m_btnStateFinish.SetCheck(TRUE);
	m_btnStateCancel.SetCheck(TRUE);
	m_btnStateEtc.SetCheck(TRUE);
	
	m_bIsSaveState = TRUE;
}

void CRcpView::LoadStateRegForCheckFilter()
{
	UINT nFlag[] = {IDC_STATE_ALL_BTN3, IDC_STATE_RCP_BTN3, IDC_STATE_WAIT_BTN3, IDC_STATE_RESERVED_BTN3, IDC_STATE_ONLY_MAN_BTN3,
IDC_STATE_ALLOC_BTN3, IDC_STATE_PICKUP_BTN3, IDC_STATE_FINISH_BTN3, IDC_STATE_CANCEL_BTN3, IDC_STATE_ETC_BTN3};

	for (int i=0; i<STATE_BTN_COUNT; i++)
		((CButton*)GetDlgItem(nFlag[i]))->SetCheck(m_bSaveState[i]);

	m_bIsSaveState = FALSE;
}

void CRcpView::OnDaeriShare()
{
	DaeriShare(TRUE);
}

void CRcpView::OnDaeriShareRelease()
{
	DaeriShare(FALSE);
}


void CRcpView::DaeriShare(BOOL bShare)
{
	if(m_ci.m_bUseCoaliShare == FALSE)
	{
		MessageBox("제휴오더 공유 기능을 사용하지 않습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	int nSelItem = m_xList.GetSelectedItem();
	int nTNo = GetItemTNo(nSelItem);

	if(GetItemSecondCross(nSelItem))
	{
		MessageBox("크로소배차된 오더를 대리에 공유 하실수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand cmd(m_pMkDb, "coali_dorder_share");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(bShare);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *parRetError = cmd.AddParameter(typeString, typeOutput, 500, "");

	if(!cmd.Execute())
		return;

	long nRet; parRet->GetValue(nRet);
	CString strError; parRetError->GetValue(strError);

	//if(strError.IsEmpty())
	if(nRet == 1)
	{
		if(bShare)
			MessageBox("제휴오더 공유 되었습니다", "확인", MB_OK);
		else
			MessageBox("제휴오더 공유 해제 되었습니다", "확인", MB_OK);

		RefreshList();
	}
	else
	{
		MessageBox(strError, "확인", MB_OK);
	}
}

void CRcpView::OnShowOrderLog()
{
	int nSelItem = m_xList.GetSelectedItem();
	BOOL bTodayOrder = GetItemTodayOrder(nSelItem);
	ShowOrderLogDetailDlgFromTNo(GetItemTNo(nSelItem), GetItemState(nSelItem), GetItemSecondCross(nSelItem), bTodayOrder == TRUE ? FALSE : TRUE);
	//int nSelItem = m_xList.GetSelectedItem();
	//ShowOrderLogDetailDlgFromTNo(GetItemTNo(nSelItem));
}

void CRcpView::OnCallPass()
{
	int nSelItem = m_xList.GetSelectedItem();
	int nTNo = GetItemTNo(nSelItem);

	if(GetItemSecondCross(nSelItem))
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_simple_info_for_callpass");
	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter("IS");

	if(!pRs.Execute(&pCmd)) 
		return;

	if(!pRs.IsEOF()) 
	{
		CInsungCallPassInfo info;
		long nStartRealDongID;

		pRs.GetFieldValue("sOPhone", info.strCID);

		pRs.GetFieldValue("sOName", info.strSCompany);
		pRs.GetFieldValue("sSDepart", info.strSDepart);
		pRs.GetFieldValue("nStartRealDongID", nStartRealDongID);
		pRs.GetFieldValue("sSDetail", info.strSDetail);
		pRs.GetFieldValue("sSPhone", info.strSPhone);

		pRs.GetFieldValue("sDName", info.strDCompany);
		pRs.GetFieldValue("sDDepart", info.strDDepart);
		pRs.GetFieldValue("sDDong", info.strDDong);
		pRs.GetFieldValue("sDDetail", info.strDDetail);
		pRs.GetFieldValue("sDPhone", info.strDPhone);

		pRs.GetFieldValue("sEtc", info.strEtc);
		pRs.GetFieldValue("nPayType", info.nPayType);
		pRs.GetFieldValue("nCarType", info.nCarType);
		pRs.GetFieldValue("nWayType", info.nWayType);
		pRs.GetFieldValue("nChargeSum", info.nCharge);
		pRs.GetFieldValue("nChargeTrans", info.nTransCharge);

		info.strSDong = m_poiNew.GetPOI(nStartRealDongID)->GetDongLi();

		m_cp.ToInsungCarType(info.nCarType);
		m_cp.CallPass(m_pMkDb, info);
	}
}
void CRcpView::OnEnChangeSearchInnerMemoEdit()
{
	ChangeSearchFilter();
} 

void CRcpView::OnEnChangeSearchMemoEdit()
{
	ChangeSearchFilter();
}

void CRcpView::OnMove(int x, int y)
{
	CRcpViewBase::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CRcpView::GetReceptCount(long &nCallCount, long &nReceiveCount, long &nRcpCount, long &nAllocCount, long &nCompleteCount, long &nCancelCount, long &nAllCount)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_recept_call_count");
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);

	if(!pRs.Execute(&pCmd))
		return;

	if(pRs.GetRecordCount() > 0)
	{ 
		pRs.GetFieldValue("nCall", nCallCount); 
		pRs.GetFieldValue("nReceive", nReceiveCount);
	}

	OrderRecordList &order = m_vrCur->GetOrderRecordList();
	OrderRecordList::iterator it;

	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	m_ToDT.GetTime(dtTo);

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nWCompany == m_ui.nCompany &&
			it->second.nWNo == m_ui.nWNo)
		{
			switch(it->second.nState)
			{
				case 10:
					nRcpCount++;
					break;
				case 11:
				case 30:
					nAllocCount++;
					break;
				case 35:
					nCompleteCount++;
					break;
				case 40:
					nCancelCount++;
					break;
			}

			nAllCount++;
		}
	}
}

void CRcpView::OnBnClickedShowMyCallCountBtn()
{
	long nCallCount = 0, nReceiveCount = 0, nRcpCount = 0, nAllocCount = 0, nCompleteCount = 0, nCancelCount = 0, nAllCount = 0;

	GetReceptCount(nCallCount, nReceiveCount, nRcpCount, nAllocCount, nCompleteCount, nCancelCount, nAllCount);

	CString strTemp = "";
	strTemp.Format("전화받은 건수 %d\r\n전화걸은 건수 %d\r\n\r\n접수 %d\r\n배차 : %d\r\n완료 : %d\r\n취소 : %d\r\n총콜수 : %d",
					nReceiveCount, nCallCount, nRcpCount, nAllocCount, nCompleteCount, nCancelCount, nAllCount);

	MessageBox(strTemp, "확인", MB_ICONINFORMATION);
}

BOOL CRcpView::RefreshListCardOkNumber()
{
	if(!LF->POWER_CHECK(1982, "승인번호컬럼 보기", FALSE))
		return FALSE;

	static BOOL bFirstCardOkNumberRefresh = TRUE;
	static DWORD dwTick = GetTickCount() - 100000;

	if(bFirstCardOkNumberRefresh == FALSE)
	{
		if(GetTickCount() - dwTick < 30000)
			return TRUE;
	}

	bFirstCardOkNumberRefresh = FALSE;

	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	m_ToDT.GetTime(dtTo);

	CMkCommand cmd(m_pMkDb, "select_rcp_card_ok_number");
	CMkRecordset rs(m_pMkDb);
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_ba.GetCount() > 2);
	cmd.AddParameter(dtFrom);
	cmd.AddParameter(dtTo);

	if(rs.Execute(&cmd))
	{
		OrderRecordList &order = m_vrOrder->GetOrderRecordList();
		CString strOkNumber;
		long nTNo;

		for(int i = 0; i < rs.GetRecordCount(); i++)
		{
			rs.GetFieldValue("nTNo", nTNo);
			rs.GetFieldValue("sOkNumber", strOkNumber);
			OrderRecordList::iterator it = order.find(nTNo);

			if(it != order.end())
			{
				if(it->second.nCreditCardType == NICE_CARD_COMPLETE || 
					it->second.nCreditCardType == NICE_CARD_COMPLETE_QUICKCALL)
				{			
					if(!m_ci.IsCrossCompany(it->second.nCompany))
						(*it).second.info[RCP_CARD_OK_NUMBER_COL] = strOkNumber;
					else
						(*it).second.info[RCP_CARD_OK_NUMBER_COL] = "N/A";

				}
			}

			rs.MoveNext();
		}

		dwTick = GetTickCount();
		return TRUE;
	}

	return FALSE;

}

void CRcpView::OnRecPlayer()
{
	int nItem = m_xList.GetSelectedItem();

	if(nItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	if(!LF->POWER_CHECK(2013, "녹취파일재생") && !LF->POWER_CHECK(2016, "본인접수파일듣기"))
	{
		
	}

	CXTPGridRecord* pRecord = m_xList.GetRows()->GetAt(nItem)->GetRecord();

	COleDateTime dtSearchDate = m_vrCur->GetOrderRecord(nItem)->dt0;
	int nSearchTNo = GetItemTNo(nItem);
	int nSearchCompany = GetItemCompany(nItem);
	CString sSearchTellNumber = GetItemPhone(nItem);

	if(!LF->POWER_CHECK(2013, "녹취파일재생"))
	{
		CString strOperator = GetItemCName(nItem);

		if(strOperator == m_ui.strName)
		{
			if(!LF->POWER_CHECK(2016, "본인접수파일듣기", TRUE))
				return;
		}
		else
		{
			MessageBox("녹취 파일듣기 권한이 없습니다.", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_record_file_name_tno");

	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(nSearchTNo);
	cmd.AddParameter("");
	cmd.AddParameter(sSearchTellNumber);
	cmd.AddParameter(dtSearchDate);

	if(!rs.Execute(&cmd))
		return;

	CString strReDate, strReKeyPhoneID, strReTellNumber, strReFileName, strReBound, strFolderDate;
	int nReTNo = 0, nReBound = 0, nRecordCount = rs.GetRecordCount();
	COleDateTime dtReDate;

	for (int nCount = 0; nCount < nRecordCount; nCount++)
	{
		rs.GetFieldValue("dtRegister", dtReDate);
		rs.GetFieldValue("nTNo", nReTNo);
		rs.GetFieldValue("sKeyPhoneID", strReKeyPhoneID);
		rs.GetFieldValue("sTellNumber", strReTellNumber);
		rs.GetFieldValue("sFileName", strReFileName);
		rs.GetFieldValue("nBound", nReBound);

		strFolderDate = LF->GetFolderDate(strReFileName);

		if (nCount == 0)
			m_PlayerDlg.InitPostFormData(dtReDate, strFolderDate, strReKeyPhoneID, strReTellNumber, strReFileName, nReBound);
		else
			m_PlayerDlg.AddPostFormData(dtReDate, strFolderDate, strReKeyPhoneID, strReTellNumber, strReFileName, nReBound);

		rs.MoveNext();
	}

	rs.Close();

	//전화기듣기
	if(nRecordCount > 0)
	{
		strFolderDate.Format("%s-%s-%s", strFolderDate.Left(4), strFolderDate.Mid(4, 2), strFolderDate.Right(2));
		PlayRecordFile(strFolderDate, strReFileName);
	}
	else
		AfxMessageBox("녹취파일이 없습니다.");
}

void CRcpView::PlayRecordFile(CString strDate, CString strFile)
{
	if(m_pCTIForm)
	{
		TRACE("View %s %s \n", strDate, strFile);
		m_pCTIForm->m_call.RecPlayMyKeyphone(strDate, strFile);
	}
}

void CRcpView::OnRecDownload()
{
	int nItem = m_xList.GetSelectedItem();

	if(nItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	CXTPGridRecord* pRecord = m_xList.GetRows()->GetAt(nItem)->GetRecord();

	COleDateTime dtSearchDate = m_vrCur->GetOrderRecord(nItem)->dt0;
	int nSearchTNo = GetItemTNo(nItem);
	int nSearchCompany = GetItemCompany(nItem);
	CString sSearchTellNumber = GetItemPhone(nItem);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_record_file_name_tno");

	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(nSearchTNo);
	cmd.AddParameter("");
	cmd.AddParameter(sSearchTellNumber);
	cmd.AddParameter(dtSearchDate);

	if(!rs.Execute(&cmd))
		return;

	CString strReDate, strReKeyPhoneID, strReTellNumber, strReFileName, strReBound, strFolderDate;
	int nReTNo = 0, nReBound = 0, nRecordCount = rs.GetRecordCount();
	COleDateTime dtReDate;

	for (int nCount = 0; nCount < nRecordCount; nCount++)
	{
		rs.GetFieldValue("dtRegister", dtReDate);
		rs.GetFieldValue("nTNo", nReTNo);
		rs.GetFieldValue("sKeyPhoneID", strReKeyPhoneID);
		rs.GetFieldValue("sTellNumber", strReTellNumber);
		rs.GetFieldValue("sFileName", strReFileName);
		rs.GetFieldValue("nBound", nReBound);

		strFolderDate = LF->GetFolderDate(strReFileName);

		if (nCount == 0)
			m_PlayerDlg.InitPostFormData(dtReDate, strFolderDate, strReKeyPhoneID, strReTellNumber, strReFileName, nReBound);
		else
			m_PlayerDlg.AddPostFormData(dtReDate, strFolderDate, strReKeyPhoneID, strReTellNumber, strReFileName, nReBound);

		rs.MoveNext();
	}

	rs.Close();

	if (nRecordCount == 1)
	{
		if(MessageBox("파일을 다운로드 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
			return;

		if(m_PlayerDlg.GetSafeHwnd() == NULL)
		{
			m_PlayerDlg.Create(IDD_RECPLAYER_DLG);
			m_PlayerDlg.CenterWindow();
		}
		m_PlayerDlg.Navigate();
		m_PlayerDlg.ShowWindow(SW_SHOW);
	}
	else if(nRecordCount > 1)
	{
		if(m_PlayerDlg.GetSafeHwnd() == NULL)
		{
			m_PlayerDlg.Create(IDD_RECPLAYER_DLG);
			m_PlayerDlg.CenterWindow();
		}
		m_PlayerDlg.Navigate();
		m_PlayerDlg.ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox("녹취파일이 없습니다.");
}

void CRcpView::OnBnClickedUseNewDlgChk()
{
	AfxGetApp()->WriteProfileInt("RcpPage", "bUseNewRcpDlg", m_chkUseNewDlg.GetCheck());
}

void CRcpView::OnBnClickedAutoScrollBtn()
{
	SetAutoScroll(!m_bAutoScroll, FALSE);
}

void CRcpView::SetAutoScroll(BOOL bAutoScroll, BOOL bChangeImage)
{
	m_bAutoScroll = bAutoScroll;
	m_btnAutoScroll.SetCheck(!m_bAutoScroll);
}

void CRcpView::SaveReportEnsureVisible(vector<UINT> &vecTNo, BOOL bFromOrderChange)
{
	if(bFromOrderChange)
		return;

	UINT nAreaRows = m_xList.GetReportAreaRows(m_xList.GetTopRowIndex(), TRUE);

	for(UINT i = m_xList.GetTopRowIndex(); i < m_xList.GetTopRowIndex() + nAreaRows + 1; i++)
	{
		if(m_xList.GetRows()->GetCount() <= (int)i)
			break;

		if(GetItemTNo(i) > 0)
			vecTNo.push_back(GetItemTNo(i));
	}

	//int nItem = m_xList.GetSelectedItem();
	//if(nItem >= 0)
	//	m_nLastSelItemNo = GetItemTNo(nItem);

	m_bReportReadyToPopulate = TRUE;
}

void CRcpView::LoadReportEnsureVisible(vector<UINT> &vecTNo, int &nSortCol, BOOL &bAsc, BOOL bFromOrderChange)
{
	//시간순으로 정렬되어 있는 경우만, 최하위로 가도록 함
	if(m_bAutoScroll && IsNeedAutoScroll(nSortCol) && bFromOrderChange == FALSE)
	{
		CXTPGridRow *pRow = m_xList.GetRows()->GetAt(bAsc ? (m_xList.GetRows()->GetCount() - 1) : 0);
		m_xList.EnsureVisible(pRow);
	}
	else 
	{
		vector<UINT>::reverse_iterator it;

		for(it = vecTNo.rbegin(); it != vecTNo.rend(); it++)
		{
			int nRow = m_vrOrder->GetItemRowFromTNo(*it);

			if(nRow >= 0)
			{
				CXTPGridRow *pRow = m_xList.GetRows()->GetAt(nRow);
				m_xList.EnsureVisible(pRow);
				break;
			}
		}

		if(m_nLastSelItemNo > 0)
		{
			int nRow = m_vrOrder->GetItemRowFromTNo(m_nLastSelItemNo);
			if(nRow >= 0)
			{
				m_xList.GetSelectedRows()->Select(m_xList.GetRows()->GetAt(nRow));
				m_xList.SetFocusedRow(m_xList.GetRows()->GetAt(nRow));
			}
		}		
	}

	m_bReportReadyToPopulate = FALSE;
}

BOOL CRcpView::IsNeedAutoScroll(int nSortCol)
{
	return !m_bStateSecondSort && 
		(nSortCol == RCP_TNO_COL || nSortCol == RCP_TIME_COL || nSortCol == RCP_RESERVE_COL );
		//(nSortCol == RCP_TNO_COL || nSortCol == RCP_TIME_COL || nSortCol == RCP_DATE_COL);
}

void CRcpView::OnReportVScroll(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTSCROLL *pItemNotify = reinterpret_cast<XTP_NM_REPORTSCROLL*>(pNotifyStruct);

	int nCol, nRows;
	BOOL bAsc, bScroll;

	m_xList.GetSortCol(&nCol, &bAsc);

	if(IsNeedAutoScroll(nCol))
	{
		nRows = m_xList.GetReportAreaRows(m_xList.GetTopRowIndex(), TRUE);

		if(bAsc)
			bScroll = ((int)(nRows + m_xList.GetTopRowIndex()) >= m_xList.GetRows()->GetCount() - 1);
		else
			bScroll = m_xList.GetTopRowIndex() == 0;

		if(!m_bReportReadyToPopulate)
			SetAutoScroll(bScroll);
	}
}

BOOL CRcpView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nCol, nRows;
	BOOL bAsc, bScroll;

	m_xList.GetSortCol(&nCol, &bAsc);
	if(IsNeedAutoScroll(nCol))
	{
		nRows = m_xList.GetReportAreaRows(m_xList.GetTopRowIndex(), TRUE);

		if(bAsc)
			bScroll = ((int)(nRows + m_xList.GetTopRowIndex()) >= m_xList.GetRows()->GetCount() - 1);
		else
			bScroll = m_xList.GetTopRowIndex() == 0;

		SetAutoScroll(bScroll);
	}

	return CRcpViewBase::OnMouseWheel(nFlags, zDelta, pt);
}

void CRcpView::OnJinsangCallingDeny()
{
	CMkLock lock(&m_csOrder);

	int nItem = m_xList.GetSelectedItem();
	if(nItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return;
	}

	CString strPhone1 = LF->GetNoneDashNumber(GetItemPhone(nItem));
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

	if(m_pCTIForm->m_bConnected)
	{
		m_pCTIForm->m_call.DenialAnswer(dlg.m_sTelNumber, atol(szDenialDuration), dlg.m_sName, dlg.m_sDesc);
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



LRESULT CRcpView::OnSaveRcpList(WPARAM wParam, LPARAM lParam)
{
	//ShellExecute(m_hWnd, "open", "regedit.exe", "/e c:\\aaa.reg HKEY_CURRENT_USER\\Software\\Logisoft\\Daeri\\ReportControl", NULL, SW_HIDE);

	CString strRcpList; long nSize;
	SaveReportState(strRcpList, nSize);

	CMkCommand cmd(m_pMkDb, "update_rcp_list");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(strRcpList);
	cmd.AddParameter(nSize);
	cmd.AddParameter(0);

	if(cmd.Execute())
		return 1;


	return 0;
}

LRESULT CRcpView::OnLoadRcpList(WPARAM wParam, LPARAM lParam)
{
	//HKEY rootKey;	
	//ShellExecute(NULL, "open", "c:\\aaa.reg", "", NULL, SW_SHOW);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_list");
	cmd.AddParameter(m_ui.nCompany); 
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return 0;

	if(rs.GetRecordCount() == 0)
		return 0;

	CString strRcpList;
	long nSize;

	rs.GetFieldValue("sData", strRcpList);
	rs.GetFieldValue("nSize", nSize);

	BYTE *pData = new BYTE[nSize];

	long nItem = 0;

	long nCount = strRcpList.GetLength();

	for(int i=0; i<nCount; i = i+2)
	{
		CString strTemp = strRcpList.Mid(i, 2);
		pData[nItem++] = LF->HexStrToInt(strTemp);
	}

	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), _T("State"), pData, nSize);
	LoadReportState();


	return 1;
}

LRESULT CRcpView::OnSaveCtiList(WPARAM wParam, LPARAM lParam)
{
	//ShellExecute(m_hWnd, "open", "regedit.exe", "/e c:\\aaa.reg HKEY_CURRENT_USER\\Software\\Logisoft\\Daeri\\ReportControl", NULL, SW_HIDE);

	return m_pCTIForm->OnSaveReportState();
}

LRESULT CRcpView::OnLoadCtiList(WPARAM wParam, LPARAM lParam)
{
	//HKEY rootKey;	
	//ShellExecute(NULL, "open", "c:\\aaa.reg", "", NULL, SW_SHOW);

	return m_pCTIForm->OnLoadReportState();
	return 1;
}

void CRcpView::OnAutoWait()
{
	CMkLock lock(&m_csOrder);

	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0) {
		return;
	}

	if(GetItemSecondCross(nSelItem))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더 자동대기 설정 하실 수 없습니다";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	long nTNo = GetItemTNo(nSelItem);
	BOOL bAutoWait = GetItemAutoWait(nSelItem);

	CMkCommand cmd(m_pMkDb, "update_auto_wait_state");
	cmd.AddParameter(nTNo);
	cmd.AddParameter(bAutoWait);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);

	if(!cmd.Execute()) return;

	MessageBox("상태가 변경되었습니다", "확인", MB_ICONINFORMATION);

	RefreshList();
}

void CRcpView::OnDelayNoticeRelesae()
{
	ChangeDelayNoticeState(FALSE);
}

void CRcpView::OnDelayNotice()
{
	ChangeDelayNoticeState(TRUE);
}

void CRcpView::ChangeDelayNoticeState(BOOL bSetting)
{
	CMkLock lock(&m_csOrder);

	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0) {
		return;
	}

	long nTNo = GetItemTNo(nSelItem);

	CMkCommand cmd(m_pMkDb, "update_delay_notice_1");
	cmd.AddParameter(nTNo);
	cmd.AddParameter(bSetting);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);

	if(!cmd.Execute()) return;

	if(bSetting)
		MessageBox("지연알림 설정되었습니다", "확인", MB_ICONINFORMATION);
	else
		MessageBox("지연알림 해제되었습니다", "확인", MB_ICONINFORMATION);

	RefreshList();
}

void CRcpView::OnUseUpCharge1()
{
	UpChange(m_pBi->nUpChargeForNotAllocate1);
}

void CRcpView::OnUseUpCharge2()
{
	UpChange(m_pBi->nUpChargeForNotAllocate2);
} 

void CRcpView::OnUseUpCharge3()
{
	UpChange(m_pBi->nUpChargeForNotAllocate3);
}

void CRcpView::OnUseUpChargeRelease()
{
	UpChange(-1);
}


BOOL CRcpView::UpChange(long nCharge)
{
	int nSelItem = m_xList.GetSelectedItem();
	if(nSelItem < 0) {
		LF->MsgBox(IDS_INVALID_ITEM);
		return FALSE;
	}

	if(GetItemSecondCross(nSelItem))
	{

		CString strMsg;
		strMsg = "크로스배차된 오더를 직접 요금인상 하실수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 취소 요청을 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(m_pBi->nUseUpChargeForNotAllocate == 0)
		return FALSE;

	LF->UpChargeForNotAllocate(GetItemTNo(nSelItem), nCharge, this);

	RefreshList();

	return TRUE;
}

long CRcpView::GetRiderAndInsertOperatorLog(long nCallCompany, CString strCID, long &nRiderCompany, long &nRNo)
{
	long nOperatorID = -1;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_phone_and_insert_operator_log2");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	cmd.AddParameter(nCallCompany);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);	
	cmd.AddParameter(strCID);
	cmd.AddParameter(m_pBi->nShareCode1);
	cmd.AddParameter(m_pBi->nShareCode2);
	cmd.AddParameter(m_pBi->nShareCode3);
	cmd.AddParameter(m_pBi->nShareCode4);
	cmd.AddParameter(m_pBi->nShareCode5);

	if(!rs.Execute(&cmd))
		return -1;

	parRet->GetValue(nOperatorID);

	if(rs.GetRecordCount() > 0)
		SearchAllocatedRiderFromOrder(rs, nRiderCompany, nRNo);

	return nOperatorID;
}

void CRcpView::SearchAllocatedRiderFromOrder(CMkRecordset &rs, long &nRiderCompany, long &nRNo)
{
	OrderRecordList &OrderList = m_vrOrder->GetOrderRecordList();
	COleDateTime dtBase = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 30, 0);
	vector<OrderRecord*> vecOrder, vecRider;
	vector<OrderRecord*>::iterator itOrder;
	nRiderCompany = 0;

	transform(OrderList.begin(), OrderList.end(), std::back_inserter(vecOrder), second_ptr(OrderList));
	itOrder = remove_if(vecOrder.begin(), vecOrder.end(), IsNotMyAllocatedOrder);
	vecOrder.erase(itOrder, vecOrder.end());
	sort(vecOrder.begin(), vecOrder.end(), COrderRecordRiderSortFunc());

	long nDbRiderCompany = 0, nDbRNo = 0;
	BOOL bCompanyRider = FALSE; //자사기사 체크유무

	for(int i = 0; i < rs.GetRecordCount(); i++)
	{
		long _nCompany, _nRNo;

		rs.GetFieldValue("nCompany", _nCompany);
		rs.GetFieldValue("nRNo", _nRNo);

		if(i == 0 && _nCompany > 0 && _nRNo > 0)
		{
			nDbRiderCompany = _nCompany;
			nDbRNo = _nRNo;
		}

		//자사 기사를 먼저 선택, 자사 기사 없으면 제일 첫 기사를 선택
		if(!m_ci.IsCrossCompany(_nCompany) && !bCompanyRider)
		{
			nRiderCompany = _nCompany;
			nRNo = _nRNo;
			bCompanyRider = TRUE;
		}
		else if(!nRiderCompany)
		{
			nRiderCompany = _nCompany;
			nRNo = _nRNo;
		}

		itOrder = lower_bound(vecOrder.begin(), vecOrder.end(), make_pair(_nCompany, _nRNo), COrderRecordRiderSortFunc());

		if(itOrder != vecOrder.end() && 
			(*itOrder)->nRiderCompany == _nCompany && 
			(*itOrder)->nRNo == _nRNo) 
		{
			vecRider.push_back(*itOrder);
		}

		rs.MoveNext();
	}

	//가장 나중에 일어난 오더와 관련된 기사를 선택
	if(vecRider.size() > 0)
	{
		sort(vecRider.begin(), vecRider.end(), COrderRecordRiderTimeSortFunc());
		nRiderCompany = vecRider[0]->nRiderCompany;
		nRNo = vecRider[0]->nRNo;
	}

	if(nRiderCompany <= 0 && nRNo <= 0 && nDbRiderCompany > 0 &&  nDbRNo > 0)
	{
		nRiderCompany = nDbRiderCompany;
		nRNo = nDbRNo;
	}
}