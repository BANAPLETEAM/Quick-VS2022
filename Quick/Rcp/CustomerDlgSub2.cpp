// CustomerDlgSub2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerDlgSub2.h"
#include "ChargeSectionTypeDlg.h"
#include "CustomerDlg.h"
// CCustomerDlgSub2

typedef struct{
	int nCompany;
	int nWNo;
	CString strWName;
}SALES_SIMPLE_INFO;
IMPLEMENT_DYNCREATE(CCustomerDlgSub2, CMyFormView)

CCustomerDlgSub2::CCustomerDlgSub2()
: CMyFormView(CCustomerDlgSub2::IDD)
, m_strDiscount(_T(""))
, m_strMileage(_T(""))
, m_strCoupon(_T(""))
, m_strEMail(_T(""))
, m_nSendStateChangeSMS(FALSE)
, m_bPreventPosUpdate(FALSE)
, m_bUseHomepage(FALSE)
, m_nICMapDisplayType(FALSE)
, m_dtSalesTime(COleDateTime::GetCurrentTime())
, m_strFax(_T(""))
, m_bDiscountApplyOnlyCredit(FALSE)
, m_bOnlinePopup(FALSE)
, m_strOnlinePopupCharge(_T(""))
{
	m_pCustomerDlg = NULL;
}

CCustomerDlgSub2::~CCustomerDlgSub2()
{
}

void CCustomerDlgSub2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRICE_GRADE_COMBO, m_cmbPriceGrade);
	DDX_Control(pDX, IDC_DISCOUNT_COMBO, m_cmbDiscount);
	DDX_Control(pDX, IDC_MILEAGE_COMBO, m_cmbMileage);
	DDX_Control(pDX, IDC_COMPANY_CHARGE_COMBO, m_cmbCompanyCharge);	
	DDX_Control(pDX, IDC_COUPON_COMBO, m_cmbCoupon);
	DDX_Control(pDX, IDC_DISCOUNT_EDIT, m_edtDiscount);
	DDX_Control(pDX, IDC_DISCOUNT_RANGE_EDIT, m_edtDiscountRange);	
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileage);
	DDX_Control(pDX, IDC_COUPON_EDIT, m_edtCoupon);
	DDX_Control(pDX, IDC_PRICE_GRADE_STATIC, m_stcPriceGrade);
	DDX_Control(pDX, IDC_DISCOUNT_STATIC, m_stcDiscount);
	DDX_Control(pDX, IDC_MILEAGE_STATIC, m_stcMileage);
	DDX_Control(pDX, IDC_COUPON_STATIC, m_stcCoupon);
	DDX_Text(pDX, IDC_DISCOUNT_EDIT, m_strDiscount);
	DDX_Text(pDX, IDC_MILEAGE_EDIT, m_strMileage);
	DDX_Text(pDX, IDC_COUPON_EDIT, m_strCoupon);

	DDX_Control(pDX, IDC_LOGIN_ID_EDIT, m_edtLoginID);
	DDX_Control(pDX, IDC_LOGIN_PW_EDIT, m_edtLoginPW);
	DDX_Text(pDX, IDC_LOGIN_ID_EDIT, m_strLoginID);
	DDX_Text(pDX, IDC_LOGIN_PW_EDIT, m_strLoginPW);
	DDX_Control(pDX, IDC_SEND_STATE_CHANGE_SMS_CHECK, m_chkSendStateChangeSMS);

	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEMail);
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
	DDX_Check(pDX, IDC_SEND_STATE_CHANGE_SMS_CHECK, m_nSendStateChangeSMS);
	DDX_Check(pDX, IDC_PREVENT_POS_UPDATE_CHECK, m_bPreventPosUpdate);
	DDX_Control(pDX, IDC_IC_MAP_DISPLAY_TYPE_CHK, m_chkICMapDisplayType);
	DDX_Check(pDX, IDC_USE_HOMEPAGE_CHECK, m_bUseHomepage);
	DDX_Check(pDX, IDC_IC_MAP_DISPLAY_TYPE_CHK, m_nICMapDisplayType);
	DDX_Control(pDX, IDC_CUSTOMER_GRADE_STATIC, m_stcCustomerGrade);
	DDX_Control(pDX, IDC_ALLOC_GROUP_STATIC, m_stcAllocGroup);

	DDX_Control(pDX, IDC_CUSTOMER_GRADE_COMBO, m_cmbCustomerGrade);
	DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_cmbAllocGroup);
	DDX_Control(pDX, IDC_SALES_TEAM_COMBO, m_cmbSalesTeam);
	DDX_Control(pDX, IDC_SALES_TIME_DATETIMEPICKER, m_dtpSalesTime);
	DDX_DateTimeCtrl(pDX, IDC_SALES_TIME_DATETIMEPICKER, m_dtSalesTime);
	DDX_Control(pDX, IDC_USE_HOMEPAGE_CHECK, m_chkUseHomePage);
	DDX_Control(pDX, IDC_PREVENT_POS_UPDATE_CHECK, m_chkPreventPosUpdate);
	DDX_Control(pDX, IDC_SET_COUPON_BTN, m_btnSetCoupon);
	DDX_Control(pDX, IDC_SET_DISCOUNT_BTN, m_btnSetDiscount);
	DDX_Control(pDX, IDC_SET_MILEAGE_BTN, m_btnSetMileage);
	DDX_Control(pDX, IDC_FAX_EDIT, m_edtFax);
	DDX_Text(pDX, IDC_FAX_EDIT, m_strFax);

	DDX_Control(pDX, IDC_DISCOUNT_APPLY_ONPY_CREDIT_CHECK, m_chkDiscountApplyOnlyCredit);
	DDX_Check(pDX, IDC_DISCOUNT_APPLY_ONPY_CREDIT_CHECK, m_bDiscountApplyOnlyCredit);
	DDX_Control(pDX, IDC_ONLINE_POPUP_CHECK, m_chkOnlinePopup);
	DDX_Control(pDX, IDC_ONLINE_POPUP_CHARGE_EDIT, m_edtOnlinePopupCharge);
	DDX_Check(pDX, IDC_ONLINE_POPUP_CHECK, m_bOnlinePopup);
	DDX_Text(pDX, IDC_ONLINE_POPUP_CHARGE_EDIT, m_strOnlinePopupCharge);
}

