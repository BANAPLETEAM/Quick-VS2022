// MakeGroupReportNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MakeGroupReportNewDlg.h"
#include "CommonDateDlg1.h"
#include "UnBillDlg.h"
#include "MakeGroupReportSendDlg.h"
#include "AddGroupDlg.h"
#include <math.h>


#define  REPORT_DATE_COLUMN 2


// CMakeGroupReportNewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMakeGroupReportNewDlg, CMyDialog)
CMakeGroupReportNewDlg::CMakeGroupReportNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMakeGroupReportNewDlg::IDD, pParent)
{
	m_nGNo = 0;
	m_bRefresh = FALSE;
	m_strGNoList = "";
	m_nCalculateCount  = 0;
	m_nCalculateSum= 0;
	m_nCalculateTrans= 0;
	m_nGroupReportID = 0;
	m_nNewMode = 0;
	m_dtBillCollection = COleDateTime::GetCurrentTime();
	m_dtPayMent = COleDateTime::GetCurrentTime();
	
}

CMakeGroupReportNewDlg::~CMakeGroupReportNewDlg()
{
}

void CMakeGroupReportNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	
	DDX_Control(pDX, IDC_NO_EDIT, m_edtReportNo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);

	DDX_DateTimeCtrl(pDX, IDC_BILL_PRESS_DATETIMEPICKER, m_dtBillCollection);
	DDX_DateTimeCtrl(pDX, IDC_PAYMENT_DATETIMEPICKER1, m_dtPayMent);

	DDX_Control(pDX, IDC_BILL_PRESS_DATETIMEPICKER, m_dtpBillCollection);
	DDX_Control(pDX, IDC_PAYMENT_DATETIMEPICKER1, m_dtpPayMent);

	DDX_Control(pDX, IDC_PAYMENT_CHECK, m_chkPayMent);
	DDX_Control(pDX, IDC_BILLPRESS_CHECK, m_chkBillPressCollection);

	
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_CREDIT_EDIT, m_edtCredit);
	DDX_Control(pDX, IDC_DISCOUNT_CHARGE_EDIT, m_edtDiscountCharge);
	DDX_Control(pDX, IDC_SUB_SUM_EDIT, m_edtSubToal);
	DDX_Control(pDX, IDC_TRANS_CHARGE_EDIT, m_edtTransCharge);
	DDX_Control(pDX, IDC_BILL_TOTAL_CHARGE_EDIT, m_edtBillTotal);
	DDX_Control(pDX, IDC_TAX_EDIT, m_edtTax);
	DDX_Control(pDX, IDC_UNCOLLECTION_EDIT, m_edtUncollection);
	
	DDX_Control(pDX, IDC_COUNT_EDIT, m_edtCount);
	DDX_Control(pDX, IDC_DISCOUNT_EDIT, m_edtDiscount);
	DDX_Control(pDX, IDC_REPORT_FIRST_DAY_COMBO, m_cmbReportFirst);
	
	DDX_Control(pDX, IDC_ADDTAX_APPLYTYPE_COMBO, m_cmbAddTaxApplyType);
	
	DDX_Control(pDX, IDC_GROUP_EDIT, m_edtGroupName);
	DDX_Control(pDX, IDC_MANAGER_EDIT, m_edtGroupManager);
	DDX_Control(pDX, IDC_MANAGER_HP_EDIT, m_edtGroupManagerHP);
	DDX_Control(pDX, IDC_MANAGER_EMAIL_EDIT, m_edtEmail);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);

	DDX_Control(pDX, IDC_SMS_SEND_CHECK, m_chkSMSSend);
	DDX_Control(pDX, IDC_EMAIL_SEND_CHECK, m_chkEmailSend);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_TEST_SEND_CHECK, m_chkTestEmail); 


}


