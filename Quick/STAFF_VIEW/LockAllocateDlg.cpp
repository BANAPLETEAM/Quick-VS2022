// LockAllocateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "LockAllocateDlg.h"


// CLockAllocateDlg 대화 상자입니다.

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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLockAllocateDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	m_cmbMinute.GetWindowText(m_sMinute);
	m_cmbCount.GetWindowText(m_sCount);

	OnOK();
}
