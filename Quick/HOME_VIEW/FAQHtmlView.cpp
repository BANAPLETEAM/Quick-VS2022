// FAQHtmlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "FAQHtmlView.h"
#include ".\faqhtmlview.h"


// CFAQHtmlView

IMPLEMENT_DYNCREATE(CFAQHtmlView, CHtmlView)

CFAQHtmlView::CFAQHtmlView()
{
	m_bRun = FALSE;
}

CFAQHtmlView::~CFAQHtmlView()
{
}

void CFAQHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFAQHtmlView, CHtmlView)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER_NAVIGATE, OnUserNavigate)
END_MESSAGE_MAP()


// CFAQHtmlView 진단입니다.

#ifdef _DEBUG
void CFAQHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CFAQHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CFAQHtmlView 메시지 처리기입니다.

void CFAQHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
}

void CFAQHtmlView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CHtmlView::OnActivate(nState, pWndOther, bMinimized);
}

void CFAQHtmlView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(bShow && !m_bRun)
	{
		if(!m_strURL.IsEmpty())
		{
			Navigate2(m_strURL, 0, 0);
			m_bRun = TRUE;
		}
		/*else
		{
			SetTimer(0, 100, NULL);
		}*/
	}

	CHtmlView::OnShowWindow(bShow, nStatus);
}

void CFAQHtmlView::OnTimer(UINT nIDEvent)
{
	if(!m_bRun && !m_strURL.IsEmpty())
	{
		// 서버부하로 인한 탭페이지 볼때 갱신
	/*	Navigate2(m_strURL, 0, 0);
		m_bRun = TRUE;
		KillTimer(0);*/
	}

	CHtmlView::OnTimer(nIDEvent);
}

LONG CFAQHtmlView::OnUserNavigate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

