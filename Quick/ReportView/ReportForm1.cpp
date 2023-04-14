
#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "ReportView.h"
#include "ReportForm1.h"
#include "CustomerDlg.h"
#include "RcpDlg.h"
#include "ColumnSelDlg.h"
#include "WebPrintDlg1.h"

// CReportForm1 대화 상자입니다.

IMPLEMENT_DYNCREATE(CReportForm1, CMyFormView)
CReportForm1::CReportForm1()
	: CMyFormView(CReportForm1::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_dtFrom= COleDateTime::GetCurrentTime() - span;
	m_dtTo= COleDateTime::GetCurrentTime();
	m_nSearchNo = 0;
	m_bGroup = FALSE;
	m_nOneRefresh = 0;
	m_nCNo = 0;
}

CReportForm1::~CReportForm1()
{
	m_CustomerList.SaveReportOrder("CReportForm1", "m_CustomerList");

	if(m_List.GetColumns()->GetCount() > 22)
		m_List.SaveReportOrder("CReportForm1", "m_List_Group");
	else
		m_List.SaveReportOrder("CReportForm1", "m_List");
}

void CReportForm1::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_LIST_REPORT, m_List);
	DDX_Control(pDX, IDC_COMBO_SEL, m_TypeCombo);
	DDX_CBString(pDX, IDC_COMBO_SEL, m_strType);
	DDX_Control(pDX, IDC_GROUP_COMBO, m_GroupCombo);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_CustomerList);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_SearchBtn);
	DDX_Control(pDX, IDC_GROUP_SEARCH_BTN, m_GroupSearchBtn);
	DDX_Control(pDX, IDC_EXPLAIN_STATIC, m_ExplainStatic);
	DDX_Control(pDX, IDC_FIND_BTN, m_btnFind);
	DDX_Control(pDX, IDC_ONE_SEARCH_BTN, m_OneSearchBtn);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_CREDIT_EDIT, m_edtCredit);
	DDX_Control(pDX, IDC_CASH_EDIT, m_edtCash);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT, m_edtSearchGroup);
}


BEGIN_MESSAGE_MAP(CReportForm1, CMyFormView)
	ON_BN_CLICKED(IDC_GROUP_SEARCH_BTN, OnBnClickedGroupSearch)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_ONE_SEARCH_BTN, OnBnClickedOneSearchBtn)
	ON_BN_CLICKED(IDC_FIND_BTN, OnBnClickedFindBtn)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_LIST_REPORT, OnReportSelChange)
	ON_NOTIFY(XTP_NM_GRID_HEADER_RCLICK, IDC_LIST_REPORT, OnReportColumnRClick)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REPORT, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, OnReportItemDblClick)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_PRINT, OnPrint)
	ON_COMMAND(ID_VISIBLE_COL, OnVisibleCol)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT, &CReportForm1::OnEnChangeSearchGroupEdit)
	ON_BN_CLICKED(IDC_WORK_SEARCH_BTN, &CReportForm1::OnBnClickedWorkSearchBtn)
END_MESSAGE_MAP()


// CReportForm1 메시지 처리기입니다.


