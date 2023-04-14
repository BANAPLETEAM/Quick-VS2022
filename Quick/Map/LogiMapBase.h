#pragma once

#include "TalMapInc.h"



#define WEB_IMAGE_PATH "http://map80.banaple.co.kr/images/MapImages2/"
#define WEB_FAIL_IMAGE_PATH "http://map1.logisoft.co.kr:8000/images/MapImages2/"

#define WEB_IMAGE_PATH1 "http://map80.banaple.co.kr/images/MapImages/"
#define WEB_FAIL_IMAGE_PATH1 "http://map1.logisoft.co.kr:8000/images/MapImages/"


#define LOCAL_IMAGE_PATH "Images"
#define WM_UI_MOUSE_UP	(WM_USER + 21)
#define MAP_MAX_LEVEL 12

class CRegionSelectAdvancedDlg;
class CPOIUnit;

class CLogiMapBase : public CWnd
{
	DECLARE_DYNCREATE(CLogiMapBase)

public:
	CLogiMapBase(void);
	~CLogiMapBase(void);

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5797B001, 0xEDDC, 0x4D2C, { 0xBD, 0x68, 0xD1, 0xFB, 0x4B, 0x38, 0x20, 0x24 } };
		//= { 0x5797B005, 0xEDDC, 0x4D2C, { 0xBD, 0x68, 0xD1, 0xFB, 0x4B, 0x38, 0x20, 0x24 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, 
		CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
		UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
			pPersist, bStorage, bstrLicKey); 
	}

	// 특성입니다.
public:

	// 작업입니다.