BEGIN_MESSAGE_MAP(CCustomerDlgSub2, CMyFormView)
	ON_BN_CLICKED(IDC_SET_MILEAGE_BTN, OnBnClickedSetMileageBtn)
	ON_BN_CLICKED(IDC_SET_DISCOUNT_BTN, OnBnClickedSetDiscountBtn)
	ON_BN_CLICKED(IDC_SET_COUPON_BTN, OnBnClickedSetCouponBtn)
	ON_CBN_SELCHANGE(IDC_DISCOUNT_COMBO, OnCbnSelchangeDiscountCombo)
	ON_CBN_SELCHANGE(IDC_PRICE_GRADE_COMBO, OnCbnSelchangePriceGradeCombo)
	ON_CBN_SELCHANGE(IDC_COUPON_COMBO, OnCbnSelchangeCouponCombo)
	ON_CBN_SELCHANGE(IDC_MILEAGE_COMBO, OnCbnSelchangeMileageCombo)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SEND_STATE_CHANGE_SMS_CHECK, OnBnClickedSendStateChangeSmsCheck)
	ON_BN_CLICKED(IDC_IC_MAP_DISPLAY_TYPE_CHK, OnBnClickedIcMapDisplayTypeChk)
	ON_BN_CLICKED(IDC_USE_HOMEPAGE_CHECK, OnBnClickedUseHomepageCheck)
	ON_BN_CLICKED(IDC_PREVENT_POS_UPDATE_CHECK, OnBnClickedPreventPosUpdateCheck)
	ON_EN_CHANGE(IDC_DISCOUNT_EDIT, OnEnChangeDiscountEdit)
	ON_EN_CHANGE(IDC_MILEAGE_EDIT, OnEnChangeMileageEdit)
	ON_EN_CHANGE(IDC_COUPON_EDIT, OnEnChangeCouponEdit)
	ON_EN_CHANGE(IDC_LOGIN_ID_EDIT, OnEnChangeLoginIdEdit)
	ON_EN_CHANGE(IDC_LOGIN_PW_EDIT, OnEnChangeLoginPwEdit)
	ON_EN_CHANGE(IDC_EMAIL_EDIT, OnEnChangeEmailEdit)
	ON_CBN_SELCHANGE(IDC_CUSTOMER_GRADE_COMBO, &CCustomerDlgSub2::OnCbnSelchangeCustomerGradeCombo)
	ON_CBN_SELCHANGE(IDC_ALLOC_GROUP_COMBO, &CCustomerDlgSub2::OnCbnSelchangeAllocGroupCombo)
	ON_CBN_SELCHANGE(IDC_SALES_TEAM_COMBO, &CCustomerDlgSub2::OnCbnSelchangeSalesTeamCombo)

	ON_BN_CLICKED(IDC_APPLY_COMPANY_CHARGE_BTN, &CCustomerDlgSub2::OnBnClickedApplyCompanyChargeBtn)
	ON_BN_CLICKED(IDC_LOAD_COMPANY_CHARGE_BTN, &CCustomerDlgSub2::OnBnClickedLoadCompanyChargeBtn)
	ON_BN_CLICKED(IDC_ONLINE_POPUP_CHECK, &CCustomerDlgSub2::OnBnClickedOnlinePopupCheck)
	ON_EN_CHANGE(IDC_ONLINE_POPUP_CHARGE_EDIT, &CCustomerDlgSub2::OnEnChangeOnlinePopupChargeEdit)
