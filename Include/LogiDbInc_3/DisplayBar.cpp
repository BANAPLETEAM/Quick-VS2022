
#include "stdafx.h"
#include "DisplayBar.h"
#include "Resource.h"
#include "TextProgressCtrl.h"

#define IDC_PROGRSS_CTRL	1

#define DELAY_SHOW_TIMER	1
#define WAIT_MODE_TIMER		2


CDisplayBar::CDisplayBar(void)
{
	m_nShowCount = 0;
	m_pctlProgress = NULL;
	m_pbtnCancel = NULL;
	m_pWndParent = NULL;
	m_hSkinRegion = NULL;
	m_nSkinHeight = 0;
	m_nSkinWidth = 0;
	m_bHideCancel = FALSE;
	m_strProgressText = PROGRESS_START_TEXT;
	m_strCenterText = TEXT_DEFAULT_MSG;
	m_fProgressRate = 0;
	m_strFontFaceName = "¸¼Àº °íµñ";
	m_nFontSize = 15;
	m_nFontWeight = FW_NORMAL;
	m_hCancelEvent = NULL;
	m_bWaitMode = FALSE;
	m_bWaitColorValueInc = FALSE;
	m_bMouseDown = FALSE;
	m_rcNewPos = CRect(0, 0, 0, 0);
	m_bUserCancel = FALSE;
}

CDisplayBar::~CDisplayBar(void)
{
	DELETE_OBJECT(m_pctlProgress);
	DELETE_OBJECT(m_pbtnCancel);
}

int CDisplayBar::Create(CWnd *pWndParent)
{
	HDC hDC=NULL;
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if(hDC)
	{
		::EnumDisplayMonitors(hDC,NULL,MonitorEnumProc, (LPARAM)this);
		DeleteDC(hDC);
	}

	m_pWndParent = pWndParent;
	CString strWndClass = AfxRegisterWndClass(NULL,AfxGetApp()->LoadStandardCursor(IDC_ARROW),GetSysColorBrush(COLOR_WINDOW),NULL);
	BOOL bRet = CreateEx(0,strWndClass,NULL,WS_POPUP,0,0,0,0, ::GetDesktopWindow(),NULL);

	if(bRet)
	{
		m_pctlProgress = new CTextProgressCtrl;
		if(m_pctlProgress->Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_PROGRSS_CTRL))
		{
			m_pctlProgress->ModifyStyleEx(NULL, WS_EX_STATICEDGE);
			m_pctlProgress->SetWindowText(m_strProgressText);
			m_pctlProgress->SetRange(0, 1000);
			m_pctlProgress->SetForeColour(RGB(0, 255, 0));
			m_pctlProgress->SetTextForeColour(RGB(0, 0, 0));

			m_pbtnCancel = new CBitmapButton;
			if(m_pbtnCancel->Create("Ãë¼Ò", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_CANCEL_BTN))
			{
				m_pbtnCancel->SetButtonStyle(BS_OWNERDRAW);
				m_pbtnCancel->LoadBitmaps(IDB_CANCEL_UP, IDB_CANCEL_DOWN);
				m_pbtnCancel->SizeToContent();
				SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

				return TRUE;
			}
		}
	}
	
	return FALSE;
}

void CDisplayBar::Hide()
{
	m_bMouseDown = FALSE;
	KillTimer(DELAY_SHOW_TIMER);
	KillTimer(WAIT_MODE_TIMER);
	MoveWindow(0,0,0,0);
	ShowWindow(SW_HIDE);
}

void CDisplayBar::Show()
{
	SetTimer(WAIT_MODE_TIMER, 50, NULL);
	m_bUserCancel = FALSE;
	ResetEvent(m_hCancelEvent);
	//SetForegroundWindow();

/*
	CRect rcMainFrame;
	CPoint ptMainFrame;

	if(AfxGetMainWnd())
	{
		AfxGetMainWnd()->GetWindowRect(rcMainFrame);
		ptMainFrame.x = (rcMainFrame.left + rcMainFrame.right) / 2;
		ptMainFrame.y = (rcMainFrame.top + rcMainFrame.bottom) / 2;
	}
	else
	{
		ptMainFrame.x = 0;
		ptMainFrame.y = 0;
	}
*/
	CPoint ptMouse;
	GetCursorPos(&ptMouse);


	m_rcClient.SetRect(0, 0, 0, 0);

	if(m_aryMonitors.GetCount() == 0)
	{
		CRect rc;
		rc.left = 0;
		rc.right = ::GetSystemMetrics(SM_CXSCREEN);
		rc.top = 0;
		rc.bottom =  ::GetSystemMetrics(SM_CYSCREEN);

		MONITORINFOEX monitor;
		monitor.rcWork = rc;
		m_aryMonitors.Add(monitor);
	}

	for(int i = 0; i < m_aryMonitors.GetCount(); i++)
	{
		CRect rc(m_aryMonitors.GetAt(i).rcWork);

		if(m_rcNewPos != CRect(0, 0, 0, 0) && rc.PtInRect(m_rcNewPos.CenterPoint()))
		{
			m_rcClient = m_rcNewPos;
			break;
		}

		if(rc.PtInRect(ptMouse))
		{
			int x = (rc.right + rc.left) / 2;
			int y = (rc.top + rc.bottom) / 2;
			x = x - m_rcImage.Width() / 2;
			y = y - m_rcImage.Height() / 2;
			m_rcClient.SetRect(x, y, x + m_rcImage.Width(), y + m_rcImage.Height());
		}
	}

	RepositionControls();
	MoveWindow(m_rcClient);
	ShowWindow(SW_SHOWNA);
	RedrawWindow();
} 

