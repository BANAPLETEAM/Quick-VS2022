// RiderMapNormalForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMapNormalForm.h"
#include "MyReportPaintManager.h"
#include "VirtualRecord.h"
#include "RcpView.h"
#include "RiderMapDlg.h"
#include "AllocatePaneDlg.h"
#include "MkLock.h"
#include "RiderMapSetDlg.h"


#define MAP_FULL_REFRESH_TIMER	1
#define MAP_ORDER_REFRESH_TIMER	2
#define RIDER_POS_INFO_EDIT_TIMER 3
#define CUSTOMER_POINT_POI		0xFFEE

int nGpsSecond[] = {99999, 3, 5, 10, 20, 30, 60, 90, 180};

// CRiderMapNormalForm

IMPLEMENT_DYNCREATE(CRiderMapNormalForm, CMyFormView)

CRiderMapNormalForm::CRiderMapNormalForm()
	: CMyFormView(CRiderMapNormalForm::IDD)
{
	m_nTopIndex = -1;
	m_pRiderMapDlg = NULL;
	m_pRiderMapSetDlg = NULL;
	m_nSearchKeyword = -1;
	m_bInitCompleted = FALSE;

	LF->LoadFromReg(m_setinfo);
}

CRiderMapNormalForm::~CRiderMapNormalForm()
{
	CMkLock lock(m_cs);

	if(m_pRiderMapSetDlg)
		delete m_pRiderMapSetDlg;

	m_wndReport.SaveReportOrder("CRiderMapNormalForm", "m_wndReport");
	m_lstOrder.SaveReportOrder("CRiderMapNormalForm", "m_lstOrder");
}

void CRiderMapNormalForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_ORDER_LIST, m_lstOrder);
	DDX_Control(pDX, IDC_MY_RIDER_CHECK, m_chkMyRider);
	DDX_Control(pDX, IDC_REALTIME_OTHER_RIDER_CHECK, m_chkRealtimeOtherRider);
	DDX_Control(pDX, IDC_OTHER_RIDER_WITH_MY_ORDER_CHECK, m_chkOtherRiderWithMyOrder);
	DDX_Control(pDX, IDC_OTHER_RIDER_CHECK, m_chkOtherRider);
	DDX_Control(pDX, IDC_INFO_EDIT, m_edtInfo);
}

BEGIN_MESSAGE_MAP(CRiderMapNormalForm, CMyFormView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)
	ON_WM_TIMER()
	ON_WM_MOUSEACTIVATE()
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_BN_CLICKED(IDC_RIDER_MAP_SET_BTN, OnBnClickedRiderMapSetBtn)
	ON_BN_CLICKED(IDC_DELETE_TEXT_BTN, OnBnClickedDeleteTextBtn)
	ON_MESSAGE(WM_RIDER_POS_REAL_TIME, OnRiderPosRealTime)
	ON_BN_CLICKED(IDC_REALTIME_OTHER_RIDER_CHECK, OnBnClickedRealtimeOtherRiderCheck)
	ON_BN_CLICKED(IDC_OTHER_RIDER_WITH_MY_ORDER_CHECK, OnBnClickedOtherRiderWithMyOrderCheck)
	ON_BN_CLICKED(IDC_OTHER_RIDER_CHECK, OnBnClickedOtherRiderCheck)
	ON_BN_CLICKED(IDC_MY_RIDER_CHECK, OnBnClickedMyRiderCheck)
	ON_BN_CLICKED(IDC_INIT_LOCATION_BTN, &CRiderMapNormalForm::OnBnClickedInitLocationBtn)
END_MESSAGE_MAP()


// CRiderMapNormalForm 진단입니다.

#ifdef _DEBUG
void CRiderMapNormalForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CRiderMapNormalForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CRiderMapNormalForm 메시지 처리기입니다.

void CRiderMapNormalForm::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_pRiderMapDlg = (CRiderMapDlg*)GetOwner();
	m_pMap = m_pRiderMapDlg->GetMap();

	CBitmap carbitmap;
	CImageList imgCarType;
	carbitmap.LoadBitmap(IDB_CAR_TYPE);
	imgCarType.Create(20, 18, ILC_COLOR32 | ILC_MASK, 1, 1);
	imgCarType.Add(&carbitmap, RGB(255, 255, 255));

	m_wndReport.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl함수의 순서중요함
		NULL);	//반드시 InsertColumn앞에 있어야함

	m_wndReport.InsertColumn(0,"No",LVCFMT_LEFT,45);
	m_wndReport.InsertColumn(1,"기사",LVCFMT_LEFT, 75);
	m_wndReport.InsertColumn(2,"사번",LVCFMT_RIGHT, 30);
	m_wndReport.InsertColumn(3,"위치",LVCFMT_LEFT,140);
	m_wndReport.InsertColumn(4,"PDA기종",LVCFMT_LEFT,100);
	m_wndReport.InsertColumn(5,"버전",LVCFMT_LEFT,37);
	m_wndReport.InsertColumn(6,"소속",LVCFMT_LEFT,100);
	m_wndReport.SetImageList(&imgCarType, LVSIL_SMALL);
	m_wndReport.SetOrderIndexCol(0);
	m_wndReport.GetColumns()->SetSortColumn(m_wndReport.GetColumns()->GetAt(0), 1);
	m_wndReport.EnableToolTips(FALSE);

	CBitmap bitmap;
	CImageList imageList;
	bitmap.LoadBitmap(IDB_LIST);
	imageList.Create(16,18,ILC_COLOR24 | ILC_MASK,1,1); 
	imageList.Add(&bitmap,RGB(0, 255, 255));
	m_lstOrder.SetImageList(&imageList,LVSIL_SMALL);
	m_lstOrder.GetPaintManager()->m_strNoItems = "";
	m_lstOrder.InsertColumn(0, "시간",LVCFMT_LEFT, 55);
	m_lstOrder.InsertColumn(1, "의뢰인",LVCFMT_LEFT, 67);
	m_lstOrder.InsertColumn(2, "출발지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(3, "도착지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(4, "요금",LVCFMT_RIGHT, 50);
	m_lstOrder.EnableToolTips(FALSE);

	m_wndReport.LoadReportOrder("CRiderMapNormalForm", "m_wndReport");
	m_lstOrder.LoadReportOrder("CRiderMapNormalForm", "m_lstOrder");

	m_pRcpView = LU->GetRcpView();

	if(!AfxGetApp()->GetProfileInt("RiderMapSet", "ShowOnce", 0))
		SetTimer(0, 2000, NULL);

	m_pMap->CreateWait();
	m_pMap->MoveMap(m_ci.m_bound.nPosX, m_ci.m_bound.nPosY);
	m_pMap->SetMapLevel(AfxGetApp()->GetProfileInt("RiderMapNormalForm", "MapLevel", 9));

	RefreshCheckButton();
	SetMapInfo();
	OnBnClickedOtherRiderCheck();

	SetTimer(MAP_FULL_REFRESH_TIMER, 10000, NULL);
	SetTimer(MAP_ORDER_REFRESH_TIMER, 5000, NULL);
	SetTimer(RIDER_POS_INFO_EDIT_TIMER, 200, NULL);

	m_bInitCompleted = TRUE;
}

