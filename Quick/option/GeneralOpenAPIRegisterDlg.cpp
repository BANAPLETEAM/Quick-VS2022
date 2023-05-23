// GenerateOpenAPIRegisterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GeneralOpenAPIRegisterDlg.h"
// CGenerateOpenAPIRegisterDlg ��ȭ �����Դϴ�.

#define FTP_IP2 "210.127.244.199"

IMPLEMENT_DYNAMIC(CGenerateOpenAPIRegisterDlg, CMyDialog)

CGenerateOpenAPIRegisterDlg::CGenerateOpenAPIRegisterDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CGenerateOpenAPIRegisterDlg::IDD, pParent)
{
	m_nIndex = 0;
	m_nState = 0;
	m_strBizLicenseUrl = ""; 
}

CGenerateOpenAPIRegisterDlg::~CGenerateOpenAPIRegisterDlg()
{
}

void CGenerateOpenAPIRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_APP_MANAGER_NAME_EDIT, m_edtManagerName);
	DDX_Control(pDX, IDC_APP_MANAGER_POSITION_EDIT, m_edtManagerPosition);
	DDX_Control(pDX, IDC_APP_MANAGER_TEL_EDIT, m_edtManagerTel);
	DDX_Control(pDX, IDC_APP_MANAGER_EMAIL_EDIT, m_edtManagerEMail);

	DDX_Control(pDX, IDC_TAX_MANAGER_NAME_EDIT, m_edtTaxManagerName);
	DDX_Control(pDX, IDC_TAX_MANAGER_TEL_EDIT, m_edtTaxManagerTel);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtTaxManagerEMail);

	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_edtBizName);
	DDX_Control(pDX, IDC_BIZ_NUMBER_EDIT, m_edtBizNumber);
	DDX_Control(pDX, IDC_BIZ_OWNER_EDIT, m_edtBizOwner);		
	DDX_Control(pDX, IDC_BIZ_TYPE1_EDIT, m_edtBizType1);
	DDX_Control(pDX, IDC_BIZ_TYPE2_EDIT, m_edtBizType2);
	DDX_Control(pDX, IDC_COMPANY_ADDR_EDIT, m_edtBizAddr);

	DDX_Control(pDX, IDC_REGISTER_BTN, m_btnRegister);
	DDX_Control(pDX, IDC_STATE_STATIC, m_stcState);
}


BEGIN_MESSAGE_MAP(CGenerateOpenAPIRegisterDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CGenerateOpenAPIRegisterDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_REGISTER_BTN, &CGenerateOpenAPIRegisterDlg::OnBnClickedRegisterBtn)
	ON_BN_CLICKED(IDC_UPLOAD_BTN, &CGenerateOpenAPIRegisterDlg::OnBnClickedUploadBtn)
END_MESSAGE_MAP()


// CGenerateOpenAPIRegisterDlg �޽��� ó�����Դϴ�.

void CGenerateOpenAPIRegisterDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CGenerateOpenAPIRegisterDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CFont *pFont = m_FontManager.GetFont("���� ���", 13, FW_NORMAL);
	SendMessageToDescendants(WM_SETFONT, (WPARAM)pFont->GetSafeHandle(), 1, TRUE, FALSE);

	if(m_nIndex > 0)
		RefreshDlg();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	if(m_nState == 0)
	{
		SetWindowText("����API ��û");
		m_btnRegister.SetWindowText("��û");
		m_stcState.SetWindowText("����API�� ��û�ϼ���");
	}
	else //1 -> ��û��, 2 ���������
	{
		SetWindowText("����API ����");
		m_btnRegister.SetWindowText("����");

		if(m_nState == 1)
			m_stcState.SetWindowText("��û�� �Ϸ�Ǿ� ����ڰ� Ȯ�����Դϴ�");
		else
			m_stcState.SetWindowText("����API�� �߱� �Ǿ����ϴ�");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGenerateOpenAPIRegisterDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "dbo.select_openapi_register_detail");
	cmd.AddParameter(m_nIndex);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	CString strManagerName, strManagerPosition, strManagerTel, strManagerEMail;

	CString strTaxManagerName, strTaxManagerTel, strTaxManagerEMail;
	CString strBizName, strBizNumber, strBizType1, strBizType2, strBizLicenseUrl, strBizAddr, strBizOwner;

	rs.GetFieldValue("nState", m_nState);
	rs.GetFieldValue("sOpenAPIManagerName", strManagerName);
	rs.GetFieldValue("sOpenAPIManagerPosition", strManagerPosition);
	rs.GetFieldValue("sOpenAPIManagerTel", strManagerTel);
	rs.GetFieldValue("sOpenAPIManagerEMail", strManagerEMail);

	rs.GetFieldValue("sTaxManagerName", strTaxManagerName);
	rs.GetFieldValue("sTaxManagerTel", strTaxManagerTel);
	rs.GetFieldValue("sTaxManagerEMail", strTaxManagerEMail);
	
	rs.GetFieldValue("sBizName", strBizName);
	rs.GetFieldValue("sBizNumber", strBizNumber);
	rs.GetFieldValue("sBizType1", strBizType1);
	rs.GetFieldValue("sBizType2", strBizType2);
	rs.GetFieldValue("sBizLicenseUrl", strBizLicenseUrl);
	rs.GetFieldValue("sBizAddr", strBizAddr);
	rs.GetFieldValue("sBizLicenseUrl", m_strBizLicenseUrl);
	rs.GetFieldValue("sBizOwner", strBizOwner);
		
	m_edtManagerName.SetWindowText(strManagerName);
	m_edtManagerPosition.SetWindowText(strManagerPosition);
	m_edtManagerTel.SetWindowText(strManagerTel);
	m_edtManagerEMail.SetWindowText(strManagerEMail);
	
	m_edtTaxManagerName.SetWindowText(strTaxManagerName);
	m_edtTaxManagerTel.SetWindowText(strTaxManagerTel);
	m_edtTaxManagerEMail.SetWindowText(strTaxManagerEMail);
	
	m_edtBizName.SetWindowText(strBizName);
	m_edtBizNumber.SetWindowText(strBizNumber);
	m_edtBizType1.SetWindowText(strBizType1);
	m_edtBizType2.SetWindowText(strBizType2);
	m_edtBizOwner.SetWindowText(strBizOwner);
	m_edtBizAddr.SetWindowText(strBizAddr);
}

