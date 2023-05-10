// SumCnoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SumCnoDlg.h"



// CSumCnoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSumCnoDlg, CMyDialog)
CSumCnoDlg::CSumCnoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSumCnoDlg::IDD, pParent)
{
}

CSumCnoDlg::~CSumCnoDlg()
{
}

void CSumCnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CNO_STATIC1, m_strCNo1);
	DDX_Text(pDX, IDC_CNO_STATIC2, m_strCNo2);
	DDX_Text(pDX, IDC_CNO_STATIC3, m_strCNo3);
}


BEGIN_MESSAGE_MAP(CSumCnoDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSumCnoDlg 메시지 처리기입니다.

BOOL CSumCnoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect rc;
	GetWindowRect(rc);
	MoveWindow(rc);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSumCnoDlg::OnBnClickedOk()
{
	if(IDYES == MessageBox("정말 통합하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
		OnOK();
	else
		OnCancel();
}
