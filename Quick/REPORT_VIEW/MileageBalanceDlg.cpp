// MileageBalanceDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "MileageBalanceDlg.h"
#include ".\mileagebalancedlg.h"


// CMileageBalanceDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMileageBalanceDlg, CMyDialog)
CMileageBalanceDlg::CMileageBalanceDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMileageBalanceDlg::IDD, pParent)
	, m_sCharge(_T(""))
	, m_sEtc(_T(""))
	, m_nType(0)
{
	m_nMileageBalance = 0;
	m_nCNo = 0;
}

CMileageBalanceDlg::~CMileageBalanceDlg()
{
}

void CMileageBalanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEFORE_STATIC, m_stcBefore);
	DDX_Control(pDX, IDC_AFTER_STATIC, m_stcAfter);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Text(pDX, IDC_CHARGE_EDIT, m_sCharge);
	DDX_Control(pDX, IDC_COMBO1, m_cmbType);
	DDX_Text(pDX, IDC_ETC_EDIT, m_sEtc);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nType);
}


BEGIN_MESSAGE_MAP(CMileageBalanceDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_EN_CHANGE(IDC_CHARGE_EDIT, OnEnChangeChargeEdit)
END_MESSAGE_MAP()


// CMileageBalanceDlg �޽��� ó�����Դϴ�.

void CMileageBalanceDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	if(atoi(m_sCharge) <= 0)
	{
        MessageBox("�����ݾ��� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	/*
	long nCharge = atol(m_sCharge);
	if(nCharge < 0 || nCharge > 1000000)
	{
		MessageBox("�ݾ��� 0�������̰ų� 1,000,000 �̻��Դϴ�. �ݾ��� �ٽ� �����Ͽ��ּ���" , 
			"Ȯ��", MB_ICONINFORMATION);
		OnCancel();
		return;
	}
	*/
	m_nType = m_cmbType.GetCurSel();
	OnOK();
}

void CMileageBalanceDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CMileageBalanceDlg::OnEnChangeChargeEdit()
{
	CString sBalance; m_edtCharge.GetWindowText(sBalance);
	long nBalance = atoi(sBalance);

	if(m_cmbType.GetCurSel() != 0)
		nBalance = nBalance * -1;

	m_stcAfter.SetWindowText(::GetMyNumberFormat(m_nMileageBalance + nBalance) + "��");
}

BOOL CMileageBalanceDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
 
	m_cmbType.SetCurSel(0);
	

	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_get_mile");	
	pCmd.AddParameter(m_nCNo);
	CMkParameter *pParMileage = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pRs.Execute(&pCmd))
		MessageBox("���ͳݿ����� ���еǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
	{
		long nMileageBalance = 0;
		pParMileage->GetValue(nMileageBalance);
		m_nMileageBalance = nMileageBalance;
		m_stcBefore.SetWindowText(::GetMyNumberFormat(nMileageBalance) + "��");
		m_stcAfter.SetWindowText(::GetMyNumberFormat(nMileageBalance) + "��");
		//m_stcBefore.SetWindowText(GetMyNumberFormat(nMileageBalance));
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