void CGenerateOpenAPIRegisterDlg::OnBnClickedRegisterBtn()
{
	//�����
	CString strManagerName, strManagerPosition, strManagerTel, strManagerEMail;
	m_edtManagerName.GetWindowText(strManagerName);
	m_edtManagerPosition.GetWindowText(strManagerPosition);
	m_edtManagerTel.GetWindowText(strManagerTel);
	m_edtManagerEMail.GetWindowText(strManagerEMail);

	if(strManagerName.GetLength() == 0 || strManagerPosition.GetLength() == 0 || strManagerTel.GetLength() == 0 || strManagerEMail.GetLength() == 0)
	{
		MessageBox("����� �̸�, ��å, �޴���, �̸��� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//���ݰ�꼭 �����
	CString strTaxManagerName, strTaxManagerTel, strTaxManagerEmail;
	m_edtTaxManagerName.GetWindowText(strTaxManagerName);
	m_edtTaxManagerTel.GetWindowText(strTaxManagerTel);
	m_edtTaxManagerEMail.GetWindowText(strTaxManagerEmail);

	if(strTaxManagerName.GetLength() == 0 || strTaxManagerTel.GetLength() == 0 || strTaxManagerEmail.GetLength() == 0)
	{
		MessageBox("���ݰ�꼭 ����� �̸�, �޴���, �̸��� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//����� ����
	CString strBizName, strBizNumber, strBizType1, strBizType2, strBizAddr, strBizOwner;
	m_edtBizName.GetWindowText(strBizName);
	m_edtBizNumber.GetWindowText(strBizNumber);
	m_edtBizType1.GetWindowText(strBizType1);
	m_edtBizType2.GetWindowText(strBizType2);
	m_edtBizAddr.GetWindowText(strBizAddr);
	m_edtBizOwner.GetWindowText(strBizOwner);

	if(strBizName.GetLength() == 0 || strBizNumber.GetLength() == 0 || strBizType1.GetLength() == 0 || strBizType2.GetLength() == 0 || strBizAddr.GetLength() == 0 || strBizOwner.GetLength() == 0)
	{
		MessageBox("����� ���� ��ȣ, ��Ϲ�ȣ, ����, ����, ��ǥ�ڸ�, �ּ� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	/* ���� ���ε尡 �����ʽ��ϴ�
	if(m_strBizLicenseUrl.IsEmpty())
	{
		MessageBox("����ڵ������ ���ε� �Ŀ� �ٽ� �õ��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	*/

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "insert_openapi_register");

	cmd.AddParameter(m_nIndex);
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManagerName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManagerPosition));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManagerTel));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManagerEMail));

	cmd.AddParameter(LF->GetStringFromEdit(&m_edtTaxManagerName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtTaxManagerTel));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtTaxManagerEMail));
	
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizNumber));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizOwner));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizType1));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizType2));
	cmd.AddParameter(m_strBizLicenseUrl);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizAddr));
	
	if(cmd.Execute())
	{
		if(m_nState == 0)
			MessageBox("����API�� ��û�Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		else
			MessageBox("���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);

		OnOK();		
	}
}

void CGenerateOpenAPIRegisterDlg::OnBnClickedUploadBtn()
{
	MessageBox("���� ���ε尡 �����ʽ��ϴ�.\r\n��û �� ��� ���ؼ� ���ε� ���ּ���.", "Ȯ��", MB_ICONINFORMATION);
}

