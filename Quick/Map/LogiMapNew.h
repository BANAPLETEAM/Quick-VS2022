#pragma once


#include "LogiMapBase.h"
#include "RiderSubInfo.h"


enum MAP_STYLE { LOGI_MS_SIMPLE = 0, LOGI_MS_CONTROL, LOGI_MS_TRACE, LOGI_DISTRIBUTION_MAP};
enum POI_GROUP_TYPE { POINT_POI = 0xFFFF, TRACE_POINT_POI = 0xFFFE, 
				TRACE_RIDER_HAS_ORDER_START = 0xFFFD, TRACE_RIDER_HAS_ORDER_DEST = 0xFFFC};
enum LAYER_TYPE { TRACE_LAYER = 0xFFFF, IN_BOUND_LAYER = 0xFFFE, RIDER_MOVE_BOUNDARY_LAVER = 0xFFFD,
				RIDER_START_DEST_LAYER = 0xFFFC, RIDER_TAIL_LAYER = 0xFFFB};
enum REGION_TYPE { RT_ALL, RT_SIDO, RT_GUGUN, RT_DONG, RT_ADDR};
enum REGION_CHANGE_DISPLAY_TYPE { RCD_NONE = 0, RCD_COMBO, RCD_EDIT};

#define LAYER_VIA 220
#define LAYER_POI 221

extern bool mci_greator(ST_RIDER_POS_INFO elem1, ST_RIDER_POS_INFO elem2);

typedef struct {
	long nCompany;
	long nRNo;
} RIDER_KEY;

typedef struct {
	long nPosX;
	long nPosY;
	COleDateTime dt;
	int nHasOrderCount;
	int nChargeSum;
} TRACE_INFO;

typedef std::vector<RIDER_KEY> RIDER_KEY_VECTOR;
typedef std::map<std::pair<long, long>, UINT> CRiderPosDupCountMap;


class CLogiMapNew : public CLogiMapBase
{
	DECLARE_DYNCREATE(CLogiMapNew)

public:
	CLogiMapNew(void);
	~CLogiMapNew(void);

	afx_msg virtual void OnCreateMap(long Value);
	afx_msg virtual void OnMouseDown(long Flag, long X, long Y);
	afx_msg virtual void OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y);

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	DWORD m_dwMapStyle;
	RIDER_KEY m_TraceRider;
	BOOL m_bTraceMode;
	BOOL m_bTraceHasTail;
	BOOL m_bDrawRiderMoveBoundary;
	DWORD m_dwLastChangeRegion;
	CRiderSubInfoMap m_mapRiderSub;
	RIDER_KEY m_RClickRider;
	//BOOL m_bRealTimeTrace;
	//BOOL m_bShowOneRider;
	void *m_pTraceRecord;
	BOOL m_bSimulationMode;
	BOOL m_bShowCurHasOrder;
	ARRAY_RIDER_POS_OFFSET_INFO m_arrRiderPosOffset;
	CRiderPosDupCountMap m_mapRiderPosDupCount;
	long m_nShowSmallSizeLevel;
	long m_nRegionChangeDisplayType;
	CEdit *m_pedtRegionDisplay;
	BOOL m_bShowRiderCaption;
	BOOL m_bShowOrderCaption;
	BOOL m_bRiderColorManual;
	BOOL m_bPrepareImage;
	BOOL m_bCheatMode;
	BOOL m_bAllowRightKeyPOIDelete;
	CXUIStaticText m_uistcMsg;
	BOOL m_bUseRearrange;
	long m_nRiderTailShowTime;
	BOOL m_bTraceMapMove;
	BOOL m_bDisableCarAlpha;

	virtual BOOL PrepareImage();
	virtual void OnChangeMapLevel();

	CXPOIItem AddPointPOI(BOOL bPosChange, CString strCaption, long nPosX, long nPosY,
		CString strContents = "", CString strImageName = "POINT", long nImageIndex = -1, 
		long nGroupID = POINT_POI, long nIndex = -1, long nData = 0, long nAlpha = 0,
		BOOL bNoEvent = FALSE);
	void AddCarPOI(BOOL bPosChange, long nCompany, long nRNo, CString strRName, long nPosX, long nPosY,
		CCarType &cartype,
		CString strCaption = "", CString strContents = "", CString strImageName = "", long nImageIndex = -1,
		COleDateTime dtUpdate = COleDateTime::GetCurrentTime());
	void AddCarPOI(BOOL bPosChange, CRiderSubInfo &subinfo);

	inline CString GetCarImageName(long &nListIndex, 
		CCarType &cartype,
		double fAngle, BOOL bActive = TRUE, 
		int nHavingOrder = 0,  BOOL bWait = FALSE, 
		COleDateTime dtAllocate = COleDateTime::GetCurrentTime(),
		int nColorIndex = 0, BOOL bSupportRider = FALSE,
		BOOL bGpsError = FALSE);

	inline CString GetCarImageName(long &nListIndex, CRiderSubInfo &info);
	inline CString GetCarTypeImage(long nCarType);
	void MakePosOffsetInfo();
	void SetMapLevel(int nLevel);
	void MoveMapRider(long nCompany, long nRNo);
	void RearrangeDupPosPOI();
	void RedrawPointPOI();
	CString GetPointImageName();
	void RefreshCarState();

