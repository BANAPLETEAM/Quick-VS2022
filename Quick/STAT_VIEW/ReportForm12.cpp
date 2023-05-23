// ReportForm12.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm12.h"




CSmsRecord::CSmsRecord()
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
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
}

CSmsRecord::CSmsRecord(CString sDate, long nBannerCount, long nAllocateCount,
					   long nBannerCompleteCount, long nAllocateCompleteCount, 
					   long nBannerFailCount, long nAllocateFailCount, long nCompletePer, long nRealCompletePer,
					   long n0, long n1, long n2, long n3, long n4, long n5, long n6,long nCustomerError, long nServiceError)
{
	m_nBannerCount = nBannerCount;
	m_nBannerCompleteCount = nBannerCompleteCount;
	m_nBannerFaileCount = nBannerFailCount;
	m_nAllocateCount = nAllocateCount;
	m_nAllocateCompleteCount = nAllocateCompleteCount;
	m_nAllocateFailCount = nAllocateFailCount;

	

	AddItem(new CXTPGridRecordItemText(sDate)); //0
	AddItem(new CXTPGridRecordItemMyFormatNumber(nBannerCount + nAllocateCount)); //1
	AddItem(new CXTPGridRecordItemMyFormatNumber(nBannerCount)); //2
	AddItem(new CXTPGridRecordItemMyFormatNumber(nAllocateCount)); //3
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBannerCompleteCount + nAllocateCompleteCount) + "(" + LF->GetMyNumberFormat(nBannerCompleteCount) + "/" + LF->GetMyNumberFormat(nAllocateCompleteCount) + ")"   )); //4 <--
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBannerFailCount + nAllocateFailCount) + "(" + LF->GetMyNumberFormat(nBannerFailCount) + "/" + LF->GetMyNumberFormat(nAllocateFailCount) + ")" )); //5 <--
	AddItem(new CXTPGridRecordItemMyPerNumber(nCompletePer));//6
	AddItem(new CXTPGridRecordItemMyPerNumber(nRealCompletePer));//7
	AddItem(new CXTPGridRecordItemMyFormatNumber(nBannerCompleteCount));//7
	AddItem(new CXTPGridRecordItemMyHyponNumber(n0));//8
	AddItem(new CXTPGridRecordItemMyHyponNumber(n1));//9
	AddItem(new CXTPGridRecordItemMyHyponNumber(n2));//10
	AddItem(new CXTPGridRecordItemMyHyponNumber(n3));//11
	AddItem(new CXTPGridRecordItemMyHyponNumber(n4));//12
	AddItem(new CXTPGridRecordItemMyHyponNumber(n5));//13
	AddItem(new CXTPGridRecordItemMyHyponNumber(n6));//14
	AddItem(new CXTPGridRecordItemMyHyponNumber(nCustomerError + nServiceError));//15
	AddItem(new CXTPGridRecordItemMyHyponNumber(nCustomerError));//16
	AddItem(new CXTPGridRecordItemMyHyponNumber(nServiceError));//17
}


void CSmsRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	//	int nCol = pDrawArgs->pColumn->GetIndex();
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	//	int nRow = pDrawArgs->pRow->GetIndex();
	int nRow = this->GetIndex();

	CXTPGridColumn *pColumn = NULL;

	CString strCaption = (this->GetItem(nCol))->GetCaption(pColumn);
	//CString strCaption = ((CXTPGridRecordItemText*)GetRecords()->GetAt(nRow)->GetItem(nCol))->GetCaption();

	if(nCol >= 16 && strCaption != "-")
		pItemMetrics->clrForeground = RGB(0, 0, 255);

	if(strCaption != "-")
		pDrawArgs->nTextAlign = DT_RIGHT;
}


IMPLEMENT_DYNCREATE(CReportForm12, CMyFormView)

CReportForm12::CReportForm12()
	: CMyFormView(CReportForm12::IDD)
