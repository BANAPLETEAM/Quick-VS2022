// ConnListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ConnListDlg2.h"
#include "RiderMsgDlg.h"
#include "MyReportPaintManager.h"
#include "VirtualRecord.h"
#include "RcpView.h"
#include "ColumnSelDlg.h"
#include "SubwayAbsentDlg.h"
#include "AllocGroupListDlg.h"

// CConnListDlg2 대화 상자입니다.

IMPLEMENT_DYNCREATE(CConnListDlg2, CMyFormView)
CConnListDlg2::CConnListDlg2()
: CMyFormView(CConnListDlg2::IDD)
{
	//	m_pParentWnd = pParent;
	m_bAsc = TRUE;
	m_nSubItem = 1;
	m_dwLastRefreshList = 0;
	m_pAllocGroupListDlg = NULL;
}

CConnListDlg2::~CConnListDlg2()
{
	DELETE_OBJECT(m_pAllocGroupListDlg);
	m_List.SaveReportOrder("CConnListDlg2", "m_List");
}


void CConnListDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PDA_CONN_LIST, m_List);
	DDX_Control(pDX, IDC_SEND_MSG_BTN, m_SendMsgBtn);
	DDX_Control(pDX, IDC_CLOSE_BUTTON, m_CloseBtn);
	DDX_Control(pDX, IDC_ALLOCATE_COMBO, m_cmbAllocate);
	DDX_Control(pDX, IDC_RIDER_COMBO, m_cmbRider);
	DDX_Control(pDX, IDC_RIDER_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_LOCATION_EDIT, m_edtLocation);
	DDX_Control(pDX, IDC_CAR_COMBO, m_cmbCar);
	DDX_Control(pDX, IDC_ALLOC_EDIT, m_edtAlloc);
}

BEGIN_MESSAGE_MAP(CConnListDlg2, CMyFormView)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, OnBnClickedSendMsgBtn)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(XTP_NM_GRID_HEADER_RCLICK, IDC_PDA_CONN_LIST, OnReportColumnRClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VISIBLE_COL, OnVisibleCol)
	ON_CBN_SELCHANGE(IDC_ALLOCATE_COMBO, &CConnListDlg2::OnCbnSelchangeAllocateCombo)
	ON_CBN_SELCHANGE(IDC_RIDER_COMBO, &CConnListDlg2::OnCbnSelchangeRiderCombo)
	ON_EN_CHANGE(IDC_RIDER_EDIT, &CConnListDlg2::OnEnChangeRiderEdit)
	ON_EN_CHANGE(IDC_LOCATION_EDIT, &CConnListDlg2::OnEnChangeLocationEdit)
	ON_COMMAND(ID_SET_WORKING, OnSetWorking)
	ON_COMMAND(ID_SET_LEAVE, OnSetLeave)
	ON_COMMAND(ID_SEND_MSG, OnSendMsg)	
	ON_COMMAND(ID_SHOW_RIDER_INFO, OnShowRiderInfo)	
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_SUBWAY_ABSENT, OnSubWayAbsent)
	ON_NOTIFY(NM_CLICK, IDC_PDA_CONN_LIST, OnReportItemClick)
	ON_CBN_SELCHANGE(IDC_CAR_COMBO, &CConnListDlg2::OnCbnSelchangeCarCombo)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CConnListDlg2::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	if(LU->GetRcpView())
	{
		CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

		if(pRecord == NULL)
			return;

		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		if(st)
			LU->GetRcpView()->RefreshList("", "", NULL, FALSE, TRUE, st->nCompany, st->nRNo);
	}
}

void CConnListDlg2::OnVisibleCol()
{ 
	CColumnSelDlg dlg;
	dlg.m_plstReport = (CXTPListCtrl2*)&m_List;
	dlg.m_sClass = "CConnListDlg2";
	dlg.m_sList = "m_List";

	if(dlg.DoModal())
	{
		m_List.LoadReportOrder(dlg.m_sClass, dlg.m_sList);
		m_List.Populate();
	}
}

