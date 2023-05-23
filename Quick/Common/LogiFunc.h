#pragma once

#include "POIUnit.h" 
#include "CompanyInfo.h"

class CCustomerGroup;
class CMileageInfo;
class CPOIData;
class CUserDongPos;
class CLogiUtil;
class CLogiFunc;
class CPOIDataNew;
class CCustomerData;

class CLogiFunc
{
public:
	CLogiFunc();
	virtual ~CLogiFunc();

	MAP_PHONE m_mapRiderPhone;
	MAP_VEC_PHONE m_mapNosmsPhone;
	MAP_EMOTICON m_mapEmoticon;

	DWORD m_dwLastInput;
	CArray<MONITORINFOEX, MONITORINFOEX> m_aryMonitors;
	
	CString	GetMyNumberFormat(CString strNumber);
	CString	GetMyNumberFormat(long nNumber);
	CString	GetNoneDashNumber(CString strPhoneNumber);
	CString GetModuleFullPath();
	void FillBackground(CDC *pDC, CWnd *pWnd, 
		COLORREF clrTop = COLOR_DEFAULT_TOP_WND, 
		COLORREF clrBottom = COLOR_DEFAULT_DOWN_WND);
	COLORREF GetRiderColor(int nColorType);
	CString GetRiderColorString(int nColorType);
	CString GetTwoToneMarkup(CString strMsg1, CString strMsg2, 
		BOOL bHasHead = FALSE, BOOL bHasTail = FALSE,
		CString strColor1 = "Black", CString strColor2 = "Green",
		BOOL bBold1 = FALSE, BOOL bBold2 = TRUE);
	void GetAutoGradientColor(COLORREF crSrc, COLORREF &crDst1, COLORREF &crDst2, long nScale = 0);
	void FillGradient(CDC *pDC, COLORREF crBack, CRect rcClient, long nScale = 20);
	BOOL OnMyCtlColor(CDC* pDC, CWnd* pWnd, UINT &nCtlColor, HBRUSH &hRetBrush);
	CString GetMyFileVersion();
	BOOL DllRegOcx(CString strPath);
	BOOL IsAllocOrder(int nState, BOOL bIncludeFinishOrder = TRUE);
	void RepositionLogConsole();
	void GetMonitorArray();
	CString GetZeroPadding(int nNumber, int nLen = 6);
	CString GetElapsedTimeString(COleDateTimeSpan span, BOOL bRemoveSec = 0);
	BOOL GetHandleScreenSize(CWnd *pWnd, CRect &rcScreen);
	void HideBehindControl(CWnd *pParent, CWnd *pWnd, BOOL bHide, CPtrArray *ppaExceptWnd = NULL);
	long GetControlDigit(CEdit *pEdit);

	void DrawRoundRect(CDC *pDC, CWnd *pMain, CWnd *pWnd1, CWnd *pWnd2 = NULL, long nLeftMargin = 0, long nTopMargin = 0, long nRightMargin = 0, long nBottomMargin = 0, COLORREF rgb = RGB(245, 245, 245), BOOL bRound = TRUE);
	void DrawRoundRect(CDC *pDC, CWnd *pMain, CRect rc, long nLeftMargin = 0, long nTopMargin = 0, long nRightMargin = 0, long nBottomMargin = 0, COLORREF rgb = RGB(245, 245, 245), BOOL bRound = TRUE);
	void MakeLineVertical(CDC *pDC, CWnd *pMain, CWnd *pLeftWnd, CWnd *RightWnd, long nTopMargin = 0, long nBottomMargin = 0, long nSize = 1, COLORREF rgb = RGB(0xbb, 0xbb, 0xbb));

	void LoadRiderPhone();
	void LoadNoSmsPhone(long nCompany);
	MAP_PHONE* GetRiderPhoneMap() {return &m_mapRiderPhone;};
	MAP_PHONE* GetNosmsPhoneMap(long nCompany) 
	{ 
		MAP_VEC_PHONE::iterator it = m_mapNosmsPhone.find(nCompany);
		return &it->second;
	};


