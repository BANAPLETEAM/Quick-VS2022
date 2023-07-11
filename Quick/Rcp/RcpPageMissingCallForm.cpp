#include "StdAfx.h"
#include "resource.h"
#include "RcpPageMissingCallForm.h"
#include "RcpView.h"
#include "RcpPageCTIForm.h"
#include "RcpDlgAdmin.h"

IMPLEMENT_DYNCREATE(CRcpPageMissingCallForm, CMyFormView)

CRcpPageMissingCallForm::CRcpPageMissingCallForm()
: CMyFormView(CRcpPageMissingCallForm::IDD)
{
}

CRcpPageMissingCallForm::~CRcpPageMissingCallForm()
{
}

void CRcpPageMissingCallForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CRcpPageMissingCallForm, CMyFormView)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, OnDtnDatetimechangeDatetimepicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO, OnDtnDatetimechangeDatetimepicker)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefresh)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRcpPageMemoForm 진단입니다.

#ifdef _DEBUG
void CRcpPageMissingCallForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CRcpPageMissingCallForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CRcpPageMemoForm 메시지 처리기입니다.

void CRcpPageMissingCallForm::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnDate.OnMenuYesterday();

	m_List.InsertColumn(0, "일자", LVCFMT_CENTER, 100);
	m_List.InsertColumn(1, "시간", LVCFMT_CENTER, 70);
	m_List.InsertColumn(2, "지사", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, "내선번호", LVCFMT_LEFT, 70);
	m_List.InsertColumn(4, "전화번호", LVCFMT_LEFT, 100);
	m_List.InsertColumn(5, "링울린시간", LVCFMT_RIGHT, 70);

	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "전번/통화자", FALSE, FALSE);

	//SetResize(IDC_REPORT_LIST, sizingRightBottom);

	RefreshList();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CRcpPageMissingCallForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd())
	{
		CRect rc, rcList; 
		GetClientRect(rc);
		m_List.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rc.right - 5;
		rcList.bottom = rc.bottom - 5;

		m_List.MoveWindow(rcList);
	}
}

void CRcpPageMissingCallForm::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_stat_missingcall");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	//	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd)) return;

	m_List.GetRecords()->RemoveAll();

	CString strDate, strTime, strTellNumber;
	int nCompany = 0, nDID = 0, nKeyPhoneID = 0, nSecond = 0, nRecordIndex = m_List.GetRecords()->GetCount();
	COleDateTime dtDate;
	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		rs.GetFieldValue("dtDate", dtDate);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nLine", nDID);
		rs.GetFieldValue("nKeyPhoneID", nKeyPhoneID);
		rs.GetFieldValue("sCID", strTellNumber);
		rs.GetFieldValue("nSecond", nSecond);

		strDate.Format("%04d-%02d-%02d(%s)", dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), LF->GetDay(dtDate));
		m_List.InsertItem(nRecordIndex, strDate);

		m_List.SetItemDataText(nRecordIndex, LF->GetStringFromLong(nDID));

		strTime.Format("%02d:%02d:%02d", dtDate.GetHour(), dtDate.GetMinute(), dtDate.GetSecond());
		m_List.SetItemText(nRecordIndex, 1, strTime);
		m_List.SetItemText(nRecordIndex, 2,  m_ci.GetBranchName(nCompany));
		m_List.SetItemText(nRecordIndex, 3,  LF->GetStringFromLong(nKeyPhoneID));
		m_List.SetItemText(nRecordIndex, 4, strTellNumber);
		m_List.SetItemText(nRecordIndex++, 5,  LF->GetStringFromLong(nSecond) + "초");

		rs.MoveNext();
	}

	rs.Close();

	OnEnChangeSearchEdit();
}

void CRcpPageMissingCallForm::OnBnClickedRefresh()
{
	//CXTPGridColumn * pCol = m_List.GetColumns()->GetAt(0);
	//m_List.GetColumns()->SetSortColumn(pCol, FALSE);
	RefreshList();
}

void CRcpPageMissingCallForm::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();

	if(nRow >= 0)
	{
		CXTPGridRecord *pRecord = m_List.GetRows()->GetAt(nRow)->GetRecord();
		LU->GetRcpDlgAdmin()->m_pCTIForm->PopupRcpDlg(pRecord->GetItem(4)->GetCaption(NULL), pRecord->GetItem(3)->GetCaption(NULL), m_List.GetItemDataText(pRecord));
	}
}

void CRcpPageMissingCallForm::OnEnChangeSearchEdit()
{
	m_edtSearch.GetWindowText(m_strSearchNumber);

	int nCount = m_List.GetRecords()->GetCount();
	CXTPGridRecord* pRecord;
	CString strKeyPhone, strTellNumber;

	for (int i = 0 ; i < nCount; i++)
	{
		pRecord = m_List.GetRecords()->GetAt(i);
		if (pRecord != NULL)
		{
			strKeyPhone = pRecord->GetItem(3)->GetCaption(NULL);
			strTellNumber = pRecord->GetItem(4)->GetCaption(NULL);

			if (strKeyPhone.Find(m_strSearchNumber) >= 0 ||
				strTellNumber.Find(m_strSearchNumber) >= 0)
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);
		}
	}

	m_List.Populate();	
}

BOOL CRcpPageMissingCallForm::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_SIZE)
	{
		AfxMessageBox("I got it");
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CRcpPageMissingCallForm::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	COleDateTime dtDate = COleDateTime::GetCurrentTime();
	if (pNMHDR->idFrom == IDC_DATETIMEPICKER_FROM)
	{
		COleDateTime dtFrom;
		m_dtpFrom.GetTime(dtFrom);
		dtDate.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
		if (dtDate < dtFrom)
		{
			m_dtpFrom.SetTime(dtDate);
			dtFrom = dtDate;
		}
		m_dtFrom = dtFrom;
		m_dtpTo.GetTime(m_dtTo);
	}
	else
	{
		COleDateTime dtTo;
		m_dtpTo.GetTime(dtTo);
		dtDate.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
		COleDateTimeSpan dtSpan(1,0,0,0);
		dtDate += dtSpan;
		if (dtDate < dtTo)
		{
			m_dtpTo.SetTime(dtDate);
			dtTo = dtDate;
		}
		m_dtTo = dtTo;
		m_dtpFrom.GetTime(m_dtFrom);
	}

	*pResult = 0;
	UpdateData(FALSE);
}

void CRcpPageMissingCallForm::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;


	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CRcpPageMissingCallForm::OnViewExcel()
{
	if(!LF->POWER_CHECK(1956, "미연결콜 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 106, m_List.GetRecords()->GetCount());  

	CMyExcel::ToExcel(&m_List, "", 1, 4);
 
	//CMyExcel::ToExcel(&m_List);
} 