BEGIN_MESSAGE_MAP(CMakeGroupReportNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MAKE_BTN, OnBnClickedMakeBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	//ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
	ON_COMMAND(ID_CHANGE_DATE, OnChangeDate)
	ON_WM_CONTEXTMENU()
	
	ON_BN_CLICKED(IDC_ETC_SAVE_BTN, &CMakeGroupReportNewDlg::OnBnClickedEtcSaveBtn)
	
	ON_BN_CLICKED(IDC_SEND_TAX_VIEW_BTN, &CMakeGroupReportNewDlg::OnBnClickedSendTaxViewBtn)
	ON_BN_CLICKED(IDC_TEST_MAIL_BTN, &CMakeGroupReportNewDlg::OnBnClickedTestMailBtn)
	ON_BN_CLICKED(IDC_GROUP_SETTING_BTN, &CMakeGroupReportNewDlg::OnBnClickedGroupSettingBtn)
	ON_EN_CHANGE(IDC_DISCOUNT_CHARGE_EDIT, &CMakeGroupReportNewDlg::OnEnChangeDiscountChargeEdit)
	ON_CBN_SELCHANGE(IDC_ADDTAX_APPLYTYPE_COMBO, &CMakeGroupReportNewDlg::OnCbnSelchangeAddtaxApplytypeCombo)
	ON_BN_CLICKED(IDC_BILLPRESS_CHECK, &CMakeGroupReportNewDlg::OnBnClickedBillpressCheck)
	ON_BN_CLICKED(IDC_PAYMENT_CHECK, &CMakeGroupReportNewDlg::OnBnClickedPaymentCheck)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMakeGroupReportNewDlg 메시지 처리기입니다.

BOOL CMakeGroupReportNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	int nCol = 0;

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	//m_btnDate.OnMenuWeek();
	m_lstReport.InsertColumn(nCol++, "No", LVCFMT_CENTER, 50);
	
	m_lstReport.InsertColumn(nCol++, "본/지", LVCFMT_LEFT, 40);
	m_lstReport.InsertColumn(REPORT_DATE_COLUMN, "생성일", LVCFMT_CENTER, 70);
	nCol++;
	m_lstReport.InsertColumn(nCol++, "정산일자", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(nCol++, "상태", LVCFMT_CENTER, 60);
	

	m_lstReport.InsertColumn(nCol++, "건수", LVCFMT_RIGHT, 35);
	m_lstReport.InsertColumn(nCol++, "신용금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(nCol++, "할인금", LVCFMT_RIGHT, 50);
	m_lstReport.InsertColumn(nCol++, "탁송료", LVCFMT_RIGHT, 50);
	
	m_lstReport.InsertColumn(nCol++, "공급가", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(nCol++, "세액", LVCFMT_RIGHT, 50);
	m_lstReport.InsertColumn(nCol++, "총합계", LVCFMT_RIGHT, 70);

	m_lstReport.InsertColumn(nCol++, "문자", LVCFMT_CENTER, 40);	
	m_lstReport.InsertColumn(nCol++, "메일", LVCFMT_CENTER, 40);	
	m_lstReport.InsertColumn(nCol++, "전자계산서", LVCFMT_CENTER, 40);	
	m_lstReport.InsertColumn(nCol++, "작업자", LVCFMT_CENTER, 60);
	m_lstReport.Populate();

	UpdateData();

	m_edtCredit.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtCredit.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");

	m_edtDiscountCharge.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtDiscountCharge.SetUserOption(RGB(0, 0, 0), RGB(255,180,180), "");

	m_edtSubToal.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtSubToal.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");
	m_edtTransCharge.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtTransCharge.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");

	m_edtBillTotal.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtBillTotal.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");
	m_edtTax.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtTax.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");

	m_edtUncollection.SetMyFont("맑은 고딕", 19, FW_BOLD);
	m_edtUncollection.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");
	
	m_edtCount.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtCount.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");

	m_edtDiscount.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtDiscount.SetUserOption(RGB(0, 0, 0), RGB(194,245,153), "");
	

	m_chkPayMent.SetCheck(TRUE);
	m_dtpPayMent.EnableWindow(TRUE);

	m_chkBillPressCollection.SetCheck(TRUE);
	m_dtpBillCollection.EnableWindow(TRUE);

	if(m_nNewMode)
		MakeReport();
	else
		LoadReport();

	RefreshList();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMakeGroupReportNewDlg::ReInit()
{

	m_nGNo = 0;
	m_bRefresh = FALSE;
	m_strGNoList = "";
	m_nCalculateCount  = 0;
	m_nCalculateSum= 0;
	m_nCalculateTrans= 0;
	m_nGroupReportID = 0;
	m_nNewMode = 0;

}

void CMakeGroupReportNewDlg::LoadReport()
{

	UpdateData();


	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report_nID");
	pCmd.AddParameter(m_nGroupReportID);
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() <= 0)
		return;

	COleDateTime dtReportStart(COleDateTime::GetCurrentTime());
	COleDateTime dtReportEnd(COleDateTime::GetCurrentTime());
	COleDateTime dtPayMent, dtBillCollection;

	long nDisCount = 0, nFirstReportDay = 0,nAddTaxApplyType = 0, nDisCountCharge = 0;
	long nSubSum = 0, nBillTotal = 0, nTax = 0, nUncollection = 0, nDiscount = 0;
	long nGroupReportID = 0;
	CString strGroupName = "", strManager = "", strManagerHP = "", strEmail = "", strEtc = "";
	CString strReportID = "";
	nSubSum = m_nCalculateSum; 



	pRs.GetFieldValue("nID", nGroupReportID);
	pRs.GetFieldValue("nGNo", m_nGNo);		
	pRs.GetFieldValue("sGroupName", strGroupName); 
	//pRs.GetFieldValue("sDept", strDept); 
	pRs.GetFieldValue("dtReportStart", dtReportStart);		
	pRs.GetFieldValue("dtReportEnd", dtReportEnd); 		
	//pRs.GetFieldValue("nReportState", nReportState);
	//pRs.GetFieldValue("dtCreate", dtCreate);
	pRs.GetFieldValue("nDiscount", nDiscount);
	pRs.GetFieldValue("nCreditCount", m_nCalculateCount);
	pRs.GetFieldValue("nCreditCharge", m_nCalculateSum);
	pRs.GetFieldValue("nTransCharge", m_nCalculateTrans);
	pRs.GetFieldValue("nDiscountCharge", nDisCountCharge);
	pRs.GetFieldValue("nBillTotalCharge", nBillTotal);
	pRs.GetFieldValue("nCreditTax", nTax);
	pRs.GetFieldValue("nUnCollection", nUncollection);
	
	pRs.GetFieldValue("dtPayMent", dtPayMent);
	pRs.GetFieldValue("dtBillCollection", dtBillCollection);	
	pRs.GetFieldValue("sEtc", strEtc);
	pRs.GetFieldValue("nAddTaxApplyType", nAddTaxApplyType);
	
	if(IsTimeValid(dtPayMent))
	{
		m_chkPayMent.SetCheck(TRUE);
		m_dtPayMent = dtPayMent;
	}
	else
	{
		m_chkPayMent.SetCheck(FALSE);
		m_dtpPayMent.EnableWindow(FALSE);
	}
	if(IsTimeValid(dtBillCollection))
	{
		m_chkBillPressCollection.SetCheck(TRUE);
		m_dtBillCollection = dtBillCollection;
	}
	else
	{
		m_chkBillPressCollection.SetCheck(FALSE);
		m_dtpBillCollection.EnableWindow(FALSE);
	}


	strReportID.Format("%d", nGroupReportID);

	if(dtReportStart.m_status != COleDateTime::valid)
	{
		LF->MsgBox("리포트의 시작일이 날자형식에 어긋납니다");
		return;
	}
	if(dtReportEnd.m_status != COleDateTime::valid)
	{
		LF->MsgBox("리포트의 시작일이 날자형식에 어긋납니다");
		return;
	}

	m_dtFrom = dtReportStart;
	m_dtTo = dtReportEnd;

	

	if(m_nGNo > 0)
	{
		if(m_nCalculateSum <= 0 )
			nDisCount = 0;
		else
			nDisCount = nDisCountCharge / m_nCalculateSum  * 100 ; //m_cg.GetGroupData(m_nGNo)->nDiscount;

		nFirstReportDay = m_cg.GetGroupData(m_nGNo)->nReportFirstDay;		
		nSubSum = m_nCalculateSum - nDisCountCharge;
		strGroupName = m_cg.GetGroupData(m_nGNo)->strGroupName;
		strManager = m_cg.GetGroupData(m_nGNo)->strName;
		//strManagerHP = m_cg.GetGroupData(m_nGNo)->strManagerHP;
		strEmail = m_cg.GetGroupData(m_nGNo)->strEmail;

	}	
	nBillTotal = nSubSum + m_nCalculateTrans;

	m_cmbAddTaxApplyType.SetCurSel(nAddTaxApplyType);

	m_edtReportNo.SetWindowText(strReportID);
	m_edtCredit.SetWindowText(LF->GetMyNumberFormat(m_nCalculateSum));
	m_edtDiscount.SetWindowText(LF->GetMyNumberFormat(nDiscount));	
	m_edtDiscountCharge.SetWindowText(LF->GetMyNumberFormat(nDisCountCharge));	
	m_edtSubToal.SetWindowText(LF->GetMyNumberFormat(nSubSum));
	m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(m_nCalculateTrans));	
	m_edtBillTotal.SetWindowText(LF->GetMyNumberFormat(nBillTotal));
	m_edtTax.SetWindowText(LF->GetMyNumberFormat(nTax));
	m_edtUncollection.SetWindowText(LF->GetMyNumberFormat(nUncollection));
	m_edtCount.SetWindowText(LF->GetMyNumberFormat(m_nCalculateCount));
	

	m_cmbReportFirst.SetCurSel(nFirstReportDay);
	m_cmbAddTaxApplyType.SetCurSel(nAddTaxApplyType);


	m_edtGroupName.SetWindowText(strGroupName);
	m_edtGroupManager.SetWindowText(strManager);
	m_edtGroupManagerHP.SetWindowText(LF->GetDashPhoneNumber(strManagerHP));
	m_edtEmail.SetWindowText(strEmail);
	m_edtEtc.SetWindowText(strEtc);




	UpdateData(FALSE);

}
BOOL CMakeGroupReportNewDlg::IsTimeValid(COleDateTime dt)
{

	if(dt.GetStatus() == COleDateTime::valid && dt.GetStatus() != COleDateTime::null)
		return TRUE;
	return FALSE;

}

void CMakeGroupReportNewDlg::ChangeReport()
{
	CString strDiscountCharge = "";
	long nDiscountCharge  = 0;
	

	m_edtDiscountCharge.GetWindowText(strDiscountCharge);
	strDiscountCharge.Replace(",", "");
	if(!LF->IsNumeric(strDiscountCharge))
	{
		m_edtDiscountCharge.SetWindowText("");
		LF->MsgBox("할인금액을 숫자로 입력하세요");
		return;
	}

	long nCreditCharge = 0,nSubSum = 0 , nCalculateTrans = 0, nBillTotal = 0, 
		nTax = 0, nUnCollection = 0,nAddTaxApplyType = 0 ;
	nCreditCharge = GetEditTextByLong(&m_edtCredit);
	nDiscountCharge = GetEditTextByLong(&m_edtDiscountCharge);
	nCalculateTrans = GetEditTextByLong(&m_edtTransCharge);
	nAddTaxApplyType =m_cmbAddTaxApplyType.GetCurSel();

	nSubSum = nCreditCharge - nDiscountCharge;
    nBillTotal = nSubSum + nCalculateTrans;
	if(nAddTaxApplyType == 0)
		nTax = 0;
	else if(nAddTaxApplyType == 1)
	{
		nBillTotal = round( nBillTotal / 1.1, 1);
		nTax = (nSubSum + m_nCalculateTrans ) - nBillTotal;
	}	
	else if(nAddTaxApplyType  == 2)
	{
		nTax = int(nBillTotal * 0.1);
	}
	else if(nAddTaxApplyType == 3)
	{
		long nTempCharge = 0;
		nTax = int( nBillTotal * 0.1);
		nTempCharge = round(nBillTotal + nTax, 0);
		nTax = nTempCharge - nBillTotal;

	}
	nUnCollection = nBillTotal + nTax;

	
	
	m_edtSubToal.SetWindowText(LF->GetMyNumberFormat(nSubSum));	
	m_edtBillTotal.SetWindowText(LF->GetMyNumberFormat(nBillTotal));
	m_edtTax.SetWindowText(LF->GetMyNumberFormat(nTax));
	m_edtUncollection.SetWindowText(LF->GetMyNumberFormat(nUnCollection));

}


void CMakeGroupReportNewDlg::MakeReport()
{

	UpdateData();

	long nDisCount = 0, nFirstReportDay = 0,nAddTaxApplyType = 0, nDisCountCharge = 0;
	long nSubSum = 0, nBillTotal = 0, nTax = 0, nUncollection = 0, nPayMentAdd = 0, nBillCollectionAdd = 0;
	CString strGroupName = "", strManager = "", strManagerHP = "", strEmail = "", strEtc = "";
	COleDateTimeSpan dtSpanPayMent, dtSpanBillCollectionAdd;
	nSubSum = m_nCalculateSum; 


	if(m_nGNo > 0)
	{
		nDisCount = m_cg.GetGroupData(m_nGNo)->nDiscount;
		nFirstReportDay = m_cg.GetGroupData(m_nGNo)->nReportFirstDay;
		nAddTaxApplyType  =  m_cg.GetGroupData(m_nGNo)->nAddTaxApplyType;
		nDisCountCharge = round(m_nCalculateSum * 0.01 * nDisCount, 1);
		nSubSum = m_nCalculateSum - nDisCountCharge;
		nAddTaxApplyType = m_cg.GetGroupData(m_nGNo)->nAddTaxApplyType;

		strGroupName = m_cg.GetGroupData(m_nGNo)->strGroupName;
		strManager = m_cg.GetGroupData(m_nGNo)->strName;
		//strManagerHP = m_cg.GetGroupData(m_nGNo)->strManagerHP;
		strEmail = m_cg.GetGroupData(m_nGNo)->strEmail;

	}
	strEtc = "";
	nBillTotal = nSubSum + m_nCalculateTrans;
	if(nAddTaxApplyType == 1)
	{
		nBillTotal = round( nBillTotal / 1.1, 1);
		nTax = (nSubSum + m_nCalculateTrans ) - nBillTotal;
	}
	else if(nAddTaxApplyType  == 2)
	{
		nTax = int(nBillTotal * 0.1);
	}
	else if(nAddTaxApplyType  == 3)
	{
		long nTempCharge = 0;
		nTax = int( nBillTotal * 0.1);
		nTempCharge = round(nBillTotal + nTax, 0);
		nTax = nTempCharge - nBillTotal;

		//nTax = round(nBillTotal * 0.1, 0);
	}

	nUncollection = nBillTotal + nTax;

	if(m_nGNo > 0 )
	{
		nPayMentAdd = m_cg.GetGroupData(m_nGNo)->nPayMentAdd;
		if(nPayMentAdd > 0)
		{
			dtSpanPayMent.SetDateTimeSpan(nPayMentAdd, 0,0,0);
			m_dtPayMent = m_dtTo + dtSpanPayMent;			
		}

		nBillCollectionAdd = m_cg.GetGroupData(m_nGNo)->nBillCollectionAdd;
		if(nBillCollectionAdd > 0)
		{
			dtSpanBillCollectionAdd.SetDateTimeSpan(nBillCollectionAdd,0,0,0);
			m_dtBillCollection = m_dtTo + dtSpanBillCollectionAdd;
		}		
	}

	m_edtCredit.SetWindowText(LF->GetMyNumberFormat(m_nCalculateSum));
	m_edtDiscountCharge.SetWindowText(LF->GetMyNumberFormat(nDisCountCharge));	
	m_edtSubToal.SetWindowText(LF->GetMyNumberFormat(nSubSum));
	m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(m_nCalculateTrans));	
	m_edtBillTotal.SetWindowText(LF->GetMyNumberFormat(nBillTotal));
	m_edtTax.SetWindowText(LF->GetMyNumberFormat(nTax));
	m_edtUncollection.SetWindowText(LF->GetMyNumberFormat(nUncollection));

	m_edtCount.SetWindowText(LF->GetMyNumberFormat(m_nCalculateCount));
	m_edtDiscount.SetWindowText(LF->GetMyNumberFormat(nDisCount));

	m_cmbReportFirst.SetCurSel(nFirstReportDay);
	m_cmbAddTaxApplyType.SetCurSel(nAddTaxApplyType);


	m_edtGroupName.SetWindowText(strGroupName);
	m_edtGroupManager.SetWindowText(strManager);
	m_edtGroupManagerHP.SetWindowText(LF->GetDashPhoneNumber(strManagerHP));
	m_edtEmail.SetWindowText(strEmail);
	m_edtEtc.SetWindowText(strEtc);




	UpdateData(FALSE);

}



double CMakeGroupReportNewDlg::round( double value, int pos )
{

	double temp;

	if(pos <= 0)
		pos = pos * 1 + -1;


	temp = value * pow( (double)10, pos );  // 원하는 소수점 자리수만큼 10의 누승을 함

	// 0.5를 더한후 버림하면 반올림이 됨
	if(pos > 0)
		temp = floor(temp + 5 );
	else
		temp = floor( temp + 0.5 );          // 0.5를 더한후 버림하면 반올림이 됨

	temp *= pow( (double)10, -pos );           // 다시 원래 소수점 자리수로

	return temp;

}

void CMakeGroupReportNewDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report");

	pCmd.AddParameter(m_nGNo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtReportStart, dtReportEnd, dtCreate, dtSendSMS, dtSendEmail, dtSendBill;
	long nReportState, nID, nGNo, nException;
	long nCreditCount, nCreditCharge, nTransCharge, nUnCollection;
	long nDiscountCharge,nBillTotalCharge,nCreditTax;
	BOOL bPressBill; int nCol; char buffer[10];
	CString sWName, strIntegrated, sSendSMS, sSendBill, sSendEmail;


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		nCol = 1;

		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("dtCreate", dtCreate);
		pRs.GetFieldValue("nException", nException);
		pRs.GetFieldValue("sWName", sWName);		
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);	

		pRs.GetFieldValue("nCreditCount", nCreditCount);	
		pRs.GetFieldValue("nCreditCharge", nCreditCharge);	
		pRs.GetFieldValue("nTransCharge", nTransCharge);	

		pRs.GetFieldValue("nDiscountCharge", nDiscountCharge);	
		pRs.GetFieldValue("nBillTotalCharge", nBillTotalCharge);	
		pRs.GetFieldValue("nCreditTax", nCreditTax);		

		pRs.GetFieldValue("nUnCollection", nUnCollection);	
		pRs.GetFieldValue("bPressBill", bPressBill);	

		pRs.GetFieldValue("dtSendSMS", dtSendSMS);	
		pRs.GetFieldValue("dtSendEmail", dtSendEmail);	
		pRs.GetFieldValue("dtSendEmail", dtSendBill);	

		if(m_cg.GetGroupData(nGNo)->nParentGNo == 0)
			strIntegrated = "(본)" + m_cg.GetGroupData(nGNo)->strDept;
		else
			strIntegrated = "(지)" + m_cg.GetGroupData(nGNo)->strDept;

		sSendSMS = (dtSendSMS.valid == COleDateTime::valid) ? dtSendSMS.Format("%m/%d") : "";
		sSendEmail = (dtSendSMS.valid == COleDateTime::valid) ? dtSendEmail.Format("%m/%d") : "";
		sSendBill = (dtSendSMS.valid == COleDateTime::valid) ? dtSendBill.Format("%m/%d") : "";

		m_lstReport.InsertItem(i,  ltoa(nID, buffer,10));
		m_lstReport.SetItemText(i, nCol++, strIntegrated);
		m_lstReport.SetItemText(i, REPORT_DATE_COLUMN, dtCreate.Format("%Y-%m-%d"));
		nCol++;
		m_lstReport.SetItemText(i, nCol++, dtReportStart.Format("%y-%m-%d") + " ~ " + dtReportEnd.Format("%y-%m-%d"));
		m_lstReport.SetItemText(i, nCol++, LF->GetReportState(nReportState));
		
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nCreditCount));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nCreditCharge));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nDiscountCharge));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nTransCharge));
		
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nBillTotalCharge));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nCreditTax));		
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nUnCollection));			

		m_lstReport.SetItemText(i, nCol++, sSendSMS);			
		m_lstReport.SetItemText(i, nCol++, sSendEmail);			
		m_lstReport.SetItemText(i, nCol++, sSendBill);			
		m_lstReport.SetItemText(i, nCol++, sWName);			
		
		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemLong2(i, nGNo);

		m_lstReport.SetItemData(i, (long)nReportState);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}


