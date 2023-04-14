// ReportForm23.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm23.h"
#include "Graph.h"
#include "AddGroupDlg.h"

// CReportForm23

IMPLEMENT_DYNCREATE(CReportForm23, CMyFormView)

CReportForm23::CReportForm23()
	: CMyFormView(CReportForm23::IDD)
{
	m_bGraphComplete = FALSE;
}

CReportForm23::~CReportForm23()
{
}

void CReportForm23::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_Report);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stcDraw);
}

BEGIN_MESSAGE_MAP(CReportForm23, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDbClick)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_REPORT_LIST, OnReportItemSelChanged)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CReportForm23 진단입니다.

#ifdef _DEBUG
void CReportForm23::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm23::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm23 메시지 처리기입니다.

void CReportForm23::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_LIST, sizingRight);
	SetResize(IDC_DRAW_STATIC, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	InitColumn();
}


void CReportForm23::InitColumn()
{
	int nColumnCount = m_Report.GetColumns()->GetCount();

	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumns *pColums = m_Report.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}

	UpdateData(TRUE);

	COleDateTime dtFrom = m_dtFrom;

	m_Report.InsertColumn(0, "그룹명", LVCFMT_LEFT, 120);
	m_Report.InsertColumn(1, "이용", LVCFMT_LEFT, 40);
	m_Report.InsertColumn(2, "취소", LVCFMT_LEFT, 40);
	m_Report.InsertColumn(3, "한도", LVCFMT_LEFT, 90);
	m_Report.InsertColumn(4, "초기화", LVCFMT_LEFT, 50);

	long nItem = 5;

	while(1)
	{
		if(m_dtTo < dtFrom)
			break;

		CString sDate = dtFrom.Format("%m/%d");
		
        m_Report.InsertColumn(nItem++, sDate, LVCFMT_LEFT, 40);

		COleDateTimeSpan span(1, 0, 0, 0);
		dtFrom = dtFrom + span;
	}

	m_Report.Populate();
}

void CReportForm23::RefreshList()
{
	CMyFormView::RefreshList();

	m_Report.DeleteAllItems();
	InitColumn();

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_use_count");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	long nMainGNo, nUseCount, nCancelCount;
	CString sDate;
	long nSumUseCount = 0, nSumCancelCount = 0;


	long nPreGNo = 0;
	long nItem = -1;

	if(pRs.GetRecordCount() == 0)
		return;
    
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{ 
		pRs.GetFieldValue("nMainGNo", nMainGNo);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nCancelCount", nCancelCount);
		pRs.GetFieldValue("sDate", sDate);

		if(nMainGNo != nPreGNo)
		{
			nItem++;

			if(nItem > 0)

			{
				m_Report.SetItemText(nItem -1, 1, ::GetMyNumberFormat(nSumUseCount));
				m_Report.SetItemText(nItem -1, 2, ::GetMyNumberFormat(nSumCancelCount));

				if(m_cg.GetGroupData(nMainGNo)->nAbleUseCharge > 0)
				{
					CString strTemp; 
					char buffer[10];
					strTemp.Format("%s / %d만원", ::GetMyNumberFormat(m_cg.GetGroupData(nMainGNo)->nUseCharge), m_cg.GetGroupData(nMainGNo)->nAbleUseCharge);
					m_Report.SetItemText(nItem -1, 3, strTemp);
					m_Report.SetItemText(nItem -1, 4, CString(itoa(m_cg.GetGroupData(nMainGNo)->nInitDay, buffer, 10)) + "일");

				}
				else
				{
					m_Report.SetItemText(nItem -1, 3, "");
					m_Report.SetItemText(nItem -1, 4, "");
				}


				nSumUseCount = 0;
				nSumCancelCount = 0;
			}

			nPreGNo = nMainGNo;
			m_Report.InsertItem(nItem, m_cg.GetGroupData(nMainGNo)->strGroupName);	
			m_Report.SetItemLong(nItem, nMainGNo);
		}

		m_Report.SetItemText(nItem, GetColumnLocation(sDate), ::GetMyNumberFormat(nUseCount) + "/" + ::GetMyNumberFormat(nCancelCount));

		nSumUseCount += nUseCount;
		nSumCancelCount += nCancelCount;

		pRs.MoveNext();
	}

	m_Report.SetItemText(nItem , 1, ::GetMyNumberFormat(nSumUseCount));
	m_Report.SetItemText(nItem , 2, ::GetMyNumberFormat(nSumCancelCount));

	m_Report.Populate();
}

long CReportForm23::GetColumnLocation(CString sDate)
{
	long nCount = m_Report.GetColumns()->GetCount();
	CString sCompaneDate = sDate.Mid(4,2) + "/" + sDate.Right(2);

	for(int i=3; i<nCount; i++)
	{
		CXTPGridColumn *pColumn = m_Report.GetColumns()->GetAt(i);

		CString sItem = pColumn->GetCaption();

		if(sCompaneDate == sItem)
		{
			return i;
		}
	}
	
	return -1;
}

void CReportForm23::OnBnClickedRefreshBtn()
{
	RefreshList();
	OnEnChangeSearchEdit();
}

void CReportForm23::OnEnChangeSearchEdit()
{
	CString sData; m_edtSearch.GetWindowText(sData);

	CXTPGridRecords *pRecords = m_Report.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString sItem = pRecord->GetItem(0)->GetCaption(NULL);

		if(sItem.Find(sData) != -1)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_Report.Populate();
}

