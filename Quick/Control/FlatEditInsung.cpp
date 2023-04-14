// FlatEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "FlatEditInsung.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

EDIT_BRUSH_MAP CFlatEditInsung::m_mapBrush;

// CFlatEditInsung

IMPLEMENT_DYNAMIC(CFlatEditInsung, CXTPEdit)

CFlatEditInsung::CFlatEditInsung()
{
	m_clrBorderHot = RGB(0, 198, 255);
	m_clrBorderNormal = RGB(204, 204, 204);
	m_clrBack = RGB(255, 255, 255);
	m_clrText = RGB(0, 0, 0);
	m_bShowCommaNumber = FALSE;
	m_bShowDashPhoneNumber = FALSE;
	m_bAutoResize = FALSE;
	m_nEditLineExtent = 0;
	m_nMaxLine = 5;
	m_nTextAlign = DT_CENTER;

	CreateClientBrush();
}

CFlatEditInsung::~CFlatEditInsung()
{
	ReleaseClientBrush();
}


BEGIN_MESSAGE_MAP(CFlatEditInsung, CXTPEdit)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()



// CFlatEditInsung 메시지 처리기입니다.


void CFlatEditInsung::OnNcPaint()
{
	TBase::OnNcPaint();

	CWindowDC dc(this);

	CRect rc;
	GetWindowRect(&rc);
	rc.OffsetRect(-rc.TopLeft());

	TRACE("%d, %d, %d, %d\n", rc.left, rc.top, rc.right, rc.bottom);

	if(m_bFocused || m_bHighlighted)
		DrawFrame(&dc, rc, 1, m_clrBorderHot);
	else
		DrawFrame(&dc, rc, 1, m_clrBorderNormal);

	if(GetStyle() & WS_VSCROLL)
		rc.right -= GetSystemMetrics(SM_CXVSCROLL); 

	if(GetStyle() & WS_HSCROLL)
		rc.bottom -= GetSystemMetrics(SM_CXHSCROLL); 


	TRACE("%d, %d, %d, %d\n", rc.left, rc.top, rc.right, rc.bottom);

	rc.DeflateRect(1, 1, 1, 1);
	DrawFrameNC(&dc, rc, m_clrBack);

	DrawHelpText(&dc, rc);
}


void CFlatEditInsung::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting

	// Get the client rect. 
	CXTPClientRect rectClient(this);


	CXTPBufferDC memDC(dcPaint);

	::FillRect(memDC, rectClient, GetClientBrush()); 
	TRACE("%d, %d, %d, %d\n", rectClient.left, rectClient.top, rectClient.right, rectClient.bottom);

	// Now let the window do its default painting...
	CEdit::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);

	DrawHelpText(&memDC, rectClient);

}


void CFlatEditInsung::PreSubclassWindow()
{
	TBase::PreSubclassWindow();

	if(m_bPreSubclassInit)
	{
		CXTPEdit::Init();
		m_clrBorderHot = RGB(0, 198, 255);
		m_clrBorderNormal = RGB(204, 204, 204);
	}
}

void CFlatEditInsung::DrawFrameNC(CDC *pDC, CRect rc, COLORREF cr)
{
	CRect rcEdit;
	GetRect(&rcEdit);

	//by mksong (2014-07-13 오전 11:33) 
	//이 부분 다시 확인해야함

	FillSolidRect(pDC, rc.left, rc.top, rc.Width(), 2, cr);
	//FillSolidRect(pDC, rc.left, rc.bottom, rc.Width(), rcEdit.bottom - rc.bottom, cr);
	FillSolidRect(pDC, rc.left, rc.bottom, rc.Width(), -2, cr);
	FillSolidRect(pDC, rc.left, rc.top, 2, rc.Height(), cr);
	FillSolidRect(pDC, rc.right, rc.top, -2, rc.Height(), cr);
}

void CFlatEditInsung::DrawFrame(CDC *pDC, CRect rc, int nSize, COLORREF cr)
{
	FillSolidRect(pDC, rc.left, rc.top, rc.right - rc.left - nSize, nSize, cr);
	FillSolidRect(pDC, rc.left, rc.top, nSize, rc.bottom - rc.top - nSize, cr);
	FillSolidRect(pDC, rc.right - nSize, rc.top, nSize, rc.bottom - rc.top, cr);
	FillSolidRect(pDC, rc.left, rc.bottom - nSize, rc.right - rc.left, nSize, cr);
}

void CFlatEditInsung::FillSolidRect(CDC *pDC, int x, int y, int cx, int cy, COLORREF cr)
{
	pDC->FillSolidRect(CRect(x, y, x + cx, y + cy), cr);
}

BOOL CFlatEditInsung::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(rc);			
	pDC->FillSolidRect(rc, m_clrBack);
	return TRUE;
}

HBRUSH CFlatEditInsung::CtlColor(CDC* pDC, UINT /*nCtlColor*/ ) 
{


	pDC->SetTextColor(m_clrText);
	pDC->SetBkColor(m_clrBack);
	return GetClientBrush();
}

HBRUSH CFlatEditInsung::GetClientBrush()
{
	if(m_clrBack == RGB(0, 0, 0))
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
	else if(m_clrBack == RGB(255, 255, 255))
		return (HBRUSH)GetStockObject(WHITE_BRUSH);

	EDIT_BRUSH_MAP::iterator it = m_mapBrush.find(m_clrBack);

	if(it != m_mapBrush.end())
		return it->second.first;
	else
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
}

