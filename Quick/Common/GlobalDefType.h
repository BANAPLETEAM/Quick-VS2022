
#pragma once

#ifndef _DEBUG
#define USE_OLD_ASSERTS
#include "BugslayerUtil.h" 
#endif

enum {SERVICE_TYPE_QUICK = 0, SERVICE_TYPE_CARGO = 1, SERVICE_TYPE_DELIVERY = 2};
enum {RC_WHITE = 0, RC_BLUE, RC_GREEN, RC_RED, RC_PURPLE, RC_YELLOW, RC_SKY,
	RC_BLACK, RC_INDIGO, RC_PINK, RC_DARKGRAY, RC_LIGHTLATEGRAY, RC_THISTLE, RC_MIDNIGHT};
enum {PAY_PRE = 0, PAY_AFTER, PAY_CREDIT, PAY_ONLINE, PAY_DIRECT, PAY_IMSI, PAY_IMSI2, PAY_CARD = 7};
/*
enum {CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK, CAR_SUBWAY, CAR_PS, CAR_6VAN, 
		CAR_1_4_TON, CAR_2_5_TON,CAR_3_5_TON, CAR_5_TON, CAR_11_TON, CAR_18_TON, CAR_25_TON}; //CAR_PARCEL_SERVICE
*/

enum {CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK, CAR_SUBWAY, CAR_PS, CAR_6VAN, 
	CAR_1_4_TON, CAR_2_5_TON,CAR_3_5_TON, CAR_5_TON, CAR_11_TON, CAR_18_TON, CAR_25_TON,
	CAR_SEDAN, CAR_5_TON_PLUS, CAR_8_TON, CAR_14_TON, CAR_15_TON
}; //CAR_PARCEL_SERVICE

enum {CARGO_NONE = 0, 
		CARGO_JABARA,
		CARGO_LIFT,
		CARGO_WING_BODY,
		CARGO_LIFT_WING,
		CARGO_FREEZER
};

//enum {TRUCK_CARGO = 0, TRUCK_TOP, TRUCK_WING};
enum {WAY_ONE = 0, WAY_TWO, WAY_SEVERAL};
enum {RUN_NORMAL = 0, RUN_SLOW, RUN_FAST, TEMP, RUN_VERY_FAST, RUN_TOGETHER = 8};
enum {SEARCH_NAME = 0, SEARCH_ADDRESS = 1, SEARCH_PHONE = 2};
enum {PLACE_ORDER = 0, PLACE_START = 1, PLACE_DEST = 2, PLACE_CUSTOMER = 3};
enum {CHARGE_TYPE_A = 0, CHARGE_TYPE_B, CHARGE_TYPE_C, CHARGE_TYPE_D, CHARGE_TYPE_GNO};
enum {DEL_SEND = 0, DEL_RECV = 1, DEL_UNKNOWN = 2};
enum { TYPE_CUSTOMER = 1, TYPE_POI = 2, TYPE_DONG = 4, TYPE_PHONE = 8, TYPE_AUTO = 15};
enum { LABO_CHARGE_DAMAS = 0, LABO_CHARGE_VAN, LABO_CHARGE_EACH};


enum{OPTION_GENERAL_TAB, OPTION_CHARGE_TAB, OPTION_CID_TAB, OPTION_SMS3_TAB, OPTION_MOBILE_NEW_TAB,
	OPTION_INTERCALL_TAB, OPTION_PERSONAL_INFO_TAB, OPTION_SMART_QUICK, OPTION_SMART_QUICK_LOGI, OPTION_CONTRACT_LOGI};

enum {PDA_V100 = 100, PDA_XG = 101, PDA_MITS330 = 330, PDA_MITS3300 = 3300, PDA_MITS400 = 400, 
	PDA_MITS4000 = 4000, PDA_POZ_SKT = 200, PDA_POZ_KTF = 2000, PDA_X301 = 3010, PDA_SC8000 = 800, 
	PDA_M500 = 500, PHONE_SKT = 11,	PHONE_KTF = 16, PHONE_LGT = 19, PHONE_WAP_SKT = 21,	
	PHONE_WAP_KTF = 26,	PHONE_WAP_LGT = 29,	PDA_KC8000_KTF = 900, PDA_RW6100 = 1000,PDA_AIV = 3000};

enum {PLACE_TYPE_ORDER = 0, PLACE_TYPE_START = 1, PLACE_TYPE_DEST = 2, POI_CHANGE_EVENT = 4, 
	POI_COMPLETE_EVENT = 8, POI_NO_CHANGED_EVENT = 16, PLACE_TYPE_CUSTOMER = 32};

enum {ST_PHONE	= 0, ST_ID = 1, ST_COMPANY = 2, ST_COMPANY_MID = 3, ST_CNO = 4, 
	ST_WORD_RANGE1 = 5, ST_WORD_RANGE2  = 6, ST_WORD_RANGE3  = 7, ST_TEAM_NO = 8, ST_GROUP_NO = 9,
	ST_DATE_RANGE	= 10, ST_PHONE_RANGE = 11, ST_NAME_DEPART = 12, ST_AUTO_DETECT  = 13};

enum {
	TEL_TYPE_GENERAL = 0,
	TEL_TYPE_MAIN = 1,
	TEL_TYPE_PHONE1 = 2,
	TEL_TYPE_PHONE2 = 3,
	TEL_TYPE_SMS = 4
};

enum {
	STATE_INTERNET = 2,
	STATE_SITE = 3,
	STATE_CARRY = 5,
	STATE_WAIT = 8,
	STATE_RESERVED = 9,
	STATE_OK = 10,
	STATE_OK_ONLY_MAN = 11,
	STATE_ALLOCATED = 30,
	STATE_PICKUP = 31,
	STATE_FINISH = 35,
	STATE_CANCELED = 40,
	STATE_RECALL = 50,
	STATE_RIDER_CALL = 51,
	STATE_INQUIRY = 60,
	STATE_NOTICE = 70
};

enum { MINUS_ONE = -1, ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN };
enum { LINE_RECV_MODE = 0, LINE_PAUSE_MODE, LINE_UNUSE_MODE, LINE_WORKING_MODE };
enum { UNMUTE_MODE = 0, MUTE_MODE, MUTE_HANGUP_MODE };
enum { UNANSWER_RECPLAY_MODE = 0, ANSWER_RECPLAY_MODE, ANSWER_RECPLAY_HANG_MODE };
enum { UNBLINDTRANSFER_MODE = 0, BLINDTRANSFER_MODE, BLINDTRANSFER_HANGUP_MODE };
enum { PH_ANSWER = 0, PH_HANG_UP, PH_RING, PH_CALLBELL, PH_TRANSFER, PH_OUT_BOUND_CALL, PH_ARS_ANSWER };

