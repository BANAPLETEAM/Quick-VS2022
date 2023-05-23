// RiderMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMapDlg.h"
#include "POiData.h"
#include "JibunData.h"
#include "MyReportPaintManager.h"
#include "RcpView.h"
#include "RiderMapNormalForm.h"
#include "RiderMsgDlg.h"
#include "AllocateBoardDlg.h"

IMPLEMENT_DYNAMIC(CRiderMapDlg, CMyDialog)

CRiderMapDlg::CRiderMapDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderMapDlg::IDD, pParent)
{
	m_pNormalForm = NULL;
	m_bHideListForm = FALSE;
	m_pRcpView = NULL;
	m_dtBase = COleDateTime::GetCurrentTime();
	m_nForLongTime = 12;
	m_nTraceTimerMSec = 100;
	m_bOtherRiderMap = TRUE;
	m_bChangeCursor = FALSE; // 화면이동 변수들
	m_bMoveControl = FALSE;
	m_bMustMoveControl = FALSE;
	m_nNormalFormWidth = 0;
	m_bMaxmize = FALSE;
}

CRiderMapDlg::~CRiderMapDlg()
{
}

void CRiderMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNO_STATIC, m_RNoStc);
	DDX_Control(pDX, IDC_RNO_EDT, m_RNoEdt);
	DDX_Control(pDX, IDC_TALMAP_CTRL, m_wndLogiMap);
}


BEGIN_MESSAGE_MAP(CRiderMapDlg, CMyDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_REFRESH_MAP_BTN, OnBnClickedRefreshMapBtn)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_RNO_EDT, OnEnChangeRnoEdt)
	ON_MESSAGE(WM_UI_MOUSE_UP, OnMapUIMouseUP)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CRiderMapDlg, CMyDialog)
	ON_EVENT(CRiderMapDlg, IDC_TALMAP_CTRL, 43, CRiderMapDlg::OnPOIClick, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


// CRiderMapDlg 메시지 처리기입니다.

BOOL CRiderMapDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcVertical = AfxGetApp()->LoadCursor(IDC_VERTICAL);
	
	m_wndLogiMap.m_bHasCargoBranch = m_ci.HasCargoBranch();
	m_wndLogiMap.m_bCargoOnly = m_ci.IsCargoOnly();

	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE/*|WS_CLIPCHILDREN|WS_CLIPSIBLINGS*/, CRect(0, 0, 0, 0), this, IDC_TABCONTROL);
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;
	m_wndTabControl.GetPaintManager()->DisableLunaColors(TRUE);

	m_pNormalForm = (CRiderMapNormalForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRiderMapNormalForm), _T("위치관제"), 0, CRiderMapNormalForm::IDD);
	m_nNormalFormWidth = AfxGetApp()->GetProfileInt("CRiderMapNormalForm", "nNormalFormWidth", 540);

	if(m_nNormalFormWidth > 2000)
		m_nNormalFormWidth = 540;

	MoveNormalForm(TRUE);
 
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRiderMapDlg::OnBnClickedRefreshMapBtn()
{ 
	if(GetActiveForm() == m_pNormalForm)
        m_pNormalForm->RefreshAllRider();
}

void CRiderMapDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	m_bMaxmize = nType == SIZE_MAXIMIZED ? TRUE : FALSE;
	MoveClient(cx, cy);
}

void CRiderMapDlg::MoveClient(int cx, int cy)
{
	if(m_wndLogiMap.GetSafeHwnd())
		MoveNormalForm(TRUE);
}

void CRiderMapDlg::OnClose()
{
	CRiderMapDlg *pDlg = LU->GetRiderMapDlg();
	CRiderMapDlg *pDlg2 = LU->GetRiderMapDlg2();

	if(!m_bOtherRiderMap && pDlg2)
	{
		CRect rc;
		pDlg->GetWindowRect(rc);
		pDlg2->MoveWindow(rc);
	}
	else if(m_bOtherRiderMap && pDlg)
	{
		CRect rc;
		pDlg2->GetWindowRect(rc);
		pDlg->MoveWindow(rc);
	}

	AfxGetApp()->WriteProfileInt("RiderMapDlg", "MapLevel", GetMap()->GetMapLevel());
	AfxGetApp()->WriteProfileInt("RiderMapDlg", "LastShowMapType", m_bOtherRiderMap);

	ShowWindow(SW_HIDE);
}

