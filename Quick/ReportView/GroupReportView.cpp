// GroupReportView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GroupReportView.h"

#include "AfterReportDlg.h"
#include "UnBillDlg.h"
#include "OrderSeeDlg.h"
#include "CommonDlg1.h"
#include "CommonDlg2.h"
#include "GroupIncomeDlg.h"
#include "MakeGroupReportDlg.h"
#include "DeleteGroupReportDlg.h"
#include "ReGroupReportDlg.h"
#include "ColumnSelDlg.h"
// CGroupReportView

IMPLEMENT_DYNCREATE(CGroupReportView, CMyFormView)

CGroupReportView::CGroupReportView()
	: CMyFormView(CGroupReportView::IDD)
{
	m_bFirst = TRUE;
	m_nNotIncome = 0;
	m_nIncome = 0;

	m_brush.CreateSolidBrush(RGB(255, 0, 0));
}

CGroupReportView::~CGroupReportView()
{
	DeleteObject(m_brush);
	m_lstReport.SaveReportOrder("CReportForm24", "m_lstReport");
}

void CGroupReportView::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_REPORT_CTRL, m_lstReport);
}

BEGIN_MESSAGE_MAP(CGroupReportView, CMyFormView)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_NOTIFY(NM_RCLICK, IDC_GROUP_REPORT_CTRL, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_REPORT_CTRL, OnReportItemDbClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_AFTER_REPORT, OnAfterReport)
	ON_COMMAND(ID_UNBILL, OnUnBill)
	ON_COMMAND(ID_TAXACCOUNT, OnTaxAccount)
	ON_COMMAND(ID_ETC, OnEtc)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_COMMAND(ID_ORDER_SEE, OnOrderSee)
	ON_COMMAND(ID_DELETE_ALL, OnDeleteAll)
	ON_COMMAND(ID_DELETE_GROUP, OnDeleteGroup)
	ON_COMMAND(ID_INCOME, OnIncome)
	ON_COMMAND(ID_MAKE_GROUP_REPORT, OnMakeGroupReport)
	ON_COMMAND(ID_DELETE_GROUP_REPORT, OnDeleteGroupReport)
	ON_COMMAND(ID_RE_GROUP_REPORT, OnReGroupReport)
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_VISIBLE_COL, OnVisibleCol)
END_MESSAGE_MAP()


// CGroupReportView 진단입니다.

#ifdef _DEBUG
void CGroupReportView::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CGroupReportView::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CGroupReportView 메시지 처리기입니다.

