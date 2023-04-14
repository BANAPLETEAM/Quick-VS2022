// workStateChangeLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "workStateChangeLogDlg.h"


// CWorkStateChangeLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWorkStateChangeLogDlg, CMyDialog)

CWorkStateChangeLogDlg::CWorkStateChangeLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWorkStateChangeLogDlg::IDD, pParent)
{

}

CWorkStateChangeLogDlg::~CWorkStateChangeLogDlg()
{
}

void CWorkStateChangeLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
}


BEGIN_MESSAGE_MAP(CWorkStateChangeLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_ALL_BTN, &CWorkStateChangeLogDlg::OnBnClickedRefreshAllBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CWorkStateChangeLogDlg::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CWorkStateChangeLogDlg 메시지 처리기입니다.

BOOL CWorkStateChangeLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuMonthIncludeToday();

	m_lstReport.InsertColumn(0, "수정일", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(1, "사번", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(2, "기사명", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(3, "작업자", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "변경내역", LVCFMT_LEFT, 140);
	m_lstReport.Populate();

	RefreshList(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWorkStateChangeLogDlg::RefreshList(BOOL bAll)
{
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_work_state_change_log_1");
	
	cmd.AddParameter(bAll);
	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nRNo;
	CString strWName, strChange, strRName;
	COleDateTime dtGenerate;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("sChange", strChange);
		rs.GetFieldValue("dtGenerate", dtGenerate);

		m_lstReport.InsertItem(i, dtGenerate.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, ::GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 2, strRName);
		m_lstReport.SetItemText(i, 3, strWName);
		m_lstReport.SetItemText(i, 4, strChange);

		rs.MoveNext();
	}	

	m_lstReport.Populate();

}

void CWorkStateChangeLogDlg::OnBnClickedRefreshAllBtn()
{
	RefreshList(TRUE);
}

void CWorkStateChangeLogDlg::OnEnChangeSearchEdit()
{
	CString strSearch;
	GetDlgItem(IDC_SEARCH_EDIT)->GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(2)->GetCaption(NULL);

		if(strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}
