// VarietyDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "VarietyDlg1.h"


// CVarietyDlg11 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVarietyDlg1, CMyDialog)
CVarietyDlg1::CVarietyDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg1::IDD, pParent)
{
	m_sValue = "";
	m_sValue2 = "";
}

CVarietyDlg1::~CVarietyDlg1()
{
}

void CVarietyDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sValue);
	DDX_Text(pDX, IDC_EDIT2, m_sValue2);
}


BEGIN_MESSAGE_MAP(CVarietyDlg1, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CVarietyDlg1 메시지 처리기입니다.

void CVarietyDlg1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CVarietyDlg1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

//void CVarietyDlg1::PreInitDialog()
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	CMyDialog::PreInitDialog();
//}

BOOL CVarietyDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData();

	this->SetWindowText(m_sTitleDlg);
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}