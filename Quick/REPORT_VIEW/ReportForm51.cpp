// ReportForm51.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm51.h"
#include "RcpView.h"
#include "AddGroupDlg.h"
#include "SearchGroupDlg.h"
#include "MakeGroupReportNewDlg.h"
#include "AfterReportDlg.h"
#include "UnBillDlg.h"
// CReportForm51

IMPLEMENT_DYNCREATE(CReportForm51, CMyFormView)

CReportForm51::CReportForm51()
	: CMyFormView(CReportForm51::IDD)
{
	m_bDragMode = FALSE;
	m_sSelectGNo = "";
	m_nCalculateCount  = 0;
	m_nCalculateSum = 0;
	m_nCalculateTrans = 0;

}

CReportForm51::~CReportForm51()
{
	//m_lstOrder.SaveReportOrder("CReportForm51", "m_lstOrder");

}

void CReportForm51::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CREDIT_CHECK, m_chkCredit);
	
}

BEGIN_MESSAGE_MAP(CReportForm51, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, OnBnClickedRefreshBtn2)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_ORDER_REPORT, OnOrderReportItemDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_REPORT, OnGroupReportItemDbClick)
	
	
	ON_NOTIFY(LVN_BEGINDRAG, IDC_ORDER_REPORT, OnReportBeginDrag)
	ON_NOTIFY(NM_CLICK, IDC_ORDER_REPORT, OnOrderReportClick)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_REPORT, OnGroupReportClick)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(ID_SEARCH_ORDER_EDIT, OnEnChangeSearchOrderEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_NOTIFY(NM_RCLICK, IDC_ORDER_REPORT, OnReportItemRClick)

	ON_COMMAND(ID_MAKE_GROUP_REPORT, OnMakeGroupReport)
	
	//ON_COMMAND(ID_AFTER_REPORT, OnAfterReport)
	//ON_COMMAND(ID_UNBILL, OnUnBill)
	/*ON_COMMAND(ID_ORDER_SEE, OnOrderSee)
	ON_COMMAND(ID_ETC, OnEtc)
	ON_COMMAND(ID_DELETE_GROUP_REPORT, OnDeleteGroupReport)
	ON_COMMAND(ID_RE_GROUP_REPORT, OnReGroupReport)
	ON_COMMAND(ID_INCOME, OnIncome)
	ON_COMMAND(ID_TAXACCOUNT, OnTaxAccount)*/

	
	ON_BN_CLICKED(IDC_DEPT_WEB_VIEW_BTN, &CReportForm51::OnBnClickedDeptWebViewBtn)
	ON_BN_CLICKED(IDC_MAIN_WEB_VIEW_BTN, &CReportForm51::OnBnClickedMainWebViewBtn)
END_MESSAGE_MAP()



#ifdef _DEBUG
void CReportForm51::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm51::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm51 메시지 처리기입니다.

void CReportForm51::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm51::OnInitialUpdate()
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

	m_chkCredit.SetCheck(TRUE);
	
	m_lstOrder.SetExtendedStyle(0);

	m_lstOrder.InsertColumn(nCol++,  "오더번호", DT_CENTER, 80);
	m_lstOrder.InsertColumn(nCol++, "날짜", DT_LEFT, 100);
	m_lstOrder.InsertColumn(nCol++, "회사명", DT_LEFT, 110);
	m_lstOrder.InsertColumn(nCol++, "담당자", DT_LEFT, 70);
	m_lstOrder.InsertColumn(nCol++, "WebID", DT_LEFT, 70);
	m_lstOrder.InsertColumn(nCol++, "출발지", DT_LEFT, 120);
	m_lstOrder.InsertColumn(nCol++, "도착지", DT_LEFT, 100);
	m_lstOrder.InsertColumn(nCol++, "상태", DT_CENTER, 45);
	m_lstOrder.InsertColumn(nCol++, "지불", DT_CENTER, 45);
	m_lstOrder.InsertColumn(nCol++, "기본", DT_RIGHT, 70);
	m_lstOrder.InsertColumn(nCol++, "추가", DT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "할인", DT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "합계", DT_RIGHT, 70);
	m_lstOrder.InsertColumn(nCol++, "탁송", DT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "물품", DT_LEFT, 70);
	m_lstOrder.InsertColumn(nCol++, "비고", DT_LEFT, 250);
	m_lstOrder.InsertColumn(nCol++, "", DT_LEFT, 0);
	m_lstOrder.InsertColumn(nCol++, "", DT_LEFT, 0);
	//m_lstOrder.InitControl();

	

	m_lstOrder.Populate();

	//m_lstOrder.LoadReportOrder("CReportForm51", "m_lstOrder");

}

