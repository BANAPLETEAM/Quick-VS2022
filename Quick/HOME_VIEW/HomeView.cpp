// IncomeView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "HomeView.h"
#include "HomeForm1.h"
#include "FAQHtmlView.h"
// CHomeView

IMPLEMENT_DYNCREATE(CHomeView, CView)

CHomeView::CHomeView()
{
}

CHomeView::~CHomeView()
{
}

BEGIN_MESSAGE_MAP(CHomeView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
END_MESSAGE_MAP()


// CHomeView 그리기입니다.

void CHomeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CHomeView 진단입니다.

#ifdef _DEBUG
void CHomeView::AssertValid() const
{
	CView::AssertValid();
}

void CHomeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CHomeView 메시지 처리기입니다.

int CHomeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(m_ci.IsThisCompany("적재물보험"))
		return 0;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CHomeForm1), _T("게시판"), 0,CHomeForm1::IDD, 0);
	//LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CHomeForm3), _T("업데이트 요청"), 0,CHomeForm3::IDD, 0);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_home_view_page");
	pCmd.AddParameter(0);			
	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{			
			int nPageOffset = i+1;
			CString strTitle, strURL;

			pRs.GetFieldValue("sTitle", strTitle);
			pRs.GetFieldValue("sURL", strURL);

			LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CFAQHtmlView), strTitle, 0, 0xFF00 + i, 0);
			CFAQHtmlView *pView = (CFAQHtmlView*)CWnd::FromHandle(m_wndTabControl.GetItem(nPageOffset)->GetHandle());
			pView->m_strURL = strURL;

			pRs.MoveNext();
		}
	}

	/*
	BOOL bHomeFormIsMainPage = AfxGetApp()->GetProfileInt("HomeForm", "MainPage", 0);

	if(bHomeFormIsMainPage)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CHomeForm1), _T("게시판"), 0,CHomeForm1::IDD, 0);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_home_view_page");
	pCmd.AddParameter(0);			
	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{			
			int nPageOffset = (bHomeFormIsMainPage ? 1 : 0) + i;
			CString strTitle, strURL;

			pRs.GetFieldValue("sTitle", strTitle);
			pRs.GetFieldValue("sURL", strURL);

			LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CFAQHtmlView), strTitle, 0, 0xFF00 + i, 0);
			CFAQHtmlView *pView = (CFAQHtmlView*)CWnd::FromHandle(m_wndTabControl.GetItem(nPageOffset)->GetHandle());
			pView->m_strURL = strURL;

			pRs.MoveNext();
		}
	}

	if(!bHomeFormIsMainPage)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CHomeForm1), _T("게시판"), 0,CHomeForm1::IDD, 0);

	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CHomeForm3), _T("업데이트 요청"), 0,CHomeForm3::IDD, 0);

	*/
	return 0;
}

void CHomeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(m_wndTabControl.GetSafeHwnd())
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
}


int CHomeView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

LONG CHomeView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != GetCurBranchInfo())
	{
		pView->FirstRefresh();
	}

	return 0;
}

void CHomeView::FirstRefresh()
{
	/*
	if(m_wndTabControl.GetSafeHwnd())
	{
		CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
		if(pItem)
		{
			CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
			pView->RefreshList();
		}
	}
	*/
}