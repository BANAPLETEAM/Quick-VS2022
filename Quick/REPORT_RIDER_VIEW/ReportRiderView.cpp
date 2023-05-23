// ReportView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportRiderView.h"
#include "ReportForm2.h"
#include "ReportForm4.h"
#include "ReportForm8.h"
#include "ReportForm13.h"
#include "ReportForm20.h"
#include "ReportForm25.h"
#include "ReportForm26.h"
#include "ReportForm29.h"
#include "ReportForm32.h"
#include "ReportForm33.h"


#include "NotHasPowerForm.h"
//#include "XTPTabControl.h"

// CReportRiderView

IMPLEMENT_DYNCREATE(CReportRiderView, CView)

CReportRiderView::CReportRiderView()
{
}

CReportRiderView::~CReportRiderView()
{
}

BEGIN_MESSAGE_MAP(CReportRiderView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CReportRiderView 그리기입니다.

void CReportRiderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CReportRiderView 진단입니다.

#ifdef _DEBUG
void CReportRiderView::AssertValid() const
{
	CView::AssertValid();
}

void CReportRiderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CReportRiderView 메시지 처리기입니다.

int CReportRiderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(LF->POWER_CHECK(4010, "기사정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm2), _T("기사정산"), 0,CReportForm2::IDD);
	if(LF->POWER_CHECK(4020, "기사별건수"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm4), _T("기사별건수"), 0,CReportForm4::IDD);
	}
	if(LF->POWER_CHECK(4030, "기사신용정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm13), _T("기사신용정산"), 0,CReportForm13::IDD);
	if(LF->POWER_CHECK(4040, "기사마일리지"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm20), _T("기사마일리지"), 0,CReportForm20::IDD);
	if(LF->POWER_CHECK(4050, "쿠폰정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm8), _T("쿠폰정산"), 0,CReportForm8::IDD);
	if(LF->POWER_CHECK(4060, "기사별건수(지입금)"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm25), _T("기사별건수(지입금)"), 0,CReportForm25::IDD);
	if(LF->POWER_CHECK(4070, "영업팀정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm26), _T("영업팀정산"), 0,CReportForm26::IDD);
	if(LF->POWER_CHECK(4080, "기사온라인출금"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm29), _T("기사온라인출금"), 0,CReportForm29::IDD);

	if(LF->POWER_CHECK(4090, "기사출금요청") && (LF->IsThisCompany("퀵콜") || LF->IsThisCompany("로지")))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm32), _T("기사출금요청"), 0,CReportForm32::IDD);
	if(LF->POWER_CHECK(4100, "단말기이력관리") && (LF->IsThisCompany("퀵콜") || LF->IsThisCompany("로지")))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm33), _T("단말기이력관리"), 0,CReportForm33::IDD);

	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("볼수 있는 권한이 있는 페이지가 존재하지 않습니다."), 0,CNotHasPowerForm::IDD);


	return 0;
}

void CReportRiderView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}


int CReportRiderView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


LONG CReportRiderView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != LF->GetCurBranchInfo())
	{
		pView->RefreshList();
	}

	return 0;
}

void CReportRiderView::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->FirstRefresh();
}

