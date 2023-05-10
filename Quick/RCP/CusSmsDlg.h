#pragma once
#include "afxwin.h"


// CCusSmsDlg ��ȭ �����Դϴ�.

class CCusSmsDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCusSmsDlg)

public:
	CCusSmsDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCusSmsDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CUS_SMS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();

public:
	long m_nCompany;
	CString m_strPhone;
	CString m_strText;

protected:
	CEdit m_PhoneEdt;
	CEdit m_TextEdt;
	CStatic m_LenStatic;
	CStatic m_BranchStatic;
	

public:
	afx_msg void OnEnChangeMemoEdit();
	void UpdateTextCount();
	int m_nRiderShotage;
};
