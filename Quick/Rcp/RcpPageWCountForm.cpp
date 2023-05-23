// RcpPageWCountForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPageWCountForm.h"
#include "WCountPaintManager.h"
#include "RcpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_CHART_REFRESH 1010
#define CLICK_BUTTON 100

BEGIN_MESSAGE_MAP(CXTPChartButtonControl, CXTPChartControl)
	ON_BN_CLICKED(CLICK_BUTTON, OnClick)
END_MESSAGE_MAP()


void CXTPChartButtonControl::OnClick()
{
	m_pMsgWnd->SendMessage(WM_CHART_REFRESH, (WPARAM)0, (LPARAM)0);
}

void CXTPChartButtonControl::MakeButton(CWnd *pMsgWnd) 
{
	m_pMsgWnd = pMsgWnd;

	CRect rc;
	GetClientRect(rc);

	rc.left = 5;
	rc.top = 5;
	rc.right = rc.left + 50;
	rc.bottom = rc.top + 20;

	m_btnClick.Create(NULL,WS_CHILD|WS_VISIBLE, rc, this, CLICK_BUTTON);
	m_btnClick.ShowWindow(TRUE);
	m_btnClick.SetWindowText("갱신");
}

// CRcpPageWCountForm

IMPLEMENT_DYNCREATE(CRcpPageWCountForm, CMyFormView)

CRcpPageWCountForm::CRcpPageWCountForm()
	: CMyFormView(CRcpPageWCountForm::IDD)
{	
	m_nAllCount = 0;
	m_nHourCount = 0;
}

CRcpPageWCountForm::~CRcpPageWCountForm()
{
}

void CRcpPageWCountForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WNO_CHART, m_chtWNo);
	DDX_Control(pDX, IDC_REPORTCTRL, m_lstReport);
}

BEGIN_MESSAGE_MAP(CRcpPageWCountForm, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CRcpPageWCountForm::OnBnClickedRefreshButton)
	ON_MESSAGE(WM_CHART_REFRESH, OnChartRefresh)
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRcpPageWCountForm 진단입니다.

#ifdef _DEBUG
void CRcpPageWCountForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRcpPageWCountForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CRcpPageWCountForm::FillData()
{
	m_mapWCount.clear();

	m_nAllCount = 0;
	m_nHourCount = 0;

	COleDateTime dtRefresh;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_wno_count_log");
	cmd.AddParameter(m_ci.m_nCompanyCode); 
	CMkParameter *parRefresh = cmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), COleDateTime::GetCurrentTime());

	if(!rs.Execute(&cmd))
		return; 

	parRefresh->GetValue(dtRefresh);

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_WCOUNT st;

		rs.GetFieldValue("nCompany", st.nCompany);
		rs.GetFieldValue("nWNo", st.nWNo);
		rs.GetFieldValue("sName", st.strWName);

		if(st.nWNo < 0 || st.nCompany == 0)
		{
			rs.MoveNext(); 
			continue;
		}
	
		st.nPreRank = 0;
		m_mapWCount.insert(MAP_WCOUNT::value_type(make_pair(st.nCompany, st.nWNo), st));

		MAP_WCOUNT::iterator it = m_mapWCount.find(make_pair(st.nCompany, st.nWNo));

		rs.GetFieldValue("nOrderCount", it->second.nOrderCount);
		rs.GetFieldValue("nHourOrderCount", it->second.nOneHourOrderCount);
		rs.GetFieldValue("nCallCount", it->second.nCallCount);
		rs.GetFieldValue("nHourCallCount", it->second.nOneHourCallCount);
		rs.GetFieldValue("nRank", it->second.nRank);

		rs.MoveNext(); 

		m_nAllCount += (it->second.nOrderCount + it->second.nCallCount);
		m_nHourCount += (it->second.nOneHourOrderCount + it->second.nOneHourCallCount);
	}

	GetPreRank(dtRefresh);

	//FillOrderData(); 
	//FillCallData();
}

void CRcpPageWCountForm::GetPreRank(COleDateTime dtRefresh)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_wno_count_log_pre_rank");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(dtRefresh);

	if(!rs.Execute(&cmd))
		return;

	long nCompany, nWNo, nRank;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nWNo", nWNo);
		rs.GetFieldValue("nRank", nRank);

		MAP_WCOUNT::iterator it = m_mapWCount.find(make_pair(nCompany, nWNo));

		if(it != m_mapWCount.end())
			it->second.nPreRank = nRank;

		rs.MoveNext();
	}
}


