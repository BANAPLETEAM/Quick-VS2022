// OptionDlgInterCall.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgInterCall2.h"
#include "MainOptionDlg2011.h"
#include "IcBannerPreViewDlg.h"
#include "OptionWorkTimeDlg.h"

// COptionDlgInterCall

IMPLEMENT_DYNCREATE(COptionDlgInterCall2, CMyFormView)

COptionDlgInterCall2::COptionDlgInterCall2()
	: CMyFormView(COptionDlgInterCall2::IDD)
	, m_bICDisplayType(FALSE)
	, m_nChargeOpenType(0)
	, m_bTransOpen(FALSE)
	, m_sICBanner(_T(""))
	, m_sICDisplayName(_T(""))
{
	m_strSlowMsg = "";
	m_strSlowCharge = "";
	m_sSlowMsg = "";
	m_strIntercallName = "";
}

COptionDlgInterCall2::~COptionDlgInterCall2()
{
}
#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d, ID = %d\n", TEXT(__FILE__), TEXT(__LINE__), y);DDX_Control(x, y, z);}
void COptionDlgInterCall2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	// 공통 
	
	DDX_Control(pDX, IDC_RECEIPT_TYPE_COMBO, m_cmbReceiptType);

	DDX_Control(pDX, IDC_ACCOUNT_INFO_EDIT, m_edtAccountInfo);
	DDX_Control(pDX, IDC_ACCOUNT_INFO_OWNER_EDIT, m_edtAccountInfoOwner);

	DDX_Control(pDX, IDC_WEB_INTER_RECEIPT_STOP_CHECK, m_chkReceiptStop);
	DDX_Control(pDX, IDC_WEB_RECEIPT_STOP_EDIT, m_edtReciptStop);
	DDX_Control(pDX, IDC_WEB_INTER_WORK_TIME_BUTTON, m_btnWebInterWorkTime);
		
		

	// 인터콜
	DDX_Control(pDX, IDC_COMPANY_WORKING_CHECK, m_CompanyWorkingCheck);
	DDX_Control(pDX, IDC_SLOW_ORDER_CHECK, m_SlowOrderCheck);
	DDX_Control(pDX, IDC_SLOW_MSG_EDIT, m_SlowMsgEdit);
	DDX_Control(pDX, IDC_SLOW_CHARGE_EDIT, m_SlowChargeEdit);

	DDX_Check(pDX, IDC_COMPANY_WORKING_CHECK, m_bCompanyWorking);
	DDX_Check(pDX, IDC_SLOW_ORDER_CHECK, m_bUseSlowOrder);
	DDX_Text(pDX, IDC_SLOW_MSG_EDIT, m_strSlowMsg);
	DDX_Text(pDX, IDC_SLOW_CHARGE_EDIT, m_strSlowCharge);
	DDX_Control(pDX, IDC_IC_DISPLAY_TYPE_CHK, m_chkICDisplayType);
	DDX_Check(pDX, IDC_IC_DISPLAY_TYPE_CHK, m_bICDisplayType);
	DDX_Control(pDX, IDC_TRANS_OPEN_CHECK, m_chkTransOpen);
	DDX_Control(pDX, IDC_CHARGE_OPEN_TYPE_COMBO, m_cmbChargeOpenType);
	DDX_CBIndex(pDX, IDC_CHARGE_OPEN_TYPE_COMBO, m_nChargeOpenType);
	DDX_Check(pDX, IDC_TRANS_OPEN_CHECK, m_bTransOpen);
	DDX_Text(pDX, IDC_IC_BANNER_EDIT, m_sICBanner);
	DDX_Text(pDX, IDC_IC_DISPLAY_NAME_EDT, m_sICDisplayName);
	DDX_Control(pDX, IDC_INTERCALL_NAME_EDIT, m_edtIntercallName);
	DDX_Text(pDX, IDC_INTERCALL_NAME_EDIT, m_strIntercallName);
	DDX_Control(pDX, IDC_ETC_COPY_CHECK, m_chkEtcInterCallCopy);	
	DDX_Control(pDX, IDC_RIDER_PHONE_VIEW_CHECK, m_chkInterCallRiderPhoneView);  // 할인/추가 표시여부
	DDX_Control(pDX, IDC_INTERCALL_NOT_VIEW_AMONT_COMBO, m_cmbIntercallNotViewAmount);  // 할인/추가 표시여부
	DDX_Control(pDX, IDC_INTERCALL_RECEIPT_STATE_COMBO, m_cmbInterCallReceiptState);													 

		// 웹
	DDX_Control(pDX, IDC_MILEAGE_USE_CHECK, m_chkMileage);
	DDX_Control(pDX, IDC_CARDPAYMENT_CHECK, m_chkPayMent);

	DDX_Control(pDX, IDC_INTERNET_CARD_NOT_USE, m_chkInternetCardNotUse);
	DDX_Control(pDX, IDC_SETTLEMENT_TAX_CHECK, m_chkSettleMentTax);
	

	DDX_Control(pDX, IDC_WAY_USE_CHECK, m_chkWayUse);
	DDX_Control(pDX, IDC_WAYADD_AMOUNT_EDIT, m_edtWayAddAmount);
	DDX_Control(pDX, IDC_RUN_USE_CHECK, m_chkRunUse);
	DDX_Control(pDX, IDC_RUNADD_AMOUNT_EDIT, m_edtRunAddAmount);
	DDX_Control(pDX, IDC_WEBCHARGE_TYPE_COMBO, m_cmbWebChargeType);
	DDX_Control(pDX, IDC_CHARGELIST_USE_CHECK, m_chkChargeListUse);
	DDX_Control(pDX, IDC_COUPHON_USE_CHECK2, m_chkCouphonUse);
	DDX_Control(pDX, IDC_BBS_USE_CHECK, m_chkBBSUse);

	DDX_Control(pDX, IDC_ONLINEPAY_CHECK, m_chkOnLinePayUse);
	DDX_Control(pDX, IDC_WEBADDRESS_EDIT, m_edtWebAddress);
	DDX_Control(pDX, IDC_INNERFRAMEUSE_CHECK, m_chkInnerFrameUse);
	DDX_Control(pDX, IDC_BGCOLOR_EDIT, m_edtBgColor);
	DDX_Control(pDX, IDC_FONTCOLOR_EDIT, m_edtFontColor);
	DDX_Control(pDX, IDC_BGCOLOR_BTN, m_btnBgColor);
	DDX_Control(pDX, IDC_FONTCOLOR_BTN, m_btnFontColor);

	DDX_Control(pDX, IDC_NIGHTRECEIPT_CALL_SMS_EDIT, m_edtNightReceiptCallSMS);
	DDX_Control(pDX, IDC_WEB_RECEIPT_STATE_COMBO, m_cmbWebReceiptState);
}

