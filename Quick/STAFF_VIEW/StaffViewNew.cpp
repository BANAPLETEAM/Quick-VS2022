// StaffView.cpp : 구현 파일입니다.
//


#include "stdafx.h"
#include "resource.h"
#include "StaffViewNew.h"
#include "StaffPage7.h"
#include "StaffPage2.h"
#include "StaffPage4.h"
#include "StaffPage10.h"
#include "StaffPage11.h"
//#include "StaffPage12.h"
#include "StaffForm13.h"
#include "StaffForm14.h"
#include "StaffPage15.h"
#include "StaffPage16.h"
#include "StaffPage17.h"
#include "StaffPage18.h"
#include "StaffPage19.h"
#include "StaffPage20.h"
#include "StaffPage21.h"
#include "TakerPage3.h"
#include "StaffForm27.h"


#include "NotHasPowerForm.h"
//#include "XTPTabControl.h"




IMPLEMENT_DYNCREATE(CStaffViewNew, CView)

CStaffViewNew::CStaffViewNew()
{
	//m_pSheet = NULL;
}

CStaffViewNew::~CStaffViewNew()
{
	//delete m_pSheet;
}

BEGIN_MESSAGE_MAP(CStaffViewNew, CView)

	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CStaffViewNew 진단입니다.

#ifdef _DEBUG
void CStaffViewNew::AssertValid() const
{
	CView::AssertValid();
}

void CStaffViewNew::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

void CStaffViewNew::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}

// CStaffViewNew 메시지 처리기입니다.

void CStaffViewNew::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}


void CStaffViewNew::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

int CStaffViewNew::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(LF->POWER_CHECK(5010, "기사관리"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffForm14), _T("기사관리"), 0,CStaffForm14::IDD);
	//	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage12), _T("기사관리"), 0,CStaffPage12::IDD);
	}
	if(LF->POWER_CHECK(5020, "내직원관리"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage11), _T("내직원관리"), 0,CStaffPage11::IDD);
	if(LF->POWER_CHECK(5030, "기사관리"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage13), _T("기사관리(일부만적용됨)"), 0,CStaffPage13::IDD);
	if(LF->POWER_CHECK(5040, "기사세부사항"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage7), _T("기사세부사항(일부만적용됨)"), 0,CStaffPage7::IDD);
	if(LF->POWER_CHECK(5050, "서비스이용료"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage19), _T("서비스이용료(배차일수)"), 0,CStaffPage19::IDD);
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage2), _T("서비스이용료(단말로그인)"), 0,CStaffPage2::IDD);
	}
	if(LF->POWER_CHECK(5060, "출근관리"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage4), _T("기사배차일"), 0,CStaffPage4::IDD);
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage17), _T("단말기로그인"), 0,CStaffPage17::IDD);
	}
	if(LF->POWER_CHECK(5070, "공유콜배차제한"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage10), _T("공유콜배차제한"), 0,CStaffPage10::IDD);
	if(LF->POWER_CHECK(5070, "공유콜배차제한(즉시공유)"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage15), _T("공유콜배차제한(즉시공유)"), 0,CStaffPage15::IDD);
	if(LF->POWER_CHECK(5090, "공유콜배차해제로그"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage16), _T("공유콜배차해제로그"), 0,CStaffPage16::IDD);
	if(LF->POWER_CHECK(5100, "삭제기사"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage18), _T("삭제기사"), 0,CStaffPage18::IDD);
	if(LF->POWER_CHECK(5200, "직원출퇴근"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage20), _T("직원출퇴근"), 0,CStaffPage20::IDD);
	if(LF->POWER_CHECK(5300, "배차그룹설정"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage21), _T("배차그룹설정"), 0,CStaffPage21::IDD);
	//if(LF->POWER_CHECK(5400, "발신자등록"))													// 4050 -> 4090
	//	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage22), _T("발신번호등록"), 0,CStaffPage22::IDD);
	if(LF->POWER_CHECK(5400, "발신자등록"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CTakerPage3), _T("발신번호등록"), 0,CTakerPage3::IDD);

	if(LF->POWER_CHECK(5500, "고용보험신고정보"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffForm27), _T("고용보험신고정보"), 0,CStaffForm27::IDD);


	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("볼수 있는 권한이 있는 페이지가 존재하지 않습니다."), 0,CNotHasPowerForm::IDD);

	return 0;
}

LONG CStaffViewNew::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != LF->GetCurBranchInfo())
	{
		pView->RefreshList();
	}

	return 0;
}


void CStaffViewNew::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->FirstRefresh();
}

int CStaffViewNew::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


