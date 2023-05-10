// EtcDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Resource.h"
#include "EtcDlg.h"


// CEtcDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEtcDlg, CMyDialog)

CEtcDlg::CEtcDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CEtcDlg::IDD, pParent)
, m_strEtc(_T(""))
{
	m_strTitle = "";
}

CEtcDlg::~CEtcDlg()
{
}

void CEtcDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
}


BEGIN_MESSAGE_MAP(CEtcDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CEtcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEtcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEtcDlg �޽��� ó�����Դϴ�.


BOOL CEtcDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//CenterWindow();

	if(!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle); 


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CEtcDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CEtcDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
