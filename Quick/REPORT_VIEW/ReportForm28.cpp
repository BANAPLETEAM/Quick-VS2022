// ReportForm13.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm28.h"

// CReportForm28

IMPLEMENT_DYNCREATE(CReportForm28, CMyFormView)

CReportForm28::CReportForm28()
	: CMyFormView(CReportForm28::IDD)
	, m_dtFrom(COleDateTime::GetCurrentTime())
	, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CReportForm28::~CReportForm28()
{
	
}

void CReportForm28::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSortType);
	DDX_Control(pDX, IDC_EDIT1, m_edtSearch);
	
}

BEGIN_MESSAGE_MAP(CReportForm28, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)

	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)

	ON_EN_CHANGE(IDC_EDIT1, &CReportForm28::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CReportForm28 진단입니다.

#ifdef _DEBUG
void CReportForm28::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm28::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm28 메시지 처리기입니다.

void CReportForm28::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm28::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	int nCol = 0;	
	m_wndReport.m_bHeader = TRUE;
	m_wndReport.SetExtendedStyle(0);
	m_wndReport.InsertColumn(nCol++, "순번", DT_CENTER, 40);
	m_wndReport.InsertColumn(nCol++, "오더번호", DT_LEFT, 60);
	m_wndReport.InsertColumn(nCol++, "발주사", DT_LEFT, 90);
	m_wndReport.InsertColumn(nCol++, "접수시간", DT_LEFT, 100);
	m_wndReport.InsertColumn(nCol++, "도시", DT_LEFT, 45);
	m_wndReport.InsertColumn(nCol++, "업체", DT_LEFT, 80);
	m_wndReport.InsertColumn(nCol++, "출발지", DT_LEFT, 100);
	m_wndReport.InsertColumn(nCol++, "도착지", DT_LEFT, 100);


	m_wndReport.InsertColumn(nCol++, "차량", DT_CENTER, 45);
	m_wndReport.InsertColumn(nCol++, "지불", DT_CENTER, 45);

	m_wndReport.InsertColumn(nCol++, "상태", DT_CENTER, 45);
	m_wndReport.InsertColumn(nCol++, "(탁)상태", DT_CENTER, 55);
	m_wndReport.InsertColumn(nCol++, "기본요금", DT_RIGHT, 60); 
	m_wndReport.InsertColumn(nCol++, "추가", DT_RIGHT, 50);
	m_wndReport.InsertColumn(nCol++, "할인", DT_RIGHT, 50);
	m_wndReport.InsertColumn(nCol++, "소계", DT_RIGHT, 60);	
	m_wndReport.InsertColumn(nCol++, "탁송료", DT_RIGHT, 50);
	m_wndReport.InsertColumn(nCol++, "연계료", DT_RIGHT, 50);
	m_wndReport.InsertColumn(nCol++, "타사요금", DT_RIGHT, 60);
	m_wndReport.InsertColumn(nCol++, "총합계", DT_RIGHT, 70); 
	m_wndReport.InsertColumn(nCol++, "타사입금액", DT_RIGHT, 70); 
	m_wndReport.InsertColumn(nCol++, "연계율", DT_RIGHT, 45); 
	m_wndReport.InsertColumn(nCol++, "수수료비", DT_RIGHT, 70); 


	m_wndReport.Populate();

	m_cmbSortType.SetCurSel(0);

	//m_wndReport.LoadReportOrder("CReportForm28", "m_wndReport");
}

