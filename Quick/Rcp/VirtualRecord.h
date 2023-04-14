#pragma once


 
typedef enum {
	STRING_SORT = 0,
	NUMBER_SORT = 1,
	DATE_SORT = 2
} SORT_TYPE;

typedef struct{
	long nIndex;
	long nTNoSet;
} TREE_ORDER_TYPE;

static const char *header_string[] = {"번호", "소속", "접수번호", "상태", "회사명", 
									"의뢰지동", "부서명", "발신전화번호", "담당전화", "출발지고객명", 
									"출발지담당", "도착지고객명",	"도착지담당", "출발지역", "출발동", 
									"도착지역", "도착동", "날짜", "시간", "접수경과", 
									"왕복", "긴급", "차량", "지불", "탁송", 
									"기사", "기사명", "접수자", "기본", "추가", 
									"할인", "요금", "운행료", "개별", "배차", 
									"픽업", "배차경과", "완료", "적요", "담당자", 
									"물품", "그룹명", "그룹부서명", "DNIS", "수수료율", 
									"기사입금액", "출발지상세위치", "도착지상세위치", "구분", "고객메모",
									"출발지전화", "도착지전화", "이용횟수", "배차방식", "연계", 
									"예약", "입금액", "의뢰지주소", "의뢰지위치", "승인번호", 
									"거리", "접수타입", "업체부담금", "최초접수", "기사반납금",
									"상세정보", "고객번호", "출발지주소", "도착지주소", "사용마일리지",
									"적립예정마일리지", "보정요금"};

static const int header_align[] = {1, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 
								0, 0, 1, 0, 1, 
								1, 1, 1, 1, 0, 
								0, 0, 0, 2, 2, 
								2, 2, 2, 0, 0, 
								0, 0, 0, 0, 0, 
								0, 0, 0, 1, 0, 
								2, 0, 0, 0, 0, 
								0, 0, 2, 0, 2, 
								2, 2, 0, 0, 0, 
								0, 0, 2, 1, 2,
								1, 2, 0, 0, 2,
								2, 2};

static const int header_width[] = {45, 70, 70, 45, 150, 
								60, 70,	80, 80, 150, 
								70, 150, 70, 70, 70, 
								70, 70, 60, 45, 45, 
								45, 45, 45, 45, 45, 
								60, 60, 50, 50, 50, 
								60, 60, 50, 50, 50, 
								60,	50,	300, 100, 50, 
								80, 60, 60, 60, 60,
								60, 150, 150, 45, 150, 
								150, 150, 60, 80, 60, 
								70, 60,	100, 100, 60, 
								40, 60, 70, 90, 60,
								60, 60, 80, 80, 60,
								60, 60};

static const char *szOrderField[] = {"No", "nCompany", "nTNo", "nState", "sCName",
									"sODong", "부서명", "sCid",	"sOPhone", "sSName", 
									"sSManager", "sDName", "sDManager", "sStartGugun", "sSDong", 
									"sDestGugun", "sDDong", "dt1", "dt1", "nElapsed", 
									"nWayType", "nRunType", "nCarType", "nPayType", "nTransOrder", 
									"nRNo", "sRName", "nWNo", "nChargeBasic", "nChargeAdd", 
									"nChargeDis", "nChargeSum", "nChargeDriving", "dt2", "dt3", 
									"dt4", "nElapsedAlloc", "dtFinal", "sEtc", "sManager", 
									"sItemType", "nGNo", "sDept", "nDNIS", "nDepositRate",
									"nFinalRiderDeposit", "sSDetail", "sDDetail", "구분", "sMemo", 
									"sSPhone", "sDPhone", "nUseCount", "bRiderOnlyMan", "nConsignSum", 
									"dtReserve", "nDeposit",	"sOAddress" , "sODetail", "sOkNumber", 
									"nDistanceMK", "nRcpType", "nChargeLogi", "dt0", "nChargeReturn",
									"bSentPickupSms2", "sSAddress", "sDAddress", "nChargeRiderAuto",
									"nMileage", "nChargeRevision"};

static const int header_sort_type[] = {1, 0, 1, 1, 0, 
									0, 0, 0, 0, 0, 
									0, 0, 0, 0, 0, 
									0, 0, 2, 2, 1, 
									0, 0, 0, 0, 1, 
									1, 0, 0, 1, 1, 
									1, 1, 1, 0, 0, 
									1, 0, 0, 0, 0, 
									0, 0, 0, 0, 1,
									1, 0, 0, 0, 0, 
									0, 0, 1, 0, 1, 
									2, 1, 0, 0, 0, 
									1, 0, 1, 2, 1,
									0, 0, 0, 0, 1,
									1, 1};

