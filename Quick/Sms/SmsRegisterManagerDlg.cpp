// SmsRegisterManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsRegisterManagerDlg.h"


// CSmsRegisterManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsRegisterManagerDlg, CMyDialog)

CSmsRegisterManagerDlg::CSmsRegisterManagerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsRegisterManagerDlg::IDD, pParent)
, m_strName(_T(""))
{

}

CSmsRegisterManagerDlg::~CSmsRegisterManagerDlg()
{
}

void CSmsRegisterManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_JOBTITLE_EDIT, m_strJobTitle);
	DDX_Text(pDX, IDC_CONTECT_NUMBER_EDIT, m_strNumber);
}


BEGIN_MESSAGE_MAP(CSmsRegisterManagerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CSmsRegisterManagerDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CSmsRegisterManagerDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CSmsRegisterManagerDlg 메시지 처리기입니다.


void CSmsRegisterManagerDlg::OnBnClickedOkBtn()
{
	OnOK();
}

void CSmsRegisterManagerDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