void CReportForm28::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(true);

	if(m_wndReport.GetRecords()->GetCount()>0)
		m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_company_income2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(m_cmbSortType.GetCurSel());
	if(!pRs.Execute(&pCmd)) return;

	long nTotChargeTot =0 ,nTotChargeTrans =0,nTotConsignCommission =0, nTotBackOrderDeposit = 0,
		nTotOtherCharge =0,nTotConsignSumCharge =0,  nTotConsignRateCharge=0; 
	
	for(int i=0; i<pRs.GetRecordCount(); i++) 
	{ 
		CString sBranchName,sSName,sDName,sConsignCity,sName,sTel;
		COleDateTime dt1;
		int nState,nConsignRate,nCarType, nPayType;
		long nChargeBasic,nChargeDis,nChargeAdd,nChargeSum,nConsignCompany,nConsignCommission,
			nConsignSumCharge, nCompany, nTNo, nChargeTrans,nConsignRateCharge =0, nOtherCharge = 0;
		long nBackOrderState, nBackOrderDeposit, nBackOrderCharge;
		pRs.GetFieldValue("nTNo",		nTNo);	
		
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sSName", sSName);
		pRs.GetFieldValue("sDName", sDName);
		pRs.GetFieldValue("sConsignCity", sConsignCity);
		pRs.GetFieldValue("nConsignRate", nConsignRate);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nConsignCompany", nConsignCompany);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nConsignCommission", nConsignCommission);
		
		pRs.GetFieldValue("nConsignSumCharge", nConsignSumCharge);
		pRs.GetFieldValue("nConsignCompany", nConsignCompany);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nPayType", nPayType);

		pRs.GetFieldValue("nBackOrderCharge", nBackOrderCharge);
		pRs.GetFieldValue("nBackOrderDeposit", nBackOrderDeposit);
		pRs.GetFieldValue("nBackOrderState", nBackOrderState);


		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sTel", sTel);

		//nOtherCharge = (nConsignSumCharge > 0) ? nConsignSumCharge - nChargeTrans - nConsignCommission : 0;
		nConsignRateCharge = nBackOrderDeposit > 0 ?  int(nBackOrderDeposit * nConsignRate /100) : 0;

		m_wndReport.MyAddItem(i);
		m_wndReport.MyAddItem(nTNo);
		m_wndReport.MyAddItem(LF->GetCurBranchInfo(nCompany)->strBranchName);
		m_wndReport.MyAddItem(dt1.Format("%Y-%m-%d %H:%M"));
		m_wndReport.MyAddItem(sConsignCity);
		m_wndReport.MyAddItem(sName);
		
		m_wndReport.MyAddItem(sSName);
		m_wndReport.MyAddItem(sDName);
		m_wndReport.MyAddItem(LF->GetCarTypeFromLong(nCarType));
		m_wndReport.MyAddItem(LF->GetPayTypeFromLong(nPayType));
		m_wndReport.MyAddItem(LF->GetStateString(nState));
		m_wndReport.MyAddItem(LF->GetStateString(nBackOrderState));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nChargeBasic));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nChargeAdd));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nChargeDis));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nChargeSum));		

		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nChargeTrans));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nConsignCommission));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nBackOrderCharge));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nConsignSumCharge));

		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nBackOrderDeposit));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nConsignRate));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nConsignRateCharge));	
		m_wndReport.EndItem();

		
		nTotChargeTot += nChargeSum;
		nTotChargeTrans += nChargeTrans;
		nTotConsignCommission += nConsignCommission;
		nTotOtherCharge += nBackOrderCharge;
		nTotConsignSumCharge += nConsignSumCharge;
		nTotConsignRateCharge += nConsignRateCharge;
		nTotBackOrderDeposit += nBackOrderDeposit;
		pRs.MoveNext();
	}

	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("합 계");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");

	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem("");	
	m_wndReport.MyAddItem("");	
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotChargeTot));
	
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotChargeTrans));
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotConsignCommission));
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotOtherCharge));		

	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotConsignSumCharge));
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotBackOrderDeposit));
	m_wndReport.MyAddItem("");
	m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTotConsignRateCharge));	
	m_wndReport.EndItem();

	pRs.Close();
	m_wndReport.Populate();
   
}
 

void CReportForm28::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol != 13) return;

	

}



void CReportForm28::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

void CReportForm28::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm28::OnViewExcel()
{
	if(!LF->POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 312, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}



void CReportForm28::OnEnChangeSearchEdit()
{
	 m_wndReport.Filter(LF->GetEditString(&m_edtSearch) );		 

}