// MainOptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MainOptionDlg2011.h"
#include "Mainfrm.h"
#include "OptionDlgGeneral2.h"
#include "OptionDlgCharge.h"
#include "OptionDlgCID.h"
#include "OptionDlgSMS3.h" 
#include "OptionDlgInterCall2.h" 
#include "OptionDlgMobileNew.h"
#include "OptionDlgPersonalInfo.h"
#include "OptionDlgSmartQ.h"
#include "OptionDlgSmartQuick.h"
#include "OptionDlgLogiContract.h"

CMainOptionTabControl2::CMainOptionTabControl2()
: CXTPTabControl()
{
	m_pMainOptionDlg = NULL;
} 

void CMainOptionTabControl2::OnItemClick(CXTPTabManagerItem* pItem)
{

	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->RefreshList();
	
	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();
	//CXTPTabControl::OnItemClick( pItem);
	//Invalidate(TRUE);
	
}

void CMainOptionTabControl2::SetControl(CMainOptionDlg2 *pDlg)
{
	m_pMainOptionDlg = pDlg;
}


IMPLEMENT_DYNAMIC(CMainOptionDlg2, CMyDialog)
CMainOptionDlg2::CMainOptionDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMainOptionDlg2::IDD, pParent)
{
	m_pParentWnd = pParent;
	
	m_nFirstSelectTab = OPTION_GENERAL_TAB;
	m_bIntegrated = FALSE;

	m_bLogView = FALSE;
	m_nLogViewCompany = -1;
	m_nLogID = -1;
	m_pMainOptionDlg = NULL;
	m_bMainOptionDlgCreate = FALSE;
}

CMainOptionDlg2::~CMainOptionDlg2()
{
}

void CMainOptionDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_BranchCombo);
	DDX_Control(pDX, IDC_APPLY_ALL_BTN, m_ApplyAllBtn);
	DDX_Control(pDX, IDOK, m_IDOK);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_CloseBtn);
	DDX_Control(pDX, IDC_CHECK2, m_chkTest);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);
	DDX_Control(pDX, IDC_LIST1, m_List);
	

	

}


BEGIN_MESSAGE_MAP(CMainOptionDlg2, CMyDialog)
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
	ON_BN_CLICKED(IDC_APPLY_ALL_BTN, OnBnClickedApplyAllBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnBnClickedClose)
	ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)	
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// CMainOptionDlg2 메시지 처리기입니다.
BOOL CMainOptionDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nCol = 0;
	m_List.InsertColumn(nCol++, "수정번호", DT_LEFT, 100, FALSE, FALSE );
	m_List.InsertColumn(nCol++, "수정일시", DT_LEFT, 140, FALSE, FALSE );
	m_List.InsertColumn(nCol++, "수정한탭", DT_LEFT, 120, FALSE, FALSE );
	m_List.InsertColumn(nCol++, "작업자", DT_LEFT, 80, FALSE, FALSE );
	m_List.InsertColumn(nCol++, "지사이름", DT_LEFT, 100, FALSE, FALSE );
	m_List.InsertColumn(nCol++, "전체적용", DT_LEFT, 60, FALSE, FALSE );
	m_List.m_bHeader = TRUE;
	m_List.InitControl();

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);



	//순서 바뀌면 안됨
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgGeneral2), "일반", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgCharge), "요금/마일리지", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgCID), "키폰", 0);	
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgSMS3), "SMS", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgMobileNew), "모바일", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgInterCall2), "인터콜", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgPersonalInfo), "카드가맹신청", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgSmartQ), "스마트퀵", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgSmartQuick), "스마트퀵(신)", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(COptionDlgLogiContract), "로지_계약정보", 0);
	
	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub);
	m_lstBranch.SetMapData(&m_cBranch);	  
	m_wndTabControl.SetCurSel(m_nFirstSelectTab);



	if(m_bLogView)
	{
		m_edtMain.ShowWindow(FALSE);
		m_edtSub.ShowWindow(FALSE);
		m_btnMain.ShowWindow(FALSE);
		m_btnSub.ShowWindow(FALSE);
		//m_BranchCombo.ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_APPLY_ALL_BTN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_APPLY_ALL_BTN)->ShowWindow(SW_HIDE);

	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMainOptionDlg2::Refresh()
{
	RefreshInfo();
	RefreshLogInfo();
}


void CMainOptionDlg2::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	//if(nItem >= 0 && m_List.GetItemText(nItem, 9).GetLength() > 0) {
	if(nItem >= 0) 
	{
		long nCompany = -1;
		CBranchInfo *pBi = m_cBranch.GetBranchInfo();

		//if(m_bIntegrated)
		//	pBi = (CBranchInfo*)m_BranchCombo.GetItemData(m_BranchCombo.GetCurSel());
		//else
		//	nCompany = (long)m_BranchCombo.GetItemData(m_BranchCombo.GetCurSel());

		long nLogID = atol(m_List.GetItemText(nItem,0));
		nCompany = pBi->nCompanyCode;


		if(!m_pMainOptionDlg )
		{
			m_pMainOptionDlg = new CMainOptionDlg2(this);
			m_bMainOptionDlgCreate = TRUE;
		}

		m_pMainOptionDlg->m_bLogView = TRUE;
		m_pMainOptionDlg->m_nLogID = nLogID;

		m_pMainOptionDlg->m_nLogViewCompany = m_bIntegrated ? pBi->nCompanyCode : nCompany;	
		if(m_bMainOptionDlgCreate)
		{
			m_pMainOptionDlg->Create(IDD_MAIN_OPTION_DLG1, this);
			m_bMainOptionDlgCreate = FALSE;
		}
		else
			m_pMainOptionDlg->Refresh();

		CRect rect, rectLog;
		this->GetClientRect(rect);

		rectLog = rect;
		rectLog.top += 10;
		rectLog.bottom -= 50;
		rectLog.left = rect.right;
		rectLog.right += rect.Width()+ 8;
		//rectLog.left = rect.right ;
		//rectLog.right += rect.Width() + 10;

		//rectLog.Height() += 20;

		m_pMainOptionDlg->MoveWindow(rectLog);
		m_pMainOptionDlg->ShowWindow(SW_SHOW);
		m_wndTabControl.SetControl(m_pMainOptionDlg);

	}


}

