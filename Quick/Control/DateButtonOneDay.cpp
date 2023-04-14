// DateButtonOneDay.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DateButtonOneDay.h"



// CDateButtonOneDay

//IMPLEMENT_DYNAMIC(CDateButtonOneDay, CButtonST)
CDateButtonOneDay::CDateButtonOneDay()
{
}

CDateButtonOneDay::~CDateButtonOneDay()
{
}


BEGIN_MESSAGE_MAP(CDateButtonOneDay, CButtonST)
	//{{AFX_MSG_MAP(CDlgAdvanced)
	ON_COMMAND(ID_MENU_YESTERDAY, OnMenuYesterday)
	ON_COMMAND(ID_MENU_WEEK, OnMenuWeek)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDateButtonOneDay::InitDateButton(CDateTimeCtrl *pFromDT, CDateTimeCtrl *pToDT)
{
	SetIcon(ID_MENU_TODAY);

	m_pFromDT = pFromDT;
	m_pToDT = pToDT;
	m_pFromDT->SetFormat("yyyy-MM-dd HH:00(dddd)");
	m_pToDT->SetFormat("yyyy-MM-dd HH:00(dddd)");
	m_pToDT->EnableWindow(FALSE);

	SetMenu(IDR_DATE_MENU2, GetSafeHwnd(), 1);
	SetMenuCallback(GetSafeHwnd(), WM_USER + 100);		
}    

void CDateButtonOneDay::OnMenuYesterday()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtTo - COleDateTimeSpan(1, 0, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

void CDateButtonOneDay::OnMenuWeek()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	dtTo = dtTo - COleDateTimeSpan(7, 0, 0, 0);
	dtFrom = dtFrom - COleDateTimeSpan(7, 0, 0, 0);

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}





