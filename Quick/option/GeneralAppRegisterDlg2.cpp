// GeneralAppRegisterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GeneralAppRegisterDlg2.h"
#include "SMSFileUpload.h"

// CGeneralAppRegisterDlg2 ��ȭ �����Դϴ�.

#define FTP_IP2 "210.127.244.199"

IMPLEMENT_DYNAMIC(CGeneralAppRegisterDlg2, CMyDialog)

CGeneralAppRegisterDlg2::CGeneralAppRegisterDlg2(CWnd* pParent /*=NULL*/)
: CMyDialog(CGeneralAppRegisterDlg2::IDD, pParent)
{
	m_nIndex = 0;
	m_nState = 0;
	m_strBizLicenseUrl = ""; 
}

CGeneralAppRegisterDlg2::~CGeneralAppRegisterDlg2()
{
}

void CGeneralAppRegisterDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_APP_NAME_EDIT, m_edtAppName);
	DDX_Control(pDX, IDC_MAIN_TEL_EDIT, m_edtMainTel);
	DDX_Control(pDX, IDC_EXPLAN_EDIT, m_edtExplan);
	DDX_Control(pDX, IDC_APP_MANAGER_NAME_EDIT, m_edtAppManagerName);
	DDX_Control(pDX, IDC_APP_MANAGER_POSITION_EDIT, m_edtAppManagerPosition);
	DDX_Control(pDX, IDC_APP_MANAGER_TEL_EDIT, m_edtAppManagerTel);
	DDX_Control(pDX, IDC_TAX_MANAGER_NAME_EDIT, m_edtTaxManagerName);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEMail);
	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_edtCompanyName);
	DDX_Control(pDX, IDC_BIZ_NUMBER_EDIT, m_edtBizNumber);
	DDX_Control(pDX, IDC_BIZ_TYPE1_EDIT, m_edtBizType1);
	DDX_Control(pDX, IDC_BIZ_TYPE2_EDIT, m_edtBizType2);
	DDX_Control(pDX, IDC_COMPANY_ADDR_EDIT, m_edtCompanyAddr);
	DDX_Control(pDX, IDC_REGISTER_BTN, m_btnRegister);
	DDX_Control(pDX, IDC_TAX_MANAGER_TEL_EDIT, m_edtTaxManagerTel);
	DDX_Control(pDX, IDC_SHORT_URL_EDIT, m_edtShortUrl);
	DDX_Control(pDX, IDC_STATE_STATIC, m_stcState);
	DDX_Control(pDX, IDC_GOOGLE_ID_EDIT, m_edtGoogleID);
	DDX_Control(pDX, IDC_GOOGLE_PW_EDIT, m_edtGooglePW);	
	DDX_Control(pDX, IDC_BIZ_OWNER_EDIT, m_edtBizOwner);		
	DDX_Control(pDX, IDC_APP_MANAGER_EMAIL_EDIT, m_edtAppManagerEMail);

	DDX_Control(pDX, IDC_ANDROID_CHECK, m_chkAndroid);
	DDX_Control(pDX, IDC_IOS_CHECK, m_chkIOS);	
	DDX_Control(pDX, IDC_APPLE_ID_EDIT, m_edtAppleID);	
	DDX_Control(pDX, IDC_APPLE_PW_EDIT, m_edtApplePW);	
}


BEGIN_MESSAGE_MAP(CGeneralAppRegisterDlg2, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CGeneralAppRegisterDlg2::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_REGISTER_BTN, &CGeneralAppRegisterDlg2::OnBnClickedRegisterBtn)
	ON_BN_CLICKED(IDC_UPLOAD_BTN, &CGeneralAppRegisterDlg2::OnBnClickedUploadBtn)
END_MESSAGE_MAP()


// CGeneralAppRegisterDlg2 �޽��� ó�����Դϴ�.

