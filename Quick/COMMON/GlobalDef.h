

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
#include "POIUnit.h" 

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

extern inline CString GetMyNumberFormat(CString strNumber);
extern inline CString GetMyNumberFormat(long nNumber);

extern CCompanyInfo m_ci;
extern CSmsDefine m_sms;

#include "GlobalPaintManager.h"
#include "GlobalXTPListCtrl.h"
#include "GlobalXTPReportRecord.h"


#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

class CCustomerGroup;
class CMileageInfo;
class CPOIData;
class CUserDongPos;
class CLogiUtil;
class CLogiFunc;
class CPOIDataNew;
class CCustomerData;
//class CCompanyInfo;


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

extern CLogiUtil* LU;
extern CLogiFunc* LF;

extern CBranchInfo* m_pbiCur;
extern CURRENT_CODE_INFO m_CurCodeInfo;

extern MAP_LINE_GROUP m_LineGroup;

extern CPOIDataNew m_poiNew;

extern CCustomerData m_cus;

extern CString GetInternetReceiptType(int nReceiptType);
extern inline CString GetStateString(UINT nState);
extern inline int GetStateFromString(CString sState);
extern inline int GetCarTypeFromString(CString strCarType);
extern inline int GetCarChargeType(long nCarType);
extern inline CString GetCarChargeTypeString(long nCarType);
extern inline CString GetCarTypeFromLong(long nCarType, BOOL bHideBaseType = 0, long nTruckType = 0, CString strTon = "");
extern inline CString GetWayTypeFromLong(long nWayType, BOOL bHideBaseType = 0, long nLoadType = 0);
extern inline CString GetPayTypeFromLong(long nPayType, BOOL bHideBaseType = 0, long nCardState = 0);
extern inline CString GetRunTypeFromLong(long nRunType, BOOL bHideBaseType = 0);
extern inline int GetRunTypeFromString(CString strRunType);
extern inline int GetWayTypeFromString(CString strWayType);
extern inline CString GetReportState(long nReportState);
extern inline BOOL IsCarTypeTruck(long nCarType);

extern inline UINT GetImageNumber(int nState,int nSubState = 0, int nCTNo = 0);
extern inline long GetMyUnNumberFormat(CString strCharge);
extern inline long GetMyUnNumberFormatEdit(CWnd *pWnd);
extern inline CString GetMyNumberFormatEdit(CWnd *pWnd);
extern inline CString GetEditString(CWnd *pWnd);
extern inline CString GetDashPhoneNumber(CString strPhoneNumber);
extern inline BOOL WriteRegistryInt(HKEY hKey, CString strSubKey, CString strValueKey, int nValue);
extern inline CString GetNoneDashNumber(CString strPhoneNumber);
extern inline CString  GetDashPhoneNumberRemoveDDD(CString strPhoneNumber);
extern inline CString  GetNoneDashNumberRemoveDDD(CString strPhoneNumber);
extern inline BOOL IsStringDigit(CString strText);
extern CString GetWebUploadUrl(CString strUseage, LONG nTNo);
extern inline BOOL IsPhoneNumber(CString strText);
extern BOOL IsBranch(long nCompany);
extern void MyTokenize(CString strInput, CString strDivide, BOOL bEpthyInsert, CStringArray &strArr);
extern CString GetDiscountType(long nDiscount);
extern CString GetGrade(long nGrade, BOOL bShowDefault = TRUE);
extern int GetGradeColor(long nGrade);
extern char* UTF8ToANSI(const char *pszCode);

extern CString GetWeekChartTitle(COleDateTime dtDate);
extern CString GetModuleFullPath();
extern CString GetMyFileName();
extern BOOL IsSoftIce95();
extern BOOL IsSoftIceNT();
extern CString GetLicenseStateString(int nType, BOOL *pbLicenseOK);
extern long GetCommaCount(CString sCommaString);