void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgGeneral2*	pOptionDlgGeneral)
{	
	BOOL bUserIDSequence = FALSE, bUserDongPos = FALSE, bUsePayBonggoFromLabo = FALSE, bCorporationTelHidden;		
	BOOL bMyCallRiderDeposit = FALSE;
	CString strTaxUseEmail = "";
	long nRcpTimeColor = 0, nAutoShareTime = 0, nRevisitCustomerSendDay = 0, nHistoryDetailAllView = 0, nAutoDelay;
	long nCnsSearchType1, nCnsSearchType2, nCnsSearchPaid;
	BOOL bKeepChargeCompany, bInitDt1StateToRcp;

	pRs->GetFieldValue("bWaitSecondCall"		, pOptionDlgGeneral->m_bWaitSecondCall);
	pRs->GetFieldValue("nRcpTimeColor"		,	nRcpTimeColor);
	pRs->GetFieldValue("bNoUseCNS"			, pOptionDlgGeneral->m_bNoUseCNS);
	pRs->GetFieldValue("bUserIDSequence", bUserIDSequence); //,   -- 고객번호 1나씩 증가시키기
	pRs->GetFieldValue("bMemoToEtc",pOptionDlgGeneral->m_bMemoToEtc );
	pRs->GetFieldValue("bRiderMemoToEtc",pOptionDlgGeneral->m_bRiderMemoToEtc );
	pRs->GetFieldValue("bCallerIDToPhone1",pOptionDlgGeneral->m_bCallerIDToPhone1 );
	pRs->GetFieldValue("bClearDestForAfterCopy",pOptionDlgGeneral->m_bClearDestForAfterCopy );
	pRs->GetFieldValue("bSingleAllocate",pOptionDlgGeneral->m_bSingleAllocate);
	pRs->GetFieldValue("bUsageHistory",pOptionDlgGeneral->m_bUsageHistory);
	pRs->GetFieldValue("bGiveChargeToRiderByCreditOrder", pOptionDlgGeneral->m_bGiveChargeRider);
	pRs->GetFieldValue("bDisableCreditBtn", pOptionDlgGeneral->m_bDisableCreditBtn);//   -
	pRs->GetFieldValue("bUserDongPos",bUserDongPos); 
	pRs->GetFieldValue("bUseOrderChangeMent",pOptionDlgGeneral->m_bUseOrderChangeMent); 
	pRs->GetFieldValue("bUseRTIDOnSpeedAllocate", pOptionDlgGeneral->m_bUseRTIDOnSpeedAllocate);
	pRs->GetFieldValue("bUsePayBonggoFromLabo",bUsePayBonggoFromLabo); 
	pRs->GetFieldValue("bSingleAllocate"	, pOptionDlgGeneral->m_bSingleAllocate);
	pRs->GetFieldValue("bUseCardTax"	, pOptionDlgGeneral->m_bUseCardTax);
	pRs->GetFieldValue("bNotUseEtcForCancel"	, pOptionDlgGeneral->m_bNotUseEtcForCancel);
	pRs->GetFieldValue("bAutoShareOrder"	, pOptionDlgGeneral->m_bAutoShareOrder);
	pRs->GetFieldValue("nAutoShareTime"	, nAutoShareTime);
	pRs->GetFieldValue("nRevisitCustomerSendDay"	, nRevisitCustomerSendDay);
	pRs->GetFieldValue("bFocusToWaitBtn",pOptionDlgGeneral->m_bFocusToWaitBtn );
	pRs->GetFieldValue("nTankType",pOptionDlgGeneral->m_nTankType);
	pRs->GetFieldValue("bShowTank",pOptionDlgGeneral->m_bShowTank);
	pRs->GetFieldValue("bUseOrderBundle",pOptionDlgGeneral->m_bUseOrderBundle);
	pRs->GetFieldValue("bCancelToInquiry",pOptionDlgGeneral->m_bCancelToInquiry);
	pRs->GetFieldValue("bEtcAuto",pOptionDlgGeneral->m_bEtcAuto);
	pRs->GetFieldValue("sEtcAuto",pOptionDlgGeneral->m_strEtcAuto);
	pRs->GetFieldValue("bCorporationTelHidden", bCorporationTelHidden);
	pRs->GetFieldValue("bMyCallRiderDeposit", bMyCallRiderDeposit);
	pRs->GetFieldValue("sTaxUseEmail", strTaxUseEmail);
	pRs->GetFieldValue("bCancelReason", pOptionDlgGeneral->m_bCancelReason);
	pRs->GetFieldValue("bInitDongInfo", pOptionDlgGeneral->m_bInitDongInfo);
	pRs->GetFieldValue("bCreditListPopup", pOptionDlgGeneral->m_bCreditListPopup);
	pRs->GetFieldValue("bNoDestPoi", pOptionDlgGeneral->m_bNoDestPoi);
	pRs->GetFieldValue("bNotClientPhone1", pOptionDlgGeneral->m_bNotClientPhone1);
	pRs->GetFieldValue("bNotCustomerAddCID", pOptionDlgGeneral->m_bNotCustomerAddCID);
	pRs->GetFieldValue("bInsertPhoneToInterCallID", pOptionDlgGeneral->m_bInsertPhoneToInterCallID);
	pRs->GetFieldValue("bCustomerAutoInsert", pOptionDlgGeneral->m_bCustomerAutoInsert);
	pRs->GetFieldValue("bFirstWaitTimePast", pOptionDlgGeneral->m_bFirstWaitTimePast);
	pRs->GetFieldValue("bNotChangedt1ForDelay", pOptionDlgGeneral->m_bNotChangedt1ForDelay);
	pRs->GetFieldValue("sNewCustomerName", pOptionDlgGeneral->m_strNewCustomerName);
	
	pRs->GetFieldValue("sInterCallPassword", pOptionDlgGeneral->m_strInterCallPassword);
	pRs->GetFieldValue("nHistoryDetailAllView", nHistoryDetailAllView);
	pRs->GetFieldValue("bPopupFocus", pOptionDlgGeneral->m_bPopupFocus);
	pRs->GetFieldValue("bColorChange", pOptionDlgGeneral->m_bColorChange);
	pRs->GetFieldValue("bOnlyLoadInsRider", pOptionDlgGeneral->m_bOnlyLoadInsRider);

	pRs->GetFieldValue("bVRAccountNoRider", pOptionDlgGeneral->m_bVRAccountNoRider);
	pRs->GetFieldValue("nAutoDelay", nAutoDelay);
	pRs->GetFieldValue("nCnsSearchType1", nCnsSearchType1);
	pRs->GetFieldValue("nCnsSearchType2", nCnsSearchType2);
	pRs->GetFieldValue("nCnsSearchPaid", nCnsSearchPaid);
	pRs->GetFieldValue("sKakaoKey", pOptionDlgGeneral->m_strKakaoKey);
	pRs->GetFieldValue("bKeepChargeCompany", bKeepChargeCompany);
	pRs->GetFieldValue("init_dt1_state_to_rcp", bInitDt1StateToRcp);

	pOptionDlgGeneral->m_chkHistoryDetailAllView.SetCheck(nHistoryDetailAllView);
	pOptionDlgGeneral->m_chkCompanyTelHidden.SetCheck(bCorporationTelHidden);
	pOptionDlgGeneral->m_chkMyCallRiderDeposit.SetCheck(bMyCallRiderDeposit);
	pOptionDlgGeneral->m_btnMyCallRiderDeposit.EnableWindow(bMyCallRiderDeposit);	
	pOptionDlgGeneral->m_edtTaxUseEmail.SetWindowText(strTaxUseEmail); 
	CString strCarTypeOrder, strPayTypeOrder;
	pRs->GetFieldValue("sPayTypeOrder", strPayTypeOrder);
	pRs->GetFieldValue("sCarTypeOrder", strCarTypeOrder);
	pOptionDlgGeneral->SetCarOrder(strCarTypeOrder);
	pOptionDlgGeneral->SetPayOrder(strPayTypeOrder);
	pOptionDlgGeneral->m_edtKakaoKey.SetWindowText(pOptionDlgGeneral->m_strKakaoKey);
	pOptionDlgGeneral->m_chkKeepChargeCompany.SetCheck(bKeepChargeCompany);
	pOptionDlgGeneral->m_chkInitDt1StateToRcp.SetCheck(bInitDt1StateToRcp);

	pOptionDlgGeneral->m_strAutoShareTime.Format("%d", nAutoShareTime);

	if(pOptionDlgGeneral->m_bShowTank)
	{
		if(m_ui.nRole == 0 && m_ui.strName == "관리자" )
		{				
			pOptionDlgGeneral->m_stcTank.ShowWindow(SW_SHOW);				
			pOptionDlgGeneral->m_btnTankAllView.ShowWindow(SW_SHOW);				
		}
	}
	else
	{
		pOptionDlgGeneral->m_stcTank.ShowWindow(SW_HIDE);			
		pOptionDlgGeneral->m_btnTankAllView.ShowWindow(SW_HIDE);			
	}
 
	if(!pOptionDlgGeneral->m_bCallerIDToPhone1)
		pOptionDlgGeneral->m_chkNotClientPhone1.EnableWindow(FALSE);

	if(pOptionDlgGeneral->m_bWaitSecondCall)
		pOptionDlgGeneral->m_bWaitSecondCall = TRUE;

	if(nRcpTimeColor == 0)
	{
		nRcpTimeColor = (3 << 16) + (7 << 8) + 15;
	}
	pOptionDlgGeneral->m_strRcpTimeColor1.Format("%d", (BYTE)(nRcpTimeColor >> 16));
	pOptionDlgGeneral->m_strRcpTimeColor2.Format("%d", (BYTE)(nRcpTimeColor >> 8));
	pOptionDlgGeneral->m_strRcpTimeColor3.Format("%d", (BYTE)(nRcpTimeColor));		
	pOptionDlgGeneral->m_UserIDSequenceCheck.SetCheck(bUserIDSequence);
	if(pOptionDlgGeneral->m_bSingleAllocate)	pOptionDlgGeneral->m_bSingleAllocate = TRUE;
	pOptionDlgGeneral->m_chkUserDongPos.SetCheck(bUserDongPos);
	pOptionDlgGeneral->m_chkUseRTIDOnSpeedAllocate.SetCheck(pOptionDlgGeneral->m_bUseRTIDOnSpeedAllocate);
	pOptionDlgGeneral->m_chkUsePayBonggoFromLabo.SetCheck(bUsePayBonggoFromLabo);
	pOptionDlgGeneral->m_chkUseCardTax.SetCheck(pOptionDlgGeneral->m_bUseCardTax);
	pOptionDlgGeneral->m_strRevisitCustomerSendDay = ::RemoveZero(nRevisitCustomerSendDay);
	pOptionDlgGeneral->m_chkRevisitCustomer.SetCheck(nRevisitCustomerSendDay);
	pOptionDlgGeneral->m_edtRevisitCustomerSendDay.EnableWindow(nRevisitCustomerSendDay);
	pOptionDlgGeneral->m_edtEtcAuto.SetWindowText(pOptionDlgGeneral->m_strEtcAuto);
	pOptionDlgGeneral->m_edtNewCustomerName.SetWindowText(pOptionDlgGeneral->m_strNewCustomerName);

	pOptionDlgGeneral->m_chkAutoDelay.SetCheck(nAutoDelay > 0);
	pOptionDlgGeneral->m_strAutoDelay.Format("%d", nAutoDelay);

	pOptionDlgGeneral->m_cmbCnsSearchType1.SetCurSel(max(nCnsSearchType1 - 1, 0));
	pOptionDlgGeneral->m_cmbCnsSearchType2.SetCurSel(max(nCnsSearchType2 - 1, 0));
	pOptionDlgGeneral->m_cmbCnsSearchPaid.SetCurSel(max(nCnsSearchPaid - 1, 0));
}

