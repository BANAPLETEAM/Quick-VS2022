// MyMarkupStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "MyMarkupStatic.h"


// CMyMarkupStatic

//IMPLEMENT_DYNAMIC(CMyMarkupStatic, CMarkupStatic)

CMyMarkupStatic::CMyMarkupStatic()
{

}

CMyMarkupStatic::~CMyMarkupStatic()
{
}


BEGIN_MESSAGE_MAP(CMyMarkupStatic, CMarkupStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyMarkupStatic 메시지 처리기입니다.

 

void CMyMarkupStatic::OnPaint()
{ 
	//CMarkupStatic::OnPaint();
 
	CPaintDC dcPaint(this); 
//	CXTPBufferDC dcBuffer(dcPaint); 
	
	CRect rc; 
	GetClientRect(rc);
//	rc.left = rc.right - 40;
	rc.top = rc.bottom - 16;

	CFont *pOldFont = dcPaint.SelectObject(m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));

	dcPaint.SetBkMode(OPAQUE);
	dcPaint.SetBkColor(RGB(255, 255, 255));
	dcPaint.SetTextColor(RGB(0, 0, 255));
	dcPaint.DrawText(m_strFooterMsg, rc, DT_RIGHT);

	if(pOldFont) dcPaint.SelectObject(pOldFont);
}
