#pragma once
#include "afxwin.h"


// CElapseLimitDlg ��ȭ �����Դϴ�.

class CElapseLimitDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CElapseLimitDlg)

public:
	CElapseLimitDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CElapseLimitDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ELAPSE_LIMIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
