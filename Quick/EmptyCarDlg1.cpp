// EmptyCarDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "EmptyCarDlg1.h"
#include "RcpView.h"
#include "MkLock.h"
#include "DelayOrderDlg2.h"
#include "CancelDlg.h"
#include "MakeHtmlTable.h" 


static LOGFONT lfSmallEdit = {14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};


//const char *szRefreshText2[] = {"수동갱신", "1초", "3초", "5초", "10초", "15초", "20초", "30초", 
//"40초", "50초", "1분", "2분", "5분", "10분"};
#define ONE_ROW_COUNT 4
IMPLEMENT_DYNCREATE(CEmptyCarDlg1, CMyFormView)

CEmptyCarDlg1::CEmptyCarDlg1()
	: CMyFormView(CEmptyCarDlg1::IDD)
{
	LU->SetEmptyCarPane(this);
	m_nDiscountSec = -1;
	m_bFirst = TRUE;
	m_bDragMode = FALSE;

	m_sSearch = "";
	m_bFollowRcpRefresh = FALSE;
}

CEmptyCarDlg1::~CEmptyCarDlg1()
{
}

void CEmptyCarDlg1::DoDataExchange(CDataExchange* pDX)
{	
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_REPORT_LIST2, m_wndReport2);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdt);
}

BEGIN_MESSAGE_MAP(CEmptyCarDlg1, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CEmptyCarDlg1 진단입니다.

#ifdef _DEBUG
void CEmptyCarDlg1::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CEmptyCarDlg1::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CEmptyCarDlg1 메시지 처리기입니다.

void CEmptyCarDlg1::OnBnClickedRefreshBtn()
{
	RefreshList();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CEmptyCarDlg1::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate(); 

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);

	m_pEPM = new CEmptyPaintManager();

	m_wndReport.SetPaintManager(m_pEPM);
	m_wndReport.SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(212, 208, 200));
	//	m_WorkReport.GetPaintManager()->SetTextFont(m_lfList);
	m_wndReport.GetPaintManager()->m_strNoItems = "조건에 맞는 데이터가 존재하지 않습니다.";
	m_wndReport.GetPaintManager()->SetTextFont(lfSmallEdit);
	m_wndReport.ShowHeader(FALSE);

	m_wndReport2.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport2.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport2.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport2.GetReportHeader()->AllowColumnSort(FALSE);
	
	m_pAPM = new CEmptyPaintManager();

	m_wndReport2.SetPaintManager(m_pAPM);
	m_wndReport2.SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport2.SetGridColor(RGB(212, 208, 200));
	//	m_WorkReport.GetPaintManager()->SetTextFont(m_lfList);
	m_wndReport2.GetPaintManager()->m_strNoItems = "조건에 맞는 데이터가 존재하지 않습니다.";
	m_wndReport2.GetPaintManager()->SetTextFont(lfSmallEdit);
	m_wndReport2.ShowHeader(FALSE);

	m_wndReport.Populate();
	m_wndReport2.Populate();

	LU->m_pEmptyCarPane = this;
	
	GetRider();

	SetResize(IDC_REPORT_LIST, sizingBottom);
	SetResize(IDC_REPORT_LIST2, sizingBottom);

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
	m_tooltip.AddTool(&m_wndReport2, "");

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CEmptyCarDlg1::RefreshList(BOOL bSearchOrder)
{
	if(bSearchOrder)
	{
		InitRider();
		InitOrderMap();
	}		

	CRect rc;

	m_wndReport.GetColumns()->Clear();
	m_wndReport.GetRows()->Clear();
	m_wndReport.GetRecords()->RemoveAll();

	m_wndReport2.GetColumns()->Clear();
	m_wndReport2.GetRows()->Clear();
	m_wndReport2.GetRecords()->RemoveAll();

	m_wndReport.GetClientRect(rc);
	int nOneWidth = rc.Width() / ONE_ROW_COUNT;

	for(int i=0; i<ONE_ROW_COUNT; i++)
	{
		CXTPGridColumn* pCol1 = 
			m_wndReport.AddColumn(new CXTPGridColumn(i, "", nOneWidth, FALSE));

		CXTPGridColumn* pCol2 = 
			m_wndReport2.AddColumn(new CXTPGridColumn(i, "", nOneWidth, FALSE));
	}

	CXTPGridRecord *pRecord = NULL;
	CXTPGridRecord *pRecord2 = NULL;
	EMPTY_RIDER_VECTOR::iterator it;

	long nCol = 0;
	long nWndReport = 0;
	long nWndReport2 = 0;

//	std::sort(m_RiderVec.begin(), m_RiderVec.end(), compare_greator_rider_no);
 
	
	for(it = m_RiderVec.begin(); it != m_RiderVec.end(); it++)
	{
		ST_RIDER_STRUCT *rider = *it;
 
		if(bSearchOrder)
		{
			UpdateLastLocation(rider);
		}
		else
		{
			if(m_sSearch != "") 
			{
				if((rider->strLastLocation.Find(m_sSearch) == -1) ) 
					continue;
			}
		}		

		if(!rider->bEmpty)
		{
			if((nWndReport2 % ONE_ROW_COUNT) == 0)
			{
				if(pRecord2 != NULL)
					m_wndReport2.AddRecord(pRecord2);

				pRecord2 = new CXTPGridRecord;			
			}

			//m_pAPM->m_RiderMap.insert(EMPTY_RIDER_MAP::value_type(std::make_pair(rider->nRiderCompany, rider->nRNo), rider));

			CMyTextRecord *pRecordItem = new CMyTextRecord("");
			pRecordItem->pAllocRiderInfo = rider;
			pRecord2->AddItem(pRecordItem);

			nWndReport2++;
		}
		else
		{
			if((nWndReport % ONE_ROW_COUNT) == 0)
			{
				if(pRecord != NULL)
					m_wndReport.AddRecord(pRecord);

				pRecord = new CXTPGridRecord;			
			}


			//m_pEPM->m_RiderMap.insert(EMPTY_RIDER_MAP::value_type(std::make_pair(rider->nRiderCompany, rider->nRNo), rider));

			CMyTextRecord *pRecordItem = new CMyTextRecord("");
			pRecordItem->pAllocRiderInfo = rider;
			pRecord->AddItem(pRecordItem);

			nWndReport++;
		}
	}

	if(pRecord)
		m_wndReport.AddRecord(pRecord);

	if(pRecord2)
		m_wndReport2.AddRecord(pRecord2);
 
	m_wndReport.Populate();
	m_wndReport2.Populate();
}

