#include "stdafx.h"
#include "Quick.h"
#include ".\ProperChargePaintManager.h"



CProperChargePaintManager::CProperChargePaintManager(void)
{
	m_nHilightCol = 1;
	m_pfntLarge = m_FontManager.GetFont("¸¼Àº °íµñ", 24, FW_BOLD);
	m_pfntNormal = m_FontManager.GetFont("¸¼Àº °íµñ", 20, FW_BOLD);
	m_pfntSmall = m_FontManager.GetFont("¸¼Àº °íµñ", 16, FW_BOLD);
}

CProperChargePaintManager::~CProperChargePaintManager(void)
{
}

int CProperChargePaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	return 35;
}

void CProperChargePaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics)
{

	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;	
	BOOL bHilightCol = (m_nHilightCol == nCol);
	CRect rcFill = rc;

	rcFill.DeflateRect(1, 1, 1, 1);

	if(nCol < 1)
	{
		pDC->FillSolidRect(rcFill, RGB(200, 255, 200));	
		pDC->SelectObject(m_pfntNormal);
		pDC->DrawText(strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return;
	}

	if(bHilightCol)
	{
		pDC->FillSolidRect(rcFill, RGB(100, 100, 255));	
	}
	/*
	else if(nCol == 5 || nCol == 6 || nCol == 7)
	{
		pDC->FillSolidRect(rcFill, RGB(255, 230, 230));	
	}
	*/
	else if(nCol == 1)
	{
		pDC->FillSolidRect(rcFill, RGB(220, 255, 255));	
	}
	/*
	else
	{
		if((m_nCarType == 0 || m_nCarType == 1) && nCol == 2)
			pDC->FillSolidRect(rcFill, RGB(255, 230, 230));	
		else if((m_nCarType == 2 || m_nCarType == 3) && nCol == 3)
			pDC->FillSolidRect(rcFill, RGB(255, 230, 230));	
		else if((m_nCarType == 4) && nCol == 4)
			pDC->FillSolidRect(rcFill, RGB(255, 230, 230));	
		else if((m_nCarType == 5 || m_nCarType == 9) && nCol == 4)
			pDC->FillSolidRect(rcFill, RGB(255, 230, 230));	
	}
	*/


	CProperChargeReportRecord *pRecord = (CProperChargeReportRecord*)pDrawArgs->pRow->GetRecord();
	ST_PROPER_CHARGE *st = pRecord->m_st;
	
	CString strCancel;

	long nTotalCount = 0, nCancelCount = 0;

	if(nCol == 1)
	{
		nTotalCount = st->nTotalCount;
		nCancelCount = st->nCancelCount;
	}
	else if(nCol == 2)
	{
		nTotalCount = st->nTotalCountCarType0;
		nCancelCount = st->nCancelCountCarType0;
	}
	else if(nCol == 3)
	{
		nTotalCount = st->nTotalCountCarType2;
		nCancelCount = st->nCancelCountCarType2;
	}
	else if(nCol == 4)
	{
		nTotalCount = st->nTotalCountCarType4;
		nCancelCount = st->nCancelCountCarType4;
	}
	else if(nCol == 5)
	{
		nTotalCount = st->nTotalCountCarType5;
		nCancelCount = st->nCancelCountCarType5;
	}


	CRect rcLine;
	int nCenterLeft = rc.Width() * 3 / 5 - 4;
	rcLine.SetRect(rc.left + nCenterLeft, rc.top, 
				rc.left + nCenterLeft + 1, rc.bottom);
	pDC->FillSolidRect(rcLine, RGB(200, 200, 200));


	if(nTotalCount == 0)
	{
		pMetrics->strText = "ÀÚ·á¾øÀ½";
	}
	else
	{		
		strCancel.Format("%0.0f%%", 100.0 * nCancelCount / nTotalCount);
		pMetrics->strText.Format("%d(%d)", nTotalCount, nCancelCount);

		CRect rcCount, rcCancel;

		rcCount.SetRect(rc.left + 2, rc.top, rc.left + nCenterLeft - 2, rc.bottom - 4);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(bHilightCol ? RGB(255, 255, 255) : RGB(0, 0, 0));
		pDC->SelectObject(m_pfntLarge);
		pDC->DrawText(LF->GetStringFromLong(nTotalCount), rcCount, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

		rcCount.SetRect(rc.left + nCenterLeft + 2, rc.top+2, rc.right - 2, rc.bottom -4);
		pDC->SelectObject(m_pfntNormal);
		pDC->DrawText(LF->GetStringFromLong(nCancelCount), rcCount, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

		/*
		rcCount.SetRect(rc.left + nCenterLeft + 2, rc.top, rc.right - 2, rc.bottom - 10);
		pDC->SelectObject(m_pfntNormal);
		pDC->DrawText(fc.LF->GetStringFromLong(nCancelCount), rcCount, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

		rcCancel = rc;
		rcCancel.DeflateRect(0, 23, 2, 2);
		pDC->SetTextColor(bHilightCol ? RGB(255, 255, 255) : RGB(255, 50, 50));
		pDC->SelectObject(m_pfntSmall);
		pDC->DrawText(strCancel, rcCancel, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		*/
	}
}


