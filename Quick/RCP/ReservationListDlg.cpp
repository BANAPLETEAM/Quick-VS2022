// ReservationListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReservationListDlg.h"



// CReservationListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CReservationListDlg, CMyDialog)
CReservationListDlg::CReservationListDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CReservationListDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_bIntegrated = FALSE;
}




CReservationListDlg::~CReservationListDlg()
{

}

void CReservationListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CReservationListDlg, CMyDialog)

	ON_BN_CLICKED(ID_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, OnLvnDeleteitemList1)
END_MESSAGE_MAP()


// CReservationListDlg �޽��� ó�����Դϴ�.

BOOL CReservationListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	m_List.InsertColumn(0,"��ȣ",LVCFMT_LEFT,40);
	m_List.InsertColumn(1,"�����",LVCFMT_LEFT,90);
	m_List.InsertColumn(2,"�߼��Ͻ�",LVCFMT_LEFT, 120);
	m_List.InsertColumn(3,"�����Ͻ�",LVCFMT_LEFT,120);
	m_List.InsertColumn(4,"�߼ۼ�",LVCFMT_LEFT,80);
	m_List.InsertColumn(5,"�߼۱ݾ�",LVCFMT_LEFT,80);	
	m_List.InsertColumn(6,"",LVCFMT_LEFT,0);


	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CReservationListDlg::RefreshList()
{
	m_List.DeleteAllItems();

	//CWaitCursor wait;

	CMkRecordset pRs2(m_pMkDb);	
	CMkCommand pCmd2(m_pMkDb, "select_sms_reservation_list_1");
	pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bIntegrated);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);

	if(!pRs2.Execute(&pCmd2)) return;

	int nItem = 0;
	long nID = 0,nAmount = 0 , nCount = 0, nBalance = 0, nCompany = 0;
	CString sBranchName = "";		
	COleDateTime dtGenerate, dtTran;
	char buffer[10];
	while(!pRs2.IsEOF())	
	{
		pRs2.GetFieldValue("sBranchName", sBranchName);
		pRs2.GetFieldValue("dtGenerate", dtGenerate);
		pRs2.GetFieldValue("nCount", nCount);		
		pRs2.GetFieldValue("nAmount", nAmount);			
		pRs2.GetFieldValue("dtTran", dtTran);				
		pRs2.GetFieldValue("nCompany", nCompany);		

		SMS_RESERVATION *obSms = new SMS_RESERVATION;
		obSms->dt = dtTran;
		obSms->nCompany = nCompany;

		m_List.InsertItem(nItem, ltoa(nItem + 1, buffer, 10));
		m_List.SetItemText(nItem, 1, sBranchName);
		m_List.SetItemText(nItem, 2, dtGenerate.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(nItem, 3, dtTran.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nCount));
		m_List.SetItemText(nItem, 5, LF->GetMyNumberFormat(nAmount));		
		m_List.SetItemText(nItem, 6, ltoa(nCompany, buffer,10));		
		m_List.SetItemData(nItem, (DWORD_PTR)obSms);

		nItem++;

		pRs2.MoveNext();
	}
	pRs2.Close();
}


void CReservationListDlg::OnBnClickedCancelBtn()
{
	long nItem = m_List.GetSelectionMark();

	if(nItem < 0) return;

	if(MessageBox(m_List.GetItemText(nItem, 0) + "���� ������ ���� ���� �Ͻðڽ��ϱ�?", 
		"�������", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{

		long nCompany = 0;
		nCompany = atol(m_List.GetItemText(nItem, 6));
		SMS_RESERVATION *obSms = NULL;
		obSms = (SMS_RESERVATION*)m_List.GetItemData(nItem);


		if(nCompany <= 0 || obSms == NULL) return;

		//CWaitCursor wait;
		CMkRecordset pRs2(m_pMkDb);		
		CMkCommand pCmd2(m_pMkDb, "delete_sms_reservation");
		pCmd2.AddParameter(typeDate , typeInput, sizeof(COleDateTime), obSms->dt);
		pCmd2.AddParameter(typeBool, typeInput, sizeof(int), nCompany);
		CMkParameter *parSuccess = pCmd2.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);
		if(!pRs2.Execute(&pCmd2)) return;
		int nSuccess = 0;
		parSuccess->GetValue(nSuccess);
		if(nSuccess)
		{
			MessageBox("���� �Ǿ����ϴ�.", 	"����", MB_ICONINFORMATION);
			RefreshList();
		}
		else
		{
			MessageBox("���� ���� �ʾҽ��ϴ�. �� 30���� �ٽû��� ��Ź�帳�ϴ�", 	
				"����", MB_ICONINFORMATION);

		}
	}	
}

void CReservationListDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReservationListDlg::OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SMS_RESERVATION *ri = NULL;
	ri = (SMS_RESERVATION*)m_List.GetItemData(pNMLV->iItem);
	if(ri != NULL)
	{
		delete ri;
		ri = NULL;
	}

	*pResult = 0;
}
