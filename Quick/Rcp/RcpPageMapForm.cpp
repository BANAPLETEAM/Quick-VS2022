// RcpPageMapForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPageMapForm.h"
#include "RcpMapSetupDlg.h"
#include "MyMkMessenger.h"
#include "RcpView.h"
#include "POIData.h"

// CRcpPageMapForm

IMPLEMENT_DYNCREATE(CRcpPageMapForm, CMyFormView)

CRcpPageMapForm::CRcpPageMapForm()
	: CMyFormView(CRcpPageMapForm::IDD)
{
	m_nTraceCompany = 0;
	m_nTraceRNo = 0;
	m_nShowType = AfxGetApp()->GetProfileInt("RcpPageMapForm", "ShowType", 1);
	::LoadFromReg(m_setinfo);

	m_bRecvOrderDistance = FALSE;
}

CRcpPageMapForm::~CRcpPageMapForm()
{
}

void CRcpPageMapForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_MAP_CTRL, m_wndRiderMap);
	DDX_Control(pDX, IDC_ORDER_MAP_CTRL, m_wndOrderMap);
	DDX_Control(pDX, IDC_MODE_BTN, m_btnMode);
	DDX_Control(pDX, IDC_SETUP_BTN, m_btnSetup);
	DDX_Control(pDX, IDC_INC_LEVEL_BTN, m_btnIncLevel);
	DDX_Control(pDX, IDC_DEC_LEVEL_BTN, m_btnDecLevel);
	DDX_Control(pDX, IDC_MOVE_PAGE_BTN, m_btnMovePage);

	DDX_Control(pDX, IDC_TIP_STATIC, m_stcTip);
	DDX_Control(pDX, IDC_DISTANCE_STATIC, m_stcDistance);
	DDX_Control(pDX, IDC_DISTANCE_RIDER_STATIC, m_stcDistanceRider);
	DDX_Control(pDX, IDC_TIP_STATIC2, m_stcTip2);
}

BEGIN_MESSAGE_MAP(CRcpPageMapForm, CMyFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MODE_BTN, &CRcpPageMapForm::OnBnClickedModeBtn)
	ON_BN_CLICKED(IDC_SETUP_BTN, &CRcpPageMapForm::OnBnClickedSetupBtn)
	ON_MESSAGE(WM_REFRESH_RIDER_POS, OnRefreshRiderPos)
	ON_BN_CLICKED(IDC_INC_LEVEL_BTN, &CRcpPageMapForm::OnBnClickedIncLevelBtn)
	ON_BN_CLICKED(IDC_DEC_LEVEL_BTN, &CRcpPageMapForm::OnBnClickedDecLevelBtn)
	ON_BN_CLICKED(IDC_MOVE_PAGE_BTN, &CRcpPageMapForm::OnBnClickedMovePageBtn)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_USER + 6000, OnGetCnsInfo)
END_MESSAGE_MAP()


// CRcpPageMapForm 메시지 처리기입니다.

void CRcpPageMapForm::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_wndRiderMap.RightTopImage("icon_man.png", 32, 32);
	m_wndRiderMap.SetRcpView(LU->GetRcpView());
	m_wndOrderMap.RightTopImage("icon_startdest.png", 32, 32);
	m_wndOrderMap.CreateWait();

	m_wndOrderMap.SetMapLevel(AfxGetApp()->GetProfileInt("CRcpPageMapForm", "OrderMapLevel", 7));
	m_wndRiderMap.SetMapLevel(AfxGetApp()->GetProfileInt("CRcpPageMapForm", "RiderMapLevel", 7));
	m_wndOrderMap.SetRefereshAdminState();
	m_wndRiderMap.SetRefereshAdminState();

	ShowClient();

	LU->GetMessenger()->AddRecvRiderPosWnd(this);
	LU->GetMessenger()->SetRecvRiderPosMsg(TRUE);
}

void CRcpPageMapForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);
	MoveClient();
}

