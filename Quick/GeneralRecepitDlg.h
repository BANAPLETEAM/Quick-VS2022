#pragma once

// CGeneralReceiptDlg 대화 상자입니다.

class CGeneralReceiptDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CGeneralReceiptDlg)

public:
	CGeneralReceiptDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGeneralReceiptDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERAL_RECEIPT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CString m_strCompanyName;
	CString m_strCompanyOwner;
	CString m_strCompanyBizType1;
	CString m_strCompanyBizType2;
	CString m_strCompanyBizNo;
	CString m_strCompanyAddress;
	CString m_strRequestCount;
	CString m_strUseMonth;
	CString m_strOName;
	CString m_strOPhone;
	CString m_strOAddress;
	CString m_strEtc;

	afx_msg void OnBnClickedSubscriptBtn();
	afx_msg void OnBnClickedShowLogBtn();
	afx_msg void OnBnClickedCloseBtn();

	BOOL CheckData();
	BOOL CheckDupRequest();
	void RefreshDlg();

	long m_nID;
	afx_msg void OnBnClickedPreShowBtn();
};
