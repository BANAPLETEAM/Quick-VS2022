// ChargeChangeHelpDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeChangeHelpDlg.h"


// CChargeChangeHelpDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeChangeHelpDlg, CMyDialog)

CChargeChangeHelpDlg::CChargeChangeHelpDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeChangeHelpDlg::IDD, pParent)
{

}

CChargeChangeHelpDlg::~CChargeChangeHelpDlg()
{
}

void CChargeChangeHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChargeChangeHelpDlg, CMyDialog)
		ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
END_MESSAGE_MAP()


void CChargeChangeHelpDlg::OnBnClickedOkBtn()
{
	OnOK();
}


BOOL CChargeChangeHelpDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}