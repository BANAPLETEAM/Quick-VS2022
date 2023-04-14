// JinsangTelRegDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "JinsangTelRegDlg.h"


// CJinsangTelRegDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CJinsangTelRegDlg, CMyDialog)
CJinsangTelRegDlg::CJinsangTelRegDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CJinsangTelRegDlg::IDD, pParent)
	, m_sTelNumber(_T(""))
	, m_sName(_T(""))
	, m_nDuration(0)
	, m_sDesc(_T(""))
{
}

CJinsangTelRegDlg::~CJinsangTelRegDlg()
{
}

void CJinsangTelRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TELNUMBER, m_sTelNumber);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT1_DURATION, m_nDuration);
	DDX_Text(pDX, IDC_EDIT_DESC, m_sDesc);
	DDX_Control(pDX, IDC_COMBO_DURATION, m_cComboDuration);
}


BEGIN_MESSAGE_MAP(CJinsangTelRegDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DURATION, OnCbnSelchangeComboDuration)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CJinsangTelRegDlg �޽��� ó�����Դϴ�.

void CJinsangTelRegDlg::OnCbnSelchangeComboDuration()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nCurSel = m_cComboDuration.GetCurSel();
	if(nCurSel == -1) return;

	CString sDuration;
	m_cComboDuration.GetLBText(nCurSel,sDuration);
	m_nDuration = atoi(sDuration);
	UpdateData(FALSE);
}

BOOL CJinsangTelRegDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_cComboDuration.ResetContent();
	m_cComboDuration.AddString("7   -1����");
	m_cComboDuration.AddString("30  -1����");
	m_cComboDuration.AddString("90  -3����");
	m_cComboDuration.AddString("180 -6����");
	m_cComboDuration.AddString("365 -1��");
	m_cComboDuration.AddString("3650-10��");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CJinsangTelRegDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	this->m_sTelNumber.Trim();
	if(m_sTelNumber.IsEmpty())
	{
		MessageBox("����� ��ȭ�� ��ϵ��� �ʾҽ��ϴ�.", 
				"Ȯ��", 
				MB_ICONINFORMATION);
		
		return;
	}

	if(this->m_nDuration <= 0)
	{
		MessageBox("����� ��ȭ�� ��ϵ��� �ʾҽ��ϴ�.", 
				"Ȯ��", 
				MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CJinsangTelRegDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
