// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.


#include "stdafx.h"
#include "resource.h"
#include "LogiMapBase.h"
#include "RegionSelectAdvancedDlg.h"
#include "POIUnit.h"
#include "SimpleMapDlg.h"
#include "GeoCoordConv.h"
#include "KingoHttp.h"

#define TALMAP_DLL_PATH		"TalMapX_1.dll"
#define TALMAP_DLL_PATH2	"c:\\SmartQ\\TalMapX_1.dll"

#define TALMAP_SR_DLL_PATH	"SmartSRX_1.0.0.88.dll"
#define TALMAP_SR_DLL_PATH2	"C:\\SmartQ\\SmartSRX_1.0.0.88.dll"

/*
//#ifdef _TEST_MAP
#define MAP_DEFAULT_PATH	"C:\\LOGISOFT\\Quick2011\\bin\\release\\Map"
#define MAP_LICENSE_PATH	"C:\\LOGISOFT\\Quick2011\\bin\\release\\Map\\KEY\\Logisoft.TML"
#define MNS_FILE_NAME		"MNS.TMT"
#else
*/


//기존Map51 임
#define MAP_DEFAULT_PATH	"http://map80.banaple.co.kr/Map82"
#define MAP_LICENSE_PATH	"http://map80.banaple.co.kr/Map82/Key/logisoft.TML"
#define MNS_FILE_NAME		"MNS.TMT"
//#endif			


/////////////////////////////////////////////////////////////////////////////
// CLogiMapBase

