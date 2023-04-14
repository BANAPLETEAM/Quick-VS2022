#include "stdafx.h"
#include "Quick.h"
#include "GlobalPaintManager.h"

void CRiderPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
					 XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	CXTPGridRow *pRow = pDrawArgs->pRow;
	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();
	CXTPGridColumn *pColumn = NULL;

	CString sItem = ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn);

	COLORREF TEXTCOLOR = RGB(255, 255, 255);
	COLORREF GROUNDCOLOR = RGB(255, 255, 255);

	CDC *pDC = pDrawArgs->pDC;
	CRect r = pDrawArgs->rcItem;

	if(sItem == "1")
	{
		TEXTCOLOR = RGB(0, 0, 255);
		GROUNDCOLOR = RGB(240, 240, 255);
	}
	else if(sItem == "2")
	{
		TEXTCOLOR = RGB(255, 0, 0);
		GROUNDCOLOR = RGB(255, 240, 240);
	}

	if(nCol == ONE)
	{		
		CFont* pOldFont = pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 14, FW_BOLD));

		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, TEXTCOLOR);
		r.DeflateRect(ONE, ONE, TWO, TWO);
		pDC->FillSolidRect(r.left , r.top , r.right , r.bottom, RGB(255, 255 , 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(TEXTCOLOR);
		pDC->DrawText(pMetrics->strText, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	

		pMetrics->clrBackground = GROUNDCOLOR;
		pDC->SelectObject(pOldFont);
	}
	else if(nCol == TWO)
	{
		CFont* pOldFont = pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 17, FW_NORMAL));
		pDC->SetTextColor(TEXTCOLOR);
		pMetrics->clrForeground = TEXTCOLOR;
		pDC->DrawText(pMetrics->strText, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	

		pDC->SelectObject(pOldFont);
	}
}

int CGroupPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	CGroupReportRecord *pRecord = (CGroupReportRecord*)pRow->GetRecord();

	if(pRecord->m_bSumRecord)
		return m_nRowHeight * 1.2;

	if(pRecord->m_stGroup.nReportRow < 0)
		return m_nRowHeight;

	return m_nRowHeight * (pRecord->m_stGroup.nReportRow + 1);
} 

void CGroupPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{		
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;

	CGroupReportRecord *pRecord = (CGroupReportRecord*)pDrawArgs->pRow->GetRecord();

	if(pRecord == NULL) return;
	GROUP_REPORT st = pRecord->m_stGroup;

	if(pRecord->m_bSumRecord)
	{
		rc.DeflateRect(0, 1, 0, 1); 
		pDC->FillSolidRect(rc, RGB(145, 215, 255));
		pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 17, FW_BOLD));
	}
	else
	{
		pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 15, FW_NORMAL));
	}

	long nHeight = rc.Height() / (st.nReportRow + 1);

	for(int i=0; i<max(st.nReportRow, 0)+1; i++)  
	{
		if(nCol > 2 && nCol != 15 && nCol != 16)
		{ 
			CString strText;

			if(pRecord->m_bHasData)
				strText = RemoveZero(::GetGroupReportText(st, nCol, i, pRecord->m_bSumRecord));
			else
				strText = "";

			CRect rcDraw = rc;

			rcDraw.top = rc.top + (nHeight * i);
			rcDraw.bottom = rcDraw.top + nHeight;
			rcDraw.right = rc.right - 1;

			if(nCol == 4 || nCol == 5 || nCol == 6 || nCol == 7 || nCol == 8 || nCol == 8 || 
				nCol == 10 || nCol == 12 ||  nCol == 14 || nCol == 15 || nCol == 16)
				pDC->DrawText(strText, rcDraw, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
			else 
				pDC->DrawText(strText, rcDraw,  DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}			
		else 
		{
			if(nCol == 15 || nCol == 16) 
			{
				CString strText;
				if(pRecord->m_bHasData)
					strText = RemoveZero(::GetGroupReportText(st, nCol, i, pRecord->m_bSumRecord));
				else
					strText = "";

				pDC->DrawText(strText, rc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);	
			}
			else
				pDC->DrawText(strText, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
	}
} //DrawItemCaption ³¡

int CGroupPaintManager24::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)pRow->GetRecord();

	if(pRecord->m_bSumRecord)
		return m_nRowHeight * 1.2;

	if(pRecord->m_stGroup.nReportRow < 0)
		return m_nRowHeight;

	return m_nRowHeight * (pRecord->m_stGroup.nReportRow + 1);
} 

void CGroupPaintManager24::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{		
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;

	CGroupReportRecord24 *pRecord = (CGroupReportRecord24*)pDrawArgs->pRow->GetRecord();

	if(pRecord == NULL) return;
	GROUP_REPORT st = pRecord->m_stGroup;
	
	if(pRecord->m_bSumRecord)
	{
		rc.DeflateRect(0, 1, 0, 1); 
		pDC->FillSolidRect(rc, RGB(145, 215, 255));
		pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 17, FW_BOLD));
	}
	else
	{
		pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 15, FW_NORMAL));
	}

	long nHeight = rc.Height() / (st.nReportRow + 1);

	for(int i=0; i<max(st.nReportRow, 0)+1; i++)   
	{
		if(nCol > 2 && nCol != 5 && nCol != 8) 
		{ 
			CString strText;

			if(pRecord->m_bHasData) 
				strText = RemoveZero(GetGroupReportText1(st, nCol, i, pRecord->m_bSumRecord));
			else
				strText = "";

			CRect rcDraw = rc;

			rcDraw.top = rc.top + (nHeight * i);
			rcDraw.bottom = rcDraw.top + nHeight;
			rcDraw.right = rc.right - 1;

			if(nCol == 4 || nCol == 5 || nCol == 6 || nCol == 7 || nCol == 8 || nCol == 8 || 
				nCol == 10 || nCol == 12 ||  nCol == 14 || nCol == 15 || nCol == 16)
				pDC->DrawText(strText, rcDraw, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
			else 
			{
				if((nCol == 3) && (st.stData[i].bNeedReReport))// ³¯Â¥ ºÎºÐ¿¡ ÀçÁ¤»ê ÃÊ·Ï»ý
					pDC->SetTextColor(RGB(0, 255, 0)); 
				else
					pDC->SetTextColor(RGB(0, 0, 0)); 			

				pDC->DrawText(strText, rcDraw,  DT_VCENTER | DT_CENTER | DT_SINGLELINE);					
			}

			if(i != max(st.nReportRow, 0)) //¸¶Áö¸·ÁÙ ¾Æ´Ô
			{        
				CPen Pen;        
				Pen.CreatePen(PS_DASH, 1, RGB(132, 132, 132)); 
				CPen *pOldPen = pDC->SelectObject(&Pen);

				pDC->MoveTo(rcDraw.left, rcDraw.bottom - 1);
				pDC->LineTo(rcDraw.right, rcDraw.bottom - 1);

				pDC->SelectObject(pOldPen);
			}
		}			
		else 
		{
			if(nCol == 5 || nCol == 8) 
			{
				CString strText;
				if(pRecord->m_bHasData)
					strText = RemoveZero(GetGroupReportText1(st, nCol, i, pRecord->m_bSumRecord));
				else
					strText = "";

				pDC->DrawText(strText, rc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);	
			}
			else
				pDC->DrawText(strText, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
	}
} //DrawItemCaption ³¡

int CConsignDrawManager2::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	return 20;
} 

void CConsignDrawManager2::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;	

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*)pDrawArgs->pRow->GetRecord();

	CRect rcTitle = rc; 
	rcTitle.top = rc.top + 2; 
	rcTitle.bottom = rcTitle.top + 18;
	rcTitle.left = rc.left + 5;

	rcTitle.top = rc.top + 2; 
	rcTitle.bottom = rcTitle.top + 18;
	rcTitle.left = rc.left + 5;
	pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 16, FW_BOLD));
	pDC->DrawText(strText, rcTitle, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
}

void CEmptyPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{		
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex();

	CRect rc = pDrawArgs->rcItem;
	CDC *pDc = pDrawArgs->pDC;
	char buffer[20];

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CMyTextRecord *pRecordItem = (CMyTextRecord*)pRecord->GetItem(nCol);

	ST_RIDER_STRUCT * pAllocRiderInfo = pRecordItem->pAllocRiderInfo;

	long nRNo = pAllocRiderInfo->nRNo;
	CString sLocation = pAllocRiderInfo->strLastLocation;
	CString sRNo = (CString)itoa(nRNo, buffer, 10);

	COLORREF rgb;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

	CXTPFontDC font(pDc, &pDrawArgs->pControl->GetPaintManager()->m_fontText);

	if(pAllocRiderInfo->nCarType <= 1)
		rgb = RGB(150, 255, 150);
	else
		rgb = RGB(150, 150, 255);

	CBrush brush(rgb);		

	CRect rcRNo = rc; 
	rcRNo.right = rcRNo.left + 40;

	pDc->FillRect(rcRNo, &brush);

	pDc->SelectObject(&pen);
	pDc->DrawText(sRNo, rcRNo, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	CRect rcLocation = rc;
	rcLocation.left = rcRNo.right;

	pDc->DrawText(sLocation, rcLocation, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

int CPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	return m_nRowHeight + 14;
}

void CPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetIndex();
	CString strText = pMetrics->strText;

	if(nCol == 0 || nCol == 1 || (nCol == 2 && strText == "°á ±Ù") || (strText.Find("-") >=0))
	{
		CRect& rcItem = pDrawArgs->rcItem;

		if(pDrawArgs->nTextAlign == DT_LEFT)
			rcItem.DeflateRect(2, 1, 2, 0);
		else
			rcItem.DeflateRect(0, 1, 0, 0);

		if(strText == "°á ±Ù" || (strText.Find("-") >=0) || (nCol == 1))
			pDrawArgs->nTextAlign = DT_CENTER;

		// draw item text
		if(!strText.IsEmpty())
		{
			int nCharCount = 0;
			int nHyperlink = 0;
			DrawTextLine(pDrawArgs, strText, rcItem, DT_WORDBREAK, nCharCount, nHyperlink);
		}
	}
	else
	{
		CXTPGridRow *pRow = pDrawArgs->pRow;
		CRiderRecord *pRecord = (CRiderRecord*)pRow->GetRecord();

		CDC *pDC = pDrawArgs->pDC;
		CString strText = "";//pMetrics->strText;

		if(nCol == 2)
			strText = pRecord->m_strWorkTime;
		else if(nCol == 3)
			strText = pRecord->m_strChargeType;
		else if(nCol == 4)
			strText = pRecord->m_strCreditType;
		else if(nCol == 5)
			strText = pRecord->m_strAllCount;

		int idx = strText.Find("Z", 0);
		CString strCount = strText.Left(idx);
		CString strCharge = strText.Mid(idx + 1);

		CXTPPenDC pen(*pDC, RGB(200, 200, 200));
		CXTPFontDC font(pDC, &pDrawArgs->pControl->GetPaintManager()->m_fontText);


		CRect rc = pDrawArgs->rcItem;
		rc.left += 5;
		rc.top = pDrawArgs->rcItem.top + 1;
		rc.bottom = (pDrawArgs->rcItem.top + pDrawArgs->rcItem.Height() / 2) + 1;

		if(nCol == 2 || nCol == 3 || nCol == 4)
			pDC->DrawText(strCount, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		else
			pDC->DrawText(strCount, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//rc.OffsetRect(0, pDrawArgs->rcItem.Height() / 2 + 1);

		rc.top = rc.bottom + 1;
		rc.bottom = pDrawArgs->rcItem.bottom - 2;

		if(nCol == 2 || nCol == 3 || nCol == 4)
			pDC->DrawText(strCharge, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		else
			pDC->DrawText(strCharge, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		pMetrics->strText = "";			
	}
}

int CReportForm14PaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{		
	CXTPGridColumn *pCol = NULL;
	CString str = pRow->GetRecord()->GetItem(0)->GetCaption(pCol);

	if(str == "ÇÕ°è : ")
		return m_nRowHeight + 2;
	else if(str.Find("ÇÕ°è") >= 0) 
		return m_nRowHeight + 4;
	else
		return m_nRowHeight;
}
