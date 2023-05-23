// OptionDlgCharge.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgCharge.h"
#include "MainOptionDlg2011.h"
//#include "ChargeDistanceDlg.h"
//#include "ChargeDongSetDlg.h"
//#include "MainFrm.h"
#include "OptionWorkTimeDlg.h"
#include "ChargeSectionTypeDlg.h"
#include "SetCountMileageDlg.h"
#include "ChargeDistanceDlg2.h"
#include "UpChargeSetDlg.h"
#include "ChargeSimpleListDlg.h"
// COptionDlgCharge

IMPLEMENT_DYNCREATE(COptionDlgCharge, CMyFormView)

COptionDlgCharge::COptionDlgCharge()
: CMyFormView(COptionDlgCharge::IDD)

, m_nLaboChargeType(0)
{
	
	m_nMileageSpan = 0;
	m_nMileage = 0;

	
	m_nBothCharge = 0;
	m_nDistanceCharge = 0;
	m_strDistanceCharge = "";

}

COptionDlgCharge::~COptionDlgCharge()
{
}

void COptionDlgCharge::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEFAULT_CHARGE_EDIT, m_DefaultChargeEdit);
	DDX_Text(pDX, IDC_DEFAULT_CHARGE_EDIT, m_strDefaultCharge);	

	DDX_Check(pDX, IDC_DISTANCE_CHARGE_CHECK, m_bDistanceChargeCheck);
	DDX_Control(pDX, IDC_DISTANCE_CHARGE_CHECK, m_chkDistanceCharge);
	DDX_Control(pDX, IDC_DISTANCE_CHARGE_COMBO, m_cmbDistanceCharge);
	DDX_Text(pDX, IDC_DISTANCE_CHARGE_COMBO, m_strDistanceCharge);
	DDX_Control(pDX, IDC_MIN_CHARGE_EDIT, m_edtMinCharge);
	DDX_Text(pDX, IDC_MIN_CHARGE_EDIT, m_nMinCharge);


	DDX_Text(pDX, IDC_DAMAS_ADD_EDIT, m_nDamasAdd);
	DDX_Text(pDX, IDC_RABO_ADD_EDIT, m_nRaboAdd);
	DDX_Text(pDX, IDC_BAN_ADD_EDIT, m_nBanAdd);
	DDX_Text(pDX, IDC_TRUCK_ADD_EDIT, m_nTruckAdd);
	DDX_Control(pDX, IDC_BOTH_CHARGE_EDIT, m_BothChargeEdt);
	DDX_Text(pDX, IDC_BOTH_CHARGE_EDIT, m_nBothCharge);
	DDX_Control(pDX, IDC_EMERGENCY_CHARGE_EDIT, m_edtEmergencyCharge);
	DDX_Text(pDX, IDC_EMERGENCY_CHARGE_EDIT, m_strEmergencyCharge);

	DDX_Control(pDX, IDC_MILEAGE_CHECK, m_chkMileage);
	DDX_Control(pDX, IDC_PERCENT_COMBO, m_cmbPercent);
	DDX_Control(pDX, IDC_MILEAGE_SPAN_EDIT, m_edtMileageSpan);
	DDX_Text(pDX, IDC_MILEAGE_SPAN_EDIT, m_nMileageSpan);
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileage);
	DDX_Text(pDX, IDC_MILEAGE_EDIT, m_nMileage);	
	DDX_Control(pDX, IDC_MILEAGE_TERM_BTN, m_btnMileageTerm);
	DDX_Control(pDX, IDC_NOGROUP_CHARGE_CHECK, m_chkNoGroupCharge);
	DDX_Control(pDX, IDC_NOMEMBER_CHARGE_CHECK, m_chkNoMemberCharge);
	DDX_Control(pDX, IDC_MEMCHA_NO_GENERAL_DATA_CHECK, m_chkMemChaNoGeneralData);
	DDX_Control(pDX, IDC_ADDDIS_CHARGE_ROUND_CHECK, m_chkAddDisChargeRound); 

	DDX_CBIndex(pDX, IDC_LABO_CHARGE_TYPE_COMBO, m_nLaboChargeType);
	DDX_Control(pDX, IDC_USE_DIRECT_DISTANCE_CHECK, m_chkUseDirectDistance);

	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_CHECK, m_chkUpChargeForNotAllocateManual);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_CHECK, m_chkUpChargeForNotAllocateAuto);

	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT1, m_edtUpChargeForNotAllocateManual1);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT2, m_edtUpChargeForNotAllocateManual2);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT3, m_edtUpChargeForNotAllocateManual3);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT1, m_strUpChargeForNotAllocateManual1);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT2, m_strUpChargeForNotAllocateManual2);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_EDIT3, m_strUpChargeForNotAllocateManual3);

	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO1, m_cmbUpChargeForNotAllocateMinute1);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO2, m_cmbUpChargeForNotAllocateMinute2);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO3, m_cmbUpChargeForNotAllocateMinute3);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO4, m_cmbUpChargeForNotAllocateMinute4);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO5, m_cmbUpChargeForNotAllocateMinute5);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO1, m_strUpChargeForNotAllocateMinute1);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO2, m_strUpChargeForNotAllocateMinute2);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO3, m_strUpChargeForNotAllocateMinute3);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO4, m_strUpChargeForNotAllocateMinute4);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_MINUTE_COMBO5, m_strUpChargeForNotAllocateMinute5);

	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT1, m_edtUpChargeForNotAllocateAuto1);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT2, m_edtUpChargeForNotAllocateAuto2);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT3, m_edtUpChargeForNotAllocateAuto3);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT4, m_edtUpChargeForNotAllocateAuto4);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT5, m_edtUpChargeForNotAllocateAuto5);

	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT1, m_strUpChargeForNotAllocateAuto1);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT2, m_strUpChargeForNotAllocateAuto2);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT3, m_strUpChargeForNotAllocateAuto3);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT4, m_strUpChargeForNotAllocateAuto4);
	DDX_Text(pDX, IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_EDIT5, m_strUpChargeForNotAllocateAuto5);
	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLOCATE_RESERVE_CHECK, m_chkUpChargeForNotAllocateReserve);

	DDX_Control(pDX, IDC_UP_CHARGE_FOR_NOT_ALLOCATE_DEPOSIT_CHECK, m_chkUpChargeForNotAllocateDeposit);
	DDX_Control(pDX, IDC_NEW_CUSTOMER_MILEAGE_EDIT, m_edtNewCustomerMileage);
	DDX_Control(pDX, IDC_BRANCH_CHARGE_DIS_EDIT , m_edtBranchDis);
	DDX_Control(pDX, IDC_DONGPOS_LI_USE_CHECK, m_chkDongPosLiUse);

	DDX_Control(pDX, IDC_BIKE_WEATHER_ADD_EDIT, m_edtBikeWeatherAdd );
	DDX_Control(pDX, IDC_DAMA_WEATHER_ADD_EDIT, m_edtDamaWeatherAdd );
	DDX_Control(pDX, IDC_LABO_WEATHER_ADD_EDIT, m_edtLaboWeatherAdd );
	DDX_Control(pDX, IDC_VAN_WEATHER_ADD_EDIT,	m_edtVanWeatherAdd  );
	DDX_Control(pDX, IDC_TRUCK_WEATHER_ADD_EDIT,m_edtTruckWeatherAdd);
	DDX_Control(pDX, IDC_WEATHER_CHARGE_CHECK,	m_chkWeatherCharge);

	DDX_Control(pDX, IDC_BIKE_WEATHER_SNOW_ADD_EDIT, m_edtBikeWeatherSnowAdd );
	DDX_Control(pDX, IDC_DAMA_WEATHER_SNOW_ADD_EDIT, m_edtDamaWeatherSnowAdd );
	DDX_Control(pDX, IDC_LABO_WEATHER_SNOW_ADD_EDIT, m_edtLaboWeatherSnowAdd );
	DDX_Control(pDX, IDC_VAN_WEATHER_SNOW_ADD_EDIT,	m_edtVanWeatherSnowAdd  );
	DDX_Control(pDX, IDC_TRUCK_WEATHER_SNOW_ADD_EDIT,m_edtTruckWeatherSnowAdd);
	DDX_Control(pDX, IDC_WEATHER_CHARGE_SNOW_CHECK,	m_chkWeatherChargeSnow);
	DDX_Control(pDX, IDC_SLOW_DIS_EDIT,	m_edtSlowDis);

	DDX_Control(pDX, IDC_WEATHER_CHARGE_AUTO_CHECK,	m_chkWeatherChargeAuto);

	DDX_Control(pDX, IDC_MILEAGE_TRUCK_CHECK, m_chkMileageTruck);
	DDX_Control(pDX, IDC_PERCENT_TRUCK_COMBO, m_cmbPercentTruck);
	DDX_Control(pDX, IDC_MILEAGE_TRUCK_EDIT, m_edtMileageTruck);

	DDX_Control(pDX, IDC_MILEAGE_SAVING_TYPE_COMBO, m_cmbMileageSavingType);


}

