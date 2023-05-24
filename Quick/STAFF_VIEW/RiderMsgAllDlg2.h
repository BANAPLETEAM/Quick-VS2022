#pragma once

#include "SMSEditCtrl.h"
#include "SmsComboBox.h"

// CRiderMsgAllDlg2 대화 상자입니다.

class CRiderMsgAllDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderMsgAllDlg2)

public:
	CRiderMsgAllDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderMsgAllDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_SMS_ALL_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMentBtn();
	afx_msg void OnEnChangeMsgEdit();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedWorkStopCheck();
	virtual BOOL OnInitDialog();

	CListCtrl m_List;
	CXTPListCtrl2 *m_List2;

	CSMSEditCtrl  m_edtMsg;

	CStatic m_stcBalance;
	CStatic m_stcSmsCount;
	CStatic m_stcMsgLen;

	long m_nCompany;

	BOOL m_bAllRider;
	BOOL m_bIntegrated;

	CString m_strMessageMent;
	CButton m_chkWorkStop;

	CSmsComboBox m_cmbPhone;
};
