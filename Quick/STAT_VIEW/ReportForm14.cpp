// ReportForm14.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm14.h"

// CReportForm14

IMPLEMENT_DYNCREATE(CReportForm14, CMyFormView)

CReportForm14::CReportForm14()
	: CMyFormView(CReportForm14::IDD)
{
}

CReportForm14::~CReportForm14()
{
	m_wndReport.SaveReportOrder("CReportForm14", "m_wndReport");
}

void CReportForm14::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_CREDIT_CHECK, m_CreditChk);
}

BEGIN_MESSAGE_MAP(CReportForm14, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)

	
END_MESSAGE_MAP()


// CReportForm14 진단입니다.

#ifdef _DEBUG
void CReportForm14::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm14::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm14 메시지 처리기입니다.

void CReportForm14::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_wndReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_wndReport.InsertColumn(1, "오더번호", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(2, "발주사", LVCFMT_RIGHT, 80);
	m_wndReport.InsertColumn(3, "발주지사", LVCFMT_RIGHT, 80);
	m_wndReport.InsertColumn(4, "접수시간", LVCFMT_RIGHT, 75);
	m_wndReport.InsertColumn(5, "상태", LVCFMT_RIGHT, 40);
	m_wndReport.InsertColumn(6, "공유차수", LVCFMT_RIGHT, 60);
	m_wndReport.InsertColumn(7, "기사소속회사",LVCFMT_RIGHT, 80);
	m_wndReport.InsertColumn(8, "사번",LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(9, "기사명",LVCFMT_RIGHT, 50);
	m_wndReport.InsertColumn(10, "기본",LVCFMT_LEFT, 85);
	m_wndReport.InsertColumn(11, "추가",LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(12, "할인",LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(13, "탁송",LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(14, "합계",LVCFMT_LEFT, 85);
	m_wndReport.InsertColumn(15, "결제",LVCFMT_RIGHT, 40);
	m_wndReport.InsertColumn(16, "입금액",LVCFMT_RIGHT, 70);
	m_wndReport.InsertColumn(17, "콜비",LVCFMT_RIGHT, 70);
	m_wndReport.InsertColumn(18, "처리비",LVCFMT_RIGHT, 70);

	m_wndReport.SetPaintManager(new CReportForm14PaintManager);
	m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndReport.GetPaintManager()->m_strNoItems = "";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(212, 208, 200));

	m_wndReport.Populate();

	m_wndReport.LoadReportOrder("CReportForm14", "m_wndReport");
}

void CReportForm14::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);

	m_map.clear();
	m_mapTake.clear();
	m_mapGive.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb,  "select_share_order_3");

	long nTake = 0;
	long nGive = 0;

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode5);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_CreditChk.GetCheck());
	
	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_SHARE *st = new ST_SHARE;

		st->nCurCompany = LF->GetCurBranchInfo()->nCompanyCode;

		pRs.GetFieldValue("nTNo", st->nTNo);
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("dt1", st->dt1);
		pRs.GetFieldValue("nState", st->nState);
		pRs.GetFieldValue("nShareCode1", st->nShareCode1);
		pRs.GetFieldValue("nShareCode2", st->nShareCode2);
		pRs.GetFieldValue("nShareCode3", st->nShareCode3);
		pRs.GetFieldValue("nShareCode4", st->nShareCode4);
		pRs.GetFieldValue("nShareCode5", st->nShareCode5);
		pRs.GetFieldValue("nRiderShareCode1", st->nRiderShareCode1);
		pRs.GetFieldValue("nRiderShareCode2", st->nRiderShareCode2);
		pRs.GetFieldValue("nRiderShareCode3", st->nRiderShareCode3);
		pRs.GetFieldValue("nRiderShareCode4", st->nRiderShareCode4);
		pRs.GetFieldValue("nRiderShareCode5", st->nRiderShareCode5);
		pRs.GetFieldValue("nRiderCompany", st->nRiderCompany);
		pRs.GetFieldValue("nRNo", st->nRNo);
		pRs.GetFieldValue("sRName", st->strRName);
		pRs.GetFieldValue("nChargeBasic", st->nChargeBasic);
		pRs.GetFieldValue("nChargeAdd", st->nChargeAdd);
		pRs.GetFieldValue("nChargeTrans", st->nChargeTrans);
		pRs.GetFieldValue("nChargeDis", st->nChargeDis);
		pRs.GetFieldValue("nChargeSum", st->nChargeSum);
		pRs.GetFieldValue("nPayType", st->nPayType);
		pRs.GetFieldValue("nDeposit", st->nDeposit);
		pRs.GetFieldValue("nRcpRate", st->nRcpRate);

		if(LF->GetCurBranchInfo()->nShareCode1 == st->nShareCode1)
		{
			st->nTakeDeposit = (st->nDeposit * ((st->nRcpRate * 5) / 100));
			st->nGiveDeposit = st->nDeposit - st->nTakeDeposit;
			m_mapTake[nTake++] = st;
		}
		else
		{
			st->nGiveDeposit = (st->nDeposit * ((st->nRcpRate * 5) / 100));
			st->nTakeDeposit = st->nDeposit - st->nGiveDeposit;
			m_mapGive[nGive++] = st;
		}

		pRs.MoveNext();
	} 

	m_wndReport.DeleteAllItems();  
	PrintList(&m_mapTake, TAKEROW, "넘긴콜 합계 : "); 
	PrintList(&m_mapGive, GIVEROW, "받은콜 합계 : ");

	if(m_mapTake.size() == 0 && m_mapGive.size() == 0)
		m_wndReport.Populate();
}

