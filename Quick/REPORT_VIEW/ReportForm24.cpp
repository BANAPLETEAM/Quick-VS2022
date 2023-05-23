// ReportForm17.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm24.h"
#include "AddGroupDlg.h"
#include "GroupSearchDlg.h" 

#include "GroupReportView.h"
#include "ColumnSelDlg.h"
 
 
void CReport24TabControl::OnItemClick(CXTPTabManagerItem* pItem)
{
	if(GetCurSel() == pItem->GetIndex()) 
		return;

	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();

	if(hWnd == NULL) 
		return;

	CWnd* pWnd =  FromHandle(pItem->GetHandle());
	CGroupReportView *pGroupView	= (CGroupReportView*)pWnd;

	CReportForm24 * pReport = (CReportForm24*)(pGroupView->GetParent()->GetParent());

	pReport->UpdateCount();
}


//기존
//그룹이름, 부서명, 담당, 기간, 총건수, 현금, 신용, 송금, 탁송료, 부가세, 당원금액, 정산상태,
//수금액,  수금일자, 미수금, 누적미수금, 계산서발행, 기타



IMPLEMENT_DYNCREATE(CReportForm24, CMyFormView)

CReportForm24::CReportForm24()
: CMyFormView(CReportForm24::IDD)
{
	for(int i=0; i<6; i++)
		m_strNotIncomeMonth[i] = "";
	m_bFullScreen = FALSE;
	m_pGroupSearchDlg = NULL;

	m_nUnBillCollection = 0;
	m_nBillCollection = 0;
	m_nCashCount = 0;
	m_nCreditCount = 0 ;
	m_nCreditCharge = 0;
	m_nCashCharge = 0;
}

CReportForm24::~CReportForm24()
{
	if(m_pGroupSearchDlg != NULL)
	{
		delete m_pGroupSearchDlg;
		m_pGroupSearchDlg = NULL;
	}
}

void CReportForm24::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_REPORT, m_List);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_DELETE_ALL_BTN, m_DeleteAllBtn);
	DDX_Control(pDX, IDC_DELETE_PART_BTN, m_DeletePartBtn);
	DDX_Control(pDX, IDC_TIP_STATIC, m_TipStc);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stcDraw);
	DDX_Control(pDX, IDC_LINE_STATIC, m_stcLine);
}

