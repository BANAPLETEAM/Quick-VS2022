// CustomerForm29.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm35.h"
#include "CustomerMileageDlg.h"
#include "EtcDlg.h"
#include "WithdrawManualDlg.h"
#include "RequestDrawingDlg.h"

#define WD_STATE_ING_CUSTOMER 0
#define WD_STATE_ING_VAN 1
#define WD_STATE_FAIL 2
#define WD_STATE_COMPLETE 3
#define WD_STATE_CANCEL 4
// CReportForm35

IMPLEMENT_DYNCREATE(CReportForm35, CMyFormView)

CReportForm35::CReportForm35()
	: CMyFormView(CReportForm35::IDD)
{
	m_pCustomerMileageDlg = NULL;
}

CReportForm35::~CReportForm35()
{
}

void CReportForm35::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CReportForm35, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CReportForm35::OnBnClickedRefreshButton)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, &CReportForm35::OnCbnSelchangeTypeCombo)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_WITHDRAW, OnWithdraw)
	ON_COMMAND(ID_WITHDRAW_MANUAL, OnWithdrawManual)
	ON_COMMAND(ID_WITHDRAW_CANCEL, OnWithdrawCancel)
	ON_COMMAND(ID_SHOW_MILEAGE_LOG, OnShowMileageLog)
	ON_COMMAND(ID_UPDATE_ETC, OnUpdateEtc)
	ON_COMMAND(ID_CHECK_ITEM, OnCheckItem)
	ON_COMMAND(ID_TO_EXCEL, OnToExcel)

	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)

	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm35::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CReportForm35 진단입니다.

#ifdef _DEBUG
void CReportForm35::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm35::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm35 메시지 처리기입니다.

void CReportForm35::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT, sizingRightBottom);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth(); 

	m_cmbType.SetCurSel(1);

	m_lstReport.InsertColumn(0, "지사명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "요청일시", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(2, "전화번호", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "요청한마일리지", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(4, "출금할금액", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(5, "실제출금액", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(6, "출금후마일리지", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(7, "은행", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(8, "계좌번호", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(9, "예금주", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(10, "상태", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(11, "출금(실패)일자", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(12, "작업자", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(13, "적요", LVCFMT_LEFT, 200);
	m_lstReport.InsertColumn(14, "접수원수동입력여부", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(15, "확인여부", LVCFMT_LEFT, 150);
	m_lstReport.Populate();
}

CString CReportForm35::GetMileageWithdrawState(long nState)
{
	if(nState == WD_STATE_ING_CUSTOMER)
		return "출금요청중(고객)";
	else if(nState == WD_STATE_ING_VAN)
		return "출금요청중(은행)";
	else if(nState == WD_STATE_COMPLETE)
		return "출금완료";
	else if(nState == WD_STATE_FAIL)
		return "출금실패";
	else if(nState == WD_STATE_CANCEL)
		return "출금취소";

	return "N/A";
}

void CReportForm35::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	//nState -- 0 출금요청중(고객), 1 출금요청중(밴사로요청), 2 출금요청실패, 3 출금요청완료

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_mileage_withdraw_log_1");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		GetRecordData(NULL, &rs);
		rs.MoveNext();
	}

	OnCbnSelchangeTypeCombo();
}

void CReportForm35::OnBnClickedRefreshButton()
{
	RefreshList();
}

void CReportForm35::OnCbnSelchangeTypeCombo()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);
	long nIndex = m_cmbType.GetCurSel();

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	BOOL bFindCombo = FALSE, bFindEdit = FALSE;

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strPhone = m_lstReport.GetItemText(pRecord, 2);
		strPhone.Replace("-", "");
		CString strBank = m_lstReport.GetItemText(pRecord, 5);
		CString strAccount = m_lstReport.GetItemText(pRecord, 6);
		CString strAccountOwner = m_lstReport.GetItemText(pRecord, 7);

		long nState = m_lstReport.GetItemLong2(pRecord);

		if(strPhone.Find(strSearch) >= 0 ||
			strBank.Find(strSearch) >= 0 ||
			strAccount.Find(strSearch) >= 0 ||
			strAccountOwner.Find(strSearch) >= 0)
		{
			bFindCombo = TRUE;
		}
		else
			bFindCombo = FALSE;

		if(nIndex == 0)
			bFindEdit = TRUE;
		else
		{
			if(nIndex == 1 && (nState == WD_STATE_ING_CUSTOMER || nState == WD_STATE_ING_VAN))
				bFindEdit = TRUE;
			else if(nIndex == 2 && nState == WD_STATE_COMPLETE)
				bFindEdit = TRUE;
			else if(nIndex == 3 && nState == WD_STATE_FAIL)
				bFindEdit = TRUE;
			else if(nIndex == 4 && nState == WD_STATE_CANCEL)
				bFindEdit = TRUE;
			else 
				bFindEdit = FALSE;
		}

		pRecord->SetVisible(bFindCombo && bFindEdit);
	}

	m_lstReport.Populate();
}