	MAP_EMOTICON *GetEmoticonMap() {return &m_mapEmoticon;};
	void FillEmotioconMap();





/// <summary>
///  global
/// </summary>

public:
	CString GetWebUploadUrl(CString strUseage, LONG nTNo);
	BOOL ConnectDrvLicSvr();
	CString GetInternetReceiptType(int nReceiptType);
	BOOL IsBranch(long nCompany);
	void MyTokenize(CString strInput, CString strDivide, BOOL bEpthyInsert, CStringArray& strArr);
	CString GetDiscountType(long nDiscount);
	CString GetGrade(long nGrade, BOOL bShowDefault = TRUE);
	int GetGradeColor(long nGrade);
	char* UTF8ToANSI(const char* pszCode);

	CString GetWeekChartTitle(COleDateTime dtDate);
	CString GetMyFileName();
	BOOL IsSoftIce95();
	BOOL IsSoftIceNT();
	CString GetLicenseStateString(int nType, BOOL* pbLicenseOK);
	long GetCommaCount(CString sCommaString);

	int AFXAPI MsgBox(CString strMsg, CString strCaption = "확인", UINT nType = MB_ICONINFORMATION);
	int AFXAPI MsgBox(UINT nIDPrompt, CString strCaption = "확인", UINT nType = MB_ICONINFORMATION);

	BOOL GetFileVersion(char* filename, VS_FIXEDFILEINFO* pvsf);
	BOOL RunProgram(CString strFileName, CString strArg);
	void StatusText(UINT nPane, CString strMsg);
	BOOL GetMacAddress(BOOL bShowMsg = FALSE);
	CString FormatString(const char* format, ...);
	void AddSecurityLog(long nCompany, long nType, long nStaffNo,
		CString strData1, CString strData2, CString strData3);
	void AddSecurityLog(long nCompany, long nType, long nStaffNo, long nData);
	void AddSecurityLog(long nCompany, long nType, long nData);
	int CheckSum(void* buffer, int nLen);

	CString RemoveZero(long nData);
	CString RemoveZero(CString strData);

	BOOL IsBrokenHangul(CString& strText);
	CString GetHddId();
	inline CBranchInfo* GetCurBranchInfo(BOOL bAllowVirtualCompany = FALSE);
	CString& StringMakeUpper(CString& str);
	CString GetDepositTypeStringFromType(int nType);
	CString GetDepositAllocateTypeStringFromType(int nType);
	ST_SMS_INFO GetSMSBalance(long nCompany);
	long GetNowBranchCode();

	CString GetHostName();

	CString GetFixedDepositStateString(int nState);
	int GetNoneCommaNumber(CString strNumber);

	int GetChargeType(int nStartType, int nDestType);
	int GetChargeDongTypeInfo(long nDongID);


	BOOL POWER_CHECK(long nPower, CString strPowerName = "", BOOL bDisplayMsg = FALSE);
	BOOL ChangeRiderWorkState(long nCompany, long nRNo, BOOL bIntegrated, CString strWorkTitle, CString strWorkMemo, BOOL bWorkStop);
	BOOL IsIntegrated(long nCompany = -1);

	void SetHanEngMode(HWND hWnd, BOOL bHan);

	long GetDepositTypeToComboSel(long nDepositType);
	long GetDepositTypeFromComboSel(long nSel);
	void CreateDir(char* Path);

	long GetDepositAllocateTypeToComboSel(long nDepositAllocateType);
	long GetDepositAllocateTypeFromComboSel(long nSel);
	BOOL IsNumeric(LPCTSTR pszText);
	BOOL SendSmsNew(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
		CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, BOOL bMsgBox = FALSE);
	BOOL SendSmsNewRev(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
		CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, COleDateTime dtRev, BOOL bMsgBox = FALSE);
	BOOL SendPDASimple(long nCompany, long nRiderCompany, long nRNo, CString sMsg);
	void SetCrystal(CWnd* pWnd, int index);
	void FillVaildRiderData();
	long GetCarTypeForCharge(long nCarType);

	BOOL NotifyPenalty(int nPenalty);
	CBranchInfo* GetBranchInfo(long nCompany);
	BOOL AddCustomerTel(long nCompany, long nCNo, long nTelID, CString strPhone);
	void GetItemCommaToArray(CString strItem, CStringArray& arryItem);
	CString GetRemoveDDDNumber(CString strPhone, long nCompany = 0);
	void GetOnlyDistance(long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY, CWnd* pReturnMsgWnd);
	CString GetCancelReason(long nReason);
	BOOL IsExceptionDetailDongUse(CPOIUnit* pDong);