void CMakeGroupReportNewDlg::OnBnClickedMakeBtn()
{
	UpdateData(TRUE);
	long nReportID = 0, nDiscountCharge = 0, nBillToatalCharge = 0,
		nTax = 0, nUnBillCollection = 0;
	CString strMsg ="", strEtc = "";
	if(m_chkSMSSend.GetCheck() )
		if(! SendKindReportCheckData(0) ) return;
	if(m_chkEmailSend.GetCheck())
		if(! SendKindReportCheckData(1) ) return;
	if(IsMake() )
		strMsg = "정산데이터를 생성하시겠습니까?";
	else
		strMsg = "정산데이터를 수정하시겠습니까?";

	if(MessageBox(strMsg, "확인", MB_YESNO) == IDNO)
			return;
	if(IsMake())
		if(CheckDate(m_dtFrom, m_dtTo) != TRUE )
			return;

	m_edtEtc.GetWindowText(strEtc);
	nDiscountCharge = GetEditTextByLong(&m_edtDiscountCharge);
	nBillToatalCharge = GetEditTextByLong(&m_edtBillTotal);
	nTax = GetEditTextByLong(&m_edtTax);
	nUnBillCollection = GetEditTextByLong(&m_edtUncollection);

	//CMkCommand pCmd(m_pMkDb, "make_customer_group_report3");
	CMkCommand pCmd(m_pMkDb, "make_customer_group_report_modify3");
	pCmd.AddParameter(m_nGNo);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strGroupName);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strDept);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strName);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->nCompany);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);
	pCmd.AddParameter(m_strGNoList);

	pCmd.AddParameter(nDiscountCharge);
	pCmd.AddParameter(nBillToatalCharge);
	pCmd.AddParameter(nTax);
	pCmd.AddParameter(nUnBillCollection);

	pCmd.AddParameter(m_chkPayMent.GetCheck());
	pCmd.AddParameter(m_dtPayMent);
	pCmd.AddParameter(m_chkBillPressCollection.GetCheck());
	pCmd.AddParameter(m_dtBillCollection);
	pCmd.AddParameter(m_cmbAddTaxApplyType.GetCurSel());
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(m_ui.strID);

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeInputOutput, sizeof(long), m_nGroupReportID);
	if(!pCmd.Execute()) return;

	pPar->GetValue(m_nGroupReportID);

	m_bRefresh = TRUE;
	BOOL bWithSend = FALSE;

	if(m_chkSMSSend.GetCheck())
		if(SendKindReport(0, FALSE, TRUE) )
			bWithSend = TRUE;
	if(m_chkEmailSend.GetCheck())
		if(SendKindReport(1, FALSE, TRUE) )
			bWithSend = TRUE;
	
	if(IsMake() )
	{
		if(bWithSend)
			LF->MsgBox("정산이 생성되었스며 동시발송작업이 완료되었습니다.", "확인", MB_ICONINFORMATION);
		else
			LF->MsgBox("정산이 생성되었습니다", "확인", MB_ICONINFORMATION);	
	}
	else
	{
		if(bWithSend)
			LF->MsgBox("정산이 수정되었스며 동시발송작업이 완료되었습니다.", "확인", MB_ICONINFORMATION);
		else
			LF->MsgBox("정산이 수정되었습니다", "확인", MB_ICONINFORMATION);
	}

	

	RefreshList();		
}