extern int AFXAPI MsgBox(CString strMsg, CString strCaption = "확인", UINT nType = MB_ICONINFORMATION);
extern int AFXAPI MsgBox(UINT nIDPrompt, CString strCaption = "확인", UINT nType = MB_ICONINFORMATION);

extern BOOL GetFileVersion(char *filename, VS_FIXEDFILEINFO *pvsf);
extern BOOL RunProgram(CString strFileName, CString strArg);
extern void StatusText(UINT nPane, CString strMsg);
extern void StatusText(UINT nPane, UINT nResource);
extern BOOL GetMacAddress(BOOL bShowMsg = FALSE);
extern CString FormatString(const char* format, ...);
extern void AddSecurityLog(long nCompany, long nType, long nStaffNo, 
						   CString strData1, CString strData2, CString strData3);
extern void AddSecurityLog(long nCompany, long nType, long nStaffNo, long nData);
extern void AddSecurityLog(long nCompany, long nType, long nData);
extern int CheckSum(void *buffer, int nLen);

extern CString RemoveZero(long nData);
extern CString RemoveZero(CString strData);

extern BOOL IsBrokenHangul(CString &strText);
extern CString GetHddId();
extern inline CBranchInfo* GetCurBranchInfo(BOOL bAllowVirtualCompany = FALSE);
extern CString &StringMakeUpper(CString &str);
extern CString GetDepositTypeStringFromType(int nType);
extern CString GetDepositAllocateTypeStringFromType(int nType);
extern ST_SMS_INFO GetSMSBalance(long nCompany);
extern long GetNowBranchCode();

extern CString GetHostName();

extern CString GetFixedDepositStateString(int nState);
extern int GetNoneCommaNumber(CString strNumber);

extern int GetChargeType(int nStartType, int nDestType);
extern int GetChargeDongTypeInfo(long nDongID);


extern BOOL POWER_CHECK(long nPower, CString strPowerName = "", BOOL bDisplayMsg = FALSE);
extern BOOL ChangeRiderWorkState(long nCompany, long nRNo, BOOL bIntegrated, CString strWorkTitle, CString strWorkMemo, BOOL bWorkStop);
extern BOOL IsIntegrated(long nCompany = -1);  

extern void SetHanEngMode(HWND hWnd, BOOL bHan);

extern long GetDepositTypeToComboSel(long nDepositType);
extern long GetDepositTypeFromComboSel(long nSel);
extern void CreateDir(char* Path);

extern long GetDepositAllocateTypeToComboSel(long nDepositAllocateType);
extern long GetDepositAllocateTypeFromComboSel(long nSel);
extern BOOL IsNumeric(LPCTSTR pszText);
extern BOOL SendSmsNew(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
					   CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, BOOL bMsgBox = FALSE);
extern BOOL SendSmsNewRev(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
						  CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, COleDateTime dtRev, BOOL bMsgBox = FALSE);
extern BOOL SendPDASimple(long nCompany, long nRiderCompany, long nRNo, CString sMsg);
extern void SetCrystal(CWnd *pWnd, int index);
extern void FillVaildRiderData();
extern long GetCarTypeForCharge(long nCarType);

extern BOOL NotifyPenalty(int nPenalty);
extern CBranchInfo * GetBranchInfo(long nCompany);
extern BOOL AddCustomerTel(long nCompany, long nCNo, long nTelID, CString strPhone);
extern void GetItemCommaToArray(CString strItem, CStringArray &arryItem);
extern CString GetRemoveDDDNumber(CString strPhone, long nCompany = 0);
extern void GetOnlyDistance(long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY, CWnd* pReturnMsgWnd);
extern CString GetCancelReason(long nReason);
extern BOOL IsExceptionDetailDongUse(CPOIUnit *pDong);

#ifndef _DEBUG
extern LONG WINAPI TheCrashHandlerFunction(EXCEPTION_POINTERS * pExPtrs);
extern LONG WINAPI TheCrashHandlerNormalFunction(EXCEPTION_POINTERS * pExPtrs);
#endif

