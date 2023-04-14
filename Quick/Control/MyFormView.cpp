// MyFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyFormView.h"
#include "MainFrm.h"
#include "FormViewDlg.h"

#define TOP_SIZING_RIGHT_MARGIN		2
#define TOP_SIZING_BOTTOM_MARGIN	2

CString CMyFormView::m_strLastFormView;
CURRENT_CODE_INFO m_CurCodeInfo;

// CMyFormView
IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView((UINT)0)
{
	m_bFirstRefreshList = FALSE;
	m_bFirstRefreshList2 = FALSE;
	m_bRefreshTimerON = FALSE;
	m_bInitialUpdateCalled = FALSE;
	m_bResizeVer = FALSE;
	m_bResizeHori = FALSE;
	m_bChangeCursor = FALSE;
	m_bMoveControl = FALSE;
	m_pwndTaskPanel = NULL;
	m_pwndPaneNetwork = NULL;
	m_bOptionView = FALSE;
}

CMyFormView::CMyFormView(UINT nID)
	: CFormView(nID)
{
	m_bFirstRefreshList = FALSE;
	m_bFirstRefreshList2 = FALSE;
	m_bRefreshTimerON = FALSE;
	m_bInitialUpdateCalled = FALSE;
	m_bOptionView = FALSE;
}


CMyFormView::~CMyFormView()
{
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_COMMAND(WM_FIRST_REFRESH, FirstRefresh)
	ON_WM_MOUSEACTIVATE()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_COPY_FORM_DLG, &CMyFormView::OnCopyFormDlg)
	ON_COMMAND(ID_COPY_FORM_DLG_NEW_MONITOR, &CMyFormView::OnCopyFormDlgNewMonitor)
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMyFormView 진단입니다.

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CMyFormView 메시지 처리기입니다.

void CMyFormView::OnInitialUpdate()
{
	g_bana_log->Print("\nCMyFormView OPEN = ### %s ###\n\n",  GetRuntimeClass()->m_lpszClassName);
	CFormView::OnInitialUpdate();

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	m_bInitialUpdateCalled = TRUE;
	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcVertical = AfxGetApp()->LoadCursor(IDC_VERTICAL);
	m_hcMiddle = AfxGetApp()->LoadCursor(IDC_MIDDLE);
}

void CMyFormView::OnSize(UINT nType, int cx, int cy)
{
	//CFormView::OnSize(nType, cx, cy);
	if(m_bInitialUpdateCalled == TRUE)
	{
		SetScaleToFitSize(CSize(cx, cy));
		MoveClient();
	}
}


void CMyFormView::MoveClient()
{
	if(m_mapSizing.size() > 0)
	{
		CRect rcView, rc;
		SIZING_MAP::iterator it;
		GetClientRect(rcView);
		for(it = m_mapSizing.begin(); it != m_mapSizing.end(); it++)
		{
			int nID = (*it).first;
			CWnd *pWnd = (CWnd*)GetDlgItem(nID);

			if(pWnd == NULL)
				return;

			pWnd->GetWindowRect(rc);
			ScreenToClient(rc);

			switch((*it).second)
			{
			case sizingRight:
				{
					int x = m_mapMargin[(*it).first].x;
					if(x == RIGHT_HOLD)
					{
						int nWidth = rc.Width();
						rc.right = rcView.right - TOP_SIZING_RIGHT_MARGIN;
						rc.left = rc.right - nWidth;
					}
					else
					{
						rc.right = rcView.right - TOP_SIZING_RIGHT_MARGIN - m_mapMargin[(*it).first].x;
					}
				}
				break;

			case sizingBottom:
				{
					int y = m_mapMargin[(*it).first].y;
					if(y == BOTTOM_HOLD)
					{
						int nHeight = rc.Height();
						rc.bottom = rcView.bottom - TOP_SIZING_BOTTOM_MARGIN;
						rc.top = rc.bottom - nHeight;
					}
					else
					{
						rc.bottom = rcView.bottom - TOP_SIZING_BOTTOM_MARGIN - m_mapMargin[(*it).first].y;
					}
				}
				break;

			case sizingRightBottom:
				{
					int x = m_mapMargin[(*it).first].x;
					if(x == RIGHT_HOLD)
					{
						int nWidth = rc.Width();
						rc.right = rcView.right - TOP_SIZING_RIGHT_MARGIN;
						rc.left = rc.right - nWidth;
					}
					else
					{
						rc.right = rcView.right - TOP_SIZING_RIGHT_MARGIN - m_mapMargin[(*it).first].x;
					}

					int y = m_mapMargin[(*it).first].y;
					if(y == BOTTOM_HOLD)
					{
						int nHeight = rc.Height();
						rc.bottom = rcView.bottom - TOP_SIZING_BOTTOM_MARGIN;
						rc.top = rc.bottom - nHeight;
					}
					else
					{
						rc.bottom = rcView.bottom - TOP_SIZING_BOTTOM_MARGIN - m_mapMargin[(*it).first].y;
					}
				}

				break;
			}

			if(pWnd) {
				pWnd->MoveWindow(rc, FALSE);
				Invalidate();
			}
		}
	}
}

