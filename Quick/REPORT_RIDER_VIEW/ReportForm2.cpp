// Report2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm2.h"
#include "RcpView.h"

// CReportForm2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CReportForm2, CMyFormView)
CReportForm2::CReportForm2()
	: CMyFormView(CReportForm2::IDD)
	, m_bCash(TRUE)
	, m_bCredit(TRUE)
	, m_bOnline(TRUE)
	, m_bCard(TRUE)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_tmFrom= COleDateTime::GetCurrentTime() - span;
	m_tmTo = COleDateTime::GetCurrentTime();
	m_bLaterDisCount = FALSE;
	m_bSms = FALSE;
}

CReportForm2::~CReportForm2()
{
	m_lcData.SaveReportOrder("CReportForm2", "m_lcData");
}

void CReportForm2::DoDataExchange(CDataExchange* pDX)
{
	//"�������� �ʴ� �۾��� �õ��Ͽ����ϴ�." ������ ��쿡 �Ʒ� �ּ��� Ǯ�� �α׸� ���� ��ġ�� ��Ȯ�� �˼� ����
	//#define DDX_Control(x, y, z) { qsLog.Print("DDX_Control: FILE = %s, LINE = %d\n", TEXT(__FILE__), TEXT(__LINE__));DDX_Control(x, y, z);}

	CMyFormView::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_LIST_LEFT, m_lcLeft); 
	DDX_Control(pDX, IDC_LIST_REPORT, m_lcData);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_tmFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_tmTo);
	DDX_Text(pDX, IDC_EDIT_DISRATE, m_strDisRate);
	DDX_Text(pDX, IDC_EDIT_CASHRATE, m_strCashRate);
	DDX_Control(pDX, IDC_EDIT_DISRATE, m_edtDisrate);
	DDX_Control(pDX, IDC_EDIT_CASHRATE, m_edtCashrate);
	DDX_Check(pDX, IDC_CHECK1, m_bCash);
	DDX_Check(pDX, IDC_CHECK2, m_bCredit);
	DDX_Check(pDX, IDC_CHECK3, m_bOnline);
	DDX_Check(pDX, IDC_CHECK5, m_bCard);
	DDX_Check(pDX, IDC_CHECK6, m_bMile);

	DDX_Check(pDX, IDC_LATER_DISCOUNT_CHECK, m_bLaterDisCount);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_BUTTON_RIDER_FETCH, m_RefreshBtn);
	DDX_Control(pDX, IDC_BUTTON_RIDER_FETCH2, m_RefreshBtn2);
	DDX_Control(pDX, IDC_LATER_DISCOUNT_CHECK, m_chkLaterDisCount);
	DDX_Control(pDX, IDC_MSG_BTN, m_btnMsg);
	DDX_Control(pDX, ID_CHECK_TYPE, m_chkType);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CReportForm2, CMyFormView)
	ON_BN_CLICKED(IDC_BUTTON_RIDER_FETCH, OnBnClickedButtonRiderFetch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LEFT, OnClicklcLeftItem)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LEFT, OnReportLeftItemDblClick)
	ON_BN_CLICKED(IDC_BUTTON_RIDER_FETCH2, OnBnClickedButtonRiderFetch2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_SEND_SMS, OnSendSms)
	ON_BN_CLICKED(IDC_TODAY_BTN, OnBnClickedTodayBtn)
	ON_BN_CLICKED(IDC_MSG_BTN, OnBnClickedMsgBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm2::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm2::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CReportForm2 �޽��� ó�����Դϴ�.

void CReportForm2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcLeft.SetImageList(&ImageList,LVSIL_SMALL); 


	m_lcLeft.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_lcLeft.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcLeft.InsertColumn(0,"��  ��",LVCFMT_LEFT,60);
	m_lcLeft.InsertColumn(1,"��  ��",LVCFMT_LEFT,60);

	InitReportColumn(FALSE);

	m_bLaterDisCount = FALSE;
	RefreshRider();

	m_chkType.SetCurSel(0);

	m_lcData.LoadReportOrder("CReportForm2", "m_lcData");

	SetResize(IDC_LIST_LEFT, sizingBottom);
	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CReportForm2::InitReportColumn(BOOL bSMS)
{
	m_lcData.GetColumns()->Clear();

	if(bSMS)
	{ 
 		m_lcData.InsertColumn(0, "üũ",LVCFMT_LEFT,40);
		m_lcData.InsertColumn(1,"���",LVCFMT_LEFT,50);  
		m_lcData.InsertColumn(2,"����",LVCFMT_LEFT,60); 
		CXTPGridColumn *pColumn = m_lcData.InsertColumn1(3,"SMS����",LVCFMT_LEFT,500);
		m_lcData.InsertColumn(4,"SMS�߼�",LVCFMT_LEFT, 45);
		m_lcData.InsertColumn(5,"�޴���",LVCFMT_LEFT,90);
		m_lcData.InsertColumn(6,"����",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(7,"�ſ�",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(8,"�۱�",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(9,"Ź��",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(10,"�Աݾ�",LVCFMT_LEFT,70);

		pColumn->GetEditOptions()->m_bAllowEdit = TRUE;
	}
	else
	{
		m_lcData.InsertColumn(0,"No",LVCFMT_LEFT,40);
		m_lcData.InsertColumn(1,"����No",LVCFMT_LEFT,60);
		m_lcData.InsertColumn(2,"���ֻ�",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(3,"����",LVCFMT_LEFT,40);
		m_lcData.InsertColumn(4,"���",LVCFMT_RIGHT,40);
		m_lcData.InsertColumn(5,"�̸�",LVCFMT_LEFT,55);	
		m_lcData.InsertColumn(6,"�ֹ��Ͻ�",LVCFMT_CENTER,80);
		m_lcData.InsertColumn(7,"�Ƿ���",LVCFMT_LEFT,120);
		m_lcData.InsertColumn(8,"�����",LVCFMT_LEFT,80);
		m_lcData.InsertColumn(9,"��ߵ�",LVCFMT_LEFT,70);
		m_lcData.InsertColumn(10,"������",LVCFMT_LEFT,80);
		m_lcData.InsertColumn(11,"������",LVCFMT_LEFT,80);
		m_lcData.InsertColumn(12,"����",LVCFMT_CENTER,50);
		m_lcData.InsertColumn(13,"�⺻",LVCFMT_RIGHT,70);
		m_lcData.InsertColumn(14,"�߰�",LVCFMT_RIGHT,50);
		m_lcData.InsertColumn(15,"����",LVCFMT_RIGHT,50);
		m_lcData.InsertColumn(16,"Ź��",LVCFMT_RIGHT,55);
		m_lcData.InsertColumn(17,"��������",LVCFMT_RIGHT,65);
		m_lcData.InsertColumn(18,"�հ�",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(19,"�����",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(20,"�����Աݾ�",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(21,"�����Աݾ�",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(22,"��ü�δ��",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(23,"����",LVCFMT_RIGHT,50);
		m_lcData.InsertColumn(24,"�����",LVCFMT_RIGHT,60);
		m_lcData.InsertColumn(25,"���",LVCFMT_RIGHT,50);
		m_lcData.InsertColumn(26,"����",LVCFMT_RIGHT,150);

		m_lcData.GetReportHeader()->AllowColumnSort(FALSE);
	}

	m_lcData.Populate();
}

void CReportForm2::RefreshRider()
{
	CWaitCursor wait;

	m_lcLeft.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_for_report2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
		m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.GetShareCode1()) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),
		m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.GetShareCode2()) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
		m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.GetShareCode3()) : -1);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[20];
	int nMNo, nCompany, nItem = 0;
	CString strName;

	m_lcLeft.DeleteAllItems();
	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("lCode", nCompany);
		pRs.GetFieldValue("nMNo", nMNo);
		pRs.GetFieldValue("sName", strName);
		m_lcLeft.InsertItem(nItem, ltoa(nMNo, buffer, 10));
        m_lcLeft.SetItemText(nItem,1, strName);
		m_lcLeft.SetItemData(nItem, nCompany);
		m_lcLeft.SetItemLong(nItem++, nMNo);
		pRs.MoveNext();
	}

	m_lcLeft.Populate();
	pRs.Close();
}

void CReportForm2::RefreshListAfterDisCount(long nParameterRNo)
{
	CWaitCursor wait;
	m_lcData.DeleteAllItems();

	CXTPGridRecord *pRecord = m_lcLeft.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	try {
		if(!(m_bCash || m_bCredit || m_bOnline || m_bCard)) 
			throw "���ҹ���� �Ѱ��� �̻� ������ �ֽñ� �ٶ��ϴ�.";

	} catch(char *msg) {
		MessageBox(msg, "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	UpdateData(TRUE);
	//CREATE                     PROC [dbo].[select_rider_report] (
	//@nCompany	INT,
	//@nLastBranch	INT,
	//@dtFrom		smalldatetime,
	//@dtTo		smalldatetime,
	//@nPayType	INT) AS
	//
	//SET NOCOUNT ON
	//
	//
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
 
	long nRNoSearch = m_lcLeft.GetItemLong(pRecord);
	long nRiderCompanySearch = m_lcLeft.GetItemData(pRecord);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_report_after_simple4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmTo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPayType);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nParameterRNo > 0 ? nParameterRNo : nRNoSearch);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRiderCompanySearch);	
	//pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nAllMNo ? 100000 : m_nMNo);	

	if(!pRs.Execute(&pCmd)) return;

	pRs.SetSort("dt1", TRUE);

	int nItem = 0;
	char buffer[20];
	COleDateTime dt1;
	CString strCName, strStart, strDest, sRiderName;
	int nAPay, nKDel, nState;
	long nBasic, nTotal, nAdd, nDis, nCon,nRNo;
	long nBasicT = 0, nTotalT = 0, nAddT = 0, nDisT = 0, nConT = 0;
	long nCash = 0, nOnline = 0, nCredit = 0, nTemp = 0, nTNo = 0;
	long nCouponCharge, nCouponChargeT = 0, nCompany, nShareCode1, nRiderShareCode1;
	CString strTemp, sDisCount ,  sManager = "";
	BOOL bCreditAfterDiscount = FALSE;
	BOOL bCompanyCreditAfterDiscount = FALSE; 

	CString sData = "", sBeforeData = "";
	long nTBasic = 0, nTAdd = 0, nTDis = 0, nTTrans = 0, nTAfter = 0, nTSum = 0, nTCoupon = 0;
	long nTCash = 0, nTCredit = 0;
	CString sSDong, sDDong;
	long nID = 0;
	long nCashCount = 0, nCreditCount = 0, nOnlineCount = 0, nTransCount = 0, nCouponCount = 0;
	long nRealDeposit = 0, nTRealDeposit = 0, nRealDepositT = 0;
	long nDeposit = 0, nTDeposit = 0, nDepositT = 0;
	long nChargeDriving = 0, nTChargeDriving = 0, nChargeDrivingT = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sName", sRiderName);
		pRs.GetFieldValue("nRNo", nRNo);
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
		pRs.GetFieldValue("bCreditAfterDiscount", bCreditAfterDiscount);
		pRs.GetFieldValue("sDiscount", sDisCount);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("sManager", sManager);
		pRs.GetFieldValue("sRName", sRiderName);
		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("nRiderShareCode1", nRiderShareCode1);
		pRs.GetFieldValue("sSDong", sSDong);
		pRs.GetFieldValue("sDDong", sDDong);
		pRs.GetFieldValue("nRealDeposit", nRealDeposit);
		pRs.GetFieldValue("nChargeDriving", nChargeDriving);

		sData = dt1.Format("%m%d");

		if(m_chkType.GetCurSel() == 1) // �ڻ�
		{
			if(GetType(nShareCode1, nRiderShareCode1) != "�ڻ�")
			{
				pRs.MoveNext();
				continue;
			}
		}

		if(m_chkType.GetCurSel() == 2) // Ÿ��
		{
			if(GetType(nShareCode1, nRiderShareCode1) != "Ÿ��")
			{
				pRs.MoveNext();
				continue;
			}
		}

		if(nItem != 0)
		{
			if(sData != sBeforeData)
			{
				InsertDayTotal(nTCash, nTCredit, nTBasic, nTAdd, nTDis, nTTrans, nTAfter, nTSum, nTChargeDriving, nDeposit, nTRealDeposit, nTCoupon, 0, nItem, FALSE);

				nItem++;
				nTBasic = 0;
				nTAdd = 0;
				nTDis = 0;
				nTTrans = 0;
				nTAfter = 0, 
				nTSum = 0;
				nTCoupon = 0;
				nTCash = 0;
				nTCredit = 0;
				nTChargeDriving = 0;
			}	
		}

		m_lcData.InsertItem(nItem, ltoa(++nID, buffer, 10));
		m_lcData.SetItemText(nItem,1, itoa(nTNo, buffer,10) );
		m_lcData.SetItemText(nItem,2, m_ci.GetBranchName(nCompany));
		m_lcData.SetItemText(nItem,3, GetType(nShareCode1, nRiderShareCode1));
		m_lcData.SetItemText(nItem,4, itoa(nRNo, buffer,10) );
		m_lcData.SetItemText(nItem,5, sRiderName);
		m_lcData.SetItemText(nItem,6, dt1.Format("%m-%d %H:%M"));
		m_lcData.SetItemText(nItem,7, strCName);	
		m_lcData.SetItemText(nItem,8, strStart);	
		m_lcData.SetItemText(nItem,9, sSDong);
		m_lcData.SetItemText(nItem,10, strDest);	
		m_lcData.SetItemText(nItem,11, sDDong);	

		if(nAPay == 2 || nAPay == 3)
			nTCredit += nTotal;
		else
			nTCash += nTotal;

		int nTotal=0;
		int nDisCount = 0;

		if(sDisCount.Left(1) == "-") 
		{
			sDisCount.Replace("-","");
			nDisCount = atol(sDisCount) * -1;
		}
		else{
			nDisCount = atol(sDisCount);
		}	

		if(nDisCount == 0){					
				nTotal = nBasic + nAdd - nDis;				
		}
		else
		{
			if(bCreditAfterDiscount && nDis == 0)  // ������ �Ǿ������� ������ �ٽþ��Ѵ�.
			{				
				if(nDisCount > -100 && nDisCount < 100 && nDisCount != 0 )  //  ���������  �������� ���־�� ��...
					nTotal  =  (nBasic + nAdd - nDis) + ((nBasic + nAdd)  * nDisCount) /100; //nCharge + (nCharge * nDisCount) / 100;				
				else  // �ݾװ��
					nTotal = (nBasic + nAdd - nDis) + nDisCount;//nCharge + nDisCount;				
			}
			else 
			{						
				if(nDis > - 100 && nDis < 100)
					nTotal = (nBasic + nAdd ) + ((nBasic + nAdd ) * -(nDis) /100);
				else
					nTotal = nBasic + nAdd - nDis;
			}			
		}
	
		switch(nAPay)
		{
			case 0:
			case 1:
			case 4:
				nCash += nTotal;
				nCashCount++;
				break;
			case 2:
				nCredit += nTotal;
				nCreditCount++;
				break;
			case 3:
				nOnline += nTotal;
				nOnlineCount++;
				break;
		}



		nTBasic += nBasic;
		nTAdd += nAdd;
		nTDis += nDis;
		nTTrans += nCon;
		nTAfter += nDisCount, 
			nTSum += nTotal;
		nTCoupon += nCouponCharge;
		nTRealDeposit += nRealDeposit;
		nTChargeDriving += nChargeDriving;

		//nTotal += nCon;
	
		m_lcData.SetItemText(nItem,12, LF->GetPayTypeFromLong(nAPay));
		m_lcData.SetItemText(nItem,13, LF->GetMyNumberFormat(nBasic));
		m_lcData.SetItemText(nItem,14, LF->GetMyNumberFormat(nAdd));
		m_lcData.SetItemText(nItem,15, (nDis < 100 && nDis > 0) ? CString(ltoa(nDis, buffer, 10)) + "%" :
							LF->GetMyNumberFormat(nDis));
		m_lcData.SetItemText(nItem,16, LF->GetMyNumberFormat(nCon));
		if(nDisCount == 0)
		{
			m_lcData.SetItemText(nItem,17, "");
		}
		else
		{
			if(bCreditAfterDiscount)	
				if(nDis != 0 && sDisCount.GetLength() > 0 )
					m_lcData.SetItemText(nItem,13, (nDisCount > -99 && nDisCount < 100) ? "(����:" + sDisCount +"%)"  :
									"����(" + LF->GetMyNumberFormat(nDisCount) + ")" );
				else
					m_lcData.SetItemText(nItem,13, (nDisCount > -99 && nDisCount < 100) ? sDisCount +"%"  :
									 LF->GetMyNumberFormat(nDisCount) );
			else
			{
				if(nDis != 0 && sDisCount.GetLength() > 0)
					m_lcData.SetItemText(nItem,13, (nDisCount > -99 && nDisCount < 100) ? "("+ sDisCount + "%)" :
									"("+LF->GetMyNumberFormat(nDisCount)+")");
					
				else
					m_lcData.SetItemText(nItem,13, (nDisCount > -99 && nDisCount < 100) ? sDisCount + "%" :
									LF->GetMyNumberFormat(nDisCount));
			}
		}

		m_lcData.SetItemText(nItem,18, LF->GetMyNumberFormat(nTotal));
		m_lcData.SetItemText(nItem,19, LF->GetMyNumberFormat(nChargeDriving));
		m_lcData.SetItemText(nItem,20, LF->GetMyNumberFormat(nCouponCharge));
		m_lcData.SetItemText(nItem,21, sManager);
		m_lcData.SetItemText(nItem,22, LF->GetStateString(nState));
		m_lcData.SetItemLong(nItem,0);
		m_lcData.SetItemLong2(nItem++, nCompany);

		nBasicT += nBasic;
		nAddT += nAdd;
		nDisT += nDis;
		nConT += nCon;
		nTotalT += nTotal;
		nCouponChargeT += nCouponCharge;
		nRealDepositT += nRealDeposit;
		nChargeDrivingT += nChargeDriving;

		sBeforeData = sData;

		if(nCon > 0)
			nTransCount++;
		if(nCouponCharge > 0)
			nCouponCount++;

		if(pRs.GetRecordCount() == i+1)
		{
			InsertDayTotal(nTCash, nTCredit, nTBasic, nTAdd, nTDis, nTTrans, nTAfter, nTSum, nChargeDrivingT, nTDeposit, nTRealDeposit, nTCoupon, nTCredit, nItem, FALSE);
			nItem++;
		}

		pRs.MoveNext();
	}

	pRs.Close();

	if(nItem > 0)
	{
		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem++,1,"");

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,6,"��");
		m_lcData.SetItemText(nItem,7,"�ſ�");
		m_lcData.SetItemText(nItem,8,"����");
	
		m_lcData.SetItemText(nItem,9,"�۱�");
		m_lcData.SetItemText(nItem,10, "Ź��");
		m_lcData.SetItemText(nItem,11,"����");
		m_lcData.SetItemText(nItem++,12,"�Աݾ�");

		nTemp = nCash + nOnline + nCredit;

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,5, "�ݾ��հ�");
		m_lcData.SetItemText(nItem,6, LF->GetMyNumberFormat(nTemp + nConT + nCouponChargeT));
		m_lcData.SetItemText(nItem,7, LF->GetMyNumberFormat(nCredit));
		m_lcData.SetItemText(nItem,8, LF->GetMyNumberFormat(nCash));

		m_lcData.SetItemText(nItem,9, LF->GetMyNumberFormat(nOnline));
		m_lcData.SetItemText(nItem,10, LF->GetMyNumberFormat(nConT));
		m_lcData.SetItemText(nItem,11, LF->GetMyNumberFormat(nCouponChargeT));
		m_lcData.SetItemText(nItem++,12, LF->GetMyNumberFormat(nRealDepositT));

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,5, "�Ǽ�");
		m_lcData.SetItemText(nItem,6, LF->GetMyNumberFormat(nCashCount + nCreditCount + nOnlineCount));
		m_lcData.SetItemText(nItem,7, LF->GetMyNumberFormat(nCreditCount));
		m_lcData.SetItemText(nItem,8, LF->GetMyNumberFormat(nCashCount));
		m_lcData.SetItemText(nItem,9, LF->GetMyNumberFormat(nOnlineCount));
		m_lcData.SetItemText(nItem,10, LF->GetMyNumberFormat(nTransCount));
		m_lcData.SetItemText(nItem,11, LF->GetMyNumberFormat(nCouponCount));
		m_lcData.SetItemText(nItem++,12, LF->GetMyNumberFormat(nCashCount + nCreditCount + nOnlineCount));

		m_lcData.InsertItem(nItem,"");		
		m_lcData.SetItemText(nItem,8,"�ſ�������");
		m_lcData.SetItemText(nItem++,9,"����������");

		m_lcData.InsertItem(nItem,"");
		strTemp.Format("%d%%", atol(m_strDisRate));
		m_lcData.SetItemText(nItem, 8, strTemp);
		strTemp.Format("%d%%", atol(m_strCashRate));
		m_lcData.SetItemText(nItem++, 9, strTemp);

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,8,"�Ұ�(�հ�����+Ź��)");
		m_lcData.SetItemText(nItem++,9,"�Ұ�(����)");

		m_lcData.InsertItem(nItem,"");
		strTemp.Format("%d", nCredit * (100 - atol(m_strDisRate)) / 100 + nConT);
		m_lcData.SetItemText(nItem,8, LF->GetMyNumberFormat(strTemp));
		strTemp.Format("%d", nCash * (100 - atol(m_strCashRate)) / 100 );
		m_lcData.SetItemText(nItem++,9,LF->GetMyNumberFormat(strTemp));
	}

	m_lcData.Populate();

}

