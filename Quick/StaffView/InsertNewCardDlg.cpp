// InsertNewCardDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "InsertNewCardDlg.h"


// CInsertNewCardDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInsertNewCardDlg, CDialog)

CInsertNewCardDlg::CInsertNewCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertNewCardDlg::IDD, pParent)
{
}

CInsertNewCardDlg::~CInsertNewCardDlg()
{
}

void CInsertNewCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARD_NUMBER_EDIT, m_edtCardNumber);
}


BEGIN_MESSAGE_MAP(CInsertNewCardDlg, CDialog)
	ON_BN_CLICKED(IDC_INSERT_CARD_BTN, &CInsertNewCardDlg::OnBnClickedInsertCardBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CInsertNewCardDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CInsertNewCardDlg �޽��� ó�����Դϴ�.

void CInsertNewCardDlg::OnBnClickedInsertCardBtn()
{
	m_edtCardNumber.GetWindowText(m_strCardNumber);
	m_strCardNumber = ::GetNoneDashNumber(m_strCardNumber);

	if(m_strCardNumber.IsEmpty())
	{
		MessageBox("ī���ȣ�� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	OnOK();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CInsertNewCardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtCardNumber.SetEditMask("0000-0000-0000-0000", LITERAL_CARD_NUMBER);
	m_edtCardNumber.SetPromptChar(' ');

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CInsertNewCardDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
