#pragma once


// CImageHtmlView HTML 뷰입니다.

class CImageHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CImageHtmlView)

protected:
	CImageHtmlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CImageHtmlView();

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

	CString m_strUrl;
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


