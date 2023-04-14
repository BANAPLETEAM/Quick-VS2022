// BillDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "EMailDlg.h"


// CEMailDlg ��ȭ �����Դϴ�.

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


// CEMailDlg �޽��� ó�����Դϴ�.

BOOL CEMailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CEMailDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_strEMail.IsEmpty() ||
		m_strEMail.Find("@") == 0 ||
		m_strEMail.Find(".") == 0)
	{
		MessageBox("�̸����� ���Ŀ� ���� �ʽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CEMailDlg::OnBnClickedCancel()
{
	OnCancel();
}