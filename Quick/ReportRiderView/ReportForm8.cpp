// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm8.h"
#include "Graph.h"

// CReportForm8 대화 상자입니다.

IMPLEMENT_DYNCREATE(CReportForm8, CMyFormView)
CReportForm8::CReportForm8()
	: CMyFormView(CReportForm8::IDD)
{
	COleDateTimeSpan span(61, 0,0,0);
	m_dtFrom= COleDateTime::GetCurrentTime() - span;
	m_dtTo = COleDateTime::GetCurrentTime();
}

CReportForm8::~CReportForm8()
{
}

void CReportForm8::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_COUPON_EDIT, m_CouponEdit);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_COUPON_EDIT, m_strCoupon);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_500_BTN, m_500Btn);
	DDX_Control(pDX, IDC_1000_BTN, m_1000Btn);
	DDX_Control(pDX, IDC_2000_BTN, m_2000Btn);
	DDX_Control(pDX, IDC_SHOW_BTN, m_ShowBtn);
}

BEGIN_MESSAGE_MAP(CReportForm8, CMyFormView)
	ON_BN_CLICKED(IDC_SHOW_BTN, OnBnClickedShowBtn)
	ON_BN_CLICKED(IDC_TODAY_BTN, OnBnClickedTodayBtn)
//	ON_BN_CLICKED(IDC_WEEK_BTN, OnBnClickedWeekBtn)
//	ON_BN_CLICKED(IDC_MONTH_BTN, OnBnClickedMonthBtn)
//	ON_BN_CLICKED(IDC_EXACT_MONTH_BTN, OnBnClickedExactMonthBtn)
	ON_BN_CLICKED(IDC_500_BTN, OnBnClicked500Btn)
	ON_BN_CLICKED(IDC_1000_BTN, OnBnClicked1000Btn)
	ON_BN_CLICKED(IDC_2000_BTN, OnBnClicked2000Btn)
	ON_EN_CHANGE(IDC_COUPON_EDIT, OnEnChangeCouponEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CReportForm8 메시지 처리기입니다.


void CReportForm8::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	m_List.InsertColumn(0,"소속코드",LVCFMT_LEFT, 60);
	m_List.InsertColumn(1,"기사번호",LVCFMT_LEFT, 80);
	m_List.InsertColumn(2,"기사명",LVCFMT_LEFT, 120);
	m_List.InsertColumn(3,"쿠폰수",LVCFMT_RIGHT, 80);
	m_List.InsertColumn(4,"합계금액",LVCFMT_RIGHT, 120);
	m_List.Populate();

	SetResize(IDC_LIST, sizingRightBottom);
}

void CReportForm8::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_coupon_report3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	long nRiderCompany, nRNo, nCnt;
	CString strName;
	long nItem = 0;
	long nNumber = 0;
	long nSum = 0, nSumTotal = 0;

	m_List.DeleteAllItems();

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nCnt", nCnt);

		nSum = nCnt * atol(m_strCoupon);

		m_List.InsertItem(nItem, GetStringFromLong(nRiderCompany));
		m_List.SetItemText(nItem, 1, GetStringFromLong(nRNo));
		m_List.SetItemText(nItem, 2, strName);
		m_List.SetItemText(nItem, 3, GetStringFromLong(nCnt));
		m_List.SetItemText(nItem++, 4, GetMyNumberFormat(nSum));

		nNumber += nCnt;
		nSumTotal += nSum;
		pRs.MoveNext();
	}

	if(nItem > 0)
	{
		m_List.InsertItem(nItem++, "");
		m_List.InsertItem(nItem, "");
		m_List.SetItemText(nItem, 1, "라이더수");
		m_List.SetItemText(nItem, 3, "총쿠폰수");
		m_List.SetItemText(nItem++, 4, "총금액");

		m_List.InsertItem(nItem, "");
		m_List.SetItemText(nItem, 1, GetStringFromLong(nItem - 2));
		m_List.SetItemText(nItem, 3, GetStringFromLong(nNumber));
		m_List.SetItemText(nItem, 4, GetMyNumberFormat(nSumTotal));
	}

	pRs.Close();
	m_List.Populate();
}

void CReportForm8::OnBnClickedShowBtn()
{
	RefreshList();
}

void CReportForm8::OnBnClickedTodayBtn()
{
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	m_FromDT.SetTime(dtTime);
	m_ToDT.SetTime(dtTime);
}

void CReportForm8::OnBnClickedWeekBtn()
{
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span(7, 0, 0, 0);
	m_FromDT.SetTime(dtTime - span);
	m_ToDT.SetTime(dtTime);
}

void CReportForm8::OnBnClickedMonthBtn()
{
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span(30, 0, 0, 0);
	m_FromDT.SetTime(dtTime - span);
	m_ToDT.SetTime(dtTime);
}

void CReportForm8::OnBnClickedExactMonthBtn()
{
	int nDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	m_ToDT.GetTime(dtTo);
	dtFrom.SetDate(dtFrom.GetYear(), dtFrom.GetMonth(), 1);
	dtTo.SetDate(dtFrom.GetYear(), dtFrom.GetMonth(), nDays[dtFrom.GetMonth() - 1]);
	m_FromDT.SetTime(dtFrom);
	m_ToDT.SetTime(dtTo);
}

void CReportForm8::OnBnClicked500Btn()
{
	m_CouponEdit.SetWindowText("500");
	OnEnChangeCouponEdit();
}

void CReportForm8::OnBnClicked1000Btn()
{
	m_CouponEdit.SetWindowText("1000");
	OnEnChangeCouponEdit();
}

void CReportForm8::OnBnClicked2000Btn()
{
	m_CouponEdit.SetWindowText("2000");
	OnEnChangeCouponEdit();
}

void CReportForm8::OnEnChangeCouponEdit()
{
	CString strCoupon;
	m_CouponEdit.GetWindowText(strCoupon);
	int nCoupon = atol(strCoupon);

	CXTPGridRecords *pRecords = m_List.GetRecords();
	int nRecordCount = pRecords->GetCount(), nTotalCharge = 0;

	for(int i = 0; i < nRecordCount; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strCode = m_List.GetItemText(pRecord, 0);
		if(strCode.GetLength() == 0)
			break;

		CString strCount = m_List.GetItemText(pRecord, 3);
		m_List.SetItemText(pRecord, 4, GetMyNumberFormat(atol(strCount) * nCoupon));
		nTotalCharge += atol(strCount) * nCoupon;
	}

	if(nRecordCount > 2)
		m_List.SetItemText(nRecordCount - 1, 4, GetMyNumberFormat(nTotalCharge));
	m_List.Populate();
}

void CReportForm8::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm8::OnViewExcel()
{
	if(!POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 329, m_ui.nWNo, m_List.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_List);
}