// ReportForm19.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm19.h"
//#include "CustomerAddNoMapDlg.h"

//#include "CustomerSMSTotal.h"

// CReportForm19 대화 상자입니다.

IMPLEMENT_DYNCREATE(CReportForm19, CMyFormView)
CReportForm19::CReportForm19()
	: CMyFormView(CReportForm19::IDD)
	, m_dtFrom(COleDateTime::GetCurrentTime())
	, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CReportForm19::~CReportForm19()
{
}

void CReportForm19::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);

	DDX_Control(pDX, IDC_LCLEFT_LIST, m_lstLeft);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstData);

	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_BALANCE_FROM_EDIT, m_edtBalanceFrom);
	DDX_Control(pDX, IDC_BALANCE_TO_EDIT, m_edtBalanceTo);
	DDX_Control(pDX, IDC_OPTION_COMBO, m_cmbOption);
	DDX_Control(pDX, IDC_BALANCE_EDIT, m_edtBalance);
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileageModify);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSearch);
}


BEGIN_MESSAGE_MAP(CReportForm19, CMyFormView)
	ON_BN_CLICKED(IDC_ORDER_SEARCH_BTN, OnBnClickedOrderSearchBtn)	
	ON_BN_CLICKED(IDC_MILEAGE_ALL_BTN, OnBnClickedMileageAllBtn)
	ON_NOTIFY(NM_CLICK, IDC_LCLEFT_LIST, OnLvnItemchangedListLeft)
	ON_NOTIFY(NM_DBLCLK, IDC_LCLEFT_LIST, OnLvnItemDbClickListLeft)

	ON_NOTIFY(NM_RCLICK, IDC_LCLEFT_LIST, OnReportItemRClick)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REPORT, OnlstDataItemRClick)

	



	ON_BN_CLICKED(IDC_MILEAGE_MODIFY_BTN, OnBnClickedMileageModifyBtn)
	ON_BN_CLICKED(IDC_BALANCE_SEARCH_BTN, OnBnClickedBalanceSearchBtn)
	ON_BN_CLICKED(IDC_BALANCE_MODIFY_BUTTON, OnBnClickedBalanceModifyButton)
	ON_CBN_SELCHANGE(IDC_OPTION_COMBO, OnCbnSelchangeOptionCombo)
	ON_CBN_SELCHANGE(IDC_SEARCH_COMBO, OnCbnSelchangeSearchCombo)
	ON_BN_CLICKED(IDC_BALANCE_INIT_BUTTON, OnBnClickedBalanceInitButton)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_VIEW_EXCEL2, OnViewExcel2)
	ON_BN_CLICKED(IDC_DIRECT_MODIFY_BUTTON, OnBnClickedDirectModifyButton)
	
	ON_BN_CLICKED(IDC_MIALEAGE_SMS_BTN, OnBnClickedMialeageSmsBtn)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CReportForm19 메시지 처리기입니다.
