#pragma once
#include "afxwin.h"
#include "SMSEditCtrl.h"
#include "SmsComboBox.h"
// CRiderSMSDlg ��ȭ �����Դϴ�.

class CRiderSMSDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderSMSDlg)

public:
	CRiderSMSDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderSMSDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_SMS_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();


public:
	CString m_strRiderPN;
	CString m_strMsg;
	CString m_strCount;

	CSMSEditCtrl  m_MsgEdit;
	CMyStatic m_CountStatic;

	CSmsComboBox m_cmbPhone;

	CString m_strRecvPhone;

public:
	afx_msg void OnEnChangeMsgEdit();
	virtual BOOL OnInitDialog();

	BOOL SendPDAMsg(int nItem);
	BOOL SendRiderSMS(int nItem);

	CString m_sBarance;
	CButton m_btnConfirm;
	long	m_nCompany;

	CString m_sSMSCount;
};


//#pragma once
//#include "afxwin.h"
//#include "FocusEditCtrl.h"
//
//// CRiderSMSDlg ��ȭ �����Դϴ�.
//
//class CRiderSMSDlg : public CDialog
//{
//	DECLARE_DYNAMIC(CRiderSMSDlg)
//
//public:
//	CRiderSMSDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
//	virtual ~CRiderSMSDlg();
//
//	// ��ȭ ���� �������Դϴ�.
//	enum { IDD = IDD_RIDER_SMS_DLG };
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
//
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnBnClickedOk();
//
//
//public:
//	CString m_strRiderPN;
//	CString m_strRecvPN;
//	CString m_strMsg;
//	CString m_strCount;
//
//	CFocusEditCtrl m_MsgEdit;
//	CStatic m_CountStatic;
//
//public:
//	afx_msg void OnEnChangeMsgEdit();
//	virtual BOOL OnInitDialog();
//
//	BOOL SendPDAMsg(int nItem);
//	BOOL SendRiderSMS(int nItem);
//
//	CString m_sBarance;
//	CButton m_btnConfirm;
//	long	m_nCompany;
//
//	CString m_sSMSCount;
//	afx_msg void OnBnClickedOk7();
//};