	BOOL SendUpdateFile(CMkDatabase& db, CString strLocalPath, CString strServerPath);
	CString EnCodeStr(CString ToCode);

	void SetEditText(CEdit* pEdit, CString strText, BOOL bFront);
	BOOL IsCash(long nPayType);
	BOOL IsThisCompany(CString strCompanyName, long nCompany = 0, long nShareCode1 = 0);
	CString GetDateTimeToString(COleDateTime dtDate, int nType, BOOL bShowDay);
	CString GetMyDateString(COleDateTime dt, BOOL bDisplayCentury, BOOL* pbSpecialDate);
	CString GetValueByArg(CString& strDataSet, CString strArg);
	BOOL IsKoreaWord(CString strWord);
	CString GetTwoPhone(CString strPhone1, CString strPhone2);
	CString GetTwoPhoneAsterisk(CString strPhone1, CString strPhone2);
	void MakeModaless();
	long GetStringLengthByAscII(CString strText);
	BOOL LengthCheck(HWND hwnd, long nApplyID, long nLengthStaticID, int nLength, CString strControlName);
	BOOL ChangeFixedDepositState(long nID, long nState);
	COleDateTime GetCompareDate(BOOL bWeeklyDeposit, COleDateTime dtMaindDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay);
	long GetAbilityDay(long nDay, long nYear, long nMonth);
	void InitGroupReportStruct(GROUP_REPORT& stSum);
	CString GetGroupReportText(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord);
	CString GetGroupReportText1(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord);
	BOOL SaveAllocateInfo(ST_RIDER_INFO_ALLOCATE* pSimple, BOOL pSimpleMode = FALSE);
	BOOL CheckGroupReport(CString strGNo, long nDstGNo, COleDateTime dtDate, long nMemberCount, CString& strNeedReReportID);
	BOOL ReReport(CString strNeedReReport);
	BOOL SaveIncomeInfo(ST_RIDER_INFO_INCOME* pIncome, BOOL pSimpleMode = FALSE);
	void InitRiderIncomeStruct(ST_RIDER_INFO_INCOME* st);
	BOOL IsCrossOrder(long nTNo, CString& sCName, long& nState);
	void FillBankCode(BOOL bRefresh = FALSE, CComboBox* pCmb = NULL, long nBankID = 0);
	long GetIndexFromBankID(CComboBox* pCmb, long nBankID);
	CString GetBankName(long nBankID);
	long GetWindowTextLong(CWnd* pEdit);
	void FillStateMent();
	void SaveToReg(ST_RIDER_MAP_SET_INFO& info);
	void LoadFromReg(ST_RIDER_MAP_SET_INFO& info);
	void SaveToReg(ST_RCP_DLG_SET_INFO& info);
	void LoadFromReg(ST_RCP_DLG_SET_INFO& info);
	void SaveToReg(ST_RCP_MAP_SET_INFO& info);
	void LoadFromReg(ST_RCP_MAP_SET_INFO& info);

	CString GetRcpType(long nRcpType, BOOL bInterNet);
	BOOL IsWindow7();
	BOOL IsWindowXP();
	long GetTailShowTimeFromIndex(long nIndex);
	CString GetStringFromLong(long nLong, BOOL bReturnZero = TRUE);
	CString IsMoveRiderOk(long nCompany, long nRNo);
	void MakeCarTypeCombo(CComboBox* pCmbBox);
	void SetCarType(CComboBox* pCmbBox, long nCarType);
	long GetCarType(CComboBox* pCmbBox);
	BOOL IsRequestOver15Day(int nCompany);

