// DepositJobDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "DepositJobDlg.h"
#include "MakeDepositJobNewDlg1.h"
#include "GroupSettingNewDlg.h"
#include "DepositJobLogDlg.h"
#include "DepositJopUpdateLogDlg.h"

//#include "IncomePage1.h"
// CDepositJobDlg ��ȭ �����Դϴ�.


IMPLEMENT_DYNAMIC(CDepositJobDlg, CMyDialog)
CDepositJobDlg::CDepositJobDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDepositJobDlg::IDD, pParent)
{
	m_pParentWnd = NULL;
	m_pDeposit = NULL;
	m_fontBig = m_FontManager.GetFont("���� ���", 17, FW_BOLD);
	m_fontSmall = m_FontManager.GetFont("���� ���", 23, FW_BOLD);
}

CDepositJobDlg::~CDepositJobDlg()
{	
}

void CDepositJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JOB_LIST, m_List);
	DDX_Control(pDX, IDC_INCLUDE_GROUP_LIST2,m_lstInclude);
	DDX_Control(pDX, IDC_NOT_INCLUDE_GROUP_LIST2, m_lstNotInclude);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stcDraw);
}


BEGIN_MESSAGE_MAP(CDepositJobDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MAKE_JOB_BTN, OnBnClickedMakeJobBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_GROUP_SETTING_BUTTON, OnBnClickedGroupSettingButton)	
	ON_NOTIFY(NM_CLICK, IDC_JOB_LIST, OnNMclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_JOB_LIST, OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_JOB_LIST, OnReportItemRClick)

	ON_BN_CLICKED(IDC_SELECT_JOB_PROCESS_BUTTON, OnBnClickedSelectJobProcessButton)
	ON_BN_CLICKED(IDC_UPDATE_JOB_BTN, OnBnClickedUpdateJobBtn)
	ON_BN_CLICKED(IDC_REFRESH_JOB_BTN, OnBnClickedRefreshJobBtn)
	ON_BN_CLICKED(IDC_DELETE_JOB_BTN, OnBnClickedDeleteJobBtn)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_ENTRY_RIDER, OnEntryRider)
	ON_COMMAND(ID_JOB_MAKE, OnJobMake)
	ON_COMMAND(ID_JOB_UPDATE, OnJobUpdate)
	ON_COMMAND(ID_JOB_DELETE, OnJobDelete)
	ON_COMMAND(ID_JOB_PLAY, OnJobPlay)
	ON_COMMAND(ID_SHOW_HISTORY, OnShowHistory)
	ON_BN_CLICKED(IDC_PLAY_JOB_BTN, OnBnClickedPlayJobBtn)
	ON_BN_CLICKED(IDC_GROUP_IN_BUTTON, &CDepositJobDlg::OnBnClickedGroupInButton)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GROUP_OUT_BUTTON, &CDepositJobDlg::OnBnClickedGroupOutButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CDepositJobDlg::OnBnClickedCancelButton)
	ON_BN_CLICKED(IDC_UPDATE_JOB_LOG_BTN, OnBnClickedUpdateLogBtn)
	ON_BN_CLICKED(IDC_UPDATE_RIDER_LOG_BTN, OnBnClickedRiderLogBtn)
END_MESSAGE_MAP()

// CDepositJobDlg �޽��� ó�����Դϴ�.

