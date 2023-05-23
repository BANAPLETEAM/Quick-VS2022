// ReportForm25.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm25.h"


// CReportForm25

IMPLEMENT_DYNCREATE(CReportForm25, CMyFormView)

CReportForm25::CReportForm25()
	: CMyFormView(CReportForm25::IDD)
{

}

CReportForm25::~CReportForm25()
{
}

void CReportForm25::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_List);

	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_tmFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_tmTo);
	DDX_Control(pDX, IDC_DTP_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DTP_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_DAY_COMBO, m_cmbDay);
}

BEGIN_MESSAGE_MAP(CReportForm25, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm25::OnBnClickedRefreshBtn)
	ON_CBN_SELCHANGE(IDC_DAY_COMBO, &CReportForm25::OnCbnSelchangeDayCombo)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm25::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_SEND_SMS_BTN, &CReportForm25::OnBnClickedSendSmsBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CReportForm25 진단입니다.

#ifdef _DEBUG
void CReportForm25::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm25::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CReportForm25::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuToday();
	m_btnDate.OnMenuExactMonth();

	m_List.InsertColumn(0, "사번", LVCFMT_LEFT, 45);
	m_List.InsertColumn(1, "기사명", LVCFMT_LEFT, 60);
	m_List.InsertColumn(2, "현금", LVCFMT_LEFT, 60);
	m_List.InsertColumn(3, "신용", LVCFMT_LEFT, 60);
	m_List.InsertColumn(4, "송금", LVCFMT_LEFT, 60);
	m_List.InsertColumn(5, "직접수금", LVCFMT_LEFT, 60);
	m_List.InsertColumn(6, "업체부담긍", LVCFMT_LEFT, 60);
	m_List.InsertColumn(7, "기타", LVCFMT_LEFT, 50);
	m_List.InsertColumn(8, "탁송(외,송)", LVCFMT_LEFT, 70);
	m_List.InsertColumn(9, "지입일", LVCFMT_LEFT, 55);
	m_List.InsertColumn(10, "지입금", LVCFMT_LEFT, 60);
	m_List.InsertColumn(11, "합계[외+송+직+기+탁+업]", LVCFMT_LEFT, 135);
	m_List.InsertColumn(12, "최종[지입금-합계]", LVCFMT_LEFT, 120);
	m_List.InsertColumn(13, "SMS", LVCFMT_LEFT, 300);
	m_List.InsertColumn(14, "휴대폰", LVCFMT_LEFT, 100);
	m_List.Populate();

	m_cmbDay.SetCurSel(0);

	SetResize(IDC_REPORT_LIST, sizingRightBottom);
}

void CReportForm25::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm25::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);

	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rider_report_by_fixed_deposit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmTo);

	char buffer[10];
	long nRNo, nCash, nCredit, nOnline, nTran, nDir, nEtc; //탁송은 신용만 올라옴
	CString sRName, sHp;
	long nFixDay, nFixDeposit, nChargeSum, nChargeFinal;
	long nCreditCon, nOnlineCon, nChargeCompany;

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("nCashCharge", nCash);
		pRs.GetFieldValue("nCreditCharge", nCredit); 
		pRs.GetFieldValue("nOnlineCharge", nOnline);
		pRs.GetFieldValue("nBillCharge", nDir);
		pRs.GetFieldValue("nEtcCharge", nEtc);
		pRs.GetFieldValue("nCreditCon", nCreditCon);
		pRs.GetFieldValue("nOnlineCon", nOnlineCon);
		pRs.GetFieldValue("nPaymentDay", nFixDay);
		pRs.GetFieldValue("nFixedDeposit", nFixDeposit);
		pRs.GetFieldValue("sHp", sHp);
		pRs.GetFieldValue("nChargeCompany", nChargeCompany);

		nTran = nCreditCon + nOnlineCon;
		nChargeSum = nCredit + nOnline + nDir + nEtc + nChargeCompany;
		nChargeFinal = nFixDeposit - (nChargeSum + nTran);

		m_List.InsertItem(i, itoa(nRNo, buffer, 10));
		m_List.SetItemText(i, 1, sRName);
		m_List.SetItemText(i, 2, LF->GetMyNumberFormat(nCash));
		m_List.SetItemText(i, 3, LF->GetMyNumberFormat(nCredit));
		m_List.SetItemText(i, 4, LF->GetMyNumberFormat(nOnline));
		m_List.SetItemText(i, 5, LF->GetMyNumberFormat(nDir));
		m_List.SetItemText(i, 6, LF->GetMyNumberFormat(nChargeCompany));
		m_List.SetItemText(i, 7, LF->GetMyNumberFormat(nEtc));
		m_List.SetItemText(i, 8, LF->GetMyNumberFormat(nTran));
		m_List.SetItemText(i, 9, LF->RemoveZero(LF->GetMyNumberFormat(nFixDay)));
		m_List.SetItemText(i, 10, LF->GetMyNumberFormat(nFixDeposit));
		m_List.SetItemText(i, 11, LF->GetMyNumberFormat(nChargeSum + nTran));
		m_List.SetItemText(i, 12, LF->GetMyNumberFormat(nChargeFinal));
 		m_List.SetItemText(i, 13, GetSmsMent(nFixDeposit, nChargeSum + nTran, nChargeFinal));
		m_List.SetItemText(i, 14, LF->GetDashPhoneNumber(sHp));

		pRs.MoveNext(); 
	}
	
	m_List.Populate();
	FilterList();
}

