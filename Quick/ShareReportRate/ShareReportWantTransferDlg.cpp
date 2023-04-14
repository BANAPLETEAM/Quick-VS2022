// ShareReportWantTransferDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportWantTransferDlg.h"

#include "ShareReportAuthPhoneDlg.h"


// CShareReportWantTransferDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareReportWantTransferDlg, CMyDialog)
CShareReportWantTransferDlg::CShareReportWantTransferDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportWantTransferDlg::IDD, pParent)
{
	m_nToCompany = 0;
	m_nSMSID = 0;
}

CShareReportWantTransferDlg::~CShareReportWantTransferDlg()
{
}

void CShareReportWantTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_MONEY_EDIT, m_SendMoneyEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
	DDX_Control(pDX, IDC_SEND_MONEY_STC, m_SendMoneyStc);
	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_CompanyNameEdt);
}

BEGIN_MESSAGE_MAP(CShareReportWantTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SEND_MONEY_EDIT, OnEnChangeSendMoneyEdit)
END_MESSAGE_MAP()


// CShareReportWantTransferDlg �޽��� ó�����Դϴ�.

void CShareReportWantTransferDlg::OnBnClickedOk()
{
	UpdateData(true);

	CString strAbilityMoney, strSendMoney;

	m_SendMoneyEdt.GetWindowText(strSendMoney);


	if(_ttoi(strSendMoney) > 300000)
	{
		MessageBox("��ʸ��� �̻� ��û �� �� �����ϴ�", "Ȯ��", MB_ICONERROR);
		return;
	}

	CString sSendCharege, sMemo;
	

	m_SendMoneyEdt.GetWindowText(sSendCharege);

	m_MemoEdt.GetWindowText(sMemo);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_share_report_want_transfer");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sSendCharege));
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nToCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0); // ��翡�� ���Ա� ���� �Ұ��� ������
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0); // �����Ұ�� nTNo
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	MessageBox("���������� ��û�Ǿ����ϴ�", "Ȯ��" ,MB_ICONINFORMATION);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CShareReportWantTransferDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}



void CShareReportWantTransferDlg::OnEnChangeSendMoneyEdit()
{
	CString sMoney;
	m_SendMoneyEdt.GetWindowText(sMoney);
	m_SendMoneyStc.SetWindowText(ReturnMoneyString(sMoney));
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CMyDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


CString CShareReportWantTransferDlg::ReturnMoneyString(CString sMoney)
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
BOOL CShareReportWantTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_SendMoneyEdt.SetLimitText(6);
	m_CompanyNameEdt.SetWindowText(m_ci.GetName(m_nToCompany));

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
