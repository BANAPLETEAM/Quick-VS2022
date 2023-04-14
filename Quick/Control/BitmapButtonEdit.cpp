// BitmapButtonEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BitmapButtonEdit.h"


// CBitmapButtonEdit

IMPLEMENT_DYNAMIC(CBitmapButtonEdit, CEdit)

CBitmapButtonEdit::CBitmapButtonEdit()
{

}

CBitmapButtonEdit::~CBitmapButtonEdit()
{
}


BEGIN_MESSAGE_MAP(CBitmapButtonEdit, CEdit)
END_MESSAGE_MAP()


void CBitmapButtonEdit::MakeButton(CWnd *pMsgWnd, UINT nImage, long nMargin) 
{
	m_pMsgWnd = pMsgWnd;

	CRect rc;
	GetClientRect(rc);

	rc.left = rc.left + nMargin;
	rc.top = rc.top  + nMargin;

	m_btnImage.Create(NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, CRect(0, 0, 50, 50), this, 100);
	m_btnImage.LoadBitmaps(nImage);
	m_btnImage.SizeToContent();
	//m_btnImage.Create(NULL,WS_CHILD|WS_VISIBLE, CRect(0, 0, 50, 50), this, 100);
	m_btnImage.ShowWindow(TRUE);

//	m_imageBtn.SizeToContent();
}

void CBitmapButtonEdit::ChangeImage(UINT nImage)
{
	m_btnImage.LoadBitmaps(nImage);
	m_btnImage.SizeToContent();
}

void CBitmapButtonEdit::ShowButton(BOOL bShow)
{
	m_btnImage.ShowWindow(bShow);
}

// CBitmapButtonEdit 메시지 처리기입니다.


