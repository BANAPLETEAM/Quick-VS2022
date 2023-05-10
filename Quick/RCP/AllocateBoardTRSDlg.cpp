// AllocateBoardTRSDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateBoardTRSDlg.h"
#include "RcpView.h"
#include "MakeHtmlTable.h"
#include "AllocateBoardTRSSetDlg.h"
#include "AllocateTRSReportPaintManager.h"

#define REFRESH_TIME	10000
#define WINDOW_CAPTION "TRS배차판 (F9설정변경)"

static LOGFONT lfBoldFont = {11,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움체"};
static COLORREF crGreen = RGB(150,255,150);



// CAllocateBoardTRSDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateBoardTRSDlg, CMyDialog)
CAllocateBoardTRSDlg::CAllocateBoardTRSDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateBoardTRSDlg::IDD, pParent)
{
	m_nOneWidth = 138;
	m_nTopIndex = -1;
	m_nWorkStateRiderCount = 0;
	m_nOfficeLine1 = 0;
	m_nOfficeLine2 = 0;
	m_nOfficeLine3 = 0;
	m_nOfficeLine4 = 0;
	m_nShowType = 0;
	m_strServerIP = "";
	m_nServerPort = 0;
	m_bShutDown = FALSE;
	m_nIndex = 0;
	m_pSocket = NULL;
	m_pSelectedRecordItem = NULL;

}

CAllocateBoardTRSDlg::~CAllocateBoardTRSDlg()
{
	m_bShutDown = TRUE;
	if(m_pSocket)
		m_pSocket->Close();
	Sleep(1000);
}

void CAllocateBoardTRSDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
}


BEGIN_MESSAGE_MAP(CAllocateBoardTRSDlg, CMyDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_REFRESH_LIST, OnRefreshList)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
//	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDblClick)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_BN_CLICKED(IDC_TEST_BTN, OnBnClickedTestBtn)
	ON_WM_TIMER()
	ON_COMMAND(ID_RIDER_INFO, OnRiderInfo)
	ON_COMMAND_RANGE(ID_LIMIT_30, ID_LIMIT_RELEASE, OnAllocateLimit)
	ON_COMMAND_RANGE(ID_LIMIT_LEVEL1, ID_LIMIT_LEVEL5, OnAllocateLimitLevel)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CAllocateBoardTRSDlg 메시지 처리기입니다.