void CConnListDlg2::HideAllocList()
{
	if(m_pAllocGroupListDlg)
		m_pAllocGroupListDlg->ShowWindow(FALSE);
}

void CConnListDlg2::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	LU->m_pConnListPane = this;

	CMyFormView::OnInitialUpdate();

	m_edtRNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRNo.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "사번/기사명");
	m_edtLocation.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtLocation.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "구/군/동");
	m_edtAlloc.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAlloc.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "배차그룹");

	m_List.InsertColumn(0, "No", LVCFMT_CENTER, 27);
	m_List.InsertColumn(1, "기사소속", LVCFMT_LEFT, 65);
	m_List.InsertColumn(2, "사번", LVCFMT_RIGHT, 45);
	m_List.InsertColumn(3, "기사명", LVCFMT_LEFT, 50);
	m_List.InsertColumn(4, "접속", LVCFMT_CENTER, 45);
	m_List.InsertColumn(5, "구/군", LVCFMT_LEFT, 60);
	m_List.InsertColumn(6, "동", LVCFMT_LEFT, 60);
	m_List.InsertColumn(7, "설정위치", LVCFMT_LEFT, 150);
	m_List.InsertColumn(8, "총건수", LVCFMT_RIGHT, 50);
	m_List.InsertColumn(9, "운행건수", LVCFMT_RIGHT, 58);
	m_List.InsertColumn(10, "운행요금", LVCFMT_RIGHT, 58);
	m_List.InsertColumn(11, "충전금", LVCFMT_RIGHT, 60);
	m_List.InsertColumn(12, "출근", LVCFMT_RIGHT, 50);
	m_List.InsertColumn(13, "대기", LVCFMT_RIGHT, 40);
	m_List.AddFooterRows();
	
	m_List.SetOrderIndexCol(0);
	m_List.Populate();

	LU->MakeAllocateGroupCombo(&m_cmbAllocate, TRUE);
	m_cmbAllocate.SetCurSel(ZERO);
	m_cmbRider.SetCurSel(ZERO);
	m_cmbCar.SetCurSel(ZERO);

	this->GetParentFrame()->GetActiveFrame()->ShowWindow(SW_HIDE);
	this->GetParentFrame()->ShowWindow(SW_HIDE);

	m_List.LoadReportOrder("CConnListDlg2", "m_List");

	SetResize(IDC_PDA_CONN_LIST, sizingRightBottom);
	SetTimer(100, 1000, NULL);
}

void CConnListDlg2::DeleteMapData()
{
	CONN_RIDER_MAP::iterator it;

	for(it = m_mapConn.begin(); it != m_mapConn.end(); it++)
	{
		CONN_RIDER_STRUCT *st = it->second;

		if(st)
		{
			delete st;
			st = NULL;
		}
	}
}

void CConnListDlg2::RefreshList(BOOL bDb)
{
	if(!m_List.GetSafeHwnd()) return;

	RefreshMap();

	UpdateDrivingCount();
	RefreshListReal();
	FilterList();
	m_List.SetFooterMessage(GetFooterData());
}

CString CConnListDlg2::GetFooterData()
{
	CXTPGridRecords *pRecords = m_List.GetRecords(); 
	long nAllCount = pRecords->GetCount();

	long nRcpCount = ZERO, nAbsentCount = ZERO, nNotAbsentCount = ZERO, nOutCount = ZERO;
	long nAuto = ZERO, nCar = ZERO;

	//전체;접속;출근;미출근;퇴근;

	for(int i=0; i<nAllCount; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CONN_RIDER_STRUCT *pInfo = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		if(pInfo)
		{
			if(pInfo->dtConn.m_status != TWO)
				nRcpCount++;

			// st->nWorkStateReport //1 -- 출근처리	//2 -- 퇴근처리 //3 -- 강제퇴근 //0 -- 미출근

			if(pInfo->nWorkReportState == ONE)
				nAbsentCount++;
			if(pInfo->nWorkReportState == ZERO)
				nNotAbsentCount++;
			if(pInfo->nWorkReportState == TWO || pInfo->nWorkReportState == THREE)
				nOutCount++;

			//enum {CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK, CAR_SUBWAY = 10, CAR_PS = 20}; //CAR_PARCEL_SERVICE

			if(pInfo->nCarType == CAR_AUTO || pInfo->nCarType == CAR_BIGBIKE)
				nAuto++;
			else if(pInfo->nCarType == CAR_DAMA || pInfo->nCarType == CAR_LABO ||
				pInfo->nCarType == CAR_VAN || pInfo->nCarType == CAR_TRUCK)
				nCar++;
		}
	}

	CString sTemp = ""; 
	sTemp.Format("전체 %d  |  접속 %d  |  출근 %d  |  미출근 %d |  퇴근 %d     오토 %d | 차량 %d", nAllCount, nRcpCount, nAbsentCount, nNotAbsentCount, nOutCount, nAuto, nCar);


	//전체;접속;출근;미출근;퇴근;

	return sTemp;	
}


