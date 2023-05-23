// ChargeForRiderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeForRiderDlg.h"


// CChargeForRiderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeForRiderDlg, CMyDialog)

CChargeForRiderDlg::CChargeForRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeForRiderDlg::IDD, pParent)
	, m_strCompany(_T(""))
{

}

CChargeForRiderDlg::~CChargeForRiderDlg()
{
}

void CChargeForRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);

	DDX_Text(pDX, IDC_COMPANY_EDIT, m_strCompany);
	DDX_Text(pDX, IDC_RNO_EDIT, m_strRNo);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
}


BEGIN_MESSAGE_MAP(CChargeForRiderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CHARGE_FOR_BTN, &CChargeForRiderDlg::OnBnClickedChargeForBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChargeForRiderDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CChargeForRiderDlg 메시지 처리기입니다.

void CChargeForRiderDlg::OnBnClickedChargeForBtn()
{
	long nCharge = LF->GetLongFromEdit(&m_edtCharge);
	CString strEtc = LF->GetStringFromEdit(&m_edtEtc);

	if(nCharge < 1000)
	{
		MessageBox("1000원 이상 청구하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(nCharge >= 300000)
	{
		MessageBox("30만원 이상 청구 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(strEtc.IsEmpty())
	{
		MessageBox("사유를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	m_nCharge = nCharge;
	m_strEtc = strEtc;

	CMyDialog::OnOK();
}

void CChargeForRiderDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CChargeForRiderDlg::OnOK()
{
	OnBnClickedChargeForBtn();
	
}
