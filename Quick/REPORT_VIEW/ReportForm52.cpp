// ReportForm52.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm52.h"
#include "RcpView.h"
#include "AddGroupDlg.h"
#include "SearchGroupDlg.h"
#include "MakeGroupReportNewDlg.h"
#include "AfterReportDlg.h"
#include "UnBillDlg.h"
#include "GroupIncomeDlg.h"
#include "DeleteGroupReportDlg.h"
#include "KingoHttp.h"
// CReportForm52

IMPLEMENT_DYNCREATE(CReportForm52, CMyFormView)

CReportForm52::CReportForm52()
	: CMyFormView(CReportForm52::IDD)
{
	m_bDragMode = FALSE;
	m_sSelectGNo = "";
	m_nCalculateCount  = 0;
	m_nCalculateSum = 0;
	m_nCalculateTrans = 0;

}

CReportForm52::~CReportForm52()
{
	//m_lstOrder.SaveReportOrder("CReportForm52", "m_lstOrder");

}

void CReportForm52::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_REPORT, m_lstGroup);
	DDX_Control(pDX, IDC_ORDER_REPORT, m_lstOrder);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);	
	DDX_Control(pDX, ID_SEARCH_ORDER_EDIT, m_edtSearchOrder);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSearhType);
	DDX_Control(pDX, IDC_LOGI_TEST1_BTN, m_btnLogiTest1);
	DDX_Control(pDX, IDC_LOGI_TEST2_BTN, m_btnLogiTest2);
	
}

BEGIN_MESSAGE_MAP(CReportForm52, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, OnBnClickedRefreshBtn2)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_ORDER_REPORT, OnOrderReportItemDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_REPORT, OnGroupReportItemDbClick)
	ON_NOTIFY(NM_CLICK, IDC_ORDER_REPORT, OnOrderReportClick)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_REPORT, OnGroupReportClick)
	
	ON_NOTIFY(LVN_BEGINDRAG, IDC_ORDER_REPORT, OnReportBeginDrag)
	ON_BN_CLICKED(IDC_BILL_PAGE_BTN, OnBnClickedBillPage)
	ON_BN_CLICKED(IDC_BILL_EXCEL_BTN, OnBnClickedBillExcel)
	ON_BN_CLICKED(IDC_BILL_TAX_BTN, OnBnClickedBill)
	
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(ID_SEARCH_ORDER_EDIT, OnEnChangeSearchOrderEdit)
	ON_WM_CONTEXTMENU()	
	ON_NOTIFY(NM_RCLICK, IDC_ORDER_REPORT, OnReportItemRClick)

	ON_COMMAND(ID_MAKE_GROUP_REPORT, OnMakeGroupReport)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_PAY_INCOME, OnPayIncome)
	ON_COMMAND(ID_PAY_END, OnPayEnd)
	ON_COMMAND(ID_PAY_CANCEL, OnPayCancel)
	ON_COMMAND(ID_REPORT_DELETE, OnReportDelete)
	ON_COMMAND(ID_PAY_VIEW, OnPayView)

	
	
	ON_BN_CLICKED(IDC_WEB_VIEW_BTN, &CReportForm52::OnBnClickedWebViewBtn)
	ON_BN_CLICKED(IDC_WEB_TAX_VIEW_BTN, &CReportForm52::OnBnClickedWebTaxViewBtn)
	ON_BN_CLICKED(IDC_LOGI_TEST1_BTN, &CReportForm52::OnBnClickedLogiTest1Btn)
	ON_BN_CLICKED(IDC_LOGI_TEST2_BTN, &CReportForm52::OnBnClickedLogiTest2Btn)
END_MESSAGE_MAP()



#ifdef _DEBUG
void CReportForm52::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm52::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm52 메시지 처리기입니다.

void CReportForm52::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm52::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	int nCol = 0;

	SetResize(IDC_GROUP_REPORT, sizingBottom);
	SetResize(IDC_ORDER_REPORT, sizingRightBottom);

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuWeek();


	CXTPGridColumn* pCol0 = m_lstGroup.AddColumn(new CXTPGridColumn(0, "그룹이름", 120));
	CXTPGridColumn *pCol1 = m_lstGroup.AddColumn(new CXTPGridColumn(1, "부서명", 90, FALSE));
	CXTPGridColumn *pCol2 = m_lstGroup.AddColumn(new CXTPGridColumn(2, "정산일", 60, FALSE));

	m_lstGroup.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstGroup.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstGroup.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstGroup.GetReportHeader()->AllowColumnReorder(FALSE);
	m_lstGroup.AllowEdit(FALSE);
	m_lstGroup.SetGridColor(RGB(222, 222, 222));
	m_lstGroup.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_lstGroup.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);

	pCol0->SetTreeColumn(1);
	m_lstGroup.SetTreeIndent(10);
	m_lstGroup.Populate();		
	m_lstOrder.SetExtendedStyle(0);
	m_cmbSearhType.SetCurSel(0);

	m_lstOrder.InsertColumn(nCol++, "No", DT_CENTER, 30);
	m_lstOrder.InsertColumn(nCol++, "발급No", DT_LEFT, 50);
	m_lstOrder.InsertColumn(nCol++, "본/지", DT_LEFT, 110);
	m_lstOrder.InsertColumn(nCol++, "생성일", DT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "정산일자", DT_LEFT, 110);
	m_lstOrder.InsertColumn(nCol++, "상태", DT_CENTER, 65);
	m_lstOrder.InsertColumn(nCol++, "할인", DT_RIGHT, 40);
	m_lstOrder.InsertColumn(nCol++, "건수", DT_RIGHT, 40);
	m_lstOrder.InsertColumn(nCol++, "신용금액", DT_RIGHT, 70);
	m_lstOrder.InsertColumn(nCol++, "할인액", DT_RIGHT, 55);
	m_lstOrder.InsertColumn(nCol++, "탁송료", DT_RIGHT, 55);
	m_lstOrder.InsertColumn(nCol++, "공급가", DT_RIGHT, 70);
	m_lstOrder.InsertColumn(nCol++, "세액", DT_RIGHT, 55);
	m_lstOrder.InsertColumn(nCol++, "총합계", DT_RIGHT, 80);
	m_lstOrder.InsertColumn(nCol++, "발행일", DT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "수금일", DT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "수금액", DT_RIGHT, 60);
	m_lstOrder.InsertColumn(nCol++, "미수금", DT_RIGHT, 60);
	m_lstOrder.InsertColumn(nCol++, "경과", DT_RIGHT, 40);
	m_lstOrder.InsertColumn(nCol++, "입금일", DT_CENTER, 55);
	
	m_lstOrder.InsertColumn(nCol++, "SMS발송", DT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "Email발송", DT_CENTER, 55);
	m_lstOrder.InsertColumn(nCol++, "Email읽음", DT_CENTER, 55);
	m_lstOrder.InsertColumn(nCol++, "전자세금", DT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "작업자", DT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "비고", DT_LEFT, 350);

	m_lstOrder.SetFreezeColumnsCount(6);
	

	m_lstOrder.Populate();

	if( m_ui.strLogiStaffName == "엄태주" || 
		m_ui.strLogiStaffName == "유준욱" || 
		m_ui.strLogiStaffName == "김형석")
	{
		m_btnLogiTest1.ShowWindow(SW_SHOW);
		m_btnLogiTest2.ShowWindow(SW_SHOW);
	}

	//m_lstOrder.LoadReportOrder("CReportForm52", "m_lstOrder");

}