void CReportForm19::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	//m_FromDT.SetFormat("yyyy-MM-dd HH:00");
	//m_ToDT.SetFormat("yyyy-MM-dd HH:59");
	m_btnDate.OnMenuToday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lstData.SetImageList(&ImageList,LVSIL_SMALL); 
	m_lstData.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_lstData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	int nItem = 0;

	CXTPGridColumn* pCol0 = m_lstLeft.AddColumn(new CXTPGridColumn(0, _T("고객명"), 90, FALSE));
	CXTPGridColumn* pCol1 = m_lstLeft.AddColumn(new CXTPGridColumn(1, _T("전화1"), 88,FALSE));		
	CXTPGridColumn* pCol2 = m_lstLeft.AddColumn(new CXTPGridColumn(2, _T("전화2"), 60,FALSE));
	CXTPGridColumn* pCol3 = m_lstLeft.AddColumn(new CXTPGridColumn(3, _T("그룹명"), 80,FALSE));
	CXTPGridColumn* pCol4 = m_lstLeft.AddColumn(new CXTPGridColumn(4, _T("구분"), 35,FALSE));
	CXTPGridColumn* pCol5 = m_lstLeft.AddColumn(new CXTPGridColumn(5, _T("횟수"), 35,FALSE));
	CXTPGridColumn* pCol6 = m_lstLeft.AddColumn(new CXTPGridColumn(6, _T("마일리지"), 55,FALSE));	
	CXTPGridColumn* pCol7 = m_lstLeft.AddColumn(new CXTPGridColumn(7, _T("개별마일"), 55,FALSE));		

	pCol0->SetAlignment(DT_LEFT);
	pCol1->SetAlignment(DT_LEFT);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);
	pCol4->SetAlignment(DT_LEFT);
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->SetAlignment(DT_RIGHT);	

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->GetEditOptions()->m_bAllowEdit = TRUE;
	
	m_lstLeft.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstLeft.SetTreeIndent(30);
	m_lstLeft.SetGridColor(RGB(222, 222, 222));
	m_lstLeft.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	//m_lstLeft.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstLeft.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstLeft.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstLeft.GetReportHeader()->AllowColumnResize(FALSE);
	
	m_lstLeft.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstLeft.AllowEdit(TRUE);
	m_lstLeft.FocusSubItems(TRUE);
	m_lstLeft.Populate();	

	nItem = 0;
	m_lstData.InsertColumn(nItem++, "오더번호", LVCFMT_LEFT, 65);
	m_lstData.InsertColumn(nItem++, "회사명", LVCFMT_LEFT, 70);
	m_lstData.InsertColumn(nItem++, "고객명", LVCFMT_LEFT, 80);
	m_lstData.InsertColumn(nItem++, "일자", LVCFMT_LEFT, 95);		
	m_lstData.InsertColumn(nItem++, "출발지",LVCFMT_LEFT, 110);
	m_lstData.InsertColumn(nItem++, "도착지",LVCFMT_LEFT, 70);
	m_lstData.InsertColumn(nItem++, "상태",LVCFMT_LEFT,60);
	m_lstData.InsertColumn(nItem++, "금액",LVCFMT_RIGHT,50);
	m_lstData.InsertColumn(nItem++, "마일",LVCFMT_RIGHT,55);		
	m_lstData.InsertColumn(nItem++, "마일잔액",LVCFMT_RIGHT,65);		
	m_lstData.InsertColumn(nItem++, "접수자",LVCFMT_LEFT,60);
	m_lstData.InsertColumn(nItem++, "",LVCFMT_LEFT,0);	

	m_cmbOption.InsertString(2,"마일리지 적용된 오더보기");
	m_cmbOption.SetCurSel(0);
	m_cmbSearch.SetCurSel(0);
	SetResize(IDC_LCLEFT_LIST, sizingBottom);
	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CReportForm19::RefreshList()
{
	if(m_cmbSearch.GetCurSel() == 0)
		SearchEdit();
	else if(m_cmbSearch.GetCurSel() == 1)
		OnBnClickedBalanceSearchBtn();
	else if(m_cmbSearch.GetCurSel() == 2)
		SearchTypeCustomer(FALSE);
	else if(m_cmbSearch.GetCurSel() == 3)
		SearchTypeCustomer(TRUE);
}

void CReportForm19::OnBnClickedOrderSearchBtn()
{
	m_lstData.DeleteAllItems();
	UpdateData(TRUE);	
	
	COleDateTimeSpan dtSpan;
	dtSpan = m_dtTo - m_dtFrom;

	COleDateTime dt(COleDateTime::GetCurrentTime());
	if(dt.GetHour() > 9 && dt.GetHour() < 18)
	{
		if(dtSpan.GetDays() > 31)
		{
			MessageBox("오전 9시 오후 6시 사이에는 1달 간격의 오더만 조회가능합니다.", "확인",MB_ICONINFORMATION);
			return;
		}		
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_order3");	
	pCmd.AddParameter(LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);	
	pCmd.AddParameter(m_cmbOption.GetCurSel());
	
	if(!pRs.Execute(&pCmd)) return;	
	
	CString strWName, strStart, strDest,strCName ;
	long nItem = 0, nTNo = 0, nCompany = 0, nCharge = 0, nTotalMileage = 0,
		nMileageBalance = 0, nCol = 1, nState = 0, nCNo = 0, nTotalCharge =0,nMileage = 0;
	char buffer[20];
	BOOL bOrder = FALSE; COleDateTime dt1;

	CString strState = "";
	
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		long nCno = 0;
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sSName", strStart);
		pRs.GetFieldValue("sDName", strDest);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nMileage", nMileage);
		pRs.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs.GetFieldValue("bOrder", bOrder);
		pRs.GetFieldValue("sWName", strWName);

		if(nState >= 30 && nState <= 35 && bOrder)
			strState = LF->GetStateString(nState);
		else if(!bOrder && nState > 40)
		{
			switch(nState)
			{
			case 101:
				strState = "초기화";
				break;
			case 102:
				strState = "콜수정";
				break;
			case 100:
				strState = "잔액수정";
				break;
			}
		}

		m_lstData.InsertItem(nItem, ltoa(nTNo, buffer,10));
		m_lstData.SetItemText(nItem, nCol++, m_ci.GetBranchName(nCompany));
		m_lstData.SetItemText(nItem, nCol++, strCName);
		m_lstData.SetItemText(nItem, nCol++, dt1.Format("%y-%m-%d %H:%M"));
		m_lstData.SetItemText(nItem, nCol++, strStart);
		m_lstData.SetItemText(nItem, nCol++, strDest);
		m_lstData.SetItemText(nItem, nCol++, strState);
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nCharge));
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileage));
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileageBalance));
		m_lstData.SetItemText(nItem, nCol++, strWName);
		m_lstData.SetItemText(nItem, nCol++, bOrder?"1":"0");
		m_lstData.SetItemData(nItem++, nCNo);

		nTotalCharge += nCharge;
		nTotalMileage += nMileage;

		nCol = 1;
		pRs.MoveNext();
	}

	m_lstData.InsertItem(nItem, "");
	m_lstData.SetItemText(nItem, 5, "합계:");
	m_lstData.SetItemText(nItem, 7,LF->GetMyNumberFormat(nTotalCharge) );
	m_lstData.SetItemText(nItem, 8,LF->GetMyNumberFormat(nTotalMileage) );
	m_lstData.SetItemData(nItem, 0 );


	m_lstData.Populate();
	pRs.Close();
}

