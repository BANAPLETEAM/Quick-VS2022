#pragma once

// CPayCashDlg ��ȭ �����Դϴ�.

class CPayCashDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPayCashDlg)

public:
	CPayCashDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPayCashDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PAY_CASH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
		
public:
	CString m_strInfo;
	CString m_strEMail;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	virtual BOOL OnInitDialog();

	CButton m_chk1;
	CButton m_chk2;

	long m_nType;
};
