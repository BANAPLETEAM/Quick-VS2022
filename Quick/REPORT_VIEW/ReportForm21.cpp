// ReportForm21.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm21.h"
#include "RcpView.h"
#include "AddGroupDlg.h"
#include "SearchGroupDlg.h"
#include "MakeGroupReportNewDlg.h"
#include "AfterReportDlg.h"
#include "UnBillDlg.h"
// CReportForm21

IMPLEMENT_DYNCREATE(CReportForm21, CMyFormView)

CReportForm21::CReportForm21()
	: CMyFormView(CReportForm21::IDD)
{
	m_bDragMode = FALSE;
	m_sSelectGNo = "";
	m_nCalculateCount  = 0;
	m_nCalculateSum = 0;
	m_nCalculateTrans = 0;

}

CReportForm21::~CReportForm21()
{
	m_lstOrder.SaveReportOrder("CReportForm21", "m_lstOrder");

}

void CReportForm21::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, ID_SEARCH_ORDER_EDIT, m_edtSearchOrder);
	DDX_Control(pDX, IDC_CREDIT_CHECK, m_chkCredit);
	
}

BEGIN_MESSAGE_MAP(CReportForm21, CMyFormView)
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

END_MESSAGE_MAP()


// CReportForm21 진단입니다.

//
//void CReportForm21::OnAfterReport()
//{
//	CXTPGridSelectedRows *pRows = m_lstOrder.GetSelectedRows();
//
//	if(pRows == NULL) return;
//	long nGNo = 0; CString strGNo;
//
//	CXTPGridRecord*pRecord = pRows->GetAt(0)->GetRecord();
//
//	strGNo = m_lstOrder.GetItemText(pRecord, 12);
//	if(!LF->IsNumeric(strGNo))
//	{
//		LF->MsgBox("선택을 다시하여주세요");
//		return;
//	}
//	nGNo = atol(strGNo);
//	
//	CAfterReportDlg dlg;
//	dlg.m_bAll = pRecord->m_bSumRecord; // 합계뿌린곳
//
//
//	if(dlg.m_bAll)
//	{
//		dlg.m_nGNo = m_cg.GetGroupData(nGNo)->nLevel == 0 ? 
//			nGNo : m_cg.GetGroupData(nGNo)->nParentGNo;
//	}
//	else
//		dlg.m_nGNo = nGNo;
//
//	dlg.DoModal();
//
//}
//
//
//void CReportForm21::OnUnBill()
//{
//	long nTopGNo = 0;
//	CXTPGridSelectedRows *pRows = m_lstOrder.GetSelectedRows();
//
//	if(pRows == NULL) return;
//	if(pRows->GetCount() == 0) return;
//
//	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();
//
//	long nGNo = 0; CString strGNo;
//
//	CXTPGridRecord*pRecord = pRows->GetAt(0)->GetRecord();
//
//	strGNo = m_lstOrder.GetItemText(pRecord, 12);
//	if(!LF->IsNumeric(strGNo))
//	{
//		LF->MsgBox("선택을 다시하여주세요");
//		return;
//	}
//	nGNo = atol(strGNo);
//
//
//
//	CUnBillDlg dlg;
//	dlg.m_bAll = pRecord->m_bSumRecord; // 합계뿌린곳
//
//	if(dlg.m_bAll)
//	{
//		dlg.m_nGNo = m_cg.GetGroupData(nGNo)->nLevel == 0 ? 
//			pRecord->m_nGNo : m_cg.GetGroupData(nGNo)->nParentGNo;
//
//		nTopGNo = dlg.m_nGNo;
//	}
//	else
//	{
//		dlg.m_nGNo = pRecord->m_nGNo;
//		nTopGNo = m_cg.GetGroupData(nGNo)->nLevel == 0 ? 
//			nGNo : m_cg.GetGroupData(nGNo)->nParentGNo;
//	}
//
//	if(dlg.DoModal() == IDOK)
//	{
//		if(dlg.m_bChangeItem)
//		{
//			CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());
//
//			CString sGNo = "";
//			sGNo.Format("%d;", dlg.m_nGNo);
//			pReport->SetData(sGNo);
//		}
//	}
//}