void CReportForm52::RefreshList()
{
	CMyFormView::RefreshList();

	long nSel = 0;

	if(m_lstGroup.GetSelectedRows()->GetCount() != 0)
		nSel = m_lstGroup.GetSelectedRows()->GetAt(0)->GetIndex();

	m_lstGroup.GetRecords()->RemoveAll();

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pGroup = m_cg.GetRefreshGroup();

	long nPreLevel = 0;

	for(it = pGroup->begin(); it != pGroup->end(); it++)
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		switch(st->nLevel)
		{
		case 0:
			pReocrdTop = m_lstGroup.AddRecord(new CGroupRecord(st));
			pReocrdTop->SetExpanded(TRUE);
			break;
		case 1:
			pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CGroupRecord(st));
			((CGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel1->SetExpanded(TRUE);
			break;
		case 2:
			pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CGroupRecord(st));
			((CGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel2->SetExpanded(TRUE);
			break;
		case 3:
			pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CGroupRecord(st));
			((CGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel3->SetExpanded(TRUE);
			break;
		case 4:
			pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CGroupRecord(st));
			((CGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel4->SetExpanded(TRUE);
			break;
		case 5:
			pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CGroupRecord(st));
			((CGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel5->SetExpanded(TRUE);
			break;
		}
	}

	m_lstGroup.Populate();

	CXTPGridRows *pRows = m_lstGroup.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nSel, m_lstGroup.GetRows()->GetCount() -1));

	m_lstGroup.GetSelectedRows()->Select(pRow);
}

void CReportForm52::OnBnClickedRefreshBtn2()
{
	RefreshOrderList();
}

void CReportForm52::RefreshOrderList()
{ 
	m_lstOrder.DeleteAllItems();
	m_lstOrder.Populate();


	if( m_sSelectGNo.GetLength() <= 0 && m_cmbSearhType.GetCurSel() == 1)
	{
		MessageBox("왼쪽그룹을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report_list");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);	
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);	
	pCmd.AddParameter(m_sSelectGNo);
	pCmd.AddParameter(m_cmbSearhType.GetCurSel());
	if(!pRs.Execute(&pCmd)) return;

	long nID, nGNo, nCreditCount, nCreditCharge, nDiscountCharge, nBillTotalCharge,
			nCreditTax, nUnCollection, nCompany, nCol,nReportState, 
			nTransCharge, nDiscount = 0;
	CString strGroupName, strDept, strWName,  strEtc,strIntegrated, strDiscount, strGNoList;
	
	COleDateTime dtReportStart, dtReportEnd, dtCreate, dtSendSMS, dtSendBill, dtSendEmail,dtPayMent,dtInputDebit,dtBillCollection;
	BOOL bPressBill; 	char buffer[10]; COleDateTimeSpan dtPaySpan;
	long nTotalCreditCount = 0, nTotalCreditCharge= 0,nTotalDiscountCharge= 0,
		nTotalTransCharge= 0,nTotalBillTotalCharge= 0, nTotalCreditTax= 0, nTotalUnCollection= 0,
		nReceivableAmount = 0, nBillCollection = 0, nTotalBillCollection =0, nTotalReceivableAmount = 0;
	COleDateTime dtEmailRead,dtNow(COleDateTime::GetCurrentTime());

	int i = 0;
	for(i = 0; i < pRs.GetRecordCount(); i++)
	{ 

		CString strDTPayMent = "", strDTCreate = "", strSendSMS = "", strSendBill = "", strPayDay = "", 
			strSendEmail = "",strDTInputDebit = "",strDTBillCollection = "", strReadEmail = "";
		nCol = 0;

        pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);		
		pRs.GetFieldValue("sGroupName", strGroupName); 
		pRs.GetFieldValue("sDept", strDept); 
		pRs.GetFieldValue("dtReportStart", dtReportStart);		
		pRs.GetFieldValue("dtReportEnd", dtReportEnd); 		
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("dtCreate", dtCreate);
		pRs.GetFieldValue("sWName", strWName);
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
		pRs.GetFieldValue("dtSendBill", dtSendBill);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sGNoList", strGNoList);
		pRs.GetFieldValue("dtPayMent", dtPayMent);
		pRs.GetFieldValue("nBillCollection", nBillCollection);
		pRs.GetFieldValue("nReceivableAmount", nReceivableAmount);
		pRs.GetFieldValue("nDiscount", nDiscount);		
		pRs.GetFieldValue("dtInputDebit", dtInputDebit);
		pRs.GetFieldValue("dtBillCollection", dtBillCollection);
		pRs.GetFieldValue("dtEmailRead", dtEmailRead);

		if(m_cg.GetGroupData(nGNo)->nParentGNo == 0)
			strIntegrated.Format("%s%s%s", "본]", m_cg.GetGroupData(nGNo)->strGroupName, 
						m_cg.GetGroupData(nGNo)->strDept );
		else
			strIntegrated.Format("%s%s%s",  "지] ",  m_cg.GetGroupData(nGNo)->strGroupName , 
						m_cg.GetGroupData(nGNo)->strDept);

		strDiscount.Format("%d%%", nDiscount);

		if(dtPayMent.GetStatus() == COleDateTime::valid)
		{
			strDTPayMent.Format("%02d-%02d", dtPayMent.GetMonth(), dtPayMent.GetDay());
			dtPaySpan = dtPayMent - dtNow;
			if(nReceivableAmount > 0)
				strPayDay.Format("%s" , dtPaySpan.GetDays() >= 0 ? "" :  LF->GetMyNumberFormat(dtPaySpan.GetDays()) + "일" );
		}
		if(dtCreate.GetStatus() == COleDateTime::valid) 
			strDTCreate.Format("%02d-%02d", dtCreate.GetMonth(), dtCreate.GetDay()) ;
		if(dtSendSMS.GetStatus() == COleDateTime::valid)
			strSendSMS.Format("%02d-%02d", dtSendSMS.GetMonth(), dtSendSMS.GetDay()) ; 
		if(dtSendBill.GetStatus() == COleDateTime::valid)
			strSendBill.Format("%02d-%02d", dtSendBill.GetMonth(), dtSendBill.GetDay()) ;
		if(dtSendEmail.GetStatus() == COleDateTime::valid)
			strSendEmail.Format("%02d-%02d", dtSendEmail.GetMonth(), dtSendEmail.GetDay()) ;
		if(dtInputDebit.GetStatus() == COleDateTime::valid)
			strDTInputDebit.Format("%02d-%02d", dtInputDebit.GetMonth(), dtInputDebit.GetDay()) ;
		if(IsTimeValid(dtBillCollection) )
			strDTBillCollection.Format("%02d-%02d", dtBillCollection.GetMonth(), dtBillCollection.GetDay()) ;
		if(IsTimeValid(dtEmailRead) )
			strReadEmail.Format("%02d-%02d", dtEmailRead.GetMonth(), dtEmailRead.GetDay()) ;
		

		m_lstOrder.InsertItem(i, itoa(i + 1, buffer, 10));
		m_lstOrder.SetItemText(i, 1, LF->GetStringFromLong(nID));
		m_lstOrder.SetItemText(i, 2, strIntegrated);
		m_lstOrder.SetItemText(i, 3, strDTCreate);
		m_lstOrder.SetItemText(i, 4, dtReportStart.Format("%y-%m-%d") + " ~ " + dtReportEnd.Format("%y-%m-%d"));
		m_lstOrder.SetItemText(i, 5, LF->GetReportState(nReportState));
		m_lstOrder.SetItemText(i, 6, strDiscount);
		m_lstOrder.SetItemText(i, 7, LF->GetMyNumberFormat(nCreditCount));
		m_lstOrder.SetItemText(i, 8, LF->GetMyNumberFormat(nCreditCharge));
		m_lstOrder.SetItemText(i, 9, LF->GetMyNumberFormat(nDiscountCharge));
		m_lstOrder.SetItemText(i, 10, LF->GetMyNumberFormat(nTransCharge));
		m_lstOrder.SetItemText(i, 11, LF->GetMyNumberFormat(nBillTotalCharge));
		m_lstOrder.SetItemText(i, 12, LF->GetMyNumberFormat(nCreditTax));
		m_lstOrder.SetItemText(i, 13, LF->GetMyNumberFormat(nUnCollection));
		m_lstOrder.SetItemText(i, 14, strDTBillCollection);
		m_lstOrder.SetItemText(i, 15, strDTPayMent);
		m_lstOrder.SetItemText(i, 16, LF->GetMyNumberFormat(nBillCollection));
		m_lstOrder.SetItemText(i, 17, LF->GetMyNumberFormat(nReceivableAmount));
		m_lstOrder.SetItemText(i, 18, strPayDay);
		m_lstOrder.SetItemText(i, 19, strDTInputDebit);
		m_lstOrder.SetItemText(i, 20, strSendSMS);
		m_lstOrder.SetItemText(i, 21, strSendEmail);
		m_lstOrder.SetItemText(i, 22, strReadEmail);
		m_lstOrder.SetItemText(i, 23, strSendBill);
		m_lstOrder.SetItemText(i, 24, strWName);
		m_lstOrder.SetItemText(i, 25, strEtc);
		m_lstOrder.SetItemLong(i, nID);
		m_lstOrder.SetItemLong2(i, nGNo);
		m_lstOrder.SetItemLong3(i, nReceivableAmount);
		m_lstOrder.SetItemData(i, (long)nUnCollection);
		m_lstOrder.SetItemDate(i, dtReportStart);
		m_lstOrder.SetItemDate2(i, dtReportEnd);
		m_lstOrder.SetItemDataText(i, strGNoList);
		m_lstOrder.SetItemDataText2(i, strEtc);


		nTotalCreditCount		+= nCreditCount;
		nTotalCreditCharge		+= nCreditCharge;
		nTotalDiscountCharge	+= nDiscountCharge;
		nTotalTransCharge		+= nTransCharge;
		nTotalBillTotalCharge	+= nBillTotalCharge;
		nTotalCreditTax			+= nCreditTax;
		nTotalUnCollection		+= nUnCollection;				

		nTotalBillCollection	+= nBillCollection;
		nTotalReceivableAmount	+= nReceivableAmount;
 
		pRs.MoveNext();
	}
	
	if(pRs.GetRecordCount() > 0)
	{
		m_lstOrder.InsertItem(i, "");
		for (int j = 1; j < 8; j++)
			m_lstOrder.SetItemText(i, j, "");

		m_lstOrder.SetItemText(i, 7, LF->GetMyNumberFormat(i) + "건");
		m_lstOrder.SetItemText(i, 8, LF->GetMyNumberFormat(nTotalCreditCharge));
		m_lstOrder.SetItemText(i, 9, LF->GetMyNumberFormat(nTotalDiscountCharge));
		m_lstOrder.SetItemText(i, 10, LF->GetMyNumberFormat(nTotalTransCharge));
		m_lstOrder.SetItemText(i, 11, LF->GetMyNumberFormat(nTotalBillTotalCharge));
		m_lstOrder.SetItemText(i, 12, LF->GetMyNumberFormat(nTotalCreditTax));
		m_lstOrder.SetItemText(i, 13, LF->GetMyNumberFormat(nTotalUnCollection));
		m_lstOrder.SetItemText(i, 14, "");
		m_lstOrder.SetItemText(i, 15, "");
		m_lstOrder.SetItemText(i, 16, LF->GetMyNumberFormat(nTotalBillCollection));
		m_lstOrder.SetItemText(i, 17, LF->GetMyNumberFormat(nTotalReceivableAmount));
		m_lstOrder.Populate();
	}
	pRs.Close();
}

