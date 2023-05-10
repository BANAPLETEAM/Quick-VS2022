#pragma once


// CRiderDepositMsgDlg 대화 상자입니다.

class CRiderDepositMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositMsgDlg)

public:
	CRiderDepositMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_DEPOSIT_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedCloseBtn();
	CString m_sMsg;
	virtual BOOL OnInitDialog();
};
