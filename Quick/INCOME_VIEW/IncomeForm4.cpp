// StaffPage2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm4.h"
#include "DepositRateDlg.h"
#include "RiderMsgDlg.h"
#include "OtherAccountDlg.h"
#include "RiderDepositDlg.h"
#include "RcpView.h"
#include "RiderDepositInfoDlg.h"

#include "DepositGroupDlg.h"



IMPLEMENT_DYNCREATE(CIncomeForm4, CMyFormView)
CIncomeForm4::CIncomeForm4()
: CMyFormView(CIncomeForm4::IDD)
{
	m_bServerTime = FALSE;
	m_nCurSel = 0;
}

CIncomeForm4::~CIncomeForm4()
{
	m_List.SaveReportOrder("CIncomeForm4", "m_List");
}

void CIncomeForm4::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EXAMPLE_DATE_STATIC, m_ExampleStatic);
	//	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_SHOW_BTN, m_ShowBtn);
	DDX_Control(pDX, IDC_MAKE_JOB_BTN, m_MakeJobBtn);
	DDX_Control(pDX, IDC_XTPLISTCTRL_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_WORK_TYPE, m_cmbWorkType);
	DDX_Control(pDX, IDC_MAKE_DEPOSIT_GROUP_BTN, m_btnMakeDepositGroup);
}


BEGIN_MESSAGE_MAP(CIncomeForm4, CMyFormView)
	ON_BN_CLICKED(IDC_ONE_DAY_BTN, OnBnClickedOneDayBtn)
	ON_BN_CLICKED(IDC_SHOW_BTN, OnBnClickedShowBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_INCOME_OK, OnIncomeOk)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_COMMAND(ID_MENU_MSG, OnSendMsg)
	ON_BN_CLICKED(IDC_CLEAR_DEPOSIT_BTN, OnBnClickedClearDepositBtn)
	ON_COMMAND(ID_EDIT_OTHER_ACCOUNT, OnEditOtherAccount)
	ON_COMMAND(ID_RIDER_DEPOSIT_MENU, OnRiderDepositMenu)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_TYPE_COMBO, OnCbnSelchangeXtplistctrlTypeCombo)
	ON_CBN_SELCHANGE(IDC_WORK_TYPE, OnCbnSelchangeWorkType)
	ON_BN_CLICKED(IDC_MAKE_DEPOSIT_GROUP_BTN, OnBnClickedMakeDepositGroupBtn)
END_MESSAGE_MAP()


// CIncomeForm4 메시지 처리기입니다.

void CIncomeForm4::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate(); 

	m_List.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl함수의 순서중요함
		GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO));	//반드시 InsertColumn앞에 있어야함

	m_List.InsertColumn(0,"기사번호",LVCFMT_CENTER,60);
	m_List.InsertColumn(1,"기사명",LVCFMT_LEFT, 90);
	m_List.InsertColumn(2,"운행요금",LVCFMT_RIGHT,65);
	m_List.InsertColumn(3,"입금액",LVCFMT_RIGHT,50);
	m_List.InsertColumn(4,"충전금잔액",LVCFMT_RIGHT, 70);
	m_List.InsertColumn(5,"자사콜",LVCFMT_CENTER, 65);
	m_List.InsertColumn(6,"타사콜",LVCFMT_CENTER, 65);
	m_List.InsertColumn(7,"지사콜",LVCFMT_CENTER, 45);
	m_List.InsertColumn(8,"근무유형",LVCFMT_CENTER, 75);
	m_List.InsertColumn(9,"입금방식",LVCFMT_CENTER, 60);
	m_List.InsertColumn(10,"지입금액",LVCFMT_RIGHT, 60);
	m_List.InsertColumn(11,"지입금일",LVCFMT_LEFT, 70);
	m_List.InsertColumn(12,"업무상태",LVCFMT_CENTER, 60);
	m_List.InsertColumn(13,"금일충전",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(14,"금일현금충전",LVCFMT_RIGHT, 80);
	m_List.InsertColumn(15,"금일차감",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(16,"자동케쥴차감",LVCFMT_RIGHT, 80);
	m_List.InsertColumn(17,"일비차감",LVCFMT_RIGHT, 80);
	//m_List.InsertColumn(14,"신용정산",LVCFMT_LEFT, 65);/
	//m_List.InsertColumn(15,"누적신용금",LVCFMT_LEFT, 75);
	//m_List.InsertColumn(16, "최종금액(지입금-신용오더)", LVCFMT_RIGHT, 160);
	//m_List.InsertColumn(17, "신용누적금", LVCFMT_RIGHT, 80);

	m_cmbWorkType.SetCurSel(1);
	
	//m_List.InsertSearchAllColumn(0);
	//m_List.InsertSearchAllColumn(1);
	//m_List.InsertSearchAllColumn(14);

	//m_List.InsertTypeList("업무가능", 12, " ");
	//m_List.InsertTypeList("업무중지", 12, "중지");

	m_List.LoadReportOrder("CIncomeForm4", "m_List");

	SetResize(IDC_LIST1, sizingRightBottom);

}



void CIncomeForm4::OnBnClickedOneDayBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	CString strDate;	

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	strDate.Format("(%d월%d일 %d:00 ~ %d월%d일 %d:00)", 
		dtFrom.GetMonth(), dtFrom.GetDay(), dtFrom.GetHour(),
		dtTo.GetMonth(), dtTo.GetDay(), dtTo.GetHour());

	m_dtFrom = dtFrom;
	m_dtTo = dtTo;
	m_ExampleStatic.SetWindowText(strDate);
}

