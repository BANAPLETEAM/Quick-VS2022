// OptionDlgMobileNew.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgMobileNew.h"
#include "MainOptionDlg2011.h"
#include "MainFrm.h"
#include "PenaltySetDlg.h"
#include "OptionDlgGeneral2.h"  
// COptionDlgMobileNew
 
IMPLEMENT_DYNCREATE(COptionDlgMobileNew, CMyFormView)

COptionDlgMobileNew::COptionDlgMobileNew() 
	: CMyFormView(COptionDlgMobileNew::IDD)
,m_dtFromDestView(COleDateTime::GetCurrentTime())	
, m_bAutoWaitOnce(FALSE)
{
	m_bDestDisplay = FALSE;
	m_sDestViewTime = "";
}

COptionDlgMobileNew::~COptionDlgMobileNew()
{
}

void COptionDlgMobileNew::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	// 모바일1
	DDX_Check(pDX, IDC_DEST_DISPLAY_CHECK, m_bDestDisplay);

	DDX_Control(pDX, IDC_SORT_TYPE_COMBO, m_SortTypeCombo);
	DDX_Control(pDX, IDC_DEST_VIEW_TIME_CHECK, m_chkDestViewTime);
	DDX_Check(pDX, IDC_DEST_VIEW_TIME_CHECK, m_bDestViewTime);
	DDX_Control(pDX, IDC_FROM_DEST_VIEW_DTP, m_dtpFromDestView);
	DDX_DateTimeCtrl(pDX, IDC_FROM_DEST_VIEW_DTP, m_dtFromDestView);
	DDX_Check(pDX, IDC_HIDE_CLIENT_MULTIPLE_CHECK, m_bHideClientMultiple);
	DDX_Control(pDX, IDC_HIDE_CLIENT_MULTIPLE_CHECK, m_HideClientMultipleCheck);
	DDX_Control(pDX, IDC_HIDE_CLIENT_SECTION_CHECK, m_HideClientSectionCheck);
	DDX_Check(pDX, IDC_HIDE_CLIENT_SECTION_CHECK, m_bHideClientSection);
	DDX_Control(pDX, IDC_REGION_COUNT_COMBO, m_RegionCountCombo);
	DDX_Check(pDX, IDC_ENABLE_CANCEL_CHECK, m_bEnableCancel);
	DDX_Control(pDX, IDC_ENABLE_CANCEL_CHECK, m_EnableCancelCheck);
	DDX_Check(pDX, IDC_INSURE_LIMIT_CHECK, m_bInsureLimit);
	DDX_Control(pDX, IDC_INSURE_LIMIT_CHECK, m_InsureLimitCheck);
	DDX_Check(pDX, IDC_CHARGE_LIMIT_CHECK, m_bChargeLimit);
	DDX_Control(pDX, IDC_CHARGE_LIMIT_CHECK, m_ChargeLimitCheck);
	DDX_Text(pDX, IDC_MAX_CHARGE_EDIT, m_strMaxCharge);
	DDX_Control(pDX, IDC_MAX_CHARGE_EDIT, m_MaxChargeEdit);
	DDX_Check(pDX, IDC_NOT_COMPLETED_LIMIT_CHECK, m_bNotCompletedLimit);
	DDX_Control(pDX, IDC_NOT_COMPLETED_LIMIT_CHECK, m_NotCompletedLimitCheck);	
	DDX_Text(pDX, IDC_MIN_COMPLETE_TIME_EDIT, m_strMinCompleteTime);
	DDX_Control(pDX, IDC_MIN_COMPLETE_TIME_EDIT, m_MinCompleteTimeEdit);
	DDX_Control(pDX, IDC_WAP_DISABLE_CHECK, m_WapDisableCheck);
	DDX_Check(pDX, IDC_WAP_DISABLE_CHECK, m_bWapDisable);
	DDX_Control(pDX, IDC_WORK_REPORT_CHECK, m_WorkReportCheck);
	DDX_Check(pDX, IDC_WORK_REPORT_CHECK, m_bWorkReport);
	DDX_Control(pDX, IDC_WORK_REPORT_CHARGE_EDIT, m_WorkReportChargeEdit);
	DDX_Text(pDX, IDC_WORK_REPORT_CHARGE_EDIT, m_strWorkReportCharge);
	DDX_Control(pDX, IDC_CANCEL_PENALTY_BTN, m_CancelPenaltyBtn);
	DDX_Control(pDX, IDC_DEST_DISPLAY_CHECK, m_DestDisplayCheck);


	// 모바일2
	DDX_Control(pDX, IDC_SUPORTABLE_CALL, m_SupportableCallCheck);
	DDX_Check(pDX, IDC_SUPORTABLE_CALL, m_bSupportableCall);
	DDX_Control(pDX, IDC_USEPICKUP_CALL, m_UsePickupCallCheck);
	DDX_Check(pDX, IDC_USEPICKUP_CALL, m_bUsePickupCall);
	DDX_Control(pDX, IDC_ALLOCATE_COMBO, m_cmbAllocateMethod);
	DDX_Control(pDX, IDC_ALLOCATE_LIMITE_TIME_EDIT, m_edtAllocateLimitTime);
	DDX_Text(pDX, IDC_ALLOCATE_LIMITE_TIME_EDIT, m_strAllocateLimitTime);
	DDX_Check(pDX, ID_CUSTPHONE_HIDE, m_bCustPhoneHide);
	DDX_Control(pDX, ID_CUSTPHONE_HIDE, m_CustPhoneHide);
	DDX_Control(pDX, IDC_CLASSBYUSECOUNT_EDIT, m_edtClassViewByUseCount);
	DDX_Text(pDX, IDC_CLASSBYUSECOUNT_EDIT, m_sClassViewByUseCount);
	DDX_Control(pDX, IDC_USE_NEWREGION, m_chkUseNewRegion);
	DDX_Check(pDX, IDC_USE_NEWREGION, m_bUseNewRegion);
	DDX_Control(pDX, IDC_MAX_DISTANCE, m_editMaxDistance);
	DDX_Text(pDX, IDC_MAX_DISTANCE, m_strMaxDistance);	
	DDX_Control(pDX, IDC_MAX_NEARORDER, m_editMaxNearOrder);
	DDX_Text(pDX, IDC_MAX_NEARORDER, m_strMaxNearOrder);
	DDX_Control(pDX, IDC_NOT_ALL_ORDERVIEW, m_chkNotAllView);
	DDX_Check(pDX, IDC_NOT_ALL_ORDERVIEW, m_bNotAllOrderView);
	DDX_Control(pDX, IDC_DISTANCE_ALLOCATE, m_edtDistanceAllocate);
	DDX_Text(pDX, IDC_DISTANCE_ALLOCATE, m_nDistanceAllocate);
	DDX_Control(pDX, IDC_USE_NEWREGION_ALL_DONG, m_chkUseNewRegionAllDong);
	DDX_Check(pDX, IDC_USE_NEWREGION_ALL_DONG, m_bUseNewRegionAllDong);
	DDX_Control(pDX, IDC_NATIONAL_CALLCENTER, m_chkNationalCallcenter);
	DDX_Check(pDX, IDC_NATIONAL_CALLCENTER, m_bNationalCallcenter);

	// 모바일3
	DDX_Control(pDX, IDC_SYMBOL_EDIT, m_editSymbol);
	DDX_Text(pDX, IDC_SYMBOL_EDIT, m_strSymbol);
	DDX_Control(pDX, IDC_SYMBOL_DISPLAY_TYPE_COMBO, m_comboSymbolDisplay);
	DDX_CBString(pDX, IDC_SYMBOL_DISPLAY_TYPE_COMBO, m_strSymbolDisplay);	
	DDX_Control(pDX, IDC_CHARGE_MIN_EDIT, m_editChargeMin);
	DDX_Text(pDX, IDC_CHARGE_MIN_EDIT, m_strChargeMin);
	DDX_Control(pDX, IDC_CHARGE_MAX_EDIT, m_editChargeMax);
	DDX_Text(pDX, IDC_CHARGE_MAX_EDIT, m_strChargeMax);
	DDX_Control(pDX, IDC_PREVENT_SHOW_ONLY_MY_COMAPNY, m_chkPreventShowOnlyMyCompanyOrder);
	DDX_Check(pDX, IDC_PREVENT_SHOW_ONLY_MY_COMAPNY, m_bPreventShowOnlyMyCompanyOrder);
	DDX_Control(pDX, IDC_IGNORE_RIDER_KM, m_chkIgnoreRiderKM);
	DDX_Check(pDX, IDC_IGNORE_RIDER_KM, m_bIgnoreRiderKM);
	DDX_Control(pDX, IDC_NEED_SIGN_FOR_COMPLETE_CHECK, m_chkNeedSignForComplete);
	DDX_Check(pDX, IDC_NEED_SIGN_FOR_COMPLETE_CHECK, m_bNeedSignForComplete);

	DDX_Control(pDX, IDC_IGNORE_RIDER_PERMIT_CAR_TYPE_CHECK, m_chkIgnoreRiderPermitCarType);
	DDX_Check(pDX, IDC_IGNORE_RIDER_PERMIT_CAR_TYPE_CHECK, m_bIgnoreRiderPermitCarType);
	DDX_Control(pDX, IDC_IGNORE_RIDER_CHARGE_CHECK, m_chkIgnoreRiderCharge);
	DDX_Check(pDX, IDC_IGNORE_RIDER_CHARGE_CHECK, m_bIgnoreRiderCharge);
	DDX_Control(pDX, IDC_IGNORE_RIDER_START_CHECK, m_chkIgnoreRiderStart);
	DDX_Check(pDX, IDC_IGNORE_RIDER_START_CHECK, m_bIgnoreRiderStart);
	DDX_Control(pDX, IDC_IGNORE_RIDER_DEST_CHECK, m_chkIgnoreRiderDest);
	DDX_Check(pDX, IDC_IGNORE_RIDER_DEST_CHECK, m_bIgnoreRiderDest);

	DDX_Control(pDX, IDC_AUTO_RANGE_COMBO, m_cmbAutoRange);
	DDX_Control(pDX, IDC_AUTO_RANGE_STATIC, m_stcAutoRange);
	DDX_Control(pDX, IDC_AUTO_WAIT_ONCE_CHECK, m_chkAutoWaitOnce);
	DDX_Check(pDX, IDC_AUTO_WAIT_ONCE_CHECK, m_bAutoWaitOnce);
}

