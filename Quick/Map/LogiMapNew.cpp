#include "StdAfx.h"
#include "resource.h"
#include "LogiMapNew.h"
#include "POIDataNew.h"

#define REGION_COMBO_CHANGE_TIMER	1
#define SHOW_ONE_RIDER_MAX_LEVEL	5
#define MIN_MOVE_DISTANCE			1.5		//단위 meter
#define MIN_SHOW_TRACE_POINT		50		//단위 meter
#define SHOW_SMALL_SIZE_LEVEL		8




IMPLEMENT_DYNCREATE(CLogiMapNew, CLogiMapBase)

CLogiMapNew::CLogiMapNew(void)
{
	m_dwMapStyle = 0;
	m_TraceRider.nCompany = 0;
	m_TraceRider.nRNo = 0;
	m_RClickRider.nCompany = 0;
	m_RClickRider.nRNo = 0;
	m_bTraceMode = FALSE;
	m_bTraceMapMove = FALSE;
	m_bDrawRiderMoveBoundary = TRUE;
	m_dwLastChangeRegion = GetTickCount();

	//m_bShowOneRider = FALSE;
	m_pTraceRecord = NULL;
	m_bSimulationMode = FALSE;
	m_bShowCurHasOrder = FALSE;
	m_nShowSmallSizeLevel = SHOW_SMALL_SIZE_LEVEL;
	m_nRegionChangeDisplayType = 0;
	m_pedtRegionDisplay = NULL;

	m_bShowRiderCaption = TRUE;
	m_bShowOrderCaption = TRUE;
	m_bRiderColorManual = FALSE;
	m_bPrepareImage = FALSE;
	m_bCheatMode = FALSE;
	m_bAllowRightKeyPOIDelete = FALSE;
	m_uistcMsg = NULL;
	m_bUseRearrange = FALSE;
	m_nRiderTailShowTime = 0;
	m_bDisableCarAlpha = FALSE;
}

CLogiMapNew::~CLogiMapNew(void)
{
}

BEGIN_MESSAGE_MAP(CLogiMapNew, CLogiMapBase)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CLogiMapNew, CLogiMapBase)
	//ON_EVENT_REFLECT(CLogiMapNew, 1, CLogiMapNew::OnCreateMap, VTS_I4)
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


void CLogiMapNew::OnCreateMap(long Value)
{
	if(!m_bMapCreated) 
	{
		CLogiMapBase::OnCreateMap(Value);
		MakePosOffsetInfo();
	}
}

void CLogiMapNew::MakePosOffsetInfo()
{
	ST_RIDER_POS_OFFSET_INFO p;
	p.x = 0; p.y = 0; m_arrRiderPosOffset.Add(p);	//0
	p.x = 1; p.y = 0; m_arrRiderPosOffset.Add(p);	//1
	p.x = 0; p.y = 1; m_arrRiderPosOffset.Add(p);	//2
	p.x = -1; p.y = 0; m_arrRiderPosOffset.Add(p);	//3
	p.x = 0; p.y = -1; m_arrRiderPosOffset.Add(p);	//4
	p.x = 1; p.y = 1; m_arrRiderPosOffset.Add(p);	//5
	p.x = -1; p.y = 1; m_arrRiderPosOffset.Add(p);	//6
	p.x = -1; p.y = -1; m_arrRiderPosOffset.Add(p);	//7
	p.x = 1; p.y = -1; m_arrRiderPosOffset.Add(p);	//8
	p.x = 2; p.y = 0; m_arrRiderPosOffset.Add(p);	//9
	p.x = 0; p.y = 2; m_arrRiderPosOffset.Add(p);	//10
	p.x = -2; p.y = 0; m_arrRiderPosOffset.Add(p);	//11
	p.x = 0; p.y = -2; m_arrRiderPosOffset.Add(p);	//12
	p.x = 2; p.y = -1; m_arrRiderPosOffset.Add(p);	//13
	p.x = -1; p.y = 2; m_arrRiderPosOffset.Add(p);	//14
	p.x = -2; p.y = -1; m_arrRiderPosOffset.Add(p);	//15
	p.x = 1; p.y = -2; m_arrRiderPosOffset.Add(p);	//16
	p.x = 1; p.y = 2; m_arrRiderPosOffset.Add(p);	//17
	p.x = -2; p.y = 1; m_arrRiderPosOffset.Add(p);	//18
	p.x = -1; p.y = -2; m_arrRiderPosOffset.Add(p);	//19
	p.x = 2; p.y = -1; m_arrRiderPosOffset.Add(p);	//20
	p.x = 0; p.y = -3; m_arrRiderPosOffset.Add(p);	//21
	p.x = -3; p.y = 0; m_arrRiderPosOffset.Add(p);	//22
	p.x = 0; p.y = -3; m_arrRiderPosOffset.Add(p);	//23
	p.x = 3; p.y = 0; m_arrRiderPosOffset.Add(p);	//24
}


BOOL CLogiMapNew::PrepareImage()
{
	CLogiMapBase::PrepareImage();

#ifdef _DAERI
	LoadWebImage("small.png", "small.png");
	LoadWebImage("add_med.png", "POINT_MED");

	LoadWebImage("blue_small.png", "blue_small.png");
	LoadWebImage("green_small.png", "green_small.png");
	LoadWebImage("red_small.png", "red_small.png");
	LoadWebImage("magenta_small.png", "magenta_small.png");
	LoadWebImage("yellow_small.png", "yellow_small.png");
	LoadWebImage("sky_small.png", "sky_small.png");

	LoadWebImage("blue_med.png", "blue_med.png");
	LoadWebImage("green_med.png", "green_med.png");
	LoadWebImage("yellow_med.png", "yellow_med.png");
	LoadWebImage("magenta_med.png", "magenta_med.png");
	LoadWebImage("red_med.png", "red_med.png");
	LoadWebImage("sky_med.png", "sky_med.png");

	LoadWebImage("blue_large.png", "blue_large.png");
	LoadWebImage("green_large.png", "green_large.png");
	LoadWebImage("yellow_large.png", "yellow_large.png");
	LoadWebImage("magenta_large.png", "magenta_large.png");
	LoadWebImage("red_large.png", "red_large.png");
	LoadWebImage("sky_large.png", "sky_large.png");

	LoadWebImage("bus_blue.png", "bus_blue");
	LoadWebImage("bus_green.png", "bus_green");
	LoadWebImage("bus_red.png", "bus_red");
	LoadWebImage("bus_magenta.png", "bus_magenta");
	LoadWebImage("bus_yellow.png", "bus_yellow");
	LoadWebImage("bus_sky.png", "bus_sky");
#endif

	LoadLocalImageList("bus_color.png", 40, 14);
	LoadLocalImageList("bigbike.png", 38, 27);
	LoadLocalImageList("dama.png", 42, 29);
	LoadLocalImageList("labo.png", 43, 29);
	LoadLocalImageList("truck.png", 46, 29);
	LoadLocalImageList("van.png", 43, 29);
	LoadLocalImageList("subway.png", 38, 27);
	LoadLocalImageList("parcelservice.png", 38, 27);

	LoadLocalImageList("cargo_1_0.png", 43, 29);
	LoadLocalImageList("cargo_1_4.png", 43, 29);
	LoadLocalImageList("cargo_2_5.png", 43, 29);
	LoadLocalImageList("cargo_3_5.png", 43, 29);
	LoadLocalImageList("cargo_4_5.png", 43, 29);
	LoadLocalImageList("cargo_5_0.png", 43, 29);
	LoadLocalImageList("cargo_11_0.png", 43, 29);

	LoadLocalImageList("topcar_1_0.png", 43, 29);
	LoadLocalImageList("topcar_1_4.png", 43, 29);
	LoadLocalImageList("topcar_2_5.png", 43, 29);
	LoadLocalImageList("topcar_3_5.png", 43, 29);
	LoadLocalImageList("topcar_4_5.png", 43, 29);
	LoadLocalImageList("topcar_5_0.png", 43, 29);
	LoadLocalImageList("topcar_11_0.png", 43, 29);

	LoadLocalImageList("circle_large.png", 20, 20);
	LoadLocalImageList("circle_med.png", 12, 8);
	LoadLocalImageList("circle_small.png", 20, 8);

	LoadLocalImageList("car_pickup.png", 44, 44);

	return TRUE;
}