void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgCharge*	pOptionDlgCharge)
{ 
	
	char buffer[10];
	long nDefaultCharge = 0, nEmergencyCharge= 0;
	BOOL bDistanceChargeCheck = FALSE, bNoGroupCharge = FALSE, bAddDisChargeRound = FALSE,
			bNotMemberCharge = FALSE, bUseDirectDistance = FALSE , bMemChaNoGeneralData = FALSE,
			bDongPosLiUse = FALSE;

	long nUseUpChargeForNotAllocate;
	long nUpChargeForNotAllocate1;
	long nUpChargeForNotAllocate2;
	long nUpChargeForNotAllocate3;

	long nUpChargeForNotAllocateMinute1;
	long nUpChargeForNotAllocateAuto1;
	long nUpChargeForNotAllocateMinute2;
	long nUpChargeForNotAllocateAuto2;
	long nUpChargeForNotAllocateMinute3;
	long nUpChargeForNotAllocateAuto3;
	long nUpChargeForNotAllocateMinute4;
	long nUpChargeForNotAllocateAuto4;
	long nUpChargeForNotAllocateMinute5;
	long nUpChargeForNotAllocateAuto5;
	BOOL bUpChargeForNotAllocateReserve;
	BOOL bUpChargeForNotAllocateDeposit, bWeatherCharge, bWeatherChargeSnow, bWeatherChargeAuto;
	long nNewCustomerMileage;
	long nBranchDiscount;
	long nBikeWeatherCharge,nDamaWeatherCharge,nLaboWeatherCharge,nVanWeatherCharge,nTruckWeatherCharge;
	long nBikeWeatherChargeSnow,nDamaWeatherChargeSnow,nLaboWeatherChargeSnow,nVanWeatherChargeSnow,nTruckWeatherChargeSnow;
	long nSlowDiscount, nMileageSavingType;

	pRs->GetFieldValue("nDefaultCharge"	, nDefaultCharge);
	pRs->GetFieldValue("bDistanceCharge"		, pOptionDlgCharge->m_bDistanceChargeCheck);
	pRs->GetFieldValue("nDistanceCharge"		, pOptionDlgCharge->m_nDistanceCharge);
	pRs->GetFieldValue("nMinCharge"			, pOptionDlgCharge->m_nMinCharge);
	pRs->GetFieldValue("nDamasPay", pOptionDlgCharge->m_nDamasAdd);
	pRs->GetFieldValue("nRaboPay", pOptionDlgCharge->m_nRaboAdd);
	pRs->GetFieldValue("nBonggoPay", pOptionDlgCharge->m_nBanAdd);
	pRs->GetFieldValue("nTruckPay", pOptionDlgCharge->m_nTruckAdd);
	pRs->GetFieldValue("nBothCharge", pOptionDlgCharge->m_nBothCharge);
	pRs->GetFieldValue("nEmergencyCharge", nEmergencyCharge);
	pRs->GetFieldValue("nMileageSettingCount",pOptionDlgCharge->m_nMileage );
//	pRs->GetFieldValue("nMileageSettingCountTruck",pOptionDlgCharge->m_nMileageTruck );
	pRs->GetFieldValue("nMileageSpan",pOptionDlgCharge->m_nMileageSpan );
	pRs->GetFieldValue("bNoGroupCharge",bNoGroupCharge);	
	pRs->GetFieldValue("bAddDisChargeRound",bAddDisChargeRound);	
	pRs->GetFieldValue("bNotMemberCharge",bNotMemberCharge);
	pRs->GetFieldValue("bMemChaNoGeneralData",bMemChaNoGeneralData);
	
	pRs->GetFieldValue("nLaboChargeType",pOptionDlgCharge->m_nLaboChargeType);	
	pRs->GetFieldValue("bUseDirectDistance",bUseDirectDistance);

	pRs->GetFieldValue("nUseUpChargeForNotAllocate",	nUseUpChargeForNotAllocate);
	pRs->GetFieldValue("nUpChargeForNotAllocate1",		nUpChargeForNotAllocate1);
	pRs->GetFieldValue("nUpChargeForNotAllocate2",		nUpChargeForNotAllocate2);
	pRs->GetFieldValue("nUpChargeForNotAllocate3",		nUpChargeForNotAllocate3);

	pRs->GetFieldValue("nUpChargeForNotAllocateMinute1",nUpChargeForNotAllocateMinute1);
	pRs->GetFieldValue("nUpChargeForNotAllocateAuto1",	nUpChargeForNotAllocateAuto1);
	pRs->GetFieldValue("nUpChargeForNotAllocateMinute2",nUpChargeForNotAllocateMinute2);
	pRs->GetFieldValue("nUpChargeForNotAllocateAuto2",	nUpChargeForNotAllocateAuto2);
	pRs->GetFieldValue("nUpChargeForNotAllocateMinute3",nUpChargeForNotAllocateMinute3);
	pRs->GetFieldValue("nUpChargeForNotAllocateAuto3",	nUpChargeForNotAllocateAuto3);
	pRs->GetFieldValue("nUpChargeForNotAllocateMinute4",nUpChargeForNotAllocateMinute4);
	pRs->GetFieldValue("nUpChargeForNotAllocateAuto4",	nUpChargeForNotAllocateAuto4);
	pRs->GetFieldValue("nUpChargeForNotAllocateMinute5",nUpChargeForNotAllocateMinute5);
	pRs->GetFieldValue("nUpChargeForNotAllocateAuto5",	nUpChargeForNotAllocateAuto5);
	pRs->GetFieldValue("bUpChargeForNotAllocateReserve",bUpChargeForNotAllocateReserve);
	pRs->GetFieldValue("bUpChargeForNotAllocateDeposit",bUpChargeForNotAllocateDeposit);
	pRs->GetFieldValue("nNewCustomerMileage",			nNewCustomerMileage);
	pRs->GetFieldValue("nBranchDiscount",				nBranchDiscount);
	pRs->GetFieldValue("bDongPosLiUse",					bDongPosLiUse);
	pRs->GetFieldValue("nBikeWeatherCharge",			nBikeWeatherCharge	);
	pRs->GetFieldValue("nDamaWeatherCharge",			nDamaWeatherCharge	);
	pRs->GetFieldValue("nLaboWeatherCharge",			nLaboWeatherCharge	);
	pRs->GetFieldValue("nVanWeatherCharge",				nVanWeatherCharge	);
	pRs->GetFieldValue("nTruckWeatherCharge",			nTruckWeatherCharge	);
	pRs->GetFieldValue("bWeatherCharge",				bWeatherCharge	);

	if(!m_bLogView)
	{
		pRs->GetFieldValue("nMileageSettingCountTruck",pOptionDlgCharge->m_nMileageTruck );
		pRs->GetFieldValue("nBikeWeatherChargeSnow",		nBikeWeatherChargeSnow	);
		pRs->GetFieldValue("nDamaWeatherChargeSnow",		nDamaWeatherChargeSnow	);
		pRs->GetFieldValue("nLaboWeatherChargeSnow",		nLaboWeatherChargeSnow	);
		pRs->GetFieldValue("nVanWeatherChargeSnow",			nVanWeatherChargeSnow	);
		pRs->GetFieldValue("nTruckWeatherChargeSnow",		nTruckWeatherChargeSnow	);
		pRs->GetFieldValue("bWeatherChargeSnow",			bWeatherChargeSnow	);
		pRs->GetFieldValue("bWeatherChargeAuto",			bWeatherChargeAuto	);
		pRs->GetFieldValue("nMileageSavingType",			nMileageSavingType	);
		pRs->GetFieldValue("nSlowDiscount",				nSlowDiscount	);
	}
	else
	{
		pOptionDlgCharge->m_nMileageTruck = 0;
		nBikeWeatherChargeSnow = 0;
		nDamaWeatherChargeSnow = 0;
		nLaboWeatherChargeSnow = 0;
		nVanWeatherChargeSnow = 0;
		nTruckWeatherChargeSnow = 0;
		bWeatherChargeSnow = 0;
		bWeatherChargeAuto = 0;
		nMileageSavingType = 0;
		nMileageSavingType = 0;
		nSlowDiscount = 0;
	}


	
	if(nUseUpChargeForNotAllocate == 1)
	{
		pOptionDlgCharge->m_chkUpChargeForNotAllocateManual.SetCheck(TRUE);
		pOptionDlgCharge->m_chkUpChargeForNotAllocateAuto.SetCheck(FALSE);
	}
	else if(nUseUpChargeForNotAllocate == 2)
	{
		pOptionDlgCharge->m_chkUpChargeForNotAllocateManual.SetCheck(FALSE);
		pOptionDlgCharge->m_chkUpChargeForNotAllocateAuto.SetCheck(TRUE);
	}
	else
	{
		pOptionDlgCharge->m_chkUpChargeForNotAllocateManual.SetCheck(FALSE);
		pOptionDlgCharge->m_chkUpChargeForNotAllocateAuto.SetCheck(FALSE);
	}  

	pOptionDlgCharge->m_strUpChargeForNotAllocateManual1 = ::GetMyNumberFormat(nUpChargeForNotAllocate1);
	pOptionDlgCharge->m_strUpChargeForNotAllocateManual2 = ::GetMyNumberFormat(nUpChargeForNotAllocate2);
	pOptionDlgCharge->m_strUpChargeForNotAllocateManual3 = ::GetMyNumberFormat(nUpChargeForNotAllocate3);
	pOptionDlgCharge->m_strUpChargeForNotAllocateMinute1 = ::GetMyNumberFormat(nUpChargeForNotAllocateMinute1);
	pOptionDlgCharge->m_strUpChargeForNotAllocateMinute2 = ::GetMyNumberFormat(nUpChargeForNotAllocateMinute2);
	pOptionDlgCharge->m_strUpChargeForNotAllocateMinute3 = ::GetMyNumberFormat(nUpChargeForNotAllocateMinute3);
	pOptionDlgCharge->m_strUpChargeForNotAllocateMinute4 = ::GetMyNumberFormat(nUpChargeForNotAllocateMinute4);
	pOptionDlgCharge->m_strUpChargeForNotAllocateMinute5 = ::GetMyNumberFormat(nUpChargeForNotAllocateMinute5);
	pOptionDlgCharge->m_strUpChargeForNotAllocateAuto1 = ::GetMyNumberFormat(nUpChargeForNotAllocateAuto1);
	pOptionDlgCharge->m_strUpChargeForNotAllocateAuto2 = ::GetMyNumberFormat(nUpChargeForNotAllocateAuto2);
	pOptionDlgCharge->m_strUpChargeForNotAllocateAuto3 = ::GetMyNumberFormat(nUpChargeForNotAllocateAuto3);
	pOptionDlgCharge->m_strUpChargeForNotAllocateAuto4 = ::GetMyNumberFormat(nUpChargeForNotAllocateAuto4);
	pOptionDlgCharge->m_strUpChargeForNotAllocateAuto5 = ::GetMyNumberFormat(nUpChargeForNotAllocateAuto5);

	pOptionDlgCharge->m_cmbUpChargeForNotAllocateMinute1.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateMinute1));
	pOptionDlgCharge->m_edtUpChargeForNotAllocateAuto1.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateAuto1));
	pOptionDlgCharge->m_cmbUpChargeForNotAllocateMinute2.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateMinute2));
	pOptionDlgCharge->m_edtUpChargeForNotAllocateAuto2.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateAuto2));
	pOptionDlgCharge->m_cmbUpChargeForNotAllocateMinute3.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateMinute3));
	pOptionDlgCharge->m_edtUpChargeForNotAllocateAuto3.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateAuto3));
	pOptionDlgCharge->m_cmbUpChargeForNotAllocateMinute4.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateMinute4));
	pOptionDlgCharge->m_edtUpChargeForNotAllocateAuto4.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateAuto4));
	pOptionDlgCharge->m_cmbUpChargeForNotAllocateMinute5.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateMinute5));
	pOptionDlgCharge->m_edtUpChargeForNotAllocateAuto5.SetWindowText(::GetMyNumberFormat(nUpChargeForNotAllocateAuto5));
	pOptionDlgCharge->m_chkUpChargeForNotAllocateReserve.SetCheck(bUpChargeForNotAllocateReserve);
	pOptionDlgCharge->m_chkUpChargeForNotAllocateDeposit.SetCheck(bUpChargeForNotAllocateDeposit);
	pOptionDlgCharge->m_edtNewCustomerMileage.SetWindowText(::GetMyNumberFormat(nNewCustomerMileage));
				 
	pOptionDlgCharge->m_chkAddDisChargeRound.SetCheck(bAddDisChargeRound);
	pOptionDlgCharge->m_chkNoGroupCharge.SetCheck(bNoGroupCharge);
	pOptionDlgCharge->m_chkNoMemberCharge.SetCheck(bNotMemberCharge);
	pOptionDlgCharge->m_chkMemChaNoGeneralData.SetCheck(bMemChaNoGeneralData);

	pOptionDlgCharge->m_chkUseDirectDistance.SetCheck(bUseDirectDistance);
	pOptionDlgCharge->m_edtBranchDis.SetWindowText(::GetStringFromLong(nBranchDiscount));
	m_ci.m_nDefaultCharge = nDefaultCharge;
	pOptionDlgCharge->m_strDefaultCharge = GetMyNumberFormat(nDefaultCharge);	 
	pOptionDlgCharge->m_chkDistanceCharge.SetCheck( pOptionDlgCharge->m_bDistanceChargeCheck);
	//pOptionDlgCharge->m_cmbDistanceCharge.EnableWindow( pOptionDlgCharge->m_bDistanceChargeCheck);
	pOptionDlgCharge->m_edtMinCharge.EnableWindow( pOptionDlgCharge->m_bDistanceChargeCheck);

	pOptionDlgCharge->m_cmbDistanceCharge.SetCurSel(pOptionDlgCharge->m_nDistanceCharge);
	//pOptionDlgCharge->m_bD
	//if(pOptionDlgCharge->m_nDistanceCharge == -1)  // 선택거리요금제		
	//	pOptionDlgCharge->m_sDistanceCharge = "선택요금제";
	//else
	//	pOptionDlgCharge->m_sDistanceCharge = itoa(pOptionDlgCharge->m_nDistanceCharge, buffer,10);	

	pOptionDlgCharge->m_strEmergencyCharge.Format("%d", nEmergencyCharge);	
	pOptionDlgCharge->m_chkDongPosLiUse.SetCheck(bDongPosLiUse);

	pOptionDlgCharge->m_chkWeatherCharge.SetCheck(bWeatherCharge);
	pOptionDlgCharge->m_edtBikeWeatherAdd.SetWindowText( ::GetStringFromLong( nBikeWeatherCharge ));
	pOptionDlgCharge->m_edtDamaWeatherAdd.SetWindowText( ::GetStringFromLong( nDamaWeatherCharge ));
	pOptionDlgCharge->m_edtLaboWeatherAdd.SetWindowText( ::GetStringFromLong( nLaboWeatherCharge ));
	pOptionDlgCharge->m_edtVanWeatherAdd.SetWindowText(  ::GetStringFromLong( nVanWeatherCharge	 ));
	pOptionDlgCharge->m_edtTruckWeatherAdd.SetWindowText(::GetStringFromLong( nTruckWeatherCharge));

	pOptionDlgCharge->m_chkWeatherChargeSnow.SetCheck(bWeatherChargeSnow);
	pOptionDlgCharge->m_edtBikeWeatherSnowAdd.SetWindowText( ::GetStringFromLong( nBikeWeatherChargeSnow ));
	pOptionDlgCharge->m_edtDamaWeatherSnowAdd.SetWindowText( ::GetStringFromLong( nDamaWeatherChargeSnow ));
	pOptionDlgCharge->m_edtLaboWeatherSnowAdd.SetWindowText( ::GetStringFromLong( nLaboWeatherChargeSnow ));
	pOptionDlgCharge->m_edtVanWeatherSnowAdd.SetWindowText(  ::GetStringFromLong( nVanWeatherChargeSnow	 ));
	pOptionDlgCharge->m_edtTruckWeatherSnowAdd.SetWindowText(::GetStringFromLong( nTruckWeatherChargeSnow));
	pOptionDlgCharge->m_edtSlowDis.SetWindowText(::GetStringFromLong( nSlowDiscount));

	pOptionDlgCharge->m_chkWeatherChargeAuto.SetCheck(bWeatherChargeAuto);
	pOptionDlgCharge->m_cmbMileageSavingType.SetCurSel(nMileageSavingType);
	
	if(pOptionDlgCharge->m_nMileage == 0)
	{
		pOptionDlgCharge->m_edtMileage.ShowWindow(SW_SHOW);
		pOptionDlgCharge->m_edtMileage.EnableWindow(FALSE);
		pOptionDlgCharge->m_chkMileage.SetCheck(FALSE);
		pOptionDlgCharge->m_btnMileageTerm.ShowWindow(SW_HIDE);
	}
	else
	{
		if(pOptionDlgCharge->m_nMileage == SECTION_MILEAGE)
		{
			pOptionDlgCharge->m_btnMileageTerm.ShowWindow(SW_SHOW);
			pOptionDlgCharge->m_edtMileage.ShowWindow(SW_HIDE);
			pOptionDlgCharge->m_cmbPercent.SetCurSel(2);
		}
		else if(pOptionDlgCharge->m_nMileage == COUNT_MILEAGE)
		{
			pOptionDlgCharge->m_btnMileageTerm.ShowWindow(SW_SHOW);
			pOptionDlgCharge->m_edtMileage.ShowWindow(SW_HIDE);
			pOptionDlgCharge->m_cmbPercent.SetCurSel(3);
		}
		else if(pOptionDlgCharge->m_nMileage > 0) //건당
		{
			pOptionDlgCharge->m_btnMileageTerm.ShowWindow(SW_HIDE);
			pOptionDlgCharge->m_edtMileage.ShowWindow(SW_SHOW);
			pOptionDlgCharge->m_cmbPercent.SetCurSel(0);
			pOptionDlgCharge->m_edtMileage.SetWindowText(ltoa(pOptionDlgCharge->m_nMileage, buffer,10));
			pOptionDlgCharge->m_edtMileage.EnableWindow(TRUE);
		}
		else //퍼센트당
		{ 
			pOptionDlgCharge->m_btnMileageTerm.ShowWindow(SW_HIDE);
			pOptionDlgCharge->m_edtMileage.ShowWindow(SW_SHOW);
			pOptionDlgCharge->m_nMileage = abs(pOptionDlgCharge->m_nMileage);
			pOptionDlgCharge->m_cmbPercent.SetCurSel(1);
			pOptionDlgCharge->m_edtMileage.SetWindowText(ltoa(pOptionDlgCharge->m_nMileage, buffer,10));
			pOptionDlgCharge->m_edtMileage.EnableWindow(TRUE);
		}

		pOptionDlgCharge->m_edtMileageSpan.EnableWindow(TRUE);			
		pOptionDlgCharge->m_edtMileageSpan.SetWindowText(ltoa(pOptionDlgCharge->m_nMileageSpan, buffer,10));
		pOptionDlgCharge->m_chkMileage.SetCheck(TRUE);
		//pOptionDlgGeneral->m_cmbMileageUseType.EnableWindow(TRUE);
	}

 	if(pOptionDlgCharge->m_nMileageTruck == 0)
	{
		pOptionDlgCharge->m_chkMileageTruck.SetCheck(FALSE);
		pOptionDlgCharge->m_edtMileageTruck.SetWindowText("");
	}
	else
	{
		pOptionDlgCharge->m_chkMileageTruck.SetCheck(TRUE);

		if(pOptionDlgCharge->m_nMileageTruck < 0)
			pOptionDlgCharge->m_cmbPercentTruck.SetCurSel(1);
		else
			pOptionDlgCharge->m_cmbPercentTruck.SetCurSel(0);

		pOptionDlgCharge->m_edtMileageTruck.SetWindowText(::GetStringFromLong(abs(pOptionDlgCharge->m_nMileageTruck)));
	}

	pOptionDlgCharge->RefreshSpecialTruckCharge(GetSelCompanyCode());
}