#ifdef _DEBUG
void CReportForm21::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm21::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm21 메시지 처리기입니다.

void CReportForm21::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm21::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	int nCol = 0;

	SetResize(IDC_GROUP_REPORT, sizingBottom);
	SetResize(IDC_ORDER_REPORT, sizingRightBottom);

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuWeek();
	m_cmbType.SetCurSel(0);

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


	m_lstOrder.InsertColumn(nCol, "현재의뢰자그룹", LVCFMT_LEFT, 100);
	m_lstOrder.InsertColumn(nCol++, "오더그룹", LVCFMT_LEFT, 100);
	m_lstOrder.InsertColumn(nCol++, "오더번호", LVCFMT_CENTER, 60);
	m_lstOrder.InsertColumn(nCol++, "날짜", LVCFMT_LEFT, 80);
	m_lstOrder.InsertColumn(nCol++, "회사명", LVCFMT_LEFT, 60);
	m_lstOrder.InsertColumn(nCol++, "담당자", LVCFMT_LEFT, 60);
	m_lstOrder.InsertColumn(nCol++, "WebID", LVCFMT_LEFT, 60);
	m_lstOrder.InsertColumn(nCol++, "출발지", LVCFMT_LEFT, 80);
	m_lstOrder.InsertColumn(nCol++, "도착지", LVCFMT_LEFT, 80);
	m_lstOrder.InsertColumn(nCol++, "상태", LVCFMT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "지불", LVCFMT_CENTER, 50);
	m_lstOrder.InsertColumn(nCol++, "기본", LVCFMT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "추가", LVCFMT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "할인", LVCFMT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "합계", LVCFMT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "탁송", LVCFMT_RIGHT, 50);
	m_lstOrder.InsertColumn(nCol++, "물품", LVCFMT_LEFT, 60);
	m_lstOrder.InsertColumn(nCol++, "비고", LVCFMT_LEFT, 250);
	m_lstOrder.InsertColumn(nCol++, "", LVCFMT_LEFT, 0);
	m_lstOrder.InsertColumn(nCol++, "", LVCFMT_LEFT, 0);
	

	m_lstOrder.Populate();

	m_lstOrder.LoadReportOrder("CReportForm21", "m_lstOrder");

}

void CReportForm21::RefreshList()
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

void CReportForm21::OnBnClickedRefreshBtn2()
{
	RefreshOrderList();
}

void CReportForm21::RefreshOrderList()
{ 
	m_lstOrder.DeleteAllItems();
	m_lstOrder.Populate();


	if(m_cmbType.GetCurSel() == 2 && m_sSelectGNo.GetLength() <= 0)
	{
		MessageBox("왼쪽그룹을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	UpdateData(TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_not_group_order3");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_cmbType.GetCurSel());
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
	int i = 0;
	for(i = 0; i<pRs.GetRecordCount(); i++)
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


		m_lstOrder.InsertItem(i, nCNo == 0 ? "고객삭제됨" : m_cg.GetGroupData(nGNo)->strFullName);
		m_lstOrder.SetItemText(i, nCol++, m_cg.GetGroupData(nOGNo)->strFullName );
		m_lstOrder.SetItemText(i, nCol++, itoa(nTNo, buffer, 10));
		m_lstOrder.SetItemText(i, nCol++, dt1.Format("%Y-%m-%d %H:%M"));
		m_lstOrder.SetItemText(i, nCol++, strOName);
		m_lstOrder.SetItemText(i, nCol++, strOManager);
		m_lstOrder.SetItemText(i, nCol++, strLoginID);
		m_lstOrder.SetItemText(i, nCol++, strSDong);
		m_lstOrder.SetItemText(i, nCol++, strDDong);
		m_lstOrder.SetItemText(i, nCol++, LF->GetStateString(nState));
		m_lstOrder.SetItemText(i, nCol++, LF->GetPayTypeFromLong(nPayType));
		m_lstOrder.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeBasic));
		m_lstOrder.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeAdd));
		m_lstOrder.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeDis));
		m_lstOrder.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeSum));
		m_lstOrder.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeTrans));
		m_lstOrder.SetItemText(i, nCol++, strItemType);
		m_lstOrder.SetItemText(i, nCol++, strEtc);		
		m_lstOrder.SetItemText(i, nCol++, ltoa(nCompany, buffer,10));		
		m_lstOrder.SetItemText(i, nCol++, ltoa(nGNo, buffer,10));		
		m_lstOrder.SetItemLong(i, nCNo);		
		m_lstOrder.SetItemLong2(i, nTNo);		
		m_lstOrder.SetItemLong3(i, nState);		
		m_lstOrder.SetItemString(i, strOName);		

		m_lstOrder.SetItemData(i, nPayType);

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

	m_lstOrder.InsertItem(i, "");
	m_lstOrder.SetItemText(i, 9, LF->GetMyNumberFormat(nTotalCount -1) + "건");
	m_lstOrder.SetItemText(i, 10, LF->GetMyNumberFormat(nChargeSumBasic));
	m_lstOrder.SetItemText(i, 11, LF->GetMyNumberFormat(nChargeSumAdd));
	m_lstOrder.SetItemText(i, 12, LF->GetMyNumberFormat(nChargeSumDis));
	m_lstOrder.SetItemText(i, 13, LF->GetMyNumberFormat(nChargeTotalSum));
	m_lstOrder.SetItemText(i, 14, LF->GetMyNumberFormat(nChargeSumTrans));	


	m_lstOrder.Populate();		
}

