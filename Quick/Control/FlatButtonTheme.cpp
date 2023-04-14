#include "StdAfx.h"
#include "FlatButtonTheme.h"
#include "FlatButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BS_HORZMASK   (BS_LEFT | BS_RIGHT | BS_CENTER)
#define BS_VERTMASK   (BS_TOP | BS_BOTTOM | BS_VCENTER)


#define CBR_CLIENTRECT 0
#define CBR_CHECKBOX   1
#define CBR_RADIOBOX   2
#define CBR_CHECKTEXT  3
#define CBR_RADIOTEXT  4
#define CBR_GROUPTEXT  5
#define CBR_GROUPFRAME 6
#define CBR_PUSHBUTTON 7


CFlatButtonTheme::CFlatButtonTheme(void)
{
}

CFlatButtonTheme::~CFlatButtonTheme(void)
{
}

void CFlatButtonTheme::DrawButton(CDC* pDC, CXTPButton* pButton)
{
	if (pButton->IsPushButton())
	{
		DrawButtonBackground(pDC, pButton);

		DrawPushButtonText(pDC, pButton);
		DrawPushButtonIcon(pDC, pButton);

		if (pButton->IsDropDownStyle() && pButton->GetPushButtonStyle() != xtpButtonDropDownNoGlyph)
		{
			DrawPushButtonDropDown(pDC, pButton);
		}

		if (::GetFocus() == pButton->m_hWnd && pButton->GetShowFocus())
		{
			DrawFocusRect(pDC, pButton);
		}
		return;
	}

	switch (pButton->GetButtonStyle())
	{
	case BS_RADIOBUTTON:
	case BS_AUTORADIOBUTTON:
		DrawRadioButtonMark(pDC, pButton);
		DrawButtonText(pDC, pButton);
		break;

	case BS_3STATE:
	case BS_AUTO3STATE:
	case BS_CHECKBOX:
	case BS_AUTOCHECKBOX:
		DrawCheckBoxMark(pDC, pButton);
		DrawButtonText(pDC, pButton);
		break;

	case BS_GROUPBOX:
		if (pButton->GetBorderStyle() != 2)
		{
			DrawGroupBox(pDC, pButton);
			DrawButtonText(pDC, pButton);
		}
		break;

	default:
		TRACE(_T("Warning: unkown style"));
	}
}

void CFlatButtonTheme::DrawButtonBackground(CDC* pDC, CXTPButton* pButton)
{
	CFlatButton *pFlatBtn = (CFlatButton*)pButton;
	BOOL bPressed = pButton->IsPushed();
	BOOL bHot = pButton->IsHighlighted();
	BYTE bStyle = pButton->GetButtonStyle();
	BOOL bDefault = bStyle == BS_DEFPUSHBUTTON;
	BOOL bChecked = pButton->GetChecked();
	CRect rc(pButton->GetButtonRect());

	pDC->FillSolidRect(&rc, bHot ? pFlatBtn->m_crPushHotBorder : pFlatBtn->m_crPushBorder); 
	rc.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(&rc, bPressed ? XTPDrawHelpers()->LightenColor(30, pFlatBtn->m_crPushBack) : pFlatBtn->m_crPushBack); 
	rc.InflateRect(1, 1, 1, 1);
}