void CGroupReportView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGroupReportView::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	if(m_bFirst == TRUE)
		m_bFirst = FALSE;
	else
		return;

	CXTPGridColumn* pCol0 = m_lstReport.AddColumn(new CXTPGridColumn(0, "그룹이름", 120));
	CXTPGridColumn *pCol1 = m_lstReport.AddColumn(new CXTPGridColumn(1, "부서명", 90, FALSE));
	CXTPGridColumn *pCol2 = m_lstReport.AddColumn(new CXTPGridColumn(2, "담당", 60, FALSE));
	CXTPGridColumn *pCol3 = m_lstReport.AddColumn(new CXTPGridColumn(3, "기간", 90, FALSE));
	CXTPGridColumn *pCol4 = m_lstReport.AddColumn(new CXTPGridColumn(4, "미수금", 75, FALSE));
	CXTPGridColumn *pCol5 = m_lstReport.AddColumn(new CXTPGridColumn(5, "누적미수금", 90, FALSE));
	CXTPGridColumn *pCol6 = m_lstReport.AddColumn(new CXTPGridColumn(6, "수금액", 75, FALSE));
	CXTPGridColumn *pCol7 = m_lstReport.AddColumn(new CXTPGridColumn(7, "수금일자", 60, FALSE));
	CXTPGridColumn *pCol8 = m_lstReport.AddColumn(new CXTPGridColumn(8, "누적수금액", 90, FALSE));
	CXTPGridColumn *pCol9 = m_lstReport.AddColumn(new CXTPGridColumn(9, "계산서발행", 70, FALSE));
	CXTPGridColumn *pCol10 = m_lstReport.AddColumn(new CXTPGridColumn(10, "기타", 200, FALSE));
	CXTPGridColumn *pCol11 = m_lstReport.AddColumn(new CXTPGridColumn(11, "총건수", 45, FALSE));
	CXTPGridColumn *pCol12 = m_lstReport.AddColumn(new CXTPGridColumn(12, "현금", 65, FALSE));
	CXTPGridColumn *pCol13 = m_lstReport.AddColumn(new CXTPGridColumn(13, "신용", 65, FALSE));
	CXTPGridColumn *pCol14 = m_lstReport.AddColumn(new CXTPGridColumn(14, "송금", 65, FALSE));
	CXTPGridColumn *pCol15 = m_lstReport.AddColumn(new CXTPGridColumn(15, "탁송료", 65, FALSE));//뒤로 한칸씩
	CXTPGridColumn *pCol16 = m_lstReport.AddColumn(new CXTPGridColumn(16, "부가세", 65, FALSE));// 
	CXTPGridColumn *pCol17 = m_lstReport.AddColumn(new CXTPGridColumn(17, "당월금액", 75, FALSE));
	CXTPGridColumn *pCol18 = m_lstReport.AddColumn(new CXTPGridColumn(18, "정산상태", 80, FALSE));;
	
	//새로
	//그룹이름, 부서명, 담당, 기간, 미수금, 누적미수금, 수금액,수금일자, 누적수금액,  계산서발행, 기타,
	//총건수, 현금, 신용, 송금. 탁송료, 부가세, 당월금액, 정산상태

	m_lstReport.SetPaintManager(new CGroupPaintManager24);
	m_lstReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	//	m_lstReport.GetReportHeader()->AllowColumnRemove(FALSE);
	//	m_lstReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstReport.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstReport.AllowEdit(FALSE);
	m_lstReport.SetGridColor(RGB(212, 208, 200));
	m_lstReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";


	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetTreeColumn(1);	
	m_lstReport.SetTreeIndent(10);

	m_lstReport.Populate();	

	m_lstReport.LoadReportOrder("CReportForm24", "m_lstReport");

	SetResize(IDC_GROUP_REPORT_CTRL, sizingRightBottom);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CGroupReportView::MakeListResultTree(long nGNo)
{ 
	if(nGNo <= 0)
		return;

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pVec = 	m_cg.GetRefreshGroup();
	long nLevel = m_cg.GetGroupData(nGNo)->nLevel;

	BOOL bFind = FALSE;

	for(it = pVec->begin(); it != pVec->end(); it++)
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);


		if(st->nGNo == nGNo)
		{
			pReocrdTop = m_lstReport.AddRecord(new CGroupReportRecord24(st));
			pReocrdTop->SetExpanded(TRUE);
			((CGroupReportRecord24*)pReocrdTop)->m_nReportTreeLevel = 0;
			bFind = TRUE;
			continue;
		}

		if(st->nParentGNo == nGNo ||
			st->nParentGNo2 == nGNo ||
			st->nParentGNo3 == nGNo ||
			st->nParentGNo4 == nGNo ||
			st->nParentGNo5 == nGNo)
		{
			switch(st->nLevel - nLevel)
			{
			case 1:
				pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CGroupReportRecord24(st));
				pReocrdLevel1->SetExpanded(TRUE);
				((CGroupReportRecord24*)pReocrdLevel1)->m_nReportTreeLevel = st->nLevel - nLevel;
				break;
			case 2:
				pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CGroupReportRecord24(st));
				pReocrdLevel2->SetExpanded(TRUE);
				((CGroupReportRecord24*)pReocrdLevel2)->m_nReportTreeLevel = st->nLevel - nLevel;
				break;
			case 3:
				pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CGroupReportRecord24(st));
				pReocrdLevel3->SetExpanded(TRUE);
				((CGroupReportRecord24*)pReocrdLevel3)->m_nReportTreeLevel = st->nLevel - nLevel;
				break;
			case 4:
				pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CGroupReportRecord24(st));
				pReocrdLevel4->SetExpanded(TRUE);
				((CGroupReportRecord24*)pReocrdLevel4)->m_nReportTreeLevel = st->nLevel - nLevel;
				break;
			case 5:
				pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CGroupReportRecord24(st));
				pReocrdLevel5->SetExpanded(TRUE);
				((CGroupReportRecord24*)pReocrdLevel5)->m_nReportTreeLevel = st->nLevel - nLevel;
				break;
			}

			//m_List.SetSelected(st->nGNo, TRUE);
		}
		else
		{
			if(bFind)
				break;
		}
	}

	GROUP_REPORT stSum;
	InitGroupReportStruct(stSum);

	stSum.nGNo = nGNo;

	m_lstReport.AddRecord(new CGroupReportRecord24(stSum, TRUE));
}


