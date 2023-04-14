/*|*\
|*|  File:      FocusEditCtrl2.h
|*|  
|*|  By:        James R. Twine, Rubin And Associates, Inc.
|*|             Copyright 1988, Rubin And Associates, Inc.
|*|  Date:      Friday, October 09, 1998
|*|             
|*|             This implementes an Edit Control that provides
|*|             a custom background color to indicate focus.
|*|             (This class uses static variables for the colors,
|*|             so all controls that uses this class will use the
|*|             same colors).
|*|				Portions of this code are derived from CDropEdit
|*|				by Chris Losinger.  (See comments below)
|*|             
|*|             These Changes May Be Freely Incorporated Into 
|*|             Projects Of Any Type Subject To The Following 
|*|             Conditions:
|*|             
|*|             o This Header Must Remain In This File, And Any
|*|               Files Derived From It
|*|             o Do Not Misrepresent The Origin Of Any Parts Of 
|*|               This Code (IOW, Do Not Claim You Wrote It)
|*|             
|*|             A "Mention In The Credits", Or Similar Acknowledgement,
|*|             Is *NOT* Required.  It Would Be Nice, Though! :)
|*|             
|*|  Revisions: 
|*|             xx/xx/99 Incorporated The Ability To "Filter" The Input.
|*|	
\*|*/
//	CDropEdit
//	Copyright 1997 Chris Losinger
//
//	This code is freely distributable and modifiable, as long as credit
//	is given to where it's due. Watch, I'll demonstrate :
//
//	shortcut expansion code modified from :
//	CShortcut, 1996 Rob Warner

#include "StdAfx.h"
#include "FocusEditCtrl2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HBRUSH CFocusEditCtrl2::m_hBrush = NULL;

static	COLORREF	g_crATColor = RGB( 0x00, 0x00, 0x00 );	// Active (Focused) Text Color
static	COLORREF	g_crABColor = RGB( 0xFF, 0xFF, 0x00 );	// Active (Focused) Background Color

/////////////////////////////////////////////////////////////////////////////
// CFocusEditCtrl2

CFocusEditCtrl2::CFocusEditCtrl2()	:
	m_bExcludeMask( false ),
	m_bIncludeMask( false )
{
	if(m_hBrush == NULL)
		m_hBrush = CreateSolidBrush(g_crABColor);

	m_clrBk = RGB(255, 255, 255);
	m_clrText = RGB(0, 0, 0);

	m_clrTextNoFocus = RGB(180, 180, 180);
	m_clrTextNoFocusHasText = RGB(0, 0, 0);
	m_bUseNoFocusHasTextColor = FALSE;

	m_strFaceName = "맑은 고딕";
	m_nHeight = 13;
	m_nWeight = FW_NORMAL;

	m_bInitFont = FALSE;
	m_bCenter = FALSE;
	m_dwData = NULL;
	m_bGradientBK = TRUE;
	m_nGradientScale = 20;

	m_bMustClrText = FALSE;;
	m_bMustClrBack = FALSE;;
}


CFocusEditCtrl2::~CFocusEditCtrl2()
{
}


BEGIN_MESSAGE_MAP(CFocusEditCtrl2, CEdit)
	//{{AFX_MSG_MAP(CFocusEditCtrl2)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT_EX(EN_KILLFOCUS, OnKillFocusReflect)
	ON_CONTROL_REFLECT_EX(EN_SETFOCUS, OnSetFocusReflect)
	ON_MESSAGE( WM_CUT, OnCut )
	ON_MESSAGE( WM_COPY, OnCopy )
	ON_MESSAGE( WM_PASTE, OnPaste )
	ON_MESSAGE( WM_CLEAR, OnClear )
	ON_MESSAGE( WM_UNDO, OnUndo )
//	ON_MESSAGE( WM_SELECTALL, OnSelectAll )
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusEditCtrl2 message handlers

HBRUSH CFocusEditCtrl2::CtlColor(CDC* pDC, UINT /*nCtlColor*/ ) 
{
	DWORD	dwStyle = GetStyle();

	CRect rc1, rc2;
	GetRect(rc1);
	if(rc1.left == 0) {
		GetClientRect(rc2);
		rc2.DeflateRect(CSize(2, 1));
		SetRect(rc2);
	}

	if( ( GetFocus() == this ) && ( !( dwStyle &			// If We Have The Focus
			WS_DISABLED ) ) && ( !( dwStyle & 				// And Control Is Not Disabled
			ES_READONLY ) ) )								// And Control Is Not ReadOnly
	{
		pDC -> SetTextColor( g_crATColor );					// Set Text Color
		pDC -> SetBkColor( g_crABColor );					// Set Background Color

		//g_bana_log->Print("CtlColor(FOCUSED)\n");

		return m_hBrush;						// Return Custom BG Brush
	}


	//g_bana_log->Print("CtlColor(NOT FOCUSED)\n");
	return( NULL );											// Do Default
}


