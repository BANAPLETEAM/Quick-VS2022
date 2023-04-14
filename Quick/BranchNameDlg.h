#pragma once


// CBranchNameDlg 대화 상자입니다.

class CBranchNameDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchNameDlg)

public:
	CBranchNameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBranchNameDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
