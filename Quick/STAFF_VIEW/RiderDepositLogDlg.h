#pragma once
#include "afxwin.h"

class CIncomeForm5;
// CRiderDepositLogDlg 대화 상자입니다.

class CRiderDepositLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CRiderDepositLogDlg)

public:
	CRiderDepositLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_DEPOSIT_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stc1;
	BOOL m_bOk;

	CCreateContext m_context;
	CIncomeForm5 *m_pIncomeView;	

	virtual BOOL OnInitDialog();
	void RefreshOneRider(long nCompany, long nRNo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
