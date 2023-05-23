// OptionDlgSmartQuick.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OptionDlgSmartQuick.h"
#include "MainOptionDlg2011.h"
#include "SmartCallBoardDlg.h"
#include "SetAppRcpTimeDlg.h"
#include "AddBoxChargeDlg.h"
#include "ChargeChangeHelpDlg.h"


// COptionDlgSmartQuick

IMPLEMENT_DYNCREATE(COptionDlgSmartQuick, CMyFormView)

COptionDlgSmartQuick::COptionDlgSmartQuick()
	: CMyFormView(COptionDlgSmartQuick::IDD)
{
	m_nBoard1 = 0;
	m_nBoard2 = 0;
	m_nBoard3 = 0;
	m_nMoreInfo1 = 0;
	m_nMoreInfo2 = 0;
	m_nMoreInfo3 = 0;
	m_nEventBoard = 0;
}

COptionDlgSmartQuick::~COptionDlgSmartQuick()
{
}

void COptionDlgSmartQuick::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_AUTO_WITHDRAW_CHECK, m_chkUseAutoWithdraw);
	DDX_Control(pDX, IDC_WITHDRAW_ABLE_MILEAGE_EDIT, m_edtWithdrawAbleMileage);
	DDX_Control(pDX, IDC_WITHDRAW_ABLE_MILEAGE_MAX_EDIT, m_edtWithdrawAbleMileageMax);
	DDX_Control(pDX, IDC_MONTHLY_WITHDRAW_ABLE_MILEAGE_COMBO, m_cmbMonthlyWithdrawAbleMileage);
	DDX_Control(pDX, IDC_DAILY_WITHDRAW_ABLE_MILEAGE_COUNT_COMBO, m_cmbDailyWithdrawAbleMileageCount);
	DDX_Control(pDX, IDC_MILEAGE_TO_CASH_PER_EDIT, m_edtMileageToCashPer);
	DDX_Control(pDX, IDC_USE_SMART_QUICK_EVENT_CHECK, m_chkUseEventBoard);

	DDX_Control(pDX, IDC_CHARGE_ETC_EDIT, m_edtChargeEtc);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC0_EDIT, m_edtPayTypeEtc0);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC1_EDIT, m_edtPayTypeEtc1);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC2_EDIT, m_edtPayTypeEtc2);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC3_EDIT, m_edtPayTypeEtc3);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC4_EDIT, m_edtPayTypeEtc4);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC6_EDIT, m_edtPayTypeEtc6);
	DDX_Control(pDX, IDC_PAY_TYPE_ETC7_EDIT, m_edtPayTypeEtc7);

	DDX_Control(pDX, IDC_USE_PAY_CASH_CHECK, m_chkUsePayCash);
	DDX_Control(pDX, IDC_USE_RUN_TYPE1_CHECK, m_chkUseRunType1);

	DDX_Control(pDX, IDC_CAR_TYPE_WEIGHT_ETC0_EDIT, m_edtCarTypeWeightEtc0);
	DDX_Control(pDX, IDC_CAR_TYPE_WEIGHT_ETC2_EDIT, m_edtCarTypeWeightEtc2);
	DDX_Control(pDX, IDC_CAR_TYPE_WEIGHT_ETC3_EDIT, m_edtCarTypeWeightEtc3);
	DDX_Control(pDX, IDC_CAR_TYPE_WEIGHT_ETC4_EDIT, m_edtCarTypeWeightEtc4);
	DDX_Control(pDX, IDC_CAR_TYPE_WEIGHT_ETC5_EDIT, m_edtCarTypeWeightEtc5);

	DDX_Control(pDX, IDC_CAR_TYPE_ETC0_EDIT, m_edtCarTypeEtc0);
	DDX_Control(pDX, IDC_CAR_TYPE_ETC2_EDIT, m_edtCarTypeEtc2);
	DDX_Control(pDX, IDC_CAR_TYPE_ETC3_EDIT, m_edtCarTypeEtc3);
	DDX_Control(pDX, IDC_CAR_TYPE_ETC4_EDIT, m_edtCarTypeEtc4);
	DDX_Control(pDX, IDC_CAR_TYPE_ETC5_EDIT, m_edtCarTypeEtc5);

	DDX_Control(pDX, IDC_CUSTOMER_ETC1_EDIT, m_edtCustomerEtc1);
	DDX_Control(pDX, IDC_CUSTOMER_ETC2_EDIT, m_edtCustomerEtc2);
	DDX_Control(pDX, IDC_CUSTOMER_ETC3_EDIT, m_edtCustomerEtc3);
	DDX_Control(pDX, IDC_CUSTOMER_ETC4_EDIT, m_edtCustomerEtc4);

	DDX_Control(pDX, IDC_ITEM_TYPE_ETC1_EDIT, m_edtItemTypeEtc1);
	DDX_Control(pDX, IDC_ITEM_TYPE_ETC2_EDIT, m_edtItemTypeEtc2);
	DDX_Control(pDX, IDC_ITEM_TYPE_ETC3_EDIT, m_edtItemTypeEtc3);
	DDX_Control(pDX, IDC_ITEM_TYPE_ETC4_EDIT, m_edtItemTypeEtc4);
	DDX_Control(pDX, IDC_ITEM_TYPE_ETC5_EDIT, m_edtItemTypeEtc5);

	DDX_Control(pDX, IDC_USE_INQUIRY_CHARGE_CHECK, m_chkUseInquiryCharge);
	DDX_Control(pDX, IDC_INQUIRY_CHARGE_MENT_EDIT, m_edtInquiryChargeMent);

	DDX_Control(pDX, IDC_USE_CUSTOMER_CHARGE_CHANGE_CHECK, m_chkUseCustomerChargeChange);
	DDX_Control(pDX, IDC_CHARGE_CHANGE_MIN_EDIT, m_edtChargeChangeMin);
	DDX_Control(pDX, IDC_CHARGE_CHANGE_MAX_EDIT, m_edtChargeChangeMax);
	DDX_Control(pDX, IDC_CHARGE_CHANGE_MENT_EDIT, m_edtChargeChangeMent);

	DDX_Control(pDX, IDC_NOT_RCP_ZERO_CHARGE_CHECK, m_chkNotRcpZeroCharge);
}

