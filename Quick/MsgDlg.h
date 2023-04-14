#pragma once


// CMsgDlg 대화 상자입니다.

class CMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMsgDlg)

public:
	CMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendMsg();

	void *m_ptrItemData;
	CWnd *m_pParentWnd;

	CString m_strRecv;
	CString m_strSend;
	CString m_strTitle;

	CEdit m_RecvEdit;
	CEdit m_SendEdit;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCallingBtn();
};
