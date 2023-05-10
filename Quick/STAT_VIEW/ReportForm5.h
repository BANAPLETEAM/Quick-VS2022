#pragma once


#include "ColorListCtrl.h"


typedef struct {
	int nTakeFee;
	int nGiveFee;
	int nTakeDeposit;
	int nGiveDeposit;
	int nTakeCount;
	int nGiveCount;
	int nTakeRcpShare;
	int nTakeProcessShare;
	int nTakeOperateShare;
	int nGiveRcpShare;
	int nGiveProcessShare;
	int nGiveOperateShare;
	char szCompany[100];
} INTERCHANGE_INFO;


typedef map<UINT, INTERCHANGE_INFO> ICM;




typedef struct { 
	int nTakeFee;
	int nGiveFee;
	int nTakeDeposit;
	int nGiveDeposit;
	int nTakeCount;
	int nGiveCount;
	int nTakeRcpShare;
	int nTakeProcessShare;
	int nTakeOperateShare;
	int nGiveRcpShare;
	int nGiveProcessShare;
	int nGiveOperateShare;
	char szCompany[30];
	char szBranchName[30];
	long nShareCode1;
	int nRcpRate;
} INTERCHANGE_INFO2;

typedef map<UINT, INTERCHANGE_INFO2> ICM2;


#include "RoundStatic.h"
#include "MFECToolTip.h"

// CReportForm5 대화 상자입니다.

class CReportForm5 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm5)

public:
	CReportForm5();
	virtual ~CReportForm5();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedShowBtn2();
	afx_msg void OnBnClickedShowBtn();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
     
protected:
	CMyStatic m_PeriodStatic;
	CDateButton m_DateBtn;

	CXTPListCtrl2 m_List;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CButton m_ShowBtn;
	CString m_strProcessRate;
	CString m_strOperateRate;
	CFlatEdit2 m_ProcessRateEdit;
	CFlatEdit2 m_OperateRateEdit;
	CButton m_FirstShareCheck;
	CButton m_SecondShareCheck;
	CButton m_ThirdShareCheck;
	CButton m_CallcenterCheck;

	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;

	
	ICM m_icm;
	CMFECToolTip m_toolTip;

	CString m_strFee;
	CFlatEdit2 m_FeeEdit;

	CButton m_CashCheck;
	CButton m_CreditCheck;
	CButton m_OnlineCheck;

	BOOL m_bCash;
	BOOL m_bCredit;
	BOOL m_bOnline;

public:
	void OnViewExcel();
	void MakeSharedCompanyList();
	void RefreshList();
	void RefreshCallcenter();
	int FilterLevel(int nCompany, int nRiderCompany);

	afx_msg void OnBnClickedCallcenterBtn();
};
