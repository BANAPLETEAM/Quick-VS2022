// ShareReportRateLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateLogDlg.h"



// CShareReportRateLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareReportRateLogDlg, CMyDialog)
CShareReportRateLogDlg::CShareReportRateLogDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CShareReportRateLogDlg::IDD, pParent)
{
}


CShareReportRateLogDlg::CShareReportRateLogDlg(CWnd* pParent /*=NULL*/,long nShareCode1A,long nShareCode1B)
	: CMyDialog(CShareReportRateLogDlg::IDD, pParent)
{
	m_nShareCode1A = nShareCode1A;
	m_nShareCode1B = nShareCode1B; 
}

CShareReportRateLogDlg::~CShareReportRateLogDlg()
{
}

void CShareReportRateLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RATELOG_LIST, m_RateLog_List);
}


BEGIN_MESSAGE_MAP(CShareReportRateLogDlg, CMyDialog)
END_MESSAGE_MAP()


// CShareReportRateLogDlg �޽��� ó�����Դϴ�.

BOOL CShareReportRateLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_RateLog_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_RateLog_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_RateLog_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_RateLog_List.InsertColumn(0, "����", LVCFMT_LEFT, 30);
	m_RateLog_List.InsertColumn(1, "�ݺ�", LVCFMT_LEFT, 50);
	m_RateLog_List.InsertColumn(2, "�ð�", LVCFMT_LEFT, 50);
	m_RateLog_List.InsertColumn(3, "�߻���", LVCFMT_LEFT, 120);
	m_RateLog_List.InsertColumn(4, "������", LVCFMT_LEFT, 70);
	m_RateLog_List.InsertColumn(5, "�Ҽ�ȸ��", LVCFMT_LEFT, 100);
	m_RateLog_List.InsertColumn(6, "", LVCFMT_LEFT, 0);

	RefreshLogList();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CShareReportRateLogDlg::RefreshLogList()
{
	CString sCompany;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_call_share_rate_change_log2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShareCode1A);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nShareCode1B);
	CMkParameter *parRet = pCmd.AddParameter(typeString, typeOutput, sCompany.GetLength());

	if(!pRs.Execute(&pCmd)) return;

	parRet->GetValue(sCompany);
	SetWindowText(sCompany);

	long nRcpRate, nId, nWCompany, nShareTime;
	COleDateTime dtLog;
	CString strWName;
	BOOL bEditShareTime;
	int nItem = 0;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nRcpRate", nRcpRate);
		pRs.GetFieldValue("nShareTime", nShareTime);
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("nWCompany", nWCompany);
		pRs.GetFieldValue("nId", nId);
		pRs.GetFieldValue("bEditShareTime", bEditShareTime);

		CString strId, strRcpRate, strItem, strShareTime;
		strId.Format("%d", nId);
		strRcpRate.Format("%d%%", nRcpRate);
		strItem.Format("%d", nItem);
		strShareTime.Format("%d��", nShareTime);

		m_RateLog_List.InsertItem(nItem, strItem);
		m_RateLog_List.SetItemText(nItem, 1, bEditShareTime ? "-" : strRcpRate);
		m_RateLog_List.SetItemText(nItem, 2, bEditShareTime ? strShareTime : "-");
		m_RateLog_List.SetItemText(nItem, 3, dtLog.Format("%y-%m-%d %H:%M"));
		m_RateLog_List.SetItemText(nItem, 4, strWName);
		m_RateLog_List.SetItemText(nItem, 5, m_ci.GetBranchName(nWCompany));
		m_RateLog_List.SetItemText(nItem, 6, strId);

		nItem ++;

		pRs.MoveNext();
	}
}

