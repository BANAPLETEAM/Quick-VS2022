#pragma once
#include "afxwin.h"


// CShareProgDlg ��ȭ �����Դϴ�.

class CShareProgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareProgDlg)

public:
	CShareProgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareProgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_PROG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
