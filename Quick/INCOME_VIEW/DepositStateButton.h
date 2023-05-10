#pragma once

#include "BtnST.h"

class CRiderDepositInfoDlg;

class CDepositStateButton : public CButtonST
{
	//DECLARE_DYNAMIC(CDepositStateButton)

public:
	CDepositStateButton();
	virtual ~CDepositStateButton();

protected:
	DECLARE_MESSAGE_MAP()

public:

	CRiderDepositInfoDlg *m_pRdiDlg;

	void InitButton(CRiderDepositInfoDlg *pDlg);
	afx_msg void OnNotReport();
	afx_msg void OnReportComplete();
	afx_msg void OnIncomeComplete();



};


