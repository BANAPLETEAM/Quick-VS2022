// RiderInitLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderInitLogDlg.h"


// CRiderInitLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderInitLogDlg, CMyDialog)

CRiderInitLogDlg::CRiderInitLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderInitLogDlg::IDD, pParent)
{

}

CRiderInitLogDlg::~CRiderInitLogDlg()
{
}

void CRiderInitLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
}


BEGIN_MESSAGE_MAP(CRiderInitLogDlg, CMyDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRiderInitLogDlg 메시지 처리기입니다.

BOOL CRiderInitLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(1, "소속", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_RIGHT, 50);
	m_lstReport.InsertColumn(3, "기사명", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "작업자", LVCFMT_LEFT, 120);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;
}

void CRiderInitLogDlg::RefreshList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_init_rider_log");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nRNo);

	if(!rs.Execute(&cmd))
		return;

	long nRNo, nWNo, nCompany;
	CString strRName, strWName;
	COleDateTime dtGenerate;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("nWNo", nWNo);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("dtGenerate", dtGenerate);

		m_lstReport.InsertItem(i, dtGenerate.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, m_ci.GetBranchName(nCompany));
		m_lstReport.SetItemText(i, 2, ::GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 3, strRName);
		m_lstReport.SetItemText(i, 4, strWName + "(" + ::GetStringFromLong(nWNo) + ")");
	}

	m_lstReport.Populate();
}

void CRiderInitLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);


	if(IsWindow(m_lstReport.GetSafeHwnd()))
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcDlg.right - 1;
		rcList.bottom = rcDlg.bottom - 1; 

		m_lstReport.MoveWindow(rcList);
	}
}