BOOL CReportForm52::IsTimeValid(COleDateTime dt)
{

	if(dt.GetStatus() == COleDateTime::valid && dt.GetStatus() != COleDateTime::null)
		return TRUE;
	return FALSE;

}

void CReportForm52::OnEnChangeSearchEdit()
{
	CString sText;
	m_edtSearch.GetWindowText(sText);
	
	
	CXTPGridRecords *pRecords = m_lstGroup.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CGroupRecord* pRecord = (CGroupRecord*)pRecords->GetAt(i);

		if(pRecord->m_strSearchData.Find(sText) >=0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstGroup.Populate();
	m_lstGroup.ExpandAll();
	
}
			
void CReportForm52::OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CGroupRecord *pRecord = (CGroupRecord*)pRow->GetRecord();

	CAddGroupDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.m_bAdd = FALSE;

	if(dlg.DoModal())
	{
		RefreshList();
		OnEnChangeSearchEdit();
	}
}

void CReportForm52::ChildInput(CGroupRecord* pOriginalRecord)
{

	long nCount = pOriginalRecord->GetChilds()->GetCount();
	for(int i = 0; i < nCount; i++)
	{
		CGroupRecord* pChildRecord = (CGroupRecord*)pOriginalRecord->GetChilds()->GetAt(i);		

		if(pChildRecord)
		{
			long nGNo = pChildRecord->m_nGNo;
			m_mapGNoList.insert(GNO_MAP::value_type(nGNo, m_cg.GetGroupData(nGNo)->nParentGNo == 0 ? 1 :0));
		}
		if(pChildRecord->GetChilds()->GetCount() > 0)
			ChildInput(pChildRecord);

	}

}



