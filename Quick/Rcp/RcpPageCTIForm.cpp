// RcpPageCTIForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Resource.h"
#include "RcpPageCTIForm.h"
#include "RcpView.h"
#include "CallListRecord.h"
#include "CTIFormSetupDlg.h"
#include "MkLock.h"
#include "ReportMultilinePaintManager.h" 
#include "AddCallHotNumberDlg.h"
#include "JinsangTelRegDlg.h"
#include "mmsystem.h"
#include "digitalv.h"
#include "CIDSelectDlg.h"
#include "OpStatePaintManagerEx.h"
#include "RecFileSelectDlg.h"
#include "MyCallMessage.h"

#define ID_MENU_HOT_NUMBER				0xF000
#define ID_MENU_MAKE_CALL				0xE000
#define ID_MENU_POPUP_RCP_DLG			0xE001
#define ID_MENU_SEARCH_RCP_LIST			0xE002
#define ID_MENU_SEARCH_RCP_LIST2		0xE003
#define ID_MENU_ADD_BLOCKING_NUMBER		0xE004
#define ID_MENU_MAKE_CALL_INNER_LINE	0xD000
#define ID_MENU_CHAT_MESSENGER			0xD001
#define ID_MENU_HOT_NUMBER_LOGISOFT		0xC000
#define ID_MENU_HOT_NUMBER_ADD			0xC001

#define ID_COLUMN_SHOW      500

PHONE_CUSTOMER_MAP CRcpPageCTIForm::m_mapPhoneCustomer;
CCriticalSection CRcpPageCTIForm::m_csPhoneCustomer;

//ALL_BARO_SMS_MAP CRcpPageCTIForm::m_mapAllbaroSMS;
//CCriticalSection CRcpPageCTIForm::m_csAllbaroSMS;

// CRcpPageCTIForm

IMPLEMENT_DYNCREATE(CRcpPageCTIForm, CMyFormView)

CRcpPageCTIForm::CRcpPageCTIForm()
: CMyFormView(CRcpPageCTIForm::IDD)
{
	m_bInitialized = FALSE;
	m_pOPPaintManager = NULL;
	m_bConnected = FALSE;
	m_bChangeCursor = FALSE; // 화면이동 변수들
	m_bMoveControl = FALSE;
	m_dwRefreshStop = 0;
	m_pLastAutoTransferRecord = NULL;
	m_dwLastAutoTransferTick = 0;
	m_pwndParent = NULL;
	m_dtLastRefresh = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 12, 0, 0);
	m_bMouseButtonDown = FALSE;
	m_bAutoBlockingThreadAlive = FALSE;
	m_hAutoBlockingHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hExitHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadDiedHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bUseCTI = FALSE;
	m_bHotCID = FALSE;
	m_bAutoTransfer = FALSE;
	m_pMainDb = NULL;
	m_pLogDb = NULL;
	m_bEnableDBRefresh = FALSE;
	m_bColumnInsert = FALSE;
	m_bQueueRcpPopup = FALSE;
	m_nRingCount = 0;
	m_bRingColor = TRUE;
	m_bRingMusic = FALSE;
	m_bIPPBX = FALSE;
	m_bSoundPlay = FALSE;
	m_dwDeviceID = 0;
	m_bNotCalllistPickup = FALSE;
	m_pOPPaintManagerEx = NULL;
	m_nOPStateWidth = 95;
}

CRcpPageCTIForm::~CRcpPageCTIForm()
{
	CString strTemp; long nSize;
	SaveReportState(strTemp, nSize);

	if(m_bAutoBlockingThreadAlive)
	{
		SetEvent(m_hExitHandle);
		WaitForSingleObject(m_hThreadDiedHandle, 2000);
	}

	CloseHandle(m_hAutoBlockingHandle);
	CloseHandle(m_hExitHandle);
	CloseHandle(m_hThreadDiedHandle);


	m_call.SetDlg(NULL);
	m_callSUB.SetDlg(NULL);
	m_call.Close();
	m_callSUB.Close();
}

void CRcpPageCTIForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATE_EDIT, m_edtState);
	DDX_Control(pDX, IDC_HANG_UP_BTN, m_btnHangUp);

	DDX_Control(pDX, IDC_RING_INFO_STATIC, m_stcRingInfo);
	DDX_Control(pDX, IDC_CALL_REPORT_CONTROL, m_wndReport);
	DDX_Control(pDX, IDC_OP_REPORT_CONTROL, m_wndOPReport);

	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_REFRESH_STOP_CHECK, m_chkRefreshStop);
	DDX_Control(pDX, IDC_MAKE_CALL_EDIT, m_edtMakeCall);
	DDX_Control(pDX, IDC_MAKE_CALL_HOT_KEY_BTN, m_btnMakeCallHotKey);

	DDX_Control(pDX, IDC_CID_BTN, m_btnCIDNumber);
	DDX_Control(pDX, IDC_QUEUE_STATE_EDIT, m_edtQueueState);
	DDX_Control(pDX, IDC_QUEUE_PAUSE_BTN, m_btnQueuePause);
}

BEGIN_MESSAGE_MAP(CRcpPageCTIForm, CMyFormView)
	ON_BN_CLICKED(IDC_HANG_UP_BTN, OnBnClickedHangUpBtn)
	ON_BN_CLICKED(IDC_ENABLE_CHECK, OnBnClickedEnableCheck)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_UP_BTN, OnBnClickedUpBtn)
	ON_BN_CLICKED(IDC_DN_BTN, OnBnClickedDnBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, OnBnClickedConnectBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AUTO_ANSWER_BTN, OnBnClickedAutoAnswerBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_CALL_REPORT_CONTROL, OnReportItemDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_OP_REPORT_CONTROL, OnOPReportItemDblClick)
	ON_NOTIFY(NM_RCLICK, IDC_CALL_REPORT_CONTROL, OnReportItemRClick)
	ON_NOTIFY(NM_RCLICK, IDC_OP_REPORT_CONTROL, OnOPReportItemRClick)
	ON_BN_CLICKED(IDC_SETUP_BTN, OnBnClickedSetupBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_EN_SETFOCUS(IDC_SEARCH_EDIT, OnEnSetfocusSearchEdit)
	ON_BN_CLICKED(IDC_REFRESH_STOP_CHECK, OnBnClickedRefreshStopCheck)
	ON_BN_CLICKED(IDC_MAKE_CALL_USER_BTN, &CRcpPageCTIForm::OnBnClickedMakeCallUserBtn)
	ON_BN_CLICKED(IDC_MAKE_CALL_HOT_KEY_BTN, &CRcpPageCTIForm::OnBnClickedMakeCallHotKeyBtn)
	ON_COMMAND_RANGE(ID_MENU_HOT_NUMBER_LOGISOFT,ID_MENU_HOT_NUMBER_LOGISOFT, OnMenuHotNumber)
	ON_COMMAND_RANGE(ID_MENU_HOT_NUMBER_ADD,ID_MENU_HOT_NUMBER_ADD, OnMenuHotNumber)
	ON_COMMAND_RANGE(ID_MENU_HOT_NUMBER,ID_MENU_HOT_NUMBER + 100, OnMenuHotNumber)
	ON_COMMAND_RANGE(ID_MENU_HOT_NUMBER+1000,ID_MENU_HOT_NUMBER + 1100, OnMenuHotNumber)
	ON_COMMAND_RANGE(ID_MENU_MAKE_CALL, ID_MENU_ADD_BLOCKING_NUMBER, OnMenuCallList)
	ON_COMMAND_RANGE(ID_MENU_MAKE_CALL_INNER_LINE, ID_MENU_CHAT_MESSENGER, OnMenuOPList)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_CALL_REPORT_CONTROL, OnReportColumnChangeChanged)
	ON_NOTIFY(XTP_NM_GRID_HEADER_RCLICK, IDC_CALL_REPORT_CONTROL, OnReportColumnRClick)
	ON_BN_CLICKED(IDC_QUEUE_PAUSE_BTN, OnBnClickedQueuePausedBtn)
	ON_COMMAND(ID_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_CID_BTN, OnBnClickedCIDBtn)
	ON_NOTIFY(NM_CLICK, IDC_OP_REPORT_CONTROL, OnOpReportItemClick)
	ON_NOTIFY(UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_MESSAGE(WM_MY_CALL_MESSAGE, OnMyCallMessage)
END_MESSAGE_MAP()


// CRcpPageCTIForm 진단입니다.

#ifdef _DEBUG
void CRcpPageCTIForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CRcpPageCTIForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CRcpPageCTIForm 메시지 처리기입니다.

void CRcpPageCTIForm::OnInitialUpdate()
{
	if(m_bInitialized)
		return;

	m_pMainFrame = (CWnd*)AfxGetMainWnd();

#ifdef _SYSMANAGER
	m_pMainDb = m_pMkSysmanager;	
	CMyCall::MakeOpLineMapping();
#else
	m_pMainDb = m_pMkDb;
	m_pLogDb = m_pMkDb;
#endif

	m_pwndParent = GetOwner();
	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcVertical = AfxGetApp()->LoadCursor(IDC_VERTICAL);
	m_bInitialized = TRUE;

	CMyFormView::OnInitialUpdate();


#ifdef _SYSMANAGER
	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "ⓝ", 25, TRUE));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "시각", 60, TRUE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "전화번호", 90, TRUE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, "지사", 0, TRUE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, "상태", 45, TRUE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, "최종시각", 60, TRUE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, "직원", 70, TRUE));
	CXTPGridColumn *pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, "고객정보", 510, TRUE));
	CXTPGridColumn *pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, "L통화자", 80, TRUE));
	CXTPGridColumn *pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, "링", 40, TRUE));
	CXTPGridColumn *pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, "통화", 50, TRUE));
	CXTPGridColumn *pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, "적요", 0, TRUE));
	pCol3->SetVisible(FALSE);
	pCol11->SetVisible(FALSE);
#else
	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "ⓝ", 25, TRUE));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "시각", 60, TRUE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "전화번호", 90, TRUE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, "상태", 45, TRUE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, "직원", 70, TRUE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, "고객명", 310, TRUE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, "부서", 70, TRUE));
	CXTPGridColumn *pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, "담당", 70, TRUE));
	CXTPGridColumn *pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, "동명", 50, TRUE));

	CXTPGridColumn *pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, "지사", 120, TRUE));
	CXTPGridColumn *pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, "최종시각", 60, TRUE));
	CXTPGridColumn *pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, "고객번호", 60, TRUE));
	CXTPGridColumn *pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(12, "최종통화", 80, TRUE));
	CXTPGridColumn *pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(13, "링", 40, TRUE));
	CXTPGridColumn *pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, "통화", 50, TRUE));
	CXTPGridColumn *pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(15, "적요", 120, TRUE));
	CXTPGridColumn *pCol16 = m_wndReport.AddColumn(new CXTPGridColumn(16, "녹취", 35, TRUE));
	CXTPGridColumn *pCol17 = m_wndReport.AddColumn(new CXTPGridColumn(17, "녹취", 35, TRUE));

#endif

	pCol9->SetVisible(FALSE);
	pCol10->SetVisible(FALSE);
	pCol11->SetVisible(FALSE);
	pCol12->SetVisible(FALSE);
	//pCol13->SetVisible(FALSE);
	//pCol14->SetVisible(FALSE);
	pCol15->SetVisible(FALSE);

	//if(m_ba.GetCount() <= 1)
	//{
	//	pCol3->SetVisible(FALSE);
	//pCol7->SetWidth(430);
	//}

	pCol0->SetAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);
	pCol4->SetAlignment(DT_LEFT);
	pCol5->SetAlignment(DT_LEFT);
	pCol6->SetAlignment(DT_LEFT);
	pCol7->SetAlignment(DT_LEFT);
	pCol8->SetAlignment(DT_LEFT);
	pCol9->SetAlignment(DT_LEFT);
	pCol10->SetAlignment(DT_LEFT);
	pCol11->SetAlignment(DT_LEFT);
	pCol16->SetAlignment(DT_CENTER);
	pCol16->SetAlignment(DT_CENTER);

	m_wndReport.SetPaintManager(new CReportMultilinePaintManager);
	m_wndReport.GetColumns()->SetSortColumn(pCol1, FALSE);
	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);


	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.SetGridColor(RGB(212, 208, 200));
	m_wndReport.SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_bHideSelection = TRUE;
	m_wndReport.EnableToolTips(FALSE);
	m_wndReport.Populate();
	m_bColumnInsert = TRUE;

	BOOL bShowLastPhoneNumber = FALSE;
#ifdef _DAERI
	bShowLastPhoneNumber = POWER_CHECK(2009, "고객전화번호 끝번호 보이기");
#else
	bShowLastPhoneNumber = TRUE;
