#pragma once
#include "afxwin.h"

// CShareReportMyRequestDetailDlg ��ȭ �����Դϴ�.

class CShareReportMyRequestDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportMyRequestDetailDlg)

public:
	CShareReportMyRequestDetailDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareReportMyRequestDetailDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_TRANSFER_MY_REQUEST_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_SeDate_Edt;
	CEdit m_SeMoney_Edt;
	CEdit m_SeMemo_Edt;
	CEdit m_ReDate_Edt;
	CEdit m_ReMoney_Edt;
	CEdit m_ReMemo_Edt;

	CString m_SeDate, m_ReDate, m_SeMoney, m_ReMoney, m_SeMemo, m_ReMemo;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
