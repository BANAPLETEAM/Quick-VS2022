// Report2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm20.h"

//#include ".ReportForm20.h"
#include "VarietyDlg1.h"

// CReportForm20 ��ȭ �����Դϴ�.

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

	m_tmFrom.SetDateTime(m_tmFrom.GetYear(), m_tmFrom.GetMonth(), m_tmFrom.GetDay(), 0, 0, 0);
	m_tmTo.SetDateTime(m_tmTo.GetYear(), m_tmTo.GetMonth(), m_tmTo.GetDay(), 23, 59, 59);
	
	m_dtLogFrom = COleDateTime::GetCurrentTime() - span;
	m_dtLogTo = COleDateTime::GetCurrentTime();

	m_dtLogFrom.SetDateTime(m_dtLogFrom.GetYear(), m_dtLogFrom.GetMonth(), m_dtLogFrom.GetDay(), 0, 0, 0);
	m_dtLogTo.SetDateTime(m_dtLogTo.GetYear(), m_dtLogTo.GetMonth(), m_dtLogTo.GetDay(), 23, 59, 59);

	m_bLaterDisCount = FALSE;
	
	m_nRiderCompany = 0;
	m_bFirstRefreshList = TRUE;
}

CReportForm20::~CReportForm20()
{
}

void CReportForm20::DoDataExchange(CDataExchange* pDX)
{
	//"�������� �ʴ� �۾��� �õ��Ͽ����ϴ�." ������ ��쿡 �Ʒ� �ּ��� Ǯ�� �α׸� ���� ��ġ�� ��Ȯ�� �˼� ����
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

// CReportForm20 �޽��� ó�����Դϴ�.

void CReportForm20::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	UpdateData();
	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	m_DateLogBtn.InitDateButton(&m_dtpFromLog, &m_dtpToLog);
	m_DateLogBtn.OnMenuMonth();

	m_bLaterDisCount = FALSE;

	m_RiderList.InsertColumn(0, "����", LVCFMT_LEFT, 90);
	m_RiderList.InsertColumn(1, "���", LVCFMT_LEFT, 50);
	m_RiderList.InsertColumn(2, "����", LVCFMT_LEFT, 70);
	m_RiderList.InsertColumn(3, "����", LVCFMT_RIGHT, 60);
	m_RiderList.InsertColumn(4, "����", LVCFMT_RIGHT, 60);
	m_RiderList.InsertColumn(5, "����", LVCFMT_RIGHT, 60);
	m_RiderList.Populate();

	m_LogList.InsertColumn(0, "No", LVCFMT_RIGHT, 30);
	m_LogList.InsertColumn(1, "�Ҽ�ȸ��", LVCFMT_LEFT, 90);
	m_LogList.InsertColumn(2, "���", LVCFMT_LEFT, 50);
	m_LogList.InsertColumn(3, "�̸�", LVCFMT_LEFT, 90);
	m_LogList.InsertColumn(4, "�Ͻ�", LVCFMT_LEFT, 95);
	m_LogList.InsertColumn(5, "����", LVCFMT_LEFT, 70);
	m_LogList.InsertColumn(6, "�Ա�", LVCFMT_RIGHT, 60);
	m_LogList.InsertColumn(7, "���", LVCFMT_RIGHT, 60);
	m_LogList.InsertColumn(8, "�ܾ�", LVCFMT_RIGHT, 70);
	m_LogList.InsertColumn(9, "�۾���", LVCFMT_LEFT, 90);
	m_LogList.InsertColumn(10, "���", LVCFMT_LEFT, 240);
	m_LogList.Populate();

	m_OrderList.InsertColumn(0, "No", LVCFMT_RIGHT, 30);
	m_OrderList.InsertColumn(1, "����No", LVCFMT_LEFT, 90);
	m_OrderList.InsertColumn(2, "���ֻ�", LVCFMT_LEFT, 90);
	m_OrderList.InsertColumn(3, "����", LVCFMT_LEFT, 40);
	m_OrderList.InsertColumn(4, "���", LVCFMT_LEFT, 50);
	m_OrderList.InsertColumn(5, "�̸�", LVCFMT_LEFT, 70);
	m_OrderList.InsertColumn(6, "�ֹ��Ͻ�", LVCFMT_LEFT, 85);
	m_OrderList.InsertColumn(7, "�Ƿ���", LVCFMT_LEFT, 100);
	m_OrderList.InsertColumn(8, "�����", LVCFMT_LEFT, 80);
	m_OrderList.InsertColumn(9, "��ߵ�", LVCFMT_LEFT, 60);
	m_OrderList.InsertColumn(10, "������", LVCFMT_LEFT, 80);
	m_OrderList.InsertColumn(11, "������", LVCFMT_LEFT, 60);
	m_OrderList.InsertColumn(12, "����", LVCFMT_CENTER, 50);
	m_OrderList.InsertColumn(13, "�⺻", LVCFMT_RIGHT, 80);
	m_OrderList.InsertColumn(14, "�߰�", LVCFMT_RIGHT, 70);
	m_OrderList.InsertColumn(15, "����", LVCFMT_RIGHT, 70);
	m_OrderList.InsertColumn(16, "Ź��", LVCFMT_RIGHT, 70);
	m_OrderList.InsertColumn(17, "��������", LVCFMT_RIGHT, 90);
	m_OrderList.InsertColumn(18, "�հ�", LVCFMT_RIGHT, 100);
	m_OrderList.InsertColumn(19, "����", LVCFMT_RIGHT, 70);
	m_OrderList.InsertColumn(20, "����", LVCFMT_RIGHT, 70);
	m_OrderList.InsertColumn(21, "�����", LVCFMT_LEFT, 90);
	m_OrderList.InsertColumn(22, "���", LVCFMT_LEFT, 80);
	m_OrderList.Populate();

	m_cmbCouphon.InsertString(2,"��翵������");
	RefreshRider();
	m_cmbCouphon.SetCurSel(0);

	SetResize(IDC_CUSTOM1, sizingBottom);		
	SetResize(IDC_LOG_LIST_REPORT, sizingRightBottom);
	SetResize(IDC_LIST_REPORT, sizingRight);
}

