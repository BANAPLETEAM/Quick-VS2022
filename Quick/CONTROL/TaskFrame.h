#pragma once

//#include "MyXTPReportView.h"
class CK2ReportView;
#include "DataBox.h"

class CTaskFrame : public CXTPFrameWnd
{
public:
	CTaskFrame();        
	CTaskFrame(CDataBox *pDataWnd);         // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

	DECLARE_DYNCREATE(CTaskFrame)
protected:
	
	virtual ~CTaskFrame();

	
	//void OnSetDataBoxCtrl(CDataBox *pDataBox);
protected:
	DECLARE_MESSAGE_MAP()

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;	
	CDataBox *m_pParentWnd;

	// Generated message map functions
public:
	//{{AFX_MSG(CTaskListFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	CK2ReportView* m_pOwnerView;

protected:
};


