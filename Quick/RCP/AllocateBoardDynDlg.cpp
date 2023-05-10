// AllocateBoardDynDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateBoardDynDlg.h"
#include "RcpView.h"
#include "RiderMapDlg.h"
#include "MainFrm.h"
#include "RiderTraceMapDlg.h"
#include "AllocateBoardDlg.h"

#define OPAQUE_INIT_VALUE	80
#define OPAQUE_END_VALUE	255
#define OPAQUE_ADD_VALUE	10

CRect CAllocateBoardDynDlg::m_rcSave = CRect(0,0,0,0);


// CAllocateBoardDynDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateBoardDynDlg, CMyDialog)
CAllocateBoardDynDlg::CAllocateBoardDynDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateBoardDynDlg::IDD, pParent)
{
	m_pParentWnd = NULL;
	m_pRiderInfo = NULL;
	m_nOpaqueValue = OPAQUE_INIT_VALUE;
	m_bAlterBkColor = FALSE;
	m_pMyDlg = NULL;
	m_bFindProperRider = FALSE;
	m_bShowPosName = FALSE;
	m_bMove = FALSE;
	m_bLButtonDown = FALSE;
	m_bFirstBox = FALSE;
}

CAllocateBoardDynDlg::~CAllocateBoardDynDlg()
{
}

void CAllocateBoardDynDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_CLOSE_ALL_BTN, m_btnCloseAll);
	DDX_Control(pDX, IDC_RIDER_INFO_BTN, m_btnRiderInfo);
	DDX_Control(pDX, IDC_RIDER_POS_BTN, m_btnRiderPos);
	DDX_Control(pDX, IDC_ALLOCATE_BTN, m_btnAllocate);
}


BEGIN_MESSAGE_MAP(CAllocateBoardDynDlg, CMyDialog)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CLOSE_ALL_BTN, OnBnClickedCloseAllBtn)
	ON_BN_CLICKED(IDC_RIDER_INFO_BTN, OnBnClickedRiderInfoBtn)
	ON_BN_CLICKED(IDC_RIDER_POS_BTN, OnBnClickedRiderPosBtn)
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, OnBnClickedAllocateBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CAllocateBoardDynDlg 메시지 처리기입니다.

