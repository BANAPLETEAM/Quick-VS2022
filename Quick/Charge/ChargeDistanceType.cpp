// ChargeDistance2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDistanceType.h"
#include "EtcDlg.h"


// CChargeDistanceType ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeDistanceType, CMyDialog)
CChargeDistanceType::CChargeDistanceType(CWnd* pParent, BOOL bTruck)
: CMyDialog(bTruck ? IDD_CHARGE_TYPE_TRUCK_DLG : IDD_CHARGE_TYPE_DLG, pParent)
{
	m_bTruck = bTruck;
	m_nCompany = 0;
	m_sCompany = "";
	m_bIntegrated = FALSE;
	m_sTypeName = "";
	m_nRegister2007ChargeCompany = 0;
	
}

CChargeDistanceType::~CChargeDistanceType()
{
}

void CChargeDistanceType::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_NAME_COMBO, m_cmbTypeName);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbCompany);
	
}


BEGIN_MESSAGE_MAP(CChargeDistanceType, CMyDialog)
		ON_BN_CLICKED(IDC_NEW_BUTTON, OnBnClickedNewButton)
		ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnBnClickedModifyButton)
		ON_BN_CLICKED(IDC_DELETE_BUTTON, OnBnClickedDeleteButton)
		ON_CBN_SELCHANGE(IDC_TYPE_NAME_COMBO, OnCbnSelchangeTypeNameCombo)		
		ON_BN_CLICKED(IDC_ROW_ADD_BUTTON, OnBnClickedRowAddButton)
		ON_BN_CLICKED(IDC_ROW_DELETE_BUTTON, OnBnClickedRowDeleteButton)
		ON_BN_CLICKED(IDC_REGISTER_BUTTON, OnBnClickedRegisterButton)
		ON_BN_CLICKED(IDC_ROW_DELETE_All_BUTTON, OnBnClickedRowDeleteAllButton)
		ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
		ON_CBN_SELENDCANCEL(IDC_BRANCH_COMBO, OnCbnSelendcancelCompanyCombo2)
END_MESSAGE_MAP()


void CChargeDistanceType::OnBnClickedNewButton()
{
	TypeNameInsert(0);
}

void CChargeDistanceType::OnBnClickedModifyButton()
{
	int nItem = m_cmbTypeName.GetCurSel();

	if(nItem < 0) 
		return;

	TypeNameInsert(m_cmbTypeName.GetItemData(nItem));
}

void CChargeDistanceType::TypeNameInsert(int id)
{
	CEtcDlg d;
	d.m_strTitle = "Ÿ�Ը��� �Է��ϼ���";

	if(d.DoModal() == IDOK) {
		CMkCommand cmd(m_pMkDb, "charge_distance_type_insert");	
		cmd.AddParameter(m_nCompany);
		cmd.AddParameter(id);
		cmd.AddParameter(d.m_strEtc);
		CMkParameter *parameter = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(cmd.Execute()) {
			int new_id = 0;
			parameter->GetValue(new_id);
			InputComboList(new_id);
			RefreshList();
		}
	}
}


void CChargeDistanceType::InputComboList(int select_id)
{
	int select_index = 0;
	
	m_cmbTypeName.ResetContent();

	//CWaitCursor wait;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "charge_distance_type_select");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);	
	pCmd2.Execute();
	
	if(pRs2.Execute(&pCmd2)) {
		int id = 0; CString type_name;
		while(!pRs2.IsEOF()) {			
			pRs2.GetFieldValue("id", id);		
			pRs2.GetFieldValue("type_name", type_name);

			int index = m_cmbTypeName.AddString(type_name);
			m_cmbTypeName.SetItemData(index, id);

			if(select_id == id)
				select_index = index;

			pRs2.MoveNext();
		}
		
		pRs2.Close();	
	}	

	if(m_cmbTypeName.GetCount() > select_index)
		m_cmbTypeName.SetCurSel(select_index);	
}