void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgCID*	pOptionDlgCID)
{
	CString strCallingLine;
	long nRevisitCustomerSendDay =0, nRevisitCustomerSendCompany = 0;
	char buffer[10];

	pRs->GetFieldValue("bUseCidPool"		, pOptionDlgCID->m_bUseCidPool);
	pRs->GetFieldValue("bCidNonfixedIntegrationTab", pOptionDlgCID->m_bCidNonfixedIntegrationTab);
	pRs->GetFieldValue("sCallingLine"		, strCallingLine);
	pRs->GetFieldValue("nRevisitCustomerSendDay",nRevisitCustomerSendDay);//,  --   휴면고객 일수 지정
	pRs->GetFieldValue("nRevisitCustomerSendCompany", nRevisitCustomerSendCompany);//   
	if(pOptionDlgCID->m_bUseCidPool)			pOptionDlgCID->m_bUseCidPool = TRUE;
	if(nRevisitCustomerSendDay > 0)
	{
		pOptionDlgCID->m_chkRevisitCustomer.SetCheck(TRUE);
		pOptionDlgCID->m_edtRevisitCustomer.EnableWindow(TRUE);
		pOptionDlgCID->m_cmbRevisitCustomer.EnableWindow(TRUE);
		pOptionDlgCID->m_edtRevisitCustomer.SetWindowText(ltoa(nRevisitCustomerSendDay, buffer,10));

		for(int i =0; i < pOptionDlgCID->m_cmbRevisitCustomer.GetCount(); i++)
		{
			long nCurCompany = pOptionDlgCID->m_cmbRevisitCustomer.GetItemData(i);				
			if( nRevisitCustomerSendCompany == nCurCompany)			
			{					
				pOptionDlgCID->m_cmbRevisitCustomer.SetCurSel(i);
				break;
			}
		}
	}
	else
	{
		pOptionDlgCID->m_chkRevisitCustomer.SetCheck(FALSE);
		pOptionDlgCID->m_edtRevisitCustomer.EnableWindow(FALSE);
		pOptionDlgCID->m_cmbRevisitCustomer.EnableWindow(FALSE);
	}

	pOptionDlgCID->m_strCallingLine = strCallingLine;
	pOptionDlgCID->m_strOriginCallingLine = strCallingLine;

	if(m_ba.GetAt(0)->bIPPBXType)
	{
		pOptionDlgCID->m_chkCompanyCalllingLine.ShowWindow(SW_SHOW);
		pOptionDlgCID->m_stcCalllingLine.ShowWindow(SW_SHOW);
		pOptionDlgCID->m_stcCalllingLine2.ShowWindow(SW_SHOW);
		pOptionDlgCID->m_stcCalllingLine3.ShowWindow(SW_SHOW);
		pOptionDlgCID->m_chkCompanyCalllingLine.SetCheck(FALSE);

		if(strCallingLine.Find("A") != -1 && strCallingLine.Find("B") != -1)
		{
			int nAIndex = strCallingLine.Find("A");
			int nBIndex = strCallingLine.Find("B");
			if(nAIndex < nBIndex)
			{
				pOptionDlgCID->m_strOriginCallingLine = strCallingLine.Left(nAIndex + 1);
				pOptionDlgCID->m_strOriginCallingAuccountDID = strCallingLine.Right(strCallingLine.GetLength() - nAIndex - 1);
			}
			else
				pOptionDlgCID->m_strOriginCallingAuccountDID = "";
		}
		else
			pOptionDlgCID->m_strOriginCallingAuccountDID = "";
	}
}
void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgSMS3*	pOptionDlgSMS3)
{
	long nCompleteSMSType = 0, nAllocateSMS = 0,nAllocateSMSDelay = 0;
	CString sCallBackNumber = "", sCompleteSMSMent ="", sCompleteBannerSMSMent = "";
	BOOL bAllocatedSMSCompanyName = FALSE, bRandomCompanyTel = FALSE;
	BOOL bUseHappyCallCompleted = FALSE, bUseHappyCallCancel = FALSE, bUsePreSms;
	CString sHappyCallMentCancel = "";

	CString strHappyCallMentInquiryToday, strPreSmsMent;
	long nHappyCallDelayInquiryToday;
	long nHappyCallDelayCancelToday;

	long nPreSmsDay, nPreSmsTerm, nPreSmsSendTime, nHappyCallDelayCompletedToday;

	// 배차관련
	pRs->GetFieldValue("bAllocateCustomerSMS", nAllocateSMS);
	pRs->GetFieldValue("bAllocatedSMSCompanyName",bAllocatedSMSCompanyName );
	pRs->GetFieldValue("nAllocateSMSDelay"	, nAllocateSMSDelay);
	pRs->GetFieldValue("bUseCancelSMS"		, pOptionDlgSMS3->m_bUseCancelSMS);
	pRs->GetFieldValue("sCancelSMSText"		, pOptionDlgSMS3->m_strCancelSMSText);		
	pRs->GetFieldValue("BankAccountSMS", pOptionDlgSMS3->m_strBankAccountSMS);
	pRs->GetFieldValue("bRandomCompanyTel",bRandomCompanyTel );
	pRs->GetFieldValue("sAllocateCustomerSMS", pOptionDlgSMS3->m_strAllocateCustomerSms);
	//pRs->GetFieldValue("sCompleteSMS", pOptionDlgSMS3->m_sCompleteSms);
	pRs->GetFieldValue("sAllocateSMSF", pOptionDlgSMS3->m_strAllocateSmsFType); 
	pRs->GetFieldValue("bUseHappyCallInquiry", pOptionDlgSMS3->m_bUseHappyCallInquiry); 
	pRs->GetFieldValue("dtHappyCallInquiry", pOptionDlgSMS3->m_dtHappyCallInquiry); 
	pRs->GetFieldValue("sHappyCallMentInquiry", pOptionDlgSMS3->m_strHappyCallMentInquiry); 
	pRs->GetFieldValue("bPickupSms", pOptionDlgSMS3->m_bPickupSms); 
	pRs->GetFieldValue("sPickupSms", pOptionDlgSMS3->m_strPickupSms); 
	pRs->GetFieldValue("bPickupSms2", pOptionDlgSMS3->m_bPickupSms2); 
	pRs->GetFieldValue("sPickupSms2", pOptionDlgSMS3->m_strPickupSms2); 

	pRs->GetFieldValue("bUseHappyCallCompleted",	bUseHappyCallCompleted); 
	pRs->GetFieldValue("dtHappyCallCompleted",		pOptionDlgSMS3->m_dtHappyCallCompleted); 
	pRs->GetFieldValue("bUseHappyCallCancel",		bUseHappyCallCancel); 
	pRs->GetFieldValue("dtHappyCallCancel",			pOptionDlgSMS3->m_dtHappyCallCancel); 
	pRs->GetFieldValue("sHappyCallMentCancel",		sHappyCallMentCancel); 
	pRs->GetFieldValue("sCompanyAppUrl",		pOptionDlgSMS3->m_strCompanyAppUrl); 
	pRs->GetFieldValue("sCompanyHomePage",		pOptionDlgSMS3->m_strCompanyHomePage); 
	pRs->GetFieldValue("sCompanyLogoImage",		pOptionDlgSMS3->m_strCompanyLogoImage); 
	if(!m_bLogView)
	{
		pRs->GetFieldValue("nHappyCallDelayCompletedToday",		nHappyCallDelayCompletedToday); 
	}
	else 
		nHappyCallDelayCompletedToday = 0;
			 
	if(nAllocateSMS == 1) {
		pOptionDlgSMS3->m_bSMSOfRider = TRUE; 
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = FALSE;
	}
	else if(nAllocateSMS == 2) {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = TRUE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = FALSE;
	}
	else if(nAllocateSMS == 3) {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = TRUE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = FALSE;
	}
	else if(nAllocateSMS == 4) {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = TRUE;
		pOptionDlgSMS3->m_bSaveMent = FALSE;
	}
	else if(nAllocateSMS == 5) {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = TRUE;
		pOptionDlgSMS3->m_rdoCompanyPhone.SetCheck(TRUE);
		pOptionDlgSMS3->m_rdoRiderPhone.SetCheck(FALSE);
	}
	else if(nAllocateSMS == 6) {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = TRUE;
		pOptionDlgSMS3->m_rdoCompanyPhone.SetCheck(FALSE);
		pOptionDlgSMS3->m_rdoRiderPhone.SetCheck(TRUE);
	}
	else {
		pOptionDlgSMS3->m_bSMSOfRider = FALSE;
		pOptionDlgSMS3->m_bSMSOfCompany = FALSE;
		pOptionDlgSMS3->m_bSMSOfIns = FALSE;
		pOptionDlgSMS3->m_bSMSOfInsRider = FALSE;
		pOptionDlgSMS3->m_bSaveMent = FALSE;
		pOptionDlgSMS3->m_rdoCompanyPhone.SetCheck(FALSE);
		pOptionDlgSMS3->m_rdoRiderPhone.SetCheck(FALSE);
	}

	if(bAllocatedSMSCompanyName) 	//배차된 고객SMS 전송회사(회사명 = 1 default,지사명)	
	{
		pOptionDlgSMS3->m_rdoSMSSendCompanyName.SetCheck(TRUE);
		pOptionDlgSMS3->m_rdoSMSSendBranchName.SetCheck(FALSE); 
	}
	else
	{
		pOptionDlgSMS3->m_rdoSMSSendCompanyName.SetCheck(FALSE);
		pOptionDlgSMS3->m_rdoSMSSendBranchName.SetCheck(TRUE); 
	}
	pOptionDlgSMS3->m_AllocateSMSDelayCombo.SetCurSel(nAllocateSMSDelay);
	pOptionDlgSMS3->m_bUseCancelSMS = pOptionDlgSMS3->m_bUseCancelSMS;

	if(bRandomCompanyTel) 	//배차된 고객SMS 전송회사(회사명 = 1 default,지사명)	
	{
		pOptionDlgSMS3->m_rdoRandomCompanyTel.SetCheck(TRUE);
		pOptionDlgSMS3->m_rdoRandomOfficeTel.SetCheck(FALSE); 
	}
	else
	{
		pOptionDlgSMS3->m_rdoRandomCompanyTel.SetCheck(FALSE);
		pOptionDlgSMS3->m_rdoRandomOfficeTel.SetCheck(TRUE); 
	}
	
	// 종료관련
	pRs->GetFieldValue("nCompleteSMSType", nCompleteSMSType);
	pRs->GetFieldValue("sCompleteSMSMent",pOptionDlgSMS3->m_sCompleteSms);
	pRs->GetFieldValue("sCompleteBannerSMSMent",pOptionDlgSMS3->m_sCompleteBannerSms);
	pRs->GetFieldValue("bSCSFRC", pOptionDlgSMS3->m_bSendCompleteSmsForRiderComplete);	
	if(nCompleteSMSType == 1) 
	{
		pOptionDlgSMS3->m_bSmsOfRiderName = TRUE;
		pOptionDlgSMS3->m_bSmsOfDt1 = FALSE;
		pOptionDlgSMS3->m_bSmsOfBanner = FALSE;
		pOptionDlgSMS3->m_bSmsOfEtc = FALSE;		
	}
	else if(nCompleteSMSType == 2)
	{
		pOptionDlgSMS3->m_bSmsOfRiderName = FALSE;
		pOptionDlgSMS3->m_bSmsOfDt1 = TRUE;
		pOptionDlgSMS3->m_bSmsOfBanner = FALSE;
		pOptionDlgSMS3->m_bSmsOfEtc = FALSE;
	}
	else if(nCompleteSMSType == 3)
	{

		pOptionDlgSMS3->m_bSmsOfRiderName = FALSE;
		pOptionDlgSMS3->m_bSmsOfDt1 = FALSE;
		pOptionDlgSMS3->m_bSmsOfBanner = FALSE;
		pOptionDlgSMS3->m_bSmsOfEtc = TRUE;
	}
	else if(nCompleteSMSType == 4)
	{
		pOptionDlgSMS3->m_bSmsOfRiderName = FALSE;
		pOptionDlgSMS3->m_bSmsOfDt1 = FALSE;
		pOptionDlgSMS3->m_bSmsOfBanner = TRUE;
		pOptionDlgSMS3->m_bSmsOfEtc = FALSE;
	}
	else
	{
		pOptionDlgSMS3->m_bSmsOfRiderName = FALSE;
		pOptionDlgSMS3->m_bSmsOfDt1 = FALSE;
		pOptionDlgSMS3->m_bSmsOfBanner = FALSE;
		pOptionDlgSMS3->m_bSmsOfEtc = FALSE;
	}
	//pOptionDlgSMS3->m_edtCompleteBannerSms.SetWindowText(sCompleteBannerSMSMent);
	//pOptionDlgSMS3->m_CompleteSmsEdt.SetWindowText(sCompleteSMSMent);
	//pOptionDlgSMS3->m_chkSendCompleteSmsForRiderComplete.SetCheck();
	pOptionDlgSMS3->m_bSendCompleteSmsForRiderComplete	;

	pRs->GetFieldValue("bUseHappyCallCompleted",	bUseHappyCallCompleted); 
	pRs->GetFieldValue("dtHappyCallCompleted",		pOptionDlgSMS3->m_dtHappyCallCompleted); 
	pRs->GetFieldValue("bUseHappyCallCancel",		bUseHappyCallCancel); 
	pRs->GetFieldValue("dtHappyCallCancel",			pOptionDlgSMS3->m_dtHappyCallCancel); 
	pRs->GetFieldValue("sHappyCallMentCancel",		sHappyCallMentCancel); 

	pOptionDlgSMS3->m_chkUseHappyCallCompleted.SetCheck(bUseHappyCallCompleted);
	pOptionDlgSMS3->m_dtpHappyCallCompleted.EnableWindow(bUseHappyCallCompleted);
	pOptionDlgSMS3->m_dtpHappyCallInquery.EnableWindow(pOptionDlgSMS3->m_bUseHappyCallInquiry);


	// 취소관련
	pOptionDlgSMS3->m_chkUseHappyCallCancel.SetCheck(bUseHappyCallCancel);
	pOptionDlgSMS3->m_dtpHappyCallCancel.EnableWindow(bUseHappyCallCancel);	 
	pOptionDlgSMS3->m_edtHappyCallMentCancel.SetWindowText(
		bUseHappyCallCancel == FALSE ? "" : sHappyCallMentCancel);

	pRs->GetFieldValue("bUseHappyInquiryToday",	pOptionDlgSMS3->m_bUseHappyCallInquiryToday); 
	pRs->GetFieldValue("sHappyCallMentInquiryToday", pOptionDlgSMS3->m_strHappyCallMentInquiryToday); 
	pRs->GetFieldValue("nHappyCallDelayInquiryToday", nHappyCallDelayInquiryToday); 
	
	pOptionDlgSMS3->m_cmbHappyCallDelayInquiryToday.SetWindowText(::GetStringFromLong(nHappyCallDelayInquiryToday));

	pRs->GetFieldValue("bUseHappyCancelToday",	pOptionDlgSMS3->m_bUseHappyCallCancelToday); 
	pRs->GetFieldValue("sHappyCallMentCancelToday", pOptionDlgSMS3->m_strHappyCallMentCancelToday); 
	pRs->GetFieldValue("nHappyCallDelayCancelToday", nHappyCallDelayCancelToday); 

	pOptionDlgSMS3->m_cmbHappyCallDelayCancelToday.SetWindowText(::GetStringFromLong(nHappyCallDelayCancelToday));
		
	
	// 기사개별
	pRs->GetFieldValue("bSendOnePage", pOptionDlgSMS3->m_bSendOnePage);
	pRs->GetFieldValue("nAllocateSMSType", pOptionDlgSMS3->m_nAllocateSMSType);
	pRs->GetFieldValue("sCallBackNumber", sCallBackNumber);

	pOptionDlgSMS3->m_chkSendOnePage.SetCheck(pOptionDlgSMS3->m_bSendOnePage);
	pOptionDlgSMS3->m_AllocateSmsTypeCmb.SetCurSel(pOptionDlgSMS3->m_nAllocateSMSType);
	pOptionDlgSMS3->m_cmbFirstPage.SetCurSel(atoi(sCallBackNumber.Left(1)));
	pOptionDlgSMS3->m_cmbSecondPage.SetCurSel(atoi(sCallBackNumber.Mid(2,1)));
	pOptionDlgSMS3->m_cmbThirdPage.SetCurSel(atoi(sCallBackNumber.Mid(4, 1)));

	//이전사용고객
	pRs->GetFieldValue("bUsePreSms", bUsePreSms);
	pRs->GetFieldValue("nPreSmsDay", nPreSmsDay);
	pRs->GetFieldValue("nPreSmsTerm", nPreSmsTerm);
	pRs->GetFieldValue("sPreSmsMent", strPreSmsMent);
	pRs->GetFieldValue("nPreSmsSendTime", nPreSmsSendTime);

	pOptionDlgSMS3->m_chkUsePreSms.SetCheck(bUsePreSms);
	pOptionDlgSMS3->SqlDayToCombo(&pOptionDlgSMS3->m_cmbPreSmsDay, nPreSmsDay);
	pOptionDlgSMS3->m_cmbPreSmsTerm.SetCurSel(max(nPreSmsTerm - 1, 0));
	pOptionDlgSMS3->m_edtPreSmsMent.SetWindowText(strPreSmsMent);
	pOptionDlgSMS3->m_cmbPreSmsSendTime.SetCurSel(max(nPreSmsSendTime - 9, 0));
 
	pOptionDlgSMS3->InitControl();			

	pOptionDlgSMS3->m_cmbCompleteSmsDelay.SetWindowText(::GetStringFromLong(nHappyCallDelayCompletedToday));
}