void CRiderMapDlg::OnOK()
{
	OnClose();
}

void CRiderMapDlg::OnCancel()
{
	OnClose();
}

void CRiderMapDlg::OnPOIClick(LPDISPATCH POI, long nFlag, long X, long Y)
{
	CXPOIItem poi;
	poi.AttachDispatch(POI, FALSE);
	OnPopupMapMenu(poi, CPoint(X, Y));
}

void CRiderMapDlg::OnPopupMapMenu(CXPOIItem item, CPoint pt)
{
	BOOL bOrder = FALSE;
	long nCompany = item.GetData() >> 16;
	long nRNo = item.GetData() & 0xFFFF;
	//BOOL bSupportRider = m_pNormalForm->GetSupportRider(nCompany, nRNo);

	CXPOIGroup group = item.GetGroup();
	if(group.GetID() == 0)
	{
		bOrder = TRUE;
		nCompany = 0;
		nRNo = item.GetData();
	}


	m_wndLogiMap.SetRClickRider(nCompany, nRNo);

	enum MAP_POPUP_SUB_MENU { MENU_SUB_TRACE_ALL_SHOW = 1000, 
		MENU_SUB_TRACE_FAST_MOVE = 1001, 
		MENU_SUB_TRACE_NORMAL_MOVE = 1002};

	CXPopupMenu submenu;
	CXPopupMenu menu = m_wndLogiMap.app.GetPopupMenu();
	menu.Create();

	if(bOrder)
	{
		CString strStartDest, strCharge, strPhone, strUseCount, strEtc, strCompany;
		OrderRecord *pOrder = (OrderRecord*)m_pRcpView->GetTodayOrderRecord(nRNo);

		strCompany = "[" + m_ci.GetProperName(pOrder->nCompany) + "]";
		strStartDest.Format("[%s->%s]", pOrder->strStart.c_str(), pOrder->strDest.c_str());
		strCharge.Format("요금\t%s원", LF->GetMyNumberFormat(pOrder->nCharge));
		strPhone.Format("전화\t 외:%s,출:%s,도:%s", LF->GetDashPhoneNumber(pOrder->strOPhone.c_str()),  
						LF->GetDashPhoneNumber(pOrder->strSPhone.c_str()),
						LF->GetDashPhoneNumber(pOrder->strDPhone.c_str()));
		strUseCount.Format("이용\t%d건", pOrder->nUseCount);

		menu.AppendString(MENU_ORDER_START_DEST+1010, strCompany, "회사명", "", 0);
		submenu = menu.AppendSubMenu(strStartDest, "출발지->도착지");
		submenu.AppendString(MENU_ORDER_START_DEST+1000, strCharge, "요금", "", 0);
		submenu.AppendString(MENU_ORDER_START_DEST+1001, strPhone, "고객전화", "", 0);
		submenu.AppendString(MENU_ORDER_START_DEST+1002, strUseCount, "사용횟수", "", 0);
		submenu.AppendString(MENU_ORDER_START_DEST+1003, pOrder->strEtc.c_str(), "적요", "", 0);
		menu.AppendString(MENU_ORDER_INFO, "오더접수창 보기", "오더접수창 보기", "", 0);
		menu.AppendString(MENU_ORDER_LOG, "오더로그창 보기", "오더로그창 보기", "", 0);
		menu.AppendString(MENU_ORDER_ALLOCATE, "개별 배차창", "개별 배차창", "", 0);

		if(m_pNormalForm->m_nSelectedRCompany > 0)
			menu.AppendString(MENU_ORDER_ALLOCATE2, "선택기사 즉시배차", "선택기사 즉시배차", "", 0);
	}
	else
	{
		menu.AppendString(MENU_RIDER_INFO, "기사정보창", "기사정보창 보기", "", 0);
		menu.AppendString(MENU_RIDER_NOTICE, "기사 공지보내기", "기사 공지보내기", "", 0);
		menu.AppendString(MENU_RIDER_ALLOCATE, "접수창에 선택된 오더 개별배차", "접수창에 선택된 오더 개별배차", "", 0);
		menu.AppendString(MENU_MAKE_CALL, "전화걸기", "기사님에게 전화 걸기", "", 0);

		submenu = menu.AppendSubMenu("기사이동 경로보기", "기사이동 로그를 보여줌");
		submenu.AppendString(MENU_SUB_TRACE_ALL_SHOW, "전체경로표시", "전체경로만 보여줌", "", 0);
		submenu.AppendString(MENU_SUB_TRACE_FAST_MOVE, "빠른속도로 움직임", "빠른속도로 시뮬레이션함", "", 0);
		submenu.AppendString(MENU_SUB_TRACE_NORMAL_MOVE, "보통속도로 움직임", "보통속도로 시뮬레이션함", "", 0);

		submenu = menu.AppendSubMenu("기사 실시간 추적", "기사 실시간 위치를 추적");
		submenu.AppendString(MENU_SUB_RIDER_REALTIME_TRACE, "현재시점부터 추적시작", "현재시점부터 꼬리를 보여줌", "", 0);
		submenu.AppendString(MENU_SUB_RIDER_REALTIME_TRACE_WITH_RECENT_LOG, "최근1시간 로그포함해서 추적시작", "최근1시간 꼬리를 보여줌", "", 0);

		if(m_ci.IsChildCompany(nCompany))
			menu.AppendString(MENU_RIDER_WORK_LEAVE, "기사 강제퇴근처리", "퇴근처리", "", 0);
		menu.AppendString(MENU_FIND_PROPER_ORDER, "적절한 오더 찾기", "기사위치/이동방향/배차오더 기준으로 적절한 추가오더를 찾음", "", 0);
	}

	CXPoint point = m_wndLogiMap.uiman.ClientToScreen(pt.x, pt.y);
	CXPopupMenuItem mitem = menu.TrackPopupMenu(0, point.GetX(), point.GetY());
	if(mitem.m_lpDispatch != NULL)
	{
		//오더이면 nCompany = 0, nRNo = nTNo
		switch(mitem.GetID())
		{
		case MENU_ORDER_INFO:
			m_pRcpView->EditOrderFromTNo(nRNo);
			break;
		//case MENU_ORDER_LOG:
		//	m_pRcpView->ShowOrderLogDetailDlgFromTNo(nRNo);
		//	break;
		case MENU_ORDER_ALLOCATE:
			m_pRcpView->AlllocateFromTNo(nRNo);
			break;	
		case MENU_ORDER_ALLOCATE2:
			m_pRcpView->AlllocateFromTNo(nRNo, m_pNormalForm->m_nSelectedRCompany, m_pNormalForm->m_nSelectedRNo);
			break;
		case MENU_RIDER_INFO:
			LU->ShowRiderInfoDlg(nCompany, nRNo);
			break;
		case MENU_RIDER_TRACE:
		case MENU_SUB_TRACE_ALL_SHOW:
		case MENU_SUB_TRACE_FAST_MOVE:
		case MENU_SUB_TRACE_NORMAL_MOVE:
		case MENU_RIDER_REALTIME_TRACE:
		case MENU_SUB_RIDER_REALTIME_TRACE:
			GoRiderTrace(mitem.GetID(), nCompany, nRNo);
			break;
		case MENU_SUB_RIDER_REALTIME_TRACE_WITH_RECENT_LOG:
			GoRiderTrace(mitem.GetID(), nCompany, nRNo, COleDateTime::GetCurrentTime(), 1);
			break;	
		case MENU_RIDER_ALLOCATE:
			m_pRcpView->SendMessage(WM_RIDER_ALLOCATE, (WPARAM)nRNo, (LPARAM)nCompany);
			break;
		case MENU_RIDER_NOTICE:
			{
				MSG_RIDER_INFO *pInfo = new MSG_RIDER_INFO;
				CRiderMsgDlg dlg;
				dlg.SetIntegrated(m_ba.GetCount() > 2);
				dlg.SetCompanyCode(m_ci.m_nCompanyCode);
				pInfo->nCompany = nCompany;
				pInfo->nRNo = nRNo;
				dlg.m_paSelected.Add((MSG_RIDER_INFO*)pInfo);
				dlg.DoModal();
				delete pInfo;
				break;
			}
		case MENU_MAKE_CALL:
			LU->ShowCallPhoneRiderDlg(nCompany, nRNo, nCompany, FALSE);
			break;


#ifndef _DAERI
		case MENU_RIDER_WORK_LEAVE:
			if(IDYES == MessageBox("강제퇴근 처리를 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
				LU->ForceLeavingWork(nCompany, nRNo);
			break;
#endif
		}
	}
}

BOOL CRiderMapDlg::GoRiderTrace(int nTraceType, long nCompany, long nRNo, COleDateTime dtBase, long nForLongHour)
{

	if(nTraceType == MENU_SUB_TRACE_ALL_SHOW)
	{
		m_wndLogiMap.TraceMode(TRUE, nCompany, nRNo, TRUE, FALSE);
		m_pNormalForm->CheckVisibleAllRider();
		m_wndLogiMap.EnableDrawRiderMoveBoundary(FALSE);
		m_wndLogiMap.SetSimulationMode(FALSE);

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_pos_log_for_trace2");
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter(nRNo);
		pCmd.AddParameter(dtBase);
		pCmd.AddParameter(nForLongHour);
		CMkParameter *parOutType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		CMkParameter *parOutDeviceName = pCmd.AddParameter(typeString, typeOutput, 50, "");
		CMkParameter *parOutDeviceVer = pCmd.AddParameter(typeString, typeOutput, 50, "");

		if(pRs.Execute(&pCmd))
		{
			COleDateTime dtPreLog;
			long nType = parOutType->GetLong();
			CString strDeviceName = parOutDeviceName->GetString();
			CString strDeviceVer = parOutDeviceVer->GetString();

			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				long nPosX, nPosY;
				COleDateTime dtLog;
				BOOL bDotLine = FALSE;

				pRs.GetFieldValue("nPosX", nPosX);		
				pRs.GetFieldValue("nPosY", nPosY);		
				pRs.GetFieldValue("dtLog", dtLog);	

				LU->GpsPosRevision(nPosX, nPosY, nType, strDeviceName, strDeviceVer);

				if(i > 0)
				{
					COleDateTimeSpan span = dtLog - dtPreLog;					
					if(span.GetTotalMinutes() > 5)
						bDotLine = TRUE;
				}

				m_wndLogiMap.AddTracePos(nPosX, nPosY, dtLog, TRUE, 0, bDotLine);
				dtPreLog = dtLog;
				pRs.MoveNext();
			}
		}

		if(pRs.GetRecordCount() == 0)
		{	
			m_wndLogiMap.TraceMode(FALSE);
			return FALSE;
		}

		AddTraceRiderHasOrder(FALSE, nCompany, nRNo, dtBase, nForLongHour);
	}
	else if(nTraceType == MENU_SUB_TRACE_FAST_MOVE || nTraceType == MENU_SUB_TRACE_NORMAL_MOVE)
	{
		m_wndLogiMap.TraceMode(TRUE, nCompany, nRNo, TRUE, FALSE);
		m_pNormalForm->CheckVisibleAllRider();
		m_wndLogiMap.EnableDrawRiderMoveBoundary(FALSE);
		m_wndLogiMap.SetSimulationMode(TRUE);

		AddTraceRiderHasOrder(FALSE, nCompany, nRNo, dtBase, nForLongHour);

		CMkRecordset *m_pTraceRecord = new CMkRecordset(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_pos_log_for_trace2");
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter(nRNo);
		pCmd.AddParameter(dtBase);
		pCmd.AddParameter(nForLongHour);
		CMkParameter *parOutType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		CMkParameter *parOutDeviceName = pCmd.AddParameter(typeString, typeOutput, 50, "");
		CMkParameter *parOutDeviceVer = pCmd.AddParameter(typeString, typeOutput, 50, "");

		if(m_pTraceRecord->Execute(&pCmd) && m_pTraceRecord->GetRecordCount()	> 0)
		{
			if(m_pTraceRecord->GetRecordCount()	> 0)
			{
				m_nTRDType = parOutType->GetLong();
				m_strTRDName = parOutDeviceName->GetString();
				m_strTRDVer = parOutDeviceVer->GetString();

				m_wndLogiMap.SetTraceRecord((void*)m_pTraceRecord);
				m_wndLogiMap.CreateTraceNavi();
				m_nTraceTimerMSec = MENU_SUB_TRACE_FAST_MOVE ? 10 : 100;
				
				SetTimer(1, m_nTraceTimerMSec, NULL);
			}
			else
			{
				delete m_pTraceRecord;
				m_wndLogiMap.SetSimulationMode(FALSE);
				m_wndLogiMap.TraceMode(FALSE);
				return FALSE;
			}
		}
		else
		{
			delete m_pTraceRecord;
			m_wndLogiMap.SetSimulationMode(FALSE);
			m_wndLogiMap.TraceMode(FALSE);
		}
	}
	else if(nTraceType == MENU_SUB_RIDER_REALTIME_TRACE)
	{
		m_wndLogiMap.TraceMode(TRUE, nCompany, nRNo, TRUE, TRUE);
		m_pNormalForm->CheckVisibleAllRider();

		m_wndLogiMap.SetMapLevel(6);
		m_wndLogiMap.EnableDrawRiderMoveBoundary(TRUE);
		m_wndLogiMap.MoveMapRider(nCompany, nRNo);
		AddTraceRiderHasOrder(TRUE, nCompany, nRNo, dtBase, nForLongHour);
		m_wndLogiMap.DrawRiderMoveBoundary();
	}
	else if(nTraceType == MENU_SUB_RIDER_REALTIME_TRACE_WITH_RECENT_LOG)
	{
		m_wndLogiMap.TraceMode(TRUE, nCompany, nRNo, TRUE, TRUE);
		m_pNormalForm->CheckVisibleAllRider();

		m_wndLogiMap.SetMapLevel(6);
		m_wndLogiMap.EnableDrawRiderMoveBoundary(TRUE);
		m_wndLogiMap.MoveMapRider(nCompany, nRNo);

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_pos_log_for_trace2");
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter(nRNo);
		pCmd.AddParameter(dtBase);
		pCmd.AddParameter(nForLongHour);
		CMkParameter *parOutType = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		CMkParameter *parOutDeviceName = pCmd.AddParameter(typeString, typeOutput, 50, "");
		CMkParameter *parOutDeviceVer = pCmd.AddParameter(typeString, typeOutput, 50, "");

		if(pRs.Execute(&pCmd))
		{
			long nType = parOutType->GetLong();
			CString strDeviceName = parOutDeviceName->GetString();
			CString strDeviceVer = parOutDeviceVer->GetString();

			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				long nPosX, nPosY;
				COleDateTime dtLog;

				pRs.GetFieldValue("nPosX", nPosX);		
				pRs.GetFieldValue("nPosY", nPosY);		
				pRs.GetFieldValue("dtLog", dtLog);		

				LU->GpsPosRevision(nPosX, nPosY, nType, strDeviceName, strDeviceVer);
				m_wndLogiMap.AddTracePos(nPosX, nPosY, dtLog, TRUE);

				pRs.MoveNext();
			}
		}

		if(pRs.GetRecordCount() == 0)
		{	
			m_wndLogiMap.TraceMode(FALSE);
			return FALSE;
		}

		AddTraceRiderHasOrder(TRUE, nCompany, nRNo, dtBase, nForLongHour);
		m_wndLogiMap.DrawRiderMoveBoundary();
	}

	return TRUE;
}

void CRiderMapDlg::SetRiderPosRealTime(CRealTimeRiderPos &pos)
{	
	if(m_pNormalForm)
	{
		//m_pNormalForm->SetRiderPosRealTime(pos);

		CRealTimeRiderPos *pPos = new CRealTimeRiderPos;
		*pPos = pos;
		m_pNormalForm->PostMessage(WM_RIDER_POS_REAL_TIME, (WPARAM)pPos, 0);
	}
}

void CRiderMapDlg::OffsetMoveWindow(CWnd *pWnd, int nOffset)
{
	CRect rc;
	pWnd->GetWindowRect(rc);
	rc.left += nOffset;
	rc.right += nOffset;
	ScreenToClient(rc);
	pWnd->MoveWindow(rc);
}

void CRiderMapDlg::MoveNormalForm(BOOL bOnlyMove)
{
	if(bOnlyMove == FALSE)
		m_bHideListForm = !m_bHideListForm;
	else
	{
		BOOL bRight = m_pNormalForm->m_setinfo.bLocateRight;
		CXUIImage imgLeft = m_wndLogiMap.m_uistcLeftArrow.GetParent();
		CXUIImage imgRight = m_wndLogiMap.m_uistcRightArrow.GetParent();
		imgLeft.SetVisible(!bRight);
		imgRight.SetVisible(bRight);
	}

	CRect rcDlg;
	GetWindowRect(rcDlg);
	ScreenToClient(rcDlg);

	CRect rcTab;
	m_wndTabControl.GetWindowRect(rcTab);
	ScreenToClient(rcTab);

	long nWidth = rcTab.Width();

	CRect rcMap;
	m_wndLogiMap.GetWindowRect(rcMap);
	ScreenToClient(rcMap); 
		
	int nMaxmize = 0;
	if(m_bMaxmize)
		nMaxmize = 15;

	if(!m_bHideListForm)
	{ 
		m_wndTabControl.ShowWindow(SW_SHOW);

		if(m_pNormalForm->m_setinfo.bLocateRight == FALSE) //탭이 왼쪽에 위치
		{ 
			rcTab.left = rcDlg.left + nMaxmize;
			rcTab.right = rcTab.left + m_nNormalFormWidth;
			rcMap.left = rcTab.right + 5;
			rcMap.right = rcDlg.right - nMaxmize;
		}
		else
		{
			/*
			rcTab.right = rcDlg.right - nMaxmize;
			rcTab.left = rcTab.right - m_nNormalFormWidth;
			rcMap.left = rcDlg.left + nMaxmize;
			rcMap.right = rcTab.left - 4;			
			*/
 
			if(nWidth < 200)
				nWidth = 200;

			rcTab.right = rcDlg.right - nMaxmize;
			rcTab.left = rcTab.right - m_nNormalFormWidth;
			rcMap.left = rcDlg.left + nMaxmize;
			rcMap.right = rcTab.left - 4;			
		}

		rcTab.bottom = rcDlg.bottom - nMaxmize;
		rcMap.bottom = rcDlg.bottom - nMaxmize;

		m_wndTabControl.MoveWindow(rcTab);
		m_wndLogiMap.MoveWindow(rcMap);
	}
	else
	{
		m_wndTabControl.ShowWindow(SW_HIDE);

		rcMap.left = rcDlg.left + nMaxmize;
		rcMap.right = rcDlg.right - nMaxmize;
		rcMap.bottom = rcDlg.bottom - nMaxmize;
		m_wndLogiMap.MoveWindow(rcMap);		
		
	}

	AfxGetApp()->WriteProfileInt("CRiderMapNormalForm", "nNormalFormWidth", m_nNormalFormWidth);
	RedrawWindow();
}


void CRiderMapDlg::RefreshOrderState()
{
	m_pNormalForm->RefreshOrderState();
	if(m_wndLogiMap.m_bTraceMode && m_wndLogiMap.m_bDrawRiderMoveBoundary)
	{
		AddTraceRiderHasOrder(m_wndLogiMap.m_bShowCurHasOrder, 
				m_wndLogiMap.m_TraceRider.nCompany, 
				m_wndLogiMap.m_TraceRider.nRNo,
				m_dtBase, 
				m_nForLongTime);
	}
}

void CRiderMapDlg::SetShowOrderCount(BOOL bShow, long nShowCount)
{
	m_wndLogiMap.m_uistcOrderCount.SetCaption("오더 " + LF->GetStringFromLong(nShowCount));
	m_wndLogiMap.m_uistcOrderCount.SetVisible(bShow);
	m_wndLogiMap.m_imageOrderCount.SetVisible(bShow);

}

void CRiderMapDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		CMkRecordset *pRs = (CMkRecordset*)m_wndLogiMap.GetTraceRecord();

		long nPosX, nPosY;
		COleDateTime dtLog;

		pRs->GetFieldValue("nPosX", nPosX);		
		pRs->GetFieldValue("nPosY", nPosY);		
		pRs->GetFieldValue("dtLog", dtLog);		

		LU->GpsPosRevision(nPosX, nPosY, m_nTRDType, m_strTRDName, m_strTRDVer);
		m_wndLogiMap.AddTracePos(nPosX, nPosY, dtLog, TRUE, TRUE);

		pRs->MoveNext();

		long nSkipCount = m_nTraceTimerMSec < 10 ? 10 - m_nTraceTimerMSec : 0;
		while(nSkipCount-- > 0 && !pRs->IsEOF())
			pRs->MoveNext();

		if(pRs->IsEOF())
		{
			m_wndLogiMap.SetSimulationMode(FALSE);
			m_pNormalForm->m_pMap->DeleteTraceNavi();
			KillTimer(nIDEvent);
		}
	}	

	CDialog::OnTimer(nIDEvent);
}

