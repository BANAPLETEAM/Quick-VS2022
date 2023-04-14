// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyListCtrl.h"
#include "RcpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_TIP_LENGTH 80


/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_pchTip = NULL;
	m_pwchTip = NULL;
	m_bToolTipCtrlCustomizeDone = FALSE;
}

CMyListCtrl::~CMyListCtrl()
{
	if(m_pchTip != NULL)
		delete m_pchTip;

	if(m_pwchTip != NULL)
		delete m_pwchTip;
}

bool CMyListCtrl::IsDraw() {
	return true;
}

bool CMyListCtrl::IsNotifyItemDraw() {
	return true;
}

bool CMyListCtrl::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) {
	return true;
}


COLORREF CMyListCtrl::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/) 
{
	ItemBaseInfo *ibi = (ItemBaseInfo*)GetItemData(nItem);

	if(!m_bIntegrated) {
		if(nSubItem < 2) {
			if(ibi->nCompany != ibi->nRiderCompany && ibi->nRiderCompany > 0 && ibi->nState != 40) {
				if(ibi->nRiderCompany == m_nDOrderCompany)
					return RGB(255, 255, 255);
				else 
					return RGB(255, 255, 255);
			}
		}
	}
	return RGB(0, 0, 0);
}

COLORREF CMyListCtrl::BkColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	ItemBaseInfo *ibi = (ItemBaseInfo*)GetItemData(nItem);

	if(!m_bIntegrated) {
		if(nSubItem < 2) {
			if(ibi->nCompany != ibi->nRiderCompany && ibi->nRiderCompany > 0 && ibi->nState != 40) {
				if(ibi->nRiderCompany == m_nDOrderCompany)
					return RGB(0, 200, 0);
				else 
					return RGB(0, 0, 255);
			}
		}
	}

	if(ibi->nState == STATE_OK &&
		nSubItem == m_nRcpTimeCol)
	{
		COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - ibi->dtRcp;
		int nDelayMinutes = (long)(dtSpan.GetTotalMinutes());
		if(nDelayMinutes >= m_nRcpTimeColor3)
			return RGB(255, 170, 170);
		else if(nDelayMinutes >= m_nRcpTimeColor2)
			return RGB(255, 255, 170);
		else if(nDelayMinutes >= m_nRcpTimeColor1)
			return RGB(170, 255, 170);
	}

	switch(ibi->nState)
	{
		case STATE_INTERNET:
			return RGB(255, 230, 230);
		case STATE_SITE:
			return RGB(230, 255, 230);
		case STATE_CARRY:
			return RGB(200, 255, 200);
		case STATE_WAIT:
			return RGB(255, 255, 200);
		case STATE_RESERVED:
			return RGB(255, 255, 230);
		case STATE_OK:
			return RGB(255, 230, 255);
		case STATE_OK_ONLY_MAN:
			return RGB(230, 255, 230);
		case STATE_ALLOCATED:
			return RGB(255,255,255);
		case STATE_FINISH:
			return RGB(255,255,255);
		case STATE_CANCELED:
			return RGB(230,230,255);
		case STATE_RECALL:
			return RGB(255, 100,100);
		case STATE_RIDER_CALL:
			return RGB(100,100, 255);
		default:
			return CLR_DEFAULT;
	}

	return RGB(255,255,255);
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrlWithCustomDraw)
	//{{AFX_MSG_MAP(CMyListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

BOOL CMyListCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect r;
	GetClientRect(r);
	CBrush brush(RGB(255,255,255));	// cyan
	pDC->FillRect(r,&brush);
	return false; // do default drawing as well
}


// Detects column resizing.
BOOL CMyListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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
int CMyListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
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
							return (long)pTI->uId;
						}
						rect.left += colwidth;
					}
				}
			}
		}
	}

	return -1;
}


