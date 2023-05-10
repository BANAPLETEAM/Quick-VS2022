// Report2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm20.h"

//#include ".ReportForm20.h"
#include "VarietyDlg1.h"

// CReportForm20 대화 상자입니다.

IMPLEMENT_DYNCREATE(CReportForm20, CMyFormView)
CReportForm20::CReportForm20()
	: CMyFormView(CReportForm20::IDD)
	, m_nMNo(0)
	, m_sName(_T(""))
	, m_bCash(TRUE)
	, m_bCredit(TRUE)
	, m_bOnline(TRUE)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_tmFrom= COleDateTime::GetCurrentTime() - span;
	m_tmTo = COleDateTime::GetCurrentTime();

	m_tmFrom.SetTime(0,0,0);
	m_tmTo.SetTime(23,59,59);
	
	m_dtLogFrom = COleDateTime::GetCurrentTime() - span;
	m_dtLogTo = COleDateTime::GetCurrentTime();

	m_dtLogFrom.SetTime(0,0,0);
	m_dtLogTo.SetTime(23,59,59);

	m_bLaterDisCount = FALSE;
	
	m_nRiderCompany = 0;
	m_bFirstRefreshList = TRUE;
}

CReportForm20::~CReportForm20()
{
}

void CReportForm20::DoDataExchange(CDataExchange* pDX)
{
	//"지원되지 않는 작업을 시도하였습니다." 에러인 경우에 아래 주석을 풀고 로그를 보면 위치를 정확히 알수 있음
	//#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d\n", TEXT(__FILE__), TEXT(__LINE__));DDX_Control(x, y, z);}

	CMyFormView::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_CUSTOM1, m_RiderList);
	DDX_Control(pDX, IDC_LIST_REPORT, m_OrderList);
	DDX_Control(pDX, IDC_LOG_LIST_REPORT, m_LogList);
	
	DDX_Check(pDX, IDC_CHECK1, m_bCash);
	DDX_Check(pDX, IDC_CHECK2, m_bCredit);
	DDX_Check(pDX, IDC_CHECK3, m_bOnline);

		DDX_Text(pDX, IDC_EDIT_MNO, m_nMNo);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_sName);

	DDX_Control(pDX, IDC_DATETIME_LOG_FROM,m_dtpFromLog );
	DDX_Control(pDX, IDC_DATETIME_LOG_TO,m_dtpToLog );
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_LOG_FROM,m_dtLogFrom );
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_LOG_TO, m_dtLogTo);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_tmFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_tmTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);


	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_DATE_BTN2, m_DateLogBtn);
	DDX_Control(pDX, IDC_COUPHON_COMBO, m_cmbCouphon);
	
	DDX_Control(pDX, IDC_RIDER_REFRESH_BTN, m_btnRiderRefresh);
	DDX_Control(pDX, IDC_CALCULATE_BTN, m_btnCalculate);
	DDX_Control(pDX, IDC_RECEIVE_BALANCE_BTN, m_btnInput);
	DDX_Control(pDX, IDC_CALCULATE_BTN3, m_btnOutput);
	DDX_Control(pDX, IDC_BUTTON_RIDER_FETCH, m_RefreshBtn);
	DDX_Control(pDX, IDC_BUTTON_RIDER_FETCH2, m_RefreshBtn2);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);

	DDX_Text(pDX, IDC_EDIT_DISRATE, m_strDisRate);
	DDX_Text(pDX, IDC_EDIT_CASHRATE, m_strCashRate);
	DDX_Control(pDX, IDC_EDIT_MNO, m_edtMNo);
	DDX_Control(pDX, IDC_EDIT_SNAME, m_edtSName);
	
	DDX_Control(pDX, IDC_EDIT_DISRATE, m_edtDisrate);
	DDX_Control(pDX, IDC_EDIT_CASHRATE, m_edtCashrate);
	DDX_Check(pDX, IDC_LATER_DISCOUNT_CHECK, m_bLaterDisCount);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	
	DDX_Control(pDX, IDC_LATER_DISCOUNT_CHECK, m_chkLaterDisCount);
}


