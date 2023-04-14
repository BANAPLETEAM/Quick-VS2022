// MmsImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MmsImageView.h"


// CMmsImageView

IMPLEMENT_DYNCREATE(CMmsImageView, CScrollView)

CMmsImageView::CMmsImageView()
{
	m_nCurShowImage = -1;
	m_nImageCount = 0;
	nZoom = 0;
}

CMmsImageView::~CMmsImageView()
{
}

BEGIN_MESSAGE_MAP(CMmsImageView, CScrollView)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CMmsImageView 그리기입니다.

void CMmsImageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMmsImageView 진단입니다.

#ifdef _DEBUG
void CMmsImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CMmsImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMmsImageView 메시지 처리기입니다.

void CMmsImageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc; 
	GetClientRect(rc);

	long nClientHeight = rc.Height();
	long nClientWidth = rc.Width();

	if(GetCurNumber() >= 0 || !m_imgMms[GetCurNumber()].IsNull())
	{
		dc.SetStretchBltMode(COLORONCOLOR);

		/*
		int nVertScroll = GetScrollPos(SB_VERT);
		int nHortScroll = GetScrollPos(SB_HORZ);

		m_imgMms[GetCurNumber()].BitBlt(dc.m_hDC, -nHortScroll, -nVertScroll);
		*/
	
		long nImageHeight = m_imgMms[GetCurNumber()].GetHeight();
		long nImageWidth = m_imgMms[GetCurNumber()].GetWidth();

		if(nImageHeight > nClientHeight || nImageWidth > nClientWidth)
		{
			long nHeightPer = (float)nClientHeight / (float)nImageHeight * 100.0;
			long nWidthPer = (float)nClientWidth / (float)nImageWidth * 100.0;

			long nPer = 1;

			if(nHeightPer > 100)
				nPer = nWidthPer;
			else if(nWidthPer > 100)
				nPer = nHeightPer;
			else
				nPer = max(nHeightPer, nWidthPer);

			nImageHeight = nImageHeight * nPer / 100.0;
			nImageWidth = nImageWidth * nPer / 100.0;
		}

		long nStartX = (nClientWidth - nImageWidth) / 2; 
		long nStartY = (nClientHeight - nImageHeight) / 2; 

		//dc.StretchBlt(nStartX, nStartY, nImageWidth , nImageHeight, CDC::FromHandle(m_imgMms[GetCurNumber()].GetDC()), 0, 0, SRCCOPY);
		//dc.StretchBlt(CDC::FromHandle(m_imgMms[GetCurNumber()].GetDC()), nStartX, nStartY, nImageWidth , nImageHeight, SRCCOPY);

		m_imgMms[GetCurNumber()].StretchBlt(dc.m_hDC, nStartX, nStartY, nImageWidth , nImageHeight, SRCCOPY); 	
	}  
	else 
		dc.Rectangle(rc.left-2, rc.top-2, rc.Width() + 4, rc.Height() + 4);
}

void CMmsImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
} 

void CMmsImageView::SetCurNumber(long nNumber) 
{
	//if(!m_strImage[nNumber].IsEmpty())
	//	m_nCurShowImage = nNumber;
	//else 

	if(m_imgMms[nNumber].IsNull())
		m_nCurShowImage = -1;
	else
		m_nCurShowImage = nNumber;

	Invalidate();
}

int CMmsImageView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return TRUE;

	return CScrollView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CMmsImageView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//Invalidate(TRUE);
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMmsImageView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//Invalidate(TRUE);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}