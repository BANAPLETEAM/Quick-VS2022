

#pragma once

#ifndef _XTP_TOOLKIT_PRO
#define _XTP_TOOLKIT_PRO
// Lets help compiler to skip some headers
#define _XTP_EXCLUDE_CALENDAR
#define _XTP_EXCLUDE_SYNTAXEDIT
#define _XTP_EXCLUDE_RIBBON

#endif

#include "Resource.h"
#include "MkDatabase.h"
#include "MkCommand.h"
#include "MkRecordset.h"
#include "MkType.h"
#include "QSocket.h"
#include "QPacket.h"
#include "BanaLog.h"
#include "EncProfile.h"
#include "Excel.h"
#include "GlobalDefType.h"
#include "LogiFunc.h"
#include "GlobalFontManager.h"
#include "GlobalHandleManager.h"
#include "SmsDefine.h"
#include "CompanyInfo.h"
#include "MakeRcpPower.h"

#include "MyStatic.h"
#include "MyStaticTri.h"
#include "MarkupStatic.h"
#include "XTPListCtrl2.h"
#include "DataBox.h"
#include "DateButton.h"
#include "FlatEdit2.h"
#include "MyMarkupStatic.h"
#include "FlatComboBox.h"
#include "MyFormView.h"
#include "LogiMapNew.h"
#include "MyDialog.h"
#include "MyResizeDialog.h"
#include "RecPlayerDlg.h"
#include "LogiUtil.h"
#include "CustomerGroup.h"
#include "POIDataNew.h"

extern CCompanyInfo m_ci;
extern CSmsDefine m_sms;

extern CLogiUtil* LU;
extern CLogiFunc* LF;

#include "GlobalPaintManager.h"
#include "GlobalXTPListCtrl.h"
#include "GlobalXTPReportRecord.h"


#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

extern CGlobalFontManager m_FontManager;
extern CGlobalHandleManager m_HandleManager;

extern long		m_nSearchPoiDlg;

extern HINSTANCE m_hCommondll;

extern char* STR_PAY_TYPE[];

extern ARRAY_CALL_ROUTE_SIDO m_crs;
extern CCustomerGroup m_cg;
extern CMileageInfo m_mi;
extern CPOIData m_poi;
extern CUserDongPos m_mapUDongPos;
extern MAP_STATE_MENT m_mapStateMent;
extern ST_USER_INFO m_ui;
extern ST_ETC_INFO m_ei;
extern ST_SERVER_INFO m_si;
extern ARRAY_BRANCH m_ba, m_ba2;
extern MAP_CARD_VENDOR m_mapCardVendor;
extern MAP_SPECIAL_TRUCK_CHARGE g_special_truck_charge;

extern COMPANY_APPLY_FROM_CITY_MAP3 m_mapConCitySetting;
extern MAP_RIDER m_rm;
extern MAP_DEPOSIT_RATE m_dr;
extern VEC_CHARGE_SECTION_TYPE m_cst;
extern MAP_CHARGE_TYPE_NAME m_mapChargeType;
extern MAP_MEMBER_CHARGE_CNO m_mapMemberCharge1;
extern MAP_BANK m_mapBank;

extern 	CEncProfile encProfile;
extern CMkDatabase* m_pMkDb;
extern CMkDatabase* m_pMkDb2;
extern CMkDatabase* m_pMkDb4DrvLic;

extern CBranchInfo* m_pbiCur;
extern CURRENT_CODE_INFO m_CurCodeInfo;

extern MAP_LINE_GROUP m_LineGroup;

extern CPOIDataNew m_poiNew;

extern CCustomerData m_cus;

extern CMakeRcpPower m_pi;