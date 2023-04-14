// D:\LOGISOFT\Daeri2011\Map\RiderMapCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMapCtrl.h"
#include "RiderMapDlg.h"
#include "RiderMapNormalForm.h"
#include "RiderMapSetDlg.h"


// CRiderMapCtrl

IMPLEMENT_DYNAMIC(CRiderMapCtrl, CLogiMapNew)

CRiderMapCtrl::CRiderMapCtrl()
{
	m_uistcLeftArrow = NULL;
	m_uistcRightArrow = NULL;
	m_uistcPlay = NULL;
	m_uistcStop = NULL;
	m_uistcSpeedUp = NULL;
	m_uistcSpeedDown = NULL;
	m_nBagType = 0;
	m_nCarType = 0;
	m_nTonType = 0;

	ZeroMemory(m_uiimageBag, sizeof(m_uiimageBag));
	ZeroMemory(m_uiimageCar, sizeof(m_uiimageCar));
	ZeroMemory(m_uiimageTon, sizeof(m_uiimageTon));

	m_bHoverShowRiderHaveOrder = FALSE;
	m_bHasCargoBranch = FALSE;
	m_bCargoOnly = FALSE;
}

CRiderMapCtrl::~CRiderMapCtrl()
{
}


BEGIN_MESSAGE_MAP(CRiderMapCtrl, CLogiMapNew)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CRiderMapCtrl, CLogiMapNew)
	ON_EVENT_REFLECT(CRiderMapCtrl, 48, CRiderMapCtrl::OnPOIMouseHover, VTS_DISPATCH)
	ON_EVENT_REFLECT(CRiderMapCtrl, 47, CRiderMapCtrl::OnPOIMouseLeave, VTS_DISPATCH)
	//ON_EVENT_REFLECT(CRiderMapCtrl, 1, CRiderMapCtrl::OnCreateMap, VTS_I4)
	//ON_EVENT_REFLECT(CRiderMapCtrl, 4, CRiderMapCtrl::OnMouseDown, VTS_I4 VTS_I4 VTS_I4)
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

// CRiderMapCtrl 메시지 처리기입니다.


