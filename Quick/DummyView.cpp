// DummyView.cpp : ���� �����Դϴ�.
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


// CDummyView �׸����Դϴ�.

void CDummyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CDummyView �����Դϴ�.

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


// CDummyView �޽��� ó�����Դϴ�.