BOOL CDepositJobDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog(); 
	CenterWindow();

	m_List.InsertColumn(0,"�۾�ID", LVCFMT_CENTER, 45);
	m_List.InsertColumn(1,"�����", LVCFMT_LEFT, 60);
	m_List.InsertColumn(2,"�� �� ��", LVCFMT_LEFT, 230);
	m_List.InsertColumn(3,"��뿩��", LVCFMT_RIGHT, 55);
	m_List.InsertColumn(4,"�۾���", LVCFMT_CENTER, 105);
	m_List.InsertColumn(5,"����/���Ա�", LVCFMT_RIGHT, 80);
	m_List.InsertColumn(6,"�ݾ�", LVCFMT_RIGHT, 70);
	m_List.InsertColumn(7,"��ϱ��", LVCFMT_RIGHT, 60);
	m_List.InsertColumn(8,"������", LVCFMT_LEFT, 65);
	m_List.InsertColumn(9,"�������������(���� ��¥)", LVCFMT_CENTER, 150);

	m_lstInclude.InsertColumn(0, "���", LVCFMT_LEFT, 50);
	m_lstInclude.InsertColumn(1, "����", LVCFMT_LEFT, 70);
	m_lstInclude.InsertColumn(2, "�������", LVCFMT_LEFT, 80);

	m_lstNotInclude.InsertColumn(0, "���,", LVCFMT_LEFT, 50);
	m_lstNotInclude.InsertColumn(1, "����,", LVCFMT_LEFT, 80);

	m_List.Populate();
	m_lstInclude.Populate();
	m_lstNotInclude.Populate();

	RefreshList();

	if(m_List.GetRecords()->GetCount() > 0)
	{
		CXTPGridRow *pRow = m_List.GetRows()->GetAt(0);
		m_List.GetSelectedRows()->Select(pRow);
		ChangeSelInfo();
	}
	//RefreshIncludeList();
	//RefreshNotIncludeList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDepositJobDlg::OnBnClickedMakeJobBtn()
{
	CMakeDepositJobNewDlg1 dlg;
	dlg.m_nDlgType = 1; // �űԸ��
	dlg.m_nCompany = m_nCompanyCode;
	dlg.m_bIntegrated = m_bIntegrated;
	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CDepositJobDlg::OnBnClickedOk()
{
	OnOK();
}

void CDepositJobDlg::OnBnClickedGroupSettingButton()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	CGroupSettingNewDlg dlg;
	dlg.m_nCompany = m_nCompanyCode;
	dlg.m_bIntegrated = m_bIntegrated; // �����̳� �����
	dlg.m_nScheduleID = pRows == NULL ? 0 : m_List.GetItemLong(pRows->GetAt(0)->GetRecord());
	
	dlg.DoModal();
	RefreshList();
}

void CDepositJobDlg::RefreshList(void)
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	long nSelRow = 0;
	long nScheduleID = 0;

	if(pRows != NULL && pRows->GetCount() != 0) 
		nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());

	DeleteMainList();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job");

	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);

	if(!pRs.Execute(&pCmd))
		return;

	int nCompany = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_DEPOSIT_JOB *st = new ST_DEPOSIT_JOB;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nID", st->nID);
		pRs.GetFieldValue("nPlayType", st->nPlayType);
		pRs.GetFieldValue("sDisplayName", st->strDisplayName);
		pRs.GetFieldValue("bSunDay", st->bSun);
		pRs.GetFieldValue("bMonDay", st->bMon);
		pRs.GetFieldValue("bTuesDay", st->bTues);
		pRs.GetFieldValue("bWednesDay", st->bWednes);
		pRs.GetFieldValue("bThursDay", st->bThurs);
		pRs.GetFieldValue("bFriDay", st->bFri);
		pRs.GetFieldValue("bSaturDay", st->bSatur);
		pRs.GetFieldValue("nMonthPlayType", st->nMonthPlayType);
		pRs.GetFieldValue("bUse", st->bUse);
		pRs.GetFieldValue("nMonthDay", st->nMonthDay); 
		pRs.GetFieldValue("nMonthWeek", st->nMonthWeek);
		pRs.GetFieldValue("nMonthWeekend", st->nMonthWeekend);
		pRs.GetFieldValue("nDepositType", st->nDepositType);
		pRs.GetFieldValue("nDeposit", st->nDeposit);
		pRs.GetFieldValue("dtStart", st->dtStart);
		pRs.GetFieldValue("dtEnd", st->dtEnd);
		pRs.GetFieldValue("sEtc", st->strEtc);
		pRs.GetFieldValue("bUseSms", st->bUseSms);
		pRs.GetFieldValue("sSmsPhone", st->strSmsPhone);
		pRs.GetFieldValue("sWName", st->strWName);
		pRs.GetFieldValue("bLastJobSuccess", st->bLastJobSuccess);
		pRs.GetFieldValue("dtLastJob", st->dtLastJob);
		pRs.GetFieldValue("nRiderCount", st->nRiderCount);
		pRs.GetFieldValue("dtMakeJob", st->dtMakeJob);
		pRs.GetFieldValue("bWorkerApply", st->bWorkerApply); 
		pRs.GetFieldValue("bNotWorkerApply", st->bNotWorkerApply);

		if(st->nID == nScheduleID)
			nSelRow = i;

		m_List.InsertItem(i, LF->GetStringFromLong(st->nID));
		m_List.SetItemText(i, 1, m_ci.GetBranchName(nCompany));
		m_List.SetItemText(i, 2, st->strDisplayName);
		m_List.SetItemText(i, 3, st->bUse == TRUE ? "���" : "������");
		m_List.SetItemText(i, 4, GetDisplayDate(st));
		m_List.SetItemText(i, 5, st->nDepositType == 0 ? "����" : "���Ա�");
		m_List.SetItemText(i, 6, LF->GetMyNumberFormat(st->nDeposit));
		m_List.SetItemText(i, 7, LF->GetStringFromLong(st->nRiderCount) + "��");
		m_List.SetItemText(i, 8, st->strWName);
		m_List.SetItemText(i, 9, GetLastPlayDate(st->bLastJobSuccess, st->dtLastJob));
		m_List.SetItemLong(i, st->nID);
		m_List.SetItemData(i, (DWORD_PTR)st);

		pRs.MoveNext();
	}

	m_List.Populate();

	if(pRs.GetRecordCount() > 0)
	{
		CXTPGridRow *pRow = m_List.GetRows()->GetAt(nSelRow);
		m_List.EnsureVisible(pRow);
		m_List.GetSelectedRows()->Select(pRow);
	}
}