void CReportForm2::InsertDayTotal(long nTCash, long nTCredit, long nTBasic, long nTAdd, long nTDis, long nTTrans, long nTAfter, 
								  long nTSum, long nTChargeDriving, long nTDeposit, long nTRealDeposit, long nTCoupon, long nTBill, long nItem, BOOL bInsert)
{
	m_lcData.InsertItem(nItem, "");
	m_lcData.SetItemText(nItem, 9, "���� : " + LF->GetMyNumberFormat(nTCash));
	m_lcData.SetItemText(nItem, 10, "�ſ� : " + LF->GetMyNumberFormat(nTCredit));
	m_lcData.SetItemText(nItem, 11, "��/�� : " + LF->GetMyNumberFormat(nTBill));
	m_lcData.SetItemText(nItem, 13, LF->GetMyNumberFormat(nTBasic));
	m_lcData.SetItemText(nItem, 14, LF->GetMyNumberFormat(nTAdd));
	m_lcData.SetItemText(nItem, 15, LF->GetMyNumberFormat(nTDis));
	m_lcData.SetItemText(nItem, 16, LF->GetMyNumberFormat(nTTrans));

	if(bInsert)
		m_lcData.SetItemText(nItem, 17, LF->GetMyNumberFormat(nTCredit));

	m_lcData.SetItemText(nItem, 18, LF->GetMyNumberFormat(nTSum));
	m_lcData.SetItemText(nItem, 19, LF->GetMyNumberFormat(nTChargeDriving));  
	m_lcData.SetItemText(nItem, 20, LF->GetMyNumberFormat(nTDeposit));  
	m_lcData.SetItemText(nItem, 21, LF->GetMyNumberFormat(nTRealDeposit));  
	m_lcData.SetItemText(nItem, 22, LF->GetMyNumberFormat(nTCoupon));  
	m_lcData.SetItemLong(nItem, 1);
	m_lcData.SetItemLong2(nItem, 0);
}
void CReportForm2::RefreshList(long nParameterRNo)
{
	//CMyFormView::RefreshList();

	UpdateData(TRUE);
	m_lcData.DeleteAllItems();

	CXTPGridRecord *pRecord = m_lcLeft.GetFirstSelectedRecord();

	if(!pRecord)
		return;
 
	//try {
	//	if(m_nMNo <= 0 && m_nAllMNo == 0) throw "��縦 �������ֽñ� �ٶ��ϴ�.";
	//	if(!(m_bCash || m_bCredit || m_bOnline || m_bCard)) 
	//		throw "���ҹ���� �Ѱ��� �̻� ������ �ֽñ� �ٶ��ϴ�.";

	//} catch(char *msg) { 
	//	MessageBox(msg, "Ȯ��", MB_ICONINFORMATION);
	//	return;
	//}

	//�ҽ� ���� ������ �ʿ���
	
	//-- bCash = 1, bCredit = 2, bOnline = 4
	//-- 1. bCash = F, bCredit = F, bOnline = F	--> 0
	//-- 2. bCash = T, bCredit = F, bOnline = F	--> 1
	//-- 3. bCash = F, bCredit = T, bOnline = F	--> 2
	//-- 4. bCash = F, bCredit = F, bOnline = T	--> 4
	//-- 5. bCash = T, bCredit = T, bOnline = F	--> 3
	//-- 6. bCash = T, bCredit = F, bOnline = T	--> 5
	//-- 7. bCash = F, bCredit = T, bOnline = T	--> 6
	//-- 8. bCash = T, bCredit = T, bOnline = T	--> 7

	long nRNoSearch = m_lcLeft.GetItemLong(pRecord);
	long nRiderCompanySearch = m_lcLeft.GetItemData(pRecord);

	int nPayType = m_bCash + (m_bCredit << 1) + (m_bOnline << 2);
	CWaitCursor wait; 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_report_simple10");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
    pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_tmTo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPayType);
	//pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nAllMNo ? 100000 : m_nMNo);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nParameterRNo > 0 ? nParameterRNo : nRNoSearch);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRiderCompanySearch);	

	if(!pRs.Execute(&pCmd)) return;

	pRs.SetSort("dt1", TRUE);

	int nItem = 0;
	char buffer[20];
	COleDateTime dt1;
	CString strCName, strStart, strDest, sRName;
	int nAPay, nKDel, nState;
	long nBasic, nTotal, nAdd, nDis, nCon, nPreTotal, nChargeCompanyTotal = 0;
	long nBasicT = 0, nTotalT = 0, nAddT = 0, nDisT = 0, nConT = 0, nTNo = 0;
	long nCash = 0, nOnline = 0, nCredit = 0, nTemp = 0, nMile = 0;

	long nCouponCharge, nCouponChargeT = 0, nRNo = 0;
	CString strTemp, sDisCount, sManager = "", sEtc;
	long nCompany, nShareCode1, nRiderShareCode1;

	CString sData = "", sBeforeData = "";
	long nTBasic = 0, nTAdd = 0, nTDis = 0, nTTrans = 0, nTAfter = 0, nTSum = 0, nTCoupon = 0;
	long nTCash = 0, nTCredit = 0;
	CString sSDong, sDDong;
	long nCashCount = 0, nCreditCount = 0, nOnlineCount = 0, nTransCount = 0, nCouponCount = 0, nMileCount = 0;
	long nBill = 0, nTBill = 0, nPreCon = 0, nBillT = 0, nBillCount = 0;
	long nCard = 0, nCardTrans = 0, nCardCount = 0 ;
	
	long nID = 0;
	long nRealDeposit = 0, nTRealDeposit = 0, nRealDepositT = 0;
	long nCreditTrans = 0;
	long nDeposit = 0, nDepositT = 0, nTDeposit = 0;
	long nChargeDriving = 0, nChargeDrivingT = 0, nTChargeDriving = 0, nChargeCompany = 0;

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
		pRs.GetFieldValue("nRealDeposit", nRealDeposit);
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
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nChargeDriving", nChargeDriving);
		pRs.GetFieldValue("nChargeCompany", nChargeCompany);

		if((m_bCash == FALSE && (nAPay == 0 || nAPay == 1)) ||
			(m_bCredit == FALSE && nAPay == 2) ||
			(m_bOnline == FALSE && nAPay == 3) ||
			(m_bCard == FALSE && nAPay == 7) ||
			(m_bMile == FALSE && nAPay == 6)
			)
		{
			if(pRs.GetRecordCount() == i+1)
			{
				InsertDayTotal(nTCash, nTCredit, nTBasic, nTAdd, nTDis, nTTrans, nTAfter, nTSum, nTChargeDriving, nDepositT, nTRealDeposit, nTCoupon,nTBill, nItem, FALSE);
				nItem++;
			}

			pRs.MoveNext();
			continue;
		}

		sData = dt1.Format("%m%d");

		nPreTotal = nTotal;
		nPreCon = nCon;
		nChargeCompanyTotal += nChargeCompany;
 
		if((m_bCash == TRUE) && (nAPay == 0 || nAPay == 1))
		{
			nTotal = nPreTotal;
			nCon = nPreCon;
		}
		else if((m_bCredit == TRUE) && nAPay == 2) 
		{
			nTotal = nPreTotal;
			nCon = nPreCon;
		}
		else if((m_bOnline == TRUE) && (nAPay == 3))
		{
			nTotal = nPreTotal;
			nCon = nPreCon;
		}
		else if((m_bMile == TRUE) && nAPay == 6)
		{
			nTotal = nPreTotal;
			nCon = nPreCon;
		}
		else if((m_bCard == TRUE) && nAPay == 7)
		{
			nTotal = nPreTotal;
			nCon = nPreCon;
		}
		else //��������
		{
			nTotal = nPreTotal;
			nCon = 0;
		}

		if(m_chkType.GetCurSel() == 1) // �ڻ� 
		{
			if(GetType(nShareCode1, nRiderShareCode1) != "�ڻ�")
			{
				pRs.MoveNext();
				continue;
			}
		}

		if(m_chkType.GetCurSel() == 2) // Ÿ��
		{
			if(GetType(nShareCode1, nRiderShareCode1) != "Ÿ��")
			{
				pRs.MoveNext();
				continue;
			}
		}


		if(nItem != 0) 
		{
			if(sData != sBeforeData)
			{
				InsertDayTotal(nTCash, nTCredit, nTBasic, nTAdd, nTDis, nTTrans, nTAfter, nTSum, nTChargeDriving, nDepositT, nTRealDeposit, nTCoupon, nTBill, nItem, FALSE);

				nItem++; 
				nTBasic = 0;
				nTAdd = 0;
				nTDis = 0;
				nTTrans = 0;
				//nTAfter = 0, 
				nTSum = 0;
				nTCoupon = 0;
				nTCredit = 0;
				nTCash = 0;
				nTBill = 0;
				nDepositT = 0;
				nTRealDeposit = 0;
				nDepositT = 0;
			}	
		}


		nTBasic += nBasic;
		nTAdd += nAdd;
		nTDis += nDis;
		nTTrans += nCon;
		//nTAfter = 0, 
		nTSum += nTotal;
		nTCoupon += nCouponCharge;
		nTRealDeposit += nRealDeposit;
		nTDeposit += nDeposit;
		nTChargeDriving += nChargeDriving;

		if(nAPay == 2 || nAPay == 3 || nAPay == 7)
			nTCredit += nTotal;
		else if(nAPay == 0 || nAPay == 1)
			nTCash += nTotal;
		else
			nTBill += nTotal;


		m_lcData.InsertItem(nItem, ltoa(++nID, buffer, 10) );
		m_lcData.SetItemText(nItem,1, itoa(nTNo,buffer,10) );
		m_lcData.SetItemText(nItem,2, m_ci.GetBranchName(nCompany));
		m_lcData.SetItemText(nItem,3, GetType(nShareCode1, nRiderShareCode1));
		m_lcData.SetItemText(nItem,4, itoa(nRNo,buffer,10) );
		m_lcData.SetItemText(nItem,5, sRName);
		m_lcData.SetItemText(nItem,6, dt1.Format("%m-%d %H:%M"));
		m_lcData.SetItemText(nItem,7, strCName);	
		m_lcData.SetItemText(nItem,8, strStart);	
		m_lcData.SetItemText(nItem,9, sSDong);
		m_lcData.SetItemText(nItem,10, strDest);	
		m_lcData.SetItemText(nItem,11, sDDong);	

		switch(nAPay)
		{
		case 0:
		case 1:
			nCash += nTotal;
			nCashCount++;
			break;
		case 2:
			nCredit += nTotal;
			nCreditTrans += nCon;
			nCreditCount++;
			break;
		case 3:
			nOnline += nTotal;
			nCreditTrans += nCon;
			nOnlineCount++;
			break;
		case 6:
			nMile += nTotal;
			nMileCount++;
		case 7:
			nCard += nTotal;
			nCardTrans += nCon;
			nCardCount++;
			break;
		default:
			nBill += nTotal;
			nBillT += nTotal;
			nBillCount++;
		}



		m_lcData.SetItemText(nItem,12, LF->GetPayTypeFromLong(nAPay));
		m_lcData.SetItemText(nItem,13, LF->GetMyNumberFormat(nBasic));
		m_lcData.SetItemText(nItem,14, LF->GetMyNumberFormat(nAdd));
		m_lcData.SetItemText(nItem,15, (nDis < 100 && nDis > 0) ? CString(ltoa(nDis, buffer, 10)) + "%" :
							LF->GetMyNumberFormat(nDis));
		m_lcData.SetItemText(nItem,16, LF->GetMyNumberFormat(nCon));
		
		m_lcData.SetItemText(nItem,18, LF->GetMyNumberFormat(nTotal));
		m_lcData.SetItemText(nItem,19, LF->GetMyNumberFormat(nChargeDriving));
		m_lcData.SetItemText(nItem,20, LF->GetMyNumberFormat(nDeposit));
		m_lcData.SetItemText(nItem,21, LF->GetMyNumberFormat(nRealDeposit));
		m_lcData.SetItemText(nItem,22, LF->GetMyNumberFormat(nChargeCompany));
		m_lcData.SetItemText(nItem,23, LF->GetMyNumberFormat(nCouponCharge));
		m_lcData.SetItemText(nItem,24, sManager);
		m_lcData.SetItemText(nItem,25, LF->GetStateString(nState));
		m_lcData.SetItemText(nItem,26, sEtc);
		m_lcData.SetItemLong(nItem, 0);
		m_lcData.SetItemLong2(nItem++, nCompany);

		nBasicT += nBasic;
		nAddT += nAdd;
		nDisT += nDis;
		nConT += nCon;
		nTotalT += nTotal;
		nCouponChargeT += nCouponCharge;
		nRealDepositT += nRealDeposit;
		nDepositT += nDeposit;
		nChargeDrivingT += nChargeDriving;
		
		sBeforeData = sData;

		if(nCon > 0)
			nTransCount++;
		if(nCouponCharge > 0)
			nCouponCount++;

		if(pRs.GetRecordCount() == i+1)
		{
			InsertDayTotal(nTCash, nTCredit, nTBasic, nTAdd, nTDis, nTTrans, nTAfter, nTSum, nTChargeDriving, nDepositT, nTRealDeposit, nTCoupon,nTBill, nItem, FALSE);
			nItem++;
		}

		pRs.MoveNext();
	}

	pRs.Close();

	if(nItem > 0)
	{
		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem++,1,"");

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,6,"��");
		m_lcData.SetItemText(nItem,7,"��ü�δ��");
		m_lcData.SetItemText(nItem,8,"�ſ�");
		m_lcData.SetItemText(nItem,9,"����");
		m_lcData.SetItemText(nItem,10,"�۱�");
		m_lcData.SetItemText(nItem,11,"ī��");
		m_lcData.SetItemText(nItem,12, "Ź��");
		m_lcData.SetItemText(nItem,13,"��������");
		m_lcData.SetItemText(nItem,14,"����");
		m_lcData.SetItemText(nItem,15, "�����Աݾ�");
		m_lcData.SetItemText(nItem++,16, "�����Աݾ�");
	
		nTemp = nCash + nOnline + nCredit ;

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,5, "�ݾ��հ�");
		m_lcData.SetItemText(nItem,6, LF->GetMyNumberFormat(nTemp + nCouponChargeT + nChargeCompanyTotal));
		m_lcData.SetItemText(nItem,7, LF->GetMyNumberFormat(nChargeCompanyTotal));
		m_lcData.SetItemText(nItem,8, LF->GetMyNumberFormat(nCredit));
		m_lcData.SetItemText(nItem,9, LF->GetMyNumberFormat(nCash));
		m_lcData.SetItemText(nItem,10, LF->GetMyNumberFormat(nOnline));
		m_lcData.SetItemText(nItem,11, LF->GetMyNumberFormat(nCard));

		m_lcData.SetItemText(nItem,12, LF->GetMyNumberFormat(nConT));
		m_lcData.SetItemText(nItem,13, LF->GetMyNumberFormat(nBillT));
		m_lcData.SetItemText(nItem,14, LF->GetMyNumberFormat(nCouponChargeT));
		m_lcData.SetItemText(nItem,15, LF->GetMyNumberFormat(nDepositT));
		m_lcData.SetItemText(nItem++,16, LF->GetMyNumberFormat(nRealDepositT));

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,5, "�Ǽ�");
		m_lcData.SetItemText(nItem,6, LF->GetMyNumberFormat(nCashCount + nCreditCount + nOnlineCount));
		m_lcData.SetItemText(nItem,8, LF->GetMyNumberFormat(nCreditCount));
		m_lcData.SetItemText(nItem,9, LF->GetMyNumberFormat(nCashCount));
		m_lcData.SetItemText(nItem,10, LF->GetMyNumberFormat(nOnlineCount));
		m_lcData.SetItemText(nItem,11, LF->GetMyNumberFormat(nCardCount));
		m_lcData.SetItemText(nItem,12, LF->GetMyNumberFormat(nTransCount));
		m_lcData.SetItemText(nItem++,13, LF->GetMyNumberFormat(nBillCount));

		m_lcData.InsertItem(nItem,"");		
		m_lcData.SetItemText(nItem,9,"�ſ�������");
		m_lcData.SetItemText(nItem++,10,"����������");

		m_lcData.InsertItem(nItem,"");
		strTemp.Format("%d%%", atol(m_strDisRate));
		m_lcData.SetItemText(nItem, 9, strTemp);
		strTemp.Format("%d%%", atol(m_strCashRate));
		m_lcData.SetItemText(nItem++, 10, strTemp);

		m_lcData.InsertItem(nItem,"");
		m_lcData.SetItemText(nItem,9,"�Ұ�(�ſ�+�۱�+ī��+Ź��)");
		m_lcData.SetItemText(nItem++,10,"�Ұ�(����)");

		m_lcData.InsertItem(nItem,"");
		//strTemp.Format("%d", nCredit * (100 - atol(m_strDisRate)) / 100 + nConT);
		m_lcData.SetItemText(nItem,9, LF->GetMyNumberFormat(nCredit + nOnline + nCard + nCreditTrans + nCardTrans + nChargeCompanyTotal));
		strTemp.Format("%d", nCash * (100 - atol(m_strCashRate)) / 100 );
		m_lcData.SetItemText(nItem++,10,LF->GetMyNumberFormat(strTemp));
	}

	m_lcData.Populate();
}

