#pragma once
#include "afxwin.h"


// CChargeForRiderTransferDlg 대화 상자입니다.

class CChargeForRiderTransferDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderTransferDlg)

public:
	CChargeForRiderTransferDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeForRiderTransferDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_FOR_RIDER_TRANSFER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitPhone();
	void InitData();
	
	CEdit m_edtCompany;
	CEdit m_edtRNo;
	CEdit m_edtName;
	CEdit m_edtCharge;
	CEdit m_edtEtc;
	CEdit m_edtAuthNumber;

	CButton m_rdoAuth1;
	CButton m_rdoAuth2;

	long m_nID;
	CButton m_btnAuth;
	
	afx_msg void OnBnClickedChargeForBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedSendSmsBtn();

	BOOL m_bSmsAuth;
	long m_nSmsID;
	afx_msg void OnBnClickedAuthBtn();
};
