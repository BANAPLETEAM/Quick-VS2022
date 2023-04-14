// RiderColorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderColorDlg.h"


// CRiderColorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderColorDlg, CMyDialog)

CRiderColorDlg::CRiderColorDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderColorDlg::IDD, pParent)
{

}

CRiderColorDlg::~CRiderColorDlg()
{
}

void CRiderColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_WHITE_CHECK, m_chkWhite);
	DDX_Control(pDX, IDC_BLUE_CHECK, m_chkBlue);
	DDX_Control(pDX, IDC_GREEN_CHECK, m_chkGreen);
	DDX_Control(pDX, IDC_RED_CHECK, m_chkRed);
	DDX_Control(pDX, IDC_PURPLE_CHECK, m_chkPurple);
	DDX_Control(pDX, IDC_YELLOW_CHECK, m_chkYellow);
	DDX_Control(pDX, IDC_SKY_CHECK, m_chkSky);
	DDX_Control(pDX, IDC_STATIC43, m_stc43);


	DDX_Control(pDX, IDC_BLACK_CHECK, m_chkBlack);
	DDX_Control(pDX, IDC_INDIGO_CHECK , m_chkIndigo);
	DDX_Control(pDX, IDC_PINK_CHECK , m_chkPink);
	DDX_Control(pDX, IDC_DARKGRAY_CHECK , m_chkDarkgray);
	DDX_Control(pDX, IDC_LIGHTLATEGRAY_CHECK , m_chkLightlategray);
	DDX_Control(pDX, IDC_THISTLE_CHECK , m_chkThistle);
	DDX_Control(pDX, IDC_MIDNIGHT_CHECK , m_chkMidnight);
}


BEGIN_MESSAGE_MAP(CRiderColorDlg, CMyDialog)
	ON_BN_CLICKED(IDC_WHITE_CHECK, &CRiderColorDlg::OnBnClickedWhiteCheck)
	ON_BN_CLICKED(IDOK, &CRiderColorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRiderColorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BLUE_CHECK, &CRiderColorDlg::OnBnClickedBlueCheck)
	ON_BN_CLICKED(IDC_GREEN_CHECK, &CRiderColorDlg::OnBnClickedGreenCheck)
	ON_BN_CLICKED(IDC_RED_CHECK, &CRiderColorDlg::OnBnClickedRedCheck)
	ON_BN_CLICKED(IDC_PURPLE_CHECK, &CRiderColorDlg::OnBnClickedPurpleCheck)
	ON_BN_CLICKED(IDC_YELLOW_CHECK, &CRiderColorDlg::OnBnClickedYellowCheck)
	ON_BN_CLICKED(IDC_SKY_CHECK, &CRiderColorDlg::OnBnClickedSkyCheck)
	ON_BN_CLICKED(IDC_BLACK_CHECK, &CRiderColorDlg::OnBnClickedBlackCheck)
	ON_BN_CLICKED(IDC_INDIGO_CHECK, &CRiderColorDlg::OnBnClickedIndigoCheck)
	ON_BN_CLICKED(IDC_PINK_CHECK, &CRiderColorDlg::OnBnClickedPinkCheck)
	ON_BN_CLICKED(IDC_DARKGRAY_CHECK, &CRiderColorDlg::OnBnClickedDarkgrayCheck)
	ON_BN_CLICKED(IDC_LIGHTLATEGRAY_CHECK, &CRiderColorDlg::OnBnClickedLightlategrayCheck)
	ON_BN_CLICKED(IDC_THISTLE_CHECK, &CRiderColorDlg::OnBnClickedThistleCheck)
	ON_BN_CLICKED(IDC_MIDNIGHT_CHECK, &CRiderColorDlg::OnBnClickedMidnightCheck)
	ON_BN_CLICKED(ID_CLEAR_BTN, &CRiderColorDlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CRiderColorDlg 메시지 처리기입니다.

BOOL CRiderColorDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_chkWhite.SetBackColor(RGB(255, 255, 255));
	m_chkBlue.SetBackColor(RGB(110, 110, 255)); 
	m_chkGreen.SetBackColor(RGB(0, 255, 0));
	m_chkRed.SetBackColor(RGB(255, 70, 70));
	m_chkPurple.SetBackColor(RGB(175, 50, 255));
	m_chkYellow.SetBackColor(RGB(255, 255, 0));
	m_chkSky.SetBackColor(RGB(0, 255, 255));
	m_stc43.SetBkColor(RGB(255, 255, 255));
	m_stc43.SetTextColor(RGB(0, 0, 0)); 

	m_chkBlack.SetBackColor(RGB(0, 0, 0)); 
	m_chkIndigo.SetBackColor(RGB(0x4B, 0, 0x82)); 
	m_chkPink.SetBackColor(RGB(0xFF, 0x0C, 0xCB)); 
	m_chkDarkgray.SetBackColor(RGB(0x2F, 0x4F, 0x4F)); 
	m_chkLightlategray.SetBackColor(RGB(0x77, 0x88, 0x99)); 
	m_chkThistle.SetBackColor(RGB(0xD8, 0xBF, 0xD8)); 
	m_chkMidnight.SetBackColor(RGB(0x19, 0x19, 0x70)); 

	m_stc43.SetBkColor(RGB(255, 255, 255));
	m_stc43.SetTextColor(RGB(0, 0, 0));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
} 

