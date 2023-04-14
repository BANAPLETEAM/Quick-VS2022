// VarietyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg.h"



// CVarietyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVarietyDlg, CMyDialog)
CVarietyDlg::CVarietyDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg::IDD, pParent)
	, m_sValue(_T(""))
{
}

CVarietyDlg::~CVarietyDlg()
{
}

void CVarietyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sValue);
}


BEGIN_MESSAGE_MAP(CVarietyDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg �޽��� ó�����Դϴ�.

void CVarietyDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CVarietyDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

//void CVarietyDlg::PreInitDialog()
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	CMyDialog::PreInitDialog();
//}

BOOL CVarietyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(FALSE);

	this->SetWindowText(m_sTitleDlg);
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