void CReportForm14::PrintList(SHARE_MAP *pMap, long nStartIndex, CString sTotal)
{ 
	long nRecordCount = m_wndReport.GetRecords()->GetCount();
	long nItem = nRecordCount;
	char buffer[10];
	long nCompany = 0;

	SHARE_MAP::iterator pos;

	long nChargeBasicSum, nChargeAddSum, nChargeDisSum, nChargeTransSum, nChargeSumSum, nDeposit, nTakeDeposit, nGiveDeposit;
	nChargeBasicSum = nChargeAddSum = nChargeDisSum = nChargeTransSum = nChargeSumSum = nDeposit = nTakeDeposit = nGiveDeposit = 0;

	long nChargeBasicSumS, nChargeAddSumS, nChargeDisSumS, nChargeTransSumS, nChargeSumSumS, nDepositS, nTakeDepositS, nGiveDepositS;
	nChargeBasicSumS = nChargeAddSumS = nChargeDisSumS = nChargeTransSumS = nChargeSumSumS = nDepositS = nTakeDepositS = nGiveDepositS = 0;

	long nIndex = 1;

	for(pos = pMap->begin(); pos != pMap->end(); pos++)
	{
		ST_SHARE *st = pos->second;

		if(nItem == nRecordCount)
			nCompany = st->nCompany;

		nChargeBasicSumS += st->nChargeBasic; 
		nChargeAddSumS += st->nChargeAdd;
		nChargeDisSumS += st->nChargeDis;
		nChargeTransSumS += st->nChargeTrans;
		nChargeSumSumS += st->nChargeSum;
		nDepositS += st->nDeposit;
		nTakeDepositS += st->nTakeDeposit;
		nGiveDepositS += st->nGiveDeposit;
 
		if(m_ci.GetShareCode1(nCompany) != m_ci.GetShareCode1(st->nCompany)) // 끝남
		{
			m_wndReport.InsertItem(nItem, "");
			m_wndReport.SetItemText(nItem, 1, "합계 : ");
			m_wndReport.SetItemText(nItem, 2, m_ci.GetName(m_ci.GetShareCode1(nCompany)));
			m_wndReport.SetItemText(nItem, 3, "");
			m_wndReport.SetItemText(nItem, 4, "");
			m_wndReport.SetItemText(nItem, 5, "");
			m_wndReport.SetItemText(nItem, 6, "");
			m_wndReport.SetItemText(nItem, 7, "");
			m_wndReport.SetItemText(nItem, 8, "");
			m_wndReport.SetItemText(nItem, 9, "");

			//m_wndReport.InsertColumn(10, "추가",LVCFMT_LEFT, 60);
			//m_wndReport.InsertColumn(11, "할인",LVCFMT_LEFT, 60);
			//m_wndReport.InsertColumn(12, "탁송",LVCFMT_LEFT, 60);
			//m_wndReport.InsertColumn(13, "합계",LVCFMT_LEFT, 60);
			//m_wndReport.InsertColumn(14, "결제",LVCFMT_RIGHT, 50);

			m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeBasicSum) + "원");
			m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(nChargeAddSum) + "원");
			m_wndReport.SetItemText(nItem, 12, LF->GetMyNumberFormat(nChargeDisSum) + "원");
			m_wndReport.SetItemText(nItem, 13, LF->GetMyNumberFormat(nChargeTransSum) + "원");
			m_wndReport.SetItemText(nItem, 14, LF->GetMyNumberFormat(nChargeSumSum) + "원");
			m_wndReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nDeposit) + "원");
			m_wndReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nTakeDeposit) + "원");
			m_wndReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nGiveDeposit) + "원");

			m_wndReport.SetItemLong(nItem, nStartIndex + 1);
			nItem++;
			nIndex = 1;

			nChargeBasicSum = nChargeAddSum = nChargeTransSum = nChargeDisSum = nChargeSumSum = 0;
			nDeposit = nTakeDeposit = nGiveDeposit = 0;
		}

		nChargeBasicSum += st->nChargeBasic;
		nChargeAddSum += st->nChargeAdd;
		nChargeDisSum += st->nChargeDis;
		nChargeTransSum += st->nChargeTrans;
		nChargeSumSum += st->nChargeSum;
		nDeposit += st->nDeposit;
		nTakeDeposit += st->nTakeDeposit;
		nGiveDeposit += st->nGiveDeposit;

		m_wndReport.InsertItem(nItem, LF->GetStringFromLong(nIndex++));
		m_wndReport.SetItemText(nItem, 1, itoa(st->nTNo, buffer, 10));

		if((m_ci.GetShareCode1(nCompany) == m_ci.GetShareCode1(st->nCompany)) &&
			(nItem != nRecordCount))
			m_wndReport.SetItemText(nItem, 2, "");
		else
			m_wndReport.SetItemText(nItem, 2, m_ci.GetName(st->nCompany));

		m_wndReport.SetItemText(nItem, 3, m_ci.GetBranchName(st->nCompany));
		m_wndReport.SetItemText(nItem, 4, st->dt1.Format("%m-%d %H:%M"));
		m_wndReport.SetItemText(nItem, 5, LF->GetStateString(st->nState));

		CString strFormat = "";
		if(st->nShareCode2 == st->nRiderShareCode2 && st->nShareCode2 != 0)
			strFormat += "②"; 
		if(st->nShareCode3 == st->nRiderShareCode3 && st->nShareCode3 != 0)
			strFormat += "③";
		if(st->nShareCode4 == st->nRiderShareCode4 && st->nShareCode4 != 0)
			strFormat += "④";
		if(st->nShareCode5 == st->nRiderShareCode5 && st->nShareCode5 != 0)
			strFormat += "⑤";

		m_wndReport.SetItemText(nItem, 6, strFormat);
		m_wndReport.SetItemText(nItem, 7, m_ci.GetBranchName(st->nRiderCompany));
		m_wndReport.SetItemText(nItem, 8, itoa(st->nRNo, buffer, 10));
		m_wndReport.SetItemText(nItem, 9, st->strRName);
		m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(st->nChargeBasic));
		m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(st->nChargeAdd));
		m_wndReport.SetItemText(nItem, 12, LF->GetMyNumberFormat(st->nChargeDis));
		m_wndReport.SetItemText(nItem, 13, LF->GetMyNumberFormat(st->nChargeTrans));
		m_wndReport.SetItemText(nItem, 14, LF->GetMyNumberFormat(st->nChargeSum));
		m_wndReport.SetItemText(nItem, 15, LF->GetPayTypeFromLong(st->nPayType));
		m_wndReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(st->nDeposit));
		m_wndReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(st->nTakeDeposit));
		m_wndReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(st->nGiveDeposit));

		m_wndReport.SetItemLong(nItem, nStartIndex);

		nCompany = st->nCompany;
		nItem++;
	}

	if(pMap->size() < 1)
		return;

	m_wndReport.InsertItem(nItem, "");
	m_wndReport.SetItemText(nItem, 1, "합계 : ");
	m_wndReport.SetItemText(nItem, 2, m_ci.GetName(m_ci.GetShareCode1(nCompany)));
	m_wndReport.SetItemText(nItem, 3, "");
	m_wndReport.SetItemText(nItem, 4, "");
	m_wndReport.SetItemText(nItem, 5, "");
	m_wndReport.SetItemText(nItem, 6, "");
	m_wndReport.SetItemText(nItem, 7, "");
	m_wndReport.SetItemText(nItem, 8, "");
	m_wndReport.SetItemText(nItem, 9, "");

	m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeBasicSum) + "원");
	m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(nChargeAddSum) + "원");
	m_wndReport.SetItemText(nItem, 12, LF->GetMyNumberFormat(nChargeDisSum) + "원");
	m_wndReport.SetItemText(nItem, 13, LF->GetMyNumberFormat(nChargeTransSum) + "원");
	m_wndReport.SetItemText(nItem, 14, LF->GetMyNumberFormat(nChargeSumSum) + "원");

	m_wndReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nDeposit) + "원");
	m_wndReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nTakeDeposit) + "원");
	m_wndReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nGiveDeposit) + "원");

	m_wndReport.SetItemLong(nItem, nStartIndex + 1); 
	nItem++;

	m_wndReport.InsertItem(nItem, "");
	m_wndReport.SetItemLong(nItem, nStartIndex);

	nItem++;

	m_wndReport.InsertItem(nItem, "");
	m_wndReport.SetItemText(nItem, 1, sTotal);
	m_wndReport.SetItemText(nItem, 2, "");
	m_wndReport.SetItemText(nItem, 3, "");
	m_wndReport.SetItemText(nItem, 4, "");
	m_wndReport.SetItemText(nItem, 5, "");
	m_wndReport.SetItemText(nItem, 6, "");
	m_wndReport.SetItemText(nItem, 7, "");
	m_wndReport.SetItemText(nItem, 8, "");
	m_wndReport.SetItemText(nItem, 9, "");
 
	m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeBasicSumS) + "원");
	m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(nChargeAddSumS) + "원");
	m_wndReport.SetItemText(nItem, 12, LF->GetMyNumberFormat(nChargeDisSumS) + "원");
	m_wndReport.SetItemText(nItem, 13, LF->GetMyNumberFormat(nChargeTransSumS) + "원");
	m_wndReport.SetItemText(nItem, 14, LF->GetMyNumberFormat(nChargeSumSumS) + "원");

	m_wndReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nDepositS) + "원");
	m_wndReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nTakeDepositS) + "원");
	m_wndReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nGiveDepositS) + "원");

	m_wndReport.SetItemLong(nItem, nStartIndex + 2);

	nChargeBasicSumS = nChargeAddSumS = nChargeDisSumS = nChargeTransSumS = nChargeSumSumS = 0;
	nDepositS = nTakeDepositS = nGiveDepositS = 0;

	m_wndReport.Populate();

}

void CReportForm14::OnBnClickedRefreshBtn()
{
	RefreshList();
}
void CReportForm14::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

void CReportForm14::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm14::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 313, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}