BEGIN_MESSAGE_MAP(COptionDlgMobileNew, CMyFormView)
	// 모바일1
	ON_WM_MOUSEACTIVATE()
	ON_MESSAGE(WM_REFRESH, OnRefresh )
	ON_BN_CLICKED(IDC_DEST_DISPLAY_CHECK, OnBnClickedDestDisplayCheck)
	ON_BN_CLICKED(IDC_DEST_VIEW_TIME_CHECK, OnBnClickedDestViewTimeCheck)
	ON_BN_CLICKED(IDC_CANCEL_PENALTY_BTN, OnBnClickedCancelPenaltyBtn)
	ON_BN_CLICKED(IDC_CHARGE_LIMIT_CHECK, OnBnClickedChargeLimitCheck)
	ON_BN_CLICKED(IDC_NOT_COMPLETED_LIMIT_CHECK, OnBnClickedNotCompletedLimitCheck)	
	// 모바일2

	ON_CBN_SELCHANGE(IDC_ALLOCATE_COMBO, OnCbnSelchangeAllocateCombo)
	ON_BN_CLICKED(IDC_USE_NEWREGION, OnBnClickedUseNewRegion)
	ON_BN_CLICKED(IDC_NOT_ALL_ORDERVIEW, OnBnClickedNotAllOrderview)
	// 모바일3
	ON_CBN_SELCHANGE(IDC_SYMBOL_DISPLAY_TYPE_COMBO, OnCbnSelchangeSymbolDisplayTypeCombo)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgMobileNew 진단입니다.

