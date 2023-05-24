// StaffView.cpp : ���� �����Դϴ�.
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


// CStaffViewNew �����Դϴ�.

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
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}

// CStaffViewNew �޽��� ó�����Դϴ�.

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

	if(LF->POWER_CHECK(5010, "������"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffForm14), _T("������"), 0,CStaffForm14::IDD);
	//	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage12), _T("������"), 0,CStaffPage12::IDD);
	}
	if(LF->POWER_CHECK(5020, "����������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage11), _T("����������"), 0,CStaffPage11::IDD);
	if(LF->POWER_CHECK(5030, "������"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage13), _T("������(�Ϻθ������)"), 0,CStaffPage13::IDD);
	if(LF->POWER_CHECK(5040, "��缼�λ���"))
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage7), _T("��缼�λ���(�Ϻθ������)"), 0,CStaffPage7::IDD);
	if(LF->POWER_CHECK(5050, "�����̿��"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage19), _T("�����̿��(�����ϼ�)"), 0,CStaffPage19::IDD);
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage2), _T("�����̿��(�ܸ��α���)"), 0,CStaffPage2::IDD);
	}
	if(LF->POWER_CHECK(5060, "��ٰ���"))
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage4), _T("��������"), 0,CStaffPage4::IDD);
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage17), _T("�ܸ���α���"), 0,CStaffPage17::IDD);
	}
	if(LF->POWER_CHECK(5070, "�����ݹ�������"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage10), _T("�����ݹ�������"), 0,CStaffPage10::IDD);
	if(LF->POWER_CHECK(5070, "�����ݹ�������(��ð���)"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage15), _T("�����ݹ�������(��ð���)"), 0,CStaffPage15::IDD);
	if(LF->POWER_CHECK(5090, "�����ݹ��������α�"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage16), _T("�����ݹ��������α�"), 0,CStaffPage16::IDD);
	if(LF->POWER_CHECK(5100, "�������"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage18), _T("�������"), 0,CStaffPage18::IDD);
	if(LF->POWER_CHECK(5200, "���������"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage20), _T("���������"), 0,CStaffPage20::IDD);
	if(LF->POWER_CHECK(5300, "�����׷켳��"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage21), _T("�����׷켳��"), 0,CStaffPage21::IDD);
	//if(LF->POWER_CHECK(5400, "�߽��ڵ��"))													// 4050 -> 4090
	//	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffPage22), _T("�߽Ź�ȣ���"), 0,CStaffPage22::IDD);
	if(LF->POWER_CHECK(5400, "�߽��ڵ��"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CTakerPage3), _T("�߽Ź�ȣ���"), 0,CTakerPage3::IDD);

	if(LF->POWER_CHECK(5500, "��뺸��Ű�����"))													// 4050 -> 4090
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CStaffForm27), _T("��뺸��Ű�����"), 0,CStaffForm27::IDD);


	if(m_wndTabControl.GetItemCount() == 0)
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CNotHasPowerForm), _T("���� �ִ� ������ �ִ� �������� �������� �ʽ��ϴ�."), 0,CNotHasPowerForm::IDD);

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


