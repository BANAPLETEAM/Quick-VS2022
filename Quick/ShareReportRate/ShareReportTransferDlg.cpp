// ShareReportTransferDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportTransferDlg.h"

#include "ShareReportAuthPhoneDlg.h"
#include "ShareTranferRequestDlg.h"
#include "ShareReportRateDlg1.h"


// CShareReportTransferDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareReportTransferDlg, CMyDialog)
CShareReportTransferDlg::CShareReportTransferDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportTransferDlg::IDD, pParent)
{
	m_nAbilityMoney = 0;
    m_nSMSID = 0;	
	m_pShareTransferRequestDlg = NULL;
	m_sMoneyR = "";
	m_sMemoR = "";
}

CShareReportTransferDlg::~CShareReportTransferDlg()
{
	m_pShareTransferRequestDlg = NULL;
}

void CShareReportTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_MONEY_STC, m_SendMoneyStc);
	DDX_Control(pDX, IDC_SEND_MONEY_EDIT, m_SendMoneyEdt);
	DDX_Control(pDX, IDC_MEMO_EDT, m_MemoEdt);
	DDX_Control(pDX, IDC_SMS_NUMBER_EDIT, m_SmsNumberEdt);
	DDX_Control(pDX, IDC_ABILITY_MONEY_EDIT, m_AbilityMoneyEdt);
	DDX_Control(pDX, DC_COMPANY_NAME_EDIT, m_CompanyNameEdt);
}


BEGIN_MESSAGE_MAP(CShareReportTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDC_AUTH_BTN, OnBnClickedAuthBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SEND_MONEY_EDIT, OnEnChangeSendMoneyEdit)
END_MESSAGE_MAP()


// CShareReportTransferDlg �޽��� ó�����Դϴ�.



BOOL CShareReportTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_SendMoneyEdt.SetLimitText(6);

	CString str;
	str.Format("%d", m_nAbilityMoney);

	m_AbilityMoneyEdt.SetWindowText(str);
	m_CompanyNameEdt.SetWindowText(m_ci.GetName(m_nToCompany));

	m_SendMoneyEdt.SetWindowText(m_sMoneyR);
	m_MemoEdt.SetWindowText(m_sMemoR);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CShareReportTransferDlg::OnBnClickedAuthBtn()
{
	CShareReportAuthPhoneDlg pDlg;
	pDlg.m_pShareReportTransferDlg = this;
	pDlg.DoModal();
}
void CShareReportTransferDlg::OnBnClickedOk()
{
	UpdateData(true);

	CString strAbilityMoney, strSendMoney;

	m_AbilityMoneyEdt.GetWindowText(strAbilityMoney);
	m_SendMoneyEdt.GetWindowText(strSendMoney);

	strAbilityMoney.Replace("��",",");

	if(_ttoi(strSendMoney) > _ttoi(strAbilityMoney))
	{
		MessageBox("��ü ���� �ݾ׺��� ���� ������ �����ϴ�.", "Ȯ��", MB_ICONERROR);
		return;
	}

	if(_ttoi(strSendMoney) > 300000)
	{
		MessageBox("��ʸ��� �̻� ���� �� �����ϴ�", "Ȯ��", MB_ICONERROR);
		return;
	} 
	
	if(_ttoi(strSendMoney) < 0)
	{
		MessageBox("0�� ���ϴ� ���� �� �����ϴ�", "Ȯ��", MB_ICONERROR);
		return;
	} 	

	if(m_nSMSID == 0)
	{
		MessageBox("��ü ���� ��û��ư�� ���� ������ ��������", "Ȯ��", MB_ICONERROR);
		return;
	}
	
	CString sSendCharege, sMemo, sSMSNumber;
	int nReturn;

	m_SendMoneyEdt.GetWindowText(sSendCharege);

	m_MemoEdt.GetWindowText(sMemo);
	m_SmsNumberEdt.GetWindowText(sSMSNumber);

	if(sMemo.GetLength() > 100)
	{
		MessageBox("��ü ������ 100�� ���Ϸ� ���ּ���.", "Ȯ��", MB_ICONERROR);
		return;
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_share_report_transfer");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSMSID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), atoi(sSendCharege));
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeString, typeInput, sSMSNumber.GetLength(), sSMSNumber);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nToCompany);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nReturn);
	if(nReturn == 111)
	{
		if(m_pShareTransferRequestDlg != NULL) //��ü ��û������ ȣ��Ǿ������
		{
			m_pShareTransferRequestDlg->FinishRequest(_ttoi(sSendCharege), sMemo);
		}

		MessageBox("���������� ��ü�Ǿ����ϴ�", "Ȯ��" ,MB_ICONINFORMATION);
	}
	else if(nReturn == 222)
		MessageBox("3���� �ʰ��Ǿ����ϴ�", "Ȯ��" ,MB_ICONERROR);
	else if(nReturn == 333)
		MessageBox("������ȣ�� Ʋ���ϴ�", "Ȯ��" ,MB_ICONERROR);
	else if(nReturn == 444)
		MessageBox("�̹� ���۵Ǿ����ϴ�", "Ȯ��" ,MB_ICONINFORMATION);

	//111���� 222 3���ʰ� 333������ȣ Ʋ��
	
	//m_pShareReportRateDlg1->RefreshList();

	OnOK();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

void CShareReportTransferDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

CString CShareReportTransferDlg::ReturnMoneyString(CString sMoney)
{
	CString strReturn;
	CString sNumber[10] = {"��", "��", "��", "��", "��", "��", "��", "ĥ", "��", "��"};
	CString sUnit[6] = {"��", "��", "��","õ", "��", "��"};

	int nLen = sMoney.GetLength();

	if(nLen == 0)
		return "";


	for(int i=0; i<nLen; i++)
	{
		if(sMoney.Mid(i, 1) == "0")
			continue;
		else
			strReturn = strReturn + sNumber[_ttoi(sMoney.Mid(i, 1))] + sUnit[nLen-i-1];
	}
	strReturn.Replace("��","");
	strReturn += "��";

	if(nLen == 6)
	{
		//	MessageBox(strReturn);
		if(sMoney.Mid(1,1) == "0")
		{
			CString str;
			strReturn.Replace("��", "�ʸ�");

			if(strReturn.GetLength() == 8)
				return strReturn;

			strReturn.Replace("�ʸ���", "�ʿ�");
			//MessageBox(strReturn, "Ȯ��", MB_ICONINFORMATION);

			return strReturn;
		}
	}


	return strReturn;

}


void CShareReportTransferDlg::OnEnChangeSendMoneyEdit()
{
	UpdateData(true);

	CString sMoney;
	m_SendMoneyEdt.GetWindowText(sMoney);
	m_SendMoneyStc.SetWindowText(ReturnMoneyString(sMoney));
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CMyDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



