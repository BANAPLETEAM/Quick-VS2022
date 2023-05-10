// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatForm3.h"


// CStatForm3 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStatForm3, CMyFormView)
CStatForm3::CStatForm3()
: CMyFormView(CStatForm3::IDD)
{
	m_Graph = NULL;
	m_bGraphComplete = FALSE;
}

CStatForm3::~CStatForm3()
{

}

void CStatForm3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lcData);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_GRAPH, m_GraphStatic);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_PHONE_BASE_CHECK, m_PhoneBaseCheck);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}


BEGIN_MESSAGE_MAP(CStatForm3, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CStatForm3 메시지 처리기입니다.

void CStatForm3::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&ImageList,LVSIL_SMALL); 
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	ChangeColumnTitle();

	m_PhoneBaseCheck.SetCheck(AfxGetApp()->GetProfileInt("Report", "PhoneBase", FALSE));

	SetResize(IDC_LIST_REPORT, sizingBottom);
	SetResize(IDC_GRAPH, sizingRightBottom);


}

void CStatForm3::RefreshListByCallingCount()
{
	UpdateData(TRUE);

	m_lcData.DeleteAllItems();
	m_bGraphComplete = FALSE;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_report_wno5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	ChangeColumnTitle();

	m_Graph = new CGraph(STACKED_BAR_GRAPH_3D);

	CString strFmt;
	strFmt.Format("접수자 통계(%s ~ %s)", m_dtFrom.Format("%Y-%m-%d"),
		m_dtTo.Format("%Y-%m-%d"));

	m_Graph->SetGraphTitle(strFmt);
	m_Graph->SetXAxisAlignment(0);
	m_Graph->Set3DDepthRatio(.1);
	m_Graph->SetXAxisLabel(" 접수자");
	m_Graph->SetYAxisLabel("건수");
	m_Graph->SetGridLines(TRUE);

	COleDateTime dt;
	long nCustomerReceive, nRiderReceive;
	long nCustomerCall, nRiderCall;
	long nItem = 0;
	long nMaxCount = 1;
	CString strName;
	int nWNo, nTotal = 0, nMiddleTotal = 0;
	char buffer[10];

	while(!pRs.IsEOF())
	{
		nMiddleTotal = 0;

		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nCustomerReceive", nCustomerReceive);
		pRs.GetFieldValue("nRiderReceive", nRiderReceive);
		pRs.GetFieldValue("nCustomerCall", nCustomerCall);
		pRs.GetFieldValue("nRiderCall", nRiderCall);

		CGraphSeries* pSeries = new CGraphSeries();
		pSeries->SetLabel(ltoa(nWNo, buffer, 10));
		pSeries->SetData(0, nCustomerReceive + nCustomerCall);
		pSeries->SetData(1, nRiderReceive + nRiderCall);
		m_Graph->AddSeries(pSeries);
		pRs.MoveNext();

		nMiddleTotal += nCustomerReceive + nRiderReceive + nCustomerCall + nRiderCall;
		nTotal += nCustomerReceive + nRiderReceive + nCustomerCall + nRiderCall;

		nMaxCount = max(nMaxCount, nMiddleTotal);

		m_lcData.InsertItem(nItem, ltoa(nWNo, buffer, 10));
		m_lcData.SetItemText(nItem, 1, strName);
		m_lcData.SetItemText(nItem, 2, ltoa(nCustomerReceive, buffer, 10));
		m_lcData.SetItemText(nItem, 3, ltoa(nRiderReceive, buffer, 10));
		m_lcData.SetItemText(nItem, 4, ltoa(nCustomerCall, buffer, 10));
		m_lcData.SetItemText(nItem, 5, ltoa(nRiderCall, buffer, 10));
		m_lcData.SetItemText(nItem++, 6, ltoa(nMiddleTotal, buffer, 10));
	}

	if(nItem > 0) {
		m_Graph->SetColor(0, FOREST_GREEN);
		m_Graph->SetColor(1, SKY_BLUE);


		m_Graph->SetLegend(0, "고객");
		m_Graph->SetLegend(1, "기사");

		int nTick = (long)(nMaxCount * 1.1 / 10);
		m_Graph->SetTickLimits(0, (long)(nMaxCount * 1.1), max(nTick, 1));
		m_bGraphComplete = TRUE;



		m_lcData.InsertItem(nItem, "");
		m_lcData.SetItemText(nItem, 1, "합계"); 
		m_lcData.SetItemText(nItem, 6, ltoa(nTotal, buffer, 10));
	}

	Invalidate(TRUE);
	AfxGetApp()->WriteProfileInt("Report", "PhoneBase", m_PhoneBaseCheck.GetCheck());
	pRs.Close();

	m_lcData.Populate();
}

