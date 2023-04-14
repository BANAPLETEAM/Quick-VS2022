// OtherRiderTransferLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OtherRiderTransferLogDlg.h"


// COtherRiderTransferLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COtherRiderTransferLogDlg, CMyDialog)

COtherRiderTransferLogDlg::COtherRiderTransferLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COtherRiderTransferLogDlg::IDD, pParent)
{

}

COtherRiderTransferLogDlg::~COtherRiderTransferLogDlg()
{
}

void COtherRiderTransferLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_To);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(COtherRiderTransferLogDlg, CMyDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COtherRiderTransferLogDlg 메시지 처리기입니다.

BOOL COtherRiderTransferLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_btnDate.InitDateButton(&m_dtFrom, &m_dtTo);
	m_btnDate.OnMenuMonth();

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(1, "기사회사", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "사번", LVCFMT_RIGHT, 45);
	m_lstReport.InsertColumn(3, "기사명", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(4, "이체회사", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(5, "금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(6, "작업자", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(7, "적요", LVCFMT_LEFT, 200);
	m_lstReport.Populate();

	RefreshList();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COtherRiderTransferLogDlg::RefreshList()
{
	UpdateData(TRUE);
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_other_rirder_transfer_log");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_From);
	cmd.AddParameter(m_To);

	if(!rs.Execute(&cmd))
		return;

	COleDateTime dtGenerate;
	long nRiderCompany, nRNo, nCompany, nCharge, nWNo, nWCompany;
	CString strRName, strWName, strEtc;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("nRiderCompany", nRiderCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nCharge", nCharge);
		rs.GetFieldValue("nWNo", nWNo);
		rs.GetFieldValue("nWCompany", nWCompany);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("sEtc", strEtc);

		m_lstReport.InsertItem(i, dtGenerate.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, m_ci.GetCompanyName(nRiderCompany));
		m_lstReport.SetItemText(i, 2, ::GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 3, strRName);
		m_lstReport.SetItemText(i, 4, m_ci.GetCompanyName(nCompany));
		m_lstReport.SetItemText(i, 5, ::GetMyNumberFormat(nCharge));
		m_lstReport.SetItemText(i, 6, strWName);
		m_lstReport.SetItemText(i, 7, strEtc);
		m_lstReport.SetItemLong(i, nRiderCompany);
		
		rs.MoveNext();
	}
	m_lstReport.Populate();
}

void COtherRiderTransferLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 5;
		rcList.bottom = rcForm.bottom - 5;
		m_lstReport.MoveWindow(rcList);
	}
}
