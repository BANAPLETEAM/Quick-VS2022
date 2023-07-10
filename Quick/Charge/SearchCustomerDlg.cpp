// SearchGroupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SearchCustomerDlg.h"

#define ST_TEL_MOBILE  2
#define ST_COMPANY_NAMET  0
#define ST_NAME_DEPART  12


// CSearchGroupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSearchCustomerDlg, CMyDialog)
CSearchCustomerDlg::CSearchCustomerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSearchCustomerDlg::IDD, pParent)
{
	m_nCompany = 0;	
	m_strCNoList = "";
	m_strReturnCustomer = "";
	m_strReturnTel = "";
	m_strReturnDept = "";
	m_strReturnName = "";	
	m_strReturnHP = "";

	m_nReturnCNo = 0;
	m_nReturnMemCNo = 0;
	m_bTypeCustomerChange = FALSE;
}

CSearchCustomerDlg::~CSearchCustomerDlg()
{ 
}

void CSearchCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_NAME_EDIT, m_edtSearchName);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbSearchType);
	DDX_Control(pDX, IDC_CUSTOM1, m_lstSearch);
	DDX_Control(pDX, IDC_HISTORY_CHARGE_INPUT_BTN, m_btnHistoryChargeInput);
}


BEGIN_MESSAGE_MAP(CSearchCustomerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CSearchCustomerDlg::OnBnClickedSearchBtn)

	ON_BN_CLICKED(IDC_HISTORY_CHARGE_INPUT_BTN, &CSearchCustomerDlg::OnBnClickedHistoryChargeInputBtn)
	ON_BN_CLICKED(IDC_SELECT_CUSTOMER_BTN, &CSearchCustomerDlg::OnBnClickedSelectCustomerBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnNMDblClkList)
END_MESSAGE_MAP()




BOOL CSearchCustomerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_cmbSearchType.SetCurSel(0);
	m_edtSearchName.SetFocus();

	m_lstSearch.InsertColumn(0, "ȸ���", 100, DT_LEFT);
	m_lstSearch.InsertColumn(1, "�μ���", 60, DT_LEFT);
	m_lstSearch.InsertColumn(2, "�����", 60, DT_LEFT);
	m_lstSearch.InsertColumn(3, "��ǥ��ȣ", 80, DT_LEFT);
	m_lstSearch.InsertColumn(4, "�޴���", 80, DT_LEFT);
	m_lstSearch.InsertColumn(5, "�ش絿", 60, DT_LEFT);		
	m_lstSearch.InsertColumn(6, "������ݸ�", 100, DT_LEFT);
	m_lstSearch.InsertColumn(7, "�׷��", 70, DT_LEFT);
	m_lstSearch.InsertColumn(8, "�����", 90, DT_LEFT);
	m_lstSearch.Populate();
	
	if(m_bTypeCustomerChange)
	{
		m_btnHistoryChargeInput.ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CSearchCustomerDlg::Apply()
{
	if(m_lstSearch.GetSelectedRows()->GetCount() <= 0)
	{
		MessageBox("�����̶� �����Ͽ� �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("�ش� ������ ����������� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_YESNO) == IDNO)
		return;

	CString sCNo = "", sTotalCNo = "";
	for(int i =0; i < m_lstSearch.GetSelectedRows()->GetCount(); i++)
	{
		long nCNo = m_lstSearch.GetItemLong(i);
		sCNo.Format("%ld", nCNo);
		sTotalCNo += sCNo + ",";
	}

	m_strCNoList = sTotalCNo;
	OnOK();
}

void CSearchCustomerDlg::OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	ChangeCustomer();		
}