BEGIN_MESSAGE_MAP(COptionDlgCharge, CMyFormView)
	ON_WM_MOUSEACTIVATE()
	ON_MESSAGE(WM_REFRESH, OnRefresh )
	ON_BN_CLICKED(IDC_MILEAGE_CHECK, OnBnClickedMileageCheck)
	ON_CBN_SELCHANGE(IDC_PERCENT_COMBO, OnCbnSelchangePercentCombo)
	ON_BN_CLICKED(IDC_MILEAGE_TERM_BTN, OnBnClickedMileageTermBtn)
	

	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_DISTANCE_CHARGE_CHECK, &COptionDlgCharge::OnBnClickedDistanceChargeCheck)
	ON_BN_CLICKED(IDC_WORKTIME_BTN, &COptionDlgCharge::OnBnClickedWorktimeBtn)
	ON_CBN_SELCHANGE(IDC_DISTANCE_CHARGE_COMBO, &COptionDlgCharge::OnCbnSelchangeDistanceChargeCombo)
	ON_BN_CLICKED(IDC_DISTANCE_CHARGE_BTN, &COptionDlgCharge::OnBnClickedDistanceChargeBtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_UP_CHARGE_SET_BTN, &COptionDlgCharge::OnBnClickedUpChargeSetBtn)
	ON_BN_CLICKED(IDC_UP_CHARGE_FOR_NOT_ALLCATE_MANUAL_CHECK, &COptionDlgCharge::OnBnClickedUpChargeForNotAllcateManualCheck)
	ON_BN_CLICKED(IDC_UP_CHARGE_FOR_NOT_ALLCATE_AUTO_CHECK, &COptionDlgCharge::OnBnClickedUpChargeForNotAllcateAutoCheck)
	ON_BN_CLICKED(IDC_AREA_SELECT_BTN, &COptionDlgCharge::OnBnClickedAreaSelectBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgCharge 진단입니다.

#ifdef _DEBUG
void COptionDlgCharge::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgCharge::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgCharge 메시지 처리기입니다.

void COptionDlgCharge::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);

	if(!LF->POWER_CHECK(1301, "요금"))
		EnableWindow(FALSE);

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 

	/*m_btnTip.LoadBitmaps(IDB_TIP_UP, IDB_TIP_DOWN);
	m_btnTip2.LoadBitmaps(IDB_TIP_UP, IDB_TIP_DOWN);*/

	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;  
	sizeTotal.cy = 1450;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	m_BothChargeEdt.SetLimitText(3);
}