END_MESSAGE_MAP()


// CCustomerDlgSub2 진단입니다.

#ifdef _DEBUG
void CCustomerDlgSub2::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerDlgSub2::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CCustomerDlgSub2::OnBnClickedSetMileageBtn()
{
	CChargeSectionTypeDlg dlg;
	dlg.m_nValueType = CST_MILEAGE;
	dlg.m_nInitClass = max(0, m_cmbMileage.GetCurSel() - 2);
	dlg.DoModal();
}

void CCustomerDlgSub2::OnBnClickedSetDiscountBtn()
{
	CChargeSectionTypeDlg dlg;
	dlg.m_nValueType = CST_DISCOUNT;
	dlg.m_nInitClass = max(0, m_cmbDiscount.GetCurSel() - 2);
	dlg.m_nCompany = m_pCustomerDlg->m_nCustomerTable;
	dlg.DoModal();
}

void CCustomerDlgSub2::OnBnClickedSetCouponBtn()
{
	CChargeSectionTypeDlg dlg;
	dlg.m_nValueType = CST_COUPON;
	dlg.m_nInitClass = max(0, m_cmbCoupon.GetCurSel() - 2);
	dlg.DoModal();
}


void CCustomerDlgSub2::OnCbnSelchangeDiscountCombo()
{

	SelChangeOption();
}

void CCustomerDlgSub2::SelChangeOption()
{
	if(m_cmbDiscount.GetCurSel() >= 2)
	{
		m_edtDiscount.SetWindowText("");
		//m_edtDiscountRange.SetWindowText("");
		m_edtDiscount.EnableWindow(FALSE);
		GetDlgItem(IDC_SET_DISCOUNT_BTN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DISCOUNT_EDIT)->ShowWindow(SW_HIDE);
		//m_edtDiscountRange.EnableWindow(FALSE);
	}
	else
	{
		m_edtDiscount.EnableWindow(TRUE);
		//m_edtDiscountRange.EnableWindow(TRUE);
		GetDlgItem(IDC_SET_DISCOUNT_BTN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DISCOUNT_EDIT)->ShowWindow(SW_SHOW);
	}

	if(m_cmbMileage.GetCurSel() == 0 || 
		m_cmbMileage.GetCurSel() == 3 )
	{
		m_edtMileage.SetWindowText("0");
		m_edtMileage.EnableWindow(FALSE);
	}
	else
	{
		m_edtMileage.EnableWindow(TRUE);
	}

	if(m_cmbCoupon.GetCurSel() >= 2)
	{
		m_edtCoupon.SetWindowText("0");
		m_edtCoupon.EnableWindow(FALSE);
	}
	else
	{
		m_edtCoupon.EnableWindow();
	}

	FindSalesMan();
}