BOOL CAllocateBoardTRSDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CenterWindow(GetDesktopWindow());

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_pRPM = new CAllocateTRSReportPaintManager;

	LoadOption();

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

	//SetTimer(0, REFRESH_TIME, NULL);

	DWORD dwThreadID;
	//소켓 통신용 쓰레드 생성
	HANDLE  threadHandle1 =  ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticSocketRead, 
		(LPVOID) this, 0, &dwThreadID);
	::CloseHandle(threadHandle1);

	if(m_strServerIP.GetLength() == 0)
	{
		PostMessage(WM_KEYDOWN, VK_F9, 0);
		PostMessage(WM_KEYUP, VK_F9, 0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateBoardTRSDlg::RefreshRiderList(CString strSearchKeyword)
{
	CRect rc;
	m_wndReport.GetClientRect(&rc);
	m_pRPM->ResortRider();

	CXTPGridRow *pRow = m_wndReport.HitTest(CPoint(rc.left+2, rc.bottom - m_pRPM->GetRowHeight(NULL, NULL)));
	if(pRow) 
		m_nTopIndex = pRow->GetIndex();

	m_wndReport.GetColumns()->Clear();
	m_wndReport.GetRows()->Clear();
	m_wndReport.GetRecords()->RemoveAll();
	m_wndReport.GetClientRect(rc);
	int nCols = rc.Width() / m_nOneWidth;

	for(int i = 0; i < nCols; i++)
	{
		CXTPGridColumn* pCol1 = 
			m_wndReport.AddColumn(new CXTPGridColumn(i, "", m_nOneWidth, FALSE));
	}


	long nCol, nRow = -1, n = 0;
	CXTPGridRecord *pRecord = NULL;
	ALLOCATE_RIDER_VECTOR2::iterator it;
	m_nWorkStateRiderCount = 0;

	for(it = m_pRPM->m_vecRider.begin(); it != m_pRPM->m_vecRider.end(); it++)
	{
		ALLOCATE_BOARD_RIDER_INFO2 *rider = *it;

		if(m_nShowType == 1) //키받은기사만
		{
			if(rider->dtLastAck < COleDateTime::GetCurrentTime() - COleDateTimeSpan(1, 0, 0, 0))
				continue;
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

		if(rider->nRNo == rider->nLine)
			strTemp.Format("%d/%s", rider->nRNo, rider->strName);
		else
			strTemp.Format("%d/%s(%d)", rider->nRNo, rider->strName, rider->nLine);

		if(rider->strGroupName.GetLength() > 0)
			strTemp += "(" + rider->strGroupName + ")";

		CMyRecordItem2 *pRecordItem = new CMyRecordItem2(strTemp);
		pRecordItem->pAllocRiderInfo = rider;
		pRecord->AddItem(pRecordItem);
	}

	if(pRecord)
		m_wndReport.AddRecord(pRecord);

	m_wndReport.Populate();
}

void CAllocateBoardTRSDlg::GetRiderInfo(long nLine)
{
	int nCompany = m_ci.m_nCompanyCode;
	CString strName = "미등록", strTel, strPosName, strDong, strGroupName;
	COleDateTime dtWorkReport, dtPos;
	BOOL bWorkReport = 0, bGpsPos = 0;
	long nWorkState = 0, nAllocateLimitMin = 0, nRNo = nLine;
	long nTRSAllocateLimitMin = 0, nTRSPenaltyLevel = 0;
	BOOL bConnRider = 0;


	if(m_nOfficeLine1 == nLine || m_nOfficeLine2 == nLine ||
		m_nOfficeLine3 == nLine || m_nOfficeLine4 == nLine)
	{
		ALLOCATE_BOARD_RIDER_INFO2 *rider = new ALLOCATE_BOARD_RIDER_INFO2;
		rider->nCompany = nCompany;
		rider->nRNo = nLine;
		rider->strPhone = strTel;
		rider->nAllocCount = 0;
		rider->nFinishCount = 0;
		rider->nTotalCount = 0;
		rider->nTotalCharge = 0;
		rider->nWorkState = nWorkState;
		rider->nAttendType = bWorkReport ? 1 : 0;
		rider->dtAttend = bWorkReport ? dtWorkReport : COleDateTime(2100, 1, 1, 1, 1, 1);
		rider->nAllocateLimitMin = nAllocateLimitMin;
		rider->bOfficeLine = TRUE;
		rider->bConnRider = FALSE;
		rider->bGpsPos = bGpsPos;
		rider->bConnRider = bConnRider;
		rider->strGroupName = strGroupName;
		rider->dtLastAck = COleDateTime::GetCurrentTime();
		rider->nPenaltyLevel = nTRSPenaltyLevel;
		rider->nLine = nLine;

		if(m_nOfficeLine1 == nLine)
			rider->strName = "상황실";
		else if(m_nOfficeLine2 == nLine)
			rider->strName = "상황실2";
		else if(m_nOfficeLine3 == nLine)
			rider->strName = "상황실3";
		else if(m_nOfficeLine4 == nLine)
			rider->strName = "상황실4";
		
		m_pRPM->m_vecRider.push_back(rider);
		m_pRPM->m_mapRider.insert(ALLOCATE_RIDER_MAP2::value_type(
			std::make_pair(nLine, m_nIndex++), rider));
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_trs_board_rider_one2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nLine);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() > 0)
	{
		pRs.GetFieldValue("nMNo", nRNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sHp", strTel);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("bWorkReport", bWorkReport);
		pRs.GetFieldValue("dtWorkReport", dtWorkReport);
		pRs.GetFieldValue("sPosName", strPosName);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("bWorkReport", bWorkReport);
		pRs.GetFieldValue("dtPos", dtPos);
		pRs.GetFieldValue("nAllocateLimitMin", nAllocateLimitMin);
		pRs.GetFieldValue("bGPSUsage", bGpsPos);
		pRs.GetFieldValue("bConnRider", bConnRider);
		pRs.GetFieldValue("sGroupName", strGroupName);
		pRs.GetFieldValue("nTRSPenaltyLevel", nTRSPenaltyLevel);
		pRs.GetFieldValue("nTRSAllocateLimitMin", nTRSAllocateLimitMin);
	}

	ALLOCATE_BOARD_RIDER_INFO2* rider = new ALLOCATE_BOARD_RIDER_INFO2;

	rider->nCompany = nCompany;
	rider->nRNo = nRNo;
	rider->strName = strName;
	if(strDong.GetLength() > 0)
	{
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - dtPos;
		if(span.GetTotalHours() < 5)
		{
			rider->strCurPosName = strDong + " " + strPosName;
			rider->dtPos = dtPos;
		}
	}

	rider->strPhone = strTel;
	rider->nAllocCount = 0;
	rider->nFinishCount = 0;
	rider->nTotalCount = 0;
	rider->nTotalCharge = 0;
	rider->nWorkState = nWorkState;
	rider->nAttendType = bWorkReport ? 1 : 0;
	rider->dtAttend = bWorkReport ? dtWorkReport : COleDateTime(2100, 1, 1, 1, 1, 1);
	rider->nAllocateLimitMin = nTRSAllocateLimitMin > 0 ? nTRSAllocateLimitMin : nAllocateLimitMin;
	rider->bOfficeLine = FALSE;
	rider->bConnRider = FALSE;
	rider->bGpsPos = bGpsPos;
	rider->bConnRider = bConnRider;
	rider->strGroupName = strGroupName;
	rider->dtLastAck = COleDateTime::GetCurrentTime();
	rider->nPenaltyLevel = nTRSPenaltyLevel;
	rider->nLine = nLine;

	m_pRPM->m_vecRider.push_back(rider);
	m_pRPM->m_mapRider.insert(ALLOCATE_RIDER_MAP2::value_type(
		std::make_pair(nRNo, m_nIndex++), rider));

}

void CAllocateBoardTRSDlg::RefreshList()
{
	m_pRPM->m_mapOrder.clear();

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::reverse_iterator it;
	long nCompleteCount = 0, nCancelCount = 0;
	RIDER_LAST_ACTION_MAP2::iterator itAction;

	for(it = order.rbegin(); it != order.rend(); it++)
	{
		if(LF->IsAllocOrder(it->second.nState))
		{
			itAction = m_mapRiderLastAction.find(std::make_pair(it->second.nRiderCompany, it->second.nRNo));
			if(itAction == m_mapRiderLastAction.end())
			{
				ST_ARIDER arider;
				arider.nCompany = it->second.nRiderCompany;
				arider.nRNo = it->second.nRNo;
				arider.dtLast = it->second.dtState;
				arider.nLastTNo = it->second.nTNo;
				m_mapRiderLastAction.insert(RIDER_LAST_ACTION_MAP2::value_type(
					std::make_pair(it->second.nRiderCompany, it->second.nRNo), 
					arider));
			}
			else if(itAction->second.dtLast < it->second.dtState)
			{
				itAction->second.dtLast = it->second.dtState;
				itAction->second.nLastTNo = it->second.nTNo;
			}


			ALLOCATE_ORDER_INFO2 order;
			order.nCompany = it->second.nRiderCompany;
			order.nRNo = it->second.nRNo;
			order.nState = it->second.nState;
			order.strStart = it->second.strStart.c_str();
			order.strDest = it->second.strDest.c_str();
			order.nCharge = it->second.nCharge;
			order.nWayType = 0;
			order.dtTime = it->second.dtState;

			m_pRPM->m_mapOrder.insert(ALLOCATE_ORDER_MAP2::value_type(
				std::make_pair(it->second.nRiderCompany, it->second.nRNo), order));

			if(m_ci.IsChildCompany(it->second.nCompany))
				nCompleteCount++;
		}
		else if(it->second.nState == 40)
		{
			nCancelCount++;
		}
	}


	ALLOCATE_RIDER_VECTOR2::iterator itSize;
	for(itSize = m_pRPM->m_vecRider.begin(); itSize != m_pRPM->m_vecRider.end(); itSize++)
	{
		ALLOCATE_BOARD_RIDER_INFO2 *rider = *itSize;
		if(rider->strCurPosName.IsEmpty())
		{
			itAction = m_mapRiderLastAction.find(std::make_pair(rider->nCompany, rider->nRNo));
			if(itAction != m_mapRiderLastAction.end())
			{
				rider->dtLastAction = itAction->second.dtLast;
				OrderRecordList::iterator it;
				it = order.find(itAction->second.nLastTNo);
				if(it != order.end())
				{
					rider->strCurPosName.Format("(X)%s", it->second.strDest.c_str());
					rider->dtPos = itAction->second.dtLast;
					rider->nPosX = it->second.nState == 35 ? it->second.nDestPosX : it->second.nStartPosX;
					rider->nPosY = it->second.nState == 35 ? it->second.nDestPosY : it->second.nStartPosY;
					rider->bGpsPos = FALSE;
				}
			}
			else
			{
/*
				rider->dtLastAction = COleDateTime(2000, 1, 1, 1, 1, 1);

				COleDateTime dtToday = COleDateTime::GetCurrentTime();
				if(dtToday.GetHour() < 10.5)
				{
					if(rider->nHomeDongID > 0)
					{
						CPOIUnit *pPOI = m_poi.FindDataFromID(rider->nHomeDongID);
						if(pPOI)
						{
							if(strcmp(pPOI->szGugun, pPOI->szDong) == 0)
								rider->strCurPosName.Format("(H)%s", pPOI->szGugun);
							else
								rider->strCurPosName.Format("(H)%s%s", pPOI->szGugun, pPOI->szDong);
							rider->dtPos = COleDateTime::GetCurrentTime();
							rider->nPosX = pPOI->dPosX * 1000000;
							rider->nPosY = pPOI->dPosY * 1000000;
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
*/
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
}


void CAllocateBoardTRSDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(nType == SIZE_MINIMIZED) return;

	if(m_wndReport.GetSafeHwnd())
	{
		m_wndReport.SetWindowPos(NULL, 0, 0, cx, cy, 0);
		RefreshRiderList();
	}
}


void CAllocateBoardTRSDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 170;

	CMyDialog::OnGetMinMaxInfo(lpMMI);
}


void CAllocateBoardTRSDlg::OnClose()
{
	m_pParentWnd->PostMessage(WM_CLOSE_TRS_BOARD_DLG, 0, 0);
	CMyDialog::OnClose();
}

void CAllocateBoardTRSDlg::OnOK()
{
	OnClose();
}

void CAllocateBoardTRSDlg::OnCancel()
{
	OnClose();
}


void CAllocateBoardTRSDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
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

					CMyRecordItem2 *pItem = (CMyRecordItem2*)pRow->GetRecord()->GetItem(pCol);
					if(pItem)
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


BOOL CAllocateBoardTRSDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	if(pMsg->message == WM_KEYDOWN)
	{	
		if(pMsg->wParam >= VK_F1 && pMsg->wParam <= VK_F4)
		{
			SetRiderAck(pMsg->wParam - VK_F1 + 1);
			return TRUE;
		}
		else if(pMsg->wParam == VK_F9)
		{
			CAllocateBoardTRSSetDlg dlg(this);
			dlg.m_nOfficeLine1 = m_nOfficeLine1;
			dlg.m_nOfficeLine2 = m_nOfficeLine2;
			dlg.m_nOfficeLine3 = m_nOfficeLine3;
			dlg.m_nOfficeLine4 = m_nOfficeLine4;
			dlg.m_strServerIP = m_strServerIP;
			dlg.m_strServerPort.Format("%d", m_nServerPort);
			if(IDOK == dlg.DoModal())
			{
				LoadOption();
				RefreshRiderList();
			}
			return TRUE;
		}
		else if(pMsg->wParam == VK_F5)
		{
			//GetRiderList(TRUE);
			RefreshRiderList();
			return TRUE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CAllocateBoardTRSDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CMyRecordItem2 *pItem = (CMyRecordItem2*)pItemNotify->pRow->GetRecord()->GetItem(pItemNotify->pColumn);
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(!pItem->pAllocRiderInfo->bOfficeLine)
		LU->GetRcpView()->SendMessage(WM_RIDER_ALLOCATE2, (WPARAM)nRNo, (LPARAM)nRiderCompany);
}


void CAllocateBoardTRSDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CMyRecordItem2 *pItem = (CMyRecordItem2*)pItemNotify->pRow->GetRecord()->GetItem(pItemNotify->pColumn);
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	if(!pItem->pAllocRiderInfo->bOfficeLine)
		LU->GetRcpView()->SendMessage(WM_RIDER_ALLOCATE2, (WPARAM)nRNo, (LPARAM)nRiderCompany);
}

void CAllocateBoardTRSDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	m_pSelectedRecordItem = GetCursorRecordItem();

	//m_wndReport.GetSelectedRows()->Select(pItemNotify->pRow);

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);
}


LONG CAllocateBoardTRSDlg::OnRefreshList(WPARAM wParam, LPARAM lParam)
{
	RefreshList();
	RefreshRiderList();
	return 0;
}

void CAllocateBoardTRSDlg::OnBnClickedTestBtn()
{
	SetRiderAck(2009);
}

void CAllocateBoardTRSDlg::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);
	//GetRiderList(TRUE);
	RefreshRiderList();
	SetTimer(nIDEvent, REFRESH_TIME, NULL);
	CMyDialog::OnTimer(nIDEvent);
}

