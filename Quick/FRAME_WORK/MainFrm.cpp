// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "resource.h"
#include "QuickDoc.h"
#include "HomeView.h"
#include "RcpView.h"
#include "CustomerView.h"
#include "StaffViewNew.h"
#include "ReportView.h"
#include "ReportRiderView.h"
#include "QuickView.h"
#include "MainFrm.h"
#include "CustomerDlg.h"
#include "RiderMsgDlg.h"
#include "ShareProgDlg.h"

#include "CidDlg.h"
#include "LogonDlg.h"
#include "Mmsystem.h"
//#include "OptionDlg.h"
//#include "FAQHtmlView.h"
#include "BillDlg.h"
#include "IntercallNoticeDlg.h"
#include "NewMsgDlg.h"
#include "CidGroupDlg.h"
#include "ChargeDongNewDlg.h"

//#include "XTPFrameWnd.h"
//#include "XTPTaskPanel.h"
#include "DummyView.h"
#include "TestVirtualCIDDlg.h"

#include "ChargeDongDlg2.h"
#include "ChargeDongDlg3.h"
#include "AuthManageDlg.h"
#include "AuthManageLogDlg.h"
#include "AuthLogDlg.h"

#include "IncomeView.h"
#include "StatView.h"
#include "MkMessenger.h"
#include "RcpDlg.h"
#include "RecvCidDlg.h"

//#include "EmptyCarDlg.h"
#include "EmptyCarDlg1.h"
#include "AllocatePaneDlg.h"
#include "ChangeColorDlg.h"
#include "MoveOrderLogDlg.h"

#include "MainOptionDlg2011.h"


#include "AllocateBoardDlg.h"
#include "RiderMapDlg.h"
#include "ShareReportRateDlg.h"

#include "ConnListDlg2.h"
#include "ShareOrderDlg.h"
#include "CallCountDlg.h"
#include "RcpPowerDlg.h"
#include "NewMsgDlg.h"
#include "QueryChargeDlg.h"
#include "AllocateGroupDlg.h"
#include "ScheduleOrderListDlg.h"
#include "DelayOrderDlg2.h"
#include "BranchFormView.h"
 
//#include "IncomeForm7.h"
#include "CompleteAfterEditDlg.h"
#include "RcpCopyData.h"
#include "MyMkMessenger.h"
#include "CorporationDlg.h"
#include "ShareReportBranchSetDlg.h"
#include "AllocateBoardTRSDlg.h"
#include "ShareRcpPageView.h"
#include "DepositJobDlg.h"
#include "OtherRegionBranchDlg.h"
#include "BranchReportMainDlg.h"
#include "POIDataNew.h"
#include "MakePOIData.h"
#include "CustomerData.h"
#include "ChargeDongUDlg.h"
#include "GroupChatDlg.h"

#include "NotifierContainer.h"
#include "CustomerCacheInfoDlg.h"
#include "MoveRiderNewDlg.h"
#include "OrderChangeRequestDlg.h"

#include "..\Include\voip\WalkieTalkieDlg.h"
#include "OtherRiderTransferDlg.h"
#include "CaptureUpload.h"

#include "TransferSmsBetweenShareBalanceDlg.h"
#include "SmsNewBulkDlg.h"
#include "InsStaffDlg1.h"
#include "GeneralRecepitDlg.h"
#include "HolidayDeliveryInfoDlg.h"
#include "SetPoiDlg.h"
#include "GenerateAppStateDlg2.h"
#include "GenerateOpenAPIStateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_POPUP_CLOSE (-1)
#define ID_GOTO_ORDER_CHANGE_PAGE (-2)
#define ID_DO_NOT_SHOW (-3)
#define ID_TRANS_INFORMATION_UPDATE (-4)

#define WM_COPYDATA_PROXY		WM_USER + 100
#define	WM_SET_ALLOC_STATE		WM_USER + 501
#define ID_TEST_FIELDCHOOSER_CUSTOMER WM_USER + 600

#define ID_MENU_SHOW_HOLIDAY_DELIVERY	1235

#define SetAllocSocketState(msg)	::PostMessage(this->GetSafeHwnd(), WM_SET_ALLOC_STATE, (WPARAM)msg, 0)


const char *ALLOC_CONNECTED	=		"배차서버 연결됨";
const char *ALLOC_CONTROL_OK	=	"배차메시지 받는중";
const char *ALLOC_DISCONNECTED =	"배차서버 연결끊김";
const char *ALLOC_INIT_FAILED	=	"네트워크 초기화 실패";
const char *ALLOC_CONNECT_FAILED =	"배차서버 연결실패";
const char *ALLOC_REQUEST_FAIL =	"배차메시지 요청실패";
const char *ALLOC_LOSE		=		"배차메시지 중지";
const char *ALLOC_GET_FAIL	=		"배차메시지 못받음";

const char *CONTROL_REQUEST_FAIL =	"제어권 요청실패";
const char *CONTROL_LOSE		=	"제어권 해제됨";
const char *CONTROL_GET_FAIL	=	"제어권 획득실패";



// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CFrameWnd::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_RCP_TAB, m_RcpTabCtrl);
}

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	ON_COMMAND(ID_PROG_SHARE, OnProgShare)
	ON_COMMAND(IDM_VIEW_PAY, OnViewPay)
	ON_COMMAND(IDM_VIEW_CAR, OnViewCar)
	ON_COMMAND(IDM_VIEW_CUSTOMER, OnViewCustomer)
	ON_COMMAND(IDM_MANAGER, OnManager)
	ON_COMMAND(IDM_VIEW_STANDARD, OnViewStandard)
	ON_COMMAND(IDM_VIEW_DELIVERYSTANDARD, OnViewDeliveryStandard)
	ON_COMMAND(IDM_VIEW_REPORT_CUSTOMER, OnViewReportCustomer)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_REPORT_CUSTOMER, OnUpdateViewReportCustomer)
	ON_COMMAND(IDM_VIEW_REPORT_RIDER, OnViewReportRider)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_REPORT_RIDER, OnUpdateViewReportRider)
	ON_COMMAND(ID_VIEW_INCOME, OnViewIncome)
	ON_COMMAND(ID_VIEW_STAT, OnViewStat)
	ON_COMMAND(ID_VIEW_CID, OnViewCid)
	ON_COMMAND(IDM_LOGOUT, OnLogout)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_OPTION, OnOption)
	ON_COMMAND(ID_MESSENGER, OnMessenger)
	ON_COMMAND(ID_CALL_COUNT, OnCallCount)
	ON_COMMAND(ID_REMOTE_CONTROL_WEB, OnRemoteControlWeb)
	ON_COMMAND(ID_ALLOCATE_BOARD, OnAllocateBoard)
	ON_COMMAND(ID_RIDER_MAP, OnRiderMap)
	ON_COMMAND(ID_OTHER_REGION_BRANCH, OnOtherRegionBranch)
	ON_COMMAND(ID_BRANCH_TRANSFER, OnBranchTransfer)
	ON_COMMAND(ID_MOVE_RIDER, OnMoveRider)
	ON_COMMAND(ID_SHOW_PRE_CHARGE, OnMShowPreCharge)
	ON_COMMAND(ID_SEND_BULK_SMS, OnSendBulkSms)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_STANDARD, OnUpdateViewStandard)
	ON_UPDATE_COMMAND_UI(IDM_MANAGER, OnUpdateManager)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_CUSTOMER, OnUpdateViewCustomer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INCOME, OnUpdateViewIncome)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STAT, OnUpdateViewStat)
	ON_UPDATE_COMMAND_UI(ID_MESSENGER, OnUpdateMessenger)
	ON_UPDATE_COMMAND_UI(ID_CALL_COUNT, OnUpdateCallCount)
	ON_UPDATE_COMMAND_UI(ID_ALLOCATE_BOARD, OnUpdateAllocateBoard)
	ON_UPDATE_COMMAND_UI(ID_RIDER_MAP, OnUpdateRiderMap)
	ON_UPDATE_COMMAND_UI(ID_OTHER_REGION_BRANCH, OnUpdateOtherRegionBranch)
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_COPYDATA()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCLBUTTONDOWN()
	ON_COMMAND(ID_SCHEDULE_JOB, OnScheduleJob)
	ON_COMMAND(ID_SEND_MAC, OnSendMac)
	ON_MESSAGE(WM_TASKBARNOTIFIERCLICKED,OnTaskbarNotifierClicked)
	//ON_COMMAND(ID_SHOW_NOTICE, OnShowNotice)
	ON_COMMAND(ID_SHOW_SECURITY_LOG, OnShowSecurityLog)
	ON_MESSAGE(WM_NOTIFIER_CLICKED, OnNotifierClicked)
	ON_MESSAGE(WM_SET_MSG_STATE, OnSetMsgState)
	ON_MESSAGE(WM_SET_INTERCALL_STATE, OnSetIntercallState)
	ON_MESSAGE(WM_SET_ALLOC_STATE, OnSetAllocState)
	ON_COMMAND_RANGE(ID_REMOTE_CONTROL1, ID_REMOTE_CONTROL20, OnRemoteControl)
	ON_COMMAND(ID_DEBUG_MODE, OnDebugMode)
	ON_COMMAND(ID_BILL, OnBill)
	ON_COMMAND(ID_INTERCALL_NOTICE, OnIntercallNotice)
	ON_COMMAND(ID_INTERCALL_CONN_LIST, OnIntercallConnList)
	ON_COMMAND(ID_ACCESS_CONTROL, OnAccessControl)
	ON_COMMAND(ID_NEW_RIDER_LIST, OnNewRiderList)
	ON_COMMAND(ID_CID_GROUP, OnCidGroup)
	ON_COMMAND(ID_ALLOCATE_GROUP, OnAllocateGroup)
	ON_COMMAND(ID_MOVE_ORDER, OnMoveOrder)
	ON_COMMAND(ID_AUTH_MANAGE, OnAuthManage)
	ON_COMMAND(ID_AUTH_LOG, OnAuthLog)
	ON_COMMAND(ID_AUTH_MANAGE_LOG, OnAuthManageLog)
	ON_COMMAND(ID_SHARE_REPORT_RATE, OnShareReportRate)
	ON_COMMAND(ID_ATTEND, OnAttend)
	ON_COMMAND(ID_GET_OFF, OnGetOff)
	ON_COMMAND(ID_TRANSFER_SMS_BETWEEN_SHARE_BALANCE, ShowTrasferSmsToShaerBalance)
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY , OnTaskPanelNotify)
	ON_COMMAND(ID_TEST_VIRTUAL_CID, OnTestVirtualCid)
	ON_COMMAND(IDM_VIEW_HOME, OnViewHome)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_HOME, OnUpdateViewHome)
	ON_MESSAGE(WM_USER+887, OnQueryChargeResponse)
	ON_MESSAGE(WM_USER+888, OnRcpCopyData)
	ON_MESSAGE(WM_USER+889, OnRcpCopyDataDirect)
	ON_MESSAGE(WM_USER+890, OnGroupChatResonse)
	ON_MESSAGE(WM_CLOSE_RIDER_DLG, OnCloseRiderDlg)
	ON_MESSAGE(WM_CLOSE_RIDER_MAP_DLG, OnCloseRiderMapDlg)
	ON_MESSAGE(WM_CLOSE_RECV_CID_DLG, OnCloseShowRecvCidDlg)
	ON_COMMAND(ID_RUN_TELCLIENT, OnRunTelclient)
	ON_COMMAND(ID_SHARE_REPORT_BRANCH_SET, OnShareReportBranchSet)
	ON_COMMAND(ID_SCHEDULE_ORDER, OnScheduleOrder)
	ON_COMMAND(ID_COMPLETE_AFTER_EDIT, OnCompleteAfterEdit)
	ON_MESSAGE(XTPWM_POPUPCONTROL_NOTIFY, OnPopUpNotify)
	ON_COMMAND(ID_TRS_BOARD_DLG, OnTrsBoardDlg)
	ON_MESSAGE(WM_CLOSE_TRS_BOARD_DLG, OnCloseTRSBoardDlg)
	ON_COMMAND(ID_DELETE_POI_FILE, &CMainFrame::OnDeletePoiFile)
	ON_COMMAND(ID_RIDER_SHARE_BOARD, OnRiderShareBoard)
	ON_COMMAND(ID_RIDER_BOARD, OnRiderBoard)
	ON_COMMAND(ID_CHARGE_FOR_RIDER, OnChargeForRider)
	ON_COMMAND(ID_CALC, &CMainFrame::OnCalc)	
	ON_COMMAND(ID_FUNCTION_TABLE, &CMainFrame::OnFunctionTable)
	ON_COMMAND(ID_REMAKE_CUSTOMER_DATA, &CMainFrame::OnRemakeCustomerData)
	ON_COMMAND(ID_ORDER_REQUEST, OnOrderRequest)
	ON_COMMAND(ID_GENERAL_RECEPIT_REQUEST, OnGeneralRecepitRequest)	
	ON_MESSAGE(WM_RECV_CID, OnRecvCid)
	ON_COMMAND(ID_OTHER_RIDER_INCOME, OnOtherRiderIncome)
	ON_XTP_CREATECONTROL()
	ON_COMMAND(ID_MENU_GENERAL_APP_REGISTER, OnGeneralAppRegister)
	ON_COMMAND(ID_MENU_GENERAL_OPENAPI_REGISTER, OnGeneralOpenAPIRegister)
	ON_COMMAND(ID_MENU_GENERAL_OPENAPI_REGISTER, OnGeneralOpenAPIRegister)
	ON_COMMAND(ID_RUN_Q5, OnRunQ5)

	ON_COMMAND(ID_MENU_SHOW_HOLIDAY_DELIVERY, OnShowHolidayDelivery)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_MESSENGER,
	ID_INDICATOR_INTERCALL,
	ID_INDICATOR_ALLOC,
	ID_INDICATOR_RECEPT,
	ID_INDICATOR_DATETIME,
	ID_INDICATOR_SHARE_BALANCE
};