void CConnListDlg2::RefreshMap()
{
	DeleteMapData();
	m_mapConn.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, ".select_conn_list_2011_3");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{	
		CONN_RIDER_STRUCT *st = new CONN_RIDER_STRUCT;
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("nRNo", st->nRNo);
		pRs.GetFieldValue("dtConn", st->dtConn);
		pRs.GetFieldValue("sName", st->strName);
		pRs.GetFieldValue("sGugun", st->strGugun);
		pRs.GetFieldValue("sDong", st->strDong);
		pRs.GetFieldValue("sPosName", st->strPosName);
		pRs.GetFieldValue("nBalance", st->nBalance);
		pRs.GetFieldValue("nAllocGroup", st->nAllocGroup);
		pRs.GetFieldValue("nWorkReportState", st->nWorkReportState);
		pRs.GetFieldValue("dtWorkReport", st->dtWorkState);
		pRs.GetFieldValue("nCarType", st->nCarType);
		pRs.GetFieldValue("sSubwayLocation", st->strSubwayLocation);
		pRs.GetFieldValue("dtSubwayLocation", st->dtSubwayLocation);
		pRs.GetFieldValue("bRcpIntMode1", st->bRcpIntMode1);

		st->strPreSubwayLocation = st->strSubwayLocation;

		st->nAllCount = ZERO; 
		st->nDrivingCount = ZERO;
		st->nDrivingCharge = ZERO;

		if(st->nWorkReportState == ONE)
			st->dtWait = st->dtWorkState;
			//st->dtWait = st->dtSubwayLocation;
			//st->dtWait = st->dtWorkState;

		if(st->dtSubwayLocation.m_status != 2)
		{
			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - st->dtSubwayLocation;

			if(span.GetTotalMinutes() > 60)
				st->strSubwayLocation = "";			
		}

		m_mapConn.insert(CONN_RIDER_MAP::value_type(make_pair(st->nCompany, st->nRNo), st));

		pRs.MoveNext();
	}	
}

void CConnListDlg2::UpdateDrivingCount()
{
	if(m_mapConn.size() <= ZERO)
		return;

	if(LU->GetRcpView() == NULL)
		return;

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		long nState = it->second.nState;
		if(nState >= STATE_OK_ONLY_MAN && 
			nState <= STATE_FINISH)
		{
			CONN_RIDER_MAP::iterator itConn;
			itConn = m_mapConn.find(make_pair(it->second.nRiderCompany, it->second.nRNo));

			if(itConn != m_mapConn.end())
			{
				CONN_RIDER_STRUCT *st = itConn->second;
				st->nAllCount++;
				st->nDrivingCharge += it->second.nCharge;
	 
				if(nState != STATE_FINISH)
				{
					if(st->dtAllocate.m_status != 2)
					{
						if(it->second.dt3 > st->dtAllocate)
						{
							st->dtAllocate = it->second.dt3;
							st->strAllocate = CString(it->second.strDest.c_str()) +"(배," + CString(it->second.strStart.c_str()) + "->" + CString(it->second.strDest.c_str()) + ")";
						}
					}
					else
					{
						st->dtAllocate = it->second.dt3;
						st->strAllocate = CString(it->second.strDest.c_str()) +"(배," + CString(it->second.strStart.c_str()) + "->" + CString(it->second.strDest.c_str()) + ")";

					}
					
					st->nDrivingCount++;
				}
				else
				{
					if(it->second.dtFinal.m_status == TWO)
						st->dtWait = it->second.dtFinal;
					else 
					{
						if(it->second.dtFinal > st->dtWait)
							st->dtWait = it->second.dtFinal;
					}

					if(st->dtSubwayLocation.m_status != 2)
					{
						if(st->dtSubwayLocation < st->dtWait)
						{
							if(st->strSubwayLocation.IsEmpty())
								st->strSubwayLocation = CString(it->second.strDest.c_str()) +"(종," + CString(it->second.strStart.c_str()) + "->" + CString(it->second.strDest.c_str()) + ")";
							else
								st->strSubwayLocation = st->strSubwayLocation +"(" + CString(it->second.strStart.c_str()) + "->" + CString(it->second.strDest.c_str()) + ")";
						}
					}
				}
			}
		}
	}
}

