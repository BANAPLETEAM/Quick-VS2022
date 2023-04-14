#pragma once
#include "afxwin.h"
#include "Quick.h"

// CCertificationRegiDlg 대화 상자입니다.

class CCertificationRegiDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCertificationRegiDlg)

public:
	CCertificationRegiDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCertificationRegiDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CERTIFICATION_REGI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_sBusinessNO;
	CString m_sBusinessName;
	CString m_sBusinessPresident;
	CString m_sBusinessAddress;
	CString m_sBusinessCondition;
	CString m_sBusinessCategory;

	CString m_sBusinessManager;
	CString m_sBusinessEmail;
	CComboBox m_cmbBillRegi;


	afx_msg void OnBnClickedCeritficationInstallBtn();
	afx_msg void OnBnClickedModifyBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCertificationRegisterBtn();
	void LoadData();
	BOOL m_bIntegrated;
	long m_nCompany;
	CButton m_chkAllBranch;
	CComboBox m_cmbBranch;
	afx_msg void OnCbnSelchangeCombo1();
};
