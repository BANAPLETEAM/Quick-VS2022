#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CGroupIncomeDlg 대화 상자입니다.

class CGroupIncomeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGroupIncomeDlg)

public:
	CGroupIncomeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGroupIncomeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GROUP_INCOME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nID;
	long m_nDebit;
	COleDateTime m_dtReIncome;
	CString m_sRet;
	CString m_sDate;
	CString m_strInputEtc;
	long m_nUnCollection;
	int m_nAllIncome;

	virtual BOOL OnInitDialog();
	void AllIncome();

	CDateTimeCtrl m_DateCtl;
	CEdit m_edtEtc;
	CButton m_chkReIncome;
	CDateTimeCtrl m_dtpReIncome;
	CComboBox m_cmbType;
	CEdit m_EdtMoney;	
	CStatic m_stcTitle;
	CStatic m_stcBalance;

	afx_msg void OnBnClickedCancelBtn();	
	afx_msg void OnEnChangeMoneyEdit();
	afx_msg void OnBnClickedIncomeBtn();	
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnBnClickedReincomCheck();
};