void CReportForm23::OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SetTimer(100, 100, NULL);
	/*
	CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	MakeData(m_Report.GetItemLong(pRow->GetRecord()));
	*/
}

void CReportForm23::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CAddGroupDlg dlg;
	dlg.m_nGNo = m_Report.GetItemLong(pRow->GetRecord());
	dlg.m_bAdd = FALSE;

	if(dlg.DoModal())
	{
		RefreshList();
		OnEnChangeSearchEdit();
	}
}

void CReportForm23::MakeData(long nGNo)
{

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_use_detail");
	pCmd.AddParameter(nGNo);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	long nGroupNo, nUseCount, nCancelCount;
	CString sDate;
	
	DRAW_MAP pMap;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nGNo", nGroupNo);
		pRs.GetFieldValue("sDate", sDate);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nCancelCount", nCancelCount);

		DRAW_MAP::iterator it = pMap.find(nGroupNo);

        if(it == pMap.end())
		{
			ARRAY_STRUCT st;

			for(int j=0; j<MAX_DAY; j++)
				st.nDay[j] = 0;
			
			pMap.insert(DRAW_MAP::value_type(nGroupNo, st));
			it = pMap.find(nGroupNo);
		}

        COleDateTime dtDate; 
		dtDate.SetDate(atoi(sDate.Left(4)), atoi(sDate.Mid(4, 2)), atoi(sDate.Right(2)));

		COleDateTimeSpan span = dtDate - m_dtFrom;
		it->second.nDay[span.GetDays()] = nUseCount;

		pRs.MoveNext();
	}

	if(pRs.GetRecordCount() != 0)
		DrawGraph(&pMap, nGNo);
}

void CReportForm23::DrawGraph(DRAW_MAP *pMap, long nGNo)
{
	long nMax = 0;
	m_bGraphComplete = FALSE;  

	//LINE_GRAPH 

	m_Graph = new CGraph(LINE_GRAPH_3D);  

	CString strFmt;
	strFmt.Format("[%s] 그룹정산(%s ~ %s)", m_cg.GetGroupData(nGNo)->strGroupName, m_dtFrom.Format("%Y-%m-%d"),
		m_dtTo.Format("%Y-%m-%d"));

	m_Graph->SetGraphTitle(strFmt);
	m_Graph->SetGraphAlignment(HORIZONTAL_ALIGN);
	m_Graph->Set3DDepthRatio(0);
	m_Graph->SetXAxisLabel("건수");
	m_Graph->SetYAxisLabel("그룹");
	m_Graph->SetGridLines(TRUE);

	COleDateTimeSpan span = m_dtTo - m_dtFrom;

	long nSpanDay  = span.GetDays() + 1;

	for(int i=0; i<nSpanDay; i++)
	{
		COleDateTime dtDate = m_dtFrom + COleDateTimeSpan(i, 0, 0, 0);
		CGraphSeries* pSeries = new CGraphSeries();
		pSeries->SetLabel(dtDate.Format("%m/%d"));

		DRAW_MAP::iterator it;
		long nItem = 0;

		for(it = pMap->begin(); it != pMap->end(); it ++)
		{
			pSeries->SetData(nItem++, it->second.nDay[i]);
			nMax = it->second.nDay[i] > nMax ? it->second.nDay[i] : nMax;
		}

		m_Graph->AddSeries(pSeries);
	}

	/*
	CGraphSeries* pSeries = new CGraphSeries();
	pSeries->SetLabel("1일");

	pSeries->SetData(0, 1);
	pSeries->SetData(1, 3);
	m_Graph->AddSeries(pSeries);

	CGraphSeries* pSeries1 = new CGraphSeries();
	pSeries1->SetLabel("2일"); //날짜

	pSeries1->SetData(0, 5);
	pSeries1->SetData(1, 8);
	m_Graph->AddSeries(pSeries1);

	CGraphSeries* pSeries2 = new CGraphSeries();
	pSeries2->SetLabel("3일");

	pSeries2->SetData(0, 3);
	pSeries2->SetData(1, 2);
	m_Graph->AddSeries(pSeries2);
	*/

	UINT color[] = {RED, GREEN, BLUE, YELLOW, ORANGE, HOT_PINK, PURPLE, CYAN, BLACK,LAVENDER, 
		PEACH, SKY_BLUE, FOREST_GREEN, BROWN, TURQUOISE, ROYAL_BLUE, GREY, DARK_GREY, TAN};

	DRAW_MAP::iterator it;
	long nItem = 0;

	for(it = pMap->begin(); it != pMap->end(); it ++)
	{
		m_Graph->SetColor(nItem, color[nItem % 18]);
		m_Graph->SetLegend(nItem++, m_cg.GetGroupData(it->first)->strGroupName + "/" + m_cg.GetGroupData(it->first)->strDept);
	}

	m_Graph->SetTickLimits(0, max(nMax, 1), max(nMax/ 15, 1));
	m_Graph->SetGraphAlignment(0);
	m_Graph->SetXAxisAlignment(0);

	m_bGraphComplete = TRUE;

	Invalidate(TRUE);

}

void CReportForm23::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 

	if(m_bGraphComplete == TRUE)
	{
		CDC *pDC = m_stcDraw.GetDC();
		m_Graph->DrawGraph(pDC);
		ReleaseDC(pDC);

	}
}

void CReportForm23::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	if(nIDEvent == 100)
	{
		CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

		if(pRow == NULL)
			return;

		MakeData(m_Report.GetItemLong(pRow->GetRecord()));
	}

	CMyFormView::OnTimer(nIDEvent);
}
