// ElapseLimitDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ElapseLimitDlg.h"


// CElapseLimitDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CElapseLimitDlg, CMyDialog)

CElapseLimitDlg::CElapseLimitDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CElapseLimitDlg::IDD, pParent)
{

}

CElapseLimitDlg::~CElapseLimitDlg()
{
}

void CElapseLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_LOCAL_COMBO, m_cmbElapseLimitAllocate);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_PICKUP_LOCAL_COMBO, m_cmbElapseLimitPickup);
	DDX_Control(pDX, IDC_TITLE_STATIC, m_stcTitle);
}


BEGIN_MESSAGE_MAP(CElapseLimitDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CElapseLimitDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CElapseLimitDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CElapseLimitDlg �޽��� ó�����Դϴ�.

BOOL CElapseLimitDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	m_stcTitle.SetWindowText(m_sTitle);
	SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CElapseLimitDlg::OnBnClickedOk() 
{
	m_cmbElapseLimitAllocate.GetWindowText(m_sElaspeLimitAllocate);
	m_cmbElapseLimitPickup.GetWindowText(m_sElapseLimitPickup);
	OnOK();
}

void CElapseLimitDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
