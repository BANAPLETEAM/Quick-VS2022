
#include "stdafx.h"
#include "resource.h"
#include "MyPaintManager.h"

CMyPaintManager::CMyPaintManager(void)
{
}

CMyPaintManager::~CMyPaintManager(void)
{	
}

int CMyPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	if(pRow)
		return 62;
	else 
		return 10;
}	

void CMyPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
									   XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;
	CRect rcDraw = rc;
	char buffer[10];

	pMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CStateRecordItem *pRecordItem = (CStateRecordItem*)pRecord->GetItem(nCol);

	//pMetrics->strText = itoa(pRecordItem->m_nDay, buffer, 10); 
	pDC->FillSolidRect(rcDraw, RGB(0, 0, 0)); 
	rcDraw.DeflateRect(1, 1, 1, 1);  
	pDC->FillSolidRect(rcDraw, RGB(255, 255, 255));  
  
	if(pRecordItem->m_bApply == FALSE) 
	{  
		rcDraw.DeflateRect(12, 12, 12, 12); 
		CPen elPen(PS_SOLID, 7, RGB(255, 0, 0));
		CPen *pOldPen = pDC->SelectObject(&elPen); 
		pDC->Ellipse(rcDraw);
		pDC->SelectObject(pOldPen);
		pDC->SetTextColor(RGB(0, 0, 1));
		pDC->DrawText(pRecordItem->m_dt1.Format("%m-%d"), rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		
	}

	CString sDay = itoa(pRecordItem->m_nDay, buffer, 10); 
 
	rc.right = rc.right - 5;
	rc.top = rc.bottom - 20;

	pDC->SetTextColor(RGB(0, 0, 255));
	pDC->DrawText(sDay, rc, DT_RIGHT | DT_SINGLELINE);
/*

	if(pBi == NULL)
		pMetrics->strText = "";
	else
		pMetrics->strText = pBi->strBranchName;

	COLORREF crBack = RGB(GetRValue(pBi->nRcpColor), GetGValue(pBi->nRcpColor), GetBValue(pBi->nRcpColor));
	COLORREF crText = RGB(GetRValue(pBi->nRcpTextColor), GetGValue(pBi->nRcpTextColor), GetBValue(pBi->nRcpTextColor));

	if(pBi->nRcpColor == pBi->nRcpTextColor)
	{
		crBack = RGB(255, 255, 255);
		crText = RGB(0, 0, 0);
	}

	rc.DeflateRect(1, 1, 1, 1); 
	pDC->FillSolidRect(rc, crText);
	rc.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rc, crBack);
	pDC->SetTextColor(crText);

	pDC->DrawText(pMetrics->strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	*/
}
