// CommonDlg2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CommonDlg2.h"



// CCommonDlg2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCommonDlg2, CMyDialog)
CCommonDlg2::CCommonDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCommonDlg2::IDD, pParent)
{
	m_nSelItem = 0;
	m_nRowCount = 0;
}

CCommonDlg2::~CCommonDlg2()
{
}

void CCommonDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	for(int i=0; i<MAX_BUTTON_COUNT; i++)
	{
		DDX_Control(pDX, ID_OPTION_BUTTON1 + i, m_btnOption[i]);
		DDX_Text(pDX, ID_OPTION_BUTTON1 + i, m_sOption[i]);
	}
}


BEGIN_MESSAGE_MAP(CCommonDlg2, CMyDialog)
	ON_COMMAND_RANGE(ID_OPTION_BUTTON1, ID_OPTION_BUTTON20, OnBtnClick)
END_MESSAGE_MAP()


// CCommonDlg2 �޽��� ó�����Դϴ�.

BOOL CCommonDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect rc;
	m_btnOption[0].GetWindowRect(rc);
	long nBottom = rc.bottom;
	int i = 0;
	for(i = 0; i < m_nRowCount; i++)
	{
		m_btnOption[i].ShowWindow(TRUE);

		CRect rc1;
		m_btnOption[i].GetWindowRect(rc1);
		nBottom = rc1.bottom;
	}

	for(int j = m_nRowCount; j < MAX_BUTTON_COUNT; j++)
	{
		m_btnOption[i].ShowWindow(FALSE);
	}

	CRect rcThis;
	GetWindowRect(rcThis);
	rcThis.bottom = nBottom + 15;

	MoveWindow(rcThis);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCommonDlg2::OnBtnClick(UINT nID)
{
	m_nSelItem = nID - ID_OPTION_BUTTON1;
	OnOK();
}

