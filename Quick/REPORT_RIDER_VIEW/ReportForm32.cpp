// ReportForm32.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ReportForm32.h"

#define ID_APPROVAL 9000
#define ID_APPROVAL_NOT 9001
// CReportForm32

IMPLEMENT_DYNCREATE(CReportForm32, CMyFormView)

CReportForm32::CReportForm32()
	: CMyFormView(CReportForm32::IDD)
{

}

CReportForm32::~CReportForm32()
{
}

void CReportForm32::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
}

BEGIN_MESSAGE_MAP(CReportForm32, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm32::OnBnClickedRefreshBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_APPROVAL, OnApproval)
	ON_COMMAND(ID_APPROVAL_NOT, OnApprovalNot)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_RNO_EDIT, &CReportForm32::OnEnChangeRnoEdit)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, &CReportForm32::OnCbnSelchangeStateCombo)
	
END_MESSAGE_MAP()


// CReportForm32 진단입니다.

#ifdef _DEBUG
void CReportForm32::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm32::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm32 메시지 처리기입니다.

void CReportForm32::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT, sizingRightBottom);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();
;
	m_cmbState.SetCurSel(0);

	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "날짜", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(3, "기사명", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(4, "은행", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(5, "계좌번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(6, "예금주", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(7, "기사잔액", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(8, "출금요청액", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(9, "소득세", LVCFMT_RIGHT, 75);
	m_lstReport.InsertColumn(10, "주민세", LVCFMT_RIGHT, 64);
	m_lstReport.InsertColumn(11, "실제출금액", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(12, "출금여부", LVCFMT_CENTER, 70);
	m_lstReport.InsertColumn(13, "승인/취소일", LVCFMT_CENTER, 100);

	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();
}

void CReportForm32::RefreshList()
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_rider_with_draw2");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nCompany, nRNo, nReqAmount, nRealAmount, nID, nApprovalType ,nBalance;
	CString strBank, strAccount, strDepositName, strRName;
	COleDateTime dtLog, dtApproval, dtCancel;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("nBalance", nBalance);
		rs.GetFieldValue("nReqAmount", nReqAmount);
		rs.GetFieldValue("nRealAmount", nRealAmount);
		rs.GetFieldValue("sBank", strBank);
		rs.GetFieldValue("sAccount", strAccount);  
		rs.GetFieldValue("sDepositName", strDepositName);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("nApprovalType", nApprovalType);
		rs.GetFieldValue("dtLog", dtLog);
		rs.GetFieldValue("dtApproval", dtApproval);
		rs.GetFieldValue("dtCancel", dtCancel);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, dtLog.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, LF->GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 3, strRName);
		m_lstReport.SetItemText(i, 4, strBank);
		m_lstReport.SetItemText(i, 5, strAccount);
		m_lstReport.SetItemText(i, 6, strDepositName);
		m_lstReport.SetItemText(i, 7, LF->GetMyNumberFormat(nBalance));
		m_lstReport.SetItemText(i, 8, LF->GetMyNumberFormat(nReqAmount));
		m_lstReport.SetItemText(i, 9, LF->GetMyNumberFormat(nReqAmount * 0.03));
		m_lstReport.SetItemText(i, 10, LF->GetMyNumberFormat((nReqAmount * 0.03) * 0.1));
		m_lstReport.SetItemText(i, 11, LF->GetMyNumberFormat(nRealAmount));

		CString strTemp;

		if(nApprovalType == 0) strTemp = "출금요청중";
		else if(nApprovalType == 1) strTemp = "송금완료";
		else if(nApprovalType == 2) strTemp = "취소";

		m_lstReport.SetItemText(i, 12, strTemp);

		if(nApprovalType == 0) 	strTemp = "";
		else if(nApprovalType == 1) strTemp = dtApproval.Format("%Y-%m-%d %H:%M");
		else if(nApprovalType == 2)	strTemp = dtCancel.Format("%Y-%m-%d %H:%M");

		m_lstReport.SetItemText(i, 13, strTemp);


		m_lstReport.SetItemLong(i, nCompany);
		m_lstReport.SetItemLong2(i, nID);
		m_lstReport.SetItemLong3(i, nApprovalType);

		rs.MoveNext();
	}

	SearchFilter();
	//m_lstReport.Populate();
}

