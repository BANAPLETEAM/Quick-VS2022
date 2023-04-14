// SetRcpPageDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SetRcpPageDlg.h"
#include "PersonOptionDlg.h"
#include "RcpView.h"
// CSetRcpPageDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetRcpPageDlg, CMyDialog)
CSetRcpPageDlg::CSetRcpPageDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetRcpPageDlg::IDD, pParent)
{
	m_bShowMapForm = FALSE;
}

CSetRcpPageDlg::~CSetRcpPageDlg()
{
}

void CSetRcpPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RESERVE_COUNT_COMBO, m_cmbReserveCount);

	DDX_Control(pDX, IDC_COLOR_STATIC1, m_stcColor1);
	DDX_Control(pDX, IDC_COLOR_STATIC2, m_stcColor2);
	DDX_Control(pDX, IDC_COLOR_STATIC3, m_stcColor3);
	DDX_Control(pDX, IDC_COLOR_STATIC4, m_stcColor4);
	DDX_Control(pDX, IDC_COLOR_STATIC5, m_stcColor5);
	DDX_Control(pDX, IDC_COLOR_STATIC6, m_stcColor6);
	DDX_Control(pDX, IDC_COLOR_STATIC7, m_stcColor7);
	DDX_Control(pDX, IDC_COLOR_STATIC8, m_stcColor8);
	DDX_Control(pDX, IDC_COLOR_STATIC9, m_stcColor9);
	DDX_Control(pDX, IDC_COLOR_STATIC10, m_stcColor10);
	DDX_Control(pDX, IDC_COLOR_STATIC12, m_stcColor12);
	DDX_Control(pDX, IDC_COLOR_STATICA, m_stcColorA);

	DDX_Control(pDX, IDC_TEXT_COLOR_BTN1, m_cpTextColor1);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN2, m_cpTextColor2);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN3, m_cpTextColor3);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN4, m_cpTextColor4);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN5, m_cpTextColor5);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN6, m_cpTextColor6);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN7, m_cpTextColor7);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN8, m_cpTextColor8);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN9, m_cpTextColor9);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTN10, m_cpTextColor10);
	DDX_Control(pDX, IDC_TEXT_COLOR_BTNA, m_cpTextColorA);

	DDX_Control(pDX, IDC_BACK_COLOR_BTN1, m_cpBackColor1);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN2, m_cpBackColor2);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN3, m_cpBackColor3);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN4, m_cpBackColor4);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN5, m_cpBackColor5);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN6, m_cpBackColor6);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN7, m_cpBackColor7);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN8, m_cpBackColor8);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN9, m_cpBackColor9);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN10, m_cpBackColor10);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN12, m_cpBackColor12);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN15, m_cpBackColor15);

	DDX_Control(pDX, IDC_FONT_COMBO, m_cmbFont);
	DDX_Control(pDX, IDC_FONT_SIZE_COMBO, m_cmbFontSize);
	DDX_Control(pDX, IDC_FONT_TEXT_EDIT, m_edtFontText);
	DDX_Control(pDX, IDC_BOLD_CHECK, m_chkBold);
	DDX_Control(pDX, IDC_SHOW_MAP_FORM_BTN, m_btnShowMapForm);
	DDX_Control(pDX, IDC_NOT_CREATE_MAP_FORM_CHECK, m_chkNotCreateMapForm);
	//DDX_Control(pDX, IDC_SCROLL_TO_TOP_CHECK, m_chkScrollToTop);	

	DDX_Control(pDX, IDC_APPLY_HEIGHT_CHECK, m_chkApplyHeight);	
	DDX_Control(pDX, IDC_APPLY_HEIGHT_COMBO, m_cmbApplyCombo);	
	DDX_Control(pDX, IDC_COLOR_STATIC15, m_stcColor15);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO1, m_cmbStateNumber1);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO2, m_cmbStateNumber2);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO3, m_cmbStateNumber3);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO4, m_cmbStateNumber4);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO5, m_cmbStateNumber5);
	DDX_Control(pDX, IDC_STATE_NUMBER_COMBO6, m_cmbStateNumber6);
}


BEGIN_MESSAGE_MAP(CSetRcpPageDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN1, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN2, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN3, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN4, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN5, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN6, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN7, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN8, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN9, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN10, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTNA, OnSelEndOkTextColor)

	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN1, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN2, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN3, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN4, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN5, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN6, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN7, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN8, OnSelEndOkBackColor)	
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN9, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN10, OnSelEndOkBackColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN12, OnSelEndOkBackColor)
	ON_BN_CLICKED(IDC_DEFAULT_COLOR_BTN, OnBnClickedDefaultColorBtn)

	ON_CBN_SELENDOK(IDC_FONT_COMBO, OnSelEndOKFontCombo)
	ON_CBN_SELCHANGE(IDC_FONT_COMBO, OnCbnSelchangeFontCombo)
	ON_CBN_SELCHANGE(IDC_FONT_SIZE_COMBO, OnCbnSelchangeFontSizeCombo)
	ON_BN_CLICKED(IDC_BOLD_CHECK, OnBnClickedBoldCheck)
	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_SHOW_MAP_FORM_BTN, OnBnClickedShowMapForm)
	ON_BN_CLICKED(IDC_APPLY_HEIGHT_CHECK, OnBnClickedApplyHeight)
	ON_BN_CLICKED(IDC_SAVE_COMPANY_SETTING_BTN, OnSaveCompanySettingBtn)
	ON_BN_CLICKED(IDC_LOAD_COMPANY_SETTING_BTN, OnLoadCompanySettingBtn)
	ON_BN_CLICKED(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK, &CSetRcpPageDlg::OnBnClickedUseCardOkNumberAddColumnCheck)
	ON_BN_CLICKED(IDC_INSUNG_COLOR_BTN, OnBnClickedInsungColorBtn)
	ON_BN_CLICKED(IDC_SAVE_MAIN_COLUMN_BTN, &CSetRcpPageDlg::OnBnClickedSaveMainColumnBtn)
	ON_BN_CLICKED(IDC_LOAD_MAIN_COLUMN_BTN, &CSetRcpPageDlg::OnBnClickedLoadMainColumnBtn)
	ON_BN_CLICKED(IDC_SAVE_CTI_COLUMN_BTN, &CSetRcpPageDlg::OnBnClickedSaveCtiColumnBtn)
	ON_BN_CLICKED(IDC_LOAD_CTI_COLUMN_BTN, &CSetRcpPageDlg::OnBnClickedLoadCtiColumnBtn)
