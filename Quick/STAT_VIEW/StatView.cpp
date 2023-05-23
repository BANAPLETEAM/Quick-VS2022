// IncomeView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatView.h"
#include "StatForm2.h"
#include "CustomerPage7.h"
#include "NotHasPowerForm.h"
#include "StatForm3.h"
#include "StatForm5.h"
#include "ReportForm11.h"
#include "ReportForm5.h"
#include "ReportForm12.h"
#include "ReportForm14.h"
#include "StatForm6.h"
#include "StatForm7.h"
#include "StatForm9.h"
#include "StatTelserverRouteLog.h"
#include "StatForm10.h"
#include "StatChildFormCustomerNew.h"


// CStatView

IMPLEMENT_DYNCREATE(CStatView, CView)

CStatView::CStatView()
{
}

CStatView::~CStatView()
{
}

BEGIN_MESSAGE_MAP(CStatView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
END_MESSAGE_MAP()


// CStatView 그리기입니다.

void CStatView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CStatView 진단입니다.

#ifdef _DEBUG
void CStatView::AssertValid() const
{
	CView::AssertValid();
}

void CStatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CStatView 메시지 처리기입니다.

int CStatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(LF->POWER_CHECK(8010, "금일콜수예측"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm2), _T("금일콜수예측"), 0,CStatForm2::IDD);
	if(LF->POWER_CHECK(8020, "동분석"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage7), _T("동분석"), 0, CCustomerPage7::IDD);
	if(LF->POWER_CHECK(8030, "접수자통계"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm3), _T("접수자통계"), 0,CStatForm3::IDD);
	if(LF->POWER_CHECK(8040, "접수자통계_콜수"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm5), _T("접수자통계_콜수"), 0,CStatForm5::IDD);
	if(LF->POWER_CHECK(8050, "일별건수"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm11), _T("일별건수"), 0,CReportForm11::IDD);
	if(LF->POWER_CHECK(8060, "지점간정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm5), _T("지점간정산"), 0,CReportForm5::IDD);
	if(LF->POWER_CHECK(8070, "SMS통계"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm12), _T("SMS통계보기"), 0,CReportForm12::IDD);
	if(LF->POWER_CHECK(8080, "공유콜"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm14), _T("공유콜"), 0,CReportForm14::IDD);
	if(LF->POWER_CHECK(8090, "접수유형비율"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm9), _T("접수유형비율"), 0,CStatForm9::IDD);
		//LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm7), _T("접수유형비율"), 0,CReportForm7::IDD);
	
	if(LF->POWER_CHECK(8100, "공유콜정산내역"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm6), _T("공유콜정산내역"), 0, CStatForm6::IDD);
	if(LF->POWER_CHECK(8110, "SMS정산"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm7), _T("SMS정산"), 0, CStatForm7::IDD);

	if(LF->POWER_CHECK(8131, "오픈API"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm10), _T("오픈API접수유형"), 0,CStatForm10::IDD);

	if(LF->POWER_CHECK(8200, "신규고객율"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatChildFormCustomerNew), _T("신규고객율"), 0,CStatChildFormCustomerNew::IDD);


	CBranchInfo *pBI;
	if (m_ba.GetCount() > 1)
		pBI = m_ba.GetAt(1);
	else
		pBI = m_ba.GetAt(0);

	BOOL bIPPBX = pBI->bIPPBXType;

	if(LF->POWER_CHECK(8120, "텔서버라우팅") && bIPPBX)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatTelserverRouteLog), _T("텔서버라우팅"), 0, CStatTelserverRouteLog::IDD);

	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("볼수 있는 권한이 있는 페이지가 존재하지 않습니다."), 0,CNotHasPowerForm::IDD);


	return 0;
}

void CStatView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}


int CStatView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

LONG CStatView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != LF->GetCurBranchInfo())
	{
		pView->FirstRefresh();
	}

	return 0;
}

void CStatView::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->FirstRefresh();
}