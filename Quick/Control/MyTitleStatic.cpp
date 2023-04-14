// MyTitleStatic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "MyTitleStatic.h"


// CMyTitleStatic

IMPLEMENT_DYNAMIC(CMyTitleStatic, CStatic)

CMyTitleStatic::CMyTitleStatic()
{
	m_nTodaycount = 0;
	m_nCNo = 0;
	m_nUseCount = 0;
	m_nCancelCount = 0;
	m_nMileageBalance = 0;
}

CMyTitleStatic::~CMyTitleStatic()
{
}


BEGIN_MESSAGE_MAP(CMyTitleStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyTitleStatic 메시지 처리기입니다.



void CMyTitleStatic::OnPaint()
{
	CPaintDC dc(this); 

	CBrush colorbrush, blackbrush;
	CRgn rgn, rgn2;
	CRect r;
	GetClientRect(r);

	dc.FillSolidRect(r, RGB(0xF0, 0xF0, 0xF0));

	dc.SetBkMode(TRANSPARENT);


	if(m_nCNo == 0) 
	{ 
		CFont *pOld = dc.SelectObject(m_FontManager.GetFont("돋움", 30, FW_NORMAL));
		dc.SetTextColor(RGB(32, 165, 170));
		dc.DrawText("고객 정보 없음", r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		dc.SelectObject(pOld);
	}
	else
	{ 
		CFont *pOld = dc.SelectObject(m_FontManager.GetFont("돋움", 13, FW_NORMAL));
		dc.SetTextColor(RGB(0, 0, 0));
		long nHeight = r.Height();

		CRect r1 = r;

		r1.bottom = r1.top + (nHeight / 2);
		r1.left += 5;
		dc.DrawText("주문 : " + GetStringFromLong(m_nTodaycount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		r1.left += 100;
		dc.DrawText("마일리지 : " + GetStringFromLong(m_nMileageBalance), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

		r1 = r;
		r1.left += 5;

		r1.top = r1.top + (nHeight / 2);
		dc.DrawText("완료 : " + GetStringFromLong(m_nUseCount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		r1.left += 100;
		dc.DrawText("취소 : " + GetStringFromLong(m_nCancelCount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		dc.SelectObject(pOld);

	}
}
