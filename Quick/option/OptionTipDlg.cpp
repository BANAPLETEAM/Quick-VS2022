// OptionTipDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "OptionTipDlg.h"


// COptionTipDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COptionTipDlg, CDialog)

COptionTipDlg::COptionTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionTipDlg::IDD, pParent)
{

}

COptionTipDlg::~COptionTipDlg()
{
}

void COptionTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionTipDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &COptionTipDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COptionTipDlg �޽��� ó�����Դϴ�.

BOOL COptionTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void COptionTipDlg::OnBnClickedButton1()
{
	OnOK();
}
