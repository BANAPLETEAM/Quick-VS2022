// ChargeMemberDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeMemberDlg.h"


// CChargeMemberDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeMemberDlg, CMyDialog)

CChargeMemberDlg::CChargeMemberDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeMemberDlg::IDD, pParent)
{
	m_nReturn = 0;
	m_strEtc = "";
	m_strChargeName = "";
}

CChargeMemberDlg::~CChargeMemberDlg()
{
}

void CChargeMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARGE_NAME_EDIT, m_strChargeName);
	DDX_Control(pDX, IDC_CHARGE_NAME_EDIT, m_edtChargeName);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
}


BEGIN_MESSAGE_MAP(CChargeMemberDlg, CMyDialog)
	
	ON_BN_CLICKED(IDYES, &CChargeMemberDlg::OnBnClickedYes)
	ON_BN_CLICKED(IDNO, &CChargeMemberDlg::OnBnClickedNo)
	ON_BN_CLICKED(IDCANCEL, &CChargeMemberDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChargeMemberDlg �޽��� ó�����Դϴ�.



void CChargeMemberDlg::OnBnClickedYes()
{
	m_nReturn = IDYES;
	UpdateData();
	if(m_strChargeName.GetLength() <= 0)
	{
		MessageBox("����� �̸��� �Է��ϼ���");
		return;
	}
	OnOK();
}

void CChargeMemberDlg::OnBnClickedNo()
{
	m_nReturn = IDNO;
	OnOK();

}

void CChargeMemberDlg::OnBnClickedCancel()
{
	m_nReturn = IDCANCEL;
	OnOK();
}

BOOL CChargeMemberDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_edtChargeName.SetFocus();
	m_edtChargeName.SetSel(0, m_strChargeName.GetLength());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
