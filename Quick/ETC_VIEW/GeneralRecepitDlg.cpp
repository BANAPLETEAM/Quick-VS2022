// BillDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GeneralRecepitDlg.h"
#include "GeneralReceiptLogDlg.h"


// CGeneralReceiptDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGeneralReceiptDlg, CMyDialog)
CGeneralReceiptDlg::CGeneralReceiptDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGeneralReceiptDlg::IDD, pParent)
{
	m_nID = 0;
}

CGeneralReceiptDlg::~CGeneralReceiptDlg()
{
}

void CGeneralReceiptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMPANY_NAME_EDIT, m_strCompanyName);
	DDX_Text(pDX, IDC_COMPANY_OWNER_EDIT, m_strCompanyOwner);
	DDX_Text(pDX, IDC_COMPANY_BIZ_TYPE_EDIT1, m_strCompanyBizType1);
	DDX_Text(pDX, IDC_COMPANY_BIZ_TYPE_EDIT2, m_strCompanyBizType2);
	DDX_Text(pDX, IDC_COMPANY_BIZ_NO_EDIT, m_strCompanyBizNo);
	DDX_Text(pDX, IDC_COMPANY_ADDRESS_EDIT, m_strCompanyAddress);
	DDX_Text(pDX, IDC_REQUEST_COUNT_EDIT, m_strRequestCount);
	DDX_Text(pDX, IDC_USE_MONTH_EDIT, m_strUseMonth);	
	DDX_Text(pDX, IDC_ONAME_EDIT, m_strOName);
	DDX_Text(pDX, IDC_OPHONE_EDIT, m_strOPhone);
	DDX_Text(pDX, IDC_OADDRESS_EDIT, m_strOAddress);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
}


BEGIN_MESSAGE_MAP(CGeneralReceiptDlg, CMyDialog)

	ON_BN_CLICKED(IDC_SUBSCRIPT_BTN, OnBnClickedSubscriptBtn)
	ON_BN_CLICKED(IDC_SHOW_LOG_BTN, OnBnClickedShowLogBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	
	ON_BN_CLICKED(IDC_PRE_SHOW_BTN, &CGeneralReceiptDlg::OnBnClickedPreShowBtn)
END_MESSAGE_MAP()


// CGeneralReceiptDlg �޽��� ó�����Դϴ�.

BOOL CGeneralReceiptDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_nID > 0)
	{
		GetDlgItem(IDC_SUBSCRIPT_BTN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHOW_LOG_BTN)->EnableWindow(FALSE);

		RefreshDlg();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGeneralReceiptDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_general_receipt_subscript");
	cmd.AddParameter(m_nID);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	long nRequestCount, nUseMonth;

	rs.GetFieldValue("sCompanyName", m_strCompanyName);
	rs.GetFieldValue("sCompanyOwner", m_strCompanyOwner);
	rs.GetFieldValue("sCompanyBizType1", m_strCompanyBizType1);
	rs.GetFieldValue("sCompanyBizType2", m_strCompanyBizType2);
	rs.GetFieldValue("sCompanyBizNo", m_strCompanyBizNo);
	rs.GetFieldValue("sCompanyAddress", m_strCompanyAddress);
	rs.GetFieldValue("nRequestCount", nRequestCount);
	rs.GetFieldValue("nUseMonth", nUseMonth);
	rs.GetFieldValue("sOName", m_strOName);
	rs.GetFieldValue("sOPhone", m_strOPhone);
	rs.GetFieldValue("sOAddress", m_strOAddress);
	rs.GetFieldValue("sEtc", m_strEtc);

	m_strRequestCount = LF->GetStringFromLong(nRequestCount, FALSE);
	m_strUseMonth = LF->GetStringFromLong(nUseMonth, FALSE);
	m_strOPhone = LF->GetMyNumberFormat(m_strOPhone);

	UpdateData(FALSE);
}

BOOL CGeneralReceiptDlg::CheckDupRequest()
{
	CMkCommand cmd(m_pMkDb, "check_general_receipt_subscript");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *parOut = cmd.AddParameter(typeString, typeOutput, 200, "");

	if(!cmd.Execute())
		return FALSE;

	CString strOutPut; parOut->GetValue(strOutPut);

	if(strOutPut.IsEmpty())
		return TRUE;

	if(MessageBox(strOutPut, "Ȯ��", MB_OKCANCEL) == IDOK)
		return TRUE;

	return FALSE;
}

