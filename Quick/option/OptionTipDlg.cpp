// OptionTipDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OptionTipDlg.h"


// COptionTipDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COptionTipDlg, CDialog)

COptionTipDlg::COptionTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionTipDlg::IDD, pParent)
{

}

COptionTipDlg::~COptionTipDlg()
{
}

void COptionTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionTipDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &COptionTipDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COptionTipDlg 메시지 처리기입니다.

BOOL COptionTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COptionTipDlg::OnBnClickedButton1()
{
	OnOK();
}
