#pragma once
#include "afxwin.h"

class COptionDlgMobileNew : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgMobileNew)

protected:
	COptionDlgMobileNew();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgMobileNew();

public:
	enum { IDD = IDD_OPTION_DLG_MOBILE_NEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	BOOL Save(long nCompany, BOOL bAll);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:

		// 모바일 1
	BOOL m_bDestDisplay;
	CComboBox m_SortTypeCombo;
	BOOL	m_bDestViewTime;
	CString m_sDestViewTime;
	CButton m_chkDestViewTime;
	CDateTimeCtrl m_dtpFromDestView;
	COleDateTime m_dtFromDestView;

	BOOL m_bHideClientMultiple;
	CButton m_HideClientMultipleCheck;
	CButton m_HideClientSectionCheck;
	BOOL m_bHideClientSection;

	CComboBox m_RegionCountCombo;
	BOOL m_bEnableCancel;
	CButton m_EnableCancelCheck;
	BOOL m_bInsureLimit;
	CButton m_InsureLimitCheck;
	BOOL m_bChargeLimit;
	CButton m_ChargeLimitCheck;
	CString m_strMaxCharge;
	CEdit	m_MaxChargeEdit;

	BOOL	m_bNotCompletedLimit;
	CButton m_NotCompletedLimitCheck;
	CString m_strMinCompleteTime;
	CEdit m_MinCompleteTimeEdit;
	CButton m_WapDisableCheck;
	BOOL m_bWapDisable;
	CButton m_WorkReportCheck;
	BOOL m_bWorkReport;
	CEdit	m_WorkReportChargeEdit;
	CString m_strWorkReportCharge;
	CButton m_CancelPenaltyBtn;
	CButton m_DestDisplayCheck;

	CButton m_chkIgnoreRiderPermitCarType;
	BOOL m_bIgnoreRiderPermitCarType;
	CButton m_chkIgnoreRiderCharge;
	BOOL m_bIgnoreRiderCharge;
	CButton m_chkIgnoreRiderStart;
	BOOL m_bIgnoreRiderStart;
	CButton m_chkIgnoreRiderDest;
	CComboBox m_cmbAutoRange;
	CMyStatic m_stcAutoRange;
	BOOL m_bIgnoreRiderDest;

	virtual void OnInitialUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg long OnRefresh(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedDestDisplayCheck();
	afx_msg void OnBnClickedDestViewTimeCheck();
	afx_msg void OnBnClickedCancelPenaltyBtn();
	afx_msg void OnBnClickedChargeLimitCheck();
	afx_msg void OnBnClickedNotCompletedLimitCheck();


	void SetAutoRangeCombo(long nRange);
	long GetAutoRangeCombo();
	
	// 모바일 2

	CButton m_SupportableCallCheck;
	BOOL	m_bSupportableCall;

	CButton m_UsePickupCallCheck;
	BOOL	m_bUsePickupCall;
	CComboBox m_cmbAllocateMethod;
	CEdit m_edtAllocateLimitTime; // 즉시배차사 시간제한
	CString m_strAllocateLimitTime;

	BOOL m_bCustPhoneHide;
	CButton m_CustPhoneHide;

	CEdit m_edtClassViewByUseCount;
	CString m_sClassViewByUseCount;

	CButton m_chkUseNewRegion;
	BOOL m_bUseNewRegion;

	CString	m_strMaxDistance;
	CEdit	m_editMaxDistance;
	CString	m_strMaxNearOrder;
	CEdit	m_editMaxNearOrder;

	BOOL	m_bNotAllOrderView;
	CButton m_chkNotAllView;

	CEdit m_edtDistanceAllocate;
	int m_nDistanceAllocate;

	CButton m_chkUseNewRegionAllDong;
	BOOL m_bUseNewRegionAllDong;

	BOOL	m_bNationalCallcenter;
	CButton	m_chkNationalCallcenter;

	BOOL m_bNeedSignForComplete;
	CButton m_chkNeedSignForComplete;
			
	afx_msg void OnBnClickedUseNewRegion();
	afx_msg void OnBnClickedNotAllOrderview();
	afx_msg void OnCbnSelchangeAllocateCombo();	

	// 모바일 3

	CEdit m_editSymbol;
	CString m_strSymbol;
	CComboBox m_comboSymbolDisplay;
	CString m_strSymbolDisplay;
	
	CComboBox m_comboChargeDisplay;
	CString m_strChargeDisplay;
	CComboBox m_comboChargeDisplayType;
	CString m_strChargeDisplayType;

	CEdit m_editChargeMin;
	CString m_strChargeMin;
	CEdit m_editChargeMax;
	CString m_strChargeMax;

	CButton m_chkPreventShowOnlyMyCompanyOrder;
	BOOL	m_bPreventShowOnlyMyCompanyOrder;
	CButton m_chkIgnoreRiderKM;
	BOOL	m_bIgnoreRiderKM;
	
	afx_msg void OnCbnSelchangeSymbolDisplayTypeCombo();
	
	afx_msg void OnPaint();
	CButton m_chkAutoWaitOnce;
	BOOL m_bAutoWaitOnce;
};