int COptionDlgCharge::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	
	return TRUE;
	//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);

}


BOOL COptionDlgCharge::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	long nMileageTruck;

	long nMileage = 0, nMileageSpan = 0;
	if(!m_chkMileage.GetCheck())
		nMileage = nMileageSpan = 0;
	else
	{
		if( m_nMileage == 0 && (m_cmbPercent.GetCurSel() < 2) 	)
		{
			MessageBox("마일리지에 금액이 없습니다 체크를 풀어주시거나 금액을 넣어주세요", "확인", MB_ICONINFORMATION	);
			return FALSE;
		}
		else
		{
			if(m_cmbPercent.GetCurSel() == 2)
				nMileage = SECTION_MILEAGE; // 금액구간
			else if(m_cmbPercent.GetCurSel() == 3)
				nMileage = COUNT_MILEAGE; // 횟수구간
			else if(m_cmbPercent.GetCurSel() == 1)
				nMileage = m_nMileage < 0 ? m_nMileage : m_nMileage * -1;
			else
				nMileage = m_nMileage;
		}

		if(m_nMileageSpan == 0)
		{
			MessageBox("마일리지를 사용할금액이 없습니다 체크를 풀어주시거나 금액을 넣어주세요", "확인", MB_ICONINFORMATION	);			
			return FALSE;
		}
		else
			nMileageSpan = m_nMileageSpan;
	}

	if(!m_chkMileageTruck.GetCheck())
		nMileageTruck = 0;
	else
	{
		long nTemp = LF->GetLongFromEdit(&m_edtMileageTruck);

		if(m_cmbPercentTruck.GetCurSel() == 1)
			nMileageTruck = nTemp * -1;
		else
			nMileageTruck = nTemp;
	}

	long nTempTypeDistanceCharge = 0;
	m_strDefaultCharge.Replace(",","");

	//if(m_chkDistanceCharge.GetCheck() == FALSE)
	//	nTempTypeDistanceCharge = 0;
	//else if(m_strDistanceCharge == "선택요금제")
	//	nTempTypeDistanceCharge = -1;	
	///*else if(m_strDistanceCharge == "기본요금+경유요금")
	//	nTempTypeDistanceCharge = -3;*/
	//else
	//	nTempTypeDistanceCharge = atol(m_strDistanceCharge);

	UpdateSpecialTruckCharge(nCompany, bAll);

	CMkCommand pCmd(m_pMkDb, "update_option_2011_charge20");
	pCmd.AddParameter(bAll);	
	pCmd.AddParameter(nCompany);		
	pCmd.AddParameter(atol(m_strDefaultCharge)); 

	pCmd.AddParameter( m_chkDistanceCharge.GetCheck());
	pCmd.AddParameter( m_cmbDistanceCharge.GetCurSel());  
	pCmd.AddParameter( m_nMinCharge);  

	pCmd.AddParameter(m_nDamasAdd);
	pCmd.AddParameter(m_nRaboAdd);
	pCmd.AddParameter(m_nBanAdd);
	pCmd.AddParameter(m_nTruckAdd);
	pCmd.AddParameter(m_nBothCharge);
	pCmd.AddParameter(atoi(m_strEmergencyCharge));	
	
	pCmd.AddParameter(nMileage);
	pCmd.AddParameter(nMileageSpan);	
	pCmd.AddParameter(nMileageTruck);	
	pCmd.AddParameter(m_ui.strID); 	
	pCmd.AddParameter(m_chkNoGroupCharge.GetCheck()); 	
	pCmd.AddParameter(m_chkNoMemberCharge.GetCheck()); 	
	pCmd.AddParameter(m_chkMemChaNoGeneralData.GetCheck()); 	
	pCmd.AddParameter(m_chkAddDisChargeRound.GetCheck());
	pCmd.AddParameter(m_nLaboChargeType);
	pCmd.AddParameter(m_chkUseDirectDistance.GetCheck());
		
	if(m_chkUpChargeForNotAllocateManual.GetCheck())
		pCmd.AddParameter(1);
	else if(m_chkUpChargeForNotAllocateAuto.GetCheck())
		pCmd.AddParameter(2);
	else
		pCmd.AddParameter(0);

	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateManual1));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateManual2));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateManual3));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_cmbUpChargeForNotAllocateMinute1));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateAuto1));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_cmbUpChargeForNotAllocateMinute2));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateAuto2));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_cmbUpChargeForNotAllocateMinute3));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateAuto3));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_cmbUpChargeForNotAllocateMinute4));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateAuto4));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_cmbUpChargeForNotAllocateMinute5));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtUpChargeForNotAllocateAuto5));
	pCmd.AddParameter(m_chkUpChargeForNotAllocateReserve.GetCheck());
	pCmd.AddParameter(m_chkUpChargeForNotAllocateDeposit.GetCheck());
	pCmd.AddParameter(m_chkDongPosLiUse.GetCheck());
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtNewCustomerMileage));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtBranchDis));

	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtBikeWeatherAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtDamaWeatherAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtLaboWeatherAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtVanWeatherAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtTruckWeatherAdd));
	pCmd.AddParameter(m_chkWeatherCharge.GetCheck());

	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtBikeWeatherSnowAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtDamaWeatherSnowAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtLaboWeatherSnowAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtVanWeatherSnowAdd));
	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtTruckWeatherSnowAdd));
	pCmd.AddParameter(m_chkWeatherChargeSnow.GetCheck());
	pCmd.AddParameter(m_chkWeatherChargeAuto.GetCheck());

	pCmd.AddParameter(LF->GetLongFromEdit(&m_edtSlowDis));
	pCmd.AddParameter(m_cmbMileageSavingType.GetCurSel());
	

	return pCmd.Execute();

