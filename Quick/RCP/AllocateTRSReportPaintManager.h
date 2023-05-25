#pragma once


#define RIDERWND_WIDTH		138
#define RIDERWND_HEIGHT	130
#define DISPLAY_COUNT2		3
#define ROW_HEIGHT			15


using namespace std;


typedef struct {
	long nCompany;
	long nRNo;
	long nState;
	CString strStart;
	CString strDest;
	COleDateTime dtTime;
	long nCharge;
	BOOL nWayType;
} ALLOCATE_ORDER_INFO2;

typedef struct {
	long nCompany;
	long nRNo;
	CString strName;
	CString strPhone;
	long nAllocCount;
	long nFinishCount;
	long nTotalCount;
	long nTotalCharge;
	long nWorkState;
	COleDateTime dtLastAck;
	COleDateTime dtAttend;
	COleDateTime dtLeave;
	CString strCurPosName;
	COleDateTime dtPos;
	COleDateTime dtLastAction;
	int nAttendType;
	long nPosX;
	long nPosY;
	BOOL bGpsPos;
	long nAllocateLimitMin;
	BOOL bOfficeLine;
	BOOL bConnRider;
	CString strGroupName;
	CString strWaitOrder;
	long nPenaltyLevel;
	long nLine;
} ALLOCATE_BOARD_RIDER_INFO2;


typedef multimap<std::pair<long,long>, ALLOCATE_ORDER_INFO2> ALLOCATE_ORDER_MAP2;
typedef vector<ALLOCATE_BOARD_RIDER_INFO2*> ALLOCATE_RIDER_VECTOR2;
typedef map<std::pair<long,long>, ALLOCATE_BOARD_RIDER_INFO2*> ALLOCATE_RIDER_MAP2;


class CMyRecordItem2 : public CXTPGridRecordItemText
{
public:
	CMyRecordItem2(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}

public:
	ALLOCATE_BOARD_RIDER_INFO2 *pAllocRiderInfo;
};


class CAllocateTRSReportPaintManager : public CXTPGridThemeResource
{
	friend class CXTPGridControl;

public:
	CAllocateTRSReportPaintManager();
	virtual ~CAllocateTRSReportPaintManager();


public:
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);

	void DrawTextLine(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
						CRect rcItem, int nFlag, int& nCharCounter, int& nHyperlikCounter);

	int DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign = DT_LEFT);

	int DrawLink(int* pnCurrDrawPos, XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
						CString strText, CRect rcLink, int nFlag);

	virtual int GetRowHeight(CDC* pDC, CXTPGridRow* pRow);

	void SetDisplayCount(UINT nCount) { m_nDisplayCount = nCount; }
	void SetOrderTimeType(int nType) { m_nOrderTimeType = nType; }
	void SetOrderStateType(int nState) { m_nOrderState = nState; }
	void SetShowPhoneAlways(BOOL bShow) { m_bShowPhoneAlways = bShow; }
	void ResortRider(long nType = 0);
	void GetRiderStateColor(ALLOCATE_BOARD_RIDER_INFO2 *pRider, COLORREF &crTop, COLORREF &crSecondTop, COLORREF &crBack);

public:
	static CImageList m_imgList;

	ALLOCATE_ORDER_MAP2 m_mapOrder;
	ALLOCATE_RIDER_VECTOR2 m_vecRider;
	ALLOCATE_RIDER_MAP2 m_mapRider;

	long m_nDisplayCount;
	long m_nOrderTimeType;
	long m_nOrderState;
	BOOL m_bShowPhoneAlways;

	COLORREF m_crPenalty[5];
};
