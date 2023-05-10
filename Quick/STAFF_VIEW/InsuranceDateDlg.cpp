// InsuranceDateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "InsuranceDateDlg.h"


// CInsuranceDateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInsuranceDateDlg, CMyDialog)

CInsuranceDateDlg::CInsuranceDateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CInsuranceDateDlg::IDD, pParent)
	, m_dtStart(COleDateTime::GetCurrentTime())
	, m_dtEnd(COleDateTime::GetCurrentTime())
{

}

CInsuranceDateDlg::~CInsuranceDateDlg()
{
}

void CInsuranceDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_1, m_dtStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_2, m_dtEnd);
}


BEGIN_MESSAGE_MAP(CInsuranceDateDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CInsuranceDateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInsuranceDateDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInsuranceDateDlg 메시지 처리기입니다.

void CInsuranceDateDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CInsuranceDateDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
