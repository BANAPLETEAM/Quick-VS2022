// RiderDepositEditHistoryDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositEditHistoryDlg.h"

#include "MyReportPaintManager.h"


// CRiderDepositEditHistoryDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderDepositEditHistoryDlg, CMyDialog)
CRiderDepositEditHistoryDlg::CRiderDepositEditHistoryDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderDepositEditHistoryDlg::IDD, pParent)
{
}

CRiderDepositEditHistoryDlg::~CRiderDepositEditHistoryDlg()
{
}

void CRiderDepositEditHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
}


BEGIN_MESSAGE_MAP(CRiderDepositEditHistoryDlg, CMyDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRiderDepositEditHistoryDlg �޽��� ó�����Դϴ�.

void CRiderDepositEditHistoryDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void CRiderDepositEditHistoryDlg::OnBnClickedOk()
{
	RefreshList();	
}

BOOL CRiderDepositEditHistoryDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CXTPGridColumn *pCol10 = m_Report.AddColumn(new CXTPGridColumn(0, "����", 40, FALSE));
	CXTPGridColumn *pCol11 = m_Report.AddColumn(new CXTPGridColumn(1, "������", 90, FALSE));
	CXTPGridColumn *pCol12 = m_Report.AddColumn(new CXTPGridColumn(2, "����", 90, FALSE));
	CXTPGridColumn *pCol13 = m_Report.AddColumn(new CXTPGridColumn(3, "�����ð�", 90, FALSE));
	CXTPGridColumn *pCol14 = m_Report.AddColumn(new CXTPGridColumn(4, "���泻��", 100, FALSE));
	CXTPGridColumn *pCol15 = m_Report.AddColumn(new CXTPGridColumn(5, "������", 130, FALSE));
	CXTPGridColumn *pCol16 = m_Report.AddColumn(new CXTPGridColumn(6, "������", 130, FALSE));

	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->SetTreeColumn(1);
	pCol10->SetAlignment(DT_RIGHT);	
	pCol11->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol11->SetAlignment(DT_RIGHT);
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol12->SetAlignment(DT_CENTER);
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol13->SetAlignment(DT_RIGHT);
	pCol14->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol14->SetAlignment(DT_CENTER);
	pCol15->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol15->SetAlignment(DT_CENTER);
	pCol16->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol16->SetAlignment(DT_CENTER);

	m_Report.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Report.GetReportHeader()->AllowColumnResize(TRUE);
	m_Report.GetReportHeader()->AllowColumnSort(FALSE);
	m_Report.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_Report.SetPaintManager(new CMyReportPaintManager());
	m_Report.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_Report.AllowEdit(FALSE);
	m_Report.FocusSubItems(TRUE);
	m_Report.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_Report.SetGridColor(RGB(180, 180, 200));
	m_Report.SetTreeIndent(30);

	m_Report.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderDepositEditHistoryDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_edit_history_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	//	2007-01-06 18:13:07.583		10	0	10	15990707	15990808	���ﵿ	�Ｚ��	[���5:���� ��]	9000	1000	
	COleDateTime dtLog;

	if(pRs.GetRecordCount() == 1)
		return;

	for(int i=0 ; i<pRs.GetRecordCount(); i++)
	{
		DEPOSIT_EDIT_HISTORY EditHistory;

		pRs.GetFieldValue("dtGenerate", EditHistory.dtEdit);
		pRs.GetFieldValue("nRiderCompany", EditHistory.nRiderCompany);
		pRs.GetFieldValue("nRNo", EditHistory.nRNo);
		pRs.GetFieldValue("sRName", EditHistory.sRName);
		pRs.GetFieldValue("nDepositType", EditHistory.nDepositType);

		pRs.GetFieldValue("nDepositAllocateType", EditHistory.nDepositAllocateType);
		pRs.GetFieldValue("sMyCallRateType", EditHistory.sMyCallRateType);
		pRs.GetFieldValue("sOtherCallRateType", EditHistory.sOtherCallRateType);
		pRs.GetFieldValue("nFixedDeposit", EditHistory.nFixedDeposit);
		pRs.GetFieldValue("nPayMentDay", EditHistory.nPayMentDay);
		pRs.GetFieldValue("nWNo", EditHistory.nWNo);
		pRs.GetFieldValue("sWName", EditHistory.sWName);

		//�ٹ�����, �Աݹ��, ���Ա�, �ڻ���, Ÿ����, ������

		
		int nItem = 0;

		EditHistory.item[nItem++] = GetDepositType(EditHistory.nDepositType);
		EditHistory.item[nItem++] = EditHistory.nDepositAllocateType == 0 ? "���Ա�" : "���Ա�";
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nFixedDeposit);
		EditHistory.item[nItem++] = EditHistory.sMyCallRateType;
		EditHistory.item[nItem++] = EditHistory.sOtherCallRateType;
		EditHistory.item[nItem++] = GetPayMentDay(EditHistory.nDepositType, EditHistory.nPayMentDay);

		m_EditHistoryMap[i] = EditHistory;

		pRs.MoveNext();
	}

	CompareMap();
}