CXPOIItem CLogiMapNew::AddPointPOI(BOOL bPosChange, CString strCaption, long nPosX, long nPosY,
						   CString strContents, CString strImageName, long nImageIndex, long nGroupID, long nIndex,
						  long nData, long nAlpha, BOOL bNoEvent)
{
	if(strImageName.IsEmpty())
		strImageName = "POINT";

	CXPOIItem poi = AddPOI(strImageName, nImageIndex, strCaption, nGroupID, nIndex, nPosX, nPosY, strContents, 
						1, 1, 1, nData, nAlpha, bNoEvent);

	if(bPosChange == TRUE)  
		MoveMap(nPosX, nPosY); 

	if(m_bAllowRightKeyPOIDelete)
		uiman.SetMessage("마우스 오른쪽키 클릭시, 포인트가 삭제됩니다.", 3000);

	return poi;
}

void CLogiMapNew::AddCarPOI(BOOL bPosChange,long nCompany, long nRNo, CString strRName, long nPosX, long nPosY, 
						CCarType &cartype, CString strCaption, CString strContents, CString strImageName, long nImageIndex, 
						COleDateTime dtUpdate)
{
	char buffer[10];
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	double fAngle = 270;
	double fDistance = 0;

	CXUtility u = GetUtility();

	if(m_bSimulationMode)
		return;

	if(dtUpdate.m_status != COleDateTime::valid)
		dtUpdate = COleDateTime::GetCurrentTime();

	IsPosUsable(nPosX, nPosY);

	CXPOIItem item = GetPOI(nCompany, nRNo);
	CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
	if(it != m_mapRiderSub.end())
	{
		if((*it).second.dtUpdate > dtUpdate || 
			(*it).second.IsSkipPos(nPosX, nPosY))
		{
			return;
		}
		else
		{
			long nPrePosX, nPrePosY;
			if((*it).second.GetPrevPos(nPrePosX, nPrePosY, 1, 300))
			{
				fAngle = u.GetAngleFromLine(GetMapPos(nPrePosX, nPrePosY), GetMapPos(nPosX, nPosY));
				//fDistance = GetCoordSys().GetRealDistance(nPrePosX, nPrePosY, nPosX, nPosY);

				fDistance = m_poiNew.GetDistanceMeter(nPrePosX, nPrePosY, nPosX, nPosY);

				if(fDistance > MIN_MOVE_DISTANCE || fDistance == 0)	//x센티미터이상이동하는경우만 각도줌
					(*it).second.fAngle = fAngle;
			}

			(*it).second.AddPos(nPosX, nPosY);
			(*it).second.cartype = cartype;
			(*it).second.dtUpdate = dtUpdate;
			(*it).second.fDistance = fDistance;
			(*it).second.fArrowDistance += fDistance;
		}
	}
	else
	{
		if(nPosX == 0)
			return;

		CRiderSubInfo rider;
		rider.nCompany = nCompany;
		rider.nRNo = nRNo;
		rider.dtUpdate = dtUpdate;
		rider.fAngle = fAngle;
		rider.fDistance = fDistance;
		rider.fArrowDistance = fDistance;
		rider.cartype = cartype;
		rider.nHavingOrder = 0;
		rider.nCompleteOrder = 0;
		rider.nAllocOrderCount = 0;
		rider.nPickupOrderCount = 0;
		rider.nChargeSum = 0;
		rider.strName = strRName;
		rider.bOtherRider = !m_ci.IsChildCompany(nCompany);
		rider.bRealtimeOtherRider = rider.bOtherRider && m_ci.IsRealtimeShareRider(nCompany);
		m_mapRiderSub.insert(CRiderSubInfoMap::value_type(std::make_pair(nCompany, nRNo), rider));
		it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
		it->second.AddPos(nPosX, nPosY);
	}

	CString strMyHint, strImageNameReal;

	it->second.strContents = strContents;
	it->second.bActive = (*it).second.dtUpdate > (dtCur -  COleDateTimeSpan(0, 0, 5, 0)) ? TRUE : FALSE;
	strMyHint = MakeHintString(it);
	strImageNameReal = !strImageName.IsEmpty() ? strImageName :	GetCarImageName(nImageIndex, it->second);

	long nAlpha = GetCarAlphaValue((*it).second);

	BOOL bShowCaption;
	if(nCompany == 0)
		bShowCaption = m_bShowOrderCaption;
	else
		bShowCaption =  m_bShowRiderCaption && GetMapLevel() <= m_nShowSmallSizeLevel;

	CXPOIItem poi = AddPOI(strImageNameReal, nImageIndex, 
	   strCaption.GetLength() > 0 ? strCaption : strRName + "(" + ltoa(nRNo, buffer, 10) + ")",
	   nCompany, nRNo, nPosX, nPosY, 
	   strMyHint, 1, bShowCaption, 1, 
	   MAKE_IDENTITY(nCompany, nRNo),
	   nAlpha);

	poi.BeginUpdate();
	poi.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")) | 
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));
	poi.EndUpdate();

	BOOL bTraceRider = m_bTraceMode && m_bTraceMapMove &&
						m_TraceRider.nCompany == nCompany && m_TraceRider.nRNo == nRNo;

	if(bPosChange || bTraceRider)
		MoveMap(nPosX, nPosY);

	if(bTraceRider)
		AddTracePos(nPosX, nPosY, COleDateTime::GetCurrentTime(), m_bTraceHasTail, bPosChange);
	else
		MakeRiderTail(it->second, nCompany, nRNo, item);
}