#endif

	m_wndOPReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndOPReport.SetTreeIndent(10);
	m_wndOPReport.GetPaintManager()->m_strNoItems = "";
	m_wndOPReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndOPReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndOPReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndOPReport.AllowEdit(FALSE);
	m_wndOPReport.FocusSubItems(FALSE);
	m_wndOPReport.GetPaintManager()->SetGridStyle(FALSE, xtpGridNoLines);
	m_wndOPReport.SetGridColor(RGB(150, 150, 180));
	m_wndOPReport.ShowHeader(FALSE);
	m_wndOPReport.EnableToolTips(FALSE);
	m_wndOPReport.GetPaintManager()->m_bHideSelection = TRUE;

	if (GetCurBranchInfo()->bIPPBXType)
	{
		m_pOPPaintManagerEx = new COPStatePaintManagerEx;
		m_pOPPaintManagerEx->m_bShowLastPhoneNumber = bShowLastPhoneNumber;
		m_wndOPReport.SetPaintManager(m_pOPPaintManagerEx);
		m_nOPStateWidth = 120;

		m_tooltip.Create(this, FALSE);
		m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
		m_tooltip.SetNotify();
		m_tooltip.SetTransparency(30);

		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
		m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

		//m_tooltip.AddTool(&m_wndOPReport, ""); choe
		m_tooltip.SetColorBk(RGB(255, 255, 0));
	}
	else
	{
		m_pOPPaintManager = new COPStatePaintManager;
		m_pOPPaintManager->m_bShowLastPhoneNumber = bShowLastPhoneNumber;
		m_wndOPReport.SetPaintManager(m_pOPPaintManager);
	}

	m_call.SetDlg(this);
	m_callSUB.SetDlg(this);

	m_edtState.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtState.SetUserOption(RGB(0, 0, 255), RGB(230, 220, 255), "", FALSE, TRUE);
	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "전번/통화자", FALSE, FALSE);
	m_edtMakeCall.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtMakeCall.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "임의전화걸기", FALSE, FALSE);

	m_pBiCID =  m_ba.GetAt(0);
	m_btnCIDNumber.SetWindowText(m_pBiCID->strBranchName.Left(10) + "▷");

	LoadCTIInfo(m_ui.strID);
	LoadReportState();
	GetPreCallInfoLog(TRUE);

	MoveTopControl();

	if(m_bUseCTI)
		OnBnClickedEnableCheck();

	SetTimer(0, 1000, NULL);
	SetTimer(2, 10000, NULL);
	SetTimer(4, 1000, NULL); //링인포 색 변화 타이머

	//if(::IsThisCompany("올바로") || ::IsThisCompany("로지"))
	//	SetTimer(10, 10000, NULL);
}

void CRcpPageCTIForm::MoveTopControl()
{
	if(!GetCurBranchInfo()->bIPPBXType)
	{
		GetDlgItem(IDC_QUEUE_STATE_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_QUEUE_PAUSE_BTN)->ShowWindow(SW_HIDE);

		MoveOffsetControl(GetDlgItem(IDC_SEARCH_STATIC), -185);
		MoveOffsetControl(GetDlgItem(IDC_SEARCH_EDIT), -185);
		MoveOffsetControl(GetDlgItem(IDC_AUTO_ANSWER_BTN), -185);
		MoveOffsetControl(GetDlgItem(IDC_HANG_UP_BTN), -185);
		MoveOffsetControl(GetDlgItem(IDC_CID_BTN), -185);
		MoveOffsetControl(GetDlgItem(IDC_MAKE_CALL_EDIT), -185);
		MoveOffsetControl(GetDlgItem(IDC_MAKE_CALL_USER_BTN), -185);
		MoveOffsetControl(GetDlgItem(IDC_MAKE_CALL_HOT_KEY_BTN), -185);
		MoveOffsetControl(GetDlgItem(IDC_RING_INFO_STATIC), -185);
	}
}

void CRcpPageCTIForm::MoveOffsetControl(CWnd *pWnd, int nOffset)
{
	CRect rc;
	pWnd->GetWindowRect(rc);
	rc.left += nOffset;
	rc.right += nOffset;
	ScreenToClient(rc);
	pWnd->MoveWindow(rc);
}

void CRcpPageCTIForm::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify->pColumn);

	PopupColumnSelect();
}

void CRcpPageCTIForm::PopupColumnSelect()
{
	CPoint ptClick;
	::GetCursorPos(&ptClick);

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	CXTPGridColumns* pColumns = m_wndReport.GetColumns();

	CMenu menuColumns;
	VERIFY(menuColumns.CreatePopupMenu());
	int nColumnCount = pColumns->GetCount();

	for(int nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		CString sCaption = pCol->GetCaption();
		//if (!sCaption.IsEmpty())
		menuColumns.AppendMenu(MF_STRING, ID_COLUMN_SHOW + nColumn, sCaption);
		menuColumns.CheckMenuItem(ID_COLUMN_SHOW + nColumn,
			MF_BYCOMMAND | (pCol->IsVisible() ? MF_CHECKED : MF_UNCHECKED) );
	}

	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuColumns.m_hMenu, "컬럼");


	// track menu
#ifndef _XTP_INCLUDE_COMMANDBARS
	int nMenuResult = menu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#else
	int nMenuResult = CXTPCommandBars::TrackPopupMenu(&menu, TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#endif

	// process column selection item
	if (nMenuResult >= ID_COLUMN_SHOW)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nMenuResult - ID_COLUMN_SHOW);
		if (pCol)
		{
			pCol->SetVisible(!pCol->IsVisible());
			CString strTemp; long nSize;
			SaveReportState(strTemp, nSize);
		}
	}
}

BOOL CRcpPageCTIForm::LoadCTIInfo(CString strUserID)
{
	CString strKey = CString("TelMonitor") + (strUserID.IsEmpty() ? "" : "\\" + strUserID);
	CString strIP = m_strIP;
	CString strIP2 = m_strIP2;
	CString strKeyPhoneID = m_strKeyPhoneID;
	BOOL bUseCTI = m_bUseCTI;
	BOOL bQueueRcpPopup = m_bQueueRcpPopup;
	CString strRingMusicPath = m_strRingMusicPath;

	m_strIP = AfxGetApp()->GetProfileString(strKey, "ServerIP", "");
	m_strIP2 = AfxGetApp()->GetProfileString(strKey, "ServerIP2", "");
	m_strKeyPhoneID = AfxGetApp()->GetProfileString(strKey, "KeyPhoneID", "");
	m_strAutoTransfer = AfxGetApp()->GetProfileString(strKey, "AutoTransfer1", "");
	m_strAutoTransfer2 = AfxGetApp()->GetProfileString(strKey, "AutoTransfer2", "");
	m_bUseCTI = AfxGetApp()->GetProfileInt(strKey, "Enable", 1);
	m_bHotCID = AfxGetApp()->GetProfileInt(strKey, "HotCID", 0);
	m_bAutoBlocking = AfxGetApp()->GetProfileInt(strKey, "AutoBlocking", 0);
	m_bAutoTransfer = AfxGetApp()->GetProfileInt(strKey, "AutoTransfer", 0);
	m_bEnableDBRefresh = AfxGetApp()->GetProfileInt(strKey, "EnableDBRefresh", 0);
	m_bQueueRcpPopup = AfxGetApp()->GetProfileInt(strKey, "QueueRcpPopup", 0);
	m_nRcpPopupSecond = AfxGetApp()->GetProfileInt(strKey, "RcpPopupSecond", 0);
	m_bRingColor = AfxGetApp()->GetProfileInt(strKey, "RingColor", 0);
	m_bRingMusic = AfxGetApp()->GetProfileInt(strKey, "RingMusic", 0);
	m_strRingMusicPath = AfxGetApp()->GetProfileString(strKey, "RingMusicPath", "");
	m_bNotCalllistPickup = AfxGetApp()->GetProfileInt("TelMonitor", "NotCalllistPickup", 0);

	CBranchInfo *pBI;
	if (m_ba.GetCount() > 1)
		pBI = m_ba.GetAt(1);
	else
		pBI = m_ba.GetAt(0);

	m_bIPPBX = pBI->bIPPBXType;
	if (m_bIPPBX == FALSE)
		m_bQueueRcpPopup = FALSE;

	if(strIP.IsEmpty())
	{
		if(strUserID.IsEmpty())
			CRcpPageCTIForm::LoadTelClientInfo(strIP, strKeyPhoneID);
		else
			LoadCTIInfo();
	}

	if(m_strIP.IsEmpty())
		LoadTelClientInfo(m_strIP, m_strKeyPhoneID);

	if(strRingMusicPath != m_strRingMusicPath)
		OnOpenMusic();

	if(strIP != m_strIP || strIP2 != m_strIP2 || strKeyPhoneID != m_strKeyPhoneID || bUseCTI != m_bUseCTI)
		return TRUE;

	return FALSE;
}

void CRcpPageCTIForm::OnOpenMusic()
{
	mciSendCommand(m_dwDeviceID,MCI_CLOSE,0,NULL);
	m_dwDeviceID = 0;
	m_bSoundPlay = FALSE;

	MCI_OPEN_PARMS mciOpenParms;
	int errorCode;

	mciOpenParms.lpstrElementName = m_strRingMusicPath;
	mciOpenParms.lpstrDeviceType = "MPEGVideo";
	errorCode = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParms);
	m_dwDeviceID = mciOpenParms.wDeviceID;

	if(errorCode != 0)
	{
		char szError[1024];
		mciGetErrorString(errorCode, szError, 1024);
		MessageBox(szError);
	}
}

BOOL CRcpPageCTIForm::OnPlayMusic()
{
	if(m_dwDeviceID <= 0)
		return FALSE;

	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	return mciSendCommand(m_dwDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT | MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms) == 0 ? TRUE : FALSE;
}

BOOL CRcpPageCTIForm::OnStopMusic()
{
	if(m_dwDeviceID <= 0)
		return TRUE;

	MCI_PLAY_PARMS mciPlayParms; 
	mciPlayParms.dwCallback = NULL;
	if(mciSendCommand(m_dwDeviceID, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms) != 0)
		return TRUE;

	mciSendCommand (m_dwDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD) (LPVOID) NULL); 
	return FALSE;
}

void CRcpPageCTIForm::OnBnClickedEnableCheck()
{
	m_call.SetKey(m_strTelserverKey.IsEmpty() ? "" : m_strTelserverKey);
	m_callSUB.SetKey(m_strTelserverKey.IsEmpty() ? "" : m_strTelserverKey);

	if(m_bUseCTI)
	{
		int nType = TYPE_TEL_CLIENT	| TYPE_TEL_CLIENT_ALLMESSAGE | TYPE_TEL_SERVER_MONITER | TYPE_TEL_SERVER_MONITER_LOG;
		//int nType = TYPE_TEL_CLIENT	| TYPE_TEL_CLIENT_ALLMESSAGE;
		if(m_strIP.GetLength() > 0 && m_strKeyPhoneID.GetLength() > 0)
		{
			m_call.Connect(m_strIP, m_strKeyPhoneID, m_ui.strName, nType);
			CString strKey = CString("TelMonitor\\") + m_ui.strID;
			AfxGetApp()->WriteProfileInt("TelMonitor", "Enable", 1);
			AfxGetApp()->WriteProfileInt(strKey, "Enable", 1);
		}
		else
		{
			RefreshState("IP/내선번호 입력요망");
		}
	}
	else 
	{
		if(!m_call.IsShutDown())
			m_call.Close();

		if(!m_callSUB.IsShutDown())
			m_callSUB.Close();

		AfxGetApp()->WriteProfileInt("TelMonitor", "Enable", 0);
	}
}


void CRcpPageCTIForm::OnBnClickedHangUpBtn()
{
	m_call.HangUp();
}


CString CRcpPageCTIForm::GetPhoneState(int nType, BOOL bOutBoundCall)
{
	CString strCall = bOutBoundCall ? "ⓒ" : "";

	switch(nType)
	{
	case PH_RING: 
		return "링";
	case PH_ANSWER:
		return strCall + "통화";
	case PH_HANG_UP:
		return strCall + "끊음";
	case PH_OUT_BOUND_CALL:
		return "걸기";
	case PH_ARS_ANSWER:
		return "ARS";
	default:
		return "N/A";
	}
}