void CIncomeForm4::OnBnClickedShowBtn()
{
	RefreshList();
}


CString CIncomeForm4::GetFixedDepositType(long nFixedDeposit, BOOL bWeeklyDeposit, long nPaymentDay)
{
	if(nFixedDeposit <= 0)
		return "";

	CString strType;
	char* strDay[] = {"일", "월", "화", "수", "목", "금", "토"};

	if(bWeeklyDeposit) //주단위
		strType.Format("주비[%s요일]", strDay[nPaymentDay]);
	else
		strType.Format("월비[%d일]", nPaymentDay, nFixedDeposit);

	return strType;
}

CString CIncomeForm4::GetFixedDepositDayString(long nFixedDeposit, COleDateTime dtNextDeposit, long &nRemainDays)
{
	if(nFixedDeposit <= 0)
		return "";

	if(dtNextDeposit.GetStatus() == COleDateTime::null) 
		return "";

	
	CString strNextDeposit;
	COleDateTimeSpan span = dtNextDeposit - COleDateTime::GetCurrentTime();


	//span = dtNextDeposit - COleDateTime::GetCurrentTime();
	
	nRemainDays = (long)span.GetTotalDays();
	if(nRemainDays > 3)
		strNextDeposit = dtNextDeposit.Format("%m-%d");
	else if(nRemainDays > 0)
		strNextDeposit.Format("%d일 전", nRemainDays+1);
	else if(nRemainDays == 0)
		strNextDeposit = "금일";
	else 
		strNextDeposit.Format("%d일 경과됨", abs(nRemainDays));

	return strNextDeposit;
}

CString CIncomeForm4::GetMyPercentString(long nPercent, BOOL bRemoveZero)
{
	CString strValue;
	if(bRemoveZero && nPercent == 0) 
		return "";

	strValue.Format("%d%%", nPercent);
	return strValue;
}

CString CIncomeForm4::GetCreditReportType(long nType)
{
	switch(nType)
	{
		case 1: 
			return "익일충전";
		case 2:
			return "지입금차감";
		default:
			return "";
	}
}