void CReportForm20::RefreshRider()
{
	m_RiderList.DeleteAllItems();
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_mileage_balance");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	
	if(!pRs.Execute(&pCmd))
		return;

	int nMNo, nCompany, nItem = 0;
	CString strName;
	long nMyCompanyMileage= 0,  nMyCompanyCouphon = 0, nMarketCallCount = 0;
	long nTotMyCompanyMileage = 0, nTotMyCompanyCoupon = 0, nTotMarketCallCount = 0;
	int i = 0;
	for (; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("lCode", nCompany);
		if(nItem == 0)
		{
			m_RiderList.InsertItem(i, "����Ʈ��ü");
			m_RiderList.SetItemText(i, 1, "999999");
			m_RiderList.SetItemText(i, 2, "������");
			m_RiderList.SetItemText(i, 3, "0");
			m_RiderList.SetItemText(i, 4, "0");
			m_RiderList.SetItemText(i, 5, "0");
			m_RiderList.SetItemLong(i, nCompany);
		}
		pRs.GetFieldValue("nMNo", nMNo);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nMyCompanyMileage", nMyCompanyMileage);
		pRs.GetFieldValue("nMyCompanyCouphon", nMyCompanyCouphon);
		pRs.GetFieldValue("nMarketCallCount", nMarketCallCount);

		nTotMyCompanyMileage +=nMyCompanyMileage;
		nTotMyCompanyCoupon +=nMyCompanyCouphon;
		nTotMarketCallCount += nMarketCallCount;

		m_RiderList.InsertItem(i + 1, m_ci.GetBranchName(nCompany));
		m_RiderList.SetItemText(i + 1, 1, LF->GetStringFromLong(nMNo));
		m_RiderList.SetItemText(i + 1, 2, strName);
		m_RiderList.SetItemText(i + 1, 3, LF->GetMyNumberFormat(nMyCompanyMileage));
		m_RiderList.SetItemText(i + 1, 4, LF->GetMyNumberFormat(nMyCompanyCouphon));
		m_RiderList.SetItemText(i + 1, 5, LF->GetMyNumberFormat(nMarketCallCount));
		m_RiderList.SetItemLong(i + 1, nCompany);
			
		nItem++;
		pRs.MoveNext();
	}
	pRs.Close();

	m_RiderList.InsertItem(i + 1, "");
	m_RiderList.SetItemText(i + 1, 1, "0");
	m_RiderList.SetItemText(i + 1, 2, "�հ�");
	m_RiderList.SetItemText(i + 1, 3, LF->GetMyNumberFormat(nTotMyCompanyMileage));
	m_RiderList.SetItemText(i + 1, 4, LF->GetMyNumberFormat(nTotMyCompanyCoupon));
	m_RiderList.SetItemText(i + 1, 5, LF->GetMyNumberFormat(nTotMarketCallCount));
	m_RiderList.SetItemLong(i + 1, -1);
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
	m_nRiderCompany = m_RiderList.GetItemLong(nRow);
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
		LF->MsgBox("������ ���°��� üũ�ϽǼ� �����ϴ�.");
		return;
	}*/

	CString sRNo = m_RiderList.GetItemText(nRow, 1);
	m_sName = m_RiderList.GetItemText(nRow, 2);
	m_nRiderCompany = m_RiderList.GetItemLong(nRow);
	m_nMNo = atol(sRNo);

	m_edtMNo.SetWindowText(sRNo);
	m_edtSName.SetWindowText(m_sName);

	UpdateData(FALSE);
}