void CDisplayBar::RepositionControls()
{
	if(m_bHideCancel)
	{
		CRect rcProgress = m_rcImage;
		rcProgress.DeflateRect(20, 15, 20, 39);
		m_pctlProgress->MoveWindow(rcProgress);
		m_pbtnCancel->ShowWindow(SW_HIDE);
	}
	else
	{
		CRect rcProgress = m_rcImage;
		rcProgress.DeflateRect(20, 15, 73, 39);
		m_pctlProgress->MoveWindow(rcProgress);

		CRect rcCancel = m_rcImage;
		rcCancel.SetRect(rcCancel.right - 69, rcCancel.top + 15, rcCancel.right - 10, rcCancel.bottom - 39);
		m_pbtnCancel->SetFont(m_FontManager.GetFont(m_strFontFaceName, m_nFontSize, m_nFontWeight));
		m_pbtnCancel->MoveWindow(rcCancel);
		m_pbtnCancel->ShowWindow(SW_SHOW);
	}
}


BEGIN_MESSAGE_MAP(CDisplayBar, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CDisplayBar::OnBnClickedCancelBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CDisplayBar::OnPaint()
{
	CPaintDC dc(this);

	CRect rc = m_rcImage;
	rc.DeflateRect(20, 38, 60, 5);

	CFont *pOldFont = dc.SelectObject(m_FontManager.GetFont("¸¼Àº °íµñ", 16, FW_BOLD));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.DrawText(m_strCenterText, -1, rc, DT_LEFT | DT_WORDBREAK | DT_END_ELLIPSIS);
	dc.SelectObject(pOldFont);
}

void CDisplayBar::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == DELAY_SHOW_TIMER)
	{
		KillTimer(nIDEvent);
		Show();
	}
	else if(nIDEvent == WAIT_MODE_TIMER)
	{
		if(m_bWaitMode)
			ProgressWaitMode();
	}
	CWnd::OnTimer(nIDEvent);
}

BOOL CDisplayBar::OnEraseBkgnd(CDC* pDC)
{
	CDC memDC;
	CBitmap *pOldBitmap;
	BITMAP bm;

	memDC.CreateCompatibleDC(pDC);
	GetObject(m_biSkinBackground.GetSafeHandle(), sizeof(bm), &bm);
	pOldBitmap=memDC.SelectObject(&m_biSkinBackground);

	pDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	return TRUE;
}

BOOL CDisplayBar::SetSkin(UINT nBitmapID,short red,short green,short blue)
{
	BITMAP bm;

	m_biSkinBackground.DeleteObject();

	if (!m_biSkinBackground.LoadBitmap(nBitmapID))
		return FALSE;
	GetObject(m_biSkinBackground.GetSafeHandle(), sizeof(bm), &bm);
	m_nSkinWidth=bm.bmWidth;
	m_nSkinHeight=bm.bmHeight;
	m_rcImage.SetRect(0,0,bm.bmWidth,bm.bmHeight);

	if (red!=-1 && green!=-1 && blue!=-1)
	{
		// No need to delete the HRGN,  SetWindowRgn() owns it after being called
		m_hSkinRegion=GenerateRegion((HBITMAP)m_biSkinBackground.GetSafeHandle(),(BYTE) red,(BYTE) green,(BYTE) blue);
		SetWindowRgn(m_hSkinRegion, true);
	}

	return TRUE;
}