BEGIN_MESSAGE_MAP(COptionDlgSmartQuick, CMyFormView)
	ON_BN_CLICKED(IDC_TIP_BTN, &COptionDlgSmartQuick::OnBnClickedTipBtn)
	ON_BN_CLICKED(IDC_EVENT_DLG_BTN, &COptionDlgSmartQuick::OnBnClickedEventDlgBtn)
	ON_WM_MOUSEACTIVATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SET_APP_TIME_BTN, &COptionDlgSmartQuick::OnBnClickedSetAppTimeBtn)
	ON_BN_CLICKED(IDC_SET_BOX_ADD_CHARGE_BTN, &COptionDlgSmartQuick::OnBnClickedSetBoxAddChargeBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HELP_BTN, &COptionDlgSmartQuick::OnBnClickedHelpBtn)
END_MESSAGE_MAP()


// COptionDlgSmartQuick 진단입니다.

#ifdef _DEBUG
void COptionDlgSmartQuick::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COptionDlgSmartQuick::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COptionDlgSmartQuick 메시지 처리기입니다.

void COptionDlgSmartQuick::OnBnClickedTipBtn()
{
//	CTipDlg dlg;
//	dlg.DoModal();
}


BOOL COptionDlgSmartQuick::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	CMkCommand cmd(m_pMkDb, "update_option_smart_quick_9");

	//cmd.AddParameter(bAll);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(m_chkUseAutoWithdraw.GetCheck());
	cmd.AddParameter(LF->GetLongFromEdit(&m_edtWithdrawAbleMileage));
	cmd.AddParameter(LF->GetLongFromEdit(&m_edtWithdrawAbleMileageMax));
	cmd.AddParameter(LF->GetLongFromEdit(&m_cmbMonthlyWithdrawAbleMileage));
	cmd.AddParameter(LF->GetLongFromEdit(&m_cmbDailyWithdrawAbleMileageCount));
	cmd.AddParameter(LF->GetLongFromEdit(&m_edtMileageToCashPer));
	cmd.AddParameter(m_chkUseEventBoard.GetCheck());
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtChargeEtc));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc0));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc1));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc2));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc3));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc4));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc6));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtPayTypeEtc7));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeWeightEtc0));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeWeightEtc2));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeWeightEtc3));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeWeightEtc4));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeWeightEtc5));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeEtc0));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeEtc2));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeEtc3));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeEtc4));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCarTypeEtc5));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCustomerEtc1));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCustomerEtc2));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCustomerEtc3));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtCustomerEtc4));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtItemTypeEtc1));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtItemTypeEtc2));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtItemTypeEtc3));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtItemTypeEtc4));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtItemTypeEtc5));

	cmd.AddParameter(m_chkUsePayCash.GetCheck());
	cmd.AddParameter(m_chkUseRunType1.GetCheck());
	cmd.AddParameter(m_chkUseInquiryCharge.GetCheck());
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtInquiryChargeMent));
	cmd.AddParameter(m_chkUseCustomerChargeChange.GetCheck());
	cmd.AddParameter(LF->GetLongFromEdit(&m_edtChargeChangeMin));
	cmd.AddParameter(LF->GetLongFromEdit(&m_edtChargeChangeMax));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtChargeChangeMent));
	cmd.AddParameter(m_chkNotRcpZeroCharge.GetCheck());

	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);


	return cmd.Execute();

}

