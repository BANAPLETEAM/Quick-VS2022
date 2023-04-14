// RiderDepositDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositDlg.h"



// CRiderDepositDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderDepositDlg, CMyDialog)
CRiderDepositDlg::CRiderDepositDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderDepositDlg::IDD, pParent)
{
}

CRiderDepositDlg::~CRiderDepositDlg()
{
}

void CRiderDepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DEPOSIT_EDIT, m_strDeposit);
}


BEGIN_MESSAGE_MAP(CRiderDepositDlg, CMyDialog)
END_MESSAGE_MAP()


// CRiderDepositDlg 메시지 처리기입니다.

BOOL CRiderDepositDlg::PreTranslateMessage(MSG* pMsg)
{
	return CMyDialog::PreTranslateMessage(pMsg);
}
