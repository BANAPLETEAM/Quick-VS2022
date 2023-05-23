// WithdrawManualDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "WithdrawManualDlg.h"


// CWithdrawManualDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWithdrawManualDlg, CMyDialog)

CWithdrawManualDlg::CWithdrawManualDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWithdrawManualDlg::IDD, pParent)
{

}

CWithdrawManualDlg::~CWithdrawManualDlg()
{
}

void CWithdrawManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REAL_WITHDRAW_EDIT, m_edtRealWithdraw);
	DDX_Control(pDX, IDC_DATE_DT, m_dtpDate);
	DDX_Control(pDX, IDC_TIME_DT, m_dtpTime);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
}

BEGIN_MESSAGE_MAP(CWithdrawManualDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CWithdrawManualDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWithdrawManualDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWithdrawManualDlg �޽��� ó�����Դϴ�.

BOOL CWithdrawManualDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dtpTime.SetFormat("tth-mm");

	m_dtpDate.SetTime(COleDateTime::GetCurrentTime());
	m_dtpTime.SetTime(COleDateTime::GetCurrentTime());

	m_edtRealWithdraw.SetWindowText(LF->GetMyNumberFormat(m_nCharge));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CWithdrawManualDlg::OnBnClickedOk()
{
	m_nCharge = LF->GetLongFromEdit(&m_edtRealWithdraw);

	if(m_nCharge <= 0)
	{
		MessageBox("���� ��ü�Ͻ� �ݾ��� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_edtEtc.GetWindowText(m_strEtc);

	COleDateTime  dtTime;
	m_dtpDate.GetTime(m_dtWithdraw);
	m_dtpTime.GetTime(dtTime);

	m_dtWithdraw.SetTime(dtTime.GetHour(), dtTime.GetMinute(), dtTime.GetSecond());
	
	OnOK();
}

void CWithdrawManualDlg::OnBnClickedCancel()
{
	OnCancel();
}

