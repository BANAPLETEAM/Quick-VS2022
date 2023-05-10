// PasswordDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "PasswordDlg.h"


// CPasswordDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPasswordDlg, CMyDialog)
CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPasswordDlg::IDD, pParent)
{
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ORIPW_EDIT, m_edtOriPW);
	DDX_Control(pDX, IDC_NEWPW_EDIT1, m_edtNewPW);
	DDX_Control(pDX, IDC_NEWPW_EDIT2, m_edtPWEdit2);
	DDX_Text(pDX, IDC_ORIPW_EDIT, m_strOriPW);
	DDX_Text(pDX, IDC_NEWPW_EDIT1, m_strNewPW1);
	DDX_Text(pDX, IDC_NEWPW_EDIT2, m_strNewPW2);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordDlg 메시지 처리기입니다.

BOOL CPasswordDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPasswordDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}
