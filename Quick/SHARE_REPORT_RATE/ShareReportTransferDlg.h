#pragma once
#include "afxwin.h"

class CShareTranferRequestDlg;
class CShareReportRateDlg1;

// CShareReportTransferDlg 대화 상자입니다.

class CShareReportTransferDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportTransferDlg)

public:
	CShareReportTransferDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareReportTransferDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REPORT_TRANSFER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nAbilityMoney;
	int m_nToCompany;
	int m_nSMSID;

	CString m_sMoneyR;
	CString m_sMemoR;

	CShareTranferRequestDlg * m_pShareTransferRequestDlg;
	//CShareReportRateDlg1 * m_pShareReportRateDlg1;

	afx_msg void OnBnClickedAuthBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CString ReturnMoneyString(CString sMoney);

	CStatic m_SendMoneyStc;
	CEdit m_SendMoneyEdt;
	CEdit m_MemoEdt;
	CEdit m_SmsNumberEdt;
	CEdit m_AbilityMoneyEdt;
	CEdit m_CompanyNameEdt;
	afx_msg void OnEnChangeSendMoneyEdit();
};
