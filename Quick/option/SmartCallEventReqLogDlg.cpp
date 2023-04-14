// SmartCallEventReqLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SmartCallEventReqLogDlg.h"


// CSmartCallEventReqLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmartCallEventReqLogDlg, CMyDialog)

CSmartCallEventReqLogDlg::CSmartCallEventReqLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSmartCallEventReqLogDlg::IDD, pParent)
{

}

CSmartCallEventReqLogDlg::~CSmartCallEventReqLogDlg()
{
}

void CSmartCallEventReqLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lstReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
}


BEGIN_MESSAGE_MAP(CSmartCallEventReqLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSmartCallEventReqLogDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_EXCEL_BTN, &CSmartCallEventReqLogDlg::OnBnClickedExcelBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CSmartCallEventReqLogDlg::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CSmartCallEventReqLogDlg 메시지 처리기입니다.
BOOL CSmartCallEventReqLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();

	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "날짜", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(2, "전화번호", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "성명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(4, "주소", LVCFMT_LEFT, 200);
	m_lstReport.InsertColumn(5, "차감마일리지", LVCFMT_LEFT, 60);

	//m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();

	OnBnClickedRefreshBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmartCallEventReqLogDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CSmartCallEventReqLogDlg::OnBnClickedExcelBtn()
{
	if(!POWER_CHECK(2010, "엑셀변환", TRUE))
		return; 

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 109, m_lstReport.GetItemCount());
	CMyExcel::ToExcel(&m_lstReport);
}

void CSmartCallEventReqLogDlg::OnBnClickedRefreshBtn()
{
	m_lstReport.DeleteAllItems();
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_smart_call_event_req_log_1");
	cmd.AddParameter(m_nBoardID);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	COleDateTime dtRequest;
	CString strPhone, strReqName, strReqLocation;
	long nUseMileage;

	for(long i = 0; i < rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("dtRequest", dtRequest);
		rs.GetFieldValue("sPhone", strPhone);
		rs.GetFieldValue("sReqName", strReqName);
		rs.GetFieldValue("sReqLocation", strReqLocation);
		rs.GetFieldValue("nUseMileage", nUseMileage);


		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, dtRequest.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, ::GetDashPhoneNumber(strPhone));
		m_lstReport.SetItemText(i, 3, strReqName);
		m_lstReport.SetItemText(i, 4, strReqLocation);
		m_lstReport.SetItemText(i, 5, ::GetMyNumberFormat(nUseMileage));
		rs.MoveNext();
	}

	m_lstReport.Populate();
}