typedef struct{
	long nCompany;
	long nRNo;
	long nWorkReportState;
	long nWait;
} STRUCT_RIDER_SORT;

typedef struct{
	long nCompany;
	long nRNo;
	long bRcpIntMode1;
} ST_RIDER_SORT1;


bool compare_rider_state(ST_RIDER_SORT1 elem1, ST_RIDER_SORT1 elem2)
{
	if(elem1.bRcpIntMode1 == elem2.bRcpIntMode1)
	{
		if(elem1.nCompany == elem2.nCompany)
			return elem1.nRNo < elem2.nRNo;
		else
			return elem1.nCompany < elem2.nCompany;
	}
	else
		return elem1.bRcpIntMode1 > elem2.bRcpIntMode1;
}

bool compare_wait_state(STRUCT_RIDER_SORT elem1, STRUCT_RIDER_SORT elem2)
{
	if(elem1.nWorkReportState == elem2.nWorkReportState)
	{
		return elem1.nWait < elem2.nWait;
	}
	else
	{
		return elem1.nWorkReportState > elem2.nWorkReportState;
	}
}

void CConnListDlg2::RefreshListRealSubway()
{
	m_List.DeleteAllItems();

	vector<STRUCT_RIDER_SORT> vec;

	CONN_RIDER_MAP::iterator itConn;
	for(itConn = m_mapConn.begin(); itConn != m_mapConn.end(); itConn++)
	{
		CONN_RIDER_STRUCT *st = itConn->second;
		STRUCT_RIDER_SORT stSort;
		stSort.nCompany = st->nCompany;
		stSort.nRNo = st->nRNo;
		stSort.nWait = GetSubWayWaitInt(st);

		if(st->nWorkReportState == 1 && st->nDrivingCount == 0)
			stSort.nWorkReportState = 100;
		else if(st->nWorkReportState == 1)
			stSort.nWorkReportState = 99;
		else if(st->nWorkReportState == 0 && st->nDrivingCount == 0)
			stSort.nWorkReportState = 98;
		else
			stSort.nWorkReportState = 0;
	
		vec.push_back(stSort);
	}

	std::sort(vec.begin(), vec.end(), compare_wait_state);

	long nSize = vec.size();
	long nCount = 0;
	char buffer[10];

	for(int i=0; i<nSize; i++)
	{
		STRUCT_RIDER_SORT stSort = vec.at(i);
		CONN_RIDER_MAP::iterator itConn = m_mapConn.find(make_pair(stSort.nCompany, stSort.nRNo));

		if(itConn == m_mapConn.end())
			return;

		CONN_RIDER_STRUCT *st = itConn->second;

		m_List.InsertItem(nCount, itoa(nCount + 1, buffer, 10));
		m_List.SetItemText(nCount, 1, LF->GetBranchInfo(st->nCompany)->strBranchName);
		m_List.SetItemText(nCount, 2, itoa(st->nRNo, buffer, 10));
		m_List.SetItemText(nCount, 3, st->strName);
		m_List.SetItemText(nCount, 4, st->dtConn.Format("%H:%M"));
		m_List.SetItemText(nCount, 5, st->strGugun);
		m_List.SetItemText(nCount, 6, st->strDong);
		m_List.SetItemText(nCount, 7, GetLocationConsiderSunway(st));
		m_List.SetItemText(nCount, 8, LF->GetMyNumberFormat(st->nAllCount));
		m_List.SetItemText(nCount, 9, LF->GetMyNumberFormat(st->nDrivingCount));
		m_List.SetItemText(nCount, 10, LF->GetMyNumberFormat(st->nDrivingCharge));
		m_List.SetItemText(nCount, 11, LF->GetMyNumberFormat(st->nBalance));
		m_List.SetItemText(nCount, 12, GetAbsentState(st));
		m_List.SetItemText(nCount, 13, GetSubWayWait(st));

		m_List.SetItemData(nCount, (DWORD_PTR)st);	
		nCount++;
	}
}

