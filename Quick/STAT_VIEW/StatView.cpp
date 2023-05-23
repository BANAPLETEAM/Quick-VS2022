// IncomeView.cpp : ���� �����Դϴ�.
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


// CStatView �׸����Դϴ�.

void CStatView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CStatView �����Դϴ�.

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


// CStatView �޽��� ó�����Դϴ�.

int CStatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(LF->POWER_CHECK(8010, "�����ݼ�����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm2), _T("�����ݼ�����"), 0,CStatForm2::IDD);
	if(LF->POWER_CHECK(8020, "���м�"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerPage7), _T("���м�"), 0, CCustomerPage7::IDD);
	if(LF->POWER_CHECK(8030, "���������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm3), _T("���������"), 0,CStatForm3::IDD);
	if(LF->POWER_CHECK(8040, "���������_�ݼ�"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm5), _T("���������_�ݼ�"), 0,CStatForm5::IDD);
	if(LF->POWER_CHECK(8050, "�Ϻ��Ǽ�"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm11), _T("�Ϻ��Ǽ�"), 0,CReportForm11::IDD);
	if(LF->POWER_CHECK(8060, "����������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm5), _T("����������"), 0,CReportForm5::IDD);
	if(LF->POWER_CHECK(8070, "SMS���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm12), _T("SMS��躸��"), 0,CReportForm12::IDD);
	if(LF->POWER_CHECK(8080, "������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm14), _T("������"), 0,CReportForm14::IDD);
	if(LF->POWER_CHECK(8090, "������������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm9), _T("������������"), 0,CStatForm9::IDD);
		//LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CReportForm7), _T("������������"), 0,CReportForm7::IDD);
	
	if(LF->POWER_CHECK(8100, "���������곻��"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm6), _T("���������곻��"), 0, CStatForm6::IDD);
	if(LF->POWER_CHECK(8110, "SMS����"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm7), _T("SMS����"), 0, CStatForm7::IDD);

	if(LF->POWER_CHECK(8131, "����API"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatForm10), _T("����API��������"), 0,CStatForm10::IDD);

	if(LF->POWER_CHECK(8200, "�ű԰���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatChildFormCustomerNew), _T("�ű԰���"), 0,CStatChildFormCustomerNew::IDD);


	CBranchInfo *pBI;
	if (m_ba.GetCount() > 1)
		pBI = m_ba.GetAt(1);
	else
		pBI = m_ba.GetAt(0);

	BOOL bIPPBX = pBI->bIPPBXType;

	if(LF->POWER_CHECK(8120, "�ڼ��������") && bIPPBX)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStatTelserverRouteLog), _T("�ڼ��������"), 0, CStatTelserverRouteLog::IDD);

	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("���� �ִ� ������ �ִ� �������� �������� �ʽ��ϴ�."), 0,CNotHasPowerForm::IDD);


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