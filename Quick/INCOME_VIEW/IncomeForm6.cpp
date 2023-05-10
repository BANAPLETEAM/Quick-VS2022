// IncomeForm6.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm6.h"

#include "MakeFixedDepositDlg.h"
#include "HalfInsertFixedDepositDlg.h"
#include "RiderReportDlg.h"
//#include "RiderDepositInfoDlg.h"
// CIncomeForm6

IMPLEMENT_DYNCREATE(CIncomeForm6, CMyFormView)

CIncomeForm6::CIncomeForm6()
	: CMyFormView(CIncomeForm6::IDD)
{
}

CIncomeForm6::~CIncomeForm6()
{
	m_wndReport.SaveReportOrder("CIncomeForm6", "m_wndReport");
}

void CIncomeForm6::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_RNO_EDIT, m_RNoEdit);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
}

BEGIN_MESSAGE_MAP(CIncomeForm6, CMyFormView)
	ON_COMMAND(ID_MAKE_FIXED_DEPOSIT, OnMakeFixedDeposit)
	ON_COMMAND(ID_HALF_INSERT_FIXED_DEPOSIT, OnHalfInsertFixedDeposit)
	ON_COMMAND(ID_DELETE_FIXED_DEPOSIT, OnDeleteFixedDeposit)
	ON_COMMAND(ID_NOT_REPORT, OnNotReport)
	ON_COMMAND(ID_REPORT_COMPLETE, OnReportComplete)
	ON_COMMAND(ID_INCOME_COMPLETE, OnIncomeComplete)
	ON_COMMAND(ID_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnClickList)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnDblClickList)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_RNO_EDIT, OnEnChangeRnoEdit)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, OnCbnSelchangeStateCombo)
END_MESSAGE_MAP()


void CIncomeForm6::OnDblClickList(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	int nItem = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

    if(nItem >= 0) 
	{ 
		long nID = (long)m_wndReport.GetItemData(nItem);
		CString strStartDate = "20" + CString(m_wndReport.GetItemText(nItem, 7));
		CString strEndDate = "20" + CString(m_wndReport.GetItemText(nItem, 8));
		CString strFixedDeposit = m_wndReport.GetItemText(nItem, 5);
        strFixedDeposit.Replace(",", "");
		long nFixedDeposit = _ttoi(strFixedDeposit);

		CString strName = m_wndReport.GetItemText(nItem, 1);
		CString strState = m_wndReport.GetItemText(nItem, 9);

		long nRiderCompany = m_wndReport.GetItemLong(nItem);
		long nRNo = _ttoi(m_wndReport.GetItemText(nItem, 0));

		CRiderReportDlg dlg;
		dlg.m_nID = nID;
		dlg.m_strRName = strName;

		if(strState == "정산완료" || strState == "입금완료")
			dlg.m_bComplete = TRUE;

		if(strStartDate == "20")
		{
			dlg.m_dtFrom = COleDateTime::GetCurrentTime();
			dlg.m_dtTo = COleDateTime::GetCurrentTime();
		}
		else
		{
			dlg.m_dtFrom = COleDateTime(_ttoi(strStartDate.Left(4)), _ttoi(strStartDate.Mid(5,2)), _ttoi(strStartDate.Right(2)), 0, 0, 0);
			dlg.m_dtTo = COleDateTime(_ttoi(strEndDate.Left(4)), _ttoi(strEndDate.Mid(5,2)), _ttoi(strEndDate.Right(2)), 23, 59, 59);
		}

		dlg.m_bAbleMove = TRUE;
		dlg.m_nRiderCompany = nRiderCompany;
		dlg.m_nRNo = nRNo;
		dlg.m_nFixedDepositCharge = nFixedDeposit;

		if(dlg.DoModal() == IDOK)
			RefreshList();	
	}
}

void CIncomeForm6::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{	
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;
}


#ifdef _DEBUG
void CIncomeForm6::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CIncomeForm6::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CIncomeForm6 메시지 처리기입니다.