void CRcpPageCTIForm::SetCallList(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,
								  const char* szDID,const char* szOperator,const char* szCustomer,
								  COleDateTime dtCur,
								  BOOL bRedraw)
{
	if(!m_wndReport.GetSafeHwnd())
		return;

	static DWORD dwTick = GetTickCount();
	//g_bana_log->Print("%s: %s tick %d\n", szPhoneNumber, GetPhoneState(nType), GetTickCount() - dwTick);
	dwTick = GetTickCount();

	if(m_bIPPBX)
		g_bana_log->Print("ippbx calllist %d, %s, %s, %s, %s \r\n", nType, szPhoneNumber, szKeyPhoneID, szDID, szOperator);

	m_dtLastRefresh = dtCur;
	SetLastRefresh();

	int nPreType = PH_HANG_UP;
	CString strEtc;
	BOOL bSimpleHangup = FALSE;
	BOOL bInserted = FALSE;
	CCallListRecord *pRecord = NULL;
	BOOL bHangUpFirst = FALSE;

	if(nType == PH_HANG_UP && strlen(szPhoneNumber) < 6)
	{
		pRecord = FindCallListItemWithKeyPhoneID(szKeyPhoneID, szPhoneNumber, dtCur);
		if(!pRecord)
			return;

		bSimpleHangup = TRUE;
	}
	else
	{
		pRecord = FindCallListItem(nType, szPhoneNumber, dtCur);
		//if(!pRecord && nType == PH_HANG_UP)
		//	return;
		if(!pRecord && nType == PH_HANG_UP)	
			bHangUpFirst = TRUE;
	}

	if(!pRecord)
	{
		bInserted = TRUE;
		pRecord = new CCallListRecord(dtCur);
		m_wndReport.AddRecord(pRecord);
		pRecord->m_bIPPBX = m_bIPPBX;
		pRecord->m_nState = nType;
		pRecord->m_strOperator = szOperator;
		pRecord->m_strLastAnswer = GetLastAnswerOP(szPhoneNumber, COleDateTime::GetCurrentTime());

#ifdef _DAERI
		pRecord->m_bShowLastPhoneNumber = POWER_CHECK(2009, "고객전화번호 끝번호 보이기");
#else
		pRecord->m_bShowLastPhoneNumber = TRUE;
#endif		
	}

	AddPhoneCustomer(szPhoneNumber, szCustomer);


	if(nType == PH_ANSWER)
		AddLastAnswerOP(szPhoneNumber, szOperator, dtCur);


	//이전상태가 ANSWER이고, 현재상태가 HANGUP인데, 시간차가 1초이내인 경우에 무시함
	//착신이되면서 HANGUP신호가 나중에 들어오는 부분을 보안한것임
	/*if((pRecord->m_nState == PH_ANSWER || pRecord->m_nState == PH_RING) && nType == PH_HANG_UP)
	{
	COleDateTimeSpan span = dtCur - pRecord->m_dtLastTime;

	if(span.GetTotalSeconds() < 0.5)
	return;	
	}*/

	CString strKeyPhoneID = szKeyPhoneID;

	if((pRecord->m_nState == PH_ANSWER || pRecord->m_nState == PH_RING) && nType == PH_HANG_UP && pRecord->m_strKeyPhoneID != strKeyPhoneID)
	{
		g_bana_log->Print("calllist %s %s -> %s %d -> %d \r\n", pRecord->m_strPhone, pRecord->m_strKeyPhoneID, strKeyPhoneID, pRecord->m_nState, nType);
		if(RefreshOK() && bRedraw && !m_bMouseButtonDown)
		{
			FilterList(m_strLastFilterPhone);
			EnsureVisibleFirstRow();
			m_wndReport.Populate();
		}
		return;
	}

	if(pRecord->m_strOperator.GetLength() < 2)
	{
		OP_STATE_MAP::iterator it = GetOPStateMap()->find(pRecord->m_strKeyPhoneID);
		if(it != GetOPStateMap()->end())
			pRecord->m_strOperator = it->second->strOperator;
	}

	if(!bSimpleHangup)
	{
#ifdef _SYSMANAGER
		CBranchInfo *pBi2 = ((CMainFrame*)AfxGetMainWnd())->SearchLineGroup((char*)szDID);
#else 
		CBranchInfo *pBi2 = LU->SearchLineGroup((char*)szDID);
#endif
		if(pBi2 == NULL)
		{
			//pRecord->m_strBranch = "";
		}
		else 
		{
			CBranchInfo *pBi = m_ba.GetCount() > 1 ? pBi2 : 0;
			if(pBi)
			{
				pRecord->m_strBranch = pBi->strBranchName;
				pRecord->m_nCompany = pBi->nCompanyCode;
				pRecord->m_strCallingLine = pBi->strCallingLine;
				CString strTemp1 = GetNoneDashNumber(pBi->strPhone);
				if(strTemp1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
					strTemp1 = strTemp1.Right(strTemp1.GetLength() - m_ci.m_strDDD.GetLength());
				pRecord->m_strCompanyPhone = strTemp1;
			}
			pRecord->m_strDID = szDID;
		}

		pRecord->m_strPhone = szPhoneNumber;
		pRecord->m_strKeyPhoneID = szKeyPhoneID;
		pRecord->m_strOperator = szOperator;

		if(!SetRecordData(pRecord, szPhoneNumber))
			pRecord->m_strCustomerName = szCustomer;
	}
	else
	{
		if(pRecord->m_nState == PH_HANG_UP)
		{
			if(RefreshOK() && bRedraw && !m_bMouseButtonDown)
			{
				if(pRecord->m_strCustomerName.IsEmpty() || pRecord->m_strCustomerName == " ")
				{
					CMkLock lock(m_csMap);
					m_map.insert(CALL_LIST_MAP::value_type(pRecord, CString(szPhoneNumber)));
					//SetRecordData(pRecord, CString(szPhoneNumber));
					SetTimer(3, 1000, NULL);//
				}				

				FilterList(m_strLastFilterPhone);
				EnsureVisibleFirstRow();
				m_wndReport.Populate();

				//g_bana_log->Print("4321 %s, %s, %s\r\n", pRecord->m_strCustomerName, szCustomer, szPhoneNumber);
			}
			else
			{
				//g_bana_log->Print("RefreshOK() = %d, bRedraw = %d, !m_bMouseButtonDown = %d\n", 
				//	RefreshOK(), bRedraw, !m_bMouseButtonDown);
			}
			return;
		}
	}

	nPreType = pRecord->m_nState;
	pRecord->m_nState = nType;
	pRecord->m_dtLastTime = dtCur;

	if(pRecord->m_nState == PH_RING)
	{
		pRecord->m_bRing = TRUE;
	}
	else if(pRecord->m_nState == PH_ANSWER)
	{
		pRecord->m_dtAnswer = pRecord->m_dtLastTime;
		pRecord->m_bAnswer = TRUE;
		pRecord->m_bMissing = FALSE;
	}
	else if(pRecord->m_nState == PH_OUT_BOUND_CALL)
	{
		pRecord->m_bOutBoundCall = TRUE;
		CCallListRecord *pLastRecord = FindCallListHasBranchInfo(szPhoneNumber);
		if(pLastRecord)
		{
			pRecord->m_strBranch = pLastRecord->m_strBranch;
			pRecord->m_strDID = pLastRecord->m_strDID;
		}
	}

	if(RefreshOK() && bRedraw && !m_bMouseButtonDown)
	{
		if(pRecord->m_strCustomerName.IsEmpty() || pRecord->m_strCustomerName == " ")
		{
			CMkLock lock(m_csMap);
			m_map.insert(CALL_LIST_MAP::value_type(pRecord, CString(szPhoneNumber)));
			//SetRecordData(pRecord, CString(szPhoneNumber));
			SetTimer(3, 1000, NULL);//
		}			

		FilterList(m_strLastFilterPhone);
		EnsureVisibleFirstRow();
		m_wndReport.Populate();

		/*if(::IsThisCompany("올바로") || ::IsThisCompany("로지"))
		{
			if(m_strKeyPhoneID == pRecord->m_strKeyPhoneID && (pRecord->m_strPhone.GetLength() == 10 || pRecord->m_strPhone.GetLength() == 11))
			{
				if(nType == PH_HANG_UP && (nPreType != PH_OUT_BOUND_CALL && nPreType != PH_HANG_UP))
					AddAllbaroSMS(pRecord->m_strPhone, m_strKeyPhoneID);
				else if(nPreType != PH_HANG_UP && nType != PH_HANG_UP)
					RemoveAllbaroSMS(pRecord->m_strPhone);
			}
		}*/
		
		g_bana_log->Print("1234 (%s), (%s), (%s)\r\n", pRecord->m_strCustomerName, szCustomer, szPhoneNumber);
	}
	else
	{
		//g_bana_log->Print("RefreshOK() = %d, bRedraw = %d, !m_bMouseButtonDown = %d\n", 
		//	RefreshOK(), bRedraw, !m_bMouseButtonDown);
	}
}

CCallListRecord* CRcpPageCTIForm::FindCallListItem(int nType, CString strPhoneNumber, COleDateTime dtCur)
{
	long nCount = m_wndReport.GetRecords()->GetCount();

	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);

		if(pRecord->m_strPhone == strPhoneNumber)
		{
			COleDateTimeSpan span = dtCur - pRecord->m_dtLastTime;

			//이전상태가 HANGUP에서 5초이내에 다시 전화가 올수없다는 전제조건하에
			//모든상태에 대해서 5초이내의 응답은 동일한호로 간주한다.
			if(span.GetTotalSeconds() <= 10)
				return pRecord;										

			if(pRecord->m_nState == PH_ANSWER || 
				pRecord->m_nState == PH_RING || 
				pRecord->m_nState == PH_ARS_ANSWER ||
				pRecord->m_nState == PH_OUT_BOUND_CALL)
			{
				if(span.GetTotalMinutes() <= 30)
					return pRecord;						
			}

			//ARS missing 상태에서 60초이내에 새로운 상태가 오면, 연결시킨다. 
			//ARS에서 일반내선으로 착신될 때, 끊어지는 현상 때문에 두개의 호로 잡히는 것을 방지함
			if(pRecord->m_bMissing && pRecord->m_strOperator.Find("ARS-") >= 0 &&
				(nType == PH_HANG_UP || nType == PH_ANSWER))
			{
				if(span.GetTotalSeconds() < 60)
					return pRecord;
			}
		}
	}
	return NULL;
}

CCallListRecord* CRcpPageCTIForm::FindCallListHasBranchInfo(CString strPhoneNumber)
{
	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);

		if(pRecord->m_strPhone == strPhoneNumber)
		{
			if(pRecord->m_strBranch.GetLength() > 0)
			{
				return pRecord;
			}
		}
	}
	return NULL;
}


CCallListRecord* CRcpPageCTIForm::FindCallListItemWithKeyPhoneID(CString strKeyPhoneID, CString strPhoneNumber, COleDateTime dtCur)
{
	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);
		if(pRecord->m_strKeyPhoneID == strKeyPhoneID && pRecord->m_strPhone == strPhoneNumber)
		{
			COleDateTimeSpan span = dtCur - pRecord->m_dtFirstTime;
			if(span.GetTotalSeconds() <= 300)
				return pRecord;		
		}
	}
	return NULL;
}


void CRcpPageCTIForm::OnSize(UINT nType, int cx, int cy)
{
	//	CMyFormView::OnSize(nType, cx, cy); //Scrollbars never are displayed;
	SetScaleToFitSize(CSize(cx, cy));

	if(m_wndReport.GetSafeHwnd())
	{
		CRect rc, rcList, rcOP;

		GetClientRect(rc);
		m_wndOPReport.GetWindowRect(rcOP);
		ScreenToClient(rcOP);
		rcOP.bottom = rc.bottom - 2;
		rcOP.right = rc.right - 2;
		rcOP.left = rcOP.right - 400;
		m_wndOPReport.MoveWindow(rcOP);

		m_wndReport.GetWindowRect(rcList);
		ScreenToClient(rcList);
		rcList.bottom = rc.bottom - 2;
		rcList.right = rcOP.left - 3;
		m_wndReport.MoveWindow(rcList);

		CXTPGridColumn *pCol = NULL;

		long nCount = m_wndReport.GetColumns()->GetCount();

		for(int i=0; i<nCount; i++)
		{
			pCol = m_wndReport.GetColumns()->GetAt(i);

			if(pCol->GetItemIndex() == COL_CUSTOMER_INFO)
				break;
		}

		if(pCol == NULL)
			pCol = m_wndReport.GetColumns()->GetAt(COL_CUSTOMER_INFO);

		int nHeaderWidth = m_wndReport.GetReportHeader()->GetWidth();
		int nColWidth = pCol->GetWidth();
		pCol->SetWidth(max(200, (nColWidth + rcList.Width() - nHeaderWidth)) - 20);

		if(m_wndOPReport.GetSafeHwnd())
			MakeOPList();
	}
}

void CRcpPageCTIForm::OnBnClickedUpBtn()
{
	((CRcpView*)GetOwner())->IncFormHeight();
}

void CRcpPageCTIForm::OnBnClickedDnBtn()
{
	((CRcpView*)GetOwner())->DecFormHeight();
}

BOOL CRcpPageCTIForm::LoadTelClientInfo(CString& strIP, CString& strKeyPhoneID)
{
	const char m_szSubKey[] = "SOFTWARE\\TelClient";
	HKEY hSubKey = 0;
	long nRet;	

	DWORD dwType;
	DWORD dwBytes = 128;
	BYTE  buffer[128] = "";


	__try {

		//레지스트리 키 오픈
		nRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
			m_szSubKey,
			0,
			KEY_ALL_ACCESS,
			&hSubKey);


		if(nRet != ERROR_SUCCESS) return FALSE;


		//값 로드
		nRet = ::RegQueryValueEx(hSubKey,
			"Server Address",
			0,
			&dwType,
			buffer,
			&dwBytes);

		if(nRet != ERROR_SUCCESS) return FALSE;
		buffer[dwBytes] = 0;
		strIP = (char*) buffer;


		memset(buffer,0,sizeof(buffer) );
		//값 로드
		nRet = ::RegQueryValueEx(hSubKey,
			"KeyPhone ID",
			0,
			&dwType,
			buffer,
			&dwBytes);

		if(nRet != ERROR_SUCCESS) return FALSE;
		buffer[dwBytes] = 0;
		strKeyPhoneID = (char*) buffer;

	}
	__finally {
		if(nRet != ERROR_SUCCESS) 
		{	
			strIP = "";
			strKeyPhoneID = "0";
		}

		RegCloseKey(hSubKey);
	}

	return TRUE;
}

void CRcpPageCTIForm::OnBnClickedConnectBtn()
{
	if(!m_call.IsShutDown())
		m_call.Close();

	if(!m_callSUB.IsShutDown())
		m_callSUB.Close();

	OnBnClickedEnableCheck();
}

