#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CWithdrawManualDlg ��ȭ �����Դϴ�.

class CWithdrawManualDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWithdrawManualDlg)

public:
	CWithdrawManualDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWithdrawManualDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WITHDRAW_MANUAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCharge;
	CString m_strEtc;
	COleDateTime m_dtWithdraw;
	CEdit m_edtRealWithdraw;
	CDateTimeCtrl m_dtpDate;
	CDateTimeCtrl m_dtpTime;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_edtEtc;
};
