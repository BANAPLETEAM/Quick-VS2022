
#include "stdafx.h"
#include "resource.h"
#include "MyReportPaintManager.h"



CMyReportPaintManager::CMyReportPaintManager(void)
{
	m_bApplyHeight = FALSE;
	m_nHeight = 15;
}

CMyReportPaintManager::~CMyReportPaintManager(void)
{
}

void CMyReportPaintManager::SetRowHeight(BOOL bApplyHeight, long nHeight)
{
	m_bApplyHeight = bApplyHeight;
	m_nHeight = nHeight;
}

void CMyReportPaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics)
{
	CString strText = pMetrics->strText;

	CRect& rcItem = pDrawArgs->rcItem;

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
}



void CMyReportPaintManager::DrawTextLine(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
										 CRect rcItem, int nFlag, int& nCharCounter, int& nHyperlikCounter)
{
	CDC* pDC = pDrawArgs->pDC;
	CXTPGridRecordItem* pItem = pDrawArgs->pItem;
	UINT nAlingFlag = 0;
	int nHyperlink = nHyperlikCounter; // Hyperlink index
	int nCharCount = nCharCounter; // Number of actually printed chars
	CXTPGridHyperlink* pHl = NULL;
	int nHyperlinks = pItem->GetHyperlinksCount();

	int nCurrStrPos = nCharCount;
	CRect rcText;
	rcText.CopyRect(&rcItem);

	if (pDrawArgs->pRow->IsSelected())
		nHyperlinks = 0;

	if (nHyperlinks == 0 && nFlag == DT_END_ELLIPSIS)
	{
		pDC->DrawText(strText, rcText, pDrawArgs->nTextAlign|DT_END_ELLIPSIS|DT_NOPREFIX|DT_VCENTER|DT_SINGLELINE);
		return;
	}


	// calculate rect for draving text for text alignment feature
	if (nFlag == DT_END_ELLIPSIS)
	{
		pDC->DrawText(strText, rcText, DT_CALCRECT|DT_NOPREFIX|DT_VCENTER|DT_SINGLELINE);
		if (rcText.Width() < rcItem.Width())
			switch (pDrawArgs->nTextAlign)
		{
			case DT_RIGHT :
				rcText.left = rcItem.right - rcText.Width();
				break;
			case DT_CENTER :
				rcText.left = rcItem.left + (rcItem.Width() - rcText.Width())/2;
				break;
		} // swith

		rcText.right = rcItem.right;
	}

	int nCurrDrawPos = rcText.left;

	while (strText.GetLength() > nCurrStrPos && nCurrDrawPos < rcText.right)
	{
		CString strOut;
		if (nHyperlinks > nHyperlink)
		{
			pHl = pItem->GetHyperlinkAt(nHyperlink);
			strOut = strText.Mid(nCurrStrPos, pHl->m_nHyperTextBegin - nCurrStrPos);
			if (strOut.GetLength() > 0) // print str
			{
				nCharCount = DrawString(&nCurrDrawPos, pDC, strOut, rcText, nFlag, pDrawArgs->nTextAlign);
				rcText.left = nCurrDrawPos > rcText.right ? rcText.right : nCurrDrawPos;

				// if previous string was cut - stop draw
				if (nCharCount < strOut.GetLength() )
				{
					nCharCount += nCurrStrPos;
					break;
				}
			}

			// print link
			nCharCount = DrawLink(&nCurrDrawPos, pDrawArgs, pHl, strText, rcText, nFlag);
			rcText.left = nCurrDrawPos > rcText.right ? rcText.right : nCurrDrawPos;

			// update current position in string
			nCurrStrPos = pHl->m_nHyperTextBegin + pHl->m_nHyperTextLen;
			nHyperlink++;

			// if previous string was cut - stop draw
			if (nCharCount < (pHl->m_nHyperTextLen))
			{
				nCharCount += nCurrStrPos;
				break;
			}
		}
		else
		{

			// print whole string without links or tail of string
			strOut = strText.Mid(nCurrStrPos, strText.GetLength() - nCurrStrPos);
			nCharCount = DrawString(&nCurrDrawPos, pDC, strOut, rcText, nFlag, pDrawArgs->nTextAlign);
			nCharCount += nCurrStrPos;
			break; // all was drawn!
		}
	}

	pDC->SetTextAlign(nAlingFlag);
	nCharCounter = nCharCount;
}


