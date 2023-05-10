// CompleteAfterEditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CompleteAfterEditDlg.h"

#include "OrderLogDetailDlg.h"
#include "VarietyDlg2.h"
#include "ShareTranferRequestDlg.h"
#include "ShareTansferMyRequest.h"

// CCompleteAfterEditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompleteAfterEditDlg, CMyDialog)
CCompleteAfterEditDlg::CCompleteAfterEditDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCompleteAfterEditDlg::IDD, pParent)
{
}

CCompleteAfterEditDlg::~CCompleteAfterEditDlg()
{
}

void CCompleteAfterEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCompleteAfterEditDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnReportItemDblClick)	
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_REQUEST_BTN, &CCompleteAfterEditDlg::OnBnClickedRequestBtn)
	ON_BN_CLICKED(IDC_MY_REQUEST_BTN, &CCompleteAfterEditDlg::OnBnClickedMyRequestBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CCompleteAfterEditDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CCompleteAfterEditDlg 메시지 처리기입니다.

BOOL CCompleteAfterEditDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	InitColumn(FALSE);
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCompleteAfterEditDlg::InitColumn(BOOL bRequest)
{  
	int nColumnCount = m_List.GetColumns()->GetCount();
	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumns *pColums = m_List.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}

	m_List.GetRecords()->RemoveAll();  

	m_List.InsertColumn(0, "요청업체", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "정산업체", LVCFMT_LEFT, 80);
	m_List.InsertColumn(2, "요청일", LVCFMT_LEFT, 80);
	m_List.InsertColumn(3, "오더번호", LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, "출발지", LVCFMT_LEFT, 90);
	m_List.InsertColumn(5, "도착지", LVCFMT_LEFT, 90);
	m_List.InsertColumn(6, "타입", LVCFMT_LEFT, 40);
	m_List.InsertColumn(7, "진행상태", LVCFMT_LEFT, 80);
	m_List.InsertColumn(8, "남은시간", LVCFMT_LEFT, 50);
	m_List.InsertColumn(9, "적요", LVCFMT_LEFT, 170);

	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);

	m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnReorder(FALSE);
	m_List.AllowEdit(FALSE);
	m_List.SetGridColor(RGB(222, 222, 222));
	m_List.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_List.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	
	m_List.Populate();
}

void CCompleteAfterEditDlg::OnBnClickedRefreshBtn()
{
    RefreshList();   	
}


void CCompleteAfterEditDlg::RefreshList()
{
	UpdateData(TRUE);
	m_List.DeleteAllItems();

	char buffer[10];
	long nTNo, nFromCompany, nToCompany, nDeposit, nType, nResult;
	COleDateTime dtGenerate;
	CString sEtc, sStart, sDest;
	COleDateTime dtResult;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_for_order_change");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nFromCompany", nFromCompany);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nResult", nResult);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("dtResult", dtResult);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);

		m_List.InsertItem(i, m_ci.GetName(nFromCompany));
		m_List.SetItemText(i, 1, m_ci.GetName(nToCompany));
		m_List.SetItemText(i, 2, dtGenerate.Format("%m-%d %H:%M"));
		m_List.SetItemText(i, 3, itoa(nTNo, buffer, 10));
		m_List.SetItemText(i, 4, sStart);
		m_List.SetItemText(i, 5, sDest);
		m_List.SetItemText(i, 6, nType == 0 ? "이체" : "청구");
		m_List.SetItemText(i, 7, GetRequestState(nResult));
		m_List.SetItemText(i, 8, nResult == 0 ? GetLeftDate(dtGenerate) : "");
		m_List.SetItemText(i, 9, sEtc);
		m_List.SetItemLong(i, nType);
		m_List.SetItemLong2(i, nResult);

		pRs.MoveNext();
	}

	m_List.Populate();
}

CString CCompleteAfterEditDlg::GetLeftDate(COleDateTime dtDate)
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	COleDateTime dtTwoDay = dtDate + COleDateTimeSpan(2, 0, 0, 0);

	COleDateTimeSpan span = dtTwoDay - dtCur;

	long nHour = span.GetTotalHours();

	CString sTemp = "";
	sTemp.Format("%d시간", nHour);

	return sTemp;
}

BOOL CCompleteAfterEditDlg::IsDifferentPayType(long nPrePayType, long nPayType)
{
	long nPre, nCur;

	if((nPrePayType == 0) || (nPrePayType == 1) || (nPrePayType == 4))
		nPre = 0;
	else
		nPre = 1;

	if((nPayType == 0) || (nPayType == 1) || (nPayType == 4))
		nCur = 0;
	else
		nCur = 1;

    if(nPre == nCur)
		return TRUE;
	else
		return FALSE;
}