void COptionDlgSmartQuick::RefreshData(CMkRecordset *pRs)
{
	BOOL bUseAutoWithdraw, bUseEventBoard, bUsePayCash, bUseRunType1, bUseInquiryCharge, bUseCustomerChargeChange;
	long nWithdrawAbleMileage, nWithdrawAbleMileageMax, nMonthlyWithdrawAbleMileage;
	long nDailyWithdrawAbleMileageCount, nMileageToCashPer;
	CString strChargeEtc, strPayTypeEtc0, strPayTypeEtc1, strPayTypeEtc2;
	CString strPayTypeEtc3, strPayTypeEtc4, strPayTypeEtc6, strPayTypeEtc7;
	CString strCarTypeWeightEtc0, strCarTypeWeightEtc2, strCarTypeWeightEtc3, strCarTypeWeightEtc4, strCarTypeWeightEtc5;
	CString strCarTypeEtc0, strCarTypeEtc2, strCarTypeEtc3, strCarTypeEtc4, strCarTypeEtc5;
	CString strCustomerEtc1, strCustomerEtc2, strCustomerEtc3, strCustomerEtc4;
	CString strItemTypeEtc1, strItemTypeEtc2, strItemTypeEtc3, strItemTypeEtc4, strItemTypeEtc5, strInquiryChargeMent, strChargeChangeMent;
	long nChargeChangeMin, nChargeChangeMax, bNotRcpZeroCharge;

	pRs->GetFieldValue("bUseAutoWithdraw", bUseAutoWithdraw);
	pRs->GetFieldValue("nWithdrawAbleMileage", nWithdrawAbleMileage);
	pRs->GetFieldValue("nWithdrawAbleMileageMax", nWithdrawAbleMileageMax);
	pRs->GetFieldValue("nMonthlyWithdrawAbleMileage", nMonthlyWithdrawAbleMileage);
	pRs->GetFieldValue("nDailyWithdrawAbleMileageCount", nDailyWithdrawAbleMileageCount);
	pRs->GetFieldValue("nMileageToCashPer", nMileageToCashPer);
	pRs->GetFieldValue("bUseEventBoard", bUseEventBoard);
	pRs->GetFieldValue("sChargeEtc", strChargeEtc);
	pRs->GetFieldValue("sPayTypeEtc0", strPayTypeEtc0);
	pRs->GetFieldValue("sPayTypeEtc1", strPayTypeEtc1);
	pRs->GetFieldValue("sPayTypeEtc2", strPayTypeEtc2);
	pRs->GetFieldValue("sPayTypeEtc3", strPayTypeEtc3);
	pRs->GetFieldValue("sPayTypeEtc4", strPayTypeEtc4);
	pRs->GetFieldValue("sPayTypeEtc6", strPayTypeEtc6);
	pRs->GetFieldValue("sPayTypeEtc7", strPayTypeEtc7);
	pRs->GetFieldValue("bUsePayCash", bUsePayCash);
	pRs->GetFieldValue("bUseRunType1", bUseRunType1);
	pRs->GetFieldValue("bUseInquiryCharge", bUseInquiryCharge);	
	pRs->GetFieldValue("sCarTypeWeightEtc0", strCarTypeWeightEtc0);
	pRs->GetFieldValue("sCarTypeWeightEtc2", strCarTypeWeightEtc2);
	pRs->GetFieldValue("sCarTypeWeightEtc3", strCarTypeWeightEtc3);
	pRs->GetFieldValue("sCarTypeWeightEtc4", strCarTypeWeightEtc4);
	pRs->GetFieldValue("sCarTypeWeightEtc5", strCarTypeWeightEtc5);
	pRs->GetFieldValue("sCarTypeEtc0", strCarTypeEtc0);
	pRs->GetFieldValue("sCarTypeEtc2", strCarTypeEtc2);
	pRs->GetFieldValue("sCarTypeEtc3", strCarTypeEtc3);
	pRs->GetFieldValue("sCarTypeEtc4", strCarTypeEtc4);
	pRs->GetFieldValue("sCarTypeEtc5", strCarTypeEtc5);
	pRs->GetFieldValue("sCustomerEtc1", strCustomerEtc1);
	pRs->GetFieldValue("sCustomerEtc2", strCustomerEtc2);
	pRs->GetFieldValue("sCustomerEtc3", strCustomerEtc3);
	pRs->GetFieldValue("sCustomerEtc4", strCustomerEtc4);
	pRs->GetFieldValue("sItemTypeEtc1", strItemTypeEtc1);
	pRs->GetFieldValue("sItemTypeEtc2", strItemTypeEtc2);
	pRs->GetFieldValue("sItemTypeEtc3", strItemTypeEtc3);
	pRs->GetFieldValue("sItemTypeEtc4", strItemTypeEtc4);
	pRs->GetFieldValue("sItemTypeEtc5", strItemTypeEtc5);
	pRs->GetFieldValue("sInquiryChargeMent", strInquiryChargeMent);
	pRs->GetFieldValue("bUseCustomerChargeChange", bUseCustomerChargeChange);
	pRs->GetFieldValue("nChargeChangeMin", nChargeChangeMin);
	pRs->GetFieldValue("nChargeChangeMax", nChargeChangeMax);
	pRs->GetFieldValue("sChargeChangeMent", strChargeChangeMent);
	pRs->GetFieldValue("bNotRcpZeroCharge", bNotRcpZeroCharge);
	
	m_chkUseAutoWithdraw.SetCheck(bUseAutoWithdraw);
	m_edtWithdrawAbleMileage.SetWindowText(LF->GetMyNumberFormat(nWithdrawAbleMileage));
	m_edtWithdrawAbleMileageMax.SetWindowText(LF->GetMyNumberFormat(nWithdrawAbleMileageMax));
	m_cmbMonthlyWithdrawAbleMileage.SetWindowText(LF->GetMyNumberFormat(nMonthlyWithdrawAbleMileage));
	m_cmbDailyWithdrawAbleMileageCount.SetWindowText(LF->GetMyNumberFormat(nDailyWithdrawAbleMileageCount));
	m_edtMileageToCashPer.SetWindowText(LF->GetMyNumberFormat(nMileageToCashPer));
	m_chkUseEventBoard.SetCheck(bUseEventBoard);

	m_edtChargeEtc.SetWindowText(strChargeEtc);
	m_edtPayTypeEtc0.SetWindowText(strPayTypeEtc0);
	m_edtPayTypeEtc1.SetWindowText(strPayTypeEtc1);
	m_edtPayTypeEtc2.SetWindowText(strPayTypeEtc2);
	m_edtPayTypeEtc3.SetWindowText(strPayTypeEtc3);
	m_edtPayTypeEtc4.SetWindowText(strPayTypeEtc4);
	m_edtPayTypeEtc6.SetWindowText(strPayTypeEtc6);
	m_edtPayTypeEtc7.SetWindowText(strPayTypeEtc7);

	m_edtCarTypeWeightEtc0.SetWindowText(strCarTypeWeightEtc0);
	m_edtCarTypeWeightEtc2.SetWindowText(strCarTypeWeightEtc2);
	m_edtCarTypeWeightEtc3.SetWindowText(strCarTypeWeightEtc3);
	m_edtCarTypeWeightEtc4.SetWindowText(strCarTypeWeightEtc4);
	m_edtCarTypeWeightEtc5.SetWindowText(strCarTypeWeightEtc5);

	m_edtCarTypeEtc0.SetWindowText(strCarTypeEtc0);
	m_edtCarTypeEtc2.SetWindowText(strCarTypeEtc2);
	m_edtCarTypeEtc3.SetWindowText(strCarTypeEtc3);
	m_edtCarTypeEtc4.SetWindowText(strCarTypeEtc4);
	m_edtCarTypeEtc5.SetWindowText(strCarTypeEtc5);

	m_edtCustomerEtc1.SetWindowText(strCustomerEtc1);
	m_edtCustomerEtc2.SetWindowText(strCustomerEtc2);
	m_edtCustomerEtc3.SetWindowText(strCustomerEtc3);
	m_edtCustomerEtc4.SetWindowText(strCustomerEtc4);

	m_edtItemTypeEtc1.SetWindowText(strItemTypeEtc1);
	m_edtItemTypeEtc2.SetWindowText(strItemTypeEtc2);
	m_edtItemTypeEtc3.SetWindowText(strItemTypeEtc3);
	m_edtItemTypeEtc4.SetWindowText(strItemTypeEtc4);
	m_edtItemTypeEtc5.SetWindowText(strItemTypeEtc5);

	m_chkUsePayCash.SetCheck(bUsePayCash);
	m_chkUseRunType1.SetCheck(bUseRunType1);
	m_chkUseInquiryCharge.SetCheck(bUseInquiryCharge);

	m_edtInquiryChargeMent.SetWindowText(strInquiryChargeMent);

	m_chkUseCustomerChargeChange.SetCheck(bUseCustomerChargeChange);
	m_edtChargeChangeMin.SetWindowText(LF->GetMyNumberFormat(nChargeChangeMin));
	m_edtChargeChangeMax.SetWindowText(LF->GetMyNumberFormat(nChargeChangeMax));
	m_edtChargeChangeMent.SetWindowText(strChargeChangeMent);
	m_chkNotRcpZeroCharge.SetCheck(bNotRcpZeroCharge);
}

