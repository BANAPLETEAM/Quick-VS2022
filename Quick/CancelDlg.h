#pragma once


// CCancelDlg 대화 상자입니다.

#define MAX_CANCEL_COUNT 5
#define MAX_CANCEL_TYPE	20

class CCancelDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCancelDlg)

public:
	CCancelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCancelDlg();

// 대화 상자 데이터입니다.
//	enum { IDD = IDD_CANCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEtcEdit();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedMentBtn();
	afx_msg void OnBnClickedMentBtn2();
	afx_msg void OnBnClickedSmsCustomerBtn();
	afx_msg void OnBnClickedSmsCustomerBtn2();

	void MakePenaltyMin();
	void MakeRiderCancelCount();
	void SetPenalty(int nID);
	void SendCustomerSms();
	void GetCusSMSInfo();

	CFlatEdit2 m_edtPenaltyMin;
	CFlatEdit2 m_edtPenaltyFee;
	CFlatEdit2 m_edtEtc;
	CFlatEdit2 m_edtCusCancelText;
	CFlatEdit2 m_edtCusCancelCallBack;
	CFlatEdit2 m_edtRiderShotageText;
	CFlatEdit2 m_edtRiderShotageCallBack;

	CButton m_btnSmsCustomer;	
	CButton m_btnRiderShotageSms;
	CButton m_chkAllocateLimit;
	CButton m_btnSms;
	CButton m_chkCancelPenaltyCharge;

	CButton m_chkChangeToWait;
	BOOL m_bChangeToWait;

	CStatic m_stcRiderInfo;

	long m_nTNo;
	long m_nCompany;
	long m_nOrderCompany;
	int m_nCancelType;
	
	BOOL m_bAllocateLimit;	
	BOOL m_bCancelPenaltyCharge;
	BOOL m_bSendCustomer;

	long m_nPenaltyMin[MAX_CANCEL_COUNT][MAX_CANCEL_TYPE];
	long m_nPenaltyFee[MAX_CANCEL_COUNT][MAX_CANCEL_TYPE];

	CString m_strCustomerPhone;
	CString m_strPenaltyCharge;
	CString m_strPenaltyMin;
	CString m_strEtc;
	CStringArray *m_psaCancel;
};