void CAllocateBoardTRSDlg::SetRiderAck(long nTRSID)
{
	static long nLastAck = 0;
	static DWORD dwTick = 0;

	if(nLastAck != nTRSID || GetTickCount() - dwTick > 60000)
	{
		GetRiderInfo(nTRSID);
		RefreshRiderList();

		nLastAck = nTRSID;
		dwTick = GetTickCount();
	}
}

void CAllocateBoardTRSDlg::LoadOption()
{
	m_nOfficeLine1 = AfxGetApp()->GetProfileInt("TRS", "OfficeLine1", 0);
	m_nOfficeLine2 = AfxGetApp()->GetProfileInt("TRS", "OfficeLine2", 0);
	m_nOfficeLine3 = AfxGetApp()->GetProfileInt("TRS", "OfficeLine3", 0);
	m_nOfficeLine4 = AfxGetApp()->GetProfileInt("TRS", "OfficeLine4", 0);
	m_strServerIP = AfxGetApp()->GetProfileString("TRS", "ServerIP", "");
	m_nServerPort = AfxGetApp()->GetProfileInt("TRS", "ServerPort", 0);

	m_crPenalty1 = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor1", STATE_COLOR_PENALTY);
	m_crPenalty2 = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor2", STATE_COLOR_PENALTY);
	m_crPenalty3 = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor3", STATE_COLOR_PENALTY);
	m_crPenalty4 = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor4", STATE_COLOR_PENALTY);
	m_crPenalty5 = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor5", STATE_COLOR_PENALTY);

	m_nPenaltyMin1 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin1", 0);
	m_nPenaltyMin2 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin2", 0);
	m_nPenaltyMin3 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin3", 0);
	m_nPenaltyMin4 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin4", 0);
	m_nPenaltyMin5 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin5", 0);

	m_pRPM->m_crPenalty[0] = m_crPenalty1;
	m_pRPM->m_crPenalty[1] = m_crPenalty2;
	m_pRPM->m_crPenalty[2] = m_crPenalty3;
	m_pRPM->m_crPenalty[3] = m_crPenalty4;
	m_pRPM->m_crPenalty[4] = m_crPenalty5;
}

