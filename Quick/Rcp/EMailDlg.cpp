// BillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "EMailDlg.h"


// CEMailDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEMailDlg, CMyDialog)
CEMailDlg::CEMailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CEMailDlg::IDD, pParent)
{
	m_strEMail = "";
}

CEMailDlg::~CEMailDlg()
{
}

void CEMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
}


BEGIN_MESSAGE_MAP(CEMailDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CEMailDlg 메시지 처리기입니다.

BOOL CEMailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEMailDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_strEMail.IsEmpty() ||
		m_strEMail.Find("@") == 0 ||
		m_strEMail.Find(".") == 0)
	{
		MessageBox("이메일이 형식에 맞지 않습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CEMailDlg::OnBnClickedCancel()
{
	OnCancel();
}