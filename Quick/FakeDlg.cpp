// TestDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "FakeDlg.h"


// CFakeDlg ��ȭ �����Դϴ�.

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


// CFakeDlg �޽��� ó�����Դϴ�.

BOOL CFakeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EndDialog(IDOK);

	return FALSE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