void CReportForm20::RefreshLogList()
{
	UpdateData();

	m_LogList.DeleteAllItems();
	//m_OrderList.GetColumns()->Clear();

	int nPayType = m_bCash + (m_bCredit << 1) + (m_bOnline << 2);
	if(m_nMNo == 999999)  ///������
	{
		COleDateTimeSpan span = m_dtLogTo - m_dtLogFrom;
		if(span.GetDays() > 62 ) 
		{
			LF->MsgBox("���ϸ��� �α��� ������ ��ȸ�� 2�ޱ����� ����˴ϴ�");
			return;
		}
	}
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_mileage_log");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
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
			//100 �����Ա�
			//-- 200 �ܾ����
			//-- 300 �ܾ���������
			//-- 400 �����Ա�����
		switch(nClass)
		{
		case 100:
			sType = "�Ա�";
			break;
		case 200:
			sType = "���";
			break;
		case 300:
			sType = "�ܾ�����";
		    break;
		case 400:
			sType = "��������";
		    break;
		default:
			sType = "N/A";
		    break;
		}
		
		m_LogList.InsertItem(i, LF->GetStringFromLong(i + 1));
		m_LogList.SetItemText(i, 1, m_ci.GetBranchName(nRiderCompany));
		m_LogList.SetItemText(i, 2, LF->GetStringFromLong(nRNo));
		m_LogList.SetItemText(i, 3, sName);
		m_LogList.SetItemText(i, 4, dtLog.Format("%y-%m-%d %H:%M"));
		m_LogList.SetItemText(i, 5, sType);
		m_LogList.SetItemText(i, 6, bAdd ? LF->GetMyNumberFormat(nAmount) : "");
		m_LogList.SetItemText(i, 7, bAdd == 0 ? LF->GetMyNumberFormat(nAmount) : "");
		m_LogList.SetItemText(i, 8, LF->GetMyNumberFormat(nBalance));
		m_LogList.SetItemText(i, 9, sWName);
		m_LogList.SetItemText(i, 10, sEtc);
		
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
		if(m_nMNo <= 0 ) throw "��縦 �������ֽñ� �ٶ��ϴ�.";
		//if(m_nMNo <= 0 && m_nAllMNo != 0) throw "��縦 �������ֽñ� �ٶ��ϴ�.";
		if(!(m_bCash || m_bCredit || m_bOnline)) 
			throw "���ҹ���� �Ѱ��� �̻� ������ �ֽñ� �ٶ��ϴ�.";

	} catch(char *msg) {
		MessageBox(msg, "Ȯ��", MB_ICONINFORMATION);
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
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
    pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
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

		
		m_OrderList.InsertItem(i, LF->GetStringFromLong(i));
		m_OrderList.SetItemText(i, 1, LF->GetStringFromLong(nTNo));
		m_OrderList.SetItemText(i, 2, m_ci.GetBranchName(nCompany));
		m_OrderList.SetItemText(i, 3, GetType(nShareCode1, nRiderShareCode1));
		m_OrderList.SetItemText(i, 4, LF->GetStringFromLong(nRNo));
		m_OrderList.SetItemText(i, 5, sRName);
		m_OrderList.SetItemText(i, 6, dt1.Format("%m-%d %H:%M"));
		m_OrderList.SetItemText(i, 7, strCName);
		m_OrderList.SetItemText(i, 8, strStart);
		m_OrderList.SetItemText(i, 9, sSDong);
		m_OrderList.SetItemText(i, 10, strDest);
		m_OrderList.SetItemText(i, 11, sDDong);
		
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

		m_OrderList.SetItemText(i, 12, LF->GetPayTypeFromLong(nAPay));
		m_OrderList.SetItemText(i, 13, LF->GetMyNumberFormat(nBasic));
		m_OrderList.SetItemText(i, 14, LF->GetMyNumberFormat(nAdd));
		m_OrderList.SetItemText(i, 15, (nDis < 100 && nDis > 0) ? CString(ltoa(nDis, buffer, 10)) + "%" : LF->GetMyNumberFormat(nDis));
		m_OrderList.SetItemText(i, 16, LF->GetMyNumberFormat(nCon));
		m_OrderList.SetItemText(i, 17, "");
		m_OrderList.SetItemText(i, 18, LF->GetMyNumberFormat(nTotal));
		m_OrderList.SetItemText(i, 19, LF->GetMyNumberFormat(nCouponCharge));
		m_OrderList.SetItemText(i, 20, LF->GetMyNumberFormat(nChargeRiderAuto));
		m_OrderList.SetItemText(i, 21, sManager);
		m_OrderList.SetItemText(i, 22, LF->GetStateString(nState));

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
	m_OrderList.Populate();
}