void CGroupReportView::GetData(CString sMainGNo, CMkRecordset &pRs)
{
	//CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_data_7");
	pCmd.AddParameter(sMainGNo);

	if(!pRs.Execute(&pCmd))
		return;

	//GetDataReal(pRs);
}

void CGroupReportView::GetDataReal(CMkRecordset *pRs)
{
	m_nNotIncome = 0;
	m_nIncome = 0;

	CString sTitle = "";
	GROUP_REPORT stSum; // 그룹별 합계
	InitGroupReportStruct(stSum);

	long nCashTax, nCreditTax, nOnlineTax, nTransTax;

	long nPreGNo = 0;
	long nGNo = 0;
	long nItem = 0;
	COleDateTime dtReportStart;

	GROUP_REPORT st;
	st = stSum;

	this->GetWindowText(sTitle);

	pRs->MoveFirst();

	for(int i=0; i<pRs->GetRecordCount(); i++)
	{
		pRs->GetFieldValue("nGNo", nGNo);
		pRs->GetFieldValue("dtReportStart", dtReportStart);

		CString sReportStart = dtReportStart.Format("%Y%m");

		if(sReportStart.Find(sTitle) == -1) 
		{
			//nPreGNo = nGNo;
			pRs->MoveNext();
			continue;
		}


		if((nGNo != nPreGNo) && (i != 0))
		{
			nItem = 0;
			m_lstReport.SetGroupData(nPreGNo, st);

			if(!m_cg.CheckGroup(nGNo, nPreGNo)) //완전히 새로운그룹
			{
				m_lstReport.SetGroupData(m_cg.GetGroupData(nPreGNo)->nParentGNo == 0 ? nPreGNo : m_cg.GetGroupData(nPreGNo)->nParentGNo, stSum, TRUE);

				InitGroupReportStruct(stSum);
				st = stSum;
			}

		}

		st.nGNo = nGNo;

		pRs->GetFieldValue("sGroupName", st.strGroupName);  
		pRs->GetFieldValue("sDept", st.strDept); 
		pRs->GetFieldValue("sName", st.strName); 
		pRs->GetFieldValue("nBalance", st.nBalance); 
		pRs->GetFieldValue("nInComeSum", st.nInComeSum); 

		pRs->GetFieldValue("nID", st.stData[nItem].nID);
		pRs->GetFieldValue("dtReportStart", st.stData[nItem].dtReportStart); 
		pRs->GetFieldValue("dtReportEnd", st.stData[nItem].dtReportEnd); 
		pRs->GetFieldValue("nCashCount", st.stData[nItem].nCashCount); 
		pRs->GetFieldValue("nCreditCount", st.stData[nItem].nCreditCount); 
		pRs->GetFieldValue("nOnlineCount", st.stData[nItem].nOnlineCount); 
		pRs->GetFieldValue("nTransCount", st.stData[nItem].nTransCount); 
		pRs->GetFieldValue("nCashCharge", st.stData[nItem].nCashCharge); 
		pRs->GetFieldValue("nCreditCharge", st.stData[nItem].nCreditCharge); 
		pRs->GetFieldValue("nOnlineCharge", st.stData[nItem].nOnlineCharge); 
		pRs->GetFieldValue("nTransCharge", st.stData[nItem].nTransCharge); 
		pRs->GetFieldValue("nReportState", st.stData[nItem].nReportState); 
		pRs->GetFieldValue("nBillCollection", st.stData[nItem].nBillCollection); 
		pRs->GetFieldValue("nUnCollection", st.stData[nItem].nUnBillCollection);  
		pRs->GetFieldValue("dtBillCollection", st.stData[nItem].dtBillCollection); 
		pRs->GetFieldValue("bPressBill", st.stData[nItem].bPressBill); 
		pRs->GetFieldValue("sEtc", st.stData[nItem].strEtc); 
		pRs->GetFieldValue("bNeedReReport", st.stData[nItem].bNeedReReport); 
		pRs->GetFieldValue("nCashTax", nCashTax);
		pRs->GetFieldValue("nCreditTax", nCreditTax);
		pRs->GetFieldValue("nOnlineTax", nOnlineTax);
		pRs->GetFieldValue("nTransTax", nTransTax);

		m_nNotIncome += st.stData[nItem].nUnBillCollection;
		m_nIncome += st.stData[nItem].nBillCollection;

		st.stData[nItem].nTax = nCashTax + nCreditTax + nOnlineTax + nTransTax;

		if(m_cg.GetGroupData(st.nGNo)->bNotShowCash)
		{
			st.stData[nItem].nCashCount = 0;
			st.stData[nItem].nCashCharge = 0;
		}


		stSum.stData[0].nCashCount += st.stData[nItem].nCashCount;
		stSum.stData[0].nCreditCount += st.stData[nItem].nCreditCount;
		stSum.stData[0].nOnlineCount += st.stData[nItem].nOnlineCount;
		stSum.stData[0].nTransCount += st.stData[nItem].nTransCount;
		stSum.stData[0].nCashCharge += st.stData[nItem].nCashCharge;
		stSum.stData[0].nCreditCharge += st.stData[nItem].nCreditCharge;
		stSum.stData[0].nOnlineCharge += st.stData[nItem].nOnlineCharge;
		stSum.stData[0].nTransCharge += st.stData[nItem].nTransCharge;

		stSum.stData[0].nSumCount += st.stData[nItem].nCashCount + st.stData[nItem].nCreditCount + st.stData[nItem].nOnlineCount;
		stSum.stData[0].nSumTotal += st.stData[nItem].nCashCharge + st.stData[nItem].nCreditCharge + st.stData[nItem].nOnlineCharge;
		stSum.stData[0].nBillCollection += st.stData[nItem].nBillCollection;
		stSum.stData[0].nUnBillCollection += st.stData[nItem].nUnBillCollection;

		stSum.stData[0].nTax += st.stData[nItem].nTax;

		if(nItem == 0) 
		{
			stSum.nBalance += st.nBalance;
			stSum.nInComeSum += st.nInComeSum;
		}

		stSum.nGNo = m_cg.GetGroupData(nGNo)->nLevel == 0 ? nGNo : m_cg.GetGroupData(nGNo)->nParentGNo;
		stSum.strGroupName = m_cg.GetGroupData(stSum.nGNo)->strGroupName;
		stSum.strDept = m_cg.GetGroupData(stSum.nGNo)->strDept;
		stSum.strName = m_cg.GetGroupData(stSum.nGNo)->strName;
		stSum.nReportRow = 0;

		nPreGNo = nGNo;
		st.nReportRow = nItem++;

		pRs->MoveNext();
	}

	m_lstReport.SetGroupData(st.nGNo, st);
	m_lstReport.SetGroupData(m_cg.GetGroupData(st.nGNo)->nParentGNo == 0 ? stSum.nGNo : m_cg.GetGroupData(st.nGNo)->nParentGNo, stSum, TRUE);

	CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());
	pReport->UpdateCount();
}

