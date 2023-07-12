// FormViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FormViewDlg.h"

#ifndef _STANDALONE
	#include "LogiUtil.h"
	#include "ChangeColorDlg.h"
	#include "MYFormView.h"
#endif

// CFormViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFormViewDlg, CMyDialog)

CFormViewDlg::CFormViewDlg(CWnd* pParent, BOOL bAutoDelete)
	: CMyDialog(CFormViewDlg::IDD, pParent)
{
	m_pObject = NULL;
	m_pView = NULL;
	m_nStartBranch = 0;
	m_bDisableFirstRefresh = FALSE;
	m_bAutoDelete = bAutoDelete;
	m_pwndTaskPanel = NULL;

	if (pParent->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CFormView))) {
		m_pFormView = (CMyFormView*)pParent;
		LU->m_nCopyFormViewCnt++;
	}
	else
		m_pFormView = NULL;
}

CFormViewDlg::~CFormViewDlg()
{
}

void CFormViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFormViewDlg, CMyDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY , OnTaskPanelNotify)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()


// CFormViewDlg 메시지 처리기입니다.
BOOL CFormViewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	SetWindowText(m_strCaption);

	if(m_rcClient.Width() > 0)
	{
		m_rcClient.InflateRect(2, 2, 2, 2);
		MoveWindow(m_rcClient);
	}

#ifndef _STANDALONE
	LU->InitPaneManager(&m_paneManager, this);
	LU->MakeNetworkPane(&m_paneManager, &m_pwndPaneNetwork, m_pwndTaskPanel, m_nStartBranch);
#endif

#ifdef _STANDALONE
	CenterWindow();
#endif

	if(!m_bDisableFirstRefresh)
		m_pView->PostMessage(WM_COMMAND, WM_FIRST_REFRESH);

	return TRUE;
}

int CFormViewDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(m_pObject)
	{
		m_pView = (CView*)m_pObject->CreateObject();

		if(!m_pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
				CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy), 
				this, AFX_IDW_PANE_FIRST, NULL))
		{
			TRACE0("Failed to create view window\n");
			return -1;
		}

		((CMyFormView*)m_pView)->m_pwndTaskPanel = m_pwndTaskPanel;
		((CMyFormView*)m_pView)->m_pwndPaneNetwork = m_pwndPaneNetwork;
		((CMyFormView*)m_pView)->m_bCopyView = TRUE;
	}

	return 0;
}

void CFormViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);

	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	if (m_pView && m_pView->GetSafeHwnd())
	{	
		m_pView->MoveWindow(rcClient);
	}	
}

void CFormViewDlg::OnClose()
{
	if (m_pFormView && m_pFormView->GetSafeHwnd())
	{
		LU->m_nCopyFormViewCnt--;
	}

	CMyDialog::OnClose();
	if(m_bAutoDelete)
		delete this;
}

LRESULT CFormViewDlg::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

#ifndef _STANDALONE
	if(wParam == XTP_DPN_SHOWWINDOW)
	{
		if(!pPane->IsValid())
		{
			if(pPane->GetID() == IDR_PANE_NETWORK)
			{
				if(LU->CreateToolBox(&m_pwndTaskPanel, this))
				{
					pPane->Attach(m_pwndTaskPanel);
					LU->ResetToolboxItems(m_pwndTaskPanel);
				}
			}
		}

		return TRUE; // handled
	}
	else if(wParam == XTP_DPN_CLOSEPANE)
	{
		pPane->Hide();			
		return XTP_ACTION_NOCLOSE;
	}
#endif

	return FALSE;
}

LRESULT CFormViewDlg::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
#ifndef _STANDALONE
	return LU->OnTaskPanelNotify(wParam, lParam, m_pwndPaneNetwork, &m_paneManager, m_pView);
#endif
	return 0;
}


LRESULT CFormViewDlg::OnKickIdle(WPARAM, LPARAM)
{
#ifndef _STANDALONE
	m_paneManager.UpdatePanes();
#endif
	return 0;
}