BEGIN_MESSAGE_MAP(COptionDlgInterCall2, CMyFormView)
	// 웹
	ON_BN_CLICKED(IDC_SLOW_ORDER_CHECK, OnBnClickedSlowOrderCheck)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_IC_DISPLAY_TYPE_CHK, OnBnClickedIcDisplayTypeChk)
	ON_CBN_SELCHANGE(IDC_CHARGE_OPEN_TYPE_COMBO, &COptionDlgInterCall2::OnCbnSelchangeChargeOpenTypeCombo)
	ON_BN_CLICKED(IDC_PRE_VIEW_BTN, &COptionDlgInterCall2::OnBnClickedPreViewBtn)
	
	// 인터콜
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CANCEL_BTN3, OnBnCancelBTN)
	ON_BN_CLICKED(IDC_WEB_INTER_WORK_TIME_BUTTON, OnBnClickedWebInterWorkTime)
	ON_BN_CLICKED(IDC_ONLINEPAY_CHECK, OnBnClickedOnlinepayCheck)
	ON_BN_CLICKED(IDC_INNERFRAMEUSE_CHECK, OnBnClickedInnerframeuseCheck)
	ON_BN_CLICKED(IDC_BGCOLOR_BTN, OnBnClickedBgcolorBtn)
	ON_BN_CLICKED(IDC_FONTCOLOR_BTN, OnBnClickedFontcolorBtn)
	ON_BN_CLICKED(IDC_INTERNET_CARD_NOT_USE, &COptionDlgInterCall2::OnBnClickedInternetCardNotUse)
	ON_NOTIFY(NM_THEMECHANGED, IDC_BGCOLOR_BTN, &COptionDlgInterCall2::OnNMThemeChangedBgcolorBtn)
	ON_BN_CLICKED(IDC_WEB_BTN, &COptionDlgInterCall2::OnBnClickedWebBtn)
	ON_BN_CLICKED(IDC_INTERCALL_BTN, &COptionDlgInterCall2::OnBnClickedIntercallBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgInterCall2 진단입니다.

#ifdef _DEBUG
void COptionDlgInterCall2::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgInterCall2::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgInterCall2 메시지 처리기입니다.

void COptionDlgInterCall2::OnBnClickedSlowOrderCheck()
{
	if(m_SlowOrderCheck.GetCheck() == 1)
	{	
		m_SlowMsgEdit.SetReadOnly(FALSE);
		m_SlowChargeEdit.SetReadOnly(FALSE);
	}
	else {
		m_SlowMsgEdit.SetReadOnly(TRUE);
		m_SlowChargeEdit.SetReadOnly(TRUE);
	}
}

void COptionDlgInterCall2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);

	if(m_ui.strLogiStaffName.GetLength() > 0)
		m_edtIntercallName.EnableWindow(TRUE);

	if(!POWER_CHECK(1307, "Intercall"))
		EnableWindow(FALSE);

	UpdateData();
	CString sBgColor, sFontColor;
	m_edtBgColor.GetWindowText(sBgColor);
	m_edtFontColor.GetWindowText(sFontColor);
	int R, G, B;
	if(sBgColor.GetLength() > 0)
	{
		sBgColor.Replace("#", "");
		B = atoi(sBgColor.Left(2));
		G = atoi(sBgColor.Mid(2,2));
		R = atoi(sBgColor.Right(2));

		m_btnBgColor.SetColor(RGB(R,G,B));

	}

	if(sFontColor.GetLength() > 0)
	{
		sFontColor.Replace("#", "");
		B = atoi(sFontColor.Left(2));
		G = atoi(sFontColor.Mid(2,2));
		R = atoi(sFontColor.Right(2));

		m_btnBgColor.SetColor(RGB(R,G,B));
	}

	m_cmbChargeOpenType.SetCurSel(0);
	m_cmbWebReceiptState.SetCurSel(0);
	m_cmbInterCallReceiptState.SetCurSel(0);

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 
	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;  
	sizeTotal.cy = 600;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
}

