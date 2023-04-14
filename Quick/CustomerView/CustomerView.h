#pragma once


// CCustomerView 폼 뷰입니다.

class CCustomerView : public CView
{
	DECLARE_DYNCREATE(CCustomerView)


public:
	CCustomerView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerView();
enum { IDD = IDD_CUSTOMER_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* pDC);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

public:
	void FirstRefresh();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg LONG OnBranchClickEvent(UINT nBranch, LPARAM lParam);
protected:
	CXTPTabControl m_wndTabControl;

};


