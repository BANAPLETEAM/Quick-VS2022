// ShareReportAuthPhoneDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportAuthPhoneDlg.h"

#include "ShareReportTransferDlg.h"
#include "ShareReportWantTransferDlg.h"


// CShareReportAuthPhoneDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareReportAuthPhoneDlg, CMyDialog)
CShareReportAuthPhoneDlg::CShareReportAuthPhoneDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportAuthPhoneDlg::IDD, pParent)
{
	m_pShareReportTransferDlg = NULL;
	m_pShareReportWantTransferDlg = NULL;
}

CShareReportAuthPhoneDlg::~CShareReportAuthPhoneDlg()
{
}

void CShareReportAuthPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHONE1_RDO, m_Phone1Rdo);
	DDX_Control(pDX, IDC_PHONE2_RDO, m_Phone2Rdo);
}


BEGIN_MESSAGE_MAP(CShareReportAuthPhoneDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CShareReportAuthPhoneDlg �޽��� ó�����Դϴ�.

void CShareReportAuthPhoneDlg::OnBnClickedOk()
{
	CString strAuthPhone;
	if(m_Phone1Rdo.GetCheck() == BST_CHECKED)
		m_Phone1Rdo.GetWindowText(strAuthPhone);
	else if(m_Phone2Rdo.GetCheck() == BST_CHECKED)
		m_Phone2Rdo.GetWindowText(strAuthPhone);
	else
	{
		MessageBox("�������� ��ȭ��ȣ�� �����ϼ���", "Ȯ��", MB_ICONERROR);
		return;
	}

	strAuthPhone.Replace("-","");

	CString sSMSSql;

	if(m_pShareReportTransferDlg == NULL)
		sSMSSql = "insert_share_report_want_transfer_phone_sms";
	else
		sSMSSql = "insert_share_report_transfer_phone_sms";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, sSMSSql);

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, strAuthPhone.GetLength() , strAuthPhone);

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);


	if(!pRs.Execute(&pCmd))
	{
		MessageBox("�޼��� ���ۿ� ���� �߽��ϴ�", "Ȯ��", MB_ICONERROR);
		return;
	}

	if(m_pShareReportTransferDlg == NULL)
		pPar->GetValue(m_pShareReportWantTransferDlg->m_nSMSID);
	else
		pPar->GetValue(m_pShareReportTransferDlg->m_nSMSID);

	MessageBox("�޽����� �����߽��ϴ�", "Ȯ��", MB_ICONINFORMATION);


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CShareReportAuthPhoneDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

BOOL CShareReportAuthPhoneDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	Init();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CShareReportAuthPhoneDlg::Init()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_Auth_Phone");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return ;

	CString strAuthPhone1;
	CString strAuthPhone2;

	pRs.GetFieldValue("sAuthPhone1", strAuthPhone1);
	pRs.GetFieldValue("sAuthPhone2", strAuthPhone2);

	m_Phone1Rdo.SetWindowText(strAuthPhone1);
	m_Phone2Rdo.SetWindowText(strAuthPhone2);
}
