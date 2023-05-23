// StatForm9.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "StatForm9.h"


// CStatForm9

IMPLEMENT_DYNCREATE(CStatForm9, CMyFormView)

CStatForm9::CStatForm9()
	: CMyFormView(CStatForm9::IDD)
{

}

CStatForm9::~CStatForm9()
{
}

void CStatForm9::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);

	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CStatForm9, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CStatForm9::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CStatForm9 �����Դϴ�.

#ifdef _DEBUG
void CStatForm9::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatForm9::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatForm9 �޽��� ó�����Դϴ�.

void CStatForm9::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_lstReport.InsertColumn(0, "����", LVCFMT_CENTER, 80);
	m_lstReport.InsertColumn(1, "�ѰǼ�", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(2, "����ƮQ", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(3, "����ƮQ��", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(4, "����Ʈ��", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(5, "������", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(6, "���ͳ�", LVCFMT_RIGHT, 70);
	m_lstReport.Populate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CStatForm9::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStatForm9::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_type_log");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	m_lstReport.DeleteAllItems();

	CString strDate;
	long nRcpSmartQ, nRcpSmartQTab, nRcpSmartQuick, nRcpInterCall, nRcpInternet, nAllCount;
	
	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sDate", strDate);
		rs.GetFieldValue("nRcpSmartQ", nRcpSmartQ);
		rs.GetFieldValue("nRcpSmartQTab", nRcpSmartQTab);
		rs.GetFieldValue("nRcpSmartQuick", nRcpSmartQuick);
		rs.GetFieldValue("nRcpInterCall", nRcpInterCall);
		rs.GetFieldValue("nRcpInternet", nRcpInternet);		
		rs.GetFieldValue("nAllCount", nAllCount);

		m_lstReport.InsertItem(i, strDate);
		m_lstReport.SetItemText(i, 1, LF->RemoveZero(LF->GetMyNumberFormat(nAllCount)));
		m_lstReport.SetItemText(i, 2, LF->RemoveZero(LF->GetMyNumberFormat(nRcpSmartQ)));
		m_lstReport.SetItemText(i, 3, LF->RemoveZero(LF->GetMyNumberFormat(nRcpSmartQTab)));
		m_lstReport.SetItemText(i, 4, LF->RemoveZero(LF->GetMyNumberFormat(nRcpSmartQuick)));
		m_lstReport.SetItemText(i, 5, LF->RemoveZero(LF->GetMyNumberFormat(nRcpInterCall)));
		m_lstReport.SetItemText(i, 6, LF->RemoveZero(LF->GetMyNumberFormat(nRcpInternet)));
		
		rs.MoveNext();
	}

	m_lstReport.Populate();
}