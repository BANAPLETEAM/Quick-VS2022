// CustomerPage15.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage18.h"


// CCustomerPage18

IMPLEMENT_DYNCREATE(CCustomerPage18, CMyFormView)

CCustomerPage18::CCustomerPage18()
	: CMyFormView(CCustomerPage18::IDD)
{
}

CCustomerPage18::~CCustomerPage18()
{
}

void CCustomerPage18::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lstReport);	
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CCustomerPage18, CMyFormView)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EXCEL, OnViewExcel)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CCustomerPage18::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CCustomerPage18::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


#ifdef _DEBUG
void CCustomerPage18::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerPage18::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCustomerPage18 메시지 처리기입니다.

void CCustomerPage18::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_LIST, sizingRightBottom);

	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(1, "등록일", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(2, "전화번호", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "등록자", LVCFMT_LEFT, 80);
	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();
}

void CCustomerPage18::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(10);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage18::OnViewExcel()
{
	if(!POWER_CHECK(6900, "고객 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCustomerTable, 215, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void CCustomerPage18::OnDelete()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nCount = pRows->GetCount();

	CString strTemp = "";
	strTemp.Format("%d건을 삭제 하시겠습니까?", nCount);

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(0);
		CXTPGridRecord *pRecord = pRow->GetRecord();

		long nCompany = m_lstReport.GetItemLong(pRecord);
		CString strTelNumber = m_lstReport.GetItemText(pRecord, 2);
		strTelNumber.Replace("-", "");

		CMkCommand cmd(m_pMkDb, "delete_telserver_jinsang_list");
		cmd.AddParameter(nCompany);
		cmd.AddParameter(strTelNumber);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
			return;

		m_lstReport.RemoveRecordEx(pRecord);
	}

	m_lstReport.Populate();
}

void CCustomerPage18::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CCustomerPage18::RefreshList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_telserver_jinsang");
	cmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(::GetCurBranchInfo()->bIntegrated);

	if(!rs.Execute(&cmd))
		return;

	long nCompany;
	COleDateTime dtStart;
	CString strTelNumber, strWName;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("dtStart", dtStart);
		rs.GetFieldValue("sTelNumber", strTelNumber);
		rs.GetFieldValue("sWName", strWName);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, dtStart.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, ::GetDashPhoneNumber(strTelNumber));
		m_lstReport.SetItemText(i, 3, strWName);
		m_lstReport.SetItemLong(i, nCompany);
		m_lstReport.SetItemDataText(i, strTelNumber);
		
		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CCustomerPage18::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
 		CString strItem = m_lstReport.GetItemText(pRecord, 2);
		CString strItem2 = m_lstReport.GetItemText(pRecord, 3);

		strItem.Replace("-", "");
		strItem2.Replace("-", "");

		if(strItem.Find(strSearch) >= 0 ||
			strItem2.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}