void CReportForm35::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);

	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(17);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm35::OnToExcel()
{
	if(!LF->POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 331, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}


CXTPGridRecord* CReportForm35::GetRecordItem(long &nID, long &nState)
{
	nID = -1;
	nState = -1;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return NULL;

	nID = m_lstReport.GetItemLong(pRecord);
	nState = m_lstReport.GetItemLong2(pRecord);

	return pRecord;
}

void CReportForm35::OnWithdraw()
{
	/*
	long nID, nState;

	if(!GetRecordItem(nID, nState))
		return;

	if(nState != 0)
	{
		MessageBox("출금 요청중인 상태만 출금이 가능합니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CRequestDrawingDlg dlg;
	dlg.m_nMileageID = nID;
	dlg.DoModal();	
	*/
}

void CReportForm35::OnWithdrawManual()
{
	long nID, nState;

	CXTPGridRecord *pRecord = GetRecordItem(nID, nState);

	if(!pRecord)
		return;

	if(nState != WD_STATE_ING_CUSTOMER)
	{
		MessageBox("고객 출금 요청중인 상태만 수동출금 할수 있습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strCharge = pRecord->GetItem(4)->GetCaption(NULL);
	strCharge.Replace(",", "");

	CWithdrawManualDlg dlg;
	dlg.m_nCharge = atoi(strCharge);
	
	if(dlg.DoModal() != IDOK)
		return;

	CMkCommand cmd(m_pMkDb, "update_customer_mileage_withdraw_manual");
	cmd.AddParameter(nID);
	cmd.AddParameter(dlg.m_nCharge);
	cmd.AddParameter(dlg.m_dtWithdraw);
	cmd.AddParameter(dlg.m_strEtc);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	
	if(cmd.Execute())
		RefreshOne(pRecord, nID);

}

void CReportForm35::OnWithdrawCancel()
{
	long nID, nState;

	CXTPGridRecord *pRecord = GetRecordItem(nID, nState);

	if(!pRecord)
		return;

	if(nState != WD_STATE_ING_CUSTOMER)
	{
		MessageBox("고객 출금 요청중인 상태만 취소 하실수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand cmd(m_pMkDb, "update_customer_mileage_request_cancel");
	cmd.AddParameter(nID);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
		RefreshOne(pRecord, nID);
}

void CReportForm35::RefreshOne(CXTPGridRecord *pRecord, long nID)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_mileage_withdraw_log_one_1");

	cmd.AddParameter(nID);

	if(!rs.Execute(&cmd))
		return;

	GetRecordData(pRecord, &rs);
	m_lstReport.RedrawControl();
}

void CReportForm35::GetRecordData(CXTPGridRecord *pRecord, CMkRecordset *rs)
{
	if(rs->GetRecordCount() == 0)
		return;

	COleDateTime dtRequest, dtWithdraw, dtCheck;
	long nCompany, nRequestMileage, nWithdrawCharge, nBankID, nState, nWCompany, nID, nCNo, nRealWithdrawCharge, nResultMileage;
	CString strPhone, strAccount, strAccountOwner, strWName, strEtc, strManualInput, strCheckWName;
	long nCheckWCompany, nCheckWNo;

	rs->GetFieldValue("dtRequest", dtRequest);
	rs->GetFieldValue("dtWithdraw", dtWithdraw);
	rs->GetFieldValue("nCompany", nCompany);
	rs->GetFieldValue("nRequestMileage", nRequestMileage);
	rs->GetFieldValue("nWithdrawCharge", nWithdrawCharge);
	rs->GetFieldValue("nBankID", nBankID);
	rs->GetFieldValue("nState", nState);
	rs->GetFieldValue("nWCompany", nWCompany);
	rs->GetFieldValue("nID", nID);
	rs->GetFieldValue("sPhone", strPhone);
	rs->GetFieldValue("sAccount", strAccount);
	rs->GetFieldValue("sAccountOwner", strAccountOwner);
	rs->GetFieldValue("sWName", strWName);
	rs->GetFieldValue("nCNo", nCNo);
	rs->GetFieldValue("sEtc", strEtc);
	rs->GetFieldValue("nRealWithdrawCharge", nRealWithdrawCharge);
	rs->GetFieldValue("sManualInput", strManualInput);
	rs->GetFieldValue("nCheckWCompany", nCheckWCompany);
	rs->GetFieldValue("nCheckWNo", nCheckWNo);
	rs->GetFieldValue("sCheckWName", strCheckWName);
	rs->GetFieldValue("dtCheck", dtCheck);
	rs->GetFieldValue("nResultMileage", nResultMileage);

	if(pRecord == NULL)
	{
		long nCount = m_lstReport.GetRecords()->GetCount();
		pRecord = m_lstReport.InsertItemReturn(nCount, m_ci.GetBranchName(nCompany));
	}
	
	m_lstReport.SetItemText(pRecord, 1, dtRequest.Format("%m-%d %H:%M"));
	m_lstReport.SetItemText(pRecord, 2, LF->GetDashPhoneNumber(strPhone));
	m_lstReport.SetItemText(pRecord, 3, LF->GetMyNumberFormat(nRequestMileage));
	m_lstReport.SetItemText(pRecord, 4, LF->GetMyNumberFormat(nWithdrawCharge));
	m_lstReport.SetItemText(pRecord, 5, LF->GetMyNumberFormat(nRealWithdrawCharge));
	m_lstReport.SetItemText(pRecord, 6, LF->GetMyNumberFormat(nResultMileage));
	m_lstReport.SetItemText(pRecord, 7, LF->GetBankName(nBankID));
	m_lstReport.SetItemText(pRecord, 8, strAccount);
	m_lstReport.SetItemText(pRecord, 9, strAccountOwner);
	m_lstReport.SetItemText(pRecord, 10, GetMileageWithdrawState(nState));

	if(nState == WD_STATE_FAIL || nState == WD_STATE_COMPLETE)
	{
		m_lstReport.SetItemText(pRecord, 11, dtWithdraw.Format("%m-%d %H:%M"));
		m_lstReport.SetItemText(pRecord, 12, m_ci.GetBranchName(nWCompany) + "/" + strWName);
	}
	else
	{
		m_lstReport.SetItemText(pRecord, 11, "");
		m_lstReport.SetItemText(pRecord, 12, "");
	}

	m_lstReport.SetItemText(pRecord, 13, strEtc);
	m_lstReport.SetItemText(pRecord, 14, strManualInput);

	if(dtCheck.m_status != 2)
		m_lstReport.SetItemText(pRecord, 15, dtCheck.Format("[%Y-%m-%d %H:%M]") + "/" + LF->GetStringFromLong(nCheckWNo, TRUE) + "," + strCheckWName);

	m_lstReport.SetItemLong(pRecord, nID);
	m_lstReport.SetItemLong2(pRecord, nState);
	m_lstReport.SetItemLong3(pRecord, nCNo);
}

void CReportForm35::OnShowMileageLog()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	if(m_pCustomerMileageDlg == NULL)
	{
		m_pCustomerMileageDlg = new CCustomerMileageDlg(this);
		m_pCustomerMileageDlg->m_nCNo = m_lstReport.GetItemLong3(pRecord);
		m_pCustomerMileageDlg->Create(CCustomerMileageDlg::IDD, this);
	}

	//m_pCustomerMileageDlg->m_pCurDb = m_pMkDb;
	m_pCustomerMileageDlg->m_nCNo = m_lstReport.GetItemLong3(pRecord);
	m_pCustomerMileageDlg->RefreshList();
	m_pCustomerMileageDlg->ShowWindow(SW_SHOW);
}

void CReportForm35::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	long nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol == 13)
		OnUpdateEtc();
	if(nCol == 14)
		OnShowMileageLog();
}

void CReportForm35::OnCheckItem()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	if(MessageBox("마일리지 수동 입력 여부를 확인 하셨습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);
	long nCNo = m_lstReport.GetItemLong3(pRecord);

	CMkCommand cmd(m_pMkDb, "customer_mileage_log_check");
	CMkParameter *par = cmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	cmd.AddParameter(nID);
	cmd.AddParameter(nCNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(!cmd.Execute())
		return;

	long nRet; par->GetValue(nRet);

	if(nRet == 1)
	{
		MessageBox("이미 확인하였습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	RefreshOne(pRecord, nID);

}

void CReportForm35::OnUpdateEtc()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CEtcDlg dlg;
	dlg.m_strEtc = pRecord->GetItem(12)->GetCaption(NULL);

	if(dlg.DoModal() != IDOK)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);

	CMkCommand cmd(m_pMkDb, "upadte_customer_mileage_withdraw_etc");
	cmd.AddParameter(nID);
	cmd.AddParameter(dlg.m_strEtc);

	if(cmd.Execute())
		RefreshOne(pRecord, nID);
}
void CReportForm35::OnEnChangeSearchEdit()
{
	OnCbnSelchangeTypeCombo();
}
