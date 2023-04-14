// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyListCtrl4.h"
#include "RcpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_TIP_LENGTH 80


/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl4

CMyListCtrl4::CMyListCtrl4()
{
	m_pchTip = NULL;
	m_pwchTip = NULL;
	m_bToolTipCtrlCustomizeDone = FALSE;
}

CMyListCtrl4::~CMyListCtrl4()
{
	if(m_pchTip != NULL)
		delete m_pchTip;

	if(m_pwchTip != NULL)
		delete m_pwchTip;
}

bool CMyListCtrl4::IsDraw() {
	return true;
}

bool CMyListCtrl4::IsNotifyItemDraw() {
	return true;
}

bool CMyListCtrl4::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) {
	return true;
}


COLORREF CMyListCtrl4::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/) 
{
	return RGB(50, 50, 255);
}

COLORREF CMyListCtrl4::BkColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	return RGB(255, 255, 255);
}


BEGIN_MESSAGE_MAP(CMyListCtrl4, CListCtrlWithCustomDraw)
	//{{AFX_MSG_MAP(CMyListCtrl4)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl4 message handlers

BOOL CMyListCtrl4::OnEraseBkgnd(CDC* pDC)
{
	CRect r;
	GetClientRect(r);
	CBrush brush(RGB(255,255,255));	// cyan
	pDC->FillRect(r,&brush);
	return false; // do default drawing as well
}


// Detects column resizing.
BOOL CMyListCtrl4::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	LPNMHEADER pNMHD = (LPNMHEADER)lParam;

	switch(pNMHD->hdr.code)
	{
		case HDN_ITEMCHANGEDA:
		case HDN_ITEMCHANGEDW:
			BOOL bRes;
			bRes = CListCtrl::OnNotify(wParam, lParam, pResult);
			//m_Header.RecalcToolRect();
			return bRes;
	}
	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}


// Detects mouse hovering and finds which row is hovering on
int CMyListCtrl4::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	CRect rect;
	GetClientRect(&rect);
	if(rect.PtInRect(point))
	{
		if(GetItemCount())
		{
			int nTopIndex = GetTopIndex();
			int nBottomIndex = nTopIndex + GetCountPerPage();
			if(nBottomIndex > GetItemCount()) nBottomIndex = GetItemCount();
			for(int nIndex = nTopIndex; nIndex <= nBottomIndex; nIndex++)
			{
				GetItemRect(nIndex, rect, LVIR_BOUNDS);
				if(rect.PtInRect(point))
				{
					// Get the number of columns
					CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
					int nColumnCount = pHeader->GetItemCount();

					// Now find the column
					for(int colnum = 0; colnum < nColumnCount; colnum++)
					{
						int colwidth = GetColumnWidth(colnum);
						if(point.x >= rect.left 
							&& point.x <= (rect.left + colwidth ))
						{
							TCHAR buf[MAX_TIP_LENGTH+1];
							HDITEM hdCol;
							hdCol.mask = HDI_TEXT;
							hdCol.pszText = buf;
							hdCol.cchTextMax = MAX_TIP_LENGTH; 
							pHeader->GetItem(colnum, &hdCol);

							RECT rectClient;
							GetClientRect(&rectClient);
							rect.right = rect.left + colwidth;

							// Make sure that the right extent does not exceed
							// the client area
							if(rect.right > rectClient.right) 
								rect.right = rectClient.right;

							pTI->hwnd = m_hWnd;
							pTI->uId = (UINT)((nIndex<<10)+(colnum&0x3ff)+1);
							pTI->lpszText = LPSTR_TEXTCALLBACK;
							pTI->rect = rect;
							return (int)pTI->uId;
						}
						rect.left += colwidth;
					}
				}
			}
		}
	}

	return -1;
}


