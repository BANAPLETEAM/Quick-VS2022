// DepositJobLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "DepositJobLogDlg.h"



// CDepositJobLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDepositJobLogDlg, CMyDialog)
CDepositJobLogDlg::CDepositJobLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDepositJobLogDlg::IDD, pParent)
{
	m_nScheduleID = 0 ;
	m_strDisplayName = "";
}

CDepositJobLogDlg::~CDepositJobLogDlg()
{
}

void CDepositJobLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HELP, m_stcHelp);
	DDX_Control(pDX, IDC_LOG_LIST, m_lstLog);
}


BEGIN_MESSAGE_MAP(CDepositJobLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_JOB_BTN, OnBnClickedRefreshJobBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CDepositJobLogDlg �޽��� ó�����Դϴ�.

BOOL CDepositJobLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	m_stcHelp.SetWindowText("�۾��� : " + m_strDisplayName);

	m_lstLog.InsertColumn(0, "�۾��ð�", LVCFMT_LEFT, 150);
	m_lstLog.InsertColumn(1, "�۾���", LVCFMT_LEFT, 80);
	m_lstLog.InsertColumn(2, "������", LVCFMT_LEFT, 70);
	m_lstLog.InsertColumn(3, "��������", LVCFMT_CENTER, 60);

	m_lstLog.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDepositJobLogDlg::OnBnClickedRefreshJobBtn()
{
	RefreshList();
}

void CDepositJobLogDlg::RefreshList()
{
	m_lstLog.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_log");

	pCmd.AddParameter(m_nScheduleID);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	COleDateTime dtPlay;
	long nApplyRider;
	CString sWName;
	BOOL bSuccess;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtPlay", dtPlay);
		pRs.GetFieldValue("nApplyRider", nApplyRider);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("bSuccess", bSuccess);

		m_lstLog.InsertItem(i, dtPlay.Format(dtPlay.Format("%y-%m-%d %H:%M:%S")));
		m_lstLog.SetItemText(i, 1, sWName);
		m_lstLog.SetItemText(i, 2, (CString)itoa(nApplyRider, buffer, 10) + "��");
		m_lstLog.SetItemText(i, 3, bSuccess == TRUE ? "����" : "����");

		pRs.MoveNext();
	}

	m_lstLog.Populate();
}


void CDepositJobLogDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