//	0 -> 라보요금 다마스요금 사용 m_nLaboChargeType
//		1 -> 라보요금 봉고요금사용 
//		2 -> 라보별도 요금사용


	

}

long COptionDlgCharge::OnRefresh(WPARAM wParam,LPARAM lParam)
{
	BOOL bDistanceChargeCheck = FALSE;

	int  nViaAmount = 0;


	m_nDistanceCharge = -1;

	CMkRecordset* pRs = (CMkRecordset*)lParam;

	return 0L;
}

void COptionDlgCharge::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	//if(nSBCode == SB_ENDSCROLL)
	//	Invalidate(TRUE);
}

BOOL COptionDlgCharge::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{ 
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);
	//if(nFlags == SB_ENDSCROLL)
	//Invalidate(TRUE);

	return TRUE;
}

void COptionDlgCharge::OnBnClickedMileageCheck()
{
	if(m_chkMileage.GetCheck())
	{
		m_edtMileageSpan.EnableWindow(TRUE);
		m_edtMileage.EnableWindow(TRUE);
	}
	else
	{
		m_edtMileage.EnableWindow(FALSE);
		m_edtMileageSpan.EnableWindow(FALSE);
	}
}

void COptionDlgCharge::OnCbnSelchangePercentCombo()
{

	if(m_cmbPercent.GetCurSel() == 2 ||
		m_cmbPercent.GetCurSel() == 3)	
	{
		m_btnMileageTerm.ShowWindow(SW_SHOW);		
		m_edtMileage.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btnMileageTerm.ShowWindow(SW_HIDE);		
		m_edtMileage.ShowWindow(SW_SHOW);
		if(m_chkMileage.GetCheck())
			m_edtMileage.EnableWindow();

		CString sMileage = "";
		m_edtMileage.GetWindowText(sMileage);
		if(sMileage == "100000")
			m_edtMileage.SetWindowText("0");
		if(sMileage == "200000")
			m_edtMileage.SetWindowText("0");

	}

}