	long GetCardVendor(long nCompany);
	void LoadCardInfo();
	BOOL CheckCardPayCondition(long nTNo, long nCharge, long nDeposit, CString& strError);
	BOOL GetCardPayType(ST_CARD_INFO& st, BOOL bUseForTranCance);
	CString GetMyCardNumber(CString strCardNumber);
	BOOL SendNiceCardPay(CMkDatabase* pMkCardDb, int nTranType, int nTNo, int nBillkey, CString strCardNumber, CString strMM, CString strYY, CString strWCompany, CString strWNo, CString& strMsg, BOOL bSendSms);
	CString GetMyNumberFadding(CString strNumber, int nLen = 4);
	CString GetDay(COleDateTime dt);
	BOOL IsCardCheckState(long nState, long nCancelType);
	long GetCardRealPay(long nTNo);
	CString ChangeStringFromExcel(VARIANT varValue);
	long GetShareLevel(long nShareCode1, long nShareCode2, long nShareCode3, long nShareCode4, long nShareCode5);
	CString GetFolderDate(CString strFileName);
	long GetRemoveMyNumberFormat(CString strNumber);
	void MoveFocus(CWnd* pWnd);
	BOOL IsUseNewDlg();
	CString RemoveComma(CString strNumber);
	CString GetStringFromEdit(CWnd* pEdit);
	long GetLongFromEdit(CWnd* pEdit);
	CString GetRemoveLastDong(CString strDong);
	BOOL IsDate(CString strTemp);
	CString GetRiderPhone(long nRiderCompany, long nRNo);
	CString GetDashCardNumber(CString strCardNumber);
	CString GetSMSTelCorp(int nState);
	CString GetSMSTelecomState(int nState);
	CString GetSMSTelUse(int nState);
	CString GetSMSFileStateType(int nState, int nTelType = 0);
	BOOL UpdateRiderCardState(CString strCardNumber, long nCompany, long nRNo, CString& strRName);
	BOOL InsertNewCard(CString strCardNumber, long nCompany, long nRNo);
	int GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2);
	BOOL MakeShareOrder(long nTNo, BOOL bShare);
	DWORD HexStrToInt(CString aStr);
	CString GetCustomerEMail(long nCNo);
	BOOL IsMobilePhoneNumber(CString strText);


	CString ConvertStringToSendData(const CString& s, CByteArray& msg);
	CString ConvertStringToSendData(CString strText);
	CString ConvertStringToSendData(CByteArray* msg);

	BOOL IsNumber(LPCTSTR pszText);
	void AddTextMiddle(CString strText, CEdit* pEdit);
	BOOL UpdateSaveMent(long nID, CString strMent);
	BOOL InsertSaveMent(long nCompany, long nType, CString strMent);
	BOOL SendSmsBulkTest(long nCompany, long nTranID, CString strRecvPhone, CString strCallBackPhone,
		CString strMsg, CString strEtc);

	BOOL DeleteSaveMent(long nID);

	BOOL UpChargeForNotAllocate(long nTNo, long nCharge, CWnd* pMsgBox);
	CString GetSecondTimeString(int nSec, BOOL bRemoveSec = 0);
	CString GetAsteriskPhoneNumber(CString strPhoneNumber);
	BOOL InsertAllocGroupCombo(CComboBox* pCombo, long nCompany);
	CString GetAutoDDDSetting(int nCompany, CString strCallingLine);
	BOOL GetConnetcInfo(CString& strAddr, long& nPort);

	BOOL IsDID(int nDID, CString strSearchDID);
	BOOL FindNumber(int nMaxIndex, CString strNumber, CString strTotalNumber);
	BOOL UpdateRiderInfoForReserved(long nTNo, long nRiderCompany, long nRNo);
	CString GetSMSCallBackLogState(int nState);
	BOOL CheckTel(CString strTel);
	BOOL IsLocalNumber(CString strPhone, CString& strRemoveDDD);

	void FillSpeicalTruckChage();
	bool IsHangul(const char* text);
	bool IsEnglish(const char* text);
	std::vector<CString> GetNeighboringCity(CString sido);

	CString  GetDashPhoneNumberRemoveDDD(CString strPhoneNumber);
	CString  GetNoneDashNumberRemoveDDD(CString strPhoneNumber);