#define OFFICE_OK_ONLY_MAN 2
#define OFFICE_ALLOCATED 16
#define OFFICE_PICKUP 64
#define OFFICE_FINISH 128
#define RIDER_OK_ONLY_MAN 3

#define SECTION_MILEAGE 100000
#define COUNT_MILEAGE 200000
#define MAX_REGION_SELECT_COUNT 5

#define ON_COMMAND_RANGE_SINGLE(x, y)  ON_COMMAND_RANGE(x, x, y)


#define LITERAL_CARD_NUMBER		"    -    -    -    "
#define LITERAL_BIZ_NO_NUMBER	"   -  -     "
#define LITERAL_ZIP_CODE_NUMBER "   -   "
#define	PST_NICE_REQUSET_OK  388	//카드 승인
#define	PST_NICE_REQUSET_CANCEL  389	//승인 취소
#define PST_NICE_REQUSET_PROTOCOL 392 //카드결제 이메일재발송, 현금영수증 관련
#define SMS_TYPE_ALLOCATE 102
#define SMS_TYPE_TEST 103
#define SMS_TYPE_BULK 999

#define WM_CHANGE_POI			(WM_USER + 500)
#define WM_CHANGE_BRANCH_CODE	WM_USER + 8001
#define WM_REFRESH_RIDER_POS	WM_USER + 8002
#define WM_REFRESH_DELAY_ORDER	WM_USER + 8003
#define WM_BRANCH_CLICK_EVENT	WM_USER + 555

#define WM_CLOSE_RCPDLG			WM_USER + 101
#define WM_REFRESH_LIST			WM_USER + 102
#define WM_RECV_CID				(WM_USER + 200)
#define WM_RESERVE_ORDER		WM_USER + 201
#define WM_FIRST_REFRESH		WM_USER + 686
#define WM_SELECT_POI_ON_MAP	WM_USER + 687
#define WM_SAVE_RCP_LIST		WM_USER + 689
#define WM_LOAD_RCP_LIST		WM_USER + 690
#define WM_SAVE_CTI_LIST		WM_USER + 691
#define WM_LOAD_CTI_LIST		WM_USER + 692


#define	WM_CLOSE_RIDER_DLG		WM_USER + 678
#define WM_RIDER_ALLOCATE		WM_USER + 679
#define WM_ALLOCATE_BOARD_DYN_CLOSE WM_USER + 990

#define WM_SEND_EMOTICON		WM_USER + 2000
#define WM_CHANGE_MENT	WM_USER + 8002

#define WM_CLOSE_SMS_DLG WM_USER + 300
#define WM_INSUNG_CUSTOMER_OK WM_USER + 301




#define MESSENGER_HOT_MSG	1

#define MAKE_SHARE_CODE(x)	x == 0 ? -1 : x
#define DB_SUBTYPE_IP	"@@CLIENT_IP"
#define DELETE_OBJECT(x) if(x) { delete x; x = NULL; }
#define DELETE_OBJECT_BR(x) if(x) { delete []x; x = NULL; }
#define MAX_BRANCH 500
#define IDC_TABCONTROL	100
#define FIRSTBRANCH(longegrated, company)	(longegrated ? company - company % 10: company) 
#define LASTBRANCH(longegrated, company)		(longegrated ? company + 9 : company)

#define MINPAY_BOUND		300

#define MAKE_IDENTITY(x, y)	((x << 16) + y)

#define MONTHLY_DEPOSIT_TYPE 20
#define WEEKLY_DEPOSIT_TYPE 30

#define MY_MAX_DEPOSIT 25

#define MAX_REPORT_COUNT 100

#define NICE_CARD_WAIT 14
#define NICE_CARD_COMPLETE 114

#define NICE_CARD_WAIT_QUICKCALL 15
#define NICE_CARD_COMPLETE_QUICKCALL 115

#define MAX_MMS_IMAGE_COUNT 3


//"지원되지 않는 작업을 시도하였습니다." 에러인 경우에 아래 주석을 풀고 로그를 보면 위치를 정확히 알수 있음
//#define DDX_Control(x, y, z) { g_bana_log->Prlong("DDX_Control: FILE = %s, LINE = %d\n", TEXT(__FILE__), TEXT(__LINE__));DDX_Control(x, y, z);}


//extern CQLog mkLog;
#define LL_STATE	0
#define LL_DEBUG	5

#define DEFINE_SMS_AMOUNT 17
#define LOG(s)  (s)
#define BASE_HOUR	0

#define CLR_WHITE RGB(0xFF, 0xFF, 0xFF)
#define CLR_BLACK RGB(0, 0, 0)
#define CLR_BLUE RGB(0, 0, 0xFF)
#define CLR_GREEN RGB(0, 0xFF, 0)
#define CLR_RED RGB(0xFF, 0, 0)
#define CLR_PURPLE RGB(0xFF, 0xFF, 0xFF)
#define CLR_YELLOW RGB(0xFF, 0xFF, 0)
#define CLR_SKY RGB(0xAF, 0x32, 0xFF)

#define COMPARE_STRING_COUNT 51

#define TYPE_SMS 0
#define TYPE_LMS 1
#define TYPE_MMS 2


#define COLOR_DEFAULT_TOP_WND	RGB(252, 253, 255)
#define COLOR_DEFAULT_DOWN_WND	RGB(200, 223, 255)
#define RIDER_COLOR_COUNT 14



typedef struct {
	long nRole;			//역할
	long nWNo;			//사원번호
	long nCompany;
	long nSiteSessionKey;

	BOOL bDeveloper;
	BOOL bBlankPassword;
	BOOL bUseWindow7;
	
	COleDateTime dtLoginTime;
	
	CString strID;
	CString strPW;
	CString strName;	
	CString strLogiStaffName;
	CString strTaxUseEmail;
} ST_USER_INFO;

typedef struct {
	long nPosX;
	long nPosY;
	long nBoundary1;
	long nBoundary2;
	long nBoundary3;
} ST_BOUNDARY_INFO;

typedef struct{
	long nSMSType;
	long nSMSBarance;
	long nCompany;

	BOOL bRcplongMode1;
}ST_SMS_INFO;

typedef struct {
	CString strWName;
	long nCompany;
	long nWNo;
	long nOrderCount;
	long nCallCount;
	long nOneHourOrderCount;
	long nOneHourCallCount;
	long nRank;
	long nPreRank;
} ST_WCOUNT;

typedef struct {
	long nGlobalMsgVer;
	long nLocalMsgVer;
	long nPCNum;
	
	COleDateTime dtTodayBound;
	COleDateTime dtServerTime;
	COleDateTime dtForceExitTime;

	CString strMac1;
	CString strMac2;
	CString strExternalIP;
	CString strProgramVersion;
	DWORD dwProgramStartTick;

} ST_ETC_INFO;

