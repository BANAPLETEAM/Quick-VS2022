// IncomeForm10.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "IncomeForm10.h"
#include "RiderSelectDlg.h"
#include "VarietyDlg.h"
// CIncomeForm10

#define TIMER_REFRESH_RIDER 2312

IMPLEMENT_DYNCREATE(CIncomeForm10, CMyFormView)

CIncomeForm10::CIncomeForm10()
	: CMyFormView(CIncomeForm10::IDD)
{

}

CIncomeForm10::~CIncomeForm10()
{
}

void CIncomeForm10::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARD_LIST, m_lstCard);
	DDX_Control(pDX, IDC_LOG_LIST, m_lstLog);
	DDX_Control(pDX, IDC_CARD_NUMBER_EDIT, m_edtCardNumber);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CIncomeForm10, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CIncomeForm10::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_INSERT_CARD_BTN, &CIncomeForm10::OnBnClickedInsertCardBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_RECHARGE_ON, OnRechargeOn)
	ON_COMMAND(ID_RECHARGE_OFF, OnRechargeOff)
	ON_COMMAND(ID_CARD_GIVE, OnCardGive)
	ON_COMMAND(ID_CARD_TAKE, OnCardTake)
	ON_COMMAND(ID_CARD_RECHARGE, OnCardRecharge)

	ON_BN_CLICKED(IDC_REFRESH_LOG_BTN, &CIncomeForm10::OnBnClickedRefreshLogBtn)
	ON_WM_TIMER()
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_CARD_LIST, OnReportItemChange)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CIncomeForm10::OnEnChangeSearchEdit)
END_MESSAGE_MAP()

void CIncomeForm10::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	SetTimer(TIMER_REFRESH_RIDER, 500, NULL);
}

// CIncomeForm10 진단입니다.

#ifdef _DEBUG
void CIncomeForm10::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIncomeForm10::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIncomeForm10 메시지 처리기입니다.

void CIncomeForm10::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();

	m_edtCardNumber.SetEditMask("0000-0000-0000-0000", LITERAL_CARD_NUMBER);
	m_edtCardNumber.SetPromptChar(' ');

	m_lstCard.InsertColumn(0, "카드번호", LVCFMT_LEFT, 120);
	m_lstCard.InsertColumn(1, "사용가능", LVCFMT_CENTER, 60);
	m_lstCard.InsertColumn(2, "충전가능", LVCFMT_CENTER, 60);
	m_lstCard.InsertColumn(3, "등록일", LVCFMT_LEFT, 100);
	m_lstCard.InsertColumn(4, "사번", LVCFMT_RIGHT, 50);
	m_lstCard.InsertColumn(5, "기사명", LVCFMT_LEFT, 60);
	m_lstCard.InsertColumn(6, "적요", LVCFMT_LEFT, 100);
	m_lstCard.Populate();

	m_lstLog.InsertColumn(0, "카드번호", LVCFMT_LEFT, 110);
	m_lstLog.InsertColumn(1, "상태", LVCFMT_LEFT, 110);
	m_lstLog.InsertColumn(2, "충전금액", LVCFMT_LEFT, 110);
	m_lstLog.InsertColumn(3, "날짜", LVCFMT_LEFT, 110);
	m_lstLog.InsertColumn(4, "적요", LVCFMT_LEFT, 200);
	m_lstLog.Populate();

	SetResize(IDC_CARD_LIST, sizingBottom);
	SetResize(IDC_LOG_LIST, sizingRightBottom);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CIncomeForm10::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstCard.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "VRCardRider_select");
	cmd.AddParameter(m_ci.m_nShareCode1);
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);

	if(!rs.Execute(&cmd))
		return;

	long nCompany, nRNo; 
	CString strCardNumber, strCardKey, strErrorMent, strRName; 
	COleDateTime dtRegister;
	BOOL bActive;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sCardNumber", strCardNumber);
		rs.GetFieldValue("sCardNumber", strCardKey);
		rs.GetFieldValue("sError", strErrorMent);
		rs.GetFieldValue("bActive", bActive);
		rs.GetFieldValue("sCardKey", strCardKey); 
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("sRName", strRName);
		
		m_lstCard.InsertItem(i, LF->GetDashCardNumber(strCardNumber));
		m_lstCard.SetItemText(i, 1, strCardKey.IsEmpty() ? "불가" : "");
		m_lstCard.SetItemText(i, 2, bActive == TRUE ? "" : "X");
		m_lstCard.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d %H:%M"));
		m_lstCard.SetItemText(i, 4, LF->GetStringFromLong(nRNo, FALSE));
		m_lstCard.SetItemText(i, 5, strRName);
		m_lstCard.SetItemText(i, 6, strErrorMent);

		m_lstCard.SetItemLong(i, nCompany);
		m_lstCard.SetItemLong2(i, nRNo);
		m_lstCard.SetItemString(i, strCardNumber);

		rs.MoveNext();
	}

	m_lstCard.Populate();
}

