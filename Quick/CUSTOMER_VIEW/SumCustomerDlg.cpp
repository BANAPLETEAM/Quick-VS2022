// SumCustomerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SumCustomerDlg.h"
//#include "CustomerDlg.h"


// CSumCustomerDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSumCustomerDlg, CMyDialog)
CSumCustomerDlg::CSumCustomerDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSumCustomerDlg::IDD, pParent)
{
}

CSumCustomerDlg::~CSumCustomerDlg()
{
}

void CSumCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_ALL, m_ReportAll);
	DDX_Control(pDX, IDC_REPORT_DEL, m_ReportDel);
	DDX_Control(pDX, IDC_REPORT_SUM, m_ReportSum);
}


BEGIN_MESSAGE_MAP(CSumCustomerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_DEL_CUS_BTN, OnBnClickedDelCusBtn)
	ON_BN_CLICKED(IDC_SUM_CUS_BTN, OnBnClickedSumCusBtn)
	ON_BN_CLICKED(IDC_DEL_CUS_BTN2, OnBnClickedDelCusBtn2)
	ON_BN_CLICKED(IDC_SUM_CUS_BTN2, OnBnClickedSumCusBtn2)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_DEL, OnNMDblclkDelReport)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_SUM, OnNMDblclkSumReport)
END_MESSAGE_MAP()


void CSumCustomerDlg::OnNMDblclkDelReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedDelCusBtn2();
}

void CSumCustomerDlg::OnNMDblclkSumReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedSumCusBtn2();
}


