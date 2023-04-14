#pragma once
#include "afxwin.h"

class CCustomerDlg;

// CCustomerDlgSub1 폼 뷰입니다.

class CCustomerDlgSub1 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerDlgSub1)
protected:
	CCustomerDlgSub1();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerDlgSub1();

public:
	enum { IDD = IDD_CUSTOMER_DLG_SUB1 };
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
	afx_msg void OnPaint();
	afx_msg void OnEnSetfocusAddrDongEdit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEnKillfocusAddrDongEdit();
	afx_msg void OnDelete();
	afx_msg void OnCallPhone();
	afx_msg void OnMakePhone1();
	afx_msg void OnMakePhone2();
	afx_msg void OnMakePhone3();
	afx_msg void OnBnClickedEditDepartBtn();
	afx_msg void OnBnClickedMakePhone1Btn();
	afx_msg void OnBnClickedMakePhone2Btn();
	afx_msg void OnBnClickedMakePhone3Btn();
	afx_msg void OnBnClickedEditManagerBtn();
	afx_msg void OnBnClickedDeletePhoneBtn();
	afx_msg void OnBnClickedEditPhone1Btn();
	afx_msg void OnBnClickedEditPhone2Btn();
	afx_msg void OnBnClickedEditPhone3Btn();
	afx_msg void OnBnClickedGroupRefreshBtn();
	afx_msg void OnBnClickedChangeGroupBtn();
	afx_msg void OnBnClickedNoGroupBtn();
	afx_msg void OnEnChangeUserIdEdit();
	afx_msg void OnEnChangeCompanyEdit();
	afx_msg void OnEnChangeDepartEdit();
	afx_msg void OnEnChangeSnameEdit();
	afx_msg void OnEnChangeTelEdit();
	afx_msg void OnEnChangeMobileEdit();
	afx_msg void OnEnChangeMemoEdit();
	afx_msg void OnEnChangeRiderMemoEdit();
	afx_msg void OnCbnSelchangeCustomerGradeCombo();
	afx_msg void OnEnChangeAddrTitleEdit();
	afx_msg void OnEnChangeLocateEdit();
	afx_msg void OnEnChangeAddrDongEdit();
	afx_msg void OnBnClickedShowMapBtn();
	afx_msg void OnBnClickedCreditCheck();
	afx_msg void OnBnClickedOnlineCheck();
	afx_msg void OnBnClickedCardCheck();
	afx_msg void OnBnClickedTelAddBtn();
	afx_msg void OnBnClickedTelDelBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnReleasePhone();
	afx_msg void OnSendSms();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTelReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	long GetCreditType();
	void ChangeTelGrade(long nGrade);
	void SearchDong(BOOL bFocus);
	void ChangePhone(long nType);
	void ShowUseCount();
	BOOL IsRowSelected();
	ST_TEL* GetCurTelInfo();
	void SetCreditCheck(long nType);

	CXTPListCtrl39 m_lstTel;
	CCustomerDlg *m_pCustomerDlg;

	CMyStatic m_stcTelAdd;
	CMyStatic m_stcType;
	CMyStatic m_stcCustomerCode;
	CMyStatic m_stcGroupName;
	CMyStatic m_stcDepart;
	CMyStatic m_stcManager;
	CMyStatic m_stcTel;
	CMyStatic m_stcMobile;
	CMyStatic m_stcCNo;
	CMyStatic m_stcMemo;	
	CMyStatic m_stcUseCount;
	CMyStatic m_stcFirstUse;
	CMyStatic m_stcLastUse;
	CMyStatic m_stcLocate;
	CMyStatic m_stcAddress;
	CMyStatic m_stcBaseDong;
	CMyStatic m_stcRiderMemo;
	CMyStatic m_stcCompany;
	CMyStatic m_stcCredit;
	CMyStatic m_stcEnterInfo2;
	CMyStatic m_stc1;
	CMyStatic m_stcEtc1;
	CMyMarkupStatic m_stcInfo;
	CMarkupStatic m_stcEtcInfo;
	CMarkupStatic m_stcAddressDisplay;

	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtSms;
	CFlatEdit2 m_edtTelAdd;
	CFlatEdit2 m_edtType;
	CFlatEdit2 m_edtCNo;
	CFlatEdit2 m_edtGroupName;
	CFlatEdit2 m_edtUserID;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtDepart;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtTel;
	CFlatEdit2 m_edtMobile;
	CFlatEdit2 m_edtRiderMemo;
	CFlatEdit2 m_edtMemo;
	CFlatEdit2 m_edtUseCount;
	CFlatEdit2 m_edtFirstUse;
	CFlatEdit2 m_editAddrTitle;
	CFlatEdit2 m_edtLocate;
	CFlatEdit2 m_edtAddrDong;
	CFlatEdit2 m_edtDisplayDong;
	CFlatEdit2 m_edtLastUse;
	CFlatEdit2 m_edtCancelCount;

	CButton m_chkCredit;
	CButton m_chkOnline;
	CButton m_chkCard;
	CButton m_chkNotAutoShareOrder;
	CButton m_chkShowPhoneType;
	CButton m_btnTelAdd;
	CButton m_btnTelDel;
	CButton m_btnGroupRefresh;
	CButton m_btnChangeGroup;
	CButton m_btnNoGroup;
	CButton m_btnShowMap;

	BOOL m_bCredit;
	BOOL m_bNotAutoShareOrder;

	CString m_strDepart;
	CString m_strName;
	CString m_strTel;
	CString m_strMobile;
	CString m_strRiderMemo;
	CString m_strMemo;
	CString m_strCustomerType;
	CString m_strID;
	CString m_strGroupName;
	CString m_strUserID;
	CString m_strCompany;
	CString m_strUseCount;
	CString m_strFirstUse;
	CString m_strAddrTitle;
	CString m_strLocation;	
	CString m_strAddrDong;	
	CString m_strDisplayDong;
	CString m_strLastUse;
	CString m_strAddress;
	CString m_strTempPhone;
	CString m_strCancelCount;
	CString m_strSms;
	afx_msg void OnBnClickedCustomerColorBtn();
	afx_msg void OnBnClickedMemoColorBtn();
	afx_msg void OnEnChangeDisplayDongEdit();
	CButton m_chkPopupCustomerDlg;
	afx_msg void OnBnClickedShowPhoneTypeCheck();
	afx_msg void OnBnClickedNotAutoShareOrderCheck();
	afx_msg void OnBnClickedPopupCustomerDlgCheck2();
};