void CFlatEditInsung::CreateClientBrush()
{
	if(m_clrBack == RGB(0, 0, 0) || m_clrBack == RGB(255, 255, 255))
		return;

	EDIT_BRUSH_MAP::iterator it = m_mapBrush.find(m_clrBack);
	if(it != m_mapBrush.end())
	{
		it->second.second++;
		return;
	}

	m_mapBrush.insert(EDIT_BRUSH_MAP::value_type(m_clrBack, make_pair(CreateSolidBrush(m_clrBack), 1)));
}

void CFlatEditInsung::ReleaseClientBrush()
{
	if(m_clrBack == RGB(0, 0, 0) || m_clrBack == RGB(255, 255, 255))
		return;

	EDIT_BRUSH_MAP::iterator it = m_mapBrush.find(m_clrBack);
	if(it != m_mapBrush.end())
	{
		if(--(it->second.second) <= 0)
		{
			DeleteObject(it->second.first);
			m_mapBrush.erase(it);
		}
	}
}

void CFlatEditInsung::SetColor(COLORREF clrText, COLORREF clrBack, BOOL bRedraw)
{
	if(m_clrBack != clrBack)
		ReleaseClientBrush();

	m_clrBack = clrBack;
	m_clrText = clrText;
	CreateClientBrush();

	if(bRedraw)
		Invalidate();
}

void CFlatEditInsung::OnKillFocus(CWnd* pNewWnd)
{
	if(m_bShowCommaNumber)
	{
		CString strCharge;
		GetWindowText(strCharge);
		SetWindowText(::GetMyNumberFormat(strCharge));
	}
	else if(m_bShowDashPhoneNumber)
	{
		CString strPhone;
		GetWindowText(strPhone);
		SetWindowText(::GetDashPhoneNumber(strPhone));
	}

	CXTPEdit::OnKillFocus(pNewWnd);
}

void CFlatEditInsung::OnSetFocus(CWnd* pOldWnd)
{
	if(m_bShowCommaNumber)
	{
		CString strCharge;
		GetWindowText(strCharge);
		SetWindowText(::RemoveComma(strCharge));
	}
	else if(m_bShowDashPhoneNumber)
	{
		CString strPhone;
		GetWindowText(strPhone);
		SetWindowText(::GetNoneDashNumber(strPhone));
	}

	CXTPEdit::OnSetFocus(pOldWnd);
}

void CFlatEditInsung::SetHelpText(CString strHelpText, COLORREF clrHelpText, UINT nTextAlign, BOOL bRedraw)
{
	m_strHelpText = strHelpText;
	m_clrHelpText = clrHelpText;
	m_nTextAlign = nTextAlign;

	if(bRedraw)
		Invalidate();
}

void CFlatEditInsung::DrawHelpText(CDC *pDC, CRect rc)
{
	if(!m_bFocused && !m_bHighlighted && !m_strHelpText.IsEmpty())
	{
		if(GetWindowTextLength() == 0)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_clrHelpText);
			pDC->SelectObject(GetFont());
			pDC->DrawText(m_strHelpText, rc, m_nTextAlign | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void CFlatEditInsung::SetWindowText(LPCTSTR lpszString)
{
	CXTPEdit::SetWindowText(lpszString);

	if(m_bAutoResize)
		OnUserChar();
}

BOOL CFlatEditInsung::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
		if(m_bAutoResize)
			OnUserChar();

	return CXTPEdit::PreTranslateMessage(pMsg);
}


void CFlatEditInsung::OnUserChar()
{
	if(m_nEditLineExtent == 0)
	{
		CClientDC dc(this);
		CFont* pEdtFont = GetFont();
		if(pEdtFont != NULL)
		{
			CFont* pOldFont = dc.SelectObject(pEdtFont);
			m_nEditLineExtent = dc.GetTextExtent(CString(" ")).cy;
		}
	}

	int nMinPos, nMaxPos;
	GetScrollRange(SB_VERT, &nMinPos, &nMaxPos);

	UINT nScrollHeight = min(nMaxPos + 1, m_nMaxLine) * m_nEditLineExtent + 6;

	CRect rcEdit;
	GetWindowRect(rcEdit);

	if(nScrollHeight != rcEdit.Height())
	{
		GetParent()->ScreenToClient(rcEdit);

		rcEdit.bottom = rcEdit.top + nScrollHeight;
		MoveWindow(rcEdit);

		GetParent()->PostMessage(WM_EDIT_RESIZE, GetDlgCtrlID(), nScrollHeight);
	}
}

void CFlatEditInsung::SetBorderColor(COLORREF clrNormal, COLORREF clrHot)
{
	m_clrBorderNormal = clrNormal;
	m_clrBorderHot = clrHot;
}

CString CFlatEditInsung::GetText()
{
	CString strText;
	GetWindowText(strText);
	return strText;
}

long CFlatEditInsung::GetTextLong()
{
	CString strText;
	GetWindowText(strText);
	strText.Replace(",", "");
	return atol(strText);
}

void CFlatEditInsung::SetWindowTextLong(long nNumber, BOOL bThousandsSep)
{
	CString strNumber;
	strNumber.Format("%ld", nNumber);
	SetWindowText(bThousandsSep ? ::GetMyNumberFormat(strNumber) : strNumber);
}