BOOL CMakeGroupReportNewDlg::SendKindReportCheckData(int nSendType)
{
	try
	{

		CString strContent = "", strMsg = "";
		if(nSendType == 0)
		{
			strMsg = "핸드폰 번호";

			m_edtGroupManagerHP.GetWindowText(strContent);
			strContent = LF->GetNoneDashNumber(strContent);
			if(strContent.GetLength() <= 9 )
				throw "전화번호의 길이가 9자 이하입니다.";

			if(strContent.Left(2).Compare("01") != 0  )
				throw "핸드폰 번호로 01로 시작되어야 합니다.";
		}
		else if(nSendType == 1 || nSendType == 2)
		{
			strMsg = "이메일";
			m_edtEmail.GetWindowText(strContent);

			if( !(strContent.Find("@", 0) > 2 ) )
				throw "이메일에 @가없습니다";

			if(strContent.GetLength() <= 5 )
				throw "이메일의 길이가 5자 이하입니다. ";


		}

		if(strContent.GetLength() < 5)
		{
			LF->MsgBox("담당자의 " + strMsg  +"이(가) 없거나 번호기 길이가 5자이하 입니다");
			return FALSE;
		}

		if(m_ui.strTaxUseEmail.GetLength() <= 0 )
		{
			LF->MsgBox("옵션의 기타항목에 세금계산서 관련한 Email을 입력하여주세요");
			return FALSE;
		}


		return TRUE;
	}	
	catch (char *str)
	{

		LF->MsgBox(str);
		return FALSE;
	}
	

	return FALSE;
}