void CMyFormView::SetResize(long nID, SIZING_TYPE st, int xMargin, int yMargin)
{
	MARGIN_DATA md;

	if(xMargin > 0 || yMargin >0)
	{
		md.x = xMargin;
		md.y = yMargin;
		m_mapMargin[nID] = md;
	}

	m_mapSizing[nID] = st;
}


void CMyFormView::RefreshList()
{
	if(FALSE == m_bInitialUpdateCalled ) return;
	m_CurCodeInfo[this] = GetCurBranchInfo(TRUE);
	m_bFirstRefreshList = TRUE;
}

void CMyFormView::RefreshList2()
{
	m_CurCodeInfo[this] = GetCurBranchInfo(TRUE);
	m_bFirstRefreshList2 = TRUE;
}



int CMyFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

BOOL CMyFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	return CFormView::PreCreateWindow(cs);
}



void CMyFormView::FirstRefresh()
{
	if(!m_bFirstRefreshList || GetOwner()->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CDialog)))
		RefreshList();
}

void CMyFormView::FirstRefresh2()
{
	if(!m_bFirstRefreshList || GetOwner()->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CDialog)))
		RefreshList2();
}


void CMyFormView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFormView::OnShowWindow(bShow, nStatus);

	//첫번째 SHOW인 경우에 리스트를 초기갱신한다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	if(pFrame)
	{
		CRuntimeClass *p = GetRuntimeClass();
		LU->SetTitlePrint(CString("CMyFormView::") +  p->m_lpszClassName);
		m_strLastFormView = CString("CMyFormView::") +  p->m_lpszClassName;

		//if(bShow &&  !m_bFirstRefreshList)
			if(bShow && !m_bFirstRefreshList && m_bInitialUpdateCalled == TRUE)
		{
			CString strClassName = p->m_lpszClassName;
			if(strClassName.Find("Staff", 0) >= 0 ||
				strClassName.Find("Report", 0) >= 0 ||
				strClassName.Find("Income", 0) >= 0 ||
				strClassName.Find("Stat", 0) >= 0 ||
				strClassName.Find("Home", 0) >= 0)
				{
				FirstRefresh();
				//RefreshList();
				//SetTimer(0xFFFF, 100, NULL);
				//m_bRefreshTimerON = TRUE;
			}
			else if(
				strClassName.Find("Customer", 0) >= 0 ) //커스텀머탭 초기갱신 Refresh2() 함수
			{
				SetTimer(1000, 100, NULL);
				m_bRefreshTimerON = TRUE;
			}
		}
	}
}

