// CommonDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDlg1.h"



// CCommonDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCommonDlg1, CMyDialog)
CCommonDlg1::CCommonDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDlg1::IDD, pParent)
	, m_strEdit(_T(""))
{
}

CCommonDlg1::~CCommonDlg1()
{
}

void CCommonDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtEdit);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
}


BEGIN_MESSAGE_MAP(CCommonDlg1, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CCommonDlg1 메시지 처리기입니다.

void CCommonDlg1::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CCommonDlg1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

BOOL CCommonDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtEdit.SetWindowText(m_strEdit);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
