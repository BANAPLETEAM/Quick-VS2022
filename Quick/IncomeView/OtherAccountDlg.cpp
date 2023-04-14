// OtherAccountDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OtherAccountDlg.h"


// COtherAccountDlg 대화 상자입니다.

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


// COtherAccountDlg 메시지 처리기입니다.

