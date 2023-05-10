#pragma once
#include "afxwin.h"


// CSearchCustomerInsungRcpDlg 대화 상자입니다.

class CSearchCustomerInsungRcpDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchCustomerInsungRcpDlg)

public:
	CSearchCustomerInsungRcpDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchCustomerInsungRcpDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_CUSTOMER_INSUNG_RCP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