void SetIcons(UINT nNormal, UINT nHot, UINT nDisabled)
{
	CBitmap bmpNormal;
	VERIFY(bmpNormal.LoadBitmap(nNormal));
	XTPImageManager()->SetIcons(IDR_MAINFRAME, bmpNormal);

	CBitmap bmpHot;
	VERIFY(bmpHot.LoadBitmap(nHot));
	XTPImageManager()->SetIcons(IDR_MAINFRAME, bmpHot, xtpImageHot);

	CBitmap bmpDisabled;
	VERIFY(bmpDisabled.LoadBitmap(nDisabled));
	XTPImageManager()->SetIcons(IDR_MAINFRAME, bmpDisabled, xtpImageChecked);

}

void CMainFrame::ShowHolidayDeliveryDlg(BOOL bIgnoreInsert)
{
	if(m_ui.nRole == 0)
	{
		if(CHolidayDeliveryInfoDlg::IsHolidayCompany(bIgnoreInsert))
		{
			CHolidayDeliveryInfoDlg dlgH;
			dlgH.DoModal();
		}
	}
}

void CMainFrame::OnShowHolidayDelivery()
{
	ShowHolidayDeliveryDlg();
}
// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	m_nStatusAccessTime = 0;
	m_bGroup = FALSE;
	m_pIntercall = NULL;
//	m_pLogiMapDlg = NULL;
	m_pbiCur = NULL;
	m_bApplicationInit = FALSE;
	m_nCurView = 0;

	m_pChargeDistanceDlg = NULL;

	m_bNoQueryExit = FALSE;
	m_pScheduleOrderListDlg = NULL;

	m_pChargeDongDlg = NULL;
	m_bRcpPageInitCompleted = FALSE;

	m_pActivePopup = NULL;
	m_ptPopup = CPoint(-1, -1);

	m_bShowOrderChangePopup = TRUE;
	m_pwndTaskPanel = NULL;
	m_nOrderRequestCount = 0;
}

CMainFrame::~CMainFrame()
{
//	if(m_pLogiMapDlg != NULL)
//	{
// 		delete m_pLogiMapDlg;
//		m_pLogiMapDlg = NULL;
//	}
	if(m_pChargeDongDlg)
	{
		delete m_pChargeDongDlg;
		m_pChargeDongDlg = NULL;
	}

	//if(m_pChargeDistanceDlg != NULL)
	//{
	//	delete m_pChargeDistanceDlg;
	//	m_pChargeDistanceDlg = NULL;
	//}


	if(m_pActivePopup != NULL)
	{
		delete m_pActivePopup;
		m_pActivePopup = NULL;
	}

	while (!m_lstPopupControl.IsEmpty()) 
	{
		delete m_lstPopupControl.RemoveTail();
	}

	DELETE_OBJECT(g_bana_log);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	 ModifyStyle(0, WS_SYSMENU,0);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      
	}

	if (!InitCommandBars())
	{
		return -1;      // fail to create
	}

	XTPPaintManager()->SetTheme(xtpThemeNativeWinXP);
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->SetMenu(_T("메뉴바"), IDR_MAINFRAME);
	XTPImageManager()->SetMaskColor(RGB(255, 0, 255));

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("툴바"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
	}

	pCommandBar->EnableDocking(xtpFlagAlignAny | xtpFlagFloating | xtpFlagStretched | xtpFlagHideWrap);
	pCommandBar->ShowTextBelowIcons(TRUE);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);
	SetIcons(IDB_SMALL_LIST1, IDB_SMALL_LIST1, IDB_SMALL_LIST1);

	GetCommandBars()->GetCommandBarsOptions()->szIcons = CSize(16, 16);
	GetCommandBars()->GetCommandBarsOptions()->szLargeIcons = CSize(16, 16);
	GetCommandBars()->GetCommandBarsOptions()->bShowExpandButtonAlways = FALSE;

	LU->SetWindowTitleWithVersion();
	InitControl();

	PostMessage(WM_SYSCOLORCHANGE);
	LU->StartMessenger();
	SetForegroundWindow();

	SetTimer(UPLOAD_TIMER, 5000, NULL);

#ifndef _DEBUG
	ShowHolidayDeliveryDlg(FALSE);
#endif 

	return 0;
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
	CWnd* pWnd = NULL;
	m_mapPanes.Lookup(pPane->GetID(), pWnd);

	if(wParam == XTP_DPN_SHOWWINDOW)
	{
		if(!pPane->IsValid())
		{
			if(pPane->GetID() == IDR_PANE_NETWORK)
			{
				if(LU->CreateToolBox(&m_pwndTaskPanel, this))
				{
					LU->SetTaskPanel(m_pwndTaskPanel);
					pPane->Attach(m_pwndTaskPanel);
					LU->ResetToolboxItems(m_pwndTaskPanel);
				}
			}
			else 
			{
				pPane->Attach(pWnd);
			}
		}

		return TRUE; // handled
	}
	else if(wParam == XTP_DPN_CLOSEPANE)
	{
		pPane->Hide();			
		return XTP_ACTION_NOCLOSE;
	}
	else if(wParam == XTP_DPN_ACTION )
	{
		XTP_DOCKINGPANE_ACTION* pAction = (XTP_DOCKINGPANE_ACTION*)lParam;
		if(pAction->action == xtpPaneActionDocked)
			LU->m_pAllocatePane->SetPaneDocking(TRUE);

		if(pAction->action == xtpPaneActionClosing || 
			pAction->action == xtpPaneActionClosed || 
			pAction->action == xtpPaneActionCollapsing ||
			pAction->action == xtpPaneActionCollapsed)
		{
			if(LU->m_pConnListPane)
				LU->m_pConnListPane->HideAllocList(); 
		}

		return TRUE;		
	}
	else if(wParam == XTP_DPN_RCLICK)
	{
	}
	
	return FALSE;
}


