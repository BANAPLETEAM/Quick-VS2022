// RemoteAddrDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RemoteAddrDlg.h"



// CRemoteAddrDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRemoteAddrDlg, CMyDialog)
CRemoteAddrDlg::CRemoteAddrDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRemoteAddrDlg::IDD, pParent)
{
	m_nApplyRemote  = 0;
}

CRemoteAddrDlg::~CRemoteAddrDlg()
{
}

void CRemoteAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REMOTE_COMBO, m_cmbRemote);
}


BEGIN_MESSAGE_MAP(CRemoteAddrDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CRemoteAddrDlg �޽��� ó�����Դϴ�.

void CRemoteAddrDlg::OnBnClickedOk()
{

	m_nApplyRemote = (int)m_cmbRemote.GetItemData(m_cmbRemote.GetCurSel());

	OnOK();
}

BOOL CRemoteAddrDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cmbRemote.ResetContent();
	CString sRemote = "";
	for(int i = 0; i < 20 ; i++)
	{
		sRemote.Format("���ݿ��� %d",i + 1);
		
		m_cmbRemote.InsertString(i,sRemote );
		m_cmbRemote.SetItemData(i, (DWORD_PTR)i);
	}
	m_cmbRemote.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRemoteAddrDlg::OnBnClickedButton1()
{
	OnCancel();
}