CString CDepositJobDlg::GetDisplayDate(ST_DEPOSIT_JOB *st)
{
	char buffer[10];
	CString strTemp = "";

	if(st->nPlayType == 0)
		return "����";
	else if(st->nPlayType == 1)
	{
		strTemp = "����(";

		if(st->bSun) strTemp += "��";
		if(st->bMon) strTemp += "��";
		if(st->bTues) strTemp += "ȭ";
		if(st->bWednes) strTemp += "��";
		if(st->bThurs) strTemp += "��";
		if(st->bFri) strTemp += "��";
		if(st->bSatur) strTemp += "��";

		strTemp += ")";
	}
	else if(st->nPlayType == 2)
	{
		strTemp = "�Ŵ�(";

		if(st->nMonthPlayType == 0)
			strTemp += (CString)itoa(st->nMonthDay, buffer, 10) + "��)";
		else if(st->nMonthPlayType == 1)
		{
			if(st->nMonthWeek == 0) {strTemp += "ù°,";}
			else if(st->nMonthWeek == 1) {strTemp += "��°,";}
			else if(st->nMonthWeek == 2) {strTemp += "��°,";}
			else if(st->nMonthWeek == 3) {strTemp += "��°,";}
			else if(st->nMonthWeek == 4) {strTemp += "������,";}

			//SQL �������� ���� �� 1���� �Ͽ��� 7�� �����
			if(st->nMonthWeekend == 1) {strTemp += " �Ͽ���";}	
			else if(st->nMonthWeekend == 2) {strTemp += " ������";}
			else if(st->nMonthWeekend == 3) {strTemp += " ȭ����";}
			else if(st->nMonthWeekend == 4) {strTemp += " ������";}
			else if(st->nMonthWeekend == 5) {strTemp += " �����";}
			else if(st->nMonthWeekend == 6) {strTemp += " �ݿ���";}
			else if(st->nMonthWeekend == 7) {strTemp += " �����";}

			strTemp += ")";
		}
	}
	return strTemp;
}

CString CDepositJobDlg::GetLastPlayDate(BOOL bLastJobSuccess, COleDateTime dtLastJob)
{
	CString strTemp = "";

	if(dtLastJob.m_status != 2)
	{
        strTemp.Format("%s", dtLastJob.Format("%Y-%m-%d %H:%M:%S"));

		if(bLastJobSuccess)
			strTemp = "����(" + strTemp + ")";
		else
			strTemp = "����(" + strTemp + ")";

		return strTemp;
	}
	
	return "�۾���� ����";
}

void CDepositJobDlg::OnNMclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{ 
	ChangeSelInfo();

	*pResult = 0;
}

void CDepositJobDlg::ChangeSelInfo()
{ 
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return; 
	if(pRows->GetCount() == 0) return;  

	ST_DEPOSIT_JOB *pDeposit = (ST_DEPOSIT_JOB*)m_List.GetItemData(pRows->GetAt(0)->GetRecord());
	//m_stcDraw.Invalidate(TRUE);

	if(m_pDeposit != NULL)
	{
		if(m_pDeposit->nID == pDeposit->nID)
			return;
	}

	m_pDeposit = pDeposit;

	SetTimer(0, 500, NULL);

	CRect rc;  
	m_stcDraw.GetWindowRect(rc);
	ScreenToClient(rc); 

	InvalidateRect(rc);
}

void CDepositJobDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem < 0) return;

	OnBnClickedUpdateJobBtn();

	*pResult = 0;
}

void CDepositJobDlg::OnBnClickedSelectJobProcessButton()
{
}

