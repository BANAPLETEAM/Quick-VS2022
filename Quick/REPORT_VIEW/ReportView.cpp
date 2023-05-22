// ReportView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportView.h"

#include "ReportForm1.h"
#include "ReportForm10.h"  
#include "ReportForm19.h"
#include "ReportForm21.h"
#include "ReportForm23.h"
#include "ReportForm24.h"
#include "ReportForm27.h"
#include "ReportForm28.h"
#include "ReportForm31.h"
#include "ReportForm34.h"
#include "ReportForm35.h"
#include "ReportForm51.h"
#include "ReportForm52.h"
#include "NotHasPowerForm.h"

// CReportView

IMPLEMENT_DYNCREATE(CReportView, CView)

CReportView::CReportView()
{
}

CReportView::~CReportView()
{
}

BEGIN_MESSAGE_MAP(CReportView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CReportView 그리기입니다.

void CReportView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CReportView 진단입니다.

#ifdef _DEBUG
void CReportView::AssertValid() const
{
	CView::AssertValid();
}

void CReportView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CReportView 메시지 처리기입니다.

int CReportView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(POWER_CHECK(3010, "고객정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm1), _T("고객정산"), 0,CReportForm1::IDD);
	if(POWER_CHECK(3020, "업체신용정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm10), _T("업체신용정산"), 0,CReportForm10::IDD);
	if(POWER_CHECK(3030, "그룹정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm24), _T("그룹정산"), 0,CReportForm24::IDD);
	
	if(POWER_CHECK(3040, "그룹외오더"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm21), _T("그룹외오더"), 0,CReportForm21::IDD);

	if(POWER_CHECK(3040, "그룹수동정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm51), _T("그룹수동정산"), 0,CReportForm51::IDD);
	if(POWER_CHECK(3040, "그룹수동정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm52), _T("정산리스트"), 0,CReportForm52::IDD);

	if(POWER_CHECK(3050, "그룹건수"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm23), _T("그룹건수"), 0,CReportForm23::IDD);
	if(POWER_CHECK(3060, "마일리지"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm19), _T("마일리지"), 0,CReportForm19::IDD);
	if(POWER_CHECK(3070, "신용정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm27), _T("신용정산"), 0,CReportForm27::IDD);
	if(POWER_CHECK(3080, "탁송정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm28), _T("탁송정산"), 0,CReportForm28::IDD);
	if(POWER_CHECK(3100, "카드결제내역"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm31), _T("카드결제내역"), 0,CReportForm31::IDD);
	if(POWER_CHECK(3110, "현금영수증"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm34), _T("현금영수증"), 0,CReportForm34::IDD);
	if(POWER_CHECK(3120, "마일리지출금관리"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm35), _T("마일리지출금관리"), 0,CReportForm35::IDD);
	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("볼수 있는 권한이 있는 페이지가 존재하지 않습니다."), 0,CNotHasPowerForm::IDD);

	return 0;
}

void CReportView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}


int CReportView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


LONG CReportView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != GetCurBranchInfo())
	{
		pView->RefreshList();
	}

	return 0;
}

void CReportView::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->FirstRefresh();
}
