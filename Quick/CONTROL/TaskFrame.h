#pragma once

//#include "MyXTPReportView.h"
class CK2ReportView;


class CTaskFrame : public CXTPFrameWnd
{
public:
	CTaskFrame();        
	CTaskFrame(CXTPListCtrl2 *pDataWnd);         // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

	DECLARE_DYNCREATE(CTaskFrame)
protected:
	
	virtual ~CTaskFrame();

	
	//void OnSetDataBoxCtrl(CXTPListCtrl2 *pDataBox);
protected:
	DECLARE_MESSAGE_MAP()

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;	
	CXTPListCtrl2 *m_pParentWnd;

	// Generated message map functions
public:
	//{{AFX_MSG(CTaskListFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	CK2ReportView* m_pOwnerView;

protected:
};