void CFlatButtonTheme::DrawPushButtonText(CDC* pDC, CXTPButton* pButton)
{
	CFlatButton *pFlatBtn = (CFlatButton*)pButton;
	BOOL bPressed = pButton->IsPushed();
	CString strText = pButton->GetButtonText();

	// if the string is empty just return.
	if (strText.IsEmpty())
		return;

	CRect rcText;
	UINT dsFlags;

	pDC->SelectObject(((CFlatButton*)pButton)->GetMyFont());
	CalcRects(pDC, pButton, &rcText, &dsFlags, NULL);

	BOOL  bSelected = pButton->GetChecked() || pButton->IsPushed();

	if (bSelected && (m_bOffsetHiliteText && !IsVisualThemeUsed(pButton)))
		rcText.OffsetRect(1, 1);

	pDC->SetTextColor(bPressed ? XTPDrawHelpers()->LightenColor(30, pFlatBtn->m_crPushText) : pFlatBtn->m_crPushText);

	if (pButton->GetMarkupUIElement())
	{
		XTPMarkupSetDefaultFont(pButton->GetMarkupContext(), NULL, pFlatBtn->m_crPushText);

		XTPMarkupRenderElement(pButton->GetMarkupUIElement(), pDC->GetSafeHdc(), rcText);

	}
	else
	{
#ifndef _XTP_ACTIVEX_BUTTON
		if (pButton->SendMessage(WM_QUERYUISTATE) & UISF_HIDEACCEL)
		{
			dsFlags |= DT_HIDEPREFIX;
		}
#endif
		rcText.InflateRect(1, 1, 1, 1);
		
		if(dsFlags & DT_SINGLELINE)
			dsFlags |= DT_VCENTER;

		pDC->DrawText(strText, rcText, dsFlags);
	}
}

void CFlatButtonTheme::DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton)
{
	CFlatButton *pFlatBtn = (CFlatButton*)pButton;
	BOOL bPressed = pButton->IsPushed();
	BOOL bHot = pButton->IsHighlighted();
	BOOL bEnabled = pButton->IsWindowEnabled();
	BOOL bChecked = pButton->GetChecked();

	CRect rcRadio;
	CalcRect(pDC, pButton, &rcRadio, CBR_RADIOBOX);

	CRect rcBox;
	const int BOX_SIZE = 13;

	rcBox.left = rcRadio.left + (pButton->GetStyle() & BS_RIGHT ? -1 : 2);
	rcBox.right = rcBox.left + BOX_SIZE;
	rcBox.top = rcRadio.top + (rcRadio.Height() - BOX_SIZE) / 2;
	rcBox.bottom = rcBox.top + BOX_SIZE;

	CPen pen;
	CBrush brush;
	pen.CreatePen(PS_SOLID, 1, bHot ? pFlatBtn->m_crCheckHotBorder : pFlatBtn->m_crCheckBorder);
	pDC->SelectObject(pen);
	brush.CreateSolidBrush(pFlatBtn->m_crCheckBack);
	pDC->SelectObject(brush);
	pDC->Ellipse(&rcBox);

	if(bChecked)
	{
		CPen pen2;
		CBrush brush2;
		pen2.CreatePen(PS_SOLID, 1, pFlatBtn->m_crCheckSelected);
		pDC->SelectObject(pen2);
		brush2.CreateSolidBrush(pFlatBtn->m_crCheckSelected);
		pDC->SelectObject(brush2);
		rcBox.DeflateRect(3, 3, 3, 3);
		pDC->Ellipse(&rcBox);
	}
}

void CFlatButtonTheme::DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton)
{
	CFlatButton *pFlatBtn = (CFlatButton*)pButton;
	BOOL bPressed = pButton->IsPushed();
	BOOL bHot = pButton->IsHighlighted();
	BYTE bStyle = pButton->GetButtonStyle();
	BOOL bEnabled = pButton->IsWindowEnabled();
	BOOL bChecked = pButton->GetChecked();

	CRect rcRadio;
	CalcRect(pDC, pButton, &rcRadio, CBR_CHECKBOX);
	
	CRect rcBox;
	const int BOX_SIZE = 12;

	rcBox.left = rcRadio.left + (pButton->GetStyle() & BS_RIGHT ? -1 : 2);
	rcBox.right = rcBox.left + BOX_SIZE;
	rcBox.top = rcRadio.top + (rcRadio.Height() - BOX_SIZE) / 2;
	rcBox.bottom = rcBox.top + BOX_SIZE;

	pDC->FillSolidRect(&rcBox, bHot ? pFlatBtn->m_crCheckHotBorder : pFlatBtn->m_crCheckBorder);
	rcBox.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(&rcBox, pFlatBtn->m_crCheckBack);

	if(bChecked)
	{
		rcBox.DeflateRect(2, 2, 2, 2);
		pDC->FillSolidRect(&rcBox, pFlatBtn->m_crCheckSelected);
	}
}

