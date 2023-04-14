// MyTitleStatic.cpp : ���� �����Դϴ�.
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



// CMyTitleStatic �޽��� ó�����Դϴ�.



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
		CFont *pOld = dc.SelectObject(m_FontManager.GetFont("����", 30, FW_NORMAL));
		dc.SetTextColor(RGB(32, 165, 170));
		dc.DrawText("�� ���� ����", r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		dc.SelectObject(pOld);
	}
	else
	{ 
		CFont *pOld = dc.SelectObject(m_FontManager.GetFont("����", 13, FW_NORMAL));
		dc.SetTextColor(RGB(0, 0, 0));
		long nHeight = r.Height();

		CRect r1 = r;

		r1.bottom = r1.top + (nHeight / 2);
		r1.left += 5;
		dc.DrawText("�ֹ� : " + GetStringFromLong(m_nTodaycount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		r1.left += 100;
		dc.DrawText("���ϸ��� : " + GetStringFromLong(m_nMileageBalance), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

		r1 = r;
		r1.left += 5;

		r1.top = r1.top + (nHeight / 2);
		dc.DrawText("�Ϸ� : " + GetStringFromLong(m_nUseCount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		r1.left += 100;
		dc.DrawText("��� : " + GetStringFromLong(m_nCancelCount), r1, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		dc.SelectObject(pOld);

	}
}
