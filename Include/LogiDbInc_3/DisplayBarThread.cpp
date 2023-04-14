// DisplayBarThread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DisplayBarThread.h"

// CDisplayBarThread

IMPLEMENT_DYNCREATE(CDisplayBarThread, CWinThread)

CDisplayBarThread::CDisplayBarThread()
{
	m_ptStartPos = CPoint(-1, -1);
}

CDisplayBarThread::~CDisplayBarThread()
{
}

BOOL CDisplayBarThread::InitInstance()
{
	m_DisplayBar.Create(GetMainWnd());
	m_DisplayBar.SetSkin(IDB_DISPLAY_BAR_ROUND, 255, 0, 255);
	m_DisplayBar.SetStartPos(m_ptStartPos);
	return TRUE;
}

int CDisplayBarThread::ExitInstance()
{
	m_DisplayBar.Hide();
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDisplayBarThread, CWinThread)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_SHOW, OnDisplayBarShow)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_HIDE, OnDisplayBarHide)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_WAIT, OnDisplayBarWait)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_PROGRESS, OnDisplayBarProgress)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_CANCEL_EVENT, OnDisplayBarCancelEvent)
	ON_THREAD_MESSAGE(WM_DISPLAY_BAR_PREVENT_CANCEL, OnDisplayBarPreventCancel)
END_MESSAGE_MAP()


// CDisplayBarThread 메시지 처리기입니다.
void CDisplayBarThread::OnDisplayBarShow(WPARAM wParam, LPARAM lParam)
{
	if(lParam == 0xFFFF)
		lParam = 0;
	else
		m_DisplayBar.m_nShowCount++;
	
	CString *pstr = (CString*)wParam;
	if(pstr)
	{
		DWORD dwDelay = (DWORD)lParam;
		if(dwDelay > 0)
			m_DisplayBar.ShowText(*pstr, dwDelay);
		else
			m_DisplayBar.ShowText(*pstr);

		delete pstr;
	}
	else
	{
		m_DisplayBar.Show();
	}
}

void CDisplayBarThread::OnDisplayBarHide(WPARAM wParam, LPARAM lParam)
{
	m_DisplayBar.m_nShowCount--;
	BOOL bCheckRefCount = (BOOL)wParam;
	if(bCheckRefCount)
	{
		if(m_DisplayBar.m_nShowCount <= 0)
		{
			m_DisplayBar.m_nShowCount = 0;
			m_DisplayBar.Hide();
		}
	}
	else
	{
		m_DisplayBar.Hide();
	}
}

void CDisplayBarThread::OnDisplayBarWait(WPARAM wParam, LPARAM lParam)
{
	m_DisplayBar.SetWaitMode((int)wParam, (int)lParam);
}

void CDisplayBarThread::OnDisplayBarProgress(WPARAM wParam, LPARAM lParam)
{
	CDisplayBarProgressInfo *pInfo = (CDisplayBarProgressInfo*)wParam;
	BOOL bDontDelete = (BOOL)lParam;

	m_DisplayBar.SetWaitMode(FALSE);
	m_DisplayBar.SetProgressText(pInfo->m_strText);
	m_DisplayBar.SetProgressRate(pInfo->m_dPos);
	m_DisplayBar.RefreshProgress();

	if(!bDontDelete)
	{
		delete pInfo;
		pInfo = NULL;
	}
}

void CDisplayBarThread::OnDisplayBarCancelEvent(WPARAM wParam, LPARAM lParam)
{
	m_DisplayBar.SetCancelEvent((HANDLE)wParam);
	m_DisplayBar.Hide();
	m_DisplayBar.m_nShowCount = 0;
}

void CDisplayBarThread::OnDisplayBarPreventCancel(WPARAM wParam, LPARAM lParam)
{
	m_DisplayBar.HideCancelButton((BOOL)wParam);
}

