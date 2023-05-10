#pragma once
#include "afxwin.h"


// CElapseLimitDlg 대화 상자입니다.

class CElapseLimitDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CElapseLimitDlg)

public:
	CElapseLimitDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CElapseLimitDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ELAPSE_LIMIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CString m_sTitle;

	CString m_sElaspeLimitAllocate;
	CString m_sElapseLimitPickup;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CComboBox m_cmbElapseLimitAllocate;
	CComboBox m_cmbElapseLimitPickup;
	CStatic m_stcTitle;
};
