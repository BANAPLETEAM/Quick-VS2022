#pragma once
#include "afxwin.h"

class CAddManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddManagerDlg)

public:
	CAddManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CFlatEdit2 m_edtManager;
	CFlatEdit2 m_edtDepart;
	CFlatEdit2 m_edtTel;
	CFlatEdit2 m_edtTel2;
	CFlatEdit2 m_edtTel3;
	CFlatEdit2 m_edtTel4;

	CButton m_btnOK;

	CString m_strManager;
	CString m_strDepart;
	CString m_strTel;
	CString m_strTel2;
	CString m_strTel3;
	CString m_strTel4;

	long m_nCNo;
	long m_nCompany;
	long m_nTelID;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedEraseBtn();
};