void CReportForm1::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_CustomerList.SetImageList(&ImageList,LVSIL_SMALL); 
	m_CustomerList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_CustomerList.InsertColumn(0,"No.",LVCFMT_CENTER, 40);
	m_CustomerList.InsertColumn(1,"고객명",LVCFMT_LEFT, 90);
	m_CustomerList.InsertColumn(2,"부서",LVCFMT_LEFT, 65);
	m_CustomerList.InsertColumn(3,"담당",LVCFMT_LEFT, 65);
	m_CustomerList.InsertColumn(4,"기준동",LVCFMT_RIGHT, 60);

	if(m_ci.m_bCreditAfterDiscount)
		m_ExplainStatic.ShowWindow(TRUE);

	m_TypeCombo.SetCurSel(0);
	RefreshGroup();

	m_CustomerList.LoadReportOrder("CReportForm1", "m_CustomerList");

	SetResize(IDC_CUSTOMER_LIST, sizingBottom);
	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CReportForm1::InitColumn(BOOL bGroup)
{
	int nColCount = m_List.GetColumns()->GetCount();

	for(int i=0;i < nColCount;i++)  
	{
		CXTPGridColumns *pColums = m_List.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}
 
	if(!bGroup) {
		m_List.InsertColumn(0,"No.",LVCFMT_LEFT,40);
		m_List.InsertColumn(1,"오더No",LVCFMT_RIGHT, 55);
		m_List.InsertColumn(2,"주문일",LVCFMT_LEFT,50);
		m_List.InsertColumn(3,"처리일",LVCFMT_LEFT,50);
		m_List.InsertColumn(4,"출발지",LVCFMT_LEFT,120);
		m_List.InsertColumn(5,"출발지담당",LVCFMT_LEFT,120);
		m_List.InsertColumn(6,"출발지부서",LVCFMT_LEFT, 70);
		m_List.InsertColumn(7,"출발지번호",LVCFMT_LEFT, 100);
		m_List.InsertColumn(8,"도착지",LVCFMT_LEFT,120);
		m_List.InsertColumn(9,"도착지담당",LVCFMT_LEFT,120);
		m_List.InsertColumn(10,"도착지부서",LVCFMT_LEFT, 70);
		m_List.InsertColumn(11,"도착지번호",LVCFMT_LEFT, 100);
		m_List.InsertColumn(12,"배송자회사",LVCFMT_RIGHT,100);
		m_List.InsertColumn(13,"배송자",LVCFMT_RIGHT,60);
		m_List.InsertColumn(14,"기본",LVCFMT_RIGHT,50);
		m_List.InsertColumn(15,"추가",LVCFMT_RIGHT,50);
		m_List.InsertColumn(16,"할인",LVCFMT_RIGHT,50);
		m_List.InsertColumn(17,"합계",LVCFMT_RIGHT,50);
		m_List.InsertColumn(18,"탁송료",LVCFMT_RIGHT,50);
		m_List.InsertColumn(19,"왕복",LVCFMT_CENTER,40);
		m_List.InsertColumn(20,"차종",LVCFMT_CENTER,40);
		m_List.InsertColumn(21,"결제",LVCFMT_CENTER,40);
		m_List.InsertColumn(22,"비고",LVCFMT_CENTER,40);
		m_List.InsertColumn(23,"적요",LVCFMT_CENTER,120);
		m_List.InsertColumn(24,"접수",LVCFMT_CENTER,120);
		m_List.InsertColumn(25,"배차",LVCFMT_CENTER,120);
		m_List.InsertColumn(26,"픽업",LVCFMT_CENTER,120);
		m_List.InsertColumn(27,"완료",LVCFMT_CENTER,120);		
		m_List.InsertColumn(28,"인터넷",LVCFMT_CENTER,50);
	}
	else {
		m_List.InsertColumn(0,"No.",LVCFMT_LEFT,40);
		m_List.InsertColumn(1,"오더No",LVCFMT_RIGHT, 55);
		m_List.InsertColumn(2,"주문일",LVCFMT_LEFT,50);
		m_List.InsertColumn(3,"처리일",LVCFMT_LEFT,50);
		m_List.InsertColumn(4,"소속",LVCFMT_LEFT, 90);
		m_List.InsertColumn(5,"부서",LVCFMT_LEFT, 60);
		m_List.InsertColumn(6,"담당",LVCFMT_LEFT, 50);
		m_List.InsertColumn(7,"출발지",LVCFMT_LEFT,90);
		m_List.InsertColumn(8,"출발동",LVCFMT_LEFT,90);
		m_List.InsertColumn(9,"출발지담당",LVCFMT_LEFT,120);
		m_List.InsertColumn(10,"출발지부서",LVCFMT_LEFT, 70);
		m_List.InsertColumn(11,"출발지번호",LVCFMT_LEFT, 100);
		m_List.InsertColumn(12,"도착지",LVCFMT_LEFT,90);
		m_List.InsertColumn(13,"도착동",LVCFMT_LEFT,90);
		m_List.InsertColumn(14,"도착지담당",LVCFMT_LEFT,120);
		m_List.InsertColumn(15,"도착지부서",LVCFMT_LEFT, 70);
		m_List.InsertColumn(16,"도착지번호",LVCFMT_LEFT, 100);
		m_List.InsertColumn(17,"배송자회사",LVCFMT_RIGHT,100);
		m_List.InsertColumn(18,"배송자",LVCFMT_RIGHT,60);
		m_List.InsertColumn(19,"기본",LVCFMT_RIGHT,40);
		m_List.InsertColumn(20,"추가",LVCFMT_RIGHT,40);
		m_List.InsertColumn(21,"할인",LVCFMT_RIGHT,40);
		m_List.InsertColumn(22,"합계",LVCFMT_RIGHT,40);
		m_List.InsertColumn(23,"탁송료",LVCFMT_RIGHT,50);
		m_List.InsertColumn(24,"왕복",LVCFMT_CENTER,40);
		m_List.InsertColumn(25,"차종",LVCFMT_CENTER,40);
		m_List.InsertColumn(26,"결제",LVCFMT_CENTER,40);
		m_List.InsertColumn(27,"비고",LVCFMT_CENTER,40);
		m_List.InsertColumn(28,"적요",LVCFMT_CENTER,120);
		m_List.InsertColumn(29,"접수",LVCFMT_CENTER,50);
		m_List.InsertColumn(30,"배차",LVCFMT_CENTER,50);
		m_List.InsertColumn(31,"픽업",LVCFMT_CENTER,50);
		m_List.InsertColumn(32,"완료",LVCFMT_CENTER,50);
		m_List.InsertColumn(33,"인터넷",LVCFMT_CENTER,60);
		m_List.InsertColumn(34,"발신번호",LVCFMT_CENTER,60);
	}

	if(bGroup) 
		m_List.LoadReportOrder("CReportForm1", "m_List_Group");
	else
		m_List.LoadReportOrder("CReportForm1", "m_List");
}