void CGroupReportView::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}

void CGroupReportView::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnUnBill();
}

void CGroupReportView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPGridColumn *p = m_lstReport.GetColumns()->GetAt(0); 
	if(p == NULL) return; 

	long h = m_lstReport.GetReportHeader()->GetGroupByHeight();

	CRect rcHeader = p->GetRect();  
	ClientToScreen(rcHeader);
	//ScreenToClient(rcHeader);

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = NULL;

	if(point.y >= rcHeader.top && 
		//point.y <= rect.top + rcHeader.Height())
		point.y <= rcHeader.bottom) 
	{
		pRMenu=rMenu.GetSubMenu(22);
	}
	else
		pRMenu=rMenu.GetSubMenu(13);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}



void CGroupReportView::OnAfterReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	CAfterReportDlg dlg;
	dlg.m_bAll = pRecord->m_bSumRecord; // 합계뿌린곳

	if(dlg.m_bAll)
	{
		dlg.m_nGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nLevel == 0 ? 
			pRecord->m_nGNo : m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;
	}
	else
		dlg.m_nGNo = pRecord->m_nGNo;

	dlg.DoModal();

}

void CGroupReportView::OnUnBill()
{
	long nTopGNo = 0;
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	CUnBillDlg dlg;
	dlg.m_bAll = pRecord->m_bSumRecord; // 합계뿌린곳

	if(dlg.m_bAll)
	{
		dlg.m_nGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nLevel == 0 ? 
			pRecord->m_nGNo : m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;

		nTopGNo = dlg.m_nGNo;
	}
	else
	{
		dlg.m_nGNo = pRecord->m_nGNo;
		nTopGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nLevel == 0 ? 
			pRecord->m_nGNo : m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;
	}

	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_bChangeItem)
		{
			CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());

			CString sGNo = "";
			sGNo.Format("%d;", dlg.m_nGNo);
			pReport->SetData(sGNo);
		}
	}
}