UINT CAllocateBoardTRSDlg::SocketRead(LPVOID lParam)
{
	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE+2] = {0,};
	CQSocket socket;
	
	((CAllocateBoardTRSDlg*)lParam)->m_pSocket = &socket;

	socket.Create();

	while(FALSE == m_bShutDown)
	{
		Sleep(500);

		if(m_strServerIP.GetLength() > 0)
		{
			char szBuffer[1024];

			socket.SetConnTimeOut(5);

			if(socket.Connect(m_strServerIP, m_nServerPort))
			{
				SetWindowText(CString("[접속됨]") + WINDOW_CAPTION);

				socket.SetTimeOut(30);
				while(1)
				{
					int nLen = socket.Read(szBuffer, 1024);
					if(nLen > 0)
					{
						szBuffer[nLen] = 0;

						CString strTemp = szBuffer;
						strTemp.Replace("iDEN:", "");
						strTemp.Replace(",", "");

						int nLineID = atol(strTemp);
						g_bana_log->Print("TRS eagle = %s, %d\n", szBuffer, nLineID);

						if(nLineID > 0)
							SetRiderAck(nLineID);
					}
					else
					{
						int nError = WSAGetLastError();
						if(nError != WSAEWOULDBLOCK &&
							nError != WSAETIMEDOUT)
						{
							if(socket.Connect(m_strServerIP, m_nServerPort))
								socket.SetTimeOut(5);
							else
							{
								if(m_bShutDown) break;
								Sleep(1000);
							}
						}
						Sleep(10);
					}

              	}
				socket.Close();
			}
			else
			{
				SetWindowText(WINDOW_CAPTION);
			}
		}
	}

	((CAllocateBoardTRSDlg*)lParam)->m_pSocket = NULL;

	return 0;
}

