#pragma once

#include "TaskbarNotifier.h"
// CStartbarNotifier

#define WM_NBASE					WM_USER + 123
#define WM_NOTIFIER_CLICKED			WM_NBASE + 1
#define WM_NOTIFIER_HIDE			WM_NBASE + 2


class CStartbarNotifier : public CTaskbarNotifier
{
	DECLARE_DYNAMIC(CStartbarNotifier)

public:
	CStartbarNotifier();
	virtual ~CStartbarNotifier();

	virtual void Show();
	virtual void Show(LPCTSTR szTitle, LPCTSTR szCaption,DWORD dwTimeToShow=500,DWORD dwTimeToStay=300000,DWORD dwTimeToHide=500,int nIncrement=1);
	virtual void Initailze(LPCTSTR szTitle, LPCTSTR szCaption,DWORD dwTimeToShow=500,DWORD dwTimeToStay=300000,DWORD dwTimeToHide=500,int nIncrement=1);
	virtual void Hide();

	void SetTitleTextColor(COLORREF crTitleColor) { m_crTitleTextColor =  crTitleColor; };

	UINT GetOffsetY() { return m_nOffsetY; };
	void SetOffsetY(UINT nOffsetY) { m_nOffsetY = nOffsetY; }; 
	UINT GetSkinHeight() { return m_nSkinHeight; };

	void SetItemData(void* ptr) { m_ptrItemData = ptr; };
	void DefaultSetting();

protected:
	DECLARE_MESSAGE_MAP()

	CString m_strTitle;
	
	COLORREF m_crTitleTextColor;
	UINT m_nOffsetY;
	void* m_ptrItemData;

public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


