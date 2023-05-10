#pragma once


// CRecvCidDlg 대화 상자입니다.


#define WM_CLOSE_RECV_CID_DLG	WM_USER + 683

class CRecvCidDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRecvCidDlg)

public:
	CRecvCidDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecvCidDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECV_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
