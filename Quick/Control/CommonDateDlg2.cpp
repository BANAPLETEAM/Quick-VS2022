// CommonDateDlg2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDateDlg2.h"



// CCommonDateDlg2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCommonDateDlg2, CMyDialog)
CCommonDateDlg2::CCommonDateDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDateDlg2::IDD, pParent)
	, m_Date(COleDateTime::GetCurrentTime())
{
}

CCommonDateDlg2::~CCommonDateDlg2()
{
}

void CCommonDateDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE_PICKER, m_DateCtrl);
//	DDX_DateTimeCtrl(pDX, IDC_DATE_PICKER, m_Date);
}


BEGIN_MESSAGE_MAP(CCommonDateDlg2, CMyDialog)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CCommonDateDlg2 �޽��� ó�����Դϴ�.

void CCommonDateDlg2::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CCommonDateDlg2::OnBnClickedOkBtn()
{
	m_DateCtrl.GetTime(m_Date);
	OnOK();
}
