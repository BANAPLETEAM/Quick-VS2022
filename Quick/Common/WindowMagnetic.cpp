#include "StdAfx.h"
#include "WindowMagnetic.h"

#define X_MARGIN	0
#define PULL_GAP	15


CWindowMagnetic::CWindowMagnetic(void)
{
	m_pWndTo = NULL;
	m_pWndThis = NULL;
	m_nAttachType = NOT_ATTACH;
	m_nAttachPosX = -1;
	m_nAttachPosY = -1;
}

CWindowMagnetic::~CWindowMagnetic(void)
{
	AfxGetApp()->WriteProfileInt(m_strSaveName, "nAttachType", m_nAttachType);
	AfxGetApp()->WriteProfileInt(m_strSaveName, "nAttachPosX", m_nAttachPosX);
	AfxGetApp()->WriteProfileInt(m_strSaveName, "nAttachPosY", m_nAttachPosY);
}

void CWindowMagnetic::SetInfo(CWnd *pThis, CWnd *pTo, CString strSaveName)
{
	m_pWndThis = pThis;
	m_pWndTo = pTo;
	m_strSaveName = strSaveName;

	m_nAttachType = AfxGetApp()->GetProfileInt(m_strSaveName, "nAttachType", 0);
	m_nAttachPosX = AfxGetApp()->GetProfileInt(m_strSaveName, "nAttachPosX", -1);
	m_nAttachPosY = AfxGetApp()->GetProfileInt(m_strSaveName, "nAttachPosY", -1);
}

void CWindowMagnetic::AttachTo()
{
	if(!m_pWndThis || !m_pWndTo)
		return;

	CRect rc, rcTo;
	m_pWndTo->GetWindowRect(rcTo);
	m_pWndThis->GetWindowRect(rc);

	int nWidth = rc.Width();
	int nHeight = rc.Height();

	if(m_nAttachType == ATTACH_LEFT)
	{
		rc.left = rcTo.left - X_MARGIN - nWidth;
		rc.right = rc.left + nWidth;
		rc.top = rcTo.top + m_nAttachPosY;
		rc.bottom = rc.top + nHeight;

		m_pWndThis->MoveWindow(rc);
	}
	else if(m_nAttachType == ATTACH_RIGHT)
	{
		rc.left = rcTo.right + X_MARGIN;
		rc.right = rc.left + nWidth;
		rc.top = rcTo.top + m_nAttachPosY;
		rc.bottom = rc.top + nHeight;

		m_pWndThis->MoveWindow(rc);
	}
}

void CWindowMagnetic::PosChanging(WINDOWPOS* lpwndpos)
{
	if(!m_pWndThis || !m_pWndTo)
		return;

	if(lpwndpos->flags & SWP_NOSIZE)
		return;

	CRect rc, rcTo;
	m_pWndTo->GetWindowRect(rcTo);

	rc.left = lpwndpos->x;
	rc.top = lpwndpos->y;
	rc.right = rc.left + lpwndpos->cx;
	rc.bottom = rc.top + lpwndpos->cy;

	m_nAttachType = NOT_ATTACH;

	if(abs(rcTo.left - rc.right) < PULL_GAP && 
		rc.top < rcTo.bottom &&
		rc.bottom > rcTo.top)
	{
		rc.left = rcTo.left - X_MARGIN - rc.Width();
		m_nAttachType = ATTACH_LEFT;
		m_nAttachPosY = rc.top - rcTo.top;
	}

	if(abs(rcTo.right - rc.left) < PULL_GAP &&
		rc.top < rcTo.bottom &&
		rc.bottom > rcTo.top)
	{
		rc.left = rcTo.right + X_MARGIN;
		m_nAttachType = ATTACH_RIGHT;
		m_nAttachPosY = rc.top - rcTo.top;
	}

	lpwndpos->x = rc.left;
	lpwndpos->y = rc.top;
}