void CRiderMapNormalForm::RefreshCheckButton()
{
	if(m_pRiderMapDlg->m_bOtherRiderMap)
	{
		CRiderMapNormalForm *pNormalForm = LU->GetRiderMapDlg()->m_pNormalForm;
		m_chkMyRider.SetCheck(pNormalForm->m_chkMyRider.GetCheck());
		m_chkRealtimeOtherRider.SetCheck(pNormalForm->m_chkRealtimeOtherRider.GetCheck());
		m_chkOtherRiderWithMyOrder.SetCheck(pNormalForm->m_chkOtherRiderWithMyOrder.GetCheck());
		m_chkRealtimeOtherRider.EnableWindow(FALSE);
		m_chkOtherRiderWithMyOrder.EnableWindow(FALSE);
		m_chkOtherRider.SetCheck(TRUE);
	}
	else
	{
		if(LU->GetRiderMapDlg2())
		{
			CRiderMapNormalForm *pNormalForm2 = LU->GetRiderMapDlg2()->m_pNormalForm;

			m_chkMyRider.SetCheck(pNormalForm2->m_chkMyRider.GetCheck());
			m_chkRealtimeOtherRider.SetCheck(pNormalForm2->m_chkRealtimeOtherRider.GetCheck());
			m_chkOtherRiderWithMyOrder.SetCheck(pNormalForm2->m_chkOtherRiderWithMyOrder.GetCheck());
		}
		else
		{
			m_chkMyRider.SetCheck(TRUE);
			m_chkRealtimeOtherRider.SetCheck(TRUE);
			m_chkOtherRiderWithMyOrder.SetCheck(TRUE);
		}
	}

}

void CRiderMapNormalForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);
	MoveControl();
}

void CRiderMapNormalForm::MoveControl()
{
	if(m_wndReport.GetSafeHwnd())
	{
 		CRect rcForm, rcReport, rcList;
		GetClientRect(rcForm);
		m_wndReport.GetWindowRect(rcReport);
		ScreenToClient(rcReport);
 
		rcReport.bottom = rcForm.Height() - 220;
		rcReport.right = rcForm.right - 4;
		m_wndReport.MoveWindow(rcReport);
		rcList.CopyRect(rcReport);
		rcList.top = rcReport.bottom + 3;
		rcList.bottom = rcForm.bottom - 1;
		rcList.right = rcForm.right - 4;
		m_lstOrder.MoveWindow(rcList);
	}
}

void CRiderMapNormalForm::RefreshOrderList(long nCompany, long nRNo)
{
	static long nPreCompany = 0;
	static long nPreRNo = 0;

	if(nCompany == nPreCompany && nRNo == nPreRNo)
		return;

	nPreCompany = nCompany;
	nPreRNo = nRNo;

	CMkLock lock(m_cs);

	m_lstOrder.DeleteAllItems();

	if(m_ci.IsChildCompany(nCompany))
	{
		OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
		OrderRecordList::reverse_iterator it;
		int index = 0;

		if(order.size() < 1)
		{
			m_pRcpView->RefreshList();
			order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
		}

		for(it = order.rbegin(); it != order.rend(); it++)
		{
			if(it->second.nRiderCompany == nCompany && it->second.nRNo == nRNo)
			{
				CString strCName;

				if(!m_ci.IsChildCompany(it->second.nCompany))
					strCName = "타사오더";
				else
					strCName = it->second.strCName.c_str();

				AddRiderHaveOrderToList(&m_lstOrder, index++, it->second.dtState, it->second.nState, 
							strCName, it->second.strStart.c_str(), 
							it->second.strDest.c_str(), it->second.nCharge);
			}
		}
	}
	else
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_have_order");
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter(nRNo);
		if(pRs.Execute(&pCmd))
		{
			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				long nCompany, nState, nCharge;
				COleDateTime dtState;
				CString strCName, strStart, strDest;
				
				pRs.GetFieldValue("nCompany", nCompany);
				pRs.GetFieldValue("nState", nState);
				pRs.GetFieldValue("dtState", dtState);
				pRs.GetFieldValue("sOName", strCName);
				pRs.GetFieldValue("sSDong", strStart);
				pRs.GetFieldValue("sDDong", strDest);
				pRs.GetFieldValue("nChargeSum", nCharge);

				if(!m_ci.IsChildCompany(nCompany))
					strCName = "타사오더";

				AddRiderHaveOrderToList(&m_lstOrder, i, dtState, nState, strCName, strStart, strDest, nCharge);

				pRs.MoveNext();
			}
		}

		if(m_lstOrder.GetRecords()->GetCount() > 0)
			UpdateRiderOrderCount(nCompany, nRNo);
	}

	m_lstOrder.Populate();
}

void CRiderMapNormalForm::UpdateRiderOrderCount(long nCompany, long nRNo)
{
	CXTPGridRecords *pRecords = m_lstOrder.GetRecords();
	
	long nAllocOrderCount = 0, nPickupOrderCount = 0, nHavingOrder = 0, nCompleteOrder = 0, nChargeSum = 0;
	CString strHasOrderList = "";

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		long nState = m_lstOrder.GetItemLong(pRecord);
		long nCharge = m_lstOrder.GetItemLong2(pRecord);
		CString strTime = pRecord->GetItem(0)->GetCaption(NULL);
		CString strStart = pRecord->GetItem(2)->GetCaption(NULL);
		CString strDest = pRecord->GetItem(3)->GetCaption(NULL);

		if(nState >= 11 && nState < 35)
		{
			CString strOrder;
			strOrder.Format("%s %s] %s -> %s", LF->GetStateString(nState), 
				strTime, 
				strStart, strDest);
			strHasOrderList += strOrder + "\n";
			nHavingOrder++;

			if(nState == 31)
				nPickupOrderCount++;
			else
				nAllocOrderCount++;
		}
		else
		{
			nCompleteOrder++;
		}

		nChargeSum += nCharge;
	}

	m_pMap->UpdateRiderOrderState(nCompany, nRNo, nAllocOrderCount, nPickupOrderCount, nHavingOrder, nCompleteOrder, nChargeSum, strHasOrderList);
}

