#pragma once
#include "afxwin.h"


// CShareProgDlg 대화 상자입니다.

class CShareProgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareProgDlg)

public:
	CShareProgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareProgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_PROG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_chkTongHap;
	afx_msg void OnBnClickedOk();
	CButton m_chkYegi;
	CButton m_chkSonja;
	CButton m_chkLogi;

	long m_nShare;
};
