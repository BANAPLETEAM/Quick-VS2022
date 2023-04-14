// RiderDepositMsgDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositMsgDlg.h"



// CRiderDepositMsgDlg ��ȭ �����Դϴ�.

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


// CRiderDepositMsgDlg �޽��� ó�����Դϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