void CRiderMapNormalForm::AddRiderHaveOrderToList(CXTPListCtrl2 *pList, int nItem, COleDateTime dtState, 
							long nState, CString strCName, CString strStart, CString strDest,
							long nCharge)
{
	COleDateTimeSpan span = 0;
	if(dtState.m_status != 2)  // DateTimeStatus.null
		span = COleDateTime::GetCurrentTime() - dtState;
	if(nState == STATE_OK ||
		nState == STATE_OK_ONLY_MAN ||
#ifdef _DAERI
		nState == STATE_ALLOCATED)
#else
		nState == STATE_ALLOCATED ||
		nState == STATE_PICKUP)
#endif
	{
		char buffer[10];
		pList->InsertItem(nItem, CString("+") + ltoa(span.GetTotalMinutes(), buffer, 10), LF->GetImageNumber(nState));
	}
	else
	{
		pList->InsertItem(nItem, dtState.Format("%H:%M"), LF->GetImageNumber(nState));
	}

	pList->SetItemText(nItem, 1, strCName);
	pList->SetItemText(nItem, 2, strStart);
	pList->SetItemText(nItem, 3, strDest);
	pList->SetItemText(nItem, 4, LF->GetMyNumberFormat(nCharge));
	pList->SetItemLong(nItem, nState);
	pList->SetItemLong2(nItem, nCharge);
}

void CRiderMapNormalForm::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CMkLock lock(m_cs);

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCompany = m_wndReport.GetItemData(nRow);
	int nRNo = m_wndReport.GetItemLong(nRow);

	m_pMap->MoveMapRider(nCompany, nRNo);
	RefreshOrderList(nCompany, nRNo);
}

void CRiderMapNormalForm::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CMkLock lock(m_cs);

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCompany = m_wndReport.GetItemData(nRow);
	int nRNo = m_wndReport.GetItemLong(nRow);

	m_pMap->MoveMapRider(nCompany, nRNo);
	m_pMap->SetMapLevel(6);
}

void CRiderMapNormalForm::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CMkLock lock(m_cs);

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCompany = m_wndReport.GetItemData(nRow);
	int nRNo = m_wndReport.GetItemLong(nRow);

	CPoint pt;
	GetCursorPos(&pt);

	CXPOIItem item = m_pMap->GetPOIIfExist(nCompany, nRNo);
	if(item)
		m_pRiderMapDlg->OnPopupMapMenu(item, pt);
}

void CRiderMapNormalForm::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);
	if(nIDEvent == MAP_FULL_REFRESH_TIMER)
	{
		if(!m_pMap->m_bSimulationMode) 
			RefreshAllRider();

		SetTimer(MAP_FULL_REFRESH_TIMER, 10000, NULL);
	}
	else if(nIDEvent == 0)
	{
		OnBnClickedRiderMapSetBtn();
	}
	else if(nIDEvent == MAP_ORDER_REFRESH_TIMER)
	{ 
		if(!m_pMap->m_bSimulationMode && IsRealTimeMode())
		{
			RefreshOrderState();
			RefreshOrder();	
			CheckVisibleAllRider();				
		}

		SetTimer(MAP_ORDER_REFRESH_TIMER, 10000, NULL);
	}
	else if(nIDEvent == RIDER_POS_INFO_EDIT_TIMER)
	{
		long nTime = 200;

		if(m_stInfo.GetCount() > 0)
		{
			CMkLock lock(m_csInfo);
			m_edtInfo.SetWindowText(m_stInfo.RemoveHead());

			if(m_stInfo.GetCount() > 0)
			{
				while(m_stInfo.GetCount() >= 20)
					m_stInfo.RemoveHead();

				nTime = 1000 / m_stInfo.GetCount();
			}
		}

		SetTimer(RIDER_POS_INFO_EDIT_TIMER, nTime, NULL);
	}

	CMyFormView::OnTimer(nIDEvent);
}


inline void PrintTick(DWORD &dwTick, CString strMsg)
{
	DWORD dwTick2 = GetTickCount();
	g_bana_log->Print("TICK: %s = %dms\n", strMsg, dwTick2 - dwTick);
	dwTick = GetTickCount();
}

inline void PrintTickSum(DWORD &dwTickSum, DWORD &dwTick)
{
	DWORD dwTick2 = GetTickCount();
	dwTickSum +=  GetTickCount() - dwTick;
	dwTick = GetTickCount();
}

