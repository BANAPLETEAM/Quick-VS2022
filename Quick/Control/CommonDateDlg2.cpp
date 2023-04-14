// CommonDateDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDateDlg2.h"



// CCommonDateDlg2 대화 상자입니다.

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


// CCommonDateDlg2 메시지 처리기입니다.

void CCommonDateDlg2::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CCommonDateDlg2::OnBnClickedOkBtn()
{
	m_DateCtrl.GetTime(m_Date);
	OnOK();
}
