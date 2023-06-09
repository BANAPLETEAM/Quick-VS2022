// ReportForm11.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm11.h"
#include "Graph.h"
#include "MyReportPaintManager.h"

CReportFormRecord11::CReportFormRecord11()
{
    AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText("")); 
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
}

CReportFormRecord11::CReportFormRecord11(COleDateTime dt, long nTotal, long nComplete, long nCancel, LONGLONG nCash,
											LONGLONG nCredit, long nTotalDeposit, long nGive, long nTake, long nMileageCharge, long nChargeCompany, long nMileage, BOOL bTotal)
{
	if(bTotal)
		AddItem(new CXTPGridRecordItemText("합 계 : "));
	else
		AddItem(new CXTPGridRecordItemMyDate(dt));

	AddItem(new CXTPGridRecordItemFormatNumber(nTotal));
	AddItem(new CXTPGridRecordItemFormatNumber(nTotal + nTake));
	AddItem(new CXTPGridRecordItemFormatNumber(nComplete));
	AddItem(new CXTPGridRecordItemFormatNumber(nCancel));

	CString strCash, strCredit, strSum;
	strCash.Format("%0.f",(double)nCash);
	strCredit.Format("%0.f",(double)nCredit);
	strSum.Format("%0.f",(double)(nCash + nCredit));
	
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(strCash)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nCredit)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(strSum)));

	/*
	AddItem(new CXTPGridRecordItemFormatNumber(nCash));
	AddItem(new CXTPGridRecordItemFormatNumber(nCredit));
	AddItem(new CXTPGridRecordItemFormatNumber(nCash + nCredit));
	*/

	if(m_ci.IsThisCompany("퀵오케이"))
		AddItem(new CXTPGridRecordItemFormatNumber((nCash + nCredit) * 0.23));
	else
		AddItem(new CXTPGridRecordItemFormatNumber(nTotalDeposit));

	AddItem(new CXTPGridRecordItemFormatNumber(nGive));
	AddItem(new CXTPGridRecordItemFormatNumber(nTake));
	AddItem(new CXTPGridRecordItemFormatNumber(nGive - nTake));

	long nShareRate;

	if(nTotal > 0) 
		nShareRate = nGive * 100 / nTotal;
	else
		nShareRate = 0;
	
	AddItem(new CXTPGridRecordItemPercentNumber(nShareRate));
	AddItem(new CXTPGridRecordItemFormatNumber(nMileageCharge));
	AddItem(new CXTPGridRecordItemFormatNumber(nChargeCompany));
	AddItem(new CXTPGridRecordItemFormatNumber(nMileage));
}

IMPLEMENT_DYNCREATE(CReportForm11, CMyFormView)

CReportForm11::CReportForm11()
	: CMyFormView(CReportForm11::IDD)
{
	m_Graph = NULL;
	m_bGraphComplete = FALSE;
}

CReportForm11::~CReportForm11()
{
}

void CReportForm11::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_BUTTON_RIDER_FETCH, m_RefreshBtn);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_To);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
	DDX_Control(pDX, IDC_GRAPH, m_GraphStc);
	DDX_Control(pDX, IDC_INTEGRATE_INQUERY_CHECK, m_chkIntegrteInquery);
	DDX_Control(pDX, IDC_HORIZONTAL_CHK, m_HorizontalChk);
	DDX_Control(pDX, IDC_PERIOD_STATIC, m_PeriodStatic);

}

BEGIN_MESSAGE_MAP(CReportForm11, CMyFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_RIDER_FETCH, OnBnClickedButtonRiderFetch)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_HORIZONTAL_CHK, OnBnClickedHorizontalChk)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_CTRL, OnReportItemRClick)
	ON_BN_CLICKED(IDC_INTEGRATE_INQUERY_CHECK, &CReportForm11::OnBnClickedIntegrateInqueryCheck)
END_MESSAGE_MAP()


// CReportForm11 진단입니다.

#ifdef _DEBUG
void CReportForm11::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm11::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm11 메시지 처리기입니다.

void CReportForm11::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_dtFrom, &m_dtTo);
	m_DateBtn.OnMenuMonth();

	//if( m_chkIntegrteInquery.GetCheck() )
	SetHeader(m_chkIntegrteInquery.GetCheck() );
	
}