void CConnListDlg2::RefreshListReal()
{
	if(m_mapConn.size() <= ZERO)
		return;

	if(m_cmbCar.GetCurSel() == 3)//지하철
	{
		RefreshListRealSubway();
		return;
	}

	m_List.DeleteAllItems();
	long nCount = 0;
	char buffer[10];

	vector<ST_RIDER_SORT1> vec;

	CONN_RIDER_MAP::iterator itConn;
	for(itConn = m_mapConn.begin(); itConn != m_mapConn.end(); itConn++)
	{
		CONN_RIDER_STRUCT *st = itConn->second;
		ST_RIDER_SORT1 stSort;
		stSort.nCompany = st->nCompany;
		stSort.nRNo = st->nRNo;
		stSort.bRcpIntMode1 = st->bRcpIntMode1;

		vec.push_back(stSort);
	}

	std::sort(vec.begin(), vec.end(), compare_rider_state);

	long nSize = vec.size();
	
	for(int i=0; i<nSize; i++)
	//for(itConn = m_mapConn.begin(); itConn != m_mapConn.end(); itConn++)
	{
		ST_RIDER_SORT1 st1 = vec.at(i);

		itConn = m_mapConn.find(std::make_pair(st1.nCompany, st1.nRNo));

		if(itConn == m_mapConn.end())
			continue;

		CONN_RIDER_STRUCT *st = itConn->second;

		m_List.InsertItem(nCount, itoa(nCount + 1, buffer, 10));
		m_List.SetItemText(nCount, 1, LF->GetBranchInfo(st->nCompany)->strBranchName);
		m_List.SetItemText(nCount, 2, itoa(st->nRNo, buffer, 10));
		m_List.SetItemText(nCount, 3, st->strName);
		m_List.SetItemText(nCount, 4, st->dtConn.Format("%H:%M"));
		m_List.SetItemText(nCount, 5, st->strGugun);
		m_List.SetItemText(nCount, 6, st->strDong);
		m_List.SetItemText(nCount, 7, GetLocationConsiderSunway(st));
		m_List.SetItemText(nCount, 8, LF->GetMyNumberFormat(st->nAllCount));
		m_List.SetItemText(nCount, 9, LF->GetMyNumberFormat(st->nDrivingCount));
		m_List.SetItemText(nCount, 10, LF->GetMyNumberFormat(st->nDrivingCharge));
		m_List.SetItemText(nCount, 11, LF->GetMyNumberFormat(st->nBalance));
		m_List.SetItemText(nCount, 12, GetAbsentState(st));
		m_List.SetItemText(nCount, 13, GetSubWayWait(st));

			
		m_List.SetItemData(nCount, (DWORD_PTR)st);

		//1 -- 출근처리
		//	2 -- 퇴근처리
		//	3 -- 강제퇴근 
		//	0 -- 미출근

		nCount++;
	}

	m_List.Populate();
}

CString CConnListDlg2::GetLocationConsiderSunway(CONN_RIDER_STRUCT *st)
{
	if(st->nCarType != CAR_SUBWAY)
		return st->strPosName;
	else
	{
		if(st->dtWait > st->dtAllocate)
			return st->strSubwayLocation;
		else
			return st->strAllocate;
	}
}

