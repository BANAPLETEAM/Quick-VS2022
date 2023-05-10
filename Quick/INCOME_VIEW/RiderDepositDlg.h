#pragma once


// CRiderDepositDlg 대화 상자입니다.

class CRiderDepositDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositDlg)

public:
	CRiderDepositDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_DEPOSIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strDeposit;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
