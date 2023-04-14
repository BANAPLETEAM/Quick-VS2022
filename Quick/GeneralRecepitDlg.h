#pragma once

// CGeneralReceiptDlg ��ȭ �����Դϴ�.

class CGeneralReceiptDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CGeneralReceiptDlg)

public:
	CGeneralReceiptDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGeneralReceiptDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GENERAL_RECEIPT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
