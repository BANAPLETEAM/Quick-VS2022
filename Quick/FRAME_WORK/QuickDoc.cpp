// QuickDoc.cpp : CQuickDoc Ŭ������ ����
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


// CQuickDoc ����/�Ҹ�

CQuickDoc::CQuickDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
//	m_Pay.Open();
}

CQuickDoc::~CQuickDoc()
{
}

BOOL CQuickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ �ٽ� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}

// CQuickDoc serialization

void CQuickDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CQuickDoc ����

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


// CQuickDoc ���

