// ChargeSectionTypeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeSectionTypeDlg.h"



// CChargeSectionTypeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeSectionTypeDlg, CMyDialog)
CChargeSectionTypeDlg::CChargeSectionTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeSectionTypeDlg::IDD, pParent)
{
	m_strTitle = "���";
	m_strValueName = "���";
	m_nValueType = 0;
	m_nInitClass = 0;
	m_nCompany = 0;
}

CChargeSectionTypeDlg::~CChargeSectionTypeDlg()
{
}

void CChargeSectionTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbTypeName);

	
	DDX_Control(pDX, IDC_BRANCH_STATIC, m_stcBranch);
	//DDX_Control(pDX, IDC_CARTYPE_COMBO, m_cmbCarType);
	//DDX_Control(pDX, IDC_COUNT_DATE, m_dtpCountType);
	//DDX_Control(pDX, IDC_COUNTDATE_STATIC, m_stcCountType);
	//DDX_Control(pDX, IDC_CARTYPE_STATIC, m_stcCount);
}


BEGIN_MESSAGE_MAP(CChargeSectionTypeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ADD_ROW_BTN, OnBnClickedAddRowBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
	ON_BN_CLICKED(IDCANCEL, &CChargeSectionTypeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChargeSectionTypeDlg �޽��� ó�����Դϴ�.


BOOL CChargeSectionTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_nValueType == CST_DISCOUNT)
	{
		m_strTitle = "��ī��Ʈ";
		m_strValueName = "���ξ�";
	}
	else if(m_nValueType == CST_COUPON)
	{
		m_strTitle = "����";
		m_strValueName = "������";
	}
	else if(m_nValueType == CST_MILEAGE)
	{
		m_strTitle = "���ϸ���";
		m_strValueName = "���ϸ���";
	}
	else if(m_nValueType == CST_BATCH_MILEAGE)
	{
		m_strTitle = "�ϰ� ���ϸ���";
		m_strValueName = "�ϰ� ���ϸ���";

		m_cmbTypeName.ResetContent();
		
		m_cmbTypeName.InsertString(0,"����,������");
		m_cmbTypeName.InsertString(1,"�ٸ�,��");
		m_cmbTypeName.InsertString(2,"��");
		m_cmbTypeName.InsertString(3,"Ʈ��");
		
	}
	/*else if(m_nValueType == CST_BATCH_MILEAGE_COUNT) 
	{
		m_strTitle = "�ϰ� ���ϸ���(���Ƚ��)";
		m_strValueName = "�ϰ� ���ϸ���(���Ƚ��)";		

		m_stcCount.ShowWindow(SW_SHOW);
		m_stcCountType.ShowWindow(SW_SHOW);

		m_cmbCarType.ShowWindow(SW_SHOW);
		m_dtpCountType.ShowWindow(SW_SHOW);


		m_cmbTypeName.InsertString(4,"��ü����");
		m_cmbTypeName.SetCurSel(4);
		
	}*/
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_List.ModifyStyle(NULL, LVS_EDITLABELS | LVS_REPORT);
	m_List.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0, "����", LVCFMT_CENTER, 50);
	if(m_nValueType == CST_BATCH_MILEAGE_COUNT)
		m_List.InsertColumn(1, "����Ƚ��",LVCFMT_CENTER, 70);
	else
		m_List.InsertColumn(1, "���ۿ��",LVCFMT_CENTER, 70);
	m_List.InsertColumn(2, "~",LVCFMT_CENTER, 30);
	if(m_nValueType == CST_BATCH_MILEAGE_COUNT)
		m_List.InsertColumn(3, "��Ƚ��",LVCFMT_CENTER, 70);
	else
		m_List.InsertColumn(3, "�����",LVCFMT_CENTER, 70);
	m_List.InsertColumn(4, m_strValueName+ "(100�̸�%)",LVCFMT_RIGHT, 140);		

	m_List.SetDisableCol(0);	
	m_List.SetDisableCol(2);

	SetWindowText(m_strTitle + " Ÿ�Լ���â");

	m_cmbTypeName.SetCurSel(m_nInitClass);

	m_stcBranch.SetWindowText(m_ci.GetBranchName(m_nCompany));
	
	if(RefreshList() == FALSE)
		OnCancel();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CChargeSectionTypeDlg::RefreshList()
{
	m_List.DeleteAllItems();

	char buffer[10];
	int nItem = 0;

	if(m_nCompany <= 0 )
	{
		MessageBox("ȸ�缳���� �ùٸ��� �ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_section_type3");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nValueType);
	pCmd.AddParameter(m_cmbTypeName.GetCurSel());	
	
	if(pRs.Execute(&pCmd))
	{
		while(!pRs.IsEOF())
		{
			long nNum, nStart, nEnd, nAmount;

			pRs.GetFieldValue("nNum", nNum);
			pRs.GetFieldValue("nStartValue", nStart);
			pRs.GetFieldValue("nEndValue", nEnd);
			pRs.GetFieldValue("nAmount", nAmount);
			
			m_List.InsertItem(nItem, ltoa(nNum, buffer, 10));
			m_List.SetItemText(nItem, 1, ltoa(nStart, buffer, 10));
			m_List.SetItemText(nItem, 3, ltoa(nEnd, buffer, 10));
			m_List.SetItemText(nItem, 4, ltoa(nAmount, buffer, 10));

			nItem++;
			pRs.MoveNext();
		}
	}

	for(int i = nItem; i < 20; i++)
		m_List.InsertItem(i, ltoa(i, buffer,10));

	m_List.ResetDirtyFlag();

	return TRUE;
}


