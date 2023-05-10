// RiderReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm7.h"
#include "WebPrintDlg.h"
#include "RiderReportOrderDlg.h"
#include "RiderReportDlg.h"
#include "MainFrm.h"
#include "MakeFixedDepositDlg.h"
#include "HalfInsertFixedDepositDlg.h"


#define MAX_ETC_COUNT 20
// CIncomeForm7 대화 상자입니다.

IMPLEMENT_DYNCREATE(CIncomeForm7, CMyFormView)
CIncomeForm7::CIncomeForm7()
: CMyFormView(CIncomeForm7::IDD)
{
	m_pRiderReportDlg  = NULL;
}

CIncomeForm7::~CIncomeForm7()
{
	if(m_pRiderReportDlg == NULL)
	{
		delete m_pRiderReportDlg;
		m_pRiderReportDlg = NULL;
	}
}

void CIncomeForm7::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_REPORT, m_lstRider);
	DDX_Control(pDX, IDC_DEPOSIT_REPORT, m_lstDeposit);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdt);
}

BEGIN_MESSAGE_MAP(CIncomeForm7, CMyFormView)
	ON_NOTIFY(NM_CLICK, IDC_RIDER_REPORT, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_DEPOSIT_REPORT, OnDepositReportItemlClick)
	ON_NOTIFY(NM_RCLICK, IDC_DEPOSIT_REPORT, OnDepositReportItemlRClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MAKE_FIXED_DEPOSIT, OnMakeFixedDeposit)
	ON_COMMAND(ID_HALF_INSERT_FIXED_DEPOSIT, OnHalfInsertFixedDeposit)
	ON_COMMAND(ID_DELETE_FIXED_DEPOSIT, OnDeleteFixedDeposit)
	ON_COMMAND(ID_NOT_REPORT, OnNotReport)
	ON_COMMAND(ID_REPORT_COMPLETE, OnReportComplete)
	ON_COMMAND(ID_INCOME_COMPLETE, OnIncomeComplete)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)

END_MESSAGE_MAP()

void CIncomeForm7::OnMakeFixedDeposit()
{
	long index = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	ST_RIDER_DEPOSIT_INFO *st = (ST_RIDER_DEPOSIT_INFO*)m_lstDeposit.GetItemData(index);

	CMakeFixedDepositDlg dlg;
	dlg.m_nRiderCompany = st->nRiderCompany;
	dlg.m_nRNo = st->nRNo;
	dlg.m_strRName = st->strRName;

	if(dlg.DoModal() == IDOK)
		RefreshDepositList();

}

void CIncomeForm7::OnHalfInsertFixedDeposit()
{
	long index = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{
		MessageBox("부분 입금 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	CHalfInsertFixedDepositDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		ST_RIDER_DEPOSIT_INFO *st = (ST_RIDER_DEPOSIT_INFO*)m_lstDeposit.GetItemData(index);

		if(dlg.m_nCharge > st->nFixedDeposit)
		{
			if(MessageBox("부분 수정 할 금액이 지입금보다 큽니다\r\n   진행하시겠습니까", "확인", MB_OKCANCEL) != IDOK)
				return;
		}

		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), st->nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nCharge);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshDepositList();

	}
}

void CIncomeForm7::OnDeleteFixedDeposit()
{
	long index = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) 
	{
		MessageBox("삭제 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	ST_RIDER_DEPOSIT_INFO * st = (ST_RIDER_DEPOSIT_INFO*)m_lstDeposit.GetItemData(index);

	CString strDate = st->strTakeDate;
	
	CString strTemp;
	strTemp.Format("지입일 : %s, 금액 : %d원을 삭제 하시겠습니까?", strDate.Right(6), st->nRiderCompany);

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) == IDOK)
	{
		long nID = (long)m_lstDeposit.GetItemLong(index);

		CMkCommand pCmd(m_pMkDb, "delete_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshDepositList();
	}
}

void CIncomeForm7::OnNotReport()
{
	long nIndex = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == -1) return;

	CString strState = m_lstDeposit.GetItemText(nIndex, 1);

	if(strState == "미정산")
		return;
	else if(strState == "정산완료" || strState == "입금완료")
	{
		long nID = (long)m_lstDeposit.GetItemLong(nIndex);

		if(::ChangeFixedDepositState(nID, 0))
			RefreshDepositList();
	}
}

void CIncomeForm7::OnReportComplete()
{
	long nIndex = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == -1) return;

	CString strState = m_lstDeposit.GetItemText(nIndex, 1);

	if(strState == "미정산")
	{
		MessageBox("정산창을 이용하세요!", "확인", MB_ICONINFORMATION);
		return; 
	}
	else if(strState == "입금완료")
	{
		long nID = (long)m_lstDeposit.GetItemLong(nIndex);

		if(::ChangeFixedDepositState(nID, 1))
			RefreshDepositList();
	}
}