void CCustomerDlgSub2::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyFormView::OnLButtonDown(nFlags, point);
}

CString CCustomerDlgSub2::GetEtcInfo()
{
	UpdateData(TRUE);
	CString strInfo = "";

	//	if(m_bCredit == TRUE)
	//		strInfo += "<Run Foreground='red' FontWeight='Normal'>[신용]</Run> ";
	if(m_nSendStateChangeSMS == TRUE)
		strInfo += "<Run Foreground='red' FontWeight='Normal'>[상태변경SMS수신]</Run> ";
	if(m_nICMapDisplayType == TRUE)
		strInfo += "<Run Foreground='red' FontWeight='Normal'>[인터콜지도오픈]</Run> ";
	if(m_bUseHomepage == TRUE)
		strInfo += "<Run Foreground='red' FontWeight='Normal'>[홈페이지사용]</Run> ";
	if(m_bPreventPosUpdate == TRUE)
		strInfo += "<Run Foreground='red' FontWeight='Normal'>[고객위치기사변경불가]</Run> ";

	CString strTemp;

	if(m_cmbPriceGrade.GetCurSel() >= 0)
	{
		strTemp = ""; m_cmbPriceGrade.GetLBText(m_cmbPriceGrade.GetCurSel(), strTemp);
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[가격:" + strTemp + "]</Run> ";
	}

	if(atoi(m_strDiscount) > 0)
	{
		strTemp = ""; m_cmbDiscount.GetLBText(m_cmbDiscount.GetCurSel(), strTemp);
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[할인:" + strTemp + "," + m_strDiscount + "]</Run> ";
	}

	if(atoi(m_strCoupon) > 0)
	{
		strTemp = ""; m_cmbCoupon.GetLBText(m_cmbCoupon.GetCurSel(), strTemp);
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[쿠폰:" + strTemp + "," + m_strCoupon + "]</Run> ";
	}

	if(atoi(m_strMileage) > 0)
	{
		strTemp = ""; m_cmbMileage.GetLBText(m_cmbMileage.GetCurSel(), strTemp);
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[마일:" + strTemp + "," + m_strMileage + "]</Run> ";
	}

	if(m_strLoginID.IsEmpty() == FALSE && m_strLoginPW.IsEmpty() == FALSE)
	{		
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[ID:" + m_strLoginID + ", PW:" + m_strLoginPW + "]</Run> ";
	}

	if(m_strEMail.IsEmpty() == FALSE)
	{		
		strInfo += "<Run Foreground='blue' FontWeight='Normal'>[E-Mail:" + m_strEMail + "]</Run> ";
	}

	strInfo = "<TextBlock FontFamily='Microsoft YaHei' HorizontalAlignment='Left' VerticalAlignment='Center'> " + strInfo ;
	strInfo += "</TextBlock>";

	return strInfo;

	return "";
}

void CCustomerDlgSub2::OnCbnSelchangePriceGradeCombo()
{
	m_pCustomerDlg->m_bDirty = TRUE;
	m_pCustomerDlg->OnCbnSelchangePriceGradeCombo();
	SelChangeOption();
}

void CCustomerDlgSub2::OnCbnSelchangeCouponCombo()
{
	m_pCustomerDlg->m_bDirty = TRUE;
	SelChangeOption();
}

void CCustomerDlgSub2::OnCbnSelchangeMileageCombo()
{
	m_pCustomerDlg->m_bDirty = TRUE;
	SelChangeOption();
}


void CCustomerDlgSub2::OnBnClickedSendStateChangeSmsCheck()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnBnClickedIcMapDisplayTypeChk()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnBnClickedUseHomepageCheck()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnBnClickedPreventPosUpdateCheck()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeDiscountEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeMileageEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeCouponEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeLoginIdEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeLoginPwEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeEmailEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnCbnSelchangeCustomerGradeCombo()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnCbnSelchangeAllocGroupCombo()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	FillDataSalesMan();
	FindSalesMan();
}

