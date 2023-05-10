// ShareOrderAllocate.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareOrderAllocate.h"



// CShareOrderAllocate ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareOrderAllocate, CMyDialog)
CShareOrderAllocate::CShareOrderAllocate(CWnd* pParent /*=NULL*/)
: CMyDialog(CShareOrderAllocate::IDD, pParent)
, m_nRider(0)
, m_sDetailEdit(_T(""))
, m_sRiderName(_T(""))
{
	m_nID = -1;
	m_ModifyButtonEnable = FALSE;
	m_nRiderCompany = -1;
}

CShareOrderAllocate::~CShareOrderAllocate()
{
}

void CShareOrderAllocate::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
	DDX_Text(pDX, IDC_RIDER_EDIT, m_nRider);	
	DDX_Text(pDX, IDC_DETAIL_EDIT, m_sDetailEdit);
	DDX_Text(pDX, IDC_EDIT3, m_sRiderName);
	DDX_Control(pDX, IDC_BUTTON1, m_btnModify);
	DDX_Control(pDX, IDC_BUTTON_APPLY_ALL, m_btnApplyAll);	
	DDX_Control(pDX, IDC_RIDER_EDIT, m_edtRiderNO);
	DDX_Control(pDX, IDC_DETAIL_EDIT, m_DetailEdit);
}


BEGIN_MESSAGE_MAP(CShareOrderAllocate, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnBnClickedTestButton)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_DETAIL_EDIT, OnEnChangeDetailEdit)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_ALL, OnBnClickedButtonApplyAll)
END_MESSAGE_MAP()


// CShareOrderAllocate �޽��� ó�����Դϴ�.


void CShareOrderAllocate::InitControl()
{
	for(int i=0; i<m_cmbCompany.GetCount(); i++)
		m_cmbCompany.DeleteString(0);


	int nItem = -1;
	MAP_SHARED_COMPANY::iterator it;
	int n = 0;

	for(it = m_ci.GetShareMapBegin(); it != m_ci.GetShareMapEnd(); it++)
	{
		m_cmbCompany.InsertString(n, (*it).second.strBranchName);
		m_cmbCompany.SetItemData(n, (*it).second.nCompany);

		TRACE("n = %d\n", (*it).second.nCompany);
		if((*it).second.nCompany == m_nRiderCompany)
			nItem = n;

		n++;
	}	

	if(nItem >= 0)
	{
		m_cmbCompany.SetCurSel(nItem);
		VerifyRider(TRUE);
	}


	/*
	char buffer[20];
	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "select_share_company2_2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);

	if(!pRs.Execute(&pCmd))
	return;

	int nItem = -1;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
	long nID;
	CString	sBranchName;

	pRs.GetFieldValue("nID", nID);
	pRs.GetFieldValue("sBranchName", sBranchName);

	m_cmbCompany.InsertString(i,sBranchName);
	m_cmbCompany.SetItemData(i,nID);

	if(nID == m_nRiderCompany)
	{
	nItem = i;
	}

	pRs.MoveNext();
	}	

	if(nItem >= 0)
	{
	m_cmbCompany.SetCurSel(nItem);
	VerifyRider(TRUE);
	}
	*/
}


void CShareOrderAllocate::NewUser()
{


}
void CShareOrderAllocate::ModifyUser()
{
	m_cmbCompany.EnableWindow(FALSE);
	m_edtRiderNO.EnableWindow(FALSE);

	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "select_share_order_modify_1");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nID);

	if(!pRs.Execute(&pCmd))
		return;


	long nID,nCompany,nRiderCompany, nRNo;
	nID = nCompany = nRiderCompany = nRNo = 0;

	CString		sRName,sMemo;

	pRs.GetFieldValue("nID", nID);
	pRs.GetFieldValue("nCompany", nCompany);
	pRs.GetFieldValue("nRiderCompany", nRiderCompany);
	pRs.GetFieldValue("nRNo", nRNo);
	pRs.GetFieldValue("sRName", sRName);
	pRs.GetFieldValue("sMemo", sMemo);

	UpdateData();
	m_nRider = nRNo;
	m_sDetailEdit = sMemo;
	m_sRiderName = sRName;
	UpdateData(FALSE);

	for(int i=0; i< m_cmbCompany.GetCount(); i++)
	{
		if( m_cmbCompany.GetItemData(i) == nRiderCompany)
		{
			m_cmbCompany.SetCurSel(i);
			break;
		}
	}
}


