// PasswordDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "PasswordDlg.h"


// CPasswordDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPasswordDlg, CMyDialog)
CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPasswordDlg::IDD, pParent)
{
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORIPW_EDIT, m_edtOriPW);
	DDX_Control(pDX, IDC_NEWPW_EDIT1, m_edtNewPW);
	DDX_Control(pDX, IDC_NEWPW_EDIT2, m_edtPWEdit2);
	DDX_Text(pDX, IDC_ORIPW_EDIT, m_strOriPW);
	DDX_Text(pDX, IDC_NEWPW_EDIT1, m_strNewPW1);
	DDX_Text(pDX, IDC_NEWPW_EDIT2, m_strNewPW2);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordDlg �޽��� ó�����Դϴ�.

BOOL CPasswordDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPasswordDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}