void CReportForm52::OnOrderReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lstOrder.GetSelectedRows();

	if(pRows == NULL){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pRows->GetCount() == 0){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};

	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);
	if(pRow == NULL) return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	

	long nReportGNo = m_lstOrder.GetItemLong(pItemNotify->pRow->GetIndex());	
	long nGNo = m_lstOrder.GetItemLong2(pItemNotify->pRow->GetIndex());
	CString strGNoList = "";
	strGNoList.Format("%d", nGNo);

	if(nGNo <= 0)
		return;
	

	LU->OpenGroupReportDlg(this,nReportGNo, nGNo,FALSE, m_dtFrom, m_dtTo,
		strGNoList,m_nCalculateCount, m_nCalculateSum,m_nCalculateTrans);


}



CString CReportForm52::GetGNoList()
{


	CString sTempData = "";
	if(m_lstGroup.GetSelectedRows()->GetCount() <= 0 ) return "";

	CString sSelectGNoList = "";
	m_mapGNoList.clear();

	CXTPGridRow *pRow;
	long nGNo ;
	for(int i = 0; i < m_lstGroup.GetSelectedRows()->GetCount(); i++ )
	{
		pRow = m_lstGroup.GetSelectedRows()->GetAt(i);
		if(pRow)
		{
			CGroupRecord *pRecord = (CGroupRecord*)pRow->GetRecord();
			nGNo = pRecord->m_nGNo;
			sTempData.Format("%ld,",nGNo );
			sSelectGNoList += sTempData;
			m_mapGNoList.insert(GNO_MAP::value_type(pRecord->m_nGNo, m_cg.GetGroupData(nGNo)->nParentGNo == 0 ? 1 :0));
			ChildInput(pRecord);

		}

	}
	return sSelectGNoList;


}



