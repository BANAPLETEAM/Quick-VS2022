// XTPGridView.cpp : implementation of the CK2ReportView class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// ?998-2005 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MyXTPReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CK2ReportView


IMPLEMENT_DYNCREATE(CK2ReportView, CView)

CK2ReportView::CK2ReportView() 
{

}



CK2ReportView::~CK2ReportView()
{
	
}

BEGIN_MESSAGE_MAP(CK2ReportView, CView)
	//{{AFX_MSG_MAP(CK2ReportView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CK2ReportView drawing

void CK2ReportView::OnDraw(CDC* /*pDC*/)
{
}

void CK2ReportView::OnPaint()
{
	Default();
}

int CK2ReportView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return 0;
	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

/////////////////////////////////////////////////////////////////////////////
// CK2ReportView diagnostics

#ifdef _DEBUG
void CK2ReportView::AssertValid() const
{
	CView::AssertValid();
}

void CK2ReportView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CK2ReportView message handlers

void CK2ReportView::PrintPreview()
{
	CView::OnFilePrintPreview();
}

CDataBox& CK2ReportView::GetDataCtrl() {
	return m_Data;
	//return m_pData;

}

BOOL CK2ReportView::OnEraseBkgnd(CDC* )
{
	return TRUE;
}

void CK2ReportView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_Data.GetSafeHwnd())
	{
		m_Data.MoveWindow(0, 0, cx, cy);
	}
}

int CK2ReportView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	if (!m_Data.Create(WS_CHILD|WS_TABSTOP|WS_VISIBLE|WM_VSCROLL|WS_HSCROLL, CRect(0, 0, 0, 0), this,XTP_ID_REPORT_CONTROL3 ))
	{
		TRACE(_T("Failed to create tab control window\n"));
		return -1;
	}
	
	
	m_Data.Populate();

	
	
	/*m_Data.GetPaintManager()->m_bHideSelection = FALSE;
	
	m_Data.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);*/


	return 0;
}

void CK2ReportView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	m_Data.SetFocus();
}


/////////////////////////////////////////////////////////////////////////////
// CReportSampleView printing

BOOL CK2ReportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK2ReportView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
	
	ASSERT(m_aPageStart.GetSize() == 0);
	m_aPageStart.Add(0);
	ASSERT(m_aPageStart.GetSize() > 0);
	

}

void CK2ReportView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
	
	m_aPageStart.RemoveAll();
}

CXTPGridPaintManager* CK2ReportView::GetPaintManager()
{
	return m_Data.GetPaintManager();
	
}
void CK2ReportView::SetPaintManager(CXTPGridPaintManager *pManager)
{

	m_Data.SetPaintManager(pManager);

}

int CK2ReportView::GetColumnWidth(CXTPGridColumn* pColumnTest, int nTotalWidth)
{
	CXTPGridColumns* pColumns = m_Data.GetColumns();

	int nColumnsWidth = 0;
	CXTPGridColumn* pLastAutoColumn = NULL;

	for (int nColumn = 0; nColumn < pColumns->GetCount(); nColumn ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(nColumn);
		if (!pColumn->IsVisible())
			continue;

		if (pColumn->IsAutoSize())
		{
			pLastAutoColumn = pColumn;
			nColumnsWidth += pColumn->GetWidth();
		}
		else
		{
			nTotalWidth -= pColumn->GetWidth();
		}
	}

	for (int i = 0; i < pColumns->GetCount(); i ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if (!pColumn->IsVisible())
			continue;

		int nWidth = pColumn->GetWidth();

		if (pColumn->IsAutoSize())
		{
			if (pColumn == pLastAutoColumn)
			{
				nWidth = max(nTotalWidth, pColumn->GetMinWidth());
			}
			else
			{
				nColumnsWidth = max(1, nColumnsWidth);

				nWidth =
					max(int(pColumn->GetWidth() * nTotalWidth / nColumnsWidth), pColumn->GetMinWidth());

				nTotalWidth -= nWidth;
				nColumnsWidth -= pColumn->GetWidth();
			}
		}

		if (pColumn == pColumnTest)
			return nWidth;
	}

	return 0;
}

void CK2ReportView::PrintHeader(CDC* pDC, CRect rcHeader)
{
	GetPaintManager()->FillHeaderControl(pDC, rcHeader);

	int x = rcHeader.left;

	CXTPGridColumns* pColumns = m_Data.GetColumns();

	for (int i = 0; i < pColumns->GetCount(); i ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if (!pColumn->IsVisible())
			continue;

		int nWidth = GetColumnWidth(pColumn, rcHeader.Width());  		
		CRect rcItem(x, rcHeader.top, x + nWidth, rcHeader.bottom);

		GetPaintManager()->DrawColumn(pDC, pColumn, m_Data.GetReportHeader(), rcItem);

		x += nWidth;
	}
}

