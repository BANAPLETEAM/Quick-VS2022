#pragma once
#include "afxwin.h"


// CUpChargeSetDlg ��ȭ �����Դϴ�.

class CUpChargeSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CUpChargeSetDlg)

public:
	CUpChargeSetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUpChargeSetDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UP_CHARGE_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CButton m_chkUseTimeSet;

	long m_nCompany;
	void RefreshDlg();
	void SetCombo(long nTime, UINT nID);
	BOOL CheckControl();
	long GetCombo(UINT nID);
};
