#pragma once


// CMsgDlg ��ȭ �����Դϴ�.

class CMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMsgDlg)

public:
	CMsgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