void CMyFormView::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0xFFFF)
	{
		KillTimer(nIDEvent);
		if(m_bRefreshTimerON)
		{
			FirstRefresh();
			m_bRefreshTimerON = FALSE;
		}
	}

	if(nIDEvent == 1000)
	{
		KillTimer(nIDEvent);
		if(m_bRefreshTimerON)
		{
			FirstRefresh2();
			m_bRefreshTimerON = FALSE;
		}
	}

	CFormView::OnTimer(nIDEvent);
}

BOOL CMyFormView::Save(long nCompany, BOOL bAll)
{
	return TRUE;
}
BOOL CMyFormView::PreTranslateMessage(MSG* pMsg)
{
	if(m_bResizeHori != TRUE && m_bResizeVer != TRUE)
		return CFormView::PreTranslateMessage(pMsg);

	
	if(pMsg->message == WM_LBUTTONUP)
	{
		m_bChangeCursor = FALSE; // 화면이동 변수들
		m_bMoveControl = FALSE;
		SetCursor(m_hcArrow);
	}

	if(pMsg->message == WM_MOUSEMOVE)
	{
		CPoint point; ::GetCursorPos(&point);
		ScreenToClient(&point); 

		if(m_bMoveControl == TRUE)
		{
			MoveList(point);
		}
		else
		{
			ChangeCursor(point);
		}
	}


	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(m_bChangeCursor) 
		{
			m_bMoveControl = TRUE;
			SetCursor(m_hcArrow); 
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}

void CMyFormView::MoveList(CPoint pt)
{
	CWnd *pLeft = GetDlgItem(m_nLeftControl);
	CWnd *pRight = GetDlgItem(m_nRightControl);

	if(pLeft == NULL || pRight == NULL) return;

	if(m_bResizeHori)
		SetCursor(m_hcVertical);  
	else
		SetCursor(m_hcMiddle);  

	CRect rcPage;
	this->GetWindowRect(&rcPage);

	CRect rcLeft, rcRight;   

	pLeft->GetWindowRect(&rcLeft);
	pRight->GetWindowRect(&rcRight);

	ScreenToClient(rcLeft);
	ScreenToClient(rcRight);

	if(m_bResizeHori == TRUE)
	{
		rcLeft.right = pt.x - 2; 
		rcRight.left = pt.x + 2; 
	}
	else
	{
		rcLeft.bottom = pt.y - 2; 
		rcRight.top = pt.y + 2; 
	}

	if((rcRight.Width() > 100 && m_bResizeHori) ||
		(rcRight.Height() > 50 && m_bResizeVer))
	{
		pLeft->MoveWindow(rcLeft);
		pRight->MoveWindow(rcRight);
	}		
}

void CMyFormView::ChangeCursor(CPoint pt)
{
	CWnd *pLeft = GetDlgItem(m_nLeftControl);
	CWnd *pRight = GetDlgItem(m_nRightControl);

	if(pLeft == NULL || pRight == NULL) return;

	CRect rcLeft, rcRight;   

	pLeft->GetWindowRect(&rcLeft);
	pRight->GetWindowRect(&rcRight);

	ScreenToClient(rcLeft);
	ScreenToClient(rcRight);

	if(m_bResizeHori)
	{
		if((rcLeft.right < pt.x) && (pt.x < rcRight.left))
		{ 
			if((rcLeft.top <= pt.y) && (rcLeft.bottom >= pt.y)) 
			{
				SetCursor(m_hcVertical);
				m_bChangeCursor = TRUE;
			}
			else
				m_bChangeCursor = FALSE;
		}
		else
			m_bChangeCursor = FALSE;
	}

	if(m_bResizeVer)
	{
		if((rcLeft.bottom < pt.y) && (pt.y < rcRight.top))
		{ 
			if((rcLeft.left <= pt.y) && (rcLeft.right >= pt.y)) 
			{
				SetCursor(m_hcMiddle);
				m_bChangeCursor = TRUE;
			}
			else
				m_bChangeCursor = FALSE;
		}
		else
			m_bChangeCursor = FALSE;
	}

	
	if(m_bChangeCursor == TRUE)
	{
		return;
	}
	else
	{
		m_bChangeCursor = FALSE;
		SetCursor(m_hcArrow);
	}
}

void CMyFormView::SetResizeVer(long nLeft, long nRight)
{
	m_nLeftControl = nLeft; m_nRightControl = nRight; 
	m_bResizeVer = TRUE; m_bResizeHori = FALSE;
	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcVertical = AfxGetApp()->LoadCursor(IDC_VERTICAL);
}

void CMyFormView::SetResizeHori(long nLeft, long nRight)
{
	m_nLeftControl = nLeft; m_nRightControl = nRight;
	m_bResizeVer = FALSE; m_bResizeHori = TRUE;
	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcMiddle = AfxGetApp()->LoadCursor(IDC_MIDDLE);
}

void CMyFormView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this);
}

