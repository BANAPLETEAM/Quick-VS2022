#pragma once
#include "afxwin.h"


// CGeneralAppRegisterDlg2 대화 상자입니다.

class CGeneralAppRegisterDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CGeneralAppRegisterDlg2)

public:
	CGeneralAppRegisterDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGeneralAppRegisterDlg2();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERAL_APP_REGISTER_DLG2 };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	virtual BOOL OnInitDialog();

	long m_nIndex;
	long m_nState;

	CEdit m_edtAppName;
	CEdit m_edtMainTel;
	CEdit m_edtExplan;
	CEdit m_edtAppManagerName;
	CEdit m_edtAppManagerPosition;
	CEdit m_edtAppManagerTel;
	CEdit m_edtTaxManagerName;
	CEdit m_edtEMail;
	CEdit m_edtCompanyName;
	CEdit m_edtBizNumber;
	CEdit m_edtBizType1;
	CEdit m_edtBizType2;
	CEdit m_edtCompanyAddr;
	afx_msg void OnBnClickedRegisterBtn();
	void RefreshDlg();
	CButton m_btnRegister;
	CString m_strBizLicenseUrl;
	afx_msg void OnBnClickedUploadBtn();
	CEdit m_edtTaxManagerTel;
	CEdit m_edtShortUrl;
	CStatic m_stcState;

	CEdit m_edtGoogleID;
	CEdit m_edtGooglePW;
	CEdit m_edtBizOwner;
	CEdit m_edtAppManagerEMail;

	CButton m_chkAndroid;
	CButton m_chkIOS;	
	CEdit m_edtAppleID;	
	CEdit m_edtApplePW;	

	void SetAppType(long nType);
	long GetAppType();
};