void CReportForm32::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm32::OnApprovalNot()
{
	if(!LF->POWER_CHECK(4091, "상태변경", TRUE))
		return;

	if(m_lstReport.GetFirstSelectedRecord() == NULL)
		return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	long nTotalCount = pRows->GetCount();
	long nSuccessCount = 0;
	BOOL bMsgBox = nTotalCount == 1 ? TRUE : FALSE;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		long nID = m_lstReport.GetItemLong2(pRecord);
		long nCompany = m_lstReport.GetItemLong(pRecord);
		long nRNo = atoi(m_lstReport.GetItemText(pRecord, 2));
		BOOL bApproval = m_lstReport.GetItemLong3(pRecord);

		CString strOutput = "";

		CMkCommand cmd(m_pMkDb, "update_rider_balance_for_withdraw_not");
		cmd.AddParameter(nID);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(m_ei.strMac1);
		cmd.AddParameter(LF->GetHddId());
		CMkParameter *parOutRet = cmd.AddParameter(typeString, typeOutput, 100, "");

		if(!cmd.Execute())
			return;

		parOutRet->GetValue(strOutput);

		if(bMsgBox == TRUE)
		{
			if(!strOutput.IsEmpty())
				MessageBox(strOutput, "확인", MB_ICONERROR);
			else
				MessageBox("기사 잔액이 충전되었습니다", "확인", MB_ICONINFORMATION);
		}
		else
		{
			if(strOutput.IsEmpty())
				nSuccessCount++;
		}
	}

	if(bMsgBox == FALSE)
	{
		if(nTotalCount == nSuccessCount)
			MessageBox("기사 잔액이 충전되었습니다", "확인", MB_ICONINFORMATION);
		else
		{ 
			CString strTemp = "";
			strTemp.Format("총 %d명중 %d명의 기사잔액이 충전되었습니다", nTotalCount, nSuccessCount);
			MessageBox(strTemp, "확인", MB_ICONINFORMATION);
		}
	}

	RefreshList();
}

void CReportForm32::OnApproval()
{
	if(!LF->POWER_CHECK(4091, "상태변경", TRUE))
		return;

	if(m_lstReport.GetFirstSelectedRecord() == NULL)
		return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	long nTotalCount = pRows->GetCount();
	long nSuccessCount = 0;
	BOOL bMsgBox = nTotalCount == 1 ? TRUE : FALSE;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		long nID = m_lstReport.GetItemLong2(pRecord);
		long nCompany = m_lstReport.GetItemLong(pRecord);
		long nRNo = atoi(m_lstReport.GetItemText(pRecord, 2));
		BOOL bApproval = m_lstReport.GetItemLong3(pRecord);

		CString strOutput = "";

		CMkCommand cmd(m_pMkDb, "update_rider_balance_for_withdraw");
		cmd.AddParameter(nID);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(m_ei.strMac1);
		cmd.AddParameter(LF->GetHddId());
		CMkParameter *parOutRet = cmd.AddParameter(typeString, typeOutput, 100, "");

		if(!cmd.Execute())
			return;
		
		parOutRet->GetValue(strOutput);

		if(bMsgBox == TRUE)
		{
			if(!strOutput.IsEmpty())
				MessageBox(strOutput, "확인", MB_ICONERROR);
			else
				MessageBox("기사 잔액에서 차감되었습니다", "확인", MB_ICONINFORMATION);
		}
		else
		{
			if(strOutput.IsEmpty())
				nSuccessCount++;
		}
	}

	if(bMsgBox == FALSE)
	{
		if(nTotalCount == nSuccessCount)
			MessageBox("기사 잔액에서 차감되었습니다", "확인", MB_ICONINFORMATION);
		else
		{ 
			CString strTemp = "";
			strTemp.Format("총 %d명중 %d명의 기사잔액이 차감되었습니다", nTotalCount, nSuccessCount);
			MessageBox(strTemp, "확인", MB_ICONINFORMATION);
		}
	}

	RefreshList();
}

void CReportForm32::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 326, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}
void CReportForm32::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;
 
	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2); 
	pRMenu->InsertMenu(0, MF_BYPOSITION, ID_APPROVAL, "송금완료");
	pRMenu->InsertMenu(1, MF_BYPOSITION, ID_APPROVAL_NOT, "취소");
	

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm32::OnEnChangeRnoEdit()
{
	SearchFilter();
	/*
	CString strSearch; m_edtRNo.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
	CXTPGridRecord *pRecord = pRecords->GetAt(i);
	CString strSSN = m_lstReport.GetItemText(pRecord, 11);
	CString strRName = m_lstReport.GetItemText(pRecord, 12);
	strSSN.Replace("-", "");

	if(strSSN.Find(strSearch) >= 0 ||
	strRName.Find(strSearch) >= 0)
	{
	pRecord->SetVisible(TRUE);
	}
	else
	pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
	*/
}


void CReportForm32::SearchFilter()
{
	long nIndex = m_cmbState.GetCurSel();
	CString strSearch; m_edtRNo.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = m_lstReport.GetItemText(pRecord, 2);
		CString strRName = m_lstReport.GetItemText(pRecord, 3);
	
		BOOL bShow = FALSE;

		if(strRNo.Find(strSearch) >= 0 || 
			strRName.Find(strSearch) >= 0 )
		{
			bShow = TRUE;
		}

		if(bShow && nIndex > 0)
		{
			long nApprovalType = m_lstReport.GetItemLong3(pRecord);

			if(nIndex == 1)
			{
				if(nApprovalType != 1)
					bShow = FALSE;
			} 
			else if(nIndex == 2)
			{
				if(nApprovalType != 0)
					bShow = FALSE;
			}
			else if(nIndex == 3)
			{
				if(nApprovalType != 2)
					bShow = FALSE;
			}
		}

		pRecord->SetVisible(bShow);		
	}

	m_lstReport.Populate();
}

void CReportForm32::OnCbnSelchangeStateCombo()
{
	SearchFilter();
}