int CMyReportPaintManager::DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign)
{
	int nCharCount = 0;


	switch (nFormat)
	{
	case DT_END_ELLIPSIS:
		{
			// in this case char count only for identify if string printed partially
			*pnCurrDrawPos += pDC->GetTextExtent(strDraw).cx;
			if(*pnCurrDrawPos >= rcDraw.right)
				nCharCount = - 1;
			else
				nCharCount = strDraw.GetLength();

			pDC->DrawText(strDraw, rcDraw, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX|DT_SINGLELINE); //
			break;
		}
	case DT_WORDBREAK:
		{
			const TCHAR seps[]   = _T("\t\n");
			TCHAR* lpszContext = 0;
			CString strOut = _T("");
			CString strSrc = strDraw;
			TCHAR* szWord = STRTOK_S(strSrc.GetBuffer(strSrc.GetLength()), seps, &lpszContext);
			int nRightStrMargin = pDC->GetTextExtent(szWord).cx;

			if (nRightStrMargin >= rcDraw.Width())
			{
				strOut = szWord;

			} else
			{
				while( szWord != NULL && nRightStrMargin < rcDraw.Width())
				{
					strOut = strOut + szWord + _T(" ");
					szWord = STRTOK_S( NULL, seps, &lpszContext );
					nRightStrMargin = pDC->GetTextExtent(strOut + szWord).cx;
				}
			}

			nCharCount = strOut.GetLength();
			*pnCurrDrawPos += pDC->GetTextExtent(strOut).cx;
			pDC->DrawText(strOut, rcDraw, nAlign|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
			break;
		}
	} // switch

	return nCharCount;
}

int CMyReportPaintManager::DrawLink(int* pnCurrDrawPos, XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
									CString strText, CRect rcLink, int nFlag)
{
	CDC* pDC = pDrawArgs->pDC;
	CString strOut = strText.Mid(pHyperlink->m_nHyperTextBegin, pHyperlink->m_nHyperTextLen);

	COLORREF clrPrev = pDC->SetTextColor(pDrawArgs->pControl->GetPaintManager()->m_pHyperlinkStyle->GetColor());

	TEXTMETRIC textMetrics;
	pDC->GetTextMetrics(&textMetrics);
	int nCharCount = 0;
	//!pHyperlink->m_rcHyperSpot.left = pDC->GetCurrentPosition().x; // update hyperlink left bound before drawing
	pHyperlink->m_rcHyperSpot.left = *pnCurrDrawPos;
	nCharCount = DrawString(pnCurrDrawPos, pDC, strOut, rcLink, nFlag, pDrawArgs->nTextAlign);

	// update hyperlink's spot
	pHyperlink->m_rcHyperSpot.top = rcLink.top;
	//!pHyperlink->m_rcHyperSpot.right = pDC->GetCurrentPosition().x;
	pHyperlink->m_rcHyperSpot.right = *pnCurrDrawPos;
	pHyperlink->m_rcHyperSpot.bottom = rcLink.top + textMetrics.tmHeight;

	pDC->SetTextColor(clrPrev);

	return nCharCount;
}

int CMyReportPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
#define MIN_SIZE_TO_SHOW_ICON 19

	if(pRow && m_bApplyHeight)
		return max(m_nHeight, MIN_SIZE_TO_SHOW_ICON);
	else 
		return max(m_nRowHeight, MIN_SIZE_TO_SHOW_ICON) ;
}	