CString CReportForm25::GetSmsMent(long nFixDeposit, long nChargeSum, long nChargeFinal)
{
	CString sTemp = "";

	if(nChargeFinal == 0)
		return "";
	else if(nChargeFinal > 0)
		sTemp.Format("[%d-%d ~ %d-%d] 지:%s 외:%s [%s] 입금바랍니다", m_tmFrom.GetMonth(), m_tmFrom.GetDay(), m_tmTo.GetMonth(), m_tmTo.GetDay(), LF->GetMyNumberFormat(nFixDeposit), LF->GetMyNumberFormat(nChargeSum), LF->GetMyNumberFormat(abs(nChargeFinal)));
	else
		sTemp.Format("[%d-%d ~ %d-%d] 지:%s 외:%s [%s] 입금예정입니다", m_tmFrom.GetMonth(), m_tmFrom.GetDay(), m_tmTo.GetMonth(), m_tmTo.GetDay(), LF->GetMyNumberFormat(nFixDeposit), LF->GetMyNumberFormat(nChargeSum), LF->GetMyNumberFormat(abs(nChargeFinal)));

	return sTemp;
}
void CReportForm25::OnCbnSelchangeDayCombo()
{
	FilterList();
}

void CReportForm25::FilterList()
{
	CString sSearch; m_edtSearch.GetWindowText(sSearch);
	long nSearchDay = m_cmbDay.GetCurSel();

	CXTPGridRecords *pRecords = m_List.GetRecords();
	
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString sRNo = m_List.GetItemText(pRecord, 0);
		CString sRName = m_List.GetItemText(pRecord, 1);

		BOOL bShow = FALSE;

		if(sRNo.Find(sSearch) >= 0 || sRName.Find(sSearch) >= 0)
		{
			bShow = TRUE;
		}

		if(bShow)
		{
			long nDay = atoi(m_List.GetItemText(pRecord, 8));

			if(nSearchDay == 0 || nSearchDay == nDay)
				bShow = TRUE;
			else
				bShow = FALSE;
		}

		pRecord->SetVisible(bShow);		
	}

	m_List.Populate();

}

void CReportForm25::OnEnChangeSearchEdit()
{
	FilterList();
}

void CReportForm25::OnBnClickedSendSmsBtn()
{
	long nCount = GetSendCount();

	if(nCount == 0)
	{
		MessageBox("전송 가능한 기사님이 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sTemp = "";
	sTemp.Format("%d명의 기사님에게 SMS를 전송 하시겠습니까?", nCount);

	if(MessageBox(sTemp, "확인", MB_OKCANCEL) != IDOK)
		return;
	
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	for(int i=0; i< pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		long nFinalCharge = atoi(m_List.GetItemText(pRecord, 12));
		CString sHp = m_List.GetItemText(pRecord, 14);
		CString sMsg = m_List.GetItemText(pRecord, 13);
		sHp.Replace("-", "");

		if(IsSendSmsOk(nFinalCharge, sHp))
		{
			if(FALSE == LF->SendSmsNew(m_ci.m_nCompanyCode, 777, sHp, m_ci.m_strOfficePhone, sMsg, "지입금", "", ""))
				break;
		}
	}
}

long CReportForm25::GetSendCount()
{
	long nCount = 0;
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	for(int i=0; i< pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		long nFinalCharge = atoi(m_List.GetItemText(pRecord, 12));
		CString sHp = m_List.GetItemText(pRecord, 14);
		sHp.Replace("-", "");
	
		if(IsSendSmsOk(nFinalCharge, sHp))
			nCount++;
	}

	return nCount;
}

BOOL CReportForm25::IsSendSmsOk(long nFinalCharge, CString sHp)
{
	if(nFinalCharge == 0) return FALSE;

	if(sHp.Left(2) != "01") return FALSE;
	if(sHp.GetLength() != 10 && sHp.GetLength() != 11) return FALSE;

	return TRUE;
}

void CReportForm25::OnViewExcel()
{
	if(!LF->POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 322, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}

void CReportForm25::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}
