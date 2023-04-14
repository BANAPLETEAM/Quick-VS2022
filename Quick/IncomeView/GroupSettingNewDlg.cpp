// GroupSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GroupSettingNewDlg.h"

#define		VIEW_MODE	100
// driver group 2


//CGroupSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGroupSettingNewDlg, CMyDialog)
CGroupSettingNewDlg::CGroupSettingNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGroupSettingNewDlg::IDD, pParent)
	, m_bIntegrated(0)
{
	m_nCompany = -1;
	m_nScheduleID = 0;
	m_bFirst = TRUE;
}

CGroupSettingNewDlg::~CGroupSettingNewDlg()
{
	
}

void CGroupSettingNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JOB_LIST, m_lstJob);
	DDX_Control(pDX, IDC_INCLUDE_GROUP_LIST,m_lstInclude);
	DDX_Control(pDX, IDC_NOT_INCLUDE_GROUP_LIST, m_lstNotInclude);
}


BEGIN_MESSAGE_MAP(CGroupSettingNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_GROUP_IN_BUTTON, OnBnClickedGroupInButton)
	ON_NOTIFY(NM_CLICK, IDC_JOB_LIST, OnReportItemClick)
	ON_BN_CLICKED(IDC_GROUP_OUT_BUTTON, OnBnClickedGroupOutButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CGroupSettingNewDlg::OnBnClickedCancelButton)
END_MESSAGE_MAP()


// CGroupSettingNewDlg 메시지 처리기입니다.

void CGroupSettingNewDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	RefreshIncludeList();
	RefreshNotIncludeList();
}

BOOL CGroupSettingNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();	

	m_lstJob.InsertColumn(0, "ID", LVCFMT_LEFT, 40);
	m_lstJob.InsertColumn(1, "작업명", LVCFMT_LEFT, 200);

	m_lstInclude.InsertColumn(0, "사번", LVCFMT_LEFT, 50);
	m_lstInclude.InsertColumn(1, "기사명", LVCFMT_LEFT, 70);
	m_lstInclude.InsertColumn(2, "등록일자", LVCFMT_LEFT, 80);

	m_lstNotInclude.InsertColumn(0, "사번,", LVCFMT_LEFT, 50);
	m_lstNotInclude.InsertColumn(1, "기사명,", LVCFMT_LEFT, 80);

	m_lstJob.Populate();
	m_lstInclude.Populate();
	m_lstNotInclude.Populate();

	RefreshJobList();
	RefreshIncludeList();
	RefreshNotIncludeList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGroupSettingNewDlg::RefreshJobList()
{
	m_lstJob.DeleteAllItems();
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job");

	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	long nID; CString sDisplayName;
	long nSelRow = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sDisplayName", sDisplayName);

		m_lstJob.InsertItem(i, itoa(nID, buffer, 10));
		m_lstJob.SetItemText(i, 1, sDisplayName);
		m_lstJob.SetItemLong(i, nID);

		if(nID == m_nScheduleID)
			nSelRow = i;

		pRs.MoveNext();
	}

	m_lstJob.Populate();

	if(pRs.GetRecordCount() > 0)
	{
		CXTPGridRow *pRow = NULL;

		if(m_bFirst == TRUE && m_nScheduleID > 0)
		{
            m_bFirst = FALSE;
			pRow = m_lstJob.GetRows()->GetAt(nSelRow);
		}
		else
		{
			pRow = m_lstJob.GetRows()->GetAt(0);
		}

		m_lstJob.EnsureVisible(pRow);
		m_lstJob.GetSelectedRows()->Select(pRow);
	}
}

void CGroupSettingNewDlg::RefreshIncludeList()
{
    m_lstInclude.DeleteAllItems();

	CXTPGridSelectedRows *pRows = m_lstJob.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nScheduleID = m_lstJob.GetItemLong(pRows->GetAt(0)->GetRecord());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_income_rider");
	pCmd.AddParameter(nScheduleID);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	long nRNo, nWorkState, lANo;
	CString sName;
	COleDateTime dtEntry;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("lANo", lANo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("dtEntry", dtEntry);
		pRs.GetFieldValue("nWorkState", nWorkState);

		m_lstInclude.InsertItem(i, itoa(nRNo, buffer, 10));
		m_lstInclude.SetItemText(i, 1, sName);
		m_lstInclude.SetItemText(i, 2, dtEntry.Format("%Y-%m-%d"));
		m_lstInclude.SetItemLong(i, lANo);
		m_lstInclude.SetItemLong2(i, nWorkState);

		pRs.MoveNext();
	}

	m_lstInclude.Populate();
}

