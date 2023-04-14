#pragma once

// CPayCashDlg 대화 상자입니다.

class CPayCashDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPayCashDlg)

public:
	CPayCashDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPayCashDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAY_CASH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
