#pragma once
#include "afxwin.h"


// CChargeForRiderTransferDlg ��ȭ �����Դϴ�.

class CChargeForRiderTransferDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderTransferDlg)

public:
	CChargeForRiderTransferDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeForRiderTransferDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_FOR_RIDER_TRANSFER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