void CAllocateBoardTRSDlg::OnContextMenu(CWnd* pWnd, CPoint point)
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
	CMenu *pRMenu=rMenu.GetSubMenu(20);


	CMyRecordItem2 *pItem = (CMyRecordItem2*)m_pSelectedRecordItem;
	long nRiderCompany = pItem->pAllocRiderInfo->nCompany;
	long nRNo = pItem->pAllocRiderInfo->nRNo;

	DWORD dwRetValue = pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	LU->GetRcpView()->SetRefreshStart();
}

CXTPGridRecordItem* CAllocateBoardTRSDlg::GetCursorRecordItem()
{
	CPoint point;
	::GetCursorPos(&point);

	m_wndReport.ScreenToClient(&point);

	CXTPGridRow * pRow = m_wndReport.HitTest(point);
	CRect rcCol;

	CXTPGridColumn *pCol = NULL;
	pRow->HitTest(point, &rcCol, &pCol);

	return pRow->GetRecord()->GetItem(pCol->GetIndex());
}

void CAllocateBoardTRSDlg::OnRiderInfo()
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem2 *pItem = (CMyRecordItem2*)m_pSelectedRecordItem;
	LU->ShowRiderInfoDlg(pItem->pAllocRiderInfo->nCompany, pItem->pAllocRiderInfo->nRNo);
}

