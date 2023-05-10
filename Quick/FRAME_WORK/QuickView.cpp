// QuickView.cpp : CQuickView 클래스의 구현
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"

#include "QuickDoc.h"
#include "QuickView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQuickView

IMPLEMENT_DYNCREATE(CQuickView, CFormView)

BEGIN_MESSAGE_MAP(CQuickView, CFormView)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CQuickView::OnBnClickedBtnLogin)
END_MESSAGE_MAP()

// CQuickView 생성/소멸

CQuickView::CQuickView()
	: CFormView(CQuickView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CQuickView::~CQuickView()
{
}

void CQuickView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CQuickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	// Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CQuickView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}


// CQuickView 진단

#ifdef _DEBUG
void CQuickView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQuickView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQuickDoc* CQuickView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQuickDoc)));
	return (CQuickDoc*)m_pDocument;
}
#endif //_DEBUG


void CQuickView::OnBnClickedBtnLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
