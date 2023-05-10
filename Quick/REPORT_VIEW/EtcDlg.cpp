// EtcDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Resource.h"
#include "EtcDlg.h"


// CEtcDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEtcDlg, CMyDialog)

CEtcDlg::CEtcDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CEtcDlg::IDD, pParent)
, m_strEtc(_T(""))
{
	m_strTitle = "";
}

CEtcDlg::~CEtcDlg()
{
}

void CEtcDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
}


BEGIN_MESSAGE_MAP(CEtcDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CEtcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEtcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEtcDlg 메시지 처리기입니다.


BOOL CEtcDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//CenterWindow();

	if(!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle); 


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEtcDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CEtcDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
