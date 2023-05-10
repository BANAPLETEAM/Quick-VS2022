#pragma once


#include "MyStaticRed.h"
#include "MyStaticBlue.h"
#include "MyStaticGreen.h"

// CNewCustomerSmsDlg ��ȭ �����Դϴ�.

class CNewCustomerSmsDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CNewCustomerSmsDlg)

public:
	CNewCustomerSmsDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNewCustomerSmsDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NEW_CUSTOMER_SMS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_wndReport;
	CXTPGridRecords *m_XTPGridRecords;
	void RefreshList();
	void InitCount();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedChangeMentBtn();
	afx_msg void OnBnClickedCloseBtn();
	CEdit m_edtMsg;
	CMyStaticRed m_stcTotal;
	CMyStaticRed m_stcSend;
	CMyStaticBlue m_stcCount;
	afx_msg void OnEnChangeMsgEdit();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CString m_strMent;
	CMyStaticGreen m_stcCallBack;
	long m_nCount;
	long m_nSendCount;
	CButton m_chkAll;
	CButton m_chkNotAll;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
};