void CIncomeForm4::RefreshList()
{
	CMyFormView::RefreshList();

	CString strText;
	int nSearchRNo = -1; 
	CString strSearchName;
	m_SearchEdit.GetWindowText(strText);

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	typedef map<UINT, UINT> DEPOSIT_RATE;
	DEPOSIT_RATE deposit;

	if(!m_bServerTime)
	{
		CMkCommand pCmd(m_pMkDb, "select_server_time3");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
		CMkRecordset pRs(m_pMkDb);
		if(pRs.Execute(&pCmd))
		{
			pRs.GetFieldValue("curtime", m_dtCurrent);
			m_dtFrom = m_dtCurrent;
			pRs.Close();
			OnBnClickedOneDayBtn();
		}
		else {
			MessageBox("서버시간을 읽어오지 못했습니다. 잠시 후 다시 시도하시기 바랍니다.", "시간체크 실패", MB_OK);
			m_bServerTime = TRUE;
			return;
		}
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_report_new12");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_cmbWorkType.GetCurSel());
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	if(!pRs.Execute(&pCmd)) return;

	long nCompany, nRNo, nCount, nDeposit, nRiderDeposit, nBalance, nCreditReportType;
	long nTodaySave, nCharge,  nCreditOrderSum; 
	long nCreditBalance;
	CString strRName;
	COleDateTime dtNextDeposit;
	char buffer[20];

	long nFixedDeposit;
	BOOL bWeeklyDeposit, bPenaltyCharge, bBranchAsOtherCall;
	long nPaymentDay, nWorkState, nDepositAllocateType;
	long nDepositType, nTodayDeposit, nTodayScheduleDeposit, nTodayCashSave, nDailyDepositCharge;
	CString sMyCallRateType, sOtherCallRateType;
	//nFixedDeposit 가 0보다 크면 월비 혹은 주비
	long nTodaySaveS = 0, nTodayDepositS = 0, nTodayScheduleDepositS = 0, nTodayCashSaveS = 0;
	long nChargeS = 0, nRiderDepositS = 0, nBalanceS = 0;
	int nItem = 0;
	for(nItem = 0; nItem < pRs.GetRecordCount(); nItem++)
	{
		long nRemainDays = 999;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nRiderDeposit", nRiderDeposit);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("nTodaySave", nTodaySave);
        pRs.GetFieldValue("dtNextDeposit", dtNextDeposit);
		pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
		pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
		pRs.GetFieldValue("nPaymentDay", nPaymentDay);
		pRs.GetFieldValue("bPenaltyCharge", bPenaltyCharge);
		pRs.GetFieldValue("bBranchAsOtherCall", bBranchAsOtherCall);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("nCreditReportType", nCreditReportType);
		pRs.GetFieldValue("nCreditOrderSum", nCreditOrderSum);
		pRs.GetFieldValue("nCreditBalance", nCreditBalance);	
		pRs.GetFieldValue("nDepositType", nDepositType);	
		pRs.GetFieldValue("nDepositAllocateType", nDepositAllocateType);
		pRs.GetFieldValue("sMyCallRateType", sMyCallRateType);	
		pRs.GetFieldValue("sOtherCallRateType", sOtherCallRateType);
		pRs.GetFieldValue("nTodayDeposit", nTodayDeposit);
		pRs.GetFieldValue("nTodayScheduleDeposit", nTodayScheduleDeposit);
		pRs.GetFieldValue("nTodayCashSave", nTodayCashSave);
		pRs.GetFieldValue("nDailyDepositCharge", nDailyDepositCharge);
		
		BOOL bRealTime = GetRealTime(nDepositType, nDepositAllocateType);

        m_List.InsertItem(nItem, ltoa(nRNo, buffer, 10), -1, 0); 
		m_List.SetItemText(nItem, 1, strRName);
		m_List.SetItemText(nItem, 2, LF->GetMyNumberFormat(nCharge));
		m_List.SetItemText(nItem, 3, LF->GetMyNumberFormat(nRiderDeposit));
		m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nBalance)); 

		if(bRealTime)
		{
			m_List.SetItemText(nItem, 5, sMyCallRateType); 
			m_List.SetItemText(nItem, 6, sOtherCallRateType);
		}
		else
		{
			m_List.SetItemText(nItem, 5, "");
			m_List.SetItemText(nItem, 6, "");
		}
		
		m_List.SetItemText(nItem, 7, bRealTime == TRUE ? (bBranchAsOtherCall ? "타사" : "my") : ""); 
		m_List.SetItemText(nItem, 8, nDepositType < 50 ? GetFixedDepositType(nFixedDeposit, bWeeklyDeposit, nPaymentDay): "프로제");
		m_List.SetItemText(nItem, 9, nDepositAllocateType == 0 ? "선입금" : "");
		m_List.SetItemText(nItem, 10, nDepositType >= 20 ? (nFixedDeposit == 0 ? "" : 
			 		CString(LF->GetMyNumberFormat(nFixedDeposit / 10000)) + "만원") : "");
		m_List.SetItemText(nItem, 11, nDepositType < 50 ? GetFixedDepositDayString(nFixedDeposit, dtNextDeposit, nRemainDays) : "");
		m_List.SetItemText(nItem, 12, nWorkState != 0 ? "중지" : ""); 
		m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nTodaySave));
		m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nTodayCashSave));
		m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nTodayDeposit));
		m_List.SetItemText(nItem, 16, LF->GetMyNumberFormat(nTodayScheduleDeposit));
		m_List.SetItemText(nItem, 17, LF->GetMyNumberFormat(nDailyDepositCharge));
		
		/*
		m_List.SetItemText(nItem, 14, GetCreditReportType(nCreditReportType));
		m_List.SetItemText(nItem, 15, nDepositType >= 20 ? (nCreditReportType == 2 ? LF->GetMyNumberFormat(nCreditOrderSum) : "") : "");
	
		long nTotal = 0;
		if(nFixedDeposit != 0)
		{
			if(nCreditReportType == 2)
				nTotal = nFixedDeposit - nCreditOrderSum;
			else
				nTotal = nFixedDeposit;
		}

		if(nTotal % 10000 == 0)
			m_List.SetItemText(nItem, 16, nDepositType >= 20 ? (nTotal == 0 ? "" : CString(LF->GetMyNumberFormat(nTotal / 10000)) + "만원") : "");        
		else
			m_List.SetItemText(nItem, 16, nDepositType >= 20 ? (nTotal == 0 ? "" : CString(LF->GetMyNumberFormat(nTotal / 10000)) + "만 " + CString(LF->GetMyNumberFormat(nTotal % 10000)) + "원") : "");        

		m_List.SetItemText(nItem, 17, nCreditBalance == 0 ? "" : LF->GetMyNumberFormat(nCreditBalance));
*/
		m_List.SetItemData(nItem, (long)nCompany);
		m_List.SetItemLong(nItem, (long)nRemainDays);

		nTodayCashSaveS += nTodayCashSave;
		nTodaySaveS += nTodaySave, nTodayDepositS += nTodayDeposit, nTodayScheduleDepositS += nTodayScheduleDeposit;
		nChargeS += nCharge, nRiderDepositS += nRiderDeposit, nBalanceS += nBalance;

		pRs.MoveNext();
	}

	nItem = m_List.GetItemCount();

	m_List.InsertItem(nItem, "");
	m_List.SetItemText(nItem, 2, LF->GetMyNumberFormat(nChargeS));
	m_List.SetItemText(nItem, 3, LF->GetMyNumberFormat(nRiderDepositS));
	m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nBalanceS));
	m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nTodaySaveS));
	m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nTodayCashSaveS));
	m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nTodayDepositS));
	m_List.SetItemText(nItem, 16, LF->GetMyNumberFormat(nTodayScheduleDepositS));

	m_List.Populate();
	//m_List.EnsureVisibleEx(m_nCurSel);
	pRs.Close();
}

