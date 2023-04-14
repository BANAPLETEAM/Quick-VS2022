#pragma once


#include "afxwin.h"
// COptionDlgPersonalInfo 폼 뷰입니다.

class COptionDlgPersonalInfo : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgPersonalInfo)

protected:
	COptionDlgPersonalInfo();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgPersonalInfo();

public:
	enum { IDD = IDD_OPTION_DLG_PERSONAL_INFO };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedUseCardPayCheck();
	afx_msg void OnBnClickedHomeCheck();
	afx_msg void OnBnClickedCompanyCheck();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	BOOL SearchRegion(long nFlag);
	void RefreshData(CMkRecordset *pRs);
	void DisplayDongInfo();
	BOOL Save(long nCompany, BOOL bAll);

	CStatic m_stcInfo;
	CStatic m_stcInfo2;
	CStatic m_stcInfo3;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtOwner;
	CFlatEdit2 m_edtTel;
	CFlatEdit2 m_edtHp;
	CFlatEdit2 m_edtEMail;
	CFlatEdit2 m_edtHomeDong;
	CFlatEdit2 m_edtHomeAddress;
	CFlatEdit2 m_edtCompanyDong;
	CFlatEdit2 m_edtCompanyAddress;
	CFlatEdit2 m_edtCardContract;
	CFlatEdit2 m_edtMID;
	CFlatEdit2 m_edtManager;
	CFlatEdit2 m_edtBank;
	CFlatEdit2 m_edtBankAccount;
	CFlatEdit2 m_edtAccountOwner;
	CFlatEdit2 m_edtFax;
	CFlatEdit2 m_edtHomePage;

	CXTMaskEdit m_edtHomeZipCode;
	CXTMaskEdit m_edtCompanyZipCode;
	CXTMaskEdit m_edtBizNo;
	CFlatEdit2 m_edtOwnerSSN;

	CButton m_chkUseCardPay;
	CMarkupStatic m_stcCompanyDong;
	CMarkupStatic m_stcHomeDong;

	CString m_strName;
	CString m_strOwner;
	CString m_strTel;
	CString m_strHp;
	CString m_strBizNo;
	CString m_strOwnerSSN;
	CString m_strEMail;
	CString m_strHomeDong;
	CString m_strHomeAddress;
	CString m_strCompanyDong;
	CString m_strCompanyAddress;
	CString m_strCardContract;
	CString m_strMID;
	CString m_strManager;
	CString m_strBank;
	CString m_strBankAccount;
	CString m_strAccountOwner;
	CString m_strFax;
	CString m_strHomePage;
	CString m_strHomeZipCode;
	CString m_strCompanyZipCode;

	CString m_strMainName;
	CString m_strMainBizNo;
	CString m_strMainOwner;
	CString m_strMainOwnerSSN;
	CString m_strMainTel;
	CString m_strMainHp;
	CString m_strMainEMail;
	long m_nMainHomeDongID;
	CString m_strMainHomeAddress;
	long m_nMainCompanyDongID;
	CString m_strMainCompanyAddress;
	CString m_strMainManager;
	CString m_strMainBank;
	CString m_strMainBankAccount;
	CString m_strMainAccountOwner;
	CString m_strMainFax;
	CString m_strMainHomePage;
	CString m_strMainHomeZipCode;
	CString m_strMainCompanyZipCode;

	long m_nMainPostalReceiveType;
	long m_nHomeDongID;
	long m_nCompanyDongID;
	long m_nPostalReceiveType;

	BOOL m_bNotApplyWithHolding;
	BOOL m_bWonCut;

	CButton m_chkWonCut;
	CButton m_chkNotApplyWithHolding;
	CButton m_chkHome;
	CButton m_chkCompany;

	CComboBox m_cmbFeeType;
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnPaint();
	void ChangeControl();
	void MoveControl(CWnd *pWnd, long nHeight);
	CStatic m_stcGeneral;
	CStatic m_stcCard;

	CRect m_rcCard;
};