#ifdef _DAERI
	void UpdateRiderOrderState(long nCompany, long nRNo, long nState, long nCharge, BOOL bClear = FALSE);
#else
	void UpdateRiderOrderState(long nCompany, long nRNo, long nState, long nCharge, 
							COleDateTime dtState, CString strStart, CString strDest, BOOL bClear = FALSE);
	void UpdateRiderOrderState(long nCompany, long nRNo, long nAllocOrderCount, long nPickupOrderCount, 
		long nHavingOrder, long nCompleteOrder, long nChargeSum, CString strHasOrderList);

#endif
	void DeleteAllRider();
	void DrawRiderStartDestLine(long nCompany, long nRNo, 
			long nStartPosX, long nStartPosY, long nDestPosX = 0, long nDestPosY = 0);
	void ClearAllLayer(BOOL bExceptPointPOI = FALSE);
	//void ShowOneRider(long nCompany, long nRNo, BOOL bShow = TRUE);
	BOOL IsCarPOI(CXPOIItem item) { return ((CXPOIGroup)item.GetGroup()).GetID() < 0xF000; }
	void TraceMode(BOOL bTrace, long nCompany = 0, long nRNo = 0, BOOL bTraceHasTail = FALSE, BOOL bTraceMapMove = TRUE);
	void ShowRiderCaption(BOOL bShow);
	void ShowOrderCaption(BOOL bShow);
	BOOL IsVisibleRiderCaption();
	BOOL IsVisibleOrderCaption();
	void SetRiderColorManual(BOOL bManual);
	void SetRClickRider(long nCompany, long nRNo) { m_RClickRider.nCompany = nCompany; m_RClickRider.nRNo = nRNo;}
	void GetRClickRider(long &nCompany, long &nRNo) { nCompany = m_RClickRider.nCompany; nRNo = m_RClickRider.nRNo;}
	void EnableDrawRiderMoveBoundary(BOOL bEnable) { m_bDrawRiderMoveBoundary = bEnable;}
	void SetSimulationMode(BOOL bMode) { m_bSimulationMode = bMode; if(m_pTraceRecord) delete m_pTraceRecord; m_pTraceRecord = NULL;}
	void AddTracePos(long nPosX, long nPosY, COleDateTime dtLog, BOOL bHasTail = FALSE, BOOL bMoveMap = FALSE, BOOL bDotLine = FALSE);
	long AddTracePointPOI(long nPosX, long nPosY, COleDateTime dtLog,
		CString strContents = "", CString strImageName = "", BOOL bAlwaysShow = TRUE);
	void DrawTraceLayer(long nPosX, long nPosY, COleDateTime dtLog, long nCurID, BOOL bDrawArrow = FALSE, BOOL bDotLine = FALSE);
	void DrawRiderMoveBoundary(BOOL bResizeMap = TRUE);
	void SetTraceRecord(void *pRecord) { m_pTraceRecord = pRecord; }
	void *GetTraceRecord() { return m_pTraceRecord; }
	void DeleteTraceRiderHasOrder();
	void AddTraceRiderHasOrder(BOOL bShowCurHasOrder, 
		long nTNo, long nState, CString strStart, CString strStartDong, long nStartX, long nStartY, 
		CString strDest, CString strDestDong, long nDestX, long nDestY,
		COleDateTime dtAllocate, COleDateTime dtPickup, COleDateTime dtFinish);

	void CreateTraceCancelBar();
	void DeleteTraceCancelBar();
	CString MakeHintString(CRiderSubInfoMap::iterator &it);
	CRiderSubInfo* GetRiderSubInfo(long nCompany, long nRNo);
	void RedrawRiderCaption();
	void SetRiderTailShowTime(long nShowTime);	//sec
	void MakeRiderTail(CRiderSubInfo &info, long nCompany, long nRNo, CXPOIItem item);
	void DeleteRiderTail(long nCompany, long nRNo);
	long GetCarAlphaValue(CRiderSubInfo &subInfo);
	CString GetTruckSimilarTonForImage(CString strTon);

	void DrawRouteInfo(CXRouteInfo4 *info4, CNS_POINT_ARRAY *pPointArray);
	void DrawRouteInfo(vector<CPoint> *vec, CNS_POINT_ARRAY *pPointArray);
};



AFX_INLINE void CLogiMapNew::ShowRiderCaption(BOOL bShow)
{
	m_bShowRiderCaption = bShow;
}

AFX_INLINE void CLogiMapNew::ShowOrderCaption(BOOL bShow)
{
	m_bShowOrderCaption = bShow;
}

AFX_INLINE BOOL CLogiMapNew::IsVisibleRiderCaption()
{
	return m_bShowRiderCaption;
}

AFX_INLINE BOOL CLogiMapNew::IsVisibleOrderCaption()
{
	return m_bShowOrderCaption;
}

AFX_INLINE void CLogiMapNew::SetRiderColorManual(BOOL bManual)
{
	m_bRiderColorManual = bManual;
}
