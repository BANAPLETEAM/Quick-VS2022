#pragma once


#include "atlImage.h"

class CMmsImageView : public CScrollView
{
	DECLARE_DYNCREATE(CMmsImageView)

protected:
	CMmsImageView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMmsImageView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	CImage m_imgMms[MAX_MMS_IMAGE_COUNT];
	CString m_strImage[MAX_MMS_IMAGE_COUNT];

	long nZoom;
	long m_nImageCount;

	long m_nCurShowImage;

	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnInitialUpdate();
	void SetCurNumber(long nNumber);
	long GetCurNumber() {return m_nCurShowImage;}

	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