void CDepositJobDlg::OnBnClickedUpdateJobBtn()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) 
	{
		MessageBox("���� �� �۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMakeDepositJobNewDlg1 dlg;
	dlg.m_nDlgType = 0;
	dlg.m_nCompany = m_nCompanyCode;
	dlg.m_bIntegrated = m_bIntegrated;
	dlg.m_nID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());
	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CDepositJobDlg::OnBnClickedRefreshJobBtn()
{
	RefreshList();
}

void CDepositJobDlg::OnBnClickedDeleteJobBtn()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) 
	{
		MessageBox("���� �� �۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}


	long nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());
	CString sDisplayName = m_List.GetItemText(pRows->GetAt(0)->GetRecord(), 1);

	if(MessageBox("[" + sDisplayName +"] �۾��� ���� �Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand pCmd(m_pMkDb, "delete_schedule_job_1");
	pCmd.AddParameter(nScheduleID);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
	{
		MessageBox("���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		RefreshList();
	}

}

void CDepositJobDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	BCMenu	m_menuPopup; 

	m_menuPopup.SetMenuDrawMode(TRUE); 
	m_menuPopup.LoadMenu(IDR_CONTEXT_MENU);
	m_menuPopup.SetBitmapBackground(RGB(0, 255, 255));
	m_menuPopup.SetIconSize(16,18);
	m_menuPopup.LoadToolbar(IDR_SCHEDULE);
	BCMenu* pRMenu = (BCMenu*)m_menuPopup.GetSubMenu(21);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CDepositJobDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_List, pt);
}

void CDepositJobDlg::OnRefresh()
{
	OnBnClickedRefreshJobBtn();
}

void CDepositJobDlg::OnEntryRider()
{
	OnBnClickedGroupSettingButton();
}

void CDepositJobDlg::OnJobMake()
{
	OnBnClickedMakeJobBtn();
}

void CDepositJobDlg::OnJobUpdate()
{
	OnBnClickedUpdateJobBtn();
}

void CDepositJobDlg::OnJobDelete()
{
	OnBnClickedDeleteJobBtn();
}

void CDepositJobDlg::OnJobPlay()
{
	OnBnClickedPlayJobBtn();
}

void CDepositJobDlg::OnBnClickedPlayJobBtn()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) 
	{
		MessageBox("���� �� �۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	long nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());
	CString sDisplayName = m_List.GetItemText(pRows->GetAt(0)->GetRecord(), 1);

	if(MessageBox("[" + sDisplayName +"] �۾��� ���� �Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand pCmd(m_pMkDb, "schedule_play");
	pCmd.AddParameter(nScheduleID);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(FALSE);

	if(pCmd.Execute())
	{
		MessageBox("�۾��� ���۵Ǿ����ϴ�. �ణ�� �ð��� �ɸ��� �ֽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
		RefreshList();	
	}
}

void CDepositJobDlg::OnShowHistory()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) 
	{
		MessageBox("�۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	long nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());
	CString strDisplayName = m_List.GetItemText(pRows->GetAt(0)->GetRecord(), 1);

	CDepositJobLogDlg dlg;
	dlg.m_nScheduleID = nScheduleID;
	dlg.m_strDisplayName = strDisplayName;

	dlg.DoModal();

}

void CDepositJobDlg::OnBnClickedGroupInButton()
{
	if(m_pDeposit == NULL)
		return;

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	CXTPGridSelectedRows *pJobRows = m_List.GetSelectedRows();
	CXTPGridSelectedRows *pNotIncomeRows = m_lstNotInclude.GetSelectedRows();

	if(pJobRows == NULL) {MessageBox("���Խ�ų �۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pJobRows->GetCount() == 0) {MessageBox("���Խ�ų �۾��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pNotIncomeRows == NULL) {MessageBox("���Խ�ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pNotIncomeRows->GetCount() == 0) {MessageBox("���Խ�ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};

	for(int i=0; i<pNotIncomeRows->GetCount(); i++)
	{
		long nRet = 0;

		CXTPGridRow *pRow = pNotIncomeRows->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long lANo = m_lstNotInclude.GetItemLong(pRecord);

		CMkCommand pCmd(m_pMkDb, "insert_schedule_rider_1");
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		pCmd.AddParameter(m_pDeposit->nID);
		pCmd.AddParameter(lANo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute())
		{
			MessageBox("��� ���� ����!!\r\n�ٽýõ����ּ���", "Ȯ��", MB_ICONINFORMATION);
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

void CDepositJobDlg::RefreshIncludeList()
{
	m_lstInclude.DeleteAllItems();

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());

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

void CDepositJobDlg::RefreshNotIncludeList()
{
	m_lstNotInclude.DeleteAllItems();

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nScheduleID = m_List.GetItemLong(pRows->GetAt(0)->GetRecord());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_not_income_rider");
	pCmd.AddParameter(nScheduleID);
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
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

void CDepositJobDlg::DeleteMainList()
{
	m_pDeposit = NULL;

	CXTPGridRecords *pRecords = m_List.GetRecords();

	for(int i=0;i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		ST_DEPOSIT_JOB *st = (ST_DEPOSIT_JOB*)m_List.GetItemData(pRecord);

		if(st != NULL)
		{
			delete st;
			st = NULL;
		}
	}

	m_List.DeleteAllItems();
}

void CDepositJobDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 0)
	{
		KillTimer(nIDEvent);
		RefreshIncludeList();
		RefreshNotIncludeList();
	}

	CMyDialog::OnTimer(nIDEvent);
}

void CDepositJobDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
 

	CRect rc;  
	m_stcDraw.GetWindowRect(rc);
	ScreenToClient(rc);  

	//dc.SetBkMode(TRANSPARENT); 
  
	dc.FillSolidRect(rc, RGB(0, 0, 0)); 
	rc.DeflateRect(1, 1, 1, 1);
	dc.FillSolidRect(rc, RGB(255, 255, 255));

	if(m_pDeposit == NULL)
	{
		return;
	}
 	rc.top += 10; rc.left += 10; 
	DrawStcText(&dc, CLR_BLACK, CLR_BLACK, m_pDeposit->strDisplayName, rc, DT_CENTER, m_fontBig);
	rc.top += 27; 
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringUse(), rc, DT_LEFT, m_fontSmall); 
	rc.top += 22;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringDate(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left += 20;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringDepositType(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left -= 20; 
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringMaker(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left += 20;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringMakeDate(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left -= 20;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringWorkDate(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left += 20;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringWorkDateEnd(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; rc.left -= 20;
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringWorkState(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; 
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringEtc(), rc, DT_LEFT, m_fontSmall);
	rc.top += 22; 
	DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringSms(), rc, DT_LEFT, m_fontSmall);
 
	if(m_pDeposit->bUseSms)
	{
		rc.top += 20; rc.left += 20;
		DrawStcText(&dc, CLR_BLUE, CLR_RED, GetStringSmsPhone(), rc, DT_LEFT, m_fontSmall);
	}
}

CString CDepositJobDlg::GetStringWorkState()
{
	if(m_pDeposit == NULL) return ""; 

	CString strTemp = "";
	if(m_pDeposit->bWorkerApply && m_pDeposit->bNotWorkerApply)
		strTemp = "* �������� [�����]�Դϴ�.";
	else if(m_pDeposit->bWorkerApply)
		strTemp = "* �������� [�������ɱ��]�Դϴ�.";
	else if(m_pDeposit->bNotWorkerApply)
		strTemp = "* �������� [�����������]�Դϴ�.";
	else
		strTemp = "* �������� [�����ϴ�].";
	
	return strTemp;
}
 
CString CDepositJobDlg::GetStringEtc()
{
	if(m_pDeposit == NULL) return ""; 

	CString strTemp = "* ����ķα׿��� [" + m_pDeposit->strEtc + "](��)�� �����ϴ�.";
	return strTemp;
}

CString CDepositJobDlg::GetStringSmsPhone()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = "";
	strTemp = "SMS��ȣ�� [" + LF->GetDashPhoneNumber(m_pDeposit->strSmsPhone) + "]�Դϴ�.";

	return strTemp;
}

CString CDepositJobDlg::GetStringSms() 
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = "";

	if(m_pDeposit->bUseSms)
		strTemp = "* �۾� �������θ� SMS�� �˸��ϴ�.";
	else
		strTemp = "* �۾� �������θ� SMS�� �˸��� �ʽ��ϴ�.";


	return strTemp;
}

CString CDepositJobDlg::GetStringMaker()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = "* [" + m_pDeposit->strWName + "]����";
	return strTemp;
}

CString CDepositJobDlg::GetStringMakeDate()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = "[" + m_pDeposit->dtMakeJob.Format("%y��%m��%d�� %H��") + "]�濡 �����Ͽ����ϴ�.";
	return strTemp;
}

CString CDepositJobDlg::GetStringWorkDate()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = "* [" + m_pDeposit->dtStart.Format("%y��%m��%d��") + "]����";
	return strTemp;
}

CString CDepositJobDlg::GetStringWorkDateEnd()
{
	if(m_pDeposit == NULL) return "";
 
	CString strTemp = "[" + m_pDeposit->dtEnd.Format("%y��%m��%d��") + "] ���̿� �����մϴ�.";
	return strTemp;
}

CString CDepositJobDlg::GetStringUse()
{ 
	if(m_pDeposit == NULL) return "";

	CString strTemp = "";
	strTemp = m_pDeposit->bUse == TRUE ? "* �����Ͻ� �۾��� ���� [�����]�� �۾��Դϴ�." :  "* �����Ͻ� �۾��� ���� [������� �ʴ�] �۾��Դϴ�.";
	return strTemp;
}

CString CDepositJobDlg::GetStringDate()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp = GetDisplayDate(m_pDeposit);
	strTemp = "* �۾����� [" + strTemp + "]�̸�,";
	return strTemp;
}

CString CDepositJobDlg::GetStringDepositType()
{
	if(m_pDeposit == NULL) return "";

	CString strTemp;
	if(m_pDeposit->nDepositType == 0)
		strTemp = LF->GetMyNumberFormat(m_pDeposit->nDeposit) + "���� [����]�մϴ�";
	else
		strTemp = LF->GetMyNumberFormat(m_pDeposit->nDeposit) + "���� [���Ա�]�մϴ�";
	
	return strTemp;
}


void CDepositJobDlg::DrawStcText(CDC *pDC, COLORREF rgbText, COLORREF rgbMainText, CString sDisplayName, CRect rc, long nType, CFont *font)
{
	CFont* pOldFont = pDC->SelectObject(font);
	pDC->SetTextColor(rgbText);  
	pDC->DrawText(sDisplayName, rc, nType);

	long nStartFind = sDisplayName.Find("[");
	if(nStartFind >= 0) 
	{ 
		long  nEndFind = sDisplayName.Find("]");
		CString sMainWord = sDisplayName.Mid(nStartFind, nEndFind - nStartFind + 1);
		CString sStartWord = sDisplayName.Left(nStartFind);

		CSize szMain = pDC->GetTextExtent(sMainWord);
		CSize szStartWord = pDC->GetTextExtent(sStartWord);

		rc.left = rc.left + szStartWord.cx;

		pDC->SetTextColor(rgbMainText);  
		pDC->DrawText(sMainWord, rc, nType);
		
	}
	

	pDC->SelectObject(pOldFont);
}

void CDepositJobDlg::OnBnClickedGroupOutButton()
{
	if(m_pDeposit == NULL)
		return;

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	CXTPGridSelectedRows *pJobRows = m_List.GetSelectedRows();
	CXTPGridSelectedRows *pIncomeRows = m_lstInclude.GetSelectedRows();

	if(pJobRows == NULL) {MessageBox("������ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pJobRows->GetCount() == 0) {MessageBox("������ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pIncomeRows == NULL) {MessageBox("������ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};
	if(pIncomeRows->GetCount() == 0) {MessageBox("������ų ��縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;};

	for(int i=0; i<pIncomeRows->GetCount(); i++)
	{
		long nRet = 0;

		CXTPGridRow *pRow = pIncomeRows->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long lANo = m_lstInclude.GetItemLong(pRecord);

		CMkCommand pCmd(m_pMkDb, "delete_schedule_rider_1");
		pCmd.AddParameter(m_pDeposit->nID);
		pCmd.AddParameter(lANo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute())
		{
			MessageBox("��� ���� ����!!\r\n�ٽýõ����ּ���", "Ȯ��", MB_ICONINFORMATION);
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

void CDepositJobDlg::OnBnClickedCancelButton()
{
	OnOK();
}

void CDepositJobDlg::OnBnClickedUpdateLogBtn()
{
	CDepositJopUpdateLogDlg dlg;
	dlg.m_nCompanyCode = m_nCompanyCode;
	dlg.m_bIntegrated = m_bIntegrated;
	dlg.m_bRiderLog = FALSE;
	dlg.DoModal();
}

void CDepositJobDlg::OnBnClickedRiderLogBtn()
{
	CDepositJopUpdateLogDlg dlg;
	dlg.m_nCompanyCode = m_nCompanyCode;
	dlg.m_bIntegrated = m_bIntegrated;
	dlg.m_bRiderLog = TRUE;
	dlg.DoModal();
}