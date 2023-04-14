// ReportForm26.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm26.h"
#include "Graph.h"
#include "RcpView.h"

// CReportForm26

IMPLEMENT_DYNCREATE(CReportForm26, CMyFormView)

CReportForm26::CReportForm26()
	: CMyFormView(CReportForm26::IDD)
{
	m_bGraphComplete = FALSE;
}

CReportForm26::~CReportForm26()
{


	if(m_Graph)
	{
		//delete m_Graph; //조성일
	}
}

void CReportForm26::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LEFT_LIST, m_lstLeft);
	DDX_Control(pDX, IDC_RIGHT_LIST, m_lstRight);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stcDraw);

	DDX_Control(pDX, IDC_DTP_FROM, m_dtFromCtl);
	DDX_Control(pDX, IDC_DTP_TO, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_DTP_FROM, m_dtFromCtl);
	DDX_Control(pDX, IDC_DTP_TO, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CReportForm26, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm26::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CReportForm26::OnBnClickedSearchBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm26::OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LEFT_LIST, OnReportItemDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_RIGHT_LIST, OnReportItemRightDblClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CReportForm26::OnViewExcel()
{
	if(!POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	::AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 328, m_lstRight.GetItemCount());  
	CMyExcel::ToExcel(&m_lstRight);
}

void CReportForm26::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstRight.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

// CReportForm26 진단입니다.

#ifdef _DEBUG
void CReportForm26::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm26::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm26 메시지 처리기입니다.

void CReportForm26::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstLeft.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_wno_sales_team");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	long nCompany, nWNo;
	CString strWName, strTemp;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("sWName", strWName);

		strTemp.Format("%d / %s", nWNo, strWName);

		m_lstLeft.InsertItem(i, strTemp);
		m_lstLeft.SetItemLong(i, nCompany);
		m_lstLeft.SetItemLong2(i, nWNo);

		pRs.MoveNext();
	}

	m_lstLeft.Populate();
}

void CReportForm26::OnBnClickedRefreshBtn()
{
	UpdateData(TRUE);

	m_bGraphComplete = FALSE;

	CXTPGridRecord *pRecord = m_lstLeft.GetFirstSelectedRecord();
	if(pRecord == NULL) return;
  
	m_lstRight.DeleteAllItems();

	m_Graph = new CGraph(BAR_GRAPH_3D);

	CString strFmt;
	strFmt.Format("%s [%s ~ %s]", m_lstLeft.GetItemText(pRecord, 0), m_dtFrom.Format("%m-%d"),
					m_dtTo.Format("%m-%d"));

	m_Graph->SetGraphTitle(strFmt);
	//m_Graph->SetGraphAlignment(HORIZONTAL_ALIGN);
	m_Graph->Set3DDepthRatio(0);
	m_Graph->SetXAxisLabel("고객명");
	m_Graph->SetYAxisLabel("수입(만원)");
	m_Graph->SetGridLines(TRUE);


	long nWCompany = m_lstLeft.GetItemLong(pRecord);
	long nWNo = m_lstLeft.GetItemLong2(pRecord);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_for_sales_team");
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);
	pCmd.AddParameter(nWCompany);
	pCmd.AddParameter(nWNo);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	long nTNo, nCompany, nOCNo, nCarType, nPayType, nCharge, nState;
	COleDateTime dt1;
	CString sOName, sSName, sDName, sEtc, sPreOName;

	long nPreCNo = ZERO, nMaxIncome = ZERO;
	long nCountM = ZERO, nChargeM = ZERO;
	long nCountS = ZERO, nChargeS = ZERO;

	long nItem = ZERO;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("nOCNo", nOCNo);
		pRs.GetFieldValue("sOName", sOName);
		pRs.GetFieldValue("sSName", sSName);
		pRs.GetFieldValue("sDName", sDName);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nChargeSum", nCharge);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nState", nState);

		if(nPreCNo != nOCNo && i != ZERO)
		{
			m_lstRight.InsertItem(nItem, "");
			m_lstRight.SetItemText(nItem, 5, "횟수 : " + CString(itoa(nCountM, buffer, 10)));
			m_lstRight.SetItemText(nItem, 6, "금액 : " + GetMyNumberFormat(nChargeM));
			m_lstRight.SetItemLong(nItem, nCompany);
			m_lstRight.SetItemLong2(nItem, ONE);
			nItem++;
			m_lstRight.InsertItem(nItem, "");
			m_lstRight.SetItemLong2(nItem, ZERO);
			nItem++;

			CGraphSeries* pSeries = new CGraphSeries();
			pSeries->SetLabel(sPreOName);
			pSeries->SetData(0, (int)(nCountM));
			pSeries->SetData(1, (int)(nChargeM / 10000));
			m_Graph->AddSeries(pSeries);

			nMaxIncome = max(nMaxIncome, nChargeM);

			nCountM = ZERO; nChargeM = ZERO;
		}

		m_lstRight.InsertItem(nItem, itoa(nTNo, buffer, 10));
		m_lstRight.SetItemText(nItem, 1, m_ci.GetBranchName(nCompany));
		m_lstRight.SetItemText(nItem, 2, dt1.Format("%m-%d %H:%M"));
		m_lstRight.SetItemText(nItem, 3, sOName);
		m_lstRight.SetItemText(nItem, 4, ::GetCarTypeFromLong(nCarType));
		m_lstRight.SetItemText(nItem, 5, ::GetPayTypeFromLong(nPayType));
		m_lstRight.SetItemText(nItem, 6, ::GetMyNumberFormat(nCharge));
		m_lstRight.SetItemText(nItem, 7, sSName);
		m_lstRight.SetItemText(nItem, 8, sDName);
		m_lstRight.SetItemText(nItem, 9, sEtc);
		m_lstRight.SetItemLong(nItem, nCompany);
		m_lstRight.SetItemLong2(nItem, ZERO);
		m_lstRight.SetItemData(nItem, nState);

		nCountM++; nChargeM += nCharge;
		nCountS++; nChargeS += nCharge;

		nItem++;

		sPreOName = sOName;
		nPreCNo = nOCNo;

		pRs.MoveNext();
	}

	if(pRs.GetRecordCount() > ZERO)
	{ 
		m_lstRight.InsertItem(nItem, "");
		m_lstRight.SetItemText(nItem, 5, "횟수 : " + CString(itoa(nCountM, buffer, 10)));
		m_lstRight.SetItemText(nItem, 6, "금액 : " + ::GetMyNumberFormat(nChargeM));
		m_lstRight.SetItemLong(nItem, ZERO);
		m_lstRight.SetItemLong2(nItem++, ONE);

		CGraphSeries* pSeries = new CGraphSeries();
		pSeries->SetLabel(sPreOName);
		pSeries->SetData(0, (int)(nCountM));
		pSeries->SetData(1, (int)(nChargeM / 10000));
		m_Graph->AddSeries(pSeries);

		m_lstRight.InsertItem(nItem, "");
		m_lstRight.SetItemLong2(nItem++, ZERO); 
		m_lstRight.InsertItem(nItem, "");
		m_lstRight.SetItemLong2(nItem++, ZERO);

		m_lstRight.InsertItem(nItem, "");
		m_lstRight.SetItemText(nItem, 5, "최종 : " + CString(itoa(nCountS, buffer, 10)));
		m_lstRight.SetItemText(nItem, 6, ::GetMyNumberFormat(nChargeS));
		m_lstRight.SetItemLong2(nItem++, ZERO);
		m_lstRight.InsertItem(nItem, "");
		m_lstRight.SetItemLong2(nItem, ZERO);


		m_Graph->SetColor(0, RGB(255, 0, 0));
		m_Graph->SetLegend(0, "건수");
		m_Graph->SetColor(1, RGB(0, 0, 255));
		m_Graph->SetLegend(1, "금액");


		int nMaxLimit = (int)(nMaxIncome / 10000 * 1.1);
		nMaxLimit = max(nMaxLimit, 10);
		m_Graph->SetTickLimits(0, nMaxLimit, nMaxLimit / 10);

		m_bGraphComplete = TRUE;
		Invalidate();
	}

	m_lstRight.Populate();
	
	/*
	CRect rc; m_stcDraw.GetWindowRect(rc);
	ScreenToClient(rc);
	InvalidateRect(rc, FALSE);
	*/
}