BOOL CMyListCtrl4::OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{

	// I want to implement this in PreSubclassWindow(), but it crashes.
	if(!m_bToolTipCtrlCustomizeDone)
	{
		#if _MSC_VER >= 1300
			CToolTipCtrl* pToolTip = AfxGetModuleState()->m_thread.GetDataNA()->m_pToolTip;
		#else
			_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
			CToolTipCtrl* pToolTip = pThreadState->m_pToolTip;
		#endif

		// Set max tip width in pixel.
		// you can change delay time, tip text or background color also. enjoy yourself!
		pToolTip->SetMaxTipWidth(500);
		pToolTip->SetDelayTime(TTDT_AUTOPOP, 25000);
		pToolTip->SetDelayTime(TTDT_INITIAL, 1);
		pToolTip->SetDelayTime(TTDT_RESHOW, 1);

		m_bToolTipCtrlCustomizeDone = TRUE;
	}

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	UINT nID = (int)pNMHDR->idFrom;

	if( nID == 0 )	  	// Notification in NT from automatically
		return FALSE;   	// created tooltip

	int row = ((nID-1) >> 10) & 0x3fffff ;
	int col = (nID-1) & 0x3ff;

	CString strTip;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	TCHAR buf[MAX_TIP_LENGTH+1];
	HDITEM hdCol;
	hdCol.mask = HDI_TEXT;
	hdCol.pszText = buf;
	hdCol.cchTextMax = MAX_TIP_LENGTH; 
	pHeader->GetItem(col, &hdCol);
	CString strText = GetItemText(row, 2);

	strTip = strText;

	if(strTip.GetLength() < 1) 
		return FALSE;

/*
	TCHAR buf[MAX_TIP_LENGTH+1];
	HDITEM hdCol;
	hdCol.mask = HDI_TEXT;
	hdCol.pszText = buf;
	hdCol.cchTextMax = MAX_TIP_LENGTH; 

	int nNumCol = GetHeaderCtrl()->GetItemCount();
	for(int col=0; col<nNumCol; col++)
	{
		GetHeaderCtrl()->GetItem(col, &hdCol);
		strTip += hdCol.pszText;
		strTip += _T(": ");
		strTip += GetItemText(nItem, col);

		if(strcmp(hdCol.pszText, "기사") == 0 && atol(GetItemText(nItem, col)) > 0) {
			RIDER_MAP::iterator it;
			CRcpPage *pPage = (CRcpPage*)GetParent();
			it = pPage->m_rm.find(atol(GetItemText(nItem, col)));
			if(it != pPage->m_rm.end()) {
				RIDER_INFO ri = (*it).second;

				strTip += _T('\n');
				strTip += "기사명: ";
				strTip += ri.strName;

				strTip += _T('\n');
				strTip += "기사전화: ";
				strTip += ri.strPhone;
			}
		}

		if(col < nNumCol-1) strTip += _T('\n');
	}
*/




#ifndef _UNICODE
	if(pNMHDR->code == TTN_NEEDTEXTA)
	{
		if(m_pchTip != NULL)
			delete m_pchTip;

		m_pchTip = new TCHAR[strTip.GetLength()+1];
		lstrcpyn(m_pchTip, strTip, strTip.GetLength());
		m_pchTip[strTip.GetLength()] = 0;
		pTTTW->lpszText = (WCHAR*)m_pchTip;
	}
	else
	{
		if(m_pwchTip != NULL)
			delete m_pwchTip;

		m_pwchTip = new WCHAR[strTip.GetLength()+1];
		_mbstowcsz(m_pwchTip, strTip, strTip.GetLength());
		m_pwchTip[strTip.GetLength()] = 0; // end of text
		pTTTW->lpszText = (WCHAR*)m_pwchTip;
	}
#else
	if(pNMHDR->code == TTN_NEEDTEXTA)
	{
		if(m_pchTip != NULL)
			delete m_pchTip;

		m_pchTip = new TCHAR[strTip.GetLength()+1];
		_wcstombsz(m_pchTip, strTip, strTip.GetLength());
		m_pchTip[strTip.GetLength()] = 0; // end of text
		pTTTA->lpszText = (LPTSTR)m_pchTip;
	}
	else
	{
		if(m_pwchTip != NULL)
			delete m_pwchTip;

		m_pwchTip = new WCHAR[strTip.GetLength()+1];
		lstrcpyn(m_pwchTip, strTip, strTip.GetLength());
		m_pwchTip[strTip.GetLength()] = 0;
		pTTTA->lpszText = (LPTSTR) m_pwchTip;
	}
#endif

	*pResult = 0;

	return TRUE;    // message was handled
}
