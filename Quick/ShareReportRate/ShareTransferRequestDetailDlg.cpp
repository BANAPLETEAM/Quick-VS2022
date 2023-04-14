// ShareTransferRequsetDetailDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTransferRequestDetailDlg.h"


// CShareTransferRequestDetailDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShareTransferRequestDetailDlg, CMyDialog)
CShareTransferRequestDetailDlg::CShareTransferRequestDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareTransferRequestDetailDlg::IDD, pParent)
{
}

CShareTransferRequestDetailDlg::~CShareTransferRequestDetailDlg()
{
}

void CShareTransferRequestDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_CompanyEdt);
	DDX_Control(pDX, IDC_DATE_EDIT, m_DateEdt);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_ChargeEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
}


BEGIN_MESSAGE_MAP(CShareTransferRequestDetailDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CShareTransferRequsetDetailDlg 메시지 처리기입니다.

void CShareTransferRequestDetailDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

BOOL CShareTransferRequestDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_CompanyEdt.SetWindowText(m_sCompany);
	m_DateEdt.SetWindowText(m_sDate);
	m_ChargeEdt.SetWindowText(m_sCharge);
	m_MemoEdt.SetWindowText(m_sMemo);
		

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
