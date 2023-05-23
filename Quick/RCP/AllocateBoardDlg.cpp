// AllocateBoardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateBoardDlg.h"
#include "RcpView.h"
#include "MakeHtmlTable.h"
#include "ColorDlg.h"
#include "AllocateBoardDynDlg.h"
#include "POIData.h"
#include "RiderMapDlg.h"
#include "AllocateBoardSettingDlg.h"
#include "RcpDlg.h"
#include "CancelDlg.h" 
#include "RiderMsgDlg.h"
#include "POIDataNew.h"
#include "MainFrm.h"
#include "MyMkMessenger.h"
#include "RiderTraceMapDlg.h"
#include "RcpMultiStateChange.h"

#define ID_SMS_ALLOCATE		0xFFFF
#define ID_PDA_ALLOCATE		(ID_SMS_ALLOCATE - 1)
#define ID_ALLOCATE_STATE	(ID_SMS_ALLOCATE - 2)
#define ID_FINISH_STATE		(ID_SMS_ALLOCATE - 3)
#define ID_WAIT_STATE		(ID_SMS_ALLOCATE - 4)
#define ID_RCP_STATE		(ID_SMS_ALLOCATE - 5)
#define ID_EDIT_ORDER		(ID_SMS_ALLOCATE - 6)
#define ID_PICKUP_STATE		(ID_SMS_ALLOCATE - 7)
#define ID_CANCEL_STATE		(ID_SMS_ALLOCATE - 8)

#define ID_SHOW_ALL	9999
#define ID_SHOW_SHARECODE	9998
#define ID_SHOW_BRANCH	9997
#define ID_SEND_MSG	9996


static LOGFONT lfBoldFont = {11,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움체"};

COLORREF crGreen = RGB(150,255,150);

#define CHANGE_SEARCH_RIDER 500
#define ALLOCATE_REFRESH 1000

BOOL CXTPTRSReportControl::OnCommand( WPARAM wParam, LPARAM lParam )
{
	GetParent()->SendMessage(WM_COMMAND,wParam,lParam);
	return CWnd::OnCommand(wParam, lParam);
}

BOOL CXTPTRSReportControl::PreTranslateMessage(MSG* pMsg)
{
	return CXTPGridControl::PreTranslateMessage(pMsg);
}

bool compare_greator_rider_score(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	return elem1->nScore > elem2->nScore;
}

bool compare_greator_rider_linear(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	return elem1->fOrderDistance < elem2->fOrderDistance;
}

// CAllocateBoardDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateBoardDlg, CMyDialog)
CAllocateBoardDlg::CAllocateBoardDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateBoardDlg::IDD, pParent)
	, m_bOnlyAuto(FALSE)
{
	m_nOneWidth = 138;
	m_nTopIndex = -1;
	m_nRefreshSecond = 0;
	m_nNowAddTime = 0;
	m_dtLastRefresh = COleDateTime(2000, 1, 1, 0, 0, 0);
	m_pSelectedRecordItem = NULL;
	m_bChkWorkReport = FALSE;
	m_bFinishTest = FALSE;
	m_bLinearType = FALSE;
	m_ptMoved = CPoint(-1, -1);
	m_nContextMenuLastOrder = 0;
	m_nContextMenuLastState = 0;
	m_nContextMenuLastCompany = 0;
	m_nContextMenuLastRNo = 0;
}

CAllocateBoardDlg::~CAllocateBoardDlg()
{

}

void CAllocateBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_ORDER_EMPTY_CHK, m_chkOrderEmpty);
	DDX_Control(pDX, IDC_SORT_COMBO, m_cmbSort);
	DDX_Control(pDX, IDC_LINE_COMBO, m_cmbLine);
	DDX_Control(pDX, IDC_ELAPSED_CHK, m_chkElapsed);
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
	DDX_Control(pDX, IDC_SHOW_RIDER_PHONE_CHK, m_chkShowRiderPhone);

	DDX_Control(pDX, IDC_TOTAL_COUNT_STATIC, m_stcTotalCount);
	DDX_Control(pDX, IDC_COMPLETE_COUNT_STATIC, m_stcCompleteCount);
	DDX_Control(pDX, IDC_CANCEL_COUNT_STATIC, m_stcCancelCount);
	DDX_Control(pDX, IDC_REG_RIDER_STATIC, m_stcRegRider);
	DDX_Control(pDX, IDC_WORK_RIDER_STATIC, m_stcWorkRider);
	DDX_Control(pDX, IDC_REFRESH_EDIT, m_edtRefresh);
	DDX_Control(pDX, IDC_SEARCH_RIDER_EDIT, m_edtSearchRider);
	DDX_Control(pDX, IDC_SHOW_DTP, m_dtpShow);
	DDX_Control(pDX, IDC_BRANCH_COMBO2, m_cmbBranch);
	DDX_Control(pDX, IDC_CAR_SHOW_TYPE_CHK, m_chkCarShowType);
	DDX_Control(pDX, ID_REFRESH_COMBO, m_cmbRefresh);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_SHOW_DYN_CHECK, m_chkShowDyn);

	DDX_Control(pDX, IDC_RIDER_GROUP_COMBO, m_cmbRiderGroup);
	DDX_Control(pDX, IDC_SHOW_RIDER_POS_CHECK, m_chkShowRiderPos);
	DDX_Control(pDX, IDC_SHOW_WORKING_RIDER_CHECK, m_chkShowWorkingRider);
	DDX_Control(pDX, IDC_FIND_PROPER_RIDER_CHECK, m_chkFindProperRider);
	DDX_Control(pDX, IDC_SHOW_ONLY_CONN_RIDER, m_chkShowOnlyConnRider);
	DDX_Control(pDX, IDC_NOTIFY_CONN_RIDER, m_chkNotifyConnRider);
	DDX_Control(pDX, IDC_ONLY_AUTO_CHECK, m_chkOnlyAuto);
	DDX_Check(pDX, IDC_ONLY_AUTO_CHECK, m_bOnlyAuto);

	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_STATIC6, m_stc6);
	DDX_Control(pDX, IDC_STATIC7, m_stc7);
	DDX_Control(pDX, IDC_STATIC8, m_stc8);
}


BEGIN_MESSAGE_MAP(CAllocateBoardDlg, CMyDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ORDER_EMPTY_CHK, OnBnClickedOrderEmptyChk)
	ON_CBN_SELCHANGE(IDC_SORT_COMBO, OnCbnSelchangeSortCombo)
	ON_CBN_SELCHANGE(IDC_LINE_COMBO, OnCbnSelchangeLineCombo)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_ELAPSED_CHK, OnBnClickedElapsedChk)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, OnCbnSelchangeStateCombo)
	ON_BN_CLICKED(IDC_SHOW_RIDER_PHONE_CHK, OnBnClickedShowRiderPhoneChk)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_SEARCH_RIDER_EDIT, OnEnChangeSearchRiderEdit)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO2, OnCbnSelchangeBranchCombo2)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_REFRESH_LIST, OnRefreshList)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	
	ON_BN_CLICKED(IDC_CAR_SHOW_TYPE_CHK, OnBnClickedCarShowTypeChk)
	ON_CBN_SELCHANGE(ID_REFRESH_COMBO, OnCbnSelchangeRefreshCombo)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_MESSAGE(WM_ALLOCATE_BOARD_DYN_CLOSE, OnCloseAllocateBoardDyn)
	ON_CBN_SELCHANGE(IDC_RIDER_GROUP_COMBO, OnCbnSelchangeRiderGroupCombo)
	ON_BN_CLICKED(IDC_SHOW_RIDER_POS_CHECK, OnBnClickedShowRiderPosCheck)
	ON_BN_CLICKED(IDC_SHOW_WORKING_RIDER_CHECK, OnBnClickedShowWorkingRiderCheck)
	ON_COMMAND(ID_UPDATE_COLOR, OnUpdateColor)
	ON_COMMAND(ID_SHOW_RIDER_POS, OnShowRiderPos)
	ON_COMMAND(ID_SET_WORKING, OnSetWorking)
	ON_COMMAND(ID_SET_LEAVE, OnSetLeave)
	ON_COMMAND(ID_SHOW_RIDER_INFO, OnShowRiderInfo)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SMS_ALLOCATE, OnSMSAllocate)
	ON_COMMAND(ID_PDA_ALLOCATE, OnPDAAllocate)
	ON_BN_CLICKED(IDC_ADDITIONAL_SETTING_BTN, OnBnClickedAdditionalSettingBtn)
	ON_BN_CLICKED(IDC_SHOW_ONLY_CONN_RIDER, OnBnClickedShowOnlyConnRider)
	ON_COMMAND(ID_ALLOCATE_STATE, OnAllocateState)
	ON_COMMAND(ID_FINISH_STATE, OnFinishState)
	ON_COMMAND(ID_WAIT_STATE, OnWaitState)
	ON_COMMAND(ID_RCP_STATE, OnRcpState)
	ON_COMMAND(ID_EDIT_ORDER, OnEditOrder)
	ON_COMMAND(ID_PICKUP_STATE, OnPickupState)
	ON_COMMAND(ID_CANCEL_STATE, OnCancelState)

	ON_COMMAND(ID_SHOW_ALL, OnShowAll)
	ON_COMMAND(ID_SHOW_SHARECODE, OnShowShareCode)
	ON_COMMAND(ID_SHOW_BRANCH, OnShowBranch)
	ON_COMMAND(ID_SEND_MSG, OnSendMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


LONG CAllocateBoardDlg::OnCloseAllocateBoardDyn(WPARAM wParam, LPARAM lParam)
{
	CAllocateBoardDynDlg *pDlg = (CAllocateBoardDynDlg*)wParam;

	if(pDlg)
	{
		DYN_WND_MAP::iterator it = m_mapDynWnd.find(pDlg);
		if(it != m_mapDynWnd.end())
			m_mapDynWnd.erase(it);

		delete pDlg;
		pDlg = NULL;
	}
	else if((int)lParam == 1)
	{
		DeleteAllDynWnd();
	}

	return 0;
}


BOOL CAllocateBoardDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_pRPM = new CAllocateReportPaintManager;
	m_wndReport.SetPaintManager(m_pRPM);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(FALSE, xtpGridNoLines);
	m_wndReport.GetPaintManager()->SetTextFont(lfBoldFont);
	m_wndReport.SetGridColor(RGB(150, 150, 180));
	m_wndReport.ShowHeader(FALSE);

	m_chkOrderEmpty.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "NoShowOrderEmpty", 0));
	m_chkElapsed.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "ElapsedTime1", 1));
	m_chkShowRiderPhone.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "ShowRiderPhone", 0));
	m_chkCarShowType.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "CarShowType1", 1));
	m_chkShowDyn.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "ShowDyn1", 1));
	m_chkShowRiderPos.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "ShowRiderPos1", 1));
	m_chkShowWorkingRider.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "ShowWorkingRider", 0));
	m_chkFindProperRider.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "FindProperRider", 0));
	m_chkOnlyAuto.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "FindProperRiderOnlyAuto", 0));

	GetAdditionalSetting();


	m_pRPM->SetOrderTimeType(m_chkElapsed.GetCheck());		
	m_pRPM->SetShowPhoneAlways(m_chkShowRiderPhone.GetCheck());		
	m_pRPM->SetShowRiderPos(m_chkShowRiderPos.GetCheck());		
	m_pRPM->SetLinearType(m_bLinearType);


	m_cmbSort.SetCurSel(0);
	m_cmbLine.SetCurSel(2);
	m_cmbState.SetCurSel(0);


	for(int i=0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo * pBi = m_ba.GetAt(i);
		m_cmbBranch.InsertString(i, pBi->strBranchName);
		m_cmbBranch.SetItemData(i, (DWORD_PTR)pBi->nCompanyCode);
	}

	m_cmbBranch.SetCurSel(0);
	m_dtpShow.SetTime(COleDateTime::GetCurrentTime());


	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	m_tooltip.SetTransparency(10);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);
	m_tooltip.AddTool(&m_wndReport, "");

	m_cmbRefresh.ResetContent();
	m_cmbRefresh.InsertString(0, "무갱신");
	m_cmbRefresh.SetItemData(0, 0);
	m_cmbRefresh.InsertString(1, "3초갱신");
	m_cmbRefresh.SetItemData(1, 3000);
	m_cmbRefresh.InsertString(2, "5초갱신");
	m_cmbRefresh.SetItemData(2, 5000);
	m_cmbRefresh.InsertString(3, "10초갱신");
	m_cmbRefresh.SetItemData(3, 10000);
	m_cmbRefresh.InsertString(4, "30초갱신");
	m_cmbRefresh.SetItemData(4, 30000);
	m_cmbRefresh.InsertString(5, "1분갱신");
	m_cmbRefresh.SetItemData(5, 60000);
	m_cmbRefresh.SetCurSel(0);
	
	LU->MakeAllocateGroupCombo(&m_cmbRiderGroup);
	m_cmbRiderGroup.SetCurSel(0);

	GetRiderList();
	RefreshRiderList();
	RefreshList();

	SetTimer(3, 5000, NULL);

	return TRUE;
}

