// ChargenameNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargenameNewDlg.h"



// CChargeNameNewDlg 대화 상자입니다.

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


// CChargeNameNewDlg 메시지 처리기입니다.

void CChargeNameNewDlg::OnBnClickedOnokBtn()
{
	OnOK();
}

void CChargeNameNewDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