void CRiderMapNormalForm::RefreshAllRider(BOOL bClear)
{
	if(IsRealTimeMode())
		return;	//실시간 GPS기사만 표시해야하므로, 갱신이 필요없다. 

	char buffer[10];

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_for_map2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int) , m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int) , m_chkOtherRider.GetCheck());
	if(!pRs.Execute(&pCmd)) return;

	CMkLock lock(m_cs);

	if(bClear)
	{
		m_wndReport.DeleteAllItems();
		m_pMap->DeleteAllRider();
	}

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{			
		long nPosX, nPosY, nCompany, nRNo, nCarType, nElapsedTime, nDeviceType;
		BOOL bUseGPS;
		CString strDong, strRName, strCompanyName, strPrgVer, strDevice;
		CString strUpdateTime, strPosName, strElapsedTime, strHp, strCity;
		COleDateTime dtLastPos;
		long nTruckType;
		CString strTon;

		pRs.GetFieldValue("nPosX", nPosX);
		pRs.GetFieldValue("nPosY", nPosY);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("bGPSUsage", bUseGPS);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("dtPos", dtLastPos);
		pRs.GetFieldValue("sName", strRName);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("sProgramVersion", strPrgVer);
		pRs.GetFieldValue("sCompanyName", strCompanyName);
		pRs.GetFieldValue("sDeviceTypeName", strDevice);
		pRs.GetFieldValue("nElapsedTime", nElapsedTime);
		pRs.GetFieldValue("sPosName", strPosName);
		pRs.GetFieldValue("nDeviceType", nDeviceType);
		pRs.GetFieldValue("sHp", strHp);
		pRs.GetFieldValue("sCity", strCity);
		pRs.GetFieldValue("nTruckType", nTruckType);
		pRs.GetFieldValue("sTon", strTon);

		//GPS 안잡히는 기사, 개성시로 이동시킴
		if(nPosX < 1000000 || nPosY < 1000000)
		{
			nPosX = 126455463;
			nPosY = 37990094;
		}

		LU->GpsPosRevision(nPosX, nPosY, nDeviceType, strDevice, strPrgVer);


		CRiderSubInfoMap::iterator it = LU->m_mapRiderSub.find(make_pair(nCompany, nRNo));

		if(it != LU->m_mapRiderSub.end())
			m_pMap->AddCarPOI(FALSE, it->second);

		ST_ALLOC_RIDER *pRider = LU->GetAllocRider(nCompany, nRNo); 

		pRider->strCurDong = strDong;
		pRider->strCurLocation = strPosName + " [" +  dtLastPos.Format("%H:%M") + "]";
	
		if(nPosX >= 0)
		{
			char buffer[10];
			strUpdateTime.Format("%s%s", bUseGPS ? "GPS" : "", nElapsedTime < 3 ? "현위치" : 
				(nElapsedTime > 60 ? "1시간이상" : CString(ltoa(nElapsedTime, buffer, 10))  + "분전"));
			strElapsedTime.Format("%d", nElapsedTime);
		}
		else
		{
			strElapsedTime.Format("%d", 9999);
		}
		
		BOOL bUpdated = FALSE;
		long nCount = m_wndReport.GetRecords()->GetCount();
		for(int nItem = 0; nItem < nCount; nItem++)
		{
			CXTPGridRecord *pRecord = m_wndReport.GetRecords()->GetAt(nItem);
			long nCompany2 = m_wndReport.GetItemData(pRecord);
			long nRNo2 = m_wndReport.GetItemLong(pRecord);

			if(nCompany2 == nCompany && nRNo2 == nRNo)
			{
				m_wndReport.SetItemText(pRecord, 3, strDong + " " + strPosName);
				m_wndReport.RedrawControl();
				bUpdated = TRUE;
				break;
			}
		}

		if(!bUpdated)
		{ 
			int nItem = m_wndReport.GetItemCount();
			m_wndReport.InsertItem(nItem, LF->GetZeroPadding(nRNo, max(0, nCarType - 1)));
			m_wndReport.SetItemText(nItem, 1, strRName);
			m_wndReport.SetItemText(nItem, 2, itoa(nRNo, buffer, 10));
			m_wndReport.SetItemText(nItem, 3, strDong + " " + strPosName);
			m_wndReport.SetItemText(nItem, 4, strDevice);
			m_wndReport.SetItemText(nItem, 5, strPrgVer);
			m_wndReport.SetItemText(nItem, 6, strCompanyName);
			m_wndReport.SetItemData(nItem, nCompany);
			m_wndReport.SetItemLong(nItem, nRNo);
		}

		COleDateTime dtPos = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, nElapsedTime, 0);
		m_pMap->AddCarPOI(FALSE, nCompany, nRNo, strRName, nPosX, nPosY,
				CCarType(nCarType, nTruckType, strTon),				
				GetRiderCaption(nCompany, nRNo, strRName, strCity), 
				GetRiderHint(strRName, strHp, strDong + " " + strPosName),
				"", -1, dtLastPos);
	

		pRs.MoveNext();
	}

	pRs.Close();
	m_wndReport.Populate();
	SetEachRecordToRiderSubInfo();

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
	
	RefreshOrderState();
	CheckVisibleAllRider();
}	


void CRiderMapNormalForm::SetRiderPosRealTime(CRealTimeRiderPos &pos, BOOL bNotPopulate)
{
	CMkLock lock(m_cs);

	CString strDeviceName = pos.strDeviceName + "/" + pos.strOS;
	CString strVersion = pos.strVersion;

	strVersion.Replace("000", "");

	static int nTickCount = 0;
	char buffer[10];
	BOOL bUpdated = FALSE;
	CString strRNameList;

	if(m_pMap->m_bSimulationMode)
		return;

	if(!m_ci.IsChildCompany(pos.nCompany))
		strRNameList = m_ci.GetName(pos.nCompany) + ")" + pos.strName; 
	else 
		strRNameList = pos.strName;

	CRiderSubInfo *pSubInfo = m_pMap->GetRiderSubInfo(pos.nCompany, pos.nRNo);

	if(pSubInfo)
	{
		CXTPGridRecord *pRecord = pSubInfo->GetRecord();
		if(pRecord)
		{
			m_wndReport.SetItemText(pRecord, 3, pos.strPosName);
			m_wndReport.SetItemText(pRecord, 4, strDeviceName);
			m_wndReport.SetItemText(pRecord, 5, strVersion);
			m_wndReport.RedrawControl();
			bUpdated = TRUE;
		}
	}

	if(!bUpdated)
	{
		int nIndex = m_wndReport.GetItemCount();
		m_wndReport.InsertItem(nIndex, LF->GetZeroPadding(pos.nRNo), max(0, pos.cartype.nCarType - 1)); 
		m_wndReport.SetItemText(nIndex, 1, strRNameList);
		m_wndReport.SetItemText(nIndex, 2, ltoa(pos.nRNo, buffer, 10));
		m_wndReport.SetItemText(nIndex, 3, pos.strPosName);
		m_wndReport.SetItemText(nIndex, 4, strDeviceName);
		m_wndReport.SetItemText(nIndex, 5, strVersion);
		m_wndReport.SetItemText(nIndex, 6, m_ci.GetName(pos.nCompany));
		m_wndReport.SetItemData(nIndex, pos.nCompany);
		m_wndReport.SetItemLong(nIndex, pos.nRNo);

		if(!bNotPopulate)
			m_wndReport.Populate();

		if(pSubInfo == NULL)
		{
			CRiderSubInfoMap::iterator it = LU->m_mapRiderSub.find(make_pair(pos.nCompany, pos.nRNo));
			if(it != LU->m_mapRiderSub.end())
				m_pMap->AddCarPOI(FALSE, it->second);
		}

		m_pMap->AddCarPOI(FALSE, pos.nCompany, pos.nRNo, pos.strName, pos.nPosX, pos.nPosY, 
				pos.cartype,
				GetRiderCaption(pos.nCompany, pos.nRNo, pos.strName, pos.strCity), 
				GetRiderHint(pos.strName, pos.strPhone, pos.strPosName));

		if(!bNotPopulate)
		{
			SetEachRecordToRiderSubInfo();
			CheckVisibleAllRider();
		}
	}
	else
	{
		m_pMap->AddCarPOI(FALSE, pos.nCompany, pos.nRNo, pos.strName, pos.nPosX, pos.nPosY, 
				pos.cartype,
				GetRiderCaption(pos.nCompany, pos.nRNo, pos.strName, pos.strCity), 
				GetRiderHint(pos.strName, pos.strPhone, pos.strPosName));

		if(pSubInfo == NULL)
			pSubInfo = m_pMap->GetRiderSubInfo(pos.nCompany, pos.nRNo);

		if(!bNotPopulate)
			CheckVisibleRider(*pSubInfo);
	}

	CString strText;
	strText.Format("%s(%d): %s", pos.strName, pos.nRNo, pos.strPosName);
	AddRiderPosInfo(strText);

	CRiderMapDlg *pRiderMapDlg2 = LU->GetRiderMapDlg2();

	if(pRiderMapDlg2 && pRiderMapDlg2->IsWindowVisible() && pRiderMapDlg2->m_pNormalForm)
		pRiderMapDlg2->m_pNormalForm->AddRiderPosInfo(strText);
}