public:

	void SetGrabType(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void SetParentDispatch(LPDISPATCH Dispatch)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Dispatch);
	}
	long SetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long GetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	void TraceMessage(LPCTSTR Msg)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Msg);
	}
	LPDISPATCH GetCtrlMan()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetUtility()
	{
		LPDISPATCH result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetSoundMaster()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetCoordSys()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetApplication()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void CopyToClipboard()
	{
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL SaveImage(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL DoSaveImage(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	void SetFocus()
	{
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long CreateScriptMan()
	{
		long result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long EvaluateScript(LPCTSTR Script, long Len, LPCTSTR Title, long LineNumber)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Script, Len, Title, LineNumber);
		return result;
	}
	void DestroyScriptMan()
	{
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH GetSKMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void MoveControl(long X, long Y, long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y, Width, Height);
	}
	void Register_TimerEvent(long Interval, long Continue_Event, long ID)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Interval, Continue_Event, ID);
	}
	void Unregister_TimerEvent(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	void Print()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

protected:
	BOOL m_bMapCreated;
	BOOL m_bRefreshAdminOnlyCenterPos;

public:
	class CSmartSRXCtrl *m_pSmartSRXPtr;

	bool bCreateLevelBar;
	bool bCreateToolBarStyle1;
	bool bCreateToolBarStyle2;

	CXCtrlMan ctrlman;
	CXMapMan mapman;
	CXThemeMan thememan;
	CXAdminMan adminman;
	CXControlState ctrlstate;
	CXPOIMan poiman;
	CXUtility util;
	CXImageMan imageman;
	CXLayerMan layerman;
	CXUIMan uiman;
	CXApplication app;
	CString m_strWEB_IMAGE_PATH;
	CString m_strWEB_IMAGE_PATH1;

	int lThemeType;
	int maxLogicalLevel;
	int minLogicalLevel;


	CXUIStaticText stcMsgArea;
	CXUIPanel bPanel;
	

	CXRouteFlag sFlag;
	CXRouteFlag eFlag;
	CXUIButton btnLevle[12];
	CXUIButton mLevelBarBg;
	CXUIButton bLevel[13];
	CXUIButton bLevelBarBg;
	CXUIButton MyToolBar2[22];
	CXMagicImageList m_imgCarStart;
	CXMagicImageList m_imgCarEnd;
	CXMagicImageList m_imgCarVia;

	CString appPath;
	CString sDefaultPath;
	CRegionSelectAdvancedDlg *m_pRegionSelectDlg;
	BOOL m_bPrepareImage;
	BOOL m_bLButtonDown;
	BOOL m_bChangeCenterPos;
	CXRouteFlag  m_sFlag, m_eFlag;
	BOOL m_bNotCreateToolBar;
	BOOL m_bNotCreateAddressBar;

	afx_msg virtual void OnCreateMap(long Value);
	afx_msg virtual void OnUIClickMap(LPDISPATCH Obj, long Flag, long X, long Y);
	afx_msg virtual void OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y);
	afx_msg virtual void OnStateChange(long Code, long Value1, long Value2);
	afx_msg virtual void OnMouseDown(long Flag, long X, long Y);
	afx_msg virtual void OnMouseMove(long Flag, long X, long Y);
	//afx_msg virtual void OnPOIMouseHover(CXPOIItem item);
	//afx_msg virtual void OnPOIMouseLeave(CXPOIItem item);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PrepareImage();
	virtual void OnChangeMapLevel() {};

	void MapLevel_Master(long level);
	void ShowLandMakkSymbol(long value);
	void CreateLevelBar();
	void CreateToolBarUI();
	void Map_ZoomIn();
	void Map_ZoomOut();
	void OnMapRotaion();
	void OnSmHistoryprev();
	void OnSmHistorynext();
	void OnSmTextView();
	void OnSmMakeCircle();
	void OnCheckArea();
	void OnCheckDistance();
	void OnSmBirdview();
	void OnSm3Dview();
	void OnSmClipboard();
	void OnSmImagesave();
	void OnPolygon();
	void OnPolyline();
	void OnObjectModify();
	void OnRemovePolygon();
	void OnAddAddressBar();
	CString GetAdminName(int nLevel = 4, BOOL bUseUserPos = FALSE, long nPosX = 0, long nPosY = 0);
	BOOL GetAdminName(CString &strSido, CString &strGugun, CString &strDong, CString &strLi, CString strAdminName = "");
	void ShowRegionSelectDlg();
	static int STRTOK2(char *delimiter, char *src, int nStart, ...);
	CString MakeRegionCombo(CString strAdminCode, CComboBox &cmbTarget, CString strSelectName);
	void RefreshAdminInfo(BOOL bForceRefresh = FALSE, BOOL bUIBarOnly = FALSE, long nPosx = 0, long nPosY = 0);
	void MoveMapFormCode(CString strCode, long nType = 0);
	void MoveMap(CPOIUnit *pPOI);
	void MoveMap(long nPosX, long nPosY);
	void MoveMap(int nPosX, int nPosY);
	void MoveMap(double dPosX, double dPosY);
	void LoadWebImage(CString strFileName, CString strName = "", CString strDefaultPath = WEB_IMAGE_PATH);
	void LoadLocalImage(CString strFileName, CString strName = "", CString strDefaultPath = LOCAL_IMAGE_PATH);
	CXMagicImageList LoadLocalImageList(CString strFileName, long nWidth, long nHeight, CString strName = "", CString strDefaultPath = LOCAL_IMAGE_PATH);
	CXPOIItem AddPOI(CString strImage, long nImageIndex, CString strCaption, UINT nGroupID = 1, UINT nPOIID = -1,
				long nPosX = 0, long nPosY = 0, CString strContents = "", UINT nStyleID = 1,
				BOOL bShowCaption = 1, BOOL bShowImage = 1, long nData = 0, long nAlpha = 0,
				BOOL bNoEvent = FALSE);

	BOOL IsPosUsable(long &nPosX, long &nPosY, BOOL bDontChange = FALSE, BOOL bWGS84ToBessel = FALSE);
	CXPOIItem GetPOI(UINT nGroupID, UINT nPOIID, BOOL *pbNew = NULL);
	CXPOIItem GetPOIIfExist(UINT nGroupID, UINT nPOIID);
	CXPOIGroup GetPOIGroup(UINT nGroupID);
	CXMapPos GetMapPos(long nPosX, long nPosY);
	CXPOIStyle GetPOIStyle(long nStyleID = 1, long nAlpha = 0);
	void GetCenterPos(long &nPosx, long &nPosY);
	CXMagicImage GetPOIImage(CString strImage);
	long GetMapLevel();
	CXLayer GetLayer(long nLayer);
	void SetPOIVisibleAsc(CXPOIItem item, long nMaxLevel = MAP_MAX_LEVEL);
	void SetPOIVisibleDec(CXPOIItem item, long nMinLevel = 0);
	long GetMapLevelMin() { return 0;}
	long GetMapLevelMax() { return MAP_MAX_LEVEL;}
	CXUIImage SetUIImage(long nID, CString strImage, CRect rc, long nAlpha, long nAnchor, long nEvent);
	long GetValue(CString strValue);
	long GetMapCX();
	long GetMapCY();
	BOOL SearchRoute(long nType, long nPosX = 0, long nPosY = 0, BOOL bShowImage = TRUE);
	CXUIStaticText AddUIStaticText(CXUIImage parent, long nID, CString strText, CRect rcBound, COLORREF crFont = RGB(0, 0, 0),
		long nFontHeight = 12, CString strFont = "돋움", long nEvent = 0);

	long GetRouteDistance();
	static BOOL RegisterMapDll();
	static CString GetModuleFullPath();

	void KatecToBessel(long &nPosX, long &nPosY);
	void WGS84ToBessel(long &nPosX, long &nPosY);
	void BesselToWGS84(long &nPosX, long &nPosY);
	void SetNotCreateToolBar();
	void SetNotCreateAddressBar();
	void DeletePOI(int nGroup, int nID = -1);
	void CreateWait();
	void SetRefereshAdminState(BOOL bOnlyCenterPos = TRUE);	//중심이동인 경우만 admin변경, 마우스이동 무시함

	BOOL m_bInitSRXItem;
	void InitSRXItem();

};
