// DummyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DummyView.h"


// CDummyView

IMPLEMENT_DYNCREATE(CDummyView, CView)

CDummyView::CDummyView()
{
}

CDummyView::~CDummyView()
{
}

BEGIN_MESSAGE_MAP(CDummyView, CView)
END_MESSAGE_MAP()


// CDummyView 그리기입니다.

void CDummyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CDummyView 진단입니다.

#ifdef _DEBUG
void CDummyView::AssertValid() const
{
	CView::AssertValid();
}

void CDummyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CDummyView 메시지 처리기입니다.
