#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CTimeLimitDlg 대화 상자입니다.

class CTimeLimitDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTimeLimitDlg)

public:
	CTimeLimitDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTimeLimitDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TIME_LIMIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtLimitDate;
	COleDateTime m_dtLimitTime;
	COleDateTime m_dtDate;
	CComboBox m_cmbTimeLimit;
	CString m_sMinute;
	afx_msg void OnBnClickedOkBtn();
	virtual BOOL OnInitDialog();
};
