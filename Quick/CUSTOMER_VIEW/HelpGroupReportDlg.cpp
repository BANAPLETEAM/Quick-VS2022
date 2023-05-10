// HelpGroupReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "HelpGroupReportDlg.h"



// CHelpGroupReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHelpGroupReportDlg, CMyDialog)
CHelpGroupReportDlg::CHelpGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CHelpGroupReportDlg::IDD, pParent)
{
}

CHelpGroupReportDlg::~CHelpGroupReportDlg()
{
}

void CHelpGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CHelpGroupReportDlg 메시지 처리기입니다.

void CHelpGroupReportDlg::OnBnClickedButton1()
{
	OnCancel();
}