void CReportForm11::SetHeader(BOOL bIntegated)
{
	int nCol = 0; 

	m_wndReport.GetColumns()->Clear();
	//for(int i =0;  i < m_wndReport.GetRecords()->GetCount();i++)
		//m_wndReport.GetRecords()->GetAt(i)->RemoveAll();

	m_wndReport.GetRecords()->RemoveAll();

	if(bIntegated == 0)
	{
		CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("일자"), 100));
		CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("접수건수"), 60));
		CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("총건수(접수+받음)"), 110));
		CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("완료건수"), 60));
		CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("취소건수"), 60));
		CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("현금"), 75));
		CXTPGridColumn* pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, _T("신용"), 75));
		CXTPGridColumn* pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, _T("총금액(현금+신용)"), 110)); 
		CXTPGridColumn* pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, _T("총입금액"), 90));
		CXTPGridColumn* pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, _T("넘긴건수"), 60));
		CXTPGridColumn* pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, _T("받은건수"), 60));
		CXTPGridColumn* pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, _T("넘긴-받음건수"), 90));
		CXTPGridColumn* pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(12, _T("공유율"), 60));
		CXTPGridColumn* pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(13, _T("마일후불(사용)"), 60));
		CXTPGridColumn* pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, _T("업체반환금"), 60));
		CXTPGridColumn* pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(15, _T("마일리지(적립)"), 60));

		pCol0->SetAlignment(DT_RIGHT);
		pCol1->SetAlignment(DT_RIGHT);
		pCol2->SetAlignment(DT_RIGHT);
		pCol3->SetAlignment(DT_RIGHT);
		pCol4->SetAlignment(DT_RIGHT);
		pCol5->SetAlignment(DT_RIGHT);
		pCol6->SetAlignment(DT_RIGHT);
		pCol7->SetAlignment(DT_RIGHT);
		pCol8->SetAlignment(DT_RIGHT);
		pCol9->SetAlignment(DT_RIGHT);
		pCol10->SetAlignment(DT_RIGHT);
		pCol11->SetAlignment(DT_RIGHT);
		pCol12->SetAlignment(DT_RIGHT);
		pCol13->SetAlignment(DT_RIGHT);
		pCol14->SetAlignment(DT_RIGHT);
		pCol15->SetAlignment(DT_RIGHT);

		m_wndReport.SetPaintManager(new CMyReportPaintManager());
		m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
		m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
		m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
		m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
		m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
		m_wndReport.SetGridColor(RGB(212, 208, 200));

		m_wndReport.GetPaintManager()->m_strNoItems = "";
		m_wndReport.AllowEdit(FALSE);
		m_wndReport.FocusSubItems(TRUE);
		m_wndReport.Populate();
		m_wndReport.RedrawControl();

		SetResize(IDC_REPORT_CTRL, sizingRight);
		SetResize(IDC_GRAPH, sizingRightBottom);	

		CWnd *pWnd = (CWnd*)GetDlgItem(IDC_REPORT_CTRL);
		pWnd->GetWindowRect(m_RcList);
		ScreenToClient(m_RcList);

		CWnd *pWnd1 = (CWnd*)GetDlgItem(IDC_GRAPH);
		pWnd1->GetWindowRect(m_RcStc);
		ScreenToClient(m_RcStc);

		m_GraphStc.ShowWindow(SW_SHOW);
	}
	else
	{
		CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("일자"), 90));
		CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("접수"), 47));
		CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("현금"), 70));
		CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("신용"), 70));
		CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("송금"), 60));
		CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("마일"), 50));
		CXTPGridColumn* pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, _T("카드"), 70));
		CXTPGridColumn* pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, _T("합계"), 85)); 
		CXTPGridColumn* pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, _T("입금액"), 68));
		CXTPGridColumn* pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, _T("기사요금"), 90));
		CXTPGridColumn* pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, _T("기사입금액"), 68));
		CXTPGridColumn* pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, _T("예외입금액"), 60));
		CXTPGridColumn* pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(12, _T("자처리"), 47));
		CXTPGridColumn* pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(13, _T("타처리"), 47));
		CXTPGridColumn* pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, _T("트럭공유"), 45));
		CXTPGridColumn* pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(15, _T("탁송료"), 60));

		pCol0->SetAlignment(DT_RIGHT);		pCol1->SetAlignment(DT_RIGHT);
		pCol2->SetAlignment(DT_RIGHT);		pCol3->SetAlignment(DT_RIGHT);
		pCol4->SetAlignment(DT_RIGHT);		pCol5->SetAlignment(DT_RIGHT);
		pCol6->SetAlignment(DT_RIGHT);		pCol7->SetAlignment(DT_RIGHT);
		pCol8->SetAlignment(DT_RIGHT);		pCol9->SetAlignment(DT_RIGHT);
		pCol10->SetAlignment(DT_RIGHT);		pCol11->SetAlignment(DT_RIGHT);
		pCol12->SetAlignment(DT_RIGHT);		pCol13->SetAlignment(DT_RIGHT);
		pCol14->SetAlignment(DT_RIGHT);		pCol15->SetAlignment(DT_RIGHT);

		m_wndReport.SetPaintManager(new CMyReportPaintManager());
		m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
		m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
		m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
		m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
		m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
		m_wndReport.SetGridColor(RGB(212, 208, 200));

		m_wndReport.GetPaintManager()->m_strNoItems = "";
		m_wndReport.AllowEdit(FALSE);
		m_wndReport.FocusSubItems(TRUE);
		
		CRect rectView,rectReport;
		this->GetWindowRect(rectView);
		m_wndReport.GetWindowRect(rectReport);

		m_wndReport.MoveWindow(0, 40, rectView.Width() , rectView.Height() );
		SetResize(IDC_REPORT_CTRL, sizingRightBottom);
		m_wndReport.ShowWindow(SW_SHOW);
		m_GraphStc.ShowWindow(SW_HIDE);

		Invalidate();

		m_wndReport.Populate();
		m_wndReport.RedrawControl();
	}
}

