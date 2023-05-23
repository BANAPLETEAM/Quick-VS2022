// StatForm7.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatForm7.h" 


// CStatForm7

IMPLEMENT_DYNCREATE(CStatForm7, CMyFormView)

CStatForm7::CStatForm7()
	: CMyFormView(CStatForm7::IDD)
{
	m_bFirst = TRUE;
}

CStatForm7::~CStatForm7()
{
}

void CStatForm7::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelp);
	DDX_Control(pDX, IDC_DAILY_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_DAILY_SUB_REPORT, m_lstSubReport);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_HELP_STATIC2, m_stcHelp2);
}

BEGIN_MESSAGE_MAP(CStatForm7, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CStatForm7::OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_DAILY_REPORT, OnReportItemDblClick)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CStatForm7::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CStatForm7 진단입니다.

#ifdef _DEBUG
void CStatForm7::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatForm7::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatForm7 메시지 처리기입니다.

void CStatForm7::OnBnClickedRefreshBtn()
{
	RefreshList();	
}

void CStatForm7::SetHelpText(long nBalance)
{
	CBranchInfo *pBi = LF->GetCurBranchInfo();

	CString sTemp = "", sTemp1 = "";
	
	if(!pBi->bIntegrated)
	{
		sTemp.Format("[%s]지사는 [%s]지사의 충전금을 사용합니다.", pBi->strBranchName, m_ci.GetBranchName(pBi->nSmsChargeCompany));
		sTemp1.Format("[%s]지사의 충전금은 [%s]원입니다.", m_ci.GetBranchName(pBi->nSmsChargeCompany), LF->GetMyNumberFormat(nBalance));
	}
	else 
	{
		sTemp = "해당 지사를 선택해 주세요.";
		sTemp1 = "";
	}

	m_stcHelp.SetWindowText(sTemp);
	m_stcHelp2.SetWindowText(sTemp1);
}

void CStatForm7::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_stcHelp.SetAlign(DT_LEFT);
	m_stcHelp2.SetAlign(DT_LEFT);

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuWeek();

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(1, "잔액", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(2, "이용건수", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(3, "이용금액", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(4, "충전건수", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(5, "충전금액", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(6, "기타건수", LVCFMT_LEFT, 60);

	m_lstReport.Populate();

	m_lstSubReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 70);
	m_lstSubReport.InsertColumn(1, "건수", LVCFMT_LEFT, 40);
	m_lstSubReport.InsertColumn(2, "차감액", LVCFMT_LEFT, 50);
	m_lstSubReport.InsertColumn(3, "입금액", LVCFMT_LEFT, 50);
	m_lstSubReport.InsertColumn(4, "잔액", LVCFMT_LEFT, 60);
	m_lstSubReport.InsertColumn(5, "적요", LVCFMT_LEFT, 150);
	m_lstSubReport.InsertColumn(6, "접수자", LVCFMT_LEFT, 60);
	m_lstSubReport.InsertColumn(7, "오더번호", LVCFMT_LEFT, 70);
	m_lstSubReport.InsertColumn(8, "전화번호", LVCFMT_LEFT, 90);
	m_lstSubReport.InsertColumn(9, "내용", LVCFMT_LEFT, 150);

	m_lstSubReport.Populate();

	SetResize(IDC_DAILY_REPORT, sizingBottom);
	SetResize(IDC_DAILY_SUB_REPORT, sizingRightBottom);
}

void CStatForm7::RefreshList()
{
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_sms_save_log_daily_1");
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(LF->GetCurBranchInfo()->nSmsChargeCompany);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	long nRet; pPar->GetValue(nRet);

	SetHelpText(nRet);

	CString sDate;
	long nUseCount, nUseCharge, nSaveCount, nSaveCharge, nEtcCount, nBalance, nIndex;
	long nItem = 0;

	m_lstReport.InsertItem(nItem, "금일");
	m_lstReport.SetItemLong(nItem++, 0);

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nIndex", nIndex); 
		pRs.GetFieldValue("sDate", sDate);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nUseCharge", nUseCharge);
		pRs.GetFieldValue("nSaveCount", nSaveCount);
		pRs.GetFieldValue("nSaveCharge", nSaveCharge);
		pRs.GetFieldValue("nEtcCount", nEtcCount);
		pRs.GetFieldValue("nBalance", nBalance);

		m_lstReport.InsertItem(nItem, GetBetweenDate(sDate));
		m_lstReport.SetItemText(nItem, 1, LF->GetMyNumberFormat(nBalance));
		m_lstReport.SetItemText(nItem, 2, LF->GetMyNumberFormat(nUseCount));
		m_lstReport.SetItemText(nItem, 3, LF->GetMyNumberFormat(nUseCharge));
		m_lstReport.SetItemText(nItem, 4, LF->GetMyNumberFormat(nSaveCount));
		m_lstReport.SetItemText(nItem, 5, LF->GetMyNumberFormat(nSaveCharge));
		m_lstReport.SetItemText(nItem, 6, LF->GetMyNumberFormat(nEtcCount));
		m_lstReport.SetItemLong(nItem++, nIndex);
 
		pRs.MoveNext();
	}
 
	m_lstReport.Populate();

	if(m_lstReport.GetItemCount() > 0) 
	{
		CXTPGridRow *pRow = m_lstReport.GetRows()->GetAt(0);
		m_lstReport.GetSelectedRows()->Select(pRow);
		RefreshSubList();
	}
}

CString CStatForm7::GetBetweenDate(CString sDate)
{
	CString sTemp = "";
	COleDateTime dtFrom, dtTo;
	dtFrom.SetDateTime(atoi(sDate.Left(4)), atoi(sDate.Mid(4, 2)), atoi((sDate.Mid(6, 2))), 0, 0, 0);
	dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);

	sTemp.Format("%d월%d일 0시 ~ %d월%d일 0시", dtFrom.GetMonth(), dtFrom.GetDay(), dtTo.GetMonth(), dtTo.GetDay());
	return sTemp;
}

void CStatForm7::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	RefreshSubList();
}