IMPLEMENT_DYNCREATE(CLogiMapBase, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CLogiMapBase 속성입니다.

/////////////////////////////////////////////////////////////////////////////
// CLogiMapBase 작업입니다.

CLogiMapBase::CLogiMapBase(void)
{
	maxLogicalLevel = 13 -1;
	minLogicalLevel = 0;
	bCreateLevelBar = false;
	bCreateToolBarStyle1 = false;
	bCreateToolBarStyle2 = false;
	m_pRegionSelectDlg = NULL;
	m_bPrepareImage = FALSE;
	m_bMapCreated = FALSE;
	m_bLButtonDown = FALSE;
	m_bChangeCenterPos = FALSE;
	m_sFlag = NULL;
	m_eFlag = NULL;
	m_imgCarStart = NULL;
	m_imgCarEnd = NULL;
	m_imgCarVia = NULL;
	m_bNotCreateToolBar = FALSE;
	m_bNotCreateAddressBar = FALSE;
	m_bRefreshAdminOnlyCenterPos = FALSE;

	m_strWEB_IMAGE_PATH = "";
	m_strWEB_IMAGE_PATH1 = "";
	m_bInitSRXItem = FALSE;

	InitSRXItem();
}

CLogiMapBase::~CLogiMapBase(void)
{
}


BEGIN_MESSAGE_MAP(CLogiMapBase, CWnd)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CLogiMapBase, CWnd)
	ON_EVENT_REFLECT(CLogiMapBase, 1, CLogiMapBase::OnCreateMap, VTS_I4)
	ON_EVENT_REFLECT(CLogiMapBase, 23, CLogiMapBase::OnUIClickMap, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT_REFLECT(CLogiMapBase, 21, CLogiMapBase::OnUIMouseUp, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT_REFLECT(CLogiMapBase, 9, CLogiMapBase::OnStateChange, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT_REFLECT(CLogiMapBase, 4, CLogiMapBase::OnMouseDown, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT_REFLECT(CLogiMapBase, 5, CLogiMapBase::OnMouseMove, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT_REFLECT(CLogiMapBase, 48, CLogiMapBase::OnPOIMouseHover, VTS_DISPATCH)
	//ON_EVENT_REFLECT(CLogiMapBase, 47, CLogiMapBase::OnPOIMouseLeave, VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 5, CSampleDlg::OnMouseMoveTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 10, CSampleDlg::OnClickNotifyTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 3, CSampleDlg::OnMouseDownTalmapxctrl1, VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 20, CSampleDlg::OnUI_MouseDownTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 48, CSampleDlg::OnPOI_MouseHoverTalmapxctrl1, VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 47, CSampleDlg::OnPOI_MouseLeaveTalmapxctrl1, VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 41, CSampleDlg::OnPOI_MouseUpTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 43, CSampleDlg::OnPOI_ClickTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 45, CSampleDlg::OnPOI_UIClickTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 VTS_DISPATCH)
	//ON_EVENT(CSampleDlg, IDC_MAP_CTRL, 21, CSampleDlg::OnUI_MouseUpTalmapxctrl1, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CLogiMapBase::OnCreateMap(long Value)
{
	if(m_bMapCreated) 
		return;
		
	ctrlman		= GetCtrlMan();
	mapman		= ctrlman.GetMapMan();
	thememan	= ctrlman.GetThemeMan();
	adminman	= ctrlman.GetAdminMan();
	ctrlstate	= ctrlman.GetControlState();
	poiman		= ctrlman.GetPOIMan();
	util		= GetUtility();
	imageman	= ctrlman.GetImageMan();
	layerman	= ctrlman.GetLayerMan();
	uiman		= ctrlman.GetUIMan();
	app			= GetApplication();

	CString strLicense = "";
	CString strDefaultPath = "";


	strLicense = MAP_LICENSE_PATH;
	strDefaultPath = MAP_DEFAULT_PATH;
	m_strWEB_IMAGE_PATH = WEB_IMAGE_PATH;
	m_strWEB_IMAGE_PATH1 = WEB_IMAGE_PATH;


	ctrlman.LoadLicense(_T(MAP_LICENSE_PATH));
	ctrlman.SetDefaultPath(_T(MAP_DEFAULT_PATH));

	// 맵 데이터를 지정한다.
	appPath = MAP_DEFAULT_PATH;

	mapman.SetDefaultPath(appPath + _T("/MapData"));;
	mapman.BaseManSetValue(301, 0, NULL);

	// 테마파일의 경로를 지정 한다.
	thememan.SetDefaultPath(appPath + _T("/Theme"));
	// 테마파일명을 지정한다.
if (thememan.LoadTheme(_T(MNS_FILE_NAME)) < 0) {
		MessageBox(_T("Theme를 로딩하지 못했습니다."));
	} else {
		lThemeType = 0;
	}
	// 행정동파일을 지정한다.
	CString sPMAPath;
	sPMAPath.Format(_T("%s%s%s"), appPath, _T("/Theme"), _T("/TalMap_M.TMA"));
	if (adminman.LoadAdmin(sPMAPath) != TRUE) {
		MessageBox(_T("TMA Data를 Loading 하지 못했습니다."));
	}


	// 초기화 레벨, 축척을 지정한다.
	ctrlstate.SetZoomScale(1.5);
	// 마우스 스크롤시에, 지도중심을 기준으로 확대한다.
	ctrlstate.SetState(33, 0); 

	if(!m_bNotCreateToolBar)
		CreateToolBarUI();
	
	if(!m_bNotCreateAddressBar)
		OnAddAddressBar();	

	PrepareImage();

	// OnMouse Move Event 사용을 위한 설정
	ctrlman.SetDefaultEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEMOVE")) | 
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")) | 
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEDOWN")));

	//출발점.도착점 초기화
	sFlag = NULL;
	eFlag = NULL;

	uiman.SetShowCompass(1);
	uiman.SetShowLevelBar(1);
	uiman.SetShowCenterCursor(0);
	uiman.SetShowCenterRadius(1); 
	uiman.SetShowCenterLine(1);

	PostMessage(WM_LBUTTONDOWN, 0, (200 << 16 | 200));

	m_bMapCreated = TRUE;
}

BOOL CLogiMapBase::PrepareImage()
{
	if(m_bPrepareImage)
		return TRUE;

	LoadLocalImage("point.png", "POINT");
	LoadLocalImage("point_med.png", "POINT_MED");
	LoadLocalImage("x.png", "X");
	LoadLocalImage("trace.png", "TRACE");

	m_imgCarStart = LoadLocalImageList("car_start.png", 44, 44);
	m_imgCarEnd = LoadLocalImageList("car_end.png", 44, 44);
	m_imgCarVia = LoadLocalImageList("car_via.png", 44, 44);

	return TRUE;
}

void CLogiMapBase::LoadWebImage(CString strFileName, CString strName, CString strDefaultPath)
{
	if(strName.IsEmpty())
		strName = strFileName;

	imageman.SetDefaultPath(strDefaultPath);
	if(!imageman.LoadImage(strName, strFileName))
	{
		#ifndef _DEBUG
			MessageBox(strFileName, "LoadWebImage error");
		#endif _DEBUG
	}
}

void CLogiMapBase::LoadLocalImage(CString strFileName, CString strName, CString strDefaultPath)
{
	if(strName.IsEmpty())
		strName = strFileName;

	strDefaultPath = GetModuleFullPath() + strDefaultPath;

	imageman.SetDefaultPath(strDefaultPath);
	if(!imageman.LoadImage(strName, strFileName))
	{
		#ifndef _DEBUG
			MessageBox(strFileName, "LoadLocalImage error");
		#endif _DEBUG
	}
}

CXMagicImageList CLogiMapBase::LoadLocalImageList(CString strFileName, long nWidth, long nHeight, 
									CString strName, CString strDefaultPath)
{
	if(strName.IsEmpty())
		strName = strFileName;

	strDefaultPath = GetModuleFullPath() + strDefaultPath;

	imageman.SetDefaultPath(strDefaultPath);
	CXMagicImageList imagelist = imageman.LoadImageList(strName, strFileName, nWidth, nHeight);
	if(!imagelist) 
	{
		#ifndef _DEBUG
		//	MessageBox(strFileName, "LoadLocalImageList error");
		#endif _DEBUG
	}
	return imagelist;
}

CXPOIItem CLogiMapBase::AddPOI(CString strImage, long nImageIndex, CString strCaption, UINT nGroupID, UINT nPOIID,
			long nPosX, long nPosY, CString strContents, UINT nStyleID, 
			BOOL bShowCaption, BOOL bShowImage, long nData, long nAlpha, BOOL bNoEvent)
{
	CXPOIItem poi = GetPOI(nGroupID, nPOIID); 

	IsPosUsable(nPosX, nPosY);

	poi.BeginUpdate();
	poi.SetLonLat(nPosX, nPosY);
	poi.SetShowImage(bShowImage);
	poi.SetShowCaption(bShowCaption);
	poi.SetCaption(strCaption);
	poi.SetContents(strContents);
	poi.SetTextStyle(0x12);
	poi.SetStyle(GetPOIStyle(nStyleID, nAlpha));
	poi.SetData((long*)nData);
	poi.SetImage(GetPOIImage(strImage));
	if(nImageIndex >= 0)
		poi.SetImageIndex(nImageIndex);
	poi.SetAlpha(nAlpha);
	if(bNoEvent)
		poi.DeleteEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEMOVE")) | 
							util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")) | 
							util.GetConstToValue(_T("TMEVENTTYPE_MOUSEDOWN")));
	poi.EndUpdate();


	//poi.SetImageIndex(1);
	//poi.SetImageOffset(8);
	//poi.SetTextStyle(0x12);
	//poi.SetStyle(style);
	//poi.SetAnimation(200);
	//poi.SetSyncAngle(1);
	//poi.SetAngle(90);
	//poi.SetAlpha(100);

	return poi;
}

CXMagicImage CLogiMapBase::GetPOIImage(CString strImage)
{
	CXMagicImage image = imageman.FindImage(strImage);

	if(!image)
		return imageman.FindImage("X");
	else
		return image;
}

CXPOIStyle CLogiMapBase::GetPOIStyle(long nStyleID, long nAlpha)
{
	nStyleID += (nAlpha << 16);

	CXPOIStyle style = poiman.FindStyle(nStyleID);

	if (style.m_lpDispatch == NULL) {
		style = poiman.NewStyle(nStyleID);
		style.SetGDIFont("돋움", 0, 9);
		style.SetFontColor(util.RGBColor(0, 0, 0));
		style.SetFontOutColor(util.RGBColor(255, 255, 255));
		style.SetBrush((nAlpha == 0) ? util.RGBColor(255, 255, 255) : util.RGBAColor(255, 255, 255, nAlpha), 
				GetValue("PS_SOLID"));
		style.SetPen(util.RGBColor(200, 200, 200), 1, GetValue("BS_SOLID"));
	}
	return style;
}

void CLogiMapBase::GetCenterPos(long &nPosX, long &nPosY)
{
	CXPoint posLL =  ctrlstate.GetLLCenter();
	nPosX = posLL.GetX();
	nPosY = posLL.GetY();
}

CXPOIItem CLogiMapBase::GetPOI(UINT nGroupID, UINT nPOIID, BOOL *pbNew)
{
	CXPOIGroup group = GetPOIGroup(nGroupID);
	CXPOIItem item = group.FindItem(nPOIID);
	if(item)
	{	
		if(pbNew) *pbNew = FALSE;
		return item;
	}
	else
	{
		if(pbNew) *pbNew = TRUE;
		return group.NewItem(nPOIID);
	}
}

CXPOIItem CLogiMapBase::GetPOIIfExist(UINT nGroupID, UINT nPOIID)
{
	if(!poiman)
		poiman = ctrlman.GetPOIMan();
	CXPOIGroup group = GetPOIGroup(nGroupID);
	CXPOIItem item = group.FindItem(nPOIID);
	return item;
}


CXPOIGroup CLogiMapBase::GetPOIGroup(UINT nGroupID)
{
	if(!poiman)
		poiman = ctrlman.GetPOIMan();

	CXPOIGroup group = poiman.FindGroup(nGroupID);

	if (group.m_lpDispatch == NULL) 
	{
		group = poiman.NewGroup(nGroupID);
		group.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")) | 
							util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));
	}

	return group;
}



void CLogiMapBase::CreateLevelBar()
{
	CXSize dpsize = ctrlstate.GetSizeDP();
	imageman.SetDefaultPath(GetModuleFullPath() + "\\Images\\LevelBar");


	// BackGround Image
	CXUIButton bg = mLevelBarBg = uiman.CreateUI_Button(uiman);
	bg.SetParent(uiman);
	bg.SetUIID(11);
	bg.SetImageList(_T("bg.png"), 24, 163);
	bg.SetBound(dpsize.GetCX()-38, (dpsize.GetCY()-170)/2, 28, 170);
	bg.SetAlpha(70);
	bg.SetCanClick(0);
	bg.SetAnchor(util.GetConstToValue(_T("TMUIOBJ_ANCHOR_RIGHT")) |
		util.GetConstToValue(_T("TMUIOBJ_ANCHOR_TOP")));
	bg.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")) |
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));
	// Zoom In Button
	CXUIButton btnZoomIn = uiman.CreateUI_Button(uiman);
	btnZoomIn.SetParent(bg);
	btnZoomIn.SetUIID(12);
	btnZoomIn.SetImageList(_T("btn_minus.png"), 16, 15);
	btnZoomIn.SetBound(5, 5, 16, 15);
	btnZoomIn.SetCanClick(1);
	btnZoomIn.SetCanDrag(1);
	btnZoomIn.SetDragTracker(1);
	btnZoomIn.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_CLICK"))|
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE"))|
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));

	// Zoom Out Button
	CXUIButton btnZoomOut = uiman.CreateUI_Button(uiman);
	btnZoomOut.SetParent(bg);
	btnZoomOut.SetUIID(13);
	btnZoomOut.SetImageList(_T("btn_plus.png"), 16, 15);
	btnZoomOut.SetBound(5, bg.GetItemHeight()-18, 16, 15);
	btnZoomOut.SetCanClick(1);
	btnZoomOut.SetCanDrag(1);
	btnZoomOut.SetDragTracker(1);
	btnZoomOut.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_CLICK")) |
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")) |
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));

	int UIID = 14;
	long CY = 24;
	CString imgName;
	for(int i = 12; i > -1; i--) {
		btnLevle[i] = uiman.CreateUI_Button(uiman);
		btnLevle[i].SetParent(bg);
		imgName.Format(_T("level_%d.png"), i);
		btnLevle[i].SetImageList(imgName, 20, 9);
		btnLevle[i].SetBound(3, CY, 20, 9);
		btnLevle[i].SetCanClick(1);
		btnLevle[i].SetCanDrag(1);
		btnLevle[i].SetDragTracker(1);
		btnLevle[i].SetImageAutoChange(0);
		btnLevle[i].SetItemIndex(1);
		btnLevle[i].AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")) |
			util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));
		CY = CY + 9;
		UIID++;

	}
	// 현재 Level 표출
	MapLevel_Master(ctrlstate.GetLevel());
}

