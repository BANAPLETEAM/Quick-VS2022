// InsuranceInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "InsuranceInfoDlg.h"


// CInsuranceInfoDlg ��ȭ �����Դϴ�.

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


// CInsuranceInfoDlg �޽��� ó�����Դϴ�.

void CInsuranceInfoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CInsuranceInfoDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
