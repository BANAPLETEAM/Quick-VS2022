#pragma once



typedef struct {
	long nPosX;
	long nPosY;
	DWORD dwTick;
} RIDER_TAIL_INFO;



#define RIDER_TAIL_COUNT	30


class CRiderSubInfo
{
public:
	CRiderSubInfo(void);
	~CRiderSubInfo(void);

public:
	long nCompany;
	long nRNo;
	CCarType cartype;
	long nTruckType;
	CString strTon;
	COleDateTime dtUpdate;
	long nHavingOrder;
	long nCompleteOrder;
	long nAllocOrderCount;
	long nPickupOrderCount;
	long nMyOrderCount;
	long nChargeSum;
	double fAngle;
	double fDistance;
	double fArrowDistance;
	BOOL bActive;
	long nTmX;
	long nTmY;
	COleDateTime dtState;
	long nState;
	int nColorIndex;
	BOOL bSupportRider;
	CString strHasOrderList;
	CString strName;
	CString strPosName;
	CString strPhone;
	CString strCity;
	CString strContents;
	BOOL bOtherRider;
	BOOL bRealtimeOtherRider;
	
	long nPosX;
	long nPosY;
	RIDER_TAIL_INFO tail[RIDER_TAIL_COUNT];

protected:
	BOOL m_bSkipPrePos;
	long m_nTailIndex;
	long m_nTailPloygonID;
	CXTPGridRecord *m_pRecord;
	BOOL m_bGpsSignalError;

public:
	void AddPos(long nPosX, long nPosY);
	BOOL GetPrevPos(long &nPosX, long &nPosY, long nSteps = 0, long nMaxElapsedSec = 0xFFF);	//0은 현재, 1은 그전, 2는 그그전
	long GetTailIndex(long nPos, BOOL bNext = TRUE);
	long GetPrevStepIndex(long nSteps);
	void SetTailPloygonID(long nPloygonID);
	long GetTailPolygonID();
	BOOL SetRecordVisible(BOOL bVisible);
	void SetReportRecord(CXTPGridRecord *pRecord) { m_pRecord = pRecord; }
	CXTPGridRecord *GetRecord() { return m_pRecord; }
	BOOL IsGpsSignalError();
	int IsFaraway(long nPosX, long nPosY, long nPosX2, long nPosY2, int nAboutValue, int nFarMeter);
	BOOL IsSkipPos(long nPosX, long nPosY);
};


typedef std::map<std::pair<long, long>, CRiderSubInfo> CRiderSubInfoMap;
