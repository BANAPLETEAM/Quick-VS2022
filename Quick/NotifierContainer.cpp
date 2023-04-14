
#include "stdafx.h"
#include "resource.h"
#include "notifiercontainer.h"


IMPLEMENT_DYNAMIC(CNotifierContainer, CWnd)
CNotifierContainer::CNotifierContainer(void)
{
	InitializeCriticalSection(&m_csNotifier);
}

CNotifierContainer::~CNotifierContainer(void)
{
	DeleteCriticalSection(&m_csNotifier);
}


BEGIN_MESSAGE_MAP(CNotifierContainer, CWnd)
	ON_MESSAGE(WM_NOTIFIER_CLICKED, OnNotifierClicked)
	ON_MESSAGE(WM_NOTIFIER_HIDE, OnNotifierHide)
END_MESSAGE_MAP()


int CNotifierContainer::Create(CWnd *pWndParent)
{
	m_pWndParent=pWndParent;
	CString strWndClass=AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW),GetSysColorBrush(COLOR_WINDOW),NULL);
	return CreateEx(0,strWndClass,NULL,WS_POPUP,0,0,0,0,pWndParent->m_hWnd,NULL);
}

void CNotifierContainer::AddNotifier(CStartbarNotifier *pNotifier)
{
	LIST_NOTIFIER::iterator it;
	UINT nNextOffsetY = 0; 

	EnterCriticalSection(&m_csNotifier);

	if(m_listNotifier.size() > 0)
	{
		nNextOffsetY = m_listNotifier.back()->GetOffsetY() + 
				m_listNotifier.back()->GetSkinHeight();
	}

	pNotifier->SetOffsetY(nNextOffsetY);
	m_listNotifier.push_back(pNotifier);
	LeaveCriticalSection(&m_csNotifier);

	pNotifier->Show();
}

void CNotifierContainer::RemoveNotifier(CStartbarNotifier *pNotifier)
{
	EnterCriticalSection(&m_csNotifier);
	m_listNotifier.remove(pNotifier);
	LeaveCriticalSection(&m_csNotifier);
}

LONG CNotifierContainer::OnNotifierClicked(WPARAM wParam, LPARAM lParam)
{
	m_pWndParent->PostMessage(WM_NOTIFIER_CLICKED, wParam, lParam);
	return 0;
}

LONG CNotifierContainer::OnNotifierHide(WPARAM wParam, LPARAM lParam)
{
	CStartbarNotifier *pNotifier = (CStartbarNotifier*)wParam;
	RemoveNotifier(pNotifier);
	delete pNotifier;
	return 0;
}



