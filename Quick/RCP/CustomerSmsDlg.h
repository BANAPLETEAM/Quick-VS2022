#pragma once


#include "afxwin.h"
#include "MyCheckButton.h"
// CCustomerSmsDlg 대화 상자입니다.

class CCustomerSmsDlg : public CMyDialog //CDialog
{
	DECLARE_DYNAMIC(CCustomerSmsDlg)

public:
	CCustomerSmsDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCustomerSmsDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_SMS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEditMentBtn();
	afx_msg void OnSendSms();
	afx_msg void OnEnChangeMentEdit();
	afx_msg void OnBnClickedCtypeCheck1();
	afx_msg void OnBnClickedCtypeCheck2();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeInDayCombo();
	afx_msg void OnCbnSelchangeDmSentCombo();	
	afx_msg void OnCbnSelchangeNewCustomerCombo();
	afx_msg void OnCbnSelchangeDmCountCombo();
	afx_msg void OnCbnSelchangeSendCountCombo();
	afx_msg void OnBnClickedReservationCancelBtn();
	afx_msg void OnBnClickedStateButton();
	afx_msg void OnBnClickedCancel();

	void MakeCustomerList();
	void CheckListCondition();

	CListCtrl m_List;
	CXTPListCtrl2 *m_pSourceList;

	CFlatEdit2 m_edtMent;
	CFlatEdit2 m_edtCompanyPhone;

	CButton m_btnConfirm;
	CButton m_btnCancel;
	CButton m_btnReservationCancel;
	CButton m_btnSMSState;
	CButton m_btnSMSMent;

	CComboBox m_cmbInDay;
	CComboBox m_cmbDmCount;
	CComboBox m_cmbDMSent;
	CComboBox m_cmbNewCustomer;	
	CComboBox m_cmbSendCount;

	CMyCheckButton m_CTypeCheck1;
	CMyCheckButton m_CTypeCheck2;
	CMyCheckButton m_DivisionCheck;

	CStatic m_stcCount;
	CStatic m_stcBranch;
	CStatic m_stcLength;

	int m_nInDay;
	int m_nPhoneCol;
	int m_nCTypeCol;
	int m_nNotWantedCol;
	int m_nLastSentCol;
	int m_nDMLastSentCol;
	int m_nNewCustomerCol;
	int m_nDMCount;

	int m_nType;
	int m_nCompany;
	int m_nUncheckedItem;

	BOOL m_bNotified;

	COleDateTime m_dtDate;
	COleDateTime m_dtTime;
	COleDateTime m_dtDateTime;
	CDateTimeCtrl m_dtpTime;
	CDateTimeCtrl m_dtpDate;

	CString m_m_strCompanyPhone;
	CString m_strBalance;
	CString m_strSMSCount;
	CString m_strMent;
	CString m_strCompanyPhone;
};
