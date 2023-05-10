#pragma once
#include "afxwin.h"
class CShareReportAuthPhoneDlg;

// CShareReportWantTransferDlg ��ȭ �����Դϴ�.

class CShareReportWantTransferDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportWantTransferDlg)

public:
	CShareReportWantTransferDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareReportWantTransferDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_REPORT_WANT_TRANSFER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nToCompany;
	int m_nSMSID;

	CEdit m_CompanyNameEdt;
	CEdit m_SendMoneyEdt;
	CEdit m_MemoEdt;

	CString ReturnMoneyString(CString sMoney);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeSendMoneyEdit();
	virtual BOOL OnInitDialog();
	CStatic m_SendMoneyStc;
	
};
