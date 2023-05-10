#pragma once


// CReportRiderView 뷰입니다.


class CReportRiderView : public CView
{
	DECLARE_DYNCREATE(CReportRiderView)

protected:
	CReportRiderView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportRiderView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg LONG OnBranchClickEvent(UINT nBranch, LPARAM lParam);

	void FirstRefresh();
protected:
	CXTPTabControl m_wndTabControl;


};


