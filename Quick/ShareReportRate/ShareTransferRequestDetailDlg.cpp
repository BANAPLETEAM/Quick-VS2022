// ShareTransferRequsetDetailDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTransferRequestDetailDlg.h"


// CShareTransferRequestDetailDlg ��ȭ �����Դϴ�.

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


// CShareTransferRequsetDetailDlg �޽��� ó�����Դϴ�.

void CShareTransferRequestDetailDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

BOOL CShareTransferRequestDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_CompanyEdt.SetWindowText(m_sCompany);
	m_DateEdt.SetWindowText(m_sDate);
	m_ChargeEdt.SetWindowText(m_sCharge);
	m_MemoEdt.SetWindowText(m_sMemo);
		

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