void CLogiMapNew::AddCarPOI(BOOL bPosChange, CRiderSubInfo &subinfo)
{
	CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(subinfo.nCompany, subinfo.nRNo));
	if(it != m_mapRiderSub.end())
	{
		int nPolygonID = it->second.GetTailPolygonID();
		it->second = subinfo;
		it->second.SetTailPloygonID(nPolygonID);
	}
	else
		m_mapRiderSub.insert(CRiderSubInfoMap::value_type(std::make_pair(subinfo.nCompany, subinfo.nRNo), subinfo));

	long nPosX, nPosY;
	subinfo.GetPrevPos(nPosX, nPosY);
	AddCarPOI(bPosChange, subinfo.nCompany, subinfo.nRNo, subinfo.strName, nPosX, nPosY, subinfo.cartype);
}


CString CLogiMapNew::GetCarImageName(long &nListIndex, CCarType &cartype, 
								  double fAngle, BOOL bActive, int nHavingOrder, 
								  BOOL bWait, COleDateTime dtAllocate, int nColorIndex, 
								  BOOL bSupportRider, BOOL bGpsError)
{
	nListIndex = -1;

#ifdef _DAERI

	CString strImage;

	if(m_bRiderColorManual)
	{
		//strImage = CLogiFunc::GetRiderColorString(nColorIndex < RC_BLUE ? RC_BLUE : nColorIndex);
		nListIndex = nColorIndex - 1;
		if(bSupportRider || m_bCheatMode)
			return "bus_color";
	}
	else
	{
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - dtAllocate;

		if(bActive)
			nListIndex = 0; //strImage = "blue";
		else if(bWait)
			nListIndex = 1; //strImage = "green";
		else if(span.GetTotalMinutes() < 10)
			nListIndex = 2; //strImage = "red";
		else if(span.GetTotalMinutes() < 20)
			nListIndex = 3; //strImage = "magenta";
		else if(span.GetTotalMinutes() < 30)
			nListIndex = 4; //strImage = "yellow";
		else if(span.GetTotalMinutes() >= 30)
			nListIndex = 5; //strImage = "sky";
		else 
			nListIndex = 0; //strImage = "green";
	}

	if(ctrlstate.GetLevel() >= m_nShowSmallSizeLevel)
		strImage = "circle_small.png";	
	else if(ctrlstate.GetLevel() >= m_nShowSmallSizeLevel - 2)
		strImage = "circle_med.png";	
	else
		strImage = "circle_large.png";

	return strImage;
#else
// 	char szCarName[][20] = {"bigbike", "bigbike", "dama", "labo", "van", "truck"};
// 	CString strImage = "";
// 
// 	if(cartype.nCarType <= 5)
// 		strImage += szCarName[cartype.nCarType];
// 	else //6, 7번도 이미지가 없어 truck으로 일괄 처리
// 		strImage += "truck";
// 	strImage += ".png";
// 
// 	if(bGpsError)
// 		nListIndex = 8;
// 	else
// 		nListIndex = min(nHavingOrder, 3) * 2;

	CString strImage = "";

	if(cartype.nCarType == CAR_AUTO || cartype.nCarType == CAR_BIGBIKE)
		strImage += "bigbike";
	else if(cartype.nCarType == CAR_DAMA)
		strImage += "dama";
	else if(cartype.nCarType == CAR_LABO)
		strImage += "labo";
	else if(cartype.nCarType == CAR_VAN)
		strImage += "van";
	else if(cartype.nCarType == CAR_TRUCK)
		strImage += "truck";
	else if(cartype.nCarType == CAR_SUBWAY)
		strImage += "subway";
	else if(cartype.nCarType == CAR_PS)
		strImage += "parcelservice";
	else if(cartype.nCarType == CAR_6VAN)
		strImage += "van";
	else if(cartype.nCarType >= CAR_1_4_TON && cartype.nCarType <= CAR_25_TON)
		strImage += "truck";
	else 
		strImage += "truck";

	strImage += ".png";

	if(bGpsError)
		nListIndex = 8;
	else
		nListIndex = min(nHavingOrder, 3) * 2;


	if(fAngle > 0 && fAngle < 180)
		nListIndex++;

	return strImage;
#endif
}

CString CLogiMapNew::GetCarImageName(long &nListIndex, CRiderSubInfo &info)
{
	return GetCarImageName(nListIndex,
					info.cartype, 
					info.fAngle, 
					info.bActive, 
					info.nHavingOrder,
					info.nState == 35 ? TRUE : FALSE,
					info.dtState,
					info.nColorIndex,
					info.bSupportRider,
					info.IsGpsSignalError());
}

CString CLogiMapNew::GetTruckSimilarTonForImage(CString strTon)
{
	double fTonList[] = {1.0, 1.4, 2.5, 3.5, 4.5, 5.0, 11.0};
	double fTon = atof(strTon);
	double fTon2 = fTonList[0];

	for(int i = 0; i < sizeof(fTonList) / sizeof(double); i++)
	{
		if(fTon == fTonList[i])
		{
			fTon2 = fTonList[i];
			break;
		}
		else if(fTon < fTonList[i])
		{
			fTon2 = fTonList[max(i-1, 0)];
			break;
		}
	}

	strTon.Format("%0.1f", fTon2);
	strTon.Replace(".", "_");
	return strTon;
}

CString CLogiMapNew::GetCarTypeImage(long nCarType)
{
	if(nCarType == 0)
		return "오토";
	else if(nCarType == 1)
		return "오토";
	else if(nCarType == 2)
		return "다마";
	else if(nCarType == 3)
		return "라보";
	else if(nCarType == 4)
		return "밴";
	else if(nCarType == 5)
		return "트럭";
	else return "오토";	
}

void CLogiMapNew::SetMapLevel(int nLevel)
{
	ctrlstate.SetLevel(nLevel);
}

void CLogiMapNew::MoveMapRider(long nCompany, long nRNo)
{
	CXPOIItem item = GetPOIIfExist(nCompany, nRNo);
	if(item) {
		CXPoint point = item.GetLonLat();
		MoveMap(point.GetX(), point.GetY());		
	}
}

void CLogiMapNew::OnChangeMapLevel()
{
	if(m_bUseRearrange)
		RearrangeDupPosPOI();
	else
		RedrawRiderCaption();
		
	RedrawPointPOI();
}

void CLogiMapNew::RedrawRiderCaption()
{
	CRiderSubInfoMap::iterator it;
	BOOL bCaption = m_bShowRiderCaption && GetMapLevel() <= m_nShowSmallSizeLevel;

	for(it = m_mapRiderSub.begin(); it != m_mapRiderSub.end(); it++)
	{
		CXPOIItem item = GetPOIIfExist((*it).second.nCompany, (*it).second.nRNo);

		if(item)
		{
			if((*it).second.nCompany > 0)
			{
				item.BeginUpdate();
				item.SetShowCaption(bCaption);
				item.EndUpdate();
			}
		}
	}
}

