// BranchReportWantTransferDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchReportWantTransferDlg.h"
#include "ShareReportMyRequestDetailDlg.h"


// CBranchReportWantTransferDlg
IMPLEMENT_DYNCREATE(CBranchReportWantTransferDlg, CMyFormView)

CBranchReportWantTransferDlg::CBranchReportWantTransferDlg()
	: CMyFormView(CBranchReportWantTransferDlg::IDD)
	, m_dtFrom(COleDateTime::GetCurrentTime())
	, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CBranchReportWantTransferDlg::~CBranchReportWantTransferDlg()
{
}

void CBranchReportWantTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
}

BEGIN_MESSAGE_MAP(CBranchReportWantTransferDlg, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_CTRL, OnReportItemDbClick)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CBranchReportWantTransferDlg 진단입니다.

#ifdef _DEBUG
void CBranchReportWantTransferDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CBranchReportWantTransferDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CBranchReportWantTransferDlg 메시지 처리기입니다.

void CBranchReportWantTransferDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CBranchReportWantTransferDlg::RefreshList()
{
	UpdateData(true);

	m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_my_request");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	CString sMemo, sReceiveMessage, strFormat;
	long nID, nToCompany, nRequestCharge, nReceiveCharge, nState;
	COleDateTime dtRequest, dtReceive;

//	char buffer[10];
	for(int i = 0 ; i < pRs.GetRecordCount(); i++)
	{ 
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("dtRequest", dtRequest);
		pRs.GetFieldValue("nRequestCharge", nRequestCharge);
		pRs.GetFieldValue("dtReceive", dtReceive);
		pRs.GetFieldValue("nReceiveCharge", nReceiveCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sReceiveMessage", sReceiveMessage);

		if(nState == 1 || nState == 3)
		{
			nReceiveCharge = -1;

			COleDateTime dtFormat;
			dtFormat.SetDateTime(1999, 01, 01, 01, 01, 01);

			dtReceive = dtFormat;
		}
/*
		if(nState == 2 || nState == 4) //정상종료 
		{
			m_List.SetItemText(i, 6, dtReceive.Format("%m-%d %H:%M"));

			strFormat.Format("%d원", nReceiveCharge);
			m_List.SetItemText(i, 7, strFormat);
		}
		else
		{
			m_List.SetItemText(i, 6, "");
			m_List.SetItemText(i, 7, "");
		}
*/
		m_wndReport.AddRecord(new CWantTransferRecord(i, nToCompany, sMemo, nState, dtRequest, nRequestCharge, dtReceive,
									nReceiveCharge, sReceiveMessage));
		
		pRs.MoveNext();
	}

	m_wndReport.Populate();
}

void CBranchReportWantTransferDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "순번", 20, TRUE));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "요청회사", 90, TRUE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "사유", 150, TRUE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, "상태", 70, TRUE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, "요청일", 80, TRUE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, "요청금액", 70, TRUE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, "입금날짜", 80, TRUE));
	CXTPGridColumn *pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, "입금금액", 70, TRUE));
	CXTPGridColumn *pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, "받은메세지", 150, TRUE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetAlignment(DT_RIGHT);	
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetAlignment(DT_RIGHT);
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->SetAlignment(DT_RIGHT);
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->SetAlignment(DT_CENTER);
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->SetAlignment(DT_CENTER);
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->SetAlignment(DT_CENTER);
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->SetAlignment(DT_CENTER);
	pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->SetAlignment(DT_CENTER);
	pCol8->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol8->SetAlignment(DT_CENTER);

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.SetGridColor(RGB(180, 180, 200));

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(180, 180, 200));

	m_wndReport.Populate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

int CBranchReportWantTransferDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return true;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CBranchReportWantTransferDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	//int nRow = pItemNotify->pRow->GetIndex();
	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	nRow = pRecord->GetIndex();

	CShareReportMyRequestDetailDlg pDlg;

	CXTPGridColumn *pColumn = NULL;
	CString SeDate, ReDate, SeMoney, ReMoney, SeMemo, ReMemo;

	SeDate = ((CXTPGridRecordItemDateTime*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(4))->GetCaption(pColumn);
	SeMoney = ((CXTPGridRecordItemNumber*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(5))->GetCaption(pColumn);
	SeMemo= ((CXTPGridRecordItemText*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(2))->GetCaption(pColumn);

	ReDate = ((CXTPGridRecordItemDateTime*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(6))->GetCaption(pColumn);
	ReMoney = ((CXTPGridRecordItemNumber*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(7))->GetCaption(pColumn);
	ReMemo = ((CXTPGridRecordItemText*)m_wndReport.GetRecords()->GetAt(nRow)->GetItem(8))->GetCaption(pColumn);

	pDlg.m_SeDate = SeDate;
	pDlg.m_SeMoney = SeMoney;
	pDlg.m_SeMemo = SeMemo;
	pDlg.m_ReDate = ReDate;
	pDlg.m_ReMoney = ReMoney;
	pDlg.m_ReMemo = ReMemo;

	pDlg.DoModal();

}
