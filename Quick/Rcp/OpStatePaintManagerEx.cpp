#include "stdafx.h"
#include "resource.h"
#include "OPStatePaintManagerEx.h"
#include "RcpPageCTIForm.h"
#include "CallListRecord.h"

COPStatePaintManagerEx::COPStatePaintManagerEx(void)
{
	m_nMyState = PH_HANG_UP;
	m_bShowLastPhoneNumber = FALSE;

	/*m_pOPNoneStream = GDIStream(IDB_OP_NONE_PNG);
	m_pOPRecvStream = GDIStream(IDB_OP_RECV_PNG);
	m_pOPPauseStream = GDIStream(IDB_OP_PAUSE_PNG);
	m_pOPWorkStream = GDIStream(IDB_OP_WORK_PNG);
	m_pOPLogOutStream = GDIStream(IDB_OP_LOGOUT_PNG);
	m_pOPRecordStream = GDIStream(IDB_OP_RECORD_PNG);
	m_pOPMuteStream  = GDIStream(IDB_OP_MUTE_PNG);
	m_pOPParkStream = GDIStream(IDB_OP_PARK_PNG);*/

	m_pMakeCallStream = GDIStream(IDB_OP_MAKECALL_PNG);
	m_pPickUpCallStream = GDIStream(IDB_OP_PICKUP_PNG);
	m_pTransferCallStream = GDIStream(IDB_OP_TRANSFER_PNG);
}

COPStatePaintManagerEx::~COPStatePaintManagerEx(void)
{
	OP_STATE_MAP::iterator it;
	for(it = m_mapOPState.begin(); it != m_mapOPState.end(); it++)
	{
		if(it->second)
			delete it->second;
	}
}

#define ROW_OFFSET 22

int COPStatePaintManagerEx::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
{
	if(!pRow)
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + (ROW_OFFSET * 2);
	}

	if (!pRow->IsGroupRow())
	{
		return m_nRowHeight + (IsGridVisible(FALSE)? 1: 0) + (ROW_OFFSET * 2);
	}

	if (m_bShadeGroupHeadings)
		return m_nRowHeight + 6 + (ROW_OFFSET * 2);

	return m_nRowHeight + 16 + (ROW_OFFSET * 2);
}