void CSumCustomerDlg::OnBnClickedDelCusBtn()
{
	long nItem = m_ReportAll.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) return;

	CXTPGridRows *pRows = m_ReportAll.GetRows();
	CXTPGridRecords *pRecords = m_ReportAll.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPGridRecord *pRecord = pRow->GetRecord();

	long nSel = pRow->GetIndex();

	pRecord->SetVisible(FALSE);

	long nCount = m_ReportDel.GetItemCount();

	m_ReportDel.InsertItem(nCount, ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn));
	m_ReportDel.SetItemText(nCount, 1, ((CXTPGridRecordItemText*)pRecord->GetItem(1))->GetCaption(pColumn));
	m_ReportDel.SetItemText(nCount, 2,((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(pColumn));
	m_ReportDel.SetItemText(nCount, 3, ((CXTPGridRecordItemText*)pRecord->GetItem(3))->GetCaption(pColumn));
	m_ReportDel.SetItemText(nCount, 4,((CXTPGridRecordItemText*)pRecord->GetItem(7))->GetCaption(pColumn));
	m_ReportDel.SetItemLong(nCount, m_ReportAll.GetItemLong(pRecord));
	m_ReportDel.SetItemData(nCount, (long)pRecord->GetIndex());

	m_ReportDel.Populate();   	
	m_ReportAll.Populate();

	m_ReportAll.SetSelectedRow(min(nSel, m_ReportAll.GetRows()->GetCount() -2));

	pRow = m_ReportAll.GetSelectedRows()->GetAt(0);
	m_ReportAll.EnsureVisible(pRow);
	

}

void CSumCustomerDlg::OnBnClickedSumCusBtn()
{
	long nItem = m_ReportAll.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) return;

	CXTPGridRows *pRows = m_ReportAll.GetRows();
	CXTPGridRecords *pRecords = m_ReportAll.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPGridRecord *pRecord = pRow->GetRecord();

	long nSel = pRow->GetIndex();

	pRecord->SetVisible(FALSE);

	long nCount = m_ReportSum.GetItemCount();

	if(nCount != 0) // ����
	{
		long nData = m_ReportSum.GetItemData(0);
		CXTPGridRecord *pRecord = m_ReportAll.GetRecords()->GetAt(nData);
		pRecord->SetVisible(TRUE);
		m_ReportAll.Populate();

		m_ReportSum.GetRecords()->RemoveAt(0);
		m_ReportSum.GetRows()->RemoveAt(0);
		m_ReportSum.Populate();
	}

	m_ReportSum.InsertItem(0, ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn));
	m_ReportSum.SetItemText(0, 1, ((CXTPGridRecordItemText*)pRecord->GetItem(1))->GetCaption(pColumn));
	m_ReportSum.SetItemText(0, 2,((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(pColumn));
	m_ReportSum.SetItemText(0, 3, ((CXTPGridRecordItemText*)pRecord->GetItem(3))->GetCaption(pColumn));
	m_ReportSum.SetItemText(0, 4,((CXTPGridRecordItemText*)pRecord->GetItem(7))->GetCaption(pColumn));
	m_ReportSum.SetItemLong(0, m_ReportAll.GetItemLong(pRecord));
	m_ReportSum.SetItemData(0, (long)pRecord->GetIndex());

	m_ReportSum.Populate();   	
	m_ReportAll.Populate();

	m_ReportAll.SetSelectedRow(min(nSel, m_ReportAll.GetRows()->GetCount() -2)); 

	pRow = m_ReportAll.GetSelectedRows()->GetAt(0); 
	m_ReportAll.EnsureVisible(pRow);
}

BOOL CSumCustomerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_ReportAll.InsertColumn(0,"��ȣ",LVCFMT_LEFT,50);
	m_ReportAll.InsertColumn(1,"��ȣ",LVCFMT_LEFT,125);
	m_ReportAll.InsertColumn(2,"�μ�",LVCFMT_LEFT,85);
	m_ReportAll.InsertColumn(3,"���",LVCFMT_LEFT,65);
	m_ReportAll.InsertColumn(4,"���̵�",LVCFMT_LEFT,60);
	m_ReportAll.InsertColumn(5,"��ȭ��ȣ",LVCFMT_LEFT,100);
	m_ReportAll.InsertColumn(6,"���ص�",LVCFMT_LEFT,70);
	m_ReportAll.InsertColumn(7,"�׷��",LVCFMT_LEFT,95);
	m_ReportAll.InsertColumn(8,"��ġ",LVCFMT_LEFT,280);
	m_ReportAll.InsertColumn(9,"�ſ�",LVCFMT_LEFT,40);
	m_ReportAll.InsertColumn(10,"�����",LVCFMT_LEFT,40);
	m_ReportAll.GetPaintManager()->m_strNoItems = "";

	m_ReportAll.Populate();

	m_ReportDel.InsertColumn(0,"��ȣ",LVCFMT_LEFT,50);
	m_ReportDel.InsertColumn(1,"��ȣ",LVCFMT_LEFT,125);
	m_ReportDel.InsertColumn(2,"�μ�",LVCFMT_LEFT,85);
	m_ReportDel.InsertColumn(3,"���",LVCFMT_LEFT,65);
	m_ReportDel.InsertColumn(4,"�׷��",LVCFMT_LEFT,60);
	m_ReportDel.GetPaintManager()->m_strNoItems = "";

	m_ReportDel.Populate();

	m_ReportSum.InsertColumn(0,"��ȣ",LVCFMT_LEFT,50);
	m_ReportSum.InsertColumn(1,"��ȣ",LVCFMT_LEFT,125);
	m_ReportSum.InsertColumn(2,"�μ�",LVCFMT_LEFT,85);
	m_ReportSum.InsertColumn(3,"���",LVCFMT_LEFT,65);
	m_ReportSum.InsertColumn(4,"�׷��",LVCFMT_LEFT,60);
	m_ReportSum.GetPaintManager()->m_strNoItems = "";

	m_ReportSum.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSumCustomerDlg::RefreshList()
{
	CXTPGridRecords *pRecords = m_CusReport->GetRecords();
	CXTPGridColumn *pColumn = NULL;

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		m_ReportAll.InsertItem(i, ((CXTPGridRecordItemNumber*)pRecord->GetItem(0))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 1, ((CXTPGridRecordItemNumber*)pRecord->GetItem(1))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 2, ((CXTPGridRecordItemNumber*)pRecord->GetItem(2))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 3, ((CXTPGridRecordItemNumber*)pRecord->GetItem(3))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 4, ((CXTPGridRecordItemNumber*)pRecord->GetItem(4))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 5, ((CXTPGridRecordItemNumber*)pRecord->GetItem(5))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 6, ((CXTPGridRecordItemNumber*)pRecord->GetItem(6))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 7, ((CXTPGridRecordItemNumber*)pRecord->GetItem(7))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 8, ((CXTPGridRecordItemNumber*)pRecord->GetItem(8))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 9, ((CXTPGridRecordItemNumber*)pRecord->GetItem(9))->GetCaption(pColumn));
		m_ReportAll.SetItemText(i, 10, ((CXTPGridRecordItemNumber*)pRecord->GetItem(10))->GetCaption(pColumn));

		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_CusReport->GetItemData(pRecord);

		m_ReportAll.SetItemLong(i, pc->nCNo);
		m_ReportAll.SetItemData(i, i);

	}

	m_ReportAll.Populate();

}

