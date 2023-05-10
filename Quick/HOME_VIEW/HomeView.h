#pragma once


// CHomeView ���Դϴ�.

class CHomeView : public CView
{
	DECLARE_DYNCREATE(CHomeView)

protected:
	CHomeView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CHomeView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


