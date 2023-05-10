// QuickDoc.cpp : CQuickDoc 클래스의 구현
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "QuickDoc.h"
#include "QuickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQuickDoc

IMPLEMENT_DYNCREATE(CQuickDoc, CDocument)

BEGIN_MESSAGE_MAP(CQuickDoc, CDocument)
END_MESSAGE_MAP()


// CQuickDoc 생성/소멸

CQuickDoc::CQuickDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
//	m_Pay.Open();
}

CQuickDoc::~CQuickDoc()
{
}

BOOL CQuickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 다시 초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

// CQuickDoc serialization

void CQuickDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CQuickDoc 진단

#ifdef _DEBUG
void CQuickDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQuickDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CQuickDoc 명령

