// StaffPage2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm5.h"
#include "DepositRateDlg.h"
#include "OrderLogDetailDlg.h"
#include "RcpView.h"
#include "RcpDlgAdmin.h"

IMPLEMENT_DYNCREATE(CIncomeForm5, CMyFormView)
CIncomeForm5::CIncomeForm5()
: CMyFormView(CIncomeForm5::IDD)
{
	m_bServerTime = FALSE;
	m_nPreCompany = 0;
	m_nPreRNo = 0;
}

CIncomeForm5::~CIncomeForm5()
{
    m_List.SaveReportOrder("CIncomeForm5", "m_List");
}

void CIncomeForm5::DoDataExchange(CDataExchange* pDX)
{

	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_RNO_EDIT, m_RNoEdit);
	DDX_Text(pDX, IDC_RNO_EDIT, m_strRNo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);

	DDX_Control(pDX, IDC_SHOW_TYPE_COMBO, m_cmbShowType);
	DDX_Control(pDX, IDC_RNO_SEARCH_EDIT, m_edtRNoSearch);
	DDX_Control(pDX, IDC_RNAME_SEARCH_EDIT, m_edtRNameSearch);
	DDX_Control(pDX, IDC_MANAGER_SEARCH_EDIT, m_edtManagerSearch);
	DDX_Control(pDX, IDC_ETC_SEARCH_EDIT, m_edtEtcSearch);
}


BEGIN_MESSAGE_MAP(CIncomeForm5, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(ID_VIEW_EXCEL, OnViewExcel)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_TYPE_COMBO, OnCbnSelchangeXtplistctrlTypeCombo)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnReportItemDblClick)

	ON_CBN_SELCHANGE(IDC_SHOW_TYPE_COMBO, OnCbnSelchangeShowTypeCombo)
	ON_EN_CHANGE(IDC_RNO_SEARCH_EDIT, &CIncomeForm5::OnEnChangeRnoSearchEdit)
	ON_EN_CHANGE(IDC_RNAME_SEARCH_EDIT, &CIncomeForm5::OnEnChangeRnameSearchEdit)
	ON_EN_CHANGE(IDC_MANAGER_SEARCH_EDIT, &CIncomeForm5::OnEnChangeManagerSearchEdit)
	ON_EN_CHANGE(IDC_ETC_SEARCH_EDIT, &CIncomeForm5::OnEnChangeEtcSearchEdit)
END_MESSAGE_MAP()


// CIncomeForm5 메시지 처리기입니다.

void CIncomeForm5::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_cmbShowType.SetCurSel(0);
	m_cmbShowType.SetDroppedWidth(100);

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl함수의 순서중요함
		GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO));	//반드시 InsertColumn앞에 있어야함

	m_List.InsertColumn(0,"생성시점",LVCFMT_LEFT, 120);
	m_List.InsertColumn(1,"기사번호",LVCFMT_CENTER, 65);
	m_List.InsertColumn(2,"기사명",LVCFMT_LEFT, 80);
	m_List.InsertColumn(3,"차감",LVCFMT_RIGHT, 70);
	m_List.InsertColumn(4,"입금",LVCFMT_RIGHT, 70);
	m_List.InsertColumn(5,"타입",LVCFMT_LEFT, 150);
	m_List.InsertColumn(6,"담당자",LVCFMT_LEFT, 80);
	m_List.InsertColumn(7,"비고",LVCFMT_LEFT, 250);
	m_List.InsertColumn(8,"오더적요",LVCFMT_LEFT, 250);
	m_List.InsertColumn(9,"잔액(원)",LVCFMT_RIGHT, 70);
	m_List.InsertColumn(10,"오더변경",LVCFMT_CENTER, 70);
	m_List.InsertColumn(11,"발주사",LVCFMT_CENTER, 80);

	m_List.InsertSearchAllColumn(1);
	m_List.InsertSearchAllColumn(2);
	m_List.InsertSearchAllColumn(5);
	m_List.InsertSearchAllColumn(7);

	m_List.InsertTypeList("취소벌금", 6, "취소벌금");
	m_List.InsertTypeList("선입금", 6, "선입금");
	m_List.InsertTypeList("보험료", 6, "보험");
	m_List.InsertTypeList("프로그램비", 6, "프로그램");
	m_List.InsertTypeList("가불", 6, "가불");

	m_edtRNoSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRNoSearch.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "기사번호");
	m_edtRNameSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRNameSearch.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "기사명");
	m_edtManagerSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtManagerSearch.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "담당자");
	m_edtEtcSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtEtcSearch.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "비고");
	
	m_List.LoadReportOrder("CIncomeForm5", "m_List");

	SetResize(IDC_LIST1, sizingRightBottom);
}