typedef struct {
	UINT nMainServerPort;
	UINT nMsgServerPort;
	UINT nRealMainServerPort;

	COleDateTime dtServerTime;

	CString strMainServerAddr;
	CString strMsgServerAddr;
	CString strRealMainServerAddr;
} ST_SERVER_INFO;

typedef struct {
	long nCompany;
	long nRNo;
	long nWorkState;

	CString strName;
	CString strPhone;
	CString strCompanyName;
} ST_RIDER_WORK_STATE_INFO;

typedef struct {
	long nCompany;
	long nID;

	CString strChargeName;
	CString strEtc;
} ST_CHARGE_TYPE_NAME_INFO;

typedef struct {
	int nCompany;
	CString strName;
	CString strBranchName;
	CString strOfficePhone;
	CString strCity;
	CString strTel;
	CString strClientSymbol;
	int nShareCode1;
	BOOL bCorporationTelHidden;
	int nShareLevel;
	BOOL bRcpIntMode1;
	CString strAuthPhone1;
	CString strAuthPhone2;
	CString strSMSOfficePhone;
} SHARE_COMPANY_INFO;

typedef struct  
{
	long nMemCNo;
	long nCompany;	
	long nCusCount;
	long nChargeCount;

	BOOL bView;
	BOOL bDelete; /// 하루만 작업 익일 삭제...

	COleDateTime dtRegister;
	COleDateTime dtChange;
	COleDateTime dtDelete;

	CString strMemo;
	CString strWName;
	CString strMemCompany;
} ST_MEMBER_CHARGE_CNO;

class CBranchInfo 
{
public:
	long nShareLevel;
	long nBranchCode;
	long nCompanyCode;
	long nDOrderTable;
	long nCustomerTable;
	long nPayTable;
	long nStateType;
	long bIntegrated;
	long nDefaultCharge;
	long nShareCode1;
	long nShareCode2;
	long nShareCode3;
	long nShareCode4;
	long nShareCode5;
	long nCancelPenaltyCharge;
	long nSubDisplayGroup;
	long nLastSelItemNo;
	long nCurSel;
	long nCurCol;
	long nDamasPay;
	long nRaboPay;
	long nTruckPay;
	long nBonggoPay;
	long nRcpColor;
	long nRcpTextColor;
	long nDiscountSec;
	long nCondition1;
	long nCondition2;
	long nRegionSection;
	long nFinalSMSSend;
	long nTankType;
	long nMileageSettingCount;
	long nMileageSpan;
	long nRevisitCustomerSendDay;
	long nRevisitCustomerSendCompany;
	long nTruckDeposit;
	long nEmergencyCharge;
	long nBothCharge;
	long nSmsChargeCompany;
	long nVirtualCompany;
	long nDistanceCharge;
	long nMinCharge;
	long nViaAmount;
	long nPayType1;
	long nPayType2;
	long nPayType3;
	long nPayType4;
	long nCarType1;
	long nCarType2;
	long nCarType3;
	long nServiceType;
	long nAutoShareTime;
	long nOtherCompanyCNo;
	long nOtherCompanyCNoTelID;
	long nNowRate;
	long nConsignID;
	long nOtherCompany;
	long nHistoryDetailAllView;

	UINT nCurTab;

	BOOL bGroup;
	BOOL nShareStartTime1;
	BOOL nShareStartTime2;
	BOOL nShareStartTime3;
	BOOL nShareStartTime4;
	BOOL nShareStartTime5;
	BOOL bMemoToEtc;
	BOOL bRiderMemoToEtc;
	BOOL bCallerIDToPhone1;
	BOOL bClearDestForAfterCopy;
	BOOL bFocusToWaitBtn;
	BOOL bNoGroupCharge;
	BOOL bAddDisChargeRound;
	BOOL bAutoShareOrder; 
	BOOL bPartRefresh;
	BOOL bPrePartRefresh;
	BOOL bColAsc;
	BOOL bCreditAfterDiscount;
	BOOL bUseChargeDong;
	BOOL bUseNewRegion;
	BOOL bUserIDSequence;
	BOOL bTodayDelete;
	BOOL bUseOnLine;
	BOOL bUserDongPos;
	long nLaboChargeType;
	BOOL bDistanceCharge;
	BOOL bDongPosLiUse;
	BOOL bPeekTimeApplyCharge;
	BOOL bDistancePointUse;
	BOOL bUseCardTax;
	BOOL bUsageHistory;
	BOOL bNotUseEtcForCancel;
	BOOL bUseOrderBundle;
	BOOL bCancelToInquiry;
	BOOL bEtcAuto;
	BOOL bUseCardPay;
	BOOL bUseBranchShareReport;
	BOOL bRcpIntMode1;
	BOOL bNotMemberCharge;
	BOOL bNoDestPoi;
	BOOL bUseDirectDistance;
	BOOL bMemChaNoGeneralData; // 히스토리입력시 기본데이터 미입력
	
	COleDateTime dtLastRefresh;
	COleDateTime dtFrom;
	COleDateTime dtTo;
	COleDateTime dtAcceptApply;
	COleDateTime dtInitDay;
	COleDateTime dtTodayDelete;
	
	CString strPhone;
	CString strCallingLine;
	CString strMemo;
	CString strCodeList;
	CString strDDD;
	CString strCity;
	CString strOtherCompanyName;
	CString strSort;
	CString strFilter;
	CString strCID;
	CString strPreCondition;
	CString strSortField;
	CString strCondition2;
	CString strName;
	CString strBranchName;
	CString strLineGroup;
	CString sEtcUserTitle1;
	CString sEtcUserTitle2;
	CString sEtcUserTitle3;
	CString sEtcUserTitle4;
	CString sEtcUserMemo1;
	CString sEtcUserMemo2;
	CString sEtcUserMemo3;
	CString sEtcUserMemo4;
	CString strEtcAuto;
	BOOL bCancelReason;
	BOOL bInitDongInfo;
	BOOL bCreditListPopup;

	long nPayType5;
	long nCarType4;
	long nCarType5;
	BOOL bIPPBXType;
	BOOL bNotClientPhone1;
	BOOL bNotCustomerAddCID;
	BOOL bCustomerAutoInsert;
	BOOL bFirstWaitTimePast;

	long nUseUpChargeForNotAllocate;
	long nUpChargeForNotAllocate1;
	long nUpChargeForNotAllocate2;
	long nUpChargeForNotAllocate3;
	BOOL bPopupFocus;
	BOOL bColorChange;
	BOOL bOnlyLoadInsRider;
	long nFeeType;
	long nBranchDiscount; // 지사특정할인,
	BOOL bVRAccountNoRider; // 기사가상계좌 사용안함.

	long nBikeAddWeather;
	long nDamaAddWeather;
	long nLaboAddWeather;
	long nVanAddWeather;
	long nTruckAddWeather;
	BOOL bWeatherCharge;

