#pragma once
//#include "afxcmn.h"
//#include "afxwin.h"

//#include "QFormView.h"
//#include "QuickPropSheet.h"
//#include "StaffPage1.h"


// CStaffViewNew 폼 뷰입니다.


class CStaffViewNew : public CView
{
	DECLARE_DYNCREATE(CStaffViewNew)


public:
	CStaffViewNew();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStaffViewNew();
	virtual void OnDraw(CDC* pDC);      
	enum { IDD = IDD_QUICK_MANAGER };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate();
	//afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:
	void FirstRefresh();
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg LONG OnBranchClickEvent(UINT nBranch, LPARAM lParam);
protected:
	CXTPTabControl m_wndTabControl;


};


