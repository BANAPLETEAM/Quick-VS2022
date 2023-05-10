// DepositGroupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositGroupDlg.h"
#include "VarietyDlg.h"

// CRiderDepositGroupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderDepositGroupDlg, CMyDialog)
CRiderDepositGroupDlg::CRiderDepositGroupDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderDepositGroupDlg::IDD, pParent)
{
	m_bSelectMode = NULL;
	m_strDepositRateGroupName = "";
	m_nCompany = 0;
}

CRiderDepositGroupDlg::~CRiderDepositGroupDlg()
{
}

void CRiderDepositGroupDlg::DoDataExchange(CDataExchange* pDX)
{   
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_LIST, m_lstGroup);
	DDX_Control(pDX, IDC_DEPOSIT_LIST, m_lstDeposit);
}


BEGIN_MESSAGE_MAP(CRiderDepositGroupDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_LIST, OnReportItemGroupClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_LIST, OnReportItemGroupDblClick)
	ON_NOTIFY(NM_CLICK, IDC_DEPOSIT_LIST, OnReportItemDepositClick)
	ON_BN_CLICKED(IDC_MAKE_GROUP_BTN, OnBnClickedMakeGroupBtn)
	ON_BN_CLICKED(IDC_UPDATE_GROUP_BTN, OnBnClickedUpdateGroupBtn)
	ON_BN_CLICKED(IDC_DELETE_GROUP_BTN, OnBnClickedDeleteGroupBtn)
	ON_BN_CLICKED(IDC_UPDATE_DEPOSIT_BTN, OnBnClickedUpdateDepositBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CRiderDepositGroupDlg �޽��� ó�����Դϴ�.

BOOL CRiderDepositGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	if(m_bSelectMode)
	{
		CString strTitle; this->GetWindowText(strTitle);
		this->SetWindowText(strTitle + "(�׷� ����Ʈ ���� Ŭ���� ���Կ��� ���� �˴ϴ�)");
	}

	m_lstGroup.InsertColumn(0, "�׷��", LVCFMT_LEFT, 100);
	m_lstGroup.GetPaintManager()->m_strNoItems = "�׷��� �����Ǿ� ���� �ʽ��ϴ�";
	m_lstGroup.Populate();

	CXTPGridColumn *pCol0 = m_lstDeposit.AddColumn(new CXTPGridColumn(0, _T("�����Աݾ�(%)"), 90, FALSE));
	CXTPGridColumn *pCol1 = m_lstDeposit.AddColumn(new CXTPGridColumn(1, _T("����Աݾ�(%)"), 90, FALSE));
	CXTPGridColumn *pCol2 = m_lstDeposit.AddColumn(new CXTPGridColumn(2, _T("�ּ�����ݾ�"), 80, FALSE));
	m_lstDeposit.GetPaintManager()->m_strNoItems = "";
	m_lstDeposit.AllowEdit(TRUE); 
	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;
	m_lstDeposit.Populate();

	RefreshGroupList();

	if(m_lstGroup.GetItemCount() > 0 &&
		m_bSelectMode == TRUE && m_nDepositRateGroup > 0)
	{
		for(int i=0; i<m_lstGroup.GetItemCount(); i++)
		{
			long nType = m_lstGroup.GetItemData(i);

			if(m_nDepositRateGroup == nType)
			{
				CXTPGridRow *pRow = m_lstGroup.GetRows()->GetAt(i);
				m_lstGroup.GetSelectedRows()->Select(pRow);
			}
		}			
	}

	RefreshDepositList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderDepositGroupDlg::OnReportItemGroupClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	RefreshDepositList();
}

void CRiderDepositGroupDlg::OnReportItemGroupDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == NULL) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_nDepositRateGroup = m_lstGroup.GetItemData(pRecord);
	m_strDepositRateGroupName = m_lstGroup.GetItemText(pRecord->GetIndex(), 0);

	OnOK();
}

void CRiderDepositGroupDlg::OnReportItemDepositClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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

void CRiderDepositGroupDlg::RefreshGroupList()
{
	m_lstGroup.DeleteAllItems(); 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_group");

	pCmd.AddParameter(m_nCompany);

	if(!pRs.Execute(&pCmd)) return;

	long nType;
	CString sTypeName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("sTypeName", sTypeName);

		m_lstGroup.InsertItem(i, sTypeName);
		m_lstGroup.SetItemData(i, nType);

		pRs.MoveNext();
	}

	m_lstGroup.Populate();

}