void CRcpPageCTIForm::SocketConnected()
{
	if(m_callSUB.Connect(m_strIP, m_strKeyPhoneID, m_ui.strName+"@1.0", TYPE_TEL_CLIENT_CUSTOMER_INFO)) //@1.0이 스마트Q인지를 확인함
	{
		//g_bana_log->Print("SUB Socket 접속됨\n");
	}

	m_bConnected = TRUE;
	RefreshState();
}
void CRcpPageCTIForm::SocketDisConnected()
{
	if(!m_callSUB.IsShutDown())
		m_callSUB.Close();

	m_bConnected = FALSE;
	RefreshState();
}

void CRcpPageCTIForm::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0)
	{
		KillTimer(0);

		if(m_chkRefreshStop.GetCheck())
		{
			if((int)GetTickCount() - (int)m_dwRefreshStop > 3000)
			{
				m_chkRefreshStop.SetCheck(FALSE);
				//g_bana_log->Print("OnTimer: %d - %d, %d\n", GetTickCount(), m_dwRefreshStop, GetTickCount() - m_dwRefreshStop);
			}
		}


		if(!IsLastRefreshInOneSec())
		{
			if(RefreshOK())
			{
				if(m_wndReport.GetRecords()->GetCount() > 0)
				{
					m_wndReport.RedrawControl();
					EnsureVisibleFirstRow();

					m_wndOPReport.RedrawControl();
				}
			}
		}

		RefreshRingInfo();
		CheckAutoTransfer();
		CheckAutoBlocking();

		if(!m_bConnected && m_bEnableDBRefresh)
			GetPreCallInfoLog();

		SetTimer(0, 1000, NULL);
	}
	else if(nIDEvent == 1)
	{
		//g_bana_log->Print("리스트컨트롤에 갱신재개\n");
		KillTimer(1);
		m_bMouseButtonDown = FALSE;
		if(RefreshOK())
			m_wndReport.Populate();
	}
	else if(nIDEvent == 2)
	{
		AutoHangUp();
	}
	else if(nIDEvent == 3)
	{
		KillTimer(3);

		m_csMap.Lock();
		if(m_map.size() <= ZERO)
		{
			m_csMap.Unlock();
			return;
		}

		CALL_LIST_MAP::iterator it = m_map.begin();

		CCallListRecord *pRecord = it->first;
		CString strPhoneNumber = it->second;

		m_map.erase(it);
		if(m_map.size() > 0)
			SetTimer(3, 1000, NULL);

		m_csMap.Unlock();

		SetRecordData(pRecord, strPhoneNumber);
	}
	else if(nIDEvent == 4)
	{
		if(m_nRingCount <= 0)
		{
			if(m_bSoundPlay)
				m_bSoundPlay = OnStopMusic();

			if(m_bRingColor)
				m_stcRingInfo.RemoveReverse();
		}
		else
		{ 
			if(m_bRingMusic && m_strRingMusicPath.GetLength() > 0)
			{
				if(!m_bSoundPlay && (GetTickCount() - m_dwRingInfoTick) > 1500)
					m_bSoundPlay = OnPlayMusic();
			}
			else if(!m_bRingMusic && m_bSoundPlay)
				m_bSoundPlay = OnStopMusic();

			if (m_bRingColor)
				m_stcRingInfo.SetReverse();
		}
		m_stcRingInfo.Invalidate();
	}
	else if(nIDEvent == 10)
	{
		//SendAllbaroSMS();
	}

	CMyFormView::OnTimer(nIDEvent);
}

void CRcpPageCTIForm::OnBnClickedAutoAnswerBtn()
{	
	//if(GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CONTROL) & 0x8000) {
	//	int *a = NULL;
	//	*a = 1;
	//}


	CString strTakingLine;
	long nState = PH_RING;
	OP_STATE_MAP::iterator it, myIt;

	CString strFirstKeyPhoneID = m_strKeyPhoneID, strKeyPhoneIDs = "," + m_strKeyPhoneID + ",";
	if(m_strKeyPhoneID.Find(",") > 0)
		strFirstKeyPhoneID = m_strKeyPhoneID.Left(m_strKeyPhoneID.Find(","));
	myIt = GetOPStateMap()->find(strFirstKeyPhoneID);

	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);

		//우리사무실은 PH_RING 상태에서 착신시키지 못한다.
		//if(pRecord->m_nState == PH_ARS_ANSWER)
		if(pRecord->m_nState == PH_RING || pRecord->m_nState == PH_ARS_ANSWER)
		{
			it = GetOPStateMap()->find(pRecord->m_strKeyPhoneID);
			if(it == GetOPStateMap()->end())
				continue;

			//if(it->second->nState != PH_ARS_ANSWER)
			if(it->second->nState != PH_RING && it->second->nState != PH_ARS_ANSWER)
				continue;

			CString strRecordKeyPhoneID = "," + pRecord->m_strKeyPhoneID + ",";
			if(strKeyPhoneIDs.Find(strRecordKeyPhoneID) >= 0)
			{
				m_call.Answer();
				return;
			}

			if(myIt != GetOPStateMap()->end())
			{
				if(myIt->second->nState == PH_RING)
				{
					if(it->second->strCurPhone == myIt->second->strCurPhone)
					{
						m_call.Answer();
						return;
					}
				}
			}

			if(IsMyPreAnswerCustomer(m_strKeyPhoneID, pRecord->m_strPhone))
			{
				strTakingLine = pRecord->m_strKeyPhoneID;
				break;
			}

			strTakingLine = pRecord->m_strKeyPhoneID;
		}
	}

	if(!strTakingLine.IsEmpty())
	{
		if(nState == PH_RING)
			m_call.Redirect_Answer(strTakingLine);
		else 
			m_call.MakeCallingOrTransfer(strTakingLine);

		//MessageBox("전화를 받습니다.", "확인", MB_ICONINFORMATION);
	}
}

BOOL CRcpPageCTIForm::IsMyPreAnswerCustomer(CString strMyID, CString strPhone)
{
	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);

		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - pRecord->m_dtFirstTime;
		if(span.GetTotalMinutes() > 60)
			break;

		if(pRecord->m_nState == PH_HANG_UP && 
			pRecord->m_bAnswer && 
			pRecord->m_strPhone == strPhone)
		{
			if(strMyID.Find(pRecord->m_strKeyPhoneID) >= 0)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


void CRcpPageCTIForm::EnsureVisibleFirstRow()
{
	if(GetFocus() != &m_wndReport)
	{
		if(m_wndReport.GetRows()->GetCount() <= 0)
			return;


		CXTPGridRow *pRow = m_wndReport.GetRows()->GetAt(0);
		if(pRow)
		{
			m_wndReport.SetFocusedRow(pRow, FALSE, TRUE);
		}
	}
}

void CRcpPageCTIForm::MakeOPList(BOOL bReDraw)
{
	if(!m_wndOPReport.GetSafeHwnd())
		return;


	CXTPGridRecord *pRecord = NULL;
	OP_STATE_MAP::iterator it;

	CRect rc;
	m_wndOPReport.GetColumns()->Clear();
	m_wndOPReport.GetRows()->Clear();
	m_wndOPReport.GetRecords()->RemoveAll();
	m_wndOPReport.GetClientRect(rc);
	int nCols = max(rc.Width() / m_nOPStateWidth, 1);
	long nCol, nRow = -1, n = 0;

	for(int i = 0; i < nCols; i++)
	{
		CXTPGridColumn* pCol1 = 
			m_wndOPReport.AddColumn(new CXTPGridColumn(i, "", m_nOPStateWidth, FALSE));
	}

	for(it = GetOPStateMap()->begin(); it != GetOPStateMap()->end(); it++)
	{
		nCol = n++ % nCols;
		if(nCol == 0)
		{
			if(pRecord != NULL)
			{
				m_wndOPReport.AddRecord(pRecord);
			}

			pRecord = new CXTPGridRecord;
			nRow++;
		}

		CString strTemp;
		strTemp.Format("%s(%s)", it->second->strOperator, it->second->strKeyPhoneID);
		AddOpRecord(strTemp, pRecord, it->second);
		//COPStateRecordItem *pRecordItem = new COPStateRecordItem(strTemp);
		//pRecordItem->pOPState = it->second;
		//pRecord->AddItem(pRecordItem);
	}

	if(pRecord)
		m_wndOPReport.AddRecord(pRecord);

	if(bReDraw)
		m_wndOPReport.Populate();
}

void CRcpPageCTIForm::SetOPState(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,const char* szOperator,
								 CString strCustomer, 
								 COleDateTime dtCur,
								 BOOL bRedraw)
{
	CString strKeyPhoneID = szKeyPhoneID;
	//if(0 < atol(strKeyPhoneID) && atol(strKeyPhoneID) < 100)
	//{
	//	strKeyPhoneID = "ARS-" + strKeyPhoneID;
	//}

	OP_STATE_MAP::iterator it;
	it = GetOPStateMap()->find(strKeyPhoneID);

	CString strCName = ::GetValueByArg(strCustomer, "CUST_NAME");;

	if(it == GetOPStateMap()->end())
	{
		OP_STATE_INFO *pInfo = new OP_STATE_INFO;
		pInfo->nState = nType;
		pInfo->strCurPhone = szPhoneNumber;
		pInfo->strOperator = szOperator;
		pInfo->strKeyPhoneID = szKeyPhoneID;
		pInfo->strCustomer = strCName.GetLength() > 0 ? strCName : strCustomer;
		pInfo->dtLastTime = dtCur;
		pInfo->dtLastAnswer = dtCur;
		pInfo->bARSLine = FALSE;

		if(atol(strKeyPhoneID) < 100)
		{
			if(nType == PH_HANG_UP)
			{
				delete pInfo;
				return;
			}

			pInfo->strOperator = strKeyPhoneID;
			pInfo->bARSLine = TRUE;
		}

		GetOPStateMap()->insert(OP_STATE_MAP::value_type(strKeyPhoneID, pInfo));
		MakeOPList(bRedraw);
	}
	else
	{
		if(nType == PH_HANG_UP)
		{
			if(it->second->nState == PH_ANSWER)
			{
				COleDateTimeSpan span = dtCur - it->second->dtLastTime;
				if(span.GetTotalSeconds() >= 10.0)
				{
					it->second->dtLastAnswer = dtCur;
				}
			}
		}

		it->second->nState = nType;
		it->second->strCurPhone = szPhoneNumber;
		it->second->strOperator = szOperator;
		it->second->strKeyPhoneID = szKeyPhoneID;
		it->second->strCustomer = strCName.GetLength() > 0 ? strCName : strCustomer;

		if(nType != PH_RING)
		{
			it->second->dtLastTime = dtCur;		
		}

		if(nType == PH_HANG_UP && it->second->bARSLine)
		{
			delete it->second;
			GetOPStateMap()->erase(it);
			MakeOPList(bRedraw);
		}
	}

	if(bRedraw && m_strKeyPhoneID == szKeyPhoneID)
	{
		if(m_pOPPaintManagerEx)
			m_pOPPaintManagerEx->m_nMyState = nType;
	}

	if(bRedraw)
		m_wndOPReport.RedrawControl();
}

void CRcpPageCTIForm::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	long nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_wndReport.GetRows()->GetAt(nRow);
		CCallListRecord *pRecord = (CCallListRecord*)pRow->GetRecord();

		if(nCol == 16 || nCol == 17) //녹취관련
		{
			if(!POWER_CHECK(1951, "파일 재생") && !POWER_CHECK(1953, "본인 파일 재생"))
			{
				MessageBox("녹취 파일듣기 권한이 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			CString strFolderDate = pRecord->m_dtFirstTime.Format("%Y-%m-%d");

			CRecFileSelectDlg dlg;

			dlg.m_dtDate = pRecord->m_dtFirstTime;
			dlg.m_nCompany = pRecord->m_nCompany == 0 ? m_ci.m_nCompanyCode : pRecord->m_nCompany;
			dlg.m_strPhone = pRecord->m_strPhone;

			if(dlg.DoModal() != IDOK)
			{
				MessageBox("녹취 파일이 없거나 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
				return;
			}

			if(nCol == 16)			//전화기 듣기
			{
				if(LU->GetRcpView())
				{
					LU->GetRcpView()->PlayRecordFile(strFolderDate, dlg.m_strRetFileName);
				}
			}		
			else if(nCol == 17)		//접수플 듣기
			{
				if(MessageBox("파일을 다운로드 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
					return;

				LU->PlayRecFile(dlg.m_dtRetDate, GetFolderDate(dlg.m_strRetFileName), dlg.m_strRetKeyPhoneID, pRecord->m_strPhone, dlg.m_strRetFileName, dlg.m_nRetBound);
			}
		}
		else
		{
			if(pRecord->m_nState == PH_HANG_UP || m_bNotCalllistPickup) 
			{
				PopupRcpDlg(pRecord->m_strPhone, pRecord->m_strKeyPhoneID, pRecord->m_strDID);
			}
			else if(pRecord->m_nState != PH_RING && pRecord->m_nState != PH_ARS_ANSWER)
			{
				MessageBox("링이 울리고 있는 라인만 받을 수 있습니다.(ARS는 가능함)", "확인", MB_ICONINFORMATION);
			}
			else
			{
				CString strKeyPhoneIDs = "," + m_strKeyPhoneID + ",", strRecordKeyPhoneID = "," + pRecord->m_strKeyPhoneID + ",";

				if(strKeyPhoneIDs.Find(strRecordKeyPhoneID) >= 0)
					m_call.Answer();
				else if(pRecord->m_nState == PH_RING)
					m_call.Redirect_Answer(pRecord->m_strKeyPhoneID);
				else 
					m_call.MakeCallingOrTransfer(pRecord->m_strKeyPhoneID);
			}
		}		
	}
}


void CRcpPageCTIForm::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
	{
		if(m_wndReport.GetColumns()->GetVisibleColumnsCount() == 0)
			PopupColumnSelect();

		return;
	}

	int nRow = pItemNotify->pRow->GetIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_wndReport.GetRows()->GetAt(nRow);
		CCallListRecord *pRecord = (CCallListRecord*)pRow->GetRecord();

		CPoint pt; 
		GetCursorPos(&pt);
		CString strPhone;
		strPhone.Format("전화걸기 (%s)", GetDashPhoneNumber(pRecord->m_strPhone));
		m_selected.strPhone = GetNoneDashNumber(pRecord->m_strPhone);
		m_selected.strKeyPhoneID = pRecord->m_strKeyPhoneID;
		m_selected.strDID = pRecord->m_strDID;
		m_selected.strCallingLine = pRecord->m_strCallingLine;

		CMenu *pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MAKE_CALL, strPhone);
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_POPUP_RCP_DLG, "접수창 팝업");
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_SEARCH_RCP_LIST, "메인리스트에서 검색");
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_SEARCH_RCP_LIST2, "고객의 마지막 접수오더 팝업");
		if(POWER_CHECK(1350, "진상고객수신거부"))
			pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_ADD_BLOCKING_NUMBER, "전화번호 자동차단 등록");
		pMenu->AppendMenu(MF_BYCOMMAND, ID_EXCEL, "엑셀변환");
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
	else
		PopupColumnSelect();
}

