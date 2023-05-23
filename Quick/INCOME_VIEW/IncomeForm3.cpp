// StaffPage2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm3.h"
#include "DepositRateDlg.h"

IMPLEMENT_DYNCREATE(CIncomeForm3, CMyFormView)
CIncomeForm3::CIncomeForm3()
	: CMyFormView(CIncomeForm3::IDD)
	
{
	m_nCompany = 0;
	m_nRNo = 0;
}

CIncomeForm3::~CIncomeForm3()
{
}

void CIncomeForm3::DoDataExchange(CDataExchange* pDX)
{

	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_SEARCH_LIST2, m_lstSearch);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_HISTORY_LIST2, m_lstHistory);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_RNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_CHARGE_COMBO, m_cmbCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_ALL_LIST2, m_AllList);
	DDX_Control(pDX, IDC_CHARGE_BTN, m_btnCharge);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);
	DDX_Control(pDX, IDC_BALANCE_EDIT, m_edtBalance);
}


BEGIN_MESSAGE_MAP(CIncomeForm3, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_CHARGE_BTN, OnBnClickedChargeBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SEARCH_LIST, OnLvnItemchangedSearchList)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CIncomeForm3::OnEnChangeSearchEdit)

	ON_NOTIFY(NM_CLICK, IDC_SEARCH_LIST2, OnNMClickList)
END_MESSAGE_MAP()


// CIncomeForm3 메시지 처리기입니다.

