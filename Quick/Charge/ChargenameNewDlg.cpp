// ChargenameNewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargenameNewDlg.h"



// CChargeNameNewDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeNameNewDlg, CMyDialog)
CChargeNameNewDlg::CChargeNameNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeNameNewDlg::IDD, pParent)
	, m_strChargeName(_T(""))
	, m_strChargeEtc(_T(""))
{
}

CChargeNameNewDlg::~CChargeNameNewDlg()
{
}

void CChargeNameNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARGE_NAME_EDIT, m_strChargeName);
	DDX_Text(pDX, IDC_CHARGE_ETC_EDIT, m_strChargeEtc);
}


BEGIN_MESSAGE_MAP(CChargeNameNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ONOK_BTN, OnBnClickedOnokBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CChargeNameNewDlg �޽��� ó�����Դϴ�.

void CChargeNameNewDlg::OnBnClickedOnokBtn()
{
	OnOK();
}

void CChargeNameNewDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