int COptionDlgInterCall2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COptionDlgInterCall2::OnBnClickedIcDisplayTypeChk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgInterCall2::OnCbnSelchangeChargeOpenTypeCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgInterCall2::OnBnClickedPreViewBtn()
{
	UpdateData(TRUE);

	CIcBannerPreViewDlg dlg;
	dlg.m_sBanner = m_sICBanner;
	dlg.DoModal();
}



BOOL COptionDlgInterCall2::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);


	BOOL bICDisplayMapCheck = m_chkICDisplayType.GetCheck();
	CString sWayAmount,sRunAmount,sNightReceiptCallSMS = "", sAccountInfo = "", sAccountInfoOwner = ""; 
	CString strWebInterReceiptStop = ""; CStringW strWebInterReceiptStop_W(L"");
	long nWayAddAmount = 0, nRunAddAmount = 0;

	m_edtWayAddAmount.GetWindowText(sWayAmount);
	m_edtRunAddAmount.GetWindowText(sRunAmount);
	m_edtAccountInfo.GetWindowText(sAccountInfo);
	m_edtAccountInfoOwner.GetWindowText(sAccountInfoOwner);
	m_edtReciptStop.GetWindowText(strWebInterReceiptStop);

	strWebInterReceiptStop_W = (CStringW)strWebInterReceiptStop;

	if(strWebInterReceiptStop_W.GetLength() > 50 && m_chkReceiptStop.GetCheck())
	{
		MsgBox("인터콜(웹) 의 사유가 50자 이상됩니다.");
		return FALSE;
	}
	if(strWebInterReceiptStop.GetLength() <= 0 &&  m_chkReceiptStop.GetCheck())
	{
		MsgBox("인터콜(웹) 의 사유를 입력하여 주세요");
		m_edtReciptStop.SetFocus();
		return FALSE;
	}



	if(IsStringDigit(sWayAmount))
		nWayAddAmount = atol(sWayAmount);
	else
	{
		MsgBox("편도,왕복에 금액을 입력하세요");
		return FALSE;
	}
	if(IsStringDigit(sRunAmount))
		nRunAddAmount = atol(sRunAmount);
	else
	{
		MsgBox("편도,왕복에 금액을 입력하세요");
		return FALSE;
	}

	

	OnBnClickedBgcolorBtn();
	OnBnClickedFontcolorBtn();
	CString sWebAddress, sFrameBgColor, sFrameFontColor;
	m_edtFontColor.GetWindowText(sFrameFontColor);
	m_edtBgColor.GetWindowText(sFrameBgColor);
	m_edtWebAddress.GetWindowText(sWebAddress);
	
	m_edtNightReceiptCallSMS.GetWindowText(sNightReceiptCallSMS);
	if(m_chkInnerFrameUse.GetCheck()&&	(sFrameBgColor.GetLength() == 0 )) //|| sFrameFontColor.GetLength() == 0)		)
	{
		MsgBox("프레임 폰트및 백그라운드 컬러값을 입력하세요");
		return FALSE;
	}	

	COLORREF Bgcolor = m_btnBgColor.GetColor();
	COLORREF Fontcolor = m_btnFontColor.GetColor();

	BYTE R = GetRValue(Bgcolor);	BYTE G = GetGValue(Bgcolor);	BYTE B = GetBValue(Bgcolor);
	sFrameBgColor.Format("%02x%02x%02x", R,G,B);	

	R = GetRValue(Fontcolor);	G = GetGValue(Fontcolor);	B = GetBValue(Fontcolor);
	sFrameFontColor.Format("%02x%02x%02x", R,G,B);

	CString sSlowCharge = m_strSlowCharge; sSlowCharge.Replace(",", "");
	long nSlowCharge = atol(sSlowCharge);
	long nReceiptType; 
	CString sReceiptType;


	m_cmbReceiptType.GetWindowText(sReceiptType);
	nReceiptType = (sReceiptType.Compare("사용자정의") == 0) ? 100 : m_cmbReceiptType.GetCurSel();

	
	
	
	CMkCommand pCmd(m_pMkDb, "update_option_2011_intercall11");	//   
	// 인터콜
	pCmd.AddParameter(bAll);	
	pCmd.AddParameter(nCompany);	
	pCmd.AddParameter(m_chkReceiptStop.GetCheck());	
	pCmd.AddParameter(strWebInterReceiptStop);	

	pCmd.AddParameter(m_bCompanyWorking);
	pCmd.AddParameter(m_bTransOpen); 
	pCmd.AddParameter(bICDisplayMapCheck); 
	pCmd.AddParameter(m_bUseSlowOrder);
	pCmd.AddParameter(m_strSlowMsg);
	pCmd.AddParameter(nSlowCharge);
	pCmd.AddParameter(m_nChargeOpenType); 	
	pCmd.AddParameter(m_sICBanner);
	pCmd.AddParameter(m_sICDisplayName);
	pCmd.AddParameter(m_strIntercallName);
	pCmd.AddParameter(m_chkEtcInterCallCopy.GetCheck());
	
					  
	pCmd.AddParameter(m_chkInterCallRiderPhoneView.GetCheck());
	pCmd.AddParameter(m_cmbIntercallNotViewAmount.GetCurSel());

	// 웹 WWW	
	pCmd.AddParameter(m_chkMileage.GetCheck()); 
	pCmd.AddParameter(m_chkChargeListUse.GetCheck()); 
	pCmd.AddParameter(m_chkCouphonUse.GetCheck()); 	
	pCmd.AddParameter(m_chkPayMent.GetCheck());
	pCmd.AddParameter(m_chkOnLinePayUse.GetCheck());
	pCmd.AddParameter(m_chkInternetCardNotUse.GetCheck());

	pCmd.AddParameter(sWebAddress); 	
	pCmd.AddParameter(m_chkBBSUse.GetCheck()); 
	pCmd.AddParameter(m_chkInnerFrameUse.GetCheck()); 
	pCmd.AddParameter(sFrameBgColor);
	pCmd.AddParameter(sFrameFontColor);
	pCmd.AddParameter(m_chkSettleMentTax.GetCheck()); 
	pCmd.AddParameter(sNightReceiptCallSMS); 
	pCmd.AddParameter(m_cmbWebReceiptState.GetCurSel()); 
	pCmd.AddParameter(m_cmbInterCallReceiptState.GetCurSel()); 
	pCmd.AddParameter(m_ui.strID); 	
		

	//공통
	pCmd.AddParameter(nReceiptType);	
	pCmd.AddParameter(sAccountInfo);	
	pCmd.AddParameter(sAccountInfoOwner);	

	

	
	/*
	pCmd.AddParameter(m_chkWayUse.GetCheck()); 
	pCmd.AddParameter(nWayAddAmount); 	
	
	pCmd.AddParameter(m_cmbWebChargeType.GetCurSel() < 0 ? 0 :
				  m_cmbWebChargeType.GetCurSel() ); 
  pCmd.AddParameter(m_chkRunUse.GetCheck()); 
  pCmd.AddParameter(nRunAddAmount); 
				  */
	return pCmd.Execute();
}

