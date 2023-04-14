// FlatEdit2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlatEdit2.h"


// CFlatEdit2

//IMPLEMENT_DYNAMIC(CFlatEdit2, CFocusEditCtrl2)
CFlatEdit2::CFlatEdit2()
{
}

CFlatEdit2::~CFlatEdit2()
{
}


BEGIN_MESSAGE_MAP(CFlatEdit2, CFocusEditCtrl2)
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CFlatEdit2 메시지 처리기입니다.


void CFlatEdit2::PreSubclassWindow()
{
	SetFontSize(15);
	CEdit::PreSubclassWindow();
}


BOOL CFlatEdit2::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID, 1, RGB(150, 150, 150)); 
	pOldPen = pDC->SelectObject(&pen);
	GetClientRect(rc);
	rc.InflateRect(1, 1, 1, 1);
	pDC->Rectangle(rc);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	return CEdit::OnEraseBkgnd(pDC);
}

void CFlatEdit2::SetWindowTextNoNotify(LPCTSTR lpszString)
{
	CString old;
	CEdit::GetWindowText(old);
	if(old == lpszString)
		return; // do nothing, already set
	//BOOL previous = notify;
	//notify = FALSE;
	CEdit::SetWindowText(lpszString);

	//notify = previous;

}

void CFlatEdit2::SetWindowText(LPCTSTR lpszString)
{
	CFocusEditCtrl2::SetWindowText(lpszString);
}

int CFlatEdit2::GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount)
{
	return CFocusEditCtrl2::GetWindowText(lpszStringBuf, nMaxCount);
}

void CFlatEdit2::GetWindowText(CString& rString)
{
	CFocusEditCtrl2::GetWindowText(rString);
}



/////////////////////////////////////////////////////////////////////////



//IMPLEMENT_DYNAMIC(CFlatMemoEdit2, CFocusEditCtrl2)
CFlatMemoEdit2::CFlatMemoEdit2()
{
}

CFlatMemoEdit2::~CFlatMemoEdit2()
{
}


BEGIN_MESSAGE_MAP(CFlatMemoEdit2, CFocusEditCtrl2)
	//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CFlatEdit2 메시지 처리기입니다.


void CFlatMemoEdit2::PreSubclassWindow()
{
	SetFontSize(12);
	//	ModifyStyle(WS_BORDER, 0);
	ModifyStyleEx(WS_EX_STATICEDGE | WS_EX_CLIENTEDGE, 0);
	CEdit::PreSubclassWindow();
}

BOOL CFlatMemoEdit2::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID, 1, RGB(150, 150, 150)); 
	pOldPen = pDC->SelectObject(&pen);
	GetClientRect(rc);
	rc.InflateRect(1, 1, 1, 1);
	pDC->Rectangle(rc);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	return CEdit::OnEraseBkgnd(pDC);
}

void CFlatMemoEdit2::SetWindowText(LPCTSTR lpszString)
{
	CFocusEditCtrl2::SetWindowText(lpszString);
}

int CFlatMemoEdit2::GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount)
{
	return CFocusEditCtrl2::GetWindowText(lpszStringBuf, nMaxCount);
}

void CFlatMemoEdit2::GetWindowText(CString& rString)
{
	CFocusEditCtrl2::GetWindowText(rString);
}