void CAllocateBoardDlg::RefreshRiderList(CString strSearchKeyword)
{
	m_pSelectedRecordItem = NULL;

	m_edtSearchRider.GetWindowText(strSearchKeyword);
	m_pRPM->ResortRider(m_cmbSort.GetCurSel(), m_chkCarShowType.GetCheck(), m_bOtherRiderHaveMyOrderSplitSort);

	CRect rc;
	m_wndReport.GetClientRect(&rc);
	CXTPGridRow *pRow = m_wndReport.HitTest(CPoint(rc.left+2, rc.bottom - m_pRPM->GetRowHeight(NULL, NULL)));
	if(pRow) 
		m_nTopIndex = pRow->GetIndex();

	m_wndReport.GetColumns()->Clear();
	m_wndReport.GetRows()->Clear();
	m_wndReport.GetRecords()->RemoveAll();
	m_wndReport.GetClientRect(rc);
	int nCols = rc.Width() / m_nOneWidth;
	if(nCols == 0)
	{
		m_wndReport.Populate();
		return;
	}

	for(int i = 0; i < nCols; i++)
	{
		CXTPGridColumn* pCol1 = 
			m_wndReport.AddColumn(new CXTPGridColumn(i, "", m_nOneWidth, FALSE));
	}


	long nCol, nRow = -1, n = 0;
	CXTPGridRecord *pRecord = NULL;
	ALLOCATE_RIDER_VECTOR::iterator it;

	for(it = m_pRPM->m_vecRider.begin(); it != m_pRPM->m_vecRider.end(); it++)
	{
		ALLOCATE_BOARD_RIDER_INFO *rider = *it;

		if(strSearchKeyword.GetLength() > 0)
		{
			if(rider->strName.Find(strSearchKeyword) < 0 &&
				rider->nRNo != atol(strSearchKeyword))
			{
				continue;
			}
		}

		if(m_chkOrderEmpty.GetCheck())
		{
			if(m_pRPM->m_mapOrder.find(std::make_pair(rider->nCompany, rider->nRNo)) == 
					m_pRPM->m_mapOrder.end())
			{
				continue;
			}
		}

		if(m_cmbRiderGroup.GetCurSel() > 0)
		{
			if(rider->nAllocGroup != m_cmbRiderGroup.GetItemData(m_cmbRiderGroup.GetCurSel()))
			{
				continue;
			}
		}

		if(m_chkShowWorkingRider.GetCheck() > 0 && !rider->bShareRiderHaveMyOrder)
		{
			if(rider->nWorkReportState != 1)
			{
				continue;
			}
		}
		
		if(m_chkShowOnlyConnRider.GetCheck() > 0)
		{
			if(!rider->bLogin &&
				rider->dtLogInOut < COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 60, 0))
			{
				continue;
			}
		}


		nCol = n++ % nCols;
		if(nCol == 0)
		{
			if(pRecord != NULL)
			{
				m_wndReport.AddRecord(pRecord);
			}

			pRecord = new CXTPGridRecord;
			nRow++;
		}

		CString strTemp;
		if(rider->bShareRiderHaveMyOrder)
		{
			CString strCompanyName = m_ci.GetName(rider->nCompany);
			strCompanyName.Replace("퀵서비스", "퀵");
			strCompanyName.Replace("(주)", "");
			strTemp.Format("%s)%d/%s", strCompanyName, rider->nRNo, rider->strName);
		}
		else
			strTemp.Format("%d/%s", rider->nRNo, rider->strName);

		CMyRecordItem *pRecordItem = new CMyRecordItem(strTemp);

		pRecordItem->pAllocRiderInfo = rider; 
		pRecord->AddItem(pRecordItem);
	}

	if(pRecord)
		m_wndReport.AddRecord(pRecord);

	m_wndReport.Populate();
}

void CAllocateBoardDlg::GetRiderList(BOOL bShareRider)
{
	if(!bShareRider)
	{
		ALLOCATE_RIDER_VECTOR::iterator it;

		for(it = m_pRPM->m_vecRider.begin(); it != m_pRPM->m_vecRider.end(); it++)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = *it;
			delete rider;
		}

		m_pRPM->m_vecRider.clear();
		m_pRPM->m_mapRider.clear();
	}
	else
	{
		ALLOCATE_RIDER_MAP::iterator it;

		for(it = m_mapShareRider.begin(); it != m_mapShareRider.end(); it++)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = it->second;
			delete rider;
		}

		m_mapShareRider.clear();
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_board_rider8");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bShareRider);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_ci.m_nShareCode1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bOtherRiderHaveMyOrder);
	CMkParameter *parWorkReprt = pCmd.AddParameter(typeBool, typeOutput, sizeof(int), 1);

	if(!pRs.Execute(&pCmd)) return;

	parWorkReprt->GetValue(m_bChkWorkReport);
	if(m_bChkWorkReport)
	{
		m_pRPM->SetDisplayAttendLeave(m_bChkWorkReport);
	}


	long  nRow = -1;
	CXTPGridRecord *pRecord = NULL;

	for(int n = 0; n < pRs.GetRecordCount(); n++)
	{
		int nMNo, nCompany;
		CString strName, strTel, strPosName, strDong;
		long nCarType, nRiderColor, nRiderTextColor, nAllocGroup;
		long nDongID, nWorkReportState;
		COleDateTime dtPos, dtLastLogin;
		COleDateTime dtAttend, dtLeave;
		long nPosX, nPosY;

		pRs.GetFieldValue("nMNo", nMNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sHp", strTel);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nRiderColor", nRiderColor);
		pRs.GetFieldValue("nRiderTextColor", nRiderTextColor);
		pRs.GetFieldValue("nAllocGroup", nAllocGroup);
		pRs.GetFieldValue("nDongID", nDongID);
		pRs.GetFieldValue("dtPos", dtPos);
		pRs.GetFieldValue("nWorkReportState", nWorkReportState);
		pRs.GetFieldValue("dtWorkReport", dtAttend);
		pRs.GetFieldValue("dtLeave", dtLeave);
		pRs.GetFieldValue("nPosX", nPosX);
		pRs.GetFieldValue("nPosY", nPosY);
		pRs.GetFieldValue("sPosName", strPosName);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("nDongID", nDongID);
		pRs.GetFieldValue("dtTodayLastLogin", dtLastLogin);

		ALLOCATE_BOARD_RIDER_INFO* rider = new ALLOCATE_BOARD_RIDER_INFO;
		rider->nCompany = nCompany;
		rider->nRNo = nMNo;
		rider->strName = strName;
		rider->strPhone = strTel;
		rider->nCarType = nCarType;
		rider->nRiderColor = nRiderColor;
		rider->nRiderTextColor = nRiderTextColor;
		rider->nAllocCount = 0;
		rider->nFinishCount = 0;
		rider->nTotalCount = 0;
		rider->nTotalCharge = 0;
		rider->nPickupCount = 0;
		rider->nAllocGroup = nAllocGroup;
		rider->strCurPosName = strDong + " " + strPosName;
		rider->dtPos = dtPos;
		rider->nWorkReportState = nWorkReportState;
		rider->dtAttend = dtAttend;
		rider->dtLeave = dtLeave;
		rider->nPosX = nPosX;
		rider->nPosY = nPosY;
		rider->nScore = 0;
		rider->nStartDistanceScore = 0;
		rider->fOrderCountScore = 0;
		rider->nDirectionScore = 0;
		rider->nAngleScore = 0;
		rider->bGpsPos = TRUE;
		rider->bDelayRider = FALSE;
		rider->bShareRider = bShareRider;
		rider->bShareRiderHaveMyOrder = (!bShareRider && !m_ci.IsChildCompany(nCompany)) ? TRUE : FALSE;
		rider->nHomeDongID = nDongID;
		rider->strHomeDong = nDongID > 0 ? m_poiNew.GetDongPOI(nDongID)->GetDong() : "";
		rider->bLogin = FALSE;
		rider->dtLogInOut = dtLastLogin;

		if(!bShareRider)
		{
			m_pRPM->m_vecRider.push_back(rider);
			m_pRPM->m_mapRider.insert(ALLOCATE_RIDER_MAP::value_type(
					std::make_pair(nCompany, nMNo), rider));
		}
		else
		{
			m_mapShareRider.insert(ALLOCATE_RIDER_MAP::value_type(
				std::make_pair(nCompany, nMNo), rider));
		}

		pRs.MoveNext();
	}

	pRs.Close();
}


