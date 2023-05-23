// ReportForm32.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ReportForm33.h"

#define ID_APPROVAL 9000
// CReportForm33

IMPLEMENT_DYNCREATE(CReportForm33, CMyFormView)

CReportForm33::CReportForm33()
: CMyFormView(CReportForm33::IDD)
{

}

CReportForm33::~CReportForm33()
{
}

void CReportForm33::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CReportForm33, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm33::OnBnClickedRefreshBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_APPROVAL, OnApproval)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_RNO_EDIT, &CReportForm33::OnEnChangeRnoEdit)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, &CReportForm33::OnCbnSelchangeStateCombo)

END_MESSAGE_MAP()


// CReportForm33 진단입니다.

#ifdef _DEBUG
void CReportForm33::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm33::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm33 메시지 처리기입니다.

void CReportForm33::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT, sizingRightBottom);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();
	m_cmbState.SetCurSel(0);

	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "날짜", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(3, "기사명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(4, "아이디", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(5, "기기아이디", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(6, "기기제조번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(7, "전화번호", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(8, "휴대폰", LVCFMT_RIGHT, 80);

	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();
}

void CReportForm33::RefreshList()
{
	CMyFormView::RefreshList();

	static BOOL bFirst = TRUE;

	if(bFirst)
	{
		bFirst = FALSE;
		return;
	}


	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CString strSearch; 
	m_edtRNo.GetWindowText(strSearch);

	/*
	if(strSearch == "")
	{
		MessageBox("검색어를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	*/

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rt_change_log");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);
	cmd.AddParameter(m_cmbState.GetCurSel());
	cmd.AddParameter(strSearch);

	if(!rs.Execute(&cmd))
		return;

	long nCompany, nRNo;
	CString strID, strName, strRTID, strRTSerial, strTel, strHP; 
	COleDateTime dtLog;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sID", strID);
		rs.GetFieldValue("sName", strName);  
		rs.GetFieldValue("sRTID", strRTID);
		rs.GetFieldValue("sRTSerial", strRTSerial);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sHP", strHP);
		rs.GetFieldValue("dtLog", dtLog);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, dtLog.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, LF->GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 3, strName);
		m_lstReport.SetItemText(i, 4, strID);
		m_lstReport.SetItemText(i, 5, strRTID);
		m_lstReport.SetItemText(i, 6, strRTSerial);
		m_lstReport.SetItemText(i, 7, strTel);
		m_lstReport.SetItemText(i, 8, strHP);

		rs.MoveNext();
	}

	m_lstReport.Populate();

	//SearchFilter();
	//m_lstReport.Populate();
}

void CReportForm33::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm33::OnApproval()
{
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

void CReportForm33::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 327, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}
void CReportForm33::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2); 
	
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm33::OnEnChangeRnoEdit()
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


void CReportForm33::SearchFilter()
{
	return;

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
			BOOL bApproval = m_lstReport.GetItemLong3(pRecord);

			if(nIndex == 1)
			{
				if(bApproval == FALSE)
					bShow = FALSE;
			}
			else if(nIndex == 2)
			{
				if(bApproval == TRUE)
					bShow = FALSE;
			}
		}

		pRecord->SetVisible(bShow);		
	}

	m_lstReport.Populate();
}

void CReportForm33::OnCbnSelchangeStateCombo()
{
	SearchFilter();
}
