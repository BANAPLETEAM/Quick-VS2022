
#pragma once

#include "BtnST.h"

class CChargeDongUDlg;
// CDepositButton

class CChargeDongButton : public CButtonST
{
	//DECLARE_DYNAMIC(CChargeDongButton)

public:
	CChargeDongButton();
	virtual ~CChargeDongButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	
	
	afx_msg void OnInItDataLoad();
	afx_msg void OnUserDongPosLoad();
	afx_msg void OnUserDongPosSave();
	afx_msg void OnUserDongPosPasteDest();
	CChargeDongUDlg *m_pChargeDongUDlg;
	void InitButton(CChargeDongUDlg *pDlg);
	long m_nSelectedCNo;
};