void CGroupReportView::OnTaxAccount()
{
	long nID = 0;
	long nItem = 0;
	CString sEtc;
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	CString sDate;
	COrderSeeDlg orderdlg;

	if(pRecord->m_bSumRecord)
	{
		MessageBox("전체 세금계산서는 수정할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_stGroup.nReportRow > 0) // 두개가 뿌려짐;
	{
		CCommonDlg2 dlg;
		dlg.m_nRowCount = pRecord->m_stGroup.nReportRow + 1;

		for(int i=0; i<pRecord->m_stGroup.nReportRow + 1; i++)
		{
			if( i <  MAX_BUTTON_COUNT)
			dlg.m_sOption[i].Format("%s ~ %s", pRecord->m_stGroup.stData[i].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[i].dtReportEnd.Format("%m-%d"));
		}

		if(dlg.DoModal() == IDOK)
		{
			nItem = dlg.m_nSelItem;
		}
	}

	nID = pRecord->m_stGroup.stData[nItem].nID;


	BOOL bPressBill = pRecord->m_stGroup.stData[nItem].bPressBill;
	CString sMsg = "";

	if(bPressBill)
		sMsg.Format("[%s ~ %s]의 세금계산서 발행을 취소 하시겠습니까?", pRecord->m_stGroup.stData[nItem].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[nItem].dtReportEnd.Format("%m-%d"));
	else
		sMsg.Format("[%s ~ %s]의 세금계산서를 발행 하시겠습니까?", pRecord->m_stGroup.stData[nItem].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[nItem].dtReportEnd.Format("%m-%d"));

	if(MessageBox(sMsg, "확인", MB_YESNO) != IDYES) return;

	CMkCommand pCmd(m_pMkDb, "update_GROUP_REPORT_bill_press");
	pCmd.AddParameter(nID);
	pCmd.AddParameter(!bPressBill);

	if(pCmd.Execute())
	{
		pRecord->m_stGroup.stData[nItem].bPressBill = !bPressBill;
	}
}

void CGroupReportView::OnEtc()
{
	long nID = 0;
	long nItem = 0;
	CString sEtc;
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());


	CString sDate;
	COrderSeeDlg orderdlg;

	if(pRecord->m_bSumRecord)
	{
		MessageBox("전체적요는 수정할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_stGroup.nReportRow > 0) // 두개가 뿌려짐;
	{
		CCommonDlg2 dlg;
		dlg.m_nRowCount = pRecord->m_stGroup.nReportRow + 1;

		for(int i=0; i<pRecord->m_stGroup.nReportRow + 1; i++)
		{
			if( i< MAX_BUTTON_COUNT)
			dlg.m_sOption[i].Format("%s ~ %s", pRecord->m_stGroup.stData[i].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[i].dtReportEnd.Format("%m-%d"));
		}

		if(dlg.DoModal() == IDOK)
		{
			nItem = dlg.m_nSelItem;
		}
	}

	nID = pRecord->m_stGroup.stData[nItem].nID;
	sEtc = pRecord->m_stGroup.stData[nItem].strEtc;

	CCommonDlg1 dlg;
	dlg.m_strEdit = sEtc;

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "update_GROUP_REPORT_etc");
		pCmd.AddParameter(nID);
		pCmd.AddParameter(dlg.m_strEdit);

		if(pCmd.Execute())
		{
			pRecord->m_stGroup.stData[nItem].strEtc = dlg.m_strEdit;
		}
	}
}

void CGroupReportView::OnExcel()
{
	if(!POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	long nRow = 0;

	CXTPGridRows *pRows = m_lstReport.GetRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRow * pRow = pRows->GetAt(i);
		CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)pRow->GetRecord();

		if(pRecord->m_bSumRecord)
			continue;

		nRow += m_cg.GetGroupData(pRecord->m_nGNo)->nGroupCount;
	}

	nRow = (nRow * 2) + pRows->GetCount() + 1;

	long nCol = m_lstReport.GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = {nRow, nCol};
	sa.Create(VT_VARIANT, 2, elements);

	long nItem = 1;

	for(int r = 0; r < pRows->GetCount()+1; r++)
	{
		if(r == 0)
		{
			CString str;

			for(int c=0; c<nCol; c++)
			{
				VARIANT v;
				VariantInit(&v);

				long index[] = {r, c};
				CXTPGridColumn *pCol = m_lstReport.GetColumns()->GetVisibleAt(c);
				str = pCol->GetCaption();
				v.vt = VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);

				VariantClear(&v);
			}
		}
		else
		{
			CXTPGridRow *pRow = pRows->GetAt(r-1);
			CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)pRow->GetRecord();
	
			GROUP_REPORT st  = pRecord->m_stGroup;

			SetExcelData(sa, st, pRecord->m_bSumRecord, nItem, nCol);
		}
	}

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 314, m_ui.nWNo, m_lstReport.GetRows()->GetCount());  

	CMyExcel::ToExcel(sa, nCol, nRow);
}