void CLogiMapBase::ShowLandMakkSymbol(long value)
{
	mapman.SetShowLandMarkSymbol(value); // value 1: 표출, value 0 : 표출하지 않음.
}

void CLogiMapBase::MapLevel_Master(long level)
{
	if(mLevelBarBg == NULL) return;
	// Image Index 설정 0~3
	int SetEnabled = 0;
	int SetDisable = 1;

	for (int i=0; i < 13; i++) {
		if (level == i) btnLevle[i].SetItemIndex(SetEnabled);
		else btnLevle[i].SetItemIndex(SetDisable);
	}
}

void CLogiMapBase::CreateToolBarUI()
{
	if (bCreateToolBarStyle1) {
		bPanel.DestroyUIObj();
		bCreateToolBarStyle1 = false;
		return;
	} else
		bCreateToolBarStyle1 = true;

	CXSize dpsize = ctrlstate.GetSizeDP();
	imageman.SetDefaultPath(GetModuleFullPath() + "\\Images");
	long width_px = dpsize.GetCX()/2 - 250;

	bPanel = uiman.CreateUI_Panel(uiman);
	bPanel.SetParent(uiman);
	bPanel.SetUIID(200);
	bPanel.SetAlpha(80);
	bPanel.SetBound(width_px, dpsize.GetCY()-50, 530, 35);
	bPanel.SetCanDrag(1);
	bPanel.SetCanClick(1);
	bPanel.SetAnchor(util.GetConstToValue(_T("TMUIOBJ_ANCHOR_BOTTOM")) | util.GetConstToValue(_T("TMUIOBJ_ANCHOR_HCENTER")));
	bPanel.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE"))|
		util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER")));

	width_px = 0;
	long UIID = 201;
	CXUIButton MyToolBar1[21];
	CString url;
	for (int i=1; i< 21; i++) {
		MyToolBar1[i] = uiman.CreateUI_Button(uiman);
		MyToolBar1[i].SetParent(bPanel);
		MyToolBar1[i].SetUIID(UIID);
		if(i ==1) MyToolBar1[i].SetHint(_T("축소"));
		else if (i == 2) MyToolBar1[i].SetHint(_T("확대"));
		else if (i == 3) MyToolBar1[i].SetHint(_T("회전"));
		else if (i == 4) MyToolBar1[i].SetHint(_T("이전화면"));
		else if (i == 5) MyToolBar1[i].SetHint(_T("다음화면"));
		else if (i == 6) MyToolBar1[i].SetHint(_T("조망보기"));
		else if (i == 7) MyToolBar1[i].SetHint(_T("3D 건물보기"));
		else if (i == 8) MyToolBar1[i].SetHint(_T("텍스트보기"));
		else if (i == 9) MyToolBar1[i].SetHint(_T("클리보드 저장"));
		else if (i == 10) MyToolBar1[i].SetHint(_T("지도화면 저장"));
		else if (i == 11) MyToolBar1[i].SetHint(_T("메일 전송"));
		else if (i == 12) MyToolBar1[i].SetHint(_T("프린트"));
		else if (i == 13) MyToolBar1[i].SetHint(_T("폴리곤 그리기"));
		else if (i == 14) MyToolBar1[i].SetHint(_T("폴리라인 그리기"));
		else if (i == 15) MyToolBar1[i].SetHint(_T("객체 지우기"));
		else if (i == 16) MyToolBar1[i].SetHint(_T("반경 그리기"));
		else if (i == 17) MyToolBar1[i].SetHint(_T("거리측정"));
		else if (i == 18) MyToolBar1[i].SetHint(_T("면적측정"));
		else if (i == 19) MyToolBar1[i].SetHint(_T("객체삭제"));
		else if (i == 20) MyToolBar1[i].SetHint(_T("객체편집"));
		else if (i == 21) MyToolBar1[i].SetHint(_T("테마보기"));

		url.Format(_T("map_btn_%d.png"), i);
		MyToolBar1[i].SetImageList(url, 21, 21);
		MyToolBar1[i].SetBound(width_px, 5, 21, 21);
		MyToolBar1[i].SetAlpha(0);
		MyToolBar1[i].SetCanClick(1);
		MyToolBar1[i].SetCanDrag(0);
		MyToolBar1[i].SetDragTracker(1);
		MyToolBar1[i].AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")) |
			util.GetConstToValue(_T("TMEVENTTYPE_MOUSEENTER"))|
			util.GetConstToValue(_T("TMEVENTTYPE_MOUSELEAVE")));

		width_px = width_px + 25;
		UIID++;
	}

}

void CLogiMapBase::OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y)
{
	CXUIObj UIObj;
	UIObj.AttachDispatch(Obj, FALSE);

	CXUIObj pObj = UIObj.GetParent();
	long pID = pObj.GetUIID();

	GetParent()->PostMessage(WM_UI_MOUSE_UP, (WPARAM)UIObj.GetUIID(), (LPARAM)Flag);

	if (pObj.GetUIID() == 11) {
		switch (UIObj.GetUIID()) {
			case 12: Map_ZoomOut();	break;
			case 13: Map_ZoomIn();	break;
			case 14: MapLevel_Master(12);	break;
			case 15: MapLevel_Master(11);	break;
			case 16: MapLevel_Master(10);	break;
			case 17: MapLevel_Master(9);	break;
			case 18: MapLevel_Master(8);	break;
			case 19: MapLevel_Master(7);	break;
			case 20: MapLevel_Master(6);	break;
			case 21: MapLevel_Master(5);	break;
			case 22: MapLevel_Master(4);	break;
			case 23: MapLevel_Master(3);	break;
			case 24: MapLevel_Master(2);	break;
			case 25: MapLevel_Master(1);	break;
			case 26: MapLevel_Master(0);	break;
		}
	} else if (pObj.GetUIID() == 101) {
		switch (UIObj.GetUIID()) {
			case 12: Map_ZoomOut();	break;
			case 13: Map_ZoomIn();	break;
			case 14: MapLevel_Master(12);	break;
			case 15: MapLevel_Master(11);	break;
			case 16: MapLevel_Master(10);	break;
			case 17: MapLevel_Master(9);	break;
			case 18: MapLevel_Master(8);	break;
			case 19: MapLevel_Master(7);	break;
			case 20: MapLevel_Master(6);	break;
			case 21: MapLevel_Master(5);	break;
			case 22: MapLevel_Master(4);	break;
			case 23: MapLevel_Master(3);	break;
			case 24: MapLevel_Master(2);	break;
			case 25: MapLevel_Master(1);	break;
			case 26: MapLevel_Master(0);	break;
		}
	} else if (pObj.GetUIID() == 200) {
		switch (UIObj.GetUIID()) {
			case 201: Map_ZoomOut();break;
			case 202: Map_ZoomIn();	break;
			case 203: OnMapRotaion();	break;
			case 204: OnSmHistoryprev();break;
			case 205: OnSmHistorynext();break;
			case 206: OnSmBirdview();	break;
			case 207: OnSm3Dview();		break;
			case 208: OnSmTextView();	break;
			case 209: OnSmClipboard();	break;
			case 210: OnSmImagesave();break;
			case 211: break;
			case 212: break;
			case 213: OnPolygon();break;
			case 214: OnPolyline();break;
			case 215: {
				CXLayerMan layerman = ctrlman.GetLayerMan();
				CXLayer layer =  layerman.FindLayer(1);
				if (layer.m_lpDispatch) layer.ClearObject();
					  };break;
			case 216: OnSmMakeCircle();break;
			case 217: OnCheckDistance();break;
			case 218: OnCheckArea();break;
			case 219: OnRemovePolygon();break;
			case 220: OnObjectModify();break;
			case 221: break;

		}
	} else if (pObj.GetUIID() == 300) {
		switch (UIObj.GetUIID()) {
			case 301: Map_ZoomOut();break;
			case 302: Map_ZoomIn();	break;
			case 303: OnMapRotaion();	break;
			case 304: OnSmHistoryprev();break;
			case 305: OnSmHistorynext();break;
			case 306: OnSmBirdview();	break;
			case 307: OnSm3Dview();		break;
			case 308: OnSmTextView();	break;
			case 309: OnSmClipboard();	break;
			case 310: OnSmImagesave();break;
			case 311: break;
			case 312: break;
			case 313: OnPolygon();break;
			case 314: OnPolyline();break;
			case 315: {
				CXLayerMan layerman = ctrlman.GetLayerMan();
				CXLayer layer =  layerman.FindLayer(1);
				if (layer.m_lpDispatch) layer.ClearObject();
					  };break;
			case 316: OnSmMakeCircle();break;
			case 317: OnCheckDistance();break;
			case 318: OnCheckArea();break;
			case 319: OnRemovePolygon();break;
			case 320: OnObjectModify();break;
			case 321: break;

		}
		MyToolBar2[UIObj.GetUIID()-300].SetItemIndex(3);
	} else if (pObj.GetUIID() == 400) {
		CString msg;
		msg.Format(_T("[%s] OnUI_MouseUp(%d, %d, %d)"), UIObj.GetName(), Flag, X, Y);
		if(stcMsgArea) stcMsgArea.SetCaption(msg);
	} 
	else 
	{
		if(UIObj.GetUIID() == 500)
			ShowRegionSelectDlg();
	}
	
}

