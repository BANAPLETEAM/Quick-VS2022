// NewCertifyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "NewCertifyDlg.h"

// CNewCertifyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNewCertifyDlg, CMyDialog)
CNewCertifyDlg::CNewCertifyDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CNewCertifyDlg::IDD, pParent)
{
	m_nLogNo = 0;
}

CNewCertifyDlg::~CNewCertifyDlg()
{
}

void CNewCertifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
	DDX_Control(pDX, IDC_PW_EDIT, m_edtPW);
	DDX_Control(pDX, IDC_RECV_PHONE_EDIT, m_edtRecvPhone);
	DDX_Control(pDX, IDC_MANAGER_CHECK, m_chkManager);
	DDX_Control(pDX, IDC_CERTIFY_EDIT, m_edtCertify);
	DDX_Control(pDX, IDC_CERTIFY_BTN, m_btnCertify);
	DDX_Control(pDX, IDC_PC_NUM_EDIT, m_edtPCNum);
	DDX_Control(pDX, IDC_RECV_BTN, m_btnRecv);

	DDX_Text(pDX, IDC_ID_EDIT, m_strID);
	DDX_Text(pDX, IDC_PW_EDIT, m_strPW);
	DDX_Text(pDX, IDC_RECV_PHONE_EDIT, m_strRecvPhone);
	DDX_Check(pDX, IDC_MANAGER_CHECK, m_bManager);
	DDX_Text(pDX, IDC_CERTIFY_EDIT, m_strCertify);
	DDX_Text(pDX, IDC_PC_NUM_EDIT, m_strPCNum);
}


BEGIN_MESSAGE_MAP(CNewCertifyDlg, CMyDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RECV_BTN, OnBnClickedRecvBtn)
	ON_BN_CLICKED(IDC_CERTIFY_BTN, OnBnClickedCertifyBtn)
END_MESSAGE_MAP()


// CNewCertifyDlg �޽��� ó�����Դϴ�.


BOOL CNewCertifyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	RefreshPCNum();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}



void CNewCertifyDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void CNewCertifyDlg::OnBnClickedRecvBtn()
{
	UpdateData(TRUE);

	LF->GetMacAddress();
	CString strInternalIP = LF->GetHostName();
	CString strHddID = LF->GetHddId();
	CString strProgramKey = "manager2008_2984345";
	m_ei.strMac1.Trim();
	m_ei.strMac2.Trim();
	strHddID.Trim();

	CMkCommand pCmd(m_pMkDb, "make_certify_phone_sms", TRUE);
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeString, typeInput, m_strID.GetLength(), m_strID);
	pCmd.AddParameter(typeString, typeInput, m_strPW.GetLength(), m_strPW);
	pCmd.AddParameter(typeString, typeInput, m_strRecvPhone.GetLength(), m_strRecvPhone);
	pCmd.AddParameter(typeString, typeInput, strHddID.GetLength(), strHddID);
	pCmd.AddParameter(typeString, typeInput, m_ei.strMac1.GetLength(), m_ei.strMac1);
	pCmd.AddParameter(typeString, typeInput, m_ei.strMac2.GetLength(), m_ei.strMac2);
	pCmd.AddParameter(typeString, typeInput, strInternalIP.GetLength(), strInternalIP);
	CMkParameter *parIP = pCmd.AddParameter(typeString, typeInputOutput, (int)strlen(DB_SUBTYPE_IP), DB_SUBTYPE_IP);
	pCmd.AddParameter(typeString, typeInput, strProgramKey.GetLength(), strProgramKey);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bManager);
	CMkParameter *parPCNum = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parLogNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(pCmd.Execute())
	{
		long nRet = parRet->GetLong();
		if(nRet == 1)
		{
			m_ei.nPCNum = parPCNum->GetLong();
			m_nLogNo = parLogNo->GetLong();
			AfxGetApp()->WriteProfileInt("manager2008", "ClientNo", m_ei.nPCNum);
			RefreshPCNum();
			m_btnRecv.EnableWindow(FALSE);
			m_btnCertify.EnableWindow(TRUE);
			MessageBox("�޴������� ������ȣ�� ���۵Ǿ����ϴ�.", "��������", MB_ICONINFORMATION);
		}
		else
		{
			Sleep(1000);
			if(nRet == 10)
			{
				MessageBox("���̵�/��й�ȣ�� ��ġ���� �ʽ��ϴ�.", "Ȯ��", MB_ICONEXCLAMATION);
			}
			else if(nRet == 20)
			{
				MessageBox("������ ������ ��쿡 �����ھ��̵� �Է��ϼž� �մϴ�.", "Ȯ��", MB_ICONEXCLAMATION);
			}
			else if(nRet == 30)
			{
				MessageBox("��ϵ� ������ȭ��ȣ�� ��ġ���� �ʴ� �޴�����ȣ�� �Է��ϼ̽��ϴ�.", "Ȯ��", MB_ICONEXCLAMATION);
			}
		}
	}

}

void CNewCertifyDlg::OnBnClickedCertifyBtn()
{
	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "check_certify_phone", TRUE);
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeString, typeInput, m_strID.GetLength(), m_strID);
	pCmd.AddParameter(typeString, typeInput, m_strPW.GetLength(), m_strPW);
	pCmd.AddParameter(typeString, typeInput, m_strRecvPhone.GetLength(), m_strRecvPhone);
	pCmd.AddParameter(typeString, typeInput, m_strCertify.GetLength(), m_strCertify);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nLogNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ei.nPCNum);
	CMkParameter *parRegKey = pCmd.AddParameter(typeString, typeOutput, 20, "");

	if(pRs.Execute(&pCmd))
	{
		int nRet = parRet->GetLong();

		if(nRet == 1)
		{
			CString strRegKey;
			parRegKey->GetValue(strRegKey);			
			AfxGetApp()->WriteProfileString("manager2008", "test", strRegKey);		
			

			MessageBox("���������� �����Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		}
		else 
		{
			MessageBox("����Ű�� ���� �ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			Sleep(1000);
		}
	}
}

void CNewCertifyDlg::RefreshPCNum()
{
	char buffer[10];
	m_ei.nPCNum = AfxGetApp()->GetProfileInt("manager2008", "ClientNo", 0);
	if(m_ei.nPCNum == 0)
		m_edtPCNum.SetWindowText("N/A");
	else
		m_edtPCNum.SetWindowText(ltoa(m_ei.nPCNum, buffer, 10));
}


BOOL CNewCertifyDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if(pMsg->hwnd == m_edtRecvPhone.GetSafeHwnd())
		{
			OnBnClickedRecvBtn();
		}
		else if(pMsg->hwnd == m_edtCertify.GetSafeHwnd())
		{
			OnBnClickedCertifyBtn();
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CNewCertifyDlg::OnOK()
{
	//CMyDialog::OnOK();
}
