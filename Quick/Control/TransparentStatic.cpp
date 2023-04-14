// MyStatic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TransparentStatic.h"


// CTransparentStatic

IMPLEMENT_DYNAMIC(CTransparentStatic, CStatic)

CTransparentStatic::CTransparentStatic()
{
	m_nID = 0;
	m_clrTransparent = RGB(255, 255, 255);
}

CTransparentStatic::~CTransparentStatic()
{
}


BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CTransparentStatic::OnPaint()
{
	if(m_nID <= 0)
		return;

	CPaintDC dc(this);  // �׸��� �׸� DC ����.

	BITMAP bmpInfo; 
	CDC MemDC; 
	MemDC.CreateCompatibleDC(&dc); 

	CBitmap bmp; 
	CBitmap *pOldbmp; 

	bmp.LoadBitmap(m_nID); 

	bmp.GetBitmap(&bmpInfo); 

	pOldbmp=MemDC.SelectObject(&bmp); 

	/*
	for (int i=0;i<50;i++) 
	{ 
		for (int k=0;k<10;k++) 
		{ 
			dc.TextOutW(10+k*40,10+i*20,_T("$     ")); 
		} 

	} 
	*/
	//���� Ȯ���� ���� Text 
	//dc.StretchBlt(10,10,bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
	//	0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY); 

	//�׸� ���� ũ�� 


	//dc.TransparentBlt(10,160,bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
	//	0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(0,0,0)); 

	//������(RGB(0,0,0))�� �����ϰ� ó�� 


	dc.TransparentBlt(0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
		0,0,bmpInfo.bmWidth,bmpInfo.bmHeight, m_clrTransparent); 

	//�Ķ���(RGB(0,0,255))�� �����ϰ� ó�� 






}
