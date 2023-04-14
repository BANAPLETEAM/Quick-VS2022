#pragma once
#include "afxcmn.h"

// CShareReportRateLogDlg ��ȭ �����Դϴ�.

class CShareReportRateLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportRateLogDlg)

public:
	CShareReportRateLogDlg(CWnd* pParent = NULL); 
	CShareReportRateLogDlg(CWnd* pParent,long nShareCode1A,long nShareCode1B);   // ǥ�� �������Դϴ�.
	virtual ~CShareReportRateLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_REPORT_RATE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nShareCode1A;
	long m_nShareCode1B;
	virtual BOOL OnInitDialog();
public:
	CListCtrl m_RateLog_List;
	void RefreshLogList();
};