LRESULT CMainFrame::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
	return LU->OnTaskPanelNotify(wParam, lParam, LU->m_pwndPaneNetwork, &LU->m_paneManager, LU->m_pwndCur);
}

CXTPDockingPane* CMainFrame::CreatePane(CRuntimeClass* pNewViewClass, 
										CString strFormat, 
										XTPDockingPaneDirection direction, 
										CXTPDockingPane* pNeighbour,
										long nID,
										CRect &rect)

{
	CXTPDockingPane* pwndPane = LU->m_paneManager.CreatePane(
		nID, rect, direction, pNeighbour);

	pwndPane->SetTitle(strFormat);

	CFrameWnd* pFrame = new CFrameWnd;

	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = GetActiveView()->GetDocument();

	pFrame->Create(NULL, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, NULL, 0, &context);
	pFrame->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	m_mapPanes.SetAt(nID, pFrame);

	return pwndPane;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	LU->CreateSplitter(this, pContext);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	LPCSTR lpzsNewName = "quick2.0 by logisoft";
	WNDCLASS wndcls;

	BOOL bRes = CFrameWnd::PreCreateWindow( cs ); // if MDI, CMDIFrameWnd
	HINSTANCE hInst = AfxGetInstanceHandle();

	// see if the class already exists
	if (!::GetClassInfo( hInst, lpzsNewName, &wndcls ) )
	{
		// get default stuff
		::GetClassInfo( hInst, cs.lpszClass, &wndcls );
		// register a new class
		wndcls.lpszClassName = lpzsNewName;
		wndcls.hIcon = ::LoadIcon(hInst,MAKEINTRESOURCE(IDR_MAINFRAME));
		::RegisterClass( &wndcls );
	}
	cs.lpszClass = lpzsNewName;
	cs.cx = 1024;
	cs.cy = 768;

	int a,b;
    a = ::GetSystemMetrics(SM_CXSCREEN); 
    b = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.x = (a - cs.cx)/2 ;
    cs.y = (b - cs.cy)/2; 
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}


// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 메시지 처리기
void CMainFrame::InitControl()
{
	LU->m_paneManager.InstallDockingPanes(this);
	LU->m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	LU->m_paneManager.SetFloatingFrameCaption(_T("팝업상태"));
	LU->m_paneManager.SetThemedFloatingFrames(TRUE);
	LU->m_paneManager.SetAnimationDelay(-1, 1, 1);

	//사용자 설정
	CString strCaption;
	strCaption.Format("%s(%d)", m_ui.strName, m_ui.nWNo);
	m_wndStatusBar.SetPaneText(ID_PANE_RECEPT, strCaption);


	int nIDIcons[] = {1, 2, 3, 4, 5, 6};
	LU->m_paneManager.SetIcons(IDB_PANE_ICONS, nIDIcons, 7, RGB(255, 0, 255));


	EnableDocking(CBRS_ALIGN_ANY);

	LU->InitFieldChooser();

	m_wndStatusBar.SetPaneInfo(ID_PANE_MESSENGER, ID_INDICATOR_MESSENGER, 0, 100);
	m_wndStatusBar.SetPaneInfo(ID_PANE_INTERCALL, ID_INDICATOR_INTERCALL, 0, 100);
	m_wndStatusBar.SetPaneInfo(ID_PANE_ALLOC, ID_INDICATOR_ALLOC, 0, 100);
	m_wndStatusBar.SetPaneInfo(ID_PANE_RECEPT, ID_INDICATOR_RECEPT, 0, 80);
	m_wndStatusBar.SetPaneInfo(ID_PANE_DATETIME, ID_INDICATOR_DATETIME, 0, 120); 
	m_wndStatusBar.SetPaneInfo(ID_PANE_SHARE_BALANCE, ID_INDICATOR_SHARE_BALANCE, 0, 105); 

	LU->InitNofityContainer();
	LU->MakeRiderList();
	LU->MakeAllocateGroup();
	LU->MakeChargeSectionType();
	LU->GetSimpleMap(FALSE); //맵 만들고 시작 

	LU->m_pwndPaneNetwork = NULL;
	if(m_ba.GetCount() > 1 && LF->POWER_CHECK(1000))
	{
		LU->m_pwndPaneNetwork = LU->m_paneManager.CreatePane(
			IDR_PANE_NETWORK, CRect(0, 0, 120, 100), xtpPaneDockLeft);
		LU->m_pwndPaneNetwork->Hide();
		//LU->m_pwndPaneNetwork->SetOptions(xtpPaneNoCloseable);
		LU->m_pwndPaneNetwork->SetIconID(3);
	}

	if(LF->POWER_CHECK(1010))
	{
		LU->m_pwndPane2 = 
			CreatePane(RUNTIME_CLASS(CConnListDlg2), 
			"접속리스트", xtpPaneDockLeft, NULL, IDR_PANE_CONNLIST,
			CRect(0, 0, 600, 100));
		LU->m_pwndPane2->Hide();
	}

	if(LF->POWER_CHECK(1020))
	{	
		LU->m_pwndPane6 = 
			CreatePane(RUNTIME_CLASS(CShareOrderDlg), 
			"공유오더", xtpPaneDockLeft, NULL, IDR_PANE_SHARECALL,
			CRect(0, 0, 600, 100));
		LU->m_pwndPane6->Hide();
	}

	if(LF->POWER_CHECK(1150))
	{	
		LU->m_pwndPane6 = 
			CreatePane(RUNTIME_CLASS(CBranchFormView), 
			"협력사조회", xtpPaneDockLeft, NULL, IDR_PANE_SHARE_COPMANY,
			CRect(0, 0, 560, 100));
		LU->m_pwndPane6->Hide();
	}

	LU->m_pwndPane7 = 
		CreatePane(RUNTIME_CLASS(CShareRcpPageView), 
		"공유콜조회", xtpPaneDockLeft, NULL, IDR_PANE_SHARE_ORDER,
		CRect(0, 0, 900, 100));
	LU->m_pwndPane7->Hide();

//	SwitchView(HOME_VIEW);
//	RecalcLayout();

	SetTimer(0, 100, NULL);		//Status창 시간 타이머f
	SetTimer(1, 1000, NULL);	//Status창 설명하는 부분 내용 지우기
	SetTimer(2, 5000, NULL);	//메시지 체크 타이머
	SetTimer(9999, 2000, NULL);
	//SetTimer(3, 5000, NULL);	//오더 변경체크

	SetTimer(888, 100, NULL);	//update.exe 체크


	if(m_ba.GetCount() > 1 && LU->m_pwndPaneNetwork)
	{
		LU->m_pwndPaneNetwork->Select();
		if(LU->ChangeBranchItemInTaskPanel(LU->m_pwndTaskPanel, m_ba.GetAt(0), LU->m_pwndPaneNetwork))
			LU->m_paneManager.RedrawPanes();
		LU->m_pwndPaneNetwork->Hide();
	}

	if(LF->POWER_CHECK(1010) || LF->POWER_CHECK(1020))
	{
		//SetTimer(ETC_REFRESH_TIMER_ID, 5000, NULL);
	}
}

