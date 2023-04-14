// FlatStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "stdafx.h"
#include "FlatStatic.h"

COLORREF TRANS_BACK = COLOR_BTNFACE;


// CFlatStatic

IMPLEMENT_DYNAMIC(CFlatStatic, CStatic)

CFlatStatic::CFlatStatic()
{
	m_clrText  = RGB(0, 0, 0);
	m_clrBack = TRANS_BACK;
	m_bAutoAddSpace = FALSE;
	m_bAddedSpace = FALSE;
}

BEGIN_MESSAGE_MAP(CFlatStatic, CEdit)
	//{{AFX_MSG_MAP(CFlatStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CFlatStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	m_hBrush.DeleteObject();

	if (m_clrBack == TRANS_BACK) {
		m_hBrush.CreateStockObject(HOLLOW_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
	}
	else {
		m_hBrush.CreateSolidBrush(m_clrBack);
		pDC->SetBkColor(m_clrBack);
	}

	pDC->SetTextColor(m_clrText);

	return (HBRUSH)m_hBrush;
}

void CFlatStatic::OnUpdate() 
{
	UpdateCtrl();
}

void CFlatStatic::UpdateCtrl()
{
	CWnd* pParent = GetParent();
	CRect rect;

	GetWindowRect(rect);
	pParent->ScreenToClient(rect);
	rect.DeflateRect(2, 2);

	pParent->InvalidateRect(rect, FALSE); 
}

void CFlatStatic::SetTextColor(COLORREF col) 
{ 
	m_clrText = col;
	UpdateCtrl();             
}
void CFlatStatic::SetBackColor(COLORREF col) 
{ 
	m_clrBack = col;                                                   
	UpdateCtrl();            
}

CString CFlatStatic::GetText()
{
	CString strText;
	GetWindowText(strText);
	return strText;
}

long CFlatStatic::GetTextLong()
{
	CString strText;
	GetWindowText(strText);
	strText.Replace(",", "");
	return atol(strText);
}

void CFlatStatic::SetWindowTextLong(long nNumber, BOOL bThousandsSep)
{
	CString strNumber;
	strNumber.Format("%ld", nNumber);
	SetWindowText(bThousandsSep ? ::GetMyNumberFormat(strNumber) : strNumber);
}

void CFlatStatic::SetWindowText(LPCTSTR lpszString)
{ 
	ASSERT(::IsWindow(m_hWnd)); 
	DWORD dwStyle = GetStyle();

	if(m_bAutoAddSpace && !(dwStyle & SS_CENTER))
	{
		CString strString;

		if(dwStyle & SS_RIGHT)
			strString.Format("%s ", lpszString);
		else 
			strString.Format(" %s", lpszString);
	
		::SetWindowText(m_hWnd, (LPSTR)(LPCTSTR)strString); 
		m_bAddedSpace = TRUE;
	}
	else
	{
		::SetWindowText(m_hWnd, lpszString);
		m_bAddedSpace = FALSE;
	}
}

void CFlatStatic::GetWindowText(CString& rString) const
{
	ASSERT(::IsWindow(m_hWnd));

#ifndef _AFX_NO_OCC_SUPPORT
	if (m_pCtrlSite == NULL)
	{
#endif
		int nLen = ::GetWindowTextLength(m_hWnd);
		::GetWindowText(m_hWnd, rString.GetBufferSetLength(nLen), nLen+1);
		rString.ReleaseBuffer();

#ifndef _AFX_NO_OCC_SUPPORT
	}
	else
	{
		m_pCtrlSite->GetWindowText(rString);
	}
#endif

	DWORD dwStyle = GetStyle();

	if(rString.GetLength() > 0 && m_bAddedSpace && !(dwStyle & SS_CENTER))
	{
		CString strString;

		if(dwStyle & SS_RIGHT && rString.Right(1) == " ")
			rString = rString.Left(rString.GetLength() - 1);
		else if(!(dwStyle & SS_RIGHT) && rString.Left(1) == " ")
			rString = rString.Right(rString.GetLength() - 1);
	}
}

int CFlatStatic::GetWindowTextLength() const
{ 
	ASSERT(::IsWindow(m_hWnd)); 
	return ::GetWindowTextLength(m_hWnd) + (m_bAddedSpace ? -1 : 0); 
}

void CFlatStatic::SetAutoAddSpace(BOOL bAdd) 
{ 
	if(m_bAutoAddSpace ^ bAdd)
	{
		m_bAutoAddSpace = bAdd; 
		SetWindowText(GetText());
	}
}