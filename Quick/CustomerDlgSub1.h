#pragma once
#include "afxwin.h"

class CCustomerDlg;


class CXTPListCtrl39 : public CXTPListCtrl
{
public:
	CXTPListCtrl39() {}
	~CXTPListCtrl39() {}


	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}
};
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

	CString m_strCustomerType;
	CString m_strID;
	CString m_strGroupName;
	CString m_strUserID;
	CString m_strCompany;

	CFlatEdit2 m_edtTelAdd;

	CFlatEdit2 m_edtType;
	CFlatEdit2 m_edtCNo;
	CFlatEdit2 m_edtGroupName;
	CFlatEdit2 m_edtUserID;
	CFlatEdit2 m_edtCompany;

	CString m_strDepart;
	CFlatEdit2 m_edtDepart;

	CFlatEdit2 m_edtName;
	CString m_strName;

	CString m_strTel;
	CFlatEdit2 m_edtTel;

	CString m_strMobile;
	CFlatEdit2 m_edtMobile;

	CFlatEdit2 m_edtRiderMemo;
	CString m_strRiderMemo;

	CFlatEdit2 m_edtMemo;
	CString m_strMemo;


	CFlatEdit2 m_edtUseCount;
	CString m_strUseCount;

	CString m_strFirstUse;
	CFlatEdit2 m_edtFirstUse;

	CFlatEdit2 m_editAddrTitle;
	CString m_strAddrTitle;

	CFlatEdit2 m_edtLocate;
	CString m_strLocation;

	CFlatEdit2 m_edtAddrDong;
	CString m_strAddrDong;

	CFlatEdit2 m_edtDisplayDong;
	CString m_strDisplayDong;

	CString m_strLastUse;
	CFlatEdit2 m_edtLastUse;

	CString m_strAddress;
	CMarkupStatic m_stcAddressDisplay;

	CFlatEdit2 m_edtSearch;

	CMyStatic m_stcCredit;

	CButton m_chkCredit;
	BOOL m_bCredit;

	CButton m_btnTelAdd;
	CButton m_btnTelDel;

	CMyStatic m_stc1;
	CMyStatic m_stcEtc1;
	CMarkupStatic m_stcEtcInfo;

	afx_msg void OnMenuContextSms(UINT nFlag);
	afx_msg void OnBnClickedGroupRefreshBtn();
	afx_msg void OnBnClickedChangeGroupBtn();
	afx_msg void OnBnClickedNoGroupBtn();
	afx_msg void OnEnChangeUserIdEdit();
	afx_msg void OnEnChangeCompanyEdit();
	afx_msg void OnBnClickedSmsButton();
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
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCreditCheck();
	afx_msg void OnBnClickedTelAddBtn();
	afx_msg void OnBnClickedTelDelBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuMakePhone2();
	afx_msg void OnMenuMakeCall();
	afx_msg void OnMenuMakeSms();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTelReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);


	CButton m_btnGroupRefresh;
	CString m_strTempPhone;
protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	void SelectFirstTelItem();
	void SearchDong(BOOL bFocus);
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnSetfocusAddrDongEdit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeSearchEdit();
	CButton m_btnChangeGroup;
	CButton m_btnNoGroup;
	CButton m_btnShowMap;
};


