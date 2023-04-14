// FAQHtmlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ImageHtmlView.h"


// CImageHtmlView

IMPLEMENT_DYNCREATE(CImageHtmlView, CHtmlView)

CImageHtmlView::CImageHtmlView()
{
}

CImageHtmlView::~CImageHtmlView()
{
}

void CImageHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageHtmlView, CHtmlView)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CImageHtmlView 진단입니다.

#ifdef _DEBUG
void CImageHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CImageHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CImageHtmlView 메시지 처리기입니다.

void CImageHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(m_strUrl, NULL, NULL);
	//Navigate2("www.naver.com", NULL, NULL);
}

void CImageHtmlView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	return;
	CHtmlView::OnActivate(nState, pWndOther, bMinimized);
}

void CImageHtmlView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CHtmlView::OnShowWindow(bShow, nStatus);
}

void CImageHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CHtmlView::OnDocumentComplete(lpszURL);
}

int CImageHtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;

	return CHtmlView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
