// CustomerPage13.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage13.h"


// CCustomerPage13

IMPLEMENT_DYNCREATE(CCustomerPage13, CMyFormView)

CCustomerPage13::CCustomerPage13()
	: CMyFormView(CCustomerPage13::IDD)
{

}

CCustomerPage13::~CCustomerPage13()
{
}

void CCustomerPage13::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_REPOR_LIST, m_lstReport);
}

BEGIN_MESSAGE_MAP(CCustomerPage13, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_ALL_BTN, &CCustomerPage13::OnBnClickedSearchAllBtn)
END_MESSAGE_MAP()


// CCustomerPage13 진단입니다.

#ifdef _DEBUG
void CCustomerPage13::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerPage13::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCustomerPage13 메시지 처리기입니다.

void CCustomerPage13::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuMonth();

	m_lstReport.InsertColumn(0,"고객번호",LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(1,"회사",LVCFMT_LEFT, 135);
	m_lstReport.InsertColumn(2,"날짜",LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3,"전화번호",LVCFMT_LEFT,100);
	m_lstReport.InsertColumn(4,"신용",LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(5,"아이디",LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(6,"기준동",LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(7,"위치",LVCFMT_LEFT, 200);
	m_lstReport.InsertColumn(8,"기존지사",LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(9,"지사변경",LVCFMT_CENTER, 65);
	m_lstReport.InsertColumn(10,"내부콜센터",LVCFMT_CENTER, 75);
	m_lstReport.Populate();

	SetResize(IDC_REPOR_LIST, sizingRightBottom);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CCustomerPage13::OnBnClickedSearchAllBtn()
{
	RefreshList();
}

void CCustomerPage13::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_revisit_customer_info_1");
	pCmd.AddParameter(GetCurBranchInfo(TRUE)->nCompanyCode);
	pCmd.AddParameter(GetCurBranchInfo(TRUE)->bIntegrated);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd))
		return;

	long nCompany, nID, nCNo, nTNo, nOriginalCompany;
	CString strTelDepart, strTelManager, strTel, strUserID, strDong, strLocation;
	BOOL bCredit, bInnerCallCenter, bChangeBranch;
	CString strPreTelDepart = "NRE", strPreTelManager = "NRE";
	long nPreCNo = -1;
	COleDateTime dtRevisit;
	char buffer[10];

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sTel", strTel);
		pRs.GetFieldValue("sUserID", strUserID);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("sLocation", strLocation);
		pRs.GetFieldValue("bCredit", bCredit);
		pRs.GetFieldValue("bInnerCallCenter", bInnerCallCenter);
		pRs.GetFieldValue("bChangeBranch", bChangeBranch);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nOriginalCompany", nOriginalCompany);
		pRs.GetFieldValue("dtRevisit", dtRevisit);

		//m_lstReport.InsertItem(i, nPreCNo != nCNo ? itoa(nID, buffer, 10) : "");
		m_lstReport.InsertItem(i, itoa(nID, buffer, 10));
		m_lstReport.SetItemText(i, 1, GetBranchInfo(nCompany)->strBranchName);
		m_lstReport.SetItemText(i, 2, dtRevisit.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 3, ::GetDashPhoneNumber(strTel));
		m_lstReport.SetItemText(i, 4, bCredit == TRUE ? "신용" : "");
		m_lstReport.SetItemText(i, 5, strUserID);
		m_lstReport.SetItemText(i, 6, strDong);
		m_lstReport.SetItemText(i, 7, strLocation);
		m_lstReport.SetItemText(i, 8, ::GetBranchInfo(nOriginalCompany)->strBranchName);
		m_lstReport.SetItemText(i, 9, bChangeBranch == TRUE ? "ㅇ" : "X");
		m_lstReport.SetItemText(i, 10, bInnerCallCenter == TRUE ? "ㅇ" : "X");

		nPreCNo = nCNo;
		strPreTelManager = strTelManager;
		strPreTelDepart = strTelDepart;

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}