void CMainFrame::SwitchView(int nView)
{
	try {
		switch(nView)
		{
			case HOME_VIEW:
				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pHomeView, RUNTIME_CLASS(CHomeView));
				break;

			case RCP_VIEW: 
				{
					if(!LF->POWER_CHECK(2000, "접수화면 보기"))
						throw "접수탭 접근 권한이 없습니다.";

					InitRcpViewRelation();
					LU->m_pwndCur = ReplaceView((CView**)&LU->m_pRcpView, RUNTIME_CLASS(CRcpView));					
				}
				break;

			case REPORT_CUSTOMER_VIEW:
				if(!LF->POWER_CHECK(3000, "고객정산화면 보기"))
					throw "고객정산탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pReportView, RUNTIME_CLASS(CReportView));
				break;

			case REPORT_RIDER_VIEW:
				if(!LF->POWER_CHECK(4000, "기사정산화면 보기"))
					throw "기사정산탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pReportRiderView, RUNTIME_CLASS(CReportRiderView));
				break;

			case STAFF_VIEW:
				if(!LF->POWER_CHECK(5000, "직원화면 보기"))
					throw "직원탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pStaffView, RUNTIME_CLASS(CStaffViewNew));
				break;
		
			case CUSTOMER_VIEW:
				if(!LF->POWER_CHECK(6000, "고객화면 보기"))
					throw "고객탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pCustomerView, RUNTIME_CLASS(CCustomerView));
				break;

			case INCOME_VIEW:
				if(!LF->POWER_CHECK(7000, "입금화면 보기"))
					throw "입금탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pIncomeView, RUNTIME_CLASS(CIncomeView));
				break;

			case STAT_VIEW:
				if(!LF->POWER_CHECK(8000, "통계화면 보기"))
					throw "고객탭 접근 권한이 없습니다.";

				LU->m_pwndCur = ReplaceView((CView**)&LU->m_pStatView, RUNTIME_CLASS(CStatView));
				break;


		}	
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg, "권한없음", MB_ICONINFORMATION);
		return;
	}

	LU->SetCurView(nView);

	switch(nView)
	{
	case HOME_VIEW:
		((CHomeView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case RCP_VIEW:
		((CRcpView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case CUSTOMER_VIEW:
		((CCustomerView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case REPORT_CUSTOMER_VIEW:
		((CReportView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case REPORT_RIDER_VIEW:
		((CReportRiderView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case STAFF_VIEW:
		((CStaffViewNew*)LU->m_pwndCur)->FirstRefresh();
		break;

	case INCOME_VIEW:
		((CIncomeView*)LU->m_pwndCur)->FirstRefresh();
		break;

	case STAT_VIEW:
		((CStatView*)LU->m_pwndCur)->FirstRefresh();
		break;
	}

	if(LU->GetRcpView())
		(LU->GetRcpView())->HideSearchDlg();
}

void CMainFrame::ViewCharge()
{
	if(!LF->POWER_CHECK(1100, "요금창 보기", TRUE))
		return;
	
	//CWaitCursor wait;
	BOOL bIntegrated = FALSE;
	CBranchInfo *pBi = NULL;

	for(int i = 0; i < m_ba.GetCount(); i++) {
		pBi = m_ba.GetAt(i);
		if(pBi->bIntegrated)
		{
			bIntegrated =	TRUE;
			
		}	
		
	}
	for(int i = 0; i < m_ba.GetCount(); i++) {
		pBi = m_ba.GetAt(i);
		if(pBi->nPayTable == m_ci.m_nCompanyCode)
			break;			
	}


	
	if(pBi->bUserDongPos)
	{
		
		m_pChargeDongUDlg = new CChargeDongUDlg(this);	
		m_pChargeDongUDlg->m_nCompany = bIntegrated ? pBi->nCompanyCode : pBi->nPayTable;		
		m_pChargeDongUDlg->m_bIntegrated = bIntegrated;				
		m_pChargeDongUDlg->Create(IDD_CHARGE_DONG_UDLG2, this);				
		m_pChargeDongUDlg->ShowWindow(SW_SHOW);	

	}
	else if(pBi->bUseNewRegion)
	{

		m_pChargeDongDlg3 = new CChargeDongDlg3(this);	
		m_pChargeDongDlg3->m_nCompany = bIntegrated ? pBi->nCompanyCode : pBi->nPayTable;		
		m_pChargeDongDlg3->m_bIntegrated = bIntegrated;				
		m_pChargeDongDlg3->Create(IDD_CHARGE_DONG_DLG3, this);				
		m_pChargeDongDlg3->ShowWindow(SW_SHOW);	
		return;
		
		/*m_pChargeDongDlg = new CChargeDongDlg2(this);	
		m_pChargeDongDlg->m_nCompany = bIntegrated ? pBi->nCompanyCode : pBi->nPayTable;		
		m_pChargeDongDlg->m_bIntegrated = bIntegrated;				
		m_pChargeDongDlg->Create(IDD_CHARGE_DONG_DLG1, this);				
		m_pChargeDongDlg->ShowWindow(SW_SHOW);	*/

	}
}

void CMainFrame::OnProgShare()
{
	if(m_ui.nRole != 0)
	{
		MessageBox("관리자만 설정 하실 수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}


	CShareProgDlg dlg;
	
	if(dlg.DoModal() == IDOK)
	{
		CMkCommand cmd(m_pMkDb, "update_coali_share"); 
		cmd.AddParameter(m_ci.m_nCompanyCode);
		cmd.AddParameter(dlg.m_nShare);

		if(cmd.Execute())
		{
			MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);
		}		
	}

}

void CMainFrame::OnViewPay()
{
	if(!LF->POWER_CHECK(1100, "요금창 보기", TRUE))
		return;

	LU->InitChargeContainer(this);
	LU->ChargeContainerShow();
}

void CMainFrame::OnViewCar()
{
}

void CMainFrame::OnViewHome()
{
	SwitchView(HOME_VIEW);
}

void CMainFrame::OnViewCustomer()
{
	SwitchView(CUSTOMER_VIEW);
}

void CMainFrame::OnManager()
{
	SwitchView(STAFF_VIEW);
}

void CMainFrame::OnViewDeliveryStandard()
{
	SwitchView(RCP_VIEW);
}

void CMainFrame::OnViewStandard()
{
	SwitchView(RCP_VIEW);
	///***/m_pRcpView->MoveClient();
}

void CMainFrame::OnViewReportCustomer()
{
	SwitchView(REPORT_CUSTOMER_VIEW);
}

void CMainFrame::OnViewReportRider()
{
	SwitchView(REPORT_RIDER_VIEW);
}

void CMainFrame::OnViewIncome()
{
	SwitchView(INCOME_VIEW);
}

void CMainFrame::OnViewStat()
{
	SwitchView(STAT_VIEW);
}

void CMainFrame::OnMenuMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	CRiderMsgDlg dlg;
	dlg.SetIntegrated(LF->GetCurBranchInfo()->bIntegrated);
	dlg.SetCompanyCode(LF->GetCurBranchInfo()->nCompanyCode);
	dlg.DoModal();
}

void CMainFrame::OnViewCid()
{
	CCidDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnLogout()
{
	m_bNoQueryExit = TRUE;
	LF->RunProgram(LF->GetMyFileName(), "/run");
	PostMessage(WM_CLOSE, 0, 0);

}

void CMainFrame::OnOption()
{
	if(!LF->POWER_CHECK(1300, "옵션설정창 보기", TRUE))
		return;

	//COptionDlg dlg;
	//dlg.DoModal();

	//CMainOptionDlg dlg;
	//dlg.DoModal();
	CREATE_AND_SHOW_MODALESS(CMainOptionDlg2, this);
}


void CMainFrame::OnMessenger()
{
	LU->ShowMessenger();
}

void CMainFrame::OnCallCount()
{
	if(!LF->POWER_CHECK(1500, "콜카운트 보기", TRUE))
		return;

	CCallCountDlg dlg;
	dlg.DoModal();
}


void CMainFrame::OnRemoteControlWeb()
{
	ShellExecute(NULL, "open", "iexplore.exe", "https://113366.com", "", SW_SHOW);
}

void CMainFrame::OnAllocateBoard()
{
	LU->CreateAllocateBoardDlg();
}

void CMainFrame::OnOtherRegionBranch()
{
	COtherRegionBranchDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnRiderMap()
{
	BOOL m_bOtherRiderMap = AfxGetApp()->GetProfileInt("RiderMapDlg", "LastShowMapType", 1);

	if(m_bOtherRiderMap && LU->GetRiderMapDlg2())	
		LU->CreateRiderMapDlg2();
	else
		LU->CreateRiderMapDlg();
}

void CMainFrame::OnUpdateViewHome(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CHomeView)));
}

void CMainFrame::OnUpdateViewStandard(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CRcpView)));
}

void CMainFrame::OnUpdateViewReportCustomer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CReportView)));
}

void CMainFrame::OnUpdateViewReportRider(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CReportRiderView)));
}

void CMainFrame::OnUpdateManager(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CStaffViewNew)));
}

void CMainFrame::OnUpdateViewCustomer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CCustomerView)));
}

void CMainFrame::OnUpdateViewIncome(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CIncomeView)));
}

void CMainFrame::OnUpdateViewStat(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!LU->GetSplitterWnd()->GetPane(0, 0)->IsKindOf(RUNTIME_CLASS(CStatView)));
}

void CMainFrame::OnUpdateMessenger(CCmdUI *pCmdUI)
{

}

void CMainFrame::OnUpdateCallCount(CCmdUI *pCmdUI)
{

}

void CMainFrame::OnUpdateAllocateBoard(CCmdUI *pCmdUI)
{

}

void CMainFrame::OnUpdateRiderMap(CCmdUI *pCmdUI)
{

}

void CMainFrame::OnUpdateOtherRegionBranch(CCmdUI *pCmdUI)
{

}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if(m_bRcpPageInitCompleted)
	{
		if(pCopyDataStruct->cbData < 100) 
		{
			char szData[100];

			memcpy(szData, pCopyDataStruct->lpData, pCopyDataStruct->cbData);
			szData[pCopyDataStruct->cbData] = '\0';
			LU->SendCIDInfo(szData);
		}
	}

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CMainFrame::GetOrderRequestCount()
{
	static long nRequestTimer = 6001;

	if(nRequestTimer > 6000) //10분
	{ 
		nRequestTimer = 0;

		CMkCommand cmd(m_pMkDb, "select_request_order_count");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		cmd.AddParameter(m_ci.m_nShareCode1);

		if(cmd.Execute())
			parRet->GetValue(m_nOrderRequestCount);
	}

	nRequestTimer++;
}


void CMainFrame::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0) 
	{	
		KillTimer(nIDEvent);
		static BOOL bFirst = TRUE;

		GetOrderRequestCount();
		COleDateTime datetime = COleDateTime::GetCurrentTime();
		CString strTemp;

		if(m_nOrderRequestCount > 0)
		{
			strTemp.Format("%d개의 오더수정 요청건이 있습니다", m_nOrderRequestCount);
			m_wndStatusBar.SetPaneText(ID_PANE_DATETIME, datetime.Format(strTemp)); 
		}
		else
			m_wndStatusBar.SetPaneText(ID_PANE_DATETIME, datetime.Format("%Y-%m-%d %H:%M:%S")); 

		if(bFirst == TRUE)
		{
			if(m_nOrderRequestCount > 0)
			{
				strTemp += "\r\n[보기]->[오더수정요청]에서 수정요청을 완료하세요";
				MessageBox(strTemp, "확인", MB_ICONINFORMATION);
			}

			CheckChargeForRider();
			bFirst = FALSE;
		}

		SetTimer(0, 10000, NULL);
	}
	else if(nIDEvent == 1) {
		if(m_nStatusAccessTime + 5000 < GetTickCount() )
		{
			GetStatusBar()->SetPaneText(0, "");
		}	
	}
