// RiderDepositDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositDlg.h"



// CRiderDepositDlg ��ȭ �����Դϴ�.

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


// CRiderDepositDlg �޽��� ó�����Դϴ�.

BOOL CRiderDepositDlg::PreTranslateMessage(MSG* pMsg)
{
	return CMyDialog::PreTranslateMessage(pMsg);
}
