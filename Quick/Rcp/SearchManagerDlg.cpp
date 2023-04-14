// SearchManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SearchManagerDlg.h"
#include "AddManagerDlg.h"
#include "CustomerData.h"
#include "RcpDlg.h"

// CSearchManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchManagerDlg, CMyDialog)

CSearchManagerDlg::CSearchManagerDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchManagerDlg::IDD, pParent)
{
	m_pRcpDlg = NULL;
	m_nCompany = 0;
	m_nCNo = 0;
}

CSearchManagerDlg::~CSearchManagerDlg()
{
}

void CSearchManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANAGER_SEARCH_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CSearchManagerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ADD_BTN, &CSearchManagerDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSearchManagerDlg::OnBnClickedCloseBtn)
	ON_NOTIFY(NM_CLICK, IDC_MANAGER_SEARCH_LIST, OnReportItemClick)

END_MESSAGE_MAP()


void CSearchManagerDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CEdit *pDepart = NULL;
	CEdit *pManager = NULL;
	CEdit *pTel = NULL;

	if(m_pRcpDlg->m_nLastDepartFocus == IDC_ORDER_DEPART_EDIT)
	{
		pDepart = m_pRcpDlg->m_EDT_ORDER_DEPART.pEdit;
		pManager = m_pRcpDlg->m_EDT_ORDER_MANAGER.pEdit;
		pTel = m_pRcpDlg->m_EDT_ORDER_PHONE.pEdit;
	}	
	else if(m_pRcpDlg->m_nLastDepartFocus == IDC_START_DEPART_EDIT)
	{	
		pDepart = m_pRcpDlg->m_EDT_START_DEPART.pEdit;
		pManager = m_pRcpDlg->m_EDT_START_MANAGER.pEdit;
		pTel = m_pRcpDlg->m_EDT_START_PHONE.pEdit;
	}
	else if(m_pRcpDlg->m_nLastDepartFocus == IDC_DEST_DEPART_EDIT)
	{
		pDepart = m_pRcpDlg->m_EDT_DEST_DEPART.pEdit;
		pManager = m_pRcpDlg->m_EDT_DEST_MANAGER.pEdit;
		pTel = m_pRcpDlg->m_EDT_DEST_PHONE.pEdit;
	}

	if(pDepart == NULL)
		return;

	pDepart->SetWindowText(m_List.GetItemText(pRecord, ONE));
	pManager->SetWindowText(m_List.GetItemText(pRecord, 2));
	pTel->SetWindowText(m_List.GetItemText(pRecord, ZERO));

	ShowWindow(FALSE);
}

// CSearchManagerDlg 메시지 처리기입니다.

void CSearchManagerDlg::OnBnClickedAddBtn()
{
	CAddManagerDlg dlg(this);
	dlg.m_nCompany = m_nCompany;
	dlg.m_nCNo = m_nCNo;

	if(dlg.DoModal() == IDOK)
	{
		m_cus.GetNewCustomer();
		m_pRcpDlg->OpenManagerSearchDlg();
	}
}

void CSearchManagerDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}

BOOL CSearchManagerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_List.InsertColumn(0, "전화", LVCFMT_LEFT, 90);
	m_List.InsertColumn(1, "담당", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "부서", LVCFMT_LEFT, 100);

	m_List.GetPaintManager()->m_strNoItems = "";
	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_List.ShowHeader(FALSE);

	m_List.Populate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