END_MESSAGE_MAP()



// CSetRcpPageDlg 메시지 처리기입니다.

BOOL CSetRcpPageDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nItem = m_cmbReserveCount.AddString("무제한");
	m_cmbReserveCount.SetItemData(nItem, 0);
	for(int i = 1; i < 30; i++)
	{
		CString strCount;
		strCount.Format("%d개", i);
		int nItem = m_cmbReserveCount.AddString(strCount);
		m_cmbReserveCount.SetItemData(nItem, i);
	}


	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state1", 1));
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state2", 1));
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state3", 1));
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state4", 1));
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state5", 1));
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state6", 1));
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state7", 1));
	((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state8", 1));
	((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "state9", 1));

	int nReserveCount = AfxGetApp()->GetProfileInt("RcpPage", "ReserveCount", 0);
	for(int i = 0; i < m_cmbReserveCount.GetCount(); i++)
	{
		if(m_cmbReserveCount.GetItemData(i) == nReserveCount)
		{
	        m_cmbReserveCount.SetCurSel(i);
			break;
		}
	}

	((CButton*)GetDlgItem(IDC_STATE_SECOND_SORT_CHECK))->SetCheck(
				AfxGetApp()->GetProfileInt("RcpPage", "StateSecondSort", 0));

	((CButton*)GetDlgItem(IDC_NOT_CREATE_MAP_FORM_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpMapSetup", "nNotCreateMapForm", 0));

	//((CButton*)GetDlgItem(IDC_SCROLL_TO_TOP_CHECK))->SetCheck(
	//			AfxGetApp()->GetProfileInt("RcpPage", "ScrollToTop", 0));

	((CButton*)GetDlgItem(IDC_GET_CUSTOMER_MEMO_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "GetCustomerMemo", 0));

	((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "CardOkNumberAddColumn", 0));

	((CButton*)GetDlgItem(IDC_SHOW_RESERVE_ORDER_DAY_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "ShowReserveOrderDay", 0));

	((CButton*)GetDlgItem(IDC_IGNORE_STATE_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "IgnoreCheckState", 1));

	((CButton*)GetDlgItem(IDC_NOT_USE_STATE_CHANGE_MSG_BOX_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "NotUseStateChangeMsgBox", 0));

	((CButton*)GetDlgItem(IDC_USE_NAVER_POI_TO_CUSTOMER_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "UseNaverPoiToCustomer", 1));

	((CButton*)GetDlgItem(IDC_USE_PICKUP_NOT_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "UsePickupNot", 0));

	((CButton*)GetDlgItem(IDC_REMOVE_SEARCH_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "RemoveSearch", 0));

	((CButton*)GetDlgItem(IDC_ADD_TACKSONG_CHAGE_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongCharge", 0));

	((CButton*)GetDlgItem(IDC_ADD_TACKSONG_DRIVING_CHAGE_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "AddTacksongDrivingCharge", 0));

	((CButton*)GetDlgItem(IDC_SEARCH_WITH_NO_WNAME_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "SearchWithNoWName", 0));

	((CButton*)GetDlgItem(IDC_RECV_ATTEND_MSG_CHECK))->SetCheck(
		AfxGetApp()->GetProfileInt("RcpPage", "RecvAttendMsg", 1));

	RefreshColor(); 
	RefreshOrderStateSort();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetRcpPageDlg::RefreshOrderStateSort()
{
	CString strOrderSort = AfxGetApp()->GetProfileString("RcpPage", "OrderStateSort", "");

	if(strOrderSort.IsEmpty())
	{
		m_cmbStateNumber1.SetCurSel(0);
		m_cmbStateNumber2.SetCurSel(1);
		m_cmbStateNumber3.SetCurSel(2);
		m_cmbStateNumber4.SetCurSel(3);
		m_cmbStateNumber5.SetCurSel(4);
		m_cmbStateNumber6.SetCurSel(5);
	}
	else
	{
		long nFirstFind = 0;
		long nSecondFind = 0;
		long nState = 0;
		CComboBox *pCmb = NULL;

		for(int i=0; i<::GetCommaCount(strOrderSort); i++)
		{
			nSecondFind = strOrderSort.Find(";", nFirstFind);
			nState = _ttoi(strOrderSort.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == 0) pCmb = &m_cmbStateNumber1;
			else if(i == 1) pCmb = &m_cmbStateNumber2;
			else if(i == 2) pCmb = &m_cmbStateNumber3;
			else if(i == 3) pCmb = &m_cmbStateNumber4;
			else if(i == 4) pCmb = &m_cmbStateNumber5;
			else if(i == 5) pCmb = &m_cmbStateNumber6;

			SetCombo(pCmb, nState);

			nFirstFind = nSecondFind + 1;

		}
	}
}

void CSetRcpPageDlg::SetCombo(CComboBox *pCmb, long nState)
{
	BOOL bSelect = FALSE;
	CString strState = GetStateString(nState);
	
	for(int i=0; i<pCmb->GetCount(); i++)
	{
		CString strText; pCmb->GetLBText(i, strText);

		if(strText == strState)
		{
			pCmb->SetCurSel(i);
			bSelect = TRUE;
			break;			
		}
	}

	if(bSelect == FALSE)
		pCmb->SetCurSel(0);
}

CString CSetRcpPageDlg::GetCombo(CComboBox *pCmb)
{
	CString strText;
	pCmb->GetLBText(pCmb->GetCurSel(), strText);

	long nState = GetStateFromString(strText);

	return GetStringFromLong(nState) + ";";
}

void CSetRcpPageDlg::SaveOrderStateSort()
{
	CString strOrderSort = "";
	strOrderSort += GetCombo(&m_cmbStateNumber1);
	strOrderSort += GetCombo(&m_cmbStateNumber2);
	strOrderSort += GetCombo(&m_cmbStateNumber3);
	strOrderSort += GetCombo(&m_cmbStateNumber4);
	strOrderSort += GetCombo(&m_cmbStateNumber5);
	strOrderSort += GetCombo(&m_cmbStateNumber6);

	AfxGetApp()->WriteProfileString("RcpPage", "OrderStateSort", strOrderSort);	
}

void CSetRcpPageDlg::RefreshColor()
{
	COLORREF crText, crBack;

	m_stcColor1.SetWindowText("접수");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor1", STATE_COLOR_TX1);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor1", STATE_COLOR_BK1);
	m_cpTextColor1.SetColor(crText);
	m_cpBackColor1.SetColor(crBack);
	m_stcColor1.SetTextColor(crText);
	m_stcColor1.SetBkColor(crBack);

	m_stcColor2.SetWindowText("대기");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor2", STATE_COLOR_TX2);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor2", STATE_COLOR_BK2);
	m_cpTextColor2.SetColor(crText);
	m_cpBackColor2.SetColor(crBack);
	m_stcColor2.SetTextColor(crText);
	m_stcColor2.SetBkColor(crBack);

	m_stcColor3.SetWindowText("예약");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor3", STATE_COLOR_TX3);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor3", STATE_COLOR_BK3);
	m_cpTextColor3.SetColor(crText);
	m_cpBackColor3.SetColor(crBack);
	m_stcColor3.SetTextColor(crText);
	m_stcColor3.SetBkColor(crBack);

	m_stcColor4.SetWindowText("개별");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor4", STATE_COLOR_TX4);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor4", STATE_COLOR_BK4);
	m_cpTextColor4.SetColor(crText);
	m_cpBackColor4.SetColor(crBack);
	m_stcColor4.SetTextColor(crText);
	m_stcColor4.SetBkColor(crBack);

	m_stcColor5.SetWindowText("배차");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor5", STATE_COLOR_TX5);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor5", STATE_COLOR_BK5);
	m_cpTextColor5.SetColor(crText);
	m_cpBackColor5.SetColor(crBack);
	m_stcColor5.SetTextColor(crText);
	m_stcColor5.SetBkColor(crBack);

	m_stcColor6.SetWindowText("픽업");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor6", STATE_COLOR_TX6);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor6", STATE_COLOR_BK6);
	m_cpTextColor6.SetColor(crText);
	m_cpBackColor6.SetColor(crBack);
	m_stcColor6.SetTextColor(crText);
	m_stcColor6.SetBkColor(crBack);

	m_stcColor7.SetWindowText("완료");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor7", STATE_COLOR_TX7);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor7", STATE_COLOR_BK7);
	m_cpTextColor7.SetColor(crText);
	m_cpBackColor7.SetColor(crBack);
	m_stcColor7.SetTextColor(crText);
	m_stcColor7.SetBkColor(crBack);

	m_stcColor8.SetWindowText("취소");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor8", STATE_COLOR_TX8);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor8", STATE_COLOR_BK8);
	m_cpTextColor8.SetColor(crText);
	m_cpBackColor8.SetColor(crBack);
	m_stcColor8.SetTextColor(crText);
	m_stcColor8.SetBkColor(crBack);

	m_stcColor9.SetWindowText("문의");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor9", STATE_COLOR_TX9);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor9", STATE_COLOR_BK9);
	m_cpTextColor9.SetColor(crText);
	m_cpBackColor9.SetColor(crBack);
	m_stcColor9.SetTextColor(crText);
	m_stcColor9.SetBkColor(crBack);

	m_stcColor10.SetWindowText("인터넷");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColor10", STATE_COLOR_TX10);
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor10", STATE_COLOR_BK10);
	m_cpTextColor10.SetColor(crText);
	m_cpBackColor10.SetColor(crBack);
	m_stcColor10.SetTextColor(crText);
	m_stcColor10.SetBkColor(crBack);

	m_stcColor12.SetWindowText("선택오더의 배경색(글자색은 자동반전됨)");
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor12", STATE_COLOR_BK12);
	m_cpBackColor12.SetColor(crBack);
	m_stcColor12.SetTextColor(RGB(
		(255 - GetRValue(crBack)), 
		(255 - GetGValue(crBack)), 
		(255 - GetBValue(crBack))));
	m_stcColor12.SetBkColor(crBack == 0 ? 1 : crBack);


	m_stcColorA.SetWindowText("접수/대기/예약상태 출발동/도착동 글자색");
	crText = AfxGetApp()->GetProfileInt("RcpPage", "TextColorA", STATE_COLOR_TXA);
	m_cpTextColorA.SetColor(crText);
	m_stcColorA.SetTextColor(crText);
	m_stcColorA.SetBkColor(RGB(255, 255, 255));


	m_stcColor15.SetWindowText("배차 20분후 픽업 상태 미변경시");
	crBack = AfxGetApp()->GetProfileInt("RcpPage", "BackColor15", STATE_COLOR_BK12);
	m_cpBackColor15.SetColor(crBack);
	m_stcColor15.SetTextColor(RGB(
		(255 - GetRValue(crBack)), 
		(255 - GetGValue(crBack)), 
		(255 - GetBValue(crBack))));
	m_stcColor15.SetBkColor(crBack == 0 ? 1 : crBack);

	CString strFontName = AfxGetApp()->GetProfileString("RcpPage", "FontName", "맑은 고딕");
	CString strFontSize = AfxGetApp()->GetProfileString("RcpPage", "FontHeight", "15");
	m_chkBold.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "FontBold", 1));
	
	
	m_cmbFont.InitControl(strFontName);
	if(m_cmbFontSize.SelectString(-1, strFontSize))
	{
		m_cmbFontSize.SetWindowText(strFontSize);
	}

	CString strDisplay = "SAMPLE - 로지소프트 세상을 움직이는 기술";
	m_edtFontText.SetMyFont(strFontName, atol(strFontSize), m_chkBold.GetCheck() ? FW_BOLD : FW_NORMAL);
	m_edtFontText.SetWindowText(strDisplay);
	m_edtFontText.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), strDisplay, FALSE);

	CString strColHeight = AfxGetApp()->GetProfileString("RcpPage", "ColHeight", "15");
	m_chkApplyHeight.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "ApplyHeight", 0));
	m_cmbApplyCombo.SetWindowText(strColHeight);

	OnBnClickedApplyHeight();
}