BOOL CMakeGroupReportNewDlg::SendKindReport(int nSendType,  BOOL bReSend, BOOL nAutoSend)
{

	if(nSendType == 0 )
	{

		CString strReportManagerPhone = "";
		m_edtGroupManagerHP.GetWindowText(strReportManagerPhone);

		CMkCommand pCmd(m_pMkDb, "send_sms_group_report");
		pCmd.AddParameter(m_nGNo);
		pCmd.AddParameter(m_nGroupReportID);
		pCmd.AddParameter(strReportManagerPhone);
		pCmd.AddParameter(nSendType);
		pCmd.AddParameter(FALSE); //m_rdoInnerBill.GetCheck());
		pCmd.AddParameter(bReSend);		
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!pCmd.Execute()) return FALSE;

		if(!nAutoSend)
			LF->MsgBox("발송하였습니다");
		int nSuccess = FALSE;
		pPar->GetValue(nSuccess);
	}
	else
	{
		SendKindReportWeb(nSendType, bReSend);

	
	}
	

	

		

	int nSuccess =0;

	return nSuccess;	

}


void CMakeGroupReportNewDlg::OnBnClickedSendTaxViewBtn()
{
	if(IsMake())
	{
		LF->MsgBox("정산생성후 보실수 있습니다" );
		return;
	}
	SendKindReportWeb(1, FALSE);
}