void CAllocateBoardTRSDlg::OnAllocateLimit(UINT nID)
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem2 *pItem = (CMyRecordItem2*)m_pSelectedRecordItem;

	int nLimitMin = 0;

	if(nID == ID_LIMIT_30)
		nLimitMin = 30;
	else if(nID == ID_LIMIT_60)
		nLimitMin = 60;
	else if(nID == ID_LIMIT_90)
		nLimitMin = 90;
	else if(nID == ID_LIMIT_120)
		nLimitMin = 120;
	else if(nID == ID_LIMIT_150)
		nLimitMin = 150;
	else if(nID == ID_LIMIT_180)
		nLimitMin = 180;
	else if(nID == ID_LIMIT_210)
		nLimitMin = 210;
	else if(nID == ID_LIMIT_240)
		nLimitMin = 240;
	else if(nID == ID_LIMIT_270)
		nLimitMin = 270;
	else if(nID == ID_LIMIT_300)
		nLimitMin = 300;
	else if(nID == ID_LIMIT_360)
		nLimitMin = 360;
	else if(nID == ID_LIMIT_420)
		nLimitMin = 420;
	else if(nID == ID_LIMIT_480)
		nLimitMin = 480;
	else if(nID == ID_LIMIT_540)
		nLimitMin = 540;
	else if(nID == ID_LIMIT_600)
		nLimitMin = 600;

	if(nID == ID_LIMIT_RELEASE)
	{
		CMkCommand pCmd(m_pMkDb, "update_driver_limit_release2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nRNo);
		if(pCmd.Execute())
		{
			pItem->pAllocRiderInfo->nAllocateLimitMin = 0;
			MessageBox("배차제한이 해제되었습니다.", "확인", MB_ICONINFORMATION);
		}
	}
	else
	{
		CMkCommand pCmd(m_pMkDb, "update_allocate_limit_only_time");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nRNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nLimitMin);
		if(pCmd.Execute())
		{
			CString strMsg;
			strMsg.Format("%d분의 배차제한이 설정되었습니다.(단말기 배차도 블가능함)", nLimitMin);

			pItem->pAllocRiderInfo->nAllocateLimitMin = nLimitMin;
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}
	}
}

