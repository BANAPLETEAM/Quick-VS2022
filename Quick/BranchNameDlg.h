#pragma once


// CBranchNameDlg ��ȭ �����Դϴ�.

class CBranchNameDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchNameDlg)

public:
	CBranchNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBranchNameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRANCH_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void SetEditCompanyInfo(BOOL bEditCompany);

	CString m_strBranchCode;
	CString m_strBranchName;
	CString m_strOfficePhone;
	CString m_strPreOfficePhone;
	CString m_strOfficePhoneSMS;
	CString m_strClientSymbol;
	CString m_strClientDisplayName;
	CString m_strClientDisplayPhone;
	long m_nCompanyCode;

	CString m_strTel;
	CString m_strTelSMS;
	virtual BOOL OnInitDialog();
};