void CRiderColorDlg::OnBnClickedWhiteCheck()
{
	SetColorCheck(IDC_WHITE_CHECK);
}

void CRiderColorDlg::OnBnClickedOk()
{
	OnOK();
}

void CRiderColorDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CRiderColorDlg::OnBnClickedBlueCheck()
{
	SetColorCheck(IDC_BLUE_CHECK);
}

void CRiderColorDlg::OnBnClickedGreenCheck()
{
	SetColorCheck(IDC_GREEN_CHECK);
}

void CRiderColorDlg::OnBnClickedRedCheck()
{
	SetColorCheck(IDC_RED_CHECK);
}

void CRiderColorDlg::OnBnClickedPurpleCheck()
{
	SetColorCheck(IDC_PURPLE_CHECK);
}

void CRiderColorDlg::OnBnClickedYellowCheck()
{
	SetColorCheck(IDC_YELLOW_CHECK);
}

void CRiderColorDlg::OnBnClickedSkyCheck()
{
	SetColorCheck(IDC_SKY_CHECK);
}

void CRiderColorDlg::SetColorCheck(UINT nFlag)
{	
	UINT nCheck[] = {IDC_WHITE_CHECK, IDC_BLUE_CHECK, IDC_GREEN_CHECK, IDC_RED_CHECK, IDC_PURPLE_CHECK, IDC_YELLOW_CHECK, IDC_SKY_CHECK,
		IDC_BLACK_CHECK, IDC_INDIGO_CHECK, IDC_PINK_CHECK, IDC_DARKGRAY_CHECK, IDC_LIGHTLATEGRAY_CHECK, IDC_THISTLE_CHECK, IDC_MIDNIGHT_CHECK};

	for(int i=0; i < RIDER_COLOR_COUNT; i++)
	{
		if(nFlag == nCheck[i])
		{
			((CButton*)GetDlgItem(nFlag))->SetCheck(TRUE);
			m_stc43.SetBkColor(LF->GetRiderColor(i));
			m_nColor = LF->GetRiderColor(i); 
		}
		else
			((CButton*)GetDlgItem(nFlag))->SetCheck(FALSE);
	}
}


void CRiderColorDlg::OnBnClickedBlackCheck()
{
	SetColorCheck(IDC_BLACK_CHECK);
}

void CRiderColorDlg::OnBnClickedIndigoCheck()
{
	SetColorCheck(IDC_INDIGO_CHECK);
}

void CRiderColorDlg::OnBnClickedPinkCheck()
{
	SetColorCheck(IDC_PINK_CHECK);
}

void CRiderColorDlg::OnBnClickedDarkgrayCheck()
{
	SetColorCheck(IDC_DARKGRAY_CHECK);
}

void CRiderColorDlg::OnBnClickedLightlategrayCheck()
{
	SetColorCheck(IDC_LIGHTLATEGRAY_CHECK);
}

void CRiderColorDlg::OnBnClickedThistleCheck()
{
	SetColorCheck(IDC_THISTLE_CHECK);
}

void CRiderColorDlg::OnBnClickedMidnightCheck()
{
	SetColorCheck(IDC_MIDNIGHT_CHECK);
}

void CRiderColorDlg::OnBnClickedClearBtn()
{
	m_nColor = 0;
	OnOK();
}
