
#include "stdafx.h"
#include "resource.h"
#include "OPStatePaintManager.h"
#include "RcpPageCTIForm.h"
#include "CallListRecord.h"

COPStatePaintManager::COPStatePaintManager(void)
{
	m_bShowLastPhoneNumber = FALSE;
 	m_pfntNormal = m_FontManager.GetFont("¸¼Àº °íµñ", 17, FW_BOLD);
	m_pfntSmall = m_FontManager.GetFont("¸¼Àº °íµñ", 13, FW_BOLD);
}

COPStatePaintManager::~COPStatePaintManager(void)
{
	OP_STATE_MAP::iterator it;
	for(it = m_mapOPState.begin(); it != m_mapOPState.end(); it++)
	{
		if(it->second)
			delete it->second;
	}
}

#define ROW_OFFSET 17

int COPStatePaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	if(!pRow)
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + ROW_OFFSET;
	}

	if (!pRow->IsGroupRow())
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + ROW_OFFSET;
	}

	if (m_bShadeGroupHeadings)
		return m_nRowHeight + 6 + ROW_OFFSET;

	return m_nRowHeight + 16 + ROW_OFFSET;
}

void COPStatePaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, 
											XTP_GRIDRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;
	OP_STATE_MAP::iterator it;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	COPStateRecordItem *pRecordItem = (COPStateRecordItem*)pRecord->GetItem(nCol);

	CFont *pfntOld = pDC->SelectObject(m_pfntNormal);
	LF->FillGradient(pDC, RGB(200, 200, 255), rc, 40);
	rc.DeflateRect(1, 1, 1, 1);

	CRect rcTopText = rc;
	rcTopText.bottom = rc.top + 18;
	CRect rcBottomText = rc;
	rcBottomText.top = rcTopText.bottom + 1;
	rcBottomText.left += 2;
	rcBottomText.right -= 2;
	CRect rcTopLeftText = rcTopText;
	rcTopLeftText.right -= 35;
	CRect rcTopRightText = rcTopText;
	rcTopRightText.left = rcTopLeftText.right + 1;

	if(pRecordItem->pOPState)
	{
		if(pRecordItem->pOPState->nState == PH_ANSWER)
			LF->FillGradient(pDC, RGB(220, 255, 220), rc, 40);
		else if(pRecordItem->pOPState->nState == PH_RING ||
			pRecordItem->pOPState->nState == PH_ARS_ANSWER)
			LF->FillGradient(pDC, RGB(255, 255, 200), rc, 40);
		else if(pRecordItem->pOPState->nState == PH_OUT_BOUND_CALL)
			LF->FillGradient(pDC, RGB(200, 200, 255), rc, 40);
		else 
			pDC->FillSolidRect(rc, RGB(255, 255, 255));	

		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->DrawText((pRecordItem->pOPState->strOperator.GetLength() > 1) ? 
			pRecordItem->pOPState->strOperator : 
			pRecordItem->pOPState->strKeyPhoneID, rcTopLeftText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		pDC->SelectObject(m_pfntSmall);
		pDC->SetTextColor(RGB(50, 50, 50));
		pDC->DrawText((pRecordItem->pOPState->nState == PH_ANSWER || 
					pRecordItem->pOPState->nState == PH_OUT_BOUND_CALL) ? 
			CCallListRecord::GetMyElapsedTimeFormat(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime()) :
			CCallListRecord::GetMyElapsedTimeFormat(COleDateTime::GetCurrentTime(), pRecordItem->pOPState->dtLastAnswer, TRUE),
			rcTopRightText, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

		pDC->SetTextColor(RGB(50, 50, 80));

		if(pRecordItem->pOPState->strCurPhone.GetLength() > 3)
		{
			CString strCurPhone = pRecordItem->pOPState->strCurPhone;
			CString strCustomer;

			if(pRecordItem->pOPState->strCustomer.GetLength() > 1)
			{
				strCustomer = pRecordItem->pOPState->strCustomer;
			}
			else
			{
				strCustomer = CRcpPageCTIForm::GetPhoneCustomer(strCurPhone);

				if(strCustomer.GetLength() < 2)
				{
					if(m_bShowLastPhoneNumber)
						strCustomer = LF->GetDashPhoneNumber(strCurPhone);
					else
						strCustomer = strCurPhone.Left(strCurPhone.GetLength() - 2) + "**";
				}
			}

			if(strCustomer.Find("PHONE") >= 0)
				strCustomer = "";

			pDC->DrawText(strCustomer, rcBottomText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
	}
	else
	{
		pDC->FillSolidRect(rc, RGB(255, 255, 255));	
		pDC->DrawText("-", rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	pDC->SelectObject(pfntOld);
}


void COPStatePaintManager::DrawTextLine(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
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


int COPStatePaintManager::DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign)
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
			const TCHAR seps[]   = _T(" \t\n");
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

int COPStatePaintManager::DrawLink(int* pnCurrDrawPos, XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
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