BEGIN_MESSAGE_MAP(CReportForm20, CMyFormView)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_BUTTON_RIDER_FETCH, OnBnClickedButtonRiderFetch)
	ON_BN_CLICKED(IDC_BUTTON_RIDER_FETCH2, OnBnClickedButtonRiderFetch2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_VIEW_EXCEL2, OnViewExcel2)
	ON_COMMAND(ID_VIEW_EXCEL3, OnViewExcel3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REPORT, OnReportItemRClick)
	ON_NOTIFY(NM_RCLICK, IDC_LOG_LIST_REPORT, OnReportItemLogRClick)
	ON_NOTIFY(NM_RCLICK, IDC_CUSTOM1, OnReportItemCustomRClick)
	ON_BN_CLICKED(IDC_TODAY_BTN, OnBnClickedTodayBtn)
	ON_BN_CLICKED(IDC_CALCULATE_BTN, OnBnClickedCalculateBtn)
	ON_BN_CLICKED(IDC_RECEIVE_BALANCE_BTN, OnBnClickedReceiveBalanceBtn)
	ON_BN_CLICKED(IDC_CALCULATE_BTN3, OnBnClickedCalculateBtn3)
	ON_CBN_SELCHANGE(IDC_COUPHON_COMBO, OnCbnSelchangeCouphonCombo)
	ON_BN_CLICKED(IDC_RIDER_REFRESH_BTN, OnBnClickedRiderRefreshBtn)
END_MESSAGE_MAP()

// CReportForm20 메시지 처리기입니다.

void CReportForm20::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	UpdateData();
	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	m_DateLogBtn.InitDateButton(&m_dtpFromLog, &m_dtpToLog);
	m_DateLogBtn.OnMenuMonth();

	m_bLaterDisCount = FALSE;
	m_cmbCouphon.InsertString(2,"기사영업정산");
	RefreshRider();
	m_cmbCouphon.SetCurSel(0);

	SetResize(IDC_CUSTOM1, sizingBottom);		
	SetResize(IDC_LOG_LIST_REPORT, sizingRightBottom);
	SetResize(IDC_LIST_REPORT, sizingRight);
}