BOOL CMyListCtrl::OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
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
		pToolTip->SetDelayTime(TTDT_AUTOPOP, 30000);
		pToolTip->SetDelayTime(TTDT_INITIAL, 1);
		pToolTip->SetDelayTime(TTDT_RESHOW, 1);

		m_bToolTipCtrlCustomizeDone = TRUE;
	}

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	UINT nID = (UINT)pNMHDR->idFrom;

	if( nID == 0 )	  	// Notification in NT from automatically
		return FALSE;   	// created tooltip

	int row = ((nID-1) >> 10) & 0x3fffff ;
	int col = (nID-1) & 0x3ff;

	if(row >= GetItemCount())
		return FALSE;

	CString strTip;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	TCHAR buf[MAX_TIP_LENGTH+1];
	HDITEM hdCol;
	hdCol.mask = HDI_TEXT;
	hdCol.pszText = buf;
	hdCol.cchTextMax = MAX_TIP_LENGTH; 
	pHeader->GetItem(col, &hdCol);
	CString strText = GetItemText(row, col);

	if(!strcmp(hdCol.pszText, "기사"))
	{
		ItemBaseInfo *ibi = (ItemBaseInfo*)GetItemData(row);
		int nRNo = ibi->nRNo;
		if(nRNo <= 0) 
			return FALSE;

		MAP_RIDER::iterator it;
		if(ibi->nRiderCompany == 0)
			it = m_rm.find(ibi->nCompany * 100000 + nRNo);
		else 
			it = m_rm.find(ibi->nRiderCompany * 100000 + nRNo);

		if(it != m_rm.end()) {
			ST_RIDER_WORK_STATE_INFO ri = (*it).second;

			if(m_nCompanyCode != ri.nCompany) {
				strTip += m_ci.GetName(ri.nCompany);
				strTip += "\n";					
			}	
			strTip += ri.strName;
			strTip += "(";
			strTip += GetDashPhoneNumber(ri.strPhone);
			strTip += ")";

			CString strOrder;
			//pPage->GetRiderOrder(strOrder, ri.nCompany, ri.nRNo);

			if(strOrder.GetLength() > 0) {
				strTip += "\n";
				strTip += strOrder;
			}
		}			
		else {
			CString strInfo;
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "select_rider_simple_info");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), ibi->nRiderCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			if(pRs.Execute(&pCmd)) {
				if(!pRs.IsEOF()) {
					CString strRTel, strRName, strTel, strName;
					pRs.GetFieldValue("sRTel", strRTel);
					pRs.GetFieldValue("sRName", strRName);
					pRs.GetFieldValue("sTel", strTel);
					pRs.GetFieldValue("sName", strName);
                    strTip += strName;
					strTip += "\n";
					strTip += strRName;
					strTip += "(";
					strTip += GetDashPhoneNumber(strRTel);
					strTip += ")";
				}
			}
		}
	}
	else if(!strcmp(hdCol.pszText, "출발지"))
	{
		strTip = strText;
	}
	else if(!strcmp(hdCol.pszText, "도착지"))
	{
		strTip = strText;
	}
	else if(!strcmp(hdCol.pszText, "시간"))
	{
		strTip.Format("%d분-초록-%d분-노랑-%d분-빨강", 
				m_nRcpTimeColor1, 
				m_nRcpTimeColor2, 
				m_nRcpTimeColor3);
	}

	if(col < 2)
	{
		ItemBaseInfo *ibi = (ItemBaseInfo*)GetItemData(row);
		if(ibi == NULL) return FALSE;

		if(ibi->nCompany != ibi->nRiderCompany && ibi->nRiderCompany > 0) {
			if(m_nDOrderCompany == ibi->nRiderCompany)
			{
				if(strTip.GetLength() > 0) strTip += "\n";

				if(ibi->nShareLevel <= 1) {

					if(m_ci.GetName(ibi->nCompany)) {
						strTip += "(①차공유) ";
						strTip += m_ci.GetName(ibi->nCompany);
						strTip += " 오더를 크로스 배차하였음";
					}
				}
				else {
					if(m_ci.GetName(ibi->nCompany)) {
						strTip += "(②차이상공유) ";
						strTip += m_ci.GetName(ibi->nCompany);
						strTip += " 오더를 크로스 배차하였음";
					}
				}

			}
			else {
				if(strTip.GetLength() > 0) strTip += "\n";

				if(ibi->nShareLevel <= 1) {
					if(m_ci.GetName(ibi->nRiderCompany)) {
						strTip += "(①차공유) ";
						strTip += m_ci.GetName(ibi->nRiderCompany);
						strTip += " 소속의 기사님이 크로스 배차하였음";
					}
				}
				else {
					if(m_ci.GetName(ibi->nRiderCompany)) {
						strTip += "(②차이상공유) ";
						strTip += m_ci.GetName(ibi->nRiderCompany);
						strTip += " 소속의 기사님이 크로스 배차하였음";
					}
				}
			}
		}
	}

	if(strTip.GetLength() < 1) 
		return FALSE;
	

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



