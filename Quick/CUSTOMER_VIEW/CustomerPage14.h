#pragma once

#include "afxdtctl.h"
#include "afxwin.h"

typedef struct{
	long nCNo;
	long nID;
	CString strCName;
	CString strTel1;
	CString strTel2;
	CString strLocation;
	COleDateTime dtRegister;
	COleDateTime dtLastUse;
	long nType;
	COleDateTime dtLastSentSMS;
	BOOL bNoSMS;
	long nAdvertCount;
	COleDateTime dtLastSentAdvertSMS;
}HUMAN_CUSTOMER_STARUCT;

typedef map<long, HUMAN_CUSTOMER_STARUCT> HUMAN_CUSTOMER_MAP;

// CCustomerPage14 대화 상자입니다.

class CCustomerPage14 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage14)

public:
	CCustomerPage14();
	virtual ~CCustomerPage14();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE14 };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	afx_msg void OnClickedSearchBtn();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnSendSms();
	afx_msg void OnDeleteCustomer();

	virtual void OnInitialUpdate();
	void	FromAfterRefreshList();
	void	TermAfterRefresh();

	DECLARE_MESSAGE_MAP()

protected:
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpRegisterFrom;
	CXTPListCtrl2	m_List;

public:
	HUMAN_CUSTOMER_MAP m_map;

	CButton m_OneBtn;
	CButton m_TwoBtn;
	CButton m_ThreeBtn;
	CButton m_FourBtn;
	CButton m_btnSearch;
	CEdit m_editUseCount;


	afx_msg void OnBnClickedOneBtn();
	afx_msg void OnBnClickedTwoBtn();
	afx_msg void OnBnClickedThreeBtn();
	afx_msg void OnBnClickedFourBtn();
	CButton m_rdoFromAfter;
	CButton m_rdoFromTerm;
	CDateTimeCtrl m_TermAfterFrom;
	CDateTimeCtrl m_TermAfterTo;

	CButton m_chkOneUse;

	CComboBox m_cmbType;
	CComboBox m_PhoneCmb;
	CComboBox m_NosmsCmb;
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnCbnSelchangePhoneCombo();
	afx_msg void OnCbnSelchangeNosmsCombo();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