void CRiderMapDlg::AddTraceRiderHasOrder(BOOL bShowCurHasOrder, long nCompany, long nRNo, COleDateTime dtBase, long nForLongHour)
{
	m_dtBase = dtBase;
	m_nForLongTime = nForLongHour;

	m_wndLogiMap.DeleteTraceRiderHasOrder();

	OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;
	BOOL bClear = TRUE;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nState >= 11 && it->second.nState <= 35)
		{
			if(it->second.nRiderCompany == nCompany &&
				it->second.nRNo == nRNo)
			{
				m_wndLogiMap.AddTraceRiderHasOrder(bShowCurHasOrder, 
					it->second.nTNo, it->second.nState, 
					it->second.strStart.c_str(), m_poiNew.GetDongPOI(it->second.nStartRealDongID)->GetDong(),
					it->second.nStartPosX, it->second.nStartPosY,
					it->second.strDest.c_str(), m_poiNew.GetDongPOI(it->second.nDestRealDongID)->GetDong(),
					it->second.nDestPosX, it->second.nDestPosY,
#ifndef _DAERI
					it->second.dt3, it->second.dt4, it->second.dtFinal);
#else
					it->second.dt3, COleDateTime::GetCurrentTime(), it->second.dtFinal);
#endif
			}
		}
	}
}