void COptionDlgSmartQuick::OnBnClickedEventDlgBtn()
{
	ChangeBoardItem(6);
}

void COptionDlgSmartQuick::ChangeBoardItem(long nBoardIndex)
{
	long *nIndex; 

	if(nBoardIndex == 0) nIndex = &m_nBoard1;
	else if(nBoardIndex == 1) nIndex = &m_nBoard2;
	else if(nBoardIndex == 2) nIndex = &m_nBoard3;
	else if(nBoardIndex == 3) nIndex = &m_nMoreInfo1;
	else if(nBoardIndex == 4) nIndex = &m_nMoreInfo2;
	else if(nBoardIndex == 5) nIndex = &m_nMoreInfo3;
	else if(nBoardIndex == 6) nIndex = &m_nEventBoard;

	if(*nIndex == 0)
	{
		CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

		CMkCommand cmd(m_pMkDb, "make_smart_call_board_index_smartd");
		cmd.AddParameter(pDlg->GetSelCompanyCode());
		cmd.AddParameter(nBoardIndex);
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(!cmd.Execute())
			return;

		parRet->GetValue(*nIndex);
	}


	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

	CSmartCallBoardDlg dlg;
	dlg.m_nBoardIndex = *nIndex;
	dlg.m_nCompany = pDlg->GetSelCompanyCode();
	dlg.m_bEventBoard = nBoardIndex == 6 ? TRUE : FALSE;
	dlg.DoModal();
}

void COptionDlgSmartQuick::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);
 
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 

	/*m_btnTip.LoadBitmaps(IDB_TIP_UP, IDB_TIP_DOWN);
	m_btnTip2.LoadBitmaps(IDB_TIP_UP, IDB_TIP_DOWN);*/

	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
 
	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;  
	sizeTotal.cy = 1300;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
}

int COptionDlgSmartQuick::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return TRUE;
	//return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COptionDlgSmartQuick::OnSize(UINT nType, int cx, int cy)
{
	return;
	CMyFormView::OnSize(nType, cx, cy);
}

void COptionDlgSmartQuick::OnBnClickedSetAppTimeBtn()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

	CSetAppRcpTimeDlg dlg;
	dlg.m_nCompany = pDlg->GetSelCompanyCode();
	dlg.DoModal();
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgSmartQuick::OnBnClickedSetBoxAddChargeBtn()
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

	CAddBoxChargeDlg dlg;
	dlg.m_nCompany = pDlg->GetSelCompanyCode();
	dlg.DoModal();
}

void COptionDlgSmartQuick::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}

void COptionDlgSmartQuick::OnBnClickedHelpBtn()
{
	CChargeChangeHelpDlg dlg;
	dlg.DoModal();
}
