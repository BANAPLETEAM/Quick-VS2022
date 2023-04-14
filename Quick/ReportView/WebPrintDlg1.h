#pragma once
#include "explorer.h"


// CWebPrintDlg1 대화 상자입니다.

class CWebPrintDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CWebPrintDlg1)

public:
	CWebPrintDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebPrintDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_PRINT_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strUrl;
public:
	virtual BOOL OnInitDialog();
	void PrintBtn(BOOL bPrint);
	CExplorer m_ex;
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnBnClickedPrintPreBtn();
};
