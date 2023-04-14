// DepositGroupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "DepositGroupDlg.h"

#include "VarietyDlg.h"

// CDepositGroupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDepositGroupDlg, CMyDialog)
CDepositGroupDlg::CDepositGroupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDepositGroupDlg::IDD, pParent)
{
	m_bSelectMode = NULL;
	m_sDepositRateGroupName = "";
}

CDepositGroupDlg::~CDepositGroupDlg()
{
}

void CDepositGroupDlg::DoDataExchange(CDataExchange* pDX)
{   
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_LIST, m_lstGroup);
	DDX_Control(pDX, IDC_DEPOSIT_LIST, m_lstDeposit);
}


BEGIN_MESSAGE_MAP(CDepositGroupDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_LIST, OnReportItemGroupClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_LIST, OnReportItemGroupDblClick)
	ON_NOTIFY(NM_CLICK, IDC_DEPOSIT_LIST, OnReportItemDepositClick)
	ON_BN_CLICKED(IDC_MAKE_GROUP_BTN, OnBnClickedMakeGroupBtn)
	ON_BN_CLICKED(IDC_UPDATE_GROUP_BTN, OnBnClickedUpdateGroupBtn)
	ON_BN_CLICKED(IDC_DELETE_GROUP_BTN, OnBnClickedDeleteGroupBtn)
	ON_BN_CLICKED(IDC_UPDATE_DEPOSIT_BTN, OnBnClickedUpdateDepositBtn)
END_MESSAGE_MAP()


// CDepositGroupDlg �޽��� ó�����Դϴ�.

BOOL CDepositGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	if(m_bSelectMode)
	{
		CString sTitle; this->GetWindowText(sTitle);
		this->SetWindowText(sTitle + "(�׷� ����Ʈ ���� Ŭ���� ���Կ��� ���� �˴ϴ�)");
	} 
 
	m_lstGroup.InsertColumn(0, "�׷��", LVCFMT_LEFT, 100);
	m_lstGroup.GetPaintManager()->m_strNoItems = "�׷��� �����Ǿ� ���� �ʽ��ϴ�";
	m_lstGroup.Populate();
	 
	CXTPGridColumn *pCol0 = m_lstDeposit.AddColumn(new CXTPGridColumn(0, _T("�����"), 100, FALSE));
	CXTPGridColumn *pCol1 = m_lstDeposit.AddColumn(new CXTPGridColumn(0, _T("�Աݾ�(%)"), 70, FALSE));
	CXTPGridColumn *pCol2 = m_lstDeposit.AddColumn(new CXTPGridColumn(0, _T("�ּ�����ݾ�"), 80, FALSE));
	m_lstDeposit.GetPaintManager()->m_strNoItems = "";
	m_lstDeposit.AllowEdit(TRUE); 
	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;
	m_lstDeposit.Populate();

	RefreshGroupList();
	RefreshDepositList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDepositGroupDlg::OnReportItemGroupClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	RefreshDepositList();
}

void CDepositGroupDlg::OnReportItemGroupDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == NULL) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_nDepositRateGroup = m_lstGroup.GetItemData(pRecord);
	m_sDepositRateGroupName = m_lstGroup.GetItemText(pRecord->GetIndex(), 0);

	OnOK();
}

void CDepositGroupDlg::OnReportItemDepositClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return; 

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex(); 

	if(nCol > 0)
	{
		((CXTPGridRecordItemText*)m_lstDeposit.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetValue("");
		((CXTPGridRecordItemText*)m_lstDeposit.GetRecords()->GetAt(nRow)->GetItem(nCol))->SetCaption("");
	}
}

void CDepositGroupDlg::RefreshGroupList()
{
	m_lstGroup.DeleteAllItems(); 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_deposit_group");

	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return;

	long nID;
	CString sDepositRateName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sDepositRateName", sDepositRateName);

		m_lstGroup.InsertItem(i, sDepositRateName);
		m_lstGroup.SetItemData(i, nID);

		pRs.MoveNext();
	}

	m_lstGroup.Populate();

}

