#pragma once

#include "SmsComboBox.h"

enum POPUP_TYPE { POPUP_CUSTOMER = 1, POPUP_ALLOCATE = 2 };
// CCustomerSmsDlg2 대화 상자입니다.

class CCustomerSmsDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerSmsDlg2)

public:
	CCustomerSmsDlg2(CWnd* pParent = NULL, int popup_type = POPUP_CUSTOMER);   // 표준 생성자입니다.
	virtual ~CCustomerSmsDlg2();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_SMS_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void RefreshList();
	void SetMsgCount();
	afx_msg void OnEnChangeMsgEdit();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSmsMentSettingButton();
	afx_msg void OnBnClickedMentSaveButton();
	afx_msg void OnBnClickedChangeCustomerCheck();
	afx_msg void OnCbnSelchangeSelectCombo();
	afx_msg void OnBnClickedReservationCheck();
	afx_msg void OnBnClickedContinueSendBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuContextEtc(UINT nFlag);

	CListCtrl m_List;

	CString m_strRecvPhone;
	POPUP_TYPE m_ePopupType;

	CDateTimeCtrl m_dtpReservationDate;
	CDateTimeCtrl m_dtpReservationTime;
	COleDateTime m_dtReservationDate;
	COleDateTime m_dtReservationTime;

	CFlatEdit2 m_edtMsg;	
	CXTFlatEdit	m_edtCustomerPN;

	CButton m_btnConfirm;
	CButton m_btnMentSet;
	CButton m_btnMentSave;
	CButton m_btnCancel;
	CButton m_btnContinueSend;
	CButton m_chkChangeTelCustomer;
	CButton m_chkReservation;

	CSmsComboBox m_cmbPhone;

	CMyStatic	m_stcCount;
	CMyStatic	m_stc1;

	CString m_strCustomerPN;
	CString m_strCustomerPN2;
	CString m_strRiderPN;
	CString m_strMsg;
	CString m_strCount;
	CString m_strBalance;
	CString m_strSMSCount;

	BOOL m_bRiderSMS;
	BOOL m_bHideCustomerPN;
	BOOL m_bReservation;

	long m_nCompany;
	int m_nContent;
	afx_msg void OnBnClickedMentBtn();
	afx_msg void OnBnClickedAllocateBtn();
};
