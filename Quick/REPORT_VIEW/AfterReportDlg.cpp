// AfterReportDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "AfterReportDlg.h"


// CAfterReportDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAfterReportDlg, CMyDialog)
CAfterReportDlg::CAfterReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAfterReportDlg::IDD, pParent)
{
}

CAfterReportDlg::~CAfterReportDlg()
{
}

void CAfterReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
}


BEGIN_MESSAGE_MAP(CAfterReportDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CAfterReportDlg �޽��� ó�����Դϴ�.

void CAfterReportDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CAfterReportDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CAfterReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	this->SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nGNo)->strDept);

	//m_Report.InsertColumn(0, "����", LVCFMT_LEFT, 120);

	CXTPGridColumn* pCol0 = m_Report.AddColumn(new CXTPGridColumn(0, _T("�׷��"), 150));

	m_Report.InsertColumn(1, "����", LVCFMT_LEFT, 80);
	m_Report.InsertColumn(2, "����", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(3, "�ſ�", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(4, "�۱�", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(5, "Ź��", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(6, "�հ�(��+��/��+��+Ź)", LVCFMT_LEFT, 120);

	m_Report.GetPaintManager()->m_strNoItems = "���� �Ϻ� ��볻���� �����ϴ�";
	m_Report.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_Report.SetGridColor(RGB(255, 255, 255));

	pCol0->SetTreeColumn(1);	
	m_Report.SetTreeIndent(10);

	m_Report.Populate();
	RefreshList();



	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAfterReportDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	long nRet = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_after_report_by_group");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bAll);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRet);

	if(nRet == 10)
	{
		MessageBox("������ �������� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
	}

	CString sDate;
	long nCashCount, nCashCharge, nCreditCount, nCreditCharge, nOnlineCount, nOnlineCharge, nTransCount, nTransCharge;
	CString sFormat; 
	long nGNo = 0, nPrenGNo = 0;

	CXTPGridRecord *pTopRecord;
	CXTPGridRecord *pBottomRecord;


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nOGNo", nGNo);

		if(nGNo != nPrenGNo)
		{
			pTopRecord = m_Report.AddRecord(new CAfterReportRecord(nGNo));
			pTopRecord->SetExpanded(TRUE);;
		}		

		pRs.GetFieldValue("sDate", sDate);
		pRs.GetFieldValue("nCashCount", nCashCount);
		pRs.GetFieldValue("nCashCharge", nCashCharge);
		pRs.GetFieldValue("nCreditCount", nCreditCount);
		pRs.GetFieldValue("nCreditCharge", nCreditCharge);
		pRs.GetFieldValue("nOnlineCount", nOnlineCount);
		pRs.GetFieldValue("nOnlineCharge", nOnlineCharge);
		pRs.GetFieldValue("nTransCount", nTransCount);
		pRs.GetFieldValue("nTransCharge", nTransCharge);

		pBottomRecord = pTopRecord->GetChilds()->Add(new CAfterReportRecord(nGNo, sDate, nCashCount, nCashCharge, nCreditCount, nCreditCharge,
								nOnlineCount, nOnlineCharge, nTransCount, nTransCharge));
		pBottomRecord->SetExpanded(TRUE);

		nPrenGNo = nGNo;

		pRs.MoveNext();
	}

	m_Report.Populate();

}