void CReportForm20::RefreshRider()
{
	m_RiderList.DeleteAllItem();
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_mileage_balance");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	
	if(!pRs.Execute(&pCmd))
		return;

	int nMNo, nCompany, nItem = 0;
	CString strName;
	long nMyCompanyMileage= 0,  nMyCompanyCouphon = 0, nMarketCallCount = 0;
	long nTotMyCompanyMileage = 0, nTotMyCompanyCoupon = 0, nTotMarketCallCount = 0;
	
	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("lCode", nCompany);
		if(nItem == 0)
		{
			m_RiderList.MyAddItem(0,"사이트전체","지사",65,FALSE,DT_LEFT);			
			m_RiderList.MyAddItem(1,999999,		"사번",	40,FALSE,DT_LEFT);
			m_RiderList.MyAddItem(2,"전직원",	"기사명",55,FALSE,DT_LEFT);
			m_RiderList.MyAddItem(3,0,	"마일",45,FALSE,DT_RIGHT);			
			m_RiderList.MyAddItem(4,0,	"쿠폰",45,FALSE,DT_RIGHT);			
			m_RiderList.MyAddItem(5,0,	"영업",45,FALSE,DT_RIGHT);			
			m_RiderList.InsertItemDataLong(nCompany);
			m_RiderList.EndItem();
		}
		pRs.GetFieldValue("nMNo", nMNo);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nMyCompanyMileage", nMyCompanyMileage);
		pRs.GetFieldValue("nMyCompanyCouphon", nMyCompanyCouphon);
		pRs.GetFieldValue("nMarketCallCount", nMarketCallCount);

		nTotMyCompanyMileage +=nMyCompanyMileage;
		nTotMyCompanyCoupon +=nMyCompanyCouphon;
		nTotMarketCallCount += nMarketCallCount;

		m_RiderList.MyAddItem(0,m_ci.GetBranchName(nCompany),"지사",65,FALSE,DT_LEFT);		
		m_RiderList.MyAddItem(1,nMNo,		"사번",	45,FALSE,DT_CENTER);
		m_RiderList.MyAddItem(2,strName,	"기사명",55,FALSE,DT_LEFT);
		m_RiderList.MyAddItem(3,GetMyNumberFormat(nMyCompanyMileage),	"마일",45,FALSE,DT_RIGHT);		
		m_RiderList.MyAddItem(4,GetMyNumberFormat(nMyCompanyCouphon),	"쿠폰",45,FALSE,DT_RIGHT);		
		m_RiderList.MyAddItem(5,GetMyNumberFormat(nMarketCallCount),	"영업",45,FALSE,DT_RIGHT);		
		m_RiderList.InsertItemDataLong(nCompany);
		m_RiderList.EndItem();
			
		nItem++;
		pRs.MoveNext();
	}
	pRs.Close();

	m_RiderList.MyAddItem(0,"","지사",65,FALSE,DT_LEFT);		
	m_RiderList.MyAddItem(1,0,		"사번",	45,FALSE,DT_CENTER);
	m_RiderList.MyAddItem(2,"합계",	"기사명",55,FALSE,DT_LEFT);
	m_RiderList.MyAddItem(3,GetMyNumberFormat(nTotMyCompanyMileage),	"마일",45,FALSE,DT_RIGHT);		
	m_RiderList.MyAddItem(4,GetMyNumberFormat(nTotMyCompanyCoupon),	"쿠폰",45,FALSE,DT_RIGHT);		
	m_RiderList.MyAddItem(5,GetMyNumberFormat(nTotMarketCallCount),	"영업",45,FALSE,DT_RIGHT);		
	m_RiderList.InsertItemDataLong(-1);
	m_RiderList.EndItem();
	m_RiderList.Populate();
}

void CReportForm20::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();

	if(nRow == -1)
		return;

	CString sRNo = m_RiderList.GetItemText(nRow, 1);
	m_sName = m_RiderList.GetItemText(nRow, 2);
	m_nRiderCompany = m_RiderList.GetItemDataLong(nRow);
	m_nMNo = atol(sRNo);

	m_edtMNo.SetWindowText(sRNo);
	m_edtSName.SetWindowText(m_sName);

	RefreshLogList();
	RefreshList();
}

void CReportForm20::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();

	if(nRow == -1)
		return;

	CString sBalance = m_RiderList.GetItemText(nRow, 4);
	long nBalance = atol(sBalance);
	int nCol = pItemNotify->pItem->GetIndex();

	/*if(nBalance == 0 && nCol == 1)
	{
		m_OrderList.SetItemCheck(nRow,nCol,m_OrderList.GetItemCheck(nRow,nCol));
		MsgBox("마일이 없는곳은 체크하실수 없습니다.");
		return;
	}*/

	CString sRNo = m_RiderList.GetItemText(nRow, 1);
	m_sName = m_RiderList.GetItemText(nRow, 2);
	m_nRiderCompany = m_RiderList.GetItemDataLong(nRow);
	m_nMNo = atol(sRNo);

	m_edtMNo.SetWindowText(sRNo);
	m_edtSName.SetWindowText(m_sName);

	UpdateData(FALSE);
}

