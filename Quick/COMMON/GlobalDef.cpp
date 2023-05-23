
#include "stdafx.h"
#include "resource.h"
#include <Iphlpapi.h>
#include "POIData.h"
#include <imm.h> 
#include "MileageInfo.h"
#include "UserDongPos.h"
#include "CustomerData.h"

#pragma comment( lib, "imm32.lib" )
#pragma comment(lib, "iphlpapi.lib")

ST_USER_INFO m_ui;
CCompanyInfo m_ci;
CSmsDefine m_sms;
ST_ETC_INFO m_ei;
ST_SERVER_INFO m_si;
ARRAY_BRANCH m_ba, m_ba2;

MAP_RIDER m_rm;
CPOIData m_poi;
ARRAY_CALL_ROUTE_SIDO	m_crs;
MAP_DEPOSIT_RATE m_dr;
VEC_CHARGE_SECTION_TYPE m_cst;
CCustomerGroup m_cg;
CMileageInfo m_mi;
CUserDongPos m_mapUDongPos;
MAP_CHARGE_TYPE_NAME m_mapChargeType;
MAP_MEMBER_CHARGE_CNO m_mapMemberCharge1;
MAP_BANK m_mapBank;
CMkDatabase *m_pMkDb		= NULL;
CMkDatabase *m_pMkDb2		= NULL;
CMkDatabase *m_pMkDb4DrvLic = NULL;
long m_nSearchPoiDlg = 0;
HINSTANCE m_hCommondll;
CEncProfile encProfile;
CGlobalFontManager m_FontManager;
CGlobalHandleManager m_HandleManager;
CMakeRcpPower m_pi;
CBranchInfo *m_pbiCur = NULL;
MAP_LINE_GROUP m_LineGroup;
CPOIDataNew m_poiNew;
CCustomerData m_cus;
MAP_STATE_MENT m_mapStateMent;
COMPANY_APPLY_FROM_CITY_MAP3 m_mapConCitySetting;
MAP_CARD_VENDOR m_mapCardVendor;
MAP_SPECIAL_TRUCK_CHARGE g_special_truck_charge;

char* STR_PAY_TYPE[] = {"선불", "착불", "신용", "송금", "수금", "", "", "카드"};

CLogiUtil* LU;
CLogiFunc* LF;