BOOL CFocusEditCtrl2::OnEraseBkgnd(CDC* pDC) 
{
	DWORD	dwStyle = GetStyle();
	CRect	rClient;
	BOOL	bStatus = TRUE;

	if( ( GetFocus() == this ) && ( !( dwStyle &			// If We Have The Focus
			WS_DISABLED ) ) && ( !( dwStyle & 				// And Control Is Not Disabled
			ES_READONLY ) ) )								// And Control Is Not ReadOnly
	{
		GetClientRect( &rClient );							// Get Our Area
		pDC->FillSolidRect( rClient, g_crABColor );		// Repaint Background
		//g_bana_log->Print("OnEraseBkgnd(ERASE)\n");
	}
	else
	{
		bStatus = CEdit::OnEraseBkgnd( pDC );				// Do Default
		//g_bana_log->Print("OnEraseBkgnd(DEFAULT)\n");
	}


	return( bStatus );										// Return Status
}


BOOL	CFocusEditCtrl2::OnKillFocusReflect( void ) 
{
	Invalidate(TRUE);											// Cause Background To Repaint
	//g_bana_log->Print("OnKillFocusReflect\n");
	return( FALSE );											// Pass On To Parent
}


BOOL	CFocusEditCtrl2::OnSetFocusReflect() 
{
	Invalidate(TRUE);											// Cause Background To Repaint
	//g_bana_log->Print("OnSetFocusReflect\n");
	return( FALSE );											// Pass On To Parent
}


int		CFocusEditCtrl2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	DragAcceptFiles(TRUE);
	SetSel(0xFFFF);

	return 0;
}		   


BOOL	CFocusEditCtrl2::PreTranslateMessage(MSG* pMsg) 
{
	if( ( pMsg -> message ) == WM_CHAR )					// If A Char Message
	{
		TCHAR	cKey = (TCHAR)( pMsg -> wParam );			// Get Key (Character In Question)
		
		//
		//	If A Paste Operation...
		//
//		if( ( ( cKey == VK_INSERT ) && ( ::GetAsyncKeyState(
		if( ( ( cKey == VK_INSERT ) && ( ::GetKeyState(
				VK_SHIFT ) & 0x8000 ) ) || ( ( cKey == 
//				'v' ) && ( ::GetAsyncKeyState( 
				'v' ) && ( ::GetKeyState( 
				VK_CONTROL ) & 0x8000 ) ) )					// If A Paste Operation
		{
			Paste();										// Call Paste Handler
			return( TRUE );									// Handled This Message (Eat Keystroke)
		}
		if( ( m_bIncludeMask ) &&							// If Using An Include Mask
				( !m_sIncludeCharMask.IsEmpty() ) )			// And Including Certain Characters
		{
			if( ( cKey != VK_BACK ) && ( !::_tcschr(		// If Not A Backspace And
					m_sIncludeCharMask, cKey ) ) )			// If Key Is Not In The Include Mask
			{										 
				return( TRUE );								// Handled This Message (Eat Keystroke)
			}
		}
		else if( ( m_bExcludeMask ) &&						// If Using An Exclude Mask
				( !m_sExcludeCharMask.IsEmpty() ) )			// And Excluding Certain Characters
		{
			if( ::_tcschr( m_sExcludeCharMask, cKey ) )		// If Key Is In The Exclude Mask
			{										 
				return( TRUE );								// Handled This Message (Eat Keystroke)
			}
		}
	}
	return( CEdit::PreTranslateMessage( pMsg ) );			// Do Default If Not Handled
}


