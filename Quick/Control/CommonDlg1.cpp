// CommonDlg1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDlg1.h"



// CCommonDlg1 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCommonDlg1, CMyDialog)
CCommonDlg1::CCommonDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDlg1::IDD, pParent)
	, m_strEdit(_T(""))
{
}

CCommonDlg1::~CCommonDlg1()
{
}

void CCommonDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtEdit);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
}


BEGIN_MESSAGE_MAP(CCommonDlg1, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CCommonDlg1 �޽��� ó�����Դϴ�.

void CCommonDlg1::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CCommonDlg1::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

BOOL CCommonDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtEdit.SetWindowText(m_strEdit);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