HRESULT CMakeGroupReportNewDlg::GetPostData(CString strKey, LPVARIANT pvPostData)
{
	HRESULT hr;
	LPSAFEARRAY psa;

	CString PostInfo= strKey;
	LPCTSTR cszPostData = (LPCTSTR)PostInfo;
	UINT cElems = lstrlen(cszPostData);
	LPSTR pPostData;

	if (!pvPostData)
	{
		return E_POINTER;
	}

	VariantInit(pvPostData);

	psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
	if (!psa)
	{
		return E_OUTOFMEMORY;
	}

	hr = SafeArrayAccessData(psa, (LPVOID*)&pPostData);
	memcpy(pPostData, cszPostData, cElems);
	hr = SafeArrayUnaccessData(psa);

	V_VT(pvPostData) = VT_ARRAY | VT_UI1;
	V_ARRAY(pvPostData) = psa;
	return NOERROR;
}

void CMakeGroupReportNewDlg::SendKindReportWeb(int nSendType,  BOOL bReSend)
{
	CString strEmail = "";
	m_edtEmail.GetWindowText(strEmail);
	
	UpdateData();
	COleDateTime dt; 
	CMakeGroupReportSendDlg dlg;
	dlg.m_nGroupReportID = m_nGroupReportID;
	dlg.m_nGNo = m_nGNo;
	dlg.m_strEmail = strEmail.GetLength() > 0 ? strEmail : "";
	dlg.m_nTest = m_chkTestEmail.GetCheck() ? 1 : 0;
	dlg.m_bPayMent = m_chkPayMent.GetCheck();
	dlg.m_dtPayMent = m_chkPayMent.GetCheck() ? m_dtPayMent : dt;
	dlg.m_bBillCollection = m_chkBillPressCollection.GetCheck();
	dlg.m_dtBillCollection = m_chkBillPressCollection.GetCheck() ? m_dtBillCollection : dt;
	if(dlg.DoModal() == IDOK)
	{
		ReInit();
		ShowWindow(SW_HIDE);
	}
}