void CReportForm51::RefreshList()
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

void CReportForm51::OnBnClickedRefreshBtn2()
{
	RefreshOrderList();
}

void CReportForm51::RefreshOrderList()
{ 
	m_lstOrder.DeleteAllItems();
	m_lstOrder.Populate();


	if( m_sSelectGNo.GetLength() <= 0)
	{
		MessageBox("왼쪽그룹을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_order3");
	pCmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(::GetCurBranchInfo()->bIntegrated);	
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);	
	pCmd.AddParameter(m_sSelectGNo);
	pCmd.AddParameter(m_chkCredit.GetCheck());
	if(!pRs.Execute(&pCmd)) return;

	long nTNo, nOCNo, nOGNo, nGNo, nState, nPayType, nCNo,nCol,nRNo;			  
	long nChargeBasic = 0, nChargeAdd = 0, nChargeDis = 0, nChargeSum = 0,nChargeTrans = 0;
	long nChargeSumBasic = 0,nChargeSumAdd = 0,nChargeSumDis = 0, nChargeTotalSum = 0, 
		nChargeSumTrans = 0,nTotalCount = 1, nCompany = 0;
	CString strOName, strSDong, strDDong, strOManager, strLoginID,strItemType, strEtc;
	COleDateTime dt1;
	char buffer[20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{ 
		nCol = 0;

        pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nOCNo", nOCNo);		
		pRs.GetFieldValue("sOName", strOName); 
		pRs.GetFieldValue("sOManager", strOManager); 
		pRs.GetFieldValue("dt1", dt1);		
		pRs.GetFieldValue("nOGNo", nOGNo); 		
		pRs.GetFieldValue("sOName", strOName);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);		
		pRs.GetFieldValue("sItemType", strItemType);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sLoginID", strLoginID);
		pRs.GetFieldValue("nCompany", nCompany);

		
		m_lstOrder.MyAddItem(itoa(nTNo, buffer, 10));
		m_lstOrder.MyAddItem( dt1.Format("%Y-%m-%d %H:%M"));
		m_lstOrder.MyAddItem( strOName);
		m_lstOrder.MyAddItem( strOManager);
		m_lstOrder.MyAddItem( strLoginID);
		m_lstOrder.MyAddItem( strSDong);
		m_lstOrder.MyAddItem( strDDong);
		m_lstOrder.MyAddItem( ::GetStateString(nState));
		m_lstOrder.MyAddItem( ::GetPayTypeFromLong(nPayType));
		m_lstOrder.MyAddItem( ::GetMyNumberFormat(nChargeBasic));
		m_lstOrder.MyAddItem( ::GetMyNumberFormat(nChargeAdd));
		m_lstOrder.MyAddItem( ::GetMyNumberFormat(nChargeDis));
		m_lstOrder.MyAddItem( ::GetMyNumberFormat(nChargeSum));
		m_lstOrder.MyAddItem( ::GetMyNumberFormat(nChargeTrans));
		m_lstOrder.MyAddItem( strItemType);
		m_lstOrder.MyAddItem( strEtc);		
		m_lstOrder.MyAddItem( ltoa(nCompany, buffer,10));		
		m_lstOrder.MyAddItem( ltoa(nGNo, buffer,10));		
		/*m_lstOrder.SetItemLong(i, nCNo);		
		m_lstOrder.SetItemLong2(i, nTNo);		
		m_lstOrder.SetItemLong3(i, nState);		
		m_lstOrder.SetItemString(i, strOName);		*/
		m_lstOrder.InsertItemDataLong(nCNo);
		m_lstOrder.InsertItemDataLong2(nTNo);
		m_lstOrder.InsertItemDataLong3(nState);


		m_lstOrder.InsertItemDataString(strOName);
		m_lstOrder.InsertItemData(nPayType);
		m_lstOrder.EndItem();


		//m_lstOrder.SetItemData(i, nPayType);

		nChargeSumBasic		+= nChargeBasic;
		nChargeSumAdd		+= nChargeAdd;
		nChargeSumDis		+= nChargeDis;
		nChargeTotalSum		+= nChargeSum;
		nChargeSumTrans		+= nChargeTrans;
		nTotalCount++;
 
		pRs.MoveNext();
	}
	m_nCalculateCount = nTotalCount - 1;
	m_nCalculateSum = nChargeTotalSum;
	m_nCalculateTrans = nChargeSumTrans;

	for(int i =0;  i < 8; i ++)
		m_lstOrder.MyAddItem("");
	m_lstOrder.MyAddItem(7, GetMyNumberFormat(nTotalCount -1) + "건", "", 0, FALSE, DT_LEFT);
	m_lstOrder.MyAddItem(8, GetMyNumberFormat(nChargeSumBasic), "", 0, FALSE, DT_LEFT);
	m_lstOrder.MyAddItem(9, GetMyNumberFormat(nChargeSumAdd), "", 0, FALSE, DT_LEFT);
	m_lstOrder.MyAddItem(10, GetMyNumberFormat(nChargeSumDis), "", 0, FALSE, DT_LEFT);
	m_lstOrder.MyAddItem(11, GetMyNumberFormat(nChargeTotalSum), "", 0, FALSE, DT_LEFT);
	m_lstOrder.MyAddItem(12, GetMyNumberFormat(nChargeSumTrans), "", 0, FALSE, DT_LEFT);	
	m_lstOrder.MyAddItem(13, GetMyNumberFormat(nChargeTotalSum + nChargeSumTrans), "", 0, FALSE, DT_LEFT);	
	m_lstOrder.EndItem();
	m_lstOrder.Populate();		
}