void COptionDlgInterCall2::OnBnCancelBTN()
{
	OnClose();
}
void COptionDlgInterCall2::OnBnClickedWebInterWorkTime()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode();

	if(nCompany <= 0)
	{
		MessageBox("지사를 선택하시기 바랍니다.","지사 선택",MB_ICONINFORMATION);
		return;
	}

	COptionWorkTimeDlg dlg;
	dlg.m_nCompany = nCompany;
	dlg.DoModal();
}
void COptionDlgInterCall2::OnBnClickedOnlinepayCheck()
{

	m_chkPayMent.EnableWindow(m_chkOnLinePayUse.GetCheck());
	m_chkSettleMentTax.EnableWindow(m_chkOnLinePayUse.GetCheck());
	m_chkInternetCardNotUse.EnableWindow(m_chkOnLinePayUse.GetCheck());

	if(!m_chkOnLinePayUse.GetCheck() )
	{
		m_chkPayMent.SetCheck(m_chkOnLinePayUse.GetCheck());
		m_chkSettleMentTax.SetCheck(m_chkOnLinePayUse.GetCheck());
		m_chkInternetCardNotUse.SetCheck(m_chkOnLinePayUse.GetCheck());
	}
	

}

void COptionDlgInterCall2::OnBnClickedInnerframeuseCheck()
{
	m_edtFontColor.EnableWindow(m_chkInnerFrameUse.GetCheck());
	m_edtBgColor.EnableWindow(m_chkInnerFrameUse.GetCheck());
	m_btnBgColor.EnableWindow(m_chkInnerFrameUse.GetCheck());
	m_btnFontColor.EnableWindow(m_chkInnerFrameUse.GetCheck());

}


