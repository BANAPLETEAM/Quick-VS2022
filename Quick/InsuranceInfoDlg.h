#pragma once
#include "afxwin.h"


// CInsuranceInfoDlg 대화 상자입니다.

class CInsuranceInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CInsuranceInfoDlg)

public:
	CInsuranceInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsuranceInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INSURANCE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_sInsCompany;
	CString m_sInsNumber;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