CString CRiderMapNormalForm::GetRiderHint(CString &strRName, CString &strPhone, CString &strPOIName)
{
	return strRName + "(" + LF->GetDashPhoneNumber(strPhone) + ")\n" + strPOIName;
}

int CRiderMapNormalForm::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CRiderMapNormalForm::OnEnChangeXtplistctrlEdit()
{
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	CString strKeyword;
	
	pEdit->GetWindowText(strKeyword);
	
	if(LF->IsStringDigit(strKeyword))
	{
		m_strSearchKeyword.Empty();
		m_nSearchKeyword = atol(strKeyword);
	}
	else
	{
		m_strSearchKeyword = strKeyword;
		m_nSearchKeyword = -1;
	}

	CheckVisibleAllRider();


	CMkLock lock(m_cs);
	if(m_wndReport.GetVisibleItemCount() == 1)
	{
		CXTPGridRecord *pRecord = m_wndReport.GetRows()->GetAt(0)->GetRecord();
		long nCompany = m_wndReport.GetItemData(pRecord);
		long nRNo = m_wndReport.GetItemLong(pRecord);
		CRiderSubInfo *pSubInfo = m_pMap->GetRiderSubInfo(nCompany, nRNo);

		long nPosX, nPosY;
		pSubInfo->GetPrevPos(nPosX, nPosY);
		m_pMap->MoveMap(nPosX, nPosY);
	}
}

void CRiderMapNormalForm::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CRiderMapNormalForm::RefreshOrderState()
{
	CMkLock lock(m_cs);

	OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;
	BOOL bClear = TRUE;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nState >= 11 && it->second.nState <= 35)
		{
			m_pMap->UpdateRiderOrderState(it->second.nRiderCompany, 
				it->second.nRNo, 
				it->second.nState, 
				it->second.nCharge, 
				it->second.dtState,
				it->second.strStart.c_str(),
				it->second.strDest.c_str(),
				bClear);		

			bClear = FALSE;
		}
	}

	m_pMap->RefreshCarState();
}

void CRiderMapNormalForm::FindRNo(CString sRNo)
{
	CMkLock lock(m_cs);

	CXTPGridColumn *pColumn = NULL;
	CXTPGridRows *pRows = m_wndReport.GetRows();
	CXTPGridRecords *pReocords = m_wndReport.GetRecords();

	for(int i=0; i<pReocords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pReocords->GetAt(i);
		long nRNo = m_wndReport.GetItemLong(pRecord);

		if(_ttoi(sRNo) == nRNo)
		{
			m_pMap->MoveMapRider((long)m_wndReport.GetItemData(pRecord), nRNo);
			m_pMap->SetMapLevel(3);
			return;
		}
	}
}

void CRiderMapNormalForm::RefreshCustomerPOI()
{
	CMkLock lock(m_cs);

	m_pMap->poiman.DeleteGroup(CUSTOMER_POINT_POI);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_pos_data");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int) , m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int) , 0);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{			
		CString strCompany;
		long nPosX, nPosY;

		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("nPosX", nPosX);
		pRs.GetFieldValue("nPosY", nPosY);

		m_pMap->AddPointPOI(FALSE, strCompany, nPosX, nPosY, strCompany, "green_small.bmp", -1,
			CUSTOMER_POINT_POI, i, 0, 50);

		pRs.MoveNext();
	}
	pRs.Close();
}	

void CRiderMapNormalForm::OnBnClickedRiderMapSetBtn()
{
	if(!m_pRiderMapSetDlg) 
		m_pRiderMapSetDlg = new CRiderMapSetDlg(this);

	m_pRiderMapSetDlg->m_nCurMapLevel = m_pMap->GetMapLevel();
	m_pRiderMapSetDlg->m_nMaxMapLevel = m_pMap->GetMapLevelMax();
	m_pRiderMapSetDlg->CreateModalessDlg(this, &m_pRiderMapSetDlg, FALSE);
}

void CRiderMapNormalForm::RefreshFromSetupDlg()
{
	LF->LoadFromReg(m_setinfo);

	if(m_setinfo.nShowRiderHasColor)
	{
		//RefreshRiderMiscInfo();
		m_pMap->SetRiderColorManual(TRUE);
	}

	MoveControl();
	SetMapInfo();
	RefreshAllRider();
	RefreshOrder();
	CheckRiderCaption();
	m_pRiderMapDlg->MoveNormalForm(TRUE);

	if(m_setinfo.nShowCompayAll)
		RefreshCustomerPOI();
	else
		m_pMap->poiman.DeleteGroup(CUSTOMER_POINT_POI);
}

void CRiderMapNormalForm::SetMapInfo()
{
	m_pMap->m_nShowSmallSizeLevel = m_setinfo.nShowRiderCaptionLevel == 0 ? MAP_MAX_LEVEL : m_setinfo.nShowRiderCaptionLevel;
	m_pMap->m_bHoverShowRiderHaveOrder = m_setinfo.nHoverShowRiderHaveOrder;

	m_pMap->ShowOrderCaption(m_setinfo.nOrderCaptionTime || 
		m_setinfo.nOrderCaptionStart || 
		m_setinfo.nOrderCaptionDest);

	m_pMap->ShowRiderCaption(m_setinfo.nRiderCaptionCompany || 
		m_setinfo.nRiderCaptionName || 
		m_setinfo.nRiderCaptionRNo);

	m_pMap->SetRiderTailShowTime(LF->GetTailShowTimeFromIndex(m_setinfo.nRiderTailShowTime));
}