BOOL CAllocateBoardDynDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	m_pRPM = new CAllocateReportPaintManager;
	m_pRPM->SetShowRiderPos(m_bShowPosName);
	m_pRPM->ShowProperRiderScore(m_bFindProperRider);
	m_pRPM->SetWideColumn(TRUE);
	//m_pRPM->SetDisplayCount(m_bFindProperRider ? 4 : m_nDisplayCount + 1);
	m_pRPM->SetDisplayCount(m_bFindProperRider ? (max(4, (m_nDisplayCount + 1))) : m_nDisplayCount + 1);
	m_pRPM->SetOrderTimeType(((CAllocateBoardDlg*)m_pParentWnd)->m_chkElapsed.GetCheck());
	m_pRPM->SetOrderStateType(((CAllocateBoardDlg*)m_pParentWnd)->m_cmbState.GetCurSel());	
	m_pRPM->SetLinearType(((CAllocateBoardDlg*)m_pParentWnd)->m_bLinearType);
	m_pRPM->m_crDelayRiderBack = ((CAllocateBoardDlg*)m_pParentWnd)->m_crDelayRiderBack;
	m_pRPM->m_crOtherOrderText = ((CAllocateBoardDlg*)m_pParentWnd)->m_crOtherOrderText;
	m_pRPM->m_crOtherOrderBack = ((CAllocateBoardDlg*)m_pParentWnd)->m_crOtherOrderBack;
	//m_pRPM->SetDisplayAttendLeave(((CAllocateBoardDlg*)m_pParentWnd)->m_bChkWorkReport);


	m_wndReport.SetPaintManager(m_pRPM);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(FALSE, xtpGridNoLines);
	//m_wndReport.GetPaintManager()->SetTextFont(lfBoldFont);
	m_wndReport.SetGridColor(RGB(150, 150, 180));
	m_wndReport.ShowHeader(FALSE);

	CRect rc;
	GetWindowRect(rc);
	int nWidth = rc.Width();

	m_wndReport.AddColumn(new CXTPGridColumn(0, "", nWidth, FALSE));
	CXTPGridRecord *pRecord = new CXTPGridRecord;

	CString strTemp;
	strTemp.Format("%d / %s", m_pRiderInfo->nRNo, m_pRiderInfo->strName);

	CMyRecordItem *pRecordItem = new CMyRecordItem(strTemp);
	pRecordItem->pAllocRiderInfo = m_pRiderInfo;
	pRecord->AddItem(pRecordItem);

	if(pRecord)
		m_wndReport.AddRecord(pRecord);

	m_wndReport.Populate();

	m_pRPM->m_vecRider.push_back(m_pRiderInfo);
	m_pRPM->m_mapRider.insert(ALLOCATE_RIDER_MAP::value_type(
		std::make_pair(m_pRiderInfo->nCompany, m_pRiderInfo->nRNo), m_pRiderInfo));
	
	if(m_pRiderInfo->x < 0)
	{
		m_rcBase.left += 10;
		m_rcBase.top = m_rcBase.bottom - 100;
	}
	else
	{
		m_rcBase.left += m_pRiderInfo->x;
		m_rcBase.top += m_pRiderInfo->y;
		m_ptInit.x = m_pRiderInfo->x;
		m_ptInit.y = m_pRiderInfo->y;
	}

	rc.top = m_rcBase.top - 8;
	rc.bottom = rc.top + m_pRPM->GetRowHeight(NULL, NULL) + 5;
	rc.left = m_rcBase.left - 9;
	rc.right = rc.left + nWidth;

	CRect rcReport = rc;

	if(m_bFindProperRider)
	{
		CRect rcBtn;
		m_btnCloseAll.GetWindowRect(rcBtn);
		int nHeight = rcBtn.Height();
		rc.bottom += nHeight + 5;
/*
		if(m_rcSave.top != 0)
		{
			int nrcHeight = rc.Height();
			rc.top = m_rcSave.top;
			rc.bottom = rc.top + nrcHeight;
		}
*/
		m_rcInit = rc;
		MoveWindow(rc);
		rcReport.OffsetRect(0, 5);
		ScreenToClient(rcReport);
		rcReport.DeflateRect(2, 2, 2, 2);
		m_wndReport.MoveWindow(rcReport);

		m_btnCloseAll.GetWindowRect(rcBtn);
		ScreenToClient(rcBtn);
		rcBtn.top = rcReport.bottom + 1;
		rcBtn.bottom = rcBtn.top + nHeight;
		m_btnCloseAll.MoveWindow(rcBtn);
		m_btnCloseAll.ShowWindow(SW_SHOW);

		if(m_pRiderInfo->nCompany > 0)
		{
			m_btnRiderInfo.GetWindowRect(rcBtn);
			ScreenToClient(rcBtn);
			rcBtn.top = rcReport.bottom + 1;
			rcBtn.bottom = rcBtn.top + nHeight;
			m_btnRiderInfo.MoveWindow(rcBtn);
			m_btnRiderInfo.ShowWindow(SW_SHOW);

			m_btnRiderPos.GetWindowRect(rcBtn);
			ScreenToClient(rcBtn);
			rcBtn.top = rcReport.bottom + 1;
			rcBtn.bottom = rcBtn.top + nHeight;
			m_btnRiderPos.MoveWindow(rcBtn);
			m_btnRiderPos.ShowWindow(SW_SHOW);

			m_btnAllocate.GetWindowRect(rcBtn);
			ScreenToClient(rcBtn);
			rcBtn.top = rcReport.bottom + 1;
			rcBtn.bottom = rcBtn.top + nHeight;
			m_btnAllocate.MoveWindow(rcBtn);
			m_btnAllocate.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		MoveWindow(rc);
		ScreenToClient(rcReport);
		rcReport.DeflateRect(2, 2, 2, 2);
		m_wndReport.MoveWindow(rcReport);
	}


	RefreshList();

	MakeTransparentWindow(this->GetSafeHwnd(), OPAQUE_INIT_VALUE);
	ShowWindow(SW_SHOW);
	SetTimer(0, 10, NULL);

	if(!m_bFindProperRider)
	{
		SetTimer(1, 200, NULL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAllocateBoardDynDlg::RefreshList()
{
	OrderRecordList &order = m_pRiderInfo->bShareRider ? ((CAllocateBoardDlg*)m_pParentWnd)->m_mapShareRiderOrder :
				LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		if(it->second.nRiderCompany == m_pRiderInfo->nCompany &&
			it->second.nRNo == m_pRiderInfo->nRNo)
		{
			if(it->second.nState >= 11 && it->second.nState <= 35)
			{
				ALLOCATE_ORDER_INFO order;
				order.nCompany = it->second.nRiderCompany;
				order.nRNo = it->second.nRNo;
				order.nState = it->second.nState;
				order.strStart = it->second.strStart.c_str();
				order.strDest = it->second.strDest.c_str();
				order.nCharge = it->second.nCharge;
				order.nWayType = it->second.nWayType;
				order.dtTime = it->second.dtState;
				order.nRunType = it->second.nRunType;

				if(m_ci.IsChildCompany(it->second.nCompany))
					order.bOtherOrder = FALSE;
				else
					order.bOtherOrder = TRUE;

				m_pRPM->m_mapOrder.insert(ALLOCATE_ORDER_MAP::value_type(
					std::make_pair(it->second.nRiderCompany, it->second.nRNo), order));
			}
		}
	}

	m_wndReport.RedrawControl();
}

void CAllocateBoardDynDlg::MakeTransparentWindow(HWND hWnd, int Opaque)
{
	#define LWA_COLORKEY         0x01
	#define LWA_ALPHA            0x02
	#define WS_EX_LAYERED           0x00080000


	typedef BOOL (WINAPI *SetLayer)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	SetLayer pSetLayer = (SetLayer)GetProcAddress(hUser32, "SetLayeredWindowAttributes");
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	pSetLayer(hWnd, 0, Opaque, LWA_ALPHA);
}


void CAllocateBoardDynDlg::OnTimer(UINT nIDEvent)
{
	if(m_nOpaqueValue == OPAQUE_INIT_VALUE)
	{
		if(m_bFindProperRider)
		{
			LU->GetRcpView()->m_xList.SetFocus();
		}
	}

	if(nIDEvent == 0)
	{
		m_nOpaqueValue += OPAQUE_ADD_VALUE;
		if(m_nOpaqueValue >= (OPAQUE_END_VALUE + (OPAQUE_ADD_VALUE * (m_bFindProperRider ? 3000 : 100))))
		{
			KillTimer(0);
			KillTimer(1);
			OnClose();
		}
		else
		{
			if(m_nOpaqueValue < OPAQUE_END_VALUE)
			{
				MakeTransparentWindow(GetSafeHwnd(), min(m_nOpaqueValue, OPAQUE_END_VALUE));
			}
		}
	}
	else if(nIDEvent == 1)
	{
		m_bAlterBkColor = !m_bAlterBkColor;
		RedrawWindow();
	}

	CMyDialog::OnTimer(nIDEvent);
}

HBRUSH CAllocateBoardDynDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == this)
	{
		if(m_bAlterBkColor)
			return m_HandleManager.GetBrushObject(RGB(0, 0, 0));
		else
		{
			if(m_bFindProperRider)
				return m_HandleManager.GetBrushObject(RGB(100, 100, 255));
			else
				return m_HandleManager.GetBrushObject(RGB(255, 0, 0));
		}
	}

	return hbr;
}

