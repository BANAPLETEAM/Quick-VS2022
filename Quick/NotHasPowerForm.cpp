// NotHasPowerForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "NotHasPowerForm.h"


// CNotHasPowerForm

IMPLEMENT_DYNCREATE(CNotHasPowerForm, CMyFormView)

CNotHasPowerForm::CNotHasPowerForm()
	: CMyFormView(CNotHasPowerForm::IDD)
{
}

CNotHasPowerForm::~CNotHasPowerForm()
{
}

void CNotHasPowerForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotHasPowerForm, CMyFormView)
END_MESSAGE_MAP()


// CNotHasPowerForm 진단입니다.

#ifdef _DEBUG
void CNotHasPowerForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CNotHasPowerForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CNotHasPowerForm 메시지 처리기입니다.
