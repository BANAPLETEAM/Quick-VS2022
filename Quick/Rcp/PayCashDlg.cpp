// BillDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "PayCashDlg.h"


// CPayCashDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPayCashDlg, CMyDialog)
CPayCashDlg::CPayCashDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPayCashDlg::IDD, pParent)
{
	m_strEMail = "";
}

CPayCashDlg::~CPayCashDlg()
{
}

void CPayCashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO_EDIT, m_strInfo);
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_CHECK2, m_chk2);
}


BEGIN_MESSAGE_MAP(CPayCashDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
END_MESSAGE_MAP()

void CPayCashDlg::OnBnClickedCheck1()
{
	m_chk2.SetCheck(!m_chk1.GetCheck());
}

void CPayCashDlg::OnBnClickedCheck2()
{
	m_chk1.SetCheck(!m_chk2.GetCheck());
}

// CPayCashDlg �޽��� ó�����Դϴ�.

BOOL CPayCashDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_chk1.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CPayCashDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_strInfo.Replace("-", "");

	if(m_strInfo.IsEmpty() ||
		::IsNumber(m_strInfo) == FALSE)
	{
		MessageBox("�߱޹�ȣ�� Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if( (m_chk1.GetCheck() && m_chk2.GetCheck()) ||
		(!m_chk1.GetCheck() && !m_chk2.GetCheck()) )
	{
		MessageBox("�뵵������ Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_chk1.GetCheck())
		m_nType = 1;
	else 
		m_nType = 2;

	OnOK();
}

void CPayCashDlg::OnBnClickedCancel()
{
	OnCancel();
}