void CAllocateBoardTRSDlg::OnAllocateLimitLevel(UINT nID)
{
	if(m_pSelectedRecordItem == NULL) return;

	CMyRecordItem2 *pItem = (CMyRecordItem2*)m_pSelectedRecordItem;

	int nLimitMin = 0;
	int nLimitLevel = 0;

	if(nID == ID_LIMIT_LEVEL1)
	{
		nLimitMin = m_nPenaltyMin1;
		nLimitLevel = 1;
	}
	else if(nID == ID_LIMIT_LEVEL2)
	{
		nLimitMin = m_nPenaltyMin2;
		nLimitLevel = 2;
	}
	else if(nID == ID_LIMIT_LEVEL3)
	{
		nLimitMin = m_nPenaltyMin3;
		nLimitLevel = 3;
	}
	else if(nID == ID_LIMIT_LEVEL4)
	{
		nLimitMin = m_nPenaltyMin4;
		nLimitLevel = 4;
	}
	else if(nID == ID_LIMIT_LEVEL5)
	{
		nLimitMin = m_nPenaltyMin5;
		nLimitLevel = 5;
	}


	if(nLimitMin <= 0)
	{
		MessageBox("레벨 페널티에 대한 시간설정을 하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}


	CMkCommand pCmd(m_pMkDb, "update_allocate_limit_trs");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), pItem->pAllocRiderInfo->nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nLimitMin);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nLimitLevel);
	if(pCmd.Execute())
	{
		CString strMsg;
		strMsg.Format("%d차 %d분의 배차제한이 설정되었습니다.(단말기 배차 가능함)", nLimitLevel, nLimitMin);

		pItem->pAllocRiderInfo->nAllocateLimitMin = nLimitMin;
		pItem->pAllocRiderInfo->nPenaltyLevel = nLimitLevel;

		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
	}
}