void CK2ReportView::PrintRow(CDC* pDC, CXTPGridRow* pRow, CRect rcRow)
{
	if (pRow->IsGroupRow())
	{
		GetPaintManager()->DrawGroupRow(pDC, (CXTPGridGroupRow*)pRow, rcRow, NULL);
		return;
	}


	XTP_GRIDRECORDITEM_DRAWARGS drawArgs;
	drawArgs.pDC = pDC;
	drawArgs.pControl = &m_Data;
	drawArgs.pRow = pRow;
	int nIndentWidth = m_Data.GetHeaderIndent();
	CXTPGridPaintManager* pPaintManager = GetPaintManager();

	CXTPGridColumns* pColumns = m_Data.GetColumns();
	int nColumnCount = pColumns->GetCount();

	// paint row background
	pPaintManager->FillRow(pDC, pRow, rcRow);

	CRect rcItem(rcRow);
	rcItem.bottom = rcItem.top + pPaintManager->GetRowHeight(pDC, pRow);

	CXTPGridRecord* pRecord = pRow->GetRecord();
	if (pRecord) // if drawing record, not group
	{
		int x = rcRow.left;
		// paint record items
		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			CXTPGridColumn* pColumn = pColumns->GetAt(nColumn);
			if (pColumn && pColumn->IsVisible() && pRow->IsItemsVisible())
			{
				rcItem.left = x;
				
				x = rcItem.right = rcItem.left + GetColumnWidth(pColumn, rcRow.Width()); 
				if (nColumn == 0)
					rcItem.left += nIndentWidth;

				CRect rcGridItem(rcItem);
				rcGridItem.left--;

				CXTPGridRecordItem* pItem = pRecord->GetItem(pColumn);

				if (pItem)
				{

					// draw item
					drawArgs.pColumn = pColumn;
					drawArgs.rcItem = rcItem;
					drawArgs.nTextAlign = pColumn->GetAlignment();
					drawArgs.pItem = pItem;
					// draw item
					pItem->Draw(&drawArgs);
				}

				pPaintManager->DrawGrid(pDC, xtpGridOrientationHorizontal, rcGridItem);
			}
		}

		if (nIndentWidth > 0)
		{
			// draw indent column
			CRect rcIndent(rcRow);
			rcIndent.right = rcRow.left + nIndentWidth;
			pPaintManager->FillIndent(pDC, rcIndent);
		}

		if (pRow->IsPreviewVisible())
		{
			CXTPGridRecordItemPreview* pItem = pRecord->GetItemPreview();
			int nPreviewHeight = pItem->GetPreviewHeight(pDC, pRow, rcRow.Width());

			CRect rcPreviewItem(rcRow);
			rcPreviewItem.DeflateRect(nIndentWidth, rcPreviewItem.Height() - nPreviewHeight, 0, 0);

			drawArgs.rcItem = rcPreviewItem;
			drawArgs.nTextAlign = DT_LEFT;
			drawArgs.pItem = pItem;
			drawArgs.pColumn = NULL;

			drawArgs.pItem->Draw(&drawArgs);
		}
	}

	BOOL bGridVisible = pPaintManager->IsGridVisible(FALSE);

	CRect rcFocus(rcRow.left, rcRow.top, rcRow.right, rcRow.bottom - (bGridVisible? 1: 0));

	if (pRow->GetIndex() < m_Data.GetRows()->GetCount() - 1 && nIndentWidth > 0)
	{
		CXTPGridRow* pNextRow = m_Data.GetRows()->GetAt(pRow->GetIndex() + 1);
		ASSERT(pNextRow);
		rcFocus.left = rcRow.left +  min(nIndentWidth, pPaintManager->m_nTreeIndent * pNextRow->GetTreeDepth());
	}

	pPaintManager->DrawGrid(pDC, xtpGridOrientationHorizontal, rcFocus);
}


int CK2ReportView::PrintRows(CDC* pDC, CRect rcClient, long nIndexStart)
{
	int y = rcClient.top;
	CXTPGridRows* pRows = m_Data.GetRows();

	for (; nIndexStart < pRows->GetCount(); nIndexStart++)
	{
		CXTPGridRow* pRow = pRows->GetAt(nIndexStart);

		int nHeight = pRow->GetHeight(pDC, 0);	//xtp 업데이트 후, 0이 추가되었음
		if (pRow->IsPreviewVisible())
		{
			CXTPGridRecordItemPreview* pItem = pRow->GetRecord()->GetItemPreview();
			nHeight+= pItem->GetPreviewHeight(pDC, pRow, rcClient.Width());
		}

		CRect rcRow(rcClient.left, y, rcClient.right, y + nHeight);

		if (rcRow.bottom > rcClient.bottom)
			break;

		PrintRow(pDC, pRow, rcRow);

		y += rcRow.Height();
	}
	return nIndexStart;
}