	long nBikeAddWeatherSnow;
	long nDamaAddWeatherSnow;
	long nLaboAddWeatherSnow;
	long nVanAddWeatherSnow;
	long nTruckAddWeatherSnow;
	long bWeatherChargeSnow;
	long nSlowDiscount;
	long nCnsSearchType1;
	long nCnsSearchType2;
	long nCnsSearchPaid;
	BOOL init_dt1_state_to_rcp;
	
public:
	BOOL IsCargo() { return nServiceType == SERVICE_TYPE_CARGO; }
	BOOL IsQuick() { return nServiceType == SERVICE_TYPE_QUICK; }
};

typedef struct
{
	long nRcpMoveMap;
	long nRcpDlgMoveMap;
	long nNotCreateMapForm;
	long nJoinWithCID;
} ST_RCP_MAP_SET_INFO;

typedef struct {
	long nCompany;
	long nShareCode1;
	long nShareCode2;
	long nShareCode3;
	long nShareCode4;
	long nShareCode5;

	BOOL bUseBranchShareReport;
	
	CString strName;
	CString strBranchName;
	CString strPhone;
	CString strOfficePhone;

	long nCnsSearchType1;
	long nCnsSearchType2;
	long nCnsSearchPaid; 
	BOOL bRcpIntMode1;

} ST_SHARE_COMPANY_INFO;

typedef struct{
	long nCompany;
	long nRNo;
	long nAllocGroup;
	long nWorkState;
	int nPanaltyTypeShowOrder;

	BOOL bLock;
	BOOL bAutoShow;
	BOOL bBigAutoShow;
	BOOL bDamaShow;
	BOOL bRaboShow;
	BOOL bBanShow;
	BOOL bTruckShow;
	BOOL bMyOrderLock;
	BOOL bOtherOrderLock;
	BOOL bJobStop;
	BOOL bTimeAllocate; //시간제한
	BOOL bServiceRentLimit; //서비스이용료제한
	BOOL bInsurance; //보험제한
	
	CString strElapseLimitAllocateLocal;
	CString strElapseLimitPickupLocal;
	CString strElapseLimitAllocateGlobal;
	CString strElapseLimitPickupGlobal;
	CString strLockTime;
	CString strLockCount;
	CString strLockTime4MyOrder;
	CString strLockCount4MyOrder;
	CString strLockTime4OCOrder;
	CString strLockCount4OCOrder; // 기본정보 끝
	CString strJobStopMemo; //업무중지사유
	CString strTimeAllocateRelease; //시간제한헤제
	CString strInsuranceCompany; //보험회사
	CString strInsuranceID;// 증권번호

	COleDateTime dtJobStart; //업무시작
	COleDateTime dtJobEnd; //업무끝
	COleDateTime dtJobStop; //업무중지시간날짜
	COleDateTime dtJobStopTime; //업무중지시간시간
	COleDateTime dtTimeAllocateDate; //시간제한시간 날짜
	COleDateTime dtTimeAllocateTime; //시간제한시간 시간
	COleDateTime dtInsuranceStart; //보험제한시작
	COleDateTime dtInsuranceEnd; //보험제한끝
} ST_RIDER_INFO_ALLOCATE;

typedef struct{
	long nCompany;
	long nRNo;
	long nDepositType;
	long nFixedDeposit;
	long nAddBalance;
	long nDT;  // 기본정보
	long nDepositExtensionDay;
	long nMyCallCash;
	long nOtherCallCash;
	long nMyCallCredit;
	long nOtherCallCredit;
	long nMyCallOnline;
	long nOtherCallOnline;
	long nMyCashApplyCharge;
	long nOtherCashApplyCharge;
	long nMyCreditApplyCharge;
	long nOtherCreditApplyCharge;
	long nMyOnlineApplyCharge;
	long nOtherOnlineApplyCharge;
	long nDepositAllocateType;
	long nAllocMinCharge;
	long nMyCallRateType;
	long nOtherCallRateType;

	int nSameRiderIncomeDay;
	int nSMSDealyDay;
	int nOtherCallDTType;
	int nMyCallDTType;
	int nCreditReportType;
	int nRiderIncomeDay;
	int bWeeklyDeposit;
	int nPayMentDay;
	int nMyCallCashWon;
	int nOtherCallCashWon;
	int nMyCallCreditWon;
	int nOtherCallCreditWon;
	int nMyCallOnlineWon;
	int nOtherCallOnlineWon;
	int nCashDTType;
	int nCashDTWon;
	int nMyCallDTWon;
	int nOtherCallDTWon;

	BOOL bUseDTPercent;
	BOOL bBranchAsOtherCall;
	BOOL bPenaltyCharge;
	BOOL bUseSmsNotify;

	CString strEtc;
	CString strEtcCharge;
	CString strCashDTFee;
	CString strMyCallDTFee;
	CString strOtherCallDTFee;
} ST_RIDER_INFO_INCOME;

typedef struct 
{
	long nValueType;
	long nClass;
	long nStart;
	long nEnd;
	long nAmount;
} ST_CHARGE_SECTION_VALUE;

//typedef map<long, CUSTOMER_GROUP_INFO> CUSTOMER_GROUP;

typedef struct {
	long nGroupID;
	long nLineID;

	DWORD dwTick;
	CBranchInfo *pBi;

	CString strPhone;
	CString strChannel;
	CString strZipCode;
} ST_CID_INFO;

typedef struct  
{
	long lCode;
	long nMNo;
	long nReleaseMin;
	long nPanaltyTypeShowOrder;
	long nLockTime4MyOrder;
	long nLockCount4MyOrder; 
	long nLockTime4OCOrder;
	long nLockCount4OCOrder;
	long nAllocType;
	long nCarType;
	long nAllocGroup;
	long nDepositType;
	long nDeposit;
	long nLockTime;
	long nLockCount;
	long nWorkState;

	BOOL bAllocateLimit;

	COleDateTime dtEnter;
	COleDateTime dtWorkStateDate;
	COleDateTime dtAllocateLimitDate;

	CString strCurDong;
	CString strCurLocation;
	CString strRTID;
	CString	strID;
	CString	strHp;
	CString strName;
	CString strBranchName;
} ST_ALLOC_RIDER;

typedef struct {
	CBranchInfo *pBi;
	COLORREF crBack;
	long nVirtualCompany;
	CString strGroupName;
} ST_BRANCH_PANE_INFO;

typedef struct{
	long nCount;
	ST_BRANCH_PANE_INFO *pBiPane[MAX_BRANCH];
} ST_BRANCH_INFO;

typedef struct {
	long nPosX;
	long nPosY;
	long nCompany;
	long nRNo;
	long nCarType;
	long nDirIcon;
	long nState;
	long nStartPosX;
	long nStartPosY;
	long nDongID;

	BOOL bUseGPS;
	BOOL bConnRider;
	
	COleDateTime dtState;

	CString strName;
	CString strPosName;
	CString strGugun;
	CString strDong;
	CString sCompanyName;	
} ST_RIDER_POS_INFO;