void CReportForm11::RefreshListRealtime()
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);
	SetHeader(TRUE);
	m_wndReport.GetRecords()->RemoveAll();

	m_bGraphComplete = FALSE;
const char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토"};
	COleDateTime dtNow(COleDateTime::GetCurrentTime());

	COleDateTimeSpan dtSpan;
	dtSpan = m_To - m_From;
	
	if(dtNow.GetHour() > 9 && dtNow.GetHour() < 18)
	{
		if(dtSpan.GetDays() > 31)
		{
			MessageBox("오전 9시 오후 6시 사이에는 1달 간격의 오더만 조회가능합니다.", "확인",MB_ICONINFORMATION);
			return;
		}		
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dailyreport_real_time");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_From);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_To);
	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dt;
	long nTotalCount =0, nTotalCash=0, nTotalOnline=0,nTotalCredit=0, nTotalMile=0,nTotalCard=0, 
		nTotalChargeSum=0, nTotalDeposit=0,nTotalChargeDriving=0,nTotalRiderDeposit=0, 
		nTotalExceptionDeposit=0, nTotalMyRider=0, nTotalOtherRider=0, nTotalTruckCount=0, 
		nTotalTrans=0;
	long nCount, nCash, nOnline,nCredit, nMile,nCard, nChargeSum, nDeposit,nChargeDriving,
			nRiderDeposit, nExceptionDeposit, nMyRider, nOtherRider, nTruckCount, nTrans;
	CString strDateTemp = "", sDt = "";

	int nRecordCount = pRs.GetRecordCount(), nCol = 1;
	if(nRecordCount == 0)
	{
		pRs.Close();
		return;
	}

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("dt", sDt);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nCash", nCash);
		pRs.GetFieldValue("nCredit", nCredit);
		pRs.GetFieldValue("nOnline", nOnline);
		pRs.GetFieldValue("nMile", nMile);
		pRs.GetFieldValue("nCard", nCard);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nDeposit", nDeposit);

		pRs.GetFieldValue("nChargeDriving", nChargeDriving);
		pRs.GetFieldValue("nRiderDeposit", nRiderDeposit);
		pRs.GetFieldValue("nExceptionDeposit", nExceptionDeposit);
		pRs.GetFieldValue("nMyRider", nMyRider);
		pRs.GetFieldValue("nOtherRider", nOtherRider);
		pRs.GetFieldValue("nTruckCount", nTruckCount);
		pRs.GetFieldValue("nTrans", nTrans);
		
		nTotalCount += nCount;
		nTotalCash	+= nCash;
		nTotalCredit += nCredit;
		nTotalOnline += nOnline;
		nTotalCard += nCard;
		nTotalChargeSum += nChargeSum;
		nTotalDeposit += nDeposit;
		nTotalChargeDriving += nChargeDriving;
		nTotalRiderDeposit += nRiderDeposit;
		nTotalExceptionDeposit += nExceptionDeposit;
		nTotalMyRider += nMyRider;
		nTotalOtherRider += nOtherRider;

		nTotalTruckCount += nTruckCount;
		nTotalTrans += nTrans;

		nCol = 1;
		COleDateTime dt(atol(sDt.Left(4)), atol(sDt.Mid(4,2)), atol(sDt.Mid(4,2)),0,0,0);
		strDateTemp.Format("%s(%s)", sDt,	dayofweek[dt.GetDayOfWeek() - 1]);

	
		m_wndReport.AddRecord(new CReportFormRecord_RealTime11(
			strDateTemp,
			LF->GetMyNumberFormat(nCount),
			LF->GetMyNumberFormat(nCash),
			LF->GetMyNumberFormat(nCredit),
			LF->GetMyNumberFormat(nOnline),
			LF->GetMyNumberFormat(nMile),
			LF->GetMyNumberFormat(nCard),
			LF->GetMyNumberFormat(nChargeSum),		
			LF->GetMyNumberFormat(nDeposit),			
			LF->GetMyNumberFormat(nChargeDriving),	
			LF->GetMyNumberFormat(nRiderDeposit),	
			LF->GetMyNumberFormat(nExceptionDeposit),
			LF->GetMyNumberFormat(nMyRider),			
			LF->GetMyNumberFormat(nOtherRider),
			LF->GetMyNumberFormat(nTruckCount),		
			LF->GetMyNumberFormat(nTrans) 
		   ));			
		
		pRs.MoveNext();
	}

	if(nRecordCount > 0)
	{
		m_wndReport.AddRecord(new CReportFormRecord_RealTime11("합계",
			LF->GetMyNumberFormat(nTotalCount),
			LF->GetMyNumberFormat(nTotalCash),
			LF->GetMyNumberFormat(nTotalCredit),
			LF->GetMyNumberFormat(nTotalOnline),
			LF->GetMyNumberFormat(nTotalMile),
			LF->GetMyNumberFormat(nTotalCard),
			LF->GetMyNumberFormat(nTotalChargeSum),
			LF->GetMyNumberFormat(nTotalDeposit),
			LF->GetMyNumberFormat(nTotalChargeDriving),
			LF->GetMyNumberFormat(nTotalRiderDeposit),
			LF->GetMyNumberFormat(nTotalExceptionDeposit),
			LF->GetMyNumberFormat(nTotalMyRider),
			LF->GetMyNumberFormat(nTotalOtherRider),
			LF->GetMyNumberFormat(nTotalTruckCount),
			LF->GetMyNumberFormat(nTotalTrans)
			
			));		
	}

	m_wndReport.Populate();

	pRs.Close();
}


