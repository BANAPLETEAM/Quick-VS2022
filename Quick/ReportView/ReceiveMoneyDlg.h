#pragma once

#include "DataBox.h"

class CReceiveMoneyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReceiveMoneyDlg)

public:
	CReceiveMoneyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CReceiveMoneyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECEIVE_MONEY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


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
