// RcpDlgSetupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpDlgSetupDlg.h"


#define LOAD_FROM_REG(y, x) info.x = AfxGetApp()->GetProfileInt("RcpDlgSetup", #x, y);
#define SAVE_TO_REG(x) AfxGetApp()->WriteProfileInt("RcpDlgSetup", #x, info.x);
#define SET_CHECK(x, y)  ((CButton*)GetDlgItem(x))->SetCheck(m_info.y);
#define SET_COMBO(x, y)  ((CComboBox*)GetDlgItem(x))->SetCurSel(m_info.y);
#define GET_CHECK(x, y)  m_info.y = ((CButton*)GetDlgItem(x))->GetCheck();
#define GET_COMBO(x, y)  m_info.y = ((CComboBox*)GetDlgItem(x))->GetCurSel();

ST_RCP_DLG_SET_INFO CRcpDlgSetupDlg::m_info;


// CRcpDlgSetupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRcpDlgSetupDlg, CMyDialog)

CRcpDlgSetupDlg::CRcpDlgSetupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpDlgSetupDlg::IDD, pParent)
{

}

CRcpDlgSetupDlg::~CRcpDlgSetupDlg()
{
}

void CRcpDlgSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRcpDlgSetupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOk)
END_MESSAGE_MAP()


// CRcpDlgSetupDlg �޽��� ó�����Դϴ�.

BOOL CRcpDlgSetupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	LoadFromReg(m_info);
	StructToResource();

	return TRUE;
}	

void CRcpDlgSetupDlg::StructToResource()
{
	SET_CHECK(IDC_REPLACE_PHONE1_WITH_CID_CHECK, nReplacePhone1WithCID);
	SET_CHECK(IDC_REPLACE_PHONE2_WITH_PHONE1_CHECK, nReplacePhone2WithPhone1);
	SET_CHECK(IDC_INCREASE_DETAIL_CONTROL_ALWAYS_CHECK, nIncreaseDetailControlAlways);
	SET_CHECK(IDC_COPY_DEST_CREDIT_CUSTOMER_CHECK, nCopyDestCreditCustomer);
	SET_CHECK(IDC_START_DONT_AUTO_COPY_CHECK, nStartDontAutoCopy);
	SET_CHECK(IDC_MENUAL_ADD_CUSTOMER_CHECK, nManualAddCustomer);
}

void CRcpDlgSetupDlg::ResourceToStruct()
{
	GET_CHECK(IDC_REPLACE_PHONE1_WITH_CID_CHECK, nReplacePhone1WithCID);
	GET_CHECK(IDC_REPLACE_PHONE2_WITH_PHONE1_CHECK, nReplacePhone2WithPhone1);
	GET_CHECK(IDC_INCREASE_DETAIL_CONTROL_ALWAYS_CHECK, nIncreaseDetailControlAlways);
	GET_CHECK(IDC_COPY_DEST_CREDIT_CUSTOMER_CHECK, nCopyDestCreditCustomer);
	GET_CHECK(IDC_START_DONT_AUTO_COPY_CHECK, nStartDontAutoCopy);
	GET_CHECK(IDC_MENUAL_ADD_CUSTOMER_CHECK, nManualAddCustomer);
}

void CRcpDlgSetupDlg::OnBnClickedOk()
{
	ResourceToStruct();
	::SaveToReg(m_info);
	OnOK();
}