void CRiderMapNormalForm::AddOrderPOI(OrderRecord &order)
{
	if(m_pMap->m_mapRiderSub.end() != 
		m_pMap->m_mapRiderSub.find(std::make_pair(0, order.nTNo)))
		return;

	long nPosX = order.nStartPosX;
	long nPosY = order.nStartPosY;
	m_pMap->IsPosUsable(nPosX, nPosY);

	CRiderSubInfo rider;
	rider.cartype.nCarType = 1;
	rider.nCompany = 0;
	rider.nRNo = order.nTNo;
	rider.bActive = 1;
	rider.nTmX = nPosX;
	rider.nTmY = nPosY;
	rider.dtState = order.dtRcp;
	rider.nState = order.nState;
	m_pMap->m_mapRiderSub.insert(CRiderSubInfoMap::value_type(std::make_pair(0, order.nTNo), rider));

	CXPOIItem poi = m_pMap->AddPointPOI(FALSE, GetOrderCaption(order), nPosX, nPosY, GetOrderCaption(order, TRUE),
		order.nState == 40 ? "X" : "POINT", -1,
		0, order.nTNo, order.nTNo);

	poi.SetShowCaption((order.nState == 40) ? FALSE : m_pMap->IsVisibleOrderCaption());
}


CString CRiderMapNormalForm::GetOrderCaption(OrderRecord &order, BOOL bFull)
{
	CString strCaption;

	if(m_setinfo.nOrderCaptionTime == 0 &&
		m_setinfo.nOrderCaptionStart == 0 &&
		m_setinfo.nOrderCaptionDest == 0)
	{
		bFull = TRUE;
	}

	if(m_setinfo.nOrderCaptionTime || bFull)
	{
		COleDateTimeSpan span = 0;
		if(order.dtRcp.m_status  != 2)  // DateTimeStatus.null
			span = COleDateTime::GetCurrentTime() - order.dtRcp;

		if(span.GetTotalSeconds() < 60)
			strCaption.Format("(%d초)", (long)span.GetTotalSeconds());		
		else
			strCaption.Format("(%d분)", (long)span.GetTotalMinutes());	
	}

	if(m_setinfo.nOrderCaptionStart || bFull)
		strCaption += order.strStart.c_str();

	if(m_setinfo.nOrderCaptionDest || bFull)
	{
		if(m_setinfo.nOrderCaptionStart || bFull)
			strCaption += "->";

		strCaption += order.strDest.c_str();
	}

	return strCaption;
}

BOOL CRiderMapNormalForm::IsUserCheckOrderCount(OrderRecord *p)
{
	if(m_setinfo.bOrderCount8 && p->nState == STATE_WAIT)
		return TRUE;

	if(m_setinfo.bOrderCount10 && p->nState == STATE_OK)
		return TRUE;

	if(m_setinfo.bOrderCount11 && p->nState == STATE_OK_ONLY_MAN)
		return TRUE;

	if(m_setinfo.bOrderCount30 && p->nState == STATE_ALLOCATED)
		return TRUE;

	if(m_setinfo.bOrderCount31 && p->nState == STATE_PICKUP)
		return TRUE;

	if(m_setinfo.bOrderCount35 && p->nState == STATE_FINISH)
		return TRUE;

	return FALSE;

}

void CRiderMapNormalForm::RefreshOrder()
{
	CRiderSubInfoMap::iterator it;
	CRiderSubInfoMap &mapRiderSub = m_pMap->m_mapRiderSub;

	CMkLock lock(m_cs);

	for(it = mapRiderSub.begin(); it != mapRiderSub.end();)
	{
		if(it->second.nCompany == 0)
		{
			it = mapRiderSub.erase(it);
			continue;
		}
		it++;	
	}

	m_pMap->DeletePOI(0);

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it2;

	long nShowCount = 0;

	for(it2 = order.begin(); it2 != order.end(); it2++)
	{
		if(!m_ci.IsChildCompany(it2->second.nCompany))
			continue;

		if(m_setinfo.bShowOrderCount)
		{
			nShowCount += IsUserCheckOrderCount(&(it2->second));
		}

		if(LF->IsAllocOrder(it2->second.nState))
		{
			if(!m_setinfo.nShowCompleteOrder)
				continue;
		}
		else if(it2->second.nState == 40)
		{
			if(!m_setinfo.nShowCancelOrder)
				continue;
		}

		if(it2->second.nState >= 10 && it2->second.nState < 40)
		{
			int nMinutes = 0;
			COleDateTimeSpan span = 0;
			if(it2->second.dtRcp.m_status  != 2)  // DateTimeStatus.null
			{
				span = COleDateTime::GetCurrentTime() - it2->second.dtRcp;
				nMinutes = span.GetMinutes();
			}

			if(!m_setinfo.nOrderBefore10 && nMinutes < 10)
				continue;

			if(!m_setinfo.nOrderBefore20 && nMinutes >= 10 && nMinutes < 20)
				continue;

			if(!m_setinfo.nOrderBefore30 && nMinutes >= 20 && nMinutes < 30)
				continue;

			if(!m_setinfo.nOrderBefore60 && nMinutes >= 30 && nMinutes < 60)
				continue;

			if(!m_setinfo.nOrderAfter60 && nMinutes >= 60)
				continue;

			AddOrderPOI(it2->second);
		}
		else if(it2->second.nState == 40)
		{
			AddOrderPOI(it2->second);
		}
	}

	m_pRiderMapDlg->SetShowOrderCount(m_setinfo.bShowOrderCount, nShowCount);
}

void CRiderMapNormalForm::CheckVisibleAllRider()
{
	CRiderSubInfoMap::iterator it;
	CRiderSubInfoMap &mapRiderSub = m_pMap->m_mapRiderSub;

	CMkLock lock(m_cs);

	for(it = mapRiderSub.begin(); it != mapRiderSub.end(); it++)
	{
		if(it->second.nCompany > 0)
			CheckVisibleRider(it->second, FALSE);
	}

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	long nCount = pRecords->GetCount();; 

	for(int i = 0; i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		long nCompany = m_wndReport.GetItemData(pRecord);
		long nRNo = m_wndReport.GetItemLong(pRecord);
		CRiderSubInfo *pSubInfo = m_pMap->GetRiderSubInfo(nCompany, nRNo);
		if(!pSubInfo)
			pRecord->SetVisible(FALSE);
		else if(pSubInfo->GetRecord() != pRecord)
			pSubInfo->SetReportRecord(pRecord);
	}

	m_wndReport.Populate();

	long nItemCount = m_wndReport.GetRows()->GetCount();

	if(m_pRiderMapDlg)
		m_pRiderMapDlg->UpdateShowRiderCount(nItemCount);
}

