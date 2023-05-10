#pragma once
#include "afxwin.h"


// CRiderIncomeDlg 대화 상자입니다.

class CRiderIncomeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderIncomeDlg)

public:
	CRiderIncomeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderIncomeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_INCOME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFlatEdit2 m_edtIncome;
	CFlatEdit2 m_edtIncomeMemo;
	CComboBox m_cmbIncome;
	afx_msg void OnBnClickedIncomeBtn();
	afx_msg void OnBnClickedIncomeBtn2();
	CString m_strIncome;
	CString m_strIncomeMemo;
	long m_nIncome;
	long m_nType;
};