/*	프로그램에서 아주 빠른 주기로 이렇게 쿼리치게 하면 안됨
//  요금을 로컬에서 가지고 있으면서 최신상태로 유지해야할 필요가 있는지..(접속자 1000명되면, 초당 200개씩 날라옴)
//  필요할 때 DB에서 쿼리하는게 나을 것 같은데...
//by mksong (2011-01-31 오전 10:29)
	else if(nIDEvent == 2) {
		static UINT nSec = 0;
		KillTimer(2);
		nSec += 5;

		// 멤버고객 히스토리 Charge 가져오기
		LU->LoadMemberCharge();
		//5분마다 공지메시지 체크
		if(nSec  >= LU->m_nTimeOfCheckNotice) {
			nSec = 0;
			LU->m_nTimeOfCheckNotice = 300;
			LU->CheckNotice();
		}
		SetTimer(2, 5000, NULL);
	}
*/
	else if(nIDEvent == 3)//오더 변경요청 있는지 
	{

	}
	else if(nIDEvent == ETC_REFRESH_TIMER_ID)
	{
		KillTimer(nIDEvent);

		static int nCount = 0;

		if(nCount++ % 4 == 0)
		{
			EtcRefresh();
		}

		SetTimer(ETC_REFRESH_TIMER_ID, ETC_REFRESH_SEC, NULL);
	}
	else if(nIDEvent == 9999)
	{
		KillTimer(nIDEvent);
		m_bApplicationInit = TRUE;
	}
	else if(nIDEvent == UPLOAD_TIMER)
	{
		KillTimer(UPLOAD_TIMER);
		CCaptureUpload cu;
		SetTimer(UPLOAD_TIMER, cu.Run() * 1000, NULL);
	}
	else if (nIDEvent == 888) {
		KillTimer(nIDEvent);
		update_exe_check_.Start(); // update.exe 버젼체크 // 지역변수로 선언하면 안됨
	}

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::CheckChargeForRider()
{
	CMkCommand cmd(m_pMkDb, "selet_is_charge_for_rider");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ci.m_nCompanyCode);

	if(!cmd.Execute())
		return;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		MessageBox("기사 이체요청이 있습니다\r\n보기 - 기사청구내역에서 확인 하실 수 있습니다", "확인", MB_ICONINFORMATION);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 1024;
	lpMMI->ptMinTrackSize.y = 768;

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnScheduleJob()
{
	if(!LF->POWER_CHECK(1960, "자동스케줄작업 보기", TRUE))
		return;

	CDepositJobDlg dlg;
	dlg.m_bIntegrated = LF->GetCurBranchInfo()->bIntegrated;
	dlg.m_nCompanyCode = LF->GetCurBranchInfo()->nCompanyCode;
	dlg.DoModal();
}

void CMainFrame::OnSendMac()
{
/*	GetMacAddress();

	_ADO_OPEN();

	CADOParameter parInCompany(CADORecordset::typeInteger, sizeof(int), CADOParameter::paramInput);
	CADOParameter parInUserID(CADORecordset::typeVarWChar, m_ui.strID.GetLength(), CADOParameter::paramInput);
	CADOParameter parInMac1(CADORecordset::typeVarWChar, max(1, m_ei.strMac1.GetLength()), CADOParameter::paramInput);
	CADOParameter parInMac2(CADORecordset::typeVarWChar, max(1, m_ei.strMac2.GetLength()), CADOParameter::paramInput);

	parInCompany.SetValue(m_ci.m_nCompanyCode);
	parInUserID.SetValue(m_ui.strID);
	parInMac1.SetValue(m_ei.strMac1);
	parInMac2.SetValue(m_ei.strMac2);

	CADOCommand pCmd(&m_db, "insert_mac_log");
	pCmd.AddParameter(&parInCompany);
	pCmd.AddParameter(&parInUserID);
	pCmd.AddParameter(&parInMac1);
	pCmd.AddParameter(&parInMac2);
	pCmd.Execute();

	MessageBox("성공적으로 전송되었습니다.", "전송확인", MB_ICONINFORMATION);
*/
}

//메신저 박스를 클릭했을때 발생하는 메시지
LRESULT CMainFrame::OnTaskbarNotifierClicked(WPARAM wParam,LPARAM lParam)
{
	if(!LF->POWER_CHECK(1740, "관리자 공지사항 보기", TRUE))
		return 0;

	/*
	CNoticeDlg dlg;
	dlg.m_bJustOpen = TRUE;
	dlg.DoModal();
	return 0;
	*/

	return 0;
}


/*
void CMainFrame::OnShowNotice()
{
	CNoticeDlg dlg;
	dlg.DoModal();
}
*/

void CMainFrame::OnShowSecurityLog()
{
	LU->ShowSecurityLogDlg();
}


//Notifier관련 이벤트
LONG CMainFrame::OnNotifierClicked(WPARAM wParam, LPARAM lParam)
{
	NOTIFIER_ITEM *pNItem = (NOTIFIER_ITEM*) wParam;
	
	//메신져 메시지인 경우
	if(pNItem->type == NFI_RECV_MESSAGE2) 
	{
		char buffer[20];
		LU->m_pMsg->ShowMsgDlg(this, pNItem->strMsg, 
			ltoa(pNItem->nCompanyCode, buffer, 10), 
			ltoa(pNItem->nMNo, buffer, 10),
			ltoa(pNItem->nClientType, buffer, 10),
			pNItem->strCompanyName, 
			pNItem->strName,
			FALSE,
			pNItem->nSendType);
	}
	else if(pNItem->type == NFI_RESERVE)
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			ShowWindow(SW_RESTORE);

		SetForegroundWindow();
		SetFocus();

		CString *pstrName = new CString;
		*pstrName = pNItem->strCName;
		SwitchView(RCP_VIEW);
		if(LU->m_pRcpView != NULL)
			LU->m_pRcpView->PostMessage(WM_RESERVE_ORDER, 
						(WPARAM)atol(pNItem->strIdentity), (LPARAM)pstrName);

		delete pNItem;
	}
	else if(pNItem->type == NFI_QUERY_CHARGE || pNItem->type == NFI_QUERY_CHARGE_INTERCALL)
	{
		char buffer[10];

		CNewMsgDlg *pNewMsgDlg = LU->m_pMsg->ShowMsgDlg(
			this, 
			"요금문의",  
			ltoa(pNItem->nCompanyCode, buffer, 10),
			ltoa(pNItem->nMNo, buffer, 10),
			pNItem->type == NFI_QUERY_CHARGE ? "" : "2",
			pNItem->strCompanyName,
			pNItem->strName, 
			TRUE);

		CQueryChargeDlg *pDlg = (CQueryChargeDlg*)pNItem->pVoid;

		if(pDlg == NULL)
			return FALSE;

		pDlg->m_pNewMsgDlg = pNewMsgDlg;
		pDlg->m_strUniqueID = pNItem->strUniqueID;

		pDlg->Create(IDD_QUERY_CHARGE_DLG, this);
		pDlg->ShowWindow(SW_SHOWNA);
		pDlg->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		delete pNItem;
	}
/*###
	else if(pNItem->type >= NFI_MESSAGE_BASE) 
	{
		if(pNItem->type - NFI_MESSAGE_BASE == ID_PANE_MESSENGER)
		{
			char buffer[20];
			m_pMsg->ShowMsgDlg(pNItem->strMsg, 
					ltoa(pNItem->nCompanyCode, buffer, 10), 
					ltoa(pNItem->nMNo, buffer, 10),
					pNItem->strCompanyName, 
					pNItem->strName);
		}
		else if(pNItem->type - NFI_MESSAGE_BASE == ID_PANE_INTERCALL)
		{
			char buffer[20];
			m_pIntercall->ShowMsgDlg(pNItem->strMsg, 
					ltoa(pNItem->nCompanyCode, buffer, 10), 
					ltoa(pNItem->nMNo, buffer, 10),
					pNItem->strCompanyName, 
					pNItem->strName);
		}
*/
	

	return 0;
}

LONG CMainFrame::OnSetMsgState(WPARAM wParam, LPARAM lParam)
{
	BOOL bIsNewAllocate = (BOOL)lParam;
	if(bIsNewAllocate)
	{
		CString *pstr = (CString*)wParam;
		m_wndStatusBar.SetPaneText(ID_PANE_MESSENGER, *pstr);
		delete pstr;
	}
	else
	{
		m_wndStatusBar.SetPaneText(ID_PANE_MESSENGER, (const char*)wParam);
	}

	return 0;
}


LONG CMainFrame::OnSetIntercallState(WPARAM wParam, LPARAM lParam)
{
	BOOL bIsNewAllocate = (BOOL)lParam;
	if(bIsNewAllocate)
	{
		CString *pstr = (CString*)wParam;
		m_wndStatusBar.SetPaneText(ID_PANE_INTERCALL, *pstr);
		delete pstr;
	}
	else
	{
		m_wndStatusBar.SetPaneText(ID_PANE_INTERCALL, (const char*)wParam);
	}

	return 0;
}

LONG CMainFrame::OnSetAllocState(WPARAM wParam, LPARAM lParam)
{
	m_wndStatusBar.SetPaneText(ID_PANE_ALLOC, (const char*)wParam);
	return 0;
}

void CMainFrame::OnClose()
{
	if(m_bNoQueryExit || IDYES == MessageBox("프로그램을 종료하시겠습니까?", "종료 확인", MB_ICONQUESTION | MB_YESNO))
	{
		LU->SaveLogOut(); //강제종료처리
		LU->Destroy();

		KillTimer(0);
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		KillTimer(ETC_REFRESH_TIMER_ID);
		encProfile.WriteInt("General", "start_flag", 100);

		CWnd *pWnd = FindWindow("자동종료", NULL);
		if(pWnd->GetSafeHwnd()) 
		{
			pWnd->PostMessage(WM_CLOSE);
			Sleep(1000);
		}

		CFrameWnd::OnClose();
	}
	else
	{
		LU->SaveLogOut(); //강제종료처리
		LU->LogOutRestore();
	}
}

