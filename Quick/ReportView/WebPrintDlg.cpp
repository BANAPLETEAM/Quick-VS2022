// WebPrintDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WebPrintDlg.h"



// CWebPrintDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWebPrintDlg, CMyDialog)
CWebPrintDlg::CWebPrintDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWebPrintDlg::IDD, pParent)
{
	m_bDelete = FALSE;
}

CWebPrintDlg::~CWebPrintDlg()
{
	if(m_bDelete)
		DeleteFile(m_sUrl);
}

void CWebPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CWebPrintDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_PRINT_BTN, OnBnClickedPrintBtn)
END_MESSAGE_MAP()


// CWebPrintDlg 메시지 처리기입니다.

void CWebPrintDlg::OnBnClickedRefreshBtn()
{	
	m_Explorer.Navigate(m_sUrl, NULL, NULL, NULL, NULL);    
}

BOOL CWebPrintDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	OnBnClickedRefreshBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWebPrintDlg::OnBnClickedPrintBtn()
{	
}
