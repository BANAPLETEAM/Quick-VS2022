// OtherAccountDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "OtherAccountDlg.h"


// COtherAccountDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COtherAccountDlg, CMyDialog)
COtherAccountDlg::COtherAccountDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COtherAccountDlg::IDD, pParent)
{
}

COtherAccountDlg::~COtherAccountDlg()
{
}

void COtherAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ACCOUNT_EDIT, m_strAccount);
}


BEGIN_MESSAGE_MAP(COtherAccountDlg, CMyDialog)
END_MESSAGE_MAP()


// COtherAccountDlg �޽��� ó�����Դϴ�.

