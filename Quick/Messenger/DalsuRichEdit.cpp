// DalsuRichEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "ExRichEdit.h"
#include "DalsuRichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDalsuRichEdit

CDalsuRichEdit::CDalsuRichEdit()
{
	nPreScrollLine = 0;
}

CDalsuRichEdit::~CDalsuRichEdit()
{
}


BEGIN_MESSAGE_MAP(CDalsuRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CDalsuRichEdit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDalsuRichEdit message handlers
int CDalsuRichEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CHARFORMAT cf;

	cf.cbSize = sizeof (CHARFORMAT);  
	cf.dwMask = CFM_FACE | CFM_SIZE; 
	//cf.dwEffects; 
	cf.yHeight = 180; 
	//cf.yOffset; 
	//cf.crTextColor=RGB(250,0,0); 
	//cf.bCharSet; 
	//cf.bPitchAndFamily; 
	sprintf(cf.szFaceName, "MS Sans Serif"); 
 
	SetDefaultCharFormat(cf); 
 
	return 0;
}


void CDalsuRichEdit::AddText(LPCTSTR szTextIn, COLORREF crNewColor)
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_STARTINDENT | PFM_RIGHTINDENT;
	pf.dxStartIndent = 200;
	pf.dxRightIndent = 100;

	//int iTotalTextLength = GetWindowTextLength();
	int iTotalTextLength = GetTextLengthEx(GTL_DEFAULT,CP_ACP); 
	SetSel(iTotalTextLength, iTotalTextLength);
	SetParaFormat(pf);
	ReplaceSel(szTextIn);
	pf.dxStartIndent = 0;
	pf.dxRightIndent = 0;
	SetParaFormat(pf);

	int iStartPos = iTotalTextLength;

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	=(unsigned long) ~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor	= crNewColor;//RGB(0, 0, 0);

	int iEndPos = GetWindowTextLength();
	SetSel(iStartPos, iEndPos);
	SetSelectionCharFormat(cf);
	HideSelection(TRUE, FALSE);	

	LineScroll(GetLineCount() - nPreScrollLine);
	nPreScrollLine = GetLineCount();
}

void CDalsuRichEdit::AddText(CString &strTextIn, COLORREF crNewColor)
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_STARTINDENT | PFM_RIGHTINDENT;
	pf.dxStartIndent = 200;
	pf.dxRightIndent = 100;

	//int iTotalTextLength = GetWindowTextLength();
	int iTotalTextLength = GetTextLengthEx(GTL_DEFAULT,CP_ACP); 
	SetSel(iTotalTextLength, iTotalTextLength);
	SetParaFormat(pf);
	ReplaceSel((LPCTSTR)strTextIn);
	pf.dxStartIndent = 0;
	pf.dxRightIndent = 0;
	SetParaFormat(pf);

	int iStartPos = iTotalTextLength;

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	= (unsigned long)~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor	= crNewColor;//RGB(0, 0, 0);
//	SetSelectionCharFormat(cf);

	int iEndPos = GetWindowTextLength();
	SetSel(iStartPos, iEndPos);
	SetSelectionCharFormat(cf);
	HideSelection(TRUE, FALSE);

	LineScroll(GetLineCount() - nPreScrollLine);
	nPreScrollLine = GetLineCount();
}

// Example : Total 20 char, Name 16char +  " : "
void CDalsuRichEdit::AddName(CString &strName, COLORREF crNewColor)
{
	// Write the strName on the DalRichEdit
	//int iTotalTextLength = GetWindowTextLength();
	int iTotalTextLength = GetTextLengthEx(GTL_DEFAULT,CP_ACP); 
	SetSel(iTotalTextLength, iTotalTextLength);
	ReplaceSel((LPCTSTR)strName);
	int iStartPos = iTotalTextLength;

	// Formating the string that will be changed
	CHARFORMAT cf;
	cf.cbSize		= sizeof (CHARFORMAT);  
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	= (unsigned long)~(CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor	= crNewColor;//RGB(0, 0, 255); 
// 	SetSelectionCharFormat(cf); 
 
	// The last iTotalTextLength is The iStartPos
	// After Replace the strName, ReCall GetWindowTextLength() and the return value
	// is iEndPos...
	int iEndPos = GetWindowTextLength();
	SetSel(iStartPos, iEndPos);
	TRACE(_T("=====Start:%d, End:%d\n"), iStartPos, iEndPos);
 	SetSelectionCharFormat(cf); 
	HideSelection(TRUE, FALSE);

	LineScroll(GetLineCount() - nPreScrollLine);
	nPreScrollLine = GetLineCount();
}

void CDalsuRichEdit::AddMsg(CString &strMsg, COLORREF crNewColor, 
							BOOL bUnderLine, 
							BOOL bBold)
{
	//int iTotalLength = GetWindowTextLength();
	int iTotalLength = GetTextLengthEx(GTL_DEFAULT,CP_ACP); 
	SetSel(iTotalLength, iTotalLength);
	ReplaceSel((LPCTSTR)strMsg);
	int iStartPos = iTotalLength;
	int iEndPos = GetWindowTextLength();

	CHARFORMAT cf;

	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_BOLD | CFM_UNDERLINE;
	cf.dwEffects = (unsigned long)~(CFE_UNDERLINE | CFE_BOLD | CFE_AUTOCOLOR);
	cf.crTextColor = crNewColor;
	cf.dwEffects |= bUnderLine ? CFE_UNDERLINE : cf.dwEffects ;
	cf.dwEffects |= bBold ? CFE_BOLD : cf.dwEffects;

	SetSel(iStartPos, iEndPos);
		TRACE(_T("AddMsg=====Start:%d, End:%d, crNewColor:%ld\n"), iStartPos, iEndPos, cf.crTextColor);
	SetSelectionCharFormat(cf);
	HideSelection(TRUE, FALSE);

	LineScroll(GetLineCount() - nPreScrollLine);
	nPreScrollLine = GetLineCount();
}