#define RCP_NO 0
#define RCP_COMPANY_COL 1
#define RCP_TNO_COL		2
#define RCP_STATE_COL	3
#define RCP_CUSTOMER_COL	4
#define RCP_DEPART_COL	6
#define RCP_CID_COL	7
#define RCP_PHONE_COL	8
#define START_COMPANY_COL	9
#define DEST_COMPANY_COL	11
#define START_GUGUN_COL	13
#define START_DONG_COL	14
#define DEST_GUGUN_COL	15
#define DEST_DONG_COL	16
#define RCP_TIME_COL	17
#define RCP_RESERVE_COL	18
#define RCP_ELAPSED_COL 19
#define RUN_TYPE_COL 21
#define PAY_TYPE_COL 23
#define TRANS_COL	24
#define RIDER_NO_COL	25
#define RIDER_NAME_COL	26
#define WNO_COL			27
#define CHARGE_COL			31
#define CHARGE_DRIVING_COL			32
#define ALLOC_ELAPSED_COL			36
#define ETC_COL			38
#define MANAGER_COL			39
#define RCP_GNO_COL	41
#define RCP_GNO_DEPT_COL	42
#define CUTOMER_MEMO_COL	49
#define USE_COUNT_COL	52
#define RIDER_ALLOCATE_COL	53
#define CONSIGN_SUM_COL	54
#define RESERVE_COL	55
#define DEPOSIT_COL	56
#define O_ADDRESS_COL 57
#define O_DETAIL_COL 58
#define RCP_CARD_OK_NUMBER_COL 59
#define RCP_DISTANCE_COL 60
#define RCP_TYPE_COL 61
#define RCP_LOGI_CHARGE_COL 62
#define PENALTY_CHARGE_COL 0
#define RCP_DT0 63
#define RCP_CHAGEGE_RETURN_COL 64
#define RCP_ALL_BARO_COL 65
#define CUSTOMER_ID_COL 66
#define CHARGE_REVISION_COL 71

#define MAX_COLUMN	72


typedef struct {
	string info[MAX_COLUMN];
	long nTNo;
	int nState;

	int nCarType;
	int nRunType;
	int nWayType;
	int nPayType;

	long nCompany;
	long nRiderCompany;
	int nShareLevel;
	int nStartSection;
	long nRNo;
	long nUseCount;
	long nStartRealDongID;
	long nDestRealDongID;

	long nCharge;
	int nWNo;
	long nWCompany;
	string strCName;
	string strOPhone;
	string strSPhone;
	string strDPhone;
	string strOMobile;
	string strSMobile;
	string strDMobile;

	string strEtc;
	string strStart;
	string strDest;
	COleDateTime dtRcp;
	COleDateTime dtState;
	COleDateTime dtLast;
	COleDateTime dt3;
	COleDateTime dt4;
	COleDateTime dtFinal;
	COleDateTime dtSort;
	BOOL bCross;
	long nShareCompany;
	long nCorporationID;
	string strSName;
	string strDName;

	long nStartPosX;
	long nStartPosY;
	long nDestPosX;
	long nDestPosY;	
	BOOL bTwoWay;
	BOOL bInternet;
	long nDistanceKM;
	long nCNo;
	long nSCNo;
	long nDCNo;
	int nReserveAfter;
	BOOL bScheduleOrder;
	long nReserveSortNumber;
	BOOL bShareOrder;
	long nSignType;
	CString strItemType;

	string strSAddress;
	string strDAddress;
	string strSDetail;
	string strDDetail;

	BOOL nTransOrder;
	BOOL bTodayOrder;

	long nGNo;
	long nDeposit;

	BOOL bRiderOkOnlyMan;
	BOOL bRiderAllocate;
	BOOL bRiderPickUp;
	BOOL bRiderFinish;

	BOOL bOfficeOkOnlyMan;

	long nShareCode1;
	long nRiderShareCode1;

	string strRName;
	string strWName;
	long nChargeTrans;

	int nDepositRate;
	int nFinalDepositRate;

	BOOL bClientShare5;
	long nTNoSet;
	BOOL bParentOrder;
	BOOL bMyOrder;
	
	COleDateTime dt0;

	int nTruckType;
	string strTon;
	int nLoadType;
	int nBillDraw;

	int nCreditCardType;
	int nDNIS;
	long nConsignTNo;
	CString sConsignDestSido;
	long nConsignWayID;
	long nRiderAllocate;

	COleDateTime dtReserve;
	long nCardOkAmt;
	long nDaeriCode;
	long nCTNo;
	long nChargeDriving;
	long nChargeCompany;
	BOOL bReserved;
	BOOL bStartWaitInquiryReceipt;
	
	COleDateTime dtDelayNotice;
	BOOL bFoodOrder;
	COleDateTime dtFoodComplete;
	BOOL bAutoWait;
} OrderRecord;

typedef struct {
	long nIndex;
	char *pszData;
	COleDateTime *pdtData;
	long nData;
	BOOL bStateSecondSort;
	long nState;
	long nTNo;
} ArrangeIndex;


typedef map<long, long> MAP_ORDER_STATE_SECOND_SORT_MAP;
typedef vector<long> RiderOrder;
typedef map<long, RiderOrder> MAP_RIDER_OWN_CALL2;  // 기사유니코드 , nTNo
typedef map<long, long> MAP_ORDER_OWN_RIDER;     


typedef map<long, OrderRecord> OrderRecordList;
typedef map<long, long> OrderIndex; // nTNo, 기사유니코드