HRGN CDisplayBar::GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue)
{
	WORD wBmpWidth,wBmpHeight;
	HRGN hRgn, hTmpRgn;

	// 24bit pixels from the bitmap
	BYTE *pPixels = Get24BitPixels(hBitmap, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;

	// create our working region
	hRgn = CreateRectRgn(0,0,wBmpWidth,wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }

	DWORD p=0;
	for (WORD y=0; y<wBmpHeight; y++)
	{
		for (WORD x=0; x<wBmpWidth; x++)
		{
			BYTE jRed   = pPixels[p+2];
			BYTE jGreen = pPixels[p+1];
			BYTE jBlue  = pPixels[p+0];

			if (jRed==red && jGreen==green && jBlue==blue)
			{
				// remove transparent color from region
				hTmpRgn = CreateRectRgn(x,y,x+1,y+1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}

			// next pixel
			p+=3;
		}
	}

	// release pixels
	delete pPixels;

	// return the region
	return hRgn;
}

BYTE* CDisplayBar::Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight)
{
	BITMAP bmpBmp;
	LPBITMAPINFO pbmiInfo;
	BITMAPINFO bmiInfo;
	WORD wBmpWidth, wBmpHeight;

	GetObject(pBitmap, sizeof(bmpBmp),&bmpBmp);
	pbmiInfo   = (LPBITMAPINFO)&bmpBmp;

	wBmpWidth  = (WORD)pbmiInfo->bmiHeader.biWidth;
	wBmpWidth -= (wBmpWidth%4);
	wBmpHeight = (WORD)pbmiInfo->bmiHeader.biHeight;

	*pwWidth  = wBmpWidth;
	*pwHeight = wBmpHeight;

	BYTE *pPixels = new BYTE[wBmpWidth*wBmpHeight*3];
	if (!pPixels) return NULL;

	HDC hDC =::GetWindowDC(NULL);

	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = wBmpWidth;
	bmiInfo.bmiHeader.biHeight = -wBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = wBmpWidth*wBmpHeight*3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;

	// get pixels from the original bitmap converted to 24bits
	int iRes = GetDIBits(hDC,pBitmap,0,wBmpHeight,(LPVOID)pPixels,&bmiInfo,DIB_RGB_COLORS);

	// release the device context
	::ReleaseDC(NULL,hDC);

	// if failed, cancel the operation.
	if (!iRes)
	{
		delete pPixels;
		return NULL;
	};

	// return the pixel array
	return pPixels;
}


void CDisplayBar::SetProgressText(CString strText, BOOL bRedraw)
{
	m_strProgressText = strText;
	if(bRedraw)
		m_pctlProgress->SetWindowText(strText);
}

void CDisplayBar::SetProgressRate(double fRate, BOOL bRedraw)
{
	m_fProgressRate = fRate;
	if(bRedraw)
		m_pctlProgress->SetPos((int)(fRate*10));

	if(m_bWaitMode)
		SetWaitMode(FALSE);
}

void CDisplayBar::RefreshProgress()
{
	m_pctlProgress->SetWindowText(m_strProgressText);
	m_pctlProgress->SetPos((int)(m_fProgressRate*10));

	if(m_bWaitMode)
		SetWaitMode(FALSE);
}

void CDisplayBar::OnBnClickedCancelBtn()
{
	m_pctlProgress->SetWindowText("Ãë¼ÒÁßÀÔ´Ï´Ù.");
	if(m_hCancelEvent)
		SetEvent(m_hCancelEvent);
	m_bUserCancel = TRUE;
}

void CDisplayBar::SetWaitMode(BOOL bWaitMode, BOOL bIgnoreAlter)
{
	if(!bIgnoreAlter && m_bWaitMode == bWaitMode)
		return;

	m_bWaitMode = bWaitMode;
	ProgressWaitMode();
}


void CDisplayBar::ProgressWaitMode()
{
	if(m_bWaitMode)
	{
		COLORREF clrBack = m_pctlProgress->GetBkColour();
		int R = GetRValue(clrBack);
		int G = GetGValue(clrBack);
		int B = GetBValue(clrBack);

		if(R <= 20 && B <= 20)
		{
			m_bWaitColorValueInc = TRUE;	
		}
		else if(R > 200 && B > 200)
		{
			m_bWaitColorValueInc = FALSE;	
		}
		else if(R == 255 && G == 255 && B == 255)
		{
			m_bWaitColorValueInc = !m_bWaitColorValueInc;
			m_pctlProgress->SetBkColour(RGB(0, 255, 0));
			m_pctlProgress->RedrawWindow();
			return;
		}

		if(m_bWaitColorValueInc)
		{
			R += 15;B += 15;
		}
		else
		{
			R -= 15;B -= 15;
		}

		clrBack = RGB(R, G, B);
		m_pctlProgress->SetBkColour(clrBack);
		m_pctlProgress->RedrawWindow();
	}
	else 
	{
		m_pctlProgress->SetBkColour(::GetSysColor(COLOR_WINDOW));
	}
}

void CDisplayBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcClient;
	GetWindowRect(&rcClient);
	GetCursorPos(&m_ptMouse);
	if(rcClient.PtInRect(m_ptMouse))
	{
		SetCapture();
		m_bMouseDown = TRUE;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CDisplayBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bMouseDown)
	{
		ReleaseCapture();
		m_bMouseDown = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CDisplayBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bMouseDown)
	{
		CPoint ptMouse2;
		CRect rcClient;
		GetCursorPos(&ptMouse2);

		GetWindowRect(&rcClient);
		rcClient.OffsetRect(ptMouse2 - m_ptMouse);
		m_rcNewPos = rcClient;
		MoveWindow(rcClient);
		m_ptMouse = ptMouse2;
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CDisplayBar::ShowText(CString strText, DWORD dwDelayShow)
{
	SetText(strText);
	if(dwDelayShow > 0)
		SetTimer(DELAY_SHOW_TIMER, dwDelayShow, NULL);
	else
		Show();
}

void CDisplayBar::SetStartPos(CPoint ptStart)
{
	if(ptStart != CPoint(-1, -1))
	{
		m_rcNewPos.left = ptStart.x;
		m_rcNewPos.top = ptStart.y;
		m_rcNewPos.right = ptStart.x + m_rcImage.Width();
		m_rcNewPos.bottom = ptStart.y + m_rcImage.Height();
	}
}