void CIncomeForm4::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(6);

		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CIncomeForm4::OnIncomeOk()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CRiderDepositInfoDlg dlg;
		dlg.m_nRiderCompany = (long)m_List.GetItemData(nItem);
		dlg.m_nRNo = atol(m_List.GetItemText(nItem, 0));
		dlg.m_strRName = m_List.GetItemText(nItem, 1);

		if(dlg.DoModal() == IDOK)
		{
			MessageBox("변경되었습니다", "확인", MB_ICONINFORMATION);
			RefreshList();
		}
	}
}

void CIncomeForm4::OnViewExcel()
{
	if(!LF->POWER_CHECK(7900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 501, m_List.GetItemCount());  
	m_List.ToExcel("입금정산");
}

void CIncomeForm4::OnNMDblclkList1(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnIncomeOk();
}

void CIncomeForm4::OnSendMsg()
{
	//if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
	//	return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nSelItem >= 0) {
		CRiderMsgDlg dlg;
		CString strRName = m_List.GetItemText(nSelItem, 1);
		int nDebtSum = LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 4)) +
			LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 6));
		int nPreDeposit = LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 5));
		CString strDepositType = m_List.GetItemText(nSelItem, 9);

		dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
		dlg.SetCompanyCode(m_List.GetItemData(nSelItem));
		dlg.m_strMsg.Format("%s 기사님, 현재 충전금 잔액이 %s원 입니다. 추가 입금바랍니다.", 
			strRName, LF->GetMyNumberFormat(m_List.GetItemText(nSelItem, 4)));

		dlg.DoModal();	
	}
}

