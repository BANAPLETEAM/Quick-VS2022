#pragma once
#include "afxwin.h"


// CChargeForRiderDlg 대화 상자입니다.

class CChargeForRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderDlg)

public:
	CChargeForRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeForRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_FOR_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChargeForBtn();
	afx_msg void OnBnClickedCancelBtn();
	CEdit m_edtCompany;
	CEdit m_edtRNo;
	CEdit m_edtName;
	CEdit m_edtCharge;
	CEdit m_edtEtc;

	long m_nCharge;
	CString m_strEtc;
	CString m_strCompany;
	CString m_strRNo;
	CString m_strName;
protected:
	virtual void OnOK();
};
