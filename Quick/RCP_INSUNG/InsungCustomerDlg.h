#pragma once
#include "afxwin.h"


// CInsungCustomerDlg 대화 상자입니다.

class CInsungCustomerDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsungCustomerDlg)

public:
	CInsungCustomerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsungCustomerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INSUNG_CUSTOMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddPhoneBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveBtn();

	void RefreshCustomer();
	void RefreshCustomerPhone();
	void SearchDong();

	BOOL CheckItem();
	void InsertCustomer();
	void UpdateCustomer();

	void FillDataSalesMan();
	void DeleteSalesCombo();

	void FindSalesMan();

	long GetCreditType();
	void SetCreditType(long nType);

	long m_nDongID;
	long m_nPosX;
	long m_nPosY;
	long m_nCNo;
	long m_nTelID;
	long m_nCompany;
	long m_nSendStateChangeSMS;
	CString m_strPhone;

	CMyStaticTri m_stcID;
	CMyStaticTri m_stcName;
	CMyStaticTri m_stcPhone1;
	CMyStaticTri m_stcPhone2;
	CMyStaticTri m_stcDepart;
	CMyStaticTri m_stcManager;
	CMyStaticTri m_stcDong;
	CMyStaticTri m_stcLocation;
	CMyStaticTri m_stcRiderMemo;
	CMyStaticTri m_stcMemo;
	CMyStaticTri m_stcPayTpye;
	CMyStaticTri m_stcChargeType;
	CMyStaticTri m_stcDiscount;
	CMyStaticTri m_stcDiscount1;
	CMyStaticTri m_stcMileage;
	CMyStaticTri m_stcMileage1;
	CMyStaticTri m_stcEnter;
	CMyStaticTri m_stcSales;
	CMyStaticTri m_stcInterNetID;
	CMyStaticTri m_stcInterNerPw;
	CMyStaticTri m_stcEMail;
	CMyStaticTri m_stcFax;
	CStatic m_stcHelp;

	CEdit m_edtID;
	CEdit m_edtName;
	CEdit m_edtPhone1;
	CEdit m_edtPhone2;
	CEdit m_edtDepart;
	CEdit m_edtManager;
	CEdit m_edtDong;
	CEdit m_edtAddress;
	CEdit m_edtLocation;
	CEdit m_edtRiderMemo;
	CEdit m_edtMemo;
	CButton m_rdoPayTpye0;
	CButton m_rdoPayTpye1;
	CButton m_rdoPayTpye2;
	CButton m_rdoPayTpye3;
	CComboBox m_cmbChargeType;
	CButton m_chkSendStateChangeSMS;
	CButton m_rdoDiscount0;
	CButton m_rdoDiscount1;
	CEdit m_edtDiscount;
	CComboBox m_cmbDiscount;
	CComboBox m_cmbMileage;
	CEdit m_edtMileage;
	CEdit m_edtCurMileage;
	CEdit m_edtEnter;
	CComboBox m_cmbSales;
	CEdit m_edtInterNetID;
	CEdit m_edtInterNetPw;
	CEdit m_edtEMail;
	CEdit m_edtFax;

	CXTPListCtrl2 m_lstTel;

	afx_msg void OnBnClickedMileageBtn();
	CButton m_chkAutoShareOrder;

	long m_nSalesCompany;
	long m_nSalesWNo;
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedMapBtn();
	afx_msg void OnBnClickedCopyCustomerBtn();
	CMyStaticTri m_stcWName;
	CMyStaticTri m_stcOther;
	CMyStaticTri m_stcPatener;
	CMyStaticTri m_stcUse;
	afx_msg void OnBnClickedDeletePhoneBtn();
	afx_msg void OnBnClickedSearchBtn();
};