void CReportForm19::SearchOnlyCustomerAlone(long nCNo)
{
	m_lstData.DeleteAllItems();
	//UpdateData(TRUE);
	if(nCNo <= 0)
	{
		MessageBox("고객번호가 이상합니다. 다시 선택해주세요","확인",MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_customer_alone3");	
	pCmd.AddParameter(nCNo);
	if(!pRs2.Execute(&pCmd)) return;	

	CString strWName, strStart, strDest, strCName ;
	long nItem = 0, nTNo = 0, nCompany = 0, nCharge = 0,nMileageBalance = 0, nCol = 1, 
		nState = 0, nTotalCharge = 0, nTotalMileage = 0, nMileage= 0;
	char buffer[20];
	BOOL bOrder = FALSE; 
	COleDateTime dt1;

	CString strState = "";	
	
	while(!pRs2.IsEOF())
	{
		long nCno = 0;
		pRs2.GetFieldValue("nTNo", nTNo);
		pRs2.GetFieldValue("nCompany", nCompany);
		pRs2.GetFieldValue("sCName", strCName);
		pRs2.GetFieldValue("dt1", dt1);
		pRs2.GetFieldValue("sStart", strStart);
		pRs2.GetFieldValue("sDest", strDest);
		pRs2.GetFieldValue("nState", nState);
		pRs2.GetFieldValue("nCharge", nCharge);
		pRs2.GetFieldValue("nMileage", nMileage);
		pRs2.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs2.GetFieldValue("bOrder", bOrder);
		pRs2.GetFieldValue("sWName", strWName);

		if(nState >= 30 && nState <= 35 && bOrder)
			strState = LF->GetStateString(nState);
		else if(!bOrder && nState > 40)
		{
			switch(nState)
			{
			case 101:
				strState = "초기화";
				break;
			case 102:
				strState = "콜수정";
				break;
			case 100:
				strState = "잔액수정";
				break;
			case 103:
				strState = "개별마일";
				break;
			}
		}

		m_lstData.InsertItem(nItem, ltoa(nTNo, buffer,10));
		m_lstData.SetItemText(nItem, nCol++, m_ci.GetBranchName(nCompany));
		m_lstData.SetItemText(nItem, nCol++, strCName);
		m_lstData.SetItemText(nItem, nCol++, dt1.Format("%y-%m-%d %H:%M"));
		m_lstData.SetItemText(nItem, nCol++, strStart);
		m_lstData.SetItemText(nItem, nCol++, strDest);
		m_lstData.SetItemText(nItem, nCol++, strState);
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nCharge));
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileage));
		m_lstData.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileageBalance));
		m_lstData.SetItemText(nItem, nCol++, strWName);
		m_lstData.SetItemText(nItem, nCol++, bOrder?"1":"0");
		m_lstData.SetItemData(nItem++, nCNo);

		nCol = 1;

		nTotalCharge += nCharge;
		nTotalMileage += nMileage;
		
		pRs2.MoveNext();
	}

	pRs2.Close();
	m_lstData.InsertItem(nItem, "");
	m_lstData.SetItemText(nItem, 5, "합계:");
	m_lstData.SetItemText(nItem, 7,LF->GetMyNumberFormat(nTotalCharge) );
	m_lstData.SetItemText(nItem, 8,LF->GetMyNumberFormat(nTotalMileage) );
	m_lstData.SetItemData(nItem, 0 );

	m_lstData.Populate();
}

