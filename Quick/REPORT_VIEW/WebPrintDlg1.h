#pragma once
#include "explorer.h"


// CWebPrintDlg1 ��ȭ �����Դϴ�.

class CWebPrintDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CWebPrintDlg1)

public:
	CWebPrintDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebPrintDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEB_PRINT_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
