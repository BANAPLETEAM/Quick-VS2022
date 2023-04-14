// BillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "PayCashDlg.h"


// CPayCashDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPayCashDlg, CMyDialog)
CPayCashDlg::CPayCashDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPayCashDlg::IDD, pParent)
{
	m_strEMail = "";
}

CPayCashDlg::~CPayCashDlg()
{
}

void CPayCashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO_EDIT, m_strInfo);
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_CHECK2, m_chk2);
}


BEGIN_MESSAGE_MAP(CPayCashDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
END_MESSAGE_MAP()

void CPayCashDlg::OnBnClickedCheck1()
{
	m_chk2.SetCheck(!m_chk1.GetCheck());
}

void CPayCashDlg::OnBnClickedCheck2()
{
	m_chk1.SetCheck(!m_chk2.GetCheck());
}

// CPayCashDlg 메시지 처리기입니다.

BOOL CPayCashDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_chk1.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPayCashDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_strInfo.Replace("-", "");

	if(m_strInfo.IsEmpty() ||
		::IsNumber(m_strInfo) == FALSE)
	{
		MessageBox("발급번호를 확인하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if( (m_chk1.GetCheck() && m_chk2.GetCheck()) ||
		(!m_chk1.GetCheck() && !m_chk2.GetCheck()) )
	{
		MessageBox("용도구분을 확인하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_chk1.GetCheck())
		m_nType = 1;
	else 
		m_nType = 2;

	OnOK();
}

void CPayCashDlg::OnBnClickedCancel()
{
	OnCancel();
}