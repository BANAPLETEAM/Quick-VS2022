// RiderCashLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderCashLogDlg.h"


// CRiderCashLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderCashLogDlg, CMyDialog)

CRiderCashLogDlg::CRiderCashLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderCashLogDlg::IDD, pParent)
{
	m_nCompany = ZERO;
	m_nRNo = ZERO;
	m_strRName = "";
}

CRiderCashLogDlg::~CRiderCashLogDlg()
{
}

void CRiderCashLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}


BEGIN_MESSAGE_MAP(CRiderCashLogDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CRiderCashLogDlg::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRiderCashLogDlg �޽��� ó�����Դϴ�.

BOOL CRiderCashLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(ZERO, "����", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(ONE, "���", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(TWO, "����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(THREE, "����", LVCFMT_LEFT, 140);
	m_lstReport.InsertColumn(FOUR, "�ݾ�", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(FIVE, "�����", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(SIX, "����", LVCFMT_LEFT, 160);

	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderCashLogDlg::OnBnClickedOk()
{
	RefreshList();
}

void CRiderCashLogDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();
	char buffer[10];
 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_cash_income_log");

	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nRNo);

	if(!pRs.Execute(&pCmd))
		return;

	long nRNo, nState, nAmount, nWNo;
	CString strRName, strEtc;
	COleDateTime dtGenerate;
	long nAmountS = 0;
	long nCount = pRs.GetRecordCount();

	for(int i = ZERO; i<nCount; i++)
	{
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("sEtc", strEtc);

		m_lstReport.InsertItem(i, ::GetDateTimeToString(dtGenerate, 3, TRUE));
		m_lstReport.SetItemText(i, 1, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(i, 2, strRName);
		m_lstReport.SetItemText(i, 3, GetFixedDepositStateString(nState));
		m_lstReport.SetItemText(i, 4, ::GetMyNumberFormat(nAmount));
		m_lstReport.SetItemText(i, 5, itoa(nWNo, buffer, 10));
		m_lstReport.SetItemText(i, 6, strEtc);

		nAmountS += nAmount;

		pRs.MoveNext();
	}

	m_lstReport.Populate();

	if(nCount > 0)
	{
		CString strTemp;
		strTemp.Format("�����α�(%d/%s) �հ�:%s��", m_nRNo, m_strRName, ::GetMyNumberFormat(nAmountS));
		this->SetWindowText(strTemp);
	}
}


void CRiderCashLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcDlg.right - 4; 
		rcList.bottom = rcDlg.bottom - 4; 

		m_lstReport.MoveWindow(rcList); 
	}
}