void CStatForm7::RefreshSubList()
{
	m_lstSubReport.DeleteAllItems(); 

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL){MessageBox("행을 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pRows->GetCount() == 0){MessageBox("행을 선택하세요", "확인", MB_ICONINFORMATION); return;};

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	long nIndex = m_lstReport.GetItemLong(pRecord);

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_sms_save_log_one_day");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nSmsChargeCompany);
	pCmd.AddParameter(nIndex);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	COleDateTime dtGenerate;
	long nDeposit, nBalance, nTNo, nType, nCount;
	CString sWName, sEtc, strPhone, strMsg;

	long nSUseCount = 0, nSUseCharge = 0, nSSaveCount = 0, nSSaveCharge = 0, nSEtcCount = 0, nSBalance = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("sSendPhone", strPhone);
		pRs.GetFieldValue("sMsg", strMsg);
		pRs.GetFieldValue("nTNo", nTNo);

		if(nIndex == 0)
		{ 
			if(nType == 10)
			{
				nSUseCount += nCount;
				nSUseCharge += nDeposit;
			}
			else if(nType == 20)
			{
				nSSaveCount += nCount;
				nSSaveCharge += nDeposit;
			}
			else if(nType == 30)
				nSEtcCount += nCount;
 
			if((i+1) == pRs.GetRecordCount()) 
				nSBalance = nBalance;
		}

		m_lstSubReport.InsertItem(i, dtGenerate.Format("%m-%d %H:%M"));
		m_lstSubReport.SetItemText(i, 1, LF->GetMyNumberFormat(nCount));

		if(nType == 10)
		{
			m_lstSubReport.SetItemText(i, 2, LF->GetMyNumberFormat(abs(nDeposit)));
			m_lstSubReport.SetItemText(i, 3, "");
		}
		else if(nType == 20)
		{
			m_lstSubReport.SetItemText(i, 2, "");
			m_lstSubReport.SetItemText(i, 3, LF->GetMyNumberFormat(abs(nDeposit)));
		}

		m_lstSubReport.SetItemText(i, 4, LF->GetMyNumberFormat(nBalance));
		m_lstSubReport.SetItemText(i, 5, sEtc);
		m_lstSubReport.SetItemText(i, 6, sWName);
		m_lstSubReport.SetItemText(i, 7, LF->RemoveZero((CString)itoa(nTNo, buffer, 10)));
		m_lstSubReport.SetItemText(i, 8, LF->GetDashPhoneNumber(strPhone));
		m_lstSubReport.SetItemText(i, 9, strMsg);
		m_lstSubReport.SetItemLong(i, nType);

		pRs.MoveNext();
	}

	m_lstSubReport.Populate();

	if(nIndex == 0)
	{
		(pRecord->GetItem(1))->SetCaption(LF->GetMyNumberFormat(nSBalance));
		(pRecord->GetItem(2))->SetCaption(LF->GetMyNumberFormat(nSUseCount));
		(pRecord->GetItem(3))->SetCaption(LF->GetMyNumberFormat(nSUseCharge));
		(pRecord->GetItem(4))->SetCaption(LF->GetMyNumberFormat(nSSaveCount));
		(pRecord->GetItem(5))->SetCaption(LF->GetMyNumberFormat(nSSaveCharge));
		(pRecord->GetItem(6))->SetCaption(LF->GetMyNumberFormat(nSEtcCount));

		m_lstReport.Populate();
	}
}

void CStatForm7::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rc, rc1;

	m_lstReport.GetWindowRect(rc);
	m_lstSubReport.GetWindowRect(rc1);

	if(rc.PtInRect(point))
		m_bLeftList = TRUE;
	else if(rc1.PtInRect(point))
		m_bLeftList = FALSE;
	else 
		return;

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU); 
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(2); 
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,this);
}

void CStatForm7::OnViewExcel()
{
	CXTPGridControl *pControl = m_bLeftList ? &m_lstReport : &m_lstSubReport;

	if(!LF->POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 608, m_ui.nWNo, pControl->GetRecords()->GetCount());  
	CMyExcel::ToExcel(pControl);


}
void CStatForm7::OnEnChangeSearchEdit()
{
	CString strSearch;
	GetDlgItem(IDC_SEARCH_EDIT)->GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstSubReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString str1 = pRecord->GetItem(7)->GetCaption(NULL);
		CString str2 = pRecord->GetItem(8)->GetCaption(NULL);
		CString str3 = pRecord->GetItem(9)->GetCaption(NULL);

		str2.Replace("-", "");

		if(str1.Find(strSearch) >= 0 ||
			str2.Find(strSearch) >= 0 ||
			str3.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstSubReport.Populate();
}
