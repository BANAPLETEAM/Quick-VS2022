#pragma once

#define WM_USER_NAVIGATE	WM_USER + 0x500

// CFAQHtmlView HTML 뷰입니다.

class CFAQHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CFAQHtmlView)

protected:
	CFAQHtmlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CFAQHtmlView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LONG OnUserNavigate(WPARAM wParam, LPARAM lParam);

	CString m_strURL;
	BOOL m_bRun;

};


