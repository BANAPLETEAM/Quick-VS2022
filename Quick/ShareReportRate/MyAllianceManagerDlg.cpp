// MyAllianceManagerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MyAllianceManagerDlg.h"



// CMyAllianceManagerDlg ��ȭ �����Դϴ�.

CMyAllianceRecord::CMyAllianceRecord(long nShareCode1, CString strName, 
									 CString strPhone, long nShareSec, 
									long nGiveCall, long nTakeCall,
									COleDateTime dtEdit)
{
	m_nShareCode1 = nShareCode1;

	AddItem(new CXTPGridRecordItemText(strName));
	AddItem(new CXTPGridRecordItemText(strPhone));
	AddItem(new CShareSecRecordItem(nShareSec));
	AddItem(new CXTPGridRecordItemNumber(nGiveCall));
	AddItem(new CXTPGridRecordItemNumber(nTakeCall));
	AddItem(new CGiveTakeRateRecordItemNumber((double)nGiveCall * 100 / max(nTakeCall, 1)));
	AddItem(new CMyRecordItemDateTime(dtEdit));
}


void CMyAllianceRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridRecord::GetItemMetrics(pDrawArgs, pItemMetrics);

	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nSec = ((CShareSecRecordItem*)GetItem(2))->GetValue();

	if(nCol < 2)
	{
		pItemMetrics->clrBackground = RGB(100, 220, 100);
		pItemMetrics->clrForeground= RGB(255, 255, 255);
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}
	else if(nCol == 2 && nSec > 1)
	{

		pItemMetrics->clrBackground = RGB(200, 255, 200);
		pItemMetrics->clrForeground= RGB(0, 0, 0);
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}
	
	if(nCol > 2)
	{
		pDrawArgs->nTextAlign = DT_RIGHT;
	}

}



IMPLEMENT_DYNAMIC(CMyAllianceManagerDlg, CMyDialog)
CMyAllianceManagerDlg::CMyAllianceManagerDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMyAllianceManagerDlg::IDD, pParent)
{
}

CMyAllianceManagerDlg::~CMyAllianceManagerDlg()
{
}

void CMyAllianceManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
}


BEGIN_MESSAGE_MAP(CMyAllianceManagerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
END_MESSAGE_MAP()





// CMyAllianceManagerDlg �޽��� ó�����Դϴ�.

BOOL CMyAllianceManagerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	long nItem = 0;
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "ȸ���", 130, FALSE));
	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "��ǥ��ȭ", 100, FALSE));
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "���ճ�������", 90, FALSE));
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "�ѱ���", 60, FALSE));
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "������", 60, FALSE));
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "������(����/����*100)", 150, FALSE));
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "�����ð�", 80, FALSE));
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;


	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(222, 222, 222));

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMyAllianceManagerDlg::RefreshList()
{
	m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_my_alliance_info");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nAllianceID);

	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			CString strName, strTel;
			long nShareCode1, nTakeSum, nGiveSum, nRate, nSec;
			COleDateTime dtLog;

			pRs.GetFieldValue("nShareCode1", nShareCode1);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sTel", strTel);
			pRs.GetFieldValue("nTakeSum", nTakeSum);
			pRs.GetFieldValue("nGiveSum", nGiveSum);
			pRs.GetFieldValue("nRate", nRate);
			pRs.GetFieldValue("nSec", nSec);
			pRs.GetFieldValue("dtLog", dtLog);

			m_wndReport.AddRecord(new CMyAllianceRecord(nShareCode1, 
							strName, strTel, nSec, nTakeSum, nGiveSum, dtLog));
			pRs.MoveNext();
		}

		m_wndReport.Populate();
	}
}


void CMyAllianceManagerDlg::OnBnClickedSaveBtn()
{
	for(int i = 0; i < m_wndReport.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long nShareCode1 = ((CMyAllianceRecord*)pRecord)->m_nShareCode1;
		long nSec = ((CMyAllianceRecord*)pRecord)->GetShareSec();

		if(((CMyAllianceRecord*)pRecord)->GetDirtyFlag())
		{
			if(m_ci.m_nAllianceID == 0)
				return;


			CMkCommand pCmd(m_pMkDb, "update_share_exp_table_for_company");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareCode1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nAllianceID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nSec);
			if(!pCmd.Execute())		
			{
				MessageBox("������ ������ �߻��߽��ϴ�.", "Ȯ��", MB_ICONERROR);
				return;
			}

		}
	}

	MessageBox("�߰�/����/���� �Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	RefreshList();
}