void CLogiMapNew::RefreshCarState()
{
	CRiderSubInfoMap::iterator it;

	for(it = m_mapRiderSub.begin(); it != m_mapRiderSub.end(); it++)
	{
		CXPOIItem item = GetPOIIfExist((*it).second.nCompany, (*it).second.nRNo);

		if(item)
		{
			if((*it).second.nCompany > 0)
			{
				item.BeginUpdate();

				long nImageIndex;
				CString strImageName = GetCarImageName(nImageIndex, (*it).second);

				item.SetImage(GetPOIImage(strImageName));
				if(nImageIndex >= 0)
					item.SetImageIndex(nImageIndex);
				item.SetAlpha(GetCarAlphaValue((*it).second));
				item.EndUpdate();
			}
		}
	}

}

void CLogiMapNew::RearrangeDupPosPOI()
{
	m_mapRiderPosDupCount.clear();

	long nCount = m_mapRiderSub.size();
	CRiderSubInfoMap::iterator it;
	CRiderPosDupCountMap::iterator it2;
	BOOL bCaption = m_bShowRiderCaption && GetMapLevel() <= m_nShowSmallSizeLevel;

	for(it = m_mapRiderSub.begin(); it != m_mapRiderSub.end(); it++)
	{
		CXPOIItem item = GetPOIIfExist((*it).second.nCompany, (*it).second.nRNo);

		if(item)
		{
			long nDupCount = 0;
			long nTmX = it->second.nTmX;
			long nTmY = it->second.nTmY;
			CXMapPos pos = GetMapPos(nTmX, nTmY);

			it2 = m_mapRiderPosDupCount.find(make_pair(nTmX, nTmY));

			if(it2 == m_mapRiderPosDupCount.end())
				m_mapRiderPosDupCount.insert(
				CRiderPosDupCountMap::value_type(make_pair(nTmX, nTmY), 0));
			else
				nDupCount = ++(it2->second);

			if(nDupCount > 0 && m_arrRiderPosOffset.GetCount() > nDupCount)
			{
				ST_RIDER_POS_OFFSET_INFO p =  m_arrRiderPosOffset.GetAt(nDupCount);
				CXPoint v = ctrlstate.LLToDP(nTmX, nTmY, 0);

				if(GetMapLevel() >= m_nShowSmallSizeLevel)
				{
					long x = v.GetX() + p.x * 5;
					long y = v.GetY() + p.y * 5;
					pos = ctrlstate.DPToLL(x, y);
				}
				else
				{
					long x = v.GetX() + p.x * (15 + (SHOW_SMALL_SIZE_LEVEL - GetMapLevel()) * 4);
					long y = v.GetY() + p.y * (15 + (SHOW_SMALL_SIZE_LEVEL - GetMapLevel()) * 4);
					pos = ctrlstate.DPToLL(x, y);
				}
			}

			item.BeginUpdate();

			if((*it).second.nCompany > 0)
			{
				long nImageIndex;
				CString strImageName = GetCarImageName(nImageIndex, (*it).second);

				item.SetImage(GetPOIImage(strImageName));
				if(nImageIndex >= 0)
					item.SetImageIndex(nImageIndex);
				item.SetLonLat(pos.GetLon(), pos.GetLat());
				item.SetShowCaption(bCaption);
				//if((*it).second.bSupportRider)
				//	item.SetTop(TRUE);
			}
			else
			{
				item.SetLonLat(pos.GetLon(), pos.GetLat());
				item.SetShowCaption(((*it).second.nState == 40) ? FALSE : m_bShowOrderCaption);
				//item.SetTop(TRUE);
			}

			item.EndUpdate();
		}
	}
}

void CLogiMapNew::RedrawPointPOI()
{
	if(m_bPrepareImage)
	{
		CXPOIGroup group = GetPOIGroup(0);
		if(group)
		{
			for(int i = 0; i < group.GetItemCount(); i++)
			{
				CXPOIItem poi = GetPOI(0, i);
				if(poi)
				{
					poi.BeginUpdate();
					poi.SetImage(GetPOIImage(GetPointImageName()));
					poi.EndUpdate();
				}
			}
		}
	}
}

CString CLogiMapNew::GetPointImageName()
{
	if(GetMapLevel() >= m_nShowSmallSizeLevel - 2)
		return "POINT_MED";	
	else
		return "POINT";
}

void CLogiMapNew::UpdateRiderOrderState(long nCompany, long nRNo, long nAllocOrderCount, long nPickupOrderCount, 
										long nHavingOrder, long nCompleteOrder, long nChargeSum, CString strHasOrderList)
{
	CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));

	if(it != m_mapRiderSub.end())
	{
		(*it).second.nHavingOrder = nHavingOrder;
		(*it).second.nCompleteOrder = nCompleteOrder;
		(*it).second.nChargeSum = nChargeSum;
		(*it).second.nAllocOrderCount = nAllocOrderCount;
		(*it).second.nPickupOrderCount = nPickupOrderCount;
		(*it).second.strHasOrderList.Empty();

		CXPOIItem poi = GetPOIIfExist(nCompany, nRNo);
		if(poi)
		{
			poi.BeginUpdate();
			poi.SetContents(MakeHintString(it));
			poi.EndUpdate();
		}
	}

}

void CLogiMapNew::UpdateRiderOrderState(long nCompany, long nRNo, long nState, long nCharge, 
									 COleDateTime dtState, CString strStart, CString strDest, BOOL bClear)
{
	CRiderSubInfoMap::iterator it;

	if(bClear)
	{
		for(it = m_mapRiderSub.begin(); it != m_mapRiderSub.end(); it++)
		{
			(*it).second.nHavingOrder = 0;
			(*it).second.nCompleteOrder = 0;
			(*it).second.nChargeSum = 0;
			(*it).second.nAllocOrderCount = 0;
			(*it).second.nPickupOrderCount = 0;
			(*it).second.strHasOrderList.Empty();
		}
	}

	it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
	if(it != m_mapRiderSub.end())
	{
		if(nState >= 11 && nState < 35)
		{
			CString strOrder;
			strOrder.Format("%s %s] %s -> %s", GetStateString(nState), 
				dtState.Format("%H:%M"), 
				strStart, strDest);
			(*it).second.strHasOrderList += strOrder + "\n";
			(*it).second.nHavingOrder++;

			if(nState == 31)
				(*it).second.nPickupOrderCount++;
			else
				(*it).second.nAllocOrderCount++;
		}
		else
		{
			(*it).second.nCompleteOrder++;
		}

		(*it).second.nChargeSum += nCharge;


		CXPOIItem poi = GetPOIIfExist(nCompany, nRNo);
		if(poi)
		{
			poi.BeginUpdate();
			poi.SetContents(MakeHintString(it));
			poi.EndUpdate();
		}
	}
}


