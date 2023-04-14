#pragma once


// CMsgConnListDlg ��ȭ �����Դϴ�.

#define WM_CLOSE_MSG_CONN_LIST_DLG	WM_USER + 681


class CMsgConnListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMsgConnListDlg)

public:
	CMsgConnListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgConnListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSG_CONN_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CWnd *m_pParentWnd;
	CListCtrl m_List;
	HANDLE m_hKillEvent;

	CButton m_RefreshCheck;
	CQSocket *m_pSocket;
	UINT m_nConnListType;

public:
	afx_msg void OnBnClickedCommBtn();
	virtual BOOL OnInitDialog();

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	CListCtrl *GetListCtrl() { return &m_List; }

	void RefreshConnList();
	UINT RefreshProc(LPVOID lParam);


	static int staticRefreshProc(CMsgConnListDlg *app)
		{ return app->RefreshProc((LPVOID)app); }

	afx_msg void OnTimer(UINT nIDEvent);

	void SetSocket(CQSocket *pSocket) { m_pSocket = pSocket;}
	void SetConnListType(UINT nStateType) { m_nConnListType = nStateType; }


};
