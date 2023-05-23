// CheckGroupReportDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CheckGroupReportDlg.h"
#include "HelpGroupReportDlg.h"


// CCheckGroupReportDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCheckGroupReportDlg, CMyDialog)
CCheckGroupReportDlg::CCheckGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCheckGroupReportDlg::IDD, pParent)
{
	m_strNeedReReportID = "";
}

CCheckGroupReportDlg::~CCheckGroupReportDlg()
{
}

void CCheckGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_HELP_BTN, m_btnHelp);
}


BEGIN_MESSAGE_MAP(CCheckGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_HELP_BTN, OnBnClickedHelpBtn)
	ON_BN_CLICKED(IDC_MOVE_BTN, OnBnClickedMoveBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()




BOOL CCheckGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//*8���� �ش� �׷�ɹ��� ��������/�������� �׷����� �̵��ϸ�
	//DATA��¥���� �� ������ �ʿ��� ���곻���� �Ʒ��� �����ϴ�(���¿� �κ��Ա� Ȥ�� �ԱݿϷ�)

	char buffer[20];
	CString str1 = "*" + (CString)itoa(m_nMemberCount, buffer, 10) + "���� �ش� �׷�ɹ���"
		+ m_cg.GetGroupData(m_nDstGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nDstGNo)->strDept + " �׷����� �̵��ϸ�";
	CString str2 = "";

	if(m_dtDate.GetYear() == 2000)
		str2 = "��ü��¥���� �� ������ �ʿ��� ���곻���� �Ʒ��� �����ϴ�(���¿� �κ��Ա� Ȥ�� �ԱݿϷ�)";
	else
		str2 = m_dtDate.Format("%m-%d") + "��¥���� �� ������ �ʿ��� ���곻���� �Ʒ��� �����ϴ�(���¿� �κ��Ա� Ȥ�� �ԱݿϷ�)";

	m_stc1.SetWindowText(str1);
	m_stc2.SetWindowText(str2);
		
	m_lstReport.InsertColumn(0, "�׷��", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "�μ���", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "�����", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(3, "����Ⱓ", LVCFMT_CENTER, 90);
	m_lstReport.InsertColumn(4, "���ݾ�", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(5, "�̼���", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(6, "����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(7, "����", LVCFMT_LEFT, 200);

	m_lstReport.Populate();
	RefreshList();

	m_btnHelp.LoadBitmaps(IDB_HELP_BTN1, IDB_HELP_BTN2);
	m_btnHelp.SizeToContent(); // Button����� �°Բ� Bitmap����� �����մϴ�

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCheckGroupReportDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report_check");

	char buffer[10];

	pCmd.AddParameter(m_strGNo);
	pCmd.AddParameter(m_nDstGNo);
	pCmd.AddParameter(m_dtDate);

	if(!pRs.Execute(&pCmd))
		return;

	long nID, nGNo, nBillCollection, nUnCollection, nReportState;
	CString strGroupName, strDept, strName;
	COleDateTime dtReportStart, dtReportEnd;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nBillCollection", nBillCollection);
		pRs.GetFieldValue("nUnCollection", nUnCollection);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("sGroupName", strGroupName);
		pRs.GetFieldValue("sDept", strDept);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);

		m_lstReport.InsertItem(i, strGroupName);
		m_lstReport.SetItemText(i, 1, strDept);
		m_lstReport.SetItemText(i, 2, strName);
		m_lstReport.SetItemText(i, 3, dtReportStart.Format("%m-%d") + " ~ " + dtReportEnd.Format("%m-%d"));
		m_lstReport.SetItemText(i, 4, LF->RemoveZero(LF->GetMyNumberFormat(nBillCollection)));
		m_lstReport.SetItemText(i, 5, LF->RemoveZero(LF->GetMyNumberFormat(nUnCollection)));
		m_lstReport.SetItemText(i, 6, GetState(nReportState));
		m_lstReport.SetItemText(i, 7, GetStateEtc(nReportState));
		m_lstReport.SetItemLong(i, nReportState);

		if(nReportState == 0)
			m_strNeedReReportID += (CString)itoa(nID, buffer, 10) + ";";
		
		pRs.MoveNext();
	}	 

	m_lstReport.Populate();
}

CString CCheckGroupReportDlg::GetState(long nReportState)
{
	if(nReportState == 0)
		return "����Ϸ�";
	if(nReportState == 10)
		return "�κ��Ա�";
	if(nReportState == 20)
		return "�ԱݿϷ�";

	return "";
}

CString CCheckGroupReportDlg::GetStateEtc(long nReportState)
{
	if(nReportState == 0)
		return "�ڵ�������";
	if(nReportState == 10)
		return "�κ��Ա����� ���� �ڵ������ �Ұ�";
	if(nReportState == 20)
		return "�ԱݿϷ�� ���� �ڵ������ �Ұ�";

	return "";
}

void CCheckGroupReportDlg::OnBnClickedButton1()
{
	CMyExcel::ToExcel(&m_lstReport);
}

void CCheckGroupReportDlg::OnBnClickedHelpBtn()
{
	CHelpGroupReportDlg dlg;
	dlg.DoModal();
}

void CCheckGroupReportDlg::OnBnClickedMoveBtn()
{
	OnOK();	
}

void CCheckGroupReportDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