void CLogiMapBase::OnMouseDown(long Flag, long X, long Y)
{
}

void CLogiMapBase::ShowRegionSelectDlg()
{
	if(!m_pRegionSelectDlg)
	{
		m_pRegionSelectDlg = new CRegionSelectAdvancedDlg(this);
		m_pRegionSelectDlg->m_pMap = this;
		m_pRegionSelectDlg->Create(IDD_REGION_SELECT_ADVANCED_DLG, this);

		CRect rc, rc2;
		GetParent()->GetClientRect(rc);
		ClientToScreen(rc);
		m_pRegionSelectDlg->GetWindowRect(rc2);
		rc2.OffsetRect(rc.left - rc2.left, rc.top - rc2.top + 22);
		m_pRegionSelectDlg->MoveWindow(rc2);
	}
	m_pRegionSelectDlg->ShowWindow(SW_SHOW);

	long nPosX, nPosY;
	GetCenterPos(nPosX, nPosY);
	RefreshAdminInfo(TRUE, FALSE, nPosX, nPosY);
}

void CLogiMapBase::OnUIClickMap(LPDISPATCH Obj, long Flag, long X, long Y)
{
	CXUIObj obj;
	obj.AttachDispatch(Obj, FALSE);

	CXUIObj pObj = obj.GetParent();
	if (pObj.GetUIID() == 400) {
		CString msg;
		msg.Format(_T("[%s] OnUI_Click(%d, %d, %d)"), obj.GetName(), Flag, X, Y);
		if (stcMsgArea) stcMsgArea.SetCaption(msg);
	}

	if (obj.GetUIID() == 12) {
		Map_ZoomIn();
	}
	if (obj.GetUIID() == 13) {
		Map_ZoomOut();
	}
}

void CLogiMapBase::OnStateChange(long Code, long Value1, long Value2)
{
	if(m_bMapCreated)
	{
		if (Code == util.GetConstToValue(_T("TMCHECKCONFIG_LEVEL"))) 
		{
			// 현재 Level 표출
			MapLevel_Master(ctrlstate.GetLevel());
			OnChangeMapLevel(); 
		} 
		else if (Code == util.GetConstToValue(_T("TMCHECKCONFIG_CENTERLONLAT"))) 
		{
			// 지도 중심 좌표 변경시 동작 코드
			m_bChangeCenterPos = TRUE;
			long nPosX, nPosY;
			GetCenterPos(nPosX, nPosY);
			RefreshAdminInfo(0, 0, nPosX, nPosY);
		} 
		else if (Code == util.GetConstToValue(_T("TMCHECKCONFIG_ROTATION"))) 
		{
			// 지도 회전 변경시 동작 코드
		}
	}
}

void CLogiMapBase::Map_ZoomIn()
{
	if (ctrlstate.GetLevel() > minLogicalLevel) {
		ctrlstate.SetLevel(ctrlstate.GetLevel() -1);
	}
}
//------------------------------------------------------------------------------
//  지도 축소
//------------------------------------------------------------------------------
void CLogiMapBase::Map_ZoomOut()
{
	if (ctrlstate.GetLevel() < maxLogicalLevel) {
		ctrlstate.SetLevel(ctrlstate.GetLevel() +1);
	}
}

void CLogiMapBase::OnMapRotaion()
{
	ctrlman.SetMapRotation(1);
}


//------------------------------------------------------------------------------
//  History Prev
//------------------------------------------------------------------------------
void CLogiMapBase::OnSmHistoryprev()
{
	CXMasterControlState ctrlstate =  ctrlman.GetControlState();
	ctrlstate.HistoryPrev();
}
//------------------------------------------------------------------------------
//  History Next
//------------------------------------------------------------------------------
void CLogiMapBase::OnSmHistorynext()
{
	CXMasterControlState ctrlstate =  ctrlman.GetControlState();
	ctrlstate.HistoryNext();
}
//------------------------------------------------------------------------------
//  텍스트 보기
//------------------------------------------------------------------------------
void CLogiMapBase::OnSmTextView()
{
	if (mapman.GetVisible() == 1) {
		mapman.SetVisible(2);
	} else if (mapman.GetVisible() == 2) {
		mapman.SetVisible(3);
	} else {
		mapman.SetVisible(1);
	}
}
//------------------------------------------------------------------------------
//  Layer Circle 그리기
//------------------------------------------------------------------------------
void CLogiMapBase::OnSmMakeCircle()
{
	uiman.SetMessage(_T("마우스 오른쪽을 클릭하면 종료됩니다."), 5000);

	CXLayerStyle style = layerman.FindStyle(400);
	if (style.m_lpDispatch == NULL)
	{
		style = layerman.NewStyle(400);
		style.SetPen(util.RGBColor(255, 0, 255), 1, util.GetConstToValue(_T("PS_SOLID")));
		style.SetBrush(util.RGBAColor(0, 255, 25, 100), util.GetConstToValue(_T("BS_SOLID")));

	}

	CXLayerCircle Obj = layerman.NewCircle(1, -1);
	Obj.SetStyle(style);
	Obj.SetClosed(1); // 0 : 선만 표시 1:내부에 Style 적용
	Obj.SetShowDistance(1);
	Obj.SetShowArea(1);
	Obj.SetCanClick(1);
	Obj.SetCanFocus(1);
	Obj.SetStateModeNew();

}
//------------------------------------------------------------------------------
//  면적 계산
//------------------------------------------------------------------------------
void CLogiMapBase::OnCheckArea()
{
	// Make Layer Style
	CXLayerStyle style = layerman.NewStyle(-1);
	style.SetPen(util.RGBColor(255, 0, 0), 1, util.GetConstToValue(_T("PS_SOLID")));
	style.SetBrush(util.RGBAColor(0, 0, 255, 100), util.GetConstToValue(_T("BS_SOLID")));

	// Make Polygon
	CXLayerPolygon  obj = layerman.NewPolygon(100, -1);
	obj.SetStyle(style);
	obj.SetClosed(1); // 1:polygon, 0:polyline
	obj.SetShowDistance(0);
	obj.SetShowArea(1); // 범위측정 값을 표시
	obj.SetCanClick(1);
	obj.SetCanFocus(1);
	obj.SetStateModeNew(); // 사용자 입력값을 받습니다
}
//------------------------------------------------------------------------------
//  거리 계산
//------------------------------------------------------------------------------
void CLogiMapBase::OnCheckDistance()
{
	// Make Layer Style
	CXLayerStyle style = layerman.NewStyle(-1);
	style.SetPen(util.RGBColor(255, 0, 0), 1, util.GetConstToValue(_T("PS_DOT")));

	// Make Polygon
	CXLayerPolygon  obj = layerman.NewPolygon(100, -1);
	obj.SetStyle(style);
	obj.SetClosed(0); // 1:polygon, 0:polyline
	obj.SetShowDistance(1);// 거리측정값을 표시 합니다.
	obj.SetCanClick(1);
	obj.SetCanFocus(1);
	obj.SetStateModeNew(); // 사용자 입력값을 받습니다
}