void	CFocusEditCtrl2::StripFilteredChars( LPTSTR cpBuffer )
{
	int		iChars = (int)::_tcslen( cpBuffer );
	int		iSizeofChar = sizeof( TCHAR );

	if( ( m_bIncludeMask ) &&								// If Using An Include Mask
			( !m_sIncludeCharMask.IsEmpty() ) )				// And Including Certain Characters
	{
		TCHAR	*pWhere = NULL;

		pWhere = ::_tcsspnp( cpBuffer, m_sIncludeCharMask );// Look For Characters Not In Include Mask
		while( pWhere )										// While "Bad" Characters Found
		{
			int		iLeft = ( ( ( iChars - 1 ) * 
							iSizeofChar ) - (int)( pWhere - 
							cpBuffer ) );					// Calculate The Amount Of Memory To Move

			::memmove( pWhere, ( pWhere + 1 ), iLeft );		// Shift Memory Over
			pWhere = ::_tcsspnp( cpBuffer, 
					m_sIncludeCharMask );					// Look For Characters Not In Include Mask
		}
	}
	else if( ( m_bExcludeMask ) &&							// If Using An Exclude Mask
			( !m_sExcludeCharMask.IsEmpty() ) )				// And Excluding Certain Characters
	{
		TCHAR	*pWhere = NULL;

		pWhere = ::_tcspbrk( cpBuffer, m_sExcludeCharMask );// Look For A "Bad" Character
		while( pWhere )										// While "Bad" Characters Found
		{
			int		iLeft = ( ( ( iChars - 1 ) * 
							iSizeofChar ) - (int)( pWhere - 
							cpBuffer ) );					// Calculate The Amount Of Memory To Move

			::memmove( pWhere, ( pWhere + 1 ), iLeft );		// Shift Memory Over
			pWhere = ::_tcspbrk( cpBuffer, 
					m_sExcludeCharMask );					// Find Next "Bad" Character
		}
	}
	return;													// Done!
}


LRESULT CFocusEditCtrl2::OnPaste( WPARAM, LPARAM )
{
	if( OpenClipboard() )									// Open The Clipboard
	{
#if defined( _UNICODE )
		HANDLE	hClipData = ::GetClipboardData( 
						CF_UNICODETEXT );					// Get Unicode Text Data From Clipboard
#else
		HANDLE	hClipData = ::GetClipboardData( CF_TEXT );	// Get ANSI Text Data From Clipboard
#endif
		if( hClipData )										// If Obtained
		{
			LPCTSTR cpText = (LPCTSTR)::GlobalLock( 
							hClipData );					// Lock Memory Into String Pointer
			if( cpText )									// If Pointer To Text Obtained
			{
				TCHAR	*cpBuffer = new TCHAR[ ::GlobalSize( 
								hClipData ) ];				// Allocate Buffer

				if( cpBuffer )								// If Buffer Allocated
				{
					::_tcscpy( cpBuffer, cpText );			// Copy Over The Text
					StripFilteredChars( cpBuffer );			// Remove Any Bad Characters
					ReplaceSel( cpBuffer, TRUE );			// Replace Selection
					
					delete [] cpBuffer;						// Free Buffer
				}
				::GlobalUnlock( (LPVOID)cpText );			// Release Memory Pointer
 			}
		}
		::CloseClipboard();									// Close The Clipboard
	}
	else
	{
		::MessageBeep( MB_ICONEXCLAMATION );				// Beep At User
		TRACE( _T( "FocusEditCtrl2: Warning!  Failed To Open The Clipboard For A Paste Operation!\n" ) );
	}
	return( 0 );											// Done!
}


LRESULT CFocusEditCtrl2::OnCut( WPARAM, LPARAM )
{
	return( Default() );									// Do Default Behaviour
}


LRESULT CFocusEditCtrl2::OnCopy( WPARAM, LPARAM )
{
	return( Default() );									// Do Default Behaviour
}


LRESULT CFocusEditCtrl2::OnClear( WPARAM, LPARAM )
{
	return( Default() );									// Do Default Behaviour
}


LRESULT CFocusEditCtrl2::OnUndo( WPARAM, LPARAM )
{
	return( Default() );									// Do Default Behaviour
}