public:	// INLINE
	CString GetStateString(UINT nState);
	int GetStateFromString(CString sState);
	int GetCarTypeFromString(CString strCarType);
	int GetCarChargeType(long nCarType);
	CString GetCarChargeTypeString(long nCarType);
	CString GetCarTypeFromLong(long nCarType, BOOL bHideBaseType = 0, long nTruckType = 0, CString strTon = "");
	CString GetWayTypeFromLong(long nWayType, BOOL bHideBaseType = 0, long nLoadType = 0);
	CString GetPayTypeFromLong(long nPayType, BOOL bHideBaseType = 0, long nCardState = 0);
	CString GetRunTypeFromLong(long nRunType, BOOL bHideBaseType = 0);
	int GetRunTypeFromString(CString strRunType);
	int GetWayTypeFromString(CString strWayType);
	CString GetReportState(long nReportState);
	BOOL IsCarTypeTruck(long nCarType);

	UINT GetImageNumber(int nState, int nSubState = 0, int nCTNo = 0);
	long GetMyUnNumberFormat(CString strCharge);
	long GetMyUnNumberFormatEdit(CWnd* pWnd);
	CString GetMyNumberFormatEdit(CWnd* pWnd);
	CString GetEditString(CWnd* pWnd);
	CString GetDashPhoneNumber(CString strPhoneNumber);
	BOOL WriteRegistryInt(HKEY hKey, CString strSubKey, CString strValueKey, int nValue);
	BOOL IsStringDigit(CString strText);
	BOOL IsPhoneNumber(CString strText);

protected:
	BOOL m_bGroup;

};

AFX_INLINE CString CLogiFunc::GetStateString(UINT nState)
{
	if (nState == 10) return "접수";
	else if (nState == 11) return "개별";
	else if (nState == 15) return "발송";
	else if (nState == 20) return "실패";
	else if (nState == 30) return "배차";
	else if (nState == 31) return "픽업";
	else if (nState == 35) return "완료";
	else if (nState == 40) return "취소";
	else if (nState == 60) return "문의";
	else if (nState == 70) return "공지";
	else if (nState == 72) return "요청";
	else if (nState == 80) return "오더묶음";
	else if (nState == 81) return "오더묶음해제";
	else if (nState == 90) return "지연알림";
	else if (nState == 91) return "지연알림해제";
	else if (nState == 92) return "자동대기설정";
	else if (nState == 93) return "자동대기해제";
	else if (nState == 2) return "인터넷";
	else if (nState == 3) return "현장";
	else if (nState == 5) return "이동";
	else if (nState == 8) return "대기";
	else if (nState == 9) return "예약";
	else if (nState == 1) return "공지";
	else if (nState == 100) return "공유";
	else if (nState == 200) return "수정";
	else if (nState == 300) return "이동";
	else if (nState == 400) return "취소";
	else return "UNKNOWN";
}

AFX_INLINE int CLogiFunc::GetStateFromString(CString sState)
{
	if (sState == "접수") return 10;
	else if (sState == "개별") return 11;
	else if (sState == "발송") return 15;
	else if (sState == "실패") return 20;
	else if (sState == "배차") return 30;
	else if (sState == "픽업") return 31;
	else if (sState == "완료") return 35;
	else if (sState == "취소") return 40;
	else if (sState == "문의") return 60;
	else if (sState == "공지") return 70;
	else if (sState == "요청") return 72;
	else if (sState == "인터넷") return 2;
	else if (sState == "현장") return 3;
	else if (sState == "이동") return 5;
	else if (sState == "대기") return 8;
	else if (sState == "예약") return 9;
	else if (sState == "공지") return 1;
	else if (sState == "공유") return 100;
	else if (sState == "수정") return 200;
	else if (sState == "이동") return 300;
	else if (sState == "취소") return 400;

	return 0;
}


AFX_INLINE CString CLogiFunc::GetCarChargeTypeString(long nCarType)
{
	CString sCarType = "";
	if (nCarType == 0)
		sCarType = "오토";
	else if (nCarType == 1)
		sCarType = "다마";
	else if (nCarType == 2)
		sCarType = "라보";
	else if (nCarType == 3)
		sCarType = "승용";
	else if (nCarType == 4)
		sCarType = "트럭";

	return sCarType;
}