void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs, COptionDlgSmartQ* pOptionSmartQ)
{
	BOOL bUseSmartQuick, bAbleSmartQuickCancel, bSendSmartQMent, bUseRcpTime;
	CString strSendSmartQMent;
	long nRcpTimeStart, nRcpTimeEnd;

	// 인터콜관련	
	pRs->GetFieldValue("bUseSmartQuick", bUseSmartQuick);	
	pRs->GetFieldValue("bAbleSmartQuickCancel", bAbleSmartQuickCancel); 
	pRs->GetFieldValue("bSendSmartQMent", bSendSmartQMent);	
	pRs->GetFieldValue("sSendSmartQMent", strSendSmartQMent); 
	pRs->GetFieldValue("bUseRcpTime", bUseRcpTime); 
	pRs->GetFieldValue("nRcpTimeStart", nRcpTimeStart); 
	pRs->GetFieldValue("nRcpTimeEnd", nRcpTimeEnd); 
	
	pOptionSmartQ->m_chkUseSmartQuick.SetCheck(bUseSmartQuick);
	pOptionSmartQ->m_chkAbleSmartQuickCancel.SetCheck(bAbleSmartQuickCancel);
	pOptionSmartQ->m_chkSendSmartQMent.SetCheck(bSendSmartQMent);
	pOptionSmartQ->m_edtSmartQMent.SetWindowText(strSendSmartQMent);
	pOptionSmartQ->m_chkUseRcpTimeCheck.SetCheck(bUseRcpTime);
	pOptionSmartQ->m_cmbRcpTimeStart.SetCurSel(nRcpTimeStart);
	pOptionSmartQ->m_cmbRcpTimeEnd.SetCurSel(nRcpTimeEnd);
}