/*|*\
|*|  JRT:
|*|  Original code was part of CDropEdit 
|*|  Copyright 1997 Chris Losinger
\*|*/
void	CFocusEditCtrl2::OnDropFiles( HDROP hdDropInfo )
{
	UINT		uiFiles = 0;
	TCHAR		*pBuffer = new TCHAR[ _MAX_PATH ];			// Allocate Buffer

	if( ( !pBuffer ) || ( !hdDropInfo ) )					// If No Drop Info Or Buffer
	{
		if( pBuffer )										// If Buffer Was Allocated
		{
			delete [] pBuffer;								// Free Buffer
		}
		return;												// Stop Here
	}				 
	uiFiles = ::DragQueryFile( hdDropInfo, (UINT)-1, NULL,
			0 );											// Get Files Dropped
	//
	//	Note!  Only Interested In The First File!
	//
	if( uiFiles )											// If One Or More Files Dropped
	{													
		::memset( pBuffer, 0, ( sizeof( TCHAR ) * 
				_MAX_PATH ) );								// Init Buffer
		::DragQueryFile( hdDropInfo, 0, pBuffer, 
				_MAX_PATH );								// Get File Path
	}
	::DragFinish( hdDropInfo );								// Done With Drop Info

/*
	CString expandedFile = ExpandShortcut(firstFile);

	// if that worked, we should have a real file name
	if (expandedFile!="") 
		firstFile=expandedFile;
	struct _stat buf;
	// get some info about that file
	int result = _stat( firstFile, &buf );
	if( result == 0 ) {

		// verify that we have a dir (if we want dirs)
		if ((buf.st_mode & _S_IFDIR) == _S_IFDIR) {
			if (m_bUseDir)
				SetWindowText(firstFile);

		// verify that we have a file (if we want files)
		} else if ((buf.st_mode & _S_IFREG) == _S_IFREG) {
			if (!m_bUseDir)
				SetWindowText(firstFile);
		}
	}
*/
	StripFilteredChars( pBuffer );							// Strip The Filtered Characters
	ReplaceSel( pBuffer, TRUE );							// Replace Selection With FilePath Text
	
	delete [] pBuffer;										// Free Buffer

	return;													// Done!
}


/*|*\
|*|  JRT:
|*|  original code was part of CShortcut 
|*|  1996 by Rob Warner
|*|  rhwarner@southeast.net
|*|  http://users.southeast.net/~rhwarner
\*|*/
/*
CString CFocusEditCtrl2::ExpandShortcut(CString &inFile)
{
	CString outFile = "";

    // Make sure we have a path
    ASSERT(inFile != _T(""));

    IShellLink* psl;
    HRESULT hres;
    LPTSTR lpsz = inFile.GetBuffer(MAX_PATH);

    // Create instance for shell link
    hres = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
        IID_IShellLink, (LPVOID*) &psl);
    if (SUCCEEDED(hres))
    {
        // Get a pointer to the persist file interface
        IPersistFile* ppf;
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*) &ppf);
        if (SUCCEEDED(hres))
        {
            // Make sure it's ANSI
            WORD wsz[MAX_PATH];
            ::MultiByteToWideChar(CP_ACP, 0, lpsz, -1, wsz, MAX_PATH);

            // Load shortcut
            hres = ppf->Load(wsz, STGM_READ);
            if (SUCCEEDED(hres)) {
				WIN32_FIND_DATA wfd;
				// find the path from that
				HRESULT hres = psl->GetPath(outFile.GetBuffer(MAX_PATH), 
								MAX_PATH,
								&wfd, 
								SLGP_UNCPRIORITY);

				outFile.ReleaseBuffer();
            }
            ppf->Release();
        }
        psl->Release();
    }

	inFile.ReleaseBuffer();

	// if this fails, outFile == ""
    return outFile;
}
*/

#pragma warning (disable : 4018)	// '<':  signed/unsigned mismatch
#pragma warning (disable : 4100)	// unreferenced formal parameter
#pragma warning (disable : 4127)	// conditional expression is constant
#pragma warning (disable : 4244)	// conv from X to Y, possible loss of data
#pragma warning (disable : 4310)	// cast truncates constant value
#pragma warning (disable : 4505)	// X: unreference local function removed
#pragma warning (disable : 4510)	// X: default ctor could not be generated
#pragma warning (disable : 4511)	// X: copy constructor could not be generated
#pragma warning (disable : 4512)	// assignment operator could not be generated
#pragma warning (disable : 4514)	// debug symbol exceeds 255 chars
#pragma warning (disable : 4610)	// union X can never be instantiated
#pragma warning (disable : 4663)	// to explicitly spec class template X use ...
#pragma warning (disable : 4710)	// function 'XXX' not expanded
#pragma	warning	(disable : 4786)	// X: identifier truncated to '255' chars


void CFocusEditCtrl2::OnFinalRelease()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CEdit::OnFinalRelease();
}

void CFocusEditCtrl2::PreSubclassWindow()
{
	CEdit::PreSubclassWindow();
	ModifyStyle(0, WS_BORDER);
	ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE , 0);
}

