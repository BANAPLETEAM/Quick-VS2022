#pragma once


// CHalfInsertFixedDepositDlg 대화 상자입니다.

class CHalfInsertFixedDepositDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CHalfInsertFixedDepositDlg)

public:
	CHalfInsertFixedDepositDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHalfInsertFixedDepositDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HALF_INSERT_FIXED_DEPOSIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCharge;
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
};
