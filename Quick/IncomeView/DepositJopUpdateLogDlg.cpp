#include "StdAfx.h"
#include "Resource.h"
#include "DepositJopUpdateLogDlg.h"
#include "MakeDepositJobNewDlg1.h"

IMPLEMENT_DYNAMIC(CDepositJopUpdateLogDlg, CMyDialog)
CDepositJopUpdateLogDlg::CDepositJopUpdateLogDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CDepositJopUpdateLogDlg::IDD, pParent)
{
	m_bRiderLog = FALSE;
}

CDepositJopUpdateLogDlg::~CDepositJopUpdateLogDlg()
{	
}

void CDepositJopUpdateLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LIST, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CDepositJopUpdateLogDlg, CMyDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LOG_LIST, OnReportItemDbClick)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()

// CDepositJobDlg �޽��� ó�����Դϴ�.

BOOL CDepositJopUpdateLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog(); 
	CenterWindow();

	m_edtSearch.SetMyFont("���� ���", 15, FW_BOLD);
	
	if(m_bRiderLog)
	{
		GetDlgItem(IDC_JOB_STATIC)->ShowWindow(SW_HIDE);
		m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "�۾�ID/����ȣ", FALSE, FALSE);
		InitRiderLogColumn();
		RefreshRiderLogList();
	}
	else
	{
		m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "�۾�ID", FALSE, FALSE);
		InitJopLogColumn();
		RefreshJobLogList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDepositJopUpdateLogDlg::InitJopLogColumn()
{
	m_List.InsertColumn(0,"����", LVCFMT_CENTER, 40);
	m_List.InsertColumn(1,"�۾�ID", LVCFMT_CENTER, 45);
	m_List.InsertColumn(2,"����", LVCFMT_LEFT, 60);
	m_List.InsertColumn(3,"�� �� ��", LVCFMT_LEFT, 230);
	m_List.InsertColumn(4,"��뿩��", LVCFMT_RIGHT, 55);
	m_List.InsertColumn(5,"������", LVCFMT_CENTER, 110);
	m_List.InsertColumn(6,"������", LVCFMT_LEFT, 65);
	m_List.InsertColumn(7,"������", LVCFMT_LEFT, 65);
	m_List.InsertColumn(8,"����", LVCFMT_LEFT, 50);

	m_List.Populate();
}

void CDepositJopUpdateLogDlg::InitRiderLogColumn()
{
	m_List.InsertColumn(0,"����", LVCFMT_CENTER, 40);
	m_List.InsertColumn(1,"�۾�ID", LVCFMT_CENTER, 45);
	m_List.InsertColumn(2,"�� �� ��", LVCFMT_LEFT, 230);
	m_List.InsertColumn(3,"���", LVCFMT_LEFT, 50);
	m_List.InsertColumn(4,"����", LVCFMT_LEFT, 70);
	m_List.InsertColumn(5,"������", LVCFMT_CENTER, 110);
	m_List.InsertColumn(6,"������", LVCFMT_LEFT, 65);
	m_List.InsertColumn(7,"����", LVCFMT_LEFT, 50);

	m_List.Populate();
}

void CDepositJopUpdateLogDlg::RefreshJobLogList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job_update_log");
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);

	if(!pRs.Execute(&pCmd))
		return;

	m_List.DeleteAllItems();

	COleDateTime dtChange;
	long nCompany = 0, nCID = 0, nID = 0;
	CString strUpdateWName, strDisplayName, strWName, strUpdateEtc;
	BOOL bUse = FALSE;

	for(int i=0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCID", nCID);
		pRs.GetFieldValue("dtChange", dtChange);
		pRs.GetFieldValue("sUpdateWName", strUpdateWName);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sDisplayName", strDisplayName);
		pRs.GetFieldValue("bUse", bUse);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("sUpdateEtc", strUpdateEtc);

		m_List.InsertItem(i, GetStringFromLong(i + 1));
		m_List.SetItemText(i, 1, GetStringFromLong(nID));
		m_List.SetItemText(i, 2, m_ci.GetBranchName(nCompany));
		m_List.SetItemText(i, 3, strDisplayName);
		m_List.SetItemText(i, 4, bUse == TRUE ? "���" : "������");
		m_List.SetItemText(i, 5, dtChange.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(i, 6, strUpdateWName);
		m_List.SetItemText(i, 7, strWName);
		m_List.SetItemText(i, 8, strUpdateEtc);
		m_List.SetItemLong(i, nCID);
		m_List.SetItemLong2(i, strUpdateEtc == "����" ? 1 : 0);

		pRs.MoveNext();
	}

	m_List.Populate();
}

void CDepositJopUpdateLogDlg::RefreshRiderLogList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_rider_log");
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);

	if(!pRs.Execute(&pCmd))
		return;

	m_List.DeleteAllItems();

	COleDateTime dtChange;
	long nCompany = 0, nScheduleID = 0, nRNo = 0;
	CString strUpdateWName, strDisplayName, strRiderName, strUpdateEtc;

	for(int i=0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtChange", dtChange);
		pRs.GetFieldValue("sUpdateWName", strUpdateWName);
		pRs.GetFieldValue("nScheduleID", nScheduleID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sDisplayName", strDisplayName);
		pRs.GetFieldValue("sUpdateEtc", strUpdateEtc);
		pRs.GetFieldValue("sName", strRiderName);
		pRs.GetFieldValue("nRNo", nRNo);

		m_List.InsertItem(i, GetStringFromLong(i + 1));
		m_List.SetItemText(i, 1, GetStringFromLong(nScheduleID));
		m_List.SetItemText(i, 2, strDisplayName);
		m_List.SetItemText(i, 3, GetStringFromLong(nRNo));
		m_List.SetItemText(i, 4, strRiderName);
		m_List.SetItemText(i, 5, dtChange.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(i, 6, strUpdateWName);
		m_List.SetItemText(i, 7, strUpdateEtc);
		m_List.SetItemLong2(i, strUpdateEtc == "����" ? 1 : 0);

		pRs.MoveNext();
	}

	m_List.Populate();
}

void CDepositJopUpdateLogDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(!m_bRiderLog)
	{
		CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();
		if(pRecord)
		{
			CMakeDepositJobNewDlg1 dlg;
			dlg.m_nDlgType = 2; // �α�Ȯ��
			dlg.m_nCompany = m_nCompanyCode;
			dlg.m_bIntegrated = m_bIntegrated;
			dlg.m_nID = m_List.GetItemLong(pRecord);
			dlg.DoModal();
		}
	}
}

void CDepositJopUpdateLogDlg::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_List.GetRecords();
	
	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		BOOL bShow = FALSE;

		CString sID = m_List.GetItemText(pRecord, 1);
		CString sRiderNum = m_List.GetItemText(pRecord, 3);

		if(sID.Find(strSearch) != -1 || (m_bRiderLog && sRiderNum.Find(strSearch) != -1))
			bShow = TRUE;

		pRecord->SetVisible(bShow);
	}

	m_List.Populate();
}