void CRiderMapCtrl::OnCreateMap(long Value)
{
	if(!m_bMapCreated) 
	{
		m_bNotCreateToolBar = TRUE;
		CLogiMapNew::OnCreateMap(Value);
		uiman.SetShowCompass(0);

		LoadLocalImage("btn_nothing.png");
		LoadLocalImage("btn_nothing_over.png");
		LoadLocalImage("btn_one.png");
		LoadLocalImage("btn_one_over.png");
		LoadLocalImage("btn_two.png");
		LoadLocalImage("btn_two_over.png");
		LoadLocalImage("btn_three.png");
		LoadLocalImage("btn_three_over.png");

		LoadLocalImage("btn_bigbike.png");
		LoadLocalImage("btn_bigbike_over.png");
		LoadLocalImage("btn_dama.png");
		LoadLocalImage("btn_dama_over.png");
		LoadLocalImage("btn_labo.png");
		LoadLocalImage("btn_labo_over.png");
		LoadLocalImage("btn_van.png");
		LoadLocalImage("btn_van_over.png");
		LoadLocalImage("btn_truck.png");
		LoadLocalImage("btn_truck_over.png");

		LoadLocalImage("btn_1_0t.png");
		LoadLocalImage("btn_1_0t_over.png");
		LoadLocalImage("btn_1_4t.png");
		LoadLocalImage("btn_1_4t_over.png");
		LoadLocalImage("btn_2_5t.png");
		LoadLocalImage("btn_2_5t_over.png");
		LoadLocalImage("btn_3_5t.png");
		LoadLocalImage("btn_3_5t_over.png");
		LoadLocalImage("btn_4_5t.png");
		LoadLocalImage("btn_4_5t_over.png");
		LoadLocalImage("btn_5_0t.png");
		LoadLocalImage("btn_5_0t_over.png");
		LoadLocalImage("btn_11_0t.png");
		LoadLocalImage("btn_11_0t_over.png");
		
		CXUIImage image = SetUIImage(600, "small_bar.png", 
			CRect(0, 22, 30, 44), 50, 
			GetValue("TMUIOBJ_ANCHOR_LEFT"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcLeftArrow = AddUIStaticText(image, 601, "<-", CRect(0, 0, 30, 22), RGB(255, 255, 255), 12, 
					"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));

		CXUIImage image2 = SetUIImage(602, "small_bar.png", 
			CRect(GetMapCX() - 30, 55, GetMapCX(), 77), 50, 
			GetValue("TMUIOBJ_ANCHOR_RIGHT"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcRightArrow = AddUIStaticText(image2, 603, "->", CRect(0, 0, 30, 22), RGB(255, 255, 255), 12, 
			"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));

		CXUIImage image3 = SetUIImage(604, "bar.png", 
			//CRect(GetMapCX() - 120, 55, GetMapCX(), 77), 50, 
			CRect(GetMapCX() - 330 , 3, GetMapCX() - 210, 23), 50, 
			GetValue("TMUIOBJ_ANCHOR_RIGHT"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcCount = AddUIStaticText(image3, 605, "라이더카운트", CRect(0, 0, 120, 22), RGB(255, 255, 255), 11, 
			"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));


		m_imageOrderCount = SetUIImage(606, "bar.png", 
			//CRect(GetMapCX() - 120, 55, GetMapCX(), 77), 50, 
			CRect(GetMapCX() - 430 , 3, GetMapCX() - 310, 23), 50, 
			GetValue("TMUIOBJ_ANCHOR_RIGHT"), 
			GetValue("TMEVENTTYPE_MOUSEUP"));

		m_uistcOrderCount = AddUIStaticText(m_imageOrderCount, 607, "오더카운트", CRect(0, 0, 120, 22), RGB(255, 255, 255), 11, 
			"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));


		//m_uistcCount.MoveTo(100, 100, 0, 0, 0);

		//m_uistcCount.MoveTo()

		if(!m_bCargoOnly)
		{
			SetBagImage();
			SetCarImage();
		}

		if(m_bHasCargoBranch)
			SetTonImage();
	}
}

void CRiderMapCtrl::CreateTraceNavi()
{
	if(!m_uistcStop)
	{
		m_uistcStop = CreateTraceNaviBtn(CRect(0, 70, 30, 92), 800, "정지");
		m_uistcPlay = CreateTraceNaviBtn(CRect(30, 70, 60, 92), 801, "계속");
		m_uistcSpeedUp = CreateTraceNaviBtn(CRect(60, 70, 90, 92), 802, "+");
		m_uistcSpeedDown = CreateTraceNaviBtn(CRect(90, 70, 120, 92), 803, "-");
	}
}

void CRiderMapCtrl::DeleteTraceNavi()
{
	if(m_uistcStop)
	{
		DeleteTraceNaviBtn(m_uistcStop);
		DeleteTraceNaviBtn(m_uistcPlay);
		DeleteTraceNaviBtn(m_uistcSpeedUp);
		DeleteTraceNaviBtn(m_uistcSpeedDown);
		m_uistcStop = NULL;
	}
}

void CRiderMapCtrl::DeleteTraceNaviBtn(CXUIStaticText uistc)
{
	if(uistc)
	{
		CXUIImage image = uistc.GetParent();
		uistc.DestroyUIObj();
		image.DestroyUIObj();
	}
}

CXUIStaticText CRiderMapCtrl::CreateTraceNaviBtn(CRect rc, int nID, CString strText)
{
	CXUIImage image = SetUIImage(nID, "small_bar.png", 
		rc, 50, 
		GetValue("TMUIOBJ_ANCHOR_LEFT"), 
		GetValue("TMEVENTTYPE_MOUSEUP"));

	return AddUIStaticText(image, nID+10, strText, CRect(0, 0, 30, 22), RGB(255, 255, 255), 9, 
		"돋움", util.GetConstToValue(_T("TMEVENTTYPE_MOUSEUP")));
}

#define BAG_BTN_ID	501
#define SET_IMAGE_BAG(ret, id, file)\
	ret = SetUIImage(id, file, \
			   CRect(nPosX, 1, nPosX + 54, 59),\
			   40, \
			   GetValue("TMUIOBJ_ANCHOR_RIGHT") | \
			   GetValue("TMUIOBJ_ANCHOR_TOP"), \
			   GetValue("TMEVENTTYPE_MOUSEUP"));\
   nPosX += 54;

void CRiderMapCtrl::SetBagImage()
{
	long nPosX = GetMapCX() - 220;
	long nID = BAG_BTN_ID;

	uiman.BeginUpdate();

	for(int i = 0; i < sizeof(m_uiimageBag) / sizeof(CXUIImage); i++)
	{
		if(m_uiimageBag[i])
		{
			m_uiimageBag[i].DestroyUIObj();
			m_uiimageBag[i] = 0;
		}
	}

	SET_IMAGE_BAG(m_uiimageBag[0], nID++, GetBagImage(BTN_BAG_TYPE_0, "btn_nothing"));
	SET_IMAGE_BAG(m_uiimageBag[1], nID++, GetBagImage(BTN_BAG_TYPE_1, "btn_one"));
	SET_IMAGE_BAG(m_uiimageBag[2], nID++, GetBagImage(BTN_BAG_TYPE_2, "btn_two"));
	SET_IMAGE_BAG(m_uiimageBag[3], nID++, GetBagImage(BTN_BAG_TYPE_3, "btn_three"));

	uiman.EndUpdate();
}


#define CAR_BTN_ID	550
#define SET_IMAGE_CAR(ret, id, file)\
	ret = SetUIImage(id, file, \
	CRect(nPosX, nPosY, nPosX + 72, nPosY + 60),\
	50, \
	GetValue("TMUIOBJ_ANCHOR_RIGHT") | \
	GetValue("TMUIOBJ_ANCHOR_BOTTOM"), \
	GetValue("TMEVENTTYPE_MOUSEUP"));\
	nPosY += 60;

void CRiderMapCtrl::SetCarImage()
{
	long nPosX = GetMapCX() - 73;
	long nPosY = GetMapCY() - 410;
	long nID = CAR_BTN_ID;

	uiman.BeginUpdate();

	for(int i = 0; i < sizeof(m_uiimageCar) / sizeof(CXUIImage); i++)
	{
		if(m_uiimageCar[i])
		{
			m_uiimageCar[i].DestroyUIObj();
			m_uiimageCar[i] = 0;
		}
	}


	SET_IMAGE_CAR(m_uiimageCar[0], nID++, GetCarImage(BTN_CAR_TYPE_BIGBIKE, "btn_bigbike"));
	SET_IMAGE_CAR(m_uiimageCar[1], nID++, GetCarImage(BTN_CAR_TYPE_DAMA, "btn_dama"));
	SET_IMAGE_CAR(m_uiimageCar[2], nID++, GetCarImage(BTN_CAR_TYPE_LABO, "btn_labo"));
	SET_IMAGE_CAR(m_uiimageCar[3], nID++, GetCarImage(BTN_CAR_TYPE_VAN, "btn_van"));
	SET_IMAGE_CAR(m_uiimageCar[4], nID++, GetCarImage(BTN_CAR_TYPE_TRUCK, "btn_truck"));

	uiman.EndUpdate();
}


#define TON_BTN_ID	580
#define SET_IMAGE_TON(ret, id, file)\
	ret = SetUIImage(id, file, \
	CRect(nPosX, nPosY, nPosX + 41, nPosY + 41),\
	40, \
	GetValue("TMUIOBJ_ANCHOR_BOTTOM") | \
	GetValue("TMUIOBJ_ANCHOR_HCENTER"), \
	GetValue("TMEVENTTYPE_MOUSEUP"));\
	nPosX += 45;


void CRiderMapCtrl::SetTonImage()
{
	long nPosX = GetMapCX() / 2 - 160;
	long nPosY = GetMapCY() - 50;
	long nID = TON_BTN_ID;

	uiman.BeginUpdate();

	for(int i = 0; i < sizeof(m_uiimageTon) / sizeof(CXUIImage); i++)
	{
		if(m_uiimageTon[i])
		{
			m_uiimageTon[i].DestroyUIObj();
			m_uiimageTon[i] = 0;
		}
	}

	SET_IMAGE_TON(m_uiimageTon[0], nID++, GetTonImage(BTN_TON_TYPE_1_0, "btn_1_0t"));
	SET_IMAGE_TON(m_uiimageTon[1], nID++, GetTonImage(BTN_TON_TYPE_1_4, "btn_1_4t"));
	SET_IMAGE_TON(m_uiimageTon[2], nID++, GetTonImage(BTN_TON_TYPE_2_5, "btn_2_5t"));
	SET_IMAGE_TON(m_uiimageTon[3], nID++, GetTonImage(BTN_TON_TYPE_3_5, "btn_3_5t"));
	SET_IMAGE_TON(m_uiimageTon[4], nID++, GetTonImage(BTN_TON_TYPE_4_5, "btn_4_5t"));
	SET_IMAGE_TON(m_uiimageTon[5], nID++, GetTonImage(BTN_TON_TYPE_5_0, "btn_5_0t"));
	SET_IMAGE_TON(m_uiimageTon[6], nID++, GetTonImage(BTN_TON_TYPE_11_0, "btn_11_0t"));

	uiman.EndUpdate();
}



void CRiderMapCtrl::OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y)
{
	CLogiMapNew::OnUIMouseUp(Obj, Flag, X, Y);

	CXUIObj UIObj;
	UIObj.AttachDispatch(Obj, FALSE);

	CXUIObj pObj = UIObj.GetParent();
	long nID = UIObj.GetUIID();

	if(nID >= BAG_BTN_ID && nID < BAG_BTN_ID + 4)
	{
		long nValue = 1 << (nID - BAG_BTN_ID);
		BitToggle(m_nBagType, nValue);
		SetBagImage();
		((CRiderMapDlg*)GetParent())->m_pNormalForm->CheckVisibleAllRider();
	}
	else if(nID >= CAR_BTN_ID && nID < CAR_BTN_ID + 5)
	{
		long nValue = 1 << (nID - CAR_BTN_ID);
		BitToggle(m_nCarType, nValue);
		SetCarImage();
		((CRiderMapDlg*)GetParent())->m_pNormalForm->CheckVisibleAllRider();
	}
	else if(nID >= TON_BTN_ID && nID < TON_BTN_ID + 7)
	{
		long nValue = 1 << (nID - TON_BTN_ID);
		BitToggle(m_nTonType, nValue);
		SetTonImage();
		((CRiderMapDlg*)GetParent())->m_pNormalForm->CheckVisibleAllRider();
	}
}

CString CRiderMapCtrl::GetBagImage(long nValue, CString strImage)
{
	return (m_nBagType & nValue) ? strImage + "_over.png" : strImage + ".png";
}

CString CRiderMapCtrl::GetCarImage(long nValue, CString strImage)
{
	return (m_nCarType & nValue) ? strImage + "_over.png" : strImage + ".png";
}

CString CRiderMapCtrl::GetTonImage(long nValue, CString strImage)
{
	return (m_nTonType & nValue) ? strImage + "_over.png" : strImage + ".png";
}

void CRiderMapCtrl::BitToggle(long &nDst, long nValue)
{
	if(nDst & nValue)
		nDst -= nValue;
	else
		nDst += nValue;
}

void CRiderMapCtrl::OnChangeMapLevel()
{
	CLogiMapNew::OnChangeMapLevel();

	CRiderMapNormalForm *pForm = ((CRiderMapDlg*)GetParent())->m_pNormalForm;
	if(pForm && pForm->m_pRiderMapSetDlg)
	{
		pForm->m_pRiderMapSetDlg->m_nCurMapLevel = GetMapLevel();
		pForm->m_pRiderMapSetDlg->SetCurMapLevel();
	}
}

void CRiderMapCtrl::OnPOIMouseHover(LPDISPATCH POI)
{
	if(!m_bTraceMode && m_bHoverShowRiderHaveOrder)
	{
		CXPOIItem item;
		item.AttachDispatch(POI, FALSE);
		CXPOIGroup group = item.GetGroup();

		if(group.GetID() > 0 && group.GetID() < 0xF000)
		{
			CRiderMapDlg *pDlg = ((CRiderMapDlg*)GetParent());
			CRiderMapNormalForm *pForm = pDlg->m_pNormalForm;
			if(pForm)
				pForm->RefreshOrderList(group.GetID(), item.GetID());

			if(pDlg)
				pDlg->AddTraceRiderHasOrder(TRUE, group.GetID(), item.GetID(), 
						COleDateTime::GetCurrentTime(), 12);
		}
	}
}

void CRiderMapCtrl::OnPOIMouseLeave(LPDISPATCH POI)
{
	if(!m_bTraceMode && m_bHoverShowRiderHaveOrder)
	{
		CXPOIItem item;
		item.AttachDispatch(POI, FALSE);
		CXPOIGroup group = item.GetGroup();

		if(group.GetID() > 0 && group.GetID() < 0xF000)
		{	
			CXPOIGroup group = poiman.FindGroup(TRACE_RIDER_HAS_ORDER_START);
			if(group)
				group.SetVisible(0);

			group = poiman.FindGroup(TRACE_RIDER_HAS_ORDER_DEST);
			if(group)
				group.SetVisible(0);
		}
	}
}