void CMainFrame::OnRemoteControl(UINT nID)
{
	LU->RunRemoteControl(nID - ID_REMOTE_CONTROL);
}

void CMainFrame::OnDebugMode()
{
	g_bana_log->SetMode(CBanaLog::TO_CONSOLE);
}

void CMainFrame::OnIntercallNotice()
{
	CIntercallNoticeDlg dlg;
	dlg.DoModal();
}


void CMainFrame::OnNewRiderList()
{
	LU->GetRcpView()->PostMessage(WM_COMMAND, ID_NEW_RIDER_LIST, 0);
}

void CMainFrame::OnAccessControl()
{
	if(m_ui.nRole != 0) {
        MessageBox("최고관리자만 권한설정이 가능합니다.", "권한없음", MB_ICONINFORMATION);
		return;
	}

	CRcpPowerDlg dlg;
	dlg.DoModal();

}

void CMainFrame::OnIntercallConnList()
{
	if(m_pIntercall == NULL)
	{
		MessageBox("인터콜서버에 연결되지 않은 상태입니다.\n"\
				"인터콜 받기 버튼을 눌러 연결하시기 바랍니다.",
				"확인",
				MB_ICONINFORMATION);
		return;
	}

	m_pIntercall->ShowMsgConnList();
}

void CMainFrame::OnCidGroup()
{
	if(!LF->POWER_CHECK(1730, "CID그룹 설정", TRUE))
		return;

	CCidGroupDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnAllocateGroup()
{
	if(!LF->POWER_CHECK(1780, "배차그룹관리", TRUE))
		return;

	CAllocateGroupDlg dlg;
	dlg.DoModal();
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_MOUSEHOVER)
	{
		if(pMsg->hwnd != LU->m_pwndTaskPanel->GetSafeHwnd())
		{
			return TRUE;
		}
	}

	return CXTPFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CXTPFrameWnd::OnWndMsg(message, wParam, lParam, pResult);
}

void CMainFrame::RecalcLayout(BOOL bNotify)
{
	CXTPFrameWnd::RecalcLayout(bNotify);
}


void CMainFrame::OnTestVirtualCid()
{
	CTestVirtualCIDDlg dlg;
	dlg.DoModal();

}

void CMainFrame::OnAuthManage()
{
	if(!LF->POWER_CHECK(1820, "인증페이지보기", TRUE))
		return;

	CAuthManageDlg pDlg;
	pDlg.DoModal();
}

void CMainFrame::OnAuthManageLog()
{
	if(!LF->POWER_CHECK(1820, "인증페이지보기", TRUE))
		return;

	CAuthManageLogDlg pDlg;
	pDlg.DoModal();
}

void CMainFrame::OnAuthLog()
{
	if(!LF->POWER_CHECK(1820, "인증페이지보기", TRUE))
		return;
	
	CAuthLogDlg pDlg;
	pDlg.DoModal();
}


LONG CMainFrame::OnGroupChatResonse(WPARAM wParam, LPARAM lParam)
{
	char *szName = (char*)wParam;
	char *szText = (char*)lParam;

	CGroupChatDlg *pDlg = LU->GetGroupChatPane();

	if(pDlg)
	{
		pDlg->GetDataText(szName, szText);
	}

	return 0;
}


LONG CMainFrame::OnQueryChargeResponse(WPARAM wParam, LPARAM lParam)
{
	long nUniqueID = (long)wParam;
	long nCharge = (long)lParam;

	CRcpDlg *pRcpDlg = LU->GetRcpView()->FindRcpDlgFromUniqueChargeID(nUniqueID);
	if(pRcpDlg)
		pRcpDlg->ChangeChargeFromQuery(nCharge);

	return 0;
}

LONG CMainFrame::OnRcpCopyData(WPARAM wParam, LPARAM lParam)
{
	CString strSendOP;
	CRcpCopyData *pData = (CRcpCopyData*)wParam;
	if(IDYES == MessageBox(pData->GetValue("SEND_OP", strSendOP) + "님으로 부터 접수창 데이터를 받았습니다.\n"\
			"넘겨받은 접수창 데이터를 사용하시겠습니까?", "접수창 데이터 넘겨 받음",
			MB_ICONQUESTION | MB_YESNO))
	{
		long nCompany;
		CString strPhone;
		pData->GetValue("nCompany", nCompany);
		pData->GetValue("m_strCID", strPhone);
		CBranchInfo *pBi = NULL;

		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = (CBranchInfo*)m_ba.GetAt(i);
			if(nCompany == pBi->nCompanyCode)
			{
				break;
			}
		}

		if(pBi)
		{
			CRcpDlg *pDlg = LU->GetRcpView()->CreateRcpDlg(pBi, "넘겨받음(" + strPhone + ")");
			if(pDlg)
				pDlg->OnRcpCopyData(pData);
		}
	}
	delete pData;

	return 0;
}


void CMainFrame::OnMoveOrder()
{
	CMoveOrderLogDlg dlg;
	dlg.DoModal();
}


void CMainFrame::OnShareReportRate()
{
	if(m_ci.m_bUseShareReport)
	{
		if(!m_ci.m_bRcpIntMode1)
		{
			MessageBox("메인회원사만 볼수 있는 메뉴입니다.", "확인", MB_OK);
			return;
		}

		if(!LF->POWER_CHECK(1760, "공유콜 정산", TRUE))
			return;

		CShareReportRateDlg dlgShareRate(NULL);
		dlgShareRate.DoModal();
	}
	else
	{
		MessageBox("공동정산을 이용하실려면, 로지소프트로 문의바랍니다.", "확인", MB_OK);
	}
}

BOOL PaneIsVisible(CXTPDockingPane* pane)
{
	if(pane)
	{
		CWnd *pWnd = (CWnd*)pane->GetChild();
		if(pWnd && pWnd->GetSafeHwnd())
		{
			if(pWnd->IsWindowVisible())
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


void CMainFrame::EtcRefresh()
{
}

void CMainFrame::OnRunTelclient()
{
	CString strPath = LF->GetModuleFullPath();
	strPath += "TelClient\\TelClient.exe";
	if(!LF->RunProgram(strPath, ""))
	{
		MessageBox("텔 클라이언트 프로그램을 찾을 수 없습니다.", "프로그램 실행 오류", MB_ICONEXCLAMATION);
	}
}

void CMainFrame::RefreshIntercallConnList()
{
	m_mapIC.clear();

	CWaitCursor wait;
	CMkDatabase *pMkDb = new CMkDatabase(g_bana_log);
	BYTE nXorKey = (pMkDb->GetXorKey() + 3) % 128;
	BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
	BYTE nXoredKey[8];

	for(int i = 0; i < 8; i++)
		nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
	pMkDb->SetServerKey(nXoredKey);

	if(pMkDb->Open(m_si.strMsgServerAddr, m_si.nMsgServerPort))
	{
		CMkRecordset pRs(pMkDb);
		CMkCommand pCmd(pMkDb, "select_msg_conn_list2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 1);

		if(pRs.Execute(&pCmd)) 
		{
			while(!pRs.IsEOF()) 
			{
				long nCompanyCode, nMNo;
				int nClientType;

				pRs.GetFieldValue("nCompany", nCompanyCode);
				pRs.GetFieldValue("nMNo", nMNo);
				pRs.GetFieldValue("nClientType", nClientType);

				if(nClientType == 1)
					m_mapIC.insert(MAP_INTERCALL_CUSTOMER::value_type(nMNo, nMNo));

				pRs.MoveNext();
			}

			pRs.Close();
		}	
	}


	pMkDb->Close();
	delete pMkDb;

}

void CMainFrame::OnScheduleOrder() 
{
	CREATE_MODALESS(CScheduleOrderListDlg, this);
	SHOW_MODALESS(CScheduleOrderListDlg, this);
	//CScheduleOrderListDlg dlg;
	//dlg.DoModal();
}

void CMainFrame::OnCompleteAfterEdit()
{
	//MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);

	//주석풀기 쉽게한 주석

	KillTimer(3);
	CCompleteAfterEditDlg dlg;
	dlg.DoModal();
	SetTimer(3, 5000, NULL);

}

void CMainFrame::OnRecvEditOrderState(long nTNo, long nTickCount, long nState, CString strWName)
{
	CRcpDlg *pRcpDlg = LU->GetRcpView()->FindRcpDlg(nTNo);
	if(pRcpDlg && !pRcpDlg->m_bEditExampleDlg)
		pRcpDlg->OnRecvEditOrderState(nTNo, nTickCount, nState, strWName);
}

void CMainFrame::ShowTransInformationRequestPopup(long nTNo, CString sStart, CString sDest, CString sRName, long nRNo, CString sOName,
												  long nState)
{
	m_pActivePopup = new CXTPPopupControl();

	UpdateData();

	CSize szPopup (329, 74);

	SetTransPopupMsg(nTNo, sStart, sDest, sRName, nRNo, sOName, nState); 

	m_pActivePopup->SetPopupAnimation((XTPPopupAnimation)3); 
	// 0:None, 1:Fade, 2:slide, 3:UnFold
	m_pActivePopup->SetShowDelay(10000);
	m_pActivePopup->SetAnimateDelay(500);
	m_pActivePopup->SetTransparency((BYTE)200); //투명도
	m_pActivePopup->SetPopupSize(szPopup);

	FindBestPosition(szPopup);

	m_pActivePopup->AllowMove(FALSE);
	m_pActivePopup->Show(this);

	m_lstPopupControl.AddTail(m_pActivePopup);
	//EnableItems(TRUE);
}

void CMainFrame::EnableItems(BOOL bEnable)
{
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		pWnd->EnableWindow(bEnable);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	//GetDlgItem(IDC_BUTTON_SHOW)->EnableWindow(TRUE);
}


void CMainFrame::FindBestPosition(CSize szPopup)
{
	if (m_ptPopup != CPoint(-1, -1)) 
		m_pActivePopup->SetPopupPos(m_ptPopup);

	CPoint ptPopup = m_pActivePopup->GetPopupPos();

	CRect rcActivePopup(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);


	BOOL bIntersect = FALSE;
	do 
	{
		bIntersect = FALSE;
		POSITION pos = m_lstPopupControl.GetHeadPosition();

		while(pos)
		{
			CXTPPopupControl* pPopup = m_lstPopupControl.GetNext(pos);

			CRect rcPopup(CPoint(pPopup->GetPopupPos().x - pPopup->GetPopupSize().cx, 
				pPopup->GetPopupPos().y - pPopup->GetPopupSize().cy), pPopup->GetPopupSize());

			if (CRect().IntersectRect(rcPopup, rcActivePopup))
			{
				ptPopup.y =  rcPopup.top;
				rcActivePopup = CRect(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);
				bIntersect = TRUE;
			}
		}
	} while (bIntersect);

	m_pActivePopup->SetPopupPos(ptPopup);
}

void CMainFrame::SetPoputMsg()
{
	m_pActivePopup->RemoveAllItems();

	// add text items.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 16, 270, 41), _T("오더 수정 확인 요청이 있습니다.")));
	pItemText->SetBold(TRUE);
	pItemText->SetID(ID_GOTO_ORDER_CHANGE_PAGE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 29, 270, 54), _T("클릭시 확인 페이지로 이동합니다.")));
	pItemText->SetID(ID_GOTO_ORDER_CHANGE_PAGE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 42, 270, 92), _T("오늘 그만보기")));
	pItemText->SetID(ID_DO_NOT_SHOW);

	pItemText->SetTextColor(RGB(0, 61, 178));
	pItemText->SetTextAlignment(DT_LEFT|DT_WORDBREAK);

	// letter icon.
	
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 12, 17, 24)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER), IMAGE_ICON, 32, 32, 0));
	pItemIcon->SetButton(FALSE);

	// close icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(308, 14, 324, 30)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CLOSE), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// flag icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(4, 49, 20, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_FLAG), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	// cross icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(23, 49, 39, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CROSS), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	m_pActivePopup->SetTheme(xtpPopupThemeOffice2003);
	m_pActivePopup->RedrawControl();
}

