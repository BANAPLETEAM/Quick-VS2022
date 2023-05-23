// CReportForm4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ReportForm4.h"


// CReportForm4

IMPLEMENT_DYNCREATE(CReportForm4, CMyFormView)

CReportForm4::CReportForm4()
: CMyFormView(CReportForm4::IDD)
{

}

CReportForm4::~CReportForm4()
{
}

void CReportForm4::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_RIDER_REPORT, m_lstRider);
}

BEGIN_MESSAGE_MAP(CReportForm4, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CReportForm4::OnBnClickedRefreshButton)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CReportForm4 진단입니다.

#ifdef _DEBUG
void CReportForm4::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm4::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CReportForm4::OnBnClickedRefreshButton()
{
	RefreshList();
}

void CReportForm4::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuYesterday();

	SetResize(IDC_RIDER_REPORT, sizingRightBottom);

	m_lstRider.InsertColumn(0, "사번", LVCFMT_LEFT, 40);
	m_lstRider.InsertColumn(1, "기사명", LVCFMT_LEFT, 70);
	m_lstRider.InsertColumn(2, "자사콜수", LVCFMT_RIGHT, 60);
	m_lstRider.InsertColumn(3, "자사현금", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(4, "현금입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(5, "자사신용", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(6, "신용입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(7, "자사지원금", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(8, "자사지원입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(9, "자사합계", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(10, "입금액합계", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(11, "타사콜수", LVCFMT_RIGHT, 60);
	m_lstRider.InsertColumn(12, "타사현금", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(13, "현금입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(14, "타사신용", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(15, "신용입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(16, "타사지원금", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(17, "타사지원입금액", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(18, "타사합계", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(19, "입금액합계", LVCFMT_RIGHT, 70);
	m_lstRider.InsertColumn(20, "총합계", LVCFMT_RIGHT, 65);
	m_lstRider.InsertColumn(21, "입금액총합계", LVCFMT_RIGHT, 80);
	m_lstRider.InsertColumn(22, "주민번호", LVCFMT_LEFT, 90);
	m_lstRider.InsertColumn(23, "주소", LVCFMT_LEFT, 160);

	m_lstRider.Populate();
}

void CReportForm4::RefreshList()
{
	m_lstRider.DeleteAllItems();

	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_report_new_2");

	pCmd.AddParameter(LF->GetCurBranchInfo(TRUE)->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo(TRUE)->bIntegrated);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd))
		return;

	CString strRName, strSSN1, strSSN2, strAddress;
	long nRNo;
	long nMyCallCount, nMyCallCashCharge, nMyCallCashDeposit, nMyCallCreditCharge, nMyCallCreditDeposit;
	long nOtherCallCount, nOtherCallCashCharge, nOtherCallCashDeposit, nOtherCallCreditCharge, nOtherCallCreditDeposit;
	long nMyCallCountS = 0, nMyCallCashChargeS = 0, nMyCallCashDepositS = 0, nMyCallCreditChargeS = 0, nMyCallCreditDepositS = 0;
	long nOtherCallCountS = 0, nOtherCallCashChargeS = 0, nOtherCallCashDepositS = 0, nOtherCallCreditChargeS = 0, nOtherCallCreditDepositS = 0;
	long nMyCallChargeS = 0, nMyCallDepositS = 0, nOtherCallChargeS = 0, nOtherCallDepositS = 0;
	long nChargeS = 0, nDepositS = 0;
	long nMyCallChargeCompany, nMyCallChargeCompanyDeposit, nOtherCallChargeCompany, nOtherCallChargeCompanyDeposit;
	long nMyCallChargeCompanyS = 0, nMyCallChargeCompanyDepositS = 0, nOtherCallChargeCompanyS = 0, nOtherCallChargeCompanyDepositS = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nMyCallCount", nMyCallCount);
		pRs.GetFieldValue("nMyCallCashCharge", nMyCallCashCharge);
		pRs.GetFieldValue("nMyCallCashDeposit", nMyCallCashDeposit);
		pRs.GetFieldValue("nMyCallCreditCharge", nMyCallCreditCharge);
		pRs.GetFieldValue("nMyCallCreditDeposit", nMyCallCreditDeposit);
		pRs.GetFieldValue("nOtherCallCount", nOtherCallCount);
		pRs.GetFieldValue("nOtherCallCashCharge", nOtherCallCashCharge);
		pRs.GetFieldValue("nOtherCallCashDeposit", nOtherCallCashDeposit);
		pRs.GetFieldValue("nOtherCallCreditCharge", nOtherCallCreditCharge);
		pRs.GetFieldValue("nOtherCallCreditDeposit", nOtherCallCreditDeposit);
		pRs.GetFieldValue("nMyCallChargeCompany", nMyCallChargeCompany);
		pRs.GetFieldValue("nMyCallChargeCompanyDeposit", nMyCallChargeCompanyDeposit);
		pRs.GetFieldValue("nOtherCallChargeCompany", nOtherCallChargeCompany);
		pRs.GetFieldValue("nOtherCallChargeCompanyDeposit", nOtherCallChargeCompanyDeposit);
		pRs.GetFieldValue("sSSN1", strSSN1);
		pRs.GetFieldValue("sSSN2", strSSN2);
		pRs.GetFieldValue("sAddress", strAddress);

		m_lstRider.InsertItem(i, LF->GetStringFromLong(nRNo));
		m_lstRider.SetItemText(i, 1, strRName);
		m_lstRider.SetItemText(i, 2, LF->GetMyNumberFormat(nMyCallCount));
		m_lstRider.SetItemText(i, 3, LF->GetMyNumberFormat(nMyCallCashCharge));
		m_lstRider.SetItemText(i, 4, LF->GetMyNumberFormat(nMyCallCashDeposit));
		m_lstRider.SetItemText(i, 5, LF->GetMyNumberFormat(nMyCallCreditCharge));
		m_lstRider.SetItemText(i, 6, LF->GetMyNumberFormat(nMyCallCreditDeposit));
		m_lstRider.SetItemText(i, 7, LF->GetMyNumberFormat(nMyCallChargeCompany));
		m_lstRider.SetItemText(i, 8, LF->GetMyNumberFormat(nMyCallChargeCompanyDeposit));
		m_lstRider.SetItemText(i, 9, LF->GetMyNumberFormat(nMyCallCashCharge + nMyCallCreditCharge + nMyCallChargeCompany));
		m_lstRider.SetItemText(i, 10, LF->GetMyNumberFormat(nMyCallCashDeposit + nMyCallCreditDeposit + nMyCallChargeCompanyDeposit));
		m_lstRider.SetItemText(i, 11, LF->GetMyNumberFormat(nOtherCallCount));
		m_lstRider.SetItemText(i, 12, LF->GetMyNumberFormat(nOtherCallCashCharge));
		m_lstRider.SetItemText(i, 13, LF->GetMyNumberFormat(nOtherCallCashDeposit));
		m_lstRider.SetItemText(i, 14, LF->GetMyNumberFormat(nOtherCallCreditCharge));
		m_lstRider.SetItemText(i, 15, LF->GetMyNumberFormat(nOtherCallCreditDeposit));
		m_lstRider.SetItemText(i, 16, LF->GetMyNumberFormat(nOtherCallChargeCompany));
		m_lstRider.SetItemText(i, 17, LF->GetMyNumberFormat(nOtherCallChargeCompanyDeposit));
		m_lstRider.SetItemText(i, 18, LF->GetMyNumberFormat(nOtherCallCashCharge + nOtherCallCreditCharge + nOtherCallChargeCompany));
		m_lstRider.SetItemText(i, 19, LF->GetMyNumberFormat(nOtherCallCashDeposit + nOtherCallCreditDeposit + nOtherCallChargeCompanyDeposit));
		m_lstRider.SetItemText(i, 20, LF->GetMyNumberFormat(nMyCallCashCharge + nMyCallCreditCharge + nOtherCallCashCharge + nOtherCallCreditCharge + nMyCallChargeCompany + nOtherCallChargeCompany));
		m_lstRider.SetItemText(i, 21, LF->GetMyNumberFormat(nMyCallCashDeposit + nMyCallCreditDeposit + nOtherCallCashDeposit + nOtherCallCreditDeposit + nMyCallChargeCompanyDeposit + nOtherCallChargeCompanyDeposit));
		if(strSSN1.GetLength() > 0)
			m_lstRider.SetItemText(i, 22, strSSN1 + "-" + strSSN2);
		m_lstRider.SetItemText(i, 23, strAddress);

		nMyCallCountS += nMyCallCount;
		nMyCallCashChargeS += nMyCallCashCharge;
		nMyCallCashDepositS += nMyCallCashDeposit;
		nMyCallCreditChargeS += nMyCallCreditCharge;
		nMyCallCreditDepositS += nMyCallCreditDeposit;
		nMyCallChargeCompanyS += nMyCallChargeCompany;
		nMyCallChargeCompanyDepositS += nMyCallChargeCompanyDeposit;
		nOtherCallCountS += nOtherCallCount;
		nOtherCallCashChargeS += nOtherCallCashCharge;
		nOtherCallCashDepositS += nOtherCallCashDeposit;
		nOtherCallCreditChargeS += nOtherCallCreditCharge;
		nOtherCallCreditDepositS += nOtherCallCreditDeposit;
		nOtherCallChargeCompanyS += nOtherCallChargeCompany;
		nOtherCallChargeCompanyDepositS += nOtherCallChargeCompanyDeposit;

		nMyCallChargeS += (nMyCallCashCharge + nMyCallCreditCharge + nMyCallChargeCompany);
		nMyCallDepositS += (nMyCallCashDeposit + nMyCallCreditDeposit + nMyCallChargeCompanyDeposit);
		nOtherCallChargeS += (nOtherCallCashCharge + nOtherCallCreditCharge + nOtherCallChargeCompany);
		nOtherCallDepositS += (nOtherCallCashDeposit + nOtherCallCreditDeposit + nOtherCallChargeCompanyDeposit);

		nChargeS += (nMyCallCashCharge + nMyCallCreditCharge + nOtherCallCashCharge + nOtherCallCreditCharge + nMyCallChargeCompany + nOtherCallChargeCompany);
		nDepositS += (nMyCallCashDeposit + nMyCallCreditDeposit + nOtherCallCashDeposit + nOtherCallCreditDeposit + nMyCallChargeCompanyDeposit + nOtherCallChargeCompanyDeposit);

		pRs.MoveNext();
	}

	if(pRs.GetRecordCount() > 0)
	{
		long nCount = pRs.GetRecordCount();
		m_lstRider.InsertItem(nCount, "");
		m_lstRider.SetItemText(nCount, 1, "합계 : ");
		m_lstRider.SetItemText(nCount, 2, LF->GetMyNumberFormat(nMyCallCountS));
		m_lstRider.SetItemText(nCount, 3, LF->GetMyNumberFormat(nMyCallCashChargeS));
		m_lstRider.SetItemText(nCount, 4, LF->GetMyNumberFormat(nMyCallCashDepositS));
		m_lstRider.SetItemText(nCount, 5, LF->GetMyNumberFormat(nMyCallCreditChargeS));
		m_lstRider.SetItemText(nCount, 6, LF->GetMyNumberFormat(nMyCallCreditDepositS));
		m_lstRider.SetItemText(nCount, 7, LF->GetMyNumberFormat(nMyCallChargeCompanyS));
		m_lstRider.SetItemText(nCount, 8, LF->GetMyNumberFormat(nMyCallChargeCompanyDepositS));
		m_lstRider.SetItemText(nCount, 9, LF->GetMyNumberFormat(nMyCallChargeS));
		m_lstRider.SetItemText(nCount, 10, LF->GetMyNumberFormat(nMyCallDepositS));
		m_lstRider.SetItemText(nCount, 11, LF->GetMyNumberFormat(nOtherCallCountS));
		m_lstRider.SetItemText(nCount, 12, LF->GetMyNumberFormat(nOtherCallCashChargeS));
		m_lstRider.SetItemText(nCount, 13, LF->GetMyNumberFormat(nOtherCallCashDepositS));
		m_lstRider.SetItemText(nCount, 14, LF->GetMyNumberFormat(nOtherCallCreditChargeS));
		m_lstRider.SetItemText(nCount, 15, LF->GetMyNumberFormat(nOtherCallCreditDepositS));
		m_lstRider.SetItemText(nCount, 16, LF->GetMyNumberFormat(nOtherCallChargeCompanyS));
		m_lstRider.SetItemText(nCount, 17, LF->GetMyNumberFormat(nOtherCallChargeCompanyDepositS));
		m_lstRider.SetItemText(nCount, 18, LF->GetMyNumberFormat(nOtherCallChargeS));
		m_lstRider.SetItemText(nCount, 19, LF->GetMyNumberFormat(nOtherCallDepositS));
		m_lstRider.SetItemText(nCount, 20, LF->GetMyNumberFormat(nChargeS));
		m_lstRider.SetItemText(nCount, 21, LF->GetMyNumberFormat(nDepositS));

	}

	m_lstRider.Populate();
}

void CReportForm4::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstRider.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm4::OnViewExcel()
{
	if(!LF->POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 303, m_ui.nWNo, m_lstRider.GetItemCount());  
	CMyExcel::ToExcel(&m_lstRider);
}