typedef struct {
	long x;
	long y;
} ST_RIDER_POS_OFFSET_INFO;

typedef struct{
	long nCNo;	
	long nID;
	long nDiscount;
	long nGNo;
	long nTeamNo;
	long nAllocGroup;	
	long nCouponCharge;
	long nPosX;
	long nPosY;
	long nDongID;
	long nNodeID;
	long nCustomerType;
	long nUseCount;
	long nCancelCount;
	long nCreditCount; 
	long nCreditCharge;
	long nMemCNo;
	long nDiscountRange;
	long nSendStateChangeSMS;
	long nCustomerGrade;
	long nPriceGrade;
	long nMileageType;
	long nReportStartDay;
	long nReportEndDay;
	long nIssueTaxBillDay;
	long nPayableDay;
	long nUnCollectedAmount;
	long nDiscountType;
	long nMileageValue;
	long nCouponType;
	long nMileageBalance;
	long nMainAddressID;
	long nSalesCompany;
	long nSalesWNo;
	long nTelID;
	long nTelType;
	long nCustomerColor;
	long nMemoColor;

	BOOL bNoSmS;
	BOOL bGroupOwner;
	BOOL nICMapDisplayType;
	BOOL bGorupSelect;
	BOOL bHasDetailPos;
	BOOL bUseHomepage;
	BOOL bMain;
	BOOL bDelete;
	BOOL bNotAutoShareOrder;
	BOOL bDiscountApplyOnlyCredit;
	BOOL bPreventPosUpdate;;
	BOOL bCreditAfterDiscount;
	BOOL bCredit;

	COleDateTime dtRegister;
	COleDateTime dtLastUse;
	COleDateTime dtPRDate;
	COleDateTime dtSales;	

	CString strRiderMemo;
	CString strMobile;
	CString strMemo;
	CString strAddress;
	CString strEMail;
	CString strUserID;
	CString strLoginID;
	CString strLoginPW;
	CString strFax;
	CString strCompany;
	CString strDepart;
	CString strName;
	CString strTel1;
	CString strTel2;
	CString strLocation;
	CString strDong;

	long nShowPhoneType;
	BOOL bPopupCustomerDlg;

	BOOL bOnlinePopup;
	long nOnlinePopupCharge;

} ST_CUSTOMER_INFO;

typedef struct{
	long nID;
	long nCNo;
	long nGNo;
	long nCompany;
	long nPosX;
	long nPosY;
	long nDongID;

	CString strAddressTitle;
	CString strDong;
	CString strLocation;
	CString strAddress;
} ST_ADDRESS;

typedef struct
{
	long nTNo;
	long nWCompany;
	long nWNo;
	long nCompany;
	long nChargeAdd;
	long nChargeBasic;
	long nChargeTrans;
	long nChargeReturn;
	long nChargeDis;
	long nChargeSum;
	long nDeposit;
	long nCouponCharge;
	long nRiderCompany;
	long nRNo;
	long nState;
	long nPayType;
	long nCarType;
	long nWayType;
	long nRunType;

	COleDateTime dtEdit;

	CString strOName;
	CString strOPhone;
	CString strOMobile;
	CString strODepart;
	CString strOManager;
	CString strOAddress;
	CString strODetail;
	CString strODong;
	CString strOMemo;
	CString strSName;
	CString strSPhone;
	CString strSMobile;
	CString strSDepart;
	CString strSManager;
	CString strSAddress;
	CString strSDetail;
	CString strSDong;
	CString	strDName;
	CString strDPhone;
	CString strDMobile;
	CString strDDepart;
	CString strDManager;
	CString strDAddress;
	CString strDDetail;
	CString strDDong;

	CString strChargeBet;
	CString strSmsNumber;
	CString	strEtc;
	CString strItemType;
	long nReserved;
	COleDateTime dtReserved;

	long nChargeDriving;
	long nShowPhoneTypeOrder;
	long nShowPhoneTypeStart;
	long nShowPhoneTypeDest;
	long nChargeCompany;

	BOOL bFoodOrder;
	COleDateTime dtFoodComplete;

	BOOL bAutoShareOrder;
	long nChargeRevision;
	CString strEditor;

	CString item[COMPARE_STRING_COUNT];
} ST_EDIT_HISTORY;

typedef struct{
	long nTNo;
	COleDateTime dt1;
} ST_COUNT_MILE;

class CLoadInsuranceData 
{
public:
	CString strCompanyName;
	long nRiderCompany;
	long nRNo;
	CString strRiderName;
	CString strSSN;
	CString strPhone;
	long nCarType;
	CString strCarNo;
	long nWorkState;
	CString strStartDate;
	CString strInsuranceCompany;

	CString inputWdate;
	CString rogiCerti;
	CString message;

	CString strErrorMsg;

	CLoadInsuranceData::CLoadInsuranceData()
	{
		strCompanyName = "";
		nRiderCompany = 0;
		nRNo = 0;
		strRiderName = "";
		strSSN = "";
		strPhone = "";
		nCarType = 0;
		strCarNo = "";
		nWorkState = 0;
		strStartDate = "";
		strInsuranceCompany = "";

		inputWdate = "";
		rogiCerti = "";
		message = "";

		strErrorMsg = "";
	}	
};

typedef struct 
{
	long nRiderAlloc;
	long nRiderPickup;
	long nRiderBefore1;
	long nRiderBefore10;
	long nRiderBefore30;
	long nRiderAfter30;
	long nRiderCaptionRNo;
	long nRiderCaptionName;
	long nRiderCaptionCompany;
	long nOrderBefore10;
	long nOrderBefore20;
	long nOrderBefore30;
	long nOrderBefore60;
	long nOrderAfter60;
	long nOrderCaptionTime;
	long nOrderCaptionStart;
	long nOrderCaptionDest;
	long nOrderAutoRefresh;
	long nNearRiderLevel;
	long nShowSectorList;
	long nShowShareRider;
	long nShowCompleteOrder;
	long nShowCancelOrder;
	long nOrderClickAutoMove;
	long nShowRiderHasColor;
	long nShowCompayAll;
	long nShowRiderCaptionLevel;
	long nOrderClickRiderMove;
	long nRiderTailShowTime;
	long nHoverShowRiderHaveOrder;
	long nGpsRiderOnly;

	long bShowOrderCount;
	long bOrderCount8;
	long bOrderCount10;
	long bOrderCount11;
	long bOrderCount30;
	long bOrderCount31;
	long bOrderCount35;

	BOOL bLocateRight;
} ST_RIDER_MAP_SET_INFO;

typedef struct{
	long nDrivingCount;
	long nWaitCount;
} ST_USER_SECTOR_COUNT;

