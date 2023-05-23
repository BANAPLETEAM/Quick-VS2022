// TransferSBSLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "TransferSBSLogDlg.h"


// CTransferSBSLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTransferSBSLogDlg, CDialog)

CTransferSBSLogDlg::CTransferSBSLogDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTransferSBSLogDlg::IDD, pParent)
{

}

CTransferSBSLogDlg::~CTransferSBSLogDlg()
{
}

void CTransferSBSLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);

	DDX_Control(pDX, IDC_REPORT_CTRL, m_lstReport);
}


BEGIN_MESSAGE_MAP(CTransferSBSLogDlg, CDialog)
	ON_BN_CLICKED(ID_REFRESH_BTN, &CTransferSBSLogDlg::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CTransferSBSLogDlg::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDCANCEL, &CTransferSBSLogDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTransferSBSLogDlg �޽��� ó�����Դϴ�.

void CTransferSBSLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CTransferSBSLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);  
	m_btnData.OnMenuMonthIncludeToday(); 

	m_lstReport.InsertColumn(0, "����", LVCFMT_LEFT, 40);
	m_lstReport.InsertColumn(1, "��¥", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "��������", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "��������", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(4, "Ÿ��", LVCFMT_LEFT, 165);
	m_lstReport.InsertColumn(5, "�ݾ�", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(6, "�۾���", LVCFMT_LEFT, 120);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTransferSBSLogDlg::OnEnChangeSearchEdit()
{	

}

void CTransferSBSLogDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_transfer_sbs_log");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo); 

	if(!rs.Execute(&cmd)) return;
	long nCount = rs.GetRecordCount();

	long nFromCompany, nToCompany, nType, nCharge, nWCompany;
	COleDateTime dtGenerate;
	CString strWName;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nFromCompany", nFromCompany);
		rs.GetFieldValue("nToCompany", nToCompany);
		rs.GetFieldValue("nType", nType);
		rs.GetFieldValue("nCharge", nCharge);
		rs.GetFieldValue("nWCompany", nWCompany);
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("sWName", strWName);

		m_lstReport.InsertItem(i, LF->GetStringFromLong(i));
		m_lstReport.SetItemText(i, 1, dtGenerate.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, m_ci.GetShareCompanyBranchName(nFromCompany));
		m_lstReport.SetItemText(i, 3, m_ci.GetShareCompanyBranchName(nToCompany));
		m_lstReport.SetItemText(i, 4, GetTransferType(nType));
		m_lstReport.SetItemText(i, 5, LF->GetMyNumberFormat(nCharge));
		m_lstReport.SetItemText(i, 6, m_ci.GetShareCompanyBranchName(nWCompany) + "/" + strWName);
		m_lstReport.SetItemLong(i, nType);

		rs.MoveNext();
	}

	m_lstReport.Populate();
}

CString CTransferSBSLogDlg::GetTransferType(long nType)
{
	if(nType == 1)
		return "���������ܾ� -> SMS�ܾ�";
	else if(nType == 2)
		return "SMS�ܾ� -> ���������ܾ�";

	return "******";
}

void CTransferSBSLogDlg::OnBnClickedCancel()
{
	OnCancel();
}
