// InsStaffDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "InsStaffDlg1.h"


// CInsStaffDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInsStaffDlg1, CMyDialog)

CInsStaffDlg1::CInsStaffDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CInsStaffDlg1::IDD, pParent)
{

}

CInsStaffDlg1::~CInsStaffDlg1()
{
}

void CInsStaffDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DAY, m_dtpDay);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CInsStaffDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CInsStaffDlg1::OnBnClickedRefreshButton)
	ON_BN_CLICKED(IDC_EXCEL_BUTTON, &CInsStaffDlg1::OnBnClickedExcelButton)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CInsStaffDlg1::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


void CInsStaffDlg1::RefreshList()
{
	m_lstReport.DeleteAllItems();

	COleDateTime dtDay;
	m_dtpDay.GetTime(dtDay);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_load_ins_staff_page1");
	cmd.AddParameter(m_ui.strID);
	cmd.AddParameter(dtDay);

	if(!rs.Execute(&cmd))
		return;

	CString strDays, strCarNo;
	long nInsCarType;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{			
		rs.GetFieldValue("sCarNo", strCarNo);
		rs.GetFieldValue("sDays", strDays);
		rs.GetFieldValue("nInsCarType", nInsCarType);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, strCarNo);		

		CString strTemp = "";

		if(nInsCarType == 0)
			strTemp = "소형화물";
		if(nInsCarType == 1)
			strTemp = "오토바이";
		if(nInsCarType == 2)
			strTemp = "지하철";

		m_lstReport.SetItemText(i, 2, strTemp);
		m_lstReport.SetItemText(i, 3, LF->GetStringFromLong(LF->GetCommaCount(strDays)));
		m_lstReport.SetItemText(i, 4, strDays);

		rs.MoveNext();
	}

	OnEnChangeSearchEdit();
}


// CInsStaffDlg1 메시지 처리기입니다.

void CInsStaffDlg1::OnBnClickedRefreshButton()
{
	RefreshList();
}

BOOL CInsStaffDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "No", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "차량번호", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(2, "운송수단", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(3, "총적용일수", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "적용일", LVCFMT_LEFT, 150);
	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInsStaffDlg1::OnBnClickedExcelButton()
{
	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 9998, m_ui.nWNo, m_lstReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void CInsStaffDlg1::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(IsWindow(m_lstReport.GetSafeHwnd()))
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcDlg.right - 3;
		rcList.bottom = rcDlg.bottom - 3; 

		m_lstReport.MoveWindow(rcList);
	}
}

void CInsStaffDlg1::OnEnChangeSearchEdit()
{
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strCarNo = pRecord->GetItem(1)->GetCaption(NULL);

		if(	strCarNo.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}