CString CConnListDlg2::GetAbsentState(CONN_RIDER_STRUCT *st)
{
	if(st->nWorkReportState == ZERO)
		return "미출근";
	else if(st->nWorkReportState == ONE)
		return "";
	else if(st->nWorkReportState == TWO)
		return "퇴근";
	else if(st->nWorkReportState == THREE)
		return "퇴근";

	return "";
}

long CConnListDlg2::GetSubWayWaitInt(CONN_RIDER_STRUCT *st)
{
	if(st->nCarType != CAR_SUBWAY)
		return 0;

	if(st->nWorkReportState != ONE)
		return 0;

	if(st->dtWait.m_status == TWO)
		return 0;

	if(st->nDrivingCount > 0)
		return 0;

	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	COleDateTimeSpan span = dtCur - st->dtWait;

	return span.GetTotalMinutes();
}

CString CConnListDlg2::GetSubWayWait(CONN_RIDER_STRUCT *st)
{
	if(st->nCarType != CAR_SUBWAY)
		return "";

	if(st->nWorkReportState != ONE)
		return "";

	if(st->dtWait.m_status == TWO)
		return "";

	if(st->nDrivingCount > 0)
		return "";

	char buffer[10];
	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	COleDateTimeSpan span = dtCur - st->dtWait;
	
	return itoa(span.GetTotalMinutes(), buffer, 10);
}
/*
void CConnListDlg2::OnClose()
{
	m_pParentWnd->PostMessage(WM_CLOSE_CONN_LIST_DLG, 0, 0);
	CDialog::OnClose();
}
*/


void CConnListDlg2::OnBnClickedSendMsgBtn()
{
	return ;

	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	CRiderMsgDlg dlg;
	dlg.SetIntegrated(m_bIntegrated);
	dlg.SetCompanyCode(m_nCompanyCode);

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++) 
	{
		MSG_RIDER_INFO *pMRI = new MSG_RIDER_INFO;

		CXTPGridRow *pRow = (CXTPGridRow*)m_List.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);
		
		pMRI->nCompany = st->nCompany;
		pMRI->nRNo = st->nRNo;
		dlg.m_paSelected.Add(pMRI);
	}

	dlg.DoModal();


	for(int i = 0; i < dlg.m_paSelected.GetCount(); i++)
	{
		MSG_RIDER_INFO *pMRI = dlg.m_paSelected.GetAt(i);
		delete pMRI;
	}
}

void CConnListDlg2::OnBnClickedCloseButton()
{
	OnClose();
}

void CConnListDlg2::OnTimer(UINT nIDEvent)
{

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(100 == nIDEvent)
	{
		KillTimer(nIDEvent);

		if(!LU->m_pwndPane2->IsFocus() && IsWindowVisible())
		{
			this->GetParentFrame()->SendMessageToDescendants(WM_PAINT, 0, 0, TRUE, TRUE);
			this->GetParentFrame()->GetActiveFrame()->Invalidate();
			if((::GetTickCount() - m_dwLastRefreshList) > 60*1000 )
			{
				RefreshList();
				this->Invalidate();
				m_dwLastRefreshList = GetTickCount();
			}
		}

		SetTimer(nIDEvent,1000,NULL);
	}

	CMyFormView::OnTimer(nIDEvent);
}


void CConnListDlg2::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CConnListDlg2::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CPoint pt;
	::GetCursorPos(&pt);

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	menu.AppendMenu(MF_STRING, ID_VISIBLE_COL, "컬럼숨김");
	menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
}

void CConnListDlg2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPGridColumn *p = m_List.GetColumns()->GetAt(0); 
	if(p == NULL) return; 
  
	#define COLUMN_HEIGHT 18

	long h = m_List.GetReportHeader()->GetGroupByHeight();
		
	CRect rcHeader = p->GetRect(); 
	//ScreenToClient(rcHeader);

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = NULL;

	if(point.y >= rect.top && 
		//point.y <= rect.top + rcHeader.Height())
		//point.y <= rect.top + h )
		point.y <= rect.top + COLUMN_HEIGHT )
	{
		pRMenu=rMenu.GetSubMenu(22);
	} 
	else
		pRMenu=rMenu.GetSubMenu(28);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CConnListDlg2::OnCbnSelchangeRiderCombo()
{
	FilterList();
}