void CStatForm3::RefreshList()
{
	CMyFormView::RefreshList();

	//CWaitCursor wait;
	UpdateData(TRUE);

	m_lcData.DeleteAllItems();
	m_bGraphComplete = FALSE;

	CString sSql = "";

	if(m_PhoneBaseCheck.GetCheck())
	{
		RefreshListByCallingCount();
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_report_wno3_1_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_PhoneBaseCheck.GetCheck());
	if(!pRs.Execute(&pCmd)) return;

	ChangeColumnTitle();

	m_Graph = new CGraph(STACKED_BAR_GRAPH_3D);

	CString strFmt;
	strFmt.Format("접수자 통계(%s ~ %s)", m_dtFrom.Format("%Y-%m-%d"),
		m_dtTo.Format("%Y-%m-%d"));

	m_Graph->SetGraphTitle(strFmt);
	m_Graph->SetXAxisAlignment(0);
	m_Graph->Set3DDepthRatio(.1);
	m_Graph->SetXAxisLabel(" 접수자");
	m_Graph->SetYAxisLabel("건수");
	m_Graph->SetGridLines(TRUE);

	COleDateTime dt;
	long nCount1, nCount2;
	long nItem = 0;
	long nMaxCount = 1;
	CString strName;
	int nWNo, nTotal = 0;
	char buffer[10];

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nCount1", nCount1);
		pRs.GetFieldValue("nCount2", nCount2);

		CGraphSeries* pSeries = new CGraphSeries();
		pSeries->SetLabel(ltoa(nWNo, buffer, 10));
		pSeries->SetData(0, nCount1);
		pSeries->SetData(1, nCount2);
		m_Graph->AddSeries(pSeries);
		pRs.MoveNext();

		nMaxCount = max(nMaxCount, nCount2 + nCount1);

		m_lcData.InsertItem(nItem, ltoa(nWNo, buffer, 10));
		m_lcData.SetItemText(nItem, 1, strName);
		m_lcData.SetItemText(nItem, 2, ltoa(nCount1, buffer, 10));
		m_lcData.SetItemText(nItem, 3, ltoa(nCount2, buffer, 10));
		m_lcData.SetItemText(nItem++, 4, ltoa(nCount1 + nCount2, buffer, 10));
		nTotal += nCount1 + nCount2;
	}

	if(nItem > 0) {
		m_Graph->SetColor(0, FOREST_GREEN);
		m_Graph->SetColor(1, SKY_BLUE);

		if(m_PhoneBaseCheck.GetCheck()) {
			m_Graph->SetLegend(0, "고객");
			m_Graph->SetLegend(1, "기사");
		}
		else {
			m_Graph->SetLegend(0, "완료");
			m_Graph->SetLegend(1, "취소");
		}

		int nTick = (long)(nMaxCount * 1.1 / 10);
		m_Graph->SetTickLimits(0, (long)(nMaxCount * 1.1), max(nTick, 1));
		m_bGraphComplete = TRUE;



		m_lcData.InsertItem(nItem, "");
		m_lcData.SetItemText(nItem, 1, "합계");
		m_lcData.SetItemText(nItem, 4, ltoa(nTotal, buffer, 10));
	}

	Invalidate(TRUE);
	AfxGetApp()->WriteProfileInt("Report", "PhoneBase", m_PhoneBaseCheck.GetCheck());
	pRs.Close();
	m_lcData.Populate();
}

void CStatForm3::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStatForm3::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CStatForm3::OnViewExcel()
{
	if(!POWER_CHECK(8900, "통계탭 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 604, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}

void CStatForm3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 

	if(m_bGraphComplete)
	{
		CDC *pDC = m_GraphStatic.GetDC();
		m_Graph->DrawGraph(pDC);
		ReleaseDC(pDC);
	}
}

void CStatForm3::ChangeColumnTitle()
{

	int nColumnCount = m_lcData.GetColumns()->GetCount();

	for (int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumn *p = m_lcData.GetColumns()->GetAt(0);
		m_lcData.GetColumns()->Remove(p);
	}

	if(m_PhoneBaseCheck.GetCheck()) 
	{
		m_lcData.InsertColumn(0,"코드",LVCFMT_LEFT, 40);
		m_lcData.InsertColumn(1,"성명",LVCFMT_LEFT, 60);
		m_lcData.InsertColumn(2,"고객(받음)",LVCFMT_RIGHT, 70);
		m_lcData.InsertColumn(3,"기사",LVCFMT_RIGHT, 40);
		m_lcData.InsertColumn(4,"고객(걸음)",LVCFMT_RIGHT, 70);
		m_lcData.InsertColumn(5,"기사",LVCFMT_RIGHT, 40);
		m_lcData.InsertColumn(6,"합계(건)",LVCFMT_RIGHT, 60);

	}
	else {
		m_lcData.InsertColumn(0,"코드",LVCFMT_LEFT, 40);
		m_lcData.InsertColumn(1,"성명",LVCFMT_LEFT, 60);
		m_lcData.InsertColumn(2,"완료",LVCFMT_RIGHT, 50);
		m_lcData.InsertColumn(3,"취소",LVCFMT_RIGHT, 50);
		m_lcData.InsertColumn(4,"합계(건)",LVCFMT_RIGHT, 60);
	}
}
