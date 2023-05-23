// AddPhoneDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "AddPhoneDlg.h"


// CAddPhoneDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddPhoneDlg, CDialog)

CAddPhoneDlg::CAddPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddPhoneDlg::IDD, pParent)
{

}

CAddPhoneDlg::~CAddPhoneDlg()
{
}

void CAddPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_ENTER_EDIT, m_edtEnter);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_MANAGER_EDIT, m_edtManager);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_ID_STATIC, m_stcID);
	DDX_Control(pDX, IDC_PHONE_STATIC, m_stcPhone);
	DDX_Control(pDX, IDC_DEPART_STATIC, m_stcDepart);
	DDX_Control(pDX, IDC_ETC_STATIC, m_stcEtc);
	DDX_Control(pDX, IDC_ENTER_STATIC, m_stcEnter);
	DDX_Control(pDX, IDC_MANAGER_STATIC, m_stcManager);
}


BEGIN_MESSAGE_MAP(CAddPhoneDlg, CDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CAddPhoneDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDCANCEL, &CAddPhoneDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CAddPhoneDlg::CheckItem()
{
	if(m_edtPhone.GetWindowTextLength() <= 0)
	{
		MessageBox("��ȭ��ȣ�� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		m_edtPhone.SetFocus();
		return FALSE;
	}

	return TRUE;	
}

void CAddPhoneDlg::OnBnClickedSaveBtn()
{
	if(!CheckItem())
		return;

	BOOL bOk = FALSE;

	if(m_nTelID > 0)
		bOk = UpdatePhone();
	else
		bOk = InsertPhone();

	if(bOk)
		OnOK();;
}

BOOL CAddPhoneDlg::InsertPhone()
{
	if(MessageBox("����/�Էµ��ڷᰡ �ֽ��ϴ�. ���� �Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
		return FALSE;

	CString strPhone = LF->GetStringFromEdit(&m_edtPhone);
	strPhone = LF->GetNoneDashNumberRemoveDDD(strPhone);

	CMkCommand cmd(m_pMkDb, "insert_phone_info");
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(strPhone);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDepart));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManager));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtEtc));

	return cmd.Execute();
}

BOOL CAddPhoneDlg::UpdatePhone()
{
	if(MessageBox("����/�Էµ��ڷᰡ �ֽ��ϴ�. ���� �Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
		return FALSE;

	CString strPhone = LF->GetStringFromEdit(&m_edtPhone);
	strPhone = LF->GetNoneDashNumberRemoveDDD(strPhone);

	CMkCommand cmd(m_pMkDb, "update_phone_info");
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nTelID);
	cmd.AddParameter(strPhone);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDepart));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManager));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtEtc));

	return cmd.Execute();
}

void CAddPhoneDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

BOOL CAddPhoneDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)		 
		{		
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAddPhoneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtID.SetWindowText(LF->GetStringFromLong(m_nCNo));

	if(m_nTelID > 0)
		RefreshPhoneInfo();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAddPhoneDlg::RefreshPhoneInfo()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_phone_info");
	cmd.AddParameter(m_nTelID); 

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	CString strTemp;
	rs.GetFieldValue("sTel", strTemp); m_edtPhone.SetWindowText(LF->GetDashPhoneNumber(strTemp));
	rs.GetFieldValue("sTelDepart", strTemp); m_edtDepart.SetWindowText(strTemp);
	rs.GetFieldValue("sTelManager", strTemp); m_edtManager.SetWindowText(strTemp);
	rs.GetFieldValue("sTelEtc", strTemp); m_edtEtc.SetWindowText(strTemp);


}