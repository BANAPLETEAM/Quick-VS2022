// QuickView.cpp : CQuickView Ŭ������ ����
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

// CQuickView ����/�Ҹ�

CQuickView::CQuickView()
	: CFormView(CQuickView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CQuickView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}


// CQuickView ����

#ifdef _DEBUG
void CQuickView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQuickView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQuickDoc* CQuickView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQuickDoc)));
	return (CQuickDoc*)m_pDocument;
}
#endif //_DEBUG


void CQuickView::OnBnClickedBtnLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
