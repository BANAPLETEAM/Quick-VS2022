// RiderMapSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMapSetDlg.h"
#include "RiderGpsSignalDlg.h"
#include "RiderMapNormalForm.h"


// CRiderMapSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderMapSetDlg, CMyDialog)

CRiderMapSetDlg::CRiderMapSetDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderMapSetDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	m_nCurMapLevel = 0;
	m_nMaxMapLevel = 0;
}

CRiderMapSetDlg::~CRiderMapSetDlg()
{
}

void CRiderMapSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOCATE_RIGHT_CHECK, m_chkLocateRight);
}


BEGIN_MESSAGE_MAP(CRiderMapSetDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &OnBnClickedOk)
	ON_BN_CLICKED(IDC_SHOW_GPS_SIGNAL_BTN, &OnBnClickedShowGpsSignalBtn)
	ON_BN_CLICKED(IDC_RIDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK2, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK3, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK4, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK5, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CHECK6, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CAPTION_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CAPTION_CHECK2, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_RIDER_CAPTION_CHECK3, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CHECK2, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CHECK3	, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CHECK4, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CHECK5, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CAPTION_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CAPTION_CHECK2, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CAPTION_CHECK3, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_AUTO_REFRESH_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_SECTOR_LIST_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_HOVER_SHOW_RIDER_HAVE_ORDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_SHARE_RIDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_COMPLETE_ORDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_CANCEL_ORDER_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_CLICK_AUTO_MOVE_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_RIDER_HAS_COLOR_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_COMPANY_ALL_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_SHOW_ORDER_COUNT_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_8_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_10_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_11_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_30_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_31_CHECK, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_ORDER_COUNT_35_CHECK, &OnBnClickedCheckBox)
	ON_CBN_SELCHANGE(IDC_NEAR_RIDER_LEVEL_COMBO, &OnCbnSelchangeNearRiderLevelCombo)
	ON_CBN_SELCHANGE(IDC_SHOW_RIDER_CAPTION_LEVEL_COMBO, &OnBnClickedCheckBox)
	ON_CBN_SELCHANGE(IDC_RIDER_TAIL_SHOW_TIME_COMBO, &OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_LOCATE_RIGHT_CHECK, &CRiderMapSetDlg::OnBnClickedCheckBox)
	ON_CBN_SELCHANGE(IDC_GPS_MINUTE_COMBO, &CRiderMapSetDlg::OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_GPS_RIDER_ONLY_CHECK, &CRiderMapSetDlg::OnBnClickedGpsRiderOnlyCheck)
END_MESSAGE_MAP()


// CRiderMapSetDlg 메시지 처리기입니다.

BOOL CRiderMapSetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	AfxGetApp()->WriteProfileInt("RiderMapSet", "ShowOnce", 1);
	
	InitLevelCombo();
	SetCurMapLevel();
	LF->LoadFromReg(m_info);
	StructToResource();
	OnBnClickedGpsRiderOnlyCheck();

	return TRUE;
}

void CRiderMapSetDlg::InitLevelCombo()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_NEAR_RIDER_LEVEL_COMBO);
	CComboBox *pCombo2 = (CComboBox*)GetDlgItem(IDC_SHOW_RIDER_CAPTION_LEVEL_COMBO);

	pCombo->AddString("변경안함");
	pCombo2->AddString("항상표시");

	for(int i = 1; i <= m_nMaxMapLevel; i++)
	{	
		CString strLevel;
		strLevel.Format("%d레벨", i);
		if(i == 1)
			strLevel += "(상세)";
		else if(i == m_nMaxMapLevel)
			strLevel += "(전국)";

		pCombo->AddString(strLevel);
		pCombo2->AddString(strLevel);
	}
}

void CRiderMapSetDlg::SetCurMapLevel()
{
	CString strMapLevel;
	strMapLevel.Format("현재맵 %d레벨", m_nCurMapLevel);
	((CEdit*)GetDlgItem(IDC_MAP_CUR_LEVEL_EDIT))->SetWindowText(strMapLevel);
	((CEdit*)GetDlgItem(IDC_MAP_CUR_LEVEL_EDIT2))->SetWindowText(strMapLevel);
}

void CRiderMapSetDlg::OnBnClickedOk()
{
	ResourceToStruct();
	LF->SaveToReg(m_info);
	OnOK();
}

#define SET_CHECK(x, y)  ((CButton*)GetDlgItem(x))->SetCheck(m_info.y);
#define SET_COMBO(x, y)  ((CComboBox*)GetDlgItem(x))->SetCurSel(m_info.y);