extern BOOL SendUpdateFile(CMkDatabase &db, CString strLocalPath, CString strServerPath);
extern CString EnCodeStr(CString ToCode);

extern void SetEditText(CEdit *pEdit, CString strText, BOOL bFront); 
extern BOOL IsCash(long nPayType);
extern BOOL IsThisCompany(CString strCompanyName, long nCompany = 0, long nShareCode1 = 0);
extern CString GetDateTimeToString(COleDateTime dtDate,int nType,BOOL bShowDay);
extern CString GetMyDateString(COleDateTime dt, BOOL bDisplayCentury, BOOL *pbSpecialDate);
extern CString GetValueByArg(CString& strDataSet, CString strArg);
extern BOOL IsKoreaWord(CString strWord);
extern CString GetTwoPhone(CString strPhone1, CString strPhone2);
extern CString GetTwoPhoneAsterisk(CString strPhone1, CString strPhone2);
extern void MakeModaless();
extern long GetStringLengthByAscII(CString strText);
extern BOOL LengthCheck(HWND hwnd, long nApplyID, long nLengthStaticID, int nLength, CString strControlName);
extern BOOL ChangeFixedDepositState(long nID, long nState);
extern COleDateTime GetCompareDate(BOOL bWeeklyDeposit, COleDateTime dtMaindDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay);
extern long GetAbilityDay(long nDay, long nYear, long nMonth);
extern void InitGroupReportStruct(GROUP_REPORT &stSum);
extern CString GetGroupReportText(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord);
extern CString GetGroupReportText1(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord);
extern BOOL SaveAllocateInfo(ST_RIDER_INFO_ALLOCATE *pSimple,  BOOL pSimpleMode = FALSE);
extern BOOL CheckGroupReport(CString strGNo, long nDstGNo, COleDateTime dtDate, long nMemberCount, CString &strNeedReReportID);
extern BOOL ReReport(CString strNeedReReport);
extern BOOL SaveIncomeInfo(ST_RIDER_INFO_INCOME *pIncome, BOOL pSimpleMode = FALSE);
extern void InitRiderIncomeStruct(ST_RIDER_INFO_INCOME *st);
extern BOOL IsCrossOrder(long nTNo, CString &sCName, long &nState);
extern void FillBankCode(BOOL bRefresh = FALSE, CComboBox *pCmb = NULL, long nBankID = 0);
extern long GetIndexFromBankID(CComboBox *pCmb, long nBankID);
extern CString GetBankName(long nBankID);
extern long GetWindowTextLong(CWnd *pEdit);
extern void FillStateMent();
extern void SaveToReg(ST_RIDER_MAP_SET_INFO &info);
extern void LoadFromReg(ST_RIDER_MAP_SET_INFO &info);
extern void SaveToReg(ST_RCP_DLG_SET_INFO &info);
extern void LoadFromReg(ST_RCP_DLG_SET_INFO &info);
extern void SaveToReg(ST_RCP_MAP_SET_INFO &info);
extern void LoadFromReg(ST_RCP_MAP_SET_INFO &info);

extern CString GetRcpType(long nRcpType, BOOL bInterNet);
extern BOOL IsWindow7();
extern BOOL IsWindowXP();
extern long GetTailShowTimeFromIndex(long nIndex);
extern CString GetStringFromLong(long nLong, BOOL bReturnZero = TRUE);
extern CString IsMoveRiderOk(long nCompany, long nRNo);
extern void MakeCarTypeCombo(CComboBox *pCmbBox);
extern void SetCarType(CComboBox *pCmbBox, long nCarType);
extern long GetCarType(CComboBox *pCmbBox);
extern BOOL IsRequestOver15Day(int nCompany);