void CReportForm20::RefreshLogList()
{
	UpdateData();

	m_LogList.DeleteAllItem();
	//m_OrderList.GetColumns()->Clear();

	int nPayType = m_bCash + (m_bCredit << 1) + (m_bOnline << 2);
	if(m_nMNo == 999999)  ///전직원
	{
		COleDateTimeSpan span = m_dtLogTo - m_dtLogFrom;
		if(span.GetDays() > 62 ) 
		{
			MsgBox("마일리지 로그의 전직원 조회는 2달까지만 적용됩니다");
			return;
		}
	}
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_mileage_log");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtLogFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtLogTo);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nMNo);		
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_cmbCouphon.GetCurSel());		

	if(!pRs.Execute(&pCmd))
		return;

	long nID,nRiderCompany,nRNo,nType,nAmount,nBalance,nClass = 0,nItem = 0;
	CString sEtc,sWName,sName,sType;

	BOOL bAdd; char buffer[10];
	COleDateTime dtLog;
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("bAdd", bAdd);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nClass", nClass);
			//100 수정입금
			//-- 200 잔액출금
			//-- 300 잔액전부정산
			//-- 400 일일입금정산
		switch(nClass)
		{
		case 100:
			sType = "입금";
			break;
		case 200:
			sType = "출금";
			break;
		case 300:
			sType = "잔액정산";
		    break;
		case 400:
			sType = "일일정산";
		    break;
		default:
			sType = "N/A";
		    break;
		}
		
		m_LogList.MyAddItem(0, ltoa(++nItem, buffer, 10),				"No",		40, FALSE,DT_RIGHT);		
		m_LogList.MyAddItem(1, m_ci.GetBranchName(nRiderCompany),"소속회사",	60, FALSE,DT_LEFT);
		m_LogList.MyAddItem(2, nRNo ,									"사번",		45, FALSE,DT_LEFT);
		m_LogList.MyAddItem(3, sName ,								"이름",	60, FALSE,DT_LEFT);		
		m_LogList.MyAddItem(4, dtLog.Format("%y-%m-%d %H:%M") ,		"일시",	70, FALSE,DT_LEFT);
		m_LogList.MyAddItem(5, sType ,								"상태",	50, FALSE,DT_LEFT);		
		m_LogList.MyAddItem(6, bAdd ? GetMyNumberFormat(nAmount) : "" ,"입금",	50, FALSE,DT_RIGHT);
		m_LogList.MyAddItem(7, bAdd == 0? GetMyNumberFormat(nAmount) : "" ,"출금",	50, FALSE,DT_RIGHT);
		m_LogList.MyAddItem(8, GetMyNumberFormat(nBalance),			"잔액",		60, FALSE,DT_RIGHT);
		m_LogList.MyAddItem(9, sWName ,								"작업자",	60, FALSE,DT_LEFT);		
		m_LogList.MyAddItem(10, sEtc ,									"비고",	200, FALSE,DT_LEFT);
		
		m_LogList.EndItem();
		
		pRs.MoveNext();
	}
	pRs.Close();
	m_LogList.Populate();
}