void CReportForm52::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CReportForm52::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyFormView::OnMouseMove(nFlags, point);
}

void CReportForm52::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		::ReleaseCapture();
		m_bDragMode  = FALSE;  //순서에 주의 할것

		CRect rect;
		m_lstGroup.GetWindowRect(&rect);
		ScreenToClient(rect);

		point -= rect.TopLeft();

		CXTPGridRow *pOrderRow = m_lstOrder.GetSelectedRows()->GetAt(0);

		if(pOrderRow == NULL)
			return;

		CXTPGridRecord *pOrderRecord = (CXTPGridRecord *)pOrderRow->GetRecord();
		CString strOName = pOrderRecord->GetItem(4)->GetCaption(NULL);

		CXTPGridRow * pGroupRow = m_lstGroup.HitTest(point);
		
		if(pGroupRow == NULL) return;

		CGroupRecord *pDestRecord = (CGroupRecord*)pGroupRow->GetRecord();

		long nDestGNo = pDestRecord->m_nGNo;

		CString strMsg = ""; 
		strMsg.Format("해당오더의 고객[%s]의\r\n그룹오더로 등록되지 않은 모든오더를\r\n[%s]그룹오더로\r\n 편입시킵니다.\r\n\r\n[%s]고객은 자동으로\r\n[%s]그룹으로 등록됩니다"
			, strOName, m_cg.GetGroupData(nDestGNo)->strFullName, strOName, m_cg.GetGroupData(nDestGNo)->strFullName);

		long nResult = MessageBox(strMsg, "확인", MB_ICONQUESTION | MB_YESNO);

		if(nResult == IDNO)
			return;

		COleDateTime dtDate(2000, 1, 1, 0, 0, 0);
		CString strNeedReportID = "";

		if(nResult == IDYES)
		{
			if(LF->CheckGroupReport("0;", pDestRecord->m_nGNo, dtDate, 1, strNeedReportID) == FALSE) // 재정산이 필요한 리포트를 선정
				return;

			//long nCNo = m_lstOrder.GetItemLong(pOrderRecord);
			long nCNo = m_lstOrder.GetItemLong(pOrderRecord);
			CMkCommand pCmd(m_pMkDb, "move_not_grouporder_to_grouporder");
			pCmd.AddParameter(nCNo);
			pCmd.AddParameter(nDestGNo);

			if(pCmd.Execute())
			{
				if(strNeedReportID != "")
				{
					if(LF->ReReport(strNeedReportID))
					{
						MessageBox("완료되었습니다.", "확인", MB_ICONINFORMATION);
						RefreshOrderList();
					}
				}
				else
				{
					MessageBox("완료되었습니다.", "확인", MB_ICONINFORMATION);	
					RefreshOrderList();
				}
			}			
		}
	}

	CMyFormView::OnLButtonUp(nFlags, point);
}

void CReportForm52::OnEnChangeSearchOrderEdit()
{
	CString strData; m_edtSearchOrder.GetWindowText(strData);

	m_lstOrder.Filter(strData);
	
}

void CReportForm52::OnOrderReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	/*CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	long nIndex = pRow->GetIndex();

	CString strData = m_lstOrder.GetItemText(nIndex, 0);

	if(strData == "고객삭제됨")
		return;

	if(strData.Find("/") > 0)
		strData = strData.Left(strData.Find("/") );

	if(strData != "") 
		m_edtSearch.SetWindowText(strData);*/

}
void CReportForm52::OnGroupReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	m_sSelectGNo = "";
	m_sSelectGNo = GetGNoList();	


	if(m_sSelectGNo.GetLength() <= 0)
	{
		MessageBox("그룹번호의 속성값이 0입니다", "확인", MB_ICONINFORMATION);
		return;
	}

}

BOOL CReportForm52::PreTranslateMessage(MSG* pMsg)
{
	
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->hwnd == m_lstGroup.GetSafeHwnd())
		{
			if(GetKeyState(VK_SHIFT) & 0x8000 || GetKeyState(VK_CONTROL) & 0x8000)
			{				
				if (pMsg->message == 256)
				{
					// 여기 
					m_sSelectGNo = "";
					m_sSelectGNo = GetGNoList();	
				}
				
			}



		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}


void CReportForm52::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstOrder, pt);

}


void CReportForm52::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 316, m_ui.nWNo, m_lstOrder.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstOrder);
}


void CReportForm52::OnPayIncome()
{
	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);
	if(pRow == NULL) return;

	long nCol = 0;
	CXTPGridColumn *pCol;
	for(int i = 0; i < m_lstOrder.GetColumns()->GetCount(); i++)
	{
		pCol =m_lstOrder.GetColumns()->GetAt(i);
		if(pCol->GetCaption().Compare("상태") == 0)
		{
			nCol = i;
			break;
		}

	}

	CString strState = pRow->GetRecord()->GetItem(nCol)->GetCaption(pCol);
	if(strState.Compare("입금완료") == 0)
	{
		LF->MsgBox("입금완료된 곳은 재입금이 불가능합니다.");
		return;
	}

	IncomeWork(0);	
}

