
#include "stdafx.h"
#include "MoveOrderPaintManager.h"

CMoveOrderPaintManager::CMoveOrderPaintManager(void)
{
}

CMoveOrderPaintManager::~CMoveOrderPaintManager(void)
{
}

int CMoveOrderPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	if(pRow)
		return 42;
	else
		return 0;
}	

void CMoveOrderPaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, 
									  XTP_GRIDRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CBranchStateRecordItem *pRecordItem = (CBranchStateRecordItem*)pRecord->GetItem(nCol);

	CBranchInfo *pBi = pRecordItem->pBi;

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

}