void COptionDlgInterCall2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	//if(nSBCode == SB_ENDSCROLL)
	//	Invalidate(TRUE);
}

BOOL COptionDlgInterCall2::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);
	//if(nFlags == SB_ENDSCROLL)
	//Invalidate(TRUE);

	return TRUE;
}


void COptionDlgInterCall2::OnSize(UINT nType, int cx, int cy)
{
	return; 
	CMyFormView::OnSize(nType, cx, cy); 

}
void COptionDlgInterCall2::OnBnClickedBgcolorBtn()
{


	COLORREF Bgcolor = m_btnBgColor.GetColor();

	CString sFrameBgColor;
	

	BYTE R = GetRValue(Bgcolor);
	BYTE G = GetGValue(Bgcolor);
	BYTE B = GetBValue(Bgcolor);

	sFrameBgColor.Format("%02x%02x%02x", R,G,B);


	m_edtBgColor.SetWindowText(sFrameBgColor);
}

void COptionDlgInterCall2::OnBnClickedFontcolorBtn()
{
	COLORREF Fontcolor = m_btnFontColor.GetColor();
	CString sFrameFontColor;
	BYTE R = GetRValue(Fontcolor);
	BYTE G = GetGValue(Fontcolor);
	BYTE B = GetBValue(Fontcolor);
	sFrameFontColor.Format("%02x%02x%02x", R,G,B);

	m_edtFontColor.SetWindowText(sFrameFontColor);

}
void COptionDlgInterCall2::OnNMThemeChangedBgcolorBtn(NMHDR *pNMHDR, LRESULT *pResult)
{
	COLORREF Fontcolor = m_btnFontColor.GetColor();
	CString sFrameFontColor;
	BYTE R = GetRValue(Fontcolor);
	BYTE G = GetGValue(Fontcolor);
	BYTE B = GetBValue(Fontcolor);
	sFrameFontColor.Format("%02x%02x%0x", B,G,R);

	m_edtFontColor.SetWindowText(sFrameFontColor);
	*pResult = 0;
}


void COptionDlgInterCall2::OnBnClickedInternetCardNotUse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COptionDlgInterCall2::OnBnClickedWebBtn()
{
	CString strWebAddress = "";
	m_edtWebAddress.GetWindowText(strWebAddress);
	if(strWebAddress.GetLength() <= 6)
		return;

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())

	strForm = " http://" +strWebAddress;
	str += strForm;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	


	}
}

void COptionDlgInterCall2::OnBnClickedIntercallBtn()
{
	CString strWebAddress = "";
	m_edtIntercallName.GetWindowText(strWebAddress);
	if(strWebAddress.GetLength() <= 6)
		return;

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())

	strForm =" http://www.logisoft.co.kr/intercall/" +strWebAddress;

	str += strForm;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	


	}
}

void COptionDlgInterCall2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}