void CRiderMapSetDlg::StructToResource()
{
	((CButton*)GetDlgItem(IDC_RIDER_CHECK))->SetCheck(m_info.nRiderAlloc);
	SET_CHECK(IDC_RIDER_CHECK, nRiderAlloc)
	SET_CHECK(IDC_RIDER_CHECK2, nRiderPickup)
	SET_CHECK(IDC_RIDER_CHECK3, nRiderBefore1)
	SET_CHECK(IDC_RIDER_CHECK4, nRiderBefore10)
	SET_CHECK(IDC_RIDER_CHECK5, nRiderBefore30)
	SET_CHECK(IDC_RIDER_CHECK6, nRiderAfter30)
	SET_CHECK(IDC_RIDER_CAPTION_CHECK, nRiderCaptionRNo)
	SET_CHECK(IDC_RIDER_CAPTION_CHECK2, nRiderCaptionName)
	SET_CHECK(IDC_RIDER_CAPTION_CHECK3, nRiderCaptionCompany)
	SET_CHECK(IDC_ORDER_CHECK, nOrderBefore10)
	SET_CHECK(IDC_ORDER_CHECK2, nOrderBefore20)
	SET_CHECK(IDC_ORDER_CHECK3	, nOrderBefore30)
	SET_CHECK(IDC_ORDER_CHECK4, nOrderBefore60)
	SET_CHECK(IDC_ORDER_CHECK5, nOrderAfter60)
	SET_CHECK(IDC_ORDER_CAPTION_CHECK, nOrderCaptionTime)
	SET_CHECK(IDC_ORDER_CAPTION_CHECK2, nOrderCaptionStart)
	SET_CHECK(IDC_ORDER_CAPTION_CHECK3, nOrderCaptionDest)
	SET_CHECK(IDC_ORDER_AUTO_REFRESH_CHECK, nOrderAutoRefresh)
	SET_COMBO(IDC_NEAR_RIDER_LEVEL_COMBO, nNearRiderLevel)
	SET_CHECK(IDC_SHOW_SECTOR_LIST_CHECK, nShowSectorList)
	SET_CHECK(IDC_HOVER_SHOW_RIDER_HAVE_ORDER_CHECK, nHoverShowRiderHaveOrder)
	SET_CHECK(IDC_SHOW_SHARE_RIDER_CHECK, nShowSectorList)
	SET_CHECK(IDC_SHOW_COMPLETE_ORDER_CHECK, nShowCompleteOrder)
	SET_CHECK(IDC_SHOW_CANCEL_ORDER_CHECK, nShowCancelOrder)
	SET_CHECK(IDC_ORDER_CLICK_AUTO_MOVE_CHECK, nOrderClickAutoMove)
	SET_CHECK(IDC_SHOW_RIDER_HAS_COLOR_CHECK, nShowRiderHasColor)
	SET_CHECK(IDC_SHOW_COMPANY_ALL_CHECK, nShowCompayAll)
	SET_COMBO(IDC_SHOW_RIDER_CAPTION_LEVEL_COMBO, nShowRiderCaptionLevel)
	SET_CHECK(IDC_ORDER_CLICK_RIDER_MOVE_CHECK, nOrderClickRiderMove)
	SET_COMBO(IDC_RIDER_TAIL_SHOW_TIME_COMBO, nRiderTailShowTime)
	SET_CHECK(IDC_LOCATE_RIGHT_CHECK, bLocateRight)
	SET_CHECK(IDC_GPS_RIDER_ONLY_CHECK, nGpsRiderOnly)
	SET_CHECK(IDC_SHOW_ORDER_COUNT_CHECK, bShowOrderCount)
	SET_CHECK(IDC_ORDER_COUNT_8_CHECK, bOrderCount8)
	SET_CHECK(IDC_ORDER_COUNT_10_CHECK, bOrderCount10)
	SET_CHECK(IDC_ORDER_COUNT_11_CHECK, bOrderCount11)
	SET_CHECK(IDC_ORDER_COUNT_30_CHECK, bOrderCount30)
	SET_CHECK(IDC_ORDER_COUNT_31_CHECK, bOrderCount31)
	SET_CHECK(IDC_ORDER_COUNT_35_CHECK, bOrderCount35)
}

#define GET_CHECK(x, y)  m_info.y = ((CButton*)GetDlgItem(x))->GetCheck();
#define GET_COMBO(x, y)  m_info.y = ((CComboBox*)GetDlgItem(x))->GetCurSel();