void CRiderMapDlg::OnEnChangeRnoEdt()
{
	if(m_RNoEdt.GetWindowTextLength() == 0)
		return;

	CString sRNo; 
	m_RNoEdt.GetWindowText(sRNo);
   	m_pNormalForm->FindRNo(sRNo);
	
}

CWnd* CRiderMapDlg::GetActiveForm()
{
	if(m_wndTabControl.GetItemCount() < 0 ) return NULL;
	int nCurSel = m_wndTabControl.GetCurSel();
	if( nCurSel < 0 ) return NULL;

	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(nCurSel);
	return CWnd::FromHandle(pItem->GetHandle());
}

void CRiderMapDlg::OrderClickAutoMoveMap(long nPosX, long nPosY, long nRCompany, long nRNo, BOOL bNearRider)
{
	if(bNearRider)
		if(m_pNormalForm->m_setinfo.nNearRiderLevel > 0)
			m_wndLogiMap.SetMapLevel(m_pNormalForm->m_setinfo.nNearRiderLevel);

	if(m_pNormalForm->m_setinfo.nOrderClickRiderMove && nRCompany > 0 && nRNo > 0)
		m_wndLogiMap.MoveMapRider(nRCompany, nRNo);
	else if(m_pNormalForm->m_setinfo.nOrderClickAutoMove)
		m_wndLogiMap.MoveMap(nPosX, nPosY);

}