void CIncomeForm5::OnBnClickedRefreshBtn()
{
	if(m_nPreCompany > 0 && m_nPreRNo > 0)
		RefreshOneRider(m_nPreCompany, m_nPreRNo);
	else
		RefreshList();
}

void CIncomeForm5::RefreshOneRider(long nCompany, long nRNo)
{
	m_nPreCompany = nCompany;
	m_nPreRNo = nRNo;
	m_edtRNoSearch.EnableWindow(FALSE);

	UpdateData(TRUE);

	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_log_for_one_rider");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	CMkRecordset pRs(m_pMkDb);
	pRs.Execute(&pCmd);

	FillReport(&pRs);
}

void CIncomeForm5::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);


	//if((m_ei.dtTodayBound - COleDateTimeSpan(0, -3, 0, 0)) > m_dtFrom)
	//{
	//	if(!LF->POWER_CHECK(7021, "통장식로그 이전데이터 검색", TRUE))
	//		return;
	//}

	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_log_for_new_3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_strRNo));
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	CMkRecordset pRs(m_pMkDb);
	pRs.Execute(&pCmd);

	FillReport(&pRs);
}

void CIncomeForm5::FillReport(CMkRecordset *rs)
{
	m_List.DeleteAllItems();

	long nRNo, nWNo, nBalance, nCount;
	CString strRName;
	COleDateTime dtGenerate;
	long nState, nAmount, nTNo, nOrderCompanyR, nOrderTNo;
	CString strEtc, strOrderEtc;
	int nItem = 0;
	char buffer[20];

	while(!rs->IsEOF())
	{
		rs->GetFieldValue("nRNo", nRNo);
		rs->GetFieldValue("sRName", strRName);
		rs->GetFieldValue("dtGenerate", dtGenerate);
		rs->GetFieldValue("nState", nState);
		rs->GetFieldValue("nAmount", nAmount);
		rs->GetFieldValue("nWNo", nWNo);
		rs->GetFieldValue("sEtc", strEtc);
		rs->GetFieldValue("sOrderEtc", strOrderEtc);
		rs->GetFieldValue("nBalance", nBalance);
		rs->GetFieldValue("nCount", nCount);
		rs->GetFieldValue("nTNo", nTNo); 
		rs->GetFieldValue("nOrderCompanyR", nOrderCompanyR); 
		rs->GetFieldValue("nEtc1", nOrderTNo); 

		m_List.InsertItem(nItem, dtGenerate.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(nItem, 1, ltoa(nRNo, buffer, 10));
		m_List.SetItemText(nItem, 2, strRName);

		if((nState >= 40 && nState <= 63) || nState == 61 || nState == 70 || nState == 71
			|| nState == 200 || nState == 201)
			m_List.SetItemText(nItem, 3, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		if((nState >= 10 && nState <= 39) || nState == 100 || nState == 101)
			m_List.SetItemText(nItem, 4, nAmount == -1 ? "-" : LF->GetMyNumberFormat(nAmount));

		m_List.SetItemText(nItem, 5, LF->GetFixedDepositStateString(nState));
		m_List.SetItemText(nItem, 6, (nWNo == 100000) ? "서버" : ltoa(nWNo, buffer, 10));
		m_List.SetItemText(nItem, 7, strEtc); 
		m_List.SetItemText(nItem, 8, strOrderEtc);
		m_List.SetItemText(nItem, 9, nBalance == -1 ? "-" : LF->GetMyNumberFormat(nBalance));
		m_List.SetItemText(nItem, 10, nCount != 0 ? (CString)itoa(nCount, buffer, 10) + "회" : "");
		m_List.SetItemText(nItem, 11, m_ci.GetShareCompanyName(nOrderCompanyR));
		m_List.SetItemData(nItem, nState);
		m_List.SetItemLong(nItem, nTNo);
		m_List.SetItemLong2(nItem, nOrderCompanyR);
		m_List.SetItemLong3(nItem, nOrderTNo);

		nItem++;
		rs->MoveNext();
	}

	CheckFilter();

	rs->Close();
}


void CIncomeForm5::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CIncomeForm5::OnViewExcel()
{
	if(!LF->POWER_CHECK(7900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 502, m_List.GetItemCount());  
	m_List.ToExcel();
}


void CIncomeForm5::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CIncomeForm5::OnEnChangeXtplistctrlEdit()
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

	ListFilter();
}

void CIncomeForm5::ListFilter()
{
	long nShowType = m_cmbShowType.GetCurSel();

	if(nShowType == 0) return;

	CXTPGridRecords *pRecords = m_List.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		if(pRecord->IsVisible() == FALSE)
			continue;

		CString sMinus = pRecord->GetItem(3)->GetCaption(NULL);
		CString sPlus = pRecord->GetItem(4)->GetCaption(NULL);

		if((nShowType == 1) && (sMinus.GetLength() == 0))
			pRecord->SetVisible(FALSE);
		else if((nShowType == 2) && (sPlus.GetLength() == 0))
			pRecord->SetVisible(FALSE);
	}

	m_List.Populate();

}

void CIncomeForm5::OnCbnSelchangeXtplistctrlTypeCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CIncomeForm5::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nOrderTNo = m_List.GetItemLong3(pRecord);

	if(nOrderTNo <= 0)
		return;

	CString sCName; long nState;

	if(LF->IsCrossOrder(nOrderTNo, sCName, nState))
	{ 
		COrderLogDetailDlg DetailLog;
		//DetailLog.m_pCurDb = IsSecondServerOrder(nSelItem) ? m_pMkSecondDb : m_pMkDb;
		DetailLog.m_nTNo = nOrderTNo;
		DetailLog.m_bCross = TRUE;
		DetailLog.DoModal();

		return;
	}

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	if(LU->GetRcpView())
	{
		LU->GetRcpDlgAdmin()->CreateRcpDlg(NULL,
			sCName,
			nOrderTNo, 
			nState, "", FALSE, -1, 0, 0, FALSE, "");
	}		
	else
	{
		MessageBox("접수탭으로 이동한 후 다시시도하세요", "확인", MB_ICONINFORMATION);
	}
}

