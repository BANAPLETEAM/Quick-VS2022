// GroupSearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GroupSearchDlg.h"
#include "ReportForm24.h"

// CGroupSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGroupSearchDlg, CMyDialog)
CGroupSearchDlg::CGroupSearchDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGroupSearchDlg::IDD, pParent)
{ 
	m_pParent = pParent;
}

CGroupSearchDlg::~CGroupSearchDlg()
{
}

void CGroupSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CASH_OPTION_CHECK, m_chkCashOption);
	DDX_Control(pDX, IDC_CREDIT_OPTION_CHECK, m_chkCreditOption);
	DDX_Control(pDX, IDC_ACTIVE_OPTION_CHECK, m_chkActiveOption);
	DDX_Control(pDX, IDC_UNACTIVE_OPTION_CHECK, m_chkUnActiveOption);
	DDX_Control(pDX, IDC_REPORT_DAY_COMBO, m_cmbReportDay);
	DDX_Control(pDX, IDC_NOT_REPORT_COMBO, m_cmbNotReport);
	DDX_Control(pDX, IDC_NOT_REPORT_COMBO2, m_cmbNotReport2);
}


BEGIN_MESSAGE_MAP(CGroupSearchDlg, CMyDialog)
	ON_BN_CLICKED(IDC_UNACTIVE_OPTION_CHECK, OnBnClickedUnactiveOptionCheck)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_CASH_OPTION_CHECK, OnBnClickedCashOptionCheck)
	ON_BN_CLICKED(IDC_CREDIT_OPTION_CHECK, OnBnClickedCreditOptionCheck)
	ON_CBN_SELCHANGE(IDC_REPORT_DAY_COMBO, OnCbnSelchangeReportDayCombo)
	ON_CBN_SELCHANGE(IDC_NOT_REPORT_COMBO, OnCbnSelchangeNotReportCombo)
	ON_BN_CLICKED(IDC_ACTIVE_OPTION_CHECK, OnBnClickedActiveOptionCheck)
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_NOT_REPORT_COMBO2, OnCbnSelchangeNotReportCombo2)
END_MESSAGE_MAP()


// CGroupSearchDlg 메시지 처리기입니다.

BOOL CGroupSearchDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_chkActiveOption.SetCheck(TRUE);
	m_chkUnActiveOption.SetCheck(TRUE);
	m_chkCashOption.SetCheck(TRUE);
	m_chkCreditOption.SetCheck(TRUE);
	m_cmbReportDay.SetCurSel(0);

	m_cmbNotReport.InsertString(0, "검색안함");
	m_cmbNotReport2.InsertString(0, "검색안함");

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	for(int i=1; i<7; i++)
	{
		CString strTemp;

		if(dtCur.GetMonth() < 10)
			strTemp.Format("%d-0%d", dtCur.GetYear(), dtCur.GetMonth());
		else
			strTemp.Format("%d-%d", dtCur.GetYear(), dtCur.GetMonth());

		m_cmbNotReport.InsertString(i, strTemp);
		m_cmbNotReport2.InsertString(i, strTemp);
		dtCur -= COleDateTimeSpan(30, 0, 0, 0);
	}

	m_cmbNotReport.SetCurSel(0);
	m_cmbNotReport2.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGroupSearchDlg::OnBnClickedUnactiveOptionCheck()
{
	((CReportForm24*)m_pParent)->SearchFilter();	    
}

void CGroupSearchDlg::OnBnClickedCloseBtn()
{
	this->ShowWindow(FALSE);
}

void CGroupSearchDlg::OnBnClickedCashOptionCheck()
{
	((CReportForm24*)m_pParent)->SearchFilter();
}

void CGroupSearchDlg::OnBnClickedCreditOptionCheck()
{
	((CReportForm24*)m_pParent)->SearchFilter();
}

void CGroupSearchDlg::OnCbnSelchangeReportDayCombo()
{
	((CReportForm24*)m_pParent)->SearchFilter();
}

void CGroupSearchDlg::OnCbnSelchangeNotReportCombo()
{
	if(m_cmbNotReport.GetCurSel() < m_cmbNotReport2.GetCurSel())
		m_cmbNotReport2.SetCurSel(m_cmbNotReport.GetCurSel());

	if(m_cmbNotReport.GetCurSel() == 0)
		m_cmbNotReport2.SetCurSel(0);

	((CReportForm24*)m_pParent)->SearchFilter();
}

void CGroupSearchDlg::OnBnClickedActiveOptionCheck()
{
	((CReportForm24*)m_pParent)->SearchFilter();
}

BOOL CGroupSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)		
		{
			ShowWindow(FALSE);
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CGroupSearchDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CGroupSearchDlg::OnCbnSelchangeNotReportCombo2()
{
	if(m_cmbNotReport.GetCurSel() < m_cmbNotReport2.GetCurSel())
		m_cmbNotReport2.SetCurSel(m_cmbNotReport.GetCurSel());

	if(m_cmbNotReport2.GetCurSel() == 0)
		m_cmbNotReport.SetCurSel(0);


	((CReportForm24*)m_pParent)->SearchFilter();
}