void CRcpPageCTIForm::OnOPReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_wndOPReport.GetRows()->GetAt(nRow);
		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();
		COPStateRecordItem *pItem = (COPStateRecordItem*)pRecord->GetItem(nCol);

		CPoint pt; 
		GetCursorPos(&pt);
		m_selected.strKeyPhoneID = pItem->pOPState->strKeyPhoneID;
		m_selected.strOperator = pItem->pOPState->strOperator;

		CMenu *pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MAKE_CALL_INNER_LINE, "내선 통화 연결");
		pMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_CHAT_MESSENGER, "메신저 대화");
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
}

void CRcpPageCTIForm::OnOPReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_wndOPReport.GetRows()->GetAt(nRow);
		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();
		COPStateRecordItem *pItem = (COPStateRecordItem*)pRecord->GetItem(nCol);
		if(pItem)
		{
			if(pItem->pOPState)
			{
				if(m_pOPPaintManagerEx)
				{
					CString strKeyPhoneIDs = "," + m_strKeyPhoneID + ",", strOPKeyPhoneID = "," + pItem->pOPState->strKeyPhoneID + ",";

					if(strKeyPhoneIDs.Find(strOPKeyPhoneID) >= 0)
						m_call.Answer();
				}
				else
					m_call.MakeCallingOrTransfer(pItem->pOPState->strKeyPhoneID);
			}
		}
	}
}

void CRcpPageCTIForm::AddPhoneCustomer(CString strPhone, CString strInfo, BOOL bLastRefresh)
{
	/*

	if(strCustomer.GetLength() < 2) return;

	PHONE_CUSTOMER_MAP::iterator it = m_mapPhoneCustomer.find(strPhone);
	if(it == m_mapPhoneCustomer.end())
	m_mapPhoneCustomer.insert(PHONE_CUSTOMER_MAP::value_type(strPhone, strCustomer));
	else if(strCustomer.GetLength() > 0)
	it->second = strCustomer;		
	*/
	//if(strInfo.GetLength() < 2) return;

	PHONE_CUSTOMER_STRUCT st;


	m_csPhoneCustomer.Lock();
	PHONE_CUSTOMER_MAP::iterator it = m_mapPhoneCustomer.find(strPhone);
	if(it == m_mapPhoneCustomer.end())
	{
		m_mapPhoneCustomer.insert(PHONE_CUSTOMER_MAP::value_type(strPhone, st));
		it = m_mapPhoneCustomer.find(strPhone);
	}
	m_csPhoneCustomer.Unlock();

	PHONE_CUSTOMER_STRUCT *stInfo = &it->second;

	//'<CUST_NAME='+ ISNULL(@sCName,'') + '><CUST_NUM=' + CAST(ISNULL(@nCustNumber,0) AS VARCHAR(10)) + '>
	//	<DEPART=' + ISNULL(@sDepart,'') + '><MANAGER=' + ISNULL(@sManager,'') + '>
	//	<DONG=>' + ISNULL(@sDong,'') + '>'

	//g_bana_log->Print("%s(%s) in AddPhoneCustomer\r\n", strPhone, strInfo);

	if(strInfo.GetLength() > 0)
	{
		CString strCName = ::GetValueByArg(strInfo, "CUST_NAME");

		if(strCName.IsEmpty())
			return;

		stInfo->strCName = ::GetValueByArg(strInfo, "CUST_NAME");
		stInfo->strID = ::GetValueByArg(strInfo, "CUST_NUM");
		stInfo->strID = stInfo->strID == "0" ? "" : stInfo->strID;
		stInfo->strDepart = ::GetValueByArg(strInfo, "DEPART");
		stInfo->strManager = ::GetValueByArg(strInfo, "MANAGER");
		stInfo->strDong = ::GetValueByArg(strInfo, "DONG");
		stInfo->strInfo = ::GetValueByArg(strInfo, "COUNT_INFO");
		stInfo->strDesc = ::GetValueByArg(strInfo, "DESC");

		if(stInfo->strInfo.IsEmpty() == FALSE)
			stInfo->strCName += " [" + stInfo->strInfo + "]";

		if(bLastRefresh)
		{
			for(int i=ZERO; i<TEN; i++) //상위10개에서 찾아서 정보를 바로 변경함
			{
				if(SetInfoToReport(strPhone, stInfo, i))
					break;
			}
		}
	}
}

BOOL CRcpPageCTIForm::SetInfoToReport(CString strPhone, PHONE_CUSTOMER_STRUCT *stInfo, long nRow)
{
	CXTPGridRows *pRows = m_wndReport.GetRows(); if(pRows == NULL) return TRUE; if(pRows->GetCount() == ZERO) return TRUE;
	CXTPGridRow *pRow = pRows->GetAt(nRow); if(pRow == NULL) return TRUE;
	CCallListRecord *pRecord = (CCallListRecord*)(pRow->GetRecord()); if(pRecord == NULL) return TRUE;

	if(pRecord->m_strPhone == strPhone)
	{
		pRecord->m_strCustomerName = stInfo->strCName;
		pRecord->m_strCustomerID = stInfo->strID;
		pRecord->m_strCustomerDepart = stInfo->strDepart;
		pRecord->m_strCustomerManager = stInfo->strManager;
		pRecord->m_strCustomerDong = stInfo->strDong;
		pRecord->m_strCustomerInfo = stInfo->strInfo;

		return TRUE;
	}

	return FALSE;
};

CString CRcpPageCTIForm::GetPhoneCustomer(CString strPhone)
{
	CMkLock lock(m_csPhoneCustomer);
	PHONE_CUSTOMER_MAP::iterator it = m_mapPhoneCustomer.find(strPhone);
	if(it != m_mapPhoneCustomer.end())
	{
		return it->second.strInfo;
	}
	return "";
}


BOOL CRcpPageCTIForm::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == m_wndReport.GetSafeHwnd())
	{
		if(pMsg->message == WM_LBUTTONDOWN ||
			pMsg->message == WM_RBUTTONDOWN ||
			pMsg->message == WM_NCLBUTTONDOWN ||
			pMsg->message == WM_LBUTTONUP ||
			pMsg->message == WM_RBUTTONUP ||
			pMsg->message == WM_NCLBUTTONUP ||
			pMsg->message == WM_MOUSEWHEEL ||
			pMsg->message == WM_MOUSEHOVER)
		{
			m_bMouseButtonDown = TRUE;
			//g_bana_log->Print("리스트컨트롤에 마우스 이벤트 발생: 갱신STOP\n");
			SetTimer(1, 5000, NULL);
		}
	}
	else if(pMsg->hwnd == m_wndOPReport.GetSafeHwnd())
	{
		if(pMsg->message == WM_MOUSEMOVE && m_pOPPaintManagerEx)
			m_tooltip.RelayEvent(pMsg);
	}

	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_F10)
		{
			if(GetKeyState(VK_CONTROL) & 0x8000)
			{
				CMkRecordset pRs(m_pMainDb);
				CMkCommand pCmd(m_pMainDb, "@select_telserver_auth");	
				pCmd.AddParameter(0);					
				if(pRs.Execute(&pCmd))
				{		
					CString strValue;
					if(pRs.GetRecordCount() > 0)
					{
						pRs.GetFieldValue("sSubValue", strValue);
					}
				}
			}
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_edtMakeCall.GetSafeHwnd())
			{
				OnBnClickedMakeCallUserBtn();
				return FALSE;
			}
		}
	}

	if(pMsg->message == WM_LBUTTONUP || pMsg->message == WM_RBUTTONUP ||
		pMsg->message == WM_NCLBUTTONUP || pMsg->message == WM_NCRBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE)
	{
		//by mksong (2010-12-12 오후 4:21) 
		//CRcpView의 pretranslate 안에서 부모의 pretranslate를 호출하면 에러발생함
		//TranslateAccelate를 호출하면 에러나지 않음

		if(m_pwndParent)
			m_pwndParent->PreTranslateMessage(pMsg);

		if(pMsg->message != WM_MOUSEMOVE)
		{
			m_bChangeCursor = FALSE; // 화면이동 변수들
			m_bMoveControl = FALSE;
			SetCursor(m_hcArrow);
			return FALSE;
		}
	}

	if(pMsg->message == WM_MOUSEMOVE)
	{
		CPoint point; ::GetCursorPos(&point);
		ScreenToClient(&point); 

		if(m_bMoveControl)
		{ // 커서 땜시 10 위로 
			SetCursor(m_hcVertical);  
			CRect rcPage;
			this->GetWindowRect(&rcPage);

			CRect rcReport, rcOPReport;   

			m_wndReport.GetWindowRect(&rcReport);
			m_wndOPReport.GetWindowRect(&rcOPReport);

			ScreenToClient(rcReport);
			ScreenToClient(rcOPReport);

			rcReport.right = point.x - 2; 
			rcOPReport.left = point.x + 2; 

			if(rcOPReport.Width() > m_nOPStateWidth + 15)  
			{
				m_wndReport.MoveWindow(rcReport);
				m_wndOPReport.MoveWindow(rcOPReport);

				MakeOPList();
			}		

		}
		else
		{

			CRect rcReport, rcOPReport;   

			m_wndReport.GetWindowRect(&rcReport);
			m_wndOPReport.GetWindowRect(&rcOPReport);

			ScreenToClient(rcReport);
			ScreenToClient(rcOPReport);

			if((rcReport.right < point.x) && (point.x < rcOPReport.left))
			{ 
				if((rcReport.top <= point.y) && (rcReport.bottom >= point.y)) 
					SetCursor(m_hcVertical);
				m_bChangeCursor = TRUE;
			}
			else
			{
				m_bChangeCursor = FALSE;
				SetCursor(m_hcArrow);
			}
		}

		return FALSE;
	}


	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(m_bChangeCursor)
		{
			m_bMoveControl = TRUE;
			SetCursor(m_hcVertical); 
			return FALSE;
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CRcpPageCTIForm::OnBnClickedSetupBtn()
{
	CCTIFormSetupDlg dlg;
	if(IDOK == dlg.DoModal())
	{
		if(LoadCTIInfo() || dlg.m_bReconnect)
			OnBnClickedConnectBtn();

		RefreshState();
	}
} 

void CRcpPageCTIForm::OnEnChangeSearchEdit()
{
	CString strPhone;
	m_edtSearch.GetWindowText(strPhone);

	ClearRecvCIDFilter();
	FilterList(strPhone, TRUE);
}

void CRcpPageCTIForm::FilterList(CString strPhone, BOOL bRedraw)
{
	static BOOL bPreVisibleAllState = TRUE;

	if(strPhone.GetLength() < 4 && bPreVisibleAllState)
	{
		if(bRedraw && !m_bMouseButtonDown)
			m_wndReport.Populate();
		return;
	}

	CString strText = strPhone;
	strPhone = GetNoneDashNumber(strPhone);
	m_strLastFilterPhone = strPhone;
	BOOL bVisibleAll = TRUE;

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();		
	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		CCallListRecord *pRecord = (CCallListRecord*)pRecords->GetAt(i);

		if(strPhone.GetLength() < 4)
			pRecord->SetVisible(TRUE);
		else 
		{
			if(pRecord->m_strPhone.Find(strPhone) >= 0 ||
				pRecord->m_strOperator.Find(strText) >= 0 ||
				pRecord->m_strCustomerName.Find(strText) >= 0)
				pRecord->SetVisible(TRUE);
			else
			{
				pRecord->SetVisible(FALSE);
				bVisibleAll = FALSE;
			}
		}
	}

	if(bRedraw && !m_bMouseButtonDown)
		m_wndReport.Populate();

	bPreVisibleAllState = bVisibleAll;
}

