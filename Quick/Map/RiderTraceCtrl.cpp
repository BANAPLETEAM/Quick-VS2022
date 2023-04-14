
#include "stdafx.h"
#include "resource.h"
#include "RiderTraceCtrl.h"
#include "RcpView.h"
#include "POIDataNew.h"
#include "LogiMapCns.h"

// CRiderTraceCtrl

IMPLEMENT_DYNAMIC(CRiderTraceCtrl, CLogiMapNew)

CRiderTraceCtrl::CRiderTraceCtrl()
{
	m_nCompany = 0;
	m_nRNo = 0;
	m_pRcpView = NULL;
}

CRiderTraceCtrl::~CRiderTraceCtrl()
{
}


BEGIN_MESSAGE_MAP(CRiderTraceCtrl, CLogiMapNew)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CRiderTraceCtrl, CLogiMapNew)
	//ON_EVENT_REFLECT(CRiderTraceCtrl, 48, CRiderTraceCtrl::OnPOIMouseHover, VTS_DISPATCH)
	//ON_EVENT_REFLECT(CRiderTraceCtrl, 47, CRiderTraceCtrl::OnPOIMouseLeave, VTS_DISPATCH)
	//ON_EVENT_REFLECT(CRiderTraceCtrl, 1, CRiderTraceCtrl::OnCreateMap, VTS_I4)
	//ON_EVENT_REFLECT(CRiderTraceCtrl, 4, CRiderTraceCtrl::OnMouseDown, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT_REFLECT(CLogiMapNew, 9, CLogiMapNew::OnStateChange, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT_REFLECT(CLogiMapNew, 23, CLogiMapNew::OnUIClickMap, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT_REFLECT(CLogiMapNew, 21, CLogiMapNew::OnUIMouseUp, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 10, CSampleDlg::OnClickNotifyTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 3, CSampleDlg::OnMouseDownTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 5, CSampleDlg::OnMouseMoveTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 20, CSampleDlg::OnUI_MouseDownTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 48, CSampleDlg::OnPOI_MouseHoverTalmapxctrl1, VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 47, CSampleDlg::OnPOI_MouseLeaveTalmapxctrl1, VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 41, CSampleDlg::OnPOI_MouseUpTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 43, CSampleDlg::OnPOI_ClickTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 45, CSampleDlg::OnPOI_UIClickTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 21, CSampleDlg::OnUI_MouseUpTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 4, CSampleDlg::OnMouseUpTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CRiderTraceCtrl 메시지 처리기입니다.


