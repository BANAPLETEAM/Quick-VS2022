#pragma once


// CHalfInsertFixedDepositDlg ��ȭ �����Դϴ�.

class CHalfInsertFixedDepositDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CHalfInsertFixedDepositDlg)

public:
	CHalfInsertFixedDepositDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHalfInsertFixedDepositDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HALF_INSERT_FIXED_DEPOSIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCharge;
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
};
