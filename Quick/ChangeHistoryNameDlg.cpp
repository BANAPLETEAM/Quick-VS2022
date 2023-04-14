// ChangeHistoryNameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChangeHistoryNameDlg.h"


// CChangeHistoryNameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChangeHistoryNameDlg, CMyDialog)

CChangeHistoryNameDlg::CChangeHistoryNameDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChangeHistoryNameDlg::IDD, pParent)
{
	m_sChargeName = "";
	m_sChargeEtc = "";

}

CChangeHistoryNameDlg::~CChangeHistoryNameDlg()
{
}

void CChangeHistoryNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADD_CHARGE_EDIT,m_sChargeName );
	DDX_Text(pDX, IDC_ETC_EDIT,m_sChargeEtc );
}


BEGIN_MESSAGE_MAP(CChangeHistoryNameDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CChangeHistoryNameDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChangeHistoryNameDlg::OnBnClickedCancelBtn)
	
END_MESSAGE_MAP()


BOOL CChangeHistoryNameDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	return TRUE;
}


void CChangeHistoryNameDlg::OnBnClickedOkBtn()
{
	UpdateData();
	if(m_sChargeName.GetLength() <= 0)
	{
		MessageBox("요금제에 이름을 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CChangeHistoryNameDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
