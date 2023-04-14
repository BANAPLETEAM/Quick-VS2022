#pragma once
#include "afxwin.h"


// CShareTransferRequsetDetailDlg 대화 상자입니다.

class CShareTransferRequestDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTransferRequestDetailDlg)

public:
	CShareTransferRequestDetailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareTransferRequestDetailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_TRANSFER_REQUEST_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_CompanyEdt;
	CEdit m_DateEdt;
	CEdit m_ChargeEdt;
	CEdit m_MemoEdt;
	CString m_sCompany;
	CString m_sDate;
	CString m_sCharge;
	CString m_sMemo;
};
