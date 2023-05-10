#pragma once


// CIntercallNoticeDlg 대화 상자입니다.

class CIntercallNoticeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CIntercallNoticeDlg)

public:
	CIntercallNoticeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIntercallNoticeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INTERCALL_NOTICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	void RefreshHistory();

	CListCtrl m_List;
	CEdit m_SendEdit;
	CEdit m_TitleEdit;
	CString m_strSend;
	CString m_strTitle;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
