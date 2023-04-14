#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CWithdrawManualDlg 대화 상자입니다.

class CWithdrawManualDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWithdrawManualDlg)

public:
	CWithdrawManualDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWithdrawManualDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WITHDRAW_MANUAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
