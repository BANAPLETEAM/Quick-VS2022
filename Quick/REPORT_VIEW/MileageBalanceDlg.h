#pragma once
#include "afxwin.h"
#include "MyStatic.h"

// CMileageBalanceDlg ��ȭ �����Դϴ�.

class CMileageBalanceDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMileageBalanceDlg)

public:
	CMileageBalanceDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMileageBalanceDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MILEAGE_BALANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