CString CReportForm2::GetType(long nShareCode1, long nRiderShareCode1)
{
	if((nShareCode1 == nRiderShareCode1)  || nRiderShareCode1 == 0) // �ڻ�
		return "�ڻ�";

	if((nShareCode1 != nRiderShareCode1)  && nRiderShareCode1 != 0)
		return "Ÿ��";

	return "�˼�����";
}

void CReportForm2::OnBnClickedButtonRiderFetch()
{
	m_bSms = FALSE;
	InitReportColumn(FALSE);

	UpdateData();
	if(m_bLaterDisCount)
		RefreshListAfterDisCount();
	else
		RefreshList();
}

void CReportForm2::OnClicklcLeftItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPListCtrlRecord2* pRecord = static_cast<CXTPListCtrlRecord2* >(m_lcLeft.GetFirstSelectedRecord());

	


	*pResult = 0;
}

void CReportForm2::OnBnClickedButtonRiderFetch2()
{
	m_bSms = FALSE;
	InitReportColumn(FALSE);

	UpdateData(TRUE);
	//��ü ����Ʈ
	if(m_bLaterDisCount)
		RefreshListAfterDisCount(100000);
	else
		RefreshList(100000);

}

void CReportForm2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);

	if(m_bSms)
	{
		CMenu *pRMenu=rMenu.GetSubMenu(16);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
	else
	{
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CReportForm2::OnViewExcel()
{
	if(!LF->POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 302, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}

void CReportForm2::OnSendSms()
{
	long nMsgCount = 0;
	long nSMSCount = 0;

	for(int i=0;i<m_lcData.GetItemCount(); i++)
	{
		if(m_lcData.GetChecked(i, 0))
		{
			BOOL bUsePDA = (BOOL)m_lcData.GetItemData(i);

			if(bUsePDA)
				nMsgCount++;
			else
				nSMSCount++;			
		}
	}

	if((nMsgCount + nSMSCount) == 0)
	{
		MessageBox("�ּ� �Ѹ� �̻� üũ�� �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString sMsg = "";
	sMsg.Format("%d���� ���Կ��� ����\r\n%d���� ���Կ��� ���� ������\r\n �Ͻðڽ��ϱ�?", nMsgCount, nSMSCount);

	if(MessageBox(sMsg, "Ȯ��", MB_ICONINFORMATION | MB_YESNO) != IDYES)
		return;


	for(int i=0;i <m_lcData.GetItemCount(); i++)
	{
		if(m_lcData.GetChecked(i, 0) == FALSE)
			continue; 

		CString sMsg = m_lcData.GetItemText(i, 3);
		CString sHp = m_lcData.GetItemText(i, 5);
		sHp.Replace("-", "");
		CString strEtc = "����Աݸ޼���";
		long nRiderCompany = (long)m_lcData.GetItemData(i);
		long nRNo = _ttoi(m_lcData.GetItemText(i, 1));

		sHp.Replace("-", "");

		BOOL bUsePDA = (BOOL)m_lcData.GetItemData(i);

		if(bUsePDA)
		{
			UpdateData(TRUE);
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "edit_rider_msg4");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
			pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRiderCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			pCmd.AddParameter(typeString, typeInput, sMsg.GetLength(), sMsg);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
			if(!pCmd.Execute()) 
			{
				MessageBox("SMS ���� ����", "���۽���", MB_ICONINFORMATION);
				return;
			}
		}
		else
		{
			LF->SendSmsNew(m_ci.m_nCompanyCode, 777, sHp, m_ci.m_strOfficePhone, sMsg, "�������α׷�(����Ա�)", "", "", TRUE);
		}		
	}

	MessageBox("���ۿϷ�", "���ۼ���", MB_ICONINFORMATION);
}

void CReportForm2::OnBnClickedTodayBtn()
{
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	m_FromDT.SetTime(dtTime);
	m_ToDT.SetTime(dtTime);
}

void CReportForm2::OnBnClickedMsgBtn()
{
	m_bSms = TRUE; 
	InitReportColumn(TRUE);
	RefreshSMSData();
}

void CReportForm2::RefreshSMSData()
{
	m_lcData.DeleteAllItems();

	char buffer[20];

	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_sms_data");

	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_tmFrom);
	pCmd.AddParameter(m_tmTo);

	if(!pRs.Execute(&pCmd)) return;

	long nRiderCompany, nRNo;
	CString sRName;
	CString sMsg = "";
	CString sStartDate = "", sEndDate = "";
	long nCashCharge, nCreditCharge, nOnlineCharge, nChargeTrans, nDeposit;
	long nCashCount, nCreditCount, nOnlineCount, nCountTrans;
	CString sRiderPhone, sID, sHp;
	BOOL bUsePDA;

	sStartDate.Format("%d/%d", m_tmFrom.GetMonth(), m_tmFrom.GetDay());
	sEndDate.Format("%d/%d", m_tmTo.GetMonth(), m_tmTo.GetDay());

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("nCashCount", nCashCount);
		pRs.GetFieldValue("nCreditCount", nCreditCount);
		pRs.GetFieldValue("nOnlineCount", nOnlineCount);
		pRs.GetFieldValue("nCountTrans", nCountTrans);
		pRs.GetFieldValue("nCashCharge", nCashCharge);
		pRs.GetFieldValue("nCreditCharge", nCreditCharge);
		pRs.GetFieldValue("nOnlineCharge", nOnlineCharge);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("sRiderPhone", sRiderPhone);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("bUsePDA", bUsePDA);

		if(bUsePDA)
		{
			m_lcData.InsertCheckItem(i, "", -1, TRUE);
			sHp = LF->GetDashPhoneNumber(sID);
		}
		else 
		{
			if((sRiderPhone.GetLength() >= 10) && (sRiderPhone.Left(2) == "01"))
			{
				m_lcData.InsertCheckItem(i, "", -1, TRUE);
				sHp = LF->GetDashPhoneNumber(sRiderPhone);
			}
			else if ((sID.GetLength() >= 10) && (sID.Left(2) == "01"))
			{
				m_lcData.InsertCheckItem(i, "", -1, TRUE);
				sHp = LF->GetDashPhoneNumber(sID);
			}
			else
			{
				m_lcData.InsertCheckItem(i, "", -1, FALSE);
				sHp = "";
			}
		}
		
		m_lcData.SetItemText(i, 1, itoa(nRNo, buffer, 10));
		m_lcData.SetItemText(i, 2, sRName);

		if((nCreditCharge + nOnlineCharge + nChargeTrans - nDeposit) < 0)
		{
			sMsg.Format("%d����%s~%s�հ�:%d�ſ�:%d:�Ա�:%d ����:%d�Աݺ�Ź�帳�ϴ�", 
				nRNo, sStartDate, sEndDate, nCashCharge + nCreditCharge + nOnlineCharge,
				nCreditCharge + nOnlineCharge, nDeposit,
				abs(nCreditCharge + nOnlineCharge + nChargeTrans - nDeposit));
		}
		else
		{
			sMsg.Format("%d����%s~%s�հ�:%d�ſ�:%d:�Ա�:%d ����:%d�޾ư��ñ�ٶ��ϴ�", 
				nRNo, sStartDate, sEndDate, nCashCharge + nCreditCharge + nOnlineCharge,
				nCreditCharge + nOnlineCharge, nDeposit,
				nCreditCharge + nOnlineCharge + nChargeTrans - nDeposit);
		}

		m_lcData.SetItemText(i, 3, sMsg);
		m_lcData.SetItemText(i, 4, bUsePDA == 1 ? "����" : "SMS");
		m_lcData.SetItemText(i, 5, sHp);
        
		m_lcData.SetItemText(i, 6, (CString)itoa(nCashCount, buffer, 10) + "/" + (CString)itoa(nCashCharge, buffer, 10));
		m_lcData.SetItemText(i, 7, (CString)itoa(nCreditCount, buffer, 10) + "/" + (CString)itoa(nCreditCharge, buffer, 10));
		m_lcData.SetItemText(i, 8, (CString)itoa(nOnlineCount, buffer, 10) + "/" + (CString)itoa(nOnlineCharge, buffer, 10));
		m_lcData.SetItemText(i, 9, (CString)itoa(nCountTrans, buffer, 10) + "/" + (CString)itoa(nChargeTrans, buffer, 10));
		m_lcData.SetItemText(i, 10, (CString)itoa(nDeposit, buffer, 10));
		m_lcData.SetItemLong(i, nRiderCompany);
		m_lcData.SetItemData(i, bUsePDA);

			
		/*282������10/1~10/7�հ�:64000�ſ�:14000�Ա�:12800�Աݺ�Ź�帳�ϴ�.*/
		pRs.MoveNext();
	}

	m_lcData.Populate();

	/*282������10/1~10/7�հ�:64000�ſ�:14000�Ա�:12800�Աݺ�Ź�帳�ϴ�.*/
}

void CReportForm2::OnReportLeftItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnBnClickedButtonRiderFetch();
}

void CReportForm2::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridSelectedRows *pRows = m_lcData.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRow *pRow = pRows->GetAt(0);
	CXTPGridColumn *pColumn = NULL;
	CXTPGridRecord *pRecord = pRow->GetRecord();

	CString sOName = pRecord->GetItem(7)->GetCaption(NULL);
	long nState = LF->GetStateFromString(pRecord->GetItem(23)->GetCaption(NULL));
	long nTNo = _ttoi(pRecord->GetItem(1)->GetCaption(NULL));
	long nCompany = m_lcData.GetItemLong2(pRecord);
	CBranchInfo *pBranch = LF->GetBranchInfo(nCompany);

	
	if(LU->GetRcpView() == NULL)
		return;


	if(LU->GetRcpView()->GetSecondCrossState(nCompany))
	{
		MessageBox("ũ�ν������� ���� Ȯ�� �Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}


	LU->GetRcpView()->CreateRcpDlg(pBranch, 
		sOName,
		nTNo, 
		nState, "", FALSE, MINUS_ONE, ZERO, ZERO, FALSE, "");
}

void CReportForm2::OnBnClickedRefreshBtn()
{
	RefreshRider();
}

void CReportForm2::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lcLeft.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = m_lcLeft.GetItemText(pRecord, 0);
		CString strRName = m_lcLeft.GetItemText(pRecord, 1);

		if(strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lcLeft.Populate();
}
