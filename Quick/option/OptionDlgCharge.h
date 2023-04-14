#pragma once
#include "afxwin.h"
// COptionDlgGeneral2 폼 뷰입니다.

class COptionDlgCharge : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgCharge)

protected:
	COptionDlgCharge();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgCharge();

public:
	enum { IDD = IDD_OPTION_DLG_CHARGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg long OnRefresh(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedMileageCheck();
	afx_msg void OnCbnSelchangePercentCombo();
	afx_msg void OnBnClickedMileageTermBtn();	
	afx_msg void OnEnChangeMileageEdit();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedDistanceChargeCheck();
	afx_msg void OnBnClickedWorktimeBtn();
	afx_msg void OnCbnSelchangeDistanceChargeCombo();

	BOOL Save(long nCompany, BOOL bAll);

	long m_nMileageSpan;	
	long m_nMileage;
	long m_nMileageTruck;
	long m_nBothCharge;
	long m_nMinCharge;	
	int	m_nDamasAdd;
	int m_nRaboAdd;
	int	m_nBanAdd;
	int	m_nTruckAdd;
	int	m_nDistanceCharge;

	CButton		m_chkDongPosLiUse;
	CFlatEdit2 	m_DefaultChargeEdit;
	CFlatEdit2 	m_BothChargeEdt;
	CFlatEdit2 	m_edtEmergencyCharge;
	CFlatEdit2 	m_edtMinCharge;	
	CFlatEdit2 	m_edtMileageSpan;
	CFlatEdit2 	m_edtMileage;

	CEdit 		m_edtBikeWeatherAdd ; 
	CEdit 		m_edtDamaWeatherAdd ; 
	CEdit 		m_edtLaboWeatherAdd ; 
	CEdit 		m_edtVanWeatherAdd  ;  
	CEdit 		m_edtTruckWeatherAdd;
	CButton		m_chkWeatherCharge;


	CEdit m_edtBikeWeatherSnowAdd;
	CEdit m_edtDamaWeatherSnowAdd;
	CEdit m_edtLaboWeatherSnowAdd;
	CEdit m_edtVanWeatherSnowAdd;
	CEdit m_edtTruckWeatherSnowAdd;
	CButton	m_chkWeatherChargeSnow;
	CButton m_chkWeatherChargeAuto;
	CEdit m_edtSlowDis;

	CButton m_chkMileageTruck;
	CComboBox m_cmbPercentTruck;
	CEdit m_edtMileageTruck;

	CString		m_strDefaultCharge;
	CString 	m_strEmergencyCharge;
	CString 	m_strDistanceCharge;
	
	BOOL		m_bDistanceChargeCheck;	

	CButton 	m_chkAddDisChargeRound;
	CButton 	m_chkDistanceCharge;
	CButton 	m_chkMileage;
	CButton 	m_btnMileageTerm;
	CButton 	m_chkNoGroupCharge;
	CButton 	m_chkNoMemberCharge;
	CButton 	m_chkMemChaNoGeneralData;
	CComboBox	m_cmbDistanceCharge;
	CComboBox	m_cmbPercent;
	
	CButton		m_chkUpChargeForNotAllocateManual;
	CButton		m_chkUpChargeForNotAllocateAuto;

	CEdit		m_edtUpChargeForNotAllocateManual1;
	CEdit		m_edtUpChargeForNotAllocateManual2;
	CEdit		m_edtUpChargeForNotAllocateManual3;

	CComboBox 	m_cmbUpChargeForNotAllocateMinute1;
	CComboBox 	m_cmbUpChargeForNotAllocateMinute2;
	CComboBox 	m_cmbUpChargeForNotAllocateMinute3;
	CComboBox 	m_cmbUpChargeForNotAllocateMinute4;
	CComboBox 	m_cmbUpChargeForNotAllocateMinute5;

	CEdit 		m_edtUpChargeForNotAllocateAuto1;
	CEdit 		m_edtUpChargeForNotAllocateAuto2;
	CEdit 		m_edtUpChargeForNotAllocateAuto3;
	CEdit 		m_edtUpChargeForNotAllocateAuto4;
	CEdit 		m_edtUpChargeForNotAllocateAuto5;

	CComboBox m_cmbMileageSavingType;

	CString m_strUpChargeForNotAllocateManual1;
	CString m_strUpChargeForNotAllocateManual2;
	CString m_strUpChargeForNotAllocateManual3;
	CString m_strUpChargeForNotAllocateMinute1;
	CString m_strUpChargeForNotAllocateMinute2;
	CString m_strUpChargeForNotAllocateMinute3;
	CString m_strUpChargeForNotAllocateMinute4;
	CString m_strUpChargeForNotAllocateMinute5;
	CString m_strUpChargeForNotAllocateAuto1;
	CString m_strUpChargeForNotAllocateAuto2;
	CString m_strUpChargeForNotAllocateAuto3;
	CString m_strUpChargeForNotAllocateAuto4;
	CString m_strUpChargeForNotAllocateAuto5;

	afx_msg void OnBnClickedDistanceChargeBtn();
	int m_nLaboChargeType;
	CButton m_chkUseDirectDistance;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_chkUpChargeForNotAllocateReserve;
	CButton m_chkUpChargeForNotAllocateDeposit;
	afx_msg void OnBnClickedUpChargeSetBtn();
	afx_msg void OnBnClickedUpChargeForNotAllcateManualCheck();
	afx_msg void OnBnClickedUpChargeForNotAllcateAutoCheck();
	CEdit m_edtNewCustomerMileage;
	CEdit m_edtBranchDis;
	afx_msg void OnBnClickedAreaSelectBtn();
	afx_msg void OnPaint();
	void RefreshSpecialTruckCharge(int company_code);
	void ClearSpeicalTruckCharge();
	CWnd* GetSpecialTruckTypeControl(int car_type, int special_truck_type);
	void UpdateSpecialTruckCharge(long nCompany, BOOL bAll);
	void UpdateSpecialTruckChargeSub(long nCompany, int car_type);
	void AddSpecialTruckCharge(int car_type, int special_truck_type, int charge);
	int GetSpecialTruckCharge(int car_type, int special_truck_type);
};