void CConnListDlg2::OnCbnSelchangeAllocateCombo()
{
	FilterList();
}

void CConnListDlg2::OnEnChangeRiderEdit()
{
	FilterList();
}

void CConnListDlg2::OnEnChangeLocationEdit()
{
	FilterList();
}

void CConnListDlg2::FilterList()
{
	vector<long> vec;

	if(m_pAllocGroupListDlg)
	{
		CXTPGridRecords *pRecords = m_pAllocGroupListDlg->m_lstAlloc.GetRecords();

		if(((CAllocGroupRecord*)(pRecords->GetAt(0)))->GetCheck() == FALSE) //전체검색이 아닐시
		{
			for(int i=1; i<pRecords->GetCount(); i++)
			{
				if(((CAllocGroupRecord*)(pRecords->GetAt(i)))->GetCheck())
					vec.push_back(((CAllocGroupRecord*)(pRecords->GetAt(i)))->m_nItem);
			}
		}		
	}
		

	CString strShRNo; m_edtRNo.GetWindowText(strShRNo);
	CString strShLocation; m_edtLocation.GetWindowText(strShLocation);
	long nAllocGroup = m_cmbAllocate.GetCurSel() - 1;
	long nWorkReportState = m_cmbRider.GetCurSel();
	long nCar = m_cmbCar.GetCurSel();

	CXTPGridRecords *pRecords = m_List.GetRecords();
	long nCount = pRecords->GetCount();

	long nRNo = -1;
	if(LF->IsNumeric(strShRNo))
		nRNo = atoi(strShRNo);
 
	for(int i=ZERO; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		// st->nWorkStateReport //1 -- 출근처리	//2 -- 퇴근처리 //3 -- 강제퇴근 //0 -- 미출근

		//전체;접속+출근;접속;출근;미출근;퇴근;
		if((nWorkReportState == ONE && (st->dtConn.m_status == TWO && st->nWorkReportState != ONE)) || 
			(nWorkReportState == TWO && st->dtConn.m_status == TWO) || 
			(nWorkReportState == THREE && st->nWorkReportState != ONE) ||
			(nWorkReportState == FOUR && st->nWorkReportState != ZERO) ||
			(nWorkReportState == FIVE && st->nWorkReportState != TWO && st->nWorkReportState != THREE))
		{
			pRecord->SetVisible(FALSE);
			continue; 
		}
 
		if((nCar == ONE && st->nCarType != CAR_AUTO && st->nCarType != CAR_BIGBIKE) ||
			(nCar == TWO && st->nCarType != CAR_DAMA && st->nCarType != CAR_LABO && st->nCarType != CAR_VAN && st->nCarType != CAR_TRUCK) ||
			(nCar == THREE && st->nCarType != CAR_SUBWAY))
		{
			pRecord->SetVisible(FALSE); 
			continue; 
		}

		if(find(vec.begin(), vec.end(), st->nAllocGroup) == vec.end() && (long)vec.size() != 0)
			pRecord->SetVisible(FALSE);
		else 
		{ 
			BOOL bVisible = TRUE;

			if((st->strName.Find(strShRNo) < 0) && (LF->IsNumeric(strShRNo) == FALSE) && (strShRNo != "") )
				bVisible = FALSE;
 
			if((st->strGugun.Find(strShLocation) < 0) && (st->strDong.Find(strShLocation) < 0) && (strShLocation != "") )
				bVisible = FALSE;

			if(nRNo != -1 && st->nRNo != nRNo && (LF->IsNumeric(strShRNo) == TRUE) && (strShRNo != ""))
				bVisible = FALSE;

			pRecord->SetVisible(bVisible);
		}		
	}

	m_List.Populate();
}

