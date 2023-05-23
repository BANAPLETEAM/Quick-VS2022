// BranchNameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchNameDlg.h"


// CBranchNameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBranchNameDlg, CMyDialog)
CBranchNameDlg::CBranchNameDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CBranchNameDlg::IDD, pParent)
{
}

CBranchNameDlg::~CBranchNameDlg()
{
}

void CBranchNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BRANCH_CODE_EDIT,			m_strBranchCode);
	DDX_Text(pDX, IDC_BRANCH_NAME_EDIT,			m_strBranchName);
	DDX_Text(pDX, IDC_OFFICE_PHONE_EDIT,		m_strOfficePhone);
	DDX_Text(pDX, IDC_CLIENT_SYMBOL_EDIT,		m_strClientSymbol);
	DDX_Text(pDX, IDC_CLIENT_DISPLAY_NAME_EDIT, m_strClientDisplayName);
	DDX_Text(pDX, IDC_CLIENT_DISPLAY_PHONE_EDIT,m_strClientDisplayPhone);
	DDX_Text(pDX, IDC_OFFICE_PHONE_SMS_EDIT,	m_strOfficePhoneSMS);

	DDX_Text(pDX, IDC_TEL_EDIT,					m_strTel);
	DDX_Text(pDX, IDC_TEL_SMS_EDIT,				m_strTelSMS);
}


BEGIN_MESSAGE_MAP(CBranchNameDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CBranchNameDlg �޽��� ó�����Դϴ�.

void CBranchNameDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_strBranchName.IsEmpty()) {
		MessageBox("������� �Է��Ͻñ� �ٶ��ϴ�.", "Ȯ��", MB_ICONEXCLAMATION);
		return;
	}

	if(m_strOfficePhone.IsEmpty()) {
		MessageBox("��Ȳ���� ��ȭ��ȣ�� �Է��ϼ���.", "Ȯ��", MB_ICONEXCLAMATION);
		return;
	}

	m_strOfficePhone.Trim();

	if(!LF->IsStringDigit(m_strOfficePhone.Left(1))){
		MessageBox("��Ȳ���� ��ȭ��ȣ�� �ùٸ��� �ʽ��ϴ�..", "Ȯ��", MB_ICONEXCLAMATION);
		return;
	}
	m_strOfficePhone.Replace("-", "");

	if(m_strPreOfficePhone != m_strOfficePhone)
		MessageBox("���α׷� �� ���ܸ��⿡ ǥ�õǴ� ��Ȳ�ǹ�ȣ�� �����˴ϴ�.\r\n<<���ڹ߽�(ȸ��) ��ȣ>>������ ��������Ʈ�� ��û�Ͽ� �����ϼ���.", "Ȯ��", MB_ICONINFORMATION);

	OnOK();
}

BOOL CBranchNameDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_branch_simple_info_1");
	cmd.AddParameter(m_nCompanyCode);

	if(!rs.Execute(&cmd))
		return TRUE;

	CString strOfficePhone = "", strOfficePhoneSMS = "",strTel = "", strTelSMS = "";

	if(rs.GetRecordCount() == 0)
		return TRUE;

	rs.GetFieldValue("sName", m_strBranchCode);
	rs.GetFieldValue("sBranchName", m_strBranchName);
	rs.GetFieldValue("sOfficePhone", strOfficePhone);
	rs.GetFieldValue("sClientSymbol", m_strClientSymbol);
	rs.GetFieldValue("sDisplayName", m_strClientDisplayName);
	rs.GetFieldValue("sDisplayPhone", m_strClientDisplayPhone);

	rs.GetFieldValue("sTel", strTel);
	rs.GetFieldValue("sOfficePhoneSMS", strOfficePhoneSMS);
	rs.GetFieldValue("sTelSMS", strTelSMS);

	m_strTel = LF->GetDashPhoneNumber(strTel);
	m_strTelSMS	= LF->GetDashPhoneNumber(strTelSMS);

	strOfficePhone.Replace("-", "");
	m_strPreOfficePhone = strOfficePhone;

	m_strOfficePhone = LF->GetDashPhoneNumber(strOfficePhone );
	m_strOfficePhoneSMS = LF->GetDashPhoneNumber(strOfficePhoneSMS );

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