void CReportForm21::OnEnChangeSearchEdit()
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
			
void CReportForm21::OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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
void CReportForm21::OnGroupReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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



void CReportForm21::OnOrderReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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


	long nTNo = m_lstOrder.GetItemLong2(pRecord);
	long nState = m_lstOrder.GetItemLong3(pRecord);
	CString strCName = m_lstOrder.GetItemString(pRecord);
	CString strCompany = m_lstOrder.GetItemText(pRow->GetIndex(),17 );
	long nCompany = 0;
	if(LF->IsNumeric(strCompany))
		nCompany = atol(strCompany);
	
	if(nCompany <= 0)
		return;

	if(nTNo < 100000) return;

	

	
	CBranchInfo *pBranchInfo = LF->GetBranchInfo(nCompany);
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

	
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	LU->GetRcpView()->CreateRcpDlg(pBranchInfo, 
		strCName,
		nTNo, 
		nState, "", FALSE, -1, 0, 0, FALSE, "");
}


CString CReportForm21::GetGNoList()
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
		}
	}
	return sSelectGNoList;
		

}


void CReportForm21::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CReportForm21::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyFormView::OnMouseMove(nFlags, point);
}

void CReportForm21::OnLButtonUp(UINT nFlags, CPoint point)
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

		CXTPGridRecord *pOrderRecord = pOrderRow->GetRecord();
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

void CReportForm21::OnEnChangeSearchOrderEdit()
{
	CString strData; m_edtSearchOrder.GetWindowText(strData);

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

	m_lstOrder.Populate();
}

void CReportForm21::OnOrderReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstOrder.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	long nIndex = pRow->GetIndex();

	CString strData = m_lstOrder.GetItemText(nIndex, 0);

	if(strData == "고객삭제됨")
		return;

	if(strData.Find("/") > 0)
		strData = strData.Left(strData.Find("/") );

	if(strData != "") 
		m_edtSearch.SetWindowText(strData);

}
BOOL CReportForm21::PreTranslateMessage(MSG* pMsg)
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


void CReportForm21::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstOrder, pt);

}


void CReportForm21::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 316, m_ui.nWNo, m_lstOrder.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstOrder);
}

void CReportForm21::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstOrder.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_GROUP_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(5);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CReportForm21::OnMakeGroupReport()
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

	CMakeGroupReportNewDlg dlg;
	dlg.m_nGNo = nReportGNo;
	dlg.m_dtFrom = m_dtFrom;
	dlg.m_dtTo = m_dtTo;
	dlg.m_strGNoList = strGNoList;
	dlg.m_nCalculateCount = m_nCalculateCount;
	dlg.m_nCalculateSum = m_nCalculateSum;
	dlg.m_nCalculateTrans = m_nCalculateTrans;

	dlg.DoModal();
}