void CReportForm1::SearchCustomer(BOOL bClickGroup)
{
	CWaitCursor wait;
	CString csCNo;
	CString csTemp;
	int nItem = 0;
	char buffer[20];

	long nCNo, nID;//, nTeamNo;
	CString strCompany, strDepart, strName;
	CString strTel1, strDong, strLocation, strPost;
//	BOOL bCredit;
//	int nDiscount;

	m_CustomerList.DeleteAllItems();
	if(m_strKeyword.IsEmpty()) return;

	CMkCommand pCmd(m_pMkDb, "search_customer_for_report_2");
	CMkRecordset pRs(m_pMkDb);

	//if(m_bCheckMidWord && m_nSearchType == ST_COMPANY) m_nSearchType++;
	m_nSearchNo = 0;

	if(bClickGroup)
		m_nSearchType = ST_GROUP_NO;

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), (int)m_nSearchType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);

 
	if(!pRs.Execute(&pCmd)) return;

	if(!pRs.IsEOF()) {
		parRet->GetValue(m_nSearchNo); }

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		//pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sDong", strDong);
		//pRs.GetFieldValue("sLocation", strLocation);
		//pRs.GetFieldValue("bCredit", bCredit);
		//pRs.GetFieldValue("nDiscount", nDiscount);
		//pRs.GetFieldValue("nTeamNo", nTeamNo);
	
		m_CustomerList.InsertItem(nItem, ltoa(nID, buffer, 10));
		m_CustomerList.SetItemText(nItem, 1, strCompany);
		m_CustomerList.SetItemText(nItem, 2, strDepart);
		m_CustomerList.SetItemText(nItem, 3, strName);
		m_CustomerList.SetItemText(nItem, 4, strDong);
		m_CustomerList.SetItemData(nItem, nCNo);
		pRs.MoveNext();
		nItem++;
	}	
	
	pRs.Close();

	m_CustomerList.Populate();
}

