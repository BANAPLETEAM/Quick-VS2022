// ShareReportMyRequestDetailDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportMyRequestDetailDlg.h"


// CShareReportMyRequestDetailDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareReportMyRequestDetailDlg, CMyDialog)
CShareReportMyRequestDetailDlg::CShareReportMyRequestDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportMyRequestDetailDlg::IDD, pParent)
{
}

CShareReportMyRequestDetailDlg::~CShareReportMyRequestDetailDlg()
{
}

void CShareReportMyRequestDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEDATE_EDIT, m_SeDate_Edt);
	DDX_Control(pDX, IDC_SEMONEY_EDIT, m_SeMoney_Edt);
	DDX_Control(pDX, IDC_SEMEMO_EDIT, m_SeMemo_Edt);
	DDX_Control(pDX, IDC_REDATE_EDT, m_ReDate_Edt);
	DDX_Control(pDX, IDC_REMONEY_EDIT, m_ReMoney_Edt);
	DDX_Control(pDX, IDC_REMEMO_EDIT, m_ReMemo_Edt);
}


BEGIN_MESSAGE_MAP(CShareReportMyRequestDetailDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CShareReportMyRequestDetailDlg �޽��� ó�����Դϴ�.

void CShareReportMyRequestDetailDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

BOOL CShareReportMyRequestDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_SeDate_Edt.SetWindowText(m_SeDate);
	m_ReDate_Edt.SetWindowText(m_ReDate);
	m_SeMoney_Edt.SetWindowText(m_SeMoney);
	m_ReMoney_Edt.SetWindowText(m_ReMoney);
	m_SeMemo_Edt.SetWindowText(m_SeMemo);
	m_ReMemo_Edt.SetWindowText(m_ReMemo);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
