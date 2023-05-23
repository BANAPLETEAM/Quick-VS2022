// SearchCustomerInsungRcpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SearchCustomerInsungRcpDlg.h"


// CSearchCustomerInsungRcpDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchCustomerInsungRcpDlg, CDialog)

CSearchCustomerInsungRcpDlg::CSearchCustomerInsungRcpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchCustomerInsungRcpDlg::IDD, pParent)
{
	m_nCompany = 0;
}

CSearchCustomerInsungRcpDlg::~CSearchCustomerInsungRcpDlg()
{
}

void CSearchCustomerInsungRcpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_STATIC, m_stcBranch);
	DDX_Control(pDX, IDC_NAME_STATIC, m_stcName);
	DDX_Control(pDX, IDC_TEL_STATIC, m_stcTel);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
}


BEGIN_MESSAGE_MAP(CSearchCustomerInsungRcpDlg, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, &CSearchCustomerInsungRcpDlg::OnBnClickedSearchButton)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnReportItemDblClick)
END_MESSAGE_MAP()


// CSearchCustomerInsungRcpDlg 메시지 처리기입니다.

BOOL CSearchCustomerInsungRcpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstCustomer.InsertColumn(0, "", LVCFMT_LEFT, 30);
	m_lstCustomer.InsertColumn(1, "고객명", LVCFMT_LEFT, 100);
	m_lstCustomer.InsertColumn(2, "전화번호", LVCFMT_LEFT, 100);
	m_lstCustomer.InsertColumn(3, "부서명", LVCFMT_LEFT, 100);
	m_lstCustomer.InsertColumn(4, "담당/직위", LVCFMT_LEFT, 80);
	m_lstCustomer.InsertColumn(5, "기준동", LVCFMT_CENTER, 80);
	m_lstCustomer.InsertColumn(6, "구분", LVCFMT_CENTER, 40);
	m_lstCustomer.InsertColumn(7, "상세위치", LVCFMT_LEFT, 200);
	m_lstCustomer.InsertColumn(8, "메모", LVCFMT_LEFT, 200);
	m_lstCustomer.SetOrderIndexCol(0);
	m_lstCustomer.Populate();

	BOOL bSelectBranch = FALSE;

	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);

		int nIndex = m_cmbBranch.AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
		m_cmbBranch.SetItemData(nIndex, pBi->nCompanyCode);

		if(m_nCompany == pBi->nCompanyCode)
		{
			m_cmbBranch.SetCurSel(nIndex);
			bSelectBranch = TRUE;
		}
	}

	if(!bSelectBranch)
		m_cmbBranch.SetCurSel(ZERO);

	if(m_nCNo > 0)
		RefreshCNo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchCustomerInsungRcpDlg::RefreshCNo()
{
	long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	long nCusCompany = LF->GetBranchInfo(nCompany)->nCustomerTable;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_like_insung_rcp_cno");
	cmd.AddParameter(nCusCompany);
	cmd.AddParameter(m_nCNo);

	if(!rs.Execute(&cmd))
		return;

	RefreshSub(&rs);
}

void CSearchCustomerInsungRcpDlg::OnBnClickedSearchButton()
{
	RefreshList();
}

void CSearchCustomerInsungRcpDlg::RefreshList()
{
	m_lstCustomer.DeleteAllItems();

	CString strShName; m_edtName.GetWindowText(strShName);
	CString strShTel; m_edtTel.GetWindowText(strShTel);

	long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	long nCusCompany = LF->GetBranchInfo(nCompany)->nCustomerTable;

	if(strShName.IsEmpty() && strShTel.IsEmpty())
		return;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_like_insung_rcp");
	cmd.AddParameter(nCusCompany);
	cmd.AddParameter(strShName);
	cmd.AddParameter(strShTel);

	if(!rs.Execute(&cmd))
		return;

	RefreshSub(&rs);
}

void CSearchCustomerInsungRcpDlg::RefreshSub(CMkRecordset *rs)
{
	long nCNo, nTelID, bCredit;
	CString strName, strTel, strDepart, strManager, strDong, strLocation, strMemo;

	for(int i=0; i<rs->GetRecordCount(); i++)
	{
		rs->GetFieldValue("sName", strName);
		rs->GetFieldValue("sTel", strTel);
		rs->GetFieldValue("sDepart", strDepart);
		rs->GetFieldValue("sManager", strManager);
		rs->GetFieldValue("sDong", strDong);
		rs->GetFieldValue("sLocation", strLocation);
		rs->GetFieldValue("sMemo", strMemo);
		rs->GetFieldValue("nCNo", nCNo);
		rs->GetFieldValue("nTelID", nTelID);
		rs->GetFieldValue("bCredit", bCredit);

		CString strTemp = "";
		if(bCredit == 1) strTemp = "신용";
		else if(bCredit == 2) strTemp = "송금";
		else if(bCredit == 3) strTemp = "카드";

		m_lstCustomer.InsertItem(i, "");
		m_lstCustomer.SetItemText(i, 1, strName);
		m_lstCustomer.SetItemText(i, 2, strTel);
		m_lstCustomer.SetItemText(i, 3, strDepart);
		m_lstCustomer.SetItemText(i, 4, strManager);
		m_lstCustomer.SetItemText(i, 5, strDong);
		m_lstCustomer.SetItemText(i, 6, strTemp);
		m_lstCustomer.SetItemText(i, 7, strLocation);
		m_lstCustomer.SetItemText(i, 8, strMemo);
		m_lstCustomer.SetItemLong(i, nCNo);
		m_lstCustomer.SetItemLong2(i, nTelID);

		rs->MoveNext();
	}

	m_lstCustomer.Populate();
}


void CSearchCustomerInsungRcpDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRecord *pRecord = m_lstCustomer.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_nCNo = m_lstCustomer.GetItemLong(pRecord);
	m_nTelID = m_lstCustomer.GetItemLong2(pRecord);

	OnOK();
}

BOOL CSearchCustomerInsungRcpDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)		 
		{  
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_NAME_EDIT:
			case IDC_TEL_EDIT:
				RefreshList();
				return FALSE;
				break;
			}

			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