void CGroupReportView::SetExcelData(COleSafeArray &sa, GROUP_REPORT st, BOOL bSumRecord, long &nItem, long nCol)
{
	for(int i=0; i<max(st.nReportRow, 0)+1; i++)
	{
		for(int j=0; j<nCol; j++)
		{ 
			CXTPGridColumn *pCol = m_lstReport.GetColumns()->GetVisibleAt(j);
			CString str = GetGroupReportText1(st, pCol->GetItemIndex(), i, bSumRecord);

			//CString str = GetGroupReportText1(st, j, i, bSumRecord);

			if((j == 0) && (m_cg.GetGroupData(st.nGNo)->nLevel != 0))
			{
				CString strEmpty = "";

				for(int k=0; k<m_cg.GetGroupData(st.nGNo)->nLevel; k++)
					strEmpty += "  ";

				str = strEmpty + "┗" + str;
			}

			VARIANT v;
			VariantInit(&v);

			long index[] = {nItem, j};
			v.vt= VT_BSTR;
			v.bstrVal = str.AllocSysString();
			sa.PutElement(index, &v);
			SysFreeString(v.bstrVal);

			VariantClear(&v);
		}
		nItem++;
	}

	if(bSumRecord)
	{
		for(int j=0; j<nCol; j++)
		{ 
			CString str = "";

			VARIANT v;
			VariantInit(&v);

			long index[] = {nItem, j};
			v.vt= VT_BSTR;
			v.bstrVal = str.AllocSysString();
			sa.PutElement(index, &v);
			SysFreeString(v.bstrVal);

			VariantClear(&v);
		}
		nItem++; //한칸 빈줄
	}	
};





void CGroupReportView::OnOrderSee()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	CString sDate;
	COrderSeeDlg orderdlg;
	long nItem = 0;

	if(pRecord->m_bSumRecord)
	{
		MessageBox("오더보기는 전체 보기를 할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_stGroup.nReportRow > 0) // 두개가 뿌려짐;
	{
		CCommonDlg2 dlg;
		dlg.m_nRowCount = min(pRecord->m_stGroup.nReportRow + 1, 20);

		for(int i=0; i<pRecord->m_stGroup.nReportRow + 1; i++)
		{
			if( i < MAX_BUTTON_COUNT)
				dlg.m_sOption[i].Format("%s ~ %s", pRecord->m_stGroup.stData[i].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[i].dtReportEnd.Format("%m-%d"));
		}

		if(dlg.DoModal() == IDOK)
		{
			nItem = dlg.m_nSelItem;
		}
	}

	orderdlg.m_nID = pRecord->m_stGroup.stData[nItem].nID;
	orderdlg.m_nGNo = pRecord->m_nGNo;
	orderdlg.DoModal();   
}

void CGroupReportView::OnDeleteAll()
{
	m_lstReport.GetRecords()->RemoveAll();
	m_lstReport.Populate();
}

void CGroupReportView::OnDeleteGroup()
{
	long nSel = 0;

	if(m_lstReport.GetSelectedRows()->GetCount() != 0) 
		nSel = m_lstReport.GetSelectedRows()->GetAt(0)->GetIndex();
	else
		return;

	//여이서부터가 밑ㅌ에 합계부분 레코드 지워주는부분
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);
	CGroupReportRecord24 *pRecord = ((CGroupReportRecord24*)pRow->GetRecord());

	for(int i=pRow->GetIndex(); i<m_lstReport.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pNextRow = m_lstReport.GetRows()->GetAt(i);
		CGroupReportRecord24 *pNextRecord = (CGroupReportRecord24*)pNextRow->GetRecord();

		if(pNextRecord->m_bSumRecord == TRUE)
		{
			pNextRecord->SetVisible(FALSE);
			pNextRecord->RemoveAll();
			break;
		}
	}

	if(pRecord->m_nGNo == 0)
		return;

	for(int i=0; i<pRecord->m_nReportTreeLevel; i++)
		pRow = pRow->GetParentRow();

	pRecord = (CGroupReportRecord24*)pRow->GetRecord();

	if(pRecord->HasChildren())
	{
		CXTPGridRecords *pChildRecords = pRecord->GetChilds();

		for(int k = 0; k < pChildRecords->GetCount(); k++)
		{
			CallChildReport(pChildRecords->GetAt(k));
		}		

		pChildRecords->RemoveAll();
	}
}