void CSumCustomerDlg::OnBnClickedDelCusBtn2()
{
	long nItem = m_ReportDel.GetNextItem(-1, LVNI_SELECTED);

	if(nItem == -1) return;

	long nData = (long)m_ReportDel.GetItemData(nItem);
		
	CXTPGridRecord *pRecord = m_ReportAll.GetRecords()->GetAt(nData);
	pRecord->SetVisible(TRUE);

	m_ReportDel.GetRecords()->RemoveAt(nItem);

	m_ReportAll.Populate();
	m_ReportDel.Populate();


	m_ReportDel.SetSelectedRow(min(nItem, m_ReportDel.GetRows()->GetCount() -2)); 

	CXTPGridRow *pRow = m_ReportDel.GetSelectedRows()->GetAt(0); 
	m_ReportDel.EnsureVisible(pRow);
}

void CSumCustomerDlg::OnBnClickedSumCusBtn2()
{
	long nItem = m_ReportSum.GetItemCount();

	if(nItem == 0) return;

	long nData = (long)m_ReportSum.GetItemData(0);

	CXTPGridRecord *pRecord = m_ReportAll.GetRecords()->GetAt(nData);
	pRecord->SetVisible(TRUE);

	m_ReportSum.GetRecords()->RemoveAt(0);

	m_ReportAll.Populate();
	m_ReportSum.Populate();

}

void CSumCustomerDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CSumCustomerDlg::OnBnClickedOkBtn()
{
	if(m_ReportDel.GetItemCount() == 0)
	{
		MessageBox("������ ���� �Ѹ� �̻� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_ReportSum.GetItemCount() == 0)
	{
		MessageBox("�������� ���� �Ѹ� �̻� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	BOOL bGNoMove = FALSE;

	if(MessageBox("���� �� ���� �׷������ ������ ������ �Բ� �̵��Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
		bGNoMove = TRUE;

	CString sMsg = "";
	CString sTitelMsg = "������(������ Ȯ���Ͻñ� �ٶ��ϴ�!!!)";
	sMsg = "�����ս� �ش���� ������ ���������� ��� ���յ˴ϴ�.";

	if(MessageBox(sMsg, sTitelMsg, MB_OKCANCEL) == IDOK)
	{
		sMsg = "�ѹ� ���յ� ����ȣ�� �ٽ� �и���ų �� ������ �����Ͻñ� �ٶ��ϴ�.\r\n[Ȯ��] Ŭ�� �� ���� ���յ˴ϴ�";

		if(MessageBox(sMsg, sTitelMsg, MB_OKCANCEL) == IDOK)
		{
            if(SumCustomer(bGNoMove))
			{
				MessageBox("���� ���յǾ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
				OnOK();
			}
		}
	}
}

BOOL CSumCustomerDlg::SumCustomer(BOOL bGNoMove)
{
	char buffer[20];
    CString sSrcCNo = "";
	long nDstCNo = 0;


	for(int i=0; i<m_ReportDel.GetItemCount(); i++)
	{
		long nCNo = m_ReportDel.GetItemLong(i);
		sSrcCNo += CString(itoa(nCNo, buffer, 10)) + ";";
	}

	nDstCNo = m_ReportSum.GetItemLong(0);

	CMkCommand pCmd(m_pMkDb, "Integrated_customer_4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeString, typeInput, sSrcCNo.GetLength(), sSrcCNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nDstCNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bGNoMove);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	CString sDeleteEtc = "������[����â] ����";
	pCmd.AddParameter(sDeleteEtc);

	if(pCmd.Execute()) return TRUE;

	return FALSE;
}
