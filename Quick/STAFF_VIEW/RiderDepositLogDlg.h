#pragma once
#include "afxwin.h"

class CIncomeForm5;
// CRiderDepositLogDlg ��ȭ �����Դϴ�.

class CRiderDepositLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CRiderDepositLogDlg)

public:
	CRiderDepositLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderDepositLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_DEPOSIT_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
