// D:\LOGISOFT\Daeri2011\Map\RcpMapCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpMapCtrl.h"


// CRcpMapCtrl

IMPLEMENT_DYNAMIC(CRcpMapCtrl, CLogiMapNew)

CRcpMapCtrl::CRcpMapCtrl()
{
	m_nRightTopWidth = 0;
	m_nRightTopHeight = 0;
}

CRcpMapCtrl::~CRcpMapCtrl()
{
}


BEGIN_MESSAGE_MAP(CRcpMapCtrl, CLogiMapNew)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CRcpMapCtrl, CLogiMapNew)
	//ON_EVENT_REFLECT(CRcpMapCtrl, 1, CRcpMapCtrl::OnCreateMap, VTS_I4)
	//ON_EVENT_REFLECT(CRcpMapCtrl, 4, CRcpMapCtrl::OnMouseDown, VTS_I4 VTS_I4 VTS_I4)
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

// CRcpMapCtrl 메시지 처리기입니다.


void CRcpMapCtrl::OnCreateMap(long Value)
{
	if(!m_bMapCreated) 
	{
		SetNotCreateToolBar();
		//SetNotCreateAddressBar();

		CLogiMapNew::OnCreateMap(Value);

		uiman.SetShowCompass(0);
		//uiman.SetShowLevelBar(0);

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
	}
}

void CRcpMapCtrl::RightTopImage(CString strRightTopImage, int nWidth, int nHeight)
{
	m_strRightTopImage = strRightTopImage;
	m_nRightTopWidth = nWidth;
	m_nRightTopHeight = nHeight;
}

