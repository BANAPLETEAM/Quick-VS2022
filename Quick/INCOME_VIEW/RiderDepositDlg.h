#pragma once


// CRiderDepositDlg ��ȭ �����Դϴ�.

class CRiderDepositDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositDlg)

public:
	CRiderDepositDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderDepositDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_DEPOSIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strDeposit;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
