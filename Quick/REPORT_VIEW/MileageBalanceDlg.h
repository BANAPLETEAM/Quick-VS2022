#pragma once
#include "afxwin.h"
#include "MyStatic.h"

// CMileageBalanceDlg 대화 상자입니다.

class CMileageBalanceDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMileageBalanceDlg)

public:
	CMileageBalanceDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMileageBalanceDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MILEAGE_BALANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nMileageBalance ;
	CMyStatic m_stcBefore;
	CMyStatic m_stcAfter;
	CEdit m_edtCharge;
	CEdit m_edtEtc;
	afx_msg void OnBnClickedOkBtn();
	CString m_sCharge;
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnEnChangeChargeEdit();
	virtual BOOL OnInitDialog();
	CComboBox m_cmbType;
	CString m_sEtc;
	long	m_nCNo;
	int m_nType;
};
