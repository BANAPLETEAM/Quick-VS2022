// VarietyDlg1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg1.h"


// CVarietyDlg11 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVarietyDlg1, CMyDialog)
CVarietyDlg1::CVarietyDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg1::IDD, pParent)
{
	m_sValue = "";
	m_sValue2 = "";
}

CVarietyDlg1::~CVarietyDlg1()
{
}

void CVarietyDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sValue);
	DDX_Text(pDX, IDC_EDIT2, m_sValue2);
}


BEGIN_MESSAGE_MAP(CVarietyDlg1, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg1 �޽��� ó�����Դϴ�.

void CVarietyDlg1::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CVarietyDlg1::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

//void CVarietyDlg1::PreInitDialog()
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	CMyDialog::PreInitDialog();
//}

BOOL CVarietyDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData();

	this->SetWindowText(m_sTitleDlg);
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}