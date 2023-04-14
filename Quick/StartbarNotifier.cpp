// StartbarNotifier.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "StartbarNotifier.h"
#include "resource.h"
#include "NotifierContainer.h"


// CStartbarNotifier

IMPLEMENT_DYNAMIC(CStartbarNotifier, CTaskbarNotifier)
CStartbarNotifier::CStartbarNotifier()
{
	m_nOffsetY = 0;
	m_ptrItemData = NULL;
}

CStartbarNotifier::~CStartbarNotifier()
{
}


BEGIN_MESSAGE_MAP(CStartbarNotifier, CTaskbarNotifier)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CStartbarNotifier 메시지 처리기입니다.
void CStartbarNotifier::Initailze(LPCTSTR szTitle, LPCTSTR szCaption,DWORD dwTimeToShow,DWORD dwTimeToLive,DWORD dwTimeToHide,int nIncrement) 
{
	m_strTitle=szTitle;
	m_strCaption=szCaption;
	m_dwTimeToShow=dwTimeToShow;
	m_dwTimeToLive=dwTimeToLive;
	m_dwTimeToHide=dwTimeToHide;
	m_nIncrement=nIncrement;
}


void CStartbarNotifier::Show(LPCTSTR szTitle, LPCTSTR szCaption,DWORD dwTimeToShow,DWORD dwTimeToLive,DWORD dwTimeToHide,int nIncrement)
{
	m_strTitle=szTitle;
	m_strCaption=szCaption;
	m_dwTimeToShow=dwTimeToShow;
	m_dwTimeToLive=dwTimeToLive;
	m_dwTimeToHide=dwTimeToHide;
	m_nIncrement=nIncrement;

	Show();
}

void CStartbarNotifier::Show()
{
	unsigned int nDesktopHeight;
	unsigned int nDesktopWidth;
	unsigned int nScreenWidth;
	unsigned int nScreenHeight;
	CRect rcDesktop;

	::SystemParametersInfo(SPI_GETWORKAREA,0,&rcDesktop,0);
	nDesktopWidth=rcDesktop.right-rcDesktop.left;
	nDesktopHeight=rcDesktop.bottom-rcDesktop.top;
	nScreenWidth=::GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight=::GetSystemMetrics(SM_CYSCREEN);

 	BOOL bTaskbarOnRight=nDesktopWidth<nScreenWidth && rcDesktop.left==0;
	BOOL bTaskbarOnLeft=nDesktopWidth<nScreenWidth && rcDesktop.left!=0;
	BOOL bTaskBarOnTop=nDesktopHeight<nScreenHeight && rcDesktop.top!=0;  
	BOOL bTaskbarOnBottom=nDesktopHeight<nScreenHeight && rcDesktop.top==0;
	
	//없어도 될듯.. 접수창에서 글 입력시 해당창이 드면서 포커스를 뺏김
	//this->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	switch (m_nAnimStatus)
	{
		case IDT_HIDDEN:
			ShowWindow(SW_SHOWNA);
			if (bTaskbarOnRight)
			{
				m_dwDelayBetweenShowEvents=m_dwTimeToShow/(m_nSkinWidth/m_nIncrement);
				m_dwDelayBetweenHideEvents=m_dwTimeToHide/(m_nSkinWidth/m_nIncrement);
				m_nStartPosX=rcDesktop.right;
				m_nStartPosY=rcDesktop.bottom-m_nSkinHeight;
				m_nTaskbarPlacement=TASKBAR_ON_RIGHT;
			}
			else if (bTaskbarOnLeft)
			{
				m_dwDelayBetweenShowEvents=m_dwTimeToShow/(m_nSkinWidth/m_nIncrement);
				m_dwDelayBetweenHideEvents=m_dwTimeToHide/(m_nSkinWidth/m_nIncrement);
				m_nStartPosX=rcDesktop.left-m_nSkinWidth;
				m_nStartPosY=rcDesktop.bottom-m_nSkinHeight;
				m_nTaskbarPlacement=TASKBAR_ON_LEFT;
			}
			else if (bTaskBarOnTop)
			{
				m_dwDelayBetweenShowEvents=m_dwTimeToShow/(m_nSkinHeight/m_nIncrement);
				m_dwDelayBetweenHideEvents=m_dwTimeToHide/(m_nSkinHeight/m_nIncrement);
				m_nStartPosX=rcDesktop.right-m_nSkinWidth;
				m_nStartPosY=rcDesktop.top-m_nSkinHeight;
				m_nTaskbarPlacement=TASKBAR_ON_TOP;
			}
			else //if (bTaskbarOnBottom)
			{
				// Taskbar is on the bottom or Invisible
				m_dwDelayBetweenShowEvents=m_dwTimeToShow/(m_nSkinHeight/m_nIncrement);
				m_dwDelayBetweenHideEvents=m_dwTimeToHide/(m_nSkinHeight/m_nIncrement);
				m_nStartPosX=0;//rcDesktop.right-m_nSkinWidth;
				m_nStartPosY=rcDesktop.bottom;
				m_nTaskbarPlacement=TASKBAR_ON_BOTTOM;
			}

			m_nCurrentPosX = m_nStartPosX;
			m_nCurrentPosY = m_nStartPosY - m_nOffsetY;

			m_nCurrentSizeX = m_nSkinWidth;
			m_nCurrentSizeY = 0;

			SetTimer(IDT_APPEARING,m_dwDelayBetweenShowEvents,NULL);
			break;

		case IDT_WAITING:
			RedrawWindow();
			KillTimer(IDT_WAITING);
			SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
			break;

		case IDT_APPEARING:
			RedrawWindow();
			break;

		case IDT_DISAPPEARING:
			KillTimer(IDT_DISAPPEARING);
			SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
			if (bTaskbarOnRight)
				m_nCurrentPosX=rcDesktop.right-m_nSkinWidth;
			else if (bTaskbarOnLeft)
				m_nCurrentPosX=rcDesktop.left;
			else if (bTaskBarOnTop)
				m_nCurrentPosY=rcDesktop.top;
			else //if (bTaskbarOnBottom)
				m_nCurrentPosY=rcDesktop.bottom-m_nSkinHeight;
			
			SetWindowPos(NULL,m_nCurrentPosX,m_nCurrentPosY,m_nSkinWidth,m_nSkinHeight,SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);
			RedrawWindow();
			break;
	}
}


