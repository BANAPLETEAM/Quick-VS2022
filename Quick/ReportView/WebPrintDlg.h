#pragma once

#include "Explorer.h"
// CWebPrintDlg ��ȭ �����Դϴ�.

class CWebPrintDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebPrintDlg)

public:
	CWebPrintDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebPrintDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEB_PRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_Explorer;
	CString m_sUrl;
	BOOL m_bDelete;
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrintBtn();
};