void CChargeDistanceType::OnBnClickedDeleteButton()
{
	int nItem = m_cmbTypeName.GetCurSel();

	if(nItem < 0)
		return;

	CString type_name; m_cmbTypeName.GetLBText(nItem, type_name);
	CString msg;
	msg.Format("[%s]�׷��� ������ �Ͻðڽ��ϱ�?", type_name);

	if(MessageBox(msg, "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	//CWaitCursor wait;
	CMkCommand pCmd2(m_pMkDb, "charge_distance_type_delete");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);	
	pCmd2.AddParameter((int)m_cmbTypeName.GetItemData(nItem));	
	pCmd2.AddParameter(m_ui.nWNo);	
	pCmd2.AddParameter(m_ui.nCompany);	
	pCmd2.AddParameter(m_ui.strName);	

	if(pCmd2.Execute()) {
		InputComboList();
		RefreshList();
	}
}


BOOL CChargeDistanceType::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_List.ModifyStyle(NULL, LVS_EDITLABELS | LVS_REPORT);
	m_List.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0, "����", LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, "���۰Ÿ�",LVCFMT_CENTER, 70);
	m_List.InsertColumn(2, "~",LVCFMT_CENTER, 30);
	m_List.InsertColumn(3, "���Ÿ�",LVCFMT_CENTER, 70);

	if(m_bTruck)
	{
		m_List.InsertColumn(4, "���(1��)",LVCFMT_RIGHT, 70);
		m_List.InsertColumn(5, "�߰�(1.4��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(6, "�߰�(2.5��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(7, "�߰�(3.5��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(8, "�߰�(5��)",LVCFMT_RIGHT, 70);
		m_List.InsertColumn(9, "�߰�(5����)",LVCFMT_RIGHT, 85);
		m_List.InsertColumn(10, "�߰�(8��)",LVCFMT_RIGHT, 70);
		m_List.InsertColumn(11, "�߰�(11��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(12, "�߰�(14��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(13, "�߰�(15��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(14, "�߰�(18��)",LVCFMT_RIGHT, 80);
		m_List.InsertColumn(15, "�߰�(25��)",LVCFMT_RIGHT, 80);
	}
	else
	{
		m_List.InsertColumn(4, "���",LVCFMT_RIGHT, 100);
	}	
	
	m_List.SetDisableCol(0);	
	m_List.SetDisableCol(2);

	UpdateData(TRUE);
	CBranchInfo *pBi = NULL;

	if(m_bIntegrated)
	{
		int nCurSel = 0;
		int nItem = 0;
		BOOL bIntegrated = FALSE;
		
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi = m_ba.GetAt(i);
			if(pBi->bIntegrated)
			{
				bIntegrated =	TRUE;
				continue;
			}
			else
			{
				if(m_nCompany == pBi->nCompanyCode)
					nCurSel = nItem;

				m_cmbCompany.InsertString(nItem,pBi->strBranchName);
				m_cmbCompany.SetItemData(nItem,pBi->nPayTable);
			}
			nItem++;
		}
		m_cmbCompany.SetCurSel(nCurSel);
		
	}
	else
	{
		m_cmbCompany.InsertString(0, m_sCompany);		
		m_cmbCompany.SetCurSel(0);
		pBi = (CBranchInfo*)m_ba.GetAt(0);
		m_nCompany = pBi->nPayTable;
		m_cmbCompany.SetItemData(0,m_nCompany);
	}

	
	
	InputComboList();
	m_cmbTypeName.SetCurSel(0);
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CChargeDistanceType::RefreshList()
{
	UpdateData(TRUE);
	int index = m_cmbTypeName.GetCurSel();	
	
	m_List.DeleteAllItems();
	
	if(index < 0)
		return;

	//CWaitCursor wait;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "charge_distance_type_detail_select");	
	pCmd2.AddParameter((int)m_cmbTypeName.GetItemData(index));		
	pCmd2.Execute();

	char buffer[10];
	int		nItem = 0;		
	if(pRs2.Execute(&pCmd2))
	{
		CString sTypeName = "";						
		
		int number, amount;
		float  start_km, end_km;
		
		while(!pRs2.IsEOF()) {			

			CString  strStartKm = "", strEndKm = "";



			pRs2.GetFieldValue("number", number);			
			pRs2.GetFieldValue("start_km", start_km);			
			pRs2.GetFieldValue("end_km", end_km);			
			pRs2.GetFieldValue("amount", amount);

			strStartKm.Format("%.1f", start_km);
			strEndKm.Format("%.1f", end_km);

			m_List.InsertItem(nItem, ::GetStringFromLong(number));
			m_List.SetItemText(nItem, 1, strStartKm );
			m_List.SetItemText(nItem, 3, strEndKm );
			m_List.SetItemText(nItem, 4, ::GetStringFromLong(amount));

			if(m_bTruck) {		
				int col = 5;
				pRs2.GetFieldValue("amount_truck_add_1_4", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_2_5", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_3_5", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_5", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_5_5", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_8", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_11", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_14", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_15", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_18", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
				pRs2.GetFieldValue("amount_truck_add_25", amount); m_List.SetItemText(nItem, col++, ::GetStringFromLong(amount));
			}
		
			
			nItem++;
			pRs2.MoveNext();
		}
		
		pRs2.Close();	
	}

	for(int i = nItem; i < 20; i++)
		m_List.InsertItem(i, ltoa(i, buffer,10));
}

void CChargeDistanceType::OnCbnSelchangeTypeNameCombo()
{
	RefreshList();
}

void CChargeDistanceType::OnBnClickedRowAddButton()
{
	char buffer[10];
	int nItem = m_List.GetSelectionMark();
	if(nItem > 0)
		m_List.InsertItem(nItem, itoa(nItem,buffer,10) );
	else
		m_List.InsertItem(m_List.GetItemCount(),"");
		

	int nCount = m_List.GetItemCount() - 1;
	for(int i = 0; i < 20; i++)
	{
		if(i > nCount)
			m_List.InsertItem(i,itoa(i, buffer,10));
		else
			m_List.SetItemText(i,0,itoa(i,buffer,10));
	}

	
}

void CChargeDistanceType::OnBnClickedRowDeleteButton()
{
	UINT i, uSelectedCount = m_List.GetSelectedCount();
	int  nItem = -1;
	
	if(uSelectedCount > 0)
	{
		for (i = 0;i < uSelectedCount; i++)
		{
			nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
			if(nItem < 0) 
				break;

			
		}
		m_List.DeleteItem(nItem);		
	}
	else {
		int nItem = m_List.GetItemCount();
		m_List.DeleteItem(nItem - 1);
	}
	char buffer[10];
	int nCount = m_List.GetItemCount() - 1;
	for(int i = 0; i < 20; i++)
	{
		if(i > nCount)
			m_List.InsertItem(i,itoa(i, buffer,10));
		else
			m_List.SetItemText(i,0,itoa(i,buffer,10));
	}

	
	
	
}
BOOL CChargeDistanceType::CheckData()
{

	try
	{
		long nFrontStartKm, nFrontDestKm, nFrontAmount;
		nFrontStartKm = nFrontDestKm = nFrontAmount = 0;
		float fStartKm, fDestKm;
		long nAmount;
		fStartKm = fDestKm = nAmount = 0;

		CString strError, strStartKm, strDestKm, strAmount = "";

		if(m_List.GetItemCount() <= 0)
			throw("�����̶� �Է��ϼž� �մϴ�.");			

		for(int i = 0; i< m_List.GetItemCount(); i++)
		{		
			strStartKm = m_List.GetItemText(i,1);
			strDestKm  = m_List.GetItemText(i,3);
			strAmount = m_List.GetItemText(i,4);

			strStartKm.Replace(",","");
			strDestKm.Replace(",","");
			strAmount.Replace(",","");

			fStartKm = atof(strStartKm);
			fDestKm = atof(strDestKm);
			nAmount = atol(strAmount);

			if((fStartKm < 0 || fStartKm > 500)  || 
				(fDestKm < 0 || fDestKm > 500)  ||  
				!IsStringDigit(strAmount) )
			{
				strError.Format("%d��° �࿡ �����Ϳ� ���ڸ� �����ϼ���", i);
				throw(strError);
			}

			if(i == 0){
				if(fDestKm <= 0 || nAmount <= 0)
				{
					strError.Format("0��° �࿡ �����Ϳ� ���Ÿ��� ����� 0�̾�� �ȵ˴ϴ�.");
					throw(strError);
				}
			}
			else			
			{
				if(fStartKm <= 0 || fDestKm <= 0 || nAmount <= 0)
				{	
					if(m_List.GetItemText(i,1).GetLength() == 0 && 
						m_List.GetItemText(i,3).GetLength() == 0 &&
						m_List.GetItemText(i,4).GetLength() == 0)
						continue;
					else
					{
						strError.Format("%d �࿡ �����, ������, �ݾ��߿� �����Ͱ� 0���� �Ǿ��ֽ��ϴ�.\n\n "\
							"0���� �����Ͽ� �ּ���", i);
						throw(strError);					
					}
				}
				if(fStartKm >= fDestKm)
				{
					strError.Format("%d��°�� ������ Km�� ���۵Ǵ� Km ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}

				if(nFrontStartKm > fStartKm || nFrontDestKm >= fStartKm)
				{
					strError.Format("%d��°�� ����Km�� �����ຸ�� ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}

				if(nFrontDestKm >= fDestKm || nFrontDestKm > fStartKm)
				{
					strError.Format("%d��°�� ����Km�� �����ຸ�� ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}
			}

			nFrontStartKm = fStartKm;
			nFrontDestKm = fDestKm;
		}
		return TRUE;
	}
	catch(CString strMsg)
	{
		MessageBox(strMsg,"Ȯ��",MB_ICONINFORMATION);
		return FALSE;
	}
}

void CChargeDistanceType::OnBnClickedRegisterButton()
{
	try{
		int nItem = 0;
		float fStartKm = 0;
		float fDestKm = 0;
		int nAmount = 0;
		
		CString strTypeName ="";
		CString strError="";

		int index = m_cmbTypeName.GetCurSel();
		
		if(index < 0)
		{
			throw("��� Ÿ���� �������ֽðų� �űԷ� ����Ͽ� �ּ���");			
			return;
		}		

		if(!CheckData())  
			return;

		long nFrontStartKm, nFrontDestKm, nFrontAmount;
		nFrontStartKm = nFrontDestKm = nFrontAmount = 0;
		
		CString sStartKm, sDestKm, sAmount = "";
		for(int i = 0; i< m_List.GetItemCount(); i++)
		{		
			sStartKm = m_List.GetItemText(i,1);
			sDestKm	= m_List.GetItemText(i,3);
			sAmount = m_List.GetItemText(i,4);

			sStartKm.Replace(",","");
			sDestKm.Replace(",","");
			sAmount.Replace(",","");

			if(sStartKm.GetLength() == 0 || sDestKm.GetLength() == 0 || sAmount.GetLength() == 0)
			{
				CString str;
				str.Format("%d ����� ��ϵǾ����ϴ�.",i-1);
				MessageBox(str,"Ȯ��",MB_ICONINFORMATION);
				return;
			}

			fStartKm = atof(sStartKm);
			fDestKm = atof(sDestKm);
			//nStartKm = atoi(sStartKm);
			//nDestKm = atoi(sDestKm);
			nAmount = atoi(sAmount);		
		
			//CWaitCursor wait;
			CMkRecordset pRs2(m_pMkDb);
			CMkCommand pCmd2(m_pMkDb, "charge_distance_type_amount_insert");				
			pCmd2.AddParameter((int)m_cmbTypeName.GetItemData(index));	
			pCmd2.AddParameter( i);	
			pCmd2.AddParameter(sStartKm);	
			pCmd2.AddParameter(sDestKm);	
			pCmd2.AddParameter(nAmount);	
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,5)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,6)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,7)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,8)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,9)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,10)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,11)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,12)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,13)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,14)) : 0);
			pCmd2.AddParameter(m_bTruck ? atoi(m_List.GetItemText(i,15)) : 0);

			pCmd2.Execute();	
			
			nFrontStartKm = fStartKm;
			nFrontDestKm = fDestKm;
			nFrontAmount = nAmount;

		}

		MessageBox("��ϵǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
		
	}
	catch(CString strMessage){

		MessageBox(strMessage, "Ȯ��", MB_ICONINFORMATION);

	}
}

void CChargeDistanceType::OnBnClickedRowDeleteAllButton()
{
	CString strTypeName ="";
	CString strError="";

	m_cmbTypeName.GetWindowText(strTypeName);
	if(strTypeName.GetLength() <= 0)
	{
		strError = "��� Ÿ���� �������ֽðų� �űԷ� ����Ͽ� �ּ���";
		MessageBox(strError,"Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//CWaitCursor wait;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "delete_charge_distance_type_name_temp");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);	
	pCmd2.AddParameter(typeString, typeInput, strTypeName.GetLength(), strTypeName);	
	

	if(pCmd2.Execute())
	{
		MessageBox("��ü���� �����Ͽ����ϴ�.", "Ȯ��",MB_ICONINFORMATION);		
		RefreshList();
	}
	else
		MessageBox("�۾��� �����Ͽ����ϴ�.", "Ȯ��",MB_ICONINFORMATION);


}

void CChargeDistanceType::OnBnClickedCloseButton()
{
	OnCancel();
}

void CChargeDistanceType::OnCbnSelendcancelCompanyCombo2()
{	
	UpdateData(TRUE);
	if(m_cmbCompany.GetCount() > 1)
		m_nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	else
		m_nCompany = (long)m_cmbCompany.GetItemData(0);

	InputComboList();	
	m_cmbTypeName.SetCurSel(0);
	RefreshList();
}