BOOL CMakeGroupReportNewDlg::CheckDate(COleDateTime dtFrom, COleDateTime dtTo, BOOL bContiune, long nRow)
{
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay(), 0, 0, 0);

	if(dtFrom > dtTo)
	{
		MessageBox("날짜를 다시 선택해 주세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CString sFrom, sTo;

	for(int i=0; i<m_lstReport.GetItemCount(); i++)
	{
		if((bContiune == TRUE) && (nRow == i))
			continue;

		BOOL bSame = FALSE;

		CXTPGridRow *pRow = m_lstReport.GetRows()->GetAt(i);
		

		CString sDate = m_lstReport.GetItemText(pRow->GetRecord(), REPORT_DATE_COLUMN +1 );
		
		if(sDate.GetLength() <= 0)
		{
			LF->MsgBox("정산데이터의 날자가 없습니다");
			return FALSE;
		}

		COleDateTime dtCompareFrom(_ttoi("20" + sDate.Left(2)), _ttoi(sDate.Mid(3, 2)), _ttoi(sDate.Mid(6 ,2)), 0, 0, 0);
		COleDateTime dtCompareTo(_ttoi("20" + sDate.Mid(11, 2)), _ttoi(sDate.Mid(14, 2)), _ttoi(sDate.Mid(17 ,2)), 0, 0, 0);

		if(((dtFrom >= dtCompareFrom ) && (dtFrom <= dtCompareTo)) ||
			((dtTo >= dtCompareFrom) && (dtTo <= dtCompareTo)))
			bSame = TRUE;


		if((dtFrom <= dtCompareFrom) && (dtTo >= dtCompareTo))
			bSame = TRUE;

		if(bSame)
		{
			MessageBox("정산일이 겹칩니다. 날짜를 다시 선택해 주세요", "확인", MB_ICONINFORMATION);
			//CXTPGridRow *pRow = m_lstReport.GetRows()->GetAt(i);
			//m_lstReport.GetSelectedRows()->Select(pRow);			
			return FALSE;
		}
	}

	return TRUE;
}

void CMakeGroupReportNewDlg::OnBnClickedCancelBtn()
{
	ReInit();
	OnOK();
}

void CMakeGroupReportNewDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(15);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

}

void CMakeGroupReportNewDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}

void CMakeGroupReportNewDlg::OnChangeDate()
{


	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;

	CXTPGridRow *pRow = pRows->GetAt(0);

	//CString sReportState = m_lstReport.GetItemText(pRow->GetIndex(), 1);
	long nReportState =(long) m_lstReport.GetItemData(pRow->GetRecord());



	//if(sReportState == "입금완료" || sReportState == "부분입금")
	if(nReportState == 10 )
	{
		CString sMsg = "정산완료 상태에서만 날짜변경이 가능합니다\r\n\r\n작업을 계속하시려면 해당 오더삭제 후\r\n정산데이터 생성 후 수금액을 입금하세요";
		MessageBox(sMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CString sDate = m_lstReport.GetItemText(pRow->GetIndex(), REPORT_DATE_COLUMN+1);
	if(sDate.GetLength() <= 0)
	{
		LF->MsgBox("정산데이터의 날자가 없습니다");
		return;
	}
	COleDateTime dtFrom(_ttoi("20" + sDate.Left(2)), _ttoi(sDate.Mid(3, 2)), _ttoi(sDate.Mid(6 ,2)), 0, 0, 0);
	COleDateTime dtTo(_ttoi("20" + sDate.Mid(11, 2)), _ttoi(sDate.Mid(14, 2)), _ttoi(sDate.Mid(17 ,2)), 0, 0, 0);

	CCommonDateDlg1 dlg;
	dlg.m_dtFrom = dtFrom;
	dlg.m_dtTo = dtTo;

	if(dlg.DoModal() == IDOK)
	{
		if(CheckDate(dlg.m_dtFrom, dlg.m_dtTo, TRUE, pRow->GetIndex()) != TRUE) 
		{
			OnChangeDate();
			return;
		}

		long nID = m_lstReport.GetItemLong(pRow->GetIndex());

		CMkCommand pCmd(m_pMkDb, "change_group_report_date");
		pCmd.AddParameter(nID);
		pCmd.AddParameter(dlg.m_dtFrom);
		pCmd.AddParameter(dlg.m_dtTo);

		if(!pCmd.Execute())
			return;

		m_bRefresh = TRUE;
		RefreshList();
		MessageBox("정산일이 수정되었습니다\r\n자동으로 재정산이 일어 납니다", "확인", MB_ICONINFORMATION);
	}    
}

void CMakeGroupReportNewDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CUnBillDlg dlg;
	dlg.m_bAlone = TRUE;
	dlg.m_nID = m_lstReport.GetItemLong(pRow->GetIndex());
	dlg.m_nGNo = m_lstReport.GetItemLong2(pRow->GetIndex());

	dlg.DoModal();
}

void CMakeGroupReportNewDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	return;
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();

	long nReportID = m_lstReport.GetItemLong(pRecord);
	long nGNo  = m_lstReport.GetItemLong2(pRecord);
		
	if(nReportID <= 0)
		return;

	m_nGroupReportID = nReportID;
	m_nNewMode = FALSE;


	LoadReport();
}