void CGeneralAppRegisterDlg2::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CGeneralAppRegisterDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CFont *pFont = m_FontManager.GetFont("���� ���", 13, FW_NORMAL);
	SendMessageToDescendants(WM_SETFONT, (WPARAM)pFont->GetSafeHandle(), 1, TRUE, FALSE);

	m_chkAndroid.SetCheck(TRUE);
	m_chkIOS.SetCheck(TRUE);

	if(m_nIndex > 0)
		RefreshDlg();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	if(m_nState == 0)
	{
		SetWindowText("���� ����Ʈ�� ��û");
		m_btnRegister.SetWindowText("��û");
		m_stcState.SetWindowText("���� ����Ʈ���� ��û�ϼ���");
	}
	else //1 -> ��û��, 2 �۵��������
	{
		SetWindowText("���� ����Ʈ�� ����");
		m_btnRegister.SetWindowText("����");

		if(m_nState == 1)
			m_stcState.SetWindowText("��û�� �Ϸ�Ǿ� ����ڰ� Ȯ�����Դϴ�");
		else
			m_stcState.SetWindowText("���� ����Ʈ���� ��Ī�Ǿ����ϴ�");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGeneralAppRegisterDlg2::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "select_generate_app_register_detail_2");
	cmd.AddParameter(m_nIndex);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	CString strAppName, strMainTel, strExplan, strAppManagerName, strAppManagerPosition, strAppManagerTel, strTaxManagerTel;
	CString strTaxManagerName, strEMail, strCompanyName, strBizNumber, strBizType1, strBizType2, strBizLicenseUrl, strCompanyAddr, strShortUrl;
	CString strGoogleID, strGooglePW, strAppManagerEMail;
	CString strBizOwner, strAppleID, strApplePW;
	long nType;

	rs.GetFieldValue("nState", m_nState);
	rs.GetFieldValue("sAppName", strAppName);
	rs.GetFieldValue("sMainTel", strMainTel);
	rs.GetFieldValue("sExplan", strExplan);
	rs.GetFieldValue("sAppManagerName", strAppManagerName);
	rs.GetFieldValue("sAppManagerPosition", strAppManagerPosition);
	rs.GetFieldValue("sAppManagerTel", strAppManagerTel);
	rs.GetFieldValue("sTaxManagerName", strTaxManagerName);
	rs.GetFieldValue("sEMail", strEMail);
	rs.GetFieldValue("sCompanyName", strCompanyName);
	rs.GetFieldValue("sBizNumber", strBizNumber);
	rs.GetFieldValue("sBizType1", strBizType1);
	rs.GetFieldValue("sBizType2", strBizType2);
	rs.GetFieldValue("sBizLicenseUrl", strBizLicenseUrl);
	rs.GetFieldValue("sCompanyAddr", strCompanyAddr);
	rs.GetFieldValue("sBizLicenseUrl", m_strBizLicenseUrl);
	rs.GetFieldValue("sTaxManagerTel", strTaxManagerTel);
	rs.GetFieldValue("sShortUrl", strShortUrl);
	rs.GetFieldValue("sGoogleID", strGoogleID);
	rs.GetFieldValue("sGooglePW", strGooglePW);
	rs.GetFieldValue("sAppleID", strAppleID);
	rs.GetFieldValue("sApplePW", strApplePW);
	rs.GetFieldValue("sBizOwner", strBizOwner);
	rs.GetFieldValue("nType", nType);
	rs.GetFieldValue("sAppManagerEMail", strAppManagerEMail);

	m_edtAppName.SetWindowText(strAppName);
	m_edtMainTel.SetWindowText(strMainTel);
	m_edtExplan.SetWindowText(strExplan);
	m_edtAppManagerName.SetWindowText(strAppManagerName);
	m_edtAppManagerPosition.SetWindowText(strAppManagerPosition);
	m_edtAppManagerTel.SetWindowText(strAppManagerTel);
	m_edtTaxManagerName.SetWindowText(strTaxManagerName);
	m_edtEMail.SetWindowText(strEMail);
	m_edtCompanyName.SetWindowText(strCompanyName);
	m_edtBizNumber.SetWindowText(strBizNumber);
	m_edtBizType1.SetWindowText(strBizType1);
	m_edtBizType2.SetWindowText(strBizType2);
	m_edtCompanyAddr.SetWindowText(strCompanyAddr);
	m_edtTaxManagerTel.SetWindowText(strTaxManagerTel);
	m_edtShortUrl.SetWindowText(strShortUrl);
	m_edtGoogleID.SetWindowText(strGoogleID);
	m_edtGooglePW.SetWindowText(strGooglePW);
	m_edtBizOwner.SetWindowText(strBizOwner);
	m_edtAppManagerEMail.SetWindowText(strAppManagerEMail);
	m_edtAppleID.SetWindowText(strAppleID);
	m_edtApplePW.SetWindowText(strApplePW);

	SetAppType(nType);
}

void CGeneralAppRegisterDlg2::SetAppType(long nType)
{
	if(nType == 0)
	{
		m_chkAndroid.SetCheck(TRUE);
		m_chkIOS.SetCheck(FALSE);
	}
	else if(nType == 1)
	{
		m_chkAndroid.SetCheck(FALSE);
		m_chkIOS.SetCheck(TRUE);
	}
	else if(nType == 2)
	{
		m_chkAndroid.SetCheck(TRUE);
		m_chkIOS.SetCheck(TRUE);
	}
}

long CGeneralAppRegisterDlg2::GetAppType()
{
	if(m_chkAndroid.GetCheck() && m_chkIOS.GetCheck())
		return 2;

	if(m_chkAndroid.GetCheck())
		return 0;

	if(m_chkIOS.GetCheck())
		return 1;

	return -1;
}

