// HelpGroupReportDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "HelpGroupReportDlg.h"



// CHelpGroupReportDlg ��ȭ �����Դϴ�.

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


// CHelpGroupReportDlg �޽��� ó�����Դϴ�.

void CHelpGroupReportDlg::OnBnClickedButton1()
{
	OnCancel();
}
