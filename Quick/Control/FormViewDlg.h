#pragma once

// CFormViewDlg ��ȭ �����Դϴ�.

class CFormViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CFormViewDlg)

public:
	CFormViewDlg(CWnd* pParent = NULL, BOOL bAutoDelete = TRUE);   // ǥ�� �������Դϴ�.
	virtual ~CFormViewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FORM_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