HBRUSH CMyFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	/*
	if(m_bOptionView)
	{
		if(nCtlColor == CTLCOLOR_STATIC ||
			nCtlColor == CTLCOLOR_BTN) 
		{
			pDC->SetBkMode(TRANSPARENT); 
		}
	}
	*/

	HBRUSH hUserBrush;
	if(pWnd != this)
		if(LF->OnMyCtlColor(pDC, pWnd, nCtlColor, hUserBrush))
			return hUserBrush;

	return hbr;
}

int CMyFormView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;
	//return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CMyFormView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if(nSBCode == SB_ENDSCROLL)
		Invalidate(FALSE);
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyFormView::OnCopyFormDlg()
{
	CFormViewDlg *pDlg = new CFormViewDlg(this);

	GetWindowText(pDlg->m_strCaption);
	GetWindowRect(pDlg->m_rcClient);
	pDlg->m_pObject = GetRuntimeClass();

	pDlg->Create(IDD_FORM_VIEW_DLG, this);
	pDlg->ShowWindow(SW_SHOW);
}

void CMyFormView::OnCopyFormDlgNewMonitor()
{
	CFormViewDlg *pDlg = new CFormViewDlg(this);

	GetWindowText(pDlg->m_strCaption);
	GetWindowRect(pDlg->m_rcClient);

	for(int i = 0; i < m_aryMonitors.GetCount(); i++)
	{
		CRect rc(m_aryMonitors.GetAt(i).rcWork);

		if(!rc.PtInRect(pDlg->m_rcClient.CenterPoint()))
			pDlg->m_rcClient = rc;
	}

	pDlg->m_pObject = GetRuntimeClass();
	pDlg->Create(IDD_FORM_VIEW_DLG, this);
	pDlg->ShowWindow(SW_SHOWMAXIMIZED);
}

void CMyFormView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CFormView::OnRButtonDown(nFlags, point);

#ifndef _QUICK
	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);

	ClientToScreen(&point);
	CMenu *pRMenu = (CMenu*)rMenu.GetSubMenu(21);
#else
	CMenu rMenu;
	rMenu.LoadMenu(IDR_COPY_FORM_MENU);

	ClientToScreen(&point);
	CMenu *pRMenu = (CMenu*)rMenu.GetSubMenu(0);
#endif

	HDC hDC=NULL;
	m_aryMonitors.RemoveAll();
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if(hDC)
	{
		::EnumDisplayMonitors(hDC,NULL,MonitorEnumProc, (LPARAM)this);
		DeleteDC(hDC);
	}

	if(m_aryMonitors.GetCount() <= 1)
	{
		pRMenu->RemoveMenu(ID_COPY_FORM_DLG_NEW_MONITOR, MF_BYCOMMAND);
	}

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

BOOL CMyFormView::OnEraseBkgnd(CDC* pDC)
{
	if(m_bOptionView)
	{
		CBrush backBrush(RGB(231, 240, 255)); // <- 흰색칼러로. 
		CBrush* pOldBrush = pDC->SelectObject(&backBrush); 
		CRect rect; pDC->GetClipBox(&rect); 
		pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
		pDC->SelectObject(pOldBrush); 
		return TRUE; 
	}
	
	return CFormView::OnEraseBkgnd(pDC);
}
