// ChargeForRiderTransferDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeForRiderTransferDlg.h"


// CChargeForRiderTransferDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeForRiderTransferDlg, CMyDialog)

CChargeForRiderTransferDlg::CChargeForRiderTransferDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeForRiderTransferDlg::IDD, pParent)
{
	m_nID = 0;
	m_nSmsID = 0;
	m_bSmsAuth = FALSE;
}

CChargeForRiderTransferDlg::~CChargeForRiderTransferDlg()
{
}

void CChargeForRiderTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_AUTH_NUMBER_EDIT, m_edtAuthNumber);

	DDX_Control(pDX, IDC_AUTH_RADIO1, m_rdoAuth1);
	DDX_Control(pDX, IDC_AUTH_RADIO2, m_rdoAuth2);
	DDX_Control(pDX, IDC_AUTH_BTN, m_btnAuth);
}


BEGIN_MESSAGE_MAP(CChargeForRiderTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CHARGE_FOR_BTN, &CChargeForRiderTransferDlg::OnBnClickedChargeForBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChargeForRiderTransferDlg::OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_SEND_SMS_BTN, &CChargeForRiderTransferDlg::OnBnClickedSendSmsBtn)
	ON_BN_CLICKED(IDC_AUTH_BTN, &CChargeForRiderTransferDlg::OnBnClickedAuthBtn)
END_MESSAGE_MAP()


void CChargeForRiderTransferDlg::InitPhone()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_Auth_Phone");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return ;

	CString strAuthPhone1;
	CString strAuthPhone2;

	pRs.GetFieldValue("sAuthPhone1", strAuthPhone1);
	pRs.GetFieldValue("sAuthPhone2", strAuthPhone2);

	m_rdoAuth1.SetWindowText(strAuthPhone1);
	m_rdoAuth2.SetWindowText(strAuthPhone2);
}

void CChargeForRiderTransferDlg::InitData()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_for_ride_detail");
	cmd.AddParameter(m_nID);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() <= 0)
		return;

	long nRiderCompany, nRNo, nCharge;
	CString strRName;

	rs.GetFieldValue("nRiderCompany", nRiderCompany);
	rs.GetFieldValue("nRNo", nRNo);
	rs.GetFieldValue("sRName", strRName);
	rs.GetFieldValue("nCharge", nCharge);

	m_edtCompany.SetWindowText(m_ci.GetShareCompanyName(nRiderCompany));
	m_edtRNo.SetWindowText(::GetStringFromLong(nRNo));
	m_edtName.SetWindowText(strRName);
	m_edtCharge.SetWindowText(::GetMyNumberFormat(nCharge));
}

BOOL CChargeForRiderTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitPhone();
	InitData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeForRiderTransferDlg::OnBnClickedChargeForBtn()
{
	if(!m_bSmsAuth)
	{
		MessageBox("SMS인증이 되지 않았습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strEtc;
	m_edtEtc.GetWindowText(strEtc);

	CMkCommand cmd(m_pMkDb, "transfer_charge_for_rider_1");
	cmd.AddParameter(m_nID);
	cmd.AddParameter(strEtc);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *parOutput = cmd.AddParameter(typeString, typeOutput, 100, "");

	if(!cmd.Execute())
		return;

	CString strOutput;
	parOutput->GetValue(strOutput);

	if(!strOutput.IsEmpty())
	{
		MessageBox(strOutput, "확인", MB_ICONINFORMATION);
		return;
	}
	
	OnOK();
}

void CChargeForRiderTransferDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CChargeForRiderTransferDlg::OnBnClickedSendSmsBtn()
{
	if(m_bSmsAuth)
	{
		MessageBox("이미 SMS인증은 받으셨습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strPhone; 

	if(m_rdoAuth1.GetCheck())
		m_rdoAuth1.GetWindowText(strPhone);
	else if(m_rdoAuth2.GetCheck())
		m_rdoAuth2.GetWindowText(strPhone);

	strPhone.Replace("-", "");

	if(!::IsMobilePhoneNumber(strPhone))
	{
		MessageBox("휴대폰 번호가 정확하지 않습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand cmd(m_pMkDb, "send_sms_for_charge_rider");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(strPhone);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *pID = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute())
		return;
	
	pID->GetValue(m_nSmsID);

	MessageBox("SMS가 전송되었습니다", "확인", MB_ICONINFORMATION);
}

void CChargeForRiderTransferDlg::OnBnClickedAuthBtn()
{
	if(m_nSmsID <= 0)
	{
		MessageBox("SMS전송 버튼을 눌려 인증번호를 요청하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strAuthNumber;
	m_edtAuthNumber.GetWindowText(strAuthNumber);

	CMkCommand cmd(m_pMkDb, "update_sms_for_charge_rider");
	cmd.AddParameter(m_nSmsID);
	cmd.AddParameter(strAuthNumber);
	CMkParameter *parOutput = cmd.AddParameter(typeString, typeOutput, 100, "");

	if(!cmd.Execute())
		return;

	CString strOutput; parOutput->GetValue(strOutput);

	if(!strOutput.IsEmpty())
	{
		MessageBox(strOutput, "확인", MB_ICONINFORMATION);
		return;
	}

	MessageBox("SMS인증 되었습니다", "확인", MB_ICONINFORMATION);
	m_bSmsAuth = TRUE;
	m_btnAuth.EnableWindow(FALSE);
}
