// MakeFixedDepositDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MakeFixedDepositDlg.h"



// CMakeFixedDepositDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMakeFixedDepositDlg, CMyDialog)
CMakeFixedDepositDlg::CMakeFixedDepositDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMakeFixedDepositDlg::IDD, pParent)
{
}

CMakeFixedDepositDlg::~CMakeFixedDepositDlg()
{
}

void CMakeFixedDepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OK_BTN, m_bntOk);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpDate);
}

BEGIN_MESSAGE_MAP(CMakeFixedDepositDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CMakeFixedDepositDlg 메시지 처리기입니다.

BOOL CMakeFixedDepositDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dtpDate.SetTime(COleDateTime::GetCurrentTime());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMakeFixedDepositDlg::OnBnClickedOkBtn()
{	
	CMkCommand pCmd(m_pMkDb, "make_fixed_deposit"); 

	CString strCharge; m_edtCharge.GetWindowText(strCharge);

	CString strEtc; m_edtEtc.GetWindowText(strEtc);
	COleDateTime dtDate; m_dtpDate.GetTime(dtDate);

	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_strRName);
	pCmd.AddParameter(_ttoi(strCharge));
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(dtDate);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);

	if(pCmd.Execute())
		OnOK();
}

void CMakeFixedDepositDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