void CK2ReportView::PrintFooter(CDC* pDC, CPrintInfo* pInfo, CRect rcFooter)
{
	CFont* pOldFont = pDC->SelectObject(&m_Data.GetPaintManager()->m_fontText);

	CString strPage;
	strPage.Format(_T("%i"), pInfo->m_nCurPage);
	pDC->SetTextColor(0);
	pDC->DrawText(strPage, rcFooter, DT_CENTER|DT_SINGLELINE|DT_NOPREFIX);

	pDC->SelectObject(pOldFont);
}

long CK2ReportView::PrintPage(CDC* pDC, CPrintInfo* pInfo, CRect rcPage, long nIndexStart)
{
	rcPage.DeflateRect(20, 20);

	pDC->Draw3dRect(rcPage, 0, 0);

	int nHeaderHeight = GetPaintManager()->GetHeaderHeight();

	CRect rcHeader(rcPage.left + 1, rcPage.top + 1, rcPage.right - 1, rcPage.top + 1 + nHeaderHeight);

	PrintHeader(pDC, rcHeader);	

	CRect rcRows(rcHeader.left, rcHeader.bottom, rcHeader.right, rcPage.bottom - 1);
	nIndexStart = PrintRows(pDC, rcRows, nIndexStart);
	

	CRect rcFooter(rcPage.left, rcPage.bottom, rcPage.right, rcPage.bottom + 20);
	PrintFooter(pDC, pInfo, rcFooter); 
	


	return nIndexStart;
}

void CK2ReportView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	
	
	UINT nPage = pInfo->m_nCurPage;
	ASSERT(nPage <= (UINT)m_aPageStart.GetSize());
	UINT nIndex = m_aPageStart[nPage-1];

	// print as much as possible in the current page.
	 nIndex = PrintPage(pDC, pInfo, pInfo->m_rectDraw, nIndex );	

	// update pagination information for page just printed
	if (nPage == (UINT)m_aPageStart.GetSize())
	{
		if ((int)nIndex < m_Data.GetRows()->GetCount())
			m_aPageStart.Add(nIndex);
	}
	else
	{
		ASSERT(nPage < (UINT)m_aPageStart.GetSize());
		m_aPageStart[nPage] = nIndex;
	}
	
}

//
//void CK2ReportView::OnActivateView(
//							   BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
//{
//	pActivateView->SetActiveWindow();
//	return;
//	if (SaveFocusControl())
//		return;     // don't call base class when focus is already set
//
//return ;
//	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
//}
//
//void CK2ReportView::OnActivateFrame(UINT nState, CFrameWnd* /*pFrameWnd*/)
//{
//	if (nState == WA_INACTIVE)
//		SaveFocusControl();     // save focus when frame loses activation
//}


BOOL CK2ReportView::SaveFocusControl()
{
	// save focus window if focus is on this window's controls
	HWND hWndFocus = ::GetFocus();
	if (hWndFocus != NULL && ::IsChild(m_hWnd, hWndFocus))
	{
		m_hWndFocus = hWndFocus;
		return TRUE;
	}
	return FALSE;
}

BOOL CK2ReportView::PaginateTo(CDC* pDC, CPrintInfo* pInfo)
// attempts pagination to pInfo->m_nCurPage, TRUE == success
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	CRect rectSave = pInfo->m_rectDraw;
	UINT nPageSave = pInfo->m_nCurPage;
	ASSERT(nPageSave > 1);
	ASSERT(nPageSave >= (UINT)m_aPageStart.GetSize());
	VERIFY(pDC->SaveDC() != 0);
	pDC->IntersectClipRect(0, 0, 0, 0);
	pInfo->m_nCurPage = (UINT)m_aPageStart.GetSize();
	while (pInfo->m_nCurPage < nPageSave)
	{
		ASSERT(pInfo->m_nCurPage == (UINT)m_aPageStart.GetSize());
		OnPrepareDC(pDC, pInfo);
		ASSERT(pInfo->m_bContinuePrinting);
		pInfo->m_rectDraw.SetRect(0, 0,
			pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
		pDC->DPtoLP(&pInfo->m_rectDraw);
		OnPrint(pDC, pInfo);
		if (pInfo->m_nCurPage == (UINT)m_aPageStart.GetSize())
			break;
		++pInfo->m_nCurPage;
	}
	BOOL bResult = pInfo->m_nCurPage == nPageSave;
	pDC->RestoreDC(-1);
	pInfo->m_nCurPage = nPageSave;
	pInfo->m_rectDraw = rectSave;
	ASSERT_VALID(this);
	return bResult;
}

void CK2ReportView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT(pInfo != NULL);  // overriding OnPaint -- never get this.

	if (pInfo->m_nCurPage > (UINT)m_aPageStart.GetSize() &&
		!PaginateTo(pDC, pInfo))
	{
		// can't paginate to that page, thus cannot print it.
		pInfo->m_bContinuePrinting = FALSE;
	}
	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
		pDC->GetDeviceCaps(LOGPIXELSY));

	pDC->SetWindowExt(100, 100);

	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
}