extern long GetCardVendor(long nCompany);
extern void LoadCardInfo();
extern BOOL CheckCardPayCondition(long nTNo, long nCharge, long nDeposit, CString &strError);
extern BOOL GetCardPayType(ST_CARD_INFO &st, BOOL bUseForTranCance);
extern CString GetMyCardNumber(CString strCardNumber);
extern BOOL SendNiceCardPay(CMkDatabase* pMkCardDb, int nTranType, int nTNo, int nBillkey, CString strCardNumber, CString strMM, CString strYY, CString strWCompany, CString strWNo, CString& strMsg, BOOL bSendSms);
extern CString GetMyNumberFadding(CString strNumber, int nLen = 4);
extern CString GetDay(COleDateTime dt);
extern BOOL IsCardCheckState(long nState, long nCancelType);
extern long GetCardRealPay(long nTNo);
extern CString ChangeStringFromExcel(VARIANT varValue);
extern long GetShareLevel(long nShareCode1, long nShareCode2, long nShareCode3, long nShareCode4, long nShareCode5);
extern CString GetFolderDate(CString strFileName);
extern long GetRemoveMyNumberFormat(CString strNumber);
extern void MoveFocus(CWnd *pWnd);
extern BOOL IsUseNewDlg();
extern CString RemoveComma(CString strNumber);
extern CString GetStringFromEdit(CWnd *pEdit);
extern long GetLongFromEdit(CWnd *pEdit);
extern CString GetRemoveLastDong(CString strDong);
extern BOOL IsDate(CString strTemp);
extern CString GetRiderPhone(long nRiderCompany, long nRNo);
extern CString GetDashCardNumber(CString strCardNumber);
extern CString GetSMSTelCorp(int nState);
extern CString GetSMSTelecomState(int nState);
extern CString GetSMSTelUse(int nState);
extern CString GetSMSFileStateType(int nState, int nTelType = 0);
extern BOOL UpdateRiderCardState(CString strCardNumber, long nCompany, long nRNo, CString &strRName);
extern BOOL InsertNewCard(CString strCardNumber, long nCompany, long nRNo);
extern int GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2);
extern BOOL MakeShareOrder(long nTNo, BOOL bShare);
extern DWORD HexStrToInt(CString aStr);
extern CString GetCustomerEMail(long nCNo);
extern BOOL IsMobilePhoneNumber(CString strText);


extern CString ConvertStringToSendData(const CString & s, CByteArray & msg);
extern CString ConvertStringToSendData(CString strText);
extern CString ConvertStringToSendData(CByteArray *msg);

extern BOOL IsNumber(LPCTSTR pszText);
extern void AddTextMiddle(CString strText, CEdit *pEdit);
extern BOOL UpdateSaveMent(long nID, CString strMent);	
extern BOOL InsertSaveMent(long nCompany, long nType, CString strMent);
extern BOOL SendSmsBulkTest(long nCompany, long nTranID, CString strRecvPhone, CString strCallBackPhone,
							CString strMsg, CString strEtc);

extern BOOL DeleteSaveMent(long nID);

extern BOOL UpChargeForNotAllocate(long nTNo, long nCharge, CWnd *pMsgBox);
extern CString GetSecondTimeString(int nSec, BOOL bRemoveSec = 0);
extern CString GetAsteriskPhoneNumber(CString strPhoneNumber);
extern BOOL InsertAllocGroupCombo(CComboBox *pCombo, long nCompany);
extern CString GetAutoDDDSetting(int nCompany, CString strCallingLine);
extern BOOL GetConnetcInfo(CString &strAddr, long &nPort);

extern BOOL IsDID(int nDID, CString strSearchDID);
extern BOOL FindNumber(int nMaxIndex, CString strNumber, CString strTotalNumber);
extern BOOL UpdateRiderInfoForReserved(long nTNo, long nRiderCompany, long nRNo);
extern CString GetSMSCallBackLogState(int nState);
extern BOOL CheckTel(CString strTel);
extern BOOL IsLocalNumber(CString strPhone, CString &strRemoveDDD);

extern void FillSpeicalTruckChage();
extern BOOL IsCarTypeTruck(int car_type);
extern bool IsHangul(const char* text);
extern std::vector<CString> GetNeighboringCity(CString sido);