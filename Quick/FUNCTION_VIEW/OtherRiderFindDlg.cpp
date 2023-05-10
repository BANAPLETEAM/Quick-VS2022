// OtherRiderFindDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "OtherRiderFindDlg.h"


// COtherRiderFindDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COtherRiderFindDlg, CDialog)

COtherRiderFindDlg::COtherRiderFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtherRiderFindDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nRNo = 0;
}

COtherRiderFindDlg::~COtherRiderFindDlg()
{
}

void COtherRiderFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(COtherRiderFindDlg, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_RIDER_BTN, &COtherRiderFindDlg::OnBnClickedSearchRiderBtn)
	ON_BN_CLICKED(IDC_OK_BUTTON, &COtherRiderFindDlg::OnBnClickedOkButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &COtherRiderFindDlg::OnBnClickedCancelButton)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
END_MESSAGE_MAP()


void COtherRiderFindDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnBnClickedOkButton();
}

// COtherRiderFindDlg �޽��� ó�����Դϴ�.

void COtherRiderFindDlg::OnBnClickedSearchRiderBtn()
{
	m_lstReport.DeleteAllItems();

	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	if(strSearch == "0" || strSearch == "")
	{
		MessageBox("�ٽ� �Է��� �ּ���" , "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_other_allocate_rider_5");
	CMkParameter *pDeposit = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode5);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
	pCmd.AddParameter(strSearch);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;

	long nCompany, nRNo, nRiderBalance, nDepositType, nWorkState;
	long nShareCode2, nShareCode3, nShareCode4, nShareCode5;
	CString sName, strCompanyName;
	char buffer[20]; 

	long nOrderDeposit = 0; pDeposit->GetValue(nOrderDeposit);


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nRiderBalance", nRiderBalance);
		pRs.GetFieldValue("nDepositType", nDepositType);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("sCompanyName", strCompanyName);

		pRs.GetFieldValue("nShareCode2", nShareCode2);
		pRs.GetFieldValue("nShareCode3", nShareCode3);
		pRs.GetFieldValue("nShareCode4", nShareCode4);
		pRs.GetFieldValue("nShareCode5", nShareCode5);

		m_lstReport.InsertItem(i, m_ci.GetName(nCompany));
		m_lstReport.SetItemText(i, 1, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(i, 2, sName);
		m_lstReport.SetItemLong(i, nCompany);
		m_lstReport.SetItemLong2(i, nRNo);

		pRs.MoveNext();
	}

	m_lstReport.Populate();

	CXTPGridRows *pRows = m_lstReport.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(0);

	m_lstReport.GetSelectedRows()->Select(pRow);

}

void COtherRiderFindDlg::OnBnClickedOkButton()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	m_nCompany = m_lstReport.GetItemLong(pRecord);
	m_nRNo = m_lstReport.GetItemLong2(pRecord);
	m_strName = m_lstReport.GetItemText(pRecord, 2);
	
	OnOK();
}

void COtherRiderFindDlg::OnBnClickedCancelButton()
{
	OnCancel();
}

BOOL COtherRiderFindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "�Ҽ�ȸ��", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "���", LVCFMT_RIGHT, 50);
	m_lstReport.InsertColumn(2, "����", LVCFMT_LEFT, 60);
	m_lstReport.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL COtherRiderFindDlg::PreTranslateMessage(MSG* pMsg)
{

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtSearch.GetSafeHwnd()) 
		{
			OnBnClickedSearchRiderBtn();
			return TRUE;
		}

		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