void CReportForm1::RefreshList( ) 
{
	CMyFormView::RefreshList();

	if(m_List.GetColumns()->GetCount() > 22)
		m_List.SaveReportOrder("CReportForm1", "m_List_Group");
	else
		m_List.SaveReportOrder("CReportForm1", "m_List");
 
	CWaitCursor wait;
	CString csTable,csFilter;

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	CString sSql = "", sCNo = "", sSearchWord = "";
	CString sCNoList[10] = {"", };
 
	sSql = "select_customer_report4_9";
	if(m_nOneRefresh == 1) //개별조회 클릭한 경우
	{
		long nCount = m_CustomerList.GetSelectedRows()->GetCount();
		if(nCount <= 0)
		{
			MessageBox("고객을 선택하세요(다중선택 고객도 가능합니다.)", "확인", MB_ICONINFORMATION);
			return;
		}

		if(nCount > 2500)
		{
			MessageBox("2500명이상 동시조회 불가능 합니다", "확인", MB_ICONINFORMATION);
			return;
		}

		for(int i =0; i < nCount; i++)
		{
			CXTPGridRow *pRow = m_CustomerList.GetSelectedRows()->GetAt(i);
			long nCNo = m_CustomerList.GetItemData(pRow->GetRecord());
			if(nCNo > 0) //300개씩 집어넣기
			{
				sCNo.Format("%ld,", nCNo);
				sCNoList[i/300] += sCNo; 
			}
		}	
		//sSql = "select_customer_one_report_3";
		if(sCNoList[0].GetLength() <= 0)
		{
			//MessageBox("검색할 고객이 없습니다. 이상이 있을시 로지소프트로 문의하세요", "확인", MB_ICONINFORMATION);
			return;

		}
		
	}
	else if(m_nOneRefresh == 2) //개별조회 클릭한 경우
	{
		m_SearchEdit.GetWindowText(sSearchWord);
	}
	else
	{
		long nCount = m_CustomerList.GetRows()->GetCount();
		if(nCount > 2500)
		{
			MessageBox("2500명이상 동시조회 불가능 합니다", "확인", MB_ICONINFORMATION);
			return;
		}

		for(int i =0; i < nCount; i++)
		{
			CXTPGridRow *pRow = m_CustomerList.GetRows()->GetAt(i);
			long nCNo = m_CustomerList.GetItemData(pRow->GetRecord());
			if(nCNo > 0)
			{
				sCNo.Format("%ld,", nCNo);
				sCNoList[i/300] += sCNo; 
			}
		}
		//sSql = "select_customer_report4_3";
		//sSql = "select_customer_report4_9";

		if(sCNoList[0].GetLength() <= 0)
		{
			//MessageBox("검색할 고객이 없습니다. 이상이 있을시 로지소프트로 문의하세요", "확인", MB_ICONINFORMATION);
			return;

		}
	}

	

	long nLength = 0;

	for(int i=0; i<10; i++)
	{
		nLength = nLength +sCNoList[i].GetLength();
	}

	if(nLength > 9500)
	{
		MessageBox("너무 많은 양을 조회 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}
	

	/*if(m_nSearchNo == 0)
		return;*/


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, sSql);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(GetCurBranchInfo()->nCustomerTable);

	//if(m_bOneRefresh) //개별조회 클릭한 경우
	//	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nCNo);
	//else
	//	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nSearchNo);

	pCmd.AddParameter(sCNoList[0]);	
	pCmd.AddParameter(sCNoList[1]);	
	pCmd.AddParameter(sCNoList[2]);	
	pCmd.AddParameter(sCNoList[3]);	
	pCmd.AddParameter(sCNoList[4]);	
	pCmd.AddParameter(sCNoList[5]);	
	pCmd.AddParameter(sCNoList[6]);	
	pCmd.AddParameter(sCNoList[7]);	
	pCmd.AddParameter(sCNoList[8]);	
	pCmd.AddParameter(sCNoList[9]);		
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_TypeCombo.GetCurSel());	
	pCmd.AddParameter(sSearchWord);		


	if(!pRs.Execute(&pCmd)) 
		return;
 
	int nItem = 0;
	CString csNo,csTemp,csTemp1;

	long nTNo, nCash =0, nCredit =0 , nOnline= 0;
	COleDateTime dt0, dt1, dt2, dt3, dt4, dtFinal;
	CString strOWNER, strDepart, strName;
	CString strStart, strDest, strDManager;
	int nRNo, nCarType, nPayType, nWayType, nState;
	long nTotalFee = 0, nTotalConFee = 0, nTotalSum = 0;
	char buffer[20];
	BOOL bInternet;
	CString strSDong, strDDong, sEtc, sRiderCompany, strSManager, strSDepart, strDDepart, strSPhone, strDPhone, strRName, strCID;
	long nChargeBasic, nChargeDis, nChargeAdd, nChargeTrans, nChargeSum;
	long nSChargeBasic = 0, nSChargeDis = 0, nSChargeAdd = 0, nSChargeTrans = 0, nSChargeSum = 0;
	long nSChargeCreditTrans = 0, nRiderCompany;

//	m_bGroup = m_CustomerList.GetItemCount() > 1;
	m_bGroup = TRUE;
	InitColumn(m_bGroup);


	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("OWNER", strOWNER);
		pRs.GetFieldValue("dt0", dt0);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("dt2", dt2);
		pRs.GetFieldValue("dt3", dt3);
		pRs.GetFieldValue("dt4", dt4);
		pRs.GetFieldValue("dtFinal", dtFinal);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nCarType", nCarType); 
		pRs.GetFieldValue("nWayType", nWayType);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("sRiderCompany", sRiderCompany);
		pRs.GetFieldValue("bInternet", bInternet);
		pRs.GetFieldValue("sSManager", strSManager);
		pRs.GetFieldValue("sDManager", strDManager);
		pRs.GetFieldValue("sSDepart", strSDepart);
		pRs.GetFieldValue("sDDepart", strDDepart);
		pRs.GetFieldValue("sSPhone", strSPhone);
		pRs.GetFieldValue("sDPhone", strDPhone);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("sCID", strCID);
					
		int nCol = 1;

		//if(nItem == 0) m_sCompany = strOWNER;
		m_List.InsertItem(nItem, ltoa(nItem + 1, buffer, 10));
		m_List.SetItemText(nItem,nCol++, ltoa(nTNo, buffer, 10));
		m_List.SetItemText(nItem, nCol++, dt0.Format("%m-%d"));
		m_List.SetItemText(nItem, nCol++, dt1.Format("%m-%d"));

		if(m_bGroup) {
			m_List.SetItemText(nItem, nCol++, strOWNER);
			m_List.SetItemText(nItem, nCol++, strDepart);
			m_List.SetItemText(nItem, nCol++, strName);
		}

		//if(strStart != strSDong && !strStart.IsEmpty() && !strSDong.IsEmpty())
         //   m_List.SetItemText(nItem, nCol++, strStart + "(" + strSDong + ")");
		//else if(!strStart.IsEmpty())
         //   m_List.SetItemText(nItem, nCol++, strStart); //7
		//else if(!strSDong.IsEmpty())
		//	m_List.SetItemText(nItem, nCol++, strSDong); //7

		m_List.SetItemText(nItem, nCol++, strStart); //7
		m_List.SetItemText(nItem, nCol++, strSDong); //7

		m_List.SetItemText(nItem, nCol++, strSManager); //7
		m_List.SetItemText(nItem, nCol++, strSDepart); //
		m_List.SetItemText(nItem, nCol++, ::GetDashPhoneNumber(strSPhone)); //

		//if(strDest != strDDong && !strDest.IsEmpty() && !strDDong.IsEmpty())
		//	m_List.SetItemText(nItem, nCol++, strDest + "(" + strDDong + ")");
		//else if(!strDest.IsEmpty())
		//	m_List.SetItemText(nItem, nCol++, strDest);
		//else
        //   m_List.SetItemText(nItem, nCol++, strDDong);

		m_List.SetItemText(nItem, nCol++, strDest);
		m_List.SetItemText(nItem, nCol++, strDDong);

		m_List.SetItemText(nItem, nCol++, strDManager);
		m_List.SetItemText(nItem, nCol++, strDDepart); //
		m_List.SetItemText(nItem, nCol++, ::GetDashPhoneNumber(strDPhone)); //
		m_List.SetItemText(nItem, nCol++, sRiderCompany);

		if(m_ci.IsChildCompany(nRiderCompany) && ::IsThisCompany("대한퀵물류"))
			csTemp = strRName;
		else
			csTemp.Format("%d 호", nRNo);		
		
		m_List.SetItemText(nItem, nCol++, csTemp);

 		nSChargeBasic += nChargeBasic;
		nSChargeDis += nChargeDis;
		nSChargeAdd += nChargeAdd; 		
		nSChargeTrans += nChargeTrans;
		nSChargeSum += nChargeSum;

		switch(nPayType)
		{
		case 0:
		case 1:
		case 5:
			nCash += nChargeSum;
			break;
		case 2:
			nCredit += nChargeSum;
			nSChargeCreditTrans += nChargeTrans;
			break;
		case 3:
			nOnline += nChargeSum;
			nSChargeCreditTrans += nChargeTrans;
			break;
		}

		m_List.SetItemText(nItem, nCol++, GetMyNumberFormat(nChargeBasic)); //11
		m_List.SetItemText(nItem, nCol++, GetMyNumberFormat(nChargeAdd));
		m_List.SetItemText(nItem, nCol++, GetMyNumberFormat(nChargeDis));
		m_List.SetItemText(nItem, nCol++, GetMyNumberFormat(nChargeSum));
		m_List.SetItemText(nItem, nCol++, RemoveZero(GetMyNumberFormat(nChargeTrans)));
		m_List.SetItemText(nItem, nCol++, GetWayTypeFromLong(nWayType)); 
		m_List.SetItemText(nItem, nCol++, GetCarTypeFromLong(nCarType));
		m_List.SetItemText(nItem, nCol++, GetPayTypeFromLong(nPayType));//18
		m_List.SetItemText(nItem, nCol++, GetStateString(nState)); 
		m_List.SetItemText(nItem, nCol++, sEtc); 
		m_List.SetItemText(nItem, nCol++, dt1.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, dt3.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, dt4.Format("%H:%M")); 
		m_List.SetItemText(nItem, nCol++, dtFinal.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, bInternet ? "O" : "X");
		m_List.SetItemText(nItem, nCol++, strCID);
 
		m_List.SetItemNoSort(nItem++, FALSE);

		pRs.MoveNext();
	}
	pRs.Close();

	if(nItem > 0)
	{
		m_List.InsertItem(nItem,""); 
		m_List.SetItemText(nItem, 19, GetMyNumberFormat(nSChargeBasic)); 
		m_List.SetItemText(nItem, 20, GetMyNumberFormat(nSChargeAdd));
		m_List.SetItemText(nItem, 21, GetMyNumberFormat(nSChargeDis));
		m_List.SetItemText(nItem, 22, GetMyNumberFormat(nSChargeSum));
		m_List.SetItemNoSort(nItem++, TRUE);

		m_List.InsertItem(nItem,"");
		m_List.SetItemText(nItem,3,"합계(운행료+탁송)");
		m_List.SetItemText(nItem,6,"운행료");
		m_List.SetItemText(nItem,7,"탁송료");
		m_List.SetItemNoSort(nItem++, TRUE);


		m_List.InsertItem(nItem,"");
		m_List.SetItemText(nItem,3, GetMyNumberFormat(nSChargeSum + nSChargeCreditTrans));
		m_List.SetItemText(nItem,6, GetMyNumberFormat(nSChargeSum));
		m_List.SetItemText(nItem,7, GetMyNumberFormat(nSChargeCreditTrans));


		m_List.SetItemNoSort(nItem++, TRUE);

		m_List.InsertItem(nItem,"");
		m_List.SetItemNoSort(nItem++, TRUE);

		m_List.InsertItem(nItem,"");	
		m_List.SetItemText(nItem, 2, "신용");
		m_List.SetItemText(nItem, 3, GetMyNumberFormat(nCredit));
		m_List.SetItemText(nItem, 4, "온라인");
		m_List.SetItemText(nItem, 5, GetMyNumberFormat(nOnline));
		m_List.SetItemText(nItem, 6, "현금");
		m_List.SetItemText(nItem, 7, GetMyNumberFormat(nCash));
		m_List.SetItemText(nItem, 8, "탁송");
		m_List.SetItemText(nItem, 9, GetMyNumberFormat(nTotalConFee));
		m_List.SetItemNoSort(nItem++, TRUE);
		
		CString sCreditDis,sCashDis;
		long nCreditDisCount = 0, nCashDisCount = 0;
		m_edtCash.GetWindowText(sCashDis);
		m_edtCredit.GetWindowText(sCreditDis);
		nCreditDisCount = atol(sCreditDis); nCashDisCount = atol(sCashDis);

		m_List.InsertItem(nItem,"");
		m_List.SetItemText(nItem, 2, "할인");
		m_List.SetItemText(nItem, 3, sCashDis.GetLength() > 0 ? sCashDis + "%" : "");
		m_List.SetItemText(nItem, 6, "할인");
		m_List.SetItemText(nItem, 7, sCreditDis.GetLength() > 0 ? sCreditDis + "%" : "");
		m_List.SetItemNoSort(nItem++, TRUE);

		//strTemp.Format("%d", nCash * (100 - atol(m_strCashRate)) / 100 );

		m_List.InsertItem(nItem,"");
		m_List.SetItemText(nItem, 2, "신용할인");
		m_List.SetItemText(nItem, 3, GetMyNumberFormat(nCredit* (100 - nCreditDisCount)/100));
		m_List.SetItemText(nItem, 6, "현금할인");
		m_List.SetItemText(nItem, 7, GetMyNumberFormat(nCash* (100 - nCashDisCount) /100));
		m_List.SetItemNoSort(nItem++, TRUE);
	}

	m_List.Populate();
}