void CReportForm51::OnEnChangeSearchEdit()
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
			
void CReportForm51::OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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
void CReportForm51::OnGroupReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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



void CReportForm51::OnOrderReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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


	long nTNo = m_lstOrder.GetItemDataLong2(pItemNotify->pRow->GetIndex());
	//long nState = m_lstOrder.GetItemLong3(pRecord);
	long nState = m_lstOrder.GetItemDataLong2(pItemNotify->pRow->GetIndex());
	//CString strCName = m_lstOrder.GetItemString(pRecord);
	CString strCName = m_lstOrder.GetItemDataRecordString(pItemNotify->pRow->GetIndex());
	CString strCompany = m_lstOrder.GetItemText(pRow->GetIndex(),17 );
	long nCompany = 0;
	if(IsNumeric(strCompany))
		nCompany = atol(strCompany);
	
	if(nCompany <= 0)
		return;

	if(nTNo < 100000) return;

	

	
	CBranchInfo *pBranchInfo =GetBranchInfo(nCompany);
	if(pBranchInfo)
	{
		if(!LU->GetRcpView() )
		{
			MessageBox(
				"접수페이지로 이동후에 다시 클릭하시기 바랍니다.", 
				"확인", MB_ICONINFORMATION);
			return;
		}
	}

	
	if(!POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	LU->GetRcpView()->CreateRcpDlg(pBranchInfo, 
		strCName,
		nTNo, 
		nState, "", FALSE, -1, 0, 0, FALSE, "");
}


CString CReportForm51::GetGNoList()
{

	
	CString sTempData = "";
	if(m_lstGroup.GetSelectedCount() <= 0 ) return "";

	CString sSelectGNoList = "";
	m_mapGNoList.clear();
		
	CXTPGridRow *pRow;
	long nGNo ;
	for(int i = 0; i < m_lstGroup.GetSelectedCount(); i++ )
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



void CReportForm51::ChildInput(CGroupRecord* pOriginalRecord)
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



void CReportForm51::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CReportForm51::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyFormView::OnMouseMove(nFlags, point);
}

