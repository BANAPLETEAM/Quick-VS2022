// WithdrawManualDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WithdrawManualDlg.h"


// CWithdrawManualDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWithdrawManualDlg, CMyDialog)

CWithdrawManualDlg::CWithdrawManualDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWithdrawManualDlg::IDD, pParent)
{

}

CWithdrawManualDlg::~CWithdrawManualDlg()
{
}

void CWithdrawManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REAL_WITHDRAW_EDIT, m_edtRealWithdraw);
	DDX_Control(pDX, IDC_DATE_DT, m_dtpDate);
	DDX_Control(pDX, IDC_TIME_DT, m_dtpTime);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
}

BEGIN_MESSAGE_MAP(CWithdrawManualDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CWithdrawManualDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWithdrawManualDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWithdrawManualDlg 메시지 처리기입니다.

BOOL CWithdrawManualDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dtpTime.SetFormat("tth-mm");

	m_dtpDate.SetTime(COleDateTime::GetCurrentTime());
	m_dtpTime.SetTime(COleDateTime::GetCurrentTime());

	m_edtRealWithdraw.SetWindowText(LF->GetMyNumberFormat(m_nCharge));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWithdrawManualDlg::OnBnClickedOk()
{
	m_nCharge = LF->GetLongFromEdit(&m_edtRealWithdraw);

	if(m_nCharge <= 0)
	{
		MessageBox("실제 이체하신 금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	m_edtEtc.GetWindowText(m_strEtc);

	COleDateTime  dtTime;
	m_dtpDate.GetTime(m_dtWithdraw);
	m_dtpTime.GetTime(dtTime);

	m_dtWithdraw.SetTime(dtTime.GetHour(), dtTime.GetMinute(), dtTime.GetSecond());
	
	OnOK();
}

void CWithdrawManualDlg::OnBnClickedCancel()
{
	OnCancel();
}

