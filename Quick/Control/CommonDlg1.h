#pragma once
#include "afxwin.h"


// CCommonDlg1 ��ȭ �����Դϴ�.

class CCommonDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDlg1)

public:
	CCommonDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommonDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMMON_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CFlatEdit2 m_edtEdit;
	CString m_strEdit;
	virtual BOOL OnInitDialog();
};
