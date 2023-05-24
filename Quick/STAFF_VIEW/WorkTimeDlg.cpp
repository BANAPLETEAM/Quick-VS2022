// WorkTimeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WorkTimeDlg.h"


// CWorkTimeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWorkTimeDlg, CMyDialog)

CWorkTimeDlg::CWorkTimeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWorkTimeDlg::IDD, pParent)
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	m_dtStartTime.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 7, 0, 0);
	m_dtEndTime.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 6, 59, 00);
}
 
CWorkTimeDlg::~CWorkTimeDlg()
{
}

void CWorkTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_dtStartTime);
	DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_dtEndTime);
}


BEGIN_MESSAGE_MAP(CWorkTimeDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CWorkTimeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWorkTimeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWorkTimeDlg 메시지 처리기입니다.

BOOL CWorkTimeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();
	return TRUE;
}

void CWorkTimeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}

void CWorkTimeDlg::OnBnClickedCancel()
{	
	OnCancel();
}
