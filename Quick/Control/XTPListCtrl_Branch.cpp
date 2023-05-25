// XTPListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "XTPListCtrl_Branch.h"
#include "MyReportPaintManager.h"
#include "BranchSel.h"



// CXTPListCtrl

IMPLEMENT_DYNAMIC(CXTPListCtrl_Branch, CXTPGridControl)

CXTPListCtrl_Branch::CXTPListCtrl_Branch()
{	
	m_bFirst = TRUE;
}

CXTPListCtrl_Branch::~CXTPListCtrl_Branch()
{

}

BEGIN_MESSAGE_MAP(CXTPListCtrl_Branch, CXTPGridControl)
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_CLICK, OnReportItemClick)
END_MESSAGE_MAP()

void CXTPListCtrl_Branch::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

	if(pRecord == NULL)
		return;

	CBranchInfo *pInfo = (CBranchInfo*)GetItemData(pRecord);

	if(pInfo == NULL)
		return;

	if(pDrawArgs->pColumn->GetIndex() > 0)
	{
		if(pInfo->nRcpTextColor == pInfo->nRcpColor)
		{
			pInfo->nRcpColor = RGB(255 -GetRValue(pInfo->nRcpColor), 
				255 - GetGValue(pInfo->nRcpColor), 
				255 - GetBValue(pInfo->nRcpColor));
		}

		pItemMetrics->clrForeground = RGB(GetRValue(pInfo->nRcpTextColor), GetGValue(pInfo->nRcpTextColor), GetBValue(pInfo->nRcpTextColor));
		pItemMetrics->clrBackground = RGB(GetRValue(pInfo->nRcpColor), GetGValue(pInfo->nRcpColor), GetBValue(pInfo->nRcpColor));
	}
}

//void CXTPListCtrl_Branch::SetMapData(MAP_BRANCH *mp)
void CXTPListCtrl_Branch::SetMapData(CBranchSel *cBranch)
{
	m_pcBranch = cBranch;
	m_map = m_pcBranch->GetMapData();

	if(m_bFirst)
		InitColumn();

	RefreshList();
}

void CXTPListCtrl_Branch::InitColumn()
{ 
	if(this->GetSafeHwnd()) 
	{
		ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP); //by mksong 2010-10-14 
		GetReportHeader()->AllowColumnResize(TRUE);
		SetPaintManager(new CMyReportPaintManager());
		GetReportHeader()->SetAutoColumnSizing(FALSE);
		GetReportHeader()->AllowColumnSort(TRUE);
		GetReportHeader()->AllowColumnRemove(FALSE);
		GetPaintManager()->m_strNoItems = "표시할 정보가 없거나, 조건에 해당하는 자료가 존재하지 않음";
		//GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
		SetGridStyle(TRUE, xtpGridSolid);
		SetGridColor(RGB(212, 208, 200));
		AllowEdit(FALSE);

		//CXTPListCtrl::InitControl();    
		CRect rc; GetClientRect(rc); 
		long nWidth = rc.Width();

		CXTPGridColumn* pColumn0 = AddColumn(new CXTPGridColumn(0, _T("ⓝ"), 50, FALSE));
		CXTPGridColumn* pColumn1 = AddColumn(new CXTPGridColumn(1, _T("그룹명"), (nWidth - 50) / 2, FALSE));
		CXTPGridColumn* pColumn2 = AddColumn(new CXTPGridColumn(2, _T("지사명"), (nWidth - 50) / 2, FALSE));
		pColumn0->SetTreeColumn(1); 
			 
		SetTreeIndent(15);
		Populate();
	}
}

void CXTPListCtrl_Branch::RefreshList()
{
	MAP_BRANCH::iterator it; 
	long nItem = 0;

	for(it = m_map->begin(); it != m_map->end(); it++)
	{
		CXTPTaskPanelItem *pItem = it->first;
		ST_BRANCH_INFO st = it->second;

		CXTPGridRecord *pTopRecord = AddRecord(new CXTPGridRecord_Branch(TRUE, pItem->GetCaption(), ""));
		pTopRecord->SetExpanded(TRUE);
		SetItemData(pTopRecord, NULL);

		for(int i=0; i<st.nCount; i++)
		{
			CBranchInfo *pInfo = st.pBiPane[i]->pBi;

			CXTPGridRecord *pSubrecord = pTopRecord->GetChilds()->Add(new CXTPGridRecord_Branch(TRUE, "", pInfo->strBranchName));
			pSubrecord->SetExpanded(TRUE);
			SetItemData(pSubrecord, (DWORD)pInfo);
		}
	}

	Populate();

}

void CXTPListCtrl_Branch::SetItemData(CXTPGridRecord *pRecord, DWORD dwData)
{
	((CXTPGridRecord_Branch*)pRecord)->m_dwData = dwData;
}

DWORD CXTPListCtrl_Branch::GetItemData(CXTPGridRecord *pRecord)
{
	return ((CXTPGridRecord_Branch*)pRecord)->m_dwData;
}

void CXTPListCtrl_Branch::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	CXTPGridControl::OnLButtonUp(nFlags, point);
}

