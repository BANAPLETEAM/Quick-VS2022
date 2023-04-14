#pragma once
#include "afxwin.h"


// CLoadInsuranceDlg ��ȭ �����Դϴ�.

class CLoadInsuranceDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLoadInsuranceDlg)

public:
	CLoadInsuranceDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLoadInsuranceDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOAD_INSURANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveButton();
	CString m_strSSN;
	CString m_strCarNo;
	long m_nCarType;
	long m_nCompany;
	long m_nRNo;
	CString m_strName;
	CString m_strSID;
	virtual BOOL OnInitDialog();
	void GetLoadInsurancePremiun(long nCarType);

	CFlatEdit2 m_edtCompanyName;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtSSN;
	CFlatEdit2 m_edtSID;
	CFlatEdit2 m_edtInsuranceStart;
	CFlatEdit2 m_edtInsuranceCompany;
	CFlatEdit2 m_edtCarNumber;
	CFlatEdit2 m_edtMonthlyPremium;
	CFlatEdit2 m_edtDailyPremium;
	CFlatEdit2 m_edtInsuranceID;
	afx_msg void OnBnClickedCloseButton();
	CComboBox m_cmbCarType;
	CMyStatic m_stcHelp;

	BOOL IsLoadInsuranceRegister(CString strSSN, CLoadInsuranceData *st);
	void RefreshDlg(CLoadInsuranceData *st);
	afx_msg void OnBnClickedReleaseButton();
	BOOL RiderInsInfo(CLoadInsuranceData *st, BOOL bInsert = FALSE);
	afx_msg void OnBnClickedClauseButton();
};