void CGroupReportView::OnIncome()
{
	long nID = 0;
	long nItem = 0;
	long nGNo = 0;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());


	if(pRecord->m_bSumRecord)
	{
		MessageBox("입금은 그룹을 선택해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_stGroup.nReportRow > 0) // 두개가 뿌려짐;
	{
		CCommonDlg2 dlg;
		dlg.m_nRowCount = pRecord->m_stGroup.nReportRow + 1;

		for(int i=0; i<pRecord->m_stGroup.nReportRow + 1; i++)
		{
			if( i < MAX_BUTTON_COUNT)
			dlg.m_sOption[i].Format("%s ~ %s", pRecord->m_stGroup.stData[i].dtReportStart.Format("%m-%d"), pRecord->m_stGroup.stData[i].dtReportEnd.Format("%m-%d"));
		}

		if(dlg.DoModal() == IDOK)
			nItem = dlg.m_nSelItem;
		else return;
	}

	nID = pRecord->m_stGroup.stData[nItem].nID;

	if(pRecord->m_stGroup.stData[nItem].nUnBillCollection <= 0)
	{
		MessageBox("이미 모두 입금처리 되었습니다", "확인", MB_ICONINFORMATION);
		return;		
	}

	CGroupIncomeDlg dlg;
	dlg.m_nID = nID;
	dlg.m_nDebit = pRecord->m_stGroup.stData[nItem].nUnBillCollection;
	dlg.m_sDate = pRecord->m_stGroup.stData[nItem].dtReportStart.Format("%m-%d") + pRecord->m_stGroup.stData[nItem].dtReportEnd.Format("%m-%d");


	if(m_cg.GetGroupData(pRecord->m_nGNo)->nLevel != 0) // 최상위 그룹을 가져온다
		nGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;//
	else
		nGNo = pRecord->m_nGNo;

	if(dlg.DoModal() == IDOK)
	{
		CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());
		
		CString sGNo = "";
		sGNo.Format("%d;", nGNo);
		pReport->SetData(sGNo);

		m_cg.SetDataNotIncomeMonth(pRecord->m_nGNo, dlg.m_sRet);
	}
}



void CGroupReportView::OnMakeGroupReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	if(pRecord->m_bSumRecord)
	{
		MessageBox("그룹 정산데이터를 생성하려는 그룹을 선택해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMakeGroupReportDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	
	

	dlg.DoModal();

	if(dlg.m_bRefresh == TRUE)
	{
		CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());

		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		pReport->SetData(sGNo);
	}

}

void CGroupReportView::OnDeleteGroupReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	if(pRecord->m_bSumRecord)
	{
		MessageBox("그룹 정산데이터를 생성하려는 그룹을 선택해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CDeleteGroupReportDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;

	dlg.DoModal();

	if(dlg.m_bRefresh == TRUE)
	{
		CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());

		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		pReport->SetData(sGNo);
	}
}

void CGroupReportView::OnReGroupReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRows->GetAt(0)->GetRecord());

	if(pRecord->m_bSumRecord)
	{
		MessageBox("그룹 정산데이터를 생성하려는 그룹을 선택해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CReGroupReportDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;

	dlg.DoModal();

	if(dlg.m_bRefresh == TRUE)
	{
		CReportForm24 * pReport = (CReportForm24*)(GetParent()->GetParent());

		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		pReport->SetData(sGNo);
	}
}

void CGroupReportView::CallChildReport(CXTPGridRecord *pRecord)
{
	if(pRecord->HasChildren()) 
	{
		CXTPGridRecords *pChildRecords = pRecord->GetChilds();

		for(int k = 0; k < pChildRecords->GetCount(); k++)
		{
			CallChildReport(pChildRecords->GetAt(k));

			CGroupReportRecord24 *pChildRecord = ((CGroupReportRecord24*)pChildRecords->GetAt(k));
//			m_List.SetSelected(pChildRecord->m_nGNo, FALSE);
		}

		pChildRecords->RemoveAll();
	}

	m_lstReport.GetRows()->RemoveRow(m_lstReport.GetRows()->GetAt(pRecord->GetIndex()));
//	m_List.SetSelected(((CGroupReportRecord24*)pRecord)->m_nGNo, FALSE);
	pRecord->RemoveAll();
}

void CGroupReportView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMyFormView::OnLButtonUp(nFlags, point);
}

