// AddCallHotNumberDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "AddCallHotNumberDlg.h"


// CAddCallHotNumberDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddCallHotNumberDlg, CMyDialog)

CAddCallHotNumberDlg::CAddCallHotNumberDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddCallHotNumberDlg::IDD, pParent)
{
	m_pMyDb = NULL;
}

CAddCallHotNumberDlg::~CAddCallHotNumberDlg()
{
}

void CAddCallHotNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
}


BEGIN_MESSAGE_MAP(CAddCallHotNumberDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOKBtn)
END_MESSAGE_MAP()


// CAddCallHotNumberDlg �޽��� ó�����Դϴ�.

void CAddCallHotNumberDlg::OnOK()
{
	
}

void CAddCallHotNumberDlg::OnBnClickedOKBtn()
{
	CString strPhone, strName;
	m_edtPhone.GetWindowText(strPhone);
	m_edtName.GetWindowText(strName);

	if(strPhone.GetLength() > 0 && strName.GetLength() >0)
	{
		CMkCommand pCmd(m_pMyDb, "insert_call_hot_number");
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(strPhone);
		pCmd.AddParameter(strName);
		if(pCmd.Execute())
		{
			MessageBox("�߰�/���� �Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			CMyDialog::OnOK();
		}
	}
}