void CIncomeForm10::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CIncomeForm10::OnBnClickedInsertCardBtn()
{
	CString strCardNumber; m_edtCardNumber.GetWindowText(strCardNumber);
	strCardNumber =LF->GetNoneDashNumber(strCardNumber);

	if(strCardNumber.IsEmpty())
	{
		MessageBox("카드번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(LF->InsertNewCard(strCardNumber, 0, 0))
		RefreshList();
}

void CIncomeForm10::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcCard;
	m_lstCard.GetWindowRect(rcCard);

	if(rcCard.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
		CMenu *pRMenu=rMenu.GetSubMenu(7);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CIncomeForm10::OnRechargeOn()
{
	ChangeAbleRechargeState(TRUE);
}

void CIncomeForm10::OnRechargeOff()
{
	ChangeAbleRechargeState(FALSE);
}

void CIncomeForm10::ChangeAbleRechargeState(BOOL bActive)
{
	CXTPGridSelectedRows *pRows = m_lstCard.GetSelectedRows();

	long nCount = pRows->GetCount();

	if(nCount == 0)
		return; 

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		CMkCommand cmd(m_pMkDb, "VRCardRider_Active");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

		cmd.AddParameter(m_lstCard.GetItemString(pRecord));
		cmd.AddParameter(bActive);
		CMkParameter *parOut = cmd.AddParameter(typeString, typeOutput, 200, "");

		if(!cmd.Execute())
			break;

		long nRet; parRet->GetValue(nRet);
		CString strError; parOut->GetValue(strError);

		if(nRet == 0)
		{
			MessageBox(strError, "확인", MB_ICONINFORMATION);
			break;
		}

		pRecord->GetItem(2)->SetCaption(bActive == TRUE ? "" : "X");
	}

	m_lstCard.RedrawControl();
}

BOOL CIncomeForm10::ChargeCardRiderState(CXTPGridRecord *pRecord, long nCompany, long nRNo)
{
	CString strRName;

	if(LF->UpdateRiderCardState(m_lstCard.GetItemString(pRecord), nCompany, nRNo, strRName) == FALSE)
		return FALSE;

	pRecord->GetItem(4)->SetCaption(LF->GetStringFromLong(nRNo, FALSE));
	pRecord->GetItem(5)->SetCaption(strRName);

	m_lstCard.SetItemLong(pRecord, nCompany);
	m_lstCard.SetItemLong2(pRecord, nRNo);

	return TRUE;
}

void CIncomeForm10::OnCardGive()
{
	CXTPGridRecord *pRecord = m_lstCard.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CRiderSelectDlg dlg;

	if(dlg.DoModal() == IDOK)
		ChargeCardRiderState(pRecord, dlg.m_nCompany, dlg.m_nRNo);

	m_lstCard.RedrawControl();
}

void CIncomeForm10::OnCardTake()
{
	CXTPGridSelectedRows *pRows = m_lstCard.GetSelectedRows();

	long nCount = pRows->GetCount();

	if(nCount == 0)
		return; 

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		if(!ChargeCardRiderState(pRecord, 0, 0))
			break;		
	}

	m_lstCard.RedrawControl();
}

void CIncomeForm10::OnCardRecharge()
{
	CXTPGridRecord *pRecord = m_lstCard.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nCompany = m_lstCard.GetItemLong(pRecord);
	long nRNo = m_lstCard.GetItemLong2(pRecord);

	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "충전금액을 입력하세요";

	if(dlg.DoModal() != IDOK)
		return;

	CString strValue = LF->GetNoneDashNumber(dlg.m_sValue);
	long nCharge = atoi(strValue);

	if(nCharge <= 0)
	{
		MessageBox("충전 금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	long nApplyCount = 0;

	CXTPGridRecords *pRecords = m_lstCard.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord1 = pRecords->GetAt(i);

		CMkCommand cmd(m_pMkDb, "VRCardRiderLayout_Insert");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		cmd.AddParameter(m_ui.strName); 
		cmd.AddParameter(nCompany);
		cmd.AddParameter(nRNo);
		cmd.AddParameter(nCharge);
		CMkParameter *parOut = cmd.AddParameter(typeString, typeOutput, 200, "");

		if(!cmd.Execute())
			break;

		long nRet; parRet->GetValue(nRet);
		CString strError; parOut->GetValue(strError);

		if(nRet == -1)
		{
			MessageBox(strError, "확인", MB_ICONINFORMATION);
			break;
		}
	}

	if(nApplyCount > 0)
	{
		CString strTemp = LF->GetStringFromLong(nApplyCount) + "건에 적용되었습니다.";
		MessageBox(strTemp, "확인", MB_ICONINFORMATION);
		RefreshLogList(FALSE);
	}
}

void CIncomeForm10::RefreshLogList(BOOL bAll)
{
	m_lstLog.DeleteAllItems();

	UpdateData(TRUE);
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd;

	if(bAll == TRUE)
	{
		cmd.SetMkCommand(m_pMkDb, "VRCardRiderLayout_select_rider_date");
		cmd.AddParameter(m_ci.m_nShareCode1);
		cmd.AddParameter(m_dtFrom);
		cmd.AddParameter(m_dtTo);
	}
	else
	{
		CXTPGridRecord *pRecord = m_lstCard.GetFirstSelectedRecord();

		if(pRecord == NULL)
			return;

		cmd.SetMkCommand(m_pMkDb, "VRCardRiderLayout_select_rider");
		cmd.AddParameter(m_lstCard.GetItemLong(pRecord));
		cmd.AddParameter(m_lstCard.GetItemLong2(pRecord));
	}

	if(!rs.Execute(&cmd))
		return;

	CString strCardNumber, strProcess, strErrorMsg;
	long nChargeAmount;
	COleDateTime dtReq;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sCardNumber", strCardNumber);
		rs.GetFieldValue("sProcess", strProcess);
		rs.GetFieldValue("sErrorMsg", strErrorMsg);
		rs.GetFieldValue("nChargeAmount", nChargeAmount);
		rs.GetFieldValue("dtReq", dtReq);

		m_lstLog.InsertItem(i, LF->GetDashCardNumber(strCardNumber));
		m_lstLog.SetItemText(i, 1, strProcess);
		m_lstLog.SetItemText(i, 2, LF->GetMyNumberFormat(nChargeAmount));
		m_lstLog.SetItemText(i, 3, dtReq.Format("%Y-%m-%d %H:%M"));
		m_lstLog.SetItemText(i, 4, strErrorMsg);

		rs.MoveNext();
	}
	
	m_lstLog.Populate();
}

void CIncomeForm10::OnBnClickedRefreshLogBtn()
{
	RefreshLogList(TRUE);
}

void CIncomeForm10::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	if(nIDEvent == TIMER_REFRESH_RIDER)
		RefreshLogList(FALSE);

	CMyFormView::OnTimer(nIDEvent);
}

void CIncomeForm10::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstCard.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strCard = m_lstCard.GetItemString(pRecord);
		CString strRNo = pRecord->GetItem(4)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(5)->GetCaption(NULL);

		if(strCard.Find(strSearch) >= 0 ||
			strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0 )
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstCard.Populate();
}
