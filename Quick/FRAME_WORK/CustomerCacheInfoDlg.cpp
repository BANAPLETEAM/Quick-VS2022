// CustomerCacheInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerCacheInfoDlg.h"
#include "CustomerData.h"


// CCustomerCacheInfoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCustomerCacheInfoDlg, CMyDialog)

CCustomerCacheInfoDlg::CCustomerCacheInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCustomerCacheInfoDlg::IDD, pParent)
{

}

CCustomerCacheInfoDlg::~CCustomerCacheInfoDlg()
{
}

void CCustomerCacheInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomerCacheInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REMAKE_BTN, &CCustomerCacheInfoDlg::OnBnClickedRemakeBtn)
END_MESSAGE_MAP()


// CCustomerCacheInfoDlg �޽��� ó�����Դϴ�.

BOOL CCustomerCacheInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_cus.SetCompanyCode(m_ci.m_nUseCustomerTable, m_ba.GetCount() < 2 ? FALSE : TRUE);
	GetDlgItem(IDC_INFO_STATIC)->SetWindowText(m_cus.GetInfo());

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCustomerCacheInfoDlg::OnBnClickedRemakeBtn()
{
	m_cus.ClearFileData();
	if(m_cus.IsDataLoadOK())
		MessageBox("���α׷� ����� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
		MessageBox("�������͸� �ʱ�ȭ �Ͽ����ϴ�.\n����ȭ������ ���� �Ͻñ� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);

}