void CReportForm52::OnPayCancel()
{
	IncomeWork(1);
}
void CReportForm52::OnPayEnd()
{
	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);
	if(pRow == NULL) return;

	long nCol = 0;
	CXTPGridColumn *pCol;
	for(int i = 0; i < m_lstOrder.GetColumns()->GetCount(); i++)
	{
		pCol =m_lstOrder.GetColumns()->GetAt(i);
		if(pCol->GetCaption().Compare("상태") == 0)
		{
			nCol = i;
			break;
		}

	}


	CString strState = pRow->GetRecord()->GetItem(nCol)->GetCaption(pCol);
	if(strState.Compare("입금완료") == 0)
	{
		LF->MsgBox("입금완료된 곳은 재입금이 불가능합니다.");
		return;
	}


	IncomeWork(2);
	
}
void CReportForm52::OnReportDelete()
{
	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);
	if(pRow == NULL) return;

	if( MessageBox("정말로 정산삭제를 하시겠습니까? \n\r\n\r정산삭제가 되면 해당 입금된 내역도 삭제됩니다.\n\r(입금내역 백업요망)",
		"확인", MB_YESNO) == IDNO) 
		return;


	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();

	long nBillID = m_lstOrder.GetItemLong(pRecord);
	long nGNo = m_lstOrder.GetItemLong2(pRecord);


	CDeleteGroupReportDlg dlg;
	dlg.m_nGNo = nGNo;
	dlg.m_nApplyReportID = nBillID;
	dlg.DoModal();
	if(dlg.m_bRefresh == TRUE)
	{
		RefreshOrderList();
	}
	


}

void CReportForm52::IncomeWork(int nType)
{
	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);

	if(pRow == NULL) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();

	long nBillID = m_lstOrder.GetItemLong(pRecord);
	long nGNo = m_lstOrder.GetItemLong2(pRecord);
	long nReceivableAmount = m_lstOrder.GetItemLong3(pRecord);
	long nUnCollection = (long)m_lstOrder.GetItemData(pRecord);
	CString strEtc = m_lstOrder.GetItemDataText2(pRecord);
	COleDateTime dtStartReport, dtEndReport;
	dtStartReport = m_lstOrder.GetItemDate(pRecord);
	dtEndReport = m_lstOrder.GetItemDate2(pRecord);

	if(nBillID <= 0 || nGNo <= 0 )
	{
		LF->MsgBox("정산할 그룹이나 정산리포트가 없습니다 로지소프트로 문의하세요");
		return;
	}

	CString strReportDate = "";
	//strReportDate.Format("",dtStartReport.Get dtEndReport)
	strReportDate.Format("%s ~ %s", dtStartReport.Format("%m-%d"), dtEndReport.Format("%m-%d"));
	CGroupIncomeDlg dlg;
	dlg.m_nID = nBillID;
	dlg.m_nDebit = nReceivableAmount;
	dlg.m_sDate = strReportDate;
	dlg.m_nUnCollection = nUnCollection;
	dlg.m_nAllIncome = nType;
	dlg.m_strInputEtc = strEtc;
	if(dlg.DoModal() == IDOK)
	{
		RefreshOrderList();
	}
}


void CReportForm52::OnPayView()
{

	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();

	long nBillID = m_lstOrder.GetItemLong(pRecord);
	long nGNo = m_lstOrder.GetItemLong2(pRecord);

	if(nBillID <= 0 || nGNo <= 0 )
	{
		LF->MsgBox("정산할 그룹이나 정산리포트가 없습니다 로지소프트로 문의하세요");
		return;
	}

	CUnBillDlg dlg;
	dlg.m_bAlone = TRUE;
	dlg.m_nID = nBillID;
	dlg.m_nGNo = nGNo;

	dlg.DoModal();
}






void CReportForm52::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstOrder.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_GROUP_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(6);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CReportForm52::OnMakeGroupReport()
{
	long nReportGNo = 0;
	CString strGroupName ,strGroupDept,strGNoList = "" ;
	GNO_MAP::iterator it;
	CString strTemp = "",strSearchGroup = "";
	BOOL bIntegrated = FALSE;

	if(m_mapGNoList.size() <= 0)
	{
		LF->MsgBox("정산할 부서를 선택하여 주세요");
		return;
	}	
	else if(m_mapGNoList.size() == 1)
	{
		CString sGNo = "";
		sGNo = m_sSelectGNo; sGNo.Replace(",","");
		if(LF->IsNumeric(sGNo))
			nReportGNo = atol(sGNo);
		strGNoList = sGNo;
	}
	else if(m_mapGNoList.size() > 1)
	{
		LF->MsgBox("대표로 정산할 부서를 검색하여 다시 선택하여 주세요");

		if(m_mapGNoList.size() > 0 )
		{
			it = m_mapGNoList.begin();
			if(it->first > 0)
				strSearchGroup = m_cg.GetGroupData(it->first)->strGroupName;
		}

		CSearchGroupDlg dlg;
		dlg.m_nCompany = LF->GetCurBranchInfo()->nCompanyCode;
		dlg.m_nDataType = SG_GROUP;
		dlg.m_strSearch = strSearchGroup.GetLength() > 0 ? strSearchGroup : "";
		if(dlg.DoModal() != IDOK) return;
		
		nReportGNo = dlg.m_nGNo;	
		
		
		for(it = m_mapGNoList.begin(); it != m_mapGNoList.end(); ++it)
		{		
			strTemp.Format("%d,", it->first);
			strGNoList += strTemp;
			
		}

	}

	strGroupName = m_cg.GetGroupData(nReportGNo)->strGroupName;
	strGroupDept = m_cg.GetGroupData(nReportGNo)->strDept;
	bIntegrated = m_cg.GetGroupData(nReportGNo)->nParentGNo == 0 ? TRUE : FALSE;

	strTemp.Format("%s%s 정산을 %s의 셋팅한 적용데이터로 생성 하시겠습니까?" ,
		strGroupName, strGroupDept.GetLength() > 0 ? "[" + strGroupDept + "]" : "",
		bIntegrated ? "본사" : "지사");

	if(MessageBox(strTemp, "확인", MB_YESNO) == IDNO) return;
	LU->OpenGroupReportDlg(this,0, nReportGNo,FALSE, m_dtFrom, m_dtTo,
		strGNoList,m_nCalculateCount, m_nCalculateSum,m_nCalculateTrans);
/*
	CMakeGroupReportNewDlg dlg;
	dlg.m_nGNo = nReportGNo;
	dlg.m_dtFrom = m_dtFrom;
	dlg.m_dtTo = m_dtTo;
	dlg.m_strGNoList = strGNoList;
	dlg.m_nCalculateCount = m_nCalculateCount;
	dlg.m_nCalculateSum = m_nCalculateSum;
	dlg.m_nCalculateTrans = m_nCalculateTrans;

	dlg.DoModal();
	*/
/*
	if(dlg.m_bRefresh == TRUE)
	{
		CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());

		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		pReport->SetData(sGNo);
	}*/

}