, m_dtFrom(COleDateTime::GetCurrentTime())
, m_dtTo(COleDateTime::GetCurrentTime())
{

}

CReportForm12::~CReportForm12()
{
}

void CReportForm12::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
}

BEGIN_MESSAGE_MAP(CReportForm12, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CReportForm12 진단입니다.

#ifdef _DEBUG
void CReportForm12::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm12::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm12 메시지 처리기입니다.

void CReportForm12::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm12::RefreshList()
{
	m_wndReport.GetRecords()->RemoveAll();
	UpdateData(true);

	long nSumAllCount;
	long nSumBannerCount, nSumAllocateCount;
	long nSumBannerCompleteCount, nSumBannerFailCount;
	long nSumAllocateCompleteCount, nSumAllocateFailCount;
	long nSumn0, nSumn1, nSumn2, nSumn3, nSumn4, nSumn5, nSumn6;
	long nSumUserError, nSumServiceError;

	nSumAllCount = nSumBannerCompleteCount = nSumBannerFailCount = nSumAllocateCompleteCount = nSumAllocateFailCount = 0;
	nSumBannerCount = nSumAllocateCount = 0;
	nSumn0 = nSumn1 = nSumn2 = nSumn3 = nSumn4 = nSumn5 = nSumn6 = 0;
	nSumUserError = nSumServiceError = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_smscountlog");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	CString sDate;
	long nBannerCount, nBannerCompleteCount, nBannerFailCount;
	long nAllocateCount, nAllocateCompleteCount, nAllocateFailCount;
	long n0, n1, n2, n3, n4, n5, n6;
	long nCustomerError, nServiceError;
	long nCompletePer, nRealCompletePer;
	long nSumCompletePer, nSumRealCompletePer;

	nSumCompletePer = nSumRealCompletePer = 0;



	if(!pRs.Execute(&pCmd)) return;

	long i = 0 ;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("dtSend", sDate);
		pRs.GetFieldValue("nBannerCount", nBannerCount);
		pRs.GetFieldValue("nBannerCompleteCount", nBannerCompleteCount);
		pRs.GetFieldValue("nBannerFailCount", nBannerFailCount);
		pRs.GetFieldValue("nAllocateCount", nAllocateCount);
		pRs.GetFieldValue("nAllocateCompleteCount", nAllocateCompleteCount);
		pRs.GetFieldValue("nAllocateFailCount", nAllocateFailCount);
		pRs.GetFieldValue("n0", n0);
		pRs.GetFieldValue("n1", n1);
		pRs.GetFieldValue("n2", n2);
		pRs.GetFieldValue("n3", n3);
		pRs.GetFieldValue("n4", n4);
		pRs.GetFieldValue("n5", n5);
		pRs.GetFieldValue("n6", n6);
		pRs.GetFieldValue("nCustomerError", nCustomerError);
		pRs.GetFieldValue("nServiceError", nServiceError);


		if(nBannerCount == 0)
		{
			nCompletePer = 0;
			nRealCompletePer = 0;
		}
		else
		{
			nCompletePer = ((float)nBannerCompleteCount / (float)nBannerCount) * 100;
			nRealCompletePer = ((float)nBannerCompleteCount / ((float)nBannerCount - (float)nCustomerError)) * 100;
		}

		m_wndReport.AddRecord(new CSmsRecord(sDate, nBannerCount, nAllocateCount, nBannerCompleteCount, nAllocateCompleteCount, nBannerFailCount, nAllocateFailCount,
			nCompletePer, nRealCompletePer, n0, n1, n2, n3, n4, n5, n6, nCustomerError, nServiceError));

		nSumAllCount = nSumAllCount + nBannerCount + nAllocateCount;
		nSumBannerCompleteCount += nBannerCompleteCount;
		nSumAllocateCompleteCount += nAllocateCompleteCount;
		nSumBannerFailCount += nBannerFailCount;
		nSumAllocateFailCount += nAllocateFailCount;
		nSumBannerCount += nBannerCount;
		nSumAllocateCount += nAllocateCount;
		nSumn0 += n0;
		nSumn1 += n1;
		nSumn2 += n2;
		nSumn3 += n3;
		nSumn4 += n4;
		nSumn5 += n5;
		nSumn6 += n6;
		nSumUserError += nCustomerError;
		nSumServiceError += nServiceError;


		pRs.MoveNext();
	}

	m_wndReport.AddRecord(new CSmsRecord());

	if(nSumBannerCount == 0)
	{
		nSumCompletePer = 0;
		nRealCompletePer = 0;
	}
	else
	{
		nSumCompletePer = ((float)nSumBannerCompleteCount / (float)nSumBannerCount) * 100;
		nSumRealCompletePer = ((float)nSumBannerCompleteCount / ((float)nSumBannerCount - (float)nSumUserError)) * 100;
	}

	m_wndReport.AddRecord(new CSmsRecord("합계:", nSumBannerCount, nSumAllocateCount, nSumBannerCompleteCount, nSumAllocateCompleteCount, 
		nSumBannerFailCount, nSumAllocateFailCount,	nSumCompletePer, nSumRealCompletePer, 
		nSumn0, nSumn1, nSumn2, nSumn3, nSumn4, nSumn5, nSumn6, nSumUserError, nSumServiceError));

	m_wndReport.Populate();

}
void CReportForm12::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_CTRL, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("일자"), 65, FALSE));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("총건수"), 65, FALSE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("광고건수"), 70, FALSE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("배차건수"), 70, FALSE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("실제발송(광고/배차)"), 135, FALSE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("오류건수(광고/배차)"), 135, FALSE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, _T("성공률"), 55, FALSE));
	CXTPGridColumn *pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, _T("실성공률"), 70, FALSE));
	CXTPGridColumn *pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, _T("광고발송"), 70, FALSE));
	CXTPGridColumn *pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, _T("당일"), 40, FALSE));
	CXTPGridColumn *pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, _T("1일"), 35, FALSE));
	CXTPGridColumn *pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, _T("2일"), 35, FALSE));
	CXTPGridColumn *pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(12, _T("3일"), 35, FALSE));
	CXTPGridColumn *pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(13, _T("4일"), 35, FALSE));
	CXTPGridColumn *pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, _T("5일"), 35, FALSE));
	CXTPGridColumn *pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(15, _T("6일"), 35, FALSE));
	CXTPGridColumn *pCol16 = m_wndReport.AddColumn(new CXTPGridColumn(16, _T("광고오류"), 70, FALSE));
	CXTPGridColumn *pCol17 = m_wndReport.AddColumn(new CXTPGridColumn(17, _T("사용자오류"), 80, FALSE));
	CXTPGridColumn *pCol18 = m_wndReport.AddColumn(new CXTPGridColumn(18, _T("통신사오류"), 80, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetAlignment(DT_RIGHT);	
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetAlignment(DT_RIGHT);
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->SetAlignment(DT_RIGHT);
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->SetAlignment(DT_RIGHT);
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->SetAlignment(DT_RIGHT);
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->SetAlignment(DT_RIGHT);
	pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->SetAlignment(DT_RIGHT);
	pCol8->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol8->SetAlignment(DT_RIGHT);
	pCol9->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol9->SetAlignment(DT_CENTER);
	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->SetAlignment(DT_CENTER);
	pCol11->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol11->SetAlignment(DT_CENTER);
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol12->SetAlignment(DT_CENTER);
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol13->SetAlignment(DT_CENTER);
	pCol14->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol14->SetAlignment(DT_CENTER);
	pCol15->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol15->SetAlignment(DT_CENTER);
	pCol16->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol16->SetAlignment(DT_CENTER);
	pCol17->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol17->SetAlignment(DT_CENTER);
	pCol18->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol18->SetAlignment(DT_CENTER);

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.Populate();
	m_wndReport.SetGridColor(RGB(180, 180, 200));
}
