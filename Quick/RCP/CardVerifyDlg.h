#pragma once



#include "afxwin.h"

// CCardVerifyDlg 대화 상자입니다.

typedef struct {
	long nID;
	CString strCardCompanyName;
	CString strCard4Digits; 
} ST_BILL_KEY;

class CCardVerifyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCardVerifyDlg)

public:
	CCardVerifyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCardVerifyDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CARD_VERIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVerifyBtn();
	afx_msg void OnBnClickedAcceptBtn();
	afx_msg void OnBnClickedRequestCancelBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedVerifyBtn2();

public:
	CBranchInfo *m_pBi;
	static CMkDatabase* m_pMkCard;
	ST_CARD_INFO m_stCardInfo;

	long m_nPreProcess;

	CString m_strTransactionNumber;
	CString m_strBCHeadBranchCode;

	CString m_strEMail;

	CComboBox m_cmbCardType;
	CFlatEdit2 m_edtPhone;
	CXTMaskEdit m_edtCardNumber;
	CFlatEdit2 m_edtCustomer;
	CFlatEdit2 m_edtBalance;
	CFlatEdit2 m_edtCardCharge;
	CFlatEdit2 m_edtCardCharge2;
	CButton m_btnAccept;
	CButton m_btnRequestCancel;

	int m_nCardType;
	CString m_strPhone;
	CString m_strCardNumber;
	CString m_strCustomer;
	CString m_strBalance;
	CString m_strCardCharge;
	CString m_strOrderPhone;

	int m_nOKCardCharge;
	CString m_strOKTranNumber;
	BOOL m_bAcceptCanceled;

	CFlatEdit2 m_edtTran;

	long m_nTNo;
	long m_nRiderCompany;
	long m_nRNo;
	long m_nCharge;
	long m_nCNo;

	CWnd *m_pParent;
	BOOL m_bAgreeCardSave;
public:
	void SaveEMail();
	void MoveDialog();
	void InsertCardLog(BOOL bPay);
	BOOL CheckCardPayOk(CString &strErrorMsg);
	void InitCombo();
	void GetValidDate(CString &strMM, CString &strYY);
	void InitUseageCardHistory();
	BOOL VerifyCustomer(BOOL bShowMsg = TRUE);
	BOOL VerifyCardNumber(BOOL bShowMsg = TRUE);
	void DeleteBillkeyCombo();
	static BOOL GetCardSocket(const char* szIP, UINT uPort);
	long GetBillKey();
	CString GetBill4Digits();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmbMonth;
	CComboBox m_cmbYear;
	afx_msg void OnBnClickedAcceptBtn2();
	CComboBox m_cmbBillKey;
	afx_msg void OnCbnSelchangeBillKeyCombo();
	CFlatEdit2 m_edtCardNumber2;
	CButton m_btnAccept2;
	afx_msg void OnBnClickedDeleteCardBtn();
	afx_msg void OnBnClickedShowHistoryBtn();
	afx_msg void OnBnClickedSendSmsCheck();
	CButton m_chkSendSms;
	CEdit m_edtEMail;
	afx_msg void OnCbnSelchangeFeeTypeCombo();
	afx_msg void OnCbnSelchangeFeeTypeCombo2();
	void RefreshResultCharge(BOOL bUp);
	BOOL UpdateFeeTypeForCard(BOOL bUp);
	CComboBox m_cmbFeeType;
	CComboBox m_cmbFeeType2;
	afx_msg void OnBnClickedAgreeCardSaveCheck();

	CButton m_chkAgreeCardSave;
	BOOL GetAgreeCardSave();
	static void SetAgreeCardSave(BOOL bAgree, long nCNo);
};
