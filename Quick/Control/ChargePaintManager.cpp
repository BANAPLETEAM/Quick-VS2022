#include "StdAfx.h"
#include "ChargePaintManager.h"

CChargePaintManager::CChargePaintManager(void)
{
	m_nFirstRowHeight = 50;
}

CChargePaintManager::~CChargePaintManager(void)
{
}

void CChargePaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, 
											XTP_GRIDRECORDITEM_METRICS* pMetrics)
{
	CString strText = pMetrics->strText;
	CRect& rcItem = pDrawArgs->rcItem;

	if(pDrawArgs->nTextAlign == DT_LEFT)
		rcItem.DeflateRect(2, 1, 2, 0);
	else
		rcItem.DeflateRect(0, 1, 0, 0);

	CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

	int nCharCount = 0;   
	int nHyperlink = 0; 
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex(); 
 
	CDC *dc = pDrawArgs->pDC; 
	CFont *pOldFont = dc->SelectObject(m_FontManager.GetFont("맑은 고딕", 18, FW_NORMAL));

	// draw item text   
	if(!strText.IsEmpty()) 
	{  		 
		if(pRecord->GetIndex() == 0) //헤더컬럼부분
		{  
			CStringW strW(strText);
			CString strTemp;
			long nCount = strW.GetLength();
 
			for(int i=0; i<nCount; i++) 
			{
				strTemp += CString(strW.Mid(i, 1)) + "\n";
			}
		 
			dc->DrawText(strTemp, rcItem, DT_WORDBREAK | DT_CENTER); 
			return;
		} 
		else   
		{
			if(nCol == 0)
				dc->DrawText(strText, rcItem,  DT_SINGLELINE | DT_LEFT | DT_VCENTER); 
			else
				dc->DrawText(strText, rcItem,  DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
				
			//strText = "개\n포";   
			//DrawTextLine(pDrawArgs, strText, rcItem, DT_WORDBREAK, nCharCount, nHyperlink);
		}		
	}

	dc->SelectObject(pOldFont);
}



int CChargePaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	CXTPGridRecord *pRecord = pRow->GetRecord();

	if(pRecord == NULL)
		return m_nRowHeight;

	if(pRecord->GetIndex() == 0)
		return m_nFirstRowHeight;

	return ROW_COL_SIZE;
}	