void CReportForm20::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);
	m_OrderList.DeleteAllItems();
	//m_OrderList.GetColumns()->Clear();

	try {
		if(m_nMNo <= 0 ) throw "기사를 선택해주시기 바랍니다.";
		//if(m_nMNo <= 0 && m_nAllMNo != 0) throw "기사를 선택해주시기 바랍니다.";
		if(!(m_bCash || m_bCredit || m_bOnline)) 
			throw "지불방식을 한가지 이상 선택해 주시기 바랍니다.";

	} catch(char *msg) {
		MessageBox(msg, "확인", MB_ICONINFORMATION);
		return;
	}
	
	//-- bCash = 1, bCredit = 2, bOnline = 4
	//-- 1. bCash = F, bCredit = F, bOnline = F	--> 0
	//-- 2. bCash = T, bCredit = F, bOnline = F	--> 1
	//-- 3. bCash = F, bCredit = T, bOnline = F	--> 2
	//-- 4. bCash = F, bCredit = F, bOnline = T	--> 4
	//-- 5. bCash = T, bCredit = T, bOnline = F	--> 3
	//-- 6. bCash = T, bCredit = F, bOnline = T	--> 5
	//-- 7. bCash = F, bCredit = T, bOnline = T	--> 6
	//-- 8. bCash = T, bCredit = T, bOnline = T	--> 7

	int nPayType = m_bCash + (m_bCredit << 1) + (m_bOnline << 2);
	CWaitCursor wait;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_mileage_coupon_report");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
    pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmTo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPayType);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nMNo);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nRiderCompany);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_cmbCouphon.GetCurSel());		

	if(!pRs.Execute(&pCmd))
		return;

	int nItem = 0;
	char buffer[20];
	COleDateTime dt1;
	CString strCName, strStart, strDest, sRName;
	int nAPay, nKDel, nState;
	long nBasic, nTotal, nAdd, nDis, nCon;
	long nBasicT = 0, nTotalT = 0, nAddT = 0, nDisT = 0, nConT = 0, nTNo = 0;
	long nCash = 0, nOnline = 0, nCredit = 0, nTemp = 0;
	long nCouponCharge, nCouponChargeT = 0, nRNo = 0, nChargeRiderAuto = 0;
	CString strTemp, sDisCount, sManager = "";
	long nCompany, nShareCode1, nRiderShareCode1;

	CString sData = "", sBeforeData = "";
	long nTBasic = 0, nTAdd = 0, nTDis = 0, nTTrans = 0, nTAfter = 0, nTSum = 0, 
		nTCoupon = 0, nTChargeRiderAuto =0;
	long nTCash = 0, nTCredit = 0;
	CString sSDong, sDDong;
	//BOOL bChargeRiderAutoCalculate;
	long nID = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nAPay", nAPay);
		pRs.GetFieldValue("nKDelivery", nKDel);
		pRs.GetFieldValue("nBasic", nBasic);
		pRs.GetFieldValue("nTotal", nTotal);
		pRs.GetFieldValue("nAdd", nAdd);
		pRs.GetFieldValue("nDis", nDis);
		pRs.GetFieldValue("nCon", nCon);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nCouponCharge", nCouponCharge);
		pRs.GetFieldValue("sManager", sManager);
		pRs.GetFieldValue("nTNo", nTNo);		
		pRs.GetFieldValue("nRNo", nRNo);		
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("nRiderShareCode1", nRiderShareCode1);
		pRs.GetFieldValue("sSDong", sSDong);
		pRs.GetFieldValue("sDDong", sDDong);
		pRs.GetFieldValue("nChargeRiderAuto", nChargeRiderAuto);
		//pRs.GetFieldValue("bChargeRiderAutoCalculate", bChargeRiderAutoCalculate);
		
		nTBasic += nBasic;
		nTAdd += nAdd;
		nTDis += nDis;
		nTTrans += nCon;
		//nTAfter = 0, 
		nTSum += nTotal;
		nTCoupon += nCouponCharge;
		nTChargeRiderAuto += nChargeRiderAuto;

		if(nAPay == 2 || nAPay == 3)
			nTCredit += nTotal;
		else
			nTCash += nTotal;

		
		m_OrderList.MyAddItem(0, ltoa(++nID, buffer, 10),				"No",		40, FALSE,DT_RIGHT);		
		m_OrderList.MyAddItem(1, nTNo,									"오더No",	60, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(2, m_ci.GetBranchName(nCompany) ,"발주사",70, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(3, GetType(nShareCode1, nRiderShareCode1) ,"지불",40, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(4, nRNo ,									"사번",40, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(5, sRName ,								"이름",55, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(6, dt1.Format("%m-%d %H:%M") ,			"주문일시",80, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(7, strCName ,								"의뢰지",100, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(8, strStart ,								"출발지",80, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(9, sSDong ,								"출발동",50, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(10, strDest ,								"도착지",80, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(11, sDDong ,								"도착동",50, FALSE,DT_LEFT);
		
		int nTotal=0;
	
		if(nDis < 100)
				nTotal = (nBasic + nAdd) * (100 - nDis) / 100;
		else 
			nTotal = nBasic + nAdd - nDis;

		if(!(nAPay == 2 || nAPay == 3)) 
			nCon = 0;		

		switch(nAPay)
		{
			case 0:
			case 1:
				nCash += nTotal;
				break;
			case 2:
				nCredit += nTotal;
				break;
			case 3:
				nOnline += nTotal;
				break;
		}

		m_OrderList.MyAddItem(12, GetPayTypeFromLong(nAPay),			"구분",50, FALSE,DT_CENTER);
		m_OrderList.MyAddItem(13, GetMyNumberFormat(nBasic),			"기본",80, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(14, GetMyNumberFormat(nAdd) ,				"추가",70, FALSE,DT_RIGHT);		
		m_OrderList.MyAddItem(15, (nDis < 100 && nDis > 0) ? CString(ltoa(nDis, buffer, 10)) + "%" :	
							GetMyNumberFormat(nDis) ,					"할인",70, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(16, GetMyNumberFormat(nCon) ,				"탁송",70, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(17, "",									"추후할인",90, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(18, GetMyNumberFormat(nTotal),			"합계",100, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(19, GetMyNumberFormat(nCouponCharge),		"쿠폰",70, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(20, GetMyNumberFormat(nChargeRiderAuto),	"마일",70, FALSE,DT_RIGHT);
		m_OrderList.MyAddItem(21, sManager ,							"담당자",60, FALSE,DT_LEFT);
		m_OrderList.MyAddItem(22, GetStateString(nState) ,				"비고",80, FALSE,DT_LEFT);
		m_OrderList.EndItem();

		nBasicT += nBasic;
		nAddT += nAdd;
		nDisT += nDis;
		nConT += nCon;
		nTotalT += nTotal;
		if(m_cmbCouphon.GetCurSel())
			nCouponChargeT += nCouponCharge;
		else
			nCouponChargeT += nChargeRiderAuto;

		sBeforeData = sData;

		pRs.MoveNext();
	}

	pRs.Close();
	if(m_OrderList.GetRecords()->GetCount() > 0)
	{
	/*
		m_OrderList.InsertItem(++i,"", FALSE);
		m_OrderList.SetItemText(i,17, "합계:");
		m_OrderList.SetItemText(i,18, GetMyNumberFormat(nTotalT));
		m_OrderList.SetItemText(i,19, GetMyNumberFormat(nCouponChargeT) );
		*/
		
	}	

	m_OrderList.Populate();
}

CString CReportForm20::GetType(long nShareCode1, long nRiderShareCode1)
{
	if((nShareCode1 == nRiderShareCode1)  || nRiderShareCode1 == 0) // 자사
		return "자사";

	if((nShareCode1 != nRiderShareCode1)  && nRiderShareCode1 != 0)
		return "타사";

	return "알수없음";
}

void CReportForm20::OnBnClickedButtonRiderFetch()
{
	UpdateData();
	RefreshList();
}

void CReportForm20::OnBnClickedButtonRiderFetch2()
{
	UpdateData(TRUE);
	//전체 리스트
	RefreshLogList();
}

void CReportForm20::OnBnClickedTodayBtn()
{
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	m_FromDT.SetTime(dtTime);
	m_ToDT.SetTime(dtTime);
}


void CReportForm20::OnBnClickedCalculateBtn()
{

	if(m_RiderList.GetSelectedCount() == 0)
	{
		MsgBox("잔액정리를 하실 기사분을 선택하세요");
		return;
	}


	int nSelectedCount = m_RiderList.GetSelectedCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999)
		{
			MsgBox("전체기사는 잔액수정이 불가능합니다.");
			return;
		}
	}

	CString sType = "쿠폰정산";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "마일리지";

	CString sMsg = "";
	sMsg.Format("%s으로 %d명의 기사님에 대해 잔액정리를 하시겠습니까?",sType, nSelectedCount);
	if( MsgBox(sMsg,  "잔액정리", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		for(int i = 0; i < nSelectedCount; i++)
		{
			long nRiderCompany = m_RiderList.GetSelectedRecord(i)->GetItemDataLong();
			long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
			long nRNo = atol(m_RiderList.GetItemText(nRow,1));


			m_RiderList.CreateComandSetQuery("update_rider_mileage_balance_init");
			m_RiderList.AddParameter(nRiderCompany);
			m_RiderList.AddParameter(nRNo);
			m_RiderList.AddParameter(m_cmbCouphon.GetCurSel());
			m_RiderList.AddParameter(m_ui.strName);
			m_RiderList.ExcuteCmd();
		}

		RefreshRider();
		RefreshLogList();
	}
}


void CReportForm20::OnBnClickedReceiveBalanceBtn()
{
	if(m_RiderList.GetSelectedCount() == 0)
	{
		MsgBox("잔액차감을 하실 기사분을 선택하세요");
		return;
	}

	int nSelectedCount = m_RiderList.GetSelectedCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999 || nAllRNo == 0)
		{
			MsgBox("전체기사는 잔액수정이 불가능합니다.");
			return;
		}
	}

	CString sType = "쿠폰정산";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "마일리지";

	CString sMsg = "";
	sMsg.Format("%s(으)로 %d명의 기사님에 대해 잔액을 차감 하시겠습니까?",sType,nSelectedCount);
	if( MsgBox(sMsg,  "잔액차감", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CVarietyDlg1 dlg;
		dlg.m_sTitleDlg = "차감하실 금액을 입력하세요 금액에 -(음수)를 안붙여셔도 됩니다.";
		if(dlg.DoModal() == IDOK)
		{
			dlg.m_sValue.Replace("-", "");
			dlg.m_sValue.Replace(",", "");
			long nAmount = atol(dlg.m_sValue);
			if(nAmount <= 0)
			{
				MsgBox("금액이 0원 이하는 적용되지 않습니다");
				return;
			}
			if(nAmount > 1000000)
			{
				MsgBox("금액적용이 10000000원 이상은 적용되지 않습니다");
				return;
			}

			for(int i = 0; i < nSelectedCount; i++)
			{
				long nRiderCompany = m_RiderList.GetSelectedRecord(i)->GetItemDataLong();
				long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
				long nRNo = atol(m_RiderList.GetItemText(nRow,1));
				long nReturn = -1;
				CString sEtc = dlg.m_sValue2;

				if(nRNo <= 0)
				{
					MsgBox("기사번호가 0 이하 입니다. 로지소프트로 문의하세요");
					return;
				}
				m_RiderList.CreateRsSetQuery("update_rider_mileage_balance_modify");
				m_RiderList.AddParameter(nRiderCompany);
				m_RiderList.AddParameter(nRNo);
				m_RiderList.AddParameter(m_cmbCouphon.GetCurSel());
				m_RiderList.AddParameter(m_ui.strName);
				m_RiderList.AddParameter(nAmount);
				m_RiderList.AddParameter(sEtc);
				m_RiderList.AddParameter(FALSE);
				CMkParameter * pPar = m_RiderList.AddOutPutParameter(nReturn);				
				
				m_RiderList.Excute();

				pPar->GetValue(nReturn);
				if(nReturn == 100)
				{
					CString sMsg = "";
					sMsg.Format("실행중 %d번째 행에서 차감하실 금액이 기사잔액보다 커서 멈춥니다. ", i+1);
					MsgBox(sMsg);
					return;
				}
			}

			RefreshRider();
			RefreshLogList();
		}
	}
}

void CReportForm20::OnBnClickedCalculateBtn3()
{
	if(m_RiderList.GetSelectedCount() == 0)
	{
		MsgBox("잔액 추가하실 기사분을 선택하세요");
		return;
	}

	int nSelectedCount = m_RiderList.GetSelectedCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999 || nAllRNo == 0)
		{
			MsgBox("전체기사는 잔액수정이 불가능합니다.");
			return;
		}
	}
	CString sType = "";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "마일리지";
	else if(m_cmbCouphon.GetCurSel() == 1)
		sType = "쿠폰정산";
	else if(m_cmbCouphon.GetCurSel() == 2)
		sType = "기사영업정산";

	CString sMsg = "";
	sMsg.Format("%s(으)로 %d명의 기사님에 대해 잔액을 추가 하시겠습니까?",sType, nSelectedCount);
	if( MsgBox(sMsg,  "잔액차감", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CVarietyDlg1 dlg;
		dlg.m_sTitleDlg = "추가하실 금액을 입력하세요";
		if(dlg.DoModal() == IDOK)
		{
			long nAmount = atol(dlg.m_sValue);
			if(nAmount <= 0)
			{
				MsgBox("금액이 0원 이하는 적용되지 않습니다");
				return;
			}
			if(nAmount > 1000000)
			{
				MsgBox("금액적용이 10000000원 이상은 적용되지 않습니다");
				return;
			}

			for(int i = 0; i < nSelectedCount; i++)
			{
				long nRiderCompany = m_RiderList.GetSelectedRecord(i)->GetItemDataLong();
				long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
				long nRNo = atol(m_RiderList.GetItemText(nRow,1));
				int	nReturn = -1;
				CString sEtc = dlg.m_sValue2;
				if(nRNo <= 0)
				{
					MsgBox("기사번호가 0 이하 입니다. 로지소프트로 문의하세요");
					return;
				}

				m_RiderList.CreateComandSetQuery("update_rider_mileage_balance_modify");
				m_RiderList.AddParameter(nRiderCompany);
				m_RiderList.AddParameter(nRNo);
				m_RiderList.AddParameter(m_cmbCouphon.GetCurSel());
				m_RiderList.AddParameter(m_ui.strName);
				m_RiderList.AddParameter(nAmount);
				m_RiderList.AddParameter(sEtc);
				m_RiderList.AddParameter(TRUE);
				CMkParameter * pPar = m_RiderList.AddOutPutParameter(nReturn);
				m_RiderList.ExcuteCmd();
			}

			RefreshRider();
			RefreshLogList();
		}
	}
}

void CReportForm20::OnCbnSelchangeCouphonCombo()
{
	RefreshLogList();
	RefreshList();
}

void CReportForm20::OnBnClickedRiderRefreshBtn()
{
	RefreshRider();
}

void CReportForm20::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_OrderList, pt);
}

void CReportForm20::OnReportItemLogRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_LogList, pt);
}

void CReportForm20::OnReportItemCustomRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_RiderList, pt);
}

void CReportForm20::OnViewExcel()
{
	if(!POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_OrderList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_OrderList);
}

void CReportForm20::OnViewExcel2()
{
	if(!POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_LogList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_LogList);
}

void CReportForm20::OnViewExcel3()
{
	if(!POWER_CHECK(4900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_LogList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_RiderList);
}

void CReportForm20::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(pWnd->GetSafeHwnd() == m_OrderList.GetSafeHwnd())
	{
		CRect rect;
		m_OrderList.GetWindowRect(&rect);
		if(!rect.PtInRect(point)) return;

		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if(pWnd->GetSafeHwnd() == m_LogList.GetSafeHwnd())
	{
		CRect rect;
		m_LogList.GetWindowRect(&rect);
		if(!rect.PtInRect(point)) return;

		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(10);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if(pWnd->GetSafeHwnd() == m_RiderList.GetSafeHwnd())
	{
		CRect rect;
		m_RiderList.GetWindowRect(&rect);
		if(!rect.PtInRect(point)) return;

		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(19);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}