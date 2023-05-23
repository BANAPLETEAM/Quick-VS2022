// TransferSBSLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "TransferSBSLogDlg.h"


// CTransferSBSLogDlg 대화 상자입니다.

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


// CTransferSBSLogDlg 메시지 처리기입니다.

void CTransferSBSLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CTransferSBSLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);  
	m_btnData.OnMenuMonthIncludeToday(); 

	m_lstReport.InsertColumn(0, "순번", LVCFMT_LEFT, 40);
	m_lstReport.InsertColumn(1, "날짜", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "차감지사", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "충전지사", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(4, "타입", LVCFMT_LEFT, 165);
	m_lstReport.InsertColumn(5, "금액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(6, "작업자", LVCFMT_LEFT, 120);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
		return "공동정산잔액 -> SMS잔액";
	else if(nType == 2)
		return "SMS잔액 -> 공동정산잔액";

	return "******";
}

void CTransferSBSLogDlg::OnBnClickedCancel()
{
	OnCancel();
}