void CIncomeForm7::OnIncomeComplete()
{
	long nIndex = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == -1) return;

	CString strState = m_lstDeposit.GetItemText(nIndex, 1);

	if(strState == "미정산")
	{
		MessageBox("정산먼저 완료하세요", "확인", MB_ICONINFORMATION);
	}
	else if(strState == "정산완료")
	{
		long nID = (long)m_lstDeposit.GetItemLong(nIndex);
		
		if(::ChangeFixedDepositState(nID, 2))
			RefreshDepositList();
	}
	else if(strState == "입금완료")
	{
		return;
	}
}

void CIncomeForm7::OnDepositReportItemlClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nIndex = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex == -1) return;

	OpenDepositDlg();
}

void CIncomeForm7::OnDepositReportItemlRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nIndex = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex == -1) return;

	CPoint pt;
	::GetCursorPos(&pt);

	OnContextMenu(NULL, pt);
}

void CIncomeForm7::OpenDepositDlg()
{
	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	long index = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);
	if(index == -1) return;

	if(m_pRiderReportDlg != NULL) 
	{ 
		m_pRiderReportDlg->ShowWindow(SW_HIDE);
		delete m_pRiderReportDlg;
		m_pRiderReportDlg = NULL;
	}

	if(m_pRiderReportDlg == NULL)  
	{ 
		m_pRiderReportDlg = new CRiderReportDlg(this);

		ST_RIDER_DEPOSIT_INFO *st = (ST_RIDER_DEPOSIT_INFO*)m_lstDeposit.GetItemData(index);

		long nID = st->nID;
		CString sStartDate = "20" + st->strStartDate;
		CString sEndDate = "20" + st->strEndDate;
		long nFixedDeposit = st->nFixedDeposit;

		CString sState = m_lstDeposit.GetItemText(index, 1);

		m_pRiderReportDlg->m_nID = st->nID;
		m_pRiderReportDlg->m_strRName = st->strRName;

		if(st->nState == 1 || st->nState == 2)
			m_pRiderReportDlg->m_bComplete = TRUE;

		if(sStartDate == "20")
		{
			COleDateTime dtCur = COleDateTime::GetCurrentTime();
			m_pRiderReportDlg->m_dtFrom = COleDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 0, 0, 0);
			m_pRiderReportDlg->m_dtTo = COleDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 23, 59, 59);
		}
		else
		{
			m_pRiderReportDlg->m_dtFrom = COleDateTime(_ttoi(sStartDate.Left(4)), _ttoi(sStartDate.Mid(5,2)), _ttoi(sStartDate.Right(2)), 0, 0, 0);
			m_pRiderReportDlg->m_dtTo = COleDateTime(_ttoi(sEndDate.Left(4)), _ttoi(sEndDate.Mid(5,2)), _ttoi(sEndDate.Right(2)), 23, 59, 59);
		}

		m_pRiderReportDlg->m_nRiderCompany = st->nRiderCompany;
		m_pRiderReportDlg->m_nRNo = st->nRNo;
		m_pRiderReportDlg->m_nFixedDepositCharge = st->nFixedDeposit;

		m_pRiderReportDlg->Create(IDD_RIDER_REPORT_DLG);

		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

		CRect rcRRDlg, mainRc, reportRc;
		m_pRiderReportDlg->GetWindowRect(rcRRDlg);
		long nWidth = rcRRDlg.Width();
		long nHeight = rcRRDlg.Height();


		m_pRiderReportDlg->MoveWindow(-2000, -2000, -2000, -2000); // 안보이는 곳으로
		m_pRiderReportDlg->ShowWindow(SW_SHOW);
		SetCrystal(m_pRiderReportDlg, ZERO);

		pFrame->GetWindowRect(mainRc);
		m_lstDeposit.GetWindowRect(reportRc);

		rcRRDlg.left = reportRc.right + 1;
		rcRRDlg.right = rcRRDlg.left + nWidth;
		rcRRDlg.top = reportRc.top;
		rcRRDlg.bottom = rcRRDlg.top + nHeight;
		
		m_pRiderReportDlg->MoveWindow(rcRRDlg);

		SetTimer(100, 100, NULL);
	}
}

void CIncomeForm7::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
	
	RefreshDepositList();	
}

void CIncomeForm7::DeleteDepositReport()
{
	long nCount = m_lstDeposit.GetItemCount();
	for(int i=0; i<nCount; i++)
	{
		ST_RIDER_DEPOSIT_INFO * st = (ST_RIDER_DEPOSIT_INFO*)m_lstDeposit.GetItemData(i);
		delete st;
	}

	m_lstDeposit.DeleteAllItems();
	m_lstDeposit.Populate();
}