void CRcpPageCTIForm::SearchRecvCID(CString strPhone)
{
	if(!m_bAutoBlocking)
	{
		m_strRecvCID = strPhone;
		m_edtSearch.SetTitle(GetDashPhoneNumber(strPhone));
		FilterList(strPhone, TRUE);
	}
}

void CRcpPageCTIForm::ClearRecvCIDFilter()
{
	if(m_strRecvCID.GetLength() > 0)
	{
		m_edtSearch.SetTitle("");
		m_strRecvCID = "";
		FilterList("", TRUE);
	}
}

void CRcpPageCTIForm::OnEnSetfocusSearchEdit()
{
	ClearRecvCIDFilter();
}

void CRcpPageCTIForm::PopupRcpDlg(const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID)
{
	if(!m_bAutoBlocking)
	{
		char *pszData = new CHAR[1000];
		STRCPY(pszData, "A", "-1", szPhoneNumber, szKeyPhoneID, szDID, VL_END);
		m_pMainFrame->PostMessage(WM_RECV_CID, (WPARAM)pszData, 0);

		//m_pMainFrame->PostMessage(WM_RECV_CID, (WPARAM)pszData, 0);
		/*
		#ifdef _SYSMANAGER	
		((CMainFrame*)AfxGetMainWnd())->SendCIDInfo(szData);
		#else
		LU->SendCIDInfo(szData);
		#endif
		*/
	}
}

void CRcpPageCTIForm::OnBnClickedRefreshStopCheck()
{
	m_dwRefreshStop = GetTickCount() + 1000000;
	if(!m_chkRefreshStop.GetCheck())
		m_wndReport.Populate();
}

BOOL CRcpPageCTIForm::RefreshOK(BOOL bFromSearch)
{
	return !m_bMouseButtonDown && !m_chkRefreshStop.GetCheck() && 
		(m_edtSearch.GetWindowTextLength() == 0 || bFromSearch);
}

BOOL CRcpPageCTIForm::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CMyFormView::PreCreateWindow(cs);
}

void CRcpPageCTIForm::DisplayRingInfo(long nRing, long nAnswer, long nMissingCallCount, long nMissingCallPerMin)
{
	static DWORD dwTickCount = 0;
	const char szTemp[] =  
		"<TextBlock FontFamily='Tahoma' HorizontalAlignment='Center' VerticalAlignment='Center'>" \
		"<Run Foreground='#0000FF' FontWeight='Bold'>링%d</Run>" \
		"<Run Foreground='Green' FontWeight='Bold'>/ 통화%d</Run>" \
		"<Run Foreground='Black' FontWeight='Bold'>/ 끊김%d</Run>" \
		"<Run Foreground='Red' FontWeight='Bold'>/ 1분간끊김%d</Run>"\
		"</TextBlock>";

	CString strTemp = "";
	strTemp.Format(szTemp, nRing, nAnswer, nMissingCallCount, nMissingCallPerMin); 

#ifdef _DAERI
	if(!POWER_CHECK(2007, "카운트 표시"))
		strTemp = "";
#endif

	//CMarkupStatic이 쓰레드 Safe하지 않아, 방식 변경함 by mksong (2010-10-06 오후 4:56)
	CMkLock lock(&m_csRinginfo);
	if(m_nRingCount == 0)
		m_dwRingInfoTick = GetTickCount();
	m_nRingCount = nRing;
	m_strRingInfo = strTemp;
}

void CRcpPageCTIForm::CheckAutoTransfer()
{
	if(m_bAutoTransfer &&
		(m_strAutoTransfer.GetLength() > 0 || m_strAutoTransfer2.GetLength() > 0) && 
		!AmIbusy() &&
		GetTickCount() - m_dwLastAutoTransferTick > 5000)
	{
		CString strAT1 = m_strAutoTransfer;
		CString strAT2 = m_strAutoTransfer2;

		if(strAT1.IsEmpty())
			strAT1 = "^%^&*&^%$#$%^&*";

		if(strAT2.IsEmpty())
			strAT2 = "^%^&*&^%$#$%^&*";

		for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
		{
			CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);

			if(pRecord == m_pLastAutoTransferRecord)
				continue;

			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - pRecord->m_dtFirstTime;

			if(pRecord->m_nState == PH_RING && span.GetTotalSeconds() >= 2 || 
				pRecord->m_nState == PH_ARS_ANSWER)
			{
				CXTPGridColumn *pColumn = NULL;

				//Why? pRecord->m_strCustomer 값이 없는 것일까?
				CString strInfo = ((CXTPGridRecordItemText*)pRecord->GetItem(COL_CUSTOMER_INFO))->GetCaption(pColumn);

				if(pRecord->m_strPhone.Find(strAT1) >= 0 ||
					strInfo.Find(strAT1) >= 0 ||
					pRecord->m_strPhone.Find(strAT2) >= 0 ||
					strInfo.Find(strAT2) >= 0)
				{
					CString strFormat;
					m_call.MakeCallingOrTransfer(pRecord->m_strKeyPhoneID);
					strFormat.Format("잠시후에 자동착신 전환되어, 전화가 들어옵니다.\n"\
						"키워드[%s,%s]\n전화번호[%s]\n정보[%s]",
						m_strAutoTransfer, m_strAutoTransfer2, 
						pRecord->m_strPhone, strInfo);
					m_pLastAutoTransferRecord = pRecord;
					m_dwLastAutoTransferTick = GetTickCount();
					MessageBox(strFormat, "자동착신", MB_ICONINFORMATION);
					break;
				}
			}
		}
	}
}

BOOL CRcpPageCTIForm::AmIbusy()
{
	OP_STATE_MAP::iterator it = GetOPStateMap()->find(m_strKeyPhoneID);
	if(it != GetOPStateMap()->end())
		if(it->second->nState != PH_HANG_UP)
			return TRUE;

	return FALSE;
}

void CRcpPageCTIForm::MakeCall(int nCompany, CString strPhone, CString strCallingLine, CString strDID)
{
	if(strPhone.GetLength() > 1)
	{
		CString strPhone1 = ::GetNoneDashNumber(strPhone), strOriginNumber;
		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		strOriginNumber = strPhone1;
		if(strOriginNumber.GetLength() > 20)
		{
			MessageBox("발신 전화번호가 20자가 넘습니다. 확인해주세요.", "확인", MB_ICONINFORMATION);
			return;
		}
		else if(strPhone1.GetLength() > 4)
		{
			if(m_bIPPBX)
			{
				if(strDID.IsEmpty())
				{
					strDID = GetBranchInfo(nCompany)->strLineGroup;
					if(strDID.Find(",") != -1)
						strDID = strDID.Mid(strDID.Find(",") + 1, strDID.Find(",", strDID.Find(",") + 1) - strDID.Find(",") - 1);
				}
				else if(strDID.Find(",") != -1)
					strDID = strDID.Mid(strDID.Find(",") + 1, strDID.Find(",", strDID.Find(",") + 1) - strDID.Find(",") - 1);

				strDID = strDID + "OP" + strOriginNumber;
			}

			strCallingLine = ::GetAutoDDDSetting(nCompany, strCallingLine);
			if(strCallingLine.Find("A") != -1 && strPhone1.Find("0") != 0)
			{
				//strPhone1 = GetBranchInfo(nCompany)->strDDD + strPhone1;
				strPhone1 = m_ci.m_strDDD + strPhone1;
				strOriginNumber = strPhone1;
			}

			strPhone1 = strCallingLine + strPhone1;
		}
		m_call.HangUp();
		m_call.MakeCall(strDID, strPhone1);
		if(LU->GetRcpView())
			LU->GetRcpView()->SaveCallingLog(strPhone, CALL_TO_CUSTOMER);
	}
}

void CRcpPageCTIForm::OnBnClickedMakeCallUserBtn()
{
	CString strPhone;
	m_edtMakeCall.GetWindowText(strPhone);
	//MakeCallUseHotNumber(strPhone);
	MakeCall(m_pBiCID->nCompanyCode, strPhone, m_pBiCID->strCallingLine, m_pBiCID->strLineGroup);
}

void CRcpPageCTIForm::GetPreCallInfoLog(BOOL bCallFromInit)
{
	static int nProgressCount = 0;

	if(!m_pLogDb)
	{
		m_pLogDb = new CMkDatabase(g_bana_log);


		BYTE nXorKey = (m_pLogDb->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8]; 

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pLogDb->SetServerKey(nXoredKey); 

		//m_pLogDb->AddDisServer("211.172.242.179",3500);
		//m_pLogDb->AddDisServer("211.172.242.180",3500);
		//m_pLogDb->AddDisServer("121.254.252.6",3500);
		//m_pLogDb->AddDisServer("121.254.252.26",3500);

		//if(!m_pLogDb->Open("211.172.242.189", 3500, TRUE))
		if(!m_pLogDb->Open(m_si.strRealMainServerAddr, 3500, TRUE))
		{
			g_bana_log->Print("telserver DB 접속 실패\n");
			DELETE_OBJECT(m_pLogDb);
			return;
		}
	}

	if(bCallFromInit)
	{
		RefreshState("이전 내역을 가져오는 중..");
	}
	else
	{
		if(!RefreshOK())
			return;

		CString strProgressText = "갱신중";
		nProgressCount++;
		for(int i = 0; i < (nProgressCount % 4); i++)
			strProgressText += "▶";
		RefreshState(strProgressText);
	}

	CMkRecordset pRs(m_pLogDb);
	CMkCommand pCmd(m_pLogDb, "select_telserver_call_info_log2");	
	//pCmd.AddParameter(m_ci.m_nCompanyCode < 1000 && m_ui.bBlankPassword ? 200 : m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	//pCmd.AddParameter(m_ci.m_nCompanyCode);
	CMkParameter *pParRefresh = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), m_dtLastRefresh);

	g_bana_log->Print("telserver DB 접속 종료함  %d, %s \n", m_ci.m_nCompanyCode < 1000 && m_ui.bBlankPassword ? 200 : m_ci.m_nCompanyCode, m_dtLastRefresh.Format("yyyy-MM-dd tth:mm:ss"));

	if(pRs.Execute(&pCmd))
	{		
		long nSubType;
		CString strPhoneNumber, strKeyPhoneID, strDID;
		CString strOperator, strCustomer, strLastOperator;
		COleDateTime dtLastEdit;

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("nSubType", nSubType);
			pRs.GetFieldValue("sPhoneNumber", strPhoneNumber);
			pRs.GetFieldValue("sCurKeyPhoneID", strKeyPhoneID);
			pRs.GetFieldValue("sExtLineID", strDID);
			pRs.GetFieldValue("sOperator", strOperator);
			pRs.GetFieldValue("sCustomer", strCustomer);
			pRs.GetFieldValue("sLastOperator", strLastOperator);
			pRs.GetFieldValue("dtLastEdit", dtLastEdit);

			m_call.CallInfoLog(nSubType, (LPSTR)(LPCTSTR)strPhoneNumber, 
				(LPSTR)(LPCTSTR)strKeyPhoneID, 
				(LPSTR)(LPCTSTR)strDID, 
				(LPSTR)(LPCTSTR)strOperator, 
				(LPSTR)(LPCTSTR)strCustomer, 
				(LPSTR)(LPCTSTR)strLastOperator,
				dtLastEdit,
				FALSE);

			pRs.MoveNext();
		}

		if(pRs.GetRecordCount() > 0 && !m_bMouseButtonDown)
		{
			EnsureVisibleFirstRow();
			m_wndReport.Populate();
			m_wndOPReport.Populate();
		}

		m_dtLastRefresh = pParRefresh->GetDate();
	}

	if(!m_bEnableDBRefresh)
	{
		if(m_pMkDb != m_pLogDb)
			DELETE_OBJECT(m_pLogDb)
			g_bana_log->Print("telserver DB 접속 종료함\n");
		RefreshState("");
	}

	if(bCallFromInit)
		AutoHangUp();
}

void CRcpPageCTIForm::AddLastAnswerOP(CString strPhoneNumber, CString strOperator, COleDateTime dtCur)
{
	m_mapLastAnswerOP[strPhoneNumber] = make_pair(strOperator, dtCur);
}

CString CRcpPageCTIForm::GetLastAnswerOP(CString strPhoneNumber, COleDateTime dtCur)
{
	LAST_ANSWER_OP_MAP::iterator it;
	it = m_mapLastAnswerOP.find(strPhoneNumber);

	if(it != m_mapLastAnswerOP.end())
	{
		CString strTemp;
		COleDateTimeSpan span = dtCur - it->second.second;
		strTemp.Format("%s-%0.0f", it->second.first,  span.GetTotalMinutes());
		return strTemp;
	}

	return "";
}

