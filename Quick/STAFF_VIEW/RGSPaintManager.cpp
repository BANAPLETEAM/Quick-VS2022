
#include "stdafx.h"
#include "resource.h"
#include "RGSPaintManager.h"


#define START_HOUR		9
#define END_HOUR		19

CRGSPaintManager::CRGSPaintManager(void)
{
}

CRGSPaintManager::~CRGSPaintManager(void)
{
}

void CRGSPaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics)
{

	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect &rcItem = pDrawArgs->rcItem;

	if(nCol < 2)
	{
		if(pDrawArgs->nTextAlign == DT_LEFT)
			rcItem.DeflateRect(2, 1, 2, 0);
		else
			rcItem.DeflateRect(0, 1, 0, 0);


		// draw item text
		if(!strText.IsEmpty())
		{
			int nCharCount = 0;
			int nHyperlink = 0;
			DrawTextLine(pDrawArgs, strText, rcItem, DT_WORDBREAK, nCharCount, nHyperlink);
		}
		return;
	}

	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;	

	if(nRow == 0)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);

		for(int i = 0; i < END_HOUR - START_HOUR + 1; i++)
		{
			CRect rc2 = CRect(rc.left + i * 60 - 10, rc.top + 5, rc.left + i * 60 + 10, rc.top + rc.Height());
			strText.Format("%d", START_HOUR + i);
			pDC->DrawText(strText, rc2, DT_BOTTOM | DT_CENTER);
		}
	}
	else
	{
		CRGSReportRecord *pRecord = (CRGSReportRecord*)pDrawArgs->pRow->GetRecord();
		SIGNAL_MAP::iterator it = m_mapSignal.find(make_pair(pRecord->m_nCompany, pRecord->m_nRNo));
		SIGNAL_VECTOR &vecSignal = it->second;
		
		COleDateTime dtCur = COleDateTime::GetCurrentTime();
		COleDateTime dtStart, dtEnd;
		dtStart.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), START_HOUR, 0, 0);
		dtEnd.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), END_HOUR, 0, 0);

		SIGNAL_VECTOR::iterator itvec;
		for(itvec = vecSignal.begin(); itvec != vecSignal.end(); itvec++)
		{
			if(itvec->dtMin < dtStart || itvec->dtMin > dtEnd)
				continue;

			COleDateTimeSpan span = itvec->dtMin - dtStart;
			long nLineCol = span.GetTotalMinutes();
			long nColorOffset = max(0, 180 - itvec->nCount * 30);
			pDC->FillSolidRect(rc.left + nLineCol, rc.top, 1, rc.Height(), RGB(nColorOffset , 255, nColorOffset));
		}

		for(int i = 1; i < END_HOUR - START_HOUR + 1; i++)
		{
			pDC->FillSolidRect(rc.left + i * 60, rc.top, 1, 4, RGB(0 ,0, 255));

			for(int k = 1; k < 6; k++)
			{
				pDC->FillSolidRect(rc.left + i * 60 + k*10, rc.top, 1, 2, RGB(150 ,150, 255));
			}
		}
	}
}
