// InsuranceInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "InsuranceInfoDlg.h"


// CInsuranceInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInsuranceInfoDlg, CMyDialog)

CInsuranceInfoDlg::CInsuranceInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CInsuranceInfoDlg::IDD, pParent)
	, m_sInsNumber(_T(""))
{

}

CInsuranceInfoDlg::~CInsuranceInfoDlg()
{
}

void CInsuranceInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INSURANCE_COMPANY, m_sInsCompany);
	DDX_Text(pDX, IDC_INSURANCE_NUMBER, m_sInsNumber);
}


BEGIN_MESSAGE_MAP(CInsuranceInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CInsuranceInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInsuranceInfoDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInsuranceInfoDlg 메시지 처리기입니다.

void CInsuranceInfoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CInsuranceInfoDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