void CRiderTraceCtrl::OnCreateMap(long Value)
{
	if(!m_bMapCreated) 
	{
		SetNotCreateToolBar();

		CLogiMapNew::OnCreateMap(Value);
		uiman.SetShowCompass(0);
		SetRiderTailShowTime(300);

		if(m_strRightTopImage.GetLength() > 0)
		{
			LoadLocalImage(m_strRightTopImage);

			SetUIImage(501, m_strRightTopImage, 
				CRect(GetMapCX() - m_nRightTopWidth, 0, GetMapCX() , m_nRightTopHeight), 
				20, 
				GetValue("TMUIOBJ_ANCHOR_RIGHT") | 
				GetValue("TMUIOBJ_ANCHOR_TOP"), 
				GetValue("TMEVENTTYPE_MOUSEUP"));
		}

		SetTimer(0, 10000, NULL);
	}

	long nTemp = 606;
	for(int i=0; i<DISPLAY_ORDER_COUNT; i++)
	{
		long nX = GetMapCX();
		long nY = GetMapCY();

		long nBottom = nY - (24 * i);
		long nTop = nBottom - 22;

		m_uiimageOrder[i] = SetUIImage(nTemp++, "order_bar.png", 
			//CRect(GetMapCX() - 120, 55, GetMapCX(), 77), 50, 
			CRect(0, nTop, 500, nBottom), 50, 
			GetValue("TMUIOBJ_ANCHOR_LEFT") | GetValue("TMUIOBJ_ANCHOR_BOTTOM"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcOrder[i] = AddUIStaticText(m_uiimageOrder[i], nTemp++, "오더", CRect(0, 0, 500, 22), RGB(255, 255, 255), 9, 
			"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));


		m_uistcOrder[i].SetTextAlign(util.GetConstToValue("TM_TEXT_ALIGN_START"));
		m_uistcOrder[i].SetVisible(0);
		m_uiimageOrder[i].SetVisible(0);
	}
}	

void CRiderTraceCtrl::RightTopImage(CString strRightTopImage, int nWidth, int nHeight)
{
	m_strRightTopImage = strRightTopImage;
	m_nRightTopWidth = nWidth;
	m_nRightTopHeight = nHeight;
}

void CRiderTraceCtrl::RefreshOrderState()
{
	if(m_nCompany > 0 && m_pRcpView)
	{
		OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
		OrderRecordList::iterator it;
		BOOL bClear = TRUE;

		for(it = order.begin(); it != order.end(); it++)
		{
			if(it->second.nRiderCompany == m_nCompany && 
				it->second.nRNo == m_nRNo)
			{
				if(it->second.nState >= 11 && it->second.nState <= 35)
				{
					UpdateRiderOrderState(it->second.nRiderCompany, 
						it->second.nRNo, 
						it->second.nState, 
						it->second.nCharge, 
						it->second.dtState,
						it->second.strStart.c_str(),
						it->second.strDest.c_str(),
						bClear);		

					AddTraceRiderHasOrder(TRUE, 
						it->second.nTNo, it->second.nState, 
						it->second.strStart.c_str(), m_poiNew.GetDongPOI(it->second.nStartRealDongID)->GetDong(),
						it->second.nStartPosX, it->second.nStartPosY,
						it->second.strDest.c_str(), m_poiNew.GetDongPOI(it->second.nDestRealDongID)->GetDong(),
						it->second.nDestPosX, it->second.nDestPosY,
						it->second.dt3, it->second.dt4, it->second.dtFinal);


					bClear = FALSE;
				}
			}
		}

		RefreshCarState();
	}
}

void CRiderTraceCtrl::SetTraceRider(long nCompany, long nRNo, OrderRecord *pOrder, BOOL bRider)
{
	DeleteAllRider();

	m_nCompany = nCompany;
	m_nRNo = nRNo;

	if(!RefreshRiderPos())
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rider_pos_one2");
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter(nRNo);
		if(pRs.Execute(&pCmd))
		{
			if(!pRs.IsEOF())
			{
				COleDateTime dtPos;
				CRealTimeRiderPos pos;

				pRs.GetFieldValue("dtPos", dtPos);
				pRs.GetFieldValue("nPosX", pos.nPosX);
				pRs.GetFieldValue("nPosY", pos.nPosY);
				pRs.GetFieldValue("sPosName", pos.strPosName);
				pRs.GetFieldValue("bGPSUsage", pos.bUseGps);
				pRs.GetFieldValue("sName", pos.strName);
				pRs.GetFieldValue("nCarType", pos.cartype.nCarType);
				pRs.GetFieldValue("nTruckType", pos.cartype.nTruckType);
				pRs.GetFieldValue("sTon", pos.cartype.strTon);
				pRs.GetFieldValue("sHp", pos.strPhone);
				pRs.GetFieldValue("sCity", pos.strCity);

				pos.nCompany = nCompany;
				pos.nRNo = nRNo;

				LU->AddRiderPos(pos, dtPos);
				RefreshRiderPos();
			}
		}
	}

	RefreshOrderState();

	if(pOrder != NULL)
	{
		CRiderSubInfo *p = LU->GetRiderPos(pOrder->nRiderCompany, pOrder->nRNo);

		CPoint s, d, v;
		CLogiMapCns *pCNS = LU->GetLogiMapCns();
		pCNS->SetOnceShowMap(this);

		pCNS->ClearPos();

		BOOL bVia = FALSE;

		if(p != NULL)
		{
			pCNS->AddPos(p->nPosX, p->nPosY);
			pCNS->AddPos(pOrder->nDestPosX* 0.36, pOrder->nDestPosY* 0.36);
		}

		CString strStart, strDest;		
		strStart = pOrder->strStart.c_str();
		strDest = pOrder->strDest.c_str(); 

		//if(bRider)
		//{
//			pCNS->SetDebugInfo("", strStart, 0, pOrder->n, 
//				pOrder->nDestRealDongID , pOrder->nDestRealDongID, 0, m_ci.m_nCompanyCode); 
		//}
		//else
		//{

			pCNS->SetDebugInfo(strStart, strDest, pOrder->nStartRealDongID, pOrder->nStartRealDongID, 
				pOrder->nDestRealDongID , pOrder->nDestRealDongID, 0, m_ci.m_nCompanyCode); 
		//}
		
		if(!m_ci.m_bNotUseCNS)
			pCNS->GetRouteDistance(GetParent(), FALSE, bVia, FALSE, FALSE, FALSE);
		//pCNS->GetRouteDistance(this, TRUE, bViaApply,bChargeCalculate, nModifyPoiConfirmCharge);
		//m_edtCNS.SetWindowText("검색중..");
	}
}

BOOL CRiderTraceCtrl::RefreshRiderPos()
{
	CRiderSubInfoMap::iterator it;
	it = LU->m_mapRiderSub.find(std::make_pair(m_nCompany, m_nRNo));
	if(it != LU->m_mapRiderSub.end())
	{
		AddCarPOI(TRUE, it->second);
		RefreshOrderState();
		return TRUE;
	}

	return FALSE;
}

BOOL CRiderTraceCtrl::IsTraceRider(long nCompany, long nRNo)
{
	return m_nCompany == nCompany && m_nRNo == nRNo;
}
