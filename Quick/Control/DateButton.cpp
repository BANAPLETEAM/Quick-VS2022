// DateButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DateButton.h"

// CDateButton
//IMPLEMENT_DYNAMIC(CDateButton, CButtonST)
CDateButton::CDateButton()
{	
}

CDateButton::~CDateButton()
{
}


BEGIN_MESSAGE_MAP(CDateButton, CButtonST)
	//{{AFX_MSG_MAP(CDlgAdvanced)
	ON_COMMAND(ID_MENU_TODAY, OnMenuToday)
	ON_COMMAND(ID_MENU_YESTERDAY, OnMenuYesterday)
	ON_COMMAND(ID_MENU_YESTERDAY_TODAY, OnMenuYesterdayToday)
	ON_COMMAND(ID_MENU_WEEK, OnMenuWeek)
	ON_COMMAND(ID_MENU_MONTH, OnMenuMonth)
	ON_COMMAND(ID_MENU_EXACT_MONTH, OnMenuExactMonth)
	ON_COMMAND(ID_MENU_PRE_EXACT_MONTH, OnMenuPreExactMonth)
	ON_COMMAND(ID_MENU_TOMORROW, OnMenuTomorrow)
	ON_COMMAND(ID_MENU_TODAY_TOMORROW, OnMenuTodayTomorrow)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_USER + 100, On_MenuCallback)
END_MESSAGE_MAP()


void CDateButton::InitDateButton(CDateTimeCtrl *pFromDT, CDateTimeCtrl *pToDT)
{
	SetIcon(ID_MENU_TODAY);

	m_pFromDT = pFromDT;
	m_pToDT = pToDT;

#ifdef _DAERI
	m_pFromDT->SetFormat("yyyy-MM-dd HH:00");
	m_pToDT->SetFormat("yyyy-MM-dd HH:00");
#else
	m_pFromDT->SetFormat("yyyy-MM-dd");
	m_pToDT->SetFormat("yyyy-MM-dd");
#endif

	short	shBtnColor = 30;

//	m_DateBtn.SetIcon(IDI_TOOLS4);
//	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
//	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 28);
//	DrawBorder();

//#ifdef	BTNST_USE_BCMENU
//	pBtn->SetMenu(IDR_DATE_MENU, m_hParent, TRUE, IDR_TOOLBAR);
	SetMenu(IDR_DATE_MENU, GetSafeHwnd());
	SetMenuCallback(GetSafeHwnd(), WM_USER + 100);		
}    



// CDateButton 메시지 처리기입니다.
LRESULT CDateButton::On_MenuCallback(WPARAM wParam, LPARAM lParam)
{
//#ifdef	BTNST_USE_BCMENU
//	BCMenu*	pMenu = (BCMenu*)wParam;
//	pMenu->EnableMenuItem(IDM_ITEM3, TRUE);
	//::EnableMenuItem((HMENU)wParam, IDM_ITEM3, MF_BYCOMMAND | MF_GRAYED);
	return 0;
} 


void CDateButton::OnMenuToday()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	

#ifdef _DAERI
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
#else
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
#endif
	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

void CDateButton::OnMenuYesterday()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	
#ifdef _DAERI
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
#else 
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
#endif

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}


void CDateButton::OnMenuYesterdayToday()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();

#ifdef _DAERI
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
#else 
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	dtTo.SetDateTime(dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay(), 23, 59, 59);
#endif

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

void CDateButton::OnMenuWeek()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	
#ifdef _DAERI
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
	dtFrom = dtFrom - COleDateTimeSpan(7, 0, 0, 0);
#else 
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
	dtFrom = dtFrom - COleDateTimeSpan(6, 0, 0, 0);
#endif


	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

void CDateButton::OnMenuMonth()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	
#ifdef _DAERI
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
	dtFrom = dtFrom - COleDateTimeSpan(30, 0, 0, 0);
#else
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
	dtFrom = dtFrom - COleDateTimeSpan(29, 0, 0, 0);
#endif


	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

void CDateButton::OnMenuExactMonth()
{
	int nDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	COleDateTime dtFrom, dtTo;
	m_pFromDT->GetTime(dtFrom);
	m_pFromDT->GetTime(dtTo);

#ifdef _DAERI
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), 1, BASE_HOUR, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), nDays[dtFrom.GetMonth() - 1], BASE_HOUR, 0, 0);
#else 
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), 1, 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), nDays[dtFrom.GetMonth() - 1], 23, 59, 59);
#endif
	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}


void CDateButton::OnMenuPreExactMonth()
{
	int nDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	COleDateTime dtFrom, dtTo;
	dtFrom = COleDateTime::GetCurrentTime();
	dtFrom = dtFrom -  COleDateTimeSpan(nDays[dtFrom.GetMonth() - 1], 0, 0, 0);

#ifdef _DAERI
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), 1, BASE_HOUR, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), nDays[dtFrom.GetMonth() - 1], BASE_HOUR, 0, 0);
#else 
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), 1, 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), nDays[dtFrom.GetMonth() - 1], 23, 59, 59);
#endif
	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}

DWORD CDateButton::OnDrawBorder(CDC* pDC, CRect* pRect)
{
	// Draw pressed button
	if (m_bIsPressed)
	{
		if (m_bIsFlat)
		{
			if (m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
		}
		else    
		{
			CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
			pDC->FrameRect(pRect, &brBtnShadow);
		}
	}
	else // ...else draw non pressed button
	{
		CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
		CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
		CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

		if (m_bIsFlat)
		{
			if (m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
		}
		else
		{
			// Draw top-left borders
			// White line
			CPen* pOldPen = pDC->SelectObject(&penBtnHiLight);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			// Light gray line
			pDC->SelectObject(pen3DLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			// Draw bottom-right borders
			// Black line
			pDC->SelectObject(pen3DDKShadow);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);
			// Dark gray line
			pDC->SelectObject(penBtnShadow);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectObject(pOldPen);
		} // else
	} // else

	return BTNST_OK;
} // End of OnDrawBorder


void CDateButton::OnMenuTomorrow()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();


#ifdef _DAERI
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
#else
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
#endif

	dtFrom += COleDateTimeSpan(1, 0, 0, 0);
	dtTo += COleDateTimeSpan(1, 0, 0, 0);

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}


void CDateButton::OnMenuTodayTomorrow()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();


#ifdef _DAERI
	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
#else
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);
#endif

	dtTo += COleDateTimeSpan(1, 0, 0, 0);

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}
 
void CDateButton::OnMenuMonthIncludeToday()
{  
	SetDate(30, 0);	
}


void CDateButton::SetDate(long nFromOffset, long nToOffset)
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();

	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 23, 59, 59);

	dtFrom = dtFrom + COleDateTimeSpan(-nFromOffset, 0, 0, 0);
	dtTo = dtTo + COleDateTimeSpan(-nToOffset, 0, 0, 0);

	m_pFromDT->SetTime(dtFrom);
	m_pToDT->SetTime(dtTo);
}


void CDateButton::OnMenuDayIncludeToday(long nDay)
{
	SetDate(nDay - 1, 0);
}

void CDateButton::OnMenuWeekIncludeToday()
{
	SetDate(6, 0);	
}

void CDateButton::OnMenuYear()
{
	SetDate(365, 0);
}

void CDateButton::OnMenu4Years()
{
	SetDate(1460, 0);
}