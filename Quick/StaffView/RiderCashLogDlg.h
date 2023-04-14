#pragma once


// CRiderCashLogDlg 대화 상자입니다.

class CRiderCashLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderCashLogDlg)

public:
	CRiderCashLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderCashLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_CASH_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	long m_nRNo;
	CString m_strRName;
	CXTPListCtrl2 m_lstReport;
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