void CRcpPageMapForm::MoveClient()
{
	if(m_wndOrderMap.GetSafeHwnd())
	{
		CRect rc, rcBtn;
		GetClientRect(rc);
		m_btnMode.GetWindowRect(rcBtn);
		ScreenToClient(rcBtn);
		CSize btnsize(rcBtn.Width(), rcBtn.Height());

		rc.right = rc.right - btnsize.cx - 2;

		if(m_nShowType == 0)
		{
			m_wndOrderMap.MoveWindow(CRect(rc.left, rc.top, rc.left + rc.Width() / 2, rc.bottom));
			m_wndRiderMap.MoveWindow(CRect(rc.left + rc.Width() / 2 + 1, rc.top, rc.right, rc.bottom));
		}
		else if(m_nShowType == 1)
		{
			m_wndRiderMap.MoveWindow(rc);
		}
		else if(m_nShowType == 2)
		{
			m_wndOrderMap.MoveWindow(rc);
		} 
		
		rcBtn.left = rc.right + 1;
		rcBtn.right = rcBtn.left + btnsize.cx;
		rcBtn.top = rc.top;
		rcBtn.bottom = rc.top + btnsize.cy;
		m_btnMode.MoveWindow(rcBtn);
		rcBtn.OffsetRect(0, rcBtn.Height() + 2);
		m_btnSetup.MoveWindow(rcBtn);
		rcBtn.OffsetRect(0, rcBtn.Height() + 4);
		m_btnIncLevel.MoveWindow(rcBtn);
		rcBtn.OffsetRect(0, rcBtn.Height() + 2);
		m_btnDecLevel.MoveWindow(rcBtn);
		rcBtn.OffsetRect(0, rcBtn.Height() + 4);
		rcBtn.bottom += rcBtn.Height(); 
		m_btnMovePage.MoveWindow(rcBtn); 

		rcBtn.OffsetRect(0, rcBtn.Height() + 2); 
		m_stcTip.MoveWindow(rcBtn);
 
		rcBtn.OffsetRect(0, btnsize.cy - 5); 
		m_stcDistance.MoveWindow(rcBtn); 

		rcBtn.OffsetRect(0, rcBtn.Height() + 2); 
		m_stcTip2.MoveWindow(rcBtn);

		rcBtn.OffsetRect(0, btnsize.cy - 5); 
		m_stcDistanceRider.MoveWindow(rcBtn); 
	}
}

void CRcpPageMapForm::AddStartPos(BOOL bMove, long nPosX, long nPosY, CString strName, CString strPos)
{
	m_wndOrderMap.AddPointPOI(bMove, CString("출발지:") + strName, nPosX, nPosY, strPos, "POINT", -1,
					POINT_POI, 1);
}

void CRcpPageMapForm::AddDestPos(BOOL bMove, long nPosX, long nPosY, CString strName, CString strPos)
{
	m_wndOrderMap.AddPointPOI(bMove, CString("도착지:") + strName, nPosX, nPosY, strPos, "POINT", -1,
					POINT_POI, 2);
}

void CRcpPageMapForm::DeleteDest()
{
	CXPOIGroup poiGroup = m_wndOrderMap.poiman.FindGroup(POINT_POI);
	poiGroup.DeleteItem(2);
}

void CRcpPageMapForm::OnBnClickedModeBtn()
{
	m_nShowType++;
	if(m_nShowType > 2)
		m_nShowType = 0;

	ShowClient();
	MoveClient();
	AfxGetApp()->WriteProfileInt("RcpPageMapForm", "ShowType", m_nShowType);
}

void CRcpPageMapForm::ShowClient()
{
	if(m_nShowType == SHOW_TYPE_RIDER)
	{
		m_wndRiderMap.ShowWindow(SW_SHOW);
		m_wndOrderMap.ShowWindow(SW_HIDE);
	}
	else if(m_nShowType == SHOW_TYPE_ORDER)
	{
		m_wndRiderMap.ShowWindow(SW_HIDE);
		m_wndOrderMap.ShowWindow(SW_SHOW);
	}
	else 
	{
		m_wndRiderMap.ShowWindow(SW_SHOW);
		m_wndOrderMap.ShowWindow(SW_SHOW);
	}
}

void CRcpPageMapForm::OnBnClickedSetupBtn()
{
	CRcpMapSetupDlg dlg;
	if(IDOK == dlg.DoModal())
		::LoadFromReg(m_setinfo);
}

LONG CRcpPageMapForm::OnRefreshRiderPos(WPARAM wParam, LPARAM lParam)
{
	if(m_wndRiderMap.IsTraceRider(wParam, lParam))
		m_wndRiderMap.RefreshRiderPos();

	return 0;
}

