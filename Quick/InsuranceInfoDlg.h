#pragma once
#include "afxwin.h"


// CInsuranceInfoDlg ��ȭ �����Դϴ�.

class CInsuranceInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CInsuranceInfoDlg)

public:
	CInsuranceInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsuranceInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INSURANCE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_sInsCompany;
	CString m_sInsNumber;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
