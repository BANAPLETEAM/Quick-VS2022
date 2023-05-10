// TestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FakeDlg.h"


// CFakeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFakeDlg, CDialog)

CFakeDlg::CFakeDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFakeDlg::IDD, pParent)
{

}

CFakeDlg::~CFakeDlg()
{
}

void CFakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFakeDlg, CDialog)

END_MESSAGE_MAP()


// CFakeDlg 메시지 처리기입니다.

BOOL CFakeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EndDialog(IDOK);

	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
