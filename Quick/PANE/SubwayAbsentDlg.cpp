// SubwayAbsentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "SubwayAbsentDlg.h"


// CSubwayAbsentDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSubwayAbsentDlg, CMyDialog)

CSubwayAbsentDlg::CSubwayAbsentDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSubwayAbsentDlg::IDD, pParent)
{

}

CSubwayAbsentDlg::~CSubwayAbsentDlg()
{
}

void CSubwayAbsentDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABSENT_CHECK, m_chkAbsent);
	DDX_Control(pDX, IDC_GET_OFF_CHECK, m_chkGetOff);
	DDX_Control(pDX, IDC_LOCATION_EDIT, m_edtLocation);
	DDX_Control(pDX, IDC_WAIT_TIME_CHECK, m_chkWaitTime);
	
}


BEGIN_MESSAGE_MAP(CSubwayAbsentDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CSubwayAbsentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSubwayAbsentDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ABSENT_CHECK, &CSubwayAbsentDlg::OnBnClickedAbsentCheck)
	ON_BN_CLICKED(IDC_GET_OFF_CHECK, &CSubwayAbsentDlg::OnBnClickedGetOffCheck)
END_MESSAGE_MAP()


// CSubwayAbsentDlg �޽��� ó�����Դϴ�.

BOOL CSubwayAbsentDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_chkAbsent.SetCheck(TRUE);
	m_edtLocation.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSubwayAbsentDlg::OnBnClickedOk()
{
	CString strLocation; m_edtLocation.GetWindowText(strLocation);

	CMkCommand pCmd(m_pMkDb, "update_subway_location_1");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nRNo);;
	pCmd.AddParameter(m_chkAbsent.GetCheck());
	pCmd.AddParameter(strLocation);
	pCmd.AddParameter(m_chkWaitTime.GetCheck());

	if(pCmd.Execute())
		OnOK();
}

void CSubwayAbsentDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CSubwayAbsentDlg::OnBnClickedAbsentCheck()
{
	m_chkGetOff.SetCheck(!m_chkAbsent.GetCheck());
}

void CSubwayAbsentDlg::OnBnClickedGetOffCheck()
{
	m_chkAbsent.SetCheck(!m_chkGetOff.GetCheck());
}