void CAllocateBoardDlg::RefreshList()
{
	#define DELAY_ORDER_MAX_DISTANCE	70		//km

	COleDateTime dtMax = COleDateTime(2000, 1, 1, 0, 0, 0);

	if(m_chkShowDyn.GetCheck())
	{
		m_mapFlashRider.clear();
		ALLOCATE_RIDER_VECTOR::iterator itSize;
		for(itSize = m_pRPM->m_vecRider.begin(); itSize != m_pRPM->m_vecRider.end(); itSize++)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = *itSize;
			rider->x = -1;
			rider->y = -1;
		}
	}

	BOOL bElapseLimitBike = m_nAL > 0 || m_nPL > 0 || m_nAG > 0 || m_nPG > 0;
	BOOL bElapseLimitCar = m_nAL2 > 0 || m_nPL2 > 0 || m_nAG2 > 0 || m_nPG2 > 0;

	if(bElapseLimitBike || bElapseLimitCar)
	{
		ALLOCATE_RIDER_MAP::iterator it;
		for(it = m_pRPM->m_mapRider.begin(); it != m_pRPM->m_mapRider.end(); it++)
		{
			it->second->bDelayRider = FALSE;
		}
	}

	m_pRPM->m_mapOrder.clear();

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList &OtherOrder = LU->GetRcpView()->GetOtherOrder();
	OrderRecordList::iterator it;
	RIDER_LAST_ACTION_MAP::iterator itAction;

	long nCompleteCount = 0, nCancelCount = 0;
	COleDateTime dtTomorrow = COleDateTime::GetCurrentTime() + COleDateTimeSpan(1, 0, 0, 0);
	dtTomorrow.SetDateTime(dtTomorrow.GetYear(), dtTomorrow.GetMonth(), dtTomorrow.GetDay(), 0, 0, 0);
 
	for(it = order.begin(); it != order.end(); it++)
	{
		AddMatchOrder(&it->second, nCompleteCount, nCancelCount, FALSE, dtTomorrow, 
					dtMax, bElapseLimitBike, bElapseLimitCar);
	}

	for(it = OtherOrder.begin(); it != OtherOrder.end(); it++)
	{
		AddMatchOrder(&it->second, nCompleteCount, nCancelCount, TRUE, dtTomorrow, 
			dtMax, bElapseLimitBike, bElapseLimitCar);
	}


	if(m_chkShowRiderPos.GetCheck())
	{
		ALLOCATE_RIDER_VECTOR::iterator itSize;
		for(itSize = m_pRPM->m_vecRider.begin(); itSize != m_pRPM->m_vecRider.end(); itSize++)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = *itSize;
			if(rider->strCurPosName.IsEmpty() || rider->bGpsPos == FALSE || 
					rider->bGpsPos && 
					!rider->bLogin && 
					rider->dtPos < COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 10, 0))
			{
				itAction = m_mapRiderLastAction.find(std::make_pair(rider->nCompany, rider->nRNo));
				if(itAction != m_mapRiderLastAction.end())
				{
					rider->dtLastAction = itAction->second.dtLast;
					it = order.find(itAction->second.nLastTNo);
					if(it != order.end())
					{
						rider->strCurPosName.Format("(X)%s", it->second.nState == 35 ? it->second.strDest.c_str() : it->second.strStart.c_str());
						rider->dtPos = itAction->second.dtLast;
						rider->nPosX = it->second.nState == 35 ? it->second.nDestPosX : it->second.nStartPosX;
						rider->nPosY = it->second.nState == 35 ? it->second.nDestPosY : it->second.nStartPosY;
						rider->bGpsPos = FALSE;
					}
				}
				else
				{
					rider->dtLastAction = COleDateTime(2000, 1, 1, 1, 1, 1);

					COleDateTime dtToday = COleDateTime::GetCurrentTime();
					if(dtToday.GetHour() < 10.5)
					{
						if(rider->nHomeDongID > 0)
						{
							CPOIUnit *pPOI = m_poiNew.GetDongPOI(rider->nHomeDongID);
							if(pPOI)
							{
								if(strcmp(pPOI->GetGugun(), pPOI->GetDong()) == 0)
									rider->strCurPosName.Format("(H)%s", pPOI->GetGugun());
								else
									rider->strCurPosName.Format("(H)%s%s", pPOI->GetGugun(), pPOI->GetDong());
								rider->dtPos = COleDateTime::GetCurrentTime();
								rider->nPosX = pPOI->GetPosX();
								rider->nPosY = pPOI->GetPosY();
								rider->bGpsPos = FALSE;
							}
						}
					}
					else
					{
						if(rider->nHomeDongID > 0 && rider->strCurPosName.GetLength() > 0)
						{
							rider->strCurPosName = "";
							rider->dtPos = COleDateTime::GetCurrentTime();
							rider->nPosX = 0;
							rider->nPosY = 0;
							rider->bGpsPos = FALSE;
						}
					}
				}
			}
			else
			{
				itAction = m_mapRiderLastAction.find(std::make_pair(rider->nCompany, rider->nRNo));
				if(itAction != m_mapRiderLastAction.end())
					rider->dtLastAction = itAction->second.dtLast;
				else
					rider->dtLastAction = COleDateTime(2000, 1, 1, 1, 1, 1);
			}
		}
	}

	m_wndReport.RedrawControl();
	
	RefreshCommon(nCompleteCount, nCancelCount);

	if(m_chkShowDyn.GetCheck())
	{
		if(m_bFirstRefresh)
			SetTimer(2, 10, NULL);				
		else
			m_bFirstRefresh = TRUE;
		m_dtLastRefresh = max(m_dtLastRefresh, dtMax);
	}

}