BEGIN_MESSAGE_MAP(CReportForm24, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_REFRESH_CHOOSE_BTN, OnBnClickedRefreshChooseBtn)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_GROUP_REPORT, OnReportBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_REPORT, OnGroupReportItemDbClick)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_REPORT, OnGroupReportItemClick)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_FULL_SCREEN_BTN, OnBnClickedFullScreenBtn)
	ON_EN_SETFOCUS(IDC_SEARCH_EDIT, OnEnSetfocusSearchEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CReportForm24 진단입니다.

#ifdef _DEBUG
void CReportForm24::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm24::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG




void CReportForm24::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CReportForm24::OnBnClickedRefreshChooseBtn()
{
	PreRefreshList(FALSE);
}

void CReportForm24::OnBnClickedRefreshBtn()
{
	PreRefreshList(TRUE);
}

void CReportForm24::PreRefreshList(BOOL bAll)
{
	DeleteAllList();

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	CXTPGridRecords *pRecords = (CXTPGridRecords*)m_List.GetRecords();
	long nCount = pRecords->GetCount();
	long nSelCount = pRows->GetCount();

	if(nCount > 400 && bAll == TRUE)
	{
		MessageBox("400 그룹이상 동시 조회 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPTabManagerItem *pItem[MAX_TAB_COUNT];
	CGroupReportView *pView[MAX_TAB_COUNT];

	CString strGNo[MAX_TAB_COUNT];
	CString strNotIncomeDate[MAX_TAB_COUNT];
	BOOL bInsert[MAX_TAB_COUNT] = {0, };
	char buffer[10];

	for(int i=0; i<MAX_TAB_COUNT; i++)
	{
		pItem[i] = m_wndTabControl.GetItem(i);
		strNotIncomeDate[i] = pItem[i]->GetCaption();
		pView[i] =  (CGroupReportView*)FromHandle(pItem[i]->GetHandle());
	}

	strNotIncomeDate[0] = "";

	if(bAll)
	{
		for(int i=0; i<nCount; i++)
		{ 
			CGroupRecord24* pRecord = (CGroupRecord24*)pRecords->GetAt(i);
			ST_CUSTOMER_GROUP_INFOMATION * pInfo = m_cg.GetGroupData(pRecord->m_nGNo);
			
			pView[0]->MakeListResultTree(pRecord->m_nGNo);
			strGNo[0] += (CString)itoa(pRecord->m_nGNo, buffer, 10) + ";";
			bInsert[0] = TRUE;

			for(int j=1; j<MAX_TAB_COUNT; j++)
			{
				if(pInfo->strNotIncomeMonthData.Find(strNotIncomeDate[j]) >= 0) 
				{
					strGNo[j] += (CString)itoa(pRecord->m_nGNo, buffer, 10) + ";";
					bInsert[j] = TRUE;
					pView[j]->MakeListResultTree(pRecord->m_nGNo);
				}
			}
		}
	}
	else
	{
		typedef std::vector<int> vec;
		vec v;

		for(int i=0; i<nSelCount; i++)
		{ 
			CXTPGridRow *pRow = pRows->GetAt(i);
			CGroupRecord24* pRecord = (CGroupRecord24*)pRow->GetRecord();  
			ST_CUSTOMER_GROUP_INFOMATION * pInfo = m_cg.GetGroupData(pRecord->m_nGNo);
 
			long nGNo = pInfo->nLevel == 0 ? pRecord->m_nGNo : pInfo->nParentGNo;

			vec::iterator it;
			it = find(v.begin(), v.end(), nGNo);

			if(it == v.end())
				v.push_back(nGNo);
			else
				continue;

			pView[0]->MakeListResultTree(nGNo);
			strGNo[0] += (CString)itoa(nGNo, buffer, 10) + ";";
			bInsert[0] = TRUE;

			for(int j=1; j<MAX_TAB_COUNT; j++)
			{
				if(pInfo->strNotIncomeMonthData.Find(strNotIncomeDate[j]) >= 0) 
				{
					strGNo[j] += (CString)itoa(pRecord->m_nGNo, buffer, 10) + ";";
					bInsert[j] = TRUE;
					pView[j]->MakeListResultTree(pRecord->m_nGNo);
				}
			}
		}
	}
	
	CMkRecordset pRs(m_pMkDb);
	pView[0]->GetData(strGNo[0], pRs); 

	for(int i=0; i<MAX_TAB_COUNT; i++)
	{
		pView[i]->SetWindowText(strNotIncomeDate[i]);
		pView[i]->m_lstReport.Populate(); 
		pView[i]->GetDataReal(&pRs);

		if(i>0)
			pView[i]->DeleteZeroRecord();
		//pView[i]->GetData(sGNo[i]);
	}

	if(m_pGroupSearchDlg == NULL)
		OpenSearchDlg();

	m_pGroupSearchDlg->ShowWindow(FALSE);
	UpdateCount();
}

void CReportForm24::OpenSearchDlg()
{
	if(m_pGroupSearchDlg == NULL)
	{ 
		m_pGroupSearchDlg = new CGroupSearchDlg(this);
		m_pGroupSearchDlg->Create(IDD_GROUP_SEARCH_DLG, this); 

		CRect rcEdt, rcBox;
		m_edtSearch.GetWindowRect(rcEdt);
		m_pGroupSearchDlg->GetWindowRect(rcBox);

		long nHeight = rcBox.Height();
		long nWidth = rcBox.Width();

		rcBox.left = rcEdt.right + 2;
		rcBox.right = rcBox.left + nWidth;
		rcBox.top = rcEdt.bottom + 1;
		rcBox.bottom = rcBox.top + nHeight;

		m_pGroupSearchDlg->MoveWindow(rcBox);		
	}

	m_pGroupSearchDlg->ShowWindow(TRUE);
}


void CReportForm24::SearchFilter()
{
	m_List.GetRecords()->RemoveAll();


	BOOL bCashOption = FALSE,  bCreditOption = FALSE, bActiveOption  = FALSE,  bUnActiveOption  = FALSE;

	CString strSearchData; m_edtSearch.GetWindowText(strSearchData);
	CString strSearchDateData;
	if(!m_pGroupSearchDlg)
		OpenSearchDlg();

	if(m_pGroupSearchDlg)
	{
		bCashOption = m_pGroupSearchDlg->m_chkCashOption.GetCheck();
		bCreditOption = m_pGroupSearchDlg->m_chkCreditOption.GetCheck();
		bActiveOption = m_pGroupSearchDlg->m_chkActiveOption.GetCheck();
		bUnActiveOption = m_pGroupSearchDlg->m_chkUnActiveOption.GetCheck();
		m_pGroupSearchDlg->m_cmbReportDay.GetLBText(m_pGroupSearchDlg->m_cmbReportDay.GetCurSel(), strSearchDateData);
		strSearchData.MakeUpper();
	}

	long nCount = 0;

	if(strSearchData.IsEmpty() == FALSE)
	{
		if(CheckCharValid(strSearchData) == FALSE)
			return;
	}

	GetSearchDay(nCount);
	
	if(strSearchDateData == "정산안함")
		strSearchDateData = "0";
	else if(strSearchDateData == "말일")
		strSearchDateData = "32";

	strSearchDateData = "$" + strSearchDateData + "%";
	strSearchDateData.Replace("$전체%", "");

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pVec = 	m_cg.GetRefreshGroup();
	BOOL bAtleastFind = FALSE;

	for(it = pVec->begin(); it != pVec->end(); it++)
	{
		BOOL bFind = TRUE;
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		if(st->nLevel == 0) 
		{
			if((bCashOption == FALSE) && (st->nGroupCredit == FALSE))
				continue;
			else if((bCreditOption == FALSE) && (st->nGroupCredit == TRUE))
				continue;

			if((bActiveOption == FALSE) && (st->nActiveGroupLevel == 1)) 
				continue;
			if((bUnActiveOption == FALSE) && (st->nActiveGroupLevel == 0))
				continue;

			st->strSearchData.MakeUpper();

			if(st->strSearchData.Find(strSearchData) == -1)
				continue;

			if(st->strSearchDateData.Find(strSearchDateData) == -1)
				continue;

			BOOL bFind = FALSE; 
			
			if(nCount == 0)
				bFind = TRUE;
			else
			{
				for(int i=0; i<nCount; i++)
				{
					if(st->strNotIncomeMonthData.Find(m_strNotIncomeMonth[i]) >=0)
					{
						bFind = TRUE;
						break;
					}				                			
				}
			}

			if(bFind == FALSE)
				continue;
		}
		else
			continue;

		bAtleastFind = TRUE;
		MakeListTree(st->nGNo, it);
	}

	//if(bAtleastFind)	m_List.Populate();	 
 
	if(pVec->size() == 0) 
		m_List.GetPaintManager()->m_strNoItems = "그룹 정보가 생성되어 있지 않습니다.";
	else if(m_List.GetRows()->GetCount() == 0)
		m_List.GetPaintManager()->m_strNoItems = "정산일 / 미수금 항목 등 검색 항목을 확인하세요.";

	m_List.Populate();
}

void CReportForm24::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CXTPGridColumn* pCol20 = m_List.AddColumn(new CXTPGridColumn(0, "그룹이름", 120));
	CXTPGridColumn *pCol21 = m_List.AddColumn(new CXTPGridColumn(1, "부서명", 90, TRUE));
	CXTPGridColumn *pCol22 = m_List.AddColumn(new CXTPGridColumn(2, "정산일", 50, TRUE));
 
	m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnReorder(FALSE);
	m_List.AllowEdit(FALSE);
	m_List.SetGridColor(RGB(222, 222, 222));
	m_List.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_List.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);

	pCol20->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol20->SetTreeColumn(1);	
	m_List.SetTreeIndent(10);

	m_List.Populate();	

	SetResize(IDC_GROUP_REPORT, sizingBottom);
	SetResize(IDC_DRAW_STATIC, sizingRightBottom);


	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_GROUP_REPORT);
	pWnd->GetWindowRect(m_rcLst);
	ScreenToClient(m_rcLst);

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_DRAW_STATIC)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_DRAW_STATIC)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CGroupReportView), "전체", 0);
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	
	for(int i=0; i<6; i++)
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CGroupReportView), dtCur.Format("%Y%m"), 0);
		dtCur = dtCur - COleDateTimeSpan(30, 0, 0, 0);
	}
}

