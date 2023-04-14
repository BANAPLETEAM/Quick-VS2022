// AddCallHotNumberDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "AddHotMsgDlg.h"


// CAddHotMsgDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddHotMsgDlg, CMyDialog)

CAddHotMsgDlg::CAddHotMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddHotMsgDlg::IDD, pParent)
{
	m_pMyDb = NULL;
}

CAddHotMsgDlg::~CAddHotMsgDlg()
{
}

void CAddHotMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_strTitle);
	DDX_Text(pDX, IDC_MSG_EDIT, m_strMsg);
	DDX_Control(pDX, IDC_TITLE_EDIT, m_edtTitle);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
}


BEGIN_MESSAGE_MAP(CAddHotMsgDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOKBtn)
END_MESSAGE_MAP()


// CAddHotMsgDlg �޽��� ó�����Դϴ�.


BOOL CAddHotMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_strKeyTitle = m_strTitle;
	return TRUE;
}

void CAddHotMsgDlg::OnOK()
{
}

void CAddHotMsgDlg::OnBnClickedOKBtn()
{
	m_edtTitle.GetWindowText(m_strTitle);
	m_edtMsg.GetWindowText(m_strMsg);

	if(m_strTitle.GetLength() > 0 && m_strMsg.GetLength() >0)
	{
		CMkCommand pCmd(m_pMyDb, "insert_hot_msg2");
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(MESSENGER_HOT_MSG);
		pCmd.AddParameter(m_strKeyTitle);
		pCmd.AddParameter(m_strMsg);
		pCmd.AddParameter(m_strTitle);
		if(pCmd.Execute())
		{
			MessageBox("�߰�/���� �Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			CMyDialog::OnOK();
		}
	}
}