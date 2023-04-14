// ChargeMemberDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeMemberDlg.h"


// CChargeMemberDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeMemberDlg, CMyDialog)

CChargeMemberDlg::CChargeMemberDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeMemberDlg::IDD, pParent)
{
	m_nReturn = 0;
	m_strEtc = "";
	m_strChargeName = "";
}

CChargeMemberDlg::~CChargeMemberDlg()
{
}

void CChargeMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARGE_NAME_EDIT, m_strChargeName);
	DDX_Control(pDX, IDC_CHARGE_NAME_EDIT, m_edtChargeName);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
}


BEGIN_MESSAGE_MAP(CChargeMemberDlg, CMyDialog)
	
	ON_BN_CLICKED(IDYES, &CChargeMemberDlg::OnBnClickedYes)
	ON_BN_CLICKED(IDNO, &CChargeMemberDlg::OnBnClickedNo)
	ON_BN_CLICKED(IDCANCEL, &CChargeMemberDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChargeMemberDlg 메시지 처리기입니다.



void CChargeMemberDlg::OnBnClickedYes()
{
	m_nReturn = IDYES;
	UpdateData();
	if(m_strChargeName.GetLength() <= 0)
	{
		MessageBox("요금제 이름을 입력하세요");
		return;
	}
	OnOK();
}

void CChargeMemberDlg::OnBnClickedNo()
{
	m_nReturn = IDNO;
	OnOK();

}

void CChargeMemberDlg::OnBnClickedCancel()
{
	m_nReturn = IDCANCEL;
	OnOK();
}

BOOL CChargeMemberDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_edtChargeName.SetFocus();
	m_edtChargeName.SetSel(0, m_strChargeName.GetLength());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