void CConnListDlg2::OnSetWorking()
{
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	if(IDYES == MessageBox("출근 처리 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
	{
		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		if(st == NULL)
		{
			MessageBox("출근 처리에 실패 했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
			return;
		}
		
		CMkCommand pCmd(m_pMkDb, "update_rider_attend_leave_state");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), st->nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), st->nRNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);

		if(pCmd.Execute())
			MessageBox("출근 처리 되었습니다", "확인", MB_OK);
	}
}

void CConnListDlg2::OnShowRiderInfo()
{
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

	if(st == NULL)
		return;

	LU->ShowRiderInfoDlg(st->nCompany, st->nRNo);
}

void CConnListDlg2::OnSendMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	CRiderMsgDlg dlg;
	dlg.SetIntegrated(m_bIntegrated);
	dlg.SetCompanyCode(m_nCompanyCode);

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++) 
	{
		MSG_RIDER_INFO *pMRI = new MSG_RIDER_INFO;

		CXTPGridRow *pRow = (CXTPGridRow*)m_List.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		pMRI->nCompany = st->nCompany;
		pMRI->nRNo = st->nRNo;
		dlg.m_paSelected.Add(pMRI);
	}

	dlg.DoModal();


	for(int i = 0; i < dlg.m_paSelected.GetCount(); i++)
	{
		MSG_RIDER_INFO *pMRI = dlg.m_paSelected.GetAt(i);
		delete pMRI;
	}
}

void CConnListDlg2::OnSetLeave()
{
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	if(IDYES == MessageBox("강제퇴근 처리를 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
	{
		CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

		if(st == NULL)
		{
			MessageBox("강제퇴근 처리에 실패 했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
			return;
		}

		if(LU->ForceLeavingWork(st->nCompany, st->nRNo))
			MessageBox("강제퇴근 처리 되었습니다", "확인", MB_OK);
	}
}

void CConnListDlg2::OnViewExcel()
{
	if(!LF->POWER_CHECK(1900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 103, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}

void CConnListDlg2::OnCbnSelchangeCarCombo()
{
	FilterList();
}

void CConnListDlg2::OnSubWayAbsent()
{ 
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CONN_RIDER_STRUCT *st = (CONN_RIDER_STRUCT*)m_List.GetItemData(pRecord);

	if(st == NULL)
		return;

	if(st->nCarType != CAR_SUBWAY)
	{
		MessageBox("지하철 기사님들만 사용가능한 메뉴 입니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CSubwayAbsentDlg dlg;
	dlg.m_nCompany = st->nCompany;
	dlg.m_nRNo = st->nRNo;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}

BOOL CConnListDlg2::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP && pMsg->hwnd == m_edtAlloc.GetSafeHwnd())
	{
		ShowAllocList();
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CConnListDlg2::ShowAllocList()
{
	if(m_pAllocGroupListDlg == NULL)
	{
		m_pAllocGroupListDlg = new CAllocGroupListDlg(this);
		m_pAllocGroupListDlg->Create(IDD_ALLOC_GROUP_LIST_DLG, this);
	}

	m_pAllocGroupListDlg->ShowWindow(TRUE);
	MoveAllocList();	
}

void CConnListDlg2::MoveAllocList()
{
	if(m_pAllocGroupListDlg == NULL)
	{
		ShowAllocList();
			return;
	}

	CRect rcEdt, rcDlg;
	m_edtAlloc.GetWindowRect(rcEdt);
	m_pAllocGroupListDlg->GetWindowRect(rcDlg);

	long nHeight = rcDlg.Height();
	long nWidth = rcDlg.Width();

	rcDlg.top = rcEdt.bottom + 1;
	rcDlg.bottom = rcDlg.top + nHeight;
	rcDlg.left = rcEdt.left;
	rcDlg.right = rcDlg.left + nWidth;

	m_pAllocGroupListDlg->MoveWindow(rcDlg);

}



void CConnListDlg2::OnKillFocus(CWnd* pNewWnd)
{
	CMyFormView::OnKillFocus(pNewWnd);

	HideAllocList();
}