void CReportForm19::SearchEdit()
{
	CString strCustomer = "";
	m_edtSearch.GetWindowText(strCustomer);
	if(strCustomer.GetLength() <= 2)
		return;

	if(strCustomer == "일반")
	{
		MessageBox("일반은 고객 검색을 하실수 없습니다.","확인", MB_ICONINFORMATION);
		return;
	}
	long  nSearchType = FALSE;
	if(LF->IsStringDigit(strCustomer))
	{
		nSearchType = TRUE;
		if(strCustomer.GetLength() < 6 || strCustomer.GetLength() > 12)
			return;
	}		
	else
	{
		nSearchType = FALSE;
		if(strCustomer.GetLength() < 2 )
			return;
	}
	m_lstLeft.GetRecords()->RemoveAll();
	//m_lstLeft.GetColumns()->Clear();
	
		//m_lstLeft.DeleteAllItems();
	
	CString strDate, strCompany, strTel1,strMobile, strAddr, strAddrNo;
	long nItem = 0, nNo = 0, nCol = 1, nCNo =0,nUseCount=0,nMileageBalance =0, 
		nTotalMailage = 0, nType = 0, nGNo = 0,nAdvertCount = 0;
	BOOL bNoSMS = FALSE;
	COleDateTime dtLastSentAdvertSMS;



	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_customer2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSearchType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCustomerTable);	
	pCmd.AddParameter(typeString, typeInput, strCustomer.GetLength(), strCustomer);
	
	if(!pRs.Execute(&pCmd)) return;	

	while(!pRs.IsEOF())
	{		
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sMobile", strMobile);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs.GetFieldValue("nGNo", nGNo);

		m_lstLeft.AddRecord(new CMileageRecord(strCompany, LF->GetDashPhoneNumber(strTel1), LF->GetDashPhoneNumber(strMobile), nGNo, nType, nUseCount, nMileageBalance, nCNo, ""));
		//,  sAddr, sAddrNo, bNoSMS, dtLastSentAdvertSMS, nAdvertCount, 
		//	COleDateTime::GetCurrentTime(),COleDateTime::GetCurrentTime()));
	
		nTotalMailage += nMileageBalance;
		nCol =1;
		pRs.MoveNext();
	}
	pRs.Close();
	m_lstLeft.Populate();
}

BOOL CReportForm19::PreTranslateMessage(MSG* pMsg)
{
	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT && pMsg->wParam == VK_RETURN)
		SearchEdit();
	return CMyFormView::PreTranslateMessage(pMsg);
}

BOOL CReportForm19::CheckData()
{
	return TRUE;
	/*
	COleDateTimeSpan dtSpan;
	COleDateTime dt(COleDateTime::GetCurrentTime());	

		if(dt.GetHour() > 9 && dt.GetHour() < 18)
	{
		MessageBox("오전 9시이후 부터 오후 6시 사이에는 전체조회가 불가능합니다.", "확인",MB_ICONINFORMATION);
		return FALSE;
		
	}
	return TRUE;
	*/
}

void CReportForm19::OnBnClickedMileageAllBtn()
{
	m_cmbSearch.SetCurSel(2);   // 2 전체검색
	SearchTypeCustomer(FALSE);
	return;
	/*

	if(!CheckData())
		return;

	m_lstLeft.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_all_customer2");	
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);	
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;	
	CString strDate, strCName, strTel1,strTel2, strPostNo, strAddr ;
	long nItem = 0, nNo = 0, nCol = 1, nCNo =0,nUseCount=0 ,
		nMileageBalance =0, nOutPut = 0, nTotalMailage = 0, nType = 0, nGNo = 0, nAdvertCount = 0;
	BOOL bNoSMS = FALSE;
	COleDateTime dtLastSentAdvertSMS;

	pPar->GetValue(nOutPut);
	if(nOutPut == 100)
	{
		MessageBox("전체 검색은 오후 6시이후부터 작업이 됩니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sTel2", strTel2);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs.GetFieldValue("nGNo", nGNo);

		m_lstLeft.AddRecord(new CMileageRecord(strCName, strTel1, strTel2, nGNo, nType, nUseCount,nMileageBalance, nCNo, ""));
	
		nTotalMailage += nMileageBalance;

		nCol =1;
		pRs.MoveNext();
	}
	pRs.Close();
	
	if(nItem > 0)
		m_lstLeft.AddRecord(new CMileageRecord("", "", "합계",0, -1, 0, nTotalMailage, 0, ""));
	
	m_lstLeft.Populate();
	*/
}