#ifdef _DEBUG
void COptionDlgMobileNew::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgMobileNew::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgMobileNew 메시지 처리기입니다.
void COptionDlgMobileNew::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);

	if(!POWER_CHECK(1304, "PDA/핸드폰"))
		EnableWindow(FALSE);

	m_cmbAutoRange.InsertString(0, "미적용"); m_cmbAutoRange.SetItemData(0, 0);
	m_cmbAutoRange.InsertString(1, "100m"); m_cmbAutoRange.SetItemData(1, 100);
	m_cmbAutoRange.InsertString(2, "200m"); m_cmbAutoRange.SetItemData(2, 200);
	m_cmbAutoRange.InsertString(3, "300m"); m_cmbAutoRange.SetItemData(3, 300);
	m_cmbAutoRange.InsertString(4, "400m"); m_cmbAutoRange.SetItemData(4, 400);
	m_cmbAutoRange.InsertString(5, "500m"); m_cmbAutoRange.SetItemData(5, 500);
	m_cmbAutoRange.InsertString(6, "600m"); m_cmbAutoRange.SetItemData(6, 600);
	m_cmbAutoRange.InsertString(7, "700m"); m_cmbAutoRange.SetItemData(7, 700);
	m_cmbAutoRange.InsertString(8, "800m"); m_cmbAutoRange.SetItemData(8, 800);
	m_cmbAutoRange.InsertString(9, "900m"); m_cmbAutoRange.SetItemData(9, 900);
	m_cmbAutoRange.InsertString(10, "1.0Km"); m_cmbAutoRange.SetItemData(10, 1000);
	m_cmbAutoRange.InsertString(11, "1.1Km"); m_cmbAutoRange.SetItemData(11, 1100);
	m_cmbAutoRange.InsertString(12, "1.2Km"); m_cmbAutoRange.SetItemData(12, 1200);
	m_cmbAutoRange.InsertString(13, "1.3Km"); m_cmbAutoRange.SetItemData(13, 1300);
	m_cmbAutoRange.InsertString(14, "1.4Km"); m_cmbAutoRange.SetItemData(14, 1400);
	m_cmbAutoRange.InsertString(15, "1.5Km"); m_cmbAutoRange.SetItemData(15, 1500);
	m_cmbAutoRange.InsertString(16, "1.6Km"); m_cmbAutoRange.SetItemData(16, 1600);
	m_cmbAutoRange.InsertString(17, "1.7Km"); m_cmbAutoRange.SetItemData(17, 1700);
	m_cmbAutoRange.InsertString(18, "1.8Km"); m_cmbAutoRange.SetItemData(18, 1800);
	m_cmbAutoRange.InsertString(19, "1.9Km"); m_cmbAutoRange.SetItemData(19, 1900);
	m_cmbAutoRange.InsertString(20, "2.0Km"); m_cmbAutoRange.SetItemData(20, 2000);
	m_cmbAutoRange.InsertString(21, "2.5Km"); m_cmbAutoRange.SetItemData(21, 2500);
	m_cmbAutoRange.InsertString(22, "3.0Km"); m_cmbAutoRange.SetItemData(22, 3000);
	m_cmbAutoRange.InsertString(23, "3.5Km"); m_cmbAutoRange.SetItemData(23, 3500);
	m_cmbAutoRange.InsertString(24, "4.0Km"); m_cmbAutoRange.SetItemData(24, 4000);
	m_cmbAutoRange.InsertString(25, "4.5Km"); m_cmbAutoRange.SetItemData(25, 4500);
	m_cmbAutoRange.InsertString(26, "5.0Km"); m_cmbAutoRange.SetItemData(26, 5000);
	m_cmbAutoRange.InsertString(27, "6.0Km"); m_cmbAutoRange.SetItemData(27, 6000);
	m_cmbAutoRange.InsertString(28, "7.0Km"); m_cmbAutoRange.SetItemData(28, 7000);
	m_cmbAutoRange.InsertString(29, "8.0Km"); m_cmbAutoRange.SetItemData(29, 8000);
	m_cmbAutoRange.InsertString(30, "9.0Km"); m_cmbAutoRange.SetItemData(30, 9000);
	m_cmbAutoRange.InsertString(31, "10.0Km"); m_cmbAutoRange.SetItemData(31, 10000);

	if(!::IsThisCompany("엔콜") && !::IsThisCompany("로지") && 
		!::IsThisCompany("예스콜") && !::IsThisCompany("대구연합"))
	{
		m_cmbAutoRange.ShowWindow(FALSE);
		m_stcAutoRange.ShowWindow(FALSE);
	}

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 
	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;  
	sizeTotal.cy = 700;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void COptionDlgMobileNew::SetAutoRangeCombo(long nRange)
{
	long nCount = m_cmbAutoRange.GetCount();

	for(int i=0; i<nCount; i++)
	{
		long nItem = m_cmbAutoRange.GetItemData(i);

		if(nItem == nRange)
		{
			m_cmbAutoRange.SetCurSel(i);
			break;
		}
	}
}

