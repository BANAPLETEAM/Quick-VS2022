// FAQHtmlView.cpp : ���� �����Դϴ�.
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


// CFAQHtmlView �����Դϴ�.

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


// CFAQHtmlView �޽��� ó�����Դϴ�.

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
		// �������Ϸ� ���� �������� ���� ����
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

