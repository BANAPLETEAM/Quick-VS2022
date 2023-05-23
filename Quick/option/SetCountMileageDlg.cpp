// SetCountMileageDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SetCountMileageDlg.h"


// CSetCountMileageDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetCountMileageDlg, CMyDialog)

CSetCountMileageDlg::CSetCountMileageDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetCountMileageDlg::IDD, pParent)
{
	m_nCompany = 0;
}

CSetCountMileageDlg::~CSetCountMileageDlg()
{
}

void CSetCountMileageDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNT_EDIT, m_edtCount);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_INTER_COUNT_EDIT, m_edtInterCount);
	DDX_Control(pDX, IDC_INTER_CHARGE_EDIT, m_edtInterCharge);
}


BEGIN_MESSAGE_MAP(CSetCountMileageDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BUTTON, &CSetCountMileageDlg::OnBnClickedOkButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CSetCountMileageDlg::OnBnClickedCancelButton)
END_MESSAGE_MAP()


// CSetCountMileageDlg �޽��� ó�����Դϴ�.


BOOL CSetCountMileageDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	RefreshEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSetCountMileageDlg::RefreshEdit()
{
	CMkCommand pCmd(m_pMkDb, "select_count_mileage_option");
	pCmd.AddParameter(m_nCompany);
	CMkParameter *pCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pInterCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pInterCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pCmd.Execute()) return;

	long nCount; pCount->GetValue(nCount);
	long nCharge; pCharge->GetValue(nCharge);
	long nInterCount; pInterCount->GetValue(nInterCount);
	long nInterCharge; pInterCharge->GetValue(nInterCharge);

	m_edtCount.SetWindowText(LF->GetMyNumberFormat(nCount));
	m_edtCharge.SetWindowText(LF->GetMyNumberFormat(nCharge));
	m_edtInterCount.SetWindowText(LF->GetMyNumberFormat(nInterCount));
	m_edtInterCharge.SetWindowText(LF->GetMyNumberFormat(nInterCharge));
}

void CSetCountMileageDlg::OnBnClickedOkButton()
{
	CString sCount; m_edtCount.GetWindowText(sCount);
	CString sCharge; m_edtCharge.GetWindowText(sCharge);
	CString sInterCount; m_edtInterCount.GetWindowText(sInterCount);
	CString sInterCharge; m_edtInterCharge.GetWindowText(sInterCharge);

	sCount.Replace(",", "");
	sCharge.Replace(",", "");
	sInterCount.Replace(",", "");
	sInterCharge.Replace(",", "");

	if(
		(atoi(sCount) <= 0 || atoi(sCharge) <= 0 ) &&
		(atoi(sInterCount) <= 0 || atoi(sInterCharge) <= 0)
		)
	{
		MessageBox("0�� Ȥ�� 0���� �Է� �ϽǼ� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
/*
	if(atoi(sCount) <= 0 || atoi(sCharge) <= 0 ||
		atoi(sInterCount) <= 0 || atoi(sInterCharge) <= 0)
	{
		MessageBox("0�� Ȥ�� 0���� �Է� �ϽǼ� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
*/
	CMkCommand pCmd(m_pMkDb, "update_count_mileage_option");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(atoi(sCount));
	pCmd.AddParameter(atoi(sCharge));
	pCmd.AddParameter(atoi(sInterCount));
	pCmd.AddParameter(atoi(sInterCharge));

	if(pCmd.Execute())
		OnOK();
}

void CSetCountMileageDlg::OnBnClickedCancelButton()
{
	OnCancel();
}