CString CReportForm20::GetType(long nShareCode1, long nRiderShareCode1)
{
	if((nShareCode1 == nRiderShareCode1)  || nRiderShareCode1 == 0) // �ڻ�
		return "�ڻ�";

	if((nShareCode1 != nRiderShareCode1)  && nRiderShareCode1 != 0)
		return "Ÿ��";

	return "�˼�����";
}

void CReportForm20::OnBnClickedButtonRiderFetch()
{
	UpdateData();
	RefreshList();
}

void CReportForm20::OnBnClickedButtonRiderFetch2()
{
	UpdateData(TRUE);
	//��ü ����Ʈ
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

	if(m_RiderList.GetSelectedRows()->GetCount() == 0)
	{
		LF->MsgBox("�ܾ������� �Ͻ� ������ �����ϼ���");
		return;
	}


	int nSelectedCount = m_RiderList.GetSelectedRows()->GetCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedRows()->GetCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999)
		{
			LF->MsgBox("��ü���� �ܾ׼����� �Ұ����մϴ�.");
			return;
		}
	}

	CString sType = "��������";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "���ϸ���";

	CString sMsg = "";
	sMsg.Format("%s���� %d���� ���Կ� ���� �ܾ������� �Ͻðڽ��ϱ�?",sType, nSelectedCount);
	if( LF->MsgBox(sMsg,  "�ܾ�����", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		for(int i = 0; i < nSelectedCount; i++)
		{
			long nRiderCompany = m_RiderList.GetItemLong(m_RiderList.GetSelectedRowsGetAtGetRecord(i));
			long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
			long nRNo = atol(m_RiderList.GetItemText(nRow,1));


			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_rider_mileage_balance_init");
			pCmd.AddParameter(nRiderCompany);
			pCmd.AddParameter(nRNo);
			pCmd.AddParameter(m_cmbCouphon.GetCurSel());
			pCmd.AddParameter(m_ui.strName);

			if (!pRs.Execute(&pCmd))
				return;
		}

		RefreshRider();
		RefreshLogList();
	}
}


