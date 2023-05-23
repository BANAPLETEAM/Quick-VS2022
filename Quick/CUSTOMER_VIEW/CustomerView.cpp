// FormMember.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerView.h"
#include "MainFrm.h"
#include "RcpDlg.h"
#include "CustomerPage1.h"
#include "CustomerPage2.h"
#include "CustomerPage3.h"
#include "CustomerPage4.h" 
#include "CustomerPage5.h"
#include "CustomerPage11.h"
#include "CustomerPage12.h"
#include "CustomerPage13.h"
#include "CustomerPage14.h"
#include "CustomerPage15.h"
#include "CustomerPage16.h"
#include "CustomerPage17.h"
#include "CustomerPage18.h"
#include "NotHasPowerForm.h"

// CCustomerView




IMPLEMENT_DYNCREATE(CCustomerView, CView)

CCustomerView::CCustomerView()
{
}

CCustomerView::~CCustomerView()
{
}

void CCustomerView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomerView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CCustomerView 진단입니다.

#ifdef _DEBUG
void CCustomerView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

void CCustomerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}


// CCustomerView 메시지 처리기입니다.
void CCustomerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CCustomerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

int CCustomerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);
	 
	if(LF->POWER_CHECK(6010, "고객관리"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage1), _T("고객관리"), 0, CCustomerPage1::IDD);
	if(LF->POWER_CHECK(6020, "우수고객조회"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage2), _T("우수고객조회"), 0, CCustomerPage2::IDD);
	if(LF->POWER_CHECK(6030, "신규고객조회"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage3), _T("신규고객조회"), 0, CCustomerPage3::IDD);
	if(LF->POWER_CHECK(6040, "불량고객조회"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage4), _T("불량고객조회"), 0, CCustomerPage4::IDD);
	if(LF->POWER_CHECK(6045, "불량고객조회2"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage17), _T("불량고객조회2"), 0, CCustomerPage17::IDD);
	if(LF->POWER_CHECK(6050, "이용증감고객"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage5), _T("이용증감고객"), 0, CCustomerPage5::IDD);
	if(LF->POWER_CHECK(6060, "그룹관리"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage11), _T("그룹관리"), 0, CCustomerPage11::IDD);
 	if(LF->POWER_CHECK(6070, "삭제고객"))
 		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage12), _T("삭제고객"), 0, CCustomerPage12::IDD);
	if(LF->POWER_CHECK(6080, "보장고객"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage13), _T("보장고객"), 0, CCustomerPage13::IDD);
	if(LF->POWER_CHECK(6090, "휴면고객"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage14), _T("휴면고객"), 0, CCustomerPage14::IDD);
	if(LF->POWER_CHECK(6100, "중복고객"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage15), _T("중복고객"), 0, CCustomerPage15::IDD);
	if(LF->POWER_CHECK(6110, "기간별조회"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage16), _T("기간별조회"), 0, CCustomerPage16::IDD);
	if(LF->POWER_CHECK(6120, "차단번호"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage18), _T("차단번호"), 0, CCustomerPage18::IDD);
  
	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("볼수 있는 권한이 있는 페이지가 존재하지 않습니다."), 0,CNotHasPowerForm::IDD);
		
	return 0;
}

LONG CCustomerView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != LF->GetCurBranchInfo())
	{
		pView->RefreshList();
	}

	return 0;
}

void CCustomerView::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	//pView->FirstRefresh();
}

int CCustomerView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
