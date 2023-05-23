
#include "stdafx.h"
#include "resource.h"
#include "AllocateTRSReportPaintManager.h"
#include "AllocateBoardTRSSetDlg.h"


CImageList CAllocateTRSReportPaintManager::m_imgList;

static BOOL m_bFirstTime = TRUE;
static CImageList m_imgList;


CAllocateTRSReportPaintManager::CAllocateTRSReportPaintManager(void)
{
	if(m_bFirstTime) {
		m_bFirstTime = FALSE;

		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_LIST);
		m_imgList.Create(16, 18, ILC_COLOR32 | ILC_MASK, 1, 1); 
		m_imgList.Add(&bitmap,RGB(0, 255, 255));
	}

	m_nDisplayCount = DISPLAY_COUNT2;
	m_nOrderTimeType = 0;
	m_nOrderState = 0;
	m_bShowPhoneAlways = FALSE;
	m_crPenalty[0] = STATE_COLOR_PENALTY;
	m_crPenalty[1] = STATE_COLOR_PENALTY;
	m_crPenalty[2] = STATE_COLOR_PENALTY;
}

CAllocateTRSReportPaintManager::~CAllocateTRSReportPaintManager(void)
{
	ALLOCATE_RIDER_VECTOR2::iterator it;

	for(it = m_vecRider.begin(); it != m_vecRider.end(); it++)
	{
		ALLOCATE_BOARD_RIDER_INFO2 *rider = *it;
		delete rider;
	}
}


int CAllocateTRSReportPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	return m_nRowHeight + ROW_HEIGHT * m_nDisplayCount + 19 + 51;
/*
	if(!pRow)
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + ROW_HEIGHT * m_nDisplayCount + 22;
	}

	if (!pRow->IsGroupRow())
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + ROW_HEIGHT * m_nDisplayCount + 22;
	}

	if (m_bShadeGroupHeadings)
		return m_nRowHeight + 6 + ROW_HEIGHT * m_nDisplayCount + 22;

	return m_nRowHeight + 19 + 36 + ROW_HEIGHT * m_nDisplayCount + 22;
*/
}

void CAllocateTRSReportPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
											XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;
	CFont *pOldFont;
	CPen pen, pen2;
	COleDateTimeSpan span;
	CString strTemp;
	CString strPos;
	CString strState;

	ALLOCATE_ORDER_MAP2::iterator it;
	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CMyRecordItem2 *pRecordItem = (CMyRecordItem2*)pRecord->GetItem(nCol);

	if(!pRecordItem) return;

	ALLOCATE_BOARD_RIDER_INFO2 *pRider = pRecordItem->pAllocRiderInfo;

	if(!pRider) return;

	COLORREF crTop, crSecondTop, crBack;
	GetRiderStateColor(pRider, crTop, crSecondTop, crBack);

	long cy =  rc.top + 19;
	pDC->FillSolidRect(rc,RGB(255, 255, 255));
	pDC->Draw3dRect(rc, RGB(200, 200, 200), RGB(100, 100, 100));
	pDC->FillSolidRect(CRect(rc.left + 1, rc.top + 1, rc.right-1, cy), crTop);
	pDC->FillSolidRect(CRect(rc.left + 1, rc.bottom - 17, rc.right-1, rc.bottom - 1), crSecondTop);
	pDC->FillSolidRect(CRect(rc.left + 1, cy, rc.right-1, cy + 50), crBack);

	pOldFont = (CFont*)pDC->SelectObject(m_FontManager.GetFont("돋움", 13, FW_BOLD));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->DrawText(strText, CRect(rc.left + 2, rc.top, rc.right, cy), 
			DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(m_FontManager.GetFont("돋움", 13, FW_NORMAL));
	pDC->SetTextColor(RGB(0, 0, 0));


	if(pRider->bOfficeLine)
	{
		pDC->DrawText("그룹관제ID", CRect(rc.left + 2, cy + 17, rc.right, cy + 32), 
			DT_LEFT | DT_VCENTER | DT_SINGLELINE);			

		if(pRider->dtLastAck > COleDateTime::GetCurrentTime() - COleDateTimeSpan(1, 0, 0, 0))
		{
			strTemp.Format("(현)%s", pRider->dtLastAck.Format("%H:%M:%S"));
			pDC->DrawText(strTemp, CRect(rc.left, cy + 33, rc.right - 2, cy + 48), 
				DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

//		pDC->DrawText(pRider->strWaitOrder, 
//				CRect(rc.left, cy + 53, rc.right - 2, cy + 53 + 3 * ROW_HEIGHT), DT_LEFT);
		return;
	}

	if(pRider->nAttendType == 1)
		strState = "(출근)";
	else if(pRider->nAttendType == 2)
		strState = "(퇴근)";
	else 
		strState = "(출근전)";

	if(pRider->bGpsPos)
		strState += "(GPS접속중)";
	else if(pRider->bConnRider)
		strState += "(접속중)";

	if(pRider->nWorkState == 1)
		strState += "(업무중지)";

	if(pRider->nAllocateLimitMin > 0)
	{
		if(pRider->nPenaltyLevel > 0)
			strState.Format("%d차)배차제한 %d분남음", pRider->nPenaltyLevel, pRider->nAllocateLimitMin);
		else
			strState.Format("배차제한 %d분남음", pRider->nAllocateLimitMin);
	}
	else if(pRider->nPenaltyLevel > 0)
	{
		CString strPenaltyLevel;
        strPenaltyLevel.Format("(페널티%d차)", pRider->nPenaltyLevel);
		strState += strPenaltyLevel;
	}

	pDC->DrawText(strState, CRect(rc.left + 2, cy + 2, rc.right, cy + 16), 
		DT_LEFT | DT_VCENTER | DT_SINGLELINE);


	if(pRider->strCurPosName.GetLength() > 0)
	{
		span = COleDateTime::GetCurrentTime() - pRider->dtPos;
		if(span.GetTotalMinutes() <= 3)
			strPos = pRider->strCurPosName;
		else
			strPos.Format("+%d %s", (long)span.GetTotalMinutes(), pRider->strCurPosName);

		pDC->DrawText(strPos, CRect(rc.left + 2, cy + 17, rc.right, cy + 32), 
			DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}


	if(pRider->nAttendType == 1)
		strTemp.Format("(출)%s", pRider->dtAttend.Format("%H:%M:%S"));
	else if(pRider->nAttendType == 2)
		strTemp.Format("(퇴)%s", pRider->dtLeave.Format("%H:%M:%S"));

	pDC->DrawText(strTemp, CRect(rc.left + 2, cy + 33, rc.right, cy + 48), 
		DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	if(pRider->dtLastAck > COleDateTime::GetCurrentTime() - COleDateTimeSpan(1, 0, 0, 0))
	{
		strTemp.Format("(현)%s", pRider->dtLastAck.Format("%H:%M:%S"));
		pDC->DrawText(strTemp, CRect(rc.left, cy + 33, rc.right - 2, cy + 48), 
			DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	}


	pen2.CreatePen(PS_SOLID, 1, RGB(255, 50, 255)); 

	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	long nDrawRow = 0;
	int x = rc.left;
	long nAllocCount = 0;
	long nFinishCount = 0;
	long nTotalCount = 0;
	long nTotalCharge = 0;

	it = m_mapOrder.find(std::make_pair(pRecordItem->pAllocRiderInfo->nCompany, 
		pRecordItem->pAllocRiderInfo->nRNo));

	while(it != m_mapOrder.end())
	{
		if((*it).second.nCompany != pRecordItem->pAllocRiderInfo->nCompany ||
			(*it).second.nRNo != pRecordItem->pAllocRiderInfo->nRNo)
			break;

		if((*it).second.nState < 35)
		{
			nAllocCount++;
		}
		else if((*it).second.nState == 35)
		{
			nFinishCount++;
		}

		nTotalCharge += (*it).second.nCharge;

		it++;
	}

	nTotalCount = nAllocCount + nFinishCount;

	it = m_mapOrder.find(std::make_pair(pRecordItem->pAllocRiderInfo->nCompany, 
				pRecordItem->pAllocRiderInfo->nRNo));

	long nCount = 0;

	while(it != m_mapOrder.end()) 
	{
		if((*it).second.nCompany != pRecordItem->pAllocRiderInfo->nCompany ||
			(*it).second.nRNo != pRecordItem->pAllocRiderInfo->nRNo)
			break;

		if(m_nOrderState == 1 && (*it).second.nState == 35 ||
			m_nOrderState == 2 && (*it).second.nState != 35)
		{
			it++;
			continue;
		}

		nCount++;
		
		switch(m_nOrderState)
		{
		case 1:
			if(nCount > m_nDisplayCount)
			{
				it++;
				continue;
			}
			break;

		case 2:
			if(nCount > m_nDisplayCount)
			{
				it++;
				continue;
			}
			break;

		default:
			if(nCount > m_nDisplayCount)
			{
				it++;
				continue;
			}
			break;
		}



		ALLOCATE_ORDER_INFO2 &order = (*it).second;
		int y = cy + 53 + nDrawRow++ * ROW_HEIGHT;

		pDC->SetTextColor(RGB(0, 0, 0));

		if(order.dtTime.GetStatus() == COleDateTime::valid)
		{
			span = dtTime - order.dtTime;
			if(span.GetTotalSeconds() <= 60) {
				//pDC->SelectObject(&pen);
				pDC->FillSolidRect(CRect(x + 20, y - 2, x + 135, y + 13), RGB(196, 225, 255));
			}
		}

		m_imgList.Draw(pDC, LF->GetImageNumber(order.nState), CPoint(x + 2, y - 4), ILD_NORMAL);
		pDC->TextOut(x + 22, y, order.strStart.Left(6));
		pDC->TextOut(x + 62, y, order.strDest.Left(6));

		pDC->SetTextColor(RGB(255, 0, 0));

		if(m_nOrderTimeType == 0 || order.nState == 35)
		{
			pDC->TextOut(x + 102, y, order.dtTime.Format("%H:%M"));
		}
		else
		{
			if(order.dtTime.GetStatus() == COleDateTime::valid)
			{
				long nMinute = max(span.GetTotalMinutes(), 0);
				strTemp.Format("+%d분", nMinute);
				pDC->TextOut(x + 102, y, strTemp);
			}
		}


		if(order.nWayType == 1) {
			pDC->SelectObject(&pen2);
			pDC->MoveTo(x + 22, y + 11);
			pDC->LineTo(x + 97, y + 11);
		}

		it++;
	}


	CString strTotal, strPayInfo;

	if(nTotalCount > 0) {
		strPayInfo.Format("%d건 / %s원", 
			nAllocCount + 
			nFinishCount, 
			LF->GetMyNumberFormat(nTotalCharge));
	}

	pDC->SetTextColor(RGB(41, 41, 214));
	pDC->TextOut(x + 4, rc.bottom - 14, strPayInfo);
}


void CAllocateTRSReportPaintManager::DrawTextLine(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
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


int CAllocateTRSReportPaintManager::DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign)
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

int CAllocateTRSReportPaintManager::DrawLink(int* pnCurrDrawPos, XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
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

bool compare_greator_rider_no(ALLOCATE_BOARD_RIDER_INFO2* elem1, ALLOCATE_BOARD_RIDER_INFO2* elem2)
{
	bool bComp1 = elem1->nCompany < elem2->nCompany;
	bool bSame1 = elem1->nCompany == elem2->nCompany;
	bool bComp2 = elem1->nRNo < elem2->nRNo;

	return bComp1 || (bSame1 && bComp2);
}

bool compare_last_ack(ALLOCATE_BOARD_RIDER_INFO2* elem1, ALLOCATE_BOARD_RIDER_INFO2* elem2)
{
	bool bComp1 = elem1->dtLastAck > elem2->dtLastAck;
	bool bSame1 = elem1->dtLastAck == elem2->dtLastAck;
	bool bComp2 = elem1->dtAttend < elem2->dtAttend;
	bool bSame2 = elem1->dtAttend == elem2->dtAttend;

	return bComp1 || (bSame1 && bComp2) || (bSame1 && bSame2 && compare_greator_rider_no(elem1, elem2));
}

void CAllocateTRSReportPaintManager::ResortRider(long nType) 
{
	std::sort(m_vecRider.begin(), m_vecRider.end(), compare_last_ack);
}

void CAllocateTRSReportPaintManager::GetRiderStateColor(ALLOCATE_BOARD_RIDER_INFO2 *pRider, 
			COLORREF &crTop, COLORREF &crSecondTop, COLORREF &crBack)
{
	enum { CRT_GREEN = 0, CTR_BLUE = 1, CTR_RED = 2, CTR_LIGHT_GREEN = 3};

	COLORREF crTopA[] = {RGB(0, 200, 0), RGB(0, 0, 200), RGB(200, 0, 0), RGB(200, 200, 0)};
	COLORREF crSecondTopA[] = {RGB(150, 255, 150), RGB(150, 150, 255), RGB(255, 150, 150), RGB(230, 230, 150)};
	COLORREF crBackA[] = {RGB(246, 253, 231), RGB(246, 231, 253), RGB(253, 246, 231), RGB(245, 255, 245)};
		
	if(pRider->nWorkState == 1 || pRider->nAllocateLimitMin > 0)
	{
		if(pRider->nPenaltyLevel > 0)
		{
			crTop = m_crPenalty[pRider->nPenaltyLevel - 1];
			crSecondTop = m_crPenalty[pRider->nPenaltyLevel - 1];
			crBack = crBackA[CTR_RED];
		}
		else
		{
			crTop = crTopA[CTR_RED];
			crSecondTop = crSecondTopA[CTR_RED];
			crBack = crBackA[CTR_RED];
		}
	}
	else if(pRider->bOfficeLine)
	{
		crTop = crTopA[CTR_BLUE];
		crSecondTop = crSecondTopA[CTR_BLUE];
		crBack = crBackA[CTR_BLUE];
	}
	else if(pRider->nAttendType == 1 && pRider->dtAttend.GetHour() < 22)
	{
		crTop = crTopA[CRT_GREEN];
		crSecondTop = crSecondTopA[CRT_GREEN];
		crBack = crBackA[CRT_GREEN];
	}
	else
	{
		crTop = crTopA[CTR_LIGHT_GREEN];
		crSecondTop = crSecondTopA[CTR_LIGHT_GREEN];
		crBack = crBackA[CTR_LIGHT_GREEN];
	}

}