void CReportForm20::OnBnClickedReceiveBalanceBtn()
{
	if(m_RiderList.GetSelectedRows()->GetCount() == 0)
	{
		LF->MsgBox("�ܾ������� �Ͻ� ������ �����ϼ���");
		return;
	}

	int nSelectedCount = m_RiderList.GetSelectedRows()->GetCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedRows()->GetCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999 || nAllRNo == 0)
		{
			LF->MsgBox("��ü���� �ܾ׼����� �Ұ����մϴ�.");
			return;
		}
	}

	CString sType = "��������";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "���ϸ���";

	CString sMsg = "";
	sMsg.Format("%s(��)�� %d���� ���Կ� ���� �ܾ��� ���� �Ͻðڽ��ϱ�?",sType,nSelectedCount);
	if( LF->MsgBox(sMsg,  "�ܾ�����", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CVarietyDlg1 dlg;
		dlg.m_sTitleDlg = "�����Ͻ� �ݾ��� �Է��ϼ��� �ݾ׿� -(����)�� �Ⱥٿ��ŵ� �˴ϴ�.";
		if(dlg.DoModal() == IDOK)
		{
			dlg.m_sValue.Replace("-", "");
			dlg.m_sValue.Replace(",", "");
			long nAmount = atol(dlg.m_sValue);
			if(nAmount <= 0)
			{
				LF->MsgBox("�ݾ��� 0�� ���ϴ� ������� �ʽ��ϴ�");
				return;
			}
			if(nAmount > 1000000)
			{
				LF->MsgBox("�ݾ������� 10000000�� �̻��� ������� �ʽ��ϴ�");
				return;
			}

			for(int i = 0; i < nSelectedCount; i++)
			{
				long nRiderCompany = m_RiderList.GetItemLong(m_RiderList.GetSelectedRowsGetAtGetRecord(i));
				long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
				long nRNo = atol(m_RiderList.GetItemText(nRow,1));
				long nReturn = -1;
				CString sEtc = dlg.m_sValue2;

				if(nRNo <= 0)
				{
					LF->MsgBox("����ȣ�� 0 ���� �Դϴ�. ��������Ʈ�� �����ϼ���");
					return;
				}
				CMkRecordset pRs(m_pMkDb);
				CMkCommand pCmd(m_pMkDb, "update_rider_mileage_balance_modify");
				pCmd.AddParameter(nRiderCompany);
				pCmd.AddParameter(nRNo);
				pCmd.AddParameter(m_cmbCouphon.GetCurSel());
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(nAmount);
				pCmd.AddParameter(sEtc);
				pCmd.AddParameter(FALSE);
				CMkParameter* pPar = pCmd.AddParameterRefOutput(nReturn);

				if (!pRs.Execute(&pCmd))
					return;
			
				pPar->GetValue(nReturn);
				if(nReturn == 100)
				{
					CString sMsg = "";
					sMsg.Format("������ %d��° �࿡�� �����Ͻ� �ݾ��� ����ܾ׺��� Ŀ�� ����ϴ�. ", i+1);
					LF->MsgBox(sMsg);
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
	if(m_RiderList.GetSelectedRows()->GetCount() == 0)
	{
		LF->MsgBox("�ܾ� �߰��Ͻ� ������ �����ϼ���");
		return;
	}

	int nSelectedCount = m_RiderList.GetSelectedRows()->GetCount();

	int nRow = -1,nAllRNo = -1;
	for(int i = 0; i < m_RiderList.GetSelectedRows()->GetCount(); i++)
	{
		nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
		nAllRNo = atol(m_RiderList.GetItemText(nRow, 1));
		if(nAllRNo == 999999 || nAllRNo == 0)
		{
			LF->MsgBox("��ü���� �ܾ׼����� �Ұ����մϴ�.");
			return;
		}
	}
	CString sType = "";
	if(m_cmbCouphon.GetCurSel() == 0)
		sType = "���ϸ���";
	else if(m_cmbCouphon.GetCurSel() == 1)
		sType = "��������";
	else if(m_cmbCouphon.GetCurSel() == 2)
		sType = "��翵������";

	CString sMsg = "";
	sMsg.Format("%s(��)�� %d���� ���Կ� ���� �ܾ��� �߰� �Ͻðڽ��ϱ�?",sType, nSelectedCount);
	if( LF->MsgBox(sMsg,  "�ܾ�����", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CVarietyDlg1 dlg;
		dlg.m_sTitleDlg = "�߰��Ͻ� �ݾ��� �Է��ϼ���";
		if(dlg.DoModal() == IDOK)
		{
			long nAmount = atol(dlg.m_sValue);
			if(nAmount <= 0)
			{
				LF->MsgBox("�ݾ��� 0�� ���ϴ� ������� �ʽ��ϴ�");
				return;
			}
			if(nAmount > 1000000)
			{
				LF->MsgBox("�ݾ������� 10000000�� �̻��� ������� �ʽ��ϴ�");
				return;
			}

			for(int i = 0; i < nSelectedCount; i++)
			{
				long nRiderCompany = m_RiderList.GetItemLong(m_RiderList.GetSelectedRowsGetAtGetRecord(i));
				long nRow = m_RiderList.GetSelectedRows()->GetAt(i)->GetIndex();
				long nRNo = atol(m_RiderList.GetItemText(nRow,1));
				int	nReturn = -1;
				CString sEtc = dlg.m_sValue2;
				if(nRNo <= 0)
				{
					LF->MsgBox("����ȣ�� 0 ���� �Դϴ�. ��������Ʈ�� �����ϼ���");
					return;
				}

				CMkRecordset pRs(m_pMkDb);
				CMkCommand pCmd(m_pMkDb, "update_rider_mileage_balance_modify");
				pCmd.AddParameter(nRiderCompany);
				pCmd.AddParameter(nRNo);
				pCmd.AddParameter(m_cmbCouphon.GetCurSel());
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(nAmount);
				pCmd.AddParameter(sEtc);
				pCmd.AddParameter(TRUE);
				CMkParameter* pPar = pCmd.AddParameterRefOutput(nReturn);

				if (!pRs.Execute(&pCmd))
					return;
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
	if(!LF->POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_OrderList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_OrderList);
}

void CReportForm20::OnViewExcel2()
{
	if(!LF->POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_LogList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_LogList);
}

void CReportForm20::OnViewExcel3()
{
	if(!LF->POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 321, m_ui.nWNo, m_LogList.GetRows()->GetCount());  
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