void CRiderMapNormalForm::CheckVisibleRider(CRiderSubInfo &info, BOOL bReportPopulate)
{
	BOOL bVisible = TRUE;
	BOOL bMyRider = m_chkMyRider.GetCheck();
	BOOL bRealtimeOtherRider = m_chkRealtimeOtherRider.GetCheck();
	BOOL bOtherRiderWithMyOrder = m_chkOtherRiderWithMyOrder.GetCheck();
	BOOL bOtherRider = m_chkOtherRider.GetCheck();

	if(m_pMap->m_bTraceMode &&
		(m_pMap->m_TraceRider.nCompany != info.nCompany || 
		 m_pMap->m_TraceRider.nRNo != info.nRNo))
	{
		bVisible = FALSE;
	}

	if(info.nRNo == 39) {
		int a= 0;
		int b= a;
	}

	//기사검색조건에 따른 표시
	while(bVisible)
	{
		if(bMyRider && !info.bOtherRider)
			break;

		if(!bMyRider && info.bOtherRider)
			break;
		
		if(bRealtimeOtherRider && info.bRealtimeOtherRider)
			break;
		
		if(bOtherRiderWithMyOrder && info.bOtherRider && info.nMyOrderCount > 0)
			break;

		bVisible = FALSE;
	}

	//접속시간/픽업/배차에 따른 표시
	while(bVisible)
	{
		if(!bOtherRider)
		{
			if(m_setinfo.nGpsRiderOnly)
			{
				COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - info.dtUpdate;
				if(dtSpan.GetTotalSeconds() < 90) //30초였음. 
					break;
			}
			else
			{
				if(m_setinfo.nRiderAlloc && info.nAllocOrderCount > 0)
					break;

				if(m_setinfo.nRiderPickup && info.nPickupOrderCount > 0)
					break;

				COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - info.dtUpdate;
				double nElapsedMin = dtSpan.GetTotalMinutes();

				if(m_setinfo.nRiderBefore1 && nElapsedMin <= 1)
					break;

				if(m_setinfo.nRiderBefore10 && nElapsedMin <= 10)
					break;

				if(m_setinfo.nRiderBefore30 && nElapsedMin <= 30)
					break;

				if(m_setinfo.nRiderAfter30 && nElapsedMin > 30)
					break;
			}
		}
		else
		{
			COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - info.dtUpdate;
			double nElapsedMin = dtSpan.GetTotalMinutes();

			if(nElapsedMin <= 1)
				break;
		}

		bVisible = FALSE;
	}

	//공차 및 차량이 가진 오더수에 따른 표시
	while(bVisible && m_pMap->m_nBagType)
	{
		if((m_pMap->m_nBagType & BTN_BAG_TYPE_0) && info.nHavingOrder == 0)
			break;

		if((m_pMap->m_nBagType & BTN_BAG_TYPE_1) && info.nHavingOrder == 1)
			break;

		if((m_pMap->m_nBagType & BTN_BAG_TYPE_2) && info.nHavingOrder == 2)
			break;

		if((m_pMap->m_nBagType & BTN_BAG_TYPE_3) && info.nHavingOrder >= 3)
			break;

		bVisible = FALSE;
	}


	//차량종류에 따른 표시
	while(bVisible && m_pMap->m_nCarType)
	{
		if((m_pMap->m_nCarType & BTN_CAR_TYPE_BIGBIKE) && (info.cartype.nCarType == CAR_BIGBIKE || info.cartype.nCarType == CAR_AUTO))
			break;

		if((m_pMap->m_nCarType & BTN_CAR_TYPE_DAMA) && info.cartype.nCarType == CAR_DAMA)
			break;

		if((m_pMap->m_nCarType & BTN_CAR_TYPE_LABO) && info.cartype.nCarType == CAR_LABO)
			break;

		if((m_pMap->m_nCarType & BTN_CAR_TYPE_VAN) && info.cartype.nCarType == CAR_VAN)
			break;

		if((m_pMap->m_nCarType & BTN_CAR_TYPE_TRUCK) && info.cartype.nCarType == CAR_TRUCK)
			break;

		bVisible = FALSE;
	}

	//트럭 톤에 따른 표시
	while(bVisible && m_pMap->m_nTonType)
	{
		if((m_pMap->m_nTonType & BTN_TON_TYPE_1_0) && info.cartype.strTon == "1.0")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_1_4) && info.cartype.strTon == "1.4")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_2_5) && info.cartype.strTon == "2.5")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_3_5) && info.cartype.strTon == "3.5")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_4_5) && info.cartype.strTon == "4.5")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_5_0) && info.cartype.strTon == "5.0")
			break;

		if((m_pMap->m_nTonType & BTN_TON_TYPE_11_0) && info.cartype.strTon == "11.0")
			break;

		bVisible = FALSE;
	}


	if(bVisible)
	{
		if(m_nSearchKeyword > 0 && m_nSearchKeyword != info.nRNo)
			bVisible = FALSE;

		if(bVisible && !m_strSearchKeyword.IsEmpty() && info.strName.Find(m_strSearchKeyword) < 0)
			bVisible = FALSE;
	}
	

	CXPOIItem item = m_pMap->GetPOIIfExist(info.nCompany, info.nRNo);
	if(item)
	{
		if(bVisible)
			m_pMap->SetPOIVisibleAsc(item);
		else
		{
			m_pMap->SetPOIVisibleDec(item, MAP_MAX_LEVEL);
			m_pMap->DeleteRiderTail(info.nCompany, info.nRNo);
		}
	}

	if(info.SetRecordVisible(bVisible))
		if(bReportPopulate)
			m_wndReport.Populate();
}

CString CRiderMapNormalForm::GetRiderCaption(long nCompany, long nRNo, CString strName, CString strCity, BOOL bFull)
{
	CString strCaption;

	if(m_setinfo.nRiderCaptionRNo == 0 &&
		m_setinfo.nRiderCaptionName == 0 &&
		m_setinfo.nRiderCaptionCompany == 0)
	{
		bFull = TRUE;
	}

	if(m_setinfo.nRiderCaptionRNo || bFull)
		strCaption.Format("(%d)", nRNo);

	if(m_setinfo.nRiderCaptionName || bFull)
		strCaption += strName;

	BOOL bIsChild = m_ci.IsChildCompany(nCompany);

	if(m_setinfo.nRiderCaptionCompany || bFull || !bIsChild)
	{
		if(m_setinfo.nRiderCaptionName || bFull)
			strCaption += "/";

		strCaption += m_ci.GetProperName(nCompany);

		if(!bIsChild)
			strCaption += "[" + strCity + "]";
	}

	return strCaption;
}

void CRiderMapNormalForm::CheckRiderCaption()
{
	CRiderSubInfoMap::iterator it;
	CRiderSubInfoMap &mapRiderSub = m_pMap->m_mapRiderSub;

	for(it = mapRiderSub.begin(); it != mapRiderSub.end(); it++)
	{
		if(it->second.nCompany > 0)
		{
			CXPOIItem item = m_pMap->GetPOIIfExist(it->second.nCompany, it->second.nRNo);
			if(item)
			{
				item.BeginUpdate();
				item.SetCaption(GetRiderCaption(it->second.nCompany, 
									it->second.nRNo, 
									it->second.strName,
									it->second.strCity));
				item.EndUpdate();
			}
		}
	}
}