//------------------------------------------------------------------------------
//  조망 보기
//------------------------------------------------------------------------------
void CLogiMapBase::OnSmBirdview()
{
	CXVector vector = ctrlstate.GetRotate();

	if (vector.GetX() != 0) {
		vector.SetX(0);
	} else {
		vector.SetX(-60);
	}
	ctrlstate.SetRotate(vector);
}
//------------------------------------------------------------------------------
//  3D 보기
//------------------------------------------------------------------------------
void CLogiMapBase::OnSm3Dview()
{
	long state =  util.GetConstToValue(_T("TMCTRLSTATE_DISPLAY_BUILDING_TYPE"));
	long type = ctrlstate.GetState(state);

	switch(type) {
		case 1 :  ctrlstate.SetState(state, util.GetConstToValue(_T("TMCTRLSTATE_CODE_BUILDING_3D_MASK")));
			break;
		case 16 : ctrlstate.SetState(state, util.GetConstToValue(_T("TMCTRLSTATE_CODE_BUILDING_3D_1")));
			break;
		case 17 : ctrlstate.SetState(state, util.GetConstToValue(_T("TMCTRLSTATE_CODE_BUILDING_3D_2")));
			break;
		case 18 : ctrlstate.SetState(state, util.GetConstToValue(_T("TMCTRLSTATE_CODE_BUILDING_NORMAL")));
			break;
		default : ctrlstate.SetState(state, util.GetConstToValue(_T("TMCTRLSTATE_CODE_BUILDING_NORMAL")));
			break;		
	}
}

void CLogiMapBase::OnSmClipboard()
{
	CopyToClipboard();
	MessageBox(_T("클립보드에 복사가 되었습니다."), _T("작업 완료"));
}

void CLogiMapBase::OnSmImagesave()
{
	CString fileName = util.FileDialog(_T("이미지 저장"), _T("C:\\"), _T("MapImage.png"),
		_T("Windows Bitmap Image (*.png)|*.png|PNG Image (*.png)|*.PNG|Jpeg Image (*.jpg)|*.JPG"));    

	if (fileName.IsEmpty() == false) {
		if (SaveImage(fileName)) 
			MessageBox(_T("이미지를 저장하였습니다"), _T("확인"));
	}
}

void CLogiMapBase::OnPolygon()
{
	uiman.SetMessage(_T("마우스 오른쪽을 클릭하면 종료 됩니다."), 5000);

	// Make Layer Style
	CXLayerStyle style = layerman.NewStyle(-1);
	style.SetPen(util.RGBColor(255, 0, 0), 1, util.GetConstToValue(_T("PS_SOLID")));
	style.SetBrush(util.RGBAColor(0, 255, 255, 100), util.GetConstToValue(_T("BS_SOLID")));

	// Make Layer Polygon
	CXLayer layer = layerman.FindLayer(1);
	if (!layer) {
		layer = layerman.NewLayer(1);
	}

	CXLayerPolygon polygon = layer.NewPolygon(-1);
	polygon.BeginUpdate();
	// 0: PolyLine, 1: Polygone
	polygon.SetClosed(1); 
	polygon.SetStyle(style);
	polygon.SetCanClick(1);
	polygon.SetCanFocus(1);
	polygon.EndUpdate();
	polygon.SetStateModeNew();

}

//------------------------------------------------------------------------------
//  사용자 입력에 따른 PolyLine 생성
//------------------------------------------------------------------------------
void CLogiMapBase::OnPolyline()
{
	uiman.SetMessage(_T("마우스 오른쪽을 클릭하면 종료 됩니다."), 5000);

	// Make Layer Style
	CXLayerStyle style = layerman.NewStyle(-1);
	style.SetPen(util.RGBColor(255, 0, 0), 1, util.GetConstToValue(_T("PS_SOLID")));

	// Make Laeyr Polyline
	CXLayer layer = layerman.FindLayer(1);
	if (!layer) {
		layer = layerman.NewLayer(1);
	}

	CXLayerPolygon polyline = layer.NewPolygon(-1);
	polyline.BeginUpdate();
	// 0: PolyLine, 1: Polygone
	polyline.SetClosed(0); 
	polyline.SetStyle(style);
	polyline.SetCanFocus(1);
	polyline.SetCanClick(1);
	polyline.EndUpdate();
	polyline.SetStateModeNew();

}
//------------------------------------------------------------------------------
//  Layer Object 수정 모드
//------------------------------------------------------------------------------
void CLogiMapBase::OnObjectModify()
{
	CXBaseMan baseman = layerman.CastToBaseManager();
	if (baseman.GetManMode() == util.GetConstToValue(_T("TMMAN_MODE_EDIT"))) {
		baseman.SetManMode(util.GetConstToValue(_T("TMMAN_MODE_NONE")));
	} else {
		baseman.SetManMode(util.GetConstToValue(_T("TMMAN_MODE_EDIT")));
	}

}
//------------------------------------------------------------------------------
//  Polygon 삭제
//------------------------------------------------------------------------------
void CLogiMapBase::OnRemovePolygon()
{
	layerman.ClearLayer();
}

void CLogiMapBase::OnAddAddressBar()
{
	CXSize dpsize = ctrlstate.GetSizeDP();
	imageman.SetDefaultPath(GetModuleFullPath() + "\\Images");

	CXUIImage btnImg = uiman.CreateUI_Image(uiman);
	btnImg.SetParent(uiman);
	btnImg.SetUIID(500);
	btnImg.SetImage("region_bar.png");
	btnImg.SetBound(0, 0, 337, 22);
	//btnImg.SetBound(0, dpsize.get__CY() -37, 337, 37);
	btnImg.SetCanClick(1);
	btnImg.SetAlpha(50);
	btnImg.SetAnchor(util.GetConstToValue("TMUIOBJ_ANCHOR_LEFT") | util.GetConstToValue("TMUIOBJ_ANCHOR_TOP"));
	btnImg.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));

	uiman = ctrlman.GetUIMan();
	CXUIStaticText stcMsgArea = uiman.CreateUI_StaticText(uiman);
	stcMsgArea.SetParent(btnImg);
	stcMsgArea.SetUIID(501);
	stcMsgArea.SetBound(5, 0, 320, 22);
	stcMsgArea.SetUIObjFontColor(util.RGBColor(255, 255, 255));
	stcMsgArea.SetFont(12, 1, "돋움", 0);  
	stcMsgArea.SetCanFocus(0);
	stcMsgArea.SetCanClick(1);
	stcMsgArea.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));

	long nPosX, nPosY;
	GetCenterPos(nPosX, nPosY);
	RefreshAdminInfo(TRUE, TRUE, nPosX, nPosY);
}

