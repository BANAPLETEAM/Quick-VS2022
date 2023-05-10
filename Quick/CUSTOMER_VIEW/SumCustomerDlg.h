#pragma once

// CSumCustomerDlg 대화 상자입니다.

class CSumCustomerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSumCustomerDlg)

public:
	CSumCustomerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSumCustomerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SUM_CUSTOMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	CXTPListCtrl2 *m_CusReport;
	CXTPListCtrl2 m_ReportAll;
	CXTPListCtrl2 m_ReportDel;
	CXTPListCtrl2 m_ReportSum;
	afx_msg void OnBnClickedDelCusBtn();
	afx_msg void OnBnClickedSumCusBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelCusBtn2();
	afx_msg void OnBnClickedSumCusBtn2();
	void RefreshList();
	BOOL SumCustomer(BOOL bGNoMove);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnNMDblclkDelReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg	void OnNMDblclkSumReport(NMHDR *pNMHDR, LRESULT *pResult);
};