typedef struct{
	long nCompany;
	long nRNo;
	long nRiderColor;
	BOOL bSupportRider;
} ST_RIDER_MISC_INFO;

typedef struct  
{
	long nGNo;
	long nCompany;
	long nMembers;
	long nCharge;
	long nDepositRate;
	long nReportFirstDay;
	long nReportSecondDay;
	long nGroupOwner;
	long nParentGNo;
	long nParentGNo2;
	long nParentGNo3;
	long nParentGNo4;
	long nParentGNo5;
	long nLevel;
	long nGNoKey;
	long nActiveLevel;
	long nActiveGroupLevel;
	long nUseCount;
	long nCancelCount;
	long nBalance;
	long nCredit;
	long nGroupCredit;
	long nDiscount;
	long nAddTaxApplyType;
	long nGroupCount;
	long nUseCharge;
	long nAbleUseCharge;
	long nInitDay;

	long nDirectDiscountType;
	long nDirectDiscount;
	long nDirectDiscountRange;
	long nInterCallNotViewAmount;
         
	long nAutoCalculate;
	long nElectronicTaxType;
	long nBillCollectionAdd;
	long nPayMentAdd;
	long nGNoListType; // 정산시 전체, 일부, 개별

	BOOL bNotShowCash;
	BOOL bNoGroupCharge;
	BOOL bManagerIsOrderInput;
	BOOL bCashApply;
	BOOL bCreditApply;
	BOOL bOnlineApply;
	BOOL bTransApply;
	BOOL bShowOrder;
	BOOL bIntercallGroupOwner; // 인터콜 그룹오너만 전체오더보기

	CString strName;
	CString strMemberTel;
	CString strManagerHP;
	CString strChargeName;	
	CString strPresident;
	CString strBusinessNo;
	CString strBusinessStatus;
	CString strBusinessCategory;
	CString strArea;
	CString strEmail;
	CString strGroupName;
	CString strDept;
	CString strTotalName;	
	CString strDetail;
	CString strPassword;
	CString strID;
	CString strKeyRef;
	CString strFullName;
	CString strNotIncomeMonth;
	CString strSearchData;
	CString strSearchDateData;
	CString strNotIncomeMonthData;		
	CString strGNoList;
	CStringArray strColumnChk;
	
	COleDateTime dtLastUse;
	COleDateTime dtLastInput;

	CXTPGridRecord* pReocrd;
} ST_CUSTOMER_GROUP_INFOMATION;

typedef struct {
	long nID;
	long nType;
	long nCompany;
	CString strMent;
} ST_STATE_MENT;


typedef struct
{
	long nReplacePhone1WithCID;
	long nReplacePhone2WithPhone1;
	long nIncreaseDetailControlAlways;
	long nCopyDestCreditCustomer;
	long nStartDontAutoCopy;
	long nManualAddCustomer;
} ST_RCP_DLG_SET_INFO;


class CCarType {
public:
	CCarType(long _nCarType, long _nTruckType = 0, CString _strTon = "")
	{
		nCarType = _nCarType;
		nTruckType = _nTruckType;
		strTon = _strTon;
	}

	CCarType()
	{
	}

	long nCarType;
	long nTruckType;
	CString strTon;
};

class CRealTimeRiderPos
{
public:
	long nCompany;
	long nRNo;
	CString strName;
	long nPosX;
	long nPosY; 
	BOOL bUseGps;
	CString strPosName;
	CString strDeviceName;
	CString strVersion;
	CString strOS;
	CString strPhone;
	CString strCity;
	CCarType cartype;
};

typedef struct {
	long nCNo;
	CString strDepart;
	CString strManager;
	CString strTel;
	long nTelID;
	long nTelType;
} ST_TEL;


typedef struct{
	COleDateTime dtDate; //

	long nState;
	long nDelay;
	long nRNo;
	long nTNo;
	long nCompany;
	long nDistanceKM;
	long nRiderCompany;
	long nCarType;
	long nDeposit;

	CString strStart;
	CString strDest;
	CString strOName;
	CString strRName;
} ST_DELAY_ORDER;

typedef struct{
	long nTNo;
	long dt1;
	long nChargeSum;
	long nChargeTrans;
	long nShareCode1;
	long nRiderShareCode1;
	long nPayType;
	long nOrderType;
	long nCouponCharge;

	BOOL bGiveChargeToRider;
} ST_RIDER_REPORT;

typedef struct{
	long nIndex;
	long nCharge;

	CString strMemo;	
} ST_RIDER_CREDIT;

typedef struct {
	long nID;
	long nRiderCompany;
	long nRNo;
	long nState;
	long nFixedDeposit;

	CString strTakeDate;
	CString strStartDate;
	CString strEndDate;
	CString strRName;	
} ST_RIDER_DEPOSIT_INFO;

typedef struct{
	long nCurCompany;
	long nCompany;
	long nShareCode1;
	long nShareCode2;
	long nShareCode3;
	long nShareCode4;
	long nShareCode5;
	long nRiderCompany;
	long nRiderShareCode1;
	long nRiderShareCode2;
	long nRiderShareCode3;
	long nRiderShareCode4;
	long nRiderShareCode5;
	long nTNo;
	long nState;
	long nRNo;
	long nChargeBasic;
	long nChargeAdd;
	long nChargeTrans;
	long nChargeDis;
	long nChargeSum;
	long nPayType;
	long nRcpRate;
	long nDeposit;
	long nTakeDeposit;
	long nGiveDeposit;

	COleDateTime dt1;

	CString strRName;
} ST_SHARE;

typedef struct {
	long nSNo;
	long nDNo;
	long nTNo;
	long nStartDongID;
	long nDestDongID;
	long nCarType;
	long nChargeAdd;
	long nChargeBasic;
	long nChargeTrans;
	long nChargeDis;
	long nChargeSum;
	long nDeposit;
	long nState;
	long nRCompany;
	long nRNo;
	long nStartPosX;
	long nStartPosY;
	long nDestPosX;
	long nDestPosY;
	long nPayType;
	long nOTelID;
	long nSTelID;
	long nDTelID;
	long nOCNo;

	CString strSName;
	CString strSDong;
	CString strDName;
	CString strDDong;

	CString strOPhone;
	CString strODepart;
	CString strChargeBet;
	CString strEtc;
	CString strOManager;

	CString strSDetail;
	CString strSPhone;
	CString strDDetail;
	CString strDPhone;

	CString strSAddress;
	CString strDAddress;

	COleDateTime dt1;
} ST_HISTORY_ITEM_INFO3;

typedef struct{
	long nID;
	long nCompany;
	long nTotal;
	long nState;
	long nRNo;
	long nFixedDeposit;

	COleDateTime dtCreditOrderStart;
	COleDateTime dtCreditOrderEnd;
	COleDateTime dtCompareDate;

	CString strBankName;
	CString strBankAccount;
	CString strBankAccountOwner;
	CString strEtc;
	CString strMemo;
	CString strRName;
	CString strHp;
} ST_DEPOSIT;