void CRiderMapDlg::SetRiderConnState(long nCompany, long nRNo, long nState)
{
	if(m_pNormalForm)
		m_pNormalForm->SetRiderConnState(nCompany, nRNo, nState);
}

LRESULT CRiderMapDlg::OnMapUIMouseUP(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case 600:
		case 602:
			MoveNormalForm();
			m_wndLogiMap.m_uistcLeftArrow.SetCaption(m_bHideListForm ? "->" : "<-");
			m_wndLogiMap.m_uistcRightArrow.SetCaption(m_bHideListForm ? "<-" : "->");
			break;

		case 700:		//추척모드 해제
			KillTimer(1);
			m_wndLogiMap.TraceMode(FALSE);
			m_wndLogiMap.DeleteTraceNavi();
			m_pNormalForm->CheckVisibleAllRider();
			break;
		case 800:		//정지
			KillTimer(1);
			break;
		case 801:		//진행
			SetTimer(1, m_nTraceTimerMSec, NULL);
			break;
		case 802:		//스피드업
			m_nTraceTimerMSec -= 2;
			m_nTraceTimerMSec = max(0, m_nTraceTimerMSec);
			SetTimer(1, m_nTraceTimerMSec, NULL);
			break;
		case 803:		//스피드다운
			m_nTraceTimerMSec += 2;
			m_nTraceTimerMSec = min(1000, m_nTraceTimerMSec);
			SetTimer(1, m_nTraceTimerMSec, NULL);
			break;
	}

	return 0;
}

