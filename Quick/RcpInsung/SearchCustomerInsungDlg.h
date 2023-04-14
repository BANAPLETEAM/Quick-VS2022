#pragma once
#include "afxwin.h"


// CSearchCustomerInsungDlg 대화 상자입니다.

class CSearchCustomerInsungDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchCustomerInsungDlg)

public:
	CSearchCustomerInsungDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchCustomerInsungDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_CUSTOMER_INSUNG_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