void COptionDlgCharge::OnBnClickedMileageTermBtn()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode();

	if(nCompany <= 0)
	{
		MessageBox("지사를 선택하시기 바랍니다.","지사 선택",MB_ICONINFORMATION);
		return;
	}

	if(m_cmbPercent.GetCurSel() == 2)
	{
		CChargeSectionTypeDlg dlg;
		dlg.m_nCompany = nCompany;
		dlg.m_nValueType = CST_BATCH_MILEAGE;
		dlg.m_nInitClass = 0;

		if(dlg.DoModal() == IDOK)
			LF->MsgBox("금액을 수정하신경우에는 모든 접수자가 재로그인을 해주셔야 적용됩니다.");
	}
	else if(m_cmbPercent.GetCurSel() == 3)
	{
		CSetCountMileageDlg dlg;
		dlg.m_nCompany = nCompany;

		if(dlg.DoModal() == IDOK)
			MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);


	}
}


void COptionDlgCharge::OnBnClickedDistanceChargeCheck()
{
	//UpdateData();
	//if(m_bDistanceChargeCheck)
	//{			
	//	m_cmbDistanceCharge.EnableWindow(TRUE);
	//	m_edtMinCharge.EnableWindow(TRUE);
	//}
	//else
	//{		
	//	m_cmbDistanceCharge.EnableWindow(FALSE);
	//	m_edtMinCharge.EnableWindow(FALSE);
	//}
}

void COptionDlgCharge::OnBnClickedWorktimeBtn()
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

void COptionDlgCharge::OnCbnSelchangeDistanceChargeCombo()
{
	if(m_cmbDistanceCharge.GetCurSel() > 0 )
		m_chkDistanceCharge.SetCheck(TRUE);
	if(m_cmbDistanceCharge.GetCurSel() == 0)
		m_chkDistanceCharge.SetCheck(FALSE);

}