void CSetRcpPageDlg::OnBnClickedOk()
{
	AfxGetApp()->WriteProfileInt("RcpPage", "state1", ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state2", ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state3", ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state4", ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state5", ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state6", ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state7", ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state8", ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "state9", ((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck());

	int nReserveCount = m_cmbReserveCount.GetItemData(m_cmbReserveCount.GetCurSel());
	AfxGetApp()->WriteProfileInt("RcpPage", "ReserveCount", nReserveCount);
	AfxGetApp()->WriteProfileInt("RcpPage", "StateSecondSort", 
				((CButton*)GetDlgItem(IDC_STATE_SECOND_SORT_CHECK))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpMapSetup", "nNotCreateMapForm", 
				((CButton*)GetDlgItem(IDC_NOT_CREATE_MAP_FORM_CHECK))->GetCheck());
	AfxGetApp()->WriteProfileInt("RcpPage", "GetCustomerMemo", 
		((CButton*)GetDlgItem(IDC_GET_CUSTOMER_MEMO_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "CardOkNumberAddColumn", 
		((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "GetCustomerMemo", 
		((CButton*)GetDlgItem(IDC_GET_CUSTOMER_MEMO_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "ShowReserveOrderDay", 
		((CButton*)GetDlgItem(IDC_SHOW_RESERVE_ORDER_DAY_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "IgnoreCheckState", 
		((CButton*)GetDlgItem(IDC_IGNORE_STATE_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "NotUseStateChangeMsgBox", 
		((CButton*)GetDlgItem(IDC_NOT_USE_STATE_CHANGE_MSG_BOX_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "UseNaverPoiToCustomer", 
		((CButton*)GetDlgItem(IDC_USE_NAVER_POI_TO_CUSTOMER_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "UsePickupNot", 
		((CButton*)GetDlgItem(IDC_USE_PICKUP_NOT_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "RemoveSearch", 
		((CButton*)GetDlgItem(IDC_REMOVE_SEARCH_CHECK))->GetCheck());
	
	AfxGetApp()->WriteProfileInt("RcpPage", "AddTacksongCharge", 
		((CButton*)GetDlgItem(IDC_ADD_TACKSONG_CHAGE_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "AddTacksongDrivingCharge", 
		((CButton*)GetDlgItem(IDC_ADD_TACKSONG_DRIVING_CHAGE_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "SearchWithNoWName", 
		((CButton*)GetDlgItem(IDC_SEARCH_WITH_NO_WNAME_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "RecvAttendMsg", 
		((CButton*)GetDlgItem(IDC_RECV_ATTEND_MSG_CHECK))->GetCheck());

	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor1", m_cpTextColor1.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor2", m_cpTextColor2.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor3", m_cpTextColor3.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor4", m_cpTextColor4.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor5", m_cpTextColor5.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor6", m_cpTextColor6.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor7", m_cpTextColor7.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor8", m_cpTextColor8.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor9", m_cpTextColor9.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColor10", m_cpTextColor10.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "TextColorA", m_cpTextColorA.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor1", m_cpBackColor1.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor2", m_cpBackColor2.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor3", m_cpBackColor3.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor4", m_cpBackColor4.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor5", m_cpBackColor5.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor6", m_cpBackColor6.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor7", m_cpBackColor7.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor8", m_cpBackColor8.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor9", m_cpBackColor9.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor10", m_cpBackColor10.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor12", m_cpBackColor12.GetColor());
	AfxGetApp()->WriteProfileInt("RcpPage", "BackColor15", m_cpBackColor15.GetColor());

	CXTLogFont lf;
	CString strFontSize;
	m_cmbFont.GetSelFont(lf);
	m_cmbFontSize.GetWindowText(strFontSize);

	AfxGetApp()->WriteProfileString("RcpPage", "FontName", lf.lfFaceName);
	AfxGetApp()->WriteProfileString("RcpPage", "FontHeight", strFontSize);
	AfxGetApp()->WriteProfileInt("RcpPage", "FontBold", m_chkBold.GetCheck());

	CString strHeight;
	m_cmbApplyCombo.GetWindowText(strHeight);
	AfxGetApp()->WriteProfileString("RcpPage", "ColHeight", strHeight);
	AfxGetApp()->WriteProfileInt("RcpPage", "ApplyHeight", m_chkApplyHeight.GetCheck());

	SaveOrderStateSort();

	OnOK();
}

void CSetRcpPageDlg::OnSelEndOkTextColor()
{
	m_stcColor1.SetTextColor(m_cpTextColor1.GetColor());
	m_stcColor2.SetTextColor(m_cpTextColor2.GetColor());
	m_stcColor3.SetTextColor(m_cpTextColor3.GetColor());
	m_stcColor4.SetTextColor(m_cpTextColor4.GetColor());
	m_stcColor5.SetTextColor(m_cpTextColor5.GetColor());
	m_stcColor6.SetTextColor(m_cpTextColor6.GetColor());
	m_stcColor7.SetTextColor(m_cpTextColor7.GetColor());
	m_stcColor8.SetTextColor(m_cpTextColor8.GetColor());
	m_stcColor9.SetTextColor(m_cpTextColor9.GetColor());
	m_stcColor10.SetTextColor(m_cpTextColor10.GetColor());
	m_stcColorA.SetTextColor(m_cpTextColorA.GetColor());
}


void CSetRcpPageDlg::OnSelEndOkBackColor()
{
	COLORREF clrSelected = m_cpBackColor12.GetColor();

	m_stcColor1.SetBkColor(m_cpBackColor1.GetColor());
	m_stcColor2.SetBkColor(m_cpBackColor2.GetColor());
	m_stcColor3.SetBkColor(m_cpBackColor3.GetColor());
	m_stcColor4.SetBkColor(m_cpBackColor4.GetColor());
	m_stcColor5.SetBkColor(m_cpBackColor5.GetColor());
	m_stcColor6.SetBkColor(m_cpBackColor6.GetColor());
	m_stcColor7.SetBkColor(m_cpBackColor7.GetColor());
	m_stcColor8.SetBkColor(m_cpBackColor8.GetColor());
	m_stcColor9.SetBkColor(m_cpBackColor9.GetColor());
	m_stcColor10.SetBkColor(m_cpBackColor10.GetColor());
	m_stcColor12.SetBkColor(clrSelected);
	m_stcColor12.SetTextColor(RGB(
		(255 - GetRValue(clrSelected)), 
		(255 - GetGValue(clrSelected)), 
		(255 - GetBValue(clrSelected))));
}


void CSetRcpPageDlg::OnBnClickedDefaultColorBtn()
{
	m_cpTextColor1.SetColor(STATE_COLOR_TX1);
	m_cpTextColor2.SetColor(STATE_COLOR_TX2);
	m_cpTextColor3.SetColor(STATE_COLOR_TX3);
	m_cpTextColor4.SetColor(STATE_COLOR_TX4);
	m_cpTextColor5.SetColor(STATE_COLOR_TX5);
	m_cpTextColor6.SetColor(STATE_COLOR_TX6);
	m_cpTextColor7.SetColor(STATE_COLOR_TX7);
	m_cpTextColor8.SetColor(STATE_COLOR_TX8);
	m_cpTextColor9.SetColor(STATE_COLOR_TX9);
	m_cpTextColor10.SetColor(STATE_COLOR_TX10);
	m_cpTextColorA.SetColor(STATE_COLOR_TXA);

	m_cpBackColor1.SetColor(STATE_COLOR_BK1);
	m_cpBackColor2.SetColor(STATE_COLOR_BK2);
	m_cpBackColor3.SetColor(STATE_COLOR_BK3);
	m_cpBackColor4.SetColor(STATE_COLOR_BK4);
	m_cpBackColor5.SetColor(STATE_COLOR_BK5);
	m_cpBackColor6.SetColor(STATE_COLOR_BK6);
	m_cpBackColor7.SetColor(STATE_COLOR_BK7);
	m_cpBackColor8.SetColor(STATE_COLOR_BK8);
	m_cpBackColor9.SetColor(STATE_COLOR_BK9);
	m_cpBackColor10.SetColor(STATE_COLOR_BK10);
	m_cpBackColor12.SetColor(STATE_COLOR_BK12);
	m_cpBackColor15.SetColor(STATE_COLOR_BK12);

	OnSelEndOkTextColor();
	OnSelEndOkBackColor();
}

void CSetRcpPageDlg::OnSelEndOKFontCombo()
{
	CXTLogFont lf;
	CString strFontSize;
	m_cmbFont.GetSelFont(lf);
	m_cmbFontSize.GetWindowText(strFontSize);
	m_edtFontText.SetMyFont(lf.lfFaceName, atol(strFontSize), m_chkBold.GetCheck() ? FW_BOLD : FW_NORMAL);
}


void CSetRcpPageDlg::OnCbnSelchangeFontCombo()
{
	OnSelEndOKFontCombo();
}

void CSetRcpPageDlg::OnCbnSelchangeFontSizeCombo()
{
	OnSelEndOKFontCombo();
}

void CSetRcpPageDlg::OnBnClickedBoldCheck()
{
	OnSelEndOKFontCombo();
}

void CSetRcpPageDlg::OnBnClickedAddBtn()
{
	CPersonOptionDlg dlg;
	dlg.DoModal();
}

void CSetRcpPageDlg::OnBnClickedShowMapForm()
{
	m_bShowMapForm = TRUE; 
	OnOK();
}

void CSetRcpPageDlg::OnBnClickedApplyHeight()
{
	m_cmbApplyCombo.EnableWindow(m_chkApplyHeight.GetCheck());
}

void CSetRcpPageDlg::OnSaveCompanySettingBtn()
{
	if(m_ui.nRole != 0)
	{
		MessageBox("관리자만 저장 가능합니다.", "확인", MB_ICONEXCLAMATION);
		return;
	}

	if(IDYES != MessageBox("현재 설정을 회사표준 설정으로 업데이트 하시겠습니까?", 
		"확인", 
		MB_ICONQUESTION | MB_YESNO))
	{
		return;
	}

	CMkCommand pCmd(m_pMkDb);
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck());

	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_STATE_SECOND_SORT_CHECK))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_NOT_CREATE_MAP_FORM_CHECK))->GetCheck());
	pCmd.AddParameter(0);
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_GET_CUSTOMER_MEMO_CHECK))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->GetCheck());
	pCmd.AddParameter(((CButton*)GetDlgItem(IDC_SHOW_RESERVE_ORDER_DAY_CHECK))->GetCheck());
	
	pCmd.AddParameter((long)m_cpTextColor1.GetColor());
	pCmd.AddParameter((long)m_cpTextColor2.GetColor());
	pCmd.AddParameter((long)m_cpTextColor3.GetColor());
	pCmd.AddParameter((long)m_cpTextColor4.GetColor());
	pCmd.AddParameter((long)m_cpTextColor5.GetColor());
	pCmd.AddParameter((long)m_cpTextColor6.GetColor()); 
	pCmd.AddParameter((long)m_cpTextColor7.GetColor());
	pCmd.AddParameter((long)m_cpTextColor8.GetColor());
	pCmd.AddParameter((long)m_cpTextColor9.GetColor());
	pCmd.AddParameter((long)m_cpTextColor10.GetColor());
	pCmd.AddParameter((long)m_cpBackColor12.GetColor());
	pCmd.AddParameter((long)m_cpTextColorA.GetColor());

	pCmd.AddParameter((long)m_cpBackColor1.GetColor());
	pCmd.AddParameter((long)m_cpBackColor2.GetColor());
	pCmd.AddParameter((long)m_cpBackColor3.GetColor());
	pCmd.AddParameter((long)m_cpBackColor4.GetColor());
	pCmd.AddParameter((long)m_cpBackColor5.GetColor());
	pCmd.AddParameter((long)m_cpBackColor6.GetColor());
	pCmd.AddParameter((long)m_cpBackColor7.GetColor());
	pCmd.AddParameter((long)m_cpBackColor8.GetColor());
	pCmd.AddParameter((long)m_cpBackColor9.GetColor());
	pCmd.AddParameter((long)m_cpBackColor10.GetColor());

	CXTLogFont lf;
	CString strFontSize;
	m_cmbFont.GetSelFont(lf);
	m_cmbFontSize.GetWindowText(strFontSize);

	pCmd.AddParameter(lf.lfFaceName);
	pCmd.AddParameter(atol(strFontSize));
	pCmd.AddParameter(m_chkBold.GetCheck());

	CString strDelayMin, strRejectCount;
	//	m_cmbDelayMin.GetWindowText(strDelayMin);
	//	m_cmbRejectCount.GetWindowText(strRejectCount);

	pCmd.AddParameter(atol(strDelayMin));
	pCmd.AddParameter(atol(strRejectCount));

	pCmd.AddParameter(m_ui.strName);
 
	if(pCmd.Execute("update_rcp_page_option_2"))
	{
		MessageBox("회사표준 설정을 업데이트 하였습니다.", "확인", MB_ICONINFORMATION);
	}

}

void CSetRcpPageDlg::OnLoadCompanySettingBtn()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rcp_page_option_1");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	if(pRs.Execute(&pCmd))
	{
		if(pRs.IsEOF())
		{
			MessageBox("회사표준 설정 데이터가 존재하지 않습니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		long nState1;  
		long nState2;  
		long nState3;  
		long nState4;  
		long nState5;  
		long nState6;  
		long nState7;  
		long nState8;  
		long nState9;  
		long nStateSecondSort;  
		long nTextColor1;  
		long nTextColor2;  
		long nTextColor3;  
		long nTextColor4;  
		long nTextColor5;  
		long nTextColor6;  
		long nTextColor7;  
		long nTextColor8;  
		long nTextColor9;  
		long nTextColor10;  
		long nTextColor11;
		long nTextColorA;
		long nBackColor1;  
		long nBackColor2;  
		long nBackColor3;  
		long nBackColor4;  
		long nBackColor5;  
		long nBackColor6;  
		long nBackColor7;  
		long nBackColor8;  
		long nBackColor9;  
		long nBackColor10;  
		CString sFontFaceName;  
		long nFontSize;  
		long nFontBold;  
		long nDelayMin;  
		long nRejectCount;  
		CString sWName;  
		COleDateTime dtWrite;
		long nNotCreateMapForm;
		long nScrollToTop;
		long nGetCustomerMemo;
		long nUseCardOkNumberAddColumn;
		long nShowReserveOrderDay;

		pRs.GetFieldValue("nState1", nState1);
		pRs.GetFieldValue("nState2", nState2);
		pRs.GetFieldValue("nState3", nState3);
		pRs.GetFieldValue("nState4", nState4);
		pRs.GetFieldValue("nState5", nState5);
		pRs.GetFieldValue("nState6", nState6);
		pRs.GetFieldValue("nState7", nState7);
		pRs.GetFieldValue("nState8", nState8);
		pRs.GetFieldValue("nState9", nState9);
		pRs.GetFieldValue("nStateSecondSort", nStateSecondSort);
		pRs.GetFieldValue("nNotCreateMapForm", nNotCreateMapForm);
		pRs.GetFieldValue("nScrollToTop", nScrollToTop);
		pRs.GetFieldValue("nGetCustomerMemo", nGetCustomerMemo);
		pRs.GetFieldValue("nShowReserveOrderDay", nShowReserveOrderDay);

		//pRs.GetFieldValue("nNoSumInqueryCount", nNoSumInqueryCount);
		//pRs.GetFieldValue("nShowRcpStateMsg", nShowRcpStateMsg);
		//pRs.GetFieldValue("nHideWaitStateMsg", nHideWaitStateMsg);
		//pRs.GetFieldValue("nShowNotCompleteMsg",nShowNotCompleteMsg);
		//pRs.GetFieldValue("nMainListStartPOIShowType", nMainListStartPOIShowType);
		//pRs.GetFieldValue("nWaitToRcpNoMsg", nWaitToRcpNoMsg);
		pRs.GetFieldValue("nTextColor1", nTextColor1);
		pRs.GetFieldValue("nTextColor2", nTextColor2);
		pRs.GetFieldValue("nTextColor3", nTextColor3);
		pRs.GetFieldValue("nTextColor4", nTextColor4);
		pRs.GetFieldValue("nTextColor5", nTextColor5);
		pRs.GetFieldValue("nTextColor6", nTextColor6);
		pRs.GetFieldValue("nTextColor7", nTextColor7);
		pRs.GetFieldValue("nTextColor8", nTextColor8);
		pRs.GetFieldValue("nTextColor9", nTextColor9);
		pRs.GetFieldValue("nTextColor10", nTextColor10);
		pRs.GetFieldValue("nTextColor11", nTextColor11);
		pRs.GetFieldValue("nTextColorA", nTextColorA);
		pRs.GetFieldValue("nBackColor1", nBackColor1);
		pRs.GetFieldValue("nBackColor2", nBackColor2);
		pRs.GetFieldValue("nBackColor3", nBackColor3);
		pRs.GetFieldValue("nBackColor4", nBackColor4);
		pRs.GetFieldValue("nBackColor5", nBackColor5);
		pRs.GetFieldValue("nBackColor6", nBackColor6);
		pRs.GetFieldValue("nBackColor7", nBackColor7);
		pRs.GetFieldValue("nBackColor8", nBackColor8);
		pRs.GetFieldValue("nBackColor9", nBackColor9);
		pRs.GetFieldValue("nBackColor10", nBackColor10);
		pRs.GetFieldValue("sFontFaceName", sFontFaceName);
		pRs.GetFieldValue("nFontSize", nFontSize);
		pRs.GetFieldValue("nFontBold", nFontBold);
		pRs.GetFieldValue("nDelayMin", nDelayMin);
		pRs.GetFieldValue("nRejectCount", nRejectCount);
		pRs.GetFieldValue("nUseCardOkNumberAddColumn", nUseCardOkNumberAddColumn);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("dtWrite", dtWrite);

		CString strMsg;
		strMsg.Format("[%s]에 [%s]님이 저장하신 데이터를 불러오시겠습니까?\n"\
			"(로드후에 저장버튼 미클릭시 반영안됨)",
			dtWrite.Format("%Y-%m-%d %H:%M:%S"), 
			sWName);

		if(IDYES == MessageBox(strMsg, "확인", MB_ICONQUESTION | MB_YESNO))
		{
			RefreshColorServer(nTextColor1,
				nTextColor2,
				nTextColor3,
				nTextColor4,
				nTextColor5,
				nTextColor6,
				nTextColor7,
				nTextColor8,
				nTextColor9,
				nTextColor10,
				nTextColor11,
				nTextColorA,
				nBackColor1, 
				nBackColor2, 
				nBackColor3, 
				nBackColor4, 
				nBackColor5, 
				nBackColor6, 
				nBackColor7, 
				nBackColor8, 
				nBackColor9, 
				nBackColor10, 
				sFontFaceName,
				nFontSize, 
				nFontBold);

			RefreshMisc(
				nState1, 
				nState2, 
				nState3, 
				nState4, 
				nState5, 
				nState6, 
				nState7, 
				nState8, 
				nState9, 
				nStateSecondSort,
				nNotCreateMapForm,
				nScrollToTop,
				nGetCustomerMemo,
				nUseCardOkNumberAddColumn,
				nShowReserveOrderDay);
		}	
	}
}

void CSetRcpPageDlg::RefreshMisc(
								 int nState1, 
								 int nState2, 
								 int nState3, 
								 int nState4, 
								 int nState5, 
								 int nState6, 
								 int nState7, 
								 int nState8, 
								 int nState9, 
								 int nStateSecondSort,
								 int nNotCreateMapForm,
								 int nScrollToTop,
								 int nGetCustomerMemo,
								 int nUseCardOkNumberAddColumn,
								 int nShowReserveOrderDay)
{
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(nState1);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(nState2);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(nState3);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(nState4);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(nState5);
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(nState6);
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(nState7);
	((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(nState8);
	((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(nState9);

	((CButton*)GetDlgItem(IDC_STATE_SECOND_SORT_CHECK))->SetCheck(nStateSecondSort);
	((CButton*)GetDlgItem(IDC_NOT_CREATE_MAP_FORM_CHECK))->SetCheck(nNotCreateMapForm);
	//((CButton*)GetDlgItem(IDC_SCROLL_TO_TOP_CHECK))->SetCheck(nScrollToTop);
	((CButton*)GetDlgItem(IDC_GET_CUSTOMER_MEMO_CHECK))->SetCheck(nGetCustomerMemo);
	((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->SetCheck(nUseCardOkNumberAddColumn);
	((CButton*)GetDlgItem(IDC_SHOW_RESERVE_ORDER_DAY_CHECK))->SetCheck(nShowReserveOrderDay);

	//CString strDelayMin, strRejectCount;
	//strDelayMin.Format("%d", nDelayMin);
	//strRejectCount.Format("%d", nRejectCount);

	//	if(m_cmbDelayMin.SelectString(-1, strDelayMin))
	//		m_cmbDelayMin.SetWindowText(strDelayMin);

	//	if(m_cmbRejectCount.SelectString(-1, strRejectCount))
	//		m_cmbRejectCount.SetWindowText(strRejectCount);
}

void CSetRcpPageDlg::RefreshColorServer(COLORREF crText1,
								  COLORREF crText2,
								  COLORREF crText3,
								  COLORREF crText4,
								  COLORREF crText5,
								  COLORREF crText6,
								  COLORREF crText7,
								  COLORREF crText8,
								  COLORREF crText9,
								  COLORREF crText10,
								  COLORREF crText11,
								  COLORREF crTextA,
								  COLORREF crBack1, 
								  COLORREF crBack2, 
								  COLORREF crBack3, 
								  COLORREF crBack4, 
								  COLORREF crBack5, 
								  COLORREF crBack6, 
								  COLORREF crBack7, 
								  COLORREF crBack8, 
								  COLORREF crBack9, 
								  COLORREF crBack10, 
								  CString strFontName,
								  long nFontSize,
								  BOOL bBold)
{
	m_stcColor1.SetWindowText("접수");
	m_cpTextColor1.SetColor(crText1);
	m_cpBackColor1.SetColor(crBack1);
	m_stcColor1.SetTextColor(crText1);
	m_stcColor1.SetBkColor(crBack1);

	m_stcColor2.SetWindowText("대기");
	m_cpTextColor2.SetColor(crText2);
	m_cpBackColor2.SetColor(crBack2);
	m_stcColor2.SetTextColor(crText2);
	m_stcColor2.SetBkColor(crBack2);

	m_stcColor3.SetWindowText("예약");
	m_cpTextColor3.SetColor(crText3);
	m_cpBackColor3.SetColor(crBack3);
	m_stcColor3.SetTextColor(crText3);
	m_stcColor3.SetBkColor(crBack3);

	m_stcColor4.SetWindowText("개별");
	m_cpTextColor4.SetColor(crText4);
	m_cpBackColor4.SetColor(crBack4);
	m_stcColor4.SetTextColor(crText4);
	m_stcColor4.SetBkColor(crBack4);

	m_stcColor5.SetWindowText("배차");
	m_cpTextColor5.SetColor(crText5);
	m_cpBackColor5.SetColor(crBack5);
	m_stcColor5.SetTextColor(crText5);
	m_stcColor5.SetBkColor(crBack5);

	m_stcColor6.SetWindowText("픽업");
	m_cpTextColor6.SetColor(crText6);
	m_cpBackColor6.SetColor(crBack6);
	m_stcColor6.SetTextColor(crText6);
	m_stcColor6.SetBkColor(crBack6);

	m_stcColor7.SetWindowText("완료");
	m_cpTextColor7.SetColor(crText7);
	m_cpBackColor7.SetColor(crBack7);
	m_stcColor7.SetTextColor(crText7);
	m_stcColor7.SetBkColor(crBack7);

	m_stcColor8.SetWindowText("취소");
	m_cpTextColor8.SetColor(crText8);
	m_cpBackColor8.SetColor(crBack8);
	m_stcColor8.SetTextColor(crText8);
	m_stcColor8.SetBkColor(crBack8);

	m_stcColor9.SetWindowText("문의");
	m_cpTextColor9.SetColor(crText9);
	m_cpBackColor9.SetColor(crBack9);
	m_stcColor9.SetTextColor(crText9);
	m_stcColor9.SetBkColor(crBack9);

	m_stcColor10.SetWindowText("인터넷");
	m_cpTextColor10.SetColor(crText10);
	m_cpBackColor10.SetColor(crBack10);
	m_stcColor10.SetTextColor(crText10);
	m_stcColor10.SetBkColor(crBack10);

	m_stcColor12.SetWindowText("선택오더의 배경색(글자색은 자동반전됨)");
	m_cpBackColor12.SetColor(crText11);
	m_stcColor12.SetTextColor(RGB(
		(255 - GetRValue(crText11)), 
		(255 - GetGValue(crText11)), 
		(255 - GetBValue(crText11))));
	m_stcColor12.SetBkColor(crText11 == 0 ? 1 : crText11);

	m_stcColorA.SetWindowText("접수/대기/예약상태 출발지/도착지 글자색");
	m_cpTextColorA.SetColor(crTextA);
	m_stcColorA.SetTextColor(crTextA);
	m_stcColorA.SetBkColor(RGB(255, 255, 255));

	char buffer[10];
	m_cmbFont.InitControl(strFontName);
	if(m_cmbFontSize.SelectString(-1, ltoa(nFontSize, buffer, 10)))
	{
		m_cmbFontSize.SetWindowText(ltoa(nFontSize, buffer, 10));
	}

	CString strDisplay = "SAMPLE - 로지소프트 세상을 움직이는 기술";
	m_edtFontText.SetMyFont(strFontName, nFontSize, m_chkBold.GetCheck() ? FW_BOLD : FW_NORMAL);
	m_edtFontText.SetWindowText(strDisplay);
	m_edtFontText.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), strDisplay, FALSE);


	CString strColHeight = AfxGetApp()->GetProfileString("RcpPage", "ColHeight", "15");
	m_chkApplyHeight.SetCheck(AfxGetApp()->GetProfileInt("RcpPage", "ApplyHeight", 0));
	m_cmbApplyCombo.SetWindowText(strColHeight);


	OnBnClickedApplyHeight();
}

void CSetRcpPageDlg::OnBnClickedUseCardOkNumberAddColumnCheck()
{
	if(((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->GetCheck())
	{
		if(!POWER_CHECK(1982, "승인번호컬럼 보기", TRUE))
		{
			((CButton*)GetDlgItem(IDC_USE_CARD_OK_NUMBER_ADD_COLUMN_CHECK))->SetCheck(FALSE);
		}
	}
}

void CSetRcpPageDlg::OnBnClickedInsungColorBtn()
{
	m_cpTextColor1.SetColor(STATE_COLOR_TX1);
	m_cpTextColor2.SetColor(STATE_COLOR_TX2);
	m_cpTextColor3.SetColor(STATE_COLOR_TX3);
	m_cpTextColor4.SetColor(STATE_COLOR_TX4);
	m_cpTextColor5.SetColor(STATE_COLOR_TX5);
	m_cpTextColor6.SetColor(STATE_COLOR_TX6);
	m_cpTextColor7.SetColor(STATE_COLOR_TX7);
	m_cpTextColor8.SetColor(STATE_COLOR_TX8);
	m_cpTextColor9.SetColor(STATE_COLOR_TX9);
	m_cpTextColor10.SetColor(STATE_COLOR_TX10);
	m_cpTextColorA.SetColor(STATE_INSUNG_COLOR_TXA);

	m_cpBackColor1.SetColor(STATE_INSUNG_COLOR_BK1);
	m_cpBackColor2.SetColor(STATE_INSUNG_COLOR_BK2);
	m_cpBackColor3.SetColor(STATE_INSUNG_COLOR_BK3);
	m_cpBackColor4.SetColor(STATE_INSUNG_COLOR_BK4);
	m_cpBackColor5.SetColor(STATE_INSUNG_COLOR_BK5);
	m_cpBackColor6.SetColor(STATE_INSUNG_COLOR_BK6);
	m_cpBackColor7.SetColor(STATE_INSUNG_COLOR_BK7);
	m_cpBackColor8.SetColor(STATE_INSUNG_COLOR_BK8);
	m_cpBackColor9.SetColor(STATE_INSUNG_COLOR_BK9);
	m_cpBackColor10.SetColor(STATE_INSUNG_COLOR_BK10);
	m_cpBackColor12.SetColor(STATE_INSUNG_COLOR_BK12);

	OnSelEndOkTextColor();
	OnSelEndOkBackColor();
}

void CSetRcpPageDlg::OnBnClickedSaveMainColumnBtn()
{
	if(LU->GetRcpView()->SendMessage(WM_SAVE_RCP_LIST, 0, 0))
		MessageBox("회사 설정으로 저장되었습니다", "확인", MB_ICONINFORMATION);
}

void CSetRcpPageDlg::OnBnClickedLoadMainColumnBtn()
{
	if(LU->GetRcpView()->SendMessage(WM_LOAD_RCP_LIST, 0, 0))
		MessageBox("회사 설정을 적용하였습니다", "확인", MB_ICONINFORMATION);
}

void CSetRcpPageDlg::OnBnClickedSaveCtiColumnBtn()
{
	if(LU->GetRcpView()->SendMessage(WM_SAVE_CTI_LIST, 0, 0))
		MessageBox("회사 설정으로 저장되었습니다", "확인", MB_ICONINFORMATION);
}

void CSetRcpPageDlg::OnBnClickedLoadCtiColumnBtn()
{ 
	if(LU->GetRcpView()->SendMessage(WM_LOAD_CTI_LIST, 0, 0)) 
		MessageBox("회사 설정을 적용하였습니다", "확인", MB_ICONINFORMATION);
}