void CRiderMapNormalForm::SetEachRecordToRiderSubInfo()
{
	for(int nItem = 0; nItem < m_wndReport.GetRecords()->GetCount(); nItem++)
	{
		CXTPGridRecord *pRecord = m_wndReport.GetRecords()->GetAt(nItem);
		long nCompany = m_wndReport.GetItemData(pRecord);
		long nRNo = m_wndReport.GetItemLong(pRecord);

		CRiderSubInfo *pInfo = m_pMap->GetRiderSubInfo(nCompany, nRNo);
		if(pInfo)
			pInfo->SetReportRecord(pRecord);
		else
			pRecord->SetVisible(FALSE);
	}
}

void CRiderMapNormalForm::OnBnClickedDeleteTextBtn()
{
	m_nSearchKeyword = -1;
	m_strSearchKeyword.Empty();
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	pEdit->SetWindowText("");
	CheckVisibleAllRider();
}

void CRiderMapNormalForm::InitGpsRider()
{
	CRiderSubInfoMap::iterator it;

	for(it = LU->m_mapRiderSub.begin(); it != LU->m_mapRiderSub.end(); it++)
	{	
		long nPosX, nPosY;
		CRiderSubInfo &info = it->second;

		info.GetPrevPos(nPosX, nPosY);

		CRealTimeRiderPos pos;
		pos.nCompany = info.nCompany;
		pos.nRNo = info.nRNo;
		pos.strName = info.strName;
		pos.nPosX = nPosX;
		pos.nPosY = nPosY;
		pos.bUseGps = TRUE;
		pos.cartype = info.cartype;
		pos.strPosName = info.strPosName;
		pos.strPhone = info.strPhone;
		pos.strCity = info.strCity;

		SetRiderPosRealTime(pos, TRUE);
	}

	m_wndReport.Populate();
	SetEachRecordToRiderSubInfo();
	CheckVisibleAllRider();
}

LONG CRiderMapNormalForm::OnRiderPosRealTime(WPARAM wParam, LPARAM lParam)
{
	//쓰레드 동기화 문제로 메시지로 변경함(Talmap.dll에서 오류발생)
	CRealTimeRiderPos *pPos = (CRealTimeRiderPos*)wParam;
	SetRiderPosRealTime(*pPos, (BOOL)lParam);
	delete pPos;
	return 0;
}

BOOL CRiderMapNormalForm::IsRealTimeMode()
{
	return !m_chkOtherRider.GetCheck() && m_setinfo.nGpsRiderOnly;
}


void CRiderMapNormalForm::AddRiderPosInfo(CString strInfo)
{
	CMkLock lock(m_csInfo);
	m_stInfo.AddTail(strInfo);
}

BOOL CRiderMapNormalForm::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP || pMsg->message == WM_MOUSEMOVE)
		m_pRiderMapDlg->PreTranslateMessage(pMsg); 

	return CMyFormView::PreTranslateMessage(pMsg);
}


void CRiderMapNormalForm::OnBnClickedMyRiderCheck()
{
	CheckVisibleAllRider();
}

void CRiderMapNormalForm::OnBnClickedRealtimeOtherRiderCheck()
{
	CheckVisibleAllRider();
}

void CRiderMapNormalForm::OnBnClickedOtherRiderWithMyOrderCheck()
{
	CheckVisibleAllRider();
}

void CRiderMapNormalForm::OnBnClickedOtherRiderCheck()
{
	BOOL bOtherRiderMap = m_chkOtherRider.GetCheck();

	if(bOtherRiderMap != m_pRiderMapDlg->IsOtherRiderMap())
	{
		CRiderMapDlg *pDlgTarget, *pDlgSource;


		if(!bOtherRiderMap)
		{
			pDlgTarget = LU->CreateRiderMapDlg();
			pDlgSource = LU->GetRiderMapDlg2();
		}
		else 
		{
			pDlgTarget = LU->CreateRiderMapDlg2();
			pDlgSource = LU->GetRiderMapDlg();
		}

		if(pDlgTarget && pDlgSource)
		{	
			CRiderMapCtrl *pMapTarget = pDlgTarget->GetMap();
			CRiderMapCtrl *pMapSource = pDlgSource->GetMap();
			CRiderMapNormalForm *pFormTarget = pDlgTarget->m_pNormalForm;
			CRiderMapNormalForm *pFormSource = pDlgSource->m_pNormalForm;

			pMapTarget->m_nBagType = pMapSource->m_nBagType;
			pMapTarget->m_nCarType = pMapSource->m_nCarType;
			pMapTarget->m_nTonType = pMapSource->m_nTonType;
			pMapTarget->SetBagImage();
			pMapTarget->SetCarImage();
			pMapTarget->SetTonImage();

			pFormTarget->m_setinfo = pFormSource->m_setinfo;

			((CEdit*)pFormTarget->GetDlgItem(IDC_XTPLISTCTRL_EDIT))->SetWindowText(pFormSource->m_strSearchKeyword);
			pFormTarget->m_nSearchKeyword = pFormSource->m_nSearchKeyword;

			pFormTarget->m_chkMyRider.SetCheck(pFormSource->m_chkMyRider.GetCheck());
			pFormTarget->m_chkRealtimeOtherRider.SetCheck(pFormSource->m_chkRealtimeOtherRider.GetCheck());
			pFormTarget->m_chkOtherRiderWithMyOrder.SetCheck(pFormSource->m_chkOtherRiderWithMyOrder.GetCheck());

			CheckVisibleAllRider();
		}

		m_chkOtherRider.SetCheck(!bOtherRiderMap);
		return;
	}

	if(IsRealTimeMode())
	{
		CMkLock lock(m_cs);
		m_pMap->m_bDisableCarAlpha = FALSE;
		m_wndReport.DeleteAllItems();
		m_pMap->DeleteAllRider();
		InitGpsRider();		
		RefreshOrder();
		CheckRiderCaption();
	}
	else
	{
		m_pMap->m_bDisableCarAlpha = TRUE;
		RefreshAllRider(TRUE);
	}
}

void CRiderMapNormalForm::OnBnClickedInitLocationBtn()
{
	if(m_pRiderMapDlg) 
	{
		m_pRiderMapDlg->m_nNormalFormWidth = 540;
		m_pRiderMapDlg->MoveNormalForm(TRUE);
	}
}
