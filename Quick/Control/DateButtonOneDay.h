#pragma once

#include "BtnST.h"


// CDateButtonOneDay

class CDateButtonOneDay : public CButtonST
{
	//DECLARE_DYNAMIC(CDateButtonOneDay)

public:
	CDateButtonOneDay();
	virtual ~CDateButtonOneDay();

protected:
	DECLARE_MESSAGE_MAP()

	CDateTimeCtrl *m_pFromDT;
	CDateTimeCtrl *m_pToDT;

public:
	//{{AFX_MSG
	//afx_msg void OnMenuToday();
	afx_msg void OnMenuYesterday();
	afx_msg void OnMenuWeek();
	//afx_msg void OnMenuMonth();
	//afx_msg void OnMenuExactMonth();
	//}}AFX_MSG

	void InitDateButton(CDateTimeCtrl *pFromDT, CDateTimeCtrl *pToDT);

	afx_msg void OnSize(UINT nType, int cx, int cy);
};


