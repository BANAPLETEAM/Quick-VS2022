// ShareProgDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ShareProgDlg.h"


// CShareProgDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareProgDlg, CMyDialog)

CShareProgDlg::CShareProgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareProgDlg::IDD, pParent)
{
	m_nShare = 0;
}

CShareProgDlg::~CShareProgDlg()
{
}

void CShareProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TONGHAP_CHECK, m_chkTongHap);
	DDX_Control(pDX, IDC_YEGI_CHECK, m_chkYegi);
	DDX_Control(pDX, IDC_SONJA_CHECK, m_chkSonja);
	DDX_Control(pDX, IDC_LOGI_CHECK, m_chkLogi);
}


BEGIN_MESSAGE_MAP(CShareProgDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CShareProgDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CShareProgDlg �޽��� ó�����Դϴ�.

BOOL CShareProgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CMkCommand cmd(m_pMkDb, "select_coali_share");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ci.m_nCompanyCode);

	if(!cmd.Execute())
		return FALSE;

	parRet->GetValue(m_nShare);
  
	m_chkLogi.SetCheck((m_nShare & 1) == 1 ? TRUE : FALSE);
	m_chkSonja.SetCheck((m_nShare & 2) == 2 ? TRUE : FALSE);
	m_chkYegi.SetCheck((m_nShare & 4) == 4 ? TRUE : FALSE); 
	m_chkTongHap.SetCheck((m_nShare & 8) == 8 ? TRUE : FALSE); 
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CShareProgDlg::OnBnClickedOk()
{
	m_nShare = 0;

	if(m_chkLogi.GetCheck()) m_nShare = m_nShare | 1;
	if(m_chkSonja.GetCheck()) m_nShare = m_nShare | 2;
	if(m_chkYegi.GetCheck()) m_nShare = m_nShare | 4;
	if(m_chkTongHap.GetCheck()) m_nShare = m_nShare | 8;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}
