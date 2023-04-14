// RiderDepositMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositMsgDlg.h"



// CRiderDepositMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderDepositMsgDlg, CMyDialog)
CRiderDepositMsgDlg::CRiderDepositMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderDepositMsgDlg::IDD, pParent)
	, m_sMsg(_T(""))
{
}

CRiderDepositMsgDlg::~CRiderDepositMsgDlg()
{
}

void CRiderDepositMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MSG_EDIT, m_sMsg);
}


BEGIN_MESSAGE_MAP(CRiderDepositMsgDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CRiderDepositMsgDlg 메시지 처리기입니다.

void CRiderDepositMsgDlg::OnBnClickedSendBtn()
{
	UpdateData(TRUE);
	OnOK();
}

void CRiderDepositMsgDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CRiderDepositMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