void CMainFrame::SetTransPopupMsg(long nTNo, CString sStart, CString sDest, CString sRName, long nRNo, CString sOName,
								long nState)
{
	m_pActivePopup->RemoveAllItems();

	CString sTransMsg = "";
	sTransMsg.Format("오더번호:%d 탁송정보가 입력되었습니다", nTNo);

	TRANS_STRUCT *st = new TRANS_STRUCT;
	st->nTNo = nTNo;
	st->nState = nState;
	st->sOName = sRName;
//CMyCXTPopupItem
	// add text items.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 16, 300, 41), _T(sTransMsg)));
	pItemText->SetBold(TRUE);
	pItemText->SetID(ID_TRANS_INFORMATION_UPDATE);
	m_TransMap.insert(TRANS_MAP::value_type(pItemText, st));
	//pItemText->SetItemData((DWORD)st);
	
	sTransMsg.Format("%s -> %s [%d/%s]", sStart, sDest, nRNo, sRName);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 29, 3000, 54), _T(sTransMsg)));
	pItemText->SetID(ID_TRANS_INFORMATION_UPDATE);
	m_TransMap.insert(TRANS_MAP::value_type(pItemText, st));
	//pItemText->SetItemData((DWORD)st);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 42, 300, 92), _T("클릭하여 탁송료를 입력하세요")));
	pItemText->SetID(ID_TRANS_INFORMATION_UPDATE);
	m_TransMap.insert(TRANS_MAP::value_type(pItemText, st));
	//pItemText->SetItemData((DWORD)st);

	pItemText->SetTextColor(RGB(0, 61, 178));
	pItemText->SetTextAlignment(DT_LEFT|DT_WORDBREAK);

	// letter icon.

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 12, 17, 24)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER), IMAGE_ICON, 32, 32, 0));
	pItemIcon->SetButton(FALSE);

	// close icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(308, 14, 324, 30)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CLOSE), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// flag icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(4, 49, 20, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_FLAG), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	// cross icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(23, 49, 39, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CROSS), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	m_pActivePopup->SetTheme(xtpPopupThemeOffice2003);
	m_pActivePopup->RedrawControl();
}

LRESULT CMainFrame::OnPopUpNotify(WPARAM wParam, LPARAM lParam)
{
	// process notify from popup wnd

	if(wParam == XTP_PCN_ITEMCLICK) 
	{
		CXTPPopupItem* pItem = (CXTPPopupItem*)lParam;
		ASSERT(pItem);

		if(pItem->GetID() == ID_TRANS_INFORMATION_UPDATE)
		{
			TRANS_MAP::iterator it;
			it = m_TransMap.find(pItem);

			if(it == m_TransMap.end())
				return 0;
	
			LU->GetRcpView()->CreateRcpDlg(NULL, 
				it->second->sOName,
				it->second->nTNo, 
				it->second->nState, "", FALSE, -1, 0, 0, FALSE, "");
		}
		else if(pItem->GetID() == ID_GOTO_ORDER_CHANGE_PAGE)
		{				
			pItem->GetPopupControl()->Close();
			OnCompleteAfterEdit();
			return TRUE;
		}
		else if(pItem->GetID() == ID_DO_NOT_SHOW)
		{
			m_bShowOrderChangePopup = FALSE;
			//pItem->GetPopupControl()->Close();
		}

		pItem->GetPopupControl()->Close();
	}
	else if(wParam == XTP_PCN_STATECHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);

		if(pControl->GetPopupState() == xtpPopupStateClosed)
		{
			POSITION pos = m_lstPopupControl.Find(pControl);
			if (pos)
			{
				m_lstPopupControl.RemoveAt(pos);

				if (m_lstPopupControl.IsEmpty())
				{
					EnableItems(TRUE);				
				}

				delete pControl;
			}
			m_pActivePopup = NULL;
		}
	}
	else if (wParam == XTP_PCN_POSCHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);

		m_ptPopup = pControl->GetPopupPos();
	}

	return TRUE;
}


LONG CMainFrame::OnCloseShowRecvCidDlg(WPARAM wParam, LPARAM lParam)
{
	LU->CloseRecvCidDlg();
	return 0;
}