BOOL CCompleteAfterEditDlg::IsDifferentState(long nPreState, long nState)
{
	long nPre, nCur;

	if((nPreState == 11) || (nPreState == 30) || (nPreState == 31) || (nPreState == 35))
		nPre = 0;
	else
		nPre = 1;

	if(LF->IsAllocOrder(nState))
		nCur = 0;
	else
		nCur = 1;

	if(nPre == nCur)
		return TRUE;
	else
		return FALSE;
	
}

CString CCompleteAfterEditDlg::GetRequestState(long nRequestState)
{
	if(nRequestState == 0)
		return "청구중";
	if(nRequestState == 1)
		return "이체거절";
	if(nRequestState == 2)
		return "정상완료";
	if(nRequestState == 3)
		return "시간경과완료";

	return "알수없음";
}

void CCompleteAfterEditDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);
 
	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	CString sTNo = ((CXTPGridRecordItemText*)(pRecord->GetItem(3)))->GetCaption(NULL);


	COrderLogDetailDlg DetailLog;
	DetailLog.m_nTNo = atoi(sTNo);
	DetailLog.m_bCross = TRUE;
	DetailLog.DoModal();
}



void CCompleteAfterEditDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nCol = pItemNotify->pColumn->GetIndex();

	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	CString sText = ((CXTPGridRecordItemText*)(pRecord->GetItem(nCol)))->GetCaption(NULL);
	long nID = m_List.GetItemData(pRecord);

	if(nCol == 7) // 승인
	{
		if(sText == "승인")
		{
			CVarietyDlg2 dlg;
			dlg.m_sTitle = "승인 사유를 입력하세요";

			if(dlg.DoModal() == IDOK)
			{
                CMkCommand pCmd(m_pMkDb, "rereport_share_account");
				pCmd.AddParameter(nID);
				pCmd.AddParameter(m_ui.nCompany);
				pCmd.AddParameter(m_ui.nWNo);
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(dlg.m_sEtc);

				if(pCmd.Execute())
				{
					MessageBox("승인하였습니다\r\n공유콜정산창에서 정산내역을 확인 하실수 있습니다", "확인", MB_ICONINFORMATION);
					RefreshList();
				}
			}
		}
	}

	if(nCol == 8) //거절
	{ 
		if(sText == "거절")
		{
			CVarietyDlg2 dlg;
			dlg.m_sTitle = "거절 사유를 입력하세요";
			if(dlg.DoModal() == IDOK)
			{
				CMkCommand pCmd(m_pMkDb, "share_account_not_agree");
				pCmd.AddParameter(nID);
				pCmd.AddParameter(m_ui.nCompany);
				pCmd.AddParameter(m_ui.nWNo);
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(dlg.m_sEtc);

				if(pCmd.Execute())
				{
					MessageBox("거절하였습니다", "확인", MB_ICONINFORMATION);
					RefreshList();
				}
			}
		}
	}
}

BOOL CCompleteAfterEditDlg::IsCash(long nPayType)
{	
	if((nPayType == 0) || (nPayType == 1) || (nPayType == 4))
		return TRUE;
	else
		return FALSE;
}
void CCompleteAfterEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd() == NULL ||
		this->GetSafeHwnd() == NULL)
		return;

	CRect rcDlg, rcList;
	GetWindowRect(rcDlg);
	m_List.GetWindowRect(rcList);
	ScreenToClient(rcDlg);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 3;
	rcList.bottom = rcDlg.bottom - 3;

	m_List.MoveWindow(rcList);
}

void CCompleteAfterEditDlg::OnBnClickedRequestBtn()
{
	CShareTranferRequestDlg dlg;

	//CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());
	//CString sBalance, sMinBalance;
	//pShareReportRateDlg->m_BalanceEdit.GetWindowText(sBalance);
	//pShareReportRateDlg->m_BasicRateEdit.GetWindowText(sMinBalance);
	//sBalance.Replace(",", "");
	//sBalance.Replace("원", "");
	//sMinBalance.Replace(",", "");
	//sMinBalance.Replace("원", "");

	int nAbilityMoney = 0;//_ttoi(sBalance) - _ttoi(sMinBalance);

	dlg.m_nAbilityMoney = GetAbilMoney();
//	dlg.m_pShareReportRateDlg1 = this;
	dlg.m_sSql = "select_transfer_request_1";

	dlg.DoModal();		
}

long CCompleteAfterEditDlg::GetAbilMoney()
{
	CMkCommand pCmd(m_pMkDb, "select_get_abil_money");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(!pCmd.Execute()) return 0;

	long nRet = 0; pPar->GetValue(nRet);

	return nRet;
}

void CCompleteAfterEditDlg::OnBnClickedMyRequestBtn()
{
	CShareTansferMyRequest pDlg;
	pDlg.DoModal();
}

void CCompleteAfterEditDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