void CRcpPageCTIForm::CheckAutoBlocking()
{	
	if(m_bAutoBlocking)
	{
		if(!m_bAutoBlockingThreadAlive)
		{
			m_bAutoBlockingThreadAlive = TRUE;
			DWORD dwThreadID1;
			HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticAutoBlockingProc, 
				(LPVOID) this, 0, &dwThreadID1);
			CloseHandle(hThread1);
		}

		//g_bana_log->Print("자동 차단 실행중\n");

		if(m_lstBlocking.GetCount() > 0)
			return;

		CXTPGridRecord *pRecord = NULL;
		OP_STATE_MAP::iterator it;
		long nOnlineCount = 0;
		long nBusyCount = 0;

		for(it = GetOPStateMap()->begin(); it != GetOPStateMap()->end(); it++)
		{
			if(it->second->nState == PH_ANSWER || it->second->nState == PH_OUT_BOUND_CALL)
				nOnlineCount++;
			else if(it->second->nState == PH_RING || it->second->nState == PH_ARS_ANSWER)
				nBusyCount++;
		}

		if((nOnlineCount + nBusyCount) >= 8 ||
			(nOnlineCount >= 5 && nBusyCount >= 2) ||
			nBusyCount >= 4)
		{
			for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
			{
				CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);
				COleDateTimeSpan span = COleDateTime::GetCurrentTime() - pRecord->m_dtFirstTime;

				if(pRecord->m_nState == PH_ARS_ANSWER &&
					span.GetTotalSeconds() >= 5 && 
					span.GetTotalSeconds() < 300)
				{
					CXTPGridColumn *pColumn = NULL;
					CString strInfo = ((CXTPGridRecordItemText*)pRecord->GetItem(COL_CUSTOMER_INFO))->GetCaption(pColumn);

					if(strInfo.GetLength() == 0 || strInfo.Find("ㄱ") == 0)
					{
						g_bana_log->Print("전화차단요청: %s(%s), %s", pRecord->m_strDID, pRecord->m_strKeyPhoneID, strInfo);
						m_lstBlocking.AddTail(pRecord->m_strKeyPhoneID);
						SetEvent(m_hAutoBlockingHandle);
					}
				}
			}
		}
	}
}

UINT CRcpPageCTIForm::AutoBlockingProc(LPVOID lParam)
{
	HANDLE hWaitObject[2];
	hWaitObject[0] = m_hAutoBlockingHandle;
	hWaitObject[1] = m_hExitHandle;

	m_bAutoBlockingThreadAlive = TRUE;

	while(m_bAutoBlocking)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(2, hWaitObject, FALSE, 1000);

		if(AmIbusy())
		{
			g_bana_log->Print("전화차단완료\n");
			m_call.HangUp(m_strKeyPhoneID);
		}

		if(dwWaitResult == WAIT_OBJECT_0)
		{
			while(m_lstBlocking.GetCount() > 0)
			{
				CString strKeyPhoneID = m_lstBlocking.RemoveHead();
				g_bana_log->Print("전화차단 유도중(%s)\n", strKeyPhoneID);
				m_call.Redirect_Answer(strKeyPhoneID);
				Sleep(100);
				m_call.HangUp();
			}
		}
		else if(dwWaitResult == WAIT_OBJECT_0 + 1)
		{
			break;
		}
	}

	SetEvent(m_hThreadDiedHandle);
	m_bAutoBlockingThreadAlive = FALSE;
	return 0;
}

void CRcpPageCTIForm::OnBnClickedMakeCallHotKeyBtn()
{
	CPoint pt; 
	GetCursorPos(&pt);
	OnContextMenu(&m_btnMakeCallHotKey, pt);
}

void CRcpPageCTIForm::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(pWnd->m_hWnd == m_btnMakeCallHotKey.GetSafeHwnd())
	{
		CMenu *pMainMenu = new CMenu;
		CMenu *pMenu = NULL;

		pMainMenu->CreatePopupMenu();
		pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_HOT_NUMBER_LOGISOFT, "로지소프트 (1599-0707)");
		pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_HOT_NUMBER_ADD, "메모리 추가");

		//CMenu *pRMenu = (CMenu*)rMenu.GetSubMenu(0);
		//pRMenu->SetMenuDrawMode(TRUE);

		CMkRecordset pRs(m_pMainDb);
		CMkCommand pCmd(m_pMainDb, "select_call_hot_number");	
		pCmd.AddParameter(m_ci.m_nCompanyCode);					
		if(pRs.Execute(&pCmd))
		{		
			CString strPhone, strName;
			CString strMenuText;
			m_saHotNumberList.RemoveAll();

			pMenu = new CMenu;
			pMenu->CreatePopupMenu();
			//pRMenu->SetMenuDrawMode(TRUE);
			pMainMenu->InsertMenu(2, MF_BYPOSITION | MF_POPUP, (UINT)pMenu->m_hMenu, "메모리 삭제");
			pMainMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				pRs.GetFieldValue("sPhone", strPhone);
				pRs.GetFieldValue("sName", strName);

				strMenuText.Format("%s (%s)", strName, GetDashPhoneNumber(strPhone));
				m_saHotNumberList.Add(GetNoneDashNumber(strPhone));

				UINT nID = ID_MENU_HOT_NUMBER + i;
				pMainMenu->AppendMenu(MF_BYCOMMAND, nID, strMenuText);
				pMenu->AppendMenu(MF_BYCOMMAND, nID + 1000, strMenuText);

				pRs.MoveNext();
			}
		}

		pMainMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

		DELETE_OBJECT(pMainMenu);
		DELETE_OBJECT(pMenu);
	}
}

void CRcpPageCTIForm::OnMenuHotNumber(UINT nID)
{
	if(nID == ID_MENU_HOT_NUMBER_ADD)
	{
		CREATE_MODALESS(CAddCallHotNumberDlg, this);
		pDlg->m_pMyDb = m_pMainDb;
		SHOW_MODALESS(CAddCallHotNumberDlg, this);
	}
	else if(nID == ID_MENU_HOT_NUMBER_LOGISOFT)
	{
		MakeCall(m_ui.nCompany, "15990707");
	}
	else if(nID >= ID_MENU_HOT_NUMBER && nID < ID_MENU_HOT_NUMBER + 1000)
	{
		long nOffset = nID - ID_MENU_HOT_NUMBER;
		if(nOffset  < m_saHotNumberList.GetCount())
		{
			MakeCall(m_ui.nCompany, m_saHotNumberList.GetAt(nOffset));
		}
	}
	else if(nID >= ID_MENU_HOT_NUMBER + 1000)
	{
		long nOffset = nID - ID_MENU_HOT_NUMBER - 1000;
		if(nOffset < m_saHotNumberList.GetCount())
		{
			CString strPhone = m_saHotNumberList.GetAt(nOffset);
			if(IDYES == MessageBox(strPhone + " 번을 삭제 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
			{
				CMkCommand pCmd(m_pMainDb, "delete_call_hot_number");
				pCmd.AddParameter(m_ci.m_nCompanyCode);
				pCmd.AddParameter(m_saHotNumberList.GetAt(nOffset));
				if(pCmd.Execute())
				{
					MessageBox("삭제되었습니다.", "확인", MB_ICONINFORMATION);
					OnBnClickedMakeCallHotKeyBtn();
				}
			}
		}
	}
}

void CRcpPageCTIForm::OnMenuCallList(UINT nID)
{
	if(nID == ID_MENU_MAKE_CALL)
	{
		MakeCall(m_ui.nCompany, m_selected.strPhone, m_selected.strCallingLine, m_selected.strDID);
	}
	else if(nID == ID_MENU_POPUP_RCP_DLG)
	{
		PopupRcpDlg(m_selected.strPhone, m_selected.strKeyPhoneID, m_selected.strDID);
	}
	else if(nID == ID_MENU_SEARCH_RCP_LIST)
	{
#ifdef _SYSMANAGER
		((CRcpPage*)m_pwndParent)->FindCustomerFromPhone(m_selected.strPhone);
#else
		((CRcpView*)m_pwndParent)->FindCustomerFromPhone(m_selected.strPhone, m_selected.strDID);
#endif
	}
	else if(nID == ID_MENU_SEARCH_RCP_LIST2)
	{
#ifdef _SYSMANAGER
		((CRcpPage*)m_pwndParent)->FindCustomerFromPhone(m_selected.strPhone, TRUE);
#else
		((CRcpView*)m_pwndParent)->FindCustomerFromPhone(m_selected.strPhone, m_selected.strDID, TRUE);
#endif
	}
	else if(nID == ID_MENU_ADD_BLOCKING_NUMBER)
	{
		AddBlockingPhone(m_selected.strPhone);
	}
}

void CRcpPageCTIForm::OnMenuOPList(UINT nID)
{
	if(nID == ID_MENU_MAKE_CALL_INNER_LINE)
	{
		m_call.MakeCallingOrTransfer(m_selected.strKeyPhoneID);
	}
	else if(nID == ID_MENU_CHAT_MESSENGER)
	{
		MessageBox("준비중입니다.", "확인", MB_ICONINFORMATION);
	}
}

void CRcpPageCTIForm::RefreshState(CString strMsg)
{
	//CMkLock lock(m_csState);

	CString strInfo;

	strInfo = m_bConnected ? "접속중" : "연결안됨";

	if(strMsg.GetLength() > 0)
	{
		strInfo += "-" + strMsg;
	}
	else
	{
		if(m_bAutoBlocking)
			strInfo += "-차단중";

		if(m_bAutoTransfer)
			strInfo += "-착신중(" + m_strAutoTransfer  + "," + m_strAutoTransfer2 + ")";
	}

	m_edtState.SetUserOption(RGB(0, 0, 0), m_bConnected ? RGB(255, 255, 200) : RGB(255, 200, 200), strInfo, FALSE, TRUE);
	RefreshQueueState();
}

void CRcpPageCTIForm::RefreshQueueState()
{
	CString strInfo;
	int nLineMode = m_call.GetQueuePause();

	if (m_bConnected == FALSE)
	{
		strInfo = "연결안됨";
		m_edtQueueState.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 200), strInfo, FALSE, TRUE);
	}
	else if (m_bConnected && nLineMode == LINE_RECV_MODE)
	{
		strInfo = "수신가능";
		m_edtQueueState.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 200), strInfo, FALSE, TRUE);
	}
	else if (m_bConnected && nLineMode == LINE_PAUSE_MODE)
	{
		strInfo = "휴식모드";
		m_edtQueueState.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 255), strInfo, FALSE, TRUE);
	}
	else if (m_bConnected && nLineMode == LINE_UNUSE_MODE)
	{
		strInfo = "해당안됨";
		m_edtQueueState.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 200), strInfo, FALSE, TRUE);
	}
	else if (m_bConnected && nLineMode == LINE_WORKING_MODE)
	{
		strInfo = "작업중";
		m_edtQueueState.SetUserOption(RGB(0, 0, 0), RGB(200, 200, 255), strInfo, FALSE, TRUE);
	}
}

void CRcpPageCTIForm::AddBlockingPhone(CString strPhone)
{
	CJinsangTelRegDlg dlg;
	dlg.m_nDuration  = 3650;
	dlg.m_sTelNumber = strPhone;

	if(IDOK == dlg.DoModal())
	{
		CString szDenialDuration;
		szDenialDuration.Format("%d",dlg.m_nDuration*24*60);

		m_call.DenialAnswer(dlg.m_sTelNumber, atol(szDenialDuration), dlg.m_sName, dlg.m_sDesc);
		MessageBox("해당 전화번호로 전화가 오면 통화가 자동 차단됩니다.", 
			"전화번호 자동차단", 
			MB_ICONINFORMATION);
	}

}

void CRcpPageCTIForm::RefreshRingInfo()
{
	CMkLock lock(m_csRinginfo);

	static CString strRingInfo;
	if(strRingInfo != m_strRingInfo)
	{
		m_stcRingInfo.SetMarkupText(m_strRingInfo);
		strRingInfo = m_strRingInfo;	
	}
}

void CRcpPageCTIForm::AutoHangUp()
{
	if(m_ci.m_nAutoHangupElapsedMin == 0)
		return;

	for(int i = m_wndReport.GetRecords()->GetCount() - 1; i >= 0; i--)
	{
		CCallListRecord *pRecord = (CCallListRecord*)m_wndReport.GetRecords()->GetAt(i);
		if(pRecord->m_nState == PH_ANSWER)
		{
			COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - pRecord->m_dtAnswer;
			if(dtSpan.GetTotalMinutes() >= m_ci.m_nAutoHangupElapsedMin)
			{
				pRecord->m_nState = PH_HANG_UP;
				pRecord->m_dtLastTime = COleDateTime::GetCurrentTime();
				pRecord->m_strEtc = "자동끊기";
			}
		}
	}
}

void CRcpPageCTIForm::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CString strTemp; long nSize;
	SaveReportState(strTemp, nSize);
}

BOOL CRcpPageCTIForm::OnSaveReportState()
{
	CString strRcpList; long nSize;
	SaveReportState(strRcpList, nSize);

	CMkCommand cmd(m_pMkDb, "update_rcp_list");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(strRcpList);
	cmd.AddParameter(nSize);
	cmd.AddParameter(1);

	if(cmd.Execute())
		return 1;

	return 1;
}

BOOL CRcpPageCTIForm::OnLoadReportState()
{

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_list");
	cmd.AddParameter(m_ui.nCompany); 
	cmd.AddParameter(1);

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
		pData[nItem++] = HexStrToInt(strTemp);
	}

	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), _T("CTI"), pData, nSize);
	LoadReportState();

	return 1;
}