void CGeneralAppRegisterDlg2::OnBnClickedRegisterBtn()
{
	//��������
	CString strAppName, strMainTel, strExplan;
	m_edtAppName.GetWindowText(strAppName);
	m_edtMainTel.GetWindowText(strMainTel);
	m_edtExplan.GetWindowText(strExplan);

	if(strAppName.GetLength() == 0 || strMainTel.GetLength() == 0 || strExplan.GetLength() == 0)
	{
		MessageBox("���ø�, ��ǥ��ȭ��ȣ, ���ü��� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//���ô����
	CString strAppManagerName, strAppManagerPosition, strAppManagerTel, strAppManagerEMail;
	m_edtAppManagerName.GetWindowText(strAppManagerName);
	m_edtAppManagerPosition.GetWindowText(strAppManagerPosition);
	m_edtAppManagerTel.GetWindowText(strAppManagerTel);
	m_edtAppManagerEMail.GetWindowText(strAppManagerEMail);

	if(strAppManagerName.GetLength() == 0 || strAppManagerPosition.GetLength() == 0 || strAppManagerTel.GetLength() == 0 || strAppManagerEMail.GetLength() == 0)
	{
		MessageBox("���� ����� �̸�, ��å, �޴���, �̸��� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//���ݰ�꼭 �����
	CString strTaxManagerName, strTaxManagerTel, strEmail;
	m_edtTaxManagerName.GetWindowText(strTaxManagerName);
	m_edtTaxManagerTel.GetWindowText(strTaxManagerTel);
	m_edtEMail.GetWindowText(strEmail);

	if(strTaxManagerName.GetLength() == 0 || strTaxManagerTel.GetLength() == 0 || strEmail.GetLength() == 0)
	{
		MessageBox("���ݰ�꼭 ����� �̸�, �޴���, �̸��� �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	//����� ����
	CString strCompanyName, strBizNumber, strBizType1, strBizType2, strCompanyAddr, strBizOwner;
	m_edtCompanyName.GetWindowText(strCompanyName);
	m_edtBizNumber.GetWindowText(strBizNumber);
	m_edtBizType1.GetWindowText(strBizType1);
	m_edtBizType2.GetWindowText(strBizType2);
	m_edtCompanyAddr.GetWindowText(strCompanyAddr);
	m_edtBizOwner.GetWindowText(strBizOwner);

	if(strCompanyName.GetLength() == 0 || strBizNumber.GetLength() == 0 || strBizType1.GetLength() == 0 || strBizType2.GetLength() == 0 || strCompanyAddr.GetLength() == 0 || strBizOwner.GetLength() == 0)
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

	//���� Ÿ��
	CString strGoogleID, strGooglePW, strAppleID, strApplePW;
	m_edtGoogleID.GetWindowText(strGoogleID);
	m_edtGooglePW.GetWindowText(strGooglePW);
	m_edtAppleID.GetWindowText(strAppleID);
	m_edtApplePW.GetWindowText(strApplePW);

	long nType = GetAppType();

	if(nType < 0)
	{
		MessageBox("�ȵ���̵� Ȥ�� IOS�� üũ �� �ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	else if(nType == 0 && (strGoogleID.GetLength() == 0 || strGooglePW.GetLength() == 0))
	{
		MessageBox("���� ID, PW �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return; 
	}
	else if(nType == 1 && (strAppleID.GetLength() == 0 || strApplePW.GetLength() == 0))
	{
		MessageBox("���� ID, PW �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return; 
	}
	else if(nType == 2 && (strGoogleID.GetLength() == 0 || strGooglePW.GetLength() == 0 || strAppleID.GetLength() == 0 || strApplePW.GetLength() == 0))
	{
		MessageBox("���� �� ���� ID, PW �κ��� �Է����ּ���.", "Ȯ��", MB_ICONINFORMATION);
		return; 
	}

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "insert_generate_app_register_4");

	cmd.AddParameter(m_nIndex);
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtMainTel));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtExplan));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppManagerName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppManagerPosition));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppManagerTel));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtTaxManagerName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtTaxManagerTel));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtEMail));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCompanyName));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizNumber));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizType1));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizType2));
	cmd.AddParameter(m_strBizLicenseUrl);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCompanyAddr));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtGoogleID));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtGooglePW));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppleID));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtApplePW));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtBizOwner));
	cmd.AddParameter(nType);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAppManagerEMail));

	if(cmd.Execute())
	{
		if(m_nState == 0)
			MessageBox("���� ������ ��û�Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		else
			MessageBox("���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);

		OnOK();		
	}
}

void CGeneralAppRegisterDlg2::OnBnClickedUploadBtn()
{
	MessageBox("���� ���ε尡 �����ʽ��ϴ�.\r\n��û �� ��� ���ؼ� ���ε� ���ּ���.", "Ȯ��", MB_ICONINFORMATION);
}