void CReportForm52::OnBnClickedWebViewBtn()
{
	
	if( m_lstOrder.GetSelectedRows()->GetCount() <= 0 )
	{
		LF->MsgBox("정산을 생성한 리스트를 선택하여주세요");
		return;
	}
	CString strGNoList = "";
	long nReportNo = 0, nGNo = 0;
	COleDateTime dtFrom, dtTo;
	CXTPGridRecord *pRecord = m_lstOrder.GetFirstSelectedRecord();
	if(pRecord)
	{
		nReportNo = m_lstOrder.GetItemLong(pRecord);
		nGNo = m_lstOrder.GetItemLong2(pRecord);
		dtFrom = m_lstOrder.GetItemDate(pRecord);
		dtTo = m_lstOrder.GetItemDate2(pRecord);
		strGNoList = m_lstOrder.GetItemDataText(pRecord);
		if(nReportNo <= 0 || nGNo <= 0)
		{
			LF->MsgBox("리포트의 생성시 그룹이 정해져 있지 않거나 리포트 번호가 없습니다.");
			return;
		}

		ReportWebView(nReportNo, nGNo, dtFrom, dtTo,strGNoList);

	}


}

void CReportForm52::OnBnClickedBillPage()
{

	if(m_lstOrder.GetSelectedRows()->GetCount() <= 0) return;



	for(int i =0; i < m_lstOrder.GetSelectedRows()->GetCount(); i++)
	{		
		long nGroupReportID, nCompany,  nGNo;
		nGroupReportID = m_lstOrder.GetItemLong(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nGNo = m_lstOrder.GetItemLong2(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		ReportBillPageView(nCompany, nGroupReportID, 1);

	}
}


void CReportForm52::OnBnClickedBillExcel()
{

	if(m_lstOrder.GetSelectedRows()->GetCount() <= 0) return;



	for(int i =0; i < m_lstOrder.GetSelectedRows()->GetCount(); i++)
	{		
		long nGroupReportID, nCompany,  nGNo;
		nGroupReportID = m_lstOrder.GetItemLong(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nGNo = m_lstOrder.GetItemLong2(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		ReportBillPageView(nCompany, nGroupReportID, 2);

	}
}


void CReportForm52::OnBnClickedBill()
{

	if(m_lstOrder.GetSelectedRows()->GetCount() <= 0) return;



	for(int i =0; i < m_lstOrder.GetSelectedRows()->GetCount(); i++)
	{		
		long nGroupReportID, nCompany,  nGNo;
		nGroupReportID = m_lstOrder.GetItemLong(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nGNo = m_lstOrder.GetItemLong2(m_lstOrder.GetSelectedRowsGetAtGetRecord(i));
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		ReportBillPageView(nCompany, nGroupReportID, 0);

	}
}

void CReportForm52::ReportBillPageView(long nCompany, long nGroupReportID, long nType)
{

	CXTPGridRecord *pRecord = NULL;
	pRecord = m_lstOrder.GetFirstSelectedRecord();	

	CString str,strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL) 
		str += LU->GetCorpDomain();
	else
	{	
		//strForm.Format(LU->GetCorpDomain() + "/pop/n_report_stream.asp?nCompany=%d&nWCompany=%d&sWID=%s&nSessionKey=%d&nGroupReportID=%d&nType=%d",
		//	nCompany,m_ui.nCompany, m_ui.strID, m_ui.nSiteSessionKey,nGroupReportID,nType);

		strForm.Format(LU->GetCorpDomain() + "/tax_reference?nCompany=%d&sWID=%s&nSessionKey=%d&nGroupReportID=%d&sIP=%s&nType=%d",
			nCompany, m_ui.strID, m_ui.nSiteSessionKey, nGroupReportID, m_ei.strExternalIP, nType);		
	}	

	str += strForm;
	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) 
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}

}



void CReportForm52::ReportWebView(long nReportNo , long nGNo, COleDateTime dtFrom, COleDateTime dtTo,CString strGNoList)
{

	CXTPGridRecord *pRecord = NULL; 
	pRecord = m_lstOrder.GetFirstSelectedRecord();	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL)
		str += LU->GetCorpDomain();
	else
	{ 

		COleDateTime dtFrom,dtTo;
		CString  strPostInfo,strID = "", strPWD = "", strFrom = "", strTo = "";		
		long nCompany = 0, nElectronicTaxType = 0;

		strFrom.Format("%d-%02d-%02d", dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay() );
		strTo.Format("%d-%02d-%02d", dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay() );
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		strID = m_cg.GetGroupData(nGNo)->strID;
		strPWD = m_cg.GetGroupData(nGNo)->strPassword;
		nElectronicTaxType = m_cg.GetGroupData(nGNo)->nElectronicTaxType;
		
		dtFrom = m_lstOrder.GetItemDate(pRecord);
		dtTo = m_lstOrder.GetItemDate2(pRecord);

		strFrom.Format("%d-%02d-%02d", dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay());
		strTo.Format("%d-%02d-%02d", dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay());
		if(nGNo == 0)
			return;



		if(strID.GetLength() <= 0 || strPWD.GetLength() <= 0)
		{
			MessageBox("법인/고객관리 에서 웹아이디및 패스워드를 생성하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		strForm.Format(LU->GetCorpDomain() + "/?txtID=%s&txtPwd=%s&nCompany=%d&sWID=%s&sWPWD=%s&nSessionKey=%d&sIP=%s&nElectronicTaxType=%d&sToDate=%s&sFromDate=%s",
			strID, strPWD, nCompany,m_ui.strID, m_ui.strPW,m_ui.nSiteSessionKey,m_ei.strExternalIP, nElectronicTaxType, strTo, strFrom);

	}

	str += strForm;
	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) 
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}

}