void CRiderMapSetDlg::ResourceToStruct()
{
	m_info.nRiderAlloc = ((CButton*)GetDlgItem(IDC_RIDER_CHECK))->GetCheck();
	GET_CHECK(IDC_RIDER_CHECK, nRiderAlloc)
	GET_CHECK(IDC_RIDER_CHECK2, nRiderPickup)
	GET_CHECK(IDC_RIDER_CHECK3, nRiderBefore1)
	GET_CHECK(IDC_RIDER_CHECK4, nRiderBefore10)
	GET_CHECK(IDC_RIDER_CHECK5, nRiderBefore30)
	GET_CHECK(IDC_RIDER_CHECK6, nRiderAfter30)
	GET_CHECK(IDC_RIDER_CAPTION_CHECK, nRiderCaptionRNo)
	GET_CHECK(IDC_RIDER_CAPTION_CHECK2, nRiderCaptionName)
	GET_CHECK(IDC_RIDER_CAPTION_CHECK3, nRiderCaptionCompany)
	GET_CHECK(IDC_ORDER_CHECK, nOrderBefore10)
	GET_CHECK(IDC_ORDER_CHECK2, nOrderBefore20)
	GET_CHECK(IDC_ORDER_CHECK3	, nOrderBefore30)
	GET_CHECK(IDC_ORDER_CHECK4, nOrderBefore60)
	GET_CHECK(IDC_ORDER_CHECK5, nOrderAfter60)
	GET_CHECK(IDC_ORDER_CAPTION_CHECK, nOrderCaptionTime)
	GET_CHECK(IDC_ORDER_CAPTION_CHECK2, nOrderCaptionStart)
	GET_CHECK(IDC_ORDER_CAPTION_CHECK3, nOrderCaptionDest)
	GET_CHECK(IDC_ORDER_AUTO_REFRESH_CHECK, nOrderAutoRefresh)
	GET_COMBO(IDC_NEAR_RIDER_LEVEL_COMBO, nNearRiderLevel)
	GET_CHECK(IDC_SHOW_SECTOR_LIST_CHECK, nShowSectorList)
	GET_CHECK(IDC_HOVER_SHOW_RIDER_HAVE_ORDER_CHECK, nHoverShowRiderHaveOrder)
	GET_CHECK(IDC_SHOW_SHARE_RIDER_CHECK, nShowSectorList)
	GET_CHECK(IDC_SHOW_COMPLETE_ORDER_CHECK, nShowCompleteOrder)
	GET_CHECK(IDC_SHOW_CANCEL_ORDER_CHECK, nShowCancelOrder)
	GET_CHECK(IDC_ORDER_CLICK_AUTO_MOVE_CHECK, nOrderClickAutoMove)
	GET_CHECK(IDC_SHOW_RIDER_HAS_COLOR_CHECK, nShowRiderHasColor)
	GET_CHECK(IDC_SHOW_COMPANY_ALL_CHECK, nShowCompayAll)
	GET_COMBO(IDC_SHOW_RIDER_CAPTION_LEVEL_COMBO, nShowRiderCaptionLevel)
	GET_CHECK(IDC_ORDER_CLICK_RIDER_MOVE_CHECK, nOrderClickRiderMove)
	GET_COMBO(IDC_RIDER_TAIL_SHOW_TIME_COMBO, nRiderTailShowTime)
	GET_CHECK(IDC_LOCATE_RIGHT_CHECK, bLocateRight)
	GET_CHECK(IDC_GPS_RIDER_ONLY_CHECK, nGpsRiderOnly)
	GET_CHECK(IDC_SHOW_ORDER_COUNT_CHECK, bShowOrderCount)
	GET_CHECK(IDC_ORDER_COUNT_8_CHECK, bOrderCount8)
	GET_CHECK(IDC_ORDER_COUNT_10_CHECK, bOrderCount10)
	GET_CHECK(IDC_ORDER_COUNT_11_CHECK, bOrderCount11)
	GET_CHECK(IDC_ORDER_COUNT_30_CHECK, bOrderCount30)
	GET_CHECK(IDC_ORDER_COUNT_31_CHECK, bOrderCount31)
	GET_CHECK(IDC_ORDER_COUNT_35_CHECK, bOrderCount35)
}

void CRiderMapSetDlg::OnBnClickedShowGpsSignalBtn()
{
	CRiderGpsSignalDlg dlg;
	dlg.DoModal();
}

void CRiderMapSetDlg::OnBnClickedCheckBox()
{
	ResourceToStruct();
	LF->SaveToReg(m_info);
	((CRiderMapNormalForm*)m_pParentWnd)->RefreshFromSetupDlg();
}

void CRiderMapSetDlg::OnCbnSelchangeNearRiderLevelCombo()
{
	ResourceToStruct();
	LF->SaveToReg(m_info);
}

void CRiderMapSetDlg::OnBnClickedGpsRiderOnlyCheck()
{
	BOOL bEnable = !((CButton*)GetDlgItem(IDC_GPS_RIDER_ONLY_CHECK))->GetCheck();

	GetDlgItem(IDC_RIDER_CHECK)->EnableWindow(bEnable);
	GetDlgItem(IDC_RIDER_CHECK2)->EnableWindow(bEnable);
	GetDlgItem(IDC_RIDER_CHECK3)->EnableWindow(bEnable);
	GetDlgItem(IDC_RIDER_CHECK4)->EnableWindow(bEnable);
	GetDlgItem(IDC_RIDER_CHECK5)->EnableWindow(bEnable);
	GetDlgItem(IDC_RIDER_CHECK6)->EnableWindow(bEnable);

	OnBnClickedCheckBox();
}
