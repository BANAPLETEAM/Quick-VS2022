#pragma once


// CRiderCashLogDlg ��ȭ �����Դϴ�.

class CRiderCashLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderCashLogDlg)

public:
	CRiderCashLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderCashLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_CASH_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