void CIncomeForm6::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CIncomeForm6::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	m_wndReport.InsertColumn(0, "사번", LVCFMT_RIGHT, 40);
	m_wndReport.InsertColumn(1, "기사명", LVCFMT_RIGHT, 60);
	m_wndReport.InsertColumn(2, "지입날짜", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(3, "입금날짜", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(4, "월납", LVCFMT_CENTER, 40);
	m_wndReport.InsertColumn(5, "지입금", LVCFMT_RIGHT, 60);
	m_wndReport.InsertColumn(6, "신용오더", LVCFMT_RIGHT, 70);
	m_wndReport.InsertColumn(7, "집계시작", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(8, "집계끝", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(9, "상태", LVCFMT_CENTER, 70);
	//m_wndReport.InsertColumn(10, "입금일-지입일", LVCFMT_CENTER, 90);
	m_wndReport.InsertColumn(10, "금일-지입일", LVCFMT_CENTER, 80);
	m_wndReport.InsertColumn(11, "입금자", LVCFMT_RIGHT, 50);
	m_wndReport.InsertColumn(12, "최종금액(지입금-신용오더)", LVCFMT_RIGHT, 160);
	m_wndReport.InsertColumn(13, "은행", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(14, "계좌번호", LVCFMT_LEFT, 110);
	m_wndReport.InsertColumn(15, "예금주", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(16, "적요", LVCFMT_LEFT, 200);
	m_wndReport.InsertColumn(17, "메모", LVCFMT_LEFT, 200);

	m_wndReport.Populate();
	m_cmbState.SetCurSel(0);

	m_wndReport.LoadReportOrder("CIncomeForm6", "m_wndReport");
	SetResize(IDC_REPORT_LIST, sizingRightBottom);
}

void CIncomeForm6::RefreshList()
{
	CMyFormView::RefreshList();

    m_wndReport.DeleteAllItems();
	UpdateData(TRUE);

	CString sRNo;
	m_RNoEdit.GetWindowText(sRNo);

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rider_fixeddeposit_taking_log_3");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	
	if(!pRs.Execute(&pCmd)) return;

	long nID, nRNo, nFixedDeposit, nWNo, nState, nCreditOrderSum, nCompany, nRiderIncomeDay;
	CString sRName, sTakeDate, sEtc;
	BOOL bWeeklyDeposit, bSameRiderIncomeDay;
	COleDateTime dtGenerate, dtCreditOrderStart, dtCreditOrderEnd;
	CString sBankName, sBankAccount, sBankAccountOwner, sMemo;

	char buffer[20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
		pRs.GetFieldValue("sTakeDate", sTakeDate);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nCreditOrderSum", nCreditOrderSum);
		pRs.GetFieldValue("dtCreditOrderStart", dtCreditOrderStart);
		pRs.GetFieldValue("dtCreditOrderEnd", dtCreditOrderEnd);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nRiderIncomeDay", nRiderIncomeDay);
		pRs.GetFieldValue("bSameRiderIncomeDay", bSameRiderIncomeDay);
		pRs.GetFieldValue("sBankName", sBankName);
		pRs.GetFieldValue("sBankAccount", sBankAccount);
		pRs.GetFieldValue("sBankAccountOwner", sBankAccountOwner);
		pRs.GetFieldValue("sMemo", sMemo);

		COleDateTime dtMainDate(_ttoi(sTakeDate.Left(4)), _ttoi(sTakeDate.Mid(4, 2)), _ttoi(sTakeDate.Right(2)), 0, 0, 0);
		COleDateTime dtCur = COleDateTime::GetCurrentTime();
		dtCur.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 0, 0, 0);

		COleDateTime dtCompareDate;

		//if(nRiderIncomeDay != 0 && bWeeklyDeposit == FALSE)
		dtCompareDate = GetCompareDate(bWeeklyDeposit, dtMainDate, nRiderIncomeDay, bSameRiderIncomeDay); 
		
		m_wndReport.InsertItem(i, itoa(nRNo, buffer, 10), -1, 0);
		m_wndReport.SetItemText(i, 1, sRName);
		m_wndReport.SetItemText(i, 2, sTakeDate.Mid(2,2) + "-" + sTakeDate.Mid(4, 2) + "-" + sTakeDate.Right(2));
		m_wndReport.SetItemText(i, 3, nRiderIncomeDay == 0 && bWeeklyDeposit == TRUE ? "" : dtCompareDate.Format("%y-%m-%d"));
		m_wndReport.SetItemText(i, 4, bWeeklyDeposit == TRUE ? "주납" : "월납");
		m_wndReport.SetItemText(i, 5, ::GetMyNumberFormat(nFixedDeposit));
		m_wndReport.SetItemText(i, 6, ::GetMyNumberFormat(nCreditOrderSum));
		m_wndReport.SetItemText(i, 7, dtCreditOrderStart.Format("%y-%m-%d"));
		m_wndReport.SetItemText(i, 8, dtCreditOrderEnd.Format("%y-%m-%d"));

		if(nState == 0)
			m_wndReport.SetItemText(i, 9, "미정산");
		else if(nState == 1)
			m_wndReport.SetItemText(i, 9, "정산완료");
		else if(nState == 2) 
			m_wndReport.SetItemText(i, 9, "입금완료");

		//m_wndReport.SetItemText(i, 10, nState == 1 && nRiderIncomeDay != 0 ? GetIncomeState(bWeeklyDeposit, dtMainDate, nRiderIncomeDay, bSameRiderIncomeDay) : "");
		m_wndReport.SetItemText(i, 10, nState == 1 ? GetIncomeState(bWeeklyDeposit, dtCompareDate, nRiderIncomeDay, bSameRiderIncomeDay) : "");
		//&& nRiderIncomeDay != 0
		m_wndReport.SetItemText(i, 11, nWNo == -1 ? "서버" : itoa(nWNo, buffer, 10));
		m_wndReport.SetItemText(i, 12, ::GetMyNumberFormat(nFixedDeposit - nCreditOrderSum));
		m_wndReport.SetItemText(i, 13, sBankName);
		m_wndReport.SetItemText(i, 14, sBankAccount);
		m_wndReport.SetItemText(i, 15, sBankAccountOwner);
		m_wndReport.SetItemText(i, 16, sEtc);
		m_wndReport.SetItemText(i, 17, sMemo);
        
		m_wndReport.SetItemLong(i, nCompany);
		m_wndReport.SetItemData(i, nID);
		m_wndReport.SetItemLong2(i, nFixedDeposit - nCreditOrderSum);

		pRs.MoveNext();
	}

	m_wndReport.Populate();
	RecordHide();
}

void CIncomeForm6::OnClickList(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nRow = pItemNotify->pRow->GetRecord()->GetIndex();
	long nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol >= 13 && nCol <= 15)
		m_wndReport.SetSelectCol(nRow, nCol);

	m_wndReport.Populate();
}

void CIncomeForm6::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	//m_wndReport.ScreenToClient(&point);
	m_wndReport.GetWindowRect(&rect);

	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(7);
	pRMenu->EnableMenuItem(ID_HALF_INSERT_FIXED_DEPOSIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

}

void CIncomeForm6::OnMakeFixedDeposit()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	long nRiderCompany = m_wndReport.GetItemLong(index);
	long nRNo = _ttoi(m_wndReport.GetItemText(index, 0));
	CString sRName = m_wndReport.GetItemText(index, 1);

	CMakeFixedDepositDlg dlg;
	dlg.m_nRiderCompany = nRiderCompany;
	dlg.m_nRNo = nRNo;
	dlg.m_strRName = sRName;

	if(dlg.DoModal() == IDOK)
		RefreshList();

}
void CIncomeForm6::OnHalfInsertFixedDeposit()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{
		MessageBox("부분 입금 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	CHalfInsertFixedDepositDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		long nID = (long)m_wndReport.GetItemData(index);

		CString sDepositCharge; sDepositCharge = m_wndReport.GetItemText(index, 11);
		sDepositCharge.Replace(",", "");

		if(dlg.m_nCharge > _ttoi(sDepositCharge))
		{
			if(MessageBox("부분 수정 할 금액이 지입금보다 큽니다\r\n   진행하시겠습니까", "확인", MB_OKCANCEL) != IDOK)
				return;
		}

		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nCharge);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshList();

	}
}
void CIncomeForm6::OnDeleteFixedDeposit()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) 
	{
		MessageBox("삭제 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sDate = m_wndReport.GetItemText(index, 3);
	CString sCharge = m_wndReport.GetItemText(index, 11);

	CString str;
	str.Format("지입일 : %s, 금액 : %s원을 삭제 하시겠습니까?", sDate.Right(5), sCharge);

	if(MessageBox(str, "확인", MB_OKCANCEL) == IDOK)
	{
		long nID = (long)m_wndReport.GetItemData(index);

		CMkCommand pCmd(m_pMkDb, "delete_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshList();
	}
}

void CIncomeForm6::OnNotReport()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndReport.GetItemText(index, 9);

	if(sState == "미정산")
	{
		return;
	}
	else if(sState == "정산완료" || sState == "입금완료")
	{
		long nID = (long)m_wndReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();	
	}
}
void CIncomeForm6::OnReportComplete()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndReport.GetItemText(index, 9);

	if(sState == "미정산")
	{
		MessageBox("정산창을 이용하세요!", "확인", MB_ICONINFORMATION);
		return; 
	}
	else if(sState == "입금완료")
	{
		long nID = (long)m_wndReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();	
	}
}
void CIncomeForm6::OnIncomeComplete()
{
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CString sState = m_wndReport.GetItemText(index, 9);

	if(sState == "미정산")
	{
		MessageBox("정산먼저 완료하세요", "확인", MB_ICONINFORMATION);
	}
	else if(sState == "정산완료")
	{
		long nID = (long)m_wndReport.GetItemData(index);
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 2);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();
	}
	else if(sState == "입금완료")
	{
		return;
	}
}

