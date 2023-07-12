#pragma once

// CFormViewDlg 대화 상자입니다.

class CFormViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CFormViewDlg)

public:
	CFormViewDlg(CWnd* pParent = NULL, BOOL bAutoDelete = TRUE);   // 표준 생성자입니다.
	virtual ~CFormViewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FORM_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CRuntimeClass *m_pObject;
	CString m_strCaption;
	CRect m_rcClient;
	int m_nStartBranch;

	CXTPDockingPaneManager m_paneManager;
	CXTPDockingPane *m_pwndPaneNetwork;
	CXTPTaskPanel *m_pwndTaskPanel;
	BOOL m_bDisableFirstRefresh;
	BOOL m_bAutoDelete;

protected:
	CXTPTabControl m_wndTabControl;
	CView *m_pView;
	CMyFormView* m_pFormView;
};
