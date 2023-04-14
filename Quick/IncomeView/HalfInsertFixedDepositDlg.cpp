// HalfInsertFixedDepositDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "HalfInsertFixedDepositDlg.h"



// CHalfInsertFixedDepositDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHalfInsertFixedDepositDlg, CMyDialog)
CHalfInsertFixedDepositDlg::CHalfInsertFixedDepositDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CHalfInsertFixedDepositDlg::IDD, pParent)
	, m_nCharge(0)
{
}

CHalfInsertFixedDepositDlg::~CHalfInsertFixedDepositDlg()
{
}

void CHalfInsertFixedDepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARGE_EDT, m_nCharge);
}


BEGIN_MESSAGE_MAP(CHalfInsertFixedDepositDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CHalfInsertFixedDepositDlg 메시지 처리기입니다.

void CHalfInsertFixedDepositDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);
	OnOK();
}

void CHalfInsertFixedDepositDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
