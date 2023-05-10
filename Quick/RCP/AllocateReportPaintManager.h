#pragma once



#define RIDERWND_WIDTH		138
#define RIDERWND_HEIGHT		85
#define DISPLAY_COUNT		3
#define ROW_HEIGHT			15

#define AB_SHARE_RIDER		-1
#define AB_MY_RIDER			-2


struct TRS_CONTROL
{
	int			nCompany;
	int			nRNo;
	CString		strID;
	CString		strName;

	CButton*	pButtonTalk;
	CButton*	pButtonMode;
	CRect		rcButton;

	~TRS_CONTROL()
	{
		if(pButtonMode != NULL)
		{
			pButtonMode->DestroyWindow();
			delete pButtonMode;
		}

		if(pButtonTalk != NULL)
		{
			pButtonTalk->DestroyWindow();
			delete pButtonTalk;
		}

	}
};

typedef struct {
	long nCompany;
	long nRNo;
	long nState;
	CString strStart;
	CString strDest;
	COleDateTime dtTime;
	long nCharge;
	int nWayType;
	int nCarType;
	BOOL bOtherOrder;
	long nTNo;
	long nRunType;
} ALLOCATE_ORDER_INFO;

typedef struct {
	long nCompany;
	long nRNo;
	CString strName;
	CString strPhone;
	long nCarType;
	long nAllocCount;
	long nPickupCount;
	long nFinishCount;
	long nTotalCount;
	long nTotalCharge;
	long nRiderColor;
	long nRiderTextColor;
	int x;
	int y;
	long nAllocGroup;
	CString strCurPosName;
	COleDateTime dtPos;
	int nWorkReportState;
	COleDateTime dtAttend;
	COleDateTime dtLeave;
	long nPosX;
	long nPosY;
	long nScore;
	long nStartDistanceScore;
	double fOrderCountScore;
	long nDirectionScore;
	long nAngleScore;
	BOOL bGpsPos;
	BOOL bDelayRider;
	BOOL bShareRider;
	BOOL bShareRiderHaveMyOrder;
	long nHomeDongID;
	CString strHomeDong;
	double fOrderDistance;
	COleDateTime dtLastAction;
	BOOL bLogin;
	COleDateTime dtLogInOut;
} ALLOCATE_BOARD_RIDER_INFO;

typedef struct {
	CRect rc;
	long nTNo;
} ORDER_RECT;


typedef multimap<std::pair<long,long>, ALLOCATE_ORDER_INFO> ALLOCATE_ORDER_MAP;
typedef vector<ALLOCATE_BOARD_RIDER_INFO*> ALLOCATE_RIDER_VECTOR;
typedef map<std::pair<long,long>, ALLOCATE_BOARD_RIDER_INFO*> ALLOCATE_RIDER_MAP;
typedef vector<ORDER_RECT> ORDER_RECT_VECTOR;


class CMyRecordItem : public CXTPGridRecordItemText
{
public:
	CMyRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}

public:
	ALLOCATE_BOARD_RIDER_INFO *pAllocRiderInfo;
	ORDER_RECT_VECTOR vecOrderRect;
};


class CAllocateReportPaintManager : public CXTPGridPaintManager
{
	friend class CXTPGridControl;

public:
	CAllocateReportPaintManager();
	virtual ~CAllocateReportPaintManager();


public:
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

	void DrawTextLine(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
						CRect rcItem, int nFlag, int& nCharCounter, int& nHyperlikCounter);

	int DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign = DT_LEFT);

	int DrawLink(int* pnCurrDrawPos, XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
						CString strText, CRect rcLink, int nFlag);

	virtual int GetRowHeight(CDC* pDC, CXTPGridRow* pRow);

	void SetDisplayCount(UINT nCount) { m_nDisplayCount = nCount; }
	void SetOrderTimeType(int nType) { m_nOrderTimeType = nType; }
	void SetOrderStateType(int nState) { m_nOrderState = nState; }
	void SetShowPhoneAlways(BOOL bShow) { m_bShowPhoneAlways = bShow; }
	void ResortRider(long nType, long nCarShowType = 0, long bOtherRiderShowType = 0);
	void SetWideColumn(BOOL bWideColumn) { m_bWideColumn = bWideColumn; }
	void SetShowRiderPos(BOOL bShow) { m_bShowPosName = bShow; }
	void SetDisplayAttendLeave(BOOL bShow) { m_bDisplayAttendLeave = bShow; }
	void ShowProperRiderScore(BOOL bShow) { m_bShowProperRiderScore = bShow;}
	void SetLinearType(BOOL bLinearType) { m_bLinearType = bLinearType;}
	BOOL HitTest( CPoint pt, TRS_CONTROL** pTRSResult );
	CString GetWString(CString strItem, long nLeft);	

public:

	CFont* m_pSmallFont;
	CFont* m_pLargeFont;
	static CImageList m_imgList;
	static CImageList m_imgListCarType;
	static CImageList m_imgListTRS;

	static CBrush m_WhiteBrush;
	static CBrush m_GreenBrush;
	static CBrush m_GreenBrush2;
	static CBrush m_BlueBrush;

	ALLOCATE_ORDER_MAP m_mapOrder;
	ALLOCATE_RIDER_VECTOR m_vecRider;
	ALLOCATE_RIDER_MAP m_mapRider;

	long m_nDisplayCount;
	long m_nOrderTimeType;
	long m_nOrderState;
	BOOL m_bShowPhoneAlways;
	BOOL m_bWideColumn;
	BOOL m_bShowPosName;
	BOOL m_bDisplayAttendLeave;
	BOOL m_bShowProperRiderScore;
	BOOL m_bLinearType;

	COLORREF m_crDelayRiderBack;
	COLORREF m_crOtherOrderText;
	COLORREF m_crOtherOrderBack;
	COLORREF m_crOtherRiderText;
	COLORREF m_crOtherRiderBack;
};
