// ElapseLimitDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ElapseLimitDlg.h"


// CElapseLimitDlg 대화 상자입니다.

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


// CElapseLimitDlg 메시지 처리기입니다.

BOOL CElapseLimitDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	m_stcTitle.SetWindowText(m_sTitle);
	SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CElapseLimitDlg::OnBnClickedOk() 
{
	m_cmbElapseLimitAllocate.GetWindowText(m_sElaspeLimitAllocate);
	m_cmbElapseLimitPickup.GetWindowText(m_sElapseLimitPickup);
	OnOK();
}

void CElapseLimitDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