void CLogiMapBase::RefreshAdminInfo(BOOL bForceRefresh, BOOL bUIBarOnly, long nPosX, long nPosY)
{
	static CString strLastAdminName;

	CString strAdminName = GetAdminName(4, TRUE, nPosX, nPosY);
	if(strAdminName.GetLength() > 0)
	{
		if(strLastAdminName != strAdminName || bForceRefresh)
		{
			CXUIObj obj = uiman.GetChildByUIID(501);
			if(obj != NULL) 
				obj.SetCaption(strAdminName);

			if(m_pRegionSelectDlg && !bUIBarOnly)
			{
				if(m_pRegionSelectDlg->IsWindowVisible() || bForceRefresh)
				{
					CString strSidoCode, strGugunCode, strDongCode;
					CString strSido, strGugun, strDong, strLi;

					GetAdminName(strSido, strGugun, strDong, strLi, strAdminName);
					strSidoCode = MakeRegionCombo("", m_pRegionSelectDlg->m_cmbSido, strSido);
					strGugunCode = MakeRegionCombo(strSidoCode, m_pRegionSelectDlg->m_cmbGugun, strGugun);
					strDongCode = MakeRegionCombo(strSidoCode + strGugunCode, m_pRegionSelectDlg->m_cmbDong, strDong);
				}
			}

			strLastAdminName = strAdminName;
		}
	}
}

CString CLogiMapBase::GetAdminName(int nLevel, BOOL bUseUserPos, long nPosX, long nPosY)
{
	if(bUseUserPos)
	{
		CXAdminItem item =  adminman.GetAdminItem(nPosX, nPosY);
		return item.GetAdminName(" ", nLevel);
	}
	else
	{
		CXPoint posLL = ctrlstate.GetLLCenter();
		CXAdminItem item =  adminman.GetAdminItem(posLL.get__X(), posLL.get__Y());
		return item.GetAdminName(" ", nLevel);
	}
}

BOOL CLogiMapBase::GetAdminName(CString &strSido, CString &strGugun, CString &strDong, CString &strLi, CString strAdminName)
{
	CString strAdmin = GetAdminName() + " ";
	char szSido[20], szGugun[50], szDong[50], szLi[50];

	int nPos = STRTOK2(" ", (LPSTR)(LPCTSTR)strAdmin, 0, szSido, szGugun, szDong, VL_END);
	if(nPos > 0)
	{
		strSido = szSido;
		strGugun = szGugun;
		strDong = szDong;
		STRTOK2(" ", (LPSTR)(LPCTSTR)strAdmin, nPos, szLi, VL_END);
		strLi = szLi;
		return TRUE;
	}

	return FALSE;
}