typedef struct{
	long nWCompany;
	long nWNo;
	long nDay[13][32];
	long nOption;

	CString strWName;
	CString strWorkDate;
} ST_WNO_DATE;

typedef struct{
	long nID;
	long nPlayType;
	long nMonthPlayType;
	long nMonthDay;
	long nMonthWeek;
	long nMonthWeekend;
	long nDepositType;
	long nDeposit;
	long nRiderCount;

	BOOL bSun;
	BOOL bMon;
	BOOL bTues;
	BOOL bWednes;
	BOOL bThurs;
	BOOL bFri;
	BOOL bSatur;
	BOOL bUse;
	BOOL bWorkerApply;
	BOOL bNotWorkerApply;
	BOOL bUseSms;
	BOOL bLastJobSuccess;

	COleDateTime dtStart;
	COleDateTime dtEnd;
	COleDateTime dtLastJob;
	COleDateTime dtMakeJob;

	CString strEtc;
	CString strSmsPhone;
	CString strWName;
	CString strDisplayName;
} ST_DEPOSIT_JOB;

typedef struct {
	long nANo;
	long nCompany;
	long nRNo;
	long nMarketLine;
	long nThShareExceptType; //즉시공유 보임 안보임  //0이 오더 다보임
	long nDailyDepositCharge;
	long nBalance;
	long nSaveSixMonth;
	long nLicenceType;	
	long nLicenceValid;
	long nAllocType;
	long nCarType;
	long nPanaltyTypeShowOrder;
	long nLockTime;
	long nLockCount;
	long nWorkState;
	long nAllocGroup;
	long nDepositType;
	long nDepositAllocateType;
	long nMyCallRateType;
	long nOtherCallRateType;
	long nBankID;
	long nMaxWithdrawMoneyPerDay;
	long nMinLeftMoneyForWithdraw;
	long nWithdrawType;
	long nRiderColor;
	long nInsType;

	BOOL bLock;	
	BOOL bAuto;
	BOOL bBigAuto;
	BOOL bSedan;
	BOOL bDama;
	BOOL bRabo;
	BOOL bTruck;

	BOOL bAdminTable;

	COleDateTime dtInsJoin;
	COleDateTime dtEnter;
	COleDateTime dtOut;
	COleDateTime dtWorkStateDate;

	CString strSSN1;
	CString strSSN2;
	CString strLicenceNo;
	CString strAddress;
	CString strMemo;
	CString strInnerMemo;
	CString strMyCallRateType;
	CString strOtherCallRateType;
	CString strName;
	CString strMp;
	CString strPhone;
	CString strRT;
	CString strID;
	CString strBankOwner;
	CString strBankName;
	CString strBankAccount;
	CString strRTSerial;
	CString strRiderDepositGroup;

	BOOL bUseRiderTax;
	BOOL bAutoAlloc;

	long nTruckMyDepositRate;
	long nTruckOtherDepositRate;

	CString strCardNumber;
	CString strCarNo;
	long nAllocMinCharge;
	BOOL bRegisterLoadIns;
	long bBusinessCar;

} ST_RIDER_INFO;

typedef struct
{
	long nType;
	CString strTypeName;
} ST_RATE;

typedef struct{
	long nID;
	long nCashCount;
	long nCreditCount;
	long nOnlineCount;
	long nTransCount;
	long nCashCharge;
	long nCreditCharge;
	long nOnlineCharge;
	long nTransCharge;
	long nReportState;
	long nBillCollection;
	long nUnBillCollection;
	long nTax;
	long nSumCount; //합계항목에서만 쓰임 cash credit online 차지의건수합
	long nSumTotal; //합계항목에서만 쓰임 cash credit online 차지의합

	BOOL bPressBill;
	BOOL bNeedReReport;

	COleDateTime dtReportStart;
	COleDateTime dtReportEnd;
	COleDateTime dtBillCollection;

	CString strEtc;
} ST_GROUP_REPORT;

typedef struct{
	long nGNo;
	long nBalance;
	long nInComeSum;
	long nReportRow;

	CString strGroupName;
	CString strDept;
	CString strName;

	ST_GROUP_REPORT stData[MAX_REPORT_COUNT];
}GROUP_REPORT;

class CustomerData
{
public:
	int	nType;
	int	nUseCount;

	long nCNo;
	long nMileage;
	long nGroupCode;
	long nAdvertCount;
	
	BOOL bNoSMS;

	COleDateTime dtLastSentAdvertSMS;
	COleDateTime dtRegister;

	CString strAddr;
	CString strPostNo;
	CString strCName;
	CString strTel1;
	CString strTel2;
};

typedef struct 
{
	long nCompany;
	long nRNo;
	COleDateTime dtLast;
	long nLastTNo;
} ST_ARIDER;

typedef struct 
{
	long nID;
	CString strBankName;
	CString strBankCode;
} ST_BANK;

typedef struct{
	long nCompany;
	long nRNo;
	long nCurCharge;
	long nBankID;

	CString strName;
	CString strBankAccount;
	CString strBankOwner;
	CString strHp;
} ST_RIDER_ACCOUNT;

typedef struct
{
	long nStartTerminalID;
	long nStartPosX;
	long nStartPosY;
	long nStartTerminalPoi;
	long nTerminalCharge;
	long nCID;
	long nKm;
	long nDestTerminalID;
	long nDestPosX;
	long nDestPosY;
	long nDestTerminalPoi;

	int nStartNearKm;
	int nElapsedTime;
	int nDestNearKm;
	int nWayType;
	int nTotalRank;

	CString strWayType;
	CString strStartTerminalTel;
	CString strDestTerminalTel;
	CString strStartTerminalName;
	CString strInterval;
	CString strDestTerminalName;
} ST_CONSIGN;

typedef struct
{
	long nStartCharge;
	long nTerminalCharge;
	long nDestCharge;
	long nTotalCharge;
	long nTempCharge;

	BOOL bLoad;
	BOOL bDestNomalCharge;
	BOOL bStartNomalCharge;
} ST_CASH_CHARGE;

typedef struct{
	long nState;
	long nRNo;
	long nRiderCompany;
	long nCarType;

	CString strStart;
	CString strDest;

	COleDateTime dtRcp;
} ST_EMPTY_ORDER;

typedef struct{
	long nRNo;
	long nRiderCompany;
	long nCarType;

	BOOL bEmpty;

	CString strRName;
	CString strLastLocation;
} ST_RIDER_STRUCT;

typedef struct{
	long nTNo;
	long nRNo;
	long nRiderCompany;
	long nCarType;

	CString strRName;
	CString strID;
	CString strOName;
	CString strOPhone;
	CString strOMobile;
	CString strSDong;
	CString strDDong;
	CString strRiderPhone;
} ST_ORDER_SMS;