void CAllocateBoardDlg::AddMatchOrder(OrderRecord *pOrder, long &nCompleteCount, long &nCancelCount, 
							BOOL bStartOherOrder, COleDateTime &dtTomorrow, COleDateTime &dtMax,
							BOOL &bElapseLimitBike, BOOL &bElapseLimitCar)
{
	if(pOrder->nState >= 11 && pOrder->nState <= 35)
	{ 
		if(pOrder->dtRcp > dtTomorrow) //내일예약건 배차는 나오지 않게 한다
		{
			return;
		}

		if((bStartOherOrder == TRUE) && m_ci.IsChildCompany(pOrder->nCompany)) //order 과 OtherOrder 사이에 중복이 있음
		{
			return;
		}				

		if(m_chkShowRiderPos.GetCheck())
		{
			RIDER_LAST_ACTION_MAP::iterator itAction;
			itAction = m_mapRiderLastAction.find(std::make_pair(pOrder->nRiderCompany, pOrder->nRNo));
			if(itAction == m_mapRiderLastAction.end())
			{
				ST_ARIDER arider;
				arider.nCompany = pOrder->nRiderCompany;
				arider.nRNo = pOrder->nRNo;
				arider.dtLast = pOrder->dtState;
				arider.nLastTNo = pOrder->nTNo;
				m_mapRiderLastAction.insert(RIDER_LAST_ACTION_MAP::value_type(
					std::make_pair(pOrder->nRiderCompany, pOrder->nRNo), 
					arider));
			}
			else if(itAction->second.dtLast < pOrder->dtState)
			{
				itAction->second.dtLast = pOrder->dtState;
				itAction->second.nLastTNo = pOrder->nTNo;
			}
		}

		ALLOCATE_ORDER_INFO order;
		order.nCompany = pOrder->nRiderCompany;
		order.nRNo = pOrder->nRNo;
		order.nState = pOrder->nState;
		order.strStart = pOrder->strStart.c_str();
		order.strDest = pOrder->strDest.c_str();
		order.nCharge = pOrder->nCharge;
		order.nWayType = pOrder->nWayType;
		order.nRunType = pOrder->nRunType;
		order.dtTime = pOrder->dtState;
		order.nTNo = pOrder->nTNo;

		if(m_ci.IsChildCompany(pOrder->nCompany))
		{
			order.bOtherOrder = FALSE;
			nCompleteCount++;
		}
		else
		{
			order.bOtherOrder = TRUE;
		}

		dtMax = max(dtMax, order.dtTime);

		m_pRPM->m_mapOrder.insert(ALLOCATE_ORDER_MAP::value_type(
			std::make_pair(pOrder->nRiderCompany, pOrder->nRNo), order));


		if(m_chkShowDyn.GetCheck())
		{
			if(m_bFirstRefresh)
			{
				if(order.dtTime > m_dtLastRefresh)
				{
					ALLOCATE_FLASH_RIDER_MAP::iterator itFlash;
					itFlash = m_mapFlashRider.find(std::make_pair(pOrder->nRiderCompany, pOrder->nRNo));
					if(m_mapFlashRider.end() == itFlash)
					{
						ST_ARIDER arider;
						arider.nCompany = pOrder->nRiderCompany;
						arider.nRNo = pOrder->nRNo;
						m_mapFlashRider.insert(ALLOCATE_FLASH_RIDER_MAP::value_type(
							std::make_pair(pOrder->nRiderCompany, pOrder->nRNo), 
							arider));
					}
				}
			}
		}

		if(pOrder->nState >= 11 && pOrder->nState < 35)
		{
			BOOL bDelayRider = FALSE;
			ALLOCATE_RIDER_MAP::iterator itRider;

			if(bElapseLimitBike || bElapseLimitCar)
			{
				itRider = m_pRPM->m_mapRider.find(std::make_pair(pOrder->nRiderCompany, pOrder->nRNo));
				if(itRider != m_pRPM->m_mapRider.end())
				{
					if(itRider->second->nCarType <= CAR_BIGBIKE && bElapseLimitBike)
					{
						if(m_poiNew.GetDongPOI(pOrder->nStartRealDongID)->GetSido() ==
							m_poiNew.GetDongPOI(pOrder->nDestRealDongID)->GetSido())
						{
							if(pOrder->nState <= 30)
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nAL, 0) &&
									m_nAL > 0)
								{
									bDelayRider = TRUE;
								}
							}
							else 
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nPL, 0) &&
									m_nPL > 0)
								{
									bDelayRider = TRUE;
								}
							}
						}
						else
						{
							if(pOrder->nState <= 30)
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nAG, 0) &&
									m_nAG > 0)
								{
									bDelayRider = TRUE;
								}
							}
							else 
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nPG, 0) &&
									m_nPG > 0)
								{
									bDelayRider = TRUE;
								}
							}
						}
					}
					else if(itRider->second->nCarType > CAR_BIGBIKE && bElapseLimitCar)
					{
						if(m_poiNew.GetDongPOI(pOrder->nStartRealDongID)->GetSido() ==
							m_poiNew.GetDongPOI(pOrder->nDestRealDongID)->GetSido())
						{
							if(pOrder->nState <= 30)
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nAL2, 0) &&
									m_nAL2 > 0)
								{
									bDelayRider = TRUE;
								}
							}
							else 
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nPL2, 0) &&
									m_nPL2 > 0)
								{
									bDelayRider = TRUE;
								}
							}
						}
						else
						{
							if(pOrder->nState <= 30)
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nAG2, 0) &&
									m_nAG2 > 0)
								{
									bDelayRider = TRUE;
								}
							}
							else 
							{
								if(pOrder->dtState < COleDateTime::GetCurrentTime() - 
									COleDateTimeSpan(0, 0, m_nPG2, 0) &&
									m_nPG2 > 0)
								{
									bDelayRider = TRUE;
								}
							}
						}
					}

					if(bDelayRider)
					{
						CPOIUnit *pStart = m_poiNew.GetDongPOI(pOrder->nStartRealDongID);
						CPOIUnit *pDest = m_poiNew.GetDongPOI(pOrder->nDestRealDongID);

						if(pStart != NULL && pDest != NULL)
						{
							if(DELAY_ORDER_MAX_DISTANCE > (pStart->GetDistanceMeter(pDest) / 1000))
							{
								itRider->second->bDelayRider = TRUE;
							}
						}
					}
				}

			}
		}
	}
	else if(pOrder->nState == 40)
	{
		nCancelCount++;
	}
}

void CAllocateBoardDlg::RefreshListPredate()
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	COleDateTime dtNew;
	COleDateTime dtShow;

	m_dtpShow.GetTime(dtShow);
	dtNew = dtShow;

	//설정된 시간이 오늘이 아닌경우
	if(!(dtCur.GetYear() == dtShow.GetYear() &&
		dtCur.GetMonth() == dtShow.GetMonth() &&
		dtCur.GetDay() == dtShow.GetDay())) 
	{
		if(dtCur.GetHour() < BASE_HOUR) {
			dtNew = dtShow - COleDateTimeSpan(1, 0, 0, 0);
		}
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_rider_state_with_date2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtNew);
	if(!pRs.Execute(&pCmd)) return;

	int nRNo, nState, nRiderCompany;
	CString strStart, strDest;
	long nCharge, nCompany;
	COleDateTime dtTime;
	int nWayType, nCarType;
	
	long nCompleteCount = 0;
	long nCancelCount = 0;
	long nTNo, nRunType;

	m_pRPM->m_mapOrder.clear();

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nWayType", nWayType);
		pRs.GetFieldValue("nRunType", nRunType);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nTNo", nTNo);

		nCompleteCount++;

		switch(nState)
		{
		case 11:
			pRs.GetFieldValue("dt2", dtTime);
			break;

		case 30:
			pRs.GetFieldValue("dt3", dtTime);
			break;

		case 35:
			pRs.GetFieldValue("dtFinal", dtTime);
			break;
		}

		ALLOCATE_ORDER_INFO order;
		order.nCompany = nRiderCompany;
		order.nRNo = nRNo;
		order.nState = nState;
		order.strStart = strStart;
		order.strDest = strDest;
		order.nCharge = nCharge;
		order.nWayType = nWayType;
		order.nRunType = nRunType;
		order.nCarType = nCarType;
		order.dtTime = dtTime;
		order.nTNo = nTNo;
		if(m_ci.IsChildCompany(nCompany))
			order.bOtherOrder = FALSE;
		else
			order.bOtherOrder = TRUE;

		m_pRPM->m_mapOrder.insert(ALLOCATE_ORDER_MAP::value_type(
					std::make_pair(nRiderCompany, nRNo), order));
		pRs.MoveNext();
	}

	RefreshCommon(nCompleteCount, nCancelCount);
	pRs.Close();
}

void CAllocateBoardDlg::RefreshCommon(long nCompleteCount, long nCancelCount)
{
	if(m_nTopIndex > 0)
	{
		CXTPGridRows *pRows = m_wndReport.GetRows();
		if(pRows)
		{
			CXTPGridRow *pRow = pRows->GetAt(m_nTopIndex);
			if(pRow)
			{
				m_wndReport.EnsureVisible(pRow);
			}
		}
	}


	CString str;
	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	if(LF->POWER_CHECK(2007, "카운트 표시"))
	{
		str.Format("총콜수: %d개", nCompleteCount + nCancelCount);
		m_stcTotalCount.SetWindowText(str);
		str.Format("완료콜수: %d개", nCompleteCount);
		m_stcCompleteCount.SetWindowText(str);
		str.Format("취소콜수: %d개", nCancelCount);
		m_stcCancelCount.SetWindowText(str);
	}
	m_edtRefresh.SetWindowText(dtCur.Format("%H:%M:%S"));


	long nWorkCount=0;
	long nPreCompany=0, nPreRNo=0;
	long nAllocCount = 0;
	long nFinishCount = 0;
	long nTotalCharge = 0;
	long nPickupCount = 0;
	ALLOCATE_ORDER_MAP::iterator it;
	ALLOCATE_RIDER_MAP::iterator itRider;
	

	for(it = m_pRPM->m_mapOrder.begin(); it != m_pRPM->m_mapOrder.end(); it++)
	{
		if((*it).second.nCompany != nPreCompany ||
			(*it).second.nRNo != nPreRNo)
		{
			itRider = m_pRPM->m_mapRider.find(std::make_pair(nPreCompany, nPreRNo));
			if(itRider != m_pRPM->m_mapRider.end())
			{
				ALLOCATE_BOARD_RIDER_INFO *rider = (*itRider).second;
				rider->nAllocCount = nAllocCount;
				rider->nFinishCount = nFinishCount;
				rider->nTotalCharge = nTotalCharge;
				rider->nTotalCount = nAllocCount + nFinishCount;
				rider->nPickupCount = nPickupCount;
			}

			nAllocCount = 0;
			nFinishCount = 0;
			nTotalCharge = 0;
			nPickupCount = 0;

			nPreCompany = (*it).second.nCompany;
			nPreRNo = (*it).second.nRNo;
			if(m_ci.IsChildCompany(nPreCompany))
				nWorkCount++;
		}

		if((*it).second.nState == 31)
			nPickupCount++;

		if((*it).second.nState < 35)
			nAllocCount++;
		else nFinishCount++;

		nTotalCharge += (*it).second.nCharge;
	}

	str.Format("출근기사: %d명", nWorkCount);
	m_stcWorkRider.SetWindowText(str);
	str.Format("등록기사: %d명", m_pRPM->m_vecRider.size());
	m_stcRegRider.SetWindowText(str);
}



void CAllocateBoardDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(nType == SIZE_MINIMIZED) return;

	if(m_wndReport.GetSafeHwnd())
	{
		m_wndReport.SetWindowPos(NULL, 126, 0, cx - 126, cy, 0);
		RefreshRiderList();
	}

}

void CAllocateBoardDlg::OnBnClickedOrderEmptyChk()
{
	OnBnClickedRefreshBtn();
}


void CAllocateBoardDlg::OnCbnSelchangeSortCombo()
{
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnCbnSelchangeLineCombo()
{
	CString strLine;
	m_cmbLine.GetWindowText(strLine);
	m_pRPM->SetDisplayCount(atol(strLine));
	m_wndReport.Populate();
}

void CAllocateBoardDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = m_nOneWidth+300;
	lpMMI->ptMinTrackSize.y = m_nOneWidth+10;

	CMyDialog::OnGetMinMaxInfo(lpMMI);
}