AFX_INLINE int CLogiFunc::GetCarTypeFromString(CString strCarType)
{
	if (strCarType == "오토" ||
		strCarType == "") return 0;
	else if (strCarType == "짐받이" ||
		strCarType == "짐받이오토바이") return 1;
	else if (strCarType == "다마") return 2;
	else if (strCarType == "라보") return 3;
	else if (strCarType == "밴") return 4;
	else if (strCarType == "트럭") return 5;
	else if (strCarType == "지하철") return 10;
	else if (strCarType == "당일택배") return 20;
	else return -1;
}

AFX_INLINE BOOL CLogiFunc::IsCarTypeTruck(long nCarType)
{
	if (nCarType == CAR_TRUCK ||
		nCarType == CAR_1_4_TON ||
		nCarType == CAR_2_5_TON ||
		nCarType == CAR_3_5_TON ||
		nCarType == CAR_5_TON ||
		nCarType == CAR_5_TON_PLUS ||
		nCarType == CAR_8_TON ||
		nCarType == CAR_11_TON ||
		nCarType == CAR_14_TON ||
		nCarType == CAR_15_TON ||
		nCarType == CAR_18_TON ||
		nCarType == CAR_25_TON)
		return TRUE;

	return FALSE;
}

AFX_INLINE int CLogiFunc::GetCarChargeType(long nCarType)
{

	if (nCarType == CAR_AUTO || nCarType == CAR_BIGBIKE)
		return 0;
	else if (nCarType == CAR_DAMA)
		return 1;
	else if (nCarType == CAR_LABO)
		return 2;
	else if (nCarType == CAR_VAN || nCarType == CAR_6VAN)
		return 3;
	else if (nCarType == CAR_TRUCK || nCarType == CAR_TRUCK || nCarType == CAR_1_4_TON
		|| nCarType == CAR_2_5_TON || nCarType == CAR_3_5_TON || nCarType == CAR_5_TON)
		return 4;
	else if (nCarType == CAR_SUBWAY)
		return 5;
	else if (nCarType == CAR_2_5_TON)
		return 6;
	else if (nCarType == CAR_3_5_TON)
		return 7;
	else if (nCarType == CAR_5_TON)
		return 8;

	return -1;
}

AFX_INLINE CString CLogiFunc::GetCarTypeFromLong(long nCarType, BOOL bHideBaseType, long nTruckType, CString strTon)
{
	CString car_type = "알수없음";
	if (nCarType == CAR_AUTO) car_type = bHideBaseType ? "" : "오토";
	else if (nCarType == CAR_BIGBIKE) car_type = "짐받이";
	else if (nCarType == CAR_DAMA) car_type = "다마";
	else if (nCarType == CAR_LABO) car_type = "라보";
	else if (nCarType == CAR_VAN) car_type = "3밴";
	else if (nCarType == CAR_TRUCK) car_type = "1톤";
	else if (nCarType == CAR_1_4_TON) car_type = "1.4톤";
	else if (nCarType == CAR_SUBWAY) car_type = "지하철";
	else if (nCarType == CAR_PS) car_type = "당일택배";
	else if (nCarType == CAR_6VAN) car_type = "6밴";
	else if (nCarType == CAR_2_5_TON) car_type = "2.5톤";
	else if (nCarType == CAR_3_5_TON) car_type = "3.5톤";
	else if (nCarType == CAR_5_TON) car_type = "5톤";
	else if (nCarType == CAR_11_TON) car_type = "11톤";
	else if (nCarType == CAR_18_TON) car_type = "18톤";
	else if (nCarType == CAR_25_TON) car_type = "25톤";
	else if (nCarType == CAR_SEDAN) car_type = "승용";
	else if (nCarType == CAR_5_TON_PLUS) car_type = "5톤축";
	else if (nCarType == CAR_8_TON) car_type = "8톤";
	else if (nCarType == CAR_14_TON) car_type = "14톤";
	else if (nCarType == CAR_15_TON) car_type = "15톤";

	if (nTruckType == CARGO_JABARA)	car_type += "(자바라)";
	else if (nTruckType == CARGO_LIFT)	car_type += "(리프트)";
	else if (nTruckType == CARGO_WING_BODY)	car_type += "(윙바디)";
	else if (nTruckType == CARGO_LIFT_WING)	car_type += "(리프트윙)";
	else if (nTruckType == CARGO_FREEZER)	car_type += "(냉동)";

	return car_type;
}