void CStartbarNotifier::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case IDT_APPEARING:
			m_nAnimStatus=IDT_APPEARING;
			switch(m_nTaskbarPlacement)
			{/*
				case TASKBAR_ON_BOTTOM:
					if (m_nCurrentPosY > (m_nStartPosY-m_nSkinHeight))
						m_nCurrentPosY-=m_nIncrement;
					else
					{
						KillTimer(IDT_APPEARING);
						SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
						m_nAnimStatus=IDT_WAITING;
					}
					break;
			*/

				case TASKBAR_ON_BOTTOM:
					if(m_nSkinHeight > m_nCurrentSizeY) {
						m_nCurrentPosY -= m_nIncrement;
						m_nCurrentSizeY += m_nIncrement;
					}
					else
					{
						KillTimer(IDT_APPEARING);
						SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
						m_nAnimStatus=IDT_WAITING;
					}
					break;

				case TASKBAR_ON_TOP:
					if ((m_nCurrentPosY-m_nStartPosY)<m_nSkinHeight)
						m_nCurrentPosY+=m_nIncrement;
					else
					{
						KillTimer(IDT_APPEARING);
						SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
						m_nAnimStatus=IDT_WAITING;
					}
					break;
				case TASKBAR_ON_LEFT:
					if ((m_nCurrentPosX-m_nStartPosX)<m_nSkinWidth)
						m_nCurrentPosX+=m_nIncrement;
					else
					{
						KillTimer(IDT_APPEARING);
						SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
						m_nAnimStatus=IDT_WAITING;
					}
					break;
				case TASKBAR_ON_RIGHT:
					if (m_nCurrentPosX>(m_nStartPosX-m_nSkinWidth))
						m_nCurrentPosX-=m_nIncrement;
					else
					{
						KillTimer(IDT_APPEARING);
						SetTimer(IDT_WAITING,m_dwTimeToLive,NULL);
						m_nAnimStatus=IDT_WAITING;
					}
					break;
			}
			SetWindowPos(NULL,m_nCurrentPosX,m_nCurrentPosY,m_nCurrentSizeX,m_nCurrentSizeY, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);
			//RedrawWindow();
			break;

		case IDT_WAITING:
                  KillTimer(IDT_WAITING);
			SetTimer(IDT_DISAPPEARING,m_dwDelayBetweenHideEvents,NULL);
			break;

		case IDT_DISAPPEARING:
			m_nAnimStatus=IDT_DISAPPEARING;
			switch(m_nTaskbarPlacement)
			{
				/*
				case TASKBAR_ON_BOTTOM:
					if (m_nCurrentPosY<m_nStartPosY)
						m_nCurrentPosY+=m_nIncrement;
					else
					{
						KillTimer(IDT_DISAPPEARING);
						Hide();
					}
					break;
				*/

				case TASKBAR_ON_BOTTOM:
					if(0 < m_nCurrentSizeY) {
						m_nCurrentPosY += m_nIncrement;
						m_nCurrentSizeY -= m_nIncrement;
					}
					else
					{
						KillTimer(IDT_DISAPPEARING);
						Hide();
					}
					break;

				case TASKBAR_ON_TOP:
					if (m_nCurrentPosY>m_nStartPosY)
						m_nCurrentPosY-=m_nIncrement;
					else
					{
						KillTimer(IDT_DISAPPEARING);
						Hide();
					}
					break;
				case TASKBAR_ON_LEFT:
					if (m_nCurrentPosX>m_nStartPosX)
						m_nCurrentPosX-=m_nIncrement;
					else
					{
						KillTimer(IDT_DISAPPEARING);
						Hide();
					}
					break;
				case TASKBAR_ON_RIGHT:
					if (m_nCurrentPosX<m_nStartPosX)
						m_nCurrentPosX+=m_nIncrement;
					else
					{
						KillTimer(IDT_DISAPPEARING);
						Hide();
					}
					break;
			}
			SetWindowPos(NULL,m_nCurrentPosX,m_nCurrentPosY,m_nCurrentSizeX,m_nCurrentSizeY, SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);
			//RedrawWindow();
			break;
	}

	CWnd::OnTimer(nIDEvent);
}

