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
	afx_msg void OnBnClickedApplyCompanyChargeBtn();
	afx_msg void OnBnClickedLoadCompanyChargeBtn();
	afx_msg void OnCbnSelchangeSalesTeamCombo();

	virtual void OnInitialUpdate();

	void DeleteSalesCombo();
	void SelChangeOption();
	void FillDataSalesMan();
	void FindSalesMan();
	CString GetEtcInfo();
	void SetCompanyCharge(long nMemCNo);

	CCustomerDlg *m_pCustomerDlg;

	CDateTimeCtrl m_dtpSalesTime;
	COleDateTime m_dtSalesTime;

	CComboBox m_cmbPriceGrade;
	CComboBox m_cmbDiscount;
	CComboBox m_cmbMileage;
	CComboBox m_cmbCompanyCharge;
	CComboBox m_cmbCoupon;
	CComboBox m_cmbCustomerGrade;
	CComboBox m_cmbAllocGroup;
	CComboBox m_cmbSalesTeam;

	CButton m_chkSendStateChangeSMS;
	CButton m_chkICMapDisplayType;	
	CButton m_chkUseHomePage;
	CButton m_chkDiscountApplyOnlyCredit;
	CButton m_chkPreventPosUpdate;
	CButton m_btnSetCoupon;
	CButton m_btnSetDiscount;
	CButton m_btnSetMileage;

	CFlatEdit2 m_edtDiscount;
	CFlatEdit2 m_edtDiscountRange;
	CFlatEdit2 m_edtMileage;
	CFlatEdit2 m_edtCoupon;
	CFlatEdit2 m_edtLoginID;
	CFlatEdit2 m_edtLoginPW;	
	CFlatEdit2 m_edtEMail;
	CFlatEdit2 m_edtFax;

	CMyStatic m_stcPriceGrade;
	CMyStatic m_stcDiscount;
	CMyStatic m_stcMileage;
	CMyStatic m_stcCoupon;	
	CMyStatic m_stcCustomerGrade;
	CMyStatic m_stcAllocGroup;

	CString m_strDiscount;
	CString m_strMileage;
	CString m_strCoupon;
	CString m_strLoginID;
	CString m_strLoginPW;
	CString m_strEMail;
	CString m_strFax;
	
	BOOL m_nSendStateChangeSMS;
	BOOL m_bPreventPosUpdate;
	BOOL m_bUseHomepage;
	BOOL m_nICMapDisplayType;
	BOOL m_bDiscountApplyOnlyCredit;

	int m_nSalesCompany;
	int m_nSalesWNo;
	CButton m_chkOnlinePopup;
	CEdit m_edtOnlinePopupCharge;
	BOOL m_bOnlinePopup;
	CString m_strOnlinePopupCharge;
	afx_msg void OnBnClickedOnlinePopupCheck();
	afx_msg void OnEnChangeOnlinePopupChargeEdit();
};