void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgInterCall2*	pOptionDlgInterCall2)
{
	char buffer[10];
	BOOL bwebUseMileage, bwebUseBBS,bwebMustOnlinePay, bWebInternetCardNotUse,bNonActiveInercall,
		bwebUseChargeList, bwebUseCouphon, bwebUseOnLinePay, bwebUseInnerFrame, bSettlementTax, 
		bEtcIntercallCopy, bChargeAddDisView = FALSE, bInterCallRiderPhoneView = FALSE;


	long	nwebChargeTypeValue = 0,nwebWayAddAmount = 0,nwebRunAddAmount = 0, nSlowCharge= 0,
		nInterCallNotViewAmount = 0;
	long nReceiptType = 0, nWebReceiptStateType = 0, nInterCallReceiptStateType = 0;
	CString	swebOnlineID, swebAddress,sFramBgColor, sFrameFontColor, sNightReceiptCallSMS;
	CString sAccountInfo, sAccountInfoOwner, sNonActiveReason;
	

	// 인터콜관련	
	pRs->GetFieldValue("nCompanyWorking", pOptionDlgInterCall2->m_bCompanyWorking);	
	pRs->GetFieldValue("nICMapDisplayType",pOptionDlgInterCall2->m_bICDisplayType); 
	pRs->GetFieldValue("bICTransOpen", pOptionDlgInterCall2->m_bTransOpen); 	
	pRs->GetFieldValue("bUseSlowOrder", pOptionDlgInterCall2->m_bUseSlowOrder);
	pRs->GetFieldValue("sSlowMsg", pOptionDlgInterCall2->m_strSlowMsg);
	pRs->GetFieldValue("nICChargeOpenType", pOptionDlgInterCall2->m_nChargeOpenType); 
	pRs->GetFieldValue("sICDisplayName", pOptionDlgInterCall2->m_sICDisplayName);	

	pRs->GetFieldValue("sICName", pOptionDlgInterCall2->m_strIntercallName);	

	pRs->GetFieldValue("sBanner", pOptionDlgInterCall2->m_sICBanner);	
	pRs->GetFieldValue("nSlowCharge", nSlowCharge);
	pRs->GetFieldValue("bEtcIntercallCopy", bEtcIntercallCopy);	
	//pRs->GetFieldValue("bIntercallChargeAddDisView",bIntercallChargeAddDisView );	
	pRs->GetFieldValue("nInterCallNotViewAmount",nInterCallNotViewAmount );	
	pRs->GetFieldValue("bInterCallRiderPhoneView",bInterCallRiderPhoneView );	
	
	
	
	pOptionDlgInterCall2->m_chkInterCallRiderPhoneView.SetCheck(bInterCallRiderPhoneView);
	
	pOptionDlgInterCall2->m_cmbIntercallNotViewAmount.SetCurSel(nInterCallNotViewAmount);
	pOptionDlgInterCall2->m_strSlowCharge = itoa(nSlowCharge, buffer, 10);	
	pOptionDlgInterCall2->m_SlowChargeEdit.EnableWindow(!pOptionDlgInterCall2->m_bUseSlowOrder);
	pOptionDlgInterCall2->m_SlowMsgEdit.SetReadOnly(!pOptionDlgInterCall2->m_bUseSlowOrder);
	pOptionDlgInterCall2->m_chkEtcInterCallCopy.SetCheck( bEtcIntercallCopy);
	

	
	//  web 관련
	pRs->GetFieldValue("bwebUseMileage", bwebUseMileage);
	pRs->GetFieldValue("bwebUseChargeList",bwebUseChargeList);
	pRs->GetFieldValue("bwebUseCouphon",bwebUseCouphon);
	pRs->GetFieldValue("bwebUseOnLinePay", bwebUseOnLinePay);		
	pRs->GetFieldValue("bwebMustOnlinePay", bwebMustOnlinePay);		
	pRs->GetFieldValue("swebAddress", swebAddress);		
	pRs->GetFieldValue("bwebUseBBS",bwebUseBBS);
	pRs->GetFieldValue("bwebUseInnerFrame", bwebUseInnerFrame);			
	pRs->GetFieldValue("sFrameBgColor", sFramBgColor);		
	pRs->GetFieldValue("sFrameFontColor", sFrameFontColor);	
	pRs->GetFieldValue("bSettlementTax", bSettlementTax);	
	pRs->GetFieldValue("bWebInternetCardNotUse", bWebInternetCardNotUse);	
	pRs->GetFieldValue("nWebReceiptStateType", nWebReceiptStateType);
	pRs->GetFieldValue("nInterCallReceiptStateType", nInterCallReceiptStateType);
	pRs->GetFieldValue("sNightReceiptCallSMS", sNightReceiptCallSMS);	

	// 공통
	pRs->GetFieldValue("bNonActiveInercall", bNonActiveInercall);	
	pRs->GetFieldValue("sNonActiveReason", sNonActiveReason);		

	pRs->GetFieldValue("nReceiptType", nReceiptType);	
	pRs->GetFieldValue("sAccountInfo", sAccountInfo);	
	pRs->GetFieldValue("sAccountInfoOwner", sAccountInfoOwner);	


	pOptionDlgInterCall2->m_chkReceiptStop.SetCheck(bNonActiveInercall);
	pOptionDlgInterCall2->m_edtReciptStop.SetWindowText(sNonActiveReason);
	pOptionDlgInterCall2->m_cmbWebReceiptState.SetCurSel(nWebReceiptStateType);
	pOptionDlgInterCall2->m_cmbInterCallReceiptState.SetCurSel(nInterCallReceiptStateType);
	
	pOptionDlgInterCall2->m_edtAccountInfo.SetWindowText(sAccountInfo);
	pOptionDlgInterCall2->m_edtAccountInfoOwner.SetWindowText(sAccountInfoOwner);

	pOptionDlgInterCall2->m_chkMileage.SetCheck(bwebUseMileage);
	pOptionDlgInterCall2->m_chkChargeListUse.SetCheck(bwebUseChargeList);
	pOptionDlgInterCall2->m_chkCouphonUse.SetCheck(bwebUseCouphon);
	

	
	pOptionDlgInterCall2->m_edtWebAddress.SetWindowText(swebAddress);
	pOptionDlgInterCall2->m_chkBBSUse.SetCheck(bwebUseBBS);
	
		pOptionDlgInterCall2->m_chkOnLinePayUse.EnableWindow(bwebUseOnLinePay);
		pOptionDlgInterCall2->m_chkPayMent.EnableWindow(bwebUseOnLinePay);
		pOptionDlgInterCall2->m_chkSettleMentTax.EnableWindow(bwebUseOnLinePay);
		pOptionDlgInterCall2->m_chkInternetCardNotUse.EnableWindow(bwebUseOnLinePay);
	
		pOptionDlgInterCall2->m_chkPayMent.SetCheck(bwebMustOnlinePay);
		pOptionDlgInterCall2->m_chkOnLinePayUse.SetCheck(bwebUseOnLinePay);
		pOptionDlgInterCall2->m_chkInternetCardNotUse.SetCheck(bWebInternetCardNotUse);
		pOptionDlgInterCall2->m_chkSettleMentTax.SetCheck(bSettlementTax);


	pOptionDlgInterCall2->m_chkInnerFrameUse.SetCheck(bwebUseInnerFrame);
	pOptionDlgInterCall2->m_edtFontColor.EnableWindow(bwebUseInnerFrame);
	pOptionDlgInterCall2->m_edtBgColor.EnableWindow(bwebUseInnerFrame);
	pOptionDlgInterCall2->m_btnBgColor.EnableWindow(bwebUseInnerFrame);
	pOptionDlgInterCall2->m_btnFontColor.EnableWindow(bwebUseInnerFrame);
	pOptionDlgInterCall2->m_edtNightReceiptCallSMS.SetWindowText(sNightReceiptCallSMS);
	
	
	if(bwebUseInnerFrame && 
		(sFramBgColor.GetLength() >= 6 || sFrameFontColor.GetLength() >= 6 ) )
	{
		long R, G, B;
		CString sR, sG, sB, sHex = "0x";

		char *buffer;
		pOptionDlgInterCall2->m_edtBgColor.SetWindowText(sFramBgColor);
		if(sFramBgColor.GetLength() > 0)
		{
			sFramBgColor.Replace("#", "");

			sR =  sFramBgColor.Left(2);
			R = strtol(sR, &buffer,16);								
			sG = sFramBgColor.Mid(2,2);
			G = strtol(sG, &buffer,16);						
			sB = sFramBgColor.Right(2);
			B = strtol(sB, &buffer,16);

			pOptionDlgInterCall2->m_btnBgColor.SetColor(RGB(R,G,B));


		}
		pOptionDlgInterCall2->m_edtFontColor.SetWindowText(sFrameFontColor);
		if(sFrameFontColor.GetLength() > 0)
		{
			sFrameFontColor.Replace("#", "");

			sR =  sFramBgColor.Left(2);
			R = strtol(sR, &buffer,16);								
			sG = sFramBgColor.Mid(2,2);
			G = strtol(sG, &buffer,16);						
			sB = sFramBgColor.Right(2);
			B = strtol(sB, &buffer,16);

			pOptionDlgInterCall2->m_btnFontColor.SetColor(RGB(R,G,B));
		}
	}
	else
	{
		pOptionDlgInterCall2->m_btnBgColor.SetColor(RGB(255,95,65));
		pOptionDlgInterCall2->m_edtBgColor.SetWindowText("#00feff");
		pOptionDlgInterCall2->m_btnFontColor.SetColor(RGB(255,255,255));
		pOptionDlgInterCall2->m_edtBgColor.SetWindowText("#ffffff");
		//OptionDlgInterCall2->m_edt

	}
	
	pOptionDlgInterCall2->OnBnClickedSlowOrderCheck();


	if(nReceiptType == 100)
		pOptionDlgInterCall2->m_cmbReceiptType.SetCurSel(pOptionDlgInterCall2->m_cmbReceiptType.GetCount() -1);
	else
		pOptionDlgInterCall2->m_cmbReceiptType.SetCurSel(nReceiptType);

	

}