void CReportForm11::RefreshList()
{
	CMyFormView::RefreshList();

	SetHeader(FALSE);
	UpdateData(TRUE);

	m_wndReport.GetRecords()->RemoveAll();
	
	m_bGraphComplete = FALSE;

	//COleDateTime dtFrom = m_From - COleDateTimeSpan(1, 0, 0, 0);
	//COleDateTime dtTo = m_To - COleDateTimeSpan(1, 0, 0, 0);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dailyreport_3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_From);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_To);

	if(m_ui.strID.MakeLower() == "mksong" ||
		m_ui.strID.MakeLower() == "mksong2" ||
		m_ui.strID.MakeLower() == "mksong3" ||
		m_ui.strID.MakeLower() == "mksong4" ||
		m_ui.strID.MakeLower() == "mksong5" ||
		m_ui.strID.MakeLower() == "mksong6" ||
		m_ui.strID.MakeLower() == "mksong7") {
			pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
		}
	else {
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	}

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dt;
	long nTotalCount, nCash, nCredit;

	int nIndex = 0;
	CString csTemp;
	long cnt =0,Total=0,Con=0;
	GRAPH_DATA *pGraphData;
	long nMaxTotal = 0;
	LONGLONG nChargeTotal = 0;
	long nTotalSum = 0;
	long nCompleteSum = 0;
	long nCancelSum = 0;
	long nCancelSum7 = 0;
	long nCompleteCount = 0;
	long nCancelCount = 0;
	long nCancelCount7 = 0;
	long nTakeCount = 0;
	long nGiveCount = 0;
	long nShareRate = 0;
	long nTakeCountSum = 0;
	long nGiveCountSum = 0;
	long nGiveTakeCountSum = 0;
	long nCountPlusGive = 0;
	LONGLONG nCashSum = 0;
	LONGLONG nCreditSum = 0;
	long nTotalDeposit = 0;
	long nTotalDepositSum = 0;

	long nMileageCharge = 0;
	long nChargeCompany = 0;
	long nMileageChargeSum = 0;
	long nChargeCompanySum = 0;
	long nMileage = 0;
	long nMileageSum = 0;

	int nRecordCount = pRs.GetRecordCount();
	if(nRecordCount == 0)
	{
		pRs.Close();
		return;
	}

	pGraphData = new GRAPH_DATA[nRecordCount];

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("dt", dt);
		pRs.GetFieldValue("nTotalCount", nTotalCount);
		pRs.GetFieldValue("nCompleteCount", nCompleteCount);
		pRs.GetFieldValue("nCancelCount", nCancelCount);
		pRs.GetFieldValue("nCredit", nCredit);
		pRs.GetFieldValue("nCash", nCash);
		pRs.GetFieldValue("nGiveCount", nGiveCount);
		pRs.GetFieldValue("nTakeCount", nTakeCount);
		pRs.GetFieldValue("nTotalDeposit", nTotalDeposit);
		pRs.GetFieldValue("nMileageCharge", nMileageCharge);
		pRs.GetFieldValue("nChargeCompany", nChargeCompany);
		pRs.GetFieldValue("nMileage", nMileage);

		if(nTotalCount > 0) {
			nShareRate = nGiveCount * 100 / nTotalCount;
		}
 
		m_wndReport.AddRecord(new CReportFormRecord11(dt, nTotalCount, nCompleteCount, nCancelCount,
											nCash, nCredit, nTotalDeposit, nGiveCount, nTakeCount, nMileageCharge, nChargeCompany, nMileage, FALSE));

		pGraphData[nIndex].nData = max(1, nTotalCount);
		pGraphData[nIndex].dt = dt;
		pGraphData[nIndex].nDayOfWeek = dt.GetDayOfWeek() - 1;

		nMaxTotal = max(nMaxTotal, nTotalCount);
		nCashSum += nCash;
		nCreditSum += nCredit;
		nTotalSum += nTotalCount;
		nCompleteSum += nCompleteCount;
		nCancelSum += nCancelCount;
		nTakeCountSum += nTakeCount;
		nGiveCountSum += nGiveCount;
		nGiveTakeCountSum += (nGiveCount - nTakeCount);
		nCountPlusGive  += (nTotalCount + nTakeCount);
		nTotalDepositSum += nTotalDeposit;
		nMileageChargeSum += nMileageCharge;
		nChargeCompanySum += nChargeCompany;
		nMileageSum += nMileage;
		nIndex++;

		pRs.MoveNext();
	}

	if(nRecordCount > 0)
	{
		m_wndReport.AddRecord(new CReportFormRecord11());

		m_wndReport.AddRecord(new CReportFormRecord11(dt, nTotalSum, nCompleteSum, nCancelSum,
			nCashSum, nCreditSum, nTotalDepositSum, nGiveCountSum, nTakeCountSum, nMileageChargeSum, nChargeCompanySum, nMileageSum, TRUE));

		DrawGraph(pGraphData, max(1, nMaxTotal), nRecordCount);
	}


	m_wndReport.Populate();

	pRs.Close();
}

