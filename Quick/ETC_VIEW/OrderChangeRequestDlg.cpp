// OrderChangeRequestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OrderChangeRequestDlg.h"


// COrderChangeRequestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COrderChangeRequestDlg, CMyDialog)

COrderChangeRequestDlg::COrderChangeRequestDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COrderChangeRequestDlg::IDD, pParent)
{

}

COrderChangeRequestDlg::~COrderChangeRequestDlg()
{
}

void COrderChangeRequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
}


BEGIN_MESSAGE_MAP(COrderChangeRequestDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, &COrderChangeRequestDlg::OnCbnSelchangeStateCombo)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COMPLETE, OnComplete)
	ON_COMMAND(ID_NOT_COMPLETE, OnNotComplete)
	ON_COMMAND(ID_CANCEL, OnCancelItem)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &COrderChangeRequestDlg::OnBnClickedRefreshBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COrderChangeRequestDlg 메시지 처리기입니다.


void COrderChangeRequestDlg::RefreshList()
{
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dorder_change_request");
	cmd.AddParameter(m_ci.m_nShareCode1);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nTNo, nChargeSum, nPayType, nResult, nID, nShareCode1, nRiderShareCode1, nPreChargeSum;
	CString strSDong, strDDong;
	COleDateTime dtGenerate;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nTNo", nTNo);
		rs.GetFieldValue("nChargeSum", nChargeSum);
		rs.GetFieldValue("nPayType", nPayType);
		rs.GetFieldValue("sSDong", strSDong);
		rs.GetFieldValue("sDDong", strDDong);
		rs.GetFieldValue("nResult", nResult);
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("nResult", nResult);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nShareCode1", nShareCode1);
		rs.GetFieldValue("nRiderShareCode1", nRiderShareCode1);
		rs.GetFieldValue("nPreChargeSum", nPreChargeSum);

		m_lstReport.InsertItem(i, dtGenerate.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, LF->GetStringFromLong(nTNo));
		m_lstReport.SetItemText(i, 2, m_ci.GetCompanyName(nShareCode1));
		m_lstReport.SetItemText(i, 3, m_ci.GetCompanyName(nRiderShareCode1));
		m_lstReport.SetItemText(i, 4, strSDong);
		m_lstReport.SetItemText(i, 5, strDDong);
		m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nPreChargeSum));
		m_lstReport.SetItemText(i, 7, LF->GetMyNumberFormat(nChargeSum));
		m_lstReport.SetItemText(i, 8, LF->GetPayTypeFromLong(nPayType));

		CString strReuslt; 

		if(nResult == 0) strReuslt = "대기중";
		else if(nResult == 1) strReuslt = "수정완료";
		else if(nResult == 2) strReuslt = "수정거부";
		else if(nResult == 3) strReuslt = "수정취소";

		m_lstReport.SetItemText(i, 8, strReuslt);
		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemLong2(i, nShareCode1);
		m_lstReport.SetItemLong3(i, nResult);

		rs.MoveNext();
	}
  
	OnCbnSelchangeStateCombo();
}

BOOL COrderChangeRequestDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonthIncludeToday();
 
	m_cmbState.SetCurSel(0);

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "오더번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "발주사", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "수주사", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "출발지", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(5, "도착지", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(6, "수정전금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(7, "변경금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(8, "입금방식", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(9, "상태", LVCFMT_RIGHT, 60);

	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COrderChangeRequestDlg::OnCbnSelchangeStateCombo()
{
	long nState = m_cmbState.GetCurSel();

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount() ;i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		long nShareCode1 = m_lstReport.GetItemLong2(pRecord);

		if(nState == 0)
			pRecord->SetVisible(TRUE);
		else if(nState == 1)
		{
			if(m_ci.m_nShareCode1 != nShareCode1)
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);			
		}
		else if(nState == 2)
		{
			if(m_ci.m_nShareCode1 == nShareCode1)
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);			
		}		
	}

	m_lstReport.Populate();
}

void COrderChangeRequestDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint pt;
	GetCursorPos(&pt);

	CRect rtReport;
	m_lstReport.GetWindowRect(&rtReport);

	if(rtReport.PtInRect(pt))
	{
		CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
		if(pRecord)
		{
			long nShareCode1 = m_lstReport.GetItemLong2(pRecord);

			BCMenu rMenu;
			rMenu.LoadMenu(IDR_CONTEXT_MENU);

			BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(30);
			pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
		}
	}
}

void COrderChangeRequestDlg::OnNotComplete()
{
	if(!LF->POWER_CHECK(1521, "승인&거부 권한"))
		return;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	long nResult = m_lstReport.GetItemLong3(pRecord);
	long nShareCode1 = m_lstReport.GetItemLong2(pRecord);
	long nID = m_lstReport.GetItemLong(pRecord);

	if(nResult != 0 || m_ci.m_nShareCode1 == nShareCode1)
	{
		MessageBox("자사에서 요청한 항목을 완료하실수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ChangeItemState(nID, 2);
}

void COrderChangeRequestDlg::OnComplete()
{
	if(!LF->POWER_CHECK(1521, "승인&거부 권한"))
		return;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	long nResult = m_lstReport.GetItemLong3(pRecord);
	long nShareCode1 = m_lstReport.GetItemLong2(pRecord);
	long nID = m_lstReport.GetItemLong(pRecord);

	if(nResult != 0 || m_ci.m_nShareCode1 == nShareCode1)
	{
		MessageBox("자사에서 요청한 항목을 완료하실수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ChangeItemState(nID, 1);
}

void COrderChangeRequestDlg::ChangeItemState(long nID, long nResult)
{

	CMkCommand cmd(m_pMkDb, "update_dorder_change_request_1");
	cmd.AddParameter(nID);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(nResult);

	cmd.Execute();
	RefreshList();
}

void COrderChangeRequestDlg::OnCancelItem()
{
	if(!LF->POWER_CHECK(1521, "승인&거부 권한"))
		return;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();
	long nResult = m_lstReport.GetItemLong3(pRecord);
	long nShareCode1 = m_lstReport.GetItemLong2(pRecord);
	long nID = m_lstReport.GetItemLong(pRecord);

	if(nResult != 0 || m_ci.m_nShareCode1 != nShareCode1)
	{
		MessageBox("타사에서 요청한 항목을 완료하실수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ChangeItemState(nID, 3);

}
void COrderChangeRequestDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void COrderChangeRequestDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 5;
		rcList.bottom = rcForm.bottom - 5;
		m_lstReport.MoveWindow(rcList);
	}
}