void CReportForm52::OnBnClickedWebTaxViewBtn()
{

	CXTPGridRecord *pRecord = NULL;
	pRecord = m_lstOrder.GetFirstSelectedRecord();	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL)
		return;
	else
	{
		CString strLicenseID, strLicenseNO, strDomain,strLocation ;
		if(m_ui.nCompany == 7700)
		{			strDomain = "qcall";
			strLicenseID = "qcallsvc";
			strLicenseNO = "d12f93dfce52a39ae6e16932475299f2";
			strLocation = "http://billapi.hiworks.co.kr/auto_login.php";

			//http://qu2.logisoft.co.kr/signin_hiworks?domain={domain}&license_id={license_id}&license_no={license_no}
		}
		else
		{
			/*strID = pBi->
			strLicenseNO = "d12f93dfce52a39ae6e16932475299f2";
			strLocation = "http://billapi.hiworks.co.kr/auto_login.php"*/

		}

			

		if(strLicenseID.GetLength() <= 0 || strLicenseNO.GetLength() <= 0)
		{
			MessageBox("전자세금계산서 업체에 등록한 키를 로지소프트로 발송하여 주시기 바랍니다.",
				"확인", MB_ICONINFORMATION);
			return;
		}

		//http://qu2.logisoft.co.kr/signin_hiworks?domain={domain}&license_id={license_id}&license_no={license_no}
		strForm.Format(LU->GetCorpDomain() + "/signin_hiworks?domain=%s&license_id=%s&license_no=%s",
			strDomain, strLicenseID,strLicenseNO);
			
	}

	str += strForm;
	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) 
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}
}

void CReportForm52::OnBnClickedLogiTest1Btn()
{
	LogiTest(0);
}



void CReportForm52::OnBnClickedLogiTest2Btn()
{
	LogiTest(1);
}


void CReportForm52::LogiTest(int nType)
{
	CString strID ="";
	CString strPass ="";	
	CXTPGridRecord *pRecord = NULL;
	pRecord = m_lstOrder.GetFirstSelectedRecord();	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	CString strTestUrl = "";
	if(nType == 0 ) 
		strTestUrl = " http://106.247.248.10:12380/co/member/sysLogin";
	else
		strTestUrl = " http://106.247.248.10:17000/co/member/sysLogin";


	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL)
	{
		MessageBox("회사를 선택하여주세요", "확인", MB_ICONINFORMATION);
		return;

	}
	else
	{
		COleDateTime dtFrom,dtTo;
		CString  strPostInfo,strID = "", strPWD = "", strFrom = "", strTo = "";		
		long nCompany = 0;	
		CString strGNoList = "";
		long nReportNo = 0, nGNo = 0;
		
		CXTPGridRecord *pRecord = m_lstOrder.GetFirstSelectedRecord();
		if(pRecord)
		{
			nReportNo = m_lstOrder.GetItemLong(pRecord);
			nGNo = m_lstOrder.GetItemLong2(pRecord);
			dtFrom = m_lstOrder.GetItemDate(pRecord);
			dtTo = m_lstOrder.GetItemDate2(pRecord);
			strGNoList = m_lstOrder.GetItemDataText(pRecord);
			if(nReportNo <= 0 || nGNo <= 0)
			{
				LF->MsgBox("리포트의 생성시 그룹이 정해져 있지 않거나 리포트 번호가 없습니다.");
				return;
			}
		}

	

		strFrom.Format("%d-%02d-%02d", dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay() );
		strTo.Format("%d-%02d-%02d", dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay() );
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		strID = m_cg.GetGroupData(nGNo)->strID;
		strPWD = m_cg.GetGroupData(nGNo)->strPassword;

		dtFrom = m_lstOrder.GetItemDate(pRecord);
		dtTo = m_lstOrder.GetItemDate2(pRecord);

		strFrom.Format("%d-%02d-%02d", dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay());
		strTo.Format("%d-%02d-%02d", dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay());
		if(nGNo == 0)
			return;

		if(strID.GetLength() <= 0 || strPWD.GetLength() <= 0)
		{
			MessageBox("법인/고객관리 에서 웹아이디및 패스워드를 생성하세요", "확인", MB_ICONINFORMATION);
			return;
		}
	
	

		strForm.Format(strTestUrl + "?prgType=Q&txtID=%s&txtPwd=%s&nCompany=%d&sWID=%s&sWPWD=%s&nSessionKey=%d&nWCompany=%d&nViewType=10&sIP=%s&dtFrom=%s&dtTo=%s&sGNoList=%s",
			strID, strPWD,nCompany,m_ui.strID, m_ui.strPW,m_ui.nSiteSessionKey,m_ui.nCompany,m_ei.strExternalIP,strFrom, strTo,strGNoList);
		
	}

	str += strForm;


	CKingoHttp http;
	str = http.ansi_utf8((char*)(LPCTSTR)str);


	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) 
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}
	
}
