#pragma once


// CRecvCidDlg ��ȭ �����Դϴ�.


#define WM_CLOSE_RECV_CID_DLG	WM_USER + 683

class CRecvCidDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRecvCidDlg)

public:
	CRecvCidDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecvCidDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECV_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

protected:
	CListCtrl m_List;
	CWnd *m_pParentWnd;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	CRITICAL_SECTION m_csListLock;
protected:
	virtual void OnOK();
	virtual void OnCancel();


public:
	void AddRecvCid(CString strPhone, DWORD dwData);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	void RemoveRecvCid(CString strPhone, CString strGroup, CString strChannel);
};
