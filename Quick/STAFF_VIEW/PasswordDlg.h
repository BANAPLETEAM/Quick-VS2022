#pragma once
#include "afxwin.h"

// CPasswordDlg ��ȭ �����Դϴ�.

class CPasswordDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPasswordDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CFlatEdit2 m_edtOriPW;
	CFlatEdit2 m_edtNewPW;
	CFlatEdit2 m_edtPWEdit2;

	CString m_strOriPW;
	CString m_strNewPW1;
	CString m_strNewPW2;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
