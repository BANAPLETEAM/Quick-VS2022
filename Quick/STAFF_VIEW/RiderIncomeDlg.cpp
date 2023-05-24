// RiderIncomeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderIncomeDlg.h"


// CRiderIncomeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderIncomeDlg, CMyDialog)

CRiderIncomeDlg::CRiderIncomeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderIncomeDlg::IDD, pParent)
	, m_strIncome(_T(""))
	, m_strIncomeMemo(_T(""))
{
	m_nIncome = 0;

}

CRiderIncomeDlg::~CRiderIncomeDlg()
{
}

void CRiderIncomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INCOME_EDIT, m_edtIncome);
	DDX_Control(pDX, IDC_INCOME_MEMO_EDIT, m_edtIncomeMemo);
	DDX_Control(pDX, IDC_INCOME_COMBO, m_cmbIncome);
	DDX_Text(pDX, IDC_INCOME_EDIT, m_strIncome);
	DDX_Text(pDX, IDC_INCOME_MEMO_EDIT, m_strIncomeMemo);
}


BEGIN_MESSAGE_MAP(CRiderIncomeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_INCOME_BTN, &CRiderIncomeDlg::OnBnClickedIncomeBtn)
	ON_BN_CLICKED(IDC_INCOME_BTN2, &CRiderIncomeDlg::OnBnClickedIncomeBtn2)
END_MESSAGE_MAP()


// CRiderIncomeDlg �޽��� ó�����Դϴ�.

BOOL CRiderIncomeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtIncome.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "�ݾ�");
	m_edtIncomeMemo.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "�Ա�����");

	m_cmbIncome.InsertString(ZERO, "(+)�ܾ�����(����)");
	m_cmbIncome.SetItemData(ZERO, 17);
	m_cmbIncome.InsertString(ONE, "(+)�ܾ�����(�¶���)");
	m_cmbIncome.SetItemData(ONE, 16);
	m_cmbIncome.InsertString(TWO, "(-)�ܾ�����");
	m_cmbIncome.SetItemData(TWO, 40);
	m_cmbIncome.InsertString(THREE, "(-)�ܾ�����(�������)");
	m_cmbIncome.SetItemData(THREE, 49);
	m_cmbIncome.SetCurSel(ZERO);

	return TRUE;
}

void CRiderIncomeDlg::OnBnClickedIncomeBtn()
{
	UpdateData(TRUE);

	m_strIncome.Replace(",", "");

	m_nIncome = atoi(m_strIncome);

	if(m_nIncome <= 0)
	{
		MessageBox("�Ա�/��� �Ͻ� �ݾ��� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		m_edtIncome.SetFocus();
		return;
	}

	if(m_strIncomeMemo.IsEmpty())
	{
		MessageBox("�Ա� ���並 �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		m_edtIncomeMemo.SetFocus();
		return;
	}

	m_nType = (long)m_cmbIncome.GetItemData(m_cmbIncome.GetCurSel());

	OnOK();
}

void CRiderIncomeDlg::OnBnClickedIncomeBtn2()
{
	OnCancel();
}
