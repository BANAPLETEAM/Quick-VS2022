// AllocateBoardTRSSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateBoardTRSSetDlg.h"

#define	STATE_COLOR_PENALTY	RGB(255, 150, 150)


// CAllocateBoardTRSSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateBoardTRSSetDlg, CMyDialog)
CAllocateBoardTRSSetDlg::CAllocateBoardTRSSetDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateBoardTRSSetDlg::IDD, pParent)
{
	m_nOfficeLine1 = 0;
	m_nOfficeLine2 = 0;
	m_nOfficeLine3 = 0;
	m_nOfficeLine4 = 0;
}

CAllocateBoardTRSSetDlg::~CAllocateBoardTRSSetDlg()
{
}

void CAllocateBoardTRSSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SERVER_IP_EDIT, m_strServerIP);
	DDX_Text(pDX, IDC_SERVER_PORT_EDIT, m_strServerPort);
	DDX_Text(pDX, IDC_OFFICE_LINE_EDIT, m_nOfficeLine1);
	DDX_Text(pDX, IDC_OFFICE_LINE_EDIT2, m_nOfficeLine2);
	DDX_Text(pDX, IDC_OFFICE_LINE_EDIT3, m_nOfficeLine3);
	DDX_Text(pDX, IDC_OFFICE_LINE_EDIT4, m_nOfficeLine4);

	DDX_Control(pDX, IDC_PENALTY_COLOR_STATIC1, m_stcPenaltyColor1);
	DDX_Control(pDX, IDC_PENALTY_COLOR_STATIC2, m_stcPenaltyColor2);
	DDX_Control(pDX, IDC_PENALTY_COLOR_STATIC3, m_stcPenaltyColor3);
	DDX_Control(pDX, IDC_PENALTY_COLOR_STATIC4, m_stcPenaltyColor4);
	DDX_Control(pDX, IDC_PENALTY_COLOR_STATIC5, m_stcPenaltyColor5);

	DDX_Control(pDX, IDC_PENALTY_COLOR_BTN1, m_cpPenaltyColor1);
	DDX_Control(pDX, IDC_PENALTY_COLOR_BTN2, m_cpPenaltyColor2);
	DDX_Control(pDX, IDC_PENALTY_COLOR_BTN3, m_cpPenaltyColor3);
	DDX_Control(pDX, IDC_PENALTY_COLOR_BTN4, m_cpPenaltyColor4);
	DDX_Control(pDX, IDC_PENALTY_COLOR_BTN5, m_cpPenaltyColor5);

	DDX_Control(pDX, IDC_PENALTY_MIN_COMBO1, m_cmbPenaltyMin1);
	DDX_Control(pDX, IDC_PENALTY_MIN_COMBO2, m_cmbPenaltyMin2);
	DDX_Control(pDX, IDC_PENALTY_MIN_COMBO3, m_cmbPenaltyMin3);
	DDX_Control(pDX, IDC_PENALTY_MIN_COMBO4, m_cmbPenaltyMin4);
	DDX_Control(pDX, IDC_PENALTY_MIN_COMBO5, m_cmbPenaltyMin5);
}


