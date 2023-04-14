// VarietyDlg1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "VarietyDlg3.h"

// CVarietyDlg3 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVarietyDlg3, CMyDialog)
CVarietyDlg3::CVarietyDlg3(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVarietyDlg3::IDD, pParent)
	, m_strMemo(_T(""))
	, m_dtAuto(COleDateTime::GetCurrentTime())
	, m_bUse(FALSE)
{
	m_strTitle = "";
	m_nAutoGroupCode = 0;
}

CVarietyDlg3::~CVarietyDlg3()
{
}

void CVarietyDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtDateAuto);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtAuto);
	DDX_Control(pDX, IDC_ALLOC_COMBO, m_cmbAlloc);
	DDX_Control(pDX, IDC_USE_CHECK, m_chkUse);
	DDX_Check(pDX, IDC_USE_CHECK, m_bUse);
}


BEGIN_MESSAGE_MAP(CVarietyDlg3, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_USE_CHECK, OnBnClickedUseCheck)
END_MESSAGE_MAP()


// CVarietyDlg3 �޽��� ó�����Դϴ�.

BOOL CVarietyDlg3::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	SetWindowText(m_strTitle);

	::InsertAllocGroupCombo(&m_cmbAlloc, GetCurBranchInfo()->nCompanyCode);
	m_cmbAlloc.SetCurSel(0);
	OnBnClickedUseCheck();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CVarietyDlg3::OnBnClickedOk()
{
	m_nAutoGroupCode = m_cmbAlloc.GetItemData(m_cmbAlloc.GetCurSel());
	OnOK();
}

void CVarietyDlg3::OnBnClickedCancel()
{
	OnCancel();
}

void CVarietyDlg3::OnBnClickedUseCheck()
{
	BOOL bChk = m_chkUse.GetCheck();
	m_dtDateAuto.EnableWindow(bChk);
	m_cmbAlloc.EnableWindow(bChk);
}