void CRiderMapDlg::ShowLeftForm(BOOL bShow) 
{ 
	if(bShow == m_bHideListForm)
		MoveNormalForm();
}


BOOL CRiderMapDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_MOUSEMOVE)
	{
		CPoint point; ::GetCursorPos(&point);
		ScreenToClient(&point); 

		if(m_bMoveControl)
		{ // 커서 땜시 10 위로 
			SetCursor(m_hcVertical);  
			m_bMustMoveControl = TRUE; 
		}
		else
		{
			CRect rcReport, rcOPReport;   

			m_wndTabControl.GetWindowRect(&rcReport);
			m_wndLogiMap.GetWindowRect(&rcOPReport);

			if(rcOPReport.left < rcReport.left)
			{
				CRect rcTemp;
				rcTemp = rcReport;
				rcReport = rcOPReport;
				rcOPReport = rcTemp;
			}

			ScreenToClient(rcReport);
			ScreenToClient(rcOPReport);  

			//g_bana_log->Print("%d %d %d\r\n", point.x, rcReport.right, rcOPReport.left);

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
 
	if(pMsg->message == WM_LBUTTONUP)
	{
		m_bMoveControl = FALSE;
		m_bChangeCursor = FALSE;
		SetCursor(m_hcArrow);

		if(m_bMustMoveControl)
			MoveControl();
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CRiderMapDlg::UpdateShowRiderCount(long nCount)
{
	//long nCount = m_pNormalForm->m_wndReport.GetRows()->GetCount();
	CString strTemp = LF->GetStringFromLong(nCount) +"명";

	m_wndLogiMap.m_uistcCount.SetCaption(strTemp);
}

void CRiderMapDlg::OnLButtonUp(UINT nFlags, CPoint point)
{	
	CMyDialog::OnLButtonUp(nFlags, point);
}

void CRiderMapDlg::MoveControl()
{
	CPoint point; ::GetCursorPos(&point);
	ScreenToClient(&point);
  
	CRect rcPage;
	this->GetWindowRect(&rcPage);

	CRect rcReport, rcOPReport;   

	m_wndTabControl.GetWindowRect(&rcReport);
	m_wndLogiMap.GetWindowRect(&rcOPReport); 
 	
	ScreenToClient(rcReport);
	ScreenToClient(rcOPReport);

	if(rcOPReport.left < rcReport.left)
	{
		rcOPReport.right = point.x - 4;
		rcReport.left = point.x + 4;   
	}
	else
	{
		rcReport.right = point.x - 4;
		rcOPReport.left = point.x + 4;   
	}

	//m_nNormalFormWidth = point.x;
	m_nNormalFormWidth = rcReport.Width();

	AfxGetApp()->WriteProfileInt("CRiderMapNormalForm", "nNormalFormWidth", m_nNormalFormWidth);
	//g_bana_log->Print("zx %d %d %d %d %d\r\n", point.x, rcReport.left, rcReport.right, rcOPReport.left, rcOPReport.right);

	if(rcReport.Width() > 100 && rcOPReport.Width() > 100)   
	{
		m_wndTabControl.MoveWindow(rcReport);
		m_wndLogiMap.MoveWindow(rcOPReport);
	}		

	m_bMustMoveControl= FALSE;
}