void CAllocateBoardDlg::OnBnClickedElapsedChk()
{
	m_pRPM->SetOrderTimeType(m_chkElapsed.GetCheck());		
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnCbnSelchangeStateCombo()
{
	m_pRPM->SetOrderStateType(m_cmbState.GetCurSel());		
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnBnClickedShowRiderPhoneChk()
{
	m_pRPM->SetShowPhoneAlways(m_chkShowRiderPhone.GetCheck());		
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnBnClickedRefreshBtn()
{
	COleDateTime dtShow;

	RefreshRiderList();

	m_dtpShow.GetTime(dtShow);
	if(m_ei.dtTodayBound < dtShow)
		RefreshList();
	else
		RefreshListPredate();
}

HBRUSH CAllocateBoardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == this)
	{
		return m_HandleManager.GetBrushObject(0, TRUE);
	}
	
	if(nCtlColor == CTLCOLOR_STATIC) {
		CRuntimeClass *p = pWnd->GetRuntimeClass();
		if(!p->IsDerivedFrom(RUNTIME_CLASS(CEdit)))
		{
			pDC->SetBkMode(TRANSPARENT);
			return m_HandleManager.GetBrushObject(RGB(150,255,150));
		}
	}

	return hbr;
}

void CAllocateBoardDlg::FillForm(CDC *pDC)
{	
	CRect rc;
	GetClientRect(&rc);
	rc.right = 130;

	CXTPPenDC pen(*pDC, 0);

	pDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), crGreen); 

	for (int i = rc.top + 1; i < rc.bottom; i+= 3)
	{
		pDC->FillSolidRect(rc.left, i, rc.Width(), 1, XTPDrawHelpers()->BlendColors(RGB(200, 255, 200), RGB(220, 255, 220), 
			(float)(1.0 - ((i - rc.top)) / (float)rc.Height())));
	}

}

void CAllocateBoardDlg::OnEnChangeSearchRiderEdit()
{
	SetTimer(0, CHANGE_SEARCH_RIDER, NULL);	
}

void CAllocateBoardDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0)
	{
		KillTimer(nIDEvent);

		RefreshRiderList();
		RefreshList();
	}
	else if(nIDEvent == ALLOCATE_REFRESH)
	{
		m_nNowAddTime += 1000;
		
		if(m_nNowAddTime >= m_nRefreshSecond)
		{
			m_btnRefresh.SetWindowText("갱신중");
			OnBnClickedRefreshBtn();

			m_nNowAddTime = 0;
		}
		else
		{
			CString sTime = "";
			sTime.Format("%d초", m_nNowAddTime / 1000);
			m_btnRefresh.SetWindowText(sTime);
		}
	}
	else if(nIDEvent == 2)
	{
		if(m_chkShowDyn.GetCheck())
			FlashRiderList();
		KillTimer(2);
	}
	else if(nIDEvent == 3)
	{
		KillTimer(3);
		UpdateRiderState();
		LU->GetMessenger()->SetRecvRiderPosMsg(TRUE);
		SetTimer(3, 60000, NULL);
	}

	CMyDialog::OnTimer(nIDEvent);
}


void CAllocateBoardDlg::OnCbnSelchangeRefreshCombo()
{
	if(m_cmbRefresh.GetCurSel() > 0 )
	{
		if(m_nRefreshSecond == 0 )
			SetTimer(ALLOCATE_REFRESH,1000,NULL);

		m_nRefreshSecond = (long)m_cmbRefresh.GetItemData(m_cmbRefresh.GetCurSel());		

	}
	else if(m_cmbRefresh.GetCurSel() == 0)
	{
		KillTimer(ALLOCATE_REFRESH);
		m_btnRefresh.SetWindowText("갱신");
		m_nRefreshSecond = 0;
	}
}

void CAllocateBoardDlg::OnCbnSelchangeBranchCombo2()
{
	GetRiderList();
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnClose()
{
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "NoShowOrderEmpty", m_chkOrderEmpty.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "ElapsedTime1", m_chkElapsed.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "ShowRiderPhone", m_chkShowRiderPhone.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "CarShowType1", m_chkCarShowType.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "ShowDyn1", m_chkShowDyn.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "ShowRiderPos1", m_chkShowRiderPos.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "ShowWorkingRider", m_chkShowWorkingRider.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "FindProperRider", m_chkFindProperRider.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "FindProperRiderOnlyAuto", m_chkOnlyAuto.GetCheck());

	m_pParentWnd->PostMessage(WM_CLOSE_RIDER_DLG, 0, 0);

	CMyDialog::OnClose();
}

void CAllocateBoardDlg::OnOK()
{

}

void CAllocateBoardDlg::OnCancel()
{
	OnClose();
}


LONG CAllocateBoardDlg::OnRefreshList(WPARAM wParam, LPARAM lParam)
{
	COleDateTime dtShow;
	m_dtpShow.GetTime(dtShow);
	if(m_ei.dtTodayBound < dtShow)
	{
		RefreshRiderList();
		RefreshList();
	}

	return 0;
}


void CAllocateBoardDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
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
		if (IDC_REPORT == nID)
		{
			m_wndReport.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_wndReport.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				if(pCol)
				{
					CMakeHtmlTable htable;

					CMyRecordItem *pItem = (CMyRecordItem*)pRow->GetRecord()->GetItem(pCol);
					if(pItem)
					{
						long nHoverTNo = 0;
						ORDER_RECT_VECTOR::iterator it;;
						for(it = pItem->vecOrderRect.begin(); it != pItem->vecOrderRect.end(); it++)
						{
							if(it->rc.PtInRect(pt))
							{
								nHoverTNo = it->nTNo;
								break;
							}
						}						

						if(nHoverTNo > 0)
						{
							if(LU->GetRcpView()->GetOrderInfoHtmlTable(&htable, nHoverTNo))
							{
								htable.SetTitle("오더수정은 마우스오른쪽 버튼클릭");
								htable.SetTableBorder(1);
								pNotify->ti->sTooltip = htable.GetHtmlTable();
								pt = *pNotify->pt;
								pt.x += 5;
								pt.y += 20;
								*pNotify->pt = pt;
							}
						}
						else
						{
							long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
							long nRNo = pItem->pAllocRiderInfo->nRNo;

							if(LU->GetRcpView()->GetRiderOrderHtmlTable(&htable, nRiderCompany, nRNo))
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
						}
					}
				}
			}
		} //if
	} //if
} //End NotifyDisplayTooltip

BOOL CAllocateBoardDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	if(pMsg->message == WM_RBUTTONDOWN)
	{
		CRect rect;
		m_wndReport.GetWindowRect(&rect);

		CPoint point;
		::GetCursorPos(&point);

		if(rect.PtInRect(point))
		{
			return TRUE;
		}
		
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CAllocateBoardDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	if(pRecord == NULL)
		return;

	CXTPGridColumn *pColumn = pItemNotify->pColumn;
	if(pColumn == NULL)
		return;

	CMyRecordItem *pItem = (CMyRecordItem*)pRecord->GetItem(pColumn->GetIndex());
	if(pItem == NULL)
		return;

	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(nRiderCompany > 0)
		LU->GetRcpView()->SendMessage(WM_RIDER_ALLOCATE, (WPARAM)nRNo, (LPARAM)nRiderCompany);
}


void CAllocateBoardDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridColumn *pColumn = pItemNotify->pColumn;
	if(pColumn == NULL)
		return;

	CMyRecordItem *pItem = (CMyRecordItem*)pItemNotify->pRow->GetRecord()->GetItem(pColumn);
	if(pItem == NULL)
		return;

	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;
}


void CAllocateBoardDlg::OnBnClickedCarShowTypeChk()
{
	RefreshRiderList();
	RefreshList();
}

void CAllocateBoardDlg::FlashRiderList()
{
	ALLOCATE_FLASH_RIDER_MAP::iterator it;

	for(it = m_mapFlashRider.begin(); it != m_mapFlashRider.end(); it++)
	{
		ALLOCATE_RIDER_MAP::iterator it2 = 
			m_pRPM->m_mapRider.find(std::make_pair(it->second.nCompany, it->second.nRNo));

		if(it2 != m_pRPM->m_mapRider.end())
			FlashRider(it2->second);
	}

	m_mapFlashRider.clear();
}

