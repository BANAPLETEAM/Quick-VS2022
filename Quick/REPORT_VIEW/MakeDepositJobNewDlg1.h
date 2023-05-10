#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"


class CMakeDepositJobNewDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CMakeDepositJobNewDlg1)

public:
	CMakeDepositJobNewDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMakeDepositJobNewDlg1();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAKE_DEPOSIT_JOB_NEW_DLG1 };

	enum COMBO_DEPOSIT_TYPE
	{
		COMBO_DEPOSIT,
		COMBO_SAVE
	};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOkBtn();

	long m_nDlgType; //0 Edit, 1 New, 2 UpdateLog
	long m_nID;
	long m_nCompany;
	BOOL m_bIntegrated;

	CEdit m_edtDisplayName;
	CString m_sDisplayName;
	BOOL m_bUse;
	CStatic m_stcDay;

	CButton m_chkDay;
	CButton m_chkWeek;
	CButton m_chkMonth;
	CButton m_chkMonthDay;
	CButton m_chkMonthWeek;

	CButton m_chkSun;
	CButton m_chkMon;
	CButton m_chkTues;
	CButton m_chkWednes;
	CButton m_chkThurs;
	CButton m_chkFri;
	CButton m_chkSatur;

	BOOL m_bMonthDay;
	BOOL m_bMonthWeek;

	BOOL m_bSun;	
	BOOL m_bMon;	
	BOOL m_bTues;	
	BOOL m_bWednes;	
	BOOL m_bThurs;	
	BOOL m_bFri;	
	BOOL m_bSatur;

	CComboBox m_cmbMonthDay;
	CComboBox m_cmbMonthWeek;
	CComboBox m_cmbMonthWeekend;

	int m_nMonthDay;
	int m_nMonthWeek;
	int m_nMonthWeekend;

	afx_msg void OnBnClickedDayCheck();
	afx_msg void OnBnClickedWeekCheck();
	afx_msg void OnBnClickedMonthCheck();

	CComboBox m_cmbDepositType;
	int m_nDepositType;
	CEdit m_edtDeposit;
	CString m_sDeposit;
	CDateTimeCtrl m_ctlTermStart;
	COleDateTime m_dtStart;
	CDateTimeCtrl m_ctlTermEnd;
	COleDateTime m_dtEnd;
	CEdit m_edtEtc;
	CString m_sEtc;
	BOOL m_bUseSms;
	CEdit m_edtSmsPhone;
	CString m_sSmsPhone;

	void InitControl();
	void InitData();
	void InitUpdateLog();
	void ChangeControl();
	void ChangeSubControl();
	BOOL InsertJob();
	BOOL UpdateJob();
	long GetPlayType();
	void SetPlayType(long nType);
	long GetMonthPlayType();
	void SetMonthPlayType(long nType);
	BOOL CheckControl();

	
	COleDateTime GetStartDate();
	COleDateTime GetEndDate();
	afx_msg void OnBnClickedMonthDayCheck();
	afx_msg void OnBnClickedThursCheck();
	afx_msg void OnBnClickedMonthWeekCheck();

	CButton m_chkWorkerApply;
	BOOL m_bWorkerApply;
	CButton m_chkNotWorkerApply;
	BOOL m_bNotWorkerApply;
	CStatic m_stcType;
	afx_msg void OnBnClickedEck();
	CButton m_chkCopy;
	afx_msg void OnBnClickedCancelBtn();
};
