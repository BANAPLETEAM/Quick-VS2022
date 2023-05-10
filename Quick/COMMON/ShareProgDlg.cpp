// ShareProgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ShareProgDlg.h"


// CShareProgDlg 대화 상자입니다.

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


// CShareProgDlg 메시지 처리기입니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CShareProgDlg::OnBnClickedOk()
{
	m_nShare = 0;

	if(m_chkLogi.GetCheck()) m_nShare = m_nShare | 1;
	if(m_chkSonja.GetCheck()) m_nShare = m_nShare | 2;
	if(m_chkYegi.GetCheck()) m_nShare = m_nShare | 4;
	if(m_chkTongHap.GetCheck()) m_nShare = m_nShare | 8;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