void CFlatButtonTheme::DrawButtonText(CDC* pDC, CXTPButton* pButton)
{
	CFlatButton *pFlatBtn = (CFlatButton*)pButton;
	BOOL bChecked = pButton->GetChecked();

	pDC->SelectObject(pFlatBtn->GetMyFont());
	pDC->SetTextColor(pButton->IsWindowEnabled() ? (bChecked ? pFlatBtn->m_crCheckSelectedText : pFlatBtn->m_crCheckText) : m_crTextDisabled);
	pDC->SetBkMode(TRANSPARENT);

	static const BYTE buttonsStyles[] =
	{
		CBR_PUSHBUTTON,
		CBR_PUSHBUTTON,
		CBR_CHECKTEXT,
		CBR_CHECKTEXT,
		CBR_RADIOTEXT,
		CBR_CHECKTEXT,
		CBR_CHECKTEXT,
		CBR_GROUPTEXT,
		CBR_CLIENTRECT,
		CBR_RADIOTEXT,
		CBR_CLIENTRECT,
		CBR_PUSHBUTTON,
	};

	RECT    rc;
	int     x, y, cx = 0, cy = 0;

	CString strText;
	UINT dsFlags = DT_SINGLELINE | DT_LEFT | DT_TOP | DT_NOCLIP;
	BYTE bStyle = pButton->GetButtonStyle();

	DWORD dwStyle = pButton->GetStyle();

	BOOL pbfPush = pButton->IsPushButton();
	if (pbfPush)
	{
		CalcRect(pDC, pButton, &rc, CBR_PUSHBUTTON);
	}
	else
	{
		CalcRect(pDC, pButton, &rc, buttonsStyles[bStyle]);
	}

	// Alignment
	strText = pButton->GetButtonText();
	UINT wAlignment = pButton->GetTextAlignment();

	HGDIOBJ hImage = 0;

	if (pButton->GetStyle() & BS_BITMAP)
	{
		hImage = (HGDIOBJ)pButton->SendMessage(BM_GETIMAGE, IMAGE_BITMAP);
		if (!hImage)
			return;

		BITMAP bmp;
		GetObject(hImage, sizeof(BITMAP), &bmp);
		cx = bmp.bmWidth;
		cy = bmp.bmHeight;
	}
	else if (pButton->GetStyle() & BS_ICON)
	{
		hImage = (HGDIOBJ)pButton->SendMessage(BM_GETIMAGE, IMAGE_ICON);
		if (!hImage)
			return;

		cx = cy = 16;
	}
	else
	{
		// Text button
		if (strText.IsEmpty())
			return;

		if (pButton->GetMarkupUIElement())
		{
			XTPMarkupSetDefaultFont(pButton->GetMarkupContext(), (HFONT)pButton->SendMessage(WM_GETFONT), COLORREF_NULL);

			CSize sz = XTPMarkupMeasureElement(pButton->GetMarkupUIElement(), rc.right - rc.left, rc.bottom - rc.top);

			cx = sz.cx;
			cy = sz.cy;

		}
		else
		{
			if (pButton->GetStyle() & BS_MULTILINE)
			{
				dsFlags |= DT_WORDBREAK | DT_EDITCONTROL;
				dsFlags &= ~DT_SINGLELINE;
			}

			CRect rcText(0, 0, rc.right - rc.left, 0);
			pDC->DrawText(strText, rcText, dsFlags | DT_CALCRECT);

			cx = rcText.Width();
			cy = rcText.Height();
		}
	}

	CRect rcText(rc);
	if (pbfPush && ((pButton->GetStyle() & BS_MULTILINE) == 0)) rcText.DeflateRect(m_cxBorder, m_cyBorder);

	// Horizontal
	switch (wAlignment & BS_HORZMASK)
	{
	case BS_LEFT:
		x = rc.left + (pbfPush ? m_cxBorder : 0);
		break;

	case BS_RIGHT:
		x = rc.right - cx -  (pbfPush ? m_cxBorder : 0);
		dsFlags |= DT_RIGHT;
		break;

	default:
		x = (rc.left + rc.right - cx) / 2;
		dsFlags |= DT_CENTER;
		break;
	}

	// Vertical
	switch (wAlignment & BS_VERTMASK)
	{
	case BS_TOP:
		y = rc.top + (pbfPush ? m_cyBorder : 0);
		break;

	case BS_BOTTOM:
		y = rc.bottom - cy - (pbfPush ? m_cyBorder : 0);
		dsFlags |= DT_BOTTOM;
		break;

	default:
		y = (rc.top + rc.bottom - cy) / 2;
		dsFlags |= DT_VCENTER;
		break;
	}

	if (dwStyle & BS_BITMAP)
	{
		pDC->DrawState(CPoint(x, y), CSize(cx, cy), (HBITMAP)hImage, DSS_NORMAL, 0);
	}
	else if (dwStyle & BS_ICON)
	{
		pDC->DrawState(CPoint(x, y), CSize(cx, cy), (HICON)hImage, DSS_NORMAL, (HBRUSH)0);
	}
	else if (bStyle !=  LOBYTE(BS_USERBUTTON))
	{
		if (pButton->GetMarkupUIElement())
		{
			XTPMarkupSetDefaultFont(pButton->GetMarkupContext(), NULL, pDC->GetTextColor());

			XTPMarkupRenderElement(pButton->GetMarkupUIElement(), pDC->GetSafeHdc(), CRect(x, y, x + cx, y + cy));
		}
		else
		{
			if (pButton->GetExStyle() & WS_EX_RTLREADING)
				dsFlags |= DT_RTLREADING;

#ifndef _XTP_ACTIVEX_BUTTON
			if (pButton->SendMessage(WM_QUERYUISTATE) & UISF_HIDEACCEL)
			{
				dsFlags |= DT_HIDEPREFIX;
			}
#endif

			if (dwStyle & BS_MULTILINE)
			{
				pDC->DrawText(strText, CRect(x, y, x + cx, y + cy), dsFlags | DT_NOCLIP);
			}
			else
			{
				pDC->DrawText(strText, rcText, dsFlags);
			}
		}
	}

	if (::GetFocus() == pButton->m_hWnd && pButton->GetShowFocus())
	{
#ifndef _XTP_ACTIVEX_BUTTON
		if ((pButton->SendMessage(WM_QUERYUISTATE) & UISF_HIDEFOCUS) == 0)
#endif
		{
			if (!pbfPush)
			{

				RECT rcClient = pButton->GetButtonRect();

				if (bStyle == LOBYTE(BS_USERBUTTON))
					CopyRect(&rc, &rcClient);
				else
				{
					// Try to leave a border all around text.  That causes
					// focus to hug text.
					rc.top = max(rcClient.top, y - m_cyBorder);
					rc.bottom = min(rcClient.bottom, rc.top + m_cyEdge + cy);

					rc.left = max(rcClient.left, x-m_cxBorder);
					rc.right = min(rcClient.right, rc.left + m_cxEdge + cx);
				}
			}
			else
				InflateRect(&rc, -m_cxBorder, -m_cyBorder);

			pDC->SetTextColor(GetXtremeColor(COLOR_BTNTEXT));
			pDC->SetBkColor(GetXtremeColor(COLOR_WINDOW));

			// Are back & fore colors set properly?
			::DrawFocusRect(pDC->GetSafeHdc(), &rc);
		}
	}
}