void CSearchCustomerDlg::OnBnClickedSelectCustomerBtn()
{
	ChangeCustomer();
}
void CSearchCustomerDlg::ChangeCustomer()
{
	if(m_lstSearch.GetSelectedRows()->GetCount() <= 0)
	{
		MessageBox("�����̶� �����Ͽ� �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = m_lstSearch.GetFirstSelectedRecord();
	m_strReturnCustomer = pRecord->GetItem(0)->GetCaption();
	m_strReturnDept = pRecord->GetItem(1)->GetCaption();
	m_strReturnName = pRecord->GetItem(2)->GetCaption();
	m_strReturnTel = pRecord->GetItem(3)->GetCaption();
	m_strReturnHP = pRecord->GetItem(4)->GetCaption();
	m_nReturnMemCNo = m_lstSearch.GetItemLong2(pRecord);
	m_nReturnCNo = m_lstSearch.GetItemLong(pRecord);

	OnOK();
}



void CSearchCustomerDlg::OnBnClickedSearchBtn()
{
	CString strSearchData = "";
	m_edtSearchName.GetWindowText(strSearchData);
	int nSearchType = -1;

	switch(m_cmbSearchType.GetCurSel())
	{
		// ��ȣ��;��ȭ��ȣ;�����;
	case 0:
		nSearchType = ST_TEL_MOBILE;
		break;
	case 1:
		nSearchType = ST_COMPANY_NAMET;
		break;
	case 2:
		nSearchType = ST_NAME_DEPART;
		break;
	}
	if(m_lstSearch.GetRecords()->GetCount() > 0)
		m_lstSearch.DeleteAllItems();

	LU->LoadMemberCharge();
	MAP_MEMBER_CHARGE_CNO::iterator itMem;

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "search_customer_new13");	
	pCmd2.AddParameter(nSearchType);			
	pCmd2.AddParameter(m_nCompany);			
	pCmd2.AddParameter(strSearchData);
	pCmd2.AddParameter(FALSE);

	if(pRs2.Execute(&pCmd2))
	{		
		for(int i = 0; i < pRs2.GetRecordCount(); i++)
		{
			long nCNo, nCompany, nMemCNo, nGNo ;
			CString strCompany, strDepart, strName, strDong, strTel1, strMobile, strGroupName = "", strHistoryChargeName = "";
			COleDateTime dtRegister;
			
			pRs2.GetFieldValue("nCNo", nCNo);
			pRs2.GetFieldValue("nCompany", nCompany);
			pRs2.GetFieldValue("sCompany", strCompany);
			pRs2.GetFieldValue("sDepart", strDepart);
			pRs2.GetFieldValue("sName", strName);
			pRs2.GetFieldValue("sTel1", strTel1);
			pRs2.GetFieldValue("sMobile", strMobile);
			pRs2.GetFieldValue("sDong", strDong);
			pRs2.GetFieldValue("dtRegister", dtRegister);
			pRs2.GetFieldValue("nCustDisplayCharge", nMemCNo);
			pRs2.GetFieldValue("nGNo", nGNo);
			pRs2.GetFieldValue("sMemCompany", strHistoryChargeName);

			//itMem = m_mapMemberCharge.find(nMemCNo);
			//if(itMem != m_mapMemberCharge.end())
			//	strHistoryChargeName = (*itMem).second->strMemCompany;

			strGroupName = m_cg.GetGroupData(nGNo)->strGroupName;

			m_lstSearch.InsertItem(i, strCompany);
			m_lstSearch.SetItemText(i, 1, strDepart);
			m_lstSearch.SetItemText(i, 2, strName);
			m_lstSearch.SetItemText(i, 3, LF->GetDashPhoneNumber(strTel1));
			m_lstSearch.SetItemText(i, 4, LF->GetDashPhoneNumber(strMobile));
			m_lstSearch.SetItemText(i, 5, strDong);
			m_lstSearch.SetItemText(i, 6, strHistoryChargeName);
			m_lstSearch.SetItemText(i, 7, strGroupName);
			m_lstSearch.SetItemText(i, 8, dtRegister.Format("%Y-%m-%d"));
			m_lstSearch.SetItemLong(i, nCNo);		
			m_lstSearch.SetItemLong2(i, nMemCNo);		
			pRs2.MoveNext();	
		}
		
	}
	pRs2.Close();
	m_lstSearch.Populate();	
}


BOOL CSearchCustomerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_edtSearchName.GetSafeHwnd())
				OnBnClickedSearchBtn();

			return TRUE;
		}

	}
	
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSearchCustomerDlg::OnBnClickedHistoryChargeInputBtn()
{
	Apply();
}

