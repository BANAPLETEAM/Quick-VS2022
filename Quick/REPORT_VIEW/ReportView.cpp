// ReportView.cpp : ���� �����Դϴ�.
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


// CReportView �׸����Դϴ�.

void CReportView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CReportView �����Դϴ�.

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


// CReportView �޽��� ó�����Դϴ�.

int CReportView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(POWER_CHECK(3010, "������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm1), _T("������"), 0,CReportForm1::IDD);
	if(POWER_CHECK(3020, "��ü�ſ�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm10), _T("��ü�ſ�����"), 0,CReportForm10::IDD);
	if(POWER_CHECK(3030, "�׷�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm24), _T("�׷�����"), 0,CReportForm24::IDD);
	
	if(POWER_CHECK(3040, "�׷�ܿ���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm21), _T("�׷�ܿ���"), 0,CReportForm21::IDD);

	if(POWER_CHECK(3040, "�׷��������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm51), _T("�׷��������"), 0,CReportForm51::IDD);
	if(POWER_CHECK(3040, "�׷��������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm52), _T("���긮��Ʈ"), 0,CReportForm52::IDD);

	if(POWER_CHECK(3050, "�׷�Ǽ�"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm23), _T("�׷�Ǽ�"), 0,CReportForm23::IDD);
	if(POWER_CHECK(3060, "���ϸ���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm19), _T("���ϸ���"), 0,CReportForm19::IDD);
	if(POWER_CHECK(3070, "�ſ�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm27), _T("�ſ�����"), 0,CReportForm27::IDD);
	if(POWER_CHECK(3080, "Ź������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm28), _T("Ź������"), 0,CReportForm28::IDD);
	if(POWER_CHECK(3100, "ī���������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm31), _T("ī���������"), 0,CReportForm31::IDD);
	if(POWER_CHECK(3110, "���ݿ�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm34), _T("���ݿ�����"), 0,CReportForm34::IDD);
	if(POWER_CHECK(3120, "���ϸ�����ݰ���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm35), _T("���ϸ�����ݰ���"), 0,CReportForm35::IDD);
	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("���� �ִ� ������ �ִ� �������� �������� �ʽ��ϴ�."), 0,CNotHasPowerForm::IDD);

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