void CReportForm26::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuMonth();

	m_lstLeft.InsertColumn(0, "영업팀", LVCFMT_LEFT, 120);
	m_lstLeft.Populate();

	m_lstRight.InsertColumn(0, "오더No", LVCFMT_LEFT, 90);
	m_lstRight.InsertColumn(1, "발주사", LVCFMT_LEFT, 100);
	m_lstRight.InsertColumn(2, "접수일시", LVCFMT_LEFT, 100);
	m_lstRight.InsertColumn(3, "의뢰지", LVCFMT_LEFT, 100);
	m_lstRight.InsertColumn(4, "차량", LVCFMT_LEFT, 50);
	m_lstRight.InsertColumn(5, "지불", LVCFMT_LEFT, 70);
	m_lstRight.InsertColumn(6, "금액", LVCFMT_LEFT, 80);
	m_lstRight.InsertColumn(7, "출발지", LVCFMT_LEFT, 90);
	m_lstRight.InsertColumn(8, "도착지", LVCFMT_LEFT, 90);
	m_lstRight.InsertColumn(9, "적요", LVCFMT_LEFT, 300);

	m_lstRight.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstRight.Populate();

	SetResize(IDC_LEFT_LIST, sizingBottom);
	SetResize(IDC_RIGHT_LIST, sizingRight);
	SetResize(IDC_DRAW_STATIC, sizingRightBottom);
}

void CReportForm26::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CReportForm26::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstLeft.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strText = m_lstLeft.GetItemText(pRecord, 0);

		if(strText.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstLeft.Populate();
}


void CReportForm26::OnReportItemRightDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pReport = m_lstRight.GetFirstSelectedRecord();

	if(pReport == NULL) return;

	CString sOName = m_lstRight.GetItemText(pReport, 3);
	long nState = m_lstRight.GetItemData(pReport);
	long nCompany = m_lstRight.GetItemLong(pReport);
	long nTNo = atoi(m_lstRight.GetItemText(pReport, 0));

	if(nTNo <= ZERO)
		return;

	CBranchInfo *pBranch = GetBranchInfo(nCompany);

	LU->GetRcpView()->CreateRcpDlg(pBranch, 
		sOName,
		nTNo, 
		nState, "", FALSE, MINUS_ONE, ZERO, ZERO, FALSE, "");
}

void CReportForm26::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnBnClickedRefreshBtn();
}

void CReportForm26::OnPaint()
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
