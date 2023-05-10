// StaffPage16.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "StaffPage16.h"


// CStaffPage16

IMPLEMENT_DYNCREATE(CStaffPage16, CMyFormView)

CStaffPage16::CStaffPage16()
	: CMyFormView(CStaffPage16::IDD)
{

}

CStaffPage16::~CStaffPage16()
{
}

void CStaffPage16::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CStaffPage16, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_LIST_BUTTON, &CStaffPage16::OnBnClickedRefreshListButton)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CStaffPage16::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CStaffPage16 진단입니다.

#ifdef _DEBUG
void CStaffPage16::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffPage16::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStaffPage16 메시지 처리기입니다.

void CStaffPage16::OnBnClickedRefreshListButton()
{
	RefreshList();
}

void CStaffPage16::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstReport.InsertColumn(0, "NO", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "소속", LVCFMT_CENTER, 110);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(3, "성명", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "아이디", LVCFMT_CENTER, 110);
	m_lstReport.InsertColumn(5, "등록일", LVCFMT_CENTER, 110);
	m_lstReport.InsertColumn(6, "주민번호", LVCFMT_CENTER, 110);
	m_lstReport.InsertColumn(7, "해제일", LVCFMT_CENTER, 120);
	m_lstReport.InsertColumn(8, "해제자", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(9, "즉시공유", LVCFMT_CENTER, 60);
	m_lstReport.SetOrderIndexCol(ZERO);

	m_lstReport.Populate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CStaffPage16::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_refusal_rider_delete_log");

	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd))
		return;

	CString strRiderCompany, strJumin, strRJumin, strRName, strID, strDeleteWName;
	COleDateTime dtPrevent, dtDelete;
	long nID, nRNo, nDeleteWNo, nDeleteWCompany;
	char buffer[10];
	BOOL bAutoRefusal;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sRiderCompany", strRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("dtPrevent", dtPrevent);
		pRs.GetFieldValue("sjumin", strJumin);
		pRs.GetFieldValue("dtDelete", dtDelete);
		pRs.GetFieldValue("nDeleteWCompany", nDeleteWCompany);
		pRs.GetFieldValue("nDeleteWNo", nDeleteWNo);
		pRs.GetFieldValue("sDeleteWName", strDeleteWName);
		pRs.GetFieldValue("bAutoRefusal", bAutoRefusal);

		strRJumin = strJumin;

		if(strJumin.GetLength() > 10)
			strJumin = "**" + strJumin.Mid(2,4);
		else
			strJumin = "";

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, strRiderCompany);
		m_lstReport.SetItemText(i, 2, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(i, 3, strRName);
		m_lstReport.SetItemText(i, 4, strID);
		m_lstReport.SetItemText(i, 5, dtPrevent.Format("%Y-%m-%d"));
		m_lstReport.SetItemText(i, 6, strJumin);
		m_lstReport.SetItemText(i, 7, dtDelete.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 8, strDeleteWName + "(" + CString(itoa(nDeleteWNo, buffer, 10)) + ")");
		m_lstReport.SetItemText(i, 9, bAutoRefusal ? "ㅇ" : "");

		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemString(i, strRJumin);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}

void CStaffPage16::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(TWO)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(THREE)->GetCaption(NULL);
		CString strID = pRecord->GetItem(FOUR)->GetCaption(NULL);
		CString strJumin = m_lstReport.GetItemString(pRecord);

		if(strRNo.Find(strSearch) >= ZERO ||
			strRName.Find(strSearch) >= ZERO ||
			strID.Find(strSearch) >= ZERO ||
			strJumin.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();		
	
}
