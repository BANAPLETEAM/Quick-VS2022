#pragma once


// CImageHtmlView HTML ���Դϴ�.

class CImageHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CImageHtmlView)

protected:
	CImageHtmlView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CImageHtmlView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	CString m_strUrl;
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