void CRcpPageMapForm::SetTraceRider(long nCompany, long nRNo, OrderRecord *pOrder)
{
	m_wndRiderMap.SetTraceRider(nCompany, nRNo, pOrder);
 
	CRiderSubInfoMap::iterator it;
	it = LU->m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
	if(it != LU->m_mapRiderSub.end())
	{
		if(it->second.nPosX > 0 && it->second.nPosY > 0)
		{
			if(pOrder->nStartPosX > 0, pOrder->nStartPosY > 0)
			{
				CXUIStaticText *pText = &m_wndRiderMap.m_uistcOrder[1];  
				CXUIImage *pImage = &m_wndRiderMap.m_uiimageOrder[1];
				
				double nPosX1 = it->second.nPosX / 1000000.0;
				double nPosY1 = it->second.nPosY / 1000000.0;
				double nPosX2 = pOrder->nStartPosX * 0.36 / 1000000.0;
				double nPosY2 = pOrder->nStartPosY * 0.36 / 1000000.0;

				double fKm = CPOIData::GetDistanceKMeter(nPosX1, nPosY1, nPosX2, nPosY2);

				CString sLeft; sLeft.Format("%0.1fKm [출발지 - 기사위치](직선)", fKm);
				pText->SetCaption(sLeft); 
				pText->SetVisible(TRUE); 
				pImage->SetVisible(TRUE);	
			}

			if(pOrder->nDestPosX > 0, pOrder->nDestPosY > 0)
			{
				CXUIStaticText *pText = &m_wndRiderMap.m_uistcOrder[0];
				CXUIImage *pImage = &m_wndRiderMap.m_uiimageOrder[0];

				double nPosX1 = it->second.nPosX / 1000000.0;
				double nPosY1 = it->second.nPosY / 1000000.0;
				double nPosX2 = pOrder->nDestPosX * 0.36 / 1000000.0;
				double nPosY2 = pOrder->nDestPosY * 0.36 / 1000000.0;


				double fKm = CPOIData::GetDistanceKMeter(nPosX1, nPosY1, nPosX2, nPosY2);

				CString sLeft; sLeft.Format("%0.1fKm [도착지 - 기사위치](직선)", fKm);
				pText->SetCaption(sLeft); 
				pText->SetVisible(TRUE); 
				pImage->SetVisible(TRUE);	
			}		
		}				
	}
}

void CRcpPageMapForm::OnBnClickedIncLevelBtn()
{
	m_wndRiderMap.Map_ZoomIn();
	m_wndOrderMap.Map_ZoomIn();
}

void CRcpPageMapForm::OnBnClickedDecLevelBtn()
{
	m_wndRiderMap.Map_ZoomOut();
	m_wndOrderMap.Map_ZoomOut();
}

void CRcpPageMapForm::OnBnClickedMovePageBtn()
{
	CString strText;

	m_btnMovePage.GetWindowText(strText);

	if(strText == "확장")
	{
		((CRcpView*)GetOwner())->SetFormHeightMax();
		m_btnMovePage.SetWindowText("축소");
	}
	else 
	{
		((CRcpView*)GetOwner())->SetFormHeightRestore();
		m_btnMovePage.SetWindowText("확장");
	}
}

void CRcpPageMapForm::OnDestroy()
{
	AfxGetApp()->WriteProfileInt("CRcpPageMapForm", "OrderMapLevel", m_wndOrderMap.GetMapLevel());
	AfxGetApp()->WriteProfileInt("CRcpPageMapForm", "RiderMapLevel", m_wndRiderMap.GetMapLevel());
	CMyFormView::OnDestroy();
}

void CRcpPageMapForm::RefreshShowType(int nType)
{
	if(m_nShowType != nType)
	{
		m_nShowType = nType;
		ShowClient();
		MoveClient();
	}
}

LONG CRcpPageMapForm::OnGetCnsInfo(WPARAM wParam, LPARAM lParam)
{
	double* pdDistance = (double*)wParam;
	if(pdDistance == NULL)
		return 0;

	float fDirectDistance = (float)*pdDistance;

	CString strDistance = "";
	strDistance.Format("%0.2f",fDirectDistance ); 

	//if(m_bRecvOrderDistance == FALSE)
	//{
		m_stcDistance.SetWindowText(strDistance);
	//	SetTraceRider()

	//	m_bRecvOrderDistance = TRUE;
	//}
	//else
	//{
	//	m_stcDistanceRider.SetWindowText(strDistance);

	//}



	return 0;
}