BOOL CIncomeForm4::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_SearchEdit.GetSafeHwnd()) {
			RefreshList();
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CIncomeForm4::OnBnClickedClearDepositBtn()
{
	if(IDYES == MessageBox("미수금내역들을 선입금에서 차감합니다.\n"\
		"단, 선입금이 부족한 경우에 정산하지 않습니다."\
		"진행하시겠습니까?", "전직원 미수금 자동정리",
		MB_ICONINFORMATION | MB_YESNO))
	{
		//CWaitCursor wait;
		CMkCommand pCmd(m_pMkDb, "request_clear_company_deposit_1");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);

		if(pCmd.Execute())
		{
			if(parRet->GetLong() == 10)
			{
				MessageBox("미수금 자동정리 가능시간은 오전 10시부터 - 오후 7시까지 입니다.\n"\
					"서버의 부하가 많이 걸리는 관계로, 업무시간에는 사용하실수 없습니다.\n",
					"정리 실패", MB_ICONINFORMATION);
			}
			else
			{
				MessageBox("서버에게 미수금 정리요청을 하였습니다.\n"\
					"백그라운드 작업으로 정리가 진행중입니다.(최대1분후에 시작됨)\n"\
					"등록기사가 많은 경우에는 몇십분까지 걸릴수 있습니다.\n"\
					"검색버튼을 누르셔서 정리가 완료되었는지 확인하시고\n"\
					"입금관련 다른 작업을 진행하시기 바랍니다.",
					"정리 시작",
					MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnEditOtherAccount()
{
	//if(!LF->POWER_CHECK(7012, "입금정산 수정권한", TRUE))
	//	return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {

		COtherAccountDlg dlg;
		dlg.m_strAccount = m_List.GetItemText(nItem, 14);
		if(IDOK == dlg.DoModal())
		{
			long nCompany = m_List.GetItemData(nItem);
			long nRNo = atol(m_List.GetItemText(nItem, 0));

			CMkCommand pCmd(m_pMkDb, "update_other_account_info");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			pCmd.AddParameter(typeString, typeInput, dlg.m_strAccount.GetLength(), dlg.m_strAccount);
			if(!pCmd.Execute())
			{
				MessageBox("수정실패함", "수정실패함", MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnRiderDepositMenu()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {

		CRiderDepositDlg dlg;
		dlg.m_strDeposit = m_List.GetItemText(nItem, 13);
		if(IDOK == dlg.DoModal())
		{
			long nCompany = m_List.GetItemLong(nItem);
			long nRNo = atol(m_List.GetItemText(nItem, 0));
			long nDepositCharge = LF->GetNoneCommaNumber(dlg.m_strDeposit);

			CMkCommand pCmd(m_pMkDb, "update_deposit_of_a_rider");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nDepositCharge);
			if(!pCmd.Execute())
			{
				MessageBox("수정실패함", "수정실패함", MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CIncomeForm4::OnEnChangeXtplistctrlEdit()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	CComboBox *pTypeCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();

	int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_List.Filter(strText, pCombo->GetCurSel(), nTypeData);
}

void CIncomeForm4::OnCbnSelchangeXtplistctrlTypeCombo()
{
	OnEnChangeXtplistctrlEdit();
}


BOOL CIncomeForm4::GetRealTime(long nDepositType, long nDepositAllocateType)
{
	if(nDepositType == 20 || nDepositType == 30 || nDepositType == 40)
	{
		if(nDepositAllocateType == 0)
			return TRUE;

		if(nDepositAllocateType == 10)
			return FALSE;

	}
	else if(nDepositType  == 50)
		return TRUE;

	return FALSE;

}
void CIncomeForm4::OnCbnSelchangeWorkType()
{
	RefreshList();
}

void CIncomeForm4::OnBnClickedMakeDepositGroupBtn()
{
	CDepositGroupDlg dlg;
	dlg.DoModal();
}