void CReportForm19::OnLvnItemDbClickListLeft(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetIndex() == MODIFY_MILEAGE)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	CMileageRecord *pRecord = (CMileageRecord *)pItemNotify->pRow->GetRecord();
	if(pRecord->m_nCNo == 0)
		return;
}

void CReportForm19::OnLvnItemchangedListLeft(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetIndex() == MODIFY_MILEAGE)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	CMileageRecord *pRecord = (CMileageRecord *)pItemNotify->pRow->GetRecord();
	if(pRecord->m_nCNo == 0)
		return;	
	
	SearchOnlyCustomerAlone(pRecord->m_nCNo);
}

void CReportForm19::OnBnClickedMileageModifyBtn()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	CString strMsg="";
	CString strModifyAmount, strModifyAmountHiphone;
	m_edtMileageModify.GetWindowText(strModifyAmountHiphone);
	strModifyAmount = strModifyAmountHiphone;
	long nSubtraction = 1;
	if(strModifyAmountHiphone.Left(1) == "-")
	{
		strModifyAmountHiphone.Replace("-","");
		nSubtraction = -1;
	}

	if(strModifyAmountHiphone.GetLength() == 0)
	{
		MessageBox("마일리지 수정금액을 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(!LF->IsStringDigit(strModifyAmountHiphone))
	{
		MessageBox("마일리지 시작 잔액에 숫자를 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}		
	
	//UINT i, uSelectedCount = m_lstData.GetSelectedRows()->GetCount();
	UINT i, uSelectedCount = m_lstData.GetSelectedRows()->GetCount();
	int  nItem = -1;
	long nTNo = 0, nCNo = 0, nAmount= 0;
	if(uSelectedCount > 0)
	{
		for (i = 0; i < uSelectedCount; i++)
		{
			nItem = m_lstData.GetNextItem(nItem, LVNI_SELECTED);
			if(nItem < 0) break;

			nTNo = atol(m_lstData.GetItemText(nItem,0));
			nCNo = (long)m_lstData.GetItemData(nItem);

			nAmount = atol(strModifyAmountHiphone) * nSubtraction;
			//  100 잔액수정, 101 마일리지초기화, 102 마일리지 수정
			
			CMkCommand pCmd(m_pMkDb, "update_mileage_modify");	
			pCmd.AddParameter(nTNo);
			pCmd.AddParameter(0);
			pCmd.AddParameter(nCNo);			
			pCmd.AddParameter(nAmount);
			pCmd.AddParameter(102);   
			pCmd.AddParameter(m_ui.strName);
			pCmd.AddParameter(m_ui.nCompany);	

			pCmd.Execute();
		}

		strMsg.Format("%d건을 수정하였습니다.", i);
		MessageBox(strMsg, "확인",MB_ICONINFORMATION);
	}
}

void CReportForm19::OnBnClickedBalanceSearchBtn()
{
	CString strBalanceFrom = "", strBalanceTo = "";
	CString strHiphoneBalanceFrom = "", strHiphoneBalanceTo = "";
	UpdateData(TRUE);

	m_edtBalanceFrom.GetWindowText(strBalanceFrom);
	m_edtBalanceTo.GetWindowText(strBalanceTo);
	strHiphoneBalanceFrom = strBalanceFrom;
	strHiphoneBalanceTo = strBalanceTo;
	strHiphoneBalanceFrom.Replace("-","");
	strHiphoneBalanceTo.Replace("-","");

	if(strBalanceFrom.GetLength() == 0)
	{
		MessageBox("마일리지 시작 잔액에 숫자를 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(strBalanceTo.GetLength() == 0)
	{
		MessageBox("마일리지 시작 잔액에 숫자를 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(!LF->IsStringDigit(strHiphoneBalanceFrom))
	{
		MessageBox("마일리지 시작 잔액에 숫자를 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}		
	if(!LF->IsStringDigit(strHiphoneBalanceTo))
	{
		MessageBox("마일리지 끝 잔액에 숫자를 기입하세요", "확인", MB_ICONINFORMATION);
		return;
	}		
	COleDateTime dt(COleDateTime::GetCurrentTime());
	if((strBalanceFrom == "0" || strBalanceTo == "0") && (dt.GetHour() >= 19 || dt.GetHour() < 6) )
	{
		MessageBox("잔액 0이 있으면 전고객을 조회해야 하므로\n\r\n\r 오후 7시이후 오전 5시이전에는 사용 하실수 없습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	m_lstLeft.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_balance2");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCustomerTable);	
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(strBalanceFrom));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(strBalanceTo));	

	if(!pRs.Execute(&pCmd)) return;	

	CString strDate, strCName, strTel1, strTel2, strAddr, strPostNo;
	long nItem = 0, nNo = 0, nCol = 1, nCNo = 0,nUseCount = 0,
		nMileageBalance =0, nTotalMailage = 0, nType = 0, nGNo = 0;
		
	COleDateTime dtLastSentAdvertSMS, dtRegister,dtLastSentSMS;
	int i = 0;
	CMileageRecord *pMileageRecord = new CMileageRecord();
	while(!pRs.IsEOF())
	{		
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sTel2", strTel2);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nMileageBalance", nMileageBalance);

		pRs.GetFieldValue("nGNo", nGNo);
	
		m_mapRow[i] = nCNo;
				
		m_lstLeft.AddRecord(new CMileageRecord(strCName, LF->GetDashPhoneNumber(strTel1), LF->GetDashPhoneNumber(strTel2), nGNo, nType, nUseCount, 	nMileageBalance, nCNo, ""));
			nTotalMailage += nMileageBalance;
		nCol =1;
		i++;
		pRs.MoveNext();
	}
	pRs.Close();
	m_lstLeft.Populate();
}

void CReportForm19::OnBnClickedButton1()
{
	CXTPGridRecords *pRecords = m_lstLeft.GetRecords();
	m_lstLeft.DeleteAllItems();
	m_lstLeft.Populate();
	CXTPGridRecords *pRecord2s = new CXTPGridRecords;

	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		pRecord2s->Add(pRecords->GetAt(i));
	}
}

void CReportForm19::MultiSelectBalance(int nType)
{
	// 1초기화 0 수정
	long nBalance = 0;
	if(nType)
	{
		nBalance = 0;
	}
	else
	{
		CString sBalance = "";
		m_edtBalance.GetWindowText(sBalance);
		if(sBalance.GetLength() == 0)
		{
			MessageBox("잔액을 입력하세요", "확인", MB_ICONINFORMATION);
			return;
		}
		if(!LF->IsStringDigit(sBalance))
		{
			MessageBox("숫자를 입력하세요","확인", MB_ICONINFORMATION);
		}
		nBalance = atol(sBalance);
	}

	CXTPGridSelectedRows *pRows = NULL;
	CMileageRecord *pMileageRecord = NULL;
	CXTPGridRecordItem *pItem = NULL;

	int j = 0;
	POSITION pos = m_lstLeft.GetSelectedRows()->GetFirstSelectedRowPosition();
	while(pos != NULL)
	{
		long nCur = m_lstLeft.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		pMileageRecord = (CMileageRecord *)m_lstLeft.GetRecords()->GetAt(nCur);
			
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_mileage_apply_balance");	
		pCmd.AddParameter(pMileageRecord->m_nCNo);			
		pCmd.AddParameter(nBalance);		
		pCmd.AddParameter(m_ui.strName);		
		pCmd.AddParameter(m_ui.nCompany);	
		pCmd.AddParameter(m_cmbSearch.GetCurSel());	

		if(!pRs.Execute(&pCmd)) return;	
		j++;
		
		char buffer[10];
		long nCount = pMileageRecord->GetItemCount();
		pMileageRecord->GetItem(MODIFY_MILEAGE)->SetCaption(ltoa(nBalance, buffer,10));		
	}
	if (j > 0)
	{
		CString sMsg = "";
		sMsg.Format("%d건을 수정하였습니다.",j);
		MessageBox(sMsg,"확인", MB_ICONINFORMATION);	
		m_lstLeft.Populate();
	}
	else
	{
		MessageBox("수정한내역이 없습니다.","확인", MB_ICONINFORMATION);	
	}	
};

void CReportForm19::OnBnClickedBalanceInitButton()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	int nRow = m_lstLeft.GetSelectedRows()->GetCount();
	if(nRow == 0)
		return;

	CString sCount = "";
	sCount.Format("%d건을 초기화 하시겠습니까?", nRow);

	if(MessageBox(sCount, "초기화", MB_YESNO | MB_ICONINFORMATION) == IDYES)
    	MultiSelectBalance(1);
}

void CReportForm19::OnBnClickedBalanceModifyButton()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	if(m_lstLeft.GetSelectedRows()->GetCount() == 0)
		return;
	MultiSelectBalance(0);
}

void CReportForm19::OnCbnSelchangeOptionCombo()
{
	if(m_cmbOption.GetCurSel() == 0)
	{
		m_edtMileageModify.EnableWindow(TRUE);
		GetDlgItem(IDC_MILEAGE_MODIFY_BTN)->EnableWindow(TRUE);
	}
	else
	{
		m_edtMileageModify.EnableWindow(FALSE);
		GetDlgItem(IDC_MILEAGE_MODIFY_BTN)->EnableWindow(FALSE);
	}
}

void CReportForm19::OnCbnSelchangeSearchCombo()
{
	if(m_cmbSearch.GetCurSel() == 0)
	{
		GetDlgItem(IDC_SEARCH_EDIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BALANCE_FROM_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_TO_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_STATIC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_SEARCH_BTN)->ShowWindow(FALSE);

	}
	else if(m_cmbSearch.GetCurSel() == 1)
	{
		GetDlgItem(IDC_SEARCH_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_FROM_EDIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BALANCE_TO_EDIT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BALANCE_STATIC)->ShowWindow(TRUE);
		GetDlgItem(IDC_BALANCE_SEARCH_BTN)->ShowWindow(TRUE);
	}
	else if(m_cmbSearch.GetCurSel() == 2)
	{
		GetDlgItem(IDC_SEARCH_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_FROM_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_TO_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_STATIC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_SEARCH_BTN)->ShowWindow(FALSE);
		SearchTypeCustomer(FALSE);
	}
	else if(m_cmbSearch.GetCurSel() == 3)
	{
		GetDlgItem(IDC_SEARCH_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_FROM_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_TO_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_STATIC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_SEARCH_BTN)->ShowWindow(FALSE);
		SearchTypeCustomer(TRUE);
	}
	else if(m_cmbSearch.GetCurSel() == 4)
	{
		GetDlgItem(IDC_SEARCH_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_FROM_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_TO_EDIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_STATIC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BALANCE_SEARCH_BTN)->ShowWindow(FALSE);
		SearchTypeCustomer(TRUE);
	}
}

void CReportForm19::SearchTypeCustomer(BOOL bType)
{
	if(!CheckData())
		return;

	m_lstLeft.GetRecords()->RemoveAll();
// 전체검색;잔액유검색;마일미적용;예외마일;
//고객명/전화번호;잔액검색;전체검색;잔액유검색;마일미적용;예외마일;
//     0             1        2         3         4          5

	int nType = 0;
	if(m_cmbSearch.GetCurSel() == 5)
		nType = 5;
	else if(m_cmbSearch.GetCurSel() == 4)
		nType = 4;
	else if(m_cmbSearch.GetCurSel() == 3)
		nType = 3;
	else if(m_cmbSearch.GetCurSel() == 2)
		nType = 2;

	if(nType== 0) return;
	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_type_customer3");	
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);	
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(nType);	
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;	
	CString strDate, strCompany, strTel1, strTel2, strPostNo, strAddr, strMileageType;
	long nItem = 0, nNo = 0, nCol = 1, nCNo =0,nUseCount=0 ,nMileageType = 0,
		nMileageBalance =0, nOutPut = 0, nTotalMailage = 0,  nGNo = 0, nAdvertCount = 0;
	BOOL bNoSMS = FALSE;
	COleDateTime dtLastSentAdvertSMS;

	pPar->GetValue(nOutPut);
	if(nOutPut == 100)
	{
		MessageBox("전체 검색은 오후 6시이후부터 작업이 됩니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sTel2", strTel2);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nMileageType", nMileageType);

		if(nMileageType == 0 && m_cmbSearch.GetCurSel() == 4)
			strMileageType = "%적용";
		else if(nMileageType == 1 && m_cmbSearch.GetCurSel() == 4)
			strMileageType = "금액(원)";
		else if(nMileageType == 10 && m_cmbSearch.GetCurSel() == 4)
			strMileageType = "적용안함";
		
		m_lstLeft.AddRecord(new CMileageRecord(strCompany, LF->GetDashPhoneNumber(strTel1), LF->GetDashPhoneNumber(strTel2), nGNo, nType, nUseCount,nMileageBalance, nCNo, strMileageType));
		
		nTotalMailage += nMileageBalance;

		nCol =1;
		pRs.MoveNext();
	}
	pRs.Close();

	if(nItem > 0)
		m_lstLeft.AddRecord(new CMileageRecord("", "", "합계",0, -1, 0, nTotalMailage, 0, ""));

	m_lstLeft.Populate();
}

void CReportForm19::OnBnClickedDirectModifyButton()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	int j = 0;
	long nBalance = 0;
	CXTPGridColumn *pCol = NULL;
	for(int row = 0; row < m_lstLeft.GetRecords()->GetCount(); row++)
	{
		CMileageRecord *pMileageRecord = (CMileageRecord *)m_lstLeft.GetRecords()->GetAt(row);
		if(pMileageRecord->m_bDirtyFlag)
		{			
			CString sBalance = "";
			sBalance = pMileageRecord->GetItem(MODIFY_MILEAGE)->GetCaption(pCol);			
			nBalance = atol(sBalance);
			
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_mileage_apply_balance");	
			pCmd.AddParameter(pMileageRecord->m_nCNo);			
			pCmd.AddParameter(nBalance);		
			pCmd.AddParameter(m_ui.strName);		
			pCmd.AddParameter(m_ui.nCompany);		
			pCmd.AddParameter(m_cmbSearch.GetCurSel());		

			if(!pRs.Execute(&pCmd)) return;	
			j++;

			pMileageRecord->m_bDirtyFlag = FALSE;

			char buffer[10];
			long nCount = pMileageRecord->GetItemCount();
			pMileageRecord->GetItem(MODIFY_MILEAGE)->SetCaption(ltoa(nBalance, buffer,10));
		}		
	}
	if( j > 0)
	{
		CString strMsg = "";
		strMsg.Format("%d건을 수정하였습니다.",j);
		MessageBox(strMsg,"확인", MB_ICONINFORMATION);	
		m_lstLeft.Populate();
	}
	else
		MessageBox("수정할 내역이 없습니다.","확인", MB_ICONINFORMATION);	
}

void CReportForm19::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstLeft, pt);
}




