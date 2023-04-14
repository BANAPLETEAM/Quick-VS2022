#pragma once
#include "MyReportPaintManager.h"
#include "MyStaticBlue.h"
#include "MyStaticGreen.h"
#include "MyStaticRed.h"
#include "PPTooltip.h"

class CMakeHtmlTable;

typedef map<COleDateTime, ST_RIDER_ORDER> RIDER_ORDER_MAP;

// CRiderOrderLogDlg 대화 상자입니다.

class CRiderOrderLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderOrderLogDlg)

public:
	CRiderOrderLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderOrderLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_ORDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void GetEmptyString(CString &sFormat);
	void RefreshList();
	BOOL MakeHtmlTable(CMakeHtmlTable *htable, CString sDate);
	void MakeTooltipData();
	
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnBnClickedWeatherBtn();
	afx_msg void OnBnClickedRefreshBtn();

	CXTPListCtrl4 m_wndReport;
	RIDER_ORDER_MAP m_mapRider;

	CMyStaticBlue m_stcRiderName;
	CMyStaticBlue m_stcRNo;
	CMyStaticBlue m_stcAttendance;
	CMyStaticBlue m_stcAbsence;
	CMyStaticRed m_stcTypeA;
	CMyStaticRed m_stcTypeB;
	CMyStaticRed m_stcTypeC;
	CMyStaticRed m_stcTypeD;
	CMyStaticGreen m_stcCash;
	CMyStaticGreen m_stcCredit;
	CMyStaticGreen m_stcRemittance;
	CMyStaticGreen m_stcTotal;

	CXTFlatEdit m_RiderNameEdt;
	CXTFlatEdit m_RnoEdt;
	CXTFlatEdit m_AttendanceEdt;
	CXTFlatEdit m_AbsenceEdt;
	CXTFlatEdit m_TypeAEdt;
	CXTFlatEdit m_TypeBEdt;
	CXTFlatEdit m_TypeCEdt;
	CXTFlatEdit m_TypeDEdt;
	CXTFlatEdit m_CashEdt;
	CXTFlatEdit m_CreditEdt;
	CXTFlatEdit m_RemittanceEdt;
	CXTFlatEdit m_TotalEdt;
	
	CButton m_btnRefresh;
	CButton m_btnWeather;

	CComboBox m_MonthCmb;

	long m_nRiderCompany;
	long m_nRNo;

	CString m_strRName;

	CPPToolTip m_tooltip;
};
