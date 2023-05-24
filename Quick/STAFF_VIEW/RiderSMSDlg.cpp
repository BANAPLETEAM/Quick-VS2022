// RiderSMSDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderSMSDlg.h"


// CRiderSMSDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderSMSDlg, CMyDialog)
CRiderSMSDlg::CRiderSMSDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderSMSDlg::IDD, pParent)
, m_sBarance(_T(""))
, m_sSMSCount(_T(""))
{
	m_nCompany = 0;
}

CRiderSMSDlg::~CRiderSMSDlg()
{
}

void CRiderSMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RIDER_PN_EDIT, m_strRiderPN);
	DDX_Text(pDX, IDC_MSG_EDIT, m_strMsg);
	DDX_Text(pDX, IDC_COUNT_STATIC, m_strCount);
	DDX_Control(pDX, IDC_MSG_EDIT, m_MsgEdit);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_CountStatic);
	DDX_Text(pDX, IDC_SMS_BARANCE_STATIC, m_sBarance);
	DDX_Control(pDX, IDOK, m_btnConfirm);

	DDX_Text(pDX, IDC_SMS_COUNT_STATIC, m_sSMSCount);
	DDX_Control(pDX, IDC_PHONE_COMBO, m_cmbPhone);
}


BEGIN_MESSAGE_MAP(CRiderSMSDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
END_MESSAGE_MAP()


// CRiderSMSDlg �޽��� ó�����Դϴ�.
BOOL CRiderSMSDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	ST_SMS_INFO smsi;
	smsi = LF->GetSMSBalance(m_nCompany); 

	m_cmbPhone.InitSmsPhoneNumber(m_nCompany, TYPE_OFFICE_TEL, 160);
	m_cmbPhone.SetReadOnly(TRUE);

	//���ϰ����� �ܾװ� �������� ���Ѵٴ� ���� �ѷ���.	
	UpdateData(TRUE);
	if(smsi.nSMSType >= 10)
	{
		if(smsi.nSMSBarance <= DEFINE_SMS_AMOUNT - 1)
		{
			m_sBarance = LF->GetMyNumberFormat(smsi.nSMSBarance);
			int nCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
			m_sSMSCount.Format("����: %d", nCount);
			m_btnConfirm.EnableWindow(0);
		}
		else
		{
			m_sBarance = LF->GetMyNumberFormat(smsi.nSMSBarance);
			int nSMCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
			m_sSMSCount.Format("����: %s��", LF->GetMyNumberFormat((long)nSMCount));
		}
	}
	else
	{
		m_sBarance = LF->GetMyNumberFormat(smsi.nSMSBarance);		
	}

	m_MsgEdit.SetFontSize(12);
	UpdateData(FALSE);
	OnEnChangeMsgEdit();
	return TRUE;
}


void CRiderSMSDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
 
	if(m_strMsg.GetLength() > 90)
	{	
		MessageBox("���۳����� 90�ڸ� �ʰ��մϴ�. 80���̳��� �ۼ��Ͽ� �ֽñ� �ٶ��ϴ�.", 
			"Ȯ��", MB_ICONINFORMATION);

		return;
	}

	m_strRecvPhone = m_cmbPhone.GetSmsPhoneNumber();

	OnOK();
}

void CRiderSMSDlg::OnEnChangeMsgEdit()
{
	CString strMsg, strCount;
	m_MsgEdit.GetWindowText(strMsg);
	strCount.Format("���ڼ�: %d", strMsg.GetLength());
	m_CountStatic.SetWindowText(strCount);
}

