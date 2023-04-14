// ReportForm13.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm13.h"

// CReportForm13

IMPLEMENT_DYNCREATE(CReportForm13, CMyFormView)

CReportForm13::CReportForm13()
	: CMyFormView(CReportForm13::IDD)
	, m_dtFrom(COleDateTime::GetCurrentTime())
	, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CReportForm13::~CReportForm13()
{
	m_wndReport.SaveReportOrder("CReportForm13", "m_wndReport");
}

void CReportForm13::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}

BEGIN_MESSAGE_MAP(CReportForm13, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)

	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)

	
END_MESSAGE_MAP()


// CReportForm13 진단입니다.

#ifdef _DEBUG
void CReportForm13::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm13::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm13 메시지 처리기입니다.

void CReportForm13::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm13::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_wndReport.InsertColumn(0, "순번", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(1, "오더번호", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(2, "발주사", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(3, "접수시간", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(4, "출발지", LVCFMT_LEFT, 110);
	m_wndReport.InsertColumn(5, "도착지", LVCFMT_LEFT, 110);
	m_wndReport.InsertColumn(6, "상태", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(7, "요금타입", LVCFMT_LEFT, 60); //요금타입
	m_wndReport.InsertColumn(8, "사번", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(9, "기사명", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(10, "기사소속회사", LVCFMT_LEFT, 80);
	//m_wndReport.InsertColumn(10, "타입", LVCFMT_LEFT, 100); //자사, 지사(지사간이체), 타사
	m_wndReport.InsertColumn(11, "탁송", LVCFMT_LEFT, 70); //자사, 지사(지사간이체), 타사
	m_wndReport.InsertColumn(12, "금액", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(13, "선입금", LVCFMT_LEFT, 70); //입금 완료 혹은 미입금 혹은 청구요청

	m_wndReport.Populate();

	m_wndReport.LoadReportOrder("CReportForm13", "m_wndReport");
}

void CReportForm13::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(true);

	m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deferred_order_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[20];
	
	for(int i=0; i<pRs.GetRecordCount(); i++) 
	{ 
		
		CREDIT_STRUCT *st = new CREDIT_STRUCT; 

		pRs.GetFieldValue("nTNo", st->nTNo);	
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("sOName", st->sOName);
		pRs.GetFieldValue("sSName", st->sSName);
		pRs.GetFieldValue("sDName", st->sDName);
		pRs.GetFieldValue("dt1", st->dt1);
		pRs.GetFieldValue("nPayType", st->nPayType);
		pRs.GetFieldValue("nRiderCompany", st->nRiderCompany);
		pRs.GetFieldValue("nRNo", st->nRNo);
		pRs.GetFieldValue("sRName", st->sRName);
		pRs.GetFieldValue("nChargeSum", st->nChargeSum);
		pRs.GetFieldValue("nChargeTrans", st->nChargeTrans);
		pRs.GetFieldValue("nState", st->nState);
		pRs.GetFieldValue("bGiveChargeToRider", st->bGiveChargeToRider);

		
		m_wndReport.InsertItem(i, itoa(i, buffer, 10));
		m_wndReport.SetItemText(i, 1, itoa(st->nTNo, buffer, 10));
		m_wndReport.SetItemText(i, 2, m_ci.GetBranchName(st->nCompany));
		m_wndReport.SetItemText(i, 3, st->dt1.Format("%m/%d %H:%M"));
		m_wndReport.SetItemText(i, 4, st->sSName);
		m_wndReport.SetItemText(i, 5, st->sDName);
		m_wndReport.SetItemText(i, 6, ::GetStateString(st->nState));
		m_wndReport.SetItemText(i, 7, ::GetPayTypeFromLong(st->nPayType));
		m_wndReport.SetItemText(i, 8, itoa(st->nRNo, buffer, 10));
		m_wndReport.SetItemText(i, 9, st->sRName);
		m_wndReport.SetItemText(i, 10, m_ci.GetBranchName(st->nRiderCompany));
		//m_wndReport.SetItemText(i, 10, GetOrderShareType(st) + "/" + GetRiderShareType(st));
		m_wndReport.SetItemText(i, 11, ::GetMyNumberFormat(st->nChargeTrans));
		m_wndReport.SetItemText(i, 12, ::GetMyNumberFormat(st->nChargeSum));
		m_wndReport.SetItemText(i, 13, st->bGiveChargeToRider == TRUE ? "입금완료" : "선입금");
		//m_wndReport.SetItemText(i, 12, GetTransferState(GetOrderShareType(st), GetRiderShareType(st), st->bGiveChargeToRider));

		m_wndReport.SetItemData(i, (DWORD_PTR)st);
		
		pRs.MoveNext();
	}

	m_wndReport.Populate();
   
}
 
CString CReportForm13::GetTransferState(CString sOrder, CString sRider, BOOL  bSuccess)
{
	if(bSuccess == TRUE)
		return "입금완료";

	if(sOrder == "자사콜" && sRider == "자사기사")
		return "선입금";
	else if(sOrder == "자사콜" && sRider == "지사기사")
		return "이체(선입금)";
	else if(sOrder == "자사콜" && sRider == "타기사")
		return "이체(선입금)";
	else if(sOrder == "지사콜" && sRider == "자사기사")
		return "청구";
	else if(sOrder == "지사콜" && sRider == "지사기사")
		return "";
	else if(sOrder == "지사콜" && sRider == "타기사")
		return "";
	else if(sOrder == "타사콜" && sRider == "자사기사")
		return "청구";
	else if(sOrder == "타사콜" && sRider == "지사기사")
		return "";
	else if(sOrder == "타사콜" && sRider == "타기사") //나올수 없는 경우
		return "";
	else 
		return "";


} 

void CReportForm13::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol != 13) return;

	CREDIT_STRUCT *st = (CREDIT_STRUCT*)m_wndReport.GetItemData(nRow);

	if(st->bGiveChargeToRider)
	{
		MessageBox("이미 입금처리 되었습니다", "확인" ,MB_ICONINFORMATION);
		return;
	}

	CString sMsg;
	sMsg.Format("사번 %d번기사님에게 \r\n %d원을 선입금 충전을 하시겠습니까?", st->nRNo, st->nChargeSum + st->nChargeTrans);

	if(MessageBox(sMsg, "확인", MB_YESNO) == IDYES)
	{
		if(InsertCharge(st->nChargeSum + st->nChargeTrans, st->nTNo, st->nRiderCompany, st->nRNo, st->sRName))
		{
			CMkCommand pCmd(m_pMkDb, "update_credit_state_for_give_to_rider");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), st->nTNo);

			if(pCmd.Execute())
			{
				st->bGiveChargeToRider = 1;
				m_wndReport.SetItemText(nRow, 13, "입금완료");
			}

		}
	}
}



CString CReportForm13::GetOrderShareType(CREDIT_STRUCT *st)
{
	CString sReturn = "";
 
	if(m_ci.GetShareCode1(m_ci.m_nCompanyCode) == m_ci.GetShareCode1(st->nCompany)) // 자사콜 OR 지사콜
	{
		if((m_ci.IsUseBranchShareReport(st->nCompany) == TRUE) && 
			(m_ci.m_nCompanyCode != st->nCompany)) // 지사콜
		{
            sReturn = "지사콜";
		}
		else
		{
			sReturn = "자사콜";
		}
	}
	else
		sReturn = "타사콜";

	return sReturn;
}

CString CReportForm13::GetRiderShareType(CREDIT_STRUCT *st)
{
	CString sReturn = "";

	if(m_ci.GetShareCode1(m_ci.m_nCompanyCode) == m_ci.GetShareCode1(st->nRiderCompany)) // 자사기사 OR 지사기사
	{
		BOOL a= m_ci.IsUseBranchShareReport(st->nRiderCompany);
		if((m_ci.IsUseBranchShareReport(st->nRiderCompany) == TRUE) && 
			(m_ci.m_nCompanyCode != st->nRiderCompany)) // 지사기사
		{
			sReturn = "지사기사";
		}
		else
		{
			sReturn = "자사기사";
		}
	}
	else
		sReturn = "타기사";

	return sReturn;
}


BOOL CReportForm13::InsertCharge(long nSendMoney, long nTNo, long nRiderCompay, long nRNo, CString sRName)
{
	CString sEtc;
	sEtc.Format("신용오더 선입금충전 오더번호(%d)", nTNo);

	long nReturn;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_balance_today");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRiderCompay);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
	pCmd.AddParameter(typeString, typeInput, sRName.GetLength(), sRName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 13); // 신용정산


	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSendMoney);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc); //사유

	if(!pRs.Execute(&pCmd)) return FALSE;

	pPar->GetValue(nReturn);

	return TRUE;
}

void CReportForm13::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

void CReportForm13::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm13::OnViewExcel()
{
	if(!POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 312, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}