void CRcpPageWCountForm::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate();

	m_lstReport.AddColumn(new CXTPGridColumn(0, "", LVCFMT_LEFT, 100));
	CWCountPaintManager *pManager = new CWCountPaintManager();
	m_lstReport.SetPaintManager(pManager);
	pManager->SetGridColor(RGB(0, 0, 255));
	m_lstReport.ShowHeader(FALSE);
	m_lstReport.GetPaintManager()->m_strNoItems = "";
	m_lstReport.SelectionEnable(FALSE);
	m_lstReport.Populate();
	m_lstReport.SetParent(&m_chtWNo);

	//LU()->SetRcpWCountForm(this);
	//m_chtWNo.MakeButton(this);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	SetResize(IDC_WNO_CHART, sizingRightBottom);

	m_chtWNo.GetContent()->GetAppearance()->LoadPalette("CHART_PALETTE_VIBRANTPASTEL");
	m_chtWNo.GetContent()->OnChartChanged();

	SetTimer(100, 1000, NULL);
	/*
	FillData();
	RefreshChart();
	*/
}

bool sort_my_call_and_count(ST_WCOUNT st1, ST_WCOUNT st2)
{
	return st1.nRank < st2.nRank;
}

#define ORDER_COUNT 0
#define CALL_COUNT 1
#define ORDER_HOUR_COUNT 2
#define CALL_HOUR_COUNT 3
 
CString CRcpPageWCountForm::GetGraphLabel(long nType)
{
	if(nType == ORDER_COUNT)
		return "접수(개별~완료)";
	else if(nType == CALL_COUNT)
		return "전화건수";
	else if(nType == ORDER_HOUR_COUNT)
		return "오더(한시간이내)";
	else if(nType == CALL_HOUR_COUNT)
		return "전화(한시간이내)";

	return "";
}

long CRcpPageWCountForm::GetGraphItem(ST_WCOUNT *st, long nType)
{
	if(nType == ORDER_COUNT)
		return st->nOrderCount;
	else if(nType == CALL_COUNT)
		return st->nCallCount;
	else if(nType == ORDER_HOUR_COUNT)
		return st->nOneHourOrderCount;
	else if(nType == CALL_HOUR_COUNT)
		return st->nOneHourCallCount;

	return 0;
}


void CRcpPageWCountForm::AddGraphData(vector <ST_WCOUNT> *vec, long nType, long nGroup){
	CXTPChartContent* pContent = m_chtWNo.GetContent();
	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	CXTPChartStackedBarSeriesStyle *pStyle = new CXTPChartStackedBarSeriesStyle();
	pSeries->SetStyle(pStyle);
	pStyle->SetStackGroup(nGroup);

	pSeries->SetName(GetGraphLabel(nType));

	for(long nItem=0; nItem<vec->size(); nItem++)
	{
		if(nItem > 9)
			break; 

		ST_WCOUNT &st = vec->at(nItem);

		CXTPChartSeriesPoint *pt = pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(st.nWNo == 0 ? st.strWName + "(" + m_ci.GetBranchName(st.nCompany) + ")" : st.strWName, GetGraphItem(&st, nType)));
		//pt->SetColor(RGB(255, 0, 0));
 	} 
 
	pSeries->GetStyle()->GetLabel()->SetVisible(TRUE);
  
	if(!LF->POWER_CHECK(1895, "접수자통계")) 
		pSeries->GetStyle()->GetLabel()->SetFormat("{V}%%");
}

void CRcpPageWCountForm::ChangeDatePer()
{
	for(MAP_WCOUNT::iterator it = m_mapWCount.begin(); it != m_mapWCount.end(); it++)
	{
		ST_WCOUNT *st = &it->second; 

		st->nOrderCount = m_nAllCount == 0 ? 0 : (float)st->nOrderCount / (float)m_nAllCount * 100;
		st->nCallCount = m_nAllCount == 0 ? 0 : (float)st->nCallCount / (float)m_nAllCount * 100;
		st->nOneHourOrderCount =m_nHourCount == 0 ? 0 : (float)st->nOneHourOrderCount / (float)m_nHourCount * 100;
		st->nOneHourCallCount = m_nHourCount == 0 ? 0 : (float)st->nOneHourCallCount / (float)m_nHourCount * 100;
	}
}

