#pragma once

#include "DisplayBar.h"

#define WM_DISPLAY_BAR_SHOW		(WM_USER + 1) 
#define WM_DISPLAY_BAR_HIDE		(WM_USER + 2) 
#define WM_DISPLAY_BAR_WAIT		(WM_USER + 3) 
#define WM_DISPLAY_BAR_PROGRESS	(WM_USER + 4) 
#define WM_DISPLAY_BAR_CANCEL_EVENT		(WM_USER + 5) 
#define WM_DISPLAY_BAR_PREVENT_CANCEL	(WM_USER + 6) 


// CDisplayBarThread
	

class AFX_EXT_CLASS CDisplayBarThread : public CWinThread
{
	DECLARE_DYNCREATE(CDisplayBarThread)

protected:
	CDisplayBarThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDisplayBarThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CDisplayBar m_DisplayBar;
	CPoint m_ptStartPos;

	void OnDisplayBarShow(WPARAM wParam, LPARAM lParam);
	void OnDisplayBarHide(WPARAM wParam, LPARAM lParam);
	void OnDisplayBarWait(WPARAM wParam, LPARAM lParam);
	void OnDisplayBarProgress(WPARAM wParam, LPARAM lParam);
	void OnDisplayBarCancelEvent(WPARAM wParam, LPARAM lParam);
	void OnDisplayBarPreventCancel(WPARAM wParam, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
};


class AFX_EXT_CLASS CDisplayBarProgressInfo 
{
public:
	CDisplayBarProgressInfo(CString strText, double dPos)
	{
		m_strText = strText;
		m_dPos = dPos;
	}

	CString m_strText;
	double m_dPos;
};


//CDisplayBarThreadText
class AFX_EXT_CLASS CDisplayBarThreadText 
{
public:
	CDisplayBarThreadText(CDisplayBarThread *pDisplayBarThread, CString strText, DWORD dwDelayShow = 1000) //ms
	{
		m_nMaxRange = 0;
		m_pDisplayBarThread = pDisplayBarThread;

		if(m_pDisplayBarThread)
		{
			CString *pstr = new CString(strText);
			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_SHOW, (LPARAM)pstr, dwDelayShow);
		}
	}

	CDisplayBarThreadText(CDisplayBarThread *pDisplayBarThread, CString strText, BOOL bWaitMode, long nMaxRange)
	{
		m_nMaxRange = nMaxRange;
		m_pDisplayBarThread = pDisplayBarThread;
		
		if(m_pDisplayBarThread)
		{
			CString *pstr = new CString(strText);
			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_SHOW, (LPARAM)pstr, 0);
			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_PREVENT_CANCEL, 1, 0);
			if(bWaitMode)
				m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_WAIT, 1, 1);
		}
	}

	void SetText(CString strText)
	{
		if(m_pDisplayBarThread)
		{
			CString *pstr = new CString(strText);
			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_SHOW, (LPARAM)pstr, 0xFFFF);
		}
	}

	void SetProgress(long nCurRange, CString strProgressText = "", BOOL bAutoCombineTextRange = FALSE)
	{
		if(m_pDisplayBarThread && m_nMaxRange > 0)
		{
			double dCurRange = nCurRange * 100.0 / m_nMaxRange;
			
			if(bAutoCombineTextRange && strProgressText.GetLength() > 0)
				strProgressText.Format("%s(%0.0f%%)", strProgressText, dCurRange);

			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_PROGRESS,
				(WPARAM)new CDisplayBarProgressInfo(strProgressText, dCurRange), 
				0);
		}
	}

	~CDisplayBarThreadText()
	{
		if(m_pDisplayBarThread)
		{
			m_pDisplayBarThread->PostThreadMessage(WM_DISPLAY_BAR_HIDE, 1, 0);
		}
	}

public:
	CDisplayBarThread *m_pDisplayBarThread;
	long m_nMaxRange;
};


