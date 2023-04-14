// LockAllocateDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "LockAllocateDlg.h"


// CLockAllocateDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLockAllocateDlg, CMyDialog)

CLockAllocateDlg::CLockAllocateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CLockAllocateDlg::IDD, pParent) 
{

}

CLockAllocateDlg::~CLockAllocateDlg()
{
}

void CLockAllocateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MINUTE, m_cmbMinute);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_cmbCount);
}


BEGIN_MESSAGE_MAP(CLockAllocateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CLockAllocateDlg::OnBnClickedOkBtn)
END_MESSAGE_MAP()



BOOL CLockAllocateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CLockAllocateDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	m_cmbMinute.GetWindowText(m_sMinute);
	m_cmbCount.GetWindowText(m_sCount);

	OnOK();
}