int CLogiMapBase::STRTOK2(char *delimiter, char *src, int nStart, ...)
{
	char *dst;
	int pos = nStart;
	int len = (int)strlen(src);
	int i;

	va_list vl;
	va_start(vl, src);
	i = va_arg(vl, int);

	while(strncmp((dst = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		if(i == len) return 0;
		for(i = pos; i < len; i++)
		{
			int z = 0;
			for(z = 0; z < strlen(delimiter); z++)
			{
				if(src[i] == delimiter[z])
				{
					memcpy(dst, &src[pos], i - pos);
					dst[i - pos] = '\0';
					pos = i + 1;
					z = 0xFFFF;
					break;
				}
			}

			if(z == 0xFFFF)
				break;
		}
	}

	va_end(vl);
	return pos == nStart ? 0 : pos ;
}

CString CLogiMapBase::MakeRegionCombo(CString strAdminCode, CComboBox &cmbTarget, CString strSelectName)
{
	BOOL bSidoQuery = strAdminCode.IsEmpty();
	CString strAdminList = adminman.GetAdminInfoList(strAdminCode, strAdminCode.IsEmpty() ? 0 : 1);

	int nPos = 0;
	char szSido[20], szCode[10];
	CString strSelectCode, strFirstCode;
	int nSelectRow = 0;
	int nEndCount = bSidoQuery ? 16 : 0xFFFF;

	cmbTarget.ResetContent();

	for(int i = 0; i < nEndCount; i++)
	{
		nPos = CLogiMapBase::STRTOK2(":;", (LPSTR)(LPCTSTR)strAdminList, nPos, szSido, szCode, VL_END);
		if(nPos <= 0)
			break;

		int nIndex = cmbTarget.AddString(szSido);
		cmbTarget.SetItemData(nIndex, atol(szCode));

		if(strSelectName == szSido)
		{
			strSelectCode = szCode;
			nSelectRow = i;
		}

		if(i == 0) 
				strFirstCode = szCode;
	}

	cmbTarget.SetCurSel(nSelectRow);

	return nSelectRow > 0 ? strSelectCode : strFirstCode;
}

void CLogiMapBase::MoveMapFormCode(CString strCode, long nType)
{
	CXAdminItem item = adminman.GetAdminItemByCode(strCode);
	if(item.m_lpDispatch != NULL)
		item.GotoCenter(nType);
}

void CLogiMapBase::MoveMap(CPOIUnit *pPOI)
{
	long nPosX = pPOI->GetPosX();
	long nPosY = pPOI->GetPosY();
	MoveMap(nPosX, nPosY);
}

void CLogiMapBase::MoveMap(long nPosX, long nPosY)
{
	CXControlState ctrlstate = ctrlman.GetControlState();
	IsPosUsable(nPosX, nPosY);
	ctrlstate.SetLLCenter(nPosX, nPosY);
}

void CLogiMapBase::MoveMap(int nPosX, int nPosY)
{
	MoveMap((long)nPosX, (long)nPosY);
}

void CLogiMapBase::MoveMap(double dPosX, double dPosY)
{
	long nPosX = dPosX * 1000000;
	long nPosY = dPosY * 1000000;
	MoveMap(nPosX, nPosY);
}

BOOL CLogiMapBase::IsPosUsable(long &nPosX, long &nPosY, BOOL bDontChange, BOOL bWGS84ToBessel)
{
	//도:분:초 -> 초단위
	if(nPosX > 100000000)
	{
		if(!bDontChange)	
		{
			nPosX = nPosX * 0.36;
			nPosY = nPosY * 0.36;
	
			if(bWGS84ToBessel) 
			{
				//CXMapPos var = GetCoordSys().WGS84ToBessel((double)nPosX, (double)nPosY);
				//nPosX = var.GetLon();
				//nPosY = var.GetLat();

				//CXCoordSys0 coordsys = m_pSmartSRXPtr->GetCoordSys();
				//CXPoint0 var = coordsys.WGS84ToBessel(nPosX, nPosY); choe
			}
		}

		return FALSE;
	}
	else if(nPosX == 0 || nPosY == 0)
	{
		//GetCenterPos(nPosX, nPosY);
		return FALSE;
	}
	//초단위인데, X/Y가 뒤집어져 있음
	else if(nPosX < 20000000)
	{
		long nPos = nPosX;
		nPosX = nPosY;
		nPosY = nPos;
	}

	return TRUE;
}

CXMapPos CLogiMapBase::GetMapPos(long nPosX, long nPosY)
{
	CXUtility u = GetUtility();
	CXMapPos pos = u.GetMapPos();

	//CXMapPos pos = GetUtility().GetMapPos();// <--에러
	pos.SetLon(nPosX);
	pos.SetLat(nPosY);
	return pos;
}

long CLogiMapBase::GetMapLevel()
{
	CXControlState ctrlstate = ctrlman.GetControlState();
	return ctrlstate.GetLevel();
}

CXLayer CLogiMapBase::GetLayer(long nLayer)
{
	CXLayer layer = layerman.FindLayer(nLayer);
	if(!layer) {
		layer = layerman.NewLayer(nLayer);
	}
	return layer;
}

void CLogiMapBase::SetPOIVisibleAsc(CXPOIItem item, long nMaxLevel)
{
	item.BeginUpdate();

	for(int i = 0; i <= MAP_MAX_LEVEL; i++)
		item.SetVisibleLevel(i, (i <= nMaxLevel) ? 1 : 0);

	item.EndUpdate();
}

void CLogiMapBase::SetPOIVisibleDec(CXPOIItem item, long nMinLevel)
{
	item.BeginUpdate();

	for(int i = 0; i <= MAP_MAX_LEVEL; i++)
		item.SetVisibleLevel(i, (i >= nMinLevel) ? 1 : 0);

	item.EndUpdate();
}

CString CLogiMapBase::GetModuleFullPath()
{
	CString strFullPath;
	TCHAR szFullPath[MAX_PATH];
	if (GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		int nPos;
		strFullPath = szFullPath;
		if ((nPos = strFullPath.ReverseFind('\\')) != -1)
			strFullPath = strFullPath.Mid(0, ++nPos);
	}

	return strFullPath;
}

CXUIImage CLogiMapBase::SetUIImage(long nID, CString strImage, CRect rc, long nAlpha, long nAnchor, long nEvent)
{
	CXSize dpsize = ctrlstate.GetSizeDP();
	CXUtility util = GetUtility();

	CXImageMan imageman = ctrlman.GetImageMan();
	imageman.SetDefaultPath(GetModuleFullPath() + "\\Images");

	CXUIImage btnImg = uiman.CreateUI_Image(uiman);
	btnImg.SetParent(uiman);
	btnImg.SetUIID(nID);
	btnImg.SetImage(strImage);
	btnImg.SetBound(rc.left, rc.top, rc.Width(), rc.Height());
	//btnImg.SetBound(0, dpsize.get__CY() -37, 337, 37);
	btnImg.SetCanClick(1);
	btnImg.SetAlpha(nAlpha);

	if(nAnchor > 0)
		btnImg.SetAnchor(nAnchor);

	if(nEvent > 0)
		btnImg.AddEventMode(nEvent);

	//btnImg.SetAnchor(util.GetConstToValue("TMUIOBJ_ANCHOR_LEFT") | util.GetConstToValue("TMUIOBJ_ANCHOR_TOP"));
	//btnImg.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));
/*
	CXUIStaticText stcMsgArea = uiman.CreateUI_StaticText(uiman);
	stcMsgArea.SetParent(btnImg);
	stcMsgArea.SetUIID(501);
	stcMsgArea.SetBound(5, 4, 320, 30);
	stcMsgArea.SetUIObjFontColor(util.RGBColor(255, 255, 255));
	stcMsgArea.SetFont(12, 1, "돋움");  
	stcMsgArea.SetCanFocus(0);
	stcMsgArea.SetCanClick(1);
	stcMsgArea.AddEventMode(util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));
*/
	return btnImg;
}

CXUIStaticText CLogiMapBase::AddUIStaticText(CXUIImage parent, long nID, CString strText, 
											 CRect rcBound, COLORREF crFont,
											long nFontHeight, CString strFont, long nEvent)
{
	CXUIStaticText stcMsgArea = uiman.CreateUI_StaticText(parent);
	stcMsgArea.SetParent(parent);
	stcMsgArea.SetUIID(nID);
	stcMsgArea.SetBound(rcBound.left, rcBound.top, rcBound.Width(), rcBound.Height());
	stcMsgArea.SetUIObjFontColor(util.RGBColor(GetRValue(crFont), GetGValue(crFont), GetBValue(crFont)));
	stcMsgArea.SetFont(nFontHeight, 1, strFont, 0);  
	stcMsgArea.SetCanFocus(0);
	stcMsgArea.SetCanClick(1);
	stcMsgArea.SetCaption(strText);
	if(nEvent > 0)
		stcMsgArea.AddEventMode(nEvent);
	return stcMsgArea;
}

long CLogiMapBase::GetValue(CString strValue)
{
	return util.GetConstToValue(strValue);
}

long CLogiMapBase::GetMapCX()
{
	CXSize dpsize = ctrlstate.GetSizeDP();
	return dpsize.get__CX();
}

long CLogiMapBase::GetMapCY()
{
	CXSize dpsize = ctrlstate.GetSizeDP();
	return dpsize.get__CY();
}

BOOL CLogiMapBase::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		m_bLButtonDown = TRUE;
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{
		m_bLButtonDown = FALSE;
		RefreshAdminInfo();
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CLogiMapBase::SearchRoute(long nType, long nPosX, long nPosY, BOOL bShowImage)
{
	return FALSE;
	/*
	int iRouteType = 1; // 0 : local, 1: server
	CXRouteMan routeman = ctrlman.GetRouteMan(); 
	CXRouteItem route = routeman.GetCurrentRoute();

	IsPosUsable(nPosX, nPosY);

	CXPOIStyle styleNULL =  poiman.FindStyle(2000);
	if (styleNULL.m_lpDispatch == NULL) {
		styleNULL = poiman.NewStyle(2000);
		//style.SetImage(255, m_imgCarStart);
		styleNULL.SetGDIFont(_T("굴림"), 0, 9);
		styleNULL.SetFontColor(util.RGBColor(255, 0, 0));
	}

	if(nType == 0)
	{
		if (route.m_lpDispatch == NULL) {
			route = routeman.NewRoute(iRouteType, 100) ;
		}

		// New cns 
		BOOL bOk = route.SetSourceInfo(_T("211.172.242.189"), 8080);  // l4
		//route.SetSourceInfo(_T("211.172.242.175"), 8080); // 실IP
		//route.SetSourceInfo(_T("211.172.242.177"), 8080);// 실IP
		//route.SetSourceInfo(_T("211.172.242.182"), 8080);// 실IP
 
		// OLD  cns
		//BOOL bOk = route.SetSourceInfo(_T("211.172.242.188"), 8080);  // l4
		//route.SetSourceInfo(_T("211.172.242.176"), 8080); // 실IP
		//route.SetSourceInfo(_T("211.172.242.163"), 8080);// 실IP
		route.ClearFlag();
 
		g_bana_log->Print("****************************** Route : %d\r\n -------------------------------------------------", bOk);

		m_sFlag = NULL;
		m_sFlag = route.AddOrigin(nPosX, nPosY, 0);

		CXPOIStyle style =  poiman.FindStyle(1000);
		if (style.m_lpDispatch == NULL) {
			style = poiman.NewStyle(1000);
			style.SetImage(255, m_imgCarStart);
			style.SetGDIFont(_T("굴림"), 0, 9);
			style.SetFontColor(util.RGBColor(255, 0, 0));
		}
		
		m_sFlag.SetCaption(_T(""));

		if(!bShowImage)
			m_sFlag.SetPOIStyle(styleNULL);
		else
			m_sFlag.SetPOIStyle(style);
	}
	else if(nType == 1)
	{
		CXRouteFlag via = route.AddVia(nPosX, nPosY, 0);

		CXPOIStyle style =  poiman.FindStyle(1001);
		if (style.m_lpDispatch == NULL) {
			style = poiman.NewStyle(1001);
			style.SetImage(255, m_imgCarVia);
			style.SetGDIFont(_T("굴림"), 0, 9);
			style.SetFontColor(util.RGBColor(255, 0, 0));
		}

		via.SetCaption(_T(""));

		if(!bShowImage)
			m_sFlag.SetPOIStyle(styleNULL);
		else
			m_sFlag.SetPOIStyle(style);
	} 
	else if(nType == 2)
	{
		route.ClearDestinationFlag();
		m_eFlag = NULL;
		m_eFlag = route.AddDestination(nPosX, nPosY, 0);

		CXPOIStyle style =  poiman.FindStyle(1002);
		if (style.m_lpDispatch == NULL) {
			style = poiman.NewStyle(1002);
			style.SetImage(255, m_imgCarEnd);
			style.SetGDIFont(_T("굴림"), 0, 9);
			style.SetFontColor(util.RGBColor(255, 0, 0));
		}

		m_eFlag.SetCaption(_T(""));

		if(!bShowImage)
			m_sFlag.SetPOIStyle(styleNULL);
		else
			m_sFlag.SetPOIStyle(style);
	} 
	else if (nType == 3) 
	{ // 경로검색
		g_bana_log->Print("***********경로검색 시작 11111111\r\n");
		if (m_eFlag == NULL || m_sFlag == NULL) return FALSE;
		if (route.m_lpDispatch) {
			
			CXRouteCost cost;
			cost = route.LoadCost(_T(""), 0);
			int nRouteOption = 2; // 최단 2 , 최적 0, 1
			nRouteOption = 2 + (1 * 0xFF) + (2 * 0xFFFF);
			//nRouteOption = 201;//choe

			g_bana_log->Print("***********경로검색 시작 nRouteOption:%d 2222222222222\r\n", nRouteOption);

			if (route.FindPath(cost, nRouteOption)) {
				g_bana_log->Print("***********경로검색 시작 33333333333\r\n");
				CXLayerMan layerman = ctrlman.GetLayerMan();
				CXLayerStyle lStyle = layerman.FindStyle(1003);
				if (lStyle.m_lpDispatch == NULL) {
					g_bana_log->Print("***********경로검색 시작 44444444\r\n");
					lStyle = layerman.NewStyle(1003);
					lStyle.SetPen(util.RGBColor(255, 0, 0), 3, util.GetConstToValue(_T("PS_SOLID")));
				}
				route.SetLayerStyle(lStyle);
			} else {
				g_bana_log->Print("***********경로검색 시작 5555555555555555\r\n");
				return FALSE;
			}
			route.FreeCost(cost);


			g_bana_log->Print("length = %0.1fkm, time = %d\n", route.GetLength() / 1000.0, route.GetTravelTime());
		}
	}
	
	return TRUE;
	*/
}

long CLogiMapBase::GetRouteDistance()
{
	return 0;
	/*
	CXRouteMan routeman = ctrlman.GetRouteMan();
	CXRouteItem route = routeman.GetCurrentRoute();
	if(route.m_lpDispatch)
		return route.GetLength();
	else
		return 0;
	*/
}

BOOL CLogiMapBase::RegisterMapDll()
{
	CString strPath = GetModuleFullPath()+ CString(TALMAP_DLL_PATH);

	if(FALSE == LF->DllRegOcx(strPath) )
	{
		if(FALSE == LF->DllRegOcx(TALMAP_DLL_PATH2))
		{
			AfxMessageBox(CString(TALMAP_DLL_PATH2) + " 지도관련 파일을 찾을 수 없습니다.");
			return FALSE;
		}
	}

	strPath = GetModuleFullPath()+ CString(TALMAP_SR_DLL_PATH);

	if(FALSE == LF->DllRegOcx(strPath))
	{
		if(FALSE == LF->DllRegOcx(TALMAP_SR_DLL_PATH2))
		{
			AfxMessageBox(CString(TALMAP_DLL_PATH2) + " 지도관련 파일을 찾을 수 없습니다.");
			return FALSE;
		}
	}

	return TRUE;
}

void CLogiMapBase::OnMouseMove(long Flag, long X, long Y)
{
	static CString Admincode; 
	CXMapPos pos =  ctrlstate.DPToLL(X, Y);
	CXAdminItem item = adminman.GetAdminItem(pos.GetLon(), pos.GetLat());

	if(item != NULL)
	{
		CString temp = item.GetAdminCode();
		if(Admincode == temp) return;
		Admincode = temp;
		CXLayer layer = layerman.FindLayer(20);
		if(layer == NULL)
			layer = layerman.NewLayer(20);

		CXLayerStyle style = layerman.FindStyle(100);
		if (style == NULL)
		{
			style = layerman.NewStyle(100);
			//style.SetPen(util.RGBColor(255, 0, 0), 2, util.GetConstToValue("PS_SOLID"));
			style.SetBrush(util.RGBAColor(200, 200, 200, 90), util.GetConstToValue("BS_SOLID"));
		}

		CXLayerPolygon obj = layer.FindObject(100);
		if (obj == NULL)
		{
			obj = layer.NewPolygon(100);
			obj.SetStyle(style);
			obj.SetClosed(0);
		}

		obj.BeginUpdate();
		obj.SetAdminShape(item, 0);
		obj.EndUpdate();
		item.Destroy();

		ctrlman.NeedUpdate(util.GetConstToValue("NU_ALL"), ctrlstate.GetDPRect());

		if(!m_bRefreshAdminOnlyCenterPos)
			RefreshAdminInfo(TRUE, TRUE, pos.GetLon(), pos.GetLat());
	}

}

void CLogiMapBase::SetNotCreateToolBar()
{
	m_bNotCreateToolBar = TRUE;
}

void CLogiMapBase::SetNotCreateAddressBar()
{
	m_bNotCreateAddressBar = TRUE;
}

void CLogiMapBase::DeletePOI(int nGroup, int nID)
{
	if(nID < 0)
		poiman.DeleteGroup(nGroup);
	else
	{
		CXPOIGroup group = poiman.FindGroup(nGroup);
		if(group.m_lpDispatch != NULL) 
			group.DeleteItem(nID);
	}
}

void CLogiMapBase::CreateWait()
{
	MSG m_msgCur;
	do AfxGetApp()->PumpMessage();
	while(::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE));
}

void CLogiMapBase::SetRefereshAdminState(BOOL bOnlyCenterPos)
{
	m_bRefreshAdminOnlyCenterPos = bOnlyCenterPos;
}

void CLogiMapBase::WGS84ToBessel(long &nPosX, long &nPosY)
{  
	CGeoCoordConv GeoCoordConv;

	GeoCoordConv.SetSrcType((GeoEllips)kWgs84, (GeoSystem)0);
	GeoCoordConv.SetDstType((GeoEllips)kBessel1984, (GeoSystem)0);

	double dPosX1 = nPosX/1000000.0;
	double dPosY1 = nPosY/1000000.0;
	double dPosX2,dPosY2;

	GeoCoordConv.Conv(dPosX1,dPosY1,dPosX2,dPosY2);
	nPosX = dPosX2 * 1000000;
	nPosY = dPosY2 * 1000000;
}

void CLogiMapBase::BesselToWGS84(long &nPosX, long &nPosY)
{
	CGeoCoordConv GeoCoordConv;

	GeoCoordConv.SetSrcType((GeoEllips)kBessel1984, (GeoSystem)0);
	GeoCoordConv.SetDstType((GeoEllips)kWgs84, (GeoSystem)0);

	double fPosX1 = nPosX/1000000.0;
	double fPosY1 = nPosY/1000000.0;
	double fPosX2, fPosY2;

	GeoCoordConv.Conv(fPosX1, fPosY1, fPosX2, fPosY2);
	nPosX = fPosX2 * 1000000;
	nPosY = fPosY2 * 1000000;
}

void CLogiMapBase::KatecToBessel(long &nPosX, long &nPosY)
{  
	CGeoCoordConv GeoCoordConv;

	GeoCoordConv.SetSrcType((GeoEllips)kBessel1984, (GeoSystem)4);
	GeoCoordConv.SetDstType((GeoEllips)kBessel1984, (GeoSystem)0);

	double dPosX2,dPosY2;

	GeoCoordConv.Conv(nPosX,nPosY,dPosX2,dPosY2);
	nPosX = dPosX2 * 1000000;
	nPosY = dPosY2 * 1000000;
}


void CLogiMapBase::InitSRXItem()
{
	if(m_bInitSRXItem == TRUE)
		return;

	m_pSmartSRXPtr = NULL;
	if(m_pSmartSRXPtr) delete m_pSmartSRXPtr;
	m_pSmartSRXPtr = new CSmartSRXCtrl();

	bool bCreateSmartSRX = false;
	COleException *pe = new COleException;
	try {
		if (m_pSmartSRXPtr->CreateDispatch(_T("SmartSRX.SmartSRXCtrl.1"), pe)) 
		{
			m_pSmartSRXPtr->SetLicenseType(1); // 1 : TalMap, 2 : SmartMap
			bCreateSmartSRX = true;
		}
		else {
			throw pe;
		}
	}
	catch (COleDispatchException * pe) 
	{
		CString cStr;		
		if (!pe->m_strSource.IsEmpty())			cStr = pe->m_strSource + _T(" - ");
		if (!pe->m_strDescription.IsEmpty())	cStr += pe->m_strDescription;
		else									cStr += "unknown error";
		AfxMessageBox(cStr, MB_OK, (pe->m_strHelpFile.IsEmpty()) ?  0 : pe->m_dwHelpContext);
		pe->Delete();
	}
	catch (CException* pe) 
	{
		TRACE("[ERROR] %s(%d): OLE Execption Caught: SCODE = %x", __FILE__, __LINE__, COleException::Process(pe));
		pe->Delete();
	}
	pe->Delete();	

	m_bInitSRXItem = TRUE;
}