void CRcpPageWCountForm::RefreshChart() 
{
	CXTPChartContent* pContent = m_chtWNo.GetContent();

	long nCount = pContent->GetSeries()->GetCount(); 
	pContent->GetSeries()->RemoveAll(); 

  
	pContent->GetLegend()->SetVisible(TRUE);   


	if(!LF->POWER_CHECK(1895, "접수자통계"))
		ChangeDatePer();

	vector <ST_WCOUNT> vec;

	for(MAP_WCOUNT::iterator it = m_mapWCount.begin(); it != m_mapWCount.end(); it++)
	{
		ST_WCOUNT &st = it->second;

		if(st.nCompany != m_ui.nCompany || st.nWNo != m_ui.nWNo)
			vec.push_back(it->second);
	}

	std::sort(vec.begin(), vec.end(), sort_my_call_and_count);

	MAP_WCOUNT::iterator itFind = m_mapWCount.find(make_pair(m_ui.nCompany, m_ui.nWNo));

	if(itFind != m_mapWCount.end())
		vec.insert(vec.begin(), itFind->second);

	AddGraphData(&vec, ORDER_COUNT, 0);
	AddGraphData(&vec, CALL_COUNT, 0);
	AddGraphData(&vec, ORDER_HOUR_COUNT, 1);
	AddGraphData(&vec, CALL_HOUR_COUNT, 1);

	RefreshRankList(); 

	pContent->GetLegend()->SetVisible(TRUE); 
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendFarOutside);
	pContent->GetLegend()->SetVerticalAlignment(xtpChartLegendFar);


	CXTPChartSeries *pSeries = pContent->GetSeries()->GetAt(0);  

 
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->SetAllowZoom(FALSE);


	pDiagram->GetAxisX()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetVisible(FALSE); 
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("상담원"));

	if(vec.size() < 4)  
	{  
		//pDiagram->GetAxisX()->GetRange()->SetMaxValue((long)vec.size());
		pDiagram->GetAxisX()->GetRange()->SetMaxValue(6);
		pDiagram->GetAxisX()->GetRange()->SetMinValue(-1); 
		pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);
	}
 
	pDiagram->GetAxisY()->SetVisible(FALSE); //
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE); 
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("건수"));
 
	m_lstReport.SetGridColor(RGB(255, 255, 255)); 
} 
 
void CRcpPageWCountForm::OnBnClickedRefreshButton()
{
	FillData();
	RefreshChart();
}

LONG CRcpPageWCountForm::OnChartRefresh(WPARAM wParam, LPARAM lParam)
{
	FillData();
	RefreshChart();

	return 0;
}
void CRcpPageWCountForm::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	static long nSecond = 301; //최초갱신

	if(nIDEvent == 100)
	{
		if(((CRcpView*)GetOwner())->m_wndTabControl.GetCurSel() == 3)
		{ 
			if(nSecond > 300) // 300임 
			{
				FillData();
				RefreshChart();
				nSecond = 0;
			}
 
			nSecond++;
		}

		SetTimer(100, 1000, NULL);
	}
	

	CMyFormView::OnTimer(nIDEvent);
}

void CRcpPageWCountForm::RefreshRankList()
{
	m_lstReport.GetRecords()->RemoveAll();
	m_lstReport.Populate();

	vector <ST_WCOUNT> vec;

	for(MAP_WCOUNT::iterator it = m_mapWCount.begin(); it != m_mapWCount.end(); it++)
	{
		ST_WCOUNT &st = it->second;
		vec.push_back(it->second);
	}

	std::sort(vec.begin(), vec.end(), sort_my_call_and_count);

	CXTPGridRecord *pRecord = NULL;

	for(long nItem=0; nItem<vec.size(); nItem++)
	{ 
		if(nItem > 9) 
			break;  

		ST_WCOUNT st = vec.at(nItem); 
		pRecord = m_lstReport.AddRecord(new CXTPGridRecord());
  
		CWcountRecordItem *pItem = (CWcountRecordItem*)pRecord->AddItem(new CWcountRecordItem(st.strWName));
		pItem->m_st = st;
   
	}   

	m_lstReport.Populate();
}


void CRcpPageWCountForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{		
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);
 
		rcList.left = rcForm.right - 144;
		rcList.right = rcForm.right - 15;  
		rcList.top = rcForm.top + 11;
		rcList.bottom = rcForm.bottom - 130;
	//	rcList.bottom = rcForm.bottom - 5;
		m_lstReport.MoveWindow(rcList);

	//	RefreshList(); 
	}
}  
 
