// CommonDateDlg1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDateDlg1.h"



// CCommonDateDlg1 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCommonDateDlg1, CMyDialog)
CCommonDateDlg1::CCommonDateDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDateDlg1::IDD, pParent)
{
	m_dtFrom = COleDateTime::GetCurrentTime();
	m_dtTo = COleDateTime::GetCurrentTime();
}

CCommonDateDlg1::~CCommonDateDlg1()
{
}

void CCommonDateDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
}


BEGIN_MESSAGE_MAP(CCommonDateDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()



// CCommonDateDlg1 �޽��� ó�����Դϴ�.

BOOL CCommonDateDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	//m_DateBtn.OnMenuWeek();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCommonDateDlg1::OnBnClickedOkBtn()
{
	UpdateData(TRUE);
	OnOK();
}

void CCommonDateDlg1::OnBnClickedCancelBtn()
{
	OnCancel();
}