void CCustomerDlgSub2::FindSalesMan()
{
	BOOL bFind = FALSE;

	for(int i=ZERO; i<m_cmbSalesTeam.GetCount(); i++)
	{
		SALES_SIMPLE_INFO *pData = (SALES_SIMPLE_INFO*)m_cmbSalesTeam.GetItemData(i);

		if(pData == NULL)
			continue;

		if(pData->nCompany == m_nSalesCompany &&
			pData->nWNo == m_nSalesWNo)
		{
			bFind = TRUE;
			m_cmbSalesTeam.SetCurSel(i);
			break;
		}
	}

	if(bFind == FALSE)
	{
		m_dtpSalesTime.EnableWindow(FALSE);
		m_cmbSalesTeam.SetCurSel(ZERO);
	}
	else
		m_dtpSalesTime.EnableWindow(TRUE);
}

void CCustomerDlgSub2::DeleteSalesCombo()
{
	for(int i=ZERO; i<m_cmbSalesTeam.GetCount(); i++)
	{
		SALES_SIMPLE_INFO *pData = (SALES_SIMPLE_INFO*)m_cmbSalesTeam.GetItemData(i);

		if(pData != NULL)
		{
			delete pData;
			pData = NULL;
		}
	}

	m_cmbSalesTeam.ResetContent();	
}

void CCustomerDlgSub2::FillDataSalesMan()
{
	DeleteSalesCombo();

	m_cmbSalesTeam.InsertString(0, "없음");

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_wno_sales_team");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	CString strTemp;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		SALES_SIMPLE_INFO *st = new SALES_SIMPLE_INFO;

		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("nWNo", st->nWNo);
		pRs.GetFieldValue("sWName", st->strWName);

		strTemp.Format("[%d %s]", st->nWNo, st->strWName);

		m_cmbSalesTeam.InsertString(i + ONE, strTemp);
		m_cmbSalesTeam.SetItemData(i + ONE, (DWORD_PTR)st);

		pRs.MoveNext();
	}
}

void CCustomerDlgSub2::OnCbnSelchangeSalesTeamCombo()
{
	long nIndex = m_cmbSalesTeam.GetCurSel();

	SALES_SIMPLE_INFO *pData = (SALES_SIMPLE_INFO*)m_cmbSalesTeam.GetItemData(nIndex);

	if(pData == NULL)
	{
		m_nSalesCompany = 0;
		m_nSalesWNo = 0;
		m_dtpSalesTime.EnableWindow(FALSE);
	}
	else
	{
		m_nSalesCompany = pData->nCompany;
		m_nSalesWNo = pData->nWNo;
		m_dtpSalesTime.EnableWindow(TRUE);
	}
}
void CCustomerDlgSub2::SetCompanyCharge(long nMemCNo)
{

	if(nMemCNo <= 0)
	{
		m_cmbCompanyCharge.SetCurSel(0);
		return;
	}
	for(int i = 0; i < m_cmbCompanyCharge.GetCount(); i++)
	{
		long nOldMemCNo = m_cmbCompanyCharge.GetItemData(i);
		if(nOldMemCNo == nMemCNo)
		{
			m_cmbCompanyCharge.SetCurSel(i);
			return;
		}
	}
	m_cmbCompanyCharge.SetCurSel(0);
}


void CCustomerDlgSub2::OnBnClickedApplyCompanyChargeBtn()
{
	long nMemCNo = m_cmbCompanyCharge.GetItemData(m_cmbCompanyCharge.GetCurSel());	
	if(nMemCNo == 0)
	{
		if( MessageBox("업체요금의 설정을 빼시겟습니까?.", "확인", MB_YESNO ) == IDNO )
			return;
	}
	if(nMemCNo < 0)
		return;

	m_pCustomerDlg->SetCompanyApplyCharge(nMemCNo);
}

void CCustomerDlgSub2::OnBnClickedLoadCompanyChargeBtn()
{
	if(LU->LoadMemberCharge() )
	{
		LU->FillCompanyChargeList(&m_cmbCompanyCharge);
	}
}

void CCustomerDlgSub2::OnBnClickedOnlinePopupCheck()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub2::OnEnChangeOnlinePopupChargeEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}