void CAllocateBoardDynDlg::OnClose()
{
	m_pParentWnd->PostMessage(WM_ALLOCATE_BOARD_DYN_CLOSE, (WPARAM)m_pMyDlg, 0);
	CMyDialog::OnClose();
}

void CAllocateBoardDynDlg::OnBnClickedCloseAllBtn()
{
	m_pParentWnd->PostMessage(WM_ALLOCATE_BOARD_DYN_CLOSE, NULL, 1);
}

void CAllocateBoardDynDlg::OnBnClickedRiderInfoBtn()
{
	LU->ShowRiderInfoDlg(m_pRiderInfo->nCompany, m_pRiderInfo->nRNo);
}

void CAllocateBoardDynDlg::OnBnClickedRiderPosBtn()
{
	CREATE_MODALESS(CRiderTraceMapDlg, this);
	pDlg->m_nCompany = m_pRiderInfo->nCompany;
	pDlg->m_nRNo = m_pRiderInfo->nRNo;
	SHOW_MODALESS(CRiderTraceMapDlg, this);
}

void CAllocateBoardDynDlg::OnBnClickedAllocateBtn()
{
	LU->GetRcpView()->SendMessage(WM_RIDER_ALLOCATE,  (WPARAM)m_pRiderInfo->nRNo, (LPARAM)m_pRiderInfo->nCompany);
}

void CAllocateBoardDynDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	LU->GetRcpView()->SendMessage(WM_RIDER_ALLOCATE,  (WPARAM)m_pRiderInfo->nRNo, (LPARAM)m_pRiderInfo->nCompany);
}

void CAllocateBoardDynDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_pRiderInfo->nCompany < 0)
	{
		((CAllocateBoardDlg*)m_pParentWnd)->ShowProperRider(m_pRiderInfo->nCompany);
	}
}

void CAllocateBoardDynDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bFindProperRider)
	{		
		m_bLButtonDown = TRUE;
		SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	}

	CMyDialog::OnLButtonDown(nFlags, point);
}


void CAllocateBoardDynDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bFindProperRider)
	{
		m_bLButtonDown = FALSE;
	}

	CMyDialog::OnLButtonUp(nFlags, point);
}

void CAllocateBoardDynDlg::OnMove(int x, int y)
{
	CMyDialog::OnMove(x, y);

	if(m_bLButtonDown)
	{
		DYN_WND_MAP::iterator it;
		DYN_WND_MAP &mapDynWnd = ((CAllocateBoardDlg*)m_pParentWnd)->m_mapDynWnd;
		for(it = mapDynWnd.begin(); it != mapDynWnd.end(); it++)
		{
			CAllocateBoardDynDlg *pDlg = (CAllocateBoardDynDlg*)it->second;
			CRect rc = pDlg->m_rcInit;
			rc.OffsetRect(x - m_rcInit.left , y - m_rcInit.top);

			if(pDlg->m_bFirstBox)
			{
				((CAllocateBoardDlg*)m_pParentWnd)->m_ptMoved = 
						CPoint(pDlg->m_ptInit.x + (x - m_rcInit.left), 
								pDlg->m_ptInit.y + (y - m_rcInit.top));
			}

			if(it->second != this)
				it->second->MoveWindow(rc);

		}
	}

}
