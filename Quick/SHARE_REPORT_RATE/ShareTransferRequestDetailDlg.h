#pragma once
#include "afxwin.h"


// CShareTransferRequsetDetailDlg ��ȭ �����Դϴ�.

class CShareTransferRequestDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTransferRequestDetailDlg)

public:
	CShareTransferRequestDetailDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareTransferRequestDetailDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_TRANSFER_REQUEST_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