void CRiderDepositEditHistoryDlg::CompareMap()
{
	CString sTitle[] = {"�ٹ�����", "�Աݹ��", "���Ա�", "�ڻ���", "Ÿ����", "������"};

	map<long, DEPOSIT_EDIT_HISTORY>::iterator pos;

	CXTPGridRecord *pMainRecord = NULL;
	CXTPGridRecord *pSubMainRecord = NULL;

	int nItem = 0;

	for(pos = m_EditHistoryMap.begin(); pos != m_EditHistoryMap.end(); pos++)
	{
		bool bTreeHead = TRUE;

		map<long, DEPOSIT_EDIT_HISTORY>::iterator pos1 = pos;
		pos1++;

		if(pos1 == m_EditHistoryMap.end())
			break;

		BOOL bDifferent = FALSE;


		for(int i=0; i<MAX_STRING_COUNT; i++)
		{
			if(pos->second.item[i] != pos1->second.item[i])
			{
				bDifferent = TRUE;
				break;
			}			
		}	

		if(bDifferent == FALSE)
			continue;

		for(int i=0; i<MAX_STRING_COUNT; i++)
		{
			if(i == 0)
			{
				pMainRecord = m_Report.AddRecord(new CRiderDepositRecord(nItem++, pos->second.dtEdit, pos->second.nRNo, pos->second.sRName,
					pos->second.nWNo, pos->second.sWName, sTitle[i], pos->second.item[i], pos1->second.item[i], TRUE));
			}
			else 
			{
				pMainRecord->GetChilds()->Add(new CRiderDepositRecord(0, pos->second.dtEdit, pos->second.nRNo, pos->second.sWName,
				pos->second.nWNo, pos->second.sWName, sTitle[i], pos->second.item[i], pos1->second.item[i], FALSE));

				pMainRecord->SetExpanded(TRUE);
			}
		}	

		m_Report.AddRecord(new CRiderDepositRecord(""));
	}

	m_Report.Populate();
}

CString CRiderDepositEditHistoryDlg::GetDepositType(long nDepositType)
{
	if(nDepositType == 20)
		return "����";
	if(nDepositType == 30)
		return "�ֺ�";
	if(nDepositType == 40)
		return "�Ϻ�";
	if(nDepositType == 50)
		return "������";

	return "�˼�����";
}

CString CRiderDepositEditHistoryDlg::GetPayMentDay(long nDepositType, long nPayMentDay)
{
	char buffer[10];
	
    if(nDepositType == 20) // ����
		return (CString)itoa(nPayMentDay, buffer, 10) + "��";

	if(nDepositType == 30) //�ֺ�
	{
		char *dayofweek[] = {"��", "��", "ȭ", "��", "��", "��", "��", "���"};
		return dayofweek[nPayMentDay];
	}

	return "";

}
