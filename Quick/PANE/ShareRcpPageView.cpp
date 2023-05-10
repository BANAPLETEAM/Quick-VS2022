// ShareRcpPageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareRcpPageView.h"
#include "ShareRcpSubPageDlg.h"


IMPLEMENT_DYNCREATE(CShareRcpPageView, CMyFormView)

CShareRcpPageView::CShareRcpPageView()
	: CMyFormView(CShareRcpPageView::IDD)
{
}

CShareRcpPageView::~CShareRcpPageView()
{
}

void CShareRcpPageView::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_OPTION, m_stcOption);
	DDX_Control(pDX, IDC_XTPLISTCTRL_COMBO, m_cmbSearch);
	DDX_Control(pDX, IDC_XTPLISTCTRL_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CShareRcpPageView, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
END_MESSAGE_MAP()

#define IDC_TABCONTROL 100
// CShareRcpPageView 진단입니다.

#ifdef _DEBUG
void CShareRcpPageView::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareRcpPageView::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CShareRcpPageView 메시지 처리기입니다. 



void CShareRcpPageView::RefreshList()
{
	long nIndex = m_wndTabControl.GetCurSel();
	CShareRcpSubPageDlg *pPage = (CShareRcpSubPageDlg*)GetTabItem(nIndex);

	pPage->Refresh();
}


CWnd* CShareRcpPageView::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}


void CShareRcpPageView::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate();

	m_cmbSearch.SetCurSel(0);
	CRect rtSTATIC_OPTION, rcWindow;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(FALSE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);

	//순서 바뀌면 안됨
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareRcpSubPageDlg), "콜 넘김(자사콜)", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareRcpSubPageDlg), "콜 받음(타사콜)", 0);

	CShareRcpSubPageDlg *pPage1 = (CShareRcpSubPageDlg*)GetTabItem(0);
	CShareRcpSubPageDlg *pPage2 = (CShareRcpSubPageDlg*)GetTabItem(1);

	pPage1->m_bTake = TRUE;
	pPage2->m_bTake = FALSE;

	SetResize(IDC_STATIC_OPTION, sizingRightBottom);

	//RefreshList();
}

void CShareRcpPageView::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CShareRcpPageView::OnEnChangeXtplistctrlEdit()
{
	CShareRcpSubPageDlg *pPage = (CShareRcpSubPageDlg*)GetTabItem(m_wndTabControl.GetCurSel());

	long nIndex = m_cmbSearch.GetCurSel();
	CString sSearch; m_edtSearch.GetWindowText(sSearch);

	pPage->FilterList(nIndex, sSearch);
}

void CShareRcpPageView::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(this->GetSafeHwnd() && m_wndTabControl.GetSafeHwnd())
	{ 
		CRect rtSTATIC_OPTION;
		this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

		CShareRcpSubPageDlg *pPage = (CShareRcpSubPageDlg*)GetTabItem(m_wndTabControl.GetCurSel());

		if(pPage != NULL)
		{
			CRect  rcLst, rcTab;

			m_wndTabControl.GetWindowRect(rcTab);
			pPage->m_lstReport.GetWindowRect(rcLst);

			ScreenToClient(rcTab);
			ScreenToClient(rtSTATIC_OPTION); 
			ScreenToClient(rcLst);

			rcTab.right = rtSTATIC_OPTION.right;
			rcTab.bottom = rtSTATIC_OPTION.bottom; 

			rcLst.left = rtSTATIC_OPTION.left + 1;
            rcLst.right = rtSTATIC_OPTION.right - 10;
			rcLst.top = rtSTATIC_OPTION.top + 25; // 해더
			rcLst.bottom = rtSTATIC_OPTION.bottom - 5;// 아래 스크롤

			ClientToScreen(rcLst);
			pPage->ScreenToClient(rcLst);
			m_wndTabControl.MoveWindow(rcTab);
			pPage->m_lstReport.MoveWindow(rcLst);
		}		
	}
}

void CShareRcpPageView::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}