void CReportForm51::OnLButtonUp(UINT nFlags, CPoint point)
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

		CMyXTPGridRecord *pOrderRecord = (CMyXTPGridRecord *)pOrderRow->GetRecord();
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
			if(::CheckGroupReport("0;", pDestRecord->m_nGNo, dtDate, 1, strNeedReportID) == FALSE) // 재정산이 필요한 리포트를 선정
				return;

			//long nCNo = m_lstOrder.GetItemLong(pOrderRecord);
			long nCNo = pOrderRecord->GetItemDataLong();
			CMkCommand pCmd(m_pMkDb, "move_not_grouporder_to_grouporder");
			pCmd.AddParameter(nCNo);
			pCmd.AddParameter(nDestGNo);

			if(pCmd.Execute())
			{
				if(strNeedReportID != "")
				{
					if(::ReReport(strNeedReportID))
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

void CReportForm51::OnEnChangeSearchOrderEdit()
{
	CString strData; m_edtSearchOrder.GetWindowText(strData);
	m_lstOrder.Filter(strData);
	return;
	/*

	CXTPGridRecords *pRecords = m_lstOrder.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString sOName = pRecord->GetItem(4)->GetCaption(NULL);

		if(sOName.Find(strData) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstOrder.Populate();*/
}

void CReportForm51::OnOrderReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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
BOOL CReportForm51::PreTranslateMessage(MSG* pMsg)
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


void CReportForm51::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstOrder, pt);

}


void CReportForm51::OnViewExcel()
{
	if(!POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 316, m_ui.nWNo, m_lstOrder.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstOrder);
}