class CMyReportControl;

class CVirtualRecord :
	public CXTPGridRecord
{
public:
	CVirtualRecord();
	~CVirtualRecord(void);

public:
	static MAP_ORDER_STATE_SECOND_SORT_MAP m_mapSecondSort;

protected:

	//virtual record간에 공유되는 정보
	
	static long m_nSelectRow;
	static long m_nCompanyCode;
	static long m_nDOrderCompany;
	static long m_bIntegrated;
	static long m_nRcpTimeCol;
	static long m_nStartCol;
	static long m_nRcpTimeColor1;
	static long m_nRcpTimeColor2;
	static long m_nRcpTimeColor3;
	static long m_nUseCountCol;
	static BOOL m_bUseNewRegion;
	static long m_nPayTypeCol;
	static CMyReportControl *m_pMyControl;


	//virtual record각각 독자적으로 가지는 정보
	OrderRecordList m_order;	//nTNo를 키로 가지는 실제오더정보
	OrderIndex m_Index;			//nTNo와 실제보여지는 ROW와 매칭되는 정보
	OrderIndex m_filter;		//filter를 사용할 경우에 m_Index와 매칭되는 정보
	OrderIndex m_arrange;		//m_Index, m_filter에서 사용하는 정렬정보
	OrderIndex m_arrangeTNoSet;		//m_arrange에서 부모가 검색이 안되고 자식만 나올경우에 저장된다.
	BOOL m_bUseFilter;			//filter를 사용하는지 여부판단 플래그, 
								//속도때문에 filter가 적용되지 않는 전체검색에서는 FALSE로 세팅됨
	BOOL m_bParentSearch;
public:
	static long m_crStateText1;
	static long m_crStateText2;
	static long m_crStateText3;
	static long m_crStateText4;
	static long m_crStateText5;
	static long m_crStateText6;
	static long m_crStateText7;
	static long m_crStateText8;
	static long m_crStateText9;
	static long m_crStateText10;
	static long m_crStateTextA;
	static long m_crStateBack1;
	static long m_crStateBack2;
	static long m_crStateBack3;
	static long m_crStateBack4;
	static long m_crStateBack5;
	static long m_crStateBack6;
	static long m_crStateBack7;
	static long m_crStateBack8;
	static long m_crStateBack9;
	static long m_crStateBack10;
	static long m_crStateBack12;
	static long m_crStateBack15;

	static BOOL m_bUsePickupNot;

public:
	MAP_ORDER_STATE_SECOND_SORT_MAP *GetSecondSortMap() { return &m_mapSecondSort; }
	MAP_RIDER_OWN_CALL2 m_mapRider;
	MAP_ORDER_OWN_RIDER m_mapOrder;
	OrderRecord *GetOrderRecord(long nIndex)
	{ 
		return m_bUseFilter ? 
				&m_order[m_Index[m_filter[m_arrange[nIndex]]]] : 
				&m_order[m_Index[m_arrange[nIndex]]];		
	}

	OrderRecordList &GetOrderRecordList() 
	{ return m_order; }

	OrderIndex &GetOrderIndex() 
	{ return m_Index; }

	OrderIndex &GetFilterIndex() 
	{ return m_filter; }

	OrderIndex &GetArrangeIndex()
	{ return m_arrange; }

	int GetItemRowFromTNo(long nTNo);

	void SetParentSearch(BOOL bParentSearch)
	{ m_bParentSearch = bParentSearch;}
	void SetCompanyCode(long nCompany)
	{ m_nCompanyCode = nCompany; }
	void SetDOrderCompany(long nCompany) 
	{ m_nDOrderCompany = nCompany; }
	void SetIntegrated(BOOL bIntegrated)
	{ m_bIntegrated = bIntegrated; }
	void SetRcpTimeCol(long nCol)
	{ m_nRcpTimeCol = nCol; }
	void SetStartCol(long nCol)
	{ m_nStartCol = nCol; }
	void SetUseCountCol(long nCol)
	{ m_nUseCountCol = nCol; }
	void SetUseNewRegion(BOOL bUseNewRegion)
	{ m_bUseNewRegion = bUseNewRegion; }

	void SetRcpTimeColor(long one, long two, long three)
	{
		m_nRcpTimeColor1 = one;
		m_nRcpTimeColor2 = two;
		m_nRcpTimeColor3 = three;
	}

	void SetMyControl(CMyReportControl *pControl)
	{ m_pMyControl = pControl;}

	void SetUseFilter(BOOL bUseFilter)
	{ m_bUseFilter = bUseFilter; }

	void SetPayTypeCol(long nCol)
	{ m_nPayTypeCol = nCol;	}

	void SortRecord(int nCol, SORT_TYPE type, BOOL bAsc = TRUE, BOOL bStateSecondSort = FALSE);

public:
	virtual void GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);
	virtual COLORREF OnColorText(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, OrderRecordList::iterator &itOrder);
	virtual COLORREF OnColorBack(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, OrderRecordList::iterator &itOrder);

	void MakeReserveOrderSortNumber();
	


};