void CReportForm24::RefreshList()
{
	CMyFormView::RefreshList();

	long nSel = 0;

	if(m_List.GetSelectedRows()->GetCount() != 0)
		nSel = m_List.GetSelectedRows()->GetAt(0)->GetIndex();

	m_List.GetRecords()->RemoveAll();

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
			pReocrdTop = m_List.AddRecord(new CGroupRecord24(st));
			pReocrdTop->SetExpanded(TRUE);
			break;
		case 1:
			pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CGroupRecord24(st));
			((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel1->SetExpanded(TRUE);
			break;
		case 2:
			pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CGroupRecord24(st));
			((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel2->SetExpanded(TRUE);
			break;
		case 3:
			pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CGroupRecord24(st));
			((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel3->SetExpanded(TRUE);
			break;
		case 4:
			pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CGroupRecord24(st));
			((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel4->SetExpanded(TRUE);
			break;
		case 5:
			pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CGroupRecord24(st));
			((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel5->SetExpanded(TRUE);
			break;
		}
	}

	m_List.Populate();

	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nSel, m_List.GetRows()->GetCount() -1));

	m_List.GetSelectedRows()->Select(pRow);
}

void CReportForm24::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyFormView::OnMouseMove(nFlags, point);
}

void CReportForm24::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		CRect rect;
		m_wndTabControl.GetWindowRect(&rect);
		ScreenToClient(rect);

		CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
		CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

		if(rect.PtInRect(point))
		{
			CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);

			if(pRow == NULL)
				return;
 
			CGroupRecord24 *pRecord = (CGroupRecord24*)pRow->GetRecord();
			long nGNo = 0; 

			if(m_cg.GetGroupData(pRecord->m_nGNo)->nLevel != 0) // 최상위 그룹을 가져온다
				nGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;//
			else
				nGNo = pRecord->m_nGNo;

			CString sGNo = "";
			sGNo.Format("%d;", nGNo); 

			pView->MakeListResultTree(nGNo); 
			pView->m_lstReport.Populate(); 

			CMkRecordset pRs;
			pView->GetData(sGNo, pRs);
			pView->GetDataReal(&pRs);
		}
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //순서에 주의 할것

	CMyFormView::OnLButtonUp(nFlags, point);
}

