// CTaskbarNotifier Header file
// By John O'Byrne - 05 July 2002

#pragma once

#define WM_TASKBARNOTIFIERCLICKED	WM_USER+123

#define TN_TEXT_NORMAL			0x0000
#define TN_TEXT_BOLD			0x0001
#define TN_TEXT_ITALIC			0x0002
#define TN_TEXT_UNDERLINE		0x0004

#define IDT_HIDDEN		0
#define IDT_APPEARING		1
#define IDT_WAITING		2
#define IDT_DISAPPEARING	3

#define TASKBAR_ON_TOP		1
#define TASKBAR_ON_LEFT		2
#define TASKBAR_ON_RIGHT	3
#define TASKBAR_ON_BOTTOM	4

// CTaskbarNotifier

class CTaskbarNotifier : public CWnd
{
	DECLARE_DYNAMIC(CTaskbarNotifier)

public:
	CTaskbarNotifier();
	virtual ~CTaskbarNotifier();

	int Create(CWnd *pWndParent);
	virtual void Show(LPCTSTR szCaption,DWORD dwTimeToShow=500,DWORD dwTimeToStay=5000,DWORD dwTimeToHide=500,int nIncrement=1);
	virtual void Hide();
	virtual void Disappearing();
	BOOL SetSkin(UINT nBitmapID,short red=-1,short green=-1,short blue=-1);
	BOOL SetSkin(LPCTSTR szFileName,short red=-1,short green=-1,short blue=-1);
	virtual void SetTextFont(LPCTSTR szFont,int nSize,int nNormalStyle,int nSelectedStyle);
	void SetTextColor(COLORREF crNormalTextColor,COLORREF crSelectedTextColor);
	void SetTextRect(RECT rcText);
	
	CWnd *m_pWndParent;
	
	CFont m_myNormalFont;
	CFont m_mySelectedFont;
	COLORREF m_crNormalTextColor;
	COLORREF m_crSelectedTextColor;
	HCURSOR m_hCursor;
	
	CBitmap m_biSkinBackground;
	HRGN m_hSkinRegion;
	CRect m_rcText;
	int m_nSkinWidth;
	int m_nSkinHeight;

	CString m_strCaption;
	BOOL m_bMouseIsOver;
	int m_nAnimStatus;

 	DWORD m_dwTimeToShow;
	DWORD m_dwTimeToLive;
	DWORD m_dwTimeToHide;
	DWORD m_dwDelayBetweenShowEvents;
	DWORD m_dwDelayBetweenHideEvents;
	int m_nStartPosX;
	int m_nStartPosY;
	int m_nCurrentPosX;
	int m_nCurrentPosY;
	int m_nTaskbarPlacement;
	int m_nIncrement;

	int m_nCurrentSizeX;
	int m_nCurrentSizeY;

	
protected:
	BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	HRGN GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM w, LPARAM l);
	afx_msg LRESULT OnMouseLeave(WPARAM w, LPARAM l);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
};


