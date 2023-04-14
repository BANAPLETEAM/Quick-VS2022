// QuickView.h : iCQuickView 클래스의 인터페이스
//


#pragma once
#include "afxwin.h"


class CQuickView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	DECLARE_DYNCREATE(CQuickView)

public:
	CQuickView();
	enum{ IDD = IDD_QUICK_FORM };

// 특성
public:
	CQuickDoc* GetDocument() const;

// 작업
public:

// 재정의
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현
public:
	virtual ~CQuickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 메시지 맵 함수를 생성했습니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
};

#ifndef _DEBUG  // QuickView.cpp의 디버그 버전
inline CQuickDoc* CQuickView::GetDocument() const
   { return reinterpret_cast<CQuickDoc*>(m_pDocument); }
#endif

