// IncomeView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeView.h"
#include "IncomeForm3.h"
#include "IncomeForm4.h"
#include "IncomeForm5.h"
#include "IncomeForm6.h"
#include "IncomeForm7.h"
#include "IncomeForm8.h"
#include "IncomeForm9.h"
#include "IncomeForm10.h"
#include "IncomeForm11.h"
#include "NotHasPowerForm.h"
#include "RiderReportDlg.h"

// CIncomeView

IMPLEMENT_DYNCREATE(CIncomeView, CView)

CIncomeView::CIncomeView()
{
	m_nIncomeForm7Tab = -1;
}

CIncomeView::~CIncomeView()
{
}

BEGIN_MESSAGE_MAP(CIncomeView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_BRANCH_CLICK_EVENT, OnBranchClickEvent)
END_MESSAGE_MAP()


// CIncomeView �׸����Դϴ�.

void CIncomeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CIncomeView �����Դϴ�.

#ifdef _DEBUG
void CIncomeView::AssertValid() const
{
	CView::AssertValid();
}

void CIncomeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CIncomeView �޽��� ó�����Դϴ�.

int CIncomeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	LU->CreateFormViewTabControl(this, &m_wndTabControl);

	if(POWER_CHECK(7010, "�Աݰ���_direct"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm4), _T("�Աݰ���"), 0,CIncomeForm4::IDD);
		m_nIncomeForm7Tab++;
	}
	if(POWER_CHECK(7020, "����ķα�_direct"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm5), _T("����ķα�"), 0,CIncomeForm5::IDD);
		m_nIncomeForm7Tab++;
	}
	if(POWER_CHECK(7030, "���Ա���������"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm3), _T("���Ա���������"), 0,CIncomeForm3::IDD);
		m_nIncomeForm7Tab++;
	}
	if(POWER_CHECK(7040, "���Աݰ���"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm7), _T("���Աݰ���"), 0,CIncomeForm7::IDD);
	}
	else
		m_nIncomeForm7Tab = -100;

	if(POWER_CHECK(7050, "���Աݷα�"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm6), _T("���Աݷα�"), 0,CIncomeForm6::IDD);
	}

	if(POWER_CHECK(7080, "���Աݷα�"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm8), _T("�������� ��������"), 0,CIncomeForm8::IDD);
	}

	if(POWER_CHECK(7090, "��簡�����") )
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm9), _T("��簡�����"), 0,CIncomeForm9::IDD);
	}

	if(POWER_CHECK(7100, "����ī��") )
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm10), _T("����ī��"), 0,CIncomeForm10::IDD);
	}

	if(POWER_CHECK(7110, "��簡���������") )
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CIncomeForm11), _T("��簡���������"), 0,CIncomeForm11::IDD);

	}

	m_wndTabControl.m_nIncomeForm7Tab = ++m_nIncomeForm7Tab;

	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("���� �ִ� ������ �ִ� �������� �������� �ʽ��ϴ�."), 0,CNotHasPowerForm::IDD);


	return 0;
}

void CIncomeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}


int CIncomeView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

LONG CIncomeView::OnBranchClickEvent(UINT nBranch, LPARAM lParam)
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());

	if(m_CurCodeInfo[pView] != GetCurBranchInfo())
	{
		pView->RefreshList();
	}

	return 0;
}

void CIncomeView::FirstRefresh()
{
	CXTPTabManagerItem *pItem = m_wndTabControl.GetItem(m_wndTabControl.GetCurSel());
	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	pView->FirstRefresh();
}


void CIncomeViewTabControl::OnItemClick(CXTPTabManagerItem* pItem)
{
	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();

	if(hWnd == NULL)
		return;

	CMyFormView *pView = (CMyFormView*)CWnd::FromHandle(pItem->GetHandle());
	CRuntimeClass * pClass = pView->GetRuntimeClass();

	if(pClass->m_lpszClassName != "CIncomeForm7")
	{
		if(m_nIncomeForm7Tab <= 0)
		{
			CXTPTabManagerItem* pXTPTabManagerItem =  GetItem(m_nIncomeForm7Tab);
			if(pXTPTabManagerItem)
			{
				if(pXTPTabManagerItem->GetHandle())
				{
					CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
					CIncomeForm7 *pIncomeForm7	= (CIncomeForm7*)pWnd;

					if(pIncomeForm7->m_pRiderReportDlg)
						pIncomeForm7->m_pRiderReportDlg->ShowWindow(SW_HIDE);
				}
			}
		}
	}
}