HBRUSH CGroupReportView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return hbr;
}

void CGroupReportView::DeleteZeroRecord()
{
	CString sText; this->GetWindowText(sText); 
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	long nCount = pRecords->GetCount();
	long nItem = 0;
 
	for(int i=0; i<nCount; i++)
	{ 
		CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRecords->GetAt(nItem));

		if(pRecord->m_bSumRecord)
		{
			if(pRecord->m_stGroup.stData[0].nUnBillCollection <= 0)
			{
				m_lstReport.GetRecords()->RemoveAt(pRecord->GetIndex());
				m_lstReport.GetRecords()->RemoveAt(pRecord->GetIndex() - 1);
				nItem -= 1;
				continue;
			}
		}

		nItem++;
	}

	m_lstReport.Populate(); //총건수가 0


	//0인거 삭제 각 지사그룹별

	pRecords = m_lstReport.GetRecords();
	nCount = pRecords->GetCount();
	nItem = 0;
	
	for(int i=0; i<nCount; i++)
	{ 
		CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)(pRecords->GetAt(nItem));
 
		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			long nSubCount = pChildRecords->GetCount();
			long nSubItem = 0;

			for(int k = 0; k < nSubCount; k++) 
			{
				CGroupReportRecord24 *pChildRecord = (CGroupReportRecord24*)pChildRecords->GetAt(nSubItem);
				CallChildReportForCheckZero(pChildRecord);

				if(!pChildRecord->HasChildren())
				{
					if(pChildRecord->m_stGroup.stData[0].nUnBillCollection <= 0)
					{
						pChildRecords->RemoveAt(nSubItem);
						continue;
					}
				}

				nSubItem++;
			}
		}

		nItem++;
	}

	m_lstReport.Populate(); 
}

void CGroupReportView::CallChildReportForCheckZero(CXTPGridRecord *pRecord)
{
	if(pRecord->HasChildren()) 
	{
		CXTPGridRecords *pChildRecords = pRecord->GetChilds();
		long nCount = pChildRecords->GetCount();

		long nItem = 0;

		for(int k = 0; k < nCount; k++)
		{
			CallChildReportForCheckZero(pChildRecords->GetAt(nItem));

			CGroupReportRecord24 *pChildRecord = ((CGroupReportRecord24*)pChildRecords->GetAt(nItem));

			if(pChildRecord->m_stGroup.stData[0].nUnBillCollection <= 0)
				pChildRecords->RemoveAt(nItem);
			else
				nItem++;			
		}
	}
}

void CGroupReportView::ShowCurLocation(long nGNo)
{ 
	CXTPGridRows *pRows = m_lstReport.GetRows();
	
 
	for(int i=0; i<pRows->GetCount(); i++)
	{
		CGroupReportRecord24 *pRecord = ((CGroupReportRecord24*)pRows->GetAt(i)->GetRecord());

		if(pRecord->m_bSumRecord)
			continue; 

		if(pRecord->m_stGroup.nGNo == nGNo) 
		{    
			CXTPGridRow *pRow = pRows->GetAt(min(i + 15, pRows->GetCount() - 1));
			m_lstReport.EnsureVisible(pRow);
			pRow =pRows->GetAt(i);
			m_lstReport.GetSelectedRows()->Select(pRow);
 
			//CXTPGridRow *pRow = pRows->GetAt(min(i + 15, pRows->GetCount() - 1));
			//pRow->EnsureVisible();
			//pRow = pRows->GetAt(i);
			//m_lstReport.GetSelectedRows()->Select(pRow);
			//m_lstReport.Populate();

			break; 
		}
	}
}

void CGroupReportView::OnVisibleCol()
{ 
	CColumnSelDlg dlg;
	dlg.m_plstReport = (CXTPListCtrl2*)&m_lstReport;
	dlg.m_sClass = "CReportForm24";

	dlg.m_sList = "m_lstReport";

	if(dlg.DoModal())
	{
		m_lstReport.LoadReportOrder(dlg.m_sClass, dlg.m_sList);
		m_lstReport.Populate();
	}
}