void CReportForm24::MakeListTree(long nGNo, VEC_CUSTOMER_GROUP::iterator it)
{
	if(nGNo <= 0)
		return; 

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	VEC_CUSTOMER_GROUP *pVec = 	m_cg.GetRefreshGroup();
	long nLevel = m_cg.GetGroupData(nGNo)->nLevel;
	BOOL bFind = TRUE;

	while(it != pVec->end())
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		if(st->nGNo == nGNo)
		{
			pReocrdTop = m_List.AddRecord(new CGroupRecord24(st));
			//pReocrdTop->SetExpanded(TRUE);
			bFind = TRUE;
			it++;
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
				pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CGroupRecord24(st));
				((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
				//pReocrdLevel1->SetExpanded(TRUE);
				break;
			case 2:
				pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CGroupRecord24(st));
				((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
				//pReocrdLevel2->SetExpanded(TRUE);
				break;
			case 3:
				pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CGroupRecord24(st));
				((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
				//pReocrdLevel3->SetExpanded(TRUE);
				break;
			case 4:
				pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CGroupRecord24(st));
				((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
				//pReocrdLevel4->SetExpanded(TRUE);
				break;
			case 5:
				pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CGroupRecord24(st));
				((CGroupRecord24*)pReocrdTop)->AddSearchData(st);
				//pReocrdLevel5->SetExpanded(TRUE);
				break;
			}

			it++;
		}
		else//(st->nParentGNo == nGNo ||
		{
			if(bFind)
				break;
		}		
	}//(it != pVec->end())
}


void CReportForm24::OnEnChangeSearchEdit()
{
	SearchFilter(); 
	m_edtSearch.SetFocus();
}

void CReportForm24::UpdateCount()
{
	m_nUnBillCollection = 0;
	m_nBillCollection = 0;
	m_nCashCount = 0;
	m_nCreditCount = 0;
	m_nCreditCharge = 0;
	m_nCashCharge = 0;

	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

	CXTPGridRows *pRows = pView->m_lstReport.GetRows();
	//long a = pRows->GetCount();

	for(int i=0; i<pRows->GetCount(); i++)
	{
        CXTPGridRow *pRow = pRows->GetAt(i);
		CGroupReportRecord24* pRecord = (CGroupReportRecord24*)pRow->GetRecord();

		if(pRecord->m_bSumRecord)
		{ 
            m_nUnBillCollection += pRecord->m_stGroup.stData[0].nUnBillCollection;
			m_nBillCollection += pRecord->m_stGroup.stData[0].nBillCollection;
			m_nCreditCharge += pRecord->m_stGroup.stData[0].nCreditCharge + pRecord->m_stGroup.stData[0].nOnlineCharge;
			m_nCashCharge += pRecord->m_stGroup.stData[0].nCashCharge;
		}
		else
		{
			if(m_cg.GetGroupData(pRecord->m_nGNo)->nLevel != 0)
				continue;

			if(m_cg.GetGroupData(pRecord->m_nGNo)->nGroupCredit == 1)
				m_nCreditCount++;
			else
				m_nCashCount++;
		}
	} 

	Invalidate(TRUE);
}

void CReportForm24::OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);

	if(pRow == NULL) 
		return;

	CGroupRecord24 *pRecord = (CGroupRecord24*)pRow->GetRecord();

	CAddGroupDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.m_bAdd = FALSE;

	if(dlg.DoModal())
	{
		RefreshList();
		OnEnChangeSearchEdit();
	}
}