long COptionDlgMobileNew::GetAutoRangeCombo()
{
	long nIndex = m_cmbAutoRange.GetCurSel();

	if(nIndex < 0)
		return 0;

	return m_cmbAutoRange.GetItemData(nIndex);
}

void COptionDlgMobileNew::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL COptionDlgMobileNew::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);
	g_bana_log->Print("%ld, nFlags  zDelta = %d", nFlags, int(zDelta));
	return TRUE;
}


void COptionDlgMobileNew::OnSize(UINT nType, int cx, int cy)
{
	return; 
	CMyFormView::OnSize(nType, cx, cy); 

}

BOOL COptionDlgMobileNew::Save(long nCompany, BOOL bAll)
{
	UpdateData();
	if(m_bDestDisplay)
	{
		if(m_bDestViewTime)
		{
			m_dtFromDestView.GetHour();
			m_dtFromDestView.GetMinute();		
			m_sDestViewTime.Format("%02d:%02d",	m_dtFromDestView.GetHour(),	m_dtFromDestView.GetMinute());	
		}
		else
			m_sDestViewTime = "";
	}
	else
		m_sDestViewTime = "";

	if(m_bNotAllOrderView && atol(m_strMaxDistance) < m_nDistanceAllocate )
	{
		MessageBox("PDA에 보이는 콜거리보다 배차제한하는 거리가 더큽니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	BOOL bAllocateMethod = FALSE;
	BOOL bTwoStateAlloc = FALSE;
	if(m_cmbAllocateMethod.GetCurSel() < 0){
		MessageBox("1,2, 즉시 배차방식을 선택해주세요","확인",MB_ICONINFORMATION);
		return FALSE;
	}
	else if(m_cmbAllocateMethod.GetCurSel() > 1)
	{
		bAllocateMethod = TRUE;
		bTwoStateAlloc = FALSE;
		if(atoi(m_strAllocateLimitTime) < 0 && atoi(m_strAllocateLimitTime) > 60)
		{
			MessageBox("60초이상은 세팅하실수 없습니다.","확인",MB_ICONINFORMATION);
			return FALSE;
		}
	}
	else if(m_cmbAllocateMethod.GetCurSel() == 1)
	{
		bAllocateMethod = FALSE;
		bTwoStateAlloc = TRUE;
	}
	else if(m_cmbAllocateMethod.GetCurSel() == 0)
	{
		bAllocateMethod = FALSE;
		bTwoStateAlloc = FALSE;
	}
	if(!IsStringDigit(m_sClassViewByUseCount))
	{
		MessageBox("고객 이용횟수에 숫자를 입력하세요","확인",MB_ICONINFORMATION);
		m_edtClassViewByUseCount.SetFocus();
		return FALSE;
	}
		

	//	pCmd.AddParameter( pOptionDlgGeneral->m_bUseDailyPay);

	m_strSymbol.Trim();
	int nSymbolDisplayType = m_comboSymbolDisplay.GetCurSel();
	if(nSymbolDisplayType < 0) nSymbolDisplayType = 3;
	int nChargeDisplayMin  = atoi(m_strChargeMin); 	
	int nChargeDisplayMax  = atoi(m_strChargeMax);
	
	CMkCommand pCmd(m_pMkDb, "update_option_2011_pda_4");	//   
	pCmd.AddParameter( bAll);
	pCmd.AddParameter( nCompany);

	pCmd.AddParameter( m_ci.m_bCheckMidWord);
	pCmd.AddParameter( FALSE);
	pCmd.AddParameter( m_bDestDisplay);

	pCmd.AddParameter( m_SortTypeCombo.GetCurSel());
	pCmd.AddParameter( m_sDestViewTime);
	pCmd.AddParameter( m_bHideClientMultiple);
	pCmd.AddParameter( m_bHideClientSection);
	
	pCmd.AddParameter(  m_RegionCountCombo.GetCurSel() + 1);
	pCmd.AddParameter( m_bEnableCancel);
	pCmd.AddParameter( m_bInsureLimit);
	pCmd.AddParameter( m_bChargeLimit);
	pCmd.AddParameter( atol(m_strMaxCharge));
	pCmd.AddParameter( m_bNotCompletedLimit);
	pCmd.AddParameter( atol(m_strMinCompleteTime));
	pCmd.AddParameter( m_bWapDisable);
	pCmd.AddParameter(  m_bWorkReport);
	pCmd.AddParameter( atol(m_strWorkReportCharge));	
	pCmd.AddParameter( m_bSupportableCall);
	pCmd.AddParameter( m_bUsePickupCall);

	pCmd.AddParameter( bTwoStateAlloc);
	pCmd.AddParameter( bAllocateMethod );
	pCmd.AddParameter( atoi(m_strAllocateLimitTime.GetLength() <= 0 ? "0" :m_strAllocateLimitTime));	
	
	pCmd.AddParameter( m_bCustPhoneHide);
	pCmd.AddParameter( atoi(m_sClassViewByUseCount)); // 사용횟수에 따른 고객표시

	// 동기반 배차방식 이용 파라미터들
	pCmd.AddParameter( m_bUseNewRegion);
	pCmd.AddParameter(  atol(m_strMaxDistance));  //오더보이는 최대거리
	pCmd.AddParameter(  atol(m_strMaxNearOrder));  //가까운거리 오더수량표시
	pCmd.AddParameter( m_bNotAllOrderView);	//전체오더보기제한 및 배차거리제한
	pCmd.AddParameter( m_nDistanceAllocate);  //배차거리제한	
	pCmd.AddParameter( m_bUseNewRegionAllDong);

	pCmd.AddParameter( m_bNationalCallcenter);	
	pCmd.AddParameter(m_strSymbol ); // 클라이언트 심볼 
	pCmd.AddParameter( nSymbolDisplayType); // 클라이언트 심볼 표시 TYPE
	pCmd.AddParameter( nChargeDisplayMin);  // 요금 표시 최저 요금(예 500원이하인경우 표시)
	pCmd.AddParameter( nChargeDisplayMax);  // 요금 표시 최대 요금(예 5000원이상인경우 표시)
	pCmd.AddParameter( m_bPreventShowOnlyMyCompanyOrder);
	pCmd.AddParameter( m_bIgnoreRiderKM);
	pCmd.AddParameter( m_bNeedSignForComplete);

	pCmd.AddParameter( m_bIgnoreRiderPermitCarType);
	pCmd.AddParameter( m_bIgnoreRiderCharge);
	pCmd.AddParameter( m_bIgnoreRiderStart);
	pCmd.AddParameter( m_bIgnoreRiderDest);
	pCmd.AddParameter( GetAutoRangeCombo());
	pCmd.AddParameter(m_bAutoWaitOnce);

	pCmd.AddParameter( m_ui.nCompany);
	pCmd.AddParameter( m_ui.nWNo);
	pCmd.AddParameter( m_ui.strName);

	pCmd.AddParameter(m_ui.strID);
	
	return pCmd.Execute();

}

int COptionDlgMobileNew::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

long COptionDlgMobileNew::OnRefresh(WPARAM wParam,LPARAM lParam)
{

	return 0L;
}

void COptionDlgMobileNew::OnBnClickedDestDisplayCheck()
{
	UpdateData();
	if(m_bDestDisplay)
	{
		m_bDestViewTime = TRUE;
		m_chkDestViewTime.SetCheck(TRUE);
		m_chkDestViewTime.EnableWindow(TRUE);
		m_dtpFromDestView.EnableWindow(TRUE);
	}
	else
	{
		m_bDestViewTime = FALSE;
		m_chkDestViewTime.SetCheck(FALSE);
		m_chkDestViewTime.EnableWindow(FALSE);
		m_dtpFromDestView.EnableWindow(FALSE);		
	}
}

void COptionDlgMobileNew::OnBnClickedDestViewTimeCheck()
{
	UpdateData();
	if(m_bDestViewTime)
		m_dtpFromDestView.EnableWindow(TRUE);	
	else
		m_dtpFromDestView.EnableWindow(FALSE);
		
}

void COptionDlgMobileNew::OnBnClickedCancelPenaltyBtn()
{
	if(!POWER_CHECK(1720, "취소페널티 설정", TRUE))
		return;

	long nCompanyCode = 0;
		//if(m_bIntegrated)
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();


	CBranchInfo *pBi = pDlg->m_cBranch.GetBranchInfo();
	CPenaltySetDlg dlg(pBi->nCompanyCode);
	dlg.m_bIntegrated = pBi->bIntegrated;
	dlg.DoModal();

	/*
	if(m_ba.GetCount() > 1) 
	{
		CBranchInfo *pBi = (CBranchInfo*)pDlg->m_BranchCombo.GetItemData(pDlg->m_BranchCombo.GetCurSel());
		nCompanyCode = pBi->nCompanyCode;
		CPenaltySetDlg dlg(nCompanyCode);
		dlg.m_bIntegrated = pBi->bIntegrated;
		dlg.DoModal();
	}
	else
	{
		nCompanyCode = (long)pDlg->m_BranchCombo.GetItemData(pDlg->m_BranchCombo.GetCurSel());
		CPenaltySetDlg dlg(nCompanyCode);
		dlg.m_bIntegrated = FALSE;
		dlg.DoModal();
	}
	*/	
}

void COptionDlgMobileNew::OnBnClickedChargeLimitCheck()
{
	m_MaxChargeEdit.EnableWindow(m_ChargeLimitCheck.GetCheck());
}


void COptionDlgMobileNew::OnBnClickedNotCompletedLimitCheck()
{
	//m_MinCompleteTimeEdit.EnableWindow(m_NotCompletedLimitCheck.GetCheck());
}



//// 모바일2


void COptionDlgMobileNew::OnBnClickedUseNewRegion()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	COptionDlgGeneral2* pOptionDlgGeneral2 =  (COptionDlgGeneral2*)pDlg->GetTabItem(0);
	ASSERT(NULL != pOptionDlgGeneral2);


	pOptionDlgGeneral2->UpdateData(TRUE);
	//	UpdateData(TRUE);


	if(m_chkUseNewRegion.GetCheck() == 1)
	{
		m_bUseNewRegion = TRUE;
		m_editMaxDistance.EnableWindow(TRUE);
		m_editMaxNearOrder.EnableWindow(TRUE);
		m_chkUseNewRegionAllDong.EnableWindow(TRUE);
		m_chkNotAllView.EnableWindow(TRUE);		
	}
	else
	{
		m_bUseNewRegion = FALSE;
		m_chkNationalCallcenter.SetCheck(FALSE);
		m_editMaxDistance.EnableWindow(FALSE);
		m_editMaxNearOrder.EnableWindow(FALSE);	

		m_chkUseNewRegionAllDong.EnableWindow(FALSE);				
		m_chkNotAllView.EnableWindow(FALSE);
		pOptionDlgGeneral2->m_nDistanceCharge = 0;		
	}
}
void COptionDlgMobileNew::OnBnClickedNotAllOrderview()
{
	if(m_chkUseNewRegion.GetCheck() == 1 && m_chkNotAllView.GetCheck() == 1)
	{
		m_edtDistanceAllocate.EnableWindow(TRUE);
	}
	else
	{
		m_nDistanceAllocate = 0;
		m_edtDistanceAllocate.SetWindowText("0");
		m_edtDistanceAllocate.EnableWindow(FALSE);
	}
}

void COptionDlgMobileNew::OnCbnSelchangeAllocateCombo()
{
	if(m_cmbAllocateMethod.GetCurSel() < 2)
		m_edtAllocateLimitTime.EnableWindow(FALSE);
	else
		m_edtAllocateLimitTime.EnableWindow(TRUE);
}

void COptionDlgMobileNew::OnCbnSelchangeSymbolDisplayTypeCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgMobileNew::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}