void COptionDlgCharge::OnBnClickedDistanceChargeBtn()
{
	if(m_cmbDistanceCharge.GetCurSel() == 0)
	{
		MessageBox("구간요금은 적용 되지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode();

	if(nCompany <= 0)
	{
		MessageBox("지사를 선택하시기 바랍니다.","지사 선택",MB_ICONINFORMATION);
		return;
	}

	CChargeDistanceDlg2 *p = new CChargeDistanceDlg2;
	p->Create(CChargeDistanceDlg2::IDD, this);
	//p->m_nCompany = nCompany;
	p->ShowWindow(SW_SHOW);
	p->SetCompany(nCompany);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgCharge::OnSize(UINT nType, int cx, int cy)
{
	return;
	CMyFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void COptionDlgCharge::OnBnClickedUpChargeSetBtn()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode();

	CUpChargeSetDlg dlg;
	dlg.m_nCompany = pDlg->GetSelCompanyCode(); 
	dlg.DoModal();
}

void COptionDlgCharge::OnBnClickedUpChargeForNotAllcateManualCheck()
{
	if(m_chkUpChargeForNotAllocateManual.GetCheck())
		m_chkUpChargeForNotAllocateAuto.SetCheck(FALSE);
}

void COptionDlgCharge::OnBnClickedUpChargeForNotAllcateAutoCheck()
{
	if(m_chkUpChargeForNotAllocateAuto.GetCheck())
		m_chkUpChargeForNotAllocateManual.SetCheck(FALSE);
}

void COptionDlgCharge::OnBnClickedAreaSelectBtn()
{


	CMainOptionDlg2* pMainDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pMainDlg->GetSelCompanyCode();


	CREATE_MODALESS(CChargeSimpleListDlg, this);
	pDlg->m_nCompany = nCompany;	
	pDlg->m_bChargeDongDlg3 = FALSE;
	SHOW_MODALESS(CChargeSimpleListDlg, this);
}

void COptionDlgCharge::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}

void COptionDlgCharge::ClearSpeicalTruckCharge()
{
	CRect left_rc, right_rc;
	GetDlgItem(IDC_SPECIAL_TRUCK_1TON_1_EDIT)->GetWindowRect(left_rc); ScreenToClient(left_rc);
	GetDlgItem(IDC_SPECIAL_TRUCK_25TON_5_EDIT)->GetWindowRect(right_rc); ScreenToClient(right_rc);

	CRect rc(left_rc.left, left_rc.top, right_rc.right, right_rc.bottom);

	CWnd *pWnd = CWnd::FromHandle(this->GetSafeHwnd()); 
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD); //제일 위의 새끼를 검색한다.

	while(pChildWnd != NULL)
	{ 
		CRect rcChild;  
		pChildWnd->GetWindowRect(rcChild); ScreenToClient(rcChild);
		CPoint pt(rcChild.left, rcChild.top);

		if(rc.PtInRect(pt))
			pChildWnd->SetWindowText("");

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

void COptionDlgCharge::RefreshSpecialTruckCharge(int company_code)
{
	ClearSpeicalTruckCharge();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "special_truck_charge_all_select");
	cmd.AddParameter(company_code);
	int car_type, jabara_add, lift_add, wing_body_add, lift_wing_add, freezer_add;

	if(rs.Execute(&cmd)) {		
		while(!rs.IsEOF()) {
			rs.GetFieldValue("car_type", car_type);
			rs.GetFieldValue("jabara_add", jabara_add);
			rs.GetFieldValue("lift_add", lift_add);
			rs.GetFieldValue("wing_body_add", wing_body_add);
			rs.GetFieldValue("lift_wing_add", lift_wing_add);
			rs.GetFieldValue("freezer_add", freezer_add);

			AddSpecialTruckCharge(car_type, CARGO_JABARA, jabara_add);
			AddSpecialTruckCharge(car_type, CARGO_LIFT, lift_add);
			AddSpecialTruckCharge(car_type, CARGO_WING_BODY, wing_body_add);
			AddSpecialTruckCharge(car_type, CARGO_LIFT_WING, lift_wing_add);
			AddSpecialTruckCharge(car_type, CARGO_FREEZER, freezer_add);			
			rs.MoveNext();
		}
	}
}

void COptionDlgCharge::AddSpecialTruckCharge(int car_type, int special_truck_type, int charge)
{
	CWnd *wnd = GetSpecialTruckTypeControl(car_type, special_truck_type);

	if(wnd) 
		wnd->SetWindowText(LF->RemoveZero(LF->GetMyNumberFormat(charge)));
}

void COptionDlgCharge::UpdateSpecialTruckCharge(long nCompany, BOOL bAll)
{
	UpdateSpecialTruckChargeSub(nCompany, CAR_TRUCK);
	UpdateSpecialTruckChargeSub(nCompany, CAR_1_4_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_2_5_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_3_5_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_5_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_5_TON_PLUS);
	UpdateSpecialTruckChargeSub(nCompany, CAR_8_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_11_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_14_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_15_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_18_TON);
	UpdateSpecialTruckChargeSub(nCompany, CAR_25_TON);

	LF->FillSpeicalTruckChage();
}

void COptionDlgCharge::UpdateSpecialTruckChargeSub(long nCompany, int car_type)
{
	CMkCommand cmd(m_pMkDb, "special_truck_charge_update");
	cmd.AddParameter(nCompany);
	cmd.AddParameter(car_type);
	cmd.AddParameter(GetSpecialTruckCharge(car_type, CARGO_JABARA));
	cmd.AddParameter(GetSpecialTruckCharge(car_type, CARGO_LIFT));
	cmd.AddParameter(GetSpecialTruckCharge(car_type, CARGO_WING_BODY));
	cmd.AddParameter(GetSpecialTruckCharge(car_type, CARGO_LIFT_WING));
	cmd.AddParameter(GetSpecialTruckCharge(car_type, CARGO_FREEZER));

	cmd.Execute();
}

int COptionDlgCharge::GetSpecialTruckCharge(int car_type, int special_truck_type)
{
	CWnd *wnd = GetSpecialTruckTypeControl(car_type, special_truck_type);

	if(wnd) 
		return LF->GetLongFromEdit(wnd);

	return 0;

}

CWnd* COptionDlgCharge::GetSpecialTruckTypeControl(int car_type, int special_truck_type)
{
	int id = 0;
	switch (car_type) {
		case CAR_TRUCK :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_1TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_1TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_1TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_1TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_1TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_1_4_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_1_4TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_1_4TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_1_4TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_1_4TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_1_4TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_2_5_TON :
			switch (special_truck_type) {
			case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_2_5TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_2_5TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_2_5TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_2_5TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_2_5TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_3_5_TON :
			switch (special_truck_type) {
			case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_3_5TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_3_5TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_3_5TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_3_5TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_3_5TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_5_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_5TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_5TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_5TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_5TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_5TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_5_TON_PLUS :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_5_5TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_5_5TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_5_5TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_5_5TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_5_5TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_8_TON :
			switch (special_truck_type) {
			case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_8TON_1_EDIT; break;
			case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_8TON_2_EDIT; break;
			case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_8TON_3_EDIT; break;
			case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_8TON_4_EDIT; break;
			case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_8TON_5_EDIT; break;
			default: id = 0; break;
			}
		break;
		case CAR_11_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_11TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_11TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_11TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_11TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_11TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_14_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_14TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_14TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_14TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_14TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_14TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_15_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_15TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_15TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_15TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_15TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_15TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_18_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_18TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_18TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_18TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_18TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_18TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		case CAR_25_TON :
			switch (special_truck_type) {
				case CARGO_JABARA : id = IDC_SPECIAL_TRUCK_25TON_1_EDIT; break;
				case CARGO_LIFT : id = IDC_SPECIAL_TRUCK_25TON_2_EDIT; break;
				case CARGO_WING_BODY : id = IDC_SPECIAL_TRUCK_25TON_3_EDIT; break;
				case CARGO_LIFT_WING : id = IDC_SPECIAL_TRUCK_25TON_4_EDIT; break;
				case CARGO_FREEZER : id = IDC_SPECIAL_TRUCK_25TON_5_EDIT; break;
				default: id = 0; break;
			}
		break;
		default: id = 0; break;		
	}

	return GetDlgItem(id);
}


