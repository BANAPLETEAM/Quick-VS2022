#include "stdafx.h"
#include "resource.h"
#include "TRSInsertRiderDlg.h"
// CTRSInsertRiderDlg 대화 상자입니다.

#define ID_TRS_RIDER_DELETE 1000

IMPLEMENT_DYNAMIC(CTRSInsertRiderDlg, CMyDialog)
CTRSInsertRiderDlg::CTRSInsertRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTRSInsertRiderDlg::IDD, pParent)
	, m_strCompany(_T(""))
	, m_strRNo(_T(""))
	, m_strRName(_T(""))
	, m_strPhone(_T(""))
	, m_strExten(_T(""))
	, m_strPW(_T(""))
{
	
}

CTRSInsertRiderDlg::~CTRSInsertRiderDlg()
{
}

void CTRSInsertRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_RNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_EXTEN_EDIT, m_edtExten);
	DDX_Control(pDX, IDC_PW_EDIT, m_edtPW);

	DDX_Text(pDX, IDC_COMPANY_EDIT, m_strCompany);
	DDX_Text(pDX, IDC_RNO_EDIT, m_strRNo);
	DDX_Text(pDX, IDC_RNAME_EDIT, m_strRName);
	DDX_Text(pDX, IDC_PHONE_EDIT, m_strPhone);
	DDX_Text(pDX, IDC_EXTEN_EDIT, m_strExten);
	DDX_Text(pDX, IDC_PW_EDIT, m_strPW);
}


BEGIN_MESSAGE_MAP(CTRSInsertRiderDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOK)
END_MESSAGE_MAP()

BOOL CTRSInsertRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTRSInsertRiderDlg::OnBnClickedOK()
{
	UpdateData(TRUE);
	OnOK();
}
