#pragma once


// CRiderDepositMsgDlg ��ȭ �����Դϴ�.

class CRiderDepositMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositMsgDlg)

public:
	CRiderDepositMsgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderDepositMsgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_DEPOSIT_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedCloseBtn();
	CString m_sMsg;
	virtual BOOL OnInitDialog();
};
