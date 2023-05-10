#pragma once

#include "Explorer.h"
// CWebPrintDlg 대화 상자입니다.

class CWebPrintDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebPrintDlg)

public:
	CWebPrintDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebPrintDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_PRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_Explorer;
	CString m_sUrl;
	BOOL m_bDelete;
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrintBtn();
};