AFX_INLINE CString CLogiFunc::GetWayTypeFromLong(long nWayType, BOOL bHideBaseType, long nLoadType)
{
	CString strWay;

	if (nWayType == 0)
		strWay = bHideBaseType ? "" : "편도";
	else if (nWayType == 1)
		strWay = "왕복";
	else if (nWayType == 2)
		strWay = "경유";
	else
		return "알수없음";

	if (nLoadType > 0)
	{
		if (strWay.GetLength() > 0)
			strWay = strWay.Left(2) + "/" + "혼";
		else
			strWay = "혼적";
	}

	return strWay;
}

AFX_INLINE int CLogiFunc::GetWayTypeFromString(CString strWayType)
{
	if (strWayType == "왕복" ||
		strWayType == "왕/혼")
		return 1;
	else if (strWayType == "경유" ||
		strWayType == "경/혼")
		return 2;
	else
		return 0;
}

AFX_INLINE CString CLogiFunc::GetPayTypeFromLong(long nPayType, BOOL bHideBaseType, long nCardState)
{
	if (nPayType == 0)
		return bHideBaseType ? "" : "선불";
	else if (nPayType == 1)
		return "착불";
	else if (nPayType == 2)
		return "신용";
	else if (nPayType == 3)
		return "송금";
	else if (nPayType == 4)
		return "직접수금";
	else if (nPayType == 6)
		return "마일";

	else if (nPayType == 7)
	{
		CString sCharge = "", sFaceCard = "";
		sCharge.Format("%d", nCardState);
		if (sCharge.Right(2).Compare("15") == 0)
			sFaceCard = "대면";
		//sFaceCard = "(F)";

		if (nCardState < 10)
			return sFaceCard + "카드";
		if (nCardState < 100)
			return sFaceCard + "카드(미결제)";
		if (nCardState > 100 && nCardState < 200)
			return sFaceCard + "카드(결제)";
		if (nCardState > 200 && nCardState < 300)
			return sFaceCard + "카드(결제취소)";
	}
	else
		return "알수없음";

	return "알수없음";
}

AFX_INLINE CString CLogiFunc::GetRunTypeFromLong(long nRunType, BOOL bHideBaseType)
{
	if (nRunType == ZERO)
		return bHideBaseType ? "" : "일반";
	else if (nRunType == ONE)
		return "완급";
	else if (nRunType == TWO)
		return "긴급";
	else if (nRunType == FOUR)
		return "특급";
	else if (nRunType == EIGHT)
		return "동승";
	else
		return "알수없음";
}

AFX_INLINE int CLogiFunc::GetRunTypeFromString(CString strRunType)
{
	if (strRunType == "완급")
		return ONE;
	else if (strRunType == "긴급")
		return TWO;
	else if (strRunType == "특긴급")
		return FOUR;
	else if (strRunType == "동승")
		return EIGHT;
	else
		return ZERO;
}


AFX_INLINE CString CLogiFunc::GetReportState(long nReportState)
{
	if (nReportState == 0)
		return "정산완료";
	else if (nReportState == 10)
		return "부분입금";
	else if (nReportState == 20)
		return "입금완료";

	return "알수없음";

}

AFX_INLINE CString CLogiFunc::GetLicenseStateString(int nType, BOOL* pbLicenseOK)
{
	switch (nType)
	{
	case 0: *pbLicenseOK = TRUE; return "정상";
	case 2: *pbLicenseOK = TRUE; return "조회중오류발생";
	case -4: *pbLicenseOK = TRUE; return "정상(면허분실상태)";
	case -1: *pbLicenseOK = FALSE; return "면허이상(정지or취소)";
	case -2: *pbLicenseOK = FALSE; return "주민번호와성명 불일치";
	case -3: *pbLicenseOK = FALSE; return "면허번호 오류";
	case -5: *pbLicenseOK = FALSE; return "성명 오류";
	case -6: *pbLicenseOK = FALSE; return "주민번호 오류";
	default: *pbLicenseOK = FALSE; return "알수없음";
	}

	return "알수없음";
}