BOOL CGeneralReceiptDlg::CheckData()
{
	if(m_strCompanyName.IsEmpty()) {MessageBox("��ü���� �Է��ϼ���"); return FALSE;}
	if(m_strCompanyOwner.IsEmpty()) {MessageBox("��ǥ�ڸ��� �Է��ϼ���"); return FALSE;}
	if(m_strCompanyBizType1.IsEmpty()) {MessageBox("������ �Է��ϼ���"); return FALSE;}
	if(m_strCompanyBizType2.IsEmpty()) {MessageBox("���¸� �Է��ϼ���"); return FALSE;}
	if(m_strCompanyBizNo.IsEmpty()) {MessageBox("����� ��Ϲ�ȣ�� �Է��ϼ���"); return FALSE;}
	if(m_strCompanyAddress.IsEmpty()) {MessageBox("����� �ּҸ� �Է��ϼ���"); return FALSE;}
	//if(m_strRequestCount.IsEmpty()) {MessageBox("������ ��� ���󹰷��� �Է��ϼ���"); return FALSE;}
	//if(m_strUseMonth.IsEmpty()) {MessageBox("������ ����ֱ⸦ �Է��ϼ���"); return FALSE;}
	if(m_strOName.IsEmpty()) {MessageBox("�Ƿ��ڸ��� �Է��ϼ���"); return FALSE;}
	if(m_strOPhone.IsEmpty()) {MessageBox("������ ����ֱ⸦ �Է��ϼ���"); return FALSE;}
	if(m_strOAddress.IsEmpty()) {MessageBox("������ ��۹��� �ּҸ� �Է��ϼ���"); return FALSE;}

	return TRUE;
}

void CGeneralReceiptDlg::OnBnClickedSubscriptBtn()
{
	UpdateData(TRUE); 

	if(!CheckData())
		return;

	if(!CheckDupRequest())
		return;

	CMkCommand cmd(m_pMkDb, "insert_general_receipt_subscript");
	cmd.AddParameter(m_strCompanyName);
	cmd.AddParameter(m_strCompanyOwner);
	cmd.AddParameter(m_strCompanyBizType1);
	cmd.AddParameter(m_strCompanyBizType2);
	cmd.AddParameter(m_strCompanyBizNo);
	cmd.AddParameter(m_strCompanyAddress);
	cmd.AddParameter(atoi(m_strRequestCount));
	cmd.AddParameter(atoi(m_strUseMonth));
	cmd.AddParameter(m_strOName);
	cmd.AddParameter(m_strOPhone);
	cmd.AddParameter(m_strOAddress);
	cmd.AddParameter(m_strEtc);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(!cmd.Execute())
		return;

	MessageBox("���뿵���� ��û�� �Ϸ�Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
	OnOK();
}

void CGeneralReceiptDlg::OnBnClickedShowLogBtn()
{
	CGeneralReceiptLogDlg dlg;
	dlg.DoModal();
}

void CGeneralReceiptDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CGeneralReceiptDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && 
		pMsg->wParam == VK_RETURN)
	{
		long nID = ::GetDlgCtrlID(pMsg->hwnd);

		if(nID == IDC_COMPANY_NAME_EDIT) GetDlgItem(IDC_COMPANY_OWNER_EDIT)->SetFocus();
		if(nID == IDC_COMPANY_OWNER_EDIT) GetDlgItem(IDC_COMPANY_BIZ_TYPE_EDIT1)->SetFocus();
		if(nID == IDC_COMPANY_BIZ_TYPE_EDIT1) GetDlgItem(IDC_COMPANY_BIZ_TYPE_EDIT2)->SetFocus();
		if(nID == IDC_COMPANY_BIZ_TYPE_EDIT2) GetDlgItem(IDC_COMPANY_BIZ_NO_EDIT)->SetFocus();
		if(nID == IDC_COMPANY_BIZ_NO_EDIT) GetDlgItem(IDC_COMPANY_ADDRESS_EDIT)->SetFocus();
		if(nID == IDC_COMPANY_ADDRESS_EDIT) GetDlgItem(IDC_REQUEST_COUNT_EDIT)->SetFocus();
		if(nID == IDC_REQUEST_COUNT_EDIT) GetDlgItem(IDC_USE_MONTH_EDIT)->SetFocus();
		if(nID == IDC_USE_MONTH_EDIT) GetDlgItem(IDC_ONAME_EDIT)->SetFocus();
		if(nID == IDC_ONAME_EDIT) GetDlgItem(IDC_OPHONE_EDIT)->SetFocus();
		if(nID == IDC_OPHONE_EDIT) GetDlgItem(IDC_OADDRESS_EDIT)->SetFocus();
		if(nID == IDC_OADDRESS_EDIT) GetDlgItem(IDC_ETC_EDIT)->SetFocus();
		if(nID == IDC_ETC_EDIT) GetDlgItem(IDC_SUBSCRIPT_BTN)->SetFocus();
		
		return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CGeneralReceiptDlg::OnBnClickedPreShowBtn()
{
	ShellExecute(NULL, "open", "msedge.exe", "http://logisoft.co.kr/qCloud.html", "", SW_SHOW);
}