void CEmptyCarDlg1::UpdateLastLocation(ST_RIDER_STRUCT *rider)
{
	EMPTY_ORDER_MAP::iterator it;	
	it = m_OrderMap.find(std::make_pair(rider->nRiderCompany, 
		rider->nRNo));

	//long nRiderCompany = rider->nRiderCompany;
	//long nRNo = rider->nRNo;

	COleDateTime dtCompare(2000, 1, 1, 0, 0, 0);

	long nCount = 0;

	while(it != m_OrderMap.end())
	{
		if((*it).second.nRiderCompany != rider->nRiderCompany ||
			(*it).second.nRNo != rider->nRNo)
			break;

		if(it->second.dtRcp > dtCompare)
		{
			if(LF->IsAllocOrder(it->second.nState, FALSE))
			{
				rider->strLastLocation = it->second.strStart;
				nCount++;
			}
			else
				rider->strLastLocation = it->second.strDest;
		}

		//if(it->second.nState == 11 || it->second.nState == 30 || it->second.nState == 31)
		//{
		//	if(it->second.dtRcp > dtCompare)
		//	{
		//		rider->sLastLocation = it->second.sStart;
		//	}
		//	nCount++;
		//}
		//else if(it->second.nState == 35)
		//{
		//	if(it->second.dtRcp > dtCompare)
		//	{
		//		rider->sLastLocation = it->second.sDest;
		//	}
		//}

		dtCompare = it->second.dtRcp;

		it++;
	}

	if(nCount > 0)
		rider->bEmpty = FALSE;

}

void CEmptyCarDlg1::InitOrderMap()
{
	m_OrderMap.clear();

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nState >= 11 && it->second.nState <= 35)
		{
			ST_EMPTY_ORDER pItem;

			//pItem.nTNo = it->second.nTNo;
			pItem.nState = it->second.nState;
			pItem.nRNo = it->second.nRNo;
			pItem.nRiderCompany = it->second.nRiderCompany;
			//pItem.sOName = it->second.strCName.c_str();
			//pItem.dtState = it->second.dtState;
			pItem.dtRcp = it->second.dtRcp;
			pItem.strStart = it->second.strStart.c_str();
			pItem.strDest = it->second.strDest.c_str();

			m_OrderMap.insert(EMPTY_ORDER_MAP::value_type(std::make_pair(it->second.nRiderCompany, it->second.nRNo), pItem));
		}
	}
}

void CEmptyCarDlg1::InitRider()
{
	EMPTY_RIDER_VECTOR::iterator it;

	for(it = m_RiderVec.begin(); it != m_RiderVec.end(); it++)
	{
		(*it)->strLastLocation = "";
		(*it)->bEmpty = TRUE;
	}

}

void CEmptyCarDlg1::GetRider()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_valid_rider_2");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return;

	long nCompany, nRNo, nCarType;
	CString sRName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_STRUCT *pItem = new ST_RIDER_STRUCT;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("nCarType", nCarType);

		pItem->bEmpty = TRUE;
		pItem->strRName = sRName;
		pItem->nRNo = nRNo;
		pItem->nRiderCompany = nCompany;
		pItem->nCarType = nCarType;
		pItem->strLastLocation = "";

		m_RiderVec.push_back(pItem);
		//m_pEPM->m_RiderMap.insert(EMPTY_RIDER_MAP::value_type(std::make_pair(nCompany, nRNo), pItem));

		pRs.MoveNext();
	}
}

void CEmptyCarDlg1::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
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
		if (IDC_REPORT_LIST == nID || IDC_REPORT_LIST2 == nID)
		{
			CXTPGridControl * pControl;
			if(nID == IDC_REPORT_LIST)
				pControl = &m_wndReport;
			else
				pControl = &m_wndReport2;

			pControl->GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = pControl->HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				if(pCol)
				{
					CMakeHtmlTable htable;

					CMyTextRecord *pItem = (CMyTextRecord*)pRow->GetRecord()->GetItem(pCol);
					if(pItem)
					{
						long nRiderCompany = pItem->pAllocRiderInfo->nRiderCompany;
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

BOOL CEmptyCarDlg1::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CEmptyCarDlg1::OnEnChangeSearchEdit()
{
	m_SearchEdt.GetWindowText(m_sSearch);
	RefreshList(FALSE);	
}