void CAllocateBoardDlg::FlashRider(ALLOCATE_BOARD_RIDER_INFO *pRiderInfo, BOOL bFindProperRider, CRect rcBase, CPoint ptOffset,
										BOOL bShareRider, BOOL bFirstBox)
{
	CString strLine;
	m_cmbLine.GetWindowText(strLine);

	CAllocateBoardDynDlg *pDlg = new CAllocateBoardDynDlg();
	pDlg->m_pParentWnd = this;

	if(rcBase.bottom == 0)
		m_wndReport.GetWindowRect(pDlg->m_rcBase);
	else
		pDlg->m_rcBase = rcBase;

	pDlg->m_pRiderInfo = new ALLOCATE_BOARD_RIDER_INFO;
	pDlg->m_pRiderInfo->nCompany = pRiderInfo->nCompany;
	pDlg->m_pRiderInfo->nRNo = pRiderInfo->nRNo;
	pDlg->m_pRiderInfo->strName = pRiderInfo->strName;
	pDlg->m_pRiderInfo->strPhone = pRiderInfo->strPhone;
	pDlg->m_pRiderInfo->nCarType = pRiderInfo->nCarType;
	pDlg->m_pRiderInfo->nAllocCount = pRiderInfo->nAllocCount;
	pDlg->m_pRiderInfo->nPickupCount = pRiderInfo->nPickupCount;
	pDlg->m_pRiderInfo->nFinishCount = pRiderInfo->nFinishCount;
	pDlg->m_pRiderInfo->nTotalCount = pRiderInfo->nTotalCount;
	pDlg->m_pRiderInfo->nTotalCharge = pRiderInfo->nTotalCharge;
	pDlg->m_pRiderInfo->nRiderColor = pRiderInfo->nRiderColor;
	pDlg->m_pRiderInfo->nRiderTextColor = pRiderInfo->nRiderTextColor;
	pDlg->m_pRiderInfo->nAllocGroup = pRiderInfo->nAllocGroup;
	pDlg->m_pRiderInfo->strCurPosName = pRiderInfo->strCurPosName;
	pDlg->m_pRiderInfo->dtPos = pRiderInfo->dtPos;
	pDlg->m_pRiderInfo->nWorkReportState = pRiderInfo->nWorkReportState;
	pDlg->m_pRiderInfo->dtAttend = pRiderInfo->dtAttend;
	pDlg->m_pRiderInfo->dtLeave = pRiderInfo->dtLeave;
	pDlg->m_pRiderInfo->nPosX = pRiderInfo->nPosX;
	pDlg->m_pRiderInfo->nPosY = pRiderInfo->nPosY;
	pDlg->m_pRiderInfo->nScore = pRiderInfo->nScore;
	pDlg->m_pRiderInfo->nStartDistanceScore = pRiderInfo->nStartDistanceScore;
	pDlg->m_pRiderInfo->fOrderCountScore = pRiderInfo->fOrderCountScore;
	pDlg->m_pRiderInfo->nDirectionScore = pRiderInfo->nDirectionScore;
	pDlg->m_pRiderInfo->nAngleScore = pRiderInfo->nAngleScore;
	pDlg->m_pRiderInfo->bGpsPos = pRiderInfo->bGpsPos;
	pDlg->m_pRiderInfo->bDelayRider = pRiderInfo->bDelayRider;
	pDlg->m_pRiderInfo->bShareRider = bShareRider;
	pDlg->m_pRiderInfo->bShareRider = pRiderInfo->bShareRider;
	pDlg->m_pRiderInfo->nHomeDongID = pRiderInfo->nHomeDongID;
	pDlg->m_pRiderInfo->strHomeDong = pRiderInfo->strHomeDong;
	pDlg->m_pRiderInfo->fOrderDistance = pRiderInfo->fOrderDistance;
	pDlg->m_pRiderInfo->dtLastAction = pRiderInfo->dtLastAction;
	pDlg->m_pRiderInfo->bLogin = pRiderInfo->bLogin;
	pDlg->m_pRiderInfo->dtLogInOut = pRiderInfo->dtLogInOut;
	pDlg->m_pRiderInfo->bShareRiderHaveMyOrder = pRiderInfo->bShareRiderHaveMyOrder;

	if(ptOffset.x == 0)
	{
		pDlg->m_pRiderInfo->x = pRiderInfo->x;
		pDlg->m_pRiderInfo->y = pRiderInfo->y;
	}
	else
	{
		pDlg->m_pRiderInfo->x = ptOffset.x;
		pDlg->m_pRiderInfo->y = ptOffset.y;
	}

	if(bFindProperRider)
	{
		m_cmbLine.GetWindowText(strLine);
		pDlg->m_nDisplayCount = atol(strLine);
	}
	else
	{
		pDlg->m_nDisplayCount = 3;
	}

	pDlg->m_pMyDlg = (void*)pDlg;
	pDlg->m_bFindProperRider = bFindProperRider;
	pDlg->m_bShowPosName = m_chkShowRiderPos.GetCheck();
	pDlg->m_bFirstBox = bFirstBox;
	pDlg->Create(IDD_ALLOCATE_BOARD_DYN_DLG, this);

	if(bFindProperRider)
		m_mapDynWnd.insert(DYN_WND_MAP::value_type(pDlg, pDlg));

}

void CAllocateBoardDlg::OnCbnSelchangeRiderGroupCombo()
{
	OnBnClickedRefreshBtn();
}


void CAllocateBoardDlg::SetRiderPosRealTime(CRealTimeRiderPos &pos)
{
	ALLOCATE_RIDER_MAP::iterator itRider;

	itRider = m_pRPM->m_mapRider.find(std::make_pair(pos.nCompany, pos.nRNo));
	if(itRider != m_pRPM->m_mapRider.end())
	{
		ALLOCATE_BOARD_RIDER_INFO *rider = (*itRider).second;
		rider->strCurPosName = pos.strPosName;
		rider->dtPos = COleDateTime::GetCurrentTime();
		rider->nPosX = pos.nPosX;
		rider->nPosY = pos.nPosY;
		rider->bLogin = TRUE;
		rider->bGpsPos = TRUE;
		rider->dtLogInOut = COleDateTime::GetCurrentTime();
	}

	m_wndReport.RedrawControl();


	DYN_WND_MAP::iterator it;
	for(it = m_mapDynWnd.begin(); it != m_mapDynWnd.end(); it++)
	{
		if(it->second)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = ((CAllocateBoardDynDlg*)it->second)->m_pRiderInfo;
			if(pos.nCompany == rider->nCompany && pos.nRNo == rider->nRNo)
			{
				rider->strCurPosName = pos.strPosName;
				rider->dtPos = COleDateTime::GetCurrentTime();
				rider->nPosX = pos.nPosX;
				rider->nPosY = pos.nPosY;	
				rider->bLogin = TRUE;
				rider->bGpsPos = TRUE;
				rider->dtLogInOut = COleDateTime::GetCurrentTime();
				((CAllocateBoardDynDlg*)it->second)->m_wndReport.RedrawControl();
				break;
			}
		}
	}
}

void CAllocateBoardDlg::SetRiderConnState(long nCompany, long nRNo, int nState)
{
	ALLOCATE_RIDER_MAP::iterator itRider;

	//g_bana_log->Print("nCompany = %d, nRNo = %d, nState = %d\n", nCompany, nRNo, nState);

	itRider = m_pRPM->m_mapRider.find(std::make_pair(nCompany, nRNo));
	if(itRider != m_pRPM->m_mapRider.end())
	{
		ALLOCATE_BOARD_RIDER_INFO *rider = (*itRider).second;
		rider->bLogin = nState;
		rider->strCurPosName.Replace("[접속]", "");
		rider->strCurPosName.Replace("[끊김]", "");
		rider->strCurPosName = rider->bLogin ? "[접속]" : "[끊김]" + rider->strCurPosName;
		rider->dtLogInOut = COleDateTime::GetCurrentTime();

		if(m_chkShowOnlyConnRider.GetCheck())
			OnBnClickedRefreshBtn();
	}

	m_wndReport.RedrawControl();


	DYN_WND_MAP::iterator it;
	for(it = m_mapDynWnd.begin(); it != m_mapDynWnd.end(); it++)
	{
		if(it->second)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = ((CAllocateBoardDynDlg*)it->second)->m_pRiderInfo;
			if(nCompany == rider->nCompany && nRNo == rider->nRNo)
			{
				rider->bLogin = nState;
				rider->strCurPosName.Replace("[접속]", "");
				rider->strCurPosName.Replace("[끊김]", "");
				rider->strCurPosName = rider->bLogin ? "[접속]" : "[끊김]" + rider->strCurPosName;
				rider->dtLogInOut = COleDateTime::GetCurrentTime();
				((CAllocateBoardDynDlg*)it->second)->m_wndReport.RedrawControl();
				break;
			}
		}
	}
}

void CAllocateBoardDlg::OnBnClickedShowRiderPosCheck()
{
	m_pRPM->SetShowRiderPos(m_chkShowRiderPos.GetCheck());		
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnBnClickedShowWorkingRiderCheck()
{
	GetRiderList();
	RefreshRiderList();
	RefreshList();
}

void CAllocateBoardDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{	
	LU->GetRcpView()->SetRefreshStop();
 
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	if(m_pSelectedRecordItem == NULL) 
		return;

	if(m_wndReport.GetSelectedRows() == NULL)
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(11);
	
	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;


	if(!pItem->pAllocRiderInfo->bShareRiderHaveMyOrder)
	{
		CMkCommand pCmd(m_pMkDb, "select_rider_allocate_type_simple_1");
		pCmd.AddParameter(nRiderCompany);
		pCmd.AddParameter(nRNo);
		
		CMkParameter *parAllocType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		CMkParameter *parShowType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(pCmd.Execute())
		{
			int nAllocType, nShowType;
			parAllocType->GetValue(nAllocType);
			parShowType->GetValue(nShowType);

			pRMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

			if(nAllocType == 2) //PDA
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SMS_ALLOCATE, "PDA배차->SMS배차변경");
			else if(nAllocType == 1)
				pRMenu->AppendMenu(MF_BYPOSITION, ID_PDA_ALLOCATE, "SMS배차->PDA배차변경");
			else
			{
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SMS_ALLOCATE, "PDA배차->SMS배차변경");
				pRMenu->AppendMenu(MF_BYPOSITION, ID_PDA_ALLOCATE, "SMS배차->PDA배차변경");
			}

			pRMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

			if(nShowType == 0)//공유콜
			{
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_SHARECODE, "자사오더만보기(1차)");				
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_BRANCH, "소속오더만보기(지사)");
			}
			else if(nShowType == 1) //자사오더
			{
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_ALL, "공유오더보기");
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_BRANCH, "소속오더만보기(지사)");
			}
			else if(nShowType == 2) //소속오더
			{
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_ALL, "공유오더보기");
				pRMenu->AppendMenu(MF_BYPOSITION, ID_SHOW_SHARECODE, "자사오더만보기(1차)");
			}

			pRMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL); 
			pRMenu->AppendMenu(MF_BYPOSITION, ID_SEND_MSG, "메세지전송");
		}

		//개별오더에 대한 메뉴 추가함
		long nHoverTNo = 0;
		ORDER_RECT_VECTOR::iterator it;
		for(it = pItem->vecOrderRect.begin(); it != pItem->vecOrderRect.end(); it++)
		{
			CPoint pt = point;
			m_wndReport.ScreenToClient(&pt);
			if(it->rc.PtInRect(pt))
			{
				nHoverTNo = it->nTNo;
				break;
			}
		}	

		if(nHoverTNo > 0)
		{
			OrderRecordList mapOrderRecord = LU->GetRcpView()->GetCurrentOrder()->GetOrderRecordList();
			OrderRecordList::iterator it = mapOrderRecord.find(nHoverTNo);

			if(it != mapOrderRecord.end())
			{			
				pRMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
				pRMenu->AppendMenu(MF_BYPOSITION | MF_DISABLED, 0, 
						CString(it->second.strStart.c_str()) + "->" + it->second.strDest.c_str());

				if(m_ci.IsChildCompany(it->second.nCompany))
				{
					if(it->second.nState != 10)
						pRMenu->AppendMenu(MF_BYPOSITION, ID_RCP_STATE, "접수상태");
					if(it->second.nState != 30)
						pRMenu->AppendMenu(MF_BYPOSITION, ID_ALLOCATE_STATE, "배차상태");
					if(it->second.nState != 31)
						pRMenu->AppendMenu(MF_BYPOSITION, ID_PICKUP_STATE, "픽업상태");
					if(it->second.nState != 35)
						pRMenu->AppendMenu(MF_BYPOSITION, ID_FINISH_STATE, "완료상태");
					if(it->second.nState != 40)
						pRMenu->AppendMenu(MF_BYPOSITION, ID_CANCEL_STATE, "취소상태");
					pRMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
					pRMenu->AppendMenu(MF_BYPOSITION, ID_EDIT_ORDER, "오더수정");
				}
				else
				{
					pRMenu->AppendMenu(MF_BYPOSITION | MF_DISABLED, 0, 
						"타사오더 상태변경 불가");
				}

				m_nContextMenuLastOrder = it->second.nTNo;
				m_nContextMenuLastState = it->second.nState;
				m_nContextMenuLastCompany = it->second.nCompany;
				m_nContextMenuLastRNo = it->second.nRNo;
			}

		}
	}
	else
	{
		pRMenu->RemoveMenu(ID_SET_WORKING, MF_BYCOMMAND);
		pRMenu->RemoveMenu(ID_SET_LEAVE, MF_BYCOMMAND);
	}

	DWORD dwRetValue = pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	LU->GetRcpView()->SetRefreshStart();
	
}

void CAllocateBoardDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	if(pRecord == NULL)
		return;

	CXTPGridColumn *pColumn = pItemNotify->pColumn;
	if(pColumn == NULL)
		return;

	CMyRecordItem *pItem = (CMyRecordItem*)pRecord->GetItem(pColumn->GetIndex());
	if(pItem == NULL)
		return;
	
	m_pSelectedRecordItem = pItem;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

void CAllocateBoardDlg::OnUpdateColor()
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(!pItem->pAllocRiderInfo->bShareRiderHaveMyOrder)
	{
		CColorDlg dlg;
		dlg.m_nColor = pItem->pAllocRiderInfo->nRiderColor;
		dlg.m_nTextColor = pItem->pAllocRiderInfo->nRiderTextColor;
		dlg.m_nCarType = pItem->pAllocRiderInfo->nCarType;
		dlg.m_nRNo = pItem->pAllocRiderInfo->nRNo;
		dlg.m_sRName = pItem->pAllocRiderInfo->strName;

		if(dlg.DoModal() == IDOK)
		{
			if(dlg.m_nTextColor == 0) dlg.m_nTextColor = 1;
			if(dlg.m_nColor == 0) dlg.m_nColor = 1;

			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_rider_color");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRiderCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nColor);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nTextColor);

			if(!pRs.Execute(&pCmd)) return;

			pItem->pAllocRiderInfo->nRiderColor = dlg.m_nColor;
			pItem->pAllocRiderInfo->nRiderTextColor = dlg.m_nTextColor;
			m_wndReport.RedrawControl();
		}
	}
	else
	{	
		OnBnClickedAdditionalSettingBtn();	
	}
}

void CAllocateBoardDlg::OnShowRiderPos()
{
	if(m_pSelectedRecordItem)
	{
		CREATE_MODALESS(CRiderTraceMapDlg, this);
		CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
		pDlg->m_nCompany = pItem->pAllocRiderInfo->nCompany;
		pDlg->m_nRNo = pItem->pAllocRiderInfo->nRNo;
		SHOW_MODALESS(CRiderTraceMapDlg, this);
	}
}

void CAllocateBoardDlg::OnSetWorking()
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(IDYES == MessageBox("출근 처리 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
	{
		CMkCommand pCmd(m_pMkDb, "update_rider_attend_leave_state");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRiderCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
		if(pCmd.Execute())
		{
			UpdateRiderState();
		}
	}
}

void CAllocateBoardDlg::OnSetLeave()
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(IDYES == MessageBox("강제퇴근 처리를 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
	{
		if(LU->ForceLeavingWork(nRiderCompany, nRNo))
			UpdateRiderState();
	}
}

void CAllocateBoardDlg::OnShowRiderInfo()
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	LU->ShowRiderInfoDlg(pItem->pAllocRiderInfo->nCompany, pItem->pAllocRiderInfo->nRNo);
}

void CAllocateBoardDlg::UpdateRiderState()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_board_rider8");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_ci.m_nShareCode1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bOtherRiderHaveMyOrder);
	CMkParameter *parWorkReprt = pCmd.AddParameter(typeBool, typeOutput, sizeof(int), 0);

	if(pRs.Execute(&pCmd))
	{
		ALLOCATE_RIDER_MAP::iterator it;
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			long nCompany, nRNo, nCarType, nWorkReportState;
			COleDateTime dtWorkReport, dtLeave;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nMNo", nRNo);
			pRs.GetFieldValue("nWorkReportState", nWorkReportState);
			pRs.GetFieldValue("nCarType", nCarType);
			pRs.GetFieldValue("dtWorkReport", dtWorkReport);
			pRs.GetFieldValue("dtLeave", dtLeave);

			it = m_pRPM->m_mapRider.find(std::make_pair(nCompany, nRNo));
			if(it != m_pRPM->m_mapRider.end())
			{
				ALLOCATE_BOARD_RIDER_INFO *rider = (*it).second;
				rider->nWorkReportState = nWorkReportState;
				rider->nCarType = nCarType;
				rider->dtAttend = dtWorkReport;
				rider->dtLeave = dtLeave;
			}
			pRs.MoveNext();
		}
	}

	RefreshRiderList();
	RefreshList();
}

void CAllocateBoardDlg::FindProperRiderLinearType(CRect rcBase, long nTNo, long nCarType, long nStartPosX, long nStartPosY, 
												long nDestPosX, long nDestPosY,	BOOL bShareRider)
{
#define MAX_DISPLAY_COUNT			10
#define CUT_LINE_DISTANCE			30.0 //km

	m_rcFPBase = rcBase;
	m_nFPTNo = nTNo;
	m_nFPCarType = nCarType;
	m_nFPStartPosX = nStartPosX;
	m_nFPStartPosY = nStartPosY;
	m_nFPDestPosX = nDestPosX;
	m_nFPDestPosY = nDestPosY;

	m_vecProperRider.clear();
	DeleteAllDynWnd();

	int x = (m_ptMoved.x != -1) ? m_ptMoved.x : 50;
	int y = (m_ptMoved.x != -1) ? m_ptMoved.y : rcBase.Height() - 250;

	ALLOCATE_RIDER_MAP::iterator it;
	OrderRecordList &order = bShareRider ? m_mapShareRiderOrder : LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator itOrder;
	ALLOCATE_RIDER_MAP &mapRider = bShareRider ? m_mapShareRider : m_pRPM->m_mapRider;

	for(it = mapRider.begin(); it != mapRider.end(); it++)
	{
		if(it->second->nWorkReportState == 2)
			continue;

		if(it->second->dtPos >= (COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 20, 0)) ||
			it->second->bLogin)
		{
			it->second->fOrderDistance = m_poiNew.GetDistanceMeter(it->second->nPosX, it->second->nPosY, nStartPosX, nStartPosY) / 1000;
			m_vecProperRider.push_back(it->second);
		}
		else
		{
			it->second->fOrderDistance = 0;
		}
	}

	//스코어가 높은 순으로 정렬함
	std::sort(m_vecProperRider.begin(), m_vecProperRider.end(), compare_greator_rider_linear);

	if(m_vecProperRider.size() > 0)
	{
		int nCount = 0;
		ALLOCATE_RIDER_VECTOR::iterator it;
		for(it = m_vecProperRider.begin(); it != m_vecProperRider.end(); it++)
		{
			ALLOCATE_BOARD_RIDER_INFO *rider = *it;

			if((m_chkOnlyAuto.GetCheck() == BST_CHECKED) &&
				(rider->nCarType >1))
				continue;

			if(nCarType > 1) // 다마 이상은 다5마이상 기사만
			{
				if(rider->nCarType <= 1)
				{
					g_bana_log->Print("nRNo=%d, nCarType=%d, rider->CarType=%d\n", rider->nRNo, nCarType, rider->nCarType);
					continue;
				}
			} 

			if(m_cmbRiderGroup.GetCurSel() > 0)
			{
				if(rider->nAllocGroup != m_cmbRiderGroup.GetItemData(m_cmbRiderGroup.GetCurSel()))
				{
					continue; 
				}
			}

			//커트라인에 따라서 표시할갯수를 조절함
			if(rider->fOrderDistance < CUT_LINE_DISTANCE)
			{
				if(nCount == (MAX_DISPLAY_COUNT / 2))
				{
					x = (m_ptMoved.x != -1) ? m_ptMoved.x : 50;
					y += 160;
				}

				FlashRider(rider, TRUE, rcBase, CPoint(x, y), bShareRider, (nCount == 0));
				x+= 190;
				nCount++;
			}

			if(nCount >= MAX_DISPLAY_COUNT)
				break;
		}

		//타기사보기 board
		ALLOCATE_BOARD_RIDER_INFO rider;
		rider.nCompany = bShareRider ? AB_MY_RIDER : AB_SHARE_RIDER;
		rider.nRNo = bShareRider ? AB_MY_RIDER : AB_SHARE_RIDER;
		FlashRider(&rider, TRUE, rcBase, CPoint(x, y), bShareRider);
	}
}

BOOL CAllocateBoardDlg::OnEraseBkgnd(CDC* pDC)
{
	FillForm(pDC);
	return CMyDialog::OnEraseBkgnd(pDC);
}


void CAllocateBoardDlg::DeleteAllDynWnd()
{
	DYN_WND_MAP::iterator it;
	for(it = m_mapDynWnd.begin(); it != m_mapDynWnd.end(); it++)
	{
		::PostMessage(it->second->GetSafeHwnd(), WM_CLOSE, 0, 0);
	}
}

void CAllocateBoardDlg::OnSMSAllocate()
{
	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo; 

	CMkCommand pCmd(m_pMkDb, "update_rider_allocate_type_simple_1");
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(1);
	if(pCmd.Execute())
	{
		MessageBox("SMS배차로 변경되었습니다.", "확인", MB_ICONINFORMATION);
	}
}