void CLogiMapNew::DeleteAllRider()
{
	layerman.DeleteLayer(RIDER_TAIL_LAYER);
	poiman.ClearGroup();
	m_mapRiderSub.clear();
}

void CLogiMapNew::DrawRiderStartDestLine(long nCompany, long nRNo, 
									  long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY)
{
	CXLayerStyle style = layerman.FindStyle(RIDER_START_DEST_LAYER);
	if(!style)
	{
		style = layerman.NewStyle(RIDER_START_DEST_LAYER);
		style.SetPen(util.RGBAColor(100, 255, 100, 150), 3, util.GetConstToValue("PS_SOLID"));
		style.SetBrush(util.RGBAColor(100, 255, 100, 150), util.GetConstToValue("BS_SOLID"));
	}

	IsPosUsable(nStartPosX, nStartPosY);

	CXLayer layer = GetLayer(RIDER_START_DEST_LAYER);
	CXLayerPolygon poly = layer.NewPolygon(-1);
	poly.BeginUpdate();
	poly.SetClosed(FALSE);
	poly.SetCursor(1);
	poly.SetUseClipping(1);
	poly.SetStyle(style);
	poly.AddPoint(nStartPosX, nStartPosY);

	if(nDestPosX == 0)
	{
		CXPOIItem item = GetPOIIfExist(nCompany, nRNo);
		if(item) 
		{
			CXPoint point = item.GetLonLat();
			poly.AddPoint(point.GetX(), point.GetY());
		}
	}
	else
	{
		IsPosUsable(nDestPosX, nDestPosY);
		poly.AddPoint(nDestPosX, nDestPosY);
	}

	poly.EndUpdate();
}

void CLogiMapNew::ClearAllLayer(BOOL bExceptPointPOI)
{	
	if(!bExceptPointPOI)
		DeleteAllRider();

	CXRouteMan routeman = ctrlman.GetRouteMan();

	layerman.DeleteLayer(LAYER_VIA);

	poiman.DeleteGroup(LAYER_POI);
	poiman.DeleteGroup(LAYER_POI + 1);
	poiman.DeleteGroup(LAYER_POI + 2); 
	poiman.DeleteGroup(LAYER_POI + 3);
	poiman.DeleteGroup(LAYER_POI + 4);
	poiman.DeleteGroup(LAYER_POI + 5);


	/*
	CXRouteItem route = routeman.GetCurrentRoute();
	if(route.m_lpDispatch != NULL) 
		route.Clear();
	*/

	//routeman.Clear();

	if(m_bTraceMode)
		TraceMode(FALSE);
}

void CLogiMapNew::TraceMode(BOOL bTrace, long nCompany, long nRNo, BOOL bTraceHasTail, BOOL bTraceMapMove)
{
	layerman.DeleteLayer(TRACE_LAYER);
	layerman.DeleteLayer(RIDER_MOVE_BOUNDARY_LAVER);

	poiman.DeleteGroup(TRACE_RIDER_HAS_ORDER_START);
	poiman.DeleteGroup(TRACE_RIDER_HAS_ORDER_DEST);
	poiman.DeleteGroup(TRACE_POINT_POI);

	if(bTrace)
	{
		m_TraceRider.nCompany = nCompany;
		m_TraceRider.nRNo = nRNo;
		m_bTraceMapMove = bTrace;
		m_bTraceHasTail = bTraceHasTail;
		m_bTraceMapMove = bTraceMapMove;
		m_bTraceMode = TRUE;

		CreateTraceCancelBar();
		SetFocus();
	}
	else
	{
		m_bSimulationMode = FALSE;
		m_bTraceMapMove = FALSE;
		m_bTraceMode = FALSE;
		uiman.SetMessage("위치추적모드가 해제되었습니다.", 500);
		DeleteTraceCancelBar();
	}
}