void COPStatePaintManagerEx::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
										   XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CString strText = pMetrics->strText;
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;
	Graphics graphics(pDC->m_hDC);

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	COPStateRecordItemEx *pRecordItem = (COPStateRecordItemEx*)pRecord->GetItem(nCol);

	CFont *pfntOld = pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 18, FW_BOLD));
	LF->FillGradient(pDC, RGB(200, 200, 255), rc, 40);
	rc.DeflateRect(1, 1, 1, 1);

	CRect rcTop = rc;
	rcTop.bottom = rc.top + 20;
	CRect rcTopText = rcTop;
	rcTopText.top += 1;
	rcTopText.left += 2;

	CRect rcMiddleText = rc;
	rcMiddleText.top = rcTop.bottom - 1;
	rcMiddleText.bottom = rcMiddleText.top + 19;
	rcMiddleText.left += 2;
	rcMiddleText.right -= 2;
	CRect rcBottomText = rc;
	rcBottomText.top = rcMiddleText.bottom + 3;
	rcBottomText.left += 60;
	rcBottomText.right -= 2;
	rcBottomText.bottom -= 1;

	if(pRecordItem->pOPState)
	{
		pRecordItem->nMyState = m_nMyState;

		if(pRecordItem->pOPState->nState == PH_ANSWER)
		{
			//CLogiFunc::FillGradient(pDC, RGB(220, 255, 220), rc, 40);

			int nSec = CCallListRecord::GetMyElapsedSecond(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime());

			if(nSec > 1800)
				LF->FillGradient(pDC, RGB(200, 200, 200), rc, 40);
			else
			{
				int nDevision = (nSec != 0 ? nSec / 600 : 0);
				LF->FillGradient(pDC, RGB(220, (255 - (nDevision * 10) > 200 ? 255 - (nDevision * 10) : 200), 220), rc, 40);
			}
		}
		else if(pRecordItem->pOPState->nState == PH_RING ||
			pRecordItem->pOPState->nState == PH_ARS_ANSWER)
		{
			//CLogiFunc::FillGradient(pDC, RGB(255, 255, 200), rc, 40);

			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - pRecordItem->pOPState->dtLastAnswer;
			int nSec = CCallListRecord::GetMyElapsedSecond(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime());

			if(nSec > 60 && pRecordItem->pOPState->nState == PH_RING)
			{
				pRecordItem->pOPState->nState = PH_HANG_UP;
				pDC->FillSolidRect(rc, RGB(255, 255, 255));
			}
			else if(nSec > 1800)
				LF->FillGradient(pDC, RGB(200, 200, 200), rc, 40);
			else
			{
				int nDevision = (nSec != 0 ? nSec / 600 : 0);
				LF->FillGradient(pDC, RGB((255 - (nDevision * 10) > 200 ? 255 - (nDevision * 10) : 200), (255 - (nDevision * 10) > 200 ? 255 - (nDevision * 10) : 200), 200)
					, rc, 40);
			}
		}
		else if(pRecordItem->pOPState->nState == PH_OUT_BOUND_CALL)
		{
			//CLogiFunc::FillGradient(pDC, RGB(200, 200, 255), rc, 40);

			int nSec = CCallListRecord::GetMyElapsedSecond(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime());
			if(nSec > 1800)
				LF->FillGradient(pDC, RGB(200, 200, 200), rc, 40);
			else
			{
				int nDevision = (nSec != 0 ? nSec / 600 : 0);
				LF->FillGradient(pDC, RGB(200, 200, (255 - (nDevision * 10) > 200 ? 255 - (nDevision * 10) : 200)), rc, 40);
			}
		}
		else
			pDC->FillSolidRect(rc, RGB(255, 255, 255));

		pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 14, FW_BOLD));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->DrawText((pRecordItem->pOPState->strOperator.GetLength() > 1) ? 
				pRecordItem->pOPState->strOperator : 
		pRecordItem->pOPState->strKeyPhoneID, rcTopText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);	

		if(!pRecordItem->pOPState->bARSLine)
		{
			if((pRecordItem->pOPState->nState == PH_ANSWER || pRecordItem->pOPState->nState == PH_OUT_BOUND_CALL || pRecordItem->pOPState->nState == PH_RING))
			{
				pDC->SetTextColor(RGB(50, 50, 50));
				pDC->DrawText(CCallListRecord::GetMyElapsedTimeFormatEx(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime()),
					rcBottomText, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->DrawText(CCallListRecord::GetMyElapsedTimeFormatEx(pRecordItem->pOPState->dtLastAnswer, COleDateTime::GetCurrentTime(), TRUE),
					rcBottomText, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			}			

			if(pRecordItem->pOPState->nState == PH_HANG_UP)
			{
				if(m_nMyState == PH_HANG_UP)
				{
					Image imageMakeCall(m_pMakeCallStream);
					if(imageMakeCall.GetLastStatus() == Ok)
						graphics.DrawImage(&imageMakeCall, rcMiddleText.left - 1, rcMiddleText.bottom + 1, imageMakeCall.GetWidth(), imageMakeCall.GetHeight());
				}
				else if(m_nMyState == PH_ANSWER)
				{
					Image imageTransferCall(m_pTransferCallStream);
					if(imageTransferCall.GetLastStatus() == Ok)
						graphics.DrawImage(&imageTransferCall, rcMiddleText.left + 47, rcMiddleText.bottom + 1, imageTransferCall.GetWidth(), imageTransferCall.GetHeight());
				}
			}
			else if(pRecordItem->pOPState->nState == PH_RING || pRecordItem->pOPState->nState == PH_ANSWER/* || pRecordItem->pOPState->nState == PH_OUT_BOUND_CALL*/)
			{
				if(m_nMyState == PH_HANG_UP)
				{
					Image imagePickUpCall(m_pPickUpCallStream);
					if(imagePickUpCall.GetLastStatus() == Ok)
						graphics.DrawImage(&imagePickUpCall, rcMiddleText.left + 23, rcMiddleText.bottom + 1, imagePickUpCall.GetWidth(), imagePickUpCall.GetHeight());
				}
			}
		}
		else
		{
			if(pRecordItem->pOPState->nState == PH_RING)
			{
				pDC->SetTextColor(RGB(50, 50, 50));
				pDC->DrawText(CCallListRecord::GetMyElapsedTimeFormatEx(pRecordItem->pOPState->dtLastTime, COleDateTime::GetCurrentTime()),
					rcBottomText, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			}

			if(m_nMyState == PH_HANG_UP)
			{
				Image imagePickUpCall(m_pPickUpCallStream);
				if(imagePickUpCall.GetLastStatus() == Ok)
					graphics.DrawImage(&imagePickUpCall, rcMiddleText.left + 22, rcMiddleText.bottom + 1, imagePickUpCall.GetWidth(), imagePickUpCall.GetHeight());
			}
		}

		if(pRecordItem->pOPState->strCurPhone.GetLength() > 3)
		{
			pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 16, FW_BOLD));
			pDC->SetTextColor(RGB(50, 50, 80));

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
						strCustomer = GetDashPhoneNumber(strCurPhone);
					else
						strCustomer = strCurPhone.Left(strCurPhone.GetLength() - 2) + "**";
				}
			}

			if(strCustomer.Find("PHONE") >= 0)
				strCustomer = "";

			pDC->DrawText(strCustomer, rcMiddleText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}

		pRecordItem->ptCall = CPoint(rcMiddleText.left - 1, rcMiddleText.bottom + 1);
		pRecordItem->ptState = rcTop.TopLeft();
	}
	else
	{
		pDC->FillSolidRect(rc, RGB(255, 255, 255));	
		pDC->DrawText("-", rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	pDC->SelectObject(pfntOld);
}

IStream* COPStatePaintManagerEx::GDIStream(UINT nResourceID)
{
	HRSRC hResource = FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(nResourceID), TEXT("PNG"));
	if(!hResource)
		return NULL;      

	DWORD imageSize = SizeofResource(AfxGetInstanceHandle(), hResource);
	HGLOBAL hGlobal = LoadResource(AfxGetInstanceHandle(), hResource);
	LPVOID pData = LockResource(hGlobal);

	HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	LPVOID pBuffer = GlobalLock(hBuffer);

	CopyMemory(pBuffer,pData,imageSize);    
	GlobalUnlock(hBuffer);   

	IStream *pStream;   
	HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

	return pStream;
}

void COPStatePaintManagerEx::DrawRectLine(CDC* pDC, CRect rcRect)
{
	rcRect.InflateRect(0, 1, 0, 0);
	//pDC->FillSolidRect(rcRect.left, rcRect.top, rcRect.Width(), rcRect.Height() - 1, RGB(255, 255, 255));
	pDC->FillSolidRect(rcRect.left - 1, rcRect.top - 1, rcRect.Width() + 1, 1, RGB(221, 221, 221));
	pDC->FillSolidRect(rcRect.left - 1, rcRect.bottom - 1, rcRect.Width() + 1, 1, RGB(221, 221, 221));
	pDC->FillSolidRect(rcRect.left - 1, rcRect.top - 1, 1, rcRect.Height(), RGB(221, 221, 221));
	pDC->FillSolidRect(rcRect.right, rcRect.top - 1, 1, rcRect.Height(), RGB(221, 221, 221));
	
}