void CReportForm19::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcLeft, rcData;
	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu;	
	m_lstLeft.GetWindowRect(&rcLeft);
	m_lstData.GetWindowRect(&rcData);

	if(rcLeft.PtInRect(point))
	{
		pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
	else if(rcData.PtInRect(point))
	{
		pRMenu=rMenu.GetSubMenu(10);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
	
	
}




void CReportForm19::OnlstDataItemRClick(NMHDR * pNotifyStruct, LRESULT *)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstData, pt);
	//OnlstDataContextMenu(&m_lstData, pt);


}


void CReportForm19::OnViewExcel()
{
	if(!LF->POWER_CHECK(2010, "엑셀변환", TRUE))
		return;

	CoInitialize(NULL);

	long rows = m_lstLeft.GetRecords()->GetCount() + 1;
	long cols = m_lstLeft.GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = {rows, cols};
	sa.Create(VT_VARIANT, 2, elements);

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			long index[] = {r, c};
			VARIANT v;
			VariantInit(&v);
			CString str;

			if(r == 0)
			{
				CXTPGridColumn *pCol = m_lstLeft.GetColumns()->GetVisibleAt(c);
				str = pCol->GetCaption();
				v.vt = VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);
			}
			else
			{
				CMileageRecord *pMileageRecord = (CMileageRecord *)m_lstLeft.GetRecords()->GetAt(r-1);
				str = pMileageRecord->m_strData[c];
				
				if(str.GetLength() > 0 && str.Left(1) == "=")
					str.Remove('=');

				v.vt= VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);

			}
			VariantClear(&v);
		}
	}
	
	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 320, rows);  

	CMyExcel::ToExcel(sa, cols, rows);
} 

void CReportForm19::OnViewExcel2()
{
	if(!LF->POWER_CHECK(2010, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 320, m_lstData.GetItemCount());  
	CMyExcel::ToExcel(&m_lstData);	
}

void CReportForm19::OnBnClickedMialeageSmsBtn()
{
	if(LF->GetCurBranchInfo()->bIntegrated) 
	{
		MessageBox("통합에서는 고객구분이 안되어 통합해서 보내실수없습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstLeft.GetRecords()->GetCount() == 0)
		return;
	
	CXTPGridRecords *pRecords=NULL;
	if(m_lstLeft.GetSelectedRows()->GetCount() > 1)
	{
		for(int i = 0; i < m_lstLeft.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_lstLeft.GetSelectedRows()->GetAt(i);
			pRecords->Add(pRow->GetRecord());
		}
	}
}
