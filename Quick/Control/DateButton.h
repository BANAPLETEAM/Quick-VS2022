#pragma once

#include "BtnST.h"


// CDateButton

class CDateButton : public CButtonST
{
	//DECLARE_DYNAMIC(CDateButton)

public:
	CDateButton();
	virtual ~CDateButton();

protected:
	DECLARE_MESSAGE_MAP()

	CDateTimeCtrl *m_pFromDT;
	CDateTimeCtrl *m_pToDT;

public:
	//{{AFX_MSG
	afx_msg LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuToday();
	afx_msg void OnMenuYesterday();
	afx_msg void OnMenuYesterdayToday();
	afx_msg void OnMenuWeek();
	afx_msg void OnMenuMonth();
	afx_msg void OnMenuExactMonth();
	afx_msg void OnMenuPreExactMonth();
	afx_msg void OnMenuTomorrow();
	afx_msg void OnMenuTodayTomorrow();
	afx_msg void OnMenuMonthIncludeToday();
	afx_msg void OnMenuWeekIncludeToday();

	//}}AFX_MSG

	void SetDate(long nFromOffset, long nToOffset);
	void InitDateButton(CDateTimeCtrl *pFromDT, CDateTimeCtrl *pToDT);
	virtual DWORD OnDrawBorder(CDC* pDC, CRect* pRect);
	void OnMenuDayIncludeToday(long nDay);  

	void OnMenuYear();
	void OnMenu4Years();

};


