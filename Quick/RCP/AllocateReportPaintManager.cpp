
#include "stdafx.h"
#include "resource.h"
#include "AllocateReportPaintManager.h"


CImageList CAllocateReportPaintManager::m_imgList;
CImageList CAllocateReportPaintManager::m_imgListCarType;
CImageList CAllocateReportPaintManager::m_imgListTRS;
CBrush CAllocateReportPaintManager::m_WhiteBrush;
CBrush CAllocateReportPaintManager::m_GreenBrush;
CBrush CAllocateReportPaintManager::m_GreenBrush2;
CBrush CAllocateReportPaintManager::m_BlueBrush;

static BOOL m_bFirstTime = TRUE;
static CImageList m_imgList;

long m_nCarShowType = 0;
long m_nOtherRiderShowType = 0;

CAllocateReportPaintManager::CAllocateReportPaintManager(void)
{
	m_pLargeFont = m_FontManager.GetFont("돋움", 13);
	m_pSmallFont = m_FontManager.GetFont("돋움", 11);

	if(m_bFirstTime) {
		m_bFirstTime = FALSE;

		CBitmap bitmap, bitmap2, bitmap3;
		bitmap.LoadBitmap(IDB_LIST);
		m_imgList.Create(16, 18, ILC_COLOR32 | ILC_MASK, 1, 1); 
		m_imgList.Add(&bitmap,RGB(0, 255, 255));

		bitmap2.LoadBitmap(IDB_CAR_TYPE);
		m_imgListCarType.Create(20, 18, ILC_COLOR32 | ILC_MASK, 1, 1);
		m_imgListCarType.Add(&bitmap2, RGB(255, 255, 255));

		bitmap3.LoadBitmap(IDB_TRS);
		m_imgListTRS.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 1);
		m_imgListTRS.Add(&bitmap3, RGB(255, 255, 255));

		
		m_WhiteBrush.CreateSolidBrush(RGB(255, 255, 255));
		m_GreenBrush.CreateSolidBrush(RGB(133, 210, 65));
		m_GreenBrush2.CreateSolidBrush(RGB(246, 253, 231));
		m_BlueBrush.CreateSolidBrush(RGB(196, 225, 255));
	}

	m_nDisplayCount = DISPLAY_COUNT;
	m_nOrderTimeType = 0;
	m_nOrderState = 0;
	m_bShowPhoneAlways = FALSE;
	m_bWideColumn = FALSE;
	m_bShowPosName = FALSE;
	m_bDisplayAttendLeave = FALSE;
	m_bShowProperRiderScore = FALSE;
	m_crDelayRiderBack = RGB(255, 255, 255);
	m_crOtherOrderText = RGB(0, 0, 0);
	m_crOtherOrderBack = RGB(255, 255, 255);
	m_crOtherRiderText = RGB(255, 255, 255);
	m_crOtherRiderBack = RGB(102, 102, 153);
	m_bLinearType = FALSE;
}

CAllocateReportPaintManager::~CAllocateReportPaintManager(void)
{
	ALLOCATE_RIDER_VECTOR::iterator it;

	for(it = m_vecRider.begin(); it != m_vecRider.end(); it++)
	{
		ALLOCATE_BOARD_RIDER_INFO *rider = *it;
		delete rider;
	}
}


int CAllocateReportPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
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

	return m_nRowHeight + 16 + ROW_HEIGHT * m_nDisplayCount + 22;
}

void CAllocateReportPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
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

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CMyRecordItem *pRecordItem = (CMyRecordItem*)pRecord->GetItem(nCol);
	pRecordItem->vecOrderRect.clear();

	//타기사보기
	if(pRecordItem->pAllocRiderInfo->nCompany < 0)	
	{
		rc.DeflateRect(0, 0, 2, 0);
		LF->FillGradient(pDC, RGB(220, 220, 255), rc);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->DrawText(pRecordItem->pAllocRiderInfo->nCompany == AB_MY_RIDER ? "자사기사 보기" : "공유기사 보기", 
					rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return;
	}

	LF->FillGradient(pDC, pRecordItem->pAllocRiderInfo->bDelayRider ? m_crDelayRiderBack : RGB(255, 255, 255), rc);
	pDC->Draw3dRect(rc, RGB(200, 200, 200), RGB(100, 100, 100));

	if(pRecordItem->pAllocRiderInfo->bShareRiderHaveMyOrder)
	{
		LF->FillGradient(pDC, m_crOtherRiderBack ? m_crOtherRiderBack : RGB(102, 102, 153),
					CRect(rc.left + 1, rc.top + 1, rc.right-1, rc.top + 19));
		pDC->SetTextColor(m_crOtherRiderText);
	}
	else
	{
		if(pRecordItem->pAllocRiderInfo->nRiderColor == 0)
		{
			if(pRecordItem->pAllocRiderInfo->nCarType == 0)
				LF->FillGradient(pDC, RGB(133, 210, 65), CRect(rc.left + 1, rc.top + 1, rc.right-1, rc.top + 19));
			else
				LF->FillGradient(pDC, RGB(150, 180, 210), CRect(rc.left + 1, rc.top + 1, rc.right-1, rc.top + 19));
		}
		else
		{
			LF->FillGradient(pDC, pRecordItem->pAllocRiderInfo->nRiderColor, CRect(rc.left + 1, rc.top + 1, rc.right-1, rc.top + 19));
		}

		if(pRecordItem->pAllocRiderInfo->nRiderTextColor == 0)
			pDC->SetTextColor(RGB(255, 255, 255));
		else
		{
			pDC->SetTextColor(pRecordItem->pAllocRiderInfo->nRiderTextColor);
		}
	}

	LF->FillGradient(pDC, RGB(246, 253, 231), CRect(rc.left + 1, rc.bottom - 17, rc.right-1, rc.bottom - 1));

	pOldFont = (CFont*)pDC->SelectObject(m_pLargeFont);
	pDC->SetBkMode(TRANSPARENT);

	
	if(m_bDisplayAttendLeave)
	{
		if(pRecordItem->pAllocRiderInfo->nWorkReportState == 1)
		{
			strText = strText + " (" + pRecordItem->pAllocRiderInfo->dtAttend.Format("%H:%M") + ")";
		}
		else if(pRecordItem->pAllocRiderInfo->nWorkReportState == 2)
		{
			strText = strText + " (퇴" + pRecordItem->pAllocRiderInfo->dtLeave.Format("%H:%M") + ")";
		}
		else if(pRecordItem->pAllocRiderInfo->nWorkReportState == 3)
		{
			strText = strText + " (강퇴" + pRecordItem->pAllocRiderInfo->dtLeave.Format("%H:%M") + ")";
		}
	}

	if(m_bShowProperRiderScore)
	{
		CString strScore;

		if(m_bLinearType)
		{
			strScore.Format("(%0.1fkm)", pRecordItem->pAllocRiderInfo->fOrderDistance);
		}
		else
		{
			strScore.Format("(%d/%d/%d/%d)", pRecordItem->pAllocRiderInfo->nStartDistanceScore, 
				(int)pRecordItem->pAllocRiderInfo->fOrderCountScore,
				pRecordItem->pAllocRiderInfo->nDirectionScore,
				pRecordItem->pAllocRiderInfo->nAngleScore);
		}
		strText += strScore;
	}


	if(pRecordItem->pAllocRiderInfo->nCarType > 1)
	{
		pDC->DrawText(strText, CRect(rc.left + 25, rc.top, rc.right, rc.top + 19), 
				DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		m_imgListCarType.Draw(pDC, pRecordItem->pAllocRiderInfo->nCarType - 1, CPoint(rc.left + 2, rc.top), ILD_NORMAL);
	}
	else
	{
		pDC->DrawText(strText, CRect(rc.left + 2, rc.top, rc.right, rc.top + 19), 
			DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	pDC->SelectObject(m_pSmallFont);
	pen2.CreatePen(PS_SOLID, 1, RGB(255, 50, 255)); 

	ALLOCATE_ORDER_MAP::iterator it;
	COleDateTime dtTime = COleDateTime::GetCurrentTime();
	long nDrawRow = 0;
	int x = rc.left;

	pRecordItem->pAllocRiderInfo->x = rc.left;
	pRecordItem->pAllocRiderInfo->y = rc.top;

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
	long nDIsplayCount = m_nDisplayCount;
	BOOL bEmptyCar = (pRecordItem->pAllocRiderInfo->nPickupCount + pRecordItem->pAllocRiderInfo->nAllocCount) == 0;

	if(m_bShowPosName)
	{
		CString strPos;

		if(pRecordItem->pAllocRiderInfo->dtPos.GetStatus() != COleDateTime::null &&
			(bEmptyCar && pRecordItem->pAllocRiderInfo->dtPos > COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 180, 0) ||
			(!bEmptyCar && pRecordItem->pAllocRiderInfo->dtPos > COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 0, 60, 0))))
		{
			int y = rc.top + nDrawRow++ * ROW_HEIGHT + 21;
			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - pRecordItem->pAllocRiderInfo->dtPos;

			if(span.GetTotalMinutes() <= 3)
				strPos = pRecordItem->pAllocRiderInfo->strCurPosName;
			else
				strPos.Format("+%d %s", (long)span.GetTotalMinutes(), pRecordItem->pAllocRiderInfo->strCurPosName);

			LF->FillGradient(pDC, pRecordItem->pAllocRiderInfo->bDelayRider ? m_crDelayRiderBack : RGB(180, 255, 165),
									CRect(rc.left + 1, y-3, rc.right-1, y + 12));
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->TextOut(x + 2, y, strPos);
			nDIsplayCount--;
		}
	}

	pDC->SetBkMode(TRANSPARENT);

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
			if(nAllocCount > nDIsplayCount &&
				nAllocCount - nDIsplayCount >= nCount)
			{
				it++;
				continue;
			}
			break;

		case 2:
			if(nFinishCount > nDIsplayCount &&
				nFinishCount - nDIsplayCount >= nCount)
			{
				it++;
				continue;
			}
			break;

		default:
			if(nTotalCount > nDIsplayCount &&
				nTotalCount - nDIsplayCount >= nCount)
			{
				it++;
				continue;
			}
			break;
		}

		ORDER_RECT OrderRect;
		ALLOCATE_ORDER_INFO &order = (*it).second;
		int y = rc.top + nDrawRow++ * ROW_HEIGHT + 22;
		OrderRect.rc = CRect(rc.left, y, rc.right, y + ROW_HEIGHT);
		OrderRect.nTNo = it->second.nTNo;
		pRecordItem->vecOrderRect.push_back(OrderRect);

		pDC->SetTextColor(RGB(0, 0, 0));

		if(order.dtTime.GetStatus() == COleDateTime::valid)
		{
			span = dtTime - order.dtTime;
			if(span.GetTotalSeconds() <= 60) 
				LF->FillGradient(pDC, RGB(196, 225, 255), CRect(x + 20, y - 2, x + 135, y + 13));
		}

		if(order.nRunType == RUN_VERY_FAST)
			LF->FillGradient(pDC, RGB(254, 0, 0), CRect(x + 20, y - 2, x + 135, y + 13));
		else if(order.nRunType == RUN_FAST)
			LF->FillGradient(pDC, RGB(239, 87, 83), CRect(x + 20, y - 2, x + 135, y + 13));
		else if(order.nRunType == RUN_SLOW)
			LF->FillGradient(pDC, RGB(255, 182, 68), CRect(x + 20, y - 2, x + 135, y + 13));

		m_imgList.Draw(pDC, LF->GetImageNumber(order.nState), CPoint(x + 2, y - 4), ILD_NORMAL);


		if(!m_bWideColumn)
		{
			if(order.bOtherOrder)
			{
				pDC->SetTextColor(m_crOtherOrderText);
				pDC->SetBkColor(m_crOtherOrderBack);
				pDC->SetBkMode(OPAQUE);
			}
			else
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 255));
				pDC->SetBkMode(TRANSPARENT);
			}

			//pDC->TextOut(x + 22, y, order.strStart.Left(6));
			//pDC->TextOut(x + 62, y, order.strDest.Left(6));

			pDC->TextOut(x + 22, y, GetWString(order.strStart,6));
			pDC->TextOut(x + 62, y, GetWString(order.strDest,6));

			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);

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
		}
		else
		{
			if(order.bOtherOrder)
			{
				pDC->SetTextColor(m_crOtherOrderText);
				pDC->SetBkColor(m_crOtherOrderBack);
				pDC->SetBkMode(OPAQUE);
			}
			else
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 255));
				pDC->SetBkMode(TRANSPARENT);
			}

			//pDC->TextOut(x + 22, y, order.strStart.Left(8));
			//pDC->TextOut(x + 72, y, order.strDest.Left(8));
			pDC->TextOut(x + 22, y, GetWString(order.strStart,8));
			pDC->TextOut(x + 72, y, GetWString(order.strDest,8));

			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);

			if(m_nOrderTimeType == 0 || order.nState == 35)
			{
				pDC->TextOut(x + 122, y, order.dtTime.Format("%H:%M"));
			}
			else
			{
				if(order.dtTime.GetStatus() == COleDateTime::valid)
				{
					long nMinute = max(span.GetTotalMinutes(), 0);
					strTemp.Format("+%d분", nMinute);
					pDC->TextOut(x + 122, y, strTemp);
				}
			}


			if(order.nWayType == 1) {
				pDC->SelectObject(&pen2);
				pDC->MoveTo(x + 22, y + 11);
				pDC->LineTo(x + 107, y + 11);
			}
		}

		it++;
	}


	CString strTotal, strPayInfo;

	//if(m_ccm[pRecordItem->pAllocRiderInfo->nCompany] != pRecordItem->pAllocRiderInfo->nCompany)
	if(pRecordItem->pAllocRiderInfo->bShareRider)
	{
		strPayInfo = m_ci.GetName(pRecordItem->pAllocRiderInfo->nCompany);
	}
	else if(!m_bShowPhoneAlways)
	{
		if(nTotalCount > 0) {
			strPayInfo.Format("%d건/%s원", 
					nAllocCount + 
					nFinishCount, 
					LF->GetMyNumberFormat(nTotalCharge));
		}

		if(bEmptyCar && m_bShowPosName)
		{
			CString strEmpty;
			COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - pRecordItem->pAllocRiderInfo->dtLastAction;
			if(dtSpan.GetTotalMinutes() < 180.0)
			{
				strEmpty.Format("  공차:%d분", dtSpan.GetTotalMinutes() < 0 ? 0 : (long)dtSpan.GetTotalMinutes());
				strPayInfo += strEmpty;
			}
		}
	}
	else
	{
		if(nTotalCount > 0) {
			strPayInfo.Format("%d / %s ", 
				nAllocCount + 
				nFinishCount, 
				LF->GetMyNumberFormat(nTotalCharge));
		}

		if(pRecordItem->pAllocRiderInfo->strPhone.GetLength() > 0)
			strPayInfo += "P:" + pRecordItem->pAllocRiderInfo->strPhone;
	}

	pDC->SetTextColor(RGB(41, 41, 214));
	pDC->TextOut(x + 4, rc.bottom - 14, strPayInfo);


	if(m_bDisplayAttendLeave)
	{
		if(pRecordItem->pAllocRiderInfo->nWorkReportState >= 2)
		{
			HPEN hOldPen = (HPEN)pDC->SelectObject(m_HandleManager.GetPenObject(RGB(255, 50, 50), 1));
			pDC->MoveTo(rc.left, rc.top);
			pDC->LineTo(rc.right, rc.bottom);
			pDC->MoveTo(rc.right, rc.top);
			pDC->LineTo(rc.left, rc.bottom);
			pDC->SelectObject((HGDIOBJ)hOldPen);
		}
	}
}