void CReportForm24::OnGroupReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRow *pRow = pRows->GetAt(0);
	CGroupRecord24 *pRecord = (CGroupRecord24*)pRow->GetRecord();

	ST_CUSTOMER_GROUP_INFOMATION * pInfo = m_cg.GetGroupData(pRecord->m_nGNo);

	if(pInfo == NULL) return;

	long nGNo = pInfo->nLevel == 0 ? pRecord->m_nGNo : pInfo->nParentGNo;

	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

	if(pView == NULL) return;

	pView->ShowCurLocation(nGNo);
}

void CReportForm24::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	MoveControl();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CReportForm24::MoveControl()
{
	if(!IsWindow(m_edtSearch.GetSafeHwnd()))
		return;

	CRect rc;
	m_stcDraw.GetWindowRect(&rc);
	ScreenToClient(rc);

	m_wndTabControl.MoveWindow(rc);
}

void CReportForm24::OnBnClickedFullScreenBtn()
{
	if(m_bFullScreen)
	{
		CRect rcList, rcListReport; 
		m_List.GetWindowRect(rcList);
		m_stcDraw.GetWindowRect(rcListReport);
		ScreenToClient(rcList);
		ScreenToClient(rcListReport);

		rcListReport.left = rcList.right + 3;
		m_stcDraw.MoveWindow(rcListReport);	

		m_List.ShowWindow(TRUE);
		MoveControl();
	}
	else
	{
		CRect rcList, rcListReport;
		m_List.GetWindowRect(rcList);
		m_stcDraw.GetWindowRect(rcListReport);
		ScreenToClient(rcList);
		ScreenToClient(rcListReport);

		rcListReport.left = rcList.left;
		m_stcDraw.MoveWindow(rcListReport);	

		m_List.ShowWindow(FALSE);		
		MoveControl();
	}

	m_bFullScreen = !m_bFullScreen;
	
}

void CReportForm24::OnEnSetfocusSearchEdit()
{
	OpenSearchDlg();
}