void CIncomeForm5::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol == 11)
	{
		long nOrderCompany = m_List.GetItemLong2(nRow);
		CString strItem = "";

		CMkCommand pCmd(m_pMkDb, "select_company_info_nCompany");
		pCmd.AddParameter(nOrderCompany);
		CMkParameter *parOut = pCmd.AddParameter(typeString, typeOutput, 100, "");

		if(!pCmd.Execute())
			return;

		parOut->GetValue(strItem);

		if(strItem.IsEmpty())
			return;

		MessageBox(strItem, "확인", MB_ICONINFORMATION);			

		return;
	}
	else if(nCol == 10)
	{
		long nTNo = m_List.GetItemLong3(nRow);
		if(nTNo <= 0)
			return;

		COrderLogDetailDlg DetailLog;
		DetailLog.m_nTNo = nTNo;
		DetailLog.m_bCross = TRUE;
		DetailLog.DoModal();
	}	
}


void CIncomeForm5::OnCbnSelchangeShowTypeCombo()
{
	CheckFilter();
}

void CIncomeForm5::OnEnChangeRnoSearchEdit()
{
	CheckFilter();
}

void CIncomeForm5::OnEnChangeRnameSearchEdit()
{
	CheckFilter();
}

void CIncomeForm5::OnEnChangeManagerSearchEdit()
{
	CheckFilter();
}

void CIncomeForm5::OnEnChangeEtcSearchEdit()
{
	CheckFilter();
}

