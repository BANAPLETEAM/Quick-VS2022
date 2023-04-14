#pragma once
#include "afxwin.h"


// CGenerateOpenAPIRegisterDlg 대화 상자입니다.

class CGenerateOpenAPIRegisterDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGenerateOpenAPIRegisterDlg)

public:
	CGenerateOpenAPIRegisterDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGenerateOpenAPIRegisterDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERAL_OPENAPI_REGISTER_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUploadBtn();
	afx_msg void OnBnClickedRegisterBtn();

	long m_nIndex;
	long m_nState;

	CEdit m_edtManagerName;
	CEdit m_edtManagerPosition;
	CEdit m_edtManagerTel;
	CEdit m_edtManagerEMail;

	CEdit m_edtBizName;
	CEdit m_edtBizNumber;
	CEdit m_edtBizOwner;
	CEdit m_edtBizType1;
	CEdit m_edtBizType2;
	CEdit m_edtBizAddr;

	CEdit m_edtTaxManagerName;
	CEdit m_edtTaxManagerTel;
	CEdit m_edtTaxManagerEMail;
	
	CStatic m_stcState;
	CButton m_btnRegister;

	CString m_strBizLicenseUrl;
	
	void RefreshDlg();
};