void CReportForm1::OnBnClickedGroupSearch()
{
	UpdateData(TRUE);

	m_strKeyword.Format("%d", m_GroupCombo.GetItemData(m_GroupCombo.GetCurSel()));
	SearchCustomer(TRUE);
	RefreshList();
}

void CReportForm1::OnCancel()
{
	//CMyFormView::OnCancel();
}

void CReportForm1::OnOK()
{
	//CMyFormView::OnOK();
}

void CReportForm1::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPGridColumn *p = m_List.GetColumns()->GetAt(0); 
	if(p == NULL) return; 

	long h = m_List.GetReportHeader()->GetGroupByHeight();

	CRect rcHeader = p->GetRect(); 
	//ScreenToClient(rcHeader);

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = NULL;

	if(point.y >= rect.top && 
		//point.y <= rect.top + rcHeader.Height())
		point.y <= rect.top + h )
	{
		pRMenu=rMenu.GetSubMenu(22);
	}
	else
		pRMenu=rMenu.GetSubMenu(34);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm1::OnViewExcel()
{
	if(!POWER_CHECK(3900, "엑셀변환", TRUE))
		return;
 
	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 301, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}

void CReportForm1::OnPrint()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	long nCount = pRows->GetCount();

	CString strTNoSum = "";

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord(); 
		CString strItem = pRecord->GetItem(1)->GetCaption(NULL);

		if(!strItem.IsEmpty() && IsNumber(strItem))
			strTNoSum += strItem + ","; 
	}

	if(strTNoSum.IsEmpty())
	{
		MessageBox("오더를 검색 후 프린터 출력을 하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CWebPrintDlg1 dlg;
	dlg.m_strUrl = "http://work.logisoft.co.kr:8000/CustomerReport/CustomerReport.asp?sTNo=" + strTNoSum;
	dlg.m_strUrl += "&nLoginCompany=" + ::GetStringFromLong(m_ui.nCompany) + "&nSiteSessionKey=" + ::GetStringFromLong(m_ui.nSiteSessionKey);
	dlg.DoModal();

	//http://211.172.242.163:5000/CustomerReport/CustomerReport.asp?sTNo=80581000,

	//http://211.172.242.163:5000/CustomerReport/CustomerReport.asp
	//nCNo strFromDate strToDate
	//작업계속 163//
	// C:\F\www_root\work.logisoft.co.kr\CustomerReport
}

BOOL CReportForm1::PreTranslateMessage(MSG* pMsg)
{
	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT)
	{
		if(pMsg->message == WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
				case VK_RETURN:
					OnBnClickedFindBtn();
					return TRUE;
					break;


			}
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CReportForm1::RefreshGroup()
{
	MAP_CUSTOMER_GROUP::iterator it;
	MAP_CUSTOMER_GROUP *pMap = m_cg.GetGroup();

	long nItem =0;
	for(it = pMap->begin(); it != pMap->end(); it++)
	{
		m_GroupCombo.InsertString(nItem, it->second->strGroupName);
		m_GroupCombo.SetItemData(nItem++, it->first);
	}
	/*
	long nGNo, nMembers;
	CString strGroupName, strDetail, strPassword;
//	char buffer[20];
	long nItem = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCustomerTable);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("strGroupName", strGroupName);
		pRs.GetFieldValue("nMembers", nMembers);
		pRs.GetFieldValue("strDetail", strDetail);
		pRs.GetFieldValue("strPassword", strPassword);

		int nItem = m_GroupCombo.AddString(strGroupName);
		m_GroupCombo.SetItemData(nItem, nGNo);

		pRs.MoveNext();
		nItem++;
	}

	pRs.Close();
	*/
}

void CReportForm1::OnBnClickedSearchBtn()
{
	m_nOneRefresh = 0;
	//OnBnClickedSearch(); 
	RefreshList();
}

void CReportForm1::OnBnClickedFindBtn()
{
	UpdateData(TRUE);

	if(!m_strSearch.IsEmpty()) {
		if(CRcpDlg::MakeSearchQuery(m_strSearch, m_strKeyword, &m_nSearchType)) {
			SearchCustomer();
		}
	}
}




void CReportForm1::OnBnClickedWorkSearchBtn()
{
	
		m_nCNo = 0;	
	m_nOneRefresh = 2;
	RefreshList();

}
void CReportForm1::OnBnClickedOneSearchBtn()
{
	long index = m_CustomerList.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{	
		m_nCNo = 0;
		return;
	}

	m_nCNo = m_CustomerList.GetItemData(index);

	m_nOneRefresh = 1;
	RefreshList();
}

void CReportForm1::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CPoint pt;
	::GetCursorPos(&pt);
}

void CReportForm1::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	
}


