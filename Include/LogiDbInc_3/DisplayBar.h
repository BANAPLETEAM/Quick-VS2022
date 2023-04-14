#pragma once


#include <winuser.h>


#define PROGRESS_START_TEXT		"처리중입니다."
#define TEXT_DEFAULT_MSG		"처리중입니다.\n잠시만 기다려주시기 바랍니다."

class CTextProgressCtrl;

class AFX_EXT_CLASS CDisplayBar :public CWnd
{
public:
	CDisplayBar(void);
	virtual ~CDisplayBar(void);

	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


protected:
	void RepositionControls();

public:
	int Create(CWnd *pParent);
	void Hide();
	void Show();
	void ShowText(CString strText, DWORD dwDelayShow = 0);
	BOOL SetSkin(UINT nBitmapID,short red=-1,short green=-1,short blue=-1);
	HRGN GenerateRegion(HBITMAP hBitmap, BYTE red=-1, BYTE green=-1, BYTE blue=-1);
	BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	void SetProgressText(CString strText = PROGRESS_START_TEXT, BOOL bRedraw = FALSE);
	void SetText(CString strText = TEXT_DEFAULT_MSG, BOOL bRedraw = FALSE);
	void HideCancelButton(BOOL bHide = TRUE);
	void SetTextFont(CString strFaceName = "맑은 고딕", int nSize = 16, int nWeight = FW_NORMAL);
	void SetProgressRate(double fRate, BOOL bRedraw = FALSE);
	double GetProgressRate();
	void RefreshProgress();
	CRITICAL_SECTION* GetProgressCriticalSection();
	void SetCancelEvent(HANDLE hEvent);
	void SetWaitMode(BOOL bWaitMode = TRUE, BOOL bIgnoreAlter = FALSE);
	BOOL GetWaitMode();
	void ProgressWaitMode();
	BOOL IsUserCancel();
	void SetStartPos(CPoint ptStart);

protected:
	CString m_strProgressText;
	CString m_strCenterText;
	CRect m_rcClient;
	CRect m_rcImage;
	CTextProgressCtrl *m_pctlProgress;
	BOOL m_bHideCancel;
	CString m_strFontFaceName;
	int m_nFontSize;
	int m_nFontWeight;
	double m_fProgressRate;
	HANDLE m_hCancelEvent;
	BOOL m_bWaitMode;
	BOOL m_bWaitColorValueInc;
	BOOL m_bMouseDown;
	CPoint m_ptMouse;
	CRect m_rcNewPos;
	BOOL m_bUserCancel;

public:
	CWnd *m_pWndParent;
	CBitmap m_biSkinBackground;
	HRGN m_hSkinRegion;
	int m_nSkinWidth;
	int m_nSkinHeight;
	CBitmapButton *m_pbtnCancel;
	CArray<MONITORINFOEX, MONITORINFOEX> m_aryMonitors;
	int m_nShowCount;
};


AFX_INLINE void CDisplayBar::SetText(CString strText, BOOL bRedraw)
{
	m_strCenterText = strText;
	if(bRedraw)
		RedrawWindow();
}

AFX_INLINE void CDisplayBar::HideCancelButton(BOOL bHide)
{
	BOOL bRedraw = FALSE;
	if(m_bHideCancel != bHide)
		bRedraw = TRUE;

	m_bHideCancel = bHide;	

	if(bRedraw)
		RepositionControls();
}


AFX_INLINE void CDisplayBar::SetTextFont(CString strFaceName, int nSize, int nWeight)
{
	m_strFontFaceName = strFaceName;
	m_nFontSize = nSize;
	m_nFontWeight = nWeight;
}

AFX_INLINE double CDisplayBar::GetProgressRate()
{
	return m_fProgressRate;
}

AFX_INLINE void CDisplayBar::SetCancelEvent(HANDLE hEvent)
{
	m_hCancelEvent = hEvent;
}

AFX_INLINE BOOL CDisplayBar::GetWaitMode()
{
	return m_bWaitMode;
}

AFX_INLINE BOOL CDisplayBar::IsUserCancel()
{
	return m_bUserCancel;
}


#define NO_DELAY_SHOW	0

//CDisplayBarText
class AFX_EXT_CLASS CDisplayBarText 
{
public:
	CDisplayBarText(CDisplayBar *pDisplayBar, CString strText, DWORD dwDelayShow = 500) //ms
	{
		m_pDisplayBar = pDisplayBar;

		if(pDisplayBar)
		{
			(pDisplayBar->m_nShowCount)++;
			m_pDisplayBar->ShowText(strText, dwDelayShow);
		}
	}

	~CDisplayBarText()
	{
		if(m_pDisplayBar)
		{
			if(--(m_pDisplayBar->m_nShowCount) == 0)
				m_pDisplayBar->Hide();
		}
	}

public:
	CDisplayBar *m_pDisplayBar;
};