BOOL CChargeSectionTypeDlg::CheckData()
{
	try
	{
		long nFrontStartKm, nFrontDestKm, nFrontAmount;
		nFrontStartKm = nFrontDestKm = nFrontAmount = 0;
		long nStartKm, nDestKm, nAmount;
		nStartKm = nDestKm = nAmount = 0;


		CString strError, sStartKm, sDestKm, sAmount = "", sTempAmount = "";

		if(m_List.GetItemCount() <= 0)
			throw("�ּ� ���� �̻� �Է¹ٶ��ϴ�.");


		for(int i = 0; i< m_List.GetItemCount(); i++)
		{		
			sStartKm = m_List.GetItemText(i,1);
			sDestKm  = m_List.GetItemText(i,3);
			sAmount = m_List.GetItemText(i,4);

			sStartKm.Replace(",","");
			sDestKm.Replace(",","");
			sAmount.Replace(",","");


			nStartKm = atoi(sStartKm);
			nDestKm = atoi(sDestKm);
			nAmount = atoi(sAmount);

			if(nDestKm == 0)
				return TRUE;

			sTempAmount = sAmount;
			sTempAmount.Replace("-", "");
			if(!IsStringDigit(sStartKm) ||!IsStringDigit(sDestKm)||!IsStringDigit(sTempAmount) )
			{
				strError.Format("%d��° ���� �����Ϳ� ���ڸ� �����ϼ���", i);
				throw(strError);
			}


			if(i == 0){
				if( nDestKm <= 0 )
				{
					strError.Format("0��° ���� �����Ϳ� ����ݹ� ���� 0 �̸� �ȵ˴ϴ�.");
					throw(strError);
				}
			}
			else			
			{

				if(nStartKm <= 0 || nDestKm <= 0 )
				{	
					if(m_List.GetItemText(i,1).GetLength() == 0 && 
						m_List.GetItemText(i,3).GetLength() == 0 &&
						m_List.GetItemText(i,4).GetLength() == 0)
						continue;
					else
					{
						strError.Format("%d �࿡ ���ۿ��, �����, ���߿� �����Ͱ� 0���� �Ǿ��ֽ��ϴ�.\n\n "\
							"0���� �����Ͽ� �ּ���", i);
						throw(strError);					
					}
				}
				if(nStartKm >= nDestKm)
				{
					strError.Format("%d��°�� ������ ����� ���۵Ǵ� ��ݰ� ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}

				if(nFrontStartKm > nStartKm || nFrontDestKm >= nStartKm)
				{
					strError.Format("%d��°�� ���ۿ���� �����ຸ�� ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}

				if(nFrontDestKm >= nDestKm || nFrontDestKm > nStartKm)
				{
					strError.Format("%d��°�� ��������� �����ຸ�� ���ų� �۽��ϴ�.", i);
					throw(strError);					
				}
			}

			nFrontStartKm = nStartKm;
			nFrontDestKm = nDestKm;
		}
		return TRUE;
	}
	catch(CString strMsg)
	{
		MessageBox(strMsg,"Ȯ��",MB_ICONINFORMATION);
		return FALSE;
	}
}


BOOL CChargeSectionTypeDlg::SaveData()
{
	UpdateData();
	if(!CheckData())  
		return FALSE;

	if(m_nCompany <= 0 )
	{
		MessageBox("ȸ�缳���� �ùٸ��� �ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		CString strStart = m_List.GetItemText(i, 1);
		CString strEnd = m_List.GetItemText(i, 3);
		CString strAmount = m_List.GetItemText(i, 4);

		strStart.Replace(",", "");
		strEnd.Replace(",", "");
		strAmount.Replace(",", "");

		if(atol(strEnd) == 0)
			break;

		CMkCommand pCmd(m_pMkDb, "update_charge_section_type4");
		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(m_nValueType);
		pCmd.AddParameter(m_cmbTypeName.GetCurSel());
		pCmd.AddParameter(i);
		pCmd.AddParameter(atol(strStart));
		pCmd.AddParameter(atol(strEnd));
		pCmd.AddParameter(atol(strAmount));
		

		if(!pCmd.Execute())
		{
			MessageBox("������Ʈ �������� ������ �߻��߽��ϴ�.\n��õ� �ٶ��ϴ�.\n", 
				"Ȯ��", MB_ICONEXCLAMATION);
			return FALSE;
		}
	}

	MessageBox("���������� ��ϵǾ����ϴ�. �����ڸ������� ������Ʈ �Ǿ�����\n\r�ٸ������ڴ� ��α����� �ؾ� �մϴ�. ", "Ȯ��", MB_ICONINFORMATION);
	LU->MakeChargeSectionType();
	m_List.ResetDirtyFlag();
	return TRUE;
}


void CChargeSectionTypeDlg::OnBnClickedAddRowBtn()
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

void CChargeSectionTypeDlg::OnOK()
{
	SaveData();
}

void CChargeSectionTypeDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CChargeSectionTypeDlg::OnCbnSelchangeTypeCombo()
{
	if(m_List.GetDirtyFlag())
	{
		if(IDYES == MessageBox("���� Ÿ�Կ� ���泻���� �����Ͻðڽ��ϱ�?", "���� ��������", MB_YESNO))
		{
			if(!SaveData())
				return;
		}
	}

	RefreshList();
}

void CChargeSectionTypeDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
