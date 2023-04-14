#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


class CCustomerDlg;
// CCustomerDlgSub2 폼 뷰입니다.

class CCustomerDlgSub2 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerDlgSub2)

protected:
	CCustomerDlgSub2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerDlgSub2();

public:
	enum { IDD = IDD_CUSTOMER_DLG_SUB2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetMileageBtn();
	afx_msg void OnBnClickedSetDiscountBtn();
	afx_msg void OnBnClickedSetCouponBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeDiscountCombo();
	afx_msg void OnCbnSelchangePriceGradeCombo();
	afx_msg void OnCbnSelchangeCouponCombo();
	afx_msg void OnCbnSelchangeMileageCombo();

	CCustomerDlg *m_pCustomerDlg;
	CComboBox m_cmbPriceGrade;
	CComboBox m_cmbDiscount;
	CComboBox m_cmbMileage;
	CComboBox m_cmbCoupon;
	CFlatEdit2 m_edtDiscount;
	CFlatEdit2 m_edtMileage;
	CFlatEdit2 m_edtCoupon;
	CMyStatic m_stcPriceGrade;
	CMyStatic m_stcDiscount;
	CMyStatic m_stcMileage;
	CMyStatic m_stcCoupon;
	
	CMyStatic m_stcCustomerGrade;
	CString m_strDiscount;
	CString m_strMileage;
	CString m_strCoupon;
	CMyStatic m_stcAllocGroup;
	
	CFlatEdit2 m_edtLoginID;
	CFlatEdit2 m_edtLoginPW;
	CString m_strLoginID;
	CString m_strLoginPW;

	void DeleteSalesCombo();
	void SelChangeOption();
	void FillDataSalesMan();
	void FindSalesMan();
	CString GetEtcInfo();

	CButton m_chkSendStateChangeSMS;
	CFlatEdit2 m_edtEMail;
	CString m_strEMail;
	BOOL m_nSendStateChangeSMS;
	BOOL m_bPreventPosUpdate;
	CButton m_chkICMapDisplayType;
	BOOL m_bUseHomepage;
	BOOL m_nICMapDisplayType;

	
	CComboBox m_cmbCustomerGrade;
	CComboBox m_cmbAllocGroup;

	afx_msg void OnBnClickedSendStateChangeSmsCheck();
	afx_msg void OnBnClickedIcMapDisplayTypeChk();
	afx_msg void OnBnClickedUseHomepageCheck();
	afx_msg void OnBnClickedPreventPosUpdateCheck();
	afx_msg void OnEnChangeDiscountEdit();
	afx_msg void OnEnChangeMileageEdit();
	afx_msg void OnEnChangeCouponEdit();
	afx_msg void OnEnChangeLoginIdEdit();
	afx_msg void OnEnChangeLoginPwEdit();
	afx_msg void OnEnChangeEmailEdit();
	afx_msg void OnCbnSelchangeCustomerGradeCombo();
	afx_msg void OnCbnSelchangeAllocGroupCombo();
	CComboBox m_cmbSalesTeam;
	virtual void OnInitialUpdate();
	CDateTimeCtrl m_dtpSalesTime;
	COleDateTime m_dtSalesTime;
	int m_nSalesCompany;
	int m_nSalesWNo;
	afx_msg void OnCbnSelchangeSalesTeamCombo();
	CButton m_chkUseHomePage;
	CButton m_chkPreventPosUpdate;
	CButton m_btnSetCoupon;
	CButton m_btnSetDiscount;
	CButton m_btnSetMileage;
};


