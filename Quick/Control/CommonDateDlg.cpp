// CommonDateDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDateDlg.h"



// CCommonDateDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCommonDateDlg, CMyDialog)
CCommonDateDlg::CCommonDateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDateDlg::IDD, pParent)
{
	m_dtDate = COleDateTime(2000, 1, 1, 0, 0, 0);
}

CCommonDateDlg::~CCommonDateDlg()
{
}

void CCommonDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_CHECK2, m_chk2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateDtp);
} 


BEGIN_MESSAGE_MAP(CCommonDateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CCommonDateDlg �޽��� ó�����Դϴ�.

void CCommonDateDlg::OnBnClickedOkBtn()
{
	if(m_chk1.GetCheck() == BST_CHECKED)
		m_dtDate = COleDateTime(2000, 1, 1, 0, 0, 0);
	else
	{
		m_DateDtp.GetTime(m_dtDate);
	}

	OnOK();
}

BOOL CCommonDateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_chk1.SetCheck(TRUE);
	OnBnClickedCheck1();


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCommonDateDlg::OnBnClickedCheck1()
{
	if(m_chk1.GetCheck() == BST_CHECKED)
	{
		m_DateDtp.EnableWindow(FALSE);
		m_chk2.SetCheck(FALSE);
	}
	else
	{
		m_DateDtp.EnableWindow(TRUE);
		m_chk2.SetCheck(TRUE);
	}
}

void CCommonDateDlg::OnBnClickedCheck2()
{
	if(m_chk2.GetCheck() == BST_CHECKED)
	{
		m_DateDtp.EnableWindow(TRUE);
		m_chk1.SetCheck(FALSE);
	}
	else
	{
		m_DateDtp.EnableWindow(FALSE);
		m_chk1.SetCheck(TRUE);
	}
}

void CCommonDateDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