BOOL CXTPListCtrl_Branch::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(OnItemClick())
			return FALSE;
	}

	return CXTPGridControl::PreTranslateMessage(pMsg);
}

BOOL CXTPListCtrl_Branch::OnItemClick()
{
	CPoint pt; 
	::GetCursorPos(&pt);
	ScreenToClient(&pt); 

	CXTPGridRow *pRow = this->HitTest(pt);

	if(pRow)
	{
		CRect rcCol;
		CXTPGridColumn *pCol = NULL;
		pRow->HitTest(pt, &rcCol, &pCol);

		long nRow = pRow->GetIndex();
		long nCol = pCol->GetIndex();

		if(nCol == 0)
		{ 
			//CheckChild(); 
			return TRUE;
		}
		else
		{
			CBranchInfo *pInfo = (CBranchInfo*)GetItemData(pRow->GetRecord());

			if(pInfo == NULL)
				return FALSE;

			m_pcBranch->SetCompany(pInfo->nCompanyCode);
			m_pcBranch->SendChangeBranchInfToParent();
		}
	}

	return FALSE;
}

void CXTPListCtrl_Branch::CheckChild()
{
	CPoint point; 
	::GetCursorPos(&point); 
	ScreenToClient(&point);
	CXTPGridRow *pRow = HitTest(point); 
	if(pRow == NULL) return; 

	CXTPGridSelectedRows *pSelRows = GetSelectedRows();
	CXTPGridRow *pSelRow = NULL; 

	if(pSelRows != NULL)
		pSelRow = pSelRows->GetAt(0);

	CXTPGridRecord_Branch *pRecord = (CXTPGridRecord_Branch*)pRow->GetRecord();

	BOOL bChk = pRecord->IsCheck();

	if(pRow == pSelRow)//체크 눌렸을때의 이벤트
		pRecord->SetCheck(bChk);
	else
		pRecord->SetCheck(!bChk);

	CXTPGridRecords *pChildRecords = pRecord->GetChilds();

	if(pChildRecords)
	{
		for(int i=0; i<pChildRecords->GetCount(); i++)
		{
			CXTPGridRecord_Branch *pChildRecord = (CXTPGridRecord_Branch*)pChildRecords->GetAt(i);
			pChildRecord->SetCheck(!bChk);
		}
	}

	Populate();
}

void CXTPListCtrl_Branch::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nRow = pItemNotify->pRow->GetIndex();
	long nCol = pItemNotify->pColumn->GetIndex();

	if(nCol == 0)
	{
		CXTPGridRecord_Branch *pRecord = (CXTPGridRecord_Branch*)pItemNotify->pRow->GetRecord();

		BOOL bChk = pRecord->IsCheck();

		CXTPGridRecords *pChildRecords = pRecord->GetChilds();
		if(pChildRecords)
		{
			for(int i=0; i < pChildRecords->GetCount(); i++)
			{
				CXTPGridRecord_Branch *pChildRecord = (CXTPGridRecord_Branch*)pChildRecords->GetAt(i);
				pChildRecord->SetCheck(bChk);
			}
		}
	}
	/*else
	{
		CBranchInfo *pInfo = (CBranchInfo*)GetItemData(pItemNotify->pRow->GetRecord());

		if(pInfo == NULL)
			return;

		m_pcBranch->SetCompany(pInfo->nCompanyCode);
		m_pcBranch->SendChangeBranchInfToParent();
	}
	*/
}

long CXTPListCtrl_Branch::GetCheckCount(CStringArray &arry)
{
	long nCount = 0;
	char buffer[10];

	CXTPGridRecords *pRecords = GetRecords(); 

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CXTPGridRecords *pChildRecords = pRecord->GetChilds();

		if(pChildRecords)
		{
			for(int i=0; i<pChildRecords->GetCount(); i++)
			{
				CXTPGridRecord_Branch *pChildRecord = (CXTPGridRecord_Branch*)pChildRecords->GetAt(i);

				if(pChildRecord->IsCheck())
				{
					CBranchInfo *pInfo = (CBranchInfo*)GetItemData(pChildRecord);
					arry.Add(itoa(pInfo->nCompanyCode, buffer, 10));
					nCount++;
				}
			}
		}
	}

	return nCount;
}

void CXTPListCtrl_Branch::SetAllNoCheckRow()
{
	CXTPGridRows *pRows = this->GetRows();
	int nParentCount =pRows->GetCount();
	for(int i=0; i<nParentCount; i++)
	{
		CXTPGridRecord_Branch *pRecord = (CXTPGridRecord_Branch*)pRows->GetAt(i)->GetRecord();
		pRecord->SetCheck(FALSE);

		if(pRecord->GetChilds()->GetCount() > 0 )
		{
			int nChildCount = pRecord->GetChilds()->GetCount();
			for(int j = 0; j < nChildCount; j++)
			{

				CXTPGridRecord_Branch *pChildRecord = (CXTPGridRecord_Branch *)pRecord->GetChilds()->GetAt(j);
				pChildRecord->SetCheck(FALSE);

			}
		}

	}
	RedrawControl();
}