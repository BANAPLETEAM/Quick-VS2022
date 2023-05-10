#pragma once

#include "afxwin.h"

// CShowRiderInfoDlg ��ȭ �����Դϴ�.

class CTRSInsertRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTRSInsertRiderDlg)

public:
	CTRSInsertRiderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTRSInsertRiderDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRS_INSERT_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOK();

	DECLARE_MESSAGE_MAP()
public:

public:
	CEdit m_edtCompany;
	CEdit m_edtRNo;
	CEdit m_edtRName;
	CEdit m_edtPhone;
	CEdit m_edtExten;
	CEdit m_edtPW;

	CString m_strCompany;
	CString m_strRNo;
	CString m_strRName;
	CString m_strPhone;
	CString m_strExten;
	CString m_strPW;
};