void CRcpPageCTIForm::SaveReportState(CString &strSave, long &nSize)
{
	if(m_bColumnInsert == FALSE)
		return;

	CMemFile memFile;
	CArchive ar (&memFile,CArchive::store);

	m_wndReport.SerializeState(ar);

	ar.Flush();

	DWORD nBytes = (DWORD)memFile.GetPosition();
	LPBYTE pData = memFile.Detach();

	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), _T("CTI"), pData, nBytes);

	char szData[10000];
	for(int i = 0; i < (int)nBytes; i++) 
		sprintf(&szData[i * 2], "%02X", (BYTE)pData[i]);

	CString strTemp(szData);

	strSave = strTemp;
	nSize = nBytes;

	ar.Close();
	memFile.Close();
	free(pData);

	/*
	CString sNewOrder = "";
	CString sNewOrderWidth = "";
	CString sNewOrderVisible = "";
	char buffer[20];

	for(int i=0; i<m_wndReport.GetColumns()->GetCount(); i++)
	{
		long nIndex  = m_wndReport.GetColumns()->GetAt(i)->GetItemIndex();
		sNewOrder += CString(itoa(nIndex, buffer, 10)) + ",";

		long nWidth = m_wndReport.GetColumns()->GetAt(i)->GetWidth();
		sNewOrderWidth += CString(itoa(nWidth, buffer, 10)) + ",";	

		long bVisible = m_wndReport.GetColumns()->GetAt(i)->IsVisible();
		sNewOrderVisible += CString(itoa(bVisible, buffer, 10)) + ",";	
	}

	AfxGetApp()->WriteProfileString("CRcpPageCTIForm", "m_wndReport", sNewOrder);
	AfxGetApp()->WriteProfileString("CRcpPageCTIForm", "m_wndReportA", sNewOrderWidth);
	AfxGetApp()->WriteProfileString("CRcpPageCTIForm", "m_wndReportB", sNewOrderVisible);
	AfxGetApp()->WriteProfileInt("CRcpPageCTIForm", "m_wndReportFirst", 0);
	*/
}

void CRcpPageCTIForm::LoadReportState()
{
	UINT nBytes = 0;
	LPBYTE pData = 0;

	if (!AfxGetApp()->GetProfileBinary(_T("ReportControl"), _T("CTI"), &pData, &nBytes))
		return;

	CMemFile memFile(pData, nBytes);
	CArchive ar (&memFile,CArchive::load);

	try
	{
		m_wndReport.SerializeState(ar);

	}
	catch (COleException* pEx)
	{
		pEx->Delete ();
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
	}

	ar.Close();
	memFile.Close();
	delete[] pData;
}

BOOL CRcpPageCTIForm::SetRecordData(CCallListRecord *pRecord, CString szPhoneNumber)
{
	CMkLock lock(m_csPhoneCustomer);
	PHONE_CUSTOMER_MAP::iterator it = m_mapPhoneCustomer.find(szPhoneNumber); //choi test
	if(it != m_mapPhoneCustomer.end())
	{
		pRecord->m_strCustomerName = it->second.strCName;
		pRecord->m_strCustomerID = it->second.strID;
		pRecord->m_strCustomerID = pRecord->m_strCustomerID == "0" ? "" : pRecord->m_strCustomerID;
		pRecord->m_strCustomerDepart = it->second.strDepart;
		pRecord->m_strCustomerManager = it->second.strManager;
		pRecord->m_strCustomerDong = it->second.strDong;
		pRecord->m_strCustomerInfo = it->second.strInfo;
		return TRUE;
	}

	return FALSE;
};

void CRcpPageCTIForm::OnViewExcel()
{
	if(!POWER_CHECK(1511, "콜리스트 엑셀변환", TRUE))
		return;

	CMyExcel::ToExcel(&m_wndReport);
}	

void CRcpPageCTIForm::OnBnClickedQueuePausedBtn()
{
	int nLineMode = m_call.GetQueuePause();

	if (nLineMode == LINE_RECV_MODE || nLineMode == LINE_WORKING_MODE)
		nLineMode = LINE_PAUSE_MODE;
	else if (nLineMode == LINE_PAUSE_MODE)
		nLineMode = LINE_RECV_MODE;
	else
		return;

	m_call.SetClientQueuePause(nLineMode);
}

UINT WINAPI CRcpPageCTIForm::_ThreadQueueRecvMode(LPVOID pParam)
{
	ASSERT(pParam);
	CRcpPageCTIForm *pForm = reinterpret_cast<CRcpPageCTIForm *> (pParam);

	pForm->ThreadQueueRecvMode();

	CloseHandle(pForm->m_threadHandle); 
	pForm->m_threadHandle = 0;
	return 0;
}


void CRcpPageCTIForm::ThreadQueueRecvMode()
{
	Sleep(m_nRcpPopupSecond * 1000);
	if (m_bThreadQueue == FALSE)
	{
		if (m_call.GetQueuePause() == LINE_WORKING_MODE)
		{
			m_call.SetClientQueuePause(LINE_RECV_MODE);
		}		
	}
}

void CRcpPageCTIForm::QueueRecvModeSecond()
{
	if (m_bQueueRcpPopup == TRUE)
	{
		int nLineMode = m_call.GetQueuePause();
		if (nLineMode == LINE_WORKING_MODE)
		{
			unsigned int nDummy;
			m_threadHandle = (HANDLE) _beginthreadex(NULL,0,_ThreadQueueRecvMode,this,
				CREATE_SUSPENDED,&nDummy);
			if (m_threadHandle)
			{
				m_bThreadQueue = FALSE;
				ResumeThread(m_threadHandle);
			} 
		}
	}	
}

void CRcpPageCTIForm::QueueWorkingMode()
{
	if (m_bQueueRcpPopup == TRUE)
	{
		int nLineMode = m_call.GetQueuePause();
		if (nLineMode == LINE_RECV_MODE)
		{
			m_call.SetClientQueuePause(LINE_WORKING_MODE);
		}
		else if (nLineMode == LINE_WORKING_MODE)
			m_bThreadQueue = TRUE;	
	}
}


void CRcpPageCTIForm::AddRecordFileNameInsertID(CString strKeyPhoneID, CString strPhoneNumber, int nInsertID)
{
	m_mapRecordFileID.insert(RECORDFILENAME_INSERTID_MAP::value_type(strPhoneNumber, nInsertID));
}

long CRcpPageCTIForm::GetRecordFileNameInsertID(CString strPhoneNumber)
{
	CString strNumber = GetNoneDashNumber(strPhoneNumber);
	RECORDFILENAME_INSERTID_MAP::iterator it = m_mapRecordFileID.find(strNumber);
	if(it != m_mapRecordFileID.end())
	{
		long nInsertID = it->second;
		m_mapRecordFileID.erase(it);

		return nInsertID;
	}

	return -1;
}

void CRcpPageCTIForm::RemoveRecordFileNameInsertID(CString strPhoneNumber)
{
	CString strTemp = strPhoneNumber;
	strTemp.Remove('-');
	m_mapRecordFileID.erase(strTemp);
}

void CRcpPageCTIForm::OnBnClickedCIDBtn()
{
	CCIDSelectDlg dlg;
	dlg.DoModal();
}

void CRcpPageCTIForm::SelectCID(CBranchInfo *pBi)
{
	m_pBiCID = pBi;

	WCHAR wChar[255] = {0,};
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_pBiCID->strBranchName, -1, wChar, 255);
	int nWLen = wcslen(wChar);

	char szData[255] = {0,}, szRet[255] = {0,}, szTemp = {0};
	int nLen = WideCharToMultiByte(CP_ACP, 0, wChar, nWLen, szData, 255, NULL, NULL), nRetIndex = 0;

	for(int i = 0; i < nLen; i++)
	{
		szTemp = szData[i];

		if(szTemp < 0x00 && i < 9)
		{
			szRet[nRetIndex++] = szTemp;
			szRet[nRetIndex++] = szData[++i];
		}
		else if(i < 9)
			szRet[nRetIndex++] = szTemp;
		else
			break;
	}

	CString strBranchName = szRet;
	m_btnCIDNumber.SetWindowText(strBranchName + "▷");
}

OP_STATE_MAP* CRcpPageCTIForm::GetOPStateMap()
{
	if(m_pOPPaintManager)
		return &(m_pOPPaintManager->m_mapOPState);
	else
		return &(m_pOPPaintManagerEx->m_mapOPState);
}

void CRcpPageCTIForm::AddOpRecord(CString strTemp, CXTPGridRecord *pRecord, OP_STATE_INFO *pInfo)
{
	if(m_pOPPaintManager)
	{
		COPStateRecordItem *pRecordItem = new COPStateRecordItem(strTemp);
		pRecordItem->pOPState = pInfo;
		pRecord->AddItem(pRecordItem);
	}
	else
	{
		COPStateRecordItemEx *pRecordItem = new COPStateRecordItemEx(strTemp);
		pRecordItem->pOPState = pInfo;
		pRecord->AddItem(pRecordItem);
	}
}

void CRcpPageCTIForm::OnOpReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	if(m_pOPPaintManager)
		return;

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_wndOPReport.GetRows()->GetAt(nRow);
		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();
		COPStateRecordItemEx *pItem = (COPStateRecordItemEx*)pRecord->GetItem(nCol);

		CPoint pt;
		GetCursorPos(&pt);
		m_wndOPReport.ScreenToClient(&pt);

		OpReportItemClickEvent(pItem->OnImageClickedCall(pt), pItem->pOPState->strKeyPhoneID);
	}
}

void CRcpPageCTIForm::OpReportItemClickEvent(int nEventType, CString strKeyPhoneID)
{
	if(m_strKeyPhoneID.Find(strKeyPhoneID) == 0)
		return;

	if(nEventType == MAKE_CALL)
		m_call.MakeCall("", strKeyPhoneID);
	else if(nEventType == TRANSFER_CALL)
		m_call.OpTransferCall(strKeyPhoneID);
	else if(nEventType == PICKUP_CALL)
		m_call.OpPickUpCall(strKeyPhoneID);
}

void CRcpPageCTIForm::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	return; //choe
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{

	}
	else
	{
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();

		CPoint pt = *pNotify->pt;
		CRect rcCtrl, rcCol;
		if (IDC_OP_REPORT_CONTROL == nID)
		{
			m_wndOPReport.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_wndOPReport.HitTest(pt);

			if(pRow)
			{
				CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);
				if(pCol)
				{
					COPStateRecordItemEx *pItem = (COPStateRecordItemEx*)pRecord->GetItem(pCol);
					if(pItem)
					{
						CString strToolTip = pItem->OnImageTooltipText(pt);
						if(strToolTip.GetLength() > 0)
						{
							pNotify->ti->sTooltip = strToolTip;
							pt = *pNotify->pt; 
							pt.x += 10;
							pt.y += 20;
							*pNotify->pt = pt;
						}
					}
				}
			}
		}
	}
}

LRESULT CRcpPageCTIForm::OnMyCallMessage(WPARAM wParam, LPARAM lParam)
{
	CMyCallMessage *pMessage = (CMyCallMessage*)wParam;
	return pMessage->Process((UINT)lParam);
}
/*
void CRcpPageCTIForm::AddAllbaroSMS(CString strPhone, CString strKeyPhone)
{
	//핸드폰에게만 문자
	if(strPhone.Left(2) == "01")
	{
		if((strPhone.Left(3).Compare("010") == 0 || strPhone.Left(3).Compare("011") == 0 || 
			strPhone.Left(3).Compare("017") == 0 || strPhone.Left(3).Compare("018") == 0 ||
			strPhone.Left(3).Compare("016") == 0))
		{
			CMkLock lock(m_csAllbaroSMS);
			m_mapAllbaroSMS.insert(ALL_BARO_SMS_MAP::value_type(strPhone, make_pair(strKeyPhone, GetTickCount())));	
			//TRACE("AddAllbaroSMS %s, %s \r\n", strPhone, strKeyPhone);
		}
	}
}

void CRcpPageCTIForm::RemoveAllbaroSMS(CString strPhone)
{
	//핸드폰에게만 문자
	if(strPhone.Left(2) == "01")
	{
		if((strPhone.Left(3).Compare("010") == 0 || strPhone.Left(3).Compare("011") == 0 || 
			strPhone.Left(3).Compare("017") == 0 || strPhone.Left(3).Compare("018") == 0 ||
			strPhone.Left(3).Compare("016") == 0))
		{
			CMkLock lock(m_csAllbaroSMS);
			m_mapAllbaroSMS.erase(strPhone);
			//TRACE("RemoveAllbaroSMS %s \r\n", strPhone);
		}
	}
}

BOOL CRcpPageCTIForm::SendAllbaroSMS()
{
	CMkLock lock(m_csAllbaroSMS);
	ALL_BARO_SMS_MAP::iterator it = m_mapAllbaroSMS.begin();
	for(; it != m_mapAllbaroSMS.end();)
	{
		if(GetTickCount() - it->second.second > 5000)
		{
			//TRACE("SendAllbaroSMS %s, %s, %d \r\n", it->first, it->second.first, GetTickCount() - it->second.second);
			CMkRecordset rs(m_pMkDb);
			CMkCommand cmd(m_pMkDb, "insert_sms_allbaro_hangup");
			cmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
			cmd.AddParameter(it->first);
			cmd.AddParameter(it->second.first);
			cmd.AddParameter(m_ui.nCompany); 
			cmd.AddParameter(m_ui.nWNo);
			cmd.AddParameter(m_ui.strName);

			if(rs.Execute(&cmd))
			{
				//TRACE("SendAllbaroSMS %s, %s, %d \r\n", it->first, it->second.first, GetTickCount() - it->second.second);
			}

			it = m_mapAllbaroSMS.erase(it);	
		}
		else
			it++;
	}
	return TRUE;
}
*/