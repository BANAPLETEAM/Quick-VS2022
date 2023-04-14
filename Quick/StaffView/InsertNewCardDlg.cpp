// InsertNewCardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "InsertNewCardDlg.h"


// CInsertNewCardDlg 대화 상자입니다.

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


// CInsertNewCardDlg 메시지 처리기입니다.

void CInsertNewCardDlg::OnBnClickedInsertCardBtn()
{
	m_edtCardNumber.GetWindowText(m_strCardNumber);
	m_strCardNumber = ::GetNoneDashNumber(m_strCardNumber);

	if(m_strCardNumber.IsEmpty())
	{
		MessageBox("카드번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	OnOK();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CInsertNewCardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtCardNumber.SetEditMask("0000-0000-0000-0000", LITERAL_CARD_NUMBER);
	m_edtCardNumber.SetPromptChar(' ');

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInsertNewCardDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
