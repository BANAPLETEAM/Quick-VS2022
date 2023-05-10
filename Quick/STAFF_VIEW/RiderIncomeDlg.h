#pragma once
#include "afxwin.h"


// CRiderIncomeDlg ��ȭ �����Դϴ�.

class CRiderIncomeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderIncomeDlg)

public:
	CRiderIncomeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderIncomeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_INCOME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