AFX_INLINE UINT CLogiFunc::GetImageNumber(int nState, int nSubState, int nCTNo)
{
	if (nCTNo > 0)
	{
		if (nState == 8 || nState == 10)
			return 19;
	}

	if (nSubState != 0)
	{
		if (nState == 35 && nSubState == 10)
			return 18;
	}
	switch (nState)
	{
	case 2:	return 8;
	case 3: return 6;
	case 5: return 7;
	case 8: return 9;
	case 9: return 0;
	case 10:return 1;
	case 11:return 2;
	case 15:return 10;
	case 20:return 11;
	case 30:return 3;
	case 31:return 15;      //퀵 픽업
		//case 32:return 3;		//###픽업아이콘 다른것으로 변경요망
	case 35:return 4;
	case 40:return 5;
	case 60:return 12;
	case 70:return 13;
	case 100: return 14;
	case 101: return 20;
	}
	return 5;
}

AFX_INLINE long CLogiFunc::GetMyUnNumberFormat(CString strCharge)
{
	int nSub = 1;
	CString strTempCharge = "0", strSub = "";
	strTempCharge = strCharge;
	strTempCharge.Replace(",", "");
	strSub = strTempCharge.Left(1);
	if (strSub.Compare("-") == 0)
	{
		nSub = -1;
		strTempCharge.Replace("-", "");
	}
	if (!IsStringDigit(strTempCharge))
		return 0;

	return atol(strTempCharge) * nSub;
}

AFX_INLINE long CLogiFunc::GetMyUnNumberFormatEdit(CWnd* pWnd)
{

	CString strEditValue = "";
	CEdit* pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if (strEditValue.GetLength() <= 0)
		return 0;

	return GetMyUnNumberFormat(strEditValue);
}

AFX_INLINE CString CLogiFunc::GetMyNumberFormatEdit(CWnd* pWnd)
{
	CString strEditValue = "";
	CEdit* pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if (strEditValue.GetLength() <= 0)
		return "";
	return GetMyNumberFormat(GetMyUnNumberFormat(strEditValue));
}

AFX_INLINE CString CLogiFunc::GetEditString(CWnd* pWnd)
{
	CString strEditValue = "";
	CEdit* pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if (strEditValue.GetLength() <= 0)
		return "";

	return strEditValue;
}

AFX_INLINE CString CLogiFunc::GetDashPhoneNumber(CString strPhoneNumber)
{
	CString strNumber = strPhoneNumber;

	strNumber.Remove('-');

	if (strNumber.GetLength() > 6)
	{
		int nOffset = 0, nRightLen;

		if (strNumber.Left(2) == "02") {
			nOffset = 3;
			strNumber.Insert(2, "-");
		}
		else if (strNumber.GetAt(0) == '0') {
			nOffset = 4;
			strNumber.Insert(3, "-");
		}

		nRightLen = strNumber.FindOneOf("~,./") != -1 ?
			strNumber.FindOneOf("~,./") : strNumber.GetLength();

		if (nRightLen > 4) strNumber.Insert(nRightLen - 4, "-");
	}

	return strNumber;
}

AFX_INLINE BOOL CLogiFunc::WriteRegistryInt(HKEY hKey, CString strSubKey, CString strValueKey, int nValue)
{
	CString strValue = _T("");
	HKEY hSubKey = NULL;

	if (::RegOpenKeyEx(hKey, (LPCSTR)strSubKey, 0, KEY_ALL_ACCESS, &hSubKey) == ERROR_SUCCESS)
	{
		::RegSetValueEx(hSubKey, (LPCSTR)strValueKey, NULL, REG_DWORD, (LPBYTE)&nValue, sizeof(int));
		::RegCloseKey(hSubKey);

		return TRUE;
	}
	return FALSE;
}


AFX_INLINE BOOL CLogiFunc::IsStringDigit(CString strText)
{
	for (int i = 0; i < strText.GetLength(); i++)
		if (!isdigit((::byte)strText.GetAt(i)))
			return FALSE;

	return TRUE;
}

AFX_INLINE BOOL CLogiFunc::IsPhoneNumber(CString strText)
{
	for (int i = 0; i < strText.GetLength(); i++) {
		if ((::byte)strText.GetAt(i) != '-' && !isdigit((::byte)strText.GetAt(i))) {
			return FALSE;
		}
	}

	return TRUE;
}