void CAllocateBoardDlg::OnPDAAllocate()
{
	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	CMkCommand pCmd(m_pMkDb, "update_rider_allocate_type_simple_1");
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(2);
	if(pCmd.Execute())
	{
		MessageBox("PDA배차로 변경되었습니다.", "확인", MB_ICONINFORMATION);
	}
}

void CAllocateBoardDlg::GetAdditionalSetting()
{
	m_bFinishTest = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "FinishTest", 0);
	m_bLinearType = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "LinearType", 0);
	m_bOtherRiderHaveMyOrder = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "HaveMyOrder", m_ci.HasShareCompany());
	m_bOtherRiderHaveMyOrderSplitSort = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "HaveMyOrderSplitSort", m_ci.HasShareCompany());
	m_nAL = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AL", ""));
	m_nPL = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PL", ""));
	m_nAG = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AG", ""));
	m_nPG = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PG", ""));
	m_nAL2 = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AL2", ""));
	m_nPL2 = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PL2", ""));
	m_nAG2 = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AG2", ""));
	m_nPG2 = atol(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PG2", ""));
	m_crDelayRiderBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "DelayBackColor", RGB(255, 200, 200));
	m_crOtherOrderText = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherOrderTextColor", RGB(0, 0, 0));
	m_crOtherOrderBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherOrderBackColor", RGB(255, 255, 255));
	m_crOtherRiderText = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherRiderTextColor", RGB(255, 255, 255));
	m_crOtherRiderBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherRiderBackColor", RGB(102, 102, 153));

	m_pRPM->m_crDelayRiderBack = m_crDelayRiderBack;
	m_pRPM->m_crOtherOrderText = m_crOtherOrderText;
	m_pRPM->m_crOtherOrderBack = m_crOtherOrderBack;
	m_pRPM->m_crOtherRiderText = m_crOtherRiderText;
	m_pRPM->m_crOtherRiderBack = m_crOtherRiderBack;
	m_pRPM->SetLinearType(m_bLinearType);
}

void CAllocateBoardDlg::OnBnClickedAdditionalSettingBtn()
{
	CAllocateBoardSettingDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetAdditionalSetting();
		if(dlg.m_bNeedRefresh)
			RefreshRiderList();
	}
}

void CAllocateBoardDlg::GetShareRiderOrderList()
{
	m_mapShareRiderOrder.clear();

	ALLOCATE_RIDER_MAP::iterator it;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_rider_order_list");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel()));
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nShareCode1);
	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			OrderRecord order;
			CString strSDong, strDDong;
			COleDateTime dt2;

			pRs.GetFieldValue("nCompany", order.nCompany);
			pRs.GetFieldValue("nRiderCompany", order.nRiderCompany);
			pRs.GetFieldValue("nRNo", order.nRNo);
			pRs.GetFieldValue("nState", order.nState);
			pRs.GetFieldValue("sSDong", strSDong);
			pRs.GetFieldValue("sDDong", strDDong);
			pRs.GetFieldValue("nChargeSum", order.nCharge);
			pRs.GetFieldValue("nWayType", order.nWayType);
			pRs.GetFieldValue("dt1", order.dtRcp);
			pRs.GetFieldValue("dt2", dt2);
			pRs.GetFieldValue("dt3", order.dt3);
			pRs.GetFieldValue("dt4", order.dt4);
			pRs.GetFieldValue("dtFinal", order.dtFinal);
			pRs.GetFieldValue("nStartRealDongID", order.nStartRealDongID);
			pRs.GetFieldValue("nDestRealDongID", order.nDestRealDongID);
			pRs.GetFieldValue("nTNo", order.nTNo);
			pRs.GetFieldValue("nStartPosX", order.nStartPosX);
			pRs.GetFieldValue("nStartPosY", order.nStartPosY);
			pRs.GetFieldValue("nDestPosX", order.nDestPosX);
			pRs.GetFieldValue("nDestPosY", order.nDestPosY);
			pRs.GetFieldValue("nTNo", order.nTNo);

			order.strStart = strSDong;
			order.strDest = strDDong;

			if(order.nState == 11)
				order.dtState = dt2;
			else if(order.nState == 30 )
				order.dtState = order.dt3;
			else if(order.nState == 31 )
				order.dtState = order.dt4;
			else if(order.nState == 35)
				order.dtState = order.dtFinal;
			else
				order.dtState = order.dtRcp;

			m_mapShareRiderOrder.insert(OrderRecordList::value_type(order.nTNo, order));

			it = m_mapShareRider.find(make_pair(order.nRiderCompany, order.nRNo));

			if(it != m_mapShareRider.end())
			{
				if(order.nState <= 30)
					it->second->nAllocCount++;
				else if(order.nState == 31)
					it->second->nPickupCount++;

				it->second->nTotalCount++;
			}

			pRs.MoveNext();
		}
	}
}

void CAllocateBoardDlg::ShowProperRider(long nType)
{
	if(nType == AB_SHARE_RIDER)
	{
		GetRiderList(TRUE);
		GetShareRiderOrderList();
	}

	FindProperRiderLinearType(m_rcFPBase, m_nFPTNo, m_nFPCarType, m_nFPStartPosX, m_nFPStartPosY, 
				m_nFPDestPosX, m_nFPDestPosY, nType == AB_SHARE_RIDER);
}

void CAllocateBoardDlg::SetRiderWorkReport(long nCompany, long nRNo, int nState)
{
	ALLOCATE_RIDER_MAP::iterator itRider;

	itRider = m_pRPM->m_mapRider.find(std::make_pair(nCompany, nRNo));
	if(itRider != m_pRPM->m_mapRider.end())
	{
		ALLOCATE_BOARD_RIDER_INFO *rider = (*itRider).second;
		if(nState == 1)
		{
			rider->nWorkReportState = nState;
			rider->dtAttend = COleDateTime::GetCurrentTime();
		}
		else if(nState == 2)
		{
			rider->nWorkReportState = nState;
			rider->dtLeave = COleDateTime::GetCurrentTime();
		}
	}

	m_wndReport.RedrawControl();
}

void CAllocateBoardDlg::OnBnClickedShowOnlyConnRider()
{
	OnBnClickedRefreshBtn();
}

void CAllocateBoardDlg::OnAllocateState()
{
	LU->GetRcpView()->GetStateChange()->CompleteState(m_nContextMenuLastCompany, m_nContextMenuLastOrder, m_nContextMenuLastRNo, m_nContextMenuLastState);
}

void CAllocateBoardDlg::OnFinishState()
{
	LU->GetRcpView()->GetStateChange()->FinishState(m_nContextMenuLastOrder, m_nContextMenuLastState);
}

void CAllocateBoardDlg::OnWaitState()
{
	LU->GetRcpView()->GetStateChange()->CancelAllocateToWait(m_nContextMenuLastOrder, m_nContextMenuLastState);
}

void CAllocateBoardDlg::OnRcpState()
{
	LU->GetRcpView()->GetStateChange()->CancelAllocate(m_nContextMenuLastOrder, m_nContextMenuLastState);
}

void CAllocateBoardDlg::OnEditOrder()
{
	LU->GetRcpView()->EditOrderFromTNo(m_nContextMenuLastOrder);
}

void CAllocateBoardDlg::OnPickupState()
{
	LU->GetRcpView()->GetStateChange()->PickupState(m_nContextMenuLastCompany, m_nContextMenuLastOrder, m_nContextMenuLastRNo, m_nContextMenuLastState);
}

void CAllocateBoardDlg::OnCancelState()
{
	CString strCancel;
	long nCancelType = 11, nPenaltyMin = 0, nPenaltyCharge = 0;
	CBranchInfo *pBi = LF->GetBranchInfo(m_nContextMenuLastCompany);

	if(pBi->bCancelReason)
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

		dlg.m_nTNo = m_nContextMenuLastOrder;
		dlg.m_nCompany = m_nContextMenuLastCompany;
		dlg.m_psaCancel = &saCancel;
		dlg.m_strCustomerPhone = "";
		dlg.m_nOrderCompany = m_nContextMenuLastCompany;

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

	LU->GetRcpView()->GetStateChange()->CancelOrder(m_nContextMenuLastCompany, m_nContextMenuLastOrder, m_nContextMenuLastState, 
		strCancel, nCancelType, nPenaltyMin, nPenaltyCharge);
}

void CAllocateBoardDlg::OnShowAll()
{
    ChangeShowType(0);
}

void CAllocateBoardDlg::OnShowShareCode()
{
	ChangeShowType(1);
}

void CAllocateBoardDlg::OnShowBranch()
{
	ChangeShowType(2);
}

void CAllocateBoardDlg::ChangeShowType(long nType)
{
	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo; 

	CMkCommand pCmd(m_pMkDb, "update_rider_show_type");
	pCmd.AddParameter(nType);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);

	if(!pCmd.Execute()) return;

	CString sTemp;

	if(nType == 0) sTemp = "[공유오더보기]";
	else if(nType == 1) sTemp = "[자사오더만보기(1차)]";
	else if(nType == 2) sTemp = "[소속오더만보기(지사)]";

	sTemp += "로 변경되었습니다.";

	MessageBox(sTemp, "확인", MB_ICONINFORMATION);
}

void CAllocateBoardDlg::OnSendMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	CMyRecordItem *pItem = (CMyRecordItem*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo; 

	MSG_RIDER_INFO *pInfo = new MSG_RIDER_INFO;
	CRiderMsgDlg dlg;
	dlg.SetIntegrated(m_ba.GetCount() > 2);
	dlg.SetCompanyCode(m_ci.m_nCompanyCode);
	pInfo->nCompany = nRiderCompany;
	pInfo->nRNo = nRNo;
	dlg.m_paSelected.Add((MSG_RIDER_INFO*)pInfo);
	dlg.DoModal();
	delete pInfo;
}

BOOL CAllocateBoardDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return CMyDialog::OnCommand(wParam, lParam);
}
