	// RcpPageInfoForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPageInfoForm.h"
#include "RcpView.h"

// CRcpPageInfoForm

IMPLEMENT_DYNCREATE(CRcpPageInfoForm, CMyFormView)

CRcpPageInfoForm::CRcpPageInfoForm()
	: CMyFormView(CRcpPageInfoForm::IDD)
{
	m_bInitialized = FALSE;
}

CRcpPageInfoForm::~CRcpPageInfoForm()
{
}

void CRcpPageInfoForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTICE_LIST, m_NoticeList);
	DDX_Control(pDX, IDC_SHOW_NOTICE_BTN, m_ShowNoticeBtn);
}

BEGIN_MESSAGE_MAP(CRcpPageInfoForm, CMyFormView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_SHOW_NOTICE_BTN, OnBnClickedShowNoticeBtn)
END_MESSAGE_MAP()


// CRcpPageInfoForm 진단입니다.

#ifdef _DEBUG
void CRcpPageInfoForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CRcpPageInfoForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CRcpPageInfoForm 메시지 처리기입니다.

void CRcpPageInfoForm::OnInitialUpdate()
{
	if(m_bInitialized)
		return;

	m_bInitialized = TRUE;
	CMyFormView::OnInitialUpdate();

	m_NoticeList.SetExtendedStyle(LVS_EX_FLATSB);
	m_NoticeList.InsertColumn(0, "1", LVCFMT_LEFT, 70);
	m_NoticeList.InsertColumn(1, "2", LVCFMT_LEFT, 80);
	m_NoticeList.InsertColumn(2, "3", LVCFMT_LEFT, 680);
	m_NoticeList.SetFont(m_FontManager.GetFont("돋움", 11));
}


void CRcpPageInfoForm::OnSize(UINT nType, int cx, int cy)
{
	//	CMyFormView::OnSize(nType, cx, cy); //Scrollbars never are displayed;
	SetScaleToFitSize(CSize(cx, cy)); 

	if(m_NoticeList.GetSafeHwnd())
	{
		CRect rc, rcEdt, rcBtn; 
		GetClientRect(rc);
		m_NoticeList.GetWindowRect(rcEdt);
		m_ShowNoticeBtn.GetWindowRect(rcBtn);
		ScreenToClient(rcEdt);
		ScreenToClient(rcBtn);

		rcBtn.right = rc.right - 5;
		rcBtn.left = rcBtn.right - 90;
		rcBtn.bottom = rc.bottom - 5;

		rcEdt.right = rcBtn.left - 5;
		rcEdt.bottom = rc.bottom - 5;

		//rcList.right = rc.right - 2;
		m_NoticeList.MoveWindow(rcEdt);
		m_ShowNoticeBtn.MoveWindow(rcBtn);
	}

	
}

void CRcpPageInfoForm::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(LU->GetRcpView()->GetBigUnderFormToggle())
		LU->GetRcpView()->SetFormHeightBig();
	else 
		LU->GetRcpView()->SetFormHeightNormal();

	CMyFormView::OnLButtonDblClk(nFlags, point);
}


void CRcpPageInfoForm::OnBnClickedShowNoticeBtn()
{  
	LU->GetRcpView()->OnBnClickedShowNoticeBtn();
}

BOOL CRcpPageInfoForm::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP || pMsg->message == WM_RBUTTONUP ||
		pMsg->message == WM_NCLBUTTONUP || pMsg->message == WM_NCRBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE)
	{
		return LU->GetRcpView()->PreTranslateMessage(pMsg);
	}

	//else if(pMsg->wParam == VK_DOWN)
	//{
	//	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_NOTEPAD_EDIT)
	//	{
	//		m_edtNotePad.GetWindowText()
	//	}
	//}


	return CMyFormView::PreTranslateMessage(pMsg);
}



