#pragma once

#include "afxwin.h"

// CShowRiderInfoDlg 대화 상자입니다.

class CTRSInsertRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTRSInsertRiderDlg)

public:
	CTRSInsertRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTRSInsertRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRS_INSERT_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