CString CAllocateReportPaintManager::GetWString(CString strItem, long nLeft)
{
	CStringW strItemW(strItem);
	strItemW = strItemW.Left(nLeft / 2);
	return CString(strItemW);
}


void CAllocateReportPaintManager::DrawTextLine(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
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
		} // switch

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


int CAllocateReportPaintManager::DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign)
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

int CAllocateReportPaintManager::DrawLink(int* pnCurrDrawPos, XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
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


bool compare_greator_rider_no(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	BOOL bCompF = (m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder < elem2->bShareRiderHaveMyOrder);
	BOOL bSameF = ((m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder == elem2->bShareRiderHaveMyOrder) || m_nOtherRiderShowType == 0);
	BOOL bComp0 = (m_nCarShowType == 1 && elem1->nCarType < elem2->nCarType);
	BOOL bSame0 = ((m_nCarShowType == 1 && elem1->nCarType == elem2->nCarType) || m_nCarShowType == 0);
	BOOL bComp1 = elem1->nCompany < elem2->nCompany;
	BOOL bSame1 = elem1->nCompany == elem2->nCompany;
	BOOL bComp2 = elem1->nRNo < elem2->nRNo;

	return  bCompF || 
			(bSameF && bComp0) || 
			(bSameF && bSame0 && bComp1) || 
			(bSameF && bSame0 && bSame1 && bComp2);
}

bool compare_greator_rider_name(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	BOOL bCompF = (m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder < elem2->bShareRiderHaveMyOrder);
	BOOL bSameF = ((m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder == elem2->bShareRiderHaveMyOrder) || m_nOtherRiderShowType == 0);
	BOOL bComp0 = (m_nCarShowType == 1 && elem1->nCarType < elem2->nCarType);
	BOOL bSame0 = ((m_nCarShowType == 1 && elem1->nCarType == elem2->nCarType) || m_nCarShowType == 0);
	int nCompare = strcmp(elem1->strName, elem2->strName);

	return  bCompF || 
			(bSameF && bComp0) || 
			(bSameF && bSame0 && nCompare < 0) || 
			(bSameF && bSame0 && nCompare == 0 && compare_greator_rider_no(elem1, elem2));
}

bool compare_greator_rider_total_count(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	BOOL bCompF = (m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder < elem2->bShareRiderHaveMyOrder);
	BOOL bSameF = ((m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder == elem2->bShareRiderHaveMyOrder) || m_nOtherRiderShowType == 0);
	BOOL bComp0 = (m_nCarShowType == 1 && elem1->nCarType < elem2->nCarType);
	BOOL bSame0 = ((m_nCarShowType == 1 && elem1->nCarType == elem2->nCarType) || m_nCarShowType == 0);
	BOOL bComp1 = elem1->nTotalCount > elem2->nTotalCount;
	BOOL bSame1 = elem1->nTotalCount == elem2->nTotalCount;
	BOOL bComp2 = elem1->nTotalCharge > elem2->nTotalCharge;
	BOOL bSame2 = elem1->nTotalCharge == elem2->nTotalCharge;

	return  bCompF ||
			(bSameF && bComp0) || 
			(bSameF && bSame0 && bComp1) || 
			(bSameF && bSame0 && bSame1 && bComp2) || 
			(bSameF && bSame0 && bSame1 && bSame2 && compare_greator_rider_no(elem1, elem2));
}

bool compare_greator_rider_total_charge(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	BOOL bCompF = (m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder < elem2->bShareRiderHaveMyOrder);
	BOOL bSameF = ((m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder == elem2->bShareRiderHaveMyOrder) || m_nOtherRiderShowType == 0);
	BOOL bComp0 = (m_nCarShowType == 1 && elem1->nCarType < elem2->nCarType);
	BOOL bSame0 = ((m_nCarShowType == 1 && elem1->nCarType == elem2->nCarType) || m_nCarShowType == 0);
	BOOL bComp1 = elem1->nTotalCharge > elem2->nTotalCharge;
	BOOL bSame1 = elem1->nTotalCharge == elem2->nTotalCharge;
	BOOL bComp2 = elem1->nTotalCount > elem2->nTotalCount;
	BOOL bSame2 = elem1->nTotalCount == elem2->nTotalCount;

	return  bCompF ||
			(bSameF && bComp0) || 
			(bSameF && bSame0 && bComp1) || 
			(bSameF && bSame0 && bSame1 && bComp2) || 
			(bSameF && bSame0 && bSame1 && bSame2 && compare_greator_rider_no(elem1, elem2));
}

bool compare_greator_rider_alloc_count(ALLOCATE_BOARD_RIDER_INFO* elem1, ALLOCATE_BOARD_RIDER_INFO* elem2)
{
	BOOL bCompF = (m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder < elem2->bShareRiderHaveMyOrder);
	BOOL bSameF = ((m_nOtherRiderShowType == 1 && elem1->bShareRiderHaveMyOrder == elem2->bShareRiderHaveMyOrder) || m_nOtherRiderShowType == 0);
	BOOL bComp0 = (m_nCarShowType == 1 && elem1->nCarType < elem2->nCarType);
	BOOL bSame0 = ((m_nCarShowType == 1 && elem1->nCarType == elem2->nCarType) || m_nCarShowType == 0);
	BOOL bComp1 = elem1->nAllocCount > elem2->nAllocCount;
	BOOL bSame1 = elem1->nAllocCount == elem2->nAllocCount;

	return  bCompF || 
			(bSameF && bComp0) || 
			(bSameF && bSame0 && bComp1) || 
			(bSameF && bSame0 && bSame1 && compare_greator_rider_no(elem1, elem2));
}

void CAllocateReportPaintManager::ResortRider(long nType, long nCarShowType, long nOtherRiderShowType)
{
	m_nCarShowType = nCarShowType;
	m_nOtherRiderShowType = nOtherRiderShowType;

	switch(nType)
	{
	case 0:
		std::sort(m_vecRider.begin(), m_vecRider.end(), compare_greator_rider_no);
		break;
	case 1:
		std::sort(m_vecRider.begin(), m_vecRider.end(), compare_greator_rider_name);
		break;
	case 2:
		std::sort(m_vecRider.begin(), m_vecRider.end(), compare_greator_rider_total_count);
		break;
	case 3:
		std::sort(m_vecRider.begin(), m_vecRider.end(), compare_greator_rider_total_charge);
		break;
	case 4:
		std::sort(m_vecRider.begin(), m_vecRider.end(), compare_greator_rider_alloc_count);
		break;
	}
}

BOOL CAllocateReportPaintManager::HitTest( CPoint pt, TRS_CONTROL** pTRSResult )
{
	return FALSE;
}