void CDepositGroupDlg::RefreshDepositList()
{ 
	m_lstDeposit.DeleteAllItems();
	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nID = m_lstGroup.GetItemData(pRows->GetAt(0)->GetRecord());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb,  "select_deposit_rate_for_group");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(nID);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10]; 
	long nTargetCompany, nMyDepositRate, nMyApply;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTargetCompany", nTargetCompany);
		pRs.GetFieldValue("nMyDepositRate", nMyDepositRate);
		pRs.GetFieldValue("nMyApply", nMyApply);

		m_lstDeposit.InsertItem(i, m_ci.GetBranchName(nTargetCompany));
		m_lstDeposit.SetItemText(i, 1, itoa(nMyDepositRate, buffer, 10));
		m_lstDeposit.SetItemText(i, 2, itoa(nMyApply, buffer, 10));

		m_lstDeposit.SetItemLong(i, nTargetCompany);

		pRs.MoveNext();
	}

	m_lstDeposit.Populate();

}

void CDepositGroupDlg::OnBnClickedMakeGroupBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "���� �� �׷���� �Է��ϼ���";

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "insert_deposit_group");
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(dlg.m_sValue);

		if(pCmd.Execute())
			RefreshGroupList();
	}
}

void CDepositGroupDlg::OnBnClickedUpdateGroupBtn()
{
	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) 
		{MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}
	else if(pRows->GetCount() == 0)
		{MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "���� �� �׷���� �Է��ϼ���";
	dlg.m_sValue = pRecord->GetItem(0)->GetCaption(NULL);

	long nDespositGroupID = m_lstDeposit.GetItemData(pRecord);

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "update_deposit_group");
		pCmd.AddParameter(nDespositGroupID);
		pCmd.AddParameter(dlg.m_sValue);

		if(pCmd.Execute())
			RefreshGroupList();
	}
}

void CDepositGroupDlg::OnBnClickedDeleteGroupBtn()
{
	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL)
		MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;
	if(pRows->GetCount() == 0)
		MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	CString sGroup = pRecord->GetItem(0)->GetCaption(NULL);
	sGroup = "[" + sGroup + "]�� ���� �Ͻðڽ��ϱ�?";

	if(MessageBox(sGroup, "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	long nDespositGroupID = m_lstDeposit.GetItemData(pRecord);

	CMkCommand pCmd(m_pMkDb, "delete_deposit_group");
	pCmd.AddParameter(nDespositGroupID);
	
	if(pCmd.Execute())
		RefreshGroupList();
}

void CDepositGroupDlg::OnBnClickedUpdateDepositBtn()
{ 
	CXTPGridSelectedRows* pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;

	long nGroupID = m_lstGroup.GetItemData(pRows->GetAt(0)->GetRecord());

	CXTPGridRecords *pRecords = m_lstDeposit.GetRecords();

	char buffer[10];
	CString sCompanySum = "";
	CString sDepositSum = "";
	CString sApplySum = "";

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		long nCompany = m_lstDeposit.GetItemLong(pRecord);
		long nDeposit = atoi(pRecord->GetItem(1)->GetCaption(NULL));
		long nApply = atoi(pRecord->GetItem(2)->GetCaption(NULL));

		if(nDeposit > MY_MAX_DEPOSIT)
		{
			MessageBox("�Աݾ��� 25���� Ŭ�� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			return;            
		}

		sCompanySum += (CString)itoa(nCompany, buffer, 10) + ";";
		sDepositSum += (CString)itoa(nDeposit, buffer, 10) + ";";
		sApplySum += (CString)itoa(nApply, buffer, 10) + ";";
	}

	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_for_group");
	pCmd.AddParameter(nGroupID);
	pCmd.AddParameter(sCompanySum);
	pCmd.AddParameter(sDepositSum);
	pCmd.AddParameter(sApplySum);

	if(pCmd.Execute())
	{
		MessageBox("���������� ����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		RefreshDepositList();
	}
}
