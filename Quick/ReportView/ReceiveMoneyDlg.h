#pragma once

#include "DataBox.h"

class CReceiveMoneyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReceiveMoneyDlg)

public:
	CReceiveMoneyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReceiveMoneyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECEIVE_MONEY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;	
	CDataBox m_wndReport;
	CDateButton m_DateBtn;	
	CMyStatic m_Stc1;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchBtn();
	virtual BOOL OnInitDialog();
	CString GetSettleType(int nType);


	BOOL m_bIntegrated;
	long m_nCompany;
	void RefreshList();
	
	
	CComboBox m_cmbCompany;
	afx_msg void OnCbnSelchangeCompanyCombo();
	afx_msg void OnMove(int x, int y);
};