void CIncomeForm5::CheckFilter()
{
	CString strShRNo; m_edtRNoSearch.GetWindowText(strShRNo);
	CString strShRName; m_edtRNameSearch.GetWindowText(strShRName);
	CString strShManager; m_edtManagerSearch.GetWindowText(strShManager);
	CString strShEtc; m_edtEtcSearch.GetWindowText(strShEtc);

	CString strManager1, strManager2, strManager3, strManager4, strManager5;
	GetStringEmpty(strShManager, strManager1, strManager2, strManager3, strManager4, strManager5);

	long nShowType = m_cmbShowType.GetCurSel();

	CXTPGridRecords *pRecords = m_List.GetRecords();
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(2)->GetCaption(NULL);
		CString strManager = pRecord->GetItem(6)->GetCaption(NULL);
		CString strEtc = pRecord->GetItem(7)->GetCaption(NULL);
		CString strOrderEtc = pRecord->GetItem(8)->GetCaption(NULL);
		long nState = (long)m_List.GetItemData(pRecord);
 
		/* 
		if(strRNo.Find(strShRNo) < 0 ||
			strRName.Find(strShRName) < 0 ||  
			strEtc.Find(strShEtc) < 0 ||
			
			((strManager.Find(strManager1) < 0 && !strManager1.IsEmpty()) || 
				(strManager.Find(strManager2) < 0 && !strManager2.IsEmpty()) ||
				(strManager.Find(strManager3) < 0 && !strManager3.IsEmpty()) ||
				(strManager.Find(strManager4) < 0 && !strManager4.IsEmpty()) ||
				(strManager.Find(strManager5) < 0 && !strManager5.IsEmpty()) )
			)
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
		*/

		if(strRNo.Find(strShRNo) >= 0 &&
			strRName.Find(strShRName) >= 0 &&  
			(strEtc.Find(strShEtc) >= 0 || strOrderEtc.Find(strShEtc) >= 0))
		{
			if(strManager1.IsEmpty() &&
				strManager2.IsEmpty() &&
				strManager3.IsEmpty() &&
				strManager4.IsEmpty() &&
				strManager5.IsEmpty())
				pRecord->SetVisible(TRUE);
			else
			{
				if((strManager.Find(strManager1) >= 0 && !strManager1.IsEmpty()) ||
					(strManager.Find(strManager2) >= 0 && !strManager2.IsEmpty()) ||
					(strManager.Find(strManager3) >= 0 && !strManager3.IsEmpty()) ||
					(strManager.Find(strManager4) >= 0 && !strManager4.IsEmpty()) ||
					(strManager.Find(strManager5) >= 0 && !strManager5.IsEmpty()) )
					pRecord->SetVisible(TRUE);
				else
					pRecord->SetVisible(FALSE);
			}
		}			
		else
			pRecord->SetVisible(FALSE);



		if(pRecord->IsVisible() == FALSE)
			continue;

		CString sMinus = pRecord->GetItem(3)->GetCaption(NULL);
		CString sPlus = pRecord->GetItem(4)->GetCaption(NULL);

		if((nShowType == 1) && (sMinus.GetLength() == 0))
			pRecord->SetVisible(FALSE);
		else if((nShowType == 2) && (sPlus.GetLength() == 0))
			pRecord->SetVisible(FALSE);
		else if(nShowType == 3 && nState != 63)
			pRecord->SetVisible(FALSE);
		else if(nShowType == 4 && nState != 31)
			pRecord->SetVisible(FALSE);

	}

	m_List.Populate();
}

void CIncomeForm5::GetStringEmpty(CString strShManager, CString &strManager1, CString &strManager2, CString &strManager3, CString &strManager4, CString &strManager5)
{
	strManager1 = strManager2 = strManager3 = strManager4 = strManager5 = "";

	long nItem = 0;

	if(strShManager.IsEmpty())
		return;

	strShManager += " ";

	long nFind = 0;
	long nSecondFind = 0;

	while(TRUE)
	{
		nSecondFind = strShManager.Find(" ", nFind);
		CString strItem = strShManager.Mid(nFind, nSecondFind - nFind);

		if(nSecondFind == -1 || nItem > 5)
			break;

		if(nItem == 0) strManager1 = strItem;
		else if(nItem == 1) strManager2 = strItem;
		else if(nItem == 2) strManager3 = strItem;
		else if(nItem == 3) strManager4 = strItem;
		else if(nItem == 4) strManager5 = strItem;

		nFind = nSecondFind + 1;
		nItem++;
	}

}