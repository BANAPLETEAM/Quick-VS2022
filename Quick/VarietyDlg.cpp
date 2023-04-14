// VarietyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg.h"



// CVarietyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVarietyDlg, CMyDialog)
CVarietyDlg::CVarietyDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg::IDD, pParent)
	, m_sValue(_T(""))
{
}

CVarietyDlg::~CVarietyDlg()
{
}

void CVarietyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sValue);
}


BEGIN_MESSAGE_MAP(CVarietyDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg 메시지 처리기입니다.

void CVarietyDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CVarietyDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

//void CVarietyDlg::PreInitDialog()
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	CMyDialog::PreInitDialog();
//}

BOOL CVarietyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(FALSE);

	this->SetWindowText(m_sTitleDlg);
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