BOOL CReportForm24::CheckCharValid(CString sData)
{
	CStringW sDataW(sData);
	CStringW sCharW(sDataW.Right(1));

	//if( sCharW >= (CStringW("ㄱ") ) && sCharW <= CStringW("ㅎ") ) return FALSE;
	if( sCharW >= (CStringW("ㄱ") ) && sCharW <= CStringW("힇") )
	{
		if(sCharW >= (CStringW("가") ) && sCharW <= CStringW("힇")) 
			return TRUE;
		else 	
			return FALSE;
	}

	return TRUE;
}

void CReportForm24::OnLButtonDown(UINT nFlags, CPoint point)
{

	CMyFormView::OnLButtonDown(nFlags, point);
}

BOOL CReportForm24::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == m_edtSearch.GetSafeHwnd())
	{
		OpenSearchDlg();
		return FALSE;
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}


void CReportForm24::GetSearchDay(long &nCount)
{
	CString strStartMonth;
	CString strEndMonth; 

	m_pGroupSearchDlg->m_cmbNotReport.GetLBText(m_pGroupSearchDlg->m_cmbNotReport.GetCurSel(), strStartMonth);
	m_pGroupSearchDlg->m_cmbNotReport2.GetLBText(m_pGroupSearchDlg->m_cmbNotReport2.GetCurSel(), strEndMonth);

	char buffer[20];
	strStartMonth.Replace("-", "");
	strEndMonth.Replace("-", ""); 

	if(strStartMonth == "검색안함")
		return;

	if((strEndMonth == "검색안함") || (strStartMonth == strEndMonth))
	{
		m_strNotIncomeMonth[0] = strStartMonth;
		nCount = 1;
		return;
	}

	COleDateTime dtDate(atoi(strEndMonth.Left(4)), atoi(strEndMonth.Right(2)), 15, 0, 0, 0);

	while(1)
	{
		if(dtDate.GetMonth() < 10)
			m_strNotIncomeMonth[nCount] = (CString)itoa(dtDate.GetYear(), buffer, 10) + "0" + (CString)itoa(dtDate.GetMonth(), buffer, 10);
		else
			m_strNotIncomeMonth[nCount] = (CString)itoa(dtDate.GetYear(), buffer, 10) + (CString)itoa(dtDate.GetMonth(), buffer, 10);

		dtDate = dtDate - COleDateTimeSpan(30, 0, 0, 0);

		if(m_strNotIncomeMonth[nCount] == strStartMonth)
			break;

		nCount++;	
	}

	nCount++;
}

void CReportForm24::DeleteAllList()
{
	for(int i=0; i<MAX_TAB_COUNT; i++)
	{
		CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(i); 
		CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

		pView->m_lstReport.GetRecords()->RemoveAll();
		pView->m_lstReport.Populate();
	}
}

void CReportForm24::SetData(CString sGNo)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(0);
	CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

	CMkRecordset pRs(m_pMkDb);
	pView->GetData(sGNo, pRs);
	
    for(int i=0; i<MAX_TAB_COUNT; i++)
	{
		CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(i);
		CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

		pView->GetDataReal(&pRs);
		pView->Invalidate(TRUE);
	}    	

	UpdateCount();
}
void CReportForm24::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 

	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CGroupReportView *pView =  (CGroupReportView*)FromHandle(pItem->GetHandle());

	pItem->SetColor(RGB(255, 0, 0));
	COLORREF clr = pItem->GetColor();
 
	CRect rc,rcRest; 
	m_stcLine.GetWindowRect(rc);
	ScreenToClient(rc);

	CXTPPenDC pen(dc, RGB(0, 0, 255));
	CXTPFontDC font1(&dc, m_FontManager.GetFont("맑은 고딕", 15, FW_BOLD));
	dc.SetBkMode(TRANSPARENT);

	CString sItem = ""; 
	sItem.Format("미수금 %s원,  수금액 %s원,  현금 %s원,  신용 %s원", 
		LF->GetMyNumberFormat(m_nUnBillCollection), LF->GetMyNumberFormat(m_nBillCollection),
		LF->GetMyNumberFormat(m_nCashCharge), LF->GetMyNumberFormat(m_nCreditCharge));

	dc.DrawText(sItem, rc, DT_RIGHT); 
}
