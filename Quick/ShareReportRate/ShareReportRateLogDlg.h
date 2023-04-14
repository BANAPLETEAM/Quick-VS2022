#pragma once
#include "afxcmn.h"

// CShareReportRateLogDlg 대화 상자입니다.

class CShareReportRateLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportRateLogDlg)

public:
	CShareReportRateLogDlg(CWnd* pParent = NULL); 
	CShareReportRateLogDlg(CWnd* pParent,long nShareCode1A,long nShareCode1B);   // 표준 생성자입니다.
	virtual ~CShareReportRateLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REPORT_RATE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nShareCode1A;
	long m_nShareCode1B;
	virtual BOOL OnInitDialog();
public:
	CListCtrl m_RateLog_List;
	void RefreshLogList();
};