void CIncomeForm3::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstSearch.InsertColumn(0,"소속",LVCFMT_LEFT, 100);
	m_lstSearch.InsertColumn(1,"기사번호",LVCFMT_CENTER, 65);
	m_lstSearch.InsertColumn(2,"기사명",LVCFMT_LEFT, 80);
	m_lstSearch.InsertColumn(3,"입금방식",LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(4,"업무상태",LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(5,"휴대폰",LVCFMT_LEFT, 100);
	m_lstSearch.InsertColumn(6,"아이디",LVCFMT_RIGHT, 120);
	m_lstSearch.InsertColumn(7,"차량종류",LVCFMT_RIGHT, 90);
	m_lstSearch.Populate();

	m_lstHistory.InsertColumn(0,"생성시점",LVCFMT_LEFT, 120);
	m_lstHistory.InsertColumn(1,"사번",LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(2,"기사명",LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(3,"차감",LVCFMT_RIGHT, 70);
	m_lstHistory.InsertColumn(4,"입금",LVCFMT_RIGHT, 70);
	m_lstHistory.InsertColumn(5,"타입",LVCFMT_LEFT, 150);
	m_lstHistory.InsertColumn(6,"담당자",LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(7,"비고",LVCFMT_LEFT, 200);
	m_lstHistory.InsertColumn(8,"잔액(원)",LVCFMT_RIGHT, 70);
	m_lstHistory.Populate();

	m_AllList.InsertColumn(0,"생성시점",LVCFMT_LEFT, 120);
	m_AllList.InsertColumn(1,"사번",LVCFMT_LEFT, 80);
	m_AllList.InsertColumn(2,"기사명",LVCFMT_LEFT, 80);
	m_AllList.InsertColumn(3,"차감",LVCFMT_RIGHT, 70);
	m_AllList.InsertColumn(4,"입금",LVCFMT_RIGHT, 70);
	m_AllList.InsertColumn(5,"타입",LVCFMT_LEFT, 150);
	m_AllList.InsertColumn(6,"담당자",LVCFMT_LEFT, 80);
	m_AllList.InsertColumn(7,"비고",LVCFMT_LEFT, 200);
	m_AllList.InsertColumn(8,"잔액(원)",LVCFMT_RIGHT, 70);;
	m_AllList.Populate();

	SetResize(IDC_SEARCH_LIST2, sizingRight);
	SetResize(IDC_HISTORY_LIST2, sizingRight);
	SetResize(IDC_ALL_LIST2, sizingRightBottom);
}

void CIncomeForm3::OnBnClickedRefreshBtn()
{
	RefreshAllLog();
}

void CIncomeForm3::OnBnClickedSearchBtn()
{
	SearchRider();
}

void CIncomeForm3::FillListData()
{
	long nItem = 0;
	char buffer[10];

	MAP_ALLOC_RIDER::iterator itRider;
	for(itRider = LU->m_mapAllocateRider.begin(); itRider != LU->m_mapAllocateRider.end(); itRider++)
	{
		if(itRider->second.strName == "신규추가")
			continue;

		m_lstSearch.InsertItem(nItem, itRider->second.strBranchName);
		m_lstSearch.SetItemText(nItem, 1, itoa(itRider->second.nMNo, buffer, 10));
		m_lstSearch.SetItemText(nItem, 2, itRider->second.strName);
		m_lstSearch.SetItemText(nItem, 3, LF->GetDepositTypeStringFromType(itRider->second.nDepositType));
		m_lstSearch.SetItemText(nItem, 4, itRider->second.nWorkState == 1 ? "중지" : "");
		m_lstSearch.SetItemText(nItem, 5, itRider->second.strHp);
		m_lstSearch.SetItemText(nItem, 6, itRider->second.strID);
		m_lstSearch.SetItemText(nItem, 7, LF->GetCarTypeFromLong(itRider->second.nCarType));

		m_lstSearch.SetItemLong(nItem, itRider->second.lCode);
		m_lstSearch.SetItemLong2(nItem, itRider->second.nMNo);
		nItem++;
	}

	m_lstSearch.Populate();
}

void CIncomeForm3::SearchRider()
{	
	//m_lstSearch.DeleteAllItems();

	CString strData;
	m_edtSearch.GetWindowText(strData);

	CXTPGridRecords *pRecords = m_lstSearch.GetRecords();
	
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString sRNo = m_lstSearch.GetItemText(pRecord, 1);
		CString sRName = m_lstSearch.GetItemText(pRecord, 2);

		if(sRNo.Find(strData) >= 0 ||
			sRName.Find(strData) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstSearch.Populate();
}

void CIncomeForm3::RefreshHistory()
{	
	m_lstHistory.DeleteAllItems();
	
	CXTPGridSelectedRows *pRows = m_lstSearch.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	long nCompany = m_lstSearch.GetItemLong(pRecord);
	long nRNo = m_lstSearch.GetItemLong2(pRecord);

	//CWaitCursor wait;

	CMkRecordset pRs(m_pMkDb);
    CMkCommand pCmd(m_pMkDb, "select_one_rider_deposit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nRNo);
	
	pRs.Execute(&pCmd);

	long nWNo, nBalance, nState, nAmount;
	CString strRName, strEtc;
	COleDateTime dtGenerate;
	int nItem = 0;
	char buffer[20];

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nBalance", nBalance);

		m_lstHistory.InsertItem(nItem, dtGenerate.Format("%Y-%m-%d %H:%M:%S"));
		m_lstHistory.SetItemText(nItem, 1, strRName);
		m_lstHistory.SetItemText(nItem, 2, itoa(nRNo, buffer, 10));

		if((nState >= 40 && nState <= 60) || nState == 61)
			m_lstHistory.SetItemText(nItem, 3, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		if(nState >= 10 && nState <= 30)
			m_lstHistory.SetItemText(nItem, 4, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		m_lstHistory.SetItemText(nItem, 5, LF->GetFixedDepositStateString(nState));
		m_lstHistory.SetItemText(nItem, 6, (nWNo == 100000) ? "서버" : ltoa(nWNo, buffer, 10));
		m_lstHistory.SetItemText(nItem, 7, strEtc);
		m_lstHistory.SetItemText(nItem, 8, nBalance == -1 ? "-" : LF->GetMyNumberFormat(nBalance));
		m_lstHistory.SetItemData(nItem, nState);
	//	m_lstHistory.SetItemLong(nItem, nTNo);

		nItem++;
		pRs.MoveNext();
	}

	m_lstHistory.Populate();

	pRs.Close();
}

void CIncomeForm3::RefreshList()
{
	CMyFormView::RefreshList();
	FillListData();
	RefreshAllLog();
}

void CIncomeForm3::RefreshAllLog()
{
	m_lstHistory.DeleteAllItems();

	CXTPGridSelectedRows *pRows = m_lstSearch.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	long nCompany = m_lstSearch.GetItemLong(pRecord);
	long nRNo = m_lstSearch.GetItemLong2(pRecord);

	//CWaitCursor wait;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_input");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),	LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);

	pRs.Execute(&pCmd);

	long nWNo, nBalance, nState, nAmount;
	CString strRName, strEtc;
	COleDateTime dtGenerate;
	int nItem = 0;
	char buffer[20];

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nBalance", nBalance);

		m_AllList.InsertItem(nItem, dtGenerate.Format("%Y-%m-%d %H:%M:%S"));
		m_AllList.SetItemText(nItem, 1, strRName);
		m_AllList.SetItemText(nItem, 2, itoa(nRNo, buffer, 10));

		if((nState >= 40 && nState <= 60) || nState == 61)
			m_AllList.SetItemText(nItem, 3, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		if(nState >= 10 && nState <= 30)
			m_AllList.SetItemText(nItem, 4, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		m_AllList.SetItemText(nItem, 5, LF->GetFixedDepositStateString(nState));
		m_AllList.SetItemText(nItem, 6, (nWNo == 100000) ? "서버" : ltoa(nWNo, buffer, 10));
		m_AllList.SetItemText(nItem, 7, strEtc);
		m_AllList.SetItemText(nItem, 8, nBalance == -1 ? "-" : LF->GetMyNumberFormat(nBalance));
		m_AllList.SetItemData(nItem, nState);
		//	m_lstHistory.SetItemLong(nItem, nTNo);

		nItem++;
		pRs.MoveNext();
	}

	m_AllList.Populate();

	pRs.Close();
}

BOOL CIncomeForm3::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtSearch.GetSafeHwnd())
		{
			if(IsCountOne())
			{
				SelectRider();
				RefreshHistory();
				m_cmbCharge.SetFocus();
			}
			return TRUE;
		}
		else if(pMsg->hwnd == m_cmbCharge.GetSafeHwnd())
		{
			OnBnClickedChargeBtn();
			return TRUE;
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

BOOL CIncomeForm3::IsCountOne()
{
	CXTPGridRows *pRows = m_lstSearch.GetRows();

	if(pRows->GetCount() == 1) 
	{
		CXTPGridRow *pRow = pRows->GetAt(0);
		m_lstSearch.GetSelectedRows()->Select(pRow);
		return TRUE;
	}

	return FALSE;
}

void CIncomeForm3::OnBnClickedChargeBtn()
{
	if(!LF->POWER_CHECK(7031, "선입금충전전용", TRUE))
		return;


	CXTPGridSelectedRows *pRows = m_lstSearch.GetSelectedRows();

	if(pRows == NULL){MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION); return;}
	if(pRows->GetCount() == 0){MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION); return;}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();
	
	CString strEtc;
	m_edtEtc.GetWindowText(strEtc);
	CString strRName = m_lstSearch.GetItemText(pRecord, 2);
	long nCompany = (long)m_lstSearch.GetItemLong(pRecord);
	long nRNo = (long)m_lstSearch.GetItemLong2(pRecord);

	if(m_nCompany != nCompany || m_nRNo != nRNo)
	{
		MessageBox("기사님 선택이 잘못 되었습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strCharge;
	m_cmbCharge.GetWindowText(strCharge);

	long nState;
	long nCharge = atoi(strCharge);

	if(nCharge == 0)
	{
		MessageBox("충전하실 금액을 입력 하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(nCharge > 0)
		nState = 17;
	else
	{
		nState = 40;
		nCharge = abs(nCharge);
	}	

	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_balance_today");
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(strRName);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(nCharge);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(strEtc);

	if(!pCmd.Execute())
	{
		MessageBox("선입금 생성을 실패하였습니다.", "확인", MB_ICONINFORMATION);	
	}
	else
	{
		MessageBox("충전 되었습니다" ,"확인", MB_ICONINFORMATION);
		RefreshHistory();
		RefreshAllLog();
		m_edtSearch.SetFocus();
	}
}

void CIncomeForm3::OnLvnItemchangedSearchList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->uNewState & LVIS_SELECTED) 
	{
		RefreshHistory();
	}

	*pResult = 0;
}

void CIncomeForm3::OnEnChangeSearchEdit()
{
	SearchRider();
}


void CIncomeForm3::OnNMClickList(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	SelectRider();
}

void CIncomeForm3::SelectRider()
{
	CXTPGridSelectedRows *pRows = m_lstSearch.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	char buffer[10];
	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_nCompany = m_lstSearch.GetItemLong(pRecord);
	m_nRNo = m_lstSearch.GetItemLong2(pRecord);

	m_edtCompany.SetWindowText(m_lstSearch.GetItemText(pRecord, 0));
	m_edtRName.SetWindowText(m_lstSearch.GetItemText(pRecord, 2));
	m_edtRNo.SetWindowText(itoa(m_nRNo, buffer, 10));

	RefreshHistory();
}