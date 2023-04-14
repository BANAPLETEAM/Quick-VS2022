#pragma once
#include "afxwin.h"


// CSearchCustomerInsungRcpDlg ��ȭ �����Դϴ�.

class CSearchCustomerInsungRcpDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchCustomerInsungRcpDlg)

public:
	CSearchCustomerInsungRcpDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchCustomerInsungRcpDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_CUSTOMER_INSUNG_RCP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	virtual BOOL OnInitDialog();
	void RefreshCNo();
	CMyStaticTri m_stcBranch;
	CMyStaticTri m_stcName;
	CMyStaticTri m_stcTel;
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CComboBox m_cmbBranch;
	CEdit m_edtName;
	CEdit m_edtTel;
	CXTPListCtrl2 m_lstCustomer;
	void RefreshList();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void RefreshSub(CMkRecordset *rs);


	long m_nCNo;
	long m_nTelID;
};