typedef struct{
	long nCompany;
	long nState;
	long nChargeSum;
	long nPayType;
	long nChargeType;    

	COleDateTime dt1;

	CString strSDong;
	CString strDDong;
} ST_RIDER_ORDER;

typedef struct {
	UINT nState;
	UINT nTotal;

	BOOL bTwoWay;

	COleDateTime dtTime;

	CString strStart;
	CString strDest;	
} ST_ORDER_DATA;

typedef struct  
{
	long nOwnerCompany;		
	long nCompany;
	long nUseCount;
	long nNoUseCount;
}ST_RIDER_ACCOUNT_SIMPLE;

typedef struct {
	long nCompany;
	int nMNo;
	int nWorkState;
	int nDailyPay;
	int nInsentivePay;

	BOOL bUseInsentive;
	BOOL bUseDailyPay;
	
	COleDateTime dtWorkStateDate;

	CString strID;
	CString strName;
	CString strPart;
	CString strDailyPayMemo;
} ST_RIDER_INFO3;

typedef struct 
{
	long nCompany;
	long nRNo;
	long nPosX;
	long nPosY;
	long nCarType;

	CString strRName;
	CString strPOIName;
	
	COleDateTime dtLog;
} ST_RCP_RIDER_POS;

typedef struct{
	CString strOName;
	CString strOPhone;
	CString strOMobile;
	CString strODepart;
	CString strOManager;
	CString strODong;
	CString strODetail;
	CString strOMemo;
	CString strSName;
	CString strSPhone;
	CString strSMobile;
	CString strSDepart;
	CString strSManager;
	CString strSDong;
	CString strSDetail;
	CString strDName;
	CString strDPhone;
	CString strDMobile;
	CString strDDepart;
	CString strDManager;
	CString strDDong;
	CString strDDetail;
	CString strDt1;
	CString strEtc;
	CString strItemType;
	CString strIntercallEtc;
	CString strPayType;
	CString strCarType;
	CString strWayType;
	CString strRunType;
	CString strChargeSum;
	CString strChargeSum4;
	CString strChargeSum3;
	CString strChargeTrans;
	CString strChargeTrans4;
	CString strChargeTrans3;	
} ST_ALLOCATE_SMS;

typedef struct
{
	COleDateTime dtLastSms;
	COleDateTime dtDMLastSms;
	COleDateTime dtNewCustomer;
} ST_CHECK_INFO;


typedef struct {
	long nID;
	char szTitle[255]; 
	char szQuery[255];
} ST_FUNC_INFO;

typedef struct {
	int nTNo;
	int nCardType;
	int nCardProcess;
	int nCharge;
	CString strDisplayCharge;
	CString strSessionKey;
	CString strCardServerAddr;
	long uCardServerPort;
	CString strLogiServerAddr;
	long uLogiServerPort;
	long nFeeType;
	CString strError;
	CString strTID;
	CString strMID;
} ST_CARD_INFO;

typedef struct {
	long nCompany;
	long nVendorCode;
	CString strVendor;
} ST_CARD_VENDOR;

typedef struct
{
	long nType;
	CString strEmoticon;
} ST_EMOTICON;

typedef struct
{
	int jabara_add; 
	int lift_add; 
	int wing_body_add; 
	int lift_wing_add;
	int freezer_add;
} ST_SPECIAL_TRUCK_CHARGE;

typedef map<pair<int, int>, ST_SPECIAL_TRUCK_CHARGE> MAP_SPECIAL_TRUCK_CHARGE;


typedef map<long, CString> MAP_PHONE;
typedef CAtlMap<long, CString> ATLMAP_PHONE;
typedef map<long, MAP_PHONE> MAP_VEC_PHONE; 

typedef map<long, ST_EMOTICON> MAP_EMOTICON;
typedef map<long, ST_CARD_VENDOR> MAP_CARD_VENDOR;
typedef map<long, long> MAP_ROW_DATA;
typedef map<long, ST_BANK> MAP_BANK;
typedef map<long, ST_STATE_MENT> MAP_STATE_MENT;
typedef map<CString, ST_USER_SECTOR_COUNT> MAP_USER_SECTOR;
typedef map <long, ST_EDIT_HISTORY> MAP_EDIT_HISTORY;
typedef map<long, ST_COUNT_MILE*> MAP_COUNT_MILE;
typedef map<CXTPTaskPanelItem*, ST_BRANCH_INFO> MAP_BRANCH;
typedef map<CString,CBranchInfo*> MAP_LINE_GROUP;
typedef map<long, ST_RIDER_WORK_STATE_INFO> MAP_RIDER;
typedef map<long, ST_MEMBER_CHARGE_CNO*> MAP_MEMBER_CHARGE_CNO;
typedef map<long, ST_CHARGE_TYPE_NAME_INFO> MAP_CHARGE_TYPE_NAME;
typedef map<long, ST_SHARE_COMPANY_INFO> MAP_SHARED_COMPANY;
typedef map<long, long> MAP_CHILD_COMPANY;
typedef map<pair<UINT, UINT>, UINT> MAP_DEPOSIT_RATE;
typedef map<pair<long, long>, ST_ALLOC_RIDER> MAP_ALLOC_RIDER;
typedef map<long, long> MAP_INTERCALL_CUSTOMER;
typedef map<long, CString> MAP_ALLOCATE_GROUP;
typedef map<CWnd*, CBranchInfo*> CURRENT_CODE_INFO;
typedef map<CString, CBranchInfo*> COMPANY_APPLY_FROM_CITY_MAP3;

typedef map<DWORD, HBRUSH> MAP_WND_BRUSH;
typedef map<long, CustomerData> MAP_CUSTOMER_DATA;
typedef map<long, ST_CUSTOMER_GROUP_INFOMATION*> MAP_CUSTOMER_GROUP;
typedef map<pair<long, long>, ST_RIDER_MISC_INFO> MAP_RIDER_MISC_INFO;
typedef map<std::pair<long,long>, ST_RIDER_POS_INFO> MAP_RIDER_POS_INFO;

typedef vector<ST_CHARGE_SECTION_VALUE> VEC_CHARGE_SECTION_TYPE;
typedef vector<ST_CUSTOMER_GROUP_INFOMATION*> VEC_CUSTOMER_GROUP;
typedef vector<ST_RIDER_POS_INFO> VEC_RIDER_POS_INFO;

typedef CArray<CBranchInfo*, CBranchInfo*> ARRAY_BRANCH;
typedef CArray<CString, CString> ARRAY_CALL_ROUTE_SIDO;
typedef CArray<ST_RIDER_POS_OFFSET_INFO, ST_RIDER_POS_OFFSET_INFO> ARRAY_RIDER_POS_OFFSET_INFO;

typedef CArray<CPoint, CPoint> CNS_POINT_ARRAY;