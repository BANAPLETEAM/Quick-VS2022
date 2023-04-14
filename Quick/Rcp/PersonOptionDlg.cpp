// PersonOptionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "PersonOptionDlg.h"



// CPersonOptionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPersonOptionDlg, CMyDialog)
CPersonOptionDlg::CPersonOptionDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPersonOptionDlg::IDD, pParent)
{
}

CPersonOptionDlg::~CPersonOptionDlg()
{
}

void CPersonOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTO_FINISH_CHECK, m_chkAutoFinish);
	DDX_Control(pDX, IDC_AUTO_ALOCATE_CHECK, m_chkAutoAllocate);
}


BEGIN_MESSAGE_MAP(CPersonOptionDlg, CMyDialog)
	ON_BN_CLICKED(IDC_AUTO_FINISH_CHECK, OnBnClickedOrderFinishCheck)
	
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_AUTO_ALOCATE_CHECK, OnBnClickedAutoAlocateCheck)
END_MESSAGE_MAP()


// CPersonOptionDlg �޽��� ó�����Դϴ�.

BOOL CPersonOptionDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nAutoFinish = encProfile.GetInt("Person", "AutoFinish", 0);
	int nAutoAllocate = encProfile.GetInt("Person", "AutoAllocate", 0);
	m_chkAutoFinish.SetCheck(nAutoFinish);
	m_chkAutoAllocate.SetCheck(nAutoAllocate);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPersonOptionDlg::OnBnClickedOrderFinishCheck()
{
	
}


void CPersonOptionDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CPersonOptionDlg::OnBnClickedButton1()
{
	encProfile.WriteInt("Person", "AutoFinish", m_chkAutoFinish.GetCheck());
	encProfile.WriteInt("Person", "AutoAllocate", m_chkAutoAllocate.GetCheck());
}

void CPersonOptionDlg::OnBnClickedAutoAlocateCheck()
{
	
}
