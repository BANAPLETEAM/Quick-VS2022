// ChargeChangeHelpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeChangeHelpDlg.h"


// CChargeChangeHelpDlg 대화 상자입니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}