void CIncomeForm7::RefreshDepositList()
{
	DeleteDepositReport();

	long nIndex = m_lstRider.GetNextItem(-1, LVNI_SELECTED);
	if(nIndex == -1) return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_fixeddeposit_log");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_lstRider.GetItemLong(nIndex));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(m_lstRider.GetItemText(nIndex, 0)));

	CString sTakeDate;
	
	COleDateTime dtCreditOrderStart, dtCreditOrderEnd;

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_DEPOSIT_INFO *st = new ST_RIDER_DEPOSIT_INFO;

		pRs.GetFieldValue("sTakeDate", st->strTakeDate);
		pRs.GetFieldValue("nState", st->nState);
		pRs.GetFieldValue("nID", st->nID);
		pRs.GetFieldValue("dtCreditOrderStart", dtCreditOrderStart);
		pRs.GetFieldValue("dtCreditOrderEnd", dtCreditOrderEnd);
		pRs.GetFieldValue("sRName", st->strRName);
		pRs.GetFieldValue("nFixedDeposit", st->nFixedDeposit);
		pRs.GetFieldValue("nCompany", st->nRiderCompany);
		pRs.GetFieldValue("nRNo", st->nRNo);

		st->strStartDate = dtCreditOrderStart.Format("%y-%m-%d");
		st->strEndDate = dtCreditOrderEnd.Format("%y-%m-%d");

		m_lstDeposit.InsertItem(i, st->strTakeDate, 0, 0);

		if(st->nState == 0)
			m_lstDeposit.SetItemText(i, 1, "미정산");
		else if(st->nState == 1)
			m_lstDeposit.SetItemText(i, 1, "정산완료");
		else if(st->nState == 2)
			m_lstDeposit.SetItemText(i, 1, "입금완료");

		m_lstDeposit.SetItemData(i, DWORD(st));
		m_lstDeposit.SetItemLong(i, st->nID);

		pRs.MoveNext();
	}

	m_lstDeposit.Populate();
}

void CIncomeForm7::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstRider.InsertColumn(0, "사번", LVCFMT_LEFT, 40);
	m_lstRider.InsertColumn(1, "이름", LVCFMT_LEFT, 70);

	m_lstDeposit.InsertColumn(0, "지입일", LVCFMT_LEFT, 60);
	m_lstDeposit.InsertColumn(1, "상태", LVCFMT_LEFT, 60);

	m_lstRider.Populate();
	m_lstDeposit.Populate();

	SetResize(IDC_RIDER_REPORT, sizingBottom);
	SetResize(IDC_DEPOSIT_REPORT, sizingBottom);
}

void CIncomeForm7::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CIncomeForm7::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstRider.DeleteAllItems();

	long lCode, nRNo;
	CString sName, sID, sHp;
	char buffer[20];

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_deposit_rider");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
 
    if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("nMNo", nRNo);
		pRs.GetFieldValue("sName", sName);

		m_lstRider.InsertItem(i, itoa(nRNo, buffer, 10), -1, 0);
		m_lstRider.SetItemText(i, 1, sName);
		m_lstRider.SetItemLong(i, lCode);

		pRs.MoveNext();
	}

	m_lstRider.Populate();
}

void CIncomeForm7::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 100)
	{
		if(m_pRiderReportDlg != NULL)
		{
			static long nCrystal = 100;
			::SetCrystal(m_pRiderReportDlg, nCrystal);

			nCrystal += 20;

            if(nCrystal >= 250)
			{
				nCrystal = 100;
				KillTimer(100);
			}
		}
	}
	

	CMyFormView::OnTimer(nIDEvent);
}

void CIncomeForm7::OnEnChangeSearchEdit()
{
	CString sSearchData; m_SearchEdt.GetWindowText(sSearchData);

	CXTPGridRows *pRows = m_lstRider.GetRows();
	CXTPGridRecords *pRecords = m_lstRider.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CString sCompany, sDepart, sName, sUserID, sTel1, sDong, sLocation;

	for(int i=0; i<m_lstRider.GetRecords()->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString sRNo = ((CXTPGridRecordItemText*)m_lstRider.GetRecords()->GetAt(i)->GetItem(0))->GetCaption(pColumn);
		CString sRName = ((CXTPGridRecordItemText*)m_lstRider.GetRecords()->GetAt(i)->GetItem(1))->GetCaption(pColumn);


		if((sRNo.Find(sSearchData) >= 0) ||
			(sRName.Find(sSearchData) >= 0))
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstRider.Populate();	
}

void CIncomeForm7::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if(!POWER_CHECK(7070, "지입금관련", TRUE))
		return;

	long index = m_lstDeposit.GetNextItem(-1, LVNI_SELECTED);
	if(index == -1) return;

	CRect rect = NULL;
	m_lstDeposit.GetWindowRect(&rect);
	
	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(7);

		pRMenu->EnableMenuItem(ID_HALF_INSERT_FIXED_DEPOSIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->EnableMenuItem(ID_EXCEL,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}

}

void CIncomeForm7::OnViewExcel()
{
	//if(!POWER_CHECK(7900, "엑셀변환", TRUE))
	//	return;

	//AddSecurityLog(m_ci.m_nCompanyCode, 504, m_wndReport.GetItemCount());  
	//CMyExcel::ToExcel(&m_wndReport);
}