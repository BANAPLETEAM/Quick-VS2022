// ReportForm23.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ReportForm34.h"
#include "CardVerifyDlg.h"

// CReportForm34

IMPLEMENT_DYNCREATE(CReportForm34, CMyFormView)

CReportForm34::CReportForm34()
: CMyFormView(CReportForm34::IDD)
{

}

CReportForm34::~CReportForm34()
{
}

void CReportForm34::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
}

BEGIN_MESSAGE_MAP(CReportForm34, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm34::OnBnClickedRefreshBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CANCEL_PAY_CASH, OnCancelPayCash)	
	ON_EN_CHANGE(IDC_RNO_EDIT, &CReportForm34::OnEnChangeRnoEdit)
END_MESSAGE_MAP()


// CReportForm34 진단입니다.

#ifdef _DEBUG
void CReportForm34::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm34::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm34 메시지 처리기입니다.

void CReportForm34::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT, sizingRightBottom);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();

	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "오더번호", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "발급날짜", LVCFMT_LEFT, 130);
	m_lstReport.InsertColumn(3, "금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(4, "용도구분", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(5, "발급번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(6, "발급자(사번)", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(7, "접수회사", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(8, "출발지", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(9, "도착지", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(10, "오더금액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(11, "오더입금액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(12, "접수날짜", LVCFMT_LEFT, 130);
	m_lstReport.SetOrderIndexCol(0);

	m_lstReport.Populate();
}

void CReportForm34::RefreshList() 
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_cash_receipt_order_log");
	cmd.AddParameter(::GetCurBranchInfo(TRUE)->nCompanyCode);
	cmd.AddParameter(::GetCurBranchInfo(TRUE)->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nTNo, nCompany, nWNo, nAmt, nIssueType, nCharge, nDeposit;
	CString strIssueKey, strStart, strDest;
	COleDateTime dtLog, dt1;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nTNo", nTNo);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nWNo", nWNo);
		rs.GetFieldValue("nAmt", nAmt);
		rs.GetFieldValue("nIssueType", nIssueType);
		rs.GetFieldValue("sIssueKey", strIssueKey);
		rs.GetFieldValue("dtLog", dtLog);
		rs.GetFieldValue("sStart", strStart);
		rs.GetFieldValue("sDest", strDest);
		rs.GetFieldValue("nCharge", nCharge);
		rs.GetFieldValue("nDeposit", nDeposit);
		rs.GetFieldValue("dt1", dt1);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, ::GetStringFromLong(nTNo));
		m_lstReport.SetItemText(i, 2, dtLog.Format("%Y-%m-%d %H:%M:%S"));
		m_lstReport.SetItemText(i, 3, ::GetMyNumberFormat(nAmt));
		m_lstReport.SetItemText(i, 4, nIssueType == 1 ? "소득공제" : "지출증빙");
		m_lstReport.SetItemText(i, 5, strIssueKey);
		m_lstReport.SetItemText(i, 6, ::GetStringFromLong(nWNo));
		m_lstReport.SetItemText(i, 7, m_ci.GetBranchName(nCompany));
		m_lstReport.SetItemText(i, 8, strStart);
		m_lstReport.SetItemText(i, 9, strDest);
		m_lstReport.SetItemText(i, 10, ::GetMyNumberFormat(nCharge));
		m_lstReport.SetItemText(i, 11, ::GetMyNumberFormat(nDeposit));
		m_lstReport.SetItemText(i, 12, dt1.m_status  != 2 ? dt1.Format("%Y-%m-%d %H:%M:%S") : "");
		m_lstReport.SetItemLong(i, nTNo);

		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CReportForm34::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm34::OnViewExcel()
{
	if(!POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 330, m_ui.nWNo, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void CReportForm34::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(12);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm34::OnEnChangeRnoEdit()
{
	SearchFilter();
}

void CReportForm34::SearchFilter()
{
	CString strItem;
	m_edtRNo.GetWindowText(strItem);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString s1 = pRecord->GetItem(5)->GetCaption(NULL);
		CString s2 = pRecord->GetItem(8)->GetCaption(NULL);
		CString s3 = pRecord->GetItem(9)->GetCaption(NULL);
		
		if(s1.Find(strItem) >= 0 ||
			s2.Find(strItem) >= 0 ||
			s3.Find(strItem) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}

void CReportForm34::OnCancelPayCash()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nTNo = m_lstReport.GetItemLong(pRecord);

	CString strAddr; long nPort;

	if(!::GetConnetcInfo(strAddr, nPort))
	{
		MessageBox("서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;	
	}

	//strAddr = "192.168.1.46";
	//nPort = 4300;

	if(!CCardVerifyDlg::GetCardSocket(strAddr, nPort))
	{
		MessageBox("서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;
	}

	CString strTemp;
	strTemp.Format("<USAGE_ID=3><SEND_SMS=0><COMPANY=%d><WCOMPANY=%d><WNO=%d><TNO=%d><CANCEL_MSG=고객취소>",
		::GetCurBranchInfo()->nCompanyCode, m_ui.nCompany, m_ui.nWNo, nTNo);

	char data[300];
	strcpy(data, strTemp); 

	if(!CCardVerifyDlg::m_pMkCard->GetSocket()->SendData(PT_REQUEST, PST_NICE_REQUSET_PROTOCOL, data)) 
	{
		MessageBox("서버 접속실패\r\n다시 시도하세요", "확인", MB_ICONERROR);
		return;
	}

	CString strMsg;
	QPACKET *rcv = (QPACKET*)CCardVerifyDlg::m_pMkCard->GetSocket()->ReadStream();

	if(rcv == NULL)
	{
		MessageBox("현금영수증 발급취소 실패\r\n다시 시도하세요", "확인", MB_ICONERROR);
		return;
	}

	if(rcv != NULL) 
	{
		if(PT_OK == rcv->nType)
		{
			MessageBox("현금영수증 발급이 취소 되었습니다", "확인", MB_ICONINFORMATION);
		}
		else
		{
			int nRet = rcv->nSubType;
			strMsg = rcv->data;			
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}

		free(rcv);
	}
}