void CReportForm11::DrawGraph(GRAPH_DATA *pGraphData, UINT nMaxTotal, int nCount)
{
	const COLORREF nColorTable[] = {RED, BLUE, YELLOW, ORANGE, HOT_PINK, FOREST_GREEN, LIGHT_GREY, LAVENDER};
	int n = 0;

	m_Graph = new CGraph(BAR_GRAPH_3D);
	m_Graph->SetGraphTitle(m_From.Format("%Y-%m-%d") + " ~ " + m_To.Format("%Y-%m-%d") + " 일별 건수");

	m_Graph->SetXAxisAlignment(0);
	m_Graph->SetXAxisLabel("일별");
	m_Graph->SetYAxisLabel("건수");
	m_Graph->SetTickLimits(0, (long)(nMaxTotal * 1.1), max(nMaxTotal / 9, 1));
	m_Graph->Set3DDepthRatio(0.005);
	m_Graph->SetGridLines(TRUE);

	while(n < nCount)
	{
		CGraphSeries* series = new CGraphSeries();
		BOOL flag = FALSE;
		int nContainDay = 0, nWeekTotal = 0;

		for(int day = 0; day < 8; day++)
		{
			if(day == 7)
			{
				if(nContainDay > 0)
				{
					int nWeekAvg = nWeekTotal / nContainDay;
					series->SetData(day, nWeekAvg);
				}
				else
				{
					series->SetData(day, 0);
				}

				if(n >= nCount) break;
			}
			else
			{
				if(day == pGraphData[n].nDayOfWeek)
				{
					series->SetData(day, max(pGraphData[n].nData, 1));

					nWeekTotal += pGraphData[n].nData;
					nContainDay++;

					//첫번째 일치
					if(!flag) 
					{
						COleDateTime dt = pGraphData[n].dt, dtTo, dtFrom;
						COleDateTimeSpan tsTo(-day,0,0,0), tsFrom(6 - day, 0, 0,0);
						dtTo = dt + tsTo;
						dtFrom = dt + tsFrom; 
						series->SetLabel(dtTo.Format("%m/%d") + "-" + dtFrom.Format("%d"));
					}

					flag = TRUE;
					if(++n >= nCount) 
					{
						day = 6;
						continue;
					}
				}
				else
				{
					series->SetData(day, 0);
				}
			}
		}

		m_Graph->AddSeries(series);
	}

	for(int i = 0; i < 8; i++)
	{
		m_Graph->SetColor(i, nColorTable[i]);
		m_Graph->SetLegend(i, dayofweek[i]);
	}

	delete[] pGraphData;

	m_bGraphComplete = TRUE;
	Invalidate(TRUE);
}