void CStartbarNotifier::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	CFont *pOldFont;
	COLORREF crTemp;
//	char *szBuffer;
		
	if (m_bMouseIsOver)
	{
		dc.SetTextColor(m_crSelectedTextColor);
		pOldFont=dc.SelectObject(&m_mySelectedFont);
	}
	else
	{
		dc.SetTextColor(m_crNormalTextColor);
		pOldFont=dc.SelectObject(&m_myNormalFont);
	}

//	szBuffer=new char[m_strCaption.GetLength()+10];
//	strcpy(szBuffer,m_strCaption);

	dc.SetBkMode(TRANSPARENT); 
//	rcClient.DeflateRect(10,20,10,20);

	if(!m_strTitle.IsEmpty())
	{
		crTemp = dc.SetTextColor(m_bMouseIsOver ? m_crSelectedTextColor : m_crTitleTextColor);
		dc.DrawText(m_strTitle, m_rcText, DT_VCENTER | DT_WORDBREAK | DT_END_ELLIPSIS);

		dc.SetTextColor(crTemp);
		m_rcText.top += 13;
		dc.DrawText(m_strCaption, m_rcText, DT_VCENTER | DT_WORDBREAK | DT_END_ELLIPSIS);
		m_rcText.top -= 13;	
	}
	else 
	{
		dc.DrawText(m_strCaption, m_rcText, DT_VCENTER | DT_WORDBREAK | DT_END_ELLIPSIS);
	}


	//	delete[] szBuffer;
	dc.SelectObject(pOldFont);
}

void CStartbarNotifier::Hide()
{
	CTaskbarNotifier::Hide();
	m_pWndParent->PostMessage(WM_NOTIFIER_HIDE, (WPARAM)this, 0L);
}

void CStartbarNotifier::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_pWndParent->PostMessage(WM_NOTIFIER_CLICKED, (WPARAM)m_ptrItemData,0);

	//NOTIFIER_ITEM *pNI = (NOTIFIER_ITEM*) m_ptrItemData;

	Disappearing();
	CWnd::OnLButtonUp(nFlags, point);
}

void CStartbarNotifier::DefaultSetting()
{
	SetSkin(IDB_SKIN_MSG);
	SetTextFont("돋움", 84,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE);
	SetTitleTextColor(RGB(120, 170, 0));
 	SetTextColor(RGB(0,0,0),RGB(0,0,200));
	SetTextRect(CRect(63,2, 295, 28));
}