void CMainOptionDlg2::OptionControlApply(CMkRecordset *pRs,COptionDlgMobileNew *pOptionDlgMobileNew)
{
	char buffer[10];
	long nMinCompleteTime;
	long nMaxCharge;
	long nMaxSelectCount;

	long nWorkReportCharge, nCancelPenaltyCharge;
	long nMaxDistance, nMaxNearOrder, nAllocateLimitTime;
	nMaxDistance = nMaxNearOrder = nAllocateLimitTime = 0;
	int nClassViewByUseCount, nViaAmount = 0;
	BOOL  bInstantAllocate, bTwoStateAlloc, bDistanceChargeCheck;

	CString sClassViewByUseCount;
	long nSortType;
	long nAARange;

	long	nwebChargeTypeValue = 0,nwebWayAddAmount = 0,nwebRunAddAmount = 0;
	CString	swebOnlineID, swebAddress,sFramBgColor, sFrameFontColor;


	UpdateData();
	// 모바일
	pRs->GetFieldValue("bDestDisplay"	, pOptionDlgMobileNew->m_bDestDisplay);
	pRs->GetFieldValue("nSortType", nSortType);		
	pRs->GetFieldValue("sDestViewTime"		, pOptionDlgMobileNew->m_sDestViewTime);
	pRs->GetFieldValue("bHideClientMultiple"	, pOptionDlgMobileNew->m_bHideClientMultiple);
	pRs->GetFieldValue("bHideClientSection"	, pOptionDlgMobileNew->m_bHideClientSection);
	pRs->GetFieldValue("bEnableCancel"	,		pOptionDlgMobileNew->m_bEnableCancel);
	pRs->GetFieldValue("bCheckInsurance"	,	pOptionDlgMobileNew->m_bInsureLimit);
	pRs->GetFieldValue("bLimitTodayCharge",	pOptionDlgMobileNew->m_bChargeLimit);	
	pRs->GetFieldValue("bWapDisable"			, pOptionDlgMobileNew->m_bWapDisable);
	pRs->GetFieldValue("bNotCompletedLimit",pOptionDlgMobileNew->m_bNotCompletedLimit);
	pRs->GetFieldValue("bChkWorkReport"		, pOptionDlgMobileNew->m_bWorkReport);
	pRs->GetFieldValue("bUsePickupCall"		, pOptionDlgMobileNew->m_bUsePickupCall);
	pRs->GetFieldValue("bSupportableCall"	, pOptionDlgMobileNew->m_bSupportableCall);
	pRs->GetFieldValue("bDistanceCharge"	, bDistanceChargeCheck);	
	pRs->GetFieldValue("nMaxTodayCharge", nMaxCharge);		
	pRs->GetFieldValue("nMinCompleteTime", nMinCompleteTime);				
	pRs->GetFieldValue("nMaxSelectCount"		, nMaxSelectCount);		
	pRs->GetFieldValue("nCancelPenaltyCharge", nCancelPenaltyCharge);		
	pRs->GetFieldValue("nWorkReportCharge"	, nWorkReportCharge);		
	pRs->GetFieldValue("bTwoStateAlloc"		, bTwoStateAlloc);   //배차방식관련
	pRs->GetFieldValue("bInstantAllocate"	, bInstantAllocate);  // 즉시배차
	pRs->GetFieldValue("nInstantLimitTime"	, nAllocateLimitTime);
	pRs->GetFieldValue("bUseNewRegion"		, pOptionDlgMobileNew->m_bUseNewRegion);
	pRs->GetFieldValue("nClientOrderRangeKM"	, pOptionDlgMobileNew->m_nDistanceAllocate);
	pRs->GetFieldValue("nClientOrderMaxCount", nMaxNearOrder);
	pRs->GetFieldValue("bNationalCallCenter"	, pOptionDlgMobileNew->m_bNationalCallcenter);		
	pRs->GetFieldValue("bUseNewRegionAllDong", pOptionDlgMobileNew->m_bUseNewRegionAllDong);		
	pRs->GetFieldValue("bCustPhoneHide"		, pOptionDlgMobileNew->m_bCustPhoneHide);					
	pRs->GetFieldValue("bNotDisplayTotalOrder",pOptionDlgMobileNew->m_bNotAllOrderView);		
	pRs->GetFieldValue("nViewOrderRangeKM",nMaxDistance);
	pRs->GetFieldValue("nClassViewByUseCount", nClassViewByUseCount);			
	pRs->GetFieldValue("bIgnoreShowOnlyMyCompanyOrder", pOptionDlgMobileNew->m_bPreventShowOnlyMyCompanyOrder);
	pRs->GetFieldValue("bIgnoreRiderKM", pOptionDlgMobileNew->m_bIgnoreRiderKM);
	pRs->GetFieldValue("bNeedSignForComplete", pOptionDlgMobileNew->m_bNeedSignForComplete);
	pRs->GetFieldValue("bIgnoreRiderPermitCarType", pOptionDlgMobileNew->m_bIgnoreRiderPermitCarType);
	pRs->GetFieldValue("bIgnoreRiderCharge", pOptionDlgMobileNew->m_bIgnoreRiderCharge);
	pRs->GetFieldValue("bIgnoreRiderStart", pOptionDlgMobileNew->m_bIgnoreRiderStart);
	pRs->GetFieldValue("bIgnoreRiderDest", pOptionDlgMobileNew->m_bIgnoreRiderDest);
	pRs->GetFieldValue("nAARange", nAARange);

	if(!m_bLogView)
		pRs->GetFieldValue("bAutoWaitOnce", pOptionDlgMobileNew->m_bAutoWaitOnce);
	
	if(pOptionDlgMobileNew->m_bPreventShowOnlyMyCompanyOrder) pOptionDlgMobileNew->m_bPreventShowOnlyMyCompanyOrder = TRUE;
	pOptionDlgMobileNew->m_chkPreventShowOnlyMyCompanyOrder.SetCheck(pOptionDlgMobileNew->m_bPreventShowOnlyMyCompanyOrder );

	if(pOptionDlgMobileNew->m_bIgnoreRiderKM) pOptionDlgMobileNew->m_bIgnoreRiderKM = TRUE;
	pOptionDlgMobileNew->m_chkIgnoreRiderKM.SetCheck(pOptionDlgMobileNew->m_bIgnoreRiderKM);

	if(pOptionDlgMobileNew->m_bDestDisplay) pOptionDlgMobileNew->m_bDestDisplay = TRUE;	
	if(pOptionDlgMobileNew->m_bEnableCancel) pOptionDlgMobileNew->m_bEnableCancel = TRUE;
	if(pOptionDlgMobileNew->m_bInsureLimit)  pOptionDlgMobileNew->m_bInsureLimit = TRUE;
	if(pOptionDlgMobileNew->m_bChargeLimit)  pOptionDlgMobileNew->m_bChargeLimit = TRUE;
	if(pOptionDlgMobileNew->m_bNotCompletedLimit) pOptionDlgMobileNew->m_bNotCompletedLimit = TRUE;

	if(pOptionDlgMobileNew->m_bHideClientMultiple)pOptionDlgMobileNew->m_bHideClientMultiple = TRUE;
	if(pOptionDlgMobileNew->m_bHideClientSection) pOptionDlgMobileNew->m_bHideClientSection = TRUE;
	if(pOptionDlgMobileNew->m_bWapDisable)		pOptionDlgMobileNew->m_bWapDisable = TRUE;
	if(pOptionDlgMobileNew->m_bWorkReport)		pOptionDlgMobileNew->m_bWorkReport = TRUE;	
	if(bTwoStateAlloc) bTwoStateAlloc = TRUE;	


	if(bInstantAllocate) 
	{			
		pOptionDlgMobileNew->m_strAllocateLimitTime = itoa(nAllocateLimitTime,buffer,10);
		pOptionDlgMobileNew->m_cmbAllocateMethod.SetCurSel(2);
		pOptionDlgMobileNew->m_edtAllocateLimitTime.EnableWindow(TRUE);
	}
	else
	{
		if(bTwoStateAlloc)
			pOptionDlgMobileNew->m_cmbAllocateMethod.SetCurSel(1);			
		else
			pOptionDlgMobileNew->m_cmbAllocateMethod.SetCurSel(0);
		
		pOptionDlgMobileNew->m_edtAllocateLimitTime.EnableWindow(FALSE);
	}

	if(pOptionDlgMobileNew->m_bUsePickupCall)		pOptionDlgMobileNew->m_bUsePickupCall = TRUE;
	if(pOptionDlgMobileNew->m_bSupportableCall)	pOptionDlgMobileNew->m_bSupportableCall = TRUE;
	//if(pOptionDlgCID->m_bCidNonfixedIntegrationTab) pOptionDlgCID->m_bCidNonfixedIntegrationTab = TRUE;

	if(pOptionDlgMobileNew->m_bUseNewRegionAllDong) pOptionDlgMobileNew->m_bUseNewRegionAllDong = TRUE;
	if(pOptionDlgMobileNew->m_bCustPhoneHide) pOptionDlgMobileNew->m_bCustPhoneHide = TRUE;
	pOptionDlgMobileNew->m_edtClassViewByUseCount.EnableWindow(pOptionDlgMobileNew->m_bCustPhoneHide);

	if(pOptionDlgMobileNew->m_bNotAllOrderView) pOptionDlgMobileNew->m_bNotAllOrderView = TRUE;
	if(pOptionDlgMobileNew->m_bDestDisplay)
	{
		pOptionDlgMobileNew->m_chkDestViewTime.EnableWindow(TRUE);			
		pOptionDlgMobileNew->m_dtpFromDestView.EnableWindow(TRUE);
		
		if(pOptionDlgMobileNew->m_sDestViewTime.GetLength() > 0) 
		{
			pOptionDlgMobileNew->m_bDestViewTime = TRUE;
			COleDateTime dt(COleDateTime::GetCurrentTime());
			pOptionDlgMobileNew->m_dtFromDestView.SetDateTime(dt.GetYear(),dt.GetMonth(),dt.GetDay(),
					atoi(pOptionDlgMobileNew->m_sDestViewTime.Left(2)), atoi(pOptionDlgMobileNew->m_sDestViewTime.Mid(3,2)),0);				
		}
		else
		{
			pOptionDlgMobileNew->m_dtpFromDestView.EnableWindow(FALSE);				
		}
	}
	else
	{
		pOptionDlgMobileNew->m_chkDestViewTime.EnableWindow(FALSE);
		pOptionDlgMobileNew->m_bDestViewTime = FALSE;			
		pOptionDlgMobileNew->m_dtpFromDestView.EnableWindow(FALSE);		
	}


	if(nMaxSelectCount == 0) nMaxSelectCount = 4;

	pOptionDlgMobileNew->m_strMaxCharge.Format("%d", nMaxCharge);
	pOptionDlgMobileNew->m_strMinCompleteTime.Format("%d", nMinCompleteTime);
	pOptionDlgMobileNew->m_RegionCountCombo.SetCurSel(nMaxSelectCount - 1);		
	pOptionDlgMobileNew->m_strWorkReportCharge.Format("%d", nWorkReportCharge);
	pOptionDlgMobileNew->m_SortTypeCombo.SetCurSel(nSortType);
	pOptionDlgMobileNew->m_sClassViewByUseCount = itoa(nClassViewByUseCount,buffer,10);

	if (pOptionDlgMobileNew->m_bUseNewRegion != 0) {
		pOptionDlgMobileNew->m_bUseNewRegion = 1;
		pOptionDlgMobileNew->m_chkUseNewRegion.SetCheck(1);
		pOptionDlgMobileNew->m_editMaxDistance.EnableWindow(TRUE);
		pOptionDlgMobileNew->m_editMaxNearOrder.EnableWindow(TRUE);
		pOptionDlgMobileNew->m_chkUseNewRegionAllDong.EnableWindow(TRUE);
		//m_chkNationalCallcenter.EnableWindow(TRUE);
		pOptionDlgMobileNew->m_strMaxDistance.Format("%d", nMaxDistance);
		pOptionDlgMobileNew->m_strMaxNearOrder.Format("%d", nMaxNearOrder);
		pOptionDlgMobileNew->m_editMaxDistance.SetWindowText(pOptionDlgMobileNew->m_strMaxDistance);
		pOptionDlgMobileNew->m_editMaxNearOrder.SetWindowText(pOptionDlgMobileNew->m_strMaxNearOrder);

		pOptionDlgMobileNew->m_chkNotAllView.EnableWindow(TRUE);
		if(pOptionDlgMobileNew->m_bNotAllOrderView)
			pOptionDlgMobileNew->m_edtDistanceAllocate.EnableWindow(TRUE);
		else
			pOptionDlgMobileNew->m_edtDistanceAllocate.EnableWindow(FALSE);


		if (pOptionDlgMobileNew->m_bNationalCallcenter != 0) {
			pOptionDlgMobileNew->m_bNationalCallcenter = 1;
			pOptionDlgMobileNew->m_chkNationalCallcenter.SetCheck(1);
		}
		else
			pOptionDlgMobileNew->m_chkNationalCallcenter.SetCheck(0);


		if(bDistanceChargeCheck) //거리요금제
		{					
			if(pOptionDlgMobileNew->m_bNotAllOrderView)
				pOptionDlgMobileNew->m_chkNotAllView.SetCheck(TRUE);
			else
				pOptionDlgMobileNew->m_chkNotAllView.SetCheck(FALSE);
		}
		
	}
	else {
		pOptionDlgMobileNew->m_chkUseNewRegion.SetCheck(0);
		pOptionDlgMobileNew->m_editMaxDistance.EnableWindow(FALSE);
		pOptionDlgMobileNew->m_editMaxNearOrder.EnableWindow(FALSE);
		pOptionDlgMobileNew->m_chkUseNewRegionAllDong.EnableWindow(FALSE);
		//m_chkNationalCallcenter.EnableWindow(FALSE);
		pOptionDlgMobileNew->m_strMaxDistance.Format("%d", nMaxDistance);
		pOptionDlgMobileNew->m_strMaxNearOrder.Format("%d", nMaxNearOrder);
		pOptionDlgMobileNew->m_editMaxDistance.SetWindowText(pOptionDlgMobileNew->m_strMaxDistance);
		pOptionDlgMobileNew->m_editMaxNearOrder.SetWindowText(pOptionDlgMobileNew->m_strMaxNearOrder);
		pOptionDlgMobileNew->m_chkNotAllView.EnableWindow(FALSE);

		if (pOptionDlgMobileNew->m_bNationalCallcenter != 0) {
			pOptionDlgMobileNew->m_bNationalCallcenter = 1;
			pOptionDlgMobileNew->m_chkNationalCallcenter.SetCheck(1);
		}
		else
			pOptionDlgMobileNew->m_chkNationalCallcenter.SetCheck(0);
	}


	long nSymbolDisplayType,nChargeDisplayMin,nChargeDisplayMax;
	pRs->GetFieldValue("sClientSymbol",pOptionDlgMobileNew->m_strSymbol);
	pRs->GetFieldValue("nSymbolDisplayType",nSymbolDisplayType);
	pRs->GetFieldValue("nChargeDisplayMin", nChargeDisplayMin);
	pRs->GetFieldValue("nChargeDisplayMax", nChargeDisplayMax);

	if(nSymbolDisplayType < 0 || nSymbolDisplayType > 3) nSymbolDisplayType = 3;		
	pOptionDlgMobileNew->m_comboSymbolDisplay.SetCurSel(nSymbolDisplayType);
	pOptionDlgMobileNew->m_comboSymbolDisplay.GetLBText(nSymbolDisplayType,pOptionDlgMobileNew->m_strSymbolDisplay);
	pOptionDlgMobileNew->m_strChargeMin.Format("%d",nChargeDisplayMin);
	pOptionDlgMobileNew->m_strChargeMax.Format("%d",nChargeDisplayMax);


	pOptionDlgMobileNew->SetAutoRangeCombo(nAARange);
}


