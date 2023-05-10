// SearchCustomerInsungDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "SearchCustomerInsungDlg.h"
#include "CustomerDlg.h"

// CSearchCustomerInsungDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchCustomerInsungDlg, CDialog)

CSearchCustomerInsungDlg::CSearchCustomerInsungDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchCustomerInsungDlg::IDD, pParent)
{
	m_pRs = NULL;
	m_nCNo = NULL;
	m_nTelID = NULL;
}

CSearchCustomerInsungDlg::~CSearchCustomerInsungDlg()
{
	DeleteList();
} 

void CSearchCustomerInsungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
	DDX_Control(pDX, IDC_SEARCH_NAME_EDIT, m_edtSearchName);
	DDX_Control(pDX, IDC_SEARCH_DEPART_EDIT, m_edtSearchDepart);
	DDX_Control(pDX, IDC_SEARCH_MANAGER_EDIT, m_edtSearchManager);
}


BEGIN_MESSAGE_MAP(CSearchCustomerInsungDlg, CDialog)
	ON_EN_CHANGE(IDC_SEARCH_NAME_EDIT, &CSearchCustomerInsungDlg::OnEnChangeSearchNameEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEPART_EDIT, &CSearchCustomerInsungDlg::OnEnChangeSearchDepartEdit)
	ON_EN_CHANGE(IDC_SEARCH_MANAGER_EDIT, &CSearchCustomerInsungDlg::OnEnChangeSearchManagerEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSearchCustomerInsungDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


BOOL CSearchCustomerInsungDlg::OnInitDialog()
{ 
	CDialog::OnInitDialog(); 

	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	m_lstCustomer.InsertColumn(0,"고객명",LVCFMT_LEFT,135);
	m_lstCustomer.InsertColumn(1,"부서명",LVCFMT_LEFT,95);	
	m_lstCustomer.InsertColumn(2,"담당/직위",LVCFMT_LEFT,100);
	m_lstCustomer.InsertColumn(3,"전화번호1",LVCFMT_LEFT,70);
	m_lstCustomer.InsertColumn(4,"전화번호2",LVCFMT_LEFT,70);
	m_lstCustomer.InsertColumn(5,"거래",LVCFMT_LEFT,40);
	m_lstCustomer.InsertColumn(6,"기준동",LVCFMT_LEFT,60);
	m_lstCustomer.InsertColumn(7,"위치",LVCFMT_LEFT,280);
	m_lstCustomer.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstCustomer.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstCustomer.Populate();

	m_lstCustomer.SetDrawCount(TRUE);

	if(m_pRs != NULL)
		RefreshList();	

	return TRUE;
}


void CSearchCustomerInsungDlg::DeleteList()
{
	CXTPGridRecords *pRecords = m_lstCustomer.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		ST_CUSTOMER_INFO *pInfo = (ST_CUSTOMER_INFO*)m_lstCustomer.GetItemData(pRecord);;

		delete pInfo;
		pInfo = NULL;
	}
	m_lstCustomer.DeleteAllItems();
}

void CSearchCustomerInsungDlg::RefreshList()
{
	DeleteList();

	for(int i=0; i<m_pRs->GetRecordCount(); i++)
	{
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		COleDateTime dtPRDate;
		CCustomerDlg::GetPcInfo(m_pRs, pc, dtPRDate, TRUE);
		
		m_lstCustomer.InsertItem(i, pc->strCompany);
		m_lstCustomer.SetItemText(i, 1, pc->strDepart);
		m_lstCustomer.SetItemText(i, 2, pc->strName);
		m_lstCustomer.SetItemText(i, 3, pc->strMobile);
		m_lstCustomer.SetItemText(i, 4, pc->strTel2);

		CString strTemp = "";
		if(pc->bCredit == 1) strTemp = "신용";
		else if(pc->bCredit == 2) strTemp = "송금";
		else if(pc->bCredit == 3) strTemp = "카드";

		m_lstCustomer.SetItemText(i, 5, strTemp);
		m_lstCustomer.SetItemText(i, 6, pc->strDong);
		m_lstCustomer.SetItemText(i, 7, pc->strLocation);

		m_lstCustomer.SetItemData(i, (DWORD)pc);
		m_pRs->MoveNext();
	}

	m_lstCustomer.Populate();
}

// CSearchCustomerInsungDlg 메시지 처리기입니다.

void CSearchCustomerInsungDlg::OnEnChangeSearchNameEdit()
{
	SearchFilter();
}

void CSearchCustomerInsungDlg::OnEnChangeSearchDepartEdit()
{
	SearchFilter();
} 

void CSearchCustomerInsungDlg::OnEnChangeSearchManagerEdit()
{
	SearchFilter();
}

void CSearchCustomerInsungDlg::SearchFilter()
{
	CString strName; m_edtSearchName.GetWindowText(strName);
	CString strDepart; m_edtSearchDepart.GetWindowText(strDepart);
	CString strManager; m_edtSearchManager.GetWindowText(strManager);

	CXTPGridRecords *pRecords = m_lstCustomer.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		ST_CUSTOMER_INFO *st = (ST_CUSTOMER_INFO*)m_lstCustomer.GetItemData(pRecord);

		if(st->strCompany.Find(strName) >= 0 &&
			st->strDepart.Find(strDepart) >= 0 &&
			st->strName.Find(strManager) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstCustomer.Populate();
}

void CSearchCustomerInsungDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
	
	SelectCustomer();
}

void CSearchCustomerInsungDlg::SelectCustomer()
{
	CXTPGridRecord *pRecord = m_lstCustomer.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *st = (ST_CUSTOMER_INFO*)m_lstCustomer.GetItemData(pRecord);

	m_nCNo = st->nCNo;
	m_nTelID = st->nTelID;

	OnOK();
}

void CSearchCustomerInsungDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CSearchCustomerInsungDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_lstCustomer.GetSafeHwnd()) 
		{
			SelectCustomer();
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
