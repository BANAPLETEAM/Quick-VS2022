// VarietyDlg2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg2.h"



// CVarietyDlg2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVarietyDlg2, CMyDialog)
CVarietyDlg2::CVarietyDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg2::IDD, pParent)
	, m_sEtc(_T(""))
{
	m_sTitle = "";
}

CVarietyDlg2::~CVarietyDlg2()
{
}

void CVarietyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Text(pDX, IDC_ETC_EDIT, m_sEtc);
}


BEGIN_MESSAGE_MAP(CVarietyDlg2, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg2 �޽��� ó�����Դϴ�.

void CVarietyDlg2::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CVarietyDlg2::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CVarietyDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	this->SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
