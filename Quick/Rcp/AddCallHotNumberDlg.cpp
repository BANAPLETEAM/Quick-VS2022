// AddCallHotNumberDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddCallHotNumberDlg.h"


// CAddCallHotNumberDlg 대화 상자입니다.

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


// CAddCallHotNumberDlg 메시지 처리기입니다.

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
			MessageBox("추가/수정 되었습니다.", "확인", MB_ICONINFORMATION);
			CMyDialog::OnOK();
		}
	}
}