void CRiderDepositGroupDlg::RefreshDepositList()
{ 
	m_lstDeposit.DeleteAllItems();
	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	long nType = m_lstGroup.GetItemData(pRows->GetAt(0)->GetRecord());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb,  "select_rider_deposit_rate_for_group_1");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(nType);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10]; 
	long nDepositRate, nRiderDeposit, nApplyCharge;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nDepositRate", nDepositRate);
		pRs.GetFieldValue("nRiderDeposit", nRiderDeposit);
		pRs.GetFieldValue("nApplyCharge", nApplyCharge);

		m_lstDeposit.InsertItem(i, itoa(nDepositRate, buffer, 10));
		m_lstDeposit.SetItemText(i, 1, itoa(nRiderDeposit, buffer, 10));
		m_lstDeposit.SetItemText(i, 2, itoa(nApplyCharge, buffer, 10));
		pRs.MoveNext();
	}

	m_lstDeposit.Populate();

}

void CRiderDepositGroupDlg::OnBnClickedMakeGroupBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "���� �� �׷���� �Է��ϼ���";

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "insert_rider_deposit_group");
		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(dlg.m_sValue);

		if(pCmd.Execute())
			RefreshGroupList();
	}
}

void CRiderDepositGroupDlg::OnBnClickedUpdateGroupBtn()
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

	long nType = m_lstGroup.GetItemData(pRecord);

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "update_rider_deposit_group");

		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(nType);
		pCmd.AddParameter(dlg.m_sValue);

		if(pCmd.Execute())
			RefreshGroupList();
	}
}

void CRiderDepositGroupDlg::OnBnClickedDeleteGroupBtn()
{
	CXTPGridSelectedRows *pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) 
	{MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}
	else if(pRows->GetCount() == 0)
	{MessageBox("������ �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	CString sGroup = pRecord->GetItem(0)->GetCaption(NULL);
	sGroup = "[" + sGroup + "]�� ���� �Ͻðڽ��ϱ�?";

	if(MessageBox(sGroup, "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	long nType = m_lstGroup.GetItemData(pRecord);

	CMkCommand pCmd(m_pMkDb, "delete_rider_deposit_group_1");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(nType);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
		RefreshGroupList();
}

void CRiderDepositGroupDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CRiderDepositGroupDlg::OnBnClickedUpdateDepositBtn()
{ 
	CXTPGridSelectedRows* pRows = m_lstGroup.GetSelectedRows();

	if(pRows == NULL) return;

	long nType = m_lstGroup.GetItemData(pRows->GetAt(0)->GetRecord());
	CString sTypeName = m_lstGroup.GetItemText(pRows->GetAt(0)->GetRecord(), 0);

	CXTPGridRecords *pRecords = m_lstDeposit.GetRecords();

	char buffer[10];
	CString sDepositSum = "";
	CString sRiderDepositSum = "";
	CString sApplySum = "";

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		long nDeposit = atoi(pRecord->GetItem(0)->GetCaption(NULL));
		long nRiderDeposit = atoi(pRecord->GetItem(1)->GetCaption(NULL));
		long nApply = atoi(pRecord->GetItem(2)->GetCaption(NULL));

		if(nDeposit > MY_MAX_DEPOSIT)
		{
			MessageBox("�Աݾ��� 25���� Ŭ�� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			return;            
		}

		sDepositSum += (CString)itoa(nDeposit, buffer, 10) + ";";
		sRiderDepositSum += (CString)itoa(nRiderDeposit, buffer, 10) + ";";
		sApplySum += (CString)itoa(nApply, buffer, 10) + ";";
	}

	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_for_group_new2");
	pCmd.AddParameter(m_nCompany);	
	pCmd.AddParameter(nType);
	pCmd.AddParameter(sTypeName);
	pCmd.AddParameter(sDepositSum);
	pCmd.AddParameter(sRiderDepositSum);
	pCmd.AddParameter(sApplySum);

	if(pCmd.Execute())
	{
		MessageBox("���������� ����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		RefreshDepositList();
	}
}