void CIncomeForm6::OnViewExcel()
{
	if(!POWER_CHECK(7900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(m_ci.m_nCompanyCode, 504, m_wndReport.GetItemCount());  
	CMyExcel::ToExcel(&m_wndReport);
}

CString CIncomeForm6::GetIncomeState(BOOL bWeeklyDeposit, COleDateTime dtMainDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay)
{

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 0, 0, 0);

	CString str ="";

	if(dtMainDate == dtCur)
		str = "금일";
	else if(dtMainDate < dtCur)
	{
		COleDateTimeSpan span = dtCur - dtMainDate;
		str.Format("%d일경과됨", span.GetDays());
	}
	else if(dtMainDate > dtCur)
	{
		COleDateTimeSpan span = dtMainDate - dtCur;
		str.Format("%d일남음", span.GetDays());
	}


	return str;
}

void CIncomeForm6::OnEnChangeRnoEdit()
{
	RecordHide();
}

void CIncomeForm6::OnCbnSelchangeStateCombo()
{
	RecordHide();
}

void CIncomeForm6::RecordHide()
{ 
	long nSel = m_cmbState.GetCurSel();
	CString sSearchRNo; m_RNoEdit.GetWindowText(sSearchRNo);
	CString sSearchState; m_cmbState.GetLBText(nSel, sSearchState);

	if(nSel == 0)
		sSearchState = "";
	
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord* pRecord = pRecords->GetAt(i); 

		CString sState = pRecord->GetItem(9)->GetCaption(NULL);
		CString sRNo = pRecord->GetItem(0)->GetCaption(NULL);

		if((sRNo == sSearchRNo || sSearchRNo == "") &&
			sState.Find(sSearchState) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_wndReport.Populate();
}

BOOL CIncomeForm6::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL) & 0x8000)
	{
		if(pMsg->wParam == 'c' || pMsg->wParam == 'C')
		{
			CPoint pt;
			::GetCursorPos(&pt);

			CRect rcList; m_wndReport.GetWindowRect(&rcList);

			if(!rcList.PtInRect(pt))
				return TRUE;

			if(m_wndReport.GetSelCol() >= 13 && m_wndReport.GetSelCol() <= 15) //은행정보
			{
				CXTPGridRecords *pRecords = m_wndReport.GetRecords();
				CXTPGridRecord* pRecord = pRecords->GetAt(m_wndReport.GetSelRow());

                CString sText = ((CXTPGridRecordItemText*)pRecord->GetItem(m_wndReport.GetSelCol()))->GetCaption(NULL);
		
				if(::OpenClipboard(m_hWnd))
				{
					::EmptyClipboard();

					HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, sText.GetLength()+1);
					LPSTR pData = (LPSTR)::GlobalLock(hData);
					::strcpy(pData, sText);
					::GlobalUnlock(hData);

					::SetClipboardData(CF_TEXT, hData);
					::CloseClipboard();
				}
			}
		}
	}
	

	return CMyFormView::PreTranslateMessage(pMsg);
}