void CMakeGroupReportNewDlg::OnBnClickedEtcSaveBtn()
{
	
	if(m_nGNo <= 0)
	{
		LF->MsgBox("그룹코드가 없습니다 다시시도하세요");
		return;
	}
	CString strManager = "", strManagerHP = "", strManagerEmail = "",
		strReportEtc = "";

	if(IsMake() && strReportEtc.GetLength() > 0)
	{
		LF->MsgBox("정산의 비고는 정산생성시 입력이 됩니다.");
		
		
	}

	m_edtGroupManager.GetWindowText(strManager);
	m_edtGroupManagerHP.GetWindowText(strManagerHP);
	m_edtEmail.GetWindowText(strManagerEmail);
	m_edtEtc.GetWindowText(strReportEtc);


	CMkCommand pCmd(m_pMkDb, "update_group_report_make_etc");
	pCmd.AddParameter(m_nGNo);
	pCmd.AddParameter(IsMake() ? 0 : m_nGroupReportID);
	pCmd.AddParameter(strManager);
	pCmd.AddParameter(strManagerHP);
	pCmd.AddParameter(strManagerEmail);
	pCmd.AddParameter(strReportEtc);
	
	if(!pCmd.Execute()) return;

	

	m_cg.GetGroupData(m_nGNo)->strName = strManager;
	m_cg.GetGroupData(m_nGNo)->strManagerHP = strManagerHP;
	m_cg.GetGroupData(m_nGNo)->strEmail = strManagerEmail;


	

}

BOOL CMakeGroupReportNewDlg::IsMake()
{

	if(m_nNewMode != 0 && m_nGroupReportID <= 0)
		return TRUE;
	
	return FALSE;
}

void CMakeGroupReportNewDlg::OnBnClickedTestMailBtn()
{

	LF->MsgBox("메일을 발송한것이 아니라 메일주소만 변경합니다.\n\r\n\r발송은 발송페이지에서 보냅니다.");

	m_edtEmail.SetWindowText(m_ui.strTaxUseEmail);
	m_chkTestEmail.SetCheck(TRUE);
}


long CMakeGroupReportNewDlg::GetEditTextByLong(CFlatEdit2 *pEdit)
{
	CString str;
	pEdit->GetWindowText(str);
	str.Replace(",", "");

	return _ttol(str);
}

void CMakeGroupReportNewDlg::OnBnClickedGroupSettingBtn()
{
	if(	m_nGNo <= 0 )
	{
		LF->MsgBox("그룹관련 정보가 없습니다.");
		return;
	}

	CAddGroupDlg dlg;
	dlg.m_nGNo = m_nGNo;
	dlg.m_bAdd = FALSE;
	if(dlg.DoModal())
	{
		if(dlg.m_bDirtyDiscount)
		{
			long nDiscountCharge = 0, nCreditCharge = 0, nDiscount = 0;
			nCreditCharge = GetEditTextByLong(&m_edtCredit);		
			nDiscount = dlg.m_nDirtyDiscount;
			
			nDiscountCharge = int(nCreditCharge * nDiscount * 0.1);			
			m_edtDiscountCharge.SetWindowText(LF->GetMyNumberFormat(nDiscountCharge));

			ChangeReport();
			
		}
		if(dlg.m_bDirtyTaxApply)
		{
			m_cmbAddTaxApplyType.SetCurSel(dlg.m_nDirtyTaxApply);
			ChangeReport();
		}
		
	}


}
void CMakeGroupReportNewDlg::OnEnChangeDiscountChargeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CMyDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeReport();

}

void CMakeGroupReportNewDlg::OnCbnSelchangeAddtaxApplytypeCombo()
{
	ChangeReport();
}

void CMakeGroupReportNewDlg::OnBnClickedBillpressCheck()
{
	m_dtpBillCollection.EnableWindow(m_chkBillPressCollection.GetCheck());
}

void CMakeGroupReportNewDlg::OnBnClickedPaymentCheck()
{
	m_dtpPayMent.EnableWindow(m_chkPayMent.GetCheck());
}

void CMakeGroupReportNewDlg::OnClose()
{
	ReInit();

	CMyDialog::OnClose();
}
