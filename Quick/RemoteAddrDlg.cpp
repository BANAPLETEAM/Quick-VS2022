// RemoteAddrDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RemoteAddrDlg.h"



// CRemoteAddrDlg 대화 상자입니다.

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


// CRemoteAddrDlg 메시지 처리기입니다.

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
		sRemote.Format("원격연결 %d",i + 1);
		
		m_cmbRemote.InsertString(i,sRemote );
		m_cmbRemote.SetItemData(i, (DWORD_PTR)i);
	}
	m_cmbRemote.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRemoteAddrDlg::OnBnClickedButton1()
{
	OnCancel();
}