BEGIN_MESSAGE_MAP(CAllocateBoardTRSSetDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CPN_XT_SELENDOK(IDC_PENALTY_COLOR_BTN1, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_PENALTY_COLOR_BTN2, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_PENALTY_COLOR_BTN3, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_PENALTY_COLOR_BTN4, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_PENALTY_COLOR_BTN5, OnSelEndOkBackColor)
END_MESSAGE_MAP()


// CAllocateBoardTRSSetDlg 메시지 처리기입니다.

BOOL CAllocateBoardTRSSetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	char buffer[10];
	int nPenaltyMin1 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin1", 0);
	int nPenaltyMin2 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin2", 0);
	int nPenaltyMin3 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin3", 0);
	int nPenaltyMin4 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin4", 0);
	int nPenaltyMin5 = AfxGetApp()->GetProfileInt("TRS", "PenaltyMin5", 0);

	m_cmbPenaltyMin1.SetWindowText(ltoa(nPenaltyMin1, buffer, 10));
	m_cmbPenaltyMin2.SetWindowText(ltoa(nPenaltyMin2, buffer, 10));
	m_cmbPenaltyMin3.SetWindowText(ltoa(nPenaltyMin3, buffer, 10));
	m_cmbPenaltyMin4.SetWindowText(ltoa(nPenaltyMin4, buffer, 10));
	m_cmbPenaltyMin5.SetWindowText(ltoa(nPenaltyMin5, buffer, 10));

	RefreshColor();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateBoardTRSSetDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	AfxGetApp()->WriteProfileInt("TRS", "OfficeLine1", m_nOfficeLine1);
	AfxGetApp()->WriteProfileInt("TRS", "OfficeLine2", m_nOfficeLine2);
	AfxGetApp()->WriteProfileInt("TRS", "OfficeLine3", m_nOfficeLine3);
	AfxGetApp()->WriteProfileInt("TRS", "OfficeLine4", m_nOfficeLine4);
	AfxGetApp()->WriteProfileString("TRS", "ServerIP", m_strServerIP);
	AfxGetApp()->WriteProfileInt("TRS", "ServerPort", atol(m_strServerPort));

	AfxGetApp()->WriteProfileInt("TRS", "PenaltyColor1", m_cpPenaltyColor1.GetColor());
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyColor2", m_cpPenaltyColor2.GetColor());
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyColor3", m_cpPenaltyColor3.GetColor());
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyColor4", m_cpPenaltyColor4.GetColor());
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyColor5", m_cpPenaltyColor5.GetColor());


	CString strPenalty1, strPenalty2, strPenalty3, strPenalty4, strPenalty5;
	m_cmbPenaltyMin1.GetWindowText(strPenalty1);
	m_cmbPenaltyMin2.GetWindowText(strPenalty2);
	m_cmbPenaltyMin3.GetWindowText(strPenalty3);
	m_cmbPenaltyMin4.GetWindowText(strPenalty4);
	m_cmbPenaltyMin5.GetWindowText(strPenalty5);

	AfxGetApp()->WriteProfileInt("TRS", "PenaltyMin1", atol(strPenalty1));
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyMin2", atol(strPenalty2));
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyMin3", atol(strPenalty3));
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyMin4", atol(strPenalty4));
	AfxGetApp()->WriteProfileInt("TRS", "PenaltyMin5", atol(strPenalty5));

	OnOK();
}

void CAllocateBoardTRSSetDlg::RefreshColor()
{
	COLORREF crBack;

	crBack = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor1", STATE_COLOR_PENALTY);
	m_cpPenaltyColor1.SetColor(crBack);
	m_stcPenaltyColor1.SetTextColor(RGB(0, 0, 0));
	m_stcPenaltyColor1.SetBkColor(crBack);

	crBack = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor2", STATE_COLOR_PENALTY);
	m_cpPenaltyColor2.SetColor(crBack);
	m_stcPenaltyColor2.SetTextColor(RGB(0, 0, 0));
	m_stcPenaltyColor2.SetBkColor(crBack);

	crBack = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor3", STATE_COLOR_PENALTY);
	m_cpPenaltyColor3.SetColor(crBack);
	m_stcPenaltyColor3.SetTextColor(RGB(0, 0, 0));
	m_stcPenaltyColor3.SetBkColor(crBack);

	crBack = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor4", STATE_COLOR_PENALTY);
	m_cpPenaltyColor4.SetColor(crBack);
	m_stcPenaltyColor4.SetTextColor(RGB(0, 0, 0));
	m_stcPenaltyColor4.SetBkColor(crBack);

	crBack = AfxGetApp()->GetProfileInt("TRS", "PenaltyColor5", STATE_COLOR_PENALTY);
	m_cpPenaltyColor5.SetColor(crBack);
	m_stcPenaltyColor5.SetTextColor(RGB(0, 0, 0));
	m_stcPenaltyColor5.SetBkColor(crBack);

}

void CAllocateBoardTRSSetDlg::OnSelEndOkBackColor()
{
	m_stcPenaltyColor1.SetBkColor(m_cpPenaltyColor1.GetColor());
	m_stcPenaltyColor2.SetBkColor(m_cpPenaltyColor2.GetColor());
	m_stcPenaltyColor3.SetBkColor(m_cpPenaltyColor3.GetColor());
	m_stcPenaltyColor4.SetBkColor(m_cpPenaltyColor4.GetColor());
	m_stcPenaltyColor5.SetBkColor(m_cpPenaltyColor5.GetColor());
}



