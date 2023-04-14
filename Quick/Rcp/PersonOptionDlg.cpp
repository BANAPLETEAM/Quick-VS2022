// PersonOptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "PersonOptionDlg.h"



// CPersonOptionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPersonOptionDlg, CMyDialog)
CPersonOptionDlg::CPersonOptionDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPersonOptionDlg::IDD, pParent)
{
}

CPersonOptionDlg::~CPersonOptionDlg()
{
}

void CPersonOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTO_FINISH_CHECK, m_chkAutoFinish);
	DDX_Control(pDX, IDC_AUTO_ALOCATE_CHECK, m_chkAutoAllocate);
}


BEGIN_MESSAGE_MAP(CPersonOptionDlg, CMyDialog)
	ON_BN_CLICKED(IDC_AUTO_FINISH_CHECK, OnBnClickedOrderFinishCheck)
	
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_AUTO_ALOCATE_CHECK, OnBnClickedAutoAlocateCheck)
END_MESSAGE_MAP()


// CPersonOptionDlg 메시지 처리기입니다.

BOOL CPersonOptionDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nAutoFinish = encProfile.GetInt("Person", "AutoFinish", 0);
	int nAutoAllocate = encProfile.GetInt("Person", "AutoAllocate", 0);
	m_chkAutoFinish.SetCheck(nAutoFinish);
	m_chkAutoAllocate.SetCheck(nAutoAllocate);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPersonOptionDlg::OnBnClickedOrderFinishCheck()
{
	
}


void CPersonOptionDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CPersonOptionDlg::OnBnClickedButton1()
{
	encProfile.WriteInt("Person", "AutoFinish", m_chkAutoFinish.GetCheck());
	encProfile.WriteInt("Person", "AutoAllocate", m_chkAutoAllocate.GetCheck());
}

void CPersonOptionDlg::OnBnClickedAutoAlocateCheck()
{
	
}
