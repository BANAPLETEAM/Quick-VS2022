#pragma once


#include "Quick.h"
#include "DataBox.h"

class CSearchCustomerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchCustomerDlg)

public:
	CSearchCustomerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchCustomerDlg();

	// ��ȭ ���� �������Դϴ�.
			           
	enum { IDD = IDD_SEARCH_CUSTOMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedHistoryChargeInputBtn();
	afx_msg void OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult);		
	afx_msg void OnBnClickedSelectCustomerBtn();
	afx_msg void OnBnClickedSearchBtn();

	void ChangeCustomer();
	void Apply();

	CDataBox m_lstSearch;

	long m_nCompany;
	long m_nReturnCNo;
	long m_nReturnMemCNo;

	BOOL m_bTypeCustomerChange;

	CFlatEdit2 m_edtSearchName;
	CButton m_btnHistoryChargeInput;
	CComboBox m_cmbSearchType;

	CString m_strCNoList;
	CString m_strReturnCustomer;
	CString m_strReturnTel;
	CString m_strReturnDept;
	CString m_strReturnName;
	CString m_strReturnMemCNo;
	CString m_strReturnHP;
};