void CMainFrame::OnShareReportBranchSet()
{
	/*
	if(m_ui.nRole != 0)
	{
		MessageBox("관리자만 권한이 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}
	*/

	if(!LF->POWER_CHECK(1760, "공유콜 정산", TRUE))
		return;

	CShareReportBranchSetDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnTrsBoardDlg()
{
	LU->CreateAllocateBoardTRSDlg();
}


LONG CMainFrame::OnCloseTRSBoardDlg(WPARAM wParam, LPARAM lParam)
{
	LU->CloseAllocateBoardTRSDlg();
	return 0;
}


LONG CMainFrame::OnCloseRiderMapDlg(WPARAM wParam, LPARAM lParam)
{
	LU->CloseRiderMapDlg();
	return 0;
}


LONG CMainFrame::OnCloseRiderDlg(WPARAM wParam, LPARAM lParam)
{
	LU->CloseAllocateBoardDlg();
	return 0;
}

void CMainFrame::OnMShowPreCharge()
{
	//ViewCharge();
	LU->InitChargeContainer(this);
	LU->ChargeContainerShow(); 
}

void CMainFrame::OnSendBulkSms()
{
	CREATE_AND_SHOW_MODALESS(CSmsNewBulkDlg, this)
	pDlg->SetWindowText("대량 SMS/MMS발송");
	//pDlg->m_strCallBackPhone = m_ci.GetPhone();
	pDlg->m_nType = SMS_TYPE_BULK;
	pDlg->InitData(NULL);
	pDlg->ResetData();
}

void CMainFrame::OnMoveRider()
{
	if(LF->POWER_CHECK(1795, "기사이동(사번변경)", TRUE)) {	
		CMoveRiderNewDlg dlg;
		dlg.DoModal();
	}
}

void CMainFrame::OnBranchTransfer()
{
	bool bOpen = FALSE;

	if(LF->GetCurBranchInfo()->bIntegrated == 1) 
	{
		MessageBox("통합 모드에서 지원되지 않는 작업입니다", "확인", MB_ICONINFORMATION);
		bOpen = FALSE;
	}
	else if(LF->GetCurBranchInfo()->nCompanyCode != m_ui.nCompany || m_ui.nRole != 0)
	{
		MessageBox("지사 관리자만 이용 가능한 메뉴 입니다.", "확인", MB_ICONINFORMATION);
		bOpen = FALSE;
	}
	else if(m_ci.m_bRcpIntMode1)
	{
		bOpen = TRUE; // 1차 통합은 그냥 오픈
	}
	else if(m_ci.m_bUseBranchShareReport == 0)
	{
		MessageBox("지사 이체기능을 사용하지 않는 회사입니다", "확인", MB_ICONINFORMATION);
		bOpen = FALSE;;
	}
	else
		bOpen = TRUE;

	if(bOpen == FALSE)
		return;

	CBranchReportMainDlg pDlg;
	pDlg.m_bRequest = FALSE;
	pDlg.DoModal();
}

void CMainFrame::OnBill()
{
	LU->ShowBillDlg();
}

CWnd* CMainFrame::ReplaceView(CView **pView, CRuntimeClass *pClass)
{
	CDisplayBarThreadText bar(m_pMkDb->GetDisplayBarThread(), "페이지를 초기화중입니다.");

	if(*pView)
		LU->GetSplitterWnd()->ReplaceView(0,0, *pView);
	else
		LU->GetSplitterWnd()->ReplaceView(0,0, pClass);
	CWnd *pWnd = LU->GetSplitterWnd()->GetPane(0, 0);;
	*pView = (CView*)pWnd;
	return pWnd;
}

void CMainFrame::InitRcpViewRelation()
{
	static BOOL bFirstRun = TRUE;
	if(bFirstRun)
	{
		//LU->GetRcpView()->m_pwndTaskPanel = LU->m_pwndTaskPanel;
		//LU->GetRcpView()->m_pwndPaneNetwork = LU->m_pwndPaneNetwork;

		if(LF->POWER_CHECK(1030))
		{	
			LU->m_pwndPane5 = 
				CreatePane(RUNTIME_CLASS(CAllocatePaneDlg), 
				"빠른배차", xtpPaneDockLeft, NULL, IDR_PANE_ALLOCATE,
				CRect(0, 0,365, 100));
			LU->m_pwndPane5->Hide();
		}

		LU->m_pwndPane6 =   
			CreatePane(RUNTIME_CLASS(CGroupChatDlg), 
			"그룹채팅", xtpPaneDockLeft, NULL, IDR_PANE_GROUP_CHAT,
			CRect(0, 0,300, 100));
		LU->m_pwndPane6->Hide();

		LU->m_pwndPane3 = 
			CreatePane(RUNTIME_CLASS(CDelayOrderDlg2), 
			"지연오더", xtpPaneDockLeft, NULL, IDR_PANE_DELAYORDER,
			CRect(0, 0, 910, 100));
		LU->m_pwndPane3->Hide();


		LU->m_pwndPane4 = 
			CreatePane(RUNTIME_CLASS(CEmptyCarDlg1), 
			"공차관리", xtpPaneDockLeft, NULL, IDR_PANE_EMPTYCAR,
			CRect(0, 0, 920, 100));
		LU->m_pwndPane4->Hide();


		CheckShareBasicRate();

		if(LF->IsRequestOver15Day(m_ci.m_nCompanyCode))
		{
			CShareTranferRequestDlg dlg;

			dlg.m_sSql = "select_transfer_request_1";

			dlg.DoModal();		
		}

		bFirstRun = FALSE;
	}
}

void CMainFrame::CheckShareBasicRate()
{
	if(m_ci.m_bRcpIntMode1 && m_ci.m_bUseShareReport)
	{
		CMkCommand pCmd(m_pMkDb, "select_share_basic_rate");
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		CMkParameter *parShareBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *parShareBasicRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(pCmd.Execute())
		{
			long nShareBalance; parShareBalance->GetValue(nShareBalance);
			long nShareBasicRate; parShareBasicRate->GetValue(nShareBasicRate);

			if(nShareBasicRate > nShareBalance)
			{
				CString strTemp;
				strTemp.Format("현재충전금이 %s원으로\r\n최소기준금액 %s원보다\r\n적어 공유가 안될수 있습니다.", LF->GetMyNumberFormat(nShareBalance), LF->GetMyNumberFormat(nShareBasicRate));
				MessageBox(strTemp, "확인", MB_ICONINFORMATION);
			}
		}
	}
}

void CMainFrame::OnDeletePoiFile()
{
	CSetPoiDlg dlg;
	dlg.DoModal();	
}

void CMainFrame::OnRiderShareBoard()
{
	LU->CreateRiderShareBoardDlg();
}

void CMainFrame::OnRiderBoard()
{
	LU->CreateRiderBoardDlg();
}

void CMainFrame::OnChargeForRider()
{
	LU->CreateChargeForRiderLogDlg();
}

void CMainFrame::OnCalc()
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)"Calc", NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

}

void CMainFrame::OnRemakeCustomerData()
{
	CCustomerCacheInfoDlg dlg;
	dlg.DoModal();
}

LONG CMainFrame::OnRecvCid(WPARAM wParam , LPARAM lParam)
{
	char *pszData = (char*)wParam;
	if(pszData)
	{
		LU->SendCIDInfo(pszData);
		delete[] pszData;
	}

	return 0;
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == WM_INPUT)
	{
		LF->m_dwLastInput = GetTickCount();	
	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnFunctionTable()
{
	if(m_ui.strID == "적재물보험1" ||
	   m_ui.strID == "적재물보험2")
	{
		CInsStaffDlg1 dlg; 
		dlg.DoModal();
		return;
	}

	LU->MakeFunctionTable();
}

LONG CMainFrame::OnRcpCopyDataDirect(WPARAM wParam, LPARAM lParam)
{
	CRcpCopyData *pData = (CRcpCopyData*)wParam;

	long nCompany;
	CString strPhone;
	pData->GetValue("nCompany", nCompany);
	pData->GetValue("m_strCID", strPhone);
	CRcpView *pView = (CRcpView*)LU->GetRcpView();	
	CBranchInfo *pBi = NULL;

	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		pBi = (CBranchInfo*)m_ba.GetAt(i);
		if(nCompany == pBi->nCompanyCode)
		{
			break; 
		}
	}

	if(pBi)
	{
		CRcpDlg *pDlg = pView->CreateRcpDlg(pBi, "추가접수(" + strPhone + ")");
		if(pDlg)
			pDlg->OnRcpCopyData(pData);
	}

	delete pData; 

	return 0;
}

void CMainFrame::OnOrderRequest()
{
	if(!LF->POWER_CHECK(1520, "오더수정요청창 보기"))
		return;

	CREATE_MODALESS(COrderChangeRequestDlg, this);
	SHOW_MODALESS(COrderChangeRequestDlg, this);
}

void CMainFrame::OnOtherRiderIncome()
{
	if(!LF->POWER_CHECK(1530, "타기사충전"))
		return;

	CREATE_AND_SHOW_MODALESS(COtherRiderTransferDlg, this);
}

void CMainFrame::OnGeneralRecepitRequest()
{
	CGeneralReceiptDlg dlg;
	dlg.DoModal();
}

BOOL CMainFrame::IsAttend()
{
	CMkCommand cmd(m_pMkDb, "is_rider_attend");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	if(MessageBox("금일 출근처리를 하였습니다.\r\n현재 시간으로 다시 출근처리 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
		return TRUE;

	return FALSE;
}


BOOL CMainFrame::IsGetOff()
{
	CMkCommand cmd(m_pMkDb, "is_rider_get_off");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	if(MessageBox("금일 퇴근처리를 하였습니다.\r\n현재 시간으로 다시 퇴근처리 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
		return TRUE;

	return FALSE;
}

void CMainFrame::OnAttend()
{
	if(!IsAttend())
		return;

	CMkCommand cmd(m_pMkDb, "update_rider_attend");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
	{
		MessageBox("출근처리 되었습니다.", "확인", MB_ICONINFORMATION);
	}
}

void CMainFrame::OnGetOff()
{
	if(!IsGetOff())
		return;

	CMkCommand cmd(m_pMkDb, "update_rider_get_off");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
	{
		MessageBox("퇴근처리 되었습니다.", "확인", MB_ICONINFORMATION);
	}
}

void CMainFrame::ShowTrasferSmsToShaerBalance()
{ 
	if(!LF->POWER_CHECK(1540, "SMS<->공유정산금 이체 보기", TRUE))
		return; 

	CREATE_MODALESS(CTransferSmsBetweenShareBalanceDlg, this);
	pDlg->m_bOnlyOneSite = (long)m_ba.GetSize() == 1 ? TRUE : FALSE;
	SHOW_MODALESS(CTransferSmsBetweenShareBalanceDlg, this);
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	CXTPMenuBar* pMenuBar = DYNAMIC_DOWNCAST(CXTPMenuBar, lpCreateControl->pCommandBar);
	if (pMenuBar)
	{
		ASSERT(lpCreateControl->pMenu);
		CMenu* pPopupMenu = lpCreateControl->pMenu->GetSubMenu(lpCreateControl->nIndex);

		if(lpCreateControl->strCaption == _T("기능(&M)"))
		{

			CXTPControlPopup* pControlPopup = CXTPControlPopup::CreateControlPopup(xtpControlPopup);

			// Exclude only IDR_MAINFRAME template
			pControlPopup->ExcludeDocTemplate(IDR_MAINFRAME);

			

			//if((m_ui.nCompany == 5908 || m_ui.nCompany == 5902) && m_ui.nRole == 0)
			//	pPopupMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_SEND_MSG_ALL_SHARE, "협력사 전체공지 보내기");

			if(m_ci.m_bRcpIntMode1 && m_ui.nRole == 0)
				pPopupMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_GENERAL_APP_REGISTER, "범용어플 신청");

			if(m_ci.m_bRcpIntMode1 && m_ui.nRole == 0)
				pPopupMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_GENERAL_OPENAPI_REGISTER, "오픈API 신청");

			if(CHolidayDeliveryInfoDlg::IsHolidayCompany(TRUE))
				pPopupMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_SHOW_HOLIDAY_DELIVERY, "명절 선물 배송지 입력창");

			pControlPopup->SetCommandBar(pPopupMenu);
			lpCreateControl->pControl = pControlPopup;

			return TRUE;
		}
	}

	return FALSE;
}

void CMainFrame::OnGeneralAppRegister()
{
	if(m_ci.m_bRcpIntMode1 != 1)
	{
		MessageBox("지사는 신청하실수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CGenerateAppStateDlg2 dlg;
	dlg.DoModal();
}

void CMainFrame::OnGeneralOpenAPIRegister()
{
	if(m_ci.m_bRcpIntMode1 != 1)
	{
		MessageBox("지사는 신청하실수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CGenerateOpenAPIStateDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnRunQ5()
{
	LF->RunProgram(LF->GetModuleFullPath() + "smartq5_update.exe", "/run");
}