void CLogiMapNew::CreateTraceCancelBar()
{
	if(!m_uistcMsg)
	{
		CXUIImage image = SetUIImage(700, "region_bar.png", 
			CRect(0, 46, 337, 68), 50, 
			GetValue("TMUIOBJ_ANCHOR_LEFT"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcMsg = AddUIStaticText(image, 701, "위치추적 모드 해제시, 여기클릭바람", 
			CRect(0, 0, 337, 22), RGB(255, 255, 255), 12, 
			"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));
	}
}

void CLogiMapNew::DeleteTraceCancelBar()
{
	if(m_uistcMsg)
	{
		CXUIImage image = m_uistcMsg.GetParent();
		m_uistcMsg.DestroyUIObj();
		image.DestroyUIObj();
		m_uistcMsg = NULL;
	}
}

/*
void CLogiMapNew::ShowOneRider(long nCompany, long nRNo, BOOL bShow)
{
	CXPOIItem item = GetPOIIfExist(nCompany, nRNo);
	if(item)
	{			
		CRiderSubInfoMap::iterator it;
		for(it = m_mapRiderSub.begin(); it != m_mapRiderSub.end(); it++)
		{
			CXPOIItem item = GetPOIIfExist(it->second.nCompany, it->second.nRNo);
			BOOL bHide = bShow && !(it->second.nCompany == nCompany && it->second.nRNo == nRNo);

			if(item)
			{
				if(!IsCarPOI(item))
					continue;

				item.BeginUpdate();
				if(bHide)
					SetPOIVisibleDec(item, MAP_MAX_LEVEL);
				else
					SetPOIVisibleAsc(item);
				item.EndUpdate();
			}

			it->second.SetRecordVisible(!bHide);
		}
	}

	//m_bShowOneRider = bShow;
}
*/

void CLogiMapNew::OnMouseDown(long Flag, long X, long Y)
{
	CLogiMapBase::OnMouseDown(Flag, X, Y);

	if(Flag == 2 && m_bAllowRightKeyPOIDelete)
		ClearAllLayer();
}


void CLogiMapNew::OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y)
{
	CLogiMapBase::OnUIMouseUp(Obj, Flag, X, Y);
/*
	CXUIObj UIObj;
	UIObj.AttachDispatch(Obj, FALSE);

	CXUIObj pObj = UIObj.GetParent();
	long pID = pObj.GetUIID();

	if(UIObj.GetUIID() == 700)
		TraceMode(FALSE);
*/

}

void CLogiMapNew::AddTracePos(long nPosX, long nPosY, COleDateTime dtLog, BOOL bHasTail, BOOL bMoveMap, BOOL bDotLine)
{
	if(m_bTraceMode)
	{
		CXUtility u = GetUtility();
		IsPosUsable(nPosX, nPosY);

		BOOL bNew;
		double fAngle = 270;
		double fDistance = 0;
		CXPOIItem item = GetPOI(m_TraceRider.nCompany, m_TraceRider.nRNo, &bNew);

		if(!bNew)
		{
			CXPoint point = item.GetLonLat();
			fAngle = u.GetAngleFromLine(GetMapPos(point.GetX(), point.GetY()), GetMapPos(nPosX, nPosY));
			//fDistance = GetCoordSys().GetRealDistance(point.GetX(), point.GetY(), nPosX, nPosY);

			fDistance = m_poiNew.GetDistanceMeter(point.GetX(), point.GetY(), nPosX, nPosY);
		}

		CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(m_TraceRider.nCompany, m_TraceRider.nRNo));

		if(it != m_mapRiderSub.end())
		{
			long nListIndex;
			item.BeginUpdate();
			item.SetLonLat(nPosX, nPosY);
			//item.SetTop(TRUE);
			item.SetImage(GetPOIImage(GetCarImageName(nListIndex, (*it).second.cartype, fAngle)));
			item.SetImageIndex(nListIndex);
			item.EndUpdate();

			if(bMoveMap)
				MoveMap(nPosX, nPosY);

			if(bHasTail)
			{
				BOOL bDrawArrow = FALSE;
				(*it).second.fArrowDistance += fDistance;
				if((*it).second.fArrowDistance > MIN_SHOW_TRACE_POINT)
				{
					(*it).second.fArrowDistance = 0;
					bDrawArrow = TRUE;
				}

				long nID = AddTracePointPOI(nPosX, nPosY, dtLog, dtLog.Format("%H시%M분"), "", FALSE);
				DrawTraceLayer(nPosX, nPosY, dtLog, nID, bDrawArrow, bDotLine);
			}

			if(m_bDrawRiderMoveBoundary)
			{
				DrawRiderMoveBoundary(TRUE);
			}
		}
	}
}

long CLogiMapNew::AddTracePointPOI(long nPosX, long nPosY, COleDateTime dtLog, 
								CString strContents, CString strImageName, BOOL bAlwaysShow)
{
	CXPOIItem item = GetPOI(TRACE_POINT_POI, -1);

	item.BeginUpdate();

	IsPosUsable(nPosX, nPosY);

	if(strImageName.IsEmpty())
		strImageName = "TRACE";

	item.SetLonLat(nPosX, nPosY);
	item.SetShowImage(1);
	item.SetShowCaption(1);
	item.SetContents(strContents);
	item.SetTextStyle(0x12);
	item.SetStyle(GetPOIStyle());
	item.SetImage(GetPOIImage(strImageName));

	static COleDateTime dtPreLog = COleDateTime::GetCurrentTime();
	static COleDateTime dtPreLog2 = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span = dtLog - dtPreLog;
	COleDateTimeSpan span2 = dtLog - dtPreLog2;

	if(abs(span2.GetTotalMinutes()) >= 10)
	{
		dtPreLog2 = dtLog;
		item.SetCaption(dtLog.Format("%H시%M분"));
		SetPOIVisibleAsc(item, 9);
	}
	else if(abs(span.GetTotalMinutes()) >= 1)
	{
		dtPreLog = dtLog;
		item.SetCaption(dtLog.Format("%H시%M분"));
		SetPOIVisibleAsc(item, 4);
	}
	else if(!bAlwaysShow)
	{
		SetPOIVisibleAsc(item, 4);
	}

	item.EndUpdate();

	return item.GetID();
}

void CLogiMapNew::DrawTraceLayer(long nPosX, long nPosY, COleDateTime dtLog, long nCurID, BOOL bDrawArrow, BOOL bDotLine)
{
	CXPOIItem item = GetPOIIfExist(TRACE_POINT_POI, nCurID -1);

	if(item)
	{
		CXLayerStyle style = layerman.FindStyle(bDotLine ? TRACE_LAYER - 1000 : TRACE_LAYER);
		if(!style)
		{
			style = layerman.NewStyle(bDotLine ? TRACE_LAYER - 1000 : TRACE_LAYER);
			style.SetPen(util.RGBAColor(0, 255, 0, 200), 5, util.GetConstToValue(bDotLine ? "PS_DOT" : "PS_SOLID"));
		}
	
		IsPosUsable(nPosX, nPosY);

/*
		CXPointList pList = util.GetPointList();
		int x = -5;
		int y = 0;

		for(int i = 0; i < 3; i++) {
			CXPoint point = util.GetPoint(x, y);
			pList.Add(point);
			x +=5;
			if (x == 5) y = x;
		}

		CXLayerFont font = layerman.NewFont(-1);
		font.AddPen(util.RGBColor(0, 0, 255), 2, util.GetConstToValue("PS_SOLID"));
		//font.AddBrush(util.RGBAColor(0, 0, 255, 100), util.GetConstToValue("BS_SOLID"));
		font.AddShape(util.GetConstToValue("TM_LAYERFONT_FILL_POLYGON"), pList);
*/
		CXPoint point = item.GetLonLat();
		CXLayer layer = GetLayer(TRACE_LAYER);
		CXLayerPolygon poly = layer.NewPolygon(-1);
		poly.BeginUpdate();
		poly.SetClosed(FALSE);
		poly.SetCursor(1);
		poly.SetUseClipping(1);
		poly.SetStyle(style);
		poly.AddPoint(point.GetX(), point.GetY());		
		poly.AddPoint(nPosX, nPosY);	
		poly.SetShowDistance(FALSE);
	//	poly.SetEndFont(font);
	//	poly.SetEndFontScale(100);
		poly.EndUpdate();
	}
}

void CLogiMapNew::DrawRiderMoveBoundary(BOOL bResizeMap)
{
/*
	if(m_bTraceMode)
	{
		CXPOIItem item = GetPOIIfExist(m_TraceRider.nCompany, m_TraceRider.nRNo);
		if(!item) return;

		CXPoint point = item.GetLonLat();
		CXObjectList list1 = poiman.GetPOIListInRadius(GetMapPos(point.GetX(), point.GetY()), TRACE_RIDER_HAS_ORDER_START, 500000);
		CXObjectList list2 = poiman.GetPOIListInRadius(GetMapPos(point.GetX(), point.GetY()), TRACE_RIDER_HAS_ORDER_DEST, 500000);
	
		int nCount = 1;
		if(list1)
			nCount += list1.GetCount();
		if(list2)
			nCount += list2.GetCount();

		if(nCount >= 2)
		{
			CXLayerStyle style = layerman.FindStyle(RIDER_MOVE_BOUNDARY_LAVER);
			if (style == NULL)
			{
				style = layerman.NewStyle(RIDER_MOVE_BOUNDARY_LAVER);
				style.SetPen(util.RGBColor(100, 255, 100), 2, util.GetConstToValue("PS_SOLID"));
				style.SetBrush(util.RGBAColor(100, 255, 100, 90), util.GetConstToValue("BS_SOLID"));
			}

			CXPoint point = item.GetLonLat();
			CXLayer layer = GetLayer(RIDER_MOVE_BOUNDARY_LAVER);
			CXLayerPolygon poly = layer.NewPolygon(-1);
			poly.BeginUpdate();
			poly.SetClosed(nCount > 2 ? TRUE : FALSE);
			poly.AddPoint(point.GetX(), point.GetY());

			for(int i = 0; i < list1.GetCount(); i++)
			{
				CXPOIItem start = list1.GetPOIItem();
				if(start)
				{
					CXPoint point = start.GetLonLat();
					poly.AddPoint(point.GetX(), point.GetY());	
				}
				list1.Next();
			}

			for(int j = 0; j < list2.GetCount(); j++)
			{
				CXPOIItem dest = list2.GetPOIItem();
				if(dest)
				{
					CXPoint point = dest.GetLonLat();
					poly.AddPoint(point.GetX(), point.GetY());	
				}
				list2.Next();
			}

			if(nCount > 2)
			{
				//RearrangePolygon(poly);
				CXPoint point = item.GetLonLat();
				poly.AddPoint(point.GetX(), point.GetY());	
			}

			poly.EndUpdate();			

			if(bResizeMap)
			{
				//GetCtrlMan().SetRectLevel(poly.GetMapRect());
				//SetMapDec();
			}
		}
	}
*/
}

void CLogiMapNew::DeleteTraceRiderHasOrder()
{
	poiman.DeleteGroup(TRACE_RIDER_HAS_ORDER_START);
	poiman.DeleteGroup(TRACE_RIDER_HAS_ORDER_DEST);
}


void CLogiMapNew::AddTraceRiderHasOrder(BOOL bShowCurHasOrder, 
									 long nTNo, long nState, CString strStart, CString strStartDong, long nStartX, long nStartY, 
									 CString strDest, CString strDestDong, long nDestX, long nDestY,
									 COleDateTime dtAllocate, COleDateTime dtPickup, COleDateTime dtFinish)
{
	CString strHint;

	if(nState == 11 || nState == 30)
	{
		strHint.Format("배차시간: %s\n도착지: %s\n", dtAllocate.Format("%H시%M분"), strDestDong);
		AddPointPOI(FALSE, strStart, nStartX, nStartY, strHint, "car_pickup.png", 1,
			TRACE_RIDER_HAS_ORDER_START, nTNo, 0, 40, TRUE);
		strHint.Format("배차시간: %s\n출발지: %s\n미픽업상태", dtAllocate.Format("%H시%M분"), strStartDong);
		AddPointPOI(FALSE, strDest, nDestX, nDestY, strHint, "car_end.png", 1,
			TRACE_RIDER_HAS_ORDER_DEST, nTNo, 0, 40, TRUE);
	}
	else if(nState == 31)
	{
		strHint.Format("배차시간: %s\n출발지: %s\n픽업완료상태", dtAllocate.Format("%H시%M분"), strStartDong);
		AddPointPOI(FALSE, strDest, nDestX, nDestY, strHint, "car_end.png", 1,
			TRACE_RIDER_HAS_ORDER_DEST, nTNo, 0, 40, TRUE);
	}
	
	if(!bShowCurHasOrder)
	{
		if(nState == 35)
		{
			strHint.Format("배차시간: %s\n도착지: %s\n", dtAllocate.Format("%H시%M분"), strDestDong);
			AddPointPOI(FALSE, CString("(완료)") + strStart, nStartX, nStartY, strHint, "car_pickup.png", 1,
				TRACE_RIDER_HAS_ORDER_START, nTNo, 0, 40, TRUE);
			strHint.Format("배차시간: %s\n출발지: %s\n", dtAllocate.Format("%H시%M분"), strStartDong);
			AddPointPOI(FALSE, CString("(완료)") + strDest, nDestX, nDestY, strHint, "car_end.png", 1,
				TRACE_RIDER_HAS_ORDER_DEST, nTNo, 0, 40, TRUE);
		}

	}

	m_bShowCurHasOrder = bShowCurHasOrder;

	if(m_bDrawRiderMoveBoundary)
		DrawRiderMoveBoundary(FALSE);
}

CString CLogiMapNew::MakeHintString(CRiderSubInfoMap::iterator &it)
{
	CString strMyHint;

	strMyHint.Format("%s\n%s\n%s\n배차:%d, 픽업:%d, 완료:%d\n총운행료:%s", 
		m_ci.GetName((*it).second.nCompany),
		(*it).second.strContents,
		((*it).second.strHasOrderList.GetLength() > 0 ? CString("\n") : CString("")) + (*it).second.strHasOrderList,
		(*it).second.nAllocOrderCount, 
		(*it).second.nPickupOrderCount, 
		(*it).second.nCompleteOrder, 
		GetMyNumberFormat((*it).second.nChargeSum));

	return strMyHint;
}

CRiderSubInfo* CLogiMapNew::GetRiderSubInfo(long nCompany, long nRNo)
{
	CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
	if(it != m_mapRiderSub.end())
		return &it->second;
	else 
		return NULL;
}

void CLogiMapNew::MakeRiderTail(CRiderSubInfo &info, long nCompany, long nRNo, CXPOIItem item)
{
	if(m_nRiderTailShowTime > 0)
	{
		CXLayer layer = GetLayer(RIDER_TAIL_LAYER);

		CXPoint point = item.GetLonLat();
		long nPosX = point.GetX();
		long nPosY = point.GetY();
		long nPrePosX, nPrePosY;


		if(info.GetTailPolygonID() >= 0)
		{
			layer.DeleteObject(info.GetTailPolygonID());
			info.SetTailPloygonID(-1);
		}

		if(info.GetPrevPos(nPrePosX, nPrePosY, 1, m_nRiderTailShowTime))
		{
			//if(GetCoordSys().GetRealDistance(nPrePosX, nPrePosY, nPosX, nPosY) < 1000)
			if(m_poiNew.GetDistanceMeter(nPrePosX, nPrePosY, nPosX, nPosY) < 1000)
			{
				CXLayerStyle style = layerman.FindStyle(RIDER_TAIL_LAYER);
				if(!style)
				{
					style = layerman.NewStyle(RIDER_TAIL_LAYER);
					style.SetPen(util.RGBAColor(0, 255, 0, 200), 3, util.GetConstToValue("PS_SOLID"));
				}

				CXLayerPolygon poly = layer.NewPolygon(-1);

				if(poly)
				{
					poly.BeginUpdate();
					poly.SetClosed(FALSE);
					poly.SetCursor(1);
					poly.SetUseClipping(1);
					poly.SetStyle(style);
					poly.AddPoint(nPosX, nPosY);	
					poly.AddPoint(nPrePosX, nPrePosY);	

					long nSteps = 2;
					long nPrePosX2 = nPrePosX;
					long nPrePosY2 = nPrePosY;

					while(nSteps < RIDER_TAIL_COUNT)
					{
						if(!info.GetPrevPos(nPrePosX, nPrePosY, nSteps++, m_nRiderTailShowTime))
							break;

						//if(GetCoordSys().GetRealDistance(nPrePosX, nPrePosY, nPrePosX2, nPrePosY2) > 1000)
						if(m_poiNew.GetDistanceMeter(nPrePosX, nPrePosY, nPrePosX2, nPrePosY2) > 1000)
							break;

						poly.AddPoint(nPrePosX, nPrePosY);
						nPrePosX2 = nPrePosX;
						nPrePosY2 = nPrePosY;
					}

					poly.SetShowDistance(FALSE);
					poly.EndUpdate();

					info.SetTailPloygonID(poly.GetID());
				}
			}
		}
	}
}

void CLogiMapNew::DeleteRiderTail(long nCompany, long nRNo)
{
	CRiderSubInfo *pInfo = GetRiderSubInfo(nCompany, nRNo);
	if(pInfo)
	{
		if(pInfo->GetTailPolygonID() >= 0)
		{
			CXLayer layer = GetLayer(RIDER_TAIL_LAYER);
			layer.DeleteObject(pInfo->GetTailPolygonID());
			pInfo->SetTailPloygonID(-1);
		}
	}
}

void CLogiMapNew::SetRiderTailShowTime(long nShowTime)
{
	m_nRiderTailShowTime = nShowTime;
	if(m_nRiderTailShowTime == 0)
		layerman.DeleteLayer(RIDER_TAIL_LAYER);
}

long CLogiMapNew::GetCarAlphaValue(CRiderSubInfo &subInfo)
{
	COleDateTimeSpan span = COleDateTime::GetCurrentTime() - subInfo.dtUpdate;
	long nTotalSeconds = span.GetTotalSeconds();
	long nAlpha = 0;

	if(!m_bDisableCarAlpha)
	{
		if(nTotalSeconds >= 12)
			nAlpha = (20 + (nTotalSeconds - 5) * 2); 
		
		if(subInfo.IsGpsSignalError())
			nAlpha = max(nAlpha, 40);
	}

	return nAlpha;
}

void CLogiMapNew::DrawRouteInfo(CXRouteInfo4 *info4, CNS_POINT_ARRAY *pPointArray)
{
	CXCtrlMan ctrlman = GetCtrlMan();
	CXControlState ctrlstate = ctrlman.GetControlState();
	CXUtility utilMng = GetUtility();

	if(info4 == NULL)
		return;

	ClearAllLayer();

	CXLayerMan layerMng = ctrlman.GetLayerMan();
	CXLayerStyle style = layerMng.FindStyle(200);

	CXLayer layer = layerMng.FindLayer(LAYER_VIA);

	if(layer)  
		layer.ClearObject();

	if (style == NULL)
	{ 
		style = layerMng.NewStyle(200);
	}       

	style.SetPen(utilMng.RGBColor(255, 0, 0), 3, utilMng.GetConstToValue(_T("PS_SOLID")));

	CXLayerPolygon polygon = layerMng.NewPolygon(LAYER_VIA, -1);
	polygon.BeginUpdate();

	int nLinkCount = info4->GetLinkCount();
	for (int i = 0; i < nLinkCount; i++)
	{
		info4->SetCurrentLinkIndex(i);
		for (int j = 0; j < info4->GetLinkNumPoint(); j++)
		{
			polygon.AddPoint(info4->GetLinkPointLon(j), info4->GetLinkPointLat(j));
		}
	}
	polygon.SetStyle(style);
	polygon.SetClosed(0);
	polygon.EndUpdate();

	long nStartGroup = LAYER_POI;

	for(int i=0; i<(int)pPointArray->GetSize(); i++)
	{   
		CPoint pt = pPointArray->GetAt(i);  

		if(i == 0) //출발지
			AddPointPOI(TRUE, "출발지", pt.x, pt.y, "", "", 0, nStartGroup + i, 1);
		else if(i == 1) //도착지
			AddPointPOI(FALSE, "도착지", pt.x, pt.y, "", "", 1, nStartGroup + i, 1);
		else //경유지
			AddPointPOI(FALSE, "경유지", pt.x, pt.y, "", "", 2, nStartGroup + i, 1);



		//CXPOIItem poi = AddPOI(strImage, nImageIndex, strCaption, nGroupID, nPOIID, nPosX, nPosY, strContents, 
		//	1, 1, 1, nData);



		//	m_wndOrderMap.AddPointPOI(bMove, CString("출발지:") + strName, nPosX, nPosY, strPos, "POINT", -1,
		//		POINT_POI, 1);

	}
}

void CLogiMapNew::DrawRouteInfo(vector<CPoint> *vec, CNS_POINT_ARRAY *pPointArray)
{
	CXCtrlMan ctrlman = GetCtrlMan();
	CXControlState ctrlstate = ctrlman.GetControlState();
	CXUtility utilMng = GetUtility();


	CXLayerMan layerMng = ctrlman.GetLayerMan();
	CXLayerStyle style = layerMng.FindStyle(200);

	CXLayer layer = layerMng.FindLayer(220);

	if(layer) 
		layer.ClearObject();

	if (style == NULL)
	{ 
		style = layerMng.NewStyle(200);
	}       

	style.SetPen(utilMng.RGBColor(255, 0, 0), 3, utilMng.GetConstToValue(_T("PS_SOLID")));

	CXLayerPolygon polygon = layerMng.NewPolygon(220, -1);
	polygon.BeginUpdate();


	for(int i=0; i<(int)vec->size(); i++) 
	{
		LONG nPosX = vec->at(i).x;
		LONG nPosY = vec->at(i).y;

		WGS84ToBessel(nPosX, nPosY);

		float x = nPosX / 1000000.0;
		float y = nPosY / 1000000.0;

		polygon.AddPoint(x * 1000000 * 0.36, y * 1000000 * 0.36);
	}


	polygon.SetStyle(style);
	polygon.SetClosed(0);
	polygon.EndUpdate();

	long nStartGroup = 63000;

	for(int i=0; i<(int)pPointArray->GetSize(); i++)
	{   
		CPoint pt = pPointArray->GetAt(i);  

		GetPOIGroup(nStartGroup + i).ClearItem();

		if(i == 0) //출발지
			AddPointPOI(TRUE, "출발지", pt.x, pt.y, "", "", 0, nStartGroup + i, 1);
		else if(i == 1) //도착지
			AddPointPOI(FALSE, "도착지", pt.x, pt.y, "", "", 1, nStartGroup + i, 1);
		else //경유지
			AddPointPOI(FALSE, "경유지", pt.x, pt.y, "", "", 2, nStartGroup + i, 1);
	}
}
