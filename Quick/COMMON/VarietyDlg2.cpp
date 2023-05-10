// VarietyDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg2.h"



// CVarietyDlg2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVarietyDlg2, CMyDialog)
CVarietyDlg2::CVarietyDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg2::IDD, pParent)
	, m_sEtc(_T(""))
{
	m_sTitle = "";
}

CVarietyDlg2::~CVarietyDlg2()
{
}

void CVarietyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Text(pDX, IDC_ETC_EDIT, m_sEtc);
}


BEGIN_MESSAGE_MAP(CVarietyDlg2, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg2 메시지 처리기입니다.

void CVarietyDlg2::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CVarietyDlg2::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CVarietyDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	this->SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
