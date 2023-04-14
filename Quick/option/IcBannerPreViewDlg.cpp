// IcBannerPreViewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "IcBannerPreViewDlg.h"


// CIcBannerPreViewDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CIcBannerPreViewDlg, CMyDialog)

CIcBannerPreViewDlg::CIcBannerPreViewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CIcBannerPreViewDlg::IDD, pParent)
{
	m_sBanner = "";
}

CIcBannerPreViewDlg::~CIcBannerPreViewDlg()
{
}
 
void CIcBannerPreViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CIcBannerPreViewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CIcBannerPreViewDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CIcBannerPreViewDlg �޽��� ó�����Դϴ�.

BOOL CIcBannerPreViewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString sUrl = "http://manual.logisoft.co.kr/Banner/Banner.asp?sEtc=" + m_sBanner;
	//m_Explorer.EnableScrollBar(SB_VERT,ESB_DISABLE_RTDN   );
	m_Explorer.Navigate(sUrl, NULL, NULL, NULL, NULL);
	m_Explorer.EnableScrollBar(SB_BOTH      ,ESB_DISABLE_BOTH      );

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CIcBannerPreViewDlg::OnBnClickedButton1()
{
	OnOK();
}
