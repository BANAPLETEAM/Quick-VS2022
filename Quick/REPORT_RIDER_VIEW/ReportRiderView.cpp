// ReportView.cpp : ���� �����Դϴ�.
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


// CReportRiderView �׸����Դϴ�.

void CReportRiderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CReportRiderView �����Դϴ�.

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


// CReportRiderView �޽��� ó�����Դϴ�.

int CReportRiderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(LF->POWER_CHECK(4010, "�������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm2), _T("�������"), 0,CReportForm2::IDD);
	if(LF->POWER_CHECK(4020, "��纰�Ǽ�"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm4), _T("��纰�Ǽ�"), 0,CReportForm4::IDD);
	}
	if(LF->POWER_CHECK(4030, "���ſ�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm13), _T("���ſ�����"), 0,CReportForm13::IDD);
	if(LF->POWER_CHECK(4040, "��縶�ϸ���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm20), _T("��縶�ϸ���"), 0,CReportForm20::IDD);
	if(LF->POWER_CHECK(4050, "��������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm8), _T("��������"), 0,CReportForm8::IDD);
	if(LF->POWER_CHECK(4060, "��纰�Ǽ�(���Ա�)"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm25), _T("��纰�Ǽ�(���Ա�)"), 0,CReportForm25::IDD);
	if(LF->POWER_CHECK(4070, "����������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm26), _T("����������"), 0,CReportForm26::IDD);
	if(LF->POWER_CHECK(4080, "���¶������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm29), _T("���¶������"), 0,CReportForm29::IDD);

	if(LF->POWER_CHECK(4090, "�����ݿ�û") && (LF->IsThisCompany("����") || LF->IsThisCompany("����")))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm32), _T("�����ݿ�û"), 0,CReportForm32::IDD);
	if(LF->POWER_CHECK(4100, "�ܸ����̷°���") && (LF->IsThisCompany("����") || LF->IsThisCompany("����")))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm33), _T("�ܸ����̷°���"), 0,CReportForm33::IDD);

	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("���� �ִ� ������ �ִ� �������� �������� �ʽ��ϴ�."), 0,CNotHasPowerForm::IDD);


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

