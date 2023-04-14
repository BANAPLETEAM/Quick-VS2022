// RiderSelectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderSelectDlg.h"


// CRiderSelectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderSelectDlg, CMyDialog)

CRiderSelectDlg::CRiderSelectDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderSelectDlg::IDD, pParent)
{

}

CRiderSelectDlg::~CRiderSelectDlg()
{
}

void CRiderSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_LIST, m_lstRider);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CRiderSelectDlg, CMyDialog)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CRiderSelectDlg::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDOK, &CRiderSelectDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_RIDER_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDCANCEL, &CRiderSelectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRiderSelectDlg �޽��� ó�����Դϴ�.

BOOL CRiderSelectDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstRider.InsertColumn(0, "�Ҽ�", LVCFMT_LEFT, 100);
	m_lstRider.InsertColumn(1, "���", LVCFMT_RIGHT, 50);
	m_lstRider.InsertColumn(2, "����", LVCFMT_LEFT, 60);
	m_lstRider.Populate();
 
	RefreshList();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderSelectDlg::RefreshList()
{
	long nItem = 0;
	MAP_ALLOC_RIDER::iterator itRider;
	for(itRider = LU->m_mapAllocateRider.begin(); itRider != LU->m_mapAllocateRider.end(); ++itRider)
	{
		if(m_ci.IsChildCompany(itRider->second.lCode) == FALSE)
			return;

		m_lstRider.InsertItem(nItem, m_ci.GetBranchName(itRider->second.lCode));
		m_lstRider.SetItemText(nItem, 1, GetStringFromLong(itRider->second.nMNo));
		m_lstRider.SetItemText(nItem, 2, itRider->second.strName);

		m_lstRider.SetItemLong(nItem, itRider->second.lCode);
		m_lstRider.SetItemLong2(nItem, itRider->second.nMNo);
		nItem++;
	}

	m_lstRider.Populate();
}

void CRiderSelectDlg::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstRider.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(2)->GetCaption(NULL);

		if(strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstRider.Populate();
}

void CRiderSelectDlg::OnBnClickedOk()
{
	OnOK();
}

void CRiderSelectDlg::OnOK()
{
	CXTPGridRecord *pRecord = m_lstRider.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		MessageBox("ī�带 �Ҵ� �� ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_nCompany = m_lstRider.GetItemLong(pRecord);
	m_nRNo = m_lstRider.GetItemLong2(pRecord);

	CMyDialog::OnOK();
}



void CRiderSelectDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnOK();
}

void CRiderSelectDlg::OnBnClickedCancel()
{
	OnCancel();
}
