// StaffPage20.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "StaffPage20.h"

// CStaffPage20

IMPLEMENT_DYNCREATE(CStaffPage20, CMyFormView)

CStaffPage20::CStaffPage20()
	: CMyFormView(CStaffPage20::IDD)
{

}

CStaffPage20::~CStaffPage20()
{
}

void CStaffPage20::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DTP_FROM, m_dtFromCtl);
	DDX_Control(pDX, IDC_DTP_TO, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);

	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CStaffPage20, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CStaffPage20::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CStaffPage20::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CStaffPage20 진단입니다.

#ifdef _DEBUG
void CStaffPage20::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffPage20::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStaffPage20 메시지 처리기입니다.

void CStaffPage20::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuMonth();

	m_lstReport.InsertColumn(0, "순번", LVCFMT_LEFT, 40);
	m_lstReport.InsertColumn(1, "아이디", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(3, "성명", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "로그인", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(5, "로그아웃", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(6, "파일버젼", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(7, "아이피", LVCFMT_CENTER, 100);
	m_lstReport.Populate();
}

void CStaffPage20::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStaffPage20::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_conn_info_1");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	m_lstReport.DeleteAllItems();

	CString strID, strName, strFileVersion, strIP;
	long nWNo, nCompany;
	COleDateTime dtLogin, dtLogout;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sID", strID);
		rs.GetFieldValue("nMNo", nWNo);
		rs.GetFieldValue("lCode", nCompany);
		rs.GetFieldValue("sName", strName);
		rs.GetFieldValue("sFileVersion", strFileVersion);
		rs.GetFieldValue("dtLogin", dtLogin);
		rs.GetFieldValue("dtLogout", dtLogout);
		rs.GetFieldValue("sIP", strIP);

		m_lstReport.InsertItem(i, LF->GetStringFromLong(i+1));
		m_lstReport.SetItemText(i, 1, strID);
		m_lstReport.SetItemText(i, 2, LF->GetStringFromLong(nWNo));
		m_lstReport.SetItemText(i, 3, strName);

		if(dtLogin.m_status != 2) 
			m_lstReport.SetItemText(i, 4, dtLogin.Format("%Y-%m-%d %H:%M:%S"));
		else
			m_lstReport.SetItemText(i, 4, "");

		if(dtLogout.m_status != 2)
			m_lstReport.SetItemText(i, 5, dtLogout.Format("%Y-%m-%d %H:%M:%S"));
		else
			m_lstReport.SetItemText(i, 5, "");

		m_lstReport.SetItemText(i, 6, strFileVersion);
		m_lstReport.SetItemText(i, 7, strIP);
		rs.MoveNext();
	}

	OnEnChangeSearchEdit();
}

void CStaffPage20::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strWNo = pRecord->GetItem(2)->GetCaption(NULL);

		if(strWNo.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}
