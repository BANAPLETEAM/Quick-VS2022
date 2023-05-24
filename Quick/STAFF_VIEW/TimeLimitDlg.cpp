// TimeLimitDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "TimeLimitDlg.h"


// CTimeLimitDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTimeLimitDlg, CMyDialog)

CTimeLimitDlg::CTimeLimitDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTimeLimitDlg::IDD, pParent)
	, m_dtLimitDate(COleDateTime::GetCurrentTime())
	, m_dtLimitTime(COleDateTime::GetCurrentTime())
	, m_dtDate(COleDateTime::GetCurrentTime())
{

}

CTimeLimitDlg::~CTimeLimitDlg()
{
}

void CTimeLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_LIMIT_DATE, m_dtLimitDate);
	DDX_DateTimeCtrl(pDX, IDC_LIMIT_TIME, m_dtLimitTime);
	DDX_Control(pDX, IDC_COMBO_TIMELIMIT, m_cmbTimeLimit);
}


BEGIN_MESSAGE_MAP(CTimeLimitDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CTimeLimitDlg::OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CTimeLimitDlg 메시지 처리기입니다.

void CTimeLimitDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	m_dtDate.SetDateTime(m_dtLimitDate.GetYear(), m_dtLimitTime.GetMonth(), m_dtLimitTime.GetDay(),
		m_dtLimitTime.GetHour(), m_dtLimitTime.GetMinute(), m_dtLimitTime.GetSecond());
	m_cmbTimeLimit.GetWindowText(m_sMinute);

	OnOK();
}

BOOL CTimeLimitDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	return TRUE;
}