void CFocusEditCtrl2::OnPaint()
{
	DWORD dwStyle = GetStyle();
	CRect rc; 
	CPaintDC dc( this );
	CString strText = "";
	CString strTemp = "";

	GetWindowText(strText);
	long nCount = GetLineCount();

	if(nCount > 1) 
	{
		long nVisible = GetFirstVisibleLine(); 
		strText = "";
		for(int i=0; i<nCount; i++)
		{ 
			long nLen = LineLength(LineIndex(i)) * 2;
			GetLine(i, strTemp.GetBuffer(nLen), nLen);
			strTemp.ReleaseBuffer(nLen);

			if(nVisible <= i)
			{
				strText += strTemp;
				strText += "\r\n";
			}
		}
	}

	if(m_bInitFont == FALSE)
	{
		SetFont(m_FontManager.GetFont(m_strFaceName, m_nHeight, m_nWeight));
		m_bInitFont = TRUE;
	}

	if( strText.IsEmpty() && this != GetFocus())
	{
		// Clearing the background
		//dc.FillSolidRect( rect, RGB(125,125,125));
		GetClientRect(rc);
		rc.InflateRect(1, 1, 1, 1);

		//CFont *pFont = GetFont();
		CFont* pOldFont = dc.SelectObject(m_FontManager.GetFont(m_strFaceName, m_nHeight, m_nWeight));
		dc.SetBkMode(TRANSPARENT);

		if(m_bGradientBK)
			LF->FillGradient(&dc, m_clrBk, rc, 20);
		else
			dc.FillSolidRect(rc, m_clrBk);

		dc.SetTextColor(m_clrTextNoFocus);
		dc.SetBkColor(m_clrBk);
		dc.DrawText(m_strTitle,rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
		dc.SelectObject(pOldFont);
	}
	else
	{
		CRect rcClient;
		GetRect(rc);
		GetClientRect(rcClient);
		rcClient.InflateRect(1, 1, 1, 1);

		CFont* SelectObject = dc.SelectObject(m_FontManager.GetFont(m_strFaceName, m_nHeight, m_nWeight));
		dc.SetBkMode(TRANSPARENT);

		COLORREF crBack = (this == GetFocus()) ? g_crABColor : m_clrBk;
		COLORREF crText = (this == GetFocus()) ? RGB(0, 0, 0) : m_clrText;

		if(m_bGradientBK)
			LF->FillGradient(&dc, crBack, rcClient, 20);
		else
			dc.FillSolidRect(rcClient, crBack);

		if(m_bMustClrText) crText = m_clrText;
		if(m_bMustClrBack) crBack = m_clrBk;

		dc.SetTextColor(this != GetFocus() && m_bUseNoFocusHasTextColor ? m_clrTextNoFocusHasText : crText);
		dc.SetBkColor(crBack);

		if(dwStyle & ES_PASSWORD)
		{
			for(int i = 0; i < strText.GetLength(); i++)
				strText.SetAt(i, '*');
		}

		if(m_bCenter)
			dc.DrawText(strText,rc, DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_NOPREFIX);
		else
		{
			if((dwStyle & ES_NUMBER) || (dwStyle & ES_RIGHT))
				dc.DrawText(strText,rc, DT_RIGHT | DT_WORDBREAK | DT_NOPREFIX);
			else
				dc.DrawText(strText,rc, DT_LEFT | DT_WORDBREAK | DT_NOPREFIX);
		}

		dc.SelectObject(SelectObject);
	}
}

void CFocusEditCtrl2::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	Invalidate(FALSE);
	//g_bana_log->Print("OnKillFocus\n");	

}

void CFocusEditCtrl2::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	Invalidate(FALSE);
	//g_bana_log->Print("OnSetFocus\n");	

}


void CFocusEditCtrl2::SetFontSize(int nSize)
{
	m_nHeight = nSize;
	SetFont(m_FontManager.GetFont(m_strFaceName, m_nHeight, m_nWeight));
	m_bInitFont = TRUE;
}

void CFocusEditCtrl2::SetMyFont(CString strFaceName, int nHeight, int nWeight)
{
	m_strFaceName = strFaceName;
	m_nHeight = nHeight;
	m_nWeight = nWeight;
	SetFont(m_FontManager.GetFont(m_strFaceName, m_nHeight, m_nWeight));
	m_bInitFont = TRUE;
}

void CFocusEditCtrl2::SetGradientBK(BOOL bGradientBK, long nGradientScale, BOOL bRedraw)
{
	m_bGradientBK = bGradientBK;
	m_nGradientScale = nGradientScale;
	if(bRedraw) 
		Invalidate(FALSE);
}