void CReportForm51::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstOrder.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_GROUP_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(5);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CReportForm51::OnMakeGroupReport()
{
	UpdateData();

	long nReportGNo = 0;
	CString strGroupName ,strGroupDept,strGNoList = "" ;
	GNO_MAP::iterator it;
	CString strTemp = "",strSearchGroup = "";
	BOOL bIntegrated = FALSE;

	if(m_mapGNoList.size() <= 0)
	{
		MsgBox("정산할 부서를 선택하여 주세요");
		return;
	}	
	else if(m_mapGNoList.size() == 1)
	{
		CString sGNo = "";
		sGNo = m_sSelectGNo; sGNo.Replace(",","");
		if(IsNumeric(sGNo))
			nReportGNo = atol(sGNo);
		strGNoList = sGNo;
	}
	else if(m_mapGNoList.size() > 1)
	{
		MsgBox("대표로 정산할 부서를 검색하여 다시 선택하여 주세요");

		if(m_mapGNoList.size() > 0 )
		{
			it = m_mapGNoList.begin();
			if(it->first > 0)
				strSearchGroup = m_cg.GetGroupData(it->first)->strGroupName;
		}

		CSearchGroupDlg dlg;
		dlg.m_nCompany = GetCurBranchInfo()->nCompanyCode;
		dlg.m_nDataType = SG_GROUP;
		dlg.m_strSearch = strSearchGroup.GetLength() > 0 ? strSearchGroup : "";
		dlg.m_nAutoSearch = TRUE;
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


	g_bana_log->Print("%d-%d ~ %d-%d",m_dtFrom.GetMonth(), m_dtFrom.GetDay(),m_dtTo.GetMonth(),m_dtTo.GetDay());


	LU->OpenGroupReportDlg(this, 0, nReportGNo,TRUE, m_dtFrom, m_dtTo,
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


void CReportForm51::OnBnClickedDeptWebViewBtn()
{

	if(m_lstOrder.GetSelectedCount() <= 0 )
		return;


	CMyXTPGridRecord *pRecord = NULL;
	pRecord = m_lstOrder.GetSelectedRecord();	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL)
		str += " co.logisoft.co.kr";
	else
	{

		COleDateTime dtFrom,dtTo;
		CString  strPostInfo,strID = "", strPWD = "", strFrom = "", strTo = "", strOGNo = "", strGNoList = "";		
		long nCompany = 0, nGNo = 0;

		CXTPGridColumn *pCol;
		/*for(int i = 0; i <= m_lstOrder.GetColumns()->GetCount(); i++)
		{
		pCol = m_lstOrder.GetColumns()->GetAt(i);
		pCol->GetCaption().Compare(")
		}*/
		pCol = m_lstOrder.GetColumns()->GetAt(17);

		CXTPGridRecordItem *pItem = pRecord->GetItem(17);
		if(pItem)
			strOGNo = pRecord->GetItem(17)->GetCaption(pCol);
		else
			return;

		if(!IsNumeric(strOGNo)) return;

		nGNo = atol(strOGNo);

		strFrom.Format("%d-%02d-%02d", m_dtFrom.GetYear(), m_dtFrom.GetMonth(), m_dtFrom.GetDay() );
		strTo.Format("%d-%02d-%02d", m_dtTo.GetYear(), m_dtTo.GetMonth(), m_dtTo.GetDay() );
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		strID = m_cg.GetGroupData(nGNo)->strID;
		strPWD = m_cg.GetGroupData(nGNo)->strPassword;

		if(nGNo == 0)
			return;		


		if(strID.GetLength() <= 0 || strPWD.GetLength() <= 0)
		{
			MessageBox("법인/고객관리 에서 웹아이디및 패스워드를 생성하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		strForm.Format( LU->GetCorpDomain() + "/hidelogin_q.asp?txtID=%s&txtPwd=%s&nCompany=%d&sWID=%s&sWPWD=%s&nSessionKey=%d&nWCompany=%d&nViewType=10&sIP=%s&dtFrom=%s&dtTo=%s",
			strID, strPWD,nCompany,m_ui.strID, m_ui.strPW,m_ui.nSiteSessionKey,m_ui.nCompany,m_ei.strExternalIP,strFrom, strTo);
		//id_name=%s&sPWD=%s&strWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&sCorpID=%s&sCorpPwd=%s&sCorpNodeID=%d",			
		//m_ui.strID, m_ui.strPW,m_ui.strName, m_ci.GetCompanyCode(), m_ci.GetRcpIntMode1() ? "1" : "0", 
		//m_ui.nSiteSessionKey, m_ei.strExternalIP, strID, strPass, nCorporationID);
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

void CReportForm51::OnBnClickedMainWebViewBtn()
{

	if(m_lstOrder.GetSelectedCount() <= 0 )
		return;


	CMyXTPGridRecord *pRecord = NULL;
	pRecord = m_lstOrder.GetSelectedRecord();	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())
	if(pRecord == NULL)
		str += " co.logisoft.co.kr";
	else
	{

		COleDateTime dtFrom,dtTo;
		CString  strPostInfo,strID = "", strPWD = "", strFrom = "", strTo = "", strOGNo = "", strGNoList = "";		
		long nCompany = 0, nGNo = 0;

		CXTPGridColumn *pCol;
		/*for(int i = 0; i <= m_lstOrder.GetColumns()->GetCount(); i++)
		{
		pCol = m_lstOrder.GetColumns()->GetAt(i);
		pCol->GetCaption().Compare(")
		}*/
		pCol = m_lstOrder.GetColumns()->GetAt(17);

		CXTPGridRecordItem *pItem = pRecord->GetItem(17);
		if(pItem)
			strOGNo = pRecord->GetItem(17)->GetCaption(pCol);
		else
			return;

		if(!IsNumeric(strOGNo)) return;

		nGNo = atol(strOGNo);

		strFrom.Format("%d-%02d-%02d", m_dtFrom.GetYear(), m_dtFrom.GetMonth(), m_dtFrom.GetDay() );
		strTo.Format("%d-%02d-%02d", m_dtTo.GetYear(), m_dtTo.GetMonth(), m_dtTo.GetDay() );
		nCompany = m_cg.GetGroupData(nGNo)->nCompany;
		strID = m_cg.GetGroupData(nGNo)->strID;
		strPWD = m_cg.GetGroupData(nGNo)->strPassword;

		if(nGNo == 0)
			return;

		m_cg.GetTopLevelID_PWD(nGNo,strID, strPWD);

		strGNoList = m_cg.GetAllGNoListFromChildGNo(nGNo);



		if(strID.GetLength() <= 0 || strPWD.GetLength() <= 0)
		{
			MessageBox("법인/고객관리 에서 웹아이디및 패스워드를 생성하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		strForm.Format(LU->GetCorpDomain() + "/hidelogin_q.asp?txtID=%s&txtPwd=%s&nCompany=%d&sWID=%s&sWPWD=%s&nSessionKey=%d&nWCompany=%d&nViewType=10&sIP=%s&dtFrom=%s&dtTo=%s",
			strID, strPWD,nCompany,m_ui.strID, m_ui.strPW,m_ui.nSiteSessionKey,m_ui.nCompany,m_ei.strExternalIP,strFrom, strTo);
		//id_name=%s&sPWD=%s&strWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&sCorpID=%s&sCorpPwd=%s&sCorpNodeID=%d",			
		//m_ui.strID, m_ui.strPW,m_ui.strName, m_ci.GetCompanyCode(), m_ci.GetRcpIntMode1() ? "1" : "0", 
		//m_ui.nSiteSessionKey, m_ei.strExternalIP, strID, strPass, nCorporationID);
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
