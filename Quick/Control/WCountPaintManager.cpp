
#include "stdafx.h"
#include "resource.h"
#include "WCountPaintManager.h"
#include "RcpPageWCountForm.h"

CWCountPaintManager::CWCountPaintManager(void)
{
	m_bLoadRabkImage = FALSE;
}

CWCountPaintManager::~CWCountPaintManager(void)
{
}

void CWCountPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
									   XTP_REPORTRECORDITEM_METRICS* pMetrics)
{ 	
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();
	CRect rc = pDrawArgs->rcItem;
	CDC *pDC = pDrawArgs->pDC;

	/*
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *pOldBrush=pDC->SelectObject(&brush);
 
	CRect rc1; 
	rc.top -= 2;
	rc.bottom += 7;


	pDC->Rectangle(rc1);  
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject(); 
	*/

	LoadRankImage(pDC); 

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pDrawArgs->pRow->GetRecord();
	CWcountRecordItem *pItem = (CWcountRecordItem*)pRecord->GetItem(nCol);
  
	DrawCountInfo(1, pDC, rc, pItem->m_st.nRank);
 
	rc.left += 20;
	pDC->DrawText(pItem->m_st.nWNo == 0 ? pItem->m_st.strWName + "(" + m_ci.GetBranchName(pItem->m_st.nCompany) + ")" : pItem->m_st.strWName, rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	CFont *pOldFont = pDC->SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 18, FW_BOLD));
	
	DrawRankInfo(pDC, rc, pItem->m_st.nRank, pItem->m_st.nPreRank);

	pDC->SelectObject(*pOldFont); 
}


void CWCountPaintManager::DrawCountInfo(long nStartPos, CDC *pDC, CRect rc, long nRank)
{
	#define W_IMAGE_COUNT 14

	IMAGEINFO image_info;
	m_imgCount.GetImageInfo(nRank-1, &image_info);	
	long nTop = (rc.Height() - (image_info.rcImage.bottom - image_info.rcImage.top)) / 2;
	nTop = rc.top + nTop;

	m_imgCount.Draw(pDC, nRank-1, CPoint(nStartPos, nTop), ILD_TRANSPARENT);
}

void CWCountPaintManager::DrawRankInfo( CDC *pDC, CRect rc, long nRank, long nPreRank)
{
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap *pOldBmp = NULL;

	MemDC.CreateCompatibleDC(pDC);

	CBitmap *img = NULL;

	long nUpRank = 0;

	if(nPreRank == 0)
		img = &m_imgNew;
	else if(nRank > nPreRank)
		img = &m_imgDown;
	else if(nRank < nPreRank)
		img = &m_imgUp;
	else if(nRank == nPreRank) 
		img = &m_imgStay;

	img->GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(img);

	long nTop = (rc.Height() - bmpInfo.bmHeight) / 2;
	nTop = rc.top + nTop;

	rc.left = rc.right - 25;

	if(nPreRank == 0 || nRank == nPreRank)
	{
		long nLeft = (rc.Width() - bmpInfo.bmWidth) / 2;
		nLeft = rc.left + nLeft;
		pDC->BitBlt(nLeft, nTop, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
	}
	else  
	{ 
		pDC->BitBlt(rc.left, nTop, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);

		rc.left += bmpInfo.bmWidth;

		pDC->DrawText(::GetStringFromLong(abs(nRank - nPreRank)), rc, DT_SINGLELINE | DT_CENTER);
	}

	MemDC.SelectObject(pOldBmp);	 
	ReleaseDC(NULL, MemDC.m_hDC); 

};

void CWCountPaintManager::LoadRankImage(CDC *pDC)
{
	if(m_bLoadRabkImage)
		return;

	m_bLoadRabkImage = TRUE;


	m_imgCount.Create(IDB_W_COUNT, 15, 14, RGB(255, 255, 255));
	m_imgUp.LoadBitmap(IDB_W_UP);
	m_imgDown.LoadBitmap(IDB_W_DOWN);
	m_imgStay.LoadBitmap(IDB_W_STAY);
	m_imgNew.LoadBitmap(IDB_W_NEW);

}
