// SumCnoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SumCnoDlg.h"



// CSumCnoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSumCnoDlg, CMyDialog)
CSumCnoDlg::CSumCnoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSumCnoDlg::IDD, pParent)
{
}

CSumCnoDlg::~CSumCnoDlg()
{
}

void CSumCnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CNO_STATIC1, m_strCNo1);
	DDX_Text(pDX, IDC_CNO_STATIC2, m_strCNo2);
	DDX_Text(pDX, IDC_CNO_STATIC3, m_strCNo3);
}


BEGIN_MESSAGE_MAP(CSumCnoDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSumCnoDlg �޽��� ó�����Դϴ�.

BOOL CSumCnoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect rc;
	GetWindowRect(rc);
	MoveWindow(rc);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSumCnoDlg::OnBnClickedOk()
{
	if(IDYES == MessageBox("���� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONQUESTION | MB_YESNO))
		OnOK();
	else
		OnCancel();
}