void CReportForm11::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 
	
	if(m_bGraphComplete)
	{
		CDC *pDC = m_GraphStc.GetDC();
		m_Graph->DrawGraph(pDC);
		ReleaseDC(pDC);
	}
}

void CReportForm11::OnBnClickedButtonRiderFetch()
{
	if(m_chkIntegrteInquery.GetCheck())
		RefreshListRealtime();		
	else
		RefreshList();
		
}

void CReportForm11::OnViewExcel()
{
	CoInitialize(NULL);
	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCustomerTable, 304, m_wndReport.GetRecords()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}

void CReportForm11::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm11::OnBnClickedHorizontalChk()
{
	UpdateData(TRUE);

	if(m_chkIntegrteInquery.GetCheck())
	{

		LF->MsgBox("실시간은 가로보기를 지원지 않습니다");
		m_HorizontalChk.SetCheck(FALSE);
		return;
	}

	if(m_HorizontalChk.GetCheck() == BST_CHECKED)
		Move(TRUE);
	else
		Move(FALSE);
}

void CReportForm11::Move(bool bWidth)
{
	if(bWidth)
	{
		CRect ClientRc,listRc, StcRc;

		GetClientRect(ClientRc);

		int nPane = ClientRc.Width() / 3;

		CWnd *pWnd = (CWnd*)GetDlgItem(IDC_REPORT_CTRL);
		pWnd->GetWindowRect(listRc);
		ScreenToClient(listRc);

		listRc.right = nPane - 2;
		listRc.bottom = ClientRc.bottom;

		CWnd *pWnd1 = (CWnd*)GetDlgItem(IDC_GRAPH);
		pWnd->GetWindowRect(StcRc);
		ScreenToClient(StcRc);

		StcRc.top = listRc.top;
		StcRc.left = nPane + 2;
		StcRc.right = ClientRc.right;
		StcRc.bottom = ClientRc.bottom;

		if(pWnd && pWnd1) {
			pWnd->MoveWindow(listRc, FALSE);
			pWnd1->MoveWindow(StcRc,FALSE);
			
			pWnd1->ShowWindow(SW_SHOW);
			Invalidate();
		}
	}

	else
	{
		CRect rcViewRect, rcList,rcGraph;
		this->GetWindowRect(rcViewRect);
		
		m_GraphStc.GetWindowRect(rcGraph);

		rcList.top = 40;
		rcList.left = 0;
		rcList.right = rcViewRect.right;
		rcList.bottom = rcViewRect.Height() / 2;

		rcGraph.top = rcList.bottom + 3;
		rcGraph.left = 0;
		rcGraph.right = rcViewRect.right;
		rcGraph.bottom = rcViewRect.bottom;

		m_wndReport.MoveWindow(rcList);
		m_GraphStc.MoveWindow(rcGraph);
		m_GraphStc.ShowWindow(SW_SHOW);
		Invalidate();
	}
}

void CReportForm11::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);
}

void CReportForm11::OnBnClickedIntegrateInqueryCheck()
{
	if(m_chkIntegrteInquery.GetCheck() && m_HorizontalChk.GetCheck())
	{
		m_chkIntegrteInquery.SetCheck(FALSE);
		LF->MsgBox("실시간집계는 가로보기를 지원지 않습니다");
		return;
	}
}