void CReportForm1::OnReportSelChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{	
}

void CReportForm1::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CPoint pt;
	::GetCursorPos(&pt);

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	menu.AppendMenu(MF_STRING, ID_VISIBLE_COL, "컬럼숨김");
	menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
}

void CReportForm1::OnVisibleCol()
{ 
	CColumnSelDlg dlg;
	dlg.m_plstReport = (CXTPListCtrl2*)&m_List;
	dlg.m_sClass = "CReportForm1";

	if(m_List.GetColumns()->GetCount() > 22)
		dlg.m_sList = "m_List_Group";
	else
		dlg.m_sList = "m_List";
	
	if(dlg.DoModal())
	{
		m_List.LoadReportOrder(dlg.m_sClass, dlg.m_sList);
		m_List.Populate();
	}
}

void CReportForm1::OnEnChangeSearchGroupEdit()
{
	CString strGroup; m_edtSearchGroup.GetWindowText(strGroup);

	int nCount = m_GroupCombo.GetCount();

	for(int i=0; i<nCount; i++)
	{
		CString strGroupTemp;
		m_GroupCombo.GetLBText(i, strGroupTemp);

		if(strGroupTemp.Find(strGroup) >= 0)
		{
			m_GroupCombo.SetCurSel(i);
			break;
		}
	}
}