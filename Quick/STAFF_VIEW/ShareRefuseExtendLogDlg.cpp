// ShareRefuseExtendLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareRefuseExtendLogDlg.h"


// CShareRefuseExtendLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareRefuseExtendLogDlg, CDialog)

CShareRefuseExtendLogDlg::CShareRefuseExtendLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShareRefuseExtendLogDlg::IDD, pParent)
{

}

CShareRefuseExtendLogDlg::~CShareRefuseExtendLogDlg()
{
}

void CShareRefuseExtendLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_REPORT, m_lstReport);
}


BEGIN_MESSAGE_MAP(CShareRefuseExtendLogDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CShareRefuseExtendLogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CShareRefuseExtendLogDlg �޽��� ó�����Դϴ�.

BOOL CShareRefuseExtendLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "������", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(1, "�۾���", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(2, "���泻��", LVCFMT_LEFT, 240);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;
}

void CShareRefuseExtendLogDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_credit_info_extend_log");
	cmd.AddParameter(m_nID);

	if(!rs.Execute(&cmd))
		return;

	COleDateTime dtGenerate, dtPrePenaltyEnd, dtPenaltyEnd;
	CString strWName;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("dtPrePenaltyEnd", dtPrePenaltyEnd);
		rs.GetFieldValue("dtPenaltyEnd", dtPenaltyEnd);
		rs.GetFieldValue("sWName", strWName);

		m_lstReport.InsertItem(i, dtGenerate.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, strWName);
		m_lstReport.SetItemText(i, 2, dtPrePenaltyEnd.Format("%Y-%m-%d %H:%M") + " -> " + dtPenaltyEnd.Format("%Y-%m-%d %H:%M"));

		rs.MoveNext();
	}

	m_lstReport.Populate();

}
void CShareRefuseExtendLogDlg::OnBnClickedOk()
{
	OnOK();
}