void CMainOptionDlg2::RefreshInfo()
{	
	COptionDlgGeneral2*	pOptionDlgGeneral2	= (COptionDlgGeneral2*)GetTabItem(OPTION_GENERAL_TAB);
	COptionDlgCharge*		pOptionDlgCharge	= (COptionDlgCharge*)GetTabItem(OPTION_CHARGE_TAB);
	COptionDlgCID*			pOptionDlgCID		= (COptionDlgCID*)GetTabItem(OPTION_CID_TAB);	
	COptionDlgSMS3*		pOptionDlgSMS3		= (COptionDlgSMS3*)GetTabItem(OPTION_SMS3_TAB);
	COptionDlgMobileNew*	pOptionDlgMobileNew	= (COptionDlgMobileNew*)GetTabItem(OPTION_MOBILE_NEW_TAB);	
	COptionDlgInterCall2*  pOptionDlgInterCall2	= (COptionDlgInterCall2*)GetTabItem(OPTION_INTERCALL_TAB);	
	COptionDlgPersonalInfo*	pOptionDlgPersonalInfo	= (COptionDlgPersonalInfo*)GetTabItem(OPTION_PERSONAL_INFO_TAB);
	COptionDlgSmartQ*	pOptionDlgSmartQ	= (COptionDlgSmartQ*)GetTabItem(OPTION_SMART_QUICK);
	COptionDlgSmartQuick*	pOptionDlgSmartQuick	= (COptionDlgSmartQuick*)GetTabItem(OPTION_SMART_QUICK_LOGI);
	COptionDlgLogiContract*	pOptionDlgLogiContract	= (COptionDlgLogiContract*)GetTabItem(OPTION_CONTRACT_LOGI);

	long nCompany = -1; CString sql = "";
	nCompany = GetSelCompanyCode();
	CBranchInfo *pRevisitCustomerSendCompany;
	pOptionDlgCID->m_cmbRevisitCustomer.ResetContent();
	if(m_ba.GetCount() > 1) 
	{	
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pRevisitCustomerSendCompany = (CBranchInfo*)m_ba.GetAt(i);
			if(pRevisitCustomerSendCompany->strBranchName == "통합")
				continue;
			int nItem = pOptionDlgCID->m_cmbRevisitCustomer.AddString(pRevisitCustomerSendCompany->strBranchName);
			pOptionDlgCID->m_cmbRevisitCustomer.SetItemData(nItem,pRevisitCustomerSendCompany->nCompanyCode);
		}
	}
	else
	{
		CString sCompany = m_ci.GetBranchName(nCompany);
		int nItem = pOptionDlgCID->m_cmbRevisitCustomer.AddString(sCompany);
		pOptionDlgCID->m_cmbRevisitCustomer.SetItemData(nItem,nCompany);
	}
 
	// 두개다 프로시져 작업해야함.
	if(m_bLogView)
		sql = "select_option_log_view_new14";	
	else	 
		sql = "select_option_q_76"; 

	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, sql);
	CMkRecordset pRs(m_pMkDb);
	if(m_bLogView)
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nLogViewCompany);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nLogID);
	}
	else
	{
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
	}

	
	if(pRs.Execute(&pCmd)) {

		// 각세션에 맞게 작업하세요...
		//---------------------- 일반  ---------------------- 	
			OptionControlApply(&pRs, pOptionDlgGeneral2);			
		//---------------------- 금액  ---------------------- 
			OptionControlApply(&pRs, pOptionDlgCharge);
		//---------------------- cid  ----------------------
			OptionControlApply(&pRs, pOptionDlgCID);
		//---------------------- sms  ----------------------
			OptionControlApply(&pRs, pOptionDlgSMS3);
		//---------------------- pda  ----------------------
			OptionControlApply(&pRs, pOptionDlgMobileNew);
		//---------------------- InterCall  ----------------------
			OptionControlApply(&pRs, pOptionDlgInterCall2);
		//---------------------- SmartQuick  ----------------------
			OptionControlApply(&pRs, pOptionDlgSmartQ);

			if(pOptionDlgPersonalInfo)
				pOptionDlgPersonalInfo->RefreshData(&pRs);

			if(pOptionDlgSmartQuick && !m_bLogView)
				pOptionDlgSmartQuick->RefreshData(&pRs);

			if(pOptionDlgLogiContract && !m_bLogView)
				pOptionDlgLogiContract->RefreshData(&pRs);

		pRs.Close();
	}

	UpdateData(FALSE);
	
	pOptionDlgGeneral2->UpdateData(FALSE);
	pOptionDlgCharge->UpdateData(FALSE);
	pOptionDlgCID->UpdateData(FALSE);
	pOptionDlgSMS3->UpdateData(FALSE);	
	pOptionDlgInterCall2->UpdateData(FALSE);
	pOptionDlgMobileNew->UpdateData(FALSE);

	pOptionDlgSmartQ->OnEnChangeSendSmartqMentEdit();
	pOptionDlgGeneral2->OnBnClickedAutoShareOrderCheck();
	pOptionDlgSMS3->OnEnChangeCancelSmsEdit();
	pOptionDlgMobileNew->OnBnClickedChargeLimitCheck();
	//pOptionDlgMobileNew->m_MinCompleteTimeEdit.EnableWindow(pOptionDlgMobileNew->m_NotCompletedLimitCheck.GetCheck());
}

void CMainOptionDlg2::RefreshLogInfo()
	{
	long nCompany = -1;
	CBranchInfo *pBi = m_cBranch.GetBranchInfo();

	m_List.DeleteAllItem();	


	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "select_company_log_user");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), pBi->bIntegrated);
	if(pRs.Execute(&pCmd)) 
	m_List.MyAddItem(pRs,TRUE);

	m_List.Populate();
}

void CMainOptionDlg2::OnBnClickedApplyAllBtn()
{

	long nItem = m_wndTabControl.GetCurSel();

	if(nItem < 0) return;

	if(SaveNew(nItem, TRUE))
		MessageBox("성공적으로 모든 지사에 적용되었습니다.\r\n옵션 항목은 프로그램 재시작 후 적용됩니다.", "설정변경", MB_ICONINFORMATION);

}


void CMainOptionDlg2::OnBnClickedOk()
{

	long nItem = m_wndTabControl.GetCurSel();

	if(nItem < 0) return;

	if(SaveNew(nItem, FALSE))
		MessageBox("성공적으로 적용되었습니다.\r\n옵션 항목은 프로그램 재시작 후 적용됩니다.", "설정변경", MB_ICONINFORMATION);
	
}

void CMainOptionDlg2::OnBnClickedClose()
{
	OnOK();
}

int CMainOptionDlg2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	

	return 0;
}

int CMainOptionDlg2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{

	return CMyDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CMainOptionDlg2::OnCbnSelchangeBranchCombo()
{	
	RefreshInfo();
	RefreshLogInfo();
}

CWnd* CMainOptionDlg2::GetTabItem(CString sCaption)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	for(int nTab = 0;nTab < nTabCount;nTab++)
	{
		CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);
		if(sCaption ==  pXTPTabManagerItem->GetCaption() )
		{
			CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
			return pWnd;
		}
	}

	return NULL;
}

CWnd* CMainOptionDlg2::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}


long CMainOptionDlg2::GetSelCompanyCode()
{
	return m_cBranch.GetBranchInfo()->nCompanyCode;
}

LONG CMainOptionDlg2::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	RefreshInfo();
	RefreshLogInfo();

	return 0;
}

BOOL CMainOptionDlg2::SaveNew(long nPage, BOOL bAll)
{
	CMyFormView *pWnd = (CMyFormView*)GetTabItem(nPage);

	CStringArray sCompanyArray;
	long nCount = m_lstBranch.GetCheckCount(sCompanyArray);
	long nCompany = GetSelCompanyCode(); 

	if(bAll)
	{
		CString sTemp = ""; 
		sTemp.Format("[%d]개의 지사에 적용 하시겠습니까?", nCount);

		if(MessageBox(sTemp, "확인", MB_OKCANCEL) != IDOK)
			return FALSE;
	}

	if(bAll)
	{
		for(int i = 0; i < sCompanyArray.GetCount(); i++)
		{
			if(!pWnd->Save(atoi(sCompanyArray.GetAt(i)), TRUE))
			{
				MessageBox("설정 저장중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.", 
					"확인", MB_ICONINFORMATION);
				return FALSE;
			}
		}

	}
	else
	{
		if(!pWnd->Save(nCompany, FALSE))
		{
			MessageBox("설정 저장중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.", 
				"확인", MB_ICONINFORMATION);
			return FALSE;
		}

	}
	RefreshLogInfo();

	return TRUE;
}
