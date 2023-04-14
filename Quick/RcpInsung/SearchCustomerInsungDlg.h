#pragma once
#include "afxwin.h"


// CSearchCustomerInsungDlg ��ȭ �����Դϴ�.

class CSearchCustomerInsungDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchCustomerInsungDlg)

public:
	CSearchCustomerInsungDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchCustomerInsungDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_CUSTOMER_INSUNG_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	long m_nCNo;
	long m_nTelID;
	void RefreshList();
	void DeleteList();
	void SearchFilter();
	void SelectCustomer();
	CXTPListCtrl2 m_lstCustomer;
	CMkRecordset *m_pRs;
	afx_msg void OnEnChangeSearchNameEdit();
	afx_msg void OnEnChangeSearchDepartEdit();
	afx_msg void OnEnChangeSearchManagerEdit();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CFlatEdit2 m_edtSearchName;
	CFlatEdit2 m_edtSearchDepart;
	CFlatEdit2 m_edtSearchManager;
	afx_msg void OnBnClickedCloseBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