void CGroupSettingNewDlg::RefreshNotIncludeList()
{
	m_lstNotInclude.DeleteAllItems();

	CXTPGridSelectedRows *pRows = m_lstJob.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nScheduleID = m_lstJob.GetItemLong(pRows->GetAt(0)->GetRecord());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_not_income_rider");
	pCmd.AddParameter(nScheduleID);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	long lANo, nRNo, nWorkState;
	CString sName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("lANo", lANo);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nWorkState", nWorkState);

		m_lstNotInclude.InsertItem(i, itoa(nRNo, buffer, 10));
		m_lstNotInclude.SetItemText(i, 1, sName);
		m_lstNotInclude.SetItemLong(i, lANo);
		m_lstNotInclude.SetItemLong2(i, nWorkState);

		pRs.MoveNext();
	}

	m_lstNotInclude.Populate();
}

void CGroupSettingNewDlg::OnBnClickedGroupInButton()
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	CXTPGridSelectedRows *pJobRows = m_lstJob.GetSelectedRows();
	CXTPGridSelectedRows *pNotIncomeRows = m_lstNotInclude.GetSelectedRows();

	if(pJobRows == NULL) {MessageBox("편입시킬 작업을 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pJobRows->GetCount() == 0) {MessageBox("편입시킬 작업을 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pNotIncomeRows == NULL) {MessageBox("편입시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pNotIncomeRows->GetCount() == 0) {MessageBox("편입시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};

	long nScheduleID = m_lstJob.GetItemLong(pJobRows->GetAt(0)->GetRecord());

	for(int i=0; i<pNotIncomeRows->GetCount(); i++)
	{
		long nRet = 0;
		
		CXTPGridRow *pRow = pNotIncomeRows->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long lANo = m_lstNotInclude.GetItemLong(pRecord);

		CMkCommand pCmd(m_pMkDb, "insert_schedule_rider_1");
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		pCmd.AddParameter(nScheduleID);
		pCmd.AddParameter(lANo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute())
		{
			MessageBox("기사 편입 실패!!\r\n다시시도해주세요", "확인", MB_ICONINFORMATION);
			return;
		}

		pPar->GetValue(nRet);
		long nWorkState = m_lstNotInclude.GetItemLong2(pRecord);
		CString sRNo = m_lstNotInclude.GetItemText(pRecord, 0);
		CString sName = m_lstNotInclude.GetItemText(pRecord, 1);
		pRecord->Delete();

        long nInCount = m_lstInclude.GetItemCount();

		m_lstInclude.InsertItem(nInCount, sRNo);
		m_lstInclude.SetItemText(nInCount, 1, sName);
		m_lstInclude.SetItemText(nInCount, 2, dtCur.Format("%Y-%m-%d"));
		m_lstInclude.SetItemLong(nInCount, nRet);
		m_lstInclude.SetItemLong2(nInCount, nWorkState);
	}

	m_lstInclude.Populate();
	m_lstNotInclude.Populate();
}

void CGroupSettingNewDlg::OnBnClickedGroupOutButton()
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	CXTPGridSelectedRows *pJobRows = m_lstJob.GetSelectedRows();
	CXTPGridSelectedRows *pIncomeRows = m_lstInclude.GetSelectedRows();

	if(pJobRows == NULL) {MessageBox("삭제시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pJobRows->GetCount() == 0) {MessageBox("삭제시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pIncomeRows == NULL) {MessageBox("삭제시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pIncomeRows->GetCount() == 0) {MessageBox("삭제시킬 기사를 선택하세요", "확인", MB_ICONINFORMATION); return;};

	long nScheduleID = m_lstJob.GetItemLong(pJobRows->GetAt(0)->GetRecord());

	for(int i=0; i<pIncomeRows->GetCount(); i++)
	{
		long nRet = 0;

		CXTPGridRow *pRow = pIncomeRows->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long lANo = m_lstInclude.GetItemLong(pRecord);

		CMkCommand pCmd(m_pMkDb, "delete_schedule_rider_1");
		pCmd.AddParameter(nScheduleID);
		pCmd.AddParameter(lANo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute())
		{
			MessageBox("기사 삭제 실패!!\r\n다시시도해주세요", "확인", MB_ICONINFORMATION);
			return;
		}

		long nWorkState = m_lstInclude.GetItemLong2(pRecord);
		CString sRNo = m_lstInclude.GetItemText(pRecord, 0);
		CString sName = m_lstInclude.GetItemText(pRecord, 1);

		pRecord->Delete();
		
		long nOutCount = m_lstNotInclude.GetItemCount();

		m_lstNotInclude.InsertItem(nOutCount, sRNo);
		m_lstNotInclude.SetItemText(nOutCount, 1, sName);
		m_lstNotInclude.SetItemLong(nOutCount, lANo);
		m_lstNotInclude.SetItemLong2(nOutCount, nWorkState);
	}

	m_lstInclude.Populate();
	m_lstNotInclude.Populate();	
}

void CGroupSettingNewDlg::OnBnClickedCancelButton()
{
	OnOK();
}