void CShareOrderAllocate::ModifyUserOk()
{
	try
	{
		if(m_nID <= 0)
			throw "������ �ٽ� ���ּ���";


		long nRiderCompany = 0;
		nRiderCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
		if(nRiderCompany <= 0 )
			throw "���缱���� ���ּ���";

		if(m_nRider <= 0 )
			throw "��縦 �ٽñ������ּ���";

		if(nRiderCompany == m_nCompany)
			throw "�ڱ�Ҽ� ���� ����Ͻ� �� �����ϴ�.";


		int nParameter = -1; 
		UpdateData(TRUE);
		//CWaitCursor wait;
		CMkCommand pCmd(m_pMkDb, "update_share_order_rider_register");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRiderCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRider );
		pCmd.AddParameter(typeString, typeInput, m_sRiderName.GetLength(), m_sRiderName  );
		pCmd.AddParameter(typeString, typeInput, m_sDetailEdit.GetLength(), m_sDetailEdit );
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode );	
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
		CMkParameter *parReturn = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(!pRs.Execute(&pCmd))
			return;

		parReturn->GetValue(nParameter);
		if(nParameter <= 0)
			throw "��ȸ�Ͻ� �������δ� ��ϵ��� �ʾҽ��ϴ�. �ٽõ�� ���ּ���";
		else if(nParameter = 10)
		{
			MessageBox("��ȸ�Ͻ� �������� �����Ǿ����ϴ�. ","����̸� Ȯ��",MB_ICONINFORMATION);
			OnOK();
		}
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��",MB_ICONINFORMATION);
		return;
	}



}
void CShareOrderAllocate::NewUserOk(BOOL bAll)
{
	try
	{
		long nRiderCompany = 0;
		nRiderCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
		if(nRiderCompany <= 0 )
			throw "���缱���� ���ּ���";

		if(m_nRider <= 0 )
			throw "����ȣ�� �ٽñ������ּ���";

		if(nRiderCompany == this->m_nCompany)
			throw "�ڱ�Ҽ� ���� ����Ͻ� �� �����ϴ�.";

		BOOL bIntegrated = FALSE;
		if(m_ba.GetCount() > 1)  //�����̸�
			bIntegrated = TRUE;

		int nParameter = -1; 
		UpdateData(TRUE);
		//CWaitCursor wait;
		CMkCommand pCmd(m_pMkDb, "insert_share_order_rider_register_1");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bAll );
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRiderCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRider );
		pCmd.AddParameter(typeString, typeInput, m_sRiderName.GetLength(), m_sRiderName);
		pCmd.AddParameter(typeString, typeInput, m_sDetailEdit.GetLength(), m_sDetailEdit);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode );	
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);

		CMkParameter *parReturn = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(!pRs.Execute(&pCmd))
			return;

		parReturn->GetValue(nParameter);
		if(nParameter <= 0)
			throw "��ȸ�Ͻ� �������δ� ��ϵ��� �ʾҽ��ϴ�. �ٽõ�� ���ּ���";
		else if(nParameter == 10)
			throw "��ȸ�Ͻ� ������ ������ ��ϵǾ��ֽ��ϴ�. ";
		else
		{
			MessageBox("��ȸ�Ͻ� �������� ��ϵǾ����ϴ�. ","����̸� Ȯ��",MB_ICONINFORMATION);
			OnOK();
		}
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��",MB_ICONINFORMATION);
		return;
	}

}
void CShareOrderAllocate::OnBnClickedButton1()
{
	BOOL bAll = FALSE;
	if(m_nMode) // 1�ű� 0 ����
	{
		NewUserOk(bAll);
	}
	else
		ModifyUserOk();
}
BOOL CShareOrderAllocate::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	InitControl();
	m_btnApplyAll.EnableWindow(GetCurBranchInfo()->bIntegrated);
	if(m_nMode) // 1�ű� 0 ����
	{
		NewUser();
	}
	else
	{
		m_btnModify.EnableWindow(m_ModifyButtonEnable);
		ModifyUser();
	}
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CShareOrderAllocate::OnBnClickedButton7()
{
	OnCancel();
}

void CShareOrderAllocate::OnBnClickedTestButton()
{
	VerifyRider();
}


void CShareOrderAllocate::VerifyRider(BOOL bNoMsg)
{
	UpdateData();


	long nCompany = 0;
	nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	if(nCompany <= 0 )
	{
		MessageBox("���缱���� ���ּ���", "���缱��", MB_ICONINFORMATION);
		return;
	}
	if(m_nRider <= 0 )
	{
		MessageBox("��縦 �ٽñ������ּ���", "��缱��", MB_ICONINFORMATION);
		return;
	}

	int nReturn;
	CString strRiderName;

	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "select_share_order_allocate_rider_test");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRider);
	CMkParameter *parReturn = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parReturnName = pCmd.AddParameter(typeString, typeOutput, 20, CString(""));

	if(!pRs.Execute(&pCmd))
		return;

	parReturn->GetValue(nReturn);
	parReturnName->GetValue(strRiderName);
	if(nReturn)
	{
		if(!bNoMsg)
			MessageBox(strRiderName + "�����Դϴ�.","����̸� Ȯ��",MB_ICONINFORMATION);		

		m_sRiderName = strRiderName;
		UpdateData(FALSE);
	}
	else
	{
		if(!bNoMsg)
			MessageBox("��ȸ�Ͻ� ��簡 ��ϵǾ� ���� �ʽ��ϴ�. �ٽ�Ȯ�� ���ּ���!","����̸� Ȯ��",MB_ICONINFORMATION);
	}
}



HBRUSH CShareOrderAllocate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_DETAIL_EDIT) {
		pDC->SetTextColor(RGB(255, 0, 0));
	}	

	return hbr;
}


void CShareOrderAllocate::OnEnChangeDetailEdit()
{
	if(m_DetailEdit.GetWindowTextLength() > 255)
	{
		CString strDetail;
		m_DetailEdit.GetWindowText(strDetail);
		m_DetailEdit.SetWindowText(strDetail.Left(strDetail.GetLength() - 1));
		MessageBox("255�� ���Ϸ� �Է��Ͻñ� �ٶ��ϴ�.", "���� �ʰ�", MB_ICONINFORMATION);
	}
}

void CShareOrderAllocate::OnBnClickedButtonApplyAll()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bAll = TRUE;
	if(m_nMode) // 1�ű� 0 ����
	{
		NewUserOk(bAll